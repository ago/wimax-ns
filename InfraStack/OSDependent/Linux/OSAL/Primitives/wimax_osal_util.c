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

#define __USE_UNIX98
#define _XOPEN_SOURCE 600
#define __USE_GNU 		// for timedjoin and tryjoin thread functions.


#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>		/* open */
#include <sys/time.h>
#include <sys/stat.h>	/* mkdir;stat */
#include <sys/types.h>	/* mkdir;stat */
#include <unistd.h>		/* stat */

#include "wimax_osal_trace.h"

#else 

#endif 


#include "wimax_osal_primitives.h"

#include "windows_error.h"
#include "wimax_consts.h"
// Mutex to implemented InterlockedXXX APIs
static pthread_mutex_t gInterlockedMtx;

////////////////////////////////////////////////////////////////////////////////////////////////
//
// Utility method for multiple objects wait method
//


UINT32 OSAL_generic_multiple_wait(int nMutexes,
			     const OSAL_mutex_t mutexes[],
				int nEvents, 
				const OSAL_event_t events[],
			     int bWaitAll, unsigned int dwMilliSeconds)
{
#if !defined(WIMAX_SYS_WINDOWS)

	int nCount = nMutexes + nEvents;

	OSALTRACE(OSAL_DEBUG,
		  ("enter with timeout of %u, #handles as %d", dwMilliSeconds,
		   nCount));
	if ((nCount == 0) || (mutexes == NULL) || (events == NULL) ) {
		OSALTRACE(OSAL_WARNING, ("exit - invalid input"));
		return WMX_EINVAL;
	}

	UINT32 iterationCount;
	UINT32 iterator = 0;
	BOOL bDone = FALSE;
	UINT32 dwRetVal = WAIT_FAILED;
	struct timespec delay;
	UINT32 i, j;
	BOOL *pbWaitResult = NULL;
	UINT32 dwSuccessfulWait = 0;
	BOOL bAbandoned = FALSE;
	struct timeval tv_before, tv_after;

#define		DELAY_PER_OBJECT_WAIT	5000

	if (dwMilliSeconds == 0)
		iterationCount = 1;
	else
		iterationCount = dwMilliSeconds;

	// adjust the delay depending on the # of objects to wait upon. 
	// Documentation claims nanosleep's granularity to be 10ms so in case the wait is less we simply dont invoke it. 
	// Bcoz apparently, even with 0 sleep time nanosleep will not return for 7-8ms
	delay.tv_sec = 0;

//      if (dwMilliSeconds > 10 )
//              delay.tv_nsec = (1000000 * 10); // 10 ms
//      else
	delay.tv_nsec = 1000 * 1000;	// 1ms

	delay.tv_nsec -= (nCount * DELAY_PER_OBJECT_WAIT);	// Some fixed amt - delay per object

	pbWaitResult = (BOOL *) calloc(nCount, sizeof(BOOL));

	if (pbWaitResult == NULL) {
		SetLastError(ERROR_NOT_ENOUGH_MEMORY);
		OSALTRACE(OSAL_ERROR, ("Allocation failure"));
		return WAIT_FAILED;
	}

	do {
		gettimeofday(&tv_before, NULL);

		for (i = 0;
		     (i < nMutexes) && !bDone && (dwSuccessfulWait < nCount);
		     i++) {
			if (!pbWaitResult[i]) {
				dwRetVal = OSAL_trylock_mutex(mutexes[i]);	//do a peek on the objecto

				//      OSALTRACE(OSAL_DEBUG, ("WaitObject(%d) returned %u during iteration %d", i, dwRetVal, iterator))

				if ((dwRetVal == 0)
				    || (dwRetVal == WAIT_ABANDONED_0))
					if (!bWaitAll) {
						bDone = TRUE;
						dwRetVal += i;
					} else {
						pbWaitResult[i] = TRUE;
						dwSuccessfulWait++;

						bAbandoned =
						    (dwRetVal ==
						     WAIT_ABANDONED_0);

						// Increment the wait delay.
						delay.tv_nsec +=
						    DELAY_PER_OBJECT_WAIT;
				} else if (dwRetVal == (UINT32)-1) {
					bDone = TRUE;
					OSALTRACE(OSAL_WARNING,
						  ("Wait failed on handle # %d",
						   i));
				}
			}
		}

		for (j = 0;
		     (j < nEvents) && !bDone && (dwSuccessfulWait < nCount);
		     j++) {
			if (!pbWaitResult[j + nMutexes]) {
				dwRetVal = OSAL_wait_event(events[j], 0);	//do a peek on the objecto

				//      OSALTRACE(OSAL_DEBUG, ("WaitObject(%d) returned %u during iteration %d", i, dwRetVal, iterator))

				if ((dwRetVal == 0)
				    || (dwRetVal == WAIT_ABANDONED_0))
					if (!bWaitAll) {
						bDone = TRUE;
						dwRetVal += j + nMutexes;
					} else {
						pbWaitResult[j + nMutexes] = TRUE;
						dwSuccessfulWait++;

						bAbandoned =
						    (dwRetVal ==
						     WAIT_ABANDONED_0);

						// Increment the wait delay.
						delay.tv_nsec +=
						    DELAY_PER_OBJECT_WAIT;
				} else if (dwRetVal == WMX_EINVAL) {
					bDone = TRUE;
					OSALTRACE(OSAL_WARNING,
						  ("Wait failed on handle # %d",
						   j));
				}
			}
		}

		if (dwSuccessfulWait == nCount)
			bDone = TRUE;

		if (!bDone) {
			//      if ( dwMilliSeconds > 10 )
			nanosleep(&delay, NULL);
			iterator++;
		}

		gettimeofday(&tv_after, NULL);

		OSALTRACE(OSAL_DEBUG,
			  ("time taken in micro-seconds: %u, objects waited upon: %d, sleep delay (n-sec): %u",
			   (unsigned)(tv_after.tv_usec - tv_before.tv_usec),
			   nCount - dwSuccessfulWait, delay.tv_nsec));
	}
	while (!bDone && (iterator < iterationCount));

	OSALTRACE(OSAL_DEBUG, ("Iterated %u times", iterator));

	if (!bDone)
	{
		if (bWaitAll && (dwSuccessfulWait == nCount))
		{
			dwRetVal =
			    bAbandoned ? WAIT_ABANDONED_0 : WAIT_OBJECT_0;
		}
		else
			dwRetVal = WAIT_TIMEOUT;
	}

	if (pbWaitResult != NULL)
		free(pbWaitResult);

	OSALTRACE(OSAL_DEBUG, ("exiting - return %u", dwRetVal));
	return dwRetVal;

#else

	// todo
#endif


}


