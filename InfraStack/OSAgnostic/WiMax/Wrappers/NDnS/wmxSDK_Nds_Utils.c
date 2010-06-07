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

#include "L5OpCodes.h"		// @@@ : JSS - case name
#include "WrappersCommon.h"

#include "WrappersUtils.h"

#include "L4BufMan_L3L4Structs_Desc.h"

#include "TraceModule.h"

void wmxNds_ConnectProgressInfoTranslation(wmx_pConnectProgressInfo_t connectProgressInfo, UINT32 driverProgressInfo)
{
	switch (driverProgressInfo)
	{		
		case E_CONNECT_PROGRESS_RANGING:
			*connectProgressInfo = Ranging;
			break;	
		case E_CONNECT_PROGRESS_SBC:
			*connectProgressInfo = SBC;
			break;	
		case E_CONNECT_PROGRESS_EAP_AUTH:
			*connectProgressInfo = EAPAuthentication;
			break;	
		case E_CONNECT_PROGRESS_3WAY_HANDSHAKE:
			*connectProgressInfo = ThreeWayHandshake;
			break;	
		case E_CONNECT_PROGRESS_REGISTRATION:
			*connectProgressInfo = Registration;
			break;	
		
		default:
			*connectProgressInfo = NotApplicable;
			break;
	}
}

void wmxNds_DriverRfStatusToRfStatus(wmx_pRfStatus_t rfStatus, UINT32 driverRfStatus)
{
	switch (driverRfStatus)
	{
		case E_SW_RF_STATUS_OFF:
			*rfStatus = Off;
			break;
		case E_SW_RF_STATUS_ON:
			*rfStatus = On;
			break;
		
		default:
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_DriverRfStatusToRfStatus Unknown Status %d", driverRfStatus);
			break;
	}
}

void wmxNds_DriverMediaStatusToMediaStatus(wmx_pMediaStatus_t mediaStatus, UINT32 driverMediaStatus)
{
	switch (driverMediaStatus)
	{
		case E_MEDIA_STATUS_LINK_UP:
			*mediaStatus = LinkUp;
			break;
		case E_MEDIA_STATUS_LINK_DOWN:
			*mediaStatus = LinkDown;
			break;
		
		default:
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_DriverMediaStatusToMediaStatus Unknown Status %d", driverMediaStatus);
			break;
	}
}

