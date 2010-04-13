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
#include "L4ConfigurationManager.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_string.h"
#include "TraceModule.h"
#include "wmxSDK_Msc_2.h"

static BOOL bInit = FALSE;

// Holds configurations for L4.
static struct {
	char DriverMode[DEFULT_STR_SIZE];	
	char IPCMode[DEFULT_STR_SIZE];	
	char dSimIpAddress[IP_STR_SIZE];
	char OutputTarget[DEFULT_STR_SIZE];
	char RootPath[MAX_REGISTRY_ANSWER];
	char TracePath[MAX_REGISTRY_ANSWER];
	char SdkIpAddress[IP_STR_SIZE];
	char LogPath[MAX_FILENAME_LEN + 1];
	char CoexistingMode[DEFULT_STR_SIZE];
	char LogFileName[MAX_FILENAME_LEN];
	char TLS_Source[MAX_ANSWER_SIZE];
	char PrivilegeKey[PRIVILEGE_KEY_SIZE + 1];
	char LED1Behavior[NUM_OF_LED_BEHAVIOR +1];
	char LED2Behavior[NUM_OF_LED_BEHAVIOR + 1];
	char NoRealmInNAI[MAX_ANSWER_SIZE];
	char CustomDecoration[MAX_REGISTRY_ANSWER];
	char Installing[MAX_ANSWER_SIZE];
	//char InstallationStatus[MAX_ANSWER_SIZE];
	UINT32 Modules;
	UINT32 Severities;
	UINT32 UseNewTraces;
	UINT32 dSimIndicationsPortNum;
	UINT32 dSimOidsPortNum;
	UINT32 GetDeviceTraces;
	UINT32 ModeOfOperationProduction;
	UINT32 StartWatchdog;	
	UINT32 SdkPortNum;
	UINT32 DnDOutputPortNum;
	UINT32 EnableVersioning;
	UINT32 DumpEnable;
	UINT32 FALL_TO_XOR_TIMEOUT;
	UINT32 ConnectTime;
	UINT32 NoXohmGroups;
	UINT32 NoSM;
	UINT32 DisableDiscovery;
	UINT32 IdleTimeout;
	UINT32 IdlePagingInterval;
	UINT32 IdleEntrySuspend;
	UINT32 FullNeIdleSuspend;
	UINT32 LinkDownTimer;
	UINT32 PbLog;
	UINT32 WatchDogTimer;
	UINT32 LimitMaxTxPower;
	UINT32 PrivilegeEnable;
	UINT32 ShowUnknownNSPs;
	UINT32 DoNotUsePseudoNAI;
	UINT32 LoopBack;
	UINT32 ResetOnAssert;
	UINT32 HarqCategory;
	UINT32 D2HDataFormat;
	UINT32 DLHostReorder;
	UINT32 CSType;
	UINT32 PaddingSize;
	UINT32 Interval;
	UINT32 NumOfLeds;
	UINT32 NVMOverride;
	UINT32 PowerSaveInd;
	UINT32 ArqSupport;
	UINT32 PowerSaveEnable;
	UINT32 EnableSelectivePLIs;
	UINT32 DelayedSelectivePLI;
	UINT32 ConsecutivePLIToReceive;
	UINT32 CommonPriviledgeEnable;
	UINT8 OnBlinkRate[NUM_OF_LED_BLINK_RATE];
	UINT8 OffBlinkRate[NUM_OF_LED_BLINK_RATE];
	UINT32 ApdoLinkUpSleep;
	UINT32 ApdoAfterLinkUpSleep;
	UINT32 ApdoLinkUpRetries;
	UINT32 StartMOCMsgProxy;
	UINT32 DnDOutputMode;
	UINT32 MaxNumOfDirs;
	UINT32 MaxNumOfFiles;
	UINT32 EnableInstrumentation;
	UINT32 InstrumentationLoadingType;
	UINT32 ApdoPackageUpdateSleep;
	UINT32 DisableFastReconnect;
	UINT32 DisableRobustConnect;

	char PackageName[MAX_REGISTRY_ANSWER];
	char ApdoReadFromNvm[DEFULT_STR_SIZE];
	char ApdoDevIDPrefix[DEV_ID_PREFIX_SIZE];
	char ApdoSecureBootstrap[DEFULT_STR_SIZE];
	char ApdoLeaveDbDefaults[DEFULT_STR_SIZE];
	char ApdoFixSpecialCharacters[DEFULT_STR_SIZE];
	char ApdoFumoSwv2String[MAX_REGISTRY_ANSWER];
	char ApdoTerminalEquipmentManID[WMX_MANUFACTURER_NAME_MAX_LENGTH];
	char ApdoTerminalEquipmentModel[WMX_MODEL_TYPE_NAME_MAX_LENGTH];
	char ApdoTerminalEquipmentFwV[WMX_DEVICE_VERSION_MAX_LENGTH];
	char ApdoTerminalEquipmentHwV[WMX_DEVICE_VERSION_MAX_LENGTH];
	char ApdoTerminalEquipmentDevType[WMX_DEVICE_VERSION_MAX_LENGTH];
	char ApdoTerminalEquipmentDevID[WMX_DEVICE_VERSION_MAX_LENGTH];

