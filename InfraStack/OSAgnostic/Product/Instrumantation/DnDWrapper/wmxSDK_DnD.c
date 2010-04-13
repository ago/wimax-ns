/**************************************************************************
 Copyright (c) 2007-2008, Intel Corporation. All rights reserved.

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
//#pragma warning(disable : 4996)
#include <Windows.h>
#include <string.h>
#include <io.h>

#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"

#include "wmxSDK_DnD.h"
#include "wmxSDK_DnD_If.h"
#include "wmxSDK_DnD_Internal.h"
#include "wmxSDK_DnD_Common.h"
#include "WrappersUtils.h"
#include "CommonServices.h"
#include "Versions.h"
#include "MonitorGeneral.h"
//#include "L5Common.h"
#include "L5Opcodes.h"
#include "L4ConfigurationManager.h"
#include "Services_Ctrl.h"
#include "PipeHandler.h"
#include "PipeHandler_Ctrl.h"
#include "TraceModule.h"

#include "L3L4CommonDefines.h"
#include "L4BufMan_L3L4Structs.h"

#include "TraceMessage.h"
#include "TraceMessageDillo.h"
#include "TraceSubsystem.h"


//typedefs
typedef enum _StateValue
{
	STATE_NOT_INITIALIZED				= 0x0000,
	STATE_TRACE_INITIALIZED				= 0x0001,
	STATE_PREFIX_NAME_ALLOCATED			= 0x0002,
	STATE_SERVICES_INITIALIZED			= 0x0004,
	STATE_PIPE_HANDLER_INITIALIZED		= 0x0008,
	STATE_APP_SRV_IP_ADD_ALLOCATED		= 0x0010,
	STATE_EVENT_CREATED					= 0x0020,
	STATE_KILL_THREAD_EVENT_CREATED		= 0x0040,
	STATE_THREAD_KILLED_EVENT_CREATED	= 0x0080,
	STATE_THREAD_CREATED				= 0x0100,
	STATE_REGISTERED_FOR_EVENTS			= 0x0200,
	STATE_HANDLER_CONNECTED				= 0x0400,
	STATE_TRACE_TABLE_LOADED			= 0x0800,
	STATE_SYSTEM_STATE_REGISTERED		= 0x1000,
	STATE_CONFIG_STATE_EVENT			= 0x2000,
	STATE_ALL							= 0xFFFF
} StateValue;


//Statics
#define DEFAULT_TRACE_PREFIX		L"Trace"
#define DEFAULT_MONITOR_PREFIX		L"Monitor"

#define MAX_NUM_OF_ATTEMPTS_TO_GET_MESSAGE 10

#define NUM_OF_EVENTS 3
static HANDLE eventsHandleArr[NUM_OF_EVENTS];
static HANDLE sThreadKilled;
static HANDLE sThreadHandle;

static BOOL sUseTrace = FALSE;
static BOOL sUseMonitor = FALSE;

static wmx_Version_t sDnDWrapperVersion;
static LONG sInitRefCnt = 0;
static WCHAR sWrapperName[WRAPPER_NAME_LEN];
static L5_CONNECTION sL5Conn;
static tL5DispatcherFunctions * sL5DispatcherFuncs;
static L5_RESULT sL5Result;
static wmx_Status_t sStatus;

static BOOL sIsOnlineMode = FALSE;
static BOOL sIsInitialized = FALSE;

static WCHAR sFullFilesPath[MAX_PATH_LEN];


static BOOL sIsFirstFileInDir = TRUE;

/* Trace File Variables */
static WCHAR *	sTraceFilesPrefixName	= NULL;
static UINT32	sNextTraceFileIndex		= 0;
static FILE *	sCurTraceFilePtr		= NULL;

/* Trace File Variables */
static WCHAR *	sMonitorFilesPrefixName	= NULL;
static UINT32	sNextMonitorFileIndex	= 0;
static FILE *	sCurMonitorFilePtr		= NULL;

//static UINT16	sLastSeqNumber			= 0;
//static UINT16	sLastTraceSeqNumber		= 0;
//static UINT16	sLastMonitorSeqNumber	= 0;
//#define NormalizeSeqNumber(seqNumber)(sLastSeqNumber + ((UINT16)(seqNumber)))

static const wchar_t * cWrapperName = L"DnDWrapper";

static wmx_CtrlStatus_t sCurrConnectionStatus;

static BOOL sIsEnabled = FALSE;
static BOOL sIsConnectedToHandler = FALSE;
static BOOL sIsPathSet = FALSE;

static char * sCurMonitorFilter = NULL;
static UINT32 sCurMonitorFilterSize = 0;
static BOOL	  sIsMonitorFilterSet = FALSE;
static char * sCurTraceFilter = NULL;
static UINT32 sCurTraceFilterSize = 0;
static BOOL	  sIsTraceSevSet = FALSE;
static WCHAR sCurPathSet[MAX_PATH_LEN];
static char * sAppSrvIpAdd = NULL;

static LPCTSTR	KEY_ENTRY_MAX_NUM_OF_FILES  = TEXT("MaxNumOfFiles");
static UINT32 sMaxNumOfFilesInDir = FILE_NAME_MAX_NUMBER;
static UINT32 sNumberOfTimesSearchedForNextMessage = 0;

static StateValue sCurState = STATE_NOT_INITIALIZED;

static HStringTable sCurStringTable;

static char * sCurLocationInTracBufferPtr = NULL;
static char * sEndL4BufferPtr = NULL;

static BOOL sIsRemoteMode = FALSE;

static BOOL sIsMonitorOnSet = FALSE;

static LONG g_numOfStateReportRegs = 0;

OSAL_critical_section fileIndexCs;
OSAL_critical_section configurationsCs;

static WCHAR * sDsimDefault = L"C:\\temp\\dSim_Default\\";

//CB for the L4 Indications
void wmxDnD_MessagesHandler(L5_CONNECTION Conn,
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
	wmx_Status_t st;
	ReportState_type stateReport;

	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(cbResponseBufferSize);
	UNREFERENCED_PARAMETER(pdwResponseMessageID);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvResponseBuffer);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbSentBufferSize);

	switch (dwSentMessageID)
	{

	case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
		switch ( L4BM_GetOpcode((UINT8*)pvSentBuffer) )
		{
		case L3_L4_OPCODE_REPORT_STATE:
			TRACE_INFO(L"wmxDnD_MessagesHandler::Got L3_L4_OPCODE_REPORT_STATE");

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
				if (E_SYSTEM_STATE_CONFIG == stateReport.SystemState.value)
				{
					if (0 != OSAL_set_event(eventsHandleArr[2]))
					{
						TRACE_ERR("Fail to set event on Config State received");
					}
				}
			}
			break;
		}
	}
}
void wmxDnD_eventHandlerCB(L5_CONNECTION Conn, L5_EVENT eEvent, void* pvEventData, void* pvUserContext)
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(eEvent);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);
	TRACE_INFO(L"Event occured. Event type = %d\nEvent data = %s", eEvent, pvEventData);
}


void UpdateNextFileIndex(UINT32* index)
{
	//If we get to the max file number then we start over
	*index = (*index + 1) % sMaxNumOfFilesInDir;
}

//comment
void EventsCB(wmx_CtrlStatus_t connStatus)
{
	sCurrConnectionStatus = connStatus;
	if (0 != OSAL_set_event(eventsHandleArr[1]))
	//if (FALSE == SetEvent(sEventHandle))
	{
		TRACE_ERR("Fail to set event on CB function");
	}

}

void HandleConnectionStatusChanged()
{
	//WCHAR filePathToSet[MAX_PATH_LEN];

	if (NOT_READY == sCurrConnectionStatus )
	{
		if (sIsConnectedToHandler)
		{
			PIPE_HANDLER_Disconnect(sL5Conn);
			sIsConnectedToHandler = FALSE;
			sCurState &= (STATE_ALL - STATE_HANDLER_CONNECTED);
		}
		else
		{
			//OSAL_sleep(2000);
			return;
		}
	}
	else //READY == connStatus
	{
		//Keep Alive on the Pipe Handler
		if (sIsConnectedToHandler)
		{
			PIPE_HANDLER_Disconnect(sL5Conn);
			sIsConnectedToHandler = FALSE;
			sCurState &= (STATE_ALL - STATE_HANDLER_CONNECTED);
		}
		if (FALSE == sIsConnectedToHandler)
		{
			TRACE_INFO(L"Attempting to perform pipe handler connect");
			sL5Result = PIPE_HANDLER_Connect(wmxDnD_MessagesHandler, NULL, &sL5Conn);			
			if (L5_RESULT_OK != sL5Result)
			{
				TRACE_ERR("Failed to reconnect to pipe handler");
				//TODO - See if this is needed
				//return -1;
				return;
			}
			sIsConnectedToHandler = TRUE;
			sCurState |= STATE_HANDLER_CONNECTED;
		}

		if (sL5DispatcherFuncs != NULL)
		{
			//Unregister and then Register on System State Changed Indication
			TRACE_INFO(L"Unregistering on driver state report");
			wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *sL5DispatcherFuncs, sL5Conn );
			sCurState &= (STATE_ALL - STATE_SYSTEM_STATE_REGISTERED);

			TRACE_INFO(L"registering on driver state report");
			sStatus = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *sL5DispatcherFuncs, sL5Conn );
			if ( WMX_ST_OK != sStatus )
			{
				TRACE_ERR("failed to register on driver state report");
				return;
			}
		}
		else
		{
			//Get the Service dispatcher functions
			sL5DispatcherFuncs = PIPE_HANDLER_GetServiceDispatcherFunctions();
			if (NULL == sL5DispatcherFuncs)
			{
				TRACE_ERR("Got NULL pointer for tL5funcsFunctions.");
				return ;
			}
			//Unregister and then Register on System State Changed Indication
			TRACE_INFO(L"Unregistering on driver state report");
			wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *sL5DispatcherFuncs, sL5Conn );
			sCurState &= (STATE_ALL - STATE_SYSTEM_STATE_REGISTERED);


			TRACE_INFO(L"registering on driver state report");
			sStatus = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *sL5DispatcherFuncs, sL5Conn );
			if ( WMX_ST_OK != sStatus )
			{
				TRACE_ERR("failed to register on driver state report");
				return;
			}

		}

		
		sCurState |= STATE_SYSTEM_STATE_REGISTERED;

		//When the Connection is set again - set all previous parameters

		//Enable file writing
		if (sIsEnabled)
		{
			if (READY == PIPE_HANDLER_GetCtrlStatus())
			{
				TRACE_INFO(L"Attempting to perform enable file writing");
				if (WMX_ST_OK != wmxDnD_EnableFileWriting())
				{
					TRACE_ERR("Failed to reset files path in EventsCB");
					return;
				}
			}
		}

		//Set Mon + Trace filters again
		SetPreviousSeveritiesOfDevice();
	}

}

void SetPreviousSeveritiesOfDevice()
{
	//Set Mon + Trace filters again
	if (TRUE == sIsMonitorFilterSet)
	{
		if (READY == PIPE_HANDLER_GetCtrlStatus())
		{
			TRACE_INFO(L"Attempting to perform set monitorFilter");
			if (WMX_ST_OK != wmxDnD_SetMonitorFilter(sCurMonitorFilter, sCurMonitorFilterSize))
			{
				TRACE_ERR("Failed to reset monitor filter in EventsCB");
				return;
			}

		}
	}

	if (TRUE == sIsTraceSevSet)
	{
		if (READY == PIPE_HANDLER_GetCtrlStatus())
		{
			TRACE_INFO(L"Attempting to perform set traceFilter");
			if (WMX_ST_OK != wmxDnD_SetTraceFilter(sCurTraceFilter, sCurTraceFilterSize))
			{
				TRACE_ERR("Failed to reset trace filter in EventsCB");
				return;
			}
		}
	}

	if (sIsMonitorOnSet)
	{
		if (READY == PIPE_HANDLER_GetCtrlStatus())
		{
			TRACE_INFO(L"Attempting to perform MonitorOn");
			if (WMX_ST_OK != wmxDnD_MonitorON())
			{
				TRACE_ERR("Failed to set MonitorOn in EventsCB");
				return;
			}
		}
	}

}

void ConnectionStatusThreadProc(LPVOID plparameter)
{
	BOOL stop = FALSE;

	UNREFERENCED_PARAMETER(plparameter);
	TRACE_INFO("Connection status changed. Current Connection Status = %s", sCurrConnectionStatus == 0 ? L"NOT READY" : L"READY");
	
	for(;!stop;)
	{
		//switch(WaitForSingleObject(sKillThreadEvent, 0))
		switch(OSAL_multiple_wait_event(NUM_OF_EVENTS,eventsHandleArr, FALSE, 500))
		{
			case WAIT_TIMEOUT:				
				break;
			case WAIT_OBJECT_0:
				TRACE_INFO("The Close thread event was signaled - thread closed");
				stop = TRUE;
				break;
			case WAIT_OBJECT_0 + 1:
				TRACE_INFO(L"Change status event received");
				HandleConnectionStatusChanged();
				break;
			case WAIT_OBJECT_0 + 2:
				TRACE_INFO(L"Config state identified");
				SetPreviousSeveritiesOfDevice();
				break;
			default:
				TRACE_ERR("Error occured on WaitForMultipleObjects in thread func");
				stop = TRUE;
				break;
		}
	}

	OSAL_set_event(sThreadKilled);
}



