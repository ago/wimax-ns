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
#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Nds_Utils.h"

#include "WrappersUtils.h"
#include "L4ConfigurationManager.h"

#include "TraceModule.h"



void wmxNds_Ctrl_FinalizeSynchEvents( )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_Ctrl_FinalizeSynchEvents(IN)");
	if (g_userScanCompletedEvent != NULL)
	{
		OSAL_delete_event(g_userScanCompletedEvent);
		g_userScanCompletedEvent = NULL;
	}

	if (g_userConnectCompletedEvent != NULL)
	{
		OSAL_delete_event(g_userConnectCompletedEvent);
		g_userConnectCompletedEvent = NULL;
	}
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_Ctrl_FinalizeSynchEvents(OUT)");
}

wmx_Status_t wmxNds_Ctrl_InitializeSynchEvents()
{
	if( g_userScanCompletedEvent != NULL )
	{
		wmxNds_Ctrl_FinalizeSynchEvents();
		return WMX_ST_PIPE_FAILURE;
	}

	if ( 0 != OSAL_create_event( &g_userScanCompletedEvent, FALSE, FALSE, NULL ) )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "Error initializing User Scan Completed Event");
		wmxNds_Ctrl_FinalizeSynchEvents();
		return WMX_ST_FAIL;
	}

	if ( 0 != OSAL_create_event( &g_userConnectCompletedEvent, FALSE, FALSE, NULL ) )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "Error initializing User Connect Completed Event");
		wmxNds_Ctrl_FinalizeSynchEvents();
		return WMX_ST_FAIL;
	}

	return WMX_ST_OK;
}



void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxNds_Finalize()
{
    TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_Finalize(IN)");
    
	if ( LAST_INIT == OSAL_atomic_decrement(&nds_numOfInits) )
	{
		//wmxNds_UnregisterOnDriverScanReport();
		//wmxNds_UnregisterOnDriverStateReport();
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_Finalize - finilizing last instance");
		if (NULL != nds_wrapper_pFuncs)
		{
			wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
			wmx_UnregisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
		}

		wmxNds_UnregisterOnAgentScanCompletedInd();
		wmxNds_UnregisterOnAgentConnectCompletedInd();
		wmxNds_Ctrl_FinalizeSynchEvents();
		wmxNds_FinalizeL5();
		OSAL_delete_critical_section( &g_plasticRWLock );
		OSAL_delete_critical_section( &g_silverRWLock );		
	}
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_Finalize(OUT)");

	OSAL_atomic_compareExchange(&nds_numOfInits, LAST_INIT, LAST_INIT - 1);
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxNds_Init()
{
	wmx_Status_t status;
	wmx_SystemState_t currentSystemState;
	wmx_ConnectProgressInfo_t connectProgressInfo;
	wmx_RfSwitchesStatus_t rfSwitchesStatus;
	BOOL res;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_Init(IN). nds_numOfInits=%d",nds_numOfInits);

	if ( FIRST_REGISTERED == OSAL_atomic_increment(&nds_numOfInits) )
	{
		OSAL_init_critical_section( &g_plasticRWLock );
		OSAL_init_critical_section( &g_silverRWLock );

		status = wmxNds_InitL5();
		if ( WMX_ST_OK != status )
		{
			wmxNds_Finalize();
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_Init - wmxNds_InitL5 failed. status=%d",status);
			return status;
		}

		status = wmxNds_Ctrl_InitializeSynchEvents();
		if ( WMX_ST_OK != status )
		{
			wmxNds_Finalize();
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_Init - wmxNds_Ctrl_InitializeSynchEvents. status=%d",status);
			return status;
		}

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on driver state report");
		status = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "failed to register on driver state report");
			wmxNds_Finalize();
			return status;
		}
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on driver scan report");
		if (NULL != nds_wrapper_pFuncs)
		{
			status = wmx_RegisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
		}
		else
		{
			status = WMX_ST_FAIL;
		}

		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "failed to register on driver scan report");
			wmxNds_Finalize();
			return status;
		}
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on agent scan completed indication");
		status = wmxNds_RegisterOnAgentScanCompletedInd();
		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "failed to register on agent scan completed indication");
			wmxNds_Finalize();
			return status;
		}
		status = wmxNds_RegisterOnAgentConnectCompletedInd();
		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "failed to register on agent connect completed indication");
			wmxNds_Finalize();
			return status;
		}

		// update internal data
		status = wmx_GetSystemState( &currentSystemState, &connectProgressInfo, &rfSwitchesStatus );
		if( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "failed to register on agent connect completed indication");
			wmxNds_Finalize();
			return status;
		}
		
		SetCurrentSystemState(currentSystemState);					

		res = L4Configurations_getConnectTime(&connectTime);
	
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "ConnectTime = %d", connectTime);
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmxNds_Init(OUT). ");

	return WMX_ST_OK;
}

