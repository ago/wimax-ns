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
#ifndef _WMX_WIMAX_API_H
#define _WMX_WIMAX_API_H

#ifndef NATIVE_WINDOWS

#else
	#include <Windows.h> 
#endif

#include "WiMaxError.h"
#include "WiMaxType.h"

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

/// Device Detection Group
///

/// Open the WiMax common API.
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
WIMAX_API_RET WIMAX_API WiMaxAPIOpen( WIMAX_API_DEVICE_ID_P pDeviceId );


/// Get list of current available devices.
/// \param[in] pDeviceId - Pass the API privilege. 
/// \param[in,out] pHwDeviceIdList - Pointer to the HW device list to be filled by the API. 
/// \param[in,out] pHwDeviceIdListSize - Pointer to pass the list size in input and receive the number of devices in output. If size is too small, an error shall be returned and the size required shall be specified.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL - if the given size is too small.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note List the devices currently available in the specified SDK. 
/// \note The index must be persistent for a device until the SDK is closed.
/// \note The device index 0 is reserved. 0 equals no device.
WIMAX_API_RET WIMAX_API GetListDevice( WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_HW_DEVICE_ID_P pHwDeviceIdList, UINT32* pHwDeviceIdListSize );


/// Open a specific device.
/// \param[in] pDeviceId - The privilege and device index must be specified. 
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Specifies the device to be controlled using the common API.
WIMAX_API_RET WIMAX_API WiMaxDeviceOpen( WIMAX_API_DEVICE_ID_P pDeviceId );


/// Close a specific device.
/// \param[in] pDeviceId - The privilege and device index must be specified. 
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Specifies the device to stop controlling using the common API.
WIMAX_API_RET WIMAX_API WiMaxDeviceClose( WIMAX_API_DEVICE_ID_P pDeviceId );

/// Close the common API.
/// \param[in] pDeviceId - The privilege in device Id must be specified. 
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n
///         See WiMaxError.h for other error codes.\n
/// \note This is the last common API functions to be called
WIMAX_API_RET WIMAX_API WiMaxAPIClose( WIMAX_API_DEVICE_ID_P pDeviceId );


/// Device Maintenance Group
///

/// Control the power management from the host.
/// \param[in] pDeviceId - Specifies the open device
/// \param[in] powerState - Specifies the power management mode to set
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note This call focuses on power modes imposed to the device by the host. 
/// \note If the caller does not have WIMAX_API_PRIVILEGE_READ_WRITE a WIMAX_API_PERMISSION_DENIED error code is returned.
WIMAX_API_RET WIMAX_API CmdControlPowerManagement( WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_RF_STATE powerState);


/// Set Current Preferred Profiles
/// if list size equals to zero (pointer can be NULL) then the current preferred NSP is deleted, 
/// \param[in] pDeviceId - Specifies the open device
/// \param[in] pCurrentPreferredNspIDs 
/// \param[in] listSize
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note 
/// \note If the caller does not have WIMAX_API_PRIVILEGE_READ_WRITE a WIMAX_API_PERMISSION_DENIED error code is returned.
WIMAX_API_RET WIMAX_API SetCurrentPreferredProfiles(WIMAX_API_DEVICE_ID_P	pDeviceId,  
													UINT32					*pCurrentPreferredNspIDs, 
													UINT32					listSize);