// -------------- Interlocked set of APIs ------------------

// There has been references to __compare_and_swap primitive on the net which could
// have been useful. However it dont seem to be part of mainstream libc/gcc tools. 
// Hence using an explicit mutex based implementation.

// It is safe to use a static global here since this method will ONLY be called in context 
// of the main thread. 
// It is called either from one of the InterlockedXXX methods or from _beginthreadex | CreateThread
// which will always be from the main thread.
int InitInterlockedMutex(void)
{

#if !defined(WIMAX_SYS_WINDOWS)

	static int b_gInterlockedMtxInited = 0;
	int ret;

	pthread_mutexattr_t mtxAttr;
	if (b_gInterlockedMtxInited == 0) {
		if ((ret = pthread_mutexattr_init(&mtxAttr)) == 0) {
			// Set type appropriate for windows style semantics for Mutexes
			ret =
			    pthread_mutexattr_settype(&mtxAttr,
						      PTHREAD_MUTEX_RECURSIVE_NP);

			if (ret != 0) {
				OSALTRACE(OSAL_ERROR,
					  ("Failed to set mutex of recursive type. return: %d",
					   ret));
				pthread_mutexattr_destroy(&mtxAttr);
				return -1;
			}

			if ((ret =
			     pthread_mutex_init(&gInterlockedMtx,
						&mtxAttr)) == 0) {
				b_gInterlockedMtxInited = 1;
				pthread_mutexattr_destroy(&mtxAttr);
				return 0;
			}
			else {
				OSALTRACE(OSAL_ERROR,
					  ("Failed to initialize mutex. return: %d",
					   ret));
			pthread_mutexattr_destroy(&mtxAttr);
				return -1;
			}

			
		} else {
			OSALTRACE(OSAL_ERROR,
				  ("Failed to initialize mutex attributes. return: %d",
				   ret));
			return -1;
		}
	}
	return 0;
#else

	// todo
#endif
}

