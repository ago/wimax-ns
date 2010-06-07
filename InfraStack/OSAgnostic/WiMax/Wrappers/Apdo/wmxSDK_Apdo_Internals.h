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
#ifndef _WMX_SDK_APDO_INTERNALS_H
#define _WMX_SDK_APDO_INTERNALS_H

#include "wmxSDK_Apdo_3.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Nds_InternalStructs.h"
#include "L5Common.h"
#include "NDnSAgent_DB_if.h"
//for option 15
wmx_Status_t wmxApdo_SendNdsMsg( 
								UINT32 opcode, NDNS_AGENT_L5_OPCODE ndnsOpcode,
								UINT32 requestLength, UINT8 *request, 
								UINT32 *responseLength, UINT8 *response );

typedef enum _Apdo_InternalOpcodes
{
	// Plastic cbs	
	AGENT_APDO_LINK_STATUS,
	AGENT_APDO_ALERT_RESPONSE,
	AGENT_APDO_SESSION_STATUS,
	AGENT_APDO_OOB_NOTIFICATION,
	AGENT_APDO_FUMO_DOWNLOAD_APPROVAL_STATUS,
	AGENT_APDO_DELETE_DM_ACCOUNT
} Apdo_InternalOpcodes;

// Connection Parameters
extern L5_CONNECTION apdo_wrapper_l5ConnID;
extern tL5DispatcherFunctions *apdo_wrapper_pFuncs;
extern tUtilityFunctions *apdo_wrapper_UtilFuncs;
extern LONG apdo_numOfInits;

extern wmx_pApdoLinkStatusCB_t ApdoLinkStatusCB;
extern wmx_pApdoAlertResponseCB_t ApdoAlertResponseCB;
//extern wmx_pApdoOobNotificationCB_t ApdoOobNotificationCB;
extern wmx_pRefreshApdoSessionStatusCB_t RefreshApdoSessionStatusCB;
extern wmx_pApdoFumoDownloadApprovalStatusCB_t ApdoFumoDownloadApprovalStatusCB;
extern wmx_pApdoDeleteDMAccountCB_t ApdoDeleteDMAccountCB;

/// Internal Parameters
extern LONG g_numOfApdoLinkStatusIndRegs;
extern LONG g_numOfApdoSessionStatusIndRegs;
extern LONG g_numOfApdoOobNotificationIndRegs;
extern LONG g_numOfApdoAlertResponseIndRegs;
extern LONG g_numOfApdoFumoDownloadApprovalStatusIndRegs;
extern LONG g_numOfApdoDeleteDMAccountIndRegs;

typedef enum _wmxApdo_FunctionType_t
{
	APDO_ApdoSessionStatus = 0x1,
	APDO_AlertNotification,
	APDO_StoreProvisioningClientCfgDataBlobStruct,
	APDO_GetProvisioningClientCfgDataBlobStruct,
	APDO_ApdoLinkStatusCBStruct,
	APDO_FumoUpdate
} wmxApdo_FunctionType_t, *wmxApdo_pFunctionType_t;

// function parameters structs
typedef struct _wmx_ApdoSessionStatusStruct_t
{
	wmx_ApdoSessionStatus_t sessionStatus;	
} wmx_ApdoSessionStatusStruct_t, *wmx_pApdoSessionStatusStruct_t;

typedef struct _wmx_AlertNotificationStruct_t
{
	wmx_ApdoAlert_t alert;
	UINT8 alertContent[MAX_ALERT_CONTENT];
	BOOL useOnGoing;
} wmx_AlertNotificationStruct_t, *wmx_pAlertNotificationStruct_t;

typedef struct _wmx_StoreProvisioningClientCfgDataBlobStruct_t
{
	wmx_NSPid_t nspId;
	UINT8 cfgDataBlob[MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB];
} wmx_StoreProvisioningClientCfgDataBlobStruct_t, *wmx_pStoreProvisioningClientCfgDataBlobStruct_t;

typedef struct _wmx_GetProvisioningClientCfgDataBlobStruct_t
{
	wmx_NSPid_t nspId;
	UINT8 cfgDataBlob[MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB];
} wmx_GetProvisioningClientCfgDataBlobStruct_t, *wmx_pGetProvisioningClientCfgDataBlobStruct_t;

typedef struct _wmx_ApdoLinkStatusCBStruct_t
{
	wmx_ApdoLinkStatus_t linkStatus;
	wmx_NSPid_t nspId;
	wmx_ApdoActivationConnection_t activationConnection;
	char nspName[WMX_NSP_NAME_MAX_SIZE];
	char realm[WMX_NSP_REALM_MAX_SIZE];
	char toDmAcc[MAX_ACCOUNT_NAME_SIZE];
} wmx_ApdoLinkStatusCBStruct_t, *wmx_pApdoLinkStatusCBStruct_t;

