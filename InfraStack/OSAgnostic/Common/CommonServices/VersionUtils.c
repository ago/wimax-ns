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
#include "VersionUtils.h"

#include "L4ConfigurationManager.h"
#include "TraceModule.h"
#include "wimax_osal_event_logger.h"
#include "wimax_osal_string.h"

static BOOL g_vrs_bIsVersionValidationEnabled = FALSE;


BOOL VersionUtils_Init()
{
	BOOL res;
	UINT32 verEnableRes;

	res =  L4Configurations_getEnableVersioning(&verEnableRes);
	if (res == FALSE)
	{
		// by default we enable version validation
		g_vrs_bIsVersionValidationEnabled = TRUE;
		//wmx_EventLogger_GenericLog(EVENTLOG_ERROR_TYPE, MSG_VERSION_ERROR, 1,"Unable to read the VersioningEnabled flag from the registry.");
		TRACE(TR_MOD_SERVICE, TR_SEV_ERR,"Unable to read the VersioningEnabled flag from the registry. Returned default value!");
	}
	else
	{
		g_vrs_bIsVersionValidationEnabled = (verEnableRes != 0) ? TRUE : FALSE;
	}

	return TRUE;
}

void VersionUtils_Fini()
{

}



EXPORT BOOL IsVersionValidationEnabled()
{
	return g_vrs_bIsVersionValidationEnabled;
}

EXPORT void GetFullVersionString(char *str, wmx_Version_t version)
{
	OSAL_sprintf_s( str, 20, "%d.%d.%d.%d.%d",version.major,version.minor, version.build, version.revision, version.branch );
}

EXPORT void GetVersionString(char *str, wmx_Version_t version)
{
	OSAL_sprintf_s( str, 20, "*.*.%d.%d.%d", version.build, version.revision, version.branch );
}

EXPORT VERSION_RESULT ValidateVersion(wmx_ModuleName_t moduleName, wmx_Version_t actualVersion, wmx_Version_t expectedVersion)
{	
	char versionActualStr[VER_STR_LEN] = {0};
	char versionExpectedStr[VER_STR_LEN] = {0};
	char versionStatus[6] = {0};

	GetFullVersionString(versionActualStr,actualVersion);

	TRACE(TR_MOD_SERVICE, TR_SEV_ALL,"[%s][%s]", moduleName, versionActualStr);


	if (!IsVersionValidationEnabled())
	{
		return VER_SUCCESS;
	}
 
	if (actualVersion.build != expectedVersion.build)
	{
		GetVersionString(versionActualStr, actualVersion);
		GetVersionString(versionExpectedStr, expectedVersion);

		//OSAL_EventLogger_GenericLog(EVENTLOG_ERROR_TYPE, MSG_VERSION_ERROR, 4, moduleName, "Error", versionActualStr, versionExpectedStr);
		TRACE(TR_MOD_SERVICE, TR_SEV_ERR,"Version validation failed for %s.\nDetected version: %s\nExpected version: %ws", moduleName, versionActualStr, versionExpectedStr);
		//MyPrintf("Error: Version validation failed for %s.\nDetected version: %ws\nExpected version: %s", moduleName, versionActualStr, versionExpectedStr);

		return VER_FAIL_INVALID_MAJOR;
	}	

	if (actualVersion.revision != expectedVersion.revision)
	{
		GetVersionString(versionActualStr, actualVersion);
		GetVersionString(versionExpectedStr, expectedVersion);
		
		if (actualVersion.revision < expectedVersion.revision)
		{
			OSAL_sprintf_s( versionStatus, 6, "Older");			
		}
		else
		{
			OSAL_sprintf_s( versionStatus, 6, "Newer");
		}

		//OSAL_EventLogger_GenericLog(EVENTLOG_WARNING_TYPE, MSG_VERSION_ERROR, 4, moduleName, "Warning - work might still be possible", versionActualStr, versionExpectedStr);
		TRACE(TR_MOD_SERVICE, TR_SEV_WARNING,"Version validation failed for %s.\nDetected version: %s\nExpected version: %s", moduleName, versionActualStr, versionExpectedStr);
		//MyPrintf("Warning: %ws version of %s detected.\nDetected version: %s\nExpected version: %s", versionStatus, moduleName, versionActualStr, versionExpectedStr);

		return VER_SUCCESS_INVALID_MINOR;
	}

	return VER_SUCCESS;
}







