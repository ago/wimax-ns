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
#ifndef _L5COMMON_H
#define _L5COMMON_H

#include "UDapiCommonDefines.h" // for MOC Payload + header size
#include "WrappersCommon.h"
#include "Messenger.h"
#include "TraceModule.h"
#include "KDapiAdapter.h"

//////////////////////////////////////////////////////////////////////////
// Definitions

// Last known value is 8192 + 16 + 12 + 4 = 8224
//#define STATUS_INDICATION_PAYLOAD_MAX_SIZE (TASK_DATA_TYPE_SIZE /* MOC Payload + header */ + sizeof(L3L4CompleteHeader_type) /* L3L4 header */ + 4 /* SV part */)
#define STATUS_INDICATION_PAYLOAD_MAX_SIZE (TASK_DATA_TYPE_SIZE /* MOC Payload + header */ + 12 /* L3L4 header */ + 4 /* SV part */)

// Dispatcher message related
//#define L5_FIRST_USER_MESSAGE_ID				(100)
#define L5_DISPATCHER_MAX_MESSAGE_BUFFER_SIZE	(STATUS_INDICATION_PAYLOAD_MAX_SIZE + 8) /* 4 bytes for OID + 4 bytes for payload length */
#define L5_DISPATCHER_MESSAGE_REPLY_TIMEOUT		(30000) // in milliseconds XXX
#define L5_DISPATCHER_CONNECT_TIMEOUT			(3000) // in milliseconds XXX

// L5 Message flags
#define L5_MESSAGE_FLAG_REPLY		0x01
#define L5_MESSAGE_FLAG_ERROR		0x02


//////////////////////////////////////////////////////////////////////////
// Typedefs

// L5_RESULTs
typedef enum _L5_RESULT
{
	// Success
	L5_RESULT_OK = 0,

	// Protocol
	L5_RESULT_TOO_MANY_CONNECTIONS,
	L5_RESULT_INVALID_PROTOCOL,
	L5_RESULT_NO_TARGET_SEQ_MATCH,

	// Logical
	L5_RESULT_ID_OUT_OF_RANGE,
	L5_RESULT_ID_ALREADY_EXISTS,
	L5_RESULT_ID_NOT_FOUND,
	L5_RESULT_NO_HANDLER,
	L5_RESULT_INVALID_PARAMS,

	// Resources
	L5_RESULT_MEMORY_ALLOC_FAILED,
	L5_RESULT_SOCKETS_ERROR,
	L5_RESULT_CREATE_EVENT_FAILED,

	// Wait
	L5_RESULT_TIMED_OUT,
	L5_RESULT_WAIT_FAILED,
	L5_RESULT_TOO_MANY_WAITING_FOR_REPLIES,

	// Shutdowns and disconnections
	L5_RESULT_SERVICE_SHUTTING_DOWN,
	L5_RESULT_ALREADY_DISCONNECTED,
	L5_RESULT_USER_REQUESTED_DISCONNECT,
	L5_RESULT_OTHER_SIDE_DISCONNECTED,

	// Deadlock prevention
	L5_RESULT_CANT_DO_DURING_CALLBACK,

	L5_RESULT_ACCESSIBILITY_ERROR,

	// services error
	L5_RESULT_SERVICES_INIT_FAILED

} L5_RESULT;

// Target IDs
typedef enum _L5_TARGET_ID
{
	L5_TARGET_DYNAMIC = 0,
	L5_TARGET_CONTROL = 0,
	L5_TARGET_GENERIC_APPLICATION,
	L5_TARGET_PIPE_SERVICES,
	L5_TARGET_SERVICES,
	
	L5_TARGET_SUPPLICANT,
	L5_TARGET_NDNS,
	L5_TARGET_L4_PROXY,
	L5_TARGET_MOC_PROXY,
	L5_TARGET_ACT,
	//L5_TARGET_NDIS_TRACE_AGENT,
	L5_TARGET_DND_AGENT,
	L5_TARGET_KDAPI_ADAPTER,
	L5_TARGET_EVENT
} L5_TARGET_ID;

typedef enum _L5_CONTROL_MESSAGE
{
	// DISPATCHER <==> CONNTECTOR, Buffer: (UINT32) Requested target ID.
	// Response: Same message, Buffer: (UINT32) L5_RESULT.
	L5_CONTROL_MESSAGE_HANDSHAKE = 0,

	// DISPATCHER  ==> CONNTECTOR
	L5_CONTROL_MESSAGE_FAILURE,
	L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION, // Should be removed. Not reported anymore.
	L5_CONTROL_MESSAGE_DRIVER_CONNECTED,
	L5_CONTROL_MESSAGE_DRIVER_DISCONNECTED
} L5_CONTROL_MESSAGE;

