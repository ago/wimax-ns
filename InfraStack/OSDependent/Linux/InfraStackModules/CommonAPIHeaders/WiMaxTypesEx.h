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
#ifndef _WIMAX_API_TYPES_EX_H
#define _WIMAX_API_TYPES_EX_H

#include "WiMaxType.h"

#define SIZE_OF_ODM_INFO_BLOB 108
#define PREAMBLES_LEN	  15
#define WIMAX_API_CHANNEL_INFO_LIST_MAX_NUM_OF_ENTRIES 32

typedef DOUBLE WIMAX_API_CONNECTION_TIME;
typedef WIMAX_API_CONNECTION_TIME *WIMAX_API_CONNECTION_TIME_P;

typedef UINT8 WIMAX_API_BINARY_BLOB[SIZE_OF_ODM_INFO_BLOB], *WIMAX_API_BINARY_BLOB_P;

/// <summary>
/// Type definition for a struct containing the NVM Version of the device. 
/// </summary>
typedef struct _WIMAX_API_NVM_VERSION
{
	UINT16 GeneralImageVersion;
	UINT16 ContentVersion;
} WIMAX_API_NVM_VERSION, *WIMAX_API_NVM_VERSION_P;

/// <summary>
/// Type definitions for variables that are fields of the wmx_ChannelInfo_t struct. 
/// </summary>
typedef UINT16 WMX_CHANNEL_ID, *WMX_CHANNEL_ID_P;
typedef UINT32 WMX_PPM_FREQ_ERROR, *WMX_PPM_FREQ_ERROR_P;
typedef UINT8 WMX_PREAMBLES[PREAMBLES_LEN], *WMX_PREAMBLES_P;
typedef UINT32 WMX_FREQUENCY, *WMX_FREQUENCY_P;
typedef UINT32 WMX_LINK_QUALITY_EX, *WMX_LINK_QUALITY_EX_P;
/// <summary>
/// Type definition for an enum specifying the possible ffts which can be set to the device as part of a wmx_ChannelInfo_t.
/// </summary>
typedef enum _WMX_FFT//_wmx_FFT_t
{
	_FFT_512 = 0x01,
	_FFT_1024 = 0x02
} WMX_FFT, *WMX_FFT_P;


/// <summary>
/// Type definition for an enum specifying the reason of the permissionupdate indication
/// </summary>
typedef enum _WMX_PERMISSION_UPDATE_EVENT
{
	WIMAX_API_PRIVILEGE_READ_WRITE_TAKEN = 0x01,
	WIMAX_API_PRIVILEGE_READ_WRITE_AVAILABLE = 0x02
} WMX_PERMISSION_UPDATE_EVENT, *_WMX_PERMISSION_UPDATE_EVENT_P;
/// <summary>
/// Type definition for an enum specifying the possible bandwidths which can be set to the device as part of a wmx_ChannelInfo_t.
/// </summary>
typedef enum _WMX_BW
{
	_BW_3_5 = 0x01,
	_BW_5,
	_BW_7,
	_BW_8_75,
	_BW_10
} WMX_BW, *WMX_BW_P;
/// <summary>
/// Type definitions for the duplex mode. 
/// </summary>
typedef UINT32	WMX_DUPLEX_MODE, *WMX_DUPLEX_MODE_P;

/// <summary>
/// Type definition for a struct containing information of a specific channel in a channel plan.
/// </summary>
typedef struct _WIMAX_API_CHANNEL_INFO
{
	WMX_CHANNEL_ID				channelID;
	WMX_FREQUENCY				frequency;			// The value in KHz in the range of 2.2Ghz � 6Ghz in resolution of  KHz
	WMX_BW						bw;					// 3.5Mhz, 5.0MHz, 7.5Mhz, 8.75Mhz, 10Mhz, 14Mhz and 20Mhz
	WMX_FFT						fft;
	WMX_PREAMBLES				preambleBitmap;		// A 114 bit map specifying the supported preambles
	WMX_DUPLEX_MODE				duplexMode;
} WIMAX_API_CHANNEL_INFO, *WIMAX_API_CHANNEL_INFO_P;

