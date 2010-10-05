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
// OSAL
#include "wimax_osal_primitives.h"
#include <unistd.h>
#include <stdlib.h>

// Project
#include "L5Dispatcher.h"

#include "CommonServices.h"

#include "L5OpCodes.h"		
#include "L5Common.h"
#include "L5CommonUtils.h"

#include "Messenger.h"
#include "TraceModule.h"

#include "Act.h"




//////////////////////////////////////////////////////////////////////////
// Prototypes 

// Utility functions
L5_TARGET_ID l5_dispatcher_AllocateNextTargetID();
tL5DispatcherConnection *l5_dispatcher_FindAllocConnectionByTargetID( L5_TARGET_ID nTargetID);
tL5DispatcherConnection *l5_dispatcher_FindAvailableConnection( void );

static List FreeList;
static List AllocList;
static OSAL_critical_section internalLock;


//////////////////////////////////////////////////////////////////////////
// Global variables
//static tL5DispatcherConnection g_atConnections[L5_DISPATCHER_MAX_CONNECTIONS]; // The L5 Connectors array.
static L5_TARGET_ID g_nNextTargetID;	// Holds the next available Target ID

typedef enum _INTERANL_REQUEST_ID
{
	NOTIFY_OF_DISCONNECTION = 0,
	RELEASE_CONNECTION
} INTERANL_REQUEST_ID;

//////////////////////////////////////////////////////////////////////////
// Implementation



// lock ok
BOOL L5_DISPATCHER_Initialize()
{
	int i;
	tL5DispatcherConnection *tempItem;

	OSAL_init_critical_section(&internalLock);
	List_Init(&FreeList,TRUE);
	List_Init(&AllocList,TRUE);

	for( i = 0; i < L5_DISPATCHER_MAX_CONNECTIONS; i++ )
	{
		tempItem = (tL5DispatcherConnection *)malloc(sizeof(tL5DispatcherConnection));
		tempItem->bFree = TRUE;
		OSAL_init_critical_section( &(tempItem->rwlConn) );

		List_AddItem(&FreeList,tempItem);
	}


	g_nNextTargetID = (L5_TARGET_ID)L5_DISPATCHER_MAX_PRESERVED_TARGET_IDS;
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_NOTICE, "L5_DISPATCHER_Initialize Succeed!");
	return TRUE;
}

void L5_DISPATCHER_Shutdown()
{
	UINT32 i;
	ListItem *tempItem;
	UINT32 listLen = 0;


	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_NOTICE, "Starting Shutdown.");

	OSAL_enter_critical_section(AllocList.pLock);
	listLen = AllocList.dwLength;
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Inside closing the pAllocList that have %d connections",listLen);
	tempItem = AllocList.pHead;
	for( i = 0; i <listLen ; i++ )
	{
		if(NULL != tempItem && NULL != tempItem->pData)
		{
			TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Inside closing the [%d] out of [%d] in the pAllocList List",i,listLen);
			OSAL_delete_critical_section(&(((tL5DispatcherConnection *)(tempItem->pData))->rwlConn));
			free(tempItem->pData);
		}
		if(tempItem->pNextItem)
		{
			tempItem = tempItem->pNextItem;
		}
	}
	OSAL_exit_critical_section(AllocList.pLock);
	
	

	List_Clear(&AllocList);
	List_Finalize(&AllocList);
	
	OSAL_enter_critical_section(FreeList.pLock);
	listLen = FreeList.dwLength;
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Inside closing the pFreeList that have %d members",listLen);

	tempItem = FreeList.pHead;
	for( i = 0; i < listLen; i++ )
	{
		if(NULL != tempItem && NULL != tempItem->pData)
		{
			TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Inside closing the [%d] out of [%d] in the pFreeList List",i,listLen);
			OSAL_delete_critical_section(&(((tL5DispatcherConnection *)(tempItem->pData))->rwlConn));
			free(tempItem->pData);
		}
		if(tempItem->pNextItem)
		{
			tempItem = tempItem->pNextItem;
		}
	}
	OSAL_exit_critical_section(FreeList.pLock);
	
	List_Clear(&FreeList);
	List_Finalize(&FreeList);

	OSAL_delete_critical_section(&internalLock);
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_NOTICE, "Shutdown Succeed!");
}


