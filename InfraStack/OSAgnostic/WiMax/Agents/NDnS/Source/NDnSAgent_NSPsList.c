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
#include "NDnSAgent.h"
#include "NDnS_L4Scanner.h"
#include "NDnSAgent_L4P.h"
#include "NDnSAgent_APDO.h"
#include "NDnSAgent_DB_if.h"

#include "CommonServices.h"
#include "WrappersCommon.h"
#include "L5OpCodes.h"		

#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Nds_Utils.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Sup_Defines.h"
#include "wmxSDK_Msc_2.h"

#include "Act.h"
#include "wimax_osal_config_controler.h"

#include "NDnSAgent_Utils.h"
#include "XmlParser.h"

#define SHARED_NAP_LOCATION 2
#define SINGLE_NSP_LOCATION 1

// Declarations
void SortAvailableNspList();
wmx_Status_t GetAvailableNspsList(UINT32 *numOfNSPs, wmx_pNSP_t nsps, BOOL isFiltered);
int GetNspIdentifier(wmx_BSid_t bsId);
void CreateFakeNSPsFromNaps(UINT32 numOfNaps, wmx_pNAP_t naps, UINT32 *numOfNsps, wmx_pNSP_t nsps);
void CreateFakeAvailableNSPsFromNaps(UINT32 numOfNaps, wmx_pNAP_t naps, UINT32 *numOfNsps, wmx_pAvailableNSP_t nsps);
BOOL CheckIfNspInAvailableList(wmx_NSPid_t nspId);
BOOL IsNspInAvailableNspsList(wmx_NSPid_t nspId);
wmx_Status_t AgeAvailableNspsList();


wmx_Status_t AddNSPToAvailableNSPsListInternal(wmx_pNSP_t nsp, wmx_BSid_t bsId, wmx_BsIdType_t bsIdType)
{
	UINT32 i;
	wmx_Status_t status = WMX_ST_OK;
	UINT32 numOfNSPs;
	wmx_AvailableNSP_t availableNSP;
	NspCategory_t nspCategory;

	// Validate the arguments
	if (nsp == NULL || nsp->numOfNspIDs <= 0)
	{
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	numOfNSPs = g_ndnsContext.availableNSPsList.numOfAvailableNSPs;

	// Find the nsp in the old available NSPs list
	for (i=0; i < numOfNSPs; i++)
	{
		if (NDnSAgent_IsNspIdInNSP(g_ndnsContext.availableNSPsList.availableNSPs[i].nspId, nsp) == TRUE)
		{
			// Update the available NSP only if the CINR is better or the existing one is not from the last scan cycle
			if (g_ndnsContext.availableNSPsList.availableNSPs[i].bestCINR < nsp->bestCINR ||
				(g_ndnsContext.availableNSPsList.availableNSPs[i].bestCINR == nsp->bestCINR &&
				g_ndnsContext.availableNSPsList.availableNSPs[i].bestRssi < nsp->bestRssi) ||
				g_ndnsContext.availableNSPsList.availableNSPs[i].agingStatus != AgingStatus_New)
			{
				// Update the available NSP's node
				g_ndnsContext.availableNSPsList.availableNSPs[i].nspId = nsp->nspIDs[0];
				g_ndnsContext.availableNSPsList.availableNSPs[i].detectionTime = OSAL_timeGetTime();
				g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex = 0; // Use UpdatePreferredIndex to assign the real values to all the available NSPs		
				OSAL_memcpy_s(g_ndnsContext.availableNSPsList.availableNSPs[i].bsId, sizeof(wmx_BSid_t), bsId, sizeof(wmx_BSid_t));
				g_ndnsContext.availableNSPsList.availableNSPs[i].bsIdType = bsIdType;
				g_ndnsContext.availableNSPsList.availableNSPs[i].bestRssi= nsp->bestRssi;
				g_ndnsContext.availableNSPsList.availableNSPs[i].bestCINR = nsp->bestCINR;
				g_ndnsContext.availableNSPsList.availableNSPs[i].linkQuality = nsp->linkQuality;
				g_ndnsContext.availableNSPsList.availableNSPs[i].agingStatus = AgingStatus_New;
			}

			break;
		}		
	}

	// If the NSP doesn't exist in the available NSPs list
	if (i == numOfNSPs)
	{		
		availableNSP.agingStatus = AgingStatus_New;
		availableNSP.nspId = nsp->nspIDs[0];
		availableNSP.detectionTime = OSAL_timeGetTime();
		availableNSP.preferredListIndex = 0; // Use UpdatePreferredIndex to assign the real values to all the available NSPs		
		OSAL_memcpy_s(availableNSP.bsId, sizeof(wmx_BSid_t), bsId, sizeof(wmx_BSid_t));
		availableNSP.bsIdType = bsIdType;
		availableNSP.bestRssi = nsp->bestRssi;
		availableNSP.bestCINR = nsp->bestCINR;
		availableNSP.linkQuality = nsp->linkQuality;

		nspCategory = L4db_GetNspCategory(availableNSP.nspId);
		
		if (nspCategory == Home)
		{
			availableNSP.connectType = ConnectReason_Home;
		}
		else
		{
			availableNSP.connectType = ConnectReason_Activation;
		}
		
		g_ndnsContext.availableNSPsList.availableNSPs[g_ndnsContext.availableNSPsList.numOfAvailableNSPs] = availableNSP;
		g_ndnsContext.availableNSPsList.numOfAvailableNSPs++;
	}

Finalize:
	return status;
}


wmx_Status_t AddMultipleNSPsToAvailableNSPsList(UINT32 numOfNsps, wmx_pNSP_t nsps, wmx_BSid_t *bsIds, wmx_BsIdType_t *bsIdsTypes)
{
	wmx_Status_t st;
	UINT32 i;
	
	if (numOfNsps <= 0)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}
	
	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	for (i=0; i < numOfNsps; i++)
	{
		st = AddNSPToAvailableNSPsListInternal(&nsps[i], bsIds[i], bsIdsTypes[i]);

		if (st != WMX_ST_OK)
		{			
			OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
			return st;
		}
	}

	SortAvailableNspList();

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
	return WMX_ST_OK;
}

