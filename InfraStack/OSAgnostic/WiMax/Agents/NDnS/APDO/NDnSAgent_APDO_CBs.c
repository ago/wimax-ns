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
#include "NDnSAgent_APDO.h"

#include "IndicatorsSubscribers.h"
#include "L5OpCodes.h"	

#include "wmxSDK_Nds_InternalStructs.h"

#include "L4ConfigurationManager.h"
#include "NDnSAgent_Monitor.h"
#include "wimax_osal_ip_services.h"

extern tUtilityFunctions *pUtils;
OSAL_thread_t LinkUpThreadHandle;
static OSAL_event_t linkUpEventSent;

wmx_Status_t NDnSAgent_ApdoSetPackageUpdateState(wmx_PackageUpdateState_t updateStatus)
{		
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	
	wmx_ApdoDownloadStatus_t apdoDownloadStatus = UpdateDenied;
	FumoInternalParams_t InternalParams;
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Apdo set package update status callback called");

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_PackageUpdateState_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData*)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return WMX_ST_FAIL;
	}
	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_APDO_FUMO_DL_APPROVAL_STATUS;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_APDO_FUMO_DL_APPROVAL_STATUS;
	pIndMsg->bufferLength = sizeof(wmx_PackageUpdateState_t);	

	st = L4db_GetFumoInternalInfo(&InternalParams);
	if (st != WMX_ST_OK)
	{
		free(pSendIndData);
		return st;
	}

	if (updateStatus == PackageUpdateApproved)
	{
		apdoDownloadStatus = DownloadApproved;
	}
	else if (updateStatus == PackageUpdateDenied)
	{				
		// Set suitable parameter for callback 
		if (InternalParams.fumoOperation == foUpdate)
		{
			apdoDownloadStatus = UpdateDenied;
		}
		else
		{
			apdoDownloadStatus = DownloadDenied;
		}
	}

	*(wmx_pApdoDownloadStatus_t)pIndMsg->buf = apdoDownloadStatus;

	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);	

	return WMX_ST_OK;
}


// Send the alert notification to all the subscribers
void NDnSAgent_AlertNotification(wmxApdo_pFunctionParamStruct alertNotificationStruct)
{
	//UINT32 msgSize;
	//UINT32 sendIndDataSize;
	//SendIndData *pSendIndData;
	//NDNS_MESSAGE *pIndMsg;
	wmx_NSPid_t nspId = (wmx_NSPid_t)L4DB_INVALID_INDEX;		
	NspCategory_t nspCategory;
	
	UNREFERENCED_PARAMETER(alertNotificationStruct);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "alert notification callback called");

	L4db_GetRecentNsp(&nspId);	

	if (nspId != (wmx_NSPid_t)L4DB_INVALID_INDEX)
	{		
		nspCategory = L4db_GetNspCategory(nspId);

		if (nspCategory == Home)
		{
			NDnSAgent_ProvisioningOperation(poUpdateRequestOngoingProvisioning, 0);
		}
		else
		{
			NDnSAgent_ProvisioningOperation(poUpdateRequestInitialProvisioning, 0);
		}
	}

	//if (nspId != (wmx_NSPid_t)L4DB_INVALID_INDEX)
	//{		
	//	nspCategory = L4db_GetNspCategory(nspId);

	//	if (nspCategory == Home)
	//	{
	//		alertNotificationStruct->FuncParamUnion.AlertNotificationStruct.useOnGoing = TRUE;
	//	}
	//	else
	//	{
	//		alertNotificationStruct->FuncParamUnion.AlertNotificationStruct.useOnGoing = FALSE;
	//	}
	//}

	//msgSize = sizeof(NDNS_MESSAGE) + sizeof(alertNotificationStruct);
	//sendIndDataSize = sizeof(SendIndData) + msgSize;
	//pSendIndData = (SendIndData*)malloc(sendIndDataSize);
	//pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	//pSendIndData->pSenderFuncs = nds_pFuncs;
	//pSendIndData->senderL5Conn = nds_l5ConnID;
	//pSendIndData->pSubscribersList = indicatorSubscribersList;
	//pSendIndData->indication_id = NDNS_OPCODE_IND_PROVISIONING_OPERATION;
	//pSendIndData->indication_buffer_size = msgSize;
	//pIndMsg->opcode = NDNS_OPCODE_IND_PROVISIONING_OPERATION;
	//pIndMsg->bufferLength = sizeof(alertNotificationStruct);
	//OSAL_memcpy_s(pIndMsg->buf, sizeof(alertNotificationStruct), alertNotificationStruct, sizeof(alertNotificationStruct));

	//Messenger_PostRequest(
	//	MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	//free(pSendIndData);	
}


