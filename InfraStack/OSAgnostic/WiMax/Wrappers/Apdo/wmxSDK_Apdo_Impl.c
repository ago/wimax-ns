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
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Ctrl.h"
#include "wmxSDK_Apdo_L5.h"
#include "wmxSDK_Apdo_Utils.h"
#include "wmxSDK_Apdo_3.h"
#include "wmxSDK_Nds_L5.h"

#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Apdo_Internals.h"

#include "L5Common.h"
#include "WrappersUtils.h"

#include "TraceModule.h"
#include "L4MsgProxyIf.h"
#include "NDnSAgent_DB_if.h"
#include "NDnSAgent_APDO.h"

#include "AES_CCM.h"
#include "bootstrap.h"

#include "L4ConfigurationManager.h"

#include "wmxSDK_Apdo_Internals.h"
#include "wimax_osal_primitives.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_types.h"

#include "XmlParser.h"

static UINT8 stringStub[MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB];
//#include "md5.h"

extern OSAL_critical_section *pcs_apdo_funcs;

wmx_Status_t wmxApdo_SendNdsMsg(
	UINT32 opcode, NDNS_AGENT_L5_OPCODE ndnsOpcode,
	UINT32 requestLength, UINT8 *request,
	UINT32 *responseLength, UINT8 *response );

//************************************************************************
//  A function that is called from the context of the messenger handler
//************************************************************************
void wmxAPDO_ThreadHandler( void *internalData, UINT32 internalRequestID, UINT32 messageID, void *buffer, UINT32 bufferLength )
{
	UNREFERENCED_PARAMETER(bufferLength);
	UNREFERENCED_PARAMETER(internalData);
	UNREFERENCED_PARAMETER(messageID);
	UNREFERENCED_PARAMETER(internalRequestID);
	UNREFERENCED_PARAMETER(buffer);
}

//************************************************
//
//************************************************
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxApdo_Init()
{
	wmx_Status_t status = WMX_ST_OK;
	int adpoInitCount;
	if (pcs_apdo_funcs != NULL)
		OSAL_enter_critical_section(pcs_apdo_funcs);
	adpoInitCount = apdo_numOfInits;
	if (pcs_apdo_funcs != NULL)
		OSAL_exit_critical_section(pcs_apdo_funcs);
	if (adpoInitCount == FIRST_REGISTERED)
		return status;
	//g_ApdoOperatorConfigurations = malloc(sizeof(wmx_ApdoOperatorConfigurations_t)*MAX_NUM_OF_CONFIGURATIONS);

		if ( FIRST_REGISTERED == OSAL_atomic_increment(&apdo_numOfInits) )
		{
			status = wmxApdo_InitL5();
			if ( WMX_ST_OK != status )
			{
				wmxApdo_Finalize();
				return status;
			}
		}

		return status;

}

//************************************************
//
//************************************************
void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxApdo_Finalize()
{
	int adpoInitCount =0;

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "void wmxApdo_Finalize()");

	if (pcs_apdo_funcs != NULL)
		OSAL_enter_critical_section(pcs_apdo_funcs);
	adpoInitCount = apdo_numOfInits;
	if (pcs_apdo_funcs != NULL)
		OSAL_exit_critical_section(pcs_apdo_funcs);

	if (adpoInitCount == LAST_REGISTERED)
		return;
	if ( LAST_REGISTERED == OSAL_atomic_decrement(&apdo_numOfInits) )
	{
		wmxApdo_FinalizeL5();
	}

	OSAL_atomic_compareExchange(&apdo_numOfInits, LAST_INIT, LAST_INIT - 1);
    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmxApdo_Finalize(OUT)");
}


//*******************************************************
// *******  Implementations of wmxSDK_Apdo_3.h  *********
//*******************************************************

