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
//////////////////////////////////////////////////////////////////////////
// Headers

// Project
#include "CommonServices.h"
#include "L5Common.h"
#include "L5CommonUtils.h"

#include "TraceModule.h"

#include "Messenger.h"

#include "IPC_Common.h"
#include "IPC_Client.h"

//OSAL
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "wimax_osal_config_controler.h"

#include "L4ConfigurationManager.h"

// Module
#include "PipeHandlerInternal.h"


//////////////////////////////////////////////////////////////////////////
// Typedefs
typedef struct
{
	///////////////////////////////////
	// Lower layer
	// Reply events
	OSAL_event_t hReplyAvailable;
	OSAL_event_t hReplyHandled;

	// Lock
	OSAL_critical_section csSendReceive;		

	// The underlying socket
	SOCKETS_CLIENT_CONTEXT	SocketContext;
	SOCKETS_CLIENT_ID		SocketID;
	
	///////////////////////////////////
	// State

	// Handshake
	BOOL bHandshakePerformed;

	/* The ID of the thread currently handling a request.
	 * This is used to prevent SendReceiveMessage() and Disconnect() calls
	 * during requests handling.
	 */
	UINT32 dwHandlingRequestThreadID;

	// Disconnection
	BOOL bDisconnected;

	///////////////////////////////////
	// Reply

	// Waiting for reply variables
	tL5ExpectedReplyMessageParams tExpectedReply;

	// Reply variables
	tL5Message *ptReplyMessage;
	L5_RESULT ReplyResult;
	
	///////////////////////////////////
	// User handlers
	tpfnMessagesHandler pfnMessagesHandler;
	tpfnEventHandler pfnEventHandler;
	void *pvUserContext;
} tL5ClientConnection;


//////////////////////////////////////////////////////////////////////////
// Global variables
static UINT32 g_dwCurrentSequentialNumber = 0;

static BOOL useNPIPE = FALSE;
//////////////////////////////////////////////////////////////////////////
// Prototypes
void l5_connector_HandleData( char *baBuffer, int cbBufferSize, SOCKETS_CLIENT_ID Socket, void *pvContext );
void l5_connector_HandleControlMessage(	tL5Message *pReceivedMessage, tL5ClientConnection *pConn );
void l5_connector_HandleRequestMessage(	tL5Message *pReceivedMessage, tL5ClientConnection *pConn );
void l5_connector_HandleReplyMessage(	tL5Message *pReceivedMessage, tL5ClientConnection *pConn );
void l5_connector_HandleDisconnection( SOCKETS_CLIENT_ID Socket, void *pvContext );
void l5_connector_Disconnect( tL5ClientConnection *pConn, BOOL bDisconnectFromServer, L5_RESULT Reason );
void l5_connector_ReturnReply( tL5ClientConnection *pConn, tL5Message *ptMessage, L5_RESULT Result );
void l5_connector_HandleEventMessage( tL5Message *pReceivedMessage, tL5ClientConnection *pConn );
//////////////////////////////////////////////////////////////////////////
// Implementation

L5_RESULT PIPE_HANDLER_ConnectEx(	
	L5_TARGET_ID nTargetID,
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,
	void *pvUserContext,
	THREAD_ID threadId,
	L5_CONNECTION *Conn )
{
	UNREFERENCED_PARAMETER(threadId);

	return PIPE_HANDLER_ConnectInternal(PIPE_HANDLER_GetIpAddress(), PIPE_HANDLER_GetPortNum(), nTargetID, pfnMessagesHandler, pfnEventHandler, pvUserContext, FALSE, Conn);
}

L5_RESULT PIPE_HANDLER_Connect(	
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,	
	L5_CONNECTION *Conn )
{
	return PIPE_HANDLER_ConnectInternal(PIPE_HANDLER_GetIpAddress(), PIPE_HANDLER_GetPortNum(), L5_TARGET_DYNAMIC, pfnMessagesHandler, pfnEventHandler, NULL, FALSE, Conn);
}


