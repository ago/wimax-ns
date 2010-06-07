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
#include "NDnSAgent.h"
#include "NDnS_L4Scanner.h"
#include "NDnS_L4Publisher.h"
#include "NDnSAgent_L4P.h"
#include "NDnSAgent_APDO.h"
#include "NDnSAgent_DB_if.h"

#include "CommonServices.h"
#include "WrappersCommon.h"
#include "L5OpCodes.h"
#include "NDnSAgent_Monitor.h"

#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Nds_Utils.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Sup_Defines.h"
#include "wmxSDK_Msc_2.h"
#include "wmxSDK_Coex_1.h"
#include "NDnS_Coex.h"
#include "L3L4Structs.h"

#include "Act.h"
#include "L4ConfigurationManager.h"

#include "NDnSAgent_Utils.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_ip_services.h"
#include "wimax_osal_crypt_services.h"

typedef wmx_Status_t (*DualFlushOp)();

extern tUtilityFunctions *pUtils;
extern wmx_CoexistenceMode_t initialCoexMode;
static wmx_LinkStatus_t g_linkStatus;
// Declarations
void L4Pub_SetDeviceStatusActivationConnect(BOOL activation);
void L4C_Reset(L4CState l4cState, wmx_pSystemStateUpdate systemStateUpdate);
wmx_Status_t NDnSAgent_GetStatistics( UINT32 *bufferLength, UINT8 *buffer );
void L4C_ScheduleTask(L4C_Task task);
void L4C_TaskHandler(UINT32 internalRequestID, void *buffer, UINT32 bufferLength);
wmx_Status_t NDnSAgent_ConnectPhase2(wmx_pConnectInfo_t connectInfo);
wmx_Status_t L4C_StartManualScanPhase2(wmx_ScanType_t scanType, BOOL isInternal);
void AddNAPsBeneathThreshold(UINT32 numOfNAPs, wmx_pNAP_t pNAPs);
wmx_Status_t NDnSAgent_SetConnectModePhase2();
wmx_Status_t NDnSAgent_InvokeDualFlushOp(L4C_Task task, void * paramsBuf, UINT32 bufSize);
void NDnSAgent_OnProgressDualFlush(L4C_Task task, DualFlushOp ExecuteTask, UINT32 phaseNum);

wmx_Status_t L4C_UpdateScanStatus(BOOL isScanning)
{
	//[Oran]
	L4Pub_UpdateData(L4Pub_CbType_ScanStatus, (L4Pub_pCallbackParamsUnion)&isScanning);
	return WMX_ST_OK;
}

wmx_Status_t NDnSAgent_RfOn()
{
	wmx_Status_t status;
	L4CState states[2];

	states[0] = L4C_SINGLE_SCAN;
	states[1] = L4C_AUTO_SCAN;

	status = wmx_InternalRfOn();

	if (status == WMX_ST_OK)
	{
		FSM_WaitForMultipleStates(&g_ndnsContext.fsm, (int*)states, 2, L4C_TIMEOUT);
	}

	return status;
}

wmx_Status_t NDnSAgent_RfOff()
{
	wmx_Status_t status;

	// in case a scan/connect process is taking place, notify device
	if(L4C_GetInitialCoexMode() == WMX_MODE_CM && g_ndnsContext.processStarted)
	{
		L4C_SetProcessStarted(FALSE);
		wmx_CmdProcessEnd();
	}

	status = wmx_InternalRfOff();

	if (status == WMX_ST_OK)
	{
		if (!FSM_WaitForState(&g_ndnsContext.fsm, L4C_RF_OFF, L4C_TIMEOUT))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Wait for RfOff state has timed out.");
			return WMX_ST_FAIL;
		}
		else
		{
			ClearAvailableNSPsList();
		}
	}

	return status;
}

// Get the current preferred NSP.
wmx_Status_t GetCurrentPreferredNSPEx(wmx_pNSP_t pNSP, UINT32 *pNumOfCurrentPreferredNSPs)
{
	wmx_Status_t rc = WMX_ST_OK;
	wmx_NSPid_t currentPreferredNspID;

	if (	NULL == pNSP	)
	{
		*pNumOfCurrentPreferredNSPs = 0;
		rc = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	rc = L4db_GetCurrentPreferredNsp(&currentPreferredNspID);
	if (rc != WMX_ST_OK)
	{
		goto Finalize;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "GetCurrentPreferredNSP. nsp ID=%d", currentPreferredNspID);

	if (currentPreferredNspID != L4DB_INVALID_INDEX)
	{
		rc = GetNspInfo(currentPreferredNspID, pNSP);
		if (rc != WMX_ST_OK)
		{
			*pNumOfCurrentPreferredNSPs = 0;
			goto Finalize;
		}

		*pNumOfCurrentPreferredNSPs = 1;
	}
	else
	{
		*pNumOfCurrentPreferredNSPs = 0;
	}

Finalize:
	return rc;
}

// Get the current preferred NSP.
wmx_Status_t GetCurrentPreferredNSP(void *buffer, UINT32 *bufferSize)
{
	wmx_Status_t rc = WMX_ST_OK;
	wmx_NSP_t currentPreferredNsp;
	UINT32 numOfCurrentPreferredNSPs;

	if (	*bufferSize < sizeof(wmx_NSP_t) ||
			NULL == buffer	)
	{
		rc = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	rc = GetCurrentPreferredNSPEx(&currentPreferredNsp, &numOfCurrentPreferredNSPs);
	if (rc != WMX_ST_OK)
	{
		*bufferSize = 0;
		goto Finalize;
	}


	if (numOfCurrentPreferredNSPs > 0)
	{
		*(wmx_pNSP_t)buffer = currentPreferredNsp;
		*bufferSize = sizeof(wmx_NSP_t) * numOfCurrentPreferredNSPs;
	}
	else
	{
		// Current preferred NSP was not set
		*bufferSize = 0;
	}

Finalize:
	return rc;
}

// Set a new current preferred NSP or unset the current preferred to none.
wmx_Status_t SetCurrentPreferredNSPEx(wmx_pNSPid_t pCurrentPreferredNspIDs, UINT32 numOfCurrentPreferredNSPs)
{
	wmx_NSPid_t currentPreferredNspID;
	wmx_SystemState_t currentSystemState;
	wmx_Status_t status = WMX_ST_OK;
	wmx_Status_t currentStatus;

	// use bufferSize=0 to unset the current preferred NSP
	if (pCurrentPreferredNspIDs == NULL &&
		numOfCurrentPreferredNSPs != 0)
	{
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	// Check that the system state is not connected.
	// This check is done here and not in the DB because internal calls might want to change the current
	// preferred NSP after being connected
	OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);
	currentSystemState = g_ndnsContext.systemState;
	OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);

	if( ( L4C_CONNECTED == FSM_GetState(&g_ndnsContext.fsm) ))
	{
		status = WMX_ST_WRONG_STATE;
		goto Finalize;
	}

	if (numOfCurrentPreferredNSPs != 0)
	{
		currentPreferredNspID = *(wmx_pNSPid_t)pCurrentPreferredNspIDs; // Use only the first one
	}
	else
	{
		currentPreferredNspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetCurrentPreferredNSP(IN). curretntPreferredNSP=%d", currentPreferredNspID);
	currentStatus = L4db_SetCurrentPreferredNsp(currentPreferredNspID);

	// Check if there was a successful change to the current preferred NSP
	if (currentStatus == WMX_ST_OK)
	{
		// Raise an indication about changing the current preferred NSP
		if (currentPreferredNspID != L4DB_INVALID_INDEX)
		{
			NDnSAgent_SendCurrentPreferredNSPChanged(1, &currentPreferredNspID); // Support only one current preferred
		}
		else
		{  // Raise size 0 when the current preferred is set to NULL
			NDnSAgent_SendCurrentPreferredNSPChanged(0, &currentPreferredNspID);
		}
	}

Finalize:
	return status;
}

// Set a new current preferred NSP or unset the current preferred to none.
wmx_Status_t SetCurrentPreferredNSP(void *buffer, UINT32 bufferSize)
{
	wmx_Status_t status = WMX_ST_OK;

	// use bufferSize=0 to unset the current preferred NSP
	if (	bufferSize != sizeof(wmx_NSPid_t) &&
			bufferSize != 0)
	{
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	SetCurrentPreferredNSPEx((wmx_pNSPid_t)buffer, (UINT32)(bufferSize / sizeof(wmx_NSPid_t)));

Finalize:
	return status;
}

// Enters the ConnectMode to the Buffer, returns an error if buffer is too short.
wmx_Status_t GetConnectMode(void *buffer, UINT32 *bufferSize)
{
	if ( *bufferSize >= sizeof(wmx_UserConnectMode_t) )
	{
		*(wmx_pUserConnectMode_t)buffer = 	L4db_GetConnectMode();

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

wmx_Status_t NDnSAgent_GetPollingSupported(BOOL *buffer, UINT32 *bufferSize)
{
	BOOL localBool;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_GetPollingSupported: [IN]");
	if ( *bufferSize >= sizeof(BOOL) )
	{
		localBool = 	L4db_GetPollingIntervalSupported();
		*buffer = localBool;
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_GetPollingSupported: [OUT-ok]");
		return WMX_ST_OK;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_GetPollingSupported: [OUT-fail]");
	return WMX_ST_FAIL;
}

// Extracts the ConnectMode from the Buffer and set it, returns an error if buffer is too short.
wmx_Status_t SetConnectMode(wmx_pUserConnectMode_t pConnectMode, UINT32 bufferSize)
{
	//wmx_SystemState_t systemState;
	//wmx_NSPid_t currentPreferredNSP;

	wmx_UserConnectMode_t lastConnectMode = L4db_GetConnectMode();
	//wmx_UserConnectMode_t connectMode;
	wmx_Status_t status = WMX_ST_FAIL;

	UNREFERENCED_PARAMETER(bufferSize);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetConnectMode(IN). systemState=%s, pConnectMode = [%d]", NDnSSystemStates[g_ndnsContext.systemState], *pConnectMode);
	// in case a scan/connect process is taking place, notify device
	if(L4C_GetInitialCoexMode() == WMX_MODE_CM && g_ndnsContext.processStarted)
	{
		L4C_SetProcessStarted(FALSE);
		wmx_CmdProcessEnd();
	}

	if (pConnectMode == NULL)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	if (lastConnectMode == *pConnectMode)
	{
		return WMX_ST_OK;
	}

	// 	//In case we need to change to AutoConnect - Make sure we have a preferred NSP set.
	// 	if((connectMode == UserSemiManScanAutoConnect || connectMode == UserAutoScanAutoConnect) &&
	// 		(L4db_GetCurrentPreferredNsp(&currentPreferredNSP) != WMX_ST_OK ) )
	// 	{
	// 		return WMX_ST_WRONG_STATE;
	// 	}

	//For all scenarios we need to call StopScan and then Update DB on DualFlash -
	status = NDnSAgent_InvokeDualFlushOp(Task_SetConnectMode, (void *)pConnectMode, sizeof(wmx_pUserConnectMode_t));

	////////////////////////////////
	// 	if ( bufferSize >= sizeof(wmx_UserConnectMode_t) )
	// 	{
	// 		connectMode = *(wmx_pUserConnectMode_t)buffer;
	//
	// 		if (lastConnectMode == connectMode)
	// 		{
	// 			return WMX_ST_OK;
	// 		}
	//
	// 		st = L4db_GetCurrentPreferredNsp(&currentPreferredNSP);
	//
	// 		// Auto connect can not be set when current preferred NSP is not set
	// 		if ((connectMode == UserSemiManScanAutoConnect ||
	// 			connectMode == UserAutoScanAutoConnect) &&
	// 			st != WMX_ST_OK)
	// 		{
	// 			return WMX_ST_WRONG_STATE;
	// 		}
	//
	// 		if( lastConnectMode == UserSemiManScanManConnect && connectMode == UserSemiManScanAutoConnect)
	// 		{
	// 			L4db_SetConnectMode(connectMode);
	// 			return WMX_ST_OK;
	// 		}
	//
	// 		if( lastConnectMode == UserSemiManScanAutoConnect && connectMode == UserSemiManScanManConnect)
	// 		{
	// 			L4db_SetConnectMode(connectMode);
	// 			return WMX_ST_OK;
	// 		}
	//
	// 		// read the current system state
	// 		RWL_LockWrite(&g_ndnsContext.lockSystemState);
	// 		systemState = g_ndnsContext.systemState;
	// 		RWL_UnlockWrite(&g_ndnsContext.lockSystemState);
	//
	// 		L4S_Reset(FALSE);
	// 		OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, FALSE);
	// 		L4db_SetConnectMode(connectMode);
	// 		// in case we move from manual to semi-manual/auto scan - this will allow the auto scan to start
	// 		if (UserManScanManConnect == lastConnectMode)
	// 		{
	// 			OSAL_reset_event(g_ndnsContext.hScanStartedEvent);
	// 		}
	// 		status = L4C_SetControllerMode(systemState, FALSE);
	// 		l4cLastState = FSM_GetState(&g_ndnsContext.fsm);
	// 		if ( (systemState == Ready) )
	// 		{
	// 			// wait for scan processing to end
	// 			if ((OSAL_wait_event(g_ndnsContext.hScanStartedEvent, L4C_TIMEOUT) != WAIT_OBJECT_0) || (g_ndnsContext.scanStatus != WMX_ST_OK))
	// 			{
	// 				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Couldn't start semi-manual/auto scan");
	// 				status = WMX_ST_FAIL;
	// 			}
	// 		}
	// 	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetConnectMode(OUT) - status=%d", status);
	return status;
}


// Enters the RoamingMode to the Buffer, returns an error if buffer is too short.
wmx_Status_t GetRoamingMode(void *buffer, UINT32 *bufferSize)
{
	if ( *bufferSize >= sizeof(wmx_UserRoamingMode_t) )
	{
// TODO: Add support when the nsp id is given
//		*(wmx_pUserRoamingMode_t)buffer = 	L4db_GetRoamingMode();
UNREFERENCED_PARAMETER(buffer);

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

// Extracts the RoamingMode from the Buffer and set it, returns an error if buffer is too short.
wmx_Status_t SetRoamingMode(void *buffer, UINT32 bufferSize)
{
	UNREFERENCED_PARAMETER(buffer);
	if ( bufferSize >= sizeof(wmx_UserRoamingMode_t) )
	{
// TODO: Add support when the nsp id is given
//		L4db_SetRoamingMode(*(wmx_pUserRoamingMode_t)buffer);
//send indication to subscribers
		NDnSAgent_RoamingModeUpdate(*(wmx_pUserRoamingMode_t)(buffer));
		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

wmx_Status_t SetFastReconnectStatus(void *buffer, UINT32 bufferSize)
{
	BOOL fastReconnectStatus;
	wmx_Status_t status = WMX_ST_FAIL;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetFastReconnectStatus(IN)");
	if ( bufferSize >= sizeof(BOOL) )
	{
		fastReconnectStatus = *(BOOL*)buffer;

		if (L4db_GetFastReconnectStatus() == fastReconnectStatus)
		{
			status = WMX_ST_OK; // no need to re-assign the same value
		}
		else
		{
			status = L4db_SetFastReconnectStatus(fastReconnectStatus);
			//send indication to subscribers
			NDnSAgent_FastReconnectModeUpdate(*(BOOL *)(buffer));
		}
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetFastReconnectStatus(OUT) - status=%d", status);
	return status;
}

// Enters the ConnectMode to the Buffer, returns an error if buffer is too short.
wmx_Status_t GetFastReconnectStatus(void *buffer, UINT32 *bufferSize)
{
	if ( *bufferSize >= sizeof(BOOL) )
	{
		*(BOOL*)buffer = L4db_GetFastReconnectStatus();

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

// Enters the setPreferredNspOnConnect to the Buffer, returns an error if buffer is too short.
wmx_Status_t GetConnectedAsCurrentPreferredCapabilityStatus(void *buffer, UINT32 *bufferSize)
{
	if ( *bufferSize >= sizeof(BOOL) )
	{
		*(BOOL*)buffer = L4db_GetSetPreferredNspOnConnectState();

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

wmx_Status_t SetConnectedAsCurrentPreferredCapabilityStatus(void *buffer, UINT32 bufferSize)
{
	BOOL isEnable;
	wmx_Status_t status = WMX_ST_FAIL;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetConnectedAsCurrentPreferredCapabilityStatus(IN)");
	if ( bufferSize >= sizeof(BOOL) )
	{
		isEnable = *(BOOL*)buffer;

		status = L4db_SetSetPreferredNspOnConnectState(isEnable);

		//send indication to subscribers
		NDnSAgent_ConnectedAsCurrentPreferredCapabilityStatusUpdate(*(BOOL *)(buffer));
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetConnectedAsCurrentPreferredCapabilityStatus(OUT) - status=%d", status);
	return status;
}

wmx_Status_t NDnSAgent_setMSChap_v2Crd( void *buffer, UINT32 bufferSize)
{
	wmx_pSetMSChapParams MSChapParams = (wmx_pSetMSChapParams)buffer;
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	if ((bufferSize >= sizeof(MSChapParams) && (bufferSize != 0)))
	{
		wmxStatus = L4db_SetEapNode(MSChapParams->nspId, MSChapParams->username, MSChapParams->password);
	}
	if(wmxStatus == WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_setMSChap_v2Crd - before save to DB");
		SaveToDB();
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_setMSChap_v2Crd(OUT). status = %d", wmxStatus);
	return wmxStatus;
}

void NDnSAgent_SendConnectCompleted( wmx_ConnectStatus_t connectStatus )
{
	wmx_UserConnectStatus_t userConnectStatus;
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "connect completed callback called");

	wmxNds_ConnectStatusToUserConnectStatus( &userConnectStatus, connectStatus );

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "sending connect completed indication");

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_UserConnectStatus_t);
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
	pSendIndData->indication_id = NDNS_OPCODE_IND_CONNECT_COMPLETED;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_CONNECT_COMPLETED;
	pIndMsg->bufferLength = sizeof(wmx_UserConnectStatus_t);
	*(wmx_pUserConnectStatus_t)pIndMsg->buf = userConnectStatus;

	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}

void NDnSAgent_SendCurrentPreferredNSPChanged(UINT32 numOfCurrentPreferred, wmx_pNSPid_t pNspIDs )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData = NULL;
	NDNS_MESSAGE *pIndMsg;
	wmx_pNSP_t pNSPs = NULL;
	int i;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_SendCurrentPreferredNSPChanged (IN)");

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(UINT32) + sizeof(wmx_NSP_t)*numOfCurrentPreferred;
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "NDnSAgent_SendCurrentPreferredNSPChanged malloc pSendIndData failed");
		goto Finalize;
	}

	pNSPs = (wmx_pNSP_t)malloc(numOfCurrentPreferred * sizeof(wmx_NSP_t));
	if (pNSPs == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "NDnSAgent_SendCurrentPreferredNSPChanged malloc pNSPs failed");
		goto Finalize;
	}

	// Fill the NSPs list
	for (i=0; i < (int)numOfCurrentPreferred; i++)
	{
		GetNspInfo(pNspIDs[i], &pNSPs[i]);
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP;
	pIndMsg->bufferLength = sizeof(UINT32) + sizeof(wmx_NSP_t)*numOfCurrentPreferred;
	*(UINT32*)pIndMsg->buf = numOfCurrentPreferred;
	OSAL_memcpy_s( pIndMsg->buf + sizeof(UINT32), sizeof(wmx_NSP_t) * numOfCurrentPreferred,
		pNSPs, sizeof(wmx_NSP_t) * numOfCurrentPreferred);

	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

Finalize:
	if (pSendIndData != NULL)
	{
		free(pSendIndData);
	}
	if (pNSPs != NULL)
	{
		free(pNSPs);
	}
}


L4C_ConnectMode L4C_GetConnectionMode(wmx_UserConnectMode_t userConnectMode)
{
	L4C_ConnectMode connectMode = ConnectMode_Manual;

	switch (userConnectMode)
	{
		case UserSemiManScanManConnect:
		case UserAutoScanManConnect:
		case UserManScanManConnect:
			connectMode = ConnectMode_Manual;
			break;
		case UserSemiManScanAutoConnect:
		case UserAutoScanAutoConnect:
			connectMode = ConnectMode_Auto;
			break;
	}

	return connectMode;
}

L4C_ScanMode L4C_GetScanMode(wmx_UserConnectMode_t userConnectMode)
{
	L4C_ScanMode scanMode = ScanMode_Auto;

	switch (userConnectMode)
	{
		case UserSemiManScanManConnect:
		case UserSemiManScanAutoConnect:
			scanMode = ScanMode_SemiManual;
			break;
		case UserAutoScanManConnect:
		case UserAutoScanAutoConnect:
			scanMode = ScanMode_Auto;
			break;
		case UserManScanManConnect:
			scanMode = ScanMode_Manual;
			break;
	}

	return scanMode;
}

// resume a scan if more chunks are available or if scan cycle is complete and L4C is in auto scan mode
wmx_Status_t L4C_ResumeScan(UINT32 internalRequestID, void *buffer, UINT32 bufferLength)
{
	wmx_Status_t status;
	// choose between semi-manual scan and auto scan
	wmx_ScanType_t scanType = (L4C_GetScanMode(L4db_GetConnectMode()) == ScanMode_Auto) ? SCAN_TYPE_WIDE : SCAN_TYPE_PREFERRED;
	wmx_LinkLossType_t linkLossType;

	UNREFERENCED_PARAMETER(bufferLength);
	UNREFERENCED_PARAMETER(buffer);
	UNREFERENCED_PARAMETER(internalRequestID);

	L4S_EnableScanner(TRUE);
	// continue scanning the next chunk / retry
	if (L4C_AUTO_SCAN == FSM_GetState(&g_ndnsContext.fsm))
	{
		status = L4S_StartScanner(FALSE);
	}
	else
	{
		status = L4S_StartScanner(TRUE);
	}


	// if retryCounter is invalid (=no more retries) we want to schedule a new scan (long link loss)
	if (status == WMX_ST_WRONG_ARGUMENT)
	{	// if we got here it means that we're in auto scan and it's time to move to long link loss
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4C_ResumeScan: Move to long link loss");

		if (FSM_GetState(&g_ndnsContext.fsm) != L4C_AUTO_SCAN)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_ResumeScan: Can't move to long link loss since L4C in not in auto scan (wrong state)");
		}
		else
		{
			linkLossType = (g_ndnsContext.linkLossType != LinkLossType_Short) ? LinkLossType_Infinite : LinkLossType_Long;
			status = L4C_StartScan(scanType, linkLossType, TRUE, TRUE);
			// TODO: [Oran] consider use a saved isInternal instead of TRUE
			if ( WMX_ST_OK != status )
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartScan Failed!");
				status = WMX_ST_FAIL;
			}

		}
	}

	g_ndnsContext.scanStatus = status;
	OSAL_set_event(g_ndnsContext.hScanStartedEvent);
	return status;
}

wmx_Status_t L4C_StartAutoScan(UINT32 internalRequestID, void *buffer, UINT32 bufferLength)
{
	wmx_Status_t status = WMX_ST_OK;
	BOOL delayStart = FALSE;
	wmx_LinkLossType_t linkLossType = LinkLossType_Short;

	UNREFERENCED_PARAMETER(bufferLength);
	UNREFERENCED_PARAMETER(buffer);
	UNREFERENCED_PARAMETER(internalRequestID);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_StartAutoScan(IN)");
	if (FALSE == (BOOL)OSAL_atomic_compareExchange(&g_ndnsContext.isScanProcessingRequired, (long)FALSE, (long)TRUE))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartAutoScan: leftovers of auto scan detected");
		return WMX_ST_FAIL;
	}

	//AgeAvailableNspsList();
	if (TRUE == OSAL_atomic_compareExchange(&g_ndnsContext.isSingleManualScan, (long)FALSE, (long)TRUE))
	{
		delayStart = TRUE;
		linkLossType = (g_ndnsContext.scheduledTaskData.scanInfo.manualScanType == SCAN_TYPE_PREFERRED ? LinkLossType_Short : LinkLossType_Long);
	}

	// if last manual scan type was wide - LinkLossType_Long, else - LinkLossType_Short
	status = L4C_StartScan(SCAN_TYPE_PREFERRED, linkLossType, delayStart, TRUE);
	if ( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartScan Failed!");
		status = WMX_ST_FAIL;
	}

	g_ndnsContext.scanStatus = status;
	OSAL_set_event(g_ndnsContext.hScanStartedEvent);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_StartAutoScan(OUT)");
	return status;
}

// configure the L4C to one of the scan modes and start scanning if required
wmx_Status_t L4C_SetScanMode(BOOL startScan)
{
	L4C_ScanMode scanMode = L4C_GetScanMode(L4db_GetConnectMode());
	L4CState prevState = FSM_GetPreviousState(&g_ndnsContext.fsm);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_SetScanMode - CurState=%d, PrevState=%d, startScan=%d",
		FSM_GetState(&g_ndnsContext.fsm), prevState, startScan);

	// set scan mode
	switch (scanMode)
	{
		case ScanMode_SemiManual:
		case ScanMode_Auto:
			if ((FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, L4C_AUTO_SCAN, L4C_AUTO_SCAN) ||
				(startScan &&	(prevState == L4C_RF_OFF) ||
								// TODO: Oran - check the consequences of adding "L4C_CONNECTING" / L4C_UNINITIALIZED
								(prevState == L4C_UNINITIALIZED) ||
								(prevState == L4C_CONNECTING))))
			{
				OSAL_atomic_exchange(&g_ndnsContext.isScanProcessingRequired, (long)TRUE);
				pUtils->tpfnPostRequest(MEDIUM, 0, NULL, 0, &L4C_StartAutoScan);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Scan mode is auto/semi-manual. Post a new scan request.");

			}
			break;
		case ScanMode_Manual:
			g_ndnsContext.scanStatus = WMX_ST_OK;
			OSAL_set_event(g_ndnsContext.hScanStartedEvent);
			OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE); // reset manual scan status
			FSM_SetState(&g_ndnsContext.fsm, L4C_SINGLE_SCAN);
			L4S_EnableScanner(TRUE);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Scan mode is manual. Do nothing.");
			break;
	}

	return WMX_ST_OK;
}

/*wmx_SystemState_t L4C_UpdateSystemState(wmx_SystemState_t systemState)
{
	OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);
	if ((verifyState) && (g_ndnsContext.systemState == systemState))
	{
		OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);
		return status;
	}
	g_ndnsContext.systemState = systemState;
	OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);
}*/

// returns true if the input system state reason is valid for fast reconnect
BOOL L4C_IsFastReconnectRequired(wmx_pSystemStateUpdate systemStateUpdate)
{
	BOOL res = FALSE;
	wmx_CoexistenceMode_t coexMode = WMX_MODE_XOR;
	UINT32 msgLength = sizeof(wmx_CoexistenceMode_t);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_IsFastReconnectRequired (IN)");

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "State Reason %d", systemStateUpdate->ReportStateReason);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "System State %d", systemStateUpdate->SystemState);
	switch(systemStateUpdate->ReportStateReason)
	{
		case StateReasonDisconnectDreg:
		case StateReasonDisconnectAbort:
		case StateReasonDisconnectReset:
		case StateReasonDisconnectSecurity:
		case StateReasonDisconnectProtocolError:
			if (systemStateUpdate->SystemState == Ready)
			{
				res = TRUE;
			}
			break;
		case StateReasonResetHwWdt:
		case StateReasonResetSwWdt:
		case StateReasonResetAssert:
		case StateReasonFWRequestDevReset:
		case StateReasonFWRequestFuncReset:
			if (systemStateUpdate->SystemState == Config)
			{
				res = TRUE;
			}
			break;
		case StateReasonResetCoExistence:
			{
				//fix for bug HSD 2694572
				//While WiMAX is connecting to the network, turning on WiFi using
				//the systray icon does not stop WiMAX from connecting and also
				//shows WiFi radio as on, but no network are found. WiMAX CU shows connection,
				//WiFi shows no networks found. Leaving it like this for approximately
				//2 minutes and WiMAX will turn the radio off and WiFi will see networks again.
				//
				//The solution for this problem for V3 is to have WiMax reset upon a WiFi request (any request),
				//while WiMax is connecting (specifically, when WiMax is in the ETLS process)
				//When L3 is resetting the device it will be sending the coex reason.
				//L4 will shut RF off here and don't do a fast reconnect.

				L4db_SetSwRfState(Off);
				GetCoexistenceMode(&coexMode,&msgLength);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_IsFastReconnectRequired User call set to FALSE");
				UserCall = FALSE;
				SetCoexistanceMode(&coexMode,msgLength);
				res = FALSE;
				break;
			}
		default:
			res = FALSE;
			break;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_IsFastReconnectRequired (OUT) res %d", res);
	return res;
}

// handle Fast Reconnect
BOOL L4C_HandleFastReconnect(wmx_pSystemStateUpdate systemStateUpdate)
{
	UINT32 disableFastReconnect = 0;
	BOOL res;
	BOOL isFastReconnectEnabled = FALSE;
	wmx_NSPid_t lastConnectedNSPid;
	wmx_Status_t status = WMX_ST_OK;
	BOOL isHandled = FALSE;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_HandleFastReconnect (IN)");
	
	// if this system state contains a valid reason for fast reconnect
	if (L4C_IsFastReconnectRequired(systemStateUpdate))
	{
		res = L4Configurations_getDisableFastReconnect(&disableFastReconnect);
		if (res) // if the reg key exists - it overrides the L4DB settings
		{
			if( disableFastReconnect)
			{
				isFastReconnectEnabled = FALSE;
			}
			else
			{
				
				isFastReconnectEnabled = TRUE;
			}
		}
		else // use L4DB settings
		{
			isFastReconnectEnabled = L4db_GetFastReconnectStatus();
		}

		if (!isFastReconnectEnabled) // Fast Reconnect is disabled
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Fast Reconnect is disabled. Skipping reconnection");
		}
		else // fast reconnect is enabled
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Starting fast reconnect. Reason: %s", wmx_StateReason_tStr[systemStateUpdate->ReportStateReason]);
			// get the recent connected NSP
			status = L4db_GetRecentNsp(&lastConnectedNSPid);
			if(status != WMX_ST_OK)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Fast reconnect canceled since the recent NSP list is empty");
			}
			else // we found a recent NSP to connect to so start connecting
			{
				// try to reconnect to the recent connected NSP
				status = NDnSAgent_StartConnect(lastConnectedNSPid, COEX_PRIORITY_CONNECT_LOW, TRUE, FALSE);

				if (status != WMX_ST_OK) // we couldn't auto-connect to any of the provisioned NSPs, so start timer
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Fast reconnect failed");
				}
				else
				{
					isHandled = TRUE; // reconnect started successfully
				}
			}
		}
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_HandleFastReconnect (OUT)");
	return isHandled;
}

BOOL L4C_HandleRobustConnect(wmx_pSystemStateUpdate systemStateUpdate, BOOL isL3Trigger)
{
	UINT32 disableRobustConnect = 0;
	BOOL res;
	wmx_NSPid_t nspId;
	wmx_Status_t status = WMX_ST_OK;
	BOOL isHandled = FALSE;
	BOOL isConnectRequired = FALSE;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_HandleRobustConnect (IN)");
	UNREFERENCED_PARAMETER(systemStateUpdate);

	//if (systemStateUpdate->ReportStateReason == StateReasonFailToConnectEAPAuth)
	//{
	//	g_ndnsContext.eapContext.isEapFail = TRUE;
	//}
	res = L4Configurations_getDisableRobustConnect(&disableRobustConnect);

	if (g_ndnsContext.eapContext.isStarted && g_ndnsContext.eapContext.isEapFail)
	{
		if (!g_ndnsContext.eapContext.isPerformedFallBack) //If did not get the change to perform fall back - still have to perform trials...
		{
			if (res) // if the reg key exists - it overrides default settings
			{
				if(!disableRobustConnect)
				{
					isConnectRequired = TRUE;
				}
				else
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Robust Connect is disabled. Skipping connection attempt");
				}
			}
			else // default - robust connect is enabled
			{
				isConnectRequired = TRUE;
			}
		}
	}

	if(isL3Trigger)
	{
		if (disableRobustConnect)
		{
			g_ndnsContext.eapContext.isEapFail = FALSE;	// In case we are not in robust connect mode - case not to fallback
		}
		NDnSAgent_SetConfigToSupplicant(Ndns_GetConnectingNSPTemp());
		isHandled = TRUE;
	}
	else
	{
		if (isConnectRequired) // if robust connect conditions are valid
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Starting robust connect sequence");
			// get the recent connected NSP
			nspId = Ndns_GetConnectingNSPTemp();

			// try to connect to the NSP used in the last unsuccessful attempt
			status = NDnSAgent_StartConnect(nspId, g_ndnsContext.tempCoexPriority, TRUE, FALSE);

			if (status != WMX_ST_OK) // we couldn't auto-connect to any of the provisioned NSPs, so start timer
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Robust connect failed");

			}
			else
			{
				isHandled = TRUE; // reconnect started successfully
			}
		}
	}

	g_ndnsContext.eapContext.isEapFail = FALSE; //	A trial is done handling of next trials with new inputs.

	if(!isHandled)
	{
		g_ndnsContext.eapContext.isStarted = FALSE;
		g_ndnsContext.eapContext.numEapRetries = 0;
		g_ndnsContext.eapContext.isEapFail = FALSE;
		g_ndnsContext.eapContext.isPerformedFallBack = FALSE;
	}
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_HandleRobustConnect (OUT)");
	return isHandled;
}

