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
#pragma warning(disable : 4201) // warning C4201: nonstandard extension used : nameless struct/union

#include "KDapiAdapter.h"
#include "SVstatus.h"

#include "TraceModule.h"
#include "L4ConfigurationManager.h"
#include "L5Common.h"
#include "WrappersUtils.h"

#include "Act.h"
#include "L4MsgProxy.h"
#include "wimax_osal_primitives.h"
#include "wimax_osal_string.h"


static IndicationCallback indCallback = NULL;
static TraceIndicationCallback trcCallback = NULL;
static UINT32 registeredInds[MAX_STATUS_IND_IDS];
static TARGET_ID targetId = MINIPORT_DRIVER;
static UINT32 gDump;
extern DRIVER_STATUS isDriverConnected;
static BOOL useDeviceTraces = FALSE;
static BOOL isStarted = FALSE;
static char *msgBuffer = NULL;

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_RestartDriverConnection()
{
	KDAPI_ADAPTER_RESULT status = KDAPI_ADAPTER_SUCCESS;

	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_DEBUG, "Enter KDAPI_ADAPTER_RestartDriverConnection");

	KDAPI_RestartDriverConnection();

	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_DEBUG, "Leave KDAPI_ADAPTER_RestartDriverConnection");		

	return status;
}

void KDAPI_ADAPTER_DsimStatusIndicationHandler( UINT32 statusID, char* buf, UINT32 bufSize )
{
	int i;

	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_INFO, "Indication arrived, sent to 0x%x", indCallback);
	if( indCallback != NULL )
	{
		// check if this statusID is registered
		for( i = 0; i < MAX_STATUS_IND_IDS; i++ )
		{
			if( registeredInds[i] == statusID )
			{
				if (gDump)
				{
					DumpHexString("FromDriver:",(UCHAR*)buf, bufSize);
				}
				indCallback( statusID, buf, bufSize );
			}
		}
	}
}

void KDAPI_ADAPTER_DriverStatusIndicationHandler( PSTATUS_ENTRY statusEntry )
{
	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_INFO, "Indication arrived, sent to 0x%x", indCallback);
	if( indCallback != NULL )
	{
		if (statusEntry->statusBufLen > STATUS_INDICATION_PAYLOAD_MAX_SIZE)
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "indication length is bigger than STATUS_INDICATION_PAYLOAD_MAX_SIZE");
			l4Proxy_pFuncs->pfnSendErrorReport(L5_TARGET_KDAPI_ADAPTER, DEVICE_PROBLEM,  __FUNCTION__, __LINE__);			
		}
		else
		{			
			if (gDump)
			{
				DumpHexString("FromDriver:",statusEntry->statusBuf, statusEntry->statusBufLen);
			}

			indCallback( statusEntry->status, statusEntry->statusBuf, statusEntry->statusBufLen );
		}
	}
}


void KDAPI_ADAPTER_TracesIndicationHandler( int bufferLength , int *location)
{
	if( trcCallback != NULL )
	{
		trcCallback( bufferLength, location );		
	}
}


// Connect and Disconnect are called over and over by the driver monitor until the Connect succeeds

// Stop is called once by the driver monitor when ACT requests, before starting all finalizations

