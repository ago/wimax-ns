#include "NDnSAgent_DB_Internal.h"
#include "wmxSDK_Msc_2.h"
#include "NDnSAgent_Utils.h"
#include "NDnSAgent_Monitor.h"

#include "L4ConfigurationManager.h"
#include "Registry_Controller.h"
#include "ver_info.h"
#include "CryptServices.h"

//globals
pL4db_Context		g_pL4dbContext;
OSAL_critical_section	g_L4dbLock; // info locks
BOOL				g_fIsInitiated;


/// <summary>
/// Init the L4-db
/// </summary>
wmx_Status_t L4db_Init()
{
	wmx_Status_t rc = WMX_ST_FAIL;

	if(FALSE == g_fIsInitiated)
	{
		g_pL4dbContext = (pL4db_Context)malloc(sizeof(L4db_Context));
		if(NULL == g_pL4dbContext)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_Init malloc failed!");
			return rc;
		}

		rc = WMX_ST_OK;


		OSAL_init_critical_section(&g_L4dbLock);
		rc = L4db_Clean();

		g_fIsInitiated = TRUE;

	}

	if (WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_Init - Failed. rc=%d!",rc);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"L4db_Init Lock Init succeeded. rc=%d!",rc);
	}
	return rc;
}

/// <summary>
/// Clean the L4-db
/// <summary/>
wmx_Status_t L4db_Clean()
{
	int i;

	OSAL_enter_critical_section(&g_L4dbLock);

	//init all NSPs
	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->nsps) ; i++)
	{
		l4db_InitNsp(&g_pL4dbContext->nsps[i]);
	}

	//init the wide scan parameters
	l4db_InitChannelPlan(&g_pL4dbContext->wideScanParams);

	//init all discovered NAPs
	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->discoveredNaps) ; i++)
	{
		l4db_InitDiscoveredNap(&g_pL4dbContext->discoveredNaps[i]);
	}

	// Init temp scan results
	g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount = 0;
	g_pL4dbContext->tempScanResults.totalNAPsCount = 0;

	//init the general Nds setting
	l4db_InitGeneralSettings(&g_pL4dbContext->generalSettings);

	//init the device certificates
	l4db_InitDeviceCerts(&g_pL4dbContext->deviceCerts);

	//init the db version
	g_pL4dbContext->l4dbVersion = L4DB_INVALID_INDEX;

	//init the preferred scan policy
	g_pL4dbContext->preferredScanPolicy = L4DB_INVALID_INDEX;

	// init FUMO parameters
	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->fumoNodes) ; i++)
	{
		l4db_InitFumoNode(&g_pL4dbContext->fumoNodes[i]);
	}	

	// Init internal parameters node
	l4db_InitAPDOInternalParametersNode(&g_pL4dbContext->apdoInternalParams);
	
	//init the connection time
	// JDarzi - change the time calculation metode.
	//g_pL4dbContext->connectionTime = DEFAULT_TIME;
	g_pL4dbContext->connectionTime = timeGetTime();

	//init the nai counter
	g_pL4dbContext->naiCounter = 1;

	//init the different dev details branches
	l4db_InitDevDetail(&g_pL4dbContext->devDetail);

	l4db_InitDevInfo(&g_pL4dbContext->devInfo);

	l4db_InitWimax(&g_pL4dbContext->wimax);

	OSAL_exit_critical_section(&g_L4dbLock);
	return WMX_ST_OK;
}



/// <summary>
/// De-Init the L4-db
/// </summary>
wmx_Status_t L4db_DeInit()
{
	wmx_Status_t rc=WMX_ST_FAIL;

	if(g_fIsInitiated)
	{
		OSAL_delete_critical_section(&g_L4dbLock);
		g_fIsInitiated = FALSE;
		rc = WMX_ST_OK;
		free(g_pL4dbContext);
	}
	return rc;
}

/// <summary>
/// Gets APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_GetAPDOinfo(wmx_APDOPath_t pAPDOPath, void *pValue, wmx_pAPDOType_t pAPDOType )
{
	//[findme][amirs] till we add buffer size parm to wmx_GetAPDOinfo we uses buffsize as temp
	int buffsize = BUFF_SIZE;
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	rc = l4db_RunCmdFromPath((char *)pAPDOPath,pValue,&buffsize,pAPDOType,APDO_GetCmd);

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}


/// <summary>
/// adds APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_AddAPDOinfo(wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType )
{
	int buffsize =  wmxApdo_GetBufferLength(pValue, APDOType);
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	rc = l4db_RunCmdFromPath((char *)pAPDOPath,pValue,&buffsize,&APDOType,APDO_AddCmd);

	OSAL_exit_critical_section(&g_L4dbLock);

	//PopulateMonitorVal();
	return rc;
}


/// <summary>
/// Updates APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_UpdateAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType )
{
	int buffsize = wmxApdo_GetBufferLength(pValue, APDOType);
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	rc = l4db_RunCmdFromPath((char *)pAPDOPath,pValue,&buffsize,&APDOType,APDO_UpdateCmd);

	OSAL_exit_critical_section(&g_L4dbLock);

	//PopulateMonitorVal();
	return rc;

}


/// <summary>
/// deletes APDO info according to a given APDO path
/// </summary>
wmx_Status_t L4db_DeleteAPDOinfo( wmx_APDOPath_t pAPDOPath )
{
	//[findme][amirs] till we add buffer size parm to wmx_GetAPDOinfo we uses buffsize as temp
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	rc = l4db_RunCmdFromPath((char *)pAPDOPath, "", NULL, NULL, APDO_DeleteCmd);

	OSAL_exit_critical_section(&g_L4dbLock);
	//PopulateMonitorVal();

	return rc;
}


/// <summary>
/// Generates a sorted Nap array for a given NSP. the array consists only of 
/// last detected NAPs which have 16g info.  The NAPs are sorted according to their CAPL priority
/// </summary>
static void l4db_Generate16gNapsArray(pProvisionedNsp_t pNsp, 
									  pL4db_Nap_t pSortedNaps, 
									  UINT32 * nSortedNapsSize)
{
	BOOL				setNapFinished = FALSE, found16gName = FALSE, foundVnsp = FALSE;				
	UINT32				i, j, k, m;
	UINT32				size = 0, priority255Size = 0;
	pProvisionedNsp_t	pFoundNsp;
	size_t tempStrLen = 0;

	//first add all last detected NAPs which have 16g info. sort them according to the capl priority.
	//Naps with no capl priority are located at the end
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)//iterate through all the discovered naps
	{
		setNapFinished = FALSE;
		// if this NAP was discovered before too much time (time to live = 0), discard it
		//if(g_pL4dbContext->discoveredNaps[i].ttl < 1)
		if(FALSE == g_pL4dbContext->discoveredNaps[i].isLastDetected)
		{
			continue;
		}

		if(0 != g_pL4dbContext->discoveredNaps[i].nspInfoSize)
		{
			for(j = 0 ; j < g_pL4dbContext->discoveredNaps[i].nspInfoSize ; j++)//iterate through the nap's nsps
			{
				for(k = 0 ; k < WMX_NSP_IDS_MAX_NUM ; k++)//iterate through our nsp ids
				{
					if(L4DB_INVALID_INDEX != pNsp->nwParams.hNsps[k].nspId)
					{
						//check if the NSP IDs are equal
						if(g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID == pNsp->nwParams.hNsps[k].nspId)
						{
							if(FALSE == setNapFinished) //check that this nap hasn't been set already
							{
								//check that we have enough space to copy
								if(size < WMX_NAPS_MAX_NUM)
								{
									//our NSP is related to this NAP and it should be copied to our pre capl
									l4db_InitNap(&pSortedNaps[size]);

									l4db_CopyDiscoveredNap(&pSortedNaps[size], &g_pL4dbContext->discoveredNaps[i]);

									size++;
									setNapFinished = TRUE;
								}
							}

							//update the 16g name, if exists
							if(FALSE == found16gName)
							{
								tempStrLen = strnlen(g_pL4dbContext->discoveredNaps[i].nspInfo[j].name, WMX_NSP_NAME_MAX_SIZE);
								if(0 != tempStrLen && WMX_NSP_NAME_MAX_SIZE != tempStrLen)
								{
									OSAL_strcpy_s(pNsp->nwParams.name16g, WMX_NSP_NAME_MAX_SIZE, g_pL4dbContext->discoveredNaps[i].nspInfo[j].name);
									found16gName = TRUE;
								}
							}
						}
					}
				}

				//update the rapl info if needed
				for(k = 0 ; k < MAX_ROAMING_PARTNERS ; k++)//iterate through all the roaming partners
				{
					if(pNsp->nwParams.rapl.roamingPartners[k].vNspID == g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID)
					{
						foundVnsp = TRUE;
					}

					else //check if we have other IDs of this vNSP
					{
						pFoundNsp = l4db_GetProvisionedNspById(pNsp->nwParams.rapl.roamingPartners[k].vNspID);
						if(NULL != pFoundNsp)
						{
							//iterate through all the equivalent IDs
							for(m = 0 ; m < WMX_NSP_IDS_MAX_NUM ; m++)
							{
								if((wmx_NSPid_t)L4DB_INVALID_INDEX != pFoundNsp->nwParams.hNsps[m].nspId)
								{
									if(pFoundNsp->nwParams.hNsps[m].nspId == g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID)
									{
										foundVnsp = TRUE;
										break;
									}
								}
							}
						}

						if(TRUE == foundVnsp)
						{
							foundVnsp = FALSE;
							if(0 == strnlen(pNsp->nwParams.rapl.roamingPartners[k].vRealm16g, MAX_REALM_SIZE))
							{
								tempStrLen = strnlen(g_pL4dbContext->discoveredNaps[i].nspInfo[j].visitedRealm, MAX_REALM_SIZE);
								if(0 != tempStrLen && MAX_REALM_SIZE != tempStrLen)
								{
									OSAL_strcpy_s(pNsp->nwParams.rapl.roamingPartners[k].vRealm16g,
										MAX_REALM_SIZE,
										g_pL4dbContext->discoveredNaps[i].nspInfo[j].visitedRealm);

									break;
								}
							}
						}
					}
				}
			}
		}
	}

	//now, we need to add \ update the provisioned nap info to our naps array
	for(i = 0 ; i < pNsp->nwParams.capl.napsSize ; i++)
	{
		//check if this NAP was also discovered and therefore added already
		for(j = 0 ; j < size ; j++)
		{
			setNapFinished = FALSE;
			if(TRUE == l4db_IsNapidEqual(pNsp->nwParams.capl.naps[i].napID, pSortedNaps[j].napID))
			{
				l4db_CopyProvisionedNap(&pSortedNaps[j], &pNsp->nwParams.capl.naps[i]);

				//if this NAP has priority 255 - we remember it and reduce the nap size later
				if(pNsp->nwParams.capl.naps[i].priority >= 255)
				{
					priority255Size++;
				}

				setNapFinished = TRUE;
				break;
			}
		}
	}
	//sort the last detected 16g NAPs according to their capl priority 
	qsort(pSortedNaps, size, sizeof(pSortedNaps[0]), l4db_CompareNapPriority);

	*nSortedNapsSize = size - priority255Size;
}


/// <summary>
/// Gets the detected info for a given NAP
/// </summary>
wmx_Status_t L4DB_GetNon16gDetectedNapInfo(wmx_NAPid_t napID, pDiscoveredNap_t nap, BOOL onlyLastDetected)
{
	int i;

	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)//iterate through all the discovered naps
	{
		if (onlyLastDetected)
		{
			if(FALSE == g_pL4dbContext->discoveredNaps[i].isLastDetected)
			{
				continue;
			}
		}		
//		else
//		{
//			// if this NAP was discovered before too much time (time to live = 0), skip it
//			if(g_pL4dbContext->discoveredNaps[i].ttl < 1)			
//			{
//				continue;
//			}
//		}

		// if the NAP contains 16g info - skip it
		if(0 != g_pL4dbContext->discoveredNaps[i].nspInfoSize)
		{
			continue;
		}

		if(TRUE == l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[i].napID, napID))
		{
			OSAL_memcpy_s(nap, sizeof(DiscoveredNap_t), &g_pL4dbContext->discoveredNaps[i], sizeof(g_pL4dbContext->discoveredNaps[i]));
			return WMX_ST_OK;
		}
	}
	return WMX_ST_DATA_UNAVAILABLE;
}

wmx_Status_t GetNapsBeneathThreshold(UINT32 *numOfNaps, wmx_pNAP_t napsBeneathThreshold)
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 i, tempNumOfNAPs;
	
	if(FALSE == g_fIsInitiated)
	{
		status = WMX_ST_MODULE_NOT_INITIALIZED;

		// Nobody init US ..., you should call init function
		goto Finalize;
	}

	if (numOfNaps == NULL ||
		napsBeneathThreshold == NULL)
	{
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	if (*numOfNaps >= g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount)
	{		
		tempNumOfNAPs = 0;

		for (i = 0; i < g_pL4dbContext->tempScanResults.totalNAPsCount; ++i)
		{
			// get only the NAPs which have ONLY channels with bad link grade
			if (g_pL4dbContext->tempScanResults.isValid[i])
			{
				OSAL_memcpy_s(&napsBeneathThreshold[tempNumOfNAPs++], sizeof(wmx_NAP_t), 
					&g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[i], sizeof(wmx_NAP_t));
			}
		}
		//OSAL_memcpy_s(	napsBeneathThreshold, (*numOfNaps) * sizeof(wmx_NAP_t), 
		//			g_pL4dbContext->tempScanResults.NAPsBeneathThreshold, (*numOfNaps) * sizeof(wmx_NAP_t));

		if (tempNumOfNAPs != g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"GetNapsBeneathThreshold: - invalid NAPs count");

		}
		*numOfNaps = tempNumOfNAPs;
	}
	else
	{
		status = WMX_ST_BUFFER_TOO_SHORT;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

Finalize:
	return status;
}

// Return the index of a nap inside the last detected NAPs. Return -1 if it doesn't exist
int GetDiscoveredNapIndex(wmx_NAPid_t napId)
{
	UINT32	i;
	int res = -1;

	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)//iterate through all the discovered naps
	{
		if(TRUE == l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[i].napID, napId))
		{
			res = i;
			break;
		}
	}

	return res;
}

/// <summary>
/// Generates a sorted Nap array for a given NSP. the array consists only of last detected NAPs / NAPs with TTL>0
/// which don't have 16g info. The NAPs are sorted according to their CAPL priority
/// </summary>
static void l4db_GenerateNon16gNapsArray(pProvisionedNsp_t pNsp,
										 pL4db_Nap_t pSortedNaps,
										 UINT32 allocatedSize,
										 UINT32 * nSortedNapsSize,
										 BOOL onlyLastDetected)
{
	BOOL				setNapFinished = FALSE;				
	UINT32				i, k;
	UINT32				size = 0;

	//first add all last detected NAPs which don't have 16g info. sort them according to the capl priority.
	//Naps with no capl priority are located at the end
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)//iterate through all the discovered naps
	{
		setNapFinished = FALSE;
		if (onlyLastDetected)
		{
			if(FALSE == g_pL4dbContext->discoveredNaps[i].isLastDetected)
			{
				continue;
			}
		}
		else
		{
			// if this NAP was discovered before too much time (time to live = 0), skip it
	//		if(g_pL4dbContext->discoveredNaps[i].ttl < 1)			
	//		{
	//			continue;
	//		}
		}
		

		if(0 != g_pL4dbContext->discoveredNaps[i].nspInfoSize)
		{
			continue;
		}

		//check if this Nap exists in the NSP's CAPL, if so, add it
		for(k = 0 ; k < WMX_NAPS_MAX_NUM ; k++)
		{
			if(size < allocatedSize)
			{
				if(TRUE == l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[i].napID, 
					pNsp->nwParams.capl.naps[k].napID))
				{
					//we add the NAP only if its priority is less than 255
					if(pNsp->nwParams.capl.naps[k].priority < 255)
					{
						l4db_InitNap(&pSortedNaps[size]);

						l4db_CopyDiscoveredNap(&pSortedNaps[size], &g_pL4dbContext->discoveredNaps[i]);
						l4db_CopyProvisionedNap(&pSortedNaps[size], &pNsp->nwParams.capl.naps[k]);

						size++;
						setNapFinished = TRUE;
						break;
					}
				}
			}
		}
	}

	//sort the array according to the CAPL's priority
	qsort(pSortedNaps, size, sizeof(pSortedNaps[0]), l4db_CompareNapPriority);

	*nSortedNapsSize = size;
}

/// <summary>
/// The function runs over the channel list and merge channels that vary only in the preamble property
/// Run over the channels and add only the first occurence of each channel (channels that don't have an equal preceding channel).
/// </summary>
/// <param name="numOfChannelInfos">(IN,OUT) Number of channel infos in the list. The number of channels might decrease in the end of the function </param>
/// <param name="channelInfoList">(IN,OUT) Channel info list </param>
/// <returns>WMX_ST_OK if successful.</returns>
wmx_Status_t l4db_DeleteDuplicatedChannels(UINT32 *numOfChannelInfos, pChannelInfo_t pChannelInfoList, BOOL isComparePreambles)
{
	UINT32 i, j, k;
	wmx_Status_t rc = WMX_ST_OK;
	pChannelInfo_t tmpChannelInfoList = NULL;	
	UINT32 numOfDeletedChannels = 0;
	BOOL tmpIsComparePreambles;

	// pointers validation
	if (numOfChannelInfos == NULL ||
		pChannelInfoList == NULL)
	{
		rc = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	tmpChannelInfoList = (pChannelInfo_t)malloc(sizeof(ChannelInfo_t) * (*numOfChannelInfos));
	if (tmpChannelInfoList == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"l4db_DeleteDuplicatedChannels: error in allocating tmpChannelInfoList");
		rc = WMX_ST_FAIL;
		goto Finalize;
	}		

	// Run over all the channels and look for duplications
	for (i = 0; i < *numOfChannelInfos; i++)
	{			
		// Run over the channels preceding the channel
		for (j = 0; j < i; j++)
		{
			tmpIsComparePreambles = isComparePreambles;
			if (tmpIsComparePreambles)
			{			
				for (k = 0; k < PREAMBLES_LENGTH; k++)
				{
					if (pChannelInfoList[i].preambleBitmap[k] != 0xFF)
					{
						break;
					}
				}
				// if this channel contains all the preambles - don't add it
				// in case it already appears with specific preambles.
				// that way neighbor channels can override channels that were reported in scan results
				if (k == PREAMBLES_LENGTH)
				{
					tmpIsComparePreambles = FALSE;
				}
			}
			// Check if the two channels differ only in the preambles part
			if (l4db_IsChannelsEqual(&pChannelInfoList[i], &pChannelInfoList[j], tmpIsComparePreambles))
			{
				break;
			}
		}

		// If there is a preceding channel with the same bw, fft and freq. don't add this channel to the new list
		if (j == i)
		{
			// Add the channel to the truncated list
			tmpChannelInfoList[i - numOfDeletedChannels] = pChannelInfoList[i];
		}
		else
		{
			numOfDeletedChannels++;
		}
	}	

	// Copy the list back to the original list
	OSAL_memcpy_s(pChannelInfoList, *numOfChannelInfos * sizeof(ChannelInfo_t), tmpChannelInfoList, (*numOfChannelInfos - numOfDeletedChannels) * sizeof(ChannelInfo_t));
	*numOfChannelInfos -= numOfDeletedChannels;

Finalize:
	if (tmpChannelInfoList != NULL)
	{
		free(tmpChannelInfoList);
	}

	return rc;
}

/// <summary>
/// Remove the duplicated channels in the last detected channels list of a specific NAP
/// </summary>
/// <param name="napID">(IN) NAP to purge </param>
/// <returns>WMX_ST_OK if successful.</returns>
wmx_Status_t L4db_DeleteDuplicatedChannelsInDetectedChannels(wmx_NAPid_t napID, BOOL isComparePreambles)
{
	wmx_Status_t rc = WMX_ST_OK;
	int napIndex;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		rc = WMX_ST_MODULE_NOT_INITIALIZED;
		goto Finalize;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	napIndex = GetDiscoveredNapIndex(napID);

	if (napIndex != -1)
	{
		rc = l4db_DeleteDuplicatedChannels(	&(g_pL4dbContext->discoveredNaps[napIndex].channelPlan.channelsSize),
											g_pL4dbContext->discoveredNaps[napIndex].channelPlan.channels, isComparePreambles);
	}

	OSAL_exit_critical_section(&g_L4dbLock);

Finalize:	
	return rc;
}

