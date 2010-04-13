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
#include "wimax_osal_config_controler.h"
#include "wimax_osal_string.h"
// Project
#include "CommonServices.h"
#include "L5Common.h"
#include "L5CommonUtils.h"

#include "TraceModule.h"


#if defined(L5_USE_SERVER_SOCKETS)
#include "IPC_Server.h"
#elif defined(L5_USE_CLIENT_SOCKETS)
#include "IPC_Client.h"
#else
#error Either L5_USE_SERVER_SOCKETS or L5_USE_CLIENT_SOCKETS must be defined!
#endif

//////////////////////////////////////////////////////////////////////////
// Prototypes
L5_RESULT l5_common_utils_ActuallySendMessage(
	SOCKETS_CLIENT Socket,
	tL5Message *pMessage );


BOOL checkedInfra = FALSE;
BOOL useNPIPE = FALSE;

//////////////////////////////////////////////////////////////////////////
// Implementation


/********************************************************************
 * Function: L5_COMMON_UTILS_VerifyL5MessageSizes
 *******************************************************************/
BOOL L5_COMMON_UTILS_VerifyL5MessageSizes( tL5Message *pMessage )
{
	if (pMessage == NULL)
	{
		return FALSE;
	}

	if( (pMessage->dwMaxReplyBufferSize > L5_DISPATCHER_MAX_MESSAGE_BUFFER_SIZE) ||
		(pMessage->dwSentBufferSize > L5_DISPATCHER_MAX_MESSAGE_BUFFER_SIZE) )
	{
		return FALSE;
	}

	return TRUE;
}


/********************************************************************
 * Function: L5_COMMON_UTILS_SendMessageParams
 *******************************************************************/
L5_RESULT L5_COMMON_UTILS_SendMessageParams( 
	SOCKETS_CLIENT Socket,

	L5_TARGET_ID SourceID,
	L5_TARGET_ID TargetID,
	BYTE fbFlags,
	UINT32 dwSequentialNumber,
	UINT32 dwMessageID,
	UINT32 dwMaxReplyBufferSize,
	UINT32 dwSentBufferSize,
	BYTE *pbaSentBuffer )
{
	L5_RESULT result;
	BYTE baMessage[ sizeof(tL5Message) + L5_DISPATCHER_MAX_MESSAGE_BUFFER_SIZE ];
	tL5Message *pMessage = (tL5Message*)baMessage;

	if(!L5_COMMON_UTILS_VerifyBufferAndSize( (void*)pbaSentBuffer, &dwSentBufferSize ))
	{
		return L5_RESULT_INVALID_PARAMS;
	}

	pMessage->SourceID = SourceID;
	pMessage->TargetID = TargetID;
	pMessage->fbFlags = fbFlags;
	pMessage->dwSequentialNumber = dwSequentialNumber;
	pMessage->dwMessageID = dwMessageID;
	pMessage->dwMaxReplyBufferSize = dwMaxReplyBufferSize;
	pMessage->dwSentBufferSize = dwSentBufferSize;

	if( FALSE == L5_COMMON_UTILS_VerifyL5MessageSizes(pMessage) )
	{
		return L5_RESULT_INVALID_PARAMS;
	}

	if( 0 != dwSentBufferSize )
	{
		OSAL_memcpy_s( pMessage->baSentBuffer, dwSentBufferSize, pbaSentBuffer, dwSentBufferSize );
	}

	result = l5_common_utils_ActuallySendMessage( Socket, pMessage );

	return result;
}

/********************************************************************
* Function: L5_COMMON_UTILS_SendEventMessage
*******************************************************************/
L5_RESULT L5_COMMON_UTILS_SendEventMessage( 
	SOCKETS_CLIENT Socket,
	L5_EVENT EventMessage,
	UINT32 dwPayload )
{
	L5_RESULT result;
	BYTE baMessage[sizeof(tL5Message) + sizeof(UINT32)] = {0};
	tL5Message *pMessage = (tL5Message*)(&baMessage);

	pMessage->SourceID = L5_TARGET_EVENT;
	pMessage->TargetID = L5_TARGET_EVENT;
	pMessage->dwMessageID = EventMessage;
	pMessage->dwSentBufferSize = sizeof(UINT32);
	pMessage->dwMaxReplyBufferSize = sizeof(UINT32);

	*((UINT32*)(&(pMessage->baSentBuffer))) = dwPayload;

	result = l5_common_utils_ActuallySendMessage( Socket, pMessage );

	return result;
}



/********************************************************************
 * Function: L5_COMMON_UTILS_SendControlMessage
 *******************************************************************/
L5_RESULT L5_COMMON_UTILS_SendControlMessage( 
	SOCKETS_CLIENT Socket,
	L5_CONTROL_MESSAGE ControlMessage,
	L5_TARGET_ID targetID,
	UINT32 dwPayload )
{
	L5_RESULT result;
	BYTE baMessage[sizeof(tL5Message) + sizeof(UINT32)] = {0};
	tL5Message *pMessage = (tL5Message*)(&baMessage);

	TRACE(TR_MOD_SERVICE, TR_SEV_NOTICE, "Send target is %d", targetID);

	pMessage->SourceID = L5_TARGET_CONTROL;
	//pMessage->TargetID = L5_TARGET_CONTROL;
	pMessage->TargetID = targetID;
	pMessage->dwMessageID = ControlMessage;
	pMessage->dwSentBufferSize = sizeof(UINT32);
	pMessage->dwMaxReplyBufferSize = sizeof(UINT32);
	
	*((UINT32*)(&(pMessage->baSentBuffer))) = dwPayload;

	result = l5_common_utils_ActuallySendMessage( Socket, pMessage );

	TRACE(TR_MOD_SERVICE, TR_SEV_NOTICE, "Result of ActuallySendMessage is %d %d", result);

	return result;
}


