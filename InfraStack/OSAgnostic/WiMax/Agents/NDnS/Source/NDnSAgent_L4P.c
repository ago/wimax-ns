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
#include "NDnSAgent_L4P.h"
#include "wimax_osal_config_controler.h"
#include "L4ConfigurationManager.h"
#include "NDnSAgent_DB_if.h"
#include "NDnSAgent_Utils.h"


#define	MAX_NUM_OF_DISCRETE_CHANNELS	500 //TODO - change this to a real value
#define XOHM_CH_GROUP_SIZE	3 //TODO: Oran - remove when the "best found" patch is removed


/// <summary>
/// creates three arrays of NSP IDs responding to three categories : recent \ home \ not home.
/// the recent array will contain not home NSPs only if the allow auto activate flag is true.
/// </summary>
wmx_Status_t l4P_CreateNspCategoryArrays(wmx_pNSPid_t pRecentNspIds,	UINT32 * nRecentNspsSize, BOOL * actFirstRecent,
										 wmx_pNSPid_t pHomeNspIds,	UINT32 * nHomeNspsSize)
{
	wmx_Status_t	rc;
	NspCategory_t	category;		
	wmx_NSPid_t		pAllRecentNspIds[MAX_NUM_OF_RECENT_NSPS];
	wmx_NSPid_t		pProvisionedNspIds[WMX_NSPS_MAX_NUM];
	UINT32			allRecentNspsSize = MAX_NUM_OF_RECENT_NSPS;
	UINT32			provisionedNspsSize = WMX_NSPS_MAX_NUM;
	UINT32			i;

	//init all the sizes
	*nRecentNspsSize = 0;
	*nHomeNspsSize = 0;

	//get the recent NSPs from the L4db
	rc = L4db_GetRecentNsp(pAllRecentNspIds);
	if (pAllRecentNspIds[0] != (wmx_NSPid_t)L4DB_INVALID_INDEX)
	{
		allRecentNspsSize = 1;
	}
	else
	{
		allRecentNspsSize = 0;
	}
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_CreateNspCategoryArrays: l4P_CreateNspCategoryArrays failed");
		return rc;
	}

	//check the categories of the recent NSPs and add the NSP to the final recent array if activate ==true 
	if(allRecentNspsSize > 0)
	{
		for(i = 0 ; i <  allRecentNspsSize ; i++)
		{
			category = L4db_GetNspCategory(pAllRecentNspIds[i]);

			//if notHome, add only if AllowAutoActivate == True
			if((L4db_GetAllowAutoActivate()) || (Home == category))
			{
				pRecentNspIds[*nRecentNspsSize] = pAllRecentNspIds[i];
				(*nRecentNspsSize)++;

				//specify if the first member an the array is the actual 1st recent NSP
				if(i == 0)
				{
					*actFirstRecent = TRUE;
				}

			}
		}
	}

	//get all provisioned NSP ids and check their categories
	rc = L4db_GetProvisionedNspIds(pProvisionedNspIds, &provisionedNspsSize);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_CreateNspCategoryArrays: L4db_GetProvisionedNspIds failed");
		return rc; 
	}

	for(i = 0 ; i < provisionedNspsSize ; i++)
	{
		category = L4db_GetNspCategory(pProvisionedNspIds[i]);
		
		if(Home == category)
		{
			pHomeNspIds[*nHomeNspsSize] = pProvisionedNspIds[i];
			(*nHomeNspsSize)++;
		}
	}

	return WMX_ST_OK;
}

/// <summary>
/// adds NSP IDs from newNspIds to curNspIds while removing duplicates, if exists
/// </summary>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t l4P_AddNspIds(wmx_pNSPid_t curNspIds, UINT32 * curNspsSize, 
							UINT32 allocCurNspsSize, wmx_pNSPid_t newNspIds, UINT32 newNspsSize)
{
	UINT32				i, j, k;
	pProvisionedNsp_t	pNsp;
	wmx_Status_t		rc = WMX_ST_OK;
	BOOL				shouldBreak = FALSE;

	pNsp = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));
	if(FALSE == pNsp)
	{
		return WMX_ST_FAIL;
	}
	for(i = 0 ; i < newNspsSize ; i++)
	{
		shouldBreak = FALSE;
		rc = L4db_GetProvisionedNsp(newNspIds[i], pNsp);
		if(WMX_ST_OK != rc)
		{
			//free(pNsp);
			//return rc;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "L4Planner: Invalid NSP ID = %d detected. It will not be included in the channel plan generation since it's not provisioned.", newNspIds[i]);
			rc = WMX_ST_OK;

			continue;
		}

		//check if this nspID or one of its equivalents exists in the current NSP IDs
		for(j = 0 ; j < pNsp->nwParams.hNspsSize ; j++)
		{
			for(k = 0 ; k < *curNspsSize ; k++)
			{
				if(pNsp->nwParams.hNsps[j].nspId == curNspIds[k])
				{
					//we don't need to add this NSP ID to our result array
					shouldBreak = TRUE;
					break;
				}
			}
			if(TRUE == shouldBreak)
			{
				break;
			}
		}

		if(FALSE == shouldBreak)//this ID should be added to our result ids
		{
			//verify that the user allocated enough space
			if(*curNspsSize < allocCurNspsSize)
			{
				curNspIds[*curNspsSize] = newNspIds[i];
			}
			else
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
			}
			
			(*curNspsSize)++;
		}
	}

	free(pNsp);
	return rc;
}
/// <summary>
/// creates the preferred NSP list for the "1st recent" policy. This means - 1st recent NSP, 
/// 1st home NSP, other recents, other home, NSPs which are provisioned but not home ((if the auto activate flag is true)).
/// </summary>
wmx_Status_t l4P_CreateFirstRecentNspList(wmx_pNSPid_t pPreferredNspIds, UINT32 * nPreferredNspsSize)
{
	wmx_NSPid_t			pRecentNspIds[MAX_NUM_OF_RECENT_NSPS];
	wmx_NSPid_t			pHomeNspIds[WMX_NSPS_MAX_NUM];
	UINT32				recentSize = 0, homeSize = 0, actPreferredSize = 0;
	BOOL				actFirstRecent = FALSE;
	wmx_Status_t		rc;
	int					offset = 0;

	if (nPreferredNspsSize == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_CreateFirstRecentNspList: nPreferredNspsSize is NULL");
		return WMX_ST_WRONG_ARGUMENT;
	}

	//create the array for the different NSP categories
	rc = l4P_CreateNspCategoryArrays(pRecentNspIds, &recentSize, &actFirstRecent, pHomeNspIds, &homeSize);
	if(WMX_ST_OK != rc)
	{
		*nPreferredNspsSize = 0;
		return rc; //TODO - add trace
	}

	//add the first recent NSP
	if(recentSize > 0)
	{
		//check if the first member in the recent NSPs array, was actually 
		//the first recent NSP and was not dropped because it wasn't home and allowAutoActivate==FALSE
		if(TRUE == actFirstRecent)
		{
			rc = l4P_AddNspIds(pPreferredNspIds, &actPreferredSize, *nPreferredNspsSize,
								pRecentNspIds, 1);//we want to add only the first recent
			if(WMX_ST_OK != rc)
			{
				*nPreferredNspsSize = 0;
				return rc;
			}
			offset = 1;
		}
		else
		{
			offset = 0;
		}
	}

	//add the first home to the preferred list
	if(homeSize > 0)
	{
		//remove NSP Ids which already exist in the preferred list
		rc = l4P_AddNspIds(pPreferredNspIds, &actPreferredSize, *nPreferredNspsSize,
							pHomeNspIds, 1); //we want to add the first home only
		if(WMX_ST_OK != rc)
		{
			*nPreferredNspsSize = 0;
			return rc;
		}
	}

	if(recentSize > 1)
	{
		//add the other recent NSPs to our array
		rc = l4P_AddNspIds(pPreferredNspIds, &actPreferredSize, *nPreferredNspsSize, 
							pRecentNspIds + offset, recentSize - offset);
		if(WMX_ST_OK != rc)
		{
			*nPreferredNspsSize = 0;
			return rc;
		}
	}

	//add the other home NSPs
	if(homeSize > 1)
	{
		offset = 1;
		rc = l4P_AddNspIds(pPreferredNspIds, &actPreferredSize, *nPreferredNspsSize, 
							pHomeNspIds + offset , homeSize - offset);
		if(WMX_ST_OK != rc)
		{
			*nPreferredNspsSize = 0;
			return rc;
		}
	}

	//update the copied size \ size to be allocated by the user
	*nPreferredNspsSize = actPreferredSize;

	return rc;
}