//Internal APIs
BOOL IsInternalTrace(char * line)
{
	UNREFERENCED_PARAMETER(line);
	return FALSE;
}
void FreeAllResources()
{
	if (NULL != sCurMonitorFilter)
	{
		free(sCurMonitorFilter);
		sCurMonitorFilter = NULL;
	}

	if (NULL != sCurTraceFilter)
	{
		free(sCurTraceFilter);
		sCurTraceFilter = NULL;
	}

	//if (NULL != sCurPathSet)
	//	free(sCurPathSet);

	sIsPathSet = FALSE;

	if ((NULL != sCurTraceFilePtr) && (sCurTraceFilePtr != sCurMonitorFilePtr))
	{
		fclose(sCurTraceFilePtr);
		sCurTraceFilePtr = NULL;
	}

	if (NULL != sCurMonitorFilePtr)
	{
		fclose(sCurMonitorFilePtr);
		sCurMonitorFilePtr = NULL;
	}

	sIsFirstFileInDir = TRUE;
	TRACE_INFO(L"FreeAllResources(). sIsFirstFileInDir = TRUE. Zeroing sNextTraceFileIndex");

	sIsEnabled = FALSE;

	sCurLocationInTracBufferPtr = NULL;
	sEndL4BufferPtr = NULL;

	sIsMonitorOnSet = FALSE;

	sIsMonitorFilterSet = FALSE;
	sIsTraceSevSet = FALSE;

	sMaxNumOfFilesInDir = FILE_NAME_MAX_NUMBER;
	OSAL_delete_critical_section(&fileIndexCs);
	OSAL_delete_critical_section(&configurationsCs);
}


wmx_Status_t AssertValidParametersForOffline(const WCHAR * offlineFilesPath)
{
	if (NULL == offlineFilesPath)
	{
		TRACE_ERR("Init failed. User must supply directory for Offline mode");
		return WMX_ST_FAIL;
	}

	//TODO: Change to a different function
	if (ACCESS_FAIL_VALUE == _waccess(offlineFilesPath, READ_PERMISSION_VAL))
	{
		//Directory offlineFilesPath not found or doesn't have Read Permissions	
		TRACE_ERR("Init failed. The directory given for Offline mode doesn't exist and/or doesn't have read permissions");
		return WMX_ST_FAIL;
	}

	//Save the full path to files.
	wcscpy_s(sFullFilesPath, MAX_PATH_LEN, offlineFilesPath);
	return WMX_ST_OK;
}
wmx_Status_t InternalVersionValidate()
{
	wmx_Version_t pipeHandlerVersion;
	wmx_Version_t expectedPipeHandlerVersion;
	VERSION_RESULT versionResult;

	//Perform version validation of the PipeHandler
	if (IsVersionValidationEnabled())
	{			
		//Get the pipe handler version
		pipeHandlerVersion = PIPE_HANDLER_GetVersion();

		// set expected versions of modules in use
		SET_VERSION(	expectedPipeHandlerVersion, 
			PIPE_HANDLER_MAJOR, 
			PIPE_HANDLER_MINOR, 
			PIPE_HANDLER_BUILD, 
			PIPE_HANDLER_REVISION, 
			PIPE_HANDLER_BRANCH );
		versionResult =  ValidateVersion("PipeHandler", pipeHandlerVersion, expectedPipeHandlerVersion);
		if (versionResult != VER_SUCCESS && versionResult != VER_SUCCESS_INVALID_MINOR)
		{
			TRACE_ERR("PipeHandler version validation failed.");
			//wmxDnD_Finalize();
			return WMX_ST_VERSION_VALIDATION_ERROR;
		}
	}

	return WMX_ST_OK;
}


wmx_Status_t InternalChangeAppSrvAdd(const char * appSrvIpAdd)
{
	sAppSrvIpAdd = (char *) malloc (strlen(appSrvIpAdd) + 1);
	if (NULL == sAppSrvIpAdd)
	{
		TRACE_ERR("Failed to allocate memory for IP address");
		wmxDnD_Finalize();
		return WMX_ST_FAIL;
	}
	//sCurState++;
	sCurState |= STATE_APP_SRV_IP_ADD_ALLOCATED;

	//TODO: Check what happenes if port is 0
	if (FALSE == PIPE_HANDLER_SetConnParams((char *)appSrvIpAdd, GetPortNum()))
	{
		TRACE_ERR("Failed to set conn params to Pipe Handler.");
		//wmxDnD_Finalize();
		return WMX_ST_FAIL;
	}

	return WMX_ST_OK;
}

