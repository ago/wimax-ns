/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
#pragma warning(disable : 4201) // warning C4201: nonstandard extension used : nameless struct/union

#include "Services_Ctrl.h"
#include "L5Common.h"
#include "IndicatorsSubscribers.h"
#include "Messenger.h"
#include "TraceModule.h"

#include "Act.h"

#include "L4MsgProxy.h"

#include "wimax_osal_primitives.h"

//*******************************************
//Private Fields of the L4MsgProxy:
//*******************************************
static List *indicatorSubscribersList = NULL;
static List *l4IndicatorSubscribersList = NULL;

//*******************************************
//globals for L5 layer:
//*******************************************
L5_CONNECTION l4Proxy_Connection = NULL;
tL5DispatcherFunctions *l4Proxy_pFuncs;

//Use to count the number of target which registered on L4 indication:
static int gNumOfL4IndSubscribers = 0; 
static OSAL_critical_section csNumOfL4IndSubscribers;

//determine whether already registered on the STATUS_INTEL_80216_CUSTOM indication as normal Status Indication!:
static BOOL gbRegisteredOnCustomStatus = FALSE; 
static OSAL_critical_section csRegisteredOnCustomStatus;

static OSAL_critical_section csSyncMessages;

//*******************************************
// Prototypes:
//*******************************************
void L4ProxyIndicationCallback(STATUS_IND_ID status_indication_id, void *indication_buffer, ULONG buffer_size );
void TotallyUnRegisterL5Target(L5_TARGET_ID nTargetID);

//*******************************************
// The followings functions are Safe Threads Getters and Setters
// of the gNumOfL4IndSubscribers,gbRegisteredOnCustomStatus fields
//*******************************************
BOOL IsRegisterOnCustomStatus()
{
	BOOL tmp;
	OSAL_enter_critical_section(&csRegisteredOnCustomStatus);
	tmp = gbRegisteredOnCustomStatus;
	OSAL_exit_critical_section(&csRegisteredOnCustomStatus);
	return tmp;
}

void SetRegisterOnCustomStatus(BOOL val)
{
	OSAL_enter_critical_section(&csRegisteredOnCustomStatus);
	gbRegisteredOnCustomStatus = val;
	OSAL_exit_critical_section(&csRegisteredOnCustomStatus);
}

int GetNumOfL4IndSubscribers()
{
	int tmp;
	OSAL_enter_critical_section(&csNumOfL4IndSubscribers);
	tmp = gNumOfL4IndSubscribers;
	OSAL_exit_critical_section(&csNumOfL4IndSubscribers);
	return tmp;
}

void IncNumOfL4IndSubscribers()
{
	OSAL_enter_critical_section(&csNumOfL4IndSubscribers);
	gNumOfL4IndSubscribers++;
	OSAL_exit_critical_section(&csNumOfL4IndSubscribers);
}

void DecNumOfL4IndSubscribers()
{
	OSAL_enter_critical_section(&csNumOfL4IndSubscribers);
	gNumOfL4IndSubscribers--;
	if(gNumOfL4IndSubscribers < 0)
	{
		gNumOfL4IndSubscribers = 0;
	}
	OSAL_exit_critical_section(&csNumOfL4IndSubscribers);
}


