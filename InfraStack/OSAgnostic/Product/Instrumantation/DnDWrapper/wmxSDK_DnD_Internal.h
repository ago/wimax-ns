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
#ifndef _WMX_SDK_DND_INTERNAL_H
#define _WMX_SDK_DND_INTERNAL_H


#include <stdio.h>
#include "XmlParser.h"
#include "TraceStringTables.h"

//Definitions
//#define	HStringTable			UINT32
//#define INVALID_HSTRING_TABLE	((UINT32)-1)
#define FILE_NAME_LEN			100

#define LOG_NUM_STR_LENGTH		4
#define FILE_NAME_MAX_NUMBER	10000


//Handles
static HStringTable		hStringTableSDillo	 = INVALID_HSTRING_TABLE;
static HStringTable		hStringTableNDillo	 = INVALID_HSTRING_TABLE;
static HStringTable		hStringTableArm0	 = INVALID_HSTRING_TABLE;
static HStringTable		hStringTableArm1	 = INVALID_HSTRING_TABLE;


//Types
typedef enum _TrcLoadEnum
{
	TRC_FILE_LOAD_SUCCESS=0,
	TRC_FILE_LOAD_ERROR,
	TRC_FILE_LOAD_FILE_NOT_FOUND	
}TrcLoadEnum;

typedef enum _DnD_SUPPORTED_L4_TYPES
{
	DND_MONITOR_ON,
	DND_MONITOR_OFF,
	DND_SET_MON_FILTER,
	DND_GET_MON_FILTER,
	DND_SET_TRC_FILTER,
	DND_GET_TRC_FILTER
}DnD_SUPPORTED_L4_TYPES;

//APIs
BOOL ConnectToStringTables();
void FreeStringTables();
FILE * GetNextFile(const WCHAR * path, UINT32 nextFileIndex, WCHAR * prefix);
INT32 GetLeadingZeros(INT32 num);

//wmx_Status_t DeviceMonitorControl(BOOL isMonitorOn);

HStringTable GetStringTableArm0();
HStringTable GetStringTableArm1();
HStringTable GetStringTableSDillo();
HStringTable GETStringTableNDillo();

UINT32 GetSignatureArm0();
UINT32 GetSignatureArm1();
UINT32 GetSignatureSDillo();
UINT32 GetSignatureNDillo();

#endif // _WMX_SDK_DND_INTERNAL_H