wmx_Status_t InternalOnlineInit(const char * appSrvIpAdd)
{
	sStatus = InternalVersionValidate();
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Version validation failed.");
		return sStatus;				
	}

	//Set the IP Address of the AppSrv, if specified
	if ( (NULL != appSrvIpAdd) && (strcmp(appSrvIpAdd, "127.0.0.1")) )
	{
		sStatus = InternalChangeAppSrvAdd(appSrvIpAdd);
		if (WMX_ST_OK != sStatus)
		{
			TRACE_ERR("Failed to change AppSrv ip address.");
			return sStatus;
		}
	}

	//Get the Service dispatcher functions
	sL5DispatcherFuncs = PIPE_HANDLER_GetServiceDispatcherFunctions();
	if (NULL == sL5DispatcherFuncs)
	{
		TRACE_ERR("Got NULL pointer for tL5funcsFunctions.");
		return WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED;
	}

	//Create the event for connection status
	OSAL_create_event(&eventsHandleArr[1] , FALSE, FALSE, NULL);
	if (NULL == eventsHandleArr[1])
	{
		TRACE_ERR("Failed to Create Event.");
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_EVENT_CREATED;

	//Create the event for killing the thread
	OSAL_create_event(&eventsHandleArr[0] , FALSE, FALSE, NULL);
	if (NULL == eventsHandleArr[0])
	{
		TRACE_ERR("Failed to Create Event.");
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_KILL_THREAD_EVENT_CREATED;

	OSAL_create_event(&eventsHandleArr[2] , FALSE, FALSE, NULL);
	if (NULL == eventsHandleArr[2])
	{
		TRACE_ERR("Failed to Create Event.");
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_CONFIG_STATE_EVENT;
	
	OSAL_create_event(&sThreadKilled , FALSE, FALSE, NULL);
	if (NULL == sThreadKilled)
	{
		TRACE_ERR("Failed to Create Event.");
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_THREAD_KILLED_EVENT_CREATED;


	//Create the thread for connection status
	OSAL_create_thread(ConnectionStatusThreadProc, NULL, &sThreadHandle );
	if (NULL == sThreadHandle)
	{
		TRACE_ERR("Failed to Create Thread.");
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_THREAD_CREATED;

	//Register to Connection Status in Pipe Handler
	PIPE_HANDLER_RegisterCtrlStatusUpdatesCB(&EventsCB);
	sCurState |= STATE_REGISTERED_FOR_EVENTS;

	//Connect to PipeHandler
	TRACE_INFO(L"Connecting to Pipe Handler");
	sL5Result = PIPE_HANDLER_Connect(wmxDnD_MessagesHandler, NULL, &sL5Conn);
	if (L5_RESULT_OK != sL5Result)
	{
		TRACE_ERR("Pipe Handler Connection - Failed. Return value = %d", sL5Result);
		return wmx_L5ResultToWMXStatus(sL5Result);
	}
	if (NULL == sL5Conn)
	{
		TRACE_ERR("Pipe Handler Connection - Failed. Return value = %d", sL5Result);
		return WMX_ST_FAIL;				
	}
	TRACE_INFO(L"Pipe Handler Connection - Success");
	sIsConnectedToHandler = TRUE;
	sCurState |= STATE_HANDLER_CONNECTED;

	//Register on System State Changed Indication
	TRACE_INFO(L"registering on driver state report");
	sStatus = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *sL5DispatcherFuncs, sL5Conn );
	if ( WMX_ST_OK != sStatus )
	{
		TRACE_ERR("failed to register on driver state report");
		return sStatus;
	}
	sCurState |= STATE_SYSTEM_STATE_REGISTERED;

	//Get the current path.
	sStatus = wmxDnD_GetFullPathToOnlineFiles(sFullFilesPath, MAX_PATH_LEN);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to Get the current files path");
		return sStatus;				
	}

	sCurTraceFilter = malloc( sizeof(char) * TRACE_SEVERITIES_TABLE_SIZE );
	if (NULL == sCurTraceFilter)
	{
		TRACE_ERR("Failed to allocate memory for Trace Filter");
		return WMX_ST_FAIL;
	}
	sCurTraceFilterSize = TRACE_SEVERITIES_TABLE_SIZE;

	sCurMonitorFilter = malloc (sizeof(char) * MONITOR_FILTER_TABLE_SIZE);
	if (NULL == sCurTraceFilter)
	{
		TRACE_ERR("Failed to allocate memory for Monitor Filter");
		return WMX_ST_FAIL;
	}
	sCurMonitorFilterSize = MONITOR_FILTER_TABLE_SIZE;
	
	return WMX_ST_OK;
}

wmx_Status_t InternalCommonInit(BOOL useMonitor, BOOL useTrace, BOOL isOnlineMode, const WCHAR *traceFilesPrefix, const WCHAR *monitorFilesPrefix)
{
	size_t prefixLength = 0;
	char getDriverMode[20];

	if (!PIPE_HANDLER_Init())
	{
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_PIPE_HANDLER_INITIALIZED;

	//Init Trace
	TRACE_INFO("wmxDnD_Init start");
	sCurState |= STATE_TRACE_INITIALIZED;

	//Init Critical Sections
	OSAL_init_critical_section(&fileIndexCs);
	OSAL_init_critical_section(&configurationsCs);

	// init services
	if (!Services_Init())
	{
		TRACE_ERR("Failed to Init Services");
		return WMX_ST_FAIL;
	}
	sCurState |= STATE_SERVICES_INITIALIZED;

	// get the driver mode
	sIsRemoteMode = FALSE;
	if (FALSE == L4Configurations_getDriverMode(getDriverMode)) // could not find the value in the registry
	{
		TRACE_WAR(L"Unable to find DriverModem key in the registry - assuming 'driver'");
	}
	else // key was in registry
	{
		if (0 == OSAL_stricmp("remote", getDriverMode))
		{
			sIsRemoteMode = TRUE;
		}
	}

	//Read the registry key of max number of files in dir
	L4Configurations_getMaxNumOfFiles(&sMaxNumOfFilesInDir);	
	if (sMaxNumOfFilesInDir <= 0 || sMaxNumOfFilesInDir >FILE_NAME_MAX_NUMBER)
	{
		TRACE_WAR(L"Max number of files read in regisrty is %u which is invalid. Setting max number of files to %d", sMaxNumOfFilesInDir, FILE_NAME_MAX_NUMBER);
		sMaxNumOfFilesInDir = FILE_NAME_MAX_NUMBER;
	}

	//Save user's init parameters
	OSAL_enter_critical_section(&configurationsCs);
	sUseMonitor = useMonitor;
	sUseTrace	= useTrace;
	OSAL_exit_critical_section(&configurationsCs);
	sIsOnlineMode = isOnlineMode;

	if (!(sUseMonitor || monitorFilesPrefix))
	{
		monitorFilesPrefix = DEFAULT_MONITOR_PREFIX;
	}
	if (!(sUseTrace || traceFilesPrefix))
	{
		traceFilesPrefix = DEFAULT_TRACE_PREFIX;
	}

	if(!(traceFilesPrefix || monitorFilesPrefix))
	{
		TRACE_ERR("A NULL traceFilesPrefix was specified for Init");
		return WMX_ST_FAIL;
	}
	
	prefixLength = wcslen(traceFilesPrefix) + 1;
	sTraceFilesPrefixName = (WCHAR *) malloc (prefixLength*2); // times two because malloc gets the amount in bytes
	if (NULL == sTraceFilesPrefixName)
	{
		return WMX_ST_FAIL;
	}

	sCurState |= STATE_PREFIX_NAME_ALLOCATED;

	wcscpy_s(sTraceFilesPrefixName, prefixLength, traceFilesPrefix);

	prefixLength = wcslen(monitorFilesPrefix) + 1;
	sMonitorFilesPrefixName = (WCHAR *) malloc (prefixLength*2); // times two because malloc gets the amount in bytes
	if (NULL == sMonitorFilesPrefixName)
	{
		return WMX_ST_FAIL;
	}
	wcscpy_s(sMonitorFilesPrefixName, prefixLength, monitorFilesPrefix);

	//Check if no DnD message is requested
	//OSAL_enter_critical_section(&configurationsCs);
	//if ((FALSE == sUseMonitor) && (FALSE == sUseTrace))
	//{
	//	TRACE_ERR((L"No data will be sent up since user doesn't use monitors nor traces"));
	//	//free(sTraceFilesPrefixName);
	//	return WMX_ST_FAIL;
	//}
	//OSAL_exit_critical_section(&configurationsCs);

	// Set wrapper's version
	SET_VERSION(	sDnDWrapperVersion,
		DND_MAJOR, 
		DND_MINOR, 
		DND_BUILD, 
		DND_REVISION, 
		DND_BRANCH );		

	// Set wrapper's name
	if (wcslen(cWrapperName) >= WRAPPER_NAME_LEN)
	{
		OSAL_wcsncpy_s(sWrapperName, WRAPPER_NAME_LEN - 1, cWrapperName, WRAPPER_NAME_LEN - 1);
	}
	else
	{
		OSAL_wcscpy_s(sWrapperName, WRAPPER_NAME_LEN - 1, cWrapperName);
	}

	return WMX_ST_OK;
}
wmx_Status_t LoadTraces()
{
	int strTableRes;
	TRACE_INFO((L"Loading TRC files"));
	strTableRes = ConnectToStringTables();
	if (0 != strTableRes)
	{
		TRACE_ERR((L"Failed to ConnectToStringTables (Load TRC file)."));

		//Unable to load DnDWrapper.xml
		if (-1 == strTableRes)
		{
			return WMX_ST_TRACE_INIT_FAILED;
		}
		else //strTableRes == -2. One or more of the trc files weren't found
		{
			return WMX_ST_CONFIG_ERROR;
		}
	}

	TRACE_INFO((L"Finished loading TRC files"));
	return WMX_ST_OK;
}
void UnloadTraces()
{
	TRACE_INFO((L"Unloading TRC files"));
	FreeStringTables();
	TRACE_INFO((L"Finished unloading TRC files"));
}

UINT32 CalcFirstFileIndexForOffline(const WCHAR *offlineFilesPath, const PWCHAR pFilesPrefixName, FILE** pCurFilePtr )
{
	FILE*			tempFile;
	UINT32			i;
	int				pathLength;
	HANDLE          fileHandle;	
	WIN32_FIND_DATAW fileInfo;
	static WCHAR	filePath[_MAX_PATH];
	
	TRACE_INFO(("CalcFirstFileIndexForOffline - start"));

	// first we check if a file exists in the directory
	pathLength  = swprintf(filePath,  _MAX_PATH, L"%s", offlineFilesPath);
	pathLength += swprintf(filePath+pathLength, _MAX_PATH - pathLength, L"/%s*", pFilesPrefixName);
	fileHandle = FindFirstFileW(filePath, &fileInfo);

	// if the directory contains trace files - look for the first one
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		// close the handle to the file
		FindClose(fileHandle); 

		// return the first index
		for (i = 0; i < sMaxNumOfFilesInDir; i++)
		{
			tempFile = GetNextFile(offlineFilesPath, i, pFilesPrefixName);
			if (NULL != tempFile) // file exists and was opened
			{
				sIsFirstFileInDir = FALSE;
				*pCurFilePtr = tempFile;
				TRACE_INFO(L"[CalcFirstFileIndexForOffline]: finished successfully. first file index calculated = %u", i);
				return i;
			}
		}

		// it if the index is not in the indexes range
		TRACE_WAR(L"[CalcFirstFileIndexForOffline]: Error finding first file in directory %s", filePath);
		return sMaxNumOfFilesInDir;
	}
	// if this is an empty directory (at least no trace files) return max
	else
	{
		TRACE_WAR((L"[CalcFirstFileIndexForOffline]: Error finding files in directory %s", filePath));
		return sMaxNumOfFilesInDir;
	}
}

wmx_Status_t InternalInit(BOOL useMonitor, BOOL useTrace, BOOL isOnlineMode , const WCHAR *traceFilesPrefix, const WCHAR *monitorFilesPrefix, const char *appSrvIpAdd, const WCHAR *offlineFilesPath)
{
	//Initialize all common parts for Online and Offline
	sStatus = InternalCommonInit(useMonitor, useTrace, isOnlineMode, traceFilesPrefix, monitorFilesPrefix);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Common initialize failed.");
		return sStatus;
	}

	//Assert valid parameters for Offline
	if (FALSE == sIsOnlineMode) //We work in Offline mode and expect directory
	{
		sStatus = AssertValidParametersForOffline(offlineFilesPath);
		if (WMX_ST_OK != sStatus)
		{
			TRACE_ERR("Error in Offline parameters");
			return sStatus;
		}

		OSAL_enter_critical_section(&fileIndexCs);
		/* Handle Traces */
		sNextTraceFileIndex = CalcFirstFileIndexForOffline(offlineFilesPath, sTraceFilesPrefixName, &sCurTraceFilePtr);
		if (sNextTraceFileIndex >= sMaxNumOfFilesInDir)
		{
			OSAL_exit_critical_section(&fileIndexCs);
			TRACE_ERR ((L"No files were found in Offline dir %s", offlineFilesPath));
			return WMX_ST_DATA_UNAVAILABLE;
		}
		UpdateNextFileIndex(&sNextTraceFileIndex);
		/* Handle Monitors */
		sNextMonitorFileIndex = CalcFirstFileIndexForOffline(offlineFilesPath, sMonitorFilesPrefixName, &sCurMonitorFilePtr);
		if (sNextMonitorFileIndex >= sMaxNumOfFilesInDir)
		{
			/* OSAL_exit_critical_section(&fileIndexCs); */
			TRACE_ERR ((L"No monitor files were found in Offline dir %s, assuming old I/F.", offlineFilesPath));
			sMonitorFilesPrefixName = sTraceFilesPrefixName;
			sNextMonitorFileIndex = CalcFirstFileIndexForOffline(offlineFilesPath, sMonitorFilesPrefixName, &sCurMonitorFilePtr);;
			/* return WMX_ST_DATA_UNAVAILABLE; */ 
		}
		UpdateNextFileIndex(&sNextMonitorFileIndex);
		OSAL_exit_critical_section(&fileIndexCs);
	}
	else //In Online mode
	{
		sStatus = InternalOnlineInit(appSrvIpAdd);
		if (WMX_ST_OK != sStatus)
		{
			TRACE_ERR("Failed to Init Online mode.");
			return sStatus;
		}
	}

	//Load TRC files to memory
	OSAL_enter_critical_section(&configurationsCs);
	if (sUseTrace)
	{
		sStatus = LoadTraces();
		if (WMX_ST_OK != sStatus)
		{
			TRACE_ERR ((L"Failed to Load Traces"));
			return sStatus;
		}
		sCurState |= STATE_TRACE_TABLE_LOADED;
	}
	OSAL_exit_critical_section(&configurationsCs);

	return WMX_ST_OK;
}

wmx_Status_t InternalFinalize()
{
	int retStat;

	//free TRC files loaded
	if (sCurState & STATE_TRACE_TABLE_LOADED)
	{
		UnloadTraces();
		sCurState &= (STATE_ALL - STATE_TRACE_TABLE_LOADED);
	}

	//Unregister from System state change event
	if (sCurState & STATE_SYSTEM_STATE_REGISTERED)
	{
		wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *sL5DispatcherFuncs, sL5Conn );
		sCurState &= (STATE_ALL - STATE_SYSTEM_STATE_REGISTERED);
	}

	//Close thread
	if (sCurState & STATE_THREAD_CREATED )
	{
		TRACE_INFO(L"Finalizing the connection status thread");
		if (0 != OSAL_set_event(eventsHandleArr[0]))
		{
			TRACE_ERR("Failed to set the kill thread event");
			return WMX_ST_FAIL;
		}
		retStat = OSAL_wait_event(sThreadKilled, 5000);
		
		sThreadHandle = NULL;
		sCurState &= (STATE_ALL - STATE_THREAD_CREATED);
	}	

	if (sCurState & STATE_THREAD_KILLED_EVENT_CREATED )
	{
		TRACE_INFO("Finalizing the kill thread event");
		if (sThreadKilled != NULL && FALSE == CloseHandle(sThreadKilled))
		{
			TRACE_ERR("Failed to close kill thread event handle");
			return WMX_ST_FAIL;
		}
		sThreadKilled = NULL;
		sCurState &= (STATE_ALL - STATE_THREAD_KILLED_EVENT_CREATED);
	}

	if (sCurState & STATE_KILL_THREAD_EVENT_CREATED )
	{
		TRACE_INFO("Finalizing the kill thread event");
		if (eventsHandleArr[0] != NULL && FALSE == CloseHandle(eventsHandleArr[0]))
		{
			TRACE_ERR("Failed to close kill thread event handle");
			return WMX_ST_FAIL;
		}
		eventsHandleArr[0] = NULL;
		sCurState &= (STATE_ALL - STATE_KILL_THREAD_EVENT_CREATED);
	}

	if (sCurState & STATE_EVENT_CREATED )
	{
		TRACE_INFO("Finalizing the connection status event");
		if (eventsHandleArr[1] != NULL && FALSE == CloseHandle(eventsHandleArr[1]))
		{
			TRACE_ERR("Failed to close event handle");
			return WMX_ST_FAIL;
		}
		eventsHandleArr[1] = NULL;
		sCurState &= (STATE_ALL - STATE_EVENT_CREATED);
	}
	
	if (sCurState & STATE_CONFIG_STATE_EVENT)
	{
		TRACE_INFO("Finalizing the config state identified event");
		if (eventsHandleArr[2] != NULL && FALSE == CloseHandle(eventsHandleArr[2]))
		{
			TRACE_ERR("Failed to close event handle");
			return WMX_ST_FAIL;
		}
		eventsHandleArr[2] = NULL;
		sCurState &= (STATE_ALL - STATE_CONFIG_STATE_EVENT);
	}

	if (sCurState & STATE_REGISTERED_FOR_EVENTS )
	{
		PIPE_HANDLER_UnregisterCtrlStatusUpdatesCB(EventsCB);
		sCurState &= (STATE_ALL - STATE_REGISTERED_FOR_EVENTS);
	}

	if (sCurState & STATE_APP_SRV_IP_ADD_ALLOCATED )
	{
		free(sAppSrvIpAdd);
		sCurState &= (STATE_ALL - STATE_APP_SRV_IP_ADD_ALLOCATED);
	}

	if (sCurState & STATE_SERVICES_INITIALIZED )
	{
		TRACE_INFO("Finalize Services");
		Services_Fini();
		sCurState &= (STATE_ALL - STATE_SERVICES_INITIALIZED);
	}

	if (sCurState & STATE_PREFIX_NAME_ALLOCATED )
	{
		if (sMonitorFilesPrefixName != sTraceFilesPrefixName)
		{
			free(sMonitorFilesPrefixName);
		}
		free(sTraceFilesPrefixName);
		sCurState &= (STATE_ALL - STATE_PREFIX_NAME_ALLOCATED);
	}

	//Free and close all static parameters
	FreeAllResources();

	if (sCurState & STATE_TRACE_INITIALIZED )
	{
		TRACE_INFO("wmxDnD_Finalize: Success");
		sCurState &= (STATE_ALL - STATE_TRACE_INITIALIZED);
	}
	

	//Disconnect from PipeHandler
	if (sCurState & STATE_HANDLER_CONNECTED )
	{
		TRACE_INFO("Disconnecting from PipeHandler");
		PIPE_HANDLER_Disconnect(sL5Conn);
		sCurState &= (STATE_ALL - STATE_HANDLER_CONNECTED);
	}

	//Keep this last since after Pipe Handler is finalized we can't write Traces anymore!
	if (sCurState & STATE_PIPE_HANDLER_INITIALIZED )
	{
		TRACE_INFO("Finalize PipeHandler");
		PIPE_HANDLER_Finalize();
		sIsConnectedToHandler = FALSE;
		sCurState &= (STATE_ALL - STATE_PIPE_HANDLER_INITIALIZED);
	}

	sL5DispatcherFuncs = NULL;

	return WMX_ST_OK;
}

wmx_Status_t L4MonitorControl(BOOL isMonitorOn)
{
	char on;
	//wmx_Status_t rc;

	if (isMonitorOn)
	{
		TRACE_INFO(L"Sending L5 message to DnD Agent - L4 Monitor On");
		on = 1;
	}
	else
	{
		TRACE_INFO(L"Sending L5 message to DnD Agent - L4 Monitor Off");
		on = 0;
	}

	sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
		L5_TARGET_DND_AGENT,
		DND_AGENT_OPCODE_SET_MON_CONTROL,
		&on, 
		1, 
		NULL,
		NULL,
		NULL);

	if (L5_RESULT_OK != sL5Result)
	{
		TRACE_ERR("Failed sending monitor control in DnD Agent. Rertun Value = %d", sL5Result);
		return wmx_L5ResultToWMXStatus(sL5Result);
	}

	TRACE_INFO(L"L4MonitorControl - finished successfully");
	return WMX_ST_OK;
}
wmx_Status_t L4SetMonitorFilter(char * pMonitorFilterBuff, UINT32 nMonitorFilterBuffSize)
{
	TRACE_INFO(L"Sending L5 message to DnD Agent - Set Monitor Filter");
	sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
		L5_TARGET_DND_AGENT,
		DND_AGENT_OPCODE_SET_MON_FILTER,
		//fullFilesPath,
		(void *)pMonitorFilterBuff,
		(UINT32)nMonitorFilterBuffSize,
		NULL,
		NULL,
		NULL);

	if (L5_RESULT_OK != sL5Result)
	{
		TRACE_ERR("Failed setting setting Monitor Filter to DnD Agent. Return Value = %d", sL5Result);
		return wmx_L5ResultToWMXStatus(sL5Result);
	}

	return WMX_ST_OK;	
}

