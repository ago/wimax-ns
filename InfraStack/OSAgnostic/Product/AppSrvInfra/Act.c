/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 3. Neither the name of the Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/
#include "Act.h"

#include "wimax_osal_primitives.h"
#include "wimax_osal_types.h"
#include "wimax_osal_string.h"
#include "wimax_osal_event_logger.h"

#include "TraceModule.h"
#include "WrappersUtils.h"
#include "L5OpCodes.h"			
#include "L4ConfigurationManager.h"
#include "L4MsgProxy.h"
#include "L5Dispatcher.h"
#include "L5SocketsDispatcher.h"
#include "DeviceConfiguration.h"

#include "Services_Ctrl.h"
#include "VersionUtils.h"

#include "wimax_osal_event_logger.h"

#include "wmxSDK_Msc_2.h"

#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Nds_3.h"		
#include "wmxSDK_Sup_L5.h"

#include "NDnSAgent.h"

#include "SupplicantAgent.h"

#include "KDapiAdapter.h"

static UINT32 agentsInitialized;
static UINT32 agentsStarted;

// for L5 layer
static L5_CONNECTION g_act_Connection = NULL;
static tL5DispatcherFunctions *g_act_pFuncs = NULL;
static tUtilityFunctions *g_act_Utils = NULL;

// The act_mutex_ctrl is initialized outside ACT (so during restart it doesn't change)
// It is used to synchronize initializations and shutdowns.
OSAL_mutex_t act_mutex_ctrl = NULL;	

static wmx_ModeOfOperation_t operationMode = ModeOfOperationNormal; 
static BOOL isL5DispatcherOpen = FALSE;
// because both error reports (internal and ctrl) will restart all entities, we will act only apon the first report
// (internal problem report won't reset the driver, but if after
// restarting all appsrv entities we will still have driver problems then we will reset the driver)

// The thread that handles the messages ACT receives -
// We cannot process these messages on the context of the sending thread (because we need to stop the 
// socket dispatcher, for example). We also don't want to use the messenger thread (because we don't want that 
// the messenger will wait on the mutex and these messages cannot be processed during initialization or shutdown)
// So we use this thread. It lives from initialization until shutdown.
static OSAL_thread_t act_thread_messagesHandler = NULL;

// The events that cause the act_thread_messagesHandler to act
static OSAL_event_t act_event_driverUp = NULL;
static OSAL_event_t act_event_ctrlProblem = NULL;
static OSAL_event_t act_event_internalProblem = NULL;
static OSAL_event_t act_event_resetForProduction = NULL;
static OSAL_event_t act_event_stopDriverUpThread = NULL;
static OSAL_event_t act_event_deviceProblem = NULL;
static OSAL_event_t act_event_fullRestart = NULL;
static OSAL_event_t act_event_kdapiAdapterRestart = NULL;
static OSAL_event_t act_event_resetDevice = NULL;
static OSAL_event_t act_event_updateAgentsEvent = NULL;

static OSAL_event_t act_event_driverUpEvent = NULL;
static OSAL_event_t act_event_driverDownEvent = NULL;

static BOOL devicePresent = TRUE;

static UINT32	configReason;
static BOOL		isConfigReasonValid = FALSE;

DRIVER_STATUS isDriverConnected = DRIVER_DOWN;
DRIVER_STATUS lastReportedIsDriverConnected = DRIVER_DOWN;

static LONG isDriverInitialized = 0;
static BOOL useTraces = FALSE;
static BOOL isActStarted = FALSE;
static BOOL isRemote = FALSE;

#define INTIALIZE(x)	&x##_Initialize()
#define FINALIZE(x)		&x##_Finalize()
#define START(x)		&x##_Start()
#define STOP(x)			&x##_Stop()

void Act_RestartDriver();
BOOL UpdateDriverStateToAgents();

// ----------- Instrumentation related changes -----------------

agent_Initialize pfn_DnDAgent_Initialize;
agent_Finalize pfn_DnDAgent_Finalize;
agent_Start pfn_DnDAgent_Start;
agent_Stop pfn_DnDAgent_Stop;
agent_EventHandler pfn_DnDAgent_EventHandler;

agent_Initialize pfn_MOCMsgProxy_Initialize;
agent_Finalize pfn_MOCMsgProxy_Finalize;
agent_Start pfn_MOCMsgProxy_Start;
agent_Stop pfn_MOCMsgProxy_Stop;
agent_EventHandler pfn_MOCMsgProxy_EventHandler;

/*
p_DnDAgent_Finalize pfn_DnDAgent_Finalize;
p_L4DnDHndlr_IsMonFiltered pfn_L4DnDHndlr_IsMonFiltered;
p_L4DnDHndlr_PostMon pfn_L4DnDHndlr_PostMon;
p_AddMessageToQueue pfn_AddMessageToQueue;
*/

APPSRV_INIT_ST LoadInstrumentationModule();
void UnloadInstrumentationModule();


tL5DispatcherFunctions *GetL5Funcs()
{
	return g_act_pFuncs;
}

tUtilityFunctions *GetUtilsFuncs()
{
	static tUtilityFunctions funcs = {
		&Messenger_PostRequest,
		&Messenger_PopRequest,
		NULL,//&TraceAgent_WriteTrace,
		&KDAPI_ADAPTER_SetTraceIndicatiosCB
	};

	return &funcs;
}

BOOL Act_GetConfigReason(UINT32 *reason)
{
	if (isConfigReasonValid)
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_GetConfigReason: Valid config reason of %d detected", configReason);
		*reason = configReason;
		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_GetConfigReason: No valid config reason");
	
	return FALSE;
}

// The function looks for the registry key that holds the mode of operation. If no key is found return Normal
// TODO: Delete that function when reset L3L4 message is implemented
wmx_ModeOfOperation_t ReadOperationMode()
{
	UINT32 answer = 0;
	wmx_ModeOfOperation_t modeOfOperation = ModeOfOperationNormal;
	
	L4Configurations_getModeOfOperationProduction(&answer);

	if  (1 == answer) 
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "Set mode of operation Production - registry key");
		modeOfOperation = ModeOfOperationProduction;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "Set mode of operation Normal - registry key");
	}

	return modeOfOperation;
}

