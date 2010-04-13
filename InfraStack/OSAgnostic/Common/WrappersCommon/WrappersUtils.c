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
#include "wimax_osal_primitives.h"

#include "Services_Ctrl.h"
#include "WrappersUtils.h"
#include "WrappersCommon.h"
#include "CommonServices.h"
#include "L5OpCodes.h"	

#include "TraceModule.h"


EXPORT wmx_Status_t wmx_L5ResultToWMXStatus( L5_RESULT l5Result )
{
	switch( l5Result ) 
	{
	case L5_RESULT_OK:
		return WMX_ST_OK;

	case L5_RESULT_TOO_MANY_CONNECTIONS:
	case L5_RESULT_INVALID_PROTOCOL:
	case L5_RESULT_NO_TARGET_SEQ_MATCH:
	case L5_RESULT_ID_OUT_OF_RANGE:
	case L5_RESULT_ID_ALREADY_EXISTS:
	case L5_RESULT_ID_NOT_FOUND:
	case L5_RESULT_NO_HANDLER:
	case L5_RESULT_INVALID_PARAMS:
	case L5_RESULT_MEMORY_ALLOC_FAILED:
	case L5_RESULT_SOCKETS_ERROR:
	case L5_RESULT_CREATE_EVENT_FAILED:
	case L5_RESULT_TIMED_OUT:
	case L5_RESULT_WAIT_FAILED:
	case L5_RESULT_TOO_MANY_WAITING_FOR_REPLIES:
	case L5_RESULT_CANT_DO_DURING_CALLBACK:
		return WMX_ST_PIPE_FAILURE;

	case L5_RESULT_SERVICE_SHUTTING_DOWN:
	case L5_RESULT_ALREADY_DISCONNECTED:
	case L5_RESULT_USER_REQUESTED_DISCONNECT:
	case L5_RESULT_OTHER_SIDE_DISCONNECTED:
		return WMX_ST_PIPE_NOT_CONNETED;

	case L5_RESULT_ACCESSIBILITY_ERROR:
		return WMX_ST_ACCESSIBILITY_ERROR;

	default:
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "Unknown L5 Result: %d", l5Result);		
		return WMX_ST_FAIL;
	}
}



EXPORT wmx_Status_t wmx_L4ResultToWMXStatus( E_L3L4ResponseStatus l3l4ResponseStatus )
{
	switch (l3l4ResponseStatus)
	{
	case L3L4_RESPONSE_STATUS_SUCCESS_DONE:
	case L3L4_RESPONSE_STATUS_SUCCESS_IN_PROCESS:
		return WMX_ST_OK;

	case L3L4_RESPONSE_STATUS_NO_RF:
		return WMX_ST_NO_RF;

	case L3L4_RESPONSE_STATUS_UNKNOWN_ERROR:
	case L3L4_RESPONSE_STATUS_PRODUCTION_ERROR:
	case L3L4_RESPONSE_STATUS_NOT_READY_FOR_POWER_SAVE:
	case L3L4_RESPONSE_STATUS_THERMAL_CRITICAL:
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "The orig status returned from the driver is: %d", l3l4ResponseStatus);
		return WMX_ST_DEVICE_FAILURE;

	case L3L4_RESPONSE_STATUS_VERSION_ERROR:
		return WMX_ST_VERSION_VALIDATION_ERROR;

	case L3L4_RESPONSE_STATUS_BUSY:
		return WMX_ST_DEVICE_BUSY;

	case L3L4_RESPONSE_STATUS_UNINITIALIZED:
		TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "The orig status returned from the driver is: %d", l3l4ResponseStatus);
		return WMX_ST_DEVICE_NOT_READY;

	case L3L4_RESPONSE_STATUS_INVALID_OPCODE:
		return WMX_ST_INVALID_OPCODE;

	case L3L4_RESPONSE_STATUS_MISSING_PARAMS:
	case L3L4_RESPONSE_STATUS_ILLEGAL_VALUE:
	case L3L4_RESPONSE_STATUS_ERROR_BAD_STATE:
	case L3L4_RESPONSE_STATUS_CORRUPTED_TLV:
	case L3L4_RESPONSE_STATUS_ACCESSIBILITY_ERROR:
		TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "The orig status returned from the driver is: %d", l3l4ResponseStatus);
		return WMX_ST_ILLEGAL_OPERATION;

	default:
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "Unknown L4 Result: %d", l3l4ResponseStatus);
		return WMX_ST_FAIL;
	}
}



