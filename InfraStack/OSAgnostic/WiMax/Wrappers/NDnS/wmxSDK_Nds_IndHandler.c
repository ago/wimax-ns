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
#include "wmxSDK_Nds_Utils.h"
#include "wmxSDK_Apdo_Internals.h"

#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_L5.h"

#include "WrappersUtils.h"
#include "L4BufMan_L3L4Structs.h"
#include "L4BufMan_L3L4Structs_Desc.h"

#include "Messenger.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_ip_services.h"
#include "TraceModule.h"

void wmxNds_CBsCaller( UINT32 internalRequestID, void *buffer, UINT32 bufferLength )
{
	wmx_pSystemStateUpdate pSystemStateUpdate;
	int i;

	UNREFERENCED_PARAMETER(bufferLength);	

	switch ( internalRequestID )
	{
	case DRIVER_SYSTEM_STATE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got system state update");
		pSystemStateUpdate = (wmx_pSystemStateUpdate)buffer;
		// The first CB (i = 0) is the main ND&S system state CB. We iterate the CBs from the last
		// to the first to insure that the CBs of all sub-components are called first before the main CB.
		for (i = SYSTEM_STATE_MAX_CALLBACKS - 1; i >= 0; --i)
		{
			if (SystemStateUpdateCBs[i] != NULL)
			{
				TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling SystemStateUpdate callback at location %d", i);
				SystemStateUpdateCBs[i]( pSystemStateUpdate );
			}
		}		
		break;

	case DRIVER_MEDIA_STATUS:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got media status update");
		if ( NULL != MediaStatusCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling MediaStatus callback. = %d", *(wmx_pMediaStatus_t)buffer);
			MediaStatusCB( *(wmx_pMediaStatus_t)buffer );
		}
		break;

	case CONNECTION_STATE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got connection state update");
		if ( NULL != ConnectionStateUpdateCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling ConnectionStateUpdate callback. ConnectionState=%s",ConnectionStateName(*(wmx_pConnectionState_t)buffer>=UnknownConnectionState?UnknownConnectionState:*(wmx_pConnectionState_t)buffer));
			ConnectionStateUpdateCB( *(wmx_pConnectionState_t)buffer );
		}
		break;


	case DRIVER_SCAN_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got driver scan update");
		if( NULL != ScanUpdateCB )
		{
			wmx_ScanStatus_t scanStatus = *(wmx_pScanStatus_t)buffer;
			UINT32 numOfNaps = *(UINT32*)((UINT8*)buffer + sizeof(wmx_ScanStatus_t));			
			wmx_pNAP_t naps = (wmx_pNAP_t)((UINT8*)buffer + sizeof(wmx_ScanStatus_t) + sizeof(UINT32));
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling agent ScanUpdate callback");
			ScanUpdateCB( scanStatus, numOfNaps, naps  );
		}
		break;

	case AGENT_ALERT_NOTIFICATION:		
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent alert notification");		

		if ( NULL != IndProvisioningOperationCB )
		{		
			wmxApdo_pFunctionParamStruct pFunctionParamStruct = (wmxApdo_pFunctionParamStruct)buffer;

			if (pFunctionParamStruct->FuncParamUnion.AlertNotificationStruct.useOnGoing == TRUE)
			{			
				IndProvisioningOperationCB(poUpdateRequestOngoingProvisioning, 0);
			}
			else
			{
				IndProvisioningOperationCB(poUpdateRequestInitialProvisioning, 0);
			}
		}
		break;	

	case DRIVER_BSINFO_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got BsInfo report");
		if (NULL != BsInfoUpdateCB)
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling agent BsInfoUpdate callback");
			BsInfoUpdateCB((wmx_pBsInfo_t)buffer);
		}	
		break;

	case DRIVER_SII_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got SII report");
		if (NULL != SIIUpdateCB)
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling agent SIIUpdate callback");
			SIIUpdateCB((wmx_pSII_t)buffer);
		}
		break;
	case DRIVER_RECENT_BS_REPORT:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got recent BSs report");
		if (NULL != RecentBSsCB)
		{
			wmx_pChannelInfo_t pChannelInfo = (wmx_pChannelInfo_t)((BYTE*)buffer + sizeof(UINT32));
			UINT32 numOfChannelInfos = *(UINT32*)buffer;
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling agent RecentBSs callback");
			RecentBSsCB(numOfChannelInfos, pChannelInfo);
		}
		break;
	case DRIVER_BEK_REPORT:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got BEK report");
		if (NULL != BekBufferCB)
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling agent BEK report callback");
			BekBufferCB((wmx_pBEKBuffer_t)buffer);
		}
		break;

	case AGENT_SYSTEM_STATE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent system state update");
		if ( NULL != UserSystemStateUpdateCB )
		{
			wmx_pUserSystemStateUpdate pUserSystemStateUpdate = (wmx_pUserSystemStateUpdate)buffer;
			
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling user system state callback");

			UserSystemStateUpdateCB( pUserSystemStateUpdate->SystemState, pUserSystemStateUpdate->ReportStateReason, pUserSystemStateUpdate->UserLinkStatus, 
									pUserSystemStateUpdate->MediaStatus, pUserSystemStateUpdate->ConnectProgress, pUserSystemStateUpdate->RfSwitchesStatus );
		}
		break;

	case AGENT_CONNECT_COMPLETED:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent connect completed");
		break;

	case AGENT_SCAN_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent scan update");
		if ( NULL != UserScanUpdateCB )
		{
			UINT32 numOfNsps = *(UINT32*)buffer;
			UINT32 scanProgress = *((UINT32*)((UINT8*)buffer + sizeof(UINT32)));
			wmx_pNSP_t nsps = (wmx_pNSP_t)((UINT8*)buffer + 2 * sizeof(UINT32));
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling user ScanUpdate callback");
			UserScanUpdateCB( numOfNsps, nsps, scanProgress);
		}
		break;

	case AGENT_MEDIA_STATUS:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got media status update");
		if ( NULL != UserMediaStatusCB)
		{
			wmx_MediaStatus_t mediaStatus = *(wmx_pMediaStatus_t)buffer;
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling user MediaStatus callback");
			UserMediaStatusCB( mediaStatus );
		}
		break;

	case AGENT_CURRENT_PREFERRED_NSP:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got current preferred NSP update");
		if ( NULL != IndCurrentPreferredProfileCB )
		{
			UINT32 numOfNsps = *(UINT32*)buffer;
			wmx_pNSP_t pNsps = (wmx_pNSP_t)((UINT8*)buffer + sizeof(UINT32));
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling user IndCurrentPreferredProfileCB callback");
			IndCurrentPreferredProfileCB( numOfNsps, pNsps );
		}
		break;

	case AGENT_SCAN_COMPLETED:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent scan completed");
		if ( NULL != UserScanCompletedCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling user ScanCompleted callback");
			UserScanCompletedCB( *(wmx_pUserScanStatus_t)buffer );
		}
		break;

	case AGENT_COEX_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got coexistance update");
		if ( NULL != CoexistenceModeCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling coexCB callback");
			CoexistenceModeCB( *(wmx_pCoexistenceMode_t)buffer );
		}
		break;
	case AGENT_CONNECTION_MODE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got connection mode update");
		if ( NULL != ConnectionModeUpdateCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling connection mode callback");
			ConnectionModeUpdateCB( *(wmx_pUserConnectMode_t)buffer );
		}
		break;

	case AGENT_ROAMING_MODE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got roaming mode update");
		if ( NULL != RoamingModeUpdateCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling roaming mode callback");
			RoamingModeUpdateCB( *(wmx_pUserRoamingMode_t)buffer );
		}
		break;

	case AGENT_FAST_RECONNECT_MODE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got fast reconnect mode update");
		if ( NULL != FastReconnectStatusUpdateCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling fast reconnect mode callback");
			FastReconnectStatusUpdateCB( *(BOOL *)buffer );
		}
		break;
		
	case AGENT_DEVICE_STATUS_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got device status update");
		if ( NULL != DeviceStatusUpdateCB )
		{
			wmx_DeviceStatus_t deviceStatus = *(wmx_pDeviceStatus_t)buffer;
			wmx_ConnectionProgressInfo_t connectionProgress = 
										*(wmx_pConnectionProgressInfo_t)(((UINT8*)buffer) + sizeof(wmx_DeviceStatus_t));
			
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling deviceStatusUpdateCB callback");
			DeviceStatusUpdateCB(deviceStatus, connectionProgress);
		}
		break;
	
	case AGENT_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got ConnectedAsCurrentPreferredCapabilityStatus update");
		if ( NULL != ConnectedAsCurrentPreferredCapabilityStatusCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling ConnectedAsCurrentPreferredCapabilityStatus mode callback");
			ConnectedAsCurrentPreferredCapabilityStatusCB( *(BOOL *)buffer );
		}
		break;
	
		// APDO
	case AGENT_PROVISIONING_OPERATION:  // Call the ND&S's callbacks
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent APDO status update");
		if ( NULL != IndProvisioningOperationCB )
		{			
			wmx_pProvisioningOperationInfo_t pProvisioningInfo = (wmx_pProvisioningOperationInfo_t)buffer;
			
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling the APDO provisioning operation callback");

			// Use this callback for GUI alerts and for session status indications
			IndProvisioningOperationCB(	pProvisioningInfo->provisioningOperation, pProvisioningInfo->contactType );			
		}
		break;

	case AGENT_PACKAGE_UPDATE:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent APDO package update");
		if ( NULL != IndPackageUpdateCB )
		{		
			wmx_pPackageUpdateStatus_t pPackageState = (wmx_pPackageUpdateStatus_t)buffer;			

			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling the APDO package update callback");

			// Use this callback for GUI alerts and for session status indications
			IndPackageUpdateCB(*pPackageState);			
		}
		break;

	case AGENT_RF_TAKEN:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got RF Taken indication");
		if ( NULL != RfTakenCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling RF taken callback");
			RfTakenCB();
		}
		break;

	case AGENT_PACKAGE_DOWNLOAD_PROGRESS:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got agent APDO package download progress");
		if ( NULL != IndPackageDownloadProgressCB )
		{	
			wmx_PackageDownloadProgressInfo_t *packageDownloadProgressInfo = (wmx_pPackageDownloadProgressInfo_t)buffer;


			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Calling the APDO package update Ex callback");

			// Use this callback for GUI alerts and for session status indications
			IndPackageDownloadProgressCB(*packageDownloadProgressInfo);			
		}
		break;

	case AGENT_PNM_NOTIFICATION:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "got PNM indication");
		if ( NULL != IndDevicePNMNotificationCB )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Calling PNM callback");
			IndDevicePNMNotificationCB();
		}
		break;	

	default:
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "Unknown internal opcode: %d", internalRequestID);
		//ASSERT();
		break;
	}
}

