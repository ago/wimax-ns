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
#pragma once

//////////////////////////////////////////////////////////////////////////
// Headers
// System
// Project
#include "CommonServices.h"
#include "L5Common.h"
#include "IPC_Common.h"



#if defined(L5_USE_SERVER_SOCKETS)
	typedef SOCKETS_CLIENT_ID SOCKETS_CLIENT;
#elif defined(L5_USE_CLIENT_SOCKETS)
	typedef SOCKETS_CLIENT_CONTEXT SOCKETS_CLIENT;
#else
	#error Either L5_USE_SERVER_SOCKETS or L5_USE_CLIENT_SOCKETS must be defined!
#endif

//////////////////////////////////////////////////////////////////////////
// Typedefs
typedef struct
{
	// Are we waiting for a reply at all?
	BOOL bWaitingForReply;

	/* The expected target ID, sequential number, and the maximum response size
	 * of the reply message.
	 */
	L5_TARGET_ID nTargetID;
	UINT32 dwSequentialNumber;
	UINT32 dwMaxReplySize;
} tL5ExpectedReplyMessageParams;


//////////////////////////////////////////////////////////////////////////
// Prototypes
BOOL L5_COMMON_UTILS_VerifyL5MessageSizes( tL5Message *pMessage );

L5_RESULT L5_COMMON_UTILS_SendMessageParams( 
	SOCKETS_CLIENT Socket,

	L5_TARGET_ID SourceID,
	L5_TARGET_ID TargetID,
	BYTE fbFlags,
	UINT32 dwSequentialNumber,
	UINT32 dwMessageID,
	UINT32 dwMaxReplyBufferSize,
	UINT32 dwSentBufferSize,
	BYTE *pbaSentBuffer );

L5_RESULT L5_COMMON_UTILS_SendControlMessage( 
	SOCKETS_CLIENT Socket,
	L5_CONTROL_MESSAGE ControlMessage,
	L5_TARGET_ID targetID,
	UINT32 dwPayload );

L5_RESULT L5_COMMON_UTILS_SendMessage( 
	SOCKETS_CLIENT Socket,
	tL5Message *pMessage );

L5_RESULT L5_COMMON_UTILS_SendEventMessage( 
	SOCKETS_CLIENT Socket,
	L5_EVENT EventMessage,
	UINT32 dwPayload );

BOOL L5_COMMON_UTILS_VerifyBufferAndSize( void *pvBuffer, UINT32 *pdwSize );
BOOL L5_COMMON_UTILS_VerifyReplyMessage( tL5Message *pMessage, tL5ExpectedReplyMessageParams *pExpected );
BOOL L5_COMMON_UTILS_IsTargetNotExist( L5_RESULT Result );

