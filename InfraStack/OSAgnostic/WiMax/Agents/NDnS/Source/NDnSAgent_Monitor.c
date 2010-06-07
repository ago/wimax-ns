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
#include "NDnSAgent_Monitor.h"
#include "L4DmMonitorGroups.h"
#include "NDnSAgent.h"

extern pL4db_Context	g_pL4dbContext;
extern BOOL				g_fIsInitiated;

#define INIT_VALUE 10


BOOL wmx_checkMultyBufferChange(UINT8 *pOriginalBuff,
								const size_t originalNumOfElements,
								const size_t originalBuffElemSize,
								size_t *pElementToChange,
								UINT8 *pNewBuff, 
								const size_t newBuffSize)

{
	
	size_t i;
	size_t temp;
	size_t sizeToCopy;

	if(originalBuffElemSize < newBuffSize)
	{
		sizeToCopy = originalBuffElemSize;
	}
	else
	{
		sizeToCopy = newBuffSize;
	}

	for(i=0; i< originalNumOfElements; i++)
	{
		//each time compare to new element
		if(0 == memcmp((pOriginalBuff + (i * originalBuffElemSize)), pNewBuff, sizeToCopy))
		{
			//the new buffer content exist in one of the original buffer elements
			return FALSE;
		}
	}
	//the content of the buffer was not found in the original buffer elements

	//change the element in the original buffer that need to be change
	OSAL_memcpy_s((pOriginalBuff + ((*pElementToChange) * originalBuffElemSize)), sizeToCopy, pNewBuff, sizeToCopy);

	//set the number of the next element that need to be change
	temp = (((*pElementToChange)++) % originalNumOfElements);

	*pElementToChange = temp;

	return TRUE;
}

BOOL wmx_checkBufferChange(void *pOriginalBuff, size_t originalBuffSize, void *pNewBuff, size_t newBuffSize)
{
	size_t elementNum =0;
	return wmx_checkMultyBufferChange(pOriginalBuff,
									  1,
									  originalBuffSize,
									  &elementNum,
									  pNewBuff,
									  newBuffSize);
}

void wmx_MonitorSendScanResults(wmx_pScanResults_t scanResults, wmx_pNSP_t pNSPs, UINT32 numOfNSPs)
{
	UINT8 buff[2*(sizeof(UINT32)*WMX_NAPS_MAX_NUM + 4) + (BM_MonitorScanResult_FullBSIDArr_FullBSID_bsID_BYTES_SIZE * WMX_NAPS_MAX_NUM + 4)];
	UINT8* tempBuff;
	UINT tempBitOff = 0;
	UINT tempBuffSize = 0;
	UINT32 i;

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_SCAN_RESULT))
	{
		BM_MonitorScanResult_AvailableNSPsIdlist_NumOfNSPs_SET(buff,numOfNSPs);
		for(i=0;i<numOfNSPs;i++)
		{
			BM_MonitorScanResult_AvailableNSPsIdlist_NSPID_value_SET(buff,i,pNSPs[i].nspIDs[0]);
		}
		BM_MonitorScanResult_FullBSIDArr_NumOfBSIDs_SET(buff,scanResults->NAPsCount);
		for(i=0;i<scanResults->NAPsCount;i++)
		{
			BM_MonitorScanResult_FullBSIDArr_FullBSID_GET_ELEMENT_POS(buff, i, tempBuff, tempBitOff);
			memcpy(tempBuff,&(scanResults->NAPs[i].bsCriteria),BM_MonitorScanResult_FullBSIDArr_FullBSID_BYTES_CELL_SIZE);
		}

		BM_MonitorScanResult_GET_BYTES_SIZE(buff, tempBuffSize);
		L4DnDHndlr_PostMon(buff,L3L4_TLV_TYPE_MONITOR_SCAN_RESULT,(UINT16)tempBuffSize);
	}
}

//send to the monitor the scan indication includes the start (as 1)or the end (as 2)indication + the time
void wmx_MonitorScanInd(BM_StartEndInd startEndInd)
{
	SYSTEMTIME SystemTime;
	UINT8 buff[BM_MonitorScanInd_BYTES_SIZE];
	UINT tempBuffSize = 0;

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_SCAN_IND))
	{
		memset(buff,'\0',BM_MonitorScanInd_BYTES_SIZE);
		BM_MonitorScanInd_ScanStartEndInd_SET(buff,startEndInd);

		OSAL_GetLocalTime(&SystemTime);
		BM_MonitorScanInd_Time_wMilliseconds_SET(buff,SystemTime.wMilliseconds);
		BM_MonitorScanInd_Time_wSecond_SET(buff,SystemTime.wSecond);
		BM_MonitorScanInd_Time_wMinute_SET(buff,SystemTime.wMinute);
		BM_MonitorScanInd_Time_wHour_SET(buff,SystemTime.wHour);

		BM_MonitorScanInd_GET_BYTES_SIZE(buff, tempBuffSize);
		L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_SCAN_IND, (UINT16)tempBuffSize);
	} 
}

