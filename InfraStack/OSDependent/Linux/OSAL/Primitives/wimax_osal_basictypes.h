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
#ifndef _WIMAX_OSAL_BASICTYPES_
#define _WIMAX_OSAL_BASICTYPES_

#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#if 0
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif 


#ifndef NATIVE_LINUX
#define	NATIVE_LINUX			// 	To keep all compilations going...
#endif

#include "wimax_osal_linux_types.h"
#include "wimax_osal_error.h"
#include "windows_error.h"
#include "wimax_consts.h"


#ifndef _WIMAX_API_TYPES_H
#include "CommonTypes.h"				// @@@ : 5/11/09 : JSS - Required (details in mtg if needed)

#else

// #include "ObsoletedTypes.h"

#endif


#define _TRUNCATE (size_t)-1

typedef wchar_t	WIMAX_CHAR;
typedef char *OSAL_WIMAX_API_WSTRING;

// ################ IMPORTANT ######################
//
// TODO::OSAL-WORK::IMPORTANT - OSAL_filetime - New type (review usage) 
typedef time_t OSAL_filetime;

typedef struct _OSAL_filetime_ex
{
	unsigned int dwLowDateTime;
	unsigned int dwHighDateTime;
} OSAL_filetime_ex;

typedef void (*OSAL_thread_func)(void *);
typedef void* (*OSAL_linux_thread_func)(void *);

typedef void* OSAL_critical_section;

typedef int pid_t;

typedef int OSAL_thread_t;

typedef void * OSAL_event_t;

//typedef void * OSAL_pfn_ptr;

typedef unsigned int OSAL_threadkey_t;

// Just to get around some crazy type dependencies..
typedef unsigned short WMX_UINT16;	
typedef unsigned int WMX_UINT32;	


typedef int SOCKET;

// TODO::OSAL-WORK::IMPORTANT-BUT-NOT-CRITICIAL - Implement this.
typedef struct _VALENT {
	char *ve_valuename;
	WMX_UINT32 ve_valuelen;
	WMX_UINT32* ve_valueptr;
	WMX_UINT32 ve_type;
} VALENT, *PVALENT;

typedef struct _SYSTEMTIME
{
	WMX_UINT16	wYear;
	WMX_UINT16  wMonth;
	WMX_UINT16  wDayOfWeek;
	WMX_UINT16  wDay;
	WMX_UINT16  wHour;
	WMX_UINT16  wMinute;
	WMX_UINT16  wSecond;
	WMX_UINT16  wMilliseconds;
} SYSTEMTIME, *LPSYSTEMTIME;

typedef struct _OVERLAPPED 
{
	int dummy;	// not being used presently;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _DATA_BLOB
{
	WMX_UINT32 cbData;
	unsigned char* pbData;
} DATA_BLOB;


typedef VALENT OSAL_VALENT;

typedef FILE OSAL_FILE;

typedef struct _OSAL_find_data
{
	unsigned int dwFileAttributes;
	OSAL_filetime_ex ftCreationTime;
	OSAL_filetime_ex ftLastAccessTime;
	OSAL_filetime_ex ftLastWriteTime;
	unsigned int nFileSizeHigh;
	unsigned int nFileSizeLow;
	char cFileName[MAX_PATH];
	
} OSAL_FIND_DATA;


typedef void * OSAL_findHandle;

typedef UINT32 OSAL_mode_t;

#define	OSAL_PATH_SEPARATOR		'/'

/*********** FILE ATTRIBUTES ***********/
#define OSAL_FILE_ATTRIBUTE_READONLY	S_IRUSR | S_IRGRP | S_IROTH
#define OSAL_FILE_ATTRIBUTE_DIRECTORY	S_IFDIR
#define OSAL_FILE_ATTRIBUTE_DEVICE	S_IFBLK
#define OSAL_FILE_ATTRIBUTE_NORMAL	S_IFREG
#define OSAL_FILE_ATTRIBUTE_TEMPORARY	S_IFREG | S_IRWXU | S_IRWXG | S_IRWXO


// ############################# WINDOWS SPECIFIC MACROS / TYPES #################


#define 	_SH_DENYNO		0

typedef void * HANDLE;

//#define BMI_INLINE

#define EXTERN_C

#define	CE_PREFIX		


// ############################# WINDOWS SPECIFIC MACROS #################

#define OSAL_PATH_SEPARATOR '/'


#endif //_WIMAX_OSAL_BASICTYPES_
