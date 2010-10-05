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

#ifndef __WIMAX_OSAL_LINUX_TYPES_H__
#define __WIMAX_OSAL_LINUX_TYPES_H__

#include <stdint.h>
#include <wchar.h>
#include <wctype.h>
#include <time.h>


#ifndef NULL
#define NULL    ((void *)0)
#endif // NULL

#ifndef FALSE
#define FALSE               0
#endif // FALSE

#ifndef TRUE
#define TRUE                1
#endif // TRUE

#if !defined(WIMAX_SYS_WINDOWS)

#ifndef IN
#define IN
#endif // IN

#ifndef OUT
#define OUT
#endif // OUT

#define EXPORT

#define EXTERN extern
// #define EXTERN_C extern

#define __stdcall

#define WCHAR wchar_t

#define CONST 		const

#endif // ! WIMAX_SYS_WINDOWS


typedef int errno_t;

typedef unsigned char byte; 


// ###########################################################################################

// @@@ : JSS - Group all the types that have been replicated inside of WiMAXTypes.h header and 
// put their definitions inside of a conditional to keep compiler happy


//#ifndef _WIMAX_API_TYPES_H

typedef unsigned char UINT8;

typedef short INT16;
typedef unsigned short UINT16;

typedef int INT32;
typedef unsigned int UINT32;

typedef signed long long INT64;
typedef unsigned long long UINT64;

//#endif // if not defined _WIMAX_API_TYPES_H

// ###########################################################################################


typedef unsigned int DWORD;

typedef int * INT_PTR;


typedef char INT8;

typedef int BOOL;
typedef char CHAR;

typedef int INT;
typedef unsigned int UINT;
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef BYTE *PBYTE;
typedef unsigned long ULONG;

#if 0 // ndef __COMMONTYPES_H

typedef unsigned int *PUINT;

typedef UINT POINTER_AND_UINT;

#endif


typedef long LONG;
typedef long *LPLONG;
typedef unsigned long *ULONG_PTR;


typedef void VOID;

typedef void * LPVOID;

typedef double DOUBLE;


//
// UNICODE
//

typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
typedef CONST WCHAR *LPCWCH, *PCWCH;
typedef WCHAR *LPWSTR, *PWSTR;
typedef CONST WCHAR *LPCWSTR, *PCWSTR;



//
// ANSI
//

typedef CHAR *PCHAR, *LPCH, *PCH;
typedef CONST CHAR *LPCCH, *PCCH;
typedef CHAR *LPSTR;
typedef CONST CHAR *LPCSTR;

//
// Neutral ANSI/UNICODE types and macros
//
#ifdef UNICODE

#ifndef _TCHAR_DEFINED
	typedef WCHAR TCHAR, *PTCHAR;
	typedef WCHAR TBYTE, *PTBYTE;
#define _TCHAR_DEFINED
#endif				// !_TCHAR_DEFINED

	typedef LPWSTR LPTCH, PTCH;
	typedef LPWSTR PTSTR, LPTSTR;
	typedef LPCWSTR PCTSTR, LPCTSTR;

#else				// UNICDOE

#ifndef _TCHAR_DEFINED
	typedef char TCHAR, *PTCHAR;
	typedef unsigned char TBYTE, *PTBYTE;
#define _TCHAR_DEFINED
#endif				// !_TCHAR_DEFINED

	typedef LPSTR LPTCH, PTCH;
	typedef LPSTR PTSTR, LPTSTR;
	typedef LPCSTR PCTSTR, LPCTSTR;

#endif				// UNICODE



// Types used for communicating with lower layers


typedef unsigned long long U64;
typedef unsigned short USHORT;

#if 0 //  __TYPES_PROXY_H		// Now already being defined in one of the platform level headers...

typedef CHAR *PSTR;
typedef CONST CHAR *PCSTR;

typedef void *PVOID;

typedef signed char *PINT8;
typedef signed short *PINT16;
typedef signed int *PINT32;
typedef unsigned char *PUINT8;
typedef unsigned short *PUINT16;
typedef unsigned int *PUINT32;

typedef signed long long  *PINT64;
typedef unsigned long long  *PUINT64;

typedef INT SINT;
typedef char SINT8;
typedef short SINT16;
typedef int SINT32;
typedef signed long long SINT64;

// booleans

typedef unsigned char BOOL8;
typedef unsigned short BOOL16;
typedef unsigned int BOOL32;
typedef unsigned long long BOOL64;


// volatiles
typedef volatile INT VINT;
typedef volatile INT8 VINT8;
typedef volatile short VINT16;
typedef volatile int VINT32;
typedef volatile long long VINT64;

typedef volatile UINT VUINT;
typedef volatile unsigned char VUINT8;
typedef volatile unsigned short VUINT16;
typedef volatile unsigned int VUINT32;
typedef volatile unsigned long long VUINT64;

 // pointers to volatile
typedef VINT *PVINT;
typedef VINT8 *PVINT8;
typedef VINT16 *PVINT16;
typedef VINT32 *PVINT32;
typedef VINT64 *PVINT64;

typedef VUINT *PVUINT;
typedef VUINT8 *PVUINT8;
typedef VUINT16 *PVUINT16;
typedef VUINT32 *PVUINT32;
typedef VUINT64 *PVUINT64;

#endif // 0

#ifndef WIMAX_SYS_WINDOWS
typedef time_t wmx_filetime;
#else
typedef FILETIME wmx_filetime;
#endif

struct wmx_file_stat
{
	wmx_filetime ftLastAccessTime;
	wmx_filetime ftLastWriteTime;
	char cFileName[256];	// just like the way dirent struct does it...
};

// time in hrs mins sec
struct time_in_day_hr_min_sec_msec
{
int tm_msec;
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};


#endif //__WIMAX_OSAL_LINUX_TYPES_H__