// The function adds an NSP to the available NSPs list and update the aging property accordingly
wmx_Status_t AddFakeNSPToAvailableNSPsListInternal(wmx_pAvailableNSP_t nsp)
{
	UINT32 i;
	wmx_Status_t status = WMX_ST_OK;
	UINT32 numOfNSPs;
	wmx_AvailableNSP_t availableNSP;
	NspCategory_t nspCategory;

	// Validate the arguments
	if (nsp == NULL || nsp->nspId == L4DB_INVALID_INDEX)
	{
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	numOfNSPs = g_ndnsContext.availableNSPsList.numOfAvailableNSPs;

	// Find the nsp in the old available NSPs list
	for (i=0; i < numOfNSPs; i++)
	{
		if (g_ndnsContext.availableNSPsList.availableNSPs[i].nspId == nsp->nspId)
		{
			if (g_ndnsContext.availableNSPsList.availableNSPs[i].bestCINR < nsp->bestCINR ||
				(g_ndnsContext.availableNSPsList.availableNSPs[i].bestCINR == nsp->bestCINR &&
				g_ndnsContext.availableNSPsList.availableNSPs[i].bestRssi < nsp->bestRssi) ||
				g_ndnsContext.availableNSPsList.availableNSPs[i].agingStatus != AgingStatus_New)
			{
				OSAL_memcpy_s(g_ndnsContext.availableNSPsList.availableNSPs[i].bsId, sizeof(wmx_BSid_t), nsp->bsId, sizeof(wmx_BSid_t));
				g_ndnsContext.availableNSPsList.availableNSPs[i].bsIdType = nsp->bsIdType;
				// Update the best CINR and RSII
				g_ndnsContext.availableNSPsList.availableNSPs[i].bestRssi = nsp->bestRssi;
				g_ndnsContext.availableNSPsList.availableNSPs[i].bestCINR = nsp->bestCINR;
				g_ndnsContext.availableNSPsList.availableNSPs[i].linkQuality = nsp->linkQuality;

				// Update the NSP's aging status
				g_ndnsContext.availableNSPsList.availableNSPs[i].agingStatus = AgingStatus_New;
			}
			break;
		}		
	}

	// If the NSP doesn't exist in the available NSPs list
	if (i == numOfNSPs)
	{		
		availableNSP.agingStatus = AgingStatus_New;
		availableNSP.nspId = nsp->nspId;
		availableNSP.detectionTime = OSAL_timeGetTime();
		availableNSP.preferredListIndex = 0; // Use UpdatePreferredIndex to assign the real values to all the available NSPs		
		OSAL_memcpy_s(availableNSP.bsId, sizeof(wmx_BSid_t), nsp->bsId, sizeof(wmx_BSid_t));
		availableNSP.bsIdType = nsp->bsIdType;
		availableNSP.bestRssi = nsp->bestRssi;
		availableNSP.bestCINR = nsp->bestCINR;
		availableNSP.linkQuality = nsp->linkQuality;

		nspCategory = L4db_GetNspCategory(availableNSP.nspId);
		
		if (nspCategory == Home)
		{
			availableNSP.connectType = ConnectReason_Home;
		}
		else
		{
			availableNSP.connectType = ConnectReason_Activation;
		}
		
		g_ndnsContext.availableNSPsList.availableNSPs[g_ndnsContext.availableNSPsList.numOfAvailableNSPs] = availableNSP;
		g_ndnsContext.availableNSPsList.numOfAvailableNSPs++;
	}

Finalize:
	return status;
}

wmx_Status_t AddSingleFakeNSPToAvailableNSPsList(wmx_pAvailableNSP_t nsp)
{
	wmx_Status_t st;
	
	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	st = AddFakeNSPToAvailableNSPsListInternal(nsp);

	if (st != WMX_ST_OK)
	{
		OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
		return st;
	}

	SortAvailableNspList();

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
	return WMX_ST_OK;
}

wmx_Status_t AddMultipleFakeNSPsToAvailableNSPsList(UINT32 numOfNsps, wmx_pAvailableNSP_t nsp)
{
	wmx_Status_t st;
	UINT32 i;
	
	if (numOfNsps <= 0)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}
	
	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	for (i=0; i < numOfNsps; i++)
	{
		st = AddFakeNSPToAvailableNSPsListInternal(&nsp[i]);

		if (st != WMX_ST_OK)
		{			
			OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
			return st;
		}
	}

	SortAvailableNspList();

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
	return WMX_ST_OK;
}

