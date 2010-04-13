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
#include "wimax_osal_primitives.h"
#include "IPC_Client.h"
#include "TraceModule.h"


int CLIENTS_NPIPE_SendToServer( char* s, int len, SOCKETS_CLIENT_CONTEXT client )
{
	int res = 0;

	return res;
}

void CLIENTS_NPIPE_Select( LPVOID lpParameter )
{

}


SOCKETS_RESULT CLIENTS_NPIPE_ConnectToServer( SOCKETS_CLIENT_CONTEXT client )
{
	return SOCKETS_ERROR;
}


SOCKETS_RESULT CLIENTS_NPIPE_CreateNewClient( void* context, SOCKETS_HandleData dataHandler, 
											SOCKETS_HandleDisconnection disconnectionHandler, 
											SOCKETS_CLIENT_CONTEXT* client, SOCKETS_CLIENT_ID* clientID )
{
	return SOCKET_ERROR;

}





SOCKETS_RESULT CLIENTS_NPIPE_Init(	SOCKETS_CLIENT_CONTEXT* client, SOCKETS_CLIENT_ID* clientID, void* context, 
									SOCKETS_HandleData dataHandler, SOCKETS_HandleDisconnection disconnectionHandler )
{
	return SOCKET_ERROR;
}

void CLIENTS_NPIPE_Fini( SOCKETS_CLIENT_CONTEXT* client )
{
}

void CLIENTS_NPIPE_DisconnectFromServer( SOCKETS_CLIENT_CONTEXT client )
{
}






