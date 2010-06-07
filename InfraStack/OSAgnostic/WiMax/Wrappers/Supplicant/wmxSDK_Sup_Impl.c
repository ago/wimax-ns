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
#include "L3L4TlvTypes.h"
#include "L3L4CommonDefines.h"
#include "wmxSDK_Sup_CtrlAgent.h"
#include "wmxSDK_Sup_Ctrl.h"
#include "wmxSDK_Sup_L5.h"
#include "wmxSDK_Sup_1.h"
#include "wmxSDK_Sup_4.h"


#include "L5Common.h"
#include "WrappersUtils.h"

#include "Messenger.h"
#include "TraceModule.h"
#include "L4MsgProxyIf.h"

#include "NDnSAgent.h"


typedef unsigned char u8;
#define TLS_IMPLEMENTATION Arm1

/* the supplicant calls procedures in this file, 
so we use symlink to actual supplicant tls.h */
#ifndef WPA_OPEN_SOURCE
#include "tls.h"
#else
#include "tls-wpa.h"
#endif

extern void	(*wpa_logproc_ptr)(int level, char *fmt, ...);
static void __keep_silence(void) {}
#ifdef NATIVE_WINDOWS
#define SUPPLICANT_LOG	(!wpa_logproc_ptr) ? __keep_silence() : wpa_logproc_ptr
#else

#ifdef _WIMAX_SDK_
#define SUPPLICANT_LOG	__keep_silence() 
#else
#define SUPPLICANT_LOG	wpa_logproc_ptr
#endif

#endif

#ifndef WPA_OPEN_SOURCE
/* temporary, remove*/
tls_functions_table_t *HardwareTlsImplementation = &Arm1_tls_functions_table;
tls_functions_table_t *SoftwareTlsImplementation = NULL;
#endif

//************************************************
// Function declarations
//************************************************
void wmxSup_InternalHandler( UINT32 internalRequestID, void *buffer, UINT32 bufferLength );
int CreateSupMsg(UINT32 opCode, UINT32 bufferLength, char *buffer, char **msg);
wmx_NSPid_t Ndns_GetConnectingNSPTemp();

//************************************************
// Internal Definitions
//************************************************

#define NO_PARAM			0

//************************************************
// Connection Parameters to L5 Layer
//************************************************
LONG numOfInits = 0;
static L5_CONNECTION l5ConnID = NULL;
static tL5DispatcherFunctions *pFuncs = NULL;


//************************************************
// Callback functions
//************************************************
//Gold
wmx_pEapKeyRequestCB_t EapKeyRequestCB = NULL;
wmx_pAlternativeEapSuccessCB_t AlternativeEapSuccessCB = NULL;
wmx_pEapRequestAvailableCB_t EapRequestAvailableCB = NULL;
wmx_pEapRestartRequestCB_t EapRestartRequestCB = NULL;
//PVC
wmx_pEventReportCB_t EventReportCB = NULL;

extern tUtilityFunctions *pUtils;
//************************************************
// Internal callback handlers
//************************************************
void wmxSup_EapRestartArrived()
{
	if (EapRestartRequestCB != NULL)
	{
		EapRestartRequestCB();
	}
}

void wmxSup_EapKeyRequestArrived()
{
	if (EapKeyRequestCB != NULL)
	{
		EapKeyRequestCB();
	}
}

void wmxSup_AlternativeEapSuccessArrived()
{
	if (AlternativeEapSuccessCB != NULL)
	{
		AlternativeEapSuccessCB();
	}
}

void wmxSup_EapRequestAvailableArrived(void *pvSentBuffer, UINT32 cbSentBufferSize)
{
	wmx_Status_t status;			
	ReportEapRequest_type reportEapRequest;
	UNREFERENCED_PARAMETER(cbSentBufferSize);

	if (EapRequestAvailableCB != NULL)
	{
		// Parse the message and call the callback function
		if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, (GENERIC_STRCT)&reportEapRequest, ReportEapRequest_Funcs, &status ) != WMX_ST_OK )
		{
			return;
		}

		// TODO: Make sure that the length is only the message length
		EapRequestAvailableCB((wmx_EapMsgLength_t)(reportEapRequest.EapRequestMessage.ActualLen), (wmx_pEapMessage_t)reportEapRequest.EapRequestMessage.BufferArr);

		//status = L4BM_Get_ReportEapRequest(&reportEapRequest, (UINT8*)pvSentBuffer);
		//if( status == L4BUFMAN_ST_OK )
		//{
		//	// TODO: Make sure that the length is only the message length
		//	EapRequestAvailableCB((wmx_EapMsgLength_t)reportEapRequest.EapRequestMessageLength, (wmx_pEapMessage_t)reportEapRequest.EapRequestMessage);
		//}		
	}
}

void wmxSup_EventReportArrived(void *pvSentBuffer, UINT32 cbSentBufferSize)
{
	UNREFERENCED_PARAMETER(cbSentBufferSize);
	if (EventReportCB != NULL)
	{	// TODO: check if this the right cast		
		wmx_SupEvent_t event = *((wmx_pSupEvent_t)pvSentBuffer);		

		EventReportCB(event);
	}
}

