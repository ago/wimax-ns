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
//*********************************
//Include Files:
//*********************************

#include "MocMsgProxy.h"

#include "MOC_Utils.h"
#include "ApplicationMocTaskDesc.h"

#include "WrappersCommon.h"

#include "L3L4CommonDefines.h"
#include "Intel_80216_L4_interface_OS.h"
#include "L4BufMan_L3L4Structs_Desc.h"
#include "L4BufMan_L3L4Structs.h"

#include "L4MsgProxyIf.h"

#include "TraceModule.h"


static tUtilityFunctions *pUtils;

static void MyPrintf(const char* format, ...)
{
//	if (mLogToConsole == 0)
//	{
//		return;
//	}

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);

	//TRACE(TR_MOD_MOCMsgProxy, TR_SEV_ERR, (format, args);
}


EXTERN_C EXPORT BOOL MocMsgProxy_Start()
{
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Start");
	return TRUE;
}

EXTERN_C EXPORT BOOL MocMsgProxy_Stop()
{
	initialized = FALSE;

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Stop(IN)");
	if (L5dispatcher != NULL)
	{
		if (!MocMsgProxy_UnBindToL4msgProxy())
		{
			//MyPrintf("\nMocMsgProxy - MocMsgProxy_Init - ERROR - Failed to register for MoC response indications with L4msgProxy. \n");
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_ALERT, "Failed to register for MoC response indications with L4msgProxy. ");
		}

		// Disconnect from L5.
		L5dispatcher->pfnDisconnect(L5ConnID);
	}

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Stop(OUT)");
	return TRUE;
}

EXTERN_C EXPORT void MocMsgProxy_Finalize()
{
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Finalize(IN)");

	L5ConnID = NULL;

	OSAL_delete_critical_section(&perAppInfoGuard);
	L5dispatcher = NULL;
	L5dispatcherBackup = NULL;

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Finalize(OUT)");
}

EXTERN_C EXPORT APPSRV_INIT_ST MocMsgProxy_Initialize(tL5DispatcherFunctions *L5disp, 
													  tUtilityFunctions *UtilFn)
{
	int i;

	initialized = FALSE;
	
	OSAL_init_critical_section(&perAppInfoGuard);

	pUtils = UtilFn;
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Initialize(IN)");

	//L5dispatcher = L5_DISPATCHER_GetServiceDispatcherFunctions();
	L5dispatcher = L5disp;
	L5dispatcherBackup = L5dispatcher;
	if (L5dispatcher == NULL)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_Init - ERROR - Got a NULL pointer to the L5DispatcherFunctions. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ALERT, "Got a NULL pointer to the L5DispatcherFunctions. ");

		return FALSE;
	}

	
	OSAL_enter_critical_section(&perAppInfoGuard);
	lastAcquiredPlace = -1;
	for (i = 0; i < MOC_MSG_PROXY_MAX_APPS; i++)
	{
		perAppInfo[i].isValid = FALSE;
		//perAppInfo[i].L5ConnID = NULL;
		perAppInfo[i].originID = 0;
		perAppInfo[i].handle = MOC_PROXY_INVALID_SOCKET_ID;
	}
	OSAL_exit_critical_section(&perAppInfoGuard);

	if (!MocMsgProxy_ConnectL5())
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_Init - ERROR - Failed to connect L5. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ALERT, "Failed to connect L5. ");
		return FALSE;
	}
	
	if (!MocMsgProxy_BindToL4msgProxy())
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_Init - ERROR - Failed to register for MoC response indications with L4msgProxy. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ALERT, "Failed to register for MoC response indications with L4msgProxy. ");
		return FALSE;
	}

	initialized = TRUE;

	//MyPrintf("\nMocMsgProxy - MocMsgProxy_Initialize - Success. \n");
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_NOTICE , "MocMsgProxy_Initialize Succeeded. Target ID=%d", L5_TARGET_MOC_PROXY);
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Initialize(OUT)");
	return TRUE;
}


/*static BOOL MocMsgProxy_Shutdown()
{
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Shutdown(IN)");

	initialized = FALSE;

	if (L5dispatcher != NULL)
	{
		if (!MocMsgProxy_UnBindToL4msgProxy())
		{
			//MyPrintf("\nMocMsgProxy - MocMsgProxy_Init - ERROR - Failed to register for MoC response indications with L4msgProxy. \n");
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_ALERT, "Failed to register for MoC response indications with L4msgProxy. ");
		}

		// Disconnect from L5.
		L5dispatcher->pfnDisconnect(L5ConnID);
		//L5dispatcher = NULL;
	}

	//L5ConnID = NULL;

	OSAL_delete_critical_section(&perAppInfoGuard);
	
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_Shutdown(OUT)");
	return TRUE;
}*/


