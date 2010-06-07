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
#include "wmxSDK_Apdo_IndHandler.h"
#include "wmxSDK_Apdo_Internals.h"
#include "wmxSDK_Apdo_Utils.h"
#include "wimax_osal_ip_services.h"




#include "wmxSDK_Apdo_3.h"
#include "wmxSDK_Apdo_L5.h"

#include "WrappersUtils.h"
#include "wimax_osal_config_controler.h"

#include "Messenger.h"
#include "TraceModule.h"
#include "wmxSDK_Nds_L5.h"


//#define BEK_LENGTH 16

//static BYTE ApdoFuncsBuffer[3*sizeof(INT32) + BEK_LENGTH]; // use it to pass the data between threads
//
//UINT32 WINAPI SleepThreadFunc( LPVOID lpParameter )
//{
//	UINT32	delayTimeRegistry, delayTime = 15000;
//	BOOL	res;
//
//	wmx_pApdoLinkStatusCBStruct_t pApdoFuncs = (wmx_pApdoLinkStatusCBStruct_t)ApdoFuncsBuffer;
//
//	UNREFERENCED_PARAMETER(lpParameter);
//
//	res = RegistryController_GetNumValue(HKEY_LOCAL_MACHINE, KEY_ENTRY_PIPECONFIG, KEY_ENTRY_LINK_UP_SLEEP, &delayTimeRegistry);
//	if (res == TRUE)
//	{
//		delayTime = delayTimeRegistry;
//	}
//
//	OSAL_sleep(delayTime);
//
//	ApdoLinkStatusCB( pApdoFuncs->linkStatus, pApdoFuncs->nspId, pApdoFuncs->activationConnection,
//								pApdoFuncs->realm);
//
//	return 0;
//}

void wmxApdo_CBsCaller( UINT32 internalRequestID, void *buffer, UINT32 bufferLength )
{
	//HANDLE SleepThreadHandle;
	wmx_pApdoLinkStatusCBStruct_t pApdoFuncs;
	wmx_Status_t status = WMX_ST_FAIL;
	wmx_ApdoOperatorConfigurations_t apdoConfigurations;
	UINT32 responseLength = (UINT32)(sizeof(wmx_ApdoOperatorConfigurations_t));
	char realmFromDHCPResponse[WMX_NSP_REALM_MAX_SIZE];
	char realmFromDHCPRequest[WMX_NSP_REALM_MAX_SIZE];
	UINT32 realmFromDHCPResponseLength = (UINT32)(sizeof(char)*WMX_NSP_REALM_MAX_SIZE);
	//int MAX_DHCP_TRIES = 5;
	UNREFERENCED_PARAMETER(bufferLength);
	
	switch ( internalRequestID )
	{				
	case AGENT_APDO_LINK_STATUS:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "got agent APDO link status");
		pApdoFuncs = (wmx_pApdoLinkStatusCBStruct_t)buffer;
		
		

		status = wmx_GetApdoOperatorConfigurations (&apdoConfigurations , sizeof(apdoConfigurations), &responseLength);

		if (status != WMX_ST_OK) 
		{
			apdoConfigurations.disableOTAP = FALSE;
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "wmxApdo_CBsCaller: GetApdoOperatorConfigurations returned != WMX_ST_OK then we use defauult which is enable OTAP !");
		}
		
		if (!apdoConfigurations.disableOTAP)
		{
			if ( NULL != ApdoLinkStatusCB )
			{
				/// Only when link up is recieved then these calls are relevant.
				if (pApdoFuncs->linkStatus != APDO_linkDown)
				{
					TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Calling user APDO link status callback");


					////for option 15
					status = wmxApdo_SendNdsMsg( NDNS_OPCODE_GET_APDO_DHCP_HOST_NAME,  NDNS_OPCODE_APDO, sizeof(char)*WMX_NSP_REALM_MAX_SIZE, 
						(UINT8*)&realmFromDHCPRequest, &realmFromDHCPResponseLength, (UINT8*)&realmFromDHCPResponse );
					TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmx_GetApdoLinkStatus() status - %d", status);


					if (status != WMX_ST_OK)
					{
						// Get realm
						TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmxApdo_CBsCaller : GetHostName != WMX_ST_OK. Using Option Pre provisioned realm if exists realm.");	
					}
					else
					{
						if (realmFromDHCPResponse[0] == '\0')
						{
							TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmxApdo_CBsCaller : GetHostName returned empty string. Using Option Pre provisioned realm if exists realm.");
							TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmxApdo_CBsCaller : GetHostName == WMX_ST_OK. Using Option Pre provisioned realm if exists realm.");
						}
						else
						{
							realmFromDHCPResponse[WMX_NSP_REALM_MAX_SIZE-1]='\0';
							TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmxApdo_CBsCaller : GetHostName - returns WMX_ST_OK. Using Option 15 realm = [%s].",realmFromDHCPResponse);
							OSAL_strcpy_s(pApdoFuncs->realm, WMX_NSP_REALM_MAX_SIZE, realmFromDHCPResponse);					
						}
					}
				}
				else
				{
					OSAL_strcpy_s(pApdoFuncs->realm, WMX_NSP_REALM_MAX_SIZE, "");	
				}
				if (ApdoLinkStatusCB != NULL)
				{
					TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "wmxApdo_CBsCaller : Calling ApdoLinkStatusCB");
					ApdoLinkStatusCB(pApdoFuncs->linkStatus, pApdoFuncs->nspName, pApdoFuncs->nspId, pApdoFuncs->activationConnection,
						pApdoFuncs->realm);
				}
			}
		}
		else
		{
			TRACE(TR_MOD_NDNS_AGENT, TR_SEV_INFO, "wmxApdo_CBsCaller: GetApdoOperatorConfigurations OTAP is disabled!");
		}
		break;	
	case AGENT_APDO_ALERT_RESPONSE:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "got agent APDO alert response");
		if ( NULL != ApdoAlertResponseCB )
		{
			wmx_pApdoAlertResponse_t pAlertResponse = (wmx_pApdoAlertResponse_t)buffer;
			
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Calling user APDO alert response callback");
						
			ApdoAlertResponseCB( *pAlertResponse );
		}
		break;
	case AGENT_APDO_SESSION_STATUS:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "got agent APDO session status");
		if ( NULL != RefreshApdoSessionStatusCB )
		{						
			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Calling user APDO session status callback");
						
			RefreshApdoSessionStatusCB();
		}
		break;
	case AGENT_APDO_FUMO_DOWNLOAD_APPROVAL_STATUS:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "got agent APDO download approval status");
		if ( NULL != ApdoFumoDownloadApprovalStatusCB )
		{		
			wmx_pApdoDownloadStatus_t pDownloadStatus = (wmx_pApdoDownloadStatus_t)buffer;

			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Calling user APDO Fumo Download approval status callback");

			ApdoFumoDownloadApprovalStatusCB(*pDownloadStatus);
		}
		break;
