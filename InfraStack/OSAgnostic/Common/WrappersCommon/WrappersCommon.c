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
#include "WrappersCommon.h"
#include "L4ConfigurationManager.h"


static char lastError[LAST_ERROR_MAX_SIZE];


EXPORT USHORT GetPortNum()
{
	UINT32 port;

	L4Configurations_getSdkPortNum(&port);

	return (USHORT)port;
}

EXPORT void wmx_ResetLastError()
{
	memset(lastError, '\0', LAST_ERROR_MAX_SIZE);
}

EXPORT LPCCH wmx_GetLastError()
{
	return lastError;
}

EXPORT void wmx_SetLastError(char *str)
{
	size_t size = strlen(str);

	if(size > LAST_ERROR_MAX_SIZE)
	{
		return;
	}

	wmx_ResetLastError();
	memcpy(lastError, str, size);
}

char *wmxGetStatusStr(wmx_Status_t status)	// @@@ : JSS : Corrected param type
{
	char *returnStr;
	switch (status)
	{
	case WMX_ST_OK:
		returnStr = "WMX_ST_OK";
		break;
	case WMX_ST_PIPE_FAILURE:
		returnStr = "WMX_ST_PIPE_FAILURE";
		break;
	case WMX_ST_PIPE_NOT_CONNETED:
		returnStr = "WMX_ST_PIPE_NOT_CONNETED";
		break;
	case WMX_ST_DEVICE_FAILURE:
		returnStr = "WMX_ST_DEVICE_FAILURE";
		break;
	case WMX_ST_DEVICE_NOT_FOUND:							
		returnStr = "WMX_ST_DEVICE_NOT_FOUND";
		break;
	case WMX_ST_DEVICE_BUSY:
		returnStr = "WMX_ST_DEVICE_BUSY";
		break;
	case WMX_ST_DEVICE_NOT_READY:
		returnStr = "WMX_ST_DEVICE_NOT_READY";
		break;
	case WMX_ST_CALLBACK_NOT_REGISTERED:
		returnStr = "WMX_ST_CALLBACK_NOT_REGISTERED";
		break;
	case WMX_ST_CALLBACK_ALREADY_REGISTERED:
		returnStr = "WMX_ST_CALLBACK_ALREADY_REGISTERED";
		break;
	case WMX_ST_INDICATION_NOT_REGISTERED:
		returnStr = "WMX_ST_INDICATION_NOT_REGISTERED";
		break;
	case WMX_ST_INDICATION_ALREADY_REGISTERED:
		returnStr = "WMX_ST_INDICATION_ALREADY_REGISTERED";
		break;
	case WMX_ST_NO_ROOM_FOR_INDICATION:
		returnStr = "WMX_ST_NO_ROOM_FOR_INDICATION";
		break;
	case WMX_ST_ILLEGAL_OPERATION:
		returnStr = "WMX_ST_ILLEGAL_OPERATION";
		break;
	case WMX_ST_INVALID_OPCODE:
		returnStr = "WMX_ST_INVALID_OPCODE";
		break;
	case WMX_ST_DATA_UNAVAILABLE:							
		returnStr = "WMX_ST_DATA_UNAVAILABLE";
		break;
	case WMX_ST_MODULE_NOT_INITIALIZED:						
		returnStr = "WMX_ST_MODULE_NOT_INITIALIZED";
		break;
	case WMX_ST_CONFIG_ERROR:
		returnStr = "WMX_ST_CONFIG_ERROR";
		break;
	case WMX_ST_VERSION_VALIDATION_ERROR:
		returnStr = "WMX_ST_VERSION_VALIDATION_ERROR";
		break;
	case WMX_ST_VERSION_VALIDATION_WARNING:
		returnStr = "WMX_ST_VERSION_VALIDATION_WARNING";
		break;
	case WMX_ST_RESPONSE_BUFFER_TOO_SHORT:					
		returnStr = "WMX_ST_RESPONSE_BUFFER_TOO_SHORT";
		break;
	case WMX_ST_NULL_APPSRV_IP_ADDRESS:						
		returnStr = "WMX_ST_NULL_APPSRV_IP_ADDRESS";
		break;
	case WMX_ST_TRACE_INIT_FAILED:							
		returnStr = "WMX_ST_TRACE_INIT_FAILED";
		break;
	case WMX_ST_NULL_L5_DISPATCHER_FUNCTIONS_POINTER:
		returnStr = "WMX_ST_NULL_L5_DISPATCHER_FUNCTIONS_POINTER";
		break;
	case WMX_ST_PIPE_HANDLER_LOAD_FAILED:
		returnStr = "WMX_ST_PIPE_HANDLER_LOAD_FAILED";
		break;
	case WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED:			
		returnStr = "WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED";
		break;
	case WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED:
		returnStr = "WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED";
		break;
	case WMX_ST_SPECIFIC_WRAPPER_SET_MSNGR_FUNCTIONS_FAILED:
		returnStr = "WMX_ST_SPECIFIC_WRAPPER_SET_MSNGR_FUNCTIONS_FAILED";
		break;
	case WMX_ST_IWMXSDK_INTERNAL_FAILURE:
		returnStr = "WMX_ST_IWMXSDK_INTERNAL_FAILURE";
		break;
	case WMX_ST_BUFFER_TOO_SHORT:							
		returnStr = "WMX_ST_BUFFER_TOO_SHORT";
		break;
	case WMX_ST_WRONG_ARGUMENT:
		returnStr = "WMX_ST_WRONG_ARGUMENT";
		break;
	case WMX_ST_NSP_ID_NOT_FOUND:
		returnStr = "WMX_ST_NSP_ID_NOT_FOUND";
		break;
	case WMX_ST_APDO_PATH_NOT_FOUND:				
		returnStr = "WMX_ST_APDO_PATH_NOT_FOUND";
		break;
	case WMX_ST_DEVICE_NOT_PROVISIONED:
		returnStr = "WMX_ST_DEVICE_NOT_PROVISIONED";
		break;
	case WMX_ST_WRONG_STATE:
		returnStr = "WMX_ST_WRONG_STATE";
		break;

	case WMX_ST_NO_RF:
		returnStr = "WMX_ST_NO_RF";
	break;

	case WMX_ST_FAIL:
		returnStr = "WMX_ST_FAIL";
		break;
	default:
		returnStr = "";
	}
	return returnStr;
}
