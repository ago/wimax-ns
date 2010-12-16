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
#if !defined(WIMAX_SYS_WINDOWS)		// and any other non-linux systems this can get ported to

#define _GNU_SOURCE

#include "wimax_osal_primitives.h"
#include <stdarg.h>
#include <wchar.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <iconv.h>
#include <errno.h>

#include "wimax_osal_trace.h"
#include "windows_error.h"

#define OSAL_MAX_MESSAGE_LEN	8192

// Internal function declaration. 

int xtox_s_1(unsigned long val,
	     char *buf, size_t sizeInTChars, unsigned radix, int is_neg);

/*
The  OSAL_memcpy_s()  function  copies  n bytes from memory area src to memory area dest.  The memory areas should not overlap.  
*/
int OSAL_memcpy_s(void *dest, size_t sizeInBytes, const void *src, size_t count)
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if ((src == NULL) || (count == 0)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error source buffer is NULL or format is NULL"));
		return -1;
	}

	if ((dest == NULL)) {
		errno = -EINVAL;
		return -1;
	}

	if (sizeInBytes < count) {
		errno = -ERANGE;
		return -1;
	}

	memcpy(dest, src, count);

	return 0;
}


/*
The OSAL_strncpy_s() function copies not more than n bytes of src to the destination string.
Thus, if there is no null byte among the first n bytes of src, the result will not be null-terminated.

In the case where the length of src is less than that of n, the remainder of dest will be padded with null bytes.
Dest string should hold count+1 characters unless count != _TRUNCATE 
*/
int OSAL_strncpy_s(char *strDest, size_t sizeInBytes, const char *strSource,
	      size_t count)
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	//int ret;
	if ((strSource == NULL) || (strDest == NULL)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error source or Destination string  is NULL"));
		return -EINVAL;
	}
	if (sizeInBytes == 0) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as size of Destination string is 0"));
		return -EINVAL;
	}

	if (count == _TRUNCATE) {
		int len = 0;
		len = strlen(strSource);
		//sizeInBytes = sizeInBytes>(len+1)?(len+1):sizeInBytes;
		if (sizeInBytes >= len + 1) {
			sizeInBytes = len + 1;
			strncpy(strDest, strSource, sizeInBytes);
			OSALTRACE(OSAL_DEBUG, ("Exit Success"));
			return 0;
		} else {
			strncpy(strDest, strSource, sizeInBytes - 1);
			strDest[sizeInBytes - 1] = '\0';
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error StrDest is filled with sizeInBytes no of charactes count=_TRUNCATE"));
			return -1;
		}
	} else {
		int len = 0;
		len = strlen(strSource);
		// To Accomodate the Null character
		// len++;               
		count = count > len ? len : count;
		// sizeInBytes-1 to include Null character
		if ((sizeInBytes - 1) < count) {
			strDest[0] = '\0';
			errno = -ERANGE;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error Dest buffer is not big enough to hold  %d characters",
				   count + 1));
			return -1;
		} else {
			strncpy(strDest, strSource, count + 1);
			strDest[count] = '\0';
			OSALTRACE(OSAL_DEBUG, ("Exit Success"));
			return 0;
		}
	}

}

/*
*  The OSAL_strcpy_s function copies the contents in the address of strSource, 
*  including the terminating null character, to the location specified by strDestination. 
*  The destination string must be large enough to hold the source string, including the terminating null character
*
*  RETURN VALUES
*  strDestination  	    numberOfElements  	    strSource  	    Return value    Contents of strDestination
*  NULL                     any                     any             -EINVAL          not modified
*  any                      any                     NULL            -EINVAL          not modified
*  any                      0, or too small         any             -ERANGE          not modified
*  
*  Function not only returns error sets the errno also
*  TODO :In Windows version invalid parameter handler is called on error, and if execution is allowed to continue error is returned, 
*        in Linux version only error is returned	
*/

int OSAL_strcpy_s(char *strDestination, size_t sizeInBytes, const char *strSource)
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if ((strDestination == NULL) || (strSource == NULL)) {
		errno = -EINVAL;
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer or Src buffer is NULL ret = -EINVAL"));
		return -EINVAL;
	}
	//strlen returns no of characters excluding the terminating NULL character
	// But strcpy_s copies the terminating Null character too
	if ((sizeInBytes == 0) || (sizeInBytes < (strnlen(strSource,sizeInBytes) + 1))) {
	// if ((sizeInBytes == 0) || (sizeInBytes < (strlen(strSource) + 1))) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer size is zero or not enough to hold src ret = -ERANGE"));
		return -ERANGE;
	}
 
	strcpy(strDestination, strSource);
	OSALTRACE(OSAL_DEBUG, ("Exit Success return is 0"));
	return 0;

}

/*
The OSAL_wcstombs_s() function converts the wide-character string src to a multibyte string starting at dest provided the 
destination string is not a NULL pointer.
	
*/
int OSAL_wcstombs_s(size_t * pReturnValue, char *mbstr, size_t sizeInBytes,
	       const wchar_t * vcstr, size_t count)
{
	size_t convertedChars = 0;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if ((vcstr == NULL) || (sizeInBytes == 0)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error source buffer is NULL or format is NULL"));
		return -1;
	} else if (mbstr == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error the required size in bytes of the destination string is: %d ",
			   pReturnValue));
		return -1;
	}

	if (count == _TRUNCATE) {
		if (sizeInBytes < count) {
			convertedChars = wcstombs(mbstr, vcstr, count);
			if (pReturnValue != NULL)
				*pReturnValue = convertedChars;
			mbstr[sizeInBytes] = '\0';
			OSALTRACE(OSAL_DEBUG,
				  ("Exit success. coiped or converted %d of bytes",
				   convertedChars));

			if (convertedChars == (size_t) - 1) {
				errno = -EINVAL;
				return EINVAL;
			} else
				return 0;	// success return
		} else {
			errno = -EINVAL;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error source buffer is NULL or format is NULL"));
			return EINVAL;
		}

	} else {
		convertedChars = wcstombs(mbstr, vcstr, count);
		if (pReturnValue != NULL)
			*pReturnValue = convertedChars;

		if (convertedChars == (size_t) - 1) {
			errno = -EINVAL;
			return EINVAL;
		} else {
			return 0;
		}
	}

}

