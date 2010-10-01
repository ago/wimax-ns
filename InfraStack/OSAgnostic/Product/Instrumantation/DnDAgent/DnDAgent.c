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
#include "wimax_osal_types.h"
#include "wimax_osal_string.h"
#include "wimax_osal_primitives.h"

#include "Intel_80216_L4_interface_OS.h"
#include "IPC_Server.h"

#include "DnDServerSocket.h"
// bitman include files:
#include "TraceLogger.h"
#include "TraceSubSystem.h"

#include "DnDAgent.h"
#include "DnDAgent_Internal.h"
#include "L4DnDHandler.h"
#include "L4DnDHandler_Internal.h"
#include "DnDUtils.h"
#include "RemoveExcessFiles.h"
#include "wimax_osal_config_controler.h"

#include "CommonServices.h"
#include "XmlParser.h"
#include "L4MonitorGroups.h"
#include "L3L4TlvTypes.h"
#include "L3L4CommonDefines.h"
#include "wmxSDK_DnD_Common.h"
#include "Queue.h"
#include "L4BufMan_L4Common.h"
#include "MonitorGeneral.h"
#include "TraceModule.h"
#include "L5Dispatcher.h"

#include "L4ConfigurationManager.h"
/************************************************************************/
/* Definitions                                                          */
/************************************************************************/
// @TODO move to OSAL

#define FILE_NAME_LEN			1024
#define LINE_BUF_MAX_LEN		1024
#define MAX_BUF_LEN				8192

#ifdef NATIVE_WINDOWS

#define PATH_SEPARATOR			"\\" // Windows		
#define INITIAL_DIR_PATH		"."##PATH_SEPARATOR##"trace" // path to use before it is configured by the user
#define TRACE_FILE_NAME_PREFIX	 PATH_SEPARATOR##"Trace"
#define MONITOR_FILE_NAME_PREFIX PATH_SEPARATOR##"Monitor"

#else

#define INITIAL_DIR_PATH		"/var/log/wimax/"
#define TRACE_FILE_NAME_PREFIX	 "/Trace"
#define MONITOR_FILE_NAME_PREFIX "/Monitor"
#define PATH_SEPARATOR			"/"  // Linux */

#endif

#define INITIAL_DIR_PATH_SIZE	sizeof(INITIAL_DIR_PATH)
#define DEFAULT_FILE_NAME_SUFFIX "0000.log"
#define FILE_NAME_PREFIX_SIZE	sizeof(FILE_NAME_PREFIX)
#define MAX_TRACE_FILE_SIZE		204800
#define FILE_NAME_MAX_NUMBER	10000
#define _SH_DENYWR				0x20
#define MAX_MESSAGE_SIZE		50
#define TRACE_TOOL_MAJOR_VERSION 1
#define TRACE_TOOL_MINOR_VERSION 1

//This value is just a patch! This needs to be fixed and calculated at run time.
#define ADDITIONAL_PATH_SIZE	70


#define ENABLE_THREAD			1
#define DISABLE_THREAD			0

#define MONITOR_ON				1
#define MONITOR_OFF				0

#define NUM_DELIMITERS_WITH_DISPLAY_STRING		6
#define NUM_DELIMITERS_WITHOUT_DISPLAY_STRING	5

#define MAX_PATH_LEN			1024

/************************************************************************/
/* Macros                                                               */
/************************************************************************/
#define ARRAY_SIZE(arr)				sizeof(arr) / sizeof(arr[0])
#define MAKE_ZERO_TERMINATED(str)	(str)[ARRAY_SIZE(str) - 1] = '\0'
#define MAKE_UINT32(msb, lsb)		((UINT32)(((UINT16)(lsb)) | ((UINT32)((UINT16)(msb))) << 16))

/************************************************************************/
/* Internal structures type definitions                                 */
/************************************************************************/
typedef struct  
{
	UINT32 timeStamp;
	UINT32 severity;
	UINT32 subSystemID;
	UINT32 moduleID;
	UINT32 numOfParams;
	UINT32 params[3];
	BOOL   bufferOverrun;
	char   *szFormatString;
	char   *szFileName;
	UINT32 lineNo;
	void   *pPayload;
	UINT32 payloadSize;
} TraceLoggerInfo;

typedef enum _MsgOrigin
{
	NOT_INITIALIZED = 0,
	SHARED_MEMORY,
	L4_INDICATION
} MsgOrigin;

typedef enum _DnDOutputMode
{
	OUTPUT_NOT_INITIALIZED = 0,
	DUMP_TO_FILES,
	SEND_OVER_SOCKET
} DnDOutputMode;

/************************************************************************/
/* static variables                                                     */
/************************************************************************/
static Queue			sMsgsQ;
static OSAL_thread_t	sFileWriterThread;
static OSAL_event_t		writeThreadKillEvent;
static pDnDOutputCB_t	pDnDOutputCb;
static DnDOutputMode	dnDOutputMode = OUTPUT_NOT_INITIALIZED;

static BOOL				isOutputEnabled = FALSE;

static char				*sDsimDefault = "C:\\temp\\dSim_Default\\";


// file variables
static FILE				*pTraceLogFile					= NULL;	/* At the first run - open a new log file, overwriting the previous*/
static UINT32			traceFileWriteSize				= 0;
static UINT32			traceFileSequenceNumber			= 0;
static UINT32			prevTraceFileSequenceNumber		= 0;
static char				traceFileName[_MAX_PATH]		= "";

static FILE				*pMonitorLogFile				= NULL;	/* At the first run - open a new log file, overwriting the previous*/
static UINT32			monitorFileWriteSize			= 0;
static UINT32			monitorFileSequenceNumber		= 0;
static UINT32			prevMonitorFileSequenceNumber	= 0;
static char				monitorFileName[_MAX_PATH]		= "";

static UINT32			path_len						= 0;
static char				path_buffer[_MAX_PATH];
static char				parentDirectory[_MAX_PATH];
static BOOL				isSetPathInInitRequired = TRUE;

// L5 connections
static L5_CONNECTION			nDisTraceConnection = NULL;
static tL5DispatcherFunctions	*pFuncs;

//Monitor parameters
static UINT8			dndUtilsMonitorBuffer[BM_DnDUtils_Statistics_BYTES_SIZE];
static UINT16			dndUtilsMonitorBufferSize = BM_DnDUtils_Statistics_BYTES_SIZE;
static UINT32			totalNumOfMessages = 0;
static UINT32			totalSizeInBytes = 0;
static UINT32			numberOfLostMessagesRaised = 0;

static UINT32			maxNumOfFilesInDir = FILE_NAME_MAX_NUMBER;


// DnD messages origin
static MsgOrigin		msgOrigin = NOT_INITIALIZED;		
static UINT32				getDeviceTraces = 0;
tUtilityFunctions		*pUtils;

static int g_windows_dsim_sock = (-1);


static int UpdateDefaultMonitorAndTraceFilters();

/************************************************************************/
/* Methods							                                    */
/************************************************************************/