/// <summary>
/// converts a "band" channel plan into a list of discrete channels. 
/// In other words, convert from the L4-db's channel plan structure to the wmx channel info structure
/// </summary>
wmx_Status_t l4P_ConvertToDiscreteChannels(pChannelPlan_t pChannelPlan, 
										  wmx_pChannelInfo_t pChannelInfoList,
										  UINT32 * nChannelInfoListSize)
{
	wmx_Status_t	rc = WMX_ST_OK;
	ChannelInfo_t	channel;
	UINT32			i;
	UINT32			size = 0;
	UINT32			j;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4P_ConvertToDiscreteChannels(IN)");
	//iterate through all the channels in the L4db's channel plan
	for(i = 0 ; i < pChannelPlan->channelsSize ; i++)
	{
		//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "chanels size=%d , i=%d",pChannelPlan->channelsSize,i);
		channel = pChannelPlan->channels[i];

		//create discrete channels from the band range
		if (channel.nextFreq == 0)
		{
			channel.lastFreq = channel.firstFreq;
		}
		for(j = channel.firstFreq ; j <= channel.lastFreq ; j += channel.nextFreq )
		{
			//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "channel.lastFreq=%d , j=%d", channel.lastFreq ,j);
			//verify that the user allocated enough space
			if(size < *nChannelInfoListSize)
			{
				//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "size=%d , nChannelInfoSize=%d", size, *nChannelInfoListSize);
				//frequency
				pChannelInfoList[size].frequency = j;

				// bandwidth
				if((wmx_BW_t)L4DB_INVALID_INDEX == channel.bw)
				{
					pChannelInfoList[size].bw = pChannelPlan->bw;
				}
				else
				{
					pChannelInfoList[size].bw = channel.bw;
				}

				//FFTSize
				if((wmx_FFT_t)L4DB_INVALID_INDEX == channel.fft)
				{
					pChannelInfoList[size].fft = pChannelPlan->fft;
				}
				else
				{
					pChannelInfoList[size].fft = channel.fft;
				}

				//preambles
				memcpy(pChannelInfoList[size].preambleBitmap, 
					channel.preambleBitmap, 
					sizeof(pChannelInfoList[size].preambleBitmap));
				
			}
			else
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
			}

			size++;
			if(channel.nextFreq == 0)
			{
				break;
			}
		}
	}

	//update the size to the user
	*nChannelInfoListSize = size;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4P_ConvertToDiscreteChannels(OUT). rc=%d, size=%d",rc,size);
	return rc;
}
/// <summary>
/// convert from the L4-db's channel structure to the wmx channel info structure
/// </summary>
wmx_Status_t l4P_ConvertTowmxChannel(pChannelInfo_t pChannelPlan, 
							wmx_pChannelInfo_t pwmxChannelInfo)
{
	wmx_Status_t	rc = WMX_ST_OK;
	BOOL			res = FALSE;
	UINT32			tempval;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4P_ConvertTowmxChannel(IN)");
	tempval = 1; // we send only one wmx_pChannelInfo as target
	res = wmxNds_DBChannelInfoToWmxChannelInfo(pwmxChannelInfo, &tempval, pChannelPlan, 1);
	if(FALSE == res)
	{
		rc = WMX_ST_FAIL;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4P_ConvertTowmxChannel(OUT).");
	return rc;
}
/// <summary>
/// decide if two channel infos are equal. for this version we are not comparing preambles
/// </summary>
BOOL l4P_IsEqualWmxChannelInfo(wmx_pChannelInfo_t pChannelInfo1, wmx_pChannelInfo_t pChannelInfo2, BOOL isCurrentPreferred)
{
	if(pChannelInfo1->bw != pChannelInfo2->bw)
	{
		return FALSE;
	}

	if(pChannelInfo1->fft != pChannelInfo2->fft)
	{
		return FALSE;
	}

	if(pChannelInfo1->frequency != pChannelInfo2->frequency)
	{
		return FALSE;
	}
	if(isCurrentPreferred && (0 != memcmp(pChannelInfo1->preambleBitmap, pChannelInfo2->preambleBitmap,PREAMBLES_LENGTH)))
	{
		return FALSE;
	}

	return TRUE;
}
/// <summary>
/// decide if two channel infos are equal. for this version we are not comparing preambles
/// </summary>
BOOL l4db_CompareChannelInfo(pChannelInfo_t pChannelInfo1, pChannelInfo_t pChannelInfo2, BOOL checkTtl)
{
	if(	pChannelInfo1->bw != pChannelInfo2->bw ||
		pChannelInfo1->fft != pChannelInfo2->fft ||
		pChannelInfo1->firstFreq != pChannelInfo2->firstFreq ||
		((TRUE == checkTtl) && (pChannelInfo1->ttl != pChannelInfo2->ttl)))
	{
		return FALSE;
	}
	
	return TRUE;
}
/// <summary>
/// creates an array of the preferred NSP IDs according to the policy which is stored in the L4db
/// </summary>
wmx_Status_t l4P_GetPreferredNspIds(wmx_pNSPid_t pPreferredNspIds, UINT32 * nPreferredNspsSize)
{
	PreferredScanPolicy_t	policy;
	wmx_Status_t			rc = WMX_ST_OK;

	//get the preferred scan policy from the L4db
	policy = L4db_GetPreferredScanPolicy();

	//according to the policy, create the preferred list. for now, we support only one policy
	switch(policy)
	{
		case FirstRecent:

			rc = l4P_CreateFirstRecentNspList(pPreferredNspIds, nPreferredNspsSize);
			break;

		default:
			*nPreferredNspsSize = 0;
			break;
	}

	return rc;
}


/// <summary>
/// gets the channel group (of size XOHM_CH_GROUP_SIZE) which contains sourceChInfo out of sourceChPlan
/// </summary>
int l4P_GetChannelGroup(wmx_pChannelInfo_t sourceChInfo, wmx_pChannelInfo_t sourceChPlan, int sourceChPlanSize, wmx_pChannelInfo_t chGroup, UINT32 *chGroupMaxSize)
{
	int i;
	int chIndex = L4DB_INVALID_INDEX;
	int firstChIndex = L4DB_INVALID_INDEX, lastChIndex;
	int currentIndex = 1;

	if (*chGroupMaxSize < XOHM_CH_GROUP_SIZE)
	{
		return L4DB_INVALID_INDEX;
	}

	for (i = 0; i < sourceChPlanSize; ++i)
	{
		if(TRUE == l4P_IsEqualWmxChannelInfo(sourceChInfo, &sourceChPlan[i], FALSE))
		{
			chIndex = i;
			break;
		}
	}

	if (chIndex != L4DB_INVALID_INDEX) // we have a match
	{
		firstChIndex = chIndex - (chIndex % XOHM_CH_GROUP_SIZE); // get the index of the first channel in the group 
		lastChIndex = (firstChIndex + XOHM_CH_GROUP_SIZE) <= sourceChPlanSize ? (firstChIndex + XOHM_CH_GROUP_SIZE) : sourceChPlanSize;

		// the source channel is the first in the group
		OSAL_memcpy_s(&chGroup[0], sizeof(wmx_ChannelInfo_t), &sourceChPlan[chIndex], sizeof(wmx_ChannelInfo_t));

		for (i = firstChIndex; i < lastChIndex; ++i)
		{
			if (i != chIndex)
			{			
				OSAL_memcpy_s(&chGroup[currentIndex++], sizeof(wmx_ChannelInfo_t), &sourceChPlan[i], sizeof(wmx_ChannelInfo_t));
			}
		}		

		if (currentIndex < XOHM_CH_GROUP_SIZE)
		{
			// in case we got less than XOHM_CH_GROUP_SIZE channels, fill the group with duplicates of the original channel
			for (i = currentIndex; i < XOHM_CH_GROUP_SIZE; ++i)
			{
				OSAL_memcpy_s(&chGroup[i], sizeof(wmx_ChannelInfo_t), sourceChInfo, sizeof(wmx_ChannelInfo_t));
			}
		}

		*chGroupMaxSize = XOHM_CH_GROUP_SIZE;
	}
	else
	{
		*chGroupMaxSize = 0;
	}
	
	return firstChIndex;
}


/// <summary>
/// merge a new channel plan to an existing channel info list while removing duplicates and completing each added channel to its parent group
/// </summary>
wmx_Status_t l4P_MergeChannelPlanByGroups(pChannelPlan_t pChannelPlan, wmx_pChannelInfo_t pChannelInfoList, 
								  UINT32 nAllocChannelsSize, UINT32 * nCurChannelsSize,
								  wmx_pChannelInfo_t pChInfoListComparer, UINT32 chInfoListComparerSize)
{
	wmx_ChannelInfo_t	pNewChannelInfos[MAX_NUM_OF_DISCRETE_CHANNELS];
	UINT32				newChannelsSize = MAX_NUM_OF_DISCRETE_CHANNELS;
	wmx_ChannelInfo_t	pChannelGroup[XOHM_CH_GROUP_SIZE];
	UINT32				chGroupSize = XOHM_CH_GROUP_SIZE;
	wmx_Status_t		rc;
	UINT32				i, j, k;
	BOOL				addChannel = TRUE;

	//convert  the received channel plans to discrete channel info lists
	rc = l4P_ConvertToDiscreteChannels(pChannelPlan, pNewChannelInfos, &newChannelsSize);
	if(WMX_ST_OK != rc)
	{
		return rc;
	}

	if(nAllocChannelsSize < *nCurChannelsSize)
	{
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}

	//add the new channel plan and remove duplicates, if exist
	for(i = 0 ; i < newChannelsSize ; i++)
	{
		addChannel = TRUE;

		//check if this channel is equal to one of the discovered channels
		for(j = 0 ; j < *nCurChannelsSize ; j++)
		{
			if(TRUE == l4P_IsEqualWmxChannelInfo(&pChannelInfoList[j], &pNewChannelInfos[i], FALSE))
			{
				addChannel = FALSE;
				break;
			}
		}

		if(TRUE == addChannel)
		{
			l4P_GetChannelGroup(&pNewChannelInfos[i], pChInfoListComparer, chInfoListComparerSize, pChannelGroup, &chGroupSize);

			//we need to add these channel infos, verify that the user allocated enough space
			if((*nCurChannelsSize + chGroupSize - 1) < nAllocChannelsSize)
			{
				for (j = 0; j < chGroupSize; ++j)
				{				
					memcpy(&pChannelInfoList[*nCurChannelsSize + j],
						&pChannelGroup[j], 
						sizeof(pChannelInfoList[*nCurChannelsSize + j]));
				}
			}
			else
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
			}
			(*nCurChannelsSize) += chGroupSize;
		}
		else
		{
			// Merge the preambles of the two channel infos in the case the other params are equal
			for (k = 0; k < PREAMBLES_LENGTH; k++)
			{
				pChannelInfoList[j].preambleBitmap[k] |= pNewChannelInfos[i].preambleBitmap[k];
			}			
		}
	}
	return rc;
}

