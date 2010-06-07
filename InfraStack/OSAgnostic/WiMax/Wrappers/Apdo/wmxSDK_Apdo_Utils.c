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
#include "L5Common.h"
#include "L5OpCodes.h"		// @@@ : JSS - correct case name
#include "WrappersUtils.h"

#include "TraceModule.h"

#include "wmxSDK_Apdo_Internals.h"

#include "wmxSDK_Nds_L5.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "wmxSDK_Apdo_Utils.h"


extern OSAL_critical_section *pcs_apdo_funcs;
//******************* APDO staff *******************//

int wmxApdo_GetBufferLength(void *value, wmx_APDOType_t apdoType);

// The function concatenates the parameters given to the resultBuffer.
// Assumes that resultBuffer is allocated by the user of the function.
void wmxApdo_CreateApdoBufferWithValue( wmx_APDOType_t APDOType, wmx_APDOPath_t remotePath, char *APDOValue, char *resultBuffer )
{
	size_t remotePathLength, APDOValueLength;
	
	remotePathLength = OSAL_strnlen((const char*)remotePath, MAX_APDO_PATH) + 1;	// + 1 for the \0
	APDOValueLength = wmxApdo_GetBufferLength(APDOValue, APDOType);

	OSAL_memcpy_s(resultBuffer, sizeof(wmx_APDOType_t), &APDOType, sizeof(wmx_APDOType_t));
	OSAL_memcpy_s(resultBuffer + sizeof(wmx_APDOType_t), remotePathLength, remotePath, remotePathLength);	
	OSAL_memcpy_s(resultBuffer + sizeof(wmx_APDOType_t) + remotePathLength, APDOValueLength, APDOValue, APDOValueLength);
}

// The function concatenates the parameters given to the resultBuffer,
// assumes that resultBuffer is allocated by the user of the function
void wmxApdo_CreateAPDOBuffer( wmx_APDOType_t APDOType, wmx_APDOPath_t remotePath, char *resultBuffer )
{
	size_t remotePathLength;
	
	remotePathLength = OSAL_strnlen((const char*)remotePath, MAX_APDO_PATH) + 1;	// + 1 for the \0

	OSAL_memcpy_s(resultBuffer, sizeof(wmx_APDOType_t), &APDOType, sizeof(wmx_APDOType_t));
	OSAL_memcpy_s(resultBuffer + sizeof(wmx_APDOType_t), remotePathLength, remotePath, remotePathLength);	
}

// Parse the input buffer and fill pAPDOPath, pValue and pAPDOType.
// The function doesn't copy the data, just points to the right location in the inputBuffer.
void wmxApdo_ParseAPDOBuffer(char *inputBuffer, wmx_pAPDOPath_t pAPDOPath, char **pValue, wmx_pAPDOType_t pAPDOType)
{
	int APDOPathLength;

	*pAPDOType = *(wmx_pAPDOType_t)inputBuffer;
	*pAPDOPath = (wmx_APDOPath_t)inputBuffer + sizeof(wmx_APDOType_t);

	APDOPathLength = (int)OSAL_strnlen((const char*)*pAPDOPath, MAX_APDO_PATH) + 1; // 1 for the \0
	*pValue = (char*)*pAPDOPath + APDOPathLength;
}

// Parse the input buffer and fill pAPDOPath and pAPDOType.
// The function doesn't copy the data, just points to the right location in the inputBuffer.
void wmxApdo_ParseAPDOBufferNoValue(char *inputBuffer, wmx_pAPDOPath_t pAPDOPath, wmx_pAPDOType_t pAPDOType)
{	
	*pAPDOType = *(wmx_pAPDOType_t)inputBuffer;
	*pAPDOPath = (wmx_APDOPath_t)inputBuffer + sizeof(wmx_APDOType_t);
}

// Gets a null terminated buffer and translate it to the corresponding Enum value
void wmxApdo_TranslateStringAPDOTypeToEnum(char *strAPDOType, wmx_pAPDOType_t pAPDOType)
{
	if (strcmp(strAPDOType, "int") == 0)
	{
		*pAPDOType = APDO_Integer;				
	}
	else if (strcmp(strAPDOType, "float") == 0)
	{
		*pAPDOType = APDO_Float;
	}
	else if (strcmp(strAPDOType, "double") == 0)
	{
		*pAPDOType = APDO_Double;
	}
	else if (strcmp(strAPDOType, "bool") == 0)
	{
		*pAPDOType = APDO_Bool;
	}
	else if (strcmp(strAPDOType, "node") == 0)
	{
		*pAPDOType = APDO_Node;
	}
	else
	{
		*pAPDOType = APDO_String;
	}
}

