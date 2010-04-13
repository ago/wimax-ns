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
#include "NDnSAgent_DB_Internal.h"
#include "L4ConfigurationManager.h"
#include "wmxSDK_Apdo_Cmn.h"		// @@@ : JSS : Corrected case name of the file
#include "NDnSAgent_Utils.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_crypt_services.h"

//This file includes methods for restoring data from the xml file

wmx_Status_t l4db_RestoreInternalStatesFromFile(pXmlElement pXml, pNdsSettings_t pSettings)
{
	int					i, j, k, numOfChildren, arrSize, intVal;
	pXmlElement			xmlNextData, xmlNextData2;
	const char			* str, *strValue;
	wmx_RfStatus_t		rfState;
	wmx_NSPid_t			nspID;
	wmx_NAPid_t			napID;


	numOfChildren = GetChildrenCount(pXml);

	//iterate through all the node's children
	for(i = 0 ; i < numOfChildren ; i++)
	{
		xmlNextData = GetChildAt(pXml, i);
		str = GetElementName(xmlNextData);

		//RF state
		if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_NDS_LAST_RF_STATE))
		{
			rfState = l4db_GetRfStateFromStr(GetElementInnerText(xmlNextData));
			pSettings->swRfState = rfState;
		}

		//setPreferredNspOnConnect State
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_NDS_SET_PREFERRED_NSP_ON_CONNECT))
		{
			pSettings->setPreferredNspOnConnect = l4db_ConvertToBoolVal(GetElementInnerText(xmlNextData));
		}
		//TH criteria
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_NDS_THCRITERIA))
		{
			arrSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < arrSize ; j++)
			{
				xmlNextData2 = GetChildAt(xmlNextData, j);
				str = GetElementName(xmlNextData2);

				if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_NDS_RSSI_THRESHOLD))
				{
					pSettings->thCriteria.rssiTH = ConvertToRssiTH(GetElementInnerText(xmlNextData2));
				} 
				else if (FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_NDS_CINR_THRESHOLD))
				{
					pSettings->thCriteria.cinrTH = ConvertToCinrTH(GetElementInnerText(xmlNextData2));
				}
			}
		}
		//Connecting mode
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_USER_CONNECTING_MODE))
		{
			pSettings->connectMode = ConvertToConnectMode(GetElementInnerText(xmlNextData));
		}

		//AllowAutoActivate
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_ALLOW_AUTO_ACTIVATE))
		{
			pSettings->allowAutoActivate = l4db_ConvertToBoolVal(GetElementInnerText(xmlNextData));
		}

		//AllowFastReconnect
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_ALLOW_FAST_RECONNECT))
		{
			pSettings->allowFastReconnect = l4db_ConvertToBoolVal(GetElementInnerText(xmlNextData));
		}

		//Roaming mode
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ROAMING_MODE))
		{
			strValue = GetElementInnerText(xmlNextData);
			intVal = ConvertToRoamingMode(strValue);
			pSettings->roamingMode = intVal;
		}
		//Current preferred NSP
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CURRENT_PREFERRED_NSP))
		{
			strValue = GetElementInnerText(xmlNextData);
			nspID = (wmx_NSPid_t)atoi(strValue);
			pSettings->currentPreferredNSP = nspID;
		}		

		//Unprovisioned profiles
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_UNPROVISIONED_PROFILES))
		{
			l4db_RestoreProfilesFromFile(xmlNextData, (pProfile_t)pSettings->unprovisionedProfiles, &pSettings->unprovisionedProfilesSize);
		}
		//Last connected NSP
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LAST_CONNETED_NSPS))
		{
			arrSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < arrSize ; j++)
			{
				xmlNextData2 = GetChildAt(xmlNextData, j);
				str = GetElementName(xmlNextData2);
				
				// The NSP ID of the last connected NSP
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LAST_CONNETED_NSP_ID))
				{
					nspID = (wmx_NSPid_t)atoi(GetElementInnerText(xmlNextData2)); //get the NSP ID

					pSettings->lastConnectedNSP.recentNspID = nspID;
				}
				// NAP IDs of the last connected NSP. Update the counter of the NAP IDs
				else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LAST_CONNETED_NAP_IDS))
				{					
					pSettings->lastConnectedNSP.numOfConnectedNapIDs = GetChildrenCount(xmlNextData2);

					for (k=0; k < (int)pSettings->lastConnectedNSP.numOfConnectedNapIDs; k++)
					{						
						strValue = GetElementInnerText(GetChildAt(xmlNextData2, k));

						l4db_SetNapidEmpty((wmx_pNAPid_t)&napID);
						l4db_ConvertNapIdStrToNapIdType(napID, strValue);
						memcpy(pSettings->lastConnectedNSP.lastConnectedNapIDs[k], napID, sizeof(wmx_NAPid_t));
					}
				}
			}			
		}		
	}
	return WMX_ST_OK;
}


///<summary>
/// Restores the contacts node from a file
///</summary>
wmx_Status_t l4db_RestoreContactsFromFile(pXmlElement pXml, pProvisionedNsp_t pNsp)
{
	pXmlElement		xmlContactsData;
	pXmlElement		nextData;
	int				i, j, contactsSize, childrenSize;
	const char		*str, *strValue;
	wmx_Status_t	rc = WMX_ST_OK;
	wmx_APDOType_t	apdoType;
	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew.
	pContactsInfo_t pAllocContact;

	contactsSize = GetChildrenCount(pXml);

	for(i = 0 ; i < contactsSize ; i++)
	{
		xmlContactsData = GetChildAt(pXml, i);
		str = GetElementName(xmlContactsData); //unique tag name

		//set the entry's unique data
		apdoType = APDO_String;
		pAllocContact = l4db_AllocContactInfo(pNsp->contacts, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

		if(NULL == pAllocContact)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_RestoreInternalStatesFromFile: too many contacts in recent contacts tag in the xml");
			return WMX_ST_FAIL;
		}

		childrenSize = GetChildrenCount(xmlContactsData);
		
		//iterate through all of the children of this contact node
		for(j = 0 ; j < childrenSize ; j++)
		{
			nextData = GetChildAt(xmlContactsData, j);
			str = GetElementName(nextData);
			strValue = GetElementInnerText(nextData);

			//uri type
			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TYPE))
			{
				pAllocContact->uriType = (UINT16)atoi(strValue);
				rc = WMX_ST_OK;
			}

			//uri
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_URI))
			{
				rc = l4db_SetStringValueNew(pAllocContact->uri, sizeof(pAllocContact->uri), 
											(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}
			//text
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TEXT))
			{
				rc = l4db_SetStringValueNew(pAllocContact->text, sizeof(pAllocContact->text), 
											(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}
		}
	}

	return rc;
}
///<summary>
/// restores a channel plan node from a file to a struct
///</summary>
wmx_Status_t l4db_RestoreChannelPlanFromFile(pXmlElement pXml, pChannelPlan_t pChannelPlan)
{
	int					i, j, k,  numOfChildren, arrSize, channelInfoArrSize;
	pXmlElement			xmlNextData, xmlNextData2, xmlNextData3;
	const char			* str;
	const char			* innerStr;
	wmx_APDOType_t		apdoType;
//	int					dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_Status_t		rc = WMX_ST_OK;
	pChannelInfo_t		pChannelInfo;


	numOfChildren = GetChildrenCount(pXml);

	//iterate through all the node's children
	for(i = 0 ; i < numOfChildren ; i++)
	{
		xmlNextData = GetChildAt(pXml, i);
		str = GetElementName(xmlNextData);

		//channel infos
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ENTRIES))
		{			
			arrSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < arrSize ; j++)
			{
				xmlNextData2 = GetChildAt(xmlNextData, j); //get the node's unique name
				str = GetElementName(xmlNextData2);

				//set the node's unique name
				apdoType = APDO_String;
				pChannelInfo = l4db_AllocChannelInfo(pChannelPlan, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

				if(NULL == pChannelInfo)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreChannelPlanFromFile unable to allocate a new channel");
					return WMX_ST_FAIL;
				}

				pChannelInfo->lastFoundInNbrAdv = FALSE;
				pChannelInfo->ttl = 0; // Set a default value for the case the TTL was not yet in the .XML file (backward compatibility)
				channelInfoArrSize = GetChildrenCount(xmlNextData2);
	
				for(k = 0 ; k < channelInfoArrSize ; k++)
				{
					xmlNextData3 = GetChildAt(xmlNextData2, k);
					str = GetElementName(xmlNextData3);

					//channel id
					if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ID))
					{
						innerStr = GetElementInnerText(xmlNextData3);
						OSAL_strncpy_s(pChannelInfo->id, MAX_REF_ID_NAME_SIZE, innerStr, OSAL_strnlen(innerStr, MAX_REF_ID_NAME_SIZE));
					}
					//first frequency
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FIRST_FREQ))
					{
						pChannelInfo->firstFreq = (UINT32)atoi(GetElementInnerText(xmlNextData3));
					}
					//last frequency
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LAST_FREQ))
					{
						pChannelInfo->lastFreq = (UINT32)atoi(GetElementInnerText(xmlNextData3));
					}
					//next frequency step
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NEXT_FREQ_STEP))
					{
						pChannelInfo->nextFreq = (UINT32)atoi(GetElementInnerText(xmlNextData3));
					}
					//BW
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_BW))
					{
						rc = ConvertToBandWidth(GetElementInnerText(xmlNextData3), &(pChannelPlan->channels[j].bw));
						
						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					//FFT size
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FFT_SIZE))
					{
						rc = ConvertToFFT(GetElementInnerText(xmlNextData3) ,&(pChannelPlan->channels[j].fft));

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					//duplex mode
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DUPLEX_MODE))
					{
						pChannelInfo->duplexMode = atoi(GetElementInnerText(xmlNextData3));
					}
					//preambles
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PREAMBLES))
					{
						ConvertToPreamblesBitmap(pChannelInfo->preambleBitmap, GetElementInnerText(xmlNextData3));
					}
					//time to live
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TTL))
					{
						pChannelInfo->ttl = atoi(GetElementInnerText(xmlNextData3));						
						if (pChannelInfo->ttl == L4DB_MAX_TTL) // this is a channel from neighbor adv.
						{
							pChannelInfo->lastFoundInNbrAdv = TRUE;
						}
					}
				}
			}

			//set the channel size
			pChannelPlan->channelsSize = arrSize;
		}
		//BW
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_BW))
		{
			rc = ConvertToBandWidth(GetElementInnerText(xmlNextData), &pChannelPlan->bw);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
		//FFT size
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FFT_SIZE))
		{
			 rc = ConvertToFFT(GetElementInnerText(xmlNextData), &pChannelPlan->fft);

			 if(WMX_ST_OK != rc)
			 {
				 return rc;
			 }
		}
		//duplex mode
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DUPLEX_MODE))
		{
			pChannelPlan->duplexMode = atoi(GetElementInnerText(xmlNextData));
		}
	}

	// Delete duplicated channels.
	L4db_DeleteDuplicatedChannels(&pChannelPlan->channelsSize, (pChannelInfo_t)&(pChannelPlan->channels), TRUE);

	return rc;
}





