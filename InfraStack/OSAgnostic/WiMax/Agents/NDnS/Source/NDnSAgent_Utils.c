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
#include "NDnSAgent_Internals.h"
#include "NDnSAgent_Utils.h"
#include "NDnSAgent_DB_if.h"

#include "L5OpCodes.h"		
#include "Act.h"
#include "L4ConfigurationManager.h"
#include "wimax_osal_services_cmn.h"


// Returns the duration (in seconds) since the connect succeeded, 0 if we are not connected.
DOUBLE  wmxNds_GetConnectionDuration()
{
	UINT32 currentTime, connectTime;
	DOUBLE connectedTime = 0;

	currentTime = OSAL_timeGetTime();
	connectTime = L4db_GetConnectionTime();
	if (connectTime != DEFAULT_TIME)
	{
		connectedTime = (currentTime - connectTime) / 1000;
	}

	return connectedTime;
}

void wmxNds_LinkStatusToUserLinkStatus(wmx_pUserLinkStatus_t userLinkStatus, wmx_LinkStatus_t linkStatus)
{	
	userLinkStatus->rssi = linkStatus.rssi;
	userLinkStatus->cinr = linkStatus.cinr;
	userLinkStatus->frequency = linkStatus.frequency;
	userLinkStatus->power = linkStatus.power;
	userLinkStatus->linkQuality = linkStatus.linkQuality;
	userLinkStatus->time = wmxNds_GetConnectionDuration(); // The driver doesn't return connection time
	userLinkStatus->upLinkSpeed = linkStatus.upLinkSpeed;
	userLinkStatus->downLinkSpeed = linkStatus.downLinkSpeed;	
	//L4db_GetRecentNsp(&userLinkStatus->nspId);
	OSAL_memcpy_s(userLinkStatus->bsId, sizeof(wmx_BSid_t), linkStatus.bsId, sizeof(wmx_BSid_t));
}

// Unregister L5 Target from indications lists.
void UnRegisterL5Target(L5_TARGET_ID targetID)
{
	// Iterate the status indication list, for each indicator - remove the target ID:
	IndicatorSubscribers *indSubscribers;
	ListItem* handle;

	handle = CreateIterator(g_ndnsContext.indicatorSubscribersList);
	handle = Iterator_GetNext(g_ndnsContext.indicatorSubscribersList, handle, &indSubscribers);
	while (NULL != handle)
	{
		Indications_RemoveSubscriber(indSubscribers, targetID);
		handle = Iterator_GetNext(g_ndnsContext.indicatorSubscribersList, handle, &indSubscribers);
	}
	FreeIterator(g_ndnsContext.indicatorSubscribersList);
}


// Used to register a Target on Indication.
wmx_Status_t NDnSAgent_RegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id)
{	
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(g_ndnsContext.indicatorSubscribersList, status_indication_id, TRUE);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_RegisterIndicator(IN) - indSubscribers=%d, status_indication_id=%d, Origin=%d", 
																			indSubscribers, status_indication_id, nOriginID);
	//VERIFY(NULL != indSubscribers);
	if(indSubscribers == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Error registering indicator. indSubscribers == NULL");
		nds_pFuncs->pfnSendErrorReport(L5_TARGET_NDNS, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return WMX_ST_FAIL;
	}

	Indications_AddSubscriber(indSubscribers, nOriginID);
	//Perform actions according to size of list and subscriber addition

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_RegisterIndicator(OUT)");
	return WMX_ST_OK;
}

// Used to unregister a Target from an Indication
wmx_Status_t NDnSAgent_UnRegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id)
{
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(g_ndnsContext.indicatorSubscribersList, status_indication_id, FALSE);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_UnRegisterIndicator(IN) - indSubscribers=%d, status_indication_id=%d, Origin=%d", 
																				indSubscribers, status_indication_id, nOriginID);
	if ((NULL == indSubscribers) || (!Indications_RemoveSubscriber(indSubscribers, nOriginID)))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "UnRegisterIndicator Failed(TargetId=%d, indication_id=0x%x)", nOriginID, status_indication_id);
		return WMX_ST_FAIL;
	}
	//Perform actions according to size of list and subscriber removal

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NDnSAgent_UnRegisterIndicator(OUT)");
	return WMX_ST_OK;	
}


