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
#include "wmxSDK_Apdo_Internals.h"


//////////////////////////////////////////////////////////////////////
// L5 Layer
// Callbacks
wmx_pApdoLinkStatusCB_t ApdoLinkStatusCB;
wmx_pApdoAlertResponseCB_t ApdoAlertResponseCB;
//wmx_pApdoOobNotificationCB_t ApdoOobNotificationCB;
wmx_pRefreshApdoSessionStatusCB_t RefreshApdoSessionStatusCB;
wmx_pApdoFumoDownloadApprovalStatusCB_t ApdoFumoDownloadApprovalStatusCB;
wmx_pApdoDeleteDMAccountCB_t ApdoDeleteDMAccountCB;

//************************************************
// Connection Parameters to L5 Layer
//************************************************
LONG apdo_numOfInits = 0;
L5_CONNECTION apdo_wrapper_l5ConnID;
tL5DispatcherFunctions *apdo_wrapper_pFuncs;
tUtilityFunctions *apdo_wrapper_UtilFuncs;

/// Internal Parameters
LONG g_numOfApdoLinkStatusIndRegs = 0;
LONG g_numOfApdoSessionStatusIndRegs = 0;
LONG g_numOfApdoOobNotificationIndRegs = 0;
LONG g_numOfApdoAlertResponseIndRegs = 0;
LONG g_numOfApdoFumoDownloadApprovalStatusIndRegs = 0;
LONG g_numOfApdoDeleteDMAccountIndRegs = 0;