L5_RESULT PIPE_HANDLER_ConnectInternal(
	char *szHostName,
	int nPort,
	L5_TARGET_ID nTargetID,
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,
	void *pvUserContext,
	BOOL isGateKeeper, 
	L5_CONNECTION *Conn )
{
	tL5ClientConnection *pConn;
	L5_RESULT Result = L5_RESULT_OK;
	UINT32 dwWaitResult;
	L5_RESULT res;

	char tempIpAddress[32];
	size_t numOfChars;
	// Progress variables for initialization
	BOOL bCreatedCriticalSection = FALSE;
	BOOL bSocketsInitialized = FALSE;
	BOOL bDoneWaiting = FALSE;
	char answer[MAX_ANSWER_SIZE];


	// Some ASSERTs
	//VERIFY( NULL != szHostName );
	if ( NULL == szHostName)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "NULL == szHostName");	
		return L5_RESULT_INVALID_PARAMS;
	}

	//VERIFY( 0 != nPort );
	if ( 0 == nPort)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "0 == nPort");	
		return L5_RESULT_INVALID_PARAMS;
	}

	//VERIFY( NULL != Conn );
	if ( NULL == Conn )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "NULL == Conn");	
		return L5_RESULT_INVALID_PARAMS;
	}

	// Clear the output variable
	*Conn = NULL;

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_ConnectInternal(IN)");
	UNREFERENCED_PARAMETER(numOfChars);
	UNREFERENCED_PARAMETER(tempIpAddress);

	if (!isGateKeeper)
	{
		//PIPE_HANDLER_AddClient(); // ensure the gate keeper is initialized
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - isGateKeeper = FALSE");	
		if (!PIPE_HANDLER_IsConnected(&res))
		{
			//PIPE_HANDLER_RemoveClient();
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal(OUT) - res=%d",res);	
			return res; //default: L5_RESULT_ALREADY_DISCONNECTED
		}
	}
	
	/*mbstowcs_s(&numOfChars, tempIpAddress, sizeof(tempIpAddress)/2, szHostName, 31); // temp - debug
	if (isGateKeeper)
	{		
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, (L"Connect - gatekeeper. IP: %ws, port: %d", tempIpAddress, nPort));
	}
	else
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, (L"Connect - client. IP: %ws, port: %d", tempIpAddress, nPort));
	}*/

	// Allocate memory for the connection structure
	pConn = (tL5ClientConnection *)OSAL_zero_alloc( sizeof(tL5ClientConnection) );
	if( NULL == pConn )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - HeapAlloc failed!!");	
		return L5_RESULT_MEMORY_ALLOC_FAILED;
	}

	// Create hReplyAvailable event
	OSAL_create_event( &pConn->hReplyAvailable , FALSE, FALSE, NULL );
	if( NULL == pConn->hReplyAvailable )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - CreateEvent failed!!");	
        Result = L5_RESULT_CREATE_EVENT_FAILED;
		goto finalize;
	}

	// Create hReplyHandled event
	OSAL_create_event( &pConn->hReplyHandled , FALSE, FALSE, NULL );
	if( NULL == pConn->hReplyHandled )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - CreateEvent failed!!");	
		Result = L5_RESULT_CREATE_EVENT_FAILED;
		goto finalize;
	}

	// Create the critical section
	// XXX handle SEH exception
	OSAL_init_critical_section( &(pConn->csSendReceive) );

	bCreatedCriticalSection = TRUE;

	// Initialize other member variables (other than zero)
	pConn->pfnMessagesHandler = pfnMessagesHandler;
	pConn->pfnEventHandler = pfnEventHandler;
	pConn->pvUserContext = pvUserContext;

	/////////////////////////////////////
	// Sockets

	// Initialize sockets

	////check if to use sockets or NPIPE
	//resReg = RegistryController_GetStrValue(HKEY_LOCAL_MACHINE, KEY_ENTRY_PIPEDEV, KEY_ENTRY_IPC, answer,MAX_ANSWER_SIZE );	
	L4Configurations_getIPCMode(answer);
	if ( 0 == OSAL_stricmp("SOCKETS", answer))
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_NOTICE, "Infrastructure : SOCKETS");
		useNPIPE = FALSE;
	}
	else
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_NOTICE, "Infrastructure: NPIPE");
		useNPIPE = TRUE;
	}

	if (useNPIPE)
	{
		if( SOCKETS_SUCCESS != CLIENTS_NPIPE_Init( 
		&(pConn->SocketContext), &(pConn->SocketID), (void*)pConn, 
		&l5_connector_HandleData, &l5_connector_HandleDisconnection ) )
		{
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - CLIENTS_NPIPE_Init failed!!");	
			Result = L5_RESULT_SOCKETS_ERROR;
			pConn->SocketContext = NULL;
			goto finalize;
		}
	}
	else if (!useNPIPE)
	{
		if( SOCKETS_SUCCESS != CLIENTS_SOCKETS_Init( 
			&(pConn->SocketContext), &(pConn->SocketID), (void*)pConn, 
			&l5_connector_HandleData, &l5_connector_HandleDisconnection ) )
		{
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - CLIENTS_SOCKETS_Init failed!!");	
			Result = L5_RESULT_SOCKETS_ERROR;
			pConn->SocketContext = NULL;
			goto finalize;
		}
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - CLIENTS_SOCKETS_Init succeeded!!");	
	bSocketsInitialized = TRUE;

	// Create a new client, register the handlers and connect to the server
	if (!useNPIPE)
	{
		if( SOCKETS_SUCCESS != CLIENTS_SOCKETS_ConnectToServer( 
		szHostName, (unsigned short)nPort, pConn->SocketContext ) )
		{
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_ConnectInternal - CLIENTS_SOCKETS_ConnectToServer failed");
			// pConn->Socket will be compared with NULL in the finalize section of the function
			Result = L5_RESULT_SOCKETS_ERROR;
			goto finalize;
		}
	}
	else if (useNPIPE)
	{	
		if( SOCKETS_SUCCESS != CLIENTS_NPIPE_ConnectToServer( pConn->SocketContext ) )
		{
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "PIPE_HANDLER_ConnectInternal - CLIENTS_NPIPE_ConnectToServer failed");
			// pConn->Socket will be compared with NULL in the finalize section of the function
			Result = L5_RESULT_SOCKETS_ERROR;
			goto finalize;
		}
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - ConnectToServer succeeded");	
	/////////////////////////////////////
	// Handshake

	// Initialize variables in the connection structure
	pConn->tExpectedReply.bWaitingForReply = TRUE;
	//OSAL_reset_event( pConn->hReplyHandled );

	res = L5_COMMON_UTILS_SendControlMessage( 
		pConn->SocketContext,
		L5_CONTROL_MESSAGE_HANDSHAKE,
		nTargetID,
		nTargetID );	// This is the requested TargetID
	if( L5_RESULT_OK != res)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "PIPE_HANDLER_ConnectInternal - L5_COMMON_UTILS_SendControlMessage failed, result = %d!", res);		
		Result = L5_RESULT_SOCKETS_ERROR;
		goto finalize;
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - PConn = 0x%x wait for 0x%x SendControlMessage succeeded",pConn, pConn->hReplyAvailable);	
	// Wait for a reply
	dwWaitResult = OSAL_wait_event( pConn->hReplyAvailable, L5_DISPATCHER_CONNECT_TIMEOUT );
	bDoneWaiting = TRUE;
	if( WAIT_TIMEOUT == dwWaitResult )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - waiting for reply timed out!!");	
		Result = L5_RESULT_TIMED_OUT;
		goto finalize;
	}
	else if( WAIT_FAILED == dwWaitResult || WAIT_ABANDONED == dwWaitResult)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - waiting for reply failed!!");	
		Result = L5_RESULT_WAIT_FAILED;
		goto finalize;
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - finished waiting for reply");	
	// If we reach this point, there is a thread waiting for us to release it...
	bDoneWaiting = TRUE;

	// Check the reply we got from the server
	if( L5_RESULT_OK != pConn->ReplyResult )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ALERT, "PIPE_HANDLER_ConnectInternal - got invalid reply -> %d!!",pConn->ReplyResult);	
		Result = pConn->ReplyResult;
		goto finalize;
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - got valid reply");	
	// All went OK, remember that we had already performed handshake
	pConn->bHandshakePerformed = TRUE;
	pConn->bDisconnected = FALSE;
	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_ConnectInternal - pConn->bDisconnected = FALSE for pCon=%d",pConn);	

