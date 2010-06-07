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
#ifndef _CONFIG_CONTROLLER_H_
#define _CONFIG_CONTROLLER_H_


#include <stdlib.h>

#include "wimax_osal_linux_types.h"
#include "XmlParser.h"

#include "wimax_osal_win_config_controller_defines.h"

// to force recompilation of this file everytime configure is run which can change some macros used in this file
#include "wns-version.h"
#define MAX_ANSWER_SIZE 	512
#define MAX_REGISTRY_ANSWER 1024
#define NUM_OF_LED_BLINK_RATE 14
#define NUM_OF_LED_BEHAVIOR 14
#define PRIVILEGE_KEY_SIZE 8
#define MAX_SIZE_OF_NSP_NAME       (128+1)
#define MAX_FILENAME_LEN            256
#define IP_STR_SIZE                 32
#define DEFULT_STR_SIZE             8


#define DEV_ID_PREFIX_SIZE			10
#define DEFAULT_EMPTY_STR			""
#define DEFAULT_TRUE_STR			"True"

#define SYSTEM_FILE_NOT_FOUND		2

#define MAX_DEVICE_VERSION	50
#define MAX_MODEL_TYPE_NAME	126
#define MAX_MANUFACTURER_NAME	126

// Default Configuration file
#define CONFIG_XMLFILE  PKG_SYSCONF_DIR "/config.xml"
#define CONFIG_XMLFILE_TMP  PKG_SYSCONF_DIR "/config.xml.tmp"

// Top Element Name
#define CONFIG_INTEL_WIMAX "Intel_WiMAX"

// Comment the following line to disable monitoring
#define ENABLE_MONITORING

// Deafult constants for the configuration
#define DEFAULT_ROOT_PATH             ""
#define DEFAULT_NETWORK_CONFIG_PATH   PKG_DATA_DIR
#define DEFAULT_LOG_PATH              PKG_VAR_LOG_DIR
//#define DEFAULT_SUPPLICANT_LIB_PATH   "/usr/lib/wimax"   // TEDD_REMOVE_IF_SANITY_PASS
#define DEFAULT_SUPPLICANT_LIB_NAME	LIB_DIR "/libwpa_wimax_supplicant.so"
#define DEFAULT_CONFIG_PATH 	 	PKG_SYSCONF_DIR

// Constants
//#define KEY_VALUE_INSTALLATION_COMPLETED "Completed"
#define KEY_VALUE_INSTALLATION_COMPLETED_SUCCESSFUL "Completed Successful"
#define KEY_VALUE_INSTALLATION_COMPLETED_FAILED "Completed Failed"
#define KEY_VALUE_INSTALLATION_IDLE      "Idle"

// Optional entries (Linux)
#define KEY_ENTRY_NETWORK_CONFIG_PATH "NetworkConfigPath"
#define KEY_ENTRY_SUPPLICANT_LIB_PATH "SupplicantLibPath"
#define KEY_ENTRY_SUPPLICANT_LIB_NAME "SupplicantLibName"


#define KEY_ENTRY_INSTRUMENTATION_LIB_NAME 	"InstrumentationLibrary"
#define KEY_ENTRY_ENABLE_INSTRUMENTATION	"EnableInstrumentation"

#define KEY_ENTRY_ROOT_PATH          "RootPath"


//## Token INTRUMENTATION_LOADING_TYPE
//## Type DWORD
//## Value 0
//## Comment How to load instrumentation module. 0 - statically, 1 - dynamically.
#define OSAL_INTRUMENTATION_LOADING_TYPE "IntrumentationLoadingType"

#define  KEY_ENTRY_COEXISTING_MODE    "CoexistingMode"

#define KEY_ENTRY_COEXISTING_TIMEOUT "FALL_TO_XOR_TIMEOUT"

#define MAX_NUM_OF_DIR			"MaxNumberOfDir"

#define KEY_ENTRY_SHOW_UNKNOWN_NSPS	"ShowUnkownNSPs"