/// <summary>
/// Append a new channel plan to an existing channel info Array without removing duplicates acording to the right order
/// </summary>
wmx_Status_t l4P_AppendTwoChannelInfoList(wmx_pChannelInfoArr pSourceChannelInfoArr, 
										  wmx_pChannelInfoArr pTargetChannelInfoArr,
										  UINT32 allocChannelsSize)
{
	UINT32 i=0 ,j=0, totalSize=0;
	wmx_Status_t		rc = WMX_ST_OK;
	pChannelInfo_t		tempBuff = NULL;

	totalSize = pTargetChannelInfoArr->arrSize + pSourceChannelInfoArr->arrSize;
	if(allocChannelsSize < (totalSize))
	{
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		tempBuff = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * totalSize);
		if(NULL == tempBuff)
		{
			return WMX_ST_NO_ROOM_FOR_INDICATION;
		}
		while((i<(pTargetChannelInfoArr->arrSize)) &&((j< pSourceChannelInfoArr->arrSize)))
		{
			if(1 > l4db_CompareChannelInfoByAge(&pTargetChannelInfoArr->pChannelInfoArr[i], &pSourceChannelInfoArr->pChannelInfoArr[j]))
			{
				memcpy(&tempBuff[i+j], &pTargetChannelInfoArr->pChannelInfoArr[i], sizeof(ChannelInfo_t));
				i++;
			}
			else
			{
				memcpy(&tempBuff[i+j], &pSourceChannelInfoArr->pChannelInfoArr[j], sizeof(ChannelInfo_t));
				j++;
			}
					
		}
		if(i == pTargetChannelInfoArr->arrSize)
		{
			memcpy(&tempBuff[i+j],
				   &pSourceChannelInfoArr->pChannelInfoArr[j],
				  (pSourceChannelInfoArr->arrSize - j)*sizeof(ChannelInfo_t));
		}
		else
		{
			memcpy(&tempBuff[i+j],
				   &pTargetChannelInfoArr->pChannelInfoArr[i],
				   (pTargetChannelInfoArr->arrSize - i)*sizeof(ChannelInfo_t));
		}

		//copy to the target array and free the locad allocated memory
		memcpy(pTargetChannelInfoArr->pChannelInfoArr, tempBuff, (totalSize * (sizeof(ChannelInfo_t))));
		pTargetChannelInfoArr->arrSize = (totalSize);

		free(tempBuff);
	}
	return rc;
}
//remove duplicated channels from channelInfo array
wmx_Status_t l4P_RemoveRedundantChannels(wmx_pChannelInfoArr pOriginalArr)
{
	wmx_Status_t rc = WMX_ST_OK;
	UINT32 uniqueSize , origSize = 0, i;
	BOOL foundMatch = FALSE;

	//the first element in the Array should remain the first one

	while(pOriginalArr->arrSize > origSize &&
		 pOriginalArr->pChannelInfoArr[origSize].lastFoundInNbrAdv)
	{
		//all the last channels having lastFoundInNbrAdv should remain in their order
		origSize++;
	}
	uniqueSize = origSize;


	for(origSize; origSize < pOriginalArr->arrSize; origSize++)
	{
		foundMatch = FALSE;
		for(i=0; i < uniqueSize ;i++)
		{
			if(l4db_CompareChannelInfo(&pOriginalArr->pChannelInfoArr[origSize], &pOriginalArr->pChannelInfoArr[i], FALSE))
			{			
				foundMatch = TRUE;
				break;
			}
		}
		if(FALSE == foundMatch)
		{
			memcpy(&pOriginalArr->pChannelInfoArr[uniqueSize], &pOriginalArr->pChannelInfoArr[origSize], sizeof(ChannelInfo_t));
			uniqueSize++;
		}
	}

	pOriginalArr->arrSize = uniqueSize;

	return rc;
}
/// <summary>
/// Append a new channel plan to an existing channel info Array without removing duplicates acording to the right order
/// </summary>
wmx_Status_t l4P_AppendChannelPlanIntoChannelInfoList(pChannelPlan_t pSourceChannelPlan, 
													 wmx_pChannelInfoArr pTargetChannelInfoArr,
													 UINT32 allocChannelsSize)
{
	wmx_Status_t		rc = WMX_ST_OK;
	wmx_ChannelInfoArr sourceChannelInfoArr;

	sourceChannelInfoArr.arrSize = pSourceChannelPlan->channelsSize;
	sourceChannelInfoArr.pChannelInfoArr = pSourceChannelPlan->channels;

	rc = l4P_AppendTwoChannelInfoList(&sourceChannelInfoArr,
									  pTargetChannelInfoArr,
									  allocChannelsSize);

	return rc;
}

/// <summary>
/// merge a new channel plan to an existing channel info list while removing duplicates
/// </summary>
wmx_Status_t l4P_MergeChannelPlan(pChannelPlan_t pChannelPlan, wmx_pChannelInfo_t pChannelInfoList, 
								  UINT32 nAllocChannelsSize, UINT32 * nCurChannelsSize, BOOL checkTtl)
{
	wmx_ChannelInfo_t	pNewChannelInfos[MAX_NUM_OF_DISCRETE_CHANNELS];
	UINT32				newChannelsSize = MAX_NUM_OF_DISCRETE_CHANNELS;
	wmx_Status_t		rc;
	UINT32				i, j, k;
	BOOL				addChannel = TRUE;

	//convert  the received channel plans to discrete channel info lists
	rc = l4P_ConvertToDiscreteChannels(pChannelPlan, pNewChannelInfos, &newChannelsSize);
	if(WMX_ST_OK != rc)
	{
		return rc;
	}

	if(nAllocChannelsSize < *nCurChannelsSize)
	{
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}

	//add the provisioned channel plan and remove duplicates, if exist
	for(i = 0 ; i < newChannelsSize ; i++)
	{
		addChannel = TRUE;

		//check if this channel is equal to one of the discovered channels
		for(j = 0 ; j < *nCurChannelsSize ; j++)
		{
			if(TRUE == l4P_IsEqualWmxChannelInfo(&pChannelInfoList[j], &pNewChannelInfos[i], checkTtl))
			{
				addChannel = FALSE;
				break;
			}
		}

		if(TRUE == addChannel)
		{
			//we need to add this channel info, verify that the user allocated enough space
			if(*nCurChannelsSize < nAllocChannelsSize)
			{
				memcpy(&pChannelInfoList[*nCurChannelsSize],
						&pNewChannelInfos[i], 
						sizeof(pChannelInfoList[*nCurChannelsSize]));
			}
			else
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
			}
			(*nCurChannelsSize)++;
		}
		else
		{
			// Merge the preambles of the two channel infos in the case the other params are equal
			for (k = 0; k < PREAMBLES_LENGTH; k++)
			{
				pChannelInfoList[j].preambleBitmap[k] |= pNewChannelInfos[i].preambleBitmap[k];
			}			
		}
	}
	return rc;
}
///<summary>
///merge the discovered channels into a given list and return a unique list 
/// </summary>
/// <param name="pChannelArr">(out) the allocated channel will be populated with the list. 
///								The size of the array will contain the allocated list length and return the number of channels that were filled</param name>
wmx_Status_t l4P_MergeAllDiscoveredChannelList(wmx_pChannelInfoArr	pChannelArr)
{
	UINT32 i;
	wmx_Status_t rc = WMX_ST_FAIL;
	DiscoveredNap_t pDiscoveredNapsList[MAX_NUM_OF_DISCOVERED_NAPS];
	UINT32 NumOfNaps = MAX_NUM_OF_DISCOVERED_NAPS;
	UINT32 allocatedChannels = 0;
	
	rc = L4db_GetAllDiscoveredNapsInfoList(pDiscoveredNapsList, &NumOfNaps);
	if(WMX_ST_OK == rc)
	{
		allocatedChannels = pChannelArr->arrSize;
		pChannelArr->arrSize = 0;
		//populate the channel list without sorting according to the TTL
		for(i=0; i<NumOfNaps; i++)
		{
			rc = l4P_AppendChannelPlanIntoChannelInfoList(&pDiscoveredNapsList[i].channelPlan, 
														 pChannelArr,
														 allocatedChannels);
		}
		l4P_RemoveRedundantChannels(pChannelArr);
	}
	return rc;
}

