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

//////////////////////////////////////////////////////////////////////////
// Headers

// OSAL
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "L4ConfigurationManager.h"

// Project
#include "L5SocketsDispatcher.h"
#include "L5Dispatcher.h"

#include "CommonServices.h"
#include "L5Common.h"
#include "L5CommonUtils.h"
#include "TraceModule.h"

#include "IPC_Common.h"
#include "IPC_Server.h"

//////////////////////////////////////////////////////////////////////////
// Typedefs

/* This structure describes a single sockets connection. It contains a
 * a socket and a L5_CONNECTION. The L5_CONNECTION is only established after
 * a successful handshake message is received.
 */
typedef struct
{
	L5_CONNECTION L5Conn;			// Can be NULL before handshake

	// Is this an active slot?
	BOOL bActive;

	// Connections from both sides
	SOCKETS_CLIENT_ID Socket;
	PIPE_CLIENT_ID PipeID;

	////////////////////////////////////////
	// Reply
	tL5ExpectedReplyMessageParams tExpectedReply;

	BOOL bResourcesAllocated;

	/* The following event is used to wakeup the thread waiting for a reply
	 * IMPORTANT NOTE: The handle may be valid even if the connection itself is
	 * invalid (bActive == FALSE). This is done to eliminate the creation of events
	 * again and again. This is signified by the bResourcesAllocated flag.
	 */
	OSAL_event_t hReplyAvailableEvent;
	OSAL_event_t hStopWaitingForReplyEvent;

	////////////////////////////////////////
	// Request
	tL5Message *pRequestMessage;

	// Lock
	OSAL_critical_section csSendReceive;
	OSAL_critical_section csHandlingRequest; 

	// Disconnection
	BOOL bDisconnected;

} tL5SocketsDispatcherConnection;

//////////////////////////////////////////////////////////////////////////
// Global variables

// Our connections
static tL5SocketsDispatcherConnection g_atSocketConnections[L5_DISPATCHER_MAX_CONNECTIONS];

// Sequential number
static UINT32 g_dwCurrentSequentialNumber;

/////////////////////////////////////
// Reply message

// The reply message and reply result
static tL5Message *g_pReplyMessage;
static L5_RESULT g_ReplyResult;

// Did the 'waiting for reply' thread ended handling the reply?
static OSAL_event_t g_hReplyHandledEvent;

// Request Handling Thread related
static OSAL_event_t g_hRequestAvailableEvent;
static OSAL_thread_t g_hRequestHandlingThread = NULL;
static OSAL_event_t g_hStopRequestHandlingThreadEvent;

static BOOL useNPIPE = FALSE;
static BOOL isStarted = FALSE;
//////////////////////////////////////////////////////////////////////////
// Prototypes

// Handlers
void l5_sockets_dispatcher_HandleData( char* bBuffer, int nSize, SOCKETS_CLIENT_ID Socket, void* context );
void l5_sockets_dispatcher_HandleNewConnection( SOCKETS_CLIENT_ID Socket, void** context );
void l5_sockets_dispatcher_HandleDisconnection( SOCKETS_CLIENT_ID Socket, void* context );

void l5_sockets_dispatcher_HandleControlMessage(	tL5Message *pReceivedMessage, tL5SocketsDispatcherConnection *pSourceConn, SOCKETS_CLIENT_ID Socket );
void l5_sockets_dispatcher_HandleRequestMessage(	tL5Message *pReceivedMessage, tL5SocketsDispatcherConnection *pConn, SOCKETS_CLIENT_ID Socket );
void l5_sockets_dispatcher_HandleReplyMessage(		tL5Message *pReceivedMessage, tL5SocketsDispatcherConnection *pConn, SOCKETS_CLIENT_ID Socket );

void l5_sockets_dispatcher_DirectMessageHandler( 
	L5_CONNECTION Conn,
	L5_TARGET_ID nOriginID,

	UINT32 dwSentMessageID,
	void  *pvSentBuffer,
	UINT32 cbSentBufferSize,

	UINT32 *pdwResponseMessageID,
	void  *pvResponseBuffer,
	UINT32 *cbResponseBufferSize,

	void *pvUserContext,
	void *pvReserved );

void l5_sockets_dispatcher_EventHandler( 
										L5_CONNECTION Conn,
										L5_EVENT eEvent,
										void *pvEventData,
										void *pvUserContext );
// Utilities
tL5SocketsDispatcherConnection *l5_sockets_dispatcher_FindAvailableConnection( void );
void l5_sockets_dispatcher_DisconnectClient( tL5SocketsDispatcherConnection *pConn, L5_RESULT Reason );
void l5_sockets_dispatcher_ReturnReply( tL5SocketsDispatcherConnection *pConn, tL5Message *ptMessage, L5_RESULT Result );

// Request Handling Thread
void l5_sockets_dispatcher_RequestHandlingThread( LPVOID lpParam );
void l5_sockets_dispatcher_ActuallySendReply( 
	tL5Message *pReplyMessage, 
	SOCKETS_CLIENT_ID socket );
tL5Message * l5_sockets_dispatcher_ActuallyHandleRequestMessage(tL5Message *pReplyMessage,tL5Message *pReceivedMessage,
																tL5SocketsDispatcherConnection *pSourceConn );

/********************************************************************
 * Function: L5_SOCKETS_DISPATCHER_Initialize
 *******************************************************************/