// The function assumes that pValue is allocated with enough memory for the resulting value
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_pAPDOType_t pAPDOType )
{
	wmx_Status_t status;
	UINT32 responseLength = MAX_APDO_GET_RESULT;
	UINT32 requestBufferSize = (UINT32)sizeof(wmx_APDOType_t) + MAX_APDO_PATH;
	UINT8 requestBuffer[sizeof(wmx_APDOType_t) + MAX_APDO_PATH];
	UINT8 resultBuffer[MAX_APDO_GET_RESULT];
	UINT32 valueLength;

	if (OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH + 1) > MAX_APDO_PATH)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - %s", pAPDOPath);

	wmxApdo_CreateAPDOBuffer(*pAPDOType, pAPDOPath, (char*)requestBuffer );
	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_APDO_INFO,  NDNS_OPCODE_APDO, requestBufferSize, requestBuffer, &responseLength, resultBuffer );
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() status - %d", status);

	// If Get failed we don't update the parameters.
	if (status != WMX_ST_OK)
	{
		return status;
	}

	*pAPDOType = *(wmx_pAPDOType_t)resultBuffer;

	//TODO: This calculation is here until the real result size will come back from wmxApdo_SendNdsMsg
	//OSAL_memcpy_s(pValue, MAX_APDO_GET_RESULT, resultBuffer + sizeof(wmx_APDOType_t), responseLength - sizeof(wmx_APDOType_t));
	valueLength = wmxApdo_GetBufferLength(resultBuffer + sizeof(wmx_APDOType_t), *pAPDOType);

	OSAL_memcpy_s(pValue, MAX_APDO_GET_RESULT, resultBuffer + sizeof(wmx_APDOType_t), valueLength);

	// Log the results of the Get command
	if (valueLength > 0)
	{

		switch(*pAPDOType)
		{
		case APDO_Bool:
		case APDO_Integer:
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - %s   APDOType - %d value - %d", pAPDOPath, *pAPDOType, *(int*)pValue);
			break;
		case APDO_Float:
		case APDO_Double:
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - %s   APDOType - %d APDOValue - %f", pAPDOPath, *pAPDOType, *(DOUBLE*)pValue);
			break;
		case APDO_String:
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - %s   APDOType - %d APDOValue - %s", pAPDOPath, *pAPDOType, pValue);
			break;
		default:
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - %s   APDOType - %d ", pAPDOPath, *pAPDOType);
		}
	}
	else
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetAPDOinfo() pAPDOPath - %s   APDOType - %d value size - %d", pAPDOPath, *pAPDOType, valueLength);
	}

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetApdoConnectionParameters( wmx_pApdoLinkStatus_t linkStatus,
																		char nspName[WMX_NSP_NAME_MAX_SIZE],
																		wmx_pNSPid_t nspId,
																		char realm[WMX_NSP_REALM_MAX_SIZE],
																		char toDmAcc[MAX_ACCOUNT_NAME_SIZE])
{
	wmx_Status_t status = WMX_ST_OK;

	UINT32 responseLength = sizeof(wmx_ApdoLinkStatusParams_t);
	wmx_ApdoLinkStatusParams_t requestBuffer;
	wmx_ApdoLinkStatusParams_t resultBuffer;
	wmx_ApdoOperatorConfigurations_t apdoConfigurations;
	UINT32 responseLengthAgain = (UINT32)(sizeof(wmx_ApdoOperatorConfigurations_t));
	//(realm == NULL) ||
	if ((linkStatus == NULL) || (nspId == NULL) || (nspName == NULL) || (toDmAcc == NULL))
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetApdoLinkStatus() wrong argument");
		return WMX_ST_WRONG_ARGUMENT;
	}


	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_APDO_LINK_STATUS,  NDNS_OPCODE_APDO, sizeof(wmx_ApdoLinkStatusParams_t),
		(UINT8*)&requestBuffer, &responseLength, (UINT8*)&resultBuffer );
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetApdoLinkStatus() status - %d", status);

	// If Get failed we don't update the parameters.
	if (status != WMX_ST_OK)
	{
		return status;
	}
	status = wmx_GetApdoOperatorConfigurations (&apdoConfigurations , sizeof(apdoConfigurations), &responseLengthAgain);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "wmxApdo_CBsCaller: GetApdoOperatorConfigurations returned != WMX_ST_OK then we use defauult which is enable OTAP !");
	}
	if (resultBuffer.nspName[0] != '\0')
	{
		if (!apdoConfigurations.disableOTAP)
		{
			*linkStatus = resultBuffer.linkStatus;
			*nspId = resultBuffer.nspId;
			OSAL_strncpy_s(realm, WMX_NSP_REALM_MAX_SIZE, resultBuffer.realm, OSAL_strnlen(resultBuffer.realm, WMX_NSP_REALM_MAX_SIZE));
			OSAL_strncpy_s(nspName, WMX_NSP_NAME_MAX_SIZE, resultBuffer.nspName,
				OSAL_strnlen(resultBuffer.nspName, WMX_NSP_NAME_MAX_SIZE));
			//resultBuffer.toDMAcc[MAX_ACCOUNT_NAME_SIZE]='\0';
			if (resultBuffer.toDMAcc[0] != '\0')
			{
				OSAL_strncpy_s(toDmAcc, MAX_ACCOUNT_NAME_SIZE, resultBuffer.toDMAcc,
					OSAL_strnlen(resultBuffer.toDMAcc, MAX_ACCOUNT_NAME_SIZE));
			}
			else
			{
				memset(toDmAcc,'\0',MAX_ACCOUNT_NAME_SIZE);
			}
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "wmx_GetApdoConnectionParameters: GetApdoOperatorConfigurations OTAP is disabled!");
		}
	}

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_AddAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType )
{
	wmx_Status_t status;
	UINT32 requestBufferSize;
	UINT8 *requestBuffer;

	UINT32 valSize = wmxApdo_GetBufferLength(pValue, APDOType);

	if (pValue == NULL)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pValue is NULL");
		return WMX_ST_WRONG_ARGUMENT;
	}

	if (valSize > MAX_APDO_GET_RESULT)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pValue - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	// +1 for \0 in pAPDOPath
	requestBufferSize = (UINT32)(sizeof(wmx_APDOType_t) + OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH) + valSize + 1);


	if (OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH + 1) > MAX_APDO_PATH)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_AddAPDOinfo() pAPDOPath - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	switch(APDOType)
	{
	case APDO_Bool:
	case APDO_Integer:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_AddAPDOinfo() pAPDOPath - %s   APDOType - %d value - %d", pAPDOPath, APDOType, *(int*)pValue);
		break;
	case APDO_Float:
	case APDO_Double:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_AddAPDOinfo() pAPDOPath - %s   APDOType - %d APDOValue - %f", pAPDOPath, APDOType, *(DOUBLE*)pValue);
		break;
	case APDO_String:
		// Create pValue as WCHAR
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_AddAPDOinfo() pAPDOPath - %s   APDOType - %d value - %s", pAPDOPath, APDOType, pValue);
		break;
	default:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_AddAPDOinfo() pAPDOPath - %s   APDOType - %d", pAPDOPath, APDOType);
	}


	requestBuffer = (UINT8 *)malloc(requestBufferSize);

	wmxApdo_CreateApdoBufferWithValue(APDOType, pAPDOPath, (char*)pValue, (char*)requestBuffer );
	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_ADD_APDO_INFO, NDNS_OPCODE_APDO, requestBufferSize, requestBuffer, 0, NULL );
	free(requestBuffer);
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_AddAPDOinfo() status - %d", status);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UpdateAPDOinfo( wmx_APDOPath_t pAPDOPath, void *pValue, wmx_APDOType_t APDOType )
{
	wmx_Status_t status;
	UINT8 *requestBuffer;
	char pAPDOValue[MAX_APDO_GET_RESULT];

	UINT32 valSize = wmxApdo_GetBufferLength(pValue, APDOType);
	UINT32 requestBufferSize = (UINT32)(sizeof(wmx_APDOType_t) + OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH) +
		valSize + 1);   // +1 for \0 in pAPDOPath

	memset(pAPDOValue, 0, MAX_APDO_GET_RESULT);
	if (pValue == NULL)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pValue is NULL");
		return WMX_ST_WRONG_ARGUMENT;
	}

	if (OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH + 1) > MAX_APDO_PATH)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pAPDOPath - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	if (valSize > MAX_APDO_GET_RESULT)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pValue - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	switch (APDOType)
	{
	case APDO_Bool:
	case APDO_Integer:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pAPDOPath - %s   APDOType - %d APDOValue - %d", pAPDOPath, APDOType, *(int*)pValue);
		break;
	case APDO_Float:
	case APDO_Double:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pAPDOPath - %s   APDOType - %d APDOValue - %f", pAPDOPath, APDOType, *(DOUBLE*)pValue);
		break;
	case APDO_String:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pAPDOPath - %s   APDOType - %d APDOValue - %s", pAPDOPath, APDOType, pAPDOValue);
		break;
	default:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() pAPDOPath - %s   APDOType - %d", pAPDOPath, APDOType);
	}

	requestBuffer = (UINT8 *)malloc(requestBufferSize);

	wmxApdo_CreateApdoBufferWithValue(APDOType, pAPDOPath, (char*)pValue, (char*)requestBuffer );
	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_UPDATE_APDO_INFO, NDNS_OPCODE_APDO, requestBufferSize, requestBuffer, 0, NULL );
	free(requestBuffer);
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UpdateAPDOinfo() status - %d", status);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_DeleteAPDOinfo( wmx_APDOPath_t pAPDOPath )
{
	wmx_Status_t status;

	if (OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH + 1) > MAX_APDO_PATH)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_DeleteAPDOinfo() pAPDOPath - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_DeleteAPDOinfo() pAPDOPath - %s", pAPDOPath);

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_DELETE_APDO_INFO,  NDNS_OPCODE_APDO, (UINT32)OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH) + 1, // +1 for \0
									(UINT8*)pAPDOPath, 0, NULL );
	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_DeleteAPDOinfo() status - %d", status);

	return status;
}

