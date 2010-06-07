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
#include <fcntl.h>
#include <netinet/in.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
#include "CommonServices.h"

#include "wimax_osal_primitives.h"

#include <string.h>
//#pragma warning(disable : 4127) //FD_SET causing warning C4127: conditional expression is constant

#include "DnDServerSocket.h"
#include "TraceModule.h"

static OSAL_mutex_t g_hDnDServerListeningMutex = NULL;
static OSAL_thread_t g_hDnDListener;
static int g_DnDListeningSocket = 0;
static OSAL_mutex_t g_hDnDServerClientsMutex = NULL;

// Added for named pipes

#define TIMEVAL_TO_TIMESPEC(tv, ts)	{	\
	(ts)->tv_sec = (tv)->tv_sec;	\
	(ts)->tv_nsec = (tv)->tv_usec * 1000; 	\
}
// Current windows client socket
int g_windows_dsim_sock = 0;
// Prevoius windows socket client
int previous_socket_client = 0;
#define printf(format,args...)



static SOCKETS_HandleDisconnection g_pfHandleDisconnection = NULL;
static SERVER_SOCKETS_HandleNewConnection g_pfHandleNewConnection = NULL;



SOCKETS_RESULT DND_SERVER_SOCKETS_Init()
{

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "start init");

	// Create the server mutexes

	/* 
	   pthread_mutexattr_t mtxAttr;

	   if (pthread_mutexattr_init(&mtxAttr) != 0) {
	   return SOCKETS_ERROR;
	   }
	   // Set type appropriate for windows style semantics for Mutexes
	   pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_RECURSIVE_NP);

	   if (pthread_mutex_init(&g_hDnDServerListeningMutex, &mtxAttr) != 0) {
	   pthread_mutexattr_destroy(&mtxAttr);
	   return SOCKETS_ERROR;

	   }
	   pthread_mutexattr_destroy(&mtxAttr);

	 */
	if (OSAL_create_mutex(&g_hDnDServerListeningMutex, 0, NULL) < 0) {
		return SOCKETS_ERROR;
	}
	/*
	   pthread_mutexattr_t mtxAttr1;

	   if (pthread_mutexattr_init(&mtxAttr1) != 0) {
	   return SOCKETS_ERROR;
	   }
	   // Set type appropriate for windows style semantics for Mutexes
	   pthread_mutexattr_settype(&mtxAttr1, PTHREAD_MUTEX_RECURSIVE_NP);

	   if (pthread_mutex_init(&g_hDnDServerClientsMutex, &mtxAttr1) != 0) {
	   pthread_mutexattr_destroy(&mtxAttr1);
	   return SOCKETS_ERROR;

	   }

	 */
	if (OSAL_create_mutex(&g_hDnDServerClientsMutex, 0, NULL) < 0) {
		return SOCKETS_ERROR;
	}

	previous_socket_client = 0;
	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "finish init");
	return SOCKETS_SUCCESS;
}

void DND_SERVER_SOCKETS_Fini()
{
	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "start fini");

	// These two lines are just to make sure...

	// void *status;
// 	struct timespec ts;
// 	struct timeval tv;

	// printf("DND_SERVER_SOCKETS_Fini called \n");

	DND_SERVER_SOCKETS_DisconnectClient();
	// printf("DND_SERVER_SOCKETS_DisconnectClient Server stopped \n");
	DND_SERVER_SOCKETS_StopServer();

	// printf("DND_SERVER_SOCKETS_Fini Server stopped \n");

	//gettimeofday(&tv, NULL);
	// TIMEVAL_TO_TIMESPEC(&tv, &ts);

	// Split the incoming millisecs into seconds and nano-seconds struct as required by the timedjoin method

