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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

#include "wimax_osal_primitives.h"

#include "IPC_Client.h"
#include "TraceModule.h"

static SOCKETS_CLIENT_ID g_iClientID = 0;

SOCKETS_RESULT CLIENTS_SOCKETS_CreateNewClient(void *context,
					       SOCKETS_HandleData dataHandler,
					       SOCKETS_HandleDisconnection
					       disconnectionHandler,
					       SOCKETS_CLIENT_CONTEXT * client,
					       SOCKETS_CLIENT_ID * clientID)
{
	if(!client)
		return SOCKETS_ERROR;

	*client = (PCLIENT_DATA)malloc(sizeof(CLIENT_DATA));
	if( *client == NULL )
	{
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_ALERT, "malloc() failed");
		return SOCKETS_ERROR;
	}

	// Create the mutex
	if(OSAL_create_mutex(&((*((PCLIENT_DATA*)client))->hMutex),FALSE,NULL) != 0) {
		free(*client);
		*client = NULL;
		return SOCKETS_ERROR;
	}

	OSAL_atomic_increment(&g_iClientID);

	// Initialize the id
	// TODO - global mutex to protected readings of g_iClientID??
	*clientID = g_iClientID;
	(*(PCLIENT_DATA*)client)->id = *clientID;

	// Initialize the socket
	(*(PCLIENT_DATA*)client)->socket = 0;

	// Initialize the listening thread
	//Solving "CU crashes with a segmentation fault when there is no appsrv running."
	(*(PCLIENT_DATA*)client)->hListener = 0;

	// Set the context of the user to the client data
	(*(PCLIENT_DATA*)client)->context = context;

	if ( OSAL_create_event(&(*(PCLIENT_DATA*)client)->threadEvent, FALSE, FALSE, NULL) != 0)
	{
		free( *client );
		*client = NULL;
		return SOCKETS_SPECIAL_ERROR;
	}

	if ( OSAL_create_event(&(*(PCLIENT_DATA*)client)->quitEvent, TRUE, FALSE, NULL) != 0)
	{
		OSAL_delete_event((*(PCLIENT_DATA*)client)->threadEvent);
		free( *client );
		*client = NULL;
		return SOCKETS_SPECIAL_ERROR;
	}

	// Register the handlers
	(*(PCLIENT_DATA*)client)->handleData = dataHandler;
	(*(PCLIENT_DATA*)client)->handleDisconnection = disconnectionHandler;

	return SOCKETS_SUCCESS;
}



SOCKETS_RESULT CLIENTS_SOCKETS_Init(SOCKETS_CLIENT_CONTEXT * client,
				    SOCKETS_CLIENT_ID * clientID, void *context,
				    SOCKETS_HandleData dataHandler,
				    SOCKETS_HandleDisconnection
				    disconnectionHandler)
{
	SOCKETS_RESULT res;
	
	g_iClientID = 0;

	// Check the arguments
	if (client == NULL) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_CRITICAL, (L"Cannot init. Bad argument.");
		return SOCKETS_BAD_DATA;
	}
	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"start init");

	// Create the client
	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"creating a new client.");
	res =
	    CLIENTS_SOCKETS_CreateNewClient(context, dataHandler,
					    disconnectionHandler, client,
					    clientID);
	if (res != SOCKETS_SUCCESS) {
		return res;
	}
	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"finish init");
	return SOCKETS_SUCCESS;
}

