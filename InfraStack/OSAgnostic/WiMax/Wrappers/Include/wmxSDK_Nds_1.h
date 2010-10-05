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
#ifndef _WMX_SDK_NDS_1_H
#define _WMX_SDK_NDS_1_H

#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Nds_Cmn.h"
#include "wmxSDK_Coex_1.h"
#include "CommonServices.h"
#include "WrappersCommon.h"

/// <summary>
/// A constant specifying the maximal length of a channel-info structs vector (in terms of the number of wmx_ChannelInfo_t structs the vector can contain).
/// </summary>
#define MAX_REALM_SIZE2 512 // TODO: Oran - unify with l4db #define
#define NSP_ID_SIZE 3
#define LOWEST_RSSI 0
#define LOWEST_CINR 0
#define LOWEST_LINK_QUALITY 0
#define SII_MAX_COUNT 32 // TODO: [Oran] replace with a real value when such is available

/// <summary>
/// A constant specifying the maximal length of a NAPs structs vector (in terms of the number of wmx_NAP_t structs the vector can contain).
/// </summary>
#define WMX_NAPS_MAX_NUM WMX_IDS_MAX_NUM
#define	WMX_PROFILES_MAX_NUM WMX_NAPS_MAX_NUM


/// <summary>
/// Type definitions for variables that are fields of the wmx_THCriteria_t struct. 
/// </summary>
typedef UINT8 wmx_RssiThreshold_t, *wmx_pRssiThreshold_t;
typedef UINT8 wmx_CinrThreshold_t, *wmx_pCinrThreshold_t;


/// <summary>
/// Type definition for a variable containing the ID of a NAP. 
/// </summary>
typedef UINT8 wmx_NAPid_t[3], *wmx_pNAPid_t;
typedef UINT16 wmx_ChannelIds_t[WMX_CHANNELS_MAX_NUM], *wmx_pChannelIds_t;
typedef UINT16 wmx_PreambleId_t[WMX_CHANNELS_MAX_NUM], *wmx_pPreambleId_t;
typedef UINT32 wmx_NSPServerId_t, *wmx_pNSPServerId_t;
typedef char wmx_VerboseNspName_t[MAX_VERBOSE_NSP_NAME_SIZE], *wmx_pVerboseNspName;
typedef char wmx_Realm_t[MAX_REALM_SIZE2], *wmx_pRealm_t;

typedef enum _wmx_ConnectionMode_t
{
	CONNECTION_MODE_MANUAL = 0x01,
	CONNECTION_MODE_AUTOMATIC,
	CONNECTION_MODE_DCD_DISCOVERY
} wmx_ConnectionMode_t, *wmx_pConnectionMode_t;

typedef enum _wmx_RoamingMode_t
{
	USER_ENABLE_ROAMING = 0x1,
	USER_DISABLE_ROAMING
} wmx_RoamingMode_t, *wmx_pRoamingMode_t;

/// <summary>
/// Type definition for an enum specifying the possible scan policies which can be set to the device as part of a scan command.
/// </summary>
typedef enum _wmx_ScanPolicy_t
{
	SCAN_MODE_FIND_FIRST  = 0x01,
	SCAN_MODE_FIND_ALL
} wmx_ScanPolicy_t, *wmx_pScanPolicy_t;

/// <summary>
/// Type definition for an enum specifying the realm requesting options.
/// </summary>
typedef enum _wmx_RequestRealm_t
{
	REQUEST_REALM_REQUEST = 0x01,
	REQUEST_REALM_DONT_REQUEST
} wmx_RequestRealm_t, *wmx_pRequestRealm_t;

/// <summary>
/// Type definition for a struct containing information requested during a connect command.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_ConnectFlags_t
{
	UINT32 visitedNspId;
	wmx_RequestRealm_t requestRealm;
	UINT8 SIQ;
} wmx_ConnectFlags_t, *wmx_pConnectFlags_t;
#pragma pack( pop )


/// <summary>
/// Type definition for a struct containing signal quality thresholds criteria specifying the minimal signal quality acceptable for a successful connection
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_THCriteria_t
{
	wmx_RssiThreshold_t rssiTH;			// Ignore detected base-stations with Rx RSSI that is below this threshold
	wmx_CinrThreshold_t cinrTH;			// Ignore detected base-stations with Rx CINR that is below this threshold
}wmx_THCriteria_t, *wmx_pTHCriteria_t;
#pragma pack( pop )

