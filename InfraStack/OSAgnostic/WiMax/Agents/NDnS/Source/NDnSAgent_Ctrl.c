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
#include "NDnSAgent_Internals.h"
#include "wmxSDK_Nds_Utils.h"
#include "NDnS_L4Scanner.h"
#include "NDnS_L4Publisher.h"
#include "NDnSAgent_APDO.h"
#include "NDnSAgent_DB_if.h"
#include "NDnSAgent_Utils.h"
#include "NDnSAgent.h"
#include "Act.h"
#include "NDnS_Coex.h"

#include "wmxSDK_Nds_CtrlAgent.h"
#include "wmxSDK_Sup_CtrlAgent.h"
#include "wmxSDK_Msc_CtrlAgent.h"
#include "wmxSDK_Sup_4.h"

#include "L4ConfigurationManager.h"
#include "IndicatorsSubscribers.h"
#include "NDnSAgent_Monitor.h"
#include "wimax_osal_services_cmn.h"

// callbacks to register
//void L4Pub_SendScanCompleted(wmx_ScanStatus_t scanStatus);
void NDnSAgent_ConnectCompleted( wmx_ConnectStatus_t connectStatus );
void NDnSAgent_SystemStateUpdate( wmx_pSystemStateUpdate systemStateUpdate );
void NDnSAgent_MediaStatusUpdate( wmx_MediaStatus_t mediaStatus );
void NDnSAgent_RecentBSs(UINT32 numOfChannelInfos, wmx_pChannelInfo_t pChannelInfos);
void NDnSAgent_SupEventReport( wmx_SupEvent_t event );
void NDnSAgent_BEKReport( wmx_pBEKBuffer_t pBEKBuffer );
APPSRV_INIT_ST NDnSAgent_InitializeInternal();

// L5
void NDnSAgent_MessagesHandler(	
	L5_CONNECTION Conn, L5_TARGET_ID nOriginID,
	UINT32 dwSentMessageID, void  *pvSentBuffer, UINT32 cbSentBufferSize,
	UINT32 *pdwResponseMessageID, void  *pvResponseBuffer, UINT32 *cbResponseBufferSize,
	void *pvUserContext, void *pvReserved );

//
wmx_Status_t NDnSAgent_StartScan();
void InitParameters();

OSAL_thread_t act_thread_coexHandler =NULL;
wmx_CoexistenceMode_t initialCoexMode;

// This is a flag that indicates a corrupted db file. Used to prevent save of wrong data.
static BOOL restoreDBSuccess = TRUE;
tUtilityFunctions *pUtils;

void NDnSAgent_FinalizeInternalResources()
{
	NDnSAgent_HandleApdoLinkStatus(APDO_linkDown);
	if (g_ndnsContext.indicatorSubscribersList != NULL)
	{
		//clean the status indicator subscribers list:
		CleanIndicatorsList(&g_ndnsContext.indicatorSubscribersList);
		g_ndnsContext.indicatorSubscribersList = NULL;
	}

	if (g_ndnsContext.connectCompletedEvent != NULL)
	{
		OSAL_set_event(g_ndnsContext.connectCompletedEvent);
		OSAL_delete_event(g_ndnsContext.connectCompletedEvent);
		g_ndnsContext.connectCompletedEvent = NULL;
	}

	if (g_ndnsContext.startManualScanCompletedEvent != NULL)
	{
		OSAL_set_event(g_ndnsContext.startManualScanCompletedEvent);
		OSAL_delete_event(g_ndnsContext.startManualScanCompletedEvent);
		g_ndnsContext.startManualScanCompletedEvent = NULL;
	}

	if (g_ndnsContext.dualFlushOpEvent != NULL)
	{
		OSAL_set_event(g_ndnsContext.dualFlushOpEvent);
		OSAL_delete_event(g_ndnsContext.dualFlushOpEvent);
		g_ndnsContext.dualFlushOpEvent = NULL;
	}

	if( g_ndnsContext.disconnectCompletedEvent != NULL )
	{
		OSAL_set_event(g_ndnsContext.disconnectCompletedEvent);
		OSAL_delete_event( g_ndnsContext.disconnectCompletedEvent );
		g_ndnsContext.disconnectCompletedEvent = NULL;
	}

	if( g_ndnsContext.hScanStartedEvent != NULL )
	{
		OSAL_set_event(g_ndnsContext.hScanStartedEvent);
		OSAL_delete_event( g_ndnsContext.hScanStartedEvent );
		g_ndnsContext.hScanStartedEvent = NULL;
	}
	
	FSM_Finalize(&g_ndnsContext.fsm);
	L4Pub_Finalize();
	OSAL_delete_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
	OSAL_delete_critical_section(&g_ndnsContext.lockSetMode);
	OSAL_delete_critical_section(&g_ndnsContext.lockSystemState);
	//Oem
	L4db_DeInit();
	g_ndnsContext.isLinkUpThreadAlive = FALSE;
	if (LinkUpThreadHandle != NULL)
	{
		OSAL_timedjoin_thread(LinkUpThreadHandle, 1000, 0);
	}
	
	OSAL_delete_critical_section(&g_ndnsContext.linkUpCS);
}