// State report arrived from the driver
// Fill a wmx_SystemStateUpdate struct from the ReportState_type data. Translate driver enums to AppSrv enums
wmx_Status_t wmxNds_StateReportArrived( ReportState_type stateReport )
{
	wmx_SystemStateUpdate systemStateUpdate;	
	UINT8 messageBuffer[sizeof(wmx_SystemStateUpdate)];  // concatenate all the fields to one buffer
	wmx_ConnectionState_t old_connectionState;
	wmx_ConnectionState_t new_connectionState;
	//wmx_ConnectStatus_t connectStatus; // TODO: remove
	wmx_SystemState_t old_SystemState;
	
	memset(&systemStateUpdate, 0, sizeof(wmx_SystemStateUpdate));

	if (stateReport.MediaStatus.Type == L3L4_TLV_TYPE_MEDIA_STATUS) 
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_StateReportArrived: MediaStatus arrived from device = %d", stateReport.MediaStatus.value);
		//wmxNds_DriverMediaStatusToMediaStatus(&(systemStateUpdate.MediaStatus), stateReport.MediaStatus.value);
		// Oran - the mapping is 1:1
		systemStateUpdate.MediaStatus = stateReport.MediaStatus.value;

		if (MediaStatusCB != NULL)
		{
			if (GetCurrentMediaStatus() != systemStateUpdate.MediaStatus)
			{
				TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "Media status is different from previous one, sending to registered users");
				SetCurrentMediaStatus(systemStateUpdate.MediaStatus);
				nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_MEDIA_STATUS, (void*)&systemStateUpdate.MediaStatus, sizeof(wmx_MediaStatus_t), &wmxNds_CBsCaller);
			}
			else
			{
				TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "Media status is identical from previous one, filtering");
			}
		}
		
		/* Added macro for Linux - prevent it from getting compiled in the contect of iWmxSdk */