///<summary>
/// restores the Wide Scan Parameters node from a file
///</summary>
wmx_Status_t l4db_RestoreWideScanParamsFromFile(pXmlElement pXml, pChannelPlan_t pChannelPlan)
{
	wmx_Status_t		rc;
	pXmlElement			xmlNextData;
	xmlNextData = GetChildAt(pXml, 0);

	rc = l4db_RestoreChannelPlanFromFile(xmlNextData, pChannelPlan);

	if(WMX_ST_OK != rc)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_RestoreWideScanParamsFromFile return status %d", rc);
		return rc; 
	}

	return rc;
}
///<summary>
/// restores the Link Loss Parameters node from a file
///</summary>
wmx_Status_t l4db_RestoreLinkLossParamsFromFile(pXmlElement pXml,
												pLinkLossParameters_t pShortLinkLossParams,
												pLinkLossParameters_t pLongLinkLossParams)
{
	int						i, j,  numOfChildren, arrSize, intArg, size_arg;
	pXmlElement				xmlNextData, xmlNextData2;
	const char				* linkLossTypeStr, *strValue, *str;
	wmx_APDOType_t			apdoType;
	wmx_Status_t			rc = WMX_ST_OK;

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all the node's children
	for(i = 0 ; i < numOfChildren ; i++)
	{
		xmlNextData = GetChildAt(pXml, i);
		linkLossTypeStr = GetElementName(xmlNextData);

		arrSize = GetChildrenCount(xmlNextData);

		for(j = 0 ; j < arrSize ; j++)
		{
			xmlNextData2 = GetChildAt(xmlNextData, j);
			str = GetElementName(xmlNextData2);
			strValue = GetElementInnerText(xmlNextData2);
			
			apdoType = APDO_Integer;
			size_arg = sizeof(intArg);
			OSAL_sscanf_s(strValue, "%d", &intArg);

			//short link loss params
			if(FALSE == l4db_CompareString(linkLossTypeStr, L4DB_XML_TOKEN_SHORT_LINK_LOSS))
			{
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TIMER))
				{
					rc = l4db_SetIntegerValueNew((int *)&pShortLinkLossParams->time, &size_arg,
						&intArg, &apdoType, APDO_AddCmd);	

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_REPETITION))
				{
					rc = l4db_SetIntegerValueNew((int *)&pShortLinkLossParams->repetition, &size_arg,
					&intArg, &apdoType, APDO_AddCmd);

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
			}

			//long link loss params
			if(FALSE == l4db_CompareString(linkLossTypeStr, L4DB_XML_TOKEN_LONG_LINK_LOSS))
			{
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TIMER))
				{
					rc = l4db_SetIntegerValueNew((int *)&pLongLinkLossParams->time, &size_arg,
						&intArg, &apdoType, APDO_AddCmd);	

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_REPETITION))
				{
					rc = l4db_SetIntegerValueNew((int *)&pLongLinkLossParams->repetition, &size_arg,
						&intArg, &apdoType, APDO_AddCmd);

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
			}
		}
	}
	return WMX_ST_OK;
}

///<summary>
/// restores the NAP change count parametres node from a file
///</summary>
wmx_Status_t l4db_RestoreDiscoveredNapInfoFromFile(pXmlElement pXml, pDiscoveredNap_t pNapsInfo)
{
	pXmlElement		xmlEntryData, xmlNapData, xmlNSPData;
	int				i, j, k, entriesSize, napDataSize, arrSize, size_arg, intArg, numOfNsps = 0;
	const char		*str, *strValue, *attrValue;
	wmx_NAPid_t		napID;
	wmx_APDOType_t	apdoType;
	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_Status_t	rc = WMX_ST_OK;
	BOOL			boolArg;

	entriesSize = GetChildrenCount(pXml);

	//check that the size doesn't exceed the max size
	if(WMX_NAPS_MAX_NUM < entriesSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_RestoreOtherNapInfoFromFile: too many NAP entries in the discovered nap tag in the xml file");
		return WMX_ST_CONFIG_ERROR;
	}

	for(i = 0 ; i < entriesSize ; i++)
	{
		xmlEntryData = GetChildAt(pXml, i);
		str = GetElementName(xmlEntryData);
		strValue = GetElementInnerText(xmlEntryData);
		
		//all entries are supposed to be of type NAP
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NAP))
		{
			//get and set the NAP ID
			numOfNsps = 0;
			attrValue = GetAttributeValueAt(xmlEntryData, 0);
			l4db_ConvertNapIdStrToNapIdType(napID, attrValue);
			memcpy(&pNapsInfo[i].napID, &napID, sizeof(pNapsInfo[i].napID));

			napDataSize = GetChildrenCount(xmlEntryData);

			for(j = 0 ; j < napDataSize ; j++)
			{
				xmlNapData = GetChildAt(xmlEntryData, j);
				str = GetElementName(xmlNapData);
				strValue = GetElementInnerText(xmlNapData);

				//NSP
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NSP))
				{
					//check that we didn't exceed the amount of allowed NSPS
					if(MAX_NUM_OF_DISCOVERED_NSPS <= numOfNsps)
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreOtherNapInfoFromFile: too many NSP entries under the discovered naps tag in the xml file");
						return WMX_ST_CONFIG_ERROR;
					}

					//get and set the NSP ID
					attrValue = GetAttributeValueAt(xmlNapData, 0);

					OSAL_sscanf_s(attrValue, "%d", &intArg);
					size_arg = sizeof(intArg);
					apdoType = APDO_Integer;

					rc = l4db_SetIntegerValueNew((int *)&pNapsInfo[i].nspInfo[numOfNsps].nspID, &size_arg,
						&intArg, &apdoType, APDO_AddCmd);

					//get other NSP values
					arrSize = GetChildrenCount(xmlNapData);

					for(k = 0 ; k < arrSize ; k++)
					{
						xmlNSPData = GetChildAt(xmlNapData, k);
						str = GetElementName(xmlNSPData);
						strValue = GetElementInnerText(xmlNSPData);
						apdoType = APDO_String;

						//16g name
						if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NAME))
						{
							rc = l4db_SetStringValueNew(pNapsInfo[i].nspInfo[numOfNsps].name,
												sizeof(pNapsInfo[i].nspInfo[numOfNsps].name), 
												(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);
							/*if(WMX_ST_OK != rc)
							{
								return rc;
							}*/
						}

						//16g visited realm
						if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_VISITED_REALM))
						{
							rc = l4db_SetStringValueNew(pNapsInfo[i].nspInfo[numOfNsps].visitedRealm,
								sizeof(pNapsInfo[i].nspInfo[numOfNsps].visitedRealm), 
								(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);
							/*if(WMX_ST_OK != rc)
							{
								return rc;
							}*/
						}
					}

					numOfNsps++;
				}

				//last detected
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LAST_DETECTED))
				{
					boolArg = l4db_ConvertToBoolVal(strValue);
					apdoType = APDO_Bool;
					size_arg = sizeof(boolArg);

					rc = l4db_SetBoolValueNew((BOOL *)&pNapsInfo[i].isLastDetected, &size_arg,
						&boolArg, &apdoType, APDO_AddCmd);	

					/*if(WMX_ST_OK != rc)
					{
						return rc;
					}*/
				}				

				//Change count
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CHANGE_COUNT))
				{
					OSAL_sscanf_s(strValue, "%d", &intArg);
					size_arg = sizeof(intArg);
					apdoType = APDO_Integer;

					rc = l4db_SetIntegerValueNew((int *)&pNapsInfo[i].changeCount, &size_arg,
						&intArg, &apdoType, APDO_AddCmd);	
					/*if(WMX_ST_OK != rc)
					{
						return rc;
					}*/
				}

				//Channel plan
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CHANNEL_PLAN))
				{
					rc = l4db_RestoreChannelPlanFromFile(xmlNapData, &pNapsInfo[i].channelPlan);
					/*if(WMX_ST_OK != rc)
					{
						return rc;
					}*/
				}
			}

			//update the number of nsps
			size_arg = sizeof(intArg);
			apdoType = APDO_Integer;
			rc = l4db_SetIntegerValueNew((int*)&pNapsInfo[i].nspInfoSize, &size_arg,	&numOfNsps, &apdoType, APDO_AddCmd);

			/*if(WMX_ST_OK != rc)
			{
				return rc;
			}*/

		}
	}

	return rc;
}



