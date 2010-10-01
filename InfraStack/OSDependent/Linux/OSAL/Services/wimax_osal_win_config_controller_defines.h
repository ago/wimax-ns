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
#ifndef _CONFIG_CONTROLER_DEFINES_H
#define _CONFIG_CONTROLER_DEFINES_H

#define OSAL_KEY_ENTRY_PIPEDEV		""
#define OSAL_KEY_ENTRY_PIPETRACE		""
#define OSAL_KEY_ENTRY_PIPECONFIG		""
#define OSAL_KEY_ENTRY_PIPEAPDO		""
#define OSAL_KEY_ENTRY_PIPECLED		""
#define OSAL_KEY_ENTRY_PIPELED_BLINK_ON		""
#define OSAL_KEY_ENTRY_PIPELED_BLINK_OFF		""

#if 0
#define OSAL_KEY_ENTRY_DND_OUTPUT_MODE		""
#define OSAL_KEY_ENTRY_START_MOC_MSG_PROXY		""

#define OSAL_MAX_NUM_OF_DIRS		"MaxNumberOfDir"

#endif // 0


// COEXISTANCE Defines

//## Token RootPath
//## Type String
//## Value C:\Program Files\Intel\WiMAX\Bin
//## Comment the location the AppSrv and its needed files should be located
#define  OSAL_KEY_ENTRY_ROOT_PATH  			"RootPath"

//## Token CoexistingMode
//## Type String
//## Value XOR
//## Comment Indicate if we can work both on the WIFI and the WIMAX (cm stand for both XOR stand for only one of them)
#define  OSAL_KEY_ENTRY_COEXISTING_MODE		"CoexistingMode"

//## Token FALL_TO_XOR_TIMEOUT
//## Type DWORD
//## Value 300
//## Comment Indicate how many seconds we should wait for CM status received from CoexistingMode in case we started with CM status
#define  OSAL_KEY_ENTRY_COEXISTING_TIMEOUT		"FALL_TO_XOR_TIMEOUT"

//## Token MAX_NUM_OF_DIR
//## Type DWORD
//## Value 10
//## Comment Indicate the maximum allowed trace directories
#define  OSAL_MAX_NUM_OF_DIR		"MaxNumberOfDir"

//## Token MAX_NUM_OF_DIR
//## Type DWORD
//## Value 10
//## Comment Indicate the maximum allowed trace files
#define  OSAL_MAX_NUM_OF_FILES  "MaxNumOfFiles"

//## End Root path

//## Root path = Software\\Intel\\WiMAX\\SDK\\Dev

//## Token ShowUnkownNSPs
//## Type DWORD
//## Value 00000001
//## Comment When the key exists - show unknown (unprovisioned) NSPs; Don't show otherwise.
#define  OSAL_KEY_ENTRY_SHOW_UNKNOWN_NSPS				 "ShowUnknownNSPs"

//## Token DoNotUsePseudoNAI
//## Type DWORD
//## Value usually this key does not exist
//## Comment When the key exists - Work with old Random NAI.
#define  OSAL_KEY_ENTRY_DO_NOT_USE_PSEUDO_NAI				 "DoNotUsePseudoNAI"

//## Token ConnectTime
//## Type DWORD
//## Value 0
//## Comment sets the time for the connection to return - used by integration guys. 
#define  OSAL_KEY_ENTRY_CONNECT_TIME			"ConnectTime"

//## Token NoXohmGroups
//## Type DWORD
//## Value usually this key does not exists
//## Comment If key exists - when building preferred channel plan - discrete channels are used in sorting instead of groups of 3 channels 
#define  OSAL_KEY_ENTRY_NO_XOHM_GROUPS		"NoXohmGroups"

//## Token NoSM
//## Type DWORD
//## Value usually this key does not exists
//## Comment If key exists - All automatic decorations in the NAI are removed
#define  OSAL_KEY_ENTRY_NO_SM_DECORATION		"NoSM"