KDAPI_ADAPTER_RESULT ConvertToKDAPI_ADAPTER_RESULT( UINT32 res, UINT32 detailedRes )
{
	if((targetId == DRIVER_SIM) || (targetId == REMOTE_HOST))
	{
		UNREFERENCED_PARAMETER(detailedRes);

		if( res == KDAPI_FOR_SIM_SUCCESS )
		{
			return KDAPI_ADAPTER_SUCCESS;
		}

		if( res == KDAPI_FOR_SIM_BUFFER_TOO_SHORT )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Bad buffer");
			return KDAPI_ADAPTER_BUFFER_TOO_SHORT;
		}

		if( res == KDAPI_FOR_SIM_BAD_ARGUMENTS )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Bad arguments");
			return KDAPI_ADAPTER_BAD_ARGUMENTS;
		}

		if( res == KDAPI_FOR_SIM_NOT_ACTIVE )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Not connected to the driver");
			return KDAPI_ADAPTER_NOT_ACTIVE;
		}

		if( ( res == KDAPI_FOR_SIM_DRIVER_GENERATED_ERR ) || ( res == KDAPI_FOR_SIM_SOCKET_DISCONNECTED ) )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Driver complained");
			return KDAPI_ADAPTER_DRIVER_GENERATED_ERR;
		}

		// KDAPI_FOR_SIM_ERROR
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Unknown error");
		return KDAPI_ADAPTER_ERROR;
	}
	else if (targetId == MINIPORT_DRIVER)
	{
		if( res == KDAPI_SUCCESS )
		{
			return KDAPI_ADAPTER_SUCCESS;
		}

		if( res == KDAPI_NO_ROOM_FOR_INDICATION )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "No room for indications");
			return KDAPI_ADAPTER_NO_ROOM_FOR_INDICATION;
		}

		if( res == KDAPI_INDICATION_NOT_REGISTERED )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Cannot unregister to unregistered indication");
			return KDAPI_ADAPTER_INDICATION_NOT_REGISTERED;
		}

		if( res == KDAPI_BAD_ARGUMENTS )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Bad arguments");
			return KDAPI_ADAPTER_BAD_ARGUMENTS;
		}

		if( res == KDAPI_NOT_ACTIVE )
		{
			TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Not connected to the driver");
			return KDAPI_ADAPTER_NOT_ACTIVE;
		}

		if( res == KDAPI_DETAILED_ERR )
		{
			if( (STATUS_INVALID_PARAMETER == detailedRes) ||
				(STATUS_NOT_SUPPORTED == detailedRes) )
			{
				TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Driver complained");
				return KDAPI_ADAPTER_DRIVER_GENERATED_ERR;
			}

			if( (STATUS_INVALID_BUFFER_SIZE == detailedRes) ||
				(STATUS_BUFFER_TOO_SMALL == detailedRes) )
			{
				TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "Bad buffer");
				return KDAPI_ADAPTER_BUFFER_TOO_SHORT;
			}
		}
	}

	// KDAPI_ERROR ||
	// KDAPI_DETAILED_ERR:
	//STATUS_UNSUCCESSFUL == detailedRes ||
	//STATUS_DEVICE_NOT_READY == detailedRes ||
	//STATUS_NO_MORE_ENTRIES == detailedRes ||
	//STATUS_PENDING == res ||
	//STATUS_BUFFER_OVERFLOW == detailedRes ||
	//NDIS_STATUS_FAILURE == detailedRes || 
	//NDIS_STATUS_RESOURCES == detailedRes
	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALERT, "unknown error");
	return KDAPI_ADAPTER_ERROR;
	
}




KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_SendReceiveMessage( 
	OID_NUM oidNum,
	void *send_buffer, int send_buffer_size,
	void *receive_buffer, int *receive_buffer_size )
{
	UINT32 res;
	UINT32 detailedRes = 0;

	if (!isStarted)
	{
		return KDAPI_ADAPTER_NOT_ACTIVE;
	}

	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_INFO, "Send message to driver");
	//TODO: add code for message dump
	if (gDump)
	{
		DumpHexString("MsgToDriver:",send_buffer, send_buffer_size);
	}

	if(targetId == DRIVER_SIM)
	{
		res = KDAPI_FOR_SIM_SendQueryOID( 
			oidNum, send_buffer, receive_buffer, send_buffer_size, *receive_buffer_size, (UINT32*)receive_buffer_size );
	}
	else if (targetId == MINIPORT_DRIVER)
	{
		res = KDAPI_SendQueryOID( 
			oidNum, send_buffer, receive_buffer, send_buffer_size, *receive_buffer_size, (UINT32*)receive_buffer_size, &detailedRes );
	}
	else // remote host
	{
		res = KDAPI_ADAPTER_SUCCESS; // do nothing
	}

	if (gDump)
	{
		DumpHexString("MsgRespondFromDriver:",receive_buffer, *receive_buffer_size);
	}
	return ConvertToKDAPI_ADAPTER_RESULT( res, detailedRes );
}

