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
#include "wmxSDK_Nds_Internals.h"
#include "wmxSDK_Nds_IndHandler.h"

#include "wmxSDK_Nds_L5.h"

#include "L5Common.h"
#include "L5OpCodes.h"	// @@@ : JSS : Case name correction
#include "WrappersUtils.h"

#include "TraceModule.h"



// ind handlers
wmx_Status_t wmxNds_StateReportArrived( ReportState_type stateReport );
wmx_Status_t wmxNds_ScanReportArrived( ReportScanResults_type scanReport );
wmx_Status_t wmxNds_BsInfoReportArrived(ReportBsInfo_type bsInfoReport);
wmx_Status_t wmxNds_SIIReportArrived(ReportSII_type siiReport);
wmx_Status_t wmxNds_RecentBSsReportArrived(ReportRecentNbrHood_type nbrHoodReport);
wmx_Status_t wmxNds_AgentScanCompletedArrived( UINT8 *buf, UINT32 bufSize );
wmx_Status_t wmxNds_AgentConnectCompletedArrived( UINT8 *buf, UINT32 bufSize );
wmx_Status_t wmxNds_AgentScanUpdateArrived( UINT8 *buf, UINT32 bufSize );
wmx_Status_t wmxNds_AgentSystemStateUpdateArrived( UINT8 *buf, UINT32 bufSize );
wmx_Status_t wmxNds_AgentCurrentPreferredNSPChanged( UINT8 *buf, UINT32 bufSize );
wmx_Status_t wmxNds_AgentMediaStatusArrived( UINT8 *buf, UINT32 bufSize );



