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
#ifndef _WMX_SDK_DND_H
#define _WMX_SDK_DND_H

#include "wmxSDK_DnD_Cmn.h"
#include "TraceModule.h"

//Definitions
#define TR_MOD_DND						999
#define READ_PERMISSION_VAL				4
#define MAX_BUFF_SIZE					8192
#define CUR_TIME_LEN					20
#define ACCESS_FAIL_VALUE				-1
#define WRAPPER_NAME_LEN				30

#define MAX_PATH_LEN					1024

#define TYPE_SIZE						2
#define LENGTH_SIZE						2

#define BST_MSB_SIZE					4
#define BST_LSB_SIZE					4

#define SUB_SYS_SIZE					4
#define SIGNATURE_SIZE					4

#define NUM_DELIMITERS_WITH_DISPLAY_STRING		6
#define NUM_DELIMITERS_WITHOUT_DISPLAY_STRING	5

#define MAX_NUM_OF_PARAMS				3

//CBs
void wmxDnD_eventHandlerCB(L5_CONNECTION Conn, L5_EVENT eEvent, void* pvEventData, void* pvUserContext);
void EventsCB(wmx_CtrlStatus_t connStatus);
void wmxDnD_MessagesHandler(L5_CONNECTION Conn,
							L5_TARGET_ID nOriginID,

							UINT32 dwSentMessageID,
							void  *pvSentBuffer,
							UINT32 cbSentBufferSize,

							UINT32 *pdwResponseMessageID,
							void  *pvResponseBuffer,
							UINT32 *cbResponseBufferSize,

							void *pvUserContext,
							void *pvReserved );


//Macros
#define TRACE_ERR(fmt, ...)\
{\
	TRACE(TR_MOD_DND, TR_SEV_ERR, fmt, ##__VA_ARGS__);\
}

#define TRACE_WAR(fmt, ...)\
{\
	TRACE(TR_MOD_DND, TR_SEV_WARNING, fmt, ##__VA_ARGS__);\
}

#define TRACE_INFO(fmt, ...)\
{\
	TRACE(TR_MOD_DND, TR_SEV_INFO, fmt, ##__VA_ARGS__);\
}

#define ARRAY_SIZE(arr)			sizeof(arr) / sizeof(arr[0])
#define MAKE_ZERO_TERMINATED(str)	(str)[ARRAY_SIZE(str) - 1] = '\0'
#define MAKE_UINT32(msb, lsb)		((UINT32)(((UINT16)(lsb)) | ((UINT32)((UINT16)(msb))) << 16))


//APIs
void FreeAllResources();
void SetPreviousSeveritiesOfDevice();

#endif //_WMX_SDK_DND_H