/// <summary>
/// Remove the channels that differ only in the preambles property in the last detected channels list
/// </summary>
/// <returns>WMX_ST_OK if successful.</returns>
wmx_Status_t L4db_DeleteDuplicatedChannelsInAllDetectedChannels(BOOL isComparePreambles)
{
	wmx_Status_t rc = WMX_ST_OK;
	int i;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		rc = WMX_ST_MODULE_NOT_INITIALIZED;
		goto Finalize;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	// Run over the list of discovered NAPs and purge their detected channels
	for (i=0; i < WMX_NAPS_MAX_NUM; i++)
	{
		if (g_pL4dbContext->discoveredNaps[i].channelPlan.channelsSize > 0)
		{
			rc = l4db_DeleteDuplicatedChannels(	&(g_pL4dbContext->discoveredNaps[i].channelPlan.channelsSize),
					g_pL4dbContext->discoveredNaps[i].channelPlan.channels, isComparePreambles);
			
			// Only one NAP should be purged (the recent connected one)
			if (rc == WMX_ST_OK)
			{
				break;
			}
		}
	}

	OSAL_exit_critical_section(&g_L4dbLock);

Finalize:	
	return WMX_ST_OK;
}

// Add the given channel info list to the last detected channel plan and purge the last channels with the same preambles
wmx_Status_t L4db_AddNeighborAdvChannels(UINT32 numOfChannelInfos, pChannelInfo_t pChannelInfoList)
{
	wmx_Status_t status = WMX_ST_OK;
	int lastConnectedNapIndex;
	wmx_NAPid_t lastConnectedNapID;
	pDiscoveredNap_t pLastConnectedNap;
	ChannelInfo_t tmpChannelList[WMX_CHANNELS_MAX_NUM];
	UINT32 tmpListSize;
	UINT32 numOfOldChannelsToCopy;
	UINT32			i;
	char		buff[MAX_NAME_STR_LEN];
	WCHAR targetStr[MAX_NAME_STR_LEN];
	size_t lengthStr;

	if (numOfChannelInfos <= 0 ||
		numOfChannelInfos > WMX_CHANNELS_MAX_NUM || 
		pChannelInfoList == NULL)
	{
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	// We must be connected and have a last connected NAP
	if (g_pL4dbContext->generalSettings.lastConnectedNSP.numOfConnectedNapIDs <= 0)
	{
		status = WMX_ST_WRONG_STATE;
		goto Finalize;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	l4db_CopyNapID(g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[0], lastConnectedNapID);
	lastConnectedNapIndex = GetDiscoveredNapIndex(lastConnectedNapID);
	pLastConnectedNap = &(g_pL4dbContext->discoveredNaps[lastConnectedNapIndex]);
	l4db_ConvertNapIdToStr(pLastConnectedNap->napID, buff);
	mbstowcs_s(&lengthStr, targetStr, MAX_NAME_STR_LEN, buff, strlen(buff));
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Saving neighbor adv. as discovered NAP: NAP-ID=%ws, Channels:", targetStr);
	for (i = 0; i < numOfChannelInfos; ++i)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Ch %u. Frequecy: %u, Origin: %ws",
			i+1,
			pChannelInfoList[i].firstFreq,
			pChannelInfoList[i].lastFoundInNbrAdv ? L4DB_NBR_ADV : L4DB_SCAN_RESULTS);
	}

	// Copy the new NbrAdv
	OSAL_memcpy_s((pChannelInfo_t)tmpChannelList, WMX_CHANNELS_MAX_NUM * sizeof(ChannelInfo_t), 
		pChannelInfoList, numOfChannelInfos * sizeof(ChannelInfo_t));

	// Copy the old results
	if (numOfChannelInfos + pLastConnectedNap->channelPlan.channelsSize <= WMX_CHANNELS_MAX_NUM)
	{
		numOfOldChannelsToCopy = pLastConnectedNap->channelPlan.channelsSize;
		tmpListSize = numOfChannelInfos + pLastConnectedNap->channelPlan.channelsSize;
	}
	else
	{
		numOfOldChannelsToCopy = WMX_CHANNELS_MAX_NUM - numOfChannelInfos;
		tmpListSize = WMX_CHANNELS_MAX_NUM;
	}

	OSAL_memcpy_s((pChannelInfo_t)&tmpChannelList[numOfChannelInfos], WMX_CHANNELS_MAX_NUM * sizeof(ChannelInfo_t), 
				pLastConnectedNap->channelPlan.channels,numOfOldChannelsToCopy * sizeof(ChannelInfo_t));

	// Copy the list back to the original list
	OSAL_memcpy_s((pChannelInfo_t)pLastConnectedNap->channelPlan.channels, WMX_CHANNELS_MAX_NUM * sizeof(ChannelInfo_t), 
		(pChannelInfo_t)tmpChannelList,tmpListSize * sizeof(ChannelInfo_t));

	pLastConnectedNap->channelPlan.channelsSize = tmpListSize;

	// Run the l4db_DeleteDuplicatedChannels before adding the new channels
	L4db_DeleteDuplicatedChannelsInDetectedChannels(lastConnectedNapID, TRUE);
	
	OSAL_exit_critical_section(&g_L4dbLock);

Finalize:	
	return status;
}

/// <summary>
/// Get the data of a provisioned NSP including last detected discovered data 
/// </summary>
/// <param name="NSPid">(IN) NSP id </param>
/// <param name="pNSP">(OUT) the NSP data </param>
/// <returns>WMX_ST_OK if successful. WMX_ST_FAIL if the specified nspID is not provisioned </returns>
wmx_Status_t L4db_GetProvisionedNsp(wmx_NSPid_t nspID, pProvisionedNsp_t pNsp)
{
	return L4db_GetProvisionedNspEx(nspID, pNsp, TRUE);
}

/// <summary>
/// Get the data of a provisioned NSP including discovered data 
/// </summary>
/// <param name="NSPid">(IN) NSP id </param>
/// <param name="pNSP">(OUT) the NSP data </param>
/// <returns>WMX_ST_OK if successful. WMX_ST_FAIL if the specified nspID is not provisioned </returns>
wmx_Status_t L4db_GetProvisionedNspEx(wmx_NSPid_t nspID, pProvisionedNsp_t pNsp, BOOL onlyLastDetected)
{
	wmx_Status_t		rc; 
	pProvisionedNsp_t	pFoundNsp;
	pL4db_Nap_t			pNaps = NULL;
	UINT32				size16g = 0, SizeNon16g = 0, totalSize = 0;


	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	pNaps = (pL4db_Nap_t)malloc(MAX_NUM_OF_DISCOVERED_NAPS * sizeof(L4db_Nap_t));

	if(NULL == pNsp)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_GetProvisionedNsp: pNsp == NULL");
		return WMX_ST_FAIL;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	rc = WMX_ST_DATA_UNAVAILABLE;

	//get the relevant NSP from the provisioned NSPS 
	pFoundNsp = l4db_GetProvisionedNspById(nspID);

	if(NULL != pFoundNsp)
	{
		//init the struct given by the user
		l4db_InitNsp(pNsp);

		//copy the NSP we have found to the struct given by the user
		l4db_CopyProvisionedNsp(pNsp, pFoundNsp);

		rc = WMX_ST_OK;

		//create the naps array and 16g info
		l4db_Generate16gNapsArray(pNsp, pNaps, &size16g);

		l4db_GenerateNon16gNapsArray(pNsp, pNaps + size16g, MAX_NUM_OF_DISCOVERED_NAPS - size16g, &SizeNon16g, onlyLastDetected);

		totalSize = size16g  + SizeNon16g;

		if (totalSize > 0)
		{
			//copy the array we have created to the returned NSP struct and update its size
			memcpy(pNsp->nwParams.capl.naps, pNaps, totalSize * sizeof(pNsp->nwParams.capl.naps[0]));
		}
		pNsp->nwParams.capl.napsSize = totalSize;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	free(pNaps);
	return rc;
}

/// <summary>
/// Returns TRUE if the nspID is an unprovisioned profile
/// </summary>
/// <param name="NSPid">(IN) NSP id </param>
BOOL L4db_IsUnprovisionedProfile(wmx_NSPid_t nspID)
{	
	UINT32 i;
	BOOL res = FALSE;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return FALSE;
	}

	if (nspID == (wmx_NSPid_t)L4DB_INVALID_INDEX)
	{
		return FALSE;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	
	// Run over the unprovisioned profiles and look for the nspID
	for (i=0; i < g_pL4dbContext->generalSettings.unprovisionedProfilesSize; i++)
	{
		if (nspID == g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID)
		{
			res = TRUE;
			break;
		}
	}
	
	OSAL_exit_critical_section(&g_L4dbLock);

	return res;
}
/// <summary>
/// retrieve the provisioned channels of a NSP
/// <param name="nspId">(in)the specific NSP we feching the data for </param name>
/// <param name="pChannelInfoList">(out)the output list of channels per the specific provisioned nsp the num of the elements allocated mention in nChannelInfoListSize</param name>
/// <param name="pChannelInfoListSize">(IN/OUT) contain the the number of Allocated channels per current NSP and return the actual number of channel where populated in the list</param name>
/// </summary>
wmx_Status_t L4db_GetChannelsPerProvisionedNsp(wmx_NSPid_t nspId,
											   pChannelInfo_t pChannelInfoList,
											   UINT32 *pChannelInfoListSize)
{
	wmx_Status_t rc = WMX_ST_OK;
	pProvisionedNsp_t pProvisionedNspData;
	UINT32	i,j, channelInfoIndex = 0;
	UINT32 numOfChannelsInChannelInfo = 0;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	pProvisionedNspData = l4db_GetProvisionedNspById(nspId);
	
	if (NULL != pProvisionedNspData)
	{
		for(i=0; i < pProvisionedNspData->nwParams.channelPlan.channelsSize; i++)
		{
			numOfChannelsInChannelInfo = (((pProvisionedNspData->nwParams.channelPlan.channels[i].lastFreq - 
										  pProvisionedNspData->nwParams.channelPlan.channels[i].firstFreq) /
										  pProvisionedNspData->nwParams.channelPlan.channels[i].nextFreq)
										  + 1); 
			if(numOfChannelsInChannelInfo + channelInfoIndex > *pChannelInfoListSize)
			{
				rc = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
				break;
			}

			for(j=0; j < numOfChannelsInChannelInfo; j++)
			{
				//splitting the channel info into discrete channels
				OSAL_memcpy_s(&pChannelInfoList[channelInfoIndex], 
						sizeof(ChannelInfo_t),
						&pProvisionedNspData->nwParams.channelPlan.channels[i],
						sizeof(ChannelInfo_t));
				
				pChannelInfoList[channelInfoIndex].firstFreq += pChannelInfoList[channelInfoIndex].nextFreq * j;
				pChannelInfoList[channelInfoIndex].lastFreq = pChannelInfoList[channelInfoIndex].firstFreq;
				pChannelInfoList[channelInfoIndex].nextFreq = 0;

				channelInfoIndex++;
			}
		}
		
	}
	*pChannelInfoListSize = channelInfoIndex;
	OSAL_exit_critical_section(&g_L4dbLock);
	return rc;
}

/// <summary>
/// find the max size of channel list for specific provisioned Nsp 
/// <param name="nspId">(in)the specific NSP we fetching the data for </param name>
/// <param name="pChannelInfoListSize">(OUT) contain the the number of provisioned channels per NSP</param name>
/// </summary>
wmx_Status_t L4db_GetMaxChannelsPerProvisionedNsp(	wmx_NSPid_t nspId,
  													UINT32 *pChannelInfoListSize)
{
	wmx_Status_t rc = WMX_ST_OK;
	pProvisionedNsp_t pProvisionedNspData = NULL;
	UINT32 i;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}
	*pChannelInfoListSize = 0;

	OSAL_enter_critical_section(&g_L4dbLock);

	pProvisionedNspData =  l4db_GetProvisionedNspById(nspId);

	if (NULL != pProvisionedNspData)
	{
		for(i=0; i<pProvisionedNspData->nwParams.channelPlan.channelsSize; i++)
		{
			//calculate the number of channels in each channel and add to the output pChannelInfoListSize
			*pChannelInfoListSize += (((pProvisionedNspData->nwParams.channelPlan.channels[i].lastFreq -
									pProvisionedNspData->nwParams.channelPlan.channels[i].firstFreq) /
									pProvisionedNspData->nwParams.channelPlan.channels[i].nextFreq)
									+ 1);
		}
	}
	OSAL_exit_critical_section(&g_L4dbLock);
	return rc;
}

/// <summary>
/// Converts a provisioned NSP structure to the interface's structure
/// </summary>
/// <param name="provisionedNsp">(IN)the provisioned NSP </param>
/// <param name="pNspIf">(OUT) the NSP iterface structure to be filled </param>
void L4db_ConvertNspToInterface(pProvisionedNsp_t pProvisionedNsp, wmx_pNSP_t pNspIf)
{
	//TODO - finish / change this after the wmx_NSP_t interface will be closed
	UINT32 i;
	pSubscriberInfo_t pPrimarySubsc;
	size_t tempStrLen = 0;

	//copy the nsp ids
	for(i = 0 ; i < pProvisionedNsp->nwParams.hNspsSize ; i++)
	{
		pNspIf->nspIDs[i] = pProvisionedNsp->nwParams.hNsps[i].nspId;
	}

	pNspIf->numOfNspIDs = pProvisionedNsp->nwParams.hNspsSize;

	//get the 16g name, if exists. Otherwise, get the provisioned name
	tempStrLen = strnlen(pProvisionedNsp->nwParams.name16g, WMX_NSP_NAME_MAX_SIZE);
	if(0 != tempStrLen && WMX_NSP_NAME_MAX_SIZE != tempStrLen)
	{
		OSAL_strcpy_s(pNspIf->nspName, WMX_NSP_NAME_MAX_SIZE, pProvisionedNsp->nwParams.name16g);
	}
	else 
	{
		tempStrLen = strnlen(pProvisionedNsp->nwParams.provisionedName, WMX_NSP_NAME_MAX_SIZE);
		if(0 != tempStrLen && WMX_NSP_NAME_MAX_SIZE != tempStrLen)
		{
		OSAL_strcpy_s(pNspIf->nspName, WMX_NSP_NAME_MAX_SIZE, pProvisionedNsp->nwParams.provisionedName);
		}
		else
		{
			pNspIf->nspName[0] = '\0';
		}
	}

	// Check the activation state of the nsp
	if (pProvisionedNsp->nwParams.hNspsSize > 0 &&
		l4db_IsHomeNsp(pProvisionedNsp->nwParams.hNsps[0].nspId) == TRUE)
	{
		pNspIf->activated = TRUE;
	}
	else
	{
		pNspIf->activated = FALSE;
	}

	pPrimarySubsc = &pProvisionedNsp->subscriptionParams.primary;

	//add the name
	OSAL_strcpy_s(pNspIf->subscribers[0].name, WMX_SUBSCRIBER_NAME_MAX_SIZE, pPrimarySubsc->name);

	//add the id and the realm
	if(pPrimarySubsc->eapInfoSize > 1)
	{
		if (pPrimarySubsc->eapInfo[0].encaps == pPrimarySubsc->eapInfo[1].EAPMethod)
		{
			OSAL_strcpy_s(pNspIf->subscribers[0].id, WMX_SUBSCRIBER_ID_MAX_SIZE, pPrimarySubsc->eapInfo[0].id);
			
			tempStrLen = strnlen(pPrimarySubsc->eapInfo[0].realm, WMX_NSP_REALM_MAX_SIZE);
			if(0 != tempStrLen && WMX_NSP_REALM_MAX_SIZE != tempStrLen)
			{
				OSAL_strcpy_s(pNspIf->nspRealm, WMX_NSP_REALM_MAX_SIZE, pPrimarySubsc->eapInfo[0].realm);
			}
			else
			{
				pNspIf->nspRealm[0] = '\0';
			}
		}
		else if (pPrimarySubsc->eapInfo[1].encaps == pPrimarySubsc->eapInfo[0].EAPMethod)
		{
			OSAL_strcpy_s(pNspIf->subscribers[0].id, WMX_SUBSCRIBER_ID_MAX_SIZE, pPrimarySubsc->eapInfo[1].id);

			tempStrLen = strnlen(pPrimarySubsc->eapInfo[1].realm, WMX_NSP_REALM_MAX_SIZE);
			if(0 != tempStrLen && WMX_NSP_REALM_MAX_SIZE != tempStrLen)
			{
				OSAL_strcpy_s(pNspIf->nspRealm, WMX_NSP_REALM_MAX_SIZE, pPrimarySubsc->eapInfo[1].realm);
			}
			else
			{
				pNspIf->nspRealm[0] = '\0';
			}
		}
	}
	else
	{
		OSAL_strcpy_s(pNspIf->subscribers[0].id, WMX_SUBSCRIBER_ID_MAX_SIZE, pPrimarySubsc->eapInfo[0].id);

		tempStrLen = strnlen(pPrimarySubsc->eapInfo[0].realm, WMX_NSP_REALM_MAX_SIZE);
		if(0 != tempStrLen && WMX_NSP_REALM_MAX_SIZE != tempStrLen)
		{
			OSAL_strcpy_s(pNspIf->nspRealm, WMX_NSP_REALM_MAX_SIZE, pPrimarySubsc->eapInfo[0].realm);
		}
		else
		{
			pNspIf->nspRealm[0] = '\0';
		}
	}

	pNspIf->subscribers[0].userCredRequired = FALSE;
	pNspIf->subscribers[0].SLA.agreementLevel = 0;
	pNspIf->subscribers[0].SLA.downLinkSpeed = 0;
	pNspIf->subscribers[0].SLA.upLinkSpeed = 0;
	pNspIf->numOfSubscribers = 1;

	//populate other fields with default values
	pNspIf->allowGuests = FALSE;
	pNspIf->bestRssi = 0;
	pNspIf->bestCINR = 0;
	pNspIf->isRoamingPartner = FALSE;
	pNspIf->numOfRoamToNsps = 0;
	pNspIf->apdoVer = 0;
}

