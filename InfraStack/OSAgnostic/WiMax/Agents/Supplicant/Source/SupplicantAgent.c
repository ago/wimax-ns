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
#pragma warning(disable:4054) // type-cast from function ptr to data ptr (void*)

#include "SupplicantAgent.h"

#include "TraceModule.h" 
#include "Messenger.h"
#include "L4ConfigurationManager.h"
#include "IndicatorsSubscribers.h"
#include "wimax_osal_event_logger.h"
#include "wmxSDK_Apdo_Cmn.h"
#include "NDnSAgent_APDO.h"
#include "L5Dispatcher.h"
#include "Act.h"
#include "wimax_osal_services_cmn.h"
#include "wimax_osal_crypt_services.h"		
#include "wimax_osal_string.h"

/********************************************************************************
***********************											*****************
***********************	   Loading Device-Scape DLL				*****************
***********************											*****************
*********************************************************************************/

typedef swc_config_t*	(*EapCconfigAllocFuncPtr)( char*, int);
typedef int				(*EapCconfigResetFuncPtr)( swc_config_t*);
typedef int				(*EapCconfigFreeFuncPtr)( swc_config_t*);
typedef int				(*EapSetCtrlIfcCallbackFuncPtr)( swc_config_t*, void*, void*);
typedef int				(*EapSmInitFuncPtr)(swc_config_t*);
typedef int				(*EapSmSetEapMethodFuncPtr)(swc_config_t*, int);
typedef int				(*EapSetCallBacksFuncPtr)(swc_config_t*, void*, void*, void*, void*, void*, void*, void*);
typedef int				(*EapSmRunFuncPtr)(swc_config_t*);
typedef int				(*EapSmGetResponseFuncPtr)(swc_config_t*, u8*, size_t*);
typedef int				(*EapSetPasswordFuncPtr)(swc_config_t*, char*);
typedef int				(*EapSetIdentityFuncPtr)(swc_config_t*, char*);
typedef int				(*EapSmGetKeyFuncPtr)(swc_config_t*, u8*, size_t*);
typedef int				(*EapSetTlsPrivateKeyFuncPtr)(swc_config_t*, unsigned char*, int , int);
typedef int				(*EapSetTlsCaCertFuncPtr)(swc_config_t*, unsigned char*, int, int);
typedef int				(*EapSetTlsClientCertFuncPtr)(swc_config_t*, unsigned char*, int, int);
typedef int				(*SetTlsMaxSizeFuncPtr)(swc_config_t*, int);
typedef void			(*PrintFuncRegisterFuncPtr)(void (*printfunc)(const char *fmt, ...));
typedef int				(*EapSetPinFuncPtr)(swc_config_t*, char*);
typedef int				(*SetAkaMaxSizeFuncPtr)(swc_config_t*, int);
typedef int				(*SetLogLevelFuncPtr)(int);
typedef void			(*WpaHexdumpPtr)(int, const char *title, const UINT8 *buf, size_t len);
typedef int				(*EapSetTlsPrivateKeyPasswordFuncPtr)(swc_config_t *sc, char *passwd);
typedef int				(*EapSetTlsFunctionTable)(void *table, void *reserved);
typedef int				(*EapSmGetBEKFuncPtr)(swc_config_t*, u8*, size_t);
typedef void			(*WpaLogprocPtr)(int level, char *fmt, ...);

EapSmInitFuncPtr				swc_eap_sm_init_pt; //[findme][amirs] buffer for 64bit
EapSmInitFuncPtr				swc_eap_sm_init_ptr;
EapSmSetEapMethodFuncPtr		swc_set_eap_method_ptr;
EapSmSetEapMethodFuncPtr		swc_set_phase2_method_ptr;
EapSetCtrlIfcCallbackFuncPtr	swc_set_ctrl_iface_callback_ptr;
EapSetCallBacksFuncPtr			swc_eap_sm_set_callbacks_ptr;
EapCconfigAllocFuncPtr			swc_config_alloc_ptr;
EapCconfigResetFuncPtr			swc_config_reset_ptr;
EapSmGetResponseFuncPtr			swc_eap_sm_get_response_ptr;
EapSmRunFuncPtr					swc_eap_sm_run_ptr;
EapSetIdentityFuncPtr			swc_set_identity_ptr;
EapSetIdentityFuncPtr			swc_set_anonymous_identity_ptr;
EapSetPasswordFuncPtr			swc_set_password_ptr;
EapSmGetKeyFuncPtr				swc_eap_sm_get_key_ptr;
EapSetTlsPrivateKeyFuncPtr		swc_set_tls_private_key_ptr;
EapSetTlsPrivateKeyPasswordFuncPtr	swc_set_tls_private_key_passwd_ptr;
EapSetTlsCaCertFuncPtr			swc_set_tls_ca_cert_ptr;
EapSetTlsClientCertFuncPtr		swc_set_tls_client_cert_ptr;
EapSetTlsPrivateKeyFuncPtr		swc_set_tls_private_key2_ptr;
EapSetTlsCaCertFuncPtr			swc_set_tls_ca_cert2_ptr;
EapSetTlsClientCertFuncPtr		swc_set_tls_client_cert2_ptr;
SetTlsMaxSizeFuncPtr			swc_set_tls_max_size_ptr;
PrintFuncRegisterFuncPtr		swc_print_function_register_ptr;
EapSetPinFuncPtr				swc_set_pin_ptr;
SetAkaMaxSizeFuncPtr			swc_set_aka_max_size_ptr;
SetLogLevelFuncPtr				swc_set_log_level_ptr;
EapCconfigFreeFuncPtr			swc_config_free_ptr;
WpaHexdumpPtr					wpa_hexdump_ptr;
WpaLogprocPtr					wpa_logproc_ptr;
EapSetTlsFunctionTable			swc_set_tls_function_table_ptr;
EapSmGetBEKFuncPtr				swc_get_BEK_ptr;

/*************************
*	     Globals         *
**************************/
OSAL_dynlib_t	g_DSlib = NULL;
SupplicantData g_SuppData;
SupplicantData g_SuppData1; //[findme][amirs] buffer for 64bit

SupplicantConfig g_SuppConfig;
SupplicantConfig g_SuppConfig1; //[findme][amirs] buffer for 64bit
UINT8		   g_TargetBuf[L4_MSG_MAX_LENGTH]; // TODO: define the correct const
BOOL		   smRunRequired;
BOOL		   smInitRequired;
static List *indicatorSubscribersList = NULL;

EapSmInitFuncPtr				aaaamirswc_eap_sm_init_ptr; //[findme][amirs] buffer for 64bit

tUtilityFunctions *pUtils;
/*************************
*	     DEFINES         *
**************************/
#define TLS_MAX_SIZE 1300
#define INTERNAL_REQUEST_ID 0 // for posting a request to the messenger in the MessageHandler
#define MAX_SUP_STR_LEN 128


/*****************************************
*	     Internal Functions Declarations *
******************************************/
wmx_Status_t InitSupplicantLibrary(VOID);

Boolean EapGetBool(VOID *ctx, enum eap_bool_var var);
void EapSetBool(void *ctx, enum eap_bool_var  var, Boolean val);
int EapGetInt(VOID *ctx, enum eap_int_var  var);
void EapSetInt(VOID *ctx, enum eap_int_var var, UINT32 val);
UINT8* EapGetReqData(VOID *ctx, size_t * datalen);
int OSAL_Crypt_EapCreateDecryptPass(u8* passwordBuff, size_t * datalen);

VOID SuppCtrlIfcCb(VOID* pContext, UINT32 cb_type, UINT32 cb_subtype);
VOID InitMethodAndPassword();
wmx_Status_t LoadSupplicantLibrary();
void SupAgent_SendIndication( wmx_EventType_t eventType, wmx_CredID_t credID );
void SupAgent_CondEapSMRun();

eSuppRetStatus EapSMRun();
wmx_Status_t CondEapSMInit();
void Sup_PrintTrace(char *sourceStr, char *caption, char *prefix);
void wmxNds_SupOpCodeToStr(SUP_AGENT_CRED_OPCODE supOpCode, char *str, int strLength);
void DS_EapRestart(VOID);
/////////////////////


//************************************************
// Connection Parameters to L5 Layer
//************************************************
static L5_CONNECTION supplicantConnection = NULL;
static tL5DispatcherFunctions *pFuncs;

