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
#include "WrappersCommon.h"
#include "L4BufMan_L3L4Structs_Desc.h"
#include "wmxSDK_Coex_1.h"
#include "WrappersUtils.h"	
#include "wmxSDK_Nds_Internals.h"
#include "NDnS_Coex.h"
#include "NDnSAgent_Internals.h"
#include "NDnSAgent.h"
#include "wmxSDK_Nds_3.h"
#include "NDnS_Coex.h"


BOOL UserCall = TRUE;
void NDnSAgent_CoexistenceUpdate( wmx_CoexistenceMode_t coexMode );
wmx_CoexistenceMode_t initialCoexMode = WMX_MODE_XOR;
OSAL_thread_t act_thread_coexHandler;

wmx_Status_t wmx_SetCoexistenceMode(wmx_CoexistenceMode_t coexMode)
{
	wmx_Status_t driver_st, send_st;
	SetCoexMode_type coexistanceMode;
	BOOL regData;
	wmx_Status_t retStatus = WMX_ST_FAIL;
//	wmx_UserConnectMode_t connectMode = UserManScanManConnect;
	UINT32 value = 0;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Now in wmx_SetCoexistenceMode function !");
	
	if (coexMode != WMX_MODE_XOR && coexMode != WMX_MODE_CM)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_ERR, "Coex mode not of a valid value !!!");
		return WMX_ST_FAIL;
	}
	if (coexMode == initialCoexMode){
		if (coexMode == WMX_MODE_CM && UserCall){
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetCoexistanceMode recieved set CM mode in CM mode.");
			if (act_thread_coexHandler!=NULL){
				OSAL_kill_thread(&act_thread_coexHandler);
				retStatus = WMX_ST_OK;
			}
			// setting fall to xor key to zero so we never fall to xor even when driver falls and brings itself up
			regData = OSAL_ConfigController_SetNumValue(OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COEXISTING_TIMEOUT, &value);
			if (!regData)
			{
				retStatus = WMX_ST_FAIL;
			}
		}
	}else {
		if (coexMode == WMX_MODE_CM){
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetCoexistanceMode recieved set CM mode in XOR mode.");
			OSAL_create_thread(NDnSAgent_CoexHandlingThreadFunc, NULL, &act_thread_coexHandler) ;
			//DISABLE ALL CU GUI ??

			//Disable AutoConnectMode
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Disabling AutoConnectMode, setting conect mode to UserManScanManConnect");
			//SetConnectMode(&connectMode,sizeof(wmx_UserConnectMode_t));

		}else {
			//connectMode = UserSemiManScanManConnect;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "SetCoexistanceMode recieved set XOR mode in CM mode.");
			// setting connection mode to last known connection mode
			//SetConnectMode(&connectMode, sizeof(wmx_UserConnectMode_t));
		}
		//send indication only when changed from initial coex mode
		NDnSAgent_CoexistenceUpdate(coexMode);
	}
	

	
	if (UserCall)
		initialCoexMode = coexMode;
	// will set 
	if (retStatus != WMX_ST_OK ){
		
		//update coexsitence registry
		regData = OSAL_ConfigController_SetStrValue(OSAL_KEY_ENTRY_PIPECONFIG, OSAL_KEY_ENTRY_COEXISTING_MODE, ((initialCoexMode) == WMX_MODE_XOR)?"XOR":"CM");
		if (!regData)
		{
			return WMX_ST_FAIL;
		}
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Coexistance mode set to - %s",(initialCoexMode)==WMX_MODE_CM?"CM":"XOR");
	}
	
	L4BM_Init_SetCoexMode(&coexistanceMode);
	coexistanceMode.CoexistenceModeType.Type = L3L4_TLV_TYPE_COEXISTENCE_MODE;
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Coexistance mode set to - %s",(initialCoexMode)==WMX_MODE_CM?"CM":"XOR");
	if(initialCoexMode == WMX_MODE_CM)
		coexistanceMode.CoexistenceModeType.value = (UINT32)(E_COEXISTENCE_MODE_CM);
	else
		coexistanceMode.CoexistenceModeType.value = (UINT32)(E_COEXISTENCE_MODE_XOR);
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "Sending Coexistance mode to driver and setting it to - %s",(initialCoexMode)==WMX_MODE_CM?"CM":"XOR");
	send_st = wmx_SendL4Command( &coexistanceMode, SetCoexMode_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );

	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "wmx_SetCoexistenceMode User call set to true");
	UserCall = TRUE;
	if( send_st != WMX_ST_OK )

	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "wmx_SetCoexistenceMode was not sent succesfully to the device");
		return send_st;
	}
	TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE, "wmx_SetCoexistenceMode was sent succesfully to the device");
	
	return driver_st;
}

wmx_Status_t wmx_CmdProcessStart(wmx_CoexState_t coexState)
{
	wmx_Status_t driver_st, send_st;
	CmdCoexProcessStart_type processStartCmdParams;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdProcessStart (IN) with coex state=%d(1=SCAN_LOW;2=SCAN_HI;3=CONNECTING)", coexState);
	L4BM_Init_CmdCoexProcessStart(&processStartCmdParams);
	processStartCmdParams.ProcessType.Type = L3L4_TLV_TYPE_COEXISTENCE_STATE;
	processStartCmdParams.ProcessType.State = (UINT32)coexState;

	send_st = wmx_SendL4Command( &processStartCmdParams, CmdCoexProcessStart_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdProcessStart (OUT) wimax status - %d, driver status - %d", send_st, driver_st);
	if (driver_st != 0) {
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_WARNING,
		      "CmxProcessStart failed with invalid opcode; ignoring\n");
		driver_st = 0;
	}
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}

wmx_Status_t wmx_CmdProcessEnd(void)
{
	wmx_Status_t driver_st, send_st;
	CmdCoexProcessEnd_type processEndCmdParams;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdProcessEnd (IN)");
	L4BM_Init_CmdCoexProcessEnd(&processEndCmdParams);

	send_st = wmx_SendL4Command( &processEndCmdParams, CmdCoexProcessEnd_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdProcessEnd (OUT) wimax status - %d, driver status - %d", send_st, driver_st);
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	return driver_st;
}
