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
#ifndef _WMX_SDK_NDS_3_H
#define _WMX_SDK_NDS_3_H


#include "wmxSDK_Nds_Cmn.h"
#include "wmxSDK_Nds_1.h"
#include "WiMaxTypesEx.h"

/// <summary>
/// Constants specifying the maximal lengths.
/// </summary>
#define WMX_NSP_NAME_MAX_SIZE 64

#define WMX_MAX_HOST_NAME_NAME 1000

#define WMX_NSP_REALM_MAX_SIZE 100

#define WMX_NSP_IDS_MAX_NUM 16

#define WMX_NSP_SUBSCRIBERS_MAX_NUM 2

#define WMX_URI_MAX_SIZE 100

#define WMX_URI_MAX_NUM 5

#define WMX_CRED_USERNAME_MAX_SIZE 64

#define WMX_CRED_PASSWORD_MAX_SIZE 253

typedef UINT32 wmx_APDOversion_t, *wmx_pAPDOversion_t;

#define MAX_ACCOUNT_NAME_SIZE			100		

/// <summary>
/// Type definition for an enum specifying the possible user connection modes which can be set to the device.
/// </summary>
typedef enum _wmx_UserConnectMode_t
{
	//UserAutoConnection = 0x1,
	//UserManualConnection
	UserSemiManScanManConnect = 0x1,
	UserSemiManScanAutoConnect,
	UserAutoScanManConnect,
	UserAutoScanAutoConnect,
	UserManScanManConnect
} wmx_UserConnectMode_t, *wmx_pUserConnectMode_t;

/// <summary>
/// Type definition for an enum specifying the possible user package download approval options
/// </summary>
typedef enum _wmx_PackageUpdateState_t
{
	PackageUpdateDenied = 0x1,
	PackageUpdateApproved	
} wmx_PackageUpdateState_t, *wmx_pPackageUpdateState_t;

/// <summary>
/// Type definition for an enum specifying the possible user roaming modes which can be set to the device.
/// </summary>
typedef enum _wmx_UserRoamingMode_t
{
	UserEnableRoaming = 0x1,
	UserDisableRoaming
} wmx_UserRoamingMode_t, *wmx_pUserRoamingMode_t;

typedef struct _wmx_UserCredentials_t
{
	char username[WMX_CRED_USERNAME_MAX_SIZE+1];
	char password[WMX_CRED_PASSWORD_MAX_SIZE+1];
} wmx_UserCredentials_t, *wmx_pUserCredentials_t;

/// <summary>
/// Type definition for a variable containing the SLA of a NSP. 
/// </summary>
//typedef UINT32 wmx_SLA_t, *wmx_pSLA_t;
#pragma pack( push, 1 )
typedef struct _wmx_SLA_t
{
	wmx_LinkSpeed_t		upLinkSpeed;
	wmx_LinkSpeed_t		downLinkSpeed;
	UINT32				agreementLevel;
} wmx_SLA_t, *wmx_pSLA_t;
#pragma pack( pop )

#define WMX_SUBSCRIBER_NAME_MAX_SIZE 100
#define WMX_SUBSCRIBER_ID_MAX_SIZE 256

#pragma pack( push, 1 )
typedef struct _wmx_SubscriberInfo_t
{
	char					id[WMX_SUBSCRIBER_ID_MAX_SIZE];
	char					name[WMX_SUBSCRIBER_NAME_MAX_SIZE];
	wmx_SLA_t				SLA;	// TODO: Oran - remove
	//////////////////
	// V3.0 new
	BOOL					userCredRequired;
	//////////////////
} wmx_SubscriberInfo_t, *wmx_pSubscriberInfo_t;
#pragma pack( pop )

/// <summary>
/// Type definition for a struct containing information of a specific NSP.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_NSP_t
{
	char					nspName[WMX_NSP_NAME_MAX_SIZE];
	char					nspRealm[WMX_NSP_REALM_MAX_SIZE];	
	wmx_NSPid_t				nspIDs[WMX_NSP_IDS_MAX_NUM];		// An NSP may have multiple NSP_IDs associated with it.
	UINT32					numOfNspIDs;
	BOOL					isHomeNSP; // always TRUE for 2.0 EP
	BOOL					isRoamingPartner;
	wmx_NSPid_t				roamToNsps[WMX_NSP_IDS_MAX_NUM];		// all Home NSPs that this NSP is known to be a roaming partner of.
	UINT32					numOfRoamToNsps;
	BOOL					allowGuests;
	wmx_LinkQuality_t		linkQuality;
	wmx_SignalStrength_t	bestRssi;
	wmx_SignalStrength_t	bestCINR;
	BOOL					activated; // always TRUE for 2.0 EP
	wmx_APDOversion_t		apdoVer;		// The version of the APDO data package provisioned by the NSP to this device.
	wmx_SubscriberInfo_t	subscribers[WMX_NSP_SUBSCRIBERS_MAX_NUM];		// The list of subscribers associated with this NSP on this device.
	UINT32					numOfSubscribers;
} wmx_NSP_t, *wmx_pNSP_t;
#pragma pack( pop )

// TODO: Add description
#pragma pack( push, 1 )
typedef struct _wmx_ContactInformation_t
{
	char	uri[WMX_URI_MAX_SIZE];
	UINT32	uriType; //TODO - don't forget to validate the values 0-255
	char	text[MAX_SIZE_OF_STRING_BUFFER];
} wmx_ContactInformation_t, *wmx_pContactInformation_t;
#pragma pack( pop )