// Not implemented yet
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ExecuteAPDOinfo( wmx_APDOPath_t pAPDOPath )
{
	wmx_Status_t status;

	if (OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH + 1) > MAX_APDO_PATH)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_ExecuteAPDOinfo() pAPDOPath - buffer too long");
		return WMX_ST_WRONG_ARGUMENT;
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_ExecuteAPDOinfo() pAPDOPath - %s", pAPDOPath);

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_EXECUTE_APDO_INFO,  NDNS_OPCODE_APDO, (UINT32)OSAL_strnlen((const char*)pAPDOPath, MAX_APDO_PATH) + 1, // +1 for \0
									(UINT8*)pAPDOPath, 0, NULL );

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoSessionStatus( wmx_ApdoSessionStatus_t sessionStatus )
{
	wmx_Status_t status;
	wmxApdo_FunctionParamStruct functionParamStruct;
	wmx_ApdoSessionStatusStruct_t apdoSessionStatusStruct;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_ApdoSessionStatus() sessionStatus - %d", sessionStatus);

	apdoSessionStatusStruct.sessionStatus = sessionStatus;

	functionParamStruct.FunctionType = APDO_ApdoSessionStatus;
	functionParamStruct.FuncParamUnion.ApdoSessionStatusStruct = apdoSessionStatusStruct;

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_APDO_TYPE,  NDNS_OPCODE_APDO, (UINT32)sizeof(functionParamStruct), (UINT8*)&functionParamStruct, 0, NULL );

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoFumoUpdate(wmx_FUMOUpdate_t updateType, wmx_FUMOUpdateContent_t updateContent )
{
	wmx_Status_t status;
//	UINT32 requestLength;
//	UINT8 *request;

	wmxApdo_FunctionParamStruct functionParamStruct;
	wmx_FUMOUpdateContent_t fumoUpdateContent;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_NOTICE, "wmx_ApdoFumoUpdate() ApdoFumoUpdate - %d", updateType);

	fumoUpdateContent = updateContent;

	functionParamStruct.FunctionType = APDO_FumoUpdate;
	functionParamStruct.FuncParamUnion.fumoUpdateContent = fumoUpdateContent;
	//requestLength = sizeof(wmx_FUMOUpdate_t) + sizeof(wmx_FUMOUpdateContent_t);

	//request = (UINT8*)malloc(requestLength);

	//OSAL_memcpy_s(request, requestLength, &updateType, sizeof(wmx_FUMOUpdate_t));
	//OSAL_memcpy_s(request + sizeof(wmx_FUMOUpdate_t), requestLength - sizeof(wmx_FUMOUpdate_t), &updateContent, sizeof(wmx_FUMOUpdateContent_t));

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_APDO_TYPE, NDNS_OPCODE_APDO, (UINT32)sizeof(functionParamStruct), (UINT8*)&functionParamStruct, 0, NULL);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoAlertNotification( wmx_ApdoAlert_t alert, wmx_ApdoAlertContent_t alertContent )
{
	wmx_Status_t status;
	wmxApdo_FunctionParamStruct functionParamStruct;
	wmx_AlertNotificationStruct_t alertNotificationStruct;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_ApdoAlertNotification()");

	alertNotificationStruct.alert = alert;
	OSAL_strcpy_s((char*)alertNotificationStruct.alertContent, MAX_ALERT_CONTENT, (const char*)alertContent);

	functionParamStruct.FuncParamUnion.AlertNotificationStruct = alertNotificationStruct;
	functionParamStruct.FunctionType = APDO_AlertNotification;

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_APDO_TYPE,  NDNS_OPCODE_APDO, (UINT32)sizeof(functionParamStruct), (UINT8*)&functionParamStruct, 0, NULL );

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_StoreProvisioningClientCfgDataBlob(wmx_NSPid_t nspId, wmx_ProvisioningClientCfgDataBlob_t cfgDataBlob)
{
	wmx_Status_t status;
	wmxApdo_FunctionParamStruct functionParamStruct;
	wmx_StoreProvisioningClientCfgDataBlobStruct_t storeProvisioningClientCfgDataBlobStruct;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_StoreProvisioningClientCfgDataBlob()");

	storeProvisioningClientCfgDataBlobStruct.nspId = nspId;
	OSAL_strcpy_s((char*)storeProvisioningClientCfgDataBlobStruct.cfgDataBlob, MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB, (const char*)cfgDataBlob);

	functionParamStruct.FunctionType = APDO_StoreProvisioningClientCfgDataBlobStruct;
	functionParamStruct.FuncParamUnion.StoreProvisioningClientCfgDataBlobStruct = storeProvisioningClientCfgDataBlobStruct;

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_APDO_TYPE,  NDNS_OPCODE_APDO, (UINT32)sizeof(functionParamStruct), (UINT8*)&functionParamStruct, 0, NULL );
	OSAL_strcpy_s((char*)stringStub, MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB, (char*)cfgDataBlob);

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetProvisioningClientCfgDataBlob(wmx_NSPid_t nspId, wmx_pProvisioningClientCfgDataBlob_t pCfgDataBlob)
{
	UNREFERENCED_PARAMETER(nspId);

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetProvisioningClientCfgDataBlob()");
	/*wmx_Status_t status;
	wmxApdo_FunctionParamStruct functionParamStruct;
	wmx_GetProvisioningClientCfgDataBlobStruct_t getProvisioningClientCfgDataBlobStruct;
	UINT32 responseLength = (UINT32)sizeof(functionParamStruct);

	getProvisioningClientCfgDataBlobStruct.nspId = nspId;

	functionParamStruct.FunctionType = APDO_GetProvisioningClientCfgDataBlobStruct;
	functionParamStruct.FuncParamUnion.GetProvisioningClientCfgDataBlobStruct = getProvisioningClientCfgDataBlobStruct;

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_APDO_TYPE,  NDNS_OPCODE_APDO, (UINT32)sizeof(functionParamStruct), (UINT8*)&functionParamStruct, &responseLength, (UINT8*)&functionParamStruct );*/
//	OSAL_strcpy_s((char*)cfgDataBlob, MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB, (const char*)functionParamStruct.FuncParamUnion.GetProvisioningClientCfgDataBlobStruct.cfgDataBlob);
	OSAL_strcpy_s((char*)*pCfgDataBlob, MAX_PROVISIONING_CLIENT_CFG_DATA_BLOB, (char*)stringStub);

	//return status;
	return WMX_ST_OK;
}


