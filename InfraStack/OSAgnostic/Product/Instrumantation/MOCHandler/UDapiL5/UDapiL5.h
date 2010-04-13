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
#ifndef _UDAPIL5_DLL_H_
#define _UDAPIL5_DLL_H_


//*********************************
//Include Files:
//*********************************
#include "UDapiDll.h"
#include "MocMsgProxyIF.h"

#include "ApplicationMocTaskDesc.h"

#include "L5Common.h"
#include "PipeHandler.h"

#include "WrappersCommon.h"

#include "L3L4CommonDefines.h"
#include "Intel_80216_L4_interface_OS.h"

#include "L4MsgProxyIf.h"

#include "../Mutl/Helpers/Include/logger.h"
#include "../Mutl/Helpers/ALogger/registry_controller.h"


typedef struct 
{
	L5_CONNECTION L5ConnID;
	UINT32	handle;
	UINT8	SocketID;
	BOOL	isValid;
	BOOL	wasClosedByClient;
	int (*pReceiveCallBack)(UINT32 handle, unsigned char * pBuf, unsigned int pBufSize);
	int (*pNoticeAlertsCallback)(UINT32 handle, UDAPI_ERROR_CODE errorCode);
}PerAppInfo;

static PerAppInfo	perAppInfo[MAX_APPS_PER_DLL];

tL5DispatcherFunctions *L5dispatcher;

Logger mLogger;


void MyPrintf(const char* format, ...);

bool UDapi_DisconnectL5(UINT32 handle);
void UDapi_SafeCallL5Disconnect(UINT32 handle);

void UDapi_MessagesHandler(
	L5_CONNECTION Conn,
	L5_TARGET_ID nOriginID,

	UINT32 dwSentMessageID,
	void  *pvSentBuffer,
	UINT32 cbSentBufferSize,

	UINT32 *pdwResponseMessageID,
	void  *pvResponseBuffer,
	UINT32 *cbResponseBufferSize,

	void *pvUserContext,
	void *pvReserved );

void UDapi_EventHandler(
	L5_CONNECTION Conn,
	L5_EVENT eEvent,
	void *pvEventData,
	void *pvUserContext );


#endif // _UDAPIL5_DLL_H_