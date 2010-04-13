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
#ifndef PIPE_HANDLER_H
#define PIPE_HANDLER_H

#pragma once


//////////////////////////////////////////////////////////////////////////
// Headers
// System


// @@@ : JSS
// Removed window.h
// removed the hard wired paths from the following includes. 


#include "wimax_osal_types.h"

// Project
//#include "PipeHandlerVersion.h"
#include "Versions.h"

#include "L5Common.h"
#include "VersionUtils.h"



//////////////////////////////////////////////////////////////////////////
// Prototypes



EXTERN_C EXPORT tL5DispatcherFunctions *PIPE_HANDLER_GetServiceDispatcherFunctions();
EXTERN_C EXPORT tUtilityFunctions *PIPE_HANDLER_GetUtilityFunctions();
EXTERN_C EXPORT wmx_Version_t PIPE_HANDLER_GetVersion();

EXTERN_C EXPORT L5_RESULT PIPE_HANDLER_Connect(	
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,	
	L5_CONNECTION *Conn);

EXTERN_C EXPORT L5_RESULT PIPE_HANDLER_ConnectEx(	
	L5_TARGET_ID nTargetID,
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,
	void *pvUserContext,
	THREAD_ID threadId,
	L5_CONNECTION *Conn);

EXTERN_C EXPORT void PIPE_HANDLER_Disconnect(L5_CONNECTION Conn);

EXTERN_C EXPORT L5_RESULT PIPE_HANDLER_SendReceiveL5( 
	L5_CONNECTION Conn,
	L5_TARGET_ID nTargetID,

	UINT32 dwSendMessageID,
	void  *pvSendBuffer,
	UINT32 cbSendBufferSize,

	UINT32 *pdwReceiveMessageID,
	void  *pvReceiveBuffer,
	UINT32 *cbReceiveBufferSize);

EXTERN_C EXPORT wmx_Status_t PIPE_HANDLER_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB);
EXTERN_C EXPORT wmx_Status_t PIPE_HANDLER_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB);
EXTERN_C EXPORT wmx_CtrlStatus_t PIPE_HANDLER_GetCtrlStatus();
EXTERN_C EXPORT wmx_Status_t PIPE_HANDLER_SetConnParams(char *szHostName, int nPort);


#endif //PIPE_HANDLER_H