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
#ifndef _WMX_SDK_MSC_L5_H
#define _WMX_SDK_MSC_L5_H


#include "CommonServices.h"
#include "WrappersCommon.h"
#include "L5Common.h"


typedef enum _MISC_WRAPPER_L4_OPCODE
{
	// Setters

	//Data Getters
	MISC_OPCODE_GET_DEVICE_VERSION,
	MISC_OPCODE_GET_MAC_ADDRESS,
	MISC_OPCODE_GET_STATISTICS,

	//Error
	MISC_OPCODE_ERROR
} MISC_WRAPPER_L4_OPCODE;

//
wmx_Status_t wmxMsc_InitL5();
void wmxMsc_FinalizeL5();

//void wmxMsc_MessagesHandler(L5_CONNECTION Conn,
//							L5_TARGET_ID nOriginID,
//
//							UINT32 dwSentMessageID,
//							void  *pvSentBuffer,
//							UINT32 cbSentBufferSize,
//
//							UINT32 *pdwResponseMessageID,
//							void  *pvResponseBuffer,
//							UINT32 *cbResponseBufferSize,
//
//							void *pvUserContext,
//							void *pvReserved );
//
//void wmxMsc_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext);


#endif // _WMX_SDK_MSC_L5_H