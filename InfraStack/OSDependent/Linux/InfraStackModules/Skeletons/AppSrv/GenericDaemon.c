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
#define _GNU_SOURCE /* for string.h:basename() */
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <dirent.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>

#include "Act.h"
#include "TraceModule.h"
#include "CommonServices.h"
#include "L5Common.h"
#include "L5OpCodes.h"
#include "L5Dispatcher.h"
#include "wimax_osal_primitives.h"
#include "L4ConfigurationManager.h"

const char *WIMAX_APPSRVD_STR = WIMAXD_NAME;

OSAL_event_t deviceInsertRemoveEvent;
OSAL_critical_section csDeviceInsertRemove;

static sem_t dsem;
static char gcLogFilePathName[MAX_FILENAME_LEN];

int IsDaemonRunning()
{
	int r;
	BOOL result;
	char pidfile_path[128] = {0}, proc_pid_exe[128], exe_file[128],
					      *basename_exe_file, *p;
	FILE *f;
	unsigned pid;
	char ifname[DEFULT_STR_SIZE];
	
	L4Configurations_getInterfaceName(ifname);
	
	// simple checking is done by looking for the pid file in /var/run/
	snprintf(pidfile_path, sizeof(pidfile_path),
		 VAR_RUN_DIR "/%s.%s.pid", WIMAX_APPSRVD_STR, ifname);
	f = fopen(pidfile_path, "r");
	
	if(f == NULL)
	{
		return FALSE;
	}
	
	result = FALSE;
	if (fscanf(f, "%u\n", &pid) != 1)
		goto error_cant_parse;
	/* WARNING! This is Linux specific -- see if the PID is running a
	 * wimaxd daemon by checking if it's exe link is this same wimaxd
	 * binary.
	 *
	 * We only check on the basename (wimaxd). Dirty, but this way we
	 * can catch installations in different prefixes that use the same
	 * PID file. If you don't want that to happen, change the PID file
	 * location...
	 *
	 * As well, if the daemon was deleted, @exe_file will read as
	 * 'FILE (deleted)'. We wipe that (deleted) part and consider the
	 * binary to be present (as it is running).
	 */
	snprintf(proc_pid_exe, sizeof(proc_pid_exe), "/proc/%u/exe", pid);
	r = readlink(proc_pid_exe, exe_file, sizeof(exe_file));
	if (r < 0)
		goto error_no_pid;
	exe_file[r] = 0;
	p = strtok(exe_file, " ");	/* remove ' (deleted)' if any */
	basename_exe_file = basename(exe_file);
	if (strcmp(WIMAXD_NAME, basename_exe_file))
		goto error_not_wimax;
	result = pid;
error_not_wimax:
error_no_pid:
error_cant_parse:
 	fclose(f);
	return result;
}

BOOL ensure_dir_exists(const char *dirname)
{
	DIR *dirent;
	
	dirent = opendir(dirname);
	if (dirent) {
		closedir(dirent);
		return TRUE;
	}
	/* Couldn't open, maybe not a dir, maybe not
	 * existant... insted of trying to analyze, we try to create
	 * it. If it fails, complain. */
	if (mkdir(VAR_RUN_DIR,
		  S_IRWXU | S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH) == -1) {
		syslog(LOG_ERR, "Cannot create " VAR_RUN_DIR ": %m\n");
		return FALSE;
	}
	return TRUE;
}


int create_pidfile(unsigned currpid)
{
	char pidfile_path[128] = { 0 };
	FILE *f;
	time_t t0, t;
	
	char ifname[DEFULT_STR_SIZE];
	
	L4Configurations_getInterfaceName(ifname);
	/* Does VAR_RUN_DIR exist? create it if not */
	if (ensure_dir_exists(VAR_RUN_DIR) == FALSE)
		return FALSE;
	
	// open/create the pid file in /var/run/
	snprintf(pidfile_path, sizeof(pidfile_path),
		 VAR_RUN_DIR "/%s.%s.pid", WIMAX_APPSRVD_STR, ifname);
	t0 = time(NULL);
	while(1) {
		f = fopen(pidfile_path, "w+");
		if(f != NULL)
			break;
		t = time(NULL);
		
		if (errno == EROFS) {
			if (t - t0 < 10) {
				syslog(LOG_INFO, "waited %ld seconds for file system "
				       "to become read only", (int) t - t0);
				sleep(1);
				continue;
			} else {
				syslog(LOG_INFO, "waited %ld seconds (too long) for "
				       "file system to become read only, giving up",
				       (int) t - t0);
				return FALSE;
			}
		}
		else
			return FALSE;
	}
	fprintf(f, "%d\n", currpid);
	fclose(f);
	return TRUE;
}