	char ApdoDevInfoManID[WMX_MANUFACTURER_NAME_MAX_LENGTH];
	char ApdoDevInfoModel[WMX_MODEL_TYPE_NAME_MAX_LENGTH];

	char ApdoDevDetailsDevType[WMX_DEVICE_VERSION_MAX_LENGTH];
	char ApdoDevDetailsFwV[WMX_DEVICE_VERSION_MAX_LENGTH];
	char ApdoDevDetailsHwV[WMX_DEVICE_VERSION_MAX_LENGTH];
	char ApdoDevDetailsSwV[WMX_DEVICE_VERSION_MAX_LENGTH];
	
	char ApdoSharedSecret[MAX_ANSWER_SIZE];
	char ApdoCalcSecret[MAX_ANSWER_SIZE];
	char ApdoMandatoryUpdateLogic[MAX_ANSWER_SIZE];
	char dndFilesPath[MAX_ANSWER_SIZE];
	char ApdoFumoDisable[MAX_ANSWER_SIZE];	
	char InstrumentationLibName[MAX_ANSWER_SIZE];
	char DhcpDomain[MAX_SIZE_OF_REALM_NAME];
	char SupplicantLibName[MAX_ANSWER_SIZE];
} L4Configurations;

// Initializes the L4Configuration struct.
void L4Configurations_init() 
{
	// This function is called from Services_Init, and one time in GenericMain. For each instance it should 
	// be initialized only once.
	if (!bInit)
	{
		memset(&L4Configurations, 0, sizeof(L4Configurations));

		OSAL_strcpy_s(L4Configurations.DriverMode, sizeof(L4Configurations.DriverMode)/sizeof(char), (const char *)DEFAULT_DRIVER_MODE);
		OSAL_strcpy_s(L4Configurations.IPCMode, sizeof(L4Configurations.IPCMode)/sizeof(char), (const char *)DEFAULT_IPC_MODE);
		OSAL_strcpy_s(L4Configurations.dSimIpAddress, sizeof(L4Configurations.dSimIpAddress)/sizeof(char), (const char *)DEFAULT_IP);
		OSAL_strcpy_s(L4Configurations.OutputTarget, sizeof(L4Configurations.OutputTarget)/sizeof(char), (const char *)DEFAULT_OUTPUT_TARGET);
		OSAL_strcpy_s(L4Configurations.RootPath, sizeof(L4Configurations.RootPath)/sizeof(char), (const char *)DEFAULT_ROOT_PATH);
		OSAL_strcpy_s(L4Configurations.SdkIpAddress, sizeof(L4Configurations.SdkIpAddress)/sizeof(char), (const char *)DEFAULT_IP);
		OSAL_strcpy_s(L4Configurations.LogPath, sizeof(L4Configurations.LogPath)/sizeof(char), (const char *)DEFAULT_LOG_PATH);
		OSAL_strcpy_s(L4Configurations.CoexistingMode, sizeof(L4Configurations.CoexistingMode)/sizeof(char), (const char *)DEFAULT_COEX_MODE);
		OSAL_strcpy_s(L4Configurations.LogFileName, sizeof(L4Configurations.LogFileName)/sizeof(char), (const char *)DEFAULT_FILE_NAME);
		OSAL_strcpy_s(L4Configurations.TLS_Source, sizeof(L4Configurations.TLS_Source)/sizeof(char), (const char *)DEFAULT_TLS_SOURCE);
		OSAL_strcpy_s(L4Configurations.LED1Behavior, sizeof(L4Configurations.LED1Behavior)/sizeof(char), (const char *)DEFAULT_LED_BEHAVIOR);
		OSAL_strcpy_s(L4Configurations.LED2Behavior, sizeof(L4Configurations.LED2Behavior)/sizeof(char), (const char *)DEFAULT_LED_BEHAVIOR);
		OSAL_strcpy_s(L4Configurations.Installing, sizeof(L4Configurations.Installing)/sizeof(char), (const char *)DEFAULT_FALSE_STR);
		//OSAL_strcpy_s(L4Configurations.InstallationStatus, sizeof(L4Configurations.InstallationStatus)/sizeof(char), (const char *)KEY_VALUE_INSTALLATION_IDLE);
		OSAL_strcpy_s(L4Configurations.ApdoReadFromNvm, sizeof(L4Configurations.ApdoReadFromNvm)/sizeof(char), (const char *)DEFAULT_TRUE_STR);	
		OSAL_strcpy_s(L4Configurations.ApdoDevIDPrefix, sizeof(L4Configurations.ApdoDevIDPrefix)/sizeof(char), (const char *)DEFUALT_APDO_DEV_ID_PREFIX);	
		OSAL_strcpy_s(L4Configurations.ApdoSecureBootstrap, sizeof(L4Configurations.ApdoSecureBootstrap)/sizeof(char), (const char *)DEFAULT_TRUE_STR);	
		OSAL_strcpy_s(L4Configurations.ApdoLeaveDbDefaults, sizeof(L4Configurations.ApdoLeaveDbDefaults)/sizeof(char), (const char *)DEFAULT_FALSE_STR);	
		OSAL_strcpy_s(L4Configurations.ApdoFixSpecialCharacters, sizeof(L4Configurations.ApdoFixSpecialCharacters)/sizeof(char), (const char *)DEFAULT_TRUE_STR);
		OSAL_strcpy_s(L4Configurations.ApdoFumoSwv2String, sizeof(L4Configurations.ApdoFumoSwv2String)/sizeof(char), (const char *)DEFAULT_EMPTY_STR);
		OSAL_strcpy_s(L4Configurations.ApdoSharedSecret, sizeof(L4Configurations.ApdoSharedSecret)/sizeof(char), (const char *)APDO_SECRET);	
		OSAL_strcpy_s(L4Configurations.ApdoCalcSecret, sizeof(L4Configurations.ApdoCalcSecret)/sizeof(char), (const char *)DEFAULT_TRUE_STR);	
		OSAL_strcpy_s(L4Configurations.ApdoMandatoryUpdateLogic, sizeof(L4Configurations.ApdoMandatoryUpdateLogic)/sizeof(char), (const char *)DEFAULT_TRUE_STR);	
		OSAL_strcpy_s(L4Configurations.ApdoFumoDisable, sizeof(L4Configurations.ApdoFumoDisable)/sizeof(char), (const char *)DEFAULT_FALSE_STR);			
		OSAL_strcpy_s(L4Configurations.SupplicantLibName, sizeof(L4Configurations.SupplicantLibName)/sizeof(char), (const char *)DEFAULT_SUPPLICANT_LIB_NAME);			
		bInit = TRUE;
	}
}