//## Token Decoration
//## Type String
//## Value usually this key does not exists
//## Comment If key exists - its content is appended as a prefix to the NAI
#define  OSAL_KEY_ENTRY_CUSTOM_DECORATION		"Decoration"

//## Token DisableDiscovery
//## Type DWORD
//## Value usually this key does not exists
//## Comment When the key exists a discovery for full BS ids in scan result will not be executed 
#define  OSAL_KEY_ENTRY_DISABLE_DISCOVERY		"DisableDiscovery"

//## Token DisableFastReconnect
//## Type DWORD
//## Value usually this key does not exists
//## Comment When the key exists - if it equal to 0 fast reconnect will be enabled, else - disabled
#define  OSAL_KEY_ENTRY_DISABLE_FAST_RECONNECT		"DisableFastReconnect"

//## Token DisableRobustConnect
//## Type DWORD
//## Value usually this key does not exists
//## Comment When the key exists - if it equals to 0 fast reconnect will be enabled, else - disabled
#define  OSAL_KEY_ENTRY_DISABLE_ROBUST_CONNECT		"DisableRobustConnect"

//## Token NoRealmInNAI
//## Type String
//## Value usually this key does not exists
//## Comment When the key exists realm will not be added to the NAI
#define  OSAL_KEY_ENTRY_NO_REALM_IN_NAI		"NoRealmInNAI"

//## Token DriverOrDsim
//## Type String
//## Value driver or Dsim
//## Comment Use this entry to specify whether a real device is used or dSim or remote
#define  OSAL_KEY_ENTRY_DRIVER_OR_DSIM			"DriverOrDsim"

//## Token dSimIpAddress
//## Type String
//## Value 127.0.0.1
//## Comment Use this entry to specify for AppSrv where dSim is running
#define  OSAL_KEY_ENTRY_DSIM_IPADDRESS			"dSimIpAddress"

//## Token dSimOidsPortNum
//## Type DWORD
//## Value 11045
//## Comment Oid port number only when using dSim
#define  OSAL_KEY_ENTRY_DSIM_OIDS_PORT_NUM		"dSimOidsPortNum"

//## Token dSimIndicationsPortNum
//## Type DWORD
//## Value 11046
//## Comment Indication port number only when using dSim
#define  OSAL_KEY_ENTRY_DSIM_INDS_PORT_NUM		"dSimIndicationsPortNum"

//## Token EnableVersioning
//## Type DWORD
//## Value 1 (enabled)
//## Comment Internal version validation between binaries used by AppSrv
#define  OSAL_KEY_ENTRY_USE_VERSIONING			"EnableVersioning"

//## Token GetDeviceTraces
//## Type DWORD
//## Value 1 (enabled)
//## Comment NDIS traces
#define  OSAL_KEY_ENTRY_GET_DEVICES_TRACE		"GetDeviceTraces"

//## Token DndOutputFilesPath
//## Type DWORD
//## Value 1 (enabled)
//## Comment path where the dnd files are written - used for the remote configuration
#define  OSAL_KEY_DND_OUTPUT_FILES_PATH		"DndOutputFilesPath"

//## Token GetDnDOrigin
//## Value 2
//## Comment defined the origin for DND data (monitor & traces) (2= origin is ndis log data, 3= origin is L4 messages sent to AppSrv)
#define  OSAL_KEY_ENTRY_DND_ORIGIN				"GetDnDOrigin"

//## Token ModeOfOperationProduction
//## Type DWORD
//## Value 0
//## Comment indicate whether the mode will be production or regular  (we use 0 stands for regular)
#define  OSAL_KEY_ENTRY_MODE_OF_OPERATION_PROD "ModeOfOperationProduction"

//## Token OutputTarget
//## Type String
//## Value Service
//## Comment Run AppSrv as a console application or as a windows service
#define  OSAL_KEY_ENTRY_TARGET					"OutputTarget"