//populate the Rapl struct from the DB global variable for the MonitorOperator TLV
//[in]pRapl_t pRapl - receive the data of the Rapl structure
//[out]UINT8 *buff - buff populate the content of the Rapl in the buff
void wmx_PopulateRapllMonitor(pRapl_t pRapl, UINT8 *buff)
{
	UINT32 i = 0;

	for(i=0; i<pRapl->roamingPartnersSize; i++)
	{
		BM_MonitorOperator_Rapls_RaplList_vNspID_SET(buff,i,pRapl->roamingPartners[i].vNspID);
		BM_MonitorOperator_Rapls_RaplList_vNspID_SET(buff,i, pRapl->roamingPartners[i].priority);
	}
	BM_MonitorOperator_Rapls_Any_SET(buff,pRapl->any);
}

//populate the Capl struct from the DB global variable for the MonitorOperator TLV
//[in]pRapl_t pCapl - receive the data of the Capl structure
//[out]UINT8 *buff - buff populate the content of the Capl in the buff
void wmx_PopulateCapllMonitor(pCapl_t pCapl, UINT8 *buff)
{
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;
	UINT32 i = 0;
	
	for(i=0; i<(pCapl->napsSize); i++)
	{
		BM_MonitorOperator_Capls_CaplNapList_NapMember_GET_POS(buff,i,tempPos,bitOff);
		memcpy(tempPos,&pCapl->naps[i].napID,BM_MonitorOperator_Capls_CaplNapList_NapMember_napID_BYTES_SIZE);

		BM_MonitorOperator_Capls_CaplNapList_priority_SET(buff, i, pCapl->naps[i].priority);
	}
}

//populate the Eap struct from the DB global variable for the MonitorOperator TLV
//[in]pRapl_t pEAP - receive the data of the EAP structure
//[out]UINT8 *buff - buff populate the content of the EAP in the buff
//[in]int counter - indicate the Eap location in the buff 
void wmx_PopulateEapMonitor(pEAP_t pEAP, UINT8 *buff, int counter)
{
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;
	BM_MonitorOperator_Eaps_EapList_EAPMethod_SET(buff, counter, pEAP->EAPMethod);
	BM_MonitorOperator_Eaps_EapList_vendorId_SET(buff, counter, pEAP->vendorId);
	BM_MonitorOperator_Eaps_EapList_vendorType_SET(buff, counter, pEAP->vendorType);

	BM_MonitorOperator_Eaps_EapList_EapId_GET_POS(buff, counter, tempPos, bitOff);
	memcpy(tempPos, pEAP->id, BM_WMX_SUBSCRIBER_ID_MAX_SIZE);

	BM_MonitorOperator_Eaps_EapList_provisionedPseudoId_GET_POS(buff, counter, tempPos, bitOff);
	memcpy(tempPos, pEAP->provisionedPseudoId, BM_WMX_SUBSCRIBER_ID_MAX_SIZE);

	BM_MonitorOperator_Eaps_EapList_EapPassword_GET_POS(buff, counter, tempPos, bitOff);
	memcpy(tempPos, pEAP->Password, BM_MAX_EAP_PASSWORD_SIZE);

	BM_MonitorOperator_Eaps_EapList_Realm_GET_POS(buff, counter, tempPos, bitOff);
	memcpy(tempPos, pEAP->realm, BM_WMX_NSP_REALM_MAX_SIZE);

	BM_MonitorOperator_Eaps_EapList_encaps_SET(buff, counter, pEAP->encaps);
	BM_MonitorOperator_Eaps_EapList_usePrivacy_SET(buff, counter, pEAP->usePrivacy);
}