wmx_Status_t NDnSAgent_InitializeInternalResources()
{
	UINT32 res = 0;
	char answer[MAX_ANSWER_SIZE];
	char path[MAX_REGISTRY_ANSWER];
	wmx_Status_t st = WMX_ST_OK;
	
	static BOOL isRestarting = FALSE; //[Oran] Patch for fast reconnect on assert
	
	//ZeroMemory(&g_ndnsContext, sizeof(wmx_NDnS_Context_t));
	memset(&g_ndnsContext, 0, sizeof(g_ndnsContext));

	// Init critical sections
	OSAL_init_critical_section( &(g_ndnsContext.lockSystemState) );
	OSAL_init_critical_section( &(g_ndnsContext.lockSetMode) );
	OSAL_init_critical_section( &(g_ndnsContext.availableNSPsList.criticalSection) );
	if (!isRestarting)
	{
		isRestarting = TRUE;
		if(FSM_Init(&g_ndnsContext.fsm) == FALSE)		
		{
			return WMX_ST_FAIL;
		}
	}
	else //[Oran] Patch for fast reconnect on assert
	{		
		FSM_InitNoReset(&g_ndnsContext.fsm);
	}	
	FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, L4C_UNINITIALIZED, L4C_UNINITIALIZED);	
	
	L4Pub_Init();
	
	// Initialize critical section for linkUp CB
	OSAL_init_critical_section(&g_ndnsContext.linkUpCS);
	if(L4db_Init() != WMX_ST_OK)
	{
		return WMX_ST_FAIL;
	}
	
	if( g_ndnsContext.indicatorSubscribersList != NULL )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	AllocIndicatorsList(&g_ndnsContext.indicatorSubscribersList);
	if ( NULL == g_ndnsContext.indicatorSubscribersList )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Indicator List Allocation Fail!");
		return WMX_ST_FAIL;
	}

	
	if( g_ndnsContext.connectCompletedEvent != NULL )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	if ( 0 != OSAL_create_event( &g_ndnsContext.connectCompletedEvent, FALSE, FALSE, NULL ) )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "Error initializing connect completed event");
		return WMX_ST_FAIL;
	}

	if( g_ndnsContext.startManualScanCompletedEvent != NULL )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	if ( 0 != OSAL_create_event( &g_ndnsContext.startManualScanCompletedEvent, FALSE, FALSE, NULL ) )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "Error initializing manual scan event");
		return WMX_ST_FAIL;
	}

	if( g_ndnsContext.dualFlushOpEvent != NULL )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	if ( 0 != OSAL_create_event( &g_ndnsContext.dualFlushOpEvent, FALSE, FALSE, NULL ))
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "Error initializing dualFlushOpEvent event");
		return WMX_ST_FAIL;
	}

	if( g_ndnsContext.disconnectCompletedEvent != NULL )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	if ( 0 !=  OSAL_create_event( &g_ndnsContext.disconnectCompletedEvent, FALSE, FALSE, NULL ))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Event Creation Fail!");
		return WMX_ST_FAIL;
	}	

	if( g_ndnsContext.hScanStartedEvent != NULL )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	if ( 0 != OSAL_create_event( &g_ndnsContext.hScanStartedEvent, FALSE, FALSE, NULL ) )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Event Creation Fail!");
		return WMX_ST_FAIL;
	}

	// Load Config must be Last in initialization process
	res = L4Configurations_getDriverMode(answer);	
	if (0 == OSAL_stricmp("dSim", answer)) 
	{
		OSAL_BuildFullPath(NDNS_DSIM_ENC_CONFIG_FILE, path, MAX_REGISTRY_ANSWER);				
		RunWithDSim = TRUE;
	}
	else
	{
		OSAL_BuildFullPath(WiMAX_ENC_DB, path, MAX_REGISTRY_ANSWER);
		RunWithDSim = FALSE;
	}
	
	st = L4db_RestoreFromFile(path);
	
	if ( st != WMX_ST_OK )
	{	
		// try restore defaults 
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "restore from default start file %s -> failed\n",path);
		st = L4db_RestoreFromDefaults();
		if (st != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Failed to restore default config file!");
			restoreDBSuccess = FALSE;
			return WMX_ST_CONFIG_ERROR;
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Config File Parse Error. Using Defaults.");
			restoreDBSuccess = TRUE;
		}
	}
	else
	{
		restoreDBSuccess = TRUE;
	}
	L4db_ResetLastDetectedNaps();

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Load Config from file");	

	return WMX_ST_OK;
}