///<summary>
///	Fill the recent channels from the pDiscoveredChannelList into the pTargetList. Set all the preambles to 1 accourding to the indication populatePreamble.
/// </summary>
/// <param name="pTargetList">(in/out) Array that is filled with the recent channels </param name>
///							  IN - contain the actual allocated list length
///							  OUT - contain the actual number of channels that were populate in the pTargetList list</param name>
/// <param name="pDiscoveredChannelList">(in) the recent channel list </param name>
/// <param name="populatePreamble"> (in) indicate if we should set all the preambles to 1 or leave them without cange</param name>
wmx_Status_t l4P_GenerateRecentChannels(wmx_pChannelInfoArr pTargetList,
										wmx_pChannelInfoArr pDiscoveredChannelList,
										BOOL populatePreamble)
{
	wmx_Status_t rc = WMX_ST_OK;
	UINT32 numOfChannelsWithPreamble = 0;
	UINT32 i=0;
	
	if (pTargetList->arrSize < pDiscoveredChannelList->arrSize)
	{
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		//finding the last index in the pDiscoveredChannelList containing the recent discovered channels
		for (i=0; i < pDiscoveredChannelList->arrSize; i++)
		{
			if (FALSE == pDiscoveredChannelList->pChannelInfoArr[i].lastFoundInNbrAdv)
			{
				break;
			}
		}

		numOfChannelsWithPreamble = i;

		if (numOfChannelsWithPreamble > 0)
		{
			//populating the recent discovered channels
			OSAL_memcpy_s(pTargetList->pChannelInfoArr,
				sizeof(ChannelInfo_t) * numOfChannelsWithPreamble,
				pDiscoveredChannelList->pChannelInfoArr,
				sizeof(ChannelInfo_t) * numOfChannelsWithPreamble);

			pTargetList->arrSize = numOfChannelsWithPreamble;

			// Set all the preambles to 1 if needed
			if (TRUE == populatePreamble)
			{
				for(i=0; i<numOfChannelsWithPreamble; i++) 
				{
					memset(&pTargetList->pChannelInfoArr[i].preambleBitmap , 0xFF, PREAMBLES_LENGTH);
				}
			}
		}
		else
		{
			pTargetList->arrSize = 0;
		}
	}
	return rc;
}
///<summary>
///	Fill the target list with the elements from the source list that has a maching entry 
/// (same index) in the pMarkedList containing 0
/// </summary>
/// <param name="pTargetList">(in/out) Array that is filled with the channels from the pSourceList accourding to pMarkedList</param name>
///							  IN - contain the actual allocated list length
///							  OUT - contain the actual number of channels that were populate in the pTargetList list</param name>
/// <param name="pSourceList">(in) the source channel list </param name>
/// <param name="pMarkedList"> (in) an array that hold indication telling if the specific source element should be added to the target</param name>
wmx_Status_t l4P_GenerateUnmarkedList(wmx_pChannelInfoArr pTargetList,
									  wmx_pChannelInfoArr pSourceList,
									  BYTE				  *pMarkedList)
{
	UINT32 i, targetIndex = 0;
	wmx_Status_t rc = WMX_ST_OK;
	
	//add the rest of the discovered channels to the list
	for(i=0; i<pSourceList->arrSize; i++)
	{
		if( 1 == pMarkedList[i])
		{
			//was added already to the Target list
			continue;
		}
		if(pTargetList->arrSize <= targetIndex)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GenerateUnmarkedList:buffer too short");
			rc = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
			goto Finalize;
		}
		OSAL_memcpy_s(&pTargetList->pChannelInfoArr[targetIndex], sizeof(ChannelInfo_t), &pSourceList->pChannelInfoArr[i], sizeof(ChannelInfo_t));
		memset(pTargetList->pChannelInfoArr[targetIndex].preambleBitmap , 0xFF, PREAMBLES_LENGTH);
		targetIndex++;
	}

	pTargetList->arrSize = targetIndex;	

Finalize:
	return rc;
}
wmx_Status_t l4P_ConvertDBTowmxChannelList(wmx_pChannelInfo_t pChannelInfoTargetList, 
										   UINT32 *pChannelInfoTargetListSize,
										   wmx_pChannelInfoArr pSourceList)
{
	wmx_Status_t rc = WMX_ST_OK;
	UINT32 i=0;
	//update the output array and convert the structure to be wmx_pChannelInfo_t instead of ChannelInfo_t
	if(*pChannelInfoTargetListSize < pSourceList->arrSize)
	{
		//printing an error but populating the max size we can (*pChannelInfoTargetListSize) 
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_ConvertDBTowmxChannelList:buffer too short");	
	}
	else
	{
		//setting the exact size of the target list
		*pChannelInfoTargetListSize = pSourceList->arrSize;
	}
	for(i=0; i<*pChannelInfoTargetListSize; i++)
	{
		//convert  the received channel plans to discrete channel info lists
		rc = l4P_ConvertTowmxChannel(&pSourceList->pChannelInfoArr[i], &pChannelInfoTargetList[i]);
		if(WMX_ST_OK != rc)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_ConvertDBTowmxChannelList: l4P_ConvertTowmxChannel failed");	
			break;
		}
	}
	return rc;
}
///<summary>
///fetch the provisioned channels and return a unique list sorted by the TTL and then the rest of the provisioned channels
/// </summary>
/// <param name="pTargetList">(in/out) the allocated channel list will contain the provisioned channels </param name>
///										IN - contain the allocated list length
///										OUT - contain the number of channels that were populated</param name>
/// <param name="pDiscoveredChannelList">(in) the detected channel list, used for sorting the result </param name>
/// <param name="pProvisionChannelList">(in) the provisioned channel list </param name>
/// <param name="pIsDiscoveredAddedToTheList">(out) an array the has the same number of elements as in the pDiscoveredChannelList
///											  this array use to marke the discovered channels we allready populate in the pAppendedChannelList</param name>
wmx_Status_t l4P_GenerateProvisionedChannels(wmx_pChannelInfoArr pTargetList,
										wmx_pChannelInfoArr pDiscoveredChannelList,
										wmx_pChannelInfoArr pProvisionChannelList,
										BYTE			*pIsDiscoveredAddedToTheList)
{
	wmx_Status_t rc = WMX_ST_WRONG_ARGUMENT;
	UINT32 checkedDiscoveredChannelsIndex = 0;
	UINT32 currentTargetIndex = 0;
	UINT32 j=0;
	BYTE *pIsProvisionAddedToTheList = NULL; //an array that marks the channels from the pProvisionChannelList that where added into the pAppendedChannelList

	pIsProvisionAddedToTheList = (BYTE *)calloc(pProvisionChannelList->arrSize, sizeof(BYTE));
	if(NULL == pIsProvisionAddedToTheList)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "l4P_GenerateProvisionedChannels: unable to allocate the pIsProvisionAddedToTheList Array");
		rc = WMX_ST_FAIL;
		goto End;
	}

	//populate the provisioned channels that where found in the discovered list sorted by age
	for(checkedDiscoveredChannelsIndex = 0; checkedDiscoveredChannelsIndex<pDiscoveredChannelList->arrSize; checkedDiscoveredChannelsIndex++)
	{
		// Look for the discovered channel in the provisioned channels list
		for(j=0; j<pProvisionChannelList->arrSize; j++)
		{
			if(pTargetList->arrSize <= currentTargetIndex)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GenerateProvisionedChannels:buffer too short");
				rc = WMX_ST_BUFFER_TOO_SHORT;
				goto End;
			}

			// Ignore the channel if it was added
			if(1 == pIsProvisionAddedToTheList[j])
			{
				//was added already to the final list
				continue;
			}

			if(TRUE == l4db_CompareChannelInfo(&pProvisionChannelList->pChannelInfoArr[j],
												 &pDiscoveredChannelList->pChannelInfoArr[checkedDiscoveredChannelsIndex],
												 FALSE))
			{
				if(FALSE == pDiscoveredChannelList->pChannelInfoArr[checkedDiscoveredChannelsIndex].lastFoundInNbrAdv)
				{
					// The channel was found in the provisioned channels list, add to the target list
					OSAL_memcpy_s(&pTargetList->pChannelInfoArr[currentTargetIndex], 
							 sizeof(ChannelInfo_t),
							 &pDiscoveredChannelList->pChannelInfoArr[checkedDiscoveredChannelsIndex],
							 sizeof(ChannelInfo_t));

					memset(pTargetList->pChannelInfoArr[currentTargetIndex].preambleBitmap , 0xFF, PREAMBLES_LENGTH);
					currentTargetIndex++;

					//mark the pProvisionChnnelList in order to skip it when adding the not recent
					// Channels to the target list
					pIsDiscoveredAddedToTheList[checkedDiscoveredChannelsIndex] = 1;
				}
				pIsProvisionAddedToTheList[j] = 1;
				break;
			}	
		}	
	}

	//add the rest of the provisioned channels that were not marked in pIsProvisionAddedToTheList
	for(j=0; j<pProvisionChannelList->arrSize; j++)
	{
		if( 1 == pIsProvisionAddedToTheList[j])
		{
			// The channel was already added
			continue;
		}
		//add to the target list
		if(pTargetList->arrSize <= currentTargetIndex)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GenerateProvisionedChannels:buffer too short");
			rc = WMX_ST_BUFFER_TOO_SHORT;
			goto End;
		}
		OSAL_memcpy_s(&pTargetList->pChannelInfoArr[currentTargetIndex],
				sizeof(ChannelInfo_t),
				&pProvisionChannelList->pChannelInfoArr[j],
				sizeof(ChannelInfo_t));

		memset(pTargetList->pChannelInfoArr[currentTargetIndex].preambleBitmap , 0xFF, PREAMBLES_LENGTH);
		currentTargetIndex++;
	}
	pTargetList->arrSize = currentTargetIndex;
	rc = WMX_ST_OK;

