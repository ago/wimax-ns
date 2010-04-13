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

#ifndef __WIMAX_STRING_H__
#define __WIMAX_STRING_H__

#include "wimax_osal_types.h"

///////////////////////////////////////////////////////////////////////
//
// memory methods...
//
int OSAL_memcpy_s(void *dest, size_t sizeInBytes, const void *src, size_t count);


///////////////////////////////////////////////////////////////////////
//
// copy methods...
//
int OSAL_strncpy_s(char *strDest, size_t sizeInBytes, const char *strSource, size_t count);

/*
*  The strcpy_s function copies the contents in the address of strSource, 
*  including the terminating null character, to the location specified by strDestination
*/
int OSAL_strcpy_s(char *strDestination, size_t sizeInBytes, const char *strSource);


int OSAL_strnlen(const char *str, size_t sizeInBytes );
size_t OSAL_wcsnlen(const wchar_t *str, size_t sizeInWchars);
size_t OSAL_CAPI_wcsnlen(const OSAL_WIMAX_API_WSTRING str, size_t sizeInWchars);
size_t OSAL_wcslen( const wchar_t *str );
size_t OSAL_CAPI_wcslen( const OSAL_WIMAX_API_WSTRING str );
int OSAL_wcscpy_s(wchar_t *strDestination, size_t sizeInWords, const wchar_t *strSource);
int OSAL_wcsncpy_s(wchar_t *strDest, size_t sizeInWords, const wchar_t *strSource, size_t count);

size_t OSAL_CAPI_wcsnlen(const OSAL_WIMAX_API_WSTRING str, size_t sizeInWchars);
int OSAL_CAPI_strcpy_s(OSAL_WIMAX_API_WSTRING strDestination, size_t sizeInWords, const OSAL_WIMAX_API_WSTRING strSource);
int OSAL_CAPI_strncmp(const char* str1, const char* str2, size_t maxCount);

char *OSAL_strstr(const char *str, const char *strSearch); 
/*
*  This function try to copy the first D wide characters of strSource to strDest, where D is the lesser 
*  of count and the length of strSource_itoa_s
*/
int OSAL_strlwr_s(char *str, size_t sizeOfBytes);

///////////////////////////////////////////////////////////////////////
//
// print char methods...
//
int OSAL_snprintf(char *buffer, size_t sizeOfBuffer, size_t count, const char *format, ...);

/* 
*  fprintf_s formats and prints a series of characters and values to the output stream.
*/
int OSAL_fprintf_s(FILE *, const char *, ...);
void OSAL_MyPrintf(const char* format, ...);

/*
*  The sprintf_s function formats and stores a series of characters and values in buffer
*/
int OSAL_sprintf_s(char *, size_t, const char *, ...);
int OSAL_wsprintf_s(WCHAR *, size_t, const WCHAR *, ...);

///////////////////////////////////////////////////////////////////////
//
// get char methods...
//
int OSAL_getch(void);
char *OSAL_gets_s(char *buffer, size_t sizeInCharacters);

///////////////////////////////////////////////////////////////////////
//
// compare wchar methods...
//
/* _wcsicmp accepts two widechar strings After converting them to lowercase function compares them */
int OSAL_wcsicmp(const WCHAR *, const WCHAR *);
/* _wcuprs_s converts strSize no of wide chars of str to uppercase */
int OSAL_wcsupr_s(WCHAR * str, size_t strSize);
int OSAL_wcscmp(const wchar_t *string1, const wchar_t *string2);

///////////////////////////////////////////////////////////////////////
//
// compare char methods...
//
/*
*The _stricmp function compares lowercase versions of two strings
*/
int OSAL_stricmp(const char *, const char *);

///////////////////////////////////////////////////////////////////////
//
// cat methods...
//
/*
*The strcat_s function appends Source string to Destination string
*/
int OSAL_strcat_s(char *, size_t, const char *);

/*
*The strcat_s function appends Source string to Destination string with n numbers
If return value is zero successfull other wise return error code
*/
int OSAL_strncat_s(char *dest, size_t desnumberofelement, const char *src,size_t maxcount);
/*
*The wcscat_s function appends Source string to Destination string
*/
char *OSAL_strtok_s(char *, const char *, char **);

///////////////////////////////////////////////////////////////////////
//
// scanf methods...
//
/*
* the sscanf_s reads formatted data from a string
*/
int OSAL_sscanf_s(const char *_Src, const char *_Format, ...);

int OSAL_fseek(FILE *stream, long offset, int origin);
///////////////////////////////////////////////////////////////////////
//
// conversion methods...
//
/*
* the _itoa_s converts an integer to string
*/
int OSAL_itoa_s(int _Value, char *_DstBuf, size_t _Size, int _Radix);

///////////////////////////////////////////////////////////////////////
//
// string helper methods...
//
int OSAL_multibytetowidechar(unsigned int codepage, UINT32 dwFlags, char *lpmultibytestr, int cbmultibyte, WIMAX_CHAR * lpwidecharstr, int cchwidechar);
int OSAL_widechartomultibyte(unsigned int CodePage, UINT32 dwFlags, WIMAX_CHAR * lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, char * lpDefaultChar, BOOL * lpUsedDefaultChar);

int OSAL_L3L4_MultiByteToWideChar(unsigned int codepage, UINT32 dwFlags, char *lpmultibytestr, int cbmultibyte, WIMAX_CHAR * lpwidecharstr, int cchwidechar);
int OSAL_L3L4_WideCharToMultiByte(unsigned int CodePage, UINT32 dwFlags, WIMAX_CHAR * lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, char * lpDefaultChar, BOOL * lpUsedDefaultChar);

int OSAL_CAPI_MultiByteToWideChar(unsigned int codepage, UINT32 dwFlags, char *lpmultibytestr, int cbmultibyte, WIMAX_CHAR * lpwidecharstr, int cchwidechar);
int OSAL_CAPI_WideCharToMultiByte(unsigned int CodePage, UINT32 dwFlags, WIMAX_CHAR * lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, char * lpDefaultChar, BOOL * lpUsedDefaultChar);

#endif				// __WIMAX_STRING_H__