// 
void UnRegisterCallbacksOnWrapper()
{
	wmx_UnregisterScanUpdateCB();
	wmx_UnregisterAllSystemStateUpdateCBs();
	wmx_UnregisterMediaStatusCB();
	wmx_UnregisterBsInfoUpdateCB();
	wmx_UnregisterRecentBSsCB();
	wmx_UnregisterSIIUpdateCB();
	wmx_UnregisterBEKBufferCB();
	if ( TRUE == g_ndnsContext.isSupplicantStarted )
	{
		wmx_UnregisterEventReportCB();
	}
}


// 
wmx_Status_t RegisterCallbacksOnWrapper()
{
	wmx_Status_t status;

	status = wmx_RegisterScanUpdateCB(&L4S_ScanUpdate);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterSystemStateUpdateCB(&NDnSAgent_SystemStateUpdate);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterMediaStatusCB(&NDnSAgent_MediaStatusUpdate);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterBsInfoUpdateCB(&L4S_BsInfoUpdate);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterRecentBSsCB(&NDnSAgent_RecentBSs);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterSIIUpdateCB(&L4S_SIIUpdate);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterBEKBufferCB(&NDnSAgent_BEKReport);
	if ( WMX_ST_OK != status )
	{
		return status;
	}

	if ( TRUE == g_ndnsContext.isSupplicantStarted)
	{
		status = wmx_RegisterEventReportCB(&NDnSAgent_SupEventReport);
		if ( WMX_ST_OK != status )
		{
			return status;
		}
	}

	return status;
}

