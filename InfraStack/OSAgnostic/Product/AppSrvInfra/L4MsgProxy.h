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
#ifndef L4_MESSAGE_PROXY_DEFINE
#define L4_MESSAGE_PROXY_DEFINE


//*********************************
//Include Files:
//*********************************
#include "L4MsgProxyIf.h"

#include "L5Common.h"

// XXX - TODO - remove the need for this
#include "WrappersCommon.h"
//#include "../../../../Common/List.h"
//#include "../../../../Common/L5CommonUtils.h"

#include "L3L4CommonDefines.h"
#include "Intel_80216_L4_interface_OS.h"
#include "L4BufMan_L4Common_Desc.h"
#include "L4BufMan_L4Common.h"

#include "L5Dispatcher.h"
#include "KDapiAdapter.h"


extern L5_CONNECTION l4Proxy_Connection;
extern tL5DispatcherFunctions *l4Proxy_pFuncs;


typedef UINT32 L4_INTEL_80216_INDICATION;


// AppSrv Agent Interface:
BOOL L4_Msg_Proxy_Initialize();
void L4_Msg_Proxy_Shutdown();
UINT32 L4Proxy_Restart();

void L4_Msg_Proxy_MessagesHandler(L5_CONNECTION Conn,
								  L5_TARGET_ID nOriginID,

								  UINT32 dwSentMessageID,
								  void  *pvSentBuffer,
								  UINT32 cbSentBufferSize,

								  UINT32 *pdwResponseMessageID,
								  void  *pvResponseBuffer,
								  UINT32 *cbResponseBufferSize,

								  void *pvUserContext,
								  void *pvReserved );

//void L4_Msg_Proxy_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext);

//Internal L4Proxy functions:
void L4Proxy_SendOID(OID_NUM oidNum, void *bufferIn, UINT32 bufferInSize,UINT32 *pdwResponseMessageID, void *bufferOut, UINT32 *bufferOutSize);
UINT32 L4Proxy_RegisterL4Indicator(L5_TARGET_ID nOriginID, L4_INTEL_80216_INDICATION l4_indication_id);
UINT32 L4Proxy_UnRegisterL4Indicator(L5_TARGET_ID nOriginID, L4_INTEL_80216_INDICATION l4_indication_id);
UINT32 L4Proxy_RegisterStatusIndicator(L5_TARGET_ID nOriginID, STATUS_IND_ID status_indication_id);
UINT32 L4Proxy_UnRegisterStatusIndicator(L5_TARGET_ID nOriginID, STATUS_IND_ID status_indication_id);


#define STATUS_OK 0
#define STATUS_ERROR -1



#endif //L4_MESSAGE_PROXY_DEFINE