//
void wmxNds_DriverReportStateReasonToReportStateReason(wmx_pStateReason_t stateReason, UINT32 driverStateReason)
{
	switch (driverStateReason)
	{
		case E_REPORT_STATE_REASON_NORMAL:
			*stateReason = StateReasonNormal;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_TO_NW:
			*stateReason = StateReasonFailToConnectToNW;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_RANGING:
			*stateReason = StateReasonFailToConnectRanging;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_SBC:
			*stateReason = StateReasonFailToConnectSBC;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_EAP_AUTH:
			*stateReason = StateReasonFailToConnectEAPAuth;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_3WAY_HANDSHAKE:
			*stateReason = StateReasonFailToConnect3WayHandshake;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_REGISTRATION:
			*stateReason = StateReasonFailToConnectREG;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_DATA_PATH:
			*stateReason = StateReasonFailToConnectDatapath;
			break;
		case E_REPORT_STATE_REASON_FAIL_TO_CONNECT_COEX_NO_RF:
			*stateReason = StateReasonFailToConnectCoexNoRF;
			break;
		case E_REPORT_STATE_REASON_DISCONNECT_DREG:
			*stateReason = StateReasonDisconnectDreg;
			break;
		case E_REPORT_STATE_REASON_DISCONNECT_ABORT:
			*stateReason = StateReasonDisconnectAbort;
			break;
		case E_REPORT_STATE_REASON_DISCONNECT_RESET:
			*stateReason = StateReasonDisconnectReset;
			break;
		case E_REPORT_STATE_REASON_DISCONNECT_DROP:
			*stateReason = StateReasonDisconnectDrop;
			break;
		case E_REPORT_STATE_REASON_SPLOCK_VALIDATION_FAILED:
			*stateReason = StateReasonSplockValidationFailed;
			break;
		case E_REPORT_STATE_REASON_DISCONNECT_SECURITY:
			*stateReason = StateReasonDisconnectSecurity;
			break;
		case E_REPORT_STATE_REASON_RESET_HW_WDT:
			*stateReason = StateReasonResetHwWdt;
			break;
		case E_REPORT_STATE_REASON_RESET_SW_WDT:
			*stateReason = StateReasonResetSwWdt;
			break;
		case E_REPORT_STATE_REASON_RESET_ASSERT:
			*stateReason = StateReasonResetAssert;
			break;
		case E_REPORT_STATE_REASON_RESET_THERMAL:
			*stateReason = StateReasonResetThermal;
			break;
		case E_REPORT_STATE_REASON_RESET_RF_KILL:
			*stateReason = StateReasonResetRfKill;
			break;
		case E_REPORT_STATE_REASON_RESET_CO_EXISTENCE:
			*stateReason = StateReasonResetCoExistence;
			break;
		case E_REPORT_STATE_REASON_RESET_HOST:
			*stateReason = StateReasonResetHost;
			break;		
		case E_REPORT_STATE_REASON_DISCONNECT_PROTOCOL_ERROR:
			*stateReason = StateReasonDisconnectProtocolError;
			break;
		case E_REPORT_STATE_REASON_FW_REQUEST_DEV_RESET:
			*stateReason = StateReasonFWRequestDevReset;
			break;
		case E_REPORT_STATE_REASON_FW_REQUEST_FUNC_RESET:
			*stateReason = StateReasonFWRequestFuncReset;
			break;
		default:
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_DriverReportStateReasonToReportStateReason Unknown State %d", driverStateReason);
			break;
	}
}

//
void wmxNds_DriverSystemStateToSystemState(wmx_pSystemState_t systemState, UINT32 driverState)
{
	switch (driverState)
	{
		case E_SYSTEM_STATE_PRODUCTION:
			*systemState = UnInitialized;
			break;
		case E_SYSTEM_STATE_CONFIG:
			*systemState = Config;
			break;
		case E_SYSTEM_STATE_UNINITIALIZED:
			*systemState = UnInitialized;
			break;
		case E_SYSTEM_STATE_INIT:
			*systemState = Initialized;
			break;
		case E_SYSTEM_STATE_READY:
			*systemState = Ready;
			break;
		case E_SYSTEM_STATE_CONNECTING:
			*systemState = Connecting;
			break;
		case E_SYSTEM_STATE_DISCONNECTING:
			*systemState = Disconnecting;
			break;
		case E_SYSTEM_STATE_SCAN:
			*systemState = Scan;
			break;
		case E_SYSTEM_STATE_WIMAX_CONNECTED:
			*systemState = WimaxConnected;
			break;
		case E_SYSTEM_STATE_DATA_PATH_CONNECTED:
			*systemState = DataPathConnected;
			break;
		case E_SYSTEM_STATE_IDLE:
			*systemState = Idle;
			break;
		case E_SYSTEM_STATE_RF_OFF:
			*systemState = RfOff;
			break;
		case E_SYSTEM_STATE_RF_SHUTDOWN:
			*systemState = RfShutDown;
			break;
		
		default:
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_DriverSystemStateToSystemState Unknown State %d", driverState);
			break;
	}
}

void wmxNds_SystemStateToConnectionState(wmx_pConnectionState_t connectionState, wmx_SystemState_t systemState)
{				
	switch (systemState)
	{
		case Production:
		case Config:
		case UnInitialized:
		case Initialized:
		case RfOff:
		case RfShutDown:
			*connectionState = ConnectionStateRfOff;
			break;

		case Ready:
		//case Standby:
		case Connecting:
		case WimaxConnected:		
		//case SleepActive:
		case Disconnecting:
		case Scan:
			*connectionState = Disconnected;
			break;

		/*case OOZ:
			*connectionState = OutOfZone;
			break;*/

		case DataPathConnected:
		case Idle:
			*connectionState = Connected;
			break;

		default:
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_SystemStateToConnectionState Unknown State %d", systemState);
			break;
	}
}

