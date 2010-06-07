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
#include "ReadWriteLock.h"
#include "Messenger.h"
#include "TraceAgent.h"

#include "L3L4CommonDefines.h"
#include "L3L4TlvTypes.h"
#include "L4BufDesc.h"
#include "L4BufMan.h"

#include "wmxSDK_CmnInternal.h"
#include "wmxSDK_Nds_Cmn.h"
#include "mxSDK_Nds_CtrlAgent.h"
#include "wmxSDK_Nds_Ctrl.h"
#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Nds_1.h"
#include "wmxSDK_Nds_2.h"
#include "wmxSDK_Nds_3.h"

#include "L4MsgProxyIf.h"



typedef UINT32 NdsCmd;

typedef enum _InternalOpcodes
{
	DRIVER_SCAN_RESULTS_ARRIVED,
    DRIVER_STATE_ARRIVED,
	AGENT_SCAN_RESULTS_ARRIVED,
	AGENT_SCAN_COMPLETED_ARRIVED
} InternalOpcodes;

//************************************************
// Internal Declarations
//************************************************
void wmxNds_ScanResultsArrived(void *scanResults);
void wmxNds_SystemStateArrived(wmx_pSystemState_t systemState);
BOOL wmxNds_DriverSystemStateArrived(void *driverState, wmx_pSystemState_t systemState);
void wmxNds_UserScanResultsArrived(void *scanResults);
wmx_Status_t wmxNds_DriverSystemStateToUserSystemState(wmx_pSystemState_t systemState, UINT16 driverState);
void wmxNds_UserSystemStateToUserConnectionState(wmx_pConnectionState_t connectionState, wmx_SystemState_t systemState);
void wmxNds_DriverScanStatusToUserScanStatus(wmx_pScanStatus_t scanStatus, UINT8 driverScanStatus);
void wmxNds_NAPtoNAP( wmx_NAPid_t target, wmx_NAPid_t source );
void wmxNds_CopyNBytes(UINT32 bytesNum, UINT8 *target, UINT8 *source);

wmx_Status_t wmx_ActuallyUnregisterOnSystemState();
wmx_Status_t wmx_ActuallyRegisterOnSystemState();

wmx_Status_t wmxNds_ActuallyRegisterUserScanCompleted();
wmx_Status_t wmxNds_ActuallyUnregisterUserScanCompleted();

//************************************************
// Internal Definitions
//************************************************
#define FIRST_REGISTERED	1
#define LAST_REGISTERED		0

//************************************************
// Connection Parameters to L5 Layer
//************************************************
static LONG numOfInits = 0; 
static L5_CONNECTION l5ConnID = NULL;
static tL5DispatcherFunctions *pFuncs = NULL;

//************************************************
// Socket data (connection to the L5 dispatcher)
//************************************************
static/*extern*/ char *ndsIpAddr = NULL;
static/*extern*/ USHORT ndsPortNum;

//************************************************
// 
//************************************************
static MessengerFuncs messengerFuncs;

//************************************************
// 
//************************************************
wmx_UserConnectStatus_t g_connectStatus;
static HANDLE g_connectStatusAvailableEvent;
static HANDLE g_disconnectAvailableEvent;
static BOOL isConnected = FALSE;

//************************************************
// Callback functions
//************************************************
//Plastic
wmx_pUserScanCompletedCB_t UserScanCompletedCB = NULL;
wmx_pUserScanUpdateCB_t UserScanUpdateCB = NULL;
//Silver
wmx_pSystemStateUpdateCB_t SystemStateUpdateCB = NULL;
wmx_pConnectionStateUpdateCB_t ConnectionStateUpdateCB = NULL;
//Gold
wmx_pScanCompletedCB_t ScanCompletedCB = NULL;
wmx_pScanUpdateCB_t ScanUpdateCB = NULL;
wmx_pConnectCompletedCB_t ConnectCompletedCB = NULL;

//************************************************
// Synchronizing events
//************************************************
static HANDLE g_scanCompletedEvent = NULL;
//static HANDLE g_scanUpdateEvent = NULL;

//************************************************
// Internal Flags
//************************************************
static LONG numOfGoldScanUpdateRegs = 0;
static LONG numOfSystemStateRegs = 0;
static LONG numOfUserScanCompleted = 0;

//************************************************
// Internal Data
//************************************************
static wmx_NAPid_t connectedNAP;
static wmx_ConnectionState_t currentConnectionState;

//************************************************
// Set L5DispatcherFunctions internal resources according to BOOL flags.
//************************************************
BOOL wmxNds_SetConnectionParams( tL5DispatcherFunctions *pL5dispatcher, char* ndsIpAddress, USHORT ndsPortNumber )
{
	pFuncs = pL5dispatcher;
	if ( NULL != ndsIpAddress )
	{
		ndsIpAddr = (char*)malloc(strlen(ndsIpAddress) + 1);
		memcpy(ndsIpAddr, ndsIpAddress, strlen(ndsIpAddress) + 1);
		ndsIpAddr[strlen(ndsIpAddress)] = '\0';
		ndsPortNum = ndsPortNumber;
	}
	return TRUE;
}

//************************************************
// 
//************************************************
BOOL wmxNds_SetMessengerFuncs( pMessengerFuncs extMessenger )
{
	messengerFuncs = *extMessenger;
	return TRUE;
}

//************************************************
// Plastic - Finalize internal resources according to BOOL flags.
//************************************************
void wmxNds_FinalizeInternalResources( BOOL freeScanCompletedEvent, BOOL freeScanUpdateEvent, BOOL freeConnectEvent, BOOL freeDisconnectEvent )
{
	UNREFERENCED_PARAMETER(freeScanUpdateEvent);
	if (freeScanCompletedEvent)
	{
		OSAL_delete_event(g_scanCompletedEvent);
		g_scanCompletedEvent = NULL;
	}
	//if (freeScanUpdateEvent)
	//{
	//	OSAL_delete_event(g_scanUpdateEvent);
	//	g_scanUpdateEvent = NULL;
	//}
	if (freeConnectEvent)
	{
		OSAL_delete_event(g_connectStatusAvailableEvent);
		g_connectStatusAvailableEvent = NULL;
	}
	if (freeDisconnectEvent)
	{
		OSAL_delete_event(g_disconnectAvailableEvent);
		g_disconnectAvailableEvent = NULL;
	}
}

//************************************************
// Plastic - Initialize internal resources
//************************************************
wmx_Status_t wmxNds_InitializeInternalResources()
{
	g_scanCompletedEvent = OSAL_create_event( NULL, FALSE, FALSE, NULL );
	if ( NULL == g_scanCompletedEvent )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, (L"Error initializing Scan Completed Event"));
		wmxNds_FinalizeInternalResources(FALSE, FALSE, FALSE, FALSE);
		return WMX_ST_FAIL;
	}
	//g_scanUpdateEvent = OSAL_create_event( NULL, FALSE, FALSE, NULL );
	//if ( NULL == g_scanUpdateEvent )
	//{
	//	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, (L"Error initializing Scan Update Event"));
	//	wmxNds_FinalizeInternalResources(TRUE, FALSE, FALSE);
	//	return WMX_ST_FAIL;
	//}
	g_connectStatusAvailableEvent = OSAL_create_event( NULL, FALSE, FALSE, NULL );
	if ( NULL == g_connectStatusAvailableEvent )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, (L"Error initializing Connect Completed Event"));
		wmxNds_FinalizeInternalResources(TRUE, TRUE, FALSE, FALSE);
		return WMX_ST_FAIL;
	}
	g_disconnectAvailableEvent = OSAL_create_event( NULL, FALSE, FALSE, NULL );
	if ( NULL == g_disconnectAvailableEvent )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, (L"Error initializing Disconnect Completed Event"));
		wmxNds_FinalizeInternalResources(TRUE, TRUE, TRUE, FALSE);
		return WMX_ST_FAIL;
	}
	return WMX_ST_OK;
}

