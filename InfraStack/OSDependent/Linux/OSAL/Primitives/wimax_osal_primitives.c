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
/////////////////////////////////////////////////////////////////////////////////
//
// File: wimax_osal.c
//
// Desc: OS abstraction layer interfaces for use in this wimax user space stack
//
// Defines abstractions for mutexes, critical sections, thread specific storage
// dynamic library functions.
//
// Notes: 
// The provided functions are not perfect generalizations and often do not 
// provide for all possible specializations under a given construct that 
// may be available on a given platform.
// It is rather true that it caters to the specific usage of these servies within
// the wimax user space stack. 
/////////////////////////////////////////////////////////////////////////////////


#if !defined(CONFIGURE_NATIVE_WINDOWS)		// and any other non-linux systems this can get ported to

#define __USE_XOPEN2K		// for timedwait semaphore & timedlock mutex functions
#define __USE_UNIX98
//#define _XOPEN_SOURCE
#define _XOPEN_SOURCE 600
#define __USE_GNU 		// for timedjoin and tryjoin thread functions.


#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "wimax_osal_trace.h"

// Probably a bug in libc6
extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) __THROW;
extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
				 __const struct timespec *__abstime);


#define TIMEVAL_TO_TIMESPEC(tv, ts)	{	\
	(ts)->tv_sec = (tv)->tv_sec;	\
	(ts)->tv_nsec = (tv)->tv_usec * 1000; 	\
}

#else 

#endif 


#include "wimax_osal_primitives.h"

#include "windows_error.h"

int linux_to_wimax_err(int err);
/////////////////////////////////////////////////////////////////////////////////////////////
//
// Thread specific storage area methods....
//
/////////////////////////////////////////////////////////////////////////////////////////////

int OSAL_create_threadkey(OSAL_threadkey_t * pkey)
{
#if !defined(WIMAX_SYS_WINDOWS)

	pthread_key_t tk;
	int ret = -1;

	OSALTRACE(OSAL_DEBUG, ("enter"));

	if (pkey == NULL)
		goto exit;

	if ((ret = pthread_key_create(&tk, NULL)) == 0) {
		*pkey = (OSAL_threadkey_t)tk;
	}
	else
		OSALTRACE(OSAL_ERROR, ("Failed to create thread key. Error  %d", ret));

exit:
	OSALTRACE(OSAL_DEBUG, ("Exiting with return %d", ret));
	return ret;
#else

	// todo
#endif

}

int OSAL_set_threadvalue(OSAL_threadkey_t key, void *value)
{
#if !defined(WIMAX_SYS_WINDOWS)

	int ret = -1;

	OSALTRACE(OSAL_DEBUG, ("enter"));
	ret = pthread_setspecific((pthread_key_t) key, value);

	OSALTRACE(OSAL_DEBUG, ("exiting with return :%d", ret));
	
	return ret;
#else

	// todo
#endif
}

void *OSAL_get_threadvalue(OSAL_threadkey_t key)
{
#if !defined(WIMAX_SYS_WINDOWS)
	return pthread_getspecific((pthread_key_t)key);
#else

	// todo
#endif
}

int OSAL_delete_threadkey(OSAL_threadkey_t key)
{
#ifndef WIMAX_SYS_WINDOWS

	return pthread_key_delete((pthread_key_t)key);
#else

#endif

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// Critical Section methods....
//
/////////////////////////////////////////////////////////////////////////////////////////////

int OSAL_init_critical_section(OSAL_critical_section* pcs)
{

#if !defined(WIMAX_SYS_WINDOWS)

	int ret = -1;
	int attr_inited = 0;
	pthread_mutexattr_t mtxAttr;

	OSALTRACE(OSAL_DEBUG, ("enter."));

	if ( pcs == NULL)
		goto exit;

	*pcs = NULL; 

	if ((ret = pthread_mutexattr_init(&mtxAttr)) != 0) {
		goto exit;
	}
	
	attr_inited = 1;

	pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_RECURSIVE_NP);

	*pcs = calloc(1, sizeof(pthread_mutex_t));

	if ( *pcs == NULL )
		goto exit;

	ret = pthread_mutex_init((pthread_mutex_t *)*pcs, &mtxAttr);


exit:
	if ( attr_inited )
		pthread_mutexattr_destroy(&mtxAttr);

	if ( ret != 0 )
		if ( *pcs != NULL ) 
			free(*pcs);
	return ret;

#else

	// todo
#endif

}

