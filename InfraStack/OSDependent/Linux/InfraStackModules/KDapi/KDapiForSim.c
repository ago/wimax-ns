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
#include "KDapiForSim.h"

#include "IPC_Common.h"
#include "IPC_Client.h"

#include "TraceModule.h"

#include "Act.h"

#include "L4MsgProxy.h"


// set the oidResponseBuffer and the oidResponseSize
// and raise the receivedOidResponseEvent
void HandleOids( char* buffer, int size, SOCKETS_CLIENT_ID client, void* context )
{
	
}


void HandleOidsDisconnection( SOCKETS_CLIENT_ID client, void* context )
{
}

void HandleInds( char* buffer, int size, SOCKETS_CLIENT_ID client, void* context )
{
}


void HandleIndsDisconnection( SOCKETS_CLIENT_ID client, void* context )
{
}


void KDAPI_FOR_SIM_Disconnect(TARGET_ID target)
{
}

void KDAPI_FOR_SIM_Stop(TARGET_ID target)
{
}

void KDAPI_FOR_SIM_Fini(TARGET_ID target)
{

}

BOOL KDAPI_FOR_SIM_Start()
{
	return TRUE;
}

BOOL KDAPI_FOR_SIM_Connect(TARGET_ID target)
{

	return FALSE;
}


KDAPI_FOR_SIM_RESULT KDAPI_FOR_SIM_Init( 
	TARGET_ID target, char* host, unsigned short oidsPort, unsigned short indsPort, 
	IN KDAPI_FOR_SIM_IndicationHandler statusHandler )
{
		return KDAPI_FOR_SIM_ERROR;
}

KDAPI_FOR_SIM_RESULT KDAPI_FOR_SIM_SendQueryOID(IN DWORD oidNum, IN PVOID pInBuf, OUT PVOID pOutBuf,
												IN DWORD oidStructSize, IN DWORD oidBufSize,
												OUT DWORD* pBytesWritten)
{
		return KDAPI_FOR_SIM_ERROR;
}

