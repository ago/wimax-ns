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
#ifndef _WMX_SDK_NDS_CMN_H
#define _WMX_SDK_NDS_CMN_H

#include "wimax_osal_primitives.h"
#include "wimax_osal_types.h"
#include "wimax_osal_string.h"

#define MAX_CONTACT_DETAILS_SIZE 512
#define MAX_SIZE_OF_STRING_BUFFER 256
#define WMX_IDS_MAX_NUM	17
#define MAX_VERBOSE_NSP_NAME_SIZE 256
#define MAX_SP_LOCK_CODE_SIZE 32
#define PREAMBLES_LENGTH	15
#define WMX_CHANNELS_MAX_NUM 64
#define MAX_INSTALLAION_VERSION_SIZE 50

/// <summary>
/// Type definitions used in the link status struct.
/// </summary>
typedef UINT8 wmx_SignalStrength_t, *wmx_pSignalStrength_t;
typedef UINT8 wmx_CINR_t, *wmx_pCINR_t;
typedef UINT32 wmx_Frequency_t, *wmx_pFrequency_t; // Oran V3.0: Converted from DOUBLE to UINT32
typedef UINT8 wmx_Power_t, *wmx_pPower_t;
typedef UINT8 wmx_MaxTxPower_t, *wmx_pMaxTxPower_t;
typedef UINT32 wmx_LinkQuality_t, *wmx_pLinkQuality_t;
typedef DOUBLE wmx_ConnectionTime_t, *wmx_pConnectionTime_t;
typedef DOUBLE wmx_LinkSpeed_t, *wmx_pLinkSpeed_t;
typedef UINT32 wmx_NspChangeCount_t, *wmx_pNspChangeCount_t;


/// <summary>
/// Type definitions for variables that are fields of the _wmx_ChannelInfo_t struct. 
/// </summary>
typedef UINT32	wmx_DuplexMode_t, *wmx_pDuplexMode_t;
typedef UINT32  wmx_NextFreqStep_t, *wmx_pNextFreqStep_t;

/// <summary>
/// Type definitions for variables that are fields of the wmx_BSSelectionCriteria_t struct. 
/// </summary>
typedef UINT8 wmx_BSid_t[6], *wmx_pBSid_t; // NetworkId
typedef UINT8 wmx_BSidMask_t[6], *wmx_pBSidMask_t;

/// <summary>
/// Type definitions for variables that are fields of the wmx_ChannelInfo_t struct. 
/// </summary>
typedef UINT16 wmx_ChannelID_t, *wmx_pChannelID_t;
typedef UINT32 wmx_PPMFreqError_t, *wmx_pPPMFreqError_t;
typedef UINT8 wmx_Preambles_t[PREAMBLES_LENGTH], *wmx_pPreambles_t;

/// <summary>
/// Type definition for a variable containing the ID of a NSP. 
/// </summary>
typedef UINT32 wmx_NSPid_t, *wmx_pNSPid_t;

typedef UINT32 wmx_timestamp_t;

/// <summary>
/// Type definition for an enum specifying the possible bandwidths which can be set to the device as part of a wmx_ChannelInfo_t.
/// </summary>
typedef enum _wmx_BW_t
{
	BW_3_5 = 0x01,
	BW_5,
	BW_7,
	BW_8_75,
	BW_10
} wmx_BW_t, *wmx_pBW_t;


/// <summary>
/// Type definition for an enum specifying the possible ffts which can be set to the device as part of a wmx_ChannelInfo_t.
/// </summary>
typedef enum _wmx_FFT_t
{
	FFT_512 = 0x01,
	FFT_1024 = 0x02
} wmx_FFT_t, *wmx_pFFT_t;

