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

#ifndef __WIMAX_CONSTS_H__
#define __WIMAX_CONSTS_H__

#define	INFINITE	0xFFFFFFFF
#define MAX_PATH          260
#define MAX_DIR          256
#define _MAX_DIR          256
#define _MAX_PATH          260

#define MAXSHORT    0x7fff

#define PATH_SEPARATOR		"/"

#define FILE_ATTRIBUTE_DIRECTORY	0x10L

#if !defined(UNREFERENCED_PARAMETER)

	#define UNREFERENCED_PARAMETER(p) 
#endif

#define CP_ACP                    0	// default to ANSI code page


#define	WINAPI	

// ################### Dummy event log constants ###################

#define	EVENTLOG_SUCCESS	0
#define	EVENTLOG_ERROR_TYPE	1
#define	EVENTLOG_WARNING_TYPE	2
#define	EVENTLOG_INFORMATION_TYPE	3
#define	EVENTLOG_AUDIT_SUCCESS	4
#define	EVENTLOG_AUDIT_FAILURE	5

#define	CP_UTF8			65001


#define 	TEXT(x)		x

#endif //__WIMAX_CONSTS_H__