void L5_Socket_Dispatcher_BroadcastControlMsg(UINT32 msgId)
{
	int i = 0;
	L5_RESULT Result = L5_RESULT_OK;
	SOCKETS_CLIENT_ID tempSock;

	while (g_atSocketConnections[i].bActive)
	{
		tempSock = g_atSocketConnections[i].Socket;

		// Send the message
		Result = L5_COMMON_UTILS_SendControlMessage(tempSock, msgId, 
			((tL5DispatcherConnection*)((g_atSocketConnections[i].L5Conn)))->nTargetID, L5_RESULT_OK);
		i++;
	}
}
BOOL L5_SOCKETS_DISPATCHER_Initialize()
{
	int i;
	char answer[MAX_ANSWER_SIZE];
	BOOL res;

	// Initialize globals
	OSAL_create_event( &g_hReplyHandledEvent , FALSE, FALSE, NULL );
	if( NULL == g_hReplyHandledEvent )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: Create ReplyHandledEvent - Failed!");
		return FALSE;
	}

	OSAL_create_event( &g_hRequestAvailableEvent , FALSE, FALSE, NULL );
	if( NULL == g_hRequestAvailableEvent )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: Create RequestAvailableEvent - Failed!");
		return FALSE;
	}

	OSAL_create_event( &g_hStopRequestHandlingThreadEvent , TRUE, FALSE, NULL );
	if( NULL == g_hStopRequestHandlingThreadEvent )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: Create RequestHandlingThreadEvent - Failed!");
		return FALSE;
	}

	g_pReplyMessage = NULL;
	g_ReplyResult = L5_RESULT_OK;
	g_dwCurrentSequentialNumber = 0;

	// Initialize connections table
	for( i = 0; i < ARRAY_ENTRIES(g_atSocketConnections); i++ )
	{
		g_atSocketConnections[i].bActive = FALSE;
		g_atSocketConnections[i].bResourcesAllocated = FALSE;
	}

	//check if to use sockets or NPIPE
	//res = OSAL_ConfigController_GetStrValue(HKEY_LOCAL_MACHINE, KEY_ENTRY_PIPEDEV, KEY_ENTRY_IPC, answer, MAX_ANSWER_SIZE);		
	res = L4Configurations_getIPCMode(answer);
	if ( (TRUE == res) && (0 == OSAL_stricmp("SOCKETS", answer)) )
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_NOTICE, "Infrastructure : SOCKETS");
		useNPIPE = FALSE;
	}
	else
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_NOTICE, "Infrastructure: NPIPE");
		useNPIPE = TRUE;
	}
	TRACE(TR_MOD_CONFIGURATION, TR_SEV_INFO, "config param %s = %s , source=%S",OSAL_KEY_ENTRY_IPC, useNPIPE?"NPipe":"Sockets", res?"Registry":"Code");
	// Sockets initialization
	if (!useNPIPE)
	{
		if( SOCKETS_SUCCESS != SERVER_SOCKETS_Init() )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: SERVER_SOCKETS_Init - Failed!");
			return FALSE;
		}
	}
	else if (useNPIPE)
	{
		if( SOCKETS_SUCCESS != SERVER_NPIPE_Init() )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: SERVER_PIPE_Init - Failed!");
			return FALSE;
		}
	}

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "L5_SOCKETS_DISPATCHER_Initialize Succeed.");
	return TRUE;
}

void l5_sockets_dispatcher_Stop()
{
	int i;

	if (!isStarted)
	{
		return;
	}

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "l5_sockets_dispatcher_Stop(IN)");
	// Stop the server listening thread, not allowing new connections
	if (!useNPIPE)
	{
		SERVER_SOCKETS_StopServer();
		SERVER_SOCKETS_DisconnectClients();
	}
	else
	{
		SERVER_NPIPE_StopServer();
		SERVER_NPIPE_DisconnectClients();
	}

	// To stop the request handling thread we must set this stop event and also disconnect all clients.
	// We will verify that the request handling thread is dead in shutdown.
	// No need to kill it now. The important thing is to disconnect the clients and stop waiting for replies.
	// If the thread will not close on its own cs might be ruined. After shutdown no one uses them.

	//wmxTerminateThread(g_hStopRequestHandlingThreadEvent, &g_hRequestHandlingThread, TR_MOD_L5_SOCKETS_DISPATCHER);
	OSAL_set_event(g_hStopRequestHandlingThreadEvent);
	OSAL_timedjoin_thread(g_hRequestHandlingThread, SHUTDOWN_TIMEOUT, NULL);
	
	// kill all connections
	for( i = 0; i < ARRAY_ENTRIES(g_atSocketConnections); i++ )
	{
		// Disconnect the clients (and release the waiting threads)
		if( TRUE == g_atSocketConnections[i].bActive )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "Disconnecting client - %d",g_atSocketConnections[i]);
			l5_sockets_dispatcher_DisconnectClient( &(g_atSocketConnections[i]), L5_RESULT_SERVICE_SHUTTING_DOWN );
		}

		// Free resources associated with the connection
		if(OSAL_atomic_compareExchange((LPLONG)(&g_atSocketConnections[i].bResourcesAllocated), FALSE, TRUE))
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "g_atSocketConnections[%d].bResourcesAllocated=%d",
				i, g_atSocketConnections[i].bResourcesAllocated);
		}

		// Free the request message if available
		if( NULL != g_atSocketConnections[i].pRequestMessage )
		{
			OSAL_free(  g_atSocketConnections[i].pRequestMessage );
			g_atSocketConnections[i].pRequestMessage = NULL;
		}
	}

	isStarted = FALSE;
	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "l5_sockets_dispatcher_Stop(OUT)");
}