// Send the alert notification to all the subscribers
void NDnSAgent_ProvisioningOperation(wmx_ProvisioningOperation_t provisioningOperation, UINT16 contactType)
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	
	wmx_ProvisioningOperationInfo_t provInfo;
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "deal with sending provisioning operation to the users");	

	provInfo.provisioningOperation = provisioningOperation;
	provInfo.contactType = contactType;

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_ProvisioningOperationInfo_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData*)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_PROVISIONING_OPERATION;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_PROVISIONING_OPERATION;
	pIndMsg->bufferLength = sizeof(wmx_ProvisioningOperationInfo_t);
	*(wmx_pProvisioningOperationInfo_t)pIndMsg->buf = provInfo;

	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);	
}


// Send the alert notification to all the subscribers
void NDnSAgent_PackageUpdate( wmx_PackageUpdateStatus_t packageUpdateStatus )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Sending package update notification to the users");	

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_PackageUpdateStatus_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData*)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_PACKAGE_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_PACKAGE_UPDATE;
	pIndMsg->bufferLength = sizeof(wmx_PackageUpdateStatus_t);
	*(wmx_pPackageUpdateStatus_t)pIndMsg->buf = packageUpdateStatus;

	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);	
}

// Send the alert notification to all the subscribers
void NDnSAgent_PackageDownloadProgress( wmx_PackageDownloadProgressInfo_t packageDownloadProgressInfo )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Sending package update extansion notification to the users");	

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_PackageDownloadProgressInfo_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData*)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS;
	pIndMsg->bufferLength = sizeof(wmx_PackageDownloadProgressInfo_t);
	*(wmx_pPackageDownloadProgressInfo_t)pIndMsg->buf = packageDownloadProgressInfo;

	Messenger_PostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);	
}



// Used to receive status of scan on scan completed event
void NDnSAgent_ApdoLinkStatus(	wmx_ApdoLinkStatus_t linkStatus, 
								char nspName[WMX_NSP_NAME_MAX_SIZE],
								wmx_NSPid_t nspId, 
								wmx_ApdoActivationConnection_t activationConnection, 
								char realm[WMX_NSP_REALM_MAX_SIZE],
								char toDmAcc[MAX_ACCOUNT_NAME_SIZE])
{	
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	
	wmx_ApdoLinkStatusCBStruct_t apdoLinkStatusCBStruct;
	size_t realmLen;
	

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "raising APDO link status CB");

		// If link is down reset the provisioning started flag.
		if (linkStatus == APDO_linkDown)
		{
			Ndns_SetProvisioningStarted(FALSE);
		}
		
		msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_ApdoLinkStatusCBStruct_t);
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
		pSendIndData->indication_id = NDNS_OPCODE_IND_APDO_LINK_STATUS;
		pSendIndData->indication_buffer_size = msgSize;
		pIndMsg->opcode = NDNS_OPCODE_IND_APDO_LINK_STATUS;
		pIndMsg->bufferLength = sizeof(wmx_ApdoLinkStatusCBStruct_t);
		apdoLinkStatusCBStruct.activationConnection = activationConnection;
		//apdoLinkStatusCBStruct.bek = bek;
		apdoLinkStatusCBStruct.linkStatus = linkStatus;
		apdoLinkStatusCBStruct.nspId = nspId;

		realmLen = OSAL_strnlen(realm, WMX_NSP_REALM_MAX_SIZE);
		OSAL_strncpy_s(apdoLinkStatusCBStruct.realm, WMX_NSP_REALM_MAX_SIZE, realm, realmLen);	
		OSAL_strncpy_s(apdoLinkStatusCBStruct.nspName, WMX_NSP_NAME_MAX_SIZE, nspName, OSAL_strnlen(nspName, WMX_NSP_NAME_MAX_SIZE));	
		OSAL_strncpy_s(apdoLinkStatusCBStruct.toDmAcc, MAX_ACCOUNT_NAME_SIZE, toDmAcc, OSAL_strnlen(toDmAcc, MAX_ACCOUNT_NAME_SIZE));	

		// @@@ : 6/9/09 : JSS - OSAL api change
		OSAL_memcpy_s(pIndMsg->buf, sizeof(wmx_ApdoLinkStatusCBStruct_t), &apdoLinkStatusCBStruct, sizeof(wmx_ApdoLinkStatusCBStruct_t));

		pUtils->tpfnPostRequest(
			MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

		free(pSendIndData);
				
}