/// <summary>
/// Type definition for an enum specifying the possible outcomes of a scan cycle.
///
/// Values:
///	UserScanSuccessful		// done scanning the whole channel plan and NSPs were found
///	UserScanExhausted		// done scanning the whole channel plan and NSPs weren't found
///	UserScanStopped			// scan was stopped
///	UserScanFailed			// scan failed
///
/// </summary>
typedef enum _wmx_UserScanStatus_t
{
	UserScanSuccessful = 0x1,		// done scanning the whole channel plan and NSPs were found
	UserScanExhausted,				// done scanning the whole channel plan and NSPs weren't found
	UserScanStopped,				// scan was stopped
	UserScanFailed					// scan failed
} wmx_UserScanStatus_t, *wmx_pUserScanStatus_t;


/// <summary>
/// Type definition for an enum specifying the possible outcomes of a connect attempt.
///
/// Values:
///	UserConnectSuccessful		// connect completed successfully
/// UserConnectCancelled		// connect was canceled
///	UserConnectFailed			// connect failed because network not found, bad handshake,...
///
/// </summary>
typedef enum _wmx_UserConnectStatus_t
{
	UserConnectSuccessful = 0x1,	// connect completed successfully
	UserConnectCancelled,			// connect was canceled
	UserConnectFailToConnectToNW,
	UserConnectFailToConnectRanging,
	UserConnectFailToConnectSBC,
	UserConnectFailToConnectEAPAuth,
	UserConnectFailToConnect3WayHandshake,
	UserConnectFailToConnectREG,
	UserConnectFailToConnectDatapath,
	UserConnectFailToConnectCoexNoRf,
	UserConnectDisconnectDreg,
	UserConnectDisconnectAbort,
	UserConnectDisconnectReset,
	UserConnectDisconnectDrop,
	UserConnectFailed,				// connect failed because network not found, bad handshake,...
	UnknownConnectStatus
} wmx_UserConnectStatus_t, *wmx_pUserConnectStatus_t;

/// <summary>
/// Type definition for a struct containing information about the link's status.
/// (i.e. the status of the link between the device and the network it is connected to).
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_UserLinkStatus_t
{
	wmx_SignalStrength_t		rssi;		// the strength (in %) of the RF signal
	wmx_CINR_t					cinr;
	wmx_Frequency_t				frequency;
	wmx_Power_t					power;
	wmx_LinkQuality_t			linkQuality;
	wmx_ConnectionTime_t		time;
	wmx_LinkSpeed_t				upLinkSpeed;
	wmx_LinkSpeed_t				downLinkSpeed;
	wmx_BSid_t					bsId;
} wmx_UserLinkStatus_t, *wmx_pUserLinkStatus_t;
#pragma pack( pop )

#pragma pack( push, 1 )
typedef struct _wmx_UserStatistics_t
{
	UINT32  timeStamp;
	UINT32	TotalRxBytes;
	UINT32	TotalRxPackets;
	UINT32	TotalTxBytes;
	UINT32	TotalTxPackets;
} wmx_UserStatistics_t, *wmx_pUserStatistics_t;
#pragma pack( pop )

/// <summary>
/// A constant specifying the maximal length of a NSPs structs vector (in terms of the number of wmx_NSP_t structs the vector can contain).
/// </summary>
#define WMX_NSPS_MAX_NUM WMX_IDS_MAX_NUM

/// <summary>
/// Type definition for an enum specifying the possible device statuses.
/// </summary>
typedef enum _wmx_DeviceStatus_t
{
	DeviceStatus_UnInitialized = 0x1,
	DeviceStatus_RF_OFF_HW_SW,
	DeviceStatus_RF_OFF_HW,
	DeviceStatus_RF_OFF_SW,
	DeviceStatus_Ready,
	DeviceStatus_Scanning,
	DeviceStatus_Connecting,
	DeviceStatus_Data_Connected
} wmx_DeviceStatus_t, *wmx_pDeviceStatus_t;

typedef enum _wmx_StatusReason_t
{
	DeviceStatusReason_Normal,
	DeviceStatusReason_Fail_to_connect_to_NW,
	DeviceStatusReason_Fail_to_connect_Ranging,
	DeviceStatusReason_Fail_to_connect_SBC,
	DeviceStatusReason_Fail_to_connect_EAP_AUTH_Device,
	DeviceStatusReason_Fail_to_connect_EAP_AUTH_User,
	DeviceStatusReason_Fail_to_connect_3_Way_Handshake,
	DeviceStatusReason_Fail_to_connect_REG,
	DeviceStatusReason_Fail_to_connect_datapath
} wmx_StatusReason_t, *wmx_pStatusReason_t;

typedef enum _wmx_ConnectionProgressInfo_t
{
	DeviceConnectionProgress_Ranging = 0x1,
	DeviceConnectionProgress_SBC,
	DeviceConnectionProgress_EAP_authentication_Device,
	DeviceConnectionProgress_EAP_authentication_User,
	DeviceConnectionProgress_3_way_handshake,
	DeviceConnectionProgress_Registration,
	DeviceConnectionProgress_De_registration,
	DeviceConnectionProgress_Registered
}wmx_ConnectionProgressInfo_t, *wmx_pConnectionProgressInfo_t;