//************************************************
//  
//************************************************
wmx_Status_t wmxSup_InitL5()
{
	L5_RESULT l5status;
	pFuncs = GetL5Funcs();
	if (NULL == pFuncs)
	{
		return WMX_ST_PIPE_FAILURE;
	}

	// Connect L5 and through it to AppSrv. Gain L5ConnID.
	l5status = pFuncs->pfnConnectEx(
									L5_TARGET_DYNAMIC,
									wmxSup_MessagesHandler, 
									wmxSup_EventHandler,
									NULL,
									THREAD_ID_DEFAULT,
									&l5ConnID	);

	if ((L5_RESULT_OK != l5status) || (NULL == l5ConnID))
	{
		return WMX_ST_PIPE_FAILURE;
	}
	return WMX_ST_OK;
}

//************************************************
//  
//************************************************
void wmxSup_FinalizeL5()
{
	pFuncs->pfnDisconnect(l5ConnID);
}

//********************************************************************************
//  Receive indications and call the registered callbacks of the supplicant agent
//********************************************************************************
void wmxSup_MessagesHandler(L5_CONNECTION Conn,
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
	L3L4CompleteHeader_type *l3L4CompleteHeader;

	l3L4CompleteHeader = (L3L4CompleteHeader_type*)pvSentBuffer;

	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbResponseBufferSize);
	UNREFERENCED_PARAMETER(pvResponseBuffer);
	UNREFERENCED_PARAMETER(pdwResponseMessageID);
	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(Conn);

	switch (dwSentMessageID)
	{
		//GOLD, SILVER
	case L4_PROXY_OPCODE_STATUS_INDICATION_ARRIVED:
	case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
		switch (l3L4CompleteHeader->Type)
		{
		case L3_L4_OPCODE_REPORT_EAP_REQUEST:
			pUtils->tpfnPostRequest(	MEDIUM,
									L3_L4_OPCODE_REPORT_EAP_REQUEST, 
									pvSentBuffer, 
									cbSentBufferSize,
									wmxSup_InternalHandler	);			
			break;
		case L3_L4_OPCODE_REPORT_EAP_RESTART:
		case L3_L4_OPCODE_REPORT_ALT_ACCEPT:			
		case L3_L4_OPCODE_REPORT_KEY_REQUEST:
			pUtils->tpfnPostRequest(	MEDIUM,
									l3L4CompleteHeader->Type, 
									NULL, 
									0,
									wmxSup_InternalHandler	);
			break;		
		case L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS:
			SUPPLICANT_LOG(1, "Received BEK (%d bytes)", l3L4CompleteHeader->Length);
			break;
		default:
			TRACE(TR_MOD_SUPPLICANT_WRAPPER, TR_SEV_ERR,"Unknown message arrived");
			break;
		}
		break;
		//PVC
	case SUP_OPCODE_INDICATION_ARRIVED:
		switch (((pSUP_MESSAGE_HEADER)pvSentBuffer)->opcode)
		{
		case SUP_OPCODE_IND_EVENT:
			EventReportCB(*(wmx_pSupEvent_t)(((pSUP_MESSAGE)pvSentBuffer)->buf));
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
void wmxSup_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext)
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(eEvent);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);
}

void wmxSup_InternalHandler( UINT32 internalRequestID, void *buffer, UINT32 bufferLength )
{

	switch (internalRequestID)
	{
	case L3_L4_OPCODE_REPORT_EAP_REQUEST:
		wmxSup_EapRequestAvailableArrived(buffer, bufferLength);
		break;
	case L3_L4_OPCODE_REPORT_ALT_ACCEPT:
		wmxSup_AlternativeEapSuccessArrived();
		break;
	case L3_L4_OPCODE_REPORT_KEY_REQUEST:
		wmxSup_EapKeyRequestArrived();
		break;
	case L3_L4_OPCODE_REPORT_EAP_RESTART:
		
		// This indication exists because of the following:
		// L3 retries to connect within its 20 seconds of link down timer might be caused of Authentication problem.
		// Thus in this case and before any additional authentication trial, the SUPPLICANT SHALL BE RESTARTED.
		// Commented out since the new implementation of following NDnSAgent_SetConfigToSupplicant starts with calling to reset.
		//wmxSup_EapRestartArrived();



		// After resetting the supplicant we shall reconfigure it from the following reasons:
		// 1. On every EAP TTLS trial the random part of the NAI shall be refreshed.
		// 2. It shall be able to count TTLS trials, to know when to fall back to LTS.
		L4C_CallHandleRobustConnect(TRUE);
		break;
	//case L3_L4_OPCODE_REPORT_CRED_REQUEST:
	//	wmxSup_EventReportArrived(buffer, bufferLength);
	//	break;
	default:
		TRACE(TR_MOD_SUPPLICANT_WRAPPER, TR_SEV_ERR,"Unknown message arrived");
		break;
	}
}

////************************************************
////  
////************************************************
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSup_Init()
//{
//	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfInits) )
//	{		
//		return wmxSup_InitL5();
//	}
//	return WMX_ST_OK;
//}
//
////************************************************
////  
////************************************************
//void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSup_Finalize()
//{
//	if ( LAST_INIT == OSAL_atomic_decrement(&numOfInits) )
//	{
//		wmxSup_FinalizeL5();		
//	}
//
//	OSAL_atomic_compareExchange(&numOfInits, LAST_INIT, LAST_INIT - 1);
//}

