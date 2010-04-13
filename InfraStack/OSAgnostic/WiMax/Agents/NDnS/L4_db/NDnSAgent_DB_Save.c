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
#include "wimax_osal_string.h"

#include "NDnSAgent_DB_Internal.h"
#include "NDnSAgent_Utils.h"
#include "wmxSDK_Apdo_Cmn.h"		// @@@ : JSS : Corrected case name of the file

// Declarations
void l4db_AddProfilesInfoToXml(pXmlElement parentXmlData, UINT32 numOfProfiles, pProfile_t pProfiles);

//This file includes methods for saving data to an xml file


void l4db_AddTagNamePrefix(char * tagName, char * tagNameWithPrefix, int buffSize)
{
	OSAL_strcpy_s(tagNameWithPrefix, buffSize, L4DB_TAG_NAME_PREFIX);
	OSAL_strcat_s(tagNameWithPrefix, buffSize, tagName);
}

/// <summary>
/// Add the internal states node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="settings">(IN) the internal states data structure </param>
void l4db_AddInternalStatesToXml(pXmlElement parentXmlData, pNdsSettings_t pSettings)
{
	char buff[BUFF_SIZE];
	
	pXmlElement internalSettingsNode;
	pXmlElement ThCriteraNode;	
	pXmlElement	lastConnectedNode, lastConnectedNapsNode;
	pXmlElement nextData;
	UINT32		numOfLastConnectedNaps, j;

	internalSettingsNode = CreateXmlData(L4DB_XML_TOKEN_INTERNAL_STATES, "");

	AddChild(parentXmlData, internalSettingsNode);

	//Last RF state
	nextData = CreateXmlData(L4DB_XML_TOKEN_NDS_LAST_RF_STATE, l4db_GetRfStateStr(pSettings->swRfState));
	AddChild(internalSettingsNode, nextData);

	//setPreferredNspOnConnect state
	l4db_GetBoolStr(pSettings->setPreferredNspOnConnect, buff);
	nextData = CreateXmlData(L4DB_XML_TOKEN_NDS_SET_PREFERRED_NSP_ON_CONNECT, buff);
	AddChild(internalSettingsNode, nextData);

	//User connection mode
	ConvertConnectModeToStr(pSettings->connectMode, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_USER_CONNECTING_MODE, buff);
	AddChild(internalSettingsNode, nextData);

	//Current preferred NSP
	if((wmx_NSPid_t)L4DB_INVALID_INDEX != pSettings->currentPreferredNSP)
	{		
		OSAL_itoa_s(pSettings->currentPreferredNSP, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_CURRENT_PREFERRED_NSP, buff);
		AddChild(internalSettingsNode, nextData);
	}

	// Last connected NSP
	lastConnectedNode = CreateXmlData(L4DB_XML_TOKEN_LAST_CONNETED_NSPS, "");  // Supports only one NSP for now
	AddChild(internalSettingsNode, lastConnectedNode);

	if((wmx_NSPid_t)L4DB_INVALID_INDEX != pSettings->lastConnectedNSP.recentNspID)
	{				
		// Add last connected NSP ID
		OSAL_itoa_s(pSettings->lastConnectedNSP.recentNspID, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_LAST_CONNETED_NSP_ID, buff);
		AddChild(lastConnectedNode, nextData);

		// Add the related NAPs
		lastConnectedNapsNode = CreateXmlData(L4DB_XML_TOKEN_LAST_CONNETED_NAP_IDS, "");
		AddChild(lastConnectedNode, lastConnectedNapsNode);
		
		numOfLastConnectedNaps = pSettings->lastConnectedNSP.numOfConnectedNapIDs;
	
		for (j=0; j < numOfLastConnectedNaps; j++)
		{
			l4db_ConvertNapIdToStr(pSettings->lastConnectedNSP.lastConnectedNapIDs[j], buff);			
			nextData = CreateXmlData(L4DB_XML_TOKEN_NAP_ID_DASH, buff);
			AddChild(lastConnectedNapsNode, nextData);
		}		
	}

	//unprovisioned profiles
	l4db_AddProfilesInfoToXml(internalSettingsNode, pSettings->unprovisionedProfilesSize, (pProfile_t)&pSettings->unprovisionedProfiles);
		
	//Allow auto activate
	l4db_GetBoolStr(pSettings->allowAutoActivate, buff);
	nextData = CreateXmlData(L4DB_XML_TOKEN_ALLOW_AUTO_ACTIVATE, buff);
	AddChild(internalSettingsNode, nextData);

	//Allow fast reconnect
	l4db_GetBoolStr(pSettings->allowFastReconnect, buff);
	nextData = CreateXmlData(L4DB_XML_TOKEN_ALLOW_FAST_RECONNECT, buff);
	AddChild(internalSettingsNode, nextData);

	//TH Criteria
	ThCriteraNode = CreateXmlData(L4DB_XML_TOKEN_NDS_THCRITERIA, "");
	AddChild(internalSettingsNode, ThCriteraNode);

	OSAL_itoa_s(pSettings->thCriteria.rssiTH, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_NDS_RSSI_THRESHOLD, buff);
	AddChild(ThCriteraNode, nextData);

	OSAL_itoa_s(pSettings->thCriteria.cinrTH, buff, BUFF_SIZE, 10);

	nextData = CreateXmlData(L4DB_XML_TOKEN_NDS_CINR_THRESHOLD, buff);
	AddChild(ThCriteraNode, nextData);

	//add the roaming mode
	ConvertRoamingModeToStr(pSettings->roamingMode, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_ROAMING_MODE, buff);
	AddChild(internalSettingsNode, nextData);
} 

/// <summary>
/// Add the device certificates node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="deviceCertificates">(IN) the device certificate data structure </param>
void l4db_AddDeviceCertificatesToXml(pXmlElement parentXmlData, DeviceCertificates_t deviceCertificates)
{
	pXmlElement deviceCertificatesNode;
	pXmlElement nextData;

	deviceCertificatesNode = CreateXmlData(L4DB_XML_TOKEN_DEVICE_CERTIFICATES, "");
	AddChild(parentXmlData, deviceCertificatesNode);

	//root cert
	nextData = CreateXmlData(L4DB_XML_TOKEN_ROOT_CERT, deviceCertificates.rootCert);
	AddChild(deviceCertificatesNode, nextData);

	//client cert
	nextData = CreateXmlData(L4DB_XML_TOKEN_CLIENT_CERT, deviceCertificates.clientCert);
	AddChild(deviceCertificatesNode, nextData);

	//private key
	nextData = CreateXmlData(L4DB_XML_TOKEN_PRIVATE_KEY, deviceCertificates.privateKey);
	AddChild(deviceCertificatesNode, nextData);
}

/// <summary>
/// Add the link loss parameters node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="shortLinkLossParams">(IN) the short link loss data structure </param>
/// <param name="longLinkLossParams">(IN) the long link loss data structure </param>
void l4db_AddLinkLossParamsToXml(pXmlElement parentXmlData, 
										 LinkLossParameters_t shortLinkLossParams,
										 LinkLossParameters_t longLinkLossParams)
{
	char		buff[BUFF_SIZE];
	pXmlElement linkLossParamsNode;
	pXmlElement shortLinkLossNode;
	pXmlElement longLinkLossNode;
	pXmlElement nextData;

	linkLossParamsNode = CreateXmlData(L4DB_XML_TOKEN_LINK_LOSS_PARAMS, "");
	AddChild(parentXmlData, linkLossParamsNode);

	//short link loss
	shortLinkLossNode = CreateXmlData(L4DB_XML_TOKEN_SHORT_LINK_LOSS, "");
	AddChild(linkLossParamsNode, shortLinkLossNode);

	//short link loss timer
	OSAL_itoa_s(shortLinkLossParams.time, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_TIMER, buff);
	AddChild(shortLinkLossNode, nextData);

	//short link loss repetition
	OSAL_itoa_s(shortLinkLossParams.repetition, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_REPETITION, buff);
	AddChild(shortLinkLossNode, nextData);

	//long link loss
	longLinkLossNode = CreateXmlData(L4DB_XML_TOKEN_LONG_LINK_LOSS, "");
	AddChild(linkLossParamsNode, longLinkLossNode);

	//long link loss timer
	OSAL_itoa_s(longLinkLossParams.time, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_TIMER, buff);
	AddChild(longLinkLossNode, nextData);

	//long link loss repetition
	OSAL_itoa_s(longLinkLossParams.repetition, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_REPETITION, buff);
	AddChild(longLinkLossNode, nextData);
}