// L5 Events
typedef enum _L5_EVENT
{
	L5_EVENT_DISCONNECTED = 0,
	L5_EVENT_OTHER_DISCONNECTED,
	L5_EVENT_DRIVER_CONNECTED,
	L5_EVENT_DRIVER_DISCONNECTED
} L5_EVENT;

#define L5_EVENT_COUNT 4

#define L5_EVENT_STR(l5event) (l5event < L5_EVENT_COUNT ? L5EventStrArr[l5event] :"Ilegal")

static char* L5EventStrArr[] = {
	"<Disconnected>",
	"<Other Disconnected>",
	"<Driver Up>",
	"<Driver Down>"
};

typedef enum _THREAD_ID
{
	THREAD_ID_DEFAULT = 0
} THREAD_ID;

// Only unrecoverable errors should be reported. 
// (Bad user inputs shouldn't be reported, instead return some error to the user)
typedef enum _ERROR_REPORT_OPCODE
{
	CTRL_PROBLEM,		// missing indications, unrecoverable response status
	INTERNAL_PROBLEM,	// bad malloc, failed create event, unknown opcode, ...
	DEVICE_PROBLEM
} ERROR_REPORT_OPCODE;

typedef void (*tpfnSendErrorReport)( L5_TARGET_ID senderID, ERROR_REPORT_OPCODE opcode, const char* function, int line );


//The L5Message should be aligned to 1 because its going to be transmitted in the protocol.
#pragma pack(push, 1)

// Basic types
typedef void* L5_CONNECTION;

// Sockets protocol messages
typedef struct _tL5Message
{
	L5_TARGET_ID SourceID;
	L5_TARGET_ID TargetID;
	UINT32 fbFlags;
	UINT32 dwSequentialNumber;
	UINT32 dwMessageID;
	UINT32 dwMaxReplyBufferSize;
	UINT32 dwSentBufferSize;
	BYTE baSentBuffer[1];
} tL5Message;

// Function pointers
typedef void (*tpfnMessagesHandler)( 
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

typedef void (*tpfnEventHandler)( 
	L5_CONNECTION Conn,
	L5_EVENT eEvent,
	void *pvEventData,
	void *pvUserContext );



typedef struct _tUtilityFunctions
{
	size_t (*tpfnPostRequest)(
		REQUEST_PRIORITY priority,
		UINT32 internalRequestID, 
		void *buffer, UINT32 bufferLength,
		InternalHandler internalHandler );

	BOOL (*tpfnPopRequest)( size_t seqNum );

	void (*tpfnTrace)(MODULE_IDS moduleID, Severities severity, const char* file, const char* function, 
						int line,const char *fmt, ...);

	void (*tpfnSetTraceIndicatiosCB)(TraceIndicationCallback callback, char **trcBuffer);
} tUtilityFunctions;

// Dispatcher functions structure
typedef struct _tL5DispatcherFunctions
{
	L5_RESULT (*pfnConnect)(	
		tpfnMessagesHandler pfnMessagesHandler,
		tpfnEventHandler pfnEventHandler,	
		L5_CONNECTION *Conn);

	L5_RESULT (*pfnConnectEx)(		
		L5_TARGET_ID nTargetID,
		tpfnMessagesHandler pfnMessagesHandler,
		tpfnEventHandler pfnEventHandler,
		void *pvUserContext,
		THREAD_ID threadId,
		L5_CONNECTION *pConn);

	void (*pfnDisconnect)( L5_CONNECTION Conn );

	L5_RESULT (*pfnSendReceiveMessage)( 
		L5_CONNECTION Conn,
		L5_TARGET_ID nTargetID,

		UINT32 dwSendMessageID,
		void  *pvSendBuffer,
		UINT32 cbSendBufferSize,

		UINT32 *pdwReceiveMessageID,
		void  *pvReceiveBuffer,
		UINT32 *cbReceiveBufferSize );

	wmx_Status_t (*pfnRegisterCtrlStatusUpdatesCB)(
		wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB);

	wmx_Status_t (*pfnUnregisterCtrlStatusUpdatesCB)(
		wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB);

	wmx_CtrlStatus_t (*pfnGetCtrlStatus)();

	wmx_Status_t (*pfnSetConnParams)(
		char *szHostName,
		int nPort);

	tpfnSendErrorReport pfnSendErrorReport;

} tL5DispatcherFunctions;

extern tL5DispatcherFunctions *GetL5Funcs();
extern tUtilityFunctions *GetUtilsFuncs();


#endif