/// <summary>
/// Type definition for a struct containing base-station selection criteria.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_BSSelectionCriteria_t
{
	wmx_BSid_t 			bsID;				// MAC address (BSid) of interesting base-stations
	wmx_BSidMask_t 		bsIDmask;			// A 6 byte mask that is combined with the BSid to specify which bits are relevant for the screening
}wmx_BSSelectionCriteria_t, *wmx_pBSSelectionCriteria_t;
#pragma pack( pop )

/// <summary>
/// Type definition for an enum specifying the possible outcomes of a scan cycle.
///
/// Values:
///	ScanSuccessful		// done scanning the whole channel plan and NAPs were found
///	ScanExhausted		// done scanning the whole channel plan and NAPs weren't found
///	ScanStopped			// scan was stopped
/// ScanFailed			// scan failed
///
/// </summary>
typedef enum _wmx_ScanStatus_t
{
	ScanSuccessful = 0x1,		// done scanning the whole channel plan and NAPs were found
	ScanExhausted,				// done scanning the whole channel plan and NAPs weren't found
	ScanStopped,				// scan was stopped
	ScanFailed					// scan failed
} wmx_ScanStatus_t, *wmx_pScanStatus_t;

/// <summary>
/// Type definition for an enum specifying the possible BsID types inside of a scan result.
///
/// Values:
///	FULL_BSID			// full BsID
///	COMPRESSED_BSID		// compressed BsID
///	FULL_NAP			// full BsID, but only the NAP part (first 3 bytes)
///	COMPRESSED_NAP		// compressed BsID, but only the NAP part (first 3 bytes)
///
/// </summary>
typedef enum _wmx_BsIdType_t
{
	FULL_BSID = 0x1,	// full BsID
	COMPRESSED_BSID,	// compressed BsID
	FULL_NAP,			// full BsID, but only the NAP part (first 3 bytes)
	COMPRESSED_NAP		// compressed BsID, but only the NAP part (first 3 bytes)
} wmx_BsIdType_t, *wmx_pBsIdType_t;


/// <summary>
/// Type definition for a struct containing information of a specific NAP.
/// </summary>
typedef struct _wmx_NAP_t
{
	wmx_BSSelectionCriteria_t		bsCriteria;	
	wmx_BsIdType_t					bsIDType;
	UINT32							numChannels; // ACTUAL size of channelIdList
	wmx_ChannelIds_t				channelIdList;	
	wmx_SignalStrength_t			bestRssi;
	wmx_CINR_t						bestCINR;
	wmx_LinkQuality_t				bestLinkQuality;
	wmx_SignalStrength_t			RSSIs[WMX_CHANNELS_MAX_NUM]; // correlated to the channelIdList
	wmx_CINR_t						CINRs[WMX_CHANNELS_MAX_NUM]; // correlated to the channelIdList
	UINT16							DummyForCompilerHappy;
	BOOL							linkGrade[WMX_CHANNELS_MAX_NUM]; // correlated to the channelIdList. FALSE is under the threshold, TRUE otherwise
	wmx_LinkQuality_t				linkQuality[WMX_CHANNELS_MAX_NUM]; // correlated to the channelIdList
	wmx_NspChangeCount_t			changeCount;
	wmx_PreambleId_t				preambleIdList;
} wmx_NAP_t, *wmx_pNAP_t;

/// <summary>
/// Type definition for a struct containing information about the link's status.
/// (i.e. the status of the link between the device and the network it is connected to).
/// </summary>
typedef struct _wmx_LinkStatus_t
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
	BOOL						linkStatusArrived;
} wmx_LinkStatus_t, *wmx_pLinkStatus_t;

typedef struct _wmx_ChannedInfo_t	
{
	UINT32		frequency;
	UINT16		channelId;
	UINT8		bandwidth;
	UINT8		fft;
	BOOL		channedInfoArrived;
} wmx_ChannedInfo_t, *wmx_pChannedInfo_t;