//## Token SdkPortNum
//## Type DWORD
//## Value 1234 (decimal)
//## Comment Use this entry to specify for the application what is the port used by AppSrv
#define  OSAL_KEY_ENTRY_SDK_PORT				"SdkPortNum"

//## Token SdkPortNum
//## Type DWORD
//## Value 1234 (decimal)
//## Comment Use this entry to specify for the application what is the port used by AppSrv
#define  OSAL_KEY_ENTRY_DND_OUTPUT__PORT		"DnDOutputPortNum"

//## Token SdkIpAddress
//## Type String
//## Value 127.0.0.1 (local host)
//## Comment Use this entry to specify for the application where AppSrv is running
#define  OSAL_KEY_ENTRY_IP_ADDRESS				"SdkIpAddress"

//## Token TrcPath
//## Type String
//## Value C:\Program Files\Intel\WiMax\Fw_bin
//## Comment Specify the path where the driver TRC file locate
#define  OSAL_KEY_ENTRY_TRC_PATH  				"TrcPath"

//## Token StartWatchdog
//## Type DWORD
//## Value 0
//## Comment Identify whether the watchdog is activate or not
#define  OSAL_KEY_ENTRY_START_WATCHDOG         "StartWatchdog"

//## Token TLS_Source
//## Type String
//## Value !internal
//## Comment Defines if the Moccana SSL library is inside the Supplicant (host = internal) or inside the device
#define  OSAL_KEY_ENTRY_TLS_SOURCE				"TLS_Source"

//## Token CommonPriviledgeEnable
//## Type DWORD
//## Value 0
//## Comment Indicate if we can by pass the restrict that only one application can do IO (use for using the developer tools such as TraceView) (1- allowed only one application)
#define  OSAL_KEY_ENTRY_COMMON_PRIVILEDGE		"CommonPriviledgeEnable"

//## Token StartMOCMsgProxy
//## Type DWORD
//## Value 0
//## Comment Determines whether to load MOC_Msg_Proxy or not
#define  OSAL_KEY_ENTRY_START_MOC_MSG_PROXY		"StartMOCMsgProxy"

//## Token DndOutputMode
//## Type DWORD
//## Value 1
//## Comment Determines DnD output mode: 1- file system. 2- sockets
#define  OSAL_KEY_ENTRY_DND_OUTPUT_MODE		"DnDOutputMode"

//## Token IPC
//## Type String
//## Value NPipe
//## Comment Are we working above Sockets or Named Pipe (if not specify Sockets it will be Named Pipe)
#define  OSAL_KEY_ENTRY_IPC					"IPC"

//## Token DisableDriverErrorCode0xA
//## Type DWORD
//## Value 0
//## Comment AppSrv makes disable\enable to the device when it gets device error code 0xA
#define  OSAL_KEY_ENTRY_DISABLE_DRIVER_ERROR_0xA		"DisableDriverErrorCode0xA"

//## Token SetConnectionMode
//## Type DWORD
//## Value 1
//## Comment Indication if we need to ran over the connection mode we set earlier after we get out from hibernate (1= allow to change the connection mode)
#define  OSAL_KEY_ENTRY_SET_CONNECTION_MODE	"SetConnectionMode"

//## Token ApdoReadFromNvm
//## Type String Indication if we should read the parameters of RadioModule in L4db from the NVM or from xml.
//## Value True
//## Comment 
#define  OSAL_KEY_ENTRY_APDO_READ_FROM_NVM			"ApdoReadFromNvm"

//## Token ApdoDevIDPrefix
//## Type String
//## Value MAC:
//## Comment Add the prefix to the device id
#define  OSAL_KEY_ENTRY_APDO_DEV_ID_PREFIX			"ApdoDevIDPrefix"

//## Token ApdoSecureBootstrap
//## Type String
//## Value True
//## Comment if the key equal to false APDO will not decrypt bootstrap message and returns input buffer as output
#define  OSAL_KEY_ENTRY_APDO_SECURE_BOOTSTRAP		"ApdoSecureBootstrap"