finalize:

	// We're not waiting anymore
	pConn->tExpectedReply.bWaitingForReply = FALSE;

	if( L5_RESULT_OK != Result )
	{
		// The server is about to disconnect anyway, so there is no need to
		// actually take this disconnection into account in the l5_connector_Disconnect()
		// function. This is because cleanup is performed in the current function
		// and not in l5_connector_Disconnect().
		// In addition, note that the disconnection function will not be called
		// until we release the SOCKETS thread by calling OSAL_set_event() below.
		pConn->bDisconnected = TRUE;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_ConnectInternal - pConn->bDisconnected = TRUE for pCon=%d",pConn);	
	}

	// Release the thread that is waiting for us to handle the response
	if( TRUE == bDoneWaiting )
	{
		OSAL_set_event( pConn->hReplyHandled );
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "PIPE_HANDLER_ConnectInternal - Connect Finished, Result = %d!", Result);

	// We had a failure, uninitialize
	if( L5_RESULT_OK != Result )
	{
		if (!isGateKeeper)
		{
			//PIPE_HANDLER_RemoveClient();
		}

		if( NULL != pConn->SocketContext )
		{
			CLIENTS_SOCKETS_DisconnectFromServer( pConn->SocketContext );
		}

		if( TRUE == bSocketsInitialized )
		{
			if (!useNPIPE)
			{
				CLIENTS_SOCKETS_Fini( &(pConn->SocketContext) );
			}
			else
			{
				CLIENTS_NPIPE_Fini(&(pConn->SocketContext));
			}
		}

		if( TRUE == bCreatedCriticalSection )
		{
			OSAL_delete_critical_section( &(pConn->csSendReceive) );
		}

		if( NULL != pConn->hReplyHandled )		{ OSAL_delete_event(pConn->hReplyHandled); }
		if( NULL != pConn->hReplyAvailable )	{ OSAL_delete_event(pConn->hReplyAvailable); }
		OSAL_free(  (LPVOID)(pConn) );
	}
	else
	{
		// All ok, return the newly created connection
		*Conn = (L5_CONNECTION)pConn;
	}    

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_ConnectInternal(OUT)");	
	return Result;
}

void PIPE_HANDLER_Disconnect( L5_CONNECTION Conn )
{
	PIPE_HANDLER_DisconnectInternal(Conn, FALSE);
}

void PIPE_HANDLER_DisconnectInternal( L5_CONNECTION Conn, BOOL isGateKeeper )
{	
	tL5ClientConnection *pConn = (tL5ClientConnection *)Conn;	
	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "PIPE_HANDLER_DisconnectInternal(IN)");

	if (pConn == NULL)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Disconnect - received pConn = NULL");
		return;
	}

