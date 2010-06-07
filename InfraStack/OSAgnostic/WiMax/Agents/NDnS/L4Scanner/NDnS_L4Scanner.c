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
#include "NDnS_L4Scanner.h"
#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Sup_4.h"
#include "NDnSAgent.h"
#include "NDnS_L4Publisher.h"
#include "NDnSAgent_Utils.h"
#include "NDnSAgent_DB_Internal.h"

extern tUtilityFunctions *pUtils;

// globals
L4ScannerContext_t g_l4ScannerContext; // isInitialized initial value will be FALSE (global)

//This is the sequence number of the last L4S_StartScannerInternal message that was posted to the messenger.
//In case it is a non zero value, it means that there is a pending message on the messenger queue that
//should be removed on SCAN RESET 
static size_t  g_SeqNum; //0 indicates an invalid seqNum

wmx_Status_t L4S_DiscoverInternal();
void WMX_EXT_CALL_CONV HandleSystemState(wmx_pSystemStateUpdate systemStateUpdate);
wmx_Status_t L4S_StartScannerInternal(UINT32 internalRequestID, void *buffer, UINT32 bufferLength);
BOOL L4S_IsReady();

//////////////////////
// Move to ND&S common tools
void CopyChannelInfo(wmx_pChannelInfo_t source, wmx_pChannelInfo_t target)
{
	OSAL_memcpy_s(target, sizeof(wmx_ChannelInfo_t), source, sizeof(wmx_ChannelInfo_t));		
}
//////////////////////

void L4S_ThreadProc(LPVOID lpParam)
{
	UINT32 eventWaitRes;
	OSAL_event_t events[2];

	UNREFERENCED_PARAMETER(lpParam);	

	events[0] = g_l4ScannerContext.hShutdownEvent;
	events[1] = g_l4ScannerContext.hTimerEvent;

	while(TRUE)
	{
		eventWaitRes = OSAL_multiple_wait_event(2, events, FALSE, g_l4ScannerContext.waitTimeout);
		switch(eventWaitRes)
		{						
		case WAIT_OBJECT_0: // shutdown
			return;
			//break;
		case (WAIT_OBJECT_0 + 1): // start timer or reset
			if ((INFINITE == g_l4ScannerContext.waitTimeout) &&
				(TRUE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isTimerStarted, FALSE, TRUE)))
			{	// reset
				g_l4ScannerContext.waitTimeout = INFINITE; // disable the thread
				L4S_SetScannerState(L4S_READY);

				if (TRUE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isResetRequested, FALSE, TRUE))
				{		
					g_l4ScannerContext.currentChunk = 0;
					g_l4ScannerContext.nextChannelToScan = 0;
					g_l4ScannerContext.isSingleScan = FALSE;
				}
			}
			OSAL_set_event(g_l4ScannerContext.hScannerResetCompleteEvent);
			break;
		case WAIT_TIMEOUT:
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Auto scan thread: issue scan request");
			//AgeAvailableNspsList();
			OSAL_atomic_exchange(&g_l4ScannerContext.isTimerStarted, FALSE);
			g_l4ScannerContext.waitTimeout = INFINITE; // disable the thread
			g_SeqNum = pUtils->tpfnPostRequest(MEDIUM, 0, NULL, 0, &L4S_StartScannerInternal); // start another scan cycle
			break;
		case WAIT_FAILED:
		case WAIT_ABANDONED_0:
		case (WAIT_ABANDONED_0 + 1):
		default:
			break;
		}
	}

	return;
}


wmx_Status_t L4S_Init()
{		
	FSM_Init(&g_l4ScannerContext.fsm);
	FSM_SetState(&g_l4ScannerContext.fsm, L4S_READY); // Move to Ready state
	L4S_Reset(FALSE);

	g_l4ScannerContext.isEnabled = TRUE;
	g_l4ScannerContext.isDeviceAligned = FALSE;
	g_l4ScannerContext.isSingleScan = FALSE;
	g_l4ScannerContext.divided = FALSE;

	if (0 != OSAL_create_event(&g_l4ScannerContext.hTimerEvent, FALSE, FALSE, NULL)) // Auto reset
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Initialize Failed: Creation of L4Scanner timer event - Failed!");		
		return L5_RESULT_CREATE_EVENT_FAILED;
	}

	if (0 != OSAL_create_event(&g_l4ScannerContext.hShutdownEvent, FALSE, FALSE, NULL)) // Auto reset
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Initialize Failed: Creation of L4Scanner timer event - Failed!");		
		L4S_Finalize();
		return L5_RESULT_CREATE_EVENT_FAILED;
	}

	if (0 != OSAL_create_event(&g_l4ScannerContext.hScannerResetCompleteEvent, FALSE, FALSE, NULL)) // Auto reset
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Initialize Failed: Creation of L4Scanner timer event - Failed!");		
		L4S_Finalize();
		return L5_RESULT_CREATE_EVENT_FAILED;
	}


	// this field will contain a real value after a scan cycle is complete
	g_l4ScannerContext.waitTimeout = INFINITE;

	if( 0 != OSAL_create_thread(L4S_ThreadProc, NULL, &g_l4ScannerContext.hTimerThread ) )
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Initialize Failed: Creation of L4Scanner timer thread - Failed!");		
		L4S_Finalize();
		return L5_RESULT_CREATE_EVENT_FAILED;
	}

	return WMX_ST_OK;
}