// TODO: Check if can be removed
//typedef struct _L4_MESSAGE_STRUCT
//{
//	UINT32 messageOpcode;
//	UINT32 bufferLength;
//	UCHAR messageBuffer[0];//the start of the buffer
//} L4_MESSAGE_STRUCT;

/********************************************/

/*static void custom_print_function(const char *fmt, ...)
{

	va_list ap;
	char buf[4096];

	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);

	printf("%s", buf);
}

// dbg
void PrintBuff(UINT8* buf, UINT32 len)
{
	int j, i=0;
	while(len>0)
	{
		if (len<16)
		{
			for (j=0; j<len; j++) printf("%02x ",buf[i++]);
			printf("\n"); break;
		}
		else  // print in lines of 16 values each
		{
			for (j=0; j<16; j++) printf("%02x ",buf[i++]); 	len-=16;
		}
		printf("\n");
	}
}*/


void FinalizeSuppConfig()
{
	FreeIfAllocated(g_SuppConfig.identity);
	FreeIfAllocated(g_SuppConfig.anonidentity);
	FreeIfAllocated(g_SuppConfig.password);
	FreeIfAllocated(g_SuppConfig.cacert);
	FreeIfAllocated(g_SuppConfig.clientcert);
	FreeIfAllocated(g_SuppConfig.privatekey);
	FreeIfAllocated(g_SuppConfig.privatekeypasswd);
	FreeIfAllocated(g_SuppConfig.cacert2);
	FreeIfAllocated(g_SuppConfig.clientcert2);
	FreeIfAllocated(g_SuppConfig.privatekey2);
	FreeIfAllocated(g_SuppConfig.privatekeypasswd2);
	FreeIfAllocated(g_SuppConfig.simreader);
	FreeIfAllocated(g_SuppConfig.simpin);		
	FreeIfAllocated(g_SuppConfig.nai);	
}

// Initialize the supplicant .dll by registering the callbacks
wmx_Status_t InitSupplicantLibrary(VOID)
{
	int rc;	
	BOOL res;
	char answer[MAX_ANSWER_SIZE];
	void *ft;

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: InitSupplicantLibrary (IN)");
	// init DS status variable
	smRunRequired = FALSE;
	smInitRequired = TRUE;

	// init DS data and config holders
	memset(&g_SuppData, 0, sizeof(g_SuppData));
	//memset(&g_SuppConfig, 0, sizeof(g_SuppConfig));
	g_SuppData.sc= swc_config_alloc_ptr("Supplicant agent", SWC_INTERFACE_TYPE_WIMAX); // Supplicant agent is for informational purposes only.

	// DEBUG
	// Possible values: MSG_MSGDUMP, MSG_DEBUG, MSG_INFO, MSG_WARNING, MSG_ERROR
	swc_set_log_level_ptr(MSG_MSGDUMP);
	///////////////////////////////

	if (g_SuppData.sc != NULL)
	{
		// Register get and set callback functions
		rc = swc_eap_sm_set_callbacks_ptr(g_SuppData.sc,
											(void*)EapGetBool, 
											(void*)EapSetBool,
											(void*)EapGetInt, 
											(void*)EapSetInt,
											(void*)EapGetReqData,
											(void*)OSAL_Crypt_EapCreateDecryptPass,		
											&g_SuppData);		
		if (SWC_STATUS_SUCCESS != rc)
		{	
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_eap_sm_set_callbacks_ptr failed");
			return WMX_ST_FAIL;
		}

		// Register callback function for asynchronous supplicant events
		rc = swc_set_ctrl_iface_callback_ptr(g_SuppData.sc, (void*)SuppCtrlIfcCb, g_SuppData.sc);		
		if (SWC_STATUS_SUCCESS != rc)
		{	
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_set_ctrl_iface_callback_ptr failed");
			return WMX_ST_FAIL;
		}		

		// TODO: remove - only for testing
		//InitMethodAndPassword();

		//swc_print_function_register_ptr(custom_print_function);
		//swc_print_function_register_ptr(MSG_DEBUG);


		rc = swc_set_tls_max_size_ptr(g_SuppData.sc, TLS_MAX_SIZE);
		if (SWC_STATUS_SUCCESS != rc)
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_eap_sm_init_ptr failed");
			return WMX_ST_FAIL;
		}		
/******						//rc = swc_set_aka_max_size_ptr(g_SuppData.sc, MAX_PACKET_SIZE); ******/

		//added ability to set TLS function internally\externally
		ft = NULL;
		res = L4Configurations_getTLS_Source(answer);
		if ( (TRUE == res) && (0 == OSAL_stricmp("internal", answer)) )
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE, "Supplicant: TLS source - Internal");			
		}
		else
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE, "Supplicant: TLS source - External");			
			//ft = HardwareTlsImplementation;			
			ft = wmx_GetTlsFunctionTable(1);
		}
		
		if (swc_set_tls_function_table_ptr)
		{
			if (swc_set_tls_function_table_ptr(ft, NULL))
			{
				TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR, "Supplicant: Can not set TLS implementation");
			}
			else
			{
				if (ft)
				{
					TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Using external TLS implementation ");
				}
				else
				{
					TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Using internal TLS implementation ");
				}
			}
		}
		else
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: The SUPPLICANT does not support external TLS implementation");			
		}
		
		
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: InitSupplicantLibrary (OUT)");
	
		return WMX_ST_OK;
	}
	else 
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_config_alloc_ptr failed");
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: InitSupplicantLibrary (OUT)");
		return WMX_ST_FAIL;
	}	
}

// for DEBUG
VOID InitMethodAndPassword()
{
	int rc;
	// For testing - replaces fetching the details from the ND&S agent	
	// Setting eap method, private key and certificate
	// make sure to put certificate files within the running directory
	rc = swc_set_eap_method_ptr(g_SuppData.sc, SWC_EAP_TYPE_TLS);
	rc = swc_set_tls_ca_cert_ptr(g_SuppData.sc,(unsigned char *)"cacert.pem", sizeof("cacerts.pem"), 0);
	rc = swc_set_tls_private_key_ptr(g_SuppData.sc,(unsigned char *)"supplicant_key.pem", sizeof("supplicant_key.pem"), 0);
	rc = swc_set_tls_client_cert_ptr(g_SuppData.sc,(unsigned char *)"supplicant_cert.pem", sizeof("supplicant_cert.pem"), 0);
	//rc = swc_set_tls_max_size_ptr(g_SuppData.sc, TLS_MAX_SIZE);
	rc = swc_set_identity_ptr(g_SuppData.sc, "oriti");
}

wmx_Status_t CondEapSMInit()
{
	int rc;
	if (smInitRequired == TRUE)
	{		
		// Init the state machine
		if(!swc_eap_sm_init_ptr)  //[findme][amirs] 64 bit hack
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_eap_sm_init_ptr is null putting old one");

			swc_eap_sm_init_ptr = aaaamirswc_eap_sm_init_ptr;
}

		if(!swc_eap_sm_init_ptr)
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_eap_sm_init_ptr is null return error");
			return WMX_ST_FAIL;
		}

		rc = swc_eap_sm_init_ptr(g_SuppData.sc);
		if (SWC_STATUS_SUCCESS != rc)
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: swc_eap_sm_init_ptr (CondEapSMInit) failed");
			return WMX_ST_FAIL;
		}
		smInitRequired = FALSE;
	}
	return WMX_ST_OK;
}
/*
* EapSMRun - 
* This function runs the SM and if the SM has generated a response, the function shall retrieve it 
* This function returns: e_SUPP_RESPONSE_AVAILABLE 
*						 e_SUPP_NO_RESPONSE
* Before calling the function set the global variables to the correct values
*/
eSuppRetStatus EapSMRun()
{
	size_t rc = e_SUPP_NO_RESPONSE;

	CondEapSMInit();

	smRunRequired = FALSE;

	// Run The State machine
	swc_eap_sm_run_ptr(g_SuppData.sc);

	// Check for response
	if (EapGetBool(&g_SuppData, EAP_eapResp) == TRUE) 
	{
		g_SuppData.RespBufferSize = RSP_MAX_SIZE;

		/* TODO: currently use static buffer to hold response information, check problems of multi threading */
		rc = swc_eap_sm_get_response_ptr(g_SuppData.sc, g_SuppData.RespBuffer, &g_SuppData.RespBufferSize);
		
		if (rc == SWC_STATUS_BUF_TOO_SMALL)
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Buffer For Response is Too Small");			
		}
		else if (rc != SWC_STATUS_SUCCESS) 
		{
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Failed to get response. Return status: %d",rc);
		}
		else // status is 'success', clear EAP_eapResp flag
		{
			// TODO: Check if it is necessary to clear the EAP_eapResp flag even in case of an error
			EapSetBool(&g_SuppData, EAP_eapResp, FALSE);
			return rc = e_SUPP_RESPONSE_AVAILABLE;
		}
	}

	return rc;
}