static BOOL MocMsgProxy_ConnectL5()
{
	L5_RESULT L5status;

	// Connect L5. Gain L5ConnID.
	L5status = L5dispatcher->pfnConnectEx(
		L5_TARGET_MOC_PROXY,
		MocMsgProxy_MessagesHandler, 
		MocMsgProxy_EventHandler, //MocMsgProxy_EventHandler,
		NULL,
		THREAD_ID_DEFAULT,
		&L5ConnID);

	if ( (L5status != L5_RESULT_OK) || (L5ConnID == NULL) )
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_ConnectL5 - ERROR - Failed to connect L5. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed to connect L5. ");
		return FALSE;
	}

	//MyPrintf("\nMocMsgProxy - MocMsgProxy_ConnectL5 - Success. \n");
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Success. ");
	return TRUE;
}


static BOOL MocMsgProxy_BindToL4msgProxy()
{
	UINT32 L5rcvMsgID = 0;
	L5_RESULT L5status;

	// Register for L4_INTEL_80216_IND_MOC_RESPONSE & L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy

	RegisteredIndication L4ind = L3_L4_OPCODE_REPORT_MOC_RESPONSE; //L4_INTEL_80216_IND_MOC_RESPONSE;
	L5status = L5dispatcher->pfnSendReceiveMessage(L5ConnID,
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_REGISTER_L4_INDICATION,
		&L4ind,
		4,
		&L5rcvMsgID,
		NULL,
		NULL);
	if (L5status != L5_RESULT_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_BindToL4msgProxy - ERROR - Failed on send of L4Proxy_OPCODE_REGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed on send of L4Proxy_OPCODE_REGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. ");
		return FALSE;
	}
	if (L5rcvMsgID != WMX_ST_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_BindToL4msgProxy - ERROR - Failed to register for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed to register for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. ");
		return FALSE;
	}
//	if (   ((MUTL_PIPE_L5_MSG_ID)L5rcvMsgID != MUTL_PIPE_L5_MSG_ID_ACQUIRE_SOCKET_ID_RESPONSE)
//		|| (L5rcvBufferSize != 1)
//		|| (*(UINT8*)L5rcvBuffer == 0) )
//	{
//		L5status = perAppInfo[handle].L5dispatcher->pfnDisconnect(perAppInfo[handle].L5ConnID);
//		MyPrintf("UDapiL5 (%d) - UDapi_Connect - ERROR - Failed to acquire SocketID from MocProxyAgent. \n", handle);
//		return false;
//	}
	L4ind = L3_L4_OPCODE_REPORT_MOC_BROADCAST; //L4_INTEL_80216_IND_MOC_BROADCAST;
	L5status = L5dispatcher->pfnSendReceiveMessage(L5ConnID,
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_REGISTER_L4_INDICATION,
		&L4ind,
		4,
		&L5rcvMsgID,
		NULL,
		NULL);
	if (L5status != L5_RESULT_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_BindToL4msgProxy - ERROR - Failed on send of L4Proxy_OPCODE_REGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed on send of L4Proxy_OPCODE_REGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy agent. ");
		return FALSE;
	}
	if (L5rcvMsgID != WMX_ST_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_BindToL4msgProxy - ERROR - Failed to register for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed to register for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. ");
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//UINT32 L5sndMsgID = 0;
	//UINT32 L5sndBufferSize = 10;
	//memset(L5rcvBuffer, 0, 10);
	//L4_Opcode_Header l4Request;
	//L4_Opcode_Header l4Response;
	//memset(L5sndBuffer, 0, L5sndBufferSize);
	//((L4_Opcode_Header*)L5sndBuffer)->opcode = 111;
	//((L4_Opcode_Header*)L5sndBuffer)->bufferLength = 33;
	//L4_Opcode_Curr_Size()
	//L4_Opcode_Buffer_Ptr()
	//memcpy(L4_Opcode_Buffer_Ptr(L5sndBuffer), "This is L4 Message From Wrapper!", 33);


//	L5status = L5dispatcher->pfnSendReceiveMessage(L5ConnID,
//		L5_TARGET_L4_PROXY,
//		L4Proxy_OPCODE_SEND_L4_OPCODE,
//		L5sndBuffer,
//		L5sndBufferSize,
//		&L5rcvMsgID,
//		L5rcvBuffer,
//		&L5rcvBufferSize);
//	if (L5status != L5_RESULT_OK)
//	{
//		MyPrintf("\nMocMsgProxy - MocMsgProxy_BindToL4msgProxy - ERROR - Failed to SEND. \n");
//		return FALSE;
//	}
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////


	//MyPrintf("\nMocMsgProxy - MocMsgProxy_BindToL4msgProxy - Success. \n");
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Success. ");
	return TRUE;
}

static BOOL MocMsgProxy_UnBindToL4msgProxy()
{
	UINT32 L5rcvMsgID = 0;
	L5_RESULT L5status;

	// UnRegister for L4_INTEL_80216_IND_MOC_RESPONSE & L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy

	//	UINT32 L5rcvMsgID = 0;
	//	UINT32 L5rcvBufferSize = 0;
	//	void *L5rcvBuffer = NULL;
	RegisteredIndication L4ind = L3_L4_OPCODE_REPORT_MOC_RESPONSE; //L4_INTEL_80216_IND_MOC_RESPONSE;
	L5status = L5dispatcher->pfnSendReceiveMessage(L5ConnID,
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION,
		&L4ind,
		4,
		&L5rcvMsgID,
		NULL,
		NULL);
	if (L5status != L5_RESULT_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_UnBindToL4msgProxy - ERROR - Failed on send of L4Proxy_OPCODE_UNREGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed on send of L4Proxy_OPCODE_UNREGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. ");
		return FALSE;
	}
	if (L5rcvMsgID != WMX_ST_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_UnBindToL4msgProxy - ERROR - Failed to register for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed to unregister for L4_INTEL_80216_IND_MOC_RESPONSE with L4msgProxy agent. ");
		return FALSE;
	}
	//	if (   ((MUTL_PIPE_L5_MSG_ID)L5rcvMsgID != MUTL_PIPE_L5_MSG_ID_ACQUIRE_SOCKET_ID_RESPONSE)
	//		|| (L5rcvBufferSize != 1)
	//		|| (*(UINT8*)L5rcvBuffer == 0) )
	//	{
	//		L5status = perAppInfo[handle].L5dispatcher->pfnDisconnect(perAppInfo[handle].L5ConnID);
	//		MyPrintf("UDapiL5 (%d) - UDapi_Connect - ERROR - Failed to acquire SocketID from MocProxyAgent. \n", handle);
	//		return false;
	//	}
	L4ind = L3_L4_OPCODE_REPORT_MOC_BROADCAST; //L4_INTEL_80216_IND_MOC_BROADCAST;
	L5status = L5dispatcher->pfnSendReceiveMessage(L5ConnID,
		L5_TARGET_L4_PROXY,
		L4_PROXY_OPCODE_UNREGISTER_L4_INDICATION,
		&L4ind,
		4,
		&L5rcvMsgID,
		NULL,
		NULL);
	if (L5status != L5_RESULT_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_UnBindToL4msgProxy - ERROR - Failed on send of L4Proxy_OPCODE_UNREGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed on send of L4Proxy_OPCODE_UNREGISTER_L4_INDICATION for L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy agent. ");
		return FALSE;
	}
	if (L5rcvMsgID != WMX_ST_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_UnBindToL4msgProxy - ERROR - Failed to register for L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy agent. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_CRITICAL, "Failed to unregister for L4_INTEL_80216_IND_MOC_BROADCAST with L4msgProxy agent. ");
		return FALSE;
	}

	//MyPrintf("\nMocMsgProxy - MocMsgProxy_UnBindToL4msgProxy - Success. \n");
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Success. ");
	return TRUE;
}