void L4S_Finalize()
{
	// TODO: Oran - add OSAL_atomic_exchange

	OSAL_set_event(g_l4ScannerContext.hShutdownEvent);

	if (g_l4ScannerContext.hTimerThread != NULL)
	{
		if ( OSAL_timedjoin_thread(g_l4ScannerContext.hTimerThread, SHUTDOWN_TIMEOUT, NULL) != 0)
			OSAL_kill_thread(g_l4ScannerContext.hTimerThread);
		g_l4ScannerContext.hTimerThread = NULL;
	}

	if (g_l4ScannerContext.hScannerResetCompleteEvent != NULL)
	{
		OSAL_delete_event(g_l4ScannerContext.hScannerResetCompleteEvent);
		g_l4ScannerContext.hScannerResetCompleteEvent = NULL;
	}

	if (g_l4ScannerContext.hShutdownEvent != NULL)
	{
		OSAL_delete_event(g_l4ScannerContext.hShutdownEvent);
		g_l4ScannerContext.hShutdownEvent = NULL;
	}

	if (g_l4ScannerContext.hTimerEvent != NULL)
	{
		OSAL_delete_event(g_l4ScannerContext.hTimerEvent);
		g_l4ScannerContext.hTimerEvent = NULL;
	}
	FSM_Finalize(&g_l4ScannerContext.fsm);
}

wmx_Status_t L4S_Reset(BOOL hardReset)
{	
	wmx_Status_t status = WMX_ST_OK;

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4S_Reset(IN). hardReset = %d", hardReset);				
	if (L4S_GetScannerState() != L4S_READY)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4S_Reset- L4S_GetScannerState() != L4S_READY");				
		wmx_UnregisterSystemStateUpdateCB(&HandleSystemState);
		OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, TRUE);
		g_l4ScannerContext.waitTimeout = INFINITE;

		//Resetting auto event - 
		//close the "gate" before the reset starts 
		//to make sure we'll wait for the reset to complete 
		OSAL_reset_event(g_l4ScannerContext.hScannerResetCompleteEvent); 
		OSAL_set_event(g_l4ScannerContext.hTimerEvent); // reset auto-retry thread

		// the reset command is now asynchronous. We check that the state has transitioned to Ready
		// when a new scanner command (like StartScanner) is requested.
		L4S_StopScanner();

		if (hardReset)
		{
			//3000 ms is arbitrary. We're signaling the the reset event two lines above 
			//so this wait should be very short
			if (OSAL_wait_event(g_l4ScannerContext.hScannerResetCompleteEvent, 3000) == WAIT_TIMEOUT)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "TimeOut on waiting to hScannerResetCompleteEvent");				
			}

			//Try to pop out the message, seqNum 0 is ignored
			if (pUtils->tpfnPopRequest(g_SeqNum) == FALSE)
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Unable to pop Message. Message id '%d' wasn't found in queue", g_SeqNum);
			}

			g_SeqNum = 0;

			L4S_SetScannerState(L4S_READY);
			OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
		}
	}
	else // no need to wait. reset now.
	{
		OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
		g_l4ScannerContext.waitTimeout = INFINITE;
		g_l4ScannerContext.currentChunk = 0;
		g_l4ScannerContext.nextChannelToScan = 0;
		g_l4ScannerContext.isSingleScan = FALSE;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4S_Reset(OUT). status = %d", status);				
	return status;
}

void L4S_EnableScanner(BOOL isEnabled)
{
	OSAL_atomic_exchange(&g_l4ScannerContext.isEnabled, (LONG)isEnabled);
}

BOOL L4S_IsReady()
{
	BOOL isReady = TRUE;

	if (TRUE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isResetRequested, TRUE, TRUE))
	{	// reset requested so we have to wait for the reset to end
		if (!FSM_WaitForState(&g_l4ScannerContext.fsm, L4S_READY, L4S_TIMEOUT))
		{	// it's taking too long to get to ready state...
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_WARNING, "Waiting for scanner reset failed. scannerState = %d",g_l4ScannerContext.fsm.state);			
			isReady = FALSE;
		}
	}
	else
	{
		isReady = (L4S_GetScannerState() == L4S_READY);
	}

	return isReady;
}

BOOL L4S_IsScanning()
{
	BOOL isScanning = FALSE;

	switch(L4S_GetScannerState())
	{
	case L4S_SCANNING:
	case L4S_DISCOVER:
	case L4S_DISCONNECT:
		isScanning = TRUE;
		break;
	}

	return isScanning;
}


BOOL L4S_IsResetRequested()
{
	if (TRUE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isResetRequested, FALSE, TRUE))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Scanner reset requested. Scan stopped.");
		//Nardimon
		// If connect command was recieved when in scanning we reset ands start from the begining thus we neeed to age the list.
		//AgeAvailableNspsList();
		L4S_SetScannerState(L4S_READY);
		OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
		g_l4ScannerContext.waitTimeout = INFINITE;
		g_l4ScannerContext.currentChunk = 0;
		g_l4ScannerContext.nextChannelToScan = 0;
		return TRUE;
	}
	return FALSE;
}

// get the current state of the scanner
ScannerState L4S_GetScannerState()
{
	return (ScannerState)FSM_GetState(&g_l4ScannerContext.fsm);
}

// set the scanner to a new state
void L4S_SetScannerState(ScannerState state)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4 Scanner: SetState = %s", ScannerStateStr[state]);
	FSM_SetState(&g_l4ScannerContext.fsm, state);
}

// set the scanner to a new state ONLY if its current state is equal to the source state parameter
BOOL L4S_SetScannerStateIfEqual(ScannerState sourceState, ScannerState targetState)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4 Scanner: SetStateIfEqual - source = %s, target = %s", ScannerStateStr[sourceState], ScannerStateStr[targetState]);
	return FSM_SetStateIfEqual(&g_l4ScannerContext.fsm, sourceState, targetState);
}