//************************************************
// 
//************************************************
void wmxNds_ThreadHandler( void *internalData, UINT32 internalRequestID, UINT32 messageID, void *buffer, UINT32 bufferLength )
{
	UNREFERENCED_PARAMETER(bufferLength);
	UNREFERENCED_PARAMETER(internalData);
	UNREFERENCED_PARAMETER(messageID);
	switch ( internalRequestID )
	{
		case DRIVER_STATE_ARRIVED:
			wmxNds_SystemStateArrived((wmx_pSystemState_t)buffer);
			break;
		case DRIVER_SCAN_RESULTS_ARRIVED:
			wmxNds_ScanResultsArrived(buffer);
			break;
		case AGENT_SCAN_COMPLETED_ARRIVED:
			if ( NULL != UserScanCompletedCB )
			{
				UserScanCompletedCB( *(wmx_pUserScanStatus_t)(((pNDNS_MESSAGE)buffer)->buf) );
			}
			break;
		case AGENT_SCAN_RESULTS_ARRIVED:
			if ( NULL != UserScanUpdateCB )
			{
				UserScanUpdateCB( *(UINT32*)(((pNDNS_MESSAGE)buffer)->buf), (wmx_pNSP_t)(((pNDNS_MESSAGE)buffer)->buf + sizeof(UINT32)) );
			}
			break;
		default:
			break;
	}
}

//************************************************
//  
//************************************************
wmx_Status_t WMX_WRAPPER_API wmxNds_InitL5()
{
	L5_RESULT l5status;
	if (NULL == pFuncs)
	{
		free(ndsIpAddr);
		return WMX_ST_PIPE_FAILURE;
	}
			
	// Connect L5 and through it to AppSrv. Gain L5ConnID.
	l5status = pFuncs->pfnConnect(	ndsIpAddr, 
									ndsPortNum,
									L5_TARGET_DYNAMIC,
									wmxNds_MessagesHandler, 
									wmxNds_EventHandler,
									NULL,
									&l5ConnID	);

    if ((L5_RESULT_OK != l5status) || (NULL == l5ConnID))
    {
		return WMX_ST_PIPE_FAILURE;
    }
	wmx_ActuallyRegisterOnSystemState();
	return WMX_ST_OK;
}

//************************************************
//  
//************************************************
void WMX_WRAPPER_API wmxNds_FinalizeL5()
{
	if (NULL == pFuncs)
	{
		return;
	}
	wmx_ActuallyUnregisterOnSystemState();
	pFuncs->pfnDisconnect(l5ConnID);
	free(ndsIpAddr);
}

//************************************************
//  
//************************************************
void WMX_WRAPPER_API wmxNds_MessagesHandler(L5_CONNECTION Conn,
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
	wmx_SystemState_t systemState;
	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(cbResponseBufferSize);
	UNREFERENCED_PARAMETER(pdwResponseMessageID);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvResponseBuffer);
	UNREFERENCED_PARAMETER(pvUserContext);
	switch (dwSentMessageID)
	{
	//GOLD, SILVER
	case L4_PROXY_OPCODE_STATUS_INDICATION_ARRIVED:
	case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
		switch ( wmx_GetOpcode((UINT8*)pvSentBuffer) )
		{
			case L3_L4_OPCODE_REPORT_STATE:
				if (TRUE == wmxNds_DriverSystemStateArrived(pvSentBuffer, &systemState))
				{
					messengerFuncs.postRequest(MEDIUM, NULL, DRIVER_STATE_ARRIVED, DRIVER_STATE_ARRIVED, (void*)&systemState, sizeof(wmx_SystemState_t), &wmxNds_ThreadHandler);
				}
				break;
			case L3_L4_OPCODE_REPORT_SCAN_RESULT:
				messengerFuncs.postRequest(MEDIUM, NULL, DRIVER_SCAN_RESULTS_ARRIVED, DRIVER_SCAN_RESULTS_ARRIVED, pvSentBuffer, cbSentBufferSize, &wmxNds_ThreadHandler);
				break;
			default:
				break;
		}
		break;
	//PLASTIC
	case NDNS_OPCODE_INDICATION_ARRIVED:
        switch (((pNDNS_MESSAGE_HEADER)pvSentBuffer)->opcode)
        {
			case NDNS_OPCODE_IND_SCAN_UPDATE:
				messengerFuncs.postRequest(MEDIUM, NULL, AGENT_SCAN_RESULTS_ARRIVED, AGENT_SCAN_RESULTS_ARRIVED, pvSentBuffer, cbSentBufferSize, &wmxNds_ThreadHandler);
        		break;
			case NDNS_OPCODE_IND_SCAN_COMPLETED:
				OSAL_set_event(g_scanCompletedEvent);
				messengerFuncs.postRequest(MEDIUM, NULL, AGENT_SCAN_COMPLETED_ARRIVED, AGENT_SCAN_COMPLETED_ARRIVED, pvSentBuffer, cbSentBufferSize, &wmxNds_ThreadHandler);
				break;
			default:
				break;
        }
	    break;
	default:
	    break;
	}
}

//************************************************
//  
//************************************************
void WMX_WRAPPER_API wmxNds_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext)
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(eEvent);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(pvEventData);
}

//************************************************
//  
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxNds_Init()
{
	wmx_Status_t status;
	wmx_SystemState_t currentSystemState;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmxNds_Init()"));
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfInits) )
	{
		if ( WMX_ST_OK != wmxNds_InitializeInternalResources())
		{
			return WMX_ST_FAIL;
		}

		status = wmxNds_InitL5();
		if ( WMX_ST_OK != status)
		{
			return status;
		}

		status = wmx_GetSystemState( &currentSystemState );
		if ( WMX_ST_OK != status )
		{
			return status;
		}
		if ( currentSystemState == DataPathConnected )
		{
			isConnected = TRUE;
		}
		else
		{
			isConnected = FALSE;
		}
		
		return wmxNds_ActuallyRegisterUserScanCompleted();
	}

    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmxNds_Init(OUT)"));

	return WMX_ST_OK;
}

//************************************************
//  
//************************************************
void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxNds_Finalize()
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"void wmxNds_Finalize()"));
    
	if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfInits) )
	{
		wmxNds_ActuallyUnregisterUserScanCompleted();
		wmxNds_FinalizeL5();
		wmxNds_FinalizeInternalResources(TRUE, TRUE, TRUE, TRUE);
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"void wmxNds_Finalize(OUT)"));

}

//************************************************
//  
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmxNds_InitAgent()
{
	wmx_Status_t status;
	wmx_SystemState_t currentSystemState;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmxNds_InitAgent()"));
    
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfInits) )
	{
		status = wmxNds_InitL5();
		if ( WMX_ST_OK != status )
		{
	    	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmxNds_InitAgent(OUT ERROR)"));

			return status;
		}

		status = wmx_GetSystemState( &currentSystemState );
		if ( WMX_ST_OK != status )
		{
	    	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmxNds_InitAgent(OUT ERROR)"));
			return status;
		}
		if ( currentSystemState == DataPathConnected )
		{
			isConnected = TRUE;
		}
		else
		{
			isConnected = FALSE;
		}

		return status;
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmxNds_InitAgent(OUT)"));
	return WMX_ST_OK;
}

//************************************************
//  
//************************************************
void WMX_WRAPPER_API WMX_INT_CALL_CONV wmxNds_FinalizeAgent()
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"void wmxNds_FinalizeAgent()"));
    
    
	if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfInits) )
	{
		wmxNds_FinalizeL5();
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"void wmxNds_FinalizeAgent(OUT)"));

}

//************************************************
// Create a L4 Message Struct and return its allocated size.
//************************************************
int CreateL4Msg(UINT32 opCode, UINT32 bufferLength, char *buffer, char **msg)
{
	NDNS_MESSAGE_HEADER ndsMsgHeader;
	int size = 0;

	ndsMsgHeader.opcode = opCode;
	ndsMsgHeader.bufferLength = bufferLength;

	*msg = (char*)malloc(sizeof(NDNS_MESSAGE_HEADER) + ndsMsgHeader.bufferLength);
	if (*msg == NULL)
	{
		return -1;
	}
	size = sizeof(NDNS_MESSAGE_HEADER) + ndsMsgHeader.bufferLength;
	memcpy(*msg, &ndsMsgHeader, sizeof(NDNS_MESSAGE_HEADER));
	if (bufferLength > 0)
	{
		if (NULL != buffer)
		{
			memcpy(sizeof(NDNS_MESSAGE_HEADER) + *msg, buffer, bufferLength);
		}
		else
		{
			memset(sizeof(NDNS_MESSAGE_HEADER) + *msg, 0, bufferLength);
		}
	}
	return size;
}

//************************************************
//************************************************
// Gold Wrapper CB registrations
//************************************************
//************************************************