/// <summary>
/// Type definition for a struct containing statistics information regarding traffic.
/// </summary>
#pragma pack( push, 1 )
typedef struct _wmx_Statistics_t
{
	UINT32  timeStamp;
	UINT32	TotalRxBytes;
	UINT32	TotalRxPackets;
	UINT32	TotalTxBytes;
	UINT32	TotalTxPackets;
} wmx_Statistics_t, *wmx_pStatistics_t;
#pragma pack( pop )

/// <summary>
/// Type definition for a structure giving a detailed info on a system state.
/// </summary>
typedef struct _wmx_SystemStateUpdate
{	
	wmx_ConnectProgressInfo_t ConnectProgress;	
	wmx_StateReason_t ReportStateReason;	
	wmx_SystemState_t SystemState;	
	wmx_LinkStatus_t linkStatus;
	wmx_MediaStatus_t MediaStatus;
	wmx_ChannedInfo_t channelInfo;
	UINT8				dummyCompilerHappy[3];
	wmx_RfSwitchesStatus_t rfSwitchesStatus;	
} wmx_SystemStateUpdate, *wmx_pSystemStateUpdate;

/// <summary>
/// Type definition for a struct containing BS information of a specific NAP.
/// </summary>
typedef struct _wmx_BsInfo_t
{
	wmx_BSid_t	bsID;
	wmx_NspChangeCount_t nspChangeCount;
} wmx_BsInfo_t, *wmx_pBsInfo_t;

/// <summary>
/// Type definition for a struct containing SII information.
/// </summary>
typedef struct _wmx_SII_t
{
	wmx_NSPid_t				nspIdList[SII_MAX_COUNT];
	UINT32					nspIdListSize;
	wmx_VerboseNspName_t	verboseNspNameList[SII_MAX_COUNT];
	wmx_Realm_t				realm;
} wmx_SII_t, *wmx_pSII_t;

/// <summary>
/// The signature definition of a wmx_pMediaStatusCB_t callback function. 
///
/// Once registered, this callback function will be called whenever the media status ofthe device is in changes.
/// </summary>
///
/// <param name="mediaStatus">(IN) An enum of type wmx_MediaStatus_t indicating if the link is up or down.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pMediaStatusCB_t)(	wmx_MediaStatus_t mediaStatus ) ;

/// <summary>
/// The signature defintion of a wmx_pScanUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever scan results are available.
///
/// This callback returns all NAPs aggregated since the beginning of the current scan.
///
/// The list is given as a vector of NAP information structs.
/// The vector's size is given using the pNumOfNaps argument (in terms of the number of wmx_NAP_t structs the vector contains).
/// The API can fill a vector of up to WMX_NAPS_MAX_NUM of wmx_NAP_t structs
/// (i.e. at maximum (WMX_NAPS_MAX_NUM * sizeof(wmx_NAP_t)) bytes).
///
/// The memory allocation for the NAPs vector will be valid only for the duration of the callback. The user must copy any information he needs to memory he allocated.
/// </summary>
///
/// <param name="numOfNaps">(IN) A UINT32 specifying the number of NAPs in the nsps vector.</param>
/// <param name="pNaps">(IN) A pointer to a wrapper allocated buffer which contains a vector of wmx_NAP_t structs containing information about the NAPs discovered in the scan operation so far.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*wmx_pScanUpdateCB_t)( wmx_ScanStatus_t scanStatus, UINT32 numOfNaps, wmx_pNAP_t pNaps );

/// <summary>
/// The signature defintion of a wmx_pRecentBSsCB_t callback function. 
///
/// Once registered, this callback function will be called upon neighbor advertisement indication. The SBS (serving BS) is the 
/// first one in the list and after it the neighbors' channels
/// </summary>
///
/// <param name="numOfChannelInfos">Number of channel infos in the list.</param>
/// <param name="pChannelInfos">Channels of the SBS and its neighbor channels. The SBS is the first one in the list</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*wmx_pRecentBSsCB_t)( UINT32 numOfChannelInfos, wmx_pChannelInfo_t pChannelInfos );

/// <summary>
/// The signature defintion of a wmx_pConnectCompletedCB_t callback function. 
///
/// Once registered, this callback function will be called upon connect attempt completion, and at least once for every time wmx_CmdStartConnect was called successfully.
/// </summary>
///
/// <param name="connectStatus">(IN) A wmx_ConnectStatus_t enum providing the status of the connect attempt that has finished.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*wmx_pConnectCompletedCB_t)( wmx_ConnectStatus_t connectStatus );