wmx_Status_t ClearAvailableNSPsList()
{
	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
	g_ndnsContext.availableNSPsList.numOfAvailableNSPs = 0;
	L4db_ResetLastDetectedNaps();
	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Available NSPs list cleared");

	return WMX_ST_OK;
}

// Update the location of the available NSPs in the preferred list
wmx_Status_t UpdatePreferredIndex()
{
	wmx_PreferredNsp preferredList[WMX_NSP_IDS_MAX_NUM];
	UINT32 preferredListLength = WMX_NSP_IDS_MAX_NUM;
	wmx_Status_t status;
	UINT32 i, j, k;
	NspCategory_t category;
	BOOL bFinish= FALSE;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex(IN). ");
	status = L4P_GetPreferredNspList(preferredList, &preferredListLength);
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "UpdatePreferredIndex error in L4P_GetPreferredNspList status=%d", status);
		return status;
	}

	// Run over the available list
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex. numOfAvailableNSPs=%d",g_ndnsContext.availableNSPsList.numOfAvailableNSPs);
	for (i=0; i < g_ndnsContext.availableNSPsList.numOfAvailableNSPs; i++)
	{		
		category = L4db_GetNspCategory(g_ndnsContext.availableNSPsList.availableNSPs[i].nspId);

		// locate the provisioned NSPs first in the available NSPs sorting, second locate the NSPs that corelate 
		// to a NAP and finally the NSPs that use shared NAP. (use the NSP Identifier Flag)
		if (category == NotProvisioned)
		{
			if (GetNspIdentifier(g_ndnsContext.availableNSPsList.availableNSPs[i].bsId) == 1)
			{
				g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex = WMX_NSP_IDS_MAX_NUM + SHARED_NAP_LOCATION;
			}
			else
			{
				g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex = WMX_NSP_IDS_MAX_NUM + SINGLE_NSP_LOCATION;
			}
		}
		else
		{
			g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex = WMX_NSP_IDS_MAX_NUM;  // default value
		}

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex. g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex=%d",g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex. preferredListLength=%d",preferredListLength);
		// Run over the preferred list
		for (j=0; !bFinish && j < preferredListLength; j++)
		{
			// Run over the IDs of the preferred nsp
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex. preferredList[%d].nspIdsSize=%d",j, preferredList[j].nspIdsSize);
			for (k=0; !bFinish && k < preferredList[j].nspIdsSize; k++)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex. preferredList[%d].nspIds[%d]=%d , availableNSPsList.availableNSPs[i].nspId=%d",j,k,preferredList[j].nspIds[k],g_ndnsContext.availableNSPsList.availableNSPs[i].nspId);
				if (preferredList[j].nspIds[k] == g_ndnsContext.availableNSPsList.availableNSPs[i].nspId)
				{
					// The NSP was found in the preferred list, update the index of its location
					g_ndnsContext.availableNSPsList.availableNSPs[i].preferredListIndex = j;
					
					// exit from the two for loops
					//k = preferredList[j].nspIdsSize;
					//j = preferredListLength;
					bFinish = TRUE;
				}
			}
		}
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "UpdatePreferredIndex(OUT). status=%d",status);
	return status;
}