void L4C_CallHandleRobustConnect(BOOL isL3Trigger)
{
	wmx_SystemStateUpdate systemStateUpdate;
	OSAL_ZeroMemory(&systemStateUpdate, sizeof(systemStateUpdate));
	L4C_HandleRobustConnect(&systemStateUpdate, isL3Trigger);
}

// handle all the reconnect use cases
BOOL L4C_HandleReconnect(wmx_pSystemStateUpdate systemStateUpdate)
{
	BOOL isHandled = FALSE;
	L4CState l4CState = FSM_GetState(&g_ndnsContext.fsm);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_HanldeReconnect (IN)");
	if (l4CState == L4C_CONNECTED) // fast reconnect
	{
		isHandled = L4C_HandleFastReconnect(systemStateUpdate);
		// reset the manual scan type (important after scan for reconnect attempt)
		g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_PREFERRED;
	}
	else if (l4CState == L4C_CONNECTING) // robust connect
	{
		isHandled = L4C_HandleRobustConnect(systemStateUpdate, FALSE);
		// reset the manual scan type (important after scan for reconnect attempt)
		g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_PREFERRED;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_HanldeReconnect (OUT)");
	return isHandled;
}

wmx_Status_t L4C_HandleDataPathConnected(wmx_pSystemStateUpdate systemStateUpdate, wmx_SystemState_t previousSystemState)
{
	wmx_NAPid_t tmpNapId;
	wmx_NSPid_t tmpNSPid = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	UINT32 connectTime;
	wmx_Status_t currentPreferredStatus;
	wmx_Status_t nspSt = WMX_ST_OK, napSt = WMX_ST_OK;
	wmx_LinkStatus_t linkStatus;
	wmx_Status_t status;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Handling DataPathConnected system state. Current state=%d, previous state=%d", systemStateUpdate->SystemState, previousSystemState);

	// we update the connection time only if we're not already in DataPathConnected
	if ( systemStateUpdate->SystemState == DataPathConnected &&
		(!(previousSystemState == DataPathConnected || previousSystemState == Idle)))
	{
		//Reset link status structure per new datapath connection
		memset(&g_linkStatus, 0, sizeof(wmx_LinkStatus_t));

		// DataPathConnected after restart
		if (FSM_GetState(&g_ndnsContext.fsm) == L4C_UNINITIALIZED)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "DataPathConnected system state after restart detected");

			nspSt = L4db_GetRecentNsp(&tmpNSPid);
			if (nspSt != WMX_ST_OK)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error finding recent NSP info");
			}

			memset(tmpNapId, L4DB_INVALID_INDEX, sizeof(wmx_NAPid_t)); // set the NAP ID to be empty

			if (!L4db_GetRecentNAP(tmpNapId))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Reading connected BsID from the device");
				status = wmx_GetLinkStatus(&linkStatus);
				if( WMX_ST_OK != status )
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error reading connected BsID from the device");
				}
				else
				{
					OSAL_memcpy_s(tmpNapId, sizeof(wmx_NAPid_t), linkStatus.bsId, sizeof(wmx_NAPid_t));
				}
				napSt = WMX_ST_FAIL;
			}
		}
		else // move from "connecting" state to "connected" state
		{
			if (initialCoexMode == WMX_MODE_CM)
			{
				// Connection is over. Send ProcessEnd
				wmx_CmdProcessEnd();
			}

			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Using cached values of NSP and NAP IDs from connection attempt");
			// use the cached NSP ID
			tmpNSPid = Ndns_GetConnectingNSPTemp();  // Get the temp connecting NSP and make it the last connected
			// use the cached NAP ID
			Ndns_GetConnectingNAPTemp((wmx_pNAPid_t)&tmpNapId);
		}

		// we have a connect NAP ID but no NSP ID - try to use the NSP ID = NAP ID bit
		if (nspSt != WMX_ST_OK && napSt == WMX_ST_OK)
		{
			//TODO: [Oran]

		}

		L4db_SetConnectedNap(tmpNapId);
		connectTime = OSAL_timeGetTime();
		L4db_SetConnectionTime (connectTime);

		// in case there was no recent NSP info or there was a mismatch between the NAP and NSP info - don't update the NSP info
		if (nspSt == WMX_ST_OK)
		{
			L4db_SetConnectedNsp(tmpNSPid);
			if(TRUE == L4db_GetSetPreferredNspOnConnectState())
			{
				currentPreferredStatus = L4db_SetCurrentPreferredNsp(tmpNSPid);
				// Check if the change was successful
				if (currentPreferredStatus == WMX_ST_OK)
				{
					NDnSAgent_SendCurrentPreferredNSPChanged(1, &tmpNSPid);
				}
			}
		}

		if (CheckIfNspInAvailableList(tmpNSPid) == FALSE)
		{
			wmx_NSP_t nsp;
			wmx_BSid_t bsId;
			wmx_BsIdType_t bsIdType = FULL_NAP; // TODO: check if the BsID type should be retreived (and saved) from the L4DB

			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Connected to NSP ID = %d but it is not contained in the available NSPs list. Synchronizing the available NSPs list", tmpNSPid);

			// the available NSPs list is doesn't contain the currently connected NSP (could be possible when the ND&S is
			// restarted when the device is already connected).
			// update the available NSPs list with that NSP.
			OSAL_ZeroMemory(&nsp, sizeof(wmx_NSP_t));
			if ( GetNspStruct(tmpNSPid, &nsp) != WMX_ST_OK)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error getting NSP info for NSP ID = %d. AvailableNSPsList will not be synchronized with the current connected NSP.", tmpNSPid);
				nspSt = WMX_ST_FAIL;
			}
			else
			{
				OSAL_ZeroMemory(&bsId, sizeof(wmx_BSid_t));
				OSAL_memcpy_s(&bsId, sizeof(wmx_NAPid_t), &tmpNapId, sizeof(wmx_NAPid_t));
				if (WMX_ST_OK == AddMultipleNSPsToAvailableNSPsList(1, &nsp, &bsId, &bsIdType))
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NSP ID = %d was added to the available NSPs list. List synchronized", tmpNSPid);
				}
				else
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error adding NSP ID = %d to the available NSPs list. List will not be synchronized", tmpNSPid);
					nspSt = WMX_ST_FAIL;
				}
			}
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NSP ID=%d is in the available NSPs list. No further handling is required", tmpNSPid);
		}
	}
	g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_PREFERRED;
	FSM_SetState(&g_ndnsContext.fsm, L4C_CONNECTED);
	return nspSt;
}

// handle system state = Ready
wmx_Status_t L4C_HandleReadyState(wmx_pSystemStateUpdate systemStateUpdate, BOOL *isReset)
{
	BOOL isHandled = FALSE;
	wmx_Status_t status = WMX_ST_OK;
	UINT32 phaseNum = 2, i;

	*isReset = FALSE;

	while (!isHandled)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Executing the current scheduled task: <%s>", L4C_TaskStr[g_ndnsContext.scheduledTask]);

		L4db_SetSwRfState(On);
		wmx_InternalRfOn();
		switch(g_ndnsContext.scheduledTask)
		{
		case Task_StartScan:
			// if a connect process was on, this means that it failed
			if (L4C_GetInitialCoexMode() == WMX_MODE_CM &&
				g_ndnsContext.processStarted &&
				FSM_GetState(&g_ndnsContext.fsm) == L4C_CONNECTING)
			{
				L4C_SetProcessStarted(FALSE);
				wmx_CmdProcessEnd();
			}
			// handle all reconnect use cases, if reconnect is required
			isHandled = L4C_HandleReconnect(systemStateUpdate);

			if (!isHandled) // no reconnect attempt / reconnect failed
			{
				if (L4S_READY == L4S_GetScannerState())
				{
					if (OSAL_atomic_compareExchange(&g_ndnsContext.isResumeScan, FALSE, TRUE))
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx: Resuming scan");
						// since we are about to begin/resume a scan - send the scan type to the L4 publisher
						L4Pub_UpdateData(L4Pub_CbType_ScanType, (L4Pub_pCallbackParamsUnion)&g_ndnsContext.scheduledTaskData.scanInfo.manualScanType);
						pUtils->tpfnPostRequest(MEDIUM, 0, NULL, 0, &L4C_ResumeScan); // schedule the next scan task
						status = WMX_ST_OK;
					}
					else
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx: A new scan is requested. Checking scan mode...");
						// reset the manual scan type (important after scan for reconnect attempt)
						g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_PREFERRED;
						// since we are about to begin/resume a scan - send the scan type to the L4 publisher
						L4Pub_UpdateData(L4Pub_CbType_ScanType, (L4Pub_pCallbackParamsUnion)&g_ndnsContext.scheduledTaskData.scanInfo.manualScanType);
						status = L4C_SetScanMode(TRUE); // system state is Ready so in auto mode we can start the scan
					}
				}
				else
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4C_SetControllerModeEx: SystemState = Ready but L4S is still scanning. Skipping state processing");
				}
				isHandled = TRUE;
			}
			break;

		case Task_StartManualScan:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Executing secheduled manual scan");
			L4C_ScheduleTask(Task_StartScan); // after the scan session is over - return to normal scan mode
			L4C_UpdateScanStatus(FALSE);
			OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE);
			// in case this is a fast reconnect scan cycle - make sure fast reconnect is allowed
			if ((g_ndnsContext.scheduledTaskData.scanInfo.manualScanType != SCAN_TYPE_RECONNECT) ||
				(L4db_GetFastReconnectStatus() == TRUE))
			{
				L4C_StartManualScanPhase2(g_ndnsContext.scheduledTaskData.scanInfo.manualScanType,
										   g_ndnsContext.scheduledTaskData.scanInfo.isInternal);
				isHandled = TRUE;
			}
			break;

		case Task_Connect:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Executing secheduled Connect");
			L4C_ScheduleTask(Task_StartScan); // after the connect session is over - return to normal scan mode
			L4C_UpdateScanStatus(FALSE);
			OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE);
			NDnSAgent_ConnectPhase2(&g_ndnsContext.scheduledTaskData.connectInfo);
			isHandled = TRUE;
			break;

		case Task_SetConnectMode:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Executing secheduled SetConnectMode");
			NDnSAgent_OnProgressDualFlush(Task_SetConnectMode, NDnSAgent_SetConnectModePhase2, phaseNum);
			isHandled = TRUE;
			break;

		case Task_AutoConnect:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Executing secheduled AutoConnect. forceManualConnect=%d", g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect);
			L4C_ScheduleTask(Task_StartScan);
			// go over the NSPs and try to connect. Stop on success or when there are no more NSPs.
			for (i = 0; i < g_ndnsContext.scheduledTaskData.connectInfo.numOfNspIDs; ++i)
			{
				status = NDnSAgent_StartConnect(g_ndnsContext.scheduledTaskData.connectInfo.nspIDs[i],
					g_ndnsContext.scheduledTaskData.connectInfo.coexPriority,
					g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect,
					g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel);
				if (WMX_ST_OK == status) break;
			}

			if (status != WMX_ST_OK) // we couldn't auto-connect to any of the provisioned NSPs, so start timer
			{
				OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, TRUE);  // continue to scan
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Couldn't auto-connect to any of the detected home NSPs. Resuming scan.");
			}
			else
			{
				isHandled = TRUE; // auto connect started successfully
			}

			break;

		case Task_StopScan:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx(OUT): Reset/StopScan during system state Ready requested");
			OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, FALSE); // go back to initial state
			NDnSAgent_OnProgressDualFlush(Task_StopScan, NULL, phaseNum);
			L4C_HandleReadyState(systemStateUpdate, isReset);
			//L4C_ScheduleTask(Task_StartScan);
			//L4C_UpdateScanStatus(FALSE);
			break;

		case Task_Reset:
		default:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx(OUT): Reset/StopScan during system state Ready requested");
			*isReset = TRUE;
			isHandled = TRUE;
			L4C_HandleReadyState(systemStateUpdate, isReset);
			break;
		}
	}
	return status;
}