/// Enumeration card presence state.
typedef enum _WIMAX_API_CONNECTION_MODE
{
	WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_MANUAL_CONNECT,	/**< SDK automatically scans, but limits the span only to recent & provisioned networks. */
															/**< User manually triggers a connection attempt. */
	WIMAX_API_CONNECTION_SEMI_MANUAL_SCAN_AUTO_CONNECT,		/**< SDK automatically scans, but limits the span only to recent & provisioned networks. */
															/**< SDK automatically attempts connection with detected networks. */

	WIMAX_API_CONNECTION_AUTO_SCAN_MANUAL_CONNECT,			/**< SDK automatically scans. */
															/**< User manually triggers a connection attempt. */
	WIMAX_API_CONNECTION_AUTO_SCAN_AUTO_CONNECT,			/**< SDK automatically scans. */
															/**< SDK automatically attempts connection with detected networks. */
	WIMAX_API_CONNECTION_MANUAL_SCAN_MANUAL_CONNECT			/**< User manually triggers a scan. */
															/**< User manually triggers a connection attempt. */
															/**< This mode is meant to be used for testing purposes only!!! */
} WIMAX_API_CONNECTION_MODE, *WIMAX_API_CONNECTION_MODE_P;

typedef struct _WIMAX_API_LINK_STATUS_INFO_EX
{
	UINT32             structureSize;      /**< size of this structure. */
	UINT32             centerFrequency;    /**< Center frequncy of the current link from device to network, in unit of KHz */
	WMX_LINK_QUALITY_EX  linkQuality;	   /**< The quality of the signal (in %). */
   	UINT8              RSSI;               /**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x53, where -123dBm is encoded as 0x00 and -40dBm encoded as 0x53 with 1dB increments. */ 
	UINT8              CINR;               /**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x3F, where -10dB is encoded as 0x00 and 53dB encoded as 0x3F with 1dB increments. */
	UINT8              txPWR;              /**< Average transmit power for the last burst transmitted by the device. Based on IEEE802.16 standard, the values are ranging from 0xxx to 0xFF, where -84dBm is encoded as 0x00  and 43.5dBm is encoded as 0xFF with 0.5dB increment. */
	UINT8              bsId[6];            /**< BS ID of the current serving BS as received from the network */
} WIMAX_API_LINK_STATUS_INFO_EX, *WIMAX_API_LINK_STATUS_INFO_EX_P;




#ifndef NATIVE_WINDOWS
	//Linux
	/// Connected NSP information structure
	typedef struct _WIMAX_API_CONNECTED_NSP_INFO_EX
	{
		UINT32                      structureSize;                 /**< size of this structure. */
		char                     NSPName[MAX_SIZE_OF_NSP_NAME]; /**< Name of NSP */
		char                     NSPRealm[MAX_SIZE_OF_NSP_NAME];/**< Name of NSP */
		UINT32                      NSPid;                         /**< Identifier */
		BOOL                        activated;                     /**< Is the device activated TRUE=Activated FALSE=NotActivated */
		WMX_LINK_QUALITY_EX			linkQuality;				   /**< The quality of the signal (in %). */
		UINT8                       RSSI;                          /**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x53, where -123dBm is encoded as 0x00 and -40dBm encoded as 0x53 with 1dB increments. */
		UINT8                       CINR;                          /**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x3F, where -10dB is encoded as 0x00 and 53dB encoded as 0x3F with 1dB increments. */
		WIMAX_API_NETWORK_TYPE      networkType;                   /**< Current network type */
	} WIMAX_API_CONNECTED_NSP_INFO_EX, *WIMAX_API_CONNECTED_NSP_INFO_EX_P;
	
	/// NSP information structure
	typedef struct _WIMAX_API_NSP_INFO_EX
	{
		UINT32                    structureSize;                 /**< size of this structure. */
		WMX_LINK_QUALITY_EX		  linkQuality;				     /**< The quality of the signal (in %). */
		char                   NSPName[MAX_SIZE_OF_NSP_NAME]; /**< the name of the NSP */
		UINT32                    NSPid;                         /**< Identifier */
		UINT8                     RSSI;                          /**< RSSI value */
		UINT8                     CINR;                          /**< CINR value */  
		WIMAX_API_NETWORK_TYPE    networkType;                   /**< Current network type */    
	} WIMAX_API_NSP_INFO_EX, *WIMAX_API_NSP_INFO_EX_P;
	
	/// string structure for strings getters in order to allocate the correct buffer size
	typedef struct _WIMAX_API_WMF_COMPLIANCE_VERSION
	{
		UINT32              structureSize;    /**< size of this structure. */
	  char         version[MAX_SIZE_OF_STRING_BUFFER];
	} WIMAX_API_WMF_COMPLIANCE_VERSION, *WIMAX_API_WMF_COMPLIANCE_VERSION_P;