// Helper function to get the global variable values. The function is used by the agent and
// as a callback by the supplicant.dll
Boolean EapGetBool(VOID* pContext, enum eap_bool_var var)
{
	SupplicantData* pData  = pContext;
	EAP_SM_Variables* pEap_SMVars = &(pData->EapSmVars);

	switch (var) {
	case EAP_eapSuccess:
		return pEap_SMVars->eapSuccess;
	case EAP_eapRestart:
		return pEap_SMVars->eapRestart;
	case EAP_eapFail:
		return pEap_SMVars->eapFail;
	case EAP_eapResp:
		return pEap_SMVars->eapResp;
	case EAP_eapNoResp:
		return pEap_SMVars->eapNoResp;
	case EAP_eapReq:
		return pEap_SMVars->eapReq;
	case EAP_portEnabled:
		return pEap_SMVars->portEnabled;
	case EAP_altAccept:
		return pEap_SMVars->altAccept;
	case EAP_altReject:
		return pEap_SMVars->altReject;
	}

	return FALSE;
}

// Helper function to set value to the global variables. The function is used by the agent and
// as a callback by the supplicant.dll
void EapSetBool(VOID* pContext,  enum eap_bool_var var, Boolean val)
{
	SupplicantData* pData  = pContext;
	EAP_SM_Variables* pEap_SMVars = &(pData->EapSmVars);

	switch (var) 
	{
	case EAP_eapSuccess:
		pEap_SMVars->eapSuccess = val;
		break;
	case EAP_eapRestart:
		pEap_SMVars->eapRestart = val;
		break;
	case EAP_eapFail:
		pEap_SMVars->eapFail = val;
		break;
	case EAP_eapResp:
		pEap_SMVars->eapResp = val;
		break;
	case EAP_eapNoResp:
		pEap_SMVars->eapNoResp = val;
		break;
	case EAP_eapReq:
		pEap_SMVars->eapReq = val;
		break;
	case EAP_portEnabled:
		pEap_SMVars->portEnabled = val;
		break;
	case EAP_altAccept:
		pEap_SMVars->altAccept = val;
		break;
	case EAP_altReject:
		pEap_SMVars->altReject = val;
		break;
	}
}

// Helper function to get the global variable values. The function is used by the agent and
// as a callback by the supplicant.dll
int EapGetInt(VOID* pContext, enum eap_int_var var)
{
	SupplicantData* pData  = pContext;
	EAP_SM_Variables* pEap_SMVars = &(pData->EapSmVars);

	switch (var) 
	{
	case EAP_idleWhile:
		return pEap_SMVars->idleWhile;
	}

	return 0;
}

// Helper function to set value to the global variables. The function is used by the agent and
// as a callback by the supplicant.dll
void EapSetInt(VOID* pContext, enum eap_int_var var, UINT32 val)
{
	SupplicantData* pData  = pContext;
	EAP_SM_Variables* pEap_SMVars = &(pData->EapSmVars);

	switch (var) 
	{
	case EAP_idleWhile:
		pEap_SMVars->idleWhile = val;
		break;
	}
}

UINT8* EapGetReqData(VOID* pContext, size_t * datalen)
{
	SupplicantData* pData  = pContext;
	EAP_SM_Variables* pEap_SMVars = &(pData->EapSmVars);

	*datalen = pEap_SMVars->eapReqData_len;

	wpa_hexdump_ptr(MSG_DEBUG, "SupAgent: EapGetReqData payload", pEap_SMVars->eapReqData, pEap_SMVars->eapReqData_len);
	return pEap_SMVars->eapReqData;
}

/*
* SuppCtrlIfcCb - Control interface callback 
* @pContext: Pointer to callback context
* @cb_type: Type of callback
* @cb_subtype: Subtype of callback
*
* The function is responsible for receiving requests for credentials or
* events related to the authentication process. The function retrieves credentials and set them in the global variable.
*
*/
VOID SuppCtrlIfcCb(VOID* pContext, UINT32 cb_type, UINT32 cb_subtype)
{
	static char	*identity;
	static char	*password;
	static char	*pin;
	static int passwordLength;
	size_t rc;	

	UNREFERENCED_PARAMETER(pContext);

	if (cb_type == SWC_CALLBACK_TYPE_CREDENTIAL) 
	{		
		switch (cb_subtype) 
		{
		case SWC_CRED_IDENTITY: 				
			smRunRequired = TRUE;			
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_IDENTITY");		
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_IDENTITY);			
			break;
		case SWC_CRED_OTP: 
			//smRunRequired = TRUE;
			//SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_IDENTITY); // future feature
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_OTP");					
			break;
		case SWC_CRED_PASSWORD:
			smRunRequired = TRUE;
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_PASSWORD");
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_PASSWORD);
			break;
		case SWC_CRED_PIN:
			smRunRequired = TRUE;
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_PIN");
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_PIN);
			break;
		case SWC_CRED_NEW_PASSWORD:
			//smRunRequired = TRUE;
			//SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_NEW_PASSWORD); // future feature
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_NEW_PASSWORD");		
			break;
		case SWC_CRED_PASSPHRASE: 
			//smRunRequired = TRUE;
			//SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_PASSPHRASE); // future feature
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_PASSPHRASE");		
			break;			
		case SWC_CRED_PRIVATE_KEY: 
			smRunRequired = TRUE;
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_PRIVATE_KEY");
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_PRIVATE_KEY); // future feature
			break;
		case SWC_CRED_CA_CERTIFICATE:
			smRunRequired = TRUE;
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Credentials Request - SWC_CRED_CA_CERTIFICATE");
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_CREDENTIAL, SWC_CRED_CA_CERTIFICATE); // future feature
			break;
		
		default:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Unknown credential request #%d",cb_subtype);					
			return;
		}
	} 
	else if (cb_type == SWC_CALLBACK_TYPE_EVENT) 
	{		
		switch (cb_subtype) {
		case SWC_EV_EAP_KEY_AVAILABLE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Event - Key available");
			g_SuppData.MskKeyActualLen = MSK_SIZE;
			// the g_SuppData.MskKeyActualLen contains the max allowed size on input and actual size on output
			rc = swc_eap_sm_get_key_ptr(g_SuppData.sc, g_SuppData.MskKey, &g_SuppData.MskKeyActualLen);
			if (rc != SWC_STATUS_SUCCESS) 
			{	
				TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Key was available though failed to retrieve it from supplicant");				
			}
			if (!swc_get_BEK_ptr)
			{
				TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Getting BEK key is not supported by supplicant!");				
			}
			else
			{
				unsigned char buf[16];
				if (swc_get_BEK_ptr(g_SuppData.sc, buf, 16) < 0)
				{
					TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Failed to get BEK key from supplicant!");				
				}
				else
				{
					TRACE(TR_MOD_NDNS_AGENT, TR_SEV_NOTICE,"Supplicant: BEK key - %X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X,%X", buf[0], buf[1], buf[2],
						buf[3], buf[4], buf[5],
						buf[6], buf[7], buf[8],
						buf[9], buf[10], buf[11],
						buf[12], buf[13], buf[14], buf[15]);
					
					SetBEK((wmx_pBEKBuffer_t)buf);
				}
			}
			break;
		case SWC_EV_EAP_SUCCESS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Event - Authentication Successful");
			g_SuppConfig.isValid = FALSE;			
			wmx_SetEapSuccess();
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_EVENT, SWC_EV_EAP_SUCCESS); // send EAP FAIL to the ND&S
			break;
		case SWC_EV_EAP_FAILURE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Event - Authentication failure");
			g_SuppConfig.isValid = FALSE;
			wmx_SetEapFail(); // send EAP FAIL to the device
			SupAgent_SendIndication(SWC_CALLBACK_TYPE_EVENT, SWC_EV_EAP_FAILURE); // send EAP FAIL to the ND&S
			break;
		case SWC_EV_REJECTED_CREDENTIAL:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Rejected Credential ");
			break;
		case SWC_EV_REJECTED_CHALLENGE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Rejected Challenge ");
			break;
		case SWC_EV_REJECTED_CERTIFICATE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Rejected Certificate ");
			break;
		case SWC_EV_REJECTED_IDENTITY:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Rejected Identity ");
			break;
		case SWC_EV_REJECTED_METHOD:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Rejected Method ");
			break;
		case SWC_EV_RESTRICTED_LOGON_HOURS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Restricted Logon Hours");
			break;
		case SWC_EV_ACCOUNT_DISABLED:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Account Disabled ");
			break;
		case SWC_EV_ACCOUNT_NO_DIAL_IN:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Account no dial-in ");
			break;
		case SWC_EV_TLV_INVALID:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: TLV Invalid ");
			break;
		case SWC_EV_TLV_UNKNOWN:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: TLV Unknown ");
			break;
		case SWC_EV_TLV_NAK:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: TLV NAK ");		
			break;
		case SWC_EV_FAST_CMAC_INVALID:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: FAST Compound MAC Invalid");
			break;
		case SWC_EV_FAST_PROVISION_SUCCESS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: FAST Provision Success");
			break;
		case SWC_EV_FAST_INVALID_PAC_KEY:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: FAST Invalid PAC Key");
			break;
		case SWC_EV_FAST_INVALID_PAC_OPAQUE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: FAST Invalid PAC Opaque");
			break;
		case SWC_EV_EAP_CLEAR_TEXT_SUCCESS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: EAP Clear Text Success");
			break;
		case SWC_EV_EAP_CLEAR_TEXT_FAILURE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: EAP Clear Text Failure");
			break;
		case SWC_EV_EAP_INTERMEDIATE_SUCCESS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: EAP Intermediate Success");
			break;
		case SWC_EV_EAP_INTERMEDIATE_FAILURE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: EAP Intermediate Failure");
			break;
		case SWC_EV_SIM_PIN_INCORRECT:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: SIM PIN Incorrect ");
			break;
		case SWC_EV_SIM_PIN_REQUIRED:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: SIM PIN Required");
			break;
		case SWC_EV_SIM_NO_READER:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: SIM No Reader");
			break;
		case SWC_EV_SIM_NO_CARD:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: SIM No Card");
			break;
		case SWC_EV_SIM_FAILURE:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: SIM Failure");
			break;
		///////////////////
		case SWC_EV_EAP_METHOD_TLS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting TLS method");
			break;
		case SWC_EV_EAP_METHOD_TTLS:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting TTLS method");
			break;
		case SWC_EV_EAP_METHOD_PEAP:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting PEAP method");
			break;
		case SWC_EV_EAP_METHOD_SIM:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting SIM method");
			break;
		case SWC_EV_EAP_METHOD_AKA:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting AKA method");
			break;
		case SWC_EV_EAP_METHOD_PSK:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting PSK method");
			break;
		case SWC_EV_EAP_METHOD_LEAP:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting LEAP method");
			break;
		case SWC_EV_EAP_METHOD_FAST:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: supporting FAST method");
			break;
		//////////////////
		default:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Unknown event type %d", cb_subtype);			
			break;
		}
	} 
	else 
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Unknown callback type %d", cb_type);
	}
}