//## Token DisableRenew
//## Type DWORD
//## Value 0
//## Comment Use in order to by pass a problem in the driver that doesn�t know to give a new IP in case of reconnect (we do it in the AppSrv)
#define  OSAL_KEY_ENTRY_DISABLE_RENEW			"DisableRenew"

//## Token DeviceResetRetries
//## Type DWORD
//## Value 50
//## Comment The Number of times trying to connect to the device (when the device return corrupted data)
#define  OSAL_KEY_ENTRY_DEVICE_RETRIES			"DeviceResetRetries"

//## Token ApdoLeaveDbDefaults
//## Type String
//## Value False
//## Comment This registry is used in the DB - If this is set to True all values will stay as read from the file and won't be overridden from registry.
#define  OSAL_KEY_ENTRY_APDO_LEAVE_DB_DEFAULTS		"ApdoLeaveDbDefaults"

//## Token ApdoFixSpecialCharacters
//## Type String
//## Value False
//## Comment 
#define  OSAL_KEY_ENTRY_APDO_FIX_SPECIAL_CHARACTERS	"ApdoFixSpecialCharacters"

//## Token ApdoFumoSwv2String
//## Type String
//## Value Empty string
//## Comment This key, if value is not NULL, will be used in order to override the SwV2 string reported to the OMA server for debug.
#define  OSAL_KEY_ENTRY_APDO_FUMO_SWV2_STRING	"ApdoFumoSwv2String"

//## Token ApdoLinkUpSleep
//## Type DWORD
//## Value 4000
//## Comment This value is used while waiting for IP in the linkUp CB. This is a sleep between checks for IP.
#define  OSAL_KEY_ENTRY_APDO_LINK_UP_SLEEP	"ApdoLinkUpSleep"

//## Token ApdoLinkUpSleep
//## Type DWORD
//## Value 10000
//## Comment This value is used after waiting for IP in the linkUp CB. This is a sleep between getting an IP and raising the ind to DMC.
#define  OSAL_KEY_ENTRY_APDO_AFTER_LINK_UP_SLEEP	"ApdoAfterLinkUpSleep"

//## Token ApdoLinkUpRetries
//## Type DWORD
//## Value 20
//## Comment This value is used while waiting for IP in the linkUp CB. This is the number of retries in the loop waiting for the IP.
#define  OSAL_KEY_ENTRY_APDO_LINK_UP_RETRIES "ApdoLinkUpRetries"

//## Token ApdoPackageUpdateSleep
//## Type DWORD
//## Value 0x2710 (10000)
//## Comment 
#define  OSAL_KEY_ENTRY_APDO_PACKAGE_UPDATE_SLEEP "ApdoPackageUpdateSleep"

//## Token ApdoSharedSecret
//## Type String
//## Value 
//## Comment This value is used in the generation of the fake bootstrap 
#define  OSAL_KEY_ENTRY_APDO_SHARED_SECRET "ApdoSharedSecret"

//## Token ApdoCalcSecret
//## Type String
//## Value True
//## Comment This value is used in the generation of the fake bootstrap. If TRUE secret is calculated if FALSE read from file
#define  OSAL_KEY_ENTRY_APDO_CALC_SECRET "ApdoCalcSecret"

//## Token ApdoMandatoryUpdateLogic
//## Type String
//## Value "FALSE"
//## Comment This value is used in the FUMO process to decide MandatoryUpdate flag logic. If this flag is False when D&U MandatoryUpdate=False.
#define  OSAL_KEY_ENTRY_APDO_MANDATORY_UPDATE_LOGIC "ApdoMandatoryUpdateLogic"

//## Token ApdoFumoDisable
//## Type String
//## Value False
//## Comment This value is used to disable the FUMO. When False FUMO is enabled.
#define  OSAL_KEY_ENTRY_APDO_FUMO_DISABLE "ApdoFumoDisable"