//send the operator information stored in the DB
wmx_Status_t wmx_PopulateMonitorOperator()
{
	UINT32 i =0 ,j = 0;
	UINT8 *buff = NULL;
	UINT8 *tempPos = NULL;
	UINT32 tempBuffSize = 0;
	UINT32 tempOperatorSize = 0;
	wmx_NSPid_t NspIds[WMX_NSP_IDS_MAX_NUM * WMX_NSPS_MAX_NUM];
	UINT32	NumOfProvisionedNspIds = 0;
	ProvisionedNsp_t ProvisionedNsp;
	wmx_Status_t status = WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED;
	UINT32 counterEAP=0;
	UINT32 numOfNsp=0;
	UINT bitOff = 0;
	

	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "wmx_PopulateMonitorOperator in");

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_OPERATOR))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "wmx_PopulateMonitorOperator buffer was allocated with success");

		NumOfProvisionedNspIds = (WMX_NSP_IDS_MAX_NUM * WMX_NSPS_MAX_NUM);
		status = L4db_GetProvisionedNspIds(NspIds, &NumOfProvisionedNspIds);
		if (WMX_ST_OK == status)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "wmx_PopulateMonitorOperator ProvisionedNspIds founded");
			//Eap		
			for(numOfNsp = 0; numOfNsp < NumOfProvisionedNspIds; numOfNsp++)
			{
				status = L4db_GetProvisionedNspEx(NspIds[numOfNsp], &ProvisionedNsp,FALSE);
				if(WMX_ST_OK != status)
				{
					//will not generate any message and exit
					break;
				}
				status = L4db_GetNwParamsPerNsp(NspIds[numOfNsp],&(ProvisionedNsp.nwParams));
				if(WMX_ST_OK != status)
				{
					break;
				}

				//in order to know the total eap amount
				counterEAP = ProvisionedNsp.subscriptionParams.primary.eapInfoSize;
				for(j=0; j<ProvisionedNsp.subscriptionParams.otherSize; j++)
				{
					for(i=0; i< ProvisionedNsp.subscriptionParams.other[j].subscriberInfo.eapInfoSize; i++)
					{
						counterEAP = counterEAP + ProvisionedNsp.subscriptionParams.other[j].subscriberInfo.eapInfoSize;
					}
				}
	
				tempOperatorSize = sizeof(MonitorOperator) + 
						(counterEAP) * BM_EapMember_BYTES_SIZE +
						(ProvisionedNsp.nwParams.capl.napsSize) * BM_CaplNapMember_BYTES_SIZE + 
						(ProvisionedNsp.nwParams.rapl.roamingPartnersSize) * BM_RoamingPartnerInfo_BYTES_SIZE;
				
				if (tempOperatorSize > tempBuffSize)
				{
					if (buff != NULL)
					{
						free(buff);
					}
					tempBuffSize = tempOperatorSize;
					buff = (UINT8*)malloc(tempBuffSize);
					if (buff == NULL)
					{
						TRACE(TR_MOD_DND_AGENT, TR_SEV_ALERT, "wmx_PopulateMonitorOperator: malloc failed !");
						return WMX_ST_FAIL;
					}	
				}
				memset(buff, '\0', tempBuffSize);

				BM_MonitorOperator_Eaps_NumOfEaps_SET(buff,(counterEAP));
				BM_MonitorOperator_Capls_NumOfNaps_SET(buff, ProvisionedNsp.nwParams.capl.napsSize);
				BM_MonitorOperator_Rapls_NumOfRoamingPartners_SET(buff, ProvisionedNsp.nwParams.rapl.roamingPartnersSize);
		
				counterEAP = 0;
				for(j=0; j < ProvisionedNsp.subscriptionParams.otherSize; j++)
				{
					for(i=0; i< ProvisionedNsp.subscriptionParams.other[j].subscriberInfo.eapInfoSize; i++)
					{
						wmx_PopulateEapMonitor(&(ProvisionedNsp.subscriptionParams.other[j].subscriberInfo.eapInfo[i]), buff, counterEAP);
						counterEAP++;
					}
				}
				for(i=0; i < ProvisionedNsp.subscriptionParams.primary.eapInfoSize; i++)
				{
					wmx_PopulateEapMonitor(&(ProvisionedNsp.subscriptionParams.primary.eapInfo[i]), buff, counterEAP);
					counterEAP++;
				}

				//Capl
				wmx_PopulateCapllMonitor(&(ProvisionedNsp.nwParams.capl), buff);

				//Rapl
				wmx_PopulateRapllMonitor(&(ProvisionedNsp.nwParams.rapl), buff);

				//we send also the operator name
				BM_MonitorOperator_operatorName_GET_POS(buff, tempPos, bitOff);
				memcpy(tempPos, ProvisionedNsp.nwParams.provisionedName, BM_MonitorOperator_operatorName_BYTES_SIZE);
				BM_MonitorOperator_pollingInterval_SET(buff, ProvisionedNsp.nwParams.pollingInterval);

		
				BM_MonitorOperator_GET_BYTES_SIZE(buff, tempBuffSize);
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_OPERATOR, (UINT16)tempBuffSize);

				TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "wmx_PopulateMonitorOperator message was sent");
			}
		}
	}
	
	// free resources
	if(buff)
	{
		free(buff);
	}
	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "wmx_PopulateMonitorOperator out");
	return status;

}

//send the full NAI to the monitor 
//[in] wmx_pNAI_t identity the NAI structure
void wmx_PopulateNAIMonitor(wmx_pNAI_t identity)
{
	UINT8 buff[WMX_SUBSCRIBER_ID_MAX_SIZE + WMX_NSP_REALM_MAX_SIZE];
	UINT8 *tempPos = NULL;
	UINT tempBuffSize = 0;
	UINT bitOff = 0;

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_NAI))
	{
		memset(buff, '\0', WMX_SUBSCRIBER_ID_MAX_SIZE + WMX_NSP_REALM_MAX_SIZE);
		BM_MonitorNAI_NAISize_SET(buff, OSAL_strnlen(identity,WMX_SUBSCRIBER_ID_MAX_SIZE + WMX_NSP_REALM_MAX_SIZE));
		BM_MonitorNAI_NAI_GET_POS(buff, tempPos, bitOff);
		memcpy(tempPos, identity, OSAL_strnlen(identity, WMX_SUBSCRIBER_ID_MAX_SIZE + WMX_NSP_REALM_MAX_SIZE));

		BM_MonitorNAI_GET_BYTES_SIZE(buff, tempBuffSize);
		L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_NAI, (UINT16)tempBuffSize);
	}
}

//When receiving during bootstrap or regular, includes details of the enum reporting the specific action: OMA-DM Session start or end, Bootstrap start/end, etc.
//the same indication is being send also in case we start polling
//[in] wmx_ApdoSessionStatus_t sessionStatus the new status
void wmx_PopulateOMASessionMonitor(wmx_ApdoSessionStatus_t sessionStatus)
{
	UINT8 buff[BM_MonitorOMASession_BYTES_SIZE];
	static UINT8 savedBuff[BM_MonitorOMASession_BYTES_SIZE];

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_OMA_SESSION))
	{
		memset(buff, '\0', BM_MonitorOMASession_BYTES_SIZE);
		BM_MonitorOMASession_OMAStatusInd_SET(buff, sessionStatus);

		if(TRUE == wmx_checkBufferChange(savedBuff,BM_MonitorOMASession_BYTES_SIZE, buff, BM_MonitorOMASession_BYTES_SIZE))
		{
			L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_OMA_SESSION, (UINT16)BM_MonitorOMASession_BYTES_SIZE);
		}
	}
}