// set the scanner to a new state ONLY if its current state is NOT equal to the source state parameter
BOOL L4S_SetScannerStateIfNotEqual(ScannerState sourceState, ScannerState targetState)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4 Scanner: SetStateIfNotEqual - source = %s, target = %s", ScannerStateStr[sourceState], ScannerStateStr[targetState]);
	return FSM_SetStateIfNotEqual(&g_l4ScannerContext.fsm, sourceState, targetState);	
}

// wait until a certain state is reached
BOOL L4S_WaitForState(int state, UINT32 timeout)
{
	return FSM_WaitForState(&g_l4ScannerContext.fsm, state, timeout);
}

// wait until one of the specified states is reached
BOOL L4S_WaitForMultipleStates(int* states, int statesCount, UINT32 timeout)
{
	return FSM_WaitForMultipleStates(&g_l4ScannerContext.fsm, states, statesCount, timeout);
}

wmx_ChannelID_t L4S_GetFirstChannelWithFullPreambles()
{
	UINT32 i, k;

	for (i = 0; i < g_l4ScannerContext.numChannels; i++)
	{
		for (k = 0; k < PREAMBLES_LENGTH; k++)
		{
			if (g_l4ScannerContext.mcp[i].preambleBitmap[k] != 0xFF)
			{
				break;
			}
		}

		if (k == PREAMBLES_LENGTH) // this is a channel with full preambles
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "FirstChannel: found full channel at index = %d", i);
			break;
		}
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "FirstChannel: num channels = %d, firstChannel index = %d",  g_l4ScannerContext.numChannels, i);
	// in case there aren't any channels with full preambles - return 0 since all the channels are of the same type
	return (i == g_l4ScannerContext.numChannels) ? 0 : (wmx_ChannelID_t)i;
}

wmx_Status_t L4S_SetDiscreteCfg(wmx_ChannelInfo_t mcp[], UINT32 numChannels, int numOfRetries, int retryInterval, wmx_CoexPriority_t coexPriority, wmx_ScanPolicy_t policy, BOOL delayStart)
{
	UINT16 i;

	if (!L4S_IsReady())
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4Scanner: Unable to set configuration. Scanner is not ready");		
		return WMX_ST_WRONG_STATE;
	}

	if (numChannels > MAX_CHANNELS_NUM) // too much channels
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4Scanner: Unable to set configuration. Too much channels. Ch num = %d, Max allowed = %d", numChannels, MAX_CHANNELS_NUM);
		return WMX_ST_WRONG_ARGUMENT;
	}

	// reset the pointers to the last chunk that was configured to L3
	g_l4ScannerContext.setChPlanStart = g_l4ScannerContext.setChPlanEnd = 0;
	g_l4ScannerContext.isDeviceAligned = FALSE;

	for (i = 0; i < numChannels; i++)
	{		
		CopyChannelInfo(&mcp[i], &(g_l4ScannerContext.mcp[i]));
		// add the channelId so we will be able to identify it once we get the results back
		g_l4ScannerContext.mcp[i].channelID = i;
	}

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "----> L4S_SetDiscreteCfg: Setting num of channels. Previous: %d, Next: %d", 
		g_l4ScannerContext.numChannels, numChannels);
	g_l4ScannerContext.numChannels = numChannels;

	// calculate the number of the chunks
	g_l4ScannerContext.numChunks =	(g_l4ScannerContext.numChannels % CHUNK_SIZE == 0) ?
		(g_l4ScannerContext.numChannels / CHUNK_SIZE) :
	(g_l4ScannerContext.numChannels / CHUNK_SIZE + 1);

	if (delayStart) // scan will NOT start immediately
	{
		g_l4ScannerContext.currentChunk = g_l4ScannerContext.numChunks;
		g_l4ScannerContext.numOfRetries = ++numOfRetries;
	}
	else // scan will start immediately							
	{
		g_l4ScannerContext.currentChunk = 0;
		g_l4ScannerContext.nextChannelToScan = 0;
		g_l4ScannerContext.firstFullChannel = L4S_GetFirstChannelWithFullPreambles();
		g_l4ScannerContext.numOfRetries = numOfRetries;
	}
	g_l4ScannerContext.retryInterval = retryInterval;
	g_l4ScannerContext.coexPriority = coexPriority;	
	g_l4ScannerContext.scanPolicy = policy;

	return WMX_ST_OK;
}

// Set configuration for preferred scan
wmx_Status_t L4S_SetPSCfg(wmx_ChannelInfo_t mcp[], UINT32 numChannels, int numOfRetries, int retryInterval, wmx_ScanPolicy_t scanPolicy, wmx_CoexPriority_t coexPriority, BOOL delayStart)
{	
	g_l4ScannerContext.scanType = SCAN_TYPE_PREFERRED;
	return L4S_SetDiscreteCfg(mcp, numChannels, numOfRetries, retryInterval, coexPriority, scanPolicy, delayStart);
}

// Set configuration for while scan
wmx_Status_t L4S_SetWhileSCfg(wmx_ChannelInfo_t mcp[], UINT32 numChannels, int numOfRetries, int retryInterval, wmx_CoexPriority_t coexPriority, BOOL delayStart)
{
	g_l4ScannerContext.scanType = SCAN_TYPE_WIDE;
	// find all - while scan
	return L4S_SetDiscreteCfg(mcp, numChannels, numOfRetries, retryInterval, coexPriority, SCAN_MODE_FIND_ALL, delayStart);	
}

