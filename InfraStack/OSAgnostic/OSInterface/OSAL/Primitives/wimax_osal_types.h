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

#ifndef __WIMAX_OSAL_TYPES_H__
#define __WIMAX_OSAL_TYPES_H__

#include "wimax_osal_basictypes.h"

#define MAX_PATH								260
#define MAX_DIR									256
#define MAXSHORT								0x7fff

#define WMX_EINVAL								22
#define	WMX_ETIMEDOUT							258		// Make it same as WAIT_TIMEOUT 

#define	WMX_EACCES								13
#define	WMX_EEXIST								17

#define TEXT_LEN(arg) 							(arg*2)

// Abstract types
typedef void * OSAL_mutex_t;
typedef void * OSAL_dynlib_t; 
typedef int (*OSAL_pfn_ptr)();

typedef	struct OSAL_file_stat_t
{
	OSAL_filetime	ftLastAccessTime;
	OSAL_filetime	ftLastWriteTime;
	OSAL_filetime	ftCreationTime;
	OSAL_mode_t		fileAttributes;
	char			cFileName[256];	// just like the way dirent struct does it...
} OSAL_file_stat;


#endif //__WIMAX_OSAL_TYPES_H__
