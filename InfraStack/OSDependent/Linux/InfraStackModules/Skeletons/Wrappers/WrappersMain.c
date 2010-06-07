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
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"

#include "iWmxSDK.h"
#include "Versions.h"

extern char g_atWrapperName[];
extern wmx_Version_t g_atVersionWrapper; 
extern OSAL_critical_section cs;

static void __attribute ((constructor)) iWmxSdk_init(void);
static void __attribute ((destructor)) iWmxSdk_fini(void);

void iWmxSdk_init()
{
	size_t nameLen;
	// init critical section

	OSAL_init_critical_section(&cs);

		SET_VERSION(g_atVersionWrapper, IWMXSDK_MAJOR, IWMXSDK_MINOR, IWMXSDK_BUILD, IWMXSDK_REVISION, IWMXSDK_BRANCH);		
		nameLen = strlen(WRAPPER_NAME);
		if (nameLen >= WRAPPER_NAME_LEN)
		{
			OSAL_strncpy_s(g_atWrapperName, WRAPPER_NAME_LEN - 1, WRAPPER_NAME, WRAPPER_NAME_LEN - 1);
		}
		else
		{
			OSAL_strcpy_s(g_atWrapperName, WRAPPER_NAME_LEN - 1, WRAPPER_NAME);
		}							
}

void iWmxSdk_fini()
{
	OSAL_delete_critical_section(&cs);
}