//Indicate new status for the current operator
//[in] BOOL *ActivationStatus - receive TRUE or FALSE to indicate if status is active or not 
void wmx_PopulateActivationStatusChangeMonitor(BOOL *ActivationStatus)
{
	UINT8 buff[sizeof(BOOL)];

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_ACTIVATION_STATUS_CHANGE))
	{
		memset(buff, '\0', BM_MonitorActivationStatusChange_ActivationStatusInd_BYTES_SIZE);
		BM_MonitorActivationStatusChange_ActivationStatusInd_SET(buff, *ActivationStatus);
		L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_ACTIVATION_STATUS_CHANGE, (UINT16)BM_MonitorActivationStatusChange_ActivationStatusInd_BYTES_SIZE);
	}
}

//populate the FUMO parameters from the DB
wmx_Status_t wmx_PopulateMonitorOMAFumoParams()
{
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;
	FumoParams_t FumoParams;
	UINT8 *buff = NULL;
	UINT tempBuffSize = 0;
	wmx_Status_t status = WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED;

	TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "wmx_PopulateMonitorOMAFumoParams in");

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_OMA_FUMO_PARAMS))
	{
		buff = (UINT8 *)malloc(sizeof(FumoParams_t));
		if(buff)
		{
			memset(buff, '\0', sizeof(FumoParams_t));

			memset(&FumoParams, '\0', sizeof(FumoParams_t));
			
			status = L4db_GetFumoNode(&FumoParams);
			if(WMX_ST_OK == status)
			{
				BM_MonitorOMAFumoParams_FUMO_pkgName_GET_POS(buff, tempPos, bitOff);
				memcpy(tempPos,FumoParams.pkgName, BM_MonitorOMAFumoParams_FUMO_pkgName_BYTES_SIZE);

				BM_MonitorOMAFumoParams_FUMO_pkgVersion_GET_POS(buff, tempPos, bitOff);
				memcpy(tempPos,FumoParams.pkgVersion, BM_MonitorOMAFumoParams_FUMO_pkgVersion_BYTES_SIZE);

				BM_MonitorOMAFumoParams_FUMO_downloadPkgURL_GET_POS(buff, tempPos, bitOff);
				memcpy(tempPos, FumoParams.downloadPkgURL, BM_MonitorOMAFumoParams_FUMO_downloadPkgURL_BYTES_SIZE);
	
				BM_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_GET_POS(buff, tempPos, bitOff);
				memcpy(tempPos, FumoParams.downloadAndUpdatePkgURL, BM_MonitorOMAFumoParams_FUMO_downloadAndUpdatePkgURL_BYTES_SIZE);

				BM_MonitorOMAFumoParams_FUMO_state_SET(buff, FumoParams.state);
				BM_MonitorOMAFumoParams_FUMO_fIsAllocated_SET(buff, FumoParams.fIsAllocated);

				BM_MonitorOMAFumoParams_GET_BYTES_SIZE(buff, tempBuffSize);
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_OMA_FUMO_PARAMS, (UINT16)tempBuffSize);
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
	}

	if(buff)
	{
		free(buff);
	}
	return status;
	
}
//populate the Radio parameters (belongs to the WimaxParam) from the DB
//[out] UINT8 *buff - the buffer to be send to the monitor
//[in] pWimax_t pWimaxParams - get the information of the WimaxParams structure
void wmx_PopulateRadioModulesMonitor(UINT8 *buff, pWimax_t pWimaxParams)
{
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;
	UINT32 i = 0;

	BM_MonitorOMAWimaxParams_RadioModule_LenOfRadioModule_SET(buff, pWimaxParams->wmxRadioModulesSize);
	for (i=0; i<(pWimaxParams->wmxRadioModulesSize); i++)
	{
		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_manufacturer_BYTES_SIZE, 
			pWimaxParams->radioModules[i].productVersions.manufacturer, sizeof(pWimaxParams->radioModules[i].productVersions.manufacturer));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_model_BYTES_SIZE, 
			pWimaxParams->radioModules[i].productVersions.model, sizeof(pWimaxParams->radioModules[i].productVersions.model));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_fwVersion_BYTES_SIZE,
			pWimaxParams->radioModules[i].productVersions.fwVersion, sizeof(pWimaxParams->radioModules[i].productVersions.fwVersion));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_swVersion_BYTES_SIZE,
			pWimaxParams->radioModules[i].productVersions.swVersion, sizeof(pWimaxParams->radioModules[i].productVersions.swVersion));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_hwVersion_BYTES_SIZE,
			pWimaxParams->radioModules[i].productVersions.hwVersion, sizeof(pWimaxParams->radioModules[i].productVersions.hwVersion));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_macAddress_BYTES_SIZE,
			pWimaxParams->radioModules[i].macAddress, sizeof(pWimaxParams->radioModules[i].macAddress));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockStatus_SET(buff, i, pWimaxParams->radioModules[i].spLock.lockStatus);
		
		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_operatorName_BYTES_SIZE,
			pWimaxParams->radioModules[i].spLock.operatorName, sizeof(pWimaxParams->radioModules[i].spLock.operatorName));

		BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_GET_POS(buff, i, tempPos, bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_RadioModule_WmxRadioModuleList_SpLock_lockMem_BYTES_SIZE,
			pWimaxParams->radioModules[i].spLock.lock, sizeof(pWimaxParams->radioModules[i].spLock.lock));
	}
}
//populate the TermEquip parameters (belongs to the WimaxParam) from the DB
//[out] UINT8 *buff - the buffer to be send to the monitor
//[in] pTerminalEquipment_t pTerminalEquipment - get the information of the TerminalEquipment structure
void wmx_PopulateTermEquipMonitor(UINT8 *buff, pTerminalEquipment_t TerminalEquipment)
{
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;

	BM_MonitorOMAWimaxParams_TerminalEquipment_devID_devID_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_devID_BYTES_SIZE,
		TerminalEquipment->devId, sizeof(TerminalEquipment->devId));
	
	BM_MonitorOMAWimaxParams_TerminalEquipment_devType_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_devType_BYTES_SIZE,
		TerminalEquipment->devType, sizeof(TerminalEquipment->devType));

	BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_fwVersion_BYTES_SIZE,
		TerminalEquipment->productVersions.fwVersion, sizeof(TerminalEquipment->productVersions.fwVersion));

	BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_swVersion_BYTES_SIZE,
		TerminalEquipment->productVersions.swVersion, sizeof(TerminalEquipment->productVersions.swVersion));

	BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_hwVersion_BYTES_SIZE,
		TerminalEquipment->productVersions.hwVersion, sizeof(TerminalEquipment->productVersions.hwVersion));

	BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_manufacturer_BYTES_SIZE,
		TerminalEquipment->productVersions.manufacturer, sizeof(TerminalEquipment->productVersions.manufacturer));

	BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_GET_POS(buff, tempPos, bitOff);
	OSAL_memcpy_s(tempPos, BM_MonitorOMAWimaxParams_TerminalEquipment_staticTermEquip_model_BYTES_SIZE,
		TerminalEquipment->productVersions.model, sizeof(TerminalEquipment->productVersions.model));

}