BOOL L4Configurations_getEnableInstrumentation(UINT32*answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.EnableInstrumentation, DEFAULT_INSTRUMENTATION_ENABLE_VALUE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_ENABLE_INSTRUMENTATION, answer, __FUNCTION__);
}

BOOL L4Configurations_getInstrumentationLibName(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.InstrumentationLibName, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_INSTRUMENT_LIBNAME, answer, __FUNCTION__);
}

BOOL L4Configurations_getInstrumentationLoadingType(UINT32*answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.InstrumentationLoadingType, DEFUALT_INSTRUMENTATION_LOADING_TYPE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPEDEV, OSAL_INTRUMENTATION_LOADING_TYPE, answer, __FUNCTION__);
}

BOOL L4Configurations_getSupplicantLibName(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.SupplicantLibName, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_SUPPLICANT_LIBNAME, answer, __FUNCTION__);
}

BOOL L4Configurations_getMaxNumOfFiles(UINT32*answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.MaxNumOfFiles, DEFUALT_MAX_NUM_OF_FILES, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPEDEV, OSAL_MAX_NUM_OF_FILES, answer, __FUNCTION__);
}

BOOL L4Configurations_getMaxNumOfDirs(UINT32*answer)
{
		return InitDwordParamFromRegOrDefaultEx(&L4Configurations.MaxNumOfDirs, DEFUALT_MAX_NUM_OF_DIRS, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPEDEV, OSAL_MAX_NUM_OF_DIR, answer, __FUNCTION__);
}

BOOL L4Configurations_getDnDOutputMode(UINT32*answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.DnDOutputMode, DEFUALT_DND_OUTPUT_MODE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DND_OUTPUT_MODE, answer, __FUNCTION__);
}

BOOL L4Configurations_getStartMOCMsgProxy(UINT32*answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.StartMOCMsgProxy, DEFUALT_MOC_MSG_PROXY, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_START_MOC_MSG_PROXY, answer, __FUNCTION__);
}


BOOL L4Configurations_getCommonPriviledgeEnable(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.CommonPriviledgeEnable, DEFAULT_COMMON_PRIVILEGE_ENABLE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COMMON_PRIVILEDGE, answer, __FUNCTION__);
}

BOOL L4Configurations_getPowerSaveEnable(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.PowerSaveEnable, DEFAULT_SLOW_CLOCK_VAL, OSAL_KEY_ENTRY_PIPEGEN, OSAL_SLOW_CLOCK_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getArqSupport(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.ArqSupport, DEFAULT_ARQ_SUPPORT_VAL, OSAL_KEY_ENTRY_PIPEGEN, OSAL_ARQ_SUPPORT_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getEnableSelectivePLIs(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.EnableSelectivePLIs, DEFAULT_ENABLE_SELECTIVE_PLIS_VAL, OSAL_KEY_ENTRY_PIPEGEN, OSAL_ENABLE_SELECTIVE_PLIS_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getDelayedSelectivePLI(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DelayedSelectivePLI, DEFAULT_DELAYED_SELECTIVE_PLI_VAL, OSAL_KEY_ENTRY_PIPEGEN, OSAL_DELAYED_SELECTIVE_PLI_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getConsecutivePLIToReceive(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.ConsecutivePLIToReceive, DEFAULT_CONSECUTIVE_PLI_VAL, OSAL_KEY_ENTRY_PIPEGEN, OSAL_CONSECUTIVE_PLI_val, answer, __FUNCTION__);
}

//BOOL L4Configurations_getInstallationStatus(LPSTR answer)
//{
//	return InitStrParamFromRegOrToDefault(L4Configurations.InstallationStatus, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEAPDO, OSAL_KEY_ENTRY_INSTALLATION_STAUTS, answer, __FUNCTION__);
//}
//
//BOOL L4Configurations_setInstallationStatus(LPSTR value)
//{
//	return WriteSTRParamToRegisrty(L4Configurations.InstallationStatus, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEAPDO, OSAL_KEY_ENTRY_INSTALLATION_STAUTS, value, __FUNCTION__);
//}

BOOL L4Configurations_getInstalling(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.Installing, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEAPDO, OSAL_KEY_ENTRY_INSTALLING, answer, __FUNCTION__);
}

BOOL L4Configurations_setInstalling(LPSTR value)
{
	return WriteSTRParamToRegisrty(L4Configurations.Installing, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEAPDO, OSAL_KEY_ENTRY_INSTALLING, value, __FUNCTION__);
}

BOOL L4Configurations_getNoRealmInNAI(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.NoRealmInNAI, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_NO_REALM_IN_NAI, answer, __FUNCTION__);
}

BOOL L4Configurations_getCustomDecoration(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.CustomDecoration, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_CUSTOM_DECORATION, answer, __FUNCTION__);
}