wmx_Status_t CheckResult( KDAPI_ADAPTER_RESULT kdapiResult )
{
	switch( kdapiResult ) 
	{
		case KDAPI_ADAPTER_SUCCESS:
			return WMX_ST_OK;

		case KDAPI_ADAPTER_BUFFER_TOO_SHORT:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_WARNING, "buffer too short");
			return WMX_ST_RESPONSE_BUFFER_TOO_SHORT;

		case KDAPI_ADAPTER_NO_ROOM_FOR_INDICATION:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_WARNING, "no room for indication");
			return WMX_ST_NO_ROOM_FOR_INDICATION;

		case KDAPI_ADAPTER_INDICATION_NOT_REGISTERED:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_WARNING, "indication not registered");
			return WMX_ST_INDICATION_NOT_REGISTERED;

		case KDAPI_ADAPTER_BAD_ARGUMENTS:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_WARNING, "bad arguments");
			return WMX_ST_ILLEGAL_OPERATION;

		case KDAPI_ADAPTER_DRIVER_GENERATED_ERR:
		case KDAPI_ADAPTER_NOT_ACTIVE:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "driver problem");
			//l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_KDAPI_ADAPTER, DEVICE_PROBLEM,  __FUNCTION__, __LINE__);
			//Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_KDAPI_ADAPTER_RESTART, NULL, 0,NULL,NULL,NULL,NULL,NULL);
			return WMX_ST_DEVICE_FAILURE;

		case KDAPI_ADAPTER_ERROR:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_ALERT, "other error %d", kdapiResult);
			//l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_L4_PROXY, DEVICE_PROBLEM,  __FUNCTION__, __LINE__);
			return WMX_ST_DEVICE_FAILURE;

		default:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_ALERT, "other error %d", kdapiResult);
			//l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_KDAPI_ADAPTER, DEVICE_PROBLEM, __FUNCTION__, __LINE__);
			//Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_KDAPI_ADAPTER_RESTART, NULL, 0,NULL,NULL,NULL,NULL,NULL);
			return WMX_ST_FAIL;
	}
}

// AppSrv Agent Interface: Shutdown
void L4_Msg_Proxy_Shutdown()
{ 
	if (l4Proxy_pFuncs != NULL)
	{
		l4Proxy_pFuncs->pfnDisconnect(l4Proxy_Connection);
		l4Proxy_Connection = NULL;
		l4Proxy_pFuncs = NULL;
	}	

	if (indicatorSubscribersList != NULL)
	{
		//clean the status indicator subscribers list:
		CleanIndicatorsList(&indicatorSubscribersList);
		indicatorSubscribersList = NULL;
	}

	if (l4IndicatorSubscribersList != NULL)
	{
		//clean the L4 indicator subscribers list:
		CleanIndicatorsList(&l4IndicatorSubscribersList);
		l4IndicatorSubscribersList = NULL;
	}

	OSAL_delete_critical_section(&csRegisteredOnCustomStatus);
	OSAL_delete_critical_section(&csNumOfL4IndSubscribers);	
	OSAL_delete_critical_section(&csSyncMessages);	

	TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "L4_Msg_Proxy_Shutdown Succeed!");	
} 

// AppSrv Agent Interface: Initialize
BOOL L4_Msg_Proxy_Initialize()
{	
	gNumOfL4IndSubscribers = 0; 
	gbRegisteredOnCustomStatus = FALSE; 

	OSAL_init_critical_section(&csNumOfL4IndSubscribers);
	OSAL_init_critical_section(&csRegisteredOnCustomStatus);
	OSAL_init_critical_section(&csSyncMessages);

	AllocIndicatorsList(&indicatorSubscribersList);
	AllocIndicatorsList(&l4IndicatorSubscribersList);

	l4Proxy_pFuncs = L5_DISPATCHER_GetServiceDispatcherFunctions();

	if ((NULL == l4Proxy_pFuncs) || 
		(L5_RESULT_OK != l4Proxy_pFuncs->pfnConnectEx(L5_TARGET_L4_PROXY, &L4_Msg_Proxy_MessagesHandler, NULL/*&L4_Msg_Proxy_EventHandler*/, NULL, THREAD_ID_DEFAULT, &l4Proxy_Connection )))
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_ALERT, "Failed to connect L5!");
		// L4_Msg_Proxy_Shutdown(); Anat - Act takes care of that
		return FALSE;
	}

	KDAPI_ADAPTER_SetDriverIndicatiosCB(L4ProxyIndicationCallback);

	//The KDApi is used only by the L4MsgProxy, hence it Initialized here:
	/*if (KDAPI_ADAPTER_SUCCESS != KDAPI_ADAPTER_Init(L4ProxyIndicationCallback))
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_ALERT, "KDAPI_ADAPTER_Init Failed!");
		// L4_Msg_Proxy_Shutdown(); Anat - Act takes care of that
		return FALSE;
	}

	if (!DriverMonitor_Init())
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_ALERT, "DriverMonitor_Init Failed!");
		return FALSE;
	}*/

	TRACE(TR_MOD_L4MsgProxy, TR_SEV_NOTICE, "L4_Msg_Proxy_Initialize Succeed!. Target ID=%d", L5_TARGET_L4_PROXY);
	return TRUE;	
}