//************************************************
//  
//************************************************
wmx_Status_t wmxSup_InitAgent()
{
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfInits) )
	{
		return wmxSup_InitL5();
	}
	return WMX_ST_OK;
}

//************************************************
//  
//************************************************
void wmxSup_FinalizeAgent()
{
	if ( LAST_INIT == OSAL_atomic_decrement(&numOfInits) )
	{
		wmxSup_FinalizeL5();
	}

	OSAL_atomic_compareExchange(&numOfInits, LAST_INIT, LAST_INIT - 1);
}

//wmx_Status_t wmxSup_GetWmxStatus(void *l4Buffer)
//{
//	L3L4CompleteHeader_type *l3L4CompleteHeader;
//	wmx_Status_t status;
//
//	l3L4CompleteHeader = (L3L4CompleteHeader_type*)l4Buffer;
//
//	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)(l3L4CompleteHeader->Status));
//
//	return status;
//}

//************************************************************
// Create a L4 Message Struct and return its allocated size.
//************************************************************
//UINT32 wmxSup_CreateL4Msg(UINT32 opCode, L4Buffer *l4Buffer, L4Buffer *l4MessageDetails, char l4MessageDetails2)
//{
//	UINT size = 0;
//	SendEapResponse_type sendEapResponse;
//	SetEapSuccess_type setEapSuccess;		
//	SetEapFail_type setEapFail;
//	SetEapKey_type setEapKey;
//
//	// Set the structs fields according to the opcode
//	switch (opCode)
//	{			
//	case SUPP_OPCODE_CMD_EAP_RESPONSE:
//		// TODO: Check the size issue
//		sendEapResponse.EapResponseMessageType = L3L4_TLV_TYPE_EAP_RESPONSE;
//		memcpy(sendEapResponse.EapResponseMessage, l4MessageDetails->buffer, l4MessageDetails->bufferLength);
//		sendEapResponse.EapResponseMessageLength = (short)l4MessageDetails->bufferLength;
//		size = L4BM_GetBufferSize_SendEapResponse(sendEapResponse);
//		l4Buffer->buffer = (UINT8*)malloc(size);
//
//		L4BM_Set_SendEapResponse(l4Buffer->buffer, sendEapResponse);
//		break;
//	case SUPP_OPCODE_CMD_EAP_SUCCESS:		
//		memset(&setEapSuccess, 0, sizeof(SetEapSuccess_type));
//		size = L4BM_GetBufferSize_SetEapSuccess(setEapSuccess);
//		l4Buffer->buffer = (UINT8*)malloc(size);
//
//		L4BM_Set_SetEapSuccess(l4Buffer->buffer, setEapSuccess);
//		break;
//	case SUPP_OPCODE_CMD_EAP_FAIL:
//		memset(&setEapFail, 0, sizeof(SetEapFail_type));
//		size = L4BM_GetBufferSize_SetEapFail(setEapFail);
//		l4Buffer->buffer = (UINT8*)malloc(size);
//
//		L4BM_Set_SetEapFail(l4Buffer->buffer, setEapFail);
//		break;
//	case SUPP_OPCODE_CMD_EAP_KEY:			
//		setEapKey.EapKeyMskType = L3L4_TLV_TYPE_SET_EAP_KEY_MSK;
//		memcpy(setEapKey.EapKeyMsk, l4MessageDetails->buffer, l4MessageDetails->bufferLength);
//		setEapKey.EapKeyMskLength = (short)l4MessageDetails->bufferLength;
//		setEapKey.EapKeyValidType = L3L4_TLV_TYPE_SET_EAP_KEY_VALID;
//		setEapKey.EapKeyValid = l4MessageDetails2;
//
//		size = L4BM_GetBufferSize_SetEapKey(setEapKey);
//		l4Buffer->buffer = (UINT8*)malloc(size);
//
//		L4BM_Set_SetEapKey(l4Buffer->buffer, setEapKey);
//		break;			
//	default:
//		break;
//	}
//
//	l4Buffer->bufferLength = size;
//	return size;
//}