L5_RESULT L5_DISPATCHER_ConnectEx(	
								  L5_TARGET_ID nTargetID,
								  tpfnMessagesHandler pfnMessagesHandler,
								  tpfnEventHandler pfnEventHandler,
								  void *pvUserContext,
								  THREAD_ID threadId,
								  L5_CONNECTION *Conn )
{
	UNREFERENCED_PARAMETER(threadId);
	
	return L5_DISPATCHER_ConnectInternal(NULL, 0, nTargetID, pfnMessagesHandler, pfnEventHandler, pvUserContext, Conn); 
}

L5_RESULT L5_DISPATCHER_Connect(	
								tpfnMessagesHandler pfnMessagesHandler,
								tpfnEventHandler pfnEventHandler,	
								L5_CONNECTION *Conn )
{
	return L5_DISPATCHER_ConnectInternal(NULL, 0, L5_TARGET_DYNAMIC, pfnMessagesHandler, pfnEventHandler, NULL, Conn);
}

// lock ok
L5_RESULT L5_DISPATCHER_ConnectInternal(
										char *szHostName,
										int nPort,
										L5_TARGET_ID nTargetID,
										tpfnMessagesHandler pfnMessagesHandler,
										tpfnEventHandler pfnEventHandler,
										void *pvUserContext,

										L5_CONNECTION *pConn )
{	
	L5_RESULT Result = L5_RESULT_OK;
	tL5DispatcherConnection *pCurrentConn;
	tL5DispatcherConnection *pTempConn;

	UNREFERENCED_PARAMETER(nPort);
	UNREFERENCED_PARAMETER(szHostName);

	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "L5_DISPATCHER_ConnectInternal(IN)");

	// VERIFY( pConn != NULL );
	if( pConn == NULL )
	{
		L5_DISPATCHER_SendErrorReport(L5_TARGET_CONTROL, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: pConn == NULL");
		return L5_RESULT_INVALID_PARAMS;
	}

	// Initialize the output variable first
	*pConn = NULL;

	// Find available connection slot
	OSAL_enter_critical_section(&internalLock);
	pCurrentConn = l5_dispatcher_FindAvailableConnection();
	if( NULL == pCurrentConn )
	{
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_ERR, "Connect Failed: Too many Connection!(TargetID=%d)", nTargetID);
		Result = L5_RESULT_TOO_MANY_CONNECTIONS;
		goto quit;
	}
	
	// Set the target ID
	if( L5_TARGET_DYNAMIC == nTargetID )
	{
		// Dynamic ID
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "L5_DISPATCHER_ConnectInternal(L5_TARGET_DYNAMIC)");
		nTargetID = l5_dispatcher_AllocateNextTargetID();		
	}
	else
	{
		// Preserved ID

		// Verify that the requested preserved ID is in the valid range
		if( nTargetID >= L5_DISPATCHER_MAX_PRESERVED_TARGET_IDS )
		{
			TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_CRITICAL, "Connect Failed, requested Target ID is out of range (%d)", nTargetID);
			Result = L5_RESULT_ID_OUT_OF_RANGE;
			goto quit;
		}

		// Verify that nobody else has already registered this ID
		pTempConn = l5_dispatcher_FindAllocConnectionByTargetID(nTargetID);
		if( NULL != pTempConn )
		{	
			TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_CRITICAL, "Connect Failed, requested Target ID already exist (%d)", nTargetID);
			Result = L5_RESULT_ID_ALREADY_EXISTS;
			goto quit;			
		}		
	}
	//if we have a spare connection available
	if(pCurrentConn)
	{
		// Actually set the members of the allocated slot
		// State
		pCurrentConn->bFree = FALSE;
		// Logic
		pCurrentConn->nTargetID = nTargetID;
		pCurrentConn->pfnMessagesHandler = pfnMessagesHandler;
		pCurrentConn->pfnEventHandler = pfnEventHandler;
		pCurrentConn->pvUserContext = pvUserContext;
		
		List_AddItem(&AllocList,pCurrentConn);		
		List_RemoveItem(&FreeList,pCurrentConn);
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "a new connection with target Id = %d was added", nTargetID);

		*pConn = (L5_CONNECTION)pCurrentConn;

	}

	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "L5_DISPATCHER_ConnectInternal(OUT). TargetID=%d, L5Connection=%d",pCurrentConn->nTargetID,pCurrentConn);

