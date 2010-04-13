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
#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Nds_Utils.h"
#include "wmxSDK_Nds_Cmn.h"

#include "WrappersUtils.h"
#include "L3L4TlvTypes.h"
#include "L4BufMan_L3L4Structs.h"
#include "L4BufMan_L3L4Structs_Desc.h"
#include "FormatConversions.h"
#include "NDnSAgent_Monitor.h"


#include "L4MsgProxyIf.h"
#include "TraceModule.h"
#include "L4ConfigurationManager.h"


// commands
//	Switch on the RF function of the WiMAX device
// Not for any user use!!!
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_InternalRfOn()
{
	wmx_Status_t driver_st, send_st;
	RfControl_type rfCmd;	
	wmx_RfStatus_t rfStatus;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_InternalRfOn called.");		
	

	L4BM_Init_RfControl(&rfCmd);
	rfCmd.RfOperation.Type = L3L4_TLV_TYPE_RF_OPERATION;
	rfCmd.RfOperation.value = E_SW_RF_STATUS_ON;

	send_st = wmx_SendL4Command( &rfCmd, RfControl_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_InternalRfOn (OUT) wimax status=%d driver status=%d", send_st, driver_st);
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}
	rfStatus = On;
	L4db_SetSwRfState(rfStatus);
	return driver_st;
}

//	Switch off the RF function of the WiMAX device
// Not for any user use!!!
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_InternalRfOff()
{
	wmx_Status_t driver_st, send_st;
	RfControl_type rfCmd;
	wmx_RfStatus_t rfStatus;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_InternalRfOff (IN)");

	L4BM_Init_RfControl(&rfCmd);
	rfCmd.RfOperation.Type = L3L4_TLV_TYPE_RF_OPERATION;
	rfCmd.RfOperation.value = E_SW_RF_STATUS_OFF;

	send_st = wmx_SendL4Command( &rfCmd, RfControl_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_InternalRfOff (out). wimax status=%d driver status=%d", send_st, driver_st);
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}
	rfStatus = Off;
	L4db_SetSwRfState(rfStatus);
	return driver_st;
}

// Oran: V3.0 OK
wmx_Status_t wmx_CmdStartScan(wmx_CoexPriority_t coexPriority)
{
	wmx_Status_t driver_st, send_st;
	ScanCommand_type scanCmd;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdStartScan (IN)");
	
	L4BM_Init_ScanCommand( &scanCmd );
	scanCmd.DoScanCommand.Type = L3L4_TLV_TYPE_SCAN_COMMAND;
	scanCmd.DoScanCommand.value = E_SCAN_COMMAND_START;
	scanCmd.CoexPriority.Type = L3L4_TLV_TYPE_COEX_PRIORITY;
	scanCmd.CoexPriority.value = coexPriority;

	send_st = wmx_SendL4Command( &scanCmd, ScanCommand_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdStartScan (OUT)");
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}
	
	return driver_st;	
}

// Oran: V3.0 OK
wmx_Status_t wmx_CmdStopScan()
{
	wmx_Status_t driver_st, send_st;
	ScanCommand_type scanCmd;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdStopScan (IN)");

	L4BM_Init_ScanCommand(&scanCmd);
	scanCmd.DoScanCommand.Type = L3L4_TLV_TYPE_SCAN_COMMAND;
	scanCmd.DoScanCommand.value = E_SCAN_COMMAND_STOP;
	// scanCmd.CoexPriority is optional and not required here (relevant only for wmx_CmdStartScan(...))

	send_st = wmx_SendL4Command( &scanCmd, ScanCommand_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdStopScan (OUT)");
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}

// Get the link status from the driver
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetLinkStatus( wmx_pLinkStatus_t linkStatus	)
{
	wmx_Status_t driver_st, send_st;
	GetLinkStatus_type getLinkStatusCmd;	

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetLinkStatus (IN)");

	if ( NULL == linkStatus )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetLinkStatus - WMX_ST_WRONG_ARGUMENT");
		return WMX_ST_WRONG_ARGUMENT;
	}

	L4BM_Init_GetLinkStatus(&getLinkStatusCmd);

	send_st = wmx_SendL4Command( &getLinkStatusCmd, GetLinkStatus_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	
	if( send_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetLinkStatus send status - %s", wmxGetStatusStr(send_st));
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetLinkStatus driver status - %s", wmxGetStatusStr(driver_st));
		return driver_st;
	}

	if( getLinkStatusCmd.LinkStatus.Type == INVALID_OPCODE )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetLinkStatus - WMX_ST_DATA_UNAVAILABLE");
		return WMX_ST_DATA_UNAVAILABLE;
	}

	linkStatus->cinr = getLinkStatusCmd.LinkStatus.RxCinr;
	linkStatus->frequency = getLinkStatusCmd.LinkStatus.CenterFrequency;
	linkStatus->linkQuality = getLinkStatusCmd.LinkStatus.LinkQuality;
	linkStatus->upLinkSpeed = getLinkStatusCmd.LinkStatus.UpLinkSpeed; 
	linkStatus->downLinkSpeed = getLinkStatusCmd.LinkStatus.DownLinkSpeed; 
	linkStatus->power = getLinkStatusCmd.LinkStatus.TxPower;
	linkStatus->rssi = getLinkStatusCmd.LinkStatus.RxRssi;	
	linkStatus->time = 0;// The driver doesn't return the connection time, AppSrv holds this data instead
	memcpy(linkStatus->bsId, getLinkStatusCmd.LinkStatus.BSID, sizeof(wmx_BSid_t));

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetLinkStatus (OUT)");
	return WMX_ST_OK;
}