// Returns TRUE if the first item is bigger; FALSE, otherwise
BOOL IsFirstItemBigger(wmx_pAvailableNSP_t pItem1, wmx_pAvailableNSP_t pItem2)
{
	if ((pItem1->preferredListIndex < pItem2->preferredListIndex) ||
		((pItem1->preferredListIndex == pItem2->preferredListIndex) && (pItem1->detectionTime < pItem2->detectionTime)))
	{
		return TRUE;
	}

	return FALSE;
}


// Get the nsp info. In case the nsp is only 16g discovered, fill only some details.
// In case the NSP is in the Available NSPs list solely, get the details from there.
wmx_Status_t GetNspInfo(wmx_NSPid_t nspId, wmx_pNSP_t pNSP)
{	
	pProvisionedNsp_t provisionedNsp;
	//wmx_NSPid_t recentNspId;
	wmx_AvailableNSP_t availableNSP;
	wmx_Status_t status = WMX_ST_FAIL;
	char provisionedName[WMX_NSP_NAME_MAX_SIZE];
	char discoveredName[WMX_NSP_NAME_MAX_SIZE];
	UINT32 provisionedNameSize = WMX_NSP_NAME_MAX_SIZE;
	UINT32 discoveredNameSize = WMX_NSP_NAME_MAX_SIZE;	
	errno_t err;
	BOOL bInAvailableNsps;
	Profile_t unprovisioned;

	provisionedNsp = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));
	if (provisionedNsp == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return WMX_ST_FAIL;
	}


	// Call the function that fetches the data from the local DB
	status = L4db_GetProvisionedNsp(nspId, provisionedNsp);
	
	switch (status)
	{
		case WMX_ST_OK:
			L4db_ConvertNspToInterface(provisionedNsp, pNSP);
			break;

		case WMX_ST_DATA_UNAVAILABLE:
			// The NSP is not provisioned, check if it is 16g discovered
			L4db_GetNspName(nspId, provisionedName, &provisionedNameSize, discoveredName, &discoveredNameSize);

			// The NSP is discovered
			if (discoveredNameSize > 0)
			{
				err = OSAL_strcpy_s(pNSP->nspName, WMX_NSP_NAME_MAX_SIZE, discoveredName);
				if (err != 0)
				{
					goto Finalize;
				}

				pNSP->nspIDs[0] = nspId;
				pNSP->numOfNspIDs = 1;
				pNSP->activated = FALSE;
				pNSP->isHomeNSP = FALSE;
				pNSP->nspRealm[0] = '\0';
				pNSP->numOfSubscribers = 0;

				//L4db_ConvertNspToInterface(provisionedNsp, pNSP);
			}	
			else  // The NSP is not discovered, check if the NSP is in the available NSPs list
			{	  // or if it was the last connected one
				bInAvailableNsps = IsNspInAvailableNspsList(nspId);			

				if ((bInAvailableNsps == TRUE) ||
					(WMX_ST_OK == L4db_GetUnprovisionedProfilePerNspID((wmx_NSPid_t)nspId, &unprovisioned )))
				{
					pNSP->activated = FALSE;
					pNSP->nspIDs[0] = nspId;
					pNSP->numOfNspIDs = 1;				
					pNSP->isHomeNSP = FALSE;
					pNSP->nspRealm[0] = '\0';

					OSAL_sprintf_s((char*)(pNSP->nspName), WMX_NSP_NAME_MAX_SIZE, "Unrecognized Operator � ID: %u", nspId);				
				}
			}
			break;
		default:
			goto Finalize;
			break;
	}
	
	// if this NSP is in the available NSPs list, fetch its current best RSSI and best CINR values
	if (GetAvailableNspNode(nspId, &availableNSP))
	{
		pNSP->bestRssi = availableNSP.bestRssi;
		pNSP->bestCINR = availableNSP.bestCINR;
		pNSP->linkQuality = availableNSP.linkQuality;
	}

	status = WMX_ST_OK;