// call SetChannelPlan towards L3 with the channel plan from the input
// (the MCP is NOT changed !!!)
wmx_Status_t L4S_SendChannelPlanToDevice(wmx_ChannelInfo_t channelPlan[], UINT32 numChannels, wmx_ScanPolicy_t scanPolicy)
{
	wmx_Status_t status;

	// set the channel plan to L3 
	status = wmx_SetChannelPlan(numChannels, channelPlan, scanPolicy);
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error sending channel plan to the device.");				
	}
	else
	{
		g_l4ScannerContext.setChPlanStart = channelPlan;
		g_l4ScannerContext.setChPlanEnd = channelPlan + numChannels;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Channel Plan with %d channels sent to the device.", numChannels);

	return status;
}

BOOL L4S_CompareChannels(wmx_pChannelInfo_t ch1, wmx_pChannelInfo_t ch2)
{
	BOOL areIdentical = TRUE;
	int i;

	if ((ch1->bw != ch2->bw) ||
		(ch1->fft != ch2->fft) ||
		(ch1->frequency != ch2->frequency))
	{
		areIdentical = FALSE;
	}

	if (areIdentical)
	{
		for (i = 0; i < PREAMBLES_LENGTH; ++i)
		{
			if (ch1->preambleBitmap[i] != ch2->preambleBitmap[i])
			{
				areIdentical = FALSE;
				break;
			}
		}
	}

	return areIdentical;
}

BOOL L4S_AreChannelsInLastChunk(wmx_ChannelInfo_t channelPlan[], UINT32 numChannels)
{
	wmx_pChannelInfo_t ch;
	BOOL isChPlanOK = TRUE;
	UINT32 i;

	if (g_l4ScannerContext.isDeviceAligned)
	{
		for (i = 0; i < numChannels; ++i)
		{
			// iterate the last configured chunk and search for the input channels
			for (ch = g_l4ScannerContext.setChPlanStart; ch < g_l4ScannerContext.setChPlanEnd; ++ch)
			{
				if (L4S_CompareChannels(channelPlan + i, ch) == TRUE)
				{
					break;
				}
			}
			if (ch == g_l4ScannerContext.setChPlanEnd)
			{	// we didn't find the channel in the configured channel plan
				isChPlanOK = FALSE;
				break;
			}
		}
	}
	else
	{
		isChPlanOK = FALSE;
	}

	return isChPlanOK;
}

BOOL L4S_AreChunksLeft()
{
	return (g_l4ScannerContext.currentChunk < g_l4ScannerContext.numChunks);
}

void L4S_EndScanCycle()
{
	g_l4ScannerContext.currentChunk = g_l4ScannerContext.numChunks;
}

wmx_pChannelInfo_t L4S_GetChannelInfo(wmx_ChannelID_t chId)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "------> L4Scanner: g_l4ScannerContext.numChannels: %d", g_l4ScannerContext.numChannels);
	if (chId < g_l4ScannerContext.numChannels)
	{
		return &(g_l4ScannerContext.mcp[chId]);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "L4Scanner: got illegal channel ID in scan results. Discarding channel. ID: %d", chId);
		return NULL;
	}
}


wmx_Status_t L4S_ConvertPreambleIdToPreambleBitmap(UINT16 preambleId,
												   wmx_pChannelInfo_t chInfo)
{
	UINT32 byteLocation = 0;
	UINT32 bitLocation = 0;
	UINT8 tempByte = 0x00;
	int idx=0;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4S_ConvertPreambleIdToPreambleBitmap(IN)");
	if(preambleId > 113)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "ERROR: L4S_ConvertPreambleIdToPreambleBitmap - preambleId = %d", preambleId);
		return WMX_ST_FAIL;
	}

	// set all bits in the preamble bitmap to 0 and turn on only the needed bits
	memset(chInfo->preambleBitmap, 0x00, sizeof(chInfo->preambleBitmap));
	// finds the byte location by converting to Oct base, and the bit location inside the byte by using %8
	byteLocation = (preambleId >> 3);
	bitLocation = (preambleId % 8); 
	tempByte = 1;
	// turn on the temp bit and move it according to bitLocation
	//L3 sees bitmap LSB is lower preamble index and byte value is bigindian 
	chInfo->preambleBitmap[0 + (byteLocation )] = (UINT8)(tempByte << bitLocation);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4S_ConvertPreambleIdToPreambleBitmap : byteLocation - [%d] bitLocation - [%d]", byteLocation,bitLocation);
	for (idx=0; idx<15 ; idx++)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4S_ConvertPreambleIdToPreambleBitmap : chInfo->preambleBitmap[%d] - [%.2x]",idx, chInfo->preambleBitmap[idx]);
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4S_ConvertPreambleIdToPreambleBitmap(OUT)");
	return WMX_ST_OK;
}