End:
	WMX_FREE(pIsProvisionAddedToTheList);
	return rc;

}
///<summary>
////merge two channels list into one list (pTargetChannelList)
/// </summary>
/// <param name="pSourceChannelList">(in) list to merge into the target list</param name>
/// <param name="pTargetChannelList">(in/out) in - the original channel list 
///												 out - the merged list		</param name>
/// <param name="numOfAllocatedChannel">(in) the number of channels can be found (in total) in the Target channel list</param name>
/// <param name="checkTtl">(in) indication if we need to compare the channels using the ttl as well</param name>
wmx_Status_t l4P_Merge2ListsOfChannelInfo(wmx_pChannelInfoArr  pSourceChannelList,
										  wmx_pChannelInfoArr  pTargetChannelList,
										  UINT32		 numOfAllocatedChannel,
										  BOOL			 checkTtl)
{
	wmx_Status_t rc = WMX_ST_OK;
	UINT32	i,j;
	UINT32 numberOfAddedChannels = 0;
	
	//adding the pSourceChannelList in the end of pTargetChannelList removing duplicates
	for (j=0; j<pSourceChannelList->arrSize; j++)
	{
		if(numOfAllocatedChannel >= (pTargetChannelList->arrSize + numberOfAddedChannels))
		{
			for(i=0; i<pTargetChannelList->arrSize; i++)
			{
				//we try to find match only in the original list without the channels where added in the function
				if(TRUE == l4db_CompareChannelInfo(&pSourceChannelList->pChannelInfoArr[j], &pTargetChannelList->pChannelInfoArr[i], checkTtl))
				{
					//if the channels are equal set the age to be the earliest possible
					if(-1 == l4db_CompareChannelInfoByAge(&pSourceChannelList->pChannelInfoArr[j], &pTargetChannelList->pChannelInfoArr[i]))
					{
						pTargetChannelList->pChannelInfoArr[i].lastFoundInNbrAdv = pSourceChannelList->pChannelInfoArr[j].lastFoundInNbrAdv;
						pTargetChannelList->pChannelInfoArr[i].ttl = pSourceChannelList->pChannelInfoArr[j].ttl;
					}

					break;
				}
			}
			if(i == pTargetChannelList->arrSize)
			{
				//we exit the inner for and didn't find match
				OSAL_memcpy_s(&pTargetChannelList->pChannelInfoArr[pTargetChannelList->arrSize + numberOfAddedChannels],
						 sizeof(ChannelInfo_t),
						 &pSourceChannelList->pChannelInfoArr[j],
						 sizeof(ChannelInfo_t));
				numberOfAddedChannels++;
			}
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_Merge2ListsOfChannelInfo: the pTargetChannelList is full");
		}
	}
	pTargetChannelList->arrSize += numberOfAddedChannels;

	return rc;
}
/// <summary>
/// creates the discovered channel list for the specific Nsp sorted accourding the Age
/// <param name="nspId">(in)the specific NSP we fetching the data for </param name>
/// <param name="pDiscoveredChannelArr">(OUT) contain the list of the discovered Channels per the NSP.
///										contain the size of the allocated list and return the actual size</param name>
/// </summary>
wmx_Status_t L4P_GetDetectedChannelsPerNsp(wmx_NSPid_t nspId, wmx_pChannelInfoArr pDiscoveredChannelArr)
{
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	ProvisionedNsp_t	provisionedData;
	UINT32 i,allocatedSize;
	Profile_t unprovisioned;
	ChannelPlan_t channelPlan;

	allocatedSize = pDiscoveredChannelArr->arrSize;
	pDiscoveredChannelArr->arrSize = 0;

	rc = L4db_GetProvisionedPerNspID(nspId,&provisionedData);
	if(rc == WMX_ST_OK)
	{
		if(NULL != &provisionedData)
		{
			for(i=0; i<provisionedData.nwParams.capl.napsSize; i++)
			{				
				if(L4db_GetMaxDetectedChannelPerNap(provisionedData.nwParams.capl.naps[i].napID) + pDiscoveredChannelArr->arrSize > allocatedSize)
				{
					rc = WMX_ST_BUFFER_TOO_SHORT;
					goto Finalize;
				}
				else 
				{
					rc = L4db_GetDetectedChannelPerNap(provisionedData.nwParams.capl.naps[i].napID, &channelPlan);
					if(WMX_ST_OK != rc)
					{
						goto Finalize;
					}
					if(0 < channelPlan.channelsSize)
					{
						//merge the channel plans in each nap to the pDiscoveredChannelList
						rc = l4P_AppendChannelPlanIntoChannelInfoList(&channelPlan, 
																	pDiscoveredChannelArr, 
																	allocatedSize);
					}
				}
			}
		}		
	}
	else
	{		
		//if the nsp was not found in the provisioned try to look for it in the unprovisioned
		rc = L4db_GetUnprovisionedProfilePerNspID(nspId, &unprovisioned);
		if(WMX_ST_OK == rc)
		{
			if(L4db_GetMaxDetectedChannelPerNap(unprovisioned.napID) > allocatedSize)
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
				goto Finalize;
			}
			else 
			{
				rc = L4db_GetDetectedChannelPerNap(unprovisioned.napID, &channelPlan);
				//merge the channel plans in each nap to the pDiscoveredChannelList
				rc = l4P_AppendChannelPlanIntoChannelInfoList(&channelPlan, 
															pDiscoveredChannelArr, 
															allocatedSize);
				if (WMX_ST_OK != rc)
				{
					goto Finalize;
				}
			}
		}
	}
	
	//we redundant only if we found data in the provisioned or in the unProvisioned	
	l4P_RemoveRedundantChannels(pDiscoveredChannelArr);

Finalize:
	return rc;
}