EXPORT WMX_EXTERN_C wmx_Status_t wmx_ParseL4Buffer( 
	UINT8* buffer,
	GENERIC_STRCT pStrct, 
	L4bufman_Funcs l4bufman_funcs, 
	wmx_Status_t *receivedSt )
{
	L4BUFMAN_Status_t res;

	// get the report state struct
	res = l4bufman_funcs.getFunc( pStrct, buffer );
	if( L4BUFMAN_ST_OK != res )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "l4bufman failed to parse report state buffer");
		return WMX_ST_FAIL;
	}

	// return the status received from the driver
	*receivedSt = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)(((L3L4Header_type*)pStrct)->Status));
	//TRACE(TR_MOD_SERVICE, TR_SEV_INFO, (L"returned status from driver is %d", *receivedSt));
	TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "returned status from driver is after wmxGetStatusStr function is %s", wmxGetStatusStr(*receivedSt));

	return WMX_ST_OK;
}


// Send a l4 command to the driver using the l4bufman
EXPORT wmx_Status_t wmx_SendL4Command( 
							   GENERIC_STRCT strct, 
							   L4bufman_Funcs l4bufman_funcs, 
							   tL5DispatcherFunctions dispatcher_funcs,
							   L5_CONNECTION conn,
							   wmx_Status_t *receivedSt )
{
	// results
	L5_RESULT l5Result;
	L4BUFMAN_Status_t res;
	wmx_Status_t st;

	// Request Fields
	UINT8 *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	UINT32 responseID;
	UINT8 *responseBuffer;
	UINT32 responseBufferSize;
	char *OpcodeName;
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SendL4Command(IN)");
	// check the arguments
	if( ( strct == NULL ) || ( conn == NULL ) || ( receivedSt == NULL ) )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "cannot send l4 command - bad arguments");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	// allocate the request buffer
	requestBufferSize = l4bufman_funcs.getBufferSizeFunc( strct );
	requestBuffer = (UINT8*)malloc( requestBufferSize );
	if (NULL == requestBuffer)
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - malloc failed");
		return WMX_ST_FAIL;
	}

	// fill the request buffer
	res = l4bufman_funcs.setFunc( requestBuffer, strct );
	if (L4BUFMAN_ST_OK != res)
	{
		free(requestBuffer);
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - setFunc faild");
		return WMX_ST_PIPE_FAILURE;
	}

	OpcodeName = GetL4Opcode(requestBuffer);
	TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "Sending L4 command=%s", OpcodeName);

	// allocate the response buffer
	responseBufferSize = l4bufman_funcs.getMaxBufferSizeFunc();
	responseBuffer = (UINT8*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(requestBuffer);
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - MALLOC FAILD");
		return WMX_ST_FAIL;
	}

	// send the request and receive the response
	l5Result = dispatcher_funcs.pfnSendReceiveMessage( 
		conn, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, 
		requestBuffer, requestBufferSize, 
		&responseID, responseBuffer, &responseBufferSize );
	free(requestBuffer);

	// check the l5 result
	st = wmx_L5ResultToWMXStatus( l5Result );
	if( st != WMX_ST_OK )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "cannot send l4 command - returned l5results is %d", l5Result);
		free(responseBuffer);
		return st;
	}

	// check the status received from the l4msgproxy
	if( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "cannot send l4 command - returned response id from l4proxy is %d", responseID);
		free(responseBuffer);
		return (wmx_Status_t)responseID;
	}

	// TODO - XXX - Add to l4bufman funcs a function that returns the opcode. Here the response opcode should be as the strct opcode
	// Check the driver returned opcode
	if( L4BM_GetOpcode(responseBuffer) == INVALID_OPCODE )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_ALERT, "bad response opcode");
		free(responseBuffer);
		return WMX_ST_DEVICE_FAILURE;
	}

	// fill the strct with the response
	res = l4bufman_funcs.getFunc( strct, responseBuffer );
	if( L4BUFMAN_ST_OK != res )
	{
		free(responseBuffer);
		return WMX_ST_PIPE_FAILURE;
	}

	free(responseBuffer);

	// return the status received from the driver
	*receivedSt = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)(((L3L4Header_type*)strct)->Status));
	//TRACE(TR_MOD_SERVICE, TR_SEV_INFO, (L"returned status from driver is %d", *receivedSt));
	TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "returned status from driver after wmxGetStatusStr function is %s", wmxGetStatusStr(*receivedSt));

	return WMX_ST_OK;
}