static int MocMsgProxy_GetFreePlace(void)
{
	int	i;
	int freePlace = -1;

	//for (i = 0; i < MOC_MSG_PROXY_MAX_APPS; i++)
	//	if (perAppInfo[i].isValid == FALSE)
	//		return i;

	for (i = (lastAcquiredPlace+1); i < MOC_MSG_PROXY_MAX_APPS; i++)
	{
		if (perAppInfo[i].isValid == FALSE)
		{
			freePlace = i;
			break;
		}
	}
	if (freePlace == -1)
	{
		for (i = 0; i <= lastAcquiredPlace; i++)
		{
			if (perAppInfo[i].isValid == FALSE)
			{
				freePlace = i;
				break;
			}
		}
	}

	if (freePlace == -1)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_GetFreePlace - Too many applications!!\n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ERR, "Too many applications!!. ");
	}
	//return -1;
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "free place=%d", freePlace);
	return freePlace;
}


static UINT8 MocMsgProxy_AcquireSocketID(L5_TARGET_ID nOriginID, UINT8 handle)
{
	UINT8	socketID;
	OSAL_enter_critical_section(&perAppInfoGuard);

	/* save in local D.B. the current connection */
	socketID = (UINT8)MocMsgProxy_GetFreePlace();
	if ( socketID == -1 )
	{
		socketID = MOC_PROXY_INVALID_SOCKET_ID;
	}
	else
	{
		perAppInfo[socketID].originID	=	nOriginID;
		perAppInfo[socketID].handle		=	handle;
		perAppInfo[socketID].isValid	=	TRUE;
		lastAcquiredPlace = socketID;
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_AcquireSocketID - TargetID = %d acquired SocketID = %d. \n", nOriginID, socketID);
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "TargetID = %d acquired SocketID = %d. ", nOriginID, socketID);
	}

	OSAL_exit_critical_section(&perAppInfoGuard);
	return socketID;
}