/*
The  OSAL_wcscpy_s()  function is the wide-character equivalent of the strcpy() function. It copies the wide character string pointed to by src, including the  terminating  L’\0’  character, to the array pointed to by dest.
The strings may not overlap.
The programmer must ensure that there is room for at least wcslen(src)+1 wide characters at dest.

*/
int OSAL_wcscpy_s(wchar_t * strDestination, size_t sizeInWordsconst,
	     const wchar_t * strSource)
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if ((strSource == NULL) || (strDestination == NULL)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error source or Destination buffer is NULL"));
		return -EINVAL;
	}
	if ((sizeInWordsconst == 0)
	    || (sizeInWordsconst < wcslen(strSource) + 1)) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit error Destination buffer size is null or too small"));
		return -ERANGE;
	}
	wcscpy(strDestination, strSource);
	OSALTRACE(OSAL_DEBUG, ("Exit Success"));
	return 0;
}
/*
*  This function try to copy the first D wide characters of strSource to strDest, where D is the lesser 
*  of count and the length of strSource. If those D wide haracters will fit within strDest (whose size is given as numberOfElements) 
*  and still leave room for a null terminator, then those wide characters are copied and a terminating null 
*  is appended; otherwise, strDest[0] is set to the null character and the invalid parameter handler is invoked.
*
*  There is an exception to the above paragraph. If count is _TRUNCATE, then as much of strSource as will 
*  fit into strDest is copied while still leaving room for the terminating null which is always appended.
*  
*  Note that unlike strncpy, if count is greater than the length of strSource, the destination string 
*  is NOT padded with null characters up to length count. 
*  
*  If strDest or strSource is NULL, or numberOfElements is 0, the invalid parameter handler is invoked. 
*  If execution is allowed to continue, the function returns -EINVAL and sets errno to -EINVAL.
*  
*  TODO: In Windows version invalid parameter handler is called on error, and if execution is allowed to 
*        continue an error is returned.In Linux version only error is returned	
*/
int OSAL_wcsncpy_s(wchar_t * strDest, size_t sizeInWords, const wchar_t * strSource,
	      size_t count)
{
	int D = 0;
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if ((strDest == NULL) || (strSource == NULL) || (sizeInWords == 0)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buf = NULL or Src buf = NULL or Size of Dest buf ret = -EINVAL"));
		return -EINVAL;
	}
	if (count == _TRUNCATE) {
		//wprintf(L"StringAPI.c wcncpy_s count = _TRUNCATE \n");
		// +1 is for the WEOF  
		// wcslen returns size except WEOF
		if ((wcslen(strSource) + 1) > sizeInWords) {
			//wprintf(L"StringAPI.c wcncpy_s wcslen(strSource)+1)>sizeInWords\n");
			wcsncpy(strDest, strSource, sizeInWords);
			strDest[sizeInWords] = L'\0';
			// According to windows we need to return STRUNCATE 
			// But Pipe source is not using the return value so forget it
			errno = -1;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error count = _TRUNCATE Dest is Truncated ret = -1"));
			return -1;
		} else {
			//wprintf(L"StringAPI.c wcncpy_s !wcslen(strSource)+1)>sizeInWords\n");
			// wcsncpy won't append the WEOF character after wcslen(strSource) wide chars 
			wcsncpy(strDest, strSource, wcslen(strSource));
			strDest[wcslen(strSource)] = L'\0';
			OSALTRACE(OSAL_DEBUG, ("Exit Success return is zero"));
			return 0;
		}
	} else {
		//wprintf(L"StringAPI.c wcncpy_s count != _TRUNCATE \n");
		// +1 is for the WEOF
		// count is the no of wide chars to be copied except WEOF 
		D = ((wcslen(strSource) + 1) >
		     count) ? count : (wcslen(strSource) + 1);
		//wprintf(L"No of characters %d", D);
		if (D > sizeInWords) {
			//wprintf(L"StringAPI.c wcncpy_s(count+1)>sizeInWords\n");
			strDest[0] = L'\0';
			errno = -EINVAL;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error Dest buffer is not as big as Src Buffer ret = -EINVAL"));
			return -EINVAL;
		} else {
			wcsncpy(strDest, strSource, D - 1);
			strDest[D - 1] = L'\0';
			OSALTRACE(OSAL_DEBUG, ("Exit Success return is zero"));
			return 0;
			//wprintf(L"StringAPI.c wcncpy_s!(count+1)>sizeInWords\n");
			/*if(count > wcslen(strSource))
			   {
			   wcsncpy(strDest, strSource, wcslen(strSource));
			   strDest[wcslen(strSource)] = L'\0';
			   OSALTRACE(OSAL_DEBUG, ("Exit Success return is zero"));
			   return 0;
			   }
			   else
			   {
			   wcsncpy(strDest, strSource, count);
			   strDest[count] = L'\0';
			   OSALTRACE(OSAL_DEBUG, ("Exit Success return is zero"));
			   return 0;
			   } */
		}
	}
}

/*
The OSAL_wcstok_s() function is the wide-character equivalent of the strtok() function, with an added argument to make it multithread-safe. It can be used to split a wide-character  string  strToken  into tokens, where a token is defined as a substring not containing any wide-characters from strDelimit.
*/

wchar_t *OSAL_wcstok_s(wchar_t * strToken, const wchar_t * strDelimit,
		  wchar_t ** context)
{
	wchar_t *token;
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if (((strToken == NULL) && ((context == NULL) || (*context == NULL)))
	    || (strDelimit == NULL)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error source buffer is NULL or format is NULL"));
		return NULL;

	}

	token = wcstok(strToken, strDelimit, context);

	if (token != NULL) {
		OSALTRACE(OSAL_DEBUG, ("Exit success"));
	} else {
		OSALTRACE(OSAL_DEBUG, ("Exit no tokens found"));
	}

	return token;
}