KDAPI_ADAPTER_RESULT InitDriver(BOOL traceEnable)
{
	KDAPI_RESULT res;
	UINT32 detailedRes = 0;

	res = KDAPI_Init(	KDAPI_ADAPTER_DriverStatusIndicationHandler,
						KDAPI_ADAPTER_TracesIndicationHandler,
						&msgBuffer,
						&detailedRes,
						traceEnable);	
	
	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALL, "Returning with %d", res);

	return (KDAPI_SUCCESS != res)?KDAPI_ADAPTER_ERROR:KDAPI_ADAPTER_SUCCESS;
}

KDAPI_ADAPTER_RESULT InitDsim()
{
	KDAPI_FOR_SIM_RESULT res;
	char dSimIpAddress[32] = {0};
	UINT32 dSimOidsPortNum = OidsPort;
	UINT32 dSimIndicationsPortNum = IndsPort;
	
	memset( registeredInds, -1, MAX_STATUS_IND_IDS*sizeof(UINT32) );

	L4Configurations_getDSimIpAddress(dSimIpAddress);
	L4Configurations_getDSimOidsPortNum(&dSimOidsPortNum);
	L4Configurations_getDSimIndicationsPortNum(&dSimIndicationsPortNum);

	//errno = wcstombs_s(&numOfCharConverted, dSimIpAddress_char, sizeof(dSimIpAddress_char), dSimIpAddress, sizeof(dSimIpAddress));

	res = KDAPI_FOR_SIM_Init( targetId, dSimIpAddress, (unsigned short)dSimOidsPortNum, (unsigned short)dSimIndicationsPortNum, KDAPI_ADAPTER_DsimStatusIndicationHandler );

	if (res != KDAPI_FOR_SIM_SUCCESS)
	{
		return KDAPI_ADAPTER_ERROR;
	}

	return KDAPI_ADAPTER_SUCCESS;
}

//KDapiAdapter interface
KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Init(BOOL traceEnable)
{
	UINT32 res;
	errno_t errno;

	char answer[MAX_ANSWER_SIZE];

	//set the useDeviceTraces flag
	useDeviceTraces = traceEnable;

	//determine the target (driver, dsim or remote):
	targetId = MINIPORT_DRIVER;
	res = L4Configurations_getDriverMode(answer);	
	if (0 == OSAL_stricmp("dsim", answer)) 
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALL, "Target: DSim");
		targetId = DRIVER_SIM;
	}
	else if (0 == OSAL_stricmp("remote", answer))
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALL, "Target: remote");
		targetId = REMOTE_HOST;
	}
	else // if nothing is written - we take it as driver
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALL, "Target: Driver");
		targetId = MINIPORT_DRIVER;
	}

	//determine whether to use dump in logs or not:
	res = L4Configurations_getDumpEnable(&gDump);
	if (gDump != 0)
	{
		gDump = 1;
	}

	//initialize the target (driver or dsim):
	if((targetId == DRIVER_SIM) || (targetId == REMOTE_HOST))
	{
		res = InitDsim();
	}
	else if (targetId == MINIPORT_DRIVER)
	{
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_ALL, "Invoking InitDriver");
		res = InitDriver(useDeviceTraces);
	}

	if (res != KDAPI_SUCCESS)
	{
		return KDAPI_ADAPTER_ERROR;
	}
	
	return KDAPI_ADAPTER_SUCCESS;

}

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Fini()
{

	if (targetId == MINIPORT_DRIVER)
	{
		KDAPI_Fini();
	}
	else 
	{
		KDAPI_FOR_SIM_Fini(targetId);
	}

	return KDAPI_ADAPTER_SUCCESS;
}

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Connect()
{
	UINT32 res = 0;

	TRACE(TR_MOD_KDAPI, TR_SEV_DEBUG, "Entering");

	if (targetId == MINIPORT_DRIVER)
	{
		res = KDAPI_Connect();
		TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_DEBUG, " KDAPI Connect returned : %d", res);
	}
	else
	{
		res = KDAPI_FOR_SIM_Connect(targetId);
	}

	return ConvertToKDAPI_ADAPTER_RESULT(res, 0);
}

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Disconnect()
{
	if (targetId == MINIPORT_DRIVER)
	{
		KDAPI_Disconnect();
	}
	else 
	{
		KDAPI_FOR_SIM_Disconnect(targetId);
	}

	return KDAPI_ADAPTER_SUCCESS;
}

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_Start()
{
	KDAPI_RESULT res;

	if (targetId == MINIPORT_DRIVER)
	{
		res = KDAPI_Start();
		if (KDAPI_SUCCESS!=res)
		{
			return KDAPI_ADAPTER_ERROR;
		}
	}
	else
	{
		if (KDAPI_SUCCESS != KDAPI_FOR_SIM_Start())
		{
			return KDAPI_ADAPTER_ERROR;
		}
	}

	// Notifying ACT that the driver is UP
	Act_DriverDeviceStatus(DRIVER_UP);

	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_DEBUG, "KDAPI_ADAPTER_Start - OSAL_reset_event(kdapiAdapterStopEvent)");

	isStarted = TRUE;
	return KDAPI_ADAPTER_SUCCESS;
}