/// <summary>
/// The signature defintion of a wmx_pUserScanCompletedCB_t callback function. 
///
/// Once registered, this callback function will be called upon scan cycle completion, and at least once for every time wmx_CmdUserStartScan was called successfully.
/// </summary>
///
/// <param name="userScanStatus">(IN) A wmx_UserScanStatus_t enum providing the status of the scan cycle that has finished.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pUserScanCompletedCB_t)( wmx_UserScanStatus_t userScanStatus);

/// <summary>
/// The signature defintion of a wmx_pUserScanUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever scan results are available.
///
/// This callback returns all NSPs aggregated since the beginning of the current scan.
///
/// The list is given as a vector of NSP information structs.
/// The vector's size is given using the pNumOfNsps argument (in terms of the number of wmx_NSP_t structs the vector contains).
/// The API can fill a vector of up to WMX_NSPS_MAX_NUM of wmx_NSP_t structs
/// (i.e. at maximum (WMX_NSPS_MAX_NUM * sizeof(wmx_NSP_t)) bytes).
///
/// The memory allocation for the NSPs vector will be valid only for the duration of the callback. The user must copy any information he needs to memory he allocated.
/// </summary>
///
/// <param name="numOfNsps">(IN) A UINT32 specifying the number of NSPs in the nsps vector.</param>
/// <param name="pNsps">(IN) A pointer to a wrapper allocated buffer which contains a vector of wmx_NSP_t structs containing information about the NSPs discovered in the scan operation so far.</param>
/// <param name="scanProgress">(IN) A UINT32 indicating the progress of the scan as a percentage.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pUserScanUpdateCB_t)( UINT32 numOfNsps, wmx_pNSP_t pNsps, UINT32 scanProgress );

/// <summary>
/// The signature definition of a wmx_pUserMediaStatusCB_t callback function. 
///
/// Once registered, this callback function will be called whenever the media status ofthe device is in changes.
/// </summary>
///
/// <param name="mediaStatus">(IN) An enum of type wmx_MediaStatus_t indicating if the link is up or down.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pUserMediaStatusCB_t)(	wmx_MediaStatus_t mediaStatus ) ;

/// <summary>
/// The signature defintion of a wmx_pUserSystemStateUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever the WiMAX system state the device is in changes.
/// </summary>
///
/// <param name="systemState">(IN) A wmx_SystemState_t enum specifying the WiMAX system state.</param>
/// <param name="stateReason">(IN) Reason includes information whether the report is due to successful 
///									operation or due to failure condition (with failure reason).</param>
/// <param name="userLinkStatus">(IN) A pointer to a wmx_UserLinkStatus_t struct in which the API will place information about the link's status.</param>
/// <param name="mediaStatus">(IN) A pointer to a wmx_MediaStatus_t struct indicating if the link is up or down.</param>
/// <param name="connectProgressInfo">(IN) A wmx_ConnectProgressInfo_t enum giving further information on the progress of a connection attempt.
///		This parameter is only relevant if the systemState reported is Connecting. Otherwise its value will be NotApplicable.</param>
/// <param name="rfSwitchesStatus">(IN) A wmx_RfSwitchesStatus_t struct giving the status (On, Off) of the HW & SW RF switches.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pUserSystemStateUpdateCB_t)(	wmx_SystemState_t systemState,
																	wmx_StateReason_t stateReason,
																	wmx_UserLinkStatus_t userLinkStatus,
																	wmx_MediaStatus_t mediaStatus,
																	wmx_ConnectProgressInfo_t connectProgressInfo,
																	wmx_RfSwitchesStatus_t rfSwitchesStatus) ;


typedef void (WMX_EXT_CALL_CONV *wmx_pIndDeviceStatusUpdateCB_t) ( wmx_DeviceStatus_t deviceStatus, wmx_ConnectionProgressInfo_t connectionProgressInfo);

// This notification is called when the PNM channel is updated.
typedef void (WMX_EXT_CALL_CONV *wmx_pIndDevicePNMNotificationCB_t) (void);

typedef void (WMX_EXT_CALL_CONV *wmx_pIndPermissionsUpdateCB_t) (wmx_PermissionUpdateEvent_t updateEvent);

typedef void (WMX_EXT_CALL_CONV *wmx_pIndProvisioningOperationCB_t) (	wmx_ProvisioningOperation_t	provisioningOperation, UINT16 contactType );

// The callback is invoked when a new NSP is selected to be the current preferred NSP
typedef void (WMX_EXT_CALL_CONV *wmx_pIndCurrentPreferredProfileCB_t) (	UINT32 numOfCurrentPreferredNSPs, wmx_pNSP_t currentPreferredNsps);

// The callback is called during FUMO process. 
typedef void (WMX_EXT_CALL_CONV *wmx_pIndPackageUpdateCB_t) (	wmx_PackageUpdateStatus_t packageUpdateStatus );
// The callback is called while FUMO is downloading.
typedef void (WMX_EXT_CALL_CONV *wmx_pIndPackageDownloadProgressCB_t) ( wmx_PackageDownloadProgressInfo_t packageDownloadProgressinfo );
/// The signature defintion of a wmx_pConnectionModeUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called upon connection mode changes.
/// </summary>
///
/// <param name="connectionModeUpdate">(IN) A wmx_ConnectionMode_t enum providing the status of the connection mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pIndConnectionModeUpdateCB_t)( wmx_ConnectionMode_t connectionModeUpdate);

