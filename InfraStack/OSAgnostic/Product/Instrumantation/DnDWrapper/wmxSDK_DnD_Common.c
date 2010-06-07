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
#include "wmxSDK_DnD_Common.h"

#include "MonitorGeneral.h"
#include "L3L4CommonDefines.h"
#include "L4BufMan_L3L4Structs.h"
#include "WrappersUtils.h"

wmx_Status_t DeviceMonitorOnControl(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs)
{
	CmdMonitorControl_type monControl;
	wmx_Status_t resReceived;
	wmx_Status_t sStatus;

	L4BM_Init_CmdMonitorControl(&monControl);
	monControl.MonitorMode.Type = L3L4_TLV_TYPE_MONITOR_CONTROL; 
	monControl.MonitorMode.value = E_MONITOR_CONTROL_ON;

	sStatus = wmx_SendL4Command(&monControl,
		CmdMonitorControl_Funcs,
		*sL5DispatcherFuncs,
		sL5Conn,
		&resReceived);

	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Send Monitor ON L4 - failed");
		return sStatus;
	}

	if (WMX_ST_OK != resReceived)
	{
		TRACE_ERR( "Response to Send Monitor ON L4 - failed. Returned value is: %d", resReceived);
		return resReceived;
	}

	return sStatus;
}
wmx_Status_t DeviceMonitorOffControl(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs)
{
	CmdMonitorControl_type monControl;
	wmx_Status_t resReceived;
	wmx_Status_t sStatus;

	L4BM_Init_CmdMonitorControl(&monControl);
	monControl.MonitorMode.Type = L3L4_TLV_TYPE_MONITOR_CONTROL; 
	monControl.MonitorMode.value = E_MONITOR_CONTROL_OFF;

	sStatus = wmx_SendL4Command(&monControl,
		CmdMonitorControl_Funcs,
		*sL5DispatcherFuncs,
		sL5Conn,
		&resReceived);

	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Send Monitor OFF L4 - failed");
		return sStatus;
	}

	if (WMX_ST_OK != resReceived)
	{
		TRACE_ERR( "Response to Send Monitor OFF L4 - failed. Returned value is: %d", resReceived);
		return resReceived;
	}

	return sStatus;
}
wmx_Status_t DeviceSetMonitorFilter(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs, char * pMonitorFilterBuff, UINT32 nMonitorFilterBuffSize)
{
	SetMonitorFilterTable_type monSetFilter;
	wmx_Status_t resReceived;
	wmx_Status_t sStatus;;

	L4BM_Init_SetMonitorFilterTable(&monSetFilter);
	monSetFilter.MonitorFilterTable.Type = L3L4_TLV_TYPE_MONITOR_FILTER_TABLE; 
	memcpy(&monSetFilter.MonitorFilterTable.FilterTable, pMonitorFilterBuff, nMonitorFilterBuffSize);

	sStatus = wmx_SendL4Command(	&monSetFilter,
		SetMonitorFilterTable_Funcs,
		*sL5DispatcherFuncs,
		sL5Conn,
		&resReceived);

	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Send SetMonitorFilter L4 - failed");
		return sStatus;
	}

	if (WMX_ST_OK != resReceived)
	{
		TRACE_ERR( "Response to Send Monitor ON L4 - failed. Returned value is: %d", resReceived);
		return resReceived;
	}

	return sStatus;
}


wmx_Status_t DeviceSetTraceFilter(L5_CONNECTION sL5Conn, tL5DispatcherFunctions* sL5DispatcherFuncs, char * pTraceFilterBuff, UINT32 nTraceFilterBuffSize)
{
	wmx_Status_t sStatus;
	SetTraceSeverityTable_type trcSetFilter;
	wmx_Status_t resReceived;


	if (nTraceFilterBuffSize != TRACE_SEVERITIES_TABLE_SIZE)
	{
		TRACE_ERR("The trace severity table should be: %d and not %d", TRACE_SEVERITIES_TABLE_SIZE, nTraceFilterBuffSize);
		return WMX_ST_WRONG_ARGUMENT;
	}

	L4BM_Init_SetTraceSeverityTable(&trcSetFilter);
	trcSetFilter.TraceSeverityTable.Type = L3L4_TLV_TYPE_TRACE_SEVERITY_TABLE; 
	memcpy(&trcSetFilter.TraceSeverityTable.SeverityTable, pTraceFilterBuff, nTraceFilterBuffSize);

	sStatus = wmx_SendL4Command(	&trcSetFilter,
		SetTraceSeverityTable_Funcs,
		*sL5DispatcherFuncs,
		sL5Conn,
		&resReceived);

	if (WMX_ST_OK != sStatus)
	{
		TRACE_ERR("Send SetTraceFilter L4 - failed");
		return sStatus;
	}

	if (WMX_ST_OK != resReceived)
	{
		TRACE_ERR( "Response to SetTraceFilter ON L4 - failed. Returned value is: %d", resReceived);
		return resReceived;
	}
	return sStatus;
}