#if defined(_DEBUG) || defined(DEBUG)
	//to prevent the user from calling disconnect during request handling.
	if( OSAL_get_threadid() == pConn->dwHandlingRequestThreadID )	
	{
		// Can't return a value in this case, so ASSERT at least
		//ASSERT( );
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Disconnect - GetCurrentThreadId() == pConn->dwHandlingRequestThreadID");
		return;
	}
#endif

	/* We should free the connection now because the user has explicitly
	 * requested to disconnect.
	 *
	 * There is no reason trying to acquire csSendRecive critical section. This
	 * is because the user MUST ensure that SendReceiveMessage() is not being executed
	 * concurrently with Disconnect().
	 *
	 * The sockets client MUST ensure that after explicitly closing the socket, the
	 * L5Connector HandleData() function won't be called again.
	 */
	l5_connector_Disconnect( pConn, TRUE, L5_RESULT_USER_REQUESTED_DISCONNECT );
	//TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, (L"Disconnect Finished!"));
	if (!isGateKeeper)
	{
		//PIPE_HANDLER_RemoveClient();	
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "PIPE_HANDLER_DisconnectInternal(OUT)");
}

L5_RESULT PIPE_HANDLER_SendReceiveL5( 
	L5_CONNECTION Conn,
	L5_TARGET_ID nTargetID,

	UINT32 dwSendMessageID,
	void  *pvSendBuffer,
	UINT32 cbSendBufferSize,

	UINT32 *pdwReceiveMessageID,
	void  *pvReceiveBuffer,
	UINT32 *cbReceiveBufferSize )
{
	tL5ClientConnection *pConn = (tL5ClientConnection *)Conn;
	UINT32 dwWaitResult;
	UINT32 dwSequentialNumber;
	L5_RESULT Result = L5_RESULT_OK;
	BOOL bErrorRequiresDisconnection = FALSE;
	BOOL bDoneWaiting = FALSE;
	L5_RESULT tempRes;

	// A few ASSERTs
	//VERIFY( NULL != pConn );
	if ( NULL == pConn )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "NULL == pConn");
		return L5_RESULT_INVALID_PARAMS;
	}
	//VERIFY( L5_COMMON_UTILS_VerifyBufferAndSize( pvSendBuffer, &cbSendBufferSize ) );
	if ( !L5_COMMON_UTILS_VerifyBufferAndSize( pvSendBuffer, &cbSendBufferSize ) )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "L5_COMMON_UTILS_VerifyBufferAndSize( pvSendBuffer, &cbSendBufferSize )");
		return L5_RESULT_INVALID_PARAMS;
	}

	//VERIFY( L5_COMMON_UTILS_VerifyBufferAndSize( pvReceiveBuffer, cbReceiveBufferSize ) );
	if ( !L5_COMMON_UTILS_VerifyBufferAndSize( pvReceiveBuffer, cbReceiveBufferSize ) )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "L5_COMMON_UTILS_VerifyBufferAndSize( pvReceiveBuffer, cbReceiveBufferSize )");
		return L5_RESULT_INVALID_PARAMS;
	}

	if (!PIPE_HANDLER_IsConnected(&tempRes))
	{
		return tempRes; //default: L5_RESULT_ALREADY_DISCONNECTED;
	}

	OSAL_enter_critical_section( &(pConn->csSendReceive) );

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "SendReceiveMessage - start");


	// Are we connected at all?
	if( TRUE == pConn->bDisconnected )
	{
		Result = L5_RESULT_ALREADY_DISCONNECTED;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Send Fail, L5_RESULT_ALREADY_DISCONNECTED! TRUE == pConn->bDisconnected for pCon=%d",pConn);
		goto finalize;
	}

	// Is this thread currently in a callback?
	if( OSAL_get_threadid() == pConn->dwHandlingRequestThreadID )	
	{
		Result = L5_RESULT_CANT_DO_DURING_CALLBACK;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Send Fail, L5_RESULT_CANT_DO_DURING_CALLBACK!");
		goto finalize;
	}

	// Set the sequential number of the message
	dwSequentialNumber = g_dwCurrentSequentialNumber++;

	// Initialize waiting variables
	pConn->tExpectedReply.nTargetID = L5_TARGET_GENERIC_APPLICATION;
	pConn->tExpectedReply.dwSequentialNumber = dwSequentialNumber;
	pConn->tExpectedReply.dwMaxReplySize = NULL_PTR_VAL_OR_ZERO(cbReceiveBufferSize);

	// Just to be on the safe side, in case of a race, turn the bWaitingForReply
	// flag after setting the rest of the connection's members.
	pConn->tExpectedReply.bWaitingForReply = TRUE;
	//OSAL_reset_event( pConn->hReplyHandled );

	// Send the message
	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "Sending message to AppSrv ...");
	Result = L5_COMMON_UTILS_SendMessageParams(
		pConn->SocketContext,
		L5_TARGET_GENERIC_APPLICATION,
		nTargetID,
		0,
		dwSequentialNumber,
		dwSendMessageID,
		NULL_PTR_VAL_OR_ZERO(cbReceiveBufferSize),
		cbSendBufferSize,
		(BYTE*)pvSendBuffer );

	if( L5_RESULT_OK != Result )
	{
		bErrorRequiresDisconnection = TRUE;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Send Message Params Failed, Result = %d!", Result);
		goto finalize;
	}

	// Wait for a reply
	dwWaitResult = OSAL_wait_event( pConn->hReplyAvailable, L5_DISPATCHER_MESSAGE_REPLY_TIMEOUT );
	bDoneWaiting = TRUE;
	if( WAIT_TIMEOUT == dwWaitResult )
	{
		Result = L5_RESULT_TIMED_OUT;
		bErrorRequiresDisconnection = TRUE;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "Timeout on hReplyAvailable event, L5_RESULT_TIMED_OUT!");
		goto finalize;
	}
	else if( WAIT_FAILED == dwWaitResult || WAIT_ABANDONED == dwWaitResult )
	{
		Result = L5_RESULT_WAIT_FAILED;
		bErrorRequiresDisconnection = TRUE;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "Wait Failed, L5_RESULT_WAIT_FAILED!");
		goto finalize;
	}

	// If we reach this point, there is a thread waiting for us to release him...
	bDoneWaiting = TRUE;

	// Check the reply we got from the server
	if( L5_RESULT_OK != pConn->ReplyResult )
	{
		Result = pConn->ReplyResult;
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Got BAD reply. L5Result: %d", pConn->ReplyResult);
		goto finalize;
	}

	/////////////////////////////////////////
	// Fill the reply parameters
	if( NULL != pdwReceiveMessageID )
	{
		*pdwReceiveMessageID = pConn->ptReplyMessage->dwMessageID;
	}

	// Get the returned length
	if( NULL != cbReceiveBufferSize )
	{
		*cbReceiveBufferSize = pConn->ptReplyMessage->dwSentBufferSize;

		// Copy the buffer
		if( 0 != *cbReceiveBufferSize )
		{
			// We've already verified this in the beginning of the function.
			// But just to be on the safe side.
			VERIFY( NULL != pvReceiveBuffer );

			memcpy( pvReceiveBuffer, pConn->ptReplyMessage->baSentBuffer, *cbReceiveBufferSize );
		}
	}
	
	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "Got valid reply. ");

