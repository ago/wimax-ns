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
#include "WiMaxAPI.h"
#include "WiMaxAPIEx.h"
#include "WiMaxTypesEx.h"
#include "wimax_osal_services_cmn.h"	
#include "wimax_osal_types.h"
#include "wimax_osal_primitives.h"
#include "CoexAPI.h"
#include "iWmxSDK.h"
#include "wmxSDK_Msc_Ctrl.h"
#include "wmxSDK_Nds_Ctrl.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Msc_2.h"
#include "wmxSDK_Coex_1.h"
#include "wmxSDK_Coex_3.h"
#include "L4ConfigurationManager.h"
#include "TraceModule.h"
#include "wmxSDK_Nds_InternalStructs.h"


WIMAX_API_RET WIMAX_API AttachToSDK(VOID);
void CleanProfileList();

//definitions
//#define WMX_SF_STATS_MAX_NUM 100
//#define UNREFFERENCED UNREFERENCED_PARAMETER
#define INTEL_DEVICE_ID 0X1
#define MAC_ADDRESS_LENGTH 6
#define COMMON_API_HIGH_VERSION_ID 1
#define COMMON_API_LOW_VERSION_ID 21

#define COMMON_API_HIGH_EX_VERSION_ID 4
#define COMMON_API_LOW_EX_VERSION_ID 100

#define THREAD_JOIN_WAIT 2000

//declaring global variables
static WIMAX_API_PRIVILEGE privilege = WIMAX_API_PRIVILEGE_READ_ONLY;
static OSAL_mutex_t namedMutex;
static BOOL isAPIOpen = FALSE;
static BOOL isAPIOpenHijackable = FALSE;
static OSAL_event_t g_events[3];
static LONG isDeviceOpen = FALSE;
OSAL_critical_section cs;
static WIMAX_API_DEVICE_ID DeviceID = {0};
static LONG isReady = FALSE;
static UINT8 systemStateCBRefCount = 0;
static IndDeviceInsertRemove ctrlStatusCB = NULL;
static IndPermissionsUpdate permissionsUpdateCB = NULL;
static IndControlPowerManagement powerStateCB = NULL;
static IndConnectToNetwork connectCB = NULL;
static IndDisconnectToNetwork disconnectCB = NULL;
static IndDeviceStatusUpdate deviceStatusCB = NULL;
static IndNetworkSearchWideScan networkSearchWideScan = NULL;
static IndNetworkSearchWideScanEx networkSearchWideScanEx = NULL; 
static IndProvisioningOperation provisioningOperationCB = NULL;
static IndPackageDownloadProgress packageDownloadProgress = NULL;
static IndCoexistenceModeUpdate coexistenceModeCB = NULL;
static IndNetworkSearch networkSearch = NULL;
static IndNetworkSearchEx networkSearchEx = NULL;
static IndCurrentPreferredProfile currentPreferredProfile = NULL;
static IndPackageUpdate packageUpdate = NULL;
static IndFastReconnectCapabilityStatusUpdate fastReconnectModeUpdateCB = NULL;
static IndRoamingModeUpdate roamingModeUpdateCB = NULL;
static IndConnectedAsCurrentPreferredCapabilityStatusUpdate connectedAsCurrentPreferredCapabilityStatusCB = NULL;
static IndConnectionModeUpdate connectionModeUpdateCB = NULL;
static IndRfTaken rfTakenCB = NULL;
static IndPNMNotification PNMNotificationCB = NULL;
static IndMediaStatusUpdate mediaStatusUpdate = NULL;
static WIMAX_API_RF_STATE rfState = WIMAX_API_RF_OFF;
static BOOL isConnected = FALSE;
static WIMAX_API_NSP_INFO_EX nspsEx[WMX_NSPS_MAX_NUM];
static UINT32 numberOfNSPs = 0;
static HANDLE namedEvent;
static OSAL_event_t hijackedEvent;
static BOOL exitLoop = TRUE;
static OSAL_event_t releasedEvent;
static OSAL_event_t firstWinsEvent;
static OSAL_event_t closeThreadEvent;
static OSAL_event_t attachedEvent;
static OSAL_event_t detachedEvent;
static OSAL_mutex_t attachDetachMutex;
static BOOL wideScanStarted = FALSE;
static BOOL wideScanStartedAndCompleted = FALSE;
static BOOL isConnectionModeSet = FALSE;
static BOOL isTryingToConnect = FALSE;
static BOOL isTryingToDisconnect = FALSE;
static LONG isAttached = 0; 
static LONG isDetached = 0; 
BOOL isResetAttach = FALSE;
static OSAL_thread_t checkEventsHandle = NULL;
static OSAL_thread_t checkNamedEventHandle = NULL;
void CheckNamedEvent(void *dummy);
void CheckEvents(void *dummy);
BOOL g_hijackedEventOn = FALSE;


struct ProfileList
{
	WIMAX_API_PROFILE_INFO_P profile;
	struct ProfileList *next;
};

typedef struct ProfileList ProfileList_t,*pProfileList_t;

static pProfileList_t profileListHead = NULL;
//typedef struct Globals
//{
//	WIMAX_API_PRIVILEGE privilege;
//	HANDLE namedMutex;
//	BOOL isAPIOpen;
//	BOOL isDeviceOpen;
//	CRITICAL_SECTION cs;
//	WIMAX_API_DEVICE_ID DeviceID = {0};
//	UINT8 systemStateCBRefCount = 0;
//	IndDeviceInsertRemove ctrlStatusCB = NULL;
//	IndControlPowerManagement powerStateCB = NULL;
//	IndConnectToNetwork connectCB = NULL;
//	IndDisconnectToNetwork disconnectCB = NULL;
//	IndDeviceStatusUpdate deviceStatus = NULL;
//	IndNetworkSearchWideScan networkSearchWideScan = NULL;
//	WIMAX_API_RF_STATE rfState = WIMAX_API_RF_OFF;
//	BOOL isConnected = FALSE;
//	WIMAX_API_NSP_INFO nsps[WMX_NAPS_MAX_NUM];
//	UINT32 numberOfNSPs = 0;
//}g_Globals;


//Helper functions

//the function convert WIMAX_API_NSP_INFO_EX into WIMAX_API_NSP_INFO
//it is the user responsibility to allocate the space for the WIMAX_API_NSP_INFO array
void nspInfoExToNspInfo(WIMAX_API_NSP_INFO_EX_P pNSPInfoEx,
						WIMAX_API_NSP_INFO_P pNSPInfo,
						UINT32 arrayLength)
{
	UINT32 i;
	for (i=0; i<arrayLength; i++)
	{
		pNSPInfo[i].CINR = pNSPInfoEx[i].CINR;
		pNSPInfo[i].RSSI = pNSPInfoEx[i].RSSI; 
		pNSPInfo[i].NSPid = pNSPInfoEx[i].NSPid;
		
		OSAL_ZeroMemory(pNSPInfo[i].NSPName, sizeof(pNSPInfo[i].NSPName));           
	    OSAL_CAPI_wmemcpy_s(pNSPInfo[i].NSPName, WMX_NSP_NAME_MAX_SIZE, pNSPInfoEx[i].NSPName, OSAL_CAPI_wcsnlen(pNSPInfoEx[i].NSPName , WMX_NSP_NAME_MAX_SIZE - 1));
		
		pNSPInfo[i].networkType = pNSPInfoEx[i].networkType;
		pNSPInfo[i].structureSize = pNSPInfoEx[i].structureSize;
	}	
}

void ResetAttachement(void *dummy)
{
	static BOOL firstTime = TRUE;
	UNREFERENCED_PARAMETER(dummy);

	OSAL_enter_critical_section(&cs);	

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ResetAttachement(IN) - DetachFromSDK");
	DetachFromSDK();

	while( (READY == wmxSDK_GetCtrlStatus()) )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ResetAttachement - Trying to AttachToSDK");
		isResetAttach = firstTime;
		if (WIMAX_API_RET_SUCCESS == AttachToSDK())
		{			
			firstTime = FALSE;
			OSAL_atomic_compareExchange(&isReady, TRUE, FALSE);
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ResetAttachement - AttachToSDK succeeded. isReady=%d , isDeviceOpen=%d",isReady, isDeviceOpen);
			//if (isDeviceOpen)
			{			
				OSAL_atomic_compareExchange((LONG *)&DeviceID.devicePresenceStatus, TRUE, FALSE);
				if (ctrlStatusCB != NULL)
				{
					OSAL_exit_critical_section(&cs);
					ctrlStatusCB(&DeviceID, TRUE);
					TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ResetAttachement(OUT) - ctrlStatusCB()");
					return;
				}
			}
			break;
		}
		else
		{
			firstTime = TRUE;
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ResetAttachement - AttachToSDK failed");
			OSAL_sleep(100);
		}
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ResetAttachement(OUT) - wmxSDK_GetCtrlStatus()=%d, isReady=%d",
												wmxSDK_GetCtrlStatus(), isReady);
	OSAL_exit_critical_section(&cs);
}



WIMAX_API_RET WmxStatusToWimaxAPIRet( wmx_Status_t wmxStatus )
{
	switch(wmxStatus)
	{
	case WMX_ST_OK:
		return WIMAX_API_RET_SUCCESS;

	case WMX_ST_PIPE_NOT_CONNETED:
		return WIMAX_API_RET_LINK_NOT_CONNECTED;

	case WMX_ST_DEVICE_NOT_FOUND:
		return WIMAX_API_RET_DEVICE_MISSING;

	case WMX_ST_RESPONSE_BUFFER_TOO_SHORT:
	case WMX_ST_BUFFER_TOO_SHORT:
		return WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;

	case WMX_ST_WRONG_ARGUMENT:
		return WIMAX_API_RET_INVALID_PARAMETER;

	case WMX_ST_NSP_ID_NOT_FOUND:
		return WIMAX_API_RET_NETWORK_PROHIBITED;

	case WMX_ST_NO_RF:
		return WIMAX_API_RET_INTEL_NO_RF;

	case WMX_ST_PIPE_FAILURE:
	case WMX_ST_DEVICE_FAILURE:
	case WMX_ST_DEVICE_BUSY:
	case WMX_ST_DEVICE_NOT_READY:
	case WMX_ST_CALLBACK_NOT_REGISTERED:
	case WMX_ST_CALLBACK_ALREADY_REGISTERED:
	case WMX_ST_INDICATION_NOT_REGISTERED:
	case WMX_ST_INDICATION_ALREADY_REGISTERED:
	case WMX_ST_NO_ROOM_FOR_INDICATION:
	case WMX_ST_ILLEGAL_OPERATION:
	case WMX_ST_INVALID_OPCODE:
	case WMX_ST_DATA_UNAVAILABLE:
	case WMX_ST_MODULE_NOT_INITIALIZED:
	case WMX_ST_CONFIG_ERROR:
	case WMX_ST_VERSION_VALIDATION_ERROR:
	case WMX_ST_VERSION_VALIDATION_WARNING:
	case WMX_ST_NULL_APPSRV_IP_ADDRESS:
	case WMX_ST_TRACE_INIT_FAILED:
	case WMX_ST_NULL_L5_DISPATCHER_FUNCTIONS_POINTER:
	case WMX_ST_PIPE_HANDLER_LOAD_FAILED:
	case WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED:
	case WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED:
	case WMX_ST_SPECIFIC_WRAPPER_SET_MSNGR_FUNCTIONS_FAILED:
	case WMX_ST_IWMXSDK_INTERNAL_FAILURE:
	case WMX_ST_APDO_PATH_NOT_FOUND:
	case WMX_ST_DEVICE_NOT_PROVISIONED:
	case WMX_ST_FAIL:
	default:
		return WIMAX_API_RET_FAILED;

	}

	// TODO: Darzi - this code is unreachable
	//return WIMAX_API_RET_LAST_COMMON_ERROR;
}



WIMAX_API_RET CheckParamsAndPermissions(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL writePermission, BOOL needDevice)
{
	//check that in pointers are valid
	if (pDeviceId == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "pDeviceId == NULL, WIMAX_API_RET_INVALID_PARAMETER");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	if (writePermission && pDeviceId->privilege != privilege)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "writePermission = %d pDeviceId->privilege = %d", writePermission, pDeviceId->privilege);
		return WIMAX_API_RET_PERMISSON_DENIED;
	}

	if (writePermission && privilege==WIMAX_API_PRIVILEGE_READ_ONLY)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "writePermission = %d privilege = WIMAX_API_PRIVILEGE_READ_ONLY", writePermission);
		return WIMAX_API_RET_PERMISSON_DENIED;
	}
	//check if API is opened
	if (!isAPIOpen)
	{
		return WIMAX_API_RET_FAILED;
	}

	if (needDevice && (!isDeviceOpen || pDeviceId->deviceIndex != INTEL_DEVICE_ID))
	{
		return WIMAX_API_RET_DEVICE_MISSING;
	}

	return WIMAX_API_RET_SUCCESS;
}
//========================================================================
// Local Function
//=======================================================================

WIMAX_API_DEVICE_STATUS WmxToCommonGetDeviceStatus(wmx_DeviceStatus_t deviceStatus)
{
	switch(deviceStatus)
	{
	case DeviceStatus_UnInitialized:
		return WIMAX_API_DEVICE_STATUS_UnInitialized;
	case DeviceStatus_RF_OFF_HW_SW:
		return WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW;
	case DeviceStatus_RF_OFF_HW:
		return WIMAX_API_DEVICE_STATUS_RF_OFF_HW;
	case DeviceStatus_RF_OFF_SW:
		return WIMAX_API_DEVICE_STATUS_RF_OFF_SW;
	case DeviceStatus_Ready:
		return WIMAX_API_DEVICE_STATUS_Ready;
	case DeviceStatus_Scanning:
		return WIMAX_API_DEVICE_STATUS_Scanning;
	case DeviceStatus_Connecting:
		return WIMAX_API_DEVICE_STATUS_Connecting;
	case DeviceStatus_Data_Connected:
		return WIMAX_API_DEVICE_STATUS_Data_Connected;
	};
	return WIMAX_API_DEVICE_STATUS_UnInitialized;
}

WIMAX_API_CONNECTION_PROGRESS_INFO GetConnectionProgress(wmx_ConnectionProgressInfo_t connectionProgressInfo)
{
	switch(connectionProgressInfo)
	{
	case DeviceConnectionProgress_Ranging:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_Ranging;
	case DeviceConnectionProgress_SBC:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_SBC;
	case DeviceConnectionProgress_EAP_authentication_Device:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_EAP_authentication_Device;
	case DeviceConnectionProgress_EAP_authentication_User:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_EAP_authentication_User;
	case DeviceConnectionProgress_3_way_handshake:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_3_way_handshake;
	case DeviceConnectionProgress_Registration:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_Registration;
	case DeviceConnectionProgress_De_registration:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_De_registration;
	case DeviceConnectionProgress_Registered:
		return WIMAX_API_DEVICE_CONNECTION_PROGRESS_Registered;	
	};

	return WIMAX_API_DEVICE_CONNECTION_PROGRESS_Ranging;
}
void wmx_rfStateUpdate(WIMAX_API_RF_STATE powerModeToUpdate)
{
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "wmx_rfStateUpdate: powerModeToUpdate=%d , rfState=%d",powerModeToUpdate, rfState);
	if (rfState != powerModeToUpdate)
	{	
		if (powerStateCB != NULL)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Calling powerStateCB with %d",powerModeToUpdate);
			powerStateCB(&DeviceID, powerModeToUpdate);
		}
		rfState = powerModeToUpdate;
	}
}

//CB functions
void DeviceStateCB( wmx_DeviceStatus_t deviceStatus, wmx_ConnectionProgressInfo_t connectionProgressInfo)
{
	static BOOL isValidForConnectionFailure;
	BOOL connectState = FALSE;

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "DeviceStateCB(IN)");

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Got DeviceStateCB. deviceStatus=%d",deviceStatus);
	switch (deviceStatus)
	{
	case DeviceStatus_UnInitialized:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_UnInitialized, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
		}
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "DeviceStateCB(OUT) - DeviceStatus_UnInitialized");
		return;

	case DeviceStatus_RF_OFF_HW:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_RF_OFF_HW, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
			isValidForConnectionFailure = FALSE;
		}
		wideScanStartedAndCompleted = wideScanStarted = FALSE;
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "wideScanStartedAndCompleted = FALSE, DeviceStateCB - DeviceStatus_RF_OFF_HW");
		wmx_rfStateUpdate(WIMAX_API_RF_OFF);
		break;

	case DeviceStatus_RF_OFF_SW:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_RF_OFF_SW, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
			isValidForConnectionFailure = FALSE;
		}
		wideScanStartedAndCompleted = wideScanStarted = FALSE;
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "wideScanStartedAndCompleted = FALSE, DeviceStateCB - DeviceStatus_RF_OFF_SW");
		wmx_rfStateUpdate(WIMAX_API_RF_OFF);
		break;

	case DeviceStatus_RF_OFF_HW_SW:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_RF_OFF_HW_SW, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
			isValidForConnectionFailure = FALSE;
		}
		wideScanStartedAndCompleted = wideScanStarted = FALSE;
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "wideScanStartedAndCompleted = FALSE, DeviceStateCB - DeviceStatus_RF_OFF_HW_SW");
		break;

	case DeviceStatus_Ready:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_Ready, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
		}
		wmx_rfStateUpdate(WIMAX_API_RF_ON);
		break;

	case DeviceStatus_Scanning:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_Scanning, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
			isValidForConnectionFailure = FALSE;
		}
		wmx_rfStateUpdate(WIMAX_API_RF_ON);
		break;

	case DeviceStatus_Connecting:
		if (deviceStatusCB != NULL)
		{
			isValidForConnectionFailure = TRUE;
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_Connecting, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
		}
		wmx_rfStateUpdate(WIMAX_API_RF_ON);
		break;

	case DeviceStatus_Data_Connected:
		if (deviceStatusCB != NULL)
		{
			deviceStatusCB(&DeviceID, WIMAX_API_DEVICE_STATUS_Data_Connected, DeviceStatusReason_Normal, GetConnectionProgress(connectionProgressInfo));
			isValidForConnectionFailure = FALSE;
		}
		connectState = TRUE;
		wmx_rfStateUpdate(WIMAX_API_RF_ON);
		break;
	
	default:
		TRACE(TR_MOD_COMMON_API, TR_SEV_CRITICAL, "Got deviceStatus is in default case. deviceStatus=%d",deviceStatus);
			
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "DeviceStateCB connectState = %d, isConnected = %d, isTryingToConnect = %d, isTryingToDisconnect = %d", 
		connectState,  isConnected, isTryingToConnect, isTryingToDisconnect);
	if (connectState)
	{
		//connect indication
		if (!isConnected)
		{	
			if (connectCB != NULL)
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Calling connectCB - CONNECTION_SUCCESS");
				connectCB(&DeviceID, WIMAX_API_CONNECTION_SUCCESS);	
				TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "after Calling connectCB");
			}
			isConnected = TRUE;
		}
		isTryingToConnect = FALSE;	

		//disconnect indication
		if (isTryingToDisconnect)
		{
			if (disconnectCB != NULL)
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Calling disconnectCB - CONNECTION_FAILURE");
				disconnectCB(&DeviceID, WIMAX_API_CONNECTION_FAILURE);	
			}
			isTryingToDisconnect = FALSE;
		}
	}
	else
	{	
		//connect indication
		if ((isTryingToConnect == TRUE) && (DeviceStatus_Connecting != deviceStatus) && isValidForConnectionFailure)
		{
			if (connectCB != NULL)
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Calling connectCB - CONNECTION_FAILURE");
				connectCB(&DeviceID, WIMAX_API_CONNECTION_FAILURE);	
			}
			isTryingToConnect = FALSE;
		}	

		//disconnect indication
		if (isConnected)
		{	
			if (disconnectCB != NULL)
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Calling disconnectCB - CONNECTION_SUCCES");
				disconnectCB(&DeviceID, WIMAX_API_CONNECTION_SUCCESS);	
			}
			isTryingToDisconnect = FALSE;
			isConnected = FALSE;
		}
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "DeviceStateCB(OUT) - function ended");
}



