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
#include "NDnSAgent.h"
#include "NDnS_L4Scanner.h"

#include "IndicatorsSubscribers.h"
#include "L5OpCodes.h"	

#include "wmxSDK_Nds_InternalStructs.h"
#include "L4ConfigurationManager.h"

#define MAX_BSID_STR_LENGTH	40

extern L4ScannerContext_t g_l4ScannerContext;


// Used to receive scan updates from the driver on scan update event
void L4S_ScanUpdate( wmx_ScanStatus_t scanStatus, UINT32 numOfNaps, wmx_pNAP_t naps )
{
	UINT32 i, channelIndex;
	UINT32 highestNapIndex = 0, highestChannelIndex=0;
	wmx_ChannelID_t highestChannelID=0;
	//UINT32 j =0;
	char bsIdTypeStr[MAX_BSID_STR_LENGTH];
	BOOL onlyFullBsIDs = TRUE;
	UINT32 disableDiscoveryValue = 0;
	BOOL isDiscoveryDisabled;
	BOOL goodResultsInChunk = FALSE, beneathListConatainsLastChannelInChunk = FALSE;
	wmx_NSPid_t nspID;
	wmx_Status_t ret;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_ScanUpdate(IN) - ScanStatus=%d, got %d naps", scanStatus, numOfNaps);
	g_l4ScannerContext.divided = FALSE;
	memset(&g_l4ScannerContext.scanResults,0,sizeof(wmx_ScanResults_t));
	for (i=0; i<numOfNaps && i < WMX_NAPS_MAX_NUM; i++)
	{
		for (channelIndex=0; channelIndex<naps[i].numChannels && channelIndex < WMX_CHANNELS_MAX_NUM; channelIndex++)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Scan results: NAP %u Ch %d: ChID %u, CINR %d, RSSI %d, linkQuality %u, linkGrade %s , g_l4ScannerContext.scanType = [%d]", i, (UINT32)channelIndex, 
				(UINT32)naps[i].channelIdList[channelIndex], (int)naps[i].CINRs[channelIndex],
				(int)naps[i].RSSIs[channelIndex], (UINT32)naps[i].linkQuality[channelIndex], (int)naps[i].linkGrade[channelIndex] == LinkGrade_AboveThr ? L"Good" : L"Bad", g_l4ScannerContext.scanType);
			if (naps[i].linkGrade[channelIndex] == LinkGrade_AboveThr)
			{
				goodResultsInChunk = TRUE;
			}
			if (highestChannelID < naps[i].channelIdList[channelIndex])
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Going to replace highestChannelID=[%d] with naps[i].channelIdList[channelIndex]= [%d]",highestChannelID ,naps[i].channelIdList[channelIndex]);
				highestChannelID = naps[i].channelIdList[channelIndex];
				highestChannelIndex = channelIndex;
				highestNapIndex = i;	
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "highestChannelID = [%d] highestChannelIndex [%d] highestNapIndex = [%d]",highestChannelID,highestChannelIndex ,highestNapIndex);
			}

		}
		
	}
	if (numOfNaps == 0)
	{
		highestChannelID = g_l4ScannerContext.nextChannelToScan;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Informaton -- > g_l4ScannerContext.currentChunkSize = [%d] (channelIndex) = [%d], g_l4ScannerContext.nextChannelToScan = [%d], g_l4ScannerContext.currentChunk = [%d]",g_l4ScannerContext.currentChunkSize,highestChannelIndex, g_l4ScannerContext.nextChannelToScan, g_l4ScannerContext.currentChunk);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "ToSplitOrNotToSplit -- > goodResultsInChunk = [%d], naps[i].linkGrade[channelIndex] = [%d], LinkGrade_BelowThrnaps[i].linkGrade[channelIndex] == LinkGrade_BelowThr", goodResultsInChunk, naps[highestNapIndex].linkGrade[highestChannelIndex], (naps[highestNapIndex].linkGrade[highestChannelIndex] == LinkGrade_BelowThr));
	ret = L4db_GetCurrentPreferredNsp(&nspID);
	//((ret!=WMX_ST_OK) || (nspID==L4DB_INVALID_INDEX)) && 
	if (((ret!=WMX_ST_OK) || (nspID==L4DB_INVALID_INDEX)) || (!goodResultsInChunk && naps[highestNapIndex].linkGrade[highestChannelIndex] == LinkGrade_BelowThr))
	{
		if ((ret!=WMX_ST_OK) || (nspID==L4DB_INVALID_INDEX)) 
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Going to check if all channels in the chunk were scanned since there is no preferred NSP !");
		}
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Before increase --> g_l4ScannerContext.currentChunkSize = [%d] (channelIndex) = [%d], g_l4ScannerContext.nextChannelToScan = [%d], g_l4ScannerContext.currentChunk = [%d]",g_l4ScannerContext.currentChunkSize,highestChannelIndex, g_l4ScannerContext.nextChannelToScan, g_l4ScannerContext.currentChunk);
		if (highestChannelIndex > 1)
		{
			if (naps[highestNapIndex].channelIdList[highestChannelIndex] == (g_l4ScannerContext.nextChannelToScan-1))
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Found highest ChannelID which is [%d] and at the end of the given chunk, no need to split.", naps[highestNapIndex].channelIdList[highestChannelIndex]);
				beneathListConatainsLastChannelInChunk = TRUE;
			}
		}
		if (highestChannelID < (g_l4ScannerContext.nextChannelToScan-1)
			&& (g_l4ScannerContext.scanType != SCAN_TYPE_WIDE) && !beneathListConatainsLastChannelInChunk)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "----------------------------------> g_l4ScannerContext.numChunks++ %d", g_l4ScannerContext.numChunks);
			g_l4ScannerContext.numChunks++;
			g_l4ScannerContext.currentChunkSize = g_l4ScannerContext.nextChannelToScan - (naps[highestNapIndex].channelIdList[highestChannelIndex] + 1);//g_l4ScannerContext.currentChunkSize - (channelIndex+1);
			g_l4ScannerContext.nextChannelToScan = highestChannelID + 1;
			g_l4ScannerContext.divided = TRUE;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "After increase -- > g_l4ScannerContext.currentChunkSize = [%d] (channelIndex) = [%d], highestChannelID+1 = [%d], g_l4ScannerContext.nextChannelToScan = [%d], g_l4ScannerContext.currentChunk++ = [%d]",g_l4ScannerContext.currentChunkSize,highestChannelIndex, highestChannelID+1, g_l4ScannerContext.nextChannelToScan, g_l4ScannerContext.currentChunk);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Did not finish the scan within the chunk in scan type prefferd and the channel recieved was LinkGrade_BelowThr");
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Calculated the g_l4ScannerContext params ==> g_l4ScannerContext.numChunks = [%d] , g_l4ScannerContext.nextChannelToScan = [%d]", g_l4ScannerContext.numChunks, g_l4ScannerContext.nextChannelToScan);
		}
	}
	beneathListConatainsLastChannelInChunk = FALSE;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "----------------------------------> g_l4ScannerContext.currentChunk++ %d", g_l4ScannerContext.currentChunk);
	g_l4ScannerContext.currentChunk++;
	//if (L4S_GetScannerState() != L4S_SCANNING)
	//{
	//	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "L4S_ScanUpdate(OUT) - Wrong state of L4 Scanner. State: %d. Scan results discarded !", L4S_GetScannerState());
	//	return; // error
	//}

	if (L4S_IsResetRequested())
	{		
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_ScanUpdate(OUT) - Scan results discarded due to scan reset !");
		return;
	}

	// check if we should disable discovery
	isDiscoveryDisabled = L4Configurations_getDisableDiscovery(&disableDiscoveryValue);	
	if (isDiscoveryDisabled) // key found - disable the discovery phase
	{	
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Discovery is disabled. Overriding compressed maps settings.");
	}

	for (i = 0; i < numOfNaps; ++i)
	{
		naps[i].bsIDType = GetBsIdType(naps[i].bsCriteria.bsIDmask);
		if (naps[i].bsIDType != FULL_BSID && naps[i].bsIDType != FULL_NAP && !isDiscoveryDisabled)
		{
			onlyFullBsIDs = FALSE;
		}
		wmxNds_BsIdMaskToStr(naps[i].bsIDType, bsIdTypeStr, MAX_BSID_STR_LENGTH - 1); 
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Got %s - NAPID: [%2x][%2x][%2x] 0x%x",
			bsIdTypeStr,
			naps[i].bsCriteria.bsID[2],
			naps[i].bsCriteria.bsID[1],
			naps[i].bsCriteria.bsID[0], 
			naps[i].bsCriteria.bsID[2] * (256 * 256) + naps[i].bsCriteria.bsID[1] * 256 + naps[i].bsCriteria.bsID[0]);
	}
	memset (&g_l4ScannerContext.scanResults, 0, sizeof (wmx_ScanResults_t));	
	// save the NAPs found in the scan update for the next steps
	OSAL_memcpy_s(g_l4ScannerContext.scanResults.NAPs, WMX_NAPS_MAX_NUM * sizeof(wmx_NAP_t), naps, numOfNaps * sizeof(wmx_NAP_t));
	g_l4ScannerContext.scanResults.NAPsCount = numOfNaps;
	g_l4ScannerContext.scanResults.scanStatus = scanStatus;
	g_l4ScannerContext.scanResults.isCycleComplete = !L4S_AreChunksLeft();

	if (_16G_ON || !onlyFullBsIDs) // 16G is on or we have at least one compressed map - discovery is required
	{	
		g_l4ScannerContext.scanResults.currentNapIndex = 0;				
		//L4S_SetScannerState(L4S_DISCOVER);
		L4S_Discover(); // execute discovery for the current chunk
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_ScanUpdate(OUT) - L4S_Discover");
		return;
	}
	else // 16G is off and we already have all the full BSIDs - no need to wait for system state ready
	{
		// if scan is complete - shift scanner to ready state
		if (g_l4ScannerContext.scanResults.scanStatus > 0 && !L4S_SetScannerStateIfEqual(L4S_SCANNING, L4S_READY))
		{
			L4S_SetScannerState(L4S_READY);
			OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Wrong state of L4 Scanner while trying to send results to L4C. State: %d. Expected: L4S_SCANNING.", L4S_GetScannerState());
		}
		g_l4ScannerContext.scanResults.currentNapIndex = numOfNaps;
		// Check if it is needed to save the last scanned channel ID
		if (g_l4ScannerContext.scanPolicy ==  SCAN_MODE_FIND_FIRST &&
			numOfNaps > 0 && 
			naps[0].numChannels > 0)
		{
			g_l4ScannerContext.nextChannelToScan = (wmx_ChannelID_t)naps[0].channelIdList[0] + 1;

			if (g_l4ScannerContext.nextChannelToScan < g_l4ScannerContext.currentChunk * g_l4ScannerContext.currentChunkSize)
			{
				g_l4ScannerContext.currentChunk--;
			}
		}		

		L4C_ProcessScanResults(&g_l4ScannerContext.scanResults);		
		//L4C_UpdateData(L4C_CbType_ScanResults, (L4C_pDataUnion)&g_l4ScannerContext.scanResults);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_ScanUpdate(OUT) - L4C_ProcessScanResults");
	}	
}


