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
#ifndef _WMX_SDK_NDS_IND_HANDLER_H
#define _WMX_SDK_NDS_IND_HANDLER_H

#include "L4BufMan_L3L4Structs_Desc.h"


wmx_Status_t wmxNds_StateReportArrived( ReportState_type stateReport );

wmx_Status_t wmxNds_ScanReportArrived( ReportScanResults_type scanReport );

wmx_Status_t wmxNds_AgentScanCompletedArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentConnectCompletedArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentScanUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentSystemStateUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_ApdoProvisioningOperationArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_ApdoStatusUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_ApdoAlertNotificationArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_BsInfoReportArrived(ReportBsInfo_type bsInfoReport);

wmx_Status_t wmxNds_SIIReportArrived(ReportSII_type siiReport);

wmx_Status_t wmxNds_AgentCoexUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentConnectionModeUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentFastReconnectStatusUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentRoamingModeUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_ApdoPackageUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_ApdoPackageDownloadProgressArrived( UINT8 *buf, UINT32 bufSize );
wmx_Status_t wmxNds_AgentDeviceStatusUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_BEKReportArrived(ReportEMSKRelatedKeys_type bekReport);

wmx_Status_t wmxNds_AgentConnectedAsCurrentPreferredCapabilityStatusUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentRfTakenUpdateArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxNds_AgentPNMNotificationArrived( UINT8 *buf, UINT32 bufSize );

#endif // _WMX_SDK_NDS_IND_HANDLER_H 