void KDAPI_ADAPTER_Stop()
{
	// Notifying ACT that the driver is DOWN
	Act_DriverDeviceStatus(DRIVER_DOWN);

	isStarted = FALSE;

	if (targetId == MINIPORT_DRIVER)
	{
		KDAPI_Stop();
	}
	else
	{
		KDAPI_FOR_SIM_Stop(targetId);
	}

	TRACE(TR_MOD_KDAPI_ADAPTER, TR_SEV_DEBUG, "KDAPI_ADAPTER_Stop - OSAL_set_event(kdapiAdapterStopEvent)");
}

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_RegisterOnIndication( STATUS_IND_ID indication_id )
{
	UINT32 res = KDAPI_ADAPTER_SUCCESS;
	UINT32 detailedRes = 0;

	if( indCallback == NULL )
	{
		return KDAPI_ADAPTER_ERROR;
	}

	if((targetId == DRIVER_SIM) || (targetId == REMOTE_HOST))
	{
		int i;
		// if already registered for that indication_id do nothing
		for( i = 0; i < MAX_STATUS_IND_IDS; i++ )
		{
			if( registeredInds[i] == indication_id )
			{
				return KDAPI_ADAPTER_SUCCESS;
			}
		}

		// search for an empty spot for the indication_id
		for( i = 0; i < MAX_STATUS_IND_IDS; i++ )
		{
			if( registeredInds[i] == -1 )
			{
				registeredInds[i] = indication_id;
				break;
			}
		}

		// no room for a new indication_id
		if( i == MAX_STATUS_IND_IDS )
		{
			return KDAPI_ADAPTER_NO_ROOM_FOR_INDICATION;
		}
	}
	else if (targetId == MINIPORT_DRIVER)
	{
		res = KDAPI_DriverStatusRegister( indication_id, &detailedRes );
	}

	return ConvertToKDAPI_ADAPTER_RESULT( res, detailedRes );
}

KDAPI_ADAPTER_RESULT KDAPI_ADAPTER_UnregisterOnIndication( STATUS_IND_ID indication_id )
{
	UINT32 res = KDAPI_ADAPTER_SUCCESS;
	UINT32 detailedRes = 0;

	if((targetId == DRIVER_SIM) || (targetId == REMOTE_HOST))
	{
		int i;

		// if the indication_id was registered, release its spot
		for( i = 0; i < MAX_STATUS_IND_IDS; i++ )
		{
			if( registeredInds[i] == indication_id )
			{
				registeredInds[i] = 0xffffffff;
				break;
			}
		}

		// the given indication_id wasn't registered
		if( i == MAX_STATUS_IND_IDS )
		{
			return KDAPI_ADAPTER_INDICATION_NOT_REGISTERED;
		}
	}
	else if (targetId == MINIPORT_DRIVER)
	{
		res = KDAPI_DriverStatusUnRegister( indication_id, &detailedRes );
	}

	return ConvertToKDAPI_ADAPTER_RESULT( res, detailedRes );
}


void KDAPI_ADAPTER_SetDriverIndicatiosCB(IndicationCallback callback)
{
	indCallback = callback;
}

EXTERN_C EXPORT void KDAPI_ADAPTER_SetTraceIndicatiosCB(TraceIndicationCallback callback, char **trcBuffer)
{
	trcCallback = callback;
	*trcBuffer = msgBuffer;
}

void KDAPI_ADAPTER_ResetDevice()
{
	if (targetId == MINIPORT_DRIVER)
	{
		KDAPI_ResetDevice();
	}
}