//populate the WimaxParam from the DB
wmx_Status_t wmx_PopulateMonitorOMAWimaxParams()
{
	Wimax_t WimaxParams;
	wmx_Status_t status = WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED;
	UINT tempBuffSize = 0;
	UINT8 *buff = NULL;


	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_OMA_WIMAX_PARAMS))
	{
		buff = (UINT8 *)malloc(sizeof(Wimax_t));
		if(buff)
		{
			memset(buff,'\0',sizeof(Wimax_t));

			status = L4db_GetWimaxNode(&WimaxParams);
			if(WMX_ST_OK == status)
			{
				wmx_PopulateRadioModulesMonitor(buff, &WimaxParams); //must be the first because it define the bitman ARR size
				wmx_PopulateTermEquipMonitor(buff, &(WimaxParams.terminalEquipment));
		
				BM_MonitorOMAWimaxParams_GET_BYTES_SIZE(buff, tempBuffSize);
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_OMA_WIMAX_PARAMS, (UINT16)tempBuffSize);
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
	}
	if(buff)
	{
		free(buff);
	}

	return status;
}

//populate the DeviceInfo parameters from the DB
//[out] UINT8 *buff - the buffer to be send to the monitor
wmx_Status_t wmx_PopulateDeviceInfoMonitor(UINT8 *buff)
{
	DevInfo_t DevInfoParams;
	wmx_Status_t status = WMX_ST_OK;
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;

	memset(&DevInfoParams, '\0', sizeof(DevInfo_t));
	status = L4db_GetDevinfo(&DevInfoParams);
	if(WMX_ST_OK == status)
	{
		BM_MonitorOMAParams_DeviceInfo_manufacturer_GET_POS(buff,tempPos,bitOff);
		memcpy(tempPos,DevInfoParams.manufacturer,BM_MonitorOMAParams_DeviceInfo_manufacturer_BYTES_SIZE);

		BM_MonitorOMAParams_DeviceInfo_model_GET_POS(buff,tempPos,bitOff);
		memcpy(tempPos,DevInfoParams.model,BM_MonitorOMAParams_DeviceInfo_model_BYTES_SIZE);

		BM_MonitorOMAParams_DeviceInfo_devID_GET_POS(buff,tempPos,bitOff);
		memcpy(tempPos,DevInfoParams.devID,BM_MonitorOMAParams_DeviceInfo_devID_BYTES_SIZE);
	}
	
	return status;
}