//************************************************
// Gold - Register Scan Complete Indication
// This callback is called whenever the driver exit the scan state
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_RegisterScanCompletedCB( wmx_pScanCompletedCB_t scanCompletedCB)
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterScanCompletedCB(wmx_pScanCompletedCB_t scanCompletedCB)"));

	if ( NULL != ScanCompletedCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	ScanCompletedCB = scanCompletedCB;
	if ( NULL == ScanCompletedCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfGoldScanUpdateRegs) )
	{
		l4Ind = L3_L4_OPCODE_REPORT_SCAN_RESULT;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_REGISTER_L4_INDICATION, &l4Ind, 
												  sizeof(RegisteredIndication), &responseID, NULL, NULL );
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterScanCompletedCB(OUT)"));
	return WMX_ST_OK;	
}

//************************************************
// Gold - Unregister Scan Complete Indication
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_UnregisterScanCompletedCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterScanCompletedCB()"));
    

	if ( NULL == ScanCompletedCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfGoldScanUpdateRegs) )
	{
		l4Ind = L3_L4_OPCODE_REPORT_SCAN_RESULT;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, &l4Ind, 
												  sizeof(RegisteredIndication), &responseID, NULL, NULL );
		ScanCompletedCB = NULL;
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
	ScanCompletedCB = NULL;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterScanCompletedCB(OUT)"));
    

	return WMX_ST_OK;
}

//************************************************
// Gold - Register Scan Update Indication
// This callback returns all naps aggregated since the beginning of the current scan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_RegisterScanUpdateCB( wmx_pScanUpdateCB_t scanUpdateCB )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterScanUpdateCB(wmx_pScanUpdateCB_t scanUpdateCB)"));
    

	if ( NULL != ScanUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	ScanUpdateCB = scanUpdateCB;
	if ( NULL == ScanUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfGoldScanUpdateRegs) )
	{
		l4Ind = L3_L4_OPCODE_REPORT_SCAN_RESULT;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_REGISTER_L4_INDICATION, &l4Ind, 
												  sizeof(RegisteredIndication), &responseID, NULL, NULL );
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterScanUpdateCB(OUT)"));
    

	return WMX_ST_OK;
}

//************************************************
// Gold - Unregister Scan Update Indication
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_UnregisterScanUpdateCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterScanUpdateCB()"));
	if ( NULL == ScanUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfGoldScanUpdateRegs) )
	{
		l4Ind = L3_L4_OPCODE_REPORT_SCAN_RESULT;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, &l4Ind,
												  sizeof(RegisteredIndication), &responseID, NULL, NULL );
		ScanUpdateCB = NULL;
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
	ScanUpdateCB = NULL;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterScanUpdateCB(OUT)"));
	return WMX_ST_OK;
}

//************************************************
// Gold - Register Connect Complete Update
// This callback is called once for every time wmx_CmdStartConnect was called successfully
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_RegisterConnectCompletedCB( wmx_pConnectCompletedCB_t connectCompletedCB )
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterConnectCompletedCB(wmx_pConnectCompletedCB_t connectCompletedCB)"));
    
    
	if ( NULL != ConnectCompletedCB )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_RegisterConnectCompletedCB(OUT ERROR)"));
		return WMX_ST_ILLEGAL_OPERATION;
	}
	ConnectCompletedCB = connectCompletedCB;
	if ( NULL == ConnectCompletedCB )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_RegisterConnectCompletedCB(OUT ERROR)"));

		return WMX_ST_ILLEGAL_OPERATION;
	}

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterConnectCompletedCB(OUT)"));

	return WMX_ST_OK;
}

//************************************************
// Gold - Unregister Connect Complete Update
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_UnregisterConnectCompletedCB()
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterConnectCompletedCB()"));
    
    
	if ( NULL == ConnectCompletedCB )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_UnregisterConnectCompletedCB(OUT ERROR)"));

		return WMX_ST_ILLEGAL_OPERATION;
	}
	ConnectCompletedCB = NULL;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterConnectCompletedCB(OUT)"));

	return WMX_ST_OK;
}

//************************************************
//************************************************
// Silver Wrapper CB registrations
//************************************************
//************************************************
wmx_Status_t wmx_ActuallyRegisterOnSystemState()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfSystemStateRegs) )
	{
		l4Ind = L3_L4_OPCODE_REPORT_STATE;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_REGISTER_L4_INDICATION, &l4Ind, 
													sizeof(RegisteredIndication), &responseID, NULL, NULL );
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
	return WMX_ST_OK;
}

wmx_Status_t wmx_ActuallyUnregisterOnSystemState()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

	if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfSystemStateRegs) )
	{
		l4Ind = L3_L4_OPCODE_REPORT_STATE;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, &l4Ind, 
												sizeof(RegisteredIndication), &responseID, NULL, NULL );
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
	return WMX_ST_OK;
}

//************************************************
// Silver - Register System State Indication Update
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterSystemStateUpdateCB( wmx_pSystemStateUpdateCB_t systemStateUpdateCB )
{
	//UINT32 responseID;
	//RegisteredIndication l4Ind;
	//L5_RESULT l5Result;
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterSystemStateUpdateCB(wmx_pSystemStateUpdateCB_t systemStateUpdateCB)"));
	if ( NULL != SystemStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	SystemStateUpdateCB = systemStateUpdateCB;
	if ( NULL == SystemStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	status = wmx_ActuallyRegisterOnSystemState();
	//if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfSystemStateRegs) )
	//{
	//	l4Ind = L3_L4_OPCODE_REPORT_STATE;
	//	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_REGISTER_L4_INDICATION, &l4Ind, 
	//											  sizeof(RegisteredIndication), &responseID, NULL, NULL );
	//	if (L5_RESULT_OK != l5Result)
	//	{
	//		return WMX_ST_PIPE_FAILURE;
	//	}
	//	status = (wmx_Status_t)responseID;
	//	return status;
	//}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterSystemStateUpdateCB(OUT)"));
	return status;
}

//************************************************
// Silver - Unregister System State Indication Update
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterSystemStateUpdateCB()
{
	//L5_RESULT l5Result;
	//UINT32 responseID;
	//RegisteredIndication l4Ind;
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterSystemStateUpdateCB()"));
	if ( NULL == SystemStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	status = wmx_ActuallyUnregisterOnSystemState();
	//if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfSystemStateRegs) )
	//{
	//	l4Ind = L3_L4_OPCODE_REPORT_STATE;
	//	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, &l4Ind, 
	//											  sizeof(RegisteredIndication), &responseID, NULL, NULL );
	//	SystemStateUpdateCB = NULL;
	//	if (L5_RESULT_OK != l5Result)
	//	{
	//		return WMX_ST_PIPE_FAILURE;
	//	}
	//	status = (wmx_Status_t)responseID;
	//	return status;
	//}
	SystemStateUpdateCB = NULL;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterSystemStateUpdateCB(OUT)"));
	return status;
}

//************************************************
// Silver - Register Connection State Indication Update
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectionStateUpdateCB( wmx_pConnectionStateUpdateCB_t connectionStateUpdateCB )
{
    
	//UINT32 responseID;
	//RegisteredIndication l4Ind;
	//L5_RESULT l5Result;
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterConnectionStateUpdateCB(wmx_pConnectionStateUpdateCB_t connectionStateUpdateCB)"));
	if ( NULL != ConnectionStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	ConnectionStateUpdateCB = connectionStateUpdateCB;
	if ( NULL == ConnectionStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	status = wmx_ActuallyRegisterOnSystemState();
	//if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfSystemStateRegs) )
	//{
	//	l4Ind = L3_L4_OPCODE_REPORT_STATE;
	//	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_REGISTER_L4_INDICATION, &l4Ind, 
	//										      sizeof(RegisteredIndication), &responseID, NULL, NULL );
	//	if (L5_RESULT_OK != l5Result)
	//	{
	//		return WMX_ST_PIPE_FAILURE;
	//	}
	//	status = (wmx_Status_t)responseID;
	//	return status;
	//}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterConnectionStateUpdateCB(OUT)"));
	return status;
}

//************************************************
// Silver - Unregister Connection State Indication Update
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectionStateUpdateCB()
{
	//L5_RESULT l5Result;
	//UINT32 responseID;
	//RegisteredIndication l4Ind;
	wmx_Status_t status;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterConnectionStateUpdateCB()"));
	if ( NULL == ConnectionStateUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	status = wmx_ActuallyUnregisterOnSystemState();
	//if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfSystemStateRegs) )
	//{
	//	l4Ind = L3_L4_OPCODE_REPORT_STATE;
	//	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, &l4Ind, 
	//											  sizeof(RegisteredIndication), &responseID, NULL, NULL );
	//	ConnectionStateUpdateCB = NULL;
	//	if (L5_RESULT_OK != l5Result)
	//	{
	//		return WMX_ST_PIPE_FAILURE;
	//	}
	//	status = (wmx_Status_t)responseID;
	//	return status;
	//}
	ConnectionStateUpdateCB = NULL;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterConnectionStateUpdateCB(OUT)"));
	return status;
}

//************************************************
//************************************************
// Plastic Wrapper CB registrations
//************************************************
//************************************************

wmx_Status_t wmxNds_ActuallyRegisterUserScanCompleted()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfUserScanCompleted) )
	{
		l4Ind = NDNS_OPCODE_IND_SCAN_COMPLETED;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_REGISTER_INDICATION, &l4Ind, 
			sizeof(RegisteredIndication), &responseID, NULL, NULL );
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
	return WMX_ST_OK;
}

wmx_Status_t wmxNds_ActuallyUnregisterUserScanCompleted()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

	if ( LAST_REGISTERED == OSAL_atomic_decrement(&numOfUserScanCompleted) )
	{
		l4Ind = NDNS_OPCODE_IND_SCAN_COMPLETED;
		l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_UNREGISTER_INDICATION, &l4Ind, 
			sizeof(RegisteredIndication), &responseID, NULL, NULL );
		if (L5_RESULT_OK != l5Result)
		{
			return WMX_ST_PIPE_FAILURE;
		}
		status = (wmx_Status_t)responseID;
		return status;
	}
	return WMX_ST_OK;
}

//************************************************
// Plastic - Register Scan Completed Indication Callback
// This callback is called at least once for every time wmx_CmdUserStartScan was called successfully
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserScanCompletedCB( wmx_pUserScanCompletedCB_t userScanCompletedCB )
{
	wmx_Status_t RC;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterUserScanCompletedCB(wmx_pUserScanCompletedCB_t userScanCompletedCB)"));
    
    
    if ( NULL != UserScanCompletedCB )
    {
		return WMX_ST_ILLEGAL_OPERATION;
    }
	UserScanCompletedCB = userScanCompletedCB;
	if ( NULL == UserScanCompletedCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	RC = wmxNds_ActuallyRegisterUserScanCompleted();
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterUserScanCompletedCB(OUT)"));
	return RC;
}

//************************************************
// Plastic - Unregister Scan Completed Indication Callback
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserScanCompletedCB()
{
	wmx_Status_t RC;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterUserScanCompletedCB()"));
    
    
	if ( NULL == UserScanCompletedCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	UserScanCompletedCB = NULL;
	RC = wmxNds_ActuallyUnregisterUserScanCompleted();
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterUserScanCompletedCB(OUT)"));
	return RC;
}

//************************************************
// Plastic - Register Scan Update Indication Callback
// This callback returns all NSP's aggregated since the beginning of the current scan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterUserScanUpdateCB( wmx_pUserScanUpdateCB_t userScanUpdateCB )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterUserScanUpdateCB(wmx_pUserScanUpdateCB_t userScanUpdateCB)"));
	if ( NULL != UserScanUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}
	UserScanUpdateCB = userScanUpdateCB;
	if ( NULL == UserScanUpdateCB )
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_RegisterUserScanUpdateCB(OUT ERROR)"));
		return WMX_ST_ILLEGAL_OPERATION;
	}

	l4Ind = NDNS_OPCODE_IND_SCAN_UPDATE;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_REGISTER_INDICATION, &l4Ind, 
											  sizeof(RegisteredIndication), &responseID, NULL, NULL );
	if (L5_RESULT_OK != l5Result)
	{
    
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_RegisterUserScanUpdateCB(OUT ERROR)"));
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterUserScanUpdateCB(OUT)"));

	return status;
}

//************************************************
// Plastic - Unregister Scan Update Indication Callback
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterUserScanUpdateCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	RegisteredIndication l4Ind;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterUserScanUpdateCB()"));
    
	if ( NULL == UserScanUpdateCB )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	l4Ind = NDNS_OPCODE_IND_SCAN_UPDATE;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_UNREGISTER_INDICATION, &l4Ind, 
											  sizeof(RegisteredIndication), &responseID, NULL, NULL );
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	UserScanUpdateCB = NULL;
	status = (wmx_Status_t)responseID;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterUserScanUpdateCB(OUT)"));
	return status;
}

