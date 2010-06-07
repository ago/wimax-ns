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
#ifndef _WMX_WIMAX_API_EXTENSIONS_H
#define _WMX_WIMAX_API_EXTENSIONS_H

#ifndef NATIVE_WINDOWS

#else
	#include <Windows.h> 
#endif

#include "WiMaxError.h"
#include "WiMaxTypesEx.h"

#if defined(_WIN32) || defined(_WIN64)
#ifdef WIMAX_EXPORTS
#define WIMAX_API __declspec(dllexport)
#else
#define WIMAX_API __declspec(dllimport)
#endif
#else
#define WIMAX_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/// Media Status enum
typedef enum _WIMAX_API_MEDIA_STATUS
{
	WIMAX_API_MEDIA_STATUS_LINK_UP = 0x01,			//Indicating that a connection has been made
	WIMAX_API_MEDIA_STATUS_LINK_DOWN,				//Indicating that a connection has been lost
	WIMAX_API_MEDIA_STATUS_LINK_RENEW				//Indicating that a connection has been renewed
} WIMAX_API_MEDIA_STATUS;

/// Open the WiMax common API. when the privilege mode can be taken from you in case of read write permissions.
/// \param[in,out] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
/// \note Must be called before calling any other common API functions
/// \note Only privilege must be specified. The application requests a privilege and the API returns WIMAX_API_RET_PERMISSION_DENIED if the requested privilege cannot be granted.
/// \note Each device vendor must install on the OS registry its own API SDK/Binary directly into a common registry key are:
/// \note Windows:
/// \note HKEY_LOCAL_MACHINE\\Software\\WiMax\\CommonAPI\\Libs\\Manufacturer\\DeviceFamily
/// \note Path=Path
/// \note Extension=xyz
/// \note Manufacturer and DeviceFamily values are controlled by each Device manufacturer. Users of the SDK will enumerate ALL entries from the Libs\ entry down and load each SDK to check for supported devices of that manufacturer. 
/// \note Linux and MAC OS TBD
/// \note Multiple applications can open the API simultaneously. However only one application has read/write privilege.
WIMAX_API_RET WIMAX_API WiMaxAPIOpenHijackable( WIMAX_API_DEVICE_ID_P pDeviceId );

/// <summary>
/// Once registered, this callback function will be called whenever a network search cycle has completed.
///	This API is similar to the IndNetworkSearchWideScan Common API, but is triggered when a 
///	regular search cycle is completed.
/// </summary>
///
/// <param name="pNspList">(OUT) Pointer to a structure with information on Networks found during search.</param>
/// <param name="listSize">(OUT) Size of the networks list.</param>
/// <param name="searchProgress">(OUT) A UINT32 indicating the progress status of the search as a percentage.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndNetworkSearch) (	WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_P pNspList, UINT32 listSize, UINT32 searchProgress);

/// <summary>
/// Once registered, this callback function will be called whenever a network search cycle has completed.
///	This API is similar to the IndNetworkSearchWideScan Common API, but is triggered when a 
///	regular search cycle is completed.
/// The difference from the IndNetworkSearch indication is the use of the new field linkQuality.
/// </summary>
///
/// <param name="pNspList">(OUT) Pointer to a structure with information on Networks found during search.</param>
/// <param name="listSize">(OUT) Size of the networks list.</param>
/// <param name="searchProgress">(OUT) A UINT32 indicating the progress status of the search as a percentage.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndNetworkSearchEx) (	WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_EX_P pNspList, UINT32 listSize, UINT32 searchProgress); 

/// <summary>
/// Once registered, this callback function will be called whenever the current preferred profiles list is changed
/// </summary>
///
/// <param name="numOfCurrentPreferredProfiles">(OUT) list of current preferred profiles.</param>
/// <param name="currentPreferredProfiles">(OUT) Size of the current preferred profiles list.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndCurrentPreferredProfile)(WIMAX_API_DEVICE_ID_P pDeviceId, UINT32 numOfCurrentPreferredProfiles, WIMAX_API_PROFILE_INFO_P currentPreferredProfiles);

