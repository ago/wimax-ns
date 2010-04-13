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
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syslog.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <signal.h>
#include <execinfo.h>

/* get REG_EIP from ucontext.h */
#define __USE_GNU
#include <ucontext.h>

#include "Act.h"
#include "TraceModule.h"
#include "CommonServices.h"
#include "L5Common.h"
#include "L5Dispatcher.h"
#include "L5OpCodes.h"

#include "wimax_osal_primitives.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "GenericMain.h"

//////////////////////////////////////////////////////////////////////////
// Debug Output
#define DEBUG_OUTPUT(param)

///////////////////////////////////////////////////////////////////////////
// Static variables
OSAL_event_t deviceInsertRemoveEvent;
OSAL_critical_section csDeviceInsertRemove;

extern const char *WIMAX_APPSRVD_STR;

int g_enable_driver_msg;

static char gcLogFilePathName[MAX_FILENAME_LEN];

void PrintOptions()
{
	printf("Enter Command:\n");
	printf("q - Quit AppSrv\n");
	printf("t - Trace ReInit (ReLoads Registry Values)\n");
	printf("u - uplink(Apdo uplink event\n");
	printf("h - Help\n");
	printf("d - Toggle driver messages to display - debug & internal only\n");
	printf("\n\n");
}

// Check whether a process is an AppSrv process and if it's different than the current
BOOL IsAppSrvProcess(UINT32 processID)
{
	char szTempProcName[MAX_PATH] = "<unknown>";
	BOOL isAppSrvFound = FALSE;
	
	if (OSAL_get_processname (szTempProcName, sizeof(szTempProcName), (pid_t) processID)) {
		if ((strcasecmp(WIMAX_APPSRVD_STR, szTempProcName) == 0)
		    && (processID != (UINT32) getpid())) {
			isAppSrvFound = TRUE;
		}
	}

	return isAppSrvFound;
}



void print_callstack_to_file(int sig, siginfo_t *info, void *secret) 
{
	void *trace[16];
  	char **messages = (char **)NULL;
  	int i, trace_size = 0;
  	ucontext_t *uc = (ucontext_t *)secret;
	FILE *fp;	
	BOOL res;
	// printf("Came here %d\n", __LINE__);
	char command[MAX_STR_LEN + MAX_FILENAME_LEN];
	/* Do something useful with siginfo_t */
  	if ((sig != SIGSEGV) && (sig != SIGINT)) {
		syslog(LOG_ERR,"Got signal %d#92", sig);
		// printf("Came here %d\n", __LINE__);
		return;
	}
	res = GetConfig_LogPath(gcLogFilePathName, MAX_FILENAME_LEN);   
	if (res == FALSE) {
		// printf("Came here %d\n", __LINE__);
		OSAL_sprintf(gcLogFilePathName, "/tmp");
	}
	strcat(gcLogFilePathName, "/callstack.log");
	if(OSAL_fopen(&fp, gcLogFilePathName, "a", 0) < 0) {
		syslog(LOG_ERR, "Got signal %d, faulty address is %p, from %p", 
		       sig, info->si_addr, uc->uc_mcontext.gregs[REG_EIP]);
		syslog(LOG_ERR, "Could not open a file %s to log call stack");
		// printf("Came here %d\n", __LINE__);
  		return;
	}
	sprintf(command, "/bin/date > %s",gcLogFilePathName); 
	// printf("Came here %d\n", __LINE__);
	system(command); 
	fprintf(fp, "==================================================================================\n");
	fprintf(fp, "If Faulty address is in wimaxd excution segment \n");
	fprintf(fp, "Use addr2line to decode the address info into file name and line no\n");
	fprintf(fp, "For Example \n");
	fprintf(fp, "$> sudo addr2line -e /usr/bin/wimaxd 806f5fe \n");
	fprintf(fp, "If Faulty address is in shared object file \n");
	fprintf(fp, "$> sudo objdump -l -d -M intel /usr/lib/libWmxInstrument.so.0 > ./libinstru_dis\n");
	fprintf(fp, "Use the function name and offset to function and search file above for the line no \n");
	fprintf(fp, "==================================================================================\n\n");
	
	fprintf(fp, "Got signal %d, faulty address is %p, from %p\n", 
		sig, info->si_addr, uc->uc_mcontext.gregs[REG_EIP]);
	// printf("Came here %d\n", __LINE__);
  	
  	trace_size = backtrace(trace, 16);
  	/* overwrite sigaction with caller's address */
  	trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];
	
  	messages = backtrace_symbols(trace, trace_size);
  	/* skip first stack frame (points here) */
  	fprintf(fp,"[bt] Execution path: \n");	
  	for (i=1; i<trace_size; ++i) {
		fprintf(fp, "[bt] %s  \n", messages[i]);
	}
 	fclose(fp);
}