//## End Root path

//## Token Installing
//## Type String
//## Value False
//## Comment Indicate if the installing by the apdo already started
#define  OSAL_KEY_ENTRY_INSTALLING				"Installing"

//## Token InstallationStatus
//## Type String
//## Value Idle
//## Comment indicate the stage we locate in the installing process (by the apdo)
#define  OSAL_KEY_ENTRY_INSTALLATION_STAUTS	"InstallationStatus"

//## Token PackageName
//## Type String
//## Value 
//## Comment This key tells the wimax updater which package to install
#define  OSAL_KEY_ENTRY_PACKAGE_NAME	"PackageName"

//## End Root path

//SDK Traces

//## Token Severities
//## Type DWORD
//## Value 7f (hexadecimal) (all errors will be printed
//## Comment Defines the severity of logs that will be printed by AppSrv
#define  OSAL_KEY_ENTRY_SEVERITIES		"Severities"

//## Token Modules
//## Type DWORD
//## Value 7fffffff (hexadecimal) (all modules will be printed)
//## Comment Use in order to by pass a problem in the driver that doesn�t know to give a new IP in case of reconnect (we do it in the AppSrv)
#define  OSAL_KEY_ENTRY_MODULES		"Modules"

//## Token LogPath
//## Type String
//## Comment This the location in which AppSrv�s logs will be saved
#define  OSAL_KEY_ENTRY_LOG_PATH		"LogPath"

//## Token LogFileName
//## Type String
//## Value usually not exists
//## Comment define the log file name (in case it is not TraceLog)
#define  OSAL_KEY_ENTRY_FILE_NAME		"LogFileName"

//## Token DumpEnable
//## Type String
//## Value 0
//## Comment indicate whether we need to writes the driver Generic Trace Message into the log
#define  OSAL_KEY_ENTRY_DUMP			"DumpEnable"

//# Token ModulesEnum
//# Type MULTI-DWORD
//# Value TR_MOD_L4MsgProxy = 1 ;TR_MOD_MocMsgProxy = 2 ;TR_MOD_KDAPI = 4 ;TR_MOD_KDAPI_ADAPTER = 8 ;TR_MOD_KDAPI_FOR_SIM = 16 ;TR_MOD_CLIENT_SOCKET = 32 ;TR_MOD_SERVER_SOCKET = 64 ;TR_MOD_L5_CONNECTOR = 128 ;TR_MOD_L5_DISPATCHER = 256 ;TR_MOD_SERVICE = 512 ;TR_MOD_ALL = 0xFFFFFFFF
//# Comment specify the severity of each modules
//#define  OSAL_KEY_ENTRY_DUMP			"ModulesEnum"


#define  OSAL_KEY_ENTRY_PB_LOG			"PbLog"

//## Token UseNewTrace
//## Type DWORD
//## Value 1
//## Comment indicate whether to use the modules traces
#define  OSAL_KEY_ENTRY_USE_NEW_TRACES	"UseNewTrace"

//## End Root path
//## General Comment If the Software\\Intel\\WiMAX\\SDK\\Dev\\Traces is not exist we will not have traces
//## General Comment 
//## General Comment LED description read me file
//## General Comment ========================================
//## General Comment There is a specific ppt that explain the LED structure deeply called "LEDs SRR_v03.ppt"
//## General Comment and excel that contain the deferent OEM defult values call "Wimax LED Settings Database v1r4.xls"



//## Token Interval
//## Type DWORD
//## Value verify between the different OEMs
//## Comment LED time interval for Power saving in On/Off mode.
#define  OSAL_LED_INTERVAL        "Interval"

//## Token NumOfLeds
//## Type DWORD
//## Value verify between the different OEMs
//## Comment define number of LEDs 
#define  OSAL_LED_NUM_OF_LEDS     "NumOfLeds"

