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
#ifndef _SUPPLICANT_AGENT_H
#define _SUPPLICANT_AGENT_H


// Pipe and L4 includes
#include "List.h"
#include "L5Common.h"
#include "L5OpCodes.h"		

#include "wmxSDK_Sup_L5.h"
#include "wmxSDK_Sup_CtrlAgent.h"
#include "wmxSDK_Sup_1.h"
#include "wmxSDK_Sup_4.h"

#include "Act.h"

#if !defined(WPA_OPEN_SOURCE)
// Devicescape's includes
#include "includes.h"
#include "common.h"
#include "config.h"
#include "eap.h"
#include "eloop.h"
#include "wpa_supplicant_i.h"
#include "radius.h"
#include "radius_client.h"

#endif

// Method types
//typedef enum _tEAPmethod
//{
//	EAP_TTLS_EAP_MsChapv2,
//	EAP_TLS_P2
//} tEAPmethod, *tpEAPmethod;

/************************/
// TODO: this value should reside in one place for all agents
#define L4_MSG_MAX_LENGTH		8192
/************************/

#define CERTIFICATES_FILES_MAX_NUM 10;
#define MSK_SIZE 64
#define RSP_MAX_SIZE 2048

#define FreeIfAllocated(x) { if (x != NULL) { free(x); x = NULL; } }

typedef enum
{
	e_SUPP_RESPONSE_AVAILABLE,
	e_SUPP_NO_RESPONSE,
	e_SUPP_KEY_AVAILABLE,
	e_SUPP_KEY_INVALID,
	e_SUPP_ERROR
} eSuppRetStatus;

#if !defined(WPA_OPEN_SOURCE)

//#/ DS I/F variables
typedef struct _EAP_SM_Variables 
{
	size_t eapReqData_len;
	UINT8 *eapReqData;
	BOOL eapSuccess;
	BOOL eapRestart;
	BOOL eapFail;
	BOOL eapResp;
	BOOL eapNoResp;
	BOOL eapReq;
	BOOL portEnabled;
	BOOL altAccept;
	BOOL altReject;
	UINT32 idleWhile;	
} EAP_SM_Variables;


typedef struct 
{
	swc_config_t	 *sc;  
	size_t			 MskKeyActualLen;
	size_t			 RespBufferSize;
	EAP_SM_Variables EapSmVars;
	UINT32           moduleId;
	UINT8            MskKey[MSK_SIZE];
	UINT8			 RespBuffer[RSP_MAX_SIZE];		
} SupplicantData;

#endif

typedef struct  
{
	BOOL isEnabled;
	BOOL isValid;
	int eapmethod;
	char *identity;
	char *anonidentity;
	char *password;
	char *cacert;
	char *clientcert;
	char *privatekey;
	char *privatekeypasswd;
	char *cacert2;
	char *clientcert2;
	char *privatekey2;
	char *privatekeypasswd2;
	int phase2;
	char *simreader;
	char *simpin;		
	char *nai;
} SupplicantConfig;



// AppSrv Agent Interface:
void SupplicantAgent_Shutdown();

void Supplicant_MessagesHandler(L5_CONNECTION Conn,
								L5_TARGET_ID nOriginID,

								UINT32 dwSentMessageID,
								void  *pvSentBuffer,
								UINT32 cbSentBufferSize,

								UINT32 *pdwResponseMessageID,
								void  *pvResponseBuffer,
								UINT32 *cbResponseBufferSize,

								void *pvUserContext,
								void *pvReserved );

//void Supplicant_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext);

//TODO: remove
void SupAgent_ResetSupplicant();
char *SupAgent_ExtractString(void *pvSentBuffer);

EXTERN_C EXPORT void SupplicantAgent_Finalize();
EXTERN_C EXPORT BOOL SupplicantAgent_Stop();
EXTERN_C EXPORT BOOL SupplicantAgent_Start();
EXTERN_C EXPORT APPSRV_INIT_ST SupplicantAgent_Initialize(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn);
#endif // _SUPPLICANT_AGENT_H