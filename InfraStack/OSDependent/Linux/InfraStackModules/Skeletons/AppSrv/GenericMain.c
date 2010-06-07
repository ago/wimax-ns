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
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/types.h>

#include "wimax_osal_primitives.h"
#include "wimax_osal_config_controler.h"
#include "GenericMain.h"

#define MAX_TARGET_NAME 256

extern char *g_ifacename;
static char *progname;
int g_kill = 0;
int g_daemon = -1;

static 
void do_help(FILE *f)
{
	fprintf(f,
		"Intel WiMAX Network Service daemon\n"
		"\n"
		"Usage: %s [OPTIONS]\n"
		"\n"
		"-i IFACENAME    Work on said network interface\n"
		"-k              Kill existing instance (requires -i)\n"
		"-d              Debug mode, work in console and don't become a daemon\n"
		"-b              Force working in background and become a daemon\n"
		"-h              This help\n", progname);
}

int main(int argc, char *argv[])
{
	BOOL res;
	char target[MAX_TARGET_NAME] = {0};
	if (geteuid() != (uid_t) 0) {
		fprintf(stderr,	"ERROR: You do not possess sufficient privileges to perform this action.\n");
		return 1;
	}
	int c;
	int ret;
	int pid;

	opterr = 0;
	progname = basename(argv[0]);
	
	while ((c = getopt(argc, argv, "i:kdbk")) != -1)
		switch (c)
		{
		case 'i':
			g_ifacename = optarg;
			break;
		case 'k':
			g_kill = 1;
			break;
		case 'd':
			g_daemon = 0;
			break;
		case 'b':
			g_daemon = 1;
			break;
		case 'h':
			do_help(stdout);
			return 1;
			break;
		case '?':
			if (optopt == 'i')
				fprintf (stderr, "Option -%c requires an argument (interface name).\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			do_help(stderr);
			return 1;
		default:
			abort ();
		}

	// checking user priviledge
	if (geteuid() != (uid_t) 0) {
		fprintf(stderr,
			"ERROR: You do not possess sufficient privileges to perform this action.\n");
		return 1;
	}
	
	pid = IsDaemonRunning();
	if (g_kill) {
		int result;
		if (pid) {
			result = kill(pid, SIGINT);
			OSAL_sleep(5000);
			pid = IsDaemonRunning();
			/* Make sure he really stops */
			if (pid) {
				result = kill(pid, SIGKILL);
			}
		}
		else {
			result = 0;
		}
		return result;
	}
	
	if (g_daemon == -1) {
		res = OSAL_ConfigController_GetStrValue("ignore", OSAL_KEY_ENTRY_TARGET, target,MAX_TARGET_NAME);
		if (0 == strcasecmp("console", target)) {
			g_daemon = 0;
		}
		else {
			g_daemon = 1;
		}
	}

	if (g_daemon == 0) {
		ret = main_console();
	}
	else {
		ret = main_daemon();
	}
	return ret;
}