//## Token PowerSaveInd
//## Type DWORD
//## Value verify between the different OEMs
//## Comment 0x1 for power savings in on/off mode. 0x0 for No power saving. 
#define  OSAL_LED_POWER_IND       "PowerSaveInd"

//## Token NVMOverride
//## Type String
//## Value 0
//## Comment 0x1 will indicate that LED Registry settings will be used. 0x0 will indicate default device�s LED settings.
#define  OSAL_LED_NVM_OVERRIDE    "NVMOverride"

//## Token LED1Behavior
//## Type String
//## Value verify between the different OEMs
//## Comment Defines WLAN_LED Behavior for each one of 14 system states for the first LED
#define  OSAL_LED_LED1_BEHAVIOR   "LED1Behavior"

//## Token LED2Behavior
//## Type String
//## Value verify between the different OEMs
//## Comment Defines WLAN_LED Behavior for each one of 14 system states for the second LED
#define  OSAL_LED_LED2_BEHAVIOR   "LED2Behavior"

//## End Root path
//## General Comment


//## Token A - M (the same meaning)
//## Type DWORD
//## Value verify between the different OEMs
//## Comment There would be a list of REG_DWORD define as �A� ,�B� ��M� that indicate the on time for each behavior.
//## Comment In addition the last key which call "PowerSave" indicate the on time for Power Save behavior
static inline
const char * OSAL_LED_REG_ARR(unsigned index)
{
	static const char *strs[] = {
		("A"),
		("B"),
		("C"),
		("D"),
		("E"),
		("F"),
		("G"),
		("H"),
		("I"),
		("J"),
		("K"),
		("L"),
		("M"),
		("PowerSave")
	};
	return strs[index];
}
	
//## End Root path
//## General Comment under the Root path Software\\Intel\\WiMAX\\LED\\LEDBlinkRate\\OffBlinkRate we define the same array
//## General Comment (same key names) for the off time
//## General Comment
//## General Comment
//## General Comment Device Configuration using the Registry
//## General Comment ========================================
//## General Comment As of the last few releases, some ini file parameters can be overridden by values from the 
//## General Comment Registry. Please read the comments below carefully.

//## Root path = Software\\Intel\\WiMAX\\GEN
#define  OSAL_KEY_ENTRY_PIPEGEN			"Software\\Intel\\WiMAX\\GEN"

//## Token IdleTimeout
//## Type DWORD
//## Value 000007d0
//## Comment The device measures time (in Milliseconds) of no traffic until Idle timeout is reached and then the device initiates idle mode.
//## Comment Valid values are:
//## Comment Any value between 300 and 300,000 (300ms � 5min). values should be in 100ms increments.
//## Comment 0 means Idle is disabled and will not be initiated by the device.
#define  OSAL_GEN_IDLE_TIMEOUT_val			"IdleTimeout"

//## Token IdlePagingInterval
//## Type DWORD
//## Value 00000400
//## Comment The device will use this number (of frames) when requesting paging interval in idle negotiation with the BS.
#define  OSAL_GEN_IDLE_PAGING_INTERVAL_val "IdlePagingInterval"

//## Token IdleEntrySuspend
//## Type DWORD
//## Value 00001388
//## Comment mSec that the device will block subsequent entering idle after successful idle entry.
//## Comment Valid values are:
//## Comment Any value between 0 and 300,000 (0ms � 5min). values should be in 100ms increments.
#define  OSAL_GEN_IDLE_ENTRY_SUSPEND_val			"IdleEntrySuspend"

//## Token FullNeSuspend
//## Type DWORD
//## Value 0000EA60
//## Comment mSec that the device will block entering idle after full NE (initial or re-entry).
//## Comment Valid values are:
//## Comment Any value between 0 and 300,000 (0ms � 5min). values should be in 100ms increments.
#define  OSAL_GEN_FULL_NE_SUSPEND_val			"FullNeSuspend"