// Translate the NSPs array to Profiles array and call the user's callback
void CurrentPreferredProfileCB(	UINT32 numOfCurrentPreferredNSPs, wmx_pNSP_t currentPreferredNsps)
{
	WIMAX_API_PROFILE_INFO currentPreferredProfiles[WMX_NSPS_MAX_NUM];
	UINT32 i;
	int nspNameConv;
	//wideScanStartedAndCompleted = FALSE;
	if (currentPreferredNsps == NULL)
	{
		return;
	}

	// Check if the callback was registered by the user
	if (currentPreferredProfile != NULL)
	{
		// Convert the NSPs to profiles
		for (i=0; i < numOfCurrentPreferredNSPs; i++)
		{			
			if (currentPreferredNsps[i].numOfNspIDs > 0)
			{
				currentPreferredProfiles[i].profileID = currentPreferredNsps[i].nspIDs[0];
			}
			
			nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, currentPreferredNsps[i].nspName, (int)OSAL_strnlen((const char*)currentPreferredNsps[i].nspName, MAX_SIZE_OF_STRING_BUFFER) + 1, currentPreferredProfiles[i].profileName, sizeof(currentPreferredProfiles[i].profileName)/sizeof(currentPreferredProfiles[i].profileName[0]));
			if( nspNameConv == 0 )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_CRITICAL, "Failed to convert nspName to WideChar");
			}
			currentPreferredProfiles[i].structureSize = sizeof(currentPreferredProfiles[i]);
		}
		
		// Call the user's callback
		currentPreferredProfile(&DeviceID, numOfCurrentPreferredNSPs, currentPreferredProfiles);
	}
}

void WimaxScanCompletedCB( wmx_UserScanStatus_t userScanStatus)
{
	WIMAX_API_NSP_INFO nsps[WMX_NSPS_MAX_NUM];

	UNREFERENCED_PARAMETER(userScanStatus);
	
	if (wideScanStarted /*&& (scanProgress == 100)*/)
	{		
		if (networkSearchWideScan != NULL)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WimaxScanCompletedCB(IN)");
			
			//convert the WIMAX_API_NSP_INFO_EX Array into WIMAX_API_NSP_INFO array
			if(WMX_NSPS_MAX_NUM >= numberOfNSPs)
			{
				nspInfoExToNspInfo(nspsEx, nsps, numberOfNSPs);
				networkSearchWideScan(&DeviceID, nsps, numberOfNSPs);
			}
			wideScanStarted = FALSE;
			wideScanStartedAndCompleted = TRUE;
		}
		if (networkSearchWideScanEx != NULL)
		{		
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WimaxScanCompletedCB(IN)");
			networkSearchWideScanEx(&DeviceID, nspsEx, numberOfNSPs);
			wideScanStarted = FALSE;
			wideScanStartedAndCompleted = TRUE;
		}
	}
}

void WimaxUserScanUpdateCB( UINT32 numOfNsps, wmx_pNSP_t pNsps, UINT32 scanProgress )
{
	UINT32 i;
	WIMAX_API_NSP_INFO nsps[WMX_NSPS_MAX_NUM];
	int nspNameConv;
	UINT32 numOfPreferredNSP;
	wmx_NSP_t currentPreferredNsp;
	wmx_Status_t status;
	

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WimaxUserScanUpdateCB(IN)");
	OSAL_ZeroMemory(nspsEx, WMX_NSPS_MAX_NUM * sizeof(WIMAX_API_NSP_INFO));
	status = wmx_GetCurrentPreferredNSP(&currentPreferredNsp, &numOfPreferredNSP);
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "WimaxUserScanUpdateCB: wmx_GetCurrentPreferredNSP failed");
	}
	for (i=0; i<numOfNsps; i++)
	{
		if ((numOfPreferredNSP > 0) && !wideScanStarted)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "GetNetworkListEx : checking if (pNsps[%d].nspIDs[0])[%d]==[%d](currentPreferredNsp.nspIDs[0])",i,pNsps[i].nspIDs[0],currentPreferredNsp.nspIDs[0]);
			if(currentPreferredNsp.nspIDs[0] == pNsps[i].nspIDs[0])
			{
				nspsEx[i].CINR = (UINT8)pNsps[i].bestCINR;
				nspsEx[i].RSSI = (UINT8)pNsps[i].bestRssi; 
				nspsEx[i].NSPid = pNsps[i].nspIDs[0];
				nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, pNsps[i].nspName, (int)OSAL_strnlen(pNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE)+1, nspsEx[i].NSPName, sizeof(nspsEx[i].NSPName)/sizeof(nspsEx[i].NSPName[0]));
				if( nspNameConv == 0 )
				{
					TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to WideChar");
				}
				nspsEx[i].networkType = WIMAX_API_HOME;
				nspsEx[i].structureSize = sizeof(nspsEx[i]);
				nspsEx[i].linkQuality = pNsps[i].linkQuality;
				numOfNsps = 1;
				break;
			}
		}
		else
		{
			nspsEx[i].CINR = (UINT8)pNsps[i].bestCINR;
			nspsEx[i].RSSI = (UINT8)pNsps[i].bestRssi; 
			nspsEx[i].NSPid = pNsps[i].nspIDs[0];
			nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, pNsps[i].nspName, (int)OSAL_strnlen(pNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE)+1, nspsEx[i].NSPName, sizeof(nspsEx[i].NSPName)/sizeof(nspsEx[i].NSPName[0]));
			if( nspNameConv == 0 )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_CRITICAL, "Failed to convert nspName to WideChar");
			}
			nspsEx[i].networkType = WIMAX_API_HOME;
			nspsEx[i].structureSize = sizeof(nspsEx[i]);
			nspsEx[i].linkQuality = pNsps[i].linkQuality;
		}
	}

	numberOfNSPs = numOfNsps;

	if (networkSearch != NULL)
	{
		if(WMX_NSPS_MAX_NUM >= numberOfNSPs)
		{
			//convert the WIMAX_API_NSP_INFO_EX Array into WIMAX_API_NSP_INFO array
			nspInfoExToNspInfo(nspsEx, nsps, numberOfNSPs);
			networkSearch(&DeviceID, nsps, numberOfNSPs, scanProgress);
		}
	}

	if (networkSearchEx != NULL)
	{
		networkSearchEx(&DeviceID, nspsEx, numberOfNSPs, scanProgress);
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WimaxUserScanUpdateCB(OUT) - found %d networks", numberOfNSPs);
}
void CtrlStatusCB(wmx_CtrlStatus_t ctrlStatus)
{
	HANDLE hThread = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_INFO, "CtrlStatusCB(IN). ctrlStatus=%d",ctrlStatus);

	if (READY == ctrlStatus)
	{			
		OSAL_create_thread(ResetAttachement, NULL, hThread );				
		//ResetAttachement(NULL);
	}
	else if(NOT_READY == ctrlStatus)
	{	
		OSAL_atomic_compareExchange(&isReady, FALSE, TRUE);
		OSAL_atomic_compareExchange((LONG *)&DeviceID.devicePresenceStatus, FALSE, TRUE);
		//if (isDeviceOpen)
		{		
			if (ctrlStatusCB != NULL)
			{
				ctrlStatusCB(&DeviceID, FALSE);
			}
		}
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_INFO, "CtrlStatusCB(OUT)");
}

void wmxProvisioningOperationCB(wmx_ProvisioningOperation_t	provisioningOperation, UINT16 contactType )
{
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "provisioning operation CB(IN). operation=%d, contactType=%d",
		provisioningOperation, contactType);

	if (provisioningOperationCB != NULL)
	{		
		switch(provisioningOperation)
		{
		case poUpdateStarted:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_STARTED, 0);
			break;
		case poUpdateCompleted:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_COMPLETED, 0);
			break;
		case poUpdateFailedNetworkDisconnect:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_NETWORK_DISCONNECT, 0);
			break;
		case poUpdateFailed:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED, 0);
			break;
		case poUpdateFailedInvalidProvisioning:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_INVALID_PROVISIONING, 0);
			break;
		case poUpdateFailedBadAuthentication:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_FAILED_BAD_AUTHENTICATION, 0);
			break;
		case poUpdateRequestInitialProvisioning:
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_INITIAL_PROVISIONING, 0);
			break;
		case poUpdateRequestOngoingProvisioning:
			// [mzur][todo] This is not raised in V3
			//provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_ONGOING_PROVISIONING, 0);
			break;
		case poUpdateWaitingForBootstrap:
			// [mzur][todo] This is not raised in V3
			//provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_ONGOING_PROVISIONING, 0);
			break;
		case poUpdateBootstrapArrived:
			// [mzur][todo] This is not raised in V3
			//provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_REQUEST_ONGOING_PROVISIONING, 0);
			break;
		case poUpdateLoadWebBrowser: 
			provisioningOperationCB(&DeviceID, WIMAX_API_PROV_OPERATION_CFG_UPDATE_TRIGGER_CONTACT, contactType);
			break;
		}
	}
}
void wmxCoexistenceModeCB(wmx_CoexistenceMode_t coexMode)
{
	if (coexistenceModeCB != NULL)
	{
		switch(coexMode)
		{
		case WMX_MODE_XOR:
			coexistenceModeCB(&DeviceID, MODE_XOR);
			break;
		case WMX_MODE_CM:
			coexistenceModeCB(&DeviceID, MODE_CM);
			break;
		}		
	}
}
void wmxConnectionModeUpdateCB(wmx_UserConnectMode_t connectionModeUpdate)
{
	if (connectionModeUpdateCB != NULL)
	{
		switch(connectionModeUpdate)
		{
			case UserSemiManScanManConnect:
				connectionModeUpdateCB(&DeviceID, WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT);
				break;
			case UserSemiManScanAutoConnect:
				connectionModeUpdateCB(&DeviceID, WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT);
				break;
			case UserAutoScanManConnect:
				connectionModeUpdateCB(&DeviceID, WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT);
				break;
			case UserAutoScanAutoConnect:
				connectionModeUpdateCB(&DeviceID, WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT);
				break;
			case UserManScanManConnect:
				connectionModeUpdateCB(&DeviceID, WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT);
				break;
		}		
	}
}
void wmxRoamingModeUpdateCB(wmx_UserRoamingMode_t roamingModeUpdate)
{
	if (roamingModeUpdateCB != NULL)
	{
		switch(roamingModeUpdate)
		{
			case UserEnableRoaming:
				roamingModeUpdateCB(&DeviceID, WIMAX_API_ROAMING_ENABLED);
				break;
			case UserDisableRoaming:
				roamingModeUpdateCB(&DeviceID, WIMAX_API_ROAMING_DISABLED);
				break;
		}		
	}
}
void wmxFastReconnectModeUpdateCB(BOOL fastReconnectModeUpdate)
{
	if (fastReconnectModeUpdateCB != NULL)
	{
		fastReconnectModeUpdateCB(&DeviceID, fastReconnectModeUpdate);
	}
}

void wmxConnectedAsCurrentPreferredCapabilityStatusCB(BOOL fastReconnectModeUpdate)
{
	if (connectedAsCurrentPreferredCapabilityStatusCB != NULL)
	{
		connectedAsCurrentPreferredCapabilityStatusCB(&DeviceID, fastReconnectModeUpdate);
	}
}

void wmxPermissionsUpdateCB(BOOL fastReconnectModeUpdate)
{
	if (connectedAsCurrentPreferredCapabilityStatusCB != NULL)
	{
		connectedAsCurrentPreferredCapabilityStatusCB(&DeviceID, fastReconnectModeUpdate);
	}
}

void wmxUserMediaStatusCB( wmx_MediaStatus_t mediaStatus)
{
	if(mediaStatusUpdate != NULL)
	{
		if (mediaStatus == WIMAX_API_MEDIA_STATUS_LINK_UP ||
			mediaStatus == WIMAX_API_MEDIA_STATUS_LINK_DOWN ||
			mediaStatus == WIMAX_API_MEDIA_STATUS_LINK_RENEW)
		{
			mediaStatusUpdate(&DeviceID, mediaStatus);
		}
	}
}

void PackageUpdateBC( wmx_PackageUpdateStatus_t packageUpdateStatus )
{
	if (packageUpdate != NULL)
	{
		switch(packageUpdateStatus)
		{
		case psUpdateReceived:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_RECEIVED);
			break;
		case psUpdateReceivedLowerStack:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_RECEIVED_LOWER_STACK);
			break;
		case psUpdateReceivedFullStack:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_RECEIVED_FULL_STACK);
			break;
		case psUpdateReceivedOmaDmClient:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_RECEIVED_OMA_DM_CLIENT);
			break;
		case psUpdateStarted:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_STARTED);
			break;
		case psUpdateCompleted:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_COMPLETED);
			break;
		case psUpdateFailedNetworkDisconnected:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_FAILED_NETWORK_DISCONNECTED);
			break;
		case psUpdateFailedInvalidPackage:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_FAILED_INVALID_PACKAGE);
			break;
		case psUpdateFailedBadAuthentication:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_FAILED_BAD_AUTHENTICATION);
			break;
		case psUpdateFailed:
			packageUpdate(&DeviceID, WIMAX_API_PACK_UPDATE_FAILED);
			break;
		}
	}
}
void wmxRfTakenCB(void)
{
	if (rfTakenCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "wmxRfTakenCB(IN)");

		rfTakenCB(&DeviceID);
	}
}


void wmxPNMNotificationCB(void)
{
	if (PNMNotificationCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "wmxPNMNotificationCB(IN)");

		PNMNotificationCB(&DeviceID);
	}
}


// This function at this point only contains psUpdateFumoDownloadProgress in the enum.
// If more values are added we should add case here. 
void PackageDownloadProgressCB( wmx_PackageDownloadProgressInfo_t packageDownloadProgressInfo )
{
	// Convert the input packageDownloadProgressInfo to a WIMAX_API_PACK_DOWNLOAD_INFO_P type.
	WIMAX_API_PACK_DOWNLOAD_INFO wmxPackageDownloadProgressInfo;	
	wmxPackageDownloadProgressInfo.downloadedBytes =  packageDownloadProgressInfo.downloadedBytes;
	wmxPackageDownloadProgressInfo.totalBytes = packageDownloadProgressInfo.totalBytes;
	
	if (packageDownloadProgress != NULL)
	{
		packageDownloadProgress(&DeviceID, &wmxPackageDownloadProgressInfo); 
	}
}

