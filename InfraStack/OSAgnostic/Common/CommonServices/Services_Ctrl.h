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
#ifndef _SERVICES_CTRL_H
#define _SERVICES_CTRL_H

#include "wimax_osal_types.h"

static char* SystemStates[] = {
	"Uninit",
	"Init",
	"Ready",
	"Scan",
	"Standby",
	"Connecting",
	"Wimax_Connected",
	"Data_Path_Connected",
	"Idle",
	"Disconnecting",
	"Out_Of_Zone",
	"Sleep_Active",
	"Producation",
	"Config",
	"RF_Off",
	"RF_Shutdown"
};

static char *L4ResponseStatus[] = {
	"L3L4_RESPONSE_STATUS_SUCCESS_DONE",
	"L3L4_RESPONSE_STATUS_SUCCESS_IN_PROCESS",
	"L3L4_RESPONSE_STATUS_INVALID_OPCODE",
	"L3L4_RESPONSE_STATUS_ERROR_BAD_STATE",
	"L3L4_RESPONSE_STATUS_ILLEGAL_VALUE",
	"L3L4_RESPONSE_STATUS_MISSING_PARAMS",
	"L3L4_RESPONSE_STATUS_VERSION_ERROR",
	"L3L4_RESPONSE_STATUS_ACCESSIBILITY_ERROR",
	"L3L4_RESPONSE_STATUS_BUSY",
	"L3L4_RESPONSE_STATUS_CORRUPTED_TLV",
	"L3L4_RESPONSE_STATUS_UNINITIALIZED",
	"L3L4_RESPONSE_STATUS_UNKNOWN_ERROR",
	"L3L4_RESPONSE_STATUS_PRODUCTION_ERROR"
};


BOOL Services_Init();
void Services_Fini();

char* GetL4Opcode(void *buffer);
char* GetL4Indication(UINT16 indCode);

#endif // _SERVICES_CTRL_H