wmx_Status_t wmx_CmdSendEapResponse ( wmx_EapMsgLength_t eapMsgLen, wmx_pEapMessage_t pEapMsg)
{
	wmx_Status_t driver_st, send_st;
	SendEapResponse_type sendEapResponse;

	sendEapResponse.EapResponseMessage.Type = L3L4_TLV_TYPE_EAP_RESPONSE;
	memcpy(sendEapResponse.EapResponseMessage.BufferArr, (UINT8*)pEapMsg, eapMsgLen);
	sendEapResponse.EapResponseMessage.ActualLen = (short)eapMsgLen;

	send_st = wmx_SendL4Command( &sendEapResponse, SendEapResponse_Funcs, *pFuncs, l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	return WMX_ST_OK;
}

wmx_Status_t wmx_SetEapSuccess()
{
	wmx_Status_t driver_st, send_st;
	SetEapSuccess_type setEapSuccess;

	memset(&setEapSuccess, 0, sizeof(SetEapSuccess_type));

	send_st = wmx_SendL4Command( &setEapSuccess, SetEapSuccess_Funcs, *pFuncs, l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	return WMX_ST_OK;
}

wmx_Status_t wmx_SetEapFail()
{
	wmx_Status_t driver_st, send_st;
	SetEapFail_type setEapFail;

	memset(&setEapFail, 0, sizeof(SetEapFail_type));

	send_st = wmx_SendL4Command( &setEapFail, SetEapFail_Funcs, *pFuncs, l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	return WMX_ST_OK;
}

wmx_Status_t wmx_SetEapKey ( wmx_EapKeyLength_t eapKeyLen, wmx_pEapKey_t pEapKey)
{
	wmx_Status_t driver_st, send_st;
	SetEapKey_type setEapKey;

	setEapKey.EapKeyMsk.Type = L3L4_TLV_TYPE_SET_EAP_KEY_MSK;
	if (eapKeyLen > 0) // supplicant has a key
	{
		memcpy(setEapKey.EapKeyMsk.EapKeyMskArr, (UINT8*)pEapKey, (short)eapKeyLen);		
		setEapKey.EapKeyValid.Type = L3L4_TLV_TYPE_SET_EAP_KEY_VALID;
		setEapKey.EapKeyValid.value = TRUE;
	}
	else // suplicant don't have a key - all other fields are ignored
	{
		setEapKey.EapKeyValid.value = FALSE;
	}
#ifdef WPA_OPEN_SOURCE
	setEapKey.EapKeyValid.value = 3;
#endif

	send_st = wmx_SendL4Command( &setEapKey, SetEapKey_Funcs, *pFuncs, l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	return WMX_ST_OK;
}

wmx_Status_t wmx_ResetSupplicant()
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	int size = 0;
	UINT32 responseID;	
	
	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_SUPPLICANT, SUP_OPCODE_RESET, NULL, (UINT32)size, &responseID, NULL, NULL );
	if (L5_RESULT_OK != l5Result)
	{
		return WMX_ST_PIPE_FAILURE;
	}
	status = (wmx_Status_t)responseID;
	if (WMX_ST_OK != status)
	{
		return status;
	}	
	return status;
}

// Internal function which creates a cred. set msg and sends it to the Supplicant Agent
wmx_Status_t wmx_SetCredInternal( SUP_AGENT_CRED_OPCODE opcode, void *pvBuffer, UINT32 bufferLen )
{
	L5_RESULT l5Result;
	wmx_Status_t status;
	char *buf;
	int size = 0;
	UINT32 responseID;
	//UINT32 responseSize;
	//void *responseBuffer = NULL;

	size = CreateSupMsg(opcode, bufferLen, (char*)pvBuffer, &buf);
	if (size < 0)
	{
		return WMX_ST_FAIL;
	}

	l5Result = pFuncs->pfnSendReceiveMessage( l5ConnID, L5_TARGET_SUPPLICANT, SUP_OPCODE_SET, buf, (UINT32)size, &responseID, NULL, NULL );
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
	return status;
}

wmx_Status_t wmx_SetIdentity( wmx_pNAI_t identity )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_IDENTITY, identity, (UINT32)OSAL_strnlen(identity, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetAnonymousIdentity( wmx_pNAI_t identity )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_ANONYMOUS_IDENTITY, identity, (UINT32)OSAL_strnlen(identity, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetPassword( wmx_pUserPassword_t password )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_PASSWORD, password, (UINT32)OSAL_strnlen(password, MAX_STRING_VALIDATE) + 1);
}

wmx_Status_t wmx_SetEapMethod( wmx_EapMathod_t eapMethod )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_EAP_METHOD, &eapMethod, sizeof(wmx_EapMathod_t) );
}

wmx_Status_t wmx_SetPhase2Method( wmx_Phase2Mathod_t phase2Method )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_PHASE2_METHOD, &phase2Method, sizeof(wmx_Phase2Mathod_t) );
}