BOOL L4Configurations_getLED2Behavior(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.LED2Behavior, NUM_OF_LED_BEHAVIOR + 1, OSAL_KEY_ENTRY_PIPECLED, OSAL_LED_LED2_BEHAVIOR, answer, __FUNCTION__);
}

BOOL L4Configurations_getLED1Behavior(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.LED1Behavior, NUM_OF_LED_BEHAVIOR + 1, OSAL_KEY_ENTRY_PIPECLED, OSAL_LED_LED1_BEHAVIOR, answer, __FUNCTION__);
}

BOOL L4Configurations_getPowerSaveInd(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.PowerSaveInd, DEFAULT_POWER_SAVE_IND, OSAL_KEY_ENTRY_PIPECLED, OSAL_LED_POWER_IND, answer, __FUNCTION__);
}

BOOL L4Configurations_getNVMOverride(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.NVMOverride, DEFAULT_NVM_OVERRIDE, OSAL_KEY_ENTRY_PIPECLED, OSAL_LED_NVM_OVERRIDE, answer, __FUNCTION__);
}

BOOL L4Configurations_getNumOfLeds(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.NumOfLeds, DEFAULT_NUM_OF_LEDS, OSAL_KEY_ENTRY_PIPECLED, OSAL_LED_NUM_OF_LEDS, answer, __FUNCTION__);
}

BOOL L4Configurations_getPrivilegeKey(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.PrivilegeKey, PRIVILEGE_KEY_SIZE, OSAL_KEY_ENTRY_PIPEGEN_PRIVILEGE, OSAL_PRIVILEGE_KEY_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getTLS_Source(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.TLS_Source, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_TLS_SOURCE, answer, __FUNCTION__);
}

