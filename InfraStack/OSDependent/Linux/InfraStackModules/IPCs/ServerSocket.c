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
#include <unistd.h>
#include <fcntl.h>


#include <string.h>

#include "wimax_osal_primitives.h"
#include "IPC_Server.h"

static OSAL_mutex_t g_hServerListeningMutex;	// to protect g_ListeningSocket
static OSAL_thread_t g_hListener;
static int g_ListeningSocket = 0;
static OSAL_mutex_t g_hServerClientsMutex;	// to protect the sockets inside g_clientsData
static OSAL_event_t g_hThreadEvent;
static OSAL_event_t g_hQuitEvent;
static SERVER_CLIENT_DATA g_clientsData[MAX_SERVER_SOCKETS] =
    { 
	{ 0, 0, NULL }
    };

// Callbacks
static SOCKETS_HandleData g_pfHandleData = NULL;
static SOCKETS_HandleDisconnection g_pfHandleDisconnection = NULL;
static SERVER_SOCKETS_HandleNewConnection g_pfHandleNewConnection = NULL;
void SERVER_SOCKETS_DisconnectClients()
{
	int i;

	for (i = 0; i < MAX_SERVER_SOCKETS; i++) {
		if ((g_clientsData[i].socket != 0)
		    && (g_clientsData[i].socket != -1)) {
			close(g_clientsData[i].socket);	// TODO - check res
		}
		g_clientsData[i].socket = 0;

		// Only the socket can be changed from the main thread
		// so we don't need any mutex here
		if (g_clientsData[i].full) {
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Calling the client disconnection handler.");
			if (g_pfHandleDisconnection != NULL) {
				g_pfHandleDisconnection((SOCKETS_CLIENT_ID) i,
							g_clientsData[i].
							context);
			}

			g_clientsData[i].full = 0;
		}
	}
}

SOCKETS_RESULT SERVER_SOCKETS_Init()
{
	int i;

	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"start init");

	// Create the server mutexes

	if(OSAL_create_mutex(&g_hServerListeningMutex,FALSE,NULL) != 0) {
		return SOCKETS_ERROR;
	}

	if(OSAL_create_mutex(&g_hServerClientsMutex,FALSE,NULL) != 0) {
		return SOCKETS_ERROR;
	}

	if ( OSAL_create_event(&g_hThreadEvent, FALSE, FALSE, NULL) != 0)
	{
		return SOCKETS_SPECIAL_ERROR;
	}

	if ( OSAL_create_event(&g_hQuitEvent, TRUE, FALSE, NULL) != 0)
	{
	        return SOCKETS_SPECIAL_ERROR;
	}

	OSAL_lock_mutex(g_hServerClientsMutex);

	// Initialize the clients data
	for (i = 0; i < MAX_SERVER_SOCKETS; i++) {
		g_clientsData[i].full = 0;
		g_clientsData[i].context = NULL;
		g_clientsData[i].socket = 0;
	}
	OSAL_unlock_mutex(g_hServerClientsMutex);

	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"finish init");
	return SOCKETS_SUCCESS;
}

void SERVER_SOCKETS_Fini()
{
	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"start fini");

	// These two lines are just to make sure...
	SERVER_SOCKETS_StopServer();
	SERVER_SOCKETS_DisconnectClients();

	// Split the incoming millisecs into seconds and nano-seconds struct as required by the timedjoin method

	// Closing the thread handle
	if (g_hListener) {
		// signal the quit event
		OSAL_set_event(g_hQuitEvent);
		if ( OSAL_timedjoin_thread(g_hListener, SOCKET_SHUTDOWN_TIMEOUT, NULL) != 0 )
			OSAL_kill_thread(g_hListener);
		g_hListener = 0;
	}

	if(g_hThreadEvent != NULL)
	{
		OSAL_delete_event(g_hThreadEvent);
	}

	if(g_hQuitEvent != NULL)
        {
	        OSAL_delete_event(g_hQuitEvent);
        }

	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"finish fini");
}

