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
#ifndef _I_WMX_SDK_H
#define _I_WMX_SDK_H


#include "VersionUtils.h"
#include "WrappersCommon.h"

#include "WiMaxAPI.h"

#define VERSION_MAX_LEN		100
#define WRAPPER_NAME_LEN	30
#define WRAPPER_NAME		"iWmxSDK"

/// <summary>
/// This API initializes the iWmxSDK wrappers DLL.
///
/// A call to this API should preceed calls to specific wrappers' wmxXXX_Init() API.
/// This API should be called only once for all threads of a user application.
/// If the user wishes to "reset" the wrappers DLL he should call the wmxSDK_Finalize() API before calling wmxSDK_Init() again.
/// </summary>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_Init();


/// <summary>
/// This API finalizes the iWmxSDK wrappers DLL.
///
/// A call to this API should be preceeded with calls to the wmxXXX_Finalize() API of all specific wrappers used.
/// </summary>
void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_Finalize();


/// <summary>
/// This API allows the user to obtain the version of the WiMAX SDK.
/// </summary>
///
/// <param name="version">(OUT) A pointer to a user-allocated wmx_pVersion_t struct in which the API will fill the WiMAX SDK's version.</param>
/// <param name="versionStr">(OUT) A pointer to a user-allocated wmx_pVersionStr_t string in which the API will fill the WiMAX SDK's version. VERSION_SDK_STR_MAX_SIZE can be used.</param>
/// <param name="versionStr">(IN) The size of the user-allocated string.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_GetVersion( wmx_pVersion_t version, wmx_pVersionStr_t versionStr, wmx_VersionStrLen_t *verMaxLen ) ;


/// <summary>
/// This API allows the user to register a callback for SDK control status updates.
/// </summary>
///
/// <param name="ctrlStatusUpdateCB">(IN) A pointer to the application function to be called upon SDK control status change.</param>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_RegisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB);


/// <summary>
/// This API allows the user to de-register for SDK control status updates.
/// </summary>
///
/// <param name="ctrlStatusUpdateCB">(IN) A pointer to the application function to be called upon SDK control status change.</param>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_UnregisterCtrlStatusUpdatesCB(wmx_pCtrlStatusUpdateCB_t ctrlStatusUpdateCB);


/// <summary>
/// This API allows the user to obtain the status of the WiMAX SDK.
///
/// SDK status info includes the extraction/insertion status of the card, the status of the driver and the AppSrv service.
/// </summary>
///
/// <returns>A wmx_CtrlStatus_t value indicating the control status of the SDK.</returns>
wmx_CtrlStatus_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_GetCtrlStatus();


/// <summary>
/// This API allows the user to set the IP address and port number of AppSrv.
/// 
/// The SDK first looks for IP address and port number settings in the Registry under 
/// [HKEY_LOCAL_MACHINE\SOFTWARE\PipeConfig\SdkIpAddress & SdkPortNum].
///
/// The application can override the Registry settings using this API.
///
/// If the application already initialized the SDK and it is already connected to the AppSrv service,
/// then calling this API will only have effect after the SDK was finalized and re-initialized.
/// </summary>
///
/// <param name="szHostName">(IN) A string containing the IP address or host name of AppSrv.</param>
/// <param name="nPort">(IN) The port number of AppSrv (a decimal value).</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxSDK_SetConnParams(char *szHostName, int nPort);

WIMAX_API_RET WIMAX_API DetachFromSDK();

#endif // _I_WMX_SDK_H