//////////////////

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoLinkStatusCB( wmx_pApdoLinkStatusCB_t apdoLinkStatusCB )
{
	wmx_Status_t RC = WMX_ST_OK;

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterApdoLinkStatusCB(wmx_pApdoLinkStatusCB_t ApdoLinkStatusCB)");
	if ( NULL != ApdoLinkStatusCB )
	{
		RC = WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	else if ( NULL == apdoLinkStatusCB )
	{
		RC = WMX_ST_ILLEGAL_OPERATION;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoLinkStatusCB = apdoLinkStatusCB;

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on apdo link status indication");
		RC = wmxApdo_RegisterOnApdoLinkStatusInd();
	}

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmxApdo_RegisterOnApdoLinkStatusInd(OUT) status = %d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoLinkStatusCB()
{
	wmx_Status_t RC = WMX_ST_OK;

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterApdoLinkStatusCB()");
	if ( NULL == ApdoLinkStatusCB )
	{
		RC = WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoLinkStatusCB = NULL;
		RC = wmxApdo_UnregisterOnApdoLinkStatusInd();
	}

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterApdoLinkStatusCB(OUT) status = %d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoAlertResponseCB( wmx_pApdoAlertResponseCB_t apdoAlertResponseCB )
{
	wmx_Status_t RC = WMX_ST_OK;

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterApdoAlertResponseCB(wmx_pApdoAlertResponseCB_t apdoAlertResponseCB)");
	if ( NULL != ApdoAlertResponseCB )
	{
		RC = WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	else if ( NULL == apdoAlertResponseCB )
	{
		RC = WMX_ST_ILLEGAL_OPERATION;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoAlertResponseCB = apdoAlertResponseCB;

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on alert response indication");
		RC = wmxApdo_RegisterOnApdoAlertResponseInd();
	}

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterApdoAlertResponseCB(OUT) status = %d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoAlertResponseCB()
{
	wmx_Status_t RC = WMX_ST_OK;

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterApdoAlertResponseCB()");
	if ( NULL == ApdoAlertResponseCB )
	{
		RC = WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoAlertResponseCB = NULL;
		RC = wmxApdo_UnregisterOnApdoAlertResponseInd();
	}

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterApdoAlertResponseCB(OUT) status = %d", RC);
	return RC;
}

//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoOobNotificationCB( wmx_pApdoOobNotificationCB_t apdoOobNotificationCB )
//{
//	wmx_Status_t RC = WMX_ST_OK;
//
//	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterApdoOobNotificationCB(wmx_pApdoOobNotificationCB_t apdoOobNotificationCB)"));
//	if ( NULL != ApdoOobNotificationCB )
//	{
//		RC = WMX_ST_CALLBACK_ALREADY_REGISTERED;
//	}
//	else if ( NULL == apdoOobNotificationCB )
//	{
//		RC = WMX_ST_ILLEGAL_OPERATION;
//	}
//
//	if (RC == WMX_ST_OK)
//	{
//		ApdoOobNotificationCB = apdoOobNotificationCB;
//
//		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, (L"registering on oob notification indication"));
//		RC = wmxApdo_RegisterOnApdoOobNotificationInd();
//	}
//
//    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, (L"wmx_Status_t wmx_RegisterApdoOobNotificationCB(OUT) status = %d", RC));
//
//	return RC;
//}
//
//wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoOobNotificationCB()
//{
//	wmx_Status_t RC = WMX_ST_OK;
//
//    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterApdoOobNotificationCB()"));
//	if ( NULL == ApdoOobNotificationCB )
//	{
//		RC = WMX_ST_CALLBACK_NOT_REGISTERED;
//	}
//
//	if (RC == WMX_ST_OK)
//	{
//		ApdoOobNotificationCB = NULL;
//		RC = wmxApdo_UnregisterOnApdoOobNotificationInd();
//	}
//
//    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, (L"wmx_Status_t wmx_UnregisterApdoOobNotificationCB(OUT) status = %d", RC));
//	return RC;
//}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterRefreshApdoSessionStatusCB( wmx_pRefreshApdoSessionStatusCB_t refreshApdoSessionStatusCB )
{
	wmx_Status_t RC = WMX_ST_OK;
    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterRefreshApdoSessionStatusCB(wmx_pRefreshApdoSessionStatusCB_t refreshApdoSessionStatusCB)");
	if ( NULL != RefreshApdoSessionStatusCB )
	{
		RC = WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	else if ( NULL == refreshApdoSessionStatusCB )
	{
		RC = WMX_ST_ILLEGAL_OPERATION;
	}

	if (RC == WMX_ST_OK)
	{
		RefreshApdoSessionStatusCB = refreshApdoSessionStatusCB;

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on refresh APDO session status indication");
		RC = wmxApdo_RegisterOnApdoSessionStatusInd();
	}

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterRefreshApdoSessionStatusCB(OUT) status = %d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterRefreshApdoSessionStatusCB()
{
	wmx_Status_t RC = WMX_ST_OK;

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterRefreshApdoSessionStatusCB()");
	if ( NULL == RefreshApdoSessionStatusCB )
	{
		RC = WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	if (RC == WMX_ST_OK)
	{
		RefreshApdoSessionStatusCB = NULL;
		RC = wmxApdo_UnregisterOnApdoSessionStatusInd();
	}

    TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterRefreshApdoSessionStatusCB(OUT) status = %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoFumoDownloadApprovalStatusCB( wmx_pApdoFumoDownloadApprovalStatusCB_t apdoFumoDownloadApprovalStatusCB )
{
	wmx_Status_t RC = WMX_ST_OK;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterApdoFumoDownloadApprovalStatusCB(wmx_pApdoFumoALinkStatusCB_t ApdoDownloadApprovalStatusCB)");
	if ( NULL != ApdoFumoDownloadApprovalStatusCB )
	{
		RC = WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	else if ( NULL == apdoFumoDownloadApprovalStatusCB )
	{
		RC = WMX_ST_ILLEGAL_OPERATION;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoFumoDownloadApprovalStatusCB = apdoFumoDownloadApprovalStatusCB;

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on apdo fumo download approval status indication");
		RC = wmxApdo_RegisterOnApdoFumoDownloadApprovalStatusInd();
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_RegisterApdoFumoDownloadApprovalStatusCB(OUT) status = %d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoFumoDownloadApprovalStatusCB()
{
	wmx_Status_t RC = WMX_ST_OK;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterApdoFumoDownloadApprovalStatusCB()");
	if ( NULL == ApdoFumoDownloadApprovalStatusCB )
	{
		RC = WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoFumoDownloadApprovalStatusCB = NULL;
		RC = wmxApdo_UnregisterOnApdoFumoDownloadApprovalStatusInd();
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_Status_t wmx_UnregisterRefreshApdoSessionStatusCB(OUT) status = %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterApdoDeleteDMAccountCB( wmx_pApdoDeleteDMAccountCB_t apdoDeleteDMAccountCB )
{
	wmx_Status_t RC = WMX_ST_OK;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_RegisterApdoDeleteDMAccountCB");
	if ( NULL != ApdoDeleteDMAccountCB )
	{
		RC = WMX_ST_CALLBACK_ALREADY_REGISTERED;
	}
	else if ( NULL == apdoDeleteDMAccountCB )
	{
		RC = WMX_ST_ILLEGAL_OPERATION;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoDeleteDMAccountCB = apdoDeleteDMAccountCB;

		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "registering on apdo delete dmAcc indication");
		RC = wmxApdo_RegisterOnApdoDeleteDMAccountInd();
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_RegisterApdoDeleteDMAccountCB(OUT) status = %d", RC);

	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterApdoDeleteDMAccountCB()
{
	wmx_Status_t RC = WMX_ST_OK;

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UnregisterApdoDeleteDMAccountCB");
	if ( NULL == ApdoDeleteDMAccountCB)
	{
		RC = WMX_ST_CALLBACK_NOT_REGISTERED;
	}

	if (RC == WMX_ST_OK)
	{
		ApdoDeleteDMAccountCB = NULL;
		RC = wmxApdo_UnregisterOnApdoDeleteDMAccountInd();
	}

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_UnregisterApdoDeleteDMAccountCB(OUT) status = %d", RC);
	return RC;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoFumoSetPackagePath(char* path, char* FileName)
{
	wmx_Status_t status;
	UINT8 *requestBuffer;
	UINT32 pathLen;
	UINT32 nameLen;
	UINT32 requestBufferSize;

	pathLen = (UINT32)(OSAL_strnlen(path, MAX_PATH) + 1)*sizeof(char);
	nameLen = (UINT32)(OSAL_strnlen(FileName , MAX_FILENAME_LEN) + 1)*sizeof(char);

	if (pathLen < MAX_PATH && nameLen < MAX_FILENAME_LEN)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_ApdoFumoSetPackagePath path - %s file name - %s", path, FileName);
	}
	else
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "wmx_ApdoFumoSetPackagePath wrong arguments");
		status = WMX_ST_WRONG_ARGUMENT;
		goto Finalize;
	}

	requestBufferSize = pathLen + sizeof(UINT32) + nameLen + sizeof(UINT32);

	requestBuffer = (UINT8 *)malloc(requestBufferSize);

	memcpy(requestBuffer, &pathLen,  sizeof(UINT32));
	memcpy(requestBuffer + sizeof(UINT32), path,  pathLen);
	requestBuffer[sizeof(UINT32) + pathLen - 1] = '\0';
	memcpy(requestBuffer + sizeof(UINT32) + pathLen, &nameLen,  sizeof(UINT32));
	memcpy(requestBuffer + sizeof(UINT32) + pathLen + sizeof(UINT32), FileName,  nameLen);
	requestBuffer[requestBufferSize - 1] = '\0';

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_APDO_SET_PACKAGE_PATH, NDNS_OPCODE_APDO, requestBufferSize,
		requestBuffer, 0, NULL );
	free(requestBuffer);

Finalize:
	return status;
}

// Get the BEK of the last connected NSP
wmx_Status_t wmx_GetBEK( wmx_pBEKBuffer_t pBEK )
{
	wmx_Status_t status;
	UINT32 responseLength = (UINT32)sizeof(wmx_BEKBuffer_t);
	UINT8 resultBuffer[sizeof(wmx_BEKBuffer_t)];

	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetBEK function (IN)");

	if (pBEK == NULL)
	{
		return WMX_ST_WRONG_ARGUMENT;
	}

	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_BEK,  NDNS_OPCODE_APDO, 0, NULL, &responseLength, resultBuffer );

	if (status == WMX_ST_OK)
	{
		OSAL_memcpy_s((void *)pBEK, sizeof(wmx_BEKBuffer_t), resultBuffer, responseLength);
	}

	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_DecBootStrap(UINT8* inBuffer, UINT32 inBufferSize, UINT8* outBuffer, UINT32 outBufferSize, UINT32* actualOutBufferSize)
{
	//UINT8 pCipherKey[] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f};
	//UINT8* tempInBuffer;
	//UINT32 tempSize;
	// UINT32 outBitOffset;
	AES_CCM_ReturnCode returnCode;

	wmx_BEKBuffer_t pCipherKey;
	wmx_Status_t st = WMX_ST_FAIL;
	char secureBootstrap[MAX_ANSWER_SIZE];

	UNREFERENCED_PARAMETER(inBufferSize);

	L4Configurations_getAPDOSecureBootstrap(secureBootstrap);

	// If secure bootstrap is true we got encrypted buffer and need to decrypt it. Otherwise, we return the input buffer as output.
	if (0 == OSAL_stricmp("true", secureBootstrap))
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_DecBootStrap function with encrypted bootstrap");
		st = wmx_GetBEK(pCipherKey);

	    if (st != WMX_ST_FAIL)
		{
			returnCode = AES_CCM_Decrypt(inBuffer, pCipherKey, outBuffer, outBufferSize, actualOutBufferSize);

			switch(returnCode)
			{
			case AES_CCM_BUFFER_TOO_SHORT:
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "wmx_DecBootStrap input buffer is too short");
				st = WMX_ST_BUFFER_TOO_SHORT;
				break;
			case AES_CCM_SUCCESS:
				st = WMX_ST_OK;
			    break;
			default:
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "wmx_DecBootStrap failure. AES_CCM returned=%d", returnCode);
				st = WMX_ST_FAIL;
			    break;
			}
		}

	}
	else
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_DecBootStrap function with plain bootstrap");

		*actualOutBufferSize = inBufferSize;

		// Validate size for output buffer
		if (outBufferSize < inBufferSize)
		{
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "wmx_DecBootStrap input buffer is too short");
			st = WMX_ST_BUFFER_TOO_SHORT;
		}
		else
		{
			OSAL_memcpy_s(outBuffer, inBufferSize, inBuffer + BOOTSTRAP_HEADER_OFFSET, inBufferSize - BOOTSTRAP_HEADER_OFFSET);
			st = WMX_ST_OK;
		}
	}

	return st;
}


#define currOperatorName "xohm"
//char currNSP[WMX_NSP_NAME_MAX_SIZE] = "xohm";

wmx_Status_t wmxApdo_getBootstrapInfo(char* nspName, pBootstrapInfo_t pBootstrapInfo)
{
	wmx_Status_t status;
	char bootstrapPath[MAX_APDO_PATH];
	char currPath[MAX_APDO_PATH];
	wmx_APDOType_t apdoType;

	if ((nspName == NULL) || (pBootstrapInfo == NULL))
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "getBootstrapInfo failed - nspName or pBootstrapInfo are NULL");
	}

	// Get info from internal data in L4DB
	OSAL_strncpy_s(bootstrapPath, MAX_APDO_PATH, BOOTSTRAP_INFO_PATH, OSAL_strnlen(BOOTSTRAP_INFO_PATH, MAX_APDO_PATH));
	OSAL_strncat_s(bootstrapPath, MAX_APDO_PATH, nspName, OSAL_strnlen(nspName, WMX_NSP_NAME_MAX_SIZE));

	// ServerID
	OSAL_strncpy_s(currPath, MAX_APDO_PATH, bootstrapPath, OSAL_strnlen(bootstrapPath, MAX_APDO_PATH));
	OSAL_strncat_s(currPath, MAX_APDO_PATH, SERVER_ID_TAG, OSAL_strnlen(SERVER_ID_TAG, MAX_APDO_PATH));

	status = wmx_GetAPDOinfo(currPath, pBootstrapInfo->serverID, &apdoType);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "getBootstrapInfo failed to get ServerID");
		return status;
	}

	// ServerURL
	OSAL_strncpy_s(currPath, MAX_APDO_PATH, bootstrapPath, OSAL_strnlen(bootstrapPath, MAX_APDO_PATH));
	OSAL_strncat_s(currPath, MAX_APDO_PATH, SERVER_URL_TAG, OSAL_strnlen(SERVER_URL_TAG, MAX_APDO_PATH));

	status = wmx_GetAPDOinfo(currPath, pBootstrapInfo->serverURL, &apdoType);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "getBootstrapInfo failed to get ServerURL");
		return status;
	}

	// ServerUserName
	OSAL_strncpy_s(currPath, MAX_APDO_PATH, bootstrapPath, OSAL_strnlen(bootstrapPath, MAX_APDO_PATH));
	OSAL_strncat_s(currPath, MAX_APDO_PATH, SERVER_USER_NAME_TAG, OSAL_strnlen(SERVER_USER_NAME_TAG, MAX_APDO_PATH));

	status = wmx_GetAPDOinfo(currPath, pBootstrapInfo->serverUserName, &apdoType);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "getBootstrapInfo failed to get serverUserName");
		return status;
	}

	// ClientUserName
	OSAL_strncpy_s(currPath, MAX_APDO_PATH, bootstrapPath, OSAL_strnlen(bootstrapPath, MAX_APDO_PATH));
	OSAL_strncat_s(currPath, MAX_APDO_PATH, CLIENT_USER_NAME_TAG, OSAL_strnlen(CLIENT_USER_NAME_TAG, MAX_APDO_PATH));

	status = wmx_GetAPDOinfo(currPath, pBootstrapInfo->clientUserName, &apdoType);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "getBootstrapInfo failed to get clientUserName");
		return status;
	}

	// portNbr
	OSAL_strncpy_s(currPath, MAX_APDO_PATH, bootstrapPath, OSAL_strnlen(bootstrapPath, MAX_APDO_PATH));
	OSAL_strncat_s(currPath, MAX_APDO_PATH, PORT_NUM_TAG, OSAL_strnlen(PORT_NUM_TAG, MAX_APDO_PATH));

	status = wmx_GetAPDOinfo(currPath, pBootstrapInfo->portNbr, &apdoType);

	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "getBootstrapInfo failed to get PortNbr");
		return status;
	}

	return status;
}

