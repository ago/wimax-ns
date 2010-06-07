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
#ifndef _MESSENGER_H
#define _MESSENGER_H

#include "CommonServices.h"

typedef enum _REQUEST_PRIORITY
{
	HIGH = 0,
	MEDIUM,
	LOW,
	MaxPriority
} REQUEST_PRIORITY;


typedef void (*InternalHandler)( UINT32 internalRequestID, void *buffer, UINT32 bufferLength );

EXPORT BOOL Messenger_Initialize( );

EXPORT void Messenger_Shutdown();

//
EXPORT void Messenger_Stop();
EXPORT BOOL Messenger_Start();

EXPORT size_t Messenger_PostRequest(
							REQUEST_PRIORITY priority,
							UINT32 internalRequestID, 
							void *buffer, UINT32 bufferLength,
							InternalHandler internalHandler );

EXPORT BOOL Messenger_PopRequest(size_t seqNum);


#endif //_MESSENGER_H