int OSAL_enter_critical_section(OSAL_critical_section *pcs)
{
#if !defined (WIMAX_SYS_WINDOWS) 
	if ( (pcs != NULL) && (*pcs != NULL) )
		return pthread_mutex_lock((pthread_mutex_t *) *pcs);
	else
	{
		OSALTRACE(OSAL_ERROR,("Pointer is NULL. return -1"));	
		return -1;
	}

#else
	// todo
#endif // 

}

int OSAL_exit_critical_section(OSAL_critical_section *pcs)
{
#if !defined (WIMAX_SYS_WINDOWS)
	if ( (pcs != NULL) && (*pcs != NULL) )
		return pthread_mutex_unlock((pthread_mutex_t *) *pcs);
	else
	{
		OSALTRACE(OSAL_ERROR,("Pointer is NULL. return -1"));	
		return -1;
	}
#else

#endif

}

int OSAL_delete_critical_section(OSAL_critical_section *pcs)
{
#if !defined (WIMAX_SYS_WINDOWS)
	int ret = -1;

	if ( (pcs != NULL) && (*pcs != NULL) )
	{
		ret = pthread_mutex_destroy((pthread_mutex_t *) *pcs);
		free(*pcs);
	}
	
	return ret;
#else

#endif

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// Mutex methods....
//
/////////////////////////////////////////////////////////////////////////////////////////////


// structure holding the actual mutex implementation details...

struct mutex_internal
{
	pthread_mutex_t mtx;
	char *name;
	sem_t * named_mtx;

};

static int OSAL_create_named_mutex(OSAL_mutex_t* pmtx, int owned, char *name);

int OSAL_create_mutex(OSAL_mutex_t *pmtx, int owned, char * name)
{

#ifndef WIMAX_SYS_WINDOWS 
	int ret = -1;
	pthread_mutexattr_t mtxAttr;
	pthread_mutex_t mtx;
	int b_attr_inited = 0;

	//int oflag = O_CREAT;		// create if not existent else open it.
	//mode_t mode = S_IRWXU;		// read, write, execute

	struct mutex_internal *p_int_mtx = NULL;

	OSALTRACE(OSAL_DEBUG, ("enter. owned: %d", owned));

	if ( pmtx == NULL )
		goto exit;

	if (name != NULL)
		return OSAL_create_named_mutex(pmtx, owned, name);


	if ((ret = pthread_mutexattr_init(&mtxAttr)) != 0) {
		OSALTRACE(OSAL_ERROR,
			  ("exit - mutexattr_init failed. return: %d", ret));
		goto exit;
	}

	b_attr_inited = 1;

	// Set type appropriate for windows style semantics for Mutexes
	pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_RECURSIVE_NP);

	if ((ret = pthread_mutex_init(&mtx, &mtxAttr)) != 0) {

		OSALTRACE(OSAL_ERROR,
			  ("exit - failure. mutex_init return code: %d", ret));
		goto exit;
	}


	if ( owned )
		pthread_mutex_lock(&mtx);

	// Mutex type is a complex structure and needs to be handled like this.
	// We will allocate it and hang on to the ptr
	p_int_mtx = (struct mutex_internal *)calloc(1, sizeof(struct mutex_internal));
	if (p_int_mtx != NULL)
	{
		p_int_mtx->mtx = mtx;
	}
	else
	{
		// error return...
		pthread_mutex_destroy(&mtx);
		OSALTRACE(OSAL_ERROR, ("exit - failure. mem alloc failed"));

		// TODO :: set the errno correctly to reflect out of memory condition
		ret = -1;
	}

	*pmtx = (void *)p_int_mtx;

exit:
	if ( b_attr_inited )
		pthread_mutexattr_destroy(&mtxAttr);
		
	return ret;
#else

#endif
}

// #############################

