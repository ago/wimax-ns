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
#include "NDnSAgent_Utils.h"
#include "NDnSAgent.h"
#include "NDnSAgent_DB_if.h"
#include "FormatConversions.h"
#include "NDnS_L4Scanner.h"
#include "NDnSAgent_APDO.h"

#include "IndicatorsSubscribers.h"
#include "L5OpCodes.h"		

#include "wmxSDK_Apdo_Internals.h"
#include "wmxSDK_Nds_InternalStructs.h"
#include "wmxSDK_Nds_Utils.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Sup_Defines.h"
#include "XmlParser.h"

extern tUtilityFunctions *pUtils;
// Used to receive roaming mode update event
void NDnSAgent_RoamingModeUpdate( wmx_UserRoamingMode_t roamingMode )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "roaming mode update callback called");
	
	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_UserRoamingMode_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_ROAMING_MODE_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_ROAMING_MODE_UPDATE;
	pIndMsg->bufferLength = sizeof(wmx_UserRoamingMode_t);
	*(wmx_pUserRoamingMode_t)pIndMsg->buf = roamingMode;

	nds_wrapper_UtilFuncs->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}

// Used to receive fastReconnect mode update event
void NDnSAgent_FastReconnectModeUpdate( BOOL fastReconnectMode )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "fastReconnectMode mode update callback called");
	
	msgSize = sizeof(NDNS_MESSAGE) + sizeof(BOOL);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE;
	pIndMsg->bufferLength = sizeof(BOOL);
	*(BOOL *)pIndMsg->buf = fastReconnectMode;

	nds_wrapper_UtilFuncs->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}
// Used to receive connection mode update event
void NDnSAgent_ConnectionModeUpdate( wmx_UserConnectMode_t connectionMode )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "connectionMode mode update callback called");
	
	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_UserConnectMode_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE;
	pIndMsg->bufferLength = sizeof(wmx_UserConnectMode_t);
	*(wmx_pUserConnectMode_t)pIndMsg->buf = connectionMode;

	nds_wrapper_UtilFuncs->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}


// Used to receive system state update on system state changed event
// Translate the system state to user system state 
void WMX_EXT_CALL_CONV NDnSAgent_SystemStateUpdate( wmx_pSystemStateUpdate systemStateUpdate )
{
	wmx_UserSystemStateUpdate userSystemStateUpdate;
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	
	wmx_SystemState_t previousSystemState;

	wmxNds_CalcConnectStatus(systemStateUpdate, &g_ndnsContext.connectStatus);

	previousSystemState = g_ndnsContext.systemState;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Connect status is: %d", g_ndnsContext.connectStatus);	
	
	userSystemStateUpdate.SystemState = systemStateUpdate->SystemState;
	userSystemStateUpdate.ReportStateReason = systemStateUpdate->ReportStateReason;
	wmxNds_LinkStatusToUserLinkStatus(&(userSystemStateUpdate.UserLinkStatus), systemStateUpdate->linkStatus);
	userSystemStateUpdate.MediaStatus = systemStateUpdate->MediaStatus;
	userSystemStateUpdate.ConnectProgress = systemStateUpdate->ConnectProgress;
	userSystemStateUpdate.RfSwitchesStatus.hwRfStatus = systemStateUpdate->rfSwitchesStatus.hwRfStatus;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------");	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "------ NDnSAgent_SystemStateUpdate : systemStateUpdate->rfSwitchesStatus.hwRfStatus is: [%d] systemStateUpdate->rfSwitchesStatus.swRfStatus is: [%d] -----------------", systemStateUpdate->rfSwitchesStatus.hwRfStatus,systemStateUpdate->rfSwitchesStatus.swRfStatus);	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------");	
	userSystemStateUpdate.RfSwitchesStatus.swRfStatus = systemStateUpdate->rfSwitchesStatus.swRfStatus;

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_UserSystemStateUpdate);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE;
	pIndMsg->bufferLength = sizeof(wmx_UserSystemStateUpdate);
	
	OSAL_memcpy_s( pIndMsg->buf, sizeof(wmx_UserSystemStateUpdate), &userSystemStateUpdate, sizeof(wmx_UserSystemStateUpdate));
	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_SystemStateUpdate: SystemState=%s, ConnectState=%s, swRf=%d, hwRf=%d",
		NDnSSystemStates[systemStateUpdate->SystemState>=UnknownState?UnknownState:systemStateUpdate->SystemState],
		wmxConnectProgressInfoName[systemStateUpdate->ConnectProgress>=Registration?NotApplicable:systemStateUpdate->ConnectProgress],
		systemStateUpdate->rfSwitchesStatus.swRfStatus,
		systemStateUpdate->rfSwitchesStatus.hwRfStatus);	

	L4C_HandleSystemStateUpdate(systemStateUpdate);

	// Raise APDO indication 	
	NDnSAgent_HandleSystemStateUpdate(systemStateUpdate->SystemState, previousSystemState);
}

