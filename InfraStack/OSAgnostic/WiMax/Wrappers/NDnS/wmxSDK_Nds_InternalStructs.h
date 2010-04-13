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
#ifndef _WMX_SDK_NDS_INTERNAL_STRUCTS_H
#define _WMX_SDK_NDS_INTERNAL_STRUCTS_H

#include "wimax_osal_services_cmn.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_3.h"


// This header file contains realtions structs

// Constant definitions
#define MAX_EAP_METHOD_SIZE 32
#define MAX_EAP_PASSWORD_SIZE OSAL_EAP_PASSWORD_SIZE
#define MAX_CERT_FILE_NAME_SIZE 50


typedef struct _wmx_ScanResults_t
{	
	UINT32 NAPsCount;
	UINT32 currentNapIndex;
	BOOL isCycleComplete;
	wmx_ScanStatus_t scanStatus;
	wmx_NAP_t NAPs[WMX_NAPS_MAX_NUM];
} wmx_ScanResults_t, *wmx_pScanResults_t;


typedef enum _wmx_AgingStatus_t
{
	AgingStatus_New = 0x1,
	AgingStatus_Old,
	AgingStatus_Remove
} wmx_AgingStatus_t, *wmx_pAgingStatus_t;

static char *wmx_AgingStatus_tStr[] = {
	"New",
	"Old",
	"Remove (filtered)"
};

// TODO: Oran - check if a similar enum has already been defined
typedef enum _wmx_ConnectType_t
{
	ConnectReason_Home = 0x1,
	ConnectReason_Roam,
	ConnectReason_Activation
} wmx_ConnectType_t, *wmx_pConnectType_t;

typedef struct _wmx_AvailableNSP_t
{ 
	UINT32 detectionTime;
	wmx_AgingStatus_t agingStatus;
	UINT32 preferredListIndex;
	wmx_NSPid_t nspId;
	wmx_BSid_t bsId;
	wmx_BsIdType_t bsIdType;
	wmx_LinkQuality_t	linkQuality;
	wmx_SignalStrength_t bestRssi;
	wmx_SignalStrength_t bestCINR;
	wmx_ConnectType_t connectType;
} wmx_AvailableNSP_t, *wmx_pAvailableNSP_t;

typedef struct _wmx_AvailableNSPsList_t
{ 
	OSAL_critical_section criticalSection;
	UINT32 numOfAvailableNSPs;
	wmx_AvailableNSP_t availableNSPs[WMX_NSP_IDS_MAX_NUM];
} wmx_AvailableNSPsList_t, * wmx_pAvailableNSPsList_t;

typedef enum _wmx_EapType_t
{
	WMX_EAP_TLS = 13,
	WMX_EAP_TTLS = 21,
	WMX_EAP_AKA = 23,
	WMX_PLAIN_MSCHAPv2 = 256,
	WMX_EAP_MSCHAPv2 = 1000,
	WMX_CHAP = 7
} wmx_EapType_t, *wmx_pEapType_t;

/// <summary>
/// Struct that relate subscriber to credentials. In order to relate a subscriber to a NSP use wmx_NSP_t.
/// </summary>
//typedef struct _wmx_Credentials_t
//{
//	char EAPMethod[MAX_EAP_METHOD_SIZE];
//	char RootCert[MAX_CERT_FILE_NAME_SIZE];
//	char ClientCert[MAX_CERT_FILE_NAME_SIZE];
//	char PrivateKey[MAX_CERT_FILE_NAME_SIZE];
//	char Identity[WMX_SUBSCRIBER_ID_MAX_SIZE];
//	char OuterIdentity[WMX_SUBSCRIBER_ID_MAX_SIZE];
//	char Phase2Method[MAX_EAP_METHOD_SIZE];
//	char Password[MAX_EAP_PASSWORD_SIZE];
//	wmx_pSubscriberInfo_t pSubscriberInfo;	
//} wmx_Credentials_t, *wmx_pCredentials_t;


/// <summary>
/// Struct that holds an NSP struct and relations to NAPs and ChannelInfos.
/// </summary>
//typedef struct _wmx_NSPFullData_t
//{	
//	wmx_NSP_t nsp;	
//	BOOL		      fIsAllocated;
//	wmx_NSPServerId_t serverId;
//	wmx_NAP_t naps[WMX_NAPS_MAX_NUM];
//	ChannelInfo_t channelPlan[WMX_CHANNELS_MAX_NUM];
//	wmx_Credentials_t subscribersCredentials[WMX_NSP_SUBSCRIBERS_MAX_NUM];
//} wmx_NSPFullData_t, *wmx_pNSPFullData_t;

// Structs for internal use
typedef struct _wmx_UserSystemStateUpdate
{	
	wmx_StateReason_t			ReportStateReason;	
	wmx_SystemState_t			SystemState;	
	wmx_UserLinkStatus_t		UserLinkStatus;
	wmx_MediaStatus_t			MediaStatus;	
	wmx_ConnectProgressInfo_t	ConnectProgress;	
	wmx_RfSwitchesStatus_t		RfSwitchesStatus;	
} wmx_UserSystemStateUpdate, *wmx_pUserSystemStateUpdate;

//typedef struct _wmx_UserAPDOStatusUpdate
//{	
//	wmx_NSPid_t				nspID;
//	wmx_APDOStatus_t 		apdoStatus;
//	wmx_APDOStatusDetail_t	apdoStatusDetail;
//	wmx_APDOContactInfo_t	apdoContactInfo;
//} wmx_UserAPDOStatusUpdate, *wmx_pUserAPDOStatusUpdate;

#endif // _WMX_SDK_NDS_INTERNAL_STRUCTS_H