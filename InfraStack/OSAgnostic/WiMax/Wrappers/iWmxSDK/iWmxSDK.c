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
#include "iWmxSDK.h"
//#include "iWmxSDKVersion.h"
#include "Versions.h"

#include "CommonServices.h"
#include "wimax_osal_config_controler.h"
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"

#include "TraceModule.h"

#include "Services_Ctrl.h"
#include "WrappersCommon.h"
#include "PipeHandler_Ctrl.h"
#include "PipeHandler.h"

static LONG s_initRefCnt = 0;
static tL5DispatcherFunctions *L5funcs = NULL;
static tUtilityFunctions *UtilFuncs = NULL;

wmx_Version_t g_atVersionWrapper;
char g_atWrapperName[WRAPPER_NAME_LEN];

// External functions
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_Init()
{
    
    
	wmx_Version_t expectedPipeHandlerVersion;
	wmx_Version_t pipeHandlerVersion;
	VERSION_RESULT versionResult;	
	
	if ( FIRST_INIT == OSAL_atomic_increment(&s_initRefCnt) )
	{
		if ((!Services_Init()) || (!PIPE_HANDLER_Init()))
		{
			wmxSDK_Finalize();
			return WMX_ST_FAIL;
		}				
       TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_Init()");
		
		pipeHandlerVersion = PIPE_HANDLER_GetVersion();

		if (IsVersionValidationEnabled())
		{			
			// set expected versions of modules in use
			SET_VERSION(expectedPipeHandlerVersion, PIPE_HANDLER_MAJOR, PIPE_HANDLER_MINOR, PIPE_HANDLER_BUILD, PIPE_HANDLER_REVISION, PIPE_HANDLER_BRANCH);
			versionResult =  ValidateVersion("PipeHandler", pipeHandlerVersion, expectedPipeHandlerVersion);
			if (versionResult != VER_SUCCESS && versionResult != VER_SUCCESS_INVALID_MINOR)
			{
				TRACE(TR_MOD_SERVICE, TR_SEV_ERR, "PipeHandler version validation failed.");
				wmxSDK_Finalize();
				return WMX_ST_VERSION_VALIDATION_ERROR;
			}
		}

		L5funcs = PIPE_HANDLER_GetServiceDispatcherFunctions();
		if (L5funcs == NULL)
		{
			TRACE(TR_MOD_SERVICE, TR_SEV_ERR, "Got NULL pointer for tL5funcsFunctions.");
			wmxSDK_Finalize();
			return WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED;
		}	

		UtilFuncs = PIPE_HANDLER_GetUtilityFunctions();
		if (UtilFuncs == NULL)
		{
			TRACE(TR_MOD_SERVICE, TR_SEV_ERR, "Got NULL pointer for UtilFuncs.");
			wmxSDK_Finalize();
			return WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED;
		}	
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_Init(OUT)");

	return WMX_ST_OK;
}

void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_Finalize()
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "void wmxSDK_Finalize()");
    
    
	if ( LAST_INIT == OSAL_atomic_decrement(&s_initRefCnt) )
	{		
		L5funcs = NULL;
		UtilFuncs = NULL;
		Services_Fini();
		PIPE_HANDLER_Finalize();
	}

	OSAL_atomic_compareExchange(&s_initRefCnt, LAST_INIT, LAST_INIT - 1);
}

tL5DispatcherFunctions *GetL5Funcs()
{
	return L5funcs;
}


tUtilityFunctions *GetUtilsFuncs()
{
	return UtilFuncs;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_GetVersion(wmx_pVersion_t version, wmx_pVersionStr_t versionStr, wmx_VersionStrLen_t *verMaxLen)
{
	char tempVersionStr[VERSION_MAX_LEN];	

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_GetVersion(wmx_pVersion_t version, wmx_pVersionStr_t versionStr, wmx_VersionStrLen_t *verMaxLen)");
	
	if (version != NULL)
	{
		version->major = g_atVersionWrapper.major;
		version->minor = g_atVersionWrapper.minor;
		version->build = g_atVersionWrapper.build;
		version->revision = g_atVersionWrapper.revision;
		version->branch = g_atVersionWrapper.branch;
	}
	OSAL_sprintf_s( tempVersionStr, 50, "%s %d.%d.%d.%d.%d", g_atWrapperName, g_atVersionWrapper.major, g_atVersionWrapper.minor, g_atVersionWrapper.build, g_atVersionWrapper.revision, g_atVersionWrapper.branch );
	if (versionStr != NULL)
	{		
		if (*verMaxLen >= strlen(tempVersionStr))
		{			
			OSAL_strcpy_s(versionStr, strlen(tempVersionStr)+1, tempVersionStr);
			*verMaxLen = strlen(tempVersionStr);
		}
		else
		{
			return WMX_ST_BUFFER_TOO_SHORT;
		}
	}
	else
	{
		return WMX_ST_WRONG_ARGUMENT;
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_GetVersion(OUT)");

	return WMX_ST_OK;
}

// PipeHandler new functionality
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)");
    
    
	if (L5funcs != NULL)
	{
		return L5funcs->pfnRegisterCtrlStatusUpdatesCB(ctrlStatusUpdateCB);
	}
	else // error - called before init
	{
        TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmxSDK_RegisterCtrlStatusUpdatesCB(OUT ERROR)");
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}	
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB)");

	if (L5funcs != NULL)
	{
		return L5funcs->pfnUnregisterCtrlStatusUpdatesCB(ctrlStatusUpdateCB);
	}
	else // error - called before init
	{
        TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmxSDK_UnregisterCtrlStatusUpdatesCB(OUT ERROR)");

		return WMX_ST_MODULE_NOT_INITIALIZED;
	}
}

wmx_CtrlStatus_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_GetCtrlStatus()
{
	if (L5funcs != NULL)
	{
		return L5funcs->pfnGetCtrlStatus();
	}
	else // error - called before init
	{
		return NOT_READY;
	}	
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_SetConnParams(char *szHostName, int nPort)
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_SetConnParams(char *szHostName, int nPort)");
    
	if (L5funcs != NULL)
	{
		return L5funcs->pfnSetConnParams(szHostName, nPort);
	}
	else // error - called before init
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxSDK_SetConnParams(OUT)");
		return WMX_ST_MODULE_NOT_INITIALIZED;
	}
}

