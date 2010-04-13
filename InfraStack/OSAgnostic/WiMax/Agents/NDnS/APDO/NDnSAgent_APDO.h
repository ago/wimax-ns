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
#ifndef _NDNS_AGENT_APDO_H
#define _NDNS_AGENT_APDO_H   
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Sup_4.h"

#include "wmxSDK_Apdo_Internals.h"

#include "NDnSAgent_DB_if.h"
#include "Act.h"


// Callback Functions to Gold Wrapper
wmx_Status_t NDnSAgent_SetPackageUpdateStatus(wmx_PackageUpdateState_t updateStatus);

void NDnSAgent_AlertNotification(wmxApdo_pFunctionParamStruct alertNotificationStruct);
void NDnSAgent_ProvisioningOperation(wmx_ProvisioningOperation_t provisioningOperation, UINT16 contactType);
void NDnSAgent_PackageUpdate(wmx_PackageUpdateStatus_t packageUpdateStatus);
void NDnSAgent_HandleSystemStateUpdate(wmx_SystemState_t systemState, wmx_SystemState_t previousSystemState);
void NDnSAgent_PackageDownloadProgress( wmx_PackageDownloadProgressInfo_t packageUpdateInfo );
void HandleFumoUpdate(wmx_FUMOUpdateContent_t fumoUpdateContent);
extern OSAL_thread_t LinkUpThreadHandle;
wmx_Status_t APDOSetPackagePath(void *buffer, UINT32 *bufferSize);
wmx_Status_t SetPackageUpdateStatus(void *buffer, UINT32 bufferSize);
wmx_Status_t NDnSAgent_ApdoSetPackageUpdateState(wmx_PackageUpdateState_t updateStatus);

wmx_Status_t GetPackageInfo(void *buffer, UINT32 *bufferSize);
wmx_Status_t GetAPDOinfo(void *buffer, UINT32 *resultBufferSize, void *resultBuffer);
wmx_Status_t AddAPDOinfo(void *buffer, UINT32 *bufferSize);
wmx_Status_t UpdateAPDOinfo(void *buffer, UINT32 *bufferSize);
wmx_Status_t DeleteAPDOinfo(void *buffer, UINT32 *bufferSize);
wmx_Status_t ExecuteAPDOinfo(void *buffer, UINT32 *bufferSize);
wmx_Status_t GetNSPContactInfoByName(char* nspName, void *buffer, UINT32 *bufferSize);
wmx_Status_t GetContactInfo(wmx_NSPid_t nspId, void *buffer, UINT32 *bufferSize);
wmx_Status_t RestoreBckProvisioningDB();
wmx_Status_t RestoreFactorySettings();
wmx_Status_t GetProvisionedNspIDs(UINT32 *bufferSize, wmx_pNSPid_t pNspIDs);
wmx_Status_t GetUnprovisionedNspIDs(UINT32 *bufferSize, wmx_pNSPid_t pNspIDs);
void HandleApdoSessionStatus(wmx_ApdoSessionStatus_t sessionStatus);

wmx_Status_t SetServiceProviderUnlock(void *buffer, UINT32 bufferSize);
wmx_Status_t GetServiceProviderLockStatus(void *buffer, UINT32 *bufferSize);

wmx_Status_t GetBEK(wmx_pBEKBuffer_t pBEK);
wmx_Status_t SetBEK(wmx_pBEKBuffer_t pBEK);

void NDnSAgent_ApdoDeleteDMAccountInd( char* accountName );
wmx_Status_t GetApdoLinkStatus(void *buffer, UINT32 *resultBufferSize, void *resultBuffer);
wmx_Status_t GetApdoOperatorsConfigurations(wmx_pApdoOperatorConfigurations_t pConfigurations);
wmx_Status_t GetConnectedNSPForAPDO(UINT32 *bufferLength, UINT8 *buffer);
wmx_Status_t GetHostName(CHAR *pHostNameBuf, UINT32 dwHostNameBufSize);
// There is a similar struct for internal NDNS usage - this struct should stay seperate since 
// it is reflected to the OMA Client side
typedef struct _wmx_ApdoLinkStatusParams_t
{
	wmx_ApdoLinkStatus_t linkStatus;
	wmx_NSPid_t nspId;
	char nspName[WMX_NSP_NAME_MAX_SIZE];
	char realm[WMX_NSP_REALM_MAX_SIZE];
	char toDMAcc[MAX_ACCOUNT_NAME_SIZE];
}wmx_ApdoLinkStatusParams_t, *wmx_pApdoLinkStatusParams_t;

#endif // _NDNS_AGENT_APDO_H