#ifndef _WIMAX_SDK_
		OSAL_RenewIP(systemStateUpdate.MediaStatus);
#endif
	}
	

	// check that system state is in the report
	if ( stateReport.SystemState.Type != L3L4_TLV_TYPE_SYSTEM_STATE )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_WARNING, "state report doesn't contain system state !!");
		return WMX_ST_OK;
	}
	
	// update the system state
	wmxNds_DriverSystemStateToSystemState( &(systemStateUpdate.SystemState), stateReport.SystemState.value );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "System State Arrived: %s", NDnSSystemStates(systemStateUpdate.SystemState));

	old_SystemState = GetCurrentSystemState();

	// TODO: Oran - update to the new connection states
	// get the new connection state
	wmxNds_SystemStateToConnectionState( &new_connectionState, systemStateUpdate.SystemState );
	wmxNds_SystemStateToConnectionState( &old_connectionState, old_SystemState );
	
	// Copy all the fields to the buffer
	SetCurrentSystemState(systemStateUpdate.SystemState);

	if (stateReport.ReportStateReason.Type == L3L4_TLV_TYPE_REPORT_STATE_REASON) 
	{	
		wmxNds_DriverReportStateReasonToReportStateReason(&(systemStateUpdate.ReportStateReason), stateReport.ReportStateReason.value);
		//systemStateUpdate.ReportStateReason = stateReport.ReportStateReason.value;
	}
	if (stateReport.LinkStatus.Type == L3L4_TLV_TYPE_LINK_STATUS)
	{	
		// Fill the link status struct
		systemStateUpdate.linkStatus.cinr = stateReport.LinkStatus.RxCinr;
		systemStateUpdate.linkStatus.downLinkSpeed = stateReport.LinkStatus.DownLinkSpeed;
		systemStateUpdate.linkStatus.frequency = stateReport.LinkStatus.CenterFrequency;
		systemStateUpdate.linkStatus.linkQuality = stateReport.LinkStatus.LinkQuality;
		OSAL_memcpy_s(systemStateUpdate.linkStatus.bsId, sizeof(wmx_BSid_t),stateReport.LinkStatus.BSID, sizeof(wmx_BSid_t));
		systemStateUpdate.linkStatus.power = stateReport.LinkStatus.TxPower;
		systemStateUpdate.linkStatus.rssi = stateReport.LinkStatus.RxRssi;		
		systemStateUpdate.linkStatus.time = 0;
		systemStateUpdate.linkStatus.upLinkSpeed = stateReport.LinkStatus.UpLinkSpeed;		
		systemStateUpdate.linkStatus.linkStatusArrived = TRUE;
	}
	else
	{
		systemStateUpdate.linkStatus.linkStatusArrived = FALSE;
	}


	if (stateReport.ChannelInfo.Type == L3L4_TLV_TYPE_CHANNEL_INFO)
	{		
		systemStateUpdate.channelInfo.bandwidth		= stateReport.ChannelInfo.Bandwidth;
		systemStateUpdate.channelInfo.channelId		= stateReport.ChannelInfo.ChannelId;
		systemStateUpdate.channelInfo.fft			= stateReport.ChannelInfo.Fft;
		systemStateUpdate.channelInfo.frequency		= stateReport.ChannelInfo.Frequency;		
		systemStateUpdate.channelInfo.channedInfoArrived = TRUE;
	}
	else
	{
		systemStateUpdate.channelInfo.channedInfoArrived = FALSE;
	}
	
	if (stateReport.ConnectProgress.Type == L3L4_TLV_TYPE_CONNECT_PROGRESS) 
	{	
		wmxNds_ConnectProgressInfoTranslation(&(systemStateUpdate.ConnectProgress), stateReport.ConnectProgress.value);
	}
	// If the TLV doesn't exist the rf status is on in the hardware and software
	if (stateReport.RFStatus.Type == L3L4_TLV_TYPE_RF_SWITCHES_STATUS) 
	{	
		wmxNds_DriverRfStatusToRfStatus(&(systemStateUpdate.rfSwitchesStatus.swRfStatus), stateReport.RFStatus.SwRFSwitch);
		wmxNds_DriverRfStatusToRfStatus(&(systemStateUpdate.rfSwitchesStatus.hwRfStatus), stateReport.RFStatus.HwRFSwitch);	
	}
	else
	{
		systemStateUpdate.rfSwitchesStatus.swRfStatus = On;
		systemStateUpdate.rfSwitchesStatus.hwRfStatus = On;
	}
	
	OSAL_memcpy_s(messageBuffer, sizeof(wmx_SystemStateUpdate), &systemStateUpdate, sizeof(wmx_SystemStateUpdate));

	// call plastic system state callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_SYSTEM_STATE_UPDATE, (void*)messageBuffer, sizeof(wmx_SystemStateUpdate), &wmxNds_CBsCaller);		

	// if connection state changed	
	if( new_connectionState != old_connectionState )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Connection State changed to: %d", new_connectionState);		
		// call silver connection state callback
		nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, CONNECTION_STATE_UPDATE, (void*)&new_connectionState, sizeof(wmx_ConnectionState_t), &wmxNds_CBsCaller);
	}	

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_ScanReportArrived( ReportScanResults_type scanReport )
{
	wmx_ScanStatus_t scanStatus;	
	UINT32 numOfChannels = 0;
	UINT32 numOfChannelsInNAP = 0;
	int numNAPsIndex = sizeof(wmx_ScanStatus_t);
	int offset = sizeof(wmx_ScanStatus_t) /* scan status */ + sizeof(UINT32); /* num of NAPs */
	UINT8 napsBuf[ sizeof(wmx_ScanStatus_t) + sizeof(UINT32) /* offset */ + (WMX_NAPS_MAX_NUM * sizeof(wmx_NAP_t)) /* NAPs */];		
	UINT32 *napsCount = (UINT32*)(napsBuf + numNAPsIndex);
	wmx_pNAP_t napsArr = (wmx_pNAP_t)(napsBuf + offset);

	((wmx_pScanStatus_t)napsBuf)[0] = 0; // reset scan status
	*napsCount = 0; // reset num of NAPs

	// get the scan results
	// count the number of found NAPs and Channels
	while( ( *napsCount < ARRAY_ENTRIES(scanReport.ScanResultList_Report) /* num of array elements */) && 
		   ( numOfChannels < ARRAY_ENTRIES(scanReport.ScanResultList_Report) ) /* Make sure we don't go out of bounds */&&
		   ( scanReport.ScanResultList_Report[numOfChannels].Type != INVALID_OPCODE ) )
	{		
		// Check if there is a need for a new NAP
		if ( *napsCount > 0 &&
			napsArr[*napsCount - 1].bsCriteria.bsID[0] == scanReport.ScanResultList_Report[numOfChannels].BsId[0].value &&
			napsArr[*napsCount - 1].bsCriteria.bsID[1] == scanReport.ScanResultList_Report[numOfChannels].BsId[1].value &&
			napsArr[*napsCount - 1].bsCriteria.bsID[2] == scanReport.ScanResultList_Report[numOfChannels].BsId[2].value)
		{ // Use the same NAP
			// Update the best RSSI and CINR in necessary
			if (napsArr[*napsCount - 1].bestRssi < scanReport.ScanResultList_Report[numOfChannels].Rssi)
			{
				napsArr[*napsCount - 1].bestRssi = scanReport.ScanResultList_Report[numOfChannels].Rssi;
			}

			if (napsArr[*napsCount - 1].bestCINR < scanReport.ScanResultList_Report[numOfChannels].Cinr)
			{
				napsArr[*napsCount - 1].bestCINR = scanReport.ScanResultList_Report[numOfChannels].Cinr;
			}

			if (napsArr[*napsCount - 1].bestLinkQuality < scanReport.ScanResultList_Report[numOfChannels].LinkQuality)
			{
				napsArr[*napsCount - 1].bestLinkQuality = scanReport.ScanResultList_Report[numOfChannels].LinkQuality;
			}
			napsArr[*napsCount - 1].preambleIdList[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].PreambleId;
			napsArr[*napsCount - 1].channelIdList[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].ChannelId;			
			napsArr[*napsCount - 1].RSSIs[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].Rssi;
			napsArr[*napsCount - 1].CINRs[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].Cinr;
			napsArr[*napsCount - 1].linkGrade[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].LinkGrade;
			napsArr[*napsCount - 1].linkQuality[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].LinkQuality;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "wmxNds_ScanReportArrived : scanReport.ScanResultList_Report[numOfChannels].ChannelId = [%d]", scanReport.ScanResultList_Report[numOfChannels].ChannelId);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "wmxNds_ScanReportArrived : scanReport.ScanResultList_Report[numOfChannels].LinkQuality = [%d]", scanReport.ScanResultList_Report[numOfChannels].LinkQuality);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "wmxNds_ScanReportArrived : scanReport.ScanResultList_Report[numOfChannels].PreambleId = [%d]", scanReport.ScanResultList_Report[numOfChannels].PreambleId);
			napsArr[*napsCount - 1].numChannels++;
			napsArr[*napsCount - 1].changeCount = 0;	
			numOfChannelsInNAP++;
		}
		else // New NAP		
		{			
			(*napsCount)++;	
			numOfChannelsInNAP = 0;	

			OSAL_memcpy_s(napsArr[*napsCount - 1].bsCriteria.bsID, sizeof(wmx_BSid_t), scanReport.ScanResultList_Report[numOfChannels].BsId, sizeof(wmx_BSid_t));
			OSAL_memcpy_s(napsArr[*napsCount - 1].bsCriteria.bsIDmask, sizeof(wmx_BSidMask_t), scanReport.ScanResultList_Report[numOfChannels].BsIdmask, sizeof(wmx_BSidMask_t));						

			napsArr[*napsCount - 1].bestRssi = scanReport.ScanResultList_Report[numOfChannels].Rssi;
			napsArr[*napsCount - 1].bestCINR = scanReport.ScanResultList_Report[numOfChannels].Cinr;
			napsArr[*napsCount - 1].bestLinkQuality = scanReport.ScanResultList_Report[numOfChannels].LinkQuality;
			napsArr[*napsCount - 1].preambleIdList[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].PreambleId;
			napsArr[*napsCount - 1].channelIdList[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].ChannelId;
			napsArr[*napsCount - 1].RSSIs[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].Rssi;
			napsArr[*napsCount - 1].CINRs[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].Cinr;
			napsArr[*napsCount - 1].linkGrade[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].LinkGrade;
			napsArr[*napsCount - 1].linkQuality[numOfChannelsInNAP] = scanReport.ScanResultList_Report[numOfChannels].LinkQuality;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "wmxNds_ScanReportArrived : scanReport.ScanResultList_Report[numOfChannels].ChannelId = [%d]", scanReport.ScanResultList_Report[numOfChannels].ChannelId);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "wmxNds_ScanReportArrived : scanReport.ScanResultList_Report[numOfChannels].LinkQuality = [%d]", scanReport.ScanResultList_Report[numOfChannels].LinkQuality);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "wmxNds_ScanReportArrived : scanReport.ScanResultList_Report[numOfChannels].PreambleId = [%d]", scanReport.ScanResultList_Report[numOfChannels].PreambleId);
			napsArr[*napsCount - 1].numChannels = 1; // First channel of the NAP
			napsArr[*napsCount - 1].changeCount = 0;	
			numOfChannelsInNAP++;							
		}

		numOfChannels++;
	}

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "scan report recieved with %d NAPs", *napsCount);

	if (*napsCount > WMX_NAPS_MAX_NUM)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "scan report contains too many NAPs. Max num allowed: %d. Lost %d NAPs.", WMX_NAPS_MAX_NUM, *napsCount - WMX_NAPS_MAX_NUM);
		*napsCount = WMX_NAPS_MAX_NUM;
	}

	// if the scan is complete - update the scan status
	if( scanReport.ScanStatus.Type == L3L4_TLV_TYPE_SCAN_STATUS && scanReport.ScanStatus.value != E_SCAN_STATUS_SCANING)
	{
		// TODO: Oran - check if ScanStopped due to coex should have a separate enum value
		scanStatus = wmxNds_CalcScanStatus( (E_ScanStatus)scanReport.ScanStatus.value, *napsCount );
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Scan status is: %d", scanStatus);
		((wmx_pScanStatus_t)napsBuf)[0] = scanStatus;
	}

	// call gold scan update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_SCAN_UPDATE, napsBuf, sizeof(napsBuf), &wmxNds_CBsCaller);

	if( scanReport.ScanStatus.Type != L3L4_TLV_TYPE_SCAN_STATUS )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "Scan report doesn't contain scan status");
		return WMX_ST_DEVICE_FAILURE;
	}

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_BEKReportArrived(ReportEMSKRelatedKeys_type bekReport)
{
	wmx_BEKBuffer_t BEKBuffer;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_BEKReportArrived");

	if (bekReport.BEK.Type == L3L4_TLV_TYPE_TLS_BEK)
	{	
		OSAL_memcpy_s(BEKBuffer, sizeof(wmx_BEKBuffer_t), bekReport.BEK.BEKKeyBufferArr, sizeof(wmx_BEKBuffer_t));		
	}	
	// call gold BEK report callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_BEK_REPORT, (void*)BEKBuffer, sizeof(wmx_BEKBuffer_t), &wmxNds_CBsCaller);	

	return WMX_ST_OK;

/*
	unsigned int i;
	unsigned char *p = (unsigned char *)bekReport.BEK.BEKKeyBufferArr;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "BEK report notification arrived");
	printf("the message of bek is:\n");
	for (i = 0; i < 16; i += 4)
	{
		printf("%X,%X,%X,%X,",p[i], p[i+1], p[i+2], p[i+3]);
	}
	printf("\n");*/
}