/// <summary>
///Gets an NSP ID for each provisioned NSP. NOTE: only one of the NSP IDs is given per NSP
///</summary>
/// <param name="pNspIds">(OUT)  an array of NSP IDs allocated by the user </param>
/// <param name="nNspsSize">(IN)  the number of elements allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               pNspIds' array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetProvisionedNspIds(wmx_pNSPid_t pNspIds, UINT32 * nNspIdsSize)
{
	wmx_Status_t		rc = WMX_ST_MODULE_NOT_INITIALIZED; 
	int					i, j;
	UINT32				actualSize = 0;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	OSAL_enter_critical_section(&g_L4dbLock);

	//iterate through all the NSPs and for each get one of its NSP IDs
	for(i = 0 ; i < WMX_NSPS_MAX_NUM ; i ++)
	{
		for(j = 0 ; j < WMX_NSP_IDS_MAX_NUM ; j++)
		{
			if((wmx_NSPid_t)L4DB_INVALID_INDEX != g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId)
			{
				//check that we have enough space in the array allocated by the user
				if(actualSize < *nNspIdsSize)
				{
					pNspIds[actualSize] = g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId;
				}
				else
				{
					rc = WMX_ST_BUFFER_TOO_SHORT;
				}
				actualSize++;
				break; //we finished handling this NSP
			}
		}
	}

	*nNspIdsSize = actualSize;
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}
/// <summary>
/// Gets the operator's name received from provisioning and 16g
/// </summary>
/// <param name="nspID">(IN)  the ID of the requested NSP</param>
/// <param name="provisionedName">(OUT) the NSP name received through provisioning. This should be allocated by the user</param>
/// <param name="nProvisionedNameSize">(IN)  the size of provisionedName allocated by the user
///			                           (OUT)The actual number of elements returned \ should be allocated in the provisionedName.</param>
/// <param name="name16g">(OUT) the NSP name received through 16g. This should be allocated by the user</param>
/// <param name="n16gNameSize">(IN)  the size of name16g allocated by the user
///			                (OUT)The actual number of elements returned \ that should be allocated in the name16g.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetNspName(wmx_NSPid_t nspID, CHAR * provisionedName, UINT32 * nProvisionedNameSize, CHAR * name16g, UINT32 * n16gNameSize)
{
	pProvisionedNsp_t	pNsp;
	UINT32				nameSize;
	int					i, k;
	UINT32				j;
	BOOL				finished = FALSE;
	BOOL				foundIndex = FALSE;
	wmx_Status_t		rc = WMX_ST_MODULE_NOT_INITIALIZED;
	size_t				tempStrLen = 0;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_DATA_UNAVAILABLE;

	if (provisionedName == NULL ||
		name16g == NULL)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}
	
	*provisionedName = '\0';
	*name16g = '\0';

	OSAL_enter_critical_section(&g_L4dbLock);

	//get the relevant provisioned NSP, if exists
	pNsp = l4db_GetProvisionedNspById(nspID);

	if(NULL != pNsp)
	{
		//handle the provisioned name
		nameSize = (UINT32)strnlen(pNsp->nwParams.provisionedName, WMX_NSP_NAME_MAX_SIZE) + 1;

		//verify that the user allocated enough space
		if(*nProvisionedNameSize < nameSize)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNspName returned WMX_ST_BUFFER_TOO_SHORT");
			rc = WMX_ST_BUFFER_TOO_SHORT;
		}

		//copy the name if possible
		if((0 != nameSize) && ((WMX_NSP_NAME_MAX_SIZE) != nameSize) && (WMX_ST_BUFFER_TOO_SHORT != rc))
		{
			OSAL_strcpy_s(provisionedName, nameSize, pNsp->nwParams.provisionedName);
			rc = WMX_ST_OK;
		}

		//update the copied size to the user
		*nProvisionedNameSize = nameSize;
	}
	else
	{
		//update the size of the provisioned name to zero
		*nProvisionedNameSize = 0;
	}

	//handle the .16g name
	nameSize = 0;
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if(FALSE == l4db_IsNapidEmpty(g_pL4dbContext->discoveredNaps[i].napID))
		{
			for(j = 0 ; j < g_pL4dbContext->discoveredNaps[i].nspInfoSize ; j++)
			{
				if(nspID == g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID)
				{
					foundIndex = TRUE;
				}
				else if(NULL != pNsp)
				{
					for(k = 0 ; k < WMX_NSP_IDS_MAX_NUM ; k++)
					{
						if(L4DB_INVALID_INDEX != pNsp->nwParams.hNsps[k].nspId)
						{
							if(g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID == pNsp->nwParams.hNsps[k].nspId)
							{
								foundIndex = TRUE;
								break;
							}
						}
					}
				}
				if(TRUE == foundIndex)//we found our NSP id or one of its equiv
				{
					foundIndex = FALSE;
					tempStrLen = strnlen(g_pL4dbContext->discoveredNaps[i].nspInfo[j].name, WMX_NSP_NAME_MAX_SIZE);
					if(0 != tempStrLen && WMX_NSP_NAME_MAX_SIZE != tempStrLen)
					{
						nameSize = (UINT32)strnlen(g_pL4dbContext->discoveredNaps[i].nspInfo[j].name, WMX_NSP_NAME_MAX_SIZE) + 1;

						//verify that the user allocated enough space
						if(*n16gNameSize < nameSize)
						{
							TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNspName returned WMX_ST_BUFFER_TOO_SHORT");
							rc =  WMX_ST_BUFFER_TOO_SHORT;
						}

						if((0 != nameSize) && ((WMX_NSP_NAME_MAX_SIZE) != nameSize) && (WMX_ST_BUFFER_TOO_SHORT != rc))
						{
							OSAL_strcpy_s(name16g, 
								nameSize, 
								g_pL4dbContext->discoveredNaps[i].nspInfo[j].name);

							rc = WMX_ST_OK;
							finished = TRUE;
							break;
						}
					}
				}
			}
		}
		if(TRUE == finished)
		{
			break;
		}
	}

	//update the 16g name size copied to the user
	if((TRUE == finished) || (WMX_ST_BUFFER_TOO_SHORT == rc))
	{
		*n16gNameSize = nameSize;
	}
	else
	{
		*n16gNameSize = 0;
	}
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Gets one of the IDs of the NSP which has the name nspName. 
/// If a 16g name exists, we will look it up first
///</summary>
/// <param name="nspName">(IN)  The requested NSP name </param>
/// <returns>L4DB_INVALID_INDEX if the name doesn't exist and its nspID otherwise</returns>
wmx_NSPid_t L4db_GetNspId(char * nspName)
{
	int			i;
	UINT32		j;
	wmx_NSPid_t nspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;

	OSAL_enter_critical_section(&g_L4dbLock);

	//first, search for this name in the discovered NSPs
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if(FALSE == l4db_IsNapidEmpty(g_pL4dbContext->discoveredNaps[i].napID))
		{
			for(j = 0 ; j < g_pL4dbContext->discoveredNaps[i].nspInfoSize ; j++)
			{
				if(FALSE == strcmp(nspName, g_pL4dbContext->discoveredNaps[i].nspInfo[j].name))
				{
					nspID =  g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID;
					OSAL_exit_critical_section(&g_L4dbLock);
					return nspID;
				}
			}
		}
	}

	//search for the name in the provisioned NSPs
	for(i = 0 ; i < WMX_NSPS_MAX_NUM; i++)
	{
		if(FALSE == strcmp(nspName, g_pL4dbContext->nsps[i].nwParams.provisionedName))
		{
			//get one of the NSP IDs
			for(j = 0 ; j < WMX_NSP_IDS_MAX_NUM ; j++)
			{
				if((wmx_NSPid_t)L4DB_INVALID_INDEX != g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId)
				{
					nspID = g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId;
					OSAL_exit_critical_section(&g_L4dbLock);
					return nspID;
				}
			}
		}
	}

	OSAL_exit_critical_section(&g_L4dbLock);
	return nspID;
}
/// <summary>
/// Gets the category of the given NSP ID
/// </summary>
/// <param name="nspID">(IN)the requested NSP ID </param>
/// <returns>NspCategory - the NSP's category</returns>
NspCategory_t L4db_GetNspCategory(wmx_NSPid_t nspID)
{
	pProvisionedNsp_t pFoundNsp;
	NspCategory_t nspCategoryResult = NotProvisioned;

	//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, L"L4db_GetNspCategory(IN). ");
	OSAL_enter_critical_section(&g_L4dbLock);

	//check if this NSP is provisioned
	pFoundNsp = l4db_GetProvisionedNspById(nspID);

	if(NULL != pFoundNsp)
	{
		if (l4db_IsHomeNsp(nspID) == TRUE)
		{
			nspCategoryResult = Home;
		}
		else
		{
			nspCategoryResult = NotHome;
		}
	}	

	//our NSP id provisioned but not home
	OSAL_exit_critical_section(&g_L4dbLock);

	//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, L"L4db_GetNspCategory(OUT). nspCategoryResult=%d",nspCategoryResult);
	return nspCategoryResult;
}