///<summary>
/// restores the Apdo Operator Configurations parametres node from a file
///</summary>
wmx_Status_t l4db_RestoreApdoOperatorConfigurationsFromFile(pXmlElement pXml, wmx_pApdoOperatorConfigurations_t pApdoOperatorConfigurations)
{
	int						i,j, k, numOfChildren, numOfOperators =0, numOfFields=0;
	const char				*str;
	pXmlElement				xmlData, xmlOperatorsFields, xmlDataOperators;
	wmx_Status_t			rc = WMX_ST_OK;
	BOOL					returnValue = FALSE;

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);	
		str = GetElementName(xmlData);
 
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_OPERATOR))
		{
			numOfOperators = GetChildrenCount(xmlData);
			//iterate through all of the operators
			for (j=0 ; j < numOfOperators ; j++)
			{
				xmlDataOperators = GetChildAt(xmlData,j);
				str = GetElementName(xmlDataOperators);
				if (str != '\0'){
					OSAL_memcpy_s(&pApdoOperatorConfigurations[j].nspTagName, (sizeof(char)*MAX_SIZE_OF_NSP_NAME), str, (sizeof(char)*MAX_SIZE_OF_NSP_NAME));
					numOfFields = GetChildrenCount(xmlDataOperators);
					for (k=0 ; k < numOfFields ; k ++)
					{
						xmlOperatorsFields = GetChildAt(xmlDataOperators,k);
						str = GetElementName(xmlOperatorsFields);
						if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PRE_PROVISIONS_BSTRAP))
						{
							str = GetElementInnerText(xmlOperatorsFields);
							returnValue = (OSAL_stricmp(str, L4DB_XML_TRUE_STR));
							if (returnValue != 0) 
							{
								returnValue = 0;
							}
							else	
							{
								returnValue = 1;
							}
							pApdoOperatorConfigurations[j].preProvBStrap = returnValue;
						}
						if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_POLLING_INTERVAL))
						{
							str = GetElementInnerText(xmlOperatorsFields);
							returnValue = (OSAL_stricmp(str, L4DB_XML_TRUE_STR));
							if (returnValue != 0) 
							{
								returnValue = 0;
							}
							else	
							{
								returnValue = 1;
							}
							pApdoOperatorConfigurations[j].pollingInterval = returnValue;
						}
						if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_POLLING_ATTEMPTS))
						{
							str = GetElementInnerText(xmlOperatorsFields);
							returnValue = (OSAL_stricmp(str, L4DB_XML_TRUE_STR));
							if (returnValue != 0) 
							{
								returnValue = 0;
							}
							else	
							{
								returnValue = 1;
							}
							pApdoOperatorConfigurations[j].pollingAttempts = returnValue;
						}
						if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_BLOCK_UDP))
						{
							str = GetElementInnerText(xmlOperatorsFields);
							returnValue = (OSAL_stricmp(str, L4DB_XML_TRUE_STR));
							if (returnValue != 0) 
							{
								returnValue = 0;
							}
							else	
							{
								returnValue = 1;
							}
							pApdoOperatorConfigurations[j].blockUDP = returnValue;
						}
						if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DISABLE_OTAP))
						{
							str = GetElementInnerText(xmlOperatorsFields);
							returnValue = (OSAL_stricmp(str, L4DB_XML_TRUE_STR));
							if (returnValue != 0) 
							{
								returnValue = 0;
							}
							else	
							{
								returnValue = 1;
							}
							pApdoOperatorConfigurations[j].disableOTAP = returnValue;
						}
						if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DISABLE_PSEUDO_NAI))
						{
							str = GetElementInnerText(xmlOperatorsFields);
							returnValue = (OSAL_stricmp(str, L4DB_XML_TRUE_STR));
							if (returnValue != 0) 
							{
								returnValue = 0;
							}
							else	
							{
								returnValue = 1;
							}
							pApdoOperatorConfigurations[j].disablePseudoNAI = returnValue;
						}
					}
				}
			}
		}
	}
	return rc;
}
///<summary>
/// restores the profile parametres node from a file
///</summary>
wmx_Status_t l4db_RestoreProfilesFromFile(pXmlElement pXml, pProfile_t pProfilesInfo, UINT32 *pNumOfProfiles)
{
	pXmlElement		xmlEntryData, xmlProfileData;
	int				i, j, entriesSize, profileDataSize;
	const char		*str, *strValue;	
	wmx_NAPid_t		napID;
	wmx_Status_t	rc = WMX_ST_OK;		
	UINT32 tempNumOfProfiles = 0;

	entriesSize = GetChildrenCount(pXml);

	//check that the size doesn't exceed the max size
	if(WMX_PROFILES_MAX_NUM < entriesSize)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_RestoreProfilesFromFile: too many profile entries in the unprovisioned profiles tag in the xml file");
		return WMX_ST_CONFIG_ERROR;
	}

	for(i = 0 ; i < entriesSize ; i++)
	{
		xmlEntryData = GetChildAt(pXml, i);
		str = GetElementName(xmlEntryData);		

		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_UNPROVISIONED_PROFILE))
		{						
			profileDataSize = GetChildrenCount(xmlEntryData);
			tempNumOfProfiles++;

			for(j = 0 ; j < profileDataSize ; j++)
			{
				xmlProfileData = GetChildAt(xmlEntryData, j);
				str = GetElementName(xmlProfileData);
				strValue = GetElementInnerText(xmlProfileData);

				// NAP ID
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NAP_ID_DASH))
				{
					l4db_ConvertNapIdStrToNapIdType(napID, strValue);
					OSAL_memcpy_s(&pProfilesInfo[i].napID, sizeof(pProfilesInfo[i].napID), &napID, sizeof(pProfilesInfo[i].napID));					
				}

				// last detected channel plan
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CHANNEL_PLAN))
				{
					rc = l4db_RestoreChannelPlanFromFile(xmlProfileData, &pProfilesInfo[i].channelPlan);
					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}	
				// NSP ID
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NSP_ID_DASH))
				{
					OSAL_sscanf_s(strValue, "%d", &pProfilesInfo[i].nspID);					
				}					
			}
		}
	}
	*pNumOfProfiles = tempNumOfProfiles;
	return rc;
}

///<summary>
/// restores the device certificates node from a file
///</summary>
wmx_Status_t l4db_RestoreDeviceCertificatesFromFile(pXmlElement pXml, pDeviceCertificates_t pDeviceCerts)
{
	int						i, numOfChildren;
	const char				*str, *strValue;
	pXmlElement				xmlNextData;

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the node's children
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlNextData = GetChildAt(pXml, i);
		str = GetElementName(xmlNextData);
		strValue = GetElementInnerText(xmlNextData);

		//root certificate
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ROOT_CERT))
		{
			OSAL_strncpy_s(pDeviceCerts->rootCert, MAX_FILE_NAME_SIZE , strValue, MAX_FILE_NAME_SIZE - 1);
		}

		//client certificate
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CLIENT_CERT))
		{
			OSAL_strncpy_s(pDeviceCerts->clientCert, MAX_FILE_NAME_SIZE, strValue, MAX_FILE_NAME_SIZE-1);
		}

		//private key
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PRIVATE_KEY))
		{
			OSAL_strncpy_s(pDeviceCerts->privateKey, MAX_FILE_NAME_SIZE, strValue,MAX_FILE_NAME_SIZE -1);
		}
	}

	return WMX_ST_OK;
}


///<summary>
/// restores the HNSP node, under network parameters, from a file
///</summary>
wmx_Status_t l4db_RestoreHnspsFromFile(pXmlElement pXml, pHomeNsp_t pHnsps)
{
	pXmlElement		xmlEnumeratorData , xmlHnspData;
	int				j, k, arrSize, collectSize, intArg, size_arg;
	const char		*str, *strValue;
	wmx_APDOType_t	apdoType;
//	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_Status_t	rc = WMX_ST_OK;
	pHomeNsp_t		pAllocHnsp;

	collectSize = GetChildrenCount(pXml);

	for(j = 0 ; j < collectSize ; j++)
	{
		xmlEnumeratorData = GetChildAt(pXml, j); //get the entry's unique name
		str = GetElementName(xmlEnumeratorData);

		//set the entry's unique data
		apdoType = APDO_String;
		pAllocHnsp = l4db_AllocHnsp(pHnsps, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

		if(NULL == pAllocHnsp)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreHnspsFromFile: too many H_NSP entries in the xml file");
			return WMX_ST_FAIL;
		}

		arrSize = GetChildrenCount(xmlEnumeratorData);

		for(k = 0 ; k < arrSize ; k++)
		{
			xmlHnspData = GetChildAt(xmlEnumeratorData, k);
			str = GetElementName(xmlHnspData);
			strValue = GetElementInnerText(xmlHnspData);

			//in both cases the value is an integer
			apdoType = APDO_Integer;
			OSAL_sscanf_s(strValue, "%d", &intArg);
			size_arg = sizeof(intArg);

			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_H_NSP_ID))
			{
				rc = l4db_SetIntegerValueNew((int *)&pAllocHnsp->nspId, &size_arg, &intArg, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}
		}
	}

	return rc;
}