wmx_Status_t L4S_ConvertChIdsToChPlan(wmx_NAP_t Nap, 
									  UINT32 chIdsCount, 
									  pChannelInfo_t chInfos, 
									  UINT32 *numOfChannelInfos)
{
	wmx_Status_t status = WMX_ST_FAIL;
	UINT32 i = 0, chNewCount = 0;
	wmx_pChannelInfo_t chInfo;


	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4S_ConvertChIdsToChPlan [IN]" );
	 
	if (chIdsCount > WMX_CHANNELS_MAX_NUM ||
		chInfos == NULL ||
		numOfChannelInfos == NULL)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}


	for (i = 0; i < chIdsCount && i < *numOfChannelInfos; ++i)
	{
		chInfo = L4S_GetChannelInfo(Nap.channelIdList[i]);
		if (chInfo != NULL)
		{	
			chInfos[chNewCount].firstFreq = chInfos[chNewCount].lastFreq = chInfo->frequency;
			chInfos[chNewCount].bw = chInfo->bw;
			chInfos[chNewCount].duplexMode = 0; // TODO: Oran - check
			chInfos[chNewCount].fft = chInfo->fft;
			OSAL_itoa_s(Nap.channelIdList[i], chInfos[chNewCount].id, MAX_REF_ID_NAME_SIZE, 10);
			chInfos[chNewCount].nextFreq = 1;
			status = L4S_ConvertPreambleIdToPreambleBitmap(Nap.preambleIdList[i], chInfo);
			// if L4S_ConvertPreambleIdToPreambleBitmap failed, change the preamble bitmap to full 
			if( WMX_ST_OK != status )
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4S_ConvertPreambleIdToPreambleBitmap failed - preambleId = %d", Nap.preambleIdList[i]);
				memset(chInfo->preambleBitmap, 0xff, sizeof(chInfo->preambleBitmap));
			}
			OSAL_memcpy_s(chInfos[chNewCount].preambleBitmap, sizeof(wmx_Preambles_t), chInfo->preambleBitmap, sizeof(wmx_Preambles_t));
			chInfos[chNewCount].tagName[0] = '\0';
			chInfos[chNewCount].ttl = L4DB_MAX_TTL;
			chInfos[chNewCount].lastFoundInNbrAdv = FALSE; // The value is TRUE only in Nbr advertisement
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4S_ConvertChIdsToChPlan : chInfos[chNewCount].firstFreq=[%d], chInfos[chNewCount].ttl = [%d]", chInfos[chNewCount].firstFreq, chInfos[chNewCount].ttl );
			++chNewCount;
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4S_ConvertChIdsToChPlan: illegal channel ID received. Unable to convert to real channel");
		}
	}

	*numOfChannelInfos = chNewCount;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4S_ConvertChIdsToChPlan [OUT]" );
	return status;
}