#define KEY_ENTRY_DO_NOT_USE_PSEUDO_NAI "DoNotUsePseudoNAI"

#define KEY_ENTRY_CONNECT_TIME       "ConnectTime"

#define KEY_ENTRY_NO_XOHM_GROUPS    "NoXohmGroups"

#define KEY_ENTRY_NO_SM_DECORATION       "NoSM"

#define KEY_ENTRY_CUSTOM_DECORATION      "Decoration"

#define KEY_ENTRY_DISABLE_DISCOVERY  "DisableDiscovery"

#define KEY_ENTRY_NO_REALM_IN_NAI    "NoRealmInNAI"

#define KEY_ENTRY_DRIVER_OR_DSIM     "DriverOrDSim"

#define KEY_ENTRY_DSIM_IPADDRESS     "dSimIpAddress"

#define KEY_ENTRY_DSIM_OIDS_PORT_NUM "dSimOidsPortNum"

#define KEY_ENTRY_DSIM_INDS_PORT_NUM "dSimIndicationsPortNum"

#define KEY_ENTRY_USE_VERSIONING     "EnableVersioning"

#define KEY_ENTRY_GET_DEVICES_TRACE  "GetDeviceTraces"

#define KEY_ENTRY_DND_ORIGIN         "GetDnDOrigin"

#define KEY_ENTRY_MODE_OF_OPERATION_PROD "ModeOfOperationProduction"

#define KEY_ENTRY_TARGET             "OutputTarget"

#define KEY_ENTRY_INTERFACE_NAME	"InterfaceName"

#define KEY_ENTRY_IP_RENEW	"IPRenew"

#define KEY_ENTRY_OBFUSCATE	"DisableObfuscate"

#define KEY_ENTRY_SDK_PORT           "SdkPortNum"

#define KEY_ENTRY_IP_ADDRESS         "SdkIpAddress"

#define KEY_ENTRY_TRC_PATH               "TrcPath"

#define KEY_ENTRY_START_WATCHDOG         "StartWatchdog"

#define KEY_ENTRY_TLS_SOURCE         "TLS_Source"

#define KEY_ENTRY_INSTALLING         "Installing"

#define KEY_ENTRY_INSTALLATION_STAUTS "InstallationStatus"

#define KEY_ENTRY_COMMON_PRIVILEDGE  "CommonPriviledgeEnable"

#define KEY_ENTRY_START_MOC_MSG_PROXY "StartMOCMsgProxy"

#define KEY_ENTRY_IPC                    "IPC"

#define KEY_ENTRY_SET_CONNECTION_MODE    "SetConnectionMode"

#define KEY_ENTRY_APDO_READ_FROM_NVM          "ApdoReadFromNvm"

#define KEY_ENTRY_APDO_DEV_ID_PREFIX          "ApdoDevIDPrefix"

#define KEY_ENTRY_APDO_SECURE_BOOTSTRAP       "ApdoSecureBootstrap"

//#define KEY_ENTRY_LINK_UP_SLEEP			"LinkUpSleep"

//#define KEY_ENTRY_IND_PKG_UPDATE_SLEEP	"IndPkgUpdateSleep"

#define KEY_ENTRY_DISABLE_RENEW          "DisableRenew"

#define KEY_ENTRY_DEVICE_RETRIES			"DeviceResetRetries"

#define KEY_ENTRY_APDO_LEAVE_DB_DEFAULTS		"ApdoLeaveDbDefaults"

#define KEY_ENTRY_APDO_FIX_SPECIAL_CHARACTERS	"ApdoFixSpecialCharacters"

#define KEY_ENTRY_APDO_FUMO_SWV2_STRING "ApdoFumoSwv2String"

#define KEY_ENTRY_APDO_LINK_UP_SLEEP	"ApdoLinkUpSleep"

#define KEY_ENTRY_APDO_AFTER_LINK_UP_SLEEP	"ApdoAfterLinkUpSleep"