finalize:

	pConn->tExpectedReply.bWaitingForReply = FALSE;

	if( TRUE == bDoneWaiting )
	{
		// We're done handling this reply
		OSAL_set_event( pConn->hReplyHandled );
	}

	if( TRUE == bErrorRequiresDisconnection )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "Error during send process, Disconnecting!");
		// if the error is a result of illegal message format - we don't want to report it as an error to the gate keeper
		if (L5_RESULT_INVALID_PARAMS != Result)
		{
			PIPE_HANDLER_ReportError(); // notify the ConnGateKeeper that it has to restart due to a critical error
		}
		l5_connector_Disconnect( pConn, FALSE, Result );
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "SendReceiveMessage - end");
	OSAL_exit_critical_section( &(pConn->csSendReceive) );

	return Result;
}

EXPORT tUtilityFunctions *PIPE_HANDLER_GetUtilityFunctions()
{
	static tUtilityFunctions funcs = {
		&Messenger_PostRequest,
		&Messenger_PopRequest,
		&TraceAgent_WriteTrace,
		NULL
	};

	return &funcs;
}

EXPORT tL5DispatcherFunctions *PIPE_HANDLER_GetServiceDispatcherFunctions()
{
	static tL5DispatcherFunctions funcs = {
		&PIPE_HANDLER_Connect,
		&PIPE_HANDLER_ConnectEx,
		&PIPE_HANDLER_Disconnect,
		&PIPE_HANDLER_SendReceiveL5,
		&PIPE_HANDLER_RegisterCtrlStatusUpdatesCB,
		&PIPE_HANDLER_UnregisterCtrlStatusUpdatesCB,
		&PIPE_HANDLER_GetCtrlStatus,
		&PIPE_HANDLER_SetConnParams,
		NULL // no need to report on errors outside of AppSrv
	};

	return &funcs;
}

