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
#ifndef _NDNS_L4_PUBLISHER_H
#define _NDNS_L4_PUBLISHER_H

#include "CommonServices.h"
#include "WrappersCommon.h"
#include "NDnSAgent_Internals.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_3.h"

////////////////////////////////////
// type definitions

typedef struct _wmx_DeviceStatusUpdate_t
{
	//OSAL_critical_section				lock;
	wmx_DeviceStatus_t				deviceStatus;
	wmx_ConnectionProgressInfo_t	connectProgress;
	/*L4CState						l4cState;
	wmx_SystemStateUpdate			systemStateUpdate;
	BOOL activation;*/
}wmx_DeviceStatusUpdate_t, *wmx_pDeviceStatusUpdate_t;

// internal L4 Publisher DB
typedef struct _L4PublisherContext_t
{
	OSAL_critical_section lock;
	wmx_DeviceStatusUpdate_t deviceStatus;
	L4CState l4cState;
	wmx_SystemStateUpdate systemStateUpdate;
	BOOL isScanning;
	wmx_ScanType_t scanType;
	BOOL activation;
	BOOL filterDeviceAssertReconnect;
	OSAL_event_t hTimerEvent;
	BOOL cmdResetWasCalled;
} L4PublisherContext_t, *pL4PublisherContext_t;

typedef struct _L4Pub_States_t
{
	wmx_pSystemStateUpdate pSystemStateUpdate;
	L4CState l4cState;
} L4Pub_States_t, *L4Pub_pStates_t;

/*typedef struct _L4Pub_ScanCycleStatus_t
{
	BOOL isScanning;
	wmx_ScanType_t scanType;
} L4Pub_ScanCycleStatus_t, *L4Pub_pScanCycleStatus_t;*/

/////////////////////////////
// Update callbacks type definitions
typedef enum _L4Pub_CallbackType_t
{
	L4Pub_CbType_StatesChange = 0x1,
	L4Pub_CbType_ScanType,
	L4Pub_CbType_ScanStatus
} L4Pub_CallbackType_t, *L4Pub_pCallbackType_t;

typedef union _L4Pub_CallbackParamsUnion  /* A definition and a declaration */
{
	L4Pub_States_t statesStruct;
	//L4Pub_ScanCycleStatus_t scanCycleStatusStruct;
	wmx_ScanType_t scanType;	
	BOOL scanStatus;
} L4Pub_CallbackParamsUnion, *L4Pub_pCallbackParamsUnion;

typedef struct _L4Pub_CallbackStruct
{
	L4Pub_CallbackType_t cbType;
	L4Pub_CallbackParamsUnion cbParamsUnion;
} L4Pub_CallbackStruct, *L4Pub_pCallbackStruct;
////////////////////////////

//////////////////////////////////
// functions declarations

void L4Pub_Init();
void L4Pub_Finalize();
void L4Pub_Reset();

// send updates to the L4 Publisher
void L4Pub_UpdateData(L4Pub_CallbackType_t dataType, L4Pub_pCallbackParamsUnion data);

// Enters the status of the device (~L4C FSM) to the Buffer, returns an error if buffer is too short.
void L4Pub_SendDeviceStatusUpdate(wmx_DeviceStatus_t deviceStatus, wmx_ConnectionProgressInfo_t connectionProgress);

void L4Pub_SetDeviceStatusActivationConnect(BOOL activation);

wmx_Status_t L4Pub_GetDeviceStatus(void *buffer, UINT32 *bufferSize);

void L4Pub_SetSystemStateUpdate(wmx_pSystemStateUpdate systemStateUpdate);

void L4Pub_SendScanCompleted(wmx_ScanStatus_t scanStatus);

void L4Pub_WatchTimerForReconnect(void);

void L4Pub_ThreadWatchTimerWatchTimerForReconnect(LPVOID lpParam);

void L4Pub_UpdateScanStatus(BOOL scanStatus);

void L4Pub_UpdateScanState (BOOL scanState);

void L4Pub_CmdReset();

#endif // _NDNS_L4_PUBLISHER_H