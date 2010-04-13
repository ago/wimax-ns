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
#ifndef _APPSRV_CONTROLLER_H
#define _APPSRV_CONTROLLER_H


#include "L5Common.h"
#include "VersionUtils.h"
#include "Versions.h"
#include "KDapiAdapter.h"


#define RESET_TIMEOUT 3000 // in milisecs


#define APPSRV_PRINT(str) printf(str);

#define MOCMSGPROXY_STARTED			0x00000001
#define DNDA_GENT_STARTED			0x00000010
#define SUPPLICANT_AGENT_STARTED	0x00000100
#define NDNS_AGENT_STARTED			0x00001000

#define INTERNAL_AGENTS_INITIALIZED		0x00000001
#define MOCMSGPROXY_INITIALIZED			0x00000010
#define DNDA_GENT_INITIALIZED			0x00000100
#define SUPPLICANT_AGENT_INITIALIZED	0x00001000
#define NDNS_AGENT_INITIALIZED			0x00010000

typedef enum _APPSRV_INIT_ST
{
	INIT_SUCCESS,
	INIT_CONFIG_FAIL,
	INIT_FAIL
} APPSRV_INIT_ST;

//ACT interface functions:
void Act_Shutdown();
BOOL Act_Initialize();
BOOL Act_InitNew();
BOOL Act_Finalize();
void Act_FullRestart();
BOOL Act_Stop();

BOOL Act_GetConfigReason(UINT32 *reason);

void Act_DriverDeviceStatus(DRIVER_STATUS driverStatus);

void Act_MessagesHandler(L5_CONNECTION Conn,
						 L5_TARGET_ID nOriginID,

						 UINT32 dwSentMessageID,
						 void  *pvSentBuffer,
						 UINT32 cbSentBufferSize,

						 UINT32 *pdwResponseMessageID,
						 void  *pvResponseBuffer,
						 UINT32 *cbResponseBufferSize,

						 void *pvUserContext,
						 void *pvReserved );


//Agent's interface functions which called by ACT:
typedef APPSRV_INIT_ST (*tpfnInitAgent)(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn);
typedef BOOL (*tpfnStartAgent)();
typedef BOOL (*tpfnStopAgent)();
typedef void (*tpfnFinalizeAgent)();
typedef BOOL (*tpfnSetDriverState)(DRIVER_STATUS driverStatus);

//Define ACT-Agent interface:
typedef struct _tACTFunctions
{
	tpfnInitAgent		pInitAgent;
	tpfnStartAgent		pStartAgent;
	tpfnStopAgent		pStopAget;
	tpfnFinalizeAgent	pFinalizeAgent;
	tpfnSetDriverState	pSetDriverState;
} tACTFunctions;

typedef APPSRV_INIT_ST (*agent_Initialize)(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn);
typedef void (*agent_Finalize)();
typedef BOOL (*agent_Start)();
typedef BOOL (*agent_Stop)();
typedef void (*agent_EventHandler)( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext );

#endif // _APPSRV_CONTROLLER_H
