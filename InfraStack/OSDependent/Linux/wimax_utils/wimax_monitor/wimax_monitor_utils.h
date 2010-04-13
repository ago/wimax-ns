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
#ifndef __WIMAX_MONITOR_UTILS_H__
#define __WIMAX_MONITOR_UTILS_H__

#include "WrappersCommon.h"
#include "iWmxSDK.h"
#include "wmxSDK_Nds_3.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_Cmn.h"


#define PRINT_DONE(str) PRINT_OUTPUT(str, "[ DONE ]")
#define PRINT_FAIL(str) PRINT_OUTPUT(str, "[ FAIL ]")
#define PRINT_OK(str)   PRINT_OUTPUT(str, "[  OK  ]")
#define PRINT_SKIP(str) PRINT_OUTPUT(str, "[ SKIP ]")

#define PRINT_ERROR(str, ...)   PRINT_LINE("ERROR", str, ##__VA_ARGS__ )
#define PRINT_WARNING(str, ...) PRINT_LINE("WARNING", str, ##__VA_ARGS__ )
#define PRINT_MSG(str, ...)     PRINT_LINE("MESSAGE", str, ##__VA_ARGS__ )
#define PRINT_OUT(str, ...)     PRINT_LINE(NULL, str, ##__VA_ARGS__ )



// Some Print methods
void PrintWmxDeviceStatus(wmx_DeviceStatus_t deviceStatus);
void PrintWmxConnectionProgressInfo(wmx_ConnectionProgressInfo_t connectionProgressInfo);
void PrintWmxSystemState (wmx_SystemState_t systemState);
void PrintWmxConnectProgressInfo( wmx_ConnectProgressInfo_t connectProgressInfo);
void PrintWmxRfSwitchesStatus(wmx_RfSwitchesStatus_t rfSwitchesStatus ) ;
void PrintWmxStateReason(wmx_StateReason_t stateReason);
void PrintWmxUserLinkStatus(wmx_UserLinkStatus_t userLinkStatus);
void PrintWmxMediaStatus(wmx_MediaStatus_t mediaStatus);



#endif //__WIMAX_MONITOR_UTILS_H__