// AppSrv Agent Interface: MessagesHandler
void L4_Msg_Proxy_MessagesHandler(L5_CONNECTION Conn,
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
	UINT32 res;
	char *OpCodeName;

	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);

// We decided to sync all the msgs in L4 Msg Proxy
// No we will work each time only one one message.
	OSAL_enter_critical_section(&csSyncMessages);

	switch(dwSentMessageID)
	{

	case L4_PROXY_OPCODE_SEND_OID:
		//extract the OID struct:
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Sending Non-L4 OID. Arrived from TargetID=%d (OIDnum=0x%x)", nOriginID, ((tL4ProxyOIDStruct*)pvSentBuffer)->oidNum);
		L4Proxy_SendOID(((tL4ProxyOIDStruct*)pvSentBuffer)->oidNum,
			&((tL4ProxyOIDStruct*)pvSentBuffer)->buffer,
			cbSentBufferSize - sizeof(UINT32),//decrease the OID Number place//((tL4ProxyOIDStruct*)pvSentBuffer)->bufferLength,
			pdwResponseMessageID,
			pvResponseBuffer, 
			cbResponseBufferSize);
		break;

	case L4_PROXY_OPCODE_SEND_L4_OPCODE:
		OpCodeName = GetL4Opcode(pvSentBuffer);
		//TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Sending L4 OpCode=0x%x. Arrived from TargetID=%d ", *(UINT16*)pvSentBuffer, nOriginID);
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Sending L4 OpCode=%s. Arrived from TargetID=%d ", OpCodeName , nOriginID);
		L4Proxy_SendOID(OID_INTEL_80216_CUSTOM, 
			pvSentBuffer,
			cbSentBufferSize,
			pdwResponseMessageID,
			pvResponseBuffer, 
			cbResponseBufferSize);
		break;

	case L4_PROXY_OPCODE_REGISTER_STATUS_INDICATION:
		res = L4Proxy_RegisterStatusIndicator(nOriginID, *((RegisteredIndication*)pvSentBuffer));
		if (NULL != pdwResponseMessageID)
		{
			*pdwResponseMessageID = res;
		}
		break;

	case L4_PROXY_OPCODE_UNREGISTER_STATUS_INDICATION:
		res = L4Proxy_UnRegisterStatusIndicator(nOriginID, *((RegisteredIndication*)pvSentBuffer));
		if (NULL != pdwResponseMessageID)
		{
			*pdwResponseMessageID = res;
		}
		break;

	case L4_PROXY_OPCODE_REGISTER_L4_INDICATION:
		res = L4Proxy_RegisterL4Indicator(nOriginID, *((L4_INTEL_80216_INDICATION*)pvSentBuffer));
		if (NULL != pdwResponseMessageID)
		{
			*pdwResponseMessageID = res;
		}
		break;

	case L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION:
		res = L4Proxy_UnRegisterL4Indicator(nOriginID, *((L4_INTEL_80216_INDICATION*)pvSentBuffer));
		if (NULL != pdwResponseMessageID)
		{
			*pdwResponseMessageID = res;
		}
		break;

	case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
		switch ( L4BM_GetOpcode((UINT8*)pvSentBuffer) )
		{
		case L3_L4_OPCODE_REPORT_STATE:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Got state report");
			//DriverMonitor_HandleDriverStateReport((UINT8*)pvSentBuffer);
			break;

		default:
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "INTERNAL_PROBLEM: unknown indication arrived: dwSentMessageID==%d", dwSentMessageID);
			l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_L4_PROXY, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
			break;
		}
		break;

	default://OPCODE is not supported
		if (NULL != pdwResponseMessageID)
		{
			*pdwResponseMessageID = WMX_ST_INVALID_OPCODE;
		}
		break;
	}

	OSAL_exit_critical_section(&csSyncMessages);
}