/// ! NOTE - This API currently should NOT be used !
/// <summary>
/// The API allows the user to set the user name and password.
/// </summary>
/// <param name="pDeviceId">(IN) pDeviceId - The privilege for the whole API in device Id must be specified. </param>
/// <param name="profileId">(IN) NSP Identifier WIMAX_API_PROFILE_ID type</param>
/// <param name="username">(IN) An enum indicating the desired connection mode</param>
/// <param name="password">(IN) password(16-bit wchar_t unicode string with null terminator)</param>
/// <returns>WIMAX_API_RET_SUCCESS - if successful.\n</returns>
///          WIMAX_API_RET_FAIL - if failure to change one or more of the fields.\n
///          WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///          any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///          See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SetMSChap_v2Crd(  WIMAX_API_DEVICE_ID_P pDeviceId,
										  WIMAX_API_PROFILE_ID profileId,
										  WIMAX_API_WSTRING username,
									      WIMAX_API_WSTRING password);

/// The API allows the user to set the connection mode of the device.
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[in] connectionMode - An enum indicating the desired connection mode
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SetConnectionMode(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_CONNECTION_MODE connectionMode);

/// The API allows the user to get the connection mode of the device.
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[out] pConnectionMode - A pointer to a user allocated enum in which the device will indicate the currently set connection mode.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetConnectionMode(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_CONNECTION_MODE_P pConnectionMode);

/// <summary>
/// Once registered, this callback function will be called whenever the connection mode changed
/// </summary>
///
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[in] connectionMode - enum which indicate the currently set connection mode.
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndConnectionModeUpdate)(WIMAX_API_DEVICE_ID_P pDeviceId, 
										   WIMAX_API_CONNECTION_MODE connectionMode);

/// Indicator for Media Status update.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] mediaStatusUpdate - Media Status update.
typedef void (*IndMediaStatusUpdate) (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_MEDIA_STATUS mediaStatus);

/// <summary>
/// The registration API for a IndMediaStatusUpdate callback function.
/// </summary>
///
/// <param name="pCallbackFnc">(IN) A pointer to the application function to be called upon Media Status update.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeMediaStatusUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndMediaStatusUpdate pCallbackFnc );

/// <summary>
/// The de-registration API for a IndMediaStatusUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeMediaStatusUpdate(WIMAX_API_DEVICE_ID_P pDeviceId);

/// <summary>
/// The registration API for a IndConnectionModeUpdate callback function.
/// </summary>
///
/// <param name="pCallbackFnc">(IN) A pointer to the application function to be called upon network search cycle completion.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeConnectionModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndConnectionModeUpdate pCallbackFnc );

/// <summary>
/// The de-registration API for a IndConnectionModeUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeConnectionModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId);



///	This API allows the user to remove a provisioned profile from the device.
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[in] profileID - The profileID of the profile to be de-provisioned.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API CmdDeprovisionProfile(	WIMAX_API_DEVICE_ID_P pDeviceId,
												WIMAX_API_PROFILE_ID profileID);

///	This API returns the time that has passed since the current connection was established.
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified.
/// \param[out] pConnectionTime - A pointer to a WIMAX_API_CONNECTION_TIME variable in which the API will place the time that has passed since the current connection was established.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetConnectionTime(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_CONNECTION_TIME_P pConnectionMode);


///	This API provides a way to restore a backup provisioning database stored by the SDK.
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API CmdRestoreBackupProvisioningDatabase(WIMAX_API_DEVICE_ID_P pDeviceId);

// <summary>
// This API allows the triggering of a scan spanning recent & provisioned networks.
// </summary>
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API CmdNetworkSearch(WIMAX_API_DEVICE_ID_P pDeviceId);

// <summary>
// This API allows the stopping of a user triggered scan.
// </summary>
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API CmdStopScan(WIMAX_API_DEVICE_ID_P pDeviceId);

// <summary>
// This API allows gets the ODM information.
// </summary>
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API GetODMInformation(	WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_BINARY_BLOB_P pBinaryBlob,
											UINT32 *pBinaryBlobSize);


// <summary>
// This API allows gets the ODM information.
// </summary>
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API GetNVMImageVersion(	WIMAX_API_DEVICE_ID_P pDeviceId,
											WIMAX_API_NVM_VERSION_P pNVMImageVersion);

/// <summary>
/// The registration API for a IndNetworkSearch callback function.
/// </summary>
///
/// <param name="coexModeCB">(IN) A pointer to the application function to be called upon network search cycle completion.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeNetworkSearchEx(WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearchEx pCallbackFnc );

/// <summary>
/// The de-registration API for a IndNetworkSearch callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearchEx(WIMAX_API_DEVICE_ID_P pDeviceId);

/// <summary>
/// The registration API for a IndNetworkSearch callback function.
/// </summary>
/// <param name="coexModeCB">(IN) A pointer to the application function to be called upon network search cycle completion.</param>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeNetworkSearch(WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearch pCallbackFnc );