//populate the DeviceDetails parameters from the DB
//[out] UINT8 *buff - the buffer to be send to the monitor
wmx_Status_t wmx_PopulateDeviceDetailsMonitor(UINT8 *buff)
{
	DevDetail_t DevDetailParams;
	wmx_Status_t status = WMX_ST_OK;
	UINT8 *tempPos = NULL;
	UINT bitOff = 0;

	memset(&DevDetailParams,'\0',sizeof(DevDetail_t));
	status = L4db_GetDevDetailParam(&DevDetailParams);
	if(WMX_ST_OK == status)
	{
		BM_MonitorOMAParams_DeviceDetails_devType_GET_POS(buff,tempPos,bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAParams_DeviceDetails_devType_BYTES_SIZE,
			DevDetailParams.devType, sizeof(DevDetailParams.devType));

		BM_MonitorOMAParams_DeviceDetails_fwVersion_GET_POS(buff,tempPos,bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAParams_DeviceDetails_fwVersion_BYTES_SIZE,
			DevDetailParams.fwVersion, sizeof(DevDetailParams.fwVersion));
	
		BM_MonitorOMAParams_DeviceDetails_swVersion_GET_POS(buff,tempPos,bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAParams_DeviceDetails_swVersion_BYTES_SIZE,
			DevDetailParams.swVersion, sizeof(DevDetailParams.swVersion));
	
		BM_MonitorOMAParams_DeviceDetails_hwVersion_GET_POS(buff,tempPos,bitOff);
		OSAL_memcpy_s(tempPos, BM_MonitorOMAParams_DeviceDetails_hwVersion_BYTES_SIZE,
			DevDetailParams.hwVersion, sizeof(DevDetailParams.hwVersion));
	}

	return status;
}

//populate the OMA parameters from the DB
wmx_Status_t wmx_PopulateMonitorOMAParams()
{
	UINT8 *buff = NULL;
	UINT tempBuffSize = 0;
	UINT32 size = 0;
	wmx_Status_t status = WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED;
	
	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_OMA_PARAMS))
	{
		size = sizeof(DevInfo_t)+sizeof(DevDetail_t);
		buff = (UINT8 *)malloc(size);
		if(buff)
		{
			memset(buff,'\0',size);
			status = wmx_PopulateDeviceInfoMonitor(buff);
		
			if(WMX_ST_OK == status)
			{
				status = wmx_PopulateDeviceDetailsMonitor(buff);
				if(WMX_ST_OK == status)
				{
					BM_MonitorOMAParams_GET_BYTES_SIZE(buff, tempBuffSize);
					L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_OMA_PARAMS, (UINT16)tempBuffSize);
				}
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
		
	}
	
	if(buff)
	{
		free(buff);
	}
	return status;
}

//inner function that get pointer to a BMS_ChannelMember in the buff and populate its values
//[out] BMS_ChannelMember *pChannelInfo - the struct need to be populate
//[in] wmx_pChannelInfo_t channelData - the data to be populate
void wmx_populateChannel(BMS_ChannelMember *pChannelInfo, wmx_pChannelInfo_t channelData)
{
	pChannelInfo->_bw = channelData->bw;
	pChannelInfo->_fft = channelData->fft;
	pChannelInfo->_frequency = channelData->frequency;
	memcpy(pChannelInfo->_Preambles._Preambles,channelData->preambleBitmap,BM_MAX_PREAMBLE_SIZE);
}

//send the channels belong to the MCP 
//[in] wmx_pChannelInfo_t pMcp - a pointer to the MCP data
//[in] UINT32 numChannels - the number of channel locate in the MCP
//[in] wmx_LinkLossType_t linkLossType - the linkLoss type (short,long,Infinite)
wmx_Status_t wmx_PopulateMonitorMCP(wmx_pChannelInfo_t pMcp, UINT32 numChannels, wmx_LinkLossType_t linkLossType)
{
	UINT8 *buff = NULL;
	static UINT8 savedBuff[sizeof(wmx_ChannelInfo_t) * TEMP_MAX_CHANNEL_NUM + sizeof(wmx_LinkLossType_t)];
	int bittOff = 0;
	UINT tempBuffSize = 0;
	UINT32 size = 0;
	UINT32 i = 0;
	BMS_ChannelMember *pBmChannelInfo;
	wmx_Status_t status = WMX_ST_OK;

	//try to populate the XMLdata parameters for the first time

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_MCP))
	{
		if(NULL == pMcp)
		{			
			return WMX_ST_FAIL;
		}
		size = sizeof(BMS_ChannelMember)* numChannels + sizeof(wmx_LinkLossType_t) + sizeof(UINT32);
		buff = (UINT8 *)malloc(size);
		if(buff)
		{
			memset(buff,'\0',size);

			BM_MonitorMCP_ChannelInfoArray_NumOfChannels_SET(buff, numChannels);
			BM_MonitorMCP_LinkLossInd_SET(buff, linkLossType);

			for(i=0; i<numChannels; i++)
			{
				if(NULL == &(pMcp[i]))
				{
					free(buff);
					return WMX_ST_FAIL;
				}

				BM_MonitorMCP_ChannelInfoArray_Channels_GET_ELEMENT_POS(buff, i, pBmChannelInfo, bittOff);
				wmx_populateChannel(pBmChannelInfo, &(pMcp[i]));
			}

			BM_MonitorMCP_GET_BYTES_SIZE(buff, tempBuffSize);
			if(TRUE == wmx_checkBufferChange(savedBuff, 
											(sizeof(wmx_ChannelInfo_t) * TEMP_MAX_CHANNEL_NUM + sizeof(wmx_LinkLossType_t) + sizeof(UINT32)),
											buff, 
											size))
			{
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_MCP, (UINT16)tempBuffSize);
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
	}
	if(buff)
	{
		free(buff);
	}
	return status;
}

