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
#ifndef _UDAPI_COMMON_DEFINES_H
#define _UDAPI_COMMON_DEFINES_H

#include "wimax_osal_types.h"

#define	OSAL_ADAPTER_AIFAL_MAX_PAYLOAD	(8 * 1024)

#define TASK_DATA_TYPE_SIZE sizeof(taskDataType)

#define MAX_APPS_PER_DLL	16


typedef struct 
{
	UINT32		taskId;
	UINT32		bIsParam4aReplyTui;
	UINT32		param4;
	UINT32      length;
	char		data[OSAL_ADAPTER_AIFAL_MAX_PAYLOAD];
} taskDataType;


// Exact listing of error codes TBD
enum UDAPI_ERROR_CODE
{
	UDAPI_SUCCESS,
	UDAPI_FAIL,
	UDAPI_TIMEOUT,
	UDAPI_NOT_CONNECTED,
	UDAPI_SOCKET_WAS_CLOSED_BY_PEER,
	UDAPI_WRONG_PAYLOAD_SIZE,
	UDAPI_ACCESSIBILITY_ERROR
};

#endif //_UDAPI_COMMON_DEFINES_H