quit:		
	OSAL_exit_critical_section(&internalLock);
	return Result;
}


void L5_DISPATCHER_Disconnect( L5_CONNECTION Conn )
{
	tL5DispatcherConnection *pConn = (tL5DispatcherConnection*)Conn;
	UINT32 i = 0;
	ListItem *tempItem;
	UINT32 listLen = 0;

	OSAL_enter_critical_section(AllocList.pLock);
	listLen = AllocList.dwLength;

	tempItem = AllocList.pHead;
	
	// Actually free the connection
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "Disconnect Connection: TargetID = %d , pConn=%d", (pConn!=NULL)?pConn->nTargetID:0, pConn);
	//
	for(i=0; i<listLen; i++)
	{
		if (NULL != tempItem && pConn == tempItem->pData)
		{
			//if((pConn->nTargetID == ((tL5DispatcherConnection *)(tempItem->pData))->nTargetID) &&
			//	FALSE == ((tL5DispatcherConnection *)(tempItem->pData))->bFree)
			if (FALSE == ((tL5DispatcherConnection *)(tempItem->pData))->bFree)
			{
				((tL5DispatcherConnection *)(tempItem->pData))->bFree = TRUE;
				List_AddItem(&FreeList,(tempItem->pData));
				List_RemoveItem(&AllocList,(tempItem->pData));
				TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "The item was removed from pAllocList into pFreeList");
				break;
			}			
		}
		if (tempItem->pNextItem)
		{
			tempItem = tempItem->pNextItem;
		}		
	} 

	OSAL_exit_critical_section(AllocList.pLock);

	/*
	// Call the event handler
	if( NULL != pConn->pfnEventHandler )
	{ 
		pConn->pfnEventHandler( 
			(L5_CONNECTION)pConn,
			L5_EVENT_DISCONNECTED,
			(PVOID)((ULONG_PTR)L5_RESULT_USER_REQUESTED_DISCONNECT),
			pConn->pvUserContext );
	}
	*/
}

L5_RESULT L5_DISPATCHER_SentEvent(L5_CONNECTION Conn, L5_TARGET_ID nTargetID, L5_EVENT l5Event)
{
	tL5DispatcherConnection *pTargetConn;

	pTargetConn = l5_dispatcher_FindAllocConnectionByTargetID(nTargetID);
	if( NULL != pTargetConn && NULL != pTargetConn->pfnEventHandler )
	{ 
		pTargetConn->pfnEventHandler(Conn, l5Event, NULL, pTargetConn->pvUserContext);
	}

	return L5_RESULT_OK;
}

L5_RESULT L5_DISPATCHER_BroadcastEvent(L5_CONNECTION Conn, L5_EVENT l5Event)
{
	L5_TARGET_ID *targetId;
	ListItem *tempItem;
	UINT32 listLen = 0;
	UINT32 i = 0;	

	OSAL_enter_critical_section(AllocList.pLock);
	listLen = AllocList.dwLength;
	tempItem = AllocList.pHead;

	targetId = malloc(sizeof(L5_TARGET_ID) * listLen);

	for(i=0; i<listLen; i++)
	{
		if (NULL == tempItem || NULL == tempItem->pData)
		{
			continue;
		}

		targetId[i] = ((tL5DispatcherConnection *)(tempItem->pData))->nTargetID;
		//L5_DISPATCHER_SentEvent(Conn, targetId, l5Event);		
		tempItem = tempItem->pNextItem;
	}

	OSAL_exit_critical_section(AllocList.pLock);

	for(i=0; i<listLen; i++)
	{
		L5_DISPATCHER_SentEvent(Conn, targetId[i], l5Event);		
	}

	free(targetId);

	return L5_RESULT_OK;
}