/// <summary>
/// The signature defintion of a wmx_pSystemStateUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever the WiMAX system state the device is in changes.
/// </summary>
///
/// <param name="systemStateUpdate">(IN) A pointer to a wrapper allocated buffer which contains a wmx_SystemStateUpdate struct containing a detailed info of a WiMAX system state</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pSystemStateUpdateCB_t)( wmx_pSystemStateUpdate systemStateUpdate ) ;
/// <summary>
/// The signature defintion of a wmx_pBsInfoUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever BS info is available.
/// </summary>
///
/// <param name="bsInfo">(IN) A pointer to a wrapper allocated buffer which contains a wmx_pBsInfo_t struct containing the full BSID and change count of a discovered NAP</param>
///
/// <returns>void</returns>
typedef void (*wmx_pBsInfoUpdateCB_t)( wmx_pBsInfo_t bsInfo );

/// <summary>
/// The signature defintion of a wmx_pSIIUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever SII info is available.
/// </summary>
///
/// <param name="sii">(IN) A pointer to a wrapper allocated buffer which contains a wmx_pSII_t struct containing 16g info of a discovered NAP</param>
///
/// <returns>void</returns>
typedef void (*wmx_pSIIUpdateCB_t)( wmx_pSII_t sii );

/// <summary>
/// The signature defintion of a wmx_pBekBufferCB_t callback function. 
///
/// Once registered, this callback function will be called whenever Bek buffer is available.
/// </summary>
///
/// <param name="BEKBuffer">(IN) A pointer to a wrapper allocated buffer which contains a 16 byte Key</param>
///
/// <returns>void</returns>
typedef void (*wmx_pBekBufferCB_t)( wmx_pBEKBuffer_t BEKBuffer);


/// <summary>
/// This API switches on the RF function of the WiMAX device. The function is used in the wmx_RfOn
/// Not for any user use!!!
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_InternalRfOn(); 

 
/// <summary>
/// This API switches off the RF function of the WiMAX device. The function is used in the wmx_RfOff.
/// Not for any user use!!!
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_InternalRfOff();

/// <summary>
/// This API causes the device to start a scan operation.
/// 
/// This is a non-blocking API. It returns after the scan request was issued to the driver.
///
/// To get the results of the scan operation (i.e. the detected NAPs) and indication of scan operation completion (successful or not),
/// the user can register a callback function using the wmx_RegisterScanUpdateCB API.
/// The scan results reporting policy can be specified using the wmx_SetScanPolicy API.
///
/// The scan operation follows the channel plan that was configured (see wmx_SetChannelPlan)
/// and behaves according to the configuration that was set by the wmx_SetScanPolicy API.
///
/// A complete scan cycle will go through the whole channel plan.
/// However, scanning cycles will repeat forever!!, at pre-configured intervals set by the wmx_SetScanPolicy API, until one of the following occurs:
/// 1. The user invokes the wmx_CmdStopScan API.
/// 2. The user invokes the wmx_CmdStartConnect API to start a connection attempt to one of the discovered NAPs.
/// 3. The user changes the RF state to Off.
/// 4. A problem prohibits the device from continuing the scan.
/// </summary>
///
/// <param name="coexPriority">(IN) A value indicating the priority of the scan.</param>
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_CmdStartScan(wmx_CoexPriority_t coexPriority);


/// <summary>
/// This API causes the device to stop a scan operation.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_CmdStopScan();

/// <summary>
/// The registration API for a wmx_pSystemStateUpdateCB_t callback function.
/// </summary>
///
/// <param name="systemStateUpdateCB">(IN) A pointer to the application function to be called when the system state changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterSystemStateUpdateCB( wmx_pSystemStateUpdateCB_t systemStateUpdateCB );


/// <summary>
/// The de-registration API for a wmx_pSystemStateUpdateCB_t callback function.
/// </summary>
///
/// <param name="systemStateUpdateCB">(IN) A pointer to the application function to be unregistered.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterSystemStateUpdateCB( wmx_pSystemStateUpdateCB_t systemStateUpdateCB );