wmx_Status_t wmx_SetTlsCaCert( wmx_pCertificatePath_t path )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_CA_CERT, path, (UINT32)OSAL_strnlen((const char*)path, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetTlsClientCert( wmx_pCertificatePath_t path )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_CLIENT_CERT, path, (UINT32)OSAL_strnlen((const char*)path, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetTlsPrivateKey( wmx_pCertificatePath_t path )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_PRIVATE_KEY, path, (UINT32)OSAL_strnlen((const char*)path, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetTlsCaCert2( wmx_pCertificatePath_t path )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_CA_CERT2, path, (UINT32)OSAL_strnlen((const char*)path, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetTlsClientCert2( wmx_pCertificatePath_t path )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_CLIENT_CERT2, path, (UINT32)OSAL_strnlen((const char*)path, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetTlsPrivateKey2( wmx_pCertificatePath_t path )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_PRIVATE_KEY2, path, (UINT32)OSAL_strnlen((const char*)path, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetPin( wmx_pPin_t pin )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_PIN, pin, (UINT32)OSAL_strnlen(pin, MAX_STRING_VALIDATE) + 1 );
}

wmx_Status_t wmx_SetTlsMaxSize( wmx_TlsMaxSize_t len )
{
	return wmx_SetCredInternal( SUP_OPCODE_SET_TLS_MAX_SIZE, &len, sizeof(wmx_TlsMaxSize_t) );
}

wmx_Status_t wmx_EnableSupplicant( BOOL enable)
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 action;

	if (enable)
	{
		action = SUP_OPCODE_ENABLE;
	}
	else
	{
		action = SUP_OPCODE_DISABLE;
	}

	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
		L5_TARGET_SUPPLICANT, 
		action, 
		NULL, 
		0, 
		&responseID, 
		NULL,
		NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;	

	return status;
}


wmx_Status_t wmx_RegisterEapRequestAvailableCB(wmx_pEapRequestAvailableCB_t pEapRequestAvailableCB)
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// It is not allowed to register twice to the same callback
	if ( NULL != EapRequestAvailableCB || NULL == pEapRequestAvailableCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	EapRequestAvailableCB = pEapRequestAvailableCB;
	
	indID = L3_L4_OPCODE_REPORT_EAP_REQUEST;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_REGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status != WMX_ST_OK)
	{
		EapRequestAvailableCB = NULL;
	}

	return status;
}

wmx_Status_t wmx_UnregisterEapRequestAvailableCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// Check if a registration was done in the past
	if ( NULL == EapRequestAvailableCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}	

	indID = L3_L4_OPCODE_REPORT_EAP_REQUEST;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status == WMX_ST_OK)
	{
		EapRequestAvailableCB = NULL;
	}

	return status;
}

wmx_Status_t wmx_RegisterAlternativeEapSuccessCB(wmx_pAlternativeEapSuccessCB_t pAlternativeEapSuccessCB)
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// It is not allowed to register twice to the same callback
	if ( NULL != AlternativeEapSuccessCB || NULL == pAlternativeEapSuccessCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	AlternativeEapSuccessCB = pAlternativeEapSuccessCB;

	indID = L3_L4_OPCODE_REPORT_ALT_ACCEPT;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_REGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status != WMX_ST_OK)
	{
		AlternativeEapSuccessCB = NULL;
	}

	return status;
}

wmx_Status_t wmx_UnregisterAlternativeEapSuccessCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// Check if a registration was done in the past
	if ( NULL == AlternativeEapSuccessCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}	

	indID = L3_L4_OPCODE_REPORT_ALT_ACCEPT;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status == WMX_ST_OK)
	{
		AlternativeEapSuccessCB = NULL;
	}

	return status;
}

wmx_Status_t wmx_RegisterEapKeyRequestCB(wmx_pEapKeyRequestCB_t pEapKeyRequestCB)
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// It is not allowed to register twice to the same callback
	if ( NULL != EapKeyRequestCB || NULL == pEapKeyRequestCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	EapKeyRequestCB = pEapKeyRequestCB;

	indID = L3_L4_OPCODE_REPORT_KEY_REQUEST;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_REGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status != WMX_ST_OK)
	{
		EapKeyRequestCB = NULL;
	}

	return status;
}

wmx_Status_t wmx_UnregisterEapKeyRequestCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// Check if a registration was done in the past
	if ( NULL == EapKeyRequestCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}	

	indID = L3_L4_OPCODE_REPORT_KEY_REQUEST;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status == WMX_ST_OK)
	{
		EapKeyRequestCB = NULL;		
	}

	return status;
}

wmx_Status_t wmx_RegisterEapRestartRequestCB(wmx_pEapRestartRequestCB_t pEapRestartRequestCB)
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// It is not allowed to register twice to the same callback
	if ( NULL != EapRestartRequestCB || NULL == pEapRestartRequestCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	EapRestartRequestCB = pEapRestartRequestCB;

	indID = L3_L4_OPCODE_REPORT_EAP_RESTART;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_REGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status != WMX_ST_OK)
	{
		EapRestartRequestCB = NULL;
	}

	return status;
}

wmx_Status_t wmx_UnregisterEapRestartRequestCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	UINT32 indID;

	// Check if a registration was done in the past
	if ( NULL == EapRestartRequestCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}	

	indID = L3_L4_OPCODE_REPORT_EAP_RESTART;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
												L5_TARGET_L4_PROXY, 
												L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION, 
												&indID, 
												4, 
												&responseID, 
												NULL,
												NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status == WMX_ST_OK)
	{
		EapRestartRequestCB = NULL;		
	}

	return status;
}

//************************************************
// PVC - Register Supplicant Event Indication Callback
//************************************************
wmx_Status_t wmx_RegisterEventReportCB( wmx_pEventReportCB_t pEventReportCB )
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	RegisteredIndication indID;

	// It is not allowed to register twice to the same callback
	if ( NULL != EventReportCB || NULL == pEventReportCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}

	EventReportCB = pEventReportCB;

	indID = SUP_OPCODE_IND_EVENT;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
		L5_TARGET_SUPPLICANT, 
		SUP_OPCODE_REGISTER_INDICATION, 
		&indID, 
		sizeof(RegisteredIndication), 
		&responseID, 
		NULL,
		NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status != WMX_ST_OK)
	{
		EventReportCB = NULL;
	}

	return status;
}

