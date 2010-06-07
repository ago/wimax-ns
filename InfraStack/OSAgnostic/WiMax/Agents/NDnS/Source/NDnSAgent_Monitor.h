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
#ifndef _NDNS_AGENT_MONITOR_H
#define _NDNS_AGENT_MONITOR_H

#include "wimax_osal_types.h"
#include "L4MonitorGroups.h"
#include "BitmanCommon.h"
#include "L4DmMonitorGroups.h"
#include "L4BufMan_L3L4Structs_Desc.h"

#include "L4DnDHandler.h"
#include "NDnSAgent_DB_Internal.h"
#include "wmxSDK_Sup_4.h"

#define TEMP_MAX_CHANNEL_NUM 128

//inner function that check if the buffer was change (TRUE) else (FALSE)
BOOL wmx_checkBufferChange(void *pOriginalBuff, size_t originalSize, void *pNewBuff, size_t newSize);

//inner function replace specific element in an elements buffer if not found in one of them
BOOL wmx_checkMultyBufferChange(UINT8 *pOriginalBuff,
								const size_t originalNumOfElements,
								const size_t originalBuffElemSize,
								size_t *pElementToChange,
								UINT8 *pNewBuff, 
								const size_t newBuffSize);

//inner function that get pointer to a BMS_ChannelMember in the buff and populate its values
void wmx_populateChannel(BMS_ChannelMember *pChannelInfo, wmx_pChannelInfo_t channelData);

//--------MonitorScanInd--------
//send to the monitor the scan indication includes the start (as 1)or the end (as 2)indication + the time
void wmx_MonitorScanInd(BM_StartEndInd startEndInd);



//check if we populated already the XML data or not if not verify if this data is monitor.
// after the data was populated with success this data will not be send again
void PopulateMonitorXmlData();

//----------MonitorOperator--------
//populate the Rapl struct from the DB global variable for the MonitorOperator TLV
void wmx_PopulateRapllMonitor(pRapl_t pRapl, UINT8 *buff);
//populate the Capl struct from the DB global variable for the MonitorOperator TLV
void wmx_PopulateCapllMonitor(pCapl_t pCapl, UINT8 *buff);
//populate the Eap struct from the DB global variable for the MonitorOperator TLV
void wmx_PopulateEapMonitor(pEAP_t EAP, UINT8 *buff, int counter);
//send the operator information stored in the DB
wmx_Status_t wmx_PopulateMonitorOperator();

//populate the FUMO parameters from the DB
wmx_Status_t wmx_PopulateMonitorOMAFumoParams();

//--------------MonitorOMAWimaxParams----------
//populate the Radio parameters (belongs to the WimaxParam) from the DB
void wmx_PopulateRadioModulesMonitor(UINT8 *buff,pWimax_t pWimaxParams);
//populate the TermEquip parameters(belongs to the WimaxParam) from the DB
void wmx_PopulateTermEquipMonitor(UINT8 *buff,pTerminalEquipment_t TerminalEquipment);
//populate the WimaxParam from the DB
wmx_Status_t wmx_PopulateMonitorOMAWimaxParams();

//-----------MonitorOMAParams------------------
//populate the DeviceInfo parameters from the DB
wmx_Status_t wmx_PopulateDeviceInfoMonitor(UINT8 *buff);
//populate the DeviceDetails parameters from the DB
wmx_Status_t wmx_PopulateDeviceDetailsMonitor(UINT8 *buff);
//populate the OMA parameters from the DB
wmx_Status_t wmx_PopulateMonitorOMAParams();


//--------MonitorNAI-----------
//send the full NAI to the monitor
void wmx_PopulateNAIMonitor(wmx_pNAI_t identity);

//--------MonitorOMASession-------------
//When receiving during bootstrap or regular, includes details of the enum reporting the specific action: OMA-DM Session start or end, Bootstrap start/end, etc.
//the same indication is being send also in case we start polling
void wmx_PopulateOMASessionMonitor(wmx_ApdoSessionStatus_t sessionStatus);


//---------MonitorActivationStatusChange------------
//Indicate new status for the current operator 
void wmx_PopulateActivationStatusChangeMonitor(BOOL *ActivationStatus);

//-----------MonitorMCP---------------
//send the channels belong to the MCP
wmx_Status_t wmx_PopulateMonitorMCP(wmx_pChannelInfo_t pMcp, UINT32 numChannels, wmx_LinkLossType_t linkLossType);

//--------------MonitorInstallationInd--------------
//send indication when SW Upgrade starts, when user authorizes SW upgrade
void wmx_PopulateMonitorInstallingInd(UINT32 currentMonitorInstallingInd);

//--------------MoniterScanConfig-------------------
//Display the scan parameters (the chunk of Master Channel Plan) being set to L3
wmx_Status_t wmx_PopulateMoniterScanConfig(ChannelInfoArray_tlv_type *pChannelInfo, UINT32 numOfChannelInfos);

//---------------MonitorRecentDiscoverNap-----------
//Recent Discovered Channels - array of BSID, NAPID, Freq
wmx_Status_t wmx_PopulateMonitorRecentDiscoverNap(pDiscoveredNap_t pNnapInfo, wmx_pBSid_t bsID);

//------------------MonitorSelectedChannel-----------
//the channel that we WILL use for successful connect in a few sec - can be more then 1from 2 different NAP
wmx_Status_t wmx_PopulateMonitorSelectedChannel(wmx_pChannelInfo_t chPlan,UINT numChannels);


void wmx_MonitorSendScanResults(wmx_pScanResults_t scanResults, wmx_pNSP_t pNSPs, UINT32 numOfNSPs);

#endif // _NDNS_AGENT_MONITOR_H