/// <summary>
/// Returns the max length of detected channels list.
/// this function returns the size in order to allocate the exact size of channels (in the calling function)
/// <param name="nspId">(in)the specific NSP we fetching the data for </param name>
/// <param name="pNumOfChannels">(OUT) contain the the number of detected channels per NSP</param name>
/// </summary>
wmx_Status_t L4P_GetMaxDetectedChannelPerNsp(wmx_NSPid_t nspId, UINT32 *pNumOfChannels)
{
	wmx_Status_t		rc = WMX_ST_DATA_UNAVAILABLE;
	ProvisionedNsp_t	provisionedData;
	UINT32 i;
	Profile_t	unprovisioned;

	*pNumOfChannels = 0;
	
	rc = L4db_GetProvisionedPerNspID(nspId, &provisionedData);
	if(rc == WMX_ST_OK)
	{
		//find the number of detected channels from the specific provisioned NSP
		for(i=0; i<provisionedData.nwParams.capl.napsSize; i++)
		{
			*pNumOfChannels += L4db_GetMaxDetectedChannelPerNap(provisionedData.nwParams.capl.naps[i].napID);				
		}
	}
	else
	{
		//if the nsp was not found in the provisioned try to look for it in the unprovisioned
		rc = L4db_GetUnprovisionedProfilePerNspID(nspId, &unprovisioned);
		if(WMX_ST_OK == rc)
		{
			//find the number of the max detected channels of a specific unprovisioned NSP
			*pNumOfChannels += L4db_GetMaxDetectedChannelPerNap(unprovisioned.napID);			
		}
	}
	return rc;
}
/// <summary>
/// creates the MCP list for the current preferred Nsp
/// <param name="currentPreferredNspId">(in)the specific NSP we feching the data for </param name>
/// <param name="pChannelInfoFinalList">(OUT) contain the list of the MCP per the NSP</param name>
///	<param name="pChannelInfoFinalListSize">(IN/OUT) contain the size of the allocated list and return the actual size</param name>
/// </summary>
wmx_Status_t l4P_GeneratePreferredScanCurrent(wmx_NSPid_t currentPreferredNspId, wmx_pChannelInfo_t pChannelInfoFinalList, UINT32 *pChannelInfoFinalListSize)
{
	wmx_Status_t rc = WMX_ST_FAIL;
	UINT32  numOfChannelsWithPreamble;
	wmx_ChannelInfoArr	appendedChannelList; // Holds the result MCP
	wmx_ChannelInfoArr	appendedChannelListCurrentPosition;	
	UINT32				allocatedSizeOfAppendedChannels;   
	wmx_ChannelInfoArr	discoveredChannelArr; //holds the detected list
	wmx_ChannelInfoArr  tempDiscoveredChannelArr;
	wmx_ChannelInfoArr  provisionedChannelArr; //holds the provisioned list
	BYTE				*pIsDiscoveredAddedToTheList = NULL; //holds a list marks if a specific detected channel was added to the appended list
	

	//call to the db functions in order to allocate the estimated size of the buffers and allocation the lists according them
	appendedChannelList.pChannelInfoArr = NULL;
	appendedChannelListCurrentPosition.pChannelInfoArr = NULL;
	discoveredChannelArr.pChannelInfoArr = NULL;
	provisionedChannelArr.pChannelInfoArr = NULL;
	rc = L4P_GetMaxDetectedChannelPerNsp(currentPreferredNspId, &discoveredChannelArr.arrSize);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4P_GetMaxDetectedChannelPerNsp returned rc = [%d]",rc);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: L4P_GetMaxDetectedChannelPerNsp failed");
		goto End;
	}
	pIsDiscoveredAddedToTheList = (BYTE *)calloc(discoveredChannelArr.arrSize, sizeof(BYTE));
	if(NULL == pIsDiscoveredAddedToTheList)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: allocation of pIsDiscoveredAddedToTheList failed");
		rc = WMX_ST_FAIL;
		goto End;
	}

	discoveredChannelArr.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * discoveredChannelArr.arrSize);
	if(NULL == discoveredChannelArr.pChannelInfoArr)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: allocation of discoveredChannelArr failed");
		rc = WMX_ST_FAIL;
		goto End;
	}
	rc = L4db_GetMaxChannelsPerProvisionedNsp(currentPreferredNspId, &provisionedChannelArr.arrSize);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4db_GetMaxChannelsPerProvisionedNsp returned rc = [%d] : &provisionedChannelArr.arrSize = [%d]",rc, provisionedChannelArr.arrSize);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: L4db_GetMaxChannelsPerProvisionedNsp failed");
		goto End;
	}
	provisionedChannelArr.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * provisionedChannelArr.arrSize);
	if(NULL == provisionedChannelArr.pChannelInfoArr)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: allocation of provisionedChannelArr failed");
		rc = WMX_ST_FAIL;
		goto End;
	}
	appendedChannelList.arrSize = provisionedChannelArr.arrSize + 2 * discoveredChannelArr.arrSize;
	appendedChannelList.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * appendedChannelList.arrSize);
	if(NULL == appendedChannelList.pChannelInfoArr)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: allocation of appendedChannelList failed");
		rc = WMX_ST_FAIL;
		goto End;
	}

	//creating the discovered list
	allocatedSizeOfAppendedChannels = appendedChannelList.arrSize;

	rc = L4P_GetDetectedChannelsPerNsp(currentPreferredNspId,
										&discoveredChannelArr);

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: L4P_GetDetectedChannelsPerNsp failed");
		 goto End;
	}
	
	//create the provisioned channels list
	rc = L4db_GetChannelsPerProvisionedNsp(currentPreferredNspId,
										   provisionedChannelArr.pChannelInfoArr,
										   &provisionedChannelArr.arrSize);

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: L4db_GetChannelsPerProvisionedNsp failed");
		goto End;
	}
	
	//finding the last index in the discoveredChannelArr containing the recent discovered channels
	rc = l4P_GenerateRecentChannels(&appendedChannelList, 
									&discoveredChannelArr,
									FALSE);

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: l4P_GenerateRecentChannels populatePreamble = FALSE failed");
		goto End; 
	}

	numOfChannelsWithPreamble = appendedChannelList.arrSize;

	//deduct the number of channels already populated
	appendedChannelListCurrentPosition.arrSize = allocatedSizeOfAppendedChannels - appendedChannelList.arrSize;
	appendedChannelListCurrentPosition.pChannelInfoArr = &appendedChannelList.pChannelInfoArr[appendedChannelList.arrSize];

	rc = l4P_GenerateRecentChannels(&appendedChannelListCurrentPosition, 
									&discoveredChannelArr,
									TRUE);

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: l4P_GenerateRecentChannels populatePreamble = TRUE failed");
		goto End; 
	}
	//add the number of channels deducted earlier 
	appendedChannelList.arrSize += appendedChannelListCurrentPosition.arrSize;

	appendedChannelListCurrentPosition.arrSize = allocatedSizeOfAppendedChannels - appendedChannelList.arrSize;
	appendedChannelListCurrentPosition.pChannelInfoArr = &appendedChannelList.pChannelInfoArr[appendedChannelList.arrSize];
	
	tempDiscoveredChannelArr.arrSize = discoveredChannelArr.arrSize - numOfChannelsWithPreamble;
	tempDiscoveredChannelArr.pChannelInfoArr = &discoveredChannelArr.pChannelInfoArr[numOfChannelsWithPreamble];

	// Add the provisioned channels sorted by the detection time
	rc = l4P_GenerateProvisionedChannels(&appendedChannelListCurrentPosition,
										 &tempDiscoveredChannelArr,
									     &provisionedChannelArr,
										 &pIsDiscoveredAddedToTheList[numOfChannelsWithPreamble]); 

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: l4P_GenerateProvisionedChannels failed");
		goto End; 
	}
	//add the number of channels found in the provisioned channel list 
	appendedChannelList.arrSize += appendedChannelListCurrentPosition.arrSize;

	appendedChannelListCurrentPosition.arrSize = allocatedSizeOfAppendedChannels - appendedChannelList.arrSize;
	appendedChannelListCurrentPosition.pChannelInfoArr = &appendedChannelList.pChannelInfoArr[appendedChannelList.arrSize];

	// Add the discovered channels that were not added yet
	rc = l4P_GenerateUnmarkedList(&appendedChannelListCurrentPosition,
								  &tempDiscoveredChannelArr,
								  &pIsDiscoveredAddedToTheList[numOfChannelsWithPreamble]);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: l4P_GenerateUnmarkedList failed");
		goto End; 
	}

	//add the number of channels added from the discovered list 
	appendedChannelList.arrSize += appendedChannelListCurrentPosition.arrSize;

	// delete all duplicated channels (compare also preambles)
	L4db_DeleteDuplicatedChannels(&appendedChannelList.arrSize, appendedChannelList.pChannelInfoArr, TRUE);

	rc = l4P_ConvertDBTowmxChannelList(	pChannelInfoFinalList,
										pChannelInfoFinalListSize,
										&appendedChannelList);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: l4P_ConvertDBTowmxChannelList failed");
	}