///<summary>
/// restores a channel refs node from a file to a struct
///</summary>
wmx_Status_t l4db_RestoreChannelsRefsFromFile(pXmlElement pXml, pChPlanRefId_t pChannelsRefs)
{
	int					i, j, numOfChildren, arrSize;
	pXmlElement			xmlNextData, xmlNextData2;
	const char			* str;
	wmx_APDOType_t		apdoType;
	int					dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_Status_t		rc = WMX_ST_OK;

	numOfChildren = GetChildrenCount(pXml);

	//verify that the number of refs isn't too large
	if(WMX_CHANNELS_MAX_NUM < numOfChildren)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreChannelsRefsFromFile: too many channel refs");
		return WMX_ST_FAIL;
	}

	//iterate through all the node's children
	for(i = 0 ; i < numOfChildren ; i++)
	{
		xmlNextData = GetChildAt(pXml, i);
		str = GetElementName(xmlNextData); //the channel ref's unique name

		//set the node's unique name
		apdoType = APDO_String;
		rc = l4db_SetStringValueNew(pChannelsRefs[i].tagName, sizeof(pChannelsRefs[i].tagName),
			(char*)str + strlen(L4DB_TAG_NAME_PREFIX), &dummyStrLen, &apdoType, APDO_AddCmd);

		if(WMX_ST_OK != rc)
		{
			return rc;
		}

		arrSize = GetChildrenCount(xmlNextData);

		for(j = 0 ; j < arrSize ; j++)
		{
			xmlNextData2 = GetChildAt(xmlNextData, j); //get the node's unique name
			str = GetElementName(xmlNextData2);

			//channel id
			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_REF_ID))
			{
				apdoType = APDO_String;

				rc = l4db_SetStringValueNew(pChannelsRefs[i].id, sizeof(pChannelsRefs[i].id),
					(char *)GetElementInnerText(xmlNextData2), &dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}
		}
	}
	return rc;
}


///<summary>
/// restores the CAPL node, under network parameters, from a file
///</summary>
wmx_Status_t l4db_RestoreCaplFromFile(pXmlElement pXml, pCapl_t pCapl)
{
	pXmlElement		xmlEnumeratorData , xmlCapldata, xmlNextData;
	int				i, j, k, arrSize, collectSize, entrySize, intArg, size_arg;
	const char		*str, *strValue;
//	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_APDOType_t	apdoType = APDO_Integer;
	wmx_Status_t	rc = WMX_ST_OK;
	wmx_NAPid_t	    napID;
	pL4db_Nap_t		pAllocNap;
	arrSize = GetChildrenCount(pXml);

	for(i = 0 ; i < arrSize ; i++)
	{
		xmlNextData = GetChildAt(pXml, i); //get the nodes under CAPL
		str = GetElementName(xmlNextData);

		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ENTRIES))
		{
			collectSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < collectSize ; j++)
			{
				xmlEnumeratorData = GetChildAt(xmlNextData, j); //get the enrty's unique name
				str = GetElementName(xmlEnumeratorData);

				//set the entry's unique name
				apdoType = APDO_String;
				pAllocNap = l4db_AllocCaplNap(pCapl->naps, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

				if(NULL == pAllocNap)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreCaplFromFile: too many CAPL entries in the xml file");
					return WMX_ST_FAIL;
				}

				entrySize = GetChildrenCount(xmlEnumeratorData);

				for(k = 0 ; k < entrySize ; k++)
				{
					xmlCapldata = GetChildAt(xmlEnumeratorData, k);
					str = GetElementName(xmlCapldata);
					strValue = GetElementInnerText(xmlCapldata);

					if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NAP_ID))
					{
						l4db_SetNapidEmpty((wmx_pNAPid_t)&napID);
						//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"l4db_RestoreCaplFromFile: before l4db_ConvertNapIdStrToNapIdType strValue = [%s]", strValue);
						l4db_ConvertNapIdStrToNapIdType(napID, strValue);
						//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, L"l4db_RestoreCaplFromFile: l4db_ConvertNapIdStrToNapIdType napID = [%d][%d][%d][%d]", napID[0], napID[1], napID[2], napID[3]);
						memcpy(&pAllocNap->napID, &napID, sizeof(pAllocNap->napID));
						
						pCapl->napsSize++;

					}
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PRIORITY))
					{
						OSAL_sscanf_s(strValue, "%d", &intArg);
						size_arg = sizeof(intArg);
						apdoType = APDO_Integer;

						rc = l4db_SetIntegerValueNew((int *)&pAllocNap->priority, &size_arg,
							&intArg, &apdoType, APDO_AddCmd);	

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CH_PLAN_REF_IDS))
					{
						rc = l4db_RestoreChannelsRefsFromFile(xmlCapldata, pCapl->naps[j].channelPlanRefIds);
						
						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
				}
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ANY)) // TODO change
		{
			rc = ConvertToAnyType((char*)GetElementInnerText(xmlNextData), &pCapl->any);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SELECT_POLICY)) 
		{
			rc = ConvertToSelectPolicyType((char*)GetElementInnerText(xmlNextData), &pCapl->selectPolicy);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}		
	}

	return rc;
}


///<summary>
/// restores the RAPL node, under the network params node, from a file
///</summary>
wmx_Status_t l4db_RestoreRaplFromFile(pXmlElement pXml, pRapl_t pRapl)
{
	pXmlElement		xmlEnumeratorData , xmlRapldata, xmlNextData;
	int				i, j, k, arrSize, collectSize, entrySize, intArg, size_arg;
	const char		*str, *strValue;
	wmx_APDOType_t	apdoType = APDO_Integer;
//	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_Status_t	rc = WMX_ST_OK;
	pRoamingPartnerInfo_t pAllocRoamingInfo;

	arrSize = GetChildrenCount(pXml);

	for(i = 0 ; i < arrSize ; i++)
	{
		xmlNextData = GetChildAt(pXml, i); //get the nodes under CAPL
		str = GetElementName(xmlNextData);

		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ENTRIES))
		{
			collectSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < collectSize ; j++)
			{
				xmlEnumeratorData = GetChildAt(xmlNextData, j); //get the entry's unique name
				str = GetElementName(xmlEnumeratorData);

				//set the entry's unique name
				apdoType = APDO_String;
				pAllocRoamingInfo = l4db_AllocRoamingInfo(pRapl->roamingPartners, 
															(char*)str + strlen(L4DB_TAG_NAME_PREFIX));

				if(NULL == pAllocRoamingInfo)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreRaplFromFile: too many RAPL entries in the xml file");
					return WMX_ST_FAIL;
				}

				entrySize = GetChildrenCount(xmlEnumeratorData);
				
				//get the rapl data for the specific entry
				for(k = 0 ; k < entrySize ; k++)
				{	
					xmlRapldata = GetChildAt(xmlEnumeratorData, k);
					str = GetElementName(xmlRapldata);
					strValue = GetElementInnerText(xmlRapldata);

					//V_NSP_ID
					if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_V_NSP_ID))
					{
						pRapl->roamingPartnersSize++;

						OSAL_sscanf_s(strValue, "%d", &intArg);
						size_arg = sizeof(intArg);
						apdoType = APDO_Integer;

						rc = l4db_SetIntegerValueNew((int *)&pAllocRoamingInfo->vNspID, &size_arg,
							&intArg, &apdoType, APDO_AddCmd);	

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					//priority
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PRIORITY))
					{
						OSAL_sscanf_s(strValue, "%d", &intArg);
						size_arg = sizeof(intArg);
						apdoType = APDO_Integer;

						rc = l4db_SetIntegerValueNew((int *)&pAllocRoamingInfo->priority, &size_arg,
							&intArg, &apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
				}
			}

		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ANY))
		{
			rc = ConvertToAnyType((char*)GetElementInnerText(xmlNextData), &pRapl->any);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SELECT_POLICY)) 
		{
			rc = ConvertToSelectPolicyType((char*)GetElementInnerText(xmlNextData), &pRapl->selectPolicy);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}	
	}

	return rc;
}

