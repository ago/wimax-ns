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

#pragma once
#pragma warning(disable : 4127) // warning C4201: nonstandard extension used : nameless struct/union
//////////////////////////////////////////////////////////////////////////
// Headers

// System

// Project
#include "CommonServices.h"
#include "L5Common.h"
#include "L5CommonUtils.h"
#include "WrappersCommon.h"

//#include "..\..\Wrappers\Include\iWmxSDKinternal.h"


//////////////////////////////////////////////////////////////////////////
// Constants
//#define L5_SOCKETS_DISPATCHER_LISTENING_PORT	GetPortNum()

//////////////////////////////////////////////////////////////////////////
// Prototypes
BOOL L5_SOCKETS_DISPATCHER_Initialize();
void L5_SOCKETS_DISPATCHER_Shutdown();

BOOL l5_sockets_dispatcher_Start();
void l5_sockets_dispatcher_Stop();
void l5_sockets_dispatcher_FreeResources();
void L5_Socket_Dispatcher_BroadcastControlMsg();
