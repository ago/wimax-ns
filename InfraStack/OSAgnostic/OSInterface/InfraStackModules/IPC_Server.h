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
#ifndef _SERVER_SOCKETS_H_
#define _SERVER_SOCKETS_H_
#ifndef _lint // disables lint warnings from this file


#include "IPC_Common.h"

typedef struct _SERVER_CLIENT_DATA
{
	// For using a slot for a new client only after the listening thread
	// updated its select group and called the disconnection handler
	BOOL full;	

	SOCKET socket;
	LPPIPEINST pipeInstance;
	void* context;
} SERVER_CLIENT_DATA, *PSERVER_CLIENT_DATA;


#define SDK_NAMED_PIPE_BUFSIZE 8236
#define SDK_NAMED_PIPE_TIMEOUT 5000
#define SDK_NAMED_PIPE TEXT("\\\\.\\pipe\\WimaxSdkPipe")


// see FD_SETSIZE (defined in winsock2, used in the select function)
#define MAX_SERVER_SOCKETS 63

typedef void (*SERVER_SOCKETS_HandleNewConnection)( SOCKETS_CLIENT_ID clientID, void** context );

SOCKETS_RESULT SERVER_SOCKETS_Init();

void SERVER_SOCKETS_Fini();


SOCKETS_RESULT SERVER_SOCKETS_StartServer( 
	UINT32 port,
	SOCKETS_HandleData dataHandler, 
	SERVER_SOCKETS_HandleNewConnection newConnectionHandler, 
	SOCKETS_HandleDisconnection disconnectionHandler );

void SERVER_SOCKETS_StopServer();

int SERVER_SOCKETS_SendToClient( char* s, int len, SOCKETS_CLIENT_ID clientID );

void SERVER_SOCKETS_DisconnectClient( SOCKETS_CLIENT_ID clientID );
void SERVER_SOCKETS_DisconnectClients();


//NPIPE functions
int SERVER_NPIPE_SendToClient( char* s, int len, SOCKETS_CLIENT_ID clientID );
void SERVER_NPIPE_DisconnectClient( SOCKETS_CLIENT_ID clientID );
void SERVER_NPIPE_StopServer();
SOCKETS_RESULT SERVER_NPIPE_Init();
SOCKETS_RESULT SERVER_NPIPE_StartServer(SOCKETS_HandleData dataHandler, 
										SERVER_SOCKETS_HandleNewConnection newConnectionHandler, 
										SOCKETS_HandleDisconnection disconnectionHandler );
void SERVER_NPIPE_Fini();
int SERVER_NPIPE_FindIDByHandle(LPPIPEINST lpPipeInst);
void SERVER_NPIPE_DisconnectClients();
#endif
#endif /* _SERVER_SOCKETS_H_ */
