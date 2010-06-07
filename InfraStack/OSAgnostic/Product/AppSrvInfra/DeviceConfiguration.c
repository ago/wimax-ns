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
#include "wimax_osal_types.h"
#include "wimax_osal_string.h"
#include "wimax_osal_config_controler.h"		
#include "L3L4Structs.h"
#include "L4BufMan_L3L4Structs_Desc.h"
#include "DeviceConfiguration.h"
#include "L4ConfigurationManager.h"
#include "TraceModule.h"



BOOL wmx_PopulateLEDBehaivor(LedOperationalConfigComp_tlv_type *pLedOperationalConfigComp)
{
	int i;
	BOOL res;
	char answer1[NUM_OF_LED_BEHAVIOR + 1];
	char answer2[NUM_OF_LED_BEHAVIOR + 1];

	res = L4Configurations_getLED1Behavior(answer1);
	res &= L4Configurations_getLED2Behavior(answer2);

	for (i = 0; i<NUM_OF_LED_BEHAVIOR; i++)
	{
		pLedOperationalConfigComp->ledBehavior[i].Led0Scheme = (UINT8)(((UINT32 *)(answer1 + i))[0] -65);
		pLedOperationalConfigComp->ledBehavior[i].Led1Scheme = (UINT8)(((UINT32 *)(answer2 +  i))[0] -65);
	}

	return res;
}

BOOL wmx_PopulateLEDStructValues(LedOperationalConfigComp_tlv_type *pLedOperationalConfigComp)
{
	BOOL res;
	UINT32 answer1, answer2, answer3, answer4;

	res = L4Configurations_getInterval(&answer1);
	res &= L4Configurations_getNumOfLeds(&answer2);
	res &= L4Configurations_getNVMOverride(&answer3);
	res &= L4Configurations_getPowerSaveInd(&answer4);

	if (res)
	{
		pLedOperationalConfigComp->powerSaveInfo.ledTimeInterval = answer1;
		pLedOperationalConfigComp->numOfLeds = (UINT8)answer2;
		pLedOperationalConfigComp->NvmOverride = (UINT8)answer3;
		pLedOperationalConfigComp->powerSaveInfo.powerSaveMode = (UINT8)answer4;

		wmx_PopulateLEDBehaivor(pLedOperationalConfigComp);

		return TRUE;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get LED values in func wmx_PopulateLEDStructValues returned");
		return FALSE;
	}
}

BOOL Populate_LedStruct(LedOperationalConfigComp_tlv_type* pLedOperationalConfigComp)
{
	int i;
	wmx_UsrIndLedBlinkRateArr_t LEDBlinkStruct;


	if(!L4Configurations_getLedBlinkRate(LEDBlinkStruct._OnPeriod, OSAL_KEY_ENTRY_PIPELED_BLINK_ON))
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Populate_LedStruct F1");
		return FALSE;
	}

	if(!L4Configurations_getLedBlinkRate(LEDBlinkStruct._OffPeriod, OSAL_KEY_ENTRY_PIPELED_BLINK_OFF))
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Populate_LedStruct F2");
		return FALSE;
	}

	for(i = 0; i < (NUM_OF_LED_BLINK_RATE - 1); i++)
	{
		pLedOperationalConfigComp->blinkingRate[i].offPeriod = LEDBlinkStruct._OffPeriod[i];
		pLedOperationalConfigComp->blinkingRate[i].onPeriod = LEDBlinkStruct._OnPeriod[i];
	}
	pLedOperationalConfigComp->powerSaveInfo.ledBlinkRate.offPeriod = LEDBlinkStruct._OffPeriod[NUM_OF_LED_BLINK_RATE -1];
	pLedOperationalConfigComp->powerSaveInfo.ledBlinkRate.onPeriod = LEDBlinkStruct._OnPeriod[NUM_OF_LED_BLINK_RATE -1];

	if(!wmx_PopulateLEDStructValues(pLedOperationalConfigComp))
	{
		TRACE(TR_MOD_ACT, TR_SEV_ERR, "Populate_LedStruct F3");
		return FALSE;
	}
	
	pLedOperationalConfigComp->Type = L3L4_TLV_TYPE_CONFIG_LEDS;
	return TRUE;
}