void DnDAgent_EventHandler( 		 L5_CONNECTION Conn,
						   L5_EVENT eEvent,
						   void *pvEventData,
						   void *pvUserContext )
{
	int res;

	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_WARNING, "Got event - %d",eEvent);

	if (L5_EVENT_DRIVER_CONNECTED == eEvent)
	{
		// read the data about the filters from the XML
		res = UpdateDefaultMonitorAndTraceFilters();
		if (res != 0)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "Could not read monitor and trace filters from XML");
		}
	}
}
static void PostDnDUtilsMonitor(UINT32 dataSize)
{
	if (L4DnDHndlr_IsMonFiltered((UINT16)L3L4_TLV_TYPE_MONITOR_DND_UTILS_STATISTICS))
	{
		if (0 == dataSize)
		{
			numberOfLostMessagesRaised++;
		}
		else
		{
			totalNumOfMessages++;
			totalSizeInBytes += dataSize;
		}
		BM_DnDUtils_Statistics_TotalNumOfMessages_SET(dndUtilsMonitorBuffer, totalNumOfMessages);
		BM_DnDUtils_Statistics_TotalSizeInBytes_SET(dndUtilsMonitorBuffer, totalSizeInBytes);
		BM_DnDUtils_Statistics_LastMessageSizeInBytes_SET(dndUtilsMonitorBuffer, dataSize);
		BM_DnDUtils_Statistics_NumberOfLostMessagesRaised_SET(dndUtilsMonitorBuffer, numberOfLostMessagesRaised);
		BM_DnDUtils_Statistics_NumberOfMessagesInQueue_SET(dndUtilsMonitorBuffer, Queue_Count(&sMsgsQ));
		BM_DnDUtils_Statistics_CurrentFileIndex_SET(dndUtilsMonitorBuffer, (UINT16)traceFileSequenceNumber);
		L4DnDHndlr_PostMon(dndUtilsMonitorBuffer, (UINT16)L3L4_TLV_TYPE_MONITOR_DND_UTILS_STATISTICS,dndUtilsMonitorBufferSize);
	}
}

static BOOL EnableFileWritingThread()
{
	BOOL status = TRUE;


	if((FALSE == DnDUtils_IsDsim())  && SHARED_MEMORY == msgOrigin )
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Resuming DnDUtils thread");
		status = DnDUtils_ResumeThread();

		if(TRUE == status)
		{
			isOutputEnabled = TRUE;
		}
	}
	else
	{
		isOutputEnabled = TRUE;
	}

	return status;
}

static BOOL DisableFileWritingThread()
{
	BOOL status = TRUE;

	if((FALSE == DnDUtils_IsDsim()) && SHARED_MEMORY == msgOrigin)
	{
		status = DnDUtils_SuspendThread();

		if(TRUE == status)
		{
			isOutputEnabled = FALSE;
		}
	}
	else
	{
		isOutputEnabled = FALSE;
	}

	return status;
}

static BOOL SetPathToOutputFiles(char* path)
{
	UINT32	filename_len;
	int		rc;
	SYSTEMTIME  timeInfo;

	//In this case we don't write files anyway and this is just a stub.
	if (DnDUtils_IsDsim() && msgOrigin == SHARED_MEMORY)
	{
		return TRUE;
	}

	if (OSAL_strnlen(path, _MAX_PATH) + ADDITIONAL_PATH_SIZE > _MAX_PATH)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[SetPathToOutputFiles]: The path supplied is too large: %s with length %d",path, OSAL_strnlen(path, _MAX_PATH));
		return FALSE;
	}

	// save the parent directory
	OSAL_sprintf_s(parentDirectory,  _MAX_PATH, "%s", path);

	traceFileSequenceNumber			= 0;
	prevTraceFileSequenceNumber		= 0;
	monitorFileSequenceNumber		= 0;
	prevMonitorFileSequenceNumber	= 0;

	/************************************************************************/
	/* creating a special directory which will contain all traces from this */
	/* run. directory name format contains current date and hour of running.*/
	/* traces files will be created in this directory.                      */ 
	/************************************************************************/	


	// copy the path from the user
	path_len = OSAL_sprintf_s(path_buffer,  _MAX_PATH - path_len, "%s", path);

	// Get the system time
	OSAL_GetLocalTime(&timeInfo);

	// add the time to the path
	path_len += OSAL_sprintf_s(path_buffer + path_len, _MAX_PATH - path_len, PATH_SEPARATOR"%02d_%02d_%02d__%02d_%02d_%02d", 
		timeInfo.wYear, timeInfo.wMonth, timeInfo.wDay, timeInfo.wHour, timeInfo.wMinute, timeInfo.wSecond);

	// create the directory
	rc = OSAL_create_directory(path_buffer);
	if (rc == 0)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[SetPathToOutputFiles]: Directory %s does not exist! Trace Logger Abort!",path_buffer);
		return FALSE;
	}


	/* First Trace file handling */

	/************************************************************************/
	/* after creating a directory, an initial file will be created in it.   */
	/* fileName variable contain full path of the file and its name e.g.    */
	/* ...\Win32UserMode\Framework\2005_12_15__17_24_20\trace0001           */
	/************************************************************************/

	// copy the path to the file name
	OSAL_strncpy_s(traceFileName, _MAX_PATH,path_buffer, _MAX_PATH - 1);
	filename_len = path_len;

	// add the "\trace" prefix
	filename_len += OSAL_sprintf_s(traceFileName+filename_len, _MAX_PATH - filename_len, "%s", TRACE_FILE_NAME_PREFIX);

	// add the sequence number
	filename_len += OSAL_sprintf_s(traceFileName+filename_len, _MAX_PATH - filename_len, "%04d.log", traceFileSequenceNumber);
	traceFileSequenceNumber++;

	//If the last file is still open we first close it.
	if (NULL != pTraceLogFile)
	{
		if ( OSAL_fclose(pTraceLogFile) != 0 )
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Trace Logger Internal Error (fclose)");
		}
	}

	// open the file - Ofer f changed
	if ((OSAL_fopen(&pTraceLogFile, traceFileName, "w+b", _SH_DENYWR)) == (-1))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[SetPathToOutputFiles]: Could not open file '%s'", traceFileName);
		if ( traceFileSequenceNumber !=0 )		
		{
			traceFileSequenceNumber--;
		}
		return FALSE;
	}

	traceFileWriteSize = 0;

	/* First Monitor file handling */

	/************************************************************************/
	/* after creating a directory, an initial file will be created in it.   */
	/* fileName variable contain full path of the file and its name e.g.    */
	/* ...\Win32UserMode\Framework\2005_12_15__17_24_20\trace0001           */
	/************************************************************************/

	// copy the path to the file name
	OSAL_strncpy_s(monitorFileName, _MAX_PATH, path_buffer, _MAX_PATH - 1);
	filename_len=path_len;

	// add the "\trace" prefix
	filename_len += OSAL_sprintf_s(monitorFileName+filename_len, _MAX_PATH - filename_len, "%s", MONITOR_FILE_NAME_PREFIX);

	// add the sequence number
	filename_len += OSAL_sprintf_s(monitorFileName+filename_len, _MAX_PATH - filename_len, "%04d.log", monitorFileSequenceNumber);
	monitorFileSequenceNumber++;

	//If the last file is still open we first close it.
	if (NULL != pMonitorLogFile)
	{
		if ( OSAL_fclose(pMonitorLogFile) != 0 )
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Monitor Logger Internal Error (fclose)");
		}
	}

	// open the file - Ofer f changed
	if ((OSAL_fopen(&pMonitorLogFile, monitorFileName, "w+b", _SH_DENYWR)) == (-1))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[SetPathToOutputFiles]: Could not open file '%s'", monitorFileName);
		if ( monitorFileSequenceNumber !=0 )		
		{
			monitorFileSequenceNumber--;
		}
		return FALSE;
	}

	monitorFileWriteSize = 0;

	// erase directories in the new directory (if they exceed the limit).
	// if we want to disable this feature we should wrote '0' in the registry key
	EraseExcessDirectories(parentDirectory);

	// If we are working in the remote configuration: write the directory in the registry
	if (DnDUtils_IsRemote() && msgOrigin == L4_INDICATION)
	{
		L4Configurations_setDndFilesPath(path_buffer);
	}

	return TRUE;
}

