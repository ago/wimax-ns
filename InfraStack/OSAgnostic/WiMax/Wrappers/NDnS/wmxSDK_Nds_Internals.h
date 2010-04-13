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
#ifndef _WMX_SDK_NDS_INTERNALS_H
#define _WMX_SDK_NDS_INTERNALS_H


#include "wmxSDK_Nds_Cmn.h"

#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_InternalStructs.h"
#include "wmxSDK_Coex_3.h"
#include "wmxSDK_Coex_1.h"	// @@@ : JSS : Case sensitive file name
#include "L5Common.h"


#if defined(USE_16G)
	#define _16G_ON 1
#else
	#define _16G_ON 0
#endif

#define SYSTEM_STATE_MAX_CALLBACKS	5

typedef enum _InternalOpcodes
{
	// Plastic cbs	
	AGENT_SCAN_UPDATE,
	AGENT_SCAN_COMPLETED,	
	AGENT_CONNECT_COMPLETED,	
	AGENT_SYSTEM_STATE_UPDATE,
//	AGENT_APDO_STATUS_ARRIVED,
	AGENT_PROVISIONING_OPERATION,
	AGENT_PACKAGE_UPDATE,
	AGENT_PACKAGE_DOWNLOAD_PROGRESS,
	AGENT_ALERT_NOTIFICATION,
	CONNECTION_STATE_UPDATE,
	AGENT_COEX_UPDATE,
	AGENT_DEVICE_STATUS_UPDATE,
	AGENT_CURRENT_PREFERRED_NSP,
	AGENT_CONNECTION_MODE_UPDATE,
	AGENT_ROAMING_MODE_UPDATE,
	AGENT_FAST_RECONNECT_MODE_UPDATE,
	AGENT_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE,
	AGENT_RF_TAKEN,
	AGENT_PNM_NOTIFICATION,
	AGENT_MEDIA_STATUS,

	// Gold cbs
	DRIVER_SYSTEM_STATE_UPDATE,
	DRIVER_SCAN_UPDATE,
	DRIVER_SCAN_COMPLETED,
	DRIVER_CONNECT_COMPLETED,
	DRIVER_BSINFO_UPDATE,
	DRIVER_RECENT_BS_REPORT,
	DRIVER_SII_UPDATE,
	DRIVER_BEK_REPORT,
	DRIVER_MEDIA_STATUS
} InternalOpcodes;

typedef struct _wmx_ConnectParams
{
	wmx_NSPid_t nspID;
	wmx_ConnectionType_t connectionType;
	wmx_NSPid_t homeNSPToRoamTo;
	wmx_UserCredentials_t userCredentials;
} wmx_ConnectParams, *wmx_pConnectParams;

typedef struct _wmx_SetMSChapParams
{
	wmx_NSPid_t nspId;
	char username[WMX_SUBSCRIBER_ID_MAX_SIZE]; 
	char password[MAX_EAP_PASSWORD_SIZE];
} wmx_SetMSChapParams, *wmx_pSetMSChapParams;

typedef struct _wmx_ContactInfoParams
{
	char nspName[MAX_SIZE_OF_NSP_NAME];
} wmx_ContactInfoParams, *wmx_pContactInfoParams;

//
extern LONG nds_numOfInits; 


//////////////////////////////////////////////////////////////////////
// L5 Layer

// Connection Parameters
extern L5_CONNECTION nds_wrapper_l5ConnID;
extern tL5DispatcherFunctions *nds_wrapper_pFuncs;
extern tUtilityFunctions *nds_wrapper_UtilFuncs;
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// plastic 
// not needed when the SDK is in the appsrv (not initialized when using wmxNds_InitAgent)
extern OSAL_critical_section g_plasticRWLock;

// Synchronizing events
extern OSAL_event_t g_userScanCompletedEvent;
extern OSAL_event_t g_userConnectCompletedEvent;

// cbs
extern wmx_pSystemStateUpdateCB_t SystemStateUpdateCBs[SYSTEM_STATE_MAX_CALLBACKS];
extern int SystemStateUpdateCBs_Count;