static int OSAL_create_named_mutex(OSAL_mutex_t* pmtx, int owned, char *name)
{

	// We create a named semaphore since Linux do not have named mutexes.

	sem_t *semForNamedMtx = NULL;
	int oflag = O_CREAT;		// create if not existent else open it.
	mode_t mode = S_IRWXU;		// read, write, execute

	int initValue =  1;
	struct mutex_internal* p_int_mtx = NULL;

	int ret = -1;

	if ( (pmtx == NULL) || (name == NULL) )
		goto exit;

	semForNamedMtx = sem_open(name, oflag, mode, initValue);

	if ( semForNamedMtx == SEM_FAILED )
	{
		OSALTRACE( OSAL_ERROR, ("failed to create/open named semaphore. errno: %d", errno));
		goto exit;
	}

	if ( owned == TRUE )
		sem_wait(semForNamedMtx);

	initValue = -1;

	sem_getvalue(semForNamedMtx, &initValue);

	OSALTRACE( OSAL_DEBUG, ("Value on named semaphore %s is %d. Handle: %p\n", name, initValue, semForNamedMtx));

	p_int_mtx  = (struct mutex_internal *)calloc(1, sizeof(struct mutex_internal));
	if ( p_int_mtx == NULL )
		goto exit;
	
	p_int_mtx->name = strdup(name);
	if ( p_int_mtx->name == NULL )
	{
		// failed...
		ret = -1;
		goto exit;
	}
	p_int_mtx->named_mtx = semForNamedMtx;

	*pmtx = (void *)p_int_mtx;

	OSALTRACE( OSAL_DEBUG, ("Successfully opened/created named mutex: %s", name));

	ret = 0;
	
exit:

	if ( ret != 0 )
	{

		if ( semForNamedMtx != SEM_FAILED ) 
		{
			if ( owned == TRUE )
				sem_post(semForNamedMtx);
 
			sem_close(semForNamedMtx);
		}
			
		if ( p_int_mtx != NULL )
		{
			if ( p_int_mtx->name != NULL )
				free(p_int_mtx->name);
			free(p_int_mtx);	
		}
	}
	return ret;
}

// ############################



int OSAL_lock_mutex(OSAL_mutex_t mtx)
{
#ifndef WIMAX_SYS_WINDOWS

	int ret = -1;
	struct mutex_internal *p_int_mtx = (struct mutex_internal *) mtx;

	if ( mtx == NULL )
		goto exit;

	if ( p_int_mtx->name == NULL )
	{
		// un-named mutex...
		ret = pthread_mutex_lock( &(p_int_mtx->mtx) );
	}
	else
	{
		ret = sem_wait( p_int_mtx->named_mtx);
	}	
	if ( ret != 0 )
		ret = linux_to_wimax_err(errno);	
	
exit:

	return ret;
#else

#endif

}

int OSAL_trylock_mutex(OSAL_mutex_t mtx)
{
#ifndef _WIMAX_SYS_WINDOWS

	int ret = -1;
	struct mutex_internal *p_int_mtx = (struct mutex_internal *) mtx;

	if ( mtx == NULL )
		goto exit;

	if ( p_int_mtx->name == NULL )
	{
		ret = pthread_mutex_trylock( &(p_int_mtx->mtx) );
	}
	else
	{
		ret = sem_trywait( p_int_mtx->named_mtx );
	}

	if ( ret != 0 )
		ret = linux_to_wimax_err(errno);	

exit:
	return ret;
#else

#endif

}

int OSAL_timedlock_mutex(OSAL_mutex_t mtx, unsigned int milliseconds)
{
#ifndef WIMAX_SYS_WINDOWS
	struct timespec ts;
	struct timeval tv;
	int ret = -1;
	struct mutex_internal *p_int_mtx = (struct mutex_internal *) mtx;

	if ( mtx == NULL )
		goto exit;

	gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, &ts);

	// Split the incoming millisecs into seconds and nano-seconds struct as required by the timedjoin method

	ts.tv_sec += (milliseconds / 1000);
	ts.tv_nsec += ((milliseconds % 1000) * 1000 * 1000);	// 1 ms = 1000000 ns
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		++ts.tv_sec;
	}

	if ( p_int_mtx->name == NULL )
	{
		ret =  pthread_mutex_timedlock( &(p_int_mtx->mtx), &ts);
	}
	else
	{
		ret = sem_timedwait( p_int_mtx->named_mtx, &ts);
	}

	if ( ret != 0)
	{
		ret = linux_to_wimax_err(errno);	
		OSALTRACE(OSAL_DEBUG, ("Timed wait failed on mutex. error: %d", errno)); 
	}

exit:
	return ret;
#else

#endif
}


int OSAL_unlock_mutex(OSAL_mutex_t mtx)
{
#ifndef WIMAX_SYS_WINDOWS

	int ret = -1;
	struct mutex_internal *p_int_mtx = (struct mutex_internal *) mtx;

	if ( mtx == NULL )
		goto exit;
	
	if ( p_int_mtx->name == NULL )
	{
		ret = pthread_mutex_unlock( &(p_int_mtx->mtx) );
	}
	else
	{
		ret = sem_post(p_int_mtx->named_mtx);
	}

	if ( ret != 0 )
		OSALTRACE( OSAL_ERROR, ("Failed to release mutex. error: %d", errno));


exit:
	return ret;

#else

#endif

}