void l5_sockets_dispatcher_FreeResources()
{
	int i;
	for( i = 0; i < ARRAY_ENTRIES(g_atSocketConnections); i++ )
	{
		if( TRUE == g_atSocketConnections[i].bActive )
		{		
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "closing handle1=%d, handle2=%d",
				g_atSocketConnections[i].hReplyAvailableEvent ,g_atSocketConnections[i].hStopWaitingForReplyEvent );
			OSAL_delete_event( g_atSocketConnections[i].hReplyAvailableEvent );
			OSAL_delete_event( g_atSocketConnections[i].hStopWaitingForReplyEvent );
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "Deleting CS1=%d, CS2=%d",
				g_atSocketConnections[i].csHandlingRequest, g_atSocketConnections[i].csSendReceive);
			OSAL_delete_critical_section( &(g_atSocketConnections[i].csHandlingRequest) );
			OSAL_delete_critical_section( &(g_atSocketConnections[i].csSendReceive) );
			g_atSocketConnections[i].bDisconnected = FALSE;
			g_atSocketConnections[i].bActive = FALSE;
		}
	}
}

BOOL l5_sockets_dispatcher_Start()
{
	if (isStarted)
	{
		return TRUE;
	}
	OSAL_reset_event(g_hStopRequestHandlingThreadEvent);
	// Create the Request Handling Thread
	OSAL_create_thread( l5_sockets_dispatcher_RequestHandlingThread, NULL, &g_hRequestHandlingThread);
	if( NULL == g_hRequestHandlingThread )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: Creation of RequestHandlingThread - Failed!");
		return FALSE;
	}

	// Sockets callback registration and start listening
	if (!useNPIPE)
	{
		if( SOCKETS_SUCCESS != SERVER_SOCKETS_StartServer(GetPortNum(), &l5_sockets_dispatcher_HandleData,
						&l5_sockets_dispatcher_HandleNewConnection,&l5_sockets_dispatcher_HandleDisconnection) )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: SERVER_SOCKETS_StartServer - Failed!");
			return FALSE;
		}
	}
	else if (useNPIPE)
	{
		if( SOCKETS_SUCCESS != SERVER_NPIPE_StartServer(
		&l5_sockets_dispatcher_HandleData,
		&l5_sockets_dispatcher_HandleNewConnection,
		&l5_sockets_dispatcher_HandleDisconnection) )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Initialize Failed: SERVER_SOCKETS_StartServer - Failed!");
			return FALSE;
		}
	}

	isStarted = TRUE;

	return TRUE;
}

void L5_SOCKETS_DISPATCHER_Shutdown()
{
	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "Sockets Dispatcher Shutdown started.");

	// Verify that the request handling thread is dead

	if (!useNPIPE)
	{
		SERVER_SOCKETS_Fini();	
	}
	else if (useNPIPE)
	{
		SERVER_NPIPE_Fini();	
	}

	// Synchronization objects
	if(g_hStopRequestHandlingThreadEvent != NULL)
	{
		OSAL_delete_event( g_hStopRequestHandlingThreadEvent );
		g_hStopRequestHandlingThreadEvent = NULL;
	}
	if(g_hRequestAvailableEvent != NULL)
	{
		OSAL_delete_event( g_hRequestAvailableEvent );
		g_hRequestAvailableEvent = NULL;
	}
	if(g_hReplyHandledEvent != NULL)
	{
		OSAL_delete_event( g_hReplyHandledEvent );
		g_hReplyHandledEvent = NULL;
	}

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "Sockets Dispatcher Shutdown succeeded.");
}

/********************************************************************
 * Function    : l5_sockets_dispatcher_HandleData
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_HandleData( char* bBuffer, int nSize, SOCKETS_CLIENT_ID Socket, void* context )
{
	/* This function will be called when a full (unfragmented) 
	 * message is received from a client. This is ensured by the sockets
	 * server.
	 */
	tL5SocketsDispatcherConnection *pConn = (tL5SocketsDispatcherConnection *)context;
	tL5Message *pReceivedMessage = (tL5Message*)bBuffer;

	UNREFERENCED_PARAMETER(nSize);

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "l5_sockets_dispatcher_HandleData(IN)");
	if (pConn->L5Conn != NULL)
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO,"Got message for targetID=%d",((tL5DispatcherConnection*)((pConn->L5Conn)))->nTargetID);
	}	
	
	if( context == NULL )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: context == NUL");
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}

	// Check the validity of the received message - prevent protocol
	// flaws or buffer overflows in the future.
	if( FALSE == L5_COMMON_UTILS_VerifyL5MessageSizes(pReceivedMessage) )
	{
        //These are critical errors - the other side is not acting in accordance to the defined protocol.
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_WARNING, "other side is not acting in accordance to the defined protocol, disconnecting Client");
		l5_sockets_dispatcher_DisconnectClient( pConn, L5_RESULT_INVALID_PROTOCOL );
		return;
	}

	// Handle control messages
	if( L5_TARGET_CONTROL == pReceivedMessage->TargetID )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "l5_sockets_dispatcher_HandleData(l5_sockets_dispatcher_HandleControlMessage)");
		l5_sockets_dispatcher_HandleControlMessage( pReceivedMessage, pConn, Socket );
		return;
	}

	// Messages other than control messages cannot be sent before we establish a 
	// direct dispatcher connection. Thus, complete the handshake.
	if( NULL == pConn->L5Conn )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "reply/request message arrived before handshake!, disconnecting Client.");//add target id to disconnect
		l5_sockets_dispatcher_DisconnectClient( pConn, L5_RESULT_INVALID_PROTOCOL );
		return;
	}

	// Handle requests and replies
	if( 0 == (pReceivedMessage->fbFlags & L5_MESSAGE_FLAG_REPLY) )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "l5_sockets_dispatcher_HandleData(l5_sockets_dispatcher_HandleRequestMessage)");
		l5_sockets_dispatcher_HandleRequestMessage( pReceivedMessage, pConn, Socket );
	}
	else
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "l5_sockets_dispatcher_HandleData(l5_sockets_dispatcher_HandleReplyMessage)");
		l5_sockets_dispatcher_HandleReplyMessage( pReceivedMessage, pConn, Socket );
	}
	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "l5_sockets_dispatcher_HandleData(OUT)");
}