// If a client disconnected calls the disconnection handler.
int SERVER_SOCKETS_CheckForClientDisconnection()
{
	int i;
	int clientDisconnected = 0;

	for (i = 0; i < MAX_SERVER_SOCKETS; i++) {
		int callDisconnectionHandler = 0;

		OSAL_lock_mutex(g_hServerClientsMutex);
		if ((g_clientsData[i].socket == 0) && (g_clientsData[i].full)) {
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"A client was disconnected.");
			clientDisconnected = 1;
			callDisconnectionHandler = 1;
		}
		OSAL_unlock_mutex(g_hServerClientsMutex);

		if (callDisconnectionHandler) {
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Calling the client disconnection handler.");
			if (g_pfHandleDisconnection != NULL) {
				g_pfHandleDisconnection((SOCKETS_CLIENT_ID) i,
							g_clientsData[i].
							context);
			}
			g_clientsData[i].full = 0;
		}
	}

	return clientDisconnected;
}
SOCKETS_RESULT SERVER_SOCKETS_EndListeningThread()
{
	SOCKETS_RESULT res;

	OSAL_lock_mutex(g_hServerListeningMutex);
	if (g_ListeningSocket == 0) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"The server was stopped.");
		res = SOCKETS_SUCCESS;
	} else {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, (L"failure... Please call StopServer.");
		if (g_ListeningSocket != -1) {
			close(g_ListeningSocket);	// TODO - check res
		}
		g_ListeningSocket = 0;
		res = SOCKETS_WSA_ERROR;
	}
	OSAL_unlock_mutex(g_hServerListeningMutex);

	return res;
}