// Returns TRUE if the NSP is valid for connection
BOOL IsValidNSP(wmx_NSPid_t nspID)
{
	//ProvisionedNsp_t provisionedNsp;	
	//wmx_Status_t status;
	
	if (L4db_GetNspCategory(nspID) == Home)
	{
		return TRUE;
	}

	return FALSE;

	/*status = L4db_GetProvisionedNsp(nspID, &provisionedNsp);
	if (status != WMX_ST_OK ||
		provisionedNsp.fIsAllocated == FALSE)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}*/
}

// Returns TRUE if a valid NSP was found in the list, and the IN OUT parameter validNSP holds its value.
BOOL GetValidNSP(wmx_pNSP_t validNSP, UINT32 numOfNSPs, wmx_pNSP_t pNSPs)
{
	UINT32 i;

	for ( i = 0; i < numOfNSPs; i++)
	{
		if ( pNSPs[i].numOfNspIDs > 0 && TRUE == IsValidNSP(pNSPs[i].nspIDs[0]) )
		{
			OSAL_memcpy_s(validNSP, sizeof(wmx_NSP_t), &(pNSPs[i]), sizeof(wmx_NSP_t));
			
			return TRUE;
		}
	}

	return FALSE;
}

// The function fill the wmx_NSP_t struct from the provisioned and discovered information
wmx_Status_t GetNspStruct(wmx_NSPid_t nspId, wmx_pNSP_t pNSP)
{
	pProvisionedNsp_t provisionedNsp;
	char provisionedName[WMX_NSP_NAME_MAX_SIZE];
	char discoveredName[WMX_NSP_NAME_MAX_SIZE];
	UINT32 provisionedNameSize = WMX_NSP_NAME_MAX_SIZE;
	UINT32 discoveredNameSize = WMX_NSP_NAME_MAX_SIZE;
	wmx_Status_t status;

	provisionedName[0] = '\0';
	discoveredName[0] = '\0';	

	provisionedNsp = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));
	if (provisionedNsp == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return WMX_ST_FAIL;
	}


	if (L4db_GetProvisionedNsp(nspId, provisionedNsp) != WMX_ST_OK)
	{
		status = L4db_GetNspName(nspId, (char*)provisionedName, &provisionedNameSize, (char*)discoveredName, &discoveredNameSize);	
		if (discoveredNameSize > 0)
		{
			OSAL_strcpy_s(pNSP->nspName, WMX_NSP_NAME_MAX_SIZE, (const char*)discoveredName);
		}

		// TODO:Ely ???????  Add support to the current preferred NSP name

		pNSP->nspIDs[0] = nspId;		
		pNSP->numOfNspIDs = 1;
	}
	else // Copy the provisioned result to the wmx_NSP_t
	{
		L4db_ConvertNspToInterface(provisionedNsp, pNSP);
	}	

	free(provisionedNsp);

	return WMX_ST_OK;
}

// Return TRUE if preferred scan is used and current preferred NSP is set
BOOL UseCurrentPreferredScan()
{
	wmx_NSPid_t currentPreferredNSP;

	if ( (WMX_ST_OK == L4db_GetCurrentPreferredNsp(&currentPreferredNSP)) &&
		 (currentPreferredNSP != L4DB_INVALID_INDEX) &&
		 (g_ndnsContext.currentScanType == SCAN_TYPE_PREFERRED) )
	{
		return TRUE;
	}

	return FALSE;
}

/// <summary>
/// Checks if two NAP IDs are equal
/// </summary>
BOOL IsBsIdEqual(wmx_BSid_t bsId1,wmx_BSid_t bsId2, wmx_BsIdType_t bsIdType)
{
	BOOL rc = FALSE;

	if(bsId1 && bsId2)
	{
		switch(bsIdType)
		{
		case COMPRESSED_BSID:		
		case COMPRESSED_NAP:
			rc = (bsId1[2] == bsId2[2]);
			break;
		case FULL_BSID:		   
		case FULL_NAP:		  
		default:
			rc = ((bsId1[0] == bsId2[0]) &&
				(bsId1[1] == bsId2[1])&&
				(bsId1[2] == bsId2[2]) &&
				(bsId1[3] == bsId2[3]) &&
				(bsId1[4] == bsId2[4])&&
				(bsId1[5] == bsId2[5]));
			break;
		}
	}
	return rc;
}