// configure the L4C to the correct mode
wmx_Status_t L4C_SetControllerModeEx(wmx_pSystemStateUpdate systemStateUpdate, BOOL verifyState)
{
	wmx_Status_t status = WMX_ST_OK;
	wmx_SystemState_t systemState = systemStateUpdate->SystemState;
	wmx_RfSwitchesStatus_t rfSwitches = systemStateUpdate->rfSwitchesStatus;
	static wmx_RfStatus_t hwRfStatus = On;
	wmx_SystemState_t previousSystemState;
	L4CState l4cLastState = FSM_GetState(&g_ndnsContext.fsm);
	BOOL isReset = FALSE;
	UINT32 disableFastReconnect = 0;
	BOOL res;
	L4Pub_States_t pubStates;
	//char readFromNVM[MAX_ANSWER_SIZE];
	wmx_CoexistenceMode_t CoexMode;
	UINT32 msgLength = sizeof(wmx_CoexistenceMode_t);
	char readFromNVM[MAX_ANSWER_SIZE];
	if (systemStateUpdate->SystemState != UnInitialized)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx(IN): systemStateUpdate=%s, swRfStatus=%d, hwRfStatus=%d",
		NDnSSystemStates[systemStateUpdate->SystemState], systemStateUpdate->rfSwitchesStatus.swRfStatus,
		systemStateUpdate->rfSwitchesStatus.hwRfStatus);
	}
	else
	{
		ClearAvailableNSPsList();
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx(IN): systemStateUpdate = UnInitialized");
	}

	if (L4C_GetInitialCoexMode() == WMX_MODE_CM &&
		systemStateUpdate->ReportStateReason == StateReasonFailToConnectCoexNoRF)
	{	// true when RF has just been taken by WiFi. Need to send indication to CM
		L4C_SetProcessStarted(FALSE);
		// Need to stop the scan  send notification 
		NDnSAgent_RfTakenIndication();
		// disable "g_l4PublisherContext.isScanning" flag to avoid next time scan or wide scan
		L4Pub_UpdateScanState(FALSE);
	}

	OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);

	if ((verifyState) &&
		(g_ndnsContext.systemState == systemState) &&
		(systemState != RfOff) && // we allow RfOff to track the changes in the RF switches
		(systemState != Connecting)) // we allow Connecting to track changes in the Connection Progress
	{
		OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx(OUT). status=%d", status);
		return status;
	}
	previousSystemState = g_ndnsContext.systemState;
	g_ndnsContext.systemState = systemState;
	OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);

	OSAL_enter_critical_section(&g_ndnsContext.lockSetMode);

	// synchronize with the driver
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx. systemState=%d", systemState);
	switch(systemState)
	{
		case Ready:
			{
				status = L4C_HandleReadyState(systemStateUpdate, &isReset);
				if (isReset)
				{
					OSAL_exit_critical_section(&g_ndnsContext.lockSetMode);
					return WMX_ST_OK;
				}
				break;
			}
		case DataPathConnected:
		case Idle:
			{
				L4C_HandleDataPathConnected(systemStateUpdate, previousSystemState);
				break;
			}
		case Config:
			{
				L4CState currentState = FSM_GetState(&g_ndnsContext.fsm);
				L4CState previousState = FSM_GetPreviousState(&g_ndnsContext.fsm);

				// this a reoccuring assert - cancel the fast reconnect
				if (g_ndnsContext.scheduledTaskData.scanInfo.manualScanType == SCAN_TYPE_RECONNECT)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Reoccuring assert. Skipping reconnection");
					L4C_ScheduleTask(Task_StartScan);
				}
				// in case of device assert - schedule a manual scan and reconnect attempts
				if ((currentState == L4C_CONNECTED ||
					currentState == L4C_UNINITIALIZED && previousState == L4C_CONNECTED) &&
					L4C_IsFastReconnectRequired(systemStateUpdate) &&
					g_ndnsContext.scheduledTaskData.scanInfo.manualScanType != SCAN_TYPE_RECONNECT)
				{
					res = L4Configurations_getDisableFastReconnect(&disableFastReconnect);
					if ((res && disableFastReconnect) || (L4db_GetFastReconnectStatus() == FALSE)) // Fast Reconnect is disabled
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Fast Reconnect (assert) is disabled. Skipping reconnection");
					}
					else
					{
						// this is the first time we get the fast reconnect trigger after the assert
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Fast Reconnect (assert) activated. Scheduling reconnection");
						g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_RECONNECT;
						L4C_ScheduleTask(Task_StartManualScan);
					}
				}
				//// If registry key is set to true update L4db from NVM
				//L4Configurations_getAPDOReadFromNvm(readFromNVM);

				//if (0 == _wcsicmp(DEFAULT_TRUE_LOWER, readFromNVM))
				//{
				//	L4db_UpdateFromNVM();
				//}
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Device in config state, setting coex mode as well !");
			}
		// Fall Down
		case UnInitialized:
		case Initialized:
			{
				L4S_Reset(TRUE); // reset the L4 scanner in a hard manner, meaning don't rely on driver indications
				FSM_SetState(&g_ndnsContext.fsm, L4C_UNINITIALIZED);
				GetCoexistenceMode(&CoexMode, &msgLength);
				UserCall = FALSE;
				SetCoexistanceMode(&CoexMode, msgLength);
				// If registry key is set to true update L4db from NVM
				L4Configurations_getAPDOReadFromNvm(readFromNVM);

			if (0 == OSAL_stricmp(DEFAULT_TRUE_LOWER, readFromNVM))
			{
				L4db_UpdateFromNVM();
			}
			break;
		}
	case RfOff:
	case RfShutDown:
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx : Device in RfShutDown\\RfOff state, checking -->");
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx : if ((FSM_GetState(&g_ndnsContext.fsm) == L4C_UNINITIALIZED) --> [%d] || (systemStateUpdate->rfSwitchesStatus.hwRfStatus == Off) --> [%d] && (systemStateUpdate->rfSwitchesStatus.swRfStatus == Off)) --> [%d]", (FSM_GetState(&g_ndnsContext.fsm) == L4C_UNINITIALIZED), (systemStateUpdate->rfSwitchesStatus.hwRfStatus == Off), (systemStateUpdate->rfSwitchesStatus.swRfStatus == Off));
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx : FSM_GetState(&g_ndnsContext.fsm)==[%d]",FSM_GetState(&g_ndnsContext.fsm));
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx : ((rfSwitches.hwRfStatus == %s && hwRfStatus == %s) && (FSM_GetState(&g_ndnsContext.fsm) == %d)", (rfSwitches.hwRfStatus==On ? "On" : "Off"), (hwRfStatus==On ? "On" : "Off") , FSM_GetState(&g_ndnsContext.fsm));
			if ((rfSwitches.hwRfStatus == On && hwRfStatus == Off) && (FSM_GetState(&g_ndnsContext.fsm) == L4C_UNINITIALIZED || FSM_GetState(&g_ndnsContext.fsm) == L4C_RF_OFF))
			{
				// Set the RF state of the driver based on the L4DB (only during ND&S init)
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx : checking --> L4db_GetSwRfState() == On --> [%d] (Set the RF state of the driver based on the L4DB (only during ND&S init))", (L4db_GetSwRfState() == On));
				if (systemStateUpdate->rfSwitchesStatus.hwRfStatus == On && (L4db_GetSwRfState() == On ))
				{
					wmx_InternalRfOn(); // Maybe the rf is already on, ignore the error in this case.
				}
				status = WMX_ST_OK;
			}
			else if (FSM_GetState(&g_ndnsContext.fsm) == L4C_UNINITIALIZED && rfSwitches.hwRfStatus == On)
			{
				// Set the RF state of the driver based on the L4DB (only during ND&S init)
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx : checking --> L4db_GetSwRfState() == On --> [%d] (Set the RF state of the driver based on the L4DB (only during ND&S init))", (L4db_GetSwRfState() == On));
				if (systemStateUpdate->rfSwitchesStatus.hwRfStatus == On && (L4db_GetSwRfState() == On ))
				{
					wmx_InternalRfOn(); // Maybe the rf is already on, ignore the error in this case.
				}
				status = WMX_ST_OK;
			}
			else
			{
				if (systemState == RfShutDown)
				{
					L4db_SetSwRfState(systemStateUpdate->rfSwitchesStatus.swRfStatus);
				}
				L4S_Reset(TRUE); // reset the L4 scanner in a hard manner, meaning don't rely on driver indicationss	
			}
			hwRfStatus = rfSwitches.hwRfStatus;
			FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, L4C_RF_OFF, L4C_RF_OFF);
			break;
		}
	default:
		{
			break;
		}
	}

	// now, after the state has been aligned, reset any old actions (scan / connect / disconnect)
	L4C_Reset(l4cLastState, systemStateUpdate);

	OSAL_exit_critical_section(&g_ndnsContext.lockSetMode);

	// [Oran]
	//L4Pub_UpdateData(L4Pub_CbType_ScanType, (L4Pub_pCallbackParamsUnion)&g_ndnsContext.scheduledTaskData.scanInfo.manualScanType);
	pubStates.l4cState = FSM_GetState(&g_ndnsContext.fsm);
	pubStates.pSystemStateUpdate = systemStateUpdate;
	L4Pub_UpdateData(L4Pub_CbType_StatesChange, (L4Pub_pCallbackParamsUnion)&pubStates);

	//L4Pub_UpdateDeviceStatus(systemStateUpdate, FSM_GetState(&g_ndnsContext.fsm));
	//////////////////////

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetControllerModeEx(OUT): status=%d", status);
	return status;
}

wmx_Status_t L4C_SetControllerMode(wmx_SystemState_t systemState, BOOL verifyState)
{
	wmx_SystemStateUpdate systemStateUpdate;
	wmx_SystemState_t tempSystemState;
	wmx_Status_t status;

	memset(&systemStateUpdate, 0, sizeof(wmx_SystemStateUpdate));
	systemStateUpdate.SystemState = systemState;

	// update internal data
	status = wmx_GetSystemState( &tempSystemState,
		&systemStateUpdate.ConnectProgress,
		&systemStateUpdate.rfSwitchesStatus );
	if( WMX_ST_OK != status )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_SetControllerMode: Error getting system state from the device. System state processing will be inaccurate. Status=%d", status);
	}

	if (UnknownState == systemState && WMX_ST_OK == status)
	{
		systemStateUpdate.SystemState = tempSystemState;
	}
	else if (tempSystemState != systemState)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "L4C_SetControllerMode: input system state <> device system state");
	}

	// set the rest of the fields of the system state update struct
	systemStateUpdate.ReportStateReason = StateReasonNormal;

	memset(systemStateUpdate.linkStatus.bsId, 0xFF, sizeof(wmx_BSid_t));

	return L4C_SetControllerModeEx(&systemStateUpdate, verifyState);
}

void L4C_Reset(L4CState l4cState, wmx_pSystemStateUpdate systemStateUpdate)
{
	wmx_SystemState_t systemState = systemStateUpdate->SystemState;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4 Controller reset (IN)");

	// if we tried to connect and now we're done (either success or failure)
	if ((l4cState == L4C_CONNECTING) && (FSM_GetState(&g_ndnsContext.fsm) != L4C_CONNECTING))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Connect done");

		g_ndnsContext.eapContext.isStarted = FALSE;
		g_ndnsContext.eapContext.numEapRetries = 0;
		g_ndnsContext.eapContext.isEapFail = FALSE;
		g_ndnsContext.eapContext.isPerformedFallBack = FALSE;
		L4S_EnableScanner(TRUE);
		OSAL_set_event(g_ndnsContext.connectCompletedEvent); // Connect // TODO: [Oran] remove - stop scan
		OSAL_set_event(g_ndnsContext.dualFlushOpEvent); // Connect
		NDnSAgent_SendConnectCompleted(g_ndnsContext.connectStatus);

	}
	else if ((l4cState == L4C_DISCONNECTING) &&
		(systemState == Ready ||
		systemState == RfOff ||
		systemState == RfShutDown))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Disconnect completed");
		L4db_SetConnectionTime(DEFAULT_TIME);
		OSAL_set_event(g_ndnsContext.disconnectCompletedEvent); // Disconnect
	}

	if (((g_ndnsContext.scheduledTask == Task_Connect)  ||
		(g_ndnsContext.scheduledTask == Task_StartManualScan) ||
		(g_ndnsContext.scheduledTask == Task_AutoConnect)) &&
		(systemState == UnInitialized ||
		systemState == Config ||
		systemState == Initialized ||
		systemState == RfOff ||
		systemState == RfShutDown))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Connect done");
		L4S_EnableScanner(TRUE);
		if (g_ndnsContext.scheduledTaskData.scanInfo.manualScanType != SCAN_TYPE_RECONNECT &&
			g_ndnsContext.scheduledTaskData.scanInfo.manualScanType != SCAN_TYPE_AUTO_CONNECT)
		{
			L4C_ScheduleTask(Task_StartScan); // return to normal mode - start scan on next Ready state
		}
		// TODO: [Oran] - check if the "if" condition above should contain also "Task_StopScan" and "Task_SetConnectMode"
		OSAL_set_event(g_ndnsContext.dualFlushOpEvent); // Connect completed event
		OSAL_set_event(g_ndnsContext.connectCompletedEvent); // Connect //TODO: [Oran] remove - stop scan
	}

	if (systemState != Ready)
	{
		if (!L4S_IsScanning())
		{
			OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE);
		}
		OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, (long)FALSE);
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4 Controller reset (OUT)");
}

void L4C_ScheduleTask(L4C_Task task)
{
	OSAL_atomic_exchange((LONG *)&g_ndnsContext.scheduledTask, (LONG)task);
}

// Generate a preferred channel plan using the L4Planner and configure the L4Scanner
wmx_Status_t L4C_SetPS(wmx_LinkLossType_t linkLossType, BOOL delayStart, BOOL isInternal)
{
	wmx_CoexPriority_t coexPriority;
	NdsSettings_t settings; // L4db struct
	wmx_ChannelInfo_t mcp[MAX_CHANNELS_NUM];
	UINT32 numChannels = MAX_CHANNELS_NUM;
	int repetitionsCount, delayTime;
	wmx_Status_t rc;
	wmx_Status_t monitorStatus;
	wmx_NSPid_t currentPreferredNspId;
	wmx_ScanPolicy_t scanPolicy;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_SetPS(IN)");
	L4db_GetNdsSettings(&settings);

	L4db_PrintDiscoveredNAPsList();
	rc = L4P_GenerateMCP(ScanType_PreferredList, mcp, &numChannels);

	if (numChannels < 1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_SetPS: Couldn't generate master channel plan for preferred scan. No channels found.");
		return WMX_ST_WRONG_ARGUMENT;
	}

	if (rc != WMX_ST_OK || numChannels == MAX_CHANNELS_NUM)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_SetPS: Couldn't generate master channel plan for preferred scan");
		return WMX_ST_WRONG_ARGUMENT;
	}

	// if we got here - then we have a valid MCP
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetPS: Master channel plan generated and contains %d channels", numChannels);


	// AutoScan / SemiManualScan = COEX_PRIORITY_SCAN_LOW, ManualScan = COEX_PRIORITY_SCAN_HIGH
	if (isInternal)
	{
		coexPriority = (settings.connectMode == UserManScanManConnect) ?
						COEX_PRIORITY_SCAN_HIGH : COEX_PRIORITY_SCAN_LOW;
	}
	else // external manual scan command
	{
		coexPriority = COEX_PRIORITY_SCAN_HIGH;
	}

	// configure the correct link loss parameters
	monitorStatus = wmx_PopulateMonitorMCP(mcp,numChannels,linkLossType);
	switch (linkLossType)
	{
		case LinkLossType_Short:
			repetitionsCount = settings.shortLinkLossParams.repetition;
			delayTime = settings.shortLinkLossParams.time;
			break;
		case LinkLossType_Long:
			repetitionsCount = settings.longLinkLossParams.repetition;
			delayTime = settings.longLinkLossParams.time;
			break;
		case LinkLossType_Infinite:
			repetitionsCount = MAXSHORT;
			delayTime = (int)(INFINITE_LINK_LOSS_RATIO * settings.longLinkLossParams.time);
			break;
		default: // short link loss is the default
			repetitionsCount = settings.shortLinkLossParams.repetition;
			delayTime = settings.shortLinkLossParams.time;
			break;
	}

	//setting the flag of the currentPreferredNspId
	rc = L4db_GetCurrentPreferredNsp(&currentPreferredNspId);

	// if the current preferred NSP is set - use FIND FIRST, otherwise use FIND ALL (=out of the box preferred scan)
	if((WMX_ST_OK == rc) && ((wmx_NSPid_t)L4DB_INVALID_INDEX != currentPreferredNspId))
	{
		scanPolicy = SCAN_MODE_FIND_FIRST;
	}
	else
	{
		scanPolicy = SCAN_MODE_FIND_ALL;
	}

	//g_ndnsContext.currentScanType = SCAN_TYPE_PREFERRED;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Link Loss config: Type = %s, Delay = %d sec, Repetitions = %d", wmx_LinkLossType_tStr[linkLossType], delayTime, repetitionsCount);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_SetPS(OUT)");
	return L4S_SetPSCfg(mcp,
						numChannels,
						repetitionsCount,
						delayTime,
						scanPolicy,
						coexPriority,
						delayStart);
}

// Generate a wide channel plan using the L4Planner and configure the L4Scanner
wmx_Status_t L4C_SetWS(wmx_LinkLossType_t linkLossType, BOOL delayStart, BOOL isInternal)
{
	wmx_CoexPriority_t coexPriority = COEX_PRIORITY_SCAN_LOW;
	NdsSettings_t settings; // L4db struct
	wmx_ChannelInfo_t mcp[MAX_CHANNELS_NUM];
	UINT32 numChannels = MAX_CHANNELS_NUM;
	int repetitionsCount, delayTime;
	wmx_Status_t rc;
	wmx_Status_t monitorStatus;

	L4db_GetNdsSettings(&settings);
	// TODO: Oran - each channel in the MCP has 0 in the MaxTxPower field
	rc = L4P_GenerateMCP(ScanType_WhileScan, mcp, &numChannels);
	monitorStatus = wmx_PopulateMonitorMCP(mcp,numChannels,linkLossType);

	if (numChannels < 1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetWS: Couldn't generate master channel plan for wide scan. No channels found.");
		return WMX_ST_WRONG_ARGUMENT;
	}

	if (rc != WMX_ST_OK || numChannels == MAX_CHANNELS_NUM)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_SetWS: Couldn't generate master channel plan for preferred scan");
		return WMX_ST_WRONG_ARGUMENT;
	}

	// if we got here - then we have a valid MCP
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetWS: Master channel plan generated and contains %d channels", numChannels);

	// AutoScan / SemiManualScan = COEX_PRIORITY_SCAN_LOW, ManualScan = COEX_PRIORITY_SCAN_HIGH
	// in the current version only manual wide scan is available
	if (TRUE == OSAL_atomic_compareExchange(&g_ndnsContext.isSingleManualScan, (long)TRUE, (long)TRUE)
		&& !isInternal)
	{
		coexPriority = COEX_PRIORITY_SCAN_HIGH;
	}

	if (linkLossType == LinkLossType_Infinite)
	{
		repetitionsCount = MAXSHORT;
		delayTime = (int)(INFINITE_LINK_LOSS_RATIO * settings.longLinkLossParams.time);
	}
	else
	{
		repetitionsCount = settings.longLinkLossParams.repetition;
		delayTime = settings.longLinkLossParams.time;
	}

	//g_ndnsContext.currentScanType = SCAN_TYPE_WIDE;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Link Loss config: Type = %s, Delay = %d sec, Repetitions = %d", wmx_LinkLossType_tStr[linkLossType], delayTime, repetitionsCount);

	return L4S_SetWhileSCfg(mcp,
							numChannels,
							repetitionsCount,
							delayTime,
							coexPriority,
							delayStart);
}


// Configure the L4Scanner to scan a specially targeted plan of selected channels (for example: in a "scan-connect" sequence)
wmx_Status_t L4C_SetTargetedScan(wmx_LinkLossType_t linkLossType, BOOL delayStart)
{
	UNREFERENCED_PARAMETER(linkLossType);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_SetTargetedScan(IN)");

	if (g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize < 1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_SetTargetedScan: Illegal channel plan detected. No channels found.");
		return WMX_ST_WRONG_ARGUMENT;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SetTargetedScan: Master channel plan contains %d channels", g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize);
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_SetTargetedScan(OUT)");

	return L4S_SetPSCfg(g_ndnsContext.scheduledTaskData.scanInfo.chPlan, // master channel plan
		g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize, // channel plan size
		1, // repetition count
		0, // delay time
		SCAN_MODE_FIND_FIRST,
		g_ndnsContext.scheduledTaskData.connectInfo.coexPriority, // For the scan we use the same coex priority as the connect
		delayStart);
}


wmx_Status_t L4C_StartScan(wmx_ScanType_t scanType, wmx_LinkLossType_t linkLossType, BOOL delayStart, BOOL isInternal)
{
	wmx_Status_t status = WMX_ST_OK;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartScan(IN): type = <%s>\tlink loss type = <%s>\ttrigger = <%s%s>",
		wmx_ScanType_tStr[scanType], wmx_LinkLossType_tStr[linkLossType],
		(g_ndnsContext.isSingleManualScan == TRUE ? NDNS_STR_MANUAL : NDNS_STR_AUTOMATIC),
		(delayStart == TRUE ? NDNS_STR_DELAYED : ""));

	g_ndnsContext.linkLossType = linkLossType;
	g_ndnsContext.currentScanType = scanType;

	L4S_EnableScanner(TRUE);
	switch(scanType)
	{
		case SCAN_TYPE_PREFERRED:
		case SCAN_TYPE_RECONNECT:
			status = L4C_SetPS(linkLossType, delayStart, isInternal);
			break;
		case SCAN_TYPE_WIDE:
			status = L4C_SetWS(linkLossType, delayStart, isInternal);
			break;
		case SCAN_TYPE_AUTO_CONNECT:
			status = L4C_SetTargetedScan(linkLossType, delayStart);
			break;
		case SCAN_TYPE_DIRECT:
			// don't read scan settings from the L4DB (overrided)
			break;
	}

	if (status != WMX_ST_OK)
	{
		goto Finalize;
	}

	// send the scan type to the L4 publisher
	L4Pub_UpdateData(L4Pub_CbType_ScanType, (L4Pub_pCallbackParamsUnion)&g_ndnsContext.scheduledTaskData.scanInfo.manualScanType);

	if (L4C_AUTO_SCAN == FSM_GetState(&g_ndnsContext.fsm))
	{
		status = L4S_StartScanner(FALSE);
	}
	else
	{
		status = L4S_StartScanner(TRUE);
	}

Finalize:
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartScan(OUT)");
	return status;
}