/*
OSAL_strlwr_s() converts the string to lower case, if possible. If c is not an unsigned char value, or EOF, the behaviour of these functions is undefined.
*/

int OSAL_strlwr_s(char *str, size_t sizeInBytes)
{

	register int counter;
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (str == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error no further tokens are found. It could be NULL"));
		return -EINVAL;
	}
	if ((sizeInBytes == 0) || (sizeInBytes < strlen(str) + 1)) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as sizeInBytes is smaller than str length"));
		return -ERANGE;
	}
	for (counter = 0; str[counter]; ++counter) {
		str[counter] = tolower(str[counter]);
		if (0 == islower(str[counter])) {
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error Could not convert string into lower case"));
			return -1;
		}
	}

	OSALTRACE(OSAL_DEBUG, ("Exit success."));
	return 0;
}

/*
The OSAL_wsprintf function formats and stores a series of characters and values in a buffer.
Any arguments are converted and copied to the output buffer according to the corresponding format specification in 
the format string. The function appends a terminating null character to the characters it writes, but the return 
value does not include the terminating null character in its character count.
*/
int OSAL_wsprintf(char *IpOut, const char *IpFmt, ...)
{
	int numOfChars;
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if (IpFmt == NULL) {

		errno = -EINVAL;
		OSALTRACE(OSAL_DEBUG, ("Exit input format is NULL"));
		return -1;
	}
	va_list ap;
	va_start(ap, IpFmt);
	if ((numOfChars = sprintf(IpOut, IpFmt, ap)) > 0) {
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return numOfChars;
	} else {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error in formating the desired output "));
		return -1;
	}

	va_end(ap);

}
int OSAL_snwprintf(wchar_t * buffer, size_t count, const wchar_t * format, ...)
{
	int numOfChars;
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (buffer == NULL || format == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL"));
		return -1;
	}

	va_list ap;
	va_start(ap, format);
	va_end(ap);

	numOfChars = vswprintf(buffer, count, format, ap);

	if (numOfChars < count) {
		buffer[numOfChars] = '\0';
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return numOfChars;
	} else if (numOfChars == count) {
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return numOfChars;
	} else if (numOfChars > count) {

		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return -1;
	} else {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL"));
		return -1;
	}

}

//OSAL_vsprintf_s is an implementation of UNIX vswprintf()
int OSAL_vswprintf_s(wchar_t * buffer, size_t sizeInWords, const wchar_t * format,
		va_list argptr)
{
	int numOfChars;
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (buffer == NULL || format == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL"));
		return -1;
	}

	if ((numOfChars = (vswprintf(buffer, sizeInWords, format, argptr))) > 0) {
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return numOfChars;
	} else {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error in formating the desired output "));
		return -1;
	}
}

int OSAL_vsnwprintf_s(wchar_t * buffer, size_t sizeOfBuffer, size_t count,
		  const wchar_t * format, va_list argptr)
{
	//int numOfChars;
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	wchar_t *tmpBuffer;
	unsigned int total_length = 0;
	if (buffer == NULL || format == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL"));
		return -EINVAL;
	}
	if (sizeOfBuffer == 0) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as size of Destination buffer is 0"));
		return -ERANGE;
	}

	tmpBuffer = (wchar_t *) malloc(OSAL_MAX_MESSAGE_LEN * sizeof(wchar_t));
	if (tmpBuffer == NULL) {
		buffer[0] = L'0';
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Unable to allocate tmp Buffer ret -1 "));
		return -1;
	}
	total_length =
	    vswprintf(tmpBuffer, OSAL_MAX_MESSAGE_LEN, format, argptr);
	if (total_length == -1) {
		buffer[0] = L'\0';
		errno = -EINVAL;
		free(tmpBuffer);
		OSALTRACE(OSAL_ERROR, ("Exit Error ret = -1"));
		return -1;
	}
	//wprintf(L"argno = %d \n", argno);

	if (count == _TRUNCATE) {
		if (sizeOfBuffer > total_length) {
			wcsncpy(buffer, tmpBuffer, total_length);
			buffer[total_length] = L'\0';
			free(tmpBuffer);
			OSALTRACE(OSAL_DEBUG,
				  ("Exit success and the number of characters printed is %d",
				   total_length));
			return total_length;

		} else {
			wcsncpy(buffer, tmpBuffer, sizeOfBuffer - 1);
			buffer[sizeOfBuffer - 1] = L'\0';
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error Dest Buffer contains as much of the string that will fit  count = _TRUNCATE "));
			free(tmpBuffer);
			return -1;
		}
	} else {
		int len = total_length;
		total_length = (count > total_length) ? total_length : count;
		if (sizeOfBuffer <= total_length) {
			buffer[0] = L'\0';
			errno = -ERANGE;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error the Dest Buffer is smaller than string to be copied "));
			free(tmpBuffer);
			return -1;
		}
		wcsncpy(buffer, tmpBuffer, total_length);
		buffer[total_length] = L'\0';
		free(tmpBuffer);
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   total_length));
		if (len != total_length) {
			return -1;
		} else {
			return total_length;
		}

	}

}