Finalize:
	free(provisionedNsp);
	return status;
}

// The function merges between two lists. An assumption is made that the start of list 2 comes 
// immediately after the end of list 1
void MergeLists(int list1Start, int list1End,
				int list2Start, int list2End)
{
	int firstListCursor, secondListCursor, currCursor;
	wmx_AvailableNSP_t tmpAvailableNSP[WMX_NSP_IDS_MAX_NUM];

	firstListCursor = list1Start;
	secondListCursor = list2Start;
	currCursor = 0;

	// Merge the two lists
	while (firstListCursor <= list1End && secondListCursor <= list2End)
	{
		if (IsFirstItemBigger(&(g_ndnsContext.availableNSPsList.availableNSPs[firstListCursor]),
								&(g_ndnsContext.availableNSPsList.availableNSPs[secondListCursor])))
		{
			tmpAvailableNSP[currCursor] = g_ndnsContext.availableNSPsList.availableNSPs[firstListCursor];
			firstListCursor++;
		}
		else
		{
			tmpAvailableNSP[currCursor] = g_ndnsContext.availableNSPsList.availableNSPs[secondListCursor];
			secondListCursor++;
		}

		currCursor++;
	}

	// Copy the rest of the unfinished list
	if (firstListCursor <= list1End)
	{
		OSAL_memcpy_s(&(tmpAvailableNSP[currCursor]), 
				sizeof(wmx_AvailableNSP_t) * (MAX_NUM_OF_DISCOVERED_NSPS - currCursor),
				&(g_ndnsContext.availableNSPsList.availableNSPs[firstListCursor]),
				sizeof(wmx_AvailableNSP_t) * (list1End - firstListCursor + 1));							
	}
	else // finish copying the second list
	{
		OSAL_memcpy_s(&(tmpAvailableNSP[currCursor]), 
				sizeof(wmx_AvailableNSP_t) * (MAX_NUM_OF_DISCOVERED_NSPS - currCursor),
				&(g_ndnsContext.availableNSPsList.availableNSPs[secondListCursor]),
				sizeof(wmx_AvailableNSP_t) * (list2End - secondListCursor + 1));							
	}

	// Copy the tmp list to the Available NSPs list
	OSAL_memcpy_s(&(g_ndnsContext.availableNSPsList.availableNSPs[list1Start]), 
			sizeof(wmx_AvailableNSP_t) * (MAX_NUM_OF_DISCOVERED_NSPS - currCursor),
			tmpAvailableNSP,
			sizeof(wmx_AvailableNSP_t) * (list2End - list1Start + 1));
}

void SortAvailableNspListByIndices(int startInd, int endInd)
{
	if (endInd - startInd > 2)
	{
		SortAvailableNspListByIndices(startInd, (int)(startInd + ((endInd - startInd)/2)));
		SortAvailableNspListByIndices((int)(startInd + ((endInd - startInd)/2) + 1), endInd);		
	}

	// Make sure that we have more then one item
	if (endInd > startInd)
	{
		MergeLists(startInd, (int)(startInd + (endInd - startInd)/2), (int)(startInd + (endInd - startInd)/2) + 1, endInd);
	}
}

