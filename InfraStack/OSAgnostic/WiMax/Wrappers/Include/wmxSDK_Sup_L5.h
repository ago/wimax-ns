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
#ifndef _WMX_SDK_SUP_L5_H
#define _WMX_SDK_SUP_L5_H


#include "CommonServices.h"
#include "WrappersCommon.h"
#include "L5Common.h"


typedef enum _SUP_AGENT_CRED_OPCODE
{
	//Commands OPCODES
	SUP_OPCODE_SET_IDENTITY = 0,
	SUP_OPCODE_SET_ANONYMOUS_IDENTITY,
	SUP_OPCODE_SET_PASSWORD,
	SUP_OPCODE_SET_NEW_PASSWORD,
	SUP_OPCODE_SET_EAP_METHOD,
	SUP_OPCODE_SET_PHASE2_METHOD,
	SUP_OPCODE_SET_TLS_CA_CERT,
	SUP_OPCODE_SET_TLS_CA_CERT2,
	SUP_OPCODE_SET_TLS_CLIENT_CERT,
	SUP_OPCODE_SET_TLS_CLIENT_CERT2,
	SUP_OPCODE_SET_TLS_PRIVATE_KEY,
	SUP_OPCODE_SET_TLS_PRIVATE_KEY2,
	SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD,
	SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD2,
	SUP_OPCODE_SET_PIN,
	SUP_OPCODE_SET_PIN_MAX_SIZE,
	SUP_OPCODE_SET_TLS_MAX_SIZE,
	//Indication Types OPCODES
	SUP_OPCODE_IND_EVENT,
	
	SUP_OPCODE_ERROR
} SUP_AGENT_CRED_OPCODE;

typedef struct _SUP_MESSAGE_HEADER
{
	UINT32 opcode;
	UINT32 bufferLength;
} SUP_MESSAGE_HEADER, *pSUP_MESSAGE_HEADER;

typedef struct _SUP_MESSAGE
{
	SUP_MESSAGE_HEADER header;
	char buf[1];
} SUP_MESSAGE, *pSUP_MESSAGE;

wmx_Status_t wmxSup_InitL5();
void wmxSup_FinalizeL5();

void wmxSup_MessagesHandler(L5_CONNECTION Conn,
											L5_TARGET_ID nOriginID,

											UINT32 dwSentMessageID,
											void  *pvSentBuffer,
											UINT32 cbSentBufferSize,

											UINT32 *pdwResponseMessageID,
											void  *pvResponseBuffer,
											UINT32 *cbResponseBufferSize,

											void *pvUserContext,
											void *pvReserved );

void wmxSup_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext);

typedef enum _SUPP_WRAPPER_L4_OPCODE
{
	// Setters
	SUPP_OPCODE_CMD_EAP_RESPONSE,	
	SUPP_OPCODE_CMD_EAP_SUCCESS,
	SUPP_OPCODE_CMD_EAP_FAIL,
	SUPP_OPCODE_CMD_EAP_KEY,

	//Indication Types OPCODES
	SUPP_OPCODE_IND_EAP_REQUEST_AVAILABLE,
	SUPP_OPCODE_IND_EAP_KEY_AVAILABLE,
	SUPP_OPCODE_IND_ALTERNATIVE_EAP_SUCCESS,	

	//Error
	SUPP_OPCODE_ERROR
} SUPP_WRAPPER_L4_OPCODE;

#endif // _WMX_SDK_SUP_L5_H