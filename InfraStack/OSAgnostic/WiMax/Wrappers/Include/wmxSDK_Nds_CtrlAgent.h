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
#ifndef _WMX_SDK_NDS_CTRL_AGENT_H
#define _WMX_SDK_NDS_CTRL_AGENT_H


#include "CommonServices.h"
#include "WrappersCommon.h"


/// <summary>
/// This API initializes the ND&S wrapper.
///
/// A call to this API should be preceded with a successful call to the iWmxSDK DLL's wmxSDK_Init() API.
/// This API should be called only once for all threads of a user application.
/// If the user wishes to "reset" the wrapper he should call the wmxNds_Finalize() API before calling wmxNds_Init() again.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmxNds_InitAgent();


/// <summary>
/// This API finalizes the ND&S wrapper.
///
/// If the user wishes to finish working with the iWmxSDK DLL altogether, then a call to this API
/// should be followed with a call to the iWmxSDK DLL's wmxSDK_Finalize() API.
/// </summary>
void wmxNds_FinalizeAgent();


#endif // _WMX_SDK_NDS_CTRL_AGENT_H