/*
APPSRV_INIT_ST LoadInstrumentationModule()
{
	char inst_lib_full_path[MAX_PATH];
	BOOL bTmpRet;

	bTmpRet = L4Configurations_getInstrumentationLibName(inst_lib_full_path);

	if ( !bTmpRet || inst_lib_full_path[0] == '\0' )
		return INIT_CONFIG_FAIL;

	if ( (p_inst_lib = OSAL_load_lib(inst_lib_full_path)) == NULL ) 
		return INIT_CONFIG_FAIL;

	if ( ( (pfn_DnDAgent_Initialize = (agent_Initialize)OSAL_find_symbol(p_inst_lib, "DnDAgent_Initialize")) == NULL) 
		|| ( (pfn_DnDAgent_Finalize = (agent_Finalize)OSAL_find_symbol(p_inst_lib, "DnDAgent_Finalize")) == NULL) 
		|| ( (pfn_DnDAgent_Start = (agent_Start)OSAL_find_symbol(p_inst_lib, "DnDAgent_Start")) == NULL) 
		||  ( (pfn_DnDAgent_Stop = (agent_Stop)OSAL_find_symbol(p_inst_lib, "DnDAgent_Stop")) == NULL) 
		||  ( (pfn_DnDAgent_EventHandler = (agent_EventHandler)OSAL_find_symbol(p_inst_lib, "DnDAgent_EventHandler")) == NULL) 
		|| ( (pfn_MOCMsgProxy_Initialize = (agent_Initialize)OSAL_find_symbol(p_inst_lib, "MOCMsgProxy_Initialize")) == NULL) 
		|| ( (pfn_MOCMsgProxy_Finalize = (agent_Finalize)OSAL_find_symbol(p_inst_lib, "MOCMsgProxy_Finalize")) == NULL) 
		|| ( (pfn_MOCMsgProxy_Start = (agent_Start)OSAL_find_symbol(p_inst_lib, "MOCMsgProxy_Start")) == NULL) 
		||  ( (pfn_MOCMsgProxy_Stop = (agent_Stop)OSAL_find_symbol(p_inst_lib, "MOCMsgProxy_Stop")) == NULL) 
		||  ( (pfn_MOCMsgProxy_EventHandler = (agent_EventHandler)OSAL_find_symbol(p_inst_lib, "MOCMsgProxy_EventHandler")) == NULL) )
	{		
		TRACE(TR_MOD_ACT, TR_SEV_ALERT, "Loading instrumentation module has failed");
		return INIT_CONFIG_FAIL;
	}
	
	return INIT_SUCCESS;
}


void UnloadInstrumentationModule()
{

	if ( p_inst_lib != NULL )		
	{
		OSAL_close_lib(p_inst_lib);
		p_inst_lib = NULL;
	}
}
*/

void Act_FiniPipe()
{
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "IN");
	L4_Msg_Proxy_Shutdown();
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "L4MsgProxy Shut down successfully");
	L5_SOCKETS_DISPATCHER_Shutdown();
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Socket server Shut down successfully");
	L5_DISPATCHER_Shutdown();
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Dispatcher shut down successfully");
	Messenger_Shutdown();
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "OUT");
}

BOOL Act_InitPipe()
{
	if (!Messenger_Initialize())
	{		
		return FALSE;
	}

	if (!Messenger_Start())
	{		
		return FALSE;
	}

	if (!L5_DISPATCHER_Initialize())
	{
		return FALSE;
	}

	if (!L5_SOCKETS_DISPATCHER_Initialize())
	{
		return FALSE;
	}

	if (!L4_Msg_Proxy_Initialize())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL Act_RegisterSystemStateCB()
{
	wmx_Status_t send_st;	
	long stateReportReg = 0;

	send_st = wmx_RegisterOnDriverReport(&stateReportReg, L3_L4_OPCODE_REPORT_STATE, *g_act_pFuncs, g_act_Connection);
	if( send_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot get state. wmx_SendL4Command returned %d", send_st);
		return FALSE;
	}
	
	return TRUE;
}
BOOL Act_SentINITState()
{
	wmx_Status_t driver_st, send_st;
	InitCommand_type initCommand;
	L4BM_Init_InitCommand(&initCommand);
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "setting INIT mode");
	send_st = wmx_SendL4Command( &initCommand, InitCommand_Funcs, *g_act_pFuncs, g_act_Connection, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set INIT. wmx_SendL4Command returned %d", send_st);
		return FALSE;
	}
	if( driver_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set INIT. driver returned %d", driver_st);
		return FALSE;
	}
	return TRUE;

}