// 	ts.tv_sec += (SOCKET_SHUTDOWN_TIMEOUT / 1000);
// 	ts.tv_nsec += ((SOCKET_SHUTDOWN_TIMEOUT % 1000) * 1000 * 1000);	// 1 ms = 1000000 ns
// 	if (ts.tv_nsec >= 1000000000) {
// 		ts.tv_nsec -= 1000000000;
// 		++ts.tv_sec;
// 	}
	/*
	   if (g_hDnDListener)
	   pthread_timedjoin_np(g_hDnDListener, &status, &ts);

	   void *thread_return;
	   if (g_hDnDListener) {
	   pthread_tryjoin_np(g_hDnDListener, &thread_return);
	   pthread_cancel(g_hDnDListener);
	   } 
	 */
	if (g_hDnDListener)
		if (OSAL_timedjoin_thread(g_hDnDListener, SHUTDOWN_TIMEOUT, NULL)
		    != 0)
			OSAL_kill_thread(g_hDnDListener);
	g_hDnDListener = 0;

	OSAL_delete_mutex(g_hDnDServerClientsMutex);
	OSAL_delete_mutex(g_hDnDServerListeningMutex);
	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "finish fini");
}
void *DND_SERVER_SOCKETS_Select(void *lpParameter)
{

	int sock_client = 0;
	void *context = NULL;		// dummy

	UNREFERENCED_PARAMETER(lpParameter);


	for (;;) {

		// add a new client or close the listening socket
		//if (FD_ISSET(g_DnDListeningSocket, &readFDs)) {

		OSAL_lock_mutex(g_hDnDServerListeningMutex);

		if (g_DnDListeningSocket == 0) {
			OSAL_unlock_mutex(g_hDnDServerListeningMutex);
			return (void *)0;	//SOCKETS_SUCCESS;
		}

		// printf("DND Windows DSIM socket - Accepting new connection \n");
		// if (g_windows_dsim_sock == 0) 
		{
			sock_client = accept(g_DnDListeningSocket, 0, 0);
			// accpet returns -1 on error
			if (sock_client ==  -1) {
				//int errorCode = WSAGetLastError();
			// TODO - check what happens if the client connected and then disconnected will the accept fail??
			//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Exiting the thread.");
			//return (void *)SERVER_SOCKETS_EndListeningThread();
				DND_SERVER_SOCKETS_StopServer();
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Problem in accepting new connection Server Closed");
				OSAL_unlock_mutex(g_hDnDServerListeningMutex);
				printf("Accepting new connection failed \n");
			return (void *)0;	//SOCKETS_ERROR;
			} else {
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "New Connection accepted");
#if 1
			// Attempt to set this flag on the new socket to prevent it from being inheritted
			// by any children inadvarently like the dhclient in our case...
			fcntl(sock_client, F_SETFD, FD_CLOEXEC);
#endif
		printf("New Connection Accepted\n");
				OSAL_lock_mutex(g_hDnDServerClientsMutex);
				if (previous_socket_client != 0)
				{
					// Be careful mow you are holding g_hDnDServerListeningMutex
					TRACE(TR_MOD_DND_AGENT, TR_SEV_CRITICAL, "Closing prev sock connection attempt");
					shutdown(previous_socket_client, 2);
					close(previous_socket_client);
					// There is a reattempt from windows so close the prevoius sock connection
				}
				g_windows_dsim_sock = sock_client;
				previous_socket_client = sock_client;;
				OSAL_unlock_mutex(g_hDnDServerClientsMutex);
					
				if (g_pfHandleNewConnection != NULL) 
						g_pfHandleNewConnection((SOCKETS_CLIENT_ID) sock_client, &context);
			}
		}
		OSAL_unlock_mutex(g_hDnDServerListeningMutex);

	}
	//}

	return (void *)0;	//SOCKETS_SUCCESS;
}