/// <summary>
//get the pNwParams per NSP ID
/// </summary>
///<param name="nspID">(IN)  wmx_NSPid_t nspID - the NSP ID.</param>
///<param name="pNwParams">(OUT) the pNwParams per the NSP</param>
/// <returns>TRUE is found a NSP per the NSP ID</returns>
wmx_Status_t L4db_GetNwParamsPerNsp(wmx_NSPid_t nspID, pNwParams_t pNwParams)
{
	wmx_Status_t status = WMX_ST_DATA_UNAVAILABLE;
	pProvisionedNsp_t pFoundNsp;

	OSAL_enter_critical_section(&g_L4dbLock);

	//check if this NSP can be found
	pFoundNsp = l4db_GetProvisionedNspById(nspID);

	if((NULL != pFoundNsp) && (NULL != pNwParams))
	{
		memcpy(pNwParams, &(pFoundNsp->nwParams),sizeof(NwParams_t));
		status = WMX_ST_OK;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return status;
}

/// <summary>
/// Gets the BEK of the last connected NSP. Only the last BEK received is stored in the DB.
/// </summary>
wmx_Status_t L4db_GetBEK( wmx_pBEKBuffer_t pBEK )
{
	OSAL_enter_critical_section(&g_L4dbLock);

	//check if this NSP is provisioned	
	wmx_memcpy(pBEK, sizeof(wmx_BEKBuffer_t), g_pL4dbContext->apdoInternalParams.bek, sizeof(wmx_BEKBuffer_t));
	
	//our NSP id provisioned but not home
	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

/// <summary>
/// Sets the BEK of the last connected NSP
/// </summary>
wmx_Status_t L4db_SetBEK( wmx_pBEKBuffer_t pBEK	)
{
	OSAL_enter_critical_section(&g_L4dbLock);

	//check if this NSP is provisioned	
	wmx_memcpy( g_pL4dbContext->apdoInternalParams.bek, sizeof(wmx_BEKBuffer_t), pBEK, sizeof(wmx_BEKBuffer_t));

	//our NSP id provisioned but not home
	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

/// <summary>
/// Checks if this is the last NSP we were connected to
/// </summary>
/// <param name="pNspID">(IN) NSP ID to check </param>
/// <returns>TRUE is this is the recent NSP</returns>
BOOL L4db_IsRecentNsp(wmx_pNSPid_t pNspID)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	pProvisionedNsp_t nsp = NULL;
	BOOL isRecent = FALSE;
	wmx_NSPid_t recentNspId = 0;
	UINT32 i;

	if(FALSE == g_fIsInitiated || pNspID == NULL)
	{
		// Nobody init US ..., you should call init function / illegal NSP ID
		return FALSE;
	}	

	OSAL_enter_critical_section(&g_L4dbLock);
	recentNspId = g_pL4dbContext->generalSettings.lastConnectedNSP.recentNspID;	
	OSAL_exit_critical_section(&g_L4dbLock);
	
	if (recentNspId == *pNspID)
	{
		return TRUE;
	}

	nsp = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));

	//there is no lock because the lock is performed within L4db_GetProvisionedNsp
	rc = L4db_GetProvisionedNsp(recentNspId, nsp);

	if (rc == WMX_ST_OK)
	{
		OSAL_enter_critical_section(&g_L4dbLock);
		for (i = 0; i < nsp->nwParams.hNspsSize; ++i)
		{
			if (nsp->nwParams.hNsps[i].nspId == *pNspID)
			{
				isRecent = TRUE;
				break;
			}
		}
		OSAL_exit_critical_section(&g_L4dbLock);
	}

	free(nsp);
	return isRecent;
}
/// <summary>
/// Gets the recent NSP we were connected to. Returns L4DB_INVALID_INDEX when there is no recent.
/// </summary>
/// <param name="pNspID">(OUT)  the recent NSP </param>
/// <returns>WMX_ST_OK if successful, WMX_ST_DATA_UNAVAILABLE if the device was not connected.</returns>
wmx_Status_t L4db_GetRecentNsp(wmx_pNSPid_t pNspID)
{
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	if (L4DB_INVALID_INDEX != g_pL4dbContext->generalSettings.lastConnectedNSP.recentNspID)
	{
		*pNspID = g_pL4dbContext->generalSettings.lastConnectedNSP.recentNspID;
		rc = WMX_ST_OK;
	}
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Gets the unprovisioned profiles
/// </summary>
/// <param name="numOfUnprovisionedProfiles">(IN/OUT)  Holds the size the user allocated in the beginning and the array size in the end</param>
/// <param name="pUnprovisionedProfiles">(IN/OUT) allocated array to get the results</param>
/// <returns>WMX_ST_OK if successful, WMX_ST_DATA_UNAVAILABLE if the device was not connected.</returns>
wmx_Status_t L4db_GetUnprovisionedProfiles(UINT32 *numOfUnprovisionedProfiles, pProfile_t pUnprovisionedProfiles)
{
	wmx_Status_t rc = WMX_ST_OK;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		rc = WMX_ST_MODULE_NOT_INITIALIZED;
		goto Finalize;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	if (*numOfUnprovisionedProfiles < g_pL4dbContext->generalSettings.unprovisionedProfilesSize)
	{
		OSAL_exit_critical_section(&g_L4dbLock);
		rc = WMX_ST_BUFFER_TOO_SHORT;
		goto Finalize;
	}

	if (g_pL4dbContext->generalSettings.unprovisionedProfilesSize > 0)
	{
		OSAL_memcpy_s(	pUnprovisionedProfiles, 
					*numOfUnprovisionedProfiles * sizeof(Profile_t),
					g_pL4dbContext->generalSettings.unprovisionedProfiles,
					g_pL4dbContext->generalSettings.unprovisionedProfilesSize * sizeof(Profile_t));
	}
	*numOfUnprovisionedProfiles = g_pL4dbContext->generalSettings.unprovisionedProfilesSize;

	OSAL_exit_critical_section(&g_L4dbLock);

Finalize:
	return rc;
}

/// <summary>
/// Gets the current preferred NSP (the user's favorite NSP)
/// </summary>
/// <param name="pNspID">(OUT) the current preferred NSP </param>
/// <returns>WMX_ST_OK if successful.</returns>
wmx_Status_t L4db_GetCurrentPreferredNsp(wmx_pNSPid_t pCurrentPreferredNspID)
{
	wmx_Status_t rc = WMX_ST_DATA_UNAVAILABLE;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	if (L4DB_INVALID_INDEX != g_pL4dbContext->generalSettings.currentPreferredNSP)
	{
		*pCurrentPreferredNspID = g_pL4dbContext->generalSettings.currentPreferredNSP;	
		rc = WMX_ST_OK;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Sets the current preferred NSP (the user's favorite NSP)
/// </summary>
/// <param name="pNspID">(IN) the current preferred NSP </param>
/// <returns>WMX_ST_OK if successful. WMX_ST_WRONG_ARGUMENT if the currentPreferredNspID is already the preferred one</returns>
wmx_Status_t L4db_SetCurrentPreferredNsp(wmx_NSPid_t currentPreferredNspID)
{
	wmx_Status_t rc = WMX_ST_OK;
	wmx_UserConnectMode_t connectMode;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		rc = WMX_ST_MODULE_NOT_INITIALIZED;
		goto Finalize;
	}		

	if (currentPreferredNspID == L4DB_INVALID_INDEX)
	{
		connectMode = L4db_GetConnectMode();

		// Current preferred NSP can't be set to NULL when the connect mode is Auto connect
		if (connectMode == UserAutoScanAutoConnect ||
			connectMode == UserSemiManScanAutoConnect)
		{
			rc = WMX_ST_WRONG_STATE;
			goto Finalize;
		}
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	if (g_pL4dbContext->generalSettings.currentPreferredNSP != currentPreferredNspID)
	{
		g_pL4dbContext->generalSettings.currentPreferredNSP = currentPreferredNspID;

		if (currentPreferredNspID != L4DB_INVALID_INDEX)
		{		
			// Add an unprovisioned profile if needed
			L4db_AddUnprovisionedProfile(currentPreferredNspID);
		}
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

Finalize:
	return rc;
}

/// <summary>
/// The function returns TRUE if nspId is the current preferred NSP; FALSE otherwise
/// </summary>
BOOL L4db_IsCurrentPreferredNSP(wmx_NSPid_t nspId)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	ProvisionedNsp_t nsp;
	BOOL isCurrent = FALSE;	
	wmx_NSPid_t currentNspId = 0;
	UINT32 i;

	if(FALSE == g_fIsInitiated || nspId == (wmx_NSPid_t)L4DB_INVALID_INDEX)
	{
		// Nobody init US ..., you should call init function / illegal NSP ID
		return FALSE;
	}	
	
	rc = L4db_GetCurrentPreferredNsp(&currentNspId);
	if (rc != WMX_ST_OK ||
		currentNspId == (wmx_NSPid_t)L4DB_INVALID_INDEX)
	{
		goto Finalize;
	}

	if (currentNspId == nspId)
	{
		isCurrent = TRUE;
		goto Finalize;
	}

	
	rc = L4db_GetProvisionedNsp(currentNspId, &nsp);

	if (rc != WMX_ST_OK)
	{
		goto Finalize;
	}
		
	// Run over all the IDs of the current preferred NSP. check if they are equal to nspId.
	for (i = 0; i < nsp.nwParams.hNspsSize; ++i)
	{
		if (nsp.nwParams.hNsps[i].nspId == nspId)
		{
			isCurrent = TRUE;
			goto Finalize;
		}
	}

Finalize:
	return isCurrent;
}

// [Ely Oran check]
wmx_Status_t L4db_GetUnprovisionedProfilesList(pProfile_t unprovisionedProfiles, UINT32 *unprovisionedProfilesSize)
{
	UINT32			actualUnprovisionedProfilesSize = 0, i;
	wmx_Status_t    rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_FAIL;

	OSAL_enter_critical_section(&g_L4dbLock);

	//calculate the the number of NSPs in the recent NSP list
	for(i = 0 ; i < MAX_NUM_OF_RECENT_NSPS ; i++)
	{
		if(L4DB_INVALID_INDEX != g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID)
		{
			//verify there is enough allocated space
			if(actualUnprovisionedProfilesSize < *unprovisionedProfilesSize)
			{
				unprovisionedProfiles[i] = g_pL4dbContext->generalSettings.unprovisionedProfiles[i];
			}

			actualUnprovisionedProfilesSize++;
		}
	}

	//verify that the user allocated enough space for the recent NSPs
	if(*unprovisionedProfilesSize < actualUnprovisionedProfilesSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetRecentNspList returned WMX_ST_BUFFER_TOO_SHORT");
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		rc = WMX_ST_OK;
	}

	//update the copied size for the user
	*unprovisionedProfilesSize = actualUnprovisionedProfilesSize;

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}
//the function return the unprovisioned element per specific Nsp
//if there is no such nsp in the unprovisioned DB the return value will be WMX_ST_NSP_ID_NOT_FOUND
wmx_Status_t L4db_GetUnprovisionedProfilePerNspID(wmx_NSPid_t nspId, pProfile_t pUnprovisioned)
{
	wmx_Status_t rc = WMX_ST_OK;
	UINT32 i;

	if (NULL != pUnprovisioned)
	{
		if(FALSE == g_fIsInitiated)
		{
			rc = WMX_ST_MODULE_NOT_INITIALIZED;
			// Nobody init US ..., you should call init function
			return rc;
		}

		rc = WMX_ST_NSP_ID_NOT_FOUND;

		OSAL_enter_critical_section(&g_L4dbLock);
		for(i = 0 ; i < g_pL4dbContext->generalSettings.unprovisionedProfilesSize ; i++)
		{			
			if(nspId == g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID)
			{
				OSAL_memcpy_s(pUnprovisioned, sizeof(Profile_t), &g_pL4dbContext->generalSettings.unprovisionedProfiles[i], sizeof(Profile_t));
				rc = WMX_ST_OK;
				break;
			}
		}
		OSAL_exit_critical_section(&g_L4dbLock);
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}
	return rc;
}

UINT32 L4db_GetMaxDetectedChannelPerNap(wmx_NAPid_t napId)
{	
	UINT32 i, res;

	if(FALSE == g_fIsInitiated)
	{				
		return 0;
	}

	res = 0;

	OSAL_enter_critical_section(&g_L4dbLock);

	// Look for the given NAP
	for (i = 0; i < WMX_NAPS_MAX_NUM; i++)
	{
		if(TRUE == l4db_IsNapidEqual(napId, g_pL4dbContext->discoveredNaps[i].napID))
		{
			res = g_pL4dbContext->discoveredNaps[i].channelPlan.channelsSize;
			break;
		}		
	}
	
	OSAL_exit_critical_section(&g_L4dbLock);

	return res;
}

wmx_Status_t L4db_GetDetectedChannelPerNap(wmx_NAPid_t napId,
										   pChannelPlan_t pChannelPlan)
{	
	UINT32 i;
	wmx_Status_t    rc = WMX_ST_OK;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	pChannelPlan->channelsSize = 0;

	OSAL_enter_critical_section(&g_L4dbLock);

	// Look for the given NAP
	for (i = 0; i < WMX_NAPS_MAX_NUM; i++)
	{
		if(TRUE == l4db_IsNapidEqual(napId, g_pL4dbContext->discoveredNaps[i].napID))
		{
			OSAL_memcpy_s(pChannelPlan, sizeof(ChannelPlan_t), &g_pL4dbContext->discoveredNaps[i].channelPlan, sizeof(ChannelPlan_t));
			break;
		}		

	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

//the function return the unprovisioned element per specific Nsp
//if there is no such nsp in the unprovisioned DB the return value will be WMX_ST_NSP_ID_NOT_FOUND
wmx_Status_t L4db_GetProvisionedPerNspID(wmx_NSPid_t nspId, pProvisionedNsp_t pProvisioned)
{
	wmx_Status_t rc = WMX_ST_OK;
	pProvisionedNsp_t pLocalProvisioned; // use to get the resault from the function and to copy it to the output param

	if (NULL != pProvisioned)
	{
		if(FALSE == g_fIsInitiated)
		{
			// Nobody init US ..., you should call init function
			return WMX_ST_MODULE_NOT_INITIALIZED;
		}

		OSAL_enter_critical_section(&g_L4dbLock);
		pLocalProvisioned = l4db_GetProvisionedNspById(nspId);
		if(NULL == pLocalProvisioned)
		{
			rc = WMX_ST_NSP_ID_NOT_FOUND;
		}
		else
		{
			OSAL_memcpy_s(pProvisioned, sizeof(ProvisionedNsp_t), pLocalProvisioned, sizeof(ProvisionedNsp_t));
		}

		OSAL_exit_critical_section(&g_L4dbLock);
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;
	}
	return rc;
}


// Add channels to the unprovisioned profile from the detected NAPs array. Make sure that there are no duplications
wmx_Status_t L4db_AddChannelPlanToUnprovisionedProfile(wmx_NSPid_t nspID)
{
	wmx_Status_t rc = WMX_ST_OK;
	UINT32 i, j, k, l;
	wmx_NAPid_t napID;
	pChannelPlan_t pChannelPlan, pToAddChannelPlan;
	int lastChannelToMove, channelIndex;

	if(FALSE == g_fIsInitiated)
	{
		rc = WMX_ST_MODULE_NOT_INITIALIZED;
		// Nobody init US ..., you should call init function
		return rc;
	}	

	if (nspID == (wmx_NSPid_t)L4DB_INVALID_INDEX)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	// Check if the profile exists
	for(i = 0 ; i < g_pL4dbContext->generalSettings.unprovisionedProfilesSize ; i++)
	{
		if (g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID == nspID)
		{	
			pChannelPlan = &g_pL4dbContext->generalSettings.unprovisionedProfiles[i].channelPlan;
			break;
		}
	}

	// If the profile exists
	if (i < g_pL4dbContext->generalSettings.unprovisionedProfilesSize)
	{
		l4db_ConvertNapIdIntToNapIdType(napID, nspID); // look for a napID that is equal to the nspID

		for (j = 0; j < MAX_NUM_OF_DISCOVERED_NAPS; j++)
		{
			if (l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[j].napID, napID) == TRUE)
			{
				pToAddChannelPlan = &g_pL4dbContext->discoveredNaps[j].channelPlan;
				break;				
			}
		}

		// If there is an equal NAP in the discovered NAPs array
		if (j < MAX_NUM_OF_DISCOVERED_NAPS)
		{
			// Add the channel infos that doesn't exist yet
			for (k = 0; k < pToAddChannelPlan->channelsSize; k++)
			{
				for (l = 0; l < pChannelPlan->channelsSize; l++)
				{	
					if (pToAddChannelPlan->channels[k].bw == pChannelPlan->channels[l].bw &&
						pToAddChannelPlan->channels[k].fft == pChannelPlan->channels[l].fft &&
						pToAddChannelPlan->channels[k].firstFreq == pChannelPlan->channels[l].firstFreq)
					{
						break;
					}
				}

				// The channel info is new, add it
				if (l == pChannelPlan->channelsSize)
				{
					// Add the new channel info to the beginning of the array and move the rest of the channels one to the right
					if (pChannelPlan->channelsSize < WMX_CHANNELS_MAX_NUM)
					{
						lastChannelToMove = (int)pChannelPlan->channelsSize - 1;
						pChannelPlan->channelsSize++;
					}
					else
					{
						lastChannelToMove = WMX_CHANNELS_MAX_NUM - 2; // the last channel info will be deleted
					}

					// Can't use memcpy because there are overlapping ranges
					for (channelIndex = lastChannelToMove; channelIndex >= 0; channelIndex--)
					{
						pChannelPlan->channels[channelIndex + 1] = pChannelPlan->channels[channelIndex];
					}

					pChannelPlan->channels[0] = pToAddChannelPlan->channels[k];					
				}
			}

		}				
	}
	else
	{
		rc = WMX_ST_WRONG_ARGUMENT;		
	}


	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

wmx_Status_t L4db_AddUnprovisionedProfile(wmx_NSPid_t nspID)
{
	int				i;
	wmx_Status_t    rc = WMX_ST_MODULE_NOT_INITIALIZED;
	BOOL			bExist = FALSE;
	int				lastIndexToMove;
	wmx_NAPid_t		napID;
	pProvisionedNsp_t	pFoundNsp;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_FAIL;

	OSAL_enter_critical_section(&g_L4dbLock);

	//chack if the nspId is a provisioned one
	
	pFoundNsp = l4db_GetProvisionedNspById(nspID);
	if(NULL != pFoundNsp)
	{
		OSAL_exit_critical_section(&g_L4dbLock);
		return WMX_ST_NSP_ID_NOT_FOUND;
	}
	
	// Check if the profile exists
	for(i = 0 ; i < (int)g_pL4dbContext->generalSettings.unprovisionedProfilesSize ; i++)
	{
		if (g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID == nspID)
		{
			bExist = TRUE;
			break;
		}
	}

	if (!bExist)
	{
		// Add a new profile to the beginning of the list and move the rest forward
		if (g_pL4dbContext->generalSettings.unprovisionedProfilesSize < MAX_NUM_OF_RECENT_NSPS)	
		{
			lastIndexToMove = g_pL4dbContext->generalSettings.unprovisionedProfilesSize - 1;
			g_pL4dbContext->generalSettings.unprovisionedProfilesSize++;
		}
		else
		{
			lastIndexToMove = MAX_NUM_OF_RECENT_NSPS - 2; // The last profile will be deleted
		}

		for (i=lastIndexToMove; i >= 0; i--)
		{
			g_pL4dbContext->generalSettings.unprovisionedProfiles[i+1] = g_pL4dbContext->generalSettings.unprovisionedProfiles[i];
		}
		
		l4db_InitChannelPlan(&g_pL4dbContext->generalSettings.unprovisionedProfiles[0].channelPlan);
		g_pL4dbContext->generalSettings.unprovisionedProfiles[0].nspID = nspID;
		l4db_ConvertNapIdIntToNapIdType(napID, nspID);
		OSAL_memcpy_s(g_pL4dbContext->generalSettings.unprovisionedProfiles[0].napID, sizeof(wmx_NAPid_t), napID, sizeof(wmx_NAPid_t));
	}

	// if the profile already exists - just update its detected channels
	L4db_AddChannelPlanToUnprovisionedProfile(nspID);

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Updates the connected NAP ID, assumes that the connected NSP is updated later
/// </summary>
/// <param name="napID">(IN)  the NAP ID we are connected to </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetConnectedNap(wmx_NAPid_t napID)
{
	int i, j;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	// Check if the new NSP is the same like the old one
	if (g_pL4dbContext->generalSettings.lastConnectedNSP.recentNspID == Ndns_GetConnectingNSPTemp())
	{
		// Add the NAP to the previous NSP

		// Check if the new NAP exists
		for (i=0; i < (int)g_pL4dbContext->generalSettings.lastConnectedNSP.numOfConnectedNapIDs; i++)
		{
			if (g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[i][0] == napID[0] &&
				g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[i][1] == napID[1] &&
				g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[i][2] == napID[2])
			{
				break;
			}			
		}

		if (i < (int)g_pL4dbContext->generalSettings.lastConnectedNSP.numOfConnectedNapIDs)
		{
			// The NAP exists
			j=i-1;			
		}
		else
		{
			// The NAP doesn't exist
			j = (i == WMX_NAPS_MAX_NUM ? i - 2 : i - 1);  // Delete one NAP if the array is full
			g_pL4dbContext->generalSettings.lastConnectedNSP.numOfConnectedNapIDs++;
		}

		// Move the NAPs one ahead until the end or where the new NAP exists
		for (; j >= 0; j--)
		{
			l4db_CopyNapID(g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[j],
				(wmx_pNAPid_t)&g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[j+1]);
		}

		// Add the new NAP to the beginning of the array
		l4db_CopyNapID(napID, (wmx_pNAPid_t)&g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[0]);
	}	
	else
	{
		// Connecting to a new NSP
		l4db_CopyNapID(napID, g_pL4dbContext->generalSettings.lastConnectedNSP.lastConnectedNapIDs[0]);
		g_pL4dbContext->generalSettings.lastConnectedNSP.numOfConnectedNapIDs = 1;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}
/// <summary>
/// Updates the connected NSP
/// </summary>
/// <param name="nspID">(IN)  the NSP ID we are connected to </param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetConnectedNsp(wmx_NSPid_t nspID)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->generalSettings.lastConnectedNSP.recentNspID = nspID;

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

/// <summary>
/// finds the EAP entry with MSCHAPv2 (if any)
/// and update the username and password nodes in the EAP.
/// </summary>
wmx_Status_t L4db_SetEapNode(wmx_NSPid_t nspID, 
							 CHAR *username,
							 CHAR *password)
{
	int eapMethodIndex = -1;
	UINT32 i;
	pProvisionedNsp_t provisioned_nsp = NULL;
	pSubscriberInfo_t eapArray = NULL;
	size_t usernameLen, passwordLen;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	provisioned_nsp = l4db_GetProvisionedNspById(nspID);

	eapArray = &provisioned_nsp->subscriptionParams.primary;
	for (i = 0 ; i < eapArray->eapInfoSize ; i++)
	{
		if(eapArray->eapInfo[i].EAPMethod == WMX_PLAIN_MSCHAPv2)
		{
			eapMethodIndex = i;
			break;
		}
	}	

	// Make sure there was an entry with MSCHAPv2 otherwise return fail
	if (eapMethodIndex == -1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"L4db_SetEapNode failed to find EAP entry with MSCHAPv2");
		OSAL_exit_critical_section(&g_L4dbLock);
		return WMX_ST_FAIL;
	}

	//TODO: Verify str len
	usernameLen = strnlen(username, WMX_SUBSCRIBER_ID_MAX_SIZE);
	if(WMX_SUBSCRIBER_ID_MAX_SIZE == usernameLen)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_SetEapNode failed - username is too long");
		OSAL_exit_critical_section(&g_L4dbLock);
		return WMX_ST_FAIL;
	}

	passwordLen = strnlen(password, MAX_EAP_PASSWORD_SIZE);
	if(MAX_EAP_PASSWORD_SIZE == passwordLen)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_SetEapNode failed - password is too long");
		OSAL_exit_critical_section(&g_L4dbLock);
		return WMX_ST_FAIL;
	}

	wmx_strncpy(eapArray->eapInfo[eapMethodIndex].id, WMX_SUBSCRIBER_ID_MAX_SIZE, 
		username, usernameLen);//change username
	L4db_SetEncryptedPassword(eapArray->eapInfo[eapMethodIndex].Password, password);//change password

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}


/// <summary>
/// Deprovisions Unprovisioned NSP
/// </summary>
wmx_Status_t l4db_DeAllocUnprovisionedNSP(wmx_NSPid_t nspID)
{
	UINT32 i;
	BOOL isExist = FALSE;

	for(i=0; i < g_pL4dbContext->generalSettings.unprovisionedProfilesSize; i++)
	{
		if (nspID == g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID)
		{
			isExist = TRUE;
			break;
		}
	}
	if(isExist)
	{
		//the profile need to be deleted locate in position i
		for(;i<g_pL4dbContext->generalSettings.unprovisionedProfilesSize - 1; i++)
		{
			//move the rest of the array one place forward
			OSAL_memcpy_s(&g_pL4dbContext->generalSettings.unprovisionedProfiles[i],
					sizeof(Profile_t),
					&g_pL4dbContext->generalSettings.unprovisionedProfiles[i + 1],
					sizeof(Profile_t));
		}

		//delete the last profile 
		g_pL4dbContext->generalSettings.unprovisionedProfiles[i].nspID = (wmx_NSPid_t)L4DB_INVALID_INDEX;
		l4db_SetNapidEmpty((wmx_pNAPid_t)&g_pL4dbContext->generalSettings.unprovisionedProfiles[i].napID);
		l4db_InitChannelPlan((pChannelPlan_t)&g_pL4dbContext->generalSettings.unprovisionedProfiles[i].channelPlan);
		g_pL4dbContext->generalSettings.unprovisionedProfilesSize--;

	}
	return WMX_ST_OK;
}

/// <summary>
/// Deprovisions an NSP
/// </summary>
wmx_Status_t L4db_DeProvisionNsp(wmx_NSPid_t nspID)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	if(!g_fIsInitiated )
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	l4db_DeAllocNsp(nspID);
	l4db_DeAllocUnprovisionedNSP(nspID);
	rc = WMX_ST_OK;

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Gets the NDnS general settings
/// </summary>
wmx_Status_t L4db_GetNdsSettings(pNdsSettings_t pSettings)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNdsSettings(IN)");
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNdsSettings(OUT). FALSE == g_fIsInitiated");
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	memcpy(pSettings, &g_pL4dbContext->generalSettings, sizeof(*pSettings));		

	rc = WMX_ST_OK;
	OSAL_exit_critical_section(&g_L4dbLock);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNdsSettings(OUT)");
	return rc;
}
/// <summary>
/// sets the NDnS general settings
/// </summary>
wmx_Status_t L4db_SetNdsSettings(NdsSettings_t settings)
{
	wmx_Status_t	rc = WMX_ST_FAIL;
	UINT32				i;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//set the RF state
	if((settings.swRfState >= Off) && (settings.swRfState <= On))
	{
		g_pL4dbContext->generalSettings.swRfState = settings.swRfState ;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetNdsSettings: set RF state error (%d)", settings.swRfState);
		OSAL_exit_critical_section(&g_L4dbLock);
		return WMX_ST_FAIL;
	}

	//set the TH criteria
	g_pL4dbContext->generalSettings.thCriteria = settings.thCriteria;

	//set allow auto activate
	g_pL4dbContext->generalSettings.allowAutoActivate = settings.allowAutoActivate;

	//set allow fast reconnect
	g_pL4dbContext->generalSettings.allowFastReconnect = settings.allowFastReconnect;

	//set short link loss parameters
	g_pL4dbContext->generalSettings.shortLinkLossParams.time = 
		settings.shortLinkLossParams.time;

	g_pL4dbContext->generalSettings.shortLinkLossParams.repetition = 
		settings.shortLinkLossParams.repetition;

	//set long link loss parameters
	g_pL4dbContext->generalSettings.longLinkLossParams.time = 
		settings.longLinkLossParams.time; 

	g_pL4dbContext->generalSettings.longLinkLossParams.repetition = 
		settings.longLinkLossParams.repetition; 

	//set the connection mode
	if((settings.connectMode >= UserSemiManScanManConnect) && (settings.connectMode <= UserManScanManConnect))
	{
		g_pL4dbContext->generalSettings.connectMode = settings.connectMode; 
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetNdsSettings: set connection mode error");
		OSAL_exit_critical_section(&g_L4dbLock);
		return rc;
	}

	g_pL4dbContext->generalSettings.currentPreferredNSP = 
		settings.currentPreferredNSP;

	g_pL4dbContext->generalSettings.lastConnectedNSP = 
		settings.lastConnectedNSP;

	//set the recent connected NSPs
	//verify that the user didn't give an array size which is too big
	if(MAX_NUM_OF_RECENT_NSPS < settings.unprovisionedProfilesSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_SetNdsSettings: max size of unprovisioned profiles is %d", MAX_NUM_OF_RECENT_NSPS);
		OSAL_exit_critical_section(&g_L4dbLock);
		return WMX_ST_FAIL;
	}

	for(i = 0 ; i < settings.unprovisionedProfilesSize ; i++)
	{
		g_pL4dbContext->generalSettings.unprovisionedProfiles[i] = settings.unprovisionedProfiles[i];
	}

	g_pL4dbContext->generalSettings.unprovisionedProfilesSize = settings.unprovisionedProfilesSize;

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}


void L4db_PrintDiscoveredNAPsList()
{
	UINT32			i, j;
	char		buff[MAX_NAME_STR_LEN];
	WCHAR targetStr[MAX_NAME_STR_LEN];
	size_t lengthStr;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Updated discovered NAPs list:");

	OSAL_enter_critical_section(&g_L4dbLock);

	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; ++i)
	{
		if (FALSE == l4db_IsNapidEmpty(g_pL4dbContext->discoveredNaps[i].napID))
		{
			l4db_ConvertNapIdToStr(g_pL4dbContext->discoveredNaps[i].napID, buff);
			mbstowcs_s(&lengthStr, targetStr, MAX_NAME_STR_LEN, buff, strlen(buff));
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Discovered NAP at location %u: NAP-ID=%ws, Channels:", i, targetStr);
			for (j = 0; j < g_pL4dbContext->discoveredNaps[i].channelPlan.channelsSize; ++j)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Ch %u. Frequecy: %u, Origin: %ws",
					j+1,
					g_pL4dbContext->discoveredNaps[i].channelPlan.channels[j].firstFreq,
					g_pL4dbContext->discoveredNaps[i].channelPlan.channels[j].lastFoundInNbrAdv ? L4DB_NBR_ADV : L4DB_SCAN_RESULTS);
			}		
		}
	}
	OSAL_exit_critical_section(&g_L4dbLock);
}
/// <summary>
/// Sets the discovered NAP Information for a specific NAP ID
/// </summary>
/// <param name="napInfo">(IN) the discovered NAP info to be updated.
/// if the nap Id already exists, its data will be overriden</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetDiscoveredNapInfo(pDiscoveredNap_t napInfo)
{
	UINT32			i, j, index = MAX_NUM_OF_DISCOVERED_NAPS - 1;
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;
	char		buff[MAX_NAME_STR_LEN];
	WCHAR targetStr[MAX_NAME_STR_LEN];
	size_t lengthStr;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	l4db_ConvertNapIdToStr(napInfo->napID, buff);
	mbstowcs_s(&lengthStr, targetStr, MAX_NAME_STR_LEN, buff, strlen(buff));
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Saving discovered NAP: NAP-ID=%ws, Channels:", targetStr);
	for (i = 0; i < napInfo->channelPlan.channelsSize; ++i)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"Ch %u. Frequecy: %u, Origin: %ws",
			i+1,
			napInfo->channelPlan.channels[i].firstFreq,
			napInfo->channelPlan.channels[i].lastFoundInNbrAdv ? L4DB_NBR_ADV : L4DB_SCAN_RESULTS);
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//check if the relevant NAP Id already exists, remove it if so
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if((TRUE == l4db_IsNapidEqual(napInfo->napID, g_pL4dbContext->discoveredNaps[i].napID)) ||
			(TRUE == l4db_IsNapidEmpty(g_pL4dbContext->discoveredNaps[i].napID)))
		{
			if (TRUE == l4db_IsNapidEqual(napInfo->napID, g_pL4dbContext->discoveredNaps[i].napID))
			{
				// Add the channel plan of the previous NAP to the new NAP.
				l4db_MergeChannelPlans(&napInfo->channelPlan, &g_pL4dbContext->discoveredNaps[i].channelPlan, FALSE);
			}

			index = i;
			break;
		}
	}


	//shift the discovered NAPs to the right up to its index
	for(j = index ; j > 0 ; j--)
	{
		memcpy(&g_pL4dbContext->discoveredNaps[j],
			&g_pL4dbContext->discoveredNaps[j - 1],
			sizeof(g_pL4dbContext->discoveredNaps[j]));
	}

	//update the recent discovered nap info
	g_pL4dbContext->discoveredNaps[0].changeCount = napInfo->changeCount; //change count
	g_pL4dbContext->discoveredNaps[0].isLastDetected = napInfo->isLastDetected; //last detected	
	g_pL4dbContext->discoveredNaps[0].nspInfoSize = napInfo->nspInfoSize; //nsp info size
	memcpy(&g_pL4dbContext->discoveredNaps[0].nspInfo, &napInfo->nspInfo, //nsp info
		sizeof(g_pL4dbContext->discoveredNaps[0].nspInfo));
	memcpy(g_pL4dbContext->discoveredNaps[0].napID, napInfo->napID, //nap info
		sizeof(g_pL4dbContext->discoveredNaps[0].napID));

	//copy the channel plan and init the relevant places
	l4db_CopyChannelPlanWithInit(&g_pL4dbContext->discoveredNaps[0].channelPlan, &napInfo->channelPlan);

	OSAL_exit_critical_section(&g_L4dbLock);
	L4db_PrintDiscoveredNAPsList();

	return rc;
}

