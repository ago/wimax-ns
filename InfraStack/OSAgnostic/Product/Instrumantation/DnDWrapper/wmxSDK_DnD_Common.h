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
#ifndef _WMX_SDK_DND_COMMON_H_
#define _WMX_SDK_DND_COMMON_H_

#include "wmxSDK_DnD_Cmn.h"
#include "wmxSDK_DnD.h"

// The following methods are in common because coth the Agent and Wrapper are using them
wmx_Status_t DeviceMonitorOnControl(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs);
wmx_Status_t DeviceMonitorOffControl(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs);
wmx_Status_t DeviceSetMonitorFilter(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs, char * pMonitorFilterBuff, UINT32 nMonitorFilterBuffSize);
wmx_Status_t DeviceSetTraceFilter(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs, char * pTraceFilterBuff, UINT32 nTraceFilterBuffSize);

#endif //_WMX_SDK_DND_COMMON_H_
