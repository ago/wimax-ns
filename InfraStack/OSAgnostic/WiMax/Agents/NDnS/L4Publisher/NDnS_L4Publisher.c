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
#include "NDnS_L4Publisher.h"
#include "wmxSDK_Nds_Internals.h"
#include "NDnSAgent.h"
#include "NDnS_L4Scanner.h"
#include "NDnSAgent_Internals.h"
#include "NDnSAgent_Monitor.h"

#define ASSERT_FILTER_TIMOUT	10000

// globals
L4PublisherContext_t g_l4PublisherContext;

extern tUtilityFunctions *pUtils;
// declarations
wmx_Status_t L4Pub_UpdateDeviceStatus();

///////////////////////////////////
// functions

void L4Pub_Init()
{
	OSAL_init_critical_section( &(g_l4PublisherContext.lock) );
	L4Pub_Reset();	

	if (0 != OSAL_create_event(&g_l4PublisherContext.hTimerEvent, FALSE, FALSE, NULL)) // Auto reset
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Initialize Failed: Creation of L4Pub timer event - Failed!");
		L4Pub_Finalize();	
	}
}

void L4Pub_Finalize()
{
	if (g_l4PublisherContext.hTimerEvent != NULL)
	{
		OSAL_set_event(g_l4PublisherContext.hTimerEvent);
		OSAL_delete_event(g_l4PublisherContext.hTimerEvent);
		g_l4PublisherContext.hTimerEvent = NULL;
	}

	if (&g_l4PublisherContext.lock != NULL /* && &g_l4PublisherContext.lock.DebugInfo != 0x00000000 */)	// @@@ : JSS : Remove - undefined field in criticalsection 
		OSAL_delete_critical_section(&g_l4PublisherContext.lock);
}

void L4Pub_Reset()
{
	g_l4PublisherContext.deviceStatus.deviceStatus = DeviceStatus_UnInitialized;
	g_l4PublisherContext.deviceStatus.connectProgress = 0;
	g_l4PublisherContext.l4cState = L4C_UNINITIALIZED;
	OSAL_ZeroMemory(&g_l4PublisherContext.systemStateUpdate, sizeof(g_l4PublisherContext.systemStateUpdate));
	g_l4PublisherContext.isScanning = FALSE;
	g_l4PublisherContext.scanType = SCAN_TYPE_PREFERRED;
	g_l4PublisherContext.activation = FALSE;
	g_l4PublisherContext.filterDeviceAssertReconnect = FALSE;
}

void L4Pub_CmdReset()
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4Pub_CmdReset - Setting to TRUE");
	g_l4PublisherContext.cmdResetWasCalled = TRUE;
}

void L4Pub_UpdateScanType(wmx_ScanType_t scanType)
{
	OSAL_enter_critical_section(&g_l4PublisherContext.lock);
	g_l4PublisherContext.scanType = scanType;
	//L4Pub_UpdateDeviceStatus();
	OSAL_exit_critical_section(&g_l4PublisherContext.lock);
}

void L4Pub_UpdateScanStatus(BOOL scanStatus)
{
	OSAL_enter_critical_section(&g_l4PublisherContext.lock);
	g_l4PublisherContext.isScanning = scanStatus;
	L4Pub_UpdateDeviceStatus();
	OSAL_exit_critical_section(&g_l4PublisherContext.lock);
}

void L4Pub_UpdateScanState (BOOL scanState)
{
	g_l4PublisherContext.isScanning = scanState;
}

void L4Pub_UpdateStatesChange(L4Pub_pStates_t states)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4Pub_UpdateDeviceStatus(IN) - systemState=%d, l4cState=%d, swRfStatus=%d, hwRfStatus=%d, l4cPreviousState=%d",
		states->pSystemStateUpdate->SystemState, 
		states->l4cState, 
		states->pSystemStateUpdate->rfSwitchesStatus.swRfStatus,
		states->pSystemStateUpdate->rfSwitchesStatus.hwRfStatus,
		g_l4PublisherContext.l4cState);

	OSAL_enter_critical_section(&g_l4PublisherContext.lock);

	// if the device was connected and it has moved to uninitialized state - mask it until we get other indication or a timer is expired.
	// in case the device gets several sequential asserts - the timer will be launched only once.
	if (g_l4PublisherContext.l4cState == L4C_CONNECTED && states->l4cState == L4C_UNINITIALIZED)
	{
		L4Pub_WatchTimerForReconnect();
	}

	// in case the L4C is no longer in UNINITIALIZED state - disable assert masking
	if (g_l4PublisherContext.l4cState == L4C_UNINITIALIZED && states->l4cState != L4C_UNINITIALIZED)
	{
		g_l4PublisherContext.filterDeviceAssertReconnect = FALSE;
		OSAL_set_event(g_l4PublisherContext.hTimerEvent);
	}
	// in case we are in thermal shutdown, disable masking
	if (states->pSystemStateUpdate->ReportStateReason == StateReasonResetThermal)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4Pub_UpdateDeviceStatus: Set Timer for assert masking ignore, thermal shutdown");
		g_l4PublisherContext.filterDeviceAssertReconnect = FALSE;
		OSAL_set_event(g_l4PublisherContext.hTimerEvent);
	}

	if(-1 != states->l4cState)	 
	{	// cache the passed L4C state
		g_l4PublisherContext.l4cState = states->l4cState;
	}

	if(NULL != states->pSystemStateUpdate)	
	{	// cache the passed systemStateUpdate
		L4Pub_SetSystemStateUpdate(states->pSystemStateUpdate);
	}

	L4Pub_UpdateDeviceStatus();
	OSAL_exit_critical_section(&g_l4PublisherContext.lock);
}