void SortAvailableNspList()
{
	// Need to have the correct values for the sort
	UpdatePreferredIndex();

	SortAvailableNspListByIndices(0, g_ndnsContext.availableNSPsList.numOfAvailableNSPs - 1);
}

// The function runs over the available NSPs list, erase the NSPs that are old and turn the new ones to old.
wmx_Status_t AgeAvailableNspsList()
{
	UINT32 i, j;
	wmx_AvailableNSP_t tmpAvailableNSP[WMX_NSP_IDS_MAX_NUM];
	UINT32 currentCursor = 0;
	L4db_Nap_t naps[WMX_NAPS_MAX_NUM];
	UINT32 napsSize = WMX_NAPS_MAX_NUM;
	wmx_Status_t tmpStatus, status = WMX_ST_OK;
	wmx_pAvailableNSP_t currentNSP;	

	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	OSAL_memcpy_s(	tmpAvailableNSP, 
				sizeof(wmx_AvailableNSP_t) * WMX_NSP_IDS_MAX_NUM,
				g_ndnsContext.availableNSPsList.availableNSPs, 
				sizeof(wmx_AvailableNSP_t) *g_ndnsContext.availableNSPsList.numOfAvailableNSPs);
				
	/*TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "<---L4db_PrintDiscoveredNAPsList - AgeAvailableNspsList before L4db_DeleteDuplicatedChannelsInAllDetectedChannels after save to db -- >");
	L4db_PrintDiscoveredNAPsList();*/
	L4db_DeleteDuplicatedChannelsInAllDetectedChannels(TRUE);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "<---L4db_PrintDiscoveredNAPsList - AgeAvailableNspsList after L4db_DeleteDuplicatedChannelsInAllDetectedChannels after save to db -- >");
	L4db_PrintDiscoveredNAPsList();

	L4db_DecreaseTtlForAllDetectedChannels();	

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "<---L4db_PrintDiscoveredNAPsList - AgeAvailableNspsList after TTL Decrease");
	L4db_PrintDiscoveredNAPsList();

	// Copy the items that have aging status AgingStatus_New or AgingStatus_Old
	for (i=0; i<g_ndnsContext.availableNSPsList.numOfAvailableNSPs; i++)
	{
		currentNSP = &(g_ndnsContext.availableNSPsList.availableNSPs[i]);
		if (currentNSP->agingStatus == AgingStatus_New)
		{
			tmpAvailableNSP[currentCursor] = *currentNSP;
			tmpAvailableNSP[currentCursor].agingStatus = AgingStatus_Old;
			currentCursor++;
		}
		else if (currentNSP->agingStatus == AgingStatus_Old)
		{
			tmpAvailableNSP[currentCursor] = *currentNSP;
			tmpAvailableNSP[currentCursor].agingStatus = AgingStatus_Remove;
			currentCursor++;	
		}
		else
		{
			// items that have aging status AgingStatus_Remove - update their last detected flag in L4DB to FALSE
			tmpStatus = L4db_GetNapsInfo(currentNSP->nspId, (pL4db_Nap_t)naps, &napsSize);
			if (tmpStatus == WMX_ST_OK)
			{
				for (j = 0; j < napsSize; ++j)
				{
					L4db_SetDetectedNapFlag(naps[j].napID , FALSE);
				}				
			}
			else
			{
				L4db_SetDetectedNapFlag((wmx_pNAPid_t)currentNSP->bsId, FALSE);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "AvailableNSPsList aging error: couldn't retrieve NAPs info from DB. NSP ID: %d", currentNSP->nspId);
				status = tmpStatus;
			}

		}
	}

	// If some of the items had status AgingStatus_New
	if (currentCursor > 0)
	{
		OSAL_memcpy_s(	g_ndnsContext.availableNSPsList.availableNSPs,		
					sizeof(wmx_AvailableNSP_t) * WMX_NSP_IDS_MAX_NUM,
					tmpAvailableNSP, 
					sizeof(wmx_AvailableNSP_t) * currentCursor);
	}

	g_ndnsContext.availableNSPsList.numOfAvailableNSPs = currentCursor;

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	if (status == WMX_ST_OK)
	{	
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Available NSPs list aging executed successfully");
	}

	return status;
}

