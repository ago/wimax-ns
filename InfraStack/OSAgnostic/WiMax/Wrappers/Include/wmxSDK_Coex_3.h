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
#include "WrappersCommon.h"
#include "wmxSDK_Coex_1.h"		
#include "wmxSDK_Nds_Cmn.h"
#include "wmxSDK_Nds_Internals.h"

/// <summary>
/// The registration API for a wmx_pCoexUpdateCB_t callback function.
/// </summary>
///
/// <param name="coexModeCB">(IN) A pointer to the application function to be called upon coexistence mode changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterCoexUpdateCB( wmx_pCoexUpdateCB_t coexModeCB );


/// <summary>
/// The de-registration API for a wmx_pCoexUpdateCB_t callback function.
/// </summary>
///
/// <param name="coexModeCB">(IN) A pointer to the application function to be called upon coexistence mode changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterCoexUpdateCB();


// <summary>
// This API allows the user to set the coexistance mode of the device.
// </summary>
//
// <param name="coexMode">(IN) An enum indicating the desired coexistance mode.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetCoexistenceMode(wmx_CoexistenceMode_t coexMode);

// <summary>
// This API allows the user to set the coexistance mode of the device.
// </summary>
//
// <param name="coexMode">(OUT) An enum indicating the desired coexistance mode.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetCoexistenceMode(wmx_pCoexistenceMode_t coexMode);
