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
#ifndef _WMX_SDK_SUP_4_H
#define _WMX_SDK_SUP_4_H


#include "CommonServices.h"
#include "WrappersCommon.h"


/// <summary>
/// Type definition for a variable containing an event type (missing cred. request or error event)
/// </summary>
typedef UINT32 wmx_EventType_t, *wmx_pEventType_t;

/// <summary>
/// Type definition for a variable containing a credential id.
/// </summary>
typedef UINT32 wmx_CredID_t, *wmx_pCredID_t;

/// <summary>
/// Type definition for a struct containing information of a supplicant event
/// </summary>
typedef struct _wmx_SupEvent_t
{
	wmx_EventType_t		eventType;
	wmx_CredID_t		credId;	
} wmx_SupEvent_t, *wmx_pSupEvent_t;

/// <summary>
/// Type definition for a variable containing the identity of the user
/// (formatted as NAI - Network Access Identifier - name@domain)
/// required for authentication during EAP exchange.
/// </summary>
typedef char	*wmx_pNAI_t;

/// <summary>
/// Type definition for a variable containing the password of the user
/// required for authentication during EAP exchange.
/// </summary>
typedef char	*wmx_pUserPassword_t;

/// <summary>
/// Type definition for a variable containing the eap method.
/// </summary>
typedef UINT32 wmx_EapMathod_t, *wmx_pEapMethod_t;

/// <summary>
/// Type definition for a variable containing the Inner/Phase2 method.
/// </summary>
typedef UINT32 wmx_Phase2Mathod_t, *wmx_pPhase2Method_t;

/// <summary>
/// Type definition for a variable containing a certificate
/// required for authentication during EAP exchange.
/// </summary>
typedef unsigned char *wmx_pCertificatePath_t;

/// <summary>
/// Type definition for a variable containing a SIM pin code
/// required for authentication during EAP-AKA exchange.
/// </summary>
typedef char	*wmx_pPin_t;

/// <summary>
/// Type definition for a variable containing the max. size of TLS messages to send.
/// </summary>
typedef UINT32 wmx_TlsMaxSize_t, *wmx_pTlsMaxSize_t;

/// <summary>
/// A constant specifying the max length of TLS messages.
/// </summary>
#define WMX_TLS_MAX_SIZE 1398

// callbacks
typedef void (WMX_EXT_CALL_CONV *wmx_pEventReportCB_t)( wmx_SupEvent_t event );

// apis
wmx_Status_t wmx_SetIdentity( wmx_pNAI_t identity );

wmx_Status_t wmx_SetAnonymousIdentity( wmx_pNAI_t identity );

wmx_Status_t wmx_SetPassword( wmx_pUserPassword_t password );

// not implemented in this version
//wmx_Status_t wmx_SetNewPassword( wmx_pUserPassword_t password );

wmx_Status_t wmx_SetEapMethod( wmx_EapMathod_t eapMethod );

wmx_Status_t wmx_SetPhase2Method( wmx_Phase2Mathod_t phase2Method );

// TLS handshake
wmx_Status_t wmx_SetTlsCaCert( wmx_pCertificatePath_t path );

// TLS handshake inside of a tunnel
wmx_Status_t wmx_SetTlsCaCert2( wmx_pCertificatePath_t path );

// TLS handshake
wmx_Status_t wmx_SetTlsClientCert( wmx_pCertificatePath_t path );

// TLS handshake inside of a tunnel
wmx_Status_t wmx_SetTlsClientCert2( wmx_pCertificatePath_t path );

// TLS handshake
wmx_Status_t wmx_SetTlsPrivateKey( wmx_pCertificatePath_t path );

// TLS handshake inside of a tunnel
wmx_Status_t wmx_SetTlsPrivateKey2( wmx_pCertificatePath_t path );

// not implemented in this version
//wmx_Status_t wmx_SetTlsPrivateKeyPasswd( wmx_pUserPassword_t path );

// not implemented in this version
//wmx_Status_t wmx_SetTlsPrivateKeyPasswd2( wmx_pUserPassword_t path );

wmx_Status_t wmx_SetPin( wmx_pPin_t pin );

wmx_Status_t wmx_SetTlsMaxSize( wmx_TlsMaxSize_t len );

wmx_Status_t wmx_EnableSupplicant( BOOL enable);

// This callback is invoked (if registered) when the Supplicant
// has a missing credential required for EAP exchange.
wmx_Status_t wmx_RegisterEventReportCB(wmx_pEventReportCB_t pEventReportCB);
wmx_Status_t wmx_UnregisterEventReportCB();


// This callback is invoked before the supplicant is being re-configured within NDnSAgent_SetConfigToSupplicant actions.
// Erase/Free previous credentials that might have been set in the config context before.
// Restart the supplicant with empty context to be assigned later on.
wmx_Status_t wmx_ResetSupplicant();

#endif // _WMX_SDK_SUP_4_H