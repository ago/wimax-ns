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

#include "TraceModule.h"



void wmxNds_FinalizeAgent()
{
	if ( LAST_INIT == OSAL_atomic_decrement(&nds_numOfInits) )
	{
		OSAL_delete_critical_section( &g_silverRWLock );		
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on driver scan results");		
		wmx_UnregisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on driver state report");		
		wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
		wmxNds_FinalizeL5();
	}
	
	OSAL_atomic_compareExchange(&nds_numOfInits, LAST_INIT, LAST_INIT - 1);
}

wmx_MediaStatus_t GetMediaStatusFromSystemState(wmx_SystemState_t systemState)
{
	switch(systemState)
	{
		case UnInitialized:
		case Config:
		case Production:
		case RfOff:
		case Ready:
		case Scan:
		case Connecting:
		case WimaxConnected:
		case RfShutDown:
		case UnknownState:
			return LinkDown;
		case DataPathConnected:
		case Idle:
		case Disconnecting:
			return LinkUp;
		default:
			return LinkDown;
	}
}

wmx_Status_t wmxNds_InitAgent()
{
	wmx_Status_t status;
	wmx_SystemState_t currentSystemState;
	wmx_ConnectProgressInfo_t connectProgressInfo;
	wmx_RfSwitchesStatus_t rfSwitchesStatus;

	if ( FIRST_REGISTERED == OSAL_atomic_increment(&nds_numOfInits) )
	{
		memset(SystemStateUpdateCBs, 0, (sizeof(wmx_pSystemStateUpdateCB_t) * SYSTEM_STATE_MAX_CALLBACKS));
		SystemStateUpdateCBs_Count = 0;
	
		OSAL_init_critical_section( &g_silverRWLock );

		status = wmxNds_InitL5();
		if ( WMX_ST_OK != status )
		{
			//wmxNds_FinalizeAgent();
			return status;
		}

		// update internal data
		status = wmx_GetSystemState( &currentSystemState, &connectProgressInfo, &rfSwitchesStatus  );
		if( WMX_ST_OK == status )
		{
			SetCurrentSystemState(currentSystemState);
			SetCurrentMediaStatus(GetMediaStatusFromSystemState(currentSystemState));
		}

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on driver state report");
		status = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
		if ( WMX_ST_OK != status )
		{
			//wmxNds_FinalizeAgent();
			return status;
		}
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on driver scan report");
		status = wmx_RegisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
		if ( WMX_ST_OK != status )
		{
			//wmxNds_FinalizeAgent();
			return status;
		}		
	}

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "ndns wrapper init agent finished");
	return WMX_ST_OK;
}