/// <summary>
///	State reason includes information whether the report is due to successful operation or due to 
/// failure condition (with failure reason).
///
/// Values: (see WiMAX SDK API documentation)	
/// </summary>
typedef enum _wmx_StateReason_t
{
	StateReasonNormal = 0x01,
	StateReasonFailToConnectToNW,
	StateReasonFailToConnectRanging,
	StateReasonFailToConnectSBC,
	StateReasonFailToConnectEAPAuth,
	StateReasonFailToConnect3WayHandshake,
	StateReasonFailToConnectREG,
	StateReasonFailToConnectDatapath,
	StateReasonFailToConnectCoexNoRF,
	StateReasonDisconnectDreg,
	StateReasonDisconnectAbort,
	StateReasonDisconnectReset,
	StateReasonDisconnectDrop,
	StateReasonSplockValidationFailed,
	StateReasonDisconnectSecurity,
	StateReasonResetHwWdt,
	StateReasonResetSwWdt,
	StateReasonResetAssert,
	StateReasonResetThermal,
	StateReasonResetRfKill,
	StateReasonResetCoExistence,
	StateReasonResetHost,
	StateReasonDisconnectProtocolError,
	StateReasonFWRequestDevReset,
	StateReasonFWRequestFuncReset,
}wmx_StateReason_t, *wmx_pStateReason_t;

static inline
const char * WMX_STATE_REASON_STR(unsigned index)
{
	static const char *wmx_StateReason_tStr[] = {
		"Illegal value",
		"Normal",
		"Failed to connect to NW",
		"Failed to connect - Ranging",
		"Failed to connect - SBC",
		"Failed to connect - EAPAuth",
		"Failed to connect - 3WayHandshake",
		"Failed to connect - REG",
		"Failed to connect - Datapath",
		"Failed to connect - CoexNoRF",
		"Disconnected - Dreg",
		"Disconnected - Abort",
		"Disconnected - Reset",
		"Disconnected - Drop",
		"SPLock validation failed",
		"Disconnected - ReAuth",
		"Reset - HwWdt",
		"Reset - SwWdt",
		"Reset - Assert",
		"Reset - Thermal",
		"Reset - RfKill",
		"Reset - CoExistence",
		"Reset - Host",
		"Disconnected - Protocol Error",
		"FW Requested Reset - Device",
		"FW Requested Reset - Function"
	};
	static const unsigned count =
		sizeof(wmx_StateReason_tStr) / sizeof(wmx_StateReason_tStr[0]);
	if (index < count)
		return wmx_StateReason_tStr[index];
	else
		return "Illegal";
}


/// <summary>
/// Type definition for an enum specifying the possible outcomes of a connect attempt.
///
/// Values:
///	ConnectSuccessful		// connect completed successfully
/// ConnectCancelled		// connect was canceled
///	ConnectFailed			// connect failed because network not found, bad handshake,...
/// 
/// </summary>
typedef enum _wmx_ConnectStatus_t
{
	ConnectSuccessful = 0x1,	// connect completed successfully
	ConnectCancelled,			// connect was canceled
	ConnectFailToConnectToNW,
	ConnectFailToConnectRanging,
	ConnectFailToConnectSBC,
	ConnectFailToConnectEAPAuth,
	ConnectFailToConnect3WayHandshake,
	ConnectFailToConnectREG,
	ConnectFailToConnectDatapath,
	ConnectFailToConnectCoexNoRf,
	ConnectDisconnectDreg,
	ConnectDisconnectAbort,
	ConnectDisconnectReset,
	ConnectDisconnectDrop,
	ConnectFailed				// connect failed because network not found, bad handshake,...
} wmx_ConnectStatus_t, *wmx_pConnectStatus_t;

/// <summary>
/// Indicates whether the link is up or down
/// </summary>
typedef enum _wmx_MediaStatus_t
{
	LinkUp = 0x01,
	LinkDown,
	LinkRenew
} wmx_MediaStatus_t, *wmx_pMediaStatus_t;

static char *wmxMediaStatusName[] = {
	"LinkUp",
	"LinkDown",
	"LinkRenew"
};

/// <summary>
/// (IN) A wmx_ConnectProgressInfo_t enum giving further information on the progress of a connection attempt.
///
/// The values are applicable when the system state is Connecting. Otherwise its value will be NotApplicable.
/// </summary>
typedef enum _wmx_ConnectProgressInfo_t
{
	NotApplicable,   // Used when the system state is not connecting
	Ranging,
	SBC,
	EAPAuthentication,
	ThreeWayHandshake,
	Registration	
}wmx_ConnectProgressInfo_t, *wmx_pConnectProgressInfo_t;

static char *wmxConnectProgressInfoName[] = {
	"NotApplicable",
	"Ranging",
	"SBC",
	"EAPAuthentication",
	"ThreeWayHandshake",
	"Registration"
};

