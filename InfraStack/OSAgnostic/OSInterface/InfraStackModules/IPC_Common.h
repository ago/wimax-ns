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
#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "CommonServices.h"
#include "wimax_osal_types.h"


// TODO - explain this size
// 8224 + 12 = 8236 (old value was: 8232)
#define MAX_DATA_SIZE 8236
// The number of attempts to read the message using recv
// Every attempt takes RCV_TIMEOUT at most
#define MAX_RCV_ATTEMPTS_NUM 4
// The timeout for every attempt to read the message
#define RCV_TIMEOUT 1000000 // in microsecs

#define SOCKET_SHUTDOWN_TIMEOUT		100

// mutex locking macros
#define SOCKETS_ACQUIRE_MUTEX(mutex)  WaitForSingleObject(mutex, INFINITE)
#define SOCKETS_RELEASE_MUTEX(mutex)  ReleaseMutex(mutex)
#define SOCKETS_RELEASE_MUTEX_WITH_CHECK(mutex)  VERIFY(ReleaseMutex(mutex))

// NPipe definitions
#define SDK_NAMED_PIPE_BUFSIZE 8236
#define SDK_NAMED_PIPE_TIMEOUT 5000
#define SDK_NAMED_PIPE TEXT("\\\\.\\pipe\\WimaxSdkPipe")


typedef enum _SOCKETS_RESULT
{
	SOCKETS_SUCCESS,
	SOCKETS_BAD_DATA,
	SOCKETS_ERROR,		// use GetLastError
	SOCKETS_WSA_ERROR,  // use WSAGetLastError
	SOCKETS_SPECIAL_ERROR
} SOCKETS_RESULT;


// Client context
typedef void* SOCKETS_CLIENT_CONTEXT;
// Client identifier - this will be sent to the handlers
typedef long SOCKETS_CLIENT_ID;
typedef long PIPE_CLIENT_ID;

typedef struct 
{ 
	OVERLAPPED oOverlap; 
	SOCKETS_CLIENT_CONTEXT hPipeInst; 
	char chRequest[SDK_NAMED_PIPE_BUFSIZE]; 
	UINT32 cbRead;
	char chReply[SDK_NAMED_PIPE_BUFSIZE]; 
	UINT32 cbToWrite; 
	void *context;
} PIPEINST, *LPPIPEINST; 

// Callbacks
typedef void (*SOCKETS_HandleData)( char* buffer, int size, SOCKETS_CLIENT_ID clientID, void* context );
typedef void (*SOCKETS_HandleDisconnection)( SOCKETS_CLIENT_ID clientID, void* context );





// Reading a message and calling the dataHandler
// buf contains rv bytes that were read before calling this function
void SOCKETS_Read( SOCKET socket, char* buf, int rv, SOCKETS_HandleData dataHandler, SOCKETS_CLIENT_ID client, void* context );

int SOCKETS_Write( SOCKET socket, char* s, int len );

int NPIPE_Read(SOCKETS_CLIENT_CONTEXT hPipe, char* buf, int rv, SOCKETS_HandleData dataHandler, SOCKETS_CLIENT_ID client, void* context );
int NPIPE_Write( SOCKETS_CLIENT_CONTEXT hPipe, char* s, int len );
VOID NPIPE_DisconnectAndClose(LPPIPEINST lpPipeInst);

#endif /* _SOCKET_H_ */