/*
*  The OSAL_snwprintf_s function formats and stores count or fewer wide characters in buffer and appends a terminating null. 
*  Each argument (if any) is converted and output according to the corresponding format specification in format. 
*  If copying occurs between strings that overlap, the behavior is undefined.
*
*  If count is _TRUNCATE, then _snprintf_s writes as much of the string as will fit in buffer while leaving room for 
*  a terminating null. If the entire string (with terminating null) fits in buffer, then _snprintf_s returns the 
*  number of characters written (not including the terminating null); otherwise, 
*  OSAL_snprintf_s returns -1 to indicate that truncation occurred.
*
*
*  TODO: 1.Truncation is not implemented as there is no way to know the length of format + variable arguments
*        For now it returns -EINVAL, if count = _TRUNCATE
*	 2.In Windows version invalid parameter handler is called on error, and if execution is allowed to continue an error is returned, 
*        in Linux version only error is returned	
*
*/
int OSAL_snwprintf_s(wchar_t * buffer, size_t sizeOfBuffer, size_t count,
		 const wchar_t * format, ...)
{
	va_list ap;
	int argno = 0;
	wchar_t *tmpBuffer;
	//size_t total_length;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (buffer == NULL || format == NULL || count == 0) {
		errno = -EINVAL;
		OSALTRACE(OSAL_DEBUG,
			  ("Exit Error Dest buffer is NULL or format is NULL or count = 0 ret = -1"));
		return -1;
	}
	if (sizeOfBuffer == 0) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer lenght is zero ret = -1"));
		return -1;
	}

	tmpBuffer = (wchar_t *) malloc(OSAL_MAX_MESSAGE_LEN * sizeof(wchar_t));
	//wprintf(L"StringAPI.c _snwprintf_s !(count+1)>sizeOfBuffer \n");
	va_start(ap, format);
	argno = vswprintf(tmpBuffer, OSAL_MAX_MESSAGE_LEN, format, ap);
	va_end(ap);
	if (argno == -1) {
		buffer[0] = L'\0';
		errno = -EINVAL;
		free(tmpBuffer);
		OSALTRACE(OSAL_ERROR, ("Exit Error ret = -1"));
		return -1;
	}
	// for \0
	//wprintf(L"argno = %d \n", argno);

	if (count != _TRUNCATE) {
		int len = argno;
		argno = (count > argno) ? argno : count;
		//wprintf(L"argno = %d %Ls\n", argno, tmpBuffer);
		//wprintf(L"StringAPI.c _snwprintf_s count != _TRUNCATE \n");
		// +1 is for the WEOF
		// count is the no of wide chars to be copied except WEOF  
		if (argno >= sizeOfBuffer) {
			//wprintf(L"StringAPI.c _snwprintf_s (count+1)>sizeOfBuffer \n");
			errno = -ERANGE;
			buffer[0] = L'\0';
			free(tmpBuffer);
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error Dest buffer is not big enough to hold count + WEOF wide characters ret = -1"));
			return -1;
		} else {
			wcsncpy(buffer, tmpBuffer, argno);
			buffer[argno] = L'\0';
			free(tmpBuffer);
			OSALTRACE(OSAL_DEBUG,
				  ("Exit Success return is %d", argno));
			if (argno != len) {
				return -1;
			} else {
				return argno;
			}
		}
	} else {
		if (argno >= sizeOfBuffer) {
			wcsncpy(buffer, tmpBuffer, sizeOfBuffer - 1);
			buffer[sizeOfBuffer - 1] = L'\0';
			free(tmpBuffer);
			errno = -EINVAL;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error count =  _TRUNCATE Destination string is terminated ret = -1"));
			return -1;
		} else {
			wcsncpy(buffer, tmpBuffer, argno);
			buffer[argno] = L'\0';
			free(tmpBuffer);
			OSALTRACE(OSAL_DEBUG,
				  ("Exit Success return is %d", argno));
			return argno;

		}
	}
}

//OSAL_snprintf() is an implementation of snprintf()

int OSAL_snprintf(char *buffer, size_t count, const char *format, ...)
{
	int numOfChars;
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if ((buffer == NULL && count > 0) || (format == NULL)) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL"));
		return -1;
	}

	va_list ap;
	va_start(ap, format);
	va_end(ap);
	numOfChars = vsnprintf(buffer, count, format, ap);

	if (numOfChars < count) {
		buffer[numOfChars] = '\0';
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return numOfChars;
	} else if (numOfChars == count) {
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return numOfChars;
	} else if (numOfChars > count) {

		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the number of characters printed is %d",
			   numOfChars));
		return -1;
	} else {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL"));
		return -1;
	}

}
/* 
*  OSAL_fprintf_s formats and prints a series of characters and values to the output stream. 
*  returns negative value on error ans sets errno to -EINVAL
*
*  TODO:
*  1. Check the format is valid or not	
*  2. In Windows version invalid parameter handler is called on error, and if execution is allowed to continue error is returned, 
*        in Linux version only error is returned
*/
int OSAL_fprintf_s(FILE * stream, const char *fmt, ...)
{
	va_list ap;
	int argno = 0;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (stream == NULL || fmt == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as File pointer or Format buffer is NULL ret = -1"));
		return -1;
	}
	//wprintf(L" frintf_s parameters test passed \n");
	va_start(ap, fmt);

	argno = vfprintf(stream, fmt, ap);
	va_end(ap);
	OSALTRACE(OSAL_DEBUG, ("exit Success return is %d", argno));
	return argno;
}

//OSAL_getch() is an implementation of UNIX getch().

int OSAL_getch()
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	register int ch;

	if ((ch = getchar()) > 0) {
		OSALTRACE(OSAL_DEBUG,
			  ("Exit success and the character is %c", ch));
		return ch;
	} else {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error in taking the standard input. "));
		return -1;
	}
}
//OSAL_gets_s() is an implementation of UNIX getline().
//NOTE: the 3rd parameter in getline() is supposed to be given from the standard input device.

char *OSAL_gets_s(char *buffer, size_t sizeInCharacters)
{

	OSALTRACE(OSAL_DEBUG, ("Enter"));
	size_t bytesRead = 0;

	if ((buffer == NULL) || (sizeInCharacters <= 0))
		return NULL;

	bytesRead = getline(&buffer, &sizeInCharacters, stdin);

	// The returned buffer contain the \n character also
	// We need to overwrite with \0 Otherwise strcmp acting on the reply 
	// of this function will be in trouble
	if ((bytesRead - 1) >= 0) {
		buffer[bytesRead - 1] = '\0';
	}
	return buffer;
}

/*
*The OSAL_wcsicmp function compares lowercase versions of string1 and string2 and returns a value indicating their relationship
*/
int OSAL_wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
	int res = 0;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if ((str1 == NULL) || (str2 == NULL)) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as src or destination string is NULL ret =_NLSCMPERROR"));
		return -_NLSCMPERROR;
	}
	while ((towlower(*str1) != '\0')
	       && (towlower(*str1) == towlower(*str2))) {
		str1++;
		str2++;
	}
	res = (int)towlower(*str1) - (int)towlower(*str2);

	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", res));
	return res;

}


