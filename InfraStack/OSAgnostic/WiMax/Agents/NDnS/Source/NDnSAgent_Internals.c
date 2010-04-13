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
#include "NDnSAgent_Internals.h"
#include "wmxSDK_Nds_InternalStructs.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Utils.h"



//************************************************
// Connection Parameters to L5 Layer
//************************************************
L5_CONNECTION nds_l5ConnID = NULL;
tL5DispatcherFunctions *nds_pFuncs = NULL;

//*******************************************
// Private Fields of the NDnS Agent
//*******************************************

// ND&S and L4C context
wmx_NDnS_Context_t g_ndnsContext;

// Holds the configuration state of the AppSrv, running with dSim or driver.
BOOL RunWithDSim = TRUE;

//*******************************************
// Config Parameters
//*******************************************
wmx_THCriteria_t thCriteria;
UINT32 numOfChannelInfos;
wmx_pChannelInfo_t channelInfos = NULL;
UINT32 numOfBSCriteria;
wmx_pBSSelectionCriteria_t bsCriteriaList = NULL;

UINT32 connectTime = 0;

BOOL provisioningStarted = FALSE;
BOOL lastConnectedState = FALSE;  // TRUE means the next time we are in ready state raise the APDOLinkStatusCB

void Ndns_SetLastConnectedState(BOOL connectedState)
{
	lastConnectedState = connectedState;
}

BOOL Ndns_GetLastConnectedState()
{
	return lastConnectedState;
}

void Ndns_SetConnectingNSPTemp(wmx_NSPid_t nspId)
{
	g_ndnsContext.tempConnectingNspId = nspId;
}

wmx_NSPid_t Ndns_GetConnectingNSPTemp()
{
	return g_ndnsContext.tempConnectingNspId;
}

void Ndns_SetConnectingNAPTemp(wmx_NAPid_t napId)
{
	l4db_CopyNapID(napId, g_ndnsContext.tempConnectingNapId);
}

BOOL Ndns_GetConnectingNAPTemp(wmx_pNAPid_t napId)
{
	if (!L4db_IsNapidEmpty(napId))
	{
		l4db_CopyNapID(g_ndnsContext.tempConnectingNapId, napId);
		return TRUE;
	}
	return FALSE;
}

void Ndns_SetProvisioningStarted(BOOL started)
{
	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Ndns_SetProvisioningStarted setting flag to [%d]", started);
	provisioningStarted = started;
}

BOOL Ndns_GetProvisioningStarted()
{
	TRACE(TR_MOD_APDO_AGENT, TR_SEV_DEBUG, "Ndns_GetProvisioningStarted==[%d]", provisioningStarted);
	return provisioningStarted;
}