// Returns various statistics information regarding traffic.
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetStatistics(wmx_pStatistics_t	pStatistics)																																	
{
	wmx_Status_t driver_st, send_st;
	GetStatistics_type statistics;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetStatistics (IN)");

	L4BM_Init_GetStatistics(&statistics);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_SendL4Command(&statistics) (IN)");
	send_st = wmx_SendL4Command( &statistics, GetStatistics_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	//TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_SendL4Command( &statistics) (OUT), sent_st= %d  , driver_st=%d", send_st, driver_st) );


	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	pStatistics->TotalRxBytes = statistics.StatisticsCommon.TotalRxBytes;
	pStatistics->TotalRxPackets = statistics.StatisticsCommon.TotalRxPackets /*+ statistics.StatisticsCommon.TotalTxPackets*/ ;
	pStatistics->TotalTxBytes = statistics.StatisticsCommon.TotalTxBytes; 
	pStatistics->TotalTxPackets = statistics.StatisticsCommon.TotalTxPackets;
	pStatistics->timeStamp = statistics.TimeStamp.value;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pStatistics->TotalRxBytes %d", pStatistics->TotalRxBytes);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pStatistics->TotalRxPackets %d", pStatistics->TotalRxPackets);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pStatistics->TotalTxBytes %d", pStatistics->TotalTxBytes);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pStatistics->TotalTxPackets %d", pStatistics->TotalTxPackets);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pSattistics->TimeStamp %d",pStatistics->timeStamp);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetStatistics (OUT)");
	return send_st;
}

