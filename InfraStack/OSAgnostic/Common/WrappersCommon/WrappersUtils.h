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
#ifndef _WRAPPERS_UTILS_H
#define _WRAPPERS_UTILS_H


#include "WrappersCommon.h"
#include "L5Common.h"

#include "L3L4TlvTypes.h"
#include "L3L4CommonDefines.h"

#include "L4BufMan_L4Common_Desc.h"
#include "L4BufMan_L4Common.h"

#include "L4BufMan_L3L4Structs_Desc.h"
#include "L4BufMan_L3L4Structs.h"


#define FIRST_REGISTERED	1
#define LAST_REGISTERED		0


EXPORT WMX_EXTERN_C wmx_Status_t wmx_L5ResultToWMXStatus( L5_RESULT l5Result );
EXPORT WMX_EXTERN_C wmx_Status_t wmx_L4ResultToWMXStatus( E_L3L4ResponseStatus l3l4ResponseStatus );


EXPORT WMX_EXTERN_C wmx_Status_t wmx_SendL4Command( 
	GENERIC_STRCT strct, 
	L4bufman_Funcs l4bufman_funcs, 
	tL5DispatcherFunctions dispatcher_funcs,
	L5_CONNECTION conn,
	wmx_Status_t *receivedSt );

EXPORT WMX_EXTERN_C wmx_Status_t wmx_ParseL4Buffer( 
	UINT8* buffer,
	GENERIC_STRCT pStrct, 
	L4bufman_Funcs l4bufman_funcs, 
	wmx_Status_t *receivedSt );

EXPORT WMX_EXTERN_C wmx_Status_t wmx_SendL5Command( 
	L5_TARGET_ID target, UINT32 msgID, 
	tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn,
	UINT8* request, UINT32 requestLength, 
	UINT8* response, UINT32* responseLength );

EXPORT WMX_EXTERN_C wmx_Status_t wmx_RegisterOnAgentIndication( 
	LONG *cnt, 
	L5_TARGET_ID target, UINT32 msgID, UINT32 ind,
	tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn );

EXPORT WMX_EXTERN_C wmx_Status_t wmx_UnregisterOnAgentIndication( 
	LONG *cnt, 
	L5_TARGET_ID target, UINT32 msgID, UINT32 ind,
	tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn );

EXPORT WMX_EXTERN_C wmx_Status_t wmx_RegisterOnDriverReport( 
	LONG *cnt, UINT32 ind,
	tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn );

EXPORT WMX_EXTERN_C wmx_Status_t wmx_UnregisterOnDriverReport( 
	LONG *cnt, UINT32 ind,
	tL5DispatcherFunctions dispatcher_funcs, L5_CONNECTION conn );



#endif // _WRAPPERS_UTILS_H