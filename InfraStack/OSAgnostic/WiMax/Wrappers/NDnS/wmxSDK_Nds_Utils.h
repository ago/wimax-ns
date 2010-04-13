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
#ifndef _WMX_SDK_NDS_UTILS_H
#define _WMX_SDK_NDS_UTILS_H


#include "L4BufMan_L3L4Structs_Desc.h"
#include "L5OpCodes.h"		// @@@ : JSS : Fixed case sensitivity in file name

wmx_Status_t SendNdsMsg( 
	UINT32 opcode, NDNS_AGENT_L5_OPCODE ndnsOpcode,
	UINT32 requestLength, UINT8 *request, 
	UINT32 *responseLength, UINT8 *response );

// Declarations
DOUBLE  wmxNds_GetConnectionDuration();
void wmxNds_DriverRfStatusToRfStatus(wmx_pRfStatus_t rfStatus, UINT32 driverRfStatus);
void wmxNds_ConnectProgressInfoTranslation(wmx_pConnectProgressInfo_t connectProgressInfo, UINT32 driverProgressInfo);
void wmxNds_DriverSystemStateToSystemState(wmx_pSystemState_t systemState, UINT32 driverState);
void wmxNds_DriverReportStateReasonToReportStateReason(wmx_pStateReason_t stateReason, UINT32 driverStateReason);
void wmxNds_DriverMediaStatusToMediaStatus(wmx_pMediaStatus_t mediaStatus, UINT32 driverMediaStatus);
// TODO: Oran - remove
//wmx_Status_t wmxNds_CalcConnectStatus( wmx_SystemState_t systemState, ReportState_type stateReport, wmx_pConnectStatus_t connectStatus );
wmx_Status_t wmxNds_CalcConnectStatus( wmx_pSystemStateUpdate systemStateUpdate, wmx_pConnectStatus_t connectStatus );
wmx_ScanStatus_t wmxNds_CalcScanStatus( E_ScanStatus driverScanStatus, UINT32 numOfScanResults );
void wmxNds_SystemStateToConnectionState(wmx_pConnectionState_t connectionState, wmx_SystemState_t systemState);

// register driver reports
/*wmx_Status_t wmxNds_RegisterOnDriverStateReport();
wmx_Status_t wmxNds_UnregisterOnDriverStateReport();
wmx_Status_t wmxNds_RegisterOnDriverScanReport();
wmx_Status_t wmxNds_UnregisterOnDriverScanReport();
wmx_Status_t wmxNds_RegisterOnDriverBsInfoReport();
wmx_Status_t wmxNds_UnregisterOnDriverBsInfoReport();
wmx_Status_t wmxNds_RegisterOnDriverSIIReport();
wmx_Status_t wmxNds_UnregisterOnDriverSIIReport();*/


// register agent indications
wmx_Status_t wmxNds_RegisterOnAgentMediaStatusInd();
wmx_Status_t wmxNds_UnregisterOnAgentMediaStatusInd();
wmx_Status_t wmxNds_RegisterOnAgentCurrentPreferredNSPInd();
wmx_Status_t wmxNds_UnregisterOnAgentCurrentPreferredNSPInd();
wmx_Status_t wmxNds_RegisterOnAgentScanUpdateInd();
wmx_Status_t wmxNds_UnregisterOnAgentScanUpdateInd();
wmx_Status_t wmxNds_RegisterOnAgentScanCompletedInd();
wmx_Status_t wmxNds_UnregisterOnAgentScanCompletedInd();
wmx_Status_t wmxNds_RegisterOnAgentConnectCompletedInd();
wmx_Status_t wmxNds_UnregisterOnAgentConnectCompletedInd();
wmx_Status_t wmxNds_RegisterOnAgentDeviceStatusInd();
wmx_Status_t wmxNds_UnregisterOnAgentDeviceStatusInd();
wmx_Status_t wmxNds_RegisterOnAgentSystemStateUpdateInd();
wmx_Status_t wmxNds_UnregisterOnAgentSystemStateUpdateInd();
wmx_Status_t wmxNds_RegisterOnUserAPDOStatusUpdateInd();
wmx_Status_t wmxNds_UnregisterOnUserAPDOStatusUpdateInd();
wmx_Status_t wmxNds_RegisterOnProvisioningOperationInd();
wmx_Status_t wmxNds_UnregisterOnProvisioningOperationInd();
wmx_Status_t wmxNds_RegisterOnPackageUpdateInd();
wmx_Status_t wmxNds_RegisterOnPackageDownloadProgressCBInd();
wmx_Status_t wmxNds_UnregisterOnPackageUpdateInd();
wmx_Status_t wmxNds_UnregisterOnPackageDownloadProgressCBInd();
wmx_Status_t wmxNds_UnregisterOnAgentCoexUpdateInd();
wmx_Status_t wmxNds_RegisterOnAgentConnectionModeUpdateInd();
wmx_Status_t wmxNds_UnregisterOnAgentConnectionModeUpdateInd();
wmx_Status_t wmxNds_RegisterOnAgentFastReconnectStatusUpdateInd();
wmx_Status_t wmxNds_UnregisterOnAgentFastReconnectStatusUpdateInd();
wmx_Status_t wmxNds_RegisterOnAgentRoamingModeUpdateInd();
wmx_Status_t wmxNds_UnregisterOnAgentRoamingModeUpdateInd();
wmx_Status_t wmxNds_RegisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd();
wmx_Status_t wmxNds_UnregisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd();
wmx_Status_t wmxNds_RegisterOnAgentRfTakenInd();
wmx_Status_t wmxNds_UnregisterOnAgentRfTakenInd();
wmx_Status_t wmxNds_RegisterOnAgentPNMNotification();
wmx_Status_t wmxNds_UnregisterOnAgentPNMNotification();

#endif // _WMX_SDK_NDS_UTILS_H