/// <summary>
/// Gets the discovered NAP Information, received from .16g or scanning process, for a specific NAP ID
/// </summary>
/// <param name="napID">(IN)  the nap ID for which we request NAP info for </param>
/// <param name="pDiscoveredNap">(OUT) a discovered nap struct</param>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_GetDiscoveredNapInfo(wmx_NAPid_t napID, pDiscoveredNap_t pDiscoveredNap)
{
	int				i;
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_DATA_UNAVAILABLE;

	OSAL_enter_critical_section(&g_L4dbLock);

	//search for the requested NAP ID
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if(TRUE == l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[i].napID, napID))
		{
			memcpy(pDiscoveredNap, &g_pL4dbContext->discoveredNaps[i], sizeof(g_pL4dbContext->discoveredNaps[0]));

			rc = WMX_ST_OK;
			break;
		}
	}


	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}
/// <summary>
/// find the max possible size of detected channel list of all the NAPs
/// <param name="pChannelInfoListSize">(OUT) contain the the number of detected channels of all the NAPs </param name>
/// </summary>
wmx_Status_t L4db_GetMaxDetectedChannels(UINT32 *pChannelInfoListSize)
{
	UINT32			i;
	wmx_Status_t	rc = WMX_ST_OK;
	wmx_NAPid_t		invalidNapId;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	if (pChannelInfoListSize == NULL )
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	l4db_SetNapidEmpty(invalidNapId);
	*pChannelInfoListSize = 0;

	OSAL_enter_critical_section(&g_L4dbLock);

	//search for the requested NAP ID
	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[i].napID, invalidNapId))
		{
			*pChannelInfoListSize += g_pL4dbContext->discoveredNaps[i].channelPlan.channelsSize;
		}		
	}
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}
/// <summary>
/// Get all the discovered naps
/// </summary>
/// <param name="pDiscoveredNapList">(OUT)  the list of the discovered nap info (should be allocated by the user) </param>
/// <param name="pNumOfNaps">(IN/OUT) the number of the naps in the list</param>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_GetAllDiscoveredNapsInfoList(pDiscoveredNap_t pDiscoveredNapList, UINT32 *pNumOfNaps)
{
	UINT32			i, numOfCopiedNaps = 0;
	wmx_Status_t	rc = WMX_ST_OK;
	wmx_NAPid_t		invalidNapId;


	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	if (pNumOfNaps == NULL ||
		pDiscoveredNapList == NULL)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}
	
	l4db_SetNapidEmpty(invalidNapId);

	OSAL_enter_critical_section(&g_L4dbLock);

	//search for the requested NAP ID
	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		if(FALSE == l4db_IsNapidEqual(g_pL4dbContext->discoveredNaps[i].napID, invalidNapId))
		{
			// Make sure the list is large enough
			if (numOfCopiedNaps >= *pNumOfNaps)
			{
				return WMX_ST_BUFFER_TOO_SHORT;
			}

			//copy the nap into the output list
			OSAL_memcpy_s(&pDiscoveredNapList[numOfCopiedNaps], sizeof(DiscoveredNap_t), &g_pL4dbContext->discoveredNaps[i], sizeof(DiscoveredNap_t));
			numOfCopiedNaps++;			
		}		
	}

	*pNumOfNaps = numOfCopiedNaps;
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Resets the Last detected NAPs so they become "old detected" NAPS
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_ResetLastDetectedNaps()
{
	int i;
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	OSAL_enter_critical_section(&g_L4dbLock);

	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		g_pL4dbContext->discoveredNaps[i].isLastDetected = FALSE;
		L4db_DecreaseTtlForAllDetectedChannels();
		// reset the temp scan results beneath the threshold
		g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount = 0;
		g_pL4dbContext->tempScanResults.totalNAPsCount = 0;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Decrease the TTL value of all detected channels
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_DecreaseTtlForAllDetectedChannels()
{
	int i, j, numOfChannels;
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	OSAL_enter_critical_section(&g_L4dbLock);
	
	// TODO: Ely Add a counter to the amount of discovered NAPs in the DB (instead of running over all the list)
	// TODO: Ely do we need to check if the NAP is legal/available?
	// Run over the detected NAPs and for each one over its detected channels
	for(i = 0; i < MAX_NUM_OF_DISCOVERED_NAPS; i++)
	{		
		numOfChannels = g_pL4dbContext->discoveredNaps[i].channelPlan.channelsSize;
		for(j = 0; j < numOfChannels; j++)
		{
			// The TTL of the Neighbor advertisement is decreased only when the NbrAdv is coming
			if (g_pL4dbContext->discoveredNaps[i].channelPlan.channels[j].lastFoundInNbrAdv == FALSE)
			{			
				// Don't decrease the TTL under 1. Use this assumption in the L4 planner
				g_pL4dbContext->discoveredNaps[i].channelPlan.channels[j].ttl > 1 ? --g_pL4dbContext->discoveredNaps[i].channelPlan.channels[j].ttl : 1;
			}			
		}
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// change the detection status of a specified nap
/// </summary>
/// <returns>wmx_Status_t</returns>
wmx_Status_t L4db_SetDetectedNapFlag(wmx_pNAPid_t napID, BOOL status)
{
	int i;
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	OSAL_enter_critical_section(&g_L4dbLock);

	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if(TRUE == l4db_IsNapidEqual(napID, g_pL4dbContext->discoveredNaps[i].napID))
		{
			g_pL4dbContext->discoveredNaps[i].isLastDetected = status;
			/*if (TRUE == status)
			{
				g_pL4dbContext->discoveredNaps[i].ttl < L4DB_MAX_TTL ? ++g_pL4dbContext->discoveredNaps[i].ttl : L4DB_MAX_TTL;
			}
			else
			{
				g_pL4dbContext->discoveredNaps[i].ttl > 0 ? --g_pL4dbContext->discoveredNaps[i].ttl : 0;
			}*/
			break;
		}
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
///Gets the Nap ids of all the last detected NAPs
///</summary>
/// <param name="pNapIds">(OUT)  an array of NAP IDs allocated by the user </param>
/// <param name="nNapIdsSize">(IN)  the size of the array allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               pNapIds' array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetLastDetectedNapIds(wmx_NAPid_t * pNapIds, UINT32 * nNapIdsSize)
{
	wmx_Status_t		rc = WMX_ST_MODULE_NOT_INITIALIZED; 
	int					i;
	UINT32				actualSize = 0;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	OSAL_enter_critical_section(&g_L4dbLock);

	//iterate through all the discovered NAPs and check if it is last detected
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i ++)
	{
		if(TRUE == g_pL4dbContext->discoveredNaps[i].isLastDetected)
		//if (g_pL4dbContext->discoveredNaps[i].ttl > 0)
		{
			//check that we have enough space in the array allocated by the user
			if(actualSize < *nNapIdsSize)
			{
				memcpy(pNapIds[actualSize], g_pL4dbContext->discoveredNaps[i].napID, sizeof(pNapIds[actualSize]));
			}
			else
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
			}
			actualSize++;
		}
	}

	*nNapIdsSize = actualSize;
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
///Gets the Nap ids of all the old detected NAPs
///</summary>
/// <param name="pNapIds">(OUT)  an array of NAP IDs allocated by the user </param>
/// <param name="nNapIdsSize">(IN)  the size of the array allocated by the user
///			                     (OUT)The actual number of elements returned \ that should be allocated in the 
///                               pNapIds' array.</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetOldDetectedNapIds(wmx_NAPid_t * pNapIds, UINT32 * nNapIdsSize)
{
	wmx_Status_t		rc = WMX_ST_MODULE_NOT_INITIALIZED; 
	int					i;
	UINT32				actualSize = 0;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_OK;

	OSAL_enter_critical_section(&g_L4dbLock);

	//iterate through all the discovered NAPs and check if it is last detected
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i ++)
	{
		if((FALSE == g_pL4dbContext->discoveredNaps[i].isLastDetected) &&
		//if((g_pL4dbContext->discoveredNaps[i].ttl < 1) &&
			(FALSE == l4db_IsNapidEmpty(g_pL4dbContext->discoveredNaps[i].napID)))
		{
			//check that we have enough space in the array allocated by the user
			if(actualSize < *nNapIdsSize)
			{
				memcpy(pNapIds[actualSize], g_pL4dbContext->discoveredNaps[i].napID, sizeof(pNapIds[actualSize]));
			}
			else
			{
				rc = WMX_ST_BUFFER_TOO_SHORT;
			}
			actualSize++;
		}
	}

	*nNapIdsSize = actualSize;
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Gets a NAPs Information for a specified provisioned NSP. This API gets both provisioned and discovered information
/// for the provisioned NSP
/// </summary>
/// <param name="nspID">(IN)  the nsp ID for which we request NAP info for </param>
/// <param name="pNaps">(OUT) an array of NAPs</param>
/// <param name="nNapsSize">(IN)  the size of pNaps allocate by the user
///                         (OUT) the actual number of elemnts returned \ that should be allocated in pNaps</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT
///     If the given NSP Id is not provisioned, the API will return WMX_ST_DATA_UNAVAILABLE</returns>
wmx_Status_t L4db_GetNapsInfo(wmx_NSPid_t nspID, pL4db_Nap_t pNaps, UINT32 * nNapsSize)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	pProvisionedNsp_t nsp = (pProvisionedNsp_t)malloc(sizeof(ProvisionedNsp_t));

	if (nsp == NULL)
	{
		return WMX_ST_FAIL;
	}

	//there is no lock because the lock is performed within L4db_GetProvisionedNsp
	rc = L4db_GetProvisionedNsp(nspID, nsp);

	if(WMX_ST_OK != rc)
	{
		*nNapsSize = 0;
		free(nsp);
		return rc;
	}

	//verify that the user allocated enough space
	if(*nNapsSize < nsp->nwParams.capl.napsSize)
	{
		rc = WMX_ST_BUFFER_TOO_SHORT;
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNapsInfo returned WMX_ST_BUFFER_TOO_SHORT");
	}
	else
	{
		memcpy(pNaps, nsp->nwParams.capl.naps, nsp->nwParams.capl.napsSize * sizeof(nsp->nwParams.capl.naps[0]));
	}

	*nNapsSize = nsp->nwParams.capl.napsSize;

	free(nsp);
	return rc;
}
/// <summary>
/// Gets an array of all NAP ID's an their change counts
/// </summary>
/// <param name="pChangeCounts">(OUT)  the array of change counts allocated by the user</param>
/// <param name="nChangeCountsSize">(IN)  the size of changeCounts allocate by the user
///                                 (OUT) the actual number of elemnts returned \ that should be allocated in changeCounts</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetNapChangeCountList(pChangeCount_t pChangeCounts, UINT32 * nChangeCountsSize)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;
	int				i, j;
	UINT32			actualNumOfNaps = 0;

	if(!g_fIsInitiated )
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_FAIL;

	OSAL_enter_critical_section(&g_L4dbLock);

	for(i = 0, j = 0; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if(FALSE == l4db_IsNapidEmpty(g_pL4dbContext->discoveredNaps[i].napID))
		{
			//verify there is enough allocated space
			if(actualNumOfNaps < *nChangeCountsSize)
			{
				pChangeCounts[j].changeCount = g_pL4dbContext->discoveredNaps[i].changeCount;
				memcpy(&pChangeCounts[j].napId, &g_pL4dbContext->discoveredNaps[i].napID,
					sizeof(pChangeCounts[j].napId));

				j++;
			}

			actualNumOfNaps++;
		}
	}

	//verify that the user allocated enough space for the recent NSPs
	if(*nChangeCountsSize < actualNumOfNaps)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetNapChangeCountList returned WMX_ST_BUFFER_TOO_SHORT");
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		rc = WMX_ST_OK;
	}

	//update the copied size for the user / that the user should allocate
	*nChangeCountsSize = actualNumOfNaps;

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// Gets the NSP IDs related to the given NAP ID. This includes NSPs which we discovered 
/// through 16g. One NSP ID is given per NSP
/// </summary>
/// <param name="bsID">(IN)  the requested BsID</param>
/// <param name="bsIdType">(IN)  the requested BsID type</param>
/// <param name="pNspIds">(OUT)  an array of NSP IDs to be filled by this API</param>
/// <param name="nNspIdsSize">(IN)  the size of pNspIds allocate by the user
///                                 (OUT) the actual number of elemnts returned \ that should be allocated in pNspIds</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_ConvertNap2Nsps(wmx_BSid_t bsID, wmx_BsIdType_t bsIdType, wmx_pNSPid_t pNspIds, UINT32 * nNspIdsSize)
{
	UINT32 actualSize = 0;
	UINT32 i, j, k, m;
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	BOOL finished = FALSE;
	pProvisionedNsp_t pFoundNsp;
	wmx_NAPid_t napID;
	int			napIdInt;

	if(!g_fIsInitiated )
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_memcpy_s(napID, sizeof(wmx_NAPid_t), bsID, sizeof(wmx_NAPid_t));

	OSAL_enter_critical_section(&g_L4dbLock);
	rc = WMX_ST_DATA_UNAVAILABLE;

	//first, search for the NAP ID in all the CAPLs
	for(i = 0 ; i < WMX_NSPS_MAX_NUM ; i++) //iterate through all the provisioned NSPs
	{
		for(j = 0 ; j < WMX_NAPS_MAX_NUM ; j++) //iterate through all NAPs in the capl
		{
			//check if we have found our NAP ID
			if(TRUE == l4db_IsNapidEqualEx(napID, g_pL4dbContext->nsps[i].nwParams.capl.naps[j].napID, bsIdType))
			{
				//get one of this NSP's IDs
				for(k = 0 ; k < WMX_NSP_IDS_MAX_NUM ; k++)
				{
					if(L4DB_INVALID_INDEX != g_pL4dbContext->nsps[i].nwParams.hNsps[k].nspId)
					{
						//verify that the user allocated enough space
						if(actualSize < *nNspIdsSize)
						{
							pNspIds[actualSize] = g_pL4dbContext->nsps[i].nwParams.hNsps[k].nspId;
							actualSize++;
							rc = WMX_ST_OK;
						}
						else
						{
							rc = WMX_ST_BUFFER_TOO_SHORT;
						}

						finished = TRUE;
						break;
					}
				}
				if(TRUE == finished)
				{
					finished = FALSE;
					break;
				}
			}
		}
	}	

	if (l4db_TestNapIdNspIdBit(bsID) == TRUE)
	{
		//verify that the user allocated enough space
		if(actualSize < *nNspIdsSize)
		{			
			l4db_ConvertNapIdTypeToNapIdInt(napID, &napIdInt);
			pNspIds[actualSize] = napIdInt;
			actualSize++;
			rc = WMX_ST_OK;
		}
		else
		{
			rc = WMX_ST_BUFFER_TOO_SHORT;
		}		
	}

	//search through the discovered NAPs to find our NAP ID. Add 16g info NSPs
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		if(TRUE == l4db_IsNapidEqualEx(napID, g_pL4dbContext->discoveredNaps[i].napID, bsIdType))
		{
			//we found our NAP, iterate through all its NSPs
			for(j = 0 ; j < g_pL4dbContext->discoveredNaps[i].nspInfoSize ; j++)
			{
				//check that this NSP or one of its equivalent has already been added
				pFoundNsp = l4db_GetProvisionedNspById(g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID);

				if(NULL != pFoundNsp)
				{
					for(k = 0 ; k < WMX_NSP_IDS_MAX_NUM ; k++)
					{
						for(m = 0 ; m < actualSize ; m++)
						{
							if(pFoundNsp->nwParams.hNsps[k].nspId == pNspIds[m])
							{
								finished = TRUE; //we don't need to add this NSP, it already exists
								break;
							}
						}
						if(TRUE == finished)
						{
							break;
						}
					}
				}

				if(finished == TRUE)
				{
					finished = FALSE;
				}
				else//we need to add this NSP ID
				{
					//verify that the user allocated enough space
					if(actualSize < *nNspIdsSize)
					{
						pNspIds[actualSize] = g_pL4dbContext->discoveredNaps[i].nspInfo[j].nspID;
						actualSize++;
						rc = WMX_ST_OK;
					}
					else
					{
						rc = WMX_ST_BUFFER_TOO_SHORT;
					}
				}
			}
		}
	}
	//update the size copied to the user \ the user needs to allocate
	*nNspIdsSize = actualSize;
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}


/// <summary>
/// Sets the user connection mode
/// </summary>
wmx_Status_t L4db_SetConnectMode(wmx_UserConnectMode_t newVal)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetConnectMode(IN). connectMode=%d", newVal);				
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetConnectMode(IN). no init - rc=%d", rc);
		return rc;
	}

	rc = WMX_ST_FAIL;

	if((newVal >= UserSemiManScanManConnect) && (newVal <= UserManScanManConnect))
	{
		OSAL_enter_critical_section(&g_L4dbLock);

		g_pL4dbContext->generalSettings.connectMode = newVal; 

		OSAL_exit_critical_section(&g_L4dbLock);
		rc = WMX_ST_OK;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetConnectMode error (%d)", newVal);
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetConnectMode(IN). rc=%d", rc);				
	return rc;
}

/// <summary>
/// Gets the user connection mode
/// </summary>
wmx_UserConnectMode_t L4db_GetConnectMode()
{
	wmx_UserConnectMode_t val;

	OSAL_enter_critical_section(&g_L4dbLock);

	val = g_pL4dbContext->generalSettings.connectMode; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return val;
}

/// <summary>
/// Sets the fast reconnect status
/// </summary>
wmx_Status_t L4db_SetFastReconnectStatus(BOOL isEnabled)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetFastReconnectStatus(IN). IsEnabled=%d", isEnabled);				
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetFastReconnectStatus(IN). no init");
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}
	
	OSAL_enter_critical_section(&g_L4dbLock);
	g_pL4dbContext->generalSettings.allowFastReconnect = isEnabled; 
	OSAL_exit_critical_section(&g_L4dbLock);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetFastReconnectStatus(OUT)");		
	return WMX_ST_OK;
}

/// <summary>
/// Gets the fast reconnect status
/// </summary>
BOOL L4db_GetFastReconnectStatus()
{
	BOOL val;

	OSAL_enter_critical_section(&g_L4dbLock);

	val = g_pL4dbContext->generalSettings.allowFastReconnect; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return val;
}

/// <summary>
/// Sets the allow auto activate flag
/// </summary>
void L4db_SetAllowAutoActivate(BOOL val)
{
	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->generalSettings.allowAutoActivate = val; 

	OSAL_exit_critical_section(&g_L4dbLock);
}

/// <summary>
/// Gets the allow auto activate flag
/// </summary>
BOOL L4db_GetAllowAutoActivate()
{
	BOOL val;

	OSAL_enter_critical_section(&g_L4dbLock);

	val = g_pL4dbContext->generalSettings.allowAutoActivate; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return val;
}

/// <summary>
/// sets the short link loss parameters
/// </summary>
void L4db_SetShortLinkLossParams(LinkLossParameters_t linkLossParams)
{
	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->generalSettings.shortLinkLossParams.time = linkLossParams.time; 
	g_pL4dbContext->generalSettings.shortLinkLossParams.repetition = linkLossParams.repetition; 

	OSAL_exit_critical_section(&g_L4dbLock);
}
/// <summary>
/// gets the short link loss parameters
/// </summary>
LinkLossParameters_t L4db_GetShortLinkLossParams()
{
	LinkLossParameters_t val;

	OSAL_enter_critical_section(&g_L4dbLock);

	val.time = g_pL4dbContext->generalSettings.shortLinkLossParams.time;
	val.repetition = g_pL4dbContext->generalSettings.shortLinkLossParams.repetition;

	OSAL_exit_critical_section(&g_L4dbLock);

	return val;
}

/// <summary>
/// sets the long link loss parameters
/// </summary>
void L4db_SetLongLinkLossParams(LinkLossParameters_t linkLossParams)
{
	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->generalSettings.longLinkLossParams.time = linkLossParams.time; 
	g_pL4dbContext->generalSettings.longLinkLossParams.repetition = linkLossParams.repetition; 

	OSAL_exit_critical_section(&g_L4dbLock);
}

/// <summary>
/// gets the long link loss parameters
/// </summary>
LinkLossParameters_t L4db_GetLongLinkLossParams()
{
	LinkLossParameters_t val;

	OSAL_enter_critical_section(&g_L4dbLock);

	val.time = g_pL4dbContext->generalSettings.longLinkLossParams.time;
	val.repetition = g_pL4dbContext->generalSettings.longLinkLossParams.repetition;

	OSAL_exit_critical_section(&g_L4dbLock);

	return val;
}
/// <summary>
/// Gets the last rf state
/// </summary>
wmx_RfStatus_t L4db_GetSwRfState()
{
	wmx_RfStatus_t state;

	OSAL_enter_critical_section(&g_L4dbLock);

	state = g_pL4dbContext->generalSettings.swRfState; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return state;
}