//Common APIs:
WIMAX_API_RET WIMAX_API GetErrorString(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_RET errorCode, WIMAX_API_WSTRING buffer, UINT32 * pLength)
{	
	UNREFERENCED_PARAMETER(pDeviceId);
	switch(errorCode)
	{
	case WIMAX_API_RET_FIRST_COMMON_ERROR:
		*pLength = (UINT32)strlen("WIMAX_API_RET_FIRST_COMMON_ERROR");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_FIRST_COMMON_ERROR"));
		break;
	case WIMAX_API_RET_SUCCESS:
		*pLength = (UINT32)strlen("WIMAX_API_RET_SUCCESS");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_SUCCESS"));
		break;
	case WIMAX_API_RET_FAILED:
		*pLength = (UINT32)strlen("WIMAX_API_RET_FAILED");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_FAILED"));
		break;
	case WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL:
		*pLength = (UINT32)strlen("WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL"));
		break;
	case WIMAX_API_RET_PERMISSON_DENIED:
		*pLength = (UINT32)strlen("WIMAX_API_RET_PERMISSON_DENIED");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_PERMISSON_DENIED"));
		break;
	case WIMAX_API_RET_INVALID_DEVICE:
		*pLength = (UINT32)strlen("WIMAX_API_RET_INVALID_DEVICE");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_INVALID_DEVICE"));
		break;
	case WIMAX_API_RET_INVALID_PARAMETER:
		*pLength = (UINT32)strlen("WIMAX_API_RET_INVALID_PARAMETER");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_INVALID_PARAMETER"));
		break;
	case WIMAX_API_RET_ALREADY_CONNECTED:
		*pLength = (UINT32)strlen("WIMAX_API_RET_ALREADY_CONNECTED");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_ALREADY_CONNECTED"));
		break;
	case WIMAX_API_RET_LINK_NOT_CONNECTED:
		*pLength = (UINT32)strlen("WIMAX_API_RET_LINK_NOT_CONNECTED");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_LINK_NOT_CONNECTED"));
		break;
	case WIMAX_API_RET_NETWORK_PROHIBITED:
		*pLength = (UINT32)strlen("WIMAX_API_RET_NETWORK_PROHIBITED");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_NETWORK_PROHIBITED"));
		break;
	case WIMAX_API_RET_DEVICE_MISSING:
		*pLength = (UINT32)strlen("WIMAX_API_RET_DEVICE_MISSING");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_DEVICE_MISSING"));
		break;
	case WIMAX_API_RET_INVALID_PROFILE:
		*pLength = (UINT32)strlen("WIMAX_API_RET_INVALID_PROFILE");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_INVALID_PROFILE"));
		break;
	case WIMAX_API_RET_ROAMING_NOT_ALLOWED:
		*pLength = (UINT32)strlen("WIMAX_API_RET_ROAMING_NOT_ALLOWED");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_ROAMING_NOT_ALLOWED"));
		break;
	case WIMAX_API_RET_CONNECTION_IN_PROGRESS:
		*pLength = (UINT32)strlen("WIMAX_API_RET_CONNECTION_IN_PROGRESS");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_CONNECTION_IN_PROGRESS"));
		break;
	case WIMAX_API_RET_LAST_COMMON_ERROR:
		*pLength = (UINT32)strlen("WIMAX_API_RET_LAST_COMMON_ERROR");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_LAST_COMMON_ERROR"));
		break;		
	case WIMAX_API_RET_INTEL_NO_RF:
		*pLength = (UINT32)strlen("WIMAX_API_RET_INTEL_NO_RF");
		OSAL_CAPI_strcpy_s(buffer, TEXT_LEN(*pLength)+1, TEXT("WIMAX_API_RET_INTEL_NO_RF"));
		break;
	}
	return WIMAX_API_RET_SUCCESS;
}
//Device detection, association and initialization
WIMAX_API_RET WIMAX_API WiMaxAPIOpen(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus;
	BOOL regData;
	UINT32 privData;
	exitLoop = TRUE;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxAPIOpen(IN)");

	//check that in pointer is valid
	if (pDeviceId == NULL)
	{
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	OSAL_init_critical_section(&cs);

	OSAL_enter_critical_section(&cs);
	if (isAPIOpen)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "isAPIOpen in on, can't open API");
		OSAL_exit_critical_section(&cs);
		return WIMAX_API_RET_FAILED;
	}
	isAPIOpen = TRUE;
	OSAL_exit_critical_section(&cs);
		
	if (0 != OSAL_create_event(&attachedEvent, TRUE, FALSE, NULL))
	{
		isAPIOpen = FALSE;
		return WIMAX_API_RET_FAILED;
	}

	if (0 != OSAL_create_event(&detachedEvent, TRUE, TRUE, NULL))
	{
		isAPIOpen = FALSE;
		return WIMAX_API_RET_FAILED;
	}

	if (0 != OSAL_create_mutex(&attachDetachMutex, FALSE, NULL))
	{
		isAPIOpen = FALSE;
		return WIMAX_API_RET_FAILED;
	}
	// in case another CU is open, ignore the error code ERROR_ALREADY_EXISTS
	if (0 != OSAL_create_event_with_security_attributes(&releasedEvent, FALSE, FALSE, "Global\\ReleasedPerimissionEvent"))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}
	if (0 != OSAL_create_event_with_security_attributes(&hijackedEvent, FALSE, FALSE, "Global\\HijackedPerimissionEvent"))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}

	if (0 != OSAL_create_event_with_security_attributes(&firstWinsEvent, TRUE, FALSE, "Global\\FirstWinsEvent"))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}
	if (0 != OSAL_create_event(&closeThreadEvent, FALSE, FALSE, NULL))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}
	
	//read registry to see if we want to block 2 apps with RW priviladges
	regData = L4Configurations_getCommonPriviledgeEnable(&privData);
	if ((regData == FALSE || privData == 1) && pDeviceId->privilege == WIMAX_API_PRIVILEGE_READ_WRITE)
	{			
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpen : waiting to see if firstWinsEvent was set...");
		if (OSAL_wait_event(firstWinsEvent,0) == WAIT_OBJECT_0)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpen : firstWinsEvent was set ! firstWinsEvent Pointer = %d", &firstWinsEvent);
			isAPIOpen = FALSE;
			return WIMAX_API_RET_PERMISSON_DENIED;
		}
		OSAL_set_event(firstWinsEvent);
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpen : setting firstWinsEvent ! firstWinsEvent Pointer = %d", &firstWinsEvent);
		
		OSAL_set_event(hijackedEvent);
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpen : setting hijackedEvent! = %d", hijackedEvent);
	}
	if (checkNamedEventHandle==NULL)
	{
		OSAL_create_thread(CheckNamedEvent,NULL, &checkNamedEventHandle);
	}
	OSAL_reset_event(hijackedEvent);
	g_events[0] = releasedEvent;
	g_events[1] = hijackedEvent;
	g_events[2] = closeThreadEvent;
	privilege = pDeviceId->privilege;

	//Init iWmxSDK wrapper
	wmxStatus = wmxSDK_Init();
	if (wmxStatus != WMX_ST_OK)
	{
		isAPIOpen = FALSE;
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	//register on system status indication
	wmxStatus = wmxSDK_RegisterCtrlStatusUpdatesCB(CtrlStatusCB);
	if (wmxStatus != WMX_ST_OK)
	{
		isAPIOpen = FALSE;
		wmxSDK_Finalize();
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}
	if (READY == wmxSDK_GetCtrlStatus())
	{								
		ResetAttachement(NULL);
	}
	
	//TODO: add support for SDK handle for identifying users.
	pDeviceId->apiVersion = (COMMON_API_HIGH_VERSION_ID << 16) + COMMON_API_LOW_VERSION_ID;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxAPIOpen - succeeded...");
	return WIMAX_API_RET_SUCCESS;
}

//Device detection, association and initialization
WIMAX_API_RET WIMAX_API WiMaxAPIOpenHijackable(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus;
	BOOL regData;
	UINT32 privData;	
	exitLoop = TRUE;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "---WiMaxAPIOpenHijackable(IN)---, requested permissions = %d", pDeviceId->privilege);

	//check that in pointer is valid
	OSAL_init_critical_section(&cs);
	if (pDeviceId == NULL)
	{
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	OSAL_enter_critical_section(&cs);
	if (isAPIOpen)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "isAPIOpen is on, can't open hijackable API");
		OSAL_exit_critical_section(&cs);
		return WIMAX_API_RET_FAILED;
	}
	isAPIOpen = TRUE;
	OSAL_exit_critical_section(&cs);

	if (0 != OSAL_create_event(&attachedEvent, TRUE, FALSE, NULL))
	{
		isAPIOpen = FALSE;
		return WIMAX_API_RET_FAILED;
	}

	if (0 != OSAL_create_event(&detachedEvent, TRUE, TRUE, NULL))
	{
		isAPIOpen = FALSE;
		return WIMAX_API_RET_FAILED;
	}

	if (0 != OSAL_create_mutex(&attachDetachMutex, FALSE, NULL))
	{
		isAPIOpen = FALSE;
		return WIMAX_API_RET_FAILED;
	}
	// in case another CU is open, ignore the error code ERROR_ALREADY_EXISTS
	if (0 != OSAL_create_event_with_security_attributes(&releasedEvent, FALSE, FALSE, "Global\\ReleasedPerimissionEvent"))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}
	if (0 != OSAL_create_event_with_security_attributes(&hijackedEvent, FALSE, FALSE, "Global\\HijackedPerimissionEvent"))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}

	if (0 != OSAL_create_event_with_security_attributes(&firstWinsEvent, TRUE, FALSE, "Global\\FirstWinsEvent"))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}
	if (0 != OSAL_create_event(&closeThreadEvent, FALSE, FALSE, NULL))
	{
		if(GetLastError() != ERROR_ALREADY_EXISTS)
		{
			isAPIOpen = FALSE;
			return WIMAX_API_RET_FAILED;
		}
	}

	//read registry to see if we want to block 2 apps with RW priviladges
	regData = L4Configurations_getCommonPriviledgeEnable(&privData);
	if ((regData == FALSE || privData == 1) && pDeviceId->privilege == WIMAX_API_PRIVILEGE_READ_WRITE)
	{			

		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpenHijackable : looking to see if firstWinsEvent was set already !");
		if (OSAL_wait_event(firstWinsEvent,0) == WAIT_OBJECT_0)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpen : firstWinsEvent was set ! firstWinsEvent Pointer = %d", &firstWinsEvent);
			isAPIOpen = FALSE;
			return WIMAX_API_RET_PERMISSON_DENIED;
		}
		OSAL_set_event(hijackedEvent);
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "WiMaxAPIOpenHijackable : setting hijackedEvent! = %d", hijackedEvent);
	}

	if (checkNamedEventHandle == NULL)
	{
		OSAL_create_thread(CheckNamedEvent,NULL, &checkNamedEventHandle);
	}
	OSAL_reset_event(hijackedEvent);
	OSAL_reset_event(releasedEvent);
	g_events[0] = releasedEvent;
	g_events[1] = hijackedEvent;
	g_events[2] = closeThreadEvent;
	//raise indication
	isAPIOpenHijackable = TRUE;
	privilege = pDeviceId->privilege;

	//Init iWmxSDK wrapper
	wmxStatus = wmxSDK_Init();
	if (wmxStatus != WMX_ST_OK)
	{
		isAPIOpen = FALSE;
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	//register on system status indication
	wmxStatus = wmxSDK_RegisterCtrlStatusUpdatesCB(CtrlStatusCB);
	if (wmxStatus != WMX_ST_OK)
	{
		isAPIOpen = FALSE;
		wmxSDK_Finalize();
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}
	if (READY == wmxSDK_GetCtrlStatus())
	{								
		ResetAttachement(NULL);
	}

	//TODO: add support for SDK handle for identifying users.
	pDeviceId->apiVersion = (COMMON_API_HIGH_VERSION_ID << 16) + COMMON_API_LOW_VERSION_ID;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxAPIOpen - succeeded");
	return WIMAX_API_RET_SUCCESS;
}

void CheckNamedEvent(void *dummy)
{
	//	UINT32 waitRes;
	int resNamed = 999;
	static int lastResult = 0;
	UNREFERENCED_PARAMETER(dummy);


	if (namedMutex == NULL)
	{
		OSAL_create_mutex(&namedMutex, FALSE, "Global\\WimaxAPI");
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckNamedEvent(IN)");
	
	
	if (privilege == WIMAX_API_PRIVILEGE_READ_ONLY)
	{
		OSAL_sleep(1000);
		while ((!((resNamed = OSAL_lock_mutex(namedMutex)) == WAIT_ABANDONED)) && exitLoop)
		{
			OSAL_unlock_mutex(namedMutex);
			OSAL_sleep(100);
			//TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "exitLoop = %d, namedMutex = %d, resNamed = %d, firstwinsEvent = %d", exitLoop, &namedMutex, resNamed,(OSAL_wait_event(firstWinsEvent,0) == WAIT_OBJECT_0));
		}
		//TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "exitLoop = %d, namedMutex = %d resNamed = %d(endWhile)", exitLoop, &namedMutex, resNamed);
	}
	else
	{
		while (resNamed != WAIT_OBJECT_0)
		{
			OSAL_sleep(10);
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "ReadWriteThreadTryingToLock namedMutex = %d, resNamed = %d, firstwinsEvent = %d", exitLoop, &namedMutex, resNamed,(OSAL_wait_event(firstWinsEvent,0) == WAIT_OBJECT_0));
			resNamed = OSAL_lock_mutex(namedMutex);
		}
		while (exitLoop)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG , "named mutex is locked !! firstwinsEvent = %d", (OSAL_wait_event(firstWinsEvent,0) == WAIT_OBJECT_0));
			OSAL_sleep(1000);
		}
		OSAL_unlock_mutex(namedMutex);
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "resNamed = %d, firstWinsEvent = %d, g_hijackedEventOn = %d", resNamed, firstWinsEvent, g_hijackedEventOn );
	if (!g_hijackedEventOn && resNamed==WAIT_ABANDONED && firstWinsEvent)
	{
		if (privilege == WIMAX_API_PRIVILEGE_READ_ONLY)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG , "CheckNamedEvent: SetEvent - releasedEvent, ResetEvent - firstWinsEvent, setting releasedEvent");
			OSAL_reset_event(firstWinsEvent);
			OSAL_set_event(releasedEvent);
		}
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckNamedEvent(OUT)" );
	g_hijackedEventOn = FALSE;
}

void CallPermissionsUpdateAsync(void* value)
{
	INT_PTR temp = (INT_PTR)value;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Indication received = %d!", (WMX_PERMISSION_UPDATE_EVENT)temp);
	if (permissionsUpdateCB != NULL)
	{
		permissionsUpdateCB(&DeviceID, (WMX_PERMISSION_UPDATE_EVENT)temp);
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "permissionsUpdateCB was called");
	}
	else 
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "permissionsUpdateCB was not called because its value is NULL");
	}
}

void CheckEvents(void *dummy)
{
	UINT32 waitRes;
	BOOL continueWaiting = TRUE;
	
	static OSAL_thread_t permmisionsThread = NULL;

	UNREFERENCED_PARAMETER(dummy);
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckEvents(IN)");
	
	while (continueWaiting == TRUE) 
	{
		waitRes = OSAL_multiple_wait_event(3, g_events, FALSE,INFINITE);
		switch(waitRes)
		{
		case WAIT_OBJECT_0 : 
			if (isAPIOpen && (privilege == WIMAX_API_PRIVILEGE_READ_ONLY))
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckEvents(IN) -  with Event releasedEvent that popped !");
				exitLoop = FALSE;

				//permissionsUpdateCB(&DeviceID, WIMAX_API_PRIVILEGE_READ_WRITE_AVAILABLE);
				OSAL_create_thread(CallPermissionsUpdateAsync, (void*)(INT_PTR)WIMAX_API_PRIVILEGE_READ_WRITE_AVAILABLE, &permmisionsThread);
			}

			break;

		case (WAIT_OBJECT_0 + 1): 
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckEvents(IN) -  with Event hijackedEvent that popped !");
			g_hijackedEventOn = TRUE;
			exitLoop = FALSE;
			DeviceID.privilege = WIMAX_API_PRIVILEGE_READ_ONLY;
			privilege = WIMAX_API_PRIVILEGE_READ_ONLY;
			isAPIOpenHijackable = TRUE;

			//permissionsUpdateCB(&DeviceID, WIMAX_API_PRIVILEGE_READ_WRITE_TAKEN);
			OSAL_create_thread(CallPermissionsUpdateAsync, (void*)(INT_PTR)WIMAX_API_PRIVILEGE_READ_WRITE_TAKEN, &permmisionsThread);
			
			if (checkNamedEventHandle == NULL)
			{
				OSAL_create_thread(CheckNamedEvent, NULL, &checkNamedEventHandle);
			}

			g_hijackedEventOn = TRUE;
			break;

		case (WAIT_OBJECT_0 + 2):
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckEvents(IN) -  with Event closeThreadEvent that popped !");
			continueWaiting = FALSE;
			break;

		default:
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckEvents(IN) -  with Event = %d", waitRes);
			break;
		}		
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CheckEvents(out) -  exiting");		
}