//************************************************
// PVC - Unregister Supplicant Event Indication Callback
//************************************************
wmx_Status_t wmx_UnregisterEventReportCB()
{
	L5_RESULT l5Result;
	wmx_Status_t status;		
	UINT32 responseID;	
	RegisteredIndication indID;

	// Check if a registration was done in the past
	if ( NULL == EventReportCB)
	{
		return WMX_ST_ILLEGAL_OPERATION;
	}	

	indID = SUP_OPCODE_IND_EVENT;
	l5Result = pFuncs->pfnSendReceiveMessage(	l5ConnID, 
		L5_TARGET_SUPPLICANT, 
		SUP_OPCODE_UNREGISTER_INDICATION, 
		&indID, 
		sizeof(RegisteredIndication), 
		&responseID, 
		NULL,
		NULL );	

	status = wmx_L5ResultToWMXStatus(l5Result);

	if (status == WMX_ST_OK) status = (wmx_Status_t)responseID;
	if (status == WMX_ST_OK)
	{
		EventReportCB = NULL;		
	}

	return status;
}

//************************************************
// Create a Supplicant targeted message struct and return its allocated size.
//************************************************
int CreateSupMsg(UINT32 opCode, UINT32 bufferLength, char *buffer, char **msg)
{
	SUP_MESSAGE_HEADER supMsgHeader;
	int size = 0;

	supMsgHeader.opcode = opCode;
	supMsgHeader.bufferLength = bufferLength;

	*msg = (char*)malloc(sizeof(SUP_MESSAGE_HEADER) + supMsgHeader.bufferLength);
	if (*msg == NULL)
	{
		return -1;
	}
	size = sizeof(SUP_MESSAGE_HEADER) + supMsgHeader.bufferLength;
	memcpy(*msg, &supMsgHeader, sizeof(SUP_MESSAGE_HEADER));
	if (bufferLength > 0)
	{
		if (NULL != buffer)
		{
			memcpy(sizeof(SUP_MESSAGE_HEADER) + *msg, buffer, bufferLength);
		}
		else
		{
			memset(sizeof(SUP_MESSAGE_HEADER) + *msg, 0, bufferLength);
		}
	}
	return size;
}

#ifndef WPA_OPEN_SOURCE
void *wmx_GetTlsFunctionTable(int param)
{
	void *ft = NULL;
	switch (param)
	{
		case 1:
			ft = HardwareTlsImplementation;
			break;
		case 2:
			
			ft = SoftwareTlsImplementation;
			break;
		default:
			break;
	}
	return ft;
}
#endif //WPA_OPEN_SOURCE

#pragma warning (disable:4100)


typedef TLSOperationRequest_type  tTLSOperationRequest;

static wmx_Status_t SendTLSRequest(tTLSOperationRequest *pr, 
								 UINT32 Operation,
								 void *Context, 
								 void *Connection, 
								 UINT32 Parameter1,
								 UINT32 Parameter2,
								 const UINT8  *InputBuffer,
								 UINT32 InputBufferSize
								 )
{
	wmx_Status_t driver_st, send_st, res = WMX_ST_OK;
	L4BM_Init_TLSOperationRequest(pr);
	pr->Common.Type = L3L4_TLV_TYPE_TLS_OPERATION_DESCRIPTOR;
	pr->Common.Operation = Operation;
	pr->Common.Context = OSAL_PtrToLong(Context);		
	pr->Common.Connection = OSAL_PtrToLong(Connection);		
	pr->Common.LParameter1 = Parameter1;
	pr->Common.LParameter2 = Parameter2;
	SUPPLICANT_LOG(1, "SuppWrapper: sending down op. %d, ctx %X, conn %X, p1 %d, p2 %d", 
		pr->Common.Operation, pr->Common.Context, pr->Common.Connection, 
		pr->Common.LParameter1, pr->Common.LParameter2);
	if (InputBuffer)
	{
		pr->ExchangeBuffer.Type = L3L4_TLV_TYPE_TLS_EXCHANGE_BUFFER;
		pr->ExchangeBuffer.ActualLen = (UINT16)InputBufferSize;
		memcpy(pr->ExchangeBuffer.BufferArr, InputBuffer, InputBufferSize);
	}
	send_st = wmx_SendL4Command(pr, TLSOperationRequest_Funcs, *pFuncs, l5ConnID, &driver_st);
	
	if( send_st != WMX_ST_OK )
	{
		SUPPLICANT_LOG(1, "SuppWrapper: bad send status %d", send_st);
		res = send_st;
	}
	else if( driver_st != WMX_ST_OK )
	{
		SUPPLICANT_LOG(1, "SuppWrapper: bad driver status %d", driver_st);
		res = driver_st;
	}
	else if (pr->Common.Type != L3L4_TLV_TYPE_TLS_OPERATION_DESCRIPTOR)
	{
		SUPPLICANT_LOG(1, "SuppWrapper: No mandatory common descriptor received!");
		res = WMX_ST_FAIL;
	}
	else
	{
		SUPPLICANT_LOG(1, "SuppWrapper: received op. %d, ctx %X, conn %X, p1 %d, p2 %d", 
			pr->Common.Operation, pr->Common.Context, pr->Common.Connection, 
			pr->Common.LParameter1, pr->Common.LParameter2);
	}
	return res;
}