/********************************************************************
 * Function    : l5_sockets_dispatcher_HandleControlMessage
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_HandleControlMessage( 
	tL5Message *pReceivedMessage,
	tL5SocketsDispatcherConnection *pSourceConn,
	SOCKETS_CLIENT_ID Socket )
{
	L5_RESULT Result;
	L5_TARGET_ID nRequestedTargetID;

	UNREFERENCED_PARAMETER(Socket);

	switch(pReceivedMessage->dwMessageID)
	{
		case L5_CONTROL_MESSAGE_HANDSHAKE:
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "L5_CONTROL_MESSAGE_HANDSHAKE");
			// Verify that we've received the requested target ID
			if( sizeof(L5_TARGET_ID) != pReceivedMessage->dwSentBufferSize )
			{
				TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Invalid Protocol: Sent buffer size incorrect!");
				l5_sockets_dispatcher_DisconnectClient( pSourceConn, L5_RESULT_INVALID_PROTOCOL );
				return;
			}

			// Did we already do the handshake?
			if( NULL != pSourceConn->L5Conn )
			{
				TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Invalid Protocol: Handshake has been performed already!");
				l5_sockets_dispatcher_DisconnectClient( pSourceConn, L5_RESULT_INVALID_PROTOCOL );
				return;
			}

			// Get the requested target ID
			nRequestedTargetID = *((L5_TARGET_ID*)(&(pReceivedMessage->baSentBuffer)));

			// Create a direct dispatcher connection
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "Create a direct dispatcher connection!");
			Result = L5_DISPATCHER_ConnectEx(
				nRequestedTargetID,
				&l5_sockets_dispatcher_DirectMessageHandler,
				&l5_sockets_dispatcher_EventHandler,
				pSourceConn,
				THREAD_ID_DEFAULT,
				&(pSourceConn->L5Conn) );

			//if (pSourceConn->L5Conn)
			//	printf("New client connected. Assigne TargetID=%d\n",((tL5DispatcherConnection*)((pSourceConn->L5Conn)))->nTargetID);

			if( L5_RESULT_OK != Result )
			{
				TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Connect to L5 Dispatcher Failed!");
				l5_sockets_dispatcher_DisconnectClient( pSourceConn, Result );
				return;
			}

			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "before L5_COMMON_UTILS_SendControlMessage!");
			// According to the protocol definition we must send a result here
			L5_COMMON_UTILS_SendControlMessage( pSourceConn->Socket, L5_CONTROL_MESSAGE_HANDSHAKE, 
											((tL5DispatcherConnection*)((pSourceConn->L5Conn)))->nTargetID, L5_RESULT_OK );
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "Handshake Performed - pConn = %x, L5Conn = %x", pSourceConn, pSourceConn->L5Conn);
			break;
		
		default:
			// We don't support any other control messages
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Invalid Protocol: expect to get Handshake control message!");
			l5_sockets_dispatcher_DisconnectClient( pSourceConn, L5_RESULT_INVALID_PROTOCOL );
	}
}

/********************************************************************
 * Function    : l5_sockets_dispatcher_HandleRequestMessage
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_HandleRequestMessage(
	tL5Message *pReceivedMessage,
	tL5SocketsDispatcherConnection *pSourceConn,
	SOCKETS_CLIENT_ID Socket )
{
	void *pMessageCopy;
	
	UNREFERENCED_PARAMETER(Socket);

	pMessageCopy = OSAL_alloc(  sizeof(tL5Message) + pReceivedMessage->dwSentBufferSize );
	if ( NULL == pMessageCopy )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "Heap Alloc Failed!");
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}

	// Copy the contents of the message to the buffer we just allocated
	memcpy( pMessageCopy, pReceivedMessage, sizeof(tL5Message) + pReceivedMessage->dwSentBufferSize );

	if( NULL != OSAL_atomic_compareexchangepointer(&(pSourceConn->pRequestMessage), pMessageCopy, NULL) )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "A request was sent during the handling of a previous request!");
		l5_sockets_dispatcher_DisconnectClient( pSourceConn, L5_RESULT_INVALID_PROTOCOL );
		return;
	}

	if(OSAL_set_event(g_hRequestAvailableEvent)<0)
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Unable to OSAL_set_event(g_hRequestAvailableEvent)");
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}
}

/********************************************************************
 * Function    : l5_sockets_dispatcher_HandleReplyMessage
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_HandleReplyMessage( 
	tL5Message *pReceivedMessage,
	tL5SocketsDispatcherConnection *pSourceConn,
	SOCKETS_CLIENT_ID Socket )
{
	L5_RESULT Result = L5_RESULT_OK;

	UNREFERENCED_PARAMETER(Socket);

	if( FALSE == L5_COMMON_UTILS_VerifyReplyMessage(pReceivedMessage, &(pSourceConn->tExpectedReply)) )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Invalid Protocol: Reply Message not as expected!");
		l5_sockets_dispatcher_DisconnectClient( pSourceConn, L5_RESULT_INVALID_PROTOCOL );
		return;
	}

	// Check whether the reply message is an error.
	// In such case, the error value is placed in the dwMessageID member variable.
	if( 0 != (pReceivedMessage->fbFlags & L5_MESSAGE_FLAG_ERROR) )
	{
		Result = (L5_RESULT)pReceivedMessage->dwMessageID;
	}

	l5_sockets_dispatcher_ReturnReply(
		pSourceConn, 
		(L5_RESULT_OK == Result) ? pReceivedMessage : NULL,
		Result );
}

/********************************************************************
 * Function    : l5_sockets_dispatcher_HandleNewConnection
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_HandleNewConnection( SOCKETS_CLIENT_ID Socket, void** context )
{
	tL5SocketsDispatcherConnection *pConn;
	L5_RESULT Result;

	// Acquire free available connection
	pConn = l5_sockets_dispatcher_FindAvailableConnection();
		
	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "New Connection being established!");
	
	if( NULL == pConn )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "New Connection denied: Too Many Connection!");
		Result = L5_RESULT_TOO_MANY_CONNECTIONS;
		goto handle_error;
	}

	// Create the event and the critical section only if they are not there yet
	if(!OSAL_atomic_compareExchange((LPLONG)(&pConn->bResourcesAllocated), TRUE, FALSE))
	{
		OSAL_create_event( &pConn->hReplyAvailableEvent , FALSE, FALSE, NULL );
		if( NULL == pConn->hReplyAvailableEvent )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "New Connection Failed: Create event failed!");
			Result = L5_RESULT_CREATE_EVENT_FAILED;
			goto handle_error;
		}

		OSAL_create_event( &pConn->hStopWaitingForReplyEvent , TRUE, FALSE, NULL );
		if( NULL == pConn->hStopWaitingForReplyEvent )
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "New Connection Failed: Create event failed!");
			Result = L5_RESULT_CREATE_EVENT_FAILED;
			goto handle_error;
		}

	}

	// Initialize the rest of the connection's member variables
	//XXX - Ilya: why isn`t it locked (pConn):
	pConn->Socket = Socket;
	pConn->L5Conn = NULL;
	pConn->tExpectedReply.bWaitingForReply = FALSE;
	pConn->bDisconnected = FALSE;
	pConn->pRequestMessage = NULL;
	// XXX SEH error handling
	OSAL_init_critical_section( &(pConn->csSendReceive) );
	OSAL_init_critical_section( &(pConn->csHandlingRequest) );
	OSAL_atomic_exchange( (LPLONG)&(pConn->bActive), TRUE );

	*context = pConn;

	printf("New connection established. pCon=0x%x . isActive=%d\n",pConn, pConn->bActive);
	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "New connection established - pConn = %x", pConn);
	return;

handle_error: 
	//VERIFY( L5_RESULT_OK != Result ); // Only error handling
	if( Result == L5_RESULT_OK )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Result == L5_RESULT_OK ");
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}
	L5_COMMON_UTILS_SendControlMessage( Socket, L5_CONTROL_MESSAGE_FAILURE, 0, Result );
	
	if (!useNPIPE)
	{
		SERVER_SOCKETS_DisconnectClient( Socket );
	}
	else
	{
		SERVER_NPIPE_DisconnectClient( Socket );
	}
}

/********************************************************************
 * Function    : l5_sockets_dispatcher_HandleDisconnection
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_HandleDisconnection( SOCKETS_CLIENT_ID Socket, void* context )
{
	UNREFERENCED_PARAMETER(Socket);

	//VERIFY( NULL != context );
	if( context == NULL )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: context == NUL");
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}

	l5_sockets_dispatcher_DisconnectClient( 
		(tL5SocketsDispatcherConnection *)context,
		L5_RESULT_OTHER_SIDE_DISCONNECTED );

	printf("Got disconnected. pCon=0x%x . isActive=%d\n",context, ((tL5SocketsDispatcherConnection *)context)->bActive);
}

void l5_sockets_dispatcher_EventHandler( 
						 L5_CONNECTION Conn,
						 L5_EVENT eEvent,
						 void *pvEventData,
						 void *pvUserContext )
{
	SOCKETS_CLIENT_ID tempSock;
	tL5SocketsDispatcherConnection *pMyConn = (tL5SocketsDispatcherConnection *)pvUserContext;
	
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(Conn);

	tempSock = pMyConn->Socket;

	switch(eEvent)
	{
	case L5_EVENT_DRIVER_CONNECTED:
		L5_COMMON_UTILS_SendEventMessage(tempSock, L5_EVENT_DRIVER_CONNECTED, L5_RESULT_OK);
		break;

	case L5_EVENT_DRIVER_DISCONNECTED:
		L5_COMMON_UTILS_SendEventMessage(tempSock, L5_EVENT_DRIVER_DISCONNECTED, L5_RESULT_OK);
		break;
	}
	
}
/********************************************************************
 * Function    : l5_sockets_dispatcher_DirectMessageHandler
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_DirectMessageHandler( 
	L5_CONNECTION Conn,
	L5_TARGET_ID nOriginID,

	UINT32 dwSentMessageID,
	void  *pvSentBuffer,
	UINT32 cbSentBufferSize,

	UINT32 *pdwResponseMessageID,
	void  *pvResponseBuffer,
	UINT32 *cbResponseBufferSize,

	void *pvUserContext,
	void *pvReserved )
{
	tL5SocketsDispatcherConnection *pMyConn = (tL5SocketsDispatcherConnection *)pvUserContext;
	UINT32 dwWaitResult;
	L5_RESULT Result = L5_RESULT_OK;
	BOOL bDoneWaiting = FALSE;
	SOCKETS_CLIENT_ID tempSock;
	UINT32 tempSequentialNumber;
	OSAL_event_t events[2];

	UNREFERENCED_PARAMETER(Conn);
	
	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "DirectMessageHandler: Conn=0x%x, nOriginID=%d, MessageID=%d",
														Conn, ((tL5DispatcherConnection*)((pMyConn->L5Conn)))->nTargetID, dwSentMessageID);
	if( ( pMyConn == NULL ) || 
		( pdwResponseMessageID == NULL ) || 
		( cbResponseBufferSize == NULL ) ||
		( !L5_COMMON_UTILS_VerifyBufferAndSize( pvResponseBuffer, cbResponseBufferSize ) ) )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: pMyConn==%p pdwResponseMessageID==%p cbResponseBufferSize==%p, one of the args is NULL or L5_COMMON_UTILS_VerifyBufferAndSize() failed", pMyConn, pdwResponseMessageID, cbResponseBufferSize);
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return;
	}

	OSAL_enter_critical_section( &(pMyConn->csSendReceive) );

	if( TRUE == pMyConn->bDisconnected )
	{
		// A better description of this rare situation would be *DISCONNECTING*
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Trying to send message while disconnecting! Conn=%d, TargetID=%d",Conn, nOriginID);
		Result = L5_RESULT_ALREADY_DISCONNECTED;
		goto finalize;
	}

	// Set the sequential number of the message
	pMyConn->tExpectedReply.nTargetID = nOriginID;
	pMyConn->tExpectedReply.dwSequentialNumber = g_dwCurrentSequentialNumber++;
	pMyConn->tExpectedReply.dwMaxReplySize = *cbResponseBufferSize;

	// Just to be on the safe side, in case of a race, turn the bWaitingForReply
	// flag after setting the rest of the connection's members.
	pMyConn->tExpectedReply.bWaitingForReply = TRUE;

	//
	tempSock = pMyConn->Socket;
	tempSequentialNumber = pMyConn->tExpectedReply.dwSequentialNumber;
	OSAL_exit_critical_section( &(pMyConn->csSendReceive) );

	events[0] = pMyConn->hStopWaitingForReplyEvent;
	events[1] = pMyConn->hReplyAvailableEvent;

	OSAL_reset_event(events[1]);
	// Send the message
	Result = L5_COMMON_UTILS_SendMessageParams(
		tempSock,
		nOriginID,
		L5_TARGET_GENERIC_APPLICATION,
		0,
		tempSequentialNumber,
		dwSentMessageID,
		*cbResponseBufferSize,
		cbSentBufferSize,
		(BYTE*)pvSentBuffer );

	OSAL_enter_critical_section( &(pMyConn->csSendReceive) );
	
	if( L5_RESULT_OK != Result )
	{
		goto finalize;
	}

	// Wait for a reply
	dwWaitResult = OSAL_multiple_wait_event( 2, events , FALSE, L5_DISPATCHER_MESSAGE_REPLY_TIMEOUT );
	if( WAIT_TIMEOUT == dwWaitResult )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Check for lost messages. Wait for Reply - Time Out. Conn=0x%x, TargetID=%d, MessageID=%d",
																Conn, ((tL5DispatcherConnection*)((pMyConn->L5Conn)))->nTargetID, dwSentMessageID);
		Result = L5_RESULT_TIMED_OUT;
		goto finalize;
	}
	else if( WAIT_FAILED == dwWaitResult )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Check for lost messages. Wait for Reply Failed");
		Result = L5_RESULT_WAIT_FAILED;
		goto finalize;
	}
	else if( WAIT_ABANDONED == dwWaitResult )
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Check for lost messages. Wait for Reply abandoned");
		Result = L5_RESULT_WAIT_FAILED;
		goto finalize;
	}
	else if(WAIT_OBJECT_0 == dwWaitResult) // hStopWaitingForReplyEvent
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Check for lost messages. Wait for Reply was stopped. Client was disconnected");
		Result = L5_RESULT_ALREADY_DISCONNECTED;
		// If we reach this point, we need to release the waiting thread
		bDoneWaiting = TRUE;
		goto finalize;
	}

	// If we reach this point, there is a thread waiting for us to release him
	bDoneWaiting = TRUE;

	// Check whether this is an actual reply, not an error
	if( L5_RESULT_OK != g_ReplyResult )
	{

		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Got Error Reply (L5-Result = %d)", g_ReplyResult);
		Result = g_ReplyResult;
		goto finalize;
	}

	// Fill the reply parameters
	*pdwResponseMessageID = g_pReplyMessage->dwMessageID;

	// Copy the buffer
	// l5_sockets_dispatcher_HandleReplyMessage has already verified that the
	// reply buffer size can fit into the user-provided buffer.
	if( 0 != *cbResponseBufferSize )
	{
		memcpy( pvResponseBuffer, g_pReplyMessage->baSentBuffer, *cbResponseBufferSize );
	}

	// Get the returned length
	*cbResponseBufferSize = g_pReplyMessage->dwSentBufferSize;

finalize:
	pMyConn->tExpectedReply.bWaitingForReply = FALSE;

	OSAL_exit_critical_section( &(pMyConn->csSendReceive) );

	// We're done handling this reply
	if( TRUE == bDoneWaiting )
	{
		OSAL_set_event( g_hReplyHandledEvent );
	}

	// Return the result to the caller
	*((L5_RESULT *)pvReserved) = Result;
}





//////////////////////////////////////////////////////////////////////////
// Utility functions

/********************************************************************
 * Function    : l5_sockets_dispatcher_AcquireAvailableConnection
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : We don`t need to protect this function - because its can only be run in 1 thread (SocketServer).
 * //XXX: ilya - is it true?
 *******************************************************************/