/// <summary>
/// Sets the last rf state
/// </summary>
wmx_Status_t L4db_SetSwRfState(wmx_RfStatus_t newState)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_FAIL;

	if((newState >= Off) && (newState <= On))
	{
		OSAL_enter_critical_section(&g_L4dbLock);
		g_pL4dbContext->generalSettings.swRfState = newState ;
		OSAL_exit_critical_section(&g_L4dbLock);
		rc = WMX_ST_OK;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetSwRfState error (%d)", newState);
	}

	return rc;
}

/// <summary>
/// Sets the TH criteria
/// </summary>
void L4db_SetThCriteria(wmx_THCriteria_t newVal)
{

	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->generalSettings.thCriteria = newVal; 

	OSAL_exit_critical_section(&g_L4dbLock);

}
/// <summary>
/// Gets the encrepted password from the specific file name and decrypt it
/// </summary>
BOOL L4db_GetEncyptedPassword(char *passwordFileName, char *decryptedPassword)
{
	FILE *file = NULL;
	CHAR path[MAX_REGISTRY_ANSWER];
	DATA_BLOB DataIn;
	DATA_BLOB DataOut;
	UINT32 buffSize = 0;
	int done =FALSE, i = 1;
	BYTE *buffData = NULL;
	errno_t err;
	BOOL rc = TRUE;

	NDnSAgent_BuildFullPath(passwordFileName, path, MAX_REGISTRY_ANSWER);

	if( ( err = OSAL_fopen(&file, path, "r+b" )) !=0 )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_GetEncyptedPassword: unable to open file contain the encrypted password");
		return FALSE;
	}
	
	//find the right size of the encrypted buffer and copy the file content into it
	do{
		buffData = (BYTE *)malloc(MAX_REGISTRY_ANSWER * i);
		buffSize = (UINT32)OSAL_fread(buffData, sizeof(BYTE), (MAX_REGISTRY_ANSWER * i), file); 
		if(((int)buffSize) < (MAX_REGISTRY_ANSWER * i))
		{
			done = TRUE;
			OSAL_fclose(file);
		}
		else
		{
			//the buffer is too small allocate again;
			free(buffData);
			i++;
			buffData = NULL;
		}
	}while(!done);
	
	DataIn.pbData = buffData;
	DataIn.cbData = buffSize;

	if (CryptUnprotectData(&DataIn, NULL, NULL, NULL, NULL, 0, &DataOut))
	{
		OSAL_strncpy_s(decryptedPassword, MAX_EAP_PASSWORD_SIZE, (char *)DataOut.pbData, DataOut.cbData);
		rc = TRUE;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_GetEncyptedPassword: unable to decrypt the password");
		rc = FALSE;
	}
	OSAL_free(DataOut.pbData);
	free(buffData);
	return rc;
}
/// <summary>
/// Sets the encrypted password into the right possition in the NSP
/// and generate new file (its name is going to be saved as the password name) that contain the encrypted password
/// </summary>
BOOL L4db_SetEncryptedPassword(char *password, char *passwordToEncrypt)
{
	int done=FALSE, encryptedFileNumber;
	DATA_BLOB DataIn;
	DATA_BLOB DataOut;
	CHAR encryptedFileName[MAX_STR_LEN];
	FILE *file = NULL;
	CHAR path[MAX_REGISTRY_ANSWER];
	errno_t err;
	static unsigned addToSead=0;

	//delete the file of the old password (if exist)and then continue to Add new one
	NDnSAgent_BuildFullPath(password, path, MAX_REGISTRY_ANSWER);
	remove(path);

	//create random file name to save the password in
	do{
		srand( addToSead + (unsigned)time( NULL ) );
		addToSead++;
		encryptedFileNumber = rand();
		if(encryptedFileNumber)
		{
			OSAL_itoa_s(encryptedFileNumber, encryptedFileName, MAX_STR_LEN, 10);
			NDnSAgent_BuildFullPath(encryptedFileName, path, MAX_REGISTRY_ANSWER);

			if( ( err = OSAL_fopen(&file, path, "r+" )) == SYSTEM_FILE_NOT_FOUND )
			{
				done = TRUE;
			}
		}
	}while(!done);


	if( ( err = OSAL_fopen(&file, path, "w+b" )) !=0 )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_SetEncryptedPassword: unable to open new file for the encrypted password");
		ZeroMemory(passwordToEncrypt, strnlen(passwordToEncrypt, MAX_EAP_PASSWORD_SIZE));
		return FALSE;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, L"The file holding the encrypted password is %s\n",encryptedFileName);

	//encrypt the password
	DataIn.cbData = (UINT32)strnlen(passwordToEncrypt, MAX_EAP_PASSWORD_SIZE -1);
	DataIn.cbData++;
	
	DataIn.pbData = (BYTE *)passwordToEncrypt;

	if (!CryptProtectData(&DataIn, NULL, NULL, NULL, NULL, CRYPTPROTECT_LOCAL_MACHINE, &DataOut))
	{
		OSAL_fclose(file);
		ZeroMemory(DataIn.pbData, DataIn.cbData);
		return FALSE;
	}
	//zero memory the clear text password
	ZeroMemory(DataIn.pbData, DataIn.cbData);

	OSAL_fwrite(DataOut.pbData, sizeof(DataOut.pbData[0]), DataOut.cbData, file);
	OSAL_fclose(file);

	OSAL_strcpy_s(password ,MAX_EAP_PASSWORD_SIZE,encryptedFileName);

	OSAL_free(DataOut.pbData);

	return TRUE;
}
/// <summary>
/// Gets the TH criteria
/// </summary>
wmx_THCriteria_t L4db_GetThCriteria()
{
	wmx_THCriteria_t val;

	OSAL_enter_critical_section(&g_L4dbLock);

	val = g_pL4dbContext->generalSettings.thCriteria; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return val;
}

void ResetNAPsBeneathThreshold()
{
	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount = 0;
	g_pL4dbContext->tempScanResults.totalNAPsCount = 0;

	OSAL_exit_critical_section(&g_L4dbLock);
}

// Store the NAPs beneath threshold
// Basically all the NAPs are stored, but those that have good link grade are marked as invalid
void AddNAPsBeneathThreshold(UINT32 numOfNAPs, wmx_pNAP_t pNAPs)
{
	UINT32 i, j, k;
	UINT32 *numOfChannels = 0;
	BOOL bAddNewNap;
	BOOL bIsValid;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return;
	}
	if (pNAPs == NULL)
	{
		return;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	// Add each channel to the correct NAP
	for (i = 0; i < numOfNAPs; i++)
	{		
		bAddNewNap = FALSE;

		// Run over the existing NAPs and look for the correct NAP to add to
		for (j = 0; j < g_pL4dbContext->tempScanResults.totalNAPsCount; j++)
		{		
			// Compare the NAP IDs
			if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsCriteria.bsID[0] == pNAPs[i].bsCriteria.bsID[0] &&
				g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsCriteria.bsID[1] == pNAPs[i].bsCriteria.bsID[1] &&
				g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsCriteria.bsID[2] == pNAPs[i].bsCriteria.bsID[2])
			{ // Existing NAP
				numOfChannels = &g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].numChannels;				

				// Add all the channels of the NAP
				for (k = 0; (k < pNAPs[i].numChannels) && (k + 1 + *numOfChannels < WMX_CHANNELS_MAX_NUM); k++)
				{
					if (pNAPs[i].linkGrade[k] == LinkGrade_AboveThr)
					{
						if (g_pL4dbContext->tempScanResults.isValid[j])
						{	
							g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount--;
							g_pL4dbContext->tempScanResults.isValid[j] = FALSE;
						}
						//continue;
						break; //[Oran] no need to add more channels since this NAP has good link grade
					}

					// Update the best CINR (bestCINR already exists because it is not the first channel added to the NAP)
					if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestCINR < pNAPs[i].CINRs[k])
					{
						g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestCINR = pNAPs[i].CINRs[k];
					}

					// Update the best RSSI (bestRSSI already exists because it is not the first channel added to the NAP)
					if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestRssi < pNAPs[i].RSSIs[k])
					{
						g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestRssi = pNAPs[i].RSSIs[k];
					}	

					// Update the best LinkQuality (bestLinkQuality already exists because it is not the first channel added to the NAP)
					if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestLinkQuality < pNAPs[i].linkQuality[k])
					{
						g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestLinkQuality = pNAPs[i].linkQuality[k];
					}	
					
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].CINRs[*numOfChannels] = pNAPs[i].CINRs[k];
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].RSSIs[*numOfChannels] = pNAPs[i].RSSIs[k];
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].channelIdList[*numOfChannels] = pNAPs[i].channelIdList[k];

					(*numOfChannels)++;					
				}

				break; // Move to the next NAP to add
			}	
		}

		// New NAP to add
		if (j == g_pL4dbContext->tempScanResults.totalNAPsCount)
		{
			bIsValid = TRUE; // by default - a newly added NAP is valid
			for (k = 0; k < pNAPs[i].numChannels; k++)
			{
				// Add the new NAP regardless of its link grade to allow comparison to NAPs found in later chunks
				if (bAddNewNap == FALSE)
				{
					bAddNewNap = TRUE;

					// New NAP's parameters
					g_pL4dbContext->tempScanResults.totalNAPsCount++;
					g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount++;
					g_pL4dbContext->tempScanResults.isValid[j] = bIsValid;
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestCINR = LOWEST_CINR; // The value will be updated to a real value in the for loop
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestRssi = LOWEST_RSSI; // The value will be updated to a real value in the for loop
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestLinkQuality = LOWEST_LINK_QUALITY; // The value will be updated to a real value in the for loop
					OSAL_memcpy_s(&g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsCriteria, sizeof(wmx_BSSelectionCriteria_t),
						&pNAPs[i].bsCriteria, sizeof(wmx_BSSelectionCriteria_t));
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsIDType = pNAPs[i].bsIDType;
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].changeCount = pNAPs[i].changeCount;
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].numChannels = 0;
					numOfChannels = &g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].numChannels;
				}

				if (pNAPs[i].linkGrade[k] == LinkGrade_AboveThr)
				{
					if (bIsValid)
					{			
						g_pL4dbContext->tempScanResults.NAPsBeneathThresholdCount--;
						bIsValid = FALSE;
					}
					//continue;
					break; //[Oran] no need to add this NAP since it has good link grade
				}
				else
				{
					//// Add the new NAP only if there is a channel with a bad linkGrade
					//if (bAddNewNap == FALSE)
					//{
					//	bAddNewNap = TRUE;

					//	// New NAP's parameters
					//	g_pL4dbContext->tempScanResults.totalNAPsCount++;
					//	g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestCINR = LOWEST_CINR; // The value will be updated to a real value in the for loop
					//	g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestRssi = LOWEST_RSSI; // The value will be updated to a real value in the for loop
					//	OSAL_memcpy_s(&g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsCriteria, sizeof(wmx_BSSelectionCriteria_t),
					//		&pNAPs[i].bsCriteria, sizeof(wmx_BSSelectionCriteria_t));
					//	g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bsIDType = pNAPs[i].bsIDType;
					//	g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].changeCount = pNAPs[i].changeCount;
					//	g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].numChannels = 0;
					//	numOfChannels = &g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].numChannels;
					//}
				}

				// Update the best CINR (bestCINR already exists because it is not the first channel added to the NAP)
				if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestCINR < pNAPs[i].CINRs[k])
				{
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestCINR = pNAPs[i].CINRs[k];
				}

				// Update the best RSSI (bestRSSI already exists because it is not the first channel added to the NAP)
				if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestRssi < pNAPs[i].RSSIs[k])
				{
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestRssi = pNAPs[i].RSSIs[k];
				}

				// Update the best LinkQuality (bestLinkQuality already exists because it is not the first channel added to the NAP)
				if (g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestLinkQuality < pNAPs[i].linkQuality[k])
				{
					g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].bestLinkQuality = pNAPs[i].linkQuality[k];
				}

				g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].CINRs[*numOfChannels] = pNAPs[i].CINRs[k];
				g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].RSSIs[*numOfChannels] = pNAPs[i].RSSIs[k];
				g_pL4dbContext->tempScanResults.NAPsBeneathThreshold[j].channelIdList[*numOfChannels] = pNAPs[i].channelIdList[k];

				(*numOfChannels)++;					
			}
			if (bAddNewNap)
			{		
				g_pL4dbContext->tempScanResults.isValid[j] = bIsValid;
			}
		}
	}

	OSAL_exit_critical_section(&g_L4dbLock);
}

// Sort NAPs by the RSSI first and CINR next
void SortNaps(wmx_pNAP_t pNaps, UINT32 numOfNaps)
{
	if (pNaps != NULL && numOfNaps > 0)
	{
		qsort(pNaps, numOfNaps, sizeof(pNaps[0]), l4db_CompareNapRSSIandCINR);
	}	
}

/// <summary>
/// Gets the current connection time
/// </summary>
UINT32 L4db_GetConnectionTime()
{
	UINT32 connTime;

	OSAL_enter_critical_section(&g_L4dbLock);

	connTime = g_pL4dbContext->connectionTime; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return connTime;
}

/// <summary>
/// Set the current connection time
/// </summary>
void L4db_SetConnectionTime(UINT32 connectionTime)
{
	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->connectionTime = connectionTime ;

	OSAL_exit_critical_section(&g_L4dbLock);
}

/// <summary>
/// Sets Roaming mode per the specified NSP
/// </summary>
wmx_Status_t L4db_SetRoamingMode(wmx_UserRoamingMode_t newVal)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_DATA_UNAVAILABLE;

	//validate the value that we should set
	if((newVal >= UserEnableRoaming) &&	(newVal <= UserDisableRoaming))
	{
		OSAL_enter_critical_section(&g_L4dbLock);

		g_pL4dbContext->generalSettings.roamingMode = newVal;
		rc = WMX_ST_OK;

		OSAL_exit_critical_section(&g_L4dbLock);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, L"L4db_SetRoamingMode error (%d)", newVal);
	}

	return rc;
}
/// <summary>
/// Gets Roaming mode per the specified NSP
/// </summary>
wmx_Status_t L4db_GetRoamingMode(wmx_pUserRoamingMode_t pVal)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	*pVal = (wmx_UserRoamingMode_t)g_pL4dbContext->generalSettings.roamingMode;

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}



/// <summary>
/// Sets the NDnS general settings
/// </summary>
/// <param name="bandRange">(OUT)  a pointer to a channelPlan struct to filled with the band range data</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetBandRange(pChannelPlan_t pBandRange)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetBandRange(IN)");
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetBandRange(OUT). ERROR - FALSE == g_fIsInitiated");
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	l4db_CopyChannelPlan(pBandRange, &g_pL4dbContext->wideScanParams);

	OSAL_exit_critical_section(&g_L4dbLock);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetBandRange(OUT)");
	return WMX_ST_OK;
}
/// <summary>
/// Sets the NDnS general settings
/// </summary>
/// <param name="bandRange">(IN)  a pointer to a channelPlan struct with the band range data</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetBandRange(pChannelPlan_t pBandRange)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//copy the channel plan and init the relevant places
	l4db_CopyChannelPlanWithInit(&g_pL4dbContext->wideScanParams, pBandRange);

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

/// <summary>
/// Gets the device certificates
/// </summary>
/// <param name="pDeviceCerts">(OUT) a pointer to a device certificates struct</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_GetDeviceCertificates(pDeviceCertificates_t pDeviceCerts)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	memcpy(pDeviceCerts, &g_pL4dbContext->deviceCerts, sizeof(*pDeviceCerts));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}
/// <summary>
/// Gets the preferred scan policy
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_SetPreferredScanPolicy(PreferredScanPolicy_t policy)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_FAIL;

	if((policy >= FirstRecent) && (policy <= OtherHome))
	{
		OSAL_enter_critical_section(&g_L4dbLock);

		g_pL4dbContext->preferredScanPolicy = policy ;

		OSAL_exit_critical_section(&g_L4dbLock);
		rc = WMX_ST_OK;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_SetPreferredScanPolicy policy cannot be (%d)", policy);
	}

	return rc;
}

/// <summary>
/// Gets the preferred scan policy
/// </summary>
/// <returns>wmx_Status_t </returns>
PreferredScanPolicy_t L4db_GetPreferredScanPolicy()
{
	PreferredScanPolicy_t policy;

	OSAL_enter_critical_section(&g_L4dbLock);

	policy = g_pL4dbContext->preferredScanPolicy; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return policy;
}
/// <summary>
/// Gets the version of the L4db
/// </summary>
/// <returns>wmx_Status_t </returns>
int L4db_GetDbVersion()
{
	int version;

	OSAL_enter_critical_section(&g_L4dbLock);

	version = g_pL4dbContext->l4dbVersion; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return version;
}

/// <summary>
/// Gets the current NAI counter
/// </summary>
/// <returns>wmx_Status_t </returns>
UINT32 L4db_GetNaiCounter() //TODO - remove this
{
	UINT32 counter;

	OSAL_enter_critical_section(&g_L4dbLock);

	counter = g_pL4dbContext->naiCounter; 

	OSAL_exit_critical_section(&g_L4dbLock);

	return counter;
}

/// <summary>
/// Gets the current NAI counter
/// </summary>
/// <returns>wmx_Status_t </returns>
void L4db_SetNaiCounter(UINT32 val) //TODO - remove this
{
	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->naiCounter = val;

	OSAL_exit_critical_section(&g_L4dbLock);
}

