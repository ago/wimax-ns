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

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "wimax_osal_config_controler.h"
#include "TraceAgentInternal.h"
//#include "ConfigController.h"

#define PRINT_HEX_LENGTH_LINE 16

struct MessageProp {
	MODULE_ID moduleID;
	SEVERITY severity;
	const char *file;
	const char *function;
	int line;
};

struct MessageProp gMessageProp;
char *messageBuf;

static OSAL_critical_section csWriteProt;
static SEVERITY gSeverity;
static MODULE_ID gModuleID;

static char gcProcessName[MAX_PATH];
static char gcLogFilePathName[MAX_FILENAME_LEN];

static FILE *gLogFile = NULL;

static BOOL isInitialized = FALSE;

static char *SeveritiesArray[] = { 
	"Alert",
	"Critical",
	"Error",
	"Warning",
	"Notice",
	"Info",
	"Debug",
	"All" };

static char* ModulesArray[] = {
	"L4MsgProxy",
	"MocMsgProxy",
	"KDAPI",
	"KDAPI_ADAPTER",
	"KDAPI_FOR_SIM",
	"CLIENT_SOCKET",
	"SERVER_SOCKET",
	"COMMON_SOCKET",
	"L5_CONNECTOR",
	"L5_DISPATCHER",
	"L5_SOCKETS_DISPATCHER",
	"SERVICE",
	"NDNS_Agent",
	"NDNS_Wrapper",
	"Messenger",
	"Supplicant_Agent",
	"Supplicant_Wrapper",
	"Production_Wrapper",
	"MISC_Wrapper",
	"Generic_Wrapper",
	"ACT",
	"Moc_Handler",
	"NdisTrace_Agent",
	"WRAPPER_LOGS",
	"DnD_Agent",
	"DnD_Wrapper",
	"APDO_Wrapper",
	"COMMON_API",
	"APDO_AGENT",
	"CONFIGURATION",
	"RAW",
	"ALL",
	"None"
};

EXPORT void DumpHexString(char *prefix, unsigned char *data, int DataLen)
{
	char buffer[100];
	int lineLen = PRINT_HEX_LENGTH_LINE;
	int offset = 0;
	int i;
	
	memset(buffer,0,sizeof(buffer));

	while (DataLen>0) 
	{
		if (lineLen > DataLen)
			lineLen = DataLen;
		for (i = 0; i<lineLen; i++) 
		{
			sprintf(&buffer[i*3] ,"%02x ",data[offset+i]);
		}
		for (i = lineLen; i<PRINT_HEX_LENGTH_LINE; i++) 
		{
			sprintf(&buffer[i*3] ,"   ");
		}

		buffer[PRINT_HEX_LENGTH_LINE*3]=' ';

		for (i =0; i<lineLen; i++) 
		{
			if((data[offset+i] > 0) &&(isprint(data[offset+i])))
				sprintf(&buffer[PRINT_HEX_LENGTH_LINE*3+1+i] ,"%c",data[offset+i]);
			else
				sprintf(&buffer[PRINT_HEX_LENGTH_LINE*3+1+i] ,"%c",'.');
		}

		buffer[16*3+1+lineLen]=0;
		TRACE(TR_MOD_RAW, TR_SEV_INFO, "%s|%s", prefix, buffer);
		offset += PRINT_HEX_LENGTH_LINE;
		DataLen -=PRINT_HEX_LENGTH_LINE;
	}
}

char *GetSeverityName(Severities sev)
{
	switch (sev) {
	case TR_SEV_ALERT:
		return SeveritiesArray[0];
	case TR_SEV_CRITICAL:
		return SeveritiesArray[1];
	case TR_SEV_ERR:
		return SeveritiesArray[2];
	case TR_SEV_WARNING:
		return SeveritiesArray[3];
	case TR_SEV_NOTICE:
		return SeveritiesArray[4];
	case TR_SEV_INFO:
		return SeveritiesArray[5];
	case TR_SEV_DEBUG:
		return SeveritiesArray[6];
	case TR_SEV_ALL:
		return SeveritiesArray[7];
	}
	return "XXXXXX";
}