wmx_Status_t L4C_StartManualScanPhase2(wmx_ScanType_t scanType, BOOL isInternal)
{
	L4CState fsmState = FSM_GetState(&g_ndnsContext.fsm);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_StartManualScanPhase2(IN) - scanType=%s, isInternal=%d",
		wmx_ScanType_tStr[scanType], isInternal);
	L4S_Reset(TRUE); // reset the L4Scanner

	if (!FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, L4C_SINGLE_SCAN, L4C_SINGLE_SCAN) &&
		(TRUE == OSAL_atomic_compareExchange(&g_ndnsContext.isSingleManualScan, (long)TRUE, (long)TRUE)))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartManualScanPhase2(OUT). Unable to start manual scan since already in single scan state");
		g_ndnsContext.scheduledTaskData.status = WMX_ST_WRONG_STATE;
		FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, fsmState, fsmState); // return to the previous state
		L4C_ScheduleTask(Task_StartScan); // reset the scheduler back to normal scan
		OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, FALSE);
		L4C_SetControllerMode(Ready, FALSE); // trigger the next scan cycle
		goto Finalize;
	}
	OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)TRUE);

	// clear the available NSPs list only if the manual scan was commanded from outside of the ND&S
	if (scanType != SCAN_TYPE_AUTO_CONNECT && scanType != SCAN_TYPE_RECONNECT)
	{
		ClearAvailableNSPsList();
	}
	// the link loss type doesn't matter here since when the auto scan will start again - the link loss type
	// will be chosen based on the type of the scan
	g_ndnsContext.scheduledTaskData.status = L4C_StartScan(scanType, LinkLossType_Short, FALSE, isInternal);
	if (g_ndnsContext.scheduledTaskData.status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartManualScanPhase2(OUT). Unable to start manual scan");
		FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, fsmState, fsmState); // return to the previous state
		L4C_ScheduleTask(Task_StartScan); // reset the scheduler back to normal scan
		OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, FALSE);
		L4C_SetControllerMode(Ready, FALSE); // trigger the next scan cycle
	}

Finalize:
	OSAL_set_event(g_ndnsContext.startManualScanCompletedEvent);

	return g_ndnsContext.scheduledTaskData.status;
}

wmx_Status_t L4C_StartManualScan(wmx_ScanType_t scanType)
{
	L4CState fsmState = FSM_GetState(&g_ndnsContext.fsm);
	wmx_Status_t status = WMX_ST_WRONG_STATE;
	wmx_ScanInfo_t scanInfo;

	// scan requests arriving outside of the ND&S can be only for preferred or wide scan
	if (scanType != SCAN_TYPE_PREFERRED && scanType != SCAN_TYPE_WIDE)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartManualScan(IN)");

	// in case a scan/connect process is taking place, notify device
	if(L4C_GetInitialCoexMode() == WMX_MODE_CM && g_ndnsContext.processStarted)
	{
		L4C_SetProcessStarted(FALSE);
		wmx_CmdProcessEnd();
	}

	if (fsmState == L4C_AUTO_SCAN || fsmState == L4C_SINGLE_SCAN)
	{
		L4C_ScheduleTask(Task_Reset); // reset the L4Controller
		L4S_Reset(FALSE); // reset the L4Scanner

		OSAL_reset_event(g_ndnsContext.startManualScanCompletedEvent);

		scanInfo.manualScanType = scanType;
		scanInfo.isInternal = FALSE;

		pUtils->tpfnPostRequest(MEDIUM, Task_StartManualScan, (void*)&scanInfo, sizeof(wmx_ScanInfo_t), &L4C_TaskHandler);

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Manual scan task was scheduled");

		if (OSAL_wait_event(g_ndnsContext.startManualScanCompletedEvent, L4C_TIMEOUT * 2) != WAIT_OBJECT_0)
		{
			L4C_ScheduleTask(Task_StartScan); // reset the scheduler back to normal scan
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error starting manual scan. Timeout expired !");
			status = WMX_ST_FAIL;
		}
		else
		{
			status = g_ndnsContext.scheduledTaskData.status;
		}
	}
	/*else if (fsmState == L4C_SINGLE_SCAN)
	{
		OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE);
		ClearAvailableNSPsList();
		status = L4C_StartScan(scanType, LinkLossType_Short, FALSE, FALSE);
		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartManualScan. Error starting manual scan. status=%d",status);
		}
	}*/
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartManualScan(OUT). Status: %d", status);

	return status;
}

wmx_Status_t L4C_StartManualScanDirect(UINT8 *pChannelsListBuffer)
{
	L4CState fsmState = FSM_GetState(&g_ndnsContext.fsm);
	wmx_Status_t status = WMX_ST_WRONG_STATE;
	wmx_ScanType_t scanType = SCAN_TYPE_DIRECT;
	int listSize = 0;
	wmx_pChannelInfo_t pList = NULL;
	UINT32 numChannels = 0;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartManualScanDirect(IN)");

	// Copy values from the buffer to each field respectively. (The first 4 bytes of the buffer are the
	// Duplex mode that is not yet supported...)
	OSAL_memcpy_s(&numChannels, sizeof(UINT32), pChannelsListBuffer + sizeof(wmx_DuplexMode_t), sizeof(UINT32));
	OSAL_memcpy_s(&g_ndnsContext.scheduledTaskData.scanInfo.isDirectScanBlocking, sizeof(BOOL), pChannelsListBuffer + sizeof(wmx_DuplexMode_t) + sizeof(UINT32), sizeof(BOOL));
	listSize = sizeof(wmx_ChannelInfo_t) * numChannels;
	pList = (wmx_pChannelInfo_t)malloc(listSize);
	if (NULL == pList)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartManualScanDirect(OUT). malloc error. Could not allocate space for pList!");
		return status;
	}
	OSAL_memcpy_s(pList, listSize, pChannelsListBuffer + sizeof(wmx_DuplexMode_t) + sizeof(UINT32) + sizeof(BOOL), listSize);

	if (fsmState == L4C_SINGLE_SCAN)
	{
		status = L4S_SetPSCfg(pList,
							  numChannels,
							  1, // One scan cycle.
							  0, // No retries interval.
							  SCAN_MODE_FIND_ALL, // in direct scan - we want to scan all the channels
							  COEX_PRIORITY_SCAN_HIGH,
							  FALSE);

		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartManualScan(OUT). Bad status returned from L4S_SetPSCfg. status: %d", status);
		}
		else
		{
			status = L4C_StartScan(scanType, LinkLossType_Short, FALSE, FALSE);
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartManualScan(OUT). Error starting manual scan. status: %d", status);
			}
		}
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_StartManualScan - Error bad state. state: %d", fsmState);
	}

	free(pList);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_StartManualScanDirect(OUT). status: %d", status);
	return status;
}

// send a scan results indication with all the available NSPs
void L4C_SendAvailableNSPsInd()
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;
	UINT32 totalNumOfNsps;
	wmx_NSP_t nsps[WMX_NSPS_MAX_NUM];

	totalNumOfNsps = WMX_NSPS_MAX_NUM;

	GetAvailableNspsList(&totalNumOfNsps, nsps, TRUE);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Sending scan update indication with %d NSPs", totalNumOfNsps);
	PrintAvailableNspsList(TRUE, TR_SEV_NOTICE);

	// size contains space for NSPs + space for NSPs number (UINT32) + space for scanProgress percentage (UINT32)
	msgSize = sizeof(NDNS_MESSAGE) + totalNumOfNsps * sizeof(wmx_NSP_t) + 2 * sizeof(UINT32);
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
	pSendIndData->indication_id = NDNS_OPCODE_IND_SCAN_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_SCAN_UPDATE;
	pIndMsg->bufferLength = totalNumOfNsps * sizeof(wmx_NSP_t) + 2 * sizeof(UINT32);
	*((UINT32*)(pIndMsg->buf)) = totalNumOfNsps;
	*((UINT32*)(pIndMsg->buf + sizeof(UINT32))) = L4S_GetScanProgress();
	OSAL_memcpy_s( pIndMsg->buf + 2 * sizeof(UINT32), totalNumOfNsps * sizeof(wmx_NSP_t), nsps, totalNumOfNsps * sizeof(wmx_NSP_t) );
		pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}

void ProcessAutoConnect(wmx_ScanType_t scanType, wmx_NSPid_t nspId, BOOL isMultiChunk)
{
	BOOL isAutoConnect = FALSE, isSaveInfo = FALSE;

	switch(scanType)
	{
		case SCAN_TYPE_PREFERRED: // if the connect mode is auto connect, connect to the current preferred NSP
			if (ConnectMode_Auto == L4C_GetConnectionMode(L4db_GetConnectMode()) &&
				ScanMode_Manual != L4C_GetScanMode(L4db_GetConnectMode()))
				//L4C_AUTO_SCAN == FSM_GetState(&g_ndnsContext.fsm))
			{
				isAutoConnect = TRUE;
				isSaveInfo = TRUE;
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "User auto connect - connect to current preferred NSP scheduled");
			}
			break;
		case SCAN_TYPE_RECONNECT:
			if (L4db_GetFastReconnectStatus())
			{
				isAutoConnect = TRUE;
				isSaveInfo = TRUE;
				isMultiChunk = FALSE;
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Fast reconnect after scan - auto connect to recent NSP scheduled");
			}
			break;
		case SCAN_TYPE_AUTO_CONNECT:
			isAutoConnect = TRUE;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "\"scan-connect\" sequence - auto connect scheduled. isMultiChunk=%d", isMultiChunk);
			break;
		default:
			break;
	}

	if (isAutoConnect)
	{
		// save the connection info for the next "Ready" system state
		if (isSaveInfo)
		{
			g_ndnsContext.scheduledTaskData.connectInfo.numOfNspIDs = 1;
			g_ndnsContext.scheduledTaskData.connectInfo.coexPriority = COEX_PRIORITY_CONNECT_LOW;
			g_ndnsContext.scheduledTaskData.connectInfo.nspIDs[0] = nspId;
			g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel = FALSE;
		}

		if (!g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel)
		{
			g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect = !isMultiChunk;
			g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel = isMultiChunk;
		}
		else // in case we've already had an iteration with only the last channel - end the scanning and connect
		{
			// this line will ensure that we won't get back here as part of this connect session
			g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect = TRUE;
			g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel = FALSE;
		}

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Auto connect scheduled. forceManualConnect=%d, useOnlyLastChannel=%d", g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect, g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel);


		L4C_ScheduleTask(Task_AutoConnect);
	}
}

BOOL L4C_GetSelectedNSP(wmx_ScanType_t scanType, wmx_pNSPid_t nspId)
{
	BOOL isFound = FALSE;

	// get the selected NSP based on the scan type
	switch(scanType)
	{
	case SCAN_TYPE_RECONNECT:
		// Fast reconnect is done only to the recent connected NSP
		if (L4db_GetRecentNsp(nspId) == WMX_ST_OK) // there are recent NSPs
		{
			isFound = TRUE;
		}
		break;
	case SCAN_TYPE_AUTO_CONNECT:
		// in case of a "scan-connect" cycle - connect only to the saved NSP
		if (g_ndnsContext.scheduledTaskData.connectInfo.numOfNspIDs > 0)
		{
			*nspId = g_ndnsContext.scheduledTaskData.connectInfo.nspIDs[0];
			isFound = TRUE;
		}
		break;
	case SCAN_TYPE_PREFERRED:
		// in preferred scan - search for the current preferred
		if (WMX_ST_OK == L4db_GetCurrentPreferredNsp(nspId) && (wmx_NSPid_t)L4DB_INVALID_INDEX != *nspId)
		{
			isFound = TRUE;
		}
	default:
		break;
	}

	return isFound;
}

// search the selected NSP in the NSPs lists
BOOL L4C_FindSelectedNsp(wmx_pNSP_t homeNsps,
						 UINT32 numOfHomeNSPs,
						 wmx_pAvailableNSP_t unknownNsps,
						 UINT32 numOfUnknownNSPs,
						 wmx_NSPid_t selectedNspId, // the selected NSP id
						 int *selectedIndex,
						 BOOL *isHomeSelected)
{
	BOOL isNspFound = FALSE;
	BOOL isHome = FALSE;
	UINT32 i = 0, j;


	// check if one of the home NSPs is the selected NSP
	for (i = 0; i < numOfHomeNSPs; ++i)
	{
		// for each NSP - go over its IDs
		for (j = 0; j < homeNsps[i].numOfNspIDs; ++j)
		{
			if (homeNsps[i].nspIDs[j] == selectedNspId)
			{
				isNspFound = TRUE;
				isHome = TRUE;
				break;
			}
		}
		if (isNspFound) break;
	}
	if (!isNspFound)
	{
		// check if one of the unknown NSPs is the selected NSP
		for (i = 0; i < numOfUnknownNSPs; ++i)
		{
			if (unknownNsps[i].nspId == selectedNspId)
			{
				isNspFound = TRUE;
				break;
			}
		}
	}

	if (isNspFound)
	{
		*selectedIndex = i;
		*isHomeSelected = isHome;
	}
	return isNspFound;
}

/// Decide which logic to apply for the next scan
/// <returns>True on success
BOOL L4C_ProcessNextScanParams(wmx_ScanType_t scanType,
							 wmx_ScanStatus_t scanStatus,
							 BOOL isNspFound,
							 long *isResumeScan,
							 BOOL *isScanCycleComplete)
{
	BOOL isReconnectRequired = FALSE;
	L4CState l4cState = FSM_GetState(&g_ndnsContext.fsm);
	BOOL res = FALSE;

	// Step 1: error checking
	if (isResumeScan == NULL || isScanCycleComplete == NULL)
	{
		goto Finalize;
	}

	// 0 represents a missing scan complete status
	if ((int)scanStatus == 0)
	{			// the scan of the current chunk is still in progress ->
		goto Finalize; // no scan parameters calculation is required at the moment
	}

	// Step 2: calculate the parameters for the next scan phase
	res = TRUE;
	*isResumeScan = FALSE;
	*isScanCycleComplete = FALSE;

	// This is the first case in which we stop the scan in the middle
	// Found an NSP which is valid for connection
	if (isNspFound)
	{
		*isScanCycleComplete = TRUE;
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Found an NSP which is valid for connection. Ending scan cycle and scheduling the next cycle.");

		if (scanType == SCAN_TYPE_AUTO_CONNECT || scanType == SCAN_TYPE_RECONNECT)
		{
			isReconnectRequired = TRUE;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "This is an auto connect scan cycle. Scheduling a fresh cycle.");
		}
	}

	if (l4cState == L4C_AUTO_SCAN && !isReconnectRequired)
	{	// in auto scan mode - always resume scan on the next state shift
		*isResumeScan = TRUE;
	}

	if (L4S_AreChunksLeft())
	{	// there are more chunks to scan - so resume scan on the next state shift
		*isResumeScan = TRUE;
	}
	else
	{	// no chunks left = the scan cycle has ended
		*isScanCycleComplete = TRUE;
	}
Finalize:
	return res;
}

// Apply the logic for the next scan
void L4C_ApplyNextScanParams(wmx_ScanType_t scanType,
							 wmx_ScanStatus_t scanStatus,
							 long isResumeScan,
							 BOOL isScanCycleComplete,
							 UINT32 numOfNSPs)
{
	L4C_ConnectMode connectionMode = L4C_GetConnectionMode(L4db_GetConnectMode());

	UNREFERENCED_PARAMETER(numOfNSPs);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE,
		"L4C_ApplyNextScanParams (IN) - scanType=%s, scanStatus=%d, isResumeScan=%d, isScanCycleComplete=%d, numOfNSPs=%d",
		wmx_ScanType_tStr[scanType], scanStatus, isResumeScan, isScanCycleComplete, numOfNSPs);
	if (isResumeScan)
	{
		OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, TRUE);
	}
	if (isScanCycleComplete)
	{
		if (initialCoexMode == WMX_MODE_CM)
		{
			wmx_CmdProcessEnd();
		}

		// we don't update (at all) the available NSPs list in 2 cases:
		// 1. when this is a direct scan cycle
		// 2. when this is a "scan-connect" sequence (targeted scan)
		if ((scanType != SCAN_TYPE_AUTO_CONNECT) &&
			(scanType != SCAN_TYPE_DIRECT || g_ndnsContext.scheduledTaskData.scanInfo.isDirectScanBlocking == FALSE))
		{
			//nardimon
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "<---L4db_PrintDiscoveredNAPsList - L4C_ApplyNextScanParams before AgeAvailableNspsList-- >");
			L4db_PrintDiscoveredNAPsList();
			//AgeAvailableNspsList(); // age the list before the next retry
		}
		L4S_EndScanCycle(); // end the scan cycle to allow the next cycle to start from scratch
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_ApplyNextScanParams - before save to DB");
		SaveToDB();

		// send scan results to the user ONLY if in manual connect mode
		// the results will be sent also if no new NSPs were found to allow updating the progress information
		if (/*(numOfNSPs > 0) &&*/ (connectionMode == ConnectMode_Manual) &&
			(scanType != SCAN_TYPE_AUTO_CONNECT) &&
			(scanType != SCAN_TYPE_DIRECT || g_ndnsContext.scheduledTaskData.scanInfo.isDirectScanBlocking == FALSE))
		{
			L4C_SendAvailableNSPsInd();
		}
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Sending scan completed event");
		L4Pub_SendScanCompleted(scanStatus); // send the scan completed event
		L4C_UpdateScanStatus(FALSE); //[Oran]
	}
	else
	{
		// send scan results to the user ONLY if in manual connect mode
		// the results will be sent also if no new NSPs were found to allow updating the progress information
		if (/*(numOfNSPs > 0) &&*/ (connectionMode == ConnectMode_Manual) &&
			(scanType != SCAN_TYPE_AUTO_CONNECT) &&
			(scanType != SCAN_TYPE_DIRECT || g_ndnsContext.scheduledTaskData.scanInfo.isDirectScanBlocking == FALSE))
		{
			L4C_SendAvailableNSPsInd();
		}
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_ApplyNextScanParams (OUT)");
}

void L4C_SaveDetectedChannels(wmx_pNAP_t pNAPs, UINT32 numOfNAPs, L4C_LinkGrade linkGrade)
{
	wmx_ChannelID_t chIds[MAX_CHANNEL_INFO_ID_SIZE];
	UINT32 numOfChIds;
	UINT32 i;
	wmx_Status_t monitorStatus;
	char targetStr[MAX_NAME_STR_LEN];
	DiscoveredNap_t napInfo[WMX_NAPS_MAX_NUM];

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SaveDetectedChannels (IN)");

	// for each NAP - convert channel IDs list to L4DB channel plan (only channels with the specified link grade)
	for (i = 0; i < numOfNAPs; ++i)
	{
		l4db_ConvertNapIdToStr(napInfo[i].napID, targetStr);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SaveDetectedChannels discovered NAP: NAP-ID=%s", targetStr);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SaveDetectedChannels : Copying pNAPs[i].numChannels = [%d]",pNAPs[i].numChannels);
		napInfo[i].channelPlan.channelsSize = MAX_CHANNEL_INFO_ID_SIZE;  // Assign the amount of allocated channels
		napInfo[i].changeCount = pNAPs[i].changeCount;
		numOfChIds = MAX_CHANNEL_INFO_ID_SIZE;
		// save only the channels which are above the threshold
		GetChannelIdsByThreshold(linkGrade, &pNAPs[i], chIds, &numOfChIds);
		L4S_ConvertChIdsToChPlan(pNAPs[i], pNAPs[i].numChannels, napInfo[i].channelPlan.channels, &napInfo[i].channelPlan.channelsSize);
		napInfo[i].isLastDetected = TRUE;
		OSAL_memcpy_s(napInfo[i].napID, sizeof(wmx_NAPid_t), pNAPs[i].bsCriteria.bsID, sizeof(wmx_NAPid_t));
		napInfo[i].nspInfoSize = 0; // no 16G NSP info
		memset(&napInfo[i].channelPlan.linkQuality,0x00,(WMX_CHANNELS_MAX_NUM*(sizeof (wmx_LinkQuality_t))));
		OSAL_memcpy_s(&napInfo[i].channelPlan.linkQuality, (pNAPs[i].numChannels*(sizeof (wmx_LinkQuality_t))), pNAPs[i].linkQuality,(pNAPs[i].numChannels*(sizeof (wmx_LinkQuality_t))));
		L4db_SetDiscoveredNapInfo(&napInfo[i], &pNAPs[i]);
		monitorStatus = wmx_PopulateMonitorRecentDiscoverNap(&napInfo[i], pNAPs[i].bsCriteria.bsID);
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_SaveDetectedChannels (OUT)");

}