// send updates to the L4 Publisher
void L4Pub_UpdateData(L4Pub_CallbackType_t dataType, L4Pub_pCallbackParamsUnion data)
{
	switch(dataType)
	{
	case L4Pub_CbType_StatesChange:
		L4Pub_UpdateStatesChange(&data->statesStruct);
		break;
	case L4Pub_CbType_ScanType:
		L4Pub_UpdateScanType(data->scanType);
		break;
	case L4Pub_CbType_ScanStatus:
		L4Pub_UpdateScanStatus(data->scanStatus);
	    break;
	default:
	    break;
	}

	// after the internal DB was updated, calculate the new device status and publish it
	//L4Pub_UpdateDeviceStatus();
}

void L4Pub_WatchTimerForReconnect(void)
{
	OSAL_thread_t hTimerThread;

	g_l4PublisherContext.filterDeviceAssertReconnect = TRUE;

	if( 0 != OSAL_create_thread(L4Pub_ThreadWatchTimerWatchTimerForReconnect, NULL, &hTimerThread ) )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Initialize Failed: Creation of L4Pub timer thread - Failed!");
	}

}

void L4Pub_ThreadWatchTimerWatchTimerForReconnect(LPVOID lpParam)
{
	UINT32 eventWaitRes;

	UNREFERENCED_PARAMETER(lpParam);	

	eventWaitRes = OSAL_wait_event(g_l4PublisherContext.hTimerEvent, ASSERT_FILTER_TIMOUT);
	switch(eventWaitRes)
	{						
	case WAIT_OBJECT_0: // timer set / shutdown
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4Pub_ThreadWatchTimerWatchTimerForReconnect: timer set");
		break;
	case WAIT_TIMEOUT:	//Timer Expired
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4Pub_ThreadWatchTimerWatchTimerForReconnect: timer expired");		
		OSAL_enter_critical_section(&g_l4PublisherContext.lock);
		if (g_l4PublisherContext.filterDeviceAssertReconnect)
		{		
			g_l4PublisherContext.filterDeviceAssertReconnect = FALSE;
			L4Pub_UpdateDeviceStatus();
		}
		OSAL_exit_critical_section(&g_l4PublisherContext.lock);
		break;
	}
}


// Enters the status of the device (~L4C FSM) to the Buffer, returns an error if buffer is too short.
void L4Pub_SendDeviceStatusUpdate(wmx_DeviceStatus_t deviceStatus, wmx_ConnectionProgressInfo_t connectionProgress)
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;
	char deviceStatusStr[MAX_NAME_STR_LEN];
	char connProgressStr[MAX_NAME_STR_LEN];

	DeviceStatusToStr(deviceStatus, deviceStatusStr, MAX_NAME_STR_LEN);
	ConnectionProgressToStr(connectionProgress, connProgressStr, MAX_NAME_STR_LEN);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "DeviceStatus update: DeviceStatus=%s ConnectionProgress=%s", deviceStatusStr, connProgressStr);

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_DeviceStatus_t) +  sizeof(wmx_ConnectionProgressInfo_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	//[Oran][Reomve reference to L4C stuff]
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE;
	pIndMsg->bufferLength = sizeof(wmx_DeviceStatus_t) +  sizeof(wmx_ConnectionProgressInfo_t);

	OSAL_memcpy_s( pIndMsg->buf, sizeof(wmx_DeviceStatus_t), &deviceStatus, sizeof(wmx_DeviceStatus_t));
	OSAL_memcpy_s( pIndMsg->buf + sizeof(wmx_DeviceStatus_t), sizeof(wmx_ConnectionProgressInfo_t), 
		&connectionProgress, sizeof(wmx_ConnectionProgressInfo_t));

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "SendDeviceStatusUpdate pSubscribersList=%d, indication_id=%d, "
		, pSendIndData->pSubscribersList, pSendIndData->indication_id);
	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);
	if (pSendIndData != NULL)
		free(pSendIndData);
}