size_t clientSecretSize = 64;
char clientSecret[64];
size_t serverSecretSize = 64;
char serverSecret[64];
BOOL apdoCalcSecret;

wmx_Status_t wmx_ApdoParseBootstrap(UINT8* pBuffer, size_t buffSize, char* pPath, size_t pathSize, pXmlElement pNode, size_t* addedSizeInside)
{
	char pNewPath[MAX_APDO_PATH];
	const char* pNodeName;
	const char* pInnerText;
	int childCount;
	size_t currStrLen;
	size_t currPathSize;
	size_t remainingBuffSize;
	size_t addedSize = 0;
	size_t tempAddedInside = 0;
	int currChildIndex;
	pXmlElement pChildNode;
	BOOL writeClientSecret = FALSE;
	BOOL writeServerSecret = FALSE;
	BOOL writeClientUserName = FALSE;
	char serialnumber[MAX_DEV_ID_SIZE];
	wmx_APDOType_t apdoType;
	wmx_Status_t status;

	remainingBuffSize = buffSize;

	// Build path so far
	OSAL_strncpy_s(pNewPath, MAX_APDO_PATH, pPath, pathSize);
	pNodeName = GetElementName(pNode);

	// Handle special cases
	if (strcmp(pNodeName, "x0") == 0)
	{
		OSAL_strncat_s(pNewPath, MAX_APDO_PATH - pathSize - 1, "0", 1);
	}
	else if (strcmp(pNodeName, "x1") == 0)
	{
		OSAL_strncat_s(pNewPath, MAX_APDO_PATH - pathSize - 1, "1", 1);
	}
	else
	{
		OSAL_strncat_s(pNewPath, MAX_APDO_PATH - pathSize - 1, pNodeName, OSAL_strnlen(pNodeName, MAX_APDO_PATH));

		if ((strcmp(pNodeName, "AAuthSecret") == 0) &&
			(strcmp(pPath, "/DMAcc/xohm/AppAuth/0/") == 0))
		{
			writeClientSecret = TRUE;
		}
		else if ((strcmp(pNodeName, "AAuthSecret") == 0) &&
			(strcmp(pPath, "/DMAcc/xohm/AppAuth/1/") == 0))
		{
			writeServerSecret = TRUE;
		}
		else if ((strcmp(pNodeName, "AAuthName") == 0) &&
			(strcmp(pPath, "/DMAcc/xohm/AppAuth/0/") == 0))
		{
			writeClientUserName = TRUE;
		}
	}

	// Copy node path to buffer
	currPathSize = OSAL_strnlen(pNewPath, MAX_APDO_PATH);
	OSAL_memcpy_s(pBuffer + addedSize, buffSize, pNewPath, currPathSize);
	remainingBuffSize = remainingBuffSize - currPathSize;
	addedSize = addedSize + currPathSize;

	childCount = GetChildrenCount(pNode);

	// check if leaf
	if (childCount == 0)
	{
		// Copy leaf desc
		OSAL_memcpy_s(pBuffer + addedSize, remainingBuffSize, bootstrapLeafPrefix, BOOTSTRAP_LEAF_PREFIX_SIZE);
		remainingBuffSize = remainingBuffSize - BOOTSTRAP_LEAF_PREFIX_SIZE;
		addedSize = addedSize + BOOTSTRAP_LEAF_PREFIX_SIZE;

		// Copy leaf value
		if (writeClientSecret && apdoCalcSecret)
		{
			currStrLen = clientSecretSize;
			OSAL_memcpy_s(pBuffer + addedSize, buffSize, clientSecret, clientSecretSize);
		}
		else if (writeServerSecret && apdoCalcSecret)
		{
			currStrLen = serverSecretSize;
			OSAL_memcpy_s(pBuffer + addedSize, buffSize, serverSecret, serverSecretSize);
		}
		// If this is the client user name node and we shouldn't take xml values
		else if (writeClientUserName && apdoCalcSecret)
		{
			// Get MacAddress from L4DB
			status = wmx_GetAPDOinfo("WiMAX/WiMAXRadioModule/0/MACAddress", serialnumber, &apdoType);
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "wmx_ApdoParseBootstrap failed to get MacAddress.");
				return status;
			}

			currStrLen = OSAL_strnlen(serialnumber, MAX_DEV_ID_SIZE);
			OSAL_memcpy_s(pBuffer + addedSize, buffSize, serialnumber, currStrLen);
		}
		else
		{
			pInnerText = GetElementInnerText(pNode);
			currStrLen = OSAL_strnlen(pInnerText, MAX_APDO_PATH);
			OSAL_memcpy_s(pBuffer + addedSize, buffSize, pInnerText, currStrLen);
		}

		remainingBuffSize = remainingBuffSize - currStrLen;
		addedSize = addedSize + currStrLen;

		// Copy leaf suffix
		OSAL_memcpy_s(pBuffer + addedSize, remainingBuffSize, bootstrapLeafSuffix, BOOTSTRAP_LEAF_SUFFIX_SIZE);
		remainingBuffSize = remainingBuffSize - BOOTSTRAP_LEAF_SUFFIX_SIZE;
		addedSize = addedSize + BOOTSTRAP_LEAF_SUFFIX_SIZE;
	}
	// This is a node add path and node prefix and go over children
	else
	{
		// Copy node desc
		OSAL_memcpy_s(pBuffer + addedSize, remainingBuffSize, bootstrapNodeDesc, BOOTSTRAP_NODE_DESC_SIZE);
		remainingBuffSize = remainingBuffSize - BOOTSTRAP_NODE_DESC_SIZE;
		addedSize = addedSize + BOOTSTRAP_NODE_DESC_SIZE;

		OSAL_strncat_s(pNewPath, MAX_APDO_PATH - pathSize, "/", 1);
		currPathSize = currPathSize + 1;

		for(currChildIndex=0; currChildIndex<childCount; currChildIndex++)
		{
			pChildNode = GetChildAt(pNode, currChildIndex);
			wmx_ApdoParseBootstrap(pBuffer + addedSize, remainingBuffSize, pNewPath, currPathSize, pChildNode, &tempAddedInside);
			addedSize = addedSize + tempAddedInside;
		}
	}

	*addedSizeInside = addedSize;

	return WMX_ST_OK;
}