// process the detected NAPs and convert them to NSPs
// <return>Number of NSPs</return>
UINT32 L4C_UpdateAvailableNSPsList(wmx_pScanResults_t scanResults,
								 L4C_LinkGrade linkGrade,
								 BOOL *isScanCycleComplete,
								 long *isResumeScan,
								 BOOL *isNspFound,
								 wmx_pNSPid_t nspId)
{
	UINT32 numOfNsps = WMX_NSPS_MAX_NUM;
	wmx_NSP_t nsps[WMX_NSPS_MAX_NUM];
	wmx_BSid_t bsIds[WMX_NSPS_MAX_NUM]; // the bsIds corresponding to the nsps array
	wmx_BsIdType_t bsIdsTypes[WMX_NSPS_MAX_NUM];
	UINT32 numOfFakeNsps = WMX_NSPS_MAX_NUM;
	wmx_AvailableNSP_t fakeNsps[WMX_NSPS_MAX_NUM];
	wmx_NAP_t napsWithNoNSP[WMX_NAPS_MAX_NUM];
	UINT32 numOfNapsWithNoNSP = WMX_NAPS_MAX_NUM;
	wmx_BSid_t selectedBsId;
	wmx_BsIdType_t selectedBsIdType;
	UINT32 selectedNAPindex;
	int nspIndex=0;
	BOOL isHomeSelected = FALSE;
	BOOL isFindFirstMode = FALSE;
	BOOL bFoundNSP = FALSE;

	BOOL isUseUnderThreshold = linkGrade == LinkGrade_BelowThr ? TRUE : FALSE;

	UINT32 showUnknownNSPs = 0;
	UINT i;

	memset(nsps, 0, sizeof(wmx_NSP_t) * WMX_NSPS_MAX_NUM);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "<---L4db_PrintDiscoveredNAPsList - isUseUnderThreshold == [%d]  -- >", isUseUnderThreshold);
	*isNspFound = FALSE;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "<---L4db_PrintDiscoveredNAPsList - L4C_UpdateAvailableNSPsList  before NAPs2NSPs-- >");
	L4db_PrintDiscoveredNAPsList();

	// Convert all the NAPs to NSPs, and then only the good signal results.
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "<-- Before NAPs2NSPs isUseUnderThreshold=[%d]  -->", isUseUnderThreshold);
	bFoundNSP = NAPs2NSPs(scanResults->NAPsCount,
							scanResults->NAPs,
							&numOfNsps,
							nsps,
							bsIds,
							bsIdsTypes,
							&numOfNapsWithNoNSP,
							napsWithNoNSP,
							isUseUnderThreshold);

	// NAP to NSP conversion completed successfully
	if (bFoundNSP && (numOfNsps>0 || numOfNapsWithNoNSP>0))
	{
		L4Configurations_getShowUnkownNSPs(&showUnknownNSPs);
		// Create fake NSPs for the NAPs that don't relate to an NSP
		if (numOfNapsWithNoNSP > 0 && showUnknownNSPs /*&& L4db_GetAllowAutoActivate() == TRUE*/)
		{
			CreateFakeAvailableNSPsFromNaps(numOfNapsWithNoNSP, napsWithNoNSP, &numOfFakeNsps, fakeNsps);
		}
		else
		{
			if (numOfNapsWithNoNSP > 0)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Filtered %d unknown NSPs from scan results", numOfNapsWithNoNSP);
			}
			numOfNapsWithNoNSP = 0; // Don't support option 3 (unmapped NAPs)
			numOfFakeNsps = 0;
		}

		// get the selected NSP (if the NSP is found then we are in a find first scan mode)
		isFindFirstMode = L4C_GetSelectedNSP(g_ndnsContext.currentScanType, nspId);

		if (isFindFirstMode)
		{
			*isNspFound = L4C_FindSelectedNsp(nsps,
				numOfNsps,
				fakeNsps,
				numOfFakeNsps,
				*nspId,
				&nspIndex,
				&isHomeSelected);

			// during Find First mode - add only the selected nsp (if it exists) to the available NSPs list
			// if this is a "scan-connect" sequence - don't update the available NSPs list
			if (*isNspFound && g_ndnsContext.currentScanType != SCAN_TYPE_AUTO_CONNECT)
			{
				if (isHomeSelected)
				{
					AddMultipleNSPsToAvailableNSPsList(1, &nsps[nspIndex], &bsIds[nspIndex], &bsIdsTypes[nspIndex]);
				}
				else
				{
					AddMultipleFakeNSPsToAvailableNSPsList(1, &fakeNsps[nspIndex]);
				}
			}
		}
		else // in Find All mode - add all the detected NSPs
		{
			// Add all the unknown NSPs to the Available NSPs list
			AddMultipleFakeNSPsToAvailableNSPsList(numOfFakeNsps, fakeNsps);
			// Add all the provisioned NSPs to the Available NSPs list
			AddMultipleNSPsToAvailableNSPsList(numOfNsps, nsps, bsIds, bsIdsTypes);
		}

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Found %d provisioned and %d unknown NSPs. Trying to add them to the available NSPs list", numOfNsps, numOfFakeNsps);
	}
	else // NAP to NSP conversion failed
	{
		numOfNsps = 0;
		numOfFakeNsps = 0;
	}
	L4C_ProcessNextScanParams(g_ndnsContext.currentScanType,
		scanResults->scanStatus,
		*isNspFound,
		isResumeScan,
		isScanCycleComplete);
	// save the ALL the detected channels which are above the threshold
	if (linkGrade == LinkGrade_AboveThr)
	{
		// for each NAP - convert channel IDs list to L4DB channel plan
		L4C_SaveDetectedChannels(scanResults->NAPs, scanResults->NAPsCount, linkGrade);
	}
	else // save SPECIFIC detected channels which are below the threshold
	{
		if (isFindFirstMode)
		{
			if (*isNspFound)
			{
				// find the BsId of the selected NSP
				if (isHomeSelected)
				{
					OSAL_memcpy_s(selectedBsId, sizeof(wmx_BSid_t), &bsIds[nspIndex], sizeof(wmx_BSid_t));
					selectedBsIdType = bsIdsTypes[nspIndex];
				}
				else
				{
					OSAL_memcpy_s(selectedBsId, sizeof(wmx_BSid_t), &fakeNsps[nspIndex].bsId, sizeof(wmx_BSid_t));
					selectedBsIdType = fakeNsps[nspIndex].bsIdType;
				}

				// find the corresponding NAP to the above selected BsId
				for (i = 0; i < scanResults->NAPsCount; ++i)
				{
					if (IsBsIdEqual(scanResults->NAPs[i].bsCriteria.bsID, selectedBsId, selectedBsIdType))
					{
						selectedNAPindex = i;
						break;
					}
				}

				// save the detected channels of the NAP corresponding to the selected NSP
				if (i == scanResults->NAPsCount)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4C_UpdateAvailableNSPsList: error finding a matching NAP for the selected NSP. Detected channels discarded.");
				}
				else
				{
					if (scanResults->scanStatus != ScanExhausted) 
					{
						L4C_SaveDetectedChannels(&scanResults->NAPs[i], 1, linkGrade);
					}
				}
			}
		}
		else // find all
		{
			if (scanResults->scanStatus != ScanExhausted) 
			{
				L4C_SaveDetectedChannels(scanResults->NAPs, scanResults->NAPsCount, linkGrade);
			}
			// for each NAP - convert channel IDs list to L4DB channel plan
			
		}
	}

	wmx_MonitorSendScanResults(scanResults, nsps, numOfNsps);

	return numOfNsps + numOfFakeNsps;
}

// Add the scan results to the available NSPs list
// and optionally send indication to the user, schedule the next scan and connect to a selected NSP (NAP)
wmx_Status_t L4C_ProcessScanResults(wmx_pScanResults_t scanResults)
{
	wmx_Status_t status;
	UINT32 totalNumOfNSPs = 0;
	wmx_NSPid_t nspId;
	BOOL isNspFound = FALSE;
	BOOL isScanCycleComplete = FALSE;
	long isResumeScan = FALSE;
	BOOL isMultiChunk = FALSE;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_ProcessScanResults(IN)");

	if (g_ndnsContext.currentScanType == SCAN_TYPE_DIRECT && g_ndnsContext.scheduledTaskData.scanInfo.isDirectScanBlocking)
	{
		L4C_ProcessNextScanParams(g_ndnsContext.currentScanType, scanResults->scanStatus, FALSE, &isResumeScan, &isScanCycleComplete);
		L4C_ApplyNextScanParams(g_ndnsContext.currentScanType,
								scanResults->scanStatus,
								isResumeScan,
								isScanCycleComplete,
								0);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_ProcessScanResults(OUT) - manual scan direct and blocking");
		return WMX_ST_OK;
	}

	// temporarily save the NAPs that have channels beneath the threshold (if exist).
	// When the scan cycle ends - use these NAPs if there are no better results
	if (scanResults->NAPsCount > 0)
	{
		AddNAPsBeneathThreshold(scanResults->NAPsCount, scanResults->NAPs);
	}

	// first process all the results that have good link grade
	totalNumOfNSPs = L4C_UpdateAvailableNSPsList(scanResults, LinkGrade_AboveThr, &isScanCycleComplete, &isResumeScan, &isNspFound, &nspId);

	// If there are no results and no chunks left, try to use the results that are under the threshold (linkGrade == FALSE)
	if (isScanCycleComplete && !isNspFound)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4C_ProcessScanResults - Scan complete and no NSP found");
		scanResults->NAPsCount = WMX_NAPS_MAX_NUM;
		// Fetch the "bad" results
		status = GetNapsBeneathThreshold(&scanResults->NAPsCount, scanResults->NAPs);
		if (scanResults->NAPsCount > 0)
		{
			// second phase (end of scan cycle) - process all the results that have bad link grade
			totalNumOfNSPs += L4C_UpdateAvailableNSPsList(scanResults, LinkGrade_BelowThr, &isScanCycleComplete, &isResumeScan, &isNspFound, &nspId);
			// since we got to the end of the scan cycle - the source of the bad results may be != last chunk
			isMultiChunk = TRUE;
		}
	}

	// apply the "end of scan chunk" logic (report scan results to the user, set params for next chunk to scan etc.)
	L4C_ApplyNextScanParams(g_ndnsContext.currentScanType,
							scanResults->scanStatus,
							isResumeScan,
							isScanCycleComplete,
							totalNumOfNSPs);

	// if required - start an auto connect sequence
	if (isNspFound)
	{
		ProcessAutoConnect(g_ndnsContext.currentScanType, nspId, isMultiChunk);
	}

	if (totalNumOfNSPs < 1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_ProcessScanResults(OUT) - WMX_ST_NSP_ID_NOT_FOUND");
		status = WMX_ST_NSP_ID_NOT_FOUND;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_ProcessScanResults(OUT)");
		status = WMX_ST_OK;
	}

	return status;
}