int delete_pidfile()
{
	char pidfile_path[128] = { 0 };
	char ifname[DEFULT_STR_SIZE];
	
	L4Configurations_getInterfaceName(ifname);
	snprintf(pidfile_path, sizeof(pidfile_path),
		 VAR_RUN_DIR "/%s.%s.pid", WIMAX_APPSRVD_STR, ifname);
	unlink(pidfile_path);
	return TRUE;
}

void daemon_signal_handler(int sig, siginfo_t *info,
			   void *secret) 
{
	// signals are captured
  	static no_of_signals;
	if(no_of_signals >= 1)  {
		exit(0);
	}
	no_of_signals++;
	
 	print_callstack_to_file(sig, info, secret);

	syslog(LOG_INFO, "shutting  daemon signal handler down");
	sem_post(&dsem);
}         

void stop_signal_handler(int sig)
{
	// signals are captured
	syslog(LOG_INFO, "stop signal is arrived: %d", sig);
	sem_post(&dsem);
	// sleep(20);
}

int main_daemon(void)
{

	pid_t pid;
	struct sigaction sa;
	int sem_ret;

	// open the syslog
	syslog(LOG_INFO, "daemon starts");

	// check if the daemon is running now
	if(IsDaemonRunning())
	{
		syslog(LOG_ERR, "daemon is already running");
		return 1;
	}

	pid = fork();
	if (pid < 0)
	{
		syslog(LOG_ERR, "fork failed");
		return 1;
	}
	else if (pid > 0)
	{
		// parent process
		exit (0);
	}

	// child process
	setsid();
	chdir("/");
	umask(0);

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	sa.sa_sigaction = (void *)daemon_signal_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;

	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGUSR1, &sa, NULL);  

	signal(SIGINT, stop_signal_handler);
	signal(SIGTERM, stop_signal_handler);
	signal(SIGPIPE, SIG_IGN);

	if(create_pidfile(getpid()))
	{
		syslog(LOG_INFO, "pdifile is created");
	}
	else
	{
		syslog(LOG_ERR, "failed to create the pidfile");
		return -1;
	}

	// init semaphore
	sem_ret = sem_init(&dsem,0,0);

	OSAL_init_critical_section(&csDeviceInsertRemove);
	OSAL_enter_critical_section(&csDeviceInsertRemove);
	if (OSAL_create_event(&deviceInsertRemoveEvent, TRUE, FALSE, NULL) != 0)
	{
		printf( "\nInitialization failed!\n" );
		OSAL_exit_critical_section(&csDeviceInsertRemove);
		OSAL_delete_critical_section(&csDeviceInsertRemove);
		//_getch();
		return -1;
	}
	// we need signalled event
	OSAL_set_event(deviceInsertRemoveEvent);
	OSAL_exit_critical_section(&csDeviceInsertRemove);

	// start the appsrv process
	if (!Act_Initialize()) {
		OSAL_delete_event(deviceInsertRemoveEvent);
		OSAL_delete_critical_section(&csDeviceInsertRemove);
		return 1;
	}

	// waiting for signal
	sem_ret = sem_wait(&dsem);

	// close the daemon
	syslog(LOG_INFO, "shutting down");
	Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_CLOSE, NULL, 0,NULL,NULL,NULL,NULL,NULL);
	OSAL_delete_event(deviceInsertRemoveEvent);
	OSAL_delete_critical_section(&csDeviceInsertRemove);
	sem_ret = sem_destroy(&dsem);   // Event semaphore handle
	delete_pidfile();

	return 0;
}