void NDnSAgent_EventHandler( 
									 L5_CONNECTION Conn,
									 L5_EVENT eEvent,
									 void *pvEventData,
									 void *pvUserContext )
{
	wmx_Status_t status;
	wmx_SystemStateUpdate systemStateUpdate;
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "%s L5 event received", L5_EVENT_STR(eEvent));


	switch(eEvent)
	{
	case L5_EVENT_DRIVER_DISCONNECTED: // Unregister all indications that were registered on the agent
		status = wmx_UnregisterEventReportCB();
		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Deregisteration of supplicant reports skipped. Already not registered",eEvent);
		}
		// clean all indications' targets
		EmptyIndicatorsList(&g_ndnsContext.indicatorSubscribersList);
		break;
	case L5_EVENT_DRIVER_CONNECTED:
		// register on supplicant reports
		status = wmx_RegisterEventReportCB(&NDnSAgent_SupEventReport);
		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Registeration on supplicant reports skipped. Already registered",eEvent);
		}
		
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "----L5_EVENT_DRIVER_CONNECTED : Trying  wmx_GetSystemState...--------");
		
		status = wmx_GetSystemState( &systemStateUpdate.SystemState,
									 &systemStateUpdate.ConnectProgress,
									 &systemStateUpdate.rfSwitchesStatus );
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "------L5_EVENT_DRIVER_CONNECTED : wmx_GetSystemState systemStateUpdate.SystemState = [%d]------", systemStateUpdate.SystemState);
		if( WMX_ST_OK == status )
		{		
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "-----L5_EVENT_DRIVER_CONNECTED : wmx_GetSystemState returned WMX_ST_OK and now LinkIsUp---- ");
			// set the rest of the fields of the system state update struct
			//systemStateUpdate.linkStatus = 0;
			systemStateUpdate.MediaStatus = LinkUp;
			systemStateUpdate.ReportStateReason = StateReasonNormal;		

			if (systemStateUpdate.SystemState == Ready)
			{
				L4S_Reset(TRUE);
			}
			L4Pub_SetSystemStateUpdate(&systemStateUpdate);
		}
		//}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "--------L5_EVENT_DRIVER_CONNECTED : wmx_GetSystemState returned != WMX_ST_OK and now systemStateUpdate.SystemState = UnInitialized -------");
			systemStateUpdate.SystemState = UnInitialized;
		}
		// set the correct state of the controller and trigger actions if needed
		OSAL_reset_event(g_ndnsContext.hScanStartedEvent);
		////the TRUE value in the last argument ensures that even if we got a valid reason for Config state from
		//// the ACT and then we got system state Config again by the GetSystemState call - it won't be processed twice.
		//g_ndnsContext.isDriverEventUp = TRUE;
		status = L4C_SetControllerMode(systemStateUpdate.SystemState, TRUE);
		//status = L4C_SetControllerModeEx(&systemStateUpdate, TRUE);
	/*	if (status != WMX_ST_OK)*/

		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error updating state L4C_SetControllerModeEx, status=%d", status);
		}
	    break;
	default:
	    break;
	}	

	
}

EXTERN_C EXPORT void NDnSAgent_Finalize()
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnS shutdown started");	
	L4S_Finalize();

	// can be called even if wmxSup_InitAgent() failed or wasn't called
	wmxSup_FinalizeAgent(); 
	// can be called even if wmxMsc_InitAgent() failed
	wmxMsc_FinalizeAgent();
	// can be called even if wmxNds_InitAgent() failed
	wmxNds_FinalizeAgent();

	if( ( nds_pFuncs != NULL ) && ( nds_l5ConnID != NULL ) )
	{
		nds_pFuncs->pfnDisconnect( nds_l5ConnID );
	}

	nds_l5ConnID = NULL;
	nds_pFuncs = NULL;

	// can be called even if NDnSAgent_InitializeInternalResources failed
	NDnSAgent_FinalizeInternalResources();
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnS shutdown completed successfully");
}

EXTERN_C EXPORT BOOL NDnSAgent_Stop()
{
	char path[MAX_REGISTRY_ANSWER];

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnS is stopping");
	UnRegisterCallbacksOnWrapper();	
	EmptyIndicatorsList(&g_ndnsContext.indicatorSubscribersList);

	// Save provisioning data and internal state to file
	if (RunWithDSim == TRUE)
	{
		OSAL_BuildFullPath(NDNS_DSIM_ENC_CONFIG_FILE, path, MAX_REGISTRY_ANSWER);			
	}
	else
	{
		OSAL_BuildFullPath(WiMAX_ENC_DB, path, MAX_REGISTRY_ANSWER);			
	}

	if (restoreDBSuccess)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "call L4db_SaveToFile from NDnSAgent_Stop");
		if(WMX_ST_OK != L4db_SaveToFile(path))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnS failed to save into the DB file");
		}
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnS stopped");

	return TRUE;
}

