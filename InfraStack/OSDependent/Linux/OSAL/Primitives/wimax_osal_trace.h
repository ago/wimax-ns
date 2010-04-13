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

#ifndef __OSALTRACE_H__

#define __OSALTRACE_H__

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <syslog.h>

// to force recompilation of this file everytime configure is run which can change some macros used in this file
#include "wns-version.h"  
// to hold the OSAL trace info like line number file name, function name etc
typedef struct _OsalTraceInfo {
	int loglevel;		// log level should be 0 to 5
	const char *fileInfo;	// it hold the file name and line number
	const char *functionname;	// it hold the function name
} OsalTraceInfo;

#define OSALTRACE_FILE  PKG_VAR_LOG_DIR "/system_log"
#define OSALTRACE_LOG_NUM_FILE PKG_SYSCONF_DIR "/logval"

#define EGIHT_X_BUFFER (1024*8)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LOCATION __FILE__ ":" TOSTRING(__LINE__)
#define FUNCTON  __func__

// Example:
// Just call this macro as following manner and it will log
// the data into logfile.txt file

// Ex : OSALTRACE(OSAL_DEBUG, ("test debug string"));
// Ex : OSALTRACE(OSAL_DEBUG, ("value x= %d", val));

//Out logs like as follows
//[timestamp]:filename:number [functionname] formatted string values

#define OSALTRACE(x,y) \
	{\
		OSALInfo(LOCATION,FUNCTON,x);\
		OSALTrace y;\
	}

#define OSAL_ERROR     0
#define OSAL_WARNING   1
#define	OSAL_INFO      2
#define OSAL_DEBUG     3

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
void OSALTrace(char *szformat, ...);

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
void OSALInfo(const char *, const char *, int);
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
void osallog(char *ch, int flush);

/*
 *
 * updateloglevevalue
 * read the log level from /var/log/wimax_appsrv/logval and update into global variable
 *	
 *
 * Parameters:
 * 	none
 *	
 *
 * Returns one of the following:
 *	- none
 *
 * Out standing issues

 *	Example
 *	
 */
void updateloglevevalue();


#endif