//## Token LinkDownTimer
//## Type DWORD
//## Value 00002710
//## Comment The number of milliseconds to retry and establish a connection before signaling link down.
#define  OSAL_GEN_LINK_DOWN_val			"LinkDownTimer"

//## Token ResetOnAssert
//## Type DWORD
//## Value 00000001
//## Comment Determines whether the device will halt or reset upon assert.
//## Comment 0 = Disable (halt), 1 = Enable (reset)
#define  OSAL_GEN_RESET_ON_ASSERT_val		"ResetOnAssert"

//## Token HarqCategory
//## Type DWORD
//## Value 00000003
//## Comment HARQ Category.
//## Comment 2, 3 or 4
#define  OSAL_GEN_HARQ_CATEGORY_val		"HarqCategory"

//## Token D2HDataFormat
//## Type DWORD
//## Value 0000002
//## Comment D2H Data Format.
//## Comment 0 = Data (Descriptor 0), 1 = Enhanced Data (Descriptor 5)
#define  OSAL_GEN_D2H_DATA_FORMAT_val		"D2HDataFormat"

//## Token DLHostReorder
//## Type DWORD
//## Value 00000001
//## Comment DL Host Reorder.
//## Comment 0 = Disable , 1 = Enable
#define  OSAL_GEN_DL_HOST_REORDER_val		"DLHostReorder"

//## Token CSType
//## Type DWORD
//## Value 00000002
//## Comment CS Type.
//## Comment 2
#define  OSAL_GEN_CS_TYPE_val		"CSType"

//## Token PaddingSize
//## Type DWORD
//## Value 00000000
//## Comment Padding Size.
//## Comment 0-255
#define  OSAL_GEN_PADDING_SIZE_val		"PaddingSize"

//## Token LoopBack
//## Type DWORD
//## Value 00000000
//## Comment PRIVILEGED
//## Comment Debug Mode - 0 = Normal, 1 = Loop Back Packets, 2 = Ping Packets
#define  OSAL_LOOP_BACK_val				"LoopBack"

//## Token LimitMaxTxPower
//## Type DWORD
//## Value 0000001e
//## Comment PRIVILEGED
//## Comment Maximum Tx power allowed (in Integer dBm). Cannot exceed the value stored in the device�s NVM.
#define  OSAL_LIMIT_MAX_TX_POWER_val		"LimitMaxTxPower"

//## Token WatchDogTimer
//## Type DWORD
//## Value 00000001
//## Comment PRIVILEGED
//## Comment Enable/disable watch dog timer in the device. 0 = Disable, 1 = Enable
#define  OSAL_WATCH_DOG_TIMER_val			"WatchDogTimer"

//## Token ArqSupport
//## Type DWORD
//## Value 00000001
//## Comment Support (or not) ARQ in the device. 0 = Disable, 1 = Enable
#define  OSAL_ARQ_SUPPORT_val				"ArqSupport"

//## Token PowerSaveEnable
//## Type DWORD
//## Value 00000001
//## Comment PRIVILEGED
//## Comment Enable/disable entering to power save mode in the device.
//## Comment 0 = Disable, 1 = Enable
#define  OSAL_SLOW_CLOCK_val				"PowerSaveEnable"

//## Token EnableSelectivePLIs
//## Type DWORD
//## Value 0
//## Comment Enable/disable Selective PLI in the device. 0 = Disable, 1 = Enable
#define  OSAL_ENABLE_SELECTIVE_PLIS_val	"EnableSelectivePLIs"

//## Token DelayedSelectivePLI
//## Type DWORD
//## Value 100
//## Comment Number of PLI cycles (in Integer 8 bits) to wait before performing Selective PLI
#define  OSAL_DELAYED_SELECTIVE_PLI_val	"DelayedSelectivePLI"

//## Token ConsecutivePLIToReceive
//## Type DWORD
//## Value 0
//## Comment How much consecutive PLI to receive (in Integer 8 bits) before ignoring one PLI
#define  OSAL_CONSECUTIVE_PLI_val			"ConsecutivePLIToReceive"