void *SERVER_SOCKETS_Select(void* lpParameter )
{
	int i;
	fd_set readFDs;
	char buf[MAX_DATA_SIZE] = { 0 };
	void *context;
	int newSock;
	int max_sock = -1;
	int ret; 

	UNREFERENCED_PARAMETER(lpParameter);

	OSAL_set_event(g_hThreadEvent);

	for (;;) {

		// @@@ : 5/28/09 : JSS - since this a loop it can create conditions for a tight loop
		// and we should allow it to exit if the event being waited up comes back as being invalid
		if( ( (ret = OSAL_wait_event(g_hQuitEvent, 0)) == 0) || ( ret != WAIT_TIMEOUT) ){
			//event is signaled - this means the thread should be killed...
			SERVER_SOCKETS_EndListeningThread();
			break;	
		}

		// prepare the select arguments
		OSAL_lock_mutex(g_hServerListeningMutex);
		FD_ZERO(&readFDs);
		FD_SET(g_ListeningSocket, &readFDs);
		max_sock = g_ListeningSocket;
		OSAL_unlock_mutex(g_hServerListeningMutex);

		OSAL_lock_mutex(g_hServerClientsMutex);
		for (i = 0; i < MAX_SERVER_SOCKETS; i++) {
			if (g_clientsData[i].full) {
				FD_SET(g_clientsData[i].socket, &readFDs);
				if (g_clientsData[i].socket > max_sock)
					max_sock = g_clientsData[i].socket;
			}
		}
		OSAL_unlock_mutex(g_hServerClientsMutex);

		if (select
		    (max_sock + 1, &readFDs, (fd_set *) 0, (fd_set *) 0,
		     NULL) == -1) {
			int clientDisconnected =
			    SERVER_SOCKETS_CheckForClientDisconnection();
			//int errorCode = WSAGetLastError();
			if (clientDisconnected) {
				continue;
			}
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Exiting the thread.");
			return (void *)SERVER_SOCKETS_EndListeningThread();
		}

		// add a new client or close the listening socket
		if (FD_ISSET(g_ListeningSocket, &readFDs)) {
			newSock = accept(g_ListeningSocket, 0, 0);
			if (newSock == -1) {
				//int errorCode = WSAGetLastError();
				// TODO - check what happens if the client connected and then disconnected will the accept fail??
				//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Exiting the thread.");
				return (void *)SERVER_SOCKETS_EndListeningThread();
			}

#if 1
			// Attempt to set this flag on the new socket to prevent it from being inheritted
			// by any children inadvarently like the dhclient in our case...
			fcntl(newSock, F_SETFD, FD_CLOEXEC);
#endif

			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"A client was trying to connect");
			for (i = 0; i < MAX_SERVER_SOCKETS; i++) {
				if (!g_clientsData[i].full) {
					//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"A new client accepted.");
					// initialize the new client data
					OSAL_lock_mutex
					    (g_hServerClientsMutex);
					g_clientsData[i].full = 1;
					g_clientsData[i].socket = newSock;
					g_clientsData[i].context = NULL;
					OSAL_unlock_mutex
					    (g_hServerClientsMutex);

					//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Calling the new connection handler.");
					if (g_pfHandleNewConnection != NULL) {
						g_pfHandleNewConnection((SOCKETS_CLIENT_ID) i, &context);
						g_clientsData[i].context =
						    context;
					}
					break;
				}
			}

			if (i == MAX_SERVER_SOCKETS) {
				//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_WARNING, (L"Cannot listen to the new client because MAX_SERVER_SOCKETS clients are already connected.");
				close(newSock);	// TODO - check result
			}
		}
		// Get data from clients
		for (i = 0; i < MAX_SERVER_SOCKETS; i++) {
			if (FD_ISSET(g_clientsData[i].socket, &readFDs)) {
				int rv;
				// The only thing the main thread can change is the socket
				int readSock;
				OSAL_lock_mutex(g_hServerClientsMutex);
				readSock = g_clientsData[i].socket;
				OSAL_unlock_mutex(g_hServerClientsMutex);

				rv = recv(g_clientsData[i].socket, buf,
					  MAX_DATA_SIZE, 0);
				if (rv > 0) {
					//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Received data from a client.");
					SOCKETS_Read(readSock, buf, rv,
						     g_pfHandleData,
						     (SOCKETS_CLIENT_ID) i,
						     g_clientsData[i].context);
				} else {
					//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"A client disconnected.");
					OSAL_lock_mutex
					    (g_hServerClientsMutex);
					if (g_clientsData[i].socket != 0) {
						if (g_clientsData[i].socket !=
						    -1) {
							close(g_clientsData[i].socket);	// TODO - check result
						}
						g_clientsData[i].socket = 0;
					}
					OSAL_unlock_mutex
					    (g_hServerClientsMutex);

					//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Calling the client disconnection handler.");
					if (g_pfHandleDisconnection != NULL) {
						g_pfHandleDisconnection((SOCKETS_CLIENT_ID) i, g_clientsData[i].context);
					}
					g_clientsData[i].full = 0;
				}
			}
		}
	}

	return 0;
}

