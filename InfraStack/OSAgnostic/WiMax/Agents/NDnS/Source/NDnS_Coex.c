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
#include "wmxSDK_Coex_1.h"
#include "wimax_osal_config_controler.h"
#include "WrappersCommon.h"
#include "L4ConfigurationManager.h"
#include "TraceModule.h"
#include "IndicatorsSubscribers.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Coex_1.h"
#include "NDnSAgent_Internals.h"
#include "L5OpCodes.h"		
#include "Messenger.h"
#include "NDnSAgent.h"
#include "wmxSDK_Nds_3.h"
#include "NDnS_Coex.h"

void NDnSAgent_CoexistenceUpdate( wmx_CoexistenceMode_t coexMode );


wmx_Status_t GetCoexistenceMode(void *buffer, UINT32 *bufferSize)
{
	BOOL regData;
	char data[10];
	wmx_pCoexistenceMode_t pCoexMode = buffer;

	if ( *bufferSize >= sizeof(wmx_CoexistenceMode_t) )
	{
		//read data from registry
		regData = L4Configurations_getCoexistingMode(data);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Trying to read registry value of COEX MODE");
		/*if (!regData)
		return WMX_ST_FAIL;*/
		*bufferSize = sizeof(wmx_CoexistenceMode_t);

		if (regData)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Suceeded to read coex mode key from registry");
			*pCoexMode = (OSAL_stricmp(data,"CM")==0)?WMX_MODE_CM:WMX_MODE_XOR;
		}
		else 
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Failed to read coex mode key from registry");
			*pCoexMode = WMX_MODE_XOR;
		}

		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}

wmx_Status_t SetCoexistanceMode(void *buffer, UINT32 bufferSize)
{
	wmx_Status_t retStatus;
	BOOL regData;
	wmx_CoexistenceMode_t CoexMode;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetCoexistanceMode User call set to false");
	if ( bufferSize >= sizeof(wmx_CoexistenceMode_t) )
	{
		CoexMode = (*(wmx_pCoexistenceMode_t)(buffer));
		//send coexistence mode to driver
		retStatus = wmx_SetCoexistenceMode(CoexMode);
		if (retStatus != WMX_ST_OK)
		{
			return retStatus;
		}

		//update coexsitence registry
		regData = OSAL_ConfigController_SetStrValue(OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COEXISTING_MODE, ((CoexMode) == WMX_MODE_XOR)?"XOR":"CM");
		if (!regData)
		{
			return WMX_ST_FAIL;
		}

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Coexistance mode set to - %s",(*(wmx_pCoexistenceMode_t)(buffer))==WMX_MODE_CM?"CM":"XOR");
		//send indication to subscribers
		NDnSAgent_CoexistenceUpdate(*(wmx_pCoexistenceMode_t)(buffer));
		return WMX_ST_OK;
	}

	return WMX_ST_FAIL;
}


void NDnSAgent_CoexHandlingThreadFunc( LPVOID lpParameter )
{
	BOOL res;
	UINT32 answerVal = 0;
	wmx_CoexistenceMode_t coexMode = WMX_MODE_XOR;
	//UINT32 msgLength = sizeof(wmx_CoexistenceMode_t);

	UNREFERENCED_PARAMETER(lpParameter);

	res = L4Configurations_getFALL_TO_XOR_TIMEOUT(&answerVal);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_CoexHandlingThreadFunc Started with value %d",answerVal);
	if (!res)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_CoexHandlingThreadFunc Started with value %d because no regitry could be read",answerVal);
		answerVal = 0;
	}
	// if parameter == 0 then we do not fall to xor ever
	if (answerVal != 0){
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_CoexHandlingThreadFunc Started with value different from 0");
		OSAL_sleep(answerVal*1000);
		wmx_InternalRfOff();

		UserCall = TRUE;
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "NDnSAgent_CoexHandlingThreadFunc User call set to true");
		wmx_SetCoexistenceMode(coexMode);
	}

	return;
}


// Used to receive coexistence update event
void NDnSAgent_CoexistenceUpdate( wmx_CoexistenceMode_t coexMode )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Coexistence mode update callback called");

	msgSize = sizeof(NDNS_MESSAGE) + sizeof(wmx_CoexistenceMode_t);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_COEX_UPDATE;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_COEX_UPDATE;
	pIndMsg->bufferLength = sizeof(wmx_CoexistenceMode_t);
	*(wmx_pUserScanStatus_t)pIndMsg->buf = coexMode;

	nds_wrapper_UtilFuncs->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}

void NDnSAgent_RfTakenIndication( void )
{
	UINT32 msgSize;
	UINT32 sendIndDataSize;
	SendIndData *pSendIndData;
	NDNS_MESSAGE *pIndMsg;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "RF taken indication callback called");

	msgSize = sizeof(NDNS_MESSAGE);
	sendIndDataSize = sizeof(SendIndData) + msgSize;
	pSendIndData = (SendIndData *)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL, "malloc failed");
		return;
	}

	pIndMsg = (NDNS_MESSAGE *)(pSendIndData->indication_buffer);

	pSendIndData->pSenderFuncs = nds_pFuncs;
	pSendIndData->senderL5Conn = nds_l5ConnID;
	pSendIndData->pSubscribersList = g_ndnsContext.indicatorSubscribersList;
	pSendIndData->indication_id = NDNS_OPCODE_IND_RF_TAKEN;
	pSendIndData->indication_buffer_size = msgSize;
	pIndMsg->opcode = NDNS_OPCODE_IND_RF_TAKEN;
	pIndMsg->bufferLength = 0;
	;

	nds_wrapper_UtilFuncs->tpfnPostRequest(
		MEDIUM, NDNS_OPCODE_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	free(pSendIndData);
}