tL5SocketsDispatcherConnection *l5_sockets_dispatcher_FindAvailableConnection( void )
{
	int i;

	for( i = 0; i < ARRAY_ENTRIES(g_atSocketConnections); i++ )
	{
		tL5SocketsDispatcherConnection *pConn = &(g_atSocketConnections[i]);

		if( pConn->bActive == FALSE )
		{
			return pConn;
		}
	}

	return NULL;
}

/********************************************************************
 * Function    : l5_sockets_dispatcher_DisconnectClient
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
void l5_sockets_dispatcher_DisconnectClient( tL5SocketsDispatcherConnection *pConn, L5_RESULT Reason )
{
	BOOL bPrevDisconnected;
	SOCKETS_CLIENT_ID tempSock;
		
	//The reason for the following line to be here is to make calls from threads
	//that are waiting on the csSendRecieve critical section quit faster.
	bPrevDisconnected = OSAL_atomic_compareExchange( (LPLONG)&(pConn->bDisconnected), TRUE, FALSE );

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "Disconnecting Client - pConn=0x%x",pConn);
	if( FALSE == bPrevDisconnected )
	{
		OSAL_enter_critical_section( &(pConn->csHandlingRequest) );
		tempSock = pConn->Socket;
		OSAL_exit_critical_section( &(pConn->csHandlingRequest) );

		//
		if((Reason != L5_RESULT_OTHER_SIDE_DISCONNECTED) && (Reason != L5_RESULT_SERVICE_SHUTTING_DOWN))
		{
			L5_COMMON_UTILS_SendControlMessage( tempSock, L5_CONTROL_MESSAGE_FAILURE, 0, Reason );

		}

		if (!useNPIPE)
		{
			SERVER_SOCKETS_DisconnectClient( tempSock );
		}
		else
		{
			SERVER_NPIPE_DisconnectClient( tempSock );
		}

		OSAL_enter_critical_section( &(pConn->csHandlingRequest) );

		if( TRUE == pConn->tExpectedReply.bWaitingForReply )
		{
			l5_sockets_dispatcher_ReturnReply( pConn, NULL, Reason );
		}

		// L5_DISPATCHER_Disconnect must be called only after returning reply to prevent a deadlock.
		// If Disconnect will be called before ReturnReply then the L5Dispatcher would try to acquire
		// a write lock while the SendReceiveMessage function is holding the read lock. The read lock
		// could only be release by returning a reply and this could only be done by calling these 
		// functions in the correct order.
   		if( NULL != pConn->L5Conn )
		{
			L5_DISPATCHER_Disconnect( pConn->L5Conn );
		}

		OSAL_atomic_exchange( (LPLONG)&(pConn->bActive), FALSE );

		OSAL_exit_critical_section( &(pConn->csHandlingRequest) );
		OSAL_delete_critical_section(&pConn->csSendReceive);
		OSAL_delete_critical_section(&pConn->csHandlingRequest);
		
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "Disconnect Client succeed");
	}	
}

void l5_sockets_dispatcher_ReturnReply( tL5SocketsDispatcherConnection *pConn, tL5Message *ptMessage, L5_RESULT Result )
{
	UINT32 waitResult;
	OSAL_event_t events[2];

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_DEBUG, "Got reply message");

	if(( pConn == NULL ) || ( !pConn->tExpectedReply.bWaitingForReply ))
	{
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_WARNING, "Cannot return reply");
		return;
	}

	g_pReplyMessage = ptMessage;
	g_ReplyResult = Result;
	OSAL_set_event( pConn->hReplyAvailableEvent );

	events[0] = g_hStopRequestHandlingThreadEvent;
	events[1] = g_hReplyHandledEvent;
	waitResult = OSAL_multiple_wait_event(2, events, FALSE, L5_DISPATCHER_MESSAGE_REPLY_TIMEOUT);
	
	if( (WAIT_OBJECT_0 + 1) !=  waitResult)
	{
		if((waitResult == WAIT_TIMEOUT) || (waitResult == WAIT_ABANDONED) || (waitResult == WAIT_OBJECT_0))
		{
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_WARNING, "wait on reply event timeout, abandoned or stopped");
			return;
		}

		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: g_hStopRequestHandlingThreadEvent was set");
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
	}
}

void l5_sockets_dispatcher_RequestHandlingThread( LPVOID lpParam )
{
	BOOL bStop = FALSE;

	// It is important to put the stop event first in the array, so it will get higher priority
	// when shutting the module down.
	OSAL_event_t ahHandles[2];
	ahHandles[0] = g_hStopRequestHandlingThreadEvent;
	ahHandles[1] = g_hRequestAvailableEvent;

	UNREFERENCED_PARAMETER(lpParam);

	TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_INFO, "Request Handling Thread started.");
	for(;!bStop;)
	{
		int i;

		switch( OSAL_multiple_wait_event(ARRAY_ENTRIES(ahHandles), ahHandles, FALSE, INFINITE) )
		{
		case WAIT_OBJECT_0:			// Stop
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "Stop the Request Handling Thread.");
			bStop = TRUE;
			continue;
		
		case (WAIT_OBJECT_0 + 1):	// Request available
		    break;
		
		case WAIT_ABANDONED:
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_WARNING, "Wait abandoned!.");
			bStop = TRUE;
			continue;

		default: //WAIT_FAILED
			TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: Wait Failed!.");
			L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
			bStop = TRUE;
			continue;
		}

		// request available:
		// iterate the connections array and check for available messages:
		for( i = 0; i < ARRAY_ENTRIES(g_atSocketConnections); i++ )
		{
			tL5SocketsDispatcherConnection *pConn = &(g_atSocketConnections[i]);
			tL5Message *pRequestMessage = NULL;
			tL5Message *pReplyMessage = NULL;
			SOCKETS_CLIENT_ID tempSock;

			if( WAIT_OBJECT_0 == OSAL_wait_event(g_hStopRequestHandlingThreadEvent, 0) )
			{
				TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_NOTICE, "Stop the Request Handling Thread.");
				bStop = TRUE;
				continue;
			}

			if( (FALSE == pConn->bActive) || (TRUE == pConn->bDisconnected) )
			{
				continue;
			}

			OSAL_enter_critical_section( &(pConn->csHandlingRequest) );
			
			tempSock = pConn->Socket;
			
			if( NULL != pConn->pRequestMessage )
			{
				pRequestMessage = OSAL_alloc(  sizeof(tL5Message) + pConn->pRequestMessage->dwSentBufferSize );
				if ( NULL == pRequestMessage )
				{
					TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ALERT, "INTERNAL_PROBLEM: Heap Alloc Failed! pRequestMessage == NUL");
					L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
					bStop = TRUE;
					continue;
				}

				// Copy the contents of the message to the buffer we just allocated
				memcpy( pRequestMessage, pConn->pRequestMessage, sizeof(tL5Message) + pConn->pRequestMessage->dwSentBufferSize );

				OSAL_free(  pConn->pRequestMessage );
				pConn->pRequestMessage = NULL;
			}
			
			OSAL_exit_critical_section( &(pConn->csHandlingRequest) );

			if( NULL != pRequestMessage )
			{
				BYTE baReplyMessage[ sizeof(tL5Message) + L5_DISPATCHER_MAX_MESSAGE_BUFFER_SIZE ];
				pReplyMessage = l5_sockets_dispatcher_ActuallyHandleRequestMessage( (tL5Message*)baReplyMessage, pRequestMessage, pConn );
				OSAL_free(  pRequestMessage );
			}

			if( NULL != pReplyMessage )
			{
				l5_sockets_dispatcher_ActuallySendReply( pReplyMessage, tempSock );
			}
		}
	}	
}
void l5_sockets_dispatcher_ActuallySendReply( 
	tL5Message *pReplyMessage, 
	SOCKETS_CLIENT_ID socket )
{
	L5_RESULT Result;

	// Send the reply
	Result = L5_COMMON_UTILS_SendMessage( socket, pReplyMessage );
	if( L5_RESULT_OK != Result )
	{
		//There is  no useful way handling this error at this point,
		TRACE(TR_MOD_L5_SOCKETS_DISPATCHER, TR_SEV_ERR, "Failed to send message - L5Result = %d)", Result);
	}
}

tL5Message * l5_sockets_dispatcher_ActuallyHandleRequestMessage(tL5Message *pReplyMessage,tL5Message *pReceivedMessage,
																tL5SocketsDispatcherConnection *pSourceConn )
{	
	L5_RESULT Result;

	// Prepare some of the reply message fields before invoking SendReceiveMessage
	pReplyMessage->SourceID = pReceivedMessage->TargetID;
	pReplyMessage->TargetID = pReceivedMessage->SourceID;
	pReplyMessage->fbFlags = L5_MESSAGE_FLAG_REPLY;
	pReplyMessage->dwSequentialNumber = pReceivedMessage->dwSequentialNumber;
	pReplyMessage->dwMessageID = 0;
	pReplyMessage->dwMaxReplyBufferSize = 0;
	pReplyMessage->dwSentBufferSize = pReceivedMessage->dwMaxReplyBufferSize;

	// Actually SendReceiveMessage
	Result = L5_DISPATCHER_SendReceiveMessage(
		pSourceConn->L5Conn,
		pReceivedMessage->TargetID,

		pReceivedMessage->dwMessageID,
		(void*)(&(pReceivedMessage->baSentBuffer)),
		pReceivedMessage->dwSentBufferSize,

		&(pReplyMessage->dwMessageID),
		&(pReplyMessage->baSentBuffer),
		&(pReplyMessage->dwSentBufferSize) );

	// Check the result, send an error message back if there was a failure
	if( L5_RESULT_OK != Result )
	{
		pReplyMessage->fbFlags = L5_MESSAGE_FLAG_REPLY | L5_MESSAGE_FLAG_ERROR;
		pReplyMessage->dwMessageID = Result;
		pReplyMessage->dwSentBufferSize = 0;
	}

	return pReplyMessage;
}