End:
	WMX_FREE(pIsDiscoveredAddedToTheList);
	WMX_FREE(discoveredChannelArr.pChannelInfoArr);
	WMX_FREE(provisionedChannelArr.pChannelInfoArr);
	WMX_FREE(appendedChannelList.pChannelInfoArr);

	return rc;
}
/// <summary>
/// creates the MCP list when the current Nsp is not found
/// <param name="pChannelInfoFinalList">(OUT) contains the list of the MCP</param name>
///	<param name="pChannelInfoFinalListSize">(IN/OUT) contains the size of the allocated list and return the actual size</param name>
/// </summary>
wmx_Status_t l4P_GeneratePreferredScanNotCurrent(wmx_pChannelInfo_t pChannelInfoFinalList, UINT32 *pChannelInfoFinalListSize)
{
	wmx_NSPid_t pNspIds[WMX_IDS_MAX_NUM]; 
	UINT32 nNspIdsSize = WMX_IDS_MAX_NUM;
	wmx_Status_t rc = WMX_ST_OK;
	UINT32 i;
	wmx_ChannelInfoArr appendedChannelArr;
	wmx_ChannelInfoArr appendedChannelListCurrentPosition;	
	wmx_ChannelInfoArr discoveredChannelArr;
	wmx_ChannelInfoArr tempDiscoveredChannelArr;
	wmx_ChannelInfoArr  provisionedChannelArr;
	UINT32		   tempNumOfProvisionedChannel = 0;
	UINT32		   tempNumOfFilledChannel = 0;
	UINT32		   allocatedSizeOfAppendedChannels;   
	wmx_ChannelInfoArr provisionedChannelPlanOfOneNsp;
	UINT32		   numOfAllocatedProvisionChannel = 0;
	BYTE		   *pIsDiscoveredAddedToTheList = NULL;

	OSAL_ZeroMemory(&appendedChannelArr, sizeof(wmx_ChannelInfoArr));
	OSAL_ZeroMemory(&appendedChannelListCurrentPosition, sizeof(wmx_ChannelInfoArr));
	OSAL_ZeroMemory(&discoveredChannelArr, sizeof(wmx_ChannelInfoArr));
	OSAL_ZeroMemory(&tempDiscoveredChannelArr, sizeof(wmx_ChannelInfoArr));
	OSAL_ZeroMemory(&provisionedChannelArr, sizeof(wmx_ChannelInfoArr));

	//setting the provisionedChannelPlanOfOneNsp
	provisionedChannelPlanOfOneNsp.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * WMX_CHANNELS_MAX_NUM);
	provisionedChannelPlanOfOneNsp.arrSize = WMX_CHANNELS_MAX_NUM;

	//get all provisioned NSP ids and check their categories
	rc = L4db_GetProvisionedNspIds(pNspIds, &nNspIdsSize);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: L4db_GetProvisionedNspIds failed");
		goto End; 
	}

	//allocate the buffer for the lists declared in the beginning of the function
	
	//finding the max provisioned channels
	provisionedChannelArr.arrSize = 0;
	for (i=0; i<nNspIdsSize; i++)
	{
		rc = L4db_GetMaxChannelsPerProvisionedNsp(pNspIds[i], &tempNumOfProvisionedChannel);
		if(WMX_ST_OK != rc)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: L4db_GetCurrentDetectedListSize failed");
			goto End;
		}
		provisionedChannelArr.arrSize += tempNumOfProvisionedChannel;
	}

	numOfAllocatedProvisionChannel = provisionedChannelArr.arrSize;
	
	//finding the max detected channels
	rc = L4db_GetMaxDetectedChannels(&discoveredChannelArr.arrSize);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: L4db_GetMaxDetectedChannels failed");
		goto End;
	}

	pIsDiscoveredAddedToTheList = (BYTE *)calloc(discoveredChannelArr.arrSize, sizeof(BYTE));
	if(NULL == pIsDiscoveredAddedToTheList)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: allocation of pIsDiscoveredAddedToTheList failed");
		rc = WMX_ST_FAIL;
		goto End;
	}

	discoveredChannelArr.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * discoveredChannelArr.arrSize);
	if(NULL == discoveredChannelArr.pChannelInfoArr)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: allocation of discoveredChannelArr.pChannelInfoArr failed");
		rc = WMX_ST_FAIL;
		goto End;
	}
	
	provisionedChannelArr.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * provisionedChannelArr.arrSize);
	if(NULL == provisionedChannelArr.pChannelInfoArr)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: allocation of provisionedChannelArr failed");
		rc = WMX_ST_FAIL;
		goto End;
	}
	appendedChannelArr.arrSize = provisionedChannelArr.arrSize + discoveredChannelArr.arrSize;
	allocatedSizeOfAppendedChannels = appendedChannelArr.arrSize;
	appendedChannelArr.pChannelInfoArr = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * appendedChannelArr.arrSize);
	if(NULL == appendedChannelArr.pChannelInfoArr)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: allocation of appendedChannelArr.pChannelInfoArr failed");
		rc = WMX_ST_FAIL;
		goto End;
	}

	// Fill the provisioned channel list
	provisionedChannelArr.arrSize = 0;
	for(i=0; i<nNspIdsSize; i++)
	{
		provisionedChannelPlanOfOneNsp.arrSize = WMX_CHANNELS_MAX_NUM;
		rc = L4db_GetChannelsPerProvisionedNsp(pNspIds[i], 
											   provisionedChannelPlanOfOneNsp.pChannelInfoArr,
											   &provisionedChannelPlanOfOneNsp.arrSize);


		if(WMX_ST_OK != rc)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: L4db_GetChannelsPerProvisionedNsp failed , rc = [%d]",rc);
			goto End; 
		}
		
		//merge two channels list into one list (provisionedChannelArr).
		// Add the new channels from the provisionedChannelPlanOfOneNsp into provisionedChannelArr
		rc = l4P_Merge2ListsOfChannelInfo(&provisionedChannelPlanOfOneNsp,
										  &provisionedChannelArr,
										  numOfAllocatedProvisionChannel,
										  FALSE);
	}

	//create the discovered channels list of all the discovered naps sorted by the discovery time
	rc = l4P_MergeAllDiscoveredChannelList(&discoveredChannelArr);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: l4P_MergeSortedFullDiscoveredChannelList failed");
		goto End;
	}
	
	// Add the recent channels with preambles = 1
	appendedChannelListCurrentPosition.arrSize = appendedChannelArr.arrSize;
	appendedChannelListCurrentPosition.pChannelInfoArr = appendedChannelArr.pChannelInfoArr;

	rc = l4P_GenerateRecentChannels(&appendedChannelListCurrentPosition, 
									&discoveredChannelArr,
									TRUE);

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanNotCurrent: l4P_GenerateRecentChannels failed");
		goto End; 
	}
	tempNumOfFilledChannel = appendedChannelListCurrentPosition.arrSize;
	tempDiscoveredChannelArr.arrSize = discoveredChannelArr.arrSize - tempNumOfFilledChannel;
	tempDiscoveredChannelArr.pChannelInfoArr = &discoveredChannelArr.pChannelInfoArr[tempNumOfFilledChannel];
	//we add the number of channels we deduct earlier 
	appendedChannelArr.arrSize = appendedChannelListCurrentPosition.arrSize;

	appendedChannelListCurrentPosition.arrSize = allocatedSizeOfAppendedChannels - appendedChannelArr.arrSize;
	appendedChannelListCurrentPosition.pChannelInfoArr = &appendedChannelArr.pChannelInfoArr[tempNumOfFilledChannel];

	 
									
	rc = l4P_GenerateProvisionedChannels(&appendedChannelListCurrentPosition,
										 &tempDiscoveredChannelArr,
									     &provisionedChannelArr,
										 &pIsDiscoveredAddedToTheList[tempNumOfFilledChannel]); 

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanCurrent: l4P_GenerateProvisionedChannels failed");
		goto End; 
	}
	//we add the number of channels we deduct earlier 
	appendedChannelArr.arrSize = appendedChannelArr.arrSize + appendedChannelListCurrentPosition.arrSize;

	rc = l4P_ConvertDBTowmxChannelList(	pChannelInfoFinalList,
										pChannelInfoFinalListSize,
										&appendedChannelArr);

End:
	WMX_FREE(provisionedChannelPlanOfOneNsp.pChannelInfoArr);
	WMX_FREE(pIsDiscoveredAddedToTheList);
	WMX_FREE(discoveredChannelArr.pChannelInfoArr);
	WMX_FREE(provisionedChannelArr.pChannelInfoArr);
	WMX_FREE(appendedChannelArr.pChannelInfoArr);

	return rc;
}

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
wmx_Status_t L4P_GenerateNspMCP( wmx_NSPid_t nspId, wmx_pChannelInfo_t pChannelInfoList, UINT32 *nChannelInfoListSize)
{
	wmx_Status_t		rc = WMX_ST_FAIL;


	if(NULL == pChannelInfoList || 0 == *nChannelInfoListSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4P_GenerateNspMCP got invalid parameters failed");
		rc = WMX_ST_WRONG_ARGUMENT;
	}
	else
	{
		if((wmx_NSPid_t)L4DB_INVALID_INDEX != nspId)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Generating preferred MCP for NSP ID=%u", nspId);
			rc = l4P_GeneratePreferredScanCurrent(nspId, pChannelInfoList, nChannelInfoListSize);				
		}		
	}

	return rc;
}

