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
#ifndef _MOC_MSG_PROXY_H_
#define _MOC_MSG_PROXY_H_


//*********************************
//Include Files:
//*********************************
#include "MocMsgProxyIF.h"

#include "L5Common.h"
#include "L5Dispatcher.h"
#include "KDapiAdapter.h"


/************************************************************************/
/* defines                                                              */
/************************************************************************/
//#define MOC_MSG_PROXY_MAX_PAYLOAD  (8 * 1024)
#define MOC_MSG_PROXY_MAX_APPS  (128)

/************************************************************************/
/* Data Structures                                                      */
/************************************************************************/
typedef struct 
{
	BOOL		isValid;
	//UINT8		socketID;
	//L5_CONNECTION L5ConnID;
	L5_TARGET_ID originID;
	UINT8		handle;
	//SOCKET		acceptedSocket;
} PerAppInfo;

/************************************************************************/
/* static variables                                                     */
/************************************************************************/
static tL5DispatcherFunctions *L5dispatcherBackup = NULL;
static PerAppInfo perAppInfo[MOC_MSG_PROXY_MAX_APPS];
static int lastAcquiredPlace;
static tL5DispatcherFunctions *L5dispatcher = NULL;
static L5_CONNECTION L5ConnID = NULL;
static OSAL_critical_section perAppInfoGuard;	
static BOOL initialized;


EXTERN_C EXPORT APPSRV_INIT_ST MocMsgProxy_Initialize(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn);
EXTERN_C EXPORT BOOL MocMsgProxy_Start();
EXTERN_C EXPORT BOOL MocMsgProxy_Stop();
EXTERN_C EXPORT void MocMsgProxy_Finalize();

BOOL MocMsgProxy_Shutdown();

static BOOL MocMsgProxy_ConnectL5();
static BOOL MocMsgProxy_BindToL4msgProxy();
static BOOL MocMsgProxy_UnBindToL4msgProxy();

static int MocMsgProxy_GetFreePlace(void);
static UINT8 MocMsgProxy_AcquireSocketID(L5_TARGET_ID nOriginID, UINT8 handle);
static void MocMsgProxy_ReleaseSocketID(L5_TARGET_ID nOriginID, void *buf, UINT32 bufSize);
static void MocMsgProxy_SendMocResponse(L5_CONNECTION Conn, L5_TARGET_ID nOriginID, void *buf, UINT32 bufSize);
static void MocMsgProxy_ProcessL4Indication(void *buf, UINT32 bufSize);

static void MocMsgProxy_MessagesHandler(
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

void MocMsgProxy_EventHandler(
	L5_CONNECTION Conn,
	L5_EVENT eEvent,
	void *pvEventData,
	void *pvUserContext );


#endif // _MOC_MSG_PROXY_H_