wmx_Status_t wmx_CmdStartConnect( wmx_BSSelectionCriteria_t bsCriteria, wmx_THCriteria_t thCriteria, wmx_pConnectFlags_t connectFlags, wmx_CoexPriority_t coexPriority, wmx_ConnectionMode_t connectionMode)
{
	wmx_Status_t driver_st, send_st;
	Connect_type connectCmd;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdStartConnect (IN)");
	L4BM_Init_Connect(&connectCmd);
	connectCmd.BSCritieria.Type = L3L4_TLV_TYPE_BS_CRITERIA;
	OSAL_memcpy_s(connectCmd.BSCritieria.BSID_Criterion, sizeof(wmx_BSid_t), bsCriteria.bsID, sizeof(wmx_BSid_t));
	OSAL_memcpy_s(connectCmd.BSCritieria.BSID_Criterion_Mask, sizeof(wmx_BSidMask_t), bsCriteria.bsIDmask, sizeof(wmx_BSidMask_t));
	connectCmd.THCriteria.Type = L3L4_TLV_TYPE_TH_CRITERIA;
	connectCmd.THCriteria.RssiTH = thCriteria.rssiTH;
	connectCmd.THCriteria.CinrTH = thCriteria.cinrTH;

	connectCmd.CoexPriority.Type = L3L4_TLV_TYPE_COEX_PRIORITY;
	connectCmd.CoexPriority.value = coexPriority;
	connectCmd.ConnectFlags.Type = L3L4_TLV_TYPE_CONNECT_FLAGS;
	connectCmd.ConnectFlags.VisitedNspId = connectFlags->visitedNspId;
	connectCmd.ConnectFlags.RequestRealm = connectFlags->requestRealm;
	connectCmd.ConnectFlags.SIQ = connectFlags->SIQ;

	connectCmd.ConnectionMode.Type = L3L4_TLV_TYPE_CONNECTION_MODE;
	connectCmd.ConnectionMode.value = connectionMode;

	send_st = wmx_SendL4Command( &connectCmd, Connect_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdStartConnect (OUT)");
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}

wmx_Status_t wmx_CmdDisconnect()
{
	wmx_Status_t driver_st, send_st;
	Disconnect_type disconnectCmd;
	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdDisconnect (IN)");
	L4BM_Init_Disconnect(&disconnectCmd);

	send_st = wmx_SendL4Command( &disconnectCmd, Disconnect_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdDisconnect (OUT)");
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}

wmx_Status_t wmx_CmdCancelConnect()
{
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdCancelConnect (IN)");
	//TODO: currently calls regular disconnect
	st = wmx_CmdDisconnect();
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdCancelConnect (OUT)");

	return st;
}


// This callback returns all naps aggregated since the beginning of the current scan
wmx_Status_t wmx_RegisterScanUpdateCB( wmx_pScanUpdateCB_t scanUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterScanUpdateCB (IN)");
	if ( NULL != ScanUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == scanUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	ScanUpdateCB = scanUpdateCB;
	st = wmx_RegisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterScanUpdateCB (OUT)");

	return st;
}

wmx_Status_t wmx_UnregisterScanUpdateCB()
{
	wmx_Status_t st;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterScanUpdateCB (IN)");
	if ( NULL == ScanUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	ScanUpdateCB = NULL;
	st = wmx_UnregisterOnDriverReport( &g_numOfScanReportRegs, L3_L4_OPCODE_REPORT_SCAN_RESULT, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterScanUpdateCB (OUT)");

	return st;
}

wmx_Status_t wmx_RegisterMediaStatusCB( wmx_pMediaStatusCB_t mediaStatusCB )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterMediaStatusCB (IN)");
	if ( NULL != MediaStatusCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == mediaStatusCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	MediaStatusCB = mediaStatusCB;

	//////////////////////////////////////////////////////////////////////////
	// No need for registration as we get this status on the system state update report
	//////////////////////////////////////////////////////////////////////////

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterMediaStatusCB (OUT)");

	return WMX_ST_OK;
}

wmx_Status_t wmx_UnregisterMediaStatusCB()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterMediaStatusCB (IN)");

	if ( NULL == MediaStatusCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	MediaStatusCB = NULL;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterMediaStatusCB (OUT)");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterSystemStateUpdateCB( wmx_pSystemStateUpdateCB_t systemStateUpdateCB )
{
	wmx_Status_t st = WMX_ST_OK;
	int location;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_RegisterSystemStateUpdateCB (IN)");

	// find a free location in the CBs array
	for (location = 0; location < SYSTEM_STATE_MAX_CALLBACKS; location++)
	{
		if (SystemStateUpdateCBs[location] == NULL)
		{
			break;
		}
	}
	// no free location found
	if (location == SYSTEM_STATE_MAX_CALLBACKS)
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	/*if ( NULL != SystemStateUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}*/
	if ( NULL == systemStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	++SystemStateUpdateCBs_Count;
	SystemStateUpdateCBs[location] = systemStateUpdateCB;
	if (SystemStateUpdateCBs_Count == FIRST_INIT)
	{
		st = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_RegisterSystemStateUpdateCB (OUT). SystemStateUpdateCBs_Count=%d", SystemStateUpdateCBs_Count);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterAllSystemStateUpdateCBs()
{
	wmx_Status_t st = WMX_ST_OK;
	int location;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterAllSystemStateUpdateCBs (IN)");

	for (location = 0; location < SYSTEM_STATE_MAX_CALLBACKS; location++)
	{
		if(SystemStateUpdateCBs[location] != NULL)
		{
			break;
		}
	}
	
	if (location < SYSTEM_STATE_MAX_CALLBACKS) // found registered callbacks, so de-register on the driver report
	{
		st = wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}
	memset(SystemStateUpdateCBs, 0, (sizeof(wmx_pSystemStateUpdateCB_t) * SYSTEM_STATE_MAX_CALLBACKS));
	SystemStateUpdateCBs_Count = 0;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterAllSystemStateUpdateCBs (OUT)");

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterSystemStateUpdateCB(wmx_pSystemStateUpdateCB_t systemStateUpdateCB)
{
	wmx_Status_t st = WMX_ST_OK;
	int location;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterSystemStateUpdateCB (IN)");

	for (location = 0; location < SYSTEM_STATE_MAX_CALLBACKS; location++)
	{
		if(SystemStateUpdateCBs[location] == systemStateUpdateCB)
		{
			break;
		}
	}

	//if ( NULL == SystemStateUpdateCB )
	if (location == SYSTEM_STATE_MAX_CALLBACKS)	
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	--SystemStateUpdateCBs_Count;
	SystemStateUpdateCBs[location] = NULL;

	if (SystemStateUpdateCBs_Count == LAST_INIT)
	{
		st = wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterSystemStateUpdateCB (OUT)");

	return st;
}

////////////////////////////
// This callback returns the full bsid and the nsp change count
wmx_Status_t wmx_RegisterBsInfoUpdateCB( wmx_pBsInfoUpdateCB_t bsInfoUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterBsInfoUpdateCB (IN)");
	if ( NULL != BsInfoUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == bsInfoUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	BsInfoUpdateCB = bsInfoUpdateCB;	

	st = wmx_RegisterOnDriverReport( &g_numOfBsInfoReportRegs, L3_L4_OPCODE_REPORT_BS_INFO, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterBsInfoUpdateCB (OUT)");

	return st;
}


wmx_Status_t wmx_UnregisterBsInfoUpdateCB()
{
	wmx_Status_t st;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterBsInfoUpdateCB (IN)");
	if ( NULL == BsInfoUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	BsInfoUpdateCB = NULL;	
	st = wmx_UnregisterOnDriverReport( &g_numOfBsInfoReportRegs, L3_L4_OPCODE_REPORT_BS_INFO, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterBsInfoUpdateCB (OUT)");

	return st;
}

////////////////////////////
// This callback returns the channels of the SBS and the neighbor BSs
wmx_Status_t wmx_RegisterRecentBSsCB( wmx_pRecentBSsCB_t recentBSsCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterRecentBsCB (IN)");
	if ( NULL != RecentBSsCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == recentBSsCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	RecentBSsCB = recentBSsCB;	

	st = wmx_RegisterOnDriverReport( &g_numOfRecentBSsReportRegs, L3_L4_OPCODE_REPORT_RECENT_BS, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterRecentBsCB (OUT)");

	return st;
}

wmx_Status_t wmx_UnregisterRecentBSsCB()
{
	wmx_Status_t st;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterRecentBsCB (IN)");
	if ( NULL == RecentBSsCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	RecentBSsCB = NULL;	
	st = wmx_UnregisterOnDriverReport( &g_numOfRecentBSsReportRegs, L3_L4_OPCODE_REPORT_RECENT_BS, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterRecentBsCB (OUT)");

	return st;
}

// This callback returns the sii information
wmx_Status_t wmx_RegisterSIIUpdateCB( wmx_pSIIUpdateCB_t siiUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterSIIUpdateCB (IN)");
	if ( NULL != SIIUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == siiUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	SIIUpdateCB = siiUpdateCB;
	st = wmx_RegisterOnDriverReport( &g_numOfSIIReportRegs, L3_L4_OPCODE_REPORT_SII, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterSIIUpdateCB (OUT)");

	return st;
}

wmx_Status_t wmx_UnregisterSIIUpdateCB()
{
	wmx_Status_t st;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterSIIUpdateCB (IN)");
	if ( NULL == SIIUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	SIIUpdateCB = NULL;
	st = wmx_UnregisterOnDriverReport( &g_numOfSIIReportRegs, L3_L4_OPCODE_REPORT_SII, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterSIIUpdateCB (OUT)");

	return st;
}
////////////////////

wmx_Status_t wmx_RegisterBEKBufferCB( wmx_pBekBufferCB_t pBekBufferCB)
{
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterBEKBufferCB (IN)");
	if ( NULL != BekBufferCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == pBekBufferCB )
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	BekBufferCB = pBekBufferCB;
	st = wmx_RegisterOnDriverReport( &g_numOfBEKStatusIndRegs, L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_RegisterBEKBufferCB (OUT)");

	return st;
}

wmx_Status_t wmx_UnregisterBEKBufferCB()
{
	wmx_Status_t st;
	
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterBEKBufferCB (IN)");
	if ( NULL == BekBufferCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	BekBufferCB = NULL;
	st = wmx_UnregisterOnDriverReport( &g_numOfBEKStatusIndRegs, L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_UnregisterBEKBufferCB (OUT)");

	return st;
}

// getters
wmx_Status_t wmx_GetConnectedNAP( wmx_pNAP_t connectedNAP )
{
	wmx_Status_t driver_st, send_st;
	GetLinkStatus_type getLinkStatusCmd;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetConnectedNAP (IN)");

	if ( NULL == connectedNAP )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	L4BM_Init_GetLinkStatus(&getLinkStatusCmd);

	send_st = wmx_SendL4Command( &getLinkStatusCmd, GetLinkStatus_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	if( getLinkStatusCmd.LinkStatus.Type == INVALID_OPCODE )
	{
		return WMX_ST_DATA_UNAVAILABLE;
	}

	connectedNAP->bestRssi = getLinkStatusCmd.LinkStatus.RxRssi;
	connectedNAP->bestCINR = getLinkStatusCmd.LinkStatus.RxCinr;
	connectedNAP->bestLinkQuality = getLinkStatusCmd.LinkStatus.LinkQuality;
	OSAL_memcpy_s(connectedNAP->bsCriteria.bsID, sizeof(wmx_BSid_t), getLinkStatusCmd.LinkStatus.BSID, sizeof(wmx_BSid_t));

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetConnectedNAP (OUT)");
	return WMX_ST_OK;
}

//// TODO: Oran - fix the scan results based on the new BM
//wmx_Status_t wmx_GetLastKnownNAPs( UINT32* pNumOfNaps, wmx_pNAP_t pNaps )
//{
//	wmx_Status_t driver_st, send_st;
//	GetScanResults_type getScanResults;
//	UINT32 i = 0;
//
//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetLastKnownNAPs (IN)");
//
//	if ( (NULL == pNaps) || (NULL == pNumOfNaps) )
//	{
//		return WMX_ST_ILLEGAL_OPERATION;
//	}
//
//	L4BM_Init_GetScanResults(&getScanResults);
//
//	send_st = wmx_SendL4Command( &getScanResults, GetScanResults_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
//	if( send_st != WMX_ST_OK )
//	{
//		return send_st;
//	}
//
//	if( driver_st != WMX_ST_OK )
//	{
//		return driver_st;
//	}
//
//	while( ( INVALID_OPCODE != getScanResults.ScanResultList_Get[i].Type ) && ( i < *pNumOfNaps ) )
//	{
//		pNaps[i].bestRssi = getScanResults.ScanResultList_Get[i].BestRssi;
//		pNaps[i].bestCINR = getScanResults.ScanResultList_Get[i].BestCINR;
//		pNaps[i].numChannels = getScanResults.ScanResultList_Get[i].NumOfLinks;
//		OSAL_memcpy_s(pNaps[i].bsCriteria.bsID, sizeof(wmx_BSid_t), getScanResults.ScanResultList_Get[i].NetworkId, sizeof(wmx_BSid_t));
//
//		i++;
//	}
//	*pNumOfNaps = i;
//
//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetLastKnownNAPs (OUT)");
//
//	return WMX_ST_OK;
//}

// Oran: V3.0 OK
// setters
wmx_Status_t wmx_SetChannelPlan( UINT32 numOfChannelInfos, wmx_pChannelInfo_t channelInfos, wmx_ScanPolicy_t scanPolicy )
{
	wmx_Status_t driver_st, send_st, monitorStatus;
	SetScanParameters_type scanParametersCmd;
	UINT32 i = 0;
	char buff[MAX_STR_LEN];


	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_SetChannelPlan (IN) set %d channels", numOfChannelInfos);

	L4BM_Init_SetScanParameters(&scanParametersCmd);	
	for ( i = 0; i < numOfChannelInfos; i++ )
	{
		ConvertPreamblesBitmapToStr(channelInfos[i].preambleBitmap, buff);
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Channel %d channel ID - %d, frequency - %d, bandwidth - %d, fft - %d, preambles - %s", numOfChannelInfos, 
																				channelInfos[i].channelID,
																				channelInfos[i].frequency,
																				channelInfos[i].bw,
																				channelInfos[i].fft,
																				buff);
		scanParametersCmd.ChannelInfoArray[i].Type = L3L4_TLV_TYPE_CHANNEL_INFO;
		scanParametersCmd.ChannelInfoArray[i].ChannelId = channelInfos[i].channelID;
		scanParametersCmd.ChannelInfoArray[i].Frequency = channelInfos[i].frequency;
		scanParametersCmd.ChannelInfoArray[i].Bandwidth = channelInfos[i].bw;
		scanParametersCmd.ChannelInfoArray[i].Fft = channelInfos[i].fft;
		OSAL_memcpy_s(scanParametersCmd.ChannelInfoArray[i].Preambles, sizeof(wmx_Preambles_t), channelInfos[i].preambleBitmap, sizeof(wmx_Preambles_t));
	}
	monitorStatus = wmx_PopulateMoniterScanConfig( scanParametersCmd.ChannelInfoArray,  numOfChannelInfos);
	
	scanParametersCmd.ScanPolicy.Type = L3L4_TLV_TYPE_SCAN_POLICY;
	scanParametersCmd.ScanPolicy.value = (UINT32)scanPolicy;

	send_st = wmx_SendL4Command( &scanParametersCmd, SetScanParameters_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_SetChannelPlan (OUT) wimax status - %d, driver status - %d", send_st, driver_st);
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}


// Get the SP Lock status from the driver
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetSpLockStatus(wmx_pSpLock_t pSpLockStatus)
{
	wmx_Status_t driver_st, send_st;
	SPLockStatusInfo_type getSpLockCmd;	

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetSpLockStatus (IN)");

	memset(pSpLockStatus, 0, sizeof(*pSpLockStatus));

	L4BM_Init_SPLockStatusInfo(&getSpLockCmd);

	send_st = wmx_SendL4Command( &getSpLockCmd, SPLockStatusInfo_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );

	if( send_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetSpLockStatus send status - %s", wmxGetStatusStr(send_st));
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetSpLockStatus driver status - %s", wmxGetStatusStr(driver_st));
		return driver_st;
	}

	if(getSpLockCmd.SPLockStatus.value != E_SP_LOCK_STATUS_LOCKED && getSpLockCmd.SPLockStatus.value != E_SP_LOCK_STATUS_UNLOCKED)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "wmx_GetSpLockStatus - WMX_ST_DATA_UNAVAILABLE");
		return WMX_ST_DATA_UNAVAILABLE;
	}

	if( getSpLockCmd.SPLockStatus.value == E_SP_LOCK_STATUS_LOCKED )
	{
		pSpLockStatus->NSPNameActualLen = getSpLockCmd.LockedToNSPNameInfo.ActualLen;
		memcpy(pSpLockStatus->NSPNameBuff, getSpLockCmd.LockedToNSPNameInfo.BufferArr, pSpLockStatus->NSPNameActualLen);
	}

	pSpLockStatus->sPLockStatus = getSpLockCmd.SPLockStatus.value;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetSpLockStatus (OUT) driver status =%d, wimax status=%d", 
		driver_st, send_st);
	return WMX_ST_OK;
}

// Set the SP Lock status to LOCKED in the driver
wmx_Status_t wmx_CmdSpLockUnLock(wmx_SpLockCode_t SpLockCode)
{
	wmx_Status_t driver_st, send_st;
	// wmx_SPLockStatus_t SPLockStatus;
	SPLockRequest_type SPLockCmd;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdTrueSpLock (IN)");

	L4BM_Init_SPLockRequest(&SPLockCmd);

	// This is a define for testing purpose only. If you define in the bitman the 
	// necessary fields you can "play" with device logic.
	#if defined(BM_SPLockRequest_List_CURRENT_SPLockStatusReq_GET_BYTES_SIZE)
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdSpLockUnLock Debug flag BM_SPLockRequest_List_CURRENT_SPLockStatusReq_GET_BYTES_SIZE defined");
		SPLockCmd.SPLockStatusReq.Type = L3L4_TLV_TYPE_SP_LOCK_STATUS;
		SPLockCmd.SPLockStatusReq.value = SpLockCode.Reserved ? E_SP_LOCK_STATUS_LOCKED : E_SP_LOCK_STATUS_UNLOCKED;
	#endif
	
	SPLockCmd.SPLockUnlockCodeReq.Type = L3L4_TLV_TYPE_SP_LOCK_UNLOCK_CODE;
	SPLockCmd.SPLockUnlockCodeReq.ActualLen = SpLockCode.ActualLen;
	OSAL_memcpy_s(SPLockCmd.SPLockUnlockCodeReq.BufferArr, OSAL_strnlen((char *)SpLockCode.BufferArr, MAX_SP_LOCK_CODE_SIZE), 
		SpLockCode.BufferArr, OSAL_strnlen((char *)SpLockCode.BufferArr, MAX_SP_LOCK_CODE_SIZE));

	send_st = wmx_SendL4Command( &SPLockCmd, SPLockRequest_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdSpLockUnLock (OUT) driver status =%d, wimax status=%d", 
		driver_st, send_st);

	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}