#define KEY_ENTRY_APDO_LINK_UP_RETRIES "ApdoLinkUpRetries"

#define KEY_ENTRY_APDO_PACKAGE_UPDATE_SLEEP "ApdoPackageUpdateSleep"

#define KEY_ENTRY_APDO_SHARED_SECRET "ApdoSharedSecret"

#define KEY_ENTRY_APDO_CALC_SECRET "ApdoCalcSecret"

#define KEY_ENTRY_APDO_MANDATORY_UPDATE_LOGIC "ApdoMandatoryUpdateLogic"

#define KEY_ENTRY_APDO_FUMO_DISABLE "ApdoFumoDisable"

#define KEY_ENTRY_PACKAGE_NAME	"PackageName"

//SDK Traces
#define KEY_ENTRY_SEVERITIES "Severities"

#define KEY_ENTRY_MODULES    "Modules"

#define KEY_ENTRY_LOG_PATH   "LogPath"

#define KEY_ENTRY_FILE_NAME  "LogFileName"

#define KEY_ENTRY_DUMP       "DumpEnable"
#define KEY_ENTRY_PB_LOG     "PbLog"
#define KEY_ENTRY_USE_NEW_TRACES	"UseNewTrace"

#define KEY_ENTRY_DISABLE_FAST_RECONNECT		"DisableFastReconnect"

#define KEY_ENTRY_DISABLE_ROBUST_CONNECT		"DisableRobustConnect"

// LED
#define LED_INTERVAL      "Interval"

#define LED_NUM_OF_LEDS   "NumOfLeds"

#define LED_POWER_IND     "PowerSaveInd"

#define LED_NVM_OVERRIDE  "NVMOverride"

#define LED_LED1_BEHAVIOR "LED1Behavior"

#define LED_LED2_BEHAVIOR "LED2Behavior"

#define KEY_ENTRY_PIPELED_BLINK_ON  "OnBlinkRate"
#define KEY_ENTRY_PIPELED_BLINK_OFF "OffBlinkRate"



//
#define  GEN_IDLE_TIMEOUT_val			"IdleTimeout"

#define  GEN_IDLE_PAGING_INTERVAL_val "IdlePagingInterval"

#define  GEN_IDLE_ENTRY_SUSPEND_val "IdleEntrySuspend"

#define  GEN_FULL_NE_SUSPEND_val	 "FullNeSuspend"

#define  GEN_LINK_DOWN_val			"LinkDownTimer"

#define  GEN_RESET_ON_ASSERT_val		"ResetOnAssert"

#define GEN_HARQ_CATEGORY_val		"HarqCategory"

#define GEN_D2H_DATA_FORMAT_val		"D2HDataFormat"

#define GEN_DL_HOST_REORDER_val		"DLHostReorder"

#define GEN_CS_TYPE_val			"CSType"

#define GEN_PADDING_SIZE_val		"PaddingSize"

#define  LOOP_BACK_val				"LoopBack"

#define  LIMIT_MAX_TX_POWER_val		"LimitMaxTxPower"

#define  WATCH_DOG_TIMER_val			"WatchDogTimer"

#define  ARQ_SUPPORT_val				"ArqSupport"

#define  SLOW_CLOCK_val				"PowerSaveEnable"

#define  ENABLE_SELECTIVE_PLIS_val	"EnableSelectivePLIs"

#define  DELAYED_SELECTIVE_PLI_val	"DelayedSelectivePLI"

#define  CONSECUTIVE_PLI_val			"ConsecutivePLIToReceive"

#define  PRIVILEGE_KEY_val				 "PrivilegeKey"

#define  PRIVILEGE_ENABLE_val				 "PrivilegeEnable"


#define  KEY_ENTRY_SERVICE_PROVIDER_LOCK	 "ServiceProviderLock"