BOOL Act_GetSystemState(E_SystemState *systemState)
{
	wmx_Status_t driver_st, send_st;
	GetState_type getState;

		
	TRACE(TR_MOD_ACT, TR_SEV_ERR, "Entering...");
	L4BM_Init_GetState(&getState);

	send_st = wmx_SendL4Command( &getState, GetState_Funcs, *g_act_pFuncs, g_act_Connection, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot get state. wmx_SendL4Command returned %d", send_st);
		return FALSE;
	}
	if( driver_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot get state. driver returned %d", driver_st);
		return FALSE;
	}

	*systemState = getState.SystemState.value;	

	if(*systemState == E_SYSTEM_STATE_CONFIG)
	{
		configReason = getState.LastReason.value;
	}
		
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "System state is %d", *systemState);

	return TRUE;
}
BOOL Act_SetDeviceConfigParam()
{
	wmx_Status_t driver_st, send_st;
	//GetState_type getState;
	SetPreInitConfiguration_type ledConfigurationStruct;
	E_SystemState systemState;
	
	L4BM_Init_SetPreInitConfiguration(&ledConfigurationStruct);
	//L4BM_Init_GetState(&getState);
	
	if (!Act_GetSystemState(&systemState))
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_GetSystemState failed!!");
		return FALSE;
	}

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "in Act_SetDeviceLEDParam function state is %d", systemState);

	if(systemState == E_SYSTEM_STATE_CONFIG)
	{
		// [Oran]
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got CONFIG system state with a reason of %d", configReason);
		//configReason = getState.LastReason.value;
		isConfigReasonValid = TRUE;	
		if(!Populate_PreInitConfigurationStruct(&ledConfigurationStruct))
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "there are no config param values in function Populate_PreInitConfigurationStruct");
			
			if(!Act_SentINITState())
			{
				TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_SentINITState failed");
				return FALSE;
			}
		}
		else
		{
			send_st = wmx_SendL4Command( &ledConfigurationStruct, SetPreInitConfiguration_Funcs, *g_act_pFuncs, g_act_Connection, &driver_st );
			
			if( send_st != WMX_ST_OK )
			{
				TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set LED param. wmx_SendL4Command returned %d", send_st);
			}
			if( driver_st != WMX_ST_OK )
			{
				TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set LED param. driver returned %d", driver_st);
			}
			
			if(!Act_SentINITState())
			{
				TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_SentINITState failed");
				return FALSE;
			}
		}		
	}

	return TRUE;
}
// Get the system state. If the state is E_SYSTEM_STATE_INIT run set mode of operation (NORMAL of PRODUCTION)
BOOL Act_SetOperationMode()
{
	wmx_Status_t driver_st, send_st;
	ModeOfOperationCommand_type setMode;
	//GetState_type getState;
	E_SystemState systemState;
	int i = 0;

	do
	{			
		Act_GetSystemState(&systemState);
		OSAL_sleep(200);
		i++;
	}
	//while((getState.SystemState.value == E_SYSTEM_STATE_CONFIG) && i<10);
	while((systemState == E_SYSTEM_STATE_CONFIG) && i<10);
	
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Trying to set the operation mode. system state=%d", systemState);

	if(systemState == E_SYSTEM_STATE_INIT)
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "setting the operation mode");
		operationMode = ReadOperationMode();
		setMode.ModeOfOperation.Type = L3L4_TLV_TYPE_MODE_OF_OPERATION;
		setMode.ModeOfOperation.value = (operationMode == ModeOfOperationProduction) ? E_MODE_OF_OPERATION_PRODUCTION : E_MODE_OF_OPERATION_NORMAL;
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Mode of operation=%s",(operationMode == ModeOfOperationProduction) ? "E_MODE_OF_OPERATION_PRODUCTION" : "E_MODE_OF_OPERATION_NORMA");

		// Return the operation mode to Normal for the next initiation of the driver
		operationMode = ModeOfOperationNormal;
		send_st = wmx_SendL4Command( &setMode, ModeOfOperationCommand_Funcs, *g_act_pFuncs, g_act_Connection, &driver_st );
		if( send_st != WMX_ST_OK )
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set mode of operation to %d. wmx_SendL4Command returned %d", operationMode, send_st);
			return FALSE;
		}
		if( driver_st != WMX_ST_OK )
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set mode of operation to normal. driver returned %d", driver_st);
			return FALSE;
		}
	}
	//else if((getState.SystemState.value == E_SYSTEM_STATE_UNINITIALIZED) || (getState.SystemState.value == E_SYSTEM_STATE_CONFIG))
	else if((systemState == E_SYSTEM_STATE_UNINITIALIZED) || (systemState == E_SYSTEM_STATE_CONFIG))
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "cannot set mode of operation to normal. system state %d - wrong state", systemState);
		return FALSE;
	}

	return TRUE;
}

void Act_ConfigInitSequence()
{
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_ConfigInitSequence(IN)");

	TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "Sending: PreInit Config");
	if(!Act_SetDeviceConfigParam())
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_SetDeviceConfigParam failed");
		return;
	}

	// setting the driver mode of operation
	TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "Sending: ModeOfOperation");
	if(!Act_SetOperationMode())
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_SetOperationMode failed");					
		return;
	}

	OSAL_reset_event(act_event_ctrlProblem);

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_ConfigInitSequence(OUT)");	
}