void DS_EapRestart(VOID)
{
	memset(g_SuppData.MskKey,0,MSK_SIZE);

	g_SuppData.EapSmVars.eapRestart=TRUE;
	g_SuppData.EapSmVars.portEnabled = FALSE;
	EapSMRun();
	g_SuppData.EapSmVars.portEnabled = TRUE;

}

void ResetSupplicantLibrary()
{
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Reset library - start");
	if (g_SuppData.sc != NULL)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Reset library - erasing DS context");
		swc_config_reset_ptr(g_SuppData.sc);
		swc_config_free_ptr(g_SuppData.sc);
		g_SuppData.sc = NULL;
	}
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Reset library - erasing last eap request data");
	FreeIfAllocated(g_SuppData.EapSmVars.eapReqData);
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Reset library - end");
}
/*******************************************/

void FinalizeSupplicantLibrary()
{	
	ResetSupplicantLibrary();
	if (g_DSlib != NULL)
	{
		OSAL_close_lib(g_DSlib);
		g_DSlib = NULL;
	}	
	FinalizeSuppConfig();
}

wmx_Status_t LoadSupplicantLibrary()
{
	char str[MAX_PATH];
	UINT32 err;

	L4Configurations_getSupplicantLibName(str);
	
	// make sure to put supplicant.dll under the running dirctory
	g_DSlib = OSAL_load_lib(str);
	if( g_DSlib == NULL ) 
	{
		err = GetLastError();
		OSAL_sprintf_s(str, MAX_PATH,"Device-Scape library failed to be loaded (LastError=%d)", err);
		OSAL_EventLogger_Log(EVENTLOG_ERROR_TYPE, (char *)str);
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: %s", str);
		return WMX_ST_CONFIG_ERROR;
	}

	swc_eap_sm_init_ptr = (EapSmInitFuncPtr)OSAL_find_symbol(g_DSlib,"swc_eap_sm_init");
	swc_set_eap_method_ptr = (EapSmSetEapMethodFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_eap_method");
	swc_set_phase2_method_ptr = (EapSmSetEapMethodFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_phase2_method");
	swc_set_ctrl_iface_callback_ptr = (EapSetCtrlIfcCallbackFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_ctrl_iface_callback");
	swc_eap_sm_set_callbacks_ptr = (EapSetCallBacksFuncPtr)OSAL_find_symbol(g_DSlib,"swc_eap_sm_set_callbacks");
	swc_config_alloc_ptr = (EapCconfigAllocFuncPtr)OSAL_find_symbol(g_DSlib,"swc_config_alloc");
	swc_config_reset_ptr = (EapCconfigResetFuncPtr)OSAL_find_symbol(g_DSlib,"swc_config_reset");
	swc_config_free_ptr = (EapCconfigFreeFuncPtr)OSAL_find_symbol(g_DSlib,"swc_config_free");
	swc_eap_sm_get_response_ptr = (EapSmGetResponseFuncPtr)OSAL_find_symbol(g_DSlib,"swc_eap_sm_get_response");
	swc_eap_sm_run_ptr = (EapSmRunFuncPtr)OSAL_find_symbol(g_DSlib,"swc_eap_sm_run");
	swc_set_identity_ptr = (EapSetIdentityFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_identity");
	swc_set_anonymous_identity_ptr = (EapSetIdentityFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_anonymous_identity");
	swc_set_password_ptr = (EapSetPasswordFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_password");
	swc_eap_sm_get_key_ptr = (EapSmGetKeyFuncPtr)OSAL_find_symbol(g_DSlib,"swc_eap_sm_get_key");
	swc_set_tls_private_key_ptr = (EapSetTlsPrivateKeyFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_private_key");
	swc_set_tls_private_key_passwd_ptr = (EapSetTlsPrivateKeyPasswordFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_private_key_passwd");
	swc_set_tls_ca_cert_ptr = (EapSetTlsCaCertFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_ca_cert");
	swc_set_tls_client_cert_ptr = (EapSetTlsClientCertFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_client_cert");
	swc_set_tls_private_key2_ptr = (EapSetTlsPrivateKeyFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_private_key2");
	swc_set_tls_ca_cert2_ptr = (EapSetTlsCaCertFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_ca_cert2");
	swc_set_tls_client_cert2_ptr = (EapSetTlsClientCertFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_client_cert2");
	swc_set_tls_max_size_ptr = (SetTlsMaxSizeFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_tls_max_size");
	swc_print_function_register_ptr = (PrintFuncRegisterFuncPtr)OSAL_find_symbol(g_DSlib, "swc_print_function_register");
	swc_set_pin_ptr = (EapSetPinFuncPtr)OSAL_find_symbol(g_DSlib,"swc_set_sim_pin");
	swc_set_log_level_ptr = (SetLogLevelFuncPtr)OSAL_find_symbol(g_DSlib, "swc_set_log_level");
	wpa_hexdump_ptr = (WpaHexdumpPtr)OSAL_find_symbol(g_DSlib, "wpa_hexdump");
	wpa_logproc_ptr = (WpaLogprocPtr)OSAL_find_symbol(g_DSlib, "wpa_printf");
	//swc_set_aka_max_size_ptr = (SetAkaMaxSizeFuncPtr)OSAL_find_symbol(g_DSlib, "swc_set_aka_max_size");
	swc_set_tls_function_table_ptr = (EapSetTlsFunctionTable)OSAL_find_symbol(g_DSlib, "swc_config_use_external_tls");
swc_get_BEK_ptr = (EapSmGetBEKFuncPtr)OSAL_find_symbol(g_DSlib, "swc_eap_get_BEK_data");
aaaamirswc_eap_sm_init_ptr =swc_eap_sm_init_ptr;  //[findme][amirs] buffer for 64bit
	return WMX_ST_OK;
}

void SupAgent_SendEapResponse()
{
	UINT8 targetBuffer[L4_MSG_MAX_LENGTH];

	memcpy((void*)targetBuffer, (void*)g_SuppData.RespBuffer, g_SuppData.RespBufferSize);

	OSAL_MyPrintf("Sending EapResponse. Data size: %d\n", g_SuppData.RespBufferSize);
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: EAP_RESP_DATA was sent to Driver. Buffer length: %d", g_SuppData.RespBufferSize);
	wmx_CmdSendEapResponse(g_SuppData.RespBufferSize, (wmx_pEapMessage_t)targetBuffer);
}
//*******************************************
// Used to receive an EAP request, pass it
// to DS and send an EapResponse if required
//*******************************************
void WMX_EXT_CALL_CONV SupAgent_EapRequestAvailable( wmx_EapMsgLength_t	eapMsgLen, wmx_pEapMessage_t pEapMsg )
{	
	int rc;

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: EAP request available (size: %d)", eapMsgLen);
	if (!g_SuppConfig.isEnabled)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_WARNING,"Supplicant: EAP request available, Supplicant disabled. Request discarded");
		return;
	}
	if((void*)pEapMsg == NULL)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: EAP request available, NULL buffer was received");	
		return;
	}		

	if (!g_SuppConfig.isValid)
	{
		// Reset Identity:			
		SupAgent_ResetSupplicant(); 		
	}

	OSAL_MyPrintf("EapRequest received. Data size: %d\n", eapMsgLen);
	rc = CondEapSMInit();

	if (rc != WMX_ST_OK) // sm init error
	{
		return;
	}

	FreeIfAllocated(g_SuppData.EapSmVars.eapReqData);
	g_SuppData.EapSmVars.eapReqData = (UINT8*)malloc(eapMsgLen);
	if (g_SuppData.EapSmVars.eapReqData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL,"SupAgent_EapRequestAvailable: malloc failed");
		return;
	}

	memcpy((void*)g_SuppData.EapSmVars.eapReqData, (void*)pEapMsg, eapMsgLen);
	//g_SuppData.EapSmVars.eapReqData = (UINT8*)pEapMsg;
	g_SuppData.EapSmVars.eapReqData_len  = eapMsgLen;
	g_SuppData.EapSmVars.eapReq = TRUE;

	rc = EapSMRun();	

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: EAP request available OUT (response: %s)", 
				(rc == e_SUPP_RESPONSE_AVAILABLE) ? "yes" : "no");

	// Check if a response from the supplicant.dll came
	if (rc == e_SUPP_RESPONSE_AVAILABLE)
	{
		SupAgent_SendEapResponse();
	}

}

//*******************************************
// Used to receive an alternative EAP success
// and pass it to DS
//*******************************************
void WMX_EXT_CALL_CONV SupAgent_AlternativeEapSuccess()
{
	int rc;
	rc = CondEapSMInit();
	if (rc != WMX_ST_OK) // sm init error
	{
		return;
	}
	g_SuppData.EapSmVars.altAccept=TRUE;
	EapSMRun();
	g_SuppConfig.isValid = FALSE;
}

//*******************************************
// Used to receive an EAP key request
// (get key) and send the key to the driver
//*******************************************
void WMX_EXT_CALL_CONV SupAgent_EapKeyRequest()
{
	//TODO
	UINT8 targetBuffer[L4_MSG_MAX_LENGTH];

	memcpy((void*)targetBuffer, g_SuppData.MskKey, g_SuppData.MskKeyActualLen);
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: EAP_SET_KEY was sent to Driver. Buffer length: %d", g_SuppData.MskKeyActualLen);

	wmx_SetEapKey (g_SuppData.MskKeyActualLen, (wmx_pEapKey_t)targetBuffer);
}

//*******************************************//

wmx_Status_t SupAgent_RegisterCallbacksOnWrapper()
{
	wmx_Status_t status;
	status = wmx_RegisterEapRequestAvailableCB(&SupAgent_EapRequestAvailable);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterAlternativeEapSuccessCB(&SupAgent_AlternativeEapSuccess);
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_RegisterEapKeyRequestCB(&SupAgent_EapKeyRequest);
	if ( WMX_ST_OK != status )
	{
		return status;
	}	

	status = wmx_RegisterEapRestartRequestCB(&SupAgent_ResetSupplicant);
	if ( WMX_ST_OK != status )
	{
		return status;
	}	
	return status;
}

wmx_Status_t SupAgent_UnRegisterCallbacksOnWrapper()
{
	wmx_Status_t status;
	status = wmx_UnregisterEapRequestAvailableCB();
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_UnregisterAlternativeEapSuccessCB();
	if ( WMX_ST_OK != status )
	{
		return status;
	}
	status = wmx_UnregisterEapKeyRequestCB();
	if ( WMX_ST_OK != status )
	{
		return status;
	}	
	status = wmx_UnregisterEapRestartRequestCB();
	if ( WMX_ST_OK != status )
	{
		return status;
	}	
	return status;
}

//*******************************************
// Used to register a Target on Indication.
//*******************************************
wmx_Status_t SupAgent_RegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id)
{
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(indicatorSubscribersList, status_indication_id, TRUE);

	if(indSubscribers == NULL)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_CRITICAL,"INTERNAL_PROBLEM: Errot registering indicator;  indSubscribers == NULL");
		pFuncs->pfnSendErrorReport(L5_TARGET_SUPPLICANT, INTERNAL_PROBLEM, __FUNCTION__, __LINE__);
		return WMX_ST_FAIL;
	}

	Indications_AddSubscriber(indSubscribers, nOriginID);
	//Perform actions according to size of list and subscriber addition
	return WMX_ST_OK;
}

//*******************************************
// Used to unregister a Target from an Indication
//*******************************************
wmx_Status_t SupAgent_UnRegisterIndicator(L5_TARGET_ID nOriginID, UINT32 status_indication_id)
{
	IndicatorSubscribers *indSubscribers = GetIndicatorSubscribers(indicatorSubscribersList, status_indication_id, FALSE);

	if ((NULL == indSubscribers) || (!Indications_RemoveSubscriber(indSubscribers, nOriginID)))
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: UnRegisterIndicator Failed(TargetId=%d, indication_id=0x%x)", nOriginID, status_indication_id);
		//return WMX_ST_FAIL;
	}
	//Perform actions according to size of list and subscriber removal
	return WMX_ST_OK;	
}

//*******************************************
// Used to send a supplicant event indication
//*******************************************
void SupAgent_SendIndication( wmx_EventType_t eventType, wmx_CredID_t credId)
{
	wmx_SupEvent_t event;
	SendIndData *pSendIndData;
	pSUP_MESSAGE eventMessage;
	UINT32 bufferSize;
	UINT32 messageSize;
	UINT32 indDataSize;

	event.eventType = eventType;
	event.credId = credId;
	
	// allocate the indication data
	bufferSize = sizeof(wmx_SupEvent_t);
	messageSize = sizeof(SUP_MESSAGE_HEADER) + bufferSize;
	indDataSize = sizeof(SendIndData) + messageSize;
	pSendIndData = (SendIndData *)malloc(indDataSize);
	if (pSendIndData == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL,"SupAgent_SendIndication: malloc failed");
		return;
	}

	eventMessage = (pSUP_MESSAGE)pSendIndData->indication_buffer;

	// fill the indication data
	pSendIndData->pSenderFuncs = pFuncs;
	pSendIndData->senderL5Conn = supplicantConnection;
	pSendIndData->pSubscribersList = indicatorSubscribersList;
	pSendIndData->indication_id = SUP_OPCODE_IND_EVENT;
	eventMessage->header.opcode = SUP_OPCODE_IND_EVENT;
	eventMessage->header.bufferLength = bufferSize;
	*(wmx_pSupEvent_t)(eventMessage->buf) = event;

	// send the indication
	pUtils->tpfnPostRequest(
		MEDIUM, SUP_OPCODE_INDICATION_ARRIVED, pSendIndData, indDataSize, &SendIndicationToSubscribers);
	
	free(pSendIndData);
}

//************************************************
// Unregister L5 Target from indications lists.
//************************************************
void SupAgent_UnRegisterL5Target(L5_TARGET_ID targetID)
{
	// Iterate the status indication list, for each indicator - remove the target ID:
	IndicatorSubscribers *indSubscribers;
	ListItem* handle;

	handle = CreateIterator(indicatorSubscribersList);
	handle = Iterator_GetNext(indicatorSubscribersList, handle, &indSubscribers);
	while (handle)
	{
		Indications_RemoveSubscriber(indSubscribers, targetID);
		handle = Iterator_GetNext(indicatorSubscribersList, handle, &indSubscribers);
	}
	FreeIterator(indicatorSubscribersList);
}

//******************************************//
// helper functions
char *SupAgent_ExtractString(void *pvSentBuffer)
{
	pSUP_MESSAGE msg = (pSUP_MESSAGE)pvSentBuffer;
	char *str = (char*)msg->buf;	
	char *resultStr = (char*)malloc(OSAL_strnlen(str, MAX_STRING_VALIDATE) + 1);
	if (resultStr == NULL)
	{
		TRACE(TR_MOD_NDNS_AGENT, TR_SEV_CRITICAL,"malloc failed");
		return NULL;
	}

	OSAL_strcpy_s(resultStr, OSAL_strnlen(str, MAX_STRING_VALIDATE) + 1,str);

	return resultStr;
}




UINT32 SupAgent_ExtractUnsignedInt(void *pvSentBuffer)
{
	pSUP_MESSAGE msg = (pSUP_MESSAGE)pvSentBuffer;
	return *(UINT32*)msg->buf;
}

INT32 SupAgent_ExtractInt(void *pvSentBuffer)
{
	pSUP_MESSAGE msg = (pSUP_MESSAGE)pvSentBuffer;
	return *(INT32*)msg->buf;
}

// Conditional sm run order
void SupAgent_CondEapSMRun()
{
	int rc;

	if (smRunRequired == TRUE)
	{					
		rc = EapSMRun();
		// Check if a response from the supplicant.dll came
		if (rc == e_SUPP_RESPONSE_AVAILABLE)
		{
			SupAgent_SendEapResponse();
		}
	}
}


//*******************************************
// AppSrv Agent Interface - start
//*******************************************


// AppSrv Agent Interface - Initialize
void Supplicant_EventHandler( 
							 L5_CONNECTION Conn,
							 L5_EVENT eEvent,
							 void *pvEventData,
							 void *pvUserContext )
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"%s L5 event received", L5_EVENT_STR(eEvent));

	// Unregister all indications that were registered on the agent
	if (L5_EVENT_DRIVER_DISCONNECTED == eEvent)
	{	
		// clean all indications' targets
		EmptyIndicatorsList(&indicatorSubscribersList);
	}	
}


void  Supplicant_InternalHandler( UINT32 internalRequestID, void *buffer, UINT32 bufferLength )
{
	pSUP_MESSAGE_HEADER msg = (pSUP_MESSAGE_HEADER)buffer;	
	char prefix[MAX_SUP_STR_LEN] ="Assign configuration";
	BOOL isValid = g_SuppConfig.isValid;

	UNREFERENCED_PARAMETER(bufferLength);
	UNREFERENCED_PARAMETER(internalRequestID);

	// by default - setting a value to the supplicant will cause a restart request.
	// the only case where a restart is not required is if this message was illegal (see "default" section below)
	g_SuppConfig.isValid = FALSE;

	switch (msg->opcode)
	{
		case SUP_OPCODE_SET_IDENTITY:
			FreeIfAllocated(g_SuppConfig.identity);
			g_SuppConfig.identity = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.identity,"Identity", prefix);
			swc_set_identity_ptr(g_SuppData.sc, g_SuppConfig.identity);
			SupAgent_CondEapSMRun();			
			break;
		case SUP_OPCODE_SET_ANONYMOUS_IDENTITY:
			FreeIfAllocated(g_SuppConfig.anonidentity);
			g_SuppConfig.anonidentity = SupAgent_ExtractString(buffer);	
			Sup_PrintTrace(g_SuppConfig.anonidentity,"OuterIdentity", prefix);
			swc_set_anonymous_identity_ptr(g_SuppData.sc, g_SuppConfig.anonidentity);
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_PASSWORD:
			FreeIfAllocated(g_SuppConfig.password);
			g_SuppConfig.password = SupAgent_ExtractString(buffer);	
			Sup_PrintTrace(g_SuppConfig.password,"Password", prefix);
			swc_set_password_ptr(g_SuppData.sc, g_SuppConfig.password);
			SupAgent_CondEapSMRun();
			break;
		//case SUP_OPCODE_SET_NEW_PASSWORD:
		//	break;
		case SUP_OPCODE_SET_EAP_METHOD:
			g_SuppConfig.eapmethod = SupAgent_ExtractUnsignedInt(buffer); 
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: %s - EapMethod = %d", prefix, g_SuppConfig.eapmethod);
			swc_set_eap_method_ptr(g_SuppData.sc, g_SuppConfig.eapmethod);
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_PHASE2_METHOD:
			g_SuppConfig.phase2 = SupAgent_ExtractUnsignedInt(buffer);
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: %s - Phase2 method = %d", prefix, g_SuppConfig.phase2);
			swc_set_phase2_method_ptr(g_SuppData.sc, g_SuppConfig.phase2);
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_TLS_CA_CERT:
			FreeIfAllocated(g_SuppConfig.cacert);
			g_SuppConfig.cacert = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.cacert,"CA cert", prefix);
			swc_set_tls_ca_cert_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.cacert, (int)OSAL_strnlen(g_SuppConfig.cacert, MAX_STRING_VALIDATE) + 1, 0);
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_TLS_CA_CERT2:
			FreeIfAllocated(g_SuppConfig.cacert2);
			g_SuppConfig.cacert2 = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.cacert2,"CA cert - phase2", prefix);
			swc_set_tls_ca_cert2_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.cacert2, (int)OSAL_strnlen(g_SuppConfig.cacert2, MAX_STRING_VALIDATE) + 1, 0);			
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_TLS_CLIENT_CERT:
			FreeIfAllocated(g_SuppConfig.clientcert);
			g_SuppConfig.clientcert = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.clientcert,"Client cert", prefix);
			swc_set_tls_client_cert_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.clientcert, (int)OSAL_strnlen(g_SuppConfig.clientcert, MAX_STRING_VALIDATE) + 1, 0);			
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_TLS_CLIENT_CERT2:
			FreeIfAllocated(g_SuppConfig.clientcert2);
			g_SuppConfig.clientcert2 = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.clientcert2,"Client cert - phase2", prefix);
			swc_set_tls_client_cert2_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.clientcert2, (int)OSAL_strnlen(g_SuppConfig.clientcert2, MAX_STRING_VALIDATE) + 1, 0);
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_TLS_PRIVATE_KEY:
			FreeIfAllocated(g_SuppConfig.privatekey);
			g_SuppConfig.privatekey = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.privatekey,"Private key", prefix);
			swc_set_tls_private_key_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.privatekey, (int)OSAL_strnlen(g_SuppConfig.privatekey, MAX_STRING_VALIDATE) + 1, 0);			
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD:
			FreeIfAllocated(g_SuppConfig.privatekeypasswd);
			g_SuppConfig.privatekeypasswd = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.privatekeypasswd,"Private key password", prefix);	
			swc_set_tls_private_key_passwd_ptr(g_SuppData.sc, (char *)g_SuppConfig.privatekeypasswd);			
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;

		case SUP_OPCODE_SET_TLS_PRIVATE_KEY2:
			FreeIfAllocated(g_SuppConfig.privatekey2);
			g_SuppConfig.privatekey2 = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.privatekey2,"Private key password - phase2", prefix);
			swc_set_tls_private_key2_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.privatekey2, (int)OSAL_strnlen(g_SuppConfig.privatekey2, MAX_STRING_VALIDATE) + 1, 0);
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		//case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD:
		//	break;
		//case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD2:
		//	break;
		case SUP_OPCODE_SET_PIN:
			FreeIfAllocated(g_SuppConfig.simpin);
			g_SuppConfig.simpin = SupAgent_ExtractString(buffer);
			Sup_PrintTrace(g_SuppConfig.simpin,"PIN", prefix);
			swc_set_pin_ptr(g_SuppData.sc, g_SuppConfig.simpin);
			smInitRequired = TRUE; // TODO: check if it's needed
			SupAgent_CondEapSMRun();
			break;
		//case SUP_OPCODE_SET_PIN_MAX_SIZE:
		//  break;
		case SUP_OPCODE_SET_TLS_MAX_SIZE:
			swc_set_tls_max_size_ptr(g_SuppData.sc, SupAgent_ExtractInt(buffer));
			smInitRequired = TRUE;
			SupAgent_CondEapSMRun();
			break;
		default:
			g_SuppConfig.isValid = isValid; // return to previous value in case this was not a set command
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Unknown SET message received");
			break;
	}	
}

