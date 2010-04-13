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

#ifndef _KDAPI_FOR_LINUX_NLSOCK_H
#define _KDAPI_FOR_LINUX_NLSOCK_H

#include "wimax_osal_primitives.h"

#include "CommonServices.h"



#define __user

#if 0
typedef enum _KDAPI_FOR_LINUX_NLSOCK_RESULT {
	KDAPI_SUCCESS,
	KDAPI_ERROR,
	KDAPI_DETAILED_ERR,
	KDAPI_NO_ROOM_FOR_INDICATION,
	KDAPI_BAD_ARGUMENTS,
	KDAPI_INDICATION_NOT_REGISTERED,
	KDAPI_NOT_ACTIVE
} KDAPI_RESULT;
#endif


struct ModeOfOperationCommand {
	UINT16 type;
	UINT16 length;
	UINT32 modeCommand;
};

struct L3L4Header {
	UINT16 Opcode;
	UINT16 Length;
	UINT16 Version;
	UINT16 Accessability;
	UINT16 Status;
	UINT16 Reserved2;
};
struct RfControl {
	UINT16 type;
	UINT16 length;
	UINT32 rfOperation;
};

typedef void (*KDAPI_IndicationHandler) (UINT32 statusID,
							  char *buf,
							  UINT32 bufSize);
//declarations for callback functions
// typedef int (*KDAPI_TraceIndicationHandler)(void *pData, UINT32 bufferLength);

KDAPI_RESULT KDAPI_Connect();

KDAPI_RESULT KDAPI_SendQueryOID(UINT32 oidNum,
						 void *pInBuf,
						 void *pOutBuf,
						 UINT32 oidStructSize,
						 UINT32 oidBufSize,
						 UINT32 * pBytesWritten,
						 UINT32 * detailedResult);


void KDAPI_Disconnect();
KDAPI_RESULT KDAPI_Fini();
KDAPI_RESULT KDAPI_Start();
void KDAPI_Stop();

KDAPI_RESULT KDAPI_TraceInit(IN KDAPI_TraceIndicationHandler traceHandler, 
							 IN OUT char **msgBuffer,
							 OUT UINT32 * detailedResult);
KDAPI_RESULT KDAPI_TraceFinalize();
KDAPI_RESULT KDAPI_TraceConnect();
void		KDAPI_TraceDisconnect();
KDAPI_RESULT KDAPI_TraceStart();
KDAPI_RESULT KDAPI_TraceStop();
KDAPI_RESULT KDAPI_TraceFinalize();
KDAPI_RESULT KDAPI_ClearDevice( OUT UINT32 * detailedResult );
void CheckForDriverFailed();
void KDAPI_ResetDevice();


#endif //_KDAPI_FOR_LINUX_NLSOCK_H