BOOL L4Configurations_getResetOnAssert(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.ResetOnAssert, DEFAULT_RESET_ON_ASSERT, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_RESET_ON_ASSERT_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getHarqCategory(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.HarqCategory, DEFAULT_HARQ_CATEGORY, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_HARQ_CATEGORY_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getD2HDataFormat(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.D2HDataFormat, DEFAULT_D2H_DATA_FORMAT, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_D2H_DATA_FORMAT_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getDLHostReorder(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DLHostReorder, DEFAULT_DL_HOST_REORDER, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_DL_HOST_REORDER_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getCSType(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.CSType, DEFAULT_CS_TYPE, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_CS_TYPE_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getPaddingSize(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.PaddingSize, DEFAULT_PADDING_SIZE, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_PADDING_SIZE_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getLoopBack(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.LoopBack, DEFAULT_LOOP_BACK, OSAL_KEY_ENTRY_PIPEGEN, OSAL_LOOP_BACK_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getPrivilegeEnable(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.PrivilegeEnable, DEFAULT_PRIVILEGE_ENABLE, OSAL_KEY_ENTRY_PIPEGEN_PRIVILEGE, OSAL_PRIVILEGE_ENABLE_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getShowUnkownNSPs(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.ShowUnknownNSPs, DEFAULT_SHOW_UNKNOWN_NSPS, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_SHOW_UNKNOWN_NSPS, answer, __FUNCTION__);
}

BOOL L4Configurations_getDhcpDomain(LPSTR answer, LPCSTR regKey ,LPSTR interfaceGUIID)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.DhcpDomain, MAX_SIZE_OF_REALM_NAME, regKey, interfaceGUIID, answer, __FUNCTION__);
}

BOOL L4Configurations_getDoNotUsePseudoNAI(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DoNotUsePseudoNAI, DEFAULT_DO_NOT_USE_PSEUDO_NAI, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DO_NOT_USE_PSEUDO_NAI, answer, __FUNCTION__);
}
BOOL L4Configurations_getLimitMaxTxPower(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.LimitMaxTxPower, DEFAULT_MAX_TX_POWER, OSAL_KEY_ENTRY_PIPEGEN, OSAL_LIMIT_MAX_TX_POWER_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getWatchDogTimer(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.WatchDogTimer, DEFAULT_WATCHDOG_TIMER, OSAL_KEY_ENTRY_PIPEGEN, OSAL_WATCH_DOG_TIMER_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getPbLog(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.PbLog, DEFAULT_USE_PB_LOG, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_PB_LOG, answer, __FUNCTION__);
}

BOOL L4Configurations_getLinkDownTimer(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.LinkDownTimer, DEFAULT_LINK_LOSS_TIMER, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_LINK_DOWN_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getIdleTimeout(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.IdleTimeout, DEFAULT_IDLE_TIMEOUT, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_IDLE_TIMEOUT_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getIdlePagingInterval(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.IdlePagingInterval, DEFAULT_IDLE_PAGING_INTERVAL, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_IDLE_PAGING_INTERVAL_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getIdleEntrySuspend(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.IdleEntrySuspend, DEFAULT_IDLE_ENTRY_SUSPEND, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_IDLE_ENTRY_SUSPEND_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getFullNeSuspend(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.FullNeIdleSuspend, DEFAULT_FULL_NE_SUSPEND, OSAL_KEY_ENTRY_PIPEGEN, OSAL_GEN_FULL_NE_SUSPEND_val, answer, __FUNCTION__);
}

BOOL L4Configurations_getNoXohmGroups(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.NoXohmGroups, DEFAULT_NO_XOHM_GROUPS, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_NO_XOHM_GROUPS, answer, __FUNCTION__);
}

BOOL L4Configurations_getNoSM(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.NoSM, DEFAULT_NO_SM, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_NO_SM_DECORATION, answer, __FUNCTION__);
}

BOOL L4Configurations_getDisableDiscovery(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DisableDiscovery, DEFAULT_DISABLE_DISCOVERY, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DISABLE_DISCOVERY, answer, __FUNCTION__);
}

BOOL L4Configurations_getInterval(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.Interval, DEFAULT_INTERVAL, OSAL_KEY_ENTRY_PIPECLED, OSAL_LED_INTERVAL, answer, __FUNCTION__);
}

BOOL L4Configurations_getLedBlinkRate(UINT8 LEDBlinkRate[], LPCTSTR name_of_subkey)
{
	OSAL_VALENT Valent[NUM_OF_LED_BLINK_RATE];
	int i;
	BOOL readFromReg;
	char regBuffer [1024];
		
	for(i=0; i<NUM_OF_LED_BLINK_RATE; i++)
	{
		Valent[i].ve_valuename = OSAL_LED_REG_ARR[i];
	}

	readFromReg = OSAL_ConfigController_GetMultValues(name_of_subkey, Valent, NUM_OF_LED_BLINK_RATE, regBuffer, sizeof(regBuffer));
	if (readFromReg)
	{
		if(OSAL_stricmp(name_of_subkey, OSAL_KEY_ENTRY_PIPELED_BLINK_ON) == 0)
		{
			for (i=0;i<NUM_OF_LED_BLINK_RATE;i++)
			{
				L4Configurations.OnBlinkRate[i] = (*(UINT8 *)(Valent[i].ve_valueptr));
				LEDBlinkRate[i] = L4Configurations.OnBlinkRate[i];
			}
		}
		else
		{
			for (i=0;i<NUM_OF_LED_BLINK_RATE;i++)
			{
				L4Configurations.OffBlinkRate[i] = (*(UINT8 *)(Valent[i].ve_valueptr));
				LEDBlinkRate[i] = L4Configurations.OffBlinkRate[i];
			}
		}
	}
	
	return readFromReg;
}

BOOL L4Configurations_getConnectTime(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.ConnectTime, DEFAULT_CONNECT_TIME, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_CONNECT_TIME, answer, __FUNCTION__);
}

BOOL L4Configurations_getFALL_TO_XOR_TIMEOUT(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.FALL_TO_XOR_TIMEOUT, DEFAULT_FALL_TO_XOR_TIMEOUT, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COEXISTING_TIMEOUT, answer, __FUNCTION__);	
}

BOOL L4Configurations_getLogFileName(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.LogFileName, MAX_FILENAME_LEN, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_FILE_NAME, answer, __FUNCTION__);
}

BOOL L4Configurations_getCoexistingMode(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.CoexistingMode, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COEXISTING_MODE, answer, __FUNCTION__);
}

BOOL L4Configurations_getDumpEnable(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DumpEnable, FALSE, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_DUMP, answer, __FUNCTION__);
}

BOOL L4Configurations_getDriverMode(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.DriverMode, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DRIVER_OR_DSIM, answer, __FUNCTION__);
}

BOOL L4Configurations_getIPCMode(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.IPCMode, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_IPC, answer, __FUNCTION__);
}

BOOL L4Configurations_getDSimIndicationsPortNum(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.dSimIndicationsPortNum, DEFAULT_DSIM_IND_PORT_NUM, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DSIM_INDS_PORT_NUM, answer, __FUNCTION__);
}

BOOL L4Configurations_getDSimIpAddress(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.dSimIpAddress, IP_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DSIM_IPADDRESS, answer, __FUNCTION__);
}

BOOL L4Configurations_getDSimOidsPortNum(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.dSimOidsPortNum, DEFAULT_DSIM_OIDS_PORT_NUM, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DSIM_OIDS_PORT_NUM, answer, __FUNCTION__);
}

BOOL L4Configurations_getEnableVersioning(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.EnableVersioning, DEFAULT_ENABLE_VERSIONING, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_USE_VERSIONING, answer, __FUNCTION__);
}

BOOL L4Configurations_getGetDeviceTraces(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.GetDeviceTraces, DEFAULT_DEVICE_TRACES, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_GET_DEVICES_TRACE, answer, __FUNCTION__);
}