void NDnSAgent_MessagesHandler(	L5_CONNECTION Conn,
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
	wmxApdo_FunctionParamStruct functionParamStruct;
	wmx_NSPid_t currentPreferredNspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
	wmx_pContactInfoParams params;
	wmx_Status_t status = WMX_ST_OK;

	if(pdwResponseMessageID == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Illegal message. pdwResponseMessageID == NULL");
		nds_pFuncs->pfnSendErrorReport(L5_TARGET_NDNS, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}

	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbSentBufferSize);
	UNREFERENCED_PARAMETER(Conn);


	switch (dwSentMessageID)
	{
		case NDNS_OPCODE_REGISTER_INDICATION:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: NDNS_OPCODE_REGISTER_INDICATION");
			*pdwResponseMessageID = NDnSAgent_RegisterIndicator(nOriginID, *(UINT32*)pvSentBuffer);
			break;

		case NDNS_OPCODE_UNREGISTER_INDICATION:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: NDNS_OPCODE_UNREGISTER_INDICATION");
			*pdwResponseMessageID = NDnSAgent_UnRegisterIndicator(nOriginID, *(UINT32*)pvSentBuffer);
			break;

		case NDNS_OPCODE_COMMAND:
			// Commands for manual and auto mode
			switch (*(UINT32*)pvSentBuffer)
			{
				case NDNS_OPCODE_RF_ON:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got RF On command");
					*pdwResponseMessageID = NDnSAgent_RfOn();
					return;
				case NDNS_OPCODE_RF_OFF:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got RF Off command");
					*pdwResponseMessageID = NDnSAgent_RfOff();
					return;
				default:

					//TODO: Oran - check implementation - update based on fsm states
					// In case of auto connect mode only the above commands are allowed
					/*if (UserSemiManScanAutoConnect == L4db_GetConnectMode() || UserAutoScanAutoConnect == L4db_GetConnectMode())
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "connect mode is auto - illegal command");
						*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
						return;
					}*/
					break;
			}

			// Commands for manual mode only
			switch (*(UINT32*)pvSentBuffer)
			{
				case NDNS_OPCODE_START_SCAN:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Start Scan command");

					*pdwResponseMessageID = L4C_StartManualScan(*(wmx_pScanType_t)(((pNDNS_MESSAGE)pvSentBuffer)->buf));

					break;
				case NDNS_OPCODE_START_SCAN_DIRECT:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Start Scan Direct command");
					*pdwResponseMessageID = L4C_StartManualScanDirect((UINT8 *)(((pNDNS_MESSAGE)pvSentBuffer)->buf));
					break;

				case NDNS_OPCODE_STOP_SCAN:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Stop Scan command");
					*pdwResponseMessageID = NDnSAgent_StopScan();
					break;

				case NDNS_OPCODE_CONNECT:
					if( (NULL == cbResponseBufferSize) ||
						(NULL == pvResponseBuffer) )
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "one of the response out arguments is null");
						*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
						break;
					}

					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Connect command");
					*pdwResponseMessageID = NDnSAgent_Connect(
						*(wmx_pConnectParams)(((pNDNS_MESSAGE)pvSentBuffer)->buf), COEX_PRIORITY_CONNECT_HIGH, (wmx_pUserConnectStatus_t)pvResponseBuffer );
					break;

				case NDNS_OPCODE_DISCONNECT:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Disconnect command");
					*pdwResponseMessageID = NDnSAgent_Disconnect();
					break;

				default:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Unsupported NDNS_OPCODE, *(UINT32*)pvSentBuffer==%d", *(UINT32*)pvSentBuffer);
					*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
					nds_pFuncs->pfnSendErrorReport(L5_TARGET_NDNS, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
					break;
			}
			break;

		case NDNS_OPCODE_GET:
			if( (NULL == cbResponseBufferSize) ||
				(NULL == pvResponseBuffer) )
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "one of the response out arguments is null");
				*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
				break;
			}

			switch(*(UINT32*)pvSentBuffer)
			{

				case NDNS_OPCODE_GET_CONNECTED_NSP:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Connected_NSPs command");
					*pdwResponseMessageID = NDnSAgent_GetConnectedNSP( (UINT32*)cbResponseBufferSize, pvResponseBuffer );
					break;

				case NDNS_OPCODE_GET_LAST_KNOWN_NSP_IDS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Last_Known_NSPs command");
					*pdwResponseMessageID = NDnSAgent_GetLastKnownNspIDs( (UINT32*)cbResponseBufferSize, pvResponseBuffer );
					break;

				case NDNS_OPCODE_GET_SLA:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_SLA command");
					*pdwResponseMessageID = NDnSAgent_GetSLA( ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength, (UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, *(UINT32*)cbResponseBufferSize, pvResponseBuffer );
					break;
				case NDNS_OPCODE_GET_LINK_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Link_Status command");
					*pdwResponseMessageID = NDnSAgent_GetLinkStatus((UINT32*)cbResponseBufferSize, pvResponseBuffer );
					break;
				case NDNS_OPCODE_GET_STATISTICS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Statistics command");
					*pdwResponseMessageID = NDnSAgent_GetStatistics((UINT32*)cbResponseBufferSize, pvResponseBuffer );
					break;
				case NDNS_OPCODE_GET_CONNECTION_MODE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Connect_Mode command");
					*pdwResponseMessageID = GetConnectMode(pvResponseBuffer, cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_ROAMING_MODE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Roaming_Mode command");
					*pdwResponseMessageID = GetRoamingMode(pvResponseBuffer, cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_DEVICE_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get device status");
					*pdwResponseMessageID = L4Pub_GetDeviceStatus(pvResponseBuffer, (UINT32*)cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_PACKAGE_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get package info");
					*pdwResponseMessageID = GetPackageInfo(pvResponseBuffer, (UINT32*)cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_WMF_COMPLIANCE_VER:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get installation info");
					*pdwResponseMessageID = GetWMFComplianceInfo(pvResponseBuffer, *(UINT32*)cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_INSTALLATION_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get installation info");
					*pdwResponseMessageID = GetInstallationInfo(pvResponseBuffer, (UINT32*)cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_COEXISTANCE_MODE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Coexistence_Mode command");
					*pdwResponseMessageID = GetCoexistenceMode(pvResponseBuffer, cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_FAST_RECONNECT_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got GetFastReconnectStatus command");
					*pdwResponseMessageID = GetFastReconnectStatus(pvResponseBuffer, cbResponseBufferSize);
					break;
				case NDNS_OPCODE_GET_CURRENT_PREFERRED_NSP:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got NDNS_OPCODE_GET_CURRENT_PREFERRED_NSP command");
					*pdwResponseMessageID = GetCurrentPreferredNSP((wmx_pNSP_t)pvResponseBuffer, cbResponseBufferSize);
					break;

				case NDNS_OPCODE_GET_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got GetConnectedAsCurrentPreferredCapabilityStatus");
					*pdwResponseMessageID = GetConnectedAsCurrentPreferredCapabilityStatus(pvResponseBuffer, cbResponseBufferSize);
					break;
				case NDNS_OPCODE_GET_PNM_REQUESTED_CHANNEL:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get PNM Requested Channel");
					*pdwResponseMessageID = L4db_GetPNM(pvResponseBuffer, (UINT32*)cbResponseBufferSize);
					break;
				case NDNS_OPCODE_GET_IS_PNM_COMM_DEV_USING_CHANNEL:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get Is Channel aquired by the device");
					*pdwResponseMessageID = L4C_GetIsPNMCommDevUsingChannel(((pNDNS_MESSAGE)pvSentBuffer)->buf, &((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;

				default:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Unsupported NDNS_OPCODE, *(UINT32*)pvSentBuffer==%d", *(UINT32*)pvSentBuffer);
					*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
					nds_pFuncs->pfnSendErrorReport(L5_TARGET_NDNS, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
					break;
			}
			break;
		case NDNS_OPCODE_SET:
			switch(((pNDNS_MESSAGE)pvSentBuffer)->opcode)
			{
				case NDNS_OPCODE_SET_CONNECTION_MODE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Set_Connection_Mode command");
					*pdwResponseMessageID = SetConnectMode((wmx_pUserConnectMode_t)(((pNDNS_MESSAGE)pvSentBuffer)->buf), ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;

				case NDNS_OPCODE_SET_ROAMING_MODE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Set_Roaming_Mode command");
					*pdwResponseMessageID = SetRoamingMode(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;

				case NDNS_OPCODE_SET_MSCHAP_V2_CRD:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Set_MSChap_V2Crd command");
					*pdwResponseMessageID = NDnSAgent_setMSChap_v2Crd(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;

				case NDNS_OPCODE_SET_COEXISTANCE_MODE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Set_Coex_Mode command");
					*pdwResponseMessageID = SetCoexistanceMode(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;

				case NDNS_OPCODE_SET_FAST_RECONNECT_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got SetFastReconnectStatus command");
					*pdwResponseMessageID = SetFastReconnectStatus(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_SET_CURRENT_PREFERRED_NSP:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got NDNS_OPCODE_SET_CURRENT_PREFERRED_NSP command");
					*pdwResponseMessageID = SetCurrentPreferredNSP(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;


				case NDNS_OPCODE_SET_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got SetConnectedAsCurrentPreferredCapabilityStatus command");
					*pdwResponseMessageID = SetConnectedAsCurrentPreferredCapabilityStatus(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;

				default:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Unsupported NDNS_OPCODE, ((pNDNS_MESSAGE)pvSentBuffer)->opcode==%d", ((pNDNS_MESSAGE)pvSentBuffer)->opcode);
					*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
					nds_pFuncs->pfnSendErrorReport(L5_TARGET_NDNS, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
					break;
			}
			break;
		case NDNS_OPCODE_APDO:
			switch(((pNDNS_MESSAGE)pvSentBuffer)->opcode)
			{
				case NDNS_OPCODE_GET_POLLING_SUPPORTED:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_DevCap command");
					*pdwResponseMessageID = NDnSAgent_GetPollingSupported(pvResponseBuffer,cbResponseBufferSize);
					break;
				case NDNS_OPCODE_GET_APDO_OPERATOR_CONFIGURATIONS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got wmx_GetApdoOperatorConfigurations command");
					*pdwResponseMessageID = GetApdoOperatorsConfigurations( pvResponseBuffer);
					break;
				case NDNS_OPCODE_GET_CONNECTED_NSP_FOR_APDO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got GET_CONNECTED_NSP_FOR_APDO command");
					*pdwResponseMessageID = GetConnectedNSPForAPDO( cbResponseBufferSize, pvResponseBuffer );
					break;
				case NDNS_OPCODE_GET_BEK:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got wmx_GetBEK command");
					*pdwResponseMessageID = GetBEK( pvResponseBuffer);
					break;
				case NDNS_OPCODE_GET_APDO_INFO:
					//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"NDnSAgent_MessagesHandler: got Get_APDO_Info command");
					*pdwResponseMessageID = GetAPDOinfo(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength, pvResponseBuffer);
			//		*cbResponseBufferSize = (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength; // TODO: Set the real size of the return buffer
					break;
				case NDNS_OPCODE_ADD_APDO_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Add_APDO_Info command");
					*pdwResponseMessageID = AddAPDOinfo(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_UPDATE_APDO_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Update_APDO_Info command");
					*pdwResponseMessageID = UpdateAPDOinfo(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_DELETE_APDO_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Delete_APDO_Info command");
					*pdwResponseMessageID = DeleteAPDOinfo(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_EXECUTE_APDO_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "execute APDO info");
					*pdwResponseMessageID = ExecuteAPDOinfo(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_GET_APDO_LINK_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Get APDO Link Status");
					*pdwResponseMessageID = GetApdoLinkStatus(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength, pvResponseBuffer);
					break;
				case NDNS_OPCODE_GET_APDO_DHCP_HOST_NAME:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Get APDO DHCP host name");
					*pdwResponseMessageID = GetHostName(pvResponseBuffer, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_APDO_SET_PACKAGE_PATH:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Set package path");
					*pdwResponseMessageID = APDOSetPackagePath(((pNDNS_MESSAGE)pvSentBuffer)->buf, (UINT32*)&((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_GET_NSP_CONTACT_INFO_BY_NAME:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get nsp contact info by name");
					params = (wmx_pContactInfoParams)((pNDNS_MESSAGE)pvSentBuffer)->buf;
					*pdwResponseMessageID = GetNSPContactInfoByName(params->nspName, pvResponseBuffer, cbResponseBufferSize);
					break;
				case NDNS_OPCODE_GET_CONTACT_INFORMATION:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "get contact info");
					*pdwResponseMessageID = GetContactInfo(*(wmx_pNSPid_t)((pNDNS_MESSAGE)pvSentBuffer)->buf, pvResponseBuffer, cbResponseBufferSize);
					break;
				case NDNS_OPCODE_DEPROVISION_NSP:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Deprovision_NSP command");

					status = WMX_ST_OK;

					// If we are in state different then RF-OFF return fail
					if (g_ndnsContext.systemState != RfOff)
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Deprovision NSP not possible when system state=[%d].", g_ndnsContext.systemState);
						status = WMX_ST_FAIL;
					}
					else
					{
						// Check if the deprovisioned NSP is the current preferred NSP
						if ((WMX_ST_OK == L4db_GetCurrentPreferredNsp(&currentPreferredNspID)) &&
							(currentPreferredNspID == *(wmx_pNSPid_t)(((pNDNS_MESSAGE)pvSentBuffer)->buf)))
						{
							currentPreferredNspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
							status = SetCurrentPreferredNSPEx(&currentPreferredNspID, 1);
						}
					}
					if (status == WMX_ST_OK)
					{
						*pdwResponseMessageID = L4db_DeProvisionNsp(*(wmx_pNSPid_t)(((pNDNS_MESSAGE)pvSentBuffer)->buf));
					}
					else // In case the current preferred NSP could not be changed
					{
						*pdwResponseMessageID = status;
					}
					break;
				case NDNS_OPCODE_RESTORE_BACKUP_PROVISIONING_DATABASE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "restore backup provisioning database");
					*pdwResponseMessageID = RestoreBckProvisioningDB();
					break;
				case NDNS_OPCODE_RESTORE_FACTORY_SETTINGS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "restore factory settings");
					*pdwResponseMessageID = RestoreFactorySettings();
					break;
				case NDNS_OPCODE_SET_PACKAGE_UPDATE_STATE:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got Set_Package_Update_State command");
					*pdwResponseMessageID = NDnSAgent_ApdoSetPackageUpdateState(*(wmx_pPackageUpdateState_t)(((pNDNS_MESSAGE)pvSentBuffer)->buf));
					break;
				case NDNS_OPCODE_GET_UNPROVISIONED_NSP_IDS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Unprovisioned_NSP_IDs command");
					*pdwResponseMessageID = GetUnprovisionedNspIDs((UINT32*)cbResponseBufferSize, (wmx_pNSPid_t)pvResponseBuffer);
					break;
				case NDNS_OPCODE_GET_PROVISIONED_NSP_IDS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_Provisioned_NSP_IDs command");
					*pdwResponseMessageID = GetProvisionedNspIDs((UINT32*)cbResponseBufferSize, (wmx_pNSPid_t)pvResponseBuffer);
					break;
				case NDNS_OPCODE_GET_NSP_INFO:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got Get_NSP_Info command");
					*pdwResponseMessageID = GetNspInfo(*(wmx_NSPid_t*)((pNDNS_MESSAGE)pvSentBuffer)->buf, (wmx_pNSP_t)pvResponseBuffer);
					break;
				case NDNS_OPCODE_GET_SERVICE_PROVIDER_LOCK_STATUS:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_MessagesHandler: got GET_SERVICE_PROVIDER_LOCK_STATUS command");
					*pdwResponseMessageID = GetServiceProviderLockStatus(pvResponseBuffer, cbResponseBufferSize);
					break;
				case NDNS_OPCODE_SET_SERVICE_PROVIDER_UNLOCK:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_MessagesHandler: got SET_SERVICE_PROVIDER_UNLOCK command");
					*pdwResponseMessageID = SetServiceProviderUnlock(((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength);
					break;
				case NDNS_OPCODE_APDO_TYPE:
					functionParamStruct = *(wmxApdo_pFunctionParamStruct)((pNDNS_MESSAGE)pvSentBuffer)->buf;

					switch (functionParamStruct.FunctionType)
					{
						case APDO_ApdoSessionStatus:
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "set APDO session status");
							HandleApdoSessionStatus(functionParamStruct.FuncParamUnion.ApdoSessionStatusStruct.sessionStatus);
							break;
						case APDO_AlertNotification:
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "alert notification");
							NDnSAgent_AlertNotification((wmxApdo_pFunctionParamStruct)((pNDNS_MESSAGE)pvSentBuffer)->buf);
							break;
						case APDO_StoreProvisioningClientCfgDataBlobStruct:
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Store provisioning client cfg data blob");
							break;
						case APDO_GetProvisioningClientCfgDataBlobStruct:
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Get provisioning client cfg data blob");
							break;
						case APDO_FumoUpdate:
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Update FUMO downloads");
							HandleFumoUpdate(functionParamStruct.FuncParamUnion.fumoUpdateContent);
							break;
						default:
							break;
					}

					*pdwResponseMessageID = WMX_ST_OK;
				//	*pdwResponseMessageID = SetAPDOSessionStatus(*(wmx_ApdoSessionStatus_t*)((pNDNS_MESSAGE)pvSentBuffer)->buf);
					break;
				default:
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Unsupported NDNS_OPCODE");
					*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
					ASSERT();
					break;
			}
			break;
		default: //Unsupported NDNS_OPCODE
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Unsupported NDNS_OPCODE, dwSentMessageID==%d", dwSentMessageID);
			*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
			nds_pFuncs->pfnSendErrorReport(L5_TARGET_NDNS, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
			break;
	}

	if (*pdwResponseMessageID != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Error in response message = %s", wmxGetStatusStr(*pdwResponseMessageID));
	}
}


// TODO: Oran - remove
// Extracts the requested NSP from the nspBuffer, finds the appropriate SLA and enters it to the slaBuffer
wmx_Status_t NDnSAgent_GetSLA( UINT32 nspIDBufferLength, UINT8 *nspIDBuffer, UINT32 slaBufferLength, UINT8 *slaBuffer )
{
	wmx_Status_t status = WMX_ST_DATA_UNAVAILABLE;

	if ( (nspIDBufferLength != sizeof(wmx_NSPid_t)) || (slaBufferLength != sizeof(wmx_SLA_t)) )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	UNREFERENCED_PARAMETER(slaBuffer);
	UNREFERENCED_PARAMETER(nspIDBuffer);

// TODO: SLA is not supported by the DB
//	status = NdsDB_GetSLA(*(wmx_pNSPid_t)nspIDBuffer, (wmx_pSLA_t)slaBuffer);

	return status;
}

// Get the last found NAPs (from the last scan). Translate the NAPs to NSP IDs and return them in a buffer
// Assums that NSP ID doesn't appear twice in two different NSPs. Return one ID of each NSP.
wmx_Status_t NDnSAgent_GetLastKnownNspIDs( UINT32 *bufferLength, UINT8 *buffer )
{
	wmx_Status_t status;
	errno_t err;
	UINT32 returnedNumberOfNSP = 0;
	UINT32 numOfNSPs = WMX_NSPS_MAX_NUM;
	wmx_NSP_t pNSPs[WMX_NSPS_MAX_NUM];
	UINT32 i;
	BOOL roamingDisabled = FALSE;

	// This API can't be called during provisioning
	if (Ndns_GetProvisioningStarted() == TRUE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Failed NDnSAgent_GetLastKnownNspIDs - called during provisioning.");
		return WMX_ST_FAIL;
	}

	//UINT32 numOfNAPs = WMX_NAPS_MAX_NUM;
	//wmx_NAP_t pNAPs[WMX_NAPS_MAX_NUM];

// TODO: Add support when nsp id is given
//	if (L4db_GetRoamingMode() == UserDisableRoaming)
	{
		roamingDisabled = FALSE;
	}

	GetAvailableNspsList(&numOfNSPs, pNSPs, TRUE);
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "GetLastKnownNspIDs - num of NSPs fetched = %d", numOfNSPs);
	PrintAvailableNspsList(TRUE, TR_SEV_INFO);

	//// TODO: make sure that there is no limit on the NAPs size
	//wmx_GetLastKnownNAPs(&numOfNAPs, pNAPs);
	//if( NAPs2NSPs( numOfNAPs, pNAPs, &numOfNSPs, pNSPs ) == FALSE )
	//{
	//	return WMX_ST_FAIL;
	//}

	// Make sure that the buffer is in a correct size
	if ( numOfNSPs <= (*bufferLength / sizeof(wmx_NSPid_t)) )
	{
		status = WMX_ST_OK;
	}
	else
	{
		numOfNSPs = (*bufferLength / sizeof(wmx_NSPid_t));
		status = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
	}

	// Run over the NSPs and copy the IDs to the result buffer
	for (i = 0; i < numOfNSPs; ++i)
	{
		// If roaming is disabled return only the home NSPs
		if (pNSPs[i].isHomeNSP == FALSE && roamingDisabled == TRUE) continue;

		// Make sure that the found NSP has an ID
		if (pNSPs[i].numOfNspIDs <= 0)
		{
			continue;
		}


		err = OSAL_memcpy_s( buffer + sizeof(UINT32) + returnedNumberOfNSP*sizeof(wmx_NSPid_t), sizeof(wmx_NSPid_t), &(pNSPs[i].nspIDs[0]), sizeof(wmx_NSPid_t) );

		if( err != 0 )
		{
			status = WMX_ST_FAIL;
		}
		returnedNumberOfNSP++;
	}

	*bufferLength = sizeof(UINT32) + (returnedNumberOfNSP * sizeof(wmx_NSPid_t));

	// The number of NSPs is returned as a UIN32 in the first 4 bytes of the buffer
	*(UINT32*)buffer = returnedNumberOfNSP;

	return status;
}


wmx_Status_t NDnSAgent_GetLinkStatus( UINT32 *bufferLength, UINT8 *buffer )
{
	wmx_Status_t status=WMX_ST_OK;
	wmx_pUserLinkStatus_t userLinkStatus;
	//static wmx_LinkStatus_t linkStatus;
	static BOOL fIsLastTimeWasIdle = FALSE;
	BOOL fIsCacheState;

	if (*bufferLength < sizeof(wmx_UserLinkStatus_t))
	{
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	userLinkStatus = (wmx_pUserLinkStatus_t)buffer;

	if (FSM_GetState(&g_ndnsContext.fsm) != L4C_CONNECTED)
	{
		return WMX_ST_WRONG_STATE;
	}

	fIsCacheState = (g_ndnsContext.systemState == Idle);

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "NDnSAgent_GetLinkStatus - device status = %s", NDnSSystemStates[g_ndnsContext.systemState>=UnknownState?UnknownState:g_ndnsContext.systemState]);

	//get the information also for cases the AppSrv reset while in DataPathConnected
	if( !fIsCacheState ||
		(0 == g_linkStatus.rssi && 0 == g_linkStatus.cinr))
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "NDnSAgent_GetLinkStatus - Data From device");
		status = wmx_GetLinkStatus(&g_linkStatus);

	}
	else
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "NDnSAgent_GetLinkStatus - Data From Cache");
	}

	userLinkStatus->cinr = g_linkStatus.cinr;
	userLinkStatus->downLinkSpeed = g_linkStatus.downLinkSpeed;
	userLinkStatus->upLinkSpeed = g_linkStatus.upLinkSpeed;
	userLinkStatus->frequency = g_linkStatus.frequency;

	userLinkStatus->linkQuality = g_linkStatus.linkQuality;
	OSAL_memcpy_s(userLinkStatus->bsId, sizeof(wmx_BSid_t), g_linkStatus.bsId, sizeof(wmx_BSid_t));
	//L4db_GetRecentNsp(&userLinkStatus.nspId);
	userLinkStatus->power = g_linkStatus.power;
	userLinkStatus->rssi = g_linkStatus.rssi;
	userLinkStatus->time = wmxNds_GetConnectionDuration();

	*bufferLength = sizeof(wmx_UserLinkStatus_t);

	return status;
}

wmx_Status_t NDnSAgent_GetStatistics( UINT32 *bufferLength, UINT8 *buffer )
{
	wmx_Status_t status=WMX_ST_OK;
	//wmx_UserLinkStatus_t userLinkStatus;
	wmx_UserStatistics_t userStatistics;
	BOOL fIsCacheState;
	static wmx_Statistics_t Statistics={0};

	static BOOL fIsLastTimeWasIdle = FALSE;


	if (*bufferLength < sizeof(wmx_UserStatistics_t))
	{
		return WMX_ST_BUFFER_TOO_SHORT;
	}


	fIsCacheState = ((g_ndnsContext.systemState == Idle)  ||
		(g_ndnsContext.systemState == Ready)  ||
		(g_ndnsContext.systemState == RfOff));

	if( !fIsCacheState)
	{
		status = wmx_GetStatistics(&Statistics);
	}
	else
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "NDnSAgent_GetStatistics - Data From Cache");
	}

	userStatistics.timeStamp      = Statistics.timeStamp;
	userStatistics.TotalRxBytes   = Statistics.TotalRxBytes;
	userStatistics.TotalRxPackets = Statistics.TotalRxPackets;
	userStatistics.TotalTxBytes   = Statistics.TotalTxBytes;
	userStatistics.TotalTxPackets = Statistics.TotalTxPackets ;

	OSAL_memcpy_s(buffer, *bufferLength, &userStatistics, sizeof(wmx_UserStatistics_t));
	*bufferLength = sizeof(wmx_UserStatistics_t);

	return status;
}

// Copies the connected NSP to the buffer, if not connected returns WMX_ST_DATA_UNAVAILABLE
wmx_Status_t NDnSAgent_GetConnectedNSP( UINT32 *bufferLength, UINT8 *buffer)
{
	// Default is to block during provisioining
	return NDnSAgent_GetConnectedNSPEx(bufferLength, buffer, TRUE);
}

// Copies the connected NSP to the buffer, if not connected returns WMX_ST_DATA_UNAVAILABLE
wmx_Status_t NDnSAgent_GetConnectedNSPEx( UINT32 *bufferLength, UINT8 *buffer, BOOL blockOnProvisioning )
{
	wmx_NSPid_t lastConnectedNSPid;
	errno_t err;
	wmx_Status_t status;
	wmx_NSP_t nsp;
	UINT32 bufferLen = sizeof(wmx_UserLinkStatus_t);
	wmx_SystemState_t currentSystemState;
	wmx_UserLinkStatus_t userLinkStatus;

	OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);
	currentSystemState = g_ndnsContext.systemState;
	OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);

	if (FSM_GetState(&g_ndnsContext.fsm) != L4C_CONNECTED)
	{
		return WMX_ST_DATA_UNAVAILABLE;
	}

	if ( *bufferLength < sizeof(wmx_NSP_t) )
	{
		return WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
	}

	if (blockOnProvisioning)
	{		
		// This API can't be called during provisioning
		if (Ndns_GetProvisioningStarted() == TRUE)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Failed NDnSAgent_GetConnectedNSP - called during provisioning.");
			return WMX_ST_FAIL;
		}
	}
	else
	{
		TRACE(TR_MOD_APDO_AGENT, TR_SEV_INFO, "NDnSAgent_GetConnectedNSP - called during provisioning - but allowed anyway.");
	}

	status = L4db_GetRecentNsp(&lastConnectedNSPid);
	// if the device is connected to an unknown network, status should be OK but last connectedNSP = -1
	if((-1 == lastConnectedNSPid) && (WMX_ST_OK == status))
	{
		// change the lastConnectedNSPid to an illegal NSPID in order to ensure that GetNspInfo will  
		// handle the WMX_ST_DATA_UNAVAILABLE case.
		lastConnectedNSPid = ILLEGAL_NSP_ID;
		
		/*OSAL_ZeroMemory(nsp.nspName, sizeof(nsp.nspName));
		OSAL_memcpy_s(nsp.nspName, sizeof(nsp.nspName), "Unrecognized Operator", sizeof("Unrecognized Operator"));*/
	}
		
	status = GetNspInfo(lastConnectedNSPid, &nsp);
	if( status != WMX_ST_OK )
	{
		return status;
	}

	status = NDnSAgent_GetLinkStatus(&bufferLen,(UINT8*)&userLinkStatus);
	nsp.linkQuality = userLinkStatus.linkQuality;
	nsp.bestRssi = userLinkStatus.rssi;
	nsp.bestCINR = userLinkStatus.cinr;

	*bufferLength = sizeof(wmx_NSP_t);
	err = OSAL_memcpy_s( buffer, sizeof(wmx_NSP_t), &nsp, sizeof(wmx_NSP_t) );
	if( err != 0 )
	{
		return WMX_ST_FAIL;
	}

	return WMX_ST_OK;
}


// Tries to Stop an A-Sync Scan, returns the status of the operation
wmx_Status_t NDnSAgent_StopScan()
{
	wmx_Status_t status;

	// StopScan can be issued only when in single scan state
	//if (FSM_GetState(&g_ndnsContext.fsm) == L4C_SINGLE_SCAN)
	//{
	//	return L4S_StopScanner();
	//}

	// in case a scan/connect process is taking place, notify device
	if(L4C_GetInitialCoexMode() == WMX_MODE_CM && g_ndnsContext.processStarted)
	{
		L4C_SetProcessStarted(FALSE);
		wmx_CmdProcessEnd();
	}

	status = NDnSAgent_InvokeDualFlushOp(Task_StopScan, NULL, 0);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR,
			"Stop Scan failed. NDnSAgent_InvokeDualFlushOp returned: '%s'",
			wmxGetStatusStr(status));
	}

	L4Pub_SendScanCompleted(ScanStopped);
	return status;
}

void L4C_TaskHandler(UINT32 internalRequestID, void *buffer, UINT32 bufferLength)
{
	wmx_SystemState_t systemState;
	wmx_pConnectInfo_t connectInfo;
	wmx_pScanInfo_t scanInfo;
	UINT32 phaseNum = 1;

	UNREFERENCED_PARAMETER(bufferLength);

	// get the current system state
	OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);
		 systemState = g_ndnsContext.systemState;
	OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_TaskHandler(IN): Got '%s' task", L4C_TaskStr[internalRequestID]);

	switch (internalRequestID)
	{
		case Task_StartManualScan:
			scanInfo = (wmx_pScanInfo_t)buffer;
			g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = scanInfo->manualScanType;
			g_ndnsContext.scheduledTaskData.scanInfo.isInternal = scanInfo->isInternal;
			// if we are already in Ready state and there is no scan in progress - we can execute the manual scan task
			// (even if we are in Ready state - there could be a pending Scanning state indication from a previous scan)
			if ((systemState == Ready) && (!L4S_IsScanning()))
			{
				// in case the scanner is active (and NOT scanning) - it means that
				// it is sleeping (LinkLoss / Standby state) - so we need to reset it
				if (L4S_READY != L4S_GetScannerState())
				{
					L4S_Reset(TRUE);
				}
				L4C_ScheduleTask(Task_StartScan); // after the scan session is over - return to normal scan mode
				L4C_UpdateScanStatus(FALSE);
				OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE);
				L4C_StartManualScanPhase2(g_ndnsContext.scheduledTaskData.scanInfo.manualScanType,
										  g_ndnsContext.scheduledTaskData.scanInfo.isInternal);
			}
			else // we are still not in Ready state - schedule the manual scan task to be executed
			{	 // only when getting to Ready state
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG,
					"State is not ready or scanner is stil scanning: system state=%s, scanner state=%s",
					NDnSSystemStates[systemState],
					ScannerStateStr[L4S_GetScannerState()]);
				L4C_ScheduleTask(Task_StartManualScan); // start Connect on the next Ready state
			}
			break;
		case Task_Connect:
			connectInfo = (wmx_pConnectInfo_t)buffer;

			// if we are already in Ready state and there is no scan in progress - we can execute the connect task
			// (even if we are in Ready state - there could be a pending Scanning state indication from a previous scan)
			if ((systemState == Ready) && (!L4S_IsScanning()))
			{
				// in case the scanner is active (and NOT scanning) - it means that
				// it is sleeping (LinkLoss / Standby state) - so we need to reset it
				if (L4S_READY != L4S_GetScannerState())
				{
					L4S_Reset(TRUE);
				}
				L4C_ScheduleTask(Task_StartScan); // after the connect session is over - return to normal scan mode
				L4C_UpdateScanStatus(FALSE);
				OSAL_atomic_exchange(&g_ndnsContext.isSingleManualScan, (long)FALSE);
				NDnSAgent_ConnectPhase2(connectInfo);
			}
			else // we are still not in Ready state - schedule the Connect task to be executed
			{	 // only when getting to Ready state
				OSAL_memcpy_s(&g_ndnsContext.scheduledTaskData.connectInfo, sizeof(g_ndnsContext.scheduledTaskData.connectInfo), connectInfo, sizeof(wmx_ConnectInfo_t));
				L4C_ScheduleTask(Task_Connect); // start Connect on the next Ready state
			}
			break;
		case Task_StopScan:
			{
				if (FSM_GetState(&g_ndnsContext.fsm) == L4C_SINGLE_SCAN)
				{
					//Nothing to do in this case, just complete the
					//process of stopping scan by calling NDnSAgent_OnProgressDualFlush()
					NDnSAgent_OnProgressDualFlush(Task_StopScan, NULL, phaseNum);
				}
				break;
			}
		case Task_SetConnectMode:
			{
				L4CState state = FSM_GetState(&g_ndnsContext.fsm);
				g_ndnsContext.scheduledTaskData.connectMode = *(wmx_pUserConnectMode_t)buffer;
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Task_SetConnectMode : g_ndnsContext.scheduledTaskData.connectMode = [%d]", g_ndnsContext.scheduledTaskData.connectMode);
				if (state == L4C_SINGLE_SCAN || state == L4C_AUTO_SCAN)
				{
					NDnSAgent_OnProgressDualFlush(Task_SetConnectMode, NDnSAgent_SetConnectModePhase2, phaseNum);
				}
				else // we are not in scanning state (RF OFF or Uninitialized...)
				{
					NDnSAgent_SetConnectModePhase2();
					g_ndnsContext.scheduledTaskData.status = WMX_ST_OK;
					L4C_ScheduleTask(Task_StartScan); // after the session is over - return to normal scan mode
					//Set Event to release the waiting thread
					OSAL_set_event(g_ndnsContext.dualFlushOpEvent);
				}
				break;
			}
		case Task_StartScan:
		case Task_Reset:
		default:
			break;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4C_TaskHandler(OUT)");
}

//
//For all cases we need to stop scan and then update the L4DB with the new connect or scan modes.
//In case we're switching between ManConnect to AutoConnect - we need to start connecting we current preferred NSP is available
//In all other cases (e.g. - In case we switch between AutoScan to SemiAutoScan or vice versa)
//we reset the scanning process (i.e. we stop scan and reschedule Task_StartScan)
wmx_Status_t NDnSAgent_SetConnectModePhase2()
{
	UINT32 totalNumOfNsps = WMX_NSPS_MAX_NUM, numCPNs, i, j;
	wmx_NSP_t currentPreferredNsp, availableNsps[WMX_NSPS_MAX_NUM] = {0} ;
	wmx_UserConnectMode_t connectMode = g_ndnsContext.scheduledTaskData.connectMode ;
	wmx_UserConnectMode_t lastConnectMode = L4db_GetConnectMode();
	wmx_SystemState_t systemState;
	wmx_Status_t status = WMX_ST_FAIL;
	wmx_SystemStateUpdate systemStateUpdate;
	BOOL isReset = FALSE;

	systemStateUpdate.SystemState = g_ndnsContext.systemState;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_SetConnectModePhase2(IN)");

	//Saving to L4DB - In case of any failure return status
	status = L4db_SetConnectMode(connectMode);

	//send CB indication
	NDnSAgent_ConnectionModeUpdate(connectMode);

	if (status == WMX_ST_OK)
	{
		if( (lastConnectMode != UserSemiManScanAutoConnect && lastConnectMode != UserAutoScanAutoConnect) &&
			(connectMode == UserSemiManScanAutoConnect || connectMode == UserAutoScanAutoConnect) )
		{
			//In case we switch from ManConnect to AutoConnect - start connect
			//(This is a special case where we override the StartScan task set in NDnSAgent_OnProgressDualFlush)
			//In any other case of switching connect (auto to man),
			//or (any to any) scan mode - leave the scheduled StartScan from NDnSAgent_OnProgressDualFlush
			//
			//first see if have a CPN...
			if(GetCurrentPreferredNSPEx(&currentPreferredNsp, &numCPNs ) == WMX_ST_OK && numCPNs > 0)
			{
				//If we have a CPN, search for it in AvailabeNSPsList.
				//If found, set params of the next scheduled task, and schedule AutoConnect
				if (GetAvailableNspsList(&totalNumOfNsps, availableNsps, FALSE) == WMX_ST_OK)
				{
					for (i = 0; i < totalNumOfNsps; i++)
					{
						for (j = 0; j < currentPreferredNsp.numOfNspIDs; j++)
						{
							if (currentPreferredNsp.nspIDs[j] == availableNsps[i].nspIDs[0])
							{
								g_ndnsContext.scheduledTaskData.connectInfo.numOfNspIDs = 1;
								g_ndnsContext.scheduledTaskData.connectInfo.coexPriority = COEX_PRIORITY_CONNECT_LOW;
								g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect = TRUE;
								g_ndnsContext.scheduledTaskData.connectInfo.nspIDs[0] = currentPreferredNsp.nspIDs[j];

								TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_SetConnectModePhase2 - scheduling the task '%s' for the next Ready state", L4C_TaskStr[Task_AutoConnect]);
								//NDnSAgent_OnProgressDualFlush(Task_AutoConnect, NULL);
								L4C_ScheduleTask(Task_AutoConnect);
								OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);
								systemState = g_ndnsContext.systemState;
								OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);
								L4C_SetControllerMode(systemState, FALSE);
								status = WMX_ST_OK;
							}
						}
					}
				}
			}
			else
			{
				//if no CPN is available return WMX_ST_WRONG_STATE
				status = WMX_ST_WRONG_STATE;
				// 				g_ndnsContext.scheduledTaskData.status = ;
				// 				//release the waiting thread... (NDnSAgent_InvokeDualFlushOp())
				// 				OSAL_set_event(g_ndnsContext.dualFlushOpEvent);
			}
		}
		else
		{
			if (g_ndnsContext.systemState == Ready)
			{
				status = L4C_HandleReadyState(&systemStateUpdate, &isReset);
			}
		}
		// 		else
		// 		{
		// 			//In any other case of switching connect (auto to man),
		// 			// or (any to any) scan mode - schedule StartScan
		// 			//NDnSAgent_OnProgressDualFlush(Task_StartScan, NDnSAgent_GenerateFictiveReadyState);
		// 			L4C_ScheduleTask(Task_StartScan);
		// 		}
	}
	// 	else
	// 	{
	// 		//In case of any failure
	// 		status = status;
	// 	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_SetConnectModePhase2(OUT)");
	return status;
}


wmx_Status_t NDnSAgent_ConnectPhase2(wmx_pConnectInfo_t connectInfo)
{
	L4CState fsmState = FSM_GetState(&g_ndnsContext.fsm);
	wmx_Status_t status;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_ConnectPhase2(IN)");

	if (!FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, L4C_CONNECTING, L4C_CONNECTING))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_ConnectPhase2(OUT).ERROR FSM_SetStateIfNotEqual returned FALSE. ");
		return WMX_ST_WRONG_STATE;
	}

	// reset the L4Scanner in a hard manner since we are now using the messenger thread and
	// the L4Scanner won't be able to get L4 indications for successful reset
	L4S_Reset(TRUE);

	if (L4C_GetInitialCoexMode() == WMX_MODE_CM)
	{
		status = wmx_CmdProcessStart(COEX_STATE_CONNECTING);
		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_Connect: ProcessStart failed status=%d", status);
			NDnSAgent_RfTakenIndication();
			return status;
		}
		L4C_SetProcessStarted(TRUE);
	}

	status = NDnSAgent_StartConnect( connectInfo->nspIDs[0], connectInfo->coexPriority, connectInfo->forceManualConnect, connectInfo->useOnlyLastChannel );
	// after manual connect attempt (even unsuccessful one) - start the next scan cycle from scratch (no resume)
	OSAL_atomic_exchange(&g_ndnsContext.isResumeScan, FALSE);
	if( status != WMX_ST_OK ) // start another scan cycle
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_ConnectPhase2(OUT).ERROR NDnSAgent_StartConnect returned %d. ", status);
		FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, fsmState, fsmState); // return to the previous state
		L4C_ScheduleTask(Task_StartScan); // reset the scheduler back to normal scan
		L4C_SetControllerMode(Ready, FALSE); // trigger the next scan cycle
	}

	L4S_EnableScanner(TRUE);
	g_ndnsContext.scheduledTaskData.status = status;
	OSAL_set_event(g_ndnsContext.connectCompletedEvent); // Connect

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_ConnectPhase2(OUT)");

	return status;
}

// Tries to Connect to specified Target, returns the status of the operation
wmx_Status_t NDnSAgent_StartConnect( wmx_NSPid_t nspID, wmx_CoexPriority_t coexPriority, BOOL forceManualConnect, BOOL useOnlyLastChannel )
{
	wmx_Status_t status, monitorStatus;
	wmx_BSSelectionCriteria_t bsCriteria;
	wmx_ConnectFlags_t connectFlags;
	wmx_AvailableNSP_t availableNSP;
	L4db_Nap_t naps[WMX_NAPS_MAX_NUM];
	UINT32 napsSize = WMX_NAPS_MAX_NUM;
	DiscoveredNap_t discoveredNAP;
	wmx_ChannelInfo_t chPlan[WMX_CHANNELS_MAX_NUM];
	UINT numChannels = WMX_CHANNELS_MAX_NUM;
	wmx_ConnectionMode_t connectionMode = CONNECTION_MODE_MANUAL;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Trying to connect - NSP ID = %d, forcing manual connect = %s", nspID, forceManualConnect == FALSE ? "False" : "True");

	FSM_SetStateIfNotEqual(&g_ndnsContext.fsm, L4C_CONNECTING, L4C_CONNECTING);

	// Save the NSP that we try to connect. When the indication of a successful connection arrives save it as the last connected
	Ndns_SetConnectingNSPTemp(nspID);
	g_ndnsContext.tempCoexPriority = coexPriority;

	if (GetAvailableNspNode(nspID, &availableNSP) == FALSE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NSP ID = %d could not be found in the available NSPs list. Aborting connect.", nspID);
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	status = L4db_GetNapsInfo(nspID, (pL4db_Nap_t)naps, &napsSize);

	if (status != WMX_ST_OK && status != WMX_ST_DATA_UNAVAILABLE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error getting provisioned data for NSP ID = %d. Aborting connect.", nspID);
		goto Finalize;
	}

	// update the BS ID based on the available NSPs list entry
	OSAL_memcpy_s(naps[0].napID, sizeof(wmx_NAPid_t), availableNSP.bsId, sizeof(wmx_NAPid_t));

	// this NSP is not provisioned, so we'll use NapID=NspID
	if (napsSize < 1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Couldn't find provisioned data for NSP ID = %d.", nspID);
		if (L4DB_GetNon16gDetectedNapInfo(naps[0].napID, &discoveredNAP, TRUE) != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error getting discovered data for NAP ID = %d.", nspID);
			status = WMX_ST_FAIL;
			goto Finalize;

		}
		// copy the discovered channel plan
		OSAL_memcpy_s(&naps[0].discoveredChannelPlan, sizeof(naps[0].discoveredChannelPlan), &discoveredNAP.channelPlan, sizeof(discoveredNAP.channelPlan));
		napsSize = 1;
	}

	// convert the detected channels for the selected NSP from L4DB type to ND&S type
	wmxNds_DBChannelInfoToWmxChannelInfo(chPlan, &numChannels, naps[0].discoveredChannelPlan.channels, naps[0].discoveredChannelPlan.channelsSize);
		monitorStatus = wmx_PopulateMonitorSelectedChannel(chPlan, numChannels);

	// if we got here - it means that the L4Scanner has been stopped and is now in Ready state
	if ((!forceManualConnect) && (!L4S_AreChannelsInLastChunk(chPlan, numChannels)))
	{
			// the required channels for the selected NAP are not in the last scanned chunk -
			// so schedule a "scan-connect" sequence
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Required channels are not in the last chunk. Scheduling \"scan-connect\" sequence for NSP ID = %d", nspID);

			// save scheduled scan info
			if (useOnlyLastChannel)
			{
				UINT32 chId = L4db_GetFirstChannelWithFullPreambles(naps[0].discoveredChannelPlan.channels, naps[0].discoveredChannelPlan.channelsSize);
				if (chId == naps[0].discoveredChannelPlan.channelsSize) // there is no channel with full preambles
				{	// in case there are no full channels - use the first partial channel
					g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize = 1;
					wmxNds_DBChannelInfoToWmxChannelInfo(chPlan, &numChannels, naps[0].discoveredChannelPlan.channels, 1);
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Couldn't find a detected channel with full preambles. Using the last detected channel with SINGLE premable to connect.");
				}
				else
				{	// use the first full channel
					///Nardimon
					///If the first full preamble is not the same as the last discovered channel then we will send
					/// both of the channels with full preambles since the channel with not full preamble that was last
					/// discovered is from NBR_ADV
					if (naps[0].discoveredChannelPlan.channels[chId].firstFreq != naps[0].discoveredChannelPlan.channels[0].firstFreq)
					{
						// use the first full channel
						g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize = 1;
						wmxNds_DBChannelInfoToWmxChannelInfo(chPlan, &numChannels, naps[0].discoveredChannelPlan.channels , 1);
						//// use the first full channel - THIS CODE IS REDUNDANT (AMIR & AVISHAI)
						//g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize += 1;
						//wmxNds_DBChannelInfoToWmxChannelInfo(chPlan, &numChannels, naps[0].discoveredChannelPlan.channels + chId, 1);
					}
					else
					{
						// use the first full channel
						g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize = 1;
						wmxNds_DBChannelInfoToWmxChannelInfo(chPlan, &numChannels, naps[0].discoveredChannelPlan.channels + chId, 1);
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Using the last detected channel with FULL premables to connect.");
					}
				}
				OSAL_memcpy_s(g_ndnsContext.scheduledTaskData.scanInfo.chPlan, sizeof(g_ndnsContext.scheduledTaskData.scanInfo.chPlan), chPlan, sizeof(chPlan));

			}
			else
			{
				// generate preferred channel plan for the requested NSP (neighbors first [if exist] and then full preambles)
				g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize = WMX_CHANNELS_MAX_NUM;
				status = L4P_GenerateNspMCP(nspID, g_ndnsContext.scheduledTaskData.scanInfo.chPlan, &g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize);
				// if we couldn't find any valid profile for this nsp (provisioned or not) - use the last detected
				if (status != WMX_ST_OK)
				{
					OSAL_memcpy_s(g_ndnsContext.scheduledTaskData.scanInfo.chPlan, sizeof(g_ndnsContext.scheduledTaskData.scanInfo.chPlan), chPlan, sizeof(chPlan));
					g_ndnsContext.scheduledTaskData.scanInfo.chPlanSize = numChannels;
				}
			}

			g_ndnsContext.scheduledTaskData.scanInfo.manualScanType = SCAN_TYPE_AUTO_CONNECT;

			// save scheduled connect info
			g_ndnsContext.scheduledTaskData.connectInfo.nspIDs[0] = nspID;
			g_ndnsContext.scheduledTaskData.connectInfo.numOfNspIDs = 1;
			g_ndnsContext.scheduledTaskData.connectInfo.coexPriority = coexPriority;
			// after the scheduled scan cycle - the detected channels for the selected NAP are in the last chunk
			g_ndnsContext.scheduledTaskData.connectInfo.forceManualConnect = TRUE;
			g_ndnsContext.scheduledTaskData.connectInfo.useOnlyLastChannel = useOnlyLastChannel;

			L4S_EnableScanner(TRUE); // enable the L4 Scanner to allow scanning
			// shift back to a scanning state
			FSM_SetState(&g_ndnsContext.fsm, FSM_GetPreviousState(&g_ndnsContext.fsm));
			L4C_ScheduleTask(Task_StartManualScan);

			// since we are already in "Ready" system state - generate an artificial "Ready" indication
			status = L4C_SetControllerMode(Ready, FALSE);
			return status;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Trying to connect to NAP ID [%02x][%02x][%02x] (%02x%02x%02x)", naps[0].napID[0],
												naps[0].napID[1], naps[0].napID[2],
												naps[0].napID[0],
												naps[0].napID[1],
												naps[0].napID[2]);

		// now that we actually connect, we can configure the supplicant
		if( TRUE == g_ndnsContext.isSupplicantStarted )
		{
			status = wmx_EnableSupplicant(TRUE); // enable the Supplicant
			if ( WMX_ST_OK != status )
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error enabling supplicant");
				goto Finalize;
			}
		}

		status = NDnSAgent_SetConfigToSupplicant( nspID );
		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Supplicant configuration error");
			goto Finalize;
		}

		Ndns_SetConnectingNAPTemp(naps[0].napID);
		NAP2BSCriteria( naps[0].napID, availableNSP.bsIdType, &bsCriteria );

		connectFlags.requestRealm = REQUEST_REALM_DONT_REQUEST;
		connectFlags.visitedNspId = 0;
		connectFlags.SIQ = 0;
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "trying to connect - bscriteria = %d, bscriteria mask = %d", bsCriteria.bsID, bsCriteria.bsIDmask);

		status = wmx_CmdStartConnect( bsCriteria, thCriteria, &connectFlags, coexPriority, connectionMode );
		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Connection attempt failed. status=%d", status);
			goto Finalize;
		}
	}