void Act_MessagesHandler(L5_CONNECTION Conn,
						 L5_TARGET_ID nOriginID,

						 UINT32 dwSentMessageID,
						 void  *pvSentBuffer,
						 UINT32 cbSentBufferSize,

						 UINT32 *pdwResponseMessageID,
						 void  *pvResponseBuffer,
						 UINT32 *cbResponseBufferSize,

						 void *pvUserContext,
						 void *pvReserved )
{
	wmx_pVersionEntry_t versionToValidate;
	wmx_Version_t appsrvVersion;
	wmx_Version_t expectedPipeHandlerVersion;
	VERSION_RESULT versionResult;
	UINT32 responseBufferSize;
	ReportState_type stateReport;
	wmx_Status_t st;	

	UNREFERENCED_PARAMETER(res);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbSentBufferSize);
	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(Conn);	

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_MessagesHandler(IN). pdwResponseMessageID=%d",pdwResponseMessageID);
	if(pdwResponseMessageID != NULL)
	{
		*pdwResponseMessageID = WMX_ST_OK;
	}

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_MessagesHandler(IN). dwSentMessageID=%d",dwSentMessageID);
	switch(dwSentMessageID)
	{
		case ACT_OPCODE_GET_DRIVER_STATE:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got ACT_OPCODE_GET_DRIVER_STATE message");
			if (OSAL_atomic_compareExchange((LPLONG)&isDriverConnected, DRIVER_UP, DRIVER_UP))
			{
				*pdwResponseMessageID = DRIVER_UP;
			}
			else
			{
				*pdwResponseMessageID = DRIVER_DOWN;
			}
			break;

		case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got L4_PROXY_OPCODE_L4_INDICATION_ARRIVED message");
			switch ( L4BM_GetOpcode((UINT8*)pvSentBuffer) )
			{
			case L3_L4_OPCODE_REPORT_STATE:				
				// get the report state struct
				if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &stateReport, ReportState_Funcs, &st ) != WMX_ST_OK )
				{
					*pdwResponseMessageID = WMX_ST_FAIL;
					return;
				}
				if( st != WMX_ST_OK )
				{
					*pdwResponseMessageID = st;
					return;
				}

				if (L3L4_TLV_TYPE_SYSTEM_STATE == stateReport.SystemState.Type)
				{
					TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got system state report. system state=%d , isL5DispatcherOpen=%d",
						stateReport.SystemState.value, isL5DispatcherOpen);
					if (E_SYSTEM_STATE_CONFIG == stateReport.SystemState.value)
					{
						//Check if need to start config-init sequence
						OSAL_set_event(act_event_updateAgentsEvent);
					}					
					if (!isL5DispatcherOpen && 
						((E_SYSTEM_STATE_READY == stateReport.SystemState.value) ||
						(E_SYSTEM_STATE_SCAN == stateReport.SystemState.value) ||
						(E_SYSTEM_STATE_DATA_PATH_CONNECTED == stateReport.SystemState.value) ||
						(E_SYSTEM_STATE_RF_OFF == stateReport.SystemState.value))
						)
					{
						OSAL_set_event(act_event_updateAgentsEvent);
					}
				}
				break;
			}			
		break;

		case ACT_OPCODE_VALIDATE_VERSION:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got ACT_OPCODE_VALIDATE_VERSION message");
			responseBufferSize = sizeof(versionResult);
			if ((*cbResponseBufferSize) < responseBufferSize)
			{
				if(pdwResponseMessageID != NULL)
				{
					*pdwResponseMessageID = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
				}
			}							
			SET_VERSION(expectedPipeHandlerVersion, PIPE_HANDLER_MAJOR, PIPE_HANDLER_MINOR, PIPE_HANDLER_BUILD, PIPE_HANDLER_REVISION, PIPE_HANDLER_BRANCH);			
			versionToValidate = (wmx_pVersionEntry_t)pvSentBuffer;				
			//versionResult = ValidateVersion(versionToValidate->moduleName, versionToValidate->version, expectedPipeHandlerVersion);
			memcpy(pvResponseBuffer, &versionResult, responseBufferSize);	
			*cbResponseBufferSize = responseBufferSize;
			return;

		case ACT_OPCODE_GET_VERSION:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got ACT_OPCODE_GET_VERSION message");
			responseBufferSize = sizeof(wmx_Version_t);
			if ((*cbResponseBufferSize) < responseBufferSize)
			{
				if(pdwResponseMessageID != NULL)
				{
					*pdwResponseMessageID = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
				}
			}							
			SET_VERSION(appsrvVersion, APPSRV_MAJOR, APPSRV_MINOR, APPSRV_BUILD, APPSRV_REVISION, APPSRV_BRANCH);			
			memcpy(pvResponseBuffer, &appsrvVersion, responseBufferSize);	
			*cbResponseBufferSize = responseBufferSize;
			return;

		// We cannot process the following messages on the context of the sending thread (because we need to stop the 
		// socket dispatcher, for example). We also don't want to use the messenger thread (because we don't want that 
		// the messenger will wait for the mutex and these messages cannot be processed during initialization or shutdown)
		// So we use wake the messages handling thread by setting the proper events
/*
		case ACT_OPCODE_DRIVER_UP:
			OSAL_set_event(act_event_driverUp);
			devicePresent = TRUE;
			return;
*/
		case ACT_OPCODE_RESET_FOR_PRODUCTION:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got ACT_OPCODE_RESET_FOR_PRODUCTION message");
			OSAL_set_event(act_event_resetForProduction);
			break;

		case ACT_OPCODE_DEVICE_REMOVED:
		case ACT_OPCODE_KDAPI_ADAPTER_RESTART:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "ACT_OPCODE_DEVICE_REMOVED - ACT_OPCODE_KDAPI_ADAPTER_RESTART");
			devicePresent = FALSE;
			OSAL_set_event(act_event_kdapiAdapterRestart);
			break;

		case ACT_OPCODE_FULL_RESTART:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "ACT_OPCODE_FULL_RESTART");
			OSAL_set_event(act_event_fullRestart);
			break;
		
		case ACT_OPCODE_CLOSE:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got ACT_OPCODE_CLOSE message");			
			OSAL_set_event(act_event_stopDriverUpThread);
			Act_Finalize();			
			break;

		case ACT_OPCODE_RESET_DEVICE:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Got ACT_OPCODE_RESET_DEVICE message");
			OSAL_set_event(act_event_resetDevice);
			L4Pub_CmdReset();
			break;

		case ACT_OPCODE_ERROR_REPORT:
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "ACT_OPCODE_ERROR_REPORT. dwSentMessageID=%d",(*(UINT32*)pvSentBuffer));
			switch (*(UINT32*)pvSentBuffer)
			{				
			case CTRL_PROBLEM:
				OSAL_set_event(act_event_ctrlProblem);				
				break;

			case INTERNAL_PROBLEM:
				TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "INTERNAL_PROBLEM - doing full restart");
				OSAL_set_event(act_event_fullRestart);				
				break;

			case DEVICE_PROBLEM:
				TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "DEVICE_PROBLEM - doing driver restart");
				OSAL_set_event(act_event_kdapiAdapterRestart);				
				break;

			default:	// wrong opcode in buffer
				if(pdwResponseMessageID != NULL)
				{
					*pdwResponseMessageID = WMX_ST_INVALID_OPCODE;
				}
				break;
			}
			break;

		default:	// opcode is not supported
			if(pdwResponseMessageID != NULL)
			{
				*pdwResponseMessageID = WMX_ST_INVALID_OPCODE;
			}
			break;
	}
}