wmx_Status_t wmxNds_CalcConnectStatus( wmx_pSystemStateUpdate systemStateUpdate, wmx_pConnectStatus_t connectStatus )
{
	if( (systemStateUpdate->SystemState == DataPathConnected ) || (systemStateUpdate->SystemState == Idle ))
	{
		*connectStatus = ConnectSuccessful;
		return WMX_ST_OK;
	}

	if( systemStateUpdate->ReportStateReason == 0 ) // missing state reason
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_WARNING, "state report doesn't contain state reason !!");		
		*connectStatus = ConnectFailed;

		return WMX_ST_DATA_UNAVAILABLE;
	}

	if(systemStateUpdate->ReportStateReason != StateReasonNormal) // TODO - XXX - change to new ConnectStatus
	{
		*connectStatus = ConnectFailed;
		return WMX_ST_DATA_UNAVAILABLE;
	}

	*connectStatus = ConnectCancelled;

	return WMX_ST_OK;
}

// TODO: Oran - remove
/*wmx_Status_t wmxNds_CalcConnectStatus( wmx_SystemState_t systemState, ReportState_type stateReport, wmx_pConnectStatus_t connectStatus )
{
	if( systemState == DataPathConnected )
	{
		*connectStatus = ConnectSuccessful;
		return WMX_ST_OK;
	}

	if( stateReport.ReportStateReason.Type != L3L4_TLV_TYPE_REPORT_STATE_REASON )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_WARNING, "state report doesn't report state reason !!");		
		*connectStatus = ConnectFailed;

		return WMX_ST_DATA_UNAVAILABLE;
	}

	if(stateReport.ReportStateReason.value != E_REPORT_STATE_REASON_NORMAL) // TODO - XXX - change to new ConnectStatus
	{
		*connectStatus = ConnectFailed;
		return WMX_ST_DATA_UNAVAILABLE;
	}

	*connectStatus = ConnectCancelled;

	return WMX_ST_OK;
}*/

wmx_ScanStatus_t wmxNds_CalcScanStatus( E_ScanStatus driverScanStatus, UINT32 numOfScanResults )
{
	if( driverScanStatus == E_SCAN_STATUS_FAILURE )
	{
		return ScanFailed;
	}

	if( driverScanStatus == E_SCAN_STATUS_STOPPED )
	{
		return ScanStopped;
	}

	if ( driverScanStatus == E_SCAN_STATUS_COEX_STOPPED )
	{
		return ScanStopped; // TODO: Oran - check if we should have a CoexScan stop
	}

	if( numOfScanResults == 0 )
	{
		return ScanExhausted;
	}

	return ScanSuccessful;
}

// register driver reports
/*wmx_Status_t wmxNds_RegisterOnDriverStateReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnDriverStateReport (IN)");
	return wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnDriverStateReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnDriverStateReport (IN)");
	return wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_RegisterOnDriverScanReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnDriverScanReport (IN)");
	return wmx_RegisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnDriverScanReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnDriverScanReport (IN)");
	return wmx_UnregisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

/////////////// Oran - new

wmx_Status_t wmxNds_RegisterOnDriverBsInfoReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnDriverBsInfoReport (IN)");
	return wmx_RegisterOnDriverReport( &g_numOfBsInfoReportRegs, L3_L4_OPCODE_REPORT_BS_INFO, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnDriverBsInfoReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnDriverBsInfoReport (IN)");
	return wmx_UnregisterOnDriverReport( &g_numOfBsInfoReportRegs, L3_L4_OPCODE_REPORT_BS_INFO, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_RegisterOnDriverSIIReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnDriverSIIReport (IN)");
	return wmx_RegisterOnDriverReport( &g_numOfSIIReportRegs, L3_L4_OPCODE_REPORT_SII, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnDriverSIIReport()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnDriverSIIReport (IN)");
	return wmx_UnregisterOnDriverReport( &g_numOfSIIReportRegs, L3_L4_OPCODE_REPORT_SII, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}*/