/// <summary>
/// The de-registration API for a IndNetworkSearch callback function.
/// </summary>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearch(WIMAX_API_DEVICE_ID_P pDeviceId);

/// <summary>
/// This API allows to enable/disable the fast reconnect capability
/// </summary>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SetFastReconnectCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL isEnabled);

/// <summary>
/// This API returns the status (enabled/disabled) of the fast reconnect capability
/// </summary>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API GetFastReconnectCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL *pIsEnabled);

/// <summary>
/// Once registered, this callback function will be called whenever the fast reconnect is being change
/// </summary>
///
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[in] fastReconnectCapabilityStatus - int which indicate the currently set fast reconnect mode.
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndFastReconnectCapabilityStatusUpdate)(WIMAX_API_DEVICE_ID_P pDeviceId, 
										   BOOL fastReconnectCapabilityStatus);

/// <summary>
/// The registration API for a IndFastReconnectCapabilityStatusUpdate callback function.
/// </summary>
///
/// <param name="pCallbackFnc">(IN) A pointer to the application function to be called fast reconnect mode change.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeFastReconnectCapabilityStatusUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndFastReconnectCapabilityStatusUpdate pCallbackFnc );

/// <summary>
/// The de-registration API for a IndFastReconnectCapabilityStatusUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeFastReconnectCapabilityStatusUpdate(WIMAX_API_DEVICE_ID_P pDeviceId);




/// <summary>
/// This API allows to enable/disable the ConnectedAsCurrentPreferredCapabilityStatus
/// </summary>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SetConnectedAsCurrentPreferredCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL isEnabled);

/// <summary>
/// This API returns the status (enabled/disabled) of the ConnectedAsCurrentPreferredCapabilityStatus
/// </summary>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API GetConnectedAsCurrentPreferredCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, BOOL *pIsEnabled);

/// <summary>
/// Once registered, this callback function will be called whenever the connectedAsCurrentPreferredCapabilityStatus is being change
/// </summary>
///
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[in] connectedAsCurrentPreferredCapabilityStatus - int which indicate the currently set connectedAsCurrentPreferredCapabilityStatus mode.
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndConnectedAsCurrentPreferredCapabilityStatusUpdate)(WIMAX_API_DEVICE_ID_P pDeviceId, 
										   BOOL connectedAsCurrentPreferredCapabilityStatus);

/// <summary>
/// The registration API for a IndConnectedAsCurrentPreferredCapabilityStatusUpdate callback function.
/// </summary>
///
/// <param name="pCallbackFnc">(IN) A pointer to the application function to be called fast reconnect mode change.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeConnectedAsCurrentPreferredCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId, IndConnectedAsCurrentPreferredCapabilityStatusUpdate pCallbackFnc );


/// <summary>
/// The de-registration API for a IndConnectedAsCurrentPreferredCapabilityStatusUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeConnectedAsCurrentPreferredCapabilityStatus(WIMAX_API_DEVICE_ID_P pDeviceId);


/// <summary>
/// Once registered, this callback function will be called whenever the PermissionsUpdate is being change
/// </summary>
///
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \paran [in] - updateEvent - Enum stating the reason for the raised indication
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndPermissionsUpdate)(WIMAX_API_DEVICE_ID_P pDeviceId, WMX_PERMISSION_UPDATE_EVENT updateEvent);

/// <summary>
/// The registration API for a IndPermissionsUpdate callback function.
/// </summary>
///
/// <param name="pCallbackFnc">(IN) A pointer to the application function .</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribePermissionsUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndPermissionsUpdate pCallbackFnc );


/// <summary>
/// The de-registration API for a IndPermissionsUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribePermissionsUpdate(WIMAX_API_DEVICE_ID_P pDeviceId);

/// <summary>
/// Once registered, this callback function will be called whenever the roaming mode is being change
/// </summary>
///
/// \param[in] pDeviceId - The privilege for the whole API in device Id must be specified. 
/// \param[in] roamingMode - enum which indicate the currently set roaming mode.
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndRoamingModeUpdate)(WIMAX_API_DEVICE_ID_P pDeviceId, 
									 WIMAX_API_ROAMING_MODE roamingMode);

/// <summary>
/// The registration API for a IndRoamingModeUpdate callback function.
/// </summary>
///
/// <param name="pCallbackFnc">(IN) A pointer to the application function to be called roaming mode change.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeRoamingModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndRoamingModeUpdate pCallbackFnc );

