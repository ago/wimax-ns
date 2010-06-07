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
#ifndef _TRACE_AGENT_H_
#define _TRACE_AGENT_H_

#include "CommonServices.h"
#include "wimax_osal_types.h"

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __WFILE__ WIDEN(__FILE__)
#define __WFUNCTION__ WIDEN(__FUNCTION__)


#define MAX_PREFIX_LEN 20
#define MAX_MESSAGE_LEN 8192
#define MAX_LINES_TO_WRITE 5000
#define MAX_CHARS_TO_WRITE 500000  // 0.5 mb
#define MAX_FILES_PER_PROCESS 10

typedef UINT32 SEVERITY;
typedef UINT32 MODULE_ID;


#define TRACE_AGENT_OPCODE_BASE		0
#define TRACE_AGENT_OPCODE_INVALID -1

//The following Message IDs are the services supported by the TraceAgent:
//Incoming Messages:
#define TRACE_AGENT_OPCODE_WRITE_TRACE		TRACE_AGENT_OPCODE_BASE + 0

typedef enum _Severities
{
	TR_SEV_ALERT	= 1, 
	TR_SEV_CRITICAL = 2, 
	TR_SEV_ERR	= 4,
	TR_SEV_WARNING	= 8,  
	TR_SEV_NOTICE	= 16, 
	TR_SEV_INFO	= 32,
	TR_SEV_DEBUG	= 64,
	TR_SEV_ALL	= 0x7FFFFFFF
}Severities;

typedef enum _MODULE_ID
{
	TR_MOD_L4MsgProxy		= 0x00000001,
	TR_MOD_MocMsgProxy		= 0x00000002,
	TR_MOD_KDAPI			= 0x00000004,
	TR_MOD_KDAPI_ADAPTER		= 0x00000008,
	TR_MOD_KDAPI_FOR_SIM		= 0x00000010,
	TR_MOD_CLIENT_SOCKET		= 0x00000020,
	TR_MOD_SERVER_SOCKET		= 0x00000040,
	TR_MOD_COMMON_SOCKET		= 0x00000080,
	TR_MOD_L5_CONNECTOR		= 0x00000100,
	TR_MOD_L5_DISPATCHER		= 0x00000200,
	TR_MOD_L5_SOCKETS_DISPATCHER    = 0x00000400,
	TR_MOD_SERVICE                  = 0x00000800,
	TR_MOD_NDNS_AGENT		= 0x00001000,
	TR_MOD_NDNS_WRAPPER		= 0x00002000,
	TR_MOD_MESSENGER		= 0x00004000,
	TR_MOD_SUPPLICANT_AGENT		= 0x00008000,
	TR_MOD_SUPPLICANT_WRAPPER	= 0x00010000,
	TR_MOD_PRODUCTION_WRAPPER 	= 0x00020000,
	TR_MOD_MISCELLANEOUS_WRAPPER	= 0x00040000,
	TR_MOD_GENERIC_WRAPPER		= 0x00080000,
	TR_MOD_ACT			= 0x00100000,
	TR_MOD_MOC_HANDLER		= 0x00200000,
	TR_MOD_NDIS_TRACE		= 0x00400000,
	TR_MOD_WRAPPER_LOGS		= 0x00800000,
	TR_MOD_DND_AGENT		= 0x01000000,
	TR_MOD_DND_WRAPPER 		= 0x02000000,
	TR_MOD_APDO_WRAPPER		= 0x04000000,
	TR_MOD_COMMON_API		= 0x08000000,
	TR_MOD_APDO_AGENT		= 0x10000000,
	TR_MOD_CONFIGURATION		= 0x20000000,
	TR_MOD_RAW			= 0x40000000,				// @@@ : JSS : Used by Linux TraceModule implementation
	TR_MOD_ALL			= 0x7FFFFFFF

} MODULE_IDS;

// Reload Filters
EXPORT BOOL TraceAgent_ReloadFilterParams();
// Writes a Generic Trace Message
EXTERN_C EXPORT void TraceAgent_WriteTrace(MODULE_IDS moduleID, Severities severity, const char* file, const char* function, int line,const char *fmt, ...);
EXTERN_C EXPORT void DumpHexString(char *prefix, unsigned char *data, int DataLen);
//
// Retrieve the system error message for the last-error code
// format it and send to TRACE macro
//
EXTERN_C EXPORT void TraceLastError(LPTSTR lpszUserMsg, MODULE_IDS module, Severities sev);

//EXTERN_C EXPORT void TraceAgent_SetMessageProperties (WCHAR* buf, MODULE_ID moduleID, SEVERITY severity, const WCHAR* file, const WCHAR* function, int line);
//EXTERN_C EXPORT void TraceAgent_PrintTrace(const WCHAR *fmt, ...);

BOOL Trace_Init();
EXPORT void Trace_Finalize();
//
//Reads the severities from registry
//
BOOL ReloadModulesSeverities();
//
// Set Maximal logger severity
//
void TraceAgent_SetSeverity(SEVERITY sev);
SEVERITY TraceAgent_GetSeverity();
void DumpTracesLog();
//
// Set Maximal logger module
//
void TraceAgent_SetModule(MODULE_ID moduleID);
MODULE_ID TraceAgent_GetModule();
char* GetSeverityName(Severities sev);
char* GetModuleName(MODULE_IDS id);
BOOL Trace_OpenLogFile();
const char * ExtractFileName(const char * fullFileName);
MODULE_ID GetModuleIdIndex(MODULE_IDS moduleID);


#ifdef _USE_TRACE 
#ifndef EXTERNAL_TRACE
	#define TRACE(moduleID, severity, fmt, ...) TraceAgent_WriteTrace(moduleID, severity, __FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__ )	
	#define TRACE_RELOAD() TraceAgent_ReloadFilterParams()
#else
	#define TRACE(moduleID, severity, fmt, ...) pUtils->tpfnTrace(moduleID, severity, __FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__ )	
#endif
#else

	#define TRACE(moduleID, severity, fmt, ...)
	#define TRACE_RELOAD() TRUE

#endif //_USE_TRACE
#endif //_TRACE_AGENT_H_