long OSAL_atomic_increment(long volatile *lpAddend)
{
#if !defined(WIMAX_SYS_WINDOWS)

	long retVal;
	int retMtx;

	if (lpAddend == NULL)
		return 0;

	retVal = *lpAddend;

	if (InitInterlockedMutex() < 0) {
		OSALTRACE(OSAL_ERROR,
				  ("Failed to Create mutex"));
		return 0;
	}

	if ((retMtx = pthread_mutex_lock(&gInterlockedMtx)) == 0) {
		(*lpAddend)++;
		retVal = (*lpAddend);
		pthread_mutex_unlock(&gInterlockedMtx);
	} else
		OSALTRACE(OSAL_ERROR,
			  ("Failed to lock mutex. return: %d", retMtx));

	return retVal;
#else

	// todo
#endif
}

long OSAL_atomic_decrement(long volatile *lpAddend)
{
#if !defined(WIMAX_SYS_WINDOWS)

	long retVal;
	int retMtx;

	if (lpAddend == NULL)
		return 0;

	retVal = *lpAddend;

	if (InitInterlockedMutex() < 0) {
		OSALTRACE(OSAL_ERROR,
				  ("Failed to Create mutex"));
		return retVal;
	}

	if ((retMtx = pthread_mutex_lock(&gInterlockedMtx)) == 0) {
		(*lpAddend)--;

		retVal = *lpAddend;

		pthread_mutex_unlock(&gInterlockedMtx);
	} else
		OSALTRACE(OSAL_ERROR,
			  ("Failed to lock mutex. return: %d", retMtx));

	return retVal;
#else

	// todo
#endif

}

long OSAL_atomic_compareExchange(long volatile *lpDest, long exchange,
				long comperand)
{
#if !defined(WIMAX_SYS_WINDOWS)

	long retVal;
	int retMtx;

	if (lpDest == NULL)
		return 0;
	retVal = *lpDest;
	if (InitInterlockedMutex() < 0) {
		OSALTRACE(OSAL_ERROR,
				  ("Failed to Create mutex"));
		return retVal;
	}

	if ((retMtx = pthread_mutex_lock(&gInterlockedMtx)) == 0) {
		retVal = *lpDest;
		if (*lpDest == comperand)
			*lpDest = exchange;

		pthread_mutex_unlock(&gInterlockedMtx);
	} else
		OSALTRACE(OSAL_ERROR,
			  ("Failed to lock mutex. return: %d", retMtx));

	return retVal;
#else

	// todo
#endif
}

long OSAL_atomic_exchange(long volatile *lpTarget, long value)
{

#if !defined(WIMAX_SYS_WINDOWS)

	long retVal;
	int retMtx;

	if (lpTarget == NULL)
		return 0;

	retVal = *lpTarget;

	if (InitInterlockedMutex() < 0) {
		OSALTRACE(OSAL_ERROR,
				  ("Failed to Create mutex"));
		return retVal;
	}

	if ((retMtx = pthread_mutex_lock(&gInterlockedMtx)) == 0) {
		retVal = *lpTarget;
		*lpTarget = value;

		pthread_mutex_unlock(&gInterlockedMtx);
	} else
		OSALTRACE(OSAL_ERROR,
			  ("Failed to lock mutex. return: %d", retMtx));

	return retVal;
#else

	// todo
#endif
}

