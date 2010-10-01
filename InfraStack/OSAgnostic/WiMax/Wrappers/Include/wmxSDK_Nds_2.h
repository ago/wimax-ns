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
#ifndef _WMX_SDK_NDS_2_H
#define _WMX_SDK_NDS_2_H


#include "wmxSDK_Nds_Cmn.h"

#include "CommonServices.h"
#include "WrappersCommon.h"

/// <summary>
/// Type definition for an enum specifying the possible connection states of the device.
///
/// Values: (see WiMAX SDK API documentation)
/// RfOff
///	Disconnected
///	OutOfZone
///	Connected
/// </summary>
typedef enum _wmx_ConnectionState_t
{
	ConnectionStateRfOff,
	Disconnected,
	OutOfZone,
	Connected,
	UnknownConnectionState
}wmx_ConnectionState_t, *wmx_pConnectionState_t;

static inline
const char * ConnectionStateName(unsigned index)
{
	static const char *strs[] = {
		"ConnectionStateRfOff",
		"Disconnected",
		"OutOfZone",
		"Connected",
		"UnknownConnectionState"
	};
	static const unsigned index_max = sizeof(strs) / sizeof(strs[0]);
	return index < index_max? strs[index] : "Illegal";
};
/// <summary>
/// The signature defintion of a wmx_pConnectionStateUpdateCB_t callback function. 
///
/// Once registered, this callback function will be called whenever the connection state of the device changes.
/// </summary>
///
/// <param name="connectionState">(IN) A wmx_ConnectionState_t enum specifying the connection state.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void (WMX_EXT_CALL_CONV *wmx_pConnectionStateUpdateCB_t)( wmx_ConnectionState_t connectionState);


/// This API returns the WiMAX system state which the device is currently in.
/// </summary>
///
/// <param name="systemState">(OUT) A pointer to a user-allocated wmx_SystemState_t enum in which the API will place the WiMAX system state.</param>
/// <param name="connectProgressInfo">
/// (OUT) A pointer to a user-allocated wmx_ConnectProgressInfo_t enum giving further information on the progress of a connection attempt.
///		
///	This parameter is only relevant if the systemState reported is Connecting. Otherwise its value will 
/// be Not_Applicable.
///	
/// The enum may contain one of the following values: Ranging, SBC, EAP authentication, 3-way-handshake, Registration. 
/// </param>
///
/// <param name="rfSwitchesStatus">
/// (OUT) A pointer to wmx_RfSwitchesStatus_t struct giving the status (On, Off) of the HW & SW RF switches.
///	This parameter is only relevant if the systemState reported is RF-Off. In the other states 
/// (Ready, Scan, Data-Connected, �) both RF switches must be on.
/// </param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetSystemState(	wmx_pSystemState_t systemState,
																	wmx_pConnectProgressInfo_t connectProgressInfo,
																	wmx_pRfSwitchesStatus_t rfSwitchesStatus );



/// <summary>
/// This API allows the user to obtain the status of the RF function of the WiMAX device.
/// </summary>
///
/// <param name="pRfStatus">(OUT) A pointer to a user-allocated wmx_pRfStatus_t enum in which the API will specify the RF status.</param>
/// <param name="pRfSwitchesStatus">(OUT) A pointer to a user-allocated wmx_pRfSwitchesStatus_t struct giving the status (On, Off) of the HW & SW RF switches.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetRfStatus(	wmx_pRfStatus_t pRfStatus, wmx_pRfSwitchesStatus_t pRfSwitchesStatus	) ;


/// <summary>
/// This API returns information that details whether the link is up or down.
/// </summary>
///
/// <param name="pMediaStatus">(OUT) A pointer to a user-allocated wmx_MediaStatus_t struct indicating if the link is up or down.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetMediaStatus( wmx_pMediaStatus_t pMediaStatus	);

/// <summary>
/// This API returns the connection state of the device.
/// </summary>
///
/// <param name="connectionState">(OUT) A pointer to a user-allocated wmx_ConnectionState_t enum in which the API will place the connection state.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetConnectionState( wmx_pConnectionState_t connectionState );


/// <summary>
/// The registration API for a wmx_pConnectionStateUpdateCB_t callback function.
/// </summary>
///
/// <param name="connectionStateUpdateCB">(IN) A pointer to the application function to be called when the connection state changes.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_RegisterConnectionStateUpdateCB( wmx_pConnectionStateUpdateCB_t connectionStateUpdateCB );


/// <summary>
/// The de-registration API for a wmx_pConnectionStateUpdateCB_t callback function.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_UnregisterConnectionStateUpdateCB();

#endif // _WMX_SDK_NDS_2_Hchar
