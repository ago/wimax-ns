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
#ifndef _NDS_AGENT_UTILS_
#define _NDS_AGENT_UTILS_

#define WMX_FREE(Arr) if(Arr){free(Arr); Arr=NULL;} //macro that try to free allocated pointer

// Returns the duration (in seconds) since the connect succeeded, 0 if we are not connected
DOUBLE  wmxNds_GetConnectionDuration();

void wmxNds_LinkStatusToUserLinkStatus(wmx_pUserLinkStatus_t userLinkStatus, wmx_LinkStatus_t linkStatus);

// Unregister L5 Target from indications lists.
void UnRegisterL5Target(L5_TARGET_ID targetID);

// Used to register a Target on Indication.
wmx_Status_t NDnSAgent_RegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id);

// Used to unregister a Target from an Indication
wmx_Status_t NDnSAgent_UnRegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id);

// Returns TRUE if the NSP is valid for connection
BOOL IsValidNSP(wmx_NSPid_t nspID);

// Returns TRUE if a valid NSP was found in the list, and the IN OUT parameter validNSP holds its value.
BOOL GetValidNSP(wmx_pNSP_t validNSP, UINT32 numOfNSPs, wmx_pNSP_t pNSPs);

BOOL UseCurrentPreferredScan();

BOOL IsBsIdEqual(wmx_BSid_t bsId1,wmx_BSid_t bsId2, wmx_BsIdType_t bsIdType);

BOOL GetChannelIdsByThreshold(L4C_LinkGrade linkGrade, wmx_pNAP_t pNAP, wmx_pChannelIds_t pChIds, UINT32 *numOfChIds);

BOOL NAPs2NSPs(UINT32 numOfNAP, wmx_pNAP_t pNAP, UINT32 *numOfNSP, wmx_NSP_t nsps[WMX_NSPS_MAX_NUM],
			   wmx_BSid_t bsIds[WMX_NSPS_MAX_NUM], wmx_BsIdType_t bsIdsTypes[WMX_NSPS_MAX_NUM],
			   UINT32 *numOfNapsWithNoNSP, wmx_pNAP_t napsWithNoNSP, BOOL bUseUnderThreshold);

// The function fill the wmx_NSP_t struct from the provisioned and discovered information
wmx_Status_t GetNspStruct(wmx_NSPid_t nspId, wmx_pNSP_t pNSP);

int GetNapId(wmx_BSid_t bsId);

// Translate the BsID mask to the correct format of the BsID
wmx_BsIdType_t GetBsIdType(wmx_BSidMask_t mask);

// Convert NAP to bs criteria
BOOL NAP2BSCriteria( wmx_NAPid_t napId, wmx_BsIdType_t bsIdType, wmx_pBSSelectionCriteria_t bsCriteria );

// The function gets two nsps and returns TRUE if they are the same, FALSE otherwise
BOOL NDnSAgent_IsNSPsEqual(wmx_pNSP_t nsp1, wmx_pNSP_t nsp2);

BOOL NDnSAgent_IsNspIdInNSP(wmx_NSPid_t nspId1, wmx_pNSP_t nsp2);

BOOL NDnSAgent_BuildFumoPath(char* src, char* dest, UINT32 destLen);

void NDnSAgent_HexEncode(const UINT8 *binPtr, char *hexPtr, UINT32 binLength);
BOOL NDnSAgent_HexDecode(const char *hexPtr, UINT8 *binPtr, UINT32 length);

// The function gets the driver mode and saves the L4DB to the disk
void SaveToDB();

// function converts a coex priority to a coex state
wmx_CoexState_t NDnSAgent_CoexPrio2CoexState (wmx_CoexPriority_t coexPrio);

extern wmx_CoexistenceMode_t initialCoexMode;
#endif // _NDS_AGENT_UTILS