EXPORT wmx_Status_t wmx_SendL5Command( 
							   L5_TARGET_ID target, UINT32 msgID, 
							   tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn,
							   UINT8* request, UINT32 requestLength, 
							   UINT8* response, UINT32* responseLength )
{
	L5_RESULT l5Result;
	wmx_Status_t st;
	UINT32 responseID;

	l5Result = dispatcher_funcs.pfnSendReceiveMessage( 
		conn, target, msgID, request, requestLength, &responseID, response, responseLength );

	// check the l5 result
	st = wmx_L5ResultToWMXStatus( l5Result );
	if( st != WMX_ST_OK )
	{
		return st;
	}

	return (wmx_Status_t)responseID;
}

EXPORT wmx_Status_t wmx_RegisterOnAgentIndication( 
									  LONG *cnt, 
									  L5_TARGET_ID target, UINT32 msgID, UINT32 ind,
									  tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn )
{
	UINT32 responseLength = 0;

	TRACE(TR_MOD_SERVICE, TR_SEV_DEBUG, "wmx_RegisterOnAgentIndication(IN)");

	if ( FIRST_REGISTERED == OSAL_atomic_increment(cnt) )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "registering at %d on %d", target, ind);
		return wmx_SendL5Command( target, msgID, dispatcher_funcs, conn, (UINT8*)&ind, sizeof(UINT32), NULL, &responseLength );
	}

	TRACE(TR_MOD_SERVICE, TR_SEV_DEBUG, "wmx_RegisterOnAgentIndication(OUT)");
	return WMX_ST_OK;
}

EXPORT wmx_Status_t wmx_UnregisterOnAgentIndication( 
										LONG *cnt, 
										L5_TARGET_ID target, UINT32 msgID, UINT32 ind,
										tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn )
{
	UINT32 responseLength = 0;

	TRACE(TR_MOD_SERVICE, TR_SEV_DEBUG, "wmx_UnregisterOnAgentIndication(IN)");
	if ( LAST_REGISTERED == OSAL_atomic_decrement(cnt) )
	{
		TRACE(TR_MOD_SERVICE, TR_SEV_INFO, "unregistering at %d on %d", target, ind);
		return wmx_SendL5Command( target, msgID, dispatcher_funcs, conn, (UINT8*)&ind, sizeof(UINT32), NULL, &responseLength );
	}

	OSAL_atomic_compareExchange(cnt, LAST_REGISTERED, LAST_REGISTERED - 1);

	TRACE(TR_MOD_SERVICE, TR_SEV_DEBUG, "wmx_UnregisterOnAgentIndication(OUT)");
	return WMX_ST_OK;
}


EXPORT wmx_Status_t wmx_RegisterOnDriverReport( 
										LONG *cnt, UINT32 ind,
										tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn )
{
	return wmx_RegisterOnAgentIndication( 
		cnt, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_REGISTER_L4_INDICATION, ind, dispatcher_funcs, conn );
}

EXPORT wmx_Status_t wmx_UnregisterOnDriverReport( 
	LONG *cnt, UINT32 ind,
	tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn )
{
	return wmx_UnregisterOnAgentIndication( 
		cnt, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, ind, dispatcher_funcs, conn );
}