void l5_connector_HandleData( char *baBuffer, int cbBufferSize, SOCKETS_CLIENT_ID Socket, void *pvContext )
{
	/* This function will be called when a full (unfragmented) 
	 * message is receiveed from a client. This is ensured by the sockets
	 * server.
	 */	
	tL5ClientConnection *pConn = (tL5ClientConnection *)pvContext;
	tL5Message *pReceivedMessage = (tL5Message*)baBuffer;

	UNREFERENCED_PARAMETER(Socket);
	UNREFERENCED_PARAMETER(cbBufferSize);

	/* Check the validity of the received message - prevent protocol
	 * flaws or buffer overflows in the future.
	 */
	if( FALSE == L5_COMMON_UTILS_VerifyL5MessageSizes(pReceivedMessage) )
	{
		/* These are critical errors - the other side is not acting in accordance
		 * to the defined protocol. Disconnect.
		 */
		
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Invalid L5 message size.");
		l5_connector_Disconnect( pConn, FALSE, L5_RESULT_INVALID_PROTOCOL );
		return;
	}

	// Handle control messages
	if( (L5_TARGET_CONTROL == pReceivedMessage->TargetID ) || (100 < pReceivedMessage->TargetID ))
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "The connection pCon=0x%x has targetID %d",pConn, pReceivedMessage->TargetID);
		//printf("Got targetID %d\n",pReceivedMessage->TargetID);
		l5_connector_HandleControlMessage( pReceivedMessage, pConn );
		return;
	}

	// Handle event messages
	if( L5_TARGET_EVENT == pReceivedMessage->TargetID )
	{
		l5_connector_HandleEventMessage( pReceivedMessage, pConn );
		return;
	}

	// Messages other than control messages cannot be sent before we fully complete
	// the handshake.
	if( FALSE == pConn->bHandshakePerformed )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Message other than control arrived before handshake performed.");
		l5_connector_Disconnect( pConn, FALSE, L5_RESULT_INVALID_PROTOCOL );
		return;
	}

	// Handle requests and replies
	if( 0 == (pReceivedMessage->fbFlags & L5_MESSAGE_FLAG_REPLY) )
	{
		l5_connector_HandleRequestMessage( pReceivedMessage, pConn );
	}
	else
	{
		l5_connector_HandleReplyMessage( pReceivedMessage, pConn );
	}
}

void l5_connector_HandleEventMessage( 
									   tL5Message *pReceivedMessage,
									   tL5ClientConnection *pConn )
{
	L5_TARGET_ID targetId;

	switch(pReceivedMessage->dwMessageID)
	{
	case L5_EVENT_DRIVER_CONNECTED:
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "Got driver connected message");
		if (NULL != pConn->pfnEventHandler)
		{
			pConn->pfnEventHandler( pConn, L5_EVENT_DRIVER_CONNECTED, &targetId, pConn->pvUserContext );
		}
		break;

	case L5_EVENT_DRIVER_DISCONNECTED:
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_NOTICE, "Got driver disconnected message");
		if (NULL != pConn->pfnEventHandler)
		{
			pConn->pfnEventHandler( pConn, L5_EVENT_DRIVER_DISCONNECTED, &targetId, pConn->pvUserContext );
		}
		break;
	}
}

void l5_connector_HandleControlMessage( 
	tL5Message *pReceivedMessage,
	tL5ClientConnection *pConn )
{
	L5_RESULT Result;
	L5_TARGET_ID TargetID;

	// Verify that we got a valid control message ID
	if( (L5_CONTROL_MESSAGE_HANDSHAKE != pReceivedMessage->dwMessageID) &&
		(L5_CONTROL_MESSAGE_FAILURE != pReceivedMessage->dwMessageID) 
		&&(L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION != pReceivedMessage->dwMessageID)
		)
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "L5_RESULT_INVALID_PROTOCOL. Bad MessageID.");
		Result = L5_RESULT_INVALID_PROTOCOL;
		goto finalize;
	}

	// Verify that the payload is of the right size
	if( (
			( 
			 (L5_CONTROL_MESSAGE_HANDSHAKE == pReceivedMessage->dwMessageID) ||
			 (L5_CONTROL_MESSAGE_FAILURE == pReceivedMessage->dwMessageID)
			)
			&&
			( sizeof(L5_RESULT) != pReceivedMessage->dwSentBufferSize )
		)
		||
		(
			(L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION == pReceivedMessage->dwMessageID)
			&&
			( sizeof(L5_TARGET_ID) != pReceivedMessage->dwSentBufferSize )
		)
	  )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "L5_RESULT_INVALID_PROTOCOL. Wrong message payload size.");
		Result = L5_RESULT_INVALID_PROTOCOL;
		goto finalize;
	}

	// Did we already do the handshake?
	if( (L5_CONTROL_MESSAGE_HANDSHAKE == pReceivedMessage->dwMessageID) &&
		(TRUE == pConn->bHandshakePerformed) )
	{
		Result = L5_RESULT_INVALID_PROTOCOL;
		goto finalize;
	}

	// Get the result
	Result = *((L5_RESULT*)(&(pReceivedMessage->baSentBuffer)));

	// Handle another TargetID's disconnection notification
	if (L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION == pReceivedMessage->dwMessageID)
	{
		// Get the TargetID which was disconnected
		TargetID = *((L5_TARGET_ID*)(&(pReceivedMessage->baSentBuffer)));

		// Call the event handler to notify the user of the other TargetID's disconnection
		if( NULL != pConn->pfnEventHandler )
		{
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Got L5_EVENT_OTHER_DISCONNECTED. Calling Wrapper's EventHandler ...");
			pConn->pfnEventHandler( pConn, L5_EVENT_OTHER_DISCONNECTED, &TargetID, pConn->pvUserContext );
		}
	}

