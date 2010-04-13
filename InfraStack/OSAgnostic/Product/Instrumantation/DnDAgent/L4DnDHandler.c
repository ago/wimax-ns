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
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"
#include "wimax_osal_types.h"

#include "L4DnDHandler.h"
#include "L4DnDHandler_Internal.h"
#include "DnDAgent_Internal.h"
#include "TraceModule.h"
#include "L3L4CommonDefines.h"
#include "L4BufMan_L4Common.h"
#include "L4DnDMonitorHeader.h"
#include "MonitorGeneral.h"
#include "TraceSubSystem.h"
#include "time.h"
#include "L5Common.h"	



//#define TIMESTAMP_LENGTH 8
//#define L4_DND_HEADER_LENGTH HEADER_SIZE + SIZE_OF_TYPE_LENGTH + BM_L4DnDMonitorHeader_HostTimestamp_BYTES_SIZE
//static UINT8 monHeader[HEADER_SIZE + SIZE_OF_TYPE_LENGTH + TIMESTAMP_LENGTH];
static UINT8 monHeader[BM_L4DnDMonitorHeader_BYTES_SIZE];
static UINT8 traceHeader[BM_L4DnDMonitorHeader_BYTES_SIZE];
static UINT8 timeStamp[BM_L4DnDMonitorHeader_HostTimestamp_BYTES_SIZE];
static UINT8 monitorFilterTable[MONITOR_FILTER_TABLE_SIZE];
static BOOL isMonitorOn = FALSE;
static BOOL isInitialized = FALSE;

static OSAL_critical_section csWriteProt;
static OSAL_critical_section csFilterTable;

extern tUtilityFunctions *pUtils;

void UpdateHeader(UINT8* header, UINT16 type, UINT16 length)
{
	SYSTEMTIME timeInfo;
	//Updating Header's length (The length of the buffer is: Type(2) + Length(2) + Timestamp(8) + Length from user
	L4BM_SetLength(header, length + SIZE_OF_TYPE_LENGTH + BM_L4DnDMonitorHeader_HostTimestamp_BYTES_SIZE);

	//Set the TLV type
	BM_L4DnDMonitorHeader_GenericTlv_Generic_Type_SET(header, type);

	//Set the TLV length
	BM_L4DnDMonitorHeader_GenericTlv_Generic_Length_SET(header, length + BM_L4DnDMonitorHeader_HostTimestamp_BYTES_SIZE);

	//Calculate the Timestamp and write it
	OSAL_GetLocalTime(&timeInfo);

	BM_L4DnDMonitorHeader_HostTimestamp_Hour_SET(header, (UINT8)timeInfo.wYear);
	BM_L4DnDMonitorHeader_HostTimestamp_Hour_SET(header, (UINT8)timeInfo.wMonth);
	BM_L4DnDMonitorHeader_HostTimestamp_Hour_SET(header, (UINT8)timeInfo.wDay);
	BM_L4DnDMonitorHeader_HostTimestamp_Hour_SET(header, (UINT8)timeInfo.wHour);
	BM_L4DnDMonitorHeader_HostTimestamp_Minute_SET(header, (UINT8)timeInfo.wMinute);
	BM_L4DnDMonitorHeader_HostTimestamp_Second_SET(header, (UINT8)timeInfo.wSecond);
	BM_L4DnDMonitorHeader_HostTimestamp_Res_SET(header, 0);
		
}

void UpdateTraceHeader(UINT16 type, UINT16 length)
{
	UNREFERENCED_PARAMETER(type);
	UNREFERENCED_PARAMETER(length);
	//UpdateHeader(traceHeader, type, length);
	//BM_L4DnDTraceHeader_SubSystemId_SET(traceHeader, L4_SUB_SYS_ID);
	//BM_L4DnDTraceHeader_Signature_SET(traceHeader, 0);
}

void L4DnDHndlr_Init()
{
	L4BM_SetOpcode(monHeader, L3_L4_OPCODE_REPORT_MONITOR_EVACUATE);
	L4BM_SetVersion(monHeader, HEADER_VERSION);
	L4BM_SetAccessibility(monHeader, HEADER_ACCESSIBILITY);
	L4BM_SetStatus(monHeader, HEADER_STATUS);

	OSAL_init_critical_section(&csWriteProt);
	OSAL_init_critical_section(&csFilterTable);

	OSAL_enter_critical_section(&csFilterTable);
	memset(monitorFilterTable, 0, MONITOR_FILTER_TABLE_SIZE);
	OSAL_exit_critical_section(&csFilterTable);

	isInitialized = TRUE;
}

void L4DnDHandlr_Finalize()
{
	isInitialized = FALSE;
	isMonitorOn = FALSE;

	OSAL_delete_critical_section(&csWriteProt);
	OSAL_delete_critical_section(&csFilterTable);
}

BOOL L4DnDHandlr_SetMonitorFilter(UINT8* buff, UINT32 length)
{
	if (FALSE == isInitialized)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[L4DnDHandlr_SetMonitorFilter]: L4DnDMonitorHandler is not initialized");
		return FALSE;
	}

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHandlr_SetMonitorFilter]: Start");
	if (length != MONITOR_FILTER_TABLE_SIZE)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHandlr_SetMonitorFilter]: length of Monitor Filter is invalid. length received = %d. length expected = %d", length, MONITOR_FILTER_TABLE_SIZE);
		return FALSE;
	}

	if (NULL == buff)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHandlr_SetMonitorFilter]: Buffer is NUL");
		return FALSE;
	}

	OSAL_enter_critical_section(&csFilterTable);
	OSAL_memcpy_s(monitorFilterTable, length, buff, length);
	OSAL_exit_critical_section(&csFilterTable);

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHandlr_SetMonitorFilter]: Finished successfully");
	return TRUE;
}