/*
* OSAL_wcuprs_s converts strSize no of wide wide chars of str to uppercase 
* This function validates its parameters. If str is a NULL pointer, the invalid parameter handler 
* is invoked, as described in Parameter Validation . If execution is allowed to continue, the functions 
* return -EINVAL and set errno to -EINVAL. If sizeInBytes or sizeInWords is less than the length of the string, 
* the functions return -ERANGE and set errno to -ERANGE.
* 
* TODO: In Windows version invalid parameter handler is called on error, and if execution is allowed to continue an error is returned, 
*       in Linux version only error is returned	
*/
int OSAL_wcsupr_s(wchar_t * str, size_t strSize)
{
	size_t size;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (str == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Src buffer is NULL ret = -EINVAL"));
		return -EINVAL;
	}

	size = wcslen(str);
	if (strSize < size) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Srs string size is more than the buffer size ret = -ERANGE"));
		return -ERANGE;
	}
	while (size) {
		*str = (wchar_t) towupper((wint_t) * str);
		str++;
		size--;
	}
	OSALTRACE(OSAL_DEBUG, ("Exit Success return is 0"));
	return 0;
}

/*
*The OSAL_stricmp function compares lowercase versions of string1 and string2 and returns a value indicating their relationship
*/
int OSAL_stricmp(const char *str1, const char *str2)
{
	int res = 0;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if ((str1 == NULL) || (str2 == NULL)) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as src or destination string is NULL ret =_NLSCMPERROR"));
		return -_NLSCMPERROR;
	}
	while ((tolower(*str1) != '\0') && (tolower(*str1) == tolower(*str2))) {
		str1++;
		str2++;
	}
	res = (int)tolower(*str1) - (int)tolower(*str2);

	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", res));
	return res;

}

/*
* The strcat_s function appends strSource to strDestination and terminates 
* the resulting string with a null character. The initial character of strSource 
* overwrites the terminating null character of strDestination. 
* The behavior of strcat_s is undefined if the source and destination strings overlap.
*
* NOTE: Note that the second parameter is the total size of the buffer, not the remaining size
*/
int OSAL_strcat_s(char *strDestination, size_t numberOfElements,
	     const char *strSource)
{
//	int res = 0;
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if ((strDestination == NULL) || (strSource == NULL)) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as src or destination string is NULL ret =-EINVAL"));
		return -EINVAL;
	}
	if ((numberOfElements == 0)
	    || (numberOfElements <
		(strlen(strDestination) + strlen(strSource) + 1))) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as NumberOfElements is zero or small ret=-ERANGE"));
		return -ERANGE;
	}
	strcat(strDestination, strSource);
	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", 0));
	return 0;
}

/*
* The OSAL_strncat_s function appends strSource to strDestination with respecitive of max 
* count and terminates the resulting string with a null character. The initial character
* of strSource overwrites the terminating null character of strDestination. 
* The behavior of strcat_s is undefined if the source and destination strings overlap.
*
* NOTE: Note that the second parameter is the total size of the buffer, not the remaining size
*/
int OSAL_strncat_s(char *dest, size_t desnumberofelement, const char *src,size_t maxcount)
{
//	int res = 0;
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if ((dest == NULL) || (src == NULL)) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as src or destination string is NULL ret =-EINVAL"));
		return -EINVAL;
	}
	if ((desnumberofelement == 0)
	    || (desnumberofelement<=maxcount)){
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as NumberOfElements is zero or small ret=-ERANGE"));
		return -ERANGE;
	}
	// linux standard function
	strncat(dest, src,maxcount);

	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", 0));
	return 0;

}

/*
* The OSAL_wcscat_s function appends strSource to strDestination and terminates 
* the resulting string with a null character. The initial character of strSource 
* overwrites the terminating null character of strDestination. 
* The behavior of strcat_s is undefined if the source and destination strings overlap.
*
* NOTE: Note that the second parameter is the total size of the buffer, not the remaining size
*/
int OSAL_wcscat_s(wchar_t * strDestination, size_t numberOfElements,
	     const wchar_t * strSource)
{
//	int res = 0;
	OSALTRACE(OSAL_DEBUG, ("Enter"));
	if ((strDestination == NULL) || (strSource == NULL)) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as src or destination string is NULL ret =-EINVAL"));
		return -EINVAL;
	}
	if ((numberOfElements == 0)
	    || (numberOfElements <
		(wcslen(strDestination) + wcslen(strSource) + 1))) {
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as NumberOfElements is zero or small ret=-ERANGE"));
		return -ERANGE;
	}
	wcscat(strDestination, strSource);
	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", 0));
	return 0;
}

/*
*  The swprintf_s function formats and stores a series of wide characters and values in buffer. 
*  Each argument (if any) is converted and output according to the corresponding format specification in format. 
*  Returns -1 and upadates -EINVAL on error
*  
*  TODO: Check the format string for valid formatting characters
*  	 In Windows version invalid parameter handler is called on error, and if execution is allowed to continue an error is returned, 
*        in Linux version only error is returned	
*/
int OSAL_swprintf_s(wchar_t * buffer, size_t sizeOfBuffer, const wchar_t * format,
	       ...)
{
	va_list ap;
	int argno = 0;

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (buffer == NULL || format == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer is NULL or format is NULL ret = -1"));
		return -1;
	}
	if (sizeOfBuffer == 0) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer lenght is zeroret = -1"));
		return -1;
	}

	va_start(ap, format);
	argno = vswprintf(buffer, sizeOfBuffer, format, ap);
	va_end(ap);
	if (argno == -1) {
		buffer[0] = L'\0';

		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer is not big enough for format + variable arguments ret = -1"));
		return argno;
	}
	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", argno));
	return argno;
}