/// <summary>
/// The de-registration API for a IndRoamingModeUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeRoamingModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId);


/// <summary>
/// This API sets the current preferred NSP. Select the favorite operator for scanning and connecting purposes.
/// After setting the current preferred operator the preferred scan will scan only its channels and return only
/// this operator as a scan result
/// The API currently supports a list of size 1 maximum
/// </summary>
/// <param name="pCurrentPreferredProfileIDs">(IN) A pointer to the list of profiles to be the current preferred.</param>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SetCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P	pDeviceId,  
													UINT32					*pCurrentPreferredProfileIDs, 
													UINT32					listSize);

/// <summary>
/// Gets the current preferred Profiles.
/// The API currently supports a list of size 1 maximum
/// </summary>
/// <param name="pCurrentPreferredProfiles">(OUT) A pointer to the list of profiles allocated by the API's user and filled by the SDK.</param>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API GetCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P		pDeviceId,  
													WIMAX_API_PROFILE_INFO_P	pCurrentPreferredProfiles, 
													UINT32						*listSize);

/// Get the current link status from the device. Active connection status.
/// The difference from the GetLinkStatus function is the use of the new field linkQuality.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pLinkStatus - Pointer to structure WIMAX_API_LINK_STATUS_INFO_EX, should return with updated link status values.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_LINK_NOT_CONNECTED - link is not connected, cannot obtain result.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetLinkStatusEx (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_LINK_STATUS_INFO_EX_P pLinkStatus);

/// This API provides information about the NSP to which the device is currently connected.
/// The difference from the GetConnectedNSP function is the use of the new field linkQuality.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pConnectedNSP - Pointer to a user-allocated struct, in which the API will place information about the currently connected NSP.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_LINK_NOT_CONNECTED - link is not connected, cannot obtain result.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note If we are not currently connected the return value will be WIMAX_API_RET_LINK_NOT_CONNECTED and the returned values should be ignored.
/// \note Contains information about the connected NSP. CM will query this list only while connected.
WIMAX_API_RET WIMAX_API GetConnectedNSPEx (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CONNECTED_NSP_INFO_EX_P pConnectedNSP);

/// Obtain the list of  NSPs currently available to the user for selection.
/// The difference from the GetNetworkList function is the use of the new field linkQuality.
/// \param[in] pDeviceId - Specifies the device
/// \param[out] pNSPInfo - Array of found NSP data records, each contains RSSI, CINR and Network Type
/// \param[in, out] pArrayLength - Pointer to pass the array size in input and receive the number of NSPInfo in output. If size is too small, an error shall be returned and the size required shall be specified.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL - if the given size is too small.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Obtain the list of  NSPs currently available to the user for selection. 
/// \note This list will be a prioritized list of networks from high to low priority.
WIMAX_API_RET WIMAX_API GetNetworkListEx (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_EX_P pNSPInfo, UINT32* pArrayLength);

/// Provide results of Wide Scan search.
/// The difference from the IndNetworkSearchWideScan indication is the use of the new field linkQuality.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pNspList - Pointer to a structure with information on Networks found during search.
/// \param[in] listSize - Size of the Network list
typedef void (*IndNetworkSearchWideScanEx) (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_EX_P pNspList, UINT32 listSize);

/// Subscribe to  network search wide scan extention event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndNetworkSearchWideScan.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribeNetworkSearchWideScanEx (WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearchWideScanEx pCallbackFnc);

/// Unsubscribe to network search wide scan extension event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearchWideScanEx (WIMAX_API_DEVICE_ID_P pDeviceId);

/// Get the extension API version
/// \param[out] pWmxApiExVersion - Pointer to returned extension version value
/// \return WIMAX_API_RET_SUCCESS\n
WIMAX_API_RET WIMAX_API GetWmxApiExVersion(UINT32 *pWmxApiExVersion);

/// <summary>
/// The registration API for a IndCurrentPreferredProfile callback function.
/// </summary>
/// <param name="pCurrentPreferredProfileCB">(IN) A pointer to the application function to be called upon current preferred profile change.</param>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P pDeviceId, IndCurrentPreferredProfile pCurrentPreferredProfileCB);

/// <summary>
/// The de-registration API for a IndCurrentPreferredProfile callback function.
/// </summary>
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API UnsubscribeCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P pDeviceId);