// Get the neighborhood channels
wmx_Status_t wmxNds_RecentBSsReportArrived(ReportRecentNbrHood_type recentNbrhoodReport)
{	
	BYTE convertedChannelsBuffer[sizeof(wmx_ChannelInfo_t)*WMX_CHANNELS_MAX_NUM + sizeof(UINT32)] = {0};
	wmx_pChannelInfo_t pChannelInfos; 
	UINT32 bufferLength;
	UINT32 i;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "wmxNds_RecentBSsReportArrived(IN)");

	// Leave a place for the size of the list
	pChannelInfos = (wmx_pChannelInfo_t)(convertedChannelsBuffer + sizeof(UINT32));

	// Run over the neighborhood channels and convert to wmx_pChannelInfo_t struct
	for (i=0; i < WMX_CHANNELS_MAX_NUM; i++)
	{	
		if (recentNbrhoodReport.ChannelInfoArray[i].Type == L3L4_TLV_TYPE_CHANNEL_INFO)
		{	
			pChannelInfos[i].channelID = 0;
			pChannelInfos[i].bw = (wmx_BW_t)recentNbrhoodReport.ChannelInfoArray[i].Bandwidth;
			pChannelInfos[i].fft = (wmx_FFT_t)recentNbrhoodReport.ChannelInfoArray[i].Fft;
			pChannelInfos[i].frequency = (wmx_Frequency_t)recentNbrhoodReport.ChannelInfoArray[i].Frequency;
			OSAL_memcpy_s(pChannelInfos[i].preambleBitmap, sizeof(wmx_Preambles_t), 
					recentNbrhoodReport.ChannelInfoArray[i].Preambles, sizeof(wmx_Preambles_t));			
		}
		else // We have reached the end of the valid part of the list
		{
			break;
		}
	}
	
	*(UINT32*)convertedChannelsBuffer = i;
	bufferLength = i * sizeof(wmx_ChannelInfo_t) + sizeof(UINT32);

	// call gold recent BS report callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_RECENT_BS_REPORT, (void*)convertedChannelsBuffer, bufferLength, &wmxNds_CBsCaller);	

	return WMX_ST_OK;
}