SOCKETS_RESULT DND_SERVER_SOCKETS_StartServer(unsigned int port,
					  SOCKETS_HandleData dataHandler,
					  SERVER_SOCKETS_HandleNewConnection
					  newConnectionHandler,
					  SOCKETS_HandleDisconnection
					  disconnectionHandler)
{
	struct sockaddr_in sa;
	int yes = 1;
	struct linger ln;
	int size;

	if (g_DnDListeningSocket != 0) {
		TRACE (TR_MOD_DND_AGENT, TR_SEV_WARNING, "Cannot start the server. Already started.");
		printf("Cannot start the server. Already started. \n");
		return SOCKETS_SUCCESS;
	}

	g_pfHandleNewConnection = newConnectionHandler;
	g_pfHandleDisconnection = disconnectionHandler;

	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Starting the server");

	OSAL_lock_mutex(g_hDnDServerListeningMutex);

	// Create the socket
	g_DnDListeningSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (g_DnDListeningSocket == -1) {
		TRACE (TR_MOD_DND_AGENT, TR_SEV_ALERT, "Cannot start the server. socket() failed.");
		printf("Cannot start the server. socket() failed \n");
		g_DnDListeningSocket = 0;
		OSAL_unlock_mutex(g_hDnDServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}
	printf("Setting socket options socket no %d port %d\n",
	       g_DnDListeningSocket, port);
	if (setsockopt
	    (g_DnDListeningSocket, SOL_SOCKET, SO_REUSEADDR, &yes,
	     sizeof(int)) == -1) {
		printf("Error in setting the sock options \n");
		g_DnDListeningSocket = 0;
		OSAL_unlock_mutex(g_hDnDServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}
	ln.l_onoff = 1;
	ln.l_linger = 1;

	if (setsockopt
	    (g_DnDListeningSocket, SOL_SOCKET, SO_LINGER, (char *)&ln,
	     sizeof(struct linger)) == -1) {
		printf("Error in setting the sock options \n");
		TRACE (TR_MOD_DND_AGENT, TR_SEV_ALERT, "Can't start the server Error in setting sock options ");
		g_DnDListeningSocket = 0;
		OSAL_unlock_mutex(g_hDnDServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}
	size = sizeof(int);
	getsockopt(g_DnDListeningSocket, SOL_SOCKET, SO_REUSEADDR, &yes,
		   (socklen_t *) & size);
	if (yes != 0) {
		printf("SO_REUSEADDR enabled on g_ListeningSocket!\n");
	}

	getsockopt(g_DnDListeningSocket, SOL_SOCKET, SO_LINGER, &yes,
		   (socklen_t *) & size);
	if (yes != 0) {
		printf("SO_REUSEADDR enabled on g_ListeningSocket!\n");
	}

#if 1
	// Testing functionality to disable inheritance of the socket by child processes
	fcntl(g_DnDListeningSocket, F_SETFD, FD_CLOEXEC);
#endif

	// Bind the socket to the internet address
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = PF_INET;
	sa.sin_port = htons(port);
	if (bind
	    (g_DnDListeningSocket, (struct sockaddr *)&sa,
	     sizeof(struct sockaddr_in)) == -1) {
		TRACE (TR_MOD_DND_AGENT, TR_SEV_ALERT, "Cannot start the server. bind() failed.");
		printf("Cannot start the server. bind() failed \n");
		close(g_DnDListeningSocket);
		g_DnDListeningSocket = 0;
		OSAL_unlock_mutex(g_hDnDServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}
	// Make the socket a listening socket
	if (listen(g_DnDListeningSocket, SOMAXCONN * 3) != 0) {
		TRACE (TR_MOD_DND_AGENT, TR_SEV_ALERT, "Cannot start the server. listen() failed.");
		printf("Cannot start the server. listen() failed \n");
		close(g_DnDListeningSocket);
		g_DnDListeningSocket = 0;
		OSAL_unlock_mutex(g_hDnDServerListeningMutex);
		return SOCKETS_WSA_ERROR;
	}

	/*
	   pthread_attr_t threadattr;

	   if (pthread_attr_init(&threadattr) != 0) {
	   return SOCKETS_SPECIAL_ERROR;
	   }

	   int retval =
	   pthread_create(&g_hDnDListener, &threadattr, DND_SERVER_SOCKETS_Select, NULL);
	 */
	int retVal =
	    OSAL_create_thread(DND_SERVER_SOCKETS_Select, NULL, &g_hDnDListener);


	if (retVal != 0) {
		TRACE (TR_MOD_DND_AGENT, TR_SEV_ALERT, "Could not start server - Unable to create the Listening thread");
		printf("Could not start server - Unable to create the Listening thread \n");
		close(g_DnDListeningSocket);
		g_DnDListeningSocket = 0;
		return SOCKETS_SPECIAL_ERROR;
	}
	OSAL_unlock_mutex(g_hDnDServerListeningMutex);
	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "The server was started successfully.");
	return SOCKETS_SUCCESS;
}

void DND_SERVER_SOCKETS_StopServer()
{
	// Check that init was called successfully
	//TRACE(TR_MOD_SERVER_SOCKET, TR_SEV_INFO, (L"Stoping the server");

	// OSAL_lock_mutex(g_hDnDServerListeningMutex);

	if (g_DnDListeningSocket != 0) {
		// This will cause the thread to end
		printf("Closing g_DnDListeningSocket \n");
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "The Socket server is stopped");
		shutdown(g_DnDListeningSocket, 2);
		close(g_DnDListeningSocket);	// TODO - check result
		g_DnDListeningSocket = 0;

	}
	// OSAL_unlock_mutex(g_hDnDServerListeningMutex);

	// We will verify that the thread is close by calling wmxTerminateThread only in the 
	// shutdown function to allow other threads to continue working with the mutex until total shutdown
	// (After calling terminate the mutex state is undefined)
	// Its o.k. if the thread will continue to work until that time as long as the socket is closed

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "The server was stopped successfully.");
}

int DND_SERVER_SOCKETS_SendToClient(char *buf, int len, int socket_id)
{
	int res = 0;
	//#define MAX_DATA_SIZE 8232
#define STATUS_INTEL_80216_CUSTOM	( 0x20000000 )	// Custom status has "1" on 29h bit
	char retMsg[MAX_DATA_SIZE];
	//int bytesSent;


	if ((buf == NULL) || (len == 0)) {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Cannot send. Invalid Data input.");
		return SOCKETS_ERROR;
	}
	if (socket_id == 0) {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Cannot send. Invalid socket.");
		return SOCKETS_ERROR;
	}
	if (len > MAX_DATA_SIZE) {
		//TRACE(TR_MOD_COMMON_SOCKET, TR_SEV_WARNING, (L"Cannot send. Invalid message length: %d, range: 1-%d", len, MAX_DATA_SIZE);
		return SOCKETS_ERROR;
	}
	// Check that init was called successfully
	OSAL_lock_mutex(g_hDnDServerClientsMutex);

#if 0

	//set the length of the message starting from the field following the length field
	*((UINT32 *) retMsg) = len + 4;

	//set OID opcode
	*((UINT32 *) & retMsg[4]) = STATUS_INTEL_80216_CUSTOM;	//the driver sends with 4 extra bytes
	OSAL_memcpy_s(retMsg + 8, MAX_DATA_SIZE, buf, len);
#endif

	if (socket_id != 0) {
		TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "About to send on socket: %d, size: %d, socket from DnD is %d.", g_windows_dsim_sock, len, socket_id);
#if 1
		res = send(g_windows_dsim_sock, buf, len, 0);
#else
		res = send(g_windows_dsim_sock, retMsg, len + 8, 0);
#endif
		if (res < 0) {
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Could not send to the Windows Client");
		printf("Could not send to the Windows DSIM Client \n");
		DND_SERVER_SOCKETS_DisconnectClient();
		OSAL_unlock_mutex(g_hDnDServerClientsMutex);
		return SOCKETS_ERROR;
	}
	}
	printf ("$$$$$$$$$$$$$$$$$$$$$$$$$$$ Sending Data to windows DSIM client \n");
	OSAL_unlock_mutex(g_hDnDServerClientsMutex);
	return res;
}

// This function should be called holding g_hDnDServerClientsMutex
void DND_SERVER_SOCKETS_DisconnectClient()
{
	// OSAL_lock_mutex(g_hDnDServerListeningMutex);

	if (g_windows_dsim_sock != 0) {
		printf("Closing g_windows_dsim_sock \n");
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "Disconnecting the Windows Client");
		shutdown(g_windows_dsim_sock, 2);
		close(g_windows_dsim_sock);	// TODO - check result


		if (g_pfHandleDisconnection != NULL )
			g_pfHandleDisconnection (g_windows_dsim_sock, NULL);

		g_windows_dsim_sock = 0;
		previous_socket_client = 0;
	}
	// OSAL_unlock_mutex(g_hDnDServerListeningMutex);
}