void L4Pub_SetDeviceStatusActivationConnect(BOOL activation)
{
	OSAL_enter_critical_section(&g_l4PublisherContext.lock);
	g_l4PublisherContext.activation = activation;
	OSAL_exit_critical_section(&g_l4PublisherContext.lock);	
}

wmx_Status_t L4Pub_UpdateDeviceStatus()
{
	wmx_pDeviceStatus_t	pNewDeviceStatus;
	wmx_DeviceStatus_t	oldDeviceStatus;
	wmx_pConnectionProgressInfo_t pNewConnectionProgress;
	wmx_ConnectionProgressInfo_t oldConnectionProgress;	
	BM_StartEndInd startEndScanInd;

	pNewDeviceStatus = &g_l4PublisherContext.deviceStatus.deviceStatus;
	oldDeviceStatus = *pNewDeviceStatus;
	pNewConnectionProgress = &g_l4PublisherContext.deviceStatus.connectProgress;
	oldConnectionProgress = *pNewConnectionProgress;

	switch (g_l4PublisherContext.l4cState)
	{
	case L4C_UNINITIALIZED:
		if (g_l4PublisherContext.filterDeviceAssertReconnect && !g_l4PublisherContext.cmdResetWasCalled)
		{	// mask device assert - don't update the device status
			//g_l4PublisherContext.deviceStatus.deviceStatus = DeviceStatus_Data_Connected;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4Pub_UpdateDeviceStatus: Assert filtered - skipped Uninitialized DeviceStatus");
		}
		else
		{
			g_l4PublisherContext.deviceStatus.deviceStatus = DeviceStatus_UnInitialized;
			*pNewConnectionProgress = 0;
			g_l4PublisherContext.cmdResetWasCalled = FALSE;
		}

		break;

	case L4C_RF_OFF:
		g_l4PublisherContext.isScanning = FALSE; 
		if((Config == g_l4PublisherContext.systemStateUpdate.SystemState) || 
			(Initialized == g_l4PublisherContext.systemStateUpdate.SystemState) ||
			(RfOff == g_l4PublisherContext.systemStateUpdate.SystemState))
		{
			wmx_RfStatus_t l4db_SwRfStatus = L4db_GetSwRfState();
			if((Off == g_l4PublisherContext.systemStateUpdate.rfSwitchesStatus.hwRfStatus) &&
				(Off == l4db_SwRfStatus))
			{
				*pNewDeviceStatus = DeviceStatus_RF_OFF_HW_SW;
			}
			else if((Off == g_l4PublisherContext.systemStateUpdate.rfSwitchesStatus.hwRfStatus) &&
				(On == l4db_SwRfStatus))
			{
				*pNewDeviceStatus = DeviceStatus_RF_OFF_HW;
			}
			else if((On == g_l4PublisherContext.systemStateUpdate.rfSwitchesStatus.hwRfStatus) &&
				(Off == l4db_SwRfStatus))
			{
				*pNewDeviceStatus = DeviceStatus_RF_OFF_SW;
			}
		}

		break;

	case L4C_SINGLE_SCAN:
		if (g_l4PublisherContext.isScanning)
		{
			*pNewDeviceStatus = DeviceStatus_Scanning;
		}
		else
		{
			*pNewDeviceStatus = DeviceStatus_Ready;
		}
		// override scanning device status
		if (g_l4PublisherContext.scanType == SCAN_TYPE_AUTO_CONNECT ||	// "scan-connect" sequence
			g_l4PublisherContext.scanType == SCAN_TYPE_RECONNECT)		// fast reconnect
		{
			*pNewDeviceStatus = DeviceStatus_Connecting;
			*pNewConnectionProgress = DeviceConnectionProgress_Ranging;
		}
		break;

	case L4C_AUTO_SCAN:
		if (g_l4PublisherContext.isScanning)
		{
			*pNewDeviceStatus = DeviceStatus_Scanning;
		}
		else
		{
			*pNewDeviceStatus = DeviceStatus_Ready;
		}
		// override scanning device status
		if (g_l4PublisherContext.scanType == SCAN_TYPE_AUTO_CONNECT ||	// "scan-connect" sequence
			g_l4PublisherContext.scanType == SCAN_TYPE_RECONNECT)		// fast reconnect
		{
			*pNewDeviceStatus = DeviceStatus_Connecting;
			*pNewConnectionProgress = DeviceConnectionProgress_Ranging;
		}
		break;

	case L4C_CONNECTING:
		*pNewDeviceStatus = DeviceStatus_Connecting;

		//update the connection progress
		if(Connecting == g_l4PublisherContext.systemStateUpdate.SystemState)
		{
			switch(g_l4PublisherContext.systemStateUpdate.ConnectProgress)
			{
			case Ranging:
				*pNewConnectionProgress = DeviceConnectionProgress_Ranging;
				break;

			case SBC:
				*pNewConnectionProgress = DeviceConnectionProgress_SBC;
				break;

			case EAPAuthentication:
				if (TRUE == g_l4PublisherContext.activation)
				{
					*pNewConnectionProgress = DeviceConnectionProgress_EAP_authentication_Device;
				}
				else
				{
					*pNewConnectionProgress = DeviceConnectionProgress_EAP_authentication_User;
				}
				break;

			case ThreeWayHandshake:
				*pNewConnectionProgress = DeviceConnectionProgress_3_way_handshake;
				break;

			case Registration:
				*pNewConnectionProgress = DeviceConnectionProgress_Registration;
				break;
			}
		}
		else if(WimaxConnected == g_l4PublisherContext.systemStateUpdate.SystemState)
		{
			*pNewConnectionProgress = DeviceConnectionProgress_Registered;
		}

		break;

	case L4C_CONNECTED:
		if(DataPathConnected == g_l4PublisherContext.systemStateUpdate.SystemState ||
			Idle == g_l4PublisherContext.systemStateUpdate.SystemState)
		{
			*pNewDeviceStatus = DeviceStatus_Data_Connected;
		}
		break;

	case L4C_DISCONNECTING:
	default: // don't change the state
		//*pNewDeviceStatus = DeviceStatus_Ready;
		break;
	}

	//check if we need to send an indication
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "oldDeviceStatus = %d, oldDeviceStatus = %d, *pNewDeviceStatus = %d, *pNewConnectionProgress = %d",
											oldDeviceStatus, oldConnectionProgress, *pNewDeviceStatus, *pNewConnectionProgress);
	if((oldDeviceStatus != *pNewDeviceStatus) || (oldConnectionProgress != *pNewConnectionProgress))
	{
		L4Pub_SendDeviceStatusUpdate(*pNewDeviceStatus, *pNewConnectionProgress);
	}
	if((DeviceStatus_Scanning != oldDeviceStatus) && (DeviceStatus_Scanning == *pNewDeviceStatus))
	{
		//start scanning
		startEndScanInd = 1;
		wmx_MonitorScanInd(startEndScanInd);
	}
	if((DeviceStatus_Scanning == oldDeviceStatus) && (DeviceStatus_Scanning != *pNewDeviceStatus))
	{
		//end scanning
		startEndScanInd = 2;
		wmx_MonitorScanInd(startEndScanInd);
	}
	
	return WMX_ST_OK;
}