// Oran - V3.0 OK
wmx_Status_t wmxNds_BsInfoReportArrived(ReportBsInfo_type bsInfoReport)
{
	wmx_BsInfo_t bsInfo;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "wmxNds_BsInfoReportArrived(IN)");
	
	if (bsInfoReport.BSID.Type == L3L4_TLV_TYPE_BSID)
	{	
		OSAL_memcpy_s(bsInfo.bsID, sizeof(wmx_BSid_t), bsInfoReport.BSID.FullBSID, sizeof(wmx_BSid_t));		
	}
	if (bsInfoReport.NspChangeCount.Type == L3L4_TLV_TYPE_NSP_CHANGE_COUNT)
	{
		bsInfo.nspChangeCount = bsInfoReport.NspChangeCount.NspChangeCount;
	}
	// call gold bsInfo callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_BSINFO_UPDATE, (void*)&bsInfo, sizeof(wmx_BsInfo_t), &wmxNds_CBsCaller);	

	return WMX_ST_OK;
}

// TODO: check about verbose names (null-terminated, encoding) when defined in the future
wmx_Status_t wmxNds_SIIReportArrived(ReportSII_type siiReport)
{
	wmx_SII_t sii;	
	int location = 0;
	UINT32 i, length = 0;
	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_SIIReportArrived");

	// extract the nsp ids
	if (siiReport.NSPIDList.Type == L3L4_TLV_TYPE_NSPID_LIST)
	{
		// TODO: Oran - we assume that an empty SII will not contain this TLV rather than send an empty list inside the TLV.
		// Verify with Ido that this is correct

		if (siiReport.NSPIDList.NspIdListLength % NSP_ID_SIZE != 0) // NSP_ID is 24 bits (3 bytes)
		{	// the buffer with the nsp ids must divide in NSP_ID_SIZE
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "NSP_ID list in SII has an illegal size");
			return WMX_ST_DEVICE_FAILURE;
		}
		// calculate the number of nsp ids
		sii.nspIdListSize = siiReport.NSPIDList.NspIdListLength / NSP_ID_SIZE;
		// extract the nsp ids
		for (i = 0; i < sii.nspIdListSize; i++)
		{
			OSAL_memcpy_s(sii.nspIdList + i, sizeof(wmx_NSPid_t), siiReport.NSPIDList.NspIdListData + (i*NSP_ID_SIZE), NSP_ID_SIZE);
		}
	}
	else
	{
		sii.nspIdListSize = 0;
	}

	// extact the verbose names
	if (siiReport.NSPVerboseNameList.Type == L3L4_TLV_TYPE_NSP_VERBOSE_NAME_LIST)
	{
		// verify that the nsp ids and verbose names lists are consistent
		if (sii.nspIdListSize == 0)
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "NSP_ID list is empty but verbose names list is not");
			return WMX_ST_DEVICE_FAILURE;
		}
		// TODO: Oran - check if the verbose name strings are null terminated / encoding
		for (i = 0; i < sii.nspIdListSize; i++) // the verbose name list MUST be at the same size of the nsp ids list
		{
			length = siiReport.NSPVerboseNameList.NspVerboseListData[location].value;
			if (location + length >= siiReport.NSPVerboseNameList.NspVerboseListLength)
			{
				TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "Verbose NSP name list in SII has an illegal size");
				return WMX_ST_DEVICE_FAILURE;
			}
			++location; // move to the start of the verbose name
			OSAL_memcpy_s(sii.verboseNspNameList[i], sizeof(MAX_VERBOSE_NSP_NAME_SIZE), siiReport.NSPVerboseNameList.NspVerboseListData + location, length);
			sii.verboseNspNameList[i][length] = 0; // string termination
			location += length;
		}
	}	

	if (siiReport.Realm.Type == L3L4_TLV_TYPE_REALM)
	{
		length = siiReport.Realm.RealmLength;
		OSAL_memcpy_s(sii.realm, sizeof(MAX_REALM_SIZE2), siiReport.Realm.RealmData, siiReport.Realm.RealmLength);
		sii.realm[siiReport.Realm.RealmLength] = 0; // string termination
	}

	// call gold SII callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, DRIVER_SII_UPDATE, (void*)&sii, sizeof(wmx_SII_t), &wmxNds_CBsCaller);	

	return WMX_ST_OK;
}
///////////////////////