/// <summary>
/// Gets all the raoming patners of a specified NSP
/// </summary>
/// <param name="hNspID">(IN)  the ID of the home NSP</param>
/// <param name="roamingPartners">(OUT)in array of roaming partners info allocated by the user</param>
/// <param name="nRoamingPartnersSize">(IN)  the size of roamingPartners allocate by the user
///                                 (OUT) the actual number of elemnts returned \ that should be allocated in roamingPartners</param>
/// <returns>WMX_ST_OK if successful.
///		If the actual number of elements is higher than the number of elements allocated, 
///     the API will return WMX_ST_BUFFER_TOO_SHORT</returns>
wmx_Status_t L4db_GetRoamingPartners(wmx_NSPid_t hNspID, pRoamingPartnerInfo_t pRoamingPartners, UINT32 * nRoamingPartnersSize)
{
	UINT32			actualSize = 0, i;
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;
	pProvisionedNsp_t pFoundNsp;
	size_t tempStrLen = 0;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	rc = WMX_ST_DATA_UNAVAILABLE;

	OSAL_enter_critical_section(&g_L4dbLock);

	//get the relevant nsp
	pFoundNsp = l4db_GetProvisionedNspById(hNspID);

	if(NULL == pFoundNsp)
	{
		//the given hNspId doesn't exist
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_GetRoamingPartners NSP ID %d does not exist", hNspID);
		OSAL_exit_critical_section(&g_L4dbLock);
		return rc;
	}

	//calculate the the number of roaming partners
	for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
	{
		tempStrLen = strnlen(pFoundNsp->nwParams.rapl.roamingPartners[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			if(actualSize < *nRoamingPartnersSize)
			{
				memcpy(&pRoamingPartners[actualSize],
					&pFoundNsp->nwParams.rapl.roamingPartners[i], 
					sizeof(pRoamingPartners[actualSize]));
			}
			actualSize++;
		}
	}

	//verify that the user allocated enough space for the recent NSPs
	if(*nRoamingPartnersSize < actualSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_GetRoamingPartners returned WMX_ST_BUFFER_TOO_SHORT");
		rc = WMX_ST_BUFFER_TOO_SHORT;
	}
	else
	{
		rc = WMX_ST_OK;
	}

	//update the copied size for the user
	*nRoamingPartnersSize = actualSize;

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;

}
/// <summary>
/// Starts an "atomic" operation. the following sequence of APIs will be treated as an atom
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_StartAtomic()
{
	//TODO - finish this
	return WMX_ST_FAIL;
}
/// <summary>
/// Ends an "atomic" operation and starts a commit process in the database.
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_EndAtomic()
{
	//TODO - finish this
	return WMX_ST_FAIL;
}

/// <summary>
/// Restore the L4-db's data from in XML file
/// </summary>
wmx_Status_t L4db_RestoreFromFile(const WCHAR *pwsFileName)
{
	wmx_Status_t	rc = WMX_ST_MODULE_NOT_INITIALIZED;
	int				i, numOfChild;
	pXmlElement		xmlRoot;
	pXmlElement		xmlNextConfig;
	pXmlElement		xmlNdsAgent;
	const char		*str, *strValue;
	BOOL			boolRc;
	PreferredScanPolicy_t policy;
	char* buff = NULL;
	static size_t buffSize = BASIC_DB_FILE_SIZE;
	size_t outSize = 0;
	CHAR sfileName [MAX_REGISTRY_ANSWER];


	xmlRoot = CreateEmptyXmlData();

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_RestoreFromFile: file name= %s",pwsFileName);
	if(FALSE == g_fIsInitiated )
	{
		// Nobody init US ..., you should call init function
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: not initializied!!. rc=%d (BugSearch)",rc);
		return rc;
	}

	wcstombs_s(&outSize, sfileName, MAX_REGISTRY_ANSWER, pwsFileName, MAX_REGISTRY_ANSWER);
	OSAL_enter_critical_section(&g_L4dbLock);

	buff = (char*)malloc(buffSize);
	if(NULL == buff)
	{
		return WMX_ST_FAIL;
	}

	boolRc = Crypt_DecryptFile(sfileName, buff, &buffSize);
	if (!boolRc) 
	{
		free(buff);
		buff = (char*)malloc(buffSize);
		if(NULL == buff)
		{
			return WMX_ST_FAIL;
		}
		boolRc = Crypt_DecryptFile(sfileName, buff, &buffSize);
	}
	if(boolRc)
	{
		boolRc = ReadXmlBuffer(xmlRoot, buff, buffSize);
	}
	free(buff);
	
	if(FALSE == boolRc)
	{
		// we encountered an error reading the xml file
		rc = WMX_ST_CONFIG_ERROR;
		OSAL_exit_critical_section(&g_L4dbLock);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to read from xml (BugSearch)");
		return rc;
	}

	str = GetElementName(xmlRoot);
	xmlNdsAgent = GetChildAt(xmlRoot, 0);
	str = GetElementName(xmlNdsAgent);

	// clean the DB
	rc = L4db_Clean();
	numOfChild = GetChildrenCount(xmlNdsAgent);

	for(i = 0 ; i < numOfChild ; i++)
	{
		xmlNextConfig = GetChildAt(xmlNdsAgent, i);
		str = GetElementName(xmlNextConfig);

		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_INTERNAL_STATES))
		{
			rc = l4db_RestoreInternalStatesFromFile(xmlNextConfig, &g_pL4dbContext->generalSettings);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreInternalStatesFromFile (BugSearch)");
				return rc;
			}
		}
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_WMX_SUPP))
		{

			rc = l4db_RestoreWmxSuppFromFile(xmlNextConfig);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreWmxSuppFromFile (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_WIDE_SCAN_PARAMS))
		{
			rc = l4db_RestoreWideScanParamsFromFile(xmlNextConfig, &g_pL4dbContext->wideScanParams);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreWideScanParamsFromFile (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LINK_LOSS_PARAMS))
		{
			rc = l4db_RestoreLinkLossParamsFromFile(xmlNextConfig, 
				&g_pL4dbContext->generalSettings.shortLinkLossParams,
				&g_pL4dbContext->generalSettings.longLinkLossParams);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreLinkLossParamsFromFile (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DISCOVERED_NAP_INFO))
		{
			rc = l4db_RestoreDiscoveredNapInfoFromFile(xmlNextConfig, g_pL4dbContext->discoveredNaps);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreDiscoveredNapInfoFromFile (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEVICE_CERTIFICATES))
		{
			rc = l4db_RestoreDeviceCertificatesFromFile(xmlNextConfig, &g_pL4dbContext->deviceCerts);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreDeviceCertificatesFromFile (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DB_VERSION))
		{
			strValue = GetElementInnerText(xmlNextConfig);
			g_pL4dbContext->l4dbVersion = atoi(strValue);
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NAI_COUNTER))//TODO - remove this
		{
			strValue = GetElementInnerText(xmlNextConfig);
			g_pL4dbContext->naiCounter = (UINT32)atoi(strValue);
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PS_POLICY))
		{
			strValue = GetElementInnerText(xmlNextConfig);
			ConvertToPsPolicy(strValue, &policy);
			g_pL4dbContext->preferredScanPolicy = policy;
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEV_INFO))
		{
			rc = l4db_RestoreDevInfoFromFile(xmlNextConfig);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_CompareString (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEV_DETAIL))
		{
			rc = l4db_RestoreDevDetailFromFile(xmlNextConfig);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreDevDetailFromFile (BugSearch)");
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_WIMAX))
		{
			rc = l4db_RestoreWmxFromFile(xmlNextConfig);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreWmxFromFile (BugSearch)");
				return rc;
			}
		}

		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FUMO))
		{
			rc = l4db_RestoreFumoFromFile(xmlNextConfig);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreFumoFromFile (BugSearch)");
				return rc;
			}
		}

		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_APDO_INTERNAL))
		{
			rc = l4db_RestoreAPDOIntenalParamsFromFile(xmlNextConfig, &g_pL4dbContext->apdoInternalParams);
			if(WMX_ST_OK != rc)
			{
				OSAL_exit_critical_section(&g_L4dbLock);
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_RestoreFromFile: failed to l4db_RestoreAPDOIntenalParamsFromFile (BugSearch)");
				return rc;
			}
		}		
	}

	FreeXmlData(xmlRoot);

	OSAL_exit_critical_section(&g_L4dbLock);

	//PopulateMonitorVal();
	return rc;
}

/// <summary>
/// restore data base from default XML file
/// </summary>
/// <returns>wmx_Status_t </returns>
wmx_Status_t L4db_RestoreFromDefaults()
{
	wmx_Status_t st;
	WCHAR path[MAX_REGISTRY_ANSWER];

	// Note: This is the only function where I don't use lock since it uses the RestoreFrom file function
	// that already checks for init an lock of the DB. All other DB interface function must protect with lock.

	NDnSAgent_BuildFullPathW(WiMAX_DEF_ENC_DB, path, MAX_REGISTRY_ANSWER);				
	//NDnSAgent_BuildFullPathW(WiMAX_DEF_DB, path, MAX_REGISTRY_ANSWER);				

	st = L4db_RestoreFromFile(path);

	if (st != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_RestoreFromDefaults Failed");
	}

	return st;
}

//void PopulateMonitorVal()
//{
//	UINT32 i;
//	UINT8 buff[sizeof(Capl_t) +sizeof(Rapl_t) +sizeof(SubscriberInfo_t)];
//	UINT8 *tempPos;
//	UINT bitOff = 0;
//	UINT tempBuffSize =0;
//
//	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_OPERATOR))
//	{
//		//Eap
//		BM_MonitorOperator_Eaps_NumOfEaps_SET(buff, 
//			(g_pL4dbContext->nsps[0].subscriptionParams.other[0].subscriberInfo.eapInfoSize + 
//			g_pL4dbContext->nsps[0].subscriptionParams.primary.eapInfoSize));
//
//		for(i=0 ; i< g_pL4dbContext->nsps[0].subscriptionParams.other[0].subscriberInfo.eapInfoSize ; i++)
//		{
//			BM_MonitorOperator_Eaps_EapList_GET_ELEMENT_POS(buff,i,tempPos,bitOff);
//			memcpy(tempPos,&g_pL4dbContext->nsps[0].subscriptionParams.other[0].subscriberInfo.eapInfo[i], BM_MonitorOperator_Eaps_EapList_BYTES_CELL_SIZE);
//		}
//		for(i=0 ; i< g_pL4dbContext->nsps[0].subscriptionParams.primary.eapInfoSize ; i++)
//		{
//			BM_MonitorOperator_Eaps_EapList_GET_ELEMENT_POS(buff,i,tempPos,bitOff);
//			memcpy(tempPos,&g_pL4dbContext->nsps[0].subscriptionParams.primary.eapInfo[i], BM_MonitorOperator_Eaps_EapList_BYTES_CELL_SIZE);
//		}
//
//		//Capl
//		BM_MonitorOperator_Capls_Any_SET(buff,g_pL4dbContext->nsps[0].nwParams.capl.any);
//		BM_MonitorOperator_Capls_NapList_napID_GET_POS(buff,tempPos,bitOff);
//		memcpy(tempPos,&g_pL4dbContext->nsps[0].nwParams.capl.naps[0].napID,BM_MonitorOperator_Capls_NapList_napID_BYTES_SIZE);
//		BM_MonitorOperator_Capls_NapList_priority_SET(buff, g_pL4dbContext->nsps[0].nwParams.capl.naps[0].priority);
//		BM_MonitorOperator_Capls_NapList_NumOfChannelRefsSize_SET(buff,g_pL4dbContext->nsps[0].nwParams.capl.naps[0].channelRefsSize);
//
//		for(i=0 ; i<g_pL4dbContext->nsps[0].nwParams.capl.naps[0].channelRefsSize ; i++)
//		{
//			BM_MonitorOperator_Capls_NapList_id_value_SET(buff, i, g_pL4dbContext->nsps[0].nwParams.capl.naps[0].channelPlanRefIds[i].id);
//		}
//
//		BM_MonitorOperator_Capls_NapList_discoveredChannelPlan_NumOfChannels_SET(buff, g_pL4dbContext->nsps[0].nwParams.capl.naps[0].discoveredChannelPlan.channelsSize);
//		for(i=0; i<g_pL4dbContext->nsps[0].nwParams.capl.naps[0].discoveredChannelPlan.channelsSize; i++)
//		{
//			BM_MonitorOperator_Capls_NapList_discoveredChannelPlan_ChannelsList_GET_ELEMENT_POS(buff,i,tempPos,bitOff);
//			memcpy(tempPos,&g_pL4dbContext->nsps[0].nwParams.capl.naps[0].discoveredChannelPlan.channels[i],BM_MonitorOperator_Capls_NapList_discoveredChannelPlan_ChannelsList_BYTES_CELL_SIZE);
//		}
//		BM_MonitorOperator_Capls_NapList_discoveredChannelPlan_bw_SET(buff,g_pL4dbContext->nsps[0].nwParams.capl.naps[0].discoveredChannelPlan.bw);
//		BM_MonitorOperator_Capls_NapList_discoveredChannelPlan_fft_SET(buff,g_pL4dbContext->nsps[0].nwParams.capl.naps[0].discoveredChannelPlan.fft);
//		BM_MonitorOperator_Capls_NapList_discoveredChannelPlan_duplexMode_SET(buff,g_pL4dbContext->nsps[0].nwParams.capl.naps[0].discoveredChannelPlan.duplexMode);
//
//		BM_MonitorOperator_Capls_NapList_changeCount_SET(buff, g_pL4dbContext->nsps[0].nwParams.capl.naps[0].changeCount);
//
//		//Rapl
//		BM_MonitorOperator_Rapls_NumOfRoamingPartners_SET(buff,g_pL4dbContext->nsps[0].nwParams.rapl.roamingPartnersSize);
//		for(i=0 ; i<g_pL4dbContext->nsps[0].nwParams.rapl.roamingPartnersSize ; i++)
//		{
//			BM_MonitorOperator_Rapls_RaplList_GET_ELEMENT_POS(buff,i,tempPos,bitOff);
//			memcpy(tempPos,&g_pL4dbContext->nsps[0].nwParams.rapl.roamingPartners[i],BM_MonitorOperator_Rapls_RaplList_BYTES_CELL_SIZE);
//		}
//		BM_MonitorOperator_Rapls_Any_SET(buff,g_pL4dbContext->nsps[0].nwParams.rapl.any);
//
//		BM_MonitorOperator_GET_BYTES_SIZE(buff, tempBuffSize);
//		L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_OPERATOR, (UINT16)tempBuffSize);
//
//	}
//}



/// <summary>
/// saves the L4-db's data to an XML file
/// </summary>
wmx_Status_t L4db_SaveToFile(const PWCHAR pwsFileName)
{
	pXmlElement rootXmlData;

	if(NULL == pwsFileName)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_SaveToFile: pwsFileName == NULL");
		return WMX_ST_FAIL;
	}

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//OSAL_fprintf(pFile, "<?xml version=\"1.0\" ?>\n");
	//tmpXmlData = CreateEmptyXmlData();

	rootXmlData = CreateXmlData(L4DB_XML_TOKEN_INTERNAL_DATA, "");

	//add the operator node
	l4db_AddWmxSuppToXml(rootXmlData, g_pL4dbContext->nsps);

	//add the internal states node
	l4db_AddInternalStatesToXml(rootXmlData, &g_pL4dbContext->generalSettings);

	//add the wide scan parameters node
	l4db_AddWideScanParamsToXml(rootXmlData, &g_pL4dbContext->wideScanParams);

	//add the link loss params node
	l4db_AddLinkLossParamsToXml(rootXmlData, 
		g_pL4dbContext->generalSettings.shortLinkLossParams,
		g_pL4dbContext->generalSettings.longLinkLossParams);

	//add the other nap info node
	l4db_AddOtherNapInfoToXml(rootXmlData, g_pL4dbContext->discoveredNaps);

	//add the device certificates node
	l4db_AddDeviceCertificatesToXml(rootXmlData, g_pL4dbContext->deviceCerts);

	//add the preferred scan policy
	l4db_AddPsPolicyToXml(rootXmlData, g_pL4dbContext->preferredScanPolicy);

	//add the L4-db version
	l4db_AddDbVersionToXml(rootXmlData, g_pL4dbContext->l4dbVersion);

	//add the nai counter
	l4db_AddNaiCounterToXml(rootXmlData, g_pL4dbContext->naiCounter);

	//add the dev info
	l4db_AddDevInfoToXml(rootXmlData, &g_pL4dbContext->devInfo);

	//add the wimax node
	l4db_AddWmxToXml(rootXmlData, &g_pL4dbContext->wimax);

	//add the dev detail
	l4db_AddDevDetailToXml(rootXmlData, &g_pL4dbContext->devDetail);

	//add the Fumo node
	l4db_AddFumoToXml(rootXmlData, g_pL4dbContext->fumoNodes);

	// add the internal parameters node
	l4db_AddInternalAPDOParamsToXml(rootXmlData, g_pL4dbContext->apdoInternalParams);
	
	WriteDBFile(rootXmlData, pwsFileName, TRUE);
	//WriteDBFile(rootXmlData, pwsFileName, FALSE);

	FreeXmlData(rootXmlData);

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

/// <summary>
/// sets the device's general details - this API is used to initialize 
/// general device and terminal charecaristics which are known on during start up of AppSrv
/// </summary>
//wmx_Status_t L4db_SetGeneralSettings(pStaticWmxDetails_t pGeneralSettings)
//{
//	UINT32 i;
//
//	if(FALSE == g_fIsInitiated)
//	{
//		// Nobody init US ..., you should call init function
//		return WMX_ST_MODULE_NOT_INITIALIZED;
//	}
//
//	OSAL_enter_critical_section(&g_L4dbLock);
//
//	//copy the terminal equipment information
//	memcpy(&g_pL4dbContext->wimax.terminalEquipment.staticTermEquip, 
//		&pGeneralSettings->staticTermEquip,
//		sizeof(g_pL4dbContext->wimax.terminalEquipment.staticTermEquip));
//
//	//copy the wimax radio modules info
//	for(i = 0 ; i < pGeneralSettings->wmxRadioModulesSize ; i++)
//	{
//		memcpy(&g_pL4dbContext->wimax.radioModules[i], 
//			&pGeneralSettings->wmxRadioModules,
//			sizeof(g_pL4dbContext->wimax.radioModules[i]));
//	}
//
//	//update the number of wimax radio modules
//	g_pL4dbContext->wimax.wmxRadioModulesSize = pGeneralSettings->wmxRadioModulesSize;
//
//	OSAL_exit_critical_section(&g_L4dbLock);
//
//	return WMX_ST_OK;
//}
//
//

/// <summary>
/// sets the SP lock details
/// </summary>
wmx_Status_t L4db_SetSpLock(CHAR * wmxRadioModTagName, pSpLock_t pSpLock)
{
	pWmxRadioModule_t pWmxRadioModule;
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	pWmxRadioModule = l4db_GetWmxRadioModule(g_pL4dbContext->wimax.radioModules, 
		g_pL4dbContext->wimax.wmxRadioModulesSize,
		wmxRadioModTagName);

	if(NULL != pWmxRadioModule)
	{
		memcpy(&pWmxRadioModule->spLock, pSpLock, sizeof(pWmxRadioModule->spLock));
		rc = WMX_ST_OK;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_SetSpLock: cannot find wimax radio module with tag name = %s", wmxRadioModTagName);
		rc = WMX_ST_DATA_UNAVAILABLE;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// sets the SP lock details
/// </summary>
wmx_Status_t L4db_GetSpLock(CHAR * wmxRadioModTagName, pSpLock_t pSpLock)
{
	pWmxRadioModule_t pWmxRadioModule;
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	pWmxRadioModule = l4db_GetWmxRadioModule(g_pL4dbContext->wimax.radioModules, 
		g_pL4dbContext->wimax.wmxRadioModulesSize,
		wmxRadioModTagName);

	if(NULL != pWmxRadioModule)
	{
		memcpy(pSpLock, &pWmxRadioModule->spLock, sizeof(pWmxRadioModule->spLock));
		rc = WMX_ST_OK;
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_GetSpLock: cannot find wimax radio module with tag name = %s", wmxRadioModTagName);
		rc = WMX_ST_DATA_UNAVAILABLE;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

wmx_Status_t L4db_GetDefaultRealm(CHAR* defaultRealm)
{
	size_t len;
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	len = strnlen(g_pL4dbContext->apdoInternalParams.defaultRealm, WMX_NSP_REALM_MAX_SIZE);
	wmx_memcpy(defaultRealm, WMX_NSP_REALM_MAX_SIZE, 
		g_pL4dbContext->apdoInternalParams.defaultRealm, len);

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

/// <summary>
/// Gets an empty NSP (that hasn't been allocated yet)
/// </summary>
pProvisionedNsp_t l4db_GetEmptyNsp()
{
	pProvisionedNsp_t pFoundNsp = NULL;
	int i;

	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->nsps) ; i++)
	{
		if(0 == strnlen(g_pL4dbContext->nsps[i].tagName, MAX_TAG_NAME_SIZE))
		{
			pFoundNsp = &g_pL4dbContext->nsps[i];
			break;
		}
	}

	return pFoundNsp;
}
/// <summary>
/// Gets a provisioned NSP according to its unique name
/// </summary>
pProvisionedNsp_t l4db_GetProvisionedNspByTagName(CHAR * tagName)
{
	int i;
	pProvisionedNsp_t pFoundNsp = NULL;

	if(NULL == tagName)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"l4db_GetProvisionedNspByTagName: tagName == NULL");
		return NULL;
	}

	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->nsps) ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, g_pL4dbContext->nsps[i].tagName))
		{
			pFoundNsp = &g_pL4dbContext->nsps[i];
			break;
		}
	}

	return pFoundNsp;
}

/// <summary>
/// Gets an empty Fumo node (that hasn't been allocated yet)
/// </summary>
pFumoParams_t l4db_GetEmptyFumoNode()
{
	pFumoParams_t pFoundNode = NULL;	
	int i;

	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->fumoNodes) ; i++)
	{
		if(0 == strnlen(g_pL4dbContext->fumoNodes[i].tagName, MAX_TAG_NAME_SIZE))
		{
			pFoundNode = &g_pL4dbContext->fumoNodes[i];
			break;
		}
	}

	return pFoundNode;
}

/// <summary>
/// Gets the Fumo Params node which has the given tag name 
/// </summary
pFumoParams_t l4db_GetFumoParamsNodeByTagName(CHAR * tagName)
{
	int i;
	pFumoParams_t pFoundFumoNode = NULL;	

	if(NULL == tagName)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"l4db_GetFumoParamsNodeByTagName: tagName == NULL");
		return NULL;
	}

	for(i = 0 ; i < ARRAY_SIZE(g_pL4dbContext->fumoNodes) ; i++)
	{
		if(FALSE == l4db_CompareString(tagName, g_pL4dbContext->fumoNodes[i].tagName))
		{
			pFoundFumoNode = &g_pL4dbContext->fumoNodes[i];
			break;
		}
	}

	return pFoundFumoNode;
}