wmx_Status_t SyncCurrentFilePtr(BOOL syncTraces, BOOL syncMonitors)
{
	UINT32 recvBufferSize = MAX_PATH_LEN + sizeof(int) + 1;
	UINT32 responseId;
	char pRecvBuffer[MAX_PATH_LEN + sizeof(int) + 1] = {'\0'};
	WCHAR pPath[MAX_PATH_LEN];
	UINT32 offset = 0;
	PCHAR  pBufLoc = NULL;
	//FILE * filePtr;
	int res;

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	TRACE_INFO(L"Sending L5 message to DnD Agent - Get Writing Position");
	sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
		L5_TARGET_DND_AGENT,
		DND_AGENT_OPCODE_GET_WRITE_POS,
		NULL, 
		0, 
		&responseId,
		pRecvBuffer,
		&recvBufferSize);

	if (L5_RESULT_OK != sL5Result)
	{
		TRACE_ERR("Failed Sync Current File Ptr in DnD Agent. Rertun Value = %d", sL5Result);
		return wmx_L5ResultToWMXStatus(sL5Result);
	}

	//update the different pointers
	sIsFirstFileInDir = FALSE;
	MultiByteToWideChar(CP_ACP, 0, pRecvBuffer, recvBufferSize, pPath, MAX_PATH_LEN);
	//wcscpy_s(pPath, MAX_PATH_LEN, pRecvBuffer);

	if(syncTraces || !sCurTraceFilePtr)
	{
		pBufLoc = ((PCHAR)pRecvBuffer) + (2*OSAL_strnlen(pRecvBuffer, MAX_PATH_LEN)) + 2;
		OSAL_enter_critical_section(&fileIndexCs);
		sNextTraceFileIndex = *(UINT32*)(pBufLoc);
		OSAL_exit_critical_section(&fileIndexCs);
		TRACE_INFO(L"sNextTraceFileIndex = %d", sNextTraceFileIndex);
		pBufLoc += sizeof(sNextTraceFileIndex);
		offset = *(UINT32*)(pBufLoc);

		sCurTraceFilePtr = GetNextFile(pPath, sNextTraceFileIndex, sTraceFilesPrefixName);
		if (NULL == sCurTraceFilePtr)
		{
			TRACE_WAR(L"Trace file unable to open for reading in directory: %s", sFullFilesPath);
			return WMX_ST_FAIL;
		}

		//move the trace file pointer to the current position
		res = fseek(sCurTraceFilePtr, offset, SEEK_SET);
		OSAL_enter_critical_section(&fileIndexCs);
		UpdateNextFileIndex(&sNextTraceFileIndex);
		OSAL_exit_critical_section(&fileIndexCs);
	}

	if(syncMonitors || !sCurMonitorFilePtr)
	{
		pBufLoc = ((PCHAR)pRecvBuffer) + 2*(OSAL_strnlen(pRecvBuffer, MAX_PATH_LEN)+sizeof(UINT32)) + 2;
		OSAL_enter_critical_section(&fileIndexCs);
		sNextMonitorFileIndex = *(UINT32*)(pBufLoc);
		OSAL_exit_critical_section(&fileIndexCs);
		TRACE_INFO(L"sNextTraceFileIndex = %d", sNextMonitorFileIndex);
		pBufLoc += sizeof(sNextMonitorFileIndex);
		offset = *(UINT32*)(pBufLoc);

		sCurMonitorFilePtr = GetNextFile(pPath, sNextMonitorFileIndex, sMonitorFilesPrefixName);
		if (NULL == sCurMonitorFilePtr)
		{
			TRACE_WAR(L"Monitor file unable to open for reading in directory: %s", sFullFilesPath);
			return WMX_ST_FAIL;
		}

		//move the monitor file pointer to the current position
		res = fseek(sCurMonitorFilePtr, offset, SEEK_SET);
		OSAL_enter_critical_section(&fileIndexCs);
		UpdateNextFileIndex(&sNextMonitorFileIndex);
		OSAL_exit_critical_section(&fileIndexCs);
	}
	return WMX_ST_OK;
}


/**
 * getMessageFromFile
 *
 * Reads an L4 message from a file (Trace or Monitor file). 
 * This is a generic function for reading L4 message.
 *
 * 
 *
 * return wmx_Status_t
 */
wmx_Status_t getMessageFromFile(PCHAR						pMsgBuff, 
								PUINT32 					nMsgBuffSize,
								L3L4CompleteHeader_type**	pL4Header,
								size_t *					pNumOfBytesRead,
								PCHAR						pTmpReadBuffer,
								L3L4CompleteHeader_type*	pTmpL4Header,
								UINT16						opcode,
								PWCHAR						pFullFilesPath, 
								PUINT32						pNextFileIndex, 
								PWCHAR						pFilesPrefixName,
								FILE**						pCurFilePtr,
								PBOOL						pSendImmediateMsg)
{
	BOOL		 useTrace	= FALSE;
	BOOL		 useMonitor	= FALSE;

	if (LAST_INIT == sInitRefCnt)
	{
		return WMX_ST_WRONG_STATE;
	}

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&configurationsCs);
	useTrace	= sUseTrace;
	useMonitor	= sUseMonitor;
	OSAL_exit_critical_section(&configurationsCs);

	if (NULL == pMsgBuff)
	{
		TRACE_ERR("The L4 Buff received in GetMessage was NULL");
		return WMX_ST_FAIL;
	}

	//Assert that the buffer received is larger than the Header size at least
	if (*nMsgBuffSize < HEADER_SIZE)
	{
		TRACE_ERR("The allocated buffer size should be larger than the header size at least (%d)", HEADER_SIZE);
		*nMsgBuffSize = 0;
		return WMX_ST_FAIL;
	}

	//This means that the last time function was called the allocated buffer was too small
	//so we send the message we already have.
	if (*pSendImmediateMsg)
	{
		//Assert that the buffer size is large enough
		if ( (UINT32)(HEADER_SIZE + pTmpL4Header->Length) > *nMsgBuffSize )
		{
			TRACE_ERR("The allocated buffer was too small");
			*nMsgBuffSize = HEADER_SIZE + pTmpL4Header->Length;
			return WMX_ST_BUFFER_TOO_SHORT;
		}

		//Build the returned parameters
		strncpy_s((void *)pMsgBuff, *nMsgBuffSize, (void *)pTmpL4Header, HEADER_SIZE);
		strncpy_s(pMsgBuff + HEADER_SIZE, *nMsgBuffSize, pTmpReadBuffer, pTmpL4Header->Length);
		*nMsgBuffSize = HEADER_SIZE + pTmpL4Header->Length;

		*pSendImmediateMsg = FALSE;
		sNumberOfTimesSearchedForNextMessage = 0;
		return WMX_ST_OK;
	}

	// If we already asked 10 times for the next L4 and didn't get any message back update the path 
	if (sNumberOfTimesSearchedForNextMessage > MAX_NUM_OF_ATTEMPTS_TO_GET_MESSAGE)
	{
		//Get the current path.
		WCHAR tempFilesPath[MAX_PATH_LEN];

		if (READY == PIPE_HANDLER_GetCtrlStatus() && sIsConnectedToHandler)
		{
			sStatus = wmxDnD_GetFullPathToOnlineFiles(tempFilesPath, MAX_PATH_LEN);
			if (WMX_ST_OK != sStatus)
			{
				TRACE_ERR("Failed to GetPath after no messages were found %d times", MAX_NUM_OF_ATTEMPTS_TO_GET_MESSAGE);
				*nMsgBuffSize = 0;
				sNumberOfTimesSearchedForNextMessage = 0;
				return WMX_ST_OK;
			}

			// if the path has changed reset the counter and change the path variable
			if (wcscmp(tempFilesPath, pFullFilesPath) != 0) 
			{
				TRACE_INFO(L"Path changed after no messages were found %d times. Old path - %s. New path - %s", MAX_NUM_OF_ATTEMPTS_TO_GET_MESSAGE, sFullFilesPath, tempFilesPath);
				wcsncpy_s(pFullFilesPath, MAX_PATH_LEN, tempFilesPath, MAX_PATH_LEN);
				TRACE_INFO(L"GetMessage() after GetPath. sIsFirstFileInDir = TRUE. Zeroing sNextFileIndex");
				sIsFirstFileInDir = TRUE;
			}
		}

		sNumberOfTimesSearchedForNextMessage = 0;
	}

	//First time 
	OSAL_enter_critical_section(&fileIndexCs);
	if (sIsFirstFileInDir)
	{
		TRACE_INFO(L"GetMessage(). sIsFirstFileInDir = TRUE. Zeroing sNextFileIndex");
		sNextTraceFileIndex		= 0;
		sNextMonitorFileIndex	= 0;
		if (NULL != sCurTraceFilePtr)
		{
			fclose(sCurTraceFilePtr);
		}
		sCurTraceFilePtr = GetNextFile(sFullFilesPath, sNextTraceFileIndex, sTraceFilesPrefixName);

		if (NULL != sCurMonitorFilePtr)
		{
			fclose(sCurMonitorFilePtr);
		}
		sCurMonitorFilePtr = GetNextFile(sFullFilesPath, sNextMonitorFileIndex, sMonitorFilesPrefixName);

		if (!(sCurTraceFilePtr || sCurMonitorFilePtr))
		{
			TRACE_WAR(L"No compatible files were found or file unable to open for reading in directory: %s", pFullFilesPath);
			*nMsgBuffSize = 0;
			sNumberOfTimesSearchedForNextMessage++;
			OSAL_exit_critical_section(&fileIndexCs);
			return WMX_ST_OK;
		}
		else if(useMonitor && sCurTraceFilePtr && !sCurMonitorFilePtr)
		{
			sMonitorFilesPrefixName = sTraceFilesPrefixName;
			sCurMonitorFilePtr = GetNextFile(sFullFilesPath, sNextMonitorFileIndex, sMonitorFilesPrefixName);
		}
		
		sIsFirstFileInDir = FALSE;
		UpdateNextFileIndex(&sNextTraceFileIndex);
		UpdateNextFileIndex(&sNextMonitorFileIndex);
	}
	OSAL_exit_critical_section(&fileIndexCs);

	//If we got to the end of the file we try to open the next file. If it doesn't exist we return 0
	//in the size and next time we will try to read the same file

	//We must first read the file since feof will return != 0 only when a read attempt as been made when the file
	//is finished.
	*pNumOfBytesRead = fread(pMsgBuff, sizeof(char), HEADER_SIZE, *pCurFilePtr );
	if ( (0 == *pNumOfBytesRead) && (feof(*pCurFilePtr)) ) // we reached the end of the file
	{
		FILE * tmpFilePtr = GetNextFile(pFullFilesPath, *pNextFileIndex, pFilesPrefixName);
		if (NULL == tmpFilePtr) // if a new file doesn't exist
		{
			TRACE_INFO(L"No more messages are found at this point.");
			*nMsgBuffSize = 0;
			sNumberOfTimesSearchedForNextMessage ++;
			return WMX_ST_OK;
		}
		//This means that we have a new file, which means that the current file is indeed finished
		//and we open the next file and work on it.
		fclose(*pCurFilePtr);
		*pCurFilePtr = tmpFilePtr;

		OSAL_enter_critical_section(&fileIndexCs);
		UpdateNextFileIndex(pNextFileIndex);
		OSAL_exit_critical_section(&fileIndexCs);

		TRACE_INFO(L"Moving to next file. pNextFileIndex = %d", *pNextFileIndex);

		//At this point we have the correct file for sure.

		//This means that we just opened the next file and it's still empty
		*pNumOfBytesRead = fread(pMsgBuff, sizeof(char), HEADER_SIZE, *pCurFilePtr );
		if (feof(*pCurFilePtr)) // if the file is empty
		{
			TRACE_INFO(L"No more messages are found at this point.");
			*nMsgBuffSize = 0;
			sNumberOfTimesSearchedForNextMessage++;
			return WMX_ST_OK;
		}
	}
	// If we reached here it means that we haven't reached the end of the current file
	// Read the next L4 in the current file

	//TRACE_INFO(L"Reading L4 message from file");
	if (HEADER_SIZE != *pNumOfBytesRead)
	{
		TRACE_ERR("Unable to read L4 Header from the file");
		*nMsgBuffSize = 0;
		return WMX_ST_FAIL;	
	}

	*pL4Header = (L3L4CompleteHeader_type *)pMsgBuff;

	OSAL_enter_critical_section(&configurationsCs);
	//Identify the type of the L4 (Monitor or Trace) and decide if we raise it or 
	//get the next message
	if (( (L3_L4_OPCODE_REPORT_MONITOR_EVACUATE == (*pL4Header)->Type) &&   (FALSE == sUseMonitor) )||
		( (L3_L4_OPCODE_REPORT_TRACE_EVACUATE == (*pL4Header)->Type)   &&   (FALSE == sUseTrace)   ))
	{
		OSAL_exit_critical_section(&configurationsCs);
		////Move the FILE* to the correct location
		*pNumOfBytesRead = fseek(*pCurFilePtr, (*pL4Header)->Length, SEEK_CUR);

		////This type was not requested so we get next message.
		//TRACE_INFO(L"Found an L4 Message which wasn't requested.");
		*nMsgBuffSize = 0xFFFFFFFF;
		return WMX_ST_OK;		
	}
	OSAL_exit_critical_section(&configurationsCs);

	//This means that we are not synchronized in the file since we've read an L4 Header which
	//wasn't expected. (Not Monitor and not Trace)
	if ((opcode != (*pL4Header)->Type) &&
		(OVERRUN_FAKE_L4_OPCODE != (*pL4Header)->Type))
	{
		//The temporary solution is - Go to the next file.
		//TODO - Change to solution at which we read bytes until we encounter the next
		//L4 Messages. This can be identified by the Type(Monitor || Trace) + Reserved(0) + Status(0)
		TRACE_ERR("Unknown type found. Type searched = 0x%04X, Type found = 0x%04X, Length found = %d", 
			opcode, (*pL4Header)->Type, (*pL4Header)->Length);

		////Move the FILE* to the end of the file - Temporary
		*pNumOfBytesRead = fseek(*pCurFilePtr, 0, SEEK_END);

		*nMsgBuffSize = 0;
		return WMX_ST_FAIL;
	}

	//If there is no payload we return only the header
	if (0 == (*pL4Header)->Length)
	{
		*nMsgBuffSize = HEADER_SIZE;
		return WMX_ST_OK;
	}

	//Assert that the buffer size is large enough
	if ( (UINT32)(HEADER_SIZE + (*pL4Header)->Length) > *nMsgBuffSize )
	{
		//Copy the Header to tmp param
		*pTmpL4Header = **pL4Header;

		//Read the payload from the file
		*pNumOfBytesRead = fread(pTmpReadBuffer, sizeof(char), pTmpL4Header->Length, *pCurFilePtr);
		if (*pNumOfBytesRead != pTmpL4Header->Length)
		{
			//TODO: Decide what to do if there is an error in the file
			TRACE_ERR("Unable to read L4 Payload from the file");
			*nMsgBuffSize = 0;
			return WMX_ST_FAIL;	
		}

		TRACE_ERR("The allocated buffer is too small");
		*nMsgBuffSize = HEADER_SIZE + pTmpL4Header->Length;
		*pSendImmediateMsg = TRUE;

		return WMX_ST_BUFFER_TOO_SHORT;
	}

	*pNumOfBytesRead = fread(pMsgBuff + HEADER_SIZE, sizeof(char), (*pL4Header)->Length, *pCurFilePtr);
	if (*pNumOfBytesRead != (*pL4Header)->Length)
	{
		//TODO: Decide what to do if there is an error in the file
		TRACE_ERR("Unable to read L4 Payload from the file");
		*nMsgBuffSize = 0;
		return WMX_ST_FAIL;	
	}

	//Build the returned parameters
	*nMsgBuffSize = HEADER_SIZE + (*pL4Header)->Length;
	sNumberOfTimesSearchedForNextMessage = 0;

	return WMX_ST_OK;
}

