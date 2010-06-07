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

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "EventLogger.h"

// Event logger definitions
#define MAX_EVENTLOG_STRING     512

// Pre-defined log message string.
const char *LOGMSG_VERSION_ERROR =
    "wimaxd event:\nVersion validation failed for modules: %s\nSeverity: %s\nModule version: %s\nExpected version: %s";
const char *LOGMSG_APPSRV_EVENT = "wimaxd event: %s";
const char *LOGMSG_UNKNOWN_LOG = "wimaxd event: Unknown Log message";
const char *LOGMSG_BAD_COMMAND = "You have chosen an incorrect command";

BOOL OSAL_EventLogger_Initialize()
{
#ifndef _WIMAX_SDK_
	openlog("wimaxd", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
#endif
	return TRUE;
}

void OSAL_EventLogger_Shutdown()
{
#ifndef _WIMAX_SDK_
	closelog();
#endif
}

EXPORT BOOL OSAL_EventLogger_GenericLog(int loglevel, int eventid, ...)
{
#ifndef _WIMAX_SDK_
	char logmsg[MAX_EVENTLOG_STRING] = "\0";

	va_list marker;
	va_start(marker, eventid);

	switch (eventid) {
	case MSG_APPSRV_EVENT:
		{
			vsprintf(logmsg, LOGMSG_APPSRV_EVENT, marker);
			break;
		}
	case MSG_VERSION_ERROR:
		{
			vsprintf(logmsg, LOGMSG_VERSION_ERROR, marker);
			break;
		}
	case MSG_BAD_COMMAND:
		{
			sprintf(logmsg, LOGMSG_BAD_COMMAND);
			break;
		}
	default:
		{
			sprintf(logmsg, LOGMSG_UNKNOWN_LOG);
		}
	}
	va_end(marker);

	// log the message
#if 1
	syslog( LOG_MAKEPRI(LOG_USER, LOG_INFO), logmsg);
#else
	syslog(loglevel, logmsg);
#endif 


#endif

	return TRUE;	
}

EXPORT BOOL OSAL_EventLogger_Log(int loglevel, char *str)
{
#ifndef _WIMAX_SDK_
	return OSAL_EventLogger_GenericLog(LOG_MAKEPRI(LOG_USER, LOG_INFO), MSG_APPSRV_EVENT, str);
#else
	return TRUE;
#endif
}