finalize:
	// XXX do we disconnect on error even if handshake not yet performed ?
	if( ( TRUE == pConn->bHandshakePerformed ) && ( Result == L5_RESULT_INVALID_PROTOCOL ) )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "Handshake Allready Performed!");
		l5_connector_Disconnect( pConn, FALSE, Result );
	}
	else if( Result == L5_RESULT_SERVICE_SHUTTING_DOWN )
	{
		// TODO - XXX - Ask Oran [Anat]
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_CRITICAL, "Service is shutting down!");
		l5_connector_Disconnect( pConn, FALSE, Result );
	}
	else if (L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION != pReceivedMessage->dwMessageID)
	{
		l5_connector_ReturnReply( pConn, NULL, Result );
	}
}

void l5_connector_HandleRequestMessage( 
	tL5Message *pReceivedMessage,
	tL5ClientConnection *pConn )
{
	BYTE baReplyMessage[ sizeof(tL5Message) + L5_DISPATCHER_MAX_MESSAGE_BUFFER_SIZE ];
	tL5Message *pReplyMessage = (tL5Message*)baReplyMessage;
	L5_RESULT Result;

	// Prepare some of the reply message fields before invoking SendReceiveMessage
	pReplyMessage->SourceID = L5_TARGET_GENERIC_APPLICATION;
	pReplyMessage->TargetID = pReceivedMessage->SourceID;
	pReplyMessage->fbFlags = L5_MESSAGE_FLAG_REPLY;
	pReplyMessage->dwSequentialNumber = pReceivedMessage->dwSequentialNumber;
	pReplyMessage->dwMessageID = 0;
	pReplyMessage->dwMaxReplyBufferSize = 0;
	pReplyMessage->dwSentBufferSize = pReceivedMessage->dwMaxReplyBufferSize;

	if( NULL != pConn->pfnMessagesHandler )
	{
		/* Currently, there is a single thread per connection that can handle
		 * requests, but this is an inexpensive call.
		 */
		pConn->dwHandlingRequestThreadID = OSAL_get_threadid();	

		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "Got request from AppSrv. Calling Wrapper's MessagesHandler ...");
		pConn->pfnMessagesHandler( 
			(L5_CONNECTION)pConn,
			pReceivedMessage->SourceID,
			
			pReceivedMessage->dwMessageID,
			(void*)(&(pReceivedMessage->baSentBuffer)),
			pReceivedMessage->dwSentBufferSize,

			&(pReplyMessage->dwMessageID),
			&(pReplyMessage->baSentBuffer),
			&(pReplyMessage->dwSentBufferSize),
			
			pConn->pvUserContext,
			NULL );

		pConn->dwHandlingRequestThreadID = 0;
	}
	else
	{
		pReplyMessage->fbFlags = L5_MESSAGE_FLAG_REPLY | L5_MESSAGE_FLAG_ERROR;
		pReplyMessage->dwMessageID = L5_RESULT_NO_HANDLER;
		pReplyMessage->dwSentBufferSize = 0;
	}
	
	// Send the reply
	Result = L5_COMMON_UTILS_SendMessage( pConn->SocketContext, pReplyMessage );

	// XXX handle error
	if (L5_RESULT_OK != Result )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "Failed to send reply to a request that arrived from AppSrv. Result = %d", Result);
		//ASSERT( );
		return;
	}
}

void l5_connector_HandleReplyMessage( 
	tL5Message *pReceivedMessage,
	tL5ClientConnection *pConn )
{
	L5_RESULT Result = L5_RESULT_OK;
	//BOOL bErrorRequiresDisconnection = FALSE;

	if( FALSE == L5_COMMON_UTILS_VerifyReplyMessage(
			pReceivedMessage,
			&(pConn->tExpectedReply)) )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "L5_COMMON_UTILS_VerifyReplyMessage failed.");
		l5_connector_Disconnect( pConn, FALSE, L5_RESULT_INVALID_PROTOCOL );  // XXX: Do we need an ASSERT here?
		return;
	}

	// Check whether the reply message is an error.
	// In such case, the error value is placed in the dwMessageID member variable.
	if( 0 != (pReceivedMessage->fbFlags & L5_MESSAGE_FLAG_ERROR) )
	{
		Result = (L5_RESULT)pReceivedMessage->dwMessageID;
	}

	l5_connector_ReturnReply( 
		pConn, 
		(L5_RESULT_OK == Result) ? pReceivedMessage : NULL,
		Result );
}

void l5_connector_HandleDisconnection( SOCKETS_CLIENT_ID Socket, void *pvContext )
{
	/* XXX This function may be called because of an error and not only because
	 * the other side has disconnected.
	 *
	 * We must not free the connection now because we're disconnecting from the
	 * sockets callback.
	 */

	UNREFERENCED_PARAMETER(Socket);

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "l5_connector_HandleDisconnection(IN)");
	l5_connector_Disconnect( (tL5ClientConnection*)pvContext, FALSE, L5_RESULT_OTHER_SIDE_DISCONNECTED );
	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "l5_connector_HandleDisconnection(OUT)");
}

