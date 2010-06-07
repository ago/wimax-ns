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
#ifndef _NDNS_AGENT_H
#define _NDNS_AGENT_H


#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Sup_4.h"
#include "wmxSDK_Coex_1.h"
#include "Act.h"

#define NUMBER_OF_GENERATED_CHARS_FOR_PSEUDO_NAI 33
#define ILLEGAL_NSP_ID 0xcaffe

//Interface functions:
EXTERN_C EXPORT void NDnSAgent_Finalize();
EXTERN_C EXPORT BOOL NDnSAgent_Stop();
EXTERN_C EXPORT BOOL NDnSAgent_Start();
EXTERN_C EXPORT void L4Pub_CmdReset();
EXTERN_C EXPORT APPSRV_INIT_ST NDnSAgent_Initialize(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn);

APPSRV_INIT_ST NDnSAgent_Initialize();
void NDnSAgent_Shutdown();
wmx_Status_t NDnSAgent_GetDevCap(BOOL *buffer, UINT32 *bufferSize);
void NDnSAgent_MessagesHandler(	L5_CONNECTION Conn,
								L5_TARGET_ID nOriginID,

								UINT32 dwSentMessageID,
								void  *pvSentBuffer,
								UINT32 cbSentBufferSize,

								UINT32 *pdwResponseMessageID,
								void  *pvResponseBuffer,
								UINT32 *cbResponseBufferSize,

								void *pvUserContext,
								void *pvReserved );

wmx_Status_t NDnSAgent_RegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id);
wmx_Status_t NDnSAgent_UnRegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id);

wmx_Status_t NDnSAgent_StartScan();
wmx_Status_t NDnSAgent_StopScan();

wmx_Status_t NDnSAgent_StartConnect(wmx_NSPid_t nspID, wmx_CoexPriority_t coexPriority, BOOL forceManualConnect, BOOL useOnlyLastChannel);
wmx_Status_t NDnSAgent_Connect(wmx_ConnectParams connectParams, wmx_CoexPriority_t coexPriority, wmx_pUserConnectStatus_t pUserConnectStatus);
wmx_Status_t NDnSAgent_StartDisconnect();
wmx_Status_t NDnSAgent_Disconnect();

//wmx_Status_t L4C_UpdateData(L4C_DataType_t dataType, L4C_pDataUnion data);
wmx_Status_t L4C_UpdateScanStatus(BOOL isScanning);
wmx_Status_t L4C_ProcessScanResults(wmx_pScanResults_t scanResults);

wmx_Status_t NDnSAgent_SetConfigToSupplicant( wmx_NSPid_t nspID );

wmx_Status_t NDnSAgent_GetLastKnownNspIDs( UINT32 *bufferLength, UINT8 *buffer );
wmx_Status_t NDnSAgent_GetLinkStatus( UINT32 *bufferLength, UINT8 *buffer );
wmx_Status_t NDnSAgent_GetConnectedNSP( UINT32 *bufferLength, UINT8 *buf );
wmx_Status_t NDnSAgent_GetConnectedNSPEx( UINT32 *bufferLength, UINT8 *buffer, BOOL blockOnProvisioning );
wmx_Status_t SetConnectMode(wmx_pUserConnectMode_t pConnectMode, UINT32 bufferSize);
wmx_Status_t NDnSAgent_GetSLA( UINT32 nspBufferLength, UINT8 *nspBuffer, UINT32 slaBufferLength, UINT8 *slaBuffer );

void NDnSAgent_SendCurrentPreferredNSPChanged(UINT32 numOfCurrentPreferred, wmx_pNSPid_t pNspIDs );
wmx_Status_t GetCurrentPreferredNSPEx(wmx_pNSP_t pNSP, UINT32 *pNumOfCurrentPreferredNSPs);

// Callback Functions to Gold Wrapper
void NDnSAgent_ConnectCompleted( wmx_ConnectStatus_t connectStatus );
void NDnSAgent_ConnectionModeUpdate( wmx_UserConnectMode_t connectionMode );
void NDnSAgent_RoamingModeUpdate( wmx_UserRoamingMode_t roamingMode );
void NDnSAgent_FastReconnectModeUpdate( BOOL fastReconnectModeUpdate );
void NDnSAgent_ConnectedAsCurrentPreferredCapabilityStatusUpdate( BOOL connectedAsCurrentPreferredCapabilityStatus );

// Callback Functions to Supplicant Wrapper
void NDnSAgent_SupEventReport( wmx_SupEvent_t event );

wmx_Status_t L4C_StartScan(wmx_ScanType_t scanType, wmx_LinkLossType_t linkLossType, BOOL delayStart, BOOL isInternal);
wmx_Status_t L4C_StartManualScanDirect(UINT8 *pChannelsListBuffer);
wmx_Status_t L4C_SetControllerMode(wmx_SystemState_t systemState, BOOL verifyState);
wmx_Status_t L4C_SetControllerModeEx(wmx_pSystemStateUpdate systemStateUpdate, BOOL verifyState);

// Available NSPs List functionality
wmx_Status_t AgeAvailableNspsList();
BOOL IsNspInAvailableNspsList(wmx_NSPid_t nspId);
wmx_Status_t ClearAvailableNSPsList();
void CreateFakeAvailableNSPsFromNaps(UINT32 numOfNaps, wmx_pNAP_t naps, UINT32 *numOfNsps, wmx_pAvailableNSP_t nsps);
wmx_Status_t AddMultipleNSPsToAvailableNSPsList(UINT32 numOfNsps, wmx_pNSP_t nsp, wmx_BSid_t *bsIds, wmx_BsIdType_t *bsIdsTypes);
wmx_Status_t AddMultipleFakeNSPsToAvailableNSPsList(UINT32 numOfNsps, wmx_pAvailableNSP_t nsp);
void PrintAvailableNspsList(BOOL isFiltered, Severities severity);
wmx_Status_t GetAvailableNspsList(UINT32 *numOfNSPs, wmx_pNSP_t nsps, BOOL isFiltered);
BOOL GetAvailableNspNode(wmx_NSPid_t nspId, wmx_pAvailableNSP_t pAvailableNsp);
BOOL CheckIfNspInAvailableList(wmx_NSPid_t nspId);
wmx_Status_t GetNspInfo(wmx_NSPid_t nspId, wmx_pNSP_t pNSP);
wmx_Status_t GetInstallationInfo(void *buffer, UINT32 *bufferSize);
wmx_CoexistenceMode_t L4C_GetInitialCoexMode(void);
wmx_Status_t GeneratePseudoNAI (char *pseudoNai, int buffSize);
void NDnSAgent_HandleApdoLinkStatus(wmx_ApdoLinkStatus_t linkStatus);
wmx_CoexistenceMode_t L4C_GetInitialCoexMode(void);
void L4C_SetProcessStarted(BOOL isProcessStarted);
wmx_Status_t GetWMFComplianceInfo(void *buffer, UINT32 bufferSize);
void L4C_CallHandleRobustConnect(BOOL isL3Trigger);
wmx_Status_t L4C_HandleSystemStateUpdate(wmx_pSystemStateUpdate systemStateUpdate);
wmx_Status_t L4C_NotifyPNMChange(void);
wmx_Status_t L4C_GetIsPNMCommDevUsingChannel(void *buffer, UINT32 *bufferSize);
#endif // _NDNS_AGENT_H