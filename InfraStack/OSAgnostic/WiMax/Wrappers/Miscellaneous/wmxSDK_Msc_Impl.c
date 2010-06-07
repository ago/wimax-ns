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
#include "wimax_osal_primitives.h"
#include "wimax_osal_config_controler.h"

#include "wmxSDK_Msc_CtrlAgent.h"
#include "wmxSDK_Msc_Ctrl.h"
#include "wmxSDK_Msc_L5.h"
#include "wmxSDK_Msc_2.h"
#include "wmxSDK_Nds_2.h"

#include "L5Common.h"
#include "L5OpCodes.h"		
#include "WrappersUtils.h"
#include "L3L4CommonDefines.h"
#include "L3L4TlvTypes.h"
#include "L4BufMan_L3L4Structs_Desc.h"

#include "Messenger.h"
#include "TraceModule.h"




#define MAC_ADDRESS_SIZE		6
#define VERSIONS_STRINGS_SIZE	100
#define	SF_LIST_SIZE			16
//************************************************
// Connection Parameters to L5 Layer
//************************************************
static LONG numOfInits = 0;
static L5_CONNECTION msc_l5ConnID = NULL;
static tL5DispatcherFunctions *msc_pFuncs = NULL;

wmx_Status_t wmxMsc_InitL5()
{	
	L5_RESULT l5status;
	msc_pFuncs = GetL5Funcs();
	if (NULL == msc_pFuncs)
	{
		return WMX_ST_PIPE_FAILURE;
	}

	// Connect L5 and through it to AppSrv. Gain L5ConnID.
	l5status = msc_pFuncs->pfnConnectEx(
									L5_TARGET_DYNAMIC,
									NULL, 
									NULL,
									NULL,
									THREAD_ID_DEFAULT,
									&msc_l5ConnID	);

	if ((L5_RESULT_OK != l5status) || (NULL == msc_l5ConnID))
	{
		return WMX_ST_PIPE_FAILURE;
	}
	return WMX_ST_OK;
}

void wmxMsc_FinalizeL5()
{
	if (msc_pFuncs != NULL)
	{
		msc_pFuncs->pfnDisconnect(msc_l5ConnID);
		msc_pFuncs = NULL;
	}
}


//void wmxMsc_MessagesHandler(L5_CONNECTION Conn,
//											L5_TARGET_ID nOriginID,
//
//											UINT32 dwSentMessageID,
//											void  *pvSentBuffer,
//											UINT32 cbSentBufferSize,
//
//											UINT32 *pdwResponseMessageID,
//											void  *pvResponseBuffer,
//											UINT32 *cbResponseBufferSize,
//
//											void *pvUserContext,
//											void *pvReserved )
//{
//	UNREFERENCED_PARAMETER(nOriginID);
//	UNREFERENCED_PARAMETER(cbResponseBufferSize);
//	UNREFERENCED_PARAMETER(pdwResponseMessageID);
//	UNREFERENCED_PARAMETER(pvReserved);
//	UNREFERENCED_PARAMETER(Conn);
//	UNREFERENCED_PARAMETER(pvResponseBuffer);
//	UNREFERENCED_PARAMETER(pvUserContext);
//
//	switch (dwSentMessageID)
//	{
//		default:
//			break;
//	}
//}
//
//void wmxMsc_EventHandler( L5_CONNECTION Conn, L5_EVENT eEvent, void *pvEventData, void *pvUserContext)
//{
//	UNREFERENCED_PARAMETER(Conn);
//	UNREFERENCED_PARAMETER(eEvent);
//	UNREFERENCED_PARAMETER(pvEventData);
//	UNREFERENCED_PARAMETER(pvUserContext);
//}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxMsc_Init()
{
	wmx_Status_t status;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_Status_t wmxMsc_Init()");
        
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfInits) )
	{		
		status = wmxMsc_InitL5();
		if ( WMX_ST_OK != status )
		{
			TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "can't init l5 connection!!");
			wmxMsc_Finalize();
			return status;
		}			
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_Status_t wmxMsc_Init(OUT)");

	return WMX_ST_OK;
}

void WMX_WRAPPER_API WMX_EXT_CALL_CONV wmxMsc_Finalize()
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "void wmxMsc_Finalize()");
    
    
	if ( LAST_INIT == OSAL_atomic_decrement(&numOfInits) )
	{
		wmxMsc_FinalizeL5();		
	}

	OSAL_atomic_compareExchange(&numOfInits, LAST_INIT, LAST_INIT - 1);
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_Status_t wmxMsc_Finalize(OUT)");

}