wmx_Status_t L4S_StartScannerInternal(UINT32 internalRequestID, void *buffer, UINT32 bufferLength)
{
	UINT16 chunkSize;	
	wmx_Status_t status;
	ScannerState scannerState = L4S_GetScannerState();

	UNREFERENCED_PARAMETER(internalRequestID);
	UNREFERENCED_PARAMETER(buffer);
	UNREFERENCED_PARAMETER(bufferLength);

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_StartScannerInternal(IN) isSingleScan=%d", g_l4ScannerContext.isSingleScan);

	if (FALSE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isEnabled, FALSE, FALSE))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_StartScannerInternal: Scanner is disabled. Scan request discarded");
		L4S_SetScannerStateIfNotEqual(L4S_READY, L4S_READY);
		return WMX_ST_OK;
	}

	// if we are already in a scanning state or standby (waking up from LL) - we can't enter it again
	if (scannerState != L4S_SCANNING && scannerState != L4S_STANDBY)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error starting scan. The scanner is already in a scanning state.");		
		return WMX_ST_WRONG_STATE;
	}
	L4S_SetScannerStateIfNotEqual(L4S_SCANNING, L4S_SCANNING);

	if (g_l4ScannerContext.numChannels < 1)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error starting scan. The configured channel plan is empty.");		
		status = WMX_ST_ILLEGAL_OPERATION;
		goto Finalize;
	}

	g_l4ScannerContext.waitTimeout = INFINITE; // disable the auto scan thread

	if (L4S_IsResetRequested())
	{
		status = WMX_ST_OK;
		goto Finalize;
	}

	/// Nardimon g_l4ScannerContext.numChunks
	// calculate the number of the chunks
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "-----------> L4S_StartScannerInternal : Checking g_l4ScannerContext.currentChunk == [%d]<-----------------",g_l4ScannerContext.currentChunk);		
	if (g_l4ScannerContext.currentChunk == 0)
	{		
		if (!g_l4ScannerContext.divided)
		{
			AgeAvailableNspsList();
			ResetNAPsBeneathThreshold();
		}
		
		//maybe add AgeAvailableNspsList(); here for all flows.
		g_l4ScannerContext.numChunks =	(g_l4ScannerContext.numChannels % CHUNK_SIZE == 0) ?
			(g_l4ScannerContext.numChannels / CHUNK_SIZE) :
		(g_l4ScannerContext.numChannels / CHUNK_SIZE + 1);
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "-----------> L4S_StartScannerInternal : Setting  g_l4ScannerContext.numChunks == [%d]",g_l4ScannerContext.numChunks);		
	}		


	if (g_l4ScannerContext.currentChunk < g_l4ScannerContext.numChunks)
	{
		wmx_ChannelID_t startCh, startChNextChunk;
		BOOL isTruncated = FALSE;

		// compute the size of the current chunk
		if (g_l4ScannerContext.currentChunk == g_l4ScannerContext.numChunks - 1) // this is the last chunk
		{
			chunkSize = (UINT16)(g_l4ScannerContext.numChannels - g_l4ScannerContext.nextChannelToScan);
		}
		else // not the last chunk
		{
			// Full chunk unless resume scan was done in the middle of a chunk
			//chunkSize = (UINT16)((g_l4ScannerContext.currentChunk + 1) * CHUNK_SIZE - g_l4ScannerContext.nextChannelToScan);
			chunkSize = CHUNK_SIZE;
			if ( (g_l4ScannerContext.nextChannelToScan % CHUNK_SIZE) != 0 )
			{
				chunkSize = CHUNK_SIZE - (g_l4ScannerContext.nextChannelToScan % CHUNK_SIZE);
			}
			if (g_l4ScannerContext.divided)
			{
				chunkSize = (UINT16)g_l4ScannerContext.currentChunkSize;
			}
		}	

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "FirstChannel: Chunk size = %d", chunkSize);


		startCh = g_l4ScannerContext.nextChannelToScan;
		startChNextChunk = g_l4ScannerContext.nextChannelToScan + chunkSize;

		// in case the current chunk contains both channels with partial preambles and with full preambles
		if (g_l4ScannerContext.firstFullChannel > startCh && g_l4ScannerContext.firstFullChannel < startChNextChunk)
		{
			// truncate the chunk (exclude the channels with full preambles)
			chunkSize = g_l4ScannerContext.firstFullChannel - g_l4ScannerContext.nextChannelToScan;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "----------------------------------> g_l4ScannerContext.numChunks++ %d", g_l4ScannerContext.numChunks);
			g_l4ScannerContext.numChunks++;
			isTruncated = TRUE;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "FirstChannel: Truncated chunk. New chunk size = %d", chunkSize);
		}
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Sending channel plan of chunk %d/%d to device. Total channels = %d", g_l4ScannerContext.currentChunk + 1, g_l4ScannerContext.numChunks, chunkSize);

		g_l4ScannerContext.currentChunkSize = chunkSize;
		// set the channel plan for the current chunk to L3 
		status = L4S_SendChannelPlanToDevice(g_l4ScannerContext.mcp + (int)g_l4ScannerContext.nextChannelToScan, chunkSize, g_l4ScannerContext.scanPolicy);
		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Error sending channel plan to the device");
			goto Finalize;		
		}
		else
		{
			// we've just reseted the context DB of L3 and until we send the scan command the device is not aligned
			g_l4ScannerContext.isDeviceAligned = FALSE;
		}
		g_l4ScannerContext.nextChannelToScan = g_l4ScannerContext.nextChannelToScan + chunkSize;
		if (!isTruncated)
		{

			//TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"----------------------------------> g_l4ScannerContext.currentChunk++ %d", g_l4ScannerContext.currentChunk);
			//g_l4ScannerContext.currentChunk++; // move to the next chunk


			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "FirstChannel: Moving to next chunk no. %d", g_l4ScannerContext.currentChunk);
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "FirstChannel: Truncated chunk. staying at chunk no. %d", g_l4ScannerContext.currentChunk);
		}

		if( TRUE == g_ndnsContext.isSupplicantStarted )
		{
			status = wmx_EnableSupplicant(FALSE); // disable the Supplicant
			if ( WMX_ST_OK != status )
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ALERT, "Could not disable the supplicant. Scan aborted !");
				status = WMX_ST_FAIL; // error
				goto Finalize;
			}
		}

		if (L4S_IsResetRequested())
		{			
			status = WMX_ST_OK;
			goto Finalize;
		}

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Starting to scan...");

		if (L4C_GetInitialCoexMode() == WMX_MODE_CM)
		{
			// Send process start only when the process is scanning. For connect process, L4C will do
			// it itself
			if (NDnSAgent_CoexPrio2CoexState(g_l4ScannerContext.coexPriority) != COEX_STATE_CONNECTING)
			{
				status = wmx_CmdProcessStart(NDnSAgent_CoexPrio2CoexState(g_l4ScannerContext.coexPriority));
				if (status != WMX_ST_OK)
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "StartScan: Error sending ProcessStart command to the device - status=%d.", status);

					if (status == WMX_ST_NO_RF) // scan did not start because RF was "stolen"
					{
						TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "StartScan: Could not start to scan because RF was taken");
						//ClearAvailableNSPsList();
						L4S_StopRollBackScanner();
						goto Finalize;
					}
				}
				L4C_SetProcessStarted(TRUE);
			}
		}

		status = wmx_CmdStartScan(g_l4ScannerContext.coexPriority);	
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "StartScan: StartScan command sent to the device.");
		if (status != WMX_ST_OK)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "StartScan: Error sending StartScan command to the device - status=%d.", status);

			if (status == WMX_ST_NO_RF && L4C_GetInitialCoexMode() == WMX_MODE_CM) // scan did not start because RF was "stolen"
			{
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "StartScan: Could not start to scan because RF was taken");
				//ClearAvailableNSPsList();
				L4S_StopRollBackScanner();
			}
		}
		else
		{
			if (g_l4ScannerContext.currentChunk <= 1) // the chunk counter has already been incremented
			{
				// [Oran] send scan cycle start notification to the L4 Controller				
				L4C_UpdateScanStatus(TRUE);
			}
			g_l4ScannerContext.isDeviceAligned = TRUE;
		}
	}
	else // the end of the scan sequence (no more chunks left)
	{
		// TODO: Oran
		// if in AutoScan - start timer
		// if in ManualScan - stop (Send ScanComplete to user - make sure scan complete is not sent BETWEEN chunks, but only when all the chunks are over)


		// Move to standby scanning state
		if (g_l4ScannerContext.numOfRetries-- > 0)
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "StartScanInternal: Scan cycle ended. Scheduling the next scan cycle to begin in %d sec", g_l4ScannerContext.retryInterval);
			g_l4ScannerContext.waitTimeout = g_l4ScannerContext.retryInterval * 1000; // set the delay before the next scan cycle executes		
			g_l4ScannerContext.currentChunk = 0; // reset the chunks count
			g_l4ScannerContext.nextChannelToScan = 0;
			OSAL_atomic_exchange(&g_l4ScannerContext.isTimerStarted, TRUE);
			L4S_SetScannerState(L4S_STANDBY); // move to standby state before going to sleep
			OSAL_set_event(g_l4ScannerContext.hTimerEvent); // start the clock
			status = WMX_ST_OK;
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "StartScanInternal: Scan cycle ended. No more retries left for the current link loss type");
			status = WMX_ST_WRONG_ARGUMENT; // no more retries
		}
	}