typedef union _FunctionParamUnion  /* A definition and a declaration */
{
	wmx_ApdoSessionStatusStruct_t ApdoSessionStatusStruct;
	wmx_AlertNotificationStruct_t AlertNotificationStruct;
	wmx_StoreProvisioningClientCfgDataBlobStruct_t StoreProvisioningClientCfgDataBlobStruct;
    wmx_GetProvisioningClientCfgDataBlobStruct_t GetProvisioningClientCfgDataBlobStruct;
	wmx_ApdoLinkStatusCBStruct_t ApdoLinkStatusCBStruct;
	wmx_FUMOUpdateContent_t fumoUpdateContent;
} FunctionParamUnion;

typedef struct _wmxApdo_FunctionParamStruct
{
	wmxApdo_FunctionType_t FunctionType;
	FunctionParamUnion FuncParamUnion;
} wmxApdo_FunctionParamStruct, *wmxApdo_pFunctionParamStruct;

// Following binary data is for the simulated bootstrap 
// header "...j.-//SYNCML//DTD SyncML 1.1//ENmlq.1.2..r.DM/1.2"...
static UINT8 bootstrapHeader[] = {0x02, 0x00, 0x00, 0x6a, 0x1d, 0x2d, 0x2f, 0x2f, 
								0x53, 0x59, 0x4e, 0x43, 0x4d, 0x4c, 0x2f, 0x2f, 
								0x44, 0x54, 0x44, 0x20, 0x53, 0x79, 0x6e, 0x63, 
								0x4d, 0x4c, 0x20, 0x31, 0x2e, 0x31, 0x2f, 0x2f, 
								0x45, 0x4e, 0x6d, 0x6c, 0x71, 0x03, 0x31, 0x2e, 
								0x32, 0x00, 0x01, 0x72, 0x03, 0x44, 0x4d, 0x2f, 
								0x31, 0x2e, 0x32, 0x00, 0x01, 0x65, 0x03, 0x30, 
								0x00, 0x01, 0x5b, 0x03, 0x30, 0x00, 0x01, 0x6e, 
								0x57, 0x03};													
#define BOOTSTRAP_HEADER_SIZE 66
static UINT8 bootstrapDevIdSuffix[] = {0x00, 0x01, 0x01, 0x67, 0x57, 0x03};
#define BOOTSTRAP_DEV_ID_SUFFIX_SIZE 6
static UINT8 bootstrapServerUrlSuffix[] = {0x00, 0x01, 0x01, 0x01, 0x6b, 0x45, 0x4b, 0x03, 
							0x31, 0x00, 0x01, 0x54, 0x6e, 0x57, 0x03, 0x2e};
#define BOOTSTRAP_SERVER_URL_SUFFIX_SIZE 16	
#define DMACC_PATH "/DMAcc/"
#define DMACC_PATH_SIZE 7
static UINT8 bootstrapNodeDesc[] = {0x00, 0x01, 0x01, 0x5a, 0x00, 0x01, 0x47, 0x03, 
									0x6e, 0x6f, 0x64, 0x65, 0x00, 0x01, 0x01, 0x01, 
									0x00, 0x00, 0x54, 0x6e, 0x57, 0x03, 0x2e};
#define BOOTSTRAP_NODE_DESC_SIZE 23	
#define APP_ID_PATH "/AppID"
#define APP_ID_PATH_SIZE 6
static UINT8 bootstrapLeafPrefix[] = {0x00, 0x01, 0x01, 0x4f, 0x03};
#define BOOTSTRAP_LEAF_PREFIX_SIZE 5
static UINT8 bootstrapLeafSuffix[] = {0x00, 0x01, 0x01, 0x54, 0x6e, 0x57, 0x03, 0x2e};
#define BOOTSTRAP_LEAF_SUFFIX_SIZE 8
#define SERVER_ID_PATH "/ServerID"
#define SERVER_ID_PATH_SIZE 9
#define NAME_PATH "/Name"
#define NAME_PATH_SIZE 5
#define PREFCONREF_PATH "/PrefConRef"
#define PREFCONREF_PATH_SIZE 11
#define PREFCONREF_VAL "/ToConRef/0"
#define PREFCONREF_VAL_SIZE 11
#define TOCONREF_PATH "/ToConRef"
#define TOCONREF_PATH_SIZE 9


static UINT8 bootstrapEnd[] = {0x2f, 0x44, 0x4d, 0x41, 0x63, 0x63, 0x2f, 0x78, 0x6f, 0x68, 
							0x6d, 0x2f, 0x45, 0x78, 0x74, 0x00, 0x01, 0x01, 0x5a, 0x00, 
							0x01, 0x47, 0x03, 0x6e, 0x6f, 0x64, 0x65, 0x00, 0x01, 0x01, 
							0x01, 0x01, 0x00, 0x00, 0x12, 0x01, 0x01};
#define BOOTSTRAP_END_SIZE 37
#define BOOTSTRAP_HEADER_OFFSET 33

#define MAX_DEV_ID_SIZE	64
#define BOOTSTRAP_INFO_PATH "ApdoInternal/BootstrapInfo/"
#define SERVER_ID_TAG				"/ServerID"
#define SERVER_URL_TAG				"/ServerURL"
#define SERVER_USER_NAME_TAG		"/ServerUserName"
#define CLIENT_USER_NAME_TAG		"/ClientUserName"
#define PORT_NUM_TAG				"/PortNbr"

#endif // _WMX_SDK_APDO_INTERNALS_H