wmx_Status_t WMX_EXT_CALL_CONV GetTrace(	  char * retString, 
											  INT32 * nRetStringSize,	
											  UINT32 * internalTimestamp,
											  UINT32 * severity, 
											  UINT32 * subsys, 
											  UINT32 * module, 
											  char overrun[], 
											  char * fileName, 
											  UINT32 * lineNum, 
											  char * rawData,
											  UINT32 * nRawDataSize)
{
	char inlineString	[USER_STR_MAX_LEN];
	char formatString	[USER_STR_MAX_LEN];

	UINT32 msgSize;
	UINT32 numOfParams;
	INT32 bytesWritten = 0;
	UINT32 params[MAX_NUM_OF_PARAMS];
	UINT32 payloadSize;
	char * pTmpPayload;
	//BOOLEAN bufferOverrun;

	//UINT32 bufSignature;

	// Read Header (signature)
	//if(bufSize < sizeof(headerSignature))
	//{
	//	TRACE(TR_MOD_NDIS_TRACE, TR_SEV_ERR, (L"Signature is missing");	
	//	return;
	//}
	//else
	//{
	//	bufSignature = (*(UINT32 *)pBuf);
	//}
	// update remaining buffer pointer and size
	//bufSize -= sizeof(headerSignature);
	//(UINT32)pBuf += sizeof(headerSignature);
	//// pass over message-message
	//while(bufSize > 0)
	//{

	if (NULL == sCurLocationInTracBufferPtr)
	{
		TRACE_ERR("The Current location pointer wasn't initialized or was finalized.");
		return WMX_ST_FAIL;
	}

	if (*nRetStringSize <= 0)
	{
		TRACE_ERR("Buffer size if 0 or less.");
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	if (sCurLocationInTracBufferPtr >= sEndL4BufferPtr)
	{
		TRACE_INFO(L"Finished parsing all current L4 Traces buffer");
		*nRetStringSize = -1;
		sCurLocationInTracBufferPtr = NULL;
		return WMX_ST_OK;
	}

	BM_TraceRunTimeMsgData_GET_BYTES_SIZE(sCurLocationInTracBufferPtr, msgSize);

	if (0 == msgSize)/* || (msgSize > bufSize))*/
	{
		TRACE_ERR("Wrong message size: msgSize=%d", msgSize);
		return WMX_ST_FAIL;
	}

	//These parameters should be present in all cases (inline string + not inline + error in trc file)
	//therefore we read them first in order to send this data to the user at all situations.
	if(BM_INLINE_TraceRunTimeMsgData_status_timeStampPresent_GET(sCurLocationInTracBufferPtr))
	{
		BM_TraceRunTimeMsgData_timeStampOpt_timeStamp_timeStamp_GET(sCurLocationInTracBufferPtr, *internalTimestamp);
	}
	else
	{
		*internalTimestamp = 0;
	}
	*severity = BM_INLINE_TraceRunTimeMsgData_status_severity_GET(sCurLocationInTracBufferPtr);
	*subsys = BM_INLINE_TraceRunTimeMsgData_status_subSystemID_GET(sCurLocationInTracBufferPtr);
	numOfParams = BM_INLINE_TraceRunTimeMsgData_status_numOfParams_GET(sCurLocationInTracBufferPtr);
	{
		UINT32 i;
		for(i = 0; i < numOfParams; i++)
		{
			BM_TraceRunTimeMsgData_params_value_GET(sCurLocationInTracBufferPtr, i, params[i]);
		}
	}
	if (BM_INLINE_TraceRunTimeMsgData_status_bufferOverrun_GET(sCurLocationInTracBufferPtr))
	{
		strcpy_s(overrun, 10, "BUF_OVRN"); 
	}
	else
	{
		strcpy_s(overrun, 10, "NO_OVRN");
	}

	if(BM_INLINE_TraceRunTimeMsgData_status_payload_GET(sCurLocationInTracBufferPtr))
	{
		BM_TraceRunTimeMsgData_payloadOpt_payload_length_GET(sCurLocationInTracBufferPtr, payloadSize);
		if (*nRawDataSize < payloadSize)
		{
			TRACE_ERR("The allocated buffer for the raw data is too small.");	
			*nRawDataSize = payloadSize;
			return WMX_ST_BUFFER_TOO_SHORT;
		}

		BM_TraceRunTimeMsgData_payloadOpt_payload_payload_GET_POS_ALIGNED(sCurLocationInTracBufferPtr, pTmpPayload);
		memcpy(rawData, pTmpPayload, payloadSize);
		*nRawDataSize = payloadSize;
	}
	else
	{
		*nRawDataSize = 0;
	}

	//Now we check all different cases (inline/not/errors in trc file)
	if(BM_INLINE_TraceRunTimeMsgData_status_inlineString_GET(sCurLocationInTracBufferPtr))// if there exists an inline string
	{
		UINT32	inlineStrLength;
		void	*pInlineStrPos;
		// copy inline string from buffer
		BM_TraceRunTimeMsgData_inlineStringOpt_inlineString_length_GET(sCurLocationInTracBufferPtr, inlineStrLength);
		BM_TraceRunTimeMsgData_inlineStringOpt_inlineString_inlineString_GET_POS_ALIGNED(sCurLocationInTracBufferPtr, pInlineStrPos);
		if(inlineStrLength >= ARRAY_SIZE(inlineString))
		{
			inlineStrLength = ARRAY_SIZE(inlineString) - 1;
		}
		memcpy((void *)inlineString, pInlineStrPos, inlineStrLength); 
		inlineString[inlineStrLength] = '\0';
	}
	else // there is no inline string
	{
		//	inline string is not present, it means that message unique ID is used
		//  to retrieve actual string from the Trace String Table	

		int iBufSize = ARRAY_SIZE(inlineString);

		if(sCurStringTable != INVALID_HSTRING_TABLE)
		{
			// msgId received from the device is the offset in four bytes words
			// Multiply by four to get offset in bytes
			UINT32 msgId = (BM_INLINE_TraceRunTimeMsgData_status_msgID_GET(sCurLocationInTracBufferPtr)) << 2;
			int loadStringRes = TST_LoadString(sCurStringTable, msgId, (char *)inlineString, iBufSize);
			/* Get string from the resource library */
			if(loadStringRes == 0)
			{
				TRACE_ERR("The pStart pointer of the string table is NULL");

				//Update the pointer
				sCurLocationInTracBufferPtr += msgSize;

				return WMX_ST_FAIL;
			}

			if(loadStringRes < 0)
			{
				TRACE_ERR("The offset of the trace in the trc file is out of bounds. Offset = %d TRC file size = %d", msgId, (-1 *loadStringRes));

				//Update the pointer
				sCurLocationInTracBufferPtr += msgSize;

				return WMX_ST_TRACE_INIT_FAILED;
			}

			//If this is an internal string we don't want to return it to the user and set the size parameter
			//to 0
			if (IsInternalTrace(inlineString))
			{
				*nRetStringSize = 0;

				//Update the ptr
				sCurLocationInTracBufferPtr += msgSize;
				return WMX_ST_OK;
			}
		}
		else
		{
			/* failed to load library */
			TRACE_WAR(L"Can't load Trace String Table");
			*nRetStringSize = 0;

			//Update the ptr
			//sCurLocationInTracBufferPtr += msgSize;

			return WMX_ST_FAIL;
		}
		MAKE_ZERO_TERMINATED(inlineString);
	}

	// take out file name, file number, moduleID and format string from inline string
	{
		char tmp[10];
		int scanned;
		formatString[0] = '\0';
		scanned = sscanf_s(inlineString, "%[^@]@%i%2[@(]%i%2[)@]%[^@]", fileName, MAX_PATH, lineNum, tmp, 10, module, tmp, 10, formatString, USER_STR_MAX_LEN);
		if ((NUM_DELIMITERS_WITH_DISPLAY_STRING != scanned) && (NUM_DELIMITERS_WITHOUT_DISPLAY_STRING != scanned))
		{
			TRACE_ERR("Wrong inlineString format, scanned=%d", scanned);

			//Update the ptr
			sCurLocationInTracBufferPtr += msgSize;

			return WMX_ST_FAIL;
		}
	}

	// replace '\t' and '\n' by ' ' in format string
	{
		char *tmp = formatString;
		while((tmp = strpbrk(tmp, "\n\t")) != NULL)
		{
			*tmp++ = ' ';
		}
	}

	//Insert parameter values to the returned string
	// Write user string (format string with parameters)
	switch(numOfParams)
	{
		case 0:
			bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, formatString);
			break;
		case 1:
			bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, formatString, params[0]);
			break;
		case 2:
			bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, formatString, params[0], params[1]);
			break;
		case 3:
			bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, formatString, params[0], params[1], params[2]);
			break;
	}

	if(bytesWritten < 0)
	{
		TRACE_ERR("Failed formatting returned string");

		//Update the pointer
		sCurLocationInTracBufferPtr += msgSize;

		return WMX_ST_FAIL;
	}
	*nRetStringSize = bytesWritten;

	//Update the pointer
	sCurLocationInTracBufferPtr += msgSize;

	return WMX_ST_OK;
}

