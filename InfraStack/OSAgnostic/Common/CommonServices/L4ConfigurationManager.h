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
#ifndef L4_CONFIGURATION_MANAGER
#define L4_CONFIGURATION_MANAGER

#include "wimax_osal_config_controler.h"

// Initializes L4Configurations to default values.
BOOL L4Configurations_getInstrumentationLibName(LPSTR answer);
BOOL L4Configurations_getInstrumentationLoadingType(UINT32*answer);
BOOL L4Configurations_getEnableInstrumentation(UINT32*answer);
BOOL L4Configurations_getSupplicantLibName(LPSTR answer);
BOOL L4Configurations_getMaxNumOfFiles(UINT32*answer);
BOOL L4Configurations_getMaxNumOfDirs(UINT32*answer);
BOOL L4Configurations_getDnDOutputMode(UINT32*answer);
void L4Configurations_init();
BOOL L4Configurations_getStartMOCMsgProxy(UINT32 *answer);
BOOL L4Configurations_getDriverMode(LPSTR answer);
BOOL L4Configurations_getIPCMode(LPSTR answer);
BOOL L4Configurations_getDSimIndicationsPortNum(UINT32 *answer);
BOOL L4Configurations_getDSimIpAddress(LPSTR answer);
BOOL L4Configurations_getDSimOidsPortNum(UINT32 *answer);
BOOL L4Configurations_getEnableVersioning(UINT32 *answer);
BOOL L4Configurations_getGetDeviceTraces(UINT32 *answer);
BOOL L4Configurations_getModeOfOperationProduction(UINT32 *answer);
BOOL L4Configurations_getOutputTarget(LPSTR answer);
BOOL L4Configurations_getSdkIpAddress(LPSTR answer);
BOOL L4Configurations_getSdkPortNum(UINT32 *answer);
BOOL L4Configurations_getDnDOutputPortNum(UINT32 *answer);
BOOL L4Configurations_getStartWatchdog(UINT32 *answer);
BOOL L4Configurations_getLogPath(LPSTR answer);
BOOL L4Configurations_getModules(UINT32 *answer);
BOOL L4Configurations_getSeverities(UINT32 *answer);
BOOL L4Configurations_getUseNewTraces(UINT32 *answer);
BOOL L4Configurations_getDumpEnable(UINT32 *answer);
BOOL L4Configurations_getCoexistingMode(LPSTR answer);
BOOL L4Configurations_getLogFileName(LPSTR answer);
BOOL L4Configurations_getFALL_TO_XOR_TIMEOUT(UINT32 *answer);
BOOL L4Configurations_getConnectTime(UINT32 *answer);
BOOL L4Configurations_getDisableDiscovery(UINT32 *answer);
BOOL L4Configurations_getIdleTimer(UINT32 *answer);
BOOL L4Configurations_getLinkDownTimer(UINT32 *answer);
BOOL L4Configurations_getPbLog(UINT32 *answer);
BOOL L4Configurations_getWatchDogTimer(UINT32 *answer);
BOOL L4Configurations_getLimitMaxTxPower(UINT32 *answer);
BOOL L4Configurations_getPrivilegeEnable(UINT32 *answer);
BOOL L4Configurations_getShowUnkownNSPs(UINT32 *answer);
BOOL L4Configurations_getDhcpDomain(LPSTR answer, LPCSTR regKey ,LPSTR interfaceGUIID);
BOOL L4Configurations_getDoNotUsePseudoNAI(UINT32 *answer);
BOOL L4Configurations_getLoopBack(UINT32 *answer);
BOOL L4Configurations_getResetOnAssert(UINT32 *answer);
BOOL L4Configurations_getHarqCategory(UINT32 *answer);
BOOL L4Configurations_getTLS_Source(LPSTR answer);
BOOL L4Configurations_getInterval(UINT32 *answer);
BOOL L4Configurations_getPrivilegeKey(LPSTR answer);
BOOL L4Configurations_getNumOfLeds(UINT32 *answer);
BOOL L4Configurations_getNVMOverride(UINT32 *answer);
BOOL L4Configurations_getPowerSaveInd(UINT32 *answer);
BOOL L4Configurations_getLED1Behavior(LPSTR answer);
BOOL L4Configurations_getLED2Behavior(LPSTR answer);
BOOL L4Configurations_getNoRealmInNAI(LPSTR answer);
BOOL L4Configurations_getInstalling(LPSTR answer);
BOOL L4Configurations_setInstalling(LPSTR value);
//BOOL L4Configurations_getInstallationStatus(LPSTR answer);
//BOOL L4Configurations_setInstallationStatus(LPSTR value);
BOOL L4Configurations_getLedBlinkRate(UINT8 LEDBlinkRate[], LPCTSTR name_of_subkey);
BOOL L4Configurations_getArqSupport(UINT32 *answer);
BOOL L4Configurations_getD2HDataFormat(UINT32 *answer);
BOOL L4Configurations_getDLHostReorder(UINT32 *answer);
BOOL L4Configurations_getCSType(UINT32 *answer);
BOOL L4Configurations_getPaddingSize(UINT32 *answer);
BOOL L4Configurations_getPowerSaveEnable(UINT32 *answer);
BOOL L4Configurations_getEnableSelectivePLIs(UINT32 *answer);
BOOL L4Configurations_getDelayedSelectivePLI(UINT32 *answer);
BOOL L4Configurations_getConsecutivePLIToReceive(UINT32 *answer);
BOOL L4Configurations_getIdleTimeout(UINT32 *answer);
BOOL L4Configurations_getIdlePagingInterval(UINT32 *answer);
BOOL L4Configurations_getIdleEntrySuspend(UINT32 *answer);
BOOL L4Configurations_getFullNeSuspend(UINT32 *answer);
BOOL L4Configurations_getCommonPriviledgeEnable(UINT32 *answer);
BOOL L4Configurations_getAPDOLinkUpSleep(UINT32 *answer);
BOOL L4Configurations_getAPDOAfterLinkUpSleep(UINT32 *answer);
BOOL L4Configurations_getAPDOLinkUpRetries(UINT32 *answer);
BOOL L4Configurations_getNoSM(UINT32 *answer);
BOOL L4Configurations_getCustomDecoration(LPSTR answer);
BOOL L4Configurations_getNoXohmGroups(UINT32 *answer);
BOOL L4Configurations_getRootPath(LPSTR answer);
BOOL L4Configurations_getTracePath(LPSTR answer);
BOOL L4Configurations_setPackagePath(LPSTR value);
BOOL L4Configurations_getAPDOReadFromNvm(LPSTR answer);
BOOL L4Configurations_getAPDODevIdPrefix(LPSTR answer);
BOOL L4Configurations_getAPDOSecureBootstrap(LPSTR answer);
BOOL L4Configurations_getAPDOLeaveDbDefaults(LPSTR answer);
BOOL L4Configurations_getAPDOFixSpecialCharacters(LPSTR answer);
BOOL L4Configurations_getApdoFumoSwv2String(LPSTR answer);
BOOL L4Configurations_getApdoTerminalEquipmentManID(LPSTR answer);
BOOL L4Configurations_getApdoTerminalEquipmentModel(LPSTR answer);
BOOL L4Configurations_getApdoTerminalEquipmentFwV(LPSTR answer);
BOOL L4Configurations_getApdoTerminalEquipmentHwV(LPSTR answer);
BOOL L4Configurations_getApdoTerminalEquipmentDevID(LPSTR answer);
BOOL L4Configurations_getApdoTerminalEquipmentDevType(LPSTR answer);
BOOL L4Configurations_getApdoDevInfoManID(LPSTR answer);
BOOL L4Configurations_getApdoDevInfoModel(LPSTR answer);
BOOL L4Configurations_getApdoDevDetailsDevType(LPSTR answer);
BOOL L4Configurations_getApdoDevDetailsFwV(LPSTR answer);
BOOL L4Configurations_getApdoDevDetailsHwV(LPSTR answer);
BOOL L4Configurations_getApdoDevDetailsSwV(LPSTR answer);
BOOL L4Configurations_getApdoPackageUpdateSleep(UINT32 *answer);
BOOL L4Configurations_getDndFilesPath(LPSTR answer);
BOOL L4Configurations_setDndFilesPath(LPSTR value);
BOOL L4Configurations_getApdoSharedSecret(LPSTR answer);
BOOL L4Configurations_getApdoCalcSecret(LPSTR answer);
BOOL L4Configurations_getApdoMandatoryUpdateLogic(LPSTR answer);
BOOL L4Configurations_getDisableFastReconnect(UINT32 *answer);
BOOL L4Configurations_getDisableRobustConnect(UINT32 *answer);
BOOL L4Configurations_getApdoFumoDisable(LPSTR answer);
BOOL L4Configurations_getInterfaceName(char *answer);	

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
BOOL InitStrParamFromRegOrToDefault(LPSTR pDBStrParam, UINT32 size, LPCTSTR regKey, LPCTSTR regName, LPSTR answer, LPCSTR callingFuncName);

//
//This function writes a (string) db field to the registry (HKEY_LOCAL_MACHINE branch) 
//according to the regKey and regName parameters. 
//It returns TRUE if the write to the registry succeeded or FALSE otherwise.
//
//The callingFunctionName parameter is for logging purposes only
//
BOOL WriteSTRParamToRegisrty(LPSTR pDBStrParam, UINT32 size, LPCTSTR regKey, LPSTR regName, LPSTR value, LPSTR callingFuncName);

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
BOOL InitDwordParamFromRegOrDefault(UINT32 *pDBDwordParam, UINT32 defaultVal, LPCTSTR regKey, LPCTSTR regName, UINT32 *outValue, LPCSTR callingFuncName);


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
BOOL InitDwordParamFromRegOrDefaultEx(UINT32 *pDBDwordParam, UINT32 defaultVal, LPCTSTR regKey1, LPCTSTR regKey2, LPCTSTR regName, UINT32 *outValue, LPCSTR callingFuncName);

#endif // L4_CONFIGURATION_MANAGER