//send indication when SW Upgrade starts, when user authorizes SW upgrade
//[in] UINT32 currentMonitorInstallingInd - the installing indication(Init = 0,Success = 1,Reset = 2)
void wmx_PopulateMonitorInstallingInd(UINT32 currentMonitorInstallingInd)
{
	UINT8 buff[sizeof(BME_MonitorInstallingInd)];
	static BME_MonitorInstallingInd MonitorInstallingInd = INIT_VALUE;

	if(INIT_VALUE != currentMonitorInstallingInd)
	{
		MonitorInstallingInd = currentMonitorInstallingInd;
	}

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_INSTALLATION_IND) &&
		INIT_VALUE != MonitorInstallingInd)
	{
		memset(buff, '\0', sizeof(UINT32));
		BM_MonitorInstallationInd_MonitorInstallingInd_SET(buff, MonitorInstallingInd);
		L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_INSTALLATION_IND, (UINT16)BM_MonitorInstallationInd_MonitorInstallingInd_BYTES_SIZE);
		MonitorInstallingInd = INIT_VALUE;
	}
}

//Display the scan parameters (the chunk of Master Channel Plan) being set to L3
//[in] ChannelInfoArray_tlv_type *pChannelInfo - the channels sent as a parameter to the scan
//[in] UINT32 numOfChannelInfos - the number of channels
wmx_Status_t wmx_PopulateMoniterScanConfig(ChannelInfoArray_tlv_type *pChannelInfo, UINT32 numOfChannelInfos)
{
	UINT32 size = 0;
	int bittOff = 0;
	UINT tempBuffSize = 0;
	UINT32 i = 0;
	UINT8 *buff = NULL;
	UINT8 sendBuff[sizeof(ChannelInfoArray_tlv_type) * 32 + 4];
	BMS_ChannelInfoArray *pBmChannelInfo = NULL;
	wmx_Status_t status = WMX_ST_OK;


	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_SCAN_CONFIG))
	{
		if(NULL == pChannelInfo)
		{
			return WMX_ST_FAIL;
		}
		size = BM_MoniterScanConfig_SetScanParam_Channels_BYTES_CELL_SIZE * numOfChannelInfos + 4;
		buff = (UINT8 *)malloc(size);
		if(buff)
		{
			memset(buff,'\0',size);

			BM_MoniterScanConfig_SetScanParam_NumOfChannels_SET(buff, numOfChannelInfos);

			for(i=0;i<numOfChannelInfos;i++)
			{
				if(NULL == &(pChannelInfo[i]))
				{					
					free(buff);
					return WMX_ST_FAIL;
				}
				BM_MoniterScanConfig_SetScanParam_Channels_GET_ELEMENT_POS(buff,i,pBmChannelInfo,bittOff);
				pBmChannelInfo->_Bandwidth = pChannelInfo[i].Bandwidth;
				pBmChannelInfo->_ChannelId = pChannelInfo[i].ChannelId;
				pBmChannelInfo->_Fft = pChannelInfo[i].Fft;
				pBmChannelInfo->_Frequency = pChannelInfo[i].Frequency;
				pBmChannelInfo->_Reserved = pChannelInfo[i].Reserved;
				memcpy(pBmChannelInfo->_Preambles,pChannelInfo[i].Preambles,BM_MoniterScanConfig_SetScanParam_Channels_Preambles_BYTES_SIZE);
			}

			BM_MoniterScanConfig_GET_BYTES_SIZE(buff, tempBuffSize);
			if(TRUE == wmx_checkBufferChange(sendBuff,
											(sizeof(ChannelInfoArray_tlv_type) * 32 + 4),
											buff, 
											size))
			{
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_SCAN_CONFIG, (UINT16)tempBuffSize);
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
	}
	if(buff)
	{
		free(buff);
	}
	return status;
}