/// <summary>
/// The signature defintion of a wmx_pFastReconnectStatusUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called upon FastReconnect mode changes.
/// </summary>
///
/// <param name="fastReconnectStatusUpdate">(IN) BOOL providing the status of the FastReconnect mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pIndFastReconnectStatusUpdateCB_t)( BOOL fastReconnectStatusUpdate);

/// <summary>
/// The signature defintion of a wmx_pRoamingModeUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called upon Roaming mode changes.
/// </summary>
///
/// <param name="fastReconnectCapabilityStatusUpdate">(IN) A wmx_RoamingMode_t enum providing the status of the Roaming mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pIndRoamingModeUpdateCB_t)( wmx_RoamingMode_t roamingModeUpdate);

/// <summary>
/// The signature defintion of a wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t callback function. 
///
/// Once registered, this callback function will be called upon change in the isEnableConnectedAsCurrentPreferred mode.
/// </summary>
///
/// <param name="connectedAsCurrentPreferredCapabilityStatus">(IN) BOOL providing the status of the isEnableConnectedAsCurrentPreferred mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t)( BOOL connectedAsCurrentPreferredCapabilityStatus);

/// <summary>
/// The signature defintion of a RF taken callback function. 
///
/// Once registered, this callback function will be called when RF taken is signalled.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pRfTakenCB_t)( void );

/// <summary>
/// This API switches on the RF function of the WiMAX device.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RfOn(); 

 
/// <summary>
/// This API switches off the RF function of the WiMAX device.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RfOff();

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetNSPContactInfoByName(char* nspName, UINT32 *pNumOfContacts, wmx_pContactInformation_t pContactInformation);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetContactInformation(wmx_NSPid_t nspId, UINT32 *pNumOfContacts, wmx_pContactInformation_t pContactInformation);

/// <summary>
/// This API causes the device to perform a scan operation and return the list of detected NSPs. 
///
/// This is a blocking API. It returns to the caller after a single full scan cycle is completed 
/// (a process that may take several seconds to several minutes). 
/// A complete scan cycle will go through the whole channel plan.
/// Unlike the wmx_CmdUserStartScan() API, wmx_CmdUserScan() triggers only the single scan cycle and scanning
/// will stop when that cycle ends and the API returns.
///
/// The detected NSPs list is given as a vector of NSP information structs.
///
/// The user must allocate space for the vector in advance and state its size using the pNumOfNsps argument 
/// (in terms of the number of wmx_NSP_t structs the vector may contain).
///
/// The API can fill a vector of up to WMX_NSPS_MAX_NUM of wmx_NSP_t structs
/// (i.e. at maximum the user should allocate (WMX_NSPS_MAX_NUM * sizeof(wmx_NSP_t)) bytes).
/// The value entered by the user in pNumOfNsps will reflect the number of wmx_NSP_t structs
/// which can be contained in the space allocated (by the user) for the pNsps vector. 
/// The API will return in pNumOfNsps the actual number of structs in the vector that were 
/// filled with data (0 if no NSPs are found).
/// </summary>
///
/// <param name="scanType">(IN) An enum, allowing the specification of the scan�s span. </param>
/// <param name="status">(OUT) A pointer to a user-allocated wmx_pUserScanStatus_t enum to which the API will place the scan completion status.</param>
/// <param name="pNumOfNsps">(INOUT) A pointer to a user-allocated UINT32 containing the expected number of NSPs as input and the actual number of NSPs in the pNsps vector as output.</param>
/// <param name="pNsps">(OUT) A pointer to a user-allocated buffer which will be filled with a vector of wmx_NSP_t structs containing information about the NSPs discovered in the scan operation. A NULL is returned when no NSPs are found.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserScan( wmx_ScanType_t scanType, wmx_pUserScanStatus_t status, UINT32* pNumOfNsps, wmx_pNSP_t pNsps );

/// <summary>
/// This API causes the device to start direct scan on the given channels.
///
/// </summary>
///
/// <param name="pChannelsInfoList">(IN) A list of channels to scan. </param>
/// <param name="pDuplexMode">(IN) Duplex mode to set to the device. </param>
/// <param name="listSize">(IN) Number of channels to scan. </param>
/// <param name="isBlocking">(IN) Specifies whether scan results return through normal pipe. </param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStartScanDirect(wmx_pChannelInfo_t pChannelsInfoList, wmx_pDuplexMode_t pDuplexMode, UINT32 listSize, BOOL isBlocking);

/// <summary>
/// This API causes the device to start a scan operation.
/// 
/// Unlike the �CmdUserScan� API, this is a non-blocking API. It returns after the scan request was issued to the driver.
///
/// To get the results of the scan operation (i.e. the detected NSPs), the user can register a callback function using the wmx_RegisterUserScanUpdateCB API.
/// To get notification of the scan operation completion, the user can register a callback function using the wmx_RegisterUserScanCompletedCB API.
///
/// A complete scan cycle will go through the whole channel plan. Completion of a scan cycle will trigger a registered wmx_pUserScanCompletedCB_t callback.
/// However, scanning cycles will repeat forever!! until one of the following occurs:
/// 1. The user invokes the wmx_CmdUserStopScan API.
/// 2. The user invokes the wmx_CmdUserConnect API to start a connection attempt to one of the discovered NSPs.
/// 3. The user changes the RF state to Off.
/// 4. A problem prohibits the device from continuing the scan.
///
/// Important: When a connection is lost or wmx_CmdUserDisconnect() is called, if the connection mode is UserManual
/// and wmx_CmdUserStopScan() was not sent down, the driver will revert to making scanning cycles and scan updates may be sent up.
/// </summary>
///
/// <param name="scanType">(IN) An enum, allowing the specification of the scan�s span. </param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStartScan( wmx_ScanType_t scanType );

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStartScanDirect(wmx_pChannelInfo_t pChannelsInfoList, wmx_pDuplexMode_t pDuplexMode, UINT32 listSize, BOOL isBlocking);