BOOL wmx_APDOGetServerParams(pXmlElement dmAccNode, char* serverID, int serverIdSize, char* serverURL, int serverUrlSize)
{
	pXmlElement xmlNSP;
	pXmlElement currChild;
	pXmlElement xmlAppAddrNSP;
	pXmlElement xmlAddr;
	const char* str;
	int childCount;
	int i;

	serverID[0] = '\0';
	serverURL[0] = '\0';

	xmlNSP = GetChildAt(dmAccNode, 0);

	if (xmlNSP == NULL)
	{
		return FALSE;
	}

	childCount = GetChildrenCount(xmlNSP);

	for (i=0; i<childCount; i++)
	{
		currChild = GetChildAt(xmlNSP, i);
		str = GetElementName(currChild);

		if (strcmp(str, "ServerID") == 0)
		{
			str = GetElementInnerText(currChild);
			OSAL_strncpy_s(serverID, serverIdSize, str, OSAL_strnlen(str, serverIdSize));
		}
		else if (strcmp(str, "AppAddr") == 0)
		{
			// AppAddr/NSP/Addr
			// get AppAddr
			xmlAppAddrNSP = GetChildAt(currChild, 0);

			if (xmlAppAddrNSP == NULL)
			{
				return FALSE;
			}

			// Get NSP
			xmlAddr = GetChildAt(xmlAppAddrNSP, 0);
			str = GetElementInnerText(xmlAddr);

			OSAL_strncpy_s(serverURL, serverUrlSize, str, OSAL_strnlen(str, serverUrlSize));
		}
	}

	return TRUE;
}
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetApdoOperatorConfigurations(wmx_pApdoOperatorConfigurations_t currentConfiguration, size_t currentConfigurationSize, UINT32 * currentConfigurationActualSize)
{

	wmx_Status_t status;
	wmx_pNSP_t connectedNSP  = malloc(sizeof(wmx_NSP_t));
	UINT8 response[sizeof(wmx_NSP_t)];
//	wmx_ApdoOperatorConfigurations_t connected_configuration;
	wmx_ApdoOperatorConfigurations_t ApdoOperatorConfigurations[MAX_NUM_OF_CONFIGURATIONS];
	UINT32 actualSize = (sizeof(wmx_ApdoOperatorConfigurations_t)*MAX_NUM_OF_CONFIGURATIONS);
	UINT32 responseSize = sizeof(wmx_NSP_t);
	int i;
	BOOL found = FALSE;
	UNREFERENCED_PARAMETER(currentConfiguration);

	// nardimon the get configuration only when == connected
	if (currentConfigurationSize >= (sizeof(wmx_ApdoOperatorConfigurations_t)))
	{
		// gets the apdo configurations nodes from db
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "SendNdsMsg NDNS_OPCODE_GET_APDO_OPERATOR_CONFIGURATIONS(IN)");
		status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_APDO_OPERATOR_CONFIGURATIONS,  NDNS_OPCODE_APDO, 0, NULL, &actualSize, (UINT8 *)ApdoOperatorConfigurations );
		if (status != WMX_ST_OK)
		{
			free(connectedNSP);
			TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "SendNdsMsg NDNS_OPCODE_GET_APDO_OPERATOR_CONFIGURATIONS(OUT) status= %d", status);
			return status;
		}
		// gets the last connectd nsp from db
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "SendNdsMsg GetConnectedNSP for APDO(IN)");
		status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_CONNECTED_NSP_FOR_APDO, NDNS_OPCODE_APDO, 0, NULL, &responseSize, response );
		if( status != WMX_ST_OK )
		{
			free(connectedNSP);
			TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "SendNdsMsg GetConnectedNSP(OUT) status= %d", status);
			return status;
		}
		if (connectedNSP != NULL)
		{
			*connectedNSP = *(wmx_pNSP_t)response;

			TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "SendNdsMsg GetConnectedNSP(OUT) connectedNSP = %d", *connectedNSP);
		}
	}
	else
	{
		free(connectedNSP);
		status = WMX_ST_RESPONSE_BUFFER_TOO_SHORT;
		return status;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "Trying wmx_GetPollingIntervalSupportedMode..");
	status = wmx_GetPollingIntervalSupportedMode (&currentConfiguration->pollingSupported);
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "Trying wmx_GetPollingIntervalSupportedMode status = [%d], Using default TRUE", status);
		currentConfiguration->pollingSupported = TRUE;
	}

	for (i=0 ; i < MAX_NUM_OF_CONFIGURATIONS && found == FALSE; i++)
	{
		if (OSAL_stricmp(MAX_TAG_NAME_DEFAULT,  ApdoOperatorConfigurations[i].nspTagName)==0)
		{
			TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG, "Set configuration entry [%d] to DEFAULT", i);
			OSAL_memcpy_s(&currentConfiguration->nspTagName , sizeof(char)*MAX_SIZE_OF_NSP_NAME, MAX_TAG_NAME_DEFAULT,sizeof(char)*MAX_SIZE_OF_NSP_NAME) ;
			OSAL_memcpy_s(&currentConfiguration->preProvBStrap , sizeof(BOOL), &ApdoOperatorConfigurations[i].preProvBStrap,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->pollingInterval , sizeof(BOOL), &ApdoOperatorConfigurations[i].pollingInterval,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->blockUDP , sizeof(BOOL), &ApdoOperatorConfigurations[i].blockUDP,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->pollingAttempts, sizeof(BOOL), &ApdoOperatorConfigurations[i].pollingAttempts,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->disableOTAP, sizeof(BOOL), &ApdoOperatorConfigurations[i].disableOTAP,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->disablePseudoNAI, sizeof(BOOL), &ApdoOperatorConfigurations[i].disablePseudoNAI,sizeof(BOOL)) ;
			*currentConfigurationActualSize = sizeof (wmx_ApdoOperatorConfigurations_t);
			status = WMX_ST_OK;
		}
		if (OSAL_stricmp(connectedNSP->nspName,  ApdoOperatorConfigurations[i].nspTagName)==0)
		{
			TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG, "Set configuration entry [%d] to [%s]", i, ApdoOperatorConfigurations[i].nspTagName);
			OSAL_memcpy_s(&currentConfiguration->nspTagName , sizeof(char)*MAX_SIZE_OF_NSP_NAME, &ApdoOperatorConfigurations[i].nspTagName,sizeof(char)*MAX_SIZE_OF_NSP_NAME) ;
			OSAL_memcpy_s(&currentConfiguration->preProvBStrap , sizeof(BOOL), &ApdoOperatorConfigurations[i].preProvBStrap,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->pollingInterval , sizeof(BOOL), &ApdoOperatorConfigurations[i].pollingInterval,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->blockUDP , sizeof(BOOL), &ApdoOperatorConfigurations[i].blockUDP,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->pollingAttempts, sizeof(BOOL), &ApdoOperatorConfigurations[i].pollingAttempts,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->disableOTAP, sizeof(BOOL), &ApdoOperatorConfigurations[i].disableOTAP,sizeof(BOOL)) ;
			OSAL_memcpy_s(&currentConfiguration->disablePseudoNAI, sizeof(BOOL), &ApdoOperatorConfigurations[i].disablePseudoNAI,sizeof(BOOL)) ;
			*currentConfigurationActualSize = sizeof (wmx_ApdoOperatorConfigurations_t);
			found = TRUE;
			status = WMX_ST_OK;
		}
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_DEBUG, "wmx_GetApdoOperatorConfigurations return nspTagName=[%s],preProvBStrap=[%d],pollingInterval=[%d],blockUDP=[%d],pollingAttempts=[%d],disableOTAP=[%d]",
		currentConfiguration->nspTagName, currentConfiguration->preProvBStrap, currentConfiguration->pollingInterval, currentConfiguration->blockUDP, currentConfiguration->pollingAttempts, currentConfiguration->disableOTAP);
	return status;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetPollingIntervalSupportedMode (BOOL *pPollingIntervalSupported){

	wmx_Status_t status = WMX_ST_FAIL;
	UINT32 actualSize = sizeof(BOOL);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "SendNdsMsg NDNS_OPCODE_GET_DEV_CAP(IN)");
	status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_POLLING_SUPPORTED,  NDNS_OPCODE_APDO, 0, NULL, &actualSize, (UINT8 *)pPollingIntervalSupported );
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "SendNdsMsg NDNS_OPCODE_GET_DEV_CAP(OUT) status = [%d] Using default pollingSupported = TRUE", status);

	}

	return status;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ApdoGetServerParams(UINT8* buffer, size_t bufferSize, size_t * actualSize)
{
	BOOL res;
	size_t fileSize = 3298;
	UINT8* pTempBuffer;
	char serialnumber[MAX_DEV_ID_SIZE];
	char devID[MAX_DEV_ID_SIZE];
	size_t macSize;

	char pSharedSecret[MAX_ANSWER_SIZE];
	// Used to make sure the data we are copying to the buffer is in the correct size
	size_t currSize;
	size_t currStrLen;

	wmx_Status_t status;
	wmx_APDOType_t apdoType;
	pXmlElement xmlRoot;
	pXmlElement	xmlDmAcc;
	pXmlElement	xmlNSP;
	const char* str;
	char nspPath[MAX_APDO_PATH];
	size_t addedInside = 0;
	char apdoCalcSecretW[MAX_ANSWER_SIZE];
	char serverID[MAX_SERVER_ID_SIZE];
	char serverURL[MAX_SERVER_URL_SIZE];
	wmx_ApdoOperatorConfigurations_t currentApdoOperatorConfigurations;
	wmx_NSP_t tempNSP;
	UINT32 responseLength = (UINT32)(sizeof(wmx_ApdoOperatorConfigurations_t));
	tempNSP.activated = TRUE;


	TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_DEBUG, "wmx_ApdoGetServerParams enter function");
	status = wmx_GetApdoOperatorConfigurations (&currentApdoOperatorConfigurations , sizeof(currentApdoOperatorConfigurations), &responseLength);

	if (status == WMX_ST_OK)
	{
		if (currentApdoOperatorConfigurations.preProvBStrap == TRUE)
		{
			// Check if the input buffer size is less then needed and if so return error and actual size
			if (fileSize > bufferSize)
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_ApdoGetServerParams buffer size is not enough");
				*actualSize = fileSize;
				return WMX_ST_BUFFER_TOO_SHORT;
			}

			// Read xml file with bootstrap configuration
			xmlRoot = CreateEmptyXmlData();

			res = ReadXmlFile(xmlRoot, "bootstrap.xml");
			if(FALSE == res)
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "wmx_ApdoGetServerParams failed to load bootstrap.xml");
				return WMX_ST_FAIL;
			}

			str = GetElementName(xmlRoot);
			xmlDmAcc = GetChildAt(xmlRoot, 0);
			str = GetElementName(xmlDmAcc);

			// Try to read parameters from xml
			if (!wmx_APDOGetServerParams(xmlDmAcc, serverID, MAX_SERVER_ID_SIZE, serverURL, MAX_SERVER_URL_SIZE))
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "wmx_ApdoGetServerParams failed to read server params from xml");
				return WMX_ST_FAIL;
			}

			// Init response
			*actualSize = 0;
			currSize = bufferSize;

			// Check if need to leave secret configuration or do calculation
			L4Configurations_getApdoCalcSecret(apdoCalcSecretW);

			if (strcmp(apdoCalcSecretW, "True") == 0)
			{
				apdoCalcSecret = TRUE;
			}
			else
			{
				apdoCalcSecret = FALSE;
			}

			/////// Start building message

			// Copy header
			OSAL_memcpy_s(buffer, currSize, bootstrapHeader, BOOTSTRAP_HEADER_SIZE);
			currSize = currSize - BOOTSTRAP_HEADER_SIZE;
			pTempBuffer = buffer + BOOTSTRAP_HEADER_SIZE;
			*actualSize = *actualSize + BOOTSTRAP_HEADER_SIZE;

			// Copy device id with prefix
			status = wmx_GetAPDOinfo("DevInfo/DevId", devID, &apdoType);
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "wmx_ApdoGetServerParams failed to get devID.");
				return status;
			}

			macSize = OSAL_strnlen(devID, MAX_DEV_ID_SIZE);
			OSAL_memcpy_s(pTempBuffer, currSize, devID, macSize);
			currSize = currSize - macSize;
			pTempBuffer = pTempBuffer + macSize;
			*actualSize = *actualSize + macSize;

			// Copy continue of message
			OSAL_memcpy_s(pTempBuffer, currSize, bootstrapDevIdSuffix, BOOTSTRAP_DEV_ID_SUFFIX_SIZE);
			currSize = currSize - BOOTSTRAP_DEV_ID_SUFFIX_SIZE;
			pTempBuffer = pTempBuffer + BOOTSTRAP_DEV_ID_SUFFIX_SIZE;
			*actualSize = *actualSize + BOOTSTRAP_DEV_ID_SUFFIX_SIZE;

			// Copy server URL
			currStrLen = OSAL_strnlen(serverURL, MAX_SERVER_URL_SIZE);
			OSAL_memcpy_s(pTempBuffer, currSize, serverURL, currStrLen);
			currSize = currSize - currStrLen;
			pTempBuffer = pTempBuffer + currStrLen;
			*actualSize = *actualSize + currStrLen;

			// Copy continue of message
			OSAL_memcpy_s(pTempBuffer, currSize, bootstrapServerUrlSuffix, BOOTSTRAP_SERVER_URL_SUFFIX_SIZE);
			currSize = currSize - BOOTSTRAP_SERVER_URL_SUFFIX_SIZE;
			pTempBuffer = pTempBuffer + BOOTSTRAP_SERVER_URL_SUFFIX_SIZE;
			*actualSize = *actualSize + BOOTSTRAP_SERVER_URL_SUFFIX_SIZE;

			// Start parsing the dmAcc tree
			xmlNSP = GetChildAt(xmlDmAcc, 0);
			OSAL_strncpy_s(nspPath, MAX_APDO_PATH, "/", 1);
			OSAL_strncat_s(nspPath, MAX_APDO_PATH, str, OSAL_strnlen(str, MAX_APDO_PATH));
			str = GetElementName(xmlNSP);
			OSAL_strncat_s(nspPath, MAX_APDO_PATH, "/", 1);

			// Read secret
			L4Configurations_getApdoSharedSecret(pSharedSecret);
			//[nDenes]
			if ( MAX_ANSWER_SIZE == (size_t)OSAL_strnlen(pSharedSecret, MAX_ANSWER_SIZE) )
			{
				TRACE(TR_MOD_COMMON_API, TR_SEV_ERR, "wmx_ApdoGetServerParams Failed - pSharedSecretW is too long");
				status = WMX_ST_FAIL;
			}

			// Get MacAddress from L4DB
			status = wmx_GetAPDOinfo("WiMAX/WiMAXRadioModule/0/MACAddress", serialnumber, &apdoType);
			if (status != WMX_ST_OK)
			{
				TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "wmx_ApdoGetServerParams failed to get MacAddress.");
				return status;
			}

			// Calculate client secret
			OSAL_CalcSecret(serialnumber, serverID, pSharedSecret, clientSecret, &clientSecretSize);

			// Calculate server secret
			OSAL_CalcSecret(serverID, serialnumber, pSharedSecret, serverSecret, &serverSecretSize);

			wmx_ApdoParseBootstrap(pTempBuffer, currSize, nspPath, OSAL_strnlen(nspPath, MAX_APDO_PATH), xmlNSP, &addedInside);

			*actualSize = *actualSize + addedInside;
			pTempBuffer = pTempBuffer + addedInside;

			// Copy continue of message
			OSAL_memcpy_s(pTempBuffer, currSize, bootstrapEnd, BOOTSTRAP_END_SIZE);
			*actualSize = *actualSize + BOOTSTRAP_END_SIZE;

			return WMX_ST_OK;
		}
}
	return WMX_ST_FAIL;
}

