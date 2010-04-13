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
#ifndef _EVENT_LOGGER_H
#define _EVENT_LOGGER_H

// Event logger auto-generated header
//#include "EventLogMessages.h"
// #include "Common.h"
		// @@@ : JSS : Remove this from here. You are creating an upwards dependency from OSAL to higher layers

/////////////////////////////////////////
// The following event types can be used:
//
// EVENTLOG_SUCCESS Success event 
// EVENTLOG_ERROR_TYPE Error event 
// EVENTLOG_WARNING_TYPE Warning event 
// EVENTLOG_INFORMATION_TYPE Information event 
// EVENTLOG_AUDIT_SUCCESS Success audit event 
// EVENTLOG_AUDIT_FAILURE Failure audit event 
/////////////////////////////////////////

BOOL OSAL_EventLogger_Initialize();
void OSAL_EventLogger_Shutdown();
void OSAL_EventLogger_Log(UINT16 wType, char *str );
void OSAL_EventLogger_GenericLog( UINT16 wType, UINT32 dwEventID, UINT16 wNumStrings, char *str, ... );


#endif // _EVENT_LOGGER_H_