/*
*  The OSAL_sprintf_s function formats and stores a series of characters and values in buffer. 
*  Each argument (if any) is converted and output according to the corresponding format specification in format. 
*  The format consists of ordinary characters and has the same form and function as the format argument for printf. 
*  A null character is appended after the last character written. If copying occurs between strings that overlap, 
*  the behavior is undefined.
*
*  One main difference between sprintf_s and sprintf is that sprintf_s checks the format string for valid 
*  formatting characters, whereas sprintf only checks if the format string or buffer are NULL pointers. 
*  If either check fails, the function returns -1 and sets errno to -EINVAL.
*
*  The other main difference between sprintf_s and sprintf is that sprintf_s takes a length parameter 
*  specifying the size of the output buffer in characters. If the buffer is too small for the text being printed 
*  then the buffer is set to an empty string 
*  Unlike snprintf, sprintf_s guarantees that the buffer will be null-terminated (unless the buffer size is zero).
*  
*  Returns -1 and upadates -EINVAL on error
*  
*  TODO: Check the format string for valid formatting characters
*  	 In Windows version invalid parameter handler is called on error, and if execution is allowed to continue an error is returned, 
*        in Linux version only error is returned	
*/
int OSAL_sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format, ...)
{
	va_list ap;
	int argno = 0;
	char tempBuffer[3]={0};

	OSALTRACE(OSAL_DEBUG, ("Enter"));

	if (buffer == NULL || format == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer pointer or Format buffer is NULL ret = -1"));
		return -1;
	}
	if (sizeOfBuffer == 0) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer lenght is zero ret = -1"));
		return -1;
	}

	//wprintf(L" sprintf_s parameters test passed \n");
	va_start(ap, format);
	// vsnprintf returns length of the complete string even though 
	// destination buffer does not have the free space required
	// So get the length of the string to be copied using this

	argno = vsnprintf(tempBuffer, 2, format, ap);

	va_end(ap);

	// vsnprintf returns size of the string without terminating NULL character
	// But Destination buffer should have size including the terminating NULL character
	if ((argno == -1) || ((argno + 1) > sizeOfBuffer)) {
		buffer[0] = '\0';
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error as Dest buffer is not big enough to hold the entire string ret = -1"));
		return -1;
	}

	va_start(ap, format);
	argno = vsnprintf(buffer, sizeOfBuffer, format, ap);
	va_end(ap);

	OSALTRACE(OSAL_DEBUG, ("exit Success return is %d", argno));

	return argno;
}


#if 0 	// Un-used for now

/*
*Converts the string into lower case
*
*Remarks: Won't check the arguments sanity.
*	Calling function should take care
*/
static int wcslower(wchar_t * str)
{
	int strSize;
	strSize = wcslen(str);
	while (strSize) {
		*str = (wchar_t) towlower((wint_t) * str);
		str++;
		strSize--;
	}
	return 0;
}

#endif


/*
* Function name : OSAL_sscanf_s
* Description: 
*	Read formatted data from a string
* Parameters 
*  const char * _Src		:  
*  const char * _Format, ...: 
*  
*  Return Values
*  
*   Known issues:
*		
*	TODO:
*/
int OSAL_sscanf_s(const char *_Src, const char *_Format, ...)
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	va_list ap;
	int argno = 0;

	// validate the argument parameters
	if (_Src == NULL || _Format == NULL) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer is NULL or format is NULL ret = -1"));
		return -1;
	}
	// format the strings
	va_start(ap, _Format);
	// call the proper function 
	argno = vsscanf(_Src, _Format, ap);
	va_end(ap);

	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", argno));
	return argno;
}

/*
* Function name : OSAL_itoa_s
* Description: 
*	Converts an integer to a string
* Parameters 
*  int _Value		:  
*  char * _DstBuf	: 
*  size_t _Size		:
*  int _Radix		:
*
*  Return Values
*  
*   Known issues:
*		
*	TODO:
*/
int OSAL_itoa_s(int _Value, char *_DstBuf, size_t _Size, int _Radix)
{
	OSALTRACE(OSAL_DEBUG, ("Enter"));

	int e = 0;

	if (_Radix == 10 && _Value < 0)
		e = xtox_s_1((unsigned long)_Value, _DstBuf, _Size, _Radix, 1);
	else
		e = xtox_s_1((unsigned long)(unsigned int)_Value, _DstBuf,
			     _Size, _Radix, 0);

	OSALTRACE(OSAL_DEBUG, ("Exit Success return is %d", e));
	return e;

}

int xtox_s_1(unsigned long val,
	     char *buf, size_t sizeInTChars, unsigned radix, int is_neg)
{
	char *p;		/* pointer to traverse string */
	char *firstdig;		/* pointer to first digit */
	char temp;		/* temp char */
	unsigned digval;	/* value of digit */
	size_t length;		/* current length of the string */

	OSALTRACE(OSAL_DEBUG, ("Enter"));
	// validate the argument parameters
	/* validation section */
	if (buf == NULL || sizeInTChars <= 0) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error Dest buffer is NULL or format is NULL or size is 0 or less ret = -1"));
		return -1;
	}
	if (sizeInTChars <= (size_t) (is_neg ? 2 : 1)) {
		errno = -ERANGE;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error could not find the sign ret = -1"));
		return -1;
	}
	if (2 > radix || radix > 36) {
		errno = -EINVAL;
		OSALTRACE(OSAL_ERROR,
			  ("Exit Error could not find the sign ret = -1"));
		return -1;
	}

	memset(buf, 0, sizeInTChars);
	length = 0;

	p = buf;

	if (is_neg) {
		/* negative, so output '-' and negate */
		*p++ = '-';
		length++;
		val = (unsigned long)(-(long)val);
	}

	firstdig = p;		/* save pointer to first digit */

	do {
		digval = (unsigned)(val % radix);
		val /= radix;	/* get next digit */

		/* convert to ascii and store */
		if (digval > 9)
			*p++ = (TCHAR) (digval - 10 + 'a');	/* a letter */
		else
			*p++ = (TCHAR) (digval + '0');	/* a digit */
		length++;
	} while (val > 0 && length < sizeInTChars);

	/* Check for buffer overrun */
	if (length >= sizeInTChars) {
		buf[0] = '\0';
		if (length >= sizeInTChars) {
			errno = -EINVAL;
			OSALTRACE(OSAL_ERROR,
				  ("Exit Error out of range ret = -1"));
			return -1;
		}
	}
	/* We now have the digit of the number in the buffer, but in reverse
	   order.  Thus we reverse them now. */

	*p-- = '\0';		/* terminate string; p points to last digit */

	do {
		temp = *p;
		*p = *firstdig;
		*firstdig = temp;	/* swap *p and *firstdig */
		--p;
		++firstdig;	/* advance to next two digits */
	} while (firstdig < p);	/* repeat until halfway */

	return 0;
}
char *OSAL_strtok_s(char *strToken, const char *strDelimit, char **context)
{
	if ((strToken == NULL) && (*context == NULL)) {
		OSALTRACE(OSAL_ERROR,
		          ("Exit Error strToken and context are NULL  ret = NULL"));
		errno = -EINVAL;
		return NULL;
	}
	if ((strDelimit == NULL) || (context == NULL)) {
	        OSALTRACE(OSAL_ERROR,
		          ("Exit Error Delimit is Null or context is NULL  ret = NULL"));
		errno = -EINVAL;
		return NULL;
	}
	OSALTRACE(OSAL_DEBUG, ("Exit Success return the string"));
	return strtok_r(strToken, strDelimit, context);
}

