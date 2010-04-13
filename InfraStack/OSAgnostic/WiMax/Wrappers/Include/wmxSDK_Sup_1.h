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
#ifndef _WMX_SDK_SUP_1_H
#define _WMX_SDK_SUP_1_H


#include "CommonServices.h"
#include "WrappersCommon.h"
#include "wmxSDK_Nds_Cmn.h"


/// <summary>
/// Type definition for a variable containing the length of an EAP message. 
/// </summary>
typedef size_t	wmx_EapMsgLength_t,	*wmx_pEapMsgLength_t;

wmx_Status_t NDnSAgent_SetConfigToSupplicant( wmx_NSPid_t nspID );
/// <summary>
/// Type definition for a buffer containing an EAP message. 
/// </summary>
typedef char	*wmx_pEapMessage_t;

void L4C_CallHandleRobustConnect(BOOL isL3Trigger);
/// <summary>
/// Type definition for a variable containing the length of an EAP key. 
/// </summary>
typedef size_t	wmx_EapKeyLength_t,	*wmx_pEapKeyLength_t;


/// <summary>
/// Type definition for a buffer containing an EAP key. 
/// </summary>
typedef char	*wmx_pEapKey_t;


/// <summary>
/// The signature defintion of a wmx_pEapRequestAvailableCB_t callback function. 
///
/// Once registered, this callback function will be called when the driver indicates that an EAP message is available for the Supplicant.
/// </summary>
///
/// <param name="eapMsgLen">(IN) The length of the EAP message that had arrived.</param>
/// <param name="pEapMsg">(IN) A pointer to a buffer containing the EAP message for the Supplicant.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pEapRequestAvailableCB_t)( wmx_EapMsgLength_t eapMsgLen, wmx_pEapMessage_t pEapMsg );


/// <summary>
/// The signature defintion of a wmx_pAlternativeEapSuccessCB_t callback function. 
///
/// Once registered, this callback function will be called when the driver indicates that it managed to 
/// validate the key without receiving an EAP success from the supplicant.
///
/// This event may occur if the last EAP message to the Supplicant (informing of the successful 
/// completion of the EAP negotiation) was lost.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pAlternativeEapSuccessCB_t)();


/// <summary>
/// The signature defintion of a wmx_pEapKeyRequestCB_t callback function. 
///
/// Once registered, this callback function will be called when the driver figures out that it should 
/// have received a master key from the Supplicant but did not receive it.
///
/// This request should trigger a transfer of a key from the Supplicant.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pEapKeyRequestCB_t)();

typedef void (WMX_EXT_CALL_CONV *wmx_pEapRestartRequestCB_t)();


/// <summary>
/// This API sends an EAP response message to the AAA server through the driver. 
/// </summary>
///
/// <param name="eapMsgLen">(IN) The length of the EAP message being sent.</param>
/// <param name="pEapMsg">(IN) A pointer to a buffer containing the EAP message that should be sent.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_CmdSendEapResponse( wmx_EapMsgLength_t eapMsgLen, wmx_pEapMessage_t pEapMsg );


/// <summary>
/// This API sends an EAP success indication to the driver, informing it that the EAP negotiation had
/// completed successfully and that a key is available for further operation.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_SetEapSuccess();


/// <summary>
/// This API sends an EAP fail indication to the driver, informing it that the EAP negotiation 
/// had completed unsuccessfully and no further operation can be performed
/// (other than another EAP negotiation attempt).
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_SetEapFail();


/// <summary>
/// This API sets the EAP master key that was created with the AAA server to the driver.
/// </summary>
///
/// <param name="eapKeyLen">(IN) The length of the EAP key in bytes.</param>
/// <param name="pEapKey">(IN) A pointer to a buffer containing the EAP key.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_SetEapKey( wmx_EapKeyLength_t eapKeyLen, wmx_pEapKey_t pEapKey );


wmx_Status_t wmx_ResetSupplicant();

/// <summary>
/// The registration API for a wmx_pEapRequestAvailableCB_t callback function.
/// </summary>
///
/// <param name="pEapRequestAvailableCB">(IN) A pointer to the application function to be called when an EAP message is available for the Supplicant.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterEapRequestAvailableCB(wmx_pEapRequestAvailableCB_t pEapRequestAvailableCB);


/// <summary>
/// The de-registration API for a wmx_pEapRequestAvailableCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterEapRequestAvailableCB();


/// <summary>
/// The registration API for a wmx_pAlternativeEapSuccessCB_t callback function.
/// </summary>
///
/// <param name="pAlternativeEapSuccessCB">(IN) A pointer to the application function to be called when the driver manages to validate the key without receiving an EAP success from the supplicant.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterAlternativeEapSuccessCB(wmx_pAlternativeEapSuccessCB_t pAlternativeEapSuccessCB);


/// <summary>
/// The de-registration API for a wmx_pAlternativeEapSuccessCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterAlternativeEapSuccessCB();


/// <summary>
/// The registration API for a wmx_pEapRequestAvailableCB_t callback function.
/// </summary>
///
/// <param name="pEapRequestAvailableCB">(IN) A pointer to the application function to be called when the driver figures out that it should have received a master key from the Supplicant but did not receive it.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_RegisterEapKeyRequestCB(wmx_pEapKeyRequestCB_t pEapKeyRequestCB);


/// <summary>
/// The de-registration API for a wmx_pEapKeyRequestCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t wmx_UnregisterEapKeyRequestCB();

wmx_Status_t wmx_RegisterEapRestartRequestCB(wmx_pEapRestartRequestCB_t pEapRestartRequestCB);
wmx_Status_t wmx_UnregisterEapRestartRequestCB();


void *wmx_GetTlsFunctionTable(int param);

#endif // _WMX_SDK_SUP_1_H