int OSAL_delete_mutex(OSAL_mutex_t mtx)
{
#ifndef WIMAX_SYS_WINDOWS

	int ret = -1; 
	struct mutex_internal *p_int_mtx = (struct mutex_internal *) mtx;

	if (mtx == NULL)
		goto exit;

	if ( p_int_mtx->name == NULL )
	{
		ret = pthread_mutex_destroy( &p_int_mtx->mtx );
	}
	else
	{
		ret = sem_close( p_int_mtx->named_mtx );
		free(p_int_mtx->name);
	}

	if ( ret != 0 )
		OSALTRACE(OSAL_ERROR, ("Failed to close/delete the mutex. Error: %d", errno));
		
	free(mtx);

exit:
	return ret;

#else
	// todo
#endif

}


/////////////////////////////////////////////////////////////////////////////////////////////
//
// Thread methods....
//
/////////////////////////////////////////////////////////////////////////////////////////////

// Note -
// this implementation presently do not support ability to change the thread creation 
// process in many ways
int OSAL_create_thread(OSAL_thread_func tf, void *arg, OSAL_thread_t *p_thread_id)
{
#ifndef WIMAX_SYS_WINDOWS
	if ( tf == NULL )
		return -1; 		// worry about errno later.

	pthread_t tid;

	int ret = pthread_create(&tid, NULL, (OSAL_linux_thread_func)tf, arg);


	if ( ret == 0 )
	{ 
		if ( p_thread_id != NULL )
			*p_thread_id = (OSAL_thread_t)tid;
	}
	else
	{
		OSALTRACE(OSAL_ERROR, ("Failed to create thread. ret: %d err: %d", ret, errno));
	}

	return ret;
#else
	// Windows and other implementations will come here. 
#endif
}

void OSAL_exit_thread(void *retval)
{
#ifndef WIMAX_SYS_WINDOWS

	pthread_exit(retval);

#else

#endif
}

int OSAL_kill_thread(OSAL_thread_t thread_id)
{
#ifndef WIMAX_SYS_WINDOWS
	
	if ( thread_id == 0 )
		return EINVAL;


	return pthread_cancel((pthread_t)thread_id);
#else

#endif

}

int OSAL_join_thread(OSAL_thread_t thread_id, void **status)
{

#ifndef WIMAX_SYS_WINDOWS

	int ret = pthread_join((pthread_t)thread_id, status);

	if ( ret == -1)
		OSALTRACE(OSAL_ERROR, ("thread join failed. err: %d", errno));

	return ret;
#else

#endif
}

int OSAL_timedjoin_thread(OSAL_thread_t thread_id, unsigned int milliseconds, void **status)
{
#ifndef WIMAX_SYS_WINDOWS

	struct timespec ts;
	struct timeval tv;
	int ret;

	if ( thread_id == 0 )
		return EINVAL;
	
	gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, &ts);

	// Split the incoming millisecs into seconds and nano-seconds struct as required by the timedjoin method

	ts.tv_sec += (milliseconds / 1000);
	ts.tv_nsec += ((milliseconds % 1000) * 1000 * 1000);	// 1 ms = 1000000 ns
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_nsec -= 1000000000;
		++ts.tv_sec;
	}

	ret = pthread_timedjoin_np((pthread_t)thread_id, status, &ts);
	
	if ( ret != 0 )
	{
		OSALTRACE(OSAL_ERROR, ("thread join failed. err: %d", errno));

		switch (errno)
		{

			case ETIMEDOUT: 
				ret = WAIT_TIMEOUT;
				break;
			case EINVAL:
			case ESRCH:
				ret = WAIT_FAILED;
				break;
		}
	}
	return ret;
#else

#endif

}

int OSAL_tryjoin_thread(OSAL_thread_t thread_id, void **status)
{
#ifndef WIMAX_SYS_WINDOWS

	int ret = pthread_tryjoin_np((pthread_t)thread_id, status);

	if ( ret != 0 )
		OSALTRACE(OSAL_ERROR, ("thread try join failed. err: %d", errno));

	return ret;
#else

#endif
}

void OSAL_sleep(unsigned int milliSecs)
{
#ifndef WIMAX_SYS_WINDOWS
	struct timespec delay;

	delay.tv_sec = milliSecs / 1000;

	delay.tv_nsec = (milliSecs % 1000) * 1000 * 1000;

	if (delay.tv_nsec >= 1000000000) {
		delay.tv_nsec = 0;
		delay.tv_sec += 1;
	}

	nanosleep(&delay, NULL);
#else

#endif
}

unsigned int OSAL_get_threadid()
{

#ifndef WIMAX_SYS_WINDOWS
	return (unsigned int)pthread_self();
#else

#endif
}