//************************************************
// Plastic - Scan (Blocking)
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserScan( wmx_pUserScanStatus_t status, UINT32* pNumOfNsps, wmx_pNSP_t pNsps )
{
	wmx_Status_t res;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserScan(wmx_pUserScanStatus_t status, UINT32* pNumOfNsps, wmx_pNSP_t pNsps)"));
	res = wmx_CmdUserStartScan();

	if( res != WMX_ST_OK )
	{
		return res;
	}

	//TODO: make sure that the wait is always stopped
	OSAL_wait_event(g_scanCompletedEvent, INFINITE);

	res = wmx_CmdUserStopScan();
	if( res != WMX_ST_OK )
	{
		return res;
	}

	res = wmx_GetLastKnownNSPs(pNumOfNsps, pNsps);
	if( res != WMX_ST_OK )
	{
		return res;
	}

	if ( *pNumOfNsps > 0 )
	{
		*status = UserScanSuccessful;
	}
	else
	{
		*status = UserScanExhausted;
	}

    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserScan(OUT)"));
	return WMX_ST_OK;
}

//************************************************
// Plastic - Start Scan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStartScan( )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	NdsCmd ndsCmd;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserStartScan()"));
	ndsCmd = NDNS_OPCODE_START_SCAN;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_COMMAND, &ndsCmd, 
											  sizeof(NdsCmd), &responseID, NULL, NULL );
	if (L5_RESULT_OK != l5Result)
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserStartScan(OUT ERROR)"));

		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserStartScan(OUT)"));

	return status;
}

//************************************************
// Plastic - Stop Scan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserStopScan( )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	NdsCmd ndsCmd;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserStopScan()"));
	ndsCmd = NDNS_OPCODE_STOP_SCAN;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_COMMAND, &ndsCmd, 
											  sizeof(NdsCmd), &responseID, NULL, NULL );
	if (L5_RESULT_OK != l5Result)
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserStopScan(OUT ERROR)"));

		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserStopScan(OUT)"));
	return status;
}

//************************************************
// Plastic - Connect
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserConnect( wmx_NSPid_t nspID, wmx_pUserConnectStatus_t connectStatus )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	char *buf;
	UINT32 size = 0;
	UINT32 responseID;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserConnect(wmx_NSPid_t nspID, wmx_pUserConnectStatus_t connectStatus)"));

	size = CreateL4Msg(NDNS_OPCODE_CONNECT, sizeof(wmx_NSPid_t), (char*)&nspID, &buf);
	if (size == -1)
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserConnect(OUT ERROR)"));
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_COMMAND, buf, size, &responseID, NULL, NULL );
	free(buf);
	if (L5_RESULT_OK != l5Result)
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserConnect(OUT ERROR)"));
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserConnect(OUT ERROR)"));

		return status;
	}
	OSAL_wait_event(g_connectStatusAvailableEvent, INFINITE);
	*connectStatus = g_connectStatus;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserConnect(OUT)"));
	return status;
}

//************************************************
// Plastic - Disconnect
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdUserDisconnect()
{
    
	L5_RESULT l5Result;
	wmx_Status_t status;
	UINT32 responseID;
	NdsCmd ndsCmd;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserDisconnect()"));

	ndsCmd = NDNS_OPCODE_DISCONNECT;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_COMMAND, &ndsCmd, 
											  sizeof(RegisteredIndication), &responseID, NULL, NULL );
	if (L5_RESULT_OK != l5Result)
	{
    
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserDisconnect(OUT ERROR)"));
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
    
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserDisconnect(OUT ERROR)"));
		return status;
	}
	OSAL_wait_event(g_disconnectAvailableEvent, INFINITE);
	// In this place isConnected is supposed to be FALSE when disconnection succeeds
	// it remains TRUE if disconnection failed and we are still connected to DATA_PATH
	if (isConnected == TRUE)
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, (L"wmx_Status_t wmx_CmdUserDisconnect(OUT ERROR)"));

		return WMX_ST_FAIL;
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdUserDisconnect(OUT)"));


	return status;
}