BOOL Populate_IdleParameterTimeoutStruct(IdleParameterTimeoutConfigComp_tlv_type* pIdleParameterTimeoutConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

	res = L4Configurations_getIdleTimeout(&answerVal);
	if (res)
	{
		pIdleParameterTimeoutConfigComp->IdleTimeout = answerVal;
		pIdleParameterTimeoutConfigComp->Type = L3L4_TLV_TYPE_CONFIG_IDLE_PARAMETERS_TIMEOUT;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get IdleTimeout value in func Populate_IdleParameterTimeoutStruct");	
	}

	return res;
}

BOOL Populate_IdleParameterPagingIntervalStruct(IdleParameterPagingIntervalConfigComp_tlv_type* pIdleParameterPagingIntervalConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

	res = L4Configurations_getIdlePagingInterval(&answerVal);
	if (res)
	{
		pIdleParameterPagingIntervalConfigComp->PagingInterval = answerVal;
		pIdleParameterPagingIntervalConfigComp->Type = L3L4_TLV_TYPE_CONFIG_IDLE_PARAMETERS_PAG_INTERVAL;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get IdlePagingInterval value in func Populate_IdleParameterPagingIntervalStruct");	
	}

	return res;
}

BOOL Populate_IdleParameterIdleEntrySuspendStruct(IdleParameterIdleEntrySuspendConfigComp_tlv_type* pIdleParameterIdleEntrySuspendConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

	res = L4Configurations_getIdleEntrySuspend(&answerVal);
	if (res)
	{
		pIdleParameterIdleEntrySuspendConfigComp->IdleEntrySuspend = answerVal;
		pIdleParameterIdleEntrySuspendConfigComp->Type = L3L4_TLV_TYPE_CONFIG_IDLE_PARAMETERS_IDLE_REENTERY_SUSPEND;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get IdleEntrySuspend value in func Populate_IdleParameterIdleEntrySuspendStruct");	
	}

	return res;
}

BOOL Populate_IdleParameterFullNeSuspendStruct(IdleParameterFullNeSuspendConfigComp_tlv_type* pIdleParameterFullNeSuspendConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

	res = L4Configurations_getFullNeSuspend(&answerVal);
	if (res)
	{
		pIdleParameterFullNeSuspendConfigComp->FullNeSuspend = answerVal;
		pIdleParameterFullNeSuspendConfigComp->Type = L3L4_TLV_TYPE_CONFIG_IDLE_PARAMETERS_FULL_NE_SUSPEND;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get FullNeSuspend value in func Populate_IdleParameterFullNeSuspendStruct");	
	}

	return res;
}

BOOL Populate_SelectivePLIParametersStruct(SelectivePLIParametersConfigComp_tlv_type* pSelectivePLIParametersConfig)
{
	BOOL res;
	BOOL resAll = TRUE;
	UINT32 answerVal = 0;

	res = L4Configurations_getEnableSelectivePLIs(&answerVal);
	if (res)
	{
		pSelectivePLIParametersConfig->EnableSelectivePLIs = (UINT8)answerVal;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get EnableSelectivePLIs value in func Populate_SelectivePLIParametersConfigComp");	
		resAll = FALSE;
	}

	res = L4Configurations_getDelayedSelectivePLI(&answerVal);
	if (res)
	{
		pSelectivePLIParametersConfig->DelayedSelectivePLI = (UINT8)answerVal;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get DelayedSelectivePLI value in func Populate_SelectivePLIParametersConfigComp");			
		resAll = FALSE;		
	}

	res = L4Configurations_getConsecutivePLIToReceive(&answerVal);
	if (res)
	{
		pSelectivePLIParametersConfig->ConsecutivePLIToReceive = (UINT8)answerVal;
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get ConsecutivePLIToReceive value in func Populate_SelectivePLIParametersConfigComp");			
		resAll = FALSE;		
	}

	if (resAll)
	{
		pSelectivePLIParametersConfig->Type = L3L4_TLV_TYPE_CONFIG_SELECTIVE_PLI_PARAMS;
	}

	return resAll;
}

BOOL Populate_D2HDataFormatStruct(D2HDataFormatConfigComp_tlv_type* pD2HDataFormatConfig)
{
	UINT32 answerVal = 0;

	L4Configurations_getD2HDataFormat(&answerVal);

	pD2HDataFormatConfig->Type			= L3L4_TLV_TYPE_CONFIG_D2H_DATA_FORMAT;
	pD2HDataFormatConfig->DataFormatMem	= (UINT8)(answerVal);
	pD2HDataFormatConfig->Reserved1		= (UINT8)(0);
	pD2HDataFormatConfig->Reserved2		= (UINT16)(0);

	return TRUE;
}