void L4S_BsInfoUpdate(wmx_pBsInfo_t bsInfo)
{
	wmx_pNAP_t currentNAP;
	wmx_SII_t sii;
	char bsIdTypeStr[MAX_BSID_STR_LENGTH];

	if (L4S_GetScannerState() == L4S_DISCOVER) // we are currently in the discovery phase
	{
		currentNAP = &g_l4ScannerContext.scanResults.NAPs[g_l4ScannerContext.scanResults.currentNapIndex];
		currentNAP->bsIDType = FULL_BSID;

		wmxNds_BsIdMaskToStr(currentNAP->bsIDType, bsIdTypeStr, MAX_BSID_STR_LENGTH - 1);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "%s [%02x][%02x][%02x][%02x][%02x][%02x] detected (Compressed: [%02x][%02x][%02x][%02x][%02x][%02x])",
			bsIdTypeStr,
			bsInfo->bsID[0], 
			bsInfo->bsID[1],
			bsInfo->bsID[2],
			bsInfo->bsID[3],
			bsInfo->bsID[4],
			bsInfo->bsID[5],
			currentNAP->bsCriteria.bsID[0],
			currentNAP->bsCriteria.bsID[1],
			currentNAP->bsCriteria.bsID[2],
			currentNAP->bsCriteria.bsID[3],
			currentNAP->bsCriteria.bsID[4],
			currentNAP->bsCriteria.bsID[5]);

		OSAL_memcpy_s(currentNAP->bsCriteria.bsID, sizeof(wmx_BSid_t), bsInfo->bsID, sizeof(wmx_BSid_t));		
		currentNAP->changeCount = bsInfo->nspChangeCount;

		// if 16g is off, we're not expecting to get a real "sii" indication, so let's fake one
		if (!_16G_ON)
		{
			sii.nspIdListSize = 0;
			L4S_SIIUpdate(&sii);
		}
	}
	// if this BsInfo report is a result of a real connect - we can ignore it.

	// TODO: Oran - check if we can get the nspChangeCount earlier as part of the scan results,
	// and that way - if the change count has changed compared to the db - we could trigger 16g.

}


void L4S_SIIUpdate(wmx_pSII_t sii)
{
	//wmx_Status_t status;
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "SII update CB (IN)");
	// we are currently in the discovery phase, it's time to disconnect...
	if (L4S_SetScannerStateIfEqual(L4S_DISCOVER, L4S_DISCONNECT))
	{	
		// TODO: Oran - finish implementation when 16g is in
		if (sii->nspIdListSize == 0) // this is an empty SII
		{
				
		}

		if (_16G_ON) // update NSPs and verbose names
		{

		}
	}
}