EXTERN_C EXPORT BOOL NDnSAgent_Start()
{
	BOOL initSt = TRUE;
	UINT32 res;
	wmx_Status_t status;
	wmx_SystemStateUpdate systemStateUpdate;
	wmx_CoexistenceMode_t coexMode=WMX_MODE_XOR;
	UINT32 msgLength = sizeof(wmx_CoexistenceMode_t);
	UINT32 answerVal = 15;
	UINT32 rawStateReason = 0;

	OSAL_ZeroMemory(&systemStateUpdate, sizeof(systemStateUpdate));
	status = RegisterCallbacksOnWrapper();
	if ( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Callback Registration Failed!");
		initSt = FALSE;
		goto Finalize;
	}

	//setting coexistence mode
	status = GetCoexistenceMode(&coexMode, &msgLength);
	if (status == WMX_ST_FAIL)
	{
		coexMode = WMX_MODE_XOR;
		msgLength = sizeof(wmx_CoexistenceMode_t);
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_Start User call set to TRUE");
	UserCall = TRUE;
	SetCoexistanceMode(&coexMode, msgLength);
	
	if (WMX_MODE_CM == coexMode)
	{
		

		res= OSAL_ConfigController_GetNumValue(OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COEXISTING_TIMEOUT, &answerVal);
		if (!res || answerVal)
		{
			OSAL_create_thread( NDnSAgent_CoexHandlingThreadFunc, NULL, &act_thread_coexHandler );			
		}
	}

	// in case the ACT received a system state Config while the ND&S agent was down - get it and process it
	if (Act_GetConfigReason(&rawStateReason))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnS init - got config state reason. Processing reason");
		wmxNds_DriverReportStateReasonToReportStateReason(&systemStateUpdate.ReportStateReason, rawStateReason);
		systemStateUpdate.SystemState = Config;

		L4Pub_SetSystemStateUpdate(&systemStateUpdate);
		// send to the L4 Controller for processing
		status = L4C_SetControllerModeEx(&systemStateUpdate, TRUE);
		OSAL_ZeroMemory(&systemStateUpdate, sizeof(systemStateUpdate));	
	}

	// update internal data
	//status = wmx_GetSystemState( &systemStateUpdate.SystemState,
	//							 &systemStateUpdate.ConnectProgress,
	//							 &systemStateUpdate.rfSwitchesStatus );
	//if( WMX_ST_OK == status )
	//{		
	//	// set the rest of the fields of the system state update struct
	//	//systemStateUpdate.linkStatus = 0;
	//	systemStateUpdate.MediaStatus = LinkUp;
	//	systemStateUpdate.ReportStateReason = StateReasonNormal;		

	//	L4Pub_SetSystemStateUpdate(&systemStateUpdate);
	//}
	//else
	//{
	//systemStateUpdate.SystemState = UnInitialized;
	//systemStateUpdate.rfSwitchesStatus.swRfStatus = Off;
	//systemStateUpdate.rfSwitchesStatus.hwRfStatus = Off;
	////}

	//memset(systemStateUpdate.linkStatus.bsId, 0xFF, sizeof(wmx_BSid_t));

	//// set the correct state of the controller and trigger actions if needed
	//ResetEvent(g_ndnsContext.hScanStartedEvent);
	//// the TRUE value in the last argument ensures that even if we got a valid reason for Config state from
	//// the ACT and then we got system state Config again by the GetSystemState call - it won't be processed twice.
	//status = L4C_SetControllerModeEx(&systemStateUpdate, TRUE);
	//if (status != WMX_ST_OK)
	//{
	//	initSt = FALSE;
	//	goto Finalize;
	//}

Finalize:
	return initSt;
}