/// <summary>
/// gets a pointer to a provisioned NSP which has the specified NSP ID. 
/// NOTE: this API doesn't copy the Provisioned NSP found 
/// </summary>
/// <param name="nspID">(IN) the requested NSP ID </param>
/// <param name="pNsps">(IN) an array of provisioned NSPs </param>
/// <returns>pointer to ProvisionedNsp_t which we found or NULL </returns>
pProvisionedNsp_t l4db_GetProvisionedNspById(wmx_NSPid_t nspID)
{
	pProvisionedNsp_t pFoundNsp = NULL;
	int i, j;
	BOOL	finished = FALSE;

	for(i = 0 ; (i < WMX_NSPS_MAX_NUM) && (FALSE == finished) ; i++)
	{
		if(TRUE == g_pL4dbContext->nsps[i].fIsAllocated)
		{
			for(j = 0 ; j < WMX_NSP_IDS_MAX_NUM ; j++)
			{
				if(nspID == g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId)
				{
					pFoundNsp = &g_pL4dbContext->nsps[i];
					finished = TRUE;
					break;
				}
			}
		}
	}
	return pFoundNsp;
}



/// <summary>
/// gets a pointer to the dev info struct kept in the db
/// </summary>
pDevInfo_t l4db_GetDevInfo()
{
	return &g_pL4dbContext->devInfo;
}

/// <summary>
/// gets a pointer to the radio module struct kept in the db
/// </summary>
pWmxRadioModule_t l4db_GetWmxRadioModuleStruct(UINT32 index)
{
	if (index > g_pL4dbContext->wimax.wmxRadioModulesSize)
	{
		return NULL;
	}

	return &g_pL4dbContext->wimax.radioModules[index];
}

/// <summary>
/// gets a pointer to the terminal equipment struct kept in the db
/// </summary>
pTerminalEquipment_t l4db_GetTeminalEquipmentStruct()
{
	return &g_pL4dbContext->wimax.terminalEquipment;
}

/// <summary>
/// gets a pointer to the dev detail ex struct kept in the db
/// </summary>
pDevDetailExt_t l4db_GetDevDetailEx()
{
	return &g_pL4dbContext->devDetail.ext;
}

/// <summary>
/// gets a pointer to the dev detail struct kept in the db
/// </summary>
pDevDetail_t l4db_GetDevDetail()
{
	return &g_pL4dbContext->devDetail;
}

wmx_Status_t L4db_GetDevDetailParam(pDevDetail_t pDevDetail)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}
		
	OSAL_enter_critical_section(&g_L4dbLock);

	if(NULL != pDevDetail)
	{
		memcpy(pDevDetail, l4db_GetDevDetail() ,sizeof(DevDetail_t));
		rc = WMX_ST_OK;
	}
	else
	{
		rc =  WMX_ST_FAIL;
	}
	

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;

}

pDevInfo_t GetDevinfo()
{
	return &g_pL4dbContext->devInfo;
}

wmx_Status_t L4db_GetDevinfo(pDevInfo_t pDevInfo)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	
	if(NULL != pDevInfo)
	{
		memcpy(pDevInfo, l4db_GetDevInfo(),sizeof(DevInfo_t));
		rc = WMX_ST_OK;
	}
	else
	{
		rc =  WMX_ST_FAIL;
	}

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;

}

/// <summary>
/// gets a pointer to the wimax_t struct kept in the db
/// </summary>
pWimax_t l4db_GetWimax()
{
	return &g_pL4dbContext->wimax;
}

wmx_Status_t L4db_GetWimaxNode(pWimax_t pWimax)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED;
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	if(NULL != pWimax)
	{
		memcpy(pWimax, l4db_GetWimax(),sizeof(Wimax_t));
		rc = WMX_ST_OK;
	}
	else
	{
		rc =  WMX_ST_FAIL;
	}
	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;

}

/// <summary>
/// gets a pointer to the APDOInternalParams_t struct kept in the db
/// </summary>
pAPDOInternalParams_t l4db_GetAPDOInternalParams()
{
	return &g_pL4dbContext->apdoInternalParams;
}

///THIS IS A PATCH - THIS SHOULD BE REMOVED IN THE FUTURE
wmx_Status_t L4db_AddNapPatch(wmx_NAPid_t napID)
{
	int i;
	pL4db_Nap_t pNap;
	wmx_Status_t rc = WMX_ST_FAIL;
	char buff[BUFF_SIZE];
	size_t tempStrLen = 0;

	buff[0] = '\0';

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//add the NAP to the first NSP we find in the db
	for(i = 0 ; i < WMX_NSPS_MAX_NUM ; i++)
	{
		tempStrLen = strnlen(g_pL4dbContext->nsps[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			OSAL_strcpy_s(buff, BUFF_SIZE, "NAP_ID_");

			l4db_ConvertNapIdToStr(napID, buff + strlen("NAP_ID_"));

			//allocate a new NAP
			pNap = l4db_AllocCaplNap(g_pL4dbContext->nsps->nwParams.capl.naps, buff);

			if(NULL != pNap)
			{
				memcpy(pNap->napID, napID, sizeof(pNap->napID));
				rc = WMX_ST_OK;
			}
			else
			{
				rc = WMX_ST_FAIL;
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"L4db_AddNapPatch: unable to allocate a new NAP");
			}
			break;
		}
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	return rc;
}
/// <summary>
/// checks if it is legal to add the given NSP ID to the DB. If irt exists in another NSP
/// or in the same NSP with a different tag name, it is illegal
/// </summary>
/// <param name="nspID">(IN) the requested NSP ID </param>
/// <param name="nspIdTagName">(IN) the nsp ID's tag name </param>
/// <param name="nspTagName">(IN) the nsp's tag name </param>
/// <returns>TRUE is legal and FALSE otherwise </returns>
BOOL l4db_IsLegalToAddNspId(wmx_NSPid_t nspID, char * nspIdTagName, char * nspTagName)
{
	int i, j;

	for( i = 0 ; i < WMX_NSPS_MAX_NUM ; i++)
	{
		//check if this is our NSP. If so, the nsp id shouldn't exist in 
		if(FALSE == l4db_CompareString(nspTagName, g_pL4dbContext->nsps[i].tagName))
		{
			for(j = 0 ; j < WMX_NSP_IDS_MAX_NUM ; j++)
			{
				if(nspID == g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId)
				{
					//if the tag names aren't equal, this NSP ID is invalid
					if(TRUE == l4db_CompareString(nspIdTagName, g_pL4dbContext->nsps[i].nwParams.hNsps[j].tagName))
					{
						return FALSE;
					}
				}
			}
		}

		//verify that this NSP ID doesn't exists in other NSPS
		for(j = 0 ; j < WMX_NSP_IDS_MAX_NUM ; j++)
		{
			if(nspID == g_pL4dbContext->nsps[i].nwParams.hNsps[j].nspId)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

pProvisionedNsp_t l4db_GetOperatorNode()
{
	return g_pL4dbContext->nsps;
}
/// <summary>
/// gets a pointer to the FUMO node in the db
/// </summary>
// MZUR TODO Varify there is only need for one FUMO node 
pFumoParams_t l4db_GetFumoNode()
{
	return g_pL4dbContext->fumoNodes;
}

wmx_Status_t L4db_GetFumoNode(pFumoParams_t FumoParams)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	memcpy(FumoParams,l4db_GetFumoNode(),sizeof(FumoParams_t));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;

}

wmx_Status_t L4db_GetFumoInternalInfo(pFumoInternalParams_t pFumoInternalParams)
{	
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	wmx_strncpy(pFumoInternalParams->fumoNodePath, MAX_APDO_PATH, 
		g_pL4dbContext->apdoInternalParams.fumoInternal.fumoNodePath,
		strnlen(g_pL4dbContext->apdoInternalParams.fumoInternal.fumoNodePath, MAX_APDO_PATH));

	wmx_strncpy(pFumoInternalParams->pkgPath, MAX_APDO_PATH, 
		g_pL4dbContext->apdoInternalParams.fumoInternal.pkgPath,
		strnlen(g_pL4dbContext->apdoInternalParams.fumoInternal.pkgPath, MAX_APDO_PATH));

	wmx_strncpy(pFumoInternalParams->pkgFileName, MAX_FILE_NAME_SIZE, 
		g_pL4dbContext->apdoInternalParams.fumoInternal.pkgFileName,
		strnlen(g_pL4dbContext->apdoInternalParams.fumoInternal.pkgFileName, MAX_FILE_NAME_SIZE));

	pFumoInternalParams->fumoOperation = g_pL4dbContext->apdoInternalParams.fumoInternal.fumoOperation;		

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

wmx_Status_t L4db_SetFumoInternalFumoNodePath(CHAR* fumoNodePath)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	wmx_strncpy(g_pL4dbContext->apdoInternalParams.fumoInternal.fumoNodePath, MAX_APDO_PATH, 
		fumoNodePath, strnlen(fumoNodePath, MAX_APDO_PATH));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;

}

wmx_Status_t L4db_SetFumoInternalPackagePath(CHAR* pkgPath)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//set the package path
	wmx_strncpy(g_pL4dbContext->apdoInternalParams.fumoInternal.pkgPath, MAX_APDO_PATH, pkgPath, 
		strnlen(pkgPath, MAX_APDO_PATH));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

wmx_Status_t L4db_SetFumoInternalPackageFileName(CHAR* pkgFileName)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//set the RF state
	wmx_strncpy(g_pL4dbContext->apdoInternalParams.fumoInternal.pkgFileName, MAX_FILE_NAME_SIZE, 
		pkgFileName, strnlen(pkgFileName, MAX_FILE_NAME_SIZE));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

wmx_Status_t L4db_SetFumoInternalFumoOperation(FumoOperation_t op)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	//set the fumo operation
	g_pL4dbContext->apdoInternalParams.fumoInternal.fumoOperation = op;	

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

wmx_Status_t L4db_UpdateFromNVM()
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 	
	unsigned char	 macAddress[BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_BYTES_SIZE];
	wmx_ModelType_t  modelType;
	wmx_Manufacturer_t manufacturerId;
	wmx_SerialNumber_t serialNumber;
	wmx_NvmVersion_t nvmVersion;
	wmx_Nonce_t nonce;
	wmx_DeviceVersion_t versions;
	wmx_ODMInfo_t odmInfo;

	size_t outSize = 0;
	CHAR manStr[WMX_MANUFACTURER_NAME_MAX_LENGTH];
	CHAR modStr[WMX_MODEL_TYPE_NAME_MAX_LENGTH];
	CHAR macHex[BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_BYTES_SIZE*2 + 1];
	
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, L"Update l4db from NVM.");

	rc = wmx_GetDeviceDetailsEx((wmx_MacAddress_t)&macAddress, &modelType, &manufacturerId, &serialNumber, 
		(wmx_pNvmVersion_t)&nvmVersion, (wmx_pODMInfo_t)&odmInfo, (wmx_pNonce_t)&nonce);

	if (rc != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, L"Failed to get device details.");
		return rc;
	}

	rc = wmx_GetDeviceVersion(&versions);

	if (rc != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, L"Failed to get device version.");
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);
	// Convert all WCHAR to CHAR
	wcstombs_s(&outSize, manStr, WMX_MANUFACTURER_NAME_MAX_LENGTH, manufacturerId.manufacturerName, 
		WMX_MANUFACTURER_NAME_MAX_LENGTH);
	wcstombs_s(&outSize, modStr, WMX_MODEL_TYPE_NAME_MAX_LENGTH, modelType.modelTypeName, 
		WMX_MODEL_TYPE_NAME_MAX_LENGTH);

	NDnSAgent_HexEncode(macAddress, macHex, BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_BYTES_SIZE);

	// Update DevInfo nodes
	wmx_strncpy(g_pL4dbContext->devInfo.devID, MAX_DEV_ID_SIZE, macHex, strnlen(macHex, MAX_DEV_ID_SIZE));		
	//wmx_strncpy(g_pL4dbContext->devInfo.manufacturer, MAX_MAN_NAME_SIZE, manStr, WMX_MANUFACTURER_NAME_MAX_LENGTH);
	//wmx_strncpy(g_pL4dbContext->devInfo.model, MAX_MOD_NAME_SIZE, modStr, WMX_MODEL_TYPE_NAME_MAX_LENGTH);

	// Update WiMAXRadioModule nodes	
	wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].macAddress, MAX_DEV_ID_SIZE, macHex, strnlen(macHex, MAX_DEV_ID_SIZE));
	wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.manufacturer, MAX_MAN_NAME_SIZE, manStr, 
		WMX_MANUFACTURER_NAME_MAX_LENGTH);
	wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.model, MAX_MOD_NAME_SIZE, modStr, 
		WMX_MODEL_TYPE_NAME_MAX_LENGTH);
		
	wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.fwVersion, MAX_VERSION_SIZE, 
		versions.Software, WMX_DEVICE_VERSION_MAX_LENGTH);
	wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.hwVersion, MAX_VERSION_SIZE, 
		versions.Asic, WMX_DEVICE_VERSION_MAX_LENGTH);		
	/*wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.swVersion, MAX_VERSION_SIZE, 
		versions.Software, WMX_DEVICE_VERSION_MAX_LENGTH);		
	*/
	l4db_BuildVersionString(g_pL4dbContext->devDetail.ext.SwV2);

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

wmx_Status_t L4db_SetInstallStatus(FUMOInstallStatus_t status)
{
	wmx_Status_t rc = WMX_ST_MODULE_NOT_INITIALIZED; 

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return rc;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	g_pL4dbContext->apdoInternalParams.installStatus = status;

	OSAL_exit_critical_section(&g_L4dbLock);

	return rc;
}

/// <summary>
/// This function takes the nsp name and makes sure there is an enrty for that name in the NSPsToDMAcc list.
/// </summary>
wmx_Status_t l4db_AddNSPToNSPsToDMAccStruct(CHAR tagName[MAX_TAG_NAME_SIZE])
{
	UINT32 i;
	int freeIndex = -1;

	for (i=0; i<WMX_NSPS_TO_DMACC_NODES_MAX_NUM; i++)
	{
		if(0 == strnlen(g_pL4dbContext->apdoInternalParams.nspsToDmAcc[i].tagName, MAX_TAG_NAME_SIZE))
		{
			// We didn't find this NSP in the list but found an empty slot for it
			freeIndex = i;
			break;
		}
		else if(FALSE == l4db_CompareString(tagName, g_pL4dbContext->apdoInternalParams.nspsToDmAcc[i].tagName))
		{
			// This NSP is already in the list.
			return WMX_ST_OK;
		}
	}

	if (freeIndex == -1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"l4db_AddNSPToNSPsToDMAccStruct - list is in maximum capacity.");
		// Failed to find empty slot
		return WMX_ST_FAIL;
	}
	
	wmx_strncpy(g_pL4dbContext->apdoInternalParams.nspsToDmAcc[freeIndex].tagName,
		sizeof(g_pL4dbContext->apdoInternalParams.nspsToDmAcc[freeIndex].tagName), 
		tagName, strnlen(tagName, MAX_TAG_NAME_SIZE));
		
	return WMX_ST_OK;
}
wmx_Status_t L4db_GetInstallationInfo(char* installVersion, size_t versionSize)
{
	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	OSAL_enter_critical_section(&g_L4dbLock);

	// MZUR - TODO - check if we can use the constant of version install
	wmx_strncpy(installVersion, versionSize, g_pL4dbContext->wimax.radioModules[0].productVersions.swVersion, 
		strnlen(g_pL4dbContext->wimax.radioModules[0].productVersions.swVersion, MAX_VERSION_SIZE - 1));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

// Set default version with "~" to show missing bin file
wmx_Status_t L4db_SetVersionDefault()
{
	CHAR packageVersion[MAX_VERSION_SIZE];
//	CHAR minorVersion[VERSION_SECTION_MAX_SIZE];
//	CHAR majorVersion[VERSION_SECTION_MAX_SIZE];
	//CHAR buildMajorVersion[VERSION_SECTION_MAX_SIZE];

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, L"L4db_SetVersionDefault - default version set.");

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}	

	//OSAL_itoa_s(PRODUCT_VERSION_MINOR, minorVersion, VERSION_SECTION_MAX_SIZE, 10);
	//OSAL_itoa_s(PRODUCT_VERSION_MAJOR, majorVersion, VERSION_SECTION_MAX_SIZE, 10);
	//OSAL_itoa_s(PRODUCT_BUILD_MAJOR, buildMajorVersion, VERSION_SECTION_MAX_SIZE, 10);

	wmx_strncpy(packageVersion, MAX_VERSION_SIZE, PRODUCT_VERSION_MAJOR, strnlen(PRODUCT_VERSION_MAJOR, VERSION_SECTION_MAX_SIZE - 1));
	strncat_s(packageVersion, MAX_VERSION_SIZE - VERSION_SECTION_MAX_SIZE, L4DB_XML_TOKEN_DOT, strlen(L4DB_XML_TOKEN_DOT));
	strncat_s(packageVersion, MAX_VERSION_SIZE - VERSION_SECTION_MAX_SIZE - 1, PRODUCT_VERSION_MINOR, VERSION_SECTION_MAX_SIZE - 1);
	strncat_s(packageVersion, MAX_VERSION_SIZE - VERSION_SECTION_MAX_SIZE, L4DB_XML_TOKEN_DOT, strlen(L4DB_XML_TOKEN_DOT));
	strncat_s(packageVersion, MAX_VERSION_SIZE - VERSION_SECTION_MAX_SIZE*2 - 1, PRODUCT_BUILD_MAJOR, 
		VERSION_SECTION_MAX_SIZE - 1);

	OSAL_enter_critical_section(&g_L4dbLock);

	// Copy to default radio module
	wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.swVersion, MAX_VERSION_SIZE,
		packageVersion, strnlen(packageVersion, MAX_VERSION_SIZE - 1));

	OSAL_exit_critical_section(&g_L4dbLock);

	return WMX_ST_OK;
}

// This function tries to get the version of the package from ver_info.bin file.
// If unsuccessfull it turns to default in ver_info.h.
wmx_Status_t L4db_UpdatePackageVersion()
{
	BOOL res;
	char* buff = NULL;
	size_t buffSize = VERSION_SECTION_MAX_SIZE*3 + 2; //size of each section xxx.yyy.zzz + 2 for dots...
	BOOL setDefaultVer = FALSE;
	WCHAR pRootPathW[MAX_REGISTRY_ANSWER] = {0};
	CHAR pRootPath[MAX_REGISTRY_ANSWER] = {0};
	size_t outSize = 0;
	CHAR* pVerFileName;
	size_t verFileNameSize;
	

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, L"L4db_UpdatePackageVersion - IN.");

	if(FALSE == g_fIsInitiated)
	{
		// Nobody init US ..., you should call init function
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}	

	// Build ver file name
	verFileNameSize = MAX_REGISTRY_ANSWER + strlen(VERSION_FILE_NAME);
	pVerFileName = (CHAR*)malloc(verFileNameSize);

	L4Configurations_getRootPath(pRootPathW);
	wcstombs_s(&outSize, pRootPath, MAX_REGISTRY_ANSWER, pRootPathW, wcsnlen(pRootPathW, MAX_REGISTRY_ANSWER));

	wmx_strncpy(pVerFileName, verFileNameSize, pRootPath, strnlen(pRootPath, MAX_REGISTRY_ANSWER));
	strncat_s(pVerFileName, verFileNameSize, L4DB_XML_TOKEN_SEPERATOR, strlen(L4DB_XML_TOKEN_SEPERATOR));
	strncat_s(pVerFileName, verFileNameSize, VERSION_FILE_NAME, strlen(VERSION_FILE_NAME));

	buff = (char*)malloc(buffSize);
	if(NULL == buff)
	{
		return WMX_ST_FAIL;
	}
	res = Crypt_DecryptFile(pVerFileName, buff, &buffSize);
	if (!res) 
	{
		free(buff);
		buff = (char*)malloc(buffSize);
		if(NULL == buff)
		{
			return WMX_ST_FAIL;
		}

		res = Crypt_DecryptFile(pVerFileName, buff, &buffSize);

		if (res == FALSE)
		{
			setDefaultVer = TRUE;
		}
	}		

	if ((setDefaultVer) || (buff == NULL))
	{
		L4db_SetVersionDefault();
	}
	// Set package version from decrypted buffer
	else
	{
		buff[buffSize] = 0;

		OSAL_enter_critical_section(&g_L4dbLock);
		wmx_strncpy(g_pL4dbContext->wimax.radioModules[0].productVersions.swVersion, MAX_VERSION_SIZE,
			buff, strnlen(buff, MAX_VERSION_SIZE));	
		OSAL_exit_critical_section(&g_L4dbLock);
	}

	if (buff != NULL)
	{
		free(buff);
	}	

	return WMX_ST_OK;
}
