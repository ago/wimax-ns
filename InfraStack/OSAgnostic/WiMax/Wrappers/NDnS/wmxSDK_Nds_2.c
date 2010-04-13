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

#include "WrappersUtils.h"
#include "TraceModule.h"


// Obtain the system state
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetSystemState(	wmx_pSystemState_t systemState,
																	wmx_pConnectProgressInfo_t connectProgressInfo,
																	wmx_pRfSwitchesStatus_t rfSwitchesStatus )
{
	wmx_Status_t driver_st = WMX_ST_FAIL, send_st;
	GetState_type getStateCmd;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetSystemState(IN)");

	if( NULL == systemState || NULL == connectProgressInfo || NULL == rfSwitchesStatus )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - nul pointer passed");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	*connectProgressInfo = NotApplicable;

	L4BM_Init_GetState(&getStateCmd);
	
	if (NULL != nds_wrapper_pFuncs)
	{
		send_st = wmx_SendL4Command( &getStateCmd, GetState_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	}
	else
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - nds_wrapper_pFuncs=NULL");
		send_st = WMX_ST_FAIL;
	}

	if( send_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - wmx_SendL4Command returned %d", send_st);
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - wmx_SendL4Command returned driver_st=%d", driver_st);
		return driver_st;
	}

	if( getStateCmd.SystemState.Type == INVALID_OPCODE)
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - getStateCmd.SystemState.Type == INVALID_OPCODE");
		return WMX_ST_DATA_UNAVAILABLE;
	}

	wmxNds_DriverSystemStateToSystemState( systemState, getStateCmd.SystemState.value );
		
	if (getStateCmd.RFStatus.Type == INVALID_OPCODE)
	{
		(*rfSwitchesStatus).hwRfStatus = On;
		(*rfSwitchesStatus).swRfStatus = On;
	}
	else
	{
		wmxNds_DriverRfStatusToRfStatus(&((*rfSwitchesStatus).hwRfStatus), getStateCmd.RFStatus.HwRFSwitch);
		wmxNds_DriverRfStatusToRfStatus(&((*rfSwitchesStatus).swRfStatus), getStateCmd.RFStatus.SwRFSwitch);
	}

	if ( getStateCmd.ConnectProgress.Type != INVALID_OPCODE )
	{
		wmxNds_ConnectProgressInfoTranslation(connectProgressInfo, getStateCmd.ConnectProgress.value);
	}

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetSystemState(OUT). SystemState=%s, ConnectState=%s, swRf=%d, hwRf=%d",
			NDnSSystemStates[*systemState>=UnknownState?UnknownState:*systemState],
			wmxConnectProgressInfoName[*connectProgressInfo>=Registration?NotApplicable:*connectProgressInfo],
			rfSwitchesStatus->swRfStatus, 
			rfSwitchesStatus->hwRfStatus);
	return WMX_ST_OK;
}

//	Obtain the status of the RF function of the WiMAX device
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetRfStatus(	wmx_pRfStatus_t pRfStatus, wmx_pRfSwitchesStatus_t pRfSwitchesStatus ) 
{
	wmx_Status_t driver_st = WMX_ST_FAIL, send_st;
	GetState_type getStateCmd;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetRfStatus(IN)");
	if( NULL == pRfStatus )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}


	L4BM_Init_GetState(&getStateCmd);

	if (NULL != nds_wrapper_pFuncs)
	{
		send_st = wmx_SendL4Command( &getStateCmd, GetState_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	}
	else
	{
		send_st = WMX_ST_FAIL;
	}
	
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	if( getStateCmd.SystemState.Type == INVALID_OPCODE )
	{
		return WMX_ST_DATA_UNAVAILABLE;
	}

	if( ( getStateCmd.SystemState.value == E_SYSTEM_STATE_UNINITIALIZED ) || 
		( getStateCmd.SystemState.value == E_SYSTEM_STATE_INIT ) ||
		( getStateCmd.SystemState.value == E_SYSTEM_STATE_CONFIG) ||
		( getStateCmd.SystemState.value == E_SYSTEM_STATE_RF_OFF) ||
		( getStateCmd.SystemState.value == E_SYSTEM_STATE_RF_SHUTDOWN) )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetRfStatus Off");
		*pRfStatus = Off;
	}
	else
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetRfStatus ON");
		*pRfStatus = On;
	}

	if (getStateCmd.RFStatus.Type == INVALID_OPCODE)
	{
		(*pRfSwitchesStatus).hwRfStatus = On;
		(*pRfSwitchesStatus).swRfStatus = On;
	}
	else
	{
		if (getStateCmd.RFStatus.HwRFSwitch == E_HW_RF_STATUS_ON)
		{
			(*pRfSwitchesStatus).hwRfStatus = On;
		}
		else
		{
			(*pRfSwitchesStatus).hwRfStatus = Off;
		}

		if (getStateCmd.RFStatus.SwRFSwitch == E_SW_RF_STATUS_ON)
		{
			(*pRfSwitchesStatus).swRfStatus = On;
		}
		else
		{
			(*pRfSwitchesStatus).swRfStatus = Off;
		}
	}
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetRfStatus(OUT). RF status=%s, swRfStatus=%d, hwRfStatus=%d",
		(*pRfStatus == On)?"ON":"OFF", getStateCmd.RFStatus.SwRFSwitch, getStateCmd.RFStatus.HwRFSwitch);

	return WMX_ST_OK;
}