SOCKETS_RESULT SERVER_SOCKETS_StartServer(unsigned int port,
					  SOCKETS_HandleData dataHandler,
					  SERVER_SOCKETS_HandleNewConnection
					  newConnectionHandler,
					  SOCKETS_HandleDisconnection
					  disconnectionHandler)
{
	struct sockaddr_in sa;
	int yes = 1;

	if (g_ListeningSocket != 0) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_WARNING, (L"Cannot start the server. Already started.");
		return SOCKETS_SPECIAL_ERROR;
	}
	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Starting the server");

	OSAL_unlock_mutex(g_hServerListeningMutex);

	// Register the handlers
	g_pfHandleData = dataHandler;
	g_pfHandleNewConnection = newConnectionHandler;
	g_pfHandleDisconnection = disconnectionHandler;

	// Create the socket
	g_ListeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (g_ListeningSocket == -1) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, (L"Cannot start the server. socket() failed.");
		g_ListeningSocket = 0;
		OSAL_unlock_mutex(g_hServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}
	// Set socket options as reusable socket
	if (setsockopt(g_ListeningSocket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, (L"Cannot Set socket options failed.");
   	 	g_ListeningSocket = 0;
		OSAL_unlock_mutex(g_hServerListeningMutex);
    		return SOCKETS_WSA_ERROR;
	} 


#if 1
	// Testing functionality to disable inheritance of the socket by child processes
	fcntl(g_ListeningSocket, F_SETFD, FD_CLOEXEC);

#endif 
	// Bind the socket to the internet address
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = PF_INET;
	sa.sin_port = htons(port);
	if (bind
	    (g_ListeningSocket, (struct sockaddr *)&sa,
	     sizeof(struct sockaddr_in)) == -1) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, (L"Cannot start the server. bind() failed.");
		close(g_ListeningSocket);
		g_ListeningSocket = 0;
		OSAL_unlock_mutex(g_hServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}
	// Make the socket a listening socket
	if (listen(g_ListeningSocket, SOMAXCONN * 3) != 0) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, (L"Cannot start the server. listen() failed.");
		close(g_ListeningSocket);
		g_ListeningSocket = 0;
		OSAL_unlock_mutex(g_hServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}

	if (  OSAL_create_thread( SERVER_SOCKETS_Select, NULL, &g_hListener ) != 0 ) {
//		TRACE(0x00000040, 4,
//		      "Cannot init. CreateThread() failed. Unable to spawn the thread");
		return SOCKETS_SPECIAL_ERROR;
	}

	if(OSAL_wait_event(g_hThreadEvent,1000)!=0){
		g_hListener = (pthread_t) 0;
		close(g_ListeningSocket);
		g_ListeningSocket = 0;
		OSAL_unlock_mutex(g_hServerListeningMutex);
		SERVER_SOCKETS_StopServer();
		return SOCKETS_ERROR;
	}

	OSAL_unlock_mutex(g_hServerListeningMutex);
	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"The server was started successfully.");
	return SOCKETS_SUCCESS;
}

void SERVER_SOCKETS_StopServer()
{
	// Check that init was called successfully
	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Stoping the server");

	OSAL_lock_mutex(g_hServerListeningMutex);

	g_pfHandleData = NULL;
	g_pfHandleNewConnection = NULL;
	g_pfHandleDisconnection = NULL;

	if (g_ListeningSocket != 0) {
		
		if (shutdown(g_ListeningSocket, 2) == -1) {
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, "Failed to shutdown to sever socket");
		}
		// This will cause the thread to end
		if(close(g_ListeningSocket) == -1) {
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_ALERT, "Failed to close to sever socket");
		}
		g_ListeningSocket = 0;

	}
	OSAL_unlock_mutex(g_hServerListeningMutex);

	// We will verify that the thread is close by calling wmxTerminateThread only in the 
	// shutdown function to allow other threads to continue working with the mutex until total shutdown
	// (After calling terminate the mutex state is undefined)
	// Its o.k. if the thread will continue to work until that time as long as the socket is closed


	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"The server was stopped successfully.");
}

int SERVER_SOCKETS_SendToClient(char *s, int len, SOCKETS_CLIENT_ID clientID)
{
	int res = 0;
	int sendSock;

	// Check the clientID
	if ((clientID < 0) || (clientID > MAX_SERVER_SOCKETS)) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_WARNING, (L"Cannot disconnect client. Bad argument.");
		return res;
	}
	// Check that init was called successfully
	OSAL_lock_mutex(g_hServerClientsMutex);
	sendSock = g_clientsData[clientID].socket;
	OSAL_unlock_mutex(g_hServerClientsMutex);

	return SOCKETS_Write(sendSock, s, len);
}

void SERVER_SOCKETS_DisconnectClient(SOCKETS_CLIENT_ID clientID)
{
	// Check the clientID
	if ((clientID < 0) || (clientID > MAX_SERVER_SOCKETS) || g_hServerClientsMutex == NULL ) {
		//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_WARNING, (L"Cannot disconnect client. Bad argument.");
		return;
	}
	// Check that init was called successfully
	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Disconnecting client");
	OSAL_lock_mutex(g_hServerClientsMutex);

	if ((g_clientsData[clientID].socket != 0)
	    && (g_clientsData[clientID].socket != -1)) {
		close(g_clientsData[clientID].socket);	// TODO - check result
	}
	g_clientsData[clientID].socket = 0;

	OSAL_unlock_mutex(g_hServerClientsMutex);
}