///<summary>
/// restores an EAP node from a file
///</summary>
wmx_Status_t l4db_RestoreEapParamsFromFile(pXmlElement pXml, pEAP_t pEap)
{
	pXmlElement		xmlNextData, xmlEnumerationData, xmlCertData;
	pXmlElement		xmlSrvRealmData;
	int				i, j, k, arrSize, collectSize, certDataSize, size_arg, intArg;
	int				srvRealmDataSize; 
	BOOL			boolArg;
	const char		*str, *strValue;
	wmx_APDOType_t	apdoType = APDO_String;
	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	wmx_Status_t	rc = WMX_ST_OK;
//	CertType_t      certType;
	pCert_t			pAllocCert;
	errno_t			err;

	char *tmp; 


	arrSize = GetChildrenCount(pXml);

	for(i = 0 ; i< arrSize ; i++)
	{
		xmlNextData = GetChildAt(pXml, i);
		str = GetElementName(xmlNextData);
		strValue = GetElementInnerText(xmlNextData);
		intArg = L4DB_INVALID_INDEX;
		///////////////////////////////
		// Incremental NAI patch
		// TODO: Oran - remove once the problem in Sprint is fixed.
		//res = L4Configurations_getIncrementalNAI(&incrementalNAI);
		//if (res) // key found
		//{
		//	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Incremental NAI has been activated.");
		//	if (strValue[0] == '{')
		//	{
		//		char tempValue[20];
		//		char tempValue2[20];
		//		int tempIntValue;

		//		OSAL_memcpy_s(tempValue, 10, strValue + 6, 7);
		//		tempValue[7] = '\0';

		//		tempIntValue = atoi(tempValue);
		//		tempIntValue++;
		//		OSAL_itoa_s(tempIntValue, tempValue2, 20, 10);
		//		OSAL_memcpy_s(strValue + 6, 10, tempValue2, 7);
		//	}		
		//}	
		//EAP type
		if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_EAP_TYPE))//Sivanne
		{
	
			intArg = l4db_ConvertToEapTypeEnum((char*)strValue);
			size_arg = sizeof(intArg);
			apdoType = APDO_Integer;

			rc = l4db_SetIntegerValueNew((int *)&pEap->EAPMethod, &size_arg,
				&intArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//vendor id
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_VENDOR_ID))
		{
			OSAL_sscanf_s(strValue, "%d", &intArg);
			size_arg = sizeof(intArg);
			apdoType = APDO_Integer;

			rc = l4db_SetIntegerValueNew((int *)&pEap->vendorId, &size_arg,
					&intArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//vendor type
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_VENDOR_TYPE))
		{
			OSAL_sscanf_s(strValue, "%d", &intArg);
			size_arg = sizeof(intArg);
			apdoType = APDO_Integer;

			rc = l4db_SetIntegerValueNew((int *)&pEap->vendorType, &size_arg,
				&intArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//user name
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_USER_IDENTITY))
		{
			apdoType = APDO_String;

			tmp = (char *)GetElementInnerText(xmlNextData);

			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Id from strvalue: %s, from innerText: %s.", strValue, tmp);

			rc = l4db_SetStringValueNew(pEap->id, sizeof(pEap->id),
							tmp, &dummyStrLen, &apdoType, APDO_AddCmd);
		
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//provisioned pseudo id
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PROVISIONED_PSEUDO_ID))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pEap->provisionedPseudoId, sizeof(pEap->provisionedPseudoId),
				(char *)GetElementInnerText(xmlNextData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//password
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_PASSWORD))
		{
			if('\0' != xmlNextData->data.value[0])
			{
				//add only if the password is filled
				strValue = FindAttribute(xmlNextData, L4DB_XML_TOKEN_IS_ENCRYPTED_PASSWORD);
				if(FALSE == l4db_CompareString(strValue, L4DB_XML_TRUE_STR))
				{
					//the password is already encrypted
					err = OSAL_strncpy_s(pEap->Password, MAX_EAP_PASSWORD_SIZE, (char *)GetElementInnerText(xmlNextData), MAX_STR_LEN - 1);
					if(err)
					{
						return WMX_ST_FAIL;
					}
				}
				else
				{
					OSAL_Crypt_SetEncryptedPassword(pEap->Password, xmlNextData->data.value);
				}
			}
		}

		//realm
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_REALM))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pEap->realm, sizeof(pEap->realm),
				(char *)GetElementInnerText(xmlNextData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//use privacy
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_USE_PRIVACY))
		{
			boolArg = l4db_ConvertToBoolVal(strValue);
			apdoType = APDO_Bool;
			size_arg = sizeof(boolArg);
			rc = l4db_SetBoolValueNew(&pEap->usePrivacy, &size_arg, &boolArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//Encaps
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_ENCAPS))
		{
			OSAL_sscanf_s(strValue, "%d", &intArg);
			size_arg = sizeof(intArg);
			apdoType = APDO_Integer;			

			rc = l4db_SetIntegerValueNew((int *)&pEap->encaps, &size_arg,
				&intArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//VFY_SRV_Realm 
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_VFY_SERVER_REALM))
		{
			boolArg = l4db_ConvertToBoolVal(strValue);
			apdoType = APDO_Bool;
			size_arg = sizeof(boolArg);
			rc = l4db_SetBoolValueNew(&pEap->vfySrvRealm, &size_arg, &boolArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}

		}

		//srv realm 
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SERVER_REALMS))
		{
			collectSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < collectSize ; j++)
			{
				xmlEnumerationData = GetChildAt(xmlNextData, j); //get the node's unique name
				str = GetElementName(xmlEnumerationData);

				//set the node's unique name
				apdoType = APDO_String;
				rc = l4db_SetStringValueNew(pEap->srvRealms[j].tagName, sizeof(pEap->srvRealms[j].tagName),
											(char*)str + strlen(L4DB_TAG_NAME_PREFIX), &dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}

				srvRealmDataSize = GetChildrenCount(xmlEnumerationData);

				for(k = 0 ; k < srvRealmDataSize ; k++)
				{
					xmlSrvRealmData = GetChildAt(xmlEnumerationData, k);
					str = GetElementName(xmlSrvRealmData);
					strValue = GetElementInnerText(xmlSrvRealmData);
					
					//srv realm
					if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SERVER_REALM))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pEap->srvRealms[j].srvRealm, sizeof(pEap->srvRealms[j].srvRealm),
							(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
				}
			}
		}

		//cert
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CERT))
		{
			collectSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < collectSize ; j++)
			{
				xmlEnumerationData = GetChildAt(xmlNextData, j); //get the node's unique name
				str = GetElementName(xmlEnumerationData);

				//set the node's unique name
				apdoType = APDO_String;
				pAllocCert = l4db_AllocCert(pEap->certs, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

				if(NULL == pAllocCert)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreEapParamsFromFile: too many certs entries in the xml file");
					return WMX_ST_FAIL;
				}

				certDataSize = GetChildrenCount(xmlEnumerationData);

				for(k = 0 ; k < certDataSize ; k++)
				{
					xmlCertData = GetChildAt(xmlEnumerationData, k);
					str = GetElementName(xmlCertData);
					strValue = GetElementInnerText(xmlCertData);

					//cert type
					if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CERT_TYPE))
					{
						//ConvertToCertType(strValue, &certType);
						//size_arg = sizeof(intArg);
						/*apdoType = APDO_Integer;

						rc = l4db_SetIntegerValueNew((int *)&pAllocCert->certType, &size_arg,
							(int*)&certType, &apdoType, APDO_AddCmd);*/

						rc = l4db_SetStringValueNew((char*)pAllocCert->certType, sizeof(pAllocCert->certType),
							(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);
						
						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}

					//ser num
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SER_NUM))
					{
						rc = l4db_SetStringValueNew((char*)pAllocCert->serNum, sizeof(pAllocCert->serNum),
							(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					// ISSUER
					else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ISSUER))
					{
						rc = l4db_SetStringValueNew((char*)pAllocCert->issuer, sizeof(pAllocCert->issuer),
							(char*)strValue, &dummyStrLen, &apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					////thumb print
					//else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_THUMB_PRINT))
					//{
					//	OSAL_sscanf_s(strValue, "%d", &intArg);
					//	size_arg = sizeof(intArg);
					//	apdoType = APDO_Integer;

					//	rc = l4db_SetIntegerValueNew((int *)&pAllocCert->thumbPrint, &size_arg,
					//		&intArg, &apdoType, APDO_AddCmd);

					//	if(WMX_ST_OK != rc)
					//	{
					//		return rc;
					//	}
					//}
				}
			}
		}
	}
	return rc;
}

///<summary>
/// restores a single subscription param node from a file
///</summary>
wmx_Status_t l4db_RestoreSingleSubscriptionFromFile(pXmlElement pXml, pSubscriberInfo_t pSubsc)
{
	int				i, j, arrSize, size_arg, collectSize;
	pXmlElement		xmlNextData, xmlEnumerationData;
	wmx_Status_t	rc = WMX_ST_OK;
	wmx_APDOType_t	apdoType;
	pEAP_t			pAllocEap;
	const char		*str, *strValue;
	BOOL			boolArg;
	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	arrSize = GetChildrenCount(pXml);

	for(i = 0 ; i < arrSize ; i++)
	{
		xmlNextData = GetChildAt(pXml, i);
		str = GetElementName(xmlNextData);
		strValue = GetElementInnerText(xmlNextData);

		//Name
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NAME))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pSubsc->name, sizeof(pSubsc->name),
				(char *)GetElementInnerText(xmlNextData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}

		}

		//Activated
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_ACTIVATED))
		{
			boolArg = l4db_ConvertToBoolVal(strValue);
			apdoType = APDO_Bool;
			size_arg = sizeof(boolArg);
			rc = l4db_SetBoolValueNew(&pSubsc->activated, &size_arg, &boolArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//EAP
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_EAP))
		{
			collectSize = GetChildrenCount(xmlNextData);

			for(j = 0 ; j < collectSize ; j++)
			{
				xmlEnumerationData = GetChildAt(xmlNextData, j); //get the node's unique name
				str = GetElementName(xmlEnumerationData);

				//set the node's unique name
				apdoType = APDO_String;
				pAllocEap = l4db_AllocEap(pSubsc->eapInfo, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

				if(NULL == pAllocEap)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreSubscriptionParmFromFile: too many eap entries in the xml file");
					return WMX_ST_FAIL;
				}

				rc = l4db_RestoreEapParamsFromFile(xmlEnumerationData, pAllocEap);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
				else
				{
					// If we managed to read the eap entry we should increase the size
					pSubsc->eapInfoSize++;
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "l4db_RestoreSubscriptionParmFromFile: pAllocEap->tagName: %s. id: %s, realm: %s", 
										pAllocEap->tagName, pAllocEap->id ? pAllocEap->id : "un-available", pAllocEap->realm);
				}
			}
		}
	}
	return rc;
}