//// AppSrv Agent Interface: EventHandler
//void L4_Msg_Proxy_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext)
//{
//	UINT32 val;
//
//	UNREFERENCED_PARAMETER(Conn);
//	UNREFERENCED_PARAMETER(pvUserContext);
//
//	if (eEvent == L5_EVENT_OTHER_DISCONNECTED)
//	{
//		val = (UINT32)pvEventData;
//		TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Got other disconnected notification - TargetID = %d, Totally Unregister this Target.", (int)pvEventData);
//		TotallyUnRegisterL5Target((L5_TARGET_ID)val);
//	}
//}

// Used to register a Target on L4 Indication.
UINT32 L4Proxy_RegisterL4Indicator(L5_TARGET_ID nOriginID, L4_INTEL_80216_INDICATION l4_indication_id)
{
	IndicatorSubscribers *l4IndSubscribers = GetIndicatorSubscribers(l4IndicatorSubscribersList, l4_indication_id, TRUE);
	Indications_AddSubscriber(l4IndSubscribers, nOriginID);
	IncNumOfL4IndSubscribers();

	//TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "RegisterL4Indicator(TargetId=%d, l4_indication_id=0x%x)", nOriginID, l4_indication_id);
	TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "RegisterL4Indicator(TargetId=%d, l4_indication_id=%s)", nOriginID, GetL4Indication(l4_indication_id));
/*
	if ((1 == GetNumOfL4IndSubscribers()) && (FALSE == IsRegisterOnCustomStatus()))
	{
		KDAPI_ADAPTER_RESULT kdapiResult;
		wmx_Status_t l4Result;

		// not register for custom indication yet, hence do it now:
		kdapiResult = KDAPI_ADAPTER_RegisterOnIndication(STATUS_INTEL_80216_CUSTOM);
		l4Result = CheckResult( kdapiResult );
		if( l4Result != WMX_ST_OK )
		{
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Register for STATUS_INTEL_80216_CUSTOM on KDAPI");
			return l4Result;
		}
	}
*/
	return WMX_ST_OK;
}

// Used to unregister a Target from IndicatorSubscribers
UINT32 UnRegisterL4IndicatorFromIndicatorSubscribers(IndicatorSubscribers *indSubscribers, L5_TARGET_ID nTargetID)
{
	if( (indSubscribers == NULL) || (!Indications_RemoveSubscriber(indSubscribers, nTargetID)) )
	{
		// TODO: Oran - we shoudln't restart AppSrv because of a mismach in the subscribers list
		//l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_L4_PROXY, INTERNAL_PROBLEM);
		return WMX_ST_FAIL;
	}

	TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "UnRegisterL4Indicator(TargetId=%d, l4_indication_id=0x%x)", nTargetID, indSubscribers->id);
	// The remove succeed hence decrease the number of L4 Indicators registered.
	DecNumOfL4IndSubscribers();

	if ((0 == GetNumOfL4IndSubscribers()) && (FALSE == IsRegisterOnCustomStatus()))
	{
		KDAPI_ADAPTER_RESULT kdapiResult;
		wmx_Status_t l4Result;

		//No one wants custom indication! So unregister from it
		kdapiResult = KDAPI_ADAPTER_UnregisterOnIndication(STATUS_INTEL_80216_CUSTOM);
		l4Result = CheckResult( kdapiResult );
		if( l4Result != WMX_ST_OK )
		{
			TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "Unregister Indication STATUS_INTEL_80216_CUSTOM from KDAPI_ADAPTER!");
			return l4Result;
		}
	}

	return WMX_ST_OK;
}

