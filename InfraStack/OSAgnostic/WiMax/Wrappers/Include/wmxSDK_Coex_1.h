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
#ifndef _WMX_SDK_COEX_H
#define _WMX_SDK_COEX_H

#include "WrappersCommon.h"
#include "wmxSDK_Nds_Cmn.h"

/// <summary>
/// Type definition for an enum specifying the possible coexistence priorities which can be set to the device as part of a scan and connect commands.
/// </summary>
typedef enum _wmx_CoexPriority_t
{
	COEX_PRIORITY_SCAN_LOW = 0x01,
	COEX_PRIORITY_SCAN_HIGH,
	COEX_PRIORITY_CONNECT_LOW,
	COEX_PRIORITY_CONNECT_HIGH
} wmx_CoexPriority_t, *wmx_pCoexPriority_t;

/// <summary>
/// Type definition for an enum specifying the possible coexisting modes which can be set to the device.
/// </summary>
typedef enum _wmx_CoexistenceMode_t
{
	WMX_MODE_XOR,
	WMX_MODE_CM
} wmx_CoexistenceMode_t, *wmx_pCoexistenceMode_t;

/// <summary>
/// Type definition for an enum specifying the possible coexistence priorities which can be set to the device as part of a scan and connect commands.
/// </summary>
typedef enum _wmx_CoexState_t
{
	COEX_STATE_SCAN_LOW = 0x01,
	COEX_STATE_SCAN_HIGH,
	COEX_STATE_CONNECTING
} wmx_CoexState_t, *wmx_pCoexState_t;


/// <summary>
/// The signature defintion of a wmx_pCoexUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called upon coexistence mode changes.
/// </summary>
///
/// <param name="coexMode">(IN) A wmx_CoexistenceMode_t enum providing the status of the coexistence mode.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pCoexUpdateCB_t)( wmx_CoexistenceMode_t coexMode);

// <summary>
// This API allows the user to set the coexistance mode of the device.
// </summary>
//
// <param name="coexMode">(IN) An enum indicating the desired coexistance mode.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetCoexistenceMode(wmx_CoexistenceMode_t coexMode);

// <summary>
// This API allows to set the coexistence state of the device for an overall process.
// </summary>
//
// <param name="coexMode">(IN) An enum indicating the desired coexistance state.</param>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdProcessStart(wmx_CoexState_t coexState);

// <summary>
// This API allows to release the coexistence state lock.
// </summary>
//
// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_CmdProcessEnd(void);

#endif // _WMX_SDK_COEX_H