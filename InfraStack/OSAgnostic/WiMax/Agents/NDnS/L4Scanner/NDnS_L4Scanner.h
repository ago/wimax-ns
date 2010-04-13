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
#ifndef _NDNS_L4_SCANNER_H
#define _NDNS_L4_SCANNER_H

#include "CommonServices.h"
#include "WrappersCommon.h"
#include "wmxSDK_Nds_1.h"
#include "NDnSAgent_L4P.h"
#include "NDnS_TinyFSM.h"

#define MAX_CHANNELS_NUM	1600
#define CHUNK_SIZE	8 //TODO: Oran - once the "best found" patch is removed, this value should be equal to 32
#define L4S_TIMEOUT	5000
#define L4S_HANDLE_ERR_SLEEP_TIME 20000

typedef enum _ScannerState
{
	L4S_READY = 0,
	L4S_SCANNING,
	L4S_DISCOVER,
	L4S_DISCONNECT,
	L4S_STANDBY,
	L4S_TRANSIENT // a special state that represents a "between states" state
} ScannerState;

static char* ScannerStateStr[] = {
	"L4S_READY",
	"L4S_SCANNING",
	"L4S_DISCOVER",
	"L4S_DISCONNECT",
	"L4S_STANDBY",
	"L4S_TRANSIENT"
};

// TODO: Oran - merge with Sivanne's version (L4P)
/*typedef enum _ScanType
{
	L4S_PREFFERED,
	L4S_WIDE
} ScanType;*/

// wmx_ScanType_t - // TODO: Oran - merge with Sivanne's version (L4P)

typedef struct _L4ScannerContext_t
{
	OSAL_thread_t hTimerThread;	// thread handle
	OSAL_event_t hTimerEvent;
	OSAL_event_t hShutdownEvent;
	OSAL_event_t hScannerResetCompleteEvent;

	TinyFSM_t fsm;	// scanner fsm
	
	UINT32 waitTimeout;

	wmx_ScanResults_t scanResults;

	LONG isTimerStarted;
	LONG isResetRequested;
	LONG isEnabled;

	NdsSettings_t settings; // TODO: Oran - temp - should be in L4C

	wmx_ScanType_t scanType;
	int numOfRetries;
	int retryInterval;
	wmx_ScanPolicy_t scanPolicy;
	wmx_CoexPriority_t coexPriority;
	BOOL isSingleScan;					// true if the current scan is in a context of single scan attempt and false in case of multiple iteration scan
	
	wmx_ChannelInfo_t mcp[MAX_CHANNELS_NUM];
	UINT32 numChannels;
	int numChunks;
	int currentChunk;
	int currentChunkSize;
	BOOL isDeviceAligned;
	wmx_pChannelInfo_t setChPlanStart;
	wmx_pChannelInfo_t setChPlanEnd;
	wmx_ChannelID_t nextChannelToScan; // Hold the last channel that was reported by L3 for resume purposes. Relevant just in SCAN_MODE_FIND_FIRST
	wmx_ChannelID_t firstFullChannel; // the first channel in the MCP which has full preambles
	BOOL divided; // is chunk divided before end;
} L4ScannerContext_t, *pL4ScannerContext_t;

//////////////////////////////////
// functions declarations

wmx_Status_t L4S_Init();
void L4S_Finalize();
wmx_Status_t L4S_Reset(BOOL hardReset);
void L4S_EnableScanner(BOOL isEnabled);
BOOL L4S_IsResetRequested();
BOOL L4S_IsScanning();

// get the current state of the scanner
ScannerState L4S_GetScannerState();
// set the scanner to a new state
void L4S_SetScannerState(ScannerState state);
// set the scanner to a new state ONLY if its current state is equal to the source state parameter
BOOL L4S_SetScannerStateIfEqual(ScannerState sourceState, ScannerState targetState);
// set the scanner to a new state ONLY if its current state is NOT equal to the source state parameter
BOOL L4S_SetScannerStateIfNotEqual(ScannerState sourceState, ScannerState targetState);

// wait until a certain state is reached
BOOL L4S_WaitForState(int state, UINT32 timeout);
// wait until one of the specified states is reached
BOOL L4S_WaitForMultipleStates(int* states, int statesCount, UINT32 timeout);

// call SetChannelPlan towards L3 with the channel plan from the input
// (the MCP is NOT changed !!!)
wmx_Status_t L4S_SendChannelPlanToDevice(wmx_ChannelInfo_t channelPlan[], UINT32 numChannels, wmx_ScanPolicy_t scanPolicy);

// Set configuration for prefered scan
wmx_Status_t L4S_SetPSCfg(wmx_ChannelInfo_t mcp[], UINT32 numChannels, int numOfRetries, int retryInterval, wmx_ScanPolicy_t scanPolicy, wmx_CoexPriority_t coexPriority, BOOL delayStart );
// Set configuration for wide scan
wmx_Status_t L4S_SetWSCfg(/* BandRange[], BandStep, Bandwidths[], */ int numOfRetries, int retryInterval, wmx_CoexPriority_t coexPriority, BOOL delayStart );
// Set configuration for while scan - only for V3.0
wmx_Status_t L4S_SetWhileSCfg(wmx_ChannelInfo_t mcp[], UINT32 numChannels, int numOfRetries, int retryInterval, wmx_CoexPriority_t coexPriority, BOOL delayStart );
// Converts the given preambleId to a preamble bitmap
wmx_Status_t L4S_ConvertPreambleIdToPreambleBitmap(UINT16 preambleId,
												   wmx_pChannelInfo_t chInfo);
wmx_Status_t L4S_StartScanner(BOOL isSingleScan);
wmx_Status_t L4S_StopScanner();
BOOL L4S_AreChunksLeft();
void L4S_EndScanCycle();
BOOL L4S_IsReady();
wmx_Status_t L4S_ConvertChIdsToChPlan(wmx_NAP_t Nap, 
									  UINT32 chIdsCount, 
									  pChannelInfo_t chInfos, 
									  UINT32 *numOfChannelInfos);
BOOL L4S_AreChannelsInLastChunk(wmx_ChannelInfo_t channelPlan[], UINT32 numChannels);

wmx_ScanType_t L4S_GetScanType();
UINT32 L4S_GetScanProgress();
wmx_Status_t L4S_Discover();

void L4S_ScanUpdate(wmx_ScanStatus_t scanStatus, UINT32 numOfNaps, wmx_pNAP_t naps);
void L4S_BsInfoUpdate(wmx_pBsInfo_t bsInfo);
void L4S_SIIUpdate(wmx_pSII_t sii);
void L4S_StopRollBackScanner();

#endif // _NDNS_L4_SCANNER_H