void Act_FreeInternalResources()
{
	//wmxTerminateThread(act_event_stopDriverUpThread, &act_thread_messagesHandler, TR_MOD_ACT);
	OSAL_set_event(act_event_stopDriverUpThread);
	OSAL_timedjoin_thread(act_thread_messagesHandler, SHUTDOWN_TIMEOUT, NULL);
	
	if(act_event_stopDriverUpThread != NULL)
	{
		OSAL_delete_event(act_event_stopDriverUpThread);
		act_event_stopDriverUpThread = NULL;
	}

	if(act_event_driverUp != NULL)
	{
		OSAL_delete_event(act_event_driverUp);
		act_event_driverUp = NULL;
	}

	if(act_event_ctrlProblem != NULL)
	{
		OSAL_delete_event(act_event_ctrlProblem);
		act_event_ctrlProblem = NULL;
	}

	if(act_event_internalProblem != NULL)
	{
		OSAL_delete_event(act_event_internalProblem);
		act_event_internalProblem = NULL;
	}

	if(act_event_resetForProduction != NULL)
	{
		OSAL_delete_event(act_event_resetForProduction);
		act_event_resetForProduction = NULL;
	}

	if(act_event_deviceProblem != NULL)
	{
		OSAL_delete_event(act_event_deviceProblem);
		act_event_deviceProblem = NULL;
	}

	if(act_event_fullRestart != NULL)
	{
		OSAL_delete_event(act_event_fullRestart);
		act_event_fullRestart = NULL;
		// We must stop in this order !!! 
		// First to stop waiting for replies from the driver to allow the dispatcher to stop,
		// then stop waiting for the dispatcher replies to allow the messenger to stop
		// and finally stop the messenger. 
	}

	if(act_event_kdapiAdapterRestart != NULL)
	{
		OSAL_delete_event(act_event_kdapiAdapterRestart);
		act_event_kdapiAdapterRestart = NULL;
	}

	if(act_event_resetDevice != NULL)
	{
		OSAL_delete_event(act_event_resetDevice);
		act_event_resetDevice = NULL;
	}
	
	if(act_event_driverDownEvent != NULL)
	{
		OSAL_delete_event(act_event_driverDownEvent);
		act_event_driverDownEvent = NULL;
	}

	if(act_event_driverUpEvent != NULL)
	{
		OSAL_delete_event(act_event_driverUpEvent);
		act_event_driverUpEvent = NULL;
	}
}

BOOL Act_InitializeInternalResources()
{
	OSAL_create_event(&act_event_resetDevice , FALSE, FALSE, NULL);
	OSAL_create_event(&act_event_kdapiAdapterRestart, FALSE, FALSE, NULL);
	OSAL_create_event(&act_event_fullRestart, TRUE, TRUE, NULL);
	OSAL_create_event(&act_event_updateAgentsEvent, TRUE, FALSE, NULL);
	OSAL_create_event( &act_event_driverUp, FALSE, FALSE, NULL );
	OSAL_create_event( &act_event_ctrlProblem, TRUE, FALSE, NULL );
	OSAL_create_event( &act_event_internalProblem , FALSE, FALSE, NULL );
	OSAL_create_event( &act_event_resetForProduction , FALSE, FALSE, NULL );
	OSAL_create_event( &act_event_stopDriverUpThread , FALSE, FALSE, NULL );
	OSAL_create_event( &act_event_deviceProblem , FALSE, FALSE, NULL );	
	OSAL_create_event( &act_event_driverUpEvent , FALSE, FALSE, NULL );
	OSAL_create_event( &act_event_driverDownEvent , FALSE, FALSE, NULL );
	if( (act_event_resetDevice == NULL) || 
		(act_event_kdapiAdapterRestart == NULL) || 
		(act_event_fullRestart == NULL) || 
		(act_event_updateAgentsEvent == NULL) || 
		(act_event_driverUp == NULL) || 
		(act_event_ctrlProblem == NULL) || 
		(act_event_internalProblem == NULL) || 
		(act_event_resetForProduction == NULL) || 
		(act_event_deviceProblem == NULL) || 		
		(act_event_driverDownEvent == NULL) || 
		(act_event_driverUpEvent == NULL) || 
		(act_event_stopDriverUpThread == NULL) )
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "OSAL_create_event failed");
		return FALSE;
	}

	return TRUE;
}


void Act_DriverDeviceStatus(DRIVER_STATUS driverStatus)
{
/*	if (isDriverConnected == driverStatus)
	{
		return;
	}

	isDriverConnected = driverStatus;	
	UpdateDriverStateToAgents();*/

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Got driverStatus as %d", driverStatus);
	if (driverStatus == DRIVER_UP)
	{
		OSAL_atomic_compareExchange((LPLONG)&isDriverConnected, DRIVER_UP, DRIVER_DOWN);
		OSAL_reset_event(act_event_driverDownEvent);
		OSAL_set_event(act_event_driverUpEvent);
	}
	else
	{
		OSAL_atomic_compareExchange((LPLONG)&isDriverConnected, DRIVER_DOWN, DRIVER_UP);
		OSAL_reset_event(act_event_driverUpEvent);
		OSAL_set_event(act_event_driverDownEvent);
	}
}
BOOL UpdateDriverStateToAgents()
{	
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "UpdateDriverStateToAgents(IN)");

	switch(OSAL_atomic_compareExchange((LPLONG)&isDriverConnected, DRIVER_UP, DRIVER_UP))
	{
	case DRIVER_DOWN:		
		// start the socket dispatcher (allowing the applications to connect)
		l5_sockets_dispatcher_Stop();	
		isL5DispatcherOpen = FALSE;
		if (L5_EVENT_DRIVER_DISCONNECTED != lastReportedIsDriverConnected)
		{
			L5_DISPATCHER_BroadcastEvent(NULL, L5_EVENT_DRIVER_DISCONNECTED);		
			lastReportedIsDriverConnected = L5_EVENT_DRIVER_DISCONNECTED;
		}
		TRACE(TR_MOD_ACT, TR_SEV_ALL, "Act_DriverDeviceStatus - DRIVER_DOWN");
		APPSRV_PRINT( "Act_DriverDeviceStatus - DRIVER_DOWN\n");	
		break;

	case DRIVER_UP:
		if (WMX_ST_OK != L4Proxy_Restart())
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_DriverDeviceStatus - L4Proxy_Restart FAILED");
			return FALSE;
		}		
		OSAL_set_event(act_event_updateAgentsEvent);		
		if (L5_EVENT_DRIVER_CONNECTED != lastReportedIsDriverConnected)
		{
			L5_DISPATCHER_BroadcastEvent(NULL, L5_EVENT_DRIVER_CONNECTED);		
			lastReportedIsDriverConnected = L5_EVENT_DRIVER_CONNECTED;
		}
		TRACE(TR_MOD_ACT, TR_SEV_ALL, "Act_DriverDeviceStatus - DRIVER_UP");
		APPSRV_PRINT( "Act_DriverDeviceStatus - DRIVER_UP\n");		
		break;
	}

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "UpdateDriverStateToAgents(OUT) - Success");
	return TRUE;
}

