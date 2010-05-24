/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

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
#ifndef wimax_osal_types_
#define wimax_osal_types_

#include "wimax_osal_types.h"

//Threads APIs
int OSAL_create_thread(OSAL_thread_func tf, void *arg, OSAL_thread_t *p_thread_id);
unsigned int OSAL_get_threadid();
int OSAL_timedjoin_thread(OSAL_thread_t threadid, unsigned int milliseconds, void **status);
int OSAL_kill_thread(OSAL_thread_t thread_id);

//Thread synchronization APIs
int OSAL_create_mutex(OSAL_mutex_t *pmtx, int owned, char * name);
int OSAL_delete_mutex(OSAL_mutex_t mtx);
int OSAL_lock_mutex(OSAL_mutex_t mtx);
int OSAL_trylock_mutex(OSAL_mutex_t mtx);
int OSAL_unlock_mutex(OSAL_mutex_t mtx);
int OSAL_timedlock_mutex(OSAL_mutex_t mtx, unsigned int milliseconds);
void OSAL_sleep(unsigned int milliSecs);
int OSAL_init_critical_section(OSAL_critical_section* pcs);
int OSAL_enter_critical_section(OSAL_critical_section* cs);
int OSAL_exit_critical_section(OSAL_critical_section* cs);
int OSAL_delete_critical_section(OSAL_critical_section* cs);

//Events:
int OSAL_create_event(OSAL_event_t* p_evt , BOOL manual_reset, BOOL initialState, char *name);
int OSAL_create_event_with_security_attributes(OSAL_event_t* p_evt , BOOL manual_reset, BOOL initialState, char *name);
int OSAL_delete_event(OSAL_event_t evt);
int OSAL_set_event(OSAL_event_t evt );
int OSAL_reset_event(OSAL_event_t evt);
int OSAL_multiple_wait_event(int count, OSAL_event_t *evts, BOOL wait_for_all_or_not, unsigned int time_out);
int OSAL_wait_event (OSAL_event_t evt , unsigned int time_out_milli_sec);

//Atomic operations
long OSAL_atomic_compareExchange(long volatile *lpDest, long exchange, long comperand);
long OSAL_atomic_exchange(long volatile *lpTarget, long value);
void* OSAL_atomic_exchangepointer(void* volatile *lpTarget, void* value);
void* OSAL_atomic_compareexchangepointer(void* volatile *lpDest, void* exchange, void* comperand);
long OSAL_atomic_increment(long volatile *lpAddend);
long OSAL_atomic_decrement(long volatile *lpAddend);

//Dynamic library
OSAL_dynlib_t OSAL_load_lib(const char *lib_filepath);
int OSAL_close_lib(OSAL_dynlib_t libhandle);
OSAL_pfn_ptr OSAL_find_symbol(OSAL_dynlib_t libhandle, const char *symbol_name);

//File system
BOOL OSAL_get_processname(char *processname, int bufsize, pid_t pid);
BOOL OSAL_create_directory(char * path_name);
BOOL OSAL_get_file_stat(const char *file_name, OSAL_file_stat * pfile_stat);
BOOL OSAL_set_file_stat(const char *file_name, OSAL_mode_t fileAttributes);
long OSAL_get_file_size(int fd);
long OSAL_compare_filetime(const OSAL_filetime * pfiletime1, const OSAL_filetime * pfiletime2);
int OSAL_fopen(FILE** pFile, const char *filename, const char *mode, int sharemode);
int OSAL_fclose(FILE *stream);
int OSAL_fflush(FILE *stream );
size_t OSAL_fread(void *buffer, size_t size, size_t count, FILE *stream );
size_t OSAL_fwrite(const void *buffer, size_t size, size_t count, FILE *stream );
int OSAL_fprintf(FILE *stream, const char *format , ...);
int OSAL_vsprintf(char *buffer, size_t sizeInBytes, const char *format, ... ); 

//Time:
UINT32 OSAL_timeGetTime();
void OSAL_GetLocalTime(LPSYSTEMTIME lpSystemTime);

//Memory:
void OSAL_ZeroMemory( void *Destination, size_t Length);
int OSAL_wmemcpy_s(wchar_t *dest, size_t sizeInWords, const wchar_t *src, size_t count);
int OSAL_CAPI_wmemcpy_s(OSAL_WIMAX_API_WSTRING dest, size_t sizeInWords, const OSAL_WIMAX_API_WSTRING src, size_t count);
int OSAL_memcpy_s(void *dest, size_t sizeInBytes, const void *src, size_t count);


void *OSAL_alloc(size_t bytes);
void *OSAL_zero_alloc(size_t bytes);
void OSAL_free(void *to_free);

long OSAL_PtrToLong(void *);	

OSAL_findHandle OSAL_FindFirstFile(const char *filepath, OSAL_FIND_DATA *pfindData);
BOOL OSAL_FindNextFile(OSAL_findHandle findHandle, OSAL_FIND_DATA *pfindData);
BOOL OSAL_FindClose(OSAL_findHandle findHandle);

int OSAL_delete_file(const char *file);
int OSAL_remove_directory(const char *directory);

// Misc.
UINT32 OSAL_GetLastError(void);

#endif