wmx_Status_t L4Pub_GetDeviceStatus(void *buffer, UINT32 *bufferSize)
{
	memset(buffer, 0, *bufferSize);

	OSAL_enter_critical_section(&g_l4PublisherContext.lock);
	*(wmx_pDeviceStatus_t)buffer =  g_l4PublisherContext.deviceStatus.deviceStatus;

	*(wmx_pConnectionProgressInfo_t)((UINT8*)buffer + sizeof(wmx_DeviceStatus_t)) = g_l4PublisherContext.deviceStatus.connectProgress;
	OSAL_exit_critical_section(&g_l4PublisherContext.lock);

	return WMX_ST_OK;
}

void L4Pub_SetSystemStateUpdate(wmx_pSystemStateUpdate systemStateUpdate)
{
	OSAL_memcpy_s(&g_l4PublisherContext.systemStateUpdate, sizeof(wmx_SystemStateUpdate), systemStateUpdate, sizeof(wmx_SystemStateUpdate));
}

// Used to receive status of scan on scan completed event
void L4Pub_SendScanCompleted(wmx_ScanStatus_t scanStatus)
{
	wmx_UserScanStatus_t userScanStatus;
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	// suppress the scan complete update since this is a "scan-connect" cycle
	if (g_l4PublisherContext.scanType == SCAN_TYPE_AUTO_CONNECT)
	{
		return;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "scan completed callback called");

	wmxNds_ScanStatusToUserScanStatus( &userScanStatus, scanStatus );

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "sending scan completed indication");

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_UserScanStatus_t);
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
	pSendIndData->indication_id = NDNS_OPCODE_IND_SCAN_COMPLETED;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_SCAN_COMPLETED;
	pIndMsg->bufferLength = sizeof(wmx_UserScanStatus_t);
	*(wmx_pUserScanStatus_t)pIndMsg->buf = userScanStatus;

	pUtils->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);
	if (pSendIndData != NULL)
		free(pSendIndData);
}
