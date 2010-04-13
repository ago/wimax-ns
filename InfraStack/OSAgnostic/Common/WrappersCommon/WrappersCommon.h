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
#ifndef _WRAPPERS_COMMON_H
#define _WRAPPERS_COMMON_H

#include "CommonServices.h"
#include "wimax_osal_types.h"

#ifdef WMX_WRAPPER_EXPORTS
	#define WMX_WRAPPER_API __declspec(dllexport)
#elif defined WMX_WRAPPER_IMPORTS
	#define WMX_WRAPPER_API __declspec(dllimport)
#else 
	#define WMX_WRAPPER_API
#endif

#if defined(WMX_EXT_STD_CALL)
#define WMX_EXT_CALL_CONV __stdcall
#elif defined(WMX_EXT_CDECL_CALL)
#define WMX_EXT_CALL_CONV __cdecl
#else 
#define WMX_EXT_CALL_CONV
#endif

//#if defined(WMX_INT_STD_CALL)
//#define WMX_INT_CALL_CONV __stdcall
//#elif defined(WMX_INT_CDECL_CALL)
//#define WMX_INT_CALL_CONV __cdecl
//#else 
//#define WMX_INT_CALL_CONV
//#endif

#ifndef WMX_EXTERN_C
#ifdef __cplusplus
#define WMX_EXTERN_C extern "C"
#else
#define WMX_EXTERN_C
#endif 
#endif

#define VERSION_SDK_STR_MAX_SIZE 255
#define IP_ADDRESS_MAX_SIZE		 20
#define LAST_ERROR_MAX_SIZE		100

// Device Connection status
typedef enum _wmx_CtrlStatus_t
{
	NOT_READY = 0,
	READY,
	DRIVER_DISCONNECTED
	//	CardExtracted = 0x1,	// Card is Extracted from system
	//  CardInserted,			// Card is Inserted to system
} wmx_CtrlStatus_t, *wmx_pCtrlStatus_t;


/// <summary>
/// The signature defintion of a wmx_pCtrlStatusUpdateCB_t callback function. 
///
/// Once registered, This callback is invoked (if registered) when a SDK status update is warranted.
///
/// SDK status info includes the extraction/insertion status of the card, the status of the driver and the AppSrv service.
/// </summary>
///
/// <param name="ctrlStatus">(IN) A wmx_CtrlStatus_t enum specifying the current control status of the SDK.</param>
///
/// <returns>A wmx_Status_t value indicating the API call's success/error.</returns>
typedef void ( *wmx_pCtrlStatusUpdateCB_t)( wmx_CtrlStatus_t ctrlStatus);



EXPORT USHORT GetPortNum();

EXPORT LPCCH wmx_GetLastError();
EXPORT void wmx_ResetLastError();
EXPORT void wmx_SetLastError(char *str);


typedef enum _wmx_Status_t
{
	WMX_ST_OK	= 0x00,									// The operation had completed successfully

	// generic pipe errors
	WMX_ST_PIPE_FAILURE,								// The operation had failed due to failing of the Pipe 
	WMX_ST_PIPE_NOT_CONNETED,							// The operation had failed since the API was invoked before the application established a connection with the Pipe and device

	// generic device errors
	WMX_ST_DEVICE_FAILURE,								// The operation had failed due to a failure to interface with the device
	WMX_ST_DEVICE_NOT_FOUND,							// The operation had failed since the device is not plugged in
	WMX_ST_DEVICE_BUSY,									// The operation could not be completed because the device is currently busy
	WMX_ST_DEVICE_NOT_READY,

	// registration errors
	WMX_ST_CALLBACK_NOT_REGISTERED,						// The operation had failed since the callback was not registered
	WMX_ST_CALLBACK_ALREADY_REGISTERED,					// 
	WMX_ST_INDICATION_NOT_REGISTERED,					// The operation had failed since the indication was not registered
	WMX_ST_INDICATION_ALREADY_REGISTERED,				//
	WMX_ST_NO_ROOM_FOR_INDICATION,						// Indication will be lost because buffer is full.

	// generic operations errors
	WMX_ST_ILLEGAL_OPERATION,							// The operation is illegal
	WMX_ST_INVALID_OPCODE,								// The operation requested in unknown
	WMX_ST_DATA_UNAVAILABLE,							// For get operations - no available data at the moment
	WMX_ST_MODULE_NOT_INITIALIZED,						// The operation failed due to using of a module that is not initialized

	// config file was not found or is malformed
	WMX_ST_CONFIG_ERROR,

	// version error
	WMX_ST_VERSION_VALIDATION_ERROR,					// The operation had failed due to incompatible version
	WMX_ST_VERSION_VALIDATION_WARNING,					// The operation had succeeded, but the version is incompatible

	// specific errors
	WMX_ST_RESPONSE_BUFFER_TOO_SHORT,					// The operation failed because the response buffer is not large enough
	WMX_ST_NULL_APPSRV_IP_ADDRESS,						// The operation had failed since a NULL IP_ADDRESS was specified by the user when calling wmxSDK_Init()
	WMX_ST_TRACE_INIT_FAILED,							// The operation had failed due to a failure to initialize the Trace infrastructure in the iWmxSDK.dll
	WMX_ST_NULL_L5_DISPATCHER_FUNCTIONS_POINTER,		// The operation had failed since a NULL pointer for the L5 Dispatcher functions was specified by the user when calling wmxSDK_Init_Internal()
	WMX_ST_PIPE_HANDLER_LOAD_FAILED,						// The operation had failed due to a failure to load the PipeHandler.dll by the iWmxSDK.dll
	WMX_ST_L5_GET_DISPATCHER_FUNCTIONS_FAILED,			// The operation had failed due to a failure to retrieve a pointer to the L5 Dispatcher functions from the PipeHandler.dll
	WMX_ST_SPECIFIC_WRAPPER_SET_L5_FUNCTIONS_FAILED,	// The operation had failed due to a failure to set the L5 Dispatcher functions pointer to one of the wrappers
	WMX_ST_SPECIFIC_WRAPPER_SET_MSNGR_FUNCTIONS_FAILED,	// The operation had failed due to a failure to set the Messemger functions pointer to one of the wrappers
	WMX_ST_IWMXSDK_INTERNAL_FAILURE,					// The operation had failed due to an internal failure in the iWmxSDK.dll
	WMX_ST_BUFFER_TOO_SHORT,							// The operation failed because the buffer is not large enough
	WMX_ST_WRONG_ARGUMENT,								// The operation had failed due to a wrong argument

	WMX_ST_NSP_ID_NOT_FOUND,							// The NSP specified using the stated NSP_ID could not be found.
	WMX_ST_APDO_PATH_NOT_FOUND,						// The path specified in the API, pointing to a location in the APDO provisioning data storage database could not be found
	WMX_ST_DEVICE_NOT_PROVISIONED,				// The operation had failed because needed information is not provisioned to the device

	WMX_ST_WRONG_STATE,							// The operation has failed since the FSM is at the wrong state
	WMX_ST_NO_RF,								// The operation has failed since the control belong to other process(or instance)

	WMX_ST_ACCESSIBILITY_ERROR,
	// Unknown failure
	WMX_ST_FAIL

} wmx_Status_t;

char *wmxGetStatusStr(wmx_Status_t status);



#endif // _WRAPPERS_COMMON_H