//## End Root path 
//## General Comment 1. The values stated here do not necessarily match the actual values stored in the ini file, so unless
//## General Comment you know the value you want to assign, you should not change the key. 
//## General Comment 
//## General Comment 2. As of WIMAX20, IdleTimeout and IdlePagingInterval are sent as a group. Both should be present in the
//## General Comment registry in order to be sent to the device.

//## Root path = Software\\Intel\\WiMAX\\GEN\\PRIVILEGE
#define  OSAL_KEY_ENTRY_PIPEGEN_PRIVILEGE		 "Software\\Intel\\WiMAX\\GEN\\PRIVILEGE"

//## Token PrivilegeKey
//## Type String
//## Value A1B2C3D4
//## Comment In future versions, the PrivilegeKey will be compared to an internal device key (Stored in the NVM) before allowing modification of privileged ini file value.
#define  OSAL_PRIVILEGE_KEY_val				 "PrivilegeKey"

//## Token PrivilegeEnable
//## Type DWORD
//## Value 00000000
//## Comment Keys that are privileged will override the values in the ini file ONLY IF the PrivilegeKey is sent to the device. Sending the PrivilegeKey is done by assigning 1 to the PrivilegeEnable key.
#define  OSAL_PRIVILEGE_ENABLE_val				 "PrivilegeEnable"


#define  OSAL_KEY_ENTRY_SERVICE_PROVIDER_LOCK	 "ServiceProviderLock"

//## End Root path 
//## General Comment At the moment, the PrivilegeKey is not checked (So any key will do).
//## General Comment Keys that are privileged will override the values in the ini file ONLY IF the PrivilegeKey is sent 
//## General Comment to the device. Sending the PrivilegeKey is done by assigning 1 to the PrivilegeEnable key.

#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT		"Software\\Intel\\WiMAX\\DeviceInformation\\TerminalEquipment"
#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT_MANUFACTURER_ID		"ManufacturerID"
#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT_MODEL				"Model"
#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT_FWV					"FirmwareVersion"
#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT_HWV					"HardwareVersion"
#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT_DEV_ID				"DevID"
#define  OSAL_KEY_ENTRY_TERM_EQUIPMENT_DEV_TYPE				"DeviceType"



#define  OSAL_KEY_ENTRY_DEV_INFO	"Software\\Intel\\WiMAX\\DeviceInformation\\DeviceInfo"
#define  OSAL_KEY_ENTRY_DEV_INFO_DEV_ID				"DevId"
#define  OSAL_KEY_ENTRY_DEV_INFO_MANUFACTURER_ID		"Manufacturer"
#define  OSAL_KEY_ENTRY_DEV_INFO_MODEL					"Model"

#define  OSAL_KEY_ENTRY_DEV_DETAILS	"Software\\Intel\\WiMAX\\DeviceDetails\\DeviceInfo"
#define  OSAL_KEY_ENTRY_DEV_DETAILS_DEV_TYPE				"DeviceType"
#define  OSAL_KEY_ENTRY_DEV_DETAILS_FWV					"FirmwareVersion"
#define  OSAL_KEY_ENTRY_DEV_DETAILS_HWV					"HardwareVersion"
#define  OSAL_KEY_ENTRY_DEV_DETAILS_SWV					"SwV"

#define  OSAL_KEY_ENTRY_PROCESSOR_SYS_ENV  "SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment\\"
#define  OSAL_KEY_ARCHITECTURE				"PROCESSOR_ARCHITECTURE"


#define  OSAL_KEY_ENTRY_ENABLE_INSTRUMENTATION	"EnableInstrumentation"
#define  OSAL_KEY_ENTRY_INSTRUMENT_LIBNAME	"InstrumentationLibrary"
#define  OSAL_KEY_ENTRY_SUPPLICANT_LIBNAME		"SupplicantLibName"

#endif //_CONFIG_CONTROLER_DEFINES_H
