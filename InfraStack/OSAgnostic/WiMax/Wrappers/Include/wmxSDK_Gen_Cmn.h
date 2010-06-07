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
#ifndef _WMX_SDK_GEN_CMN_H
#define _WMX_SDK_GEN_CMN_H


#include "WrappersCommon.h"

#include "MOCHandlerAPIs.h"


typedef L5_RESULT (*pMOC_ConnectEx)(const char *TUIsFilePath, BOOL enableVersionControl, const char* versionVectorsPath, 
									BroadcastHandlerCB pfnBroadcastHandler, THREAD_ID threadId, L5_CONNECTION *Conn);

typedef L5_RESULT (*pMOC_SendReceiveMOCEx)(L5_CONNECTION Conn, const char *TUIname, UINT commandID, UCHAR *paramsBuffer,
										   UINT paramsBufferSize, UINT param4, BOOL replyExpected, MOCTaskType *resultTaskType, UCHAR **expectedResultsBuffer, UINT *expectedResultsBufferSize,
										   UINT *resultParam4, MOCInvokeStreamCB pStreamCBFunc);

typedef L5_RESULT (*pMOC_SendReceiveAsyncMOCEx)(L5_CONNECTION Conn, const char *TUIname, UINT commandID, UCHAR *paramsBuffer,
												UINT paramsBufferSize, UINT param4, BOOL replyExpected, UINT *seqNum, 
												MOCInvokeAsyncTaskCB pAsyncTaskCBFunc,MOCInvokeStreamCB pStreamCBFunc);

typedef L5_RESULT (*pMOC_Disconnect)(L5_CONNECTION Conn);


#endif // _WMX_SDK_GEN_CMN_H