//TODO: Change this so that the calling function allocates memory
static char* GetPathToOutputFiles()
{
	if (FALSE == DnDUtils_IsDsim() || msgOrigin == L4_INDICATION)
	{
		return path_buffer;
	}
	else
	{
		return sDsimDefault;
	}
	//char curDir[MAX_PATH_LEN];
	//GetCurrentDirectory(MAX_PATH_LEN, curDir);
	//wcscat(curDir, "\\");
	//wcscat(curDir, path_buffer);	
	//return curDir;
}
static byte GetValue(char* c)
{
	if (((*c - '0' <= 9) && (*c - '0' >= 0))||
		((*c - 'a' <= 5) && (*c - 'a' >= 0)))
	{
		switch(*c)
		{
		case 'a':
			return 10;
			break;
		case 'b':
			return 11;
			break;
		case 'c':
			return 12;
			break;
		case 'd':
			return 13;
			break;
		case 'e':
			return 14;
			break;
		case 'f':
			return 15;
			break;
		default:
			return (*c - '0');
			break;
		}
	}
	else // this is an invalid char
	{
		return 0;
	}
}

static int GetBufferFromXml(pXmlElement xmlElm, char* moduleName, BYTE* dataBuffer, int sizeOfDataBuffer)
{
	BOOL foundFilters = FALSE;
	char* msb;
	char* lsb;
	char tempText[MAX_STR_LEN];
	char filterName[MAX_STR_LEN];
	int i, j, k, numberOfFilters, numberOfBuffers;
	pXmlElement filter, buffer;

	if (FindAttribute(xmlElm, "active") != NULL) // if the active attribute is there
	{
		OSAL_strncpy_s(tempText, MAX_STR_LEN, FindAttribute(xmlElm, "active"), MAX_STR_LEN - 1); // find the name of the active filter
		numberOfFilters = GetChildrenCount(xmlElm);
		for (i=0; i< numberOfFilters; i++)
		{
			filter = GetChildAt(xmlElm, i);
			if (OSAL_stricmp(filter->data.name, moduleName) == 0) // verify that this is a correct node
			{
				// Get the filter name and check if this is the filter we wanted
				if (FindAttribute(filter, "name") != NULL)
				{
					OSAL_strncpy_s(filterName, MAX_STR_LEN, FindAttribute(filter, "name"), MAX_STR_LEN - 1);
					if ((filterName != NULL) && (OSAL_stricmp(filterName, tempText) == 0)) 
					{
						//this is the wanted trace element
						int indexToWrite = 0;
						int textBufferSize;
						TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Reading from %s buffer %s", moduleName, filterName);

						// read the data and store it
						numberOfBuffers = GetChildrenCount(filter);
						for (j=0; j< numberOfBuffers; j++)
						{
							buffer = GetChildAt(filter, j);
							OSAL_strncpy_s(tempText, MAX_STR_LEN, GetElementInnerText(buffer), MAX_STR_LEN - 1);
							textBufferSize = OSAL_strnlen(tempText, MAX_STR_LEN - 1);

							// write the data to the correct buffer
							for (k=0; (k < textBufferSize/2) && (k + indexToWrite < sizeOfDataBuffer); k++)
							{
								msb = tempText + k*2;
								lsb = tempText + k*2 + 1;

								dataBuffer[k + indexToWrite] = (byte)(GetValue(msb)*16 + GetValue(lsb));
							} 
							indexToWrite += textBufferSize/2; // 2 - because each byte is written as text into 2 chars
						}

						// Indicate that we have default filters for the trace
						//no need to search for more active nodes
						foundFilters = TRUE;
						TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Succeded in setting default %s filter", moduleName);
						break; 
					}
				}
				else // name attribute doesn't exist
				{
					TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "'name' attribute doesn't exist in on of the %s filters", moduleName);
				}
			}
		}
	}
	else
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Not using default %s because 'active' node doesn't exist", moduleName);
	}

	// Here we check if we found an active filter buffer
	if (foundFilters == FALSE)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Could not find default %s filter with name %s", moduleName, tempText);
		return -1;
	}
	else // we found an active filter
	{
		return 0;
	}
}