// AppSrv Agent Interface - MessagesHandler
void Supplicant_MessagesHandler(L5_CONNECTION Conn,
								L5_TARGET_ID nOriginID,

								UINT32 dwSentMessageID,
								void  *pvSentBuffer,
								UINT32 cbSentBufferSize,

								UINT32 *pdwResponseMessageID,
								void  *pvResponseBuffer,
								UINT32 *cbResponseBufferSize,

								void *pvUserContext,
								void *pvReserved )
{
	wmx_Status_t status;
	pSUP_MESSAGE_HEADER msg;
	char opCodeStr[MAX_SUP_STR_LEN] ="";
	
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbResponseBufferSize);
	UNREFERENCED_PARAMETER(pvResponseBuffer);
	UNREFERENCED_PARAMETER(Conn);

	msg = (pSUP_MESSAGE_HEADER)pvSentBuffer;
	switch (dwSentMessageID)
	{
		case SUP_OPCODE_REGISTER_INDICATION:
			status = SupAgent_RegisterIndicator(nOriginID, *(UINT32*)pvSentBuffer);
			if (NULL != pdwResponseMessageID)
			{
				*pdwResponseMessageID = status;
			}
			break;
		case SUP_OPCODE_UNREGISTER_INDICATION:
			status = SupAgent_UnRegisterIndicator(nOriginID, *(UINT32*)pvSentBuffer);
			if (NULL != pdwResponseMessageID)
			{
				*pdwResponseMessageID = status;
			}
			break;
		case SUP_OPCODE_ENABLE:
			g_SuppConfig.isEnabled = TRUE;
			*pdwResponseMessageID = WMX_ST_OK;
			break;
		case SUP_OPCODE_DISABLE:
			g_SuppConfig.isEnabled = FALSE;
			*pdwResponseMessageID = WMX_ST_OK;
			break;		
		case SUP_OPCODE_SET:
			wmxNds_SupOpCodeToStr(msg->opcode, opCodeStr, MAX_SUP_STR_LEN - 1);
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: SET request received - %s", opCodeStr);
			switch (msg->opcode)
			{
				case SUP_OPCODE_SET_IDENTITY:
				case SUP_OPCODE_SET_ANONYMOUS_IDENTITY:
				case SUP_OPCODE_SET_PASSWORD:
				//case SUP_OPCODE_SET_NEW_PASSWORD:
				case SUP_OPCODE_SET_EAP_METHOD:
				case SUP_OPCODE_SET_PHASE2_METHOD:
				case SUP_OPCODE_SET_TLS_CA_CERT:					
				case SUP_OPCODE_SET_TLS_CA_CERT2:					
				case SUP_OPCODE_SET_TLS_CLIENT_CERT:					
				case SUP_OPCODE_SET_TLS_CLIENT_CERT2:					
				case SUP_OPCODE_SET_TLS_PRIVATE_KEY:					
				case SUP_OPCODE_SET_TLS_PRIVATE_KEY2:					
				case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD:					
				//case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD2:
				case SUP_OPCODE_SET_PIN:
				//case SUP_OPCODE_SET_PIN_MAX_SIZE:
				case SUP_OPCODE_SET_TLS_MAX_SIZE:
				{				
					pUtils->tpfnPostRequest(	
						MEDIUM, msg->opcode, pvSentBuffer, cbSentBufferSize, &Supplicant_InternalHandler );
					if (NULL != pdwResponseMessageID)
					{
						*pdwResponseMessageID = WMX_ST_OK;
					}
					break;
				}
				default:
					TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Unknown SET message received");
					if (NULL != pdwResponseMessageID)
					{
					*pdwResponseMessageID = WMX_ST_FAIL;
					}
					break;
				}
				break;
		case SUP_OPCODE_RESET:
			// Perform the following actions:
			// Erase/Free previous credentials that might have been set in the config context before.
			// Restart the supplicant with empty context to be assigned later on. (Will erase the supplicant context itself)
			{
				TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO, "Supplicant: SUP_OPCODE_RESET received");
				FinalizeSuppConfig();
				SupAgent_ResetSupplicant();
				*pdwResponseMessageID = WMX_ST_OK;
				break;
			}
		default:
			TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Unknown message received");
			if (NULL != pdwResponseMessageID)
			{
				*pdwResponseMessageID = WMX_ST_FAIL;
			}
			break;
	}
}

