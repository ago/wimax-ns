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

// declarations
wmx_Status_t wmxNds_NspIDsToNsps(UINT32 numberOfNsps, wmx_NSPid_t *nspIds, wmx_NSP_t *nsps);

// This callback is called when a new current preferred NSP is selected
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterCurrentPreferredProfileCB( wmx_pIndCurrentPreferredProfileCB_t indCurrentPreferredProfileCB)
{
	wmx_Status_t RC;
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterCurrentPreferredProfileCB(IN)");
	if ( NULL != IndCurrentPreferredProfileCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == indCurrentPreferredProfileCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	IndCurrentPreferredProfileCB = indCurrentPreferredProfileCB;
	
	RC = wmxNds_RegisterOnAgentCurrentPreferredNSPInd();    
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterCurrentPreferredProfileCB(OUT) status=%d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterCurrentPreferredProfileCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterCurrentPreferredProfileCB(IN)");
	if ( NULL == IndCurrentPreferredProfileCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	IndCurrentPreferredProfileCB = NULL;
	RC = wmxNds_UnregisterOnAgentCurrentPreferredNSPInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterCurrentPreferredProfileCB(OUT) status %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectionModeUpdateCB( wmx_pIndConnectionModeUpdateCB_t connectionModeUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterConnectionModeUpdateCB(IN)");
	if ( NULL != ConnectionModeUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == connectionModeUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	ConnectionModeUpdateCB = connectionModeUpdateCB;	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "registering on agent connection mode Update indication");
	st = wmxNds_RegisterOnAgentConnectionModeUpdateInd();
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterConnectionModeUpdateCB(OUT) status=%d", st);

	return st;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectionModeUpdateCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterConnectionModeUpdateCB(IN)");
	if ( NULL == ConnectionModeUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	ConnectionModeUpdateCB = NULL;
	RC = wmxNds_UnregisterOnAgentConnectionModeUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterConnectionModeUpdateCB(OUT) status %d", RC);
	return RC;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterFastReconnectStatusUpdateCB( wmx_pIndFastReconnectStatusUpdateCB_t fastReconnectStatusUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterFastReconnectStatusUpdateCB(IN)");
	if ( NULL != FastReconnectStatusUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == fastReconnectStatusUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	FastReconnectStatusUpdateCB = fastReconnectStatusUpdateCB;	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "registering on agent FastReconnect Update indication");
	st = wmxNds_RegisterOnAgentFastReconnectStatusUpdateInd();
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterFastReconnectStatusUpdateCB(OUT) status=%d", st);

	return st;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterFastReconnectStatusUpdateCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterFastReconnectStatusUpdateCB(IN)");
	if ( NULL == FastReconnectStatusUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	FastReconnectStatusUpdateCB = NULL;
	RC = wmxNds_UnregisterOnAgentFastReconnectStatusUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterFastReconnectStatusUpdateCB(OUT) status %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRoamingModeUpdateCB( wmx_pIndRoamingModeUpdateCB_t roamingModeUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterRoamingModeUpdateCB(IN)");
	if ( NULL != RoamingModeUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == roamingModeUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	RoamingModeUpdateCB = roamingModeUpdateCB;	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "registering on agent Roaming Update indication");
	st = wmxNds_RegisterOnAgentRoamingModeUpdateInd();
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterRoamingUpdateCB(OUT) status=%d", st);

	return st;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRoamingModeUpdateCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterRoamingModeUpdateCB(IN)");
	if ( NULL == RoamingModeUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	RoamingModeUpdateCB = NULL;
	RC = wmxNds_UnregisterOnAgentRoamingModeUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterRoamingModeUpdateCB(OUT) status %d", RC);
	return RC;
}
// This callback is called at least once for every time wmx_CmdUserStartScan was called successfully
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserScanCompletedCB( wmx_pUserScanCompletedCB_t userScanCompletedCB )
{
	wmx_Status_t RC;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserScanCompletedCB(IN)");
	if ( NULL != UserScanCompletedCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == userScanCompletedCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	UserScanCompletedCB = userScanCompletedCB;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on agent scan completed indication");
	RC = wmxNds_RegisterOnAgentScanCompletedInd();    
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserScanCompletedCB(OUT) status=%d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserScanCompletedCB()
{
	wmx_Status_t RC;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserScanCompletedCB(IN)");
	if ( NULL == UserScanCompletedCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	UserScanCompletedCB = NULL;
	RC = wmxNds_UnregisterOnAgentScanCompletedInd();
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserScanCompletedCB(OUT) status %d", RC);
	return RC;
}

// This callback returns all NSP's aggregated since the beginning of the current scan
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserScanUpdateCB( wmx_pUserScanUpdateCB_t userScanUpdateCB )
{
	wmx_Status_t RC;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserScanUpdateCB(IN)");
    
    
	if ( NULL != UserScanUpdateCB )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_WARNING, "wmx_RegisterUserScanUpdateCB - CALLBACK_ALREADY_REGISTERED");
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == userScanUpdateCB )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_RegisterUserScanUpdateCB - WMX_ST_ILLEGAL_OPERATION");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	UserScanUpdateCB = userScanUpdateCB;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on agent scan update indication");
	RC = wmxNds_RegisterOnAgentScanUpdateInd();
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserScanUpdateCB(OUT)");
	return RC;

}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserScanUpdateCB()
{
	wmx_Status_t RC;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserScanUpdateCB(IN)");
    
    
	if ( NULL == UserScanUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	UserScanUpdateCB = NULL;
	RC = wmxNds_UnregisterOnAgentScanUpdateInd();
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserScanUpdateCB(OUT) status=%d", RC);

	return RC;
}

// This callback returns all NSP's aggregated since the beginning of the current scan
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserSystemStateUpdateCB( wmx_pUserSystemStateUpdateCB_t userSystemStateUpdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserSystemStateUpdateCB(IN)");

	if ( NULL != UserSystemStateUpdateCB)
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == userSystemStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	UserSystemStateUpdateCB = userSystemStateUpdateCB;
	
	st = wmxNds_RegisterOnAgentSystemStateUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserSystemStateUpdateCB(OUT) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserSystemStateUpdateCB()
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserSystemStateUpdateCB(IN)");

	if ( NULL == UserSystemStateUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	UserSystemStateUpdateCB = NULL;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Unregistering on agent system state update indication");
	st = wmxNds_UnregisterOnAgentSystemStateUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserSystemStateUpdateCB(OUT) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserMediaStatusCB( wmx_pUserMediaStatusCB_t userMediaStatusCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserMediaStatusCB(IN)");

	if ( NULL != UserMediaStatusCB)
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == userMediaStatusCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	UserMediaStatusCB = userMediaStatusCB;

	st = wmxNds_RegisterOnAgentMediaStatusInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterUserMediaStatusCB(OUT) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserMediaStatusCB()
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserMediaStatusCB(IN)");

	if ( NULL == UserMediaStatusCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	UserMediaStatusCB = NULL;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "Unregistering on agent media status indication");
	st = wmxNds_UnregisterOnAgentMediaStatusInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterUserMediaStatusCB(OUT) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterDeviceStatusUpdateCB( wmx_pIndDeviceStatusUpdateCB_t deviceStatuspdateCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterDeviceStatusUpdateCB(IN)");
	if ( NULL != DeviceStatusUpdateCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == deviceStatuspdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	DeviceStatusUpdateCB = deviceStatuspdateCB;	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "registering on agent Device Status Update indication");
	st = wmxNds_RegisterOnAgentDeviceStatusInd();
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterDeviceStatusUpdateCB(OUT) status=%d", st);

	return st;
}



wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterDeviceStatusUpdateCB()
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterDeviceStatusUpdateCB(IN)");

	if ( NULL == DeviceStatusUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	DeviceStatusUpdateCB = NULL;
	st = wmxNds_UnregisterOnAgentDeviceStatusInd();
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterDeviceStatusUpdateCB(OUT) status=%d", st);

	return st;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterPermisssionsUpdateCB()
{
	wmx_Status_t st = WMX_ST_OK;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterPermisssionsUpdateCB(IN)");

	if ( NULL == PermissionsUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	PermissionsUpdateCB = NULL;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterPermisssionsUpdateCB(OUT) status=%d", st);

	return st;
}


//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserAPDOStatusUpdateCB( wmx_pUserAPDOStatusUpdateCB_t userAPDOStatusUpdateCB)
//{
//	if ( NULL != UserAPDOStatusUpdateCB)
//	{
//		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
//	}
//	if ( NULL == userAPDOStatusUpdateCB )
//	{
//		return WMX_ST_ILLEGAL_OPERATION;
//	}
//
//	UserAPDOStatusUpdateCB = userAPDOStatusUpdateCB;
//
//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on user APDO status update");
//	return wmxNds_RegisterOnUserAPDOStatusUpdateInd();	
//}
//
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserAPDOStatusUpdateCB()
//{
//	if ( NULL == UserAPDOStatusUpdateCB )
//	{
//		return WMX_ST_CALLBACK_NOT_REGISTERED;
//	}
//
//	UserAPDOStatusUpdateCB = NULL;
//	return wmxNds_UnregisterOnUserAPDOStatusUpdateInd();
//}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterIndProvisioningOperationCB( wmx_pIndProvisioningOperationCB_t indProvisioningOperationCB)
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterIndProvisioningOperationCB(IN)");

	if ( NULL != IndProvisioningOperationCB)
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == indProvisioningOperationCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	IndProvisioningOperationCB = indProvisioningOperationCB;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on user APDO status update");
	st = wmxNds_RegisterOnProvisioningOperationInd();	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterIndProvisioningOperationCB(IN) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterIndProvisioningOperationCB()
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterIndProvisioningOperationCB(IN)");

	if ( NULL == IndProvisioningOperationCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	IndProvisioningOperationCB = NULL;
	st = wmxNds_UnregisterOnProvisioningOperationInd();
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterIndPackageUpdateCB(OUT) %d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterIndPackageUpdateCB( wmx_pIndPackageUpdateCB_t indPackageUpdateCB )
{	
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterIndPackageUpdateCB(IN)");

	if ( NULL != IndPackageUpdateCB)
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == indPackageUpdateCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	IndPackageUpdateCB = indPackageUpdateCB;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on indication package update CB");
	st = wmxNds_RegisterOnPackageUpdateInd();

	if (st != WMX_ST_OK)
	{
		return st;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterIndPackageUpdateCB(OUT) %d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterIndPackageUpdateCB()
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterIndPackageUpdateCB(IN)");
	if ( NULL == IndPackageUpdateCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	IndPackageUpdateCB = NULL;
	st = wmxNds_UnregisterOnPackageUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterIndPackageUpdateCB(OUT) %d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectedAsCurrentPreferredCapabilityStatusCB( wmx_pIndConnectedAsCurrentPreferredCapabilityStatusCB_t connectedAsCurrentPreferredCapabilityStatusCB )
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterConnectedAsCurrentPreferredCapabilityStatusCB(IN)");
	if ( NULL != ConnectedAsCurrentPreferredCapabilityStatusCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == connectedAsCurrentPreferredCapabilityStatusCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	ConnectedAsCurrentPreferredCapabilityStatusCB = connectedAsCurrentPreferredCapabilityStatusCB;	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "registering on agent connectedAsCurrentPreferredCapabilityStatusCB Update indication");
	st = wmxNds_RegisterOnAgentConnectedAsCurrentPreferredCapabilityStatusInd();
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterConnectedAsCurrentPreferredCapabilityStatusCB(OUT) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectedAsCurrentPreferredCapabilityStatusCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterConnectedAsCurrentPreferredCapabilityStatusCB(IN)");
	if ( NULL == ConnectedAsCurrentPreferredCapabilityStatusCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	ConnectedAsCurrentPreferredCapabilityStatusCB = NULL;
	RC = wmxNds_UnregisterOnAgentFastReconnectStatusUpdateInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterConnectedAsCurrentPreferredCapabilityStatusCB(OUT) status %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterIndPackageDownloadProgressCB( wmx_pIndPackageDownloadProgressCB_t indPackageDownloadProgressCB)
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterIndPPackageDownloadProgressCB(IN)");

	if ( NULL != IndPackageDownloadProgressCB)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "Callback is already register");
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == indPackageDownloadProgressCB )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wrong argument - indPackageDownloadProgressCB = NULL");
		return WMX_ST_ILLEGAL_OPERATION;
	}

	IndPackageDownloadProgressCB = indPackageDownloadProgressCB;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on indication package update extension CB");
	st = wmxNds_RegisterOnPackageDownloadProgressCBInd();	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmxNds_RegisterOnPackageDownloadProgressCBInd(IN) status=%d", st);

	return st;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterIndPackageDownloadProgressCB()
{
	wmx_Status_t st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterIndPackageDownloadProgressCB(IN)");
	if ( NULL == IndPackageDownloadProgressCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	IndPackageDownloadProgressCB = NULL;
	st = wmxNds_UnregisterOnPackageDownloadProgressCBInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterIndPackageDownloadProgressCB(OUT) %d", st);

	return st;
}

// commands
wmx_Status_t SendNdsCommand( UINT32 opcode, UINT32 requestLength, UINT8 *request )
{
	UINT32 responseLength = 0;
	return SendNdsMsg( opcode, NDNS_OPCODE_COMMAND, requestLength, request, &responseLength, NULL );
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserScan( 
	wmx_ScanType_t scanType, wmx_pUserScanStatus_t scanStatus, UINT32* pNumOfNsps, wmx_pNSP_t pNsps )
{
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserScan(IN) scan type=%d", scanType);
	status = wmx_CmdUserStartScan(scanType);
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "user start scan failed, returned %d", status);
		return status;
	}

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "waiting for scan complete event");
	OSAL_wait_event(g_userScanCompletedEvent, INFINITE);
		
	*scanStatus = GetCurrentUserScanStatus();

	/*if( ( *scanStatus == UserScanSuccessful ) ||
		( *scanStatus == UserScanExhausted ) )
	{
		status = wmx_CmdUserStopScan();
		if( status != WMX_ST_OK )
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "user stop scan failed, returned %d", status);
			return status;
		}
	}*/

	status = wmx_GetLastKnownNSPs(pNumOfNsps, pNsps);
	if( status != WMX_ST_OK )
	{
		return status;
	}

	// Set NULL to the struct if no NSPs are returned
	if (pNumOfNsps == 0)
	{
		pNsps = NULL;
	}

    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserScan(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStartScanDirect(wmx_pChannelInfo_t pChannelsInfoList, 
																		  wmx_pDuplexMode_t pDuplexMode,
																		  UINT32 listSize,
																		  BOOL isBlocking)
{
	wmx_Status_t status;
	UINT8 *pList = NULL;
	int buffSize = 0;
	
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserStartScanDirect(IN)");

	// Validates function parameters. (pDuplexMode not yet supported)
	if (NULL == pChannelsInfoList || /*NULL == pDuplexMode ||*/ listSize == 0)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "wmx_CmdUserStartScanDirect(OUT). Error - Bad parameters. ChannelsList is NULL = %s, list size = %d.", NULL == pChannelsInfoList? "TRUE" : "FALSE", listSize);
		return WMX_ST_WRONG_ARGUMENT;
	}

	// Allocates pList space.
	buffSize = sizeof(wmx_ChannelInfo_t) * listSize + sizeof(wmx_DuplexMode_t) + sizeof(UINT32) + sizeof(BOOL);
	pList = (UINT8 *)malloc(buffSize);
	if (NULL == pList)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "wmx_CmdUserStartScanDirect(OUT). Error - malloc error. Unable to allocate space for pList!!!");
		return WMX_ST_FAIL;
	}

	// Builds the buffer to send to NDnS agent...
	// Duplex mode is not supported at this time.
	if (NULL != pDuplexMode)
	{
		OSAL_memcpy_s(pList, sizeof(wmx_DuplexMode_t), pDuplexMode, sizeof(wmx_DuplexMode_t)); 
	}
	OSAL_memcpy_s(pList + sizeof(wmx_DuplexMode_t), sizeof(UINT32), &listSize, sizeof(UINT32));
	OSAL_memcpy_s(pList + sizeof(wmx_DuplexMode_t) + sizeof(UINT32), sizeof(BOOL), &isBlocking, sizeof(BOOL));
	OSAL_memcpy_s(pList + sizeof(wmx_DuplexMode_t) + sizeof(UINT32) + sizeof(BOOL), 
		sizeof(wmx_ChannelInfo_t) * listSize, 
		pChannelsInfoList, 
		sizeof(wmx_ChannelInfo_t) * listSize);  

	status = SendNdsCommand(NDNS_OPCODE_START_SCAN_DIRECT, buffSize, (UINT8 *)pList);
	if(status != WMX_ST_OK)
	{
		TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "wmx_CmdUserStartScanDirect(OUT). Error - SendNdsCommand returned status-%s", wmxGetStatusStr(status));
		free(pList);
		return status;
	}

	SetCurrentUserScanStarted(TRUE);

	free(pList);
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserStartScanDirect(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStartScan( wmx_ScanType_t scanType )
{
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserStartScan(IN) scan type=%d", scanType);

	status = SendNdsCommand( NDNS_OPCODE_START_SCAN, sizeof(wmx_ScanType_t), (UINT8*)&scanType );
	if( status != WMX_ST_OK )
	{
		return status;
	}

	SetCurrentUserScanStarted(TRUE);

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserStartScan(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStopScan( )
{
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserStopScan(IN)");
	status = SendNdsCommand( NDNS_OPCODE_STOP_SCAN, 0, NULL );	
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserStopScan(OUT)");

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RfOn()
{
	wmx_Status_t status;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RfOn(IN)");
	status = SendNdsCommand( NDNS_OPCODE_RF_ON, 0, NULL );	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RfOn(OUT) status=%d", status);
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RfOff()
{
	wmx_Status_t status;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RfOff(IN)");
	status = SendNdsCommand( NDNS_OPCODE_RF_OFF, 0, NULL );

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RfOff(OUT) status=%d", status);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetCurrentPreferredNSP(UINT32 numOfCurrentPreferred, wmx_pNSPid_t currentPreferredNspIDs)
{
	wmx_Status_t status = WMX_ST_FAIL;
	UINT32 responseLength = 0;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetCurrentPreferredNSP(IN)");
		
	if (numOfCurrentPreferred == 0)
	{  // Clear the current preferred NSP
		status = SendNdsMsg( NDNS_OPCODE_SET_CURRENT_PREFERRED_NSP, NDNS_OPCODE_SET, 0, NULL, &responseLength, NULL );
	}
	else if (numOfCurrentPreferred > 0)
	{ // Supports only one current preferred at the moment
		status = SendNdsMsg( NDNS_OPCODE_SET_CURRENT_PREFERRED_NSP, NDNS_OPCODE_SET, sizeof(UINT32), (UINT8*)&currentPreferredNspIDs[0], &responseLength, NULL );
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetCurrentPreferredNSP(OUT) status=%d", status);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetCurrentPreferredNSP(wmx_pNSP_t pCurrentPreferredNsps, UINT32 *numOfCurrentPreferredNsps)
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_NSP_t);
	UINT8 response[sizeof(wmx_NSP_t)];

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetCurrentPreferredNSP(IN)");
	
	status = SendNdsMsg( NDNS_OPCODE_GET_CURRENT_PREFERRED_NSP, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{				
		goto Finalize;
	}

	*numOfCurrentPreferredNsps = (UINT32)(responseSize / sizeof(wmx_NSP_t));
	*pCurrentPreferredNsps = *(wmx_pNSP_t)response;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetCurrentPreferredNSP(OUT) status=%d", status);

Finalize:
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetNSPContactInfoByName(char* nspName, UINT32 *pNumOfContacts, wmx_pContactInformation_t pContactInformation)
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_ContactInformation_t);// * WMX_URI_MAX_NUM;
	UINT8 *response;	
	UINT32 tmpResponseNumOfContacts;
	wmx_ContactInfoParams contactParams;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_GetNSPContactInfoByName (IN)");	

	OSAL_strncpy_s(contactParams.nspName, MAX_SIZE_OF_NSP_NAME, nspName, OSAL_strnlen(nspName, MAX_SIZE_OF_NSP_NAME));

	responseSize *= WMX_URI_MAX_NUM;
	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg(NDNS_OPCODE_GET_NSP_CONTACT_INFO_BY_NAME, NDNS_OPCODE_APDO, 
		sizeof(wmx_ContactInfoParams), (UINT8*)&contactParams, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		free(response);
		return status;
	}

	// Make sure that the returned buffer is in a correct size	
	tmpResponseNumOfContacts = (UINT32)(responseSize / sizeof(wmx_ContactInformation_t));
	if (tmpResponseNumOfContacts * sizeof(wmx_ContactInformation_t) != responseSize) 
	{
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}

	// Make sure that the buffer allocated has enough space
	if (tmpResponseNumOfContacts <= *pNumOfContacts)
	{
		*pNumOfContacts = tmpResponseNumOfContacts;
	}
	else
	{
		free(response);
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	OSAL_memcpy_s(pContactInformation, sizeof(wmx_ContactInformation_t) * WMX_URI_MAX_NUM, response, responseSize);	

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_GetNSPContactInfoByName (OUT)");
	free(response);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetContactInformation(wmx_NSPid_t nspId, UINT32 *pNumOfContacts, wmx_pContactInformation_t pContactInformation)
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_ContactInformation_t);// * WMX_URI_MAX_NUM;
	UINT8 *response;	
	UINT32 tmpResponseNumOfContacts;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_GetContactInformation (IN)");	
	
	responseSize *= WMX_URI_MAX_NUM;
	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg(
		NDNS_OPCODE_GET_CONTACT_INFORMATION, NDNS_OPCODE_APDO, sizeof(wmx_NSPid_t), (UINT8*)&nspId, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		free(response);
		return status;
	}
	
	// Make sure that the returned buffer is in a correct size	
	tmpResponseNumOfContacts = (UINT32)(responseSize / sizeof(wmx_ContactInformation_t));
	if (tmpResponseNumOfContacts * sizeof(wmx_ContactInformation_t) != responseSize) 
	{
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}

	// Make sure that the buffer allocated has enough space
	if (tmpResponseNumOfContacts <= *pNumOfContacts)
	{
		*pNumOfContacts = tmpResponseNumOfContacts;
	}
	else
	{
		free(response);
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	OSAL_memcpy_s(pContactInformation, sizeof(wmx_ContactInformation_t) * WMX_URI_MAX_NUM, response, responseSize);

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmx_GetContactInformation (OUT)");
	free(response);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserConnect( 
	wmx_NSPid_t nspID, 
	wmx_ConnectionType_t connectionType,
	wmx_NSPid_t homeNSPToRoamTo,
	wmx_pUserCredentials_t userCredentials,
	wmx_pUserConnectStatus_t connectStatus )
{
	wmx_Status_t status;
    UINT32 responseSize = sizeof(wmx_UserConnectStatus_t);
	UINT8 response[sizeof(wmx_UserConnectStatus_t)];
	wmx_ConnectParams connectParams;	
	UINT32 configuredConnectTime;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserConnect(IN). nspID=%d", nspID);
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "sending user connect to agent");

	// prepare the input params for sending
	connectParams.connectionType = connectionType;
	connectParams.homeNSPToRoamTo = homeNSPToRoamTo;
	connectParams.nspID = nspID;
	if (userCredentials != NULL)
	{
		OSAL_strcpy_s(connectParams.userCredentials.username, WMX_CRED_USERNAME_MAX_SIZE, userCredentials->username);
		OSAL_strcpy_s(connectParams.userCredentials.password, WMX_CRED_PASSWORD_MAX_SIZE, userCredentials->password);
	}
	else
	{
		connectParams.userCredentials.username[0] = 0;
		connectParams.userCredentials.password[0] = 0;
	}

	SetCurrentUserConnectStarted(TRUE);

	OSAL_reset_event(g_userConnectCompletedEvent);
	// send the connect command
	status = SendNdsMsg( 
		NDNS_OPCODE_CONNECT, NDNS_OPCODE_COMMAND, sizeof(wmx_ConnectParams), (UINT8*)&connectParams, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "user connect failed, returned %d", status);
		return status;
	}

	configuredConnectTime = (connectTime == 0 ? LONG_OPERATIONS_TIMEOUT : connectTime);

	// To remove the blocking behaviour of connect command
/*	rc = OSAL_wait_event(g_userConnectCompletedEvent, configuredConnectTime);
	if( rc != WAIT_OBJECT_0)	
	{
		if (connectTime != 0) // only if the connect time field is configured in the registry
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_WARNING, "missing connect completed event - continue normal execution patch");
			*connectStatus = UserConnectSuccessful;
			return WMX_ST_OK;
		}		
		*connectStatus = UserConnectFailed;
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserConnect(OUT timeout). connect status=%s", wmxUserConnectStatusName[(*connectStatus - 1)>=UnknownConnectStatus?UnknownConnectStatus:(*connectStatus - 1)]);
		return WMX_ST_DEVICE_FAILURE;				
	}
	else
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmx_CmdUserConnect(g_userConnectCompletedEvent)");
		*connectStatus = GetCurrentUserConnectStatus();	
	}
//	*connectStatus = *(wmx_pUserConnectStatus_t)response; // Oran: old implementation
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserConnect(OUT). connect status=%s", wmxUserConnectStatusName[(*connectStatus - 1)>=UnknownConnectStatus?UnknownConnectStatus:(*connectStatus - 1)]);
	if (UserConnectSuccessful != (*connectStatus) )
	{
		return WMX_ST_DEVICE_FAILURE;
	}
*/
	*connectStatus = GetCurrentUserConnectStatus(); // unnecessary but for good order;
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "[OUT] wmx_CmdUserConnect - connectStatus=%d", configuredConnectTime);

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserDisconnect()
{
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserDisconnect(IN)");
	status = SendNdsCommand( NDNS_OPCODE_DISCONNECT, 0, NULL );
	if( status != WMX_ST_OK )
	{
		return status;
	}

    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_CmdUserDisconnect(OUT)");
	return WMX_ST_OK;
}

// getters
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectedNSP( wmx_pNSP_t connectedNSP )
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(wmx_NSP_t);
	UINT8 response[sizeof(wmx_NSP_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectedNSP(IN)");	
	status = SendNdsMsg( NDNS_OPCODE_GET_CONNECTED_NSP, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetConnectedNSP(OUT) status= %d", status);
		return status;
	}

	*connectedNSP = *(wmx_pNSP_t)response;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectedNSP(OUT) connectedNSP = %d", *connectedNSP);
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetLastKnownNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps )
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(UINT32) + (*pNumOfNsps * sizeof(wmx_NSPid_t));
	UINT8 *response = NULL;	

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetLastKnownNSPs(IN)");
	// allocate the response buffer
	response = (UINT8*)malloc(responseSize);
	
	if (response == NULL) return WMX_ST_FAIL;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "sending get last known nsps to agent");
	status = SendNdsMsg( 
		NDNS_OPCODE_GET_LAST_KNOWN_NSP_IDS, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_GetLastKnownNSPs(OUT ERROR)");

		return status;
	}

	if (*pNumOfNsps >= *(UINT32*)response )
	{
		*pNumOfNsps = *(UINT32*)response;
	}

	status = wmxNds_NspIDsToNsps(*pNumOfNsps, (wmx_NSPid_t*)(response + sizeof(UINT32)), pNsps);

	// free the response buffer
	free( response );
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetLastKnownNSPs(OUT) found %d NSPs", *pNumOfNsps);
	return status;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserConnectMode( wmx_pUserConnectMode_t connectMode )
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(wmx_UserConnectMode_t);
	UINT8 response[sizeof(wmx_UserConnectMode_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUserConnectMode(IN)");
    

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "sending get user connect mode to agent");
	status = SendNdsMsg( 
		NDNS_OPCODE_GET_CONNECTION_MODE, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_GetUserConnectMode(OUT ERROR)");

		return status;
	}

	*connectMode = *(wmx_pUserConnectMode_t)response;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmx_GetUserConnectMode(OUT) user connect mode=%d", *connectMode);

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserLinkStatus( wmx_pUserLinkStatus_t userLinkStatus	)
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(wmx_UserLinkStatus_t);
	UINT8 response[sizeof(wmx_UserLinkStatus_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetLinkStatus(IN)");

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_LINK_STATUS, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		return status;
	}

	OSAL_memcpy_s(userLinkStatus, sizeof(wmx_UserLinkStatus_t), response, sizeof(wmx_UserLinkStatus_t));	

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUserLinkStatus(OUT)");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserStatistics( wmx_pUserStatistics_t	pStatistics)
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(wmx_Statistics_t);
	UINT8 response[sizeof(wmx_Statistics_t)];

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUserStatistics(IN)");

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_STATISTICS, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		return status;
	}

	OSAL_memcpy_s(pStatistics, sizeof(wmx_Statistics_t), response, sizeof(wmx_Statistics_t));	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUserStatistics(OUT)");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetNspInfo (wmx_NSPid_t nspID, wmx_pNSP_t pNsp)
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(wmx_NSP_t);
	UINT8 response[sizeof(wmx_NSP_t)];

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetNspInfo(IN)");
	if (pNsp == NULL) return WMX_ST_RESPONSE_BUFFER_TOO_SHORT;

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_NSP_INFO, NDNS_OPCODE_APDO, sizeof(wmx_NSPid_t), (UINT8*)&nspID, &responseSize, response );
	
	if( status != WMX_ST_OK )
	{
		return status;
	}

	if ( responseSize != sizeof(wmx_NSP_t) )
	{
		return WMX_ST_PIPE_FAILURE;
	}

	OSAL_memcpy_s(pNsp, sizeof(wmx_NSP_t), response, sizeof(wmx_NSP_t));	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetNspInfo(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserRoamingMode( wmx_pUserRoamingMode_t roamingMode )
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(wmx_UserRoamingMode_t);
	UINT8 response[sizeof(wmx_UserRoamingMode_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUserRoamingMode(IN)");
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "sending get user roaming mode to agent");
	status = SendNdsMsg( 
		NDNS_OPCODE_GET_ROAMING_MODE, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
    
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_GetUserRoamingMode(OUT ERROR)");


		return status;
	}

	*roamingMode = *(wmx_pUserRoamingMode_t)response;

    
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUserRoamingMode(OUT). Roaming mode=%s", (*roamingMode == UserEnableRoaming)?"UserEnableRoaming":"UserDisableRoaming");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectedAsCurrentPreferredCapabilityStatus( BOOL *pIsEnable)
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(BOOL);
	UINT8 response[sizeof(BOOL)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectedAsCurrentPreferredCapabilityStatus(IN)");
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "sending GetConnectedAsCurrentPreferredCapabilityStatus to agent");
	status = SendNdsMsg( 
		NDNS_OPCODE_GET_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
    
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_GetConnectedAsCurrentPreferredCapabilityStatus(OUT ERROR)");
		return status;
	}
    	*pIsEnable = response[0];
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectedAsCurrentPreferredCapabilityStatus. enable mode=%s", (TRUE == *pIsEnable)?"Enable":"Disable");
	//OSAL_memcpy_s(pIsEnable, sizeof(BOOL), response, sizeof(BOOL));
		
	//TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetConnectedAsCurrentPreferredCapabilityStatus(OUT)mode =%d",*pIsEnable);
	return WMX_ST_OK;
}


//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetCoexMode(wmx_pCoexistenceMode_t pCoexMode)
//{
//	int res;
//	WCHAR answer[MAX_REGISTRY_ANSWER];
//
//	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_GetCoexMode(IN)");
//	//get the coexisting mode from the registry
//	res = L4Configurations_getCoexistingMode(answer);
//	if (TRUE != res)
//	{
//		return WMX_ST_FAIL;
//	}
//	if (0 == OSAL_stricmp(L"xor", answer))
//	{
//		*pCoexMode = MODE_XOR;		
//	}
//	else if (0 == OSAL_stricmp(L"cm", answer))
//	{
//		*pCoexMode = MODE_CM;		
//	}
//	else
//	{
//		return WMX_ST_FAIL;
//	}
//
//	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_GetCoexMode(OUT)");
//	return WMX_ST_OK;
//}

// setters
wmx_Status_t SendNdsSet( UINT32 opcode, UINT32 requestLength, UINT8 *request )
{
	UINT32 responseLength = 0;
	return SendNdsMsg( opcode, NDNS_OPCODE_SET, requestLength, request, &responseLength, NULL );
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserConnectMode( wmx_UserConnectMode_t connectMode )
{
	wmx_Status_t status;
	wmx_UserConnectMode_t previousConnectMode;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetUserConnectMode(IN) connectMode=%d", connectMode);

	status = wmx_GetUserConnectMode(&previousConnectMode);
	if ( WMX_ST_OK != status )
	{
   	 	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_SetUserConnectMode(OUT ERROR)");
		return status;
	}

	if( previousConnectMode == connectMode )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmx_SetUserConnectMode(OUT)");
		return WMX_ST_OK;
	}

	status = SendNdsSet( NDNS_OPCODE_SET_CONNECTION_MODE, sizeof(wmx_UserConnectMode_t), (UINT8*)&connectMode );
	if( status != WMX_ST_OK )
	{
   	 	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_SetUserConnectMode(OUT ERROR)");

		return status;
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetUserConnectMode(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserRoamingMode( wmx_UserRoamingMode_t roamingMode )
{
	wmx_Status_t status;
	wmx_UserRoamingMode_t previousRoamingMode;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetUserRoamingMode(IN) roamingMode=%d", roamingMode);
	status = wmx_GetUserRoamingMode(&previousRoamingMode);
	if ( WMX_ST_OK != status )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_SetUserRoamingMode(OUT ERROR)");

		return status;
	}

	if( previousRoamingMode == roamingMode )
	{
    
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmx_SetUserRoamingMode(OUT)");


		return WMX_ST_OK;
	}

	status = SendNdsSet( NDNS_OPCODE_SET_ROAMING_MODE, sizeof(wmx_UserRoamingMode_t), (UINT8*)&roamingMode );
	if( status != WMX_ST_OK )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_SetUserRoamingMode(OUT ERROR)");
		return status;
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetUserRoamingMode(OUT)");

	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUnprovisionedNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps )
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_NSPid_t) * WMX_NSPS_MAX_NUM;
	UINT8 *response = NULL;
	UINT32 tmpResponseNumOfNSPs;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUnprovisionedNSPs(IN)");
	response = (UINT8*)malloc(responseSize);
	if (response == NULL)
	{
		status = WMX_ST_PIPE_FAILURE;
		goto Finalize;
	}

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_UNPROVISIONED_NSP_IDS, NDNS_OPCODE_APDO, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		goto Finalize;
	}

	// Make sure that the returned buffer is in a correct size	
	tmpResponseNumOfNSPs = (UINT32)(responseSize / sizeof(wmx_NSPid_t));
	if (tmpResponseNumOfNSPs * sizeof(wmx_NSPid_t) != responseSize) 
	{		
		status = WMX_ST_PIPE_FAILURE;
		goto Finalize;
	}

	if (tmpResponseNumOfNSPs < *pNumOfNsps)
	{
		*pNumOfNsps = tmpResponseNumOfNSPs;
	}

	status = wmxNds_NspIDsToNsps(*pNumOfNsps, (wmx_NSPid_t*)response, pNsps);	

Finalize:
	if (response != NULL)
	{
		free(response);
	}	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetUnprovisionedNSPs(OUT)");
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetProvisionedNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps )
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_NSPid_t) * WMX_NSPS_MAX_NUM;
	UINT8 *response;
	UINT32 tmpResponseNumOfNSPs;	
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetProvisionedNSPs(IN)");
	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_PROVISIONED_NSP_IDS, NDNS_OPCODE_APDO, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		free(response);
		return status;
	}
	
	// Make sure that the returned buffer is in a correct size	
	tmpResponseNumOfNSPs = (UINT32)(responseSize / sizeof(wmx_NSPid_t));
	if (tmpResponseNumOfNSPs * sizeof(wmx_NSPid_t) != responseSize) 
	{
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}

	if (tmpResponseNumOfNSPs < *pNumOfNsps)
	{
		*pNumOfNsps = tmpResponseNumOfNSPs;
	}

	status = wmxNds_NspIDsToNsps(*pNumOfNsps, (wmx_NSPid_t*)response, pNsps);	

	free(response);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetProvisionedNSPs(OUT) found %d provisioned NSPs", *pNumOfNsps);
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_DeprovisionNSP( wmx_NSPid_t nspID )
{
	wmx_Status_t status;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_DeprovisionNSP(IN) nspId=%d", nspID);
	status = SendNdsMsg( 
		NDNS_OPCODE_DEPROVISION_NSP, NDNS_OPCODE_APDO, sizeof(wmx_NSPid_t), (UINT8*)&nspID, 0, NULL );
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_DeprovisionNSP(OUT)");
	return status;	
}

// this function receives profileId from WimaxAPI as if it was nspIds - need to change in the future.
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetMSChap_v2Crd( wmx_NSPid_t nspId,
																    char* username, 
																    char* password )
{
	wmx_Status_t status;
	wmx_SetMSChapParams MSChapParams;

	// copy the parameters to the MSChapParams struct
	MSChapParams.nspId = nspId;
	OSAL_strncpy_s(MSChapParams.password, (size_t)MAX_EAP_PASSWORD_SIZE, password, OSAL_strnlen(password, MAX_EAP_PASSWORD_SIZE - 1));
	OSAL_strncpy_s(MSChapParams.username, WMX_SUBSCRIBER_ID_MAX_SIZE, username, OSAL_strnlen(username, WMX_SUBSCRIBER_ID_MAX_SIZE - 1));
	
	status = SendNdsMsg
		(NDNS_OPCODE_SET_MSCHAP_V2_CRD, NDNS_OPCODE_SET, sizeof(MSChapParams), (UINT8*)&MSChapParams, 0, NULL);
		

	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_SetMSChap_v2Crd(OUT ERROR)");
		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetMSChap_v2Crd(OUT).");
	return WMX_ST_OK;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_IsAssociated(wmx_pAssociate_t pAssociated)
{
	wmx_Status_t status;
	//	wmx_SystemState_t systemState;
	wmx_DeviceStatus_t deviceStatus;
	wmx_ConnectProgressInfo_t connectProgress;
	//wmx_RfSwitchesStatus_t rfSwitchesStatus;


	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_IsAssociated(IN)");

	status = wmx_GetDeviceStatus(&deviceStatus, &connectProgress);
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_IsAssociated(OUT ERROR)");
		return status;
	}

	if ( DeviceStatus_Connecting == deviceStatus || DeviceStatus_Data_Connected == deviceStatus)
	{
		*pAssociated = Associated;
	}
	else
	{
		*pAssociated = Not_Associated;
	}
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_IsAssociated(OUT) IsAssociated = %d", *pAssociated);

	return WMX_ST_OK;
}
//	wmx_Status_t driver_st, send_st;
//	SetCoexMode_type coexistanceMode;
//
//	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_SetCoexMode (IN)");
//
//	L4BM_Init_SetCoexMode(&coexistanceMode);
//	coexistanceMode.CoexistenceModeType.Type = L3L4_TLV_TYPE_COEXISTENCE_MODE;
//	coexistanceMode.CoexistenceModeType.value = (coexMode == MODE_XOR)? E_COEXISTENCE_MODE_XOR : E_COEXISTENCE_MODE_CM; 
//
//	send_st = wmx_SendL4Command( &coexistanceMode, SetCoexMode_Funcs, *msc_pFuncs, msc_l5ConnID, &driver_st );
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
//	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_SetCoexMode(OUT)");
//	return WMX_ST_OK;

//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_IsAssociated(wmx_pAssociate_t pAssociated)
//{
//	wmx_Status_t return_st;
//	wmx_SystemState_t systemState;
//	wmx_ConnectProgressInfo_t connectProgressInfo;
//	wmx_RfSwitchesStatus_t rfSwitchesStatus;
//
//	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_IsAssociated(IN)");
//	return_st = wmx_GetSystemState(&systemState, &connectProgressInfo, &rfSwitchesStatus);
//	if( return_st != WMX_ST_OK )
//	{
//		return return_st;
//	}
//
//	switch(systemState)
//	{
//	case Connecting:
//	case WimaxConnected:
//	case DataPathConnected:
//		*pAssociated = Associated;
//		break;
//
//	default:
//		*pAssociated = Not_Associated;
//		break;
//	}
//
//	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_IsAssociated(OUT)");
//	return WMX_ST_OK; 
//}

wmx_Status_t wmx_RestoreBackupProvisioningDatabase()
{
	wmx_Status_t status;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RestoreBackupProvisioningDatabase(IN)");
	status = SendNdsMsg( 
		NDNS_OPCODE_RESTORE_BACKUP_PROVISIONING_DATABASE, NDNS_OPCODE_APDO, 0, NULL, 0, NULL );

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RestoreBackupProvisioningDatabase(OUT) status=%d", status);

	return status;
}

wmx_Status_t wmx_ResetToFactorySettings()
{
	wmx_Status_t status;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_ResetToFactorySettings(IN)");
	status = SendNdsMsg( 
		NDNS_OPCODE_RESTORE_FACTORY_SETTINGS, NDNS_OPCODE_APDO, 0, NULL, 0, NULL );

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_ResetToFactorySettings(OUT) status=%d", status);

	return status;
}

// The function gets a buffer of nsp ids and fill a buffer with nsp structs
wmx_Status_t wmxNds_NspIDsToNsps(UINT32 numberOfNsps, wmx_NSPid_t *nspIds, wmx_NSP_t *nsps)
{
	UINT32 currentNspIndex;
	wmx_NSPid_t nspId;
	wmx_Status_t status = WMX_ST_OK;
	wmx_NSP_t nsp;

	// Fetch the NSP structs of the returned NSP IDs and copy them to pNsps
	for (currentNspIndex = 0; currentNspIndex < numberOfNsps; currentNspIndex++)
	{
		//nspId = *(wmx_NSPid_t*)(nspIds + currentNspIndex * sizeof(wmx_NSPid_t));
		nspId = nspIds[currentNspIndex];
		wmx_GetNspInfo(nspId, &nsp);

		OSAL_memcpy_s(&nsps[currentNspIndex], sizeof(wmx_NSP_t), &nsp, sizeof(wmx_NSP_t));
	}

	return status;
}

wmx_Status_t wmx_GetDeviceStatus(wmx_pDeviceStatus_t deviceStatus, wmx_pConnectionProgressInfo_t connectionProgressInfo)
{
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_DeviceStatus_t) + sizeof(wmx_ConnectionProgressInfo_t);
	UINT32 tmpResponseSize = responseSize;
	UINT8 *response;	
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceStatus(IN)");

	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_DEVICE_STATUS, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		free(response);
		return status;
	}
	
	// Make sure that the returned buffer is in a correct size	
	if (tmpResponseSize != responseSize) 
	{
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}
	OSAL_memcpy_s(deviceStatus, sizeof(wmx_DeviceStatus_t), response, sizeof(wmx_DeviceStatus_t));
	OSAL_memcpy_s(connectionProgressInfo, sizeof(wmx_ConnectionProgressInfo_t), response + sizeof(wmx_DeviceStatus_t), sizeof(wmx_ConnectionProgressInfo_t));
	
	free(response);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceStatus(OUT)");
	return status;
}

wmx_Status_t wmx_GetPNMRequestedChannel(CHAR *buffer, UINT32 *bufferSize)
{
	wmx_Status_t status = WMX_ST_OK;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetPNMRequestedChannel(IN)");


	status = SendNdsMsg(NDNS_OPCODE_GET_PNM_REQUESTED_CHANNEL, NDNS_OPCODE_GET, 0, NULL, (UINT32*) bufferSize, (UINT8*)buffer );
	if( status != WMX_ST_OK )
	{		
		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetPNMRequestedChannel(OUT)");
	return status;
}
wmx_Status_t wmx_GetIsPNMCommDevUsingChannel(CHAR *buffer, UINT32 *bufferSize, BOOL *result)
{
	wmx_Status_t status = WMX_ST_OK;	// using status as a returned value for result

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetIsPNMCommDevUsingChannel(IN)");

	status = SendNdsMsg(NDNS_OPCODE_GET_IS_PNM_COMM_DEV_USING_CHANNEL, NDNS_OPCODE_GET, (UINT32)*bufferSize, (UINT8*) buffer, 0, NULL);
	
	switch(status)
	{
	case WMX_ST_OK:		// The device is using the channel
		*result = TRUE;
		break;
	case WMX_ST_FAIL:	// The device is NOT using the channel
		*result = FALSE;
	    break;
	default:
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetIsPNMCommDevUsingChannel: error status");
	    break;
	}
	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetIsPNMCommDevUsingChannel(OUT)");
	return WMX_ST_OK;
}
wmx_Status_t wmx_SetPackageUpdateState( wmx_PackageUpdateState_t packageUpdateState )
{
	//NDNS_OPCODE_APDO_APPROVE_ACTION_REQUEST
	wmx_Status_t status;	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetPackageUpdateState(IN)");

	status = SendNdsMsg(NDNS_OPCODE_SET_PACKAGE_UPDATE_STATE, NDNS_OPCODE_APDO, sizeof(wmx_PackageUpdateState_t), 
		(UINT8*)&packageUpdateState, 0, NULL );

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetPackageUpdateState(OUT)");
	return status;
}

wmx_Status_t wmx_GetPackageInfo( wmx_pPackageInfo_t packageInfo )
{
	UINT8 *response;
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_PackageInfo_t);
	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetPackageInfo(IN)");

	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg(NDNS_OPCODE_GET_PACKAGE_INFO, NDNS_OPCODE_GET, 0, NULL, &responseSize, response);

	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "GetPackageInfo Failed");
		free(response);
		return status;
	}

	// Make sure that the returned buffer is in a correct size	
	if (sizeof(wmx_PackageInfo_t) != responseSize) 
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "GetPackageInfo Failed. Wrong response size");
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}

	OSAL_memcpy_s(packageInfo, sizeof(wmx_PackageInfo_t), response, sizeof(wmx_PackageInfo_t));

	free(response);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetPackageInfo(OUT)");

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetServiceProviderUnLock(char* lockCode)
{
	wmx_Status_t status;	
	UINT32 len;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_NOTICE, "wmx_SetServiceProviderUnLock(IN)");
	
	len = (UINT32)OSAL_strnlen(lockCode, MAX_SP_LOCK_CODE_SIZE + 1);
	if (len > MAX_SP_LOCK_CODE_SIZE)
	{		
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_NOTICE, "wmx_SetServiceProviderUnLock lock code size is invalid");
		return WMX_ST_WRONG_ARGUMENT;
	}

	status = SendNdsMsg(NDNS_OPCODE_SET_SERVICE_PROVIDER_UNLOCK, NDNS_OPCODE_APDO, len, (UINT8*)lockCode, 0, 
		NULL);

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_NOTICE, "wmx_SetServiceProviderUnLock(OUT)");
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetServiceProviderLockStatus(wmx_pSPLockStatus_t pLockStatus, 
																				char* pNSPName)
{
	UINT8 *response;
	wmx_Status_t status = WMX_ST_OK;
	wmx_SpLock_t spLock;
	UINT32 responseSize = sizeof(wmx_SpLock_t);

	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg(NDNS_OPCODE_GET_SERVICE_PROVIDER_LOCK_STATUS, NDNS_OPCODE_APDO, 0, NULL, &responseSize, 
		response);

	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "GetServiceProviderLockStatus Failed");
		free(response);
		return status;
	}

	// Make sure that the returned buffer is in a correct size	
	if (sizeof(wmx_SpLock_t) != responseSize) 
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "GetServiceProviderLockStatus Failed. Wrong response size");
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}

	OSAL_memcpy_s(&spLock, sizeof(wmx_SpLock_t), response, sizeof(wmx_SpLock_t));

	*pLockStatus = spLock.sPLockStatus;

	// If not locket reset NSP name
	if (spLock.sPLockStatus == SP_LOCK_STATUS_UNLOCKED)
	{
		memset(pNSPName, 0x0, MAX_SIZE_OF_NSP_NAME);
	}
	else
	{
		OSAL_memcpy_s(pNSPName, spLock.NSPNameActualLen, spLock.NSPNameBuff, spLock.NSPNameActualLen);
	}


	free(response);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserFastReconnectStatus( BOOL isEnabled )
{
	wmx_Status_t status;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetUserFastReconnectStatus(IN)");	

	status = SendNdsSet( NDNS_OPCODE_SET_FAST_RECONNECT_STATUS, sizeof(BOOL), (UINT8*)&isEnabled );
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_SetUserFastReconnectStatus(OUT ERROR)");
		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetUserFastReconnectStatus(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserFastReconnectStatus( BOOL *pIsEnabled	)
{
	wmx_Status_t status;
	UINT32 responseSize = sizeof(BOOL);
	UINT8 response[sizeof(BOOL)];

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetFastReconnectStatus(IN)");

	status = SendNdsMsg( 
		NDNS_OPCODE_GET_FAST_RECONNECT_STATUS, NDNS_OPCODE_GET, 0, NULL, &responseSize, response );
	if( status != WMX_ST_OK )
	{
		return status;
	}

	OSAL_memcpy_s(pIsEnabled, sizeof(BOOL), response, sizeof(BOOL));	

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetFastReconnectStatus(OUT)");

	return WMX_ST_OK;
}

wmx_Status_t wmx_GetInstallationInfo(wmx_pInstallationInfo_t pInstallationInfo)
{
	UINT8 *response;
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = sizeof(wmx_InstallationInfo_t);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetInstallationInfo(IN)");

	response = (UINT8*)malloc(responseSize);
	if (response == NULL) return WMX_ST_PIPE_FAILURE;

	status = SendNdsMsg(NDNS_OPCODE_GET_INSTALLATION_INFO, NDNS_OPCODE_GET, 0, NULL, &responseSize, response);

	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "GetInstallationInfo Failed");
		free(response);
		return status;
	}

	// Make sure that the returned buffer is in a correct size	
	if (sizeof(wmx_InstallationInfo_t) != responseSize) 
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "GetInstallationInfo Failed. Wrong response size");
		free(response);
		return WMX_ST_PIPE_FAILURE;
	}

	OSAL_memcpy_s(pInstallationInfo, sizeof(wmx_InstallationInfo_t), response, sizeof(wmx_InstallationInfo_t));

	free(response);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetInstallationInfo(OUT)");

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetConnectedAsCurrentPreferredCapabilityStatus( BOOL isEnabled )
{
	wmx_Status_t status;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetConnectedAsCurrentPreferredCapabilityStatus(IN)");	

	status = SendNdsSet( NDNS_OPCODE_SET_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS, sizeof(BOOL), (UINT8*)&isEnabled );
	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_SetConnectedAsCurrentPreferredCapabilityStatus(OUT ERROR)");
		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetConnectedAsCurrentPreferredCapabilityStatus(OUT)");
	return WMX_ST_OK;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRfTakenCB( wmx_pRfTakenCB_t rfTakenCB )
{
	wmx_Status_t RC;
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterRfTakenCB(IN)");
	if ( NULL != RfTakenCB )
	{
		return WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	if ( NULL == rfTakenCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	RfTakenCB = rfTakenCB;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on agent RF taken indication");
	RC = wmxNds_RegisterOnAgentRfTakenInd();    
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterRfTakenCB(OUT) status=%d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRfTakenCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterRfTakenCB(IN)");
	if ( NULL == RfTakenCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	RfTakenCB = NULL;
	RC = wmxNds_UnregisterOnAgentRfTakenInd();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterRfTakenCB(OUT) status %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterPNMNotificationCB(wmx_pIndDevicePNMNotificationCB_t indDevicePNMNotificationCB)
{
	wmx_Status_t RC;
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterPNMNotificationCB(IN)");
	if ( NULL == indDevicePNMNotificationCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	IndDevicePNMNotificationCB  = indDevicePNMNotificationCB;


	RC = wmxNds_RegisterOnAgentPNMNotification();    
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_RegisterPNMNotificationCB(OUT) status=%d", RC);

	return RC;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterPNMNotificationCB()
{
	wmx_Status_t RC;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterPNMNotificationCB(IN)");
	if ( NULL == IndDevicePNMNotificationCB )
	{
		return WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	IndDevicePNMNotificationCB = NULL;
	RC = wmxNds_UnregisterOnAgentPNMNotification();

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_UnregisterPNMNotificationCB(OUT) status %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API wmx_GetWMFComplianceVersion(char *pWMFComplianceVersion, UINT32 WMFComplianceVersionLen)
{
	UINT8 *response;
	wmx_Status_t status = WMX_ST_OK;
	UINT32 responseSize = WMFComplianceVersionLen;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetWMFComplianceVersion(IN)");

	response = (UINT8*)malloc(responseSize);
	if (response == NULL) 
	{
		return WMX_ST_PIPE_FAILURE;
	}

	status = SendNdsMsg(NDNS_OPCODE_GET_WMF_COMPLIANCE_VER, NDNS_OPCODE_GET, 0, NULL, &responseSize, response);

	if( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "GetWMFCompliancInfo Failed");
		free(response);
		return status;
	}

	// Make sure that the returned buffer is in a correct size	
	if (WMFComplianceVersionLen < responseSize) 
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "GetInstallationInfo Failed. Wrong response size");
		free(response);
		return WMX_ST_BUFFER_TOO_SHORT;
	}

	OSAL_strcpy_s(pWMFComplianceVersion, WMFComplianceVersionLen, (char *)response); 
	free(response);
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetInstallationInfo(OUT)");

	return status;
}
wmx_Status_t WMX_WRAPPER_API wmx_GetNonce(WIMAX_API_NONCE_BLOB_P pNonce,UINT32 *pNonceSize)
{

	GetDeviceInfo_type deviceInfo;
	wmx_Status_t driver_st, send_st;
	driver_st = WMX_ST_FAIL;

	
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetNonce(IN)");
	L4BM_Init_GetDeviceInfo( &deviceInfo );
	if (NULL != nds_wrapper_pFuncs)
	{
		send_st = wmx_SendL4Command( &deviceInfo, GetDeviceInfo_Funcs, *nds_wrapper_pFuncs, nds_wrapper_l5ConnID, &driver_st );
	}
	else
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_GetSystemState - nds_wrapper_pFuncs=NULL");
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

	if (deviceInfo.DeviceDetails.Type == L3L4_TLV_TYPE_DEVICE_DETAILS)
	{
		if (*pNonceSize >= sizeof (deviceInfo.DeviceDetails.Nonce))
		{
			OSAL_memcpy_s(pNonce, sizeof(WIMAX_API_NONCE_BLOB), (const char*)deviceInfo.DeviceDetails.Nonce, sizeof(WIMAX_API_NONCE_BLOB));
			*pNonceSize = sizeof (deviceInfo.DeviceDetails.Nonce);
		}
		else
		{
			send_st = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
		}
		
	}
	else
	{
		send_st = WMX_ST_DEVICE_FAILURE;
	}
	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetNonce(OUT)");

	return send_st;
}
