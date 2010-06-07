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

#include "wmxSDK_Nds_L5.h"

#include "WrappersUtils.h"
#include "L4BufMan_L3L4Structs.h"
#include "wimax_osal_config_controler.h"

#include "TraceModule.h"
#include "L4MsgProxyIf.h"

#include "L4ConfigurationManager.h"
#include "wmxSDK_Nds_L5.h"
#include "WrappersUtils.h"
#include "wmxSDK_Coex_3.h"

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetCoexistenceMode(wmx_CoexistenceMode_t coexMode)
{
	wmx_Status_t status;
	UINT32 responseLength = 0;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetCoexistanceMode(IN)");

	status = SendNdsMsg( NDNS_OPCODE_SET_COEXISTANCE_MODE, NDNS_OPCODE_SET, sizeof(wmx_CoexistenceMode_t), (UINT8*)&coexMode, &responseLength, NULL );	
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_SetCoexMode(OUT ERROR)");

		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetCoexistanceMode(OUT). Coex mode = %s", (coexMode == WMX_MODE_CM)?"CM":"XOR");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetCoexistenceMode(wmx_pCoexistenceMode_t coexMode)
{
	wmx_Status_t status;
	UINT32 responseLength = sizeof(wmx_CoexistenceMode_t);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetCoexistanceMode(IN)");

	status = SendNdsMsg( NDNS_OPCODE_GET_COEXISTANCE_MODE, NDNS_OPCODE_GET, 0, NULL, &responseLength, (UINT8*)coexMode );	
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetCoexistanceMode(OUT ERROR)");

		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetCoexistanceMode(OUT). Coex mode = %s",(*coexMode == WMX_MODE_CM)?"CM":"XOR");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterCoexUpdateCB( wmx_pCoexUpdateCB_t coexModeCB )
{
	wmx_Status_t RC;
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterCoexUpdateCB(IN)");
	if ( NULL != CoexistenceModeCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == coexModeCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	CoexistenceModeCB = coexModeCB;

	RC = wmx_RegisterOnAgentIndication( 
		&g_coexistenceUpdateIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_COEX_UPDATE, 
		*nds_wrapper_pFuncs, nds_wrapper_l5ConnID );
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterCoexUpdateCB(OUT)");

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterCoexUpdateCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterCoexUpdateCB(IN)");
	if ( NULL == CoexistenceModeCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	CoexistenceModeCB = NULL;
	RC = wmxNds_UnregisterOnAgentCoexUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterCoexUpdateCB(OUT) status %d", RC);
	return RC;
}