/// <summary>
/// creates the preferred scan discrete channel list for preferred NSP
/// </summary>
wmx_Status_t l4P_GeneratePreferredScanParams(wmx_pChannelInfo_t pChannelInfoList, UINT32 *nChannelInfoListSize)
{
	wmx_Status_t		rc = WMX_ST_FAIL;
	wmx_NSPid_t			currentPreferredNspId = (wmx_NSPid_t)L4DB_INVALID_INDEX;


	if(NULL == pChannelInfoList || 0 == *nChannelInfoListSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GeneratePreferredScanParams got invalid parameters failed");
		rc = WMX_ST_WRONG_ARGUMENT;
	}
	else
	{
		//setting the flag of the currentPreferredNspId	
		rc = L4db_GetCurrentPreferredNsp(&currentPreferredNspId);
		if((WMX_ST_OK == rc) && ((wmx_NSPid_t)L4DB_INVALID_INDEX != currentPreferredNspId))
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Current preferred NSP is set. Generating preferred MCP");
			rc = l4P_GeneratePreferredScanCurrent(currentPreferredNspId, pChannelInfoList, nChannelInfoListSize);				
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Current preferred NSP is NOT set. Generating preferred MCP");
			rc =l4P_GeneratePreferredScanNotCurrent(pChannelInfoList, nChannelInfoListSize);
		}
	}

	return rc;
}
/// <summary>
/// creates the while scan's discretre channel info list
/// </summary>
wmx_Status_t l4P_GenerateWhileScanParams(wmx_pChannelInfo_t pChannelInfoList, UINT32 *nChannelInfoListSize)
{
	wmx_Status_t	rc;
	ChannelPlan_t	channelPlan;
	UINT32			preferredScanListSize, wideScanListSize;
	UINT32			j, indexLocation, currentLocation;
	BOOL foundMatch = FALSE;

	preferredScanListSize = *nChannelInfoListSize;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4P_GenerateWhileScanParams(IN)");

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "ScanType_PreferredList inside l4P_GenerateWhileScanParams");
	rc = l4P_GeneratePreferredScanNotCurrent(pChannelInfoList, &preferredScanListSize);

	//get the wide scan parameters from the db
	rc = L4db_GetBandRange(&channelPlan);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GenerateWhileScanParams(OUT). rc=%d",rc);
		return rc;
	}

	wideScanListSize = *nChannelInfoListSize - preferredScanListSize;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "->>>>>>>>---[%d] = [%d] - [%d] ==> wideScanListSize = *nChannelInfoListSize - preferredScanListSize->>>>>>>>---",*nChannelInfoListSize - preferredScanListSize,*nChannelInfoListSize,preferredScanListSize );
 	//create an array of discrete channels, we asuume there are no duplicates
	rc = l4P_ConvertToDiscreteChannels(&channelPlan, &pChannelInfoList[preferredScanListSize], &wideScanListSize);
	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4P_GenerateWhileScanParams after l4P_ConvertToDiscreteChannels. rc=%d",rc);
		return rc;
	}

	

	currentLocation=0;
	//remove dupplicate channels (each list contain unique channels - need to check duplicate between lists)
	for(indexLocation=0 ; indexLocation<wideScanListSize ; indexLocation++)
	{
		for(j=0 ; j<preferredScanListSize ; j++)
		{
			if(TRUE == l4P_IsEqualWmxChannelInfo(&pChannelInfoList[j], &pChannelInfoList[preferredScanListSize + indexLocation], FALSE))
			{
				foundMatch = TRUE;
				break;
			}
		}
		if (FALSE == foundMatch)
		{
			if(currentLocation != indexLocation)
			{
				OSAL_memcpy_s(&pChannelInfoList[preferredScanListSize + currentLocation],
						sizeof(wmx_ChannelInfo_t),
						&pChannelInfoList[preferredScanListSize + indexLocation],
						sizeof(wmx_ChannelInfo_t));
			}

			currentLocation++;
		}
		foundMatch = FALSE;
	}

	*nChannelInfoListSize = preferredScanListSize + currentLocation;
	
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4P_GenerateWhileScanParams(OUT). rc=%d",rc);
	return rc;
}

/// <summary>
/// Generates the master - plan according to the requested scan type
/// </summary>
/// <param name="scanType">(IN)  the requested scan type</param>
/// <param name="pChannelInfoList">(OUT) an array of channel infos allocated by the user</param>
/// <param name="nChannelInfoListSize">(IN)  the size of the array allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GenerateMCP( wmx_ScanType scanType, wmx_pChannelInfo_t pChannelInfoList, UINT32 *nChannelInfoListSize)
{
	wmx_Status_t rc = WMX_ST_FAIL;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4P_GenerateMCP(IN)");
	switch (scanType)
	{
		case ScanType_WhileScan:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "ScanType_WhileScan - nChannelInfoListSize = [%d]  - Nardimon",*nChannelInfoListSize);
			rc = l4P_GenerateWhileScanParams(pChannelInfoList, nChannelInfoListSize);
			break;

		case ScanType_PreferredList:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "ScanType_PreferredList - nChannelInfoListSize = [%d]",*nChannelInfoListSize);
			rc = l4P_GeneratePreferredScanParams(pChannelInfoList, nChannelInfoListSize);
			break;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4P_GenerateMCP(OUT)");
	return rc;
}
/// <summary>
/// Generates the master channel plan according to the requested scan type
/// </summary>
/// <param name="pChannelInfos">(OUT) an array of channel info ((a struct defined in the L4db))</param>
/// <param name="nChannelInfosSize">(IN)  the size of the array allocated by the user
///			                        (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GetWideScanParams(pChannelInfo_t pChannelInfos, UINT32 * nChannelInfosSize)
{
	wmx_Status_t rc;
	ChannelPlan_t channelPlan;

	//get the wide scan params from the L4db
	rc = L4db_GetBandRange(&channelPlan);
	if(WMX_ST_OK != rc)
	{
		return rc;
	}

	//verify that the user allocated enough space
	if(*nChannelInfosSize < channelPlan.channelsSize)
	{
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		rc = WMX_ST_OK;
		memcpy(pChannelInfos, channelPlan.channels, channelPlan.channelsSize * sizeof(*pChannelInfos));
	}

	//update the size copied \ that should be allocated to the user
	*nChannelInfosSize = channelPlan.channelsSize;

	return rc;
}


/// <summary>
/// Generates the list of preferred NSPs according the policy in the L4db
/// </summary>
/// <param name="pPreferredNsps">(OUT) an array of preferred NSPs allocated by the user</param>
/// <param name="nPreferredNspsSize">(IN)  the size of the array allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4P_GetPreferredNspList(wmx_pPreferredNsp pPreferredNsps, UINT32 * nPreferredNspsSize)
{
	wmx_Status_t		rc;
	wmx_NSPid_t			pPreferredNspIds[WMX_NSP_IDS_MAX_NUM];
	UINT32				idsSize = WMX_NSP_IDS_MAX_NUM;
	UINT32				actSize = 0;
	UINT32				i, j;
	pProvisionedNsp_t	pNsp;
	NspCategory_t		category;
	size_t				tempStrLen = 0;

	rc = l4P_GetPreferredNspIds(pPreferredNspIds, &idsSize);
	if(WMX_ST_OK != rc)
	{
		return rc;
	}
	pNsp = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));
	if(FALSE == pNsp)
	{
		return WMX_ST_FAIL;
	}

	//verify that the user allocated enough space
	if(*nPreferredNspsSize <idsSize)
	{
		rc =  WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		//iterate through all the nsp IDs an get the relevant info
		for(i = 0 ; i < idsSize ; i++)
		{
			rc = L4db_GetProvisionedNsp(pPreferredNspIds[i], pNsp);
			if(WMX_ST_OK != rc)
			{
				free(pNsp);
				return rc;
			}
			
			//copy all nsp ids
			for(j = 0 ; j < pNsp->nwParams.hNspsSize ; j++)
			{
				pPreferredNsps[actSize].nspIds[j] = pNsp->nwParams.hNsps[j].nspId;
			}

			pPreferredNsps[actSize].nspIdsSize = pNsp->nwParams.hNspsSize;

			//copy all NAP ids
			for(j = 0 ; j < pNsp->nwParams.capl.napsSize ; j++)
			{
				memcpy(pPreferredNsps[actSize].napIds[j], 
					   pNsp->nwParams.capl.naps[j].napID,
					   sizeof(pPreferredNsps[actSize].napIds[j]));
			}

			pPreferredNsps[actSize].napsSize = pNsp->nwParams.capl.napsSize;

			//get the nsp's name. If 16g name exists, we will take it.
			tempStrLen = OSAL_strnlen(pNsp->nwParams.name16g, WMX_NSP_NAME_MAX_SIZE);
			if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
			{
				memcpy(pPreferredNsps[actSize].name, pNsp->nwParams.name16g, sizeof(pPreferredNsps[actSize].name));
			}
			else
			{
				memcpy(pPreferredNsps[actSize].name, pNsp->nwParams.provisionedName, sizeof(pPreferredNsps[actSize].name));
			}
			
			//get the NSP's category
			category = L4db_GetNspCategory(pPreferredNspIds[i]);
			
			if(Home == category)
			{
				pPreferredNsps[actSize].isHome = TRUE;
			}
			else
			{
				pPreferredNsps[actSize].isHome = FALSE;
			}
		
			actSize++;
		}
	}

	//update the copies size \ size to be allocated 
	*nPreferredNspsSize = idsSize;
	free(pNsp);
	return rc;
}