void Sup_PrintTrace(char *sourceStr, char *caption, char *prefix)
{
	#define MAX_TEMP_STR_LEN 1024

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: %s - %s = %s", prefix, caption, sourceStr);
}

void ReassignSupConfig()
{
	char prefix[MAX_SUP_STR_LEN] ="Reassign configuration";

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: Reassign configuration - start");
	if (g_SuppConfig.identity)
	{
		Sup_PrintTrace(g_SuppConfig.identity,"Identity", prefix);
		swc_set_identity_ptr(g_SuppData.sc, g_SuppConfig.identity);
	}
	if (g_SuppConfig.anonidentity)
	{
		Sup_PrintTrace(g_SuppConfig.anonidentity,"OuterIdentity", prefix);		
		swc_set_anonymous_identity_ptr(g_SuppData.sc, g_SuppConfig.anonidentity);
	}
	if (g_SuppConfig.password)
	{
		Sup_PrintTrace(g_SuppConfig.password,"Password", prefix);		
		swc_set_password_ptr(g_SuppData.sc, g_SuppConfig.password);
	}
	if (g_SuppConfig.eapmethod)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: %s - EapMethod = %d", prefix, g_SuppConfig.eapmethod);
		swc_set_eap_method_ptr(g_SuppData.sc, g_SuppConfig.eapmethod);
	}
	if (g_SuppConfig.phase2)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: %s - Phase2 method = %d", prefix, g_SuppConfig.phase2);
		swc_set_phase2_method_ptr(g_SuppData.sc, g_SuppConfig.phase2);
	}
	if (g_SuppConfig.cacert)
	{
		Sup_PrintTrace(g_SuppConfig.cacert,"CA cert", prefix);
		swc_set_tls_ca_cert_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.cacert, (int)OSAL_strnlen(g_SuppConfig.cacert, MAX_STRING_VALIDATE) + 1, 0);			
	}
	if (g_SuppConfig.cacert2)
	{
		Sup_PrintTrace(g_SuppConfig.cacert2,"CA cert - phase2", prefix);		
		swc_set_tls_ca_cert2_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.cacert2, (int)OSAL_strnlen(g_SuppConfig.cacert2, MAX_STRING_VALIDATE) + 1, 0);			
	}
	if (g_SuppConfig.clientcert)
	{
		Sup_PrintTrace(g_SuppConfig.clientcert,"Client cert", prefix);		
		swc_set_tls_client_cert_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.clientcert, (int)OSAL_strnlen(g_SuppConfig.clientcert, MAX_STRING_VALIDATE) + 1, 0);
	}
	if (g_SuppConfig.clientcert2)
	{
		Sup_PrintTrace(g_SuppConfig.clientcert2,"Client cert - phase2", prefix);
		swc_set_tls_client_cert2_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.clientcert2, (int)OSAL_strnlen(g_SuppConfig.clientcert2, MAX_STRING_VALIDATE) + 1, 0);
	}
	if (g_SuppConfig.privatekey)
	{
		Sup_PrintTrace(g_SuppConfig.privatekey,"Private key", prefix);		
		swc_set_tls_private_key_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.privatekey, (int)OSAL_strnlen(g_SuppConfig.privatekey, MAX_STRING_VALIDATE) + 1, 0);
	}
	if (g_SuppConfig.privatekeypasswd)
	{
		Sup_PrintTrace(g_SuppConfig.privatekeypasswd,"Private key password", prefix);		
		swc_set_tls_private_key_passwd_ptr(g_SuppData.sc, (char *)g_SuppConfig.privatekeypasswd);
	}
	if (g_SuppConfig.privatekey2)
	{
		Sup_PrintTrace(g_SuppConfig.privatekey2,"Private key password - phase2", prefix);		
		swc_set_tls_private_key2_ptr(g_SuppData.sc, (unsigned char *)g_SuppConfig.privatekey2, (int)OSAL_strnlen(g_SuppConfig.privatekey2, MAX_STRING_VALIDATE) + 1, 0);
	}
	if (g_SuppConfig.simpin)
	{
		Sup_PrintTrace(g_SuppConfig.simpin,"PIN", prefix);		
		swc_set_pin_ptr(g_SuppData.sc, g_SuppConfig.simpin);
	}
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_NOTICE,"Supplicant: Reassign configuration - end");
}


