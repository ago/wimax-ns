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
#ifndef _WMX_SDK_MSC_2_H
#define _WMX_SDK_MSC_2_H

#include "wimax_osal_services_cmn.h"
#include "CommonServices.h"
#include "WrappersCommon.h"



typedef enum _wmx_ModeOfOperation_t
{
	ModeOfOperationNormal,
	ModeOfOperationProduction
} wmx_ModeOfOperation_t, *wmx_pModeOfOperation_t;


#define WMX_SIZE_OF_MAC_ADDRESS 6
/// <summary>
/// Type definition for a 6-byte buffer containing the 6-byte MAC address of the device. 
/// </summary>
typedef UINT8 wmx_MacAddress_t[WMX_SIZE_OF_MAC_ADDRESS], *wmx_pMacAddress_t;

#define WMX_SIZE_OF_NONCE 8

/// <summary>
/// Type definition for a 8-byte buffer containing the NONCE of the device. 
/// </summary>
typedef UINT8 wmx_Nonce_t[WMX_SIZE_OF_NONCE], *wmx_pNonce_t;

/// <summary>
/// Type definition for a struct containing the NVM Version of the device. 
/// </summary>
typedef struct _wmx_NvmVersion_t
{
	UINT16 GeneralImageVersion;
	UINT16 ContentVersion;
} wmx_NvmVersion_t, *wmx_pNvmVersion_t;


/// <summary>
/// Type definition for a struct containing the ODM Information of the device. 
/// </summary>
#define ODM_INFO_SIZE 108
typedef UINT8 wmx_ODMInfo_t[ODM_INFO_SIZE], *wmx_pODMInfo_t;

/// <summary>
/// A constant specifying the maximal length of the modelType string.
/// </summary>
#define WMX_MODEL_TYPE_NAME_MAX_LENGTH 62

/// <summary>
/// Definition of a struct that holds the model type ID and string. 
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_ModelType_t
{
	UINT32	modelTypeID;
	char	modelTypeName[WMX_MODEL_TYPE_NAME_MAX_LENGTH];
} wmx_ModelType_t, *wmx_pModelType_t;
#pragma pack( pop )

/// <summary>
/// A constant specifying the maximal length of the manufacturer string.
/// </summary>
#define WMX_MANUFACTURER_NAME_MAX_LENGTH 62

/// <summary>
/// Definition of a struct that holds the manufacturer ID and string. 
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_Manufacturer_t
{
	UINT32	manufacturerID;
	char	manufacturerName[WMX_MANUFACTURER_NAME_MAX_LENGTH];
} wmx_Manufacturer_t, *wmx_pManufacturer_t;
#pragma pack( pop )

/// <summary>
/// Definition of a struct that holds the manufacturer ID and string. 
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_DevicePID_t
{
	UINT32	productID;	
} wmx_DevicePID_t, *wmx_pDevicePID_t;
#pragma pack( pop )

/// <summary>
/// A constant specifying the maximal length of the serial number string.
/// </summary>
#define WMX_SERIAL_NUMBER_MAX_LENGTH 62

/// <summary>
/// Definition of a struct that holds the serial number string. 
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_SerialNumber_t
{	
	char	serialNumber[WMX_SERIAL_NUMBER_MAX_LENGTH];
} wmx_SerialNumber_t, *wmx_pSerialNumber_t;
#pragma pack( pop )



/// <summary>
/// Type definition for a struct containing statistics information regarding traffic.
/// </summary>
//#pragma pack( push, 1 )
//typedef struct _wmx_Statistics_t
//{
//	UINT32  timeStamp;
//	UINT32	TotalRxBytes;
//	UINT32	TotalRxPackets;
//	UINT32	TotalTxBytes;
//	UINT32	TotalTxPackets;
//} wmx_Statistics_t, *wmx_pStatistics_t;
//#pragma pack( pop )