// The function fills the given NSP list with the available NSPs
wmx_Status_t GetAvailableNspsList(UINT32 *numOfNSPs, wmx_pNSP_t nsps, BOOL isFiltered)
{
	UINT32 i, j = 0;	
	wmx_Status_t st;

	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	for (i = 0; i < g_ndnsContext.availableNSPsList.numOfAvailableNSPs && j < *numOfNSPs ; i++)
	{
		if ((!isFiltered) || (g_ndnsContext.availableNSPsList.availableNSPs[i].agingStatus != AgingStatus_Remove))
		{		
			st = GetNspInfo(g_ndnsContext.availableNSPsList.availableNSPs[i].nspId, &(nsps[j++]));

			if (st != WMX_ST_OK)
			{
				return st;
			}
		}
	}

	*numOfNSPs = j;

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	return WMX_ST_OK;
}

void PrintAvailableNspsList(BOOL isFiltered, Severities severity)
{
	UINT32 numOfNSPs, i, j;
	wmx_NSP_t nsps[WMX_NSPS_MAX_NUM];

	UNREFERENCED_PARAMETER(severity);
	numOfNSPs= WMX_NSPS_MAX_NUM;

	GetAvailableNspsList(&numOfNSPs, nsps, isFiltered);

	TRACE(TR_MOD_NDNS_AGENT, severity, "Available NSPs List currently contains %d NSPs (%s filtered):", numOfNSPs, isFiltered ? NDNS_STR_EMPTY : NDNS_STR_NOT);
	for (i = 0; i < numOfNSPs; ++i)
	{
		char nspIdsStr[MAX_STR_LEN] = {0};
		
		for (j = 0; j < nsps[i].numOfNspIDs; ++j)
		{
			OSAL_sprintf_s(nspIdsStr, MAX_STR_LEN, " %d", nsps[i].nspIDs[j]);
		}			
		TRACE(TR_MOD_NDNS_AGENT, severity, "%d. %s - NSP ID(s):%s", i + 1, nsps[i].nspName, nspIdsStr);
	}
}

// The function fills the given NSP list with the available NSPs
BOOL IsNspInAvailableNspsList(wmx_NSPid_t nspId)
{
	UINT32 i;		
	BOOL bExist = FALSE;

	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	for (i=0; i<g_ndnsContext.availableNSPsList.numOfAvailableNSPs; i++)
	{		
		if (nspId == g_ndnsContext.availableNSPsList.availableNSPs[i].nspId)
		{
			bExist = TRUE;
			break;
		}
	}

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	return bExist;
}

// The function returns TRUE if a NSP was found; FALSE, otherwise. The function returns the node with the best RSSI
BOOL GetAvailableNspNode(wmx_NSPid_t nspId, wmx_pAvailableNSP_t pAvailableNsp)
{
	UINT32 i;		
	BOOL found = FALSE;	

	OSAL_enter_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	for (i=0; i<g_ndnsContext.availableNSPsList.numOfAvailableNSPs; i++)
	{
		if (g_ndnsContext.availableNSPsList.availableNSPs[i].nspId == nspId)
		{
			found = TRUE;
			OSAL_memcpy_s(pAvailableNsp, sizeof(wmx_AvailableNSP_t), g_ndnsContext.availableNSPsList.availableNSPs + i, sizeof(wmx_AvailableNSP_t));
			// TODO: it should work both ways, but it's here for debug purposes...
			//*pAvailableNsp = g_ndnsContext.availableNSPsList.availableNSPs[i];			
			break;
		}
	}

	OSAL_exit_critical_section( &g_ndnsContext.availableNSPsList.criticalSection );

	return found;
}


