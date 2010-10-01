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
#ifndef KDAPI_H
#define KDAPI_H

#include "CommonServices.h"
#include "wimax_osal_types.h"

#include "CommonTypes.h"				
#define DRV_SYMBOLIC_NAME "\\\\.\\BPENUM"


//#define STATUS_CANCELLED 0xC0000120L // from ntstatus.h ( in ntddk.h )
#define KDAPI_PEND_WAS_CANCELLED 0x000003e3L

#define KDAPI_MAX_INDS_LIST_SIZE 1600
#define KDAPI_STATUS_BUF_SIZE    (8224)

typedef enum _KDAPI_RESULT
{
	KDAPI_SUCCESS,
	KDAPI_ERROR,
	KDAPI_DETAILED_ERR,
	KDAPI_NO_ROOM_FOR_INDICATION,
	KDAPI_BAD_ARGUMENTS,
	KDAPI_INDICATION_NOT_REGISTERED,
	KDAPI_NOT_ACTIVE,
	KDAPI_DRIVER_DISCONNECTED
} KDAPI_RESULT;

typedef struct _STATUS_ENTRY
{
	ULONG status;
	UCHAR statusBuf[KDAPI_STATUS_BUF_SIZE];
	ULONG statusBufLen;
} STATUS_ENTRY, *PSTATUS_ENTRY;

//declarations for callback functions
typedef void (*KDAPI_StatusIndicationHandler)( PSTATUS_ENTRY statusEntry );
typedef void (*KDAPI_TraceIndicationHandler)(int bufferLength, int *location);

//Operational interface functions
KDAPI_RESULT KDAPI_Init(IN KDAPI_StatusIndicationHandler	statusHandler, 
						IN KDAPI_TraceIndicationHandler		traceHandler, 
						INOUT char **						traceMsgBuffer,
						OUT PUINT32							detailedResult,
						IN BOOL								withDebug);
KDAPI_RESULT KDAPI_Connect();
KDAPI_RESULT KDAPI_Start();
void		 KDAPI_Stop();
void		 KDAPI_Disconnect();
KDAPI_RESULT KDAPI_Fini();

KDAPI_RESULT KDAPI_SendQueryOID(IN UINT32 oidNum, 
								IN PVOID pInBuf, 
								OUT PVOID pOutBuf,
								IN UINT32 oidStructSize, 
								IN UINT32 oidBufSize,
								OUT UINT32* pBytesWritten, 
								OUT PUINT32 detailedResult );

KDAPI_RESULT KDAPI_TraceStart();
KDAPI_RESULT KDAPI_TraceStop();


KDAPI_RESULT KDAPI_RestartDriverConnection();

KDAPI_RESULT KDAPI_DriverStatusRegister( IN ULONG statusID, OUT PUINT32 detailedResult );
KDAPI_RESULT KDAPI_DriverStatusUnRegister( IN ULONG statusID, OUT PUINT32 detailedResult );

KDAPI_RESULT KDAPI_ClearDevice( OUT PUINT32 detailedResult );
void CheckForDriverFailed();
void KDAPI_ResetDevice();


#endif /* KDAPI_H */