static int UpdateDefaultMonitorAndTraceFilters()
{
	// This method reads from the 'DefaultTracesAndMonitors' xml, looks for the 'active' filter for the trace
	// and monitor, and sends the buffers to the device.
	// The purpose is to set monitors and traces without external tools.

	char					tmpPath[MAX_REGISTRY_ANSWER];
	char					defaultBufferPath[_MAX_PATH];
	char					tempText[MAX_STR_LEN];
	static byte				defaultMonitors[MONITOR_FILTER_TABLE_SIZE];
	static byte				defaultTraces[TRACE_SEVERITIES_TABLE_SIZE];
	wmx_Status_t			status;
	BOOL					res;

	pXmlElement rootElm, useDefaults, templates, traces, monitors;

	// first we "zero" the buffers
	OSAL_ZeroMemory(defaultMonitors, MONITOR_FILTER_TABLE_SIZE);
	OSAL_ZeroMemory(defaultTraces, TRACE_SEVERITIES_TABLE_SIZE);

	// open the xml file and get the root mode
	L4Configurations_getRootPath(tmpPath);
	if (OSAL_strnlen(tmpPath, _MAX_PATH) + 50 > _MAX_PATH)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[GetDefaultMonitorAndTraceFilters]: The RootPath is too large");
		return -1;
	}

		

	OSAL_strncpy_s(defaultBufferPath,_MAX_PATH,tmpPath,(_MAX_PATH - strlen("DefaultTracesAndMonitors.xml") - 1)); 
	OSAL_strncat_s(defaultBufferPath, _MAX_PATH, "DefaultTracesAndMonitors.xml",strlen("DefaultTracesAndMonitors.xml"));


	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "Complete TraceMonitorFilter path is %s.", defaultBufferPath);
	
	rootElm = CreateEmptyXmlData();
	if (ReadXmlFile(rootElm, defaultBufferPath) != TRUE)
	{
		FreeXmlData(rootElm);
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[GetDefaultMonitorAndTraceFilters]: cannot load DefaultTracesAndMonitors.xm");
		return -1;
	}
	templates = FindChild(rootElm, "Templates");
	if (templates == NULL)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Not using defaults because \"Templates\" node doesn't exist. XML is corrupt");
		FreeXmlData(rootElm);
		return -1;
	}

	// check if the user wants to use the defaults, meaning that the traces or Monitor are needed.
	useDefaults = FindChild(templates, "UseDefaults");
	if (useDefaults != NULL)
	{
		OSAL_strncpy_s(tempText, MAX_STR_LEN, GetElementInnerText(useDefaults), MAX_STR_LEN - 1);	
		if(OSAL_stricmp(tempText, "true") != 0)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Not using defaults because \"UseDefaults\" is not 'true'");
			FreeXmlData(rootElm);
			return 0;
		}
		else // User wants to use the defaults
		{
			res = EnableFileWritingThread();
			if (res != TRUE)
			{
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Could not enable file writing");
				FreeXmlData(rootElm);
				return -1;
			}
		}
	}
	else // if 'UseDefaults' node doesn't exist - behave like 'false'
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Not using defaults because \"UseDefaults\" node doesn't exist");
		FreeXmlData(rootElm);
		return -1;
	}

	// find the active trace and read its data:
	traces = FindChild(templates, "Traces");
	if (traces != NULL)
	{
		if (0 == GetBufferFromXml(traces, "Trace", defaultTraces, TRACE_SEVERITIES_TABLE_SIZE))
		{
			// we found the trace buffer
			status = DeviceSetTraceFilter(nDisTraceConnection, pFuncs, (char *)defaultTraces, TRACE_SEVERITIES_TABLE_SIZE);
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Could not set trace filters");
			}
		}
	}
	else // 'Traces' node doesn't exist
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Not using default traces because 'Traces' node doesn't exist");
	}

	// find the active monitor and read its data:
	monitors = FindChild(templates, "Monitors");
	if (monitors != NULL)
	{
		if (0 == GetBufferFromXml(monitors, "Monitor", defaultMonitors, MONITOR_FILTER_TABLE_SIZE))
		{
			// we found the monitor buffer
			status = DeviceSetMonitorFilter(nDisTraceConnection, pFuncs, (char *)defaultMonitors, MONITOR_FILTER_TABLE_SIZE);
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Could not set monitor filters");
			}
			status = DeviceMonitorOnControl(nDisTraceConnection, pFuncs); // set monitor to On
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Could not set monitor to On");
			}
		}
	}
	else // 'Monitors' node doesn't exist
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Not using default monitors because \"Monitors\" node doesn't exist");
	}

	// free the xml document. this frees all inner xml nodes
	FreeXmlData(rootElm);
	return 0;
}
static BOOL GetCurrentWritingPosition(UINT8* buffer, UINT32 * size)
{
	int len;
	UINT32 tmpFileSeqNum;

	if(*size < path_len + sizeof(traceFileSequenceNumber) + sizeof(traceFileWriteSize) + 1)
	{
		//TODO - add trace

		//update the size that should be allocated
		*size = path_len + sizeof(traceFileSequenceNumber) + sizeof(traceFileWriteSize) + 1;
		return FALSE;
	}

	//copy the path
	if((FALSE == DnDUtils_IsDsim()) && SHARED_MEMORY == msgOrigin)
	{
		len = OSAL_strnlen(path_buffer, _MAX_PATH)*2 + 2;
		OSAL_memcpy_s(buffer, *size, path_buffer, len);
	}
	else
	{
		//create the path that dsim creates
		len = OSAL_strnlen(sDsimDefault, _MAX_PATH)*2 + 2;
		OSAL_memcpy_s(buffer, *size, sDsimDefault, len);
	}

	//write the current trace file index
	tmpFileSeqNum = traceFileSequenceNumber + ((traceFileSequenceNumber) ? -1 : 0 );
	OSAL_memcpy_s(buffer + len, *size - len, &tmpFileSeqNum, sizeof(traceFileSequenceNumber));

	TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Current trace file index = %d", tmpFileSeqNum);

	len += sizeof(traceFileSequenceNumber);

	//write the current position in the trace file
	OSAL_memcpy_s(buffer + len, *size - len, &traceFileWriteSize, sizeof(traceFileWriteSize));

	TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Current location in trace file = %d", traceFileWriteSize);

	//update the copied size
	len += sizeof(traceFileWriteSize);

	//write the current monitor file index
	tmpFileSeqNum = monitorFileSequenceNumber + ((monitorFileSequenceNumber) ? -1 : 0 );
	OSAL_memcpy_s(buffer + len, *size - len, &tmpFileSeqNum, sizeof(monitorFileSequenceNumber));

	TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Current monitor file index = %d", tmpFileSeqNum);

	len += sizeof(monitorFileSequenceNumber);

	//write the current position in the trace file
	OSAL_memcpy_s(buffer + len, *size - len, &monitorFileWriteSize, sizeof(monitorFileWriteSize));

	TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Current location in monitor file = %d", monitorFileWriteSize);

	//update the copied size
	*size = len + sizeof(monitorFileWriteSize);

	return TRUE;
}

static int bhAdapter_Write(PVOID	pData, 
						   UINT32	dataLength,
						   char*	fileName,
						   char*	fileNamePrefix,
						   PUINT32	pFileWriteSize,
						   PUINT32	pFileSequenceNumber,
						   PUINT32	pPrevFileSequenceNumber,
						   FILE**	pLogFile)
{
	UINT32  writenBytes				= 0;
	char	pathBuffer[_MAX_PATH]	= {0};
	UINT32	rc						= 0;

	if (dataLength != 0) 
	{
		/************************************************************************/
		/* check that current file didn't exceed its max size.                   */
		/* if it did -> then open a new file.                                   */
		/* if it didn't, continue with current file.							*/
		/************************************************************************/
		if (*pFileWriteSize + dataLength > MAX_TRACE_FILE_SIZE)
		{
			// create the new file name
			OSAL_sprintf_s(fileName, _MAX_PATH, "%s%s%04d.log", path_buffer, fileNamePrefix, *pFileSequenceNumber);
			OSAL_sprintf_s(pathBuffer, _MAX_PATH, "%s%s%04d.log", path_buffer, fileNamePrefix, *pFileSequenceNumber + 1);

			// file name sequence number is blocked. if it reached it max value, than wrap around
			*pPrevFileSequenceNumber = *pFileSequenceNumber;
			*pFileSequenceNumber = (*pFileSequenceNumber + 1) % maxNumOfFilesInDir;

			//If the last file is open - close it
			if (NULL != *pLogFile)
			{
				OSAL_fclose(*pLogFile);
				*pLogFile = NULL;
			}

			// Delete the file ahead file
			if (!OSAL_set_file_stat(pathBuffer, OSAL_FILE_ATTRIBUTE_NORMAL))
			{
				rc = OSAL_GetLastError();
				if (OSAL_ERROR_FILE_NOT_FOUND != rc)
				{
					TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING,"Failed to changing file attributes for %s, Error Code = %d (0x%08X), Continuing...", pathBuffer, rc, rc);
				}
			}

			if (!OSAL_delete_file(pathBuffer))
			{
				rc = OSAL_GetLastError();
				if (OSAL_ERROR_FILE_NOT_FOUND != rc)
				{
					TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR,"Failed to delete file %s, Error Code = %d (0x%08X), Continuing...", pathBuffer, rc, rc);
				}
			}
			
			// open the new file
			if ((OSAL_fopen(pLogFile, fileName, "w+b", _SH_DENYWR))==(-1))
			{
				// if we didn't succeed - return to the old file number
				*pFileSequenceNumber = *pPrevFileSequenceNumber;
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR,"Failed in opening new file for writing");
				return -1;
			}

			// update the new file size
			*pFileWriteSize = 0;
		}

		// write the data and update the size
		if (*pLogFile != NULL)
		{
			writenBytes = (UINT32)OSAL_fwrite(pData, sizeof(unsigned char), dataLength, *pLogFile);
			if (writenBytes > 0)
			{
				OSAL_fflush(*pLogFile);
				(*pFileWriteSize) += dataLength;
			}
		}
	}

	return 0;
}