Finalize:
	if (status != WMX_ST_OK)
	{
		L4S_SetScannerState(L4S_READY);
		OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
	}
	return status;
}


wmx_Status_t L4S_StartScanner(BOOL isSingleScan)
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_StartScanner(IN) - isSingleScan=%d", isSingleScan);

	if ((!L4S_IsReady()) && (TRUE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isResetRequested, TRUE, TRUE)))
	{	// the scanner is not ready due to incomplete reset process
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4Scanner: Unable to start scan. Scanner is not ready");		
		return WMX_ST_WRONG_STATE;
	}

	if (FALSE == OSAL_atomic_compareExchange(&g_l4ScannerContext.isEnabled, FALSE, FALSE))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_StartScanner: Scanner is disabled. Scan request discarded");
		return WMX_ST_OK;
	}

	// if we are already in a scanning state - we can't enter it again
	if (!L4S_SetScannerStateIfNotEqual(L4S_SCANNING, L4S_SCANNING))
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4Scanner: Unable to start scan. Scanner state is already in a scanning state");		
		return WMX_ST_WRONG_STATE;
	}	

	g_l4ScannerContext.isSingleScan = isSingleScan;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_StartScanner(almost OUT)");
	return L4S_StartScannerInternal(0, NULL, 0);
}


wmx_Status_t L4S_StopScanner()
{
	/*wmx_Status_t status;

	status = wmx_CmdStopScan();
	if( status != WMX_ST_OK )
	{
	return status;
	}*/

	return WMX_ST_OK;
}

// this call is used to in stop the scanner when the device is not available
// anymore for this activity (e.g. because of RF taken). The content is
// similar to L4S_Reset() with slight changes
void L4S_StopRollBackScanner()
{
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG,
		"L4S_StopRollBackScanner(IN) Scanner state=%s.",
		ScannerStateStr[L4S_GetScannerState()]);

	// scanner is stopped. no need for system update anymore
	wmx_UnregisterSystemStateUpdateCB(&HandleSystemState);
	if (g_l4ScannerContext.isSingleScan)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "No background scan context.");
		L4S_SetScannerState(L4S_READY);
	}
	else
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "Background scan context. Restart background scan");
		g_l4ScannerContext.numOfRetries++;
		g_l4ScannerContext.waitTimeout = g_l4ScannerContext.retryInterval * 1000; // set the delay before the next scan cycle executes
		g_l4ScannerContext.currentChunk = 0;
		g_l4ScannerContext.nextChannelToScan = 0;
		OSAL_atomic_exchange(&g_l4ScannerContext.isTimerStarted, TRUE);
		L4S_SetScannerState(L4S_STANDBY); // move to standby state before going to sleep
		OSAL_set_event(g_l4ScannerContext.hTimerEvent); // reset auto-retry thread
	}

	L4C_SetProcessStarted(FALSE);
	OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_DEBUG, "L4S_StopRollBackScanner(OUT)");				
}

UINT32 L4S_GetScanProgress()
{
	if (g_l4ScannerContext.numChunks != 0)
	{
		return (UINT32)(g_l4ScannerContext.currentChunk * 100 / g_l4ScannerContext.numChunks);	
	}
	else
	{
		return 0;
	}
}