static wmx_ApdoLinkStatusCBStruct_t ApdoLinkUpParamsBuffer; // use it to pass the data between threads

void LinkUpThreadFunc( LPVOID lpParameter )
{	
	wmx_ApdoLinkStatus_t linkStatus = APDO_linkDown;
	wmx_ApdoLinkStatusCBStruct_t apdoLinkUpParams;
	UINT32 retries;
	UINT32 linkUpSleep;  
	UINT32 afterLinkUpSleep;

	// @@@ JSS :: There is no point in setting this global to true after the thread has been fired. 
	// The linkUpCS gets initialized way before the control can reach here. 
	g_ndnsContext.isLinkUpThreadAlive = TRUE;
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "APDO: LinkUpThreadFunc - IN.");
	OSAL_create_event(&linkUpEventSent, TRUE, FALSE, "LinkUpSleepEvent");
	L4Configurations_getAPDOLinkUpRetries(&retries);
	L4Configurations_getAPDOLinkUpSleep(&linkUpSleep);
	L4Configurations_getAPDOAfterLinkUpSleep(&afterLinkUpSleep);
	// race condition - in case LinkUp thread is alive, linkUpCS will be uninitialized.
	if(!g_ndnsContext.isLinkUpThreadAlive)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "LinkUpThreadFunc: isLinkUpThreadAlive == FALSE.");
		return;
	}
	OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
	OSAL_memcpy_s(&apdoLinkUpParams, sizeof(wmx_ApdoLinkStatusCBStruct_t), lpParameter, sizeof(wmx_ApdoLinkStatusCBStruct_t));
	OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);
	
		// If Link status is down send indication
		if (apdoLinkUpParams.linkStatus == APDO_linkDown)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "APDO: LinkUpThreadFunc calling APDO link status down");
			if(!g_ndnsContext.isLinkUpThreadAlive)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "LinkUpThreadFunc: isLinkUpThreadAlive == FALSE.");
				return;
			}
			OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
			NDnSAgent_ApdoLinkStatus(apdoLinkUpParams.linkStatus, apdoLinkUpParams.nspName, apdoLinkUpParams.nspId, 
				apdoLinkUpParams.activationConnection, apdoLinkUpParams.realm, apdoLinkUpParams.toDmAcc);	;
			OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);
			return;
		}
		// Link status is up - wait for ip
		if (apdoLinkUpParams.linkStatus == APDO_linkUp)
		{
			// Wait until we get IP or link down.
			while ((!IsIPAddReady()))
			{
				// Make sure there was no disconnection while waiting for IP
				if(!g_ndnsContext.isLinkUpThreadAlive)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "LinkUpThreadFunc: isLinkUpThreadAlive == FALSE.");
					return;
				}	
				OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
				linkStatus = ApdoLinkUpParamsBuffer.linkStatus;
				OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);

			if (linkStatus == APDO_linkDown)
			{
				// There is no need to raise CB since we did't raise the link up CB yet.
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "APDO: LinkUpThreadFunc - got linkDown while waiting for IP. exit thread");
				return;
			}
			OSAL_sleep(linkUpSleep);
		}
	}

	OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);

	OSAL_memcpy_s(&apdoLinkUpParams, sizeof(wmx_ApdoLinkStatusCBStruct_t), lpParameter, sizeof(wmx_ApdoLinkStatusCBStruct_t));

	OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);

	// Only raise indication when linkup
	if (apdoLinkUpParams.linkStatus == APDO_linkUp)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "APDO:  LinkUpThreadFunc calling APDO link status CB");
		//We add this list for now because we witnessed many cases that the initial call to the
		//OMA server didn't make it outside our device because a lot of OS created traffic occurs as soon as
		//we get an IP. Especially on Vista.
		OSAL_sleep(afterLinkUpSleep);
			if(g_ndnsContext.isLinkUpThreadAlive)
			{
				OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
			}
			NDnSAgent_ApdoLinkStatus(apdoLinkUpParams.linkStatus, apdoLinkUpParams.nspName, apdoLinkUpParams.nspId, 
								 apdoLinkUpParams.activationConnection, apdoLinkUpParams.realm, apdoLinkUpParams.toDmAcc);	
		linkStatus = ApdoLinkUpParamsBuffer.linkStatus;
		OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);
		apdoLinkUpParams.linkStatus = linkStatus;
		if (apdoLinkUpParams.linkStatus == APDO_linkDown)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "APDO: LinkUpThreadFunc calling APDO link status down");
			OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
			NDnSAgent_ApdoLinkStatus(apdoLinkUpParams.linkStatus, apdoLinkUpParams.nspName, apdoLinkUpParams.nspId, 
				apdoLinkUpParams.activationConnection, apdoLinkUpParams.realm, apdoLinkUpParams.toDmAcc);	;
			OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);
		}
	}
	else
	{
		if (apdoLinkUpParams.linkStatus == APDO_linkDown)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "APDO: LinkUpThreadFunc calling APDO link status down");
			OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
			NDnSAgent_ApdoLinkStatus(apdoLinkUpParams.linkStatus, apdoLinkUpParams.nspName, apdoLinkUpParams.nspId, 
				apdoLinkUpParams.activationConnection, apdoLinkUpParams.realm, apdoLinkUpParams.toDmAcc);	;
			OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);
		}
	}
	return ;
}