/********************************************************************
 * Function: L5_COMMON_UTILS_SendMessage
 *******************************************************************/
L5_RESULT L5_COMMON_UTILS_SendMessage( 
	SOCKETS_CLIENT Socket,
	tL5Message *pMessage )
{
	L5_RESULT result;
	if( FALSE == L5_COMMON_UTILS_VerifyL5MessageSizes(pMessage) )
	{
		return L5_RESULT_INVALID_PARAMS;
	}

	result = l5_common_utils_ActuallySendMessage( Socket, pMessage );

	return result;
}


/********************************************************************
 * Function    : l5_common_utils_ActuallySendMessage
 * Purpose     : 
 * Arguments   : 
 * Return value: 
 * Context     : 
 * Assumptions : 
 *******************************************************************/
L5_RESULT l5_common_utils_ActuallySendMessage(
	SOCKETS_CLIENT Socket,
	tL5Message *pMessage )
{
	char answer[MAX_ANSWER_SIZE];
	UINT32 res;
		
	TRACE(TR_MOD_SERVICE, TR_SEV_NOTICE, "Sending from sourceid: %d, to targetid: %d", pMessage->SourceID, pMessage->TargetID);

	if (!checkedInfra)
	{
		//check if to use sockets or NPIPE
		res = OSAL_ConfigController_GetStrValue(OSAL_KEY_ENTRY_PIPEDEV, OSAL_KEY_ENTRY_IPC, answer, MAX_ANSWER_SIZE);	
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
		checkedInfra = TRUE;
	}

#if defined(L5_USE_SERVER_SOCKETS)
	if (!useNPIPE)
	{
		if( SOCKET_ERROR == SERVER_SOCKETS_SendToClient( 
							(char*)pMessage,
							sizeof(tL5Message) + pMessage->dwSentBufferSize,
							Socket) )
		{
			return L5_RESULT_SOCKETS_ERROR;
		}
	}
	else if(useNPIPE)
	{
		if( SOCKET_ERROR == SERVER_NPIPE_SendToClient( 
		(char*)pMessage,
		sizeof(tL5Message) + pMessage->dwSentBufferSize,
		Socket) )
		{
			return L5_RESULT_SOCKETS_ERROR;
		}
	}

#elif defined(L5_USE_CLIENT_SOCKETS)
	if (!useNPIPE)
	{
		if( SOCKET_ERROR == CLIENTS_SOCKETS_SendToServer( 
							(char*)pMessage,
							sizeof(tL5Message) + pMessage->dwSentBufferSize,
							Socket) )
		{
			return L5_RESULT_SOCKETS_ERROR;
		}
	}
	else if (useNPIPE)
	{
		if( SOCKET_ERROR == CLIENTS_NPIPE_SendToServer( 
		(char*)pMessage,
		sizeof(tL5Message) + pMessage->dwSentBufferSize,
		Socket) )
		{
			return L5_RESULT_SOCKETS_ERROR;
		}
	}

#else
#error Either L5_USE_SERVER_SOCKETS or L5_USE_CLIENT_SOCKETS must be defined!
#endif
	
	return L5_RESULT_OK;
}

/*
 *	pvBuffer	pdwSize
 *	NULL		NULL/zero	OK		No data, no length.
 *	NULL		non-zero	ERROR	We have the data length, but there is no
 *									actual data. This is an error.
 *	ptr			NULL/zero	OK		There is a valid pointer to the data, but
 *									the length of it is zero.
 *	ptr			non-zero	OK		There is data to send/receive. The most
 *									common case.
 */
BOOL L5_COMMON_UTILS_VerifyBufferAndSize( void *pvBuffer, UINT32 *pdwSize )
{
	if( (NULL == pvBuffer) && (0 != NULL_PTR_VAL_OR_ZERO(pdwSize)) )
	{
		//TRACE(TR_MOD_SERVICE, TR_SEV_ERR, "verification failed");
		return FALSE;
	}

	return TRUE;
}

BOOL L5_COMMON_UTILS_VerifyReplyMessage( tL5Message *pMessage, tL5ExpectedReplyMessageParams *pExpected )
{
	if( 0 == (pMessage->fbFlags & L5_MESSAGE_FLAG_REPLY) )
	{
		//TRACE(TR_MOD_SERVICE, TR_SEV_ERR, "verification failed");
		return FALSE;
	}

	if( (FALSE == pExpected->bWaitingForReply)								||
		(pExpected->nTargetID			!= pMessage->TargetID)				||
		(pExpected->dwSequentialNumber	!= pMessage->dwSequentialNumber)	||
		(pExpected->dwMaxReplySize		<  pMessage->dwSentBufferSize) )
	{
		return FALSE;
	}

	if( (0 != (pMessage->fbFlags & L5_MESSAGE_FLAG_ERROR)) && 
		(L5_RESULT_OK == (L5_RESULT)pMessage->dwMessageID) )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL L5_COMMON_UTILS_IsTargetNotExist( L5_RESULT Result )
{
	//each of the following L5Result mean that the connection is no exist any more.
	return	(L5_RESULT_ALREADY_DISCONNECTED == Result) ||
			(L5_RESULT_OTHER_SIDE_DISCONNECTED == Result) ||
			(L5_RESULT_ID_NOT_FOUND == Result) ||
			(L5_RESULT_NO_HANDLER == Result) || 
			(L5_RESULT_SOCKETS_ERROR == Result);
}