void console_signal_handler(int sig, siginfo_t *info, void *secret) 
{
	// signals are captured
  	static no_of_signals;
	if(no_of_signals >= 1)  {
		// printf("Second ctrl +c recieived \n");
		exit(0);
	}
	// printf("First ctrl +c recieived \n");
	no_of_signals++;
	
	if ((sig == SIGSEGV) && (sig == SIGINT)) {
		syslog(LOG_ERR,"Got signal %d", sig);
		print_callstack_to_file(sig, info, secret);
	}
 	
	
	Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_CLOSE, NULL, 0,NULL,NULL,NULL,NULL,NULL);	
//	if (act_mutex_ctrl != NULL) {
//		wmx_delete_mutex(act_mutex_ctrl);
	OSAL_delete_event(deviceInsertRemoveEvent);
	OSAL_delete_critical_section(&csDeviceInsertRemove);
//	}
	printf("Bye.\n");
	exit(0);
}         

int main_console(void)
{
	struct sigaction sa;
	char cmd[256];
	//UINT32 lastError;
	//UINT numberOfDevicesFound;
	//OSAL_critical_section csDeviceInsertRemove;
	const char *realm = "xhom.com";
	g_enable_driver_msg = FALSE; 

	int existing_pid;
	
	PrintOptions();

  	sa.sa_sigaction = (void *)console_signal_handler;
  	sigemptyset (&sa.sa_mask);
  	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	
  	sigaction(SIGSEGV, &sa, NULL);
  	sigaction(SIGUSR1, &sa, NULL);   // install our handler
	sigaction(SIGINT, &sa, NULL);
  	sigaction(SIGTERM, &sa, NULL);   // install our handler
	
	signal(SIGPIPE, SIG_IGN);
	
	existing_pid = IsDaemonRunning();
	if (existing_pid != 0) {
		fprintf(stderr, "Another instance of wimax (pid %d) is already running!. Shutting down...\n",
			existing_pid);
		return -1;
	}
	
	if(create_pidfile(getpid())) {
		syslog(LOG_INFO, "pidfile is created");
	}
	else {
		syslog(LOG_ERR, "failed to create the pidfile");
		return -1;
	}
	
	OSAL_init_critical_section(&csDeviceInsertRemove);
	OSAL_enter_critical_section(&csDeviceInsertRemove);
	if (OSAL_create_event(&deviceInsertRemoveEvent, TRUE, FALSE, NULL) != 0)
	{
		OSAL_exit_critical_section(&csDeviceInsertRemove);
		OSAL_delete_critical_section(&csDeviceInsertRemove);
		printf( "\nInitialization failed!\n" );
		//_getch();
		return -1;
	}
	// we need signalled event
	OSAL_set_event(deviceInsertRemoveEvent);
	OSAL_exit_critical_section(&csDeviceInsertRemove);
	
	if (!Act_Initialize()) {
		printf("\nInitialization failed!\n");
		OSAL_delete_event(deviceInsertRemoveEvent);
		OSAL_delete_critical_section(&csDeviceInsertRemove);
		// Stops the execution Not required
		//_getch();
		return -1;
	}
	

	for (;;) {
		OSAL_gets_s(cmd, 256);
		OSAL_strlwr_s(cmd, 256);
		
		if (!strcmp(cmd, "q")) {
			//wmx_EventLogger_Log(LOG_INFO, "Shutting down");
			printf("Shutting down...\n");
			Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_CLOSE, NULL, 0,NULL,NULL,NULL,NULL,NULL);
			
			OSAL_delete_event(deviceInsertRemoveEvent);
			OSAL_delete_critical_section(&csDeviceInsertRemove);
			
			printf("Bye.\n");
			return 0;
			
		}
		else if (!strcmp(cmd, "t")) {
			if (FALSE == TRACE_RELOAD()) {
				printf("Trace reload failed - Shutting down...\n");
				Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_CLOSE, NULL, 0,NULL,NULL,NULL,NULL,NULL);
				OSAL_delete_event(deviceInsertRemoveEvent);
				OSAL_delete_critical_section(&csDeviceInsertRemove);
				printf("Bye.\n");
				return 0;
			}
			printf("Trace Filters Reloaded\n");
			
		}
		else if(!strcmp(cmd, "r")) {
			printf("Resetting Device!\n");
			Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_RESET_DEVICE, NULL, 0,NULL,NULL,NULL,NULL,NULL);
		}
		
		else if(!strcmp(cmd, "f")) {
			printf("Full Restart!\n");
			Act_MessagesHandler(NULL, L5_TARGET_CONTROL, ACT_OPCODE_FULL_RESTART, NULL, 0,NULL,NULL,NULL,NULL,NULL);
		}
		else if(!strcmp(cmd,"u")) {
			NDnSAgent_ApdoLinkStatus(APDO_linkUp, 111,TRUE, realm);
			printf("apdo uplink\n");
			
		}
		else if (!strcmp(cmd, "h")) {
			PrintOptions();
			
		}
		else if (!strcmp(cmd, "d")) {
			if(g_enable_driver_msg == TRUE) {
				printf("DISABLE DEBUG\n");
				g_enable_driver_msg = FALSE;
			}
			else {
				printf("ENABLE DEBUG\n");
				g_enable_driver_msg = TRUE;
			}
		}
		else if (strlen(cmd) != 0) {
			printf("Unknown Command!\n");
		}
	}
	delete_pidfile();
}