wmx_Status_t wmxMsc_InitAgent()
{   
	wmx_Status_t st;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxMsc_InitAgent()");
 
	if ( FIRST_REGISTERED == OSAL_atomic_increment(&numOfInits) )
	{
		st = wmxMsc_InitL5();
		if( st != WMX_ST_OK )
		{
			wmxMsc_FinalizeAgent();

		    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmxMsc_InitAgent(OUT ERROR)");
			return st;
		}
	}

	   
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "wmx_Status_t wmxMsc_InitAgent(OUT)");
	return WMX_ST_OK;
}

void wmxMsc_FinalizeAgent()
{
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "void wmxMsc_FinalizeAgent()");
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "void wmxMsc_FinalizeAgent(OUT)");
    
	if ( LAST_INIT == OSAL_atomic_decrement(&numOfInits) )
	{
		wmxMsc_FinalizeL5();
	}

	OSAL_atomic_compareExchange(&numOfInits, LAST_INIT, LAST_INIT - 1);
}


// returns false when there are no versions left
BOOL wmxMsc_CopyNextVersion(char **curPosition, char *version, UINT32 versionLen)
{
	size_t strLength = OSAL_strnlen(*curPosition, versionLen);
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "versions wmxMsc_CopyNextVersion(IN)");

	if (version != NULL)
	{
		memcpy(version, *curPosition, strLength + 1);
	}

	*curPosition += strLength + 1;  // 1 for the \0
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "versions wmxMsc_CopyNextVersion(OUT)");

	return TRUE;
}

wmx_Status_t wmxMsc_GetWmxStatus(void *l4Buffer)
{
	L3L4CompleteHeader_type *l3L4CompleteHeader;
	wmx_Status_t status;

	l3L4CompleteHeader = (L3L4CompleteHeader_type*)l4Buffer;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmxMsc_GetWmxStatus(IN)");
	status = wmx_L4ResultToWMXStatus((E_L3L4ResponseStatus)l3L4CompleteHeader->Status);

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmxMsc_GetWmxStatus(OUT)");
	return status;
}




wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceDetails(wmx_MacAddress_t macAddress,
																	wmx_pModelType_t modelType,
																	wmx_pManufacturer_t manufacturer,
																	wmx_pSerialNumber_t serialNumber) 
{
	GetDeviceInfo_type deviceInfo;
	wmx_Status_t driver_st, send_st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceDetails (IN)");
	L4BM_Init_GetDeviceInfo( &deviceInfo );
	send_st = wmx_SendL4Command( &deviceInfo, GetDeviceInfo_Funcs, *msc_pFuncs, msc_l5ConnID, &driver_st );

	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	if (deviceInfo.DeviceDetails.Type == L3L4_TLV_TYPE_DEVICE_DETAILS)
	{

		// Copy macAddress
		OSAL_memcpy_s(macAddress, sizeof(deviceInfo.DeviceDetails.MacAddress), deviceInfo.DeviceDetails.MacAddress, sizeof(deviceInfo.DeviceDetails.MacAddress));

		// Copy modelType
		(*modelType).modelTypeID = deviceInfo.DeviceDetails.ModelType;
		if (deviceInfo.DeviceDetails.ModelTypeStringLength > 0)
		{
			OSAL_L3L4_WideCharToMultiByte(CP_ACP, 0, (WIMAX_CHAR *)deviceInfo.DeviceDetails.ModelTypeString, -1, (*modelType).modelTypeName, sizeof(deviceInfo.DeviceDetails.ModelTypeString), NULL, NULL);
		}

		// Copy manufacturer
		/* //This is the Old manufacturer ID, this is static data and so we take different information.
		(*manufacturer).manufacturerID = deviceInfo.DeviceDetails.ManufacturerId;
		if (deviceInfo.DeviceDetails.ManufacturerIdStringLength > 0)
		{
		OSAL_memcpy_s((*manufacturer).manufacturerName, sizeof((*manufacturer).manufacturerName), (const char*)deviceInfo.DeviceDetails.ManufacturerIdString, sizeof(deviceInfo.DeviceDetails.ManufacturerIdString));
		}
		*/

		// Copy SerialNumber
		if (deviceInfo.DeviceDetails.NvmProductStringLength > 0)
		{
			OSAL_L3L4_WideCharToMultiByte(CP_ACP, 0, (WIMAX_CHAR *)deviceInfo.DeviceDetails.NvmProductString, -1, (*serialNumber).serialNumber, sizeof(deviceInfo.DeviceDetails.NvmProductString), NULL, NULL);
		}
	}
	else
	{
		send_st = WMX_ST_DEVICE_FAILURE;
	}

	if (deviceInfo.NvmManufacturer.Type == L3L4_TLV_TYPE_NVM_MANID)
	{
		// Copy manufacturer
		(*manufacturer).manufacturerID = deviceInfo.DeviceDetails.ManufacturerId;
		if (deviceInfo.NvmManufacturer.NvmManufacturerIdStringLength > 0)
		{
			OSAL_L3L4_WideCharToMultiByte(CP_ACP, 0, (WIMAX_CHAR *)deviceInfo.NvmManufacturer.NvmManufacturerIdString, -1, (*manufacturer).manufacturerName, sizeof(deviceInfo.NvmManufacturer.NvmManufacturerIdString), NULL, NULL);
		}
	}
	else
	{
		send_st = WMX_ST_DEVICE_FAILURE;
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceDetails (OUT)");
	return send_st;	
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceDetailsEx(	wmx_MacAddress_t macAddress,
																		wmx_pModelType_t modelType,
																		wmx_pManufacturer_t manufacturer,
																		wmx_pSerialNumber_t serialNumber,
																		wmx_pNvmVersion_t nvmVersion,
																		wmx_pODMInfo_t odmInfo,
																		wmx_pNonce_t nonce,
																		wmx_pDevicePID_t pid) 
{
	GetDeviceInfo_type deviceInfo;
	wmx_Status_t driver_st, send_st;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceDetails (IN)");
	L4BM_Init_GetDeviceInfo( &deviceInfo );
	send_st = wmx_SendL4Command( &deviceInfo, GetDeviceInfo_Funcs, *msc_pFuncs, msc_l5ConnID, &driver_st );

	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	if (deviceInfo.DeviceDetails.Type == L3L4_TLV_TYPE_DEVICE_DETAILS)
	{

		// Copy macAddress
		OSAL_memcpy_s(macAddress, sizeof(deviceInfo.DeviceDetails.MacAddress), deviceInfo.DeviceDetails.MacAddress, sizeof(deviceInfo.DeviceDetails.MacAddress));
		
		// Copy modelType
		(*modelType).modelTypeID = deviceInfo.DeviceDetails.ModelType;
		if (deviceInfo.DeviceDetails.ModelTypeStringLength > 0)
		{
			OSAL_L3L4_WideCharToMultiByte(CP_ACP, 0, (WIMAX_CHAR *)deviceInfo.DeviceDetails.ModelTypeString, -1, (*modelType).modelTypeName, sizeof(deviceInfo.DeviceDetails.ModelTypeString), NULL, NULL);
		}

		// Copy manufacturer
		//This is the Old manufacturer ID, this is static data and so we take different information.
		(*manufacturer).manufacturerID = deviceInfo.DeviceDetails.ManufacturerId;
		if (deviceInfo.DeviceDetails.ManufacturerIdStringLength > 0)
		{
			OSAL_memcpy_s((*manufacturer).manufacturerName, sizeof((*manufacturer).manufacturerName), (const char*)deviceInfo.DeviceDetails.ManufacturerIdString, sizeof((*manufacturer).manufacturerName));
		}
		

		// Copy SerialNumber
		if (deviceInfo.DeviceDetails.NvmProductStringLength > 0)
		{
			OSAL_L3L4_WideCharToMultiByte(CP_ACP, 0, (WIMAX_CHAR *)deviceInfo.DeviceDetails.NvmProductString, -1, (*serialNumber).serialNumber, sizeof(deviceInfo.DeviceDetails.NvmProductString), NULL, NULL);
		}

		// Copy Nonce
		OSAL_memcpy_s(nonce, sizeof(wmx_Nonce_t), (const char*)deviceInfo.DeviceDetails.Nonce, sizeof(wmx_Nonce_t));
		send_st = WMX_ST_OK;
	}
	else
	{
		send_st = WMX_ST_DEVICE_FAILURE;
	}

	if (deviceInfo.NvmManufacturer.Type == L3L4_TLV_TYPE_NVM_MANID)
	{
		// Copy manufacturer
		if (deviceInfo.NvmManufacturer.NvmManufacturerIdStringLength > 0)
		{
			OSAL_L3L4_WideCharToMultiByte(CP_ACP, 0, (WIMAX_CHAR *)deviceInfo.NvmManufacturer.NvmManufacturerIdString, -1, (*manufacturer).manufacturerName, sizeof(deviceInfo.NvmManufacturer.NvmManufacturerIdString), NULL, NULL);
		}
	}
	else
	{
		send_st = WMX_ST_DEVICE_FAILURE;
	}

	if (deviceInfo.DevicePID.Type == L3L4_TLV_TYPE_DEVICE_PID)
	{
		// Copy PID
		(*pid).productID = deviceInfo.DevicePID.PID;		
	}
	else
	{
		send_st = WMX_ST_DEVICE_FAILURE;
	}

	if (deviceInfo.NvmInformation.Type == L3L4_TLV_TYPE_NVM_INFORMATION)
	{
		(*nvmVersion).ContentVersion = deviceInfo.NvmInformation.ContentVersion;
		(*nvmVersion).GeneralImageVersion = deviceInfo.NvmInformation.GeneralImageVersion;
	}
	else
	{
		(*nvmVersion).ContentVersion = 0;
		(*nvmVersion).GeneralImageVersion = 0;
	}

	if (deviceInfo.OdmInformation.Type == L3L4_TLV_TYPE_ODM_INFORMATION)
	{
		OSAL_memcpy_s((void*)(odmInfo), ODM_INFO_SIZE, deviceInfo.OdmInformation.OdmInformation, ODM_INFO_SIZE);
		
	}
	else
	{
		OSAL_memcpy_s((void*)(odmInfo), ODM_INFO_SIZE, "\0", ODM_INFO_SIZE);
	}

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceDetails (OUT)");
	return send_st;	
}

// Get the versions of the device
wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_GetDeviceVersion(	wmx_pDeviceVersion_t pDeviceVersion	)
{
	BOOL versionsLeft;	
	char *curPosition;

	wmx_Status_t driver_st, send_st;
	GetDeviceInfo_type deviceInfo;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceVersion(IN)");

	L4BM_Init_GetDeviceInfo( &deviceInfo );
	send_st = wmx_SendL4Command( &deviceInfo, GetDeviceInfo_Funcs, *msc_pFuncs, msc_l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

	if (deviceInfo.VersionsStrings.Type == L3L4_TLV_TYPE_VERSIONS_STRINGS)
	{
		curPosition = (char*)deviceInfo.VersionsStrings.BufferArr;

		// wmxMsc_CopyNextVersion returns false if the last version was NULL
		versionsLeft = wmxMsc_CopyNextVersion(&curPosition, pDeviceVersion->Asic, WMX_DEVICE_VERSION_MAX_LENGTH);
		if (versionsLeft == FALSE) return WMX_ST_FAIL;
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pDeviceVersion->Asic %s",pDeviceVersion->Asic);

		versionsLeft = wmxMsc_CopyNextVersion(&curPosition, pDeviceVersion->Board, WMX_DEVICE_VERSION_MAX_LENGTH);
		if (versionsLeft == FALSE) return WMX_ST_FAIL;
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pDeviceVersion->Board %s",pDeviceVersion->Board);

		versionsLeft = wmxMsc_CopyNextVersion(&curPosition, pDeviceVersion->Software, WMX_DEVICE_VERSION_MAX_LENGTH);
		if (versionsLeft == FALSE) return WMX_ST_FAIL;
		TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_INFO, "pDeviceVersion->Software %s",pDeviceVersion->Software);
	}
	else
	{
	    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_ERR, "wmx_Status_t wmx_GetDeviceVersion(OUT ERROR)");

		return WMX_ST_DEVICE_FAILURE;
	}
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_GetDeviceVersion(OUT)");

	return WMX_ST_OK;
}


wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_ResetDevice( )
{
	wmx_Status_t send_st;
	ResetDeviceCommand_type resetCmd;

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_ResetDevice(IN)");

	L4BM_Init_ResetDeviceCommand( &resetCmd );
	resetCmd.ResetDevice.Type = L3L4_TLV_TYPE_DEVICE_RESET;
	resetCmd.ResetDevice.value = E_RESET_COMMAND_WARM;

	send_st = wmx_SendL5Command(L5_TARGET_ACT, ACT_OPCODE_RESET_DEVICE, *msc_pFuncs, msc_l5ConnID, NULL, 0, NULL, NULL);
	//send_st = wmx_SendL4Command( &resetCmd, ResetDeviceCommand_Funcs, *msc_pFuncs, msc_l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}
    
    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_ResetDevice(OUT)");
	return WMX_ST_OK;
}

wmx_Status_t WMX_WRAPPER_API WMX_EXT_CALL_CONV wmx_SetModeOfOperation( wmx_ModeOfOperation_t modeOfOperation )
{   
	wmx_Status_t driver_st, send_st;
	ModeOfOperationCommand_type operationCmd;

	TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetModeOfOperation(IN)");
    
	L4BM_Init_ModeOfOperationCommand( &operationCmd );
	operationCmd.ModeOfOperation.Type = L3L4_TLV_TYPE_MODE_OF_OPERATION;
	operationCmd.ModeOfOperation.value = (modeOfOperation == ModeOfOperationProduction) ? E_MODE_OF_OPERATION_PRODUCTION : E_MODE_OF_OPERATION_NORMAL;

	send_st = wmx_SendL4Command( &operationCmd, ModeOfOperationCommand_Funcs, *msc_pFuncs, msc_l5ConnID, &driver_st );
	if( send_st != WMX_ST_OK )
	{
		return send_st;
	}

	if( driver_st != WMX_ST_OK )
	{
		return driver_st;
	}

    TRACE(TR_MOD_WRAPPER_LOGS, TR_SEV_NOTICE, "wmx_SetModeOfOperation(OUT)");
	return WMX_ST_OK;
}