void SupAgent_ResetSupplicant()
{
	if (!g_SuppConfig.isEnabled)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_WARNING,"Supplicant: Reset - Supplicant disabled. Request discarded");
		return;
	}
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Reset - start");
	ResetSupplicantLibrary();	
	InitSupplicantLibrary();
	ReassignSupConfig();
	g_SuppConfig.isValid = TRUE;

	// Reassigning new TTLS Identity in TTLS case. Otherwise - Original TLS Identity will be assigned
	//SupAgent_RefreshIdentity();
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Reset - end");
}

void wmxNds_SupOpCodeToStr(SUP_AGENT_CRED_OPCODE supOpCode, char *str, int strLength)
{
	switch (supOpCode)
	{
	case SUP_OPCODE_SET_IDENTITY:
		OSAL_strncpy_s(str, strLength,"Set identity", strLength);
		break;
	case SUP_OPCODE_SET_ANONYMOUS_IDENTITY:
		OSAL_strncpy_s(str, strLength,"Set outer identity", strLength);
		break;
	case SUP_OPCODE_SET_PASSWORD:
		OSAL_strncpy_s(str, strLength,"Set password", strLength);
		break;
	case SUP_OPCODE_SET_NEW_PASSWORD:
		OSAL_strncpy_s(str, strLength,"set new password", strLength);
		break;
	case SUP_OPCODE_SET_EAP_METHOD:
		OSAL_strncpy_s(str, strLength,"Set EAP method", strLength);
		break;
	case SUP_OPCODE_SET_PHASE2_METHOD:
		OSAL_strncpy_s(str, strLength,"Set EAP method - phase 2", strLength);
		break;
	case SUP_OPCODE_SET_TLS_CA_CERT:
		OSAL_strncpy_s(str, strLength,"Set CA cert", strLength);
		break;
	case SUP_OPCODE_SET_TLS_CA_CERT2:
		OSAL_strncpy_s(str, strLength,"Set CA cert - phase 2", strLength);
		break;
	case SUP_OPCODE_SET_TLS_CLIENT_CERT:
		OSAL_strncpy_s(str, strLength,"Set client cert", strLength);
		break;
	case SUP_OPCODE_SET_TLS_CLIENT_CERT2:
		OSAL_strncpy_s(str, strLength,"Set client cert - phase 2", strLength);
		break;
	case SUP_OPCODE_SET_TLS_PRIVATE_KEY:
		OSAL_strncpy_s(str, strLength,"Set private key", strLength);
		break;
	case SUP_OPCODE_SET_TLS_PRIVATE_KEY2:
		OSAL_strncpy_s(str, strLength,"Set private key - phase 2", strLength);
		break;
	case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD:
		OSAL_strncpy_s(str, strLength,"Set private key password", strLength);
		break;
	case SUP_OPCODE_SET_TLS_PRIVATE_KEY_PASSWD2:
		OSAL_strncpy_s(str, strLength,"Set private key password - phase 2", strLength);
		break;
	case SUP_OPCODE_SET_PIN:
		OSAL_strncpy_s(str, strLength,"Set PIN", strLength);
		break;
	case SUP_OPCODE_SET_PIN_MAX_SIZE:
		OSAL_strncpy_s(str, strLength,"Set PIN max size", strLength);
		break;
	case SUP_OPCODE_SET_TLS_MAX_SIZE:
		OSAL_strncpy_s(str, strLength,"Set TLS max size", strLength);
		break;
	}
}