extern wmx_pConnectionStateUpdateCB_t ConnectionStateUpdateCB;
extern wmx_pIndProvisioningOperationCB_t IndProvisioningOperationCB;
extern wmx_pUserSystemStateUpdateCB_t UserSystemStateUpdateCB;
extern wmx_pIndDeviceStatusUpdateCB_t DeviceStatusUpdateCB;
extern wmx_pIndPermissionsUpdateCB_t PermissionsUpdateCB;
extern wmx_pUserScanCompletedCB_t UserScanCompletedCB;
extern wmx_pUserScanUpdateCB_t UserScanUpdateCB;
extern wmx_pUserMediaStatusCB_t UserMediaStatusCB;
extern wmx_pMediaStatusCB_t MediaStatusCB;
extern wmx_pConnectionStateUpdateCB_t ConnectionStateUpdateCB;
extern wmx_pScanUpdateCB_t ScanUpdateCB;
extern wmx_pBsInfoUpdateCB_t BsInfoUpdateCB;
extern wmx_pRecentBSsCB_t RecentBSsCB;
extern wmx_pSIIUpdateCB_t SIIUpdateCB;
extern wmx_pCoexUpdateCB_t CoexistenceModeCB;
extern wmx_pIndPackageUpdateCB_t IndPackageUpdateCB;
extern wmx_pIndPackageDownloadProgressCB_t IndPackageDownloadProgressCB;
extern wmx_pBekBufferCB_t BekBufferCB;
extern wmx_pIndCurrentPreferredProfileCB_t IndCurrentPreferredProfileCB;
extern wmx_pIndConnectionModeUpdateCB_t ConnectionModeUpdateCB;
extern wmx_pIndFastReconnectStatusUpdateCB_t FastReconnectStatusUpdateCB;
extern wmx_pIndRoamingModeUpdateCB_t RoamingModeUpdateCB;
extern wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t ConnectedAsCurrentPreferredCapabilityStatusCB;
extern wmx_pRfTakenCB_t RfTakenCB;
extern wmx_pIndDevicePNMNotificationCB_t IndDevicePNMNotificationCB;
//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// Silver 
extern OSAL_critical_section g_silverRWLock;  // use only in getters and setters!!!

// Getter and setter
wmx_SystemState_t GetCurrentSystemState();
void SetCurrentSystemState(wmx_SystemState_t systemState);

wmx_MediaStatus_t GetCurrentMediaStatus();
void SetCurrentMediaStatus(wmx_MediaStatus_t mediaStatus);

wmx_UserScanStatus_t GetCurrentUserScanStatus();
void SetCurrentUserScanStatus(wmx_UserScanStatus_t userScanStatus);

BOOL GetCurrentUserScanStarted();
void SetCurrentUserScanStarted(BOOL userScanStarted);

wmx_UserConnectStatus_t GetCurrentUserConnectStatus();		// @@@ : JSS - Corrected return type (was wrong)
void SetCurrentUserConnectStatus(wmx_UserConnectStatus_t userConnectStatus);

BOOL GetCurrentUserConnectStarted();
void SetCurrentUserConnectStarted(BOOL userConnectStarted);

BOOL IsConnectStarted();
void SetConnectStarted(BOOL started);

//////////////////////////////////////////////////////////////////////


// driver reports registration counters
extern LONG g_numOfStateReportRegs;
extern LONG g_numOfScanReportRegs;
extern LONG g_numOfBsInfoReportRegs;
extern LONG g_numOfBEKStatusIndRegs;
extern LONG g_numOfSIIReportRegs;
extern LONG g_numOfRecentBSsReportRegs;
// agent indications registration counters
extern LONG g_numOfCurrentPreferredIndRegs;
extern LONG g_numOfMediaStatusIndRegs;
extern LONG g_numOfScanCompletedIndRegs;
extern LONG g_numOfConnectCompletedIndRegs;
extern LONG g_numOfScanUpdateIndRegs;
extern LONG g_numOfSystemStateUpdateIndRegs;
extern LONG g_numOfUserAPDOStatusUpdateIndRegs;
extern LONG g_numOfProvisioningOperationIndRegs;
extern LONG g_numOfPackageUpdateIndRegs;
extern LONG g_numOfPackageDownloadProgressIndRegs;
extern LONG g_coexistenceUpdateIndRegs;
extern LONG g_numOfDeviceStatusIndRegs;
extern BOOL g_ConnectStarted;
extern UINT32 connectTime;			
extern LONG g_connectionModeUpdateIndRegs;
extern LONG g_fastReconnectStatusUpdateIndRegs;
extern LONG g_roamingModeUpdateIndRegs;
extern LONG g_connectedAsCurrentPreferredCapabilityStatusIndRegs;
extern LONG g_rfTakenIndRegs;
extern LONG g_PNMTakenIndRegs;

#endif // _WMX_SDK_NDS_INTERNALS_H