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
#ifndef _EVENT_LOGGER_H_
#define _EVENT_LOGGER_H_

#include "wimax_osal_primitives.h"

#include <sys/syslog.h>
#include "CommonServices.h"

// Event MessageId: MSG_BAD_COMMAND
//
// MessageText:
//
//  You have chosen an incorrect command.
//
#define MSG_BAD_COMMAND                  1

// Event MessageId: MSG_APPSRV_EVENT
//
// MessageText:
//
//  AppSrv event: %1
//
#define MSG_APPSRV_EVENT                 2

// Event MessageId: MSG_VERSION_ERROR
//
// MessageText:
//
//  AppSrv event:%n
//  Version validation failed for module %1.%n
//  Severity: %2%n
//  Module version: %3%n
//  Expected version: %4%n
//
#define MSG_VERSION_ERROR                3

BOOL OSAL_EventLogger_Initialize();
void OSAL_EventLogger_Shutdown();
EXPORT BOOL OSAL_EventLogger_Log(int loglevel, char *str);
EXPORT BOOL OSAL_EventLogger_GenericLog(int loglevel, int eventid, ...);

#endif // _EVENT_LOGGER_H_