/// Reset WiMax device command
/// \param[in] pDeviceId - Specifies the device 
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obtain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Reset the WiMax device. 
/// \note The device look at the �Auto Connect� setting in the OMA-DM tree to see if it needs to auto connect.
WIMAX_API_RET WIMAX_API CmdResetWimaxDevice (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Reset WiMax device to factory settings command.
/// \param[in] pDeviceId - Specifies the device 
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Reset the device persistent data to the factory defaults, and then reset the device. 
/// \note If the caller does not have write privilege a WIMAX_API_PERMISSION_DENIED error code is returned.
/// \note The device reboot should the device look at the �Auto Connect� setting in the OMA-DM tree to see if it needs to auto connect.
WIMAX_API_RET WIMAX_API CmdResetToFactorySettings (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Get the error string
/// \param[in] pDeviceId - Specifies the device to manage
/// \param[in] errorCode - Error code to translate in string
/// \param[out] buffer - Returns the error string in the allocated buffer as specified by the pLength
/// \param[in, out] pLength - Pointer to pass the buffer size in input and receive the error string size in output. If size is too small, an error shall be returned and the size required shall be specified.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL if buffer is too small.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note This function is called only for vendor specific error. This is used for logging purpose.
/// \note If the number of bytes required to store the data exceeds length, then the returned value of length indicates the necessary buffer length to store the data. 
WIMAX_API_RET WIMAX_API GetErrorString(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_RET errorCode, WIMAX_API_WSTRING buffer, UINT32* pLength);


/// Service Provider UnLock 
///

/// Unlock the device from a particular service provider.
/// \param[in] pDeviceId - Specifies the device.
/// \param[in] lockCode - unlock code(16-bit wchar_t unicode string with null terminator).
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_INVALID_PARAMETER if invalid unlock code.\n 
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Unlock the device to a particular service provider. 
WIMAX_API_RET WIMAX_API SetServiceProviderUnLock(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_WSTRING lockCode);


/// Get the current lock status.
/// \param[in] pDeviceId - Specifies the device.
/// \param[out] pLockStatus - Pointer to the service provider lock status.
/// \param[out] NSPName - Returns the NSP name for which the card is locked to.
/// \return WIMAX_API_RET_SUCCESS if successful.\n See WiMaxError.h for other error codes.
/// \note Get the current lock status.
/// \note If the card is locked, the NSP name shall be provided to identify to which service provider the card is locked to.
#ifndef NATIVE_WINDOWS
	WIMAX_API_RET WIMAX_API GetServiceProviderLockStatus(  WIMAX_API_DEVICE_ID_P  pDeviceId, WIMAX_API_LOCK_STATUS_P  pLockStatus, char  NSPName[MAX_SIZE_OF_NSP_NAME]);
#else
	WIMAX_API_RET WIMAX_API GetServiceProviderLockStatus(  WIMAX_API_DEVICE_ID_P  pDeviceId, WIMAX_API_LOCK_STATUS_P  pLockStatus, UCHAR16  NSPName[MAX_SIZE_OF_NSP_NAME]);
#endif

/// Network search and connection and disconnection group
///

/// Obtain the list of  NSPs currently available to the user for selection.
/// \param[in] pDeviceId - Specifies the device
/// \param[out] pNSPInfo - Array of found NSP data records, each contains RSSI, CINR and Network Type
/// \param[in, out] pArrayLength - Pointer to pass the array size in input and receive the number of NSPInfo in output. If size is too small, an error shall be returned and the size required shall be specified.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n
///         WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL - if the given size is too small.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Obtain the list of  NSPs currently available to the user for selection. 
/// \note This list will be a prioritized list of networks from high to low priority.
WIMAX_API_RET WIMAX_API GetNetworkList (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_NSP_INFO_P pNSPInfo, UINT32* pArrayLength);


/// Connect to network.
/// \param[in] pDeviceId - Specifies the device
/// \param[in] nspName - NSP name string
/// \param[in] profileId Profile number
/// \param[in] password - password(16-bit wchar_t unicode string with null terminator).
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The connect command contains the profile identifier and the password.
/// \note Profile id 0 is reserved to connection without specifying a user account. 
/// \note The card is always in automatic connection mode at host startup. Once the connection manager requests a disconnect, the card goes into manual connection mode.
/// \note Only after a device reboot should the device look at the �Auto Connect� setting in the OMA-DM tree to see if it needs to auto connects.
WIMAX_API_RET WIMAX_API CmdConnectToNetwork (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_WSTRING nspName, WIMAX_API_PROFILE_ID profileId, WIMAX_API_WSTRING password);

/// Disconnect from network.
/// \param[in] pDeviceId - Specifies the device
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Once the connection manager requests a disconnect, the card goes into manual connection mode.
/// \note Only after a device reboot should the device look at the �Auto Connect� setting in the OMA-DM tree to see if it needs to auto connects.
WIMAX_API_RET WIMAX_API CmdDisconnectFromNetwork (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Wide Scan disruptive search for networks.  
/// \param[in] pDeviceId - Specifies the device
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_ALREADY_CONNECTED - network has already been connected.\n
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note This optional command can be triggered to perform a wide scan and get a complete list of networks through a disruptive scan.   Intention is to have a means to do a wider ranging search in extreme cases though specific user request or diagnostic reasons.
WIMAX_API_RET WIMAX_API CmdNetworkSearchWideScan (WIMAX_API_DEVICE_ID_P pDeviceId);

/// Get IP interface index.  
/// \param[in] pDeviceId - Specifies the device
/// \param[out] pInterfaceInfo - returns the interface information
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetIPInterfaceIndex(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_INTERFACE_INFO_P pInterfaceInfo);

/// Credentials and Activation Group
///

/// Get user Profile list.
/// \param[in] pDeviceId - Specifies the device
/// \param[in] pProfileList - Pointer to profile info structure
/// \param[in,out] pListSize - Pointer to pass the size of the profile list in input and receive the number of profiles in output. If size is too small, an error shall be returned and the size required shall be specified.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL - if the given size is too small.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetSelectProfileList (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PROFILE_INFO_P pProfileList, UINT32* pListSize);

/// Device Info Group
///

/// Get the current link status from the device. Active connection status.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pLinkStatus - Pointer to structure WIMAX_API_LINK_STATUS_INFO, should return with updated link status values.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_LINK_NOT_CONNECTED - link is not connected, cannot obtain result.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetLinkStatus (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_LINK_STATUS_INFO_P pLinkStatus);

/// Get device information such as HW, FW versions.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pDeviceInfo - Pointer to structure WIMAX_API_DEVICE_INFO, should return with device information.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Pointer to WIMAX_API_DEVICE_INFO structure. Updated values should be populated in the structure upon return.
WIMAX_API_RET WIMAX_API GetDeviceInformation (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_INFO_P pDeviceInfo);


/// Device Status and subscriptions Group
///

/// The statuses provided by this API can generally be mapped to movements along the SDK common state machine. The API may provide further detailed information using the API�s arguments when relevant.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pDeviceStatus - Pointer to the device Status value
/// \param[out] pConnectionProgressInfo - Pointer to the connection progress value
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The Connection progress info is valid only when there is a connection is progress.
WIMAX_API_RET WIMAX_API GetDeviceStatus (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_DEVICE_STATUS_P pDeviceStatus, WIMAX_API_CONNECTION_PROGRESS_INFO_P pConnectionProgressInfo);


/// This API provides information about the NSP to which the device is currently connected.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pConnectedNSP - Pointer to a user-allocated struct, in which the API will place information about the currently connected NSP.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_LINK_NOT_CONNECTED - link is not connected, cannot obtain result.\n
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note If we are not currently connected the return value will be WIMAX_API_RET_LINK_NOT_CONNECTED and the returned values should be ignored.
/// \note Contains information about the connected NSP. CM will query this list only while connected.
WIMAX_API_RET WIMAX_API GetConnectedNSP (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CONNECTED_NSP_INFO_P pConnectedNSP);


/// Connection Info
///

/// This API sets the user roaming mode (Enable / Disable).
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] roamingMode - An enum specifying the roaming mode to be set.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         WIMAX_API_RET_PERMISSION_DENIED - if not enough privilege to obtain result.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note This roaming indicator overrides the network setting as follows:\n
///        Network=Allowed + User=Allowed = Allowed\n
///        Network=Disallowed + User=Allowed = Disallowed\n
///        Network=Allowed + User=Disallowed = Disallowed\n
///        Network=disallowed + User=Disallowed = Disallowed\n
WIMAX_API_RET WIMAX_API SetRoamingMode (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_ROAMING_MODE roamingMode);


/// This API gets the user roaming mode (Enable / Disable).
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pRoamingMode -  Pointer to a WIMAX_API_ROAMING_MODE enum in which the API will place the currently set roaming mode.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetRoamingMode (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_ROAMING_MODE_P pRoamingMode);


/// Connection Stats Group
///

/// Get the connection statistics.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pStatistics - Pointer to Integer, where to put statistics.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetStatistics (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_CONNECTION_STAT_P pStatistics);


/// OMA group
///

/// Get provisoning status.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] nspName - NSP name string
/// \param[out] pProvisoningStatus - Pointer to a boolean provisioning status.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetProvisioningStatus(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_WSTRING nspName, BOOL* pProvisoningStatus);


/// Get contact information.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] nspName - NSP name string
/// \param[out] pContactInfo - Pointer to contact information list.
/// \param[in,out] pSizeOfContactList - Pointer to sizeof contact info list, return the size filled. If too small the required size is returned with error code WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note For contact information the following will be available in the OMA-DM tree on the device:
/// \note Text (for display to the user; e.g., �My Account�) 
/// \note URI (http://my.xohm.com)
/// \note Code (type of text/link to be displayed; thinking of 0: Technical Support, 1: Subscription Portal, all others, Operator defined) 
WIMAX_API_RET WIMAX_API GetContactInformation(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_WSTRING nspName, WIMAX_API_CONTACT_INFO_P pContactInfo, UINT32* pSizeOfContactList);


/// Get package information required to execute package update. After getting the file name, the connection manager must close the API and execute the update. The update can update the SDK, Driver and firmware. The Connection manager must also force the OS the reload the driver.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pPackageInfo - Pointer to package information.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API GetPackageInformation(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PACKAGE_INFO_P pPackageInfo);

/// Set package update state 
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] packageUpdateState - package update state to set
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note Set the package update state from user feedback.
WIMAX_API_RET WIMAX_API SetPackageUpdateState(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PACKAGE_UPDATE_STATE packageUpdateState);

/// Subscriptions to Events Group
/// Subscription is done once in the API for all devices.

/// Subscribe to Device Status Change.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndDeviceStatusUpdate.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The device status notification shall be generated each time the connection state changes. 
/// \note The goal is to allow CM to log connection steps if a connection problem occurs.
/// \note The Connection progress info in the indication is valid only when there is a connection is progress.
WIMAX_API_RET WIMAX_API SubscribeDeviceStatusChange (WIMAX_API_DEVICE_ID_P pDeviceId, IndDeviceStatusUpdate pCallbackFnc);


/// Subscribe to Device Insertion or Removal events.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndDeviceInsertRemove.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The indication can be received even if the device open API was not executed.
WIMAX_API_RET WIMAX_API SubscribeDeviceInsertRemove (WIMAX_API_DEVICE_ID_P pDeviceId, IndDeviceInsertRemove pCallbackFnc);


/// Subscribe to power management event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndControlPowerManagement.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribeControlPowerManagement (WIMAX_API_DEVICE_ID_P pDeviceId, IndControlPowerManagement pCallbackFnc);


/// Subscribe to connect to network event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndConnectToNetwork.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
/// \note The Connect to network indication is generated only when the connection attempt is terminated.
/// \note If the connection attempt failed, the connection failure reason can be retrieve from GetDeviceStatus or from the last device status device indication.
WIMAX_API_RET WIMAX_API SubscribeConnectToNetwork (WIMAX_API_DEVICE_ID_P pDeviceId, IndConnectToNetwork pCallbackFnc);


/// Subscribe to disconnect to network event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc -  Pointer to callback function IndDisconnectToNetwork.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribeDisconnectToNetwork (WIMAX_API_DEVICE_ID_P pDeviceId, IndDisconnectToNetwork pCallbackFnc);


/// Subscribe to  network search wide scan event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndNetworkSearchWideScan.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribeNetworkSearchWideScan (WIMAX_API_DEVICE_ID_P pDeviceId, IndNetworkSearchWideScan pCallbackFnc);


/// Subscribe to provisioning operation event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndProvisioningOperation.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribeProvisioningOperation (WIMAX_API_DEVICE_ID_P pDeviceId, IndProvisioningOperation pCallbackFnc);


/// Subscribe to package update indicator event.
/// \param[in] pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[in] pCallbackFnc - Pointer to callback function IndPackageUpdate.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API SubscribePackageUpdate (WIMAX_API_DEVICE_ID_P pDeviceId, IndPackageUpdate pCallbackFnc);


/// Unsubscribe to Device Status Change event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeDeviceStatusChange (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Unsubscribe to Device Insertion or Removal events.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeDeviceInsertRemove (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Unsubscribe to power management event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeControlPowerManagement (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Unsubscribe to connect to network event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeConnectToNetwork (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Unsubscribe to disconnect to network event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeDisconnectToNetwork (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Unsubscribe to network search wide scan event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeNetworkSearchWideScan (WIMAX_API_DEVICE_ID_P pDeviceId);

/// Unsubscribe to provisioning operation event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribeProvisioningOperation (WIMAX_API_DEVICE_ID_P pDeviceId);


/// Unsubscribe to package update indicator event.
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \return WIMAX_API_RET_SUCCESS - if successful.\n
///         WIMAX_API_RET_FAIL - if failure to obain result.\n
///         WIMAX_API_RET_INVALID_DEVICE - if invalid device detected.\n 
///         any WIMAX_API_RET_VENDOR_ERROR - for vendor error.\n 
///         See WiMaxError.h for other error codes.\n
WIMAX_API_RET WIMAX_API UnsubscribePackageUpdate (WIMAX_API_DEVICE_ID_P pDeviceId);


#ifdef __cplusplus
}
#endif

#endif //_WMX_WIMAX_API_H