BOOL L4DnDHandlr_GetMonitorFilter(UINT8* buff, UINT32* length)
{
	if (FALSE == isInitialized)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[L4DnDHandlr_GetMonitorFilter]: L4DnDMonitorHandler is not initialized");
		return FALSE;
	}

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHandlr_GetMonitorFilter]: Start");
	if (*length < MONITOR_FILTER_TABLE_SIZE)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHandlr_GetMonitorFilter]: length of Monitor Filter is too short. length received = %d. length expected = %d", *length, MONITOR_FILTER_TABLE_SIZE);
		return FALSE;
	}

	if (NULL == buff)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHandlr_GetMonitorFilter]: Buffer is NUL");
		return FALSE;
	}

	*length = MONITOR_FILTER_TABLE_SIZE;

	OSAL_enter_critical_section(&csFilterTable);
	OSAL_memcpy_s(buff, MONITOR_FILTER_TABLE_SIZE, monitorFilterTable, MONITOR_FILTER_TABLE_SIZE);
	OSAL_exit_critical_section(&csFilterTable);

	TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHandlr_GetMonitorFilter]: Finished successfully");
	return TRUE;
}

BOOL L4DnDHndlr_IsMonFiltered(UINT16 type)
{
	BOOL res;

	if (FALSE == isInitialized)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[L4DnDHndlr_IsMonFiltered]: L4 DnD Monitor Handler is not initialized yet");		
		return FALSE;
	}

	if (FALSE == isMonitorOn)
	{
		return FALSE;
	}

	if (type < MONITOR_FIRST_FILTER_TYPE || type >=  MONITOR_FIRST_FILTER_TYPE + MONITOR_FILTER_TABLE_SIZE)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHndlr_IsMonFiltered]: Type supplied is invalid. type = %d. type range is ");		
		return FALSE;
	}

	//TODO: This should be changed when we will support periodic monitors.
	//For now we returned TRUE if the value is larger than zero
	OSAL_enter_critical_section(&csFilterTable);
	res = (monitorFilterTable[type - MONITOR_FIRST_FILTER_TYPE] > 0);
	OSAL_exit_critical_section(&csFilterTable);

	return res;
}

void L4DnDHandlr_SetMonitorControl(BOOL setToOn)
{
	isMonitorOn = setToOn;
}
BOOL L4DnDHndlr_PostMon(UINT8* buffer, UINT16 type, UINT16 length)
{
	int res;
	//Assert correct params
	if (FALSE == isInitialized)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_WARNING, "[L4DnDHndlr_PostMon]: L4 DnD Monitor Handler is not initialized yet");		
		return FALSE;
	}

	if (length == 0)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHndlr_PostMon]: Length is 0 - illegal. ");
		return FALSE;
	}

	if (NULL == buffer)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHndlr_PostMon]: Buffer is NULL - illegal. ");
		return FALSE;
	}

	//Check if this type is requested
	if (FALSE == L4DnDHndlr_IsMonFiltered(type))
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHndlr_PostMon]: Type = %d isn't filtered on. Not reporting");
		return TRUE;
	}

	//Lock this part.
	OSAL_enter_critical_section(&csWriteProt);

	//Update the header with correct params
	UpdateHeader(monHeader, type, length);

	//Add message to queue
	res = AddMessageAndHeaderToQueue(monHeader, BM_L4DnDMonitorHeader_BYTES_SIZE, buffer, length);

	//Unlock
	OSAL_exit_critical_section(&csWriteProt);

	if (res != 0)
	{
		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHndlr_PostMon]: Failed to add message to queue");
		return FALSE;
	}

	return TRUE;
}
//BOOL L4DnDHndlr_PostTrace(UINT8* buffer, UINT16 length)
//{
//	int res;
//	UINT16 type = L3L4_TLV_TYPE_TRACE_EVACUATE;
//	//Assert correct params
//	if (length == 0)
//	{
//		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHndlr_PostTrace]: Length is 0 - illegal. ");
//		return FALSE;
//	}
//
//	if (NULL == buffer)
//	{
//		TRACE(TR_MOD_DND_AGENT, TR_SEV_ERR, "[L4DnDHndlr_PostTrace]: Buffer is NULL - illegal. ");
//		return FALSE;
//	}
//
//	//Lock this part.
//	OSAL_enter_critical_section(&csWriteProt);
//
//	//Update the header with correct params
//	UpdateTraceHeader(type, length);
//
//	//Add message to queue
//	res = AddMessageAndHeaderToQueue(monHeader, BM_L4DnDTraceHeader_BYTES_SIZE, buffer, length);
//	
//	//Unlock
//	OSAL_exit_critical_section(&csWriteProt);
//	
//	if (res != 0)
//	{
//		TRACE(TR_MOD_DND_AGENT, TR_SEV_INFO, "[L4DnDHndlr_PostTrace]: Failed to add message to queue");
//		return FALSE;
//	}
//
//	return TRUE;
//}