WIMAX_API_RET WIMAX_API GetWmxApiExVersion(UINT32 *pWmxApiExVersion)
{
	*pWmxApiExVersion = (COMMON_API_HIGH_EX_VERSION_ID << 16) + COMMON_API_LOW_EX_VERSION_ID;
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API WiMaxAPIClose(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxAPIClose(IN)");
	//check that in pointer is valid
	
	
	if (pDeviceId == NULL)
	{
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	
	if (!isAPIOpen)
	{
		return WIMAX_API_RET_FAILED;
	}

	//OSAL_create_thread(DetachFromSDK, NULL, &detachThreadHandle);

	//Signaling checkEventsHandle Thread to close
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG , "seting closeThreadEvent");
	OSAL_set_event(closeThreadEvent);
	
	
	//Signaling checkNamedEventHandle Thread to close
	exitLoop = FALSE;
	if (namedMutex != NULL)
	{
		OSAL_unlock_mutex(namedMutex);
	}
	
	OSAL_sleep(100);

	//OSAL_wait_event(checkNamedEventHandle, THREAD_JOIN_WAIT);
	//if (checkNamedEventHandle != NULL)
	//{
	//	OSAL_kill_thread(checkNamedEventHandle);
	//	checkNamedEventHandle = NULL;
	//}

	OSAL_wait_event(checkEventsHandle, THREAD_JOIN_WAIT);
	if (checkEventsHandle != NULL)
	{
		OSAL_kill_thread(checkEventsHandle);
		checkEventsHandle = NULL;
	}

	if (privilege == WIMAX_API_PRIVILEGE_READ_WRITE)
	{
		OSAL_reset_event(releasedEvent);
		OSAL_reset_event(hijackedEvent);
		if( !isAPIOpenHijackable )
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG , "WiMaxAPIClose: ResetEvent - firstWinsEvent");
			OSAL_reset_event(firstWinsEvent);
		}
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG , "seting releasedEvent");
		OSAL_set_event(releasedEvent);
	}

	
	if (releasedEvent != NULL)
	{
		//OSAL_delete_event(releasedEvent);
		releasedEvent = NULL;
	}
	if (hijackedEvent != NULL)
	{
		//OSAL_delete_event(hijackedEvent);
		hijackedEvent = NULL;
	}

	if (firstWinsEvent != NULL)
	{
		//OSAL_delete_event(firstWinsEvent);
		firstWinsEvent = NULL;
	}

	if (closeThreadEvent != NULL)
	{
		//OSAL_set_event(closeThreadEvent);
		//OSAL_reset_event(closeThreadEvent);
		OSAL_delete_event(closeThreadEvent);
		closeThreadEvent = NULL;
	}

	isAPIOpenHijackable = FALSE;
	
	//unregister on control status indication
	wmxStatus = wmxSDK_UnregisterCtrlStatusUpdatesCB(CtrlStatusCB);
	if (wmxStatus != WMX_ST_OK)
	{
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	isAPIOpen = FALSE;

	

	if (attachedEvent != NULL)
	{
		OSAL_delete_event(attachedEvent);
		attachedEvent = NULL;
	}

	if (detachedEvent != NULL)
	{
		OSAL_delete_event(detachedEvent);
		detachedEvent = NULL;
	}
	
	if (attachDetachMutex != NULL)
	{
		OSAL_delete_mutex(attachDetachMutex);
		attachDetachMutex = NULL;
	}
	
	
	wmxSDK_Finalize();

	// [FindMe][Amirs] clean the callbacks
	ctrlStatusCB = NULL;
	powerStateCB = NULL;
	connectCB = NULL;
	disconnectCB = NULL;
	deviceStatusCB = NULL;
	networkSearchWideScan = NULL;
	networkSearchWideScanEx = NULL;
	provisioningOperationCB = NULL;
	coexistenceModeCB = NULL;
	networkSearchEx = NULL;
	networkSearch = NULL;
	packageUpdate = NULL;
	currentPreferredProfile = NULL;
	connectionModeUpdateCB = NULL;
	roamingModeUpdateCB = NULL;
	fastReconnectModeUpdateCB = NULL;
	rfTakenCB = NULL;
	permissionsUpdateCB = NULL;

//	OSAL_delete_critical_section(&cs);	

	CleanProfileList();

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, ("WiMaxAPIClose(OUT) - succeded"));
	return WIMAX_API_RET_SUCCESS;
}
///// till here
WIMAX_API_RET WIMAX_API GetListDevice(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_HW_DEVICE_ID_P pHwDeviceIdList, UINT32 * pHwDeviceIdListSize)
{
	wmx_CtrlStatus_t ctrlStatus;
	WIMAX_API_RET wmxRet;
	char ifname[DEFULT_STR_SIZE];
	char append[sizeof(ifname) + sizeof(" if:") + 1];
	char deviceName[MAX_SIZE_OF_STRING_BUFFER] = {0};
	BOOL retStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetListDevice(IN)");
	//check parameters & permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No Permissions");
		return wmxRet;
	}
	//check that in pointers are valid
	if (pHwDeviceIdListSize == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pHwDeviceIdListSize == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	
	//check if there is device present
	ctrlStatus = wmxSDK_GetCtrlStatus();
	if (ctrlStatus == NOT_READY)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Device not ready");
		*pHwDeviceIdListSize = 0;		
	}
	else
	{
		if ( *pHwDeviceIdListSize == 0 )
		{
			*pHwDeviceIdListSize = 1;
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL");
			return WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;
		}

		if (pHwDeviceIdList == NULL)
		{
			*pHwDeviceIdListSize = 1;
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "WIMAX_API_RET_INVALID_PARAMETER");
			return WIMAX_API_RET_INVALID_PARAMETER;
		}		
		
		*pHwDeviceIdListSize = 1;
		pHwDeviceIdList->deviceIndex = INTEL_DEVICE_ID;
		pHwDeviceIdList->deviceType = WIMAX_API_DEV_TYPE_WIMAX;
		
		retStatus = OSAL_FindDeviceFileName(deviceName);
		if (retStatus)
		{
			OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, deviceName, (int)OSAL_strnlen(deviceName, sizeof(deviceName)) + 1, 
				pHwDeviceIdList->deviceName, sizeof(pHwDeviceIdList->deviceName)/sizeof(pHwDeviceIdList->deviceName[0]));
		}
		else
		{
			OSAL_CAPI_strcpy_s(pHwDeviceIdList->deviceName, MAX_SIZE_OF_STRING_BUFFER, TEXT("Intel WiMAX Besor Device (TEST)"));
		}
	}

	L4Configurations_getInterfaceName(ifname);
	snprintf(append, sizeof(append), " if:%s", ifname);
	strncat(pHwDeviceIdList->deviceName, append,
		sizeof(pHwDeviceIdList->deviceName) - strlen(pHwDeviceIdList->deviceName));
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetListDevice(OUT). Device name = %s", pHwDeviceIdList->deviceName);
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API WiMaxDeviceOpen(WIMAX_API_DEVICE_ID_P pDeviceId)
{	
	WIMAX_API_RET wmxRet;
	WIMAX_CHAR errorStr[100];
	UINT32 length = 100;
	wmx_Status_t wmxStatus;
	wmx_SystemState_t systemState;
	wmx_ConnectProgressInfo_t connectionProgressInfo;
	wmx_RfSwitchesStatus_t rfSwitchesStatus;


	wmxRet = WIMAX_API_RET_SUCCESS;
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxDeviceOpen(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "No permissions");
		goto Finalize;
	}

	//check device index	
	if (pDeviceId->deviceIndex != INTEL_DEVICE_ID)
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "WIMAX_API_RET_INVALID_DEVICE");
		wmxRet = WIMAX_API_RET_INVALID_DEVICE;
		goto Finalize;
	}

	/*wmxRet = AttachToSDK();
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}*/

	if (!isReady)
	{
		wmxRet = WIMAX_API_RET_DEVICE_MISSING;
		goto Finalize;
	}

	OSAL_enter_critical_section(&cs);	
	DeviceID.deviceIndex = pDeviceId->deviceIndex;
	DeviceID.privilege = pDeviceId->privilege;	
	DeviceID.devicePresenceStatus = pDeviceId->devicePresenceStatus = TRUE;
	OSAL_exit_critical_section(&cs);

	wmxStatus = wmx_GetSystemState(&systemState, &connectionProgressInfo, &rfSwitchesStatus);
	if (systemState>RfOff) 
	{
		rfState = WIMAX_API_RF_ON;
	}

	OSAL_atomic_compareExchange(&isDeviceOpen, TRUE, FALSE);

Finalize:
	GetErrorString(pDeviceId, wmxRet, errorStr, &length);
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxDeviceOpen(OUT). wmxRet = %s", errorStr);
	return wmxRet;
}

WIMAX_API_RET WIMAX_API WiMaxDeviceClose(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_CHAR errorStr[100];
	UINT32 length = 100;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;

	do
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxDeviceClose(IN)");
		//check that in pointers are valid
		wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
		if (wmxRet != WIMAX_API_RET_SUCCESS)
		{		
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
			//goto Finalize;
			break;
		}

		//check device index	
		if (pDeviceId->deviceIndex != INTEL_DEVICE_ID)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Wrong device id");
			wmxRet = WIMAX_API_RET_INVALID_DEVICE;
			//goto Finalize;
			break;
		}	

		//wmxRet = DetachFromSDK();
		OSAL_atomic_compareExchange(&isDeviceOpen, TRUE, FALSE);

		memset(&DeviceID, 0, sizeof(DeviceID));	
		pDeviceId->deviceIndex = 0;
	}
	while(wmxRet != WIMAX_API_RET_SUCCESS);

//Finalize:
	GetErrorString(pDeviceId, wmxRet, errorStr, &length);
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "WiMaxDeviceClose(OUT). wmxRet = %s", errorStr);
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SubscribePermissionsUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndPermissionsUpdate pCallbackFnc )
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePermissionsUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No Permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (permissionsUpdateCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "SubscribePermissionsUpdate(OUT). ERROR - allready registered");
		return WIMAX_API_RET_FAILED;
	}
	OSAL_enter_critical_section(&cs);
	permissionsUpdateCB = pCallbackFnc;
	OSAL_exit_critical_section(&cs);

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "checkEventsHandle = %d", checkEventsHandle);
	if(checkEventsHandle == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "creating thread CheckEvents");
		OSAL_create_thread(CheckEvents, NULL, &checkEventsHandle);
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePermissionsUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribePermissionsUpdate(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePermissionsUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		return wmxRet;
	}
	
	//exitLoop = FALSE;
	permissionsUpdateCB = NULL;
	/*if (checkEventsHandle != NULL)
	{
		OSAL_kill_thread(checkEventsHandle);
		checkEventsHandle = NULL;
	}*/
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePermissionsUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;
}


WIMAX_API_RET WIMAX_API SubscribeDeviceInsertRemove(WIMAX_API_DEVICE_ID_P pDeviceId, IndDeviceInsertRemove pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeDeviceInsertRemove(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No Permissions, status=%d", wmxRet);
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (ctrlStatusCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "SubscribeDeviceInsertRemove(OUT). ERROR - allready registered");
		return WIMAX_API_RET_FAILED;
	}
	
	ctrlStatusCB = pCallbackFnc;
	//if (checkEventsHandle!=NULL)
	//{
	//	OSAL_delete_event(checkEventsHandle);
	//	checkEventsHandle=NULL;
	//}
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeDeviceInsertRemove(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeDeviceInsertRemove(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeDeviceInsertRemove(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions, status=%d", wmxRet);
		return wmxRet;
	}

	ctrlStatusCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeDeviceInsertRemove(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
//Device maintenance
WIMAX_API_RET WIMAX_API CmdControlPowerManagement(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_RF_STATE powerState)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdControlPowerManagement(IN)");
	//Check Parameters And Permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//set the RF state, according to powerState
	switch(powerState)
	{
	case WIMAX_API_RF_ON:
		wmxStatus = wmx_RfOn(); 
		if (wmxStatus != WMX_ST_OK)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdControlPowerManagement(OUT). Error status=%s", wmxGetStatusStr(wmxStatus));
			return WmxStatusToWimaxAPIRet(wmxStatus);
		}
		break;

	case WIMAX_API_RF_OFF:
		wmxStatus = wmx_RfOff(); 
		if (wmxStatus != WMX_ST_OK)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdControlPowerManagement(OUT). Error status=%s", wmxGetStatusStr(wmxStatus));
			return WmxStatusToWimaxAPIRet(wmxStatus);
		}
		break;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdControlPowerManagement(OUT)");

	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API SubscribeControlPowerManagement(WIMAX_API_DEVICE_ID_P pDeviceId, IndControlPowerManagement pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeControlPowerManagement(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No Permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (powerStateCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Allready registered");
		return WIMAX_API_RET_FAILED;
	}

	powerStateCB = pCallbackFnc;
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeControlPowerManagement(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeControlPowerManagement(WIMAX_API_DEVICE_ID_P pDeviceId)
{
//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeControlPowerManagement(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		return wmxRet;
	}

	powerStateCB = NULL;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeControlPowerManagement(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
//Network search, Connect\Disconnect
WIMAX_API_RET WIMAX_API CmdNetworkSearchWideScan(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
//	wmx_UserScanStatus_t scanStatus;
//	UINT32 numOfNSPs = WMX_NSPS_MAX_NUM;
//	wmx_NSP_t wmxNsps[WMX_NSPS_MAX_NUM];

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearchWideScan(IN)");
	//Check Parameters And Permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//perform scan
	wmxStatus = wmx_CmdUserStartScan(SCAN_TYPE_WIDE);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearchWideScan(OUT). ERROR - Returned value-%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}
	//wmxStatus = wmx_CmdUserStopScan();

	wideScanStarted = TRUE;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearchWideScan(OUT). Returned-%s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}


WIMAX_API_RET WIMAX_API GetNetworkListEx(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_EX_P pNSPInfo, UINT32 * pArrayLength)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	UINT32 numOfNSPs = WMX_NSPS_MAX_NUM;
	wmx_NSP_t wmxNsps[WMX_NSPS_MAX_NUM];
	UINT32 i;
	BOOL preferredExists=FALSE;
	int nspNameConv;
	wmx_NSP_t currentPreferredNsp;
	wmx_Status_t status;
	UINT32 numOfCurrentPreferredNsps;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNetworkListEx(IN)");

	if (pArrayLength == NULL)
	{
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting last known NSPs
	wmxStatus = wmx_GetLastKnownNSPs(&numOfNSPs, (wmx_pNSP_t)&wmxNsps);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetNetworkListEx(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}	

	if ((pNSPInfo == NULL) && (*pArrayLength>0))
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetNetworkListEx(OUT). ERROR - WIMAX_API_RET_INVALID_PARAMETER");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	
	preferredExists = FALSE;
	//getting the current preferred NSP	
	status = wmx_GetCurrentPreferredNSP(&currentPreferredNsp, &numOfCurrentPreferredNsps);
	if( status != WMX_ST_OK )
	{
		wmxRet =   WmxStatusToWimaxAPIRet(status);
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetNetworkListEx: wmx_GetCurrentPreferredNSP = [%d]", wmxRet);
	}	
	if (numOfCurrentPreferredNsps > 0)
	{
		preferredExists = TRUE;
	}
	for (i=0; i<numOfNSPs; i++)
	{
		if (i >= *pArrayLength)
		{
			numberOfNSPs = *pArrayLength = numOfNSPs;
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetNetworkListEx(OUT). ERROR - WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL");
			return WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;
		}
		// IF A PREFERRED PROFILE EXISTS RETURN IN THE LIST ONLY IT.OTHERWISE ADD ALL FOUND.
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "-----------wideScanStartedAndCompleted = %d----------- Before the if == hacham yoter", wideScanStartedAndCompleted);
		if (preferredExists && !wideScanStartedAndCompleted)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "GetNetworkListEx : preferredExists=TRUE, adding only preferred nspid");
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "GetNetworkListEx : checking if (wmxNsps[%d].nspIDs[0])[%d]==[%d](currentPreferredNsp.nspIDs[0])",i,wmxNsps[i].nspIDs[0],currentPreferredNsp.nspIDs[0]);
			if (currentPreferredNsp.nspIDs[0]==wmxNsps[i].nspIDs[0])
			{
				nspsEx[i].CINR = pNSPInfo[i].CINR = (UINT8)wmxNsps[i].bestCINR; //TODO: check what are the right eqvivalents
				nspsEx[i].RSSI = pNSPInfo[i].RSSI = (UINT8)wmxNsps[i].bestRssi; 
				nspsEx[i].NSPid = pNSPInfo[i].NSPid = wmxNsps[i].nspIDs[0];
				nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, wmxNsps[i].nspName, (int)OSAL_strnlen(wmxNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE)+1, pNSPInfo[i].NSPName, sizeof(pNSPInfo[i].NSPName)/sizeof(pNSPInfo[i].NSPName[0]));
				if( nspNameConv == 0 )
				{
					TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to UTF-8. error=%d",GetLastError());
					return WIMAX_API_RET_FAILED;
				}
				nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, wmxNsps[i].nspName, (int)OSAL_strnlen(wmxNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE)+1, nspsEx[i].NSPName, sizeof(nspsEx[i].NSPName)/sizeof(nspsEx[i].NSPName[0]));
				if( nspNameConv == 0 )
				{
					TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspExName to UTF-8. error=%d",GetLastError());
					return WIMAX_API_RET_FAILED;
				}

				nspsEx[i].networkType = pNSPInfo[i].networkType = WIMAX_API_HOME;
				nspsEx[i].structureSize = pNSPInfo[i].structureSize = sizeof(pNSPInfo[i]);
				nspsEx[i].linkQuality = pNSPInfo[i].linkQuality = wmxNsps[i].linkQuality; 
				TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "GetNetworkListEx : added preferred nspid = [%d], list size is 1!",wmxNsps[i].nspIDs[0]);
				numOfNSPs = 1;
				break;
			}
		}
		else
		{
			//TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "wideScanStartedAndCompleted = FALSE, GetNetworkListEx");
			nspsEx[i].CINR = pNSPInfo[i].CINR = (UINT8)wmxNsps[i].bestCINR; //TODO: check what are the right eqvivalents
			nspsEx[i].RSSI = pNSPInfo[i].RSSI = (UINT8)wmxNsps[i].bestRssi; 
			nspsEx[i].NSPid = pNSPInfo[i].NSPid = wmxNsps[i].nspIDs[0];
			nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, wmxNsps[i].nspName, (int)OSAL_strnlen(wmxNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE)+1, pNSPInfo[i].NSPName, sizeof(pNSPInfo[i].NSPName)/sizeof(pNSPInfo[i].NSPName[0]));
			if( nspNameConv == 0 )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to UTF-8. error=%d",GetLastError());
				return WIMAX_API_RET_FAILED;
			}
			nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, wmxNsps[i].nspName, (int)OSAL_strnlen(wmxNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE)+1, nspsEx[i].NSPName, sizeof(nspsEx[i].NSPName)/sizeof(nspsEx[i].NSPName[0]));
			if( nspNameConv == 0 )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspExName to UTF-8. error=%d",GetLastError());
				return WIMAX_API_RET_FAILED;
			}
			
			nspsEx[i].networkType = pNSPInfo[i].networkType = WIMAX_API_HOME;
			nspsEx[i].structureSize = pNSPInfo[i].structureSize = sizeof(pNSPInfo[i]);
			nspsEx[i].linkQuality = pNSPInfo[i].linkQuality = wmxNsps[i].linkQuality; 
			if (numOfNSPs == (i-1))
			{
				wideScanStartedAndCompleted = FALSE;
			}
		}	
	}
	
	numberOfNSPs = *pArrayLength = numOfNSPs;
	

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNetworkListEx(OUT). found %d networks",numOfNSPs);
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API GetNetworkList(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_P pNSPInfo, UINT32 * pArrayLength)
{
	WIMAX_API_RET wmxRet;
	WIMAX_CHAR errorStr[100];
	UINT32 length = 100;
	WIMAX_API_NSP_INFO_EX_P pNSPInfoEx;

	pNSPInfoEx = (WIMAX_API_NSP_INFO_EX_P)malloc(sizeof(WIMAX_API_NSP_INFO_EX) * (*pArrayLength));
	if(NULL == pNSPInfoEx)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetNetworkList(OUT). ERROR - unable to malloc");
		return WIMAX_API_RET_FAILED;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNetworkList(IN)");

	wmxRet = GetNetworkListEx(pDeviceId, pNSPInfoEx, pArrayLength);
	if(WIMAX_API_RET_SUCCESS == wmxRet)
	{
		nspInfoExToNspInfo(pNSPInfoEx, pNSPInfo, *pArrayLength);
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNetworkList(OUT). found %d networks",*pArrayLength);
	}
	GetErrorString(pDeviceId, wmxRet, errorStr, &length);
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNetworkList(OUT). wmxRet = %s", errorStr);
	free(pNSPInfoEx);
	return wmxRet;
}



void CleanProfileList()
{
	pProfileList_t temp;

	while (profileListHead != NULL)
	{
		if (profileListHead->profile != NULL)
		{
			free(profileListHead->profile);
		}
		temp = profileListHead;
		profileListHead = profileListHead->next;
		free(temp);
	}
}

