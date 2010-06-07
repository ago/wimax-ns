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
#ifndef _NDNS_AGENT_INTERNALS_H
#define _NDNS_AGENT_INTERNALS_H

#include "FormatConversions.h"
#include "wmxSDK_Coex_1.h"
#include "L5Common.h"

#include "IndicatorsSubscribers.h"
#include "TraceModule.h"
#include "wmxSDK_Apdo_Cmn.h"

#include "wmxSDK_Nds_InternalStructs.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_3.h"

#include "NDnS_TinyFSM.h"
#include "L5Dispatcher.h"

#include "L4DmMonitorGroups.h"
#include "L4DnDHandler.h"

#define NDNS_STR_MANUAL		"Manual"
#define NDNS_STR_AUTOMATIC	"Automatic"
#define NDNS_STR_DELAYED	"Delayed"
#define NDNS_STR_EMPTY		""
#define NDNS_STR_NOT		"NOT"

#define FUMO_UPDATE_PATH_SUFFIX "/Update"
#define FUMO_DOWNLOAD_PATH_SUFFIX "/Download"
#define FUMO_DOWNLOAD_AND_UPDATE_PATH_SUFFIX "/DownloadAndUpdate"
#define FUMO_STATE_PATH_SUFFIX "/State"
#define FUMO_PACKAGE_PATH_PATH "/FUMOInternal/PkgPath"
#define FUMO_PACKAGE_NAME_PATH "/FUMOInternal/PkgName"
#define FUMO_NODE_PATH_PATH "/FUMOInternal/FumoNodePath"
#define FUMO_OPERATION "/FUMOInternal/FumoOperation"

#define CONTACTS_TRIGGER_0_PATH "Contacts/0/Trigger"
#define CONTACTS_TRIGGER_1_PATH "Contacts/1/Trigger"

#define L4C_TIMEOUT	5000
#define MAX_NAME_STR_LEN 128
#define INFINITE_LINK_LOSS_RATIO 3.5
#define EAP_NUM_RETRIES 3

// The following are constant definitions for the MSCHAPv2 according to OTA standard
#define EAP_MSCHAPV2_VENDOR_ID 24757
#define EAP_MSCHAPV2_VENDOR_TYPE 1

typedef enum _INTERNAL_NDNS_REQUESTS
{
	NDNS_CONNECT_NAP
} INTERNAL_NDNS_REQUESTS;

typedef enum _L4CState
{
	L4C_UNINITIALIZED = 0,
	L4C_RF_OFF,
	L4C_SINGLE_SCAN,
	L4C_AUTO_SCAN,
	L4C_CONNECTING,
	L4C_CONNECTED,
	L4C_DISCONNECTING,
	L4C_TRANSIENT // a special state that represents a "between states" state
} L4CState;

typedef enum _L4C_Task
{
	Task_StartScan,
	Task_StartManualScan,
	Task_Connect,
	Task_AutoConnect,
	Task_Reset,
	Task_StopScan,
	Task_SetConnectMode
} L4C_Task;

static char* L4C_TaskStr[] = {
	"Start Scan",	
	"Start Manual Scan",
	"Connect",
	"Auto Connect",
	"Reset",
	"Stop Scan",
	"Set Connect Mode"
};

typedef enum _L4C_ScanMode
{
	ScanMode_Auto,
	ScanMode_SemiManual,
	ScanMode_Manual
} L4C_ScanMode;

typedef enum _L4C_ConnectMode
{
	ConnectMode_Auto,
	ConnectMode_Manual
} L4C_ConnectMode;

typedef enum _L4C_LinkGrade
{
	LinkGrade_AboveThr = 0,
	LinkGrade_BelowThr
} L4C_LinkGrade;

// holds the info for a scheduled connect task
typedef struct _wmx_ConnectInfo_t
{
	wmx_NSPid_t nspIDs[WMX_NSP_IDS_MAX_NUM];
	UINT32 numOfNspIDs;
	wmx_CoexPriority_t coexPriority;
	BOOL forceManualConnect;
	BOOL useOnlyLastChannel;
} wmx_ConnectInfo_t, *wmx_pConnectInfo_t;

// holds the info for a scheduled manual scan task
typedef struct _wmx_ScanInfo_t
{
	wmx_ScanType_t manualScanType;	
	UINT32 chPlanSize;
	BOOL isInternal;
	BOOL isDirectScanBlocking;
	wmx_ChannelInfo_t chPlan[WMX_CHANNELS_MAX_NUM];
} wmx_ScanInfo_t, *wmx_pScanInfo_t;