/*
* Returns Zero on error
* Limitations : This function should result in size of destination widechar string if
* cchWideChar is zero, This functionality is yet to be implemented, for now this function
* returns zero.
*               This function only converts multi byte to Wide char
*/
int OSAL_multibytetowidechar(unsigned int codepage,
			UINT32 dwFlags,
			char *lpmultibytestr,
			int cbmultibyte,
			wchar_t * lpwidecharstr, int cchwidechar)
{
	size_t ret;
	mbstate_t mbstate;
	const char *cssrc = lpmultibytestr;

	if (lpmultibytestr == NULL || lpwidecharstr == NULL)
		return 0;

	if (cchwidechar == 0)
		return 0;

	memset((void *)&mbstate, 0, sizeof(mbstate));

	if (cbmultibyte == -1) {
		ret =
		    mbsrtowcs(lpwidecharstr, &cssrc, strlen(lpmultibytestr),
			      &mbstate);
	} else if (cbmultibyte > 0) {
		ret = mbsrtowcs(lpwidecharstr, &cssrc, cbmultibyte, &mbstate);
	} else {
		return 0;
	}

	return ret;
}

int OSAL_strnlen(const char *str, size_t sizeinbytes)
{
	return strnlen(str, sizeinbytes);
}

char *OSAL_strstr(const char *str, const char *search)
{
	return strstr(str, search);
}

int OSAL_wcsnlen(const wchar_t* str, size_t sizeInWchar)
{
	// The real wide char version...
	return wcsnlen(str, sizeInWchar);
}


// Note this is prefixed with CAPI name. It means the actual string passes is a ansi char *
int OSAL_CAPI_wcsnlen(const wchar_t* str, size_t sizeInWchar)
{
	return strnlen((char *)str, sizeInWchar);
}


int OSAL_widechartomultibyte(unsigned int CodePage, UINT32 dwFlags, WCHAR * lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, char * lpDefaultChar, BOOL * lpUsedDefaultChar)
{

	// TODO::OSAL-WORK::ASSUMPTION - Not being used anywhere currently hence not implemented
	//  How is this supposed to be any different from the other two below??

	return 0;	// error - per windows semantics or convention of this method
}



// #############################################################################
//
// IMPORTANT: ASSUMPTION / CONVENTION
//
// These methods are used to convert the strings originating from the device. 

int OSAL_L3L4_MultiByteToWideChar(unsigned int codepage, UINT32 dwFlags, char *lpmultibytestr, int cbmultibyte, WCHAR * lpwidecharstr, int cchwidechar)
{


	// There are no situations or instances needing to convert a string from MBCS to Wide
	// that pass from L4 to L3. 

	// Hence this method will simply return success for now. 
	return cbmultibyte;	// success
}

int OSAL_L3L4_WideCharToMultiByte(unsigned int CodePage, UINT32 dwFlags, WCHAR * lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, char * lpDefaultChar, BOOL * lpUsedDefaultChar)
{


#if 1

	// If there are any issues disable this code and use the workaround implementation below.

	short *cast_ptr_short = (short *)lpWideCharStr;
	size_t inBytesLeft, outBytesLeft;
	iconv_t cd = (iconv_t)-1;
	int ret = -1;
	char *inBuf, *outBuf;


	OSALTRACE(OSAL_ERROR, ("cchWideChar: %d, cbMultiByte: %d", cchWideChar, cbMultiByte));

	if ( (lpWideCharStr == NULL) || (cchWideChar == 0) || 
		(lpMultiByteStr == NULL)  )
		return 0;		// Not sure if this is the right way to indicate error here. 
	
	// There are instances where we are passed with unknown input string length and are
	// expected to deduce it as a null terminated string...
	if ( cchWideChar == -1 )
	{
		cchWideChar = 0;
		while ( cast_ptr_short[cchWideChar] != (short)0 ) 
			cchWideChar++;
			
		cchWideChar++;
	}

	if ( cbMultiByte < cchWideChar )
		return (cchWideChar);

	if ( (cd = iconv_open("UTF-8", "UTF-16")) == (iconv_t)-1 )
		return -1;

	inBytesLeft = cchWideChar * 2;

	outBytesLeft = cchWideChar;

	// reset the output buffer as precaution...
	// memset(lpMultiByteStr, 0, cbMultiByte);

	inBuf = (char *)lpWideCharStr;
	outBuf = (char *)lpMultiByteStr;

	if ( (ret = iconv(cd, (char **)&inBuf, &inBytesLeft, (char **)&outBuf, &outBytesLeft) ) == -1)
	{
		OSALTRACE(OSAL_ERROR, ("iconv failed. errno: %d ", errno));
		goto exit;
	}


	ret = cchWideChar;


	//lpMultiByteStr[ret] = '\0';

	OSALTRACE(OSAL_ERROR, ("Updated cchWideChar: %d, converted %d chars, Output string: %s", cchWideChar, ret, lpMultiByteStr));
exit:
	if ( cd != (iconv_t)-1 )
		iconv_close(cd);	


	return ret;
#else

	// Used for converting the special 'UTF-16" wide char string to multibyte utf-8 that originate from the device 
	// like the device details of version strings etc. 

	BOOL bNoLenCheck = FALSE;
	char *cast_ptr_widestring = (char *)lpWideCharStr;
	short *cast_ptr_short = (short *)lpWideCharStr;
	
	if ( cbMultiByte < cchWideChar )
		return (cchWideChar / 2);

	if ( lpMultiByteStr == NULL )
		return 0;

	if ( cchWideChar == -1 )
		bNoLenCheck = TRUE;

	// @@@ : JSS : Quick and dirty implementation (assumes the wide char to be english string info)
	int nameLength = 0;
	while ( ( !bNoLenCheck && (nameLength < cchWideChar) ) ||
			( cast_ptr_short[nameLength] != (short)0 ) )
	{
		lpMultiByteStr[nameLength]=cast_ptr_widestring[nameLength*2];
		nameLength++;
	}

	lpMultiByteStr[nameLength] = '\0';

	return nameLength;	// success

#endif // 1/0

}