void* OSAL_atomic_exchangepointer(void* volatile *lpTarget, void* value)
{

#if !defined(WIMAX_SYS_WINDOWS)

	void* retVal;
	int retMtx;

	if (lpTarget == NULL)
		return 0;

	retVal = *lpTarget;

	if (InitInterlockedMutex() < 0) {
		OSALTRACE(OSAL_ERROR,
				  ("Failed to Create mutex"));
		return retVal;
	}

	if ((retMtx = pthread_mutex_lock(&gInterlockedMtx)) == 0) {
		retVal = *lpTarget;
		*lpTarget = value;

		pthread_mutex_unlock(&gInterlockedMtx);
	} else
		OSALTRACE(OSAL_ERROR,
			  ("Failed to lock mutex. return: %d", retMtx));

	return retVal;
#else

	// todo
#endif
}

void* OSAL_atomic_compareexchangepointer(void* volatile *lpDest, void* exchange,
					void* comperand)
{

#if !defined(WIMAX_SYS_WINDOWS)

	void* retVal = NULL;
	int retMtx;

	if (lpDest == NULL)
		return NULL;
	retVal = *lpDest;
	if (InitInterlockedMutex() < 0) {
		OSALTRACE(OSAL_ERROR,
				  ("Failed to Create mutex"));
		return retVal;
	}

	if ((retMtx = pthread_mutex_lock(&gInterlockedMtx)) == 0) {
		retVal = *lpDest;

		if (*lpDest == comperand)
			*lpDest = exchange;

		pthread_mutex_unlock(&gInterlockedMtx);
	} else
		OSALTRACE(OSAL_ERROR,
			  ("Failed to lock mutex. return: %d", retMtx));

	return retVal;
#else

	// todo
#endif
}

// Extract the process' name from proc/<pid>/cmdline
BOOL OSAL_get_processname(char *namebuf, int bufsize, pid_t pid)
{
#if !defined(WIMAX_SYS_WINDOWS)
	char path[32];
	int fd;
	char buffer[512];
	char *curr = 0, *temp = 0;
	int readbyte = 0;
	int copysize;

	snprintf(path, sizeof(path), "/proc/%u/cmdline", pid);

	// open file to read
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return FALSE;

	// Don't need to read entire command line file.
	// only read once (2048) because you can get the application name at first read.
	readbyte = read(fd, buffer, sizeof(buffer) - 1);
	if (readbyte <= 0)
		return FALSE;	// nothing to read or read error

	buffer[readbyte++] = '\0';
	close(fd);

	// remove ./ if any
	curr = strstr(buffer, "./");
	if (curr == NULL) {	// NOT FOUND
		curr = buffer;
	} else {		// FOUND
		curr += 2;
	}

	// some process name has /xxx/yyy/zzz/appname.
	// Find the last occurance of / to get appname only
	temp = strrchr(curr, '/');
	if (temp != NULL) {	// FOUND
		curr = temp + 1;
	}

	if (bufsize <= strlen(curr))
		copysize = bufsize - 1;
	else
		copysize = strlen(curr);

	strncpy(namebuf, curr, copysize + 1);

	return TRUE;
#else

	// todo
#endif
}



UINT32 timeGetTime()
{
	int res;
	struct timeval tv;
	res = gettimeofday(&tv, NULL);
	return (tv.tv_sec*1000);
}