//////////////////

// Helper function
wmx_Status_t wmxApdo_SendNdsMsg(
	UINT32 opcode, NDNS_AGENT_L5_OPCODE ndnsOpcode,
	UINT32 requestLength, UINT8 *request,
	UINT32 *responseLength, UINT8 *response )
{
	// results
	L5_RESULT l5Result;
	wmx_Status_t st;

	// Request Fields
	UINT32 messageSize;
	pNDNS_MESSAGE pMessage;

	// Response Fields
	UINT32 responseID = (UINT32)WMX_ST_FAIL;

	// Check that the variables are initialized
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (apdo_wrapper_l5ConnID == NULL ||
		apdo_wrapper_pFuncs == NULL || pcs_apdo_funcs == NULL /* || cs_apdo_funcs.DebugInfo == NULL */)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}

	// create the request
	messageSize = sizeof(NDNS_MESSAGE) + requestLength;
	pMessage = (pNDNS_MESSAGE)malloc(messageSize);
	pMessage->opcode = opcode;
	pMessage->bufferLength = requestLength;
	if (requestLength > 0)
	{
		VERIFY( request != NULL );
		OSAL_memcpy_s(pMessage->buf, requestLength, request, requestLength);
	}

	// sent the request
	if (NULL != apdo_wrapper_pFuncs)
	{
		l5Result = apdo_wrapper_pFuncs->pfnSendReceiveMessage(
							apdo_wrapper_l5ConnID, L5_TARGET_NDNS, ndnsOpcode,
							pMessage, messageSize, &responseID, response, responseLength );
	}
	else
	{
		l5Result = L5_RESULT_NO_HANDLER;
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	free(pMessage);

	// check the l5 result
	st = wmx_L5ResultToWMXStatus( l5Result );
	if( st != WMX_ST_OK )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "l5 result is %d", l5Result);
		return st;
	}

	// check the status received from the ndns agent
	if( WMX_ST_OK != (wmx_Status_t)responseID )
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ERR, "ndns response id is %d", responseID);
		return (wmx_Status_t)responseID;
	}

	return WMX_ST_OK;
}