OSAL_dynlib_t OSAL_load_lib(const char *lib_filepath)
{
#ifndef WIMAX_SYS_WINDOWS 

	void *plib = dlopen(lib_filepath, RTLD_LAZY);

	if ( plib == NULL )
		OSALTRACE(OSAL_ERROR, ("Failed to load library. Error: %s", dlerror()) );

	return (OSAL_dynlib_t)plib;	

#else

#endif
}

int OSAL_close_lib(OSAL_dynlib_t libhandle)
{
#ifndef WIMAX_SYS_WINDOWS

	return dlclose((void *)libhandle);

#else

#endif
}

OSAL_pfn_ptr OSAL_find_symbol(OSAL_dynlib_t libhandle, const char *symbol_name)
{
#ifndef WIMAX_SYS_WINDOWS

	void * sym = dlsym((void *)libhandle, symbol_name);

	if ( sym == NULL )
		OSALTRACE(OSAL_ERROR, ("Failed to find symbol %s. Error: %s", symbol_name, dlerror()) );

	return (OSAL_pfn_ptr)  sym;
#else

#endif
}



int linux_to_wimax_err(int err)
{

	switch (err)
	{
		case EINVAL: 
			return WMX_EINVAL;

		case ETIMEDOUT:
		case EBUSY:
			return WMX_ETIMEDOUT;

		default:
			return err;
	}

	return -1; 	// ideally control should never reach this
}


void* OSAL_alloc(size_t bytes)
{
	return malloc(bytes);
}

void * OSAL_zero_alloc(size_t bytes)
{
	return calloc(bytes, 1);
}

void OSAL_free(void *ptr)
{
	free(ptr);
}


/* 
 * This function requires to return the system up time in milisecond.
 * "time" function will not work here.
 * Use /proc/uptime file to get the system up time.
 */
UINT32 OSAL_timeGetTime()
{
	FILE * file;
	double up=0;
	int ret;

	file = fopen("/proc/uptime", "r");
	if (!file) {
		OSALTRACE(OSAL_ERROR, ("Failed to read /proc/uptime"));
		return 0;
	}

	// first value of /proc/uptime is up time
	ret = fscanf(file, "%lf", &up);
	if (ret < 1) {
		OSALTRACE(OSAL_ERROR, ("Failed to get uptime from /proc/uptime"));
		fclose(file);
		return 0;
	}
	fclose(file);

	// convert to milisecond
	return (UINT32)(up * 1000);
}

void OSAL_GetLocalTime(LPSYSTEMTIME pSysTime)
{
	time_t tm;
	struct tm *brokenup_time;

	if ( pSysTime == NULL )
		return;

	tm = time(NULL);

	brokenup_time = localtime(&tm);

	// Transfer the fields to desired format in output structure
	pSysTime->wYear = brokenup_time->tm_year;
	pSysTime->wMonth = brokenup_time->tm_mon;
	pSysTime->wDayOfWeek = brokenup_time->tm_wday;
	pSysTime->wDay = brokenup_time->tm_mday;
	pSysTime->wHour = brokenup_time->tm_hour;
	pSysTime->wMinute = brokenup_time->tm_min;
	pSysTime->wSecond = brokenup_time->tm_sec;
	pSysTime->wMilliseconds = 0;

}


int OSAL_fseek(FILE *f, long offset, int whence)
{
	return fseek(f, offset, whence);
}


long OSAL_PtrToLong(void *ptr)
{
	return (long)ptr;
}


OSAL_findHandle OSAL_FindFirstFile(const char *filepath, OSAL_FIND_DATA *pfindData)
{
	// TODO::OSAL-WORK::REQUIRED FOR INSTRUMENTATION - OSAL_FindFirstFile - API to be implemented

	return NULL;
}

BOOL OSAL_FindNextFile(OSAL_findHandle findHandle, OSAL_FIND_DATA *pfindData)
{

	// TODO::OSAL-WORK::REQUIRED FOR INSTRUMENTATION - OSAL_FindNextFile - API to be implemented
	return FALSE;
}

BOOL OSAL_FindClose(OSAL_findHandle findHandle)
{

	// TODO::OSAL-WORK::REQUIRED FOR INSTRUMENTATION - OSAL_FindClose - API to be implemented

	return FALSE;
}


int OSAL_delete_file(const char *file)
{
	return !remove(file);
}

int OSAL_remove_directory(const char *pathname)
{
	return !rmdir(pathname);
}

UINT32 OSAL_GetLastError(void)
{
  return GetLastError();
}


