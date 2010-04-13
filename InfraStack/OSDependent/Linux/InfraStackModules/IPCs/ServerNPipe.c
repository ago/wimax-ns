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

#include "IPC_Server.h"
#include "TraceModule.h"


VOID WINAPI CompletedWriteRoutine(DWORD dwErr, DWORD cbWritten, LPOVERLAPPED lpOverLap) ;

BOOL SERVER_NPIPE_CheckForClientDisconnection();

BOOL ConnectToNewClient(HANDLE hPipe, LPOVERLAPPED lpo) 
{ 
	return FALSE; 
}



BOOL CreateAndConnectInstance(LPOVERLAPPED lpoOverlap) 
{ 

	return FALSE;
}



VOID WINAPI CompletedReadRoutine(DWORD dwErr, DWORD cbBytesRead, 
								 LPOVERLAPPED lpOverLap) 
{ 
}

VOID WINAPI CompletedWriteRoutine(DWORD dwErr, DWORD cbWritten, LPOVERLAPPED lpOverLap) 
{ 

} 


void SERVER_NPIPE_Select( LPVOID lpParameter )
{

}



SOCKETS_RESULT SERVER_NPIPE_StartServer(SOCKETS_HandleData dataHandler, 
										SERVER_SOCKETS_HandleNewConnection newConnectionHandler, 
										SOCKETS_HandleDisconnection disconnectionHandler )
{

	return SOCKETS_ERROR;

}



SOCKETS_RESULT SERVER_NPIPE_Init()
{
	return SOCKETS_ERROR;
}


void SERVER_NPIPE_StopServer()
{

}

void SERVER_NPIPE_DisconnectClients()
{

}



void SERVER_NPIPE_Fini()
{

}

int SERVER_NPIPE_SendToClient( char* s, int len, SOCKETS_CLIENT_ID clientID )
{
	int res = 0;

	return res;
}


int SERVER_NPIPE_FindIDByHandle(LPPIPEINST lpPipeInst)
{

	return -1;
}
BOOL SERVER_NPIPE_CheckForClientDisconnection()
{
	BOOL clientDisconnected = FALSE;


	return clientDisconnected;
}
void SERVER_NPIPE_DisconnectClient( SOCKETS_CLIENT_ID clientID )
{

}
