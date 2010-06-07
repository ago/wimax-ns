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
#ifndef _WMX_SDK_APDO_UTILS_H
#define _WMX_SDK_APDO_UTILS_H

#include "wmxSDK_Apdo_Cmn.h"
#include "L5OpCodes.h"

#define SERVER_SECRET_PATH "AppAuth/1/AAuthSecret"
#define OFFSET 10
#define END_OF_STR "00"

// The function concatenates the parameters given to the resultBuffer,
// assumes that resultBuffer is allocated by the user of the function
void wmxApdo_CreateApdoBufferWithValue( wmx_APDOType_t APDOType, wmx_APDOPath_t remotePath, char *APDOValue, char *resultBuffer );

// The function concatenates the parameters given to the resultBuffer,
// assumes that resultBuffer is allocated by the user of the function
void wmxApdo_CreateAPDOBuffer( wmx_APDOType_t APDOType, wmx_APDOPath_t remotePath, char *resultBuffer );
//void wmxApdo_ParseAPDOBuffer(char *inputBuffer, char **pAPDOPath, char **pValue, wmx_pAPDOType_t pAPDOType);
//void wmxApdo_ParseAPDOBufferNoValue(char *inputBuffer, char **pAPDOPath, wmx_pAPDOType_t pAPDOType);

// Parse the input buffer and fill pAPDOPath, pValue and pAPDOType.
// The function doesn't copy the data, just points to the right location in the inputBuffer.
void wmxApdo_ParseAPDOBuffer(char *inputBuffer, wmx_pAPDOPath_t pAPDOPath, char **pValue, wmx_pAPDOType_t pAPDOType);

// Parse the input buffer and fill pAPDOPath and pAPDOType.
// The function doesn't copy the data, just points to the right location in the inputBuffer.
void wmxApdo_ParseAPDOBufferNoValue(char *inputBuffer, wmx_pAPDOPath_t pAPDOPath, wmx_pAPDOType_t pAPDOType);


// Gets a null terminated buffer and translate it to the corresponding Enum value
void wmxApdo_TranslateStringAPDOTypeToEnum(char *strAPDOType, wmx_pAPDOType_t pAPDOType);

// Returns the size of a buffer according to the type of the data
int wmxApdo_GetBufferLength(void *value, wmx_APDOType_t apdoType);

/////////
wmx_Status_t wmxApdo_RegisterOnApdoLinkStatusInd();
wmx_Status_t wmxApdo_RegisterOnApdoAlertResponseInd();
wmx_Status_t wmxApdo_RegisterOnApdoSessionStatusInd();
wmx_Status_t wmxApdo_RegisterOnApdoOobNotificationInd();
wmx_Status_t wmxApdo_RegisterOnApdoFumoDownloadApprovalStatusInd();
wmx_Status_t wmxApdo_RegisterOnApdoDeleteDMAccountInd();

wmx_Status_t wmxApdo_UnregisterOnApdoLinkStatusInd();
wmx_Status_t wmxApdo_UnregisterOnApdoAlertResponseInd();
wmx_Status_t wmxApdo_UnregisterOnApdoSessionStatusInd();
wmx_Status_t wmxApdo_UnregisterOnApdoOobNotificationInd();
wmx_Status_t wmxApdo_UnregisterOnApdoFumoDownloadApprovalStatusInd();
wmx_Status_t wmxApdo_UnregisterOnApdoDeleteDMAccountInd();
wmx_Status_t wmx_GetApdoOperatorsConfigurations(wmx_pApdoOperatorConfigurations_t pConfigurations);

#endif  // _WMX_SDK_APDO_UTILS_H