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
#ifndef _KDAPI_FOR_SIM_H
#define _KDAPI_FOR_SIM_H

//#include <windows.h>	// @@@ : JSS : Remove

#include "CommonServices.h"
#include "KDapiAdapter.h"


//// mutex locking macros
//#define KDAPI_FOR_SIM_ACQUIRE_MUTEX(mutex)             WaitForSingleObject(mutex, INFINITE)
//#define KDAPI_FOR_SIM_RELEASE_MUTEX_WITH_CHECK(mutex)  VERIFY(ReleaseMutex(mutex))


typedef enum _KDAPI_FOR_SIM_RESULT
{
	KDAPI_FOR_SIM_SUCCESS,
	KDAPI_FOR_SIM_ERROR,  
	KDAPI_FOR_SIM_BUFFER_TOO_SHORT,
	KDAPI_FOR_SIM_DRIVER_GENERATED_ERR,
	KDAPI_FOR_SIM_SOCKET_DISCONNECTED,
	KDAPI_FOR_SIM_BAD_ARGUMENTS,
	KDAPI_FOR_SIM_NOT_ACTIVE
} KDAPI_FOR_SIM_RESULT;

typedef void (*KDAPI_FOR_SIM_IndicationHandler)( UINT32 statusID, char* buf, UINT32 bufSize );


BOOL KDAPI_FOR_SIM_Connect(TARGET_ID target);
KDAPI_FOR_SIM_RESULT KDAPI_FOR_SIM_Init(TARGET_ID target,
										char* host, 
										unsigned short oidsPort, 
										unsigned short indsPort, 
										IN KDAPI_FOR_SIM_IndicationHandler statusHandler );

KDAPI_FOR_SIM_RESULT KDAPI_FOR_SIM_SendQueryOID(
	IN UINT32 oidNum, 
	IN PVOID pInBuf, OUT PVOID pOutBuf,
	IN UINT32 oidStructSize, IN UINT32 oidBufSize,
	OUT UINT32* pBytesWritten);

void KDAPI_FOR_SIM_Disconnect();
BOOL KDAPI_FOR_SIM_Start();
void KDAPI_FOR_SIM_Stop(TARGET_ID target);
void KDAPI_FOR_SIM_Fini(TARGET_ID target);


#endif /* _KDAPI_FOR_SIM_H */