wmx_Status_t wmxNds_AgentScanCompletedArrived( UINT8 *buf, UINT32 bufSize )
{
	wmx_UserScanStatus_t currentUserScanStatus;
	//BOOL userScanStarted = GetCurrentUserScanStarted();

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "agent scan completed arrived");

	//VERIFY( bufSize == sizeof(wmx_UserScanStatus_t) );
	currentUserScanStatus = *(wmx_pUserScanStatus_t)buf;

	// update internal data and set synchronizing event	
	SetCurrentUserScanStatus(currentUserScanStatus);

	OSAL_set_event( g_userScanCompletedEvent );

//	if( userScanStarted )
	{
		// call plastic scan completed callback
		nds_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_SCAN_COMPLETED, buf, bufSize, &wmxNds_CBsCaller );

		// reset g_userScanStarted if the repeated scan process of the driver ended 
		if( ( currentUserScanStatus == UserScanStopped ) || ( currentUserScanStatus == UserScanFailed ) )
		{
			SetCurrentUserScanStarted(FALSE);			
		}
	}	

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentConnectCompletedArrived( UINT8 *buf, UINT32 bufSize )
{
	wmx_UserConnectStatus_t currentUserConnectStatus;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "agent connect completed arrived");

	//VERIFY( bufSize == sizeof(wmx_UserScanStatus_t) );
	currentUserConnectStatus = *(wmx_pUserConnectStatus_t)buf;

	// update internal data and set synchronizing event	
	SetCurrentUserConnectStatus(currentUserConnectStatus);

	OSAL_set_event( g_userConnectCompletedEvent );

