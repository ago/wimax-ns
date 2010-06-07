/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
#ifndef _WMX_SDK_GEN_2_H
#define _WMX_SDK_GEN_2_H



#include "wmxSDK_Gen_Cmn.h"



#define  MAX_HANDLES 10

typedef void (WMX_EXT_CALL_CONV *wmx_pMessageHandlerCB_t)( 									
									L5_TARGET_ID nOriginID,

									unsigned dwSentMessageID,
									void  *pvSentBuffer,
									unsigned cbSentBufferSize,

									unsigned *pdwResponseMessageID,
									void  *pvResponseBuffer,
									unsigned *cbResponseBufferSize );

// Oran
//typedef void (WMX_EXT_CALL_CONV *wmx_pEvenHandlerCB_t)( wmx_CtrlStatus_t ctrlStatus);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetMessagesCB ( int handle, wmx_pMessageHandlerCB_t messageCB );

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ResetMessagesCB (int handle);

// Oran
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetEventsHandlerCB( int handle, wmx_pEvenHandlerCB_t eventCB);

// Oran
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_OSAL_reset_eventsCB (int handle);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SendL5Request( int handle, L5_TARGET_ID nOriginID,
																	UINT32 dwSendMessageID, void  *pvSendBuffer, UINT32 cbSendBufferSize,
																	UINT32 *pdwReceiveMessageID, void  *pvReceiveBuffer, UINT32 *cbReceiveBufferSize );

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SendMOCEx( int handle, const char *TUIName, UINT commandID,
																UCHAR *paramsBuffer, UINT paramsBufferSize, UINT param4, BOOL replyExpected, 
																MOCTaskType *resultTaskType, UCHAR **expectedResultBuffer, UINT *expectedResultBufferSize,
																UINT *resultParam4, MOCInvokeStreamCB pStreamCBFunc);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SendAsyncMOCEx( int handle, const char *TUIName, UINT commandID,
																	 UCHAR *paramsBuffer, UINT paramsBufferSize, UINT param4, BOOL replyExpected, 																
																	 UINT *seqNum, MOCInvokeAsyncTaskCB pAsyncTaskCBFunc,MOCInvokeStreamCB pStreamCBFunc);

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxGen_GetVersion(wmx_pVersion_t version, wmx_pVersionStr_t versionStr, wmx_VersionStrLen_t verMaxLen);
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxGen_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusCB);
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxGen_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusCB);
wmx_CtrlStatus_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxGen_GetCtrlStatus();
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxGen_SetConnParams(char *szHostName, int nPort);
BOOL WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxGen_VerGenValidateVersion(int handle, const char* fileName, const char* fileBuffer, unsigned int fileBufferLength,
														   char **userVersion, const char* versionsVectorsPath);
#endif // _WMX_SDK_GEN_2_H
