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
#ifndef _WIMAX_ERROR_H
#define _WIMAX_ERROR_H

/// Errors codes returned by the APIs.
/// \note Insert new error codes between WIMAX_API_RET_FIRST_COMMON_ERROR and WIMAX_API_RET_LAST_COMMON_ERROR for common error code
typedef enum _WIMAX_API_RET
{
	WIMAX_API_RET_FIRST_COMMON_ERROR = 0,
	/// No errors
	WIMAX_API_RET_SUCCESS,	
	/// Fail to obtain results
	WIMAX_API_RET_FAILED,	
	/// Buffer size pass in parameter is too small.
	WIMAX_API_RET_BUFFER_SIZE_TOO_SMALL,	
	/// Invalid privileges to execute the command
	WIMAX_API_RET_PERMISSON_DENIED,	
	/// Device specified is invalid.
	WIMAX_API_RET_INVALID_DEVICE,	
	/// Invalid Parameter Passed
    WIMAX_API_RET_INVALID_PARAMETER,
	/// Cannot perform the command mobile connection.
	WIMAX_API_RET_ALREADY_CONNECTED,
    /// Link is not connected, cannot obtain result.
	WIMAX_API_RET_LINK_NOT_CONNECTED,
	/// Connection to the network is prohibited
	WIMAX_API_RET_NETWORK_PROHIBITED,
	/// Device specified is missing because of just being removed!
	WIMAX_API_RET_DEVICE_MISSING,
	/// Profile specified is invalid.
	WIMAX_API_RET_INVALID_PROFILE,	
	/// Connection to a roaming network is not allowed.
	WIMAX_API_RET_ROAMING_NOT_ALLOWED,	
	/// Connection is already in progress
	WIMAX_API_RET_CONNECTION_IN_PROGRESS,

	/// last error code
	WIMAX_API_RET_LAST_COMMON_ERROR,	

	///intel extended return code
	///does not have the rf control
	WIMAX_API_RET_INTEL_NO_RF
} WIMAX_API_RET;

#endif