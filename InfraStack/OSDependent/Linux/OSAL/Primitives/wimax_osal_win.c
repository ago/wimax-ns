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

/*
 *
 * File: wimax_osal_win.c
 *
 * Desc: Contains implementations of the core/base type methods.
 *
 * Implemented API methods:
 *	- GetLastError
 *	- SetLastError
 *      - GetCurrentProcessId
 *      - CreateDirectory
 *      - GetCommandLine
 *	- CompareFileTime
 *
 * OUTSTANDING OPENS:
 *
 * ASSUMPTIONS / NOTES:
 */

#include <pthread.h>

// This define is required for sem_timedwait implementation.
#define _XOPEN_SOURCE 600
#include <semaphore.h>

#include <stdlib.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <wchar.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

//#include "windows_consts.h"
#include "wimax_osal_types.h"

#include "wimax_osal_trace.h"

#define TIMEVAL_TO_TIMESPEC(tv, ts)	{	\
	(ts)->tv_sec = (tv)->tv_sec;	\
	(ts)->tv_nsec = (tv)->tv_usec * 1000; 	\
}



void SetLastError(UINT32 errCode);


/*******************************************************************************
 *
 * We need to keep this API even if we remove OSAL
 *
 *******************************************************************************/
pthread_key_t LASTERROR_THREAD_KEY;
void InitLastErrorThreadKey()
{
	static int gLastErrorThreadKeyInited = 0;
	int ret;

	int oldErrno;		// preserve the errno in case it gets disturbed with the system calls below
	if (gLastErrorThreadKeyInited == 0) {
		// important to do this here so errno dont get changed by the api calls below
		oldErrno = errno;

		// It is safe to create the key here bcoz it will only be created in context of the main thread.  
		// Bcoz we control when other threads get created and we have this code there as well
		if ((ret =
		     pthread_key_create(&LASTERROR_THREAD_KEY, NULL)) == 0) {
			pthread_setspecific(LASTERROR_THREAD_KEY, (void *)0);
			gLastErrorThreadKeyInited = 1;
		} else
			OSALTRACE(OSAL_ERROR,
				  ("Failed to allocate thread key. ret: %d",
				   ret));

		errno = oldErrno;
	}
}

UINT32 GetLastError(void)
{

	UINT32 retVal;

	InitLastErrorThreadKey();
	retVal = (UINT32) (size_t) pthread_getspecific(LASTERROR_THREAD_KEY);

	return retVal;
}

void SetLastError(UINT32 errCode)
{
	InitLastErrorThreadKey();
	pthread_setspecific(LASTERROR_THREAD_KEY, (void *) (size_t) errCode);
}


// ###################### Dummy definitions of some Win APIs referred in rest of code ############

// These exist just to keep the compiler happy - hopefully references to these get replaced
// with their OSAL equivalents.

#if 0
 
void LocalFree(void *ptr)
{

}


void ReleaseMutex(OSAL_mutex_t mtx)
{

}

BOOL ResetEvent(OSAL_event_t evt)
{
	return FALSE;
}

int sprintf_s(char *str, int size, const char *fmt, ...)
{
	return 0;
}

int sscanf_s(char *str, const char *fmr, ...)
{

	return 0;
}


void _itoa_s(int num, char *buff, int size, int radix)
{

}

int _stricmp(const char *a, const char *b)
{
	return -1;
}

char *strtok_s(char * a, char *b, char **context)
{
	return NULL;
}

int _strcmpi(char *a, char *b)
{
	return -1;
}

FILE *_fsopen(char *file, char* mode, int share)
{
	return NULL;
}

int WaitForSingleObject(OSAL_event_t evt, int timeout)
{
	return -1;
}

void SetEvent(OSAL_event_t evt)
{

}

void *CreateMutex(void * lpSec, BOOL initialState, const char *name)
{
	return NULL;
}

#endif //0 
