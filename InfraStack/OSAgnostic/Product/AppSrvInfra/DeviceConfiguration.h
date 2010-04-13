/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
#ifndef _DEVICE_CONFIGURATION_H
#define _DEVICE_CONFIGURATION_H

#include "wimax_osal_types.h"
#include "L4BufMan_L3L4DmStructs_Desc.h"

#define NUM_OF_LED_BLINK_RATE 14
#define NUM_OF_LED_BEHAVIOR 14
#define NUM_OF_LED_GEN_ARG 6
#define PRIVILEGE_KEY_SIZE 8

typedef struct _wmx_UsrIndLedBlinkRateArr_t
{
   UINT8 _OnPeriod[NUM_OF_LED_BLINK_RATE];         
   UINT8 _OffPeriod[NUM_OF_LED_BLINK_RATE];
} wmx_UsrIndLedBlinkRateArr_t, *wmx_pUsrIndLedBlinkRateArr_t;


BOOL wmx_PopulateLEDBehaivor(LedOperationalConfigComp_tlv_type *pLedOperationalConfigComp);
BOOL wmx_PopulateLEDStructValues(LedOperationalConfigComp_tlv_type *pLedOperationalConfigComp);
BOOL Populate_LedStruct(LedOperationalConfigComp_tlv_type* pLedOperationalConfigComp);
BOOL Populate_LinkDownStruct(LinkDownTimerConfigComp_tlv_type* pLinkDownTimerConfigComp);
BOOL Populate_IdleParameterTimeoutStruct(IdleParameterTimeoutConfigComp_tlv_type* pIdleParameterTimeoutConfigComp);
BOOL Populate_IdleParameterPagingIntervalStruct(IdleParameterPagingIntervalConfigComp_tlv_type* pIdleParameterPagingIntervalConfigComp);
BOOL Populate_IdleParameterIdleEntrySuspendStruct(IdleParameterIdleEntrySuspendConfigComp_tlv_type* pIdleParameterIdleEntrySuspendConfigComp);
BOOL Populate_IdleParameterFullNeSuspendStruct(IdleParameterFullNeSuspendConfigComp_tlv_type* pIdleParameterFullNeSuspendConfigComp);
BOOL Populate_PreInitConfigurationStruct(SetPreInitConfiguration_type* pLedConfigurationStruct);
BOOL Populate_ResetOnAssertStruct(ResetOnAssertConfigComp_tlv_type* pResetOnAssertConfigComp);
BOOL Populate_HarqParametersStruct(HarqParametersConfigComp_tlv_type* pHarqParametersConfigComp);
BOOL Populate_LoopBackStruct(LoopBackConfigComp_tlv_type* pLoopBackConfigComp);
BOOL Populate_PrivilegeStruct(PrivilegeKeyConfigComp_tlv_type* pPrivilegeKeyConfigComp);
BOOL Populate_PrivilegeKeyStruct(PrivilegeKeyConfigComp_tlv_type* pPrivilegeKeyConfigComp);
BOOL Populate_LimitMaxTxPowerStruct(LimitMaxTxPowerConfigComp_tlv_type* pLimitMaxTxPowerConfigComp);
BOOL Populate_WatchDogTimerStruct(WatchDogTimerConfigComp_tlv_type* pWatchDogTimerConfig);
BOOL Populate_SlowClockStruct(SlowClockConfigComp_tlv_type* pSlowClockConfig);
BOOL Populate_SelectivePLIParametersStruct(SelectivePLIParametersConfigComp_tlv_type* pSelectivePLIParametersConfig);
BOOL Populate_D2HDataFormatStruct(D2HDataFormatConfigComp_tlv_type* pD2HDataFormatConfig);
BOOL Populate_DLHostReorderStruct(DLHostReorderConfigComp_tlv_type* pDLHostReorderConfig);
BOOL Populate_PaddingPerCSTypeStruct(PaddingPerCSConfigComp_tlv_type* pPaddingPerCSConfig);


#endif //_DEVICE_CONFIGURATION_H