BOOL Populate_DLHostReorderStruct(DLHostReorderConfigComp_tlv_type* pDLHostReorderConfig)
{
	UINT32 answerVal = 0;

	L4Configurations_getDLHostReorder(&answerVal);

	pDLHostReorderConfig->Type			= L3L4_TLV_TYPE_CONFIG_DL_HOST_REORDER;
	pDLHostReorderConfig->DLHostReorder = (UINT8)(answerVal);
	pDLHostReorderConfig->Reserved1		= (UINT8)(0);
	pDLHostReorderConfig->Reserved2		= (UINT16)(0);

	return TRUE;
}


BOOL Populate_PaddingPerCSStruct(PaddingPerCSConfigComp_tlv_type* pPaddingPerCSConfig)
{
	BOOL res;
	UINT resAll = 0;
	UINT32 answerVal = 0;

	res = L4Configurations_getCSType(&answerVal);
	pPaddingPerCSConfig->CSType = (UINT8)answerVal;

	if (res)
	{
		resAll++;
	}

	res = L4Configurations_getPaddingSize(&answerVal);
	pPaddingPerCSConfig->PaddingSize = (UINT8)answerVal;

	if (res)
	{
		resAll++;
	}

	// If all parameters were received from the same source (either default (0) or registry (2))
	if ((resAll == 0) || (resAll == 2))
	{
		pPaddingPerCSConfig->Type = L3L4_TLV_TYPE_CONFIG_PADDING_PER_CS;
	}

	return (resAll == 1) ? FALSE : TRUE;
}