static int  TraceBhAdapter_Write(void *pData, UINT32 dataLength)
{
	return bhAdapter_Write(	pData, 
		dataLength, 
		traceFileName,
		TRACE_FILE_NAME_PREFIX,
		&traceFileWriteSize, 
		&traceFileSequenceNumber, 
		&prevTraceFileSequenceNumber, 
		&pTraceLogFile );
}

static int  MonitorBhAdapter_Write(void *pData, UINT32 dataLength)
{
	return bhAdapter_Write(	pData, 
		dataLength, 
		monitorFileName,
		MONITOR_FILE_NAME_PREFIX,
		&monitorFileWriteSize, 
		&monitorFileSequenceNumber, 
		&prevMonitorFileSequenceNumber, 
		&pMonitorLogFile );
}

int AddMessageToQueue(void *pData, UINT32 dataLength)
{
	//Allocate memory for Item
	BOOL res;
	QueueElementData item;
		
	if ( (SEND_OVER_SOCKET == dnDOutputMode) && (g_windows_dsim_sock < 0) )
	{
		//TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Client Socket is not connected Could not send the data");
		return -1;
	}

	item = (QueueElementData) malloc ( sizeof(byte) * dataLength);
	if (NULL == item)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR,"Failed to allocate memory to queue item");
	}

	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG,"IN - packet length: %d", dataLength);
	//Copy the buffer to allocated memory
	OSAL_memcpy_s(item, dataLength, pData, dataLength);

	//Insert to queue
	res = Queue_Enqueue(&sMsgsQ, item);
	if (FALSE == res) 
	{
		return -1;
	}
	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG,"OUT");
	return 0;
}
int AddMessageAndHeaderToQueue(void *pHeader, UINT32 headerLength, void *pData, UINT32 dataLength)
{
	//Allocate memory for Item
	BOOL res;
	UINT8 * item = (UINT8*) malloc ( sizeof(byte) * (dataLength + headerLength));
	if (NULL == item)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR,"Failed to allocate memory to queue item");
	}

	//Copy the header to allocated memory
	OSAL_memcpy_s(item, headerLength, pHeader, headerLength);

	//Copy the buffer to allocated memory
	OSAL_memcpy_s(item + headerLength, dataLength, pData, dataLength);

	//Insert to queue
	res = Queue_Enqueue(&sMsgsQ, (QueueElementData)item);
	if (FALSE == res) 
	{
		return -1;
	}
	return 0;
}

static void FreeAllRecources()
{
	totalNumOfMessages = 0;
	totalSizeInBytes = 0;
	numberOfLostMessagesRaised = 0;

	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "FreeAllRecources(IN)");
	// disconnect from the L5
	if (pFuncs != NULL)
	{
		pFuncs->pfnDisconnect(nDisTraceConnection);
		pFuncs = NULL;
	}

	//Close the current trace file if it is open
	if (NULL != pTraceLogFile)
	{
		if (0 != OSAL_fclose(pTraceLogFile))
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Trace Logger Internal Error (fclose)!");
		}
		pTraceLogFile = NULL;
	}

	//Close the current monitor file if it is open
	if (NULL != pMonitorLogFile)
	{
		if (0 != OSAL_fclose(pMonitorLogFile))
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Monitor Logger Internal Error (fclose)!");
		}
		pMonitorLogFile = NULL;
	}

	//Close event
	if (NULL != writeThreadKillEvent)
	{
		OSAL_delete_event(writeThreadKillEvent);
		writeThreadKillEvent = NULL;
	}

	//Finalize the messages Queue
	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "calling Queue_Finalize");
	Queue_Finalize(&sMsgsQ);

	//Finalize L4 DnD Handler
	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "calling L4DnDHandlr_Finalize");
	L4DnDHandlr_Finalize();	

	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "FreeAllRecources(OUT)");

}

static BOOL RegiserOnL4Indications()
{
	UINT32 l4Indication;
	L5_RESULT l5Result;
	char resBuffer[MAX_BUF_LEN];
	UINT32 resBufferSize = MAX_BUF_LEN;

	//Monitor L4 indication
	l4Indication = L3_L4_OPCODE_REPORT_MONITOR_EVACUATE;
	l5Result = pFuncs->pfnSendReceiveMessage(	nDisTraceConnection, 
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_REGISTER_L4_INDICATION, 
		&l4Indication, 
		sizeof(UINT32), 
		NULL,
		resBuffer, 
		&resBufferSize 
		);

	if (L5_RESULT_OK != l5Result)
	{
		return FALSE;
	}

	//Trace L4 indication
	l4Indication = L3_L4_OPCODE_REPORT_TRACE_EVACUATE; 
	l5Result = pFuncs->pfnSendReceiveMessage(	nDisTraceConnection, 
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_REGISTER_L4_INDICATION, 
		&l4Indication, 
		sizeof(UINT32), 
		NULL, 
		resBuffer, 
		&resBufferSize 
		);

	if (L5_RESULT_OK != l5Result)
	{
		return FALSE;
	}

	return TRUE;
}

static BOOL UnRegisterOnL4Indications()
{
	UINT32 l4Indication;
	L5_RESULT l5Result;
	char resBuffer[MAX_BUF_LEN];
	UINT32 resBufferSize = MAX_BUF_LEN;

	//Monitor L4 indication
	l4Indication = L3_L4_OPCODE_REPORT_MONITOR_EVACUATE;
	l5Result = pFuncs->pfnSendReceiveMessage(	nDisTraceConnection, 
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, 
		&l4Indication, 
		sizeof(UINT32), 
		NULL,
		resBuffer, 
		&resBufferSize 
		);

	if (L5_RESULT_OK != l5Result)
	{
		return FALSE;
	}

	//Trace L4 indication
	l4Indication = L3_L4_OPCODE_REPORT_TRACE_EVACUATE; 
	l5Result = pFuncs->pfnSendReceiveMessage(	nDisTraceConnection, 
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, 
		&l4Indication, 
		sizeof(UINT32), 
		NULL, 
		resBuffer, 
		&resBufferSize 
		);

	if (L5_RESULT_OK != l5Result)
	{
		return FALSE;
	}

	return TRUE;
}

