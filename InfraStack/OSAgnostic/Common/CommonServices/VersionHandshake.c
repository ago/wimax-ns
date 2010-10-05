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
// Project
#include <unistd.h>
#include <stdlib.h>
#include "PipeHandlerInternal.h"
#include "VersionUtils.h"
#include "L5OpCodes.h"	

#include "TraceModule.h"

#ifdef WINCE
#include "../../Common/CEHeader.h"
#endif

#define TIMEOUT 10000
#define MAX_STR_SIZE 32

// send the version of the PipeHandler to AppSrv to verify
// that AppSrv is willing to work with it.
VERSION_RESULT PIPE_HANDLER_ValidateOwnVersion(L5_CONNECTION l5ConnID)
{
	L5_RESULT l5Result;	
	wmx_VersionEntry_t versionEntry;
	VERSION_RESULT validationResult;
	void *responseBuffer = NULL;
	UINT32 responseSize;
	UINT32 responseID; 

	// if version validation is disabled - "validation" always succeeds
	if (!IsVersionValidationEnabled())
	{
		return VER_SUCCESS;
	}

	validationResult = VER_FAIL_MODULE_ID_NOT_FOUND;
	SET_VERSION(versionEntry.version, PIPE_HANDLER_MAJOR, PIPE_HANDLER_MINOR, PIPE_HANDLER_BUILD, PIPE_HANDLER_REVISION, PIPE_HANDLER_BRANCH);
	
	responseSize = sizeof(VERSION_RESULT);
	responseBuffer = malloc(responseSize);

	l5Result = PIPE_HANDLER_SendReceiveL5(	l5ConnID, 
												L5_TARGET_ACT, 
												ACT_OPCODE_VALIDATE_VERSION, 
												(void *)&versionEntry, 
												sizeof(versionEntry), 
												&responseID, 
												responseBuffer, 
												&responseSize );	

	// If the l5 result was OK then check the version validation result in the response message
	if (l5Result == L5_RESULT_OK)
	{		
		validationResult = *((VERSION_RESULT*)responseBuffer);		
	}	
	free(responseBuffer);

	switch (validationResult)
	{
		case VER_SUCCESS:
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_INFO, "ConnGateKeeper - version validation succeeded");
			break;
		case VER_SUCCESS_INVALID_MINOR:
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_WARNING, "ConnGateKeeper - version validation succeeded, but minor version is incompatible");
			break;
		default:
			TRACE(TR_MOD_L5_CONNECTOR, TR_SEV_ERR, "ConnGateKeeper - version validation failed. ErrorCode: %d", validationResult);
			break;
	}	

	return validationResult;
}