///<summary>
/// restores the subscription params node from a file
///</summary>
wmx_Status_t l4db_RestoreSubscriptionParmFromFile(pXmlElement pXml, pSubscriptionParams_t pSubscParam)
{
	pXmlElement		xmlSubscriptionParams, xmlNextData;
	int				i, j, subscriptionParamSize, arrSize;
	const char		*str;
	pOtherSubsInfo_t pAllocOtherSubsc;
	wmx_APDOType_t	apdoType;
	wmx_Status_t    rc = WMX_ST_OK;

	subscriptionParamSize = GetChildrenCount(pXml); 

	for(i = 0 ; i < subscriptionParamSize ; i++)
	{
		xmlSubscriptionParams = GetChildAt(pXml, i);
		str = GetElementName(xmlSubscriptionParams);

		//primary subscription
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PRIMARY))
		{
			rc = l4db_RestoreSingleSubscriptionFromFile(xmlSubscriptionParams, &pSubscParam->primary);
			
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
					
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Eap sections: %d. eapInfo[0].tagName: %s, eapInfo[1].tagName: %s.", 
				pSubscParam->primary.eapInfoSize, 
				pSubscParam->primary.eapInfo[0].tagName, 
				pSubscParam->primary.eapInfo[1].tagName);
		}

		//other subscription
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_OTHER_SUBSCRIPTIONS))
		{
			arrSize = GetChildrenCount(xmlSubscriptionParams);

			for(j = 0 ; j < arrSize ; j++)
			{
				xmlNextData = GetChildAt(xmlSubscriptionParams, j); // get the node's unique name
				str = GetElementName(xmlNextData);
				
				//set the node's unique name
				apdoType = APDO_String;
				pAllocOtherSubsc = l4db_AllocOtherSubsc(pSubscParam->other, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

				if(NULL == pAllocOtherSubsc)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreSubscriptionParmFromFile: too many other subscription entries in the xml file");
					return WMX_ST_FAIL;
				}

				rc = l4db_RestoreSingleSubscriptionFromFile(xmlNextData, &pAllocOtherSubsc->subscriberInfo);
				
				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}
		}
	}
	return rc;
}
/// <summary>
/// restore network parms from XML file
/// </summary>
/// <param name="pNsp">(OUT)  a pointer to the NSP struct that should be filled</param>
/// <param name="pXml">(IN) a pointer to the network params node in the xml</param>
/// <returns>wmx_Status_t </returns>
wmx_Status_t l4db_RestoreNetWorkParmFromFile(pXmlElement pXml, pNwParams_t pNwParams)
{
	pXmlElement		nextConfig;
	int				numOfChild;
	int				i, size_arg, intArg;
	const char		*str;
	wmx_APDOType_t	apdoType = APDO_String;
	int				dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	wmx_Status_t rc = WMX_ST_OK;

	numOfChild = GetChildrenCount(pXml);

	for(i = 0 ; i < numOfChild ; i++) //iterate through all the children of the network param node
	{
		nextConfig = GetChildAt(pXml, i);
		str = GetElementName(nextConfig);

		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_H_NSP))
		{
			rc = l4db_RestoreHnspsFromFile(nextConfig, pNwParams->hNsps);
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CAPL))
		{
			rc = l4db_RestoreCaplFromFile(nextConfig, &pNwParams->capl);
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_RAPL))
		{
			rc = l4db_RestoreRaplFromFile(nextConfig, &pNwParams->rapl);
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_OPERATOR_NAME))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pNwParams->provisionedName, sizeof(pNwParams->provisionedName)
				,(char *)GetElementInnerText(nextConfig), &dummyStrLen, &apdoType, APDO_AddCmd);
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		// ServerID
		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_SERVER_ID))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pNwParams->serverID, sizeof(pNwParams->serverID)
				,(char *)GetElementInnerText(nextConfig), &dummyStrLen, &apdoType, APDO_AddCmd);
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_CHANNEL_PLAN))
		{
			rc = l4db_RestoreChannelPlanFromFile(nextConfig, &(pNwParams->channelPlan));
			
			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_POLLING_INTERVAL))
		{
			apdoType = APDO_Integer;
			size_arg = sizeof(intArg);
			OSAL_sscanf_s((char *)GetElementInnerText(nextConfig), "%d", &intArg);

			rc = l4db_SetIntegerValueNew((int *)&pNwParams->pollingInterval, &size_arg,
				&intArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		else if(FALSE == l4db_CompareString(str,L4DB_XML_TOKEN_POLLING_ATTEMPTS))
		{
			apdoType = APDO_Integer;
			size_arg = sizeof(intArg);
			OSAL_sscanf_s((char *)GetElementInnerText(nextConfig), "%d", &intArg);

			rc = l4db_SetIntegerValueNew((int *)&pNwParams->pollingAttempts, &size_arg,
				&intArg, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
	}
	return rc;
}

///<summary>
/// Restores the operator node from a file
///</summary>
wmx_Status_t l4db_RestoreOperatorsFromFile(pXmlElement pXml)
{
	int						i, j, numOfChildren, arrSize;
	const char				*str;
	pXmlElement				xmlEnumerationData, xmlOperatorData;
	wmx_Status_t			rc = WMX_ST_OK;
	pProvisionedNsp_t		pNsp = NULL;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		//allocate a new NSP
		pNsp = l4db_GetEmptyNsp(pNsp);

		if(NULL == pNsp)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreOperatorsFromFile: cannot add a new NSP");
			return rc;
		}

		//get the operator's unique name
		xmlEnumerationData = GetChildAt(pXml, i);	
		str = GetElementName(xmlEnumerationData);

		//set the operator's unique name
		apdoType = APDO_String;
		rc = l4db_SetStringValueNew(pNsp->tagName, sizeof(pNsp->tagName), (char*)str + strlen(L4DB_TAG_NAME_PREFIX), 
									&dummyStrLen, &apdoType, APDO_AddCmd);

		if(WMX_ST_OK != rc)
		{
			return rc;
		}

		arrSize = GetChildrenCount(xmlEnumerationData);

		for(j = 0 ; j < arrSize ; j++)
		{
			xmlOperatorData = GetChildAt(xmlEnumerationData, j);
			str = GetElementName(xmlOperatorData);

			//network parameters
			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NETWORK_PARM))
			{
				rc = l4db_RestoreNetWorkParmFromFile(xmlOperatorData, &pNsp->nwParams);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}

			//subscription parameters
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SUBSCRIPTION_PARAM))
			{
				rc = l4db_RestoreSubscriptionParmFromFile(xmlOperatorData, &pNsp->subscriptionParams);
				
				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}

			//contacts
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CONTACTS))
			{
				rc = l4db_RestoreContactsFromFile(xmlOperatorData, pNsp);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}
		}
	}
	return rc;
}

///<summary>
/// Restores the Dev Info node from a file
///</summary>
wmx_Status_t l4db_RestoreDevInfoFromFile(pXmlElement pXml)
{
	int						i, numOfChildren;
	const char				*str;
	pXmlElement				xmlData;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	pDevInfo_t				pDevInfo;

	pDevInfo = l4db_GetDevInfo();

	numOfChildren = GetChildrenCount(pXml);

	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);
		str = GetElementName(xmlData);

		//manufacturer
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MAN))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevInfo->manufacturer, sizeof(pDevInfo->manufacturer),
										(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//model
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MOD))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevInfo->model, sizeof(pDevInfo->model),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}	

		// DevId - MZUR TODO this should be read from NVM need to change this
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEV_ID))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevInfo->devID, sizeof(pDevInfo->devID),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}	
	}
	return rc;
}


///<summary>
/// Restores the DevDetail URI node from a file
///</summary>
wmx_Status_t l4db_RestoreDevDetailUriFromFile(pXmlElement pXml, pDevDetailURI_t pDevDetailURI)
{
	int						i, numOfChildren;
	const char				*str;
	pXmlElement				xmlData;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);
		str = GetElementName(xmlData);

		// MaxDepth
		if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_URI_MAX_DEPTH))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetailURI->MaxDepth, sizeof(pDevDetailURI->MaxDepth),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
			
		}
		// MaxTotLen
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_URI_MAX_TOT_LEN))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetailURI->MaxTotLen, sizeof(pDevDetailURI->MaxTotLen),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
		// MaxSegLen
		else  if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_URI_MAX_SEG_LEN))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetailURI->MaxSegLen, sizeof(pDevDetailURI->MaxSegLen),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
	}
	return rc;
}