static void OutputQueueItemToSocket()
{
	UINT32	orgSize = 0, remLength	= 0, totalPktSize = 0;
	QueueElementData	item;
	static char dndInd[MAX_DATA_SIZE];
	//char *dndInd = NULL;
	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "Have a packet to be shipped over socket");

	if(g_windows_dsim_sock < 0) 
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Client Socket is not connected Could not send the data");
		return;
	}

	item = Queue_Dequeue(&sMsgsQ);
	
	if ( item == NULL )
		return;

	orgSize = (UINT32)L4BM_GetLength(item) + HEADER_SIZE;
	// This denotes the length of rest of the packet not including this 
	// length bytes itself. 
	remLength = orgSize + 4;

	totalPktSize = remLength + 4; // while shipping out we need to know the total

	// printf("Size is %d %d \n",(UINT32)L4BM_GetLength(item), length);
	((int*)dndInd)[0] = remLength;
	((int*)dndInd)[1] = STATUS_INTEL_80216_CUSTOM;
	OSAL_memcpy_s(dndInd+8, orgSize, item, (UINT32)L4BM_GetLength(item) + HEADER_SIZE);

			

	do
	{
		if(g_windows_dsim_sock < 0) {
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Client Socket is not connected Could not send the data");
			//printf("no Socket not writing anything \n");
			break;
		}

		if (SOCKETS_ERROR == DND_SERVER_SOCKETS_SendToClient(dndInd, totalPktSize, g_windows_dsim_sock)) {
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Client Socket unavailable Could not send data");
			//printf("Client Socket unavailable Could not send data \n");
			break;
		}
	} while (FALSE);
	free(item);

}

static void WriteQueueItemToFile()
{
	UINT32				length	= 0;
	UINT16				opcode	= 0;
	QueueElementData	item;

	item = Queue_Dequeue(&sMsgsQ);

	length = (UINT32)L4BM_GetLength(item) + HEADER_SIZE;

	opcode = L4BM_GetOpcode(item);
	switch(opcode)
	{
	case L3_L4_OPCODE_REPORT_TRACE_EVACUATE:
		TraceBhAdapter_Write(item, length);
		break;
	case L3_L4_OPCODE_REPORT_MONITOR_EVACUATE:
		MonitorBhAdapter_Write(item, length);
		break;
	default:
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[WriteQueueItemToFile]: Unknown L4 Msg Opcode: 0x%04X", opcode);
		break;
	}

	free(item);
}
void DnD_ThreadWriteFunc( LPVOID lpParameter )
{
	// This message is responsible for reading data from the queue and writing it to files
//	QueueElementData item;
	//UINT32 length;

#define		QUEUE_PUMP_BURST	10
	BOOL bStop = FALSE;
	int i = 0;

	UNREFERENCED_PARAMETER(lpParameter);

	TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "Started 'DnD_ThreadWriteFunc' method in new thread");

	for(;!bStop;)
	{
		switch( OSAL_wait_event(writeThreadKillEvent, 0) )
		{
		case WAIT_OBJECT_0:			// Stop
			TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[DnD_ThreadWriteFunc]Stop Event Signaled - Write queue and abort thread");
			while (Queue_Count(&sMsgsQ) > 0)// write everything in the queue before terminating
			{
				//WriteQueueItemToFile();
				pDnDOutputCb();
			}
			TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Done WriteQueueItemToFile");
			bStop = TRUE;
			continue;

		case WAIT_TIMEOUT:			// Write to file
			i = 0;
			if (Queue_Count(&sMsgsQ) > 0)
			{
				while ( (i < QUEUE_PUMP_BURST) && (Queue_Count(&sMsgsQ) > 0) )
				{
					pDnDOutputCb();
					i++;
				}
			}
			else
			{
				OSAL_sleep(500);//If no message is found in the queue we wait until it appears
			}
			break;

		default:					//WAIT_FAILED 
			TRACE(TR_MOD_DND_AGENT, TR_SEV_CRITICAL, "Wait failed!");
			//pFuncs->pfnSendErrorReport(L5_TARGET_DND_AGENT, INTERNAL_PROBLEM);TODO - handle this everywhere
			bStop = TRUE;
			continue;
		}
	}

	return;// 0;
}

APPSRV_INIT_ST OutputFileSystemInit(void)
{
	char tmpPath[MAX_REGISTRY_ANSWER];
	char *dirString;
	char *next_token;

	//We check if we want the AppSrv to open a new directory.
	if ((0 != OSAL_stricmp(traceFileName, "")) && (0 != OSAL_stricmp(traceFileName, ""))) // if a directory was already opened
	{
		do 
		{
			//TODO: Make sure that traceFileSequenceNumber and traceFileWriteSize wasn't deleted
			if ((OSAL_fopen(&pTraceLogFile, traceFileName, "ab", _SH_DENYWR))==(-1)) // open in appending binary mode
			{
				//If we can't open this file then we just open a new session and SetPath
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[DnDAgent_Initialize]: Could not open file '%s' therefore performing SetPath", traceFileName);
				isSetPathInInitRequired = TRUE;
				break;
			}
			else // go to the end of the file
			{
				OSAL_fseek(pTraceLogFile, 0, SEEK_END);
				isSetPathInInitRequired = FALSE;
			}

			if((OSAL_fopen(&pMonitorLogFile, monitorFileName, "ab", _SH_DENYWR))==(-1)) // open in appending binary mode
			{
				//If we can't open this file then we just open a new session and SetPath
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[DnDAgent_Initialize]: Could not open file '%s' therefore performing SetPath", monitorFileName);
				isSetPathInInitRequired = TRUE;
				break;
			}
			else // go to the end of the file
			{
				OSAL_fseek(pMonitorLogFile, 0, SEEK_END);
				isSetPathInInitRequired = FALSE;
			}
		} while(FALSE);
	}
	else
	{
		isSetPathInInitRequired = TRUE;
	}

	//If we need to SetPath
	if (isSetPathInInitRequired)
	{	
		L4Configurations_getRootPath(tmpPath);

		if (OSAL_strnlen(tmpPath, _MAX_PATH) + ADDITIONAL_PATH_SIZE <= _MAX_PATH)
		{
			OSAL_strcpy_s(path_buffer, _MAX_PATH, tmpPath);
		}
		else
		{
			dirString = OSAL_strtok_s(tmpPath,":", &next_token);
			if (NULL == dirString)
			{
				TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "The RootPath did not contain a full path (no : was found in the string). DnD does not support this");
				return INIT_FAIL;
			}
			OSAL_strcpy_s(path_buffer, _MAX_PATH, dirString);
			OSAL_strcpy_s(path_buffer, _MAX_PATH, ":");
		}
		OSAL_strcat_s(path_buffer,  _MAX_PATH, "\\");
		OSAL_strcat_s(path_buffer,  _MAX_PATH, INITIAL_DIR_PATH);
		OSAL_create_directory(path_buffer);
		if (FALSE == SetPathToOutputFiles(path_buffer))
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "DnD agent is not initiallized - could not set the default path to the output files");
			return INIT_FAIL;
		}
	}

	// Read the registry key of max number of files in dir
	L4Configurations_getMaxNumOfFiles(&maxNumOfFilesInDir);
	if (maxNumOfFilesInDir <= 0 || maxNumOfFilesInDir >FILE_NAME_MAX_NUMBER)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[DnDAgent_Initialize]Max number of files read in regisrty is %u which is invalid. Setting max number of files to %d", maxNumOfFilesInDir, FILE_NAME_MAX_NUMBER);
		maxNumOfFilesInDir = FILE_NAME_MAX_NUMBER;
	}

	return INIT_SUCCESS;
}