WIMAX_API_RET WIMAX_API GetSelectProfileList(WIMAX_API_DEVICE_ID_P pDeviceId,  WIMAX_API_PROFILE_INFO_P  pProfileList, UINT32 *  pListSize)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	UINT32 numOfNSPs = WMX_NSPS_MAX_NUM;
	wmx_NSP_t wmxNsps[WMX_NSPS_MAX_NUM];
	UINT32 numOfUnprovisionedNSPs = WMX_NSPS_MAX_NUM;
	wmx_NSP_t wmxUnprovisionedNsps[WMX_NSPS_MAX_NUM];
	UINT32 listSize = 0;
	UINT32 numOfAddedUnprovisionedNSPs = 0;
	UINT32 i, j, numOfIDs;
	UINT32 strSize;
	pProfileList_t profList;
	int nspNameConv, subscribersConv;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetSelectProfileList(IN)");
	if (pListSize == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetSelectProfileList(OUT). ERROR - WIMAX_API_RET_INVALID_PARAMETER");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		return wmxRet;
	}

	//get provisioned NSPs
	wmxStatus = wmx_GetProvisionedNSPs( &numOfNSPs, wmxNsps );
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetSelectProfileList(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	wmxStatus = wmx_GetUnprovisionedNSPs( &numOfUnprovisionedNSPs, wmxUnprovisionedNsps );
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetSelectProfileList(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	// Add the unprovisioned NSPs only if there is a place in the array
	if (numOfNSPs < WMX_NSPS_MAX_NUM)
	{
		// Add the unprovisioned NSPs after checking for duplications
		for (i=0; i < numOfUnprovisionedNSPs; i++)
		{
			for (j=0; j < numOfNSPs; j++)
			{
				for (numOfIDs=0; numOfIDs < wmxNsps[j].numOfNspIDs; numOfIDs++)
				{			
					// There is only one ID in the unprovisioned NSP
					if (wmxUnprovisionedNsps[i].nspIDs[0] == wmxNsps[i].nspIDs[numOfIDs])
					{
						break;
					}
				}

				if (numOfIDs < wmxNsps[j].numOfNspIDs)
				{
					// The NSP exists, don't add it again
					break;
				}
			}

			// The NSP is a new one. Add it to the list.
			if (j == numOfNSPs)
			{
				wmxNsps[numOfNSPs + numOfAddedUnprovisionedNSPs] = wmxUnprovisionedNsps[i];
				numOfAddedUnprovisionedNSPs++;

				// Make sure that we don't exceed the array size
				if (numOfNSPs + numOfAddedUnprovisionedNSPs == WMX_NSPS_MAX_NUM)
				{
					break;
				}
			}
		}

		numOfNSPs += numOfAddedUnprovisionedNSPs;
	}

	if (numOfNSPs == 0)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetSelectProfileList(OUT). numOfNSPs == 0");
		*pListSize = 0;
		return WIMAX_API_RET_SUCCESS;
	}
	
	//clean list
	CleanProfileList();

	//go over NSPs list, and find which are activated
	//TODO: should change the activate field in NDnS from NSP to subscriber	
	for (i=0; i<numOfNSPs; i++)
	{
		/*if (wmxNsps[i].activated)
		{*/
			listSize++;
			if (*pListSize<listSize)
			{
				//*pListSize = listSize;
				//TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetSelectProfileList(OUT). ERROR - WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL");
				//return WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;
				continue;
			}

			if (pProfileList == NULL)
			{
				*pListSize = listSize;
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetSelectProfileList(OUT). ERROR - WIMAX_API_RET_INVALID_PARAMETER");
				return WIMAX_API_RET_INVALID_PARAMETER;
			}

			//TODO: for V3 only - taking first nspID for profileID
			pProfileList[listSize-1].profileID = wmxNsps[i].nspIDs[0];

			//TODO: for v3 only - taking first subscriber name as primary subscriber
			strSize = WMX_NSP_NAME_MAX_SIZE;//(int)strlen(wmxNsps[i].nspName)+1;
			nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, wmxNsps[i].nspName, strSize, pProfileList[listSize-1].profileName, sizeof(pProfileList[listSize-1].profileName)/sizeof(pProfileList[listSize-1].profileName[0]));			
			if( nspNameConv == 0 )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to WideChar");
				return WIMAX_API_RET_FAILED;
			}
			pProfileList[listSize-1].profileName[OSAL_CAPI_wcslen(pProfileList[listSize-1].profileName)] = ':';
			strSize = WMX_NSP_NAME_MAX_SIZE - (int)OSAL_strnlen(wmxNsps[i].nspName, WMX_NSP_NAME_MAX_SIZE - 1);//(int)strlen(wmxNsps[i].subscribers[0].name)+1;
			subscribersConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, wmxNsps[i].subscribers[0].name, strSize, pProfileList[listSize-1].profileName + (int)strlen(wmxNsps[i].nspName)+1, sizeof(pProfileList[listSize-1].profileName)/sizeof(pProfileList[listSize-1].profileName[0]));			
			if( subscribersConv == 0 )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert subscribers name to WideChar");
				return WIMAX_API_RET_FAILED;
			}

			if (profileListHead == NULL)
			{
				profileListHead = (ProfileList_t*)malloc(sizeof(ProfileList_t));
				if (profileListHead == NULL)
				{
					return WIMAX_API_RET_FAILED;
				}
				profileListHead->next = NULL;
			}
			else
			{
				profList = (ProfileList_t*)malloc(sizeof(ProfileList_t));
				if (profList == NULL)
				{
					return WIMAX_API_RET_FAILED;
				}
				profList->next = profileListHead;
				profileListHead = profList;
			}

			//profileListHead->profile = &pProfileList[listSize-1];
			profileListHead->profile = malloc(sizeof(WIMAX_API_PROFILE_INFO));
			
			if (profileListHead->profile != NULL)
			{
				memcpy(profileListHead->profile, &pProfileList[listSize-1], sizeof(WIMAX_API_PROFILE_INFO));
			}
		/*}*/
	}

	if (*pListSize<listSize)
	{
		*pListSize = listSize;
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetSelectProfileList(OUT). ERROR - WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL");
		return WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;
	}

	*pListSize = listSize;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetSelectProfileList(OUT)");
	return WIMAX_API_RET_SUCCESS;
}