// Calculate the parameters for the ApdoLinkStatusCB and call NDnSAgent_ApdoLinkStatus to raise the indication.
void NDnSAgent_HandleApdoLinkStatus(wmx_ApdoLinkStatus_t linkStatus)
{
	wmx_NSPid_t nspId = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	//wmx_ApdoLinkStatus_t linkSt = APDO_linkDown;
	wmx_ApdoActivationConnection_t activationConnection = TRUE;
	//wmx_pBEKBuffer_t bek = NULL;
	wmx_Status_t st;
	NspCategory_t nspCategory;	
	BOOL lastConnectedStatus;
	wmx_NSP_t nspInfo;
	char realm[WMX_NSP_REALM_MAX_SIZE] = "\0";
	char nspName[WMX_NSP_NAME_MAX_SIZE] = "\0";
	char toDmAcc[MAX_ACCOUNT_NAME_SIZE] = "\0";
	ProvisionedNsp_t nsp;
			
	lastConnectedStatus = Ndns_GetLastConnectedState();	

	// Check if the link status has changed
	if (linkStatus == APDO_linkUp && lastConnectedStatus == FALSE ||
		linkStatus == APDO_linkDown && lastConnectedStatus == TRUE)
	{
		return; // No change in the link status
	}

	if (linkStatus == APDO_linkUp)
	{
		st = L4db_GetRecentNsp(&nspId);	

		if (st == WMX_ST_OK)
		{			
			nspCategory = L4db_GetNspCategory(nspId);
			if (nspCategory == NotProvisioned)
			{
				activationConnection = FALSE;
			}			

			// Get realm
			st = GetNspInfo(nspId, &nspInfo);
			
			if (st == WMX_ST_OK)
			{
				if (nspInfo.nspRealm != NULL)
				{
					OSAL_strncpy_s(realm, WMX_NSP_REALM_MAX_SIZE, nspInfo.nspRealm, OSAL_strnlen(nspInfo.nspRealm, WMX_NSP_REALM_MAX_SIZE));				
				}				
			}

			st = L4db_GetProvisionedNsp(nspId, &nsp);

			if (st == WMX_ST_OK)
			{
				OSAL_strcpy_s(nspName, WMX_NSP_NAME_MAX_SIZE, nsp.tagName);
				L4db_GetToDMAccByTagName(nsp.tagName, toDmAcc);
			}
		}
	}	
	
	Ndns_SetLastConnectedState(!lastConnectedStatus);	
	OSAL_enter_critical_section(&g_ndnsContext.linkUpCS);
	ApdoLinkUpParamsBuffer.activationConnection = activationConnection;
	ApdoLinkUpParamsBuffer.linkStatus = linkStatus;
	ApdoLinkUpParamsBuffer.nspId = nspId;
	OSAL_strncpy_s(ApdoLinkUpParamsBuffer.realm, WMX_NSP_REALM_MAX_SIZE, realm, 
		OSAL_strnlen(realm, WMX_NSP_REALM_MAX_SIZE));
	OSAL_strncpy_s(ApdoLinkUpParamsBuffer.nspName, WMX_NSP_NAME_MAX_SIZE, nspName, 
		OSAL_strnlen(nspName, WMX_NSP_NAME_MAX_SIZE));
	OSAL_strncpy_s(ApdoLinkUpParamsBuffer.toDmAcc, MAX_ACCOUNT_NAME_SIZE, toDmAcc, 
		OSAL_strnlen(toDmAcc, MAX_ACCOUNT_NAME_SIZE));

	OSAL_exit_critical_section(&g_ndnsContext.linkUpCS);
	if (LinkUpThreadHandle != NULL)
	{
		OSAL_kill_thread(LinkUpThreadHandle);
		LinkUpThreadHandle = NULL;
	}
	// Create thread to handle raise of link up indication only when we have IP
	if( 0 != OSAL_create_thread(LinkUpThreadFunc, &ApdoLinkUpParamsBuffer, &LinkUpThreadHandle ) )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Unable to create a thread for link up callback to the OMA client");			
	}
	g_ndnsContext.isLinkUpThreadAlive = TRUE;
}