/// <summary>
/// Represents the possible types of the scan process
/// </summary>
typedef enum _wmx_ScanType_t
{
	SCAN_TYPE_PREFERRED,
	SCAN_TYPE_WIDE,
	SCAN_TYPE_RECONNECT,
	SCAN_TYPE_AUTO_CONNECT,
	SCAN_TYPE_DIRECT
} wmx_ScanType_t, *wmx_pScanType_t;

static char *wmx_ScanType_tStr[] = {
	"Preferred Scan",
	"Wide Scan",
	"Scan for reconnect",
	"Scan for auto connect",
	"Direct Scan"
};

typedef enum _wmx_LinkLossType_t
{
	LinkLossType_Short,
	LinkLossType_Long,
	LinkLossType_Infinite
} wmx_LinkLossType_t;

static char* wmx_LinkLossType_tStr[] = {
	"Short Link Loss",
	"Long Link Loss",
	"Infinite Link Loss"
};

typedef enum _wmx_ConnectionType_t
{
	CONN_TYPE_HOME,
	CONN_TYPE_ROAM,
	CONN_TYPE_ACTIVATE
} wmx_ConnectionType_t, *wmx_pConnectionType_t;

/// <summary>
/// Type definition for an enum specifying the RF status of the device.
///
/// Values:
///	On 
///	Off
///
/// </summary>
typedef enum _wmx_RfStatus_t
{
	Off = 0x0,
	On	
} wmx_RfStatus_t, *wmx_pRfStatus_t;



/// <summary>
/// Type definition for an enum specifying the possible device's association modes.
/// </summary>
typedef enum _wmx_Associate_t
{
	Associated,
	Not_Associated
} wmx_Associate_t, *wmx_pAssociate_t;

/// <summary>
/// Type definition for an enum specifying the possible WiMAX system states the device can be in.
///
/// Values: (see WiMAX SDK API documentation)
/// </summary>
typedef enum _wmx_SystemState_t
{
	UnInitialized,
	Config,
	Initialized,
	Production,
	RfOff,
	Ready,
	Scan,
	//OOZ,
	//Standby,
	Connecting,
	WimaxConnected,
	DataPathConnected,
	Idle,
	//SleepActive,
	Disconnecting,
	RfShutDown,
	UnknownState
}wmx_SystemState_t, *wmx_pSystemState_t;

static char* NDnSSystemStates[] = {
	"UnInitialized",
	"Config",
	"Initialized",
	"Production",
	"RfOff",
	"Ready",
	"Scan",
//	"OOZ",
//	"Standby",
	"Connecting",
	"WimaxConnected",
	"DataPathConnected",
	"Idle",
//	"SleepActive",
	"Disconnecting",
	"RfShutDown",
	"UnknownState"
};

typedef enum _wmx_ProvisioningOperation_t
{
	poUpdateStarted,
	poUpdateCompleted,
	poUpdateFailedNetworkDisconnect,
	poUpdateFailed,
	poUpdateFailedInvalidProvisioning,
	poUpdateFailedBadAuthentication,
	poUpdateRequestInitialProvisioning,
	poUpdateRequestOngoingProvisioning,
	poUpdateWaitingForBootstrap,
	poUpdateBootstrapArrived,
	poUpdateLoadWebBrowser 
} wmx_ProvisioningOperation_t, *wmx_pProvisioningOperation_t;

typedef enum _wmx_PermissionUpdateEvent_t
{
	PrivilegeReadWriteTaken,
	PrivilegeReadWriteAvailable
} wmx_PermissionUpdateEvent_t, *wmx_pPermissionUpdateEvent_t;

typedef struct _wmx_ProvisioningOperationInfo_t
{
	wmx_ProvisioningOperation_t provisioningOperation;
	UINT16 contactType;
}wmx_ProvisioningOperationInfo_t, *wmx_pProvisioningOperationInfo_t;

typedef enum _wmx_PackageUpdateStatus_t
{
	psUpdateReceived,
	psUpdateReceivedLowerStack,
	psUpdateReceivedFullStack,
	psUpdateReceivedOmaDmClient,
	psUpdateStarted,
	psUpdateCompleted,
	psUpdateFailedNetworkDisconnected,
	psUpdateFailedInvalidPackage,
	psUpdateFailedBadAuthentication,
	psUpdateFailed,
	psUpdateFumoDownloadProgress
} wmx_PackageUpdateStatus_t, *wmx_pPackageUpdateStatus_t;