char *GetModuleName(MODULE_IDS id)
{
	switch (id) {
	case TR_MOD_L4MsgProxy:
		return ModulesArray[0];
	case TR_MOD_MocMsgProxy:
		return ModulesArray[1];
	case TR_MOD_KDAPI:
		return ModulesArray[2];
	case TR_MOD_KDAPI_ADAPTER:
		return ModulesArray[3];
	case TR_MOD_KDAPI_FOR_SIM:
		return ModulesArray[4];
	case TR_MOD_CLIENT_SOCKET:
		return ModulesArray[5];
	case TR_MOD_SERVER_SOCKET:
		return ModulesArray[6];
	case TR_MOD_COMMON_SOCKET:
		return ModulesArray[7];
	case TR_MOD_L5_CONNECTOR:
		return ModulesArray[8];
	case TR_MOD_L5_DISPATCHER:
		return ModulesArray[9];
	case TR_MOD_L5_SOCKETS_DISPATCHER:
		return ModulesArray[10];
	case TR_MOD_SERVICE:
		return ModulesArray[11];
	case TR_MOD_NDNS_AGENT:
		return ModulesArray[12];
	case TR_MOD_NDNS_WRAPPER:
		return ModulesArray[13];
	case TR_MOD_MESSENGER:
		return ModulesArray[14];
	case TR_MOD_SUPPLICANT_AGENT:
		return ModulesArray[15];
	case TR_MOD_SUPPLICANT_WRAPPER:
		return ModulesArray[16];
	case TR_MOD_PRODUCTION_WRAPPER:
		return ModulesArray[17];
	case TR_MOD_MISCELLANEOUS_WRAPPER:
		return ModulesArray[18];
	case TR_MOD_GENERIC_WRAPPER:
		return ModulesArray[19];
	case TR_MOD_ACT:
		return ModulesArray[20];
	case TR_MOD_MOC_HANDLER:
		return ModulesArray[21];
	case TR_MOD_NDIS_TRACE:
		return ModulesArray[22];
	case TR_MOD_WRAPPER_LOGS:
		return ModulesArray[23];
	case TR_MOD_DND_AGENT:
		return ModulesArray[24];
	case TR_MOD_DND_WRAPPER:
		return ModulesArray[25];
	case TR_MOD_APDO_WRAPPER:
		return ModulesArray[26];
	case TR_MOD_COMMON_API:
		return ModulesArray[27];
	case TR_MOD_APDO_AGENT:
		return ModulesArray[28];
	case TR_MOD_CONFIGURATION:
		return ModulesArray[29];
	case TR_MOD_RAW:
		return ModulesArray[30];
	case TR_MOD_ALL:
		return ModulesArray[31];
	}
	return "Unknown Module";
}

void TraceAgent_InitCriticalSections()
{
	OSAL_init_critical_section(&csWriteProt);
}

void TraceAgent_FinalizeCriticalSections()
{
	OSAL_delete_critical_section(&csWriteProt);
}

void Trace_CloseLogFile()
{
	if (gLogFile != NULL) {
		fclose(gLogFile);
		gLogFile = NULL;
	}
}