BOOL L4Configurations_getModeOfOperationProduction(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.ModeOfOperationProduction, DEFAULT_MODE_OF_OP_PROD, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_MODE_OF_OPERATION_PROD, answer, __FUNCTION__);	
}

BOOL L4Configurations_getOutputTarget(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.OutputTarget, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_TARGET, answer, __FUNCTION__);
}

BOOL L4Configurations_getSdkIpAddress(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.SdkIpAddress, IP_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_IP_ADDRESS, answer, __FUNCTION__);
}

BOOL L4Configurations_getSdkPortNum(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.SdkPortNum, DEFAULT_SDK_PORT_NUM, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_SDK_PORT, answer, __FUNCTION__);
}

BOOL L4Configurations_getDnDOutputPortNum(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DnDOutputPortNum, DEFAULT_DND_OUTPUT_PORT_NUM, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DND_OUTPUT__PORT, answer, __FUNCTION__);
}

BOOL L4Configurations_getStartWatchdog(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.StartWatchdog, DEFAULT_START_WATCHDOG, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_START_WATCHDOG, answer, __FUNCTION__);
}

BOOL L4Configurations_getLogPath(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.LogPath, MAX_FILENAME_LEN, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_LOG_PATH, answer, __FUNCTION__);
}

BOOL L4Configurations_getModules(UINT32 *answer)
{
 	return InitDwordParamFromRegOrDefault(&L4Configurations.Modules, DEFAULT_MODULES, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_MODULES, answer, __FUNCTION__);
}

BOOL L4Configurations_getSeverities(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.Severities, DEFAULT_SEVERITIES, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_SEVERITIES, answer, __FUNCTION__);
}

BOOL L4Configurations_getUseNewTraces(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.UseNewTraces, DEFAULT_USENEWTRACES, OSAL_KEY_ENTRY_PIPETRACE, OSAL_KEY_ENTRY_USE_NEW_TRACES, answer, __FUNCTION__);
}

BOOL L4Configurations_getRootPath(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.RootPath, MAX_REGISTRY_ANSWER, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_ROOT_PATH, answer, __FUNCTION__);}

BOOL L4Configurations_getTracePath(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.TracePath, MAX_REGISTRY_ANSWER, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_TRC_PATH, answer, __FUNCTION__);
}

BOOL L4Configurations_getAPDOLinkUpSleep(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.ApdoLinkUpSleep, DEFUALT_APDO_LINK_UP_SLEEP, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_APDO_LINK_UP_SLEEP, answer, __FUNCTION__);
}

BOOL L4Configurations_getAPDOAfterLinkUpSleep(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.ApdoAfterLinkUpSleep, DEFUALT_APDO_AFTER_LINK_UP_SLEEP, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_APDO_AFTER_LINK_UP_SLEEP, answer, __FUNCTION__);
}

BOOL L4Configurations_getAPDOLinkUpRetries(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.ApdoLinkUpRetries, DEFUALT_APDO_LINK_UP_RETRIES, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_APDO_LINK_UP_RETRIES, answer, __FUNCTION__);
}

BOOL L4Configurations_setPackagePath(LPSTR value)
{
	return WriteSTRParamToRegisrty(L4Configurations.PackageName, MAX_REGISTRY_ANSWER, OSAL_KEY_ENTRY_PIPEAPDO, OSAL_KEY_ENTRY_PACKAGE_NAME, value, __FUNCTION__);
}

BOOL L4Configurations_getAPDOReadFromNvm(LPSTR  answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoReadFromNvm, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_READ_FROM_NVM, answer, __FUNCTION__);
}

BOOL L4Configurations_getAPDODevIdPrefix(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevIDPrefix, DEV_ID_PREFIX_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_DEV_ID_PREFIX, answer, __FUNCTION__);
}

BOOL L4Configurations_getAPDOSecureBootstrap(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoSecureBootstrap, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_SECURE_BOOTSTRAP, answer, __FUNCTION__);	
}

BOOL L4Configurations_getAPDOLeaveDbDefaults(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoLeaveDbDefaults, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_LEAVE_DB_DEFAULTS, answer, __FUNCTION__);
}