void DnD_SOCKETS_HandleNewConnection( SOCKETS_CLIENT_ID clientID, void** context )
{
	UNREFERENCED_PARAMETER(context);
	g_windows_dsim_sock = clientID;
}

void DnD_SOCKETS_HandleDisconnection( SOCKETS_CLIENT_ID clientID, void* context )
{
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(clientID);
	g_windows_dsim_sock = -1;
}


APPSRV_INIT_ST OutputSocketInit(void)
{
	UINT32 port;

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "DND Socket Server enteringStarted!");
	if( SOCKETS_SUCCESS != DND_SERVER_SOCKETS_Init() ) 
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ALERT, "Initialize Failed: DND_SERVER_SOCKETS_Init - Failed!");
		return INIT_FAIL;
	}

	L4Configurations_getDnDOutputPortNum(&port);
	if( SOCKETS_SUCCESS != DND_SERVER_SOCKETS_StartServer( port, NULL, DnD_SOCKETS_HandleNewConnection, DnD_SOCKETS_HandleDisconnection ))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ALERT, "Initialize Failed: DND_SERVER_SOCKETS_StartServer - Failed!");
		return INIT_FAIL;
	}

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "DND Socket Server Started - listening on port %d!", port);

	return INIT_SUCCESS;
}

EXTERN_C EXPORT APPSRV_INIT_ST DnDAgent_Initialize(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn)
{	
	static pDnDOutputInitCB_t	pDnDOutputInitCb;
	APPSRV_INIT_ST				initStatus = INIT_SUCCESS;

	// Set pointer to AppSrv's utility functions
	pUtils = UtilFn;

	// Connect to L5
	pFuncs = L5disp;
	if ((NULL == pFuncs) || 
		(L5_RESULT_OK != pFuncs->pfnConnectEx(L5_TARGET_DND_AGENT, &DnDAgent_MessagesHandler, &DnDAgent_EventHandler, NULL, THREAD_ID_DEFAULT, &nDisTraceConnection )))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "DnD agent is not initiallized - could not connect to the L5 dispatcher");
		return INIT_FAIL;
	}

	// Get the message origin (L4 indications or shared memory)
	L4Configurations_getGetDeviceTraces(&getDeviceTraces);
	
	switch(getDeviceTraces)
	{
	case 2: // 2 means Traces from DnD through nDis Log Data (Shared Memory), with driver attached headers
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO,"The DnD origin was set to - nDis Log Data with driver attached headers");
		msgOrigin = SHARED_MEMORY;
		break;
	case 3: // 3 means Traces from DnD through L4 Indication through AppSrv
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "The DnD origin was set to - L4 Messages via AppSrv");
		msgOrigin = L4_INDICATION;
		break;
	default:
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "The Get Device Traces should be set to 2/4 - Shared Memory or 3 - L4 indication and it was set to: %d", getDeviceTraces);
		return INIT_FAIL;
	}

	L4Configurations_getDnDOutputMode((UINT32*)&dnDOutputMode);

	if (SEND_OVER_SOCKET == dnDOutputMode) 
	{
		pDnDOutputCb = OutputQueueItemToSocket;
		pDnDOutputInitCb = OutputSocketInit;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "Set DnD output to socket");
	}
	else
	{
		dnDOutputMode = DUMP_TO_FILES;
		pDnDOutputCb = WriteQueueItemToFile;
		pDnDOutputInitCb = OutputFileSystemInit;
		TRACE(TR_MOD_ACT, TR_SEV_INFO, "Set DnD output to file system");
	}

	// Initialize output specific parts
	initStatus = pDnDOutputInitCb();
	if (INIT_SUCCESS != initStatus)
	{
		DnDUtils_Finalize();
		FreeAllRecources();
		return initStatus;
	}

	//Initialize the messages Queue
	Queue_Initialize(&sMsgsQ, TRUE);

	//Open killing event
	// Start the writing file thread. This thread reads from the queue and writes the output to the files
	OSAL_create_event(&writeThreadKillEvent, FALSE, FALSE, NULL);
	if (NULL == writeThreadKillEvent)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "DnDAgentInit() failed. Error creating 'writeThreadKillEvent'");
		DnDUtils_Finalize();
		FreeAllRecources();
		return INIT_FAIL;
	}

	// Initialize L4 DnD Handler
	L4DnDHndlr_Init();	

	// Create the Thread that runs the whole show, and start running
	// Ofer f 11.5.07 - The Agent will support both reading from:
	//1. Ndis Log Data (Ndis Shared Memory) - In V2 this should be moved to the KDAPI.
	//2. L4 Indications
	// This is decide according to a Registry Key.
	if (L4_INDICATION == msgOrigin)
	{
		if (FALSE == RegiserOnL4Indications())
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "Initialize Failed: Register on L4 indications - Failed!");
			DnDUtils_Finalize();
			FreeAllRecources();
			return INIT_FAIL;
		}
	}

	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnD agent initiallized succesfully. Target ID=%d", L5_TARGET_DND_AGENT);
	return INIT_SUCCESS;
}

void DnDAgent_InitLogic()
{

}

EXTERN_C EXPORT BOOL DnDAgent_Start()
{
	BOOL status;
	UINT32 ret;

	// if we are working with a real driver with a shared memory (+ headers) - we need to initialize DnDUtils


	// @@@ : 6/11/09 : JSS
	// Linux version also exposes a dedicated trace indications callback from KDAPI so the check below need not be limited to 
	// shared memory version. 
	// However when messages arrive via L4 indications (NOT SHARED MEMORY)then they should not be attempted for parsing inside
	// DnDUtils as they are of different format which kills the parse buffer but instead written to in raw form
	
	// PLEASE SEE MORE COMMENTS ON THIS INSIDE OF DnDUtils_Init method

	if (DnDUtils_IsDriver() /* &&  msgOrigin == SHARED_MEMORY */)
	{
		// DnDUtils thread adds the messages it finds to a Queue and not directly to files. 
		// Later on we have a thread which writes the Queue contents to files.
		status = DnDUtils_Init(AddMessageToQueue, FALSE, pUtils,  (msgOrigin == L4_INDICATION) /* (SEND_OVER_SOCKET == dnDOutputMode) */ );
		if(FALSE == status)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "Initialize Failed: DnDUtils_Init failed!");
			FreeAllRecources();
			return INIT_FAIL;
		}
			
		TRACE(TR_MOD_DND_AGENT, TR_SEV_DEBUG, "After DnDUtils_Init. DnD output mode is %d.", dnDOutputMode);

		DnDUtils_RegisterPostMessage(PostDnDUtilsMonitor);
	}
	
	// enable the file writing if we are working in remote mode
	if (TRUE == DnDUtils_IsRemote())
	{
		isOutputEnabled = TRUE;
	}

	//Start the writing file thread
	ret = OSAL_create_thread(DnD_ThreadWriteFunc, NULL, &sFileWriterThread);

	if ((NULL == sFileWriterThread) || (INVALID_HANDLE_VALUE == sFileWriterThread))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "DnDAgentInit() failed.Error creating file writing thread. sFileWriterThread = %d", sFileWriterThread);
		DnDUtils_Finalize();
		FreeAllRecources();
		return FALSE;
	}

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "DnDAgent started successfully");
	return TRUE;
}

