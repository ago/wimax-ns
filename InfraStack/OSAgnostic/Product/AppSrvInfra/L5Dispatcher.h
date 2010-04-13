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
#ifndef L5DISPATCHER_H
#define L5DISPATCHER_H

//////////////////////////////////////////////////////////////////////////
// Headers

// OSAL
#include "wimax_osal_primitives.h"

// Project
#include "CommonServices.h"
#include "L5Common.h"

#include "Act.h"

#include "List.h"


//////////////////////////////////////////////////////////////////////////
// Definitions
#define L5_DISPATCHER_MAX_CONNECTIONS				30  /*XXX*/
#define L5_DISPATCHER_MAX_PRESERVED_TARGET_IDS		100 /*XXX*/

//////////////////////////////////////////////////////////////////////////
// Typedefs
typedef struct
{
	// State
	BOOL bFree;  // Connection is getting free after all the targets were informed on disconnection

	// Logic
	L5_TARGET_ID nTargetID;
	tpfnMessagesHandler pfnMessagesHandler;
	tpfnEventHandler pfnEventHandler;
	void *pvUserContext;

	OSAL_critical_section rwlConn;

} tL5DispatcherConnection;

//////////////////////////////////////////////////////////////////////////
// Prototypes
BOOL L5_DISPATCHER_Initialize();
void L5_DISPATCHER_Shutdown();
tL5DispatcherFunctions *L5_DISPATCHER_GetServiceDispatcherFunctions();
L5_RESULT L5_DISPATCHER_BroadcastEvent(L5_CONNECTION Conn, L5_EVENT l5Event);


L5_RESULT L5_DISPATCHER_Connect(	
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,	
	L5_CONNECTION *Conn);

L5_RESULT L5_DISPATCHER_ConnectEx(	
	L5_TARGET_ID nTargetID,
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,
	void *pvUserContext,
	THREAD_ID threadId,
	L5_CONNECTION *Conn);

L5_RESULT L5_DISPATCHER_ConnectInternal(
	char *szHostName,
	int nPort,
	L5_TARGET_ID nTargetID,
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,
	void *pvUserContext,

	L5_CONNECTION *pConn );

void L5_DISPATCHER_Disconnect( L5_CONNECTION Conn );

L5_RESULT L5_DISPATCHER_SendReceiveMessage( 
	L5_CONNECTION Conn,
	L5_TARGET_ID nTargetID,

	UINT32 dwSendMessageID,
	void  *pvSendBuffer,
	UINT32 cbSendBufferSize,

	UINT32 *pdwReceiveMessageID,
	void  *pvReceiveBuffer,
	UINT32 *cbReceiveBufferSize );

void L5_DISPATCHER_SendErrorReport( L5_TARGET_ID senderID, ERROR_REPORT_OPCODE opcode, const char* function, int line);

void L5_DISPATCHER_SendDeviceRemoveReport(L5_TARGET_ID senderID);

#endif