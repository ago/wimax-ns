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
#include "WrappersUtils.h"

// Declarations
void InitParams();

//
LONG nds_numOfInits = 0; 


//////////////////////////////////////////////////////////////////////
// L5 Layer

// Connection Parameters
L5_CONNECTION nds_wrapper_l5ConnID = NULL;
tL5DispatcherFunctions *nds_wrapper_pFuncs = NULL;
tUtilityFunctions *nds_wrapper_UtilFuncs = NULL;


//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// plastic 
// not needed when the SDK is in the appsrv (not initialized when using wmxNds_InitAgent)
OSAL_critical_section g_plasticRWLock;

// data 
wmx_UserScanStatus_t g_userScanStatus = UserScanStopped;
// Setter and Getter
wmx_UserScanStatus_t GetCurrentUserScanStatus()
{
	return g_userScanStatus;
}
void SetCurrentUserScanStatus(wmx_UserScanStatus_t userScanStatus)
{	
	g_userScanStatus = userScanStatus;
}

BOOL g_userScanStarted = FALSE;
// Setter and Getter
BOOL GetCurrentUserScanStarted()
{
	return g_userScanStarted;
}
void SetCurrentUserScanStarted(BOOL userScanStarted)
{	
	g_userScanStarted = userScanStarted;
}

wmx_UserConnectStatus_t g_userConnectStatus = UserConnectSuccessful;
// Setter and Getter
wmx_UserConnectStatus_t GetCurrentUserConnectStatus()
{
	return g_userConnectStatus;
}
void SetCurrentUserConnectStatus(wmx_UserConnectStatus_t userConnectStatus)
{	
	g_userConnectStatus = userConnectStatus;
}

BOOL g_userConnectStarted = FALSE;
// Setter and Getter
BOOL GetCurrentUserSConnectStarted()
{
	return g_userConnectStarted;
}
void SetCurrentUserConnectStarted(BOOL userConnectStarted)
{	
	g_userConnectStarted = userConnectStarted;
}

BOOL IsConnectStarted()
{
	return g_ConnectStarted;
}

void SetConnectStarted(BOOL started)
{
	g_ConnectStarted = started;
}

// Synchronizing events
OSAL_event_t g_userScanCompletedEvent = NULL;
OSAL_event_t g_userConnectCompletedEvent = NULL;

// cbs
wmx_pIndProvisioningOperationCB_t IndProvisioningOperationCB = NULL;
wmx_pIndPackageUpdateCB_t IndPackageUpdateCB = NULL;
wmx_pIndPackageDownloadProgressCB_t IndPackageDownloadProgressCB = NULL;
//wmx_pUserAPDOStatusUpdateCB_t UserAPDOStatusUpdateCB = NULL;
wmx_pUserSystemStateUpdateCB_t UserSystemStateUpdateCB = NULL;
wmx_pUserScanCompletedCB_t UserScanCompletedCB = NULL;
wmx_pUserScanUpdateCB_t UserScanUpdateCB = NULL;
wmx_pUserMediaStatusCB_t UserMediaStatusCB;
wmx_pMediaStatusCB_t MediaStatusCB;

wmx_pSystemStateUpdateCB_t SystemStateUpdateCBs[SYSTEM_STATE_MAX_CALLBACKS];
int SystemStateUpdateCBs_Count = 0;

wmx_pConnectionStateUpdateCB_t ConnectionStateUpdateCB = NULL;
wmx_pScanUpdateCB_t ScanUpdateCB = NULL;
wmx_pBsInfoUpdateCB_t BsInfoUpdateCB = NULL;
wmx_pRecentBSsCB_t RecentBSsCB = NULL;
wmx_pSIIUpdateCB_t SIIUpdateCB = NULL;
wmx_pCoexUpdateCB_t CoexistenceModeCB = NULL;
wmx_pIndDeviceStatusUpdateCB_t DeviceStatusUpdateCB = NULL;
wmx_pIndPermissionsUpdateCB_t PermissionsUpdateCB=NULL;
wmx_pBekBufferCB_t BekBufferCB = NULL;
wmx_pIndCurrentPreferredProfileCB_t IndCurrentPreferredProfileCB;
wmx_pIndConnectionModeUpdateCB_t ConnectionModeUpdateCB;
wmx_pIndFastReconnectStatusUpdateCB_t FastReconnectStatusUpdateCB;
wmx_pIndRoamingModeUpdateCB_t RoamingModeUpdateCB;
wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t ConnectedAsCurrentPreferredCapabilityStatusCB;
wmx_pRfTakenCB_t RfTakenCB = NULL;
wmx_pIndDevicePNMNotificationCB_t IndDevicePNMNotificationCB = NULL;