void * tls_init(const struct tls_config *conf)
{
	return (PVOID)((ULONG_PTR)1);
}
void   tls_deinit(void *tls_ctx)
{

}

struct tls_connection * tls_connection_init(void *tls_ctx)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
	res = SendTLSRequest(&r, ETLSOP_CONNECTION_INIT, tls_ctx, NULL, 0, 0, NULL, 0);
	if (!res && !r.Common.LParameter1)
	{
		SUPPLICANT_LOG(1, "SuppWrapper: Connection init => %lX", r.Common.Connection);
		return (void *)(INT_PTR)r.Common.Connection;
	}
	return NULL;
}

void tls_connection_deinit(void *tls_ctx, struct tls_connection *conn)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
	res = SendTLSRequest(&r, ETLSOP_CONNECTION_DEINIT, tls_ctx, conn, 0, 0, NULL, 0);
}

int tls_connection_established(void *tls_ctx, struct tls_connection *conn)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
	res = SendTLSRequest(&r, ETLSOP_GET_ESTABLISHED, tls_ctx, conn, 0, 0, NULL, 0);
	return (!res && r.Common.LParameter1) ? 1 : 0;
}

u8 * tls_connection_handshake(void *tls_ctx, struct tls_connection *conn,
								 const u8 *in_data, size_t in_len,
								 size_t *out_len, u8 **appl_data,
								 size_t *appl_data_len)
{
	tTLSOperationRequest r;
	u8 *data = NULL;
	wmx_Status_t res;
	res = SendTLSRequest(&r, ETLSOP_HANDSHAKE, tls_ctx, conn, 0, 0, in_data, (UINT32)in_len);
	if (!res && !r.Common.LParameter1)
	{
		/* reallocate data & appl_data, if returned */
		if (r.ExchangeBuffer.Type == L3L4_TLV_TYPE_TLS_EXCHANGE_BUFFER)
		{
			data = malloc(r.ExchangeBuffer.ActualLen + 1);
			memcpy(data, r.ExchangeBuffer.BufferArr, r.ExchangeBuffer.ActualLen);
			*out_len = r.ExchangeBuffer.ActualLen;
		}
		else
		{
			SUPPLICANT_LOG(1, "SuppWrapper: No data received!!!");
		}
		if (r.ExchangeBuffer.Type == L3L4_TLV_TYPE_TLS_APP_OUTPUT_BUFFER)
		{
			*appl_data = malloc(r.AppOutputBuffer.ActualLen + 1);
			memcpy(*appl_data, r.AppOutputBuffer.BufferArr, r.AppOutputBuffer.ActualLen);
			*appl_data_len = r.AppOutputBuffer.ActualLen;
		}
	}
	return data;
}

int tls_connection_prf(void *tls_ctx, struct tls_connection *conn, const char *label, int server_random_first, u8 *out, size_t out_len)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
#ifdef WPA_OPEN_SOURCE
	out_len = 0x40;
#endif
	size_t in_len = OSAL_strnlen(label, MAX_STRING_VALIDATE) + 1;
	res = SendTLSRequest(&r, ETLSOP_PRF, tls_ctx, conn, server_random_first, (UINT32)out_len, 
		(const UINT8 *)label, (UINT32)in_len);
	if (!res && !r.Common.LParameter1 && 
		r.ExchangeBuffer.Type == L3L4_TLV_TYPE_TLS_EXCHANGE_BUFFER && 
		out_len == r.ExchangeBuffer.ActualLen)
	{
		OSAL_memcpy_s(out, out_len,
			r.ExchangeBuffer.BufferArr, r.ExchangeBuffer.ActualLen);
		return 0;
	}
	return -1;
}

int tls_connection_encrypt(void *tls_ctx, struct tls_connection *conn,
						   const u8 *in_data, size_t in_len,
						   u8 *out_data, size_t out_len)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
	res	= (wmx_Status_t)SendTLSRequest(&r, ETLSOP_ENCRYPT, tls_ctx, conn, 0, (UINT32)out_len, in_data, (UINT32)in_len);
	if (!res && out_len >= r.ExchangeBuffer.ActualLen)
	{
		memcpy(out_data, r.ExchangeBuffer.BufferArr, r.ExchangeBuffer.ActualLen);
		return r.Common.LParameter1;
	}
	return -1;
}

int tls_connection_decrypt(void *tls_ctx, struct tls_connection *conn,
						   const u8 *in_data, size_t in_len,
						   u8 *out_data, size_t out_len)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
	res = (wmx_Status_t)SendTLSRequest(&r, ETLSOP_DECRYPT, tls_ctx, conn, 0, (UINT32)out_len, in_data, (UINT32)in_len);
	if (!res && out_len >= r.ExchangeBuffer.ActualLen)
	{
		memcpy(out_data, r.ExchangeBuffer.BufferArr, r.ExchangeBuffer.ActualLen);
		return r.Common.LParameter1;
	}
	return -1;
}


int    tls_get_errors(void *tls_ctx)
{
	return 0;
}



int tls_connection_resumed(void *tls_ctx, struct tls_connection *conn)
{
	return 0;
}