int wmxApdo_GetBufferLength(void *value, wmx_APDOType_t apdoType)
{
	int result = 0;

	// In case of string leave the pointer is it is.
	switch (apdoType)
	{		
		case APDO_Integer:
			result = sizeof(int);
			break;
		case APDO_Float:
			result = sizeof(float);
			break;
		case APDO_Double:
			result = sizeof(double);
			break;
		case APDO_Bool:
			result = sizeof(BOOL);
			break;
		case APDO_String:
		case APDO_Node:
			result = (int)OSAL_strnlen((char*)value, MAX_APDO_GET_RESULT) + 1; // + 1 for \0						  
	}

	return result;
}

// Register on indications
wmx_Status_t wmxApdo_RegisterOnApdoLinkStatusInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (NULL == apdo_wrapper_pFuncs)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return status;
	}
	status = wmx_RegisterOnAgentIndication( 
		&g_numOfApdoLinkStatusIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_APDO_LINK_STATUS, 
		*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_RegisterOnApdoAlertResponseInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (NULL == apdo_wrapper_pFuncs)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return status;
	}
	status = wmx_RegisterOnAgentIndication( 
		&g_numOfApdoAlertResponseIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_APDO_ALERT_RESPONSE, 
		*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_RegisterOnApdoSessionStatusInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (NULL == apdo_wrapper_pFuncs)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return status;
	}
	status = wmx_RegisterOnAgentIndication( 
		&g_numOfApdoSessionStatusIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_APDO_SESSION_STATUS, 
		*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_RegisterOnApdoOobNotificationInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (NULL == apdo_wrapper_pFuncs)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return status;
	}
	status = wmx_RegisterOnAgentIndication( 
		&g_numOfApdoOobNotificationIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_APDO_OOB_NOTIFICATION, 
		*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_RegisterOnApdoFumoDownloadApprovalStatusInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (NULL == apdo_wrapper_pFuncs)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return status;
	}
	status = wmx_RegisterOnAgentIndication( 
		&g_numOfApdoFumoDownloadApprovalStatusIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_APDO_FUMO_DL_APPROVAL_STATUS, 
		*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_RegisterOnApdoDeleteDMAccountInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (NULL == apdo_wrapper_pFuncs)
	{
		OSAL_exit_critical_section(pcs_apdo_funcs);
		return status;
	}
	status = wmx_RegisterOnAgentIndication( 
		&g_numOfApdoDeleteDMAccountIndRegs, 
		L5_TARGET_NDNS, 
		NDNS_OPCODE_REGISTER_INDICATION, 
		NDNS_OPCODE_IND_APDO_DELETE_DM_ACCOUNT, 
		*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_UnregisterOnApdoLinkStatusInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if(apdo_wrapper_pFuncs != NULL)
	{
		status = wmx_UnregisterOnAgentIndication( 
			&g_numOfApdoLinkStatusIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_APDO_LINK_STATUS, 
			*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_UnregisterOnApdoAlertResponseInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if(apdo_wrapper_pFuncs != NULL)
	{
		status = wmx_UnregisterOnAgentIndication( 
			&g_numOfApdoAlertResponseIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_APDO_ALERT_RESPONSE, 
			*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_UnregisterOnApdoSessionStatusInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if(apdo_wrapper_pFuncs != NULL)
	{
		status = wmx_UnregisterOnAgentIndication( 
			&g_numOfApdoSessionStatusIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_APDO_SESSION_STATUS, 
			*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_UnregisterOnApdoOobNotificationInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if(apdo_wrapper_pFuncs != NULL)
	{
		status =  wmx_UnregisterOnAgentIndication( 
			&g_numOfApdoOobNotificationIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_APDO_OOB_NOTIFICATION, 
			*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_UnregisterOnApdoFumoDownloadApprovalStatusInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if(apdo_wrapper_pFuncs != NULL)
	{
		status =  wmx_UnregisterOnAgentIndication( 
			&g_numOfApdoFumoDownloadApprovalStatusIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_APDO_FUMO_DL_APPROVAL_STATUS, 
			*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

wmx_Status_t wmxApdo_UnregisterOnApdoDeleteDMAccountInd()
{
	wmx_Status_t status = WMX_ST_FAIL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if(apdo_wrapper_pFuncs != NULL)
	{
		status =  wmx_UnregisterOnAgentIndication( 
			&g_numOfApdoDeleteDMAccountIndRegs, 
			L5_TARGET_NDNS, 
			NDNS_OPCODE_UNREGISTER_INDICATION, 
			NDNS_OPCODE_IND_APDO_DELETE_DM_ACCOUNT, 
			*apdo_wrapper_pFuncs, apdo_wrapper_l5ConnID );
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	return status;
}