/// <summary>
/// This API causes the device to stop a scan operation.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStopScan( );

/// <summary>
/// The registration API for a wmx_pIndCurrentPreferredProfileCB_t callback function.
/// </summary>
///
/// <param name="userScanUpdateCB">(IN) A pointer to the application function to be called when a new NSP is selected to be the current preferred NSP.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterCurrentPreferredProfileCB( wmx_pIndCurrentPreferredProfileCB_t currentPreferredProfileCB);


/// <summary>
/// The de-registration API for a wmx_pIndCurrentPreferredProfileCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterCurrentPreferredProfileCB();

/// <summary>
/// The registration API for a wmx_pUserScanCompletedCB_t callback function.
/// </summary>
///
/// <param name="userScanCompletedCB">(IN) A pointer to the application function to be called upon scan cycle completion.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserScanCompletedCB( wmx_pUserScanCompletedCB_t userScanCompletedCB);

/// <summary>
/// The de-registration API for a wmx_pUserScanCompletedCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserScanCompletedCB();


/// <summary>
/// The registration API for a wmx_pUserScanUpdateCB_t callback function.
/// </summary>
///
/// <param name="userScanUpdateCB">(IN) A pointer to the application function to be called when scan results are available.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserScanUpdateCB( wmx_pUserScanUpdateCB_t userScanUpdateCB);


/// <summary>
/// The de-registration API for a wmx_pUserScanUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserScanUpdateCB();

/// <summary>
/// The registration API for a wmx_pUserSystemStateUpdateCB_t callback function.
/// </summary>
///
/// <param name="userSystemStateUpdateCB">(IN) A pointer to the application function to be called when system state is changed.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserSystemStateUpdateCB( wmx_pUserSystemStateUpdateCB_t userSystemStateUpdateCB );


/// <summary>
/// The de-registration API for a wmx_pUserSystemStateUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserSystemStateUpdateCB();

/// <summary>
/// The registration API for a wmx_pUserMediaStatusCB_t callback function.
/// </summary>
///
/// <param name="userMediaStatusCB">(IN) A pointer to the application function to be called when media statys is changed.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserMediaStatusCB( wmx_pUserMediaStatusCB_t userMediaStatusCB );


/// <summary>
/// The de-registration API for a wmx_pUserMediaStatusCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserMediaStatusCB();

/// <summary>
/// The registration API for a wmx_pDeviceStatusUpdateCB_t callback function.
/// </summary>
///
/// <param name="deviceStatuspdateCB">(IN) A pointer to the application function to be called when the device status changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterDeviceStatusUpdateCB( wmx_pIndDeviceStatusUpdateCB_t deviceStatuspdateCB );


/// <summary>
/// The de-registration API for a wmx_pDeviceStatusUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterDeviceStatusUpdateCB();


/// <summary>
/// The de-registration API for a wmx_pDeviceStatusUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterPermisssionsUpdateCB();




/// <summary>
/// The registration API for a wmx_pIndDevicePNMNotificationCB_t callback function.
/// </summary>
///
/// <param name="deviceStatuspdateCB">(IN) A pointer to the application function to be called when the device status changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterPNMNotificationCB(wmx_pIndDevicePNMNotificationCB_t infPNMNotificationCB);

/// <summary>
/// The de-registration API for a wmx_pIndDevicePNMNotificationCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterPNMNotificationCB();
											   

/// <summary>
/// The registration API for a wmx_pUserAPDOStatusUpdateCB_t callback function.
/// </summary>
///
/// <param name="refreshApdoSessionStatusCB">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserAPDOStatusUpdateCB( wmx_pUserAPDOStatusUpdateCB_t userAPDOStatusUpdateCB);


/// <summary>
/// The de-registration API for a wmx_pUserAPDOStatusUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserAPDOStatusUpdateCB();


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterIndProvisioningOperationCB( wmx_pIndProvisioningOperationCB_t indProvisioningOperationCB);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterIndProvisioningOperationCB();

/// <summary>
/// The registration API for a wmx_pIndPackageUpdateCB_t callback function.
/// </summary>
///
/// <param name="indPackageUpdateCB">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterIndPackageUpdateCB( wmx_pIndPackageUpdateCB_t indPackageUpdateCB );

/// <summary>
/// The de-registration API for a wmx_pIndPackageUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterIndPackageUpdateCB();

/// <summary>
/// The registration API for a wmx_pIndPackageDownloadProgressCB_t callback function.
/// 
/// <param name="indPackageDownloadProgressCB">(IN) A pointer to the application function to be called (more details in the callback's definition).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterIndPackageDownloadProgressCB( wmx_pIndPackageDownloadProgressCB_t indPackageDownloadProgressCB);