void Act_HandlingThreadFunc( LPVOID lpParameter )
{
	OSAL_event_t events[8];
	UINT32 waitRes;
	E_SystemState systemState = E_SYSTEM_STATE_UNINITIALIZED;
	static int failCount = 0;

	UNREFERENCED_PARAMETER(lpParameter);

	events[0] = act_event_stopDriverUpThread;
	events[1] = act_event_fullRestart;
	events[2] = act_event_kdapiAdapterRestart;
	events[3] = act_event_driverDownEvent;
	events[4] = act_event_driverUpEvent;
	events[5] = act_event_resetForProduction;
	events[6] = act_event_resetDevice;
	events[7] = act_event_updateAgentsEvent;

	TRACE(TR_MOD_ACT, TR_SEV_ALL, "Act_HandlingThreadFunc STARTED!!");
	while ((waitRes = OSAL_multiple_wait_event(8, events, FALSE, INFINITE)) != WAIT_OBJECT_0)
	{
		OSAL_lock_mutex(act_mutex_ctrl);

		switch(waitRes)
		{
		case WAIT_OBJECT_0 + 7:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_updateAgentsEvent event");
			break;

		case WAIT_OBJECT_0 + 6:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_resetDevice event");
			KDAPI_ADAPTER_ResetDevice();
			break;

		case WAIT_OBJECT_0 + 5:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_resetForProduction event");
			operationMode = ModeOfOperationProduction;
			Act_FullRestart();
			break;

		case WAIT_OBJECT_0 + 4:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_driverUpEvent event");
			UpdateDriverStateToAgents();
			break;

		case WAIT_OBJECT_0 + 3:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_driverDownEvent event");
			UpdateDriverStateToAgents();
			break;

		case WAIT_OBJECT_0 + 2:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_kdapiAdapterRestart event");
			KDAPI_ADAPTER_RestartDriverConnection();
			break;

		case WAIT_OBJECT_0 + 1:
			TRACE(TR_MOD_ACT, TR_SEV_ALL, "Got act_event_fullRestart event");
			Act_FullRestart();
			break;		
		}
		
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "isDriverConnected=%d", OSAL_atomic_compareExchange((LPLONG)&isDriverConnected, DRIVER_UP, DRIVER_UP));
		if (OSAL_atomic_compareExchange((LPLONG)&isDriverConnected, DRIVER_UP, DRIVER_UP) && isRemote==FALSE && isActStarted)
		{
		
			TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Querying system state");
			if (Act_GetSystemState(&systemState))
			{
				TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "systemState=%d , isL5DispatcherOpen=%d", systemState, isL5DispatcherOpen);
				failCount = 0;
				if (E_SYSTEM_STATE_CONFIG == systemState)
				{
					TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "Arrived: CONFIG_STATE");

					if (pfn_DnDAgent_EventHandler != NULL)
					{
						pfn_DnDAgent_EventHandler(NULL, L5_EVENT_DRIVER_CONNECTED, NULL, NULL);
					}
					else
					{
						TRACE(TR_MOD_ACT, TR_SEV_ERR, "DnDAgent_EventHandler is not loaded");
					}
					Act_ConfigInitSequence();
					OSAL_set_event(act_event_driverUpEvent);
				}
				else if(systemState == E_SYSTEM_STATE_INIT)
				{
					TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "Arrived: INIT_STATE");
					Act_SetOperationMode();
					OSAL_set_event(act_event_driverUpEvent);
				}
				else if (E_SYSTEM_STATE_PRODUCTION == systemState)
				{
					TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "Arrived: PRODUCTION_STATE");
					if (!l5_sockets_dispatcher_Start())
					{
						TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_DriverDeviceStatus - l5_sockets_dispatcher_Start FAILED");
					}
					else
					{
						isL5DispatcherOpen = TRUE;
						OSAL_reset_event(act_event_updateAgentsEvent);
					}
				}

				if (!isL5DispatcherOpen && 
					((E_SYSTEM_STATE_READY == systemState) ||
					(E_SYSTEM_STATE_SCAN == systemState) ||
					(E_SYSTEM_STATE_DATA_PATH_CONNECTED == systemState) ||
					(E_SYSTEM_STATE_IDLE == systemState) ||
					(E_SYSTEM_STATE_RF_OFF == systemState))
					)
				{
					// start the socket dispatcher (allowing the applications to connect)
					if (!l5_sockets_dispatcher_Start())
					{
						TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_DriverDeviceStatus - l5_sockets_dispatcher_Start FAILED");
					}
					else
					{
						isL5DispatcherOpen = TRUE;
						OSAL_reset_event(act_event_updateAgentsEvent);
					}
				}
				else if (isL5DispatcherOpen)
				{
					OSAL_reset_event(act_event_updateAgentsEvent);
				}

			}
		}
		else if (isRemote == TRUE)
		{
			if (!l5_sockets_dispatcher_Start())
			{
				TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_DriverDeviceStatus - l5_sockets_dispatcher_Start FAILED");
			}
			else
			{
				isL5DispatcherOpen = TRUE;
				OSAL_reset_event(act_event_updateAgentsEvent);
			}
			OSAL_reset_event(act_event_updateAgentsEvent);
		}

		OSAL_unlock_mutex(act_mutex_ctrl);
		OSAL_sleep(500);
	}
	
	TRACE(TR_MOD_ACT, TR_SEV_ALL, "Exiting Act_HandlingThreadFunc");
	return ;
}

void Act_StartKDapiAdapter()
{
	KDAPI_ADAPTER_RESULT res;

	TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "Entering ");
	res = KDAPI_ADAPTER_Init(useTraces);
	if (res != KDAPI_ADAPTER_SUCCESS)
	{
		return;
	}

	TRACE(TR_MOD_ACT, TR_SEV_DEBUG, "About to invoke KDAPI_ADAPTER_Connect ");
	res = KDAPI_ADAPTER_Connect();

	if (res != KDAPI_ADAPTER_SUCCESS)
	{
		TRACE(TR_MOD_ACT, TR_SEV_WARNING, "Driver is not connected !!! still openning the status thread in order to connect.");
	}

	res = KDAPI_ADAPTER_Start();
	if (res != KDAPI_ADAPTER_SUCCESS)
	{
		return;
	}

	isDriverInitialized = 1;
}

void Act_StopKDapiAdapter()
{
	if (0 ==OSAL_atomic_compareExchange(&isDriverInitialized, 0, 1))
		return;

	KDAPI_ADAPTER_Stop();
	KDAPI_ADAPTER_Disconnect();	
	KDAPI_ADAPTER_Fini();
}