EXTERN_C EXPORT BOOL DnDAgent_Stop()
{
	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnDAgent_Stop(IN)");
	if (L4_INDICATION == msgOrigin)
	{
		UnRegisterOnL4Indications();
	}

	//Signal the thread killing event
	if (NULL != writeThreadKillEvent)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "SetEvent(writeThreadKillEvent)");
		OSAL_set_event(writeThreadKillEvent);
	}

	//Wait until the thread is stopped
	if (NULL != sFileWriterThread)
	{
		//wait till the thread dies:
		switch( OSAL_timedjoin_thread( sFileWriterThread, SHUTDOWN_TIMEOUT, NULL) ) 
		{
		case WAIT_OBJECT_0:			// The thread died
			break;
		case WAIT_TIMEOUT:			//Force stop
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Time Out on stopping the NDis Trace Thread!");
			OSAL_set_event(writeThreadKillEvent);
			OSAL_timedjoin_thread(sFileWriterThread, SHUTDOWN_TIMEOUT, NULL);			
			break;
		default: //WAIT_FAILED
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Wait failed");
			OSAL_set_event(writeThreadKillEvent);
			OSAL_timedjoin_thread(sFileWriterThread, SHUTDOWN_TIMEOUT, NULL);			
			break;
		}
	}

	if (DnDUtils_IsDriver() &&  msgOrigin == SHARED_MEMORY)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "calling DnDUtils_Finalize");
		DnDUtils_Finalize();
	}

	return TRUE;
}
// AppSrv Agent Interface: Shutdown
//void DnDAgent_Shutdown()
EXTERN_C EXPORT void DnDAgent_Finalize()
{ 	
	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnDAgent_Finalize(IN)");

	if (dnDOutputMode == SEND_OVER_SOCKET)
	{
		DND_SERVER_SOCKETS_Fini();
	}

	FreeAllRecources();
	TRACE(TR_MOD_DND_AGENT, TR_SEV_NOTICE, "DnDAgent_Finalize(OUT)");	
}


//*******************************************
// AppSrv Agent Interface: MessagesHandler
//*******************************************
void DnDAgent_MessagesHandler(L5_CONNECTION Conn,
							  L5_TARGET_ID nOriginID,

							  UINT32 dwSentMessageID,
							  void  *pvSentBuffer,
							  UINT32 cbSentBufferSize,

							  UINT32 *pdwResponseMessageID,
							  void  *pvResponseBuffer,
							  UINT32 *cbResponseBufferSize,

							  void *pvUserContext,
							  void *pvReserved )
{
	char* path;
	UINT32 pathLength;
	BOOL success;
	UINT32 result;
	char cPath[MAX_PATH];

	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(Conn);

	switch(dwSentMessageID)
	{
	case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
		if (isOutputEnabled)
		{
			TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Got indication from driver/device. Adding to the queue for processing.");
			result = AddMessageToQueue(pvSentBuffer, cbSentBufferSize);
			if (0 != result)
			{
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Failed to add L4 to queue.");
				*pdwResponseMessageID = WMX_ST_FAIL;
			}
			else
			{
				*pdwResponseMessageID = WMX_ST_OK;
			}
		}
		break;

	case DND_AGENT_OPCODE_SET_PATH:
		OSAL_widechartomultibyte(CP_ACP, 0, (WIMAX_CHAR*)pvSentBuffer, (int)OSAL_wcslen((WIMAX_CHAR*)pvSentBuffer)+2, cPath, MAX_PATH, NULL, NULL);
		//if(SetPathToOutputFiles((char*)pvSentBuffer))
		if(SetPathToOutputFiles(cPath))
		{
			*pdwResponseMessageID = WMX_ST_OK;
		}
		else
		{
			*pdwResponseMessageID = WMX_ST_PIPE_FAILURE;
		}
		break;

	case DND_AGENT_OPCODE_GET_PATH:
		path = GetPathToOutputFiles();
		pathLength = OSAL_strnlen(path, _MAX_PATH) + 1;

		if (*cbResponseBufferSize < pathLength)
		{
			*pdwResponseMessageID = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
			break;
		}

		OSAL_strncpy_s(pvResponseBuffer, *cbResponseBufferSize, path, pathLength);
		*cbResponseBufferSize = pathLength;
		*pdwResponseMessageID = WMX_ST_OK;
		break;

		// enables or disables the file writing thread
	case DND_AGENT_OPCODE_FILE_WRITE:
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "Unrecognized opcode for file writing: State - 1(Enable)/0(Disable)");
		if (FALSE == DnDUtils_IsDsim() || msgOrigin == L4_INDICATION)
		{
			switch (*((char *)pvSentBuffer))
			{
			case ENABLE_THREAD:
				success = EnableFileWritingThread();
				break;

			case DISABLE_THREAD:
				success = DisableFileWritingThread();
				break;

			default:
				TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Unrecognized opcode for file writing: State - 1(Enable)/0(Disable)");
				success = FALSE;
			}
		}
		else
		{
			success = TRUE;
		}

		if (success)
			*pdwResponseMessageID = WMX_ST_OK;
		else
			*pdwResponseMessageID = WMX_ST_FAIL;
		break;

	case DND_AGENT_OPCODE_GET_WRITE_POS:
		success = GetCurrentWritingPosition((UINT8*)pvResponseBuffer, cbResponseBufferSize);

		if(FALSE == success)
		{
			*pdwResponseMessageID = WMX_ST_BUFFER_TOO_SHORT;
		}
		else
		{
			*pdwResponseMessageID = WMX_ST_OK;
		}
		break;

	case DND_AGENT_OPCODE_SET_MON_FILTER:
		success = L4DnDHandlr_SetMonitorFilter(pvSentBuffer, (UINT32)cbSentBufferSize);
		if (FALSE == success)
		{
			*pdwResponseMessageID = WMX_ST_FAIL;
		}
		else
		{
			*pdwResponseMessageID = WMX_ST_OK;
		}
		break;

	case DND_AGENT_OPCODE_GET_MON_FILTER:
		success = L4DnDHandlr_GetMonitorFilter(pvResponseBuffer, (UINT32*)&cbResponseBufferSize);
		if (FALSE == success)
		{
			*pdwResponseMessageID = WMX_ST_FAIL;
		}
		else
		{
			*pdwResponseMessageID = WMX_ST_OK;
		}
		break;

	case DND_AGENT_OPCODE_SET_MON_CONTROL:
		success = TRUE;
		switch (*((char *)pvSentBuffer))
		{
		case MONITOR_ON:
			L4DnDHandlr_SetMonitorControl(TRUE);
			break;

		case DISABLE_THREAD:
			L4DnDHandlr_SetMonitorControl(FALSE);
			break;

		default:
			TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "Unrecognized opcode for Monitor Control: State - 1(On)/0(Off). Received = %d",*((char *)pvSentBuffer) );
			success = FALSE;
		}

		if (success)
			*pdwResponseMessageID = WMX_ST_OK;
		else
			*pdwResponseMessageID = WMX_ST_FAIL;
		break;

	default://OPCODE is not supported
		if (pdwResponseMessageID != NULL)
		{
			*pdwResponseMessageID = WMX_ST_INVALID_OPCODE;
		}  
		break;
	}
}