// Used to unregister a Target from L4 Indication.
UINT32 L4Proxy_UnRegisterL4Indicator(L5_TARGET_ID nOriginID, L4_INTEL_80216_INDICATION l4_indication_id)
{
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(l4IndicatorSubscribersList, l4_indication_id, FALSE);

	TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "UnregisterL4Indicator(TargetId=%d, l4_indication_id=%s)", nOriginID, GetL4Indication(l4_indication_id));
	
	if ((NULL == indSubscribers) || 
		(WMX_ST_OK != UnRegisterL4IndicatorFromIndicatorSubscribers(indSubscribers, nOriginID)))
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "UnRegisterL4Indicator Failed(TargetId=%d, l4_indication_id=0x%x)", nOriginID, l4_indication_id);
		return WMX_ST_FAIL;
	}

	return WMX_ST_OK;	
}


UINT32 L4Proxy_Restart()
{
	ListItem* handle;
	IndicatorSubscribers *pTempInd = NULL;
	KDAPI_ADAPTER_RESULT kdapiResult;
	wmx_Status_t l4Result = WMX_ST_OK;

	//Register for L4 indications:
	kdapiResult = KDAPI_ADAPTER_RegisterOnIndication(STATUS_INTEL_80216_CUSTOM);
	l4Result = CheckResult( kdapiResult );
	if( l4Result != WMX_ST_OK )
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "Register status indication on KDAPI_ADAPTER FAILED(ststus_indication_id=0x%x)", STATUS_INTEL_80216_CUSTOM);
		return l4Result;
	}
	
	//Register for status indication:
	handle = CreateIterator(indicatorSubscribersList);
	handle = Iterator_GetNext(indicatorSubscribersList, handle, (void**)&pTempInd);
	while (handle != NULL)
	{
		if (STATUS_INTEL_80216_CUSTOM != pTempInd->id)
		{
			kdapiResult = KDAPI_ADAPTER_RegisterOnIndication(pTempInd->id);
			l4Result = CheckResult( kdapiResult );
			if( l4Result != WMX_ST_OK )
			{
				TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "Register status indication on KDAPI_ADAPTER FAILED(ststus_indication_id=0x%x)", pTempInd->id);
				return l4Result;
			}			
		}
		handle = Iterator_GetNext(indicatorSubscribersList, handle, (void**)&pTempInd);
	}
	FreeIterator(indicatorSubscribersList);


	return l4Result;
}
// Used to register a Target on status Indication.
UINT32 L4Proxy_RegisterStatusIndicator(L5_TARGET_ID nOriginID, STATUS_IND_ID status_indication_id)
{
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(indicatorSubscribersList, status_indication_id, TRUE);

	//VERIFY(NULL != indSubscribers);
	if(indSubscribers == NULL)
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_CRITICAL, "INTERNAL_PROBLEM: indSubscribers == NULL, Register status indication on KDAPI_ADAPTER FAILED(ststus_indication_id=0x%x)", status_indication_id);
		l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_L4_PROXY, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return WMX_ST_FAIL;
	}

	Indications_AddSubscriber(indSubscribers, nOriginID);

	if (STATUS_INTEL_80216_CUSTOM != status_indication_id)
	{
		if (1 == List_Length(&(indSubscribers->subscribersList))) //Register on L4Proxy only on first indReg request
		{
			KDAPI_ADAPTER_RESULT kdapiResult;
			wmx_Status_t l4Result;

			kdapiResult = KDAPI_ADAPTER_RegisterOnIndication(status_indication_id);
			l4Result = CheckResult( kdapiResult );
			if( l4Result != WMX_ST_OK )
			{
				TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "Register status indication on KDAPI_ADAPTER FAILED(ststus_indication_id=0x%x)", status_indication_id);
				return l4Result;
			}
		}
	}
	else
	{
		if ((FALSE == IsRegisterOnCustomStatus()) && (0 == GetNumOfL4IndSubscribers())) //Register on The Custom Status Id only if not registered yet
		{
			KDAPI_ADAPTER_RESULT kdapiResult;
			wmx_Status_t l4Result;

			kdapiResult = KDAPI_ADAPTER_RegisterOnIndication(STATUS_INTEL_80216_CUSTOM);
			l4Result = CheckResult( kdapiResult );
			if( l4Result != WMX_ST_OK )
			{
				TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "Register status indication on KDAPI_ADAPTER FAILED(ststus_indication_id=STATUS_INTEL_80216_CUSTOM)");
				return l4Result;
			}
		}
		SetRegisterOnCustomStatus(TRUE);
	}

	return WMX_ST_OK;
}