/// <summary>
/// Type definition for a struct containing statistics for a specific service flow.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_SfStatistics_t
{
	UINT32	sfId;
	UINT32	CID;
	UINT32	noReceivedBytes;
	UINT32	noTransmittedBytes;
} wmx_SfStatistics_t, *wmx_pSfStatistics_t;
#pragma pack( pop )

/// <summary>
/// A constant specifying the maximal length of the strings in the wmx_DeviceVersion_t struct.
/// </summary>
#define WMX_DEVICE_VERSION_MAX_LENGTH OSAL_DEVICE_VERSION_MAX_LENGTH

/// <summary>
/// Type definition for a struct containing the versions of various components of the device.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_DeviceVersion_t
{
	char	Asic[WMX_DEVICE_VERSION_MAX_LENGTH];
	char	AsicName[WMX_DEVICE_VERSION_MAX_LENGTH];
	char	Board[WMX_DEVICE_VERSION_MAX_LENGTH];
	char	BoardName[WMX_DEVICE_VERSION_MAX_LENGTH];
	char	Software[WMX_DEVICE_VERSION_MAX_LENGTH];
} wmx_DeviceVersion_t, *wmx_pDeviceVersion_t;
#pragma pack( pop )



/// <summary>
/// A constant specifying the maximal length of a service flows statistics structs vector (in terms of the number of wmx_pSfStatistics_t structs the vector can contain).
/// </summary>
#define WMX_SF_STATS_MAX_NUM 100





/// <summary>
/// This API is used to obtain some details of the device, including its 6 byte MAC address.
/// </summary>
///
/// <param name="macAddress">(OUT) A pointer to a user-allocated 6-byte buffer in which the API will place the MAC address.</param>
/// <param name="modelType">(OUT) A pointer to a user allocated wmx_ModelType_t struct that holds the device model type (both integer and string representation).</param>
/// <param name="manufacturerId">(OUT) A pointer to a user allocated wmx_ManufacturerId_t struct that holds the device manufacturer Id (both integer and string representation).</param>
/// <param name="serialNumber">(OUT) A pointer to a user allocated wmx_SerialNumber_t struct that holds the device�s serial number string.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceDetails(wmx_MacAddress_t macAddress,
																	wmx_pModelType_t modelType,
																	wmx_pManufacturer_t manufacturer,
																	wmx_pSerialNumber_t serialNumber);

/// <summary>
/// This API is used to obtain some details of the device, including its 6 byte MAC address.
/// </summary>
///
/// <param name="macAddress">(OUT) A pointer to a user-allocated 6-byte buffer in which the API will place the MAC address.</param>
/// <param name="modelType">(OUT) A pointer to a user allocated wmx_ModelType_t struct that holds the device model type (both integer and string representation).</param>
/// <param name="manufacturerId">(OUT) A pointer to a user allocated wmx_ManufacturerId_t struct that holds the device manufacturer Id (both integer and string representation).</param>
/// <param name="serialNumber">(OUT) A pointer to a user allocated wmx_SerialNumber_t struct that holds the device�s serial number string.</param>
/// <param name="nvmVersion">(OUT) A pointer to a user allocated wmx_NvmVersion_t struct that holds the device�s Nvm Version binary data.</param>
/// <param name="nonce">(OUT) A pointer to a user allocated wmx_Nonce_t struct that holds the device�s Nonce blob.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceDetailsEx(	wmx_MacAddress_t macAddress,
																		wmx_pModelType_t modelType,
																		wmx_pManufacturer_t manufacturer,
																		wmx_pSerialNumber_t serialNumber,
																		wmx_pNvmVersion_t nvmVersion,
																		wmx_pODMInfo_t odmInfo,
																		wmx_pNonce_t nonce,
																		wmx_pDevicePID_t pid); 


// <summary>
// This API allows the user to obtain the versions of various components of the device.
// </summary>
//
// <param name="pDeviceVersion">(OUT) A pointer to a user-allocated wmx_pDeviceVersion_t struct to which the API will copy the versions information.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceVersion( wmx_pDeviceVersion_t pDeviceVersion	);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ResetDevice( );
#endif // _WMX_SDK_MSC_2_H