BOOL L4Configurations_getAPDOFixSpecialCharacters(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoFixSpecialCharacters, DEFULT_STR_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_FIX_SPECIAL_CHARACTERS, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoFumoSwv2String(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoFumoSwv2String, MAX_REGISTRY_ANSWER, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_FUMO_SWV2_STRING, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoTerminalEquipmentManID(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoTerminalEquipmentManID, (WMX_MANUFACTURER_NAME_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_TERM_EQUIPMENT, OSAL_KEY_ENTRY_TERM_EQUIPMENT_MANUFACTURER_ID, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoTerminalEquipmentModel(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoTerminalEquipmentModel, (WMX_MODEL_TYPE_NAME_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_TERM_EQUIPMENT, OSAL_KEY_ENTRY_TERM_EQUIPMENT_MODEL, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoTerminalEquipmentFwV(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoTerminalEquipmentFwV, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_TERM_EQUIPMENT, OSAL_KEY_ENTRY_TERM_EQUIPMENT_FWV, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoTerminalEquipmentHwV(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoTerminalEquipmentHwV, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_TERM_EQUIPMENT, OSAL_KEY_ENTRY_TERM_EQUIPMENT_HWV, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoTerminalEquipmentDevID(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoTerminalEquipmentDevID, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_TERM_EQUIPMENT, OSAL_KEY_ENTRY_TERM_EQUIPMENT_DEV_ID, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoTerminalEquipmentDevType(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoTerminalEquipmentDevType, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_TERM_EQUIPMENT, OSAL_KEY_ENTRY_TERM_EQUIPMENT_DEV_TYPE, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoDevInfoManID(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevInfoManID, (WMX_MANUFACTURER_NAME_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_DEV_INFO, OSAL_KEY_ENTRY_DEV_INFO_MANUFACTURER_ID, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoDevInfoModel(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevInfoModel, (WMX_MODEL_TYPE_NAME_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_DEV_INFO, OSAL_KEY_ENTRY_DEV_INFO_MODEL, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoDevDetailsDevType(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevDetailsDevType, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_DEV_INFO, OSAL_KEY_ENTRY_DEV_DETAILS_DEV_TYPE, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoDevDetailsFwV(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevDetailsFwV, WMX_DEVICE_VERSION_MAX_LENGTH - 1, OSAL_KEY_ENTRY_DEV_INFO, OSAL_KEY_ENTRY_DEV_DETAILS_FWV, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoDevDetailsHwV(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevDetailsHwV, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_DEV_INFO, OSAL_KEY_ENTRY_DEV_DETAILS_HWV, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoDevDetailsSwV(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoDevDetailsSwV, (WMX_DEVICE_VERSION_MAX_LENGTH / 2) - 1, OSAL_KEY_ENTRY_DEV_INFO, OSAL_KEY_ENTRY_DEV_DETAILS_SWV, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoPackageUpdateSleep(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefaultEx(&L4Configurations.ApdoPackageUpdateSleep, DEFUALT_APDO_PACKAGE_UPDATE_SLEEP, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_APDO_PACKAGE_UPDATE_SLEEP, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoSharedSecret(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoSharedSecret, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_SHARED_SECRET, answer, __FUNCTION__);
}

BOOL L4Configurations_getDisableFastReconnect(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DisableFastReconnect, DEFAULT_DISABLE_FAST_RECONNECT, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DISABLE_FAST_RECONNECT, answer, __FUNCTION__);
}

BOOL L4Configurations_getDisableRobustConnect(UINT32 *answer)
{
	return InitDwordParamFromRegOrDefault(&L4Configurations.DisableRobustConnect, DEFAULT_DISABLE_ROBUST_CONNECT, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_DISABLE_ROBUST_CONNECT, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoCalcSecret(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoCalcSecret, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_CALC_SECRET, answer, __FUNCTION__);
}

BOOL L4Configurations_getApdoMandatoryUpdateLogic(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoMandatoryUpdateLogic, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_MANDATORY_UPDATE_LOGIC, answer, __FUNCTION__);
}

BOOL L4Configurations_getDndFilesPath(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.dndFilesPath , MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_DND_OUTPUT_FILES_PATH, answer, __FUNCTION__);
}

BOOL L4Configurations_setDndFilesPath(LPSTR value)
{
	return WriteSTRParamToRegisrty(L4Configurations.dndFilesPath , MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_DND_OUTPUT_FILES_PATH, value, __FUNCTION__);
}

BOOL L4Configurations_getApdoFumoDisable(LPSTR answer)
{
	return InitStrParamFromRegOrToDefault(L4Configurations.ApdoFumoDisable, MAX_ANSWER_SIZE, OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_APDO_FUMO_DISABLE, answer, __FUNCTION__);
}

BOOL L4Configurations_getInterfaceName(char *answer)
{
	BOOL readFromReg;
	char regInterfaceName[DEFULT_STR_SIZE];

	readFromReg =
	    OSAL_ConfigController_GetStrValue(OSAL_KEY_ENTRY_PIPECONFIG, KEY_ENTRY_INTERFACE_NAME,
			       (char *)regInterfaceName, DEFULT_STR_SIZE);
	OSAL_strcpy_s(answer, DEFULT_STR_SIZE, regInterfaceName);
	return readFromReg;
}


//
//This function initializes a (string) db field from the registry (HKEY_LOCAL_MACHINE branch) 
//according to the regKey and regName parameters. 
//It returns TRUE if the read from registry succeeded or FALSE otherwise.
//The answer parameter is an out parameter which contains the db field value.
//In case the registry read fails, the answer parameter is initialized with the db field value prior to the registry read.
//(that's its default value) 
//
//The callingFunctionName parameter is for logging purposes only
//
BOOL InitStrParamFromRegOrToDefault(LPSTR pDBStrParam, UINT32 size, LPCTSTR regKey, LPCTSTR regName, LPSTR answer, LPCSTR callingFuncName)
{
	BOOL readFromReg = FALSE;
	char regVal[MAX_REGISTRY_ANSWER] = {0}; //Should be big enough to support sizes of all fields....
	UNREFERENCED_PARAMETER(callingFuncName);

	//Read value from registry - if succeeded copy it to the DB param
	readFromReg = OSAL_ConfigController_GetStrValue(regKey, regName, regVal, MAX_REGISTRY_ANSWER);
	if (readFromReg)
	{
		OSAL_strncpy_s(pDBStrParam, size, regVal, _TRUNCATE);
	}

	//now copy DB param to the answer. 
	//In case the read from registry has failed the current (default value) will be copied
	OSAL_strncpy_s(answer, size, pDBStrParam, _TRUNCATE);

	//log the results...
	TRACE(TR_MOD_CONFIGURATION, TR_SEV_INFO,"calling function: '%s'. config param %s\\%s = %s , source=%s", callingFuncName, regKey, regName, answer, readFromReg?"Registry":"Code");
	
	return readFromReg;
}

//
//This function writes a (string) db field to the registry (HKEY_LOCAL_MACHINE branch) 
//according to the regKey and regName parameters. 
//It returns TRUE if the write to the registry succeeded or FALSE otherwise.
//
//The callingFunctionName parameter is for logging purposes only
//
BOOL WriteSTRParamToRegisrty(LPSTR pDBStrParam, UINT32 size, LPCSTR regKey, LPSTR regName, LPSTR value, LPSTR callingFuncName)
{
	BOOL writeRes;

	UNREFERENCED_PARAMETER(callingFuncName);

	writeRes = OSAL_ConfigController_SetStrValue( regKey, regName, value);

	if (writeRes)
	{
		OSAL_strncpy_s(pDBStrParam, size, value, _TRUNCATE);
		TRACE(TR_MOD_CONFIGURATION, TR_SEV_INFO,"calling function: '%s'. Config param %s\\%s = %s", callingFuncName, regKey, regName, value);
	}
	else
	{
		TRACE(TR_MOD_CONFIGURATION, TR_SEV_NOTICE,"calling function: '%s'. Seting config param %s\\%s to value %s failed.", callingFuncName, regKey, regName, value);
	}	

	return writeRes;
}

//
//This function initializes a (UINT32) db field from the registry (HKEY_LOCAL_MACHINE branch) 
//according to the regKey and regName parameters. 
//It returns TRUE if the read from registry succeeded or FALSE otherwise.
//The outValue parameter is an out parameter which contains the db field value.
//In case the registry read fails, the outValue parameter is initialized with the db field value prior to the registry read.
//(that's its default value) 
//
//The callingFunctionName parameter is for logging purposes only
//
BOOL InitDwordParamFromRegOrDefault(UINT32 *pDBDwordParam, UINT32 defaultVal, LPCTSTR regKey, LPCTSTR regName, UINT32 *outValue, LPCSTR callingFuncName)
{
	BOOL readFromReg;
	UINT32 regDwordVal;
	
	UNREFERENCED_PARAMETER(callingFuncName);

	//Set to default
	*pDBDwordParam = defaultVal;

	//Read value from registry - if succeeded copy it to the DB param
	readFromReg = OSAL_ConfigController_GetNumValue(regKey, regName, &regDwordVal);
	if (readFromReg)
	{
		*pDBDwordParam = regDwordVal;
	}

	//now copy DB param to the answer. 
	//In case the read from registry has failed the current (default value) will be copied
	*outValue = *pDBDwordParam;

	//log the results...
	TRACE(TR_MOD_CONFIGURATION, TR_SEV_INFO,"calling function: '%s'. config param %s\\%s = %d , source=%s", callingFuncName, regKey, regName, *outValue, readFromReg?"Registry":"Default");

	return readFromReg;
}

//
//This function initializes a (UINT32) db field from the registry (HKEY_LOCAL_MACHINE branch) 
//according to the regKey and regName parameters. 
//It first tries to read the value according to regKey1 parameter, 
//if fails it tries to read the value according to regKey2 parameter.
//It returns TRUE if either of the reads from registry succeeded, or FALSE otherwise.
//The outValue parameter is an out parameter which contains the db field value.
//In case the registry read fails, the outValue parameter is initialized with the db field value prior to the registry read.
//(that's its default value) 
//
//The callingFunctionName parameter is for logging purposes only
//
BOOL InitDwordParamFromRegOrDefaultEx(UINT32 *pDBDwordParam, UINT32 defaultVal, LPCTSTR regKey1, LPCTSTR regKey2, LPCTSTR regName, UINT32 *outValue, LPCSTR callingFuncName)
{
	BOOL readFromReg;
	UINT32 regDwordVal;
	LPCTSTR regKey = NULL;

	UNREFERENCED_PARAMETER(callingFuncName);

	//Set to default
	*pDBDwordParam = defaultVal;

	//Read value from registry - if succeeded copy it to the DB param
	readFromReg = OSAL_ConfigController_GetNumValue(regKey1, regName, &regDwordVal);
	if (readFromReg)
	{
		*pDBDwordParam = regDwordVal;
		regKey = regKey1;
	}
	else
	{
		readFromReg = OSAL_ConfigController_GetNumValue(regKey2, regName, &regDwordVal);
		if (readFromReg)
		{
			*pDBDwordParam = regDwordVal;
			regKey = regKey2;
		}		
	}

	//now copy DB param to the answer. 
	//In case the read from registry has failed the current (default value) will be copied
	*outValue = *pDBDwordParam;

	//log the results...
	if (regKey != NULL)
	{
		TRACE(TR_MOD_CONFIGURATION, TR_SEV_INFO,"calling function: '%s'. config param %s\\%s = %d , source=%s", callingFuncName, regKey, regName, *outValue, readFromReg?"Registry":"Default");
	}
	

	return readFromReg;
}

