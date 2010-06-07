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
#ifndef PIPE_HANDLER_INTERN_H
#define PIPE_HANDLER_INTERN_H

#pragma once


//////////////////////////////////////////////////////////////////////////
// Headers

// Project
#include "PipeHandler.h"

#include "L5Common.h"		
#include "VersionUtils.h"


//////////////////////////////////////////////////////////////////////////
// Prototypes

void PIPE_HANDLER_InitCriticalSections();
void PIPE_HANDLER_FinalizeCriticalSections();
L5_RESULT PIPE_HANDLER_InitConnectivity();
void PIPE_HANDLER_FiniConnectivity();

char *PIPE_HANDLER_GetIpAddress();
UINT32 PIPE_HANDLER_GetPortNum();

L5_RESULT PIPE_HANDLER_ConnectInternal(
	char *szHostName,
	int nPort,
	L5_TARGET_ID nTargetID,
	tpfnMessagesHandler pfnMessagesHandler,
	tpfnEventHandler pfnEventHandler,
	void *pvUserContext,
	BOOL isGateKeeper, 
	L5_CONNECTION *Conn );

void PIPE_HANDLER_DisconnectInternal( L5_CONNECTION Conn, BOOL isGateKeeper );

//void PIPE_HANDLER_AddClient();
//void PIPE_HANDLER_RemoveClient();
BOOL PIPE_HANDLER_IsConnected(L5_RESULT *status);
void PIPE_HANDLER_ReportError();

BOOL PIPE_HANDLER_IsInitialized();

#endif //PIPE_HANDLER_INTERN_H