#else
	//windows
	/// Connected NSP information structure
	typedef struct _WIMAX_API_CONNECTED_NSP_INFO_EX
	{
		UINT32                      structureSize;                 /**< size of this structure. */
		UCHAR16                     NSPName[MAX_SIZE_OF_NSP_NAME]; /**< Name of NSP */
		UCHAR16                     NSPRealm[MAX_SIZE_OF_NSP_NAME];/**< Name of NSP */
		UINT32                      NSPid;                         /**< Identifier */
		BOOL                        activated;                     /**< Is the device activated TRUE=Activated FALSE=NotActivated */
		WMX_LINK_QUALITY_EX			linkQuality;				   /**< The quality of the signal (in %). */
		UINT8                       RSSI;                          /**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x53, where -123dBm is encoded as 0x00 and -40dBm encoded as 0x53 with 1dB increments. */
		UINT8                       CINR;                          /**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x3F, where -10dB is encoded as 0x00 and 53dB encoded as 0x3F with 1dB increments. */
		WIMAX_API_NETWORK_TYPE      networkType;                   /**< Current network type */
	} WIMAX_API_CONNECTED_NSP_INFO_EX, *WIMAX_API_CONNECTED_NSP_INFO_EX_P;
	
	/// NSP information structure
	typedef struct _WIMAX_API_NSP_INFO_EX
	{
		UINT32                    structureSize;                 /**< size of this structure. */
		WMX_LINK_QUALITY_EX		  linkQuality;				     /**< The quality of the signal (in %). */
		UCHAR16                   NSPName[MAX_SIZE_OF_NSP_NAME]; /**< the name of the NSP */
		UINT32                    NSPid;                         /**< Identifier */
		UINT8                     RSSI;                          /**< RSSI value */
		UINT8                     CINR;                          /**< CINR value */  
		WIMAX_API_NETWORK_TYPE    networkType;                   /**< Current network type */    
	} WIMAX_API_NSP_INFO_EX, *WIMAX_API_NSP_INFO_EX_P;
	
	/// string structure for strings getters in order to allocate the correct buffer size
	typedef struct _WIMAX_API_WMF_COMPLIANCE_VERSION
	{
		UINT32              structureSize;    /**< size of this structure. */
	  UCHAR16         version[MAX_SIZE_OF_STRING_BUFFER];
	} WIMAX_API_WMF_COMPLIANCE_VERSION, *WIMAX_API_WMF_COMPLIANCE_VERSION_P;
#endif

#define SIZE_OF_NONCE_BLOB 8
typedef UINT8 WIMAX_API_NONCE_BLOB[SIZE_OF_NONCE_BLOB], *WIMAX_API_NONCE_BLOB_P;
typedef enum _WMX_API_PLOCK_STATUS 
{
	NOT_LOCKED = 0x01,
	LOCKED = 0x02
} WMX_API_PLOCK_STATUS, *WMX_API_PLOCK_STATUS_P;


typedef struct _WIMAX_API_PACK_DOWNLOAD_INFO
{
	UINT32 downloadedBytes;
	UINT32 totalBytes;
} WIMAX_API_PACK_DOWNLOAD_INFO, *WIMAX_API_PACK_DOWNLOAD_INFO_P;

// Structure used for Platform Noise Mitigation parameters
typedef struct _WIMAX_API_PPNM_COMMDEV_INFO
{
	UINT32	channelNumber;					// Not Used Yet
	UINT32	centerFrequency;
	UINT32	frequencySpread; 				// (BW)
	UINT32	noisePower;						// Not Used Yet
	
	UINT32	signalToNoiseRatio;				//	(CINR)	
	/**< CINR measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x3F, where -10dB is encoded as 0x00 and 53dB encoded as 0x3F with 1dB increments. */

	UINT32	rSSI;
	/**< Mean RSSI measured by device. As according to IEEE 802.16 standard, values are ranging from 0x00 to 0x53, where -123dBm is encoded as 0x00 and -40dBm encoded as 0x53 with 1dB increments. */ 

	// The transmitter connect status:		
	UINT32	connectStatus;					// 0 = Not using channel; 1 = Using channel
	UINT32	bitError;			// Not used
	UINT32	reserved;					// reserved
} WIMAX_API_PNM_COMMDEV_INFO, *WIMAX_API_PPNM_COMMDEV_INFO_P;





/// Indicator for package download progress. 
/// !! This must be joined in the future with IndPackageUpdate
/// \param[in]  pDeviceId - Pointer to Device Identifier passed on open of device.
/// \param[out] pPackageDownloadInfo - Details of the package download progress.
typedef void (*IndPackageDownloadProgress) (WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_PACK_DOWNLOAD_INFO_P pPackageDownloadInfo);

#endif //_WIMAX_API_TYPES_EX_H