wmx_Status_t WMX_EXT_CALL_CONV GetRunTimeDilloTrace(	  char * retString, 
														  INT32 * nRetStringSize,	
														  UINT32 * internalTimestamp,
														  UINT32 * severity, 
														  UINT32 * subsys, 
														  UINT32 * module, 
														  char overrun[], 
														  char * fileName, 
														  UINT32 * lineNum, 
														  char * rawData,
														  UINT32 * nRawDataSize)
{
	UINT32 msgSize;
	//TraceLoggerInfo info;
	UINT32 numOfParams;
	UINT32 params[MAX_NUM_OF_PARAMS];
	INT32 bytesWritten = 0;
	//BOOLEAN bufferOverrun;
	UINT32	msgID;
	int loadStringRes;
	BMS_DilloCompileTimeMsgData dilloStruct;

	UNREFERENCED_PARAMETER(rawData);

	if (NULL == sCurLocationInTracBufferPtr)
	{
		TRACE_ERR("The Current location pointer wasn't initialized or was finalized.");
		return WMX_ST_FAIL;
	}

	if (sCurLocationInTracBufferPtr >= sEndL4BufferPtr)
	{
		TRACE_INFO(L"Finished parsing all current L4 Traces buffer");
		*nRetStringSize = -1;
		sCurLocationInTracBufferPtr = NULL;
		return WMX_ST_OK;
	}

	// verify that string table is already loaded
	if(sCurStringTable == INVALID_HSTRING_TABLE)
	{
		TRACE_WAR(L"Can't load Trace String Table");
		*nRetStringSize = 0;
		return WMX_ST_FAIL;
	}

	BM_DilloRunTimeMsgData_GET_BYTES_SIZE(sCurLocationInTracBufferPtr, msgSize);
	if (0 == msgSize)/* || (msgSize > bufSize))*/
	{
		TRACE_ERR("Wrong message size: msgSize=%d", msgSize);
		return WMX_ST_FAIL;
	}

	// message ID starts from 1 and not 0
	msgID = BM_INLINE_DilloMsgStatus_msgID_GET(sCurLocationInTracBufferPtr) - 1;

	// retrieve appropriate section from string table
	if(TST_LoadSection(sCurStringTable, msgID, (LPVOID)&dilloStruct, sizeof(dilloStruct)) <= 0)
	{
		TRACE_ERR("Can't load String from Trace String Table");	
		return WMX_ST_FAIL;
	}

	//load the traces
	loadStringRes = TST_LoadSection(sCurStringTable, msgID, (LPVOID)&dilloStruct, sizeof(dilloStruct));
	if(loadStringRes == 0)
	{
		TRACE_ERR("The pStart pointer of the string table is NULL - error with the table HANDLE");

		//Update the pointer
		sCurLocationInTracBufferPtr += msgSize;
		return WMX_ST_FAIL;
	}
	if(loadStringRes < 0)
	{
		TRACE_ERR("The offset of the trace section in the trc file is out of bounds. Offset = %d TRC file size = %d", (msgID*sizeof(dilloStruct)), (-1 *loadStringRes));

		//Update the pointer
		sCurLocationInTracBufferPtr += msgSize;

		return WMX_ST_TRACE_INIT_FAILED;
	}

	//If this is an internal string we don't want to return it to the user and set the size parameter to 0
	if (IsInternalTrace((char *)dilloStruct._userString))
	{
		*nRetStringSize = 0;

		//Update the ptr
		sCurLocationInTracBufferPtr += msgSize;
		return WMX_ST_OK;
	}


	// send to output (including payload!)
	if(BM_INLINE_DilloMsgStatus_timeStampPresent_GET(sCurLocationInTracBufferPtr))
	{
		UINT16 lsb, msb;
		BM_DilloRunTimeMsgData_timeStampOpt_timeStamp_leastSignificant_GET(sCurLocationInTracBufferPtr, lsb);
		BM_DilloRunTimeMsgData_timeStampOpt_timeStamp_mostSignificant_GET(sCurLocationInTracBufferPtr, msb);
		*internalTimestamp = MAKE_UINT32(msb, lsb);
	}
	else
	{
		*internalTimestamp = 0;
	}
	*severity = dilloStruct._severity;
	*subsys = S_ARMADILLO_SUB_SYS_ID;
	*module = dilloStruct._moduleID;
	strcpy_s(fileName, MAX_PATH, (char *)dilloStruct._fileName);
	*lineNum = dilloStruct._lineNumber;
	numOfParams = BM_INLINE_DilloRunTimeMsgData_status_numOfParams_GET(sCurLocationInTracBufferPtr);
	{
		UINT32 i;
		for(i = 0; i < numOfParams; i++)
		{
			params[i] = (UINT32)BM_INLINE_DilloRunTimeMsgData_params_value_GET(sCurLocationInTracBufferPtr, i);
		}
	}

	if (BM_INLINE_DilloRunTimeMsgData_status_bufferOverrun_GET(sCurLocationInTracBufferPtr))
	{
		strcpy_s(overrun, 10, "BUF_OVRN"); 
	}
	else
	{
		strcpy_s(overrun, 10, "NO_OVRN");
	}

	*nRawDataSize = 0;

	//Insert parameter values to the returned string
	// Write user string (format string with parameters)
	switch(numOfParams)
	{
	case 0:
		bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, (char *)dilloStruct._userString);
		break;
	case 1:
		bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, (char *)dilloStruct._userString, params[0]);
		break;
	case 2:
		bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, (char *)dilloStruct._userString, params[0], params[1]);
		break;
	case 3:
		bytesWritten = _snprintf_s(retString, *nRetStringSize, *nRetStringSize, (char *)dilloStruct._userString, params[0], params[1], params[2]);
		break;
	}

	if(bytesWritten < 0)
	{
		TRACE_ERR("Failed formatting returned string");

		//Update the pointer
		sCurLocationInTracBufferPtr += msgSize;

		return WMX_ST_FAIL;
	}
	*nRetStringSize = bytesWritten;

	//Update the pointer
	sCurLocationInTracBufferPtr += msgSize;

	return WMX_ST_OK;
}

