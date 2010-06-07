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
#include "wmxSDK_Apdo_L5.h"
#include "wmxSDK_Nds_L5.h"

#include "wmxSDK_Nds_IndHandler.h"
#include "wmxSDK_Apdo_Internals.h"
#include "wmxSDK_Apdo_IndHandler.h"

#include "L5OpCodes.h"		// @@@ : JSS : Corrected case name of the file 
#include "L5Common.h"
#include "WrappersUtils.h"

#include "TraceModule.h"

OSAL_critical_section *pcs_apdo_funcs = NULL;
//************************************************
//  Callback for handling indications
//************************************************

void wmxApdo_MessagesHandler(	L5_CONNECTION Conn,
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
	wmx_Status_t st;	

	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(cbResponseBufferSize);
	UNREFERENCED_PARAMETER(pdwResponseMessageID);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvResponseBuffer);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbSentBufferSize);

	switch (dwSentMessageID)
	{
		case NDNS_OPCODE_INDICATION_ARRIVED:
			switch ( ((pAPDO_MESSAGE)pvSentBuffer)->opcode )
			{				
				case NDNS_OPCODE_IND_ALERT_NOTIFICATION:				
					st = wmxNds_ApdoAlertNotificationArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_APDO_LINK_STATUS:					
					st = wmxApdo_LinkStatusArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_APDO_ALERT_RESPONSE:					
					st = wmxApdo_AlertResponseArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_APDO_SESSION_STATUS:					
					st = wmxApdo_RefreshApdoSessionStatusArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_APDO_OOB_NOTIFICATION:					
					st = wmxApdo_OobNotificationArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;	
				case NDNS_OPCODE_IND_APDO_FUMO_DL_APPROVAL_STATUS:
					st = wmxApdo_FumoDownloadApprovalStatusArrived(
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_APDO_DELETE_DM_ACCOUNT:
					st = wmxApdo_DeleteDMAccountArrived((UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, 
						((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				default:
					ASSERT();
					break;
			}
			break;
		default:
			ASSERT();
			break;
	}
}

//************************************************
//  
//************************************************
void wmxApdo_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext)
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(eEvent);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);
}

//************************************************
// 
//************************************************
wmx_Status_t wmxApdo_InitL5()
{	
	L5_RESULT l5status = L5_RESULT_NO_HANDLER;
	if ( pcs_apdo_funcs == NULL )	
		pcs_apdo_funcs = malloc (sizeof(OSAL_critical_section));

	if (pcs_apdo_funcs!=NULL)
	{
		OSAL_init_critical_section(pcs_apdo_funcs);
		if (pcs_apdo_funcs == NULL)
		{
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_CRITICAL, "wmxApdo_InitL5 - Failed to initialize critical section");
			return WMX_ST_FAIL;
		}
	}
	else
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_DEBUG, "wmxApdo_InitL5 - pcs_apdo_funcs already initialized");
	}
	OSAL_enter_critical_section(pcs_apdo_funcs);
	apdo_wrapper_pFuncs = GetL5Funcs();
	OSAL_exit_critical_section(pcs_apdo_funcs);
	apdo_wrapper_UtilFuncs = GetUtilsFuncs();
	if (NULL == apdo_wrapper_pFuncs)
	{
		TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_CRITICAL, "wmxApdo_InitL5 - apdo_wrapper_pFuncs == NULL ");
		return WMX_ST_PIPE_FAILURE;
	}

	// Init the callback functions
	ApdoLinkStatusCB = NULL;
	ApdoAlertResponseCB = NULL;
//	ApdoOobNotificationCB = NULL;
	RefreshApdoSessionStatusCB = NULL;
	ApdoFumoDownloadApprovalStatusCB = NULL;
	OSAL_enter_critical_section(pcs_apdo_funcs);
	// Connect L5 and through it to AppSrv. Gain L5ConnID.
	if (NULL != apdo_wrapper_pFuncs)
	{
		l5status = apdo_wrapper_pFuncs->pfnConnectEx(
									L5_TARGET_DYNAMIC,
									wmxApdo_MessagesHandler, 
									wmxApdo_EventHandler,
									NULL,
									THREAD_ID_DEFAULT,
									&apdo_wrapper_l5ConnID	);
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	if ((L5_RESULT_OK != l5status) || (NULL == apdo_wrapper_l5ConnID))
	{
		return WMX_ST_PIPE_FAILURE;
	}
	return WMX_ST_OK;
}

//************************************************
//  
//************************************************
void wmxApdo_FinalizeL5()
{
	OSAL_enter_critical_section(pcs_apdo_funcs);
	if (apdo_wrapper_pFuncs != NULL)
	{
		apdo_wrapper_pFuncs->pfnDisconnect(apdo_wrapper_l5ConnID);
		apdo_wrapper_pFuncs = NULL;
	}
	OSAL_exit_critical_section(pcs_apdo_funcs);
	 //Removed delete of critical section - Because it caused race condition.
		//If finalized is called from one thread and other APDO function is called from another there is a case
		//where CS is already deleted in finalize and in the other function we try to enter that CS.
	
	if (pcs_apdo_funcs != NULL)
	{
		OSAL_delete_critical_section(pcs_apdo_funcs);		
		free(pcs_apdo_funcs);
		pcs_apdo_funcs = NULL;
	}
	
}