////////////////



// register agent indications
wmx_Status_t wmxNds_RegisterOnAgentScanUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentScanUpdateInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfScanUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_SCAN_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentScanUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentScanUpdateInd (IN)");
	
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfScanUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_SCAN_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentCurrentPreferredNSPInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentCurrentPreferredNSPInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfCurrentPreferredIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentCurrentPreferredNSPInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentCurrentPreferredNSPInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfCurrentPreferredIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentMediaStatusInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentMediaStatusInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfMediaStatusIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_MEDIA_STATUS, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentMediaStatusInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentMediaStatusInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfMediaStatusIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_MEDIA_STATUS, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentScanCompletedInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentScanCompletedInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfScanCompletedIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_SCAN_COMPLETED, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentScanCompletedInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentScanCompletedInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfScanCompletedIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_SCAN_COMPLETED, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_UnregisterOnAgentConnectionModeUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentConnectionModeUpdateInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_connectionModeUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_UnregisterOnAgentRoamingModeUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentRoamingModeUpdateInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_connectionModeUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_ROAMING_MODE_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_UnregisterOnAgentFastReconnectStatusUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentFastReconnectStatusUpdateInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_fastReconnectStatusUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_UnregisterOnAgentCoexUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentCoexUpdateInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_coexistenceUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_COEX_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentConnectCompletedInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentConnectCompletedInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_RegisterOnAgentConnectCompletedInd - NULL == nds_wrapper_pFuncs");
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfConnectCompletedIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_CONNECT_COMPLETED, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentConnectCompletedInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentConnectCompletedInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfConnectCompletedIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_CONNECT_COMPLETED, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentDeviceStatusInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentDeviceStatusInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfDeviceStatusIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_RegisterOnAgentConnectionModeUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentConnectionModeUpdateInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_connectionModeUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_RegisterOnAgentRoamingModeUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentRoamingModeUpdateInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_roamingModeUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_ROAMING_MODE_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_RegisterOnAgentFastReconnectStatusUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentFastReconnectStatusUpdateInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_fastReconnectStatusUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}
wmx_Status_t wmxNds_UnregisterOnAgentDeviceStatusInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentDeviceStatusInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfDeviceStatusIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_UnregisterOnAgentDeviceStatusInd (OUT) - nds_wrapper_pFuncs=NULL");
	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentSystemStateUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentSystemStateUpdateInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfSystemStateUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentSystemStateUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentSystemStateUpdateInd (IN)");
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfSystemStateUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnProvisioningOperationInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnIndProvisioningOperationInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfProvisioningOperationIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_PROVISIONING_OPERATION, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnProvisioningOperationInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnIndProvisioningOperationInd (IN)");
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfProvisioningOperationIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_PROVISIONING_OPERATION, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnPackageUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnPackageUpdateInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfPackageUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_PACKAGE_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnPackageUpdateInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnPackageUpdateInd (IN)");
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfPackageUpdateIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_PACKAGE_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}


wmx_Status_t wmxNds_RegisterOnAgentPNMNotification()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentPNMNotification (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}
	return wmx_RegisterOnAgentIndication( 
			 &g_PNMTakenIndRegs, 
			 L5_TARGET_NDNS, 
			 NDNS_OPCODE_REGISTER_INDICATION, 
			 NDNS_OPCODE_IND_PNM_NOTIFICATION, 
			 *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}
wmx_Status_t wmxNds_UnregisterOnAgentPNMNotification()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_UnregisterOnAgentPNMNotification (IN)");
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_PNMTakenIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_PNM_NOTIFICATION, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}
	return WMX_ST_FAIL;
}

wmx_Status_t wmxNds_RegisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_connectedAsCurrentPreferredCapabilityStatusIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd (IN)");
	if( nds_wrapper_pFuncs != NULL )
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_connectedAsCurrentPreferredCapabilityStatusIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}