#define KEY_ENTRY_TERM_EQUIPMENT_MANUFACTURER_ID    	"ManufacturerID"
#define KEY_ENTRY_TERM_EQUIPMENT_MODEL			"Model"
#define KEY_ENTRY_TERM_EQUIPMENT_FWV			"FwV"
#define KEY_ENTRY_TERM_EQUIPMENT_HWV			"HwV"
#define KEY_ENTRY_TERM_EQUIPMENT_DEV_ID			"DevID"

#define KEY_ENTRY_DEV_INFO_MODEL			"Model"
#define KEY_ENTRY_DEV_INFO_MANUFACTURER_ID		"ManufacturerID"

#define KEY_ENTRY_DEV_DETAILS_DEV_TYPE	"DevType"
#define KEY_ENTRY_DEV_DETAILS_FWV	"FwV"
#define KEY_ENTRY_DEV_DETAILS_HWV	"HwV"
#define KEY_ENTRY_DEV_DETAILS_SWV	"SwV"

#define KEY_ENTRY_PROCESSOR_SYS_ENV  "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\\"
#define KEY_ARCHITECTURE				"PROCESSOR_ARCHITECTURE"
#define KEY_ENTRY_MAX_NUM_OF_FILES  "MaxNumOfFiles"



//  Purpose: returns the value of an entry in the registry of type REG_DWORD
//
//  Remarks: if the function fails the value is unchanged
//
//  Parameters:
//  --------------------------------------------------------------------------------------------
//			name		|		type and Purpose		|-> <-|			Deleted by
//  --------------------------------------------------------------------------------------------
//  hMainKey			 the main key					 [in]			N/A
//						 for example, HKEY_LOCAL_MACHINE
//
//  name_of_subkey		 the name of the sub key		 [in]			N/A
//						 for example "Software\\Armadillo\\svc\\"
//
//  name_of_value		 the name of the entry from		 [in]			N/A
//						 which you want to retrieve the information
//
//	value				 the returned value read from	 [in-out]		N/A
//						 the registry
//
//
//  Return value: false - if name_of_subkey is null or not found
//						- if name_of_value is null or not found
//				  true  - success
//
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL GetConfig_NumValue(const char *config_name,UINT32 * value);
BOOL SetConfig_NumValue(const char *config_name,UINT32 * value);
BOOL GetConfig_StrValue(const char *config_name,char* value,UINT32 maxsize);
BOOL SetConfig_StrValue(const char *config_name,char* value);
char *GetConfig_RootPath(void);
char *GetConfig_ConfigPath(void);
BOOL GetConfig_NetworkConfigPath(char * configpath, int bufsize);
//BOOL GetConifg_SupplicantLibFullPath(char * libfullpath, int bufsize); //TEDD_REMOVE_IF_SANITY_PASS
BOOL GetConfig_LogPath(char * logpath, int bufsize);

BOOL GetConifg_InstrumentationLibName(char *libpath, int bufsize);