// holds the info for a general scheduled task
typedef struct _wmx_ScheduledTaskData_t
{
	wmx_ConnectInfo_t connectInfo;
	wmx_ScanInfo_t scanInfo;
	wmx_UserConnectMode_t connectMode;
	wmx_Status_t status;
} wmx_ScheduledTaskData_t, *wmx_pScheduledTaskData_t;

typedef struct _wmx_EapContext_t
{	
	UINT32 numEapRetries;
	BOOL isStarted;
	BOOL isEapFail;
	BOOL isPerformedFallBack;
} wmx_EapContext_t, *wmx_pEapContext_t;

//#pragma pack( push, 1 )
typedef struct _wmx_NDnS_Context_t
{
	OSAL_critical_section lockSetMode;
	OSAL_critical_section lockSystemState;
	OSAL_critical_section linkUpCS;

	OSAL_event_t connectCompletedEvent; // = NULL //TODO: [Oran] remove - stop scan
	OSAL_event_t startManualScanCompletedEvent; //TODO: [Oran] remove - stop scan
	OSAL_event_t dualFlushOpEvent;
	OSAL_event_t disconnectCompletedEvent; // = NULL
	OSAL_event_t hScanStartedEvent;

	wmx_AvailableNSPsList_t availableNSPsList;

	LONG isResumeScan;
	long isScanProcessingRequired;
	long isSingleManualScan;
	List *indicatorSubscribersList;

	wmx_ConnectStatus_t connectStatus;
	int  DummyForCompilerHappy3;
	TinyFSM_t fsm;
	L4C_Task scheduledTask;
	wmx_ScheduledTaskData_t scheduledTaskData;	
	wmx_Status_t scanStatus;
	wmx_LinkLossType_t linkLossType;
	wmx_ScanType_t currentScanType;

	// for setting configuration
	BOOL isScanParametersSet; // = FALSE
	BOOL isSupplicantStarted; // = FALSE
	// for synchronization
	BOOL disconnectStarted; // = FALSE
		
	BOOL connectStarted; // = FALSE
	BOOL processStarted;
	
	// Global system state
	wmx_SystemState_t systemState; // = UnInitialized
	wmx_NSPid_t tempConnectingNspId;
	wmx_NAPid_t tempConnectingNapId;
	wmx_CoexPriority_t tempCoexPriority;

	wmx_EapContext_t eapContext;
	BOOL isDriverEventUp;

	BOOL isLinkUpThreadAlive; 

} wmx_NDnS_Context_t, *wmx_pNDnS_Context_t;
//#pragma pack( pop )

#define VALIDATE(x) { if (x == NULL) { return WMX_ST_CONFIG_ERROR; } }

// NAI defines	
#define PROVISIONING_NAI_DECORATION "{sm=1}"
#define ADDRESS_STR "@"
#define DEFAULT_REALM "wimax.com"


//************************************************
// Connection Parameters to L5 Layer
//************************************************
extern L5_CONNECTION nds_l5ConnID;
extern tL5DispatcherFunctions *nds_pFuncs;

//*******************************************
// Private Fields of the NDnS Agent
//*******************************************

// ND&S and L4C context
extern wmx_NDnS_Context_t g_ndnsContext;

// Holds the configuration state of the AppSrv, running with dSim or driver.
extern BOOL RunWithDSim;

//*******************************************
// Config Parameters
//*******************************************
extern wmx_THCriteria_t thCriteria;
extern UINT32 numOfChannelInfos;
extern wmx_pChannelInfo_t channelInfos;
extern UINT32 numOfBSCriteria;
extern wmx_pBSSelectionCriteria_t bsCriteriaList;

extern UINT32 connectTime;

extern BOOL provisioningStarted;
extern BOOL lastConnectedState;

void Ndns_SetConnectingNSPTemp(wmx_NSPid_t nspId);
wmx_NSPid_t Ndns_GetConnectingNSPTemp();

// Add the napID if the connecting NSP wasn't changed. Change the NAP's location in the array if it exists.
// If a new NSP is used override the NAPs list.
void Ndns_SetConnectingNAPTemp(wmx_NAPid_t napId);
BOOL Ndns_GetConnectingNAPTemp(wmx_pNAPid_t napId);

void Ndns_SetProvisioningStarted(BOOL started);
BOOL Ndns_GetProvisioningStarted();

void Ndns_SetLastConnectedState(BOOL connectedState);
BOOL Ndns_GetLastConnectedState();

void l4db_CopyNapID(wmx_NAPid_t srcNapID, wmx_pNAPid_t pDstNapID);

#endif //_NDNS_AGENT_INTERNALS_Hchar