// used to continue/finalize the discovery stage
// (active right after the disconnection following a discovery connect)
void WMX_EXT_CALL_CONV HandleSystemState(wmx_pSystemStateUpdate systemStateUpdate)
{
	wmx_Status_t status;
	ScannerState scannerState = L4S_GetScannerState();
	//UINT32 j=0;


	/*TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, L"<--- HandleSystemState DOING L4db_SortNapChannels -->");
	for (j=0 ; j < g_l4ScannerContext.scanResults.NAPsCount; j++)
	{
	L4db_SortNapChannels(&g_l4ScannerContext.scanResults.NAPs[j], 0, (int)(g_l4ScannerContext.scanResults.NAPs[j].numChannels-1));

	}*/
	if (L4C_GetInitialCoexMode() == WMX_MODE_CM &&
		systemStateUpdate->ReportStateReason == StateReasonFailToConnectCoexNoRF)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "L4S HandleSystemState: Rf was taken. Must abort current process.");
		L4S_StopRollBackScanner();
		L4C_ProcessScanResults(&g_l4ScannerContext.scanResults);
		return;
	}

	if ((scannerState == L4S_SCANNING) && (systemStateUpdate->SystemState == Ready))
	{
		L4S_SetScannerState(L4S_DISCOVER);
		status = L4S_DiscoverInternal(); // execute discovery for the current chunk
		if (L4C_GetInitialCoexMode() == WMX_MODE_CM && status == WMX_ST_NO_RF) // RF was taken from us. No need to continue.
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Discovery process could not start because RF was taken.");
			L4S_StopRollBackScanner();
			L4C_ProcessScanResults(&g_l4ScannerContext.scanResults);
		}
	}
	// set disconnect completed if needed
	else if (((scannerState == L4S_DISCONNECT) || (scannerState == L4S_DISCOVER)) && (systemStateUpdate->SystemState == Ready))	
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Discovery disconnect completed");

		if (++g_l4ScannerContext.scanResults.currentNapIndex < g_l4ScannerContext.scanResults.NAPsCount)
		{
			if ((!L4S_SetScannerStateIfEqual(L4S_DISCONNECT, L4S_DISCOVER)) && (L4S_GetScannerState() != L4S_DISCOVER))
			{
				// if the scanner is not in L4S_DISCOVER state and it also can't move to this state - report an error
				TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4Scanner::HandleSystemState - state has changed from L4S_DISCONNECT in the middle of the function");
			}
			else
			{
				status = L4S_DiscoverInternal(); // continue discovery for the next NAP
				if (L4C_GetInitialCoexMode() == WMX_MODE_CM && status == WMX_ST_NO_RF) // RF was taken from us. No need to continue.
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Discovery process could not start because RF was taken.");
					L4S_StopRollBackScanner();
					L4C_ProcessScanResults(&g_l4ScannerContext.scanResults);
				}
			}
		}
		else // discovery for the current chunk is done. Report the L4C
		{
			wmx_UnregisterSystemStateUpdateCB(&HandleSystemState);
			// Use the 0 value in the scan status for incremental results
			if (g_l4ScannerContext.scanResults.scanStatus > 0) // if this was the last scan result in the current chunk
			{
				L4S_SetScannerState(L4S_READY);
				OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
			}
			else // there are more results - continue scanning (meaning more scan updates during the SAME chunk)
			{
				L4S_SetScannerState(L4S_SCANNING);
			}		
			//L4C_UpdateData(L4C_CbType_ScanResults, (L4C_pDataUnion)&g_l4ScannerContext.scanResults);
			L4C_ProcessScanResults(&g_l4ScannerContext.scanResults);
		}
	}
	// TODO: Oran - check if we should verify more states (RfShutDown etc.)
	// This check if a backup - in case the L4C doesn't stop the L4S on time
	else if ((systemStateUpdate->SystemState == RfOff) ||
		(systemStateUpdate->SystemState == RfShutDown) ||
		(systemStateUpdate->SystemState == UnInitialized) ||
		(systemStateUpdate->SystemState == Config) ||
		(systemStateUpdate->SystemState == Initialized))
	{
		wmx_UnregisterSystemStateUpdateCB(&HandleSystemState);
		L4S_SetScannerState(L4S_READY);
		OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
	}
	else if (systemStateUpdate->SystemState == WimaxConnected || systemStateUpdate->SystemState == DataPathConnected)
	{
		L4S_SetScannerState(L4S_READY);
	}
}

wmx_Status_t L4S_Discover()
{
	wmx_Status_t status = WMX_ST_OK;

	status = wmx_RegisterSystemStateUpdateCB(&HandleSystemState);
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4S_Discover: Unable to register on system state update");
	}

	return status;
}

wmx_Status_t L4S_DiscoverInternal()
{	

	wmx_ConnectFlags_t connectFlags;	
	wmx_NAP_t currentNAP = g_l4ScannerContext.scanResults.NAPs[g_l4ScannerContext.scanResults.currentNapIndex];

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_DiscoverInternal(IN)");
	if (L4S_GetScannerState() != L4S_DISCOVER)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "L4S_DiscoverInternal(OUT) - WMX_ST_WRONG_STATE");
		return WMX_ST_WRONG_STATE;
	}

	if (!_16G_ON) // if 16G is off, we don't need to discover entries which already have full NAP ID
	{
		// skip entries with full nap / bsid
		while ((currentNAP.bsIDType == FULL_BSID || currentNAP.bsIDType == FULL_NAP) &&
			(g_l4ScannerContext.scanResults.currentNapIndex < g_l4ScannerContext.scanResults.NAPsCount))
		{			
			currentNAP = g_l4ScannerContext.scanResults.NAPs[++g_l4ScannerContext.scanResults.currentNapIndex];
		}

		connectFlags.SIQ = 0; // don't request 16G info
	}
	else
	{
		connectFlags.SIQ = 0xF; // request 16G info
	}

	if (g_l4ScannerContext.scanResults.currentNapIndex < g_l4ScannerContext.scanResults.NAPsCount)
	{
		connectFlags.requestRealm = REQUEST_REALM_DONT_REQUEST;
		connectFlags.visitedNspId = 0;

		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "Trying to connect - bscriteria = %d, bscriteria mask = %d", currentNAP.bsCriteria.bsID, currentNAP.bsCriteria.bsIDmask);

		return wmx_CmdStartConnect( currentNAP.bsCriteria, thCriteria, &connectFlags, COEX_PRIORITY_CONNECT_LOW, CONNECTION_MODE_DCD_DISCOVERY );
	}
	else
	{
		if (g_l4ScannerContext.scanResults.scanStatus > 0) // if this was the last scan result in the current chunk
		{
			//L4S_SetScannerState(L4S_READY);
			OSAL_atomic_exchange(&g_l4ScannerContext.isResetRequested, FALSE);
		}
		else // there are more results - continue scanning (meaning more scan updates during the SAME chunk)
		{
			L4S_SetScannerState(L4S_SCANNING);
		}
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "L4S_DiscoverInternal(OUT) - L4C_ProcessScanResults");
		return L4C_ProcessScanResults(&g_l4ScannerContext.scanResults);
		//return L4C_UpdateData(L4C_CbType_ScanResults, (L4C_pDataUnion)&g_l4ScannerContext.scanResults);
	}
}

wmx_ScanType_t L4S_GetScanType()
{
	return g_l4ScannerContext.scanType;
}