/// <summary>
/// The registration API for a wmx_pMediaStatusCB_t callback function.
/// </summary>
///
/// <param name="systemStateUpdateCB">(IN) A pointer to the application function to be called when the media status updates through a system state change report.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterMediaStatusCB( wmx_pMediaStatusCB_t mediaStatusCB );


/// <summary>
/// The de-registration API for a wmx_pMediaStatusCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterMediaStatusCB();


/// <summary>
/// The de-registration API for a all wmx_pSystemStateUpdateCB_t callback functions.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterAllSystemStateUpdateCBs();


/// <summary>
/// The registration API for a wmx_pScanUpdateCB_t callback function.
/// </summary>
///
/// <param name="scanUpdateCB">(IN) A pointer to the application function to be called when scan results are available.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterScanUpdateCB( wmx_pScanUpdateCB_t scanUpdateCB );


/// <summary>
/// The de-registration API for a wmx_pScanUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterScanUpdateCB();


/// <summary>
/// The registration API for a wmx_pBsInfoUpdateCB_t callback function.
/// </summary>
///
/// <param name="scanUpdateCB">(IN) A pointer to the function to be called when bs info is available.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterBsInfoUpdateCB( wmx_pBsInfoUpdateCB_t bsInfoUpdateCB );

wmx_Status_t wmx_RegisterBEKBufferCB( wmx_pBekBufferCB_t pBekBufferCB);

wmx_Status_t wmx_UnregisterBEKBufferCB();

/// <summary>
/// The de-registration API for a wmx_pBsInfoUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterBsInfoUpdateCB();


/// <summary>
/// The registration API for a wmx_pSIIUpdateCB_t callback function.
/// </summary>
///
/// <param name="scanUpdateCB">(IN) A pointer to the function to be called when sii (16g) info is available.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterSIIUpdateCB( wmx_pSIIUpdateCB_t siiUpdateCB );


/// <summary>
/// The de-registration API for a wmx_pSIIUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterSIIUpdateCB();

/// <summary>
/// The registration API for a wmx_pRecentBSsCB_t callback function.
/// </summary>
///
/// <param name="scanUpdateCB">(IN) A pointer to the function to be called when neighbor's advertisement is available.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterRecentBSsCB( wmx_pRecentBSsCB_t recentBSsCB );


/// <summary>
/// The de-registration API for a wmx_pRecentBSsCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterRecentBSsCB();


/// <summary>
/// This API commands the device to start a connection attempt to the BS / NAP specified in the bsCriteria argument.
///
/// This is a non-blocking API. It returns after the connect request was issued to the driver.
///
/// To get notification of the connect operation completion (successful or not), the user can register a callback function using the wmx_RegisterConnectCompletedCB API.
///
/// At any given time, the application can instruct the driver to disconnect from the network using the wmx_CmdDisconnect command.
/// </summary>
///
/// <param name="bsCriteria">(IN) A specific BS_ID to connect to, or a NAP_ID, depeneding on the mask specified.</param>
/// <param name="thCriteria">(IN) Signal quality thresholds criteria specifying the minimal signal quality acceptable for a successful connection.</param>
/// <param name="connectFlags">(IN) Flags specifing the requested info following the connect command.</param>
/// <param name="coexPriority">(IN) A value indicating the priority of the connection.</param>
/// <param name="connectionMode">(IN) A value indicating if the connection is automatic or manual.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_CmdStartConnect( wmx_BSSelectionCriteria_t bsCriteria, wmx_THCriteria_t thCriteria, wmx_pConnectFlags_t connectFlags, wmx_CoexPriority_t coexPriority, wmx_ConnectionMode_t connectionMode );


/// <summary>
/// This API commands the device to disconnect from the network (i.e. From the currently connected NAP). 
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_CmdCancelConnect( );


/// <summary>
/// This API commands the device to disconnect from the network (i.e. From the currently connected NAP). 
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_CmdDisconnect();


/// <summary>
/// This API provides the NAP to which the device is currently connected.
///
/// If we are not currently connected the return value will be WMX_ST_DATA_UNAVAILABLE.
/// </summary>
///
/// <param name="connectedNAP">(OUT) A pointer to a user-allocated wmx_NAP_t struct in which the API will place information about the currently connected NAP.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_GetConnectedNAP( wmx_pNAP_t connectedNAP );