Finalize:
	if (status != WMX_ST_OK)
	{
		g_ndnsContext.eapContext.isStarted = FALSE;
		g_ndnsContext.eapContext.numEapRetries = 0;
		g_ndnsContext.eapContext.isEapFail = FALSE;
		g_ndnsContext.eapContext.isPerformedFallBack = FALSE;
		FSM_SetState(&g_ndnsContext.fsm, FSM_GetPreviousState(&g_ndnsContext.fsm));
	}

	return status;
}


// Tries to Connect to specified Target, returns the status of the operation
wmx_Status_t NDnSAgent_Connect( wmx_ConnectParams connectParams, wmx_CoexPriority_t coexPriority, wmx_pUserConnectStatus_t pUserConnectStatus )
{
	wmx_Status_t status = WMX_ST_OK;
	L4CState fsmState = FSM_GetState(&g_ndnsContext.fsm);
	//wmx_NSPid_t nspID = connectParams.nspID;
	UINT8 messageBuffer[sizeof(wmx_ConnectInfo_t)];
	wmx_ConnectInfo_t connectInfo;

	UNREFERENCED_PARAMETER(pUserConnectStatus);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_Connect(IN)");
	// TODO: Oran - for future version - pass all the parameters in connectParams to StartConnect and use them.

	if (fsmState != L4C_SINGLE_SCAN && fsmState != L4C_AUTO_SCAN)
	{	// TODO: Oran - check also the state of the L4Scanner (and stop the scanning, if necessary)
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_Connect(OUT). ERROR WMX_ST_WRONG_STATE. fsmState=%d",fsmState);
		return WMX_ST_WRONG_STATE;
	}

	// Make sure that the NSP is in the available NSPs list
	if (CheckIfNspInAvailableList(connectParams.nspID) == FALSE)
	{

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_Connect(OUT). NSP ID = %d was not found in available NSPs list", connectParams.nspID);
		PrintAvailableNspsList(FALSE, TR_SEV_NOTICE);

		return WMX_ST_WRONG_ARGUMENT;
	}

	// in case a scan process is taking place, notify device
	if(L4C_GetInitialCoexMode() == WMX_MODE_CM && g_ndnsContext.processStarted)
	{
		L4C_SetProcessStarted(FALSE);
		wmx_CmdProcessEnd();
	}

	L4C_ScheduleTask(Task_Reset); // reset the L4Controller
	L4S_EnableScanner(FALSE);
	L4S_Reset(FALSE); // reset the L4Scanner

	OSAL_reset_event(g_ndnsContext.connectCompletedEvent);

	connectInfo.nspIDs[0] = connectParams.nspID;
	connectInfo.numOfNspIDs = 1;
	connectInfo.coexPriority = coexPriority;
	connectInfo.forceManualConnect = FALSE;
	connectInfo.useOnlyLastChannel = FALSE;

	OSAL_memcpy_s(messageBuffer, sizeof(connectInfo), &connectInfo, sizeof(connectInfo));

	g_ndnsContext.scheduledTaskData.status = WMX_ST_FAIL;

	pUtils->tpfnPostRequest(MEDIUM, Task_Connect, (void*)messageBuffer, sizeof(wmx_ConnectInfo_t), &L4C_TaskHandler);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Connect task was scheduled for the next system state Ready");

	if (OSAL_wait_event(g_ndnsContext.connectCompletedEvent, L4C_TIMEOUT * 2) != WAIT_OBJECT_0)
	{
		L4C_ScheduleTask(Task_StartScan); // reset the scheduler back to normal scan
		L4S_EnableScanner(TRUE);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Error connecting to NSP ID = %d. Timeout expired !", connectParams.nspID);
		status = WMX_ST_FAIL;
	}
	else
	{
		status = g_ndnsContext.scheduledTaskData.status;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_Connect(OUT) - status=%d", status);
	return status;
}


// Tries to Disconnect, returns the status of the operation
wmx_Status_t NDnSAgent_Disconnect()
{
	wmx_Status_t status;

	if (!FSM_SetStateIfEqual(&g_ndnsContext.fsm, L4C_CONNECTED, L4C_DISCONNECTING))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSANDnSAgent_Disconnect failed to set state");
		return WMX_ST_WRONG_STATE;
	}

	// TODO: Oran - V3.0 phase2 new
	//status = NDnSAgent_StartDisconnect();
	OSAL_reset_event(g_ndnsContext.disconnectCompletedEvent); // Oran - new
	status = wmx_CmdDisconnect();

	if (status != WMX_ST_OK)
	{
		// change the state back the "CONNECTED" ONLY if we havn't got a new system state that caused us to reset the "DISCONNECTING" state
		FSM_SetStateIfEqual(&g_ndnsContext.fsm, L4C_DISCONNECTING, L4C_CONNECTED);
		return status;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "waiting for disconnect complete event");
	if(OSAL_wait_event(g_ndnsContext.disconnectCompletedEvent, LONG_OPERATIONS_TIMEOUT) != WAIT_OBJECT_0)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "missing disconnect completed event");
		return WMX_ST_FAIL;
	}

	return WMX_ST_OK;
}

wmx_Status_t NDnSAgent_GenerateNAI(wmx_EapType_t eapMethod, char* id, char* provisionedPseudoId,
								   char* realm, BOOL isHome, wmx_pNAI_t nai, UINT32 naiSize)
{
	wmx_Status_t st;
	unsigned char macAddress[BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_BYTES_SIZE];
	wmx_ModelType_t modelType;
	wmx_Manufacturer_t manufacturerId;
	wmx_SerialNumber_t serialNumber;
	wmx_NvmVersion_t nvmVersion;
	wmx_Nonce_t nonce;
	wmx_ODMInfo_t odmInfo;
	wmx_DevicePID_t pid;
	wmx_ApdoOperatorConfigurations_t operatorConfigurations[MAX_NUM_OF_CONFIGURATIONS];
	int naiCounter;
	int numberOfNaiCounterDigits, remainder;
	char buff[BUFF_SIZE];
	size_t	tempLength = 0;
	BOOL res;
    char answer[MAX_ANSWER_SIZE];
	char macHex[BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_BYTES_SIZE*2 + 1];
	UINT32 noSm = FALSE;

	char * naiHex;
	naiHex = malloc ((sizeof(BYTE))*NUMBER_OF_GENERATED_CHARS_FOR_PSEUDO_NAI);
	if (naiHex == NULL){
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR	, "Could not allocate naiHex !!!");
		return WMX_ST_FAIL;
	}

	res = L4Configurations_getNoSM(&noSm);

	if((!res) && (!isHome) && ((WMX_EAP_TLS == eapMethod) || (WMX_EAP_TTLS == eapMethod)))
	{
		//concatenate the provisioning decoration
		OSAL_strcpy_s(nai, naiSize, PROVISIONING_NAI_DECORATION);
		L4Pub_SetDeviceStatusActivationConnect(TRUE);
	}
	else
	{
		OSAL_strcpy_s(nai, naiSize, "\0");
		L4Pub_SetDeviceStatusActivationConnect(FALSE);
	}

	res = L4Configurations_getCustomDecoration(buff);

	if ((res) && ((WMX_EAP_TLS == eapMethod) || (WMX_EAP_TTLS == eapMethod)))
	{
		OSAL_strcat_s(nai, naiSize, buff);
	}

	//regData = OSAL_ConfigController_GetStrValue(OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_DO_NOT_USE_PSEUDO_NAI, answer, MAX_ANSWER_SIZE);
	if(WMX_EAP_TTLS == eapMethod)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG	, "NDnSAgent_GenerateNAI : Trying GetApdoOperatorsConfigurations...");
		st = GetApdoOperatorsConfigurations(operatorConfigurations);

		if (st == WMX_ST_FAIL)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_GenerateNAI : GetApdoOperatorsConfigurations == WMX_ST_FAIL, Using default behavior which is do not disable pseudo nai !");
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_GenerateNAI : GetApdoOperatorsConfigurations != WMX_ST_FAIL, Using pseudoNAI == [%s].", (operatorConfigurations[0].disablePseudoNAI == TRUE ? "True" : "False"));
		}


		if (operatorConfigurations[0].disablePseudoNAI)
		{
			if('\0' != provisionedPseudoId[0])
			{
				OSAL_strcat_s(nai, naiSize, provisionedPseudoId);
			}
			else // generate the incremental NAI
			{
				naiCounter = L4db_GetNaiCounter();
				OSAL_itoa_s(naiCounter, buff, BUFF_SIZE, 10);
				OSAL_strcat_s(nai, naiSize, buff);
				naiCounter++;
				L4db_SetNaiCounter(naiCounter);
			}
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Trying GeneratePseudoNAI...");
			st = GeneratePseudoNAI(naiHex,NUMBER_OF_GENERATED_CHARS_FOR_PSEUDO_NAI);
			if (WMX_ST_OK != st)
			{
				free(naiHex);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "GeneratePseudoNAI returned %d", st);
				return WMX_ST_FAIL;
			}
			naiCounter = L4db_GetNaiCounter();
			remainder = (naiCounter % 10);
			if (remainder == 0)
			{
				naiCounter = L4db_GetNaiCounter();
				naiCounter++;
				L4db_SetNaiCounter(naiCounter);
			}
			numberOfNaiCounterDigits =(int) log10(naiCounter) + 1;
			naiHex[(NUMBER_OF_GENERATED_CHARS_FOR_PSEUDO_NAI-(numberOfNaiCounterDigits+1))] = '\0';
			OSAL_strcat_s(nai, naiSize, naiHex);
			OSAL_itoa_s(naiCounter, buff, BUFF_SIZE, 10);
			OSAL_strcat_s(nai, naiSize, buff);
			naiCounter++;
			L4db_SetNaiCounter(naiCounter);
			if (naiHex)
			{
				free(naiHex);
				naiHex = NULL;
			}
		}
	}
	else if((WMX_EAP_TLS == eapMethod) && ('\0' == id[0]))//check if we should get the mac address or not
	{
		st = wmx_GetDeviceDetailsEx(macAddress, &modelType, &manufacturerId, &serialNumber, (wmx_pNvmVersion_t)&nvmVersion, (wmx_pODMInfo_t)&odmInfo, (wmx_pNonce_t)&nonce, (wmx_pDevicePID_t)&pid);

		if(WMX_ST_OK != st)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "wmx_GetDeviceDetails returned %d", st);
			return st;
		}

		NDnSAgent_HexEncode(macAddress, macHex, BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_BYTES_SIZE);

		tempLength = OSAL_strnlen(nai, MAX_STRING_VALIDATE);
		OSAL_strcat_s(nai, naiSize, (char*)macHex);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "NDnSAgent_GenerateNAI: concatenate the given user identity ");
		//concatenate the given user identity - this patch is temp!!
		OSAL_strcat_s(nai, naiSize, id);
	}

	res = L4Configurations_getNoRealmInNAI(answer);
	if ( TRUE == res )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_GenerateNAI: NoRealmInNAI patch no adding NAI");
		return WMX_ST_OK;
	}

	if('\0' != realm[0])
	{
		//concatenate the @
		OSAL_strcat_s(nai, naiSize, ADDRESS_STR);
		OSAL_strcat_s(nai, naiSize, realm);
	}
	else if(WMX_PLAIN_MSCHAPv2 != eapMethod) // concatenate "wimax.com" when in TLS/TTLS/AKA
	{
		//concatenate the @
		//OSAL_strcat_s(nai, naiSize, ADDRESS_STR);
		//OSAL_strcat_s(nai, naiSize, DEFAULT_REALM);
	}
	/*else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_GenerateNAI: no realm or wrong eap method");
		return WMX_ST_FAIL;
	}*/

	return WMX_ST_OK;
}