BOOL OSAL_create_directory(char * path_name)
{
#if !defined(WIMAX_SYS_WINDOWS)
	int status;
	if (path_name == NULL) {
		SetLastError(WMX_EINVAL);
		return FALSE;
	}
	// create a directory with default access priviledge (rwxr-xr-x)
	status = mkdir(path_name, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	if (status) {
		if (errno == EEXIST) 
		{
			SetLastError(WMX_EEXIST);
		}
		else if (errno == EACCES) 
		{
			SetLastError(WMX_EACCES);
		}
		else 
		{ // We may need some kind of generic error such as ERROR_UNKNOWN
			SetLastError(WMX_EINVAL);
		}
		return FALSE;
	}

	return TRUE;
#else
	// Windows Implementation here

#endif
}


BOOL OSAL_get_file_stat(const char *file_name, OSAL_file_stat * pfile_stat)
{
	BOOL ret = FALSE;

	if (file_name == NULL || pfile_stat == NULL) {
		return FALSE;
	}

#if !defined(WIMAX_SYS_WINDOWS)
	int fd;
	char * tempFileNameOnly = NULL;
	
	fd = open(file_name, O_RDONLY);
	if (fd != -1) {
		struct stat fileStat;
		memset(pfile_stat, 0, sizeof(OSAL_file_stat));
		
		fstat(fd, &fileStat);
		
		pfile_stat->ftLastAccessTime = fileStat.st_atime;
		pfile_stat->ftLastWriteTime = fileStat.st_mtime;
		pfile_stat->ftCreationTime = fileStat.st_mtime;
		pfile_stat->fileAttributes = fileStat.st_mode;
		tempFileNameOnly = strrchr(file_name, '/');
		tempFileNameOnly++;
		
		strncpy(pfile_stat->cFileName, tempFileNameOnly, strlen(tempFileNameOnly));
		
		close(fd);
		ret = TRUE;
		OSALTRACE(OSAL_DEBUG, ("Found match: %s", file_name));
	}
	return ret;
#else
	// Windows Implementation here

#endif
}

BOOL OSAL_set_file_stat(const char *file_name, OSAL_mode_t fileAttributes)
{
#if !defined(WIMAX_SYS_WINDOWS)
	/* This is blank function to make the compiler happy since we are not using this function */
	return TRUE;
#else
	// Windows Implementation here
#endif
}


long OSAL_compare_filetime(const OSAL_filetime * pfiletime1, const OSAL_filetime * pfiletime2)
{
#if !defined(WIMAX_SYS_WINDOWS)	
	if (pfiletime1 == NULL || pfiletime2 == NULL) 
	{
		OSALTRACE(OSAL_ERROR, ("Exit Error out of range ret = -1"));
		return -5;
	}
    
	if (*pfiletime1 == *pfiletime2)
	{
		return 0;
	}
	else if(*pfiletime1 > *pfiletime2)
	{
		return 1;
	}
	else //if(pfiletime1 < pfiletime2) 
	{
		return -1;
	}
#else
	// Windows Implementation here

#endif	
}

long OSAL_get_file_size(int fd)
{
#if !defined(WIMAX_SYS_WINDOWS)
	if (fd == -1)
	{
		return -1l;
	}
	
	struct stat fileStat;
	if (fstat(fd, &fileStat) != -1) {
		return fileStat.st_size;
	} else {
		return -1l;
	}
#else
	// Windows Implementation here
	return _filelength(gLogFile->_file);
#endif	
}


int OSAL_fopen(FILE** stream, const char *filename, const char *mode, int sharemode)
{
	if ( stream && filename && mode)
	{
		if ( (*stream = fopen(filename, mode)) == NULL )
			return errno;
		return 0;
	}
	return -1;
}


int OSAL_fclose(FILE *stream)
{
	return fclose(stream);
}

int OSAL_fflush(FILE* stream)
{
	return fflush(stream);
}

size_t OSAL_fread(void *buffer, size_t size, size_t count, FILE *stream )
{
	return fread(buffer, size, count, stream);
}

size_t OSAL_fwrite(const void *buffer, size_t size, size_t count, FILE *stream )
{

	return fwrite(buffer, size, count, stream);
}


void OSAL_ZeroMemory(void *buffer, size_t length)
{
	memset(buffer, 0, length);
}

int GetLogPath(char *buffer, int bufferLen)
{
	if ( (buffer == NULL) || (bufferLen == 0) )
		return FALSE;

	if ( bufferLen < strlen(PKG_VAR_LOG_DIR) )
		return FALSE;

	strcpy(buffer, PKG_VAR_LOG_DIR);

	return TRUE;
}