BOOL g_ConnectStarted;
UINT32 connectTime;

//////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////
// Silver 
OSAL_critical_section g_silverRWLock; //  use only in getters and setters!!!

//////////////////////////////////////////////////////////////////////
// data
wmx_SystemState_t g_ndsWrapper_systemState;
wmx_MediaStatus_t g_ndsWrapper_mediaStatus;

wmx_MediaStatus_t GetCurrentMediaStatus()
{
	return g_ndsWrapper_mediaStatus;
}

void SetCurrentMediaStatus(wmx_MediaStatus_t mediaStatus)
{
	g_ndsWrapper_mediaStatus = mediaStatus;
}

// Getter and setter
wmx_SystemState_t GetCurrentSystemState()
{
	return g_ndsWrapper_systemState;
}

void SetCurrentSystemState(wmx_SystemState_t systemState)
{
	g_ndsWrapper_systemState = systemState;

	// Init the local params when we are in Initialized state
	if (systemState == Initialized)
	{
		InitParams();
	}
}

//////////////////////////////////////////////////////////////////////

void InitParams()
{
	g_numOfStateReportRegs = 0;
	g_numOfScanReportRegs = 0;
	g_numOfBsInfoReportRegs = 0;
	g_numOfRecentBSsReportRegs = 0;
	g_numOfSIIReportRegs = 0;	
	g_numOfCurrentPreferredIndRegs = 0;
	g_numOfMediaStatusIndRegs = 0;
	g_numOfScanCompletedIndRegs = 0;
	g_numOfConnectCompletedIndRegs = 0;
	g_numOfScanUpdateIndRegs = 0;
	g_numOfSystemStateUpdateIndRegs = 0;
	g_numOfUserAPDOStatusUpdateIndRegs = 0;
	g_coexistenceUpdateIndRegs = 0;
	g_numOfProvisioningOperationIndRegs = 0;
	g_numOfPackageUpdateIndRegs = 0;
	g_numOfDeviceStatusIndRegs = 0;
	g_numOfBEKStatusIndRegs = 0;
	nds_numOfInits = 0;
	g_ConnectStarted = FALSE;
	g_connectionModeUpdateIndRegs = 0;
	g_fastReconnectStatusUpdateIndRegs = 0;
	g_roamingModeUpdateIndRegs = 0;
	g_connectedAsCurrentPreferredCapabilityStatusIndRegs = 0;
	g_rfTakenIndRegs = 0;
	g_PNMTakenIndRegs = 0;
}

// driver reports registration counters
LONG g_numOfStateReportRegs = 0;
LONG g_numOfScanReportRegs = 0;
LONG g_numOfBsInfoReportRegs = 0;
LONG g_numOfRecentBSsReportRegs = 0;
LONG g_numOfSIIReportRegs = 0;
// agent indications registration counters
LONG g_numOfCurrentPreferredIndRegs = 0;
LONG g_numOfMediaStatusIndRegs;
LONG g_numOfScanCompletedIndRegs = 0;
LONG g_numOfConnectCompletedIndRegs = 0;
LONG g_numOfScanUpdateIndRegs = 0;
LONG g_numOfSystemStateUpdateIndRegs = 0;
LONG g_numOfUserAPDOStatusUpdateIndRegs = 0;
LONG g_coexistenceUpdateIndRegs = 0;
LONG g_numOfProvisioningOperationIndRegs = 0;
LONG g_numOfPackageUpdateIndRegs = 0;
LONG g_numOfPackageDownloadProgressIndRegs = 0;
LONG g_numOfDeviceStatusIndRegs = 0;
LONG g_numOfBEKStatusIndRegs = 0;
LONG g_connectionModeUpdateIndRegs = 0;
LONG g_fastReconnectStatusUpdateIndRegs = 0;
LONG g_roamingModeUpdateIndRegs = 0;
LONG g_connectedAsCurrentPreferredCapabilityStatusIndRegs = 0;
LONG g_rfTakenIndRegs = 0;
LONG g_PNMTakenIndRegs = 0;