///<summary>
/// Restores the Dev Detail node from a file
///</summary>
wmx_Status_t l4db_RestoreDevDetailFromFile(pXmlElement pXml)
{
	int						i, numOfChildren;
	const char				*str;
	pXmlElement				xmlData;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	pDevDetail_t			pDevDetail;

	pDevDetail = l4db_GetDevDetail();

	numOfChildren = GetChildrenCount(pXml);

	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);
		str = GetElementName(xmlData);

		//dev typ
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEV_TYP))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetail->devType, sizeof(pDevDetail->devType),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//sw version
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SW_VERSION))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetail->swVersion, sizeof(pDevDetail->swVersion),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//fw version
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FW_VERSION))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetail->fwVersion, sizeof(pDevDetail->fwVersion),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		//hw version
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_HW_VERSION))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetail->hwVersion, sizeof(pDevDetail->hwVersion),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		// URI
		if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_URI))
		{
			rc = l4db_RestoreDevDetailUriFromFile(xmlData, &pDevDetail->uri);
			if(WMX_ST_OK != rc)
			{				
				return rc;
			}
		}
		//lrg obj
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_LRG_OBJ))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pDevDetail->lrgObj, sizeof(pDevDetail->lrgObj),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
	}
	return rc;
}
///<summary>
/// Restores the wimax node from a file
///</summary>
wmx_Status_t l4db_RestoreWmxFromFile(pXmlElement pXml)
{
	int						i, j, k, l, m, size_arg, numOfChildren, arrSize, arrSizePollingSupported, arrSizeUpdateMethods, arrSizeClientInitiated;
	const char				*str, *stringValue;
	pXmlElement				xmlData, xmlInnerData,  xmlDataUpdateMethods, xmlDataClientInitiated, xmlDataPollingSupported;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 
	pWimax_t				pWimax;
	BOOL					boolArg;
	int						intVal;
	pWimax = l4db_GetWimax();

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);
		str = GetElementName(xmlData);

		//DevCap nodes
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEV_CAP))
		{
			// UpdateMethods inner nodes.
			arrSizeUpdateMethods = GetChildrenCount(xmlData);
			for(k = 0 ; k < arrSizeUpdateMethods ; k++)
			{
				xmlDataUpdateMethods = GetChildAt(xmlData, k);
				str = GetElementName(xmlDataUpdateMethods);
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_UPDATE_METHODS))
				{
					arrSizeClientInitiated = GetChildrenCount(xmlDataUpdateMethods);
					for(l = 0 ; l < arrSizeUpdateMethods ; l++)
					{
						xmlDataClientInitiated = GetChildAt(xmlDataUpdateMethods, l);
						str = GetElementName(xmlDataClientInitiated);
						if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CLIENT_INIT))
						{
							arrSizePollingSupported = GetChildrenCount(xmlDataClientInitiated);
							for(m = 0 ; m < arrSizePollingSupported ; m++)
							{
								xmlDataPollingSupported = GetChildAt(xmlDataClientInitiated,m);
								str = GetElementName(xmlDataPollingSupported);
								stringValue = GetElementInnerText(xmlDataPollingSupported);								

								if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_POLLING_SUPPORTED))
								{									
									if (stringValue != NULL)
									{
										if (OSAL_stricmp (stringValue, L4DB_XML_TRUE_STR)==FALSE)
											boolArg = TRUE;
										else
											boolArg = FALSE;
									}
									else	
									{
										boolArg = TRUE;
									}

									apdoType = APDO_Bool;
									size_arg = sizeof(boolArg);

									rc = l4db_SetBoolValueNew( &pWimax->devCap.updateMethods.clientInitiated.pollingSupported, &size_arg, 
										&boolArg, &apdoType, APDO_AddCmd);	
									if(WMX_ST_OK != rc)
									{
										return rc;
									}
								}

								else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_POLLING_INTERVAL))
								{
									OSAL_sscanf_s(stringValue, "%d", &intVal);
									size_arg = sizeof(intVal);
									apdoType = APDO_Integer;

									rc = l4db_SetIntegerValueNew((int *)&pWimax->devCap.updateMethods.clientInitiated.pollingInterval, 
										&size_arg, &intVal, &apdoType, APDO_AddCmd);	
									if(WMX_ST_OK != rc)
									{
										return rc;
									}
								}

								else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_POLLING_ATTEMPTS))
								{
									OSAL_sscanf_s(stringValue, "%d", &intVal);
									size_arg = sizeof(intVal);
									apdoType = APDO_Integer;

									rc = l4db_SetIntegerValueNew((int *)&pWimax->devCap.updateMethods.clientInitiated.pollingAttempts, 
										&size_arg, &intVal, &apdoType, APDO_AddCmd);	
									if(WMX_ST_OK != rc)
									{
										return rc;
									}
								}
							}			
						}
					}
				}
			}
		}

		//terminal equipment
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TERM_EQUIP))
		{
			arrSize = GetChildrenCount(xmlData);

			for(j = 0 ; j < arrSize ; j++)
			{
				xmlInnerData = GetChildAt(xmlData, j);
				str = GetElementName(xmlInnerData);

				//dev id
				if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TERMINAL_DEV_ID))
				{
					apdoType = APDO_String;

					rc = l4db_SetStringValueNew(pWimax->terminalEquipment.devId, 
												sizeof(pWimax->terminalEquipment.devId),
												(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
												&apdoType, APDO_AddCmd);

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
				//Man
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MAN))
				{
					apdoType = APDO_String;

					rc = l4db_SetStringValueNew(pWimax->terminalEquipment.productVersions.manufacturer,
						sizeof(pWimax->terminalEquipment.productVersions.manufacturer),
						(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
						&apdoType, APDO_AddCmd);

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
				// Mod
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MOD))
				{
					apdoType = APDO_String;

					rc = l4db_SetStringValueNew(pWimax->terminalEquipment.productVersions.model,
						sizeof(pWimax->terminalEquipment.productVersions.model),
						(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
						&apdoType, APDO_AddCmd);

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
				// SwV
				else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SW_VERSION))
				{
					apdoType = APDO_String;

					rc = l4db_SetStringValueNew(pWimax->terminalEquipment.productVersions.swVersion,
						sizeof(pWimax->terminalEquipment.productVersions.swVersion),
						(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
						&apdoType, APDO_AddCmd);

					if(WMX_ST_OK != rc)
					{
						return rc;
					}
				}
			}
		}

		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_WMX_RADIO_MODULE))		
		{
			xmlData = GetChildAt(xmlData, 0);
			str = GetElementName(xmlData);

			if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_WIMAX))		
			{				
				arrSize = GetChildrenCount(xmlData);

				for(j = 0 ; j < arrSize ; j++)
				{					
					xmlInnerData = GetChildAt(xmlData, j);
					str = GetElementName(xmlInnerData);

					// Man
					if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MAN))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pWimax->radioModules[0].productVersions.manufacturer, 
							sizeof(pWimax->radioModules[0].productVersions.manufacturer),
							(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
							&apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
					else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MOD))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pWimax->radioModules[0].productVersions.model, 
							sizeof(pWimax->radioModules[0].productVersions.model),
							(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
							&apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}

					}
					else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FW_VERSION))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pWimax->radioModules[0].productVersions.fwVersion, 
							sizeof(pWimax->radioModules[0].productVersions.fwVersion),
							(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
							&apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}

					}
					else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_HW_VERSION))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pWimax->radioModules[0].productVersions.hwVersion, 
							sizeof(pWimax->radioModules[0].productVersions.hwVersion),
							(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
							&apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}

					}
					else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SW_VERSION))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pWimax->radioModules[0].productVersions.swVersion, 
							sizeof(pWimax->radioModules[0].productVersions.swVersion),
							(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
							&apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}

					}
					else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_MAC_ADDRESS))
					{
						apdoType = APDO_String;

						rc = l4db_SetStringValueNew(pWimax->radioModules[0].macAddress, 
							MAX_DEV_ID_SIZE,//sizeof(pWimax->radioModules[0].macAddress),
							(char *)GetElementInnerText(xmlInnerData), &dummyStrLen,
							&apdoType, APDO_AddCmd);

						if(WMX_ST_OK != rc)
						{
							return rc;
						}
					}
				}
			}
		}
	}
	return rc;
}

///<summary>
/// Restores the wimax supp node from a file
///</summary>
wmx_Status_t l4db_RestoreWmxSuppFromFile(pXmlElement pXml)
{
	int						i, numOfChildren;
	const char				*str;
	pXmlElement				xmlData;
	wmx_Status_t			rc = WMX_ST_OK;

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);
		str = GetElementName(xmlData);

		//terminal equipment
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_OPERATOR))
		{
			rc = l4db_RestoreOperatorsFromFile(xmlData);
		}
	}
	return rc;
}

wmx_Status_t l4db_RestoreAPDOIntenalParamsFromFile(pXmlElement pXml, pAPDOInternalParams_t pAPDOInternalParams)
{
	int						i, numOfChildren;
	const char				*str;
	pXmlElement				xmlData;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512;

	UINT8 tempBEK[BEK_LENGTH];
	char* readBek;

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);
		str = GetElementName(xmlData);

		// Fumo Internal params
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FUMO_INTERNAL))
		{
			rc = l4db_RestoreFumoIntenalFromFile(xmlData, &pAPDOInternalParams->fumoInternal);
		}
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_APDO_OPERAOTR_CONFIGURATIONS))
		{
			int stam;
			rc = l4db_RestoreApdoOperatorConfigurationsFromFile(xmlData, pAPDOInternalParams->configurations);
			
			for (stam = 0; stam<MAX_NUM_OF_CONFIGURATIONS;stam++)
			{
				TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG, "wmx_GetApdoOperatorConfigurations return nspTagName=[%s],preProvBStrap=[%d],pollingInterval=[%d],blockUDP=[%d],pollingAttempts=[%d],disableOTAP=[%d]", 
					pAPDOInternalParams->configurations[stam].nspTagName, 
					pAPDOInternalParams->configurations[stam].preProvBStrap, 
					pAPDOInternalParams->configurations[stam].pollingInterval, 
					pAPDOInternalParams->configurations[stam].blockUDP, 
					pAPDOInternalParams->configurations[stam].pollingAttempts, 
					pAPDOInternalParams->configurations[stam].disableOTAP);
			}			
		}
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEFAULT_REALM))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pAPDOInternalParams->defaultRealm, sizeof(pAPDOInternalParams->defaultRealm),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DEFAULT_BEK))
		{
			size_t len;
			apdoType = APDO_String;

			readBek = (char *)GetElementInnerText(xmlData);

			NDnSAgent_HexDecode(readBek, tempBEK, (UINT32)strlen(readBek));
			len = strlen((const char*)tempBEK);

			rc = l4db_SetStringValueNew(pAPDOInternalParams->bek, sizeof(pAPDOInternalParams->bek),
				(char *)tempBEK, &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_NSPS_TO_DMACC))
		{
			rc = l4db_RestoreNSPsToDMAccFromFile(xmlData, pAPDOInternalParams->nspsToDmAcc);
		}
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_BOOTSTRAP_INFO))
		{
			rc = l4db_RestoreBootstrapInfoFromFile(xmlData, pAPDOInternalParams->bootstrapInfo);
		}
		else if (FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_APDO_OPERAOTR_CONFIGURATIONS))
		{
			rc = l4db_RestoreApdoOperatorConfigurationsFromFile(xmlData, pAPDOInternalParams->configurations);
		}
	}

	return rc;
}