// Used to unregister a Target from status Indication.
UINT32 UnRegisterStatusIndicatorFromIndicatorSubscribers(IndicatorSubscribers *indSubscribers, L5_TARGET_ID nTargetID)
{	
	if ((NULL == indSubscribers) || (!Indications_RemoveSubscriber(indSubscribers, nTargetID)))
	{
		return WMX_ST_FAIL;
	}

	if (0 == List_Length(&(indSubscribers->subscribersList))) //UnRegister only if no subscribers in list
	{
		if (STATUS_INTEL_80216_CUSTOM != indSubscribers->id)//status_indication_id)
		{
			KDAPI_ADAPTER_RESULT kdapiResult;
			wmx_Status_t l4Result;

			kdapiResult = KDAPI_ADAPTER_UnregisterOnIndication(indSubscribers->id);
			l4Result = CheckResult( kdapiResult );
			if( l4Result != WMX_ST_OK )
			{
				// trace ??
				return l4Result;
			}
		}
		else
		{
			SetRegisterOnCustomStatus(FALSE);
			if (0 == GetNumOfL4IndSubscribers())
			{
				KDAPI_ADAPTER_RESULT kdapiResult;
				wmx_Status_t l4Result;

				kdapiResult = KDAPI_ADAPTER_UnregisterOnIndication(STATUS_INTEL_80216_CUSTOM);
				l4Result = CheckResult( kdapiResult );
				if( l4Result != WMX_ST_OK )
				{
					// trace ??
					return l4Result;
				}
			}
		}
	}
	
	return WMX_ST_OK;
}

// Used to unregister a Target from status Indication.
UINT32 L4Proxy_UnRegisterStatusIndicator(L5_TARGET_ID nOriginID, STATUS_IND_ID status_indication_id)
{
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(indicatorSubscribersList, status_indication_id, FALSE);

	if ((NULL == indSubscribers) || 
		(WMX_ST_OK != UnRegisterStatusIndicatorFromIndicatorSubscribers(indSubscribers, nOriginID)))
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_ERR, "UnRegisterStatusIndicator Failed(TargetId=%d, status_indication_id=0x%x)", nOriginID, status_indication_id);
		return WMX_ST_FAIL;
	}
	return WMX_ST_OK;
}

// Used to send OID 
void L4Proxy_SendOID(OID_NUM oidNum, void *bufferIn, UINT32 bufferInSize,UINT32 *pdwResponseMessageID, void *bufferOut, UINT32 *bufferOutSize)
{
	KDAPI_ADAPTER_RESULT kdapiResult;

	kdapiResult = KDAPI_ADAPTER_SendReceiveMessage(oidNum, bufferIn, bufferInSize, bufferOut, (int*)bufferOutSize);
	if(KDAPI_ADAPTER_SUCCESS != kdapiResult)
	{
		//l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_KDAPI_ADAPTER, DEVICE_PROBLEM, __FUNCTION__, __LINE__);
		//Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_KDAPI_ADAPTER_RESTART, NULL, 0,NULL,NULL,NULL,NULL,NULL);
	}
	*pdwResponseMessageID = CheckResult( kdapiResult );
}

