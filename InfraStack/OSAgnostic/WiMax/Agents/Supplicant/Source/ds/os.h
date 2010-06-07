/*
 * wpa_supplicant/hostapd / OS specific functions
 * Copyright (c) 2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * All Rights Reserved.
 */

#ifndef OS_H
#define OS_H

#include "cfgdefs.h"

typedef long os_time_t;

#ifndef CONFIG_NATIVE_WINDOWS
#include <pthread.h>
typedef pthread_mutex_t	os_mutex_t;
typedef pthread_t	os_thread_t;
#else
#include <windows.h>
typedef HANDLE		os_mutex_t;
typedef struct os_thread_t {
	HANDLE t_handle;
	UINT32 t_id;
} os_thread_t;
#endif

/**
 * os_sleep - Sleep (sec, usec)
 * @sec: Number of seconds to sleep
 * @usec: Number of microseconds to sleep
 */
void os_sleep(os_time_t sec, os_time_t usec);

struct os_time {
	os_time_t sec;
	os_time_t usec;
};

/**
 * os_get_time - Get current time (sec, usec)
 * @t: Pointer to buffer for the time
 * Returns: 0 on success, -1 on failure
 */
int os_get_time(struct os_time *t);


/* Helper macros for handling struct os_time */

#define os_time_before(a, b) \
	((a)->sec < (b)->sec || \
	 ((a)->sec == (b)->sec && (a)->usec < (b)->usec))

#define os_time_sub(a, b, res) do { \
	(res)->sec = (a)->sec - (b)->sec; \
	(res)->usec = (a)->usec - (b)->usec; \
	if ((res)->usec < 0) { \
		(res)->sec--; \
		(res)->usec += 1000000; \
	} \
} while (0)


/**
 * os_daemonize - Run in the background (detach from the controlling terminal)
 * @pid_file: File name to write the process ID to or %NULL to skip this
 * Returns: 0 on success, -1 on failure
 */
int os_daemonize(const char *pid_file);

/**
 * os_daemonize_terminate - Stop running in the background (remove pid file)
 * @pid_file: File name to write the process ID to or %NULL to skip this
 */
void os_daemonize_terminate(const char *pid_file);

/**
 * os_get_random - Get cryptographically strong pseudo random data
 * @buf: Buffer for pseudo random data
 * @len: Length of the buffer
 * Returns: 0 on success, -1 on failure
 */
int os_get_random(unsigned char *buf, size_t len);

/**
 * os_random - Get pseudo random value (not necessarily very strong)
 * Returns: Pseudo random value
 */
unsigned long os_random(void);

/**
 * os_rel2abs_path - Get an absolute path for a file
 * @rel_path: Relative path to a file
 * Returns: Absolute path for the file or %NULL on failure
 *
 * This function tries to convert a relative path of a file to an absolute path
 * in order for the file to be found even if current working directory has
 * changed. The returned value is allocated and caller is responsible for
 * freeing it. It is acceptable to just return the same path in an allocated
 * buffer, e.g., return strdup(rel_path). This function is only used to find
 * configuration files when os_daemonize() may have changed the current working
 * directory and relative path would be pointing to a different location.
 */
char * os_rel2abs_path(const char *rel_path);

/**
 * os_program_init - Program initialization (called at start)
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a programs starts. If there are any OS specific
 * processing that is needed, it can be placed here. It is also acceptable to
 * just return 0 if not special processing is needed.
 */
int os_program_init(void);

/**
 * os_program_deinit - Program deinitialization (called just before exit)
 *
 * This function is called just before a program exists. If there are any OS
 * specific processing, e.g., freeing resourced allocated in os_program_init(),
 * it should be done here. It is also acceptable for this function to do
 * nothing.
 */
void os_program_deinit(void);

/**
 * os_mutex_init - Mutex initialization, allocate any needed resources
 * @mutex: Mutex pointer
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a program needs to initialize a Mutex. The
 * default state of the mutex is released.
 */
int os_mutex_init(os_mutex_t *mutex);

/**
 * os_mutex_destroy - Mutex deinitialization, release any acquired resources
 * @mutex: Mutex pointer
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a program needs to deinitialize a Mutex as
 * part of a shutdown/deinit sequence. 
 */
int os_mutex_destroy(os_mutex_t *mutex);

/**
 * os_mutex_acquire - Mutex acquisiting, wait forever on mutex
 * @mutex: Mutex pointer
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a program needs to lock a mutex in order to
 * enter a critical section. The call will block until the mutex is acquired,
 * so care should be taken to avoid a deadlock scenario.
 */
int os_mutex_acquire(os_mutex_t *mutex);

/**
 * os_mutex_release - Mutex release, remove lock on mutex
 * @mutex: Mutex pointer
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a program needs to unlock a mutex in order to
 * allow other threads to have the ability to enter a critical section. 
 */
int os_mutex_release(os_mutex_t *mutex);

/**
 * os_thread_create - Create a thread running the function/arg specified
 * @t: Thread pointer
 * @t_ent: Function to be called as thread entry point
 * @t_arg: Pointer to pass as argument to thread entry point function
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a program needs to start a Thread. The thread
 * is created in a running state.
 */
int os_thread_create(os_thread_t *t, void *t_ent, void *t_arg);

/**
 * os_thread_destroy - Stop a thread
 * @t: Thread pointer
 * Returns: 0 on success, -1 on failure
 *
 * This function is called when a program needs to stop a Thread. This results
 * in simply stoping the thread execution without any deinitialization.
 */
int os_thread_destroy(os_thread_t *t);


#endif /* OS_H */