// TTLS -> TLS fall-back support
BOOL NDnSAgent_HandleTTLSFallback(pEAP_t ttlsInfo)
{
	BOOL isTLS = FALSE;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_HandleTTLSFallback: isStarted = (%d) isEapFail = (%d)",g_ndnsContext.eapContext.isStarted, g_ndnsContext.eapContext.isEapFail);

	if (ttlsInfo->EAPMethod == WMX_EAP_TTLS)
	{
		if (g_ndnsContext.eapContext.isStarted && g_ndnsContext.eapContext.isEapFail)
		{
			switch(g_ndnsContext.eapContext.numEapRetries)
			{
			case 1:		// Fallback to TLS
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_HandleTTLSFallback: Tallback to TLS");
				// no more TTLS retries left. Move to TLS
				ttlsInfo->Password[0] = '\0';
				ttlsInfo->EAPMethod = WMX_EAP_TLS;
				isTLS = TRUE;
				g_ndnsContext.eapContext.numEapRetries = 0;
				g_ndnsContext.eapContext.isPerformedFallBack = TRUE;
				break;
			case 0:		// Run out of trials - Restarting...
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "NDnSAgent_HandleTTLSFallback: Ran out of trials - starting over TTLS-->TTLS-->TTLS-->TLS-->");
				g_ndnsContext.eapContext.numEapRetries = EAP_NUM_RETRIES;
			    break;
			default:	// This case assumes that numEapRetries > 1
				g_ndnsContext.eapContext.numEapRetries--;
			    break;
			}
		}
		else // start an EAP TTLS session. Assign number of TTLS retries before fall-back to TLS
		{
			g_ndnsContext.eapContext.isStarted = TRUE;
			g_ndnsContext.eapContext.numEapRetries = EAP_NUM_RETRIES;
			g_ndnsContext.eapContext.isEapFail = FALSE;
			g_ndnsContext.eapContext.isPerformedFallBack = FALSE;
		}
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_HandleTTLSFallback: g_ndnsContext.eapContext.numEapRetries = [%d]",g_ndnsContext.eapContext.numEapRetries);
	}
	else
	{
		g_ndnsContext.eapContext.isStarted = FALSE;
	}

	return isTLS;
}

// Set Config to Supplicant.
wmx_Status_t NDnSAgent_SetConfigToSupplicant( wmx_NSPid_t nspID )
{
	wmx_Status_t status;
	pProvisionedNsp_t provisionedNSP=NULL;
	pSubscriberInfo_t pPrimarySubsInfo = NULL;
	BOOL IsNewPrimarySubsInfoAlloc = FALSE;
	pEAP_t mainEap, encapsedEap = NULL;
	DeviceCertificates_t deviceCertificates;
	char buff[MAX_REGISTRY_ANSWER];
	wmx_EapMathod_t eapMethod, encapsedEapMethod;
	char eapTypeStr[MAX_NAME_STR_LEN];
	char identity[WMX_SUBSCRIBER_ID_MAX_SIZE + WMX_NSP_REALM_MAX_SIZE];
	UINT32 tagName;


	// This will reset both contexts:
	// 1. The config context that is saved for the supplicant
	// 2. The supplicant context itself that is saved by the SupplicantAgent.
	wmx_ResetSupplicant();
	provisionedNSP = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));
	if (provisionedNSP == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return WMX_ST_FAIL;
	}

	status = L4db_GetProvisionedNsp(nspID, provisionedNSP);

	if (status == WMX_ST_DATA_UNAVAILABLE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "SetConfigToSupplicant: nspID not found");

		pPrimarySubsInfo = (pSubscriberInfo_t)malloc(sizeof(SubscriberInfo_t));
		if (pPrimarySubsInfo == NULL)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
			goto SupFinalize;
		}

		IsNewPrimarySubsInfoAlloc = TRUE;

		memset(&pPrimarySubsInfo->eapInfo[0], 0, sizeof(pPrimarySubsInfo->eapInfo[0]));
		pPrimarySubsInfo->activated = FALSE;
		pPrimarySubsInfo->eapInfoSize = 1;
		pPrimarySubsInfo->eapInfo[0].encaps = (UINT32)L4DB_INVALID_INDEX;
		pPrimarySubsInfo->eapInfo[0].EAPMethod = WMX_EAP_TLS;
		OSAL_strcpy_s(pPrimarySubsInfo->eapInfo[0].id, sizeof(pPrimarySubsInfo->eapInfo[0].id), "\0");
	}
	else if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error in NDnSAgent_SetConfigToSupplicant");
		goto SupFinalize;
	}
	else
	{
		pPrimarySubsInfo = &(provisionedNSP->subscriptionParams.primary);
	}

	status = L4db_GetDeviceCertificates(&deviceCertificates);
	if (status == WMX_ST_DATA_UNAVAILABLE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: no certificates found");
		goto SupFinalize;
	}

	// sync between inner and outer EAP methods
	if (pPrimarySubsInfo->eapInfoSize > 1) // we've got a tunnel... Yeh !
	{
		OSAL_sscanf_s(pPrimarySubsInfo->eapInfo[1].tagName, "%d", &tagName);
		// The encaps value should be a pointer to the index of the entry this entry is encapsulated in
		if (pPrimarySubsInfo->eapInfo[0].encaps == tagName)
		{
			encapsedEap = &pPrimarySubsInfo->eapInfo[0]; // inner
			mainEap = &pPrimarySubsInfo->eapInfo[1]; // outer
		}
		// This is the case that should be accordiing to the OTA standard
		else
		{
			OSAL_sscanf_s(pPrimarySubsInfo->eapInfo[0].tagName, "%d", &tagName);
			if (pPrimarySubsInfo->eapInfo[1].encaps == tagName)
			{
				encapsedEap = &pPrimarySubsInfo->eapInfo[1]; // inner
				mainEap = &pPrimarySubsInfo->eapInfo[0]; // outer
			}
			else
			{
				mainEap = &pPrimarySubsInfo->eapInfo[0]; // no sync is possible, take the first one
				encapsedEap = &pPrimarySubsInfo->eapInfo[1];
				// TODO: Oran - report error
				encapsedEap->encaps = (UINT32)L4DB_INVALID_INDEX; // make sure we won't try to access the encapsed node
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant - error in encaps definition.");
			}
		}

		// check if we have TTLS->TLS fall-back
		if (mainEap && NDnSAgent_HandleTTLSFallback(mainEap))
		{	// override TTLS session with TLS
			encapsedEap = mainEap;
			encapsedEap->encaps = (UINT32)L4DB_INVALID_INDEX;
		}
	}
	else // no tunnel, boring...
	{
		mainEap = &pPrimarySubsInfo->eapInfo[0];
		mainEap->encaps = (UINT32)L4DB_INVALID_INDEX; // make sure we won't try to access the encapsed node
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "SetConfigToSupplicant started");

	// Make sure that the Eap method is provisioned
	if (mainEap->EAPMethod == L4DB_INVALID_INDEX)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: No provisioned EAP method");
		status = WMX_ST_CONFIG_ERROR;
		goto SupFinalize;
	}

	l4db_ConvertToEapTypeStr(mainEap->EAPMethod, eapTypeStr);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "SetConfigToSupplicant: EAP method - %s", eapTypeStr);

	eapMethod = wmx_EapTypeToDS_EapType(mainEap->EAPMethod);
	if (eapMethod == SWC_EAP_TYPE_NONE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: invalid EAP method");
		status = WMX_ST_CONFIG_ERROR;
		goto SupFinalize;
	}

	// set eap method (phase 1)
	status = wmx_SetEapMethod(eapMethod);
	if (WMX_ST_OK != status)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetEapMethod (encapsulating) failed");
		goto SupFinalize;
	}

	if ((encapsedEap == NULL) || (encapsedEap->encaps == L4DB_INVALID_INDEX)) // no encapsulating EAP method
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "SetConfigToSupplicant: Setting supplicant according main EAP entry ");

		// NAI formatting
		status = NDnSAgent_GenerateNAI(mainEap->EAPMethod, mainEap->id, mainEap->provisionedPseudoId,
			mainEap->realm, pPrimarySubsInfo->activated, identity, (UINT32)sizeof(identity));

		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: failed to generate encapsulating NAI");
			goto SupFinalize;
		}

		status = wmx_SetIdentity((wmx_pNAI_t)identity);

		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetIdentity failed");
			goto SupFinalize;
		}
		wmx_PopulateNAIMonitor((wmx_pNAI_t)identity);

		if (mainEap->Password[0] != '\0')
		{
			status = wmx_SetPassword((wmx_pUserPassword_t)mainEap->Password);
			if (WMX_ST_OK != status)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetPassword failed");
				goto SupFinalize;
			}
		}
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "SetConfigToSupplicant: Setting supplicant according tunnel EAP entry ");

		// Make sure that the Eap method is provisioned for the encaps eap
		if ((encapsedEap->vendorId != EAP_MSCHAPV2_VENDOR_ID) || (encapsedEap->vendorType != EAP_MSCHAPV2_VENDOR_TYPE))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: problem in provisioned EAP method tunnel");
			status = WMX_ST_CONFIG_ERROR;
			goto SupFinalize;
		}

		encapsedEapMethod = SWC_PHASE2_METHOD_MSCHAPV2;

		// first set the phase 2 method
		status = wmx_SetPhase2Method(encapsedEapMethod); // set the provisioned eap method as the phase 2 method
		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: wmx_SetPhase2Method failed");
			goto SupFinalize;
		}

		// NAI formatting
		status = NDnSAgent_GenerateNAI(mainEap->EAPMethod, mainEap->id, mainEap->provisionedPseudoId,
			mainEap->realm, pPrimarySubsInfo->activated, identity, (UINT32)sizeof(identity));

		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: failed to generate encapsulating NAI");
			goto SupFinalize;
		}

		status = wmx_SetAnonymousIdentity((wmx_pNAI_t)identity);
		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: wmx_SetAnonymousIdentity failed");
			goto SupFinalize;
		}

		// NAI formatting
		status = NDnSAgent_GenerateNAI(encapsedEap->EAPMethod, encapsedEap->id, encapsedEap->provisionedPseudoId,
			encapsedEap->realm, pPrimarySubsInfo->activated, identity, (UINT32)sizeof(identity));

		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: failed to generate encapsulating NAI");
			goto SupFinalize;
		}

		status = wmx_SetIdentity((wmx_pNAI_t)identity);

		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetIdentity failed");
			goto SupFinalize;
		}
		wmx_PopulateNAIMonitor((wmx_pNAI_t)identity);

		if (encapsedEap->Password[0] != '\0')
		{
			status = wmx_SetPassword((wmx_pUserPassword_t)encapsedEap->Password);
			if (WMX_ST_OK != status)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetPassword failed");
				goto SupFinalize;
			}
		}
	}

	// now set the certificates
	if (deviceCertificates.rootCert[0] == '\0')
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: missing root cert");
		status = WMX_ST_CONFIG_ERROR;
		goto SupFinalize;
	}

	OSAL_BuildFullPath(deviceCertificates.rootCert, buff, MAX_REGISTRY_ANSWER -1);
	status = wmx_SetTlsCaCert((wmx_pCertificatePath_t)buff);
	if (WMX_ST_OK != status)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetTlsCaCert failed");
		goto SupFinalize;
	}

	if (deviceCertificates.clientCert[0] != '\0')
	{
		OSAL_BuildFullPath(deviceCertificates.clientCert, buff, MAX_REGISTRY_ANSWER -1);
		status = wmx_SetTlsClientCert((wmx_pCertificatePath_t)buff);
		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetTlsClientCert failed");
			goto SupFinalize;
		}
	}

	if (deviceCertificates.privateKey[0] != '\0')
	{
		OSAL_BuildFullPath(deviceCertificates.privateKey, buff, MAX_REGISTRY_ANSWER -1);
		status = wmx_SetTlsPrivateKey((wmx_pCertificatePath_t)buff);
		if (WMX_ST_OK != status)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "SetConfigToSupplicant: SetTlsPrivateKey failed");
			goto SupFinalize;
		}
	}


	if (mainEap->EAPMethod == WMX_EAP_AKA)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "SetConfigToSupplicant: AKA method is not supported");

		// TODO: unmark the next lines when .Pin will be supported in the Credentials struct. Erase the two lines above

		//if (eap->Pin[0] == '\0')
		//{
		//	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "SetConfigToSupplicant: Pin is empty");
		//	return WMX_ST_CONFIG_ERROR;
		//}
		//status = wmx_SetPin((wmx_pPin_t)pCredentials->Pin);
		//if (WMX_ST_OK != status)
		//{
		//	return status;
		//}
	}

SupFinalize:

	if(provisionedNSP)
		if (provisionedNSP != NULL){
			free(provisionedNSP);
			provisionedNSP=NULL;
		}

	if (IsNewPrimarySubsInfoAlloc == TRUE)
	{
		if(pPrimarySubsInfo)
			if (pPrimarySubsInfo != NULL){
				free(pPrimarySubsInfo);
				pPrimarySubsInfo = NULL;
			}
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "SetConfigToSupplicant finished successfully");

	return status;
}

wmx_Status_t NDnSAgent_InvokeDualFlushOp(L4C_Task task, void * paramsBuf, UINT32 bufSize)
{
	wmx_Status_t status = WMX_ST_OK;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_InvokeDualFlushOp(IN)");

	L4C_ScheduleTask(Task_Reset); // reset the L4Controller
	L4S_EnableScanner(FALSE);
	L4S_Reset(FALSE); // reset the L4Scanner

	OSAL_reset_event(g_ndnsContext.dualFlushOpEvent);

	g_ndnsContext.scheduledTaskData.status = WMX_ST_FAIL;

	Messenger_PostRequest(MEDIUM, task, paramsBuf, bufSize, &L4C_TaskHandler);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Task '%s' was scheduled for the L4C_TaskHandler", L4C_TaskStr[task]);

	if (OSAL_wait_event(g_ndnsContext.dualFlushOpEvent, L4C_TIMEOUT * 2) != WAIT_OBJECT_0)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Timout - task '%s' execution is too long (more than %d sec)", L4C_TaskStr[task], (L4C_TIMEOUT * 2 / 1000));
		L4C_ScheduleTask(Task_StartScan); // reset the scheduler back to normal scan
		L4S_EnableScanner(TRUE);
		status = WMX_ST_FAIL;
	}
	else
	{
		status = g_ndnsContext.scheduledTaskData.status;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_InvokeDualFlushOp(OUT). Status = %s", wmxGetStatusStr(status));
	return status;
}

void NDnSAgent_OnProgressDualFlush(L4C_Task task, DualFlushOp ExecuteTask, UINT32 phaseNum)
{
	wmx_SystemState_t systemState;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_OnProgressDualFlush(IN) - task: '%s'", L4C_TaskStr[task]);
	// get the current system state
	OSAL_enter_critical_section(&g_ndnsContext.lockSystemState);
	systemState = g_ndnsContext.systemState;
	OSAL_exit_critical_section(&g_ndnsContext.lockSystemState);

	if (phaseNum > 1)
	{
		// reset the L4Scanner in a hard manner since this is an adavanced phase of dual flush
		// (we are now using the messenger thread and the L4Scanner won't be able to get L4 indications
		// for successful reset)
		L4S_Reset(TRUE);
	}

	// if we are already in Ready state and there is no scan in progress - we can execute the connect task
	// (even if we are in Ready state - there could be a pending Scanning state indication from a previous scan)
	if ((systemState == Ready) && (!L4S_IsScanning()))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_OnProgressDualFlush - executing the task: '%s'", L4C_TaskStr[task]);
		// in case the scanner is active (and NOT scanning) - it means that
		// it is sleeping (LinkLoss / Standby state) - so we need to reset it
		if (L4S_READY != L4S_GetScannerState())
		{
			L4S_Reset(TRUE);
		}

		L4C_ScheduleTask(Task_StartScan); // after the session is over - return to normal scan mode
		L4C_UpdateScanStatus(FALSE);

		//Call The Task function if we have any
		if (ExecuteTask != NULL)
		{
			g_ndnsContext.scheduledTaskData.status = ExecuteTask();
		}
		else
		{
			g_ndnsContext.scheduledTaskData.status = WMX_ST_OK;
		}

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_OnProgressDualFlush - task: '%s' executed", L4C_TaskStr[task]);
		//Set Event to release the thread that is waiting for the answer (NDnSAgent_InvokeDualFlushOp())
		OSAL_set_event(g_ndnsContext.dualFlushOpEvent);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_OnProgressDualFlush - scheduling the task '%s' for the next Ready state (current state=%s)", L4C_TaskStr[task], NDnSSystemStates[systemState]);
		// we are still not in Ready state - schedule the Connect task to be executed
		// only when getting to Ready state
		L4C_ScheduleTask(task); // start the task on the next Ready state
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_OnProgressDualFlush(OUT)");
}


wmx_Status_t GetInstallationInfo(void *buffer, UINT32 *bufferSize)
{
	wmx_InstallationInfo_t installInfo;
	wmx_Status_t st;

	// validate return buffer size
	if (*bufferSize >= sizeof(wmx_InstallationInfo_t))
	{
		memset(&installInfo, 0, sizeof(wmx_InstallationInfo_t));

		st = L4db_GetInstallationInfo(installInfo.swVersion, MAX_INSTALLAION_VERSION_SIZE);

		if (st != WMX_ST_OK)
		{
			return st;
		}

		*(wmx_pInstallationInfo_t)buffer = installInfo;

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

//Generates a string of 16 random chars.
wmx_Status_t GeneratePseudoNAI (char *pseudoNai, int buffSize){

	BOOL st;
	static char *lastString;

	if (pseudoNai == NULL || buffSize == 0) {
		return WMX_ST_FAIL;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Trying OSAL_CreateRandomBit...");
	st = OSAL_CreateRandomBit(pseudoNai, buffSize);
	if (st != TRUE)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "OSAL_CreateRandomBit returned FAIL !");
		return WMX_ST_FAIL;
	}

	//pseudoNai[NUMBER_OF_GENERATED_CHARS_FOR_PSEUDO_NAI] = '\0';



	return WMX_ST_OK;

}

wmx_CoexistenceMode_t L4C_GetInitialCoexMode(void)
{
	return initialCoexMode;
}

void L4C_SetProcessStarted(BOOL isProcessStarted)
{
	g_ndnsContext.processStarted = isProcessStarted;
}

wmx_Status_t GetWMFComplianceInfo(void *buffer, UINT32 bufferSize)
{
	wmx_Status_t st;

	st = L4db_WMFComplianceVersion((char *)buffer, bufferSize);
	// validate L4db_WMFComplianceVersion function
	if(WMX_ST_OK == st)
	{
		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}
wmx_Status_t L4C_HandleSystemStateUpdate(wmx_pSystemStateUpdate systemStateUpdate)
{
	BOOL channelUpdated = FALSE;
	// Set Control Mode:
	L4C_SetControllerModeEx(systemStateUpdate, TRUE);

	// Update Platform Noise Mitigation:
	L4db_PNMUpdate(systemStateUpdate, &channelUpdated);
	if (channelUpdated)
	{
		L4C_NotifyPNMChange();
	}
	return WMX_ST_OK;
}


wmx_Status_t L4C_NotifyPNMChange(void)
{
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;
	UINT32 msgSize;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "PNM_SendNotificationEventToPNMService: (IN)");

	msgSize = sizeof(NDNS_MESSAGE);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_PNM_NOTIFICATION;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_PNM_NOTIFICATION;
	pIndMsg->bufferLength = 0;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "PNM_SendNotificationEventToPNMService pSubscribersList=%d, indication_id=%d, "
		, pSendIndData->pSubscribersList, pSendIndData->indication_id);
	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);
	if (pSendIndData != NULL)
		free(pSendIndData);
	return WMX_ST_OK;
}




//	Platform Noise Mitigation
wmx_Status_t L4C_GetIsPNMCommDevUsingChannel(void *buffer, UINT32 *bufferSize)
{

	wmx_Status_t result = WMX_ST_OK;	// By default we are using the channel
	wmx_Status_t TMPstatus;
	PPNM_COMMDEV_CHANNEL_INFO givenPNMInfo;
	pnm_t innerPNMInfo;
	UINT32 innerBufferSize[1];
	*innerBufferSize = sizeof(pnm_t);
	UNREFERENCED_PARAMETER(bufferSize);

	givenPNMInfo = (PPNM_COMMDEV_CHANNEL_INFO)buffer;

	TMPstatus = L4db_GetPNM(&innerPNMInfo, innerBufferSize);

	if (TMPstatus == WMX_ST_OK)
	{
		// The case where we are not using the NPM:
		// 1. We are not connected:
		if (innerPNMInfo.m_dwConnectStatus == PNM_STATUS_NOT_CONNECTED)
		{
			result = WMX_ST_FAIL;
		}

		// 2. We are using a different channel:
		if (innerPNMInfo.m_dwCenterFrequency != givenPNMInfo->m_dwCenterFrequency ||		// Different center frequency or
			innerPNMInfo.m_dwFrequencySpread != givenPNMInfo->m_dwFrequencySpread)		// Different bandwidth
		{
			result = WMX_ST_FAIL;
		}


	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4Pub_GetIsPNMCommDevUsingChannel: Could not get PNM info");
	}
	return result;
}
