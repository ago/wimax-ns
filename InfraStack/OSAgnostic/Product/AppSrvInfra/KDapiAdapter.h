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
#ifndef _KDAPI_ADAPTER_H_
#define _KDAPI_ADAPTER_H_

#include "wimax_osal_types.h"
#define DRIVER_RESPONE_TIMEOUT 30000

typedef enum _KDAPI_ADAPTER_RESULT
{
	KDAPI_ADAPTER_SUCCESS,
	KDAPI_ADAPTER_ERROR, 
	KDAPI_ADAPTER_BUFFER_TOO_SHORT,
	KDAPI_ADAPTER_DRIVER_GENERATED_ERR,
	KDAPI_ADAPTER_NO_ROOM_FOR_INDICATION,
	KDAPI_ADAPTER_INDICATION_NOT_REGISTERED,
	KDAPI_ADAPTER_BAD_ARGUMENTS,
	KDAPI_ADAPTER_NOT_ACTIVE
} KDAPI_ADAPTER_RESULT;

typedef enum _TARGET_ID
{
	DRIVER_SIM,
	MINIPORT_DRIVER,
	REMOTE_HOST
} TARGET_ID;

typedef ULONG STATUS_IND_ID;
typedef UINT32 OID_NUM;

typedef void (*IndicationCallback)(STATUS_IND_ID indication_id, void *indication_buffer, ULONG buffer_size );
typedef void (*TraceIndicationCallback)(int bufferLength, int *location);



#define MAX_STATUS_IND_IDS 10

// For the driver simulator
#ifdef WINCE
//#define Host "169.254.2.2"
#define Host "127.0.0.1"

#else
//#define Host "127.0.0.1"
#define Host "169.254.2.1"
#endif
#define OidsPort 11045
#define IndsPort 11046


#include "KDapi.h"
#include "KDapiForSim.h"


//KDapiAdapter interface functions:
//---------------------------------

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Init(IN BOOL traceEnable); //Initialize internal resources
KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Fini(); //Finalize internal resources

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Connect(); //Connects to the driver
KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Disconnect(); //Disconnects from driver

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Start(); //Starts indications (and traces) threads
void KDAPI_ADAPTER_Stop(); //Stops indications (and traces) threads

EXTERN_C EXPORT void KDAPI_ADAPTER_SetTraceIndicatiosCB(TraceIndicationCallback callback, 
																		char **trcBuffer);
void KDAPI_ADAPTER_SetDriverIndicatiosCB(IndicationCallback callback);

// The receive_buffer_size is an INOUT argument. 
// It must contain the expected response size which is allocated in the receive_buffer. 
// When returned it contain the actual size written to the received_buffer.
KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_SendReceiveMessage( 
	OID_NUM oidNum,
	void *send_buffer, int send_buffer_size,
	void *receive_buffer, int *receive_buffer_size );

// Call RegisterOnIndication after SetIndicationsCallback !
KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_RegisterOnIndication( STATUS_IND_ID indication_id );
KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_UnregisterOnIndication( STATUS_IND_ID indication_id );
void KDAPI_ADAPTER_ResetDevice();

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_RestartDriverConnection();

#endif // _KDAPI_ADAPTER_H_