/// <summary>
/// This API commands a scan on a list of specified channels.
///
/// The list is given as a vector of channel information structs.
///
/// The user must allocate space for the vector in advance and state the number of channels in the list using the listSize 
/// argument (in terms of the number of WIMAX_API_CHANNEL_INFO structs the vector may contain).
///
/// The API can fill a vector of up to WIMAX_API_CHANNEL_INFO_LIST_MAX_NUM_OF_ENTRIES of WIMAX_API_CHANNEL_INFO structs (i.e. at maximum the user 
/// should allocate (WIMAX_API_CHANNEL_INFO_LIST_MAX_NUM_OF_ENTRIES * sizeof(WIMAX_API_CHANNEL_INFO)) bytes).
///
/// The memory allocation for the channels vector must remain valid until the API returns. After that the user may free the memory.
///
/// If the isBlocking parameter is set to TRUE, the scan results will not be reported, nor will they be used or saved internally by the WiMAX SDK.
///
/// Important:
/// The user is expected to set the SDK to manual scan mode, using the SetConnectionMode() API, before triggering this command.
/// </summary>
///
/// <param name="pDeviceId">(IN) The privilege for the whole API in device Id must be specified. </param>
/// <param name="pChannels">(IN) A pointer to a user-allocated vector of WIMAX_API_CHANNEL_INFO_P structs specifying the list of channels to be scanned.</param>
/// <param name="listSize">(IN) A UINT32 specifying the number of channels in the pChannels vector.</param>
/// <param name="isBlocking">(IN) A Boolean specifying whether reporting of the scan results should be blocked.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API CmdNetworkSearchDirect(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CHANNEL_INFO_P pChannels, UINT32 listSize, BOOL isBlocking);

/// Signals that RF was given to WiFi.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
typedef void (*IndRfTaken) (WIMAX_API_DEVICE_ID_P pDeviceId);

/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
typedef void (*IndPNMNotification) (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Subscribe to RF-taken event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndRfTaken.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribeRfTaken (WIMAX_API_DEVICE_ID_P pDeviceId, IndRfTaken pCallbackFnc);

/// Unsubscribe to RF-taken event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeRfTaken (WIMAX_API_DEVICE_ID_P pDeviceId);

/// Get the WMF Compliance Version
/// <param name="pWMFComplianceVersion">(OUT)- Pointer to returned WMF compliancd version value. </param>
/// <returns>return WIMAX_API_RET_SUCCESS.<returns>
WIMAX_API_RET WIMAX_API GetWMFComplianceVersion(WIMAX_API_WMF_COMPLIANCE_VERSION_P pWMFComplianceVersion);



/// Use it for getting the Production Lock Nonce & Lock Status.
///
///
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetNonce(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NONCE_BLOB_P pNonce, UINT32 *pNonceSize);


/// Subscribe to package download progress event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndPackageDownloadProgress.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribePackageDownloadProgress (WIMAX_API_DEVICE_ID_P pDeviceId, IndPackageDownloadProgress pCallbackFnc);

/// Unsubscribe to package download progress event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribePackageDownloadProgress (WIMAX_API_DEVICE_ID_P pDeviceId);


/// The statuses provided by this API can generally be mapped to movements along the SDK common state machine. The API may provide further detailed information using the API�s arguments when relevant.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pPNMInfo - Pointer to the PNM parameters
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The Connection progress info is valid only when there is a connection is progress.
WIMAX_API_RET WIMAX_API GetPNMRequestedChannel(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PPNM_COMMDEV_INFO_P pPNMInfo);



/// The statuses provided by this API can generally be mapped to movements along the SDK common state machine. The API may provide further detailed information using the API�s arguments when relevant.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pPNMInfo - Pointer to the PNM parameters
/// \param[result] pPNMInfo - Pointer to the result answer if the channel is in use
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The Connection progress info is valid only when there is a connection is progress.
WIMAX_API_RET WIMAX_API GetIsPNMCommDevUsingChannel(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PPNM_COMMDEV_INFO_P pPNMInfo, BOOL* result);




/// Subscribe to Platform Noise Mitigation event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndPNMNotification.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribePNMNotification (WIMAX_API_DEVICE_ID_P pDeviceId, IndPNMNotification pCallbackFnc);

/// Unsubscribe to Platform Noise Mitigation event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribePNMNotification (WIMAX_API_DEVICE_ID_P pDeviceId);


#ifdef __cplusplus
}
#endif

#endif // _WMX_WIMAX_API_EXTENSIONS_H