L5_RESULT L5_DISPATCHER_SendReceiveMessage( 
	L5_CONNECTION Conn,
	L5_TARGET_ID nTargetID,

	UINT32 dwSendMessageID,
	void  *pvSendBuffer,
	UINT32 cbSendBufferSize,

	UINT32 *pdwReceiveMessageID,
	void  *pvReceiveBuffer,
	UINT32 *cbReceiveBufferSize )
{
	tL5DispatcherConnection *pOriginConn = (tL5DispatcherConnection*)Conn;
	tL5DispatcherConnection *pTargetConn;
	L5_RESULT Result = L5_RESULT_OK;

	// The dummy variables are used to 
	UINT32 dwDummyReceiveMessageID = 0;
	UINT32 cbDummyReceiveBufferSize = 0;

	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "L5_DISPATCHER_SendReceiveMessage");

	if( ( Conn == NULL ) ||
		( !L5_COMMON_UTILS_VerifyBufferAndSize( pvSendBuffer, &cbSendBufferSize ) ) ||
		( !L5_COMMON_UTILS_VerifyBufferAndSize( pvReceiveBuffer, cbReceiveBufferSize ) ) )
	{
		return L5_RESULT_INVALID_PARAMS;
	}

	//Lock the originalCon in order to prevent this connection while the messageHandler
	//TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Try to read lock TargetID (%d)", pOriginConn->nTargetID));
	OSAL_enter_critical_section( &(pOriginConn->rwlConn) );
	//TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Read lock TargetID (%d)", pOriginConn->nTargetID));

	// Search for the target ID
	//pTargetConn = l5_dispatcher_FindConnectionByTargetID( nTargetID);
	pTargetConn = l5_dispatcher_FindAllocConnectionByTargetID(nTargetID);

	if( ( NULL == pTargetConn ) || ( pTargetConn->bFree == TRUE ) )
	{
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_ERR, "SendReceiveMessage Failed! Target ID %d not found .", nTargetID);
		Result = L5_RESULT_ID_NOT_FOUND;
		goto finalize;
	}

	// Verify that there is a messages handler
	if( NULL == pTargetConn->pfnMessagesHandler )
	{
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_ERR, "SendReceiveMessage Failed! Target ID %d has no handler .", nTargetID);
		Result = L5_RESULT_NO_HANDLER;
		goto finalize;
	}
		
	if (pTargetConn->bFree)
	{
		TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_ERR, "pTargetConn->bFree = %d",pTargetConn->bFree);
		goto finalize;
	}

	// Actually send the message
	
	pTargetConn->pfnMessagesHandler( 
		pTargetConn,
		pOriginConn->nTargetID,

		dwSendMessageID,
		pvSendBuffer,
		cbSendBufferSize,

		(NULL == pdwReceiveMessageID) ? &dwDummyReceiveMessageID : pdwReceiveMessageID,
		pvReceiveBuffer,
		(NULL == cbReceiveBufferSize) ? &cbDummyReceiveBufferSize : cbReceiveBufferSize,

		pTargetConn->pvUserContext,
		(void*)(&Result) );

finalize:
	OSAL_exit_critical_section( &(pOriginConn->rwlConn) );

	//TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Unlock the lock on targetID (%d)", pOriginConn->rwlConn));
	return Result;
}


void L5_DISPATCHER_SendErrorReport( L5_TARGET_ID senderID, ERROR_REPORT_OPCODE opcode, const char* function, int line)
{
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_ERR, "Got Error Report from %s at line %d", function, line);
	Act_MessagesHandler(NULL, senderID, ACT_OPCODE_ERROR_REPORT, &opcode, sizeof(opcode),NULL,NULL,NULL,NULL,NULL);
}

void L5_DISPATCHER_SendDeviceRemoveReport(L5_TARGET_ID senderID)
{	
	Act_MessagesHandler(NULL, senderID, ACT_OPCODE_DEVICE_REMOVED, NULL, 0,NULL,NULL,NULL,NULL,NULL);
}