BOOL GetChannelIdsByThreshold(L4C_LinkGrade linkGrade, wmx_pNAP_t pNAP, wmx_pChannelIds_t pChIds, UINT32 *numOfChIds)
{
	UINT32 i, tempNumOfChIds = 0;
	wmx_ChannelID_t tempChIds[MAX_CHANNEL_INFO_ID_SIZE];
	
	// for each NAP - iterate through all its channelIds
	for (i = 0; i < pNAP->numChannels && tempNumOfChIds < *numOfChIds; ++i)
	{			
		if (pNAP->linkGrade[i] == linkGrade)
		{	// add channels with the requested link grade
			tempChIds[tempNumOfChIds++] = pNAP->channelIdList[i];			
		}
	}
	*numOfChIds = tempNumOfChIds;

	// in case there isn't enough space in the supplied buffer - return an error
	if (tempNumOfChIds == *numOfChIds && i < pNAP->numChannels)
	{
		return FALSE;	
	}

	// copy the temp list of the channel ids to the returned list
	OSAL_memcpy_s(pChIds, *numOfChIds, tempChIds, *numOfChIds);
	return TRUE;
}

BOOL NAPs2NSPs(UINT32 numOfNAP, wmx_pNAP_t pNAP, UINT32 *numOfNSPs, wmx_NSP_t nsps[WMX_NSPS_MAX_NUM],
			   wmx_BSid_t bsIds[WMX_NSPS_MAX_NUM], wmx_BsIdType_t bsIdsTypes[WMX_NSPS_MAX_NUM],
			   UINT32 *numOfNapsWithNoNSP, wmx_pNAP_t napsWithNoNSP, BOOL bUseUnderThreshold)
{
	UINT32 i, j, k, l;
	wmx_NSPid_t tmpNspIds[(WMX_NSPS_MAX_NUM + MAX_NUM_OF_DISCOVERED_NSPS)];
	UINT32 tmpNumOfNspIds;
	BOOL add;
	errno_t err;
	UINT32 maxNumOfResults = *numOfNSPs;
	wmx_NSP_t nsp;
	wmx_Status_t rc;
	UINT32 tmpNumOfNapsWithNoNSP = 0;
	BOOL bHasGoodChannels;
	BOOL result = TRUE;
	UINT32  showUnknownNSPs = 0;

	*numOfNSPs = 0;	

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NAPs2NSPs (IN) - #NAPs=%d", numOfNAP);
	// Run over the NAPs and add the NSPs of each NAP.

	for ( i = 0; i < numOfNAP; i++)
	{
		tmpNumOfNspIds = WMX_NSPS_MAX_NUM;
		bHasGoodChannels = FALSE;

		// If bUseUnderThreshold == FALSE check if there is a need to convert the current NAP
		if (bUseUnderThreshold == FALSE)
		{		
			// Look for a channel with a good signal
			for (l = 0; l < pNAP[i].numChannels; l++)
			{
				if (pNAP[i].linkGrade[l] == LinkGrade_AboveThr)
				{
					bHasGoodChannels = TRUE;
					break;
				}
			}

			if (bHasGoodChannels == FALSE)
			{
				continue;
			}
		}

		rc = L4db_ConvertNap2Nsps(pNAP[i].bsCriteria.bsID,
			bsIdsTypes[i], tmpNspIds, &tmpNumOfNspIds);

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NAP No. %d converted to %d NSPs", i, tmpNumOfNspIds);
		L4Configurations_getShowUnkownNSPs(&showUnknownNSPs);
		// Get the NSPs of a NAP
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NAPs2NSPs : L4db_ConvertNap2Nsps - #NAPs=%d pNAP[i].bsCriteria.bsID=[%d], tmpNumOfNspIds=[%d]", numOfNAP, pNAP[i].bsCriteria.bsID, tmpNumOfNspIds);
		if ((tmpNumOfNspIds == 0 && showUnknownNSPs) || tmpNumOfNspIds > 0)
		{
		if ( tmpNumOfNspIds == 0)
		{	
			if (*numOfNapsWithNoNSP > tmpNumOfNapsWithNoNSP)
			{
				napsWithNoNSP[tmpNumOfNapsWithNoNSP] = pNAP[i];
				tmpNumOfNapsWithNoNSP++;
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Added 1 unknown NSP");
			}
			else
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "NAPs2NSPs buffer too small");
			}
		}

		if(rc != WMX_ST_OK)
		{
			continue;
		}

		// Run over the NSPs of the NAP and add the new ones
		for( k = 0; k < tmpNumOfNspIds; k++ )
		{
			add = TRUE;
			// Check if the NSP exists, run over the found NSPs
			for( j = 0; j < *numOfNSPs; j++ )
			{				
				// Check the list of IDs. There is an assumption that the same ID doesn't appear in two different NSPs
				for (l = 0; l < nsps[j].numOfNspIDs; l++)
				{
					if( nsps[j].nspIDs[l] == tmpNspIds[k] )
					{
						add = FALSE;
						break;
					}
				}
			}
			if( add )
			{
				// Get the wmx_NSP_t struct out of the NSP ID
				OSAL_ZeroMemory(&nsp, sizeof(wmx_NSP_t));
				if ( GetNspStruct(tmpNspIds[k], &nsp) != WMX_ST_OK) 
				{	
					continue;
				}

				nsp.bestRssi = pNAP[i].bestRssi;				
				nsp.bestCINR = pNAP[i].bestCINR;
				nsp.linkQuality = pNAP[i].bestLinkQuality;

				err = OSAL_memcpy_s( &(nsps[*numOfNSPs]), sizeof(wmx_NSP_t), &nsp, sizeof(wmx_NSP_t) );
				if( err != 0 )
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "memcpy failed");					
					result = FALSE;
					goto Finalize;
				}
				OSAL_memcpy_s(bsIds[*numOfNSPs], sizeof(wmx_BSid_t), pNAP[i].bsCriteria.bsID, sizeof(wmx_BSid_t));
				bsIdsTypes[*numOfNSPs] = pNAP[i].bsIDType;
				(*numOfNSPs)++;
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Added 1 NSP. NSP ID=%d", tmpNspIds[k]);

				if (maxNumOfResults <= *numOfNSPs) // the nsps array is full so finish
				{					
					 goto Finalize;
				}
			}
		}
	}
	}
	