BOOL Act_Start()
{
	UINT32 valAnswer;
	BOOL res;
	BOOL bEnableInstrumentation = FALSE;

	//Initialize internal agents: Messenger, L5dispatcher, L5SocketDispatcher & L4MsgProxy
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Initialize internal agents: Messenger, L5dispatcher, L5SocketDispatcher & L4MsgProxy");
	if (!Act_InitPipe())
	{
		TRACE(TR_MOD_ACT, TR_SEV_CRITICAL, "Act_Start (OUT) - Act_InitPipe failed");
		return FALSE;
	}

	agentsInitialized = INTERNAL_AGENTS_INITIALIZED;

	res = L4Configurations_getGetDeviceTraces(&valAnswer);
	if (0 != valAnswer) 
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "starting DnD");		
		useTraces = TRUE;
	}

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Starting KDAPI_ADAPTER");
	Act_StartKDapiAdapter();	

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Connecting to L5 Connector");
	if (L5_RESULT_OK != g_act_pFuncs->pfnConnectEx( L5_TARGET_ACT, &Act_MessagesHandler, NULL, NULL, THREAD_ID_DEFAULT, &g_act_Connection ))		
	{		
		TRACE(TR_MOD_ACT, TR_SEV_ALL, "Act_Initialize (OUT) - pfnConnectEx failed");
		return FALSE;
	}

	L4Configurations_getEnableInstrumentation((UINT32*)&bEnableInstrumentation);
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Instrumentation enable is set to %d", bEnableInstrumentation);

	if ( bEnableInstrumentation ) 
	{
		if (INIT_SUCCESS != LoadInstrumentationModule())
		{
			return FALSE;
		}
	}
	
	//Initialize agents:
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Initializing Agents:");
	if ( bEnableInstrumentation )
	{
		if ( !pfn_MOCMsgProxy_Initialize(g_act_pFuncs, g_act_Utils))
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "MocMsgProxy_Initialize FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "MocMsgProxy_Initialize succeeded");
		agentsInitialized |= MOCMSGPROXY_INITIALIZED;
	}

	if ( bEnableInstrumentation && useTraces)
	{
		if (INIT_FAIL == pfn_DnDAgent_Initialize(g_act_pFuncs, g_act_Utils))
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "DnDAgent_Initialize FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "DnDAgent_Initialize succeeded");
		agentsInitialized |= DNDA_GENT_INITIALIZED;
	}

	if (isRemote == FALSE)
	{
		if (INIT_SUCCESS != SupplicantAgent_Initialize(g_act_pFuncs, g_act_Utils))
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "SupplicantAgent_Initialize FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "SupplicantAgent_Initialize succeeded");
		agentsInitialized |= SUPPLICANT_AGENT_INITIALIZED;

		if (INIT_SUCCESS != NDnSAgent_Initialize(g_act_pFuncs, g_act_Utils))
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "NDnSAgent_Initialize FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "NDnSAgent_Initialize succeeded");
		agentsInitialized |= NDNS_AGENT_INITIALIZED;

	}	
	else
	{
		printf("Working in remote mode\n");
	}

	//start agents:
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Starting Agetns:");
	if ( agentsInitialized & MOCMSGPROXY_INITIALIZED )
	{ 
		if ( !pfn_MOCMsgProxy_Start() )
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "MocMsgProxy_Start FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "MocMsgProxy_Start succeeded");
		agentsStarted |= MOCMSGPROXY_STARTED;

	}

	if ( (agentsInitialized & DNDA_GENT_INITIALIZED) && useTraces)
	{
		if (!pfn_DnDAgent_Start())
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "DnDAgent_Start FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "DnDAgent_Start succeeded");
		agentsStarted |= DNDA_GENT_STARTED;
	}

	if (isRemote == FALSE)
	{
		if (!SupplicantAgent_Start())
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "SupplicantAgent_Start FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "SupplicantAgent_Start succeeded");
		agentsStarted |= SUPPLICANT_AGENT_STARTED;

		if (!NDnSAgent_Start())
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "NDnSAgent_Start FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "NDnSAgent_Start succeeded");
		agentsStarted |= NDNS_AGENT_STARTED;
	}

	//register for system state changes indication
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Act_RegisterSystemStateCB");
	Act_RegisterSystemStateCB();

	return TRUE;