static void MocMsgProxy_ReleaseSocketIDs()
{
	int i;

	lastAcquiredPlace = -1;
	for (i = 0; i < MOC_MSG_PROXY_MAX_APPS; i++)
	{
		perAppInfo[i].isValid = FALSE;
		//perAppInfo[i].L5ConnID = NULL;
		perAppInfo[i].originID = 0;
		perAppInfo[i].handle = MOC_PROXY_INVALID_SOCKET_ID;
	}
}

static void MocMsgProxy_ReleaseSocketID(L5_TARGET_ID nOriginID, void *buf, UINT32 bufSize)
{	
	UINT8 socketID = *(UINT8*)buf;

	UNREFERENCED_PARAMETER(nOriginID);

	if (bufSize != 1)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_ReleaseSocketID - ERROR - Got SocketID buffer of size != 1 from TargetID = %d. \n", nOriginID);
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ERR, "Got SocketID buffer of size != 1 from TargetID = %d. ", nOriginID);
		return;
	}

	OSAL_enter_critical_section(&perAppInfoGuard);
	perAppInfo[socketID].isValid = FALSE;
	perAppInfo[socketID].originID = 0;
	OSAL_exit_critical_section(&perAppInfoGuard);

	//MyPrintf("\nMocMsgProxy - MocMsgProxy_ReleaseSocketID - Released SocketID = %d held by TargetID = %d. \n", socketID, nOriginID);
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Released SocketID = %d held by TargetID = %d. ", socketID, nOriginID);
}

static void MocMsgProxy_ReleaseSocketIDByTarget(L5_TARGET_ID targetID)
{
	int i;
	BOOL success = FALSE;
	
	OSAL_enter_critical_section(&perAppInfoGuard);
	for (i = 0; i < MOC_MSG_PROXY_MAX_APPS; i++)
	{
		if (perAppInfo[i].originID == targetID)
		{
			perAppInfo[i].isValid = FALSE;
			perAppInfo[i].originID = 0;
			//MyPrintf("\nMocMsgProxy - MocMsgProxy_ReleaseSocketIDByTarget - Released SocketID = %d, associated with TargetID = %d. \n", i, targetID);
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Released SocketID = %d, associated with TargetID = %d. ", i, targetID);
			success = TRUE;
			break;
		}
	}
	OSAL_exit_critical_section(&perAppInfoGuard);

	if (!success)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_ReleaseSocketIDByTarget - Failed to find a SocketID matching TargetID = %d. \n", targetID);
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Released SocketID = Failed to find a SocketID matching TargetID = %d.", targetID);
	}
}

static void MocMsgProxy_SendMocResponse(L5_CONNECTION Conn, L5_TARGET_ID nOriginID, void *buf, UINT32 bufSize)
{
	L5_RESULT L5status;

	UNREFERENCED_PARAMETER(Conn);

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_SendMocResponse(IN). L5dispatcher=0x8%x",L5dispatcher);

	L5status = L5dispatcher->pfnSendReceiveMessage(
		L5ConnID,
		nOriginID,
		MOC_PROXY_L5_MSG_ID_MOC_RESPONSE_INDICATION,
		buf,
		bufSize,
		NULL,
		NULL,
		NULL);
	if (L5status != L5_RESULT_OK)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_SendMocResponse - ERROR - Failed to send MoC response to UDapiL5 (TargetID = %d). \n", nOriginID);
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ERR, "Failed to send MoC response to UDapiL5 (TargetID = %d). ", nOriginID);
	}

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_SendMocResponse(OUT)");
}