// lock ok - not needed
tL5DispatcherFunctions *L5_DISPATCHER_GetServiceDispatcherFunctions()
{
	static tL5DispatcherFunctions funcs = {
		&L5_DISPATCHER_Connect,
		&L5_DISPATCHER_ConnectEx,
		&L5_DISPATCHER_Disconnect,
		&L5_DISPATCHER_SendReceiveMessage,
		NULL, /*&L5_DISPATCHER_RegisterCtrlStatusUpdatesCB,*/
		NULL, /*&L5_DISPATCHER_UnregisterCtrlStatusUpdatesCB,*/
		NULL, /*&L5_DISPATCHER_GetCtrlStatus,*/
		NULL, /*&L5_DISPATCHER_SetConnParams*/
		&L5_DISPATCHER_SendErrorReport
	};

	return &funcs;
}

//////////////////////////////////////////////////////////////////////////
// Utility functions

// lock ok - not needed - must be performed by the caller
L5_TARGET_ID l5_dispatcher_AllocateNextTargetID()
{
	L5_TARGET_ID nResult;
	tL5DispatcherConnection *pTempCon;

	do
	{
		// Allocate next ID
		nResult = g_nNextTargetID;
		g_nNextTargetID = (L5_TARGET_ID)((int)g_nNextTargetID + 1);

		// Handle wraparound
		if( 0 == g_nNextTargetID )
		{
			g_nNextTargetID = (L5_TARGET_ID)L5_DISPATCHER_MAX_PRESERVED_TARGET_IDS;
		}

		/* Note that entering an endless loop is impossible here. This is because
		* there is a limited number of allowed connections at any given time.
		*/

		pTempCon = l5_dispatcher_FindAllocConnectionByTargetID(nResult);
		if ( NULL != pTempCon)
		{
			//			OSAL_exit_critical_section( &(pTempCon->rwlConn) );
			TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_INFO, "Unlock the lock on targetID (%d)", pTempCon->rwlConn);
		}


	} while( NULL !=  pTempCon);

	return nResult;
}

tL5DispatcherConnection *l5_dispatcher_FindAllocConnectionByTargetID( L5_TARGET_ID nTargetID )
{
	tL5DispatcherConnection *resItem = NULL;
	ListItem *tempItem = NULL;
	UINT32 i = 0;
	UINT32 listLen = 0;
	
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Enter into l5_dispatcher_FindAllocConnectionByTargetID function");

	OSAL_enter_critical_section(AllocList.pLock);


	listLen = AllocList.dwLength;
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "the length of pAllocList list is %d", listLen );
	tempItem = AllocList.pHead;

	for(i=0; i<listLen; i++)
	{
		if (NULL == tempItem || NULL == tempItem->pData)
		{
			continue;
		}
		if((FALSE == ((tL5DispatcherConnection *)(tempItem->pData))->bFree) && (nTargetID == ((tL5DispatcherConnection *)(tempItem->pData))->nTargetID))
		{
			TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "the connection in pAllocList list was found - targetId = %d", nTargetID );
			OSAL_exit_critical_section(AllocList.pLock);
			return ((tL5DispatcherConnection *)(tempItem->pData));
		}
		tempItem = tempItem->pNextItem;
	}
	OSAL_exit_critical_section(AllocList.pLock);
	
	TRACE(TR_MOD_L5_DISPATCHER, TR_SEV_DEBUG, "Leave l5_dispatcher_FindAllocConnectionByTargetID function");

	return resItem;
}

// lock ok - by the caller
// if available connection found - the connection is locked for write and returned (unlock write responsibility lies on caller)
tL5DispatcherConnection *l5_dispatcher_FindAvailableConnection( void )
{
	tL5DispatcherConnection *pRetConnection = NULL;
	if( FreeList.pHead )
	{
		pRetConnection = (tL5DispatcherConnection *)(FreeList.pHead->pData);
		return pRetConnection;
	}


	return NULL;
}

