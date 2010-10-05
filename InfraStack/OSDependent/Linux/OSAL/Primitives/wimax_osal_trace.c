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

#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "wimax_osal_types.h"
#include "wimax_osal_trace.h"

// Som hard coded info string to log into file
const char *g_logtype[] = { "Error:",
	"Warning:",
	"Info:",
	"Debug:",
	"Trace:"
};

// gloabel variable which hold the osal trace info while logging
OsalTraceInfo g_OsalTraceInfo;

// to avoid exced the count level
int g_iloglevel = 2;
int g_iloglevelreadflag = 0;

// to avoid multi tread environment to log the thread
static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 *
 * File: osaltrace.h
 *
 * Desc: This module is used for log the info to to flat file
 *
 * Implemented API methods:
 *		- OSALTrace
 *		-
 * OUTSTANDING OPENS:
 *		1. At present the error condition not checked. Assumed that the flat file opened.
 *			File is not able to open this function return.
 *		2. At present we are not closing the file and flush the file once write it for
 *			Time saving purpose
 *
 * ASSUMPTIONS / NOTES:
 *		1.
 */

/*
 *
 * OSALTrace
 * This function takes the location and function and and formated string as argument and
 * log into logfile.txt at present
 * Parameters:
 * char* szformat, ...[IN] - formated string which same like sprintf
 *
 * Returns one of the following:
 *	- Function return value is nothing
 *
 * Out standing issues
 *		-  1. log file hardcoded as logfile.txt and it will create at application running or
 *			 application changed directory.
 *		   2.  Time stamp is not formated string value is 8 digit time value.
 *		   3. First two agrument should be hide in this function but i could not write some
 *				powerful macro
 *	Example
 *	/OSAL/unittests/osaltrace
 */

void OSALTrace(char *szformat, ...)
{
	// log type should be 0 to 4 default value will assign info
	if (g_OsalTraceInfo.loglevel > g_iloglevel
	    || g_OsalTraceInfo.loglevel < 0) {
		goto out;
	}
	// if argument path  null....
	if (szformat == NULL) {
		goto out;
	}

	time_t currTime;
        struct tm timeinfo;

	va_list args;
	static char Buffer[EGIHT_X_BUFFER] = { 0 };
	static char outBuffer[EGIHT_X_BUFFER] = { 0 };
	time_t tim = time(NULL);
 	currTime = time(NULL);
        timeinfo = *(localtime(&currTime));

	sprintf(Buffer, "{pid:%u, tid: %u time = %02d:%02d:%02d} [%i] %s %s [%s]", getpid(), (unsigned int)pthread_self(), timeinfo.tm_hour,
        timeinfo.tm_min,
        timeinfo.tm_sec,(int)tim, g_OsalTraceInfo.fileInfo,
		g_logtype[g_OsalTraceInfo.loglevel],
		g_OsalTraceInfo.functionname);
	osallog(Buffer, 0);
	Buffer[0] = '\0';

	va_start(args, szformat);
	// avoid buffer over flow
	vsnprintf(Buffer, EGIHT_X_BUFFER - 2, szformat, args);
	va_end(args);

	sprintf(outBuffer, "%s\n", Buffer);

	osallog(outBuffer, 1);

out:
	// release the lock once done
	pthread_mutex_unlock(&g_mutex);
}

/*
 *
 * osallog
 * This function create the log file and flush into file. if file unable to open
 *	it will return simply with out writing into file
 *
 * Parameters:
 * 	char *ch[IN]- Inparameter buffer to write into file. buffer size max is MAX_PATH into 4 times
 *	int flush[IN] - 0 means no flush the file 1 means flush the file
 *
 * Returns one of the following:
 *	- Function return value is nothing
 *
 * Out standing issues

 *	Example
 *	/OSAL/unittests/osaltrace
 */
void osallog(char *ch, int flush)
{
	static FILE *log = 0;

	if (log == 0) {
        log = fopen(OSALTRACE_FILE, "at");
		if (!log)
            log = fopen(OSALTRACE_FILE, "wt");
		if (!log) {
			syslog(LOG_ERR, "wimaxd[osal] - can not open logfile (%s) for writing.\n", OSALTRACE_FILE);
			return;	// bail out if we can't log
		}
	}
	// write into file
	fprintf(log, "%s", ch);
	// put extra to log next line to build
	//fprintf(log,"\n");
	if (flush == 1)
		fflush(log);

#ifdef OSAL_CONSOLE
	printf(ch);
#endif

	// fclose(log);
}

/*
 *
 * OSALInfo
 * This function takes the location and function and and formated string as argument and
 * log into logfile.txt at present
 * Parameters:
 * 	const char* location[IN]- location name This argument must be LOCATION macro which
 *							 define above this file
 *	const char * funcName[IN]- function name of the callee. this should be FUNCTON macro
 *								define above
 *  int logtype[IN]	- this could be 0 to 4 value this value defined in the macro as
 *						OSAL_ERROR 		0
 *						OSAL_WARNING	1
 *						OSAL_INFO		2
 *						OSAL_DEBUG		3
 *
 * Returns one of the following:
 *	- Function return value is nothing
 *
 * Out standing issues
 *		-  1. log file hardcoded as logfile.txt and it will create at application running or
 *			 application changed directory.
 *		   2.  Time stamp is not formated string value is 8 digit time value.
 *		   3. First two agrument should be hide in this function but i could not write some
 *				powerful macro
 *	Example
 *	/OSAL/unittests/osaltrace
 */
void OSALInfo(const char *filelocation, const char *functionname, int loglevel)
{
	// lock the threads and won it
	pthread_mutex_lock(&g_mutex);

	updateloglevevalue();
	// store the file info
	g_OsalTraceInfo.fileInfo = filelocation;
	g_OsalTraceInfo.functionname = functionname;
	g_OsalTraceInfo.loglevel = loglevel;
}

void updateloglevevalue()
{
	FILE *log = 0;
	char number[20] = {0};
	// open if first time 
	if ( g_iloglevelreadflag == 0 )
	{
		g_iloglevelreadflag = 1;
        log = fopen(OSALTRACE_LOG_NUM_FILE, "r");
		if (log){
			fgets(number,10,log);
			g_iloglevel = atoi(number);
			fclose(log);
		}
	}
}