//Recent Discovered Channels - array of BSID, NAPID, Freq 
//[in] pDiscoveredNap_t pNapInfo - a list of channels per Nap that where discovered during the scan
//[in] wmx_pBSid_t pBsID - the BsID received with the Nap
wmx_Status_t wmx_PopulateMonitorRecentDiscoverNap(pDiscoveredNap_t pNapInfo, wmx_pBSid_t pBsID)
{
	UINT8 *tempBuff = NULL;
	int bittOff = 0;
	UINT tempBuffSize = 0;
	UINT32 i = 0;
	UINT8 *buff = NULL;
	static UINT8 savedBuff[(sizeof(DiscoveredNap_t) + sizeof(wmx_BSid_t)) * 3];
	static size_t elementToChange = 0;
	BMS_NapMember *pNapId = NULL;
	BMS_ChannelMember *pChannelInfo = NULL;
	UINT32 size = 0;
	wmx_Status_t status = WMX_ST_OK;

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_RECENT_DISCOVER_NAP))
	{
		
		if(NULL == pNapInfo || NULL == pBsID)
		{
			return WMX_ST_FAIL;
		}
		size = sizeof(DiscoveredNap_t) + sizeof(wmx_BSid_t);
		buff = (UINT8 *)malloc(size);
		if(buff)
		{
			memset(buff, '\0', size);

			BM_MonitorRecentDiscoverNap_ChannelInfoArray_NumOfChannels_SET(buff, pNapInfo->channelPlan.channelsSize);
			for(i=0; i<pNapInfo->channelPlan.channelsSize; i++)
			{
				if(NULL == &(pNapInfo->channelPlan.channels[i]))
				{					
					free(buff);
					return WMX_ST_FAIL;
				}
				BM_MonitorRecentDiscoverNap_ChannelInfoArray_Channels_GET_ELEMENT_POS(buff, i, pChannelInfo, bittOff);
				pChannelInfo->_bw = pNapInfo->channelPlan.channels[i].bw;
				pChannelInfo->_fft = pNapInfo->channelPlan.channels[i].fft;
				pChannelInfo->_frequency = pNapInfo->channelPlan.channels[i].firstFreq; //the frequency will get the first one only
				memcpy(pChannelInfo->_Preambles._Preambles,pNapInfo->channelPlan.channels[i].preambleBitmap,BM_MAX_PREAMBLE_SIZE);
			}		
		
			BM_MonitorRecentDiscoverNap_NapMember_napID_GET_POS(buff, pNapId, bittOff);
			memcpy(pNapId->_napID, pNapInfo->napID, BM_MonitorRecentDiscoverNap_NapMember_napID_BYTES_SIZE);

			BM_MonitorRecentDiscoverNap_bsID_GET_POS(buff, tempBuff, bittOff);
			memcpy(tempBuff, pBsID, BM_MonitorRecentDiscoverNap_bsID_BYTES_SIZE );

			BM_MonitorRecentDiscoverNap_GET_BYTES_SIZE(buff, tempBuffSize);

			if(TRUE == wmx_checkMultyBufferChange(savedBuff,
												  3,
												  (sizeof(DiscoveredNap_t) + sizeof(wmx_BSid_t)),
												  &elementToChange,
												  buff,
												  size))
			{
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_RECENT_DISCOVER_NAP, (UINT16)tempBuffSize);
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
	}
	if(buff)
	{
		free(buff);
	}
	return status;
}

//the channel that we WILL use for successful connect in a few sec - can be more then 1from 2 different NAP
//[in] wmx_pChannelInfo_t chPlan - the channel plan was selected
//[in] UINT numChannels - number of plans
wmx_Status_t wmx_PopulateMonitorSelectedChannel(wmx_pChannelInfo_t chPlan, UINT numChannels)
{
	int bittOff = 0;
	UINT tempBuffSize = 0;
	UINT32 i = 0;
	UINT8 *buff = NULL;
	static UINT8 sendBuff[sizeof(wmx_ChannelInfo_t) * WMX_CHANNELS_MAX_NUM + 4];
	BMS_ChannelMember *pChannelInfo = NULL;
	UINT32 size = 0;
	wmx_Status_t status = WMX_ST_OK;

	if(L4DnDHndlr_IsMonFiltered(L3L4_TLV_TYPE_MONITOR_SELECTED_CHANNEL))
	{
		if(NULL == chPlan)
		{
			return WMX_ST_FAIL;
		}
		size = sizeof(wmx_ChannelInfo_t) * numChannels + 4;
		buff = (UINT8 *)malloc(size);
		if(buff)
		{
			memset(buff,'\0',size);

			BM_MonitorSelectedChannel_ChannelInfoArray_NumOfChannels_SET(buff,numChannels);
			for(i=0 ; i<numChannels ;i++ )
			{
				if(NULL == &(chPlan[i]))
				{
					free(buff);
					return WMX_ST_FAIL;
				}
				BM_MonitorSelectedChannel_ChannelInfoArray_Channels_GET_ELEMENT_POS(buff,i,pChannelInfo,bittOff);
				wmx_populateChannel(pChannelInfo,&(chPlan[i]));
			}
			BM_MonitorSelectedChannel_GET_BYTES_SIZE(buff, tempBuffSize);
			if(TRUE == wmx_checkBufferChange(sendBuff,
											 (sizeof(wmx_ChannelInfo_t) * WMX_CHANNELS_MAX_NUM + 4),
											 buff,
											 size))
			{
				L4DnDHndlr_PostMon(buff, L3L4_TLV_TYPE_MONITOR_SELECTED_CHANNEL, (UINT16)tempBuffSize);
			}
		}
		else
		{
			status = WMX_ST_NO_ROOM_FOR_INDICATION;
		}
	}
	
	if(buff)
	{
		free(buff);
	}
	return status;
}

void PopulateMonitorXmlData()
{
	wmx_Status_t monitorStatus = WMX_ST_OK;

	monitorStatus = wmx_PopulateMonitorOMAParams();
	if(WMX_ST_OK != monitorStatus)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "wmx_PopulateMonitorOMAParams was not able to send the message return status = %d",monitorStatus);
	}

	monitorStatus = wmx_PopulateMonitorOMAFumoParams();
	if(WMX_ST_OK != monitorStatus)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "wmx_PopulateMonitorOMAFumoParams was not able to send the message return status = %d",monitorStatus);
	}
		
	monitorStatus = wmx_PopulateMonitorOMAWimaxParams();
	if(WMX_ST_OK != monitorStatus)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "wmx_PopulateMonitorOMAWimaxParams was not able to send the message return status = %d",monitorStatus);
	}
	
	monitorStatus = wmx_PopulateMonitorOperator();
	if(WMX_ST_OK != monitorStatus)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "wmx_PopulateMonitorOperator was not able to send the message return status = %d",monitorStatus);
	}
	wmx_PopulateMonitorInstallingInd(INIT_VALUE);
}