//TODO: Unregister a specific L5 target ID from all indications
void TotallyUnRegisterL5Target(L5_TARGET_ID nTargetID)
{
	// Iterate the status indication list, for each indicator - remove the target ID:
	IndicatorSubscribers *indSubscribers;
	ListItem* handle;

	TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Totally remove Target ID from DB(L5_TARGET_ID=%d)", nTargetID);

	handle = CreateIterator(indicatorSubscribersList);
	handle = Iterator_GetNext(indicatorSubscribersList, handle, (void**)&indSubscribers);
	while (NULL != handle)
	{
		UnRegisterStatusIndicatorFromIndicatorSubscribers(indSubscribers, nTargetID);
		handle = Iterator_GetNext(indicatorSubscribersList, handle, (void**)&indSubscribers);
	}

	FreeIterator(indicatorSubscribersList);

	// Iterate the L4 indication list, for each indicator - remove the target ID:
	handle = CreateIterator(l4IndicatorSubscribersList);
	handle = Iterator_GetNext(l4IndicatorSubscribersList, handle, (void**)&indSubscribers);
	while (NULL != handle)
	{
		UnRegisterL4IndicatorFromIndicatorSubscribers(indSubscribers, nTargetID);
		handle = Iterator_GetNext(l4IndicatorSubscribersList, handle, (void**)&indSubscribers);
	}
	FreeIterator(l4IndicatorSubscribersList);
}

// Indication call back to KDapi:
void L4ProxyIndicationCallback(STATUS_IND_ID status_indication_id, void *indication_buffer, ULONG buffer_size )
{
	SendIndData *pSendIndData;
	UINT32 sendIndDataSize;
	L4_INTEL_80216_INDICATION l4_indication_id;

	TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Status Indication Arrived(%x)", status_indication_id);

	if (STATUS_INTEL_80216_CUSTOM != status_indication_id)
	{
		//TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Status Indication Arrived(id=0x%x)", status_indication_id);
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "Status Indication Arrived(id=%s)", GetL4Indication((UINT16)status_indication_id));
	}

	if (buffer_size > STATUS_INDICATION_PAYLOAD_MAX_SIZE)
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_CRITICAL, "Indication size too big: %d", buffer_size);
		//l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_KDAPI_ADAPTER, DEVICE_PROBLEM, __FUNCTION__, __LINE__);
		//Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_KDAPI_ADAPTER_RESTART, NULL, 0,NULL,NULL,NULL,NULL,NULL);
	}

	sendIndDataSize = sizeof(SendIndData) + buffer_size;
	pSendIndData = (SendIndData*)malloc(sendIndDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_CRITICAL, "malloc failed");
		return;
	}
	pSendIndData->pSenderFuncs = l4Proxy_pFuncs;
	pSendIndData->senderL5Conn = l4Proxy_Connection;
	pSendIndData->indication_buffer_size = buffer_size;
	if(buffer_size > 0)
	{
		OSAL_memcpy_s(pSendIndData->indication_buffer, buffer_size, indication_buffer, buffer_size);
	}

	pSendIndData->pSubscribersList = indicatorSubscribersList;
	pSendIndData->indication_id = status_indication_id;
	Messenger_PostRequest(
		MEDIUM, L4_PROXY_OPCODE_STATUS_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);

	if (STATUS_INTEL_80216_CUSTOM == status_indication_id)
	{
		l4_indication_id = L4BM_GetOpcode((UINT8*)indication_buffer);
		//TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "L4 Indication Arrived(id=0x%x)", l4_indication_id);
		TRACE(TR_MOD_L4MsgProxy, TR_SEV_INFO, "L4 Indication Arrived(id=%s = id=0x%x)", GetL4Indication(l4_indication_id), l4_indication_id);

		pSendIndData->pSubscribersList = l4IndicatorSubscribersList;
		pSendIndData->indication_id = l4_indication_id;
		Messenger_PostRequest(
			MEDIUM, L4_PROXY_OPCODE_L4_INDICATION_ARRIVED, pSendIndData, sendIndDataSize, &SendIndicationToSubscribers);
	}

	free(pSendIndData);
}