//	if( userScanStarted )
	{
		// call plastic connect completed callback
		nds_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_CONNECT_COMPLETED, buf, bufSize, &wmxNds_CBsCaller );
		
		SetCurrentUserConnectStarted(FALSE);			
	}	

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentScanUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentScanUpdateArrived");

	// call plastic scan update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_SCAN_UPDATE, buf, bufSize, &wmxNds_CBsCaller );
	
	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentMediaStatusArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentMediaStatusArrived");

	// call plastic scan update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_MEDIA_STATUS, buf, bufSize, &wmxNds_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentCurrentPreferredNSPChanged( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentCurrentPreferredNSPChanged");

	// call plastic current preferred callback
	nds_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_CURRENT_PREFERRED_NSP, buf, bufSize, &wmxNds_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentSystemStateUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentSystemStateUpdateArrived system state update arrived");

	if( bufSize > sizeof(wmx_SystemStateUpdate) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentSystemStateUpdateArrived bufSize > sizeof(wmx_SystemStateUpdate) + 1");
	}

	// call plastic system state update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_SYSTEM_STATE_UPDATE, buf, bufSize, &wmxNds_CBsCaller);
	
	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentCoexUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentCoexUpdateArrived coexistance update arrived");

	if( bufSize > sizeof(wmx_CoexistenceMode_t) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentCoexUpdateArrived bufSize > sizeof(wmx_CoexistenceMode_t) + 1");
	}

	// call plastic system state update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_COEX_UPDATE, buf, bufSize, &wmxNds_CBsCaller);
	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentConnectionModeUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentConnectionModeUpdateArrived coexistance update arrived");

	if( bufSize > sizeof(wmx_UserConnectMode_t) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentConnectionModeUpdateArrived bufSize > sizeof(wmx_ConnectionMode_t) + 1");
	}

	// call plastic system state update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_CONNECTION_MODE_UPDATE, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentRoamingModeUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentRoamingModeUpdateArrived roaming update arrived");

	if( bufSize > sizeof(wmx_UserRoamingMode_t) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentRoamingModeUpdateArrived bufSize > sizeof(wmx_RoamingMode_t) + 1");
	}

	// call plastic system state update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_ROAMING_MODE_UPDATE, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentFastReconnectStatusUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentFastReconnectStatusUpdateArrived fast reconnect update arrived");

	if( bufSize > sizeof(BOOL) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentFastReconnectStatusUpdateArrived bufSize > sizeof(BOOL) + 1");
	}

	// call plastic system state update callback
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_FAST_RECONNECT_MODE_UPDATE, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentDeviceStatusUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentDeviceStatusUpdateArrived device status update arrived");

	if( bufSize > sizeof(wmx_DeviceStatus_t) + sizeof(wmx_ConnectionProgressInfo_t) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentDeviceStatusUpdateArrived bufSize > sizeof(wmx_DeviceStatus_t) + sizeof(wmx_ConnectionProgressInfo_t) + 1");
	}

	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_DEVICE_STATUS_UPDATE, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentRfTakenUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentRfTakenUpdateArrived update arrived");

	//TODO: David
	//if( bufSize > sizeof(wmx_DeviceStatus_t) + sizeof(wmx_ConnectionProgressInfo_t) + 1)
	//{
	//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentRfTakenUpdateArrived bufSize > sizeof(wmx_DeviceStatus_t) + sizeof(wmx_ConnectionProgressInfo_t) + 1");
	//}

	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_RF_TAKEN, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentPNMNotificationArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentPNMNotificationArrived update arrived");

	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_PNM_NOTIFICATION, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}