/*	case AGENT_APDO_OOB_NOTIFICATION:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "got agent APDO oob notification");
		if ( NULL != ApdoOobNotificationCB )
		{			
			wmx_ApdoOobMessage_t *pOobMessage = (wmx_ApdoOobMessage_t*)buffer;

			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Calling user APDO oob notification callback");
						
			ApdoOobNotificationCB( *pOobMessage );
		}
		break;*/	
	case AGENT_APDO_DELETE_DM_ACCOUNT:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "got agent APDO delete dm account");
		if ( NULL != ApdoDeleteDMAccountCB )
		{		
			wmx_pApdoDeleteDMAccountCBStruct_t deleteDMAccStruct = (wmx_pApdoDeleteDMAccountCBStruct_t)buffer;

			TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_INFO, "Calling delete DM account CB");
			ApdoDeleteDMAccountCB(*deleteDMAccStruct);
		}
		break;
	default:
		TRACE(TR_MOD_APDO_WRAPPER, TR_SEV_ERR, "Unknown internal opcode: %d", internalRequestID);
		ASSERT();
		break;
	}
}

wmx_Status_t wmxApdo_LinkStatusArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxApdo_LinkStatusArrived (IN)");

	/*Messenger_PostRequest*/apdo_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_APDO_LINK_STATUS, buf, bufSize, &wmxApdo_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxApdo_AlertResponseArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxApdo_AlertResponseArrived (IN)");

	/*Messenger_PostRequest*/apdo_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_APDO_ALERT_RESPONSE, buf, bufSize, &wmxApdo_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxApdo_OobNotificationArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxApdo_OobNotificationArrived (IN)");

	/*Messenger_PostRequest*/apdo_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_APDO_OOB_NOTIFICATION, buf, bufSize, &wmxApdo_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxApdo_RefreshApdoSessionStatusArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxApdo_RefreshApdoSessionStatusArrived (IN)");

	/*Messenger_PostRequest*/apdo_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_APDO_OOB_NOTIFICATION, buf, bufSize, &wmxApdo_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxApdo_FumoDownloadApprovalStatusArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxApdo_FumoDownloadApprovalStatusArrived (IN)");
	
	/*Messenger_PostRequest*/apdo_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_APDO_FUMO_DOWNLOAD_APPROVAL_STATUS, buf, bufSize, &wmxApdo_CBsCaller );

	return WMX_ST_OK;
}

wmx_Status_t wmxApdo_DeleteDMAccountArrived( UINT8 *buf, UINT32 bufSize )
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxApdo_DeleteDMAccountArrived(IN)");

	/*Messenger_PostRequest*/apdo_wrapper_UtilFuncs->tpfnPostRequest( MEDIUM, AGENT_APDO_DELETE_DM_ACCOUNT, buf, bufSize, &wmxApdo_CBsCaller );

	return WMX_ST_OK;
}