static void MocMsgProxy_ProcessL4Indication(void *buf, UINT32 bufSize)
{
	UINT32 taskId;
	UINT32 socketID;
	L5_TARGET_ID curOriginID;
	BOOL curIsValid;
	int i;
	UINT16 opcode;
	//L4_Indication_Header *pHeader = NULL;
	//UINT32 l4_indication_id;
	
	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_ProcessL4Indication(IN)");
	if (bufSize == 0)
	{
		//MyPrintf("\nMocMsgProxy - MocMsgProxy_ProcessL4Indication - ERROR - Got L4_Indication buffer of size == 0. \n");
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_ERR, "Got L4_Indication buffer of size == 0. ");
		return;
	}

	//pHeader = (L4_Indication_Header*)buf;
	//l4_indication_id = BM_INLINE_L3L4CompleteHeader_Type_GET(buf, 0);

	//switch(pHeader->indication)
	opcode = L4BM_GetOpcode(buf);
	switch(opcode)
	{
		case L3_L4_OPCODE_REPORT_MOC_RESPONSE: //L4_INTEL_80216_IND_MOC_RESPONSE:
			//taskId = BM_INLINE_MocOverSocket_TaskID_GET(L4_Indication_Buffer_Ptr(pHeader);
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "opcode = L3_L4_OPCODE_REPORT_MOC_RESPONSE");
			taskId = BM_INLINE_MocOverSocket_TaskID_GET((UINT8*)buf + HEADER_SIZE);
			socketID = (taskId & 0xff);
			
			OSAL_enter_critical_section(&perAppInfoGuard);
			curIsValid = perAppInfo[socketID].isValid;
			OSAL_exit_critical_section(&perAppInfoGuard);
			if(!curIsValid)
			{
				//MyPrintf("\nMocMsgProxy - MocMsgProxy_ProcessL4Indication - ERROR - SocketID encoded on MoC response is not valid! Moc task dropped. SocketID = %d. \n", socketID);
				TRACE(TR_MOD_MocMsgProxy, TR_SEV_ERR, "SocketID encoded on MoC response is not valid! Moc task dropped. SocketID = %d. ", socketID);
				break;
			}
			OSAL_enter_critical_section(&perAppInfoGuard);
			//pHeader->indication = perAppInfo[socketID].handle;
			L4BM_SetOpcode( buf, perAppInfo[socketID].handle );
			curOriginID = perAppInfo[socketID].originID;
			OSAL_exit_critical_section(&perAppInfoGuard);

			//MyPrintf("\nMocMsgProxy - MocMsgProxy_ProcessL4Indication - Sending MoC response to SocketID = %d (TargetID = %d). \n", socketID, curOriginID);
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Sending MoC response to SocketID = %d (TargetID = %d). ", socketID, curOriginID);
			MocMsgProxy_SendMocResponse(
				L5ConnID,
				curOriginID,
				buf,
				bufSize);
				//L4_Indication_Buffer_Ptr(pHeader),
				//pHeader->bufferLength);
			break;

		case L3_L4_OPCODE_REPORT_MOC_BROADCAST: //L4_INTEL_80216_IND_MOC_BROADCAST:
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "opcode = L3_L4_OPCODE_REPORT_MOC_BROADCAST");
			for (i = 0; i < MOC_MSG_PROXY_MAX_APPS; i++)
			{
				OSAL_enter_critical_section(&perAppInfoGuard);
				curIsValid = perAppInfo[i].isValid;
				OSAL_exit_critical_section(&perAppInfoGuard);
				if (curIsValid)
				{
					OSAL_enter_critical_section(&perAppInfoGuard);
					//pHeader->indication = perAppInfo[i].handle;
					L4BM_SetOpcode( buf, perAppInfo[i].handle );
					curOriginID = perAppInfo[i].originID;
					OSAL_exit_critical_section(&perAppInfoGuard);
					
					//MyPrintf("\nMocMsgProxy - MocMsgProxy_ProcessL4Indication - Sending MoC response for SocketID = %d (TargetID = %d). \n", i, curOriginID);
					TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Sending MoC broadcast to SocketID = %d (TargetID = %d). ", i, curOriginID);
					MocMsgProxy_SendMocResponse(
						L5ConnID,
						curOriginID,
						buf,
						bufSize);
						//L4_Indication_Buffer_Ptr(pHeader),
						//pHeader->bufferLength);
				}
			}
			break;
		
		default:
			//MyPrintf("\nMocMsgProxy - MocMsgProxy_ProcessL4Indication - ERROR - L4 indication of unhandled type arrived. L4 indication = %d. \n", opcode);
			TRACE(TR_MOD_MocMsgProxy, TR_SEV_ERR, "L4 indication of unhandled type arrived. L4 indication = %d. ", opcode);
	}

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_ProcessL4Indication(OUT)");
}