void NDnSAgent_HandleSystemStateUpdate(wmx_SystemState_t systemState, wmx_SystemState_t previousSystemState)
{
	// Raise APDO indication
	switch (systemState)
	{
		case DataPathConnected:
		case Idle:
			//We don't want to raise APDO event if we were connected and we switched to Idle.
			//We should consider raising an event only if IP was changed.
			if (previousSystemState != DataPathConnected && previousSystemState != Idle)
			{			
				NDnSAgent_HandleApdoLinkStatus(APDO_linkUp);
				//in case we change the state to DataPathConnected or Idle we are sending the monitor for the XML
				PopulateMonitorXmlData();
			}
			break;
		default:
			NDnSAgent_HandleApdoLinkStatus(APDO_linkDown);
			break;

	}
}

void NDnSAgent_ApdoDeleteDMAccountInd( char* accountName )
{	
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;	
	wmx_ApdoDeleteDMAccountCBStruct_t apdoDeleteDMAccountStruct;

	TRACE(TR_MOD_APDO_AGENT, TR_SEV_INFO, "raising delete dm account indication");
	
	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_ApdoDeleteDMAccountCBStruct_t);
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
	pSendIndData->indication_id = NDNS_OPCODE_IND_APDO_DELETE_DM_ACCOUNT;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_APDO_DELETE_DM_ACCOUNT;
	pIndMsg->bufferLength = sizeof(wmx_ApdoDeleteDMAccountCBStruct_t);
	
	OSAL_strncpy_s(apdoDeleteDMAccountStruct.accountName, MAX_DM_ACCOUNT_NAME, accountName, 
		OSAL_strnlen(accountName, MAX_DM_ACCOUNT_NAME - 1));

	OSAL_memcpy_s(pIndMsg->buf, sizeof(wmx_ApdoDeleteDMAccountCBStruct_t), &apdoDeleteDMAccountStruct, 
		sizeof(wmx_ApdoDeleteDMAccountCBStruct_t));

	Messenger_PostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}