//External APIs
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_Init(BOOL useMonitor, BOOL useTrace, BOOL isOnlineMode , const WCHAR *filesPrefix,const char *appSrvIpAdd, const WCHAR *offlineFilesPath )
{
	wmx_Status_t tmpStatus;
	//static BOOL sStop = TRUE;

	//if (sStop)
	//{
	//	__asm int 3;
	//}

	if ( FIRST_INIT == OSAL_atomic_increment(&sInitRefCnt) )
	{
		sStatus = InternalInit(useMonitor, useTrace, isOnlineMode, filesPrefix, DEFAULT_MONITOR_PREFIX, appSrvIpAdd, offlineFilesPath);
		if (WMX_ST_OK != sStatus)
		{
			tmpStatus = sStatus;
			TRACE_ERR("Init Failed.");
			wmxDnD_Finalize();
			return tmpStatus;
		}
	}
	else
	{
		TRACE_WAR(L"wmxDnD_Init already Initialized");
		sInitRefCnt = FIRST_INIT;
	}
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_InitEx(BOOL useMonitor, BOOL useTrace, BOOL isOnlineMode , const WCHAR *traceFilesPrefix, const WCHAR *monitorFilesPrefix, const char *appSrvIpAdd, const WCHAR *offlineFilesPath )
{
	wmx_Status_t tmpStatus;
	if ( FIRST_INIT == OSAL_atomic_increment(&sInitRefCnt) )
	{
		sStatus = InternalInit(useMonitor, useTrace, isOnlineMode, traceFilesPrefix, monitorFilesPrefix, appSrvIpAdd, offlineFilesPath);
		if (WMX_ST_OK != sStatus)
		{
			tmpStatus = sStatus;
			TRACE_ERR("Init Failed.");
			wmxDnD_Finalize();
			return tmpStatus;
		}
	}
	else
	{
		TRACE_WAR(L"wmxDnD_InitEx already Initialized");
		sInitRefCnt = FIRST_INIT;
	}
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_Finalize()
{
	if ( LAST_INIT == OSAL_atomic_decrement(&sInitRefCnt) )
	{
		sStatus = InternalFinalize();
		if (WMX_ST_OK != sStatus)
		{
			//TRACE_ERR("Failed to finalize");
			return sStatus;
		}

		if ( sInitRefCnt <= LAST_INIT )
		{
			sInitRefCnt = LAST_INIT;
		}	
	}
	else
	{
		sInitRefCnt = LAST_INIT;
	}

	return WMX_ST_OK;
}






wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetTraceMessage(char * pMsgBuff, UINT32 * nMsgBuffSize)
{
	static UINT32						sNumOfAttemptsToGetMessage		= 0;
	static L3L4CompleteHeader_type *	sL4Header;
	static size_t						sNumOfBytesRead					= 0;
	static char							tmpReadBuffer[MAX_BUFF_SIZE];
	static L3L4CompleteHeader_type		tmpL4Header;
	static BOOL							sSendImmediateMsg				= FALSE;

	wmx_Status_t						status							= WMX_ST_OK;

	status = getMessageFromFile(pMsgBuff,
								nMsgBuffSize,
								&sL4Header,
								&sNumOfBytesRead,
								tmpReadBuffer,
								&tmpL4Header,
								L3_L4_OPCODE_REPORT_TRACE_EVACUATE,
								sFullFilesPath,
								&sNextTraceFileIndex,
								sTraceFilesPrefixName,
								&sCurTraceFilePtr,
								&sSendImmediateMsg);
	if (WMX_ST_OK != status)
	{
		TRACE_ERR("getMessageFromFile FAILD !!! Error Code: 0x%X", status);
	}

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetMonitorMessage(char * pMsgBuff, UINT32 * nMsgBuffSize)
{
	static UINT32						sNumOfAttemptsToGetMessage		= 0;
	static L3L4CompleteHeader_type *	sL4Header;
	static size_t						sNumOfBytesRead					= 0;
	static char							tmpReadBuffer[MAX_BUFF_SIZE];
	static L3L4CompleteHeader_type		tmpL4Header;
	static BOOL							sSendImmediateMsg				= FALSE;

	wmx_Status_t						status							= WMX_ST_OK;

	status = getMessageFromFile(pMsgBuff,
								nMsgBuffSize,
								&sL4Header,
								&sNumOfBytesRead,
								tmpReadBuffer,
								&tmpL4Header,
								L3_L4_OPCODE_REPORT_MONITOR_EVACUATE,
								sFullFilesPath,
								&sNextMonitorFileIndex,
								sMonitorFilesPrefixName,
								&sCurMonitorFilePtr,
								&sSendImmediateMsg);
	if (WMX_ST_OK != status)
	{
		TRACE_ERR("getMessageFromFile FAILD !!! Error Code: 0x%X", status);
	}

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetMessage(char * pMsgBuff, UINT32 * nMsgBuffSize)
{
	wmx_Status_t status		= WMX_ST_OK;
	BOOL		 useTrace	= FALSE;
	BOOL		 useMonitor	= FALSE;

	TRACE_INFO(L"wmxDnD_GetMessage - start");

	OSAL_enter_critical_section(&configurationsCs);
	useTrace	= sUseTrace;
	useMonitor	= sUseMonitor;
	OSAL_exit_critical_section(&configurationsCs);

	if(useTrace && useMonitor)
	{
		status = WMX_ST_ILLEGAL_OPERATION;
	} 
	else
	{
		if (useTrace)
		{
			status = wmxDnD_GetTraceMessage(pMsgBuff, nMsgBuffSize);
		} 
		else if(useMonitor)
		{
			status = wmxDnD_GetMonitorMessage(pMsgBuff, nMsgBuffSize);
		}
	}
	if (WMX_ST_OK != status)
	{
		TRACE_ERR("wmxDnD_Get{Monitor,Trace}Message FAILED !!!");
	}

	TRACE_INFO(L"wmxDnD_GetMessage - end");

	return status;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_EnableFileWriting()
{
	char enable = 1;
	//wmx_Status_t rc;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_EnableFileWriting - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to enable file writing in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	//get the current file that is being written and the offset in it
	//rc = SyncCurrentFilePtr();
	//if(WMX_ST_OK != rc)
	//{
	//	return rc;
	//}

	TRACE_INFO(L"Sending L5 message to DnD Agent - Enable File Writing");
	sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
		L5_TARGET_DND_AGENT,
		DND_AGENT_OPCODE_FILE_WRITE,
		&enable, 
		1, 
		NULL,
		NULL,
		NULL);

	if (L5_RESULT_OK != sL5Result)
	{
		TRACE_ERR("Failed enabling file writing in DnD Agent. Rertun Value = %d", sL5Result);
		return wmx_L5ResultToWMXStatus(sL5Result);
	}

	//Get the current path of the Online files
	//sStatus = wmxDnD_GetFullPathToOnlineFiles(sFullFilesPath, MAX_PATH_LEN);
	//if (WMX_ST_OK != sStatus)
	//{
	//	TRACE_ERR("Failed to perform GetPath through EnableWriting method. Return Value = %d", sStatus);
	//	return sStatus;
	//}

	sIsEnabled = TRUE;

	TRACE_INFO(L"wmxDnD_EnableFileWriting - finished successfully");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_DisableFileWriting()
{
	char disable = 0;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_DisableFileWriting - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to disable file writing in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}


		TRACE_INFO(L"Sending L5 message to DnD Agent - Disable File Writing");
		sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
			L5_TARGET_DND_AGENT,
			DND_AGENT_OPCODE_FILE_WRITE,
			&disable, 
			1, 
			NULL,
			NULL,
			NULL);
		if (L5_RESULT_OK != sL5Result)
		{
			TRACE_ERR("Failed disabling file writing in DnD Agent. Rertun Value = %d", sL5Result);
			return wmx_L5ResultToWMXStatus(sL5Result);
		}

		sIsEnabled = FALSE;
		TRACE_INFO(L"wmxDnD_EnableFileWriting - finished successfully");
		return WMX_ST_OK;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SyncFileReading()
{
	wmx_Status_t rc;
	BOOL		 useTrace	= FALSE;
	BOOL		 useMonitor	= FALSE;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_SyncFileRading - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to sync file reading in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	//First we Sync to the current Path
	sStatus = wmxDnD_GetFullPathToOnlineFiles(sFullFilesPath, MAX_PATH_LEN);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to GetPath in Sync");
		return sStatus;				
	}

	OSAL_enter_critical_section(&configurationsCs);
	useTrace	= sUseTrace;
	useMonitor	= sUseMonitor;
	OSAL_exit_critical_section(&configurationsCs);

	//sync to the current file that is being written and the offset in it
	if (FALSE == sIsRemoteMode)
	{
		rc = SyncCurrentFilePtr(useTrace, useMonitor);
		if(WMX_ST_OK != rc)
		{
			return rc;
		}
	}

	TRACE_INFO(L"wmxDnD_SyncFileRading - finished successfully");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SyncTraceFileReading()
{
	wmx_Status_t rc;
	BOOL		 useTrace	= FALSE;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_SyncTraceFileReading - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to sync file reading in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	//First we Sync to the current Path
	sStatus = wmxDnD_GetFullPathToOnlineFiles(sFullFilesPath, MAX_PATH_LEN);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to GetPath in Sync");
		return sStatus;				
	}

	OSAL_enter_critical_section(&configurationsCs);
	useTrace	= sUseTrace;
	OSAL_exit_critical_section(&configurationsCs);

	//sync to the current file that is being written and the offset in it
	if (FALSE == sIsRemoteMode)
	{
		rc = SyncCurrentFilePtr(useTrace, FALSE);
		if(WMX_ST_OK != rc)
		{
			return rc;
		}
	}

	TRACE_INFO(L"wmxDnD_SyncTraceFileReading - finished successfully");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SyncMonitorFileReading()
{
	wmx_Status_t rc;
	BOOL		 useMonitor	= FALSE;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_SyncMonitorFileReading - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to sync file reading in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	//First we Sync to the current Path
	sStatus = wmxDnD_GetFullPathToOnlineFiles(sFullFilesPath, MAX_PATH_LEN);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to GetPath in Sync");
		return sStatus;				
	}

	OSAL_enter_critical_section(&configurationsCs);
	useMonitor	= sUseMonitor;
	OSAL_exit_critical_section(&configurationsCs);

	//sync to the current file that is being written and the offset in it
	if (FALSE == sIsRemoteMode)
	{
		rc = SyncCurrentFilePtr(FALSE, useMonitor);
		if(WMX_ST_OK != rc)
		{
			return rc;
		}
	}

	TRACE_INFO(L"wmxDnD_SyncMonitorFileReading - finished successfully");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetOnlineFilesRootPath( const WCHAR * filesPath )
{
	wmx_Status_t status;
	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_SetOnlineFilesRootPath - start");

	if (NULL == filesPath)
	{
		TRACE_ERR("The files Path was received as NULL - SetPath");
		return WMX_ST_FAIL;
	}

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to set Online files path in Offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsRemoteMode) 
	{
		if (FALSE == sIsConnectedToHandler)
		{
		TRACE_ERR("The connection to the PipeHandler is off");
			return WMX_ST_PIPE_NOT_CONNETED;
		}

		//Send L5 to DnD Agent
		TRACE_INFO(L"Sending L5 message to DnD Agent - Set Path");
		sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
			L5_TARGET_DND_AGENT,
			DND_AGENT_OPCODE_SET_PATH,
			//fullFilesPath,
			(void *)filesPath,
			(UINT32)(wcslen(filesPath) * 2 + 2),
			NULL,
			NULL,
			NULL);

		if (L5_RESULT_OK != sL5Result)
		{
			TRACE_ERR("Failed setting path to DnD Agent. Return Value = %d", sL5Result);
			return wmx_L5ResultToWMXStatus(sL5Result);
		}

		//Save the current set file path
		//free(sCurPathSet);
		ZeroMemory(sCurPathSet, MAX_PATH_LEN * 2);
		sIsPathSet = TRUE;
		//sCurPathSet = (WCHAR *) malloc (wcslen(filesPath) + 2);
		wcscpy_s(sCurPathSet, MAX_PATH_LEN, filesPath);

		//ZeroMemory(sFullFilesPath, MAX_PATH_LEN * 2);
		status = wmxDnD_GetFullPathToOnlineFiles(sFullFilesPath, MAX_PATH_LEN);
		if (WMX_ST_OK != status)
		{
			TRACE_ERR("Failed to GetPath in SetPath func");
			return status;
		}

		//Start reading from the first file in the directory
		TRACE_INFO(L"SetOnlinePath(). sIsFirstFileInDir = TRUE. Zeroing sNextFileIndex");
		sIsFirstFileInDir = TRUE;
		//sNextFileIndex = 0;

		TRACE_INFO(L"wmxDnD_SetOnlineFilesRootPath - finished successfully - Path set to: %s", filesPath);
	}
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetFullPathToOnlineFiles( WCHAR * pFilesPath, UINT32 nfilesMaxPathLength )
{
	UINT32 responseId;
	UINT32 tmpSize = ((UINT32)nfilesMaxPathLength * 2) + 2;
	char tmpBuf[MAX_PATH_LEN];

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_GetFullPathToOnlineFiles - start");

	if (NULL == pFilesPath)
	{
		TRACE_ERR("Files Path was received as NULL - GetPath");
		return WMX_ST_FAIL;
	}

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to get online files path in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsRemoteMode) 
	{
		if (FALSE == sIsConnectedToHandler)
		{
			TRACE_ERR("The connection to the PipeHandler is off");
			return WMX_ST_PIPE_NOT_CONNETED;
		}

		//Send L5 to DnD Agent
		TRACE_INFO(L"Sending L5 message to DnD Agent - Get Path");
		sL5Result = PIPE_HANDLER_SendReceiveL5(	sL5Conn,
			L5_TARGET_DND_AGENT,
			DND_AGENT_OPCODE_GET_PATH,
			NULL,
			0,
			&responseId,
			tmpBuf,
			&tmpSize); //The size of the buffer in bytes
		

		if (L5_RESULT_OK != sL5Result)
		{
			TRACE_ERR("Failed getting path from DnD Agent. Rertun Value = %d", sL5Result);
			return wmx_L5ResultToWMXStatus(sL5Result);
		}

		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)tmpBuf, sizeof(tmpBuf), pFilesPath, nfilesMaxPathLength);
		OSAL_ZeroMemory(&pFilesPath[tmpSize], nfilesMaxPathLength-tmpSize);
		TRACE_INFO(L"wmxDnD_GetFullPathToOnlineFiles - finished successfully. Path is: %s", pFilesPath);
		return WMX_ST_OK;
	}
	else // if we are in the remote mode - read the path from the registry
	{
		BOOL res;
		char dndOutputDirectoryPath[MAX_ANSWER_SIZE];
		res = L4Configurations_getDndFilesPath(dndOutputDirectoryPath);
		if (res)
		{
			MultiByteToWideChar(CP_ACP, 0, dndOutputDirectoryPath, sizeof(dndOutputDirectoryPath), pFilesPath, nfilesMaxPathLength);
			//wcscpy_s(pFilesPath, nfilesMaxPathLength, dndOutputDirectoryPath);
			return WMX_ST_OK;
		}
		else
		{
			TRACE_ERR((L"Error Getting the path to the output files"));
			return WMX_ST_FAIL;
		}
	}
}





wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_MonitorON()
{
	//CmdMonitorControl_type monControl;
	//wmx_Status_t resReceived;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_MonitorON - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to turn monitor ON in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	sStatus = DeviceMonitorOnControl(sL5Conn, sL5DispatcherFuncs);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to set Monitor ON to the Device. Ret value = %d", sStatus);
		return sStatus;
	}

	sStatus = L4MonitorControl(TRUE);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to set Monitor ON to the L4. Ret value = %d", sStatus);
		return sStatus;
	}

	sIsMonitorOnSet = TRUE;
	TRACE_INFO(L"wmxDnD_MonitorON - finished successfully");
	return sStatus;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_MonitorOFF()
{
	//CmdMonitorControl_type monControl;
	//wmx_Status_t resReceived;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_MonitorOFF - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to turn monitor OFF in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	sStatus = DeviceMonitorOffControl(sL5Conn, sL5DispatcherFuncs);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Failed to set Monitor ON to the Device. Ret value = %d", sStatus);
		return sStatus;
	}

	sIsMonitorOnSet = FALSE;
	TRACE_INFO(L"wmxDnD_MonitorOFF - finished successfully");
	return sStatus;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetMonitorFilter( char * pMonitorFilterBuff, UINT32 nMonitorFilterBuffSize )
{
	//SetMonitorFilterTable_type monSetFilter;
	//wmx_Status_t resReceived;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_SetMonitorFilter - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to set Monitor Filter in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	sStatus = DeviceSetMonitorFilter(sL5Conn, sL5DispatcherFuncs, pMonitorFilterBuff, nMonitorFilterBuffSize);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Set Device Monitor Filter Failed. Ret value = %d", sStatus);
		return sStatus;
	}

	sStatus = L4SetMonitorFilter(pMonitorFilterBuff, nMonitorFilterBuffSize);
	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Set L4 Monitor Filter Failed. Ret value = %d", sStatus);
		return sStatus;
	}

	memcpy(sCurMonitorFilter, pMonitorFilterBuff, nMonitorFilterBuffSize);
	sCurMonitorFilterSize = nMonitorFilterBuffSize;
	sIsMonitorFilterSet = TRUE;
	TRACE_INFO(L"wmxDnD_SetMonitorFilter - finished successfully");
	return sStatus;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetMonitorFilter( char * pMonitorFilterBuff, UINT32 * nMonitorFilterBuffSize )
{
	GetMonitorFilterTable_type monGetFilter;
	wmx_Status_t resReceived;
	UINT32 actualBufferSize;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO(L"wmxDnD_GetMonitorFilter - start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to get Monitor Filter in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	L4BM_Init_GetMonitorFilterTable(&monGetFilter);
	//L4BM_Init_GetMonitorFiltersL4(&monGetFilter);
	monGetFilter.MonitorFilterTable.Type = L4_L3_OPCODE_GET_MONITOR_FILTER_TABLE; //TODO: Change to real type

	sStatus = wmx_SendL4Command(	&monGetFilter,
									GetMonitorFilterTable_Funcs,
									*sL5DispatcherFuncs,
									sL5Conn,
									&resReceived);

	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Send GetMonitorFilter L4 - failed");
		return sStatus;
	}

	if (WMX_ST_OK != resReceived)
	{
		TRACE_ERR("Response to Send Monitor ON L4 - failed. Returned value is: %d", resReceived);
		return resReceived;
	}

	//Return the returned buffer in the OUT parameters - if size is big enough
	//TODO: Change the Bitman file and compile with Buffman in order to fit this.
	//actualBufferSize = L4BM_GetBufferSize_GetMonitorFiltersL4(monGetFilter) - HEADER_SIZE - 4 /*4 = Type(2 Bytes) + Length (2 Bytes)*/;
	actualBufferSize = L4BM_GetBufferSize_GetMonitorFilterTable(monGetFilter) - HEADER_SIZE - 4 /*4 = Type(2 Bytes) + Length (2 Bytes)*/;
	if (*nMonitorFilterBuffSize < actualBufferSize)
	{
		TRACE_ERR("The user supplied a buffer too small for GetMonitorFilter");
		*nMonitorFilterBuffSize = actualBufferSize;
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	memcpy(pMonitorFilterBuff, monGetFilter.MonitorFilterTable.FilterTable, actualBufferSize);
	*nMonitorFilterBuffSize = actualBufferSize;

	TRACE_INFO(L"wmxDnD_GetMonitorFilter - finished successfully");
	return sStatus;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetTraceFilter(char * pTraceFilterBuff, UINT32 nTraceFilterBuffSize)
{
	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_FAIL;
	}

	TRACE_INFO(L"Setting Trace filter severities - Start");
	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to set Trace Filter in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	if (nTraceFilterBuffSize != TRACE_SEVERITIES_TABLE_SIZE)
	{
		TRACE_ERR("The trace severity table should be: %d and not %d", TRACE_SEVERITIES_TABLE_SIZE, nTraceFilterBuffSize);
		return WMX_ST_WRONG_ARGUMENT;
	}
	// send the L4 command and return the status
	sStatus = DeviceSetTraceFilter(sL5Conn, sL5DispatcherFuncs, pTraceFilterBuff, nTraceFilterBuffSize);
	if (sStatus != WMX_ST_OK)
	{
		return sStatus;
	}

	memcpy(sCurTraceFilter, pTraceFilterBuff, nTraceFilterBuffSize);
	sCurTraceFilterSize = nTraceFilterBuffSize;
	sIsTraceSevSet = TRUE;
	TRACE_INFO(L"Setting Trace filter severities - Finish");
	return sStatus;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetTraceFilter(char * pTraceFilterBuff, UINT32 * nTraceFilterBuffSize)
{
	GetTraceSeverityTable_type trcGetFilter;
	wmx_Status_t resReceived;
	UINT32 actualBufferSize;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_FAIL;
	}

	TRACE_INFO(L"Getting Trace filter severities - Start");

	if (FALSE == sIsOnlineMode)
	{
		TRACE_WAR(L"Unable to get Trace Filter in offline mode");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	if (FALSE == sIsConnectedToHandler)
	{
		TRACE_ERR("The connection to the PipeHandler is off");
		return WMX_ST_PIPE_NOT_CONNETED;
	}

	L4BM_Init_GetTraceSeverityTable(&trcGetFilter);
	//L4BM_Init_GetSeveritiesL4(&trcGetFilter);
	trcGetFilter.TraceSeverityTable.Type = L4_L3_OPCODE_GET_TRACE_SEVERITY_TABLE; //TODO: Change to real type

	sStatus = wmx_SendL4Command(	&trcGetFilter,
									GetTraceSeverityTable_Funcs,
									*sL5DispatcherFuncs,
									sL5Conn,
									&resReceived);

	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Send GetTraceFilter L4 - failed");
		return sStatus;
	}

	if (WMX_ST_OK != resReceived)
	{
		TRACE_ERR("Response to Send Monitor ON L4 - failed. Returned value is: %d", resReceived);
		return resReceived;
	}

	//Return the returned buffer in the OUT parameters - if size is big enough
	actualBufferSize = L4BM_GetBufferSize_GetTraceSeverityTable(trcGetFilter) - HEADER_SIZE - 4 /*4 = Type(2 Bytes) + Length (2 Bytes)*/;
	//actualBufferSize = L4BM_GetBufferSize_GetSeveritiesL4(trcGetFilter) - HEADER_SIZE - 4 /*4 = Type(2 Bytes) + Length (2 Bytes)*/;
	if (*nTraceFilterBuffSize < actualBufferSize)
	{
		TRACE_ERR("The user supplied a buffer too small for GetTraceFilter");
		*nTraceFilterBuffSize = actualBufferSize;
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	memcpy(pTraceFilterBuff, trcGetFilter.TraceSeverityTable.SeverityTable, actualBufferSize);
	*nTraceFilterBuffSize = actualBufferSize;

	TRACE_INFO(L"Getting Trace filter severities - Finished");
	return sStatus;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCurrentTraceFileIndex(UINT32 * nCurrentFileIndex)
{
	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO((L"wmxDnD_GetCurrentTraceFileIndex - start"));

	OSAL_enter_critical_section(&fileIndexCs);
	if (0 == sNextTraceFileIndex)
	{
		*nCurrentFileIndex = sNextTraceFileIndex;
	}
	else
	{
		*nCurrentFileIndex = sNextTraceFileIndex - 1;
	}
	OSAL_exit_critical_section(&fileIndexCs);

	TRACE_INFO(L"wmxDnD_GetCurrentTraceFileIndex - finsihed successfully. *nCurrentFileIndex = %u", *nCurrentFileIndex);
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCurrentMonitorFileIndex(UINT32 * nCurrentFileIndex)
{
	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO((L"wmxDnD_GetCurrentMonitorFileIndex - start"));

	OSAL_enter_critical_section(&fileIndexCs);
	if (0 == sNextMonitorFileIndex)
	{
		*nCurrentFileIndex = sNextMonitorFileIndex;
	}
	else
	{
		*nCurrentFileIndex = sNextMonitorFileIndex - 1;
	}
	OSAL_exit_critical_section(&fileIndexCs);

	TRACE_INFO(L"wmxDnD_GetCurrentMonitorFileIndex - finsihed successfully. *nCurrentFileIndex = %u", *nCurrentFileIndex);
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCurrentFileIndex(UINT32 * nCurrentFileIndex)
{
	BOOL		 useTrace	= FALSE;
	BOOL		 useMonitor	= FALSE;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO((L"wmxDnD_GetCurrentFileIndex - start"));

	OSAL_enter_critical_section(&configurationsCs);
	useTrace	= sUseTrace;
	useMonitor	= sUseMonitor;
	OSAL_exit_critical_section(&configurationsCs);

	OSAL_enter_critical_section(&fileIndexCs);
	if (useTrace && useMonitor)
	{
		*nCurrentFileIndex = sNextTraceFileIndex + sNextMonitorFileIndex;
		*nCurrentFileIndex -= ((*nCurrentFileIndex) ? 2 : 0);
	} 
	else
	{
		*nCurrentFileIndex = (useTrace ? sNextTraceFileIndex : sNextMonitorFileIndex);
		*nCurrentFileIndex -= ((*nCurrentFileIndex) ? 1 : 0);
	}
	OSAL_exit_critical_section(&fileIndexCs);

	TRACE_INFO(L"wmxDnD_GetCurrentFileIndex - finsihed successfully. *nCurrentFileIndex = %u", *nCurrentFileIndex);
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_SetConfiguration(BOOL useMonitor, BOOL useTrace)
{
	wmx_Status_t st;

	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO((L"wmxDnD_SetConfiguration - start"));

	//if (FALSE == useMonitor && FALSE == useTrace)
	//{
	//	TRACE_ERR((L"Cannot set both trace and monitor to FALSE"));
	//	return WMX_ST_FAIL;
	//}

	OSAL_enter_critical_section(&configurationsCs);
	if (sUseMonitor != useMonitor)
	{
		sUseMonitor = useMonitor;
	}

	if (sUseTrace != useTrace)
	{
		//Load TRC files to memory
		if (useTrace)
		{
			st = LoadTraces();
			if (WMX_ST_OK != st)
			{
				TRACE_ERR ((L"Failed to Load Traces"));
				return st;
			}
			sCurState |= STATE_TRACE_TABLE_LOADED;
		}
		else //Unload the TRC files.
		{		
			UnloadTraces();
			sCurState &= (STATE_ALL - STATE_TRACE_TABLE_LOADED);
		}
		sUseTrace = useTrace;
	}

	OSAL_exit_critical_section(&configurationsCs);

	TRACE_INFO(L"wmxDnD_SetConfiguration - finsihed successfully. Current configuration - monitor = %i, traces = %i", (int)sUseMonitor, (int)sUseTrace);
	return WMX_ST_OK;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetConfiguration(BOOL * useMonitor, BOOL * useTrace)
{
	if (sCurState == STATE_NOT_INITIALIZED)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	TRACE_INFO((L"wmxDnD_GetConfiguration - start"));

	OSAL_enter_critical_section(&configurationsCs);
	*useMonitor = sUseMonitor;
	*useTrace = sUseTrace;
	OSAL_exit_critical_section(&configurationsCs);

	TRACE_INFO(L"wmxDnD_GetConfiguration - finished successfully. Current configuration: monitors = %i, traces = %i", sUseMonitor, sUseTrace);
	return WMX_ST_OK;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_InitTraceParseFunc(char * pL4Buff, UINT32 * msbTimestamp, UINT32 * lsbTimeStamp, wmxDnD_GetNextTrace * pFunc)
{
	UINT32 type, bufferSig;
	L3L4CompleteHeader_type header;
	//Get the timestamp and return it in out params
	//TODO: Assert endianness for the timestamp reading

	if (NULL == pL4Buff)
	{
		TRACE_ERR("The L4 Buffer is NULL - InitTraceParseFunc");
		return WMX_ST_FAIL;
	}

	*msbTimestamp = *(UINT32*)(pL4Buff + HEADER_SIZE + TYPE_SIZE + LENGTH_SIZE);
	*lsbTimeStamp = *(UINT32*)(pL4Buff + HEADER_SIZE + TYPE_SIZE + LENGTH_SIZE + BST_MSB_SIZE); //4 is the size of the msb timestamp

	header = *(L3L4CompleteHeader_type*)pL4Buff;

	//Update the function ptr according to the type of the trace
	type = *(UINT32*)(pL4Buff + HEADER_SIZE + TYPE_SIZE + LENGTH_SIZE + BST_MSB_SIZE + BST_LSB_SIZE);
	bufferSig = *((UINT32*)(pL4Buff + HEADER_SIZE + TYPE_SIZE + LENGTH_SIZE + BST_MSB_SIZE + BST_LSB_SIZE + SUB_SYS_SIZE));

	switch (type)
	{
		case DEVICE_MODE_DRIVER_SUB_SYS_ID:
			*pFunc = ((wmxDnD_GetNextTrace)GetTrace);	
			sCurStringTable = GetStringTableArm1();
			if (GetSignatureArm1() != bufferSig)
			{
				TRACE_ERR("Arm1 trc file not updated. Buffer sig = %d, trc file sig = %d", bufferSig,GetSignatureArm1());
				return WMX_ST_FAIL;
			}
			break;
		case S_ARMADILLO_SUB_SYS_ID:
			*pFunc = ((wmxDnD_GetNextTrace)GetRunTimeDilloTrace);
			sCurStringTable = GetStringTableSDillo();
			break;
		case FW_SUB_SYS_ID:
			*pFunc = ((wmxDnD_GetNextTrace)GetTrace);	
			sCurStringTable = GetStringTableArm0();
			if (GetSignatureArm0() != bufferSig)
			{
				TRACE_ERR("Arm0 trc file not updated. Buffer sig = %d, trc file sig = %d", bufferSig,GetSignatureArm0());
				return WMX_ST_FAIL;
			}
			break;
		default:
			*pFunc = ((wmxDnD_GetNextTrace)GetTrace);
			sCurStringTable = GetStringTableArm0();
			break;
	}

	//Update the pointer to be at the first trace in the L4 payload
	sCurLocationInTracBufferPtr = pL4Buff + HEADER_SIZE + TYPE_SIZE + LENGTH_SIZE + BST_MSB_SIZE + BST_LSB_SIZE + SUB_SYS_SIZE + SIGNATURE_SIZE;//8 is the size of full bst
	sEndL4BufferPtr = pL4Buff + HEADER_SIZE + header.Length;
	return WMX_ST_OK;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)
{
	wmx_Status_t status = WMX_ST_FAIL;
	if (sCurState & STATE_PIPE_HANDLER_INITIALIZED && sIsConnectedToHandler)
	{
		status = PIPE_HANDLER_RegisterCtrlStatusUpdatesCB(ctrlStatusUpdateCB);
	}
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)
{
	wmx_Status_t status = WMX_ST_FAIL;
	if (sIsConnectedToHandler)
	{
		status = PIPE_HANDLER_UnregisterCtrlStatusUpdatesCB(ctrlStatusUpdateCB);
	}
	return status;
}

wmx_CtrlStatus_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetCtrlStatus()
{
	if (sCurState == STATE_NOT_INITIALIZED || FALSE == sIsConnectedToHandler)
	{
		return NOT_READY;
	}

	return PIPE_HANDLER_GetCtrlStatus();
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxDnD_GetVersion(wmx_pVersion_t version, wmx_pVersionStr_t versionStr, wmx_VersionStrLen_t verMaxLen)
{
	char tempVersionStr[51];

	if (sCurState == STATE_NOT_INITIALIZED || FALSE == sIsConnectedToHandler)
	{
		return WMX_ST_FAIL;
	}

	if (version != NULL)
	{
		version->major = sDnDWrapperVersion.major;
		version->minor = sDnDWrapperVersion.minor;
		version->build = sDnDWrapperVersion.build;
		version->revision = sDnDWrapperVersion.revision;
		version->branch = sDnDWrapperVersion.branch;
	}
	OSAL_sprintf_s(tempVersionStr,
					50, 
					"%ws %d.%d.%d.%d.%d", 
					sWrapperName, 
					sDnDWrapperVersion.major, 
					sDnDWrapperVersion.minor, 
					sDnDWrapperVersion.build, 
					sDnDWrapperVersion.revision, 
					sDnDWrapperVersion.branch );
	if (versionStr != NULL)
	{
		if (verMaxLen >= (wmx_VersionStrLen_t)OSAL_strnlen(tempVersionStr, 51) + 2)
		{
			OSAL_strcpy_s(versionStr, OSAL_strnlen(tempVersionStr, 51)+2, tempVersionStr);
		}
		else
		{
			return WMX_ST_BUFFER_TOO_SHORT;
		}
	}
	return WMX_ST_OK;
}