int tls_connection_get_failed(void *tls_ctx, struct tls_connection *conn)
{
	tTLSOperationRequest r;
	wmx_Status_t res;
	res = SendTLSRequest(&r, ETLSOP_GET_FAILED, tls_ctx, conn, 0, 0, NULL, 0);
	return (!res && r.Common.LParameter1) ? 1 : 0;
}

int tls_connection_get_read_alerts(void *tls_ctx, struct tls_connection *conn)
{
	return 0;
}

int tls_connection_get_write_alerts(void *tls_ctx, struct tls_connection *conn)
{
	return 0;
}

int tls_connection_get_keyblock_size(void *tls_ctx, struct tls_connection *conn)
{
	return -1;
}

unsigned int tls_capabilities(void *tls_ctx)
{
	return 0;
}

int tls_connection_ia_send_phase_finished(void *tls_ctx,
struct tls_connection *conn,
	int final,
	u8 *out_data, size_t out_len)
{
	return 0;
}

int tls_connection_ia_final_phase_finished(void *tls_ctx, struct tls_connection *conn)
{
	return -1;
}

int tls_connection_ia_permute_inner_secret(void *tls_ctx, struct tls_connection *conn, const u8 *key, size_t key_len)
{
	return -1;
}

int tls_set_master_secret_cb(void *tls_ctx, int (*cb)(void *tls_ctx, struct tls_set_master_secret *info, void *ctx), void *ctx)
{
	return -1;
}
int tls_connection_shutdown(void *tls_ctx, struct tls_connection *conn)
{
	return -1;
}

int tls_connection_set_params(void *tls_ctx, struct tls_connection *conn,
							  const struct tls_connection_params *params)
{
	int rc = 0; 

	if (params->client_cert)
	{
		const char *secondsideRootName = "rootcert.crt";
		char *p = strrchr(params->client_cert, OSAL_PATH_SEPARATOR);
		if (p)
		{
			size_t lpath;
			char *secondsideRoot;
			size_t secondsideRootNameLength = strlen(secondsideRootName);
			size_t secondsideRootSize = 0;
			p++; 
			lpath = p - params->client_cert;
			secondsideRootSize = lpath + secondsideRootNameLength + 10;
			secondsideRoot = calloc(secondsideRootSize, 1);//Zero-ing memory
			if (secondsideRoot)
			{
				FILE *f = NULL;
				
				memcpy(secondsideRoot, params->client_cert, lpath);
				if (OSAL_strncat_s(secondsideRoot, secondsideRootSize, secondsideRootName, secondsideRootNameLength) == 0)//returns Zero if successful
				{
					//we have the file name so open it...
					if (OSAL_fopen(&f, secondsideRoot, "rb", _SH_DENYNO) == 0) //returns Zero if successful
					{
						long len;
						void *buf;
						fseek(f, 0, SEEK_END);
						len = ftell(f);
						fseek(f, 0, SEEK_SET);
						if (len > 0)
						{
							buf = malloc(len);
							if (buf)
							{
								tTLSOperationRequest r;
								wmx_Status_t res;
								OSAL_fread(buf, 1, len, f);
								SUPPLICANT_LOG(1, "SuppWrapper: Loading RootCert (%d bytes) from %s", 
									len, secondsideRoot);
								res = SendTLSRequest(&r, 97, tls_ctx, conn, 0, 0, (UINT8 *)buf, len);
								
								if (res != WMX_ST_OK)
								{
									rc = -1; //failure return code
								}
								
								free(buf);
							}
						}
						OSAL_fclose(f);
					}
				}
				else		
				{
					TRACE(TR_MOD_SUPPLICANT_WRAPPER, TR_SEV_ERR,"Unable to build secondside root name: %s\\%s",secondsideRoot, secondsideRootName);
				}

				free(secondsideRoot);
			}
		}
	}

	return rc;
}

int tls_global_set_params(void *tls_ctx, const struct tls_connection_params *params)
{
	return 0;
}

int tls_global_set_verify(void *tls_ctx, int check_crl)
{
	return 0;
}

int tls_connection_set_verify(void *tls_ctx, struct tls_connection *conn, int verify_peer)
{
	return 0;
}

int tls_connection_set_ia(void *tls_ctx, struct tls_connection *conn, int tls_ia)
{
	return -1;
}

int tls_connection_get_keys(void *tls_ctx, struct tls_connection *conn, struct tls_keys *keys)
{
	return -1;
}

u8 * tls_connection_server_handshake(void *tls_ctx,
struct tls_connection *conn,
	const u8 *in_data, size_t in_len,
	size_t *out_len)
{
	return NULL;
}

int tls_connection_set_master_key(void *tls_ctx, struct tls_connection *conn, const u8 *key, size_t key_len)
{
	return -1;
}

int tls_connection_set_cipher_list(void *tls_ctx, struct tls_connection *conn, u8 *ciphers)
{
	return -1;
}

int tls_get_cipher(void *tls_ctx, struct tls_connection *conn, char *buf, size_t buflen)
{
	return -1;
}

int tls_connection_enable_workaround(void *tls_ctx, struct tls_connection *conn)
{
	return -1;
}

int tls_connection_client_hello_ext(void *tls_ctx, struct tls_connection *conn,
									int ext_type, const u8 *data,
									size_t data_len)
{
	return -1;
}