// ################# DEFINITIONS FOR WINDOWS STUFF :-( ###############
// Default values for L4 configurations.
#define DEFAULT_DRIVER_MODE				"Driver"
#define DEFAULT_IPC_MODE				"Sockets"
#define DEFAULT_DSIM_IND_PORT_NUM		0x00002b26
#define DEFAULT_IP						"127.0.0.1"
#define DEFAULT_DSIM_OIDS_PORT_NUM		0x00002b25
#define DEFAULT_DEVICE_TRACES			0x00000002
#define DEFAULT_MODE_OF_OP_PROD			0x00000000
#define DEFAULT_MODULES					0x7fffffff
#define DEFAULT_OUTPUT_TARGET			"Service"
#define DEFAULT_SDK_PORT_NUM			0x000004d2 //1234
#define DEFAULT_DND_OUTPUT_PORT_NUM		0x000002b26 //11046
#define DEFAULT_SEVERITIES				0x00000000 //31
#define DEFAULT_USENEWTRACES			0x00000000 
#define DEFAULT_START_WATCHDOG			0x00000000
#define DEFAULT_ENABLE_VERSIONING		0x00000000
#define DEFAULT_FALSE_STR				"False"
#define DEFAULT_COEX_MODE				"xor"
#define DEFAULT_FILE_NAME				"TraceLog"
#define DEFAULT_FALL_TO_XOR_TIMEOUT		0
#define DEFAULT_CONNECT_TIME			0x00000000
#define DEFAULT_NO_XOHM_GROUPS			0x00000000
#define DEFAULT_NO_SM				0x00000000
#define DEFAULT_DISABLE_DISCOVERY		0x00000000
#define DEFAULT_IDLE_TIMEOUT			0x00001770
#define DEFAULT_IDLE_ENTRY_SUSPEND		0x00002710
#define DEFAULT_FULL_NE_SUSPEND			0x00000000
#define DEFAULT_LINK_LOSS_TIMER			0x00004e20
#define DEFAULT_USE_PB_LOG			0x00000001
#define DEFAULT_WATCHDOG_TIMER			0x00000001
#define DEFAULT_MAX_TX_POWER			0x00000000
#define DEFAULT_PRIVILEGE_ENABLE		0x00000000
#define DEFAULT_SHOW_UNKNOWN_NSPS		0x00000000
#define DEFAULT_DO_NOT_USE_PSEUDO_NAI		0x00000000
#define DEFAULT_LOOP_BACK			0x00000000
#define DEFAULT_RESET_ON_ASSERT			0x00000001
#define DEFAULT_HARQ_CATEGORY			0x00000000
#define DEFAULT_D2H_DATA_FORMAT			0x00000001
#define DEFAULT_DL_HOST_REORDER			0x00000001
#define DEFAULT_CS_TYPE				0x00000000
#define DEFAULT_PADDING_SIZE			0x00000000
#define DEFAULT_TLS_SOURCE			"external"
#define DEFAULT_NUM_OF_LEDS			0x00000002
#define DEFAULT_NVM_OVERRIDE			0x00000001
#define DEFAULT_POWER_SAVE_IND			0x00000000
#define DEFAULT_LED_BEHAVIOR			"AAAAAAAAAAAAAA"
#define DEFAULT_IDLE_PAGING_INTERVAL		0x00000400
#define DEFAULT_ARQ_SUPPORT_VAL			0x00000001
#define DEFAULT_SLOW_CLOCK_VAL			0x00000001
#define DEFAULT_LOW_POWER_IS_VAL		0x00000000
#define DEFAULT_ENABLE_SELECTIVE_PLIS_VAL	0x00000000
#define DEFAULT_DELAYED_SELECTIVE_PLI_VAL	0x00000000
#define	DEFAULT_CONSECUTIVE_PLI_VAL		0x00000000
#define DEFAULT_DISABLE_FAST_RECONNECT		0x00000000
#define DEFAULT_DISABLE_ROBUST_CONNECT		0x00000000

#define DEFAULT_COMMON_PRIVILEGE_ENABLE 0x00000000
#define DEFAULT_INTERVAL				0x00000000

// Retries number to wait for IP when link up
#define DEFUALT_APDO_LINK_UP_RETRIES 20
#define DEFUALT_APDO_LINK_UP_SLEEP 4000
#define DEFUALT_APDO_AFTER_LINK_UP_SLEEP 10000
#define DEFUALT_APDO_PACKAGE_UPDATE_SLEEP 10000
#define DEFUALT_APDO_DEV_ID_PREFIX "MAC:"

#define DEFUALT_MOC_MSG_PROXY 0

#define DEFUALT_DND_OUTPUT_MODE 1
#define DEFUALT_MAX_NUM_OF_DIRS 10
#define DEFUALT_MAX_NUM_OF_FILES 10000
#define DEFUALT_INSTRUMENTATION_LOADING_TYPE 1

#define DEFAULT_INSTRUMENTATION_ENABLE_VALUE	0
#



#endif // _CONFIG_CONTROLLER_H_