/// <summary>
/// This API provides information about the last known NAPs (those detected during the last scan operation).
///
/// The list is given as a vector of NAP information structs.
///
/// The user must allocate space for the vector in advance and state its size using the pNumOfNaps argument 
/// (in terms of the number of wmx_NAP_t structs the vector may contain).
///
/// The API can fill a vector of up to WMX_NAPS_MAX_NUM of wmx_NAP_t structs
/// (i.e. at maximum the user should allocate (WMX_NAPS_MAX_NUM * sizeof(wmx_NAP_t)) bytes).
/// The value entered by the user in pNumOfNaps will be the actual max number of wmx_NAP_t structs filled 
/// in the vector. The API will return the actual number of structs in pNumOfNaps (0 if no NAPs are found).
/// </summary>
///
/// <param name="pNumOfNaps">(INOUT) A pointer to a user-allocated UINT32 containing the expected number of NAPs as input and the actual number of NAPs in the pNaps vector as output.</param>
/// <param name="pNaps">(OUT) A pointer to a user-allocated buffer which will be filled with a vector of wmx_NAP_t structs containing information about the last known NAPs.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
//wmx_Status_t wmx_GetLastKnownNAPs( UINT32* pNumOfNaps, wmx_pNAP_t pNaps );


/// <summary>
/// This API specifies the list of frequencies and other related Phy attributes required during the scanning operation to detect networks.
///
/// The list is given as a vector of channel information structs.
///
/// The user must allocate space for the vector in advance and state its size using the numOfChannelInfos argument 
/// (in terms of the number of wmx_ChannelInfo_t structs the vector may contain).
///
/// The vector should only contain up to WMX_CHANNELS_MAX_NUM of wmx_ChannelInfo_t structs
/// (i.e. at maximum the user should allocate (WMX_CHANNELS_MAX_NUM * sizeof(wmx_ChannelInfo_t)) bytes).
/// </summary>
///
/// <param name="numOfChannelInfos">(IN) A UINT32 specifying the number of information elements in the channel plan.</param>
/// <param name="channelInfos">(IN) A pointer to a user-allocated buffer which contains the vector of wmx_ChannelInfo_t information element structs.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_SetChannelPlan( UINT32 numOfChannelInfos, wmx_pChannelInfo_t channelInfos, wmx_ScanPolicy_t scanPolicy );


/// <summary>
/// This API returns information that describes the status of the link (i.e. the link between the device and the network it is connected to).
///
/// If we are not currently connected the return value will be WMX_ST_DATA_UNAVAILABLE.
/// </summary>
///
/// <param name="linkStatus">(OUT) A pointer to a user-allocated wmx_pLinkStatus_t struct in which the API will place information about the link's status.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetLinkStatus( wmx_pLinkStatus_t linkStatus	);

/// <summary>
/// This API returns various statistics information regarding traffic.
///
/// Some of the statistics are provided per each established service flow.
/// These SF specific statistics are given as a vector of SF statistics information structs.
///
/// The user must allocate space for the vector in advance and state its size using the pNoOfSfs argument 
/// (in terms of the number of wmx_pSfStatistics_t structs the vector may contain).
///
/// The API can fill a vector of up to WMX_SF_STATS_MAX_NUM of wmx_pSfStatistics_t structs
/// (i.e. at maximum the user should allocate (WMX_SF_STATS_MAX_NUM * sizeof(wmx_pSfStatistics_t)) bytes).
/// The value entered by the user in pNoOfSfs will be the actual max number of wmx_pSfStatistics_t structs filled 
/// in the vector. The API will return the actual number of structs in pNoOfSfs.
/// </summary>
///
/// <param name="pStatistics">(OUT) A pointer to a user-allocated wmx_pStatistics_t struct to which the API will copy the gathered statistics information.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetStatistics(wmx_pStatistics_t	pStatistics); 

// <summary>
// This API allows the user to set the coexistance mode of the device.
// </summary>
//
// <param name="">No parameters.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_IsAssociated(wmx_pAssociate_t pAssociated);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetSpLockStatus(wmx_pSpLock_t pSpLockStatus);
wmx_Status_t wmx_CmdSpLockUnLock(wmx_SpLockCode_t SpLockCode);

#endif // _WMX_SDK_NDS_1_H