EXTERN_C EXPORT void SupplicantAgent_Finalize()
{	
	wmxSup_FinalizeAgent();
	if(pFuncs != NULL)
	{
		pFuncs->pfnDisconnect( supplicantConnection );
		pFuncs = NULL;
	}
	FinalizeSupplicantLibrary();
	CleanIndicatorsList(&indicatorSubscribersList);

	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Agent shutdown Succeeded");
}

EXTERN_C EXPORT BOOL SupplicantAgent_Stop()
{
	SupAgent_UnRegisterCallbacksOnWrapper();
	EmptyIndicatorsList(&indicatorSubscribersList);
	TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Agent stopped");
	
	return TRUE;
}

EXTERN_C EXPORT BOOL SupplicantAgent_Start()
{
	BOOL initSt = TRUE;
	wmx_Status_t status;
	
	// Register Callbacks
	status = SupAgent_RegisterCallbacksOnWrapper();
	if ( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Can't register callbacks");		
		initSt = FALSE;
	}
	else
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Agent started. Target ID=%d", L5_TARGET_SUPPLICANT);
	}

	return initSt;
}

EXTERN_C EXPORT APPSRV_INIT_ST SupplicantAgent_Initialize(tL5DispatcherFunctions *L5disp, tUtilityFunctions *UtilFn)
{	
	L5_RESULT l5Result;
	wmx_Status_t status;

	APPSRV_INIT_ST initSt = INIT_SUCCESS;
	pFuncs = L5disp;
	pUtils = UtilFn;
	

	status = LoadSupplicantLibrary(); // Load DS Supplicant.dll
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Can't load Supplicant library");
		if( WMX_ST_CONFIG_ERROR == status )
		{
			initSt = INIT_CONFIG_FAIL;			
		}
		else
		{		
			initSt = INIT_FAIL;
		}
		goto Finalize;
	}

	OSAL_strcpy_s((char*)g_TargetBuf, L4_MSG_MAX_LENGTH, "This is sup test\n");

	AllocIndicatorsList(&indicatorSubscribersList);
	memset(&g_SuppConfig, 0, sizeof(g_SuppConfig));
	status = InitSupplicantLibrary(); // Init DS Supplicant.dll
	if (status != WMX_ST_OK)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Can't init Supplicant library");
		FinalizeSupplicantLibrary();
		CleanIndicatorsList(&indicatorSubscribersList);
		initSt = INIT_FAIL;
		goto Finalize;
	}	

	// Init L5 connection and methods
	/*
	pFuncs = L5_DISPATCHER_GetServiceDispatcherFunctions();
	if (NULL == pFuncs)
	{
	FinalizeSupplicantLibrary();
	CleanIndicatorsList(&indicatorSubscribersList);
	return INIT_FAIL;
	}*/

	l5Result = pFuncs->pfnConnectEx(/*	NULL, 
									0, */
									L5_TARGET_SUPPLICANT, 
									&Supplicant_MessagesHandler, 
									&Supplicant_EventHandler,  
									NULL, 
									THREAD_ID_DEFAULT,
									&supplicantConnection );

	if ((L5_RESULT_OK != l5Result) || (NULL == supplicantConnection))
	{
		FinalizeSupplicantLibrary();
		CleanIndicatorsList(&indicatorSubscribersList);
		initSt = INIT_FAIL;
		goto Finalize;
	}

	// Init Wrapper
	status = wmxSup_InitAgent();
	if ( status != WMX_ST_OK )
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Can't init wrappers");
		initSt = INIT_FAIL;
	}

Finalize:
	if (initSt == INIT_SUCCESS)
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_INFO,"Supplicant: Agent initialization succeeded. Target ID=%d", L5_TARGET_SUPPLICANT);
	}
	else
	{
		TRACE(TR_MOD_SUPPLICANT_AGENT, TR_SEV_ERR,"Supplicant: Agent initialization failed");
	}
	return initSt;
}
//*******************************************
// AppSrv Agent Interface - end
//*******************************************
