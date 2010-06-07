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
#ifndef _DEBUG_INTERNAL_H_
#define _DEBUG_INTERNAL_H_

#include "\DebugWrapperCommon.h"
#include "List.h"
#include "L5Common.h"

#define BY_VAL_BUF_SZ (12) 
#define TR_MOD_ORANGE_DEBUG (888)

wmx_Status_t InitInternalResources();
void FinalizeInternalResources();

wmx_Status_t RegisterDilloCBFunc(MetricStreamsCallback pCallBack);
wmx_Status_t RegisterMonitorCBFunc(MetricStreamsCallback pCallBack);
wmx_Status_t RegisterCBFunc(List* handlersList, MetricStreamsCallback pCallBack);

wmx_Status_t UnregisterDilloCBFunc(MetricStreamsCallback pCallBack);
wmx_Status_t UnregisterMonitorCBFunc(MetricStreamsCallback pCallBack);
wmx_Status_t UnregisterCBFunc(List* handlersList, MetricStreamsCallback pCallBack);

void InvokeCBFunctions(List* handlersList,
					   int descType, 
					   int descLength, 
					   unsigned char * descriptorBuf,
					   int payloadLength, 
					   unsigned char * payloadBuf, 
					   unsigned seqNum, 
					   unsigned frameNum);


void CreateByValBuf(unsigned char data[], UINT32 param1, UINT32 param2, UINT32 param3);

wmx_Status_t Peek(L5_CONNECTION  handle, UINT32 address, UINT32 mask, UINT32* outVal);
wmx_Status_t Poke(L5_CONNECTION  handle, UINT32 address, UINT32 mask, UINT32 value, UINT32 sizeBytes);


wmx_Status_t SendMocByVal(L5_CONNECTION  handle, const char* tuiName, PUINT8 data, PUINT8* pResBuf, MOCInvokeStreamCB pFunc);
wmx_Status_t SendMocWithNoParams(L5_CONNECTION  handle, const char* tuiName, MOCInvokeStreamCB pFunc);
wmx_Status_t SendLTAMoc(L5_CONNECTION handle, const char * tuiName, PUINT8 data, UINT32 dataSize, unsigned char** resBuf);


int DilloStreamCallback(L5_RESULT callbackStatus,                          
								  unsigned int commandID,
								  unsigned int mocSeqNum,
								  BOOL streamEnd,
								  MOCTaskType resultTaskType,
								  unsigned char * expectedResultsBuffer, unsigned int expectedResultsBufferSize,
								  unsigned int resultParam4);

int MonitorStreamCallback(L5_RESULT callbackStatus,                          
									unsigned int commandID,
									unsigned int mocSeqNum,
									BOOL streamEnd,
									MOCTaskType resultTaskType,
									unsigned char * expectedResultsBuffer, unsigned int expectedResultsBufferSize,
									unsigned int resultParam4);
#endif // _DEBUG_INTERNAL_H_