void NDnSAgent_MediaStatusUpdate(wmx_MediaStatus_t mediaStatus)
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_MediaStatus_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_MEDIA_STATUS;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_MEDIA_STATUS;
	pIndMsg->bufferLength = sizeof(wmx_MediaStatus_t);

	OSAL_memcpy_s( pIndMsg->buf, sizeof(wmx_MediaStatus_t), &mediaStatus, sizeof(wmx_MediaStatus_t));
	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}

// Used to receive ConnectedAsCurrentPreferredCapabilityStatus update event
void NDnSAgent_ConnectedAsCurrentPreferredCapabilityStatusUpdate( BOOL isEnable )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "ConnectedAsCurrentPreferredCapabilityStatus update callback called");
	
	msgSize = sizeof(NDNS_MESSAGE) + sizeof(BOOL);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE;
	pIndMsg->bufferLength = sizeof(BOOL);
	*(BOOL *)pIndMsg->buf = isEnable;

	nds_wrapper_UtilFuncs->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}

void NDnSAgent_RecentBSs(UINT32 numOfChannelInfos, wmx_pChannelInfo_t pChannelInfos)
{
	wmx_NSPid_t connectedNspID;
	BOOL		isUnprovisionedProfile;
	UINT32		i;
	char		bwStr[MAX_STR_LEN] = {0}, bwStr2[MAX_STR_LEN] = {0};	
	ChannelInfo_t dbChannelInfos[WMX_CHANNELS_MAX_NUM];
	UINT32 dbChannelInfosCount = WMX_CHANNELS_MAX_NUM;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Recent BSs report CB (IN)");	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Neighbor adv. - Got %d channels:", numOfChannelInfos);	

	for (i=0; i<numOfChannelInfos && i < WMX_CHANNELS_MAX_NUM; i++)
	{
		ConvertBandWidthToStr(pChannelInfos[i].bw, bwStr, MAX_STR_LEN);
		ConvertPreamblesBitmapToStr(pChannelInfos[i].preambleBitmap, bwStr2);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Channel number %d: Freq = %d, BW = %s, Preambles = %s", i, pChannelInfos[i].frequency, bwStr, bwStr2);
	}

	if (WMX_ST_OK == L4db_GetRecentNsp(&connectedNspID))
	{	

		isUnprovisionedProfile = L4db_IsUnprovisionedProfile(connectedNspID);	

		wmxNds_WmxChannelInfoToDBChannelInfo(dbChannelInfos, &dbChannelInfosCount, pChannelInfos, numOfChannelInfos, TRUE);
		// Add the neighbor channels to the detected channels in the L4 DB
		L4db_AddNeighborAdvChannels(numOfChannelInfos, dbChannelInfos);		
		L4db_PrintDiscoveredNAPsList();

		// If the connected NSP is an unprovisioned profile, add the channels to the profile
		if (isUnprovisionedProfile == TRUE)
		{
			L4db_AddChannelPlanToUnprovisionedProfile(connectedNspID);
		}
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Recent BSs report CB: No recent NSP found while connected");
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_RecentBSs - before save to DB");
	SaveToDB();
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Recent BSs report CB (OUT)");
}