wmx_Status_t l4db_RestoreFumoIntenalFromFile(pXmlElement pXml, pFumoInternalParams_t pFumoInternalParams)
{
	int						i, numOfChildren;
	const char				*str, *strValue;
	int						intArg, sizeArg;
	pXmlElement				xmlData;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		xmlData = GetChildAt(pXml, i);	
		str = GetElementName(xmlData);

		// PkgPath 
		if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PKG_PATH))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pFumoInternalParams->pkgPath, sizeof(pFumoInternalParams->pkgPath),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		// PkgFileName
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PKG_FILE_NAME))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pFumoInternalParams->pkgFileName, sizeof(pFumoInternalParams->pkgFileName),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}

		// FUMO node path
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FUMO_NODE_PATH))
		{
			apdoType = APDO_String;

			rc = l4db_SetStringValueNew(pFumoInternalParams->fumoNodePath, sizeof(pFumoInternalParams->fumoNodePath),
				(char *)GetElementInnerText(xmlData), &dummyStrLen, &apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}	

		// FUMO operation
		else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_FUMO_OPERATION))
		{
			apdoType = APDO_Integer;

			strValue = GetElementInnerText(xmlData);
			intArg = atoi(strValue);
			sizeArg = sizeof(intArg);

			rc = l4db_SetIntegerValueNew((int*)&pFumoInternalParams->fumoOperation, &sizeArg, &intArg,
				&apdoType, APDO_AddCmd);

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}	
	}
	return rc;
}

///<summary>
/// Restores the NSPsToDMAcc nodes from file
///</summary>
wmx_Status_t l4db_RestoreNSPsToDMAccFromFile(pXmlElement pXml, pNSPToDMAcc_t pNSPsToDMAcc)
{
	int						i, k, numOfChildren;
	const char				*str, *strValue;
//	int						intArg, sizeArg;
	int						entrySize;
	pXmlElement				xmlData;
	pXmlElement				xmlNSPToDMData;
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	pNSPToDMAcc_t			pAllocNSPToDMAcc;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i=0; i<numOfChildren; ++i)
	{
		xmlData = GetChildAt(pXml, i);	
		str = GetElementName(xmlData);

		apdoType = APDO_String;

		pAllocNSPToDMAcc = l4db_AllocNSPToDMAcc(pNSPsToDMAcc, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

		if(NULL == pAllocNSPToDMAcc)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreNSPsToDMAccFromFile: too many NSPToDMAcc entries in the xml file");
			return WMX_ST_FAIL;
		}

		entrySize = GetChildrenCount(xmlData);

		for(k=0; k<entrySize; k++)
		{
			xmlNSPToDMData = GetChildAt(xmlData, k);
			str = GetElementName(xmlNSPToDMData);
			strValue = GetElementInnerText(xmlNSPToDMData);

			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_TO_DM_ACCOUNT))
			{
				rc = l4db_SetStringValueNew(pAllocNSPToDMAcc->toDMAcc, 
					sizeof(pAllocNSPToDMAcc->toDMAcc), (char*)strValue, &dummyStrLen, 
					&apdoType, APDO_AddCmd);
			}

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
	}

	return rc;
}

wmx_Status_t l4db_RestoreBootstrapInfoFromFile(pXmlElement pXml, pBootstrapInfo_t pBootstrapInfo)
{	
	int						i, k, numOfChildren;
	const char				*str, *strValue;
	int						entrySize;
	pXmlElement				xmlData;	
	pXmlElement				xmlBootstrapInfoData;	
	wmx_Status_t			rc = WMX_ST_OK;
	wmx_APDOType_t			apdoType;
	pBootstrapInfo_t		pAllocBootstrapInfo;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i=0; i<numOfChildren; ++i)
	{
		xmlData = GetChildAt(pXml, i);	
		str = GetElementName(xmlData);

		apdoType = APDO_String;

		pAllocBootstrapInfo = l4db_AllocBootstrapInfo(pBootstrapInfo, (char*)str + strlen(L4DB_TAG_NAME_PREFIX));

		if(NULL == pAllocBootstrapInfo)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreBootstrapInfoFromFile: too many BootstrapInfo entries in the xml file");
			return WMX_ST_FAIL;
		}

		entrySize = GetChildrenCount(xmlData);

		for(k=0; k<entrySize; k++)
		{
			xmlBootstrapInfoData = GetChildAt(xmlData, k);
			str = GetElementName(xmlBootstrapInfoData);
			strValue = GetElementInnerText(xmlBootstrapInfoData);

			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SERVER_ID))
			{
				rc = l4db_SetStringValueNew(pAllocBootstrapInfo->serverID, 
					sizeof(pAllocBootstrapInfo->serverID), (char*)strValue, &dummyStrLen, 
					&apdoType, APDO_AddCmd);
			}
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SERVER_USER_NAME))
			{
				rc = l4db_SetStringValueNew(pAllocBootstrapInfo->serverUserName, 
					sizeof(pAllocBootstrapInfo->serverUserName), (char*)strValue, &dummyStrLen, 
					&apdoType, APDO_AddCmd);
			}
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_CLIENT_USER_NAME))
			{
				rc = l4db_SetStringValueNew(pAllocBootstrapInfo->clientUserName, 
					sizeof(pAllocBootstrapInfo->clientUserName), (char*)strValue, &dummyStrLen, 
					&apdoType, APDO_AddCmd);
			}
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_SERVER_URL))
			{
				rc = l4db_SetStringValueNew(pAllocBootstrapInfo->serverURL, 
					sizeof(pAllocBootstrapInfo->serverURL), (char*)strValue, &dummyStrLen, 
					&apdoType, APDO_AddCmd);
			}
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PORT_NUMBER))
			{
				rc = l4db_SetStringValueNew(pAllocBootstrapInfo->portNbr, 
					sizeof(pAllocBootstrapInfo->portNbr), (char*)strValue, &dummyStrLen, 
					&apdoType, APDO_AddCmd);
			}

			if(WMX_ST_OK != rc)
			{
				return rc;
			}
		}
	}

	return rc;
}

///<summary>
/// Restores the Fumo node from a file
///</summary>
wmx_Status_t l4db_RestoreFumoFromFile(pXmlElement pXml)
{
	int						i, j, numOfChildren, arrSize;
	const char				*str;
	pXmlElement				xmlEnumerationData;
	pXmlElement				xmlFumoData;
//	pXmlElement				xmlChildData;
	wmx_Status_t			rc = WMX_ST_OK;
	pFumoParams_t			pFumoNode = NULL;	
	wmx_APDOType_t			apdoType;
	int						dummyStrLen = 512; // We use this argument for the safe copy at ndsDB_SetStringValueNew. 

	numOfChildren = GetChildrenCount(pXml);

	//iterate through all of the operators
	for(i = 0 ; i < numOfChildren ; ++i)
	{
		//allocate a new Fumo node
		pFumoNode = l4db_GetEmptyFumoNode(pFumoNode);

		if(NULL == pFumoNode)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "l4db_RestoreFumoFromFile: cannot add a new Fumo node");
			return rc;
		}

		//get the Fumo node's name
		xmlEnumerationData = GetChildAt(pXml, i);	
		str = GetElementName(xmlEnumerationData);

		//set the operator's unique name
		apdoType = APDO_String;
		rc = l4db_SetStringValueNew(pFumoNode->tagName, sizeof(pFumoNode->tagName), (char*)str, &dummyStrLen, &apdoType, APDO_AddCmd);

		arrSize = GetChildrenCount(xmlEnumerationData);

		for(j = 0 ; j < arrSize ; j++)
		{
			xmlFumoData = GetChildAt(xmlEnumerationData, j);
			str = GetElementName(xmlFumoData);

			// PkgName
			if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PKG_NAME))
			{
				apdoType = APDO_String;

				rc = l4db_SetStringValueNew(pFumoNode->pkgName, sizeof(pFumoNode->pkgName),
					(char *)GetElementInnerText(xmlFumoData), &dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}

			// PkgVersion
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_PKG_VERSION))
			{
				apdoType = APDO_String;

				rc = l4db_SetStringValueNew(pFumoNode->pkgVersion, sizeof(pFumoNode->pkgVersion),
					(char *)GetElementInnerText(xmlFumoData), &dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}

			// Download and update 
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DOWNLOAD_AND_UPDATE))
			{
		/*		apdoType = APDO_String;

				xmlChildData = GetChildAt(xmlFumoData, 0);
				str = GetElementName(xmlChildData);
			
				rc = l4db_SetStringValueNew(pFumoNode->downloadAndUpdatePkgURL,
					sizeof(pFumoNode->downloadAndUpdatePkgURL), (char*)GetElementInnerText(xmlChildData), 
					&dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}*/
			}		

			// Download  
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_DOWNLOAD))
			{
				/*apdoType = APDO_String;

				xmlChildData = GetChildAt(xmlFumoData, 0);
				str = GetElementName(xmlChildData);

				rc = l4db_SetStringValueNew(pFumoNode->downloadPkgURL,
					sizeof(pFumoNode->downloadPkgURL), (char *)GetElementInnerText(xmlChildData), 
					&dummyStrLen, &apdoType, APDO_AddCmd);

				if(WMX_ST_OK != rc)
				{
					return rc;
				}*/
			}	

			// State
			else if(FALSE == l4db_CompareString(str, L4DB_XML_TOKEN_STATE))
			{
				apdoType = APDO_Integer;
				
				rc = ConvertToDownloadState(GetElementInnerText(xmlFumoData), &(pFumoNode->state));
				
				if(WMX_ST_OK != rc)
				{
					return rc;
				}
			}

		}
	}
	return rc;
}