// Obtain the status if the media
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetMediaStatus( wmx_pMediaStatus_t pMediaStatus	)
{
	wmx_Status_t driver_st, send_st;
	GetMediaStatus_type getMediaCmd;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetMediaStatus(IN)");

	if( NULL == pMediaStatus )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	L4BM_Init_GetMediaStatus(&getMediaCmd);

	if (NULL != nds_wrapper_pFuncs)
	{
		send_st = wmx_SendL4Command( &getMediaCmd, GetMediaStatus_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	}
	else
	{
		return WMX_ST_FAIL;
	}

	send_st = wmx_SendL4Command( &getMediaCmd, GetMediaStatus_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	if( getMediaCmd.MediaStatus.Type == INVALID_OPCODE )
	{
		return WMX_ST_DATA_UNAVAILABLE;
	}

	if( getMediaCmd.MediaStatus.value == E_MEDIA_STATUS_LINK_UP )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetMediaStatus LinkUp");

		*pMediaStatus = LinkUp;
	}
	else
	{
    
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_GetMediaStatus LinkDown");

		*pMediaStatus = LinkDown;
	}

    
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetMediaStatus(OUT). Media status=%s",*pMediaStatus == LinkUp?"LinkUp":"LinkDown");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectionState( wmx_pConnectionState_t connectionState )
{
	wmx_SystemState_t systemState;
	wmx_ConnectProgressInfo_t connectProgressInfo;
	wmx_RfSwitchesStatus_t rfSwitchesStatus;
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectionState(IN)");

	status = wmx_GetSystemState( &systemState, &connectProgressInfo, &rfSwitchesStatus );
	if ( WMX_ST_OK != status )
	{
		return status;
	}

	wmxNds_SystemStateToConnectionState(connectionState, systemState);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectionState(OUT). state %s)",ConnectionStateName[*connectionState>=UnknownConnectionState?UnknownConnectionState:*connectionState]);

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectionStateUpdateCB( wmx_pConnectionStateUpdateCB_t connectionStateUpdateCB )
{

	wmx_Status_t RC;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterConnectionStateUpdateCB(IN)");
    
    
	if ( NULL != ConnectionStateUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == connectionStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	ConnectionStateUpdateCB = connectionStateUpdateCB;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "registering on driver state report");
	RC = wmx_RegisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterConnectionStateUpdateCB(OUT)");
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectionStateUpdateCB()
{
	wmx_Status_t RC = WMX_ST_FAIL;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterConnectionStateUpdateCB(IN)");
    
    
	if ( NULL == ConnectionStateUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	ConnectionStateUpdateCB = NULL;
	if (NULL != nds_wrapper_pFuncs)
	{
		RC = wmx_UnregisterOnDriverReport( &g_numOfStateReportRegs, L3_L4_OPCODE_REPORT_STATE, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterConnectionStateUpdateCB(OUT)");
	
	return RC;
}