/// <summary>
/// The de-registration API for a wmx_pIndPackageDownloadProgressCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterIndPackageDownloadProgressCB();

/// <summary>
/// The registration API for a wmx_pConnectionModeUpdateCB_t callback function.
/// </summary>
///
/// <param name="connectModeCB">(IN) A pointer to the application function to be called upon connection mode changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectionModeUpdateCB( wmx_pIndConnectionModeUpdateCB_t connectModeCB );


/// <summary>
/// The de-registration API for a wmx_pConnectionModeUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectionModeUpdateCB();

/// <summary>
/// The registration API for a wmx_pFastReconnectUpdateCB_t callback function.
/// </summary>
///
/// <param name="fastReconnectStatusCB">(IN) A pointer to the application function to be called upon FastReconnect mode changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterFastReconnectStatusUpdateCB( wmx_pIndFastReconnectStatusUpdateCB_t fastReconnectStatusCB );


/// <summary>
/// The de-registration API for a wmx_pFastReconnectStatusUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterFastReconnectStatusUpdateCB();

/// <summary>
/// The registration API for a wmx_pRoamingModeUpdateCB_t callback function.
/// </summary>
///
/// <param name="roamingReconnectModeCB">(IN) A pointer to the application function to be called upon Roaming mode changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRoamingModeUpdateCB( wmx_pIndRoamingModeUpdateCB_t roamingModeCB );


/// <summary>
/// The de-registration API for a wmx_pRoamingModeUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRoamingModeUpdateCB();
/// <summary>
/// The registration API for a wmx_pRfTakenCB_t callback function.
/// </summary>
///
/// <param name="rfTakenCB">(IN) A pointer to the application function to be called upon RF taken indication.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRfTakenCB( wmx_pRfTakenCB_t rfTakenCB);

/// <summary>
/// The de-registration API for a wmx_pRfTakenCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRfTakenCB();
/// <summary>
/// The registration API for a wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t callback function.
/// </summary>
///
/// <param name="fastReconnectStatusCB">(IN) A pointer to the application function to be called upon connectedAsCurrentPreferredCapabilityStatus mode changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectedAsCurrentPreferredCapabilityStatusCB( wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t connectedAsCurrentPreferredCapabilityStatusCB );


/// <summary>
/// The de-registration API for a wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectedAsCurrentPreferredCapabilityStatusCB();

/// <summary>
/// The registration API for a wmx_pRfTakenCB_t callback function.
/// </summary>
///
/// <param name="rfTakenCB">(IN) A pointer to the application function to be called upon RF taken indication.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRfTakenCB( wmx_pRfTakenCB_t rfTakenCB);

/// <summary>
/// The de-registration API for a wmx_pRfTakenCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRfTakenCB();



/// <summary>
/// This API commands the device to connect to the NSP specified in the nspID argument, 
/// when the connection mode is set to UserManualConnection.
///
/// This API will be ignored when the connection mode is set to UserAutoConnection.
/// This is a blocking API. It returns after the connect operation had been completed
/// (either successfully or not).
/// </summary>
///
/// <param name="nspID">(IN) The ID of the NSP to connect to.</param>
/// <param name="connectStatus">(OUT) A pointer to a user-allocated wmx_pUserConnectStatus_t enum to which the API will place the status of the connection attempt.</param>
/// <param name="connectionType">(IN) Home / Roam / Activate. Indicates the type of connection requested. Can be either a direct connection to an existing Home NSP, a roaming connection to an existing Home NSP through a roaming partner or an activation attempt against a new NSP.
/// <param name="homeNSPToRoamTo">(IN) The ID of the Home NSP to roam to through the roaming partner. This argument is relevant only when the connection type is Roam.
/// <param name="userCredentials">(IN) A pointer to an optional user-allocated wmx_pUserCredentials_t structure containing the username & password of the subscriber. When not needed, this argument can be set to NULL.
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserConnect( wmx_NSPid_t nspID, wmx_ConnectionType_t connectionType, wmx_NSPid_t homeNSPToRoamTo, wmx_pUserCredentials_t userCredentials, wmx_pUserConnectStatus_t connectStatus );


/// <summary>
/// This API commands the device to disconnect from the network (i.e. From the currently connected NSP). 
///
/// This API will be ignored when the connection mode is set to UserAutoConnection.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserDisconnect();


/// <summary>
/// This API provides the NSP to which the device is currently connected.
///
/// If we are not currently connected the return value will be WMX_ST_DATA_UNAVAILABLE.
/// </summary>
///
/// <param name="connectedNSP">(OUT) A pointer to a user-allocated wmx_NSP_t struct in which the API will place information about the currently connected NSP.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectedNSP( wmx_pNSP_t connectedNSP );


/// <summary>
/// This API provides information about the last known NSPs (those detected during the last scan operation).
///
/// The list is given as a vector of NSP information structs.
///
/// The user must allocate space for the vector in advance and state its size using the pNumOfNsps argument 
/// (in terms of the number of wmx_NSP_t structs the vector may contain).
///
/// The API can fill a vector of up to WMX_NSPS_MAX_NUM of wmx_NSP_t structs
/// (i.e. at maximum the user should allocate (WMX_NSPS_MAX_NUM * sizeof(wmx_NSP_t)) bytes).
/// The value entered by the user in pNumOfNsps will reflect the number of wmx_NSP_t structs 
/// which can be contained in the space allocated (by the user) for the pNsps vector. 
/// The API will return in pNumOfNsps the actual number of structs in the vector that were
/// filled with data (0 if no NSPs are found).
/// </summary>
///
/// <param name="pNumOfNsps">(INOUT) A pointer to a user-allocated UINT32 containing the expected number of NSPs as input and the actual number of NSPs in the pNsps vector as output.</param>
/// <param name="pNsps">(OUT) A pointer to a user-allocated buffer which will be filled with a vector of wmx_NSP_t structs containing information about the last known NSPs.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetLastKnownNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps );

/// <summary>
/// This API provides the data for all NSPs that were provisioned to the WiMAX SDK (using the APDO APIs).
///
/// The NSP data includes information about the NSP itself, as well as information about all subscribers 
/// to the NSP on this machine.
///
/// The list is given as a vector of NSP information structs.
///
/// The user must allocate space for the vector in advance and state its size using the pNumOfNsps 
/// argument (in terms of the number of wmx_NSP_t structs the vector may contain).
///
/// The API can fill a vector of up to WMX_NSPS_MAX_NUM of wmx_NSP_t structs (i.e. at maximum the user 
/// should allocate (WMX_NSPS_MAX_NUM * sizeof(wmx_NSP_t)) bytes).
///
/// The value entered by the user in pNumOfNsps will reflect the number of wmx_NSP_t structs 
/// which can be contained in the space allocated (by the user) for the pNsps vector. 
/// The API will return in pNumOfNsps the actual number of structs in the vector that were filled
/// with data (0 if no NSPs are found).
/// </summary>
///
/// <param name="pNumOfNsps">(INOUT) A pointer to a user-allocated UINT32 containing the expected number of NSPs as input and the actual number of NSPs in the pNsps vector as output.</param>
/// <param name="pNsps">(OUT) A pointer to a user-allocated buffer which will be filled with a vector of wmx_NSP_t structs containing information about the provisioned NSPs.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetProvisionedNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps );

/// <summary>
/// Return the unprovisioned NSPs that where added when the unprovisioned NSPs became the current preferred NSPSs
/// </summary>
/// <param name="pNumOfNsps">(INOUT) A pointer to a user-allocated UINT32 containing the expected number of NSPs as input and the actual number of NSPs in the pNsps vector as output.</param>
/// <param name="pNsps">(OUT) A pointer to a user-allocated buffer which will be filled with a vector of wmx_NSP_t structs containing information about the provisioned NSPs.</param>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUnprovisionedNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps );

/// <summary>
/// This API provides a way to de-provision the data of a specific NSP.
///
/// This data is provisioned using APDO APIs and may also be de-provisioned using these, 
/// but the wmx_DeprovisionNSP allows a user to erase the data provisioned to his computer
/// on his own accord.
/// </summary>
///
/// <param name="nspID">nspId � (IN) The NSP_ID of the NSP to be deprovisioned.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_DeprovisionNSP( wmx_NSPid_t nspID );

/// <summary>
/// This API updates the new username and password.
/// </summary>
///
/// <param name="nspID">nspId � (IN) The NSP_ID of the NSP to be deprovisioned.</param>
/// <param name="username">(IN) An enum indicating the desired connection mode</param>
/// <param name="password">(IN) password(16-bit wchar_t unicode string with null terminator)</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetMSChap_v2Crd( wmx_NSPid_t nspIds, 
																    char* username, 
																	char* password );

/// <summary>
/// This API retrieves the currently set user connection mode (Manual / Automatic).
/// </summary>
///
/// <param name="connectMode">(OUT) A pointer to a user-allocated wmx_pUserConnectMode_t enum in which the API will place the currently set connection mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserConnectMode( wmx_pUserConnectMode_t connectMode );


/// <summary>
/// This API sets the user connection mode (Manual / Automatic).
/// </summary>
///
/// <param name="connectMode">(IN) The connection mode to be set.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserConnectMode( wmx_UserConnectMode_t connectMode );


/// <summary>
/// This API retrieves the currently set user roaming mode (Enable / Disable).
/// </summary>
///
/// <param name="roamingMode">(OUT) A pointer to a user-allocated wmx_pUserRoamingMode_t enum in which the API will place the currently set roaming mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserRoamingMode( wmx_pUserRoamingMode_t roamingMode );


/// <summary>
/// This API sets the user roaming mode (Enable / Disable).
/// </summary>
///
/// <param name="roamingMode">(IN) The roaming mode to be set.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserRoamingMode( wmx_UserRoamingMode_t roamingMode );


/// <summary>
/// This API returns information that describes the status of the link (i.e. the link between the device and the network it is connected to).
///
/// If we are not currently connected the return value will be WMX_ST_DATA_UNAVAILABLE.
/// </summary>
///
/// <param name="userLinkStatus">(OUT) A pointer to a user-allocated wmx_pUserLinkStatus_t struct in which the API will place information about the link's status.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserLinkStatus( wmx_pUserLinkStatus_t userLinkStatus	);


/// <summary>
/// This API returns various statistics information regarding traffic.
///
/// Some of the statistics are provided per each established service flow.
/// These SF specific statistics are given as a vector of SF statistics information structs.
///
/// </summary>
///
/// <param name="pStatistics">(OUT) A pointer to a user-allocated wmx_pStatistics_t struct to which the API will copy the gathered statistics information.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserStatistics( wmx_pUserStatistics_t userStatistics	);