Finalize:
	TRACE(TR_MOD_ACT, TR_SEV_ALL, "Act_Start (OUT) - Initialization FAILED");
	if (isDriverInitialized)
	{
		Act_StopKDapiAdapter();
	}

	Act_Stop();
	return FALSE;
}
BOOL Act_Initialize()
{
	char answer[100];
	BOOL res;
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_Initialize (IN)");

	OSAL_create_mutex(&act_mutex_ctrl, FALSE, NULL);
	OSAL_lock_mutex(act_mutex_ctrl);
	//Get AppSrv configuration:Driver or dSim or Remote , Sockets or Named pipe
	L4Configurations_init();

	//Initialize internal resources:
	if (!Act_InitializeInternalResources())
	{
		TRACE(TR_MOD_ACT, TR_SEV_CRITICAL, "Act_Initialize (OUT) - Act_InitializeInternalResources failed");
		OSAL_unlock_mutex(act_mutex_ctrl);
		return FALSE;
	}

	//Get L5 connection functions:
	g_act_pFuncs = L5_DISPATCHER_GetServiceDispatcherFunctions();
	if (g_act_pFuncs == NULL)
	{
		TRACE(TR_MOD_ACT, TR_SEV_CRITICAL, "Act_Initialize (OUT) - L5_DISPATCHER_GetServiceDispatcherFunctions failed");
		OSAL_unlock_mutex(act_mutex_ctrl);
		return FALSE;
	}

	//Initialize the utility functions:
	g_act_Utils = GetUtilsFuncs();
	if (g_act_Utils == NULL)
	{
		TRACE(TR_MOD_ACT, TR_SEV_CRITICAL, "Act_Initialize (OUT) - GetUtilsFuncs failed");
		OSAL_unlock_mutex(act_mutex_ctrl);
		return FALSE;
	}
	res = L4Configurations_getDriverMode(answer);	
	if ((res != 0)&&(0 == OSAL_stricmp("remote", answer))) 
	{
		isRemote = TRUE;
	}

	//start listening thread for error events & driver connection events:
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Starting Act_HandlingThreadFunc");
	OSAL_create_thread(Act_HandlingThreadFunc, NULL, &act_thread_messagesHandler);
	if( act_thread_messagesHandler == NULL )
	{
		TRACE(TR_MOD_ACT, TR_SEV_CRITICAL, "Act_Initialize (OUT) - Act_HandlingThreadFunc failed");
		OSAL_unlock_mutex(act_mutex_ctrl);
		return FALSE;
	}
		
	OSAL_unlock_mutex(act_mutex_ctrl);

	APPSRV_PRINT( "AppSrv is ready !\n" );
	OSAL_EventLogger_Log((UINT16)EVENTLOG_INFORMATION_TYPE, "AppSrv is ready");	

	TRACE(TR_MOD_ACT, TR_SEV_ALL, "AppSrv is ready");
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_Initialize (OUT)");

	agentsInitialized = 0;
	agentsInitialized = 0;

	return TRUE;
}
BOOL Act_Stop()
{
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_Stop(IN)");

	l5_sockets_dispatcher_Stop();

	//stop agents:
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Stopping Agetns:");
	if ((agentsStarted&NDNS_AGENT_STARTED) && !NDnSAgent_Stop())
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "NDnSAgent_Stop FAILED");
		goto Finalize;
	}
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "NDnSAgent_Stop succeeded");
	agentsStarted &= ~NDNS_AGENT_STARTED;

	if ((agentsStarted&SUPPLICANT_AGENT_STARTED) && !SupplicantAgent_Stop())
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "SupplicantAgent_Stop FAILED");
		goto Finalize;
	}
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "SupplicantAgent_Stop succeeded");
	agentsStarted &= ~SUPPLICANT_AGENT_STARTED;
	
	if (useTraces)
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "Before DnDAgent_Stop ");
		if ((agentsStarted&DNDA_GENT_STARTED) && !pfn_DnDAgent_Stop())
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "DnDAgent_Stop FAILED");
			goto Finalize;
		}
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "DnDAgent_Stop succeeded");
		agentsStarted &= ~DNDA_GENT_STARTED;
	}

	if ((agentsStarted&MOCMSGPROXY_STARTED) && !pfn_MOCMsgProxy_Stop())
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "MocMsgProxy_Stop FAILED");
		goto Finalize;
	}
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "MocMsgProxy_Stop succeeded");
	agentsStarted &= ~MOCMSGPROXY_STARTED;
	
	Messenger_Stop();

	//Finalize agents:
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Finalizing Agetns:");
	if (agentsInitialized&NDNS_AGENT_INITIALIZED)
	{
		NDnSAgent_Finalize();
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "NDnSAgent_Finalize succeeded");
		agentsInitialized &= ~NDNS_AGENT_INITIALIZED;
	}

	if (agentsInitialized&SUPPLICANT_AGENT_INITIALIZED)
	{
		SupplicantAgent_Finalize();
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "SupplicantAgent_Finalize succeeded");
		agentsInitialized &= ~SUPPLICANT_AGENT_INITIALIZED;
	}

	if (useTraces)
	{
		if (agentsInitialized&DNDA_GENT_INITIALIZED)
		{
			pfn_DnDAgent_Finalize();
			TRACE(TR_MOD_ACT, TR_SEV_INFO, "DnDAgent_Finalize succeeded");
			agentsInitialized &= ~DNDA_GENT_INITIALIZED;
		}
	}

	if (agentsInitialized&MOCMSGPROXY_INITIALIZED)
	{
		pfn_MOCMsgProxy_Finalize();
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "MocMsgProxy_Finalize succeeded");
		agentsInitialized &= ~MOCMSGPROXY_INITIALIZED;
	}


	UnloadInstrumentationModule();
	//internal finalizations:
	Act_StopKDapiAdapter();
	TRACE(TR_MOD_ACT, TR_SEV_INFO, "After Act_StopKDapiAdapter");

	if (agentsInitialized&INTERNAL_AGENTS_INITIALIZED)
	{
		Act_FiniPipe();
		agentsInitialized &= ~INTERNAL_AGENTS_INITIALIZED;
	}

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_Stop(OUT) - Succeeded");
	return TRUE;

Finalize:
	TRACE(TR_MOD_ACT, TR_SEV_ALL, "Act_Stop (OUT) - FAILED");
	if (isDriverInitialized)
	{
		Act_StopKDapiAdapter();
	}

	return FALSE;
}
BOOL Act_Finalize()
{	
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_Finalize (IN)");
	//capture act_mutex_ctrl to gaurd against getting events during finalize
	OSAL_lock_mutex(act_mutex_ctrl);
	
	Act_Stop();
	Act_FreeInternalResources();

	OSAL_unlock_mutex(act_mutex_ctrl);

	OSAL_delete_mutex(act_mutex_ctrl);
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_Finalize (OUT)");
	return TRUE;
}

void Act_RestartDriver()
{	
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_RestartDriver(IN)");
	APPSRV_PRINT( "Act_RestartDriver!\n" );

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Act_RestartDriver - closing KDAPI_ADAPTER");
	Act_StopKDapiAdapter();

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Act_RestartDriver - reopen KDAPI_ADAPTER");
	Act_StartKDapiAdapter();

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_RestartDriver(OUT)");
}

void Act_FullRestart()
{
	APPSRV_PRINT( "Act_FullRestart!\n" );
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_FullRestart(IN)");

	if (isActStarted)
	{
		if (!Act_Stop()) //TODO: Check what happens if Act_Stop fails in the middle (some agent have stopped and some not).
		{
			TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_FullRestart - Stopping AppSrv FAILED!!");
			return;
		}
	}

	isActStarted = FALSE;

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Act_FullRestart - Starting AppSrv");
	if (!Act_Start())
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Act_FullRestart - Starting AppSrv FAILED!!");
		return;
	}

	isActStarted = TRUE;
	OSAL_reset_event(act_event_fullRestart);

	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "Act_FullRestart(OUT)");
}