void CLIENTS_SOCKETS_Fini(SOCKETS_CLIENT_CONTEXT * client)
{
	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"start fini");

	// Check the client
	if (client == NULL) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_WARNING, "Cannot CLIENTS_SOCKETS_Fini. Bad argument.");
		return;
	}
	if (*client == NULL) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_WARNING, "CLIENTS_SOCKETS_Fini already called.");
		return;
	}
	// Disconnect From Server - without using the mutex
	if (((*(PCLIENT_DATA*)client)->socket != 0)
	    && ((*(PCLIENT_DATA*)client)->socket != -1)) {
		// This will cause the thread to end
		close((*(PCLIENT_DATA*)client)->socket);
		(*(PCLIENT_DATA*)client)->socket = 0;
	}

	
	if ((*(PCLIENT_DATA*)client)->hListener) {
		// signal the quit event
		OSAL_set_event((*(PCLIENT_DATA*)client)->quitEvent);

		OSAL_sleep(50);

		if ( OSAL_timedjoin_thread((*(PCLIENT_DATA*)client)->hListener, SOCKET_SHUTDOWN_TIMEOUT, NULL) != 0 )
			OSAL_kill_thread((*(PCLIENT_DATA*)client)->hListener);
		(*(PCLIENT_DATA*)client)->hListener = 0;
	}

	if ((*(PCLIENT_DATA*)client)->hMutex != NULL )
		OSAL_delete_mutex((*(PCLIENT_DATA*)client)->hMutex);

	if((*(PCLIENT_DATA*)client)->threadEvent != NULL)
	{
		OSAL_delete_event((*(PCLIENT_DATA*)client)->threadEvent);
		(*(PCLIENT_DATA*)client)->threadEvent = NULL;
	}

	if((*(PCLIENT_DATA*)client)->quitEvent != NULL)
	{
		OSAL_delete_event((*(PCLIENT_DATA*)client)->quitEvent);
		(*(PCLIENT_DATA*)client)->quitEvent = NULL;
	}
	
	if(*client == NULL) {
		free(*client);
		*client = NULL;
	}

	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "finish fini");
}


void *CLIENTS_SOCKETS_Select(void *lpParameter)
{
	fd_set readFDs;
	char buf[MAX_DATA_SIZE] = { 0 };
	PCLIENT_DATA pdata = (PCLIENT_DATA)lpParameter;

	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "CLIENTS_SOCKETS_Select entered. lpParameter address = %x", lpParameter);

	OSAL_set_event(pdata->threadEvent);

	for (;;) {
		if(OSAL_wait_event(pdata->quitEvent, 0) == 0 ){
			//event is signaled - this means the thread should be killed...
			pdata->handleDisconnection(pdata->id, pdata->context);
			break;	
		}

		FD_ZERO(&readFDs);
		FD_SET(pdata->socket, &readFDs);

		if (select
		    (pdata->socket + 1, &readFDs, (fd_set *) 0, (fd_set *) 0,
		     NULL) == -1) {
			SOCKETS_RESULT res;

			OSAL_lock_mutex(pdata->hMutex);
			if (pdata->socket != 0) {
				TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_ALERT, "select() failed.");
				if (pdata->socket != -1) {
					close(pdata->socket);	// TODO - check result

				}
				pdata->socket = 0;
				res = SOCKETS_WSA_ERROR;
			} else {
				TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "The client disconnected.");
				res = SOCKETS_SUCCESS;
			}
			OSAL_unlock_mutex(pdata->hMutex);

			//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "Calling the disconnection handler.");
			if (pdata->handleDisconnection != NULL) {
				pdata->handleDisconnection(pdata->id,
							   pdata->context);
			}
			//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "Exiting the thread.");
			return (void *)res;	// thread function signature conformance
		}

		if (FD_ISSET(pdata->socket, &readFDs)) {
			int rv;
			// The only thing the main thread can change is the socket
			int readSock;
			OSAL_lock_mutex(pdata->hMutex);
			readSock = pdata->socket;
			OSAL_unlock_mutex(pdata->hMutex);

			rv = recv(readSock, buf, MAX_DATA_SIZE, 0);
			if (rv > 0) {
				TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "Received data from the server.");
				SOCKETS_Read(readSock, buf, rv,
					     pdata->handleData, pdata->id,
					     pdata->context);
			} else {
				TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "The client disconnected.");
				OSAL_lock_mutex(pdata->hMutex);
				if (pdata->socket != 0) {
					if (pdata->socket != -1) {
						close(pdata->socket);	// TODO - check result
					}
					pdata->socket = 0;
				}
				OSAL_unlock_mutex(pdata->hMutex);

				//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "Calling the disconnection handler.");
				if (pdata->handleDisconnection != NULL) {
					pdata->handleDisconnection(pdata->id,
								   pdata->
								   context);
				}
				//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, "Exiting the thread.");
				return (void *)SOCKETS_SUCCESS;
			}
		}
	}

	return (void *)SOCKETS_SUCCESS;
}