/// <summary>
/// The NSP info includes information about the NSP itself, as well as information about all subscribers to 
/// the NSP on this machine.
/// </summary>/
/// <param name="nspID">(IN) Id of the NSP.</param>
/// <param name="pNsp">(OUT) A pointer to a user-allocated wmx_pNSP_t struct in which the API will place information about the NSP.</param>
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetNspInfo (wmx_NSPid_t nspID, wmx_pNSP_t pNsp);

// <summary>
// This API allows the user to get the association status.
// </summary>
//
// <param name="pAssociated">(OUT) An enum indicating the current association mode.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_IsAssociated(wmx_pAssociate_t pAssociated);
/// <summary>
/// This API provides a way to restore a backup provisioning database stored by the SDK.
/// This API will return an error when the SDK does not have a backup provisioning database stored.
/// </summary>
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RestoreBackupProvisioningDatabase();

/// <summary>
/// This API provides a way to restore the SDK to its factory provided default settings.
/// </summary>
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ResetToFactorySettings(); 

/// <summary>
/// The statuses provided by this API can generally be mapped to movements along the SDK common state machine.
/// </summary>
/// <param name="deviceStatus">(OUT) A pointer to a user-allocated wmx_pDeviceStatus_t enum in which the API will place the device status.</param>
/// <param name="connectionProgressInfo">(OUT) A pointer to a user-allocated wmx_ConnectionProgressInfo_t enum giving further information on the progress of a connection attempt.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceStatus(wmx_pDeviceStatus_t deviceStatus, wmx_pConnectionProgressInfo_t connectionProgressInfo) ;


/// <summary>
/// The information gathered here is used for Platform Noise Mitigation
/// </summary>
/// <param name="buffer">(OUT) A pointer to a user-allocated buffer for the data.</param>
/// <param name="bufferSize">(INOUT) A pointer to a user-allocated buffer for the data.</returns>
wmx_Status_t wmx_GetPNMRequestedChannel(CHAR *buffer, UINT32 *bufferSize);

/// <summary>
/// The information gathered here is the device currently uses the given channel
/// </summary>
/// <param name="buffer">(IN) A pointer to the channel data .</param>`
/// <param name="result">(OUT) A pointer to a user-allocated buffer for the data.</returns>
wmx_Status_t wmx_GetIsPNMCommDevUsingChannel(CHAR *buffer, UINT32 *bufferSize, BOOL *result);



// <summary>
// This API allows the user to set the package update state 
// </summary>
//
// <param name="packageUpdateState">(IN) An enum indicating the user download approval state.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetPackageUpdateState( wmx_PackageUpdateState_t packageUpdateState );

// <summary>
// This API allows the user to get information about the package which is needed for executing package update.
// </summary>
//
// <param name="packageInfo">(OUT) pointer to package information struct.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetPackageInfo( wmx_pPackageInfo_t packageInfo );

/// <summary>
/// This API should be used to unlock the device from a particular service provider.
/// </summary>
///
/// <param name="lockCode">(IN) The unlock code(16-bit wchar_t unicode string with null terminator). 
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetServiceProviderUnLock(char* lockCode);

/// <summary>
/// This API should be used to get the current lock status.
/// </summary>
///
/// <param name="pLockStatus">(OUT) Pointer to the service provider lock status.</param>
/// <param name="NSPName">(OUT) The NSP name for which the card is locked to.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetServiceProviderLockStatus(wmx_pSPLockStatus_t pLockStatus, 
																				char* pNSPName);
/// <summary>
/// This API allows to enable/disable fast reconnecting
/// </summary>
///
/// <param name="isEnabled">(IN) The fast reconnect status.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserFastReconnectStatus( BOOL isEnabled );

/// <summary>
/// This API should be used to check if fast reconnect is allowed.
/// </summary>
///
/// <param name="pIsEnabled">(OUT) Pointer to the fast reconnect status.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserFastReconnectStatus( BOOL *pIsEnabled	);

/// <summary>
/// This API returns information about the package which was installed.
/// </summary>
//
// <param name="pInstallationInfo">(OUT) pointer to installation information struct.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetInstallationInfo(wmx_pInstallationInfo_t pInstallationInfo);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetCurrentPreferredNSP(wmx_pNSP_t pCurrentPreferredNsps, UINT32 *numOfCurrentPreferredNsps);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetCurrentPreferredNSP(UINT32 numOfCurrentPreferred, wmx_pNSPid_t currentPreferredNspIDs);

/// <summary>
/// This API allows to enable/disable CurrentPreferredCapabilityStatus
/// </summary>
///
/// <param name="isEnabled">(IN) The CurrentPreferredCapabilityStatus status.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetConnectedAsCurrentPreferredCapabilityStatus( BOOL isEnabled );

/// <summary>
/// This API should be used to check if CurrentPreferredCapabilityStatus is enable.
/// </summary>
///
/// <param name="pIsEnabled">(OUT) Pointer to the CurrentPreferredCapabilityStatus status.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectedAsCurrentPreferredCapabilityStatus( BOOL *pIsEnabled	);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetWMFComplianceVersion(char *WMFComplianceVersion, UINT32 WMFComplianceVersionLen);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetNonce(WIMAX_API_NONCE_BLOB_P pNonce,UINT32 *pNonceSize);
#endif // _WMX_SDK_NDS_3_H