void NDnSAgent_MergeNSPsList(wmx_pNSPid_t firstNSPsList, UINT32 firstListSize,
							 wmx_pNSPid_t secondNSPsList, UINT32 secondListSize,
							 UINT32 howManyFromFirstList, 
							 wmx_pNSPid_t mergedList, UINT32 *responseSize)
{
	UINT32 currentSize = 0;
	UINT32 currentSizeSecondList = 0;
	BOOL addMore = TRUE; // Gets false when there where no elements to add

	// Make sure that there is a place in the result list
	while (currentSize < *responseSize && addMore == TRUE)
	{
		addMore = FALSE;

		// Fill the result list from the first input list
		if (howManyFromFirstList > currentSize && 
			currentSize < firstListSize)
		{
			mergedList[currentSize] = firstNSPsList[currentSize];
			addMore = TRUE;			
			currentSize++;
		}		
		else if (currentSizeSecondList < secondListSize) // Fill the result list from the second input list
		{
			mergedList[currentSize] = secondNSPsList[currentSizeSecondList];
			addMore = TRUE;
			currentSize++;
			currentSizeSecondList++;
		}
	}

	*responseSize = currentSize;
}


int GetNspIdentifier(wmx_BSid_t bsId)
{
	UINT8 mask = 0x7f;

	if ((bsId[4] | mask) != 0)
	{
		return 1;
	}

	return 0;
}

void CreateFakeAvailableNSPsFromNaps(UINT32 numOfNaps, wmx_pNAP_t naps, UINT32 *numOfNsps, wmx_pAvailableNSP_t nsps)
{
	UINT32 i;

	

	if (*numOfNsps < numOfNaps)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "CreateFakeNSPsFromNaps: Buffer too short");
		numOfNaps = *numOfNsps;
	}
	else
	{
		*numOfNsps = numOfNaps;
	}

	for (i=0; i<numOfNaps; i++)
	{
		memset(&nsps[i],0,sizeof(nsps[i]));
		nsps[i].agingStatus = AgingStatus_New;
		OSAL_memcpy_s(nsps[i].bsId, sizeof(wmx_BSid_t), naps[i].bsCriteria.bsID, sizeof(wmx_BSid_t));
		nsps[i].bsIdType = naps[i].bsIDType;
		nsps[i].connectType = ConnectReason_Activation;
		nsps[i].detectionTime = OSAL_timeGetTime();
		nsps[i].nspId = ((naps[i].bsCriteria.bsID[0] << 16) |
							(naps[i].bsCriteria.bsID[1] << 8) |
							(naps[i].bsCriteria.bsID[2] << 0));
		nsps[i].preferredListIndex = 0; // Use UpdatePreferredIndex to assign the real values to all the available NSPs				
		nsps[i].bestRssi = naps[i].bestRssi;
		nsps[i].bestCINR = naps[i].bestCINR;
		nsps[i].linkQuality = naps[i].bestLinkQuality;
	}
}

void CreateFakeNSPsFromNaps(UINT32 numOfNaps, wmx_pNAP_t naps, UINT32 *numOfNsps, wmx_pNSP_t nsps)
{
	UINT32 i;

	if (*numOfNsps < numOfNaps)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "CreateFakeNSPsFromNaps: Buffer too short");
		numOfNaps = *numOfNsps;
	}
	else
	{
		*numOfNsps = numOfNaps;
	}

	for (i=0; i<numOfNaps; i++)
	{
		memset(&nsps[i],0,sizeof(nsps[i]));
		nsps[i].activated = FALSE;
		nsps[i].isHomeNSP = FALSE;
		nsps[i].nspIDs[0] = ((naps[i].bsCriteria.bsID[0] << 16) |
							(naps[i].bsCriteria.bsID[1] << 8) |
							(naps[i].bsCriteria.bsID[2] << 0));
		OSAL_sprintf_s((char*)(nsps[i].nspName), WMX_NSP_NAME_MAX_SIZE, "Unrecognized Operator � ID: 0x%u", nsps[i].nspIDs[0]);				
		nsps[i].numOfNspIDs = 1;		
	}
}

BOOL CheckIfNspInAvailableList(wmx_NSPid_t nspId)
{
	wmx_Status_t st;
	UINT32 numOfNsps;
	UINT32 i;
	wmx_NSP_t nsps[WMX_NSP_IDS_MAX_NUM];
	BOOL result = FALSE;

	numOfNsps = WMX_NSP_IDS_MAX_NUM;
	st = GetAvailableNspsList(&numOfNsps, nsps, FALSE);

	for (i=0; i<numOfNsps; i++)
	{
		if (NDnSAgent_IsNspIdInNSP(nspId, &nsps[i]) == TRUE)
		{
			result = TRUE;
			break;
		}
	}

	return result;
}