void NDnSAgent_BEKReport( wmx_pBEKBuffer_t pBEKBuffer )
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_BEKReport (IN)");

	if (pBEKBuffer != NULL)
	{	
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X", pBEKBuffer[0], pBEKBuffer[1], pBEKBuffer[2],
			pBEKBuffer[3], pBEKBuffer[4], pBEKBuffer[5],
			pBEKBuffer[6], pBEKBuffer[7], pBEKBuffer[8],
			pBEKBuffer[9], pBEKBuffer[10], pBEKBuffer[11],
			pBEKBuffer[12], pBEKBuffer[13], pBEKBuffer[14], pBEKBuffer[15]);
		SetBEK(pBEKBuffer);
	}
}

// Used to receive event reports from Supplicant Agent
void NDnSAgent_SupEventReport( wmx_SupEvent_t event )
{		
	char identity[WMX_SUBSCRIBER_ID_MAX_SIZE];
	char password[MAX_EAP_PASSWORD_SIZE];
	char privateKey[MAX_CERT_FILE_NAME_SIZE];
	size_t tempLen;


	switch(event.eventType)
	{
	case SWC_CALLBACK_TYPE_CREDENTIAL: // missing credential
		switch(event.credId)
		{
		case SWC_CRED_IDENTITY:
			tempLen = OSAL_strnlen(identity, WMX_SUBSCRIBER_ID_MAX_SIZE);			
			if (0 < tempLen && WMX_SUBSCRIBER_ID_MAX_SIZE != tempLen)
			{
				wmx_SetIdentity((wmx_pNAI_t)identity);
			}
			break;
		case SWC_CRED_PASSWORD:			
			tempLen = OSAL_strnlen(password, MAX_EAP_PASSWORD_SIZE);
			if (MAX_EAP_PASSWORD_SIZE != tempLen && tempLen > 0)
			{
				wmx_SetPassword((wmx_pUserPassword_t)password);
			}
			break;
		case SWC_CRED_PRIVATE_KEY:			
			tempLen = OSAL_strnlen(privateKey, MAX_CERT_FILE_NAME_SIZE);
			if (MAX_CERT_FILE_NAME_SIZE != tempLen && tempLen > 0)
			{
				wmx_SetTlsPrivateKey((wmx_pCertificatePath_t)privateKey);
			}
			break;
		default:
			break;
		}
		break;
	case SWC_CALLBACK_TYPE_EVENT: // general supplicant event
		switch(event.credId)
		{
		case SWC_EV_EAP_FAILURE:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "EAP authentication failed");
			g_ndnsContext.eapContext.isEapFail = TRUE;
			break;
		case SWC_EV_EAP_SUCCESS:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "EAP authentication succeeded");
			g_ndnsContext.eapContext.isEapFail = FALSE;
			break;
		case SWC_EV_REJECTED_CREDENTIAL:
		case SWC_EV_REJECTED_IDENTITY:
		case SWC_EV_REJECTED_CERTIFICATE:
		case SWC_EV_REJECTED_CHALLENGE:
		case SWC_EV_RESTRICTED_LOGON_HOURS:
		case SWC_EV_ACCOUNT_DISABLED:
		case SWC_EV_ACCOUNT_NO_DIAL_IN:
		case SWC_EV_TLV_INVALID:
		case SWC_EV_TLV_UNKNOWN:
		case SWC_EV_TLV_NAK:
		case SWC_EV_FAST_CMAC_INVALID:
		case SWC_EV_FAST_PROVISION_SUCCESS:
		case SWC_EV_FAST_INVALID_PAC_KEY:
		case SWC_EV_FAST_INVALID_PAC_OPAQUE:
		case SWC_EV_EAP_CLEAR_TEXT_FAILURE:
		case SWC_EV_EAP_CLEAR_TEXT_SUCCESS:		
		case SWC_EV_EAP_INTERMEDIATE_FAILURE:
		case SWC_EV_EAP_INTERMEDIATE_SUCCESS:
		case SWC_EV_SIM_PIN_INCORRECT:
		case SWC_EV_SIM_PIN_REQUIRED:
		case SWC_EV_SIM_NO_READER:
		case SWC_EV_SIM_NO_CARD:
		case SWC_EV_SIM_FAILURE:
		default:
			break;
		}
		break;
	}
}