/// <summary>
/// Add a channel plan node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pChannelPlan">(IN) the channel plan data structure </param>
void l4db_AddChannelPlanToXml(pXmlElement parentXmlData, pChannelPlan_t pChannelPlan)
{
	char		buff[BUFF_SIZE];
	char		channelTagName[MAX_INT_TAG_NAME_SIZE];
	int			i;
	pXmlElement channelPlanNode;
	pXmlElement tagNameNode;
	pXmlElement entriesNode;
	pXmlElement nextData;
	//size_t		tempStrLen = 0;

	//channel plan node
	channelPlanNode = CreateXmlData(L4DB_XML_TOKEN_CHANNEL_PLAN, "");
	AddChild(parentXmlData, channelPlanNode);

	//entries node
	entriesNode = CreateXmlData(L4DB_XML_TOKEN_ENTRIES, "");
	AddChild(channelPlanNode, entriesNode);

	//iterate through all the entries
	for(i = 0 ; i < (int)pChannelPlan->channelsSize ; i++)
	{	
		memset(channelTagName,'\0',MAX_INT_TAG_NAME_SIZE);
		OSAL_itoa_s(i, channelTagName, MAX_INT_TAG_NAME_SIZE, 10);
		l4db_AddTagNamePrefix(channelTagName, buff, BUFF_SIZE);

		/*
		tempStrLen = OSAL_strnlen(pChannelPlan->channels[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			l4db_AddTagNamePrefix(pChannelPlan->channels[i].tagName, buff, BUFF_SIZE);
		}
		else
		{
			l4db_AddTagNamePrefix(MAX_TAG_NAME_DEFAULT, buff, BUFF_SIZE);
		}*/

		tagNameNode = CreateXmlData(buff, ""); //create a node for the entry's unique name
		AddChild(entriesNode, tagNameNode);

		//channel id
		OSAL_strncpy_s(buff, BUFF_SIZE - 1 , pChannelPlan->channels[i].id, OSAL_strnlen(pChannelPlan->channels[i].id, MAX_REF_ID_NAME_SIZE));
		nextData = CreateXmlData(L4DB_XML_TOKEN_ID, buff);
		AddChild(tagNameNode, nextData);

		//first frequency
		OSAL_itoa_s(pChannelPlan->channels[i].firstFreq, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_FIRST_FREQ, buff);
		AddChild(tagNameNode, nextData);

		//last frequency
		OSAL_itoa_s(pChannelPlan->channels[i].lastFreq, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_LAST_FREQ, buff);
		AddChild(tagNameNode, nextData);

		//next frequency step
		OSAL_itoa_s(pChannelPlan->channels[i].nextFreq, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_NEXT_FREQ_STEP, buff);
		AddChild(tagNameNode, nextData);

		//preambles
		ConvertPreamblesBitmapToStr(pChannelPlan->channels[i].preambleBitmap, buff);
		nextData = CreateXmlData(L4DB_XML_TOKEN_PREAMBLES, buff);
		AddChild(tagNameNode,nextData);

		//bandwidth
		ConvertBandWidthToStr(pChannelPlan->channels[i].bw, buff, BUFF_SIZE);
		nextData = CreateXmlData(L4DB_XML_TOKEN_BW, buff);
		AddChild(tagNameNode, nextData);

		//FFT size
		ConvertFFTtoStr(pChannelPlan->channels[i].fft, buff, BUFF_SIZE);
		nextData = CreateXmlData(L4DB_XML_TOKEN_FFT_SIZE, buff);
		AddChild(tagNameNode, nextData);

		//Duplex mode
		OSAL_itoa_s(pChannelPlan->channels[i].duplexMode, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_DUPLEX_MODE, buff);
		AddChild(tagNameNode, nextData);

		//add the time to live (ttl) node
		OSAL_itoa_s(pChannelPlan->channels[i].ttl, buff, BUFF_SIZE, 10);
		nextData = CreateXmlData(L4DB_XML_TOKEN_TTL, buff);
		AddChild(tagNameNode, nextData);
	}

	//bandwidth
	ConvertBandWidthToStr(pChannelPlan->bw, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_BW, buff);
	AddChild(channelPlanNode, nextData);

	//FFT size
	ConvertFFTtoStr(pChannelPlan->fft, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_FFT_SIZE, buff);
	AddChild(channelPlanNode, nextData);

	//Duplex mode
	OSAL_itoa_s(pChannelPlan->duplexMode, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_DUPLEX_MODE, buff);
	AddChild(channelPlanNode, nextData);
}