void l5_connector_Disconnect( 
	tL5ClientConnection *pConn,
	BOOL bFreeConnection,
	L5_RESULT Reason )
{
	//VERIFY( NULL != pConn );
	if ( NULL == pConn )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "NULL == pConn");
		return;
	}
	
	//VERIFY( L5_RESULT_OK != Reason );
	if ( L5_RESULT_OK == Reason )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "L5_RESULT_OK == Reason");
		return;
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "l5_connector_Disconnect(IN)");	
	// Should we disconnect from the server?
	// This if statement will only be executed once per connection.
	// This will prevent from anyone from entering this if statement again.
	if( FALSE == OSAL_atomic_compareExchange((LPLONG)&(pConn->bDisconnected), TRUE, FALSE) )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "L5_EVENT_DISCONNECTED - pConn->bDisconnected = TRUE for pCon=%d",pConn);	
		if( FALSE == pConn->bHandshakePerformed )
		{
			// This is a very specific state. Verify that all is OK.
			//VERIFY( TRUE == pConn->tExpectedReply.bWaitingForReply );
			if ( TRUE != pConn->tExpectedReply.bWaitingForReply )
			{
				TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "TRUE != pConn->tExpectedReply.bWaitingForReply");
				return;
			}
			//VERIFY( FALSE == bFreeConnection );
			if ( FALSE != bFreeConnection )
			{
				TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "FALSE != bFreeConnection");
				return;
			}

			// Make sure that we don't enter this function again - the ASSERT
			// above will fail.
			pConn->bDisconnected = TRUE;
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_DEBUG, "L5_EVENT_DISCONNECTED - pConn->bDisconnected = TRUE for pCon=%d",pConn);	

			// The connection will be cleaned up by the Connect() function.
			l5_connector_ReturnReply( pConn, NULL, Reason );
			return;
		}

		/* Call the event handler to notify the user that we're disconnecting.
		 * This should only be done if we're currently connected. This is determined
		 * by testing (NULL != pConn->Socket).
		 */
		if( NULL != pConn->pfnEventHandler )
		{
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "L5_EVENT_DISCONNECTED. Calling Wrapper's EventHandler ...");
			pConn->pfnEventHandler( pConn, L5_EVENT_DISCONNECTED, &Reason, pConn->pvUserContext );
		}

		/* Are we waiting for a reply? If we do, release the waiting thread with an error.
		 *
		 * WARNING WARNING WARNING: If a thread that is currently waiting for a reply is
		 * calling this function - this will result in a deadlock. This is because the
		 * l5_connector_ReturnReply() function that will wait for the hReplyHandled event
		 * to be raised by the same thread.
		 * Before calling this function, the thread that is waiting for a reply must clear
		 * the bWaitingForReply boolean.
		 */
		if( TRUE == pConn->tExpectedReply.bWaitingForReply )
		{
			l5_connector_ReturnReply( pConn, NULL, Reason );
		}
	}

	if( TRUE == bFreeConnection )
	{
		if (!useNPIPE)
		{
			CLIENTS_SOCKETS_DisconnectFromServer( pConn->SocketContext );
			CLIENTS_SOCKETS_Fini( &(pConn->SocketContext) );
		}
		else if (useNPIPE)
		{
			CLIENTS_NPIPE_DisconnectFromServer( pConn->SocketContext );
			CLIENTS_NPIPE_Fini(&(pConn->SocketContext));
		}
		OSAL_delete_critical_section( &(pConn->csSendReceive) );
		OSAL_delete_event( pConn->hReplyHandled );
		OSAL_delete_event( pConn->hReplyAvailable );
		OSAL_free(  (LPVOID)(pConn) );		
	}

	TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "l5_connector_Disconnect(OUT)");	
}

void l5_connector_ReturnReply( tL5ClientConnection *pConn, tL5Message *ptMessage, L5_RESULT Result )
{
	//VERIFY( NULL != pConn );
	if ( NULL == pConn )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "NULL == pConn");
		return;
	}
	//VERIFY( TRUE == pConn->tExpectedReply.bWaitingForReply );
	if ( TRUE != pConn->tExpectedReply.bWaitingForReply )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "TRUE != pConn->tExpectedReply.bWaitingForReply");
		return;
	}

	pConn->ptReplyMessage = ptMessage;
	pConn->ReplyResult = Result;
	//TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "OSAL_set_event( pConn->hReplyAvailable 0x%x )",pConn->hReplyAvailable);
	OSAL_set_event( pConn->hReplyAvailable );

	//VERIFY( WAIT_OBJECT_0 == OSAL_wait_event(pConn->hReplyHandled, INFINITE) );
	if ( WAIT_OBJECT_0 != OSAL_wait_event(pConn->hReplyHandled, 5000/*INFINITE*/) )
	{
		TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "WAIT_OBJECT_0 != OSAL_wait_event(pConn->hReplyHandled, INFINITE)");
		return;
	}
}