BOOL Trace_OpenLogFile()
{
	char fileName[MAX_PATH];
	int lastLogFileIndex;
//	struct stat fileStat;

	OSAL_snprintf(fileName, MAX_FILENAME_LEN, "%s/%s%s", gcLogFilePathName,
		      gcProcessName, ".log");

	// Open the new log file for writing
	gLogFile = fopen(fileName, "a+");
	chmod (fileName, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if (gLogFile == NULL) {
		return FALSE;
	}
	
	return TRUE;
}

BOOL Trace_Init()
{
//	char *final, *begin, *context;
	BOOL res;
	char dateStr[100];

	time_t currTime;
	struct tm timeinfo;


	OSAL_init_critical_section(&csWriteProt);

	currTime = time(NULL);
	timeinfo = *(localtime(&currTime));

    res = OSAL_ConfigController_GetNumValue("ignore", OSAL_KEY_ENTRY_SEVERITIES, &gSeverity);
    if (res == FALSE)
    {
        gSeverity = TR_SEV_ALERT + TR_SEV_CRITICAL + TR_SEV_ERR + TR_SEV_WARNING;
    }

    res = OSAL_ConfigController_GetNumValue("ignore", OSAL_KEY_ENTRY_MODULES, &gModuleID);
    if (res == FALSE)   
    {
        gModuleID = TR_MOD_ALL;
    }

	res = GetConfig_LogPath(gcLogFilePathName, MAX_FILENAME_LEN);   
	if (res == FALSE) {
		OSAL_sprintf(gcLogFilePathName, "/tmp");
	}

	if (strlen(gcLogFilePathName) == 0) {
		OSAL_sprintf(gcLogFilePathName, "/tmp");
	}

	if (!OSAL_create_directory(gcLogFilePathName)) {
		if (GetLastError() != WMX_EEXIST) {
			return FALSE;
		}
	}
	
	// get the process name
	OSAL_get_processname(gcProcessName, MAX_PATH, getpid());

	if (!Trace_OpenLogFile()) {
		return FALSE;
	}

	OSAL_atomic_compareExchange((LPLONG) &isInitialized, TRUE, FALSE);

	TRACE(TR_MOD_ALL, TR_SEV_NOTICE,
	      "new tarce ================================================");
	OSAL_sprintf_s(dateStr, sizeof(dateStr) / 2, "%02d:%02d:%02d",
		  timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
	TRACE(TR_MOD_ALL, TR_SEV_NOTICE,
	      "new trace   %s  Trace file opened at %s", gcProcessName, dateStr);
	TRACE(TR_MOD_ALL, TR_SEV_NOTICE,
	      "new tarce ================================================");
	
	return TRUE;
}

EXPORT BOOL TraceAgent_ReloadFilterParams()
{
	BOOL res;
	time_t currTime;
	struct tm *ptimeinfo;
	UINT32 sev;
	UINT32 moduleID;

    res = OSAL_ConfigController_GetNumValue("ignore", OSAL_KEY_ENTRY_SEVERITIES, &sev);
    res &= OSAL_ConfigController_GetNumValue("ignore", OSAL_KEY_ENTRY_MODULES, &moduleID);

	currTime = time(NULL);
	ptimeinfo = localtime(&currTime);

	if (res == TRUE) {
		gSeverity = sev;
		gModuleID = moduleID;


		OSAL_enter_critical_section(&csWriteProt);
		fprintf(gLogFile,
			"%02d:%02d:%02d@@@@Trace Filters Have Changed, Severity = 0x%x, Modules = 0x%x\n",
			ptimeinfo->tm_hour, ptimeinfo->tm_min, ptimeinfo->tm_sec, gSeverity, gModuleID);
		fflush(gLogFile);
		OSAL_exit_critical_section(&csWriteProt);
	} else {

		OSAL_enter_critical_section(&csWriteProt);
		fprintf(gLogFile,
			"%02d:%02d:%02d@@@@Trace Filters Haven't Changed !!!, Severity = 0x%x, Modules = 0x%x\n",
			ptimeinfo->tm_hour, ptimeinfo->tm_min, ptimeinfo->tm_sec, gSeverity, gModuleID);
		fflush(gLogFile);
		OSAL_exit_critical_section(&csWriteProt);
	}

	return res;
}

void TraceAgent_SetSeverity(SEVERITY sev)
{
	gSeverity = sev;
}

SEVERITY TraceAgent_GetSeverity()
{
	return gSeverity;
}

void TraceAgent_SetModule(MODULE_ID moduleID)
{
	gModuleID = moduleID;
}

MODULE_ID TraceAgent_GetModule()
{
	return gModuleID;
}

void Trace_Finalize()
{
	OSAL_atomic_compareExchange((LPLONG) & isInitialized, FALSE, TRUE);
	Trace_CloseLogFile();
	OSAL_delete_critical_section(&csWriteProt);
}

EXPORT void TraceAgent_SetMessageProperties(char *buf, MODULE_ID moduleID,
					    SEVERITY severity, const char *file,
					    const char *function, int line)
{
	// if the trace agent is not initialized - exit
	if (FALSE == OSAL_atomic_compareExchange((LPLONG) & isInitialized, FALSE, FALSE)) 
	{
		return;
	}
	
	// TODO - XXX - combine the two parts of the macro to 1 function ?!
	OSAL_enter_critical_section(&csWriteProt);	// Leave is in the other part of the macro

	gMessageProp.moduleID = moduleID;
	gMessageProp.severity = severity;
	gMessageProp.file = file;
	gMessageProp.function = function;
	gMessageProp.line = line;
}

EXPORT void TraceAgent_PrintTrace(const char *fmt, ...)
{
	va_list arglist;
	time_t currTime;
	struct tm timeinfo;
	
	const char *delimitedFileName = NULL;
	int tmpByteWritten;
	char userMessage[512] = {0}, fullMsg[512 + 128] = {0};

	// Make sure that the log file is initialized
	if (gLogFile == NULL)
		return;

	if ((gMessageProp.moduleID & gModuleID) && (gMessageProp.severity & gSeverity)) {

		delimitedFileName = strrchr(gMessageProp.file, '/');
		if (delimitedFileName == NULL) {
			delimitedFileName = gMessageProp.file;
		} else {
			delimitedFileName = delimitedFileName + 1;
		}

		currTime = time(NULL);
		timeinfo = *(localtime(&currTime));

		va_start(arglist, fmt);
		vsnprintf(userMessage, 512, fmt, arglist);
		va_end(arglist);

		OSAL_snprintf(fullMsg, 512 + 128, "%s [%s]", userMessage, gMessageProp.function);
		


		tmpByteWritten = fprintf(gLogFile, "%02d:%02d:%02d:%12u @%-8s@%-15s@%-150s@%-16s(%d)\t@%s\n",
			timeinfo.tm_hour,
			timeinfo.tm_min,
			timeinfo.tm_sec,
			OSAL_get_threadid(),
			GetSeverityName((Severities)gMessageProp.severity),
			GetModuleName((MODULE_IDS)gMessageProp.moduleID),
			fullMsg,			
			delimitedFileName,
			gMessageProp.line,
			gcProcessName);

		fflush(gLogFile);
	}

	OSAL_exit_critical_section(&csWriteProt);
}


EXPORT void TraceAgent_WriteTrace(MODULE_IDS moduleID, Severities severity, const char* file, const char* function, int line,const char *fmt, ...)
{
  va_list arglist;
  struct tm timeinfo;
  time_t currTime;
  BOOL result;
  const char *delimitedFileName = NULL;
  int tmpByteWritten;
  char userMessage[512] = {0}, fullMsg[512 + 128] = {0};

  if (FALSE == OSAL_atomic_compareExchange((LPLONG) & isInitialized, FALSE, FALSE)) {

	result = Trace_Init();
	if (result ==FALSE)
	return;
  }
  
  OSAL_enter_critical_section(&csWriteProt);	// Leave is in the other part of the macro
  
  // Make sure that the log file is initialized
  if (gLogFile == NULL) {
  OSAL_exit_critical_section(&csWriteProt);
    return;
  }

  if ((moduleID & gModuleID) && (severity & gSeverity)) {

    delimitedFileName = strrchr(file, '/');
    if (delimitedFileName == NULL) {
      delimitedFileName = file;
    } else {
      delimitedFileName = delimitedFileName + 1;
    }
    
	currTime = time(NULL);
    timeinfo = *(localtime(&currTime));
    
    va_start(arglist, fmt);
    vsnprintf(userMessage, 512, fmt, arglist);
    va_end(arglist);
    
    snprintf(fullMsg, 512 + 128, "%s [%s]", userMessage, function);
    
    tmpByteWritten = fprintf(gLogFile, "%02d:%02d:%02d:%12u @%-8s @%-15s@%-150s@%-16s(%d)\t@%s\n",
			     timeinfo.tm_hour,
			     timeinfo.tm_min,
			     timeinfo.tm_sec,
			     OSAL_get_threadid(),
			     GetSeverityName((Severities)severity),
			     GetModuleName((MODULE_IDS)moduleID),
			     fullMsg,			
			     delimitedFileName,
			     line,
			     gcProcessName);
    
    fflush(gLogFile);
  }
  
  OSAL_exit_critical_section(&csWriteProt);

}