SOCKETS_RESULT CLIENTS_SOCKETS_ConnectToServer(char *host, unsigned short port,
					       SOCKETS_CLIENT_CONTEXT client)
{
	struct hostent *he;
	struct sockaddr_in addr;

	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"CLIENTS_SOCKETS_ConnectToServer entered.");
	// Check the arguments
	if (client == NULL) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_CRITICAL, "Cannot connect. Bad argument.");
		return SOCKETS_BAD_DATA;
	}

	OSAL_lock_mutex(((PCLIENT_DATA)client)->hMutex);

	// Create the socket for the client
	((PCLIENT_DATA)client)->socket =
	    socket(AF_INET, SOCK_STREAM, 0);
	if (((PCLIENT_DATA)client)->socket == -1) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_CRITICAL, (L"socket() failed.");
		((PCLIENT_DATA)client)->socket = 0;
		OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);
		return SOCKETS_WSA_ERROR;
	}
	if ((he = gethostbyname(host)) == 0) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_ALERT, (L"Cannot connect. gethostbyname failed(). error=%d",error);
		close(((PCLIENT_DATA)client)->socket);
		((PCLIENT_DATA)client)->socket = 0;
		OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);
		return SOCKETS_WSA_ERROR;
	}
	addr.sin_addr = *((struct in_addr *)he->h_addr);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	memset(&(addr.sin_zero), 0, 8);
	if (connect
	    (((PCLIENT_DATA)client)->socket, (struct sockaddr *)&addr,
	     sizeof(struct sockaddr_in))) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_ALERT, (L"Cannot connect. connect() failed. error=%d",error);
		close(((PCLIENT_DATA)client)->socket);
		((PCLIENT_DATA)client)->socket = 0;
		OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);
		return SOCKETS_WSA_ERROR;
	}

	if (  OSAL_create_thread( CLIENTS_SOCKETS_Select, client, &((PCLIENT_DATA)client)->hListener ) != 0 ) {
//		TRACE(0x00000040, 4,
//		      "Cannot init. CreateThread() failed. Unable to spawn the thread");
		return SOCKETS_SPECIAL_ERROR;
	}

	if(OSAL_wait_event(((PCLIENT_DATA)client)->threadEvent,1000)!=0){
		close(((PCLIENT_DATA)client)->socket);
		((PCLIENT_DATA)client)->socket = 0;
		OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);
		CLIENTS_SOCKETS_DisconnectFromServer(client);
		return SOCKETS_ERROR;
	}
	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"The client was connected successfully.");
	OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);
	return SOCKETS_SUCCESS;
}

void CLIENTS_SOCKETS_DisconnectFromServer(SOCKETS_CLIENT_CONTEXT client)
{
	// Check the client
	if (client == NULL || ((PCLIENT_DATA)client)->hMutex == NULL ) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_WARNING, (L"Cannot disconnect. Bad argument.");
		return;
	}
	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"Starting to disconnect the client.");

	OSAL_lock_mutex(((PCLIENT_DATA)client)->hMutex);
	
	if ((((PCLIENT_DATA)client)->socket != 0)
	    && (((PCLIENT_DATA)client)->socket != -1)) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"Stopping thread... . Client: %x", client);
		// This will cause the thread to end
		close(((PCLIENT_DATA)client)->socket);	// TODO - check result
		((PCLIENT_DATA)client)->socket = 0;
	}

	OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);

	//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_INFO, (L"The client was disconnected.");
}

int CLIENTS_SOCKETS_SendToServer(char *s, int len,
				 SOCKETS_CLIENT_CONTEXT client)
{
	int res = 0;
	int sendSock;

	// Check the client
	if (client == NULL) {
		//TRACE(TR_MOD_CLIENT_SOCKET, TR_SEV_WARNING, (L"Cannot send. Bad argument.");
		return res;
	}

	OSAL_lock_mutex(((PCLIENT_DATA)client)->hMutex);

	sendSock = ((PCLIENT_DATA)client)->socket;
	OSAL_unlock_mutex(((PCLIENT_DATA)client)->hMutex);

	return SOCKETS_Write(sendSock, s, len);
}