void wmxNds_MessagesHandler(L5_CONNECTION Conn,
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
	ReportState_type stateReport;
	ReportScanResults_type scanReport;
	ReportBsInfo_type bsInfoReport;
	ReportSII_type siiReport;
	ReportRecentNbrHood_type nbrHoodReport;
	ReportEMSKRelatedKeys_type bekReport;

	UNREFERENCED_PARAMETER(nOriginID);
	UNREFERENCED_PARAMETER(cbResponseBufferSize);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvResponseBuffer);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(cbSentBufferSize);

	*pdwResponseMessageID = WMX_ST_OK;

	switch (dwSentMessageID)
	{
		case L4_PROXY_OPCODE_STATUS_INDICATION_ARRIVED:
			break;

		//GOLD, SILVER
		case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:
			switch ( L4BM_GetOpcode((UINT8*)pvSentBuffer) )
			{
				case L3_L4_OPCODE_REPORT_STATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got L3_L4_OPCODE_REPORT_STATE");

					// get the report state struct
					if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &stateReport, ReportState_Funcs, &st ) != WMX_ST_OK )
					{
						*pdwResponseMessageID = WMX_ST_FAIL;
						return;
					}
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					
					st = wmxNds_StateReportArrived( stateReport  );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				
				case L3_L4_OPCODE_REPORT_SCAN_RESULT:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got L3_L4_OPCODE_REPORT_SCAN_RESULT");

					// get the report scan struct
					if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &scanReport, ReportScanResults_Funcs, &st ) != WMX_ST_OK )
					{
						*pdwResponseMessageID = WMX_ST_FAIL;
						return;
					}
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}

					st = wmxNds_ScanReportArrived( scanReport );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				// BS info
				case L3_L4_OPCODE_REPORT_BS_INFO:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got L3_L4_OPCODE_REPORT_BS_INFO");

					// get the report state struct
					if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &bsInfoReport, ReportBsInfo_Funcs, &st ) != WMX_ST_OK )
					{
						*pdwResponseMessageID = WMX_ST_FAIL;
						return;
					}
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					
					st = wmxNds_BsInfoReportArrived( bsInfoReport  );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				// SII
				case L3_L4_OPCODE_REPORT_SII:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got L3_L4_OPCODE_REPORT_SII");

					// get the report state struct
					if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &siiReport, ReportSII_Funcs, &st ) != WMX_ST_OK )
					{
						*pdwResponseMessageID = WMX_ST_FAIL;
						return;
					}
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					
					st = wmxNds_SIIReportArrived( siiReport  );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case L3_L4_OPCODE_REPORT_RECENT_BS:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got L3_L4_OPCODE_REPORT_RECENT_BS");

					if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &nbrHoodReport, ReportRecentNbrHood_Funcs, &st ) != WMX_ST_OK )
					{
						*pdwResponseMessageID = WMX_ST_FAIL;
						return;
					}
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					st = wmxNds_RecentBSsReportArrived( nbrHoodReport  );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
					// BEK
				case L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS");

					// get the report state struct
					if( wmx_ParseL4Buffer( (UINT8*)pvSentBuffer, &bekReport, ReportEMSKRelatedKeys_Funcs, &st ) != WMX_ST_OK )
					{
						*pdwResponseMessageID = WMX_ST_FAIL;
						return;
					}
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}

					st = wmxNds_BEKReportArrived( bekReport  );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				default:

					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "wmxNds_MessagesHandler Got L4_PROXY_OPCODE_L4_INDICATION_ARRIVED Unknown OPCODE");
					//ASSERT();
					*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
					break;
			}
			break;
		
		//PLASTIC
		case NDNS_OPCODE_INDICATION_ARRIVED:
			switch ( ((pNDNS_MESSAGE)pvSentBuffer)->opcode )
			{
				case NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_CURRENT_PREFERRED_NSP");

					st = wmxNds_AgentCurrentPreferredNSPChanged(
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_MEDIA_STATUS:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_MEDIA_STATUS");

					st = wmxNds_AgentMediaStatusArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_SCAN_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_SCAN_UPDATE");
					
					st = wmxNds_AgentScanUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_SCAN_COMPLETED:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_SCAN_COMPLETED");
					
					st = wmxNds_AgentScanCompletedArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				
				case NDNS_OPCODE_IND_CONNECT_COMPLETED:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_CONNECT_COMPLETED");
					
					st = wmxNds_AgentConnectCompletedArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_SYSTEM_STATE_UPDATE");

					st = wmxNds_AgentSystemStateUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_PROVISIONING_OPERATION:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_PROVISIONING_OPERATION");

					st = wmxNds_ApdoProvisioningOperationArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_PACKAGE_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_PACKAGE_UPDATE");

					st = wmxNds_ApdoPackageUpdateArrived((UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, 
						((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_PACKAGE_DOWNLOAD_PROGRESS");

					st = wmxNds_ApdoPackageDownloadProgressArrived((UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, 
						((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_CONNECTION_MODE_UPDATE");

					st = wmxNds_AgentConnectionModeUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_FAST_RECONNECT_MODE_UPDATE");

					st = wmxNds_AgentFastReconnectStatusUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_COEX_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_COEX_UPDATE");

					st = wmxNds_AgentCoexUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_ROAMING_MODE_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_ROAMING_MODE_UPDATE");

					st = wmxNds_AgentRoamingModeUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_DEVICE_STATUS_UPDATE");

					st = wmxNds_AgentDeviceStatusUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				case NDNS_OPCODE_IND_PNM_NOTIFICATION:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_PNM_NOTIFICATION");

					st = wmxNds_AgentPNMNotificationArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;


				case NDNS_OPCODE_IND_RF_TAKEN:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_RF_TAKEN");

					st = wmxNds_AgentRfTakenUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;

				case NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_INFO, "wmxNds_MessagesHandler::Got NDNS_OPCODE_IND_CONNECTED_AS_CURRENT_PREFERRED_CAPABILITY_STATUS_UPDATE");

					st = wmxNds_AgentConnectedAsCurrentPreferredCapabilityStatusUpdateArrived( 
						(UINT8*)((pNDNS_MESSAGE)pvSentBuffer)->buf, ((pNDNS_MESSAGE)pvSentBuffer)->bufferLength );
					if( st != WMX_ST_OK )
					{
						*pdwResponseMessageID = st;
						return;
					}
					break;
				
				default:
					TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "wmxNds_MessagesHandler Got NDNS_OPCODE_INDICATION_ARRIVED Unknown OPCODE");
					*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
					break;
			}
			break;

		default:
			TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_ALERT, "wmxNds_MessagesHandler Got Unknown msg = %d",dwSentMessageID);
			*pdwResponseMessageID = WMX_ST_ILLEGAL_OPERATION;
			break;
	}
}

void wmxNds_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext)
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(eEvent);
	UNREFERENCED_PARAMETER(pvUserContext);
	UNREFERENCED_PARAMETER(pvEventData);
}

void wmxNds_FinalizeL5()
{
	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_FinalizeL5(IN)");
	if ( ( nds_wrapper_pFuncs != NULL ) && ( nds_wrapper_l5ConnID != NULL ) )
	{
		nds_wrapper_pFuncs->pfnDisconnect(nds_wrapper_l5ConnID);
	}

	nds_wrapper_l5ConnID = NULL;
	nds_wrapper_pFuncs = NULL;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_FinalizeL5(OUT)");
}

wmx_Status_t wmxNds_InitL5()
{
	L5_RESULT l5status;
	wmx_Status_t st;

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_InitL5(IN)");
	nds_wrapper_pFuncs = GetL5Funcs();
	nds_wrapper_UtilFuncs = GetUtilsFuncs();
	if (NULL == nds_wrapper_pFuncs)
	{
		return WMX_ST_PIPE_FAILURE;
	}

	// Connect L5 and through it to AppSrv. Gain L5ConnID.
	l5status = nds_wrapper_pFuncs->pfnConnectEx( 
							/*ndsIpAddr, 
							ndsPortNum,*/
							L5_TARGET_DYNAMIC,
							wmxNds_MessagesHandler, 
							wmxNds_EventHandler,
							NULL,
							THREAD_ID_DEFAULT,
							&nds_wrapper_l5ConnID );
	st = wmx_L5ResultToWMXStatus( l5status );
	if( st != WMX_ST_OK )
	{
		return st;
	}

	TRACE(TR_MOD_NDNS_WRAPPER, TR_SEV_NOTICE, "wmxNds_InitL5(OUT). status=%d, nds_wrapper_l5ConnID=%d", l5status, nds_wrapper_l5ConnID);
	return WMX_ST_OK;
}






