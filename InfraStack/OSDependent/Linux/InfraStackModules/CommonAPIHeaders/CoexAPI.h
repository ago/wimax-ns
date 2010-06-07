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
#ifndef _WMX_WIMAX_API_COEX_EXTENSIONS_H
#define _WMX_WIMAX_API_COEX_EXTENSIONS_H


/// <summary>
/// Type definition for an enum specifying the possible coexistence modes which can be set to the device.
/// </summary>
typedef enum _WIMAX_API_COEXISTENCE_MODE
{
	MODE_XOR,
	MODE_CM
} WIMAX_API_COEXISTENCE_MODE, *WIMAX_API_COEXISTENCE_MODE_P;

/// <summary>
/// Type definition for an enum specifying the possible device's association modes.
/// </summary>
typedef enum _WIMAX_API_ASSOCIATION_STATUS
{
	WIMAX_API_DEVICE_ASSOCIATED,
	WIMAX_API_DEVICE_NOT_ASSOCIATED
} WIMAX_API_ASSOCIATION_STATUS, *WIMAX_API_ASSOCIATION_STATUS_P;

/// <summary>
/// The signature defintion of a IndCoexistenceModeUpdate callback function. 
///
/// Once registered, this callback function will be called upon coexistence mode changes.
/// </summary>
///
/// <param name="coexMode">(IN) A WIMAX_API_COEXISTENCE_MODE enum providing the status of the coexistence mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (*IndCoexistenceModeUpdate)( WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_COEXISTENCE_MODE coexMode);

/// <summary>
/// The registration API for a IndCoexistenceModeUpdate callback function.
/// </summary>
///
/// <param name="coexModeCB">(IN) A pointer to the application function to be called upon coexistence mode changes.</param>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SubscribeCoexistenceModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId, IndCoexistenceModeUpdate pCallbackFnc );

/// <summary>
/// The de-registration API for a IndCoexistenceModeUpdate callback function.
/// </summary>
///
/// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>

WIMAX_API_RET WIMAX_API UnsubscribeCoexistenceModeUpdate(WIMAX_API_DEVICE_ID_P pDeviceId);


// <summary>
// This API allows the user to set the coexistence mode of the device.
// </summary>
//
// <param name="coexMode">(IN) An enum indicating the desired coexistance mode.</param>
//
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API SetCoexistenceMode(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_COEXISTENCE_MODE coexMode);

// <summary>
// This API allows the user to get the coexistence mode of the device.
// </summary>
//
// <param name="coexMode">(OUT) A pointer to a user allocated enum in which the device will indicate the currently set coexistence mode.</param>
//
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API GetCoexistenceMode(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_COEXISTENCE_MODE_P pCoexMode);

// <summary>
// This API allows the user to check if the device is associated with a network (i.e. the link is up).
// </summary>
//
// <param name="pAssociated">(OUT) A pointer to a user allocated enum in which the device will indicate its association state.</param>
//
// <returns>A WIMAX_API_RET value indicating the API call's success/error.</returns>
WIMAX_API_RET WIMAX_API IsAssociated(WIMAX_API_DEVICE_ID_P pDeviceId, WIMAX_API_ASSOCIATION_STATUS_P pAssociated);

#endif // _WMX_WIMAX_API_COEX_EXTENSIONS_H