Finalize:
	*numOfNapsWithNoNSP = tmpNumOfNapsWithNoNSP;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "NAPs2NSPs (OUT)");

	return TRUE;
}

int GetNapId(wmx_BSid_t bsId)
{
	int napId = 0;

	napId |= bsId[0];
	napId <<= 8;
	napId |= bsId[1];
	napId <<= 8;
	napId |= bsId[2];

	return napId;
}

// Translate the BsID mask to the correct format of the BsID
wmx_BsIdType_t GetBsIdType(wmx_BSidMask_t mask)
{
	UINT32 fullFlag = 0, napFlag = 0;  

	// convert the "compressed" flag to int
	fullFlag |= mask[0];
	fullFlag <<= 8;
	fullFlag |= mask[1];
	fullFlag <<= 8;
	fullFlag |= mask[2];
	// convert the inner type of the BsID to int
	napFlag |= mask[3];
	napFlag <<= 8;
	napFlag |= mask[4];
	napFlag <<= 8;
	napFlag |= mask[5];
	
	if (fullFlag == 0xFFFFFF) // full BsID
	{
		if (napFlag == 0xFFFFFF) // full BsID
		{
			return FULL_BSID;
		}
		else // only NAP part
		{
			return FULL_NAP;
		}
	}
	else // compressed BsID
	{
		if (napFlag == 0xFF) // compressed BsID
		{
			return COMPRESSED_BSID;
		}
		else // only NAP part
		{
			return COMPRESSED_NAP;
		}
	}
}

// Convert NAP to bs criteria
BOOL NAP2BSCriteria( wmx_NAPid_t napId, wmx_BsIdType_t bsIdType, wmx_pBSSelectionCriteria_t bsCriteria )
{
	errno_t err;

	OSAL_ZeroMemory(bsCriteria->bsID, sizeof(bsCriteria->bsID));
	err = OSAL_memcpy_s( bsCriteria->bsID, sizeof(bsCriteria->bsID), napId, sizeof(wmx_NAPid_t) );
	if( err != 0 )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "memcpy failed");
		return FALSE;
	}
	switch(bsIdType)
	{		
		case COMPRESSED_BSID:
		case COMPRESSED_NAP:
			bsCriteria->bsIDmask[0] = 0;
			bsCriteria->bsIDmask[1] = 0;
			break;
		case FULL_BSID:
		case FULL_NAP:
		default: // the default is FULL NAP ID
			bsCriteria->bsIDmask[0] = 0xFF;
			bsCriteria->bsIDmask[1] = 0xFF;
			break;

	}	
	bsCriteria->bsIDmask[2] = 0xFF;
	// we use only the NAP part (MSB) of the BSID for connection
	bsCriteria->bsIDmask[3] = 0; //0x80;
	bsCriteria->bsIDmask[4] = 0;
	bsCriteria->bsIDmask[5] = 0;

	return TRUE;
}

