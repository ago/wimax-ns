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
#ifndef _WMX_SDK_APDO_IND_HANDLER_H
#define _WMX_SDK_APDO_IND_HANDLER_H

#include "WrappersCommon.h"

wmx_Status_t wmxApdo_LinkStatusArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxApdo_AlertResponseArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxApdo_OobNotificationArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxApdo_RefreshApdoSessionStatusArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxApdo_FumoDownloadApprovalStatusArrived( UINT8 *buf, UINT32 bufSize );

wmx_Status_t wmxApdo_DeleteDMAccountArrived( UINT8 *buf, UINT32 bufSize );

void wmxNds_CBsCaller( UINT32 internalRequestID, void *buffer, UINT32 bufferLength );

#endif //_WMX_SDK_APDO_IND_HANDLER_H