/// <summary>
/// Add a channel refs node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="channelPlan">(IN) the channel plan data structure </param>
void l4db_AddChannelsRefsToXml(pXmlElement parentXmlData, pChPlanRefId_t pChannelsRefs)
{
	char		buff[BUFF_SIZE];
	int			i;
	pXmlElement channelRefsNode;
	pXmlElement tagNameNode;
	pXmlElement nextData;
	size_t tempStrLen = 0;

	//channel ref ids node
	channelRefsNode = CreateXmlData(L4DB_XML_TOKEN_CH_PLAN_REF_IDS, "");
	AddChild(parentXmlData, channelRefsNode);

	//iterate through all the entries
	for(i = 0 ; i < WMX_CHANNELS_MAX_NUM ; i++)
	{
		tempStrLen = OSAL_strnlen(pChannelsRefs[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			l4db_AddTagNamePrefix(pChannelsRefs[i].tagName, buff, BUFF_SIZE);
			tagNameNode = CreateXmlData(buff , ""); //create a node for the entry's unique name
			AddChild(channelRefsNode, tagNameNode);

			//channel id
			OSAL_strncpy_s(buff, BUFF_SIZE - 1, pChannelsRefs[i].id, OSAL_strnlen(pChannelsRefs[i].id, MAX_REF_ID_NAME_SIZE));
			nextData = CreateXmlData(L4DB_XML_TOKEN_REF_ID, buff);
			AddChild(tagNameNode, nextData);
		}
	}
}



/// <summary>
/// Add a wide scan parameters node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pWideScanParams">(IN) the channel plan data structure </param>
void l4db_AddWideScanParamsToXml(pXmlElement parentXmlData, pChannelPlan_t pWideScanParams)
{
	pXmlElement wideScanParamsNode;

	//create a wide scan parameters node
	wideScanParamsNode = CreateXmlData(L4DB_XML_TOKEN_WIDE_SCAN_PARAMS, "");
	AddChild(parentXmlData, wideScanParamsNode);

	//add a channel plan node under the wide scan parameters node
	l4db_AddChannelPlanToXml(wideScanParamsNode, pWideScanParams);
}

/// <summary>
/// Add a db version node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="l4dbversion">(IN) the db version</param>
void l4db_AddDbVersionToXml(pXmlElement parentXmlData, int l4dbversion)
{
	pXmlElement versionNode;
	char buff[BUFF_SIZE];

	OSAL_itoa_s(l4dbversion, buff, BUFF_SIZE, 10);
	versionNode = CreateXmlData(L4DB_XML_TOKEN_DB_VERSION, buff);
	AddChild(parentXmlData, versionNode);
}

/// <summary>
/// Add a nai counter node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="naiCounter">(IN) the db version</param>
void l4db_AddNaiCounterToXml(pXmlElement parentXmlData, UINT32 naiCounter)
{
	pXmlElement versionNode;
	char buff[BUFF_SIZE];

	OSAL_itoa_s(naiCounter, buff, BUFF_SIZE, 10);
	versionNode = CreateXmlData(L4DB_XML_TOKEN_NAI_COUNTER, buff);
	AddChild(parentXmlData, versionNode);
}

/// <summary>
/// Add a preferred scan policy node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="policy">(IN) the preferred scan policy</param>
void l4db_AddPsPolicyToXml(pXmlElement parentXmlData, PreferredScanPolicy_t policy)
{
	pXmlElement versionNode;
	char buff[BUFF_SIZE];

	ConvertPsPolicyToStr(policy, buff, BUFF_SIZE);
	versionNode = CreateXmlData(L4DB_XML_TOKEN_PS_POLICY, buff);
	AddChild(parentXmlData, versionNode);
}

/// <summary>
/// Add an HNSP node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pHnsps">(IN) all H_NSPS</param>
void l4db_AddHnspsToXml(pXmlElement parentXmlData, pHomeNsp_t pHnsps)
{
	pXmlElement	hNspsNode;
	pXmlElement	uniqueNameNode;
	pXmlElement	nextData;
	char		buff[BUFF_SIZE];
	int			i;
	size_t		tempStrLen = 0;

	//create the H_NSP node
	hNspsNode = CreateXmlData(L4DB_XML_TOKEN_H_NSP, "");
	AddChild(parentXmlData, hNspsNode);

	//iterate through all the entries
	for(i = 0 ; i < WMX_NSP_IDS_MAX_NUM ; i++)
	{
		//check if the node has been allocated
		tempStrLen = OSAL_strnlen(pHnsps[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//add the unique name node
			l4db_AddTagNamePrefix(pHnsps[i].tagName, buff, BUFF_SIZE);
			uniqueNameNode = CreateXmlData(buff ,"");
			AddChild(hNspsNode, uniqueNameNode);
			
			//add the H_NSP_D
			OSAL_itoa_s(pHnsps[i].nspId, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_H_NSP_ID, buff);
			AddChild(uniqueNameNode, nextData);
		}
	}
}


/// <summary>
/// Add a CAPL node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pCapl">(IN) the Capl data structure</param>
void l4db_AddCaplToXml(pXmlElement parentXmlData, pCapl_t pCapl)
{
	pXmlElement caplNode;
	pXmlElement entryNode;
	pXmlElement	uniqueNameNode;
	pXmlElement nextData;
	char		buff[BUFF_SIZE];
	int			i;
	size_t		tempStrLen = 0;

	//create the CAPL node;
	caplNode = CreateXmlData(L4DB_XML_TOKEN_CAPL, "");
	AddChild(parentXmlData, caplNode);

	//add the entry node
	entryNode = CreateXmlData(L4DB_XML_TOKEN_ENTRIES, "");
	AddChild(caplNode, entryNode);

	//add all capl entries
	for(i = 0 ; i < WMX_NAPS_MAX_NUM ; i++)
	{
		//check that the entry has been allocated
		tempStrLen = OSAL_strnlen(pCapl->naps[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//create a node with the unique name
			l4db_AddTagNamePrefix(pCapl->naps[i].tagName, buff, BUFF_SIZE);
			uniqueNameNode = CreateXmlData(buff, "");
			AddChild(entryNode, uniqueNameNode);

			//add the NAP ID
			l4db_ConvertNapIdToStr(pCapl->naps[i].napID, buff);
			nextData = CreateXmlData(L4DB_XML_TOKEN_NAP_ID, buff);
			AddChild(uniqueNameNode, nextData);

			//add the priority
			OSAL_itoa_s(pCapl->naps[i].priority, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_PRIORITY, buff);
			AddChild(uniqueNameNode, nextData);

			//add the channel refs
			l4db_AddChannelsRefsToXml(uniqueNameNode, pCapl->naps[i].channelPlanRefIds);
		}
	}

	//add the any node
	ConvertToAnyStr(pCapl->any, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_ANY, buff);
	AddChild(caplNode, nextData);

	//add the selectPolicy node
	ConvertToSelectPolicyStr(pCapl->selectPolicy, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_SELECT_POLICY, buff);
	AddChild(caplNode, nextData);
}

/// <summary>
/// Add a RAPL node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pRapl">(IN) the Rapl data structure</param>
void l4db_AddRaplToXml(pXmlElement parentXmlData, pRapl_t pRapl)
{
	pXmlElement raplNode;
	pXmlElement entryNode;
	pXmlElement	uniqueNameNode;
	pXmlElement nextData;
	char		buff[BUFF_SIZE];
	int			i;
	size_t		tempStrLen = 0;

	//create the RAPL node;
	raplNode = CreateXmlData(L4DB_XML_TOKEN_RAPL, "");
	AddChild(parentXmlData, raplNode);

	//add the entry node
	entryNode = CreateXmlData(L4DB_XML_TOKEN_ENTRIES, "");
	AddChild(raplNode, entryNode);

	//add all capl entries
	for(i = 0 ; i < MAX_ROAMING_PARTNERS ; i++)
	{
		//check that the entry has been allocated
		tempStrLen = OSAL_strnlen(pRapl->roamingPartners[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//create a node with the unique name
			l4db_AddTagNamePrefix(pRapl->roamingPartners[i].tagName, buff, BUFF_SIZE);
			uniqueNameNode = CreateXmlData(buff, "");
			AddChild(entryNode, uniqueNameNode);

			//add the V_NSP_ID ID
			OSAL_itoa_s(pRapl->roamingPartners[i].vNspID, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_V_NSP_ID, buff);
			AddChild(uniqueNameNode, nextData);

			//add the priority
			OSAL_itoa_s(pRapl->roamingPartners[i].priority, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_PRIORITY, buff);
			AddChild(uniqueNameNode, nextData);
		}
	}

	//add the any node
	ConvertToAnyStr(pRapl->any, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_ANY, buff);
	AddChild(raplNode, nextData);

	//add the selectPolicy node
	ConvertToSelectPolicyStr(pRapl->selectPolicy, buff, BUFF_SIZE);
	nextData = CreateXmlData(L4DB_XML_TOKEN_SELECT_POLICY, buff);
	AddChild(raplNode, nextData);
}

/// <summary>
/// Add a NW params node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="nwParams">(IN) the NW params data structure</param>
void l4db_AddNwParamsToXml(pXmlElement parentXmlData, pNwParams_t pNwParams)
{
	pXmlElement	nwParamsNode;
	pXmlElement	nextData;
	char		buff[BUFF_SIZE];

	//create the NW params node
	nwParamsNode = CreateXmlData(L4DB_XML_TOKEN_NETWORK_PARM, "");
	AddChild(parentXmlData, nwParamsNode);

	//add the H_NSPs
	l4db_AddHnspsToXml(nwParamsNode, pNwParams->hNsps);

	//add the CAPL data
	l4db_AddCaplToXml(nwParamsNode, &pNwParams->capl);

	//add the RAPL data
	l4db_AddRaplToXml(nwParamsNode, &pNwParams->rapl);

	//add the default channel plan
	l4db_AddChannelPlanToXml(nwParamsNode, &pNwParams->channelPlan);

	//add the Operator name
	nextData = CreateXmlData(L4DB_XML_TOKEN_OPERATOR_NAME, pNwParams->provisionedName);
	AddChild(nwParamsNode, nextData);

	//add the polling interval
	OSAL_itoa_s(pNwParams->pollingInterval, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_POLLING_INTERVAL, buff);
	AddChild(nwParamsNode, nextData);

	//add the polling attempts
	OSAL_itoa_s(pNwParams->pollingAttempts, buff, BUFF_SIZE, 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_POLLING_ATTEMPTS, buff);
	AddChild(nwParamsNode, nextData);

	//add the serverID
	nextData = CreateXmlData(L4DB_XML_TOKEN_SERVER_ID, pNwParams->serverID);
	AddChild(nwParamsNode, nextData);
}

/// <summary>
/// Add an EAP node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pEap">(IN) an EAP array data structure</param>
void l4db_AddEapToXml(pXmlElement parentXmlData, pEAP_t pEap)
{
	pXmlElement eapNode;
	pXmlElement	eapUniqueNameNode;
	pXmlElement	srvUniqueNameNode;	
	pXmlElement	certUniqueNameNode;
	pXmlElement	certNode;
	pXmlElement	srvRealmsNode;
	pXmlElement	nextData;
	char		buff[BUFF_SIZE];
	int			i, j;
	size_t		tempStrLen = 0;

	//create the EAP node
	eapNode = CreateXmlData(L4DB_XML_TOKEN_EAP, "");
	AddChild(parentXmlData, eapNode);

	//iterate through all the EAP entries
	for(i = 0 ; i < MAX_NUM_OF_EAP_METHODS ; i++)
	{
		//check that the node has been allocated
		tempStrLen = OSAL_strnlen(pEap[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//add the unique name node
			l4db_AddTagNamePrefix(pEap[i].tagName, buff, BUFF_SIZE);
			eapUniqueNameNode = CreateXmlData(buff, "");
			AddChild(eapNode, eapUniqueNameNode);

			//add EAP type node
			l4db_ConvertToEapTypeStr(pEap[i].EAPMethod, buff);
			nextData = CreateXmlData(L4DB_XML_TOKEN_EAP_TYPE, buff);
			AddChild(eapUniqueNameNode, nextData);

			//add the vendor id
			OSAL_itoa_s(pEap[i].vendorId, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_VENDOR_ID, buff);
			AddChild(eapUniqueNameNode, nextData);

			//add the vendor type
			OSAL_itoa_s(pEap[i].vendorType, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_VENDOR_TYPE, buff);
			AddChild(eapUniqueNameNode, nextData);

			//add user id node
			nextData = CreateXmlData(L4DB_XML_TOKEN_USER_IDENTITY, pEap[i].id);
			AddChild(eapUniqueNameNode, nextData);

			//add pseudo id
			nextData = CreateXmlData(L4DB_XML_TOKEN_PROVISIONED_PSEUDO_ID, pEap[i].provisionedPseudoId);
			AddChild(eapUniqueNameNode, nextData);

			//add password node. TODO - code the password
			nextData = CreateXmlData(L4DB_XML_TOKEN_PASSWORD, pEap[i].Password);
			
			//the password that in the memory is always encrypted
			if('\0' != pEap[i].Password[0])
			{
				OSAL_strcpy_s(buff, BUFF_SIZE, L4DB_XML_TRUE_STR); 
				AddAttribute(nextData, L4DB_XML_TOKEN_IS_ENCRYPTED_PASSWORD, L4DB_XML_TRUE_STR);
			}
			AddChild(eapUniqueNameNode, nextData);

			//add realm node
			nextData = CreateXmlData(L4DB_XML_TOKEN_REALM, pEap[i].realm);
			AddChild(eapUniqueNameNode, nextData);

			//add use pseudo node
			l4db_GetBoolStr(pEap[i].usePrivacy, buff);
			nextData = CreateXmlData(L4DB_XML_TOKEN_USE_PRIVACY, buff);
			AddChild(eapUniqueNameNode, nextData);

			//add encaps node
			OSAL_itoa_s(pEap[i].encaps, buff, BUFF_SIZE, 10);			
			nextData = CreateXmlData(L4DB_XML_TOKEN_ENCAPS, buff);
			AddChild(eapUniqueNameNode, nextData);

			//add VFY srv realm node
			l4db_GetBoolStr(pEap[i].vfySrvRealm, buff);
			nextData = CreateXmlData(L4DB_XML_TOKEN_VFY_SERVER_REALM, buff);
			AddChild(eapUniqueNameNode, nextData);

			//add the srv realms node
			srvRealmsNode = CreateXmlData(L4DB_XML_TOKEN_SERVER_REALMS, "");
			AddChild(eapUniqueNameNode, srvRealmsNode);

			// add nodes under srv realm 
			for(j = 0 ; j < MAX_NUM_OF_SRV_REALMS ; j++)
			{
				//check that this node has been allocated
				tempStrLen = OSAL_strnlen(pEap[i].srvRealms[j].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					//add the unique name node
					l4db_AddTagNamePrefix(pEap[i].srvRealms[j].tagName, buff, BUFF_SIZE);
					srvUniqueNameNode = CreateXmlData(buff, "");
					AddChild(srvRealmsNode, srvUniqueNameNode);

					//add the srv realm node
					nextData = CreateXmlData(L4DB_XML_TOKEN_SERVER_REALM, pEap[i].srvRealms[j].srvRealm);
					AddChild(srvUniqueNameNode, nextData);
				}
			}

			//add the cert node
			certNode = CreateXmlData(L4DB_XML_TOKEN_CERT, "");
			AddChild(eapUniqueNameNode, certNode);

			//add node under the cert node
			for(j = 0 ; j < MAX_NUM_OF_CERTS ; j++)
			{
				//check that the node has been allocated
				tempStrLen = OSAL_strnlen(pEap[i].certs[j].tagName, MAX_TAG_NAME_SIZE);
				if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
				{
					//allocate the unique name tag
					l4db_AddTagNamePrefix(pEap[i].certs[j].tagName, buff, BUFF_SIZE);
					certUniqueNameNode = CreateXmlData(buff, "");
					AddChild(certNode, certUniqueNameNode);

					//add the cert type node
					//ConvertCertTypeToStr(pEap[i].certs[j].certType, buff, BUFF_SIZE);
					nextData = CreateXmlData(L4DB_XML_TOKEN_CERT_TYPE, pEap[i].certs[j].certType);
					AddChild(certUniqueNameNode, nextData);

					//add the serial number node 
					nextData = CreateXmlData(L4DB_XML_TOKEN_SER_NUM, pEap[i].certs[j].serNum);
					AddChild(certUniqueNameNode, nextData);
					
					//add the issuer node 
					nextData = CreateXmlData(L4DB_XML_TOKEN_ISSUER, pEap[i].certs[j].issuer);
					AddChild(certUniqueNameNode, nextData);

					////add the thumb print node
					//_itoa_s(pEap[i].certs[j].thumbPrint, buff, BUFF_SIZE, 10);
					//nextData = CreateXmlData(L4DB_XML_TOKEN_THUMB_PRINT, buff);
					//AddChild(certUniqueNameNode, nextData);
				}
			}
		}
	}
}
/// <summary>
/// Add a subscription params node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="subscParams">(IN) a subscription params data structure</param>
void l4db_AddSubscriptionParamsToXml(pXmlElement parentXmlData, pSubscriptionParams_t pSubscParams)
{
	pXmlElement	subscriptionInfoNode;
	pXmlElement primaryNode;
	pXmlElement	otherSubscriptionNode;
	pXmlElement	otherUniqueNameNode;
	pXmlElement	nextData;
	int			i;
	char		buff[BUFF_SIZE];
	size_t		tempStrLen = 0;

	//add the subscription parameters node
	subscriptionInfoNode = CreateXmlData(L4DB_XML_TOKEN_SUBSCRIPTION_PARAM, "");
	AddChild(parentXmlData, subscriptionInfoNode);

	//add the primary subscription node
	primaryNode = CreateXmlData(L4DB_XML_TOKEN_PRIMARY, "");
	AddChild(subscriptionInfoNode, primaryNode);

	//add nodes under the primary subscription
	//add the name node
	nextData = CreateXmlData(L4DB_XML_TOKEN_NAME, pSubscParams->primary.name);
	AddChild(primaryNode, nextData);

	//add the activated node
	l4db_GetBoolStr(pSubscParams->primary.activated, buff);
	nextData = CreateXmlData(L4DB_XML_TOKEN_ACTIVATED, buff);
	AddChild(primaryNode, nextData);

	//add the EAP node
	l4db_AddEapToXml(primaryNode, pSubscParams->primary.eapInfo);

	//add the other subscription parameters node
	otherSubscriptionNode = CreateXmlData(L4DB_XML_TOKEN_OTHER_SUBSCRIPTIONS, "");
	AddChild(subscriptionInfoNode, otherSubscriptionNode);

	//add entries under the other subscription node
	for(i = 0 ; i < WMX_NSP_SUBSCRIBERS_MAX_NUM ; i++)
	{
		//check that the node has been allocated
		tempStrLen = OSAL_strnlen(pSubscParams->other[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && (MAX_TAG_NAME_SIZE) != tempStrLen)
		{
			//add the unique name node
			l4db_AddTagNamePrefix(pSubscParams->other[i].tagName, buff, BUFF_SIZE);
			otherUniqueNameNode = CreateXmlData(buff, "");
			AddChild(otherSubscriptionNode, otherUniqueNameNode);

			//add the nodes under the specific unique name
			//add EAP node
			l4db_AddEapToXml(otherUniqueNameNode, pSubscParams->other[i].subscriberInfo.eapInfo);

			//add the name node
			nextData = CreateXmlData(L4DB_XML_TOKEN_NAME, pSubscParams->other[i].subscriberInfo.name);
			AddChild(otherUniqueNameNode, nextData);

			//add the activated node
			l4db_GetBoolStr(pSubscParams->other[i].subscriberInfo.activated, buff);
			nextData = CreateXmlData(L4DB_XML_TOKEN_ACTIVATED, buff);
			AddChild(otherUniqueNameNode, nextData);
		}
	}
}

/// <summary>
/// Add a contacts node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="contacts">(IN) a contacts data structure</param>
void l4db_AddContactsToXml(pXmlElement parentXmlData, pContactsInfo_t pContacts)
{
	pXmlElement	contactsNode;
	pXmlElement	nextData;
	pXmlElement uniqueNameNode;
	int i;
	char	buff[BUFF_SIZE];
	size_t	tempStrLen = 0;

	//add the contacts node
	contactsNode = CreateXmlData(L4DB_XML_TOKEN_CONTACTS,"");
	AddChild(parentXmlData, contactsNode);

	//add the entries under the contacts node
	for(i = 0 ; i < MAX_NUM_OF_CONTACTS ; i++)
	{
		//check that the node has been allocated
		tempStrLen = OSAL_strnlen(pContacts[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//add the unique name node
			l4db_AddTagNamePrefix(pContacts[i].tagName, buff, BUFF_SIZE);
			uniqueNameNode = CreateXmlData(buff, "");
			AddChild(contactsNode, uniqueNameNode);

			//add the uri type
			OSAL_itoa_s(pContacts[i].uriType, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_TYPE, buff);
			AddChild(uniqueNameNode, nextData);

			//add the uri
			nextData = CreateXmlData(L4DB_XML_TOKEN_URI, (char*)pContacts[i].uri);
			AddChild(uniqueNameNode, nextData);

			//add the text
			nextData = CreateXmlData(L4DB_XML_TOKEN_TEXT, (char*)pContacts[i].text);
			AddChild(uniqueNameNode, nextData);
		}
	}
}

/// <summary>
/// Add an operator node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNsps">(IN) an array of NSPs data structure</param>
void l4db_AddOperatorToXml(pXmlElement parentXmlData, pProvisionedNsp_t pNsps)
{
	pXmlElement	operatorNode;
	pXmlElement	nspUniqueNameNode;
	int i;
	char		buff[BUFF_SIZE];
	size_t		tempStrLen = 0;

	//add the operator node
	operatorNode = CreateXmlData(L4DB_XML_TOKEN_OPERATOR, "");
	AddChild(parentXmlData, operatorNode);
	
	//add all NSPs under the operator node
	for(i = 0 ; i < WMX_NSPS_MAX_NUM ; i++)
	{
		//check that the node has been allocated
		tempStrLen = OSAL_strnlen(pNsps[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//create the unique name node
			l4db_AddTagNamePrefix(pNsps[i].tagName, buff, BUFF_SIZE);
			nspUniqueNameNode = CreateXmlData(buff, "");
			AddChild(operatorNode, nspUniqueNameNode);

			//add the nw params node
			l4db_AddNwParamsToXml(nspUniqueNameNode, &pNsps[i].nwParams);

			//add the subscription parameters node
			l4db_AddSubscriptionParamsToXml(nspUniqueNameNode, &pNsps[i].subscriptionParams);

			//add the contacts node
			l4db_AddContactsToXml(nspUniqueNameNode, pNsps[i].contacts);
		}
	}
}

/// <summary>
/// Add an internal parameters node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="internalParamsNode">(IN) Internal parameters node data structure</param>
void l4db_AddInternalAPDOParamsToXml(pXmlElement parentXmlData, APDOInternalParams_t apdoInternalParamsNode)
{
	UINT32 i;
	pXmlElement	apdoInternalNode;
	pXmlElement	nextData;
	pXmlElement nspsToDmAccNode;
	pXmlElement currNSPNode;
	pXmlElement bootstrapInfoNode;
	pXmlElement currBootstrapNode;
	char		tempBEK[BEK_LENGTH*2 + 4];
	char		buff[BUFF_SIZE];
	
	//add the internal node
	apdoInternalNode = CreateXmlData(L4DB_XML_TOKEN_APDO_INTERNAL, "");	
	AddChild(parentXmlData, apdoInternalNode);

	l4db_AddFumoInternalToXml(apdoInternalNode, apdoInternalParamsNode.fumoInternal);	

	//add the default realm node 
	nextData = CreateXmlData(L4DB_XML_TOKEN_DEFAULT_REALM, apdoInternalParamsNode.defaultRealm);
	AddChild(apdoInternalNode, nextData);

	//add the default BEK node
	tempBEK[0] = '\0';
	if (strlen(apdoInternalParamsNode.bek) != 0)
	{
		NDnSAgent_HexEncode((const UINT8*)apdoInternalParamsNode.bek, tempBEK, BEK_LENGTH - 1);
	}
	
	nextData = CreateXmlData(L4DB_XML_TOKEN_DEFAULT_BEK, tempBEK);
	AddChild(apdoInternalNode, nextData);
	
	
	// Add the NSPsTODMAcc
	nspsToDmAccNode = CreateXmlData(L4DB_XML_TOKEN_NSPS_TO_DMACC, "");
	AddChild(apdoInternalNode, nspsToDmAccNode);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Before Save APDOInternal NSPsTODMAcc entries to DB");
	// Add all NSPs nodes and the correlating DMAcc 
	for (i=0; i<WMX_NSPS_TO_DMACC_NODES_MAX_NUM; i++)
	{
		if(FALSE != l4db_CompareString(apdoInternalParamsNode.nspsToDmAcc[i].tagName, C_L4DB_EMPTY_STRING))
		{
			//create the unique name node
			l4db_AddTagNamePrefix(apdoInternalParamsNode.nspsToDmAcc[i].tagName, buff, BUFF_SIZE);
			currNSPNode = CreateXmlData(buff, "");
			AddChild(nspsToDmAccNode, currNSPNode);

			nextData = CreateXmlData(L4DB_XML_TOKEN_TO_DM_ACCOUNT, apdoInternalParamsNode.nspsToDmAcc[i].toDMAcc);
			AddChild(currNSPNode, nextData);
		}
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "After Save APDOInternal NSPsTODMAcc entries to DB");

	// Add all bootstrap info nodes and data
	bootstrapInfoNode = CreateXmlData(L4DB_XML_TOKEN_BOOTSTRAP_INFO, "");
	AddChild(apdoInternalNode, bootstrapInfoNode);
	
	for (i=0; i<WMX_NSPS_MAX_NUM; i++)
	{
		if(FALSE != l4db_CompareString(apdoInternalParamsNode.bootstrapInfo[i].tagName, C_L4DB_EMPTY_STRING))
		{
			//create the unique name node
			l4db_AddTagNamePrefix(apdoInternalParamsNode.bootstrapInfo[i].tagName, buff, BUFF_SIZE);
			currBootstrapNode = CreateXmlData(buff, "");
			AddChild(bootstrapInfoNode, currBootstrapNode);

			nextData = CreateXmlData(L4DB_XML_TOKEN_SERVER_ID, apdoInternalParamsNode.bootstrapInfo[i].serverID);
			AddChild(currBootstrapNode, nextData);
			nextData = CreateXmlData(L4DB_XML_TOKEN_SERVER_USER_NAME, apdoInternalParamsNode.bootstrapInfo[i].serverUserName);
			AddChild(currBootstrapNode, nextData);
			nextData = CreateXmlData(L4DB_XML_TOKEN_CLIENT_USER_NAME, apdoInternalParamsNode.bootstrapInfo[i].clientUserName);
			AddChild(currBootstrapNode, nextData);
			nextData = CreateXmlData(L4DB_XML_TOKEN_SERVER_URL, apdoInternalParamsNode.bootstrapInfo[i].serverURL);
			AddChild(currBootstrapNode, nextData);
			nextData = CreateXmlData(L4DB_XML_TOKEN_PORT_NUMBER, apdoInternalParamsNode.bootstrapInfo[i].portNbr);
			AddChild(currBootstrapNode, nextData);
		}
	}
	l4db_AddApdoOperatorConfigurationToXml(apdoInternalNode, apdoInternalParamsNode.configurations);	
}
/// <summary>
/// Add a fumo internal node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="FumoNode">(IN) Fumo internal node data structure</param>
void l4db_AddFumoInternalToXml(pXmlElement parentXmlData, FumoInternalParams_t fumoNode)
{
	pXmlElement	fumoInternalNode;
	pXmlElement	nextData;
	char		buf[BUFF_SIZE];

	//add the FUMO internal node
	fumoInternalNode = CreateXmlData(L4DB_XML_TOKEN_FUMO_INTERNAL, "");	
	AddChild(parentXmlData, fumoInternalNode);

	//add the PkgPath node
	nextData = CreateXmlData(L4DB_XML_TOKEN_PKG_PATH, fumoNode.pkgPath);
	AddChild(fumoInternalNode, nextData);

	//add the PkgFileName node
	nextData = CreateXmlData(L4DB_XML_TOKEN_PKG_FILE_NAME, fumoNode.pkgFileName);
	AddChild(fumoInternalNode, nextData);

	//add the PkgPath node
	nextData = CreateXmlData(L4DB_XML_TOKEN_FUMO_NODE_PATH, fumoNode.fumoNodePath);
	AddChild(fumoInternalNode, nextData);

	//add the Fumo Operation node
	OSAL_itoa_s(fumoNode.fumoOperation, buf, sizeof(buf), 10);
	nextData = CreateXmlData(L4DB_XML_TOKEN_FUMO_OPERATION, buf);
	AddChild(fumoInternalNode, nextData);
}

/// <summary>
/// Add a ApdoOperatorConfigurationToXml internal node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="FumoNode">(IN) ApdoOperatorConfiguration internal node data structure</param>
void l4db_AddApdoOperatorConfigurationToXml(pXmlElement parentXmlData, wmx_ApdoOperatorConfigurations_t configurationNode[MAX_NUM_OF_CONFIGURATIONS])
{

	pXmlElement	configurationInternalNode;
	pXmlElement	nextData;
	pXmlElement	nextNextData, currentNode;
	char		buf[BUFF_SIZE];
	int i=0;
	UNREFERENCED_PARAMETER(buf);
	//UNREFERENCED_PARAMETER(configurationNode);

	//char		tempOperatorName[MAX_SIZE_OF_NSP_NAME];

	//add the ApdoOperatorConfigurations internal node
	configurationInternalNode = CreateXmlData(L4DB_XML_TOKEN_APDO_OPERAOTR_CONFIGURATIONS, "");	
	AddChild(parentXmlData, configurationInternalNode);

	//add the Operator node
	nextData = CreateXmlData(L4DB_XML_TOKEN_OPERATOR, "");
	AddChild(configurationInternalNode, nextData);
	
	for (i =0 ; i < MAX_NUM_OF_CONFIGURATIONS ; i++){
		//add the Operator Tag Name node
		if (OSAL_stricmp(configurationNode[i].nspTagName, L4DB_XML_APDO_CONFIG_UNAVAILABLE) != 0)
		{
			nextNextData = CreateXmlData(configurationNode[i].nspTagName, "");
			AddChild(nextData, nextNextData);
			//add the PreProvBStrap node
			currentNode = CreateXmlData(L4DB_XML_TOKEN_PRE_PROVISIONS_BSTRAP, (configurationNode[i].preProvBStrap ? L4DB_XML_TRUE_STR : L4DB_XML_FALSE_STR));
			AddChild(nextNextData,currentNode);
			//add the PollingInterval node
			currentNode = CreateXmlData(L4DB_XML_TOKEN_POLLING_INTERVAL, (configurationNode[i].pollingInterval ? L4DB_XML_TRUE_STR : L4DB_XML_FALSE_STR));
			AddChild(nextNextData,currentNode);
			//add the BLOCK UDP  node
			currentNode = CreateXmlData(L4DB_XML_TOKEN_BLOCK_UDP, (configurationNode[i].blockUDP ? L4DB_XML_TRUE_STR : L4DB_XML_FALSE_STR));
			AddChild(nextNextData,currentNode);
			//add the polling attempts
			currentNode = CreateXmlData(L4DB_XML_TOKEN_POLLING_ATTEMPTS, (configurationNode[i].pollingAttempts? L4DB_XML_TRUE_STR : L4DB_XML_FALSE_STR));
			AddChild(nextNextData,currentNode);
			//add the disable OTAP
			currentNode = CreateXmlData(L4DB_XML_TOKEN_DISABLE_OTAP, (configurationNode[i].disableOTAP? L4DB_XML_TRUE_STR : L4DB_XML_FALSE_STR));
			AddChild(nextNextData,currentNode);
			//add the disable PseudoNAI
			currentNode = CreateXmlData(L4DB_XML_TOKEN_DISABLE_PSEUDO_NAI, (configurationNode[i].disablePseudoNAI? L4DB_XML_TRUE_STR : L4DB_XML_FALSE_STR));
			AddChild(nextNextData,currentNode);
		}
	}
}
/// <summary>
/// Add a Fumo node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNsps">(IN) an array of Fumo nodes data structure</param>
void l4db_AddFumoToXml(pXmlElement parentXmlData, pFumoParams_t pFumoNodes)
{
	char		buff[BUFF_SIZE];
	pXmlElement	fumoNode;
	pXmlElement	fumoUniqueNameNode;
	pXmlElement downloadNode;
	pXmlElement	nextData;
	int i;
	size_t		tempStrLen = 0;

	//add the Fumo node
	fumoNode = CreateXmlData(L4DB_XML_TOKEN_FUMO, "");	
	AddChild(parentXmlData, fumoNode);

	//add all Fumo parameters nodes under the main Fumo node
	for(i = 0 ; i < WMX_FUMO_NODES_MAX_NUM ; i++)
	{
		//check that the node has been allocated
		tempStrLen = OSAL_strnlen(pFumoNodes[i].tagName, MAX_TAG_NAME_SIZE);
		if(0 != tempStrLen && MAX_TAG_NAME_SIZE != tempStrLen)
		{
			//create the unique name node
			fumoUniqueNameNode = CreateXmlData(pFumoNodes[i].tagName, "");
			AddChild(fumoNode, fumoUniqueNameNode);

			//add all nodes under this Fumo node
			
			//add the PkgName node
			nextData = CreateXmlData(L4DB_XML_TOKEN_PKG_NAME, pFumoNodes[i].pkgName);
			AddChild(fumoUniqueNameNode, nextData);

			//add the PkgVersion node
			nextData = CreateXmlData(L4DB_XML_TOKEN_PKG_VERSION, pFumoNodes[i].pkgVersion);
			AddChild(fumoUniqueNameNode, nextData);

			//add the download node 
			downloadNode = CreateXmlData(L4DB_XML_TOKEN_DOWNLOAD, "");
			AddChild(fumoUniqueNameNode, downloadNode);

			/*nextData = CreateXmlData(L4DB_XML_TOKEN_PKG_URL, pFumoNodes[i].downloadPkgURL);
			AddChild(downloadNode, nextData);*/						

			//add the download And update node 
			downloadNode = CreateXmlData(L4DB_XML_TOKEN_DOWNLOAD_AND_UPDATE, "");
			AddChild(fumoUniqueNameNode, downloadNode);

			/*nextData = CreateXmlData(L4DB_XML_TOKEN_PKG_URL, pFumoNodes[i].downloadAndUpdatePkgURL);
			AddChild(downloadNode, nextData);	*/					

			//add the state node
			ConvertDownloadStateToStr(pFumoNodes[i].state, buff, BUFF_SIZE);
			nextData = CreateXmlData(L4DB_XML_TOKEN_STATE, buff);
			AddChild(fumoUniqueNameNode, nextData);
		}
	}
}
/// <summary>
/// Add the other nap info node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNaps">(IN) an array of discovered naps data structure</param>
void l4db_AddOtherNapInfoToXml(pXmlElement parentXmlData, pDiscoveredNap_t pNaps)
{
	pXmlElement	otherNapsInfoNode;
	pXmlElement	napNode;
	pXmlElement nspNode;
	pXmlElement nextData;
	char		buff[BUFF_SIZE];
	int			i;
	UINT32		j;	

	//create the other nap info node
	otherNapsInfoNode = CreateXmlData(L4DB_XML_TOKEN_DISCOVERED_NAP_INFO, "");
	AddChild(parentXmlData, otherNapsInfoNode);

	//iterate through all the NAPs
	for(i = 0 ; i < MAX_NUM_OF_DISCOVERED_NAPS ; i++)
	{
		//check that this NAP has been allocated
		if(FALSE == L4db_IsNapidEmpty(pNaps[i].napID))
		{
			napNode = CreateXmlData(L4DB_XML_TOKEN_NAP,"");
			l4db_ConvertNapIdToStr(pNaps[i].napID, buff);
			AddAttribute(napNode, L4DB_XML_TOKEN_ID, buff);
			AddChild(otherNapsInfoNode, napNode);

			//add all nodes under this NAP
			l4db_GetBoolStr(pNaps[i].isLastDetected, buff);
			nextData = CreateXmlData(L4DB_XML_TOKEN_LAST_DETECTED, buff);
			AddChild(napNode, nextData);

			//add the change count node
			OSAL_itoa_s(pNaps[i].changeCount, buff, BUFF_SIZE, 10);
			nextData = CreateXmlData(L4DB_XML_TOKEN_CHANGE_COUNT, buff);
			AddChild(napNode, nextData);

			// Add the channel plan node. 
			l4db_AddChannelPlanToXml(napNode, &pNaps[i].channelPlan);

			//add all NSP nodes
			for(j = 0 ; j < pNaps[i].nspInfoSize; j++)
			{
				//check that this NSP has been allocates
				if(L4DB_INVALID_INDEX != pNaps[i].nspInfo[j].nspID)
				{
					nspNode = CreateXmlData(L4DB_XML_TOKEN_NSP, "");
					OSAL_itoa_s(pNaps[i].nspInfo[j].nspID, buff, BUFF_SIZE, 10);
					AddAttribute(nspNode, L4DB_XML_TOKEN_ID, buff);
					AddChild(napNode, nspNode);

					//add all nodes under this NSP
					//add the name node
					nextData = CreateXmlData(L4DB_XML_TOKEN_NAME, pNaps[i].nspInfo[j].name);
					AddChild(nspNode, nextData);

					//add the visited realm node
					nextData = CreateXmlData(L4DB_XML_TOKEN_VISITED_REALM, pNaps[i].nspInfo[j].visitedRealm);
					AddChild(nspNode, nextData);
				}
			}
		}
	}
}

/// <summary>
/// Add the profiles info node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="numOfProfiles">(IN) number of elements in the profiles array</param>
/// <param name="pProfiles">(IN) an array of profiles' data structure</param>
void l4db_AddProfilesInfoToXml(pXmlElement parentXmlData, UINT32 numOfProfiles, pProfile_t pProfiles)
{
	pXmlElement		profilesNode, profileNode, NapIDNode, NspIDNode;	
	char			buff[BUFF_SIZE];
	UINT32			i, k;	
	wmx_Status_t	st;
	wmx_NSPid_t		nspIds[WMX_NSP_IDS_MAX_NUM];
	UINT32			numOfNspIDs = WMX_NSP_IDS_MAX_NUM;

	st = L4db_GetProvisionedNspIds(nspIds, &numOfNspIDs);	
	
	profilesNode = CreateXmlData(L4DB_XML_TOKEN_UNPROVISIONED_PROFILES, "");
	AddChild(parentXmlData, profilesNode);

	// Validity check
	if (numOfProfiles <= 0 ||
		numOfProfiles > WMX_NSPS_MAX_NUM ||
		pProfiles == NULL)
	{
		return;
	}

	//iterate through all the Profiles
	for(i = 0 ; i < numOfProfiles ; i++)
	{
		if((wmx_NSPid_t)L4DB_INVALID_INDEX != pProfiles[i].nspID)
		{
			for (k=0; k < (int)numOfNspIDs; k++)
			{
				if (pProfiles[i].nspID == nspIds[k])	
				{
					break; // The NSP exists in the provisioned information
				}
			}

			// Check if the NSP ID exists
			if (k != (int)numOfNspIDs)
			{			
				// The NSP exists
				continue;
			}
		}

		profileNode = CreateXmlData(L4DB_XML_TOKEN_UNPROVISIONED_PROFILE,"");
		OSAL_itoa_s(i, buff, BUFF_SIZE, 10);
		AddAttribute(profileNode, L4DB_XML_TOKEN_ID, buff);
		AddChild(profilesNode, profileNode);

		l4db_ConvertNapIdToStr(pProfiles[i].napID, buff);
		NapIDNode = CreateXmlData(L4DB_XML_TOKEN_NAP_ID_DASH, buff);
		AddChild(profileNode, NapIDNode);

		OSAL_itoa_s(pProfiles[i].nspID, buff, BUFF_SIZE, 10);
		NspIDNode = CreateXmlData(L4DB_XML_TOKEN_NSP_ID_DASH, buff);
		AddChild(profileNode, NspIDNode);

		// Add the channel plan node. 
		l4db_AddChannelPlanToXml(profileNode, &pProfiles[i].channelPlan);		
	}
}
/// <summary>
/// Add the dev info node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevInfo">(IN) the dev info data structure</param>
void l4db_AddDevInfoToXml(pXmlElement parentXmlData, pDevInfo_t pDevInfo)
{
	pXmlElement	devInfoNode;
	pXmlElement	nextNode;

	//create the dev info node
	devInfoNode = CreateXmlData(L4DB_XML_TOKEN_DEV_INFO, "");
	AddChild(parentXmlData, devInfoNode);

	//add the manufacturer node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_MAN, pDevInfo->manufacturer);
	AddChild(devInfoNode, nextNode);

	//add the model node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_MOD, pDevInfo->model);
	AddChild(devInfoNode, nextNode);

	//add the devid node mzur todo remove in the future 
	nextNode = CreateXmlData(L4DB_XML_TOKEN_DEV_ID, pDevInfo->devID);
	AddChild(devInfoNode, nextNode);
}

/// <summary>
/// Add the dev detail uri node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevDetailUri">(IN) the dev detail uri data structure</param>
void l4db_AddDevDetailUriToXml(pXmlElement parentXmlData, pDevDetailURI_t pDevDetailUri)
{
	pXmlElement	devDetailUriNode;
	pXmlElement	nextNode;

	//create the dev detail uri node
	devDetailUriNode = CreateXmlData(L4DB_XML_TOKEN_URI, "");
	AddChild(parentXmlData, devDetailUriNode);

	//add the MaxDepth node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_URI_MAX_DEPTH, pDevDetailUri->MaxDepth);
	AddChild(devDetailUriNode, nextNode);

	//add the MaxDepth node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_URI_MAX_TOT_LEN, pDevDetailUri->MaxTotLen);
	AddChild(devDetailUriNode, nextNode);

	//add the MaxDepth node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_URI_MAX_SEG_LEN, pDevDetailUri->MaxSegLen);
	AddChild(devDetailUriNode, nextNode);
}


/// <summary>
/// Add the dev detail node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevDetail">(IN) the dev detail data structure</param>
void l4db_AddDevDetailToXml(pXmlElement parentXmlData, pDevDetail_t pDevDetail)
{
	pXmlElement	devDetailNode;
	pXmlElement	nextNode;

	//create the dev info node
	devDetailNode = CreateXmlData(L4DB_XML_TOKEN_DEV_DETAIL, "");
	AddChild(parentXmlData, devDetailNode);

	//add the dev typ node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_DEV_TYP, pDevDetail->devType);
	AddChild(devDetailNode, nextNode);

	//add the sw version node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_SW_VERSION, pDevDetail->swVersion);
	AddChild(devDetailNode, nextNode);

	//add the fw version node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_FW_VERSION, pDevDetail->fwVersion);
	AddChild(devDetailNode, nextNode);

	//add the hw version node
	nextNode = CreateXmlData(L4DB_XML_TOKEN_HW_VERSION, pDevDetail->hwVersion);
	AddChild(devDetailNode, nextNode);

	// add the uri node
	l4db_AddDevDetailUriToXml(devDetailNode, &pDevDetail->uri);

	//add the lrg obj version node	
	nextNode = CreateXmlData(L4DB_XML_TOKEN_LRG_OBJ, pDevDetail->lrgObj);
	AddChild(devDetailNode, nextNode);
}

/// <summary>
/// Add the wimax supp node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pNsps">(IN) a pointer to the array of NSPs</param>
void l4db_AddWmxSuppToXml(pXmlElement parentXmlData, pProvisionedNsp_t pNsps)
{
	pXmlElement	wmxSuppNode;
//	pXmlElement	nextNode;

	//create the dev info node
	wmxSuppNode = CreateXmlData(L4DB_XML_TOKEN_WMX_SUPP, "");
	AddChild(parentXmlData, wmxSuppNode);

	l4db_AddOperatorToXml(wmxSuppNode, pNsps);
}
/// <summary>
/// Add the wimax node to the XML structure
/// </summary>
/// <param name="parentXmlData">(IN) the node's parent XML node</param>
/// <param name="pDevDetail">(IN) the wimax data structure</param>
void l4db_AddWmxToXml(pXmlElement parentXmlData, pWimax_t pWimax)
{
	pXmlElement	wimaxNode;
	pXmlElement	termEquipNode;
	pXmlElement devCapNode, UpdateMethodsNode,  ClientInitiatedNode, PollingSupportedNode;
	pXmlElement	devIdNode;
	pXmlElement	wmxRadioModule;
	pXmlElement	wmxDynamicNode;
	pXmlElement	tempNode;
	char		buff[BUFF_SIZE];

	//create the wimax
	wimaxNode = CreateXmlData(L4DB_XML_TOKEN_WIMAX, "");
	AddChild(parentXmlData, wimaxNode);

	//add the terminal equipment
	termEquipNode = CreateXmlData(L4DB_XML_TOKEN_TERM_EQUIP, "");
	AddChild(wimaxNode, termEquipNode);

	//add the dev id node
	devIdNode = CreateXmlData(L4DB_XML_TOKEN_TERMINAL_DEV_ID, pWimax->terminalEquipment.devId);
	AddChild(termEquipNode, devIdNode);

	// Add terminal equipment nodes
	tempNode = CreateXmlData(L4DB_XML_TOKEN_MOD, pWimax->terminalEquipment.productVersions.model);
	AddChild(termEquipNode, tempNode);
	tempNode = CreateXmlData(L4DB_XML_TOKEN_MAN, pWimax->terminalEquipment.productVersions.manufacturer);
	AddChild(termEquipNode, tempNode);
	tempNode = CreateXmlData(L4DB_XML_TOKEN_SW_VERSION, pWimax->terminalEquipment.productVersions.swVersion);
	AddChild(termEquipNode, tempNode);

	// add the devcap tree node
	devCapNode = CreateXmlData(L4DB_XML_TOKEN_DEV_CAP, "");
	AddChild(wimaxNode, devCapNode);
	// Add devcap tree nodeS
	UpdateMethodsNode = CreateXmlData(L4DB_XML_TOKEN_UPDATE_METHODS, "");
	AddChild(devCapNode, UpdateMethodsNode);
	ClientInitiatedNode = CreateXmlData(L4DB_XML_TOKEN_CLIENT_INIT, "");
	AddChild(UpdateMethodsNode, ClientInitiatedNode);	
	PollingSupportedNode = CreateXmlData(L4DB_XML_TOKEN_POLLING_SUPPORTED, (pWimax->devCap.updateMethods.clientInitiated.pollingSupported == TRUE ? "True" : "False"));
	AddChild(ClientInitiatedNode, PollingSupportedNode);
	OSAL_itoa_s(pWimax->devCap.updateMethods.clientInitiated.pollingInterval, buff, BUFF_SIZE, 10);
	PollingSupportedNode = CreateXmlData(L4DB_XML_TOKEN_POLLING_INTERVAL, buff);
	AddChild(ClientInitiatedNode, PollingSupportedNode);
	OSAL_itoa_s(pWimax->devCap.updateMethods.clientInitiated.pollingAttempts, buff, BUFF_SIZE, 10);
	PollingSupportedNode = CreateXmlData(L4DB_XML_TOKEN_POLLING_ATTEMPTS, buff);
	AddChild(ClientInitiatedNode, PollingSupportedNode);
	
	// Add radio module node 
	wmxRadioModule = CreateXmlData(L4DB_XML_TOKEN_WMX_RADIO_MODULE, "");
	AddChild(wimaxNode, wmxRadioModule);

	// Add WiMAX "dynamic" node	
	wmxDynamicNode = CreateXmlData(L4DB_XML_TOKEN_WIMAX, "");
	AddChild(wmxRadioModule, wmxDynamicNode);

	// Add nodes under radio module
	// Mod
	tempNode = CreateXmlData(L4DB_XML_TOKEN_MOD, pWimax->radioModules[0].productVersions.model);
	AddChild(wmxDynamicNode, tempNode);
	// Man
	tempNode = CreateXmlData(L4DB_XML_TOKEN_MAN, pWimax->radioModules[0].productVersions.manufacturer);
	AddChild(wmxDynamicNode, tempNode);
	// swv
	tempNode = CreateXmlData(L4DB_XML_TOKEN_SW_VERSION, pWimax->radioModules[0].productVersions.swVersion);
	AddChild(wmxDynamicNode, tempNode);
	// hwv
	tempNode = CreateXmlData(L4DB_XML_TOKEN_HW_VERSION, pWimax->radioModules[0].productVersions.hwVersion);
	AddChild(wmxDynamicNode, tempNode);
	// fwv
	tempNode = CreateXmlData(L4DB_XML_TOKEN_FW_VERSION, pWimax->radioModules[0].productVersions.fwVersion);
	AddChild(wmxDynamicNode, tempNode);

	// Mac address
	tempNode = CreateXmlData(L4DB_XML_TOKEN_MAC_ADDRESS, pWimax->radioModules[0].macAddress);
	AddChild(wmxDynamicNode, tempNode);
}