// The function gets two nsps and returns TRUE if they are the same, FALSE otherwise
BOOL NDnSAgent_IsNSPsEqual(wmx_pNSP_t pNsp1, wmx_pNSP_t pNsp2)
{	
	UINT32 i, j;

	for (i=0; i < pNsp1->numOfNspIDs; i++)
	{
		for (j=0; j < pNsp2->numOfNspIDs; j++)
		{
			if (pNsp1->nspIDs[i] == pNsp2->nspIDs[j])
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

// The function gets an nsp and NspID and returns TRUE if ID belongs to the NSP
BOOL NDnSAgent_IsNspIdInNSP(wmx_NSPid_t nspId1, wmx_pNSP_t pNsp2)
{	
	UINT32 i;

	for (i=0; i < pNsp2->numOfNspIDs; i++)
	{
		if (nspId1 == pNsp2->nspIDs[i])
		{
			return TRUE;
		}	
	}

	return FALSE;
}

BOOL NDnSAgent_BuildFumoPath(char* src, char* dest, UINT32 destLen)
{
	wmx_Status_t st; 
	size_t pathLen;
	size_t srcLen;

	// Read FUMO node path from l4db
	FumoInternalParams_t fumoInternalParams;
	
	st = L4db_GetFumoInternalInfo(&fumoInternalParams);

	if (st != WMX_ST_OK)
	{
		return FALSE;
	}
	
	pathLen = OSAL_strnlen(fumoInternalParams.fumoNodePath, MAX_APDO_PATH);
	srcLen = OSAL_strnlen(src, MAX_PATH);
	
	if((pathLen + srcLen) < destLen)
	{
		memcpy(dest, fumoInternalParams.fumoNodePath,  pathLen);	
		memcpy(dest + pathLen, src, srcLen);			
	
		dest[pathLen + srcLen] = '\0';
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

static const char CONST_hexDigits[]	= "0123456789ABCDEF";

void NDnSAgent_HexEncode(const UINT8 *binPtr, char *hexPtr, UINT32 binLength)
{
	const UINT8 *bp;

	for (bp = binPtr; bp < &binPtr[binLength]; bp++)
	{
		*hexPtr++ = CONST_hexDigits[*bp >> 4];
		*hexPtr++ = CONST_hexDigits[*bp & 0xF];
	}

	*hexPtr++ = '\0';
}

BOOL NDnSAgent_HexDecode(const char *hexPtr, UINT8 *binPtr, UINT32 length)
{
	const char *cp = hexPtr;
	UINT8 nbl;
	UINT32 i;

	if (length & 0x1)
	  return FALSE;

	for (i = 0; i < length; i++, cp++)
	{
		if (*cp >= '0' && *cp <= '9')
			nbl = (UINT8)(*cp - '0');
		else if (*cp >= 'A' && *cp <= 'F')
			nbl = (UINT8)(*cp - 'A' + 10);
		else if (*cp >= 'a' && *cp <= 'f')
			nbl = (UINT8)(*cp - 'a' + 10);
		else		
			return FALSE;

		if ((i & 0x1) == 0)
			*binPtr = (UINT8)(nbl << 4);
		else
			*binPtr++ |= nbl;
	}

	*binPtr++ = '\0';

	return TRUE;
}

// The function gets the driver mode and saves the L4DB to the disk
void SaveToDB()
{
	char path[MAX_REGISTRY_ANSWER];

	if (RunWithDSim == FALSE)
	{

			OSAL_BuildFullPath(WiMAX_ENC_DB, path, MAX_REGISTRY_ANSWER);        
	} 
	else
	{
			OSAL_BuildFullPath(NDNS_DSIM_ENC_CONFIG_FILE, path, MAX_REGISTRY_ANSWER);
 	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "call L4db_SaveToFile from SaveToDB");
	L4db_SaveToFile(path);
}

// function converts a coex priority to a coex state
wmx_CoexState_t NDnSAgent_CoexPrio2CoexState (wmx_CoexPriority_t coexPrio)
{
	switch(coexPrio)
	{
	case COEX_PRIORITY_SCAN_LOW:
		return COEX_STATE_SCAN_LOW;
		break;
	case COEX_PRIORITY_SCAN_HIGH:
		return COEX_STATE_SCAN_HIGH;
		break;
	case COEX_PRIORITY_CONNECT_LOW:
	case COEX_PRIORITY_CONNECT_HIGH:
		return COEX_STATE_CONNECTING;
	    break;
	default:
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "NDnSAgent_CoexPrio2CoexState: Coexistence priority is unknown");
		return COEX_PRIORITY_SCAN_LOW;
	}
}