EXTERN_C EXPORT APPSRV_INIT_ST NDnSAgent_Initialize(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn)
{	
	UINT32 res;
	L5_RESULT l5status;
	wmx_Status_t status;
	char readFromNVM[MAX_ANSWER_SIZE];

	APPSRV_INIT_ST initSt = INIT_SUCCESS;
	nds_pFuncs = L5disp;
	pUtils = UtilFn;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnS Agent - initialization started");
	InitParameters();

	status = NDnSAgent_InitializeInternalResources();
	if ( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Internal Initialize Failed!");
		if( WMX_ST_CONFIG_ERROR == status )
		{
			initSt = INIT_CONFIG_FAIL;
		}
		else
		{		
			initSt = INIT_FAIL;
		}
		goto Finalize;
	}

	status = L4S_Init();
	if ( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "L4Scanner initialization error!");
		initSt =  INIT_FAIL;
		goto Finalize;
	}

	// Connect L5 and through it to AppSrv. Gain L5ConnID.
	l5status = nds_pFuncs->pfnConnectEx(L5_TARGET_NDNS, &NDnSAgent_MessagesHandler, &NDnSAgent_EventHandler, NULL, THREAD_ID_DEFAULT, &nds_l5ConnID	);
	if (L5_RESULT_OK != l5status)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Connect to L5 Failed!");
		initSt =  INIT_FAIL;
		goto Finalize;
	}

	// Init Wrapper and Register Callbacks
	status = wmxNds_InitAgent();
	if ( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "NDnS Wrapper Init Failed!");
		initSt =  INIT_FAIL;
		goto Finalize;
	}

	// Init Wrapper and Register Callbacks
	status = wmxMsc_InitAgent();
	if ( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Misc Wrapper Init Failed!");
		initSt =  INIT_FAIL;
		goto Finalize;
	}

	res = L4Configurations_getConnectTime(&connectTime);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "ConnectTime = %d", connectTime);

	// Init Supplicant Wrapper
	status = wmxSup_InitAgent();
	if ( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Supplicant Wrapper Init Failed!");
		initSt =  INIT_FAIL;
		goto Finalize;
	}
	g_ndnsContext.isSupplicantStarted = TRUE;

	// If registry key is set to true update L4db from NVM 
	L4Configurations_getAPDOReadFromNvm(readFromNVM);

	if (0 == OSAL_stricmp(DEFAULT_TRUE_LOWER, readFromNVM))
	{		
		L4db_UpdateFromNVM();  
	}		

	// Update the package version in L4DB
	L4db_UpdatePackageVersion();
	
Finalize:
	if (initSt == INIT_SUCCESS)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnS Agent initialization completed successfully");
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnS Agent initialization failed");
	}
	return initSt;
}


// The function initiates all the internal parameters
void InitParameters()
{
	nds_l5ConnID = NULL;
	//nds_pFuncs = NULL;
	g_ndnsContext.indicatorSubscribersList = NULL;
	g_ndnsContext.isScanParametersSet = FALSE;	
	g_ndnsContext.isSupplicantStarted = FALSE;
	g_ndnsContext.disconnectStarted = FALSE;
	g_ndnsContext.disconnectCompletedEvent = NULL;
	g_ndnsContext.hScanStartedEvent = NULL;
	g_ndnsContext.connectStarted = FALSE;
	g_ndnsContext.processStarted = FALSE;
	g_ndnsContext.connectCompletedEvent = NULL;
	g_ndnsContext.startManualScanCompletedEvent = NULL;
	g_ndnsContext.dualFlushOpEvent = NULL;
	g_ndnsContext.systemState = UnInitialized;
	g_ndnsContext.scanStatus = WMX_ST_OK;
	g_ndnsContext.isScanProcessingRequired = FALSE;
	channelInfos = NULL;	
	bsCriteriaList = NULL;
	Ndns_SetConnectingNSPTemp((wmx_NSPid_t)L4DB_INVALID_INDEX);
	l4db_SetNapidEmpty(g_ndnsContext.tempConnectingNapId);
	connectTime = 0;
	provisioningStarted = FALSE;
	lastConnectedState = TRUE;
	L4Pub_Reset();
	g_ndnsContext.isResumeScan = FALSE;
	g_ndnsContext.linkLossType = LinkLossType_Short;
	g_ndnsContext.isSingleManualScan = FALSE;
	g_ndnsContext.currentScanType = SCAN_TYPE_PREFERRED;
	g_ndnsContext.scheduledTask = Task_StartScan;
	g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_PREFERRED;
	g_ndnsContext.scheduledTaskData.scanInfo.isInternal = TRUE;
	g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize = 0;
	g_ndnsContext.eapContext.numEapRetries = 0;
	g_ndnsContext.eapContext.isStarted = FALSE;
}