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
#include "NDnSAgent_DB_if.h"
#include "NDnSAgent_Internals.h"

#ifndef _NDNS_AGENT_L4PLANNER_
#define _NDNS_AGENT_L4PLANNER_

/// <summary>
/// This enum describes the differenet scan types
/// </summary>
typedef enum _wmx_ScanType
{
	ScanType_WhileScan = 0x1,
	ScanType_PreferredList
}wmx_ScanType, * wmx_pScanType;

/// <summary>
/// Struct that holds a preferred NSP information
/// </summary>
typedef struct _wmx_PreferredNsp
{
	wmx_NSPid_t		nspIds[WMX_NSP_IDS_MAX_NUM];
	UINT32			nspIdsSize;
	char			name[WMX_NSP_NAME_MAX_SIZE];
	wmx_NAPid_t		napIds[WMX_NAPS_MAX_NUM];
	UINT32			napsSize;
	BOOL			isHome;
}wmx_PreferredNsp, *wmx_pPreferredNsp;

typedef struct _ChannelInfoArr
{
	pChannelInfo_t pChannelInfoArr;
	UINT32		   arrSize;
}wmx_ChannelInfoArr, *wmx_pChannelInfoArr;

/// <summary>
/// Generates the master channel plan according to the requested scan type
/// </summary>
/// <param name="scanType">(IN)  the requested scan type</param>
/// <param name="pChannelInfoList">(OUT) an array of channel infos allocated by the user</param>
/// <param name="nChannelInfoListSize">(IN)  the size of the array allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GenerateMCP( wmx_ScanType scanType, wmx_pChannelInfo_t pChannelInfoList, UINT32 *nChannelInfoListSize);
/// <summary>
/// Generates the master channel plan for a specific NSP
/// </summary>
/// <param name="nspId">(IN)  the nsp Id</param>
/// <param name="pChannelInfoList">(OUT) an array of channel infos allocated by the user</param>
/// <param name="nChannelInfoListSize">(IN)  the size of the array allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GenerateNspMCP( wmx_NSPid_t nspId, wmx_pChannelInfo_t pChannelInfoList, UINT32 *nChannelInfoListSize);

/// <summary>
/// Generates the master channel plan according to the requested scan type
/// </summary>
/// <param name="pChannelInfos">(OUT) an array of channel info ((a struct defined in the L4db))</param>
/// <param name="nChannelInfosSize">(IN)  the size of the array allocated by the user
///			                        (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GetWideScanParams(pChannelInfo_t pChannelInfos, UINT32 * nChannelInfosSize);

/// <summary>
/// Generates the list of preferred NSPs according the policy in the L4db
/// </summary>
/// <param name="pPreferredNsps">(OUT) an array of preferred NSPs allocated by the user</param>
/// <param name="nPreferredNspsSize">(IN)  the size of the array allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GetPreferredNspList(wmx_pPreferredNsp pPreferredNsps, UINT32 * nPreferredNspsSize); 

/// <summary>
/// find the max detected channel list length for specific Current Nsp.
/// this function only get the size in order to allocate the exact size of channels (in the calling function)
/// <param name="nspId">(in)the specific NSP we fetching the data for </param name>
/// <param name="pNumOfChannels">(OUT) contain the the number of detected channels per current NSP</param name>
/// </summary>
wmx_Status_t L4P_GetMaxDetectedChannelPerNsp(wmx_NSPid_t nspId, UINT32 *pNumOfChannels);

///<summary>
////merge two channels list into one list (pTargetChannelList)
/// </summary>
/// <param name="pSourceChannelList">(in) list to merge into the target list</param name>
/// <param name="pTargetChannelList">(in/out) in - the original channel list 
///												 out - the merged list		</param name>
/// <param name="numOfAllocatedChannel">(in) the number of channels can be found (in total) in the final channel list</param name>
/// <param name="checkTtl">(in) indication if we need to compare the channels using the ttl as well</param name>
wmx_Status_t l4P_Merge2ListsOfChannelInfo(wmx_pChannelInfoArr  pSourceChannelList,
										  wmx_pChannelInfoArr  pTargetChannelList,
										  UINT32		 numOfAllocatedChannel,
										  BOOL			 checkTtl);