void MocMsgProxy_EventHandler( 
						 L5_CONNECTION Conn,
						 L5_EVENT eEvent,
						 void *pvEventData,
						 void *pvUserContext )
{
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvEventData);
	UNREFERENCED_PARAMETER(pvUserContext);

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_NOTICE, "Got event - %d",eEvent);

	if (eEvent == L5_EVENT_DRIVER_DISCONNECTED)
	{
		TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "calling MocMsgProxy_ReleaseSocketIDs..");
		MocMsgProxy_ReleaseSocketIDs();
	}
}
static void MocMsgProxy_MessagesHandler( 
	L5_CONNECTION Conn,
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
	UNREFERENCED_PARAMETER(Conn);
	UNREFERENCED_PARAMETER(pvReserved);
	UNREFERENCED_PARAMETER(pvUserContext);

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_MessagesHandler(IN)");

	switch(dwSentMessageID)
	{
		case MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID:
			if (cbSentBufferSize != 1 || !initialized)
			{
				*((UINT8*)pvResponseBuffer) = MOC_PROXY_INVALID_SOCKET_ID;
				if (!initialized)
				{
					TRACE(TR_MOD_MocMsgProxy, TR_SEV_WARNING, "Not initialized - Discarded a MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID message from TargetID=%d. ", nOriginID);
				}
			}
			else
			{
				*((UINT8*)pvResponseBuffer) = MocMsgProxy_AcquireSocketID(nOriginID, *((UINT8*)pvSentBuffer));				
			}
			*cbResponseBufferSize = 1;
			*pdwResponseMessageID = MOC_PROXY_L5_MSG_ID_ACQUIRE_SOCKET_ID_RESPONSE;
			break;
		case MOC_PROXY_L5_MSG_ID_RELEASE_SOCKET_ID_INDICATION:
			if (initialized)
			{
				MocMsgProxy_ReleaseSocketID(nOriginID, pvSentBuffer, cbSentBufferSize);				
			}
			else
			{
				TRACE(TR_MOD_MocMsgProxy, TR_SEV_WARNING, "Not initialized - Discarded a MOC_PROXY_L5_MSG_ID_RELEASE_SOCKET_ID_INDICATION message from TargetID=%d. ", nOriginID);
			}
			break;
		case L4_PROXY_OPCODE_L4_INDICATION_ARRIVED:			
			if (initialized)
			{
				MocMsgProxy_ProcessL4Indication(pvSentBuffer, cbSentBufferSize);
			}
			else
			{
				TRACE(TR_MOD_MocMsgProxy, TR_SEV_WARNING, "Not initialized - Discarded a L4_PROXY_OPCODE_L4_INDICATION_ARRIVED message from TargetID=%d. ", nOriginID);
			}
			break;
		default:
			break;
	}

	TRACE(TR_MOD_MocMsgProxy, TR_SEV_DEBUG, "MocMsgProxy_MessagesHandler(OUT)");
}


//void MocMsgProxy_EventHandler( 
//	L5_CONNECTION Conn,
//	L5_EVENT eEvent,
//	void *pvEventData,
//	void *pvUserContext )
//{
//	UNREFERENCED_PARAMETER(Conn);
//	UNREFERENCED_PARAMETER(pvUserContext);
//
//	if (!initialized)
//	{
//		TRACE(TR_MOD_MocMsgProxy, TR_SEV_WARNING, "Not initialized - Discarded an event. ");
//		return;
//	}
//
//	if (eEvent == L5_EVENT_OTHER_DISCONNECTED)
//	{
//		//MyPrintf("\nMocMsgProxy - MocMsgProxy_EventHandler - Got L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION. TargetID = %d \n", (int)pvEventData);
//		TRACE(TR_MOD_MocMsgProxy, TR_SEV_INFO, "Got L5_CONTROL_MESSAGE_OTHER_DISCONNECTED_NOTIFICATION. TargetID = %d", (int)pvEventData);
//		MocMsgProxy_ReleaseSocketIDByTarget((L5_TARGET_ID)pvEventData);
//	}
//}