// #############################################################################
//
// IMPORTANT: ASSUMPTION / CONVENTION
//
// These methods are used from within the CommonAPI layer.
// On Linux the Commmon API will expose UTF-8 encoded strings. Rest of the stack will internally process all strings in UTF-8 format. 
// 
// So these method implementation on Linux are supposed to be dummy - they will be copying the input string as is to the output string

int OSAL_CAPI_MultiByteToWideChar(unsigned int codepage, UINT32 dwFlags, char *lpmultibytestr, int cbmultibyte, WCHAR * lpwidecharstr, int cchwidechar)
{
	if ( (cchwidechar == 0) || (cbmultibyte > cchwidechar) )
	{
		// size of output buffer requested
		return cbmultibyte;
	}

	if (lpwidecharstr == NULL )
		return 0;	// error
	
	memset(lpwidecharstr, 0, cchwidechar);

	memcpy(	lpwidecharstr, lpmultibytestr, cbmultibyte);

	return cbmultibyte;	// success


}

int OSAL_CAPI_WideCharToMultiByte(unsigned int CodePage, UINT32 dwFlags, WCHAR * lpWideCharStr, int cchWideChar, char * lpMultiByteStr, int cbMultiByte, char * lpDefaultChar, BOOL * lpUsedDefaultChar)
{

	if ( (cbMultiByte == 0) || (cbMultiByte < cchWideChar) )
	{
		// size of output buffer requested
		return cchWideChar;
	}

	if ( (lpMultiByteStr == NULL) || (lpWideCharStr == NULL) )
		return 0;	// error


	if (cchWideChar == -1)
	{
		// In this case we obtain the actual length of the incoming wide string
		cchWideChar = (int)strlen((char *)lpWideCharStr);

		if ( cbMultiByte < cchWideChar )
			return cchWideChar;
	}

	memset(lpMultiByteStr, 0, cbMultiByte);
	memcpy(	lpMultiByteStr, lpWideCharStr, cchWideChar);

	return cchWideChar;	// success

}

int OSAL_fprintf(FILE *stream, const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = fprintf(stream, format, ap); 
	va_end(ap);

	return ret;
}

int OSAL_sprintf(char *str, const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = sprintf(str, format, ap); 
	va_end(ap);

	return ret;
}

int OSAL_MyPrintf( const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = vfprintf(stdout, format, ap); 
	va_end(ap);

	return ret;
}

int OSAL_wmemcpy_s(wchar_t *dest, size_t sizeInWords, const wchar_t *src, size_t count)
{
	// TODO::OSAL-WORK::IMPORTANT BUT NON-CRITICAL - OSAL_wmemcpy_s - Assumption here (revisit please)

	if ( (count == 0) || (sizeInWords == 0) || (dest == NULL) || ( src == NULL) )
		return 0;	// dont know whats return supposed to be

	if ( sizeInWords < count )
		return 0;	// dont copy

	memcpy(dest, src, count);
	return count;
}


int OSAL_CAPI_wmemcpy_s(OSAL_WIMAX_API_WSTRING dest, size_t sizeInWords, const OSAL_WIMAX_API_WSTRING src, size_t count)
{
	// TODO::OSAL-WORK::Note the OSAL_CAPI_wmemcpy_s here (revisit please)

	if ( (count == 0) || (sizeInWords == 0) || (dest == NULL) || ( src == NULL) )
		return 0;	// dont know whats return supposed to be

	if ( sizeInWords < count )
		return 0;	// dont copy

	memcpy(dest, src, count);
	return count;
}
// TODO::OSAL-WORK::IMPORTANT - OSAL_wcscmp, OSAL_wcslen - What happens when these methods are fed with ansi strings???

int OSAL_wcscmp(OSAL_WIMAX_API_WSTRING string1, OSAL_WIMAX_API_WSTRING string2)
{
#ifdef NATIVE_LINUX
	return strcmp(string1, string2);
#else
	return wcscmp(string1, string2);
#endif
}


int OSAL_wcslen(const wchar_t *string)
{
	return wcslen(string);
}

int OSAL_CAPI_wcslen(const wchar_t *string)
{
	// IMPORTANT - ASSUMPTION :: The actual incoming string is a simple ascii string
	return strlen((char *)string);
}


int OSAL_CAPI_strcpy_s(OSAL_WIMAX_API_WSTRING strDestination, size_t sizeInWords, const OSAL_WIMAX_API_WSTRING strSource)
{

	// Since the actual argument type is plain char* we can reuse the non CAPI version of the implementation 

	return OSAL_strcpy_s( (char *)strDestination, sizeInWords, (char *)strSource);
}

int OSAL_CAPI_strncmp(const char* str1, const char* str2, size_t maxCount)
{
	return strncmp(str1, str2, maxCount);
}


#else // WIMAX_SYS_WINDOWS

#endif