WIMAX_API_RET WIMAX_API CmdConnectToNetwork(
	WIMAX_API_DEVICE_ID_P pDeviceId,
	WIMAX_API_WSTRING nspName,
	WIMAX_API_PROFILE_ID profileId,
	WIMAX_API_WSTRING password)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_NSPid_t nspID = 0;
	wmx_UserConnectStatus_t connectStatus;
	wmx_ConnectionType_t connectionType = CONN_TYPE_HOME; // TODO: Darzi - replace with a real value
	wmx_pUserCredentials_t userCredentials = NULL; // TODO: Darzi - replace with a real value
	UINT32 i;
	pProfileList_t selectedProfile = profileListHead;
	char username[WMX_CRED_USERNAME_MAX_SIZE*2] = {0};
	char *token;
	WIMAX_API_PROFILE_INFO profileList[5];
	UINT32 listSize=5;
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE,
		"CmdConnectToNetwork(IN). nspName=%s , profileId=%d , password=%s",
		nspName, profileId, password);
	//Check Parameters And Permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//if profileID!=0 build user credentials and connect
	if (profileId != 0)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "using profile ID=%d", profileId);
		//go over the list and find the right profile id
		if (selectedProfile == NULL)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "calling GetSelectProfileList to build list");
			GetSelectProfileList(pDeviceId,  profileList, &listSize);
			selectedProfile = profileListHead;
		}

		while(selectedProfile != NULL)
		{
			if (selectedProfile->profile->profileID == profileId)
			{
				break;
			}
			selectedProfile = selectedProfile->next;
		}; 

		//if no right profile is found - return error
		if (selectedProfile == NULL)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdConnectToNetwork(OUT). No right profile found");
			return WIMAX_API_RET_FAILED; 
		}

		//build user credentials from the profile
		userCredentials = (wmx_pUserCredentials_t)malloc(sizeof(wmx_UserCredentials_t));
		if (password != NULL)
		{
			OSAL_CAPI_WideCharToMultiByte(CP_ACP, 0, password, -1, userCredentials->password, WMX_CRED_USERNAME_MAX_SIZE, NULL, NULL);
		}
		else
		{
			OSAL_CAPI_WideCharToMultiByte(CP_ACP, 0, TEXT(""), -1, userCredentials->password, WMX_CRED_USERNAME_MAX_SIZE, NULL, NULL);
		}
		OSAL_CAPI_WideCharToMultiByte(CP_ACP, 0, selectedProfile->profile->profileName, -1, username, WMX_CRED_USERNAME_MAX_SIZE, NULL, NULL);
		token = OSAL_strtok_s(username,":",&token);
		OSAL_strncpy_s(userCredentials->username, WMX_CRED_USERNAME_MAX_SIZE, username+OSAL_strnlen(token, WMX_CRED_USERNAME_MAX_SIZE)+1, WMX_CRED_USERNAME_MAX_SIZE-OSAL_strnlen(token, WMX_CRED_USERNAME_MAX_SIZE - 1));

		//perform connect
		//  TODO: Darzi - replace the 0 in homeNspToRoamTo with a real value when applicable
		wmxStatus = wmx_CmdUserConnect(selectedProfile->profile->profileID, connectionType, 0, userCredentials, &connectStatus);
		free(userCredentials);
	}
	else
	{
		//if profileID=0 connect through name 
		//find the nspId from the nspName
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "using NSP name");
		for (i=0; i<numberOfNSPs; i++)
		{
			if (OSAL_wcscmp(nspName, nspsEx[i].NSPName)==0)
			{
				nspID = nspsEx[i].NSPid;
				break;
			}
		}

		if (i==numberOfNSPs)
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdConnectToNetwork(OUT). no NSP with that name");
			return WIMAX_API_RET_FAILED;
		}
		//perform connect
		//  TODO: Darzi - replace the 0 in homeNspToRoamTo with a real value when applicable
		wmxStatus = wmx_CmdUserConnect(nspID, connectionType, 0, userCredentials, &connectStatus);
	}
	if ( WMX_ST_OK == wmxStatus)
	{
		isTryingToConnect = TRUE;
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdConnectToNetwork(OUT). returned - %s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}
WIMAX_API_RET WIMAX_API SubscribeConnectToNetwork(WIMAX_API_DEVICE_ID_P pDeviceId, IndConnectToNetwork pCallbackFnc)
{
//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeConnectToNetwork(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (connectCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "callback allready registered");
		return WIMAX_API_RET_FAILED;
	}

	connectCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeConnectToNetwork(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeConnectToNetwork(WIMAX_API_DEVICE_ID_P pDeviceId)
{
//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeConnectToNetwork(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	connectCB = NULL;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeConnectToNetwork(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API CmdDisconnectFromNetwork (WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdDisconnectFromNetwork(IN)");
	//Check Parameters And Permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No Permissions");
		return wmxRet;
	}

	//perform connect
	isTryingToDisconnect = TRUE;
	wmxStatus = wmx_CmdUserDisconnect();

	if ( WMX_ST_OK != wmxStatus)
	{
		isTryingToDisconnect = FALSE;
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdDisconnectFromNetwork(OUT), returned - %s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}

WIMAX_API_RET WIMAX_API SubscribeDisconnectToNetwork (WIMAX_API_DEVICE_ID_P pDeviceId, IndDisconnectToNetwork pCallbackFnc)
{
//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeDisconnectToNetwork(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (disconnectCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_FAILED;
	}

	disconnectCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeDisconnectToNetwork(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeDisconnectToNetwork(WIMAX_API_DEVICE_ID_P pDeviceId)
{
//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeDisconnectToNetwork(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	disconnectCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeDisconnectToNetwork(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API SubscribeNetworkSearchWideScan (WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearchWideScan pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearchWideScan(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (networkSearchWideScan != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_FAILED;
	}	

	networkSearchWideScan = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearchWideScan(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API SubscribeNetworkSearchWideScanEx (WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearchWideScanEx pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearchWideScanEx(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (networkSearchWideScanEx != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_FAILED;
	}	

	networkSearchWideScanEx = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearchWideScanEx(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearchWideScan (WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScan(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	networkSearchWideScan = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScan(IN)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearchWideScanEx (WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScanEx(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	networkSearchWideScanEx = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScanEx(IN)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearch(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScan(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	networkSearch = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScan(IN)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearchEx(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScanEx(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	networkSearchEx = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeNetworkSearchWideScanEx(IN)");
	return WIMAX_API_RET_SUCCESS;
}

//Device Info

WIMAX_API_RET WIMAX_API GetLinkStatus(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_LINK_STATUS_INFO_P pLinkStatus)
{
	WIMAX_API_RET wmxRet;
	WIMAX_API_LINK_STATUS_INFO_EX LinkStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetLinkStatus(IN)");

	wmxRet = GetLinkStatusEx(pDeviceId, &LinkStatus);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetLinkStatusEx failed");
		return wmxRet;
	}

	pLinkStatus->centerFrequency = (UINT32)LinkStatus.centerFrequency;
	pLinkStatus->CINR = (UINT8)LinkStatus.CINR;
	pLinkStatus->RSSI = (UINT8)LinkStatus.RSSI;
	pLinkStatus->txPWR = (UINT8)LinkStatus.txPWR;
	OSAL_memcpy_s(pLinkStatus->bsId, 6, &LinkStatus.bsId, 6);
	pLinkStatus->structureSize = sizeof(*pLinkStatus);

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetLinkStatus(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API GetLinkStatusEx(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_LINK_STATUS_INFO_EX_P pLinkStatus)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_UserLinkStatus_t linkStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetLinkStatusEx(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting last known NSPs
	wmxStatus = wmx_GetUserLinkStatus(&linkStatus);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetLinkStatusEx(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	pLinkStatus->centerFrequency = (UINT32)linkStatus.frequency;
	pLinkStatus->CINR = (UINT8)linkStatus.cinr;
	pLinkStatus->RSSI = (UINT8)linkStatus.rssi;
	pLinkStatus->txPWR = (UINT8)linkStatus.power;
	pLinkStatus->linkQuality = (WMX_LINK_QUALITY_EX)linkStatus.linkQuality;
	OSAL_memcpy_s(pLinkStatus->bsId, 6, &linkStatus.bsId, 6);
	pLinkStatus->structureSize = sizeof(*pLinkStatus);

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetLinkStatusEx(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
//Device Status
WIMAX_API_RET WIMAX_API GetDeviceStatus(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_STATUS_P pDeviceStatus, 
										WIMAX_API_CONNECTION_PROGRESS_INFO_P pConnectionProgressInfo)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_DeviceStatus_t deviceStatus;
	wmx_ConnectionProgressInfo_t connectionProgress;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetDeviceStatus(IN)");
	
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_GetDeviceStatus(&deviceStatus, &connectionProgress);

	if(wmxStatus == WMX_ST_OK)
	{
		*pDeviceStatus = WmxToCommonGetDeviceStatus(deviceStatus);
		*pConnectionProgressInfo = GetConnectionProgress(connectionProgress);
	}

	wmxRet = WmxStatusToWimaxAPIRet( wmxStatus );
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetDeviceStatus(OUT). Device status=%d",*pDeviceStatus);
	return wmxRet;
}


// Get Platform Noise Mitigation
WIMAX_API_RET WIMAX_API GetPNMRequestedChannel(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PPNM_COMMDEV_INFO_P pPNMInfo)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	UINT32			PNMInfoSize;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetPNMRequestedChannel(IN)");


	PNMInfoSize = sizeof(WIMAX_API_PNM_COMMDEV_INFO);	

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	if (pPNMInfo == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Input Buffer is NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	wmxStatus = wmx_GetPNMRequestedChannel((CHAR*)pPNMInfo, &PNMInfoSize);
	
	wmxRet = WmxStatusToWimaxAPIRet( wmxStatus );
	
	return wmxRet;
}


// Platform Noise Mitigation
WIMAX_API_RET WIMAX_API GetIsPNMCommDevUsingChannel(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PPNM_COMMDEV_INFO_P pPNMInfo, BOOL* result)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;	
	UINT32			PNMInfoSize;

	

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetIsPNMCommDevUsingChannel(IN)");

	PNMInfoSize = sizeof(WIMAX_API_PNM_COMMDEV_INFO);

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_GetIsPNMCommDevUsingChannel((CHAR*)pPNMInfo, & PNMInfoSize, result);
	wmxRet = WmxStatusToWimaxAPIRet( wmxStatus );
	
	return wmxRet;
}
 


WIMAX_API_RET WIMAX_API GetDeviceInformation(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_INFO_P pDeviceInfo)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	//wmx_MacAddress_t macAdrress = (wmx_MacAddress_t)malloc(MAC_ADDRESS_LENGTH);
	UINT8 macAdrress[MAC_ADDRESS_LENGTH];
	wmx_ModelType_t modelType;
	wmx_Manufacturer_t manufacturer;
	wmx_SerialNumber_t serialNumber;
	wmx_DeviceVersion_t deviceVersion;
	wmx_NvmVersion_t nvmVersion;
	wmx_DevicePID_t pid;
	wmx_Nonce_t nonce;
	wmx_ODMInfo_t odmInfo;
	char tmp[WMX_MODEL_TYPE_NAME_MAX_LENGTH];
	wmx_InstallationInfo_t installInfo;
	UINT32 strSize=0;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetDeviceInformation(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_GetDeviceDetailsEx(macAdrress, &modelType, &manufacturer, &serialNumber, (wmx_pNvmVersion_t)&nvmVersion, (wmx_pODMInfo_t)&odmInfo,(wmx_pNonce_t)&nonce, &pid);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetDeviceInformation(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}
		
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After wmx_GetDeviceDetailsEx");

	wmxStatus = wmx_GetDeviceVersion(&deviceVersion);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetDeviceInformation(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After wmx_GetDeviceVersion");

	wmxStatus = wmx_GetInstallationInfo(&installInfo);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetDeviceInformation(OUT). ERROR GetInstallInfo- ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After wmx_GetInstallationInfo");
	//update hwVersion
	// version:
	OSAL_itoa_s(modelType.modelTypeID, tmp, WMX_MODEL_TYPE_NAME_MAX_LENGTH, 10);
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, tmp, WMX_MODEL_TYPE_NAME_MAX_LENGTH, 
																pDeviceInfo->hwVersion.version, MAX_SIZE_OF_STRING_BUFFER);

	// name:
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, modelType.modelTypeName, WMX_MODEL_TYPE_NAME_MAX_LENGTH, pDeviceInfo->hwVersion.name, sizeof(pDeviceInfo->hwVersion.name)/sizeof(pDeviceInfo->hwVersion.name[0]));
	//memcpy_s(pDeviceInfo->hwVersion.name, WMX_MODEL_TYPE_NAME_MAX_LENGTH, modelType.modelTypeName, WMX_MODEL_TYPE_NAME_MAX_LENGTH);

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After copying hw version");

	//update swVersion
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, installInfo.swVersion, MAX_INSTALLAION_VERSION_SIZE, 
																pDeviceInfo->swVersion.version, MAX_SIZE_OF_STRING_BUFFER);
	//OSAL_memcpy_s(pDeviceInfo->swVersion.version, WMX_MODEL_TYPE_NAME_MAX_LENGTH, deviceVersion.Software, WMX_DEVICE_VERSION_MAX_LENGTH);
	//OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, deviceVersion.Software, sizeof(deviceVersion.Software), pDeviceInfo->swVersion.version, sizeof(pDeviceInfo->swVersion.version)/sizeof(pDeviceInfo->swVersion.version[0]));
	// name: should be nothing
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, "", 1, pDeviceInfo->swVersion.name, sizeof(pDeviceInfo->swVersion.name)/sizeof(pDeviceInfo->swVersion.name[0]));

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After copying sw version");

	//update rfVersion
	// version: should be 0 (not used)
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, "0", WMX_MODEL_TYPE_NAME_MAX_LENGTH, pDeviceInfo->rfVersion.version, sizeof(pDeviceInfo->rfVersion.version)/sizeof(pDeviceInfo->rfVersion.version[0]));
	// name: should be nothing
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, "", 1, pDeviceInfo->rfVersion.name, sizeof(pDeviceInfo->rfVersion.name)/sizeof(pDeviceInfo->rfVersion.name[0]));

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After copying rf version");

	//update asicVersion
	// version: used for VID:PID
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, "0x", WMX_MODEL_TYPE_NAME_MAX_LENGTH, pDeviceInfo->asicVersion.version, sizeof(pDeviceInfo->asicVersion.version)/sizeof(pDeviceInfo->asicVersion.version[0]));
	OSAL_itoa_s(manufacturer.manufacturerID, tmp, WMX_MODEL_TYPE_NAME_MAX_LENGTH, 16);
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, tmp, WMX_MODEL_TYPE_NAME_MAX_LENGTH, &pDeviceInfo->asicVersion.version[2], sizeof(pDeviceInfo->asicVersion.version)/sizeof(pDeviceInfo->asicVersion.version[0]));
	strSize = (UINT32)OSAL_wcslen(pDeviceInfo->asicVersion.version);
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, ":0x", WMX_MODEL_TYPE_NAME_MAX_LENGTH, &pDeviceInfo->asicVersion.version[strSize], sizeof(pDeviceInfo->asicVersion.version)/sizeof(pDeviceInfo->asicVersion.version[0]));
	OSAL_itoa_s(pid.productID, tmp, WMX_MODEL_TYPE_NAME_MAX_LENGTH, 16);
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, tmp, WMX_MODEL_TYPE_NAME_MAX_LENGTH, &pDeviceInfo->asicVersion.version[strSize+3], sizeof(pDeviceInfo->asicVersion.version)/sizeof(pDeviceInfo->asicVersion.version[0]));

	// name: should be nothing
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, "", 1, pDeviceInfo->asicVersion.name, sizeof(pDeviceInfo->asicVersion.name)/sizeof(pDeviceInfo->asicVersion.name[0]));

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After copying asic version");

	//update MAC address
	OSAL_memcpy_s(pDeviceInfo->macAddress, 6, macAdrress, 6);

	//update vendorName
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, manufacturer.manufacturerName, (int)strlen(manufacturer.manufacturerName)+1, pDeviceInfo->vendorName, sizeof(pDeviceInfo->vendorName)/sizeof(pDeviceInfo->vendorName[0]));
	//memcpy_s(pDeviceInfo->vendorName, WMX_MODEL_TYPE_NAME_MAX_LENGTH, manufacturer.manufacturerName, WMX_MODEL_TYPE_NAME_MAX_LENGTH);

	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "After copying vendor info ");

	pDeviceInfo->vendorSpecificInfoIncl = 0; //TODO: check what is vendorSpecificInfoIncl

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetDeviceInformation(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API GetODMInformation(	WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_BINARY_BLOB_P pBinaryBlob, UINT32 *pBinaryBlobSize)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_MacAddress_t macAdrress;
	wmx_ModelType_t modelType;
	wmx_Manufacturer_t manufacturer;
	wmx_SerialNumber_t serialNumber;
	wmx_NvmVersion_t nvmVersion;
	wmx_Nonce_t nonce;
	wmx_DevicePID_t pid;
	wmx_ODMInfo_t odmInfo;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetODMInformation(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_GetDeviceDetailsEx(macAdrress, &modelType, &manufacturer, &serialNumber, (wmx_pNvmVersion_t)&nvmVersion, (wmx_pODMInfo_t)&odmInfo,(wmx_pNonce_t)&nonce, &pid);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetDeviceInformation(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	if (*pBinaryBlobSize < sizeof(odmInfo))
	{
		*pBinaryBlobSize = sizeof(odmInfo);
		return WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;
	}
	
	*pBinaryBlobSize = sizeof(odmInfo);
	OSAL_memcpy_s(pBinaryBlob, *pBinaryBlobSize, odmInfo, *pBinaryBlobSize);

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetODMInformation(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API GetNVMImageVersion(	WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NVM_VERSION_P pNVMImageVersion)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_MacAddress_t macAdrress;
	wmx_ModelType_t modelType;
	wmx_Manufacturer_t manufacturer;
	wmx_SerialNumber_t serialNumber;
	wmx_NvmVersion_t nvmVersion;
	wmx_Nonce_t nonce;
	wmx_DevicePID_t pid;
	wmx_ODMInfo_t odmInfo;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNVMImageVersion(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_GetDeviceDetailsEx(macAdrress, &modelType, &manufacturer, &serialNumber, (wmx_pNvmVersion_t)&nvmVersion, (wmx_pODMInfo_t)&odmInfo,(wmx_pNonce_t)&nonce, &pid);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetNVMImageVersion(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	pNVMImageVersion->ContentVersion = nvmVersion.ContentVersion;
	pNVMImageVersion->GeneralImageVersion = nvmVersion.GeneralImageVersion;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNVMImageVersion(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API GetConnectedNSPEx(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CONNECTED_NSP_INFO_EX_P pConnectedNSP)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_NSP_t connectedNsp;
	int nspNameConv, nspRealmConv;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectedNSPEx(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting last known NSPs
	wmxStatus = wmx_GetConnectedNSP(&connectedNsp);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetConnectedNSPEx(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	pConnectedNSP->activated = connectedNsp.activated;
	pConnectedNSP->CINR = (UINT8)connectedNsp.bestCINR; 
	pConnectedNSP->NSPid = connectedNsp.nspIDs[0];
	nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, connectedNsp.nspName, (int)OSAL_strnlen(connectedNsp.nspName, WMX_NSP_NAME_MAX_SIZE)+1, pConnectedNSP->NSPName, sizeof(pConnectedNSP->NSPName)/sizeof(pConnectedNSP->NSPName[0]));
	if( nspNameConv == 0 )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to WideChar");
		return WIMAX_API_RET_FAILED;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_INFO, "realm: %s", connectedNsp.nspRealm ? connectedNsp.nspRealm : "invalid");

	nspRealmConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, connectedNsp.nspRealm, (int)OSAL_strnlen(connectedNsp.nspRealm, WMX_NSP_REALM_MAX_SIZE)+1, pConnectedNSP->NSPRealm, sizeof(pConnectedNSP->NSPRealm)/sizeof(pConnectedNSP->NSPRealm[0]));
	if( nspRealmConv == 0 )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspRealm to WideChar");
		return WIMAX_API_RET_FAILED;
	}
	pConnectedNSP->networkType = WIMAX_API_HOME; //TODO: no romaing mode on iWmxSDK structure
	pConnectedNSP->RSSI = (UINT8)connectedNsp.bestRssi;
	pConnectedNSP->linkQuality = (WMX_LINK_QUALITY_EX)connectedNsp.linkQuality;
	pConnectedNSP->structureSize = sizeof(*pConnectedNSP);

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectedNSPEx(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API GetConnectedNSP(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CONNECTED_NSP_INFO_P pConnectedNSP)
{
	WIMAX_API_RET res;
	WIMAX_API_CONNECTED_NSP_INFO_EX connectedNsp;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectedNSP(IN)");
	//check that in pointers are valid
	res = GetConnectedNSPEx(pDeviceId, &connectedNsp);
	if(WIMAX_API_RET_SUCCESS == res)
	{
		pConnectedNSP->activated = connectedNsp.activated;
		pConnectedNSP->CINR = (UINT8)connectedNsp.CINR;
		pConnectedNSP->NSPid = connectedNsp.NSPid;
		OSAL_CAPI_wmemcpy_s(pConnectedNSP->NSPName, WMX_NSP_NAME_MAX_SIZE , connectedNsp.NSPName, OSAL_CAPI_wcsnlen(connectedNsp.NSPName, WMX_NSP_NAME_MAX_SIZE -1) +1);
		OSAL_CAPI_wmemcpy_s(pConnectedNSP->NSPRealm, WMX_NSP_NAME_MAX_SIZE , connectedNsp.NSPRealm, OSAL_CAPI_wcsnlen(connectedNsp.NSPRealm, WMX_NSP_NAME_MAX_SIZE -1) +1);
		pConnectedNSP->networkType = connectedNsp.networkType;
		pConnectedNSP->RSSI = (UINT8)connectedNsp.RSSI;
		pConnectedNSP->structureSize = connectedNsp.structureSize;
	}
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectedNSP(OUT)");
	return res;
}
WIMAX_API_RET WIMAX_API SubscribeDeviceStatusChange (WIMAX_API_DEVICE_ID_P pDeviceId, IndDeviceStatusUpdate pCallbackFnc)
{
	//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeDeviceStatusChange(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (deviceStatusCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_FAILED;
	}

	deviceStatusCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeDeviceStatusChange(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeDeviceStatusChange(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	//	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeDeviceStatusChange(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (deviceStatusCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	deviceStatusCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeDeviceStatusChange(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API CmdResetToFactorySettings  (  WIMAX_API_DEVICE_ID_P  pDeviceId   )   
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdResetToFactorySettings(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_ResetToFactorySettings();
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdResetToFactorySettings(OUT). returned - %s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}
WIMAX_API_RET WIMAX_API CmdResetWimaxDevice( WIMAX_API_DEVICE_ID_P  pDeviceId ) 
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdResetWimaxDevice(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//cmdDisable();
	//cmdEnable();
	wmxStatus = wmx_ResetDevice();

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdResetWimaxDevice(OUT)");
	return WmxStatusToWimaxAPIRet(wmxStatus);	
}
//Connection Info
WIMAX_API_RET WIMAX_API SetRoamingMode(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_ROAMING_MODE roamingMode)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetRoamingMode(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting last known NSPs
	if (roamingMode == WIMAX_API_ROAMING_ENABLED)
	{
		wmxStatus = wmx_SetUserRoamingMode(UserEnableRoaming);
	}
	else
	{
		wmxStatus = wmx_SetUserRoamingMode(UserDisableRoaming);
	}
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetRoamingMode(OUT). Returned - %s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);	
}

WIMAX_API_RET WIMAX_API GetRoamingMode(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_ROAMING_MODE_P pRoamingMode)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_UserRoamingMode_t roamingMode;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetRoamingMode(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting last known NSPs
	wmxStatus = wmx_GetUserRoamingMode(&roamingMode);
	if (roamingMode == UserDisableRoaming)
	{
		*pRoamingMode = WIMAX_API_ROAMING_DISABLED;
	}
	else
	{
		*pRoamingMode = WIMAX_API_ROAMING_ENABLED;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetRoamingMode(OUT). Returned=%s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);	
}


WIMAX_API_RET WIMAX_API SetConnectedAsCurrentPreferredCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL isEnable)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet;	

	wmxRet = WIMAX_API_RET_SUCCESS;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetConnectedAsCurrentPreferredCapabilityStatus(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_SetConnectedAsCurrentPreferredCapabilityStatus(isEnable);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetConnectedAsCurrentPreferredCapabilityStatus(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API GetConnectedAsCurrentPreferredCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL *pIsEnabled)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectedAsCurrentPreferredCapabilityStatus(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting Connect as Current preferred status
	wmxStatus = wmx_GetConnectedAsCurrentPreferredCapabilityStatus(pIsEnabled);


	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectedAsCurrentPreferredCapabilityStatus(OUT). Returned=%s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);	
}

WIMAX_API_RET WIMAX_API SubscribeRoamingModeUpdate (WIMAX_API_DEVICE_ID_P pDeviceId, IndRoamingModeUpdate pCallbackFnc) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeRoamingModeUpdate(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (roamingModeUpdateCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	roamingModeUpdateCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeRoamingModeUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;	
}

WIMAX_API_RET WIMAX_API SubscribeConnectedAsCurrentPreferredCapabilityStatus (WIMAX_API_DEVICE_ID_P pDeviceId, IndConnectedAsCurrentPreferredCapabilityStatusUpdate pCallbackFnc) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeConnectedAsCurrentPreferredCapabilityStatus(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (connectedAsCurrentPreferredCapabilityStatusCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	connectedAsCurrentPreferredCapabilityStatusCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeConnectedAsCurrentPreferredCapabilityStatus(OUT)");
	return WIMAX_API_RET_SUCCESS;	
}

WIMAX_API_RET WIMAX_API UnsubscribeRoamingModeUpdate (WIMAX_API_DEVICE_ID_P pDeviceId) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeRoamingModeUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (roamingModeUpdateCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	//TODO: Add capability to unregister on NDnS agent!!
	roamingModeUpdateCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeRoamingModeUpdate(OUT)");
	return wmxRet;	
}

WIMAX_API_RET WIMAX_API UnsubscribeConnectedAsCurrentPreferredCapabilityStatus (WIMAX_API_DEVICE_ID_P pDeviceId) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeConnectedAsCurrentPreferredCapabilityStatus(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (connectedAsCurrentPreferredCapabilityStatusCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	connectedAsCurrentPreferredCapabilityStatusCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeConnectedAsCurrentPreferredCapabilityStatus(OUT)");
	return wmxRet;	
}

WIMAX_API_RET WIMAX_API GetIPInterfaceIndex(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_INTERFACE_INFO_P pInterfaceInfo) 
{
	WIMAX_API_RET wmxRet;
	char deviceName[MAX_SIZE_OF_STRING_BUFFER];
	BOOL retVal;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetIPInterfaceIndex(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting the interface name
	retVal = OSAL_FindDeviceFileName(deviceName);
	if (retVal)
	{
		OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, deviceName, (int)OSAL_strnlen(deviceName, sizeof(deviceName)) + 1, 
			pInterfaceInfo->interfaceName, sizeof(pInterfaceInfo->interfaceName)/sizeof(pInterfaceInfo->interfaceName[0]));
	}
	else
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No interface found");
		return WIMAX_API_RET_FAILED;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetIPInterfaceIndex(OUT). Inteface name=%s", pInterfaceInfo->interfaceName);
	return wmxRet;	
}
//Connection Status
WIMAX_API_RET WIMAX_API GetStatistics(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CONNECTION_STAT_P pStatistics)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_UserStatistics_t statistics;
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetStatistics(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//getting last known NSPs
	wmxStatus = wmx_GetUserStatistics(&statistics);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetStatistics(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}
	
	pStatistics->totalRxByte = statistics.TotalRxBytes;
	pStatistics->totalRxPackets = statistics.TotalRxPackets;
	pStatistics->totalTxByte = statistics.TotalTxBytes;
	pStatistics->totalTxPackets = statistics.TotalTxPackets;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetStatistics(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

//OMA Object group
WIMAX_API_RET WIMAX_API GetProvisioningStatus(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_WSTRING nspName, BOOL * pProvisoningStatus)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	UINT32 numOfNSPs = 0, i;
	wmx_pNSP_t pNSP = NULL;
	char tmpName[MAX_SIZE_OF_NSP_NAME] = {'\0'};

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetProvisioningStatus(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check for provisioned NSPs
	wmxStatus = wmx_GetProvisionedNSPs(&numOfNSPs, pNSP);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetProvisioningStatus(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	*pProvisoningStatus = FALSE;
	//search for the nsp's name
	if (nspName != NULL)
	{
		if ( MAX_SIZE_OF_NSP_NAME == (size_t)OSAL_wcsnlen(nspName, MAX_SIZE_OF_NSP_NAME) )
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetProvisioningStatus Failed - nspName is too long");
			return WIMAX_API_RET_FAILED;
		}
		OSAL_CAPI_WideCharToMultiByte(CP_ACP, 0, nspName, -1, tmpName, MAX_SIZE_OF_NSP_NAME, NULL, NULL);
		for (i=0; i<numOfNSPs; i++)
		{
			if (strcmp(tmpName, pNSP[i].nspName) == 0)
			{
				*pProvisoningStatus = pNSP[i].activated;
			}
		}
	}
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetProvisioningStatus(OUT). Provision status = %d",*pProvisoningStatus);
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API GetContactInformation(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_WSTRING nspName, WIMAX_API_CONTACT_INFO_P pContactInfo, UINT32* pSizeOfContactList)
{
	WIMAX_API_RET wmxRet;
	wmx_Status_t wmxStatus;
	UINT32 i;	
	char tmpName[MAX_SIZE_OF_NSP_NAME];
	wmx_ContactInformation_t contactInformation[WMX_URI_MAX_NUM];
	UINT32 numOfContacts = WMX_URI_MAX_NUM;
	int uriConv, textConv;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetContactInformation(IN)");
		
	if (pSizeOfContactList == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pSizeOfContactList == NULL");
		wmxRet = WIMAX_API_RET_INVALID_PARAMETER;
		*pSizeOfContactList = 0;
		goto GetContactInformation_end;
	}

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");		
		*pSizeOfContactList = 0;
		goto GetContactInformation_end;
	}
	
	if ((pContactInfo == NULL) || (nspName == NULL))
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetContactInformation wrong argument");
		wmxRet = WIMAX_API_RET_INVALID_PARAMETER;
		*pSizeOfContactList = 0;
		goto GetContactInformation_end;
	}

	if ( MAX_SIZE_OF_NSP_NAME == (size_t)wcsnlen(nspName, MAX_SIZE_OF_NSP_NAME) )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetContactInformation Failed - nspName is too long");
		wmxRet = WIMAX_API_RET_FAILED;
		*pSizeOfContactList = 0;
		goto GetContactInformation_end;
	}

	// Copy the nsp's name
		OSAL_CAPI_WideCharToMultiByte(CP_ACP, 0, nspName, -1, tmpName, MAX_SIZE_OF_NSP_NAME, NULL, NULL);

	wmxStatus = wmx_GetNSPContactInfoByName(tmpName, &numOfContacts, contactInformation);
	
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetContactInformation(OUT). ERROR - ret val for nsp=%s is %s",
			nspName, wmxGetStatusStr(wmxStatus));
		*pSizeOfContactList = 0;
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto GetContactInformation_end;
	}

	if (*pSizeOfContactList < numOfContacts)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL");
		*pSizeOfContactList = 0;
		wmxRet = WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL;
		goto GetContactInformation_end;
	}
	else
	{
		*pSizeOfContactList = numOfContacts;
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "GetContactInfo: list size=[%d]", *pSizeOfContactList);		
	}

	for (i=0; i < numOfContacts; i++)
	{
		uriConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, contactInformation[i].uri, (int)OSAL_strnlen(contactInformation[i].uri, WMX_URI_MAX_SIZE)+1, pContactInfo[i].URI, sizeof(pContactInfo[i].URI)/sizeof(pContactInfo[i].URI[0]));
		if( uriConv == 0 )
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert uri to WideChar");
			return WIMAX_API_RET_FAILED;
		}
		textConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, contactInformation[i].text, (int)OSAL_strnlen(contactInformation[i].text, MAX_SIZE_OF_STRING_BUFFER)+1, pContactInfo[i].textForURI, sizeof(pContactInfo[i].textForURI)/sizeof(pContactInfo[i].textForURI[0]));
		if( textConv == 0 )
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert contact information text to WideChar");
			return WIMAX_API_RET_FAILED;
		}
		pContactInfo[i].contactType = (WIMAX_API_CONTACT_TYPE)contactInformation[i].uriType;
		pContactInfo[i].structureSize = sizeof(pContactInfo[i]);
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "GetContactInfo: uri[%d]=[%s]", i, contactInformation[i].uri);		
	}
		
	wmxRet = WIMAX_API_RET_SUCCESS;

GetContactInformation_end:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetContactInformation(OUT)");
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SubscribeProvisioningOperation (WIMAX_API_DEVICE_ID_P pDeviceId, IndProvisioningOperation pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeProvisioningOperation(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (provisioningOperationCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	
	provisioningOperationCB = pCallbackFnc;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeProvisioningOperation(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeProvisioningOperation(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeProvisioningOperation(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is not NULL
	if (provisioningOperationCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}
	
	provisioningOperationCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeProvisioningOperation(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API SetServiceProviderUnLock(WIMAX_API_DEVICE_ID_P  pDeviceId, WIMAX_API_WSTRING  lockCode )
{
	WIMAX_API_RET wmxRet;
	char *cLockCode;
	size_t lockCodeLength;
	int retVal;
	wmx_Status_t wmxStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetServiceProviderUnLock(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//convert wide char to char string
	lockCodeLength = OSAL_wcslen(lockCode);
	cLockCode = malloc(TEXT_LEN(lockCodeLength));
	retVal = OSAL_CAPI_WideCharToMultiByte(CP_ACP, 0 , lockCode, -1, cLockCode, (int)(TEXT_LEN(lockCodeLength)), NULL, NULL);
	if (retVal == 0)
	{
		free(cLockCode);
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "String conversion failure");
		return WIMAX_API_RET_FAILED;
	}

	wmxStatus = wmx_SetServiceProviderUnLock(cLockCode);
	free(cLockCode);
	////TODO: STUB - need to update
	//retVal = RegistryController_SetStrValue(HKEY_LOCAL_MACHINE, KEY_ENTRY_PIPECONFIG, KEY_ENTRY_SERVICE_PROVIDER_LOCK, "");
	//if (!retVal)
	//{
	//	TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No locked service provider");
	//	return WIMAX_API_RET_FAILED;
	//}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetServiceProviderUnLock(OUT). Returned - %d", wmxStatus);
	return WmxStatusToWimaxAPIRet(wmxStatus);	
}

#ifdef NATIVE_LINUX
	WIMAX_API_RET WIMAX_API GetServiceProviderLockStatus(  WIMAX_API_DEVICE_ID_P  pDeviceId, WIMAX_API_LOCK_STATUS_P  pLockStatus, char  NSPName[MAX_SIZE_OF_NSP_NAME])
#else
	WIMAX_API_RET WIMAX_API GetServiceProviderLockStatus(  WIMAX_API_DEVICE_ID_P  pDeviceId, WIMAX_API_LOCK_STATUS_P  pLockStatus, UCHAR16  NSPName[MAX_SIZE_OF_NSP_NAME])
#endif
{
	WIMAX_API_RET wmxRet;
	char val[MAX_SIZE_OF_NSP_NAME];
	wmx_Status_t wmxStatus;
	wmx_SPLockStatus_t spLockStatus;
	int nspNameConv;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetServiceProviderLockStatus(IN)");
	*pLockStatus = WIMAX_API_DEVICE_UNLOCKED;

	if (NSPName == NULL)
	{
		wmxRet = WIMAX_API_RET_INVALID_PARAMETER;
		goto Finalize;
	}
	OSAL_CAPI_strcpy_s(NSPName, MAX_SIZE_OF_NSP_NAME, TEXT(""));

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		goto Finalize;
	}

	//call native function
	wmxStatus = wmx_GetServiceProviderLockStatus(&spLockStatus, val);

	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}

	*pLockStatus = (spLockStatus == WIMAX_API_DEVICE_UNLOCKED)? WIMAX_API_DEVICE_UNLOCKED : WIMAX_API_DEVICE_UNLOCKED;
	nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, val, (int)OSAL_strnlen(val, MAX_SIZE_OF_NSP_NAME)+1, NSPName, sizeof(NSPName)/sizeof(NSPName[0]));
	if( nspNameConv == 0)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to WideChar");
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;
	}
	
Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetServiceProviderLockStatus(OUT). ret val = %d",wmxRet);
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SetPackageUpdateState( WIMAX_API_DEVICE_ID_P  pDeviceId, WIMAX_API_PACKAGE_UPDATE_STATE  packageUpdateState )  
{
	WIMAX_API_RET wmxRet;
	wmx_Status_t wmxStatus;
	wmx_PackageUpdateState_t wmxPackageUpdateState;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetPackageUpdateState(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//call the ND&S function
	wmxPackageUpdateState = (packageUpdateState == WIMAX_API_PACKAGE_UPDATE_DELAY)? PackageUpdateDenied : PackageUpdateApproved;
	wmxStatus = wmx_SetPackageUpdateState(wmxPackageUpdateState);

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetPackageUpdateState(OUT). Returned - %s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);		
}

WIMAX_API_RET WIMAX_API SubscribePackageUpdate (WIMAX_API_DEVICE_ID_P pDeviceId, IndPackageUpdate pCallbackFnc) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePackageUpdate(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (packageUpdate != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	packageUpdate = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePackageUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;	
}
WIMAX_API_RET WIMAX_API UnsubscribePackageUpdate (WIMAX_API_DEVICE_ID_P pDeviceId) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePackageUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (packageUpdate == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	//TODO: Add capability to unregister on NDnS agent!!
	packageUpdate = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePackageUpdate(OUT)");
	return wmxRet;	
}
WIMAX_API_RET WIMAX_API SubscribePackageDownloadProgress (WIMAX_API_DEVICE_ID_P pDeviceId, IndPackageDownloadProgress pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePackageDownloadProgress(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	if (packageDownloadProgress != NULL)
	{
		TRACE (TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	packageDownloadProgress  = pCallbackFnc;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePackageDownloadProgress(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribePackageDownloadProgress (WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePackageDownloadProgress(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	if (packageDownloadProgress == NULL)
	{
		TRACE (TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	packageDownloadProgress  = NULL;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePackageDownloadProgress(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API GetPackageInformation(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PACKAGE_INFO_P pPackageInfo)
{
	WIMAX_API_RET wmxRet;
	wmx_Status_t wmxStatus;
	wmx_PackageInfo_t packageInfo;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetPackageInformation(IN)");
	if (pPackageInfo == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pPackageInfo == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//get contact information
	wmxStatus = wmx_GetPackageInfo(&packageInfo);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetPackageInformation(OUT). ERROR - ret value=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	//copy fields
	pPackageInfo->forceReboot = packageInfo.forceReboot;
	pPackageInfo->mandatoryUpdate = packageInfo.mandatoryUpdate;
	pPackageInfo->warnUser = packageInfo.warnUser;
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, packageInfo.fileName, (int)OSAL_strnlen(packageInfo.fileName, MAX_SIZE_OF_STRING_BUFFER)+1, pPackageInfo->fileName, sizeof(pPackageInfo->fileName)/sizeof(pPackageInfo->fileName[0]));
	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, packageInfo.filePath, (int)OSAL_strnlen(packageInfo.filePath, MAX_SIZE_OF_STRING_BUFFER)+1, pPackageInfo->filePath, sizeof(pPackageInfo->filePath)/sizeof(pPackageInfo->filePath[0]));

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetPackageInformation(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
//Coexistence
WIMAX_API_RET WIMAX_API SetCoexistenceMode(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_COEXISTENCE_MODE coexMode)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetCoexistenceMode(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	switch(coexMode)
	{
	case MODE_XOR:
		TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "CommonAPI is trying to change the coex to XOR. This is not supported by EVP");
		//wmxStatus = wmx_SetCoexistenceMode(MODE_XOR);
		wmxStatus = WMX_ST_FAIL;

	case MODE_CM:
		wmxStatus = wmx_SetCoexistenceMode(MODE_CM);
		break;
	}
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetCoexistenceMode(OUT). Returned-%s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}
WIMAX_API_RET WIMAX_API GetCoexistenceMode(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_COEXISTENCE_MODE_P pCoexMode)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_CoexistenceMode_t coexMode;
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetCoexistenceMode(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_GetCoexistenceMode(&coexMode);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetCoexistenceMode(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	switch(coexMode)
	{
	case WMX_MODE_XOR:
		*pCoexMode = MODE_XOR;
		break;
	case WMX_MODE_CM:
		*pCoexMode = MODE_CM;
		break;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetCoexistenceMode(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API IsAssociated(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_ASSOCIATION_STATUS_P pAssociated)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;
	wmx_Associate_t associated;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "IsAssociated(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	wmxStatus = wmx_IsAssociated(&associated);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "IsAssociated(OUT). ERROR - ret val=%s",wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	switch(associated)
	{
	case WIMAX_API_DEVICE_ASSOCIATED:
		*pAssociated = Associated;
		break;
	case WIMAX_API_DEVICE_NOT_ASSOCIATED:
		*pAssociated = Not_Associated;
		break;
	}

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "IsAssociated(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API SubscribeCoexistenceModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndCoexistenceModeUpdate pCallbackFnc )
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeCoexistenceModeUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is not NULL
	if (coexistenceModeCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_FAILED;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	
	coexistenceModeCB = pCallbackFnc;
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeCoexistenceModeUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribeCoexistenceModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeCoexistenceModeUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (coexistenceModeCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	//TODO: Add capability to unregister on NDnS agent!!
	coexistenceModeCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeCoexistenceModeUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API SetMSChap_v2Crd(  WIMAX_API_DEVICE_ID_P pDeviceId,
										  WIMAX_API_PROFILE_ID profileId,
									  	  WIMAX_API_WSTRING username,
										  WIMAX_API_WSTRING password)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet;
	char tmpUsername[WMX_SUBSCRIBER_ID_MAX_SIZE] = {'\0'};
	char tmpPassword[MAX_EAP_PASSWORD_SIZE] = {'\0'};
	/*size_t outSize;*/
	int passConv, userConv;
	//pProfileList_t selectedProfile = profileListHead;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetMSChap_v2Crd(IN)");
	//Check Parameters And Permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");		
		goto Finalize;
	}
	
	// TODO: In current implementation we take profileId as NSPId without conversion. 
	// In the future we will need to add logic for a better translation

	if( (username == NULL) || (password == NULL) )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Parameters holds NULL");
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;	
	}
	// TODO: see if a specific API return value is needed.
	if ( WMX_SUBSCRIBER_ID_MAX_SIZE == (size_t)wcsnlen(username, WMX_SUBSCRIBER_ID_MAX_SIZE) )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "SetMSChap_v2Crd Failed - username is too long");
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;
	}

	if ( MAX_EAP_PASSWORD_SIZE == (size_t)wcsnlen(password, MAX_EAP_PASSWORD_SIZE) )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "SetMSChap_v2Crd Failed - password is too long");
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;
	}

	// convert username and password from WIMAX_API_WSTRING (UCHAR16*) to Multi-byte
	userConv = OSAL_CAPI_WideCharToMultiByte
		(CP_UTF8, 0, username, -1, tmpUsername, WMX_SUBSCRIBER_ID_MAX_SIZE, NULL, NULL);
	if ( userConv == 0 )
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert username to UTF-8. error=%d",GetLastError());
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;
	}

	passConv = OSAL_CAPI_WideCharToMultiByte
		(CP_UTF8, 0, password, -1, tmpPassword, MAX_EAP_PASSWORD_SIZE, NULL, NULL);
	if ( passConv == 0 )
	{
		//int err = GetLastError();
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert password to UTF-8.");
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;
	}

	wmxStatus = wmx_SetMSChap_v2Crd(profileId, tmpUsername, tmpPassword);	
	wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);  

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetMSChap_v2Crd(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SetConnectionMode(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_CONNECTION_MODE connectionMode)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet;	
	wmx_UserConnectMode_t userConnectMode;

	wmxRet = WIMAX_API_RET_SUCCESS;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetConnectionMode(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}	

	switch(connectionMode)
	{
	case WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT:
		userConnectMode = UserSemiManScanManConnect;
		break;		 
	case WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT:
		userConnectMode = UserSemiManScanAutoConnect;
		break;
	case WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT:
		userConnectMode = UserAutoScanManConnect;
		break;
	case WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT:
		userConnectMode = UserAutoScanAutoConnect;
		break;
	case WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT:
		userConnectMode = UserManScanManConnect;
		break;
	default:
		wmxRet = WIMAX_API_RET_FAILED;
		goto Finalize;
		break;
	}

	wmxStatus = wmx_SetUserConnectMode(userConnectMode);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}
	isConnectionModeSet = TRUE;

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetConnectionMode(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API GetConnectionMode(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_CONNECTION_MODE_P pConnectionMode)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;	
	wmx_UserConnectMode_t userConnectMode;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectionMode(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_GetUserConnectMode(&userConnectMode);
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "Got connectionMode=%d",userConnectMode);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}

	switch(userConnectMode)
	{
	case UserSemiManScanManConnect:
		*pConnectionMode = WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT;
		break;		 
	case UserSemiManScanAutoConnect:
		*pConnectionMode = WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT;
		break;
	case UserAutoScanManConnect:
		*pConnectionMode = WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT;
		break;
	case UserAutoScanAutoConnect:
		*pConnectionMode = WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT;
		break;
	case UserManScanManConnect:
		*pConnectionMode = WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT;
		break;
	default:
		wmxRet = WIMAX_API_RET_FAILED;
		break;
	}

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectionMode(OUT). ret val = %s, connectionMode=%d",wmxGetStatusStr(wmxStatus), *pConnectionMode);
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SubscribeMediaStatusUpdate (WIMAX_API_DEVICE_ID_P pDeviceId, IndMediaStatusUpdate pCallbackFnc) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeMediaStatusUpdate(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (mediaStatusUpdate != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	mediaStatusUpdate = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeMediaStatusUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;	
}

WIMAX_API_RET WIMAX_API UnsubscribeMediaStatusUpdate (WIMAX_API_DEVICE_ID_P pDeviceId) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeMediaStatusUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (mediaStatusUpdate == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	mediaStatusUpdate = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeMediaStatusUpdate(OUT)");
	return wmxRet;	
}

WIMAX_API_RET WIMAX_API SubscribeConnectionModeUpdate (WIMAX_API_DEVICE_ID_P pDeviceId, IndConnectionModeUpdate pCallbackFnc) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeConnectionModeUpdate(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (connectionModeUpdateCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	connectionModeUpdateCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeConnectionModeUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;	
}
WIMAX_API_RET WIMAX_API UnsubscribeConnectionModeUpdate (WIMAX_API_DEVICE_ID_P pDeviceId) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeConnectionModeUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (connectionModeUpdateCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	//TODO: Add capability to unregister on NDnS agent!!
	connectionModeUpdateCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeConnectionModeUpdate(OUT)");
	return wmxRet;	
}
WIMAX_API_RET WIMAX_API CmdDeprovisionProfile(	WIMAX_API_DEVICE_ID_P pDeviceId,
												WIMAX_API_PROFILE_ID profileID)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;		

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdDeprovisionProfile(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_DeprovisionNSP(profileID);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}	

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdDeprovisionProfile(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API GetConnectionTime(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_CONNECTION_TIME_P pConnectionTime)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;	
	wmx_UserLinkStatus_t userLinkStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectionTime(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_GetUserLinkStatus(&userLinkStatus);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}	

	*pConnectionTime = userLinkStatus.time;

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetConnectionTime(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API CmdNetworkSearch(	WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;		

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearch(IN)");
	wideScanStartedAndCompleted = FALSE;
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "wideScanStartedAndCompleted = FALSE, CmdNetworkSearch");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_CmdUserStartScan(SCAN_TYPE_PREFERRED);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}		

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearch(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API CmdRestoreBackupProvisioningDatabase(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;		

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdRestoreBackupProvisioningDatabase(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_RestoreBackupProvisioningDatabase();
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}		

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdRestoreBackupProvisioningDatabase(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SubscribeNetworkSearch(WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearch pCallbackFnc )
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearch(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (networkSearch != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback already registered");
		return WIMAX_API_RET_FAILED;
	}	

	networkSearch = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearch(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API SubscribeNetworkSearchEx(WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearchEx pCallbackFnc )
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearchEx(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (networkSearchEx != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback already registered");
		return WIMAX_API_RET_FAILED;
	}	

	networkSearchEx = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeNetworkSearchEx(OUT)");
	return WIMAX_API_RET_SUCCESS;

}
WIMAX_API_RET WIMAX_API SubscribeCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P pDeviceId, IndCurrentPreferredProfile pCallbackFnc )
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeCurrentPreferredProfile(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (currentPreferredProfile != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback already registered");
		return WIMAX_API_RET_FAILED;
	}	

	currentPreferredProfile = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeCurrentPreferredProfile(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribeCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscriberCurrentPreferredProfile(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	currentPreferredProfile = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscriberCurrentPreferredProfile(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API CmdStopScan( WIMAX_API_DEVICE_ID_P pDeviceId )
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdStopScan(IN)");
	//Check Parameters And Permissions
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//stop the scanning
	wmxStatus = wmx_CmdUserStopScan();

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdStopScan(OUT). returned - %s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}
//	Call the wrappers init, 
//	register to scan completed and system state
//	change the connect mode
WIMAX_API_RET WIMAX_API AttachToSDK()
{
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	BOOL regData;
	UINT32 privData;
	wmx_SystemState_t systemState;
	wmx_ConnectProgressInfo_t connectionProgressInfo = NotApplicable;
	wmx_RfSwitchesStatus_t rfSwitchesStatus;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "AttachToSDK(IN)");

	OSAL_lock_mutex(attachDetachMutex);
	TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "AttachToSDK - isAttached=%d, isDetached=%d", isAttached, isDetached);
	if (OSAL_atomic_compareExchange(&isAttached, 1, 0) == 0)
	{				
		if (READY == wmxSDK_GetCtrlStatus())
		{		
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "AttachToSDK - READY == wmxSDK_GetCtrlStatus()");
			wmxStatus = wmxNds_Init();
			if (wmxStatus != WMX_ST_OK)
			{			
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmxMsc_Init();
			if (wmxStatus != WMX_ST_OK)
			{			
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			//setting scan mode & connect mode	
			if(WIMAX_API_PRIVILEGE_READ_WRITE == privilege)
			{
				regData = OSAL_ConfigController_GetNumValue(OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_SET_CONNECTION_MODE, &privData);
				if ((!regData) || privData == 1)
				{
					if (isResetAttach)
					{
						if (!isConnectionModeSet)
						{
							wmxStatus = wmx_SetUserConnectMode(UserSemiManScanManConnect);
							if (wmxStatus != WMX_ST_OK)
							{			
								wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
								goto Finalize;
							}

							isConnectionModeSet = TRUE;
						}
					}
					isResetAttach = FALSE;
				}
			}
			
			wmxStatus = wmx_RegisterDeviceStatusUpdateCB(DeviceStateCB);
			TRACE(TR_MOD_COMMON_API, TR_SEV_DEBUG, "registered on wmx_RegisterDeviceStatusUpdateCB"); //[ndenes]
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{				
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			wmxStatus = wmx_RegisterUserMediaStatusCB(wmxUserMediaStatusCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{				
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			
			wmxStatus = wmx_RegisterUserScanCompletedCB(WimaxScanCompletedCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{								
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}					

			wmxStatus = wmx_RegisterUserScanUpdateCB(WimaxUserScanUpdateCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{								
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}					

			wmxStatus = wmx_RegisterIndPackageUpdateCB(PackageUpdateBC);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{								
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			wmxStatus = wmx_RegisterIndPackageDownloadProgressCB(PackageDownloadProgressCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{								
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			wmxStatus = wmx_RegisterIndProvisioningOperationCB(wmxProvisioningOperationCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			wmxStatus = wmx_RegisterCoexUpdateCB(wmxCoexistenceModeCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			wmxStatus = wmx_RegisterCurrentPreferredProfileCB(CurrentPreferredProfileCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmx_RegisterConnectionModeUpdateCB(wmxConnectionModeUpdateCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmx_RegisterFastReconnectStatusUpdateCB(wmxFastReconnectModeUpdateCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmx_RegisterRoamingModeUpdateCB(wmxRoamingModeUpdateCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmx_RegisterRfTakenCB(wmxRfTakenCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmx_RegisterPNMNotificationCB(wmxPNMNotificationCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{	
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "wmx_RegisterPNMNotificationCB(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}
			wmxStatus = wmx_GetSystemState(&systemState, &connectionProgressInfo, &rfSwitchesStatus);
			if (wmxStatus != WMX_ST_OK)
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetDeviceStatus(OUT). ERROR - ret val=%s", wmxGetStatusStr(wmxStatus));
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			wmxStatus = wmx_RegisterConnectedAsCurrentPreferredCapabilityStatusCB(wmxConnectedAsCurrentPreferredCapabilityStatusCB);
			if (wmxStatus != WMX_ST_OK &&
				wmxStatus != WMX_ST_CALLBACK_ALREADY_REGISTERED)
			{
				wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
				goto Finalize;
			}

			if(DataPathConnected == systemState || 
				Idle == systemState)
			{
				isConnected = TRUE;
			}

			if (systemState<=RfOff)
			{
				rfState = WIMAX_API_RF_OFF;
			}
			else
			{
				rfState = WIMAX_API_RF_ON;
			}

			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "AttachToSDK: systemState=%d , rfState=%d", systemState, rfState);
			//isDeviceOpen = TRUE;
			OSAL_atomic_compareExchange(&isDetached, 0, 1); 
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "AttachToSDK(OUT). Device Ready. SDK attached - isAttached=%d, isDetached=%d", isAttached, isDetached);
			OSAL_unlock_mutex(attachDetachMutex);
			return WIMAX_API_RET_SUCCESS;
		}
		else
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "AttachToSDK(OUT). Device not ready - isAttached=%d, isDetached=%d", isAttached, isDetached);
			wmxRet = WIMAX_API_RET_DEVICE_MISSING;
			goto Finalize;
		}
	}
	else
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "AttachToSDK(OUT) - isAttached=%d, isDetached=%d", isAttached, isDetached);
		OSAL_unlock_mutex(attachDetachMutex);
		return WIMAX_API_RET_SUCCESS;
	}
	
Finalize:	
	//isDeviceOpen = FALSE;
	OSAL_atomic_compareExchange(&isAttached, 0, 1); 
	OSAL_atomic_compareExchange(&isDetached, 0, 1); 	
	OSAL_unlock_mutex(attachDetachMutex);
	DetachFromSDK();
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "AttachToSDK(OUT). RetVal=%s", wmxGetStatusStr(wmxStatus));	
	return wmxRet;
}

WIMAX_API_RET WIMAX_API DetachFromSDK()
{	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "DetachFromSDK(IN)");
	OSAL_lock_mutex(attachDetachMutex);
	if (OSAL_atomic_compareExchange(&isDetached, 1, 0) == 0)
	{
		wmx_UnregisterDeviceStatusUpdateCB();
		wmx_UnregisterUserMediaStatusCB();
		wmx_UnregisterUserScanCompletedCB();
		wmx_UnregisterUserScanUpdateCB();
		wmx_UnregisterIndPackageUpdateCB();
		wmx_UnregisterIndProvisioningOperationCB();
		wmx_UnregisterCoexUpdateCB();
		wmx_UnregisterCurrentPreferredProfileCB();
		wmx_UnregisterConnectionModeUpdateCB();
		wmx_UnregisterFastReconnectStatusUpdateCB();
		wmx_UnregisterRoamingModeUpdateCB();
		wmx_UnregisterConnectedAsCurrentPreferredCapabilityStatusCB();
		wmx_UnregisterRfTakenCB();
		wmx_UnregisterPNMNotificationCB();
		wmx_UnregisterIndPackageDownloadProgressCB();
		wmxNds_Finalize();
		wmxMsc_Finalize();	
	}
	else
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "DetachFromSDK(OUT) - isDetached=%d, isAttached=%d",isDetached, isAttached);	
		OSAL_unlock_mutex(attachDetachMutex);		
		return WIMAX_API_RET_SUCCESS;
	}
	
	//isDeviceOpen = FALSE;	
	OSAL_atomic_compareExchange(&isAttached, 0, 1); 
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "DetachFromSDK(OUT) - isDetached=%d, isAttached=%d",isDetached, isAttached);	
	OSAL_unlock_mutex(attachDetachMutex);
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API SetFastReconnectCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL isEnabled)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet;	

	wmxRet = WIMAX_API_RET_SUCCESS;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetFastReconnectCapabilityStatus(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_SetUserFastReconnectStatus(isEnabled);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetFastReconnectCapabilityStatus(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}

WIMAX_API_RET WIMAX_API GetFastReconnectCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL *pIsEnabled)
{
	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;	
	BOOL isEnabled;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetFastReconnectCapabilityStatus(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		return wmxRet;
	}

	wmxStatus = wmx_GetUserFastReconnectStatus(&isEnabled);
	if (wmxStatus != WMX_ST_OK)
	{
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}	

	*pIsEnabled = isEnabled;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetFastReconnectCapabilityStatus(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}
WIMAX_API_RET WIMAX_API SubscribeFastReconnectCapabilityStatusUpdate (WIMAX_API_DEVICE_ID_P pDeviceId, IndFastReconnectCapabilityStatusUpdate pCallbackFnc) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeFastReconnectCapabilityStatusUpdate(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (fastReconnectModeUpdateCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	//check that the passed pointer is valid
	if (pCallbackFnc == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pCallbackFnc == NULL");
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	fastReconnectModeUpdateCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeFastReconnectCapabilityStatusUpdate(OUT)");
	return WIMAX_API_RET_SUCCESS;	
}
WIMAX_API_RET WIMAX_API UnsubscribeFastReconnectCapabilityStatusUpdate (WIMAX_API_DEVICE_ID_P pDeviceId) 
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeFastReconnectCapabilityStatusUpdate(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (fastReconnectModeUpdateCB == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback not registered");
		return WIMAX_API_RET_FAILED;
	}

	//TODO: Add capability to unregister on NDnS agent!!
	fastReconnectModeUpdateCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeFastReconnectCapabilityStatusUpdate(OUT)");
	return wmxRet;	
}


WIMAX_API_RET WIMAX_API CmdNetworkSearchDirect(WIMAX_API_DEVICE_ID_P pDeviceId, 
											   WIMAX_API_CHANNEL_INFO_P pChannels,
											   UINT32 listSize,
											   BOOL isBlocking)
{
	wmx_Status_t wmxStatus;
	WIMAX_API_RET wmxRet;	
	wmx_pChannelInfo_t pList = NULL;
	int i;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearchDirect(IN)");

	// Verifies device permissions.
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdNetworkSearchDirect(OUT). Error - No permissions");
		return wmxRet;
	}

	// Validates function parameters.
	if (NULL == pChannels || listSize == 0 || listSize > WIMAX_API_CHANNEL_INFO_LIST_MAX_NUM_OF_ENTRIES)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdNetworkSearchDirect(OUT). Error - Bad parameters. pChannels is NULL = %s, listSize is %d.", NULL == pChannels? "TRUE" : "FALSE", listSize);
		return WIMAX_API_RET_INVALID_PARAMETER;
	}

	pList = (wmx_pChannelInfo_t)malloc(listSize * sizeof(wmx_ChannelInfo_t));  
	if (NULL == pList)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdNetworkSearchDirect(OUT). Error - malloc error. pList failed to be allocated!!!");
		return WIMAX_API_RET_FAILED;
	}

	// Copies all values of each element in pChannels into pList.
	// The duplex mode is not copied.
	for (i = 0; i < (int) listSize; i++)
	{
		pList[i].bw = (wmx_BW_t) pChannels[i].bw;
		pList[i].channelID = (wmx_ChannelID_t) pChannels[i].channelID;
		pList[i].fft = (wmx_FFT_t) pChannels[i].fft;
		pList[i].frequency = (wmx_Frequency_t) pChannels[i].frequency;
		OSAL_memcpy_s(pList[i].preambleBitmap, sizeof(wmx_Preambles_t), pChannels[i].preambleBitmap, sizeof(WMX_PREAMBLES));
	}

	// Performs direct scan (Only the first duplex mode is passed...).
	wmxStatus = wmx_CmdUserStartScanDirect(pList, &(pChannels->duplexMode), listSize, isBlocking);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "CmdNetworkSearchDirect(OUT). ERROR - wmx_CmdUserStartScanDirect returned-%s", wmxGetStatusStr(wmxStatus));
	} 

	free(pList);
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "CmdNetworkSearchDirect(OUT). Returned-%s", wmxGetStatusStr(wmxStatus));
	return WmxStatusToWimaxAPIRet(wmxStatus);
}

WIMAX_API_RET WIMAX_API SetCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P	pDeviceId,  
													UINT32					*pCurrentPreferredNspIDs, 
													UINT32					listSize)
{	
	WIMAX_API_RET	wmxRet = WIMAX_API_RET_SUCCESS;	
	UINT32			tmpUseOnlyOne = 0;
	wmx_Status_t	status;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetCurrentPreferredProfile(IN)");

	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, TRUE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		goto Finalize;
	}

	if (NULL == pCurrentPreferredNspIDs &&	listSize > 0)
	{
		wmxRet = WIMAX_API_RET_INVALID_PARAMETER;
		goto Finalize;
	}

	if (listSize > 0)
	{
		tmpUseOnlyOne = 1;
	}

	//setting the current preferred NSP	
	status = wmx_SetCurrentPreferredNSP(listSize, (wmx_pNSPid_t)&pCurrentPreferredNspIDs[0]);
	if( status != WMX_ST_OK )
	{		
		wmxRet =   WmxStatusToWimaxAPIRet(status);
		goto Finalize;
	}

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SetCurrentPreferredProfile(OUT) status= %d", wmxRet);
	return wmxRet;
}

WIMAX_API_RET WIMAX_API GetCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P		pDeviceId,  
													WIMAX_API_PROFILE_INFO_P	pCurrentPreferredNSPs, 
													UINT32						*listSize)
{	
	wmx_NSP_t currentPreferredNsp;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;	
	wmx_Status_t status;
	UINT32 numOfCurrentPreferredNsps;
	int nspNameConv;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetCurrentPreferredProfile(IN)");
	
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		goto Finalize;
	}

	if (NULL == pCurrentPreferredNSPs ||
		*listSize < 1)
	{
		wmxRet = WIMAX_API_RET_INVALID_PARAMETER;
		goto Finalize;
	}

	//getting the current preferred NSP	
	status = wmx_GetCurrentPreferredNSP(&currentPreferredNsp, &numOfCurrentPreferredNsps);
	if( status != WMX_ST_OK )
	{		
		wmxRet =   WmxStatusToWimaxAPIRet(status);
		goto Finalize;
	}	
	
	if (numOfCurrentPreferredNsps > 0)
	{			
		pCurrentPreferredNSPs->profileID = currentPreferredNsp.nspIDs[0];
		nspNameConv = OSAL_CAPI_MultiByteToWideChar(CP_UTF8, 0, currentPreferredNsp.nspName, (int)OSAL_strnlen(currentPreferredNsp.nspName, WMX_NSP_NAME_MAX_SIZE)+1, pCurrentPreferredNSPs->profileName, sizeof(pCurrentPreferredNSPs->profileName)/sizeof(pCurrentPreferredNSPs->profileName[0]));			
		if( nspNameConv == 0 )
		{
			TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Failed to convert nspName to WideChar");
			return WIMAX_API_RET_FAILED;
		}
		pCurrentPreferredNSPs->structureSize = sizeof(*pCurrentPreferredNSPs);	
	}
	*listSize = numOfCurrentPreferredNsps; // The API currently supports only one current preferred NSP

Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetCurrentPreferredProfile(OUT) status= %d", wmxRet);
	return wmxRet;
}

WIMAX_API_RET WIMAX_API SubscribeRfTaken (WIMAX_API_DEVICE_ID_P pDeviceId, IndRfTaken pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeRfTaken(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (rfTakenCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback allready registered");
		return WIMAX_API_RET_FAILED;
	}	

	rfTakenCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeRfTaken(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API UnsubscribeRfTaken (WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeRfTaken(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	rfTakenCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribeRfTaken(IN)");
	return WIMAX_API_RET_SUCCESS;
}


WIMAX_API_RET WIMAX_API SubscribePNMNotification (WIMAX_API_DEVICE_ID_P pDeviceId, IndPNMNotification pCallbackFnc)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribePNMNotification(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	//check that the pointer to function is NULL
	if (PNMNotificationCB != NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "Callback already registered");
		return WIMAX_API_RET_FAILED;
	}	

	PNMNotificationCB = pCallbackFnc;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "SubscribeRfTaken(OUT)");
	return WIMAX_API_RET_SUCCESS;
}
WIMAX_API_RET WIMAX_API UnsubscribePNMNotification (WIMAX_API_DEVICE_ID_P pDeviceId)
{
	WIMAX_API_RET wmxRet;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePNMNotification(IN)");
	//check that in pointers are valid
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, FALSE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "No permissions");
		return wmxRet;
	}

	PNMNotificationCB = NULL;

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "UnsubscribePNMNotification(IN)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API GetWMFComplianceVersion(WIMAX_API_WMF_COMPLIANCE_VERSION_P outWMFComplianceVersion)
{
	wmx_Status_t wmxStatus;
	char WMFComplianceVersion[MAX_SIZE_OF_STRING_BUFFER];
	
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetWMFComplianceVersion(IN)");

	if (outWMFComplianceVersion == NULL)
	{
		return WIMAX_API_RET_INVALID_PARAMETER;
	}
	OSAL_CAPI_strcpy_s(outWMFComplianceVersion->version, MAX_SIZE_OF_STRING_BUFFER, TEXT(""));

	wmxStatus = wmx_GetWMFComplianceVersion(WMFComplianceVersion, MAX_SIZE_OF_STRING_BUFFER);
	if (wmxStatus != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "GetWMFComplianceVersion(OUT). ERROR wmx_GetWMFComplianceVersion- ret val=%s", wmxGetStatusStr(wmxStatus));
		return WmxStatusToWimaxAPIRet(wmxStatus);
	}

	OSAL_CAPI_MultiByteToWideChar(CP_ACP, 0, WMFComplianceVersion, (int)OSAL_strnlen(WMFComplianceVersion, MAX_SIZE_OF_STRING_BUFFER)+1, outWMFComplianceVersion->version, sizeof(outWMFComplianceVersion->version)/sizeof(outWMFComplianceVersion->version[0]));	
	outWMFComplianceVersion->structureSize = sizeof(*outWMFComplianceVersion);
	

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetWMFComplianceVersion(OUT)");
	return WIMAX_API_RET_SUCCESS;
}

WIMAX_API_RET WIMAX_API GetNonce(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NONCE_BLOB_P pNonce, UINT32 *pNonceSize)
{

	wmx_Status_t wmxStatus = WMX_ST_FAIL;
	WIMAX_API_RET wmxRet = WIMAX_API_RET_SUCCESS;		

	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNonce(IN)");
	//check that in pointers are valid
	if (pNonceSize == NULL)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "pNonceSize == NULL");
		wmxRet = WIMAX_API_RET_INVALID_PARAMETER;
		*pNonceSize = 0;
		goto Finalize;
	}
	wmxRet = CheckParamsAndPermissions(pDeviceId, FALSE, TRUE);
	if (wmxRet != WIMAX_API_RET_SUCCESS)
	{
		goto Finalize;
	}

	wmxStatus = wmx_GetNonce(pNonce, pNonceSize);
	if (wmxStatus != WMX_ST_OK)
	{
		wmxRet = WmxStatusToWimaxAPIRet(wmxStatus);
		goto Finalize;
	}		



Finalize:
	TRACE(TR_MOD_COMMON_API, TR_SEV_NOTICE, "GetNonce(OUT). ret val=%s",wmxGetStatusStr(wmxStatus));
	return wmxRet;
}