wmx_Status_t wmxNds_RegisterOnAgentRfTakenInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnAgentRfTakenInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_rfTakenIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_RF_TAKEN, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnAgentRfTakenInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnAgentRfTakenInd (IN)");
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_rfTakenIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_RF_TAKEN, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}
wmx_Status_t wmxNds_RegisterOnPackageDownloadProgressCBInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnPackageDownloadProgressCBInd (IN)");
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_FAIL;
	}

	return wmx_RegisterOnAgentIndication( 
		&g_numOfPackageDownloadProgressIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
}

wmx_Status_t wmxNds_UnregisterOnPackageDownloadProgressCBInd()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnPackageDownloadProgressCBInd (IN)");
	if(nds_wrapper_pFuncs != NULL)
	{
		return wmx_UnregisterOnAgentIndication( 
			&g_numOfPackageDownloadProgressIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS, 
			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	return WMX_ST_FAIL;
}


//wmx_Status_t wmxNds_RegisterOnUserAPDOStatusUpdateInd()
//{
//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_RegisterOnUserAPDOStatusUpdateInd (IN)");
//	return wmx_RegisterOnAgentIndication( 
//		&g_numOfUserAPDOStatusUpdateIndRegs, 
//		L5_TARGET_NDNS, 
//		NDNS_OPCODE_REGISTER_INDICATION, 
//		NDNS_OPCODE_IND_APDO_STATUS_UPDATE, 
//		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
//}
//
//wmx_Status_t wmxNds_UnregisterOnUserAPDOStatusUpdateInd()
//{
//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_UnregisterOnUserAPDOStatusUpdateInd (IN)");
//	if(nds_wrapper_pFuncs != NULL)
//	{
//		return wmx_UnregisterOnAgentIndication( 
//			&g_numOfUserAPDOStatusUpdateIndRegs, 
//			L5_TARGET_NDNS, 
//			NDNS_OPCODE_UNREGISTER_INDICATION, 
//			NDNS_OPCODE_IND_APDO_STATUS_UPDATE, 
//			*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
//	}
//
//	return WMX_ST_OK;
//}

wmx_Status_t SendNdsMsg( 
	UINT32 opcode, NDNS_AGENT_L5_OPCODE ndnsOpcode,
	UINT32 requestLength, UINT8 *request, 
	UINT32 *responseLength, UINT8 *response )
{
	// results
	L5_RESULT l5Result;
	wmx_Status_t st;

	// Request Fields
	UINT32 messageSize;
	pNDNS_MESSAGE pMessage;

	// Response Fields
	UINT32 responseID;

	if (nds_wrapper_pFuncs == NULL ||
		nds_wrapper_l5ConnID == NULL)
	{
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	// create the request
	messageSize = sizeof(NDNS_MESSAGE) + requestLength;
	pMessage = (pNDNS_MESSAGE)malloc(messageSize);
	if (pMessage == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return WMX_ST_FAIL;
	}

	pMessage->opcode = opcode;
	pMessage->bufferLength = requestLength;
	if (requestLength > 0)
	{
		if( !request)
		{   
			free(pMessage);
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "SendNdsMsg request is NULL");
			return WMX_ST_FAIL;
		}

		OSAL_memcpy_s(pMessage->buf, requestLength, request, requestLength);
	}

	// sent the request
	l5Result = nds_wrapper_pFuncs->pfnSendReceiveMessage( 
		nds_wrapper_l5ConnID, L5_TARGET_NDNS, ndnsOpcode, 
		pMessage, messageSize, &responseID, response, responseLength );

	free(pMessage);

	// check the l5 result
	st = wmx_L5ResultToWMXStatus( l5Result );
	if( st != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "SendNdsMsg: l5 result is %d", l5Result);
		return st;
	}

	// check the status received from the ndns agent
	if( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "SendNdsMsg: ndns response id is %s", wmxGetStatusStr(responseID));
		return (wmx_Status_t)responseID;
	}

	return WMX_ST_OK;
}