//************************************************
// Plastic - Get Connected NSP
// Returns NULL if not connected
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectedNSP( wmx_pNSP_t connectedNSP )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	NdsCmd ndsCmd;
	UINT32 responseID;
	UINT32 responseSize = sizeof(wmx_NSP_t);
	char responseBuffer[sizeof(wmx_NSP_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetConnectedNSP(wmx_pNSP_t connectedNSP)"));
    
//	// TODO: Patch only, should be handled by dSim
//	if (isConnected == FALSE)
//	{
//		connectedNSP->nspID = 0;
//		return WMX_ST_OK;
//	}

	ndsCmd = NDNS_OPCODE_GET_CONNECTED_NSP;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_GET, &ndsCmd, sizeof(NdsCmd), 
											  &responseID, responseBuffer, &responseSize );
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
		return status;
	}
	*connectedNSP = *(wmx_pNSP_t)responseBuffer;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetConnectedNSP(OUT)"));
	return status;
}

//************************************************
// Plastic - Get Last Known NSPs
// pNumOfNsps is an in out parameter. It should contain the expected number of NSPs to begin with.
// see WMX_NSPS_MAX_NUM
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetLastKnownNSPs( UINT32* pNumOfNsps, wmx_pNSP_t pNsps )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	NdsCmd ndsCmd;
	UINT32 responseID;
	UINT32 responseSize = sizeof(UINT32) + (*pNumOfNsps * sizeof(wmx_NSP_t));
	char *responseBuffer;
	responseBuffer = (char*)malloc(responseSize);

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetLastKnownNSPs(UINT32* pNumOfNsps, wmx_pNSP_t pNsps)"));
	ndsCmd = NDNS_OPCODE_GET_LAST_KNOWN_NSPS;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_GET, &ndsCmd, sizeof(NdsCmd), 
											  &responseID, responseBuffer, &responseSize );
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
		return status;
	}
	if (*pNumOfNsps >= *(UINT32*)responseBuffer )
	{
		*pNumOfNsps = *(UINT32*)responseBuffer;
	}
	memcpy(pNsps, (responseBuffer + sizeof(UINT32)), (*pNumOfNsps * sizeof(wmx_NSP_t)) );
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetLastKnownNSPs(OUT)"));
	return status;
}