typedef struct _wmx_PackageDownloadProgressInfo_t
{
	UINT32 downloadedBytes;
	UINT32 totalBytes;
} wmx_PackageDownloadProgressInfo_t, *wmx_pPackageDownloadProgressInfo_t;

/// <summary>
/// Type definition for a structure giving the status (On, Off) of the HW, SW & thermal RF switches.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_RfSwitchesStatus_t
{ 
	wmx_RfStatus_t swRfStatus;
	wmx_RfStatus_t hwRfStatus;
}wmx_RfSwitchesStatus_t, *wmx_pRfSwitchesStatus_t;

/// <summary>
/// A struct in which the API will place information (such as URLs, VoIP numbers, �) that are relevant to the
/// status & reason indicated (example: The URL of the Subscriptions Portal when the HotlineNotification
/// status & SubscriptionCreation reason are indicated).
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_APDOContactInfo_t
{
	char	contactDetails[MAX_CONTACT_DETAILS_SIZE];
} wmx_APDOContactInfo_t, *wmx_pAPDOContactInfo_t;

/// <summary>
/// A struct in which the API will place information which is needed in the package update process.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_PackageInfo_t
{
	UINT32	structureSize;                       /**< size of this structure. */
	char	filePath[MAX_SIZE_OF_STRING_BUFFER]; /**< file path. */ 
	char	fileName[MAX_SIZE_OF_STRING_BUFFER]; /**< file name. */ 
	BOOL	forceReboot;                         /**< (TRUE = Reboot required, FALSE No reboot required)*/
	BOOL	mandatoryUpdate;                     /**< (TRUE = mandatory FALSE, optional) */
	BOOL	warnUser;                            /**< (TRUE = warn user, FALSE = no user warning */
} wmx_PackageInfo_t, *wmx_pPackageInfo_t;

typedef enum _wmx_SPLockStatus_t
{
	SP_LOCK_STATUS_LOCKED = 0x00,
	SP_LOCK_STATUS_UNLOCKED = 0x01
}wmx_SPLockStatus_t, *wmx_pSPLockStatus_t;

typedef struct _wmx_SpLock_t
{
	wmx_SPLockStatus_t	sPLockStatus;
	UINT16				NSPNameActualLen;
	UINT8				NSPNameBuff[MAX_VERBOSE_NSP_NAME_SIZE];
}wmx_SpLock_t, *wmx_pSpLock_t;

typedef struct _wmx_SpLockCode_t
{
	UINT16 ActualLen;
	UINT8 BufferArr[MAX_SP_LOCK_CODE_SIZE];

}wmx_SpLockCode_t, *wmx_pSpLockCode_t;

/// <summary>
/// Type definition for a struct containing information of a specific channel in a channel plan.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_ChannelInfo_t
{
	wmx_ChannelID_t				channelID;
	wmx_Frequency_t				frequency;			// The value in KHz in the range of 2.2Ghz � 6Ghz in resolution of  KHz
	wmx_BW_t					bw;					// 3.5Mhz, 5.0MHz, 7.5Mhz, 8.75Mhz, 10Mhz, 14Mhz and 20Mhz
	wmx_FFT_t					fft;
	wmx_Preambles_t				preambleBitmap;		// A 114 bit map specifying the supported preambles
} wmx_ChannelInfo_t, *wmx_pChannelInfo_t;
#pragma pack( pop )


/// <summary>
/// A struct in which the API will place information which is needed in the package update process.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_InstallationInfo_t
{
	UINT32	structureSize;									 /**< size of this structure. */
	char	swVersion[MAX_INSTALLAION_VERSION_SIZE];		 /**< The version of the package which was installed. */ 
	char	fwVersion[MAX_INSTALLAION_VERSION_SIZE];		 
	char	hwVersion[MAX_INSTALLAION_VERSION_SIZE];
} wmx_InstallationInfo_t, *wmx_pInstallationInfo_t;

#endif // _WMX_SDK_NDS_CMN_H