///<summary>
///merge the discovered channels into a given list and return a unique list 
/// </summary>
/// <param name="pChannelArr">(out) the allocated channel will be populate with the list. 
///								The size of the array will contain the actual allocated list length and return  the actual number of channels that were returned</param name>
wmx_Status_t l4P_MergeAllDiscoveredChannelList(wmx_pChannelInfoArr	pChannelArr);

/// <summary>
/// creates the discovered channel list for the specific Nsp sorted accourding the Age
/// <param name="nspId">(in)the specific NSP we fetching the data for </param name>
/// <param name="pDiscoveredChannelArr">(OUT) contain the list of the discovered Channels per the NSP.
///										contain the size of the allocated list and return the actual size</param name>
/// </summary>
wmx_Status_t L4P_GetDetectedChannelsPerNsp(wmx_NSPid_t nspId, wmx_pChannelInfoArr pDiscoveredChannelArr);

///<summary>
///fetch the provisioned channels and return a unique list sorted by the TTL and then the rest of the provisioned channels
/// </summary>
/// <param name="pTargetLIst">(in/out) the allocated channel will contain the provisions channels </param name>
///										IN - contain the actual allocated list length
///										OUT - contain the actual number of channels that were populate</param name>
/// <param name="pDiscoveredChannelList">(in) the detected channel list </param name>
/// <param name="pProvisionChannelList">(in) the provisioned channel list </param name>
/// <param name="pIsDiscoveredAddedToTheList">(out) an array the has the same number of elements as in the pDiscoveredChannelList
///											  this array use to marke the discovered channels we allready populate in the pAppendedChannelList</param name>
wmx_Status_t l4P_GenerateProvisionedChannels(wmx_pChannelInfoArr pTargetLIst,
										wmx_pChannelInfoArr pDiscoveredChannelList,
										wmx_pChannelInfoArr pProvisionChannelList,
										BYTE			*pIsDiscoveredAddedToTheList);

///<summary>
///fetch the recent channels and return the recent channels with all the preamble set to on
/// </summary>
/// <param name="pTargetLIst">(in/out) the allocated channel will contain the recent channels </param name>
///							  IN - contain the actual allocated list length
///							  OUT - contain the actual number of channels that were populate in the pAppendedChannelList list</param name>
/// <param name="pDiscoveredChannelList">(in) the recent channel list </param name>
/// <param name="populatePreamble"> (in) indicate if we should set all the preambles to 1 or leave them without cange</param name>
wmx_Status_t l4P_GenerateRecentChannels(wmx_pChannelInfoArr pTargetLIst,
										wmx_pChannelInfoArr pDiscoveredChannelList,
										BOOL				populatePreamble);

///<summary>
///	Fill the target list with the elements in the source list that has mach entry (same index) in the pMarkedList containing 0
/// </summary>
/// <param name="pTargetList">(in/out) Array that is filled with the channels from the pSourceList accourding to pMarkedList</param name>
///							  IN - contain the actual allocated list length
///							  OUT - contain the actual number of channels that were populate in the pTargetList list</param name>
/// <param name="pSourceList">(in) the source channel list </param name>
/// <param name="pMarkedList"> (in) an array that hold indication telling if the specific source element should be added to the target</param name>
wmx_Status_t l4P_GenerateUnmarkedList(wmx_pChannelInfoArr pTargetList,
									  wmx_pChannelInfoArr pSourceList,
									  BYTE				  *pMarkedList);

/// <summary>
/// Append a new channel plan to an existing channel info Array without removing duplicates acording to the right order
/// </summary>
wmx_Status_t l4P_AppendChannelPlanIntoChannelInfoList(pChannelPlan_t pSourceChannelPlan, 
													 wmx_pChannelInfoArr pTargetChannelInfoArr,
													 UINT32 allocChannelsSize);

/// <summary>
/// Append a new channelInfo array into an existing channel info Array without removing duplicates acording to the right order
/// </summary>
wmx_Status_t l4P_AppendTwoChannelInfoList(wmx_pChannelInfoArr pSourceChannelInfoArr, 
										  wmx_pChannelInfoArr pTargetChannelInfoArr,
										  UINT32 allocChannelsSize);

//remove duplicated channels from channelInfo array
wmx_Status_t l4P_RemoveRedundantChannels(wmx_pChannelInfoArr pOriginalArr);

#endif //_NDNS_AGENT_L4PLANNER_