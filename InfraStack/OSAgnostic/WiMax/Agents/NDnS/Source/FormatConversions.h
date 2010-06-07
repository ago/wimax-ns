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
#ifndef _NDNS_FORMAT_CONVERSIONS_H
#define _NDNS_FORMAT_CONVERSIONS_H

#include "CommonServices.h"
#include "L5Common.h"
#include "Messenger.h"

#include "wmxSDK_Nds_Cmn.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Nds_CtrlAgent.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Sup_4.h"
#include "NDnSAgent_DB_if.h"



wmx_UserConnectMode_t ConvertToConnectMode(const char* val);
void ConvertConnectModeToStr(wmx_UserConnectMode_t val, char * dst, int size);
wmx_UserConnectMode_t ConvertToRoamingMode(const char* val);
void ConvertRoamingModeToStr(wmx_UserConnectMode_t val, char * dst, int size);
wmx_RssiThreshold_t ConvertToRssiTH(const char* val);
wmx_CinrThreshold_t ConvertToCinrTH(const char* val);
wmx_ChannelID_t ConvertToChannelID(const char* val);
wmx_Frequency_t ConvertToFrequency(const char* val);
wmx_Status_t ConvertToBandWidth(const char* val,wmx_pBW_t pBWtype);
wmx_Status_t ConvertToFFT(const char* val, wmx_pFFT_t pFFT);
void ConvertBandWidthToStr(wmx_BW_t bwt, char * dst, int size);
void ConvertFFTtoStr(wmx_FFT_t fft, char * dst, int size);
wmx_MaxTxPower_t ConvertToMaxTxPower(const char* val);
void ConvertPreamblesBitmapToStr(wmx_pPreambles_t preambles, char* val);
void ConvertToPreamblesBitmap(wmx_pPreambles_t preambles, const char* val);
UINT32 ConvertToSLA(const char* val);
wmx_LinkSpeed_t ConvertToLinkSpeed(const char* val);

wmx_Status_t ConvertToPsPolicy(const char* val, pPreferredScanPolicy_t pPolicy);
void ConvertPsPolicyToStr(PreferredScanPolicy_t policy, char * dst, int size);
//wmx_Status_t ConvertToCertType(const char* val, pCertType_t pCertType);
//void ConvertCertTypeToStr(CertType_t certType, char * dst, int size);
wmx_Status_t ConvertToAnyType(char * anyStr, pAny_t pAny);
void ConvertToAnyStr(Any_t any, char * anyStr, int size);
wmx_Status_t ConvertToSelectPolicyType(char * selectPolicyStr, pSelectPolicy_t pSelectPolicy);
void ConvertToSelectPolicyStr(SelectPolicy_t selectPolicy, char * selectPolicyStr, int size);
void l4db_ConvertToEapTypeStr(wmx_EapType_t eapType, char * eapTypeStr);
wmx_EapType_t l4db_ConvertToEapTypeEnum(char * eapTypeStr);
void strlower(char *target, const char *source, UINT32 targetLen);

void wmxNds_ScanStatusToUserScanStatus(wmx_pUserScanStatus_t userScanStatus, wmx_ScanStatus_t scanStatus);
void wmxNds_ConnectStatusToUserConnectStatus(wmx_pUserConnectStatus_t userConnectStatus, wmx_ConnectStatus_t connectStatus);
void wmxNds_BsIdMaskToStr(wmx_BsIdType_t bsIdType, char *str, int strLength);
wmx_EapMathod_t wmx_EapTypeToDS_EapType(wmx_EapType_t eapType);

wmx_Status_t ConvertToDownloadState(const char* val,  pDownloadState_t pDownloadState);
void ConvertDownloadStateToStr(DownloadState_t downloadState, char * dst, int size);
BOOL wmxNds_DBChannelInfoToWmxChannelInfo(wmx_pChannelInfo_t target, UINT32 *targetMaxCount, pChannelInfo_t source, UINT32 sourceCount);
BOOL wmxNds_WmxChannelInfoToDBChannelInfo(pChannelInfo_t target, UINT32 *targetMaxCount, wmx_pChannelInfo_t source, UINT32 sourceCount, BOOL isFoundInNbrAdv);
void DeviceStatusToStr(wmx_DeviceStatus_t deviceStatus, char * deviceStatusStr, size_t size);
void ConnectionProgressToStr(wmx_ConnectionProgressInfo_t connProgresss, char * connProgressStr, size_t size);

#endif //_NDNS_FORMAT_CONVERSIONS_H