wmx_Status_t wmxNds_ApdoProvisioningOperationArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "APDO provisioning operation arrived");
	
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_PROVISIONING_OPERATION, buf, bufSize, &wmxNds_CBsCaller);
	
	return WMX_ST_OK;
}

wmx_Status_t wmxNds_ApdoPackageUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "APDO package update arrived");

	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_PACKAGE_UPDATE, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_ApdoPackageDownloadProgressArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "APDO package download progress arrived");

	Messenger_PostRequest(MEDIUM, AGENT_PACKAGE_DOWNLOAD_PROGRESS, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_ApdoAlertNotificationArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "APDO alert notification arrived");

	// call plastic APDO status update callback	
	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_ALERT_NOTIFICATION, buf, bufSize, &wmxNds_CBsCaller);
	
	return WMX_ST_OK;
}

wmx_Status_t wmxNds_AgentConnectedAsCurrentPreferredCapabilityStatusUpdateArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_AgentConnectedAsCurrentPreferredCapabilityStatusUpdateArrived update arrived");

	if( bufSize > sizeof(BOOL) + 1)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmxNds_AgentConnectedAsCurrentPreferredCapabilityStatusUpdateArrived bufSize > sizeof(BOOL) + 1");
	}

	nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}

wmx_Status_t wmxNds_RfTakenIndArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "RF Taken indication arrived");

	/*Messenger_PostRequest*/nds_wrapper_UtilFuncs->tpfnPostRequest(MEDIUM, AGENT_RF_TAKEN, buf, bufSize, &wmxNds_CBsCaller);

	return WMX_ST_OK;
}