//************************************************
// Plastic - Get Service Level Agreement for requested NSP
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetSLA( wmx_NSPid_t nspID, wmx_pSLA_t pSla )
{
    
	L5_RESULT l5Result;
	wmx_Status_t status;
	char *buf;
	UINT32 size = 0;
	UINT32 responseID;
	UINT32 responseSize = sizeof(wmx_SLA_t);
	char responseBuffer[sizeof(wmx_SLA_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetSLA(wmx_NSPid_t nspID, wmx_pSLA_t pSla)"));
	size = CreateL4Msg(NDNS_OPCODE_GET_SLA, sizeof(wmx_NSP_t), (char*)&nspID, &buf);
	if (size == -1)
	{
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage(l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_GET, buf, size, &responseID, responseBuffer, &responseSize );
	free(buf);
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
		return status;
	}
	*pSla = *(wmx_pSLA_t)responseBuffer;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetSLA(OUT)"));
	return status;
}

//************************************************
// Plastic - Get User Connect Mode that is set in the Agent
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserConnectMode( wmx_pUserConnectMode_t connectMode )
{
    
	L5_RESULT l5Result;
	wmx_Status_t status;
	NdsCmd ndsCmd;
	UINT32 responseID;
	UINT32 responseSize = sizeof(wmx_UserConnectMode_t);
	char responseBuffer[sizeof(wmx_UserConnectMode_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetUserConnectMode(wmx_pUserConnectMode_t connectMode)"));
	ndsCmd = NDNS_OPCODE_GET_CONNECTION_MODE;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_GET, &ndsCmd, sizeof(NdsCmd), 
											  &responseID, responseBuffer, &responseSize );
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
		return status;
	}
	*connectMode = *(wmx_pUserConnectMode_t)responseBuffer;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetUserConnectMode(OUT)"));


	return status;
}

//************************************************
// Plastic - Set the User Connect Mode to the Agent
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserConnectMode( wmx_UserConnectMode_t connectMode )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	char *buf;
	UINT32 size = 0;
	UINT32 responseID;
	wmx_UserConnectMode_t previousConnectMode;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetUserConnectMode(wmx_UserConnectMode_t connectMode)"));

	status = wmx_GetUserConnectMode(&previousConnectMode);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	size = CreateL4Msg(NDNS_OPCODE_SET_CONNECTION_MODE, sizeof(wmx_UserConnectMode_t), (char*)&connectMode, &buf);
	if (size == -1)
	{
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage(l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_SET, buf, size, &responseID, NULL, NULL );
	free(buf);
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if ( WMX_ST_OK == status )
	{
		if ( (previousConnectMode == UserAutoConnection) && (connectMode == UserManualConnection) )
		{
			if ( FALSE == isConnected )
			{
				status = wmx_CmdStopScan();
			}
		}
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetUserConnectMode(OUT)"));
	return status;
}

//************************************************
// Plastic - Get User Roaming Mode that is set in the Agent
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetUserRoamingMode( wmx_pUserRoamingMode_t connectMode )
{
    
	L5_RESULT l5Result;
	wmx_Status_t status;
	NdsCmd ndsCmd;
	UINT32 responseID;
	UINT32 responseSize = sizeof(wmx_UserRoamingMode_t);
	char responseBuffer[sizeof(wmx_UserRoamingMode_t)];

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetUserRoamingMode(wmx_pUserRoamingMode_t connectMode)"));
	ndsCmd = NDNS_OPCODE_GET_ROAMING_MODE;
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_GET, &ndsCmd, sizeof(NdsCmd), 
		&responseID, responseBuffer, &responseSize );
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
		return status;
	}
	*connectMode = *(wmx_pUserRoamingMode_t)responseBuffer;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetUserRoamingMode(OUT)"));
	return status;
}

//************************************************
// Plastic - Set the User Roaming Mode to the Agent
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetUserRoamingMode( wmx_UserRoamingMode_t connectMode )
{
    
	L5_RESULT l5Result;
	wmx_Status_t status;
	char *buf;
	UINT32 size = 0;
	UINT32 responseID;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetUserRoamingMode(wmx_UserRoamingMode_t connectMode)"));
	size = CreateL4Msg(NDNS_OPCODE_SET_ROAMING_MODE, sizeof(wmx_UserRoamingMode_t), (char*)&connectMode, &buf);
	if (size == -1)
	{
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage(l5ConnID, L5_TARGET_NDNS, NDNS_OPCODE_SET, buf, size, &responseID, NULL, NULL );
	free(buf);
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetUserRoamingMode(OUT)"));
	return status;
}

//************************************************
// Gold - Start Scan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_CmdStartScan()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	ScanCommand_type scanCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdStartScan()"));

	responseBufferSize = wmx_GetMaxBufferSize_ScanCommand();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;
    
	wmx_Init_ScanCommand(&scanCmd);
	scanCmd.DoScanCommandType = L3L4_TLV_TYPE_SCAN_COMMAND;
	scanCmd.DoScanCommand = E_SCAN_COMMAND_START;
	requestBufferSize = wmx_GetBufferSize_ScanCommand(scanCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_ScanCommand((UINT8*)requestBuffer, scanCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( (L5_CONNECTION)l5ConnID, (L5_TARGET_ID)L5_TARGET_L4_PROXY, (UINT32)L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  (UINT32*)&responseID, (void*)response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_ScanCommand(&scanCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)scanCmd.header.Status);
	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdStartScan(OUT)"));
	return status;
}

//************************************************
// Gold - Stop Scan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_CmdStopScan()
{
    
	L5_RESULT l5Result;
	wmx_Status_t status;
	ScanCommand_type scanCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdStopScan()"));
	responseBufferSize = wmx_GetMaxBufferSize_ScanCommand();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_ScanCommand(&scanCmd);
	scanCmd.DoScanCommandType = L3L4_TLV_TYPE_SCAN_COMMAND;
	scanCmd.DoScanCommand = E_SCAN_COMMAND_STOP;
	requestBufferSize = wmx_GetBufferSize_ScanCommand(scanCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_ScanCommand((UINT8*)requestBuffer, scanCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( (L5_CONNECTION)l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, (void*)response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_ScanCommand(&scanCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)scanCmd.header.Status);
	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdStopScan(OUT)"));
	return status;
}

//************************************************
// Gold - Start Connect
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_CmdStartConnect(wmx_NAPid_t napID)
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	Connect_type connectCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdStartConnect(wmx_NAPid_t napID)"));
	responseBufferSize = wmx_GetMaxBufferSize_Connect();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	//connectCmd.OperatorID[0] = nap[0];
	//connectCmd.OperatorID[1] = nap[2];
	//connectCmd.OperatorID[2] = nap[3];
	wmx_Init_Connect(&connectCmd);
	wmxNds_NAPtoNAP(connectCmd.OperatorID, napID);
	connectCmd.OperatorIDType = L3L4_TLV_TYPE_OPERATOR_ID;
	connectCmd.ConnectOperation = E_CONNECT_OPERATION_TO_FIRST;
	connectCmd.ConnectOperationType = L3L4_TLV_TYPE_CONNECT_OPERATION;
	requestBufferSize = wmx_GetBufferSize_Connect(connectCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_Connect((UINT8*)requestBuffer, connectCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
		&responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_Connect(&connectCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)connectCmd.header.Status);
	free(response.buffer);
	if ( WMX_ST_OK == status )
	{
		//connectedNAP[0] = nap[0];
		//connectedNAP[1] = nap[1];
		//connectedNAP[2] = nap[2];
		wmxNds_NAPtoNAP(connectedNAP, napID);
		ConnectCompletedCB(ConnectSuccessful);
	}
	else
	{
		//connectedNAP[0] = 0;
		//connectedNAP[1] = 0;
		//connectedNAP[2] = 0;
		wmxNds_NAPtoNAP(connectedNAP, NULL);
		ConnectCompletedCB(ConnectFailed);
	}
	
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdStartConnect(OUT)"));
	return status;
}

//************************************************
// Gold - Disconnect
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_CmdDisconnect()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	Disconnect_type disconnectCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdDisconnect()"));
	responseBufferSize = wmx_GetMaxBufferSize_Disconnect();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	//disconnectCmd.OperatorID[0] = connectedNAP[0];
	//disconnectCmd.OperatorID[1] = connectedNAP[1];
	//disconnectCmd.OperatorID[2] = connectedNAP[2];
	wmx_Init_Disconnect(&disconnectCmd);
	wmxNds_NAPtoNAP(disconnectCmd.OperatorID, connectedNAP);
	disconnectCmd.OperatorIDType = L3L4_TLV_TYPE_OPERATOR_ID;
	requestBufferSize = wmx_GetBufferSize_Disconnect(disconnectCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_Disconnect((UINT8*)requestBuffer, disconnectCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_Disconnect(&disconnectCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)disconnectCmd.header.Status);
	free(response.buffer);
	if ( WMX_ST_OK == status )
	{
		//connectedNAP[0] = 0;
		//connectedNAP[1] = 0;
		//connectedNAP[2] = 0;
		wmxNds_NAPtoNAP(connectedNAP, NULL);
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdDisconnect(OUT)"));
	return status;
}

//************************************************
// Gold - Cancel Connect
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_CmdCancelConnect()
{
	//TODO: currently calls regular disconnect
	wmx_Status_t status;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdCancelConnect()"));
	status = wmx_CmdDisconnect();
	if ( WMX_ST_OK == status )
	{
		ConnectCompletedCB(ConnectCancelled);
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_CmdCancelConnect(OUT)"));
	return status;
}

//************************************************
// Gold - Get Connected NAP
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_GetConnectedNAP( wmx_pNAP_t connectedNAP )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	GetLinkParameters_type getLinkParametersCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetConnectedNAP(wmx_pNAP_t connectedNAP)"));

	if ( NULL == connectedNAP )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	responseBufferSize = wmx_GetMaxBufferSize_GetLinkParameters();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_GetLinkParameters(&getLinkParametersCmd);
	requestBufferSize = wmx_GetBufferSize_GetLinkParameters(getLinkParametersCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_GetLinkParameters((UINT8*)requestBuffer, getLinkParametersCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
		&responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_GetLinkParameters(&getLinkParametersCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)getLinkParametersCmd.header.Status);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	if ( INVALID_OPCODE != getLinkParametersCmd.OperatorIDType )
	{
		//pNap->napID[0] = getLinkParametersCmd.OperatorID[0];
		//pNap->napID[1] = getLinkParametersCmd.OperatorID[1];
		//pNap->napID[2] = getLinkParametersCmd.OperatorID[2];
		wmxNds_NAPtoNAP(connectedNAP->napID, getLinkParametersCmd.OperatorID);
	}
	else
	{
		//pNap->napID[0] = 0;
		//pNap->napID[1] = 0;
		//pNap->napID[2] = 0;
		wmxNds_NAPtoNAP(connectedNAP->napID, NULL);
		status = WMX_ST_DEVICE_FAILURE;
	}
	if ( INVALID_OPCODE != getLinkParametersCmd.LinkStatusType )
	{
		connectedNAP->bestRssi = getLinkParametersCmd.RxRssi;
	}
	
	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetConnectedNAP(OUT)"));
	return status;
}

//************************************************
// Gold - Get Last Known NAP's
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_GetLastKnownNAPs( UINT32* pNumOfNaps, wmx_pNAP_t pNaps )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	GetScanResults_type getScanResults;
	L4BUFMAN_Status_t res;
	UINT32 i = 0;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetLastKnownNAPs(UINT32* pNumOfNaps, wmx_pNAP_t pNaps)"));

	if ( (NULL == pNaps) || (NULL == pNumOfNaps) )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	responseBufferSize = wmx_GetMaxBufferSize_GetScanResults();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_GetScanResults(&getScanResults);
	requestBufferSize = wmx_GetBufferSize_GetScanResults(getScanResults);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_GetScanResults((UINT8*)requestBuffer, getScanResults);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_GetScanResults(&getScanResults, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)getScanResults.header.Status);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	
	for ( i = 0; i < *pNumOfNaps; i++ )
	{
		if ( INVALID_OPCODE != getScanResults.ScanResultList[i].ScanResultListType )
		{
			pNaps[i].bestRssi = getScanResults.ScanResultList[i].BestRssi;
			pNaps[i].numOfBSs = getScanResults.ScanResultList[i].NumOfLinks;
			wmxNds_NAPtoNAP(pNaps[i].napID, getScanResults.ScanResultList[i].NetworkId);
		}
		else
		{
			*pNumOfNaps = i;
		}
	}

	free(response.buffer);
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetLastKnownNAPs(OUT)"));
	return status;
}

//************************************************
// Gold - Set Scan Policy
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_SetScanPolicy( wmx_ScanPolicy_t scanPolicy )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	SetScanParameters_type scanParametersCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetScanPolicy(wmx_ScanPolicy_t scanPolicy)"));

	responseBufferSize = wmx_GetMaxBufferSize_SetScanParameters();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_SetScanParameters(&scanParametersCmd);
	scanParametersCmd.ScanPolicyType = L3L4_TLV_TYPE_SCAN_POLICY;
	scanParametersCmd.StandbyScanInterval = (UINT16)scanPolicy.standByScanInterval;
	scanParametersCmd.OozScanInterval = (UINT16)scanPolicy.oozInterval;
	scanParametersCmd.ReportPolicy = scanPolicy.reportPolicy;
	scanParametersCmd.ReportTimer = (UINT8)scanPolicy.reportTimer;
	scanParametersCmd.ScanMode = (UINT8)scanPolicy.scanMode; // TODO
	scanParametersCmd.IsRssiScanRequired = (UINT8)scanPolicy.isRssiScanRequired;
	requestBufferSize = wmx_GetBufferSize_SetScanParameters(scanParametersCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_SetScanParameters((UINT8*)requestBuffer, scanParametersCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_SetScanParameters(&scanParametersCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)scanParametersCmd.header.Status);
	
	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetScanPolicy(OUT)"));
	return status;
}

//************************************************
// Gold - Set Channel Plan
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_SetChannelPlan( UINT32 numOfChannelInfos, wmx_pChannelInfo_t channelInfos )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	SetScanParameters_type scanParametersCmd;
	L4BUFMAN_Status_t res;
	UINT32 i;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetChannelPlan(UINT32 numOfChannelInfos, wmx_pChannelInfo_t channelInfos)"));
	responseBufferSize = wmx_GetMaxBufferSize_SetScanParameters();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_SetScanParameters(&scanParametersCmd);
	for ( i = 0; i < numOfChannelInfos; i++ )
	{
		if ( NULL != (channelInfos + i * sizeof(wmx_ChannelInfo_t)) )
		{
			//UINT8 Fft;
			scanParametersCmd.ChannelInfoArray[i].ChannelInfoArrayType = L3L4_TLV_TYPE_CHANNEL_INFO;
			scanParametersCmd.ChannelInfoArray[i].ChannelId = channelInfos[i].channelID;
			scanParametersCmd.ChannelInfoArray[i].Frequency = (UINT32)(channelInfos[i].frequency);
			scanParametersCmd.ChannelInfoArray[i].Bandwidth = channelInfos[i].bw;
			scanParametersCmd.ChannelInfoArray[i].CyclicPrefix = channelInfos[i].cyclicPrefix;
			scanParametersCmd.ChannelInfoArray[i].FrameLength = (UINT8)channelInfos[i].frameLen;
			scanParametersCmd.ChannelInfoArray[i].PpmFreqError = (UINT8)channelInfos[i].ppmFreqErr;
			wmxNds_CopyNBytes(sizeof(wmx_Preambles_t), scanParametersCmd.ChannelInfoArray[i].Preambles, channelInfos[i].preambleBitmap);
		}
	}
	requestBufferSize = wmx_GetBufferSize_SetScanParameters(scanParametersCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_SetScanParameters((UINT8*)requestBuffer, scanParametersCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
		&responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_SetScanParameters(&scanParametersCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)scanParametersCmd.header.Status);

	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetChannelPlan(OUT)"));
	return status;
}

//************************************************
// Gold - Set Common Scan Criteria
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_SetCommonScanCriteria( wmx_CommonCriteria_t commonCriteria )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	SetScanParameters_type scanParametersCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetCommonScanCriteria(wmx_CommonCriteria_t commonCriteria)"));

	responseBufferSize = wmx_GetMaxBufferSize_SetScanParameters();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_SetScanParameters(&scanParametersCmd);
	scanParametersCmd.CommonScanCriteriaType = L3L4_TLV_TYPE_COMMON_SCAN_CRITERIA;
	scanParametersCmd.RssiTH = commonCriteria.rssiTH;
	scanParametersCmd.CinrTH = commonCriteria.cinrTH;
	requestBufferSize = wmx_GetBufferSize_SetScanParameters(scanParametersCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_SetScanParameters((UINT8*)requestBuffer, scanParametersCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_SetScanParameters(&scanParametersCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)scanParametersCmd.header.Status);

	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetCommonScanCriteria(OUT)"));
	return status;
}

//************************************************
// Gold - Set Security Config
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_SetSecurityConfig( wmx_SecurityConfig_t securityConfig )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	SetLinkParameters_type setLinkParametersCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetSecurityConfig(wmx_SecurityConfig_t securityConfig)"));
	responseBufferSize = wmx_GetMaxBufferSize_SetLinkParameters();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_SetLinkParameters(&setLinkParametersCmd);
	// TODO: Use correct ENUM
	setLinkParametersCmd.SecurityConfigType = L3L4_TLV_TYPE_SECURITY_CONFIG;
	switch(securityConfig)
	{
		case Enabled:
			setLinkParametersCmd.SecurityConfig = 1;
			break;
		default:
			break;
	}
	requestBufferSize = wmx_GetBufferSize_SetLinkParameters(setLinkParametersCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_SetLinkParameters((UINT8*)requestBuffer, setLinkParametersCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
		&responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_SetLinkParameters(&setLinkParametersCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)setLinkParametersCmd.header.Status);

	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetSecurityConfig(OUT)"));
	return status;
}

//************************************************
// Gold - Set BS Selection Criteria
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_INT_CALL_CONV wmx_SetBSSelectionCriteria( UINT32 numOfCriteria, wmx_pBSSelectionCriteria_t criteria )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	SetLinkParameters_type setLinkParametersCmd;
	L4BUFMAN_Status_t res;
	UINT32 i;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetBSSelectionCriteria(UINT32 numOfCriteria, wmx_pBSSelectionCriteria_t criteria)"));
	responseBufferSize = wmx_GetMaxBufferSize_SetLinkParameters();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_SetLinkParameters(&setLinkParametersCmd);
	for ( i = 0; i < numOfCriteria; i++ )
	{
		setLinkParametersCmd.BSCritieriaList[i].BSCritieriaListType = L3L4_TLV_TYPE_BS_CRITERIA;
		wmxNds_CopyNBytes(sizeof(wmx_BSIDCriterion_t), setLinkParametersCmd.BSCritieriaList[i].BSID_Criterion, criteria[i].BSID_Criterion);
		wmxNds_CopyNBytes(sizeof(wmx_BSIDCriterion_t), setLinkParametersCmd.BSCritieriaList[i].BSID_CriterionMask, criteria[i].BSID_CriterionMask);
		setLinkParametersCmd.BSCritieriaList[i].HomeOperator = criteria[i].HomeOperator;
	}
	requestBufferSize = wmx_GetBufferSize_SetLinkParameters(setLinkParametersCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_SetLinkParameters((UINT8*)requestBuffer, setLinkParametersCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
		&responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_SetLinkParameters(&setLinkParametersCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)setLinkParametersCmd.header.Status);

	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_SetBSSelectionCriteria(OUT)"));
	return status;
}

//************************************************
// Silver - Get the current system state
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetSystemState( wmx_pSystemState_t systemState )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	GetState_type getStateCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetSystemState(wmx_pSystemState_t systemState)"));
	if ( NULL == systemState )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	responseBufferSize = wmx_GetMaxBufferSize_GetState();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_GetState(&getStateCmd);
	requestBufferSize = wmx_GetBufferSize_GetState(getStateCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;

	res = wmx_Set_GetState((UINT8*)requestBuffer, getStateCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_GetState(&getStateCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)getStateCmd.header.Status);
	if ( WMX_ST_OK != wmxNds_DriverSystemStateToUserSystemState(systemState, getStateCmd.SystemState) )
	{
		status = WMX_ST_FAIL;
	}
	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetSystemState(OUT)"));
	return status;
}

//************************************************
// Silver - Get the current connection state
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectionState( wmx_pConnectionState_t connectionState )
{
	wmx_SystemState_t systemState;
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetConnectionState(wmx_pConnectionState_t connectionState)"));
	status = wmx_GetSystemState( &systemState );
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	wmxNds_UserSystemStateToUserConnectionState(connectionState, systemState);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetConnectionState(OUT)"));
	return status;
}

//************************************************
// Silver - Get the link status
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetLinkStatus( wmx_pLinkStatus_t linkStatus	)
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	GetLinkStatus_type getLinkStatusCmd;
	L4BUFMAN_Status_t res;

	// Request Fields
	L4Buffer request;
	char *requestBuffer;
	UINT32 requestBufferSize;

	// Response Fields
	L4Buffer response;
	UINT32 responseID;
	char *responseBuffer;
	UINT32 responseBufferSize;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetLinkStatus(wmx_pLinkStatus_t linkStatus)"));
	
	if ( NULL == linkStatus )
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	responseBufferSize = wmx_GetMaxBufferSize_GetLinkStatus();
	responseBuffer = (char*)malloc(responseBufferSize);
	if (NULL == responseBuffer)
	{
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	response.buffer = (UINT8*)responseBuffer;
	response.bufferLength = responseBufferSize;

	wmx_Init_GetLinkStatus(&getLinkStatusCmd);
	requestBufferSize = wmx_GetBufferSize_GetLinkStatus(getLinkStatusCmd);
	requestBuffer = (char*)malloc(requestBufferSize);
	if (NULL == requestBuffer)
	{
		free(requestBuffer);
		free(responseBuffer);
		return WMX_ST_FAIL;
	}
	request.buffer = (UINT8*)requestBuffer;
	request.bufferLength = requestBufferSize;
	
	res = wmx_Set_GetLinkStatus((UINT8*)requestBuffer, getLinkStatusCmd);
	if (L4BUFMAN_ST_OK != res)
	{
		free(request.buffer);
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_L4_PROXY, L4_PROXY_OPCODE_SEND_L4_OPCODE, request.buffer, request.bufferLength, 
											  &responseID, response.buffer, (UINT32*)&(response.bufferLength) );
	free(request.buffer);
	if (L5_RESULT_OK != l5Result)
	{
		free(response.buffer);
		return WMX_ST_PIPE_FAILURE;
	}
	if ( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		free(response.buffer);
		return (wmx_Status_t)responseID;
	}
	res = wmx_Get_GetLinkStatus(&getLinkStatusCmd, (UINT8*)responseBuffer);
	if (L4BUFMAN_ST_OK != res)
	{
		free(response.buffer);
		return WMX_ST_FAIL;
	}
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)getLinkStatusCmd.header.Status);
	linkStatus->cinr = getLinkStatusCmd.RxCinr;
	linkStatus->frequency = getLinkStatusCmd.CenterFrequency;
	linkStatus->linkQuality = getLinkStatusCmd.LinkQuality;
	linkStatus->upLinkSpeed = getLinkStatusCmd.UpLinkSpeed; // TODO
	linkStatus->downLinkSpeed = getLinkStatusCmd.DownLinkSpeed; // TODO
	linkStatus->power = getLinkStatusCmd.TxPower;
	linkStatus->rssi = getLinkStatusCmd.RxRssi;
	linkStatus->time = getLinkStatusCmd.ConnectionTime;

	free(response.buffer);
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, (L"wmx_Status_t wmx_GetLinkStatus(OUT)"));
    
	return status;
}

//************************************************
// Internal - Translate Driver System State to User System State
//************************************************
wmx_Status_t wmxNds_DriverSystemStateToUserSystemState(wmx_pSystemState_t systemState, UINT16 driverState)
{
	wmx_Status_t status = WMX_ST_OK;
	// TODO: add following State enums
	//	Scan,
	//	Connecting,
	//	Disconnecting
	switch (driverState)
	{
	case E_SYSTEM_STATE_INIT:
		*systemState = Init;
		break;
	case E_SYSTEM_STATE_READY:
		*systemState = Ready;
		break;
	case E_SYSTEM_STATE_OUT_OF_ZONE:
		*systemState = OOZ;
		break;
	case E_SYSTEM_STATE_STANDBY:
		*systemState = Standby;
		break;
	case E_SYSTEM_STATE_WIMAX_CONNECTED:
		*systemState = WimaxConnected;
		break;
	case E_SYSTEM_STATE_DATA_PATH_CONNECTED:
		*systemState = DataPathConnected;
		break;
	case E_SYSTEM_STATE_IDLE:
		*systemState = Idle;
		break;
	case E_SYSTEM_STATE_SLEEP_ACTIVE:
		*systemState = SleepActive;
		break;
	case E_SYSTEM_STATE_SCAN:
		*systemState = Scan;
		break;
	default:
		status = WMX_ST_FAIL;
		break;
	}
	return status;
}

//************************************************
// Internal - Translate User System State to User Connection State
//************************************************
void wmxNds_UserSystemStateToUserConnectionState(wmx_pConnectionState_t connectionState, wmx_SystemState_t systemState)
{
	switch (systemState)
	{
		case Init:
			*connectionState = RfOff;
			break;
		case Ready:
		case Standby:
		case Connecting:
		case WimaxConnected:
		case Idle:
		case SleepActive:
		case Disconnecting:
			*connectionState = Disconnected;
			break;
		case OOZ:
			*connectionState = OutOfZone;
			break;
		case DataPathConnected:
			*connectionState = Connected;
			break;
		default:
			*connectionState = Disconnected;
			break;
	}
}

//************************************************
// Internal - Translate Driver Scan Status to User Scan Status
//************************************************
void wmxNds_DriverScanStatusToUserScanStatus(wmx_pScanStatus_t scanStatus, UINT8 driverScanStatus)
{
	switch (driverScanStatus)
	{
	case E_SCAN_STATUS_DONE:
		*scanStatus = ScanSuccessful;
		break;
	case E_SCAN_STATUS_SCANING:
		*scanStatus = (wmx_ScanStatus_t)0;
		break;
	case E_SCAN_STATUS_FAILURE:
		*scanStatus = (wmx_ScanStatus_t)0;
	    break;
	default:
		break;
	}
}

//************************************************
// Internal - Scan Results Arrived internal analysis function
//************************************************
void wmxNds_ScanResultsArrived(void *scanResults)
{
	ReportScanResults_type scanResultsReport;
	wmx_pNAP_t naps;
	int numOfNAPs = 0;
	wmx_ScanStatus_t scanStatus;
	L4BUFMAN_Status_t res;
	int i = 0;

	if ( numOfGoldScanUpdateRegs > 0 )
	{
		res = wmx_Get_ReportScanResults(&scanResultsReport, (UINT8*)scanResults );
		if ( L4BUFMAN_ST_OK != res)
		{
			return;
		}
		if ( scanResultsReport.ScanStatusType == L3L4_TLV_TYPE_SCAN_STATUS )
		{
			if (NULL != ScanUpdateCB )
			{
				while ( scanResultsReport.ScanResultList[numOfNAPs].ScanResultListType != INVALID_OPCODE )
				{
					numOfNAPs++;
				}
				naps = (wmx_pNAP_t)malloc( numOfNAPs * sizeof(wmx_NAP_t) );
				if ( NULL != naps )
				{
					for ( i = 0; i < numOfNAPs; i++)
					{
						naps[i].bestRssi = scanResultsReport.ScanResultList[i].BestRssi;
						naps[i].numOfBSs = scanResultsReport.ScanResultList[i].NumOfLinks;
						//naps[i].napID[0] = scanResultsReport.ScanResultList[i].NetworkId[0];
						//naps[i].napID[1] = scanResultsReport.ScanResultList[i].NetworkId[1];
						//naps[i].napID[2] = scanResultsReport.ScanResultList[i].NetworkId[2];
						wmxNds_NAPtoNAP(naps[i].napID, scanResultsReport.ScanResultList[i].NetworkId);
					}
					if ( NULL != ScanUpdateCB )
					{
						ScanUpdateCB(numOfNAPs, naps);
					}
					free(naps);
				}
			}

			if ( NULL != ScanCompletedCB )
			{
				wmxNds_DriverScanStatusToUserScanStatus(&scanStatus, scanResultsReport.ScanStatus);
				if ( (scanStatus != 0) && (NULL != ScanCompletedCB) )
				{
					ScanCompletedCB(scanStatus);
				}
			}
		}
	}
}

//************************************************
// Internal - System State Update Arrived internal analysis function
//************************************************
void wmxNds_SystemStateArrived(wmx_pSystemState_t systemState)
{
	wmx_ConnectionState_t connectionState;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, (L"System State Arrived: %d", systemState));
	if ( NULL != SystemStateUpdateCB )
	{
		SystemStateUpdateCB(*systemState);
	}
	if ( NULL != ConnectionStateUpdateCB )
	{	
		wmxNds_UserSystemStateToUserConnectionState(&connectionState, *systemState);
		if ( connectionState != currentConnectionState )
		{
			currentConnectionState = connectionState;
			ConnectionStateUpdateCB(connectionState);
		}
	}
}

//************************************************
// Internal - Driver System State Update Arrived internal analysis function
//************************************************
BOOL wmxNds_DriverSystemStateArrived(void *driverState, wmx_pSystemState_t systemState)
{
	ReportState_type stateReport;
	wmx_SystemState_t intSystemState;
	wmx_Status_t status;
	L4BUFMAN_Status_t res;

	if ( numOfSystemStateRegs > 0 )
	{
		res = wmx_Get_ReportState(&stateReport, (UINT8*)driverState);
		if ( L4BUFMAN_ST_OK != res)
		{
			return FALSE;
		}
		if ( stateReport.SystemStateType == L3L4_TLV_TYPE_SYSTEM_STATE )
		{
			status = wmxNds_DriverSystemStateToUserSystemState(&intSystemState, stateReport.SystemState);
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, (L"System State Arrived: %d", systemState));
			if (WMX_ST_OK == status)
			{
				*systemState = intSystemState;
				if ( isConnected == TRUE )
				{
					if (intSystemState != DataPathConnected)
					{
						isConnected = FALSE;
						OSAL_set_event(g_disconnectAvailableEvent);
					}
					else
					{
						OSAL_set_event(g_disconnectAvailableEvent);
					}
				}
				if (intSystemState == DataPathConnected)
				{
					g_connectStatus = UserConnectSuccessful;
					isConnected = TRUE;
					OSAL_set_event(g_connectStatusAvailableEvent);
				}
				if ( (stateReport.ReportStateReason == E_REPORT_STATE_REASON_FAIL_TO_CONNECT_DATA_PATH) ||
					(stateReport.ReportStateReason == E_REPORT_STATE_REASON_FAIL_TO_CONNECT_TO_NW)	)
				{
					g_connectStatus = UserConnectFailed;
					OSAL_set_event(g_connectStatusAvailableEvent);
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

//************************************************
// Internal - Copy N Bytes
//************************************************
void wmxNds_CopyNBytes(UINT32 bytesNum, UINT8 *target, UINT8 *source)
{
	UINT32 i;
	for ( i = 0; i < bytesNum; i++ )
	{
		if ( NULL != source )
		{
			target[i] = source[i];
		} 
		else
		{
			target[i] = 0;
		}
	}
}

//************************************************
// Internal - Copy NAP ID to NAP ID
//************************************************
void wmxNds_NAPtoNAP( wmx_NAPid_t target, wmx_NAPid_t source )
{
	wmxNds_CopyNBytes(sizeof(wmx_NAPid_t), target, source);
}