BOOL Populate_LinkDownStruct(LinkDownTimerConfigComp_tlv_type* pLinkDownTimerConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getLinkDownTimer(&answerVal);
	if (res)
	{
		pLinkDownTimerConfigComp->Type = L3L4_TLV_TYPE_CONFIG_LINK_DOWN_TIMER;
		pLinkDownTimerConfigComp->LinkDown = answerVal;
		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get LinkDown value in func Populate_LinkDownStruct");
	return FALSE;
}

BOOL Populate_ArqSupportStruct(ArqSupportConfigComp_tlv_type* pArqSupportConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

	res = L4Configurations_getArqSupport(&answerVal);
	if (res)
	{
		pArqSupportConfigComp->Type = L3L4_TLV_TYPE_CONFIG_ARQ_SUPPORT;
		pArqSupportConfigComp->GeneralState = (UINT8)(answerVal);
		pArqSupportConfigComp->Reserved1 = (UINT8)(0);
		pArqSupportConfigComp->Reserved2 = (UINT16)(0);

		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get ArqSupport value in func Populate_ArqSupportStruct");
	return FALSE;
}


BOOL Populate_ResetOnAssertStruct(ResetOnAssertConfigComp_tlv_type* pResetOnAssertConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getResetOnAssert(&answerVal);
	if (res)
	{
		pResetOnAssertConfigComp->Type = L3L4_TLV_TYPE_CONFIG_RESET_ON_ASSERT;
		pResetOnAssertConfigComp->GeneralState = (UINT8)(answerVal);
		pResetOnAssertConfigComp->Reserved1 = (UINT8)(0);
		pResetOnAssertConfigComp->Reserved2 = (UINT16)(0);

		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get ResetOnAssert value in func Populate_ResetOnAssertStruct");
	return FALSE;
}

BOOL Populate_HarqParametersStruct(HarqParametersConfigComp_tlv_type* pHarqParametersConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

	res = L4Configurations_getHarqCategory(&answerVal);
	if (res)
	{
		pHarqParametersConfigComp->Type				= L3L4_TLV_TYPE_CONFIG_HARQ_PARAMETERS;
		pHarqParametersConfigComp->HarqCategory		= (UINT8)(answerVal);
		pHarqParametersConfigComp->Reserved1		= (UINT8)(0);
		pHarqParametersConfigComp->Reserved2		= (UINT16)(0);

		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get Harq Parameters value in func Populate_HarqParametersStruct");
	return FALSE;
}

BOOL Populate_LoopBackStruct(LoopBackConfigComp_tlv_type* pLoopBackConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getLoopBack(&answerVal);
	if (res)
	{
		pLoopBackConfigComp->Type = L3L4_TLV_TYPE_CONFIG_LOOP_BACK;
		pLoopBackConfigComp->OperationMode = (UINT8)(answerVal);
		pLoopBackConfigComp->Reserved1 = (UINT8)(0);
		pLoopBackConfigComp->Reserved2 =(UINT16)(0);
		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get LoopBack value in func Populate_LoopBackStruct");
	return FALSE;
}
int convertHexToDec(char charToConvert)
{
	int tempInt;

	tempInt =(int)(charToConvert);
	if( tempInt<= 70 && tempInt >= 65)
	{
		return (tempInt - 55);
	}
	if( tempInt<= 57 && tempInt >= 48)
	{
		return (tempInt - 48);
	}
	return 256;
}
BOOL Populate_PrivilegeKeyStruct(PrivilegeKeyConfigComp_tlv_type* pPrivilegeKeyConfigComp)
{
	BOOL res;
	char answerVal[PRIVILEGE_KEY_SIZE + 1];
	int i;

    res = L4Configurations_getPrivilegeKey(answerVal);
	if (res || (OSAL_strnlen(answerVal, PRIVILEGE_KEY_SIZE + 1) == PRIVILEGE_KEY_SIZE) )
	{
		for(i=0;i<PRIVILEGE_KEY_SIZE; i=i+2)
		{
			pPrivilegeKeyConfigComp->Key[(i/2)].value = (UINT8)((convertHexToDec(answerVal[i]) * 16 + convertHexToDec(answerVal[i+1])));
			if(pPrivilegeKeyConfigComp->Key[(i/2)].value < 0)
			{
				i = PRIVILEGE_KEY_SIZE;
				TRACE(TR_MOD_ACT, TR_SEV_ERR, "The value in PrivilegeKey is invalid");
				return FALSE;
			}
		}
		pPrivilegeKeyConfigComp->Type = L3L4_TLV_TYPE_PRIVILEGE_KEY;
		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get PrivilegeKey value in func Populate_PrivilegeKeyStruct");
	return FALSE;
}

BOOL Populate_PrivilegeStruct(PrivilegeKeyConfigComp_tlv_type* pPrivilegeKeyConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getPrivilegeEnable(&answerVal);
	if (res)
	{
		if(answerVal == 1)
		{
			res = Populate_PrivilegeKeyStruct(pPrivilegeKeyConfigComp);
			if (!res)
			{
				TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get PrivilegeKey value in func Populate_PrivilegeStruct");
				return FALSE;
			}
		}
		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get PrivilegeEnable value in func Populate_PrivilegeStruct");
	return FALSE;
}
BOOL Populate_LimitMaxTxPowerStruct(LimitMaxTxPowerConfigComp_tlv_type* pLimitMaxTxPowerConfigComp)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getLimitMaxTxPower(&answerVal);
	if (res)
	{
		pLimitMaxTxPowerConfigComp->Type = L3L4_TLV_TYPE_CONFIG_LINK_DOWN_TIMER;
		pLimitMaxTxPowerConfigComp->LimitMaxTxPower = (UINT32)(answerVal);
		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get LimitMaxTxPower value in func Populate_LimitMaxTxPowerStruct");
	return FALSE;
}

BOOL Populate_WatchDogTimerStruct(WatchDogTimerConfigComp_tlv_type* pWatchDogTimerConfig)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getWatchDogTimer(&answerVal);
	if (res)
	{
		pWatchDogTimerConfig->Type = L3L4_TLV_TYPE_CONFIG_WATCH_DOG_TIMER;
		pWatchDogTimerConfig->GeneralState = (UINT8)(answerVal);
		pWatchDogTimerConfig->Reserved1 = (UINT8)(0);
		pWatchDogTimerConfig->Reserved2 = (UINT16)(0);

		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get WatchDogTimer value in func Populate_WatchDogTimerStruct");
	return FALSE;
}

BOOL Populate_SlowClockStruct(SlowClockConfigComp_tlv_type* pSlowClockConfig)
{
	BOOL res;
	UINT32 answerVal = 0;

    res = L4Configurations_getPowerSaveEnable(&answerVal);
	if (res)
	{
		pSlowClockConfig->Type = L3L4_TLV_TYPE_CONFIG_SLOW_CLOCK;
		pSlowClockConfig->GeneralState = (UINT8)(answerVal);
		pSlowClockConfig->Reserved1 = (UINT8)(0);
		pSlowClockConfig->Reserved2 = (UINT16)(0);

		return TRUE;
	}
	TRACE(TR_MOD_ACT, TR_SEV_NOTICE, "cannot get SlowClock value in func Populate_SlowClockStruct");
	return FALSE;
}

BOOL Populate_PreInitConfigurationStruct(SetPreInitConfiguration_type* pSetPreInitConfiguration)
{
	BOOL tlvValidate = FALSE;

	TRACE(TR_MOD_ACT, TR_SEV_INFO, "Populate_PreInitConfigurationStruct (IN)");
	if(Populate_LedStruct(&(pSetPreInitConfiguration->LedOperationalConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got LED registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get LED registry parameters");
	}

	if(Populate_IdleParameterTimeoutStruct(&(pSetPreInitConfiguration->IdleParameterTimeoutConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Idle Parameter Timeout registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Idle Parameter Timeout registry parameters");
	}

	if(Populate_IdleParameterPagingIntervalStruct(&(pSetPreInitConfiguration->IdleParameterPagingIntervalConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Idle Parameter Paging Interval registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Idle Parameter Paging Interval registry parameters");
	}

	if(Populate_IdleParameterIdleEntrySuspendStruct(&(pSetPreInitConfiguration->IdleParameterIdleEntrySuspendConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Idle Parameter Idle Entry Suspend registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Idle Parameter Idle Entry Suspend registry parameters");
	}

	if(Populate_IdleParameterFullNeSuspendStruct(&(pSetPreInitConfiguration->IdleParameterFullNeSuspendConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Idle Parameter Full NE Suspend registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Idle Parameter Full NE Suspend registry parameters");
	}

	if(Populate_LinkDownStruct(&(pSetPreInitConfiguration->LinkDownTimerConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Link Down registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Link Down registry parameters");
	}
	
	if(Populate_ArqSupportStruct(&(pSetPreInitConfiguration->ArqSupportConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Arq Support registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get ArqSupport registry parameters");
	}
	
	if(Populate_ResetOnAssertStruct(&(pSetPreInitConfiguration->ResetOnAssertConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Reset On Assert registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Reset On Assert registry parameter");
	}

	if(Populate_HarqParametersStruct(&(pSetPreInitConfiguration->HarqParametersConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got HARQ Parameters registry parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get HARQ Parameters registry parameter");
	}	

	if(Populate_D2HDataFormatStruct(&(pSetPreInitConfiguration->D2HDataFormatConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got D2H Data Format parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get D2H Data Format parameters");
	}	

	if(Populate_DLHostReorderStruct(&(pSetPreInitConfiguration->DLHostReorderConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got DL Host Reorder parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get DL Host Reorder parameters");
	}	

	if(Populate_PaddingPerCSStruct(&(pSetPreInitConfiguration->PaddingPerCSConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Padding Per CS parameters with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get Padding Per CS parameters");
	}	

	if(Populate_LoopBackStruct(&(pSetPreInitConfiguration->LoopBackConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got loop back registry parameter with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get loop back registry parameter");
	}
	if(Populate_PrivilegeStruct(&(pSetPreInitConfiguration->PrivilegeKeyConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got Privilege Key registry parameter with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get valid Privilege Key registry parameter");
	}
	if(Populate_LimitMaxTxPowerStruct(&(pSetPreInitConfiguration->LimitMaxTxPowerConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got LimitMaxTxPower Key registry parameter with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get valid LimitMaxTxPower Key registry parameter");
	}
	
	if(Populate_WatchDogTimerStruct(&(pSetPreInitConfiguration->WatchDogTimerConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got WatchDogTimer Key registry parameter with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get valid WatchDogTimer Key registry parameter");
	}

	if(Populate_SlowClockStruct(&(pSetPreInitConfiguration->SlowClockConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got SlowClock Key registry parameter with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get valid SlowClock Key registry parameter");
	}

	if(Populate_SelectivePLIParametersStruct(&(pSetPreInitConfiguration->SelectivePLIParametersConfigComp)))
	{
		tlvValidate = TRUE;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "got SelectivePLIParameters registry parameter with success");
	}
	else
	{
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "cannot get valid SelectivePLIParameters registry parameter");
	}

	if (tlvValidate)
	{
		return TRUE;
	}
	return FALSE;

}
