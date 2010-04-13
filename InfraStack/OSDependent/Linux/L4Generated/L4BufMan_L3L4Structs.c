
/****************************************************************************
*
* Auto generated file
* Version XXX
* Compliant with XXX.bm version XXX
* 11/19/2009 12:55:59 AM
*
*****************************************************************************/


#include "L4BufMan_L3L4Structs.h"
#include "L3L4Structs.h"





//
// GetL4MVersion
//
L4BUFMAN_Status_t L4BM_Get_GetL4MVersion(GetL4MVersion_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_GetL4MVersion(pMsg);
	BM_GetL4MVersion_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetL4MVersion_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetL4MVersion_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetL4MVersion_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetL4MVersion_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetL4MVersion_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetL4MVersion_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 129 )
			{
				pMsg->L4MVersion.Type = (UINT16)type;
				BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMajor_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MVersion.VersionMajor );
				BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMinor_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MVersion.VersionMinor );
				BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionBranch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MVersion.VersionBranch );
				BM_GetL4MVersion_List_CURRENT_L4MVersion_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MVersion.Reserved2 );
			}
			if( type == 135 )
			{
				pMsg->L4MProductionVersion.Type = (UINT16)type;
				BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMajor_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MProductionVersion.VersionMajor );
				BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMinor_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MProductionVersion.VersionMinor );
				BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionBranch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MProductionVersion.VersionBranch );
				BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MProductionVersion.Reserved2 );
			}
			if( type == 136 )
			{
				pMsg->L4MDnDVersion.Type = (UINT16)type;
				BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMajor_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MDnDVersion.VersionMajor );
				BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMinor_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MDnDVersion.VersionMinor );
				BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionBranch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MDnDVersion.VersionBranch );
				BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->L4MDnDVersion.Reserved2 );
			}

			BM_GetL4MVersion_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetL4MVersion(UINT8* pBuf, GetL4MVersion_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_GetL4MVersion_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.L4MVersion.Type == 129 )
	{
		BM_GetL4MVersion_List_SET_TYPE( cur_ptr, cur_bitoff, 129 );
		length = 8;
		BM_GetL4MVersion_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMajor_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MVersion.VersionMajor );
		BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionMinor_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MVersion.VersionMinor );
		BM_GetL4MVersion_List_CURRENT_L4MVersion_VersionBranch_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MVersion.VersionBranch );
		BM_GetL4MVersion_List_CURRENT_L4MVersion_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MVersion.Reserved2 );
		BM_GetL4MVersion_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L4MProductionVersion.Type == 135 )
	{
		BM_GetL4MVersion_List_SET_TYPE( cur_ptr, cur_bitoff, 135 );
		length = 8;
		BM_GetL4MVersion_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMajor_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MProductionVersion.VersionMajor );
		BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionMinor_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MProductionVersion.VersionMinor );
		BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_VersionBranch_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MProductionVersion.VersionBranch );
		BM_GetL4MVersion_List_CURRENT_L4MProductionVersion_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MProductionVersion.Reserved2 );
		BM_GetL4MVersion_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.L4MDnDVersion.Type == 136 )
	{
		BM_GetL4MVersion_List_SET_TYPE( cur_ptr, cur_bitoff, 136 );
		length = 8;
		BM_GetL4MVersion_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMajor_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MDnDVersion.VersionMajor );
		BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionMinor_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MDnDVersion.VersionMinor );
		BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_VersionBranch_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MDnDVersion.VersionBranch );
		BM_GetL4MVersion_List_CURRENT_L4MDnDVersion_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.L4MDnDVersion.Reserved2 );
		BM_GetL4MVersion_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetL4MVersion_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_LM_VERSION );
	BM_GetL4MVersion_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetL4MVersion_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetL4MVersion_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetL4MVersion_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetL4MVersion(UINT8* pBuf, GetL4MVersion_type* msg)
{
	return L4BM_Set_GetL4MVersion(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetL4MVersion(GetL4MVersion_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.L4MVersion.Type == 129 )
	{
		length += 8;
		length += 4;
	}
	if( msg.L4MProductionVersion.Type == 135 )
	{
		length += 8;
		length += 4;
	}
	if( msg.L4MDnDVersion.Type == 136 )
	{
		length += 8;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetL4MVersion(GetL4MVersion_type* msg)
{
	return L4BM_GetBufferSize_GetL4MVersion(*msg);
}
UINT L4BM_GetMaxBufferSize_GetL4MVersion( void )
{
	UINT32 length = HEADER_SIZE;

	length += 8;
	length += 4;
	length += 8;
	length += 4;
	length += 8;
	length += 4;

	return length;
}
void L4BM_Init_GetL4MVersion(GetL4MVersion_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->L4MVersion.Type = INVALID_OPCODE;
	pMsg->L4MProductionVersion.Type = INVALID_OPCODE;
	pMsg->L4MDnDVersion.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetL4MVersion_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetL4MVersion,
	(pf_SetL4Command)L4BM_generic_Set_GetL4MVersion,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetL4MVersion,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetL4MVersion,
	(pf_InitL4Command)L4BM_Init_GetL4MVersion
};



//
// ReportKeyRequest
//
L4BUFMAN_Status_t L4BM_Get_ReportKeyRequest(ReportKeyRequest_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_ReportKeyRequest_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportKeyRequest_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportKeyRequest_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportKeyRequest(UINT8* pBuf, ReportKeyRequest_type msg)
{
	PVOID base_ptr = pBuf;

	ReportKeyRequest_type tmp = msg;
	tmp = tmp;

	BM_ReportKeyRequest_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_KEY_REQUEST );
	BM_ReportKeyRequest_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportKeyRequest_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportKeyRequest_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportKeyRequest_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportKeyRequest(UINT8* pBuf, ReportKeyRequest_type* msg)
{
	return L4BM_Set_ReportKeyRequest(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportKeyRequest(ReportKeyRequest_type msg)
{

	ReportKeyRequest_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_ReportKeyRequest(ReportKeyRequest_type* msg)
{
	return L4BM_GetBufferSize_ReportKeyRequest(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportKeyRequest( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_ReportKeyRequest(ReportKeyRequest_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs ReportKeyRequest_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportKeyRequest,
	(pf_SetL4Command)L4BM_generic_Set_ReportKeyRequest,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportKeyRequest,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportKeyRequest,
	(pf_InitL4Command)L4BM_Init_ReportKeyRequest
};



//
// TLSOperationRequest
//
L4BUFMAN_Status_t L4BM_Get_TLSOperationRequest(TLSOperationRequest_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_TLSOperationRequest(pMsg);
	BM_TLSOperationRequest_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_TLSOperationRequest_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_TLSOperationRequest_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_TLSOperationRequest_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_TLSOperationRequest_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_TLSOperationRequest_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_TLSOperationRequest_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1033 )
			{
				pMsg->Common.Type = (UINT16)type;
				BM_TLSOperationRequest_List_CURRENT_Common_Operation_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->Common.Operation );
				BM_TLSOperationRequest_List_CURRENT_Common_LParameter1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->Common.LParameter1 );
				BM_TLSOperationRequest_List_CURRENT_Common_LParameter2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->Common.LParameter2 );
				BM_TLSOperationRequest_List_CURRENT_Common_Context_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->Common.Context );
				BM_TLSOperationRequest_List_CURRENT_Common_Connection_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->Common.Connection );
			}
			if( type == 1034 )
			{
				pMsg->ExchangeBuffer.Type = (UINT16)type;
				BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ExchangeBuffer.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->ExchangeBuffer.ActualLen; i0++ )
				{
					BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ExchangeBuffer.BufferArr[i0].value );
				}
			}
			if( type == 1035 )
			{
				pMsg->AppOutputBuffer.Type = (UINT16)type;
				BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->AppOutputBuffer.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->AppOutputBuffer.ActualLen; i0++ )
				{
					BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->AppOutputBuffer.BufferArr[i0].value );
				}
			}

			BM_TLSOperationRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_TLSOperationRequest(UINT8* pBuf, TLSOperationRequest_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_TLSOperationRequest_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.Common.Type == 1033 )
	{
		BM_TLSOperationRequest_List_SET_TYPE( cur_ptr, cur_bitoff, 1033 );
		length = 20;
		BM_TLSOperationRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_TLSOperationRequest_List_CURRENT_Common_Operation_SET( base_ptr, cur_ptr, cur_bitoff, msg.Common.Operation );
		BM_TLSOperationRequest_List_CURRENT_Common_LParameter1_SET( base_ptr, cur_ptr, cur_bitoff, msg.Common.LParameter1 );
		BM_TLSOperationRequest_List_CURRENT_Common_LParameter2_SET( base_ptr, cur_ptr, cur_bitoff, msg.Common.LParameter2 );
		BM_TLSOperationRequest_List_CURRENT_Common_Context_SET( base_ptr, cur_ptr, cur_bitoff, msg.Common.Context );
		BM_TLSOperationRequest_List_CURRENT_Common_Connection_SET( base_ptr, cur_ptr, cur_bitoff, msg.Common.Connection );
		BM_TLSOperationRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ExchangeBuffer.Type == 1034 )
	{
		BM_TLSOperationRequest_List_SET_TYPE( cur_ptr, cur_bitoff, 1034 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.ExchangeBuffer.ActualLen + 2);
		BM_TLSOperationRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.ExchangeBuffer.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.ExchangeBuffer.ActualLen; i0++ )
		{
			BM_TLSOperationRequest_List_CURRENT_ExchangeBuffer_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ExchangeBuffer.BufferArr[i0].value );
		}
		BM_TLSOperationRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.AppOutputBuffer.Type == 1035 )
	{
		BM_TLSOperationRequest_List_SET_TYPE( cur_ptr, cur_bitoff, 1035 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.AppOutputBuffer.ActualLen + 2);
		BM_TLSOperationRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.AppOutputBuffer.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.AppOutputBuffer.ActualLen; i0++ )
		{
			BM_TLSOperationRequest_List_CURRENT_AppOutputBuffer_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.AppOutputBuffer.BufferArr[i0].value );
		}
		BM_TLSOperationRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_TLSOperationRequest_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_TLS_OPERATION_RESULT );
	BM_TLSOperationRequest_Header_Version_SET( base_ptr, msg.header.Version );
	BM_TLSOperationRequest_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_TLSOperationRequest_Header_Status_SET( base_ptr, msg.header.Status );
	BM_TLSOperationRequest_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_TLSOperationRequest(UINT8* pBuf, TLSOperationRequest_type* msg)
{
	return L4BM_Set_TLSOperationRequest(pBuf, *msg);
}
UINT L4BM_GetBufferSize_TLSOperationRequest(TLSOperationRequest_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.Common.Type == 1033 )
	{
		length += 20;
		length += 4;
	}
	if( msg.ExchangeBuffer.Type == 1034 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.ExchangeBuffer.ActualLen + 2);
		length += 4;
	}
	if( msg.AppOutputBuffer.Type == 1035 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.AppOutputBuffer.ActualLen + 2);
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_TLSOperationRequest(TLSOperationRequest_type* msg)
{
	return L4BM_GetBufferSize_TLSOperationRequest(*msg);
}
UINT L4BM_GetMaxBufferSize_TLSOperationRequest( void )
{
	UINT32 length = HEADER_SIZE;

	length += 20;
	length += 4;
	length += L4BM_RoundUp4Bytes((UINT32)3000 + 2);
	length += 4;
	length += L4BM_RoundUp4Bytes((UINT32)3000 + 2);
	length += 4;

	return length;
}
void L4BM_Init_TLSOperationRequest(TLSOperationRequest_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->Common.Type = INVALID_OPCODE;
	pMsg->ExchangeBuffer.Type = INVALID_OPCODE;
	pMsg->AppOutputBuffer.Type = INVALID_OPCODE;

}
L4bufman_Funcs TLSOperationRequest_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_TLSOperationRequest,
	(pf_SetL4Command)L4BM_generic_Set_TLSOperationRequest,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_TLSOperationRequest,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_TLSOperationRequest,
	(pf_InitL4Command)L4BM_Init_TLSOperationRequest
};



//
// SetScanParameters
//
L4BUFMAN_Status_t L4BM_Get_SetScanParameters(SetScanParameters_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SetScanParameters(pMsg);
	BM_SetScanParameters_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetScanParameters_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetScanParameters_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetScanParameters_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{
		UINT32 ChannelInfoArray_index = 0;

		BM_SetScanParameters_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetScanParameters_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetScanParameters_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 181 )
			{
				if ( ChannelInfoArray_index < 32)
				{
					pMsg->ChannelInfoArray[ChannelInfoArray_index].Type = (UINT16)type;
					BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Frequency );
					BM_SetScanParameters_List_CURRENT_ChannelInfoArray_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].ChannelId );
					BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Bandwidth );
					BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Fft_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Fft );
					for( i0 = 0; i0 < 15; i0++ )
					{
						BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Preambles[i0].value );
					}
					BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Reserved );
				}
				ChannelInfoArray_index++;
			}
			if( type == 183 )
			{
				pMsg->ScanPolicy.Type = (UINT16)type;
				BM_SetScanParameters_List_CURRENT_ScanPolicy_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanPolicy.value );
			}

			BM_SetScanParameters_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetScanParameters(UINT8* pBuf, SetScanParameters_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, j = 0, i0 = 0;


	BM_SetScanParameters_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	for( j = 0; j < 32; j++ )
	{
		if( msg.ChannelInfoArray[j].Type == 181 )
		{
			BM_SetScanParameters_List_SET_TYPE( cur_ptr, cur_bitoff, 181 );
			length = 24;
			BM_SetScanParameters_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Frequency );
			BM_SetScanParameters_List_CURRENT_ChannelInfoArray_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].ChannelId );
			BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Bandwidth );
			BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Fft_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Fft );
			for( i0 = 0; i0 < 15; i0++ )
			{
				BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Preambles[i0].value );
			}
			BM_SetScanParameters_List_CURRENT_ChannelInfoArray_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Reserved );
			BM_SetScanParameters_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}
	if( msg.ScanPolicy.Type == 183 )
	{
		BM_SetScanParameters_List_SET_TYPE( cur_ptr, cur_bitoff, 183 );
		length = 4;
		BM_SetScanParameters_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetScanParameters_List_CURRENT_ScanPolicy_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanPolicy.value );
		BM_SetScanParameters_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetScanParameters_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_SCAN_PARAM );
	BM_SetScanParameters_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetScanParameters_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetScanParameters_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetScanParameters_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetScanParameters(UINT8* pBuf, SetScanParameters_type* msg)
{
	return L4BM_Set_SetScanParameters(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetScanParameters(SetScanParameters_type msg)
{
	UINT32 length = HEADER_SIZE, j = 0;

	for( j = 0; j < 32; j++ )
	{
		if( msg.ChannelInfoArray[j].Type == 181 )
		{
			length += 24;
			length += 4;
		}
	}
	if( msg.ScanPolicy.Type == 183 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetScanParameters(SetScanParameters_type* msg)
{
	return L4BM_GetBufferSize_SetScanParameters(*msg);
}
UINT L4BM_GetMaxBufferSize_SetScanParameters( void )
{
	UINT32 length = HEADER_SIZE, j = 0;

	for( j = 0; j < 32; j++ )
	{
		length += 24;
		length += 4;
	}
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_SetScanParameters(SetScanParameters_type* pMsg)
{
	UINT32 j = 0;

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	for( j = 0; j < 32; j++ )
	{
		pMsg->ChannelInfoArray[j].Type = INVALID_OPCODE;
	}
	pMsg->ScanPolicy.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetScanParameters_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetScanParameters,
	(pf_SetL4Command)L4BM_generic_Set_SetScanParameters,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetScanParameters,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetScanParameters,
	(pf_InitL4Command)L4BM_Init_SetScanParameters
};



//
// Connect
//
L4BUFMAN_Status_t L4BM_Get_Connect(Connect_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_Connect(pMsg);
	BM_Connect_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_Connect_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_Connect_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_Connect_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_Connect_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_Connect_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_Connect_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 190 )
			{
				pMsg->BSCritieria.Type = (UINT16)type;
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->BSCritieria.BSID_Criterion[i0].value );
				}
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_Mask_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->BSCritieria.BSID_Criterion_Mask[i0].value );
				}
			}
			if( type == 182 )
			{
				pMsg->THCriteria.Type = (UINT16)type;
				BM_Connect_List_CURRENT_THCriteria_RssiTH_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->THCriteria.RssiTH );
				BM_Connect_List_CURRENT_THCriteria_CinrTH_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->THCriteria.CinrTH );
			}
			if( type == 143 )
			{
				pMsg->ConnectionMode.Type = (UINT16)type;
				BM_Connect_List_CURRENT_ConnectionMode_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectionMode.value );
			}
			if( type == 192 )
			{
				pMsg->ConnectFlags.Type = (UINT16)type;
				BM_Connect_List_CURRENT_ConnectFlags_VisitedNspId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectFlags.VisitedNspId );
				BM_Connect_List_CURRENT_ConnectFlags_RequestRealm_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectFlags.RequestRealm );
				BM_Connect_List_CURRENT_ConnectFlags_SIQ_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectFlags.SIQ );
				BM_Connect_List_CURRENT_ConnectFlags_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectFlags.Reserved1 );
				BM_Connect_List_CURRENT_ConnectFlags_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectFlags.Reserved2 );
			}
			if( type == 164 )
			{
				pMsg->CoexPriority.Type = (UINT16)type;
				BM_Connect_List_CURRENT_CoexPriority_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->CoexPriority.value );
			}

			BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_Connect(UINT8* pBuf, Connect_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_Connect_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.BSCritieria.Type == 190 )
	{
		BM_Connect_List_SET_TYPE( cur_ptr, cur_bitoff, 190 );
		length = 12;
		BM_Connect_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.BSCritieria.BSID_Criterion[i0].value );
		}
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_Connect_List_CURRENT_BSCritieria_BSID_Criterion_Mask_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.BSCritieria.BSID_Criterion_Mask[i0].value );
		}
		BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.THCriteria.Type == 182 )
	{
		BM_Connect_List_SET_TYPE( cur_ptr, cur_bitoff, 182 );
		length = 8;
		BM_Connect_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_Connect_List_CURRENT_THCriteria_RssiTH_SET( base_ptr, cur_ptr, cur_bitoff, msg.THCriteria.RssiTH );
		BM_Connect_List_CURRENT_THCriteria_CinrTH_SET( base_ptr, cur_ptr, cur_bitoff, msg.THCriteria.CinrTH );
		BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ConnectionMode.Type == 143 )
	{
		BM_Connect_List_SET_TYPE( cur_ptr, cur_bitoff, 143 );
		length = 4;
		BM_Connect_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_Connect_List_CURRENT_ConnectionMode_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectionMode.value );
		BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ConnectFlags.Type == 192 )
	{
		BM_Connect_List_SET_TYPE( cur_ptr, cur_bitoff, 192 );
		length = 8;
		BM_Connect_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_Connect_List_CURRENT_ConnectFlags_VisitedNspId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectFlags.VisitedNspId );
		BM_Connect_List_CURRENT_ConnectFlags_RequestRealm_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectFlags.RequestRealm );
		BM_Connect_List_CURRENT_ConnectFlags_SIQ_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectFlags.SIQ );
		BM_Connect_List_CURRENT_ConnectFlags_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectFlags.Reserved1 );
		BM_Connect_List_CURRENT_ConnectFlags_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectFlags.Reserved2 );
		BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.CoexPriority.Type == 164 )
	{
		BM_Connect_List_SET_TYPE( cur_ptr, cur_bitoff, 164 );
		length = 4;
		BM_Connect_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_Connect_List_CURRENT_CoexPriority_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.CoexPriority.value );
		BM_Connect_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_Connect_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_CONNECT );
	BM_Connect_Header_Version_SET( base_ptr, msg.header.Version );
	BM_Connect_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_Connect_Header_Status_SET( base_ptr, msg.header.Status );
	BM_Connect_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_Connect(UINT8* pBuf, Connect_type* msg)
{
	return L4BM_Set_Connect(pBuf, *msg);
}
UINT L4BM_GetBufferSize_Connect(Connect_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.BSCritieria.Type == 190 )
	{
		length += 12;
		length += 4;
	}
	if( msg.THCriteria.Type == 182 )
	{
		length += 8;
		length += 4;
	}
	if( msg.ConnectionMode.Type == 143 )
	{
		length += 4;
		length += 4;
	}
	if( msg.ConnectFlags.Type == 192 )
	{
		length += 8;
		length += 4;
	}
	if( msg.CoexPriority.Type == 164 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_Connect(Connect_type* msg)
{
	return L4BM_GetBufferSize_Connect(*msg);
}
UINT L4BM_GetMaxBufferSize_Connect( void )
{
	UINT32 length = HEADER_SIZE;

	length += 12;
	length += 4;
	length += 8;
	length += 4;
	length += 4;
	length += 4;
	length += 8;
	length += 4;
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_Connect(Connect_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->BSCritieria.Type = INVALID_OPCODE;
	pMsg->THCriteria.Type = INVALID_OPCODE;
	pMsg->ConnectionMode.Type = INVALID_OPCODE;
	pMsg->ConnectFlags.Type = INVALID_OPCODE;
	pMsg->CoexPriority.Type = INVALID_OPCODE;

}
L4bufman_Funcs Connect_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_Connect,
	(pf_SetL4Command)L4BM_generic_Set_Connect,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_Connect,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_Connect,
	(pf_InitL4Command)L4BM_Init_Connect
};



//
// MOC_Request
//
L4BUFMAN_Status_t L4BM_Get_MOC_Request(MOC_Request_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_MOC_Request_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_MOC_Request_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_MOC_Request_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_MOC_Request(UINT8* pBuf, MOC_Request_type msg)
{
	PVOID base_ptr = pBuf;

	MOC_Request_type tmp = msg;
	tmp = tmp;

	BM_MOC_Request_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_MOC_REQUEST );
	BM_MOC_Request_Header_Version_SET( base_ptr, msg.header.Version );
	BM_MOC_Request_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_MOC_Request_Header_Status_SET( base_ptr, msg.header.Status );
	BM_MOC_Request_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_MOC_Request(UINT8* pBuf, MOC_Request_type* msg)
{
	return L4BM_Set_MOC_Request(pBuf, *msg);
}
UINT L4BM_GetBufferSize_MOC_Request(MOC_Request_type msg)
{

	MOC_Request_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_MOC_Request(MOC_Request_type* msg)
{
	return L4BM_GetBufferSize_MOC_Request(*msg);
}
UINT L4BM_GetMaxBufferSize_MOC_Request( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_MOC_Request(MOC_Request_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs MOC_Request_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_MOC_Request,
	(pf_SetL4Command)L4BM_generic_Set_MOC_Request,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_MOC_Request,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_MOC_Request,
	(pf_InitL4Command)L4BM_Init_MOC_Request
};



//
// RfControl
//
L4BUFMAN_Status_t L4BM_Get_RfControl(RfControl_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_RfControl(pMsg);
	BM_RfControl_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_RfControl_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_RfControl_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_RfControl_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_RfControl_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_RfControl_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_RfControl_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 162 )
			{
				pMsg->RfOperation.Type = (UINT16)type;
				BM_RfControl_List_CURRENT_RfOperation_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RfOperation.value );
			}

			BM_RfControl_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_RfControl(UINT8* pBuf, RfControl_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_RfControl_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.RfOperation.Type == 162 )
	{
		BM_RfControl_List_SET_TYPE( cur_ptr, cur_bitoff, 162 );
		length = 4;
		BM_RfControl_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_RfControl_List_CURRENT_RfOperation_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.RfOperation.value );
		BM_RfControl_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_RfControl_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_RF_CONTROL );
	BM_RfControl_Header_Version_SET( base_ptr, msg.header.Version );
	BM_RfControl_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_RfControl_Header_Status_SET( base_ptr, msg.header.Status );
	BM_RfControl_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_RfControl(UINT8* pBuf, RfControl_type* msg)
{
	return L4BM_Set_RfControl(pBuf, *msg);
}
UINT L4BM_GetBufferSize_RfControl(RfControl_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.RfOperation.Type == 162 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_RfControl(RfControl_type* msg)
{
	return L4BM_GetBufferSize_RfControl(*msg);
}
UINT L4BM_GetMaxBufferSize_RfControl( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_RfControl(RfControl_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->RfOperation.Type = INVALID_OPCODE;

}
L4bufman_Funcs RfControl_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_RfControl,
	(pf_SetL4Command)L4BM_generic_Set_RfControl,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_RfControl,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_RfControl,
	(pf_InitL4Command)L4BM_Init_RfControl
};



//
// ReportEapRestart
//
L4BUFMAN_Status_t L4BM_Get_ReportEapRestart(ReportEapRestart_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_ReportEapRestart_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportEapRestart_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportEapRestart_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportEapRestart(UINT8* pBuf, ReportEapRestart_type msg)
{
	PVOID base_ptr = pBuf;

	ReportEapRestart_type tmp = msg;
	tmp = tmp;

	BM_ReportEapRestart_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_EAP_RESTART );
	BM_ReportEapRestart_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportEapRestart_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportEapRestart_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportEapRestart_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportEapRestart(UINT8* pBuf, ReportEapRestart_type* msg)
{
	return L4BM_Set_ReportEapRestart(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportEapRestart(ReportEapRestart_type msg)
{

	ReportEapRestart_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_ReportEapRestart(ReportEapRestart_type* msg)
{
	return L4BM_GetBufferSize_ReportEapRestart(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportEapRestart( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_ReportEapRestart(ReportEapRestart_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs ReportEapRestart_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportEapRestart,
	(pf_SetL4Command)L4BM_generic_Set_ReportEapRestart,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportEapRestart,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportEapRestart,
	(pf_InitL4Command)L4BM_Init_ReportEapRestart
};



//
// ReportEapRequest
//
L4BUFMAN_Status_t L4BM_Get_ReportEapRequest(ReportEapRequest_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportEapRequest(pMsg);
	BM_ReportEapRequest_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportEapRequest_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportEapRequest_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportEapRequest_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ReportEapRequest_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportEapRequest_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportEapRequest_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1026 )
			{
				pMsg->EapRequestMessage.Type = (UINT16)type;
				BM_ReportEapRequest_List_CURRENT_EapRequestMessage_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->EapRequestMessage.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->EapRequestMessage.ActualLen; i0++ )
				{
					BM_ReportEapRequest_List_CURRENT_EapRequestMessage_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->EapRequestMessage.BufferArr[i0].value );
				}
			}

			BM_ReportEapRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportEapRequest(UINT8* pBuf, ReportEapRequest_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_ReportEapRequest_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.EapRequestMessage.Type == 1026 )
	{
		BM_ReportEapRequest_List_SET_TYPE( cur_ptr, cur_bitoff, 1026 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.EapRequestMessage.ActualLen + 2);
		BM_ReportEapRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportEapRequest_List_CURRENT_EapRequestMessage_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.EapRequestMessage.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.EapRequestMessage.ActualLen; i0++ )
		{
			BM_ReportEapRequest_List_CURRENT_EapRequestMessage_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.EapRequestMessage.BufferArr[i0].value );
		}
		BM_ReportEapRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ReportEapRequest_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_EAP_REQUEST );
	BM_ReportEapRequest_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportEapRequest_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportEapRequest_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportEapRequest_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportEapRequest(UINT8* pBuf, ReportEapRequest_type* msg)
{
	return L4BM_Set_ReportEapRequest(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportEapRequest(ReportEapRequest_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.EapRequestMessage.Type == 1026 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.EapRequestMessage.ActualLen + 2);
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportEapRequest(ReportEapRequest_type* msg)
{
	return L4BM_GetBufferSize_ReportEapRequest(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportEapRequest( void )
{
	UINT32 length = HEADER_SIZE;

	length += L4BM_RoundUp4Bytes((UINT32)1400 + 2);
	length += 4;

	return length;
}
void L4BM_Init_ReportEapRequest(ReportEapRequest_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->EapRequestMessage.Type = INVALID_OPCODE;

}
L4bufman_Funcs ReportEapRequest_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportEapRequest,
	(pf_SetL4Command)L4BM_generic_Set_ReportEapRequest,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportEapRequest,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportEapRequest,
	(pf_InitL4Command)L4BM_Init_ReportEapRequest
};



//
// ReportRecentNbrHood
//
L4BUFMAN_Status_t L4BM_Get_ReportRecentNbrHood(ReportRecentNbrHood_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportRecentNbrHood(pMsg);
	BM_ReportRecentNbrHood_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportRecentNbrHood_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportRecentNbrHood_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportRecentNbrHood_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{
		UINT32 ChannelInfoArray_index = 0;

		BM_ReportRecentNbrHood_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportRecentNbrHood_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportRecentNbrHood_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 181 )
			{
				if ( ChannelInfoArray_index < 33)
				{
					pMsg->ChannelInfoArray[ChannelInfoArray_index].Type = (UINT16)type;
					BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Frequency );
					BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].ChannelId );
					BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Bandwidth );
					BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Fft_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Fft );
					for( i0 = 0; i0 < 15; i0++ )
					{
						BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Preambles[i0].value );
					}
					BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfoArray[ChannelInfoArray_index].Reserved );
				}
				ChannelInfoArray_index++;
			}

			BM_ReportRecentNbrHood_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportRecentNbrHood(UINT8* pBuf, ReportRecentNbrHood_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, j = 0, i0 = 0;


	BM_ReportRecentNbrHood_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	for( j = 0; j < 33; j++ )
	{
		if( msg.ChannelInfoArray[j].Type == 181 )
		{
			BM_ReportRecentNbrHood_List_SET_TYPE( cur_ptr, cur_bitoff, 181 );
			length = 24;
			BM_ReportRecentNbrHood_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Frequency );
			BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].ChannelId );
			BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Bandwidth );
			BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Fft_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Fft );
			for( i0 = 0; i0 < 15; i0++ )
			{
				BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Preambles[i0].value );
			}
			BM_ReportRecentNbrHood_List_CURRENT_ChannelInfoArray_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfoArray[j].Reserved );
			BM_ReportRecentNbrHood_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}

	BM_ReportRecentNbrHood_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_RECENT_BS );
	BM_ReportRecentNbrHood_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportRecentNbrHood_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportRecentNbrHood_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportRecentNbrHood_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportRecentNbrHood(UINT8* pBuf, ReportRecentNbrHood_type* msg)
{
	return L4BM_Set_ReportRecentNbrHood(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportRecentNbrHood(ReportRecentNbrHood_type msg)
{
	UINT32 length = HEADER_SIZE, j = 0;

	for( j = 0; j < 33; j++ )
	{
		if( msg.ChannelInfoArray[j].Type == 181 )
		{
			length += 24;
			length += 4;
		}
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportRecentNbrHood(ReportRecentNbrHood_type* msg)
{
	return L4BM_GetBufferSize_ReportRecentNbrHood(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportRecentNbrHood( void )
{
	UINT32 length = HEADER_SIZE, j = 0;

	for( j = 0; j < 33; j++ )
	{
		length += 24;
		length += 4;
	}

	return length;
}
void L4BM_Init_ReportRecentNbrHood(ReportRecentNbrHood_type* pMsg)
{
	UINT32 j = 0;

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	for( j = 0; j < 33; j++ )
	{
		pMsg->ChannelInfoArray[j].Type = INVALID_OPCODE;
	}

}
L4bufman_Funcs ReportRecentNbrHood_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportRecentNbrHood,
	(pf_SetL4Command)L4BM_generic_Set_ReportRecentNbrHood,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportRecentNbrHood,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportRecentNbrHood,
	(pf_InitL4Command)L4BM_Init_ReportRecentNbrHood
};



//
// GetLinkStatus
//
L4BUFMAN_Status_t L4BM_Get_GetLinkStatus(GetLinkStatus_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_GetLinkStatus(pMsg);
	BM_GetLinkStatus_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetLinkStatus_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetLinkStatus_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetLinkStatus_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetLinkStatus_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetLinkStatus_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetLinkStatus_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 160 )
			{
				pMsg->LinkStatus.Type = (UINT16)type;
				BM_GetLinkStatus_List_CURRENT_LinkStatus_UpLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.UpLinkSpeed );
				BM_GetLinkStatus_List_CURRENT_LinkStatus_DownLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.DownLinkSpeed );
				BM_GetLinkStatus_List_CURRENT_LinkStatus_CenterFrequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.CenterFrequency );
				BM_GetLinkStatus_List_CURRENT_LinkStatus_TxPower_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.TxPower );
				BM_GetLinkStatus_List_CURRENT_LinkStatus_RxRssi_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.RxRssi );
				BM_GetLinkStatus_List_CURRENT_LinkStatus_RxCinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.RxCinr );
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_GetLinkStatus_List_CURRENT_LinkStatus_BSID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LinkStatus.BSID[i0].value );
				}
				BM_GetLinkStatus_List_CURRENT_LinkStatus_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.LinkQuality );
				BM_GetLinkStatus_List_CURRENT_LinkStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.Reserved );
			}
			if( type == 181 )
			{
				pMsg->ChannelInfo.Type = (UINT16)type;
				BM_GetLinkStatus_List_CURRENT_ChannelInfo_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Frequency );
				BM_GetLinkStatus_List_CURRENT_ChannelInfo_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.ChannelId );
				BM_GetLinkStatus_List_CURRENT_ChannelInfo_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Bandwidth );
				BM_GetLinkStatus_List_CURRENT_ChannelInfo_Fft_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Fft );
				for( i0 = 0; i0 < 15; i0++ )
				{
					BM_GetLinkStatus_List_CURRENT_ChannelInfo_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Preambles[i0].value );
				}
				BM_GetLinkStatus_List_CURRENT_ChannelInfo_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Reserved );
			}

			BM_GetLinkStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetLinkStatus(UINT8* pBuf, GetLinkStatus_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_GetLinkStatus_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.LinkStatus.Type == 160 )
	{
		BM_GetLinkStatus_List_SET_TYPE( cur_ptr, cur_bitoff, 160 );
		length = 24;
		BM_GetLinkStatus_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_UpLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.UpLinkSpeed );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_DownLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.DownLinkSpeed );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_CenterFrequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.CenterFrequency );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_TxPower_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.TxPower );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_RxRssi_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.RxRssi );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_RxCinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.RxCinr );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_GetLinkStatus_List_CURRENT_LinkStatus_BSID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LinkStatus.BSID[i0].value );
		}
		BM_GetLinkStatus_List_CURRENT_LinkStatus_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.LinkQuality );
		BM_GetLinkStatus_List_CURRENT_LinkStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.Reserved );
		BM_GetLinkStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ChannelInfo.Type == 181 )
	{
		BM_GetLinkStatus_List_SET_TYPE( cur_ptr, cur_bitoff, 181 );
		length = 24;
		BM_GetLinkStatus_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetLinkStatus_List_CURRENT_ChannelInfo_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Frequency );
		BM_GetLinkStatus_List_CURRENT_ChannelInfo_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.ChannelId );
		BM_GetLinkStatus_List_CURRENT_ChannelInfo_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Bandwidth );
		BM_GetLinkStatus_List_CURRENT_ChannelInfo_Fft_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Fft );
		for( i0 = 0; i0 < 15; i0++ )
		{
			BM_GetLinkStatus_List_CURRENT_ChannelInfo_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ChannelInfo.Preambles[i0].value );
		}
		BM_GetLinkStatus_List_CURRENT_ChannelInfo_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Reserved );
		BM_GetLinkStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetLinkStatus_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_LINK_STATUS );
	BM_GetLinkStatus_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetLinkStatus_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetLinkStatus_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetLinkStatus_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetLinkStatus(UINT8* pBuf, GetLinkStatus_type* msg)
{
	return L4BM_Set_GetLinkStatus(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetLinkStatus(GetLinkStatus_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.LinkStatus.Type == 160 )
	{
		length += 24;
		length += 4;
	}
	if( msg.ChannelInfo.Type == 181 )
	{
		length += 24;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetLinkStatus(GetLinkStatus_type* msg)
{
	return L4BM_GetBufferSize_GetLinkStatus(*msg);
}
UINT L4BM_GetMaxBufferSize_GetLinkStatus( void )
{
	UINT32 length = HEADER_SIZE;

	length += 24;
	length += 4;
	length += 24;
	length += 4;

	return length;
}
void L4BM_Init_GetLinkStatus(GetLinkStatus_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->LinkStatus.Type = INVALID_OPCODE;
	pMsg->ChannelInfo.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetLinkStatus_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetLinkStatus,
	(pf_SetL4Command)L4BM_generic_Set_GetLinkStatus,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetLinkStatus,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetLinkStatus,
	(pf_InitL4Command)L4BM_Init_GetLinkStatus
};



//
// SetD2HChannelMask
//
L4BUFMAN_Status_t L4BM_Get_SetD2HChannelMask(SetD2HChannelMask_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_SetD2HChannelMask(pMsg);
	BM_SetD2HChannelMask_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetD2HChannelMask_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetD2HChannelMask_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetD2HChannelMask_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SetD2HChannelMask_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetD2HChannelMask_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetD2HChannelMask_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 134 )
			{
				pMsg->D2HChannelMask.Type = (UINT16)type;
				BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HChannelMask.DataChannelSwitch );
				BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HChannelMask.DiagnosticsChannelSwitch );
				BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HChannelMask.Reserved );
			}

			BM_SetD2HChannelMask_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetD2HChannelMask(UINT8* pBuf, SetD2HChannelMask_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_SetD2HChannelMask_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.D2HChannelMask.Type == 134 )
	{
		BM_SetD2HChannelMask_List_SET_TYPE( cur_ptr, cur_bitoff, 134 );
		length = 4;
		BM_SetD2HChannelMask_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HChannelMask.DataChannelSwitch );
		BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HChannelMask.DiagnosticsChannelSwitch );
		BM_SetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HChannelMask.Reserved );
		BM_SetD2HChannelMask_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetD2HChannelMask_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_D2H_CHANNEL_MASK );
	BM_SetD2HChannelMask_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetD2HChannelMask_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetD2HChannelMask_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetD2HChannelMask_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetD2HChannelMask(UINT8* pBuf, SetD2HChannelMask_type* msg)
{
	return L4BM_Set_SetD2HChannelMask(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetD2HChannelMask(SetD2HChannelMask_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.D2HChannelMask.Type == 134 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetD2HChannelMask(SetD2HChannelMask_type* msg)
{
	return L4BM_GetBufferSize_SetD2HChannelMask(*msg);
}
UINT L4BM_GetMaxBufferSize_SetD2HChannelMask( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_SetD2HChannelMask(SetD2HChannelMask_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->D2HChannelMask.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetD2HChannelMask_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetD2HChannelMask,
	(pf_SetL4Command)L4BM_generic_Set_SetD2HChannelMask,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetD2HChannelMask,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetD2HChannelMask,
	(pf_InitL4Command)L4BM_Init_SetD2HChannelMask
};



//
// EnterPowerSaveCommand
//
L4BUFMAN_Status_t L4BM_Get_EnterPowerSaveCommand(EnterPowerSaveCommand_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_EnterPowerSaveCommand(pMsg);
	BM_EnterPowerSaveCommand_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_EnterPowerSaveCommand_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_EnterPowerSaveCommand_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_EnterPowerSaveCommand_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_EnterPowerSaveCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_EnterPowerSaveCommand_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_EnterPowerSaveCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 144 )
			{
				pMsg->WakeupMode.Type = (UINT16)type;
				BM_EnterPowerSaveCommand_List_CURRENT_WakeupMode_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->WakeupMode.value );
			}

			BM_EnterPowerSaveCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_EnterPowerSaveCommand(UINT8* pBuf, EnterPowerSaveCommand_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_EnterPowerSaveCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.WakeupMode.Type == 144 )
	{
		BM_EnterPowerSaveCommand_List_SET_TYPE( cur_ptr, cur_bitoff, 144 );
		length = 4;
		BM_EnterPowerSaveCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_EnterPowerSaveCommand_List_CURRENT_WakeupMode_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.WakeupMode.value );
		BM_EnterPowerSaveCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_EnterPowerSaveCommand_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_ENTER_POWER_SAVE );
	BM_EnterPowerSaveCommand_Header_Version_SET( base_ptr, msg.header.Version );
	BM_EnterPowerSaveCommand_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_EnterPowerSaveCommand_Header_Status_SET( base_ptr, msg.header.Status );
	BM_EnterPowerSaveCommand_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_EnterPowerSaveCommand(UINT8* pBuf, EnterPowerSaveCommand_type* msg)
{
	return L4BM_Set_EnterPowerSaveCommand(pBuf, *msg);
}
UINT L4BM_GetBufferSize_EnterPowerSaveCommand(EnterPowerSaveCommand_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.WakeupMode.Type == 144 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_EnterPowerSaveCommand(EnterPowerSaveCommand_type* msg)
{
	return L4BM_GetBufferSize_EnterPowerSaveCommand(*msg);
}
UINT L4BM_GetMaxBufferSize_EnterPowerSaveCommand( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_EnterPowerSaveCommand(EnterPowerSaveCommand_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->WakeupMode.Type = INVALID_OPCODE;

}
L4bufman_Funcs EnterPowerSaveCommand_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_EnterPowerSaveCommand,
	(pf_SetL4Command)L4BM_generic_Set_EnterPowerSaveCommand,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_EnterPowerSaveCommand,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_EnterPowerSaveCommand,
	(pf_InitL4Command)L4BM_Init_EnterPowerSaveCommand
};



//
// SPLockStatusInfo
//
L4BUFMAN_Status_t L4BM_Get_SPLockStatusInfo(SPLockStatusInfo_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SPLockStatusInfo(pMsg);
	BM_SPLockStatusInfo_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SPLockStatusInfo_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SPLockStatusInfo_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SPLockStatusInfo_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SPLockStatusInfo_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SPLockStatusInfo_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SPLockStatusInfo_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1067 )
			{
				pMsg->SPLockStatus.Type = (UINT16)type;
				BM_SPLockStatusInfo_List_CURRENT_SPLockStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SPLockStatus.value );
			}
			if( type == 1068 )
			{
				pMsg->LockedToNSPNameInfo.Type = (UINT16)type;
				BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LockedToNSPNameInfo.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->LockedToNSPNameInfo.ActualLen; i0++ )
				{
					BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LockedToNSPNameInfo.BufferArr[i0].value );
				}
			}

			BM_SPLockStatusInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SPLockStatusInfo(UINT8* pBuf, SPLockStatusInfo_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SPLockStatusInfo_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.SPLockStatus.Type == 1067 )
	{
		BM_SPLockStatusInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 1067 );
		length = 4;
		BM_SPLockStatusInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SPLockStatusInfo_List_CURRENT_SPLockStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.SPLockStatus.value );
		BM_SPLockStatusInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LockedToNSPNameInfo.Type == 1068 )
	{
		BM_SPLockStatusInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 1068 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.LockedToNSPNameInfo.ActualLen + 2);
		BM_SPLockStatusInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.LockedToNSPNameInfo.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.LockedToNSPNameInfo.ActualLen; i0++ )
		{
			BM_SPLockStatusInfo_List_CURRENT_LockedToNSPNameInfo_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LockedToNSPNameInfo.BufferArr[i0].value );
		}
		BM_SPLockStatusInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SPLockStatusInfo_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_SPLOCK_STATUS );
	BM_SPLockStatusInfo_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SPLockStatusInfo_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SPLockStatusInfo_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SPLockStatusInfo_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SPLockStatusInfo(UINT8* pBuf, SPLockStatusInfo_type* msg)
{
	return L4BM_Set_SPLockStatusInfo(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SPLockStatusInfo(SPLockStatusInfo_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.SPLockStatus.Type == 1067 )
	{
		length += 4;
		length += 4;
	}
	if( msg.LockedToNSPNameInfo.Type == 1068 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.LockedToNSPNameInfo.ActualLen + 2);
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SPLockStatusInfo(SPLockStatusInfo_type* msg)
{
	return L4BM_GetBufferSize_SPLockStatusInfo(*msg);
}
UINT L4BM_GetMaxBufferSize_SPLockStatusInfo( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += L4BM_RoundUp4Bytes((UINT32)256 + 2);
	length += 4;

	return length;
}
void L4BM_Init_SPLockStatusInfo(SPLockStatusInfo_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->SPLockStatus.Type = INVALID_OPCODE;
	pMsg->LockedToNSPNameInfo.Type = INVALID_OPCODE;

}
L4bufman_Funcs SPLockStatusInfo_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SPLockStatusInfo,
	(pf_SetL4Command)L4BM_generic_Set_SPLockStatusInfo,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SPLockStatusInfo,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SPLockStatusInfo,
	(pf_InitL4Command)L4BM_Init_SPLockStatusInfo
};



//
// GetMediaStatus
//
L4BUFMAN_Status_t L4BM_Get_GetMediaStatus(GetMediaStatus_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_GetMediaStatus(pMsg);
	BM_GetMediaStatus_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetMediaStatus_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetMediaStatus_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetMediaStatus_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetMediaStatus_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetMediaStatus_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetMediaStatus_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 161 )
			{
				pMsg->MediaStatus.Type = (UINT16)type;
				BM_GetMediaStatus_List_CURRENT_MediaStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->MediaStatus.value );
			}

			BM_GetMediaStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetMediaStatus(UINT8* pBuf, GetMediaStatus_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_GetMediaStatus_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.MediaStatus.Type == 161 )
	{
		BM_GetMediaStatus_List_SET_TYPE( cur_ptr, cur_bitoff, 161 );
		length = 4;
		BM_GetMediaStatus_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetMediaStatus_List_CURRENT_MediaStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.MediaStatus.value );
		BM_GetMediaStatus_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetMediaStatus_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_MEDIA_STATUS );
	BM_GetMediaStatus_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetMediaStatus_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetMediaStatus_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetMediaStatus_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetMediaStatus(UINT8* pBuf, GetMediaStatus_type* msg)
{
	return L4BM_Set_GetMediaStatus(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetMediaStatus(GetMediaStatus_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.MediaStatus.Type == 161 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetMediaStatus(GetMediaStatus_type* msg)
{
	return L4BM_GetBufferSize_GetMediaStatus(*msg);
}
UINT L4BM_GetMaxBufferSize_GetMediaStatus( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_GetMediaStatus(GetMediaStatus_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->MediaStatus.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetMediaStatus_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetMediaStatus,
	(pf_SetL4Command)L4BM_generic_Set_GetMediaStatus,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetMediaStatus,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetMediaStatus,
	(pf_InitL4Command)L4BM_Init_GetMediaStatus
};



//
// GetState
//
L4BUFMAN_Status_t L4BM_Get_GetState(GetState_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_GetState(pMsg);
	BM_GetState_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetState_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetState_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetState_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetState_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetState_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetState_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 141 )
			{
				pMsg->SystemState.Type = (UINT16)type;
				BM_GetState_List_CURRENT_SystemState_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SystemState.value );
			}
			if( type == 191 )
			{
				pMsg->ConnectProgress.Type = (UINT16)type;
				BM_GetState_List_CURRENT_ConnectProgress_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectProgress.value );
			}
			if( type == 163 )
			{
				pMsg->RFStatus.Type = (UINT16)type;
				BM_GetState_List_CURRENT_RFStatus_SwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RFStatus.SwRFSwitch );
				BM_GetState_List_CURRENT_RFStatus_HwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RFStatus.HwRFSwitch );
				BM_GetState_List_CURRENT_RFStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RFStatus.Reserved );
			}
			if( type == 150 )
			{
				pMsg->LastReason.Type = (UINT16)type;
				BM_GetState_List_CURRENT_LastReason_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LastReason.value );
			}

			BM_GetState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetState(UINT8* pBuf, GetState_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_GetState_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.SystemState.Type == 141 )
	{
		BM_GetState_List_SET_TYPE( cur_ptr, cur_bitoff, 141 );
		length = 4;
		BM_GetState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetState_List_CURRENT_SystemState_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.SystemState.value );
		BM_GetState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ConnectProgress.Type == 191 )
	{
		BM_GetState_List_SET_TYPE( cur_ptr, cur_bitoff, 191 );
		length = 4;
		BM_GetState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetState_List_CURRENT_ConnectProgress_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectProgress.value );
		BM_GetState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.RFStatus.Type == 163 )
	{
		BM_GetState_List_SET_TYPE( cur_ptr, cur_bitoff, 163 );
		length = 4;
		BM_GetState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetState_List_CURRENT_RFStatus_SwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.RFStatus.SwRFSwitch );
		BM_GetState_List_CURRENT_RFStatus_HwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.RFStatus.HwRFSwitch );
		BM_GetState_List_CURRENT_RFStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.RFStatus.Reserved );
		BM_GetState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LastReason.Type == 150 )
	{
		BM_GetState_List_SET_TYPE( cur_ptr, cur_bitoff, 150 );
		length = 4;
		BM_GetState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetState_List_CURRENT_LastReason_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.LastReason.value );
		BM_GetState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetState_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_STATE );
	BM_GetState_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetState_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetState_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetState_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetState(UINT8* pBuf, GetState_type* msg)
{
	return L4BM_Set_GetState(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetState(GetState_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.SystemState.Type == 141 )
	{
		length += 4;
		length += 4;
	}
	if( msg.ConnectProgress.Type == 191 )
	{
		length += 4;
		length += 4;
	}
	if( msg.RFStatus.Type == 163 )
	{
		length += 4;
		length += 4;
	}
	if( msg.LastReason.Type == 150 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetState(GetState_type* msg)
{
	return L4BM_GetBufferSize_GetState(*msg);
}
UINT L4BM_GetMaxBufferSize_GetState( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_GetState(GetState_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->SystemState.Type = INVALID_OPCODE;
	pMsg->ConnectProgress.Type = INVALID_OPCODE;
	pMsg->RFStatus.Type = INVALID_OPCODE;
	pMsg->LastReason.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetState_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetState,
	(pf_SetL4Command)L4BM_generic_Set_GetState,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetState,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetState,
	(pf_InitL4Command)L4BM_Init_GetState
};



//
// GetScanResults
//
L4BUFMAN_Status_t L4BM_Get_GetScanResults(GetScanResults_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_GetScanResults(pMsg);
	BM_GetScanResults_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetScanResults_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetScanResults_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetScanResults_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{
		UINT32 ScanResultList_Get_index = 0;

		BM_GetScanResults_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetScanResults_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetScanResults_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 187 )
			{
				pMsg->ScanStatus.Type = (UINT16)type;
				BM_GetScanResults_List_CURRENT_ScanStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanStatus.value );
			}
			if( type == 189 )
			{
				if ( ScanResultList_Get_index < 33)
				{
					pMsg->ScanResultList_Get[ScanResultList_Get_index].Type = (UINT16)type;
					BM_GetScanResults_List_CURRENT_ScanResultList_Get_Rssi_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].Rssi );
					BM_GetScanResults_List_CURRENT_ScanResultList_Get_Cinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].Cinr );
					for( i0 = 0; i0 < 6; i0++ )
					{
						BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsIdmask_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].BsIdmask[i0].value );
					}
					for( i0 = 0; i0 < 6; i0++ )
					{
						BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].BsId[i0].value );
					}
					BM_GetScanResults_List_CURRENT_ScanResultList_Get_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].ChannelId );
					BM_GetScanResults_List_CURRENT_ScanResultList_Get_PreambleId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].PreambleId );
					BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkGrade_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].LinkGrade );
					BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Get[ScanResultList_Get_index].LinkQuality );
				}
				ScanResultList_Get_index++;
			}

			BM_GetScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetScanResults(UINT8* pBuf, GetScanResults_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, j = 0, i0 = 0;


	BM_GetScanResults_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.ScanStatus.Type == 187 )
	{
		BM_GetScanResults_List_SET_TYPE( cur_ptr, cur_bitoff, 187 );
		length = 4;
		BM_GetScanResults_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetScanResults_List_CURRENT_ScanStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanStatus.value );
		BM_GetScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	for( j = 0; j < 33; j++ )
	{
		if( msg.ScanResultList_Get[j].Type == 189 )
		{
			BM_GetScanResults_List_SET_TYPE( cur_ptr, cur_bitoff, 189 );
			length = 20;
			BM_GetScanResults_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_GetScanResults_List_CURRENT_ScanResultList_Get_Rssi_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].Rssi );
			BM_GetScanResults_List_CURRENT_ScanResultList_Get_Cinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].Cinr );
			for( i0 = 0; i0 < 6; i0++ )
			{
				BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsIdmask_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].BsIdmask[i0].value );
			}
			for( i0 = 0; i0 < 6; i0++ )
			{
				BM_GetScanResults_List_CURRENT_ScanResultList_Get_BsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].BsId[i0].value );
			}
			BM_GetScanResults_List_CURRENT_ScanResultList_Get_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].ChannelId );
			BM_GetScanResults_List_CURRENT_ScanResultList_Get_PreambleId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].PreambleId );
			BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkGrade_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].LinkGrade );
			BM_GetScanResults_List_CURRENT_ScanResultList_Get_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Get[j].LinkQuality );
			BM_GetScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}

	BM_GetScanResults_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_SCAN_RESULT );
	BM_GetScanResults_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetScanResults_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetScanResults_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetScanResults_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetScanResults(UINT8* pBuf, GetScanResults_type* msg)
{
	return L4BM_Set_GetScanResults(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetScanResults(GetScanResults_type msg)
{
	UINT32 length = HEADER_SIZE, j = 0;

	if( msg.ScanStatus.Type == 187 )
	{
		length += 4;
		length += 4;
	}
	for( j = 0; j < 33; j++ )
	{
		if( msg.ScanResultList_Get[j].Type == 189 )
		{
			length += 20;
			length += 4;
		}
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetScanResults(GetScanResults_type* msg)
{
	return L4BM_GetBufferSize_GetScanResults(*msg);
}
UINT L4BM_GetMaxBufferSize_GetScanResults( void )
{
	UINT32 length = HEADER_SIZE, j = 0;

	length += 4;
	length += 4;
	for( j = 0; j < 33; j++ )
	{
		length += 20;
		length += 4;
	}

	return length;
}
void L4BM_Init_GetScanResults(GetScanResults_type* pMsg)
{
	UINT32 j = 0;

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->ScanStatus.Type = INVALID_OPCODE;
	for( j = 0; j < 33; j++ )
	{
		pMsg->ScanResultList_Get[j].Type = INVALID_OPCODE;
	}

}
L4bufman_Funcs GetScanResults_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetScanResults,
	(pf_SetL4Command)L4BM_generic_Set_GetScanResults,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetScanResults,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetScanResults,
	(pf_InitL4Command)L4BM_Init_GetScanResults
};



//
// ReportEMSKRelatedKeys
//
L4BUFMAN_Status_t L4BM_Get_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportEMSKRelatedKeys(pMsg);
	BM_ReportEMSKRelatedKeys_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportEMSKRelatedKeys_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportEMSKRelatedKeys_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportEMSKRelatedKeys_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ReportEMSKRelatedKeys_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportEMSKRelatedKeys_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportEMSKRelatedKeys_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1040 )
			{
				pMsg->BEK.Type = (UINT16)type;
				for( i0 = 0; i0 < 16; i0++ )
				{
					BM_ReportEMSKRelatedKeys_List_CURRENT_BEK_BEKKeyBufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->BEK.BEKKeyBufferArr[i0].value );
				}
			}

			BM_ReportEMSKRelatedKeys_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportEMSKRelatedKeys(UINT8* pBuf, ReportEMSKRelatedKeys_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_ReportEMSKRelatedKeys_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.BEK.Type == 1040 )
	{
		BM_ReportEMSKRelatedKeys_List_SET_TYPE( cur_ptr, cur_bitoff, 1040 );
		length = 16;
		BM_ReportEMSKRelatedKeys_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 16; i0++ )
		{
			BM_ReportEMSKRelatedKeys_List_CURRENT_BEK_BEKKeyBufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.BEK.BEKKeyBufferArr[i0].value );
		}
		BM_ReportEMSKRelatedKeys_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ReportEMSKRelatedKeys_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS );
	BM_ReportEMSKRelatedKeys_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportEMSKRelatedKeys_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportEMSKRelatedKeys_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportEMSKRelatedKeys_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportEMSKRelatedKeys(UINT8* pBuf, ReportEMSKRelatedKeys_type* msg)
{
	return L4BM_Set_ReportEMSKRelatedKeys(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.BEK.Type == 1040 )
	{
		length += 16;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type* msg)
{
	return L4BM_GetBufferSize_ReportEMSKRelatedKeys(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportEMSKRelatedKeys( void )
{
	UINT32 length = HEADER_SIZE;

	length += 16;
	length += 4;

	return length;
}
void L4BM_Init_ReportEMSKRelatedKeys(ReportEMSKRelatedKeys_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->BEK.Type = INVALID_OPCODE;

}
L4bufman_Funcs ReportEMSKRelatedKeys_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportEMSKRelatedKeys,
	(pf_SetL4Command)L4BM_generic_Set_ReportEMSKRelatedKeys,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportEMSKRelatedKeys,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportEMSKRelatedKeys,
	(pf_InitL4Command)L4BM_Init_ReportEMSKRelatedKeys
};



//
// ReportScanResults
//
L4BUFMAN_Status_t L4BM_Get_ReportScanResults(ReportScanResults_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportScanResults(pMsg);
	BM_ReportScanResults_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportScanResults_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportScanResults_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportScanResults_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{
		UINT32 ScanResultList_Report_index = 0;

		BM_ReportScanResults_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportScanResults_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportScanResults_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 187 )
			{
				pMsg->ScanStatus.Type = (UINT16)type;
				BM_ReportScanResults_List_CURRENT_ScanStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanStatus.value );
			}
			if( type == 189 )
			{
				if ( ScanResultList_Report_index < 33)
				{
					pMsg->ScanResultList_Report[ScanResultList_Report_index].Type = (UINT16)type;
					BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Rssi_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].Rssi );
					BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Cinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].Cinr );
					for( i0 = 0; i0 < 6; i0++ )
					{
						BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsIdmask_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].BsIdmask[i0].value );
					}
					for( i0 = 0; i0 < 6; i0++ )
					{
						BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsId_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].BsId[i0].value );
					}
					BM_ReportScanResults_List_CURRENT_ScanResultList_Report_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].ChannelId );
					BM_ReportScanResults_List_CURRENT_ScanResultList_Report_PreambleId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].PreambleId );
					BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkGrade_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].LinkGrade );
					BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ScanResultList_Report[ScanResultList_Report_index].LinkQuality );
				}
				ScanResultList_Report_index++;
			}

			BM_ReportScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportScanResults(UINT8* pBuf, ReportScanResults_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, j = 0, i0 = 0;


	BM_ReportScanResults_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.ScanStatus.Type == 187 )
	{
		BM_ReportScanResults_List_SET_TYPE( cur_ptr, cur_bitoff, 187 );
		length = 4;
		BM_ReportScanResults_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportScanResults_List_CURRENT_ScanStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanStatus.value );
		BM_ReportScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	for( j = 0; j < 33; j++ )
	{
		if( msg.ScanResultList_Report[j].Type == 189 )
		{
			BM_ReportScanResults_List_SET_TYPE( cur_ptr, cur_bitoff, 189 );
			length = 20;
			BM_ReportScanResults_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
			BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Rssi_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].Rssi );
			BM_ReportScanResults_List_CURRENT_ScanResultList_Report_Cinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].Cinr );
			for( i0 = 0; i0 < 6; i0++ )
			{
				BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsIdmask_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].BsIdmask[i0].value );
			}
			for( i0 = 0; i0 < 6; i0++ )
			{
				BM_ReportScanResults_List_CURRENT_ScanResultList_Report_BsId_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].BsId[i0].value );
			}
			BM_ReportScanResults_List_CURRENT_ScanResultList_Report_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].ChannelId );
			BM_ReportScanResults_List_CURRENT_ScanResultList_Report_PreambleId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].PreambleId );
			BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkGrade_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].LinkGrade );
			BM_ReportScanResults_List_CURRENT_ScanResultList_Report_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, msg.ScanResultList_Report[j].LinkQuality );
			BM_ReportScanResults_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize += 4;
			listSize += length;
		}
	}

	BM_ReportScanResults_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_SCAN_RESULT );
	BM_ReportScanResults_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportScanResults_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportScanResults_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportScanResults_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportScanResults(UINT8* pBuf, ReportScanResults_type* msg)
{
	return L4BM_Set_ReportScanResults(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportScanResults(ReportScanResults_type msg)
{
	UINT32 length = HEADER_SIZE, j = 0;

	if( msg.ScanStatus.Type == 187 )
	{
		length += 4;
		length += 4;
	}
	for( j = 0; j < 33; j++ )
	{
		if( msg.ScanResultList_Report[j].Type == 189 )
		{
			length += 20;
			length += 4;
		}
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportScanResults(ReportScanResults_type* msg)
{
	return L4BM_GetBufferSize_ReportScanResults(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportScanResults( void )
{
	UINT32 length = HEADER_SIZE, j = 0;

	length += 4;
	length += 4;
	for( j = 0; j < 33; j++ )
	{
		length += 20;
		length += 4;
	}

	return length;
}
void L4BM_Init_ReportScanResults(ReportScanResults_type* pMsg)
{
	UINT32 j = 0;

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->ScanStatus.Type = INVALID_OPCODE;
	for( j = 0; j < 33; j++ )
	{
		pMsg->ScanResultList_Report[j].Type = INVALID_OPCODE;
	}

}
L4bufman_Funcs ReportScanResults_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportScanResults,
	(pf_SetL4Command)L4BM_generic_Set_ReportScanResults,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportScanResults,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportScanResults,
	(pf_InitL4Command)L4BM_Init_ReportScanResults
};



//
// SetMonitorFilterTable
//
L4BUFMAN_Status_t L4BM_Get_SetMonitorFilterTable(SetMonitorFilterTable_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SetMonitorFilterTable(pMsg);
	BM_SetMonitorFilterTable_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetMonitorFilterTable_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetMonitorFilterTable_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetMonitorFilterTable_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SetMonitorFilterTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetMonitorFilterTable_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetMonitorFilterTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 4003 )
			{
				pMsg->MonitorFilterTable.Type = (UINT16)type;
				for( i0 = 0; i0 < 256; i0++ )
				{
					BM_SetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->MonitorFilterTable.FilterTable[i0].value );
				}
			}

			BM_SetMonitorFilterTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetMonitorFilterTable(UINT8* pBuf, SetMonitorFilterTable_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SetMonitorFilterTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.MonitorFilterTable.Type == 4003 )
	{
		BM_SetMonitorFilterTable_List_SET_TYPE( cur_ptr, cur_bitoff, 4003 );
		length = 256;
		BM_SetMonitorFilterTable_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 256; i0++ )
		{
			BM_SetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.MonitorFilterTable.FilterTable[i0].value );
		}
		BM_SetMonitorFilterTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetMonitorFilterTable_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_MONITOR_FILTER_TABLE );
	BM_SetMonitorFilterTable_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetMonitorFilterTable_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetMonitorFilterTable_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetMonitorFilterTable_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetMonitorFilterTable(UINT8* pBuf, SetMonitorFilterTable_type* msg)
{
	return L4BM_Set_SetMonitorFilterTable(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetMonitorFilterTable(SetMonitorFilterTable_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.MonitorFilterTable.Type == 4003 )
	{
		length += 256;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetMonitorFilterTable(SetMonitorFilterTable_type* msg)
{
	return L4BM_GetBufferSize_SetMonitorFilterTable(*msg);
}
UINT L4BM_GetMaxBufferSize_SetMonitorFilterTable( void )
{
	UINT32 length = HEADER_SIZE;

	length += 256;
	length += 4;

	return length;
}
void L4BM_Init_SetMonitorFilterTable(SetMonitorFilterTable_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->MonitorFilterTable.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetMonitorFilterTable_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetMonitorFilterTable,
	(pf_SetL4Command)L4BM_generic_Set_SetMonitorFilterTable,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetMonitorFilterTable,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetMonitorFilterTable,
	(pf_InitL4Command)L4BM_Init_SetMonitorFilterTable
};



//
// CmdCoexProcessEnd
//
L4BUFMAN_Status_t L4BM_Get_CmdCoexProcessEnd(CmdCoexProcessEnd_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_CmdCoexProcessEnd_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CmdCoexProcessEnd_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CmdCoexProcessEnd_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CmdCoexProcessEnd(UINT8* pBuf, CmdCoexProcessEnd_type msg)
{
	PVOID base_ptr = pBuf;

	CmdCoexProcessEnd_type tmp = msg;
	tmp = tmp;

	BM_CmdCoexProcessEnd_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_COEX_PROCESS_END );
	BM_CmdCoexProcessEnd_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CmdCoexProcessEnd_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CmdCoexProcessEnd_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CmdCoexProcessEnd_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CmdCoexProcessEnd(UINT8* pBuf, CmdCoexProcessEnd_type* msg)
{
	return L4BM_Set_CmdCoexProcessEnd(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CmdCoexProcessEnd(CmdCoexProcessEnd_type msg)
{

	CmdCoexProcessEnd_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_CmdCoexProcessEnd(CmdCoexProcessEnd_type* msg)
{
	return L4BM_GetBufferSize_CmdCoexProcessEnd(*msg);
}
UINT L4BM_GetMaxBufferSize_CmdCoexProcessEnd( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_CmdCoexProcessEnd(CmdCoexProcessEnd_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs CmdCoexProcessEnd_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CmdCoexProcessEnd,
	(pf_SetL4Command)L4BM_generic_Set_CmdCoexProcessEnd,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CmdCoexProcessEnd,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CmdCoexProcessEnd,
	(pf_InitL4Command)L4BM_Init_CmdCoexProcessEnd
};



//
// GetD2HChannelMask
//
L4BUFMAN_Status_t L4BM_Get_GetD2HChannelMask(GetD2HChannelMask_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_GetD2HChannelMask(pMsg);
	BM_GetD2HChannelMask_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetD2HChannelMask_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetD2HChannelMask_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetD2HChannelMask_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetD2HChannelMask_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetD2HChannelMask_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetD2HChannelMask_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 134 )
			{
				pMsg->D2HChannelMask.Type = (UINT16)type;
				BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HChannelMask.DataChannelSwitch );
				BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HChannelMask.DiagnosticsChannelSwitch );
				BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HChannelMask.Reserved );
			}

			BM_GetD2HChannelMask_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetD2HChannelMask(UINT8* pBuf, GetD2HChannelMask_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_GetD2HChannelMask_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.D2HChannelMask.Type == 134 )
	{
		BM_GetD2HChannelMask_List_SET_TYPE( cur_ptr, cur_bitoff, 134 );
		length = 4;
		BM_GetD2HChannelMask_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DataChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HChannelMask.DataChannelSwitch );
		BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_DiagnosticsChannelSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HChannelMask.DiagnosticsChannelSwitch );
		BM_GetD2HChannelMask_List_CURRENT_D2HChannelMask_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HChannelMask.Reserved );
		BM_GetD2HChannelMask_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetD2HChannelMask_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_D2H_CHANNEL_MASK );
	BM_GetD2HChannelMask_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetD2HChannelMask_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetD2HChannelMask_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetD2HChannelMask_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetD2HChannelMask(UINT8* pBuf, GetD2HChannelMask_type* msg)
{
	return L4BM_Set_GetD2HChannelMask(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetD2HChannelMask(GetD2HChannelMask_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.D2HChannelMask.Type == 134 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetD2HChannelMask(GetD2HChannelMask_type* msg)
{
	return L4BM_GetBufferSize_GetD2HChannelMask(*msg);
}
UINT L4BM_GetMaxBufferSize_GetD2HChannelMask( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_GetD2HChannelMask(GetD2HChannelMask_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->D2HChannelMask.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetD2HChannelMask_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetD2HChannelMask,
	(pf_SetL4Command)L4BM_generic_Set_GetD2HChannelMask,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetD2HChannelMask,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetD2HChannelMask,
	(pf_InitL4Command)L4BM_Init_GetD2HChannelMask
};



//
// SetPreInitConfiguration
//
L4BUFMAN_Status_t L4BM_Get_SetPreInitConfiguration(SetPreInitConfiguration_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SetPreInitConfiguration(pMsg);
	BM_SetPreInitConfiguration_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetPreInitConfiguration_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetPreInitConfiguration_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetPreInitConfiguration_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SetPreInitConfiguration_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetPreInitConfiguration_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetPreInitConfiguration_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 501 )
			{
				pMsg->PrivilegeKeyConfigComp.Type = (UINT16)type;
				for( i0 = 0; i0 < 4; i0++ )
				{
					BM_SetPreInitConfiguration_List_CURRENT_PrivilegeKeyConfigComp_Key_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->PrivilegeKeyConfigComp.Key[i0].value );
				}
			}
			if( type == 502 )
			{
				pMsg->LedOperationalConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_NvmOverride_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.NvmOverride );
				for( i0 = 0; i0 < 14; i0++ )
				{
					BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led0Scheme_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.ledBehavior[i0].Led0Scheme );
					BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led1Scheme_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.ledBehavior[i0].Led1Scheme );
				}
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_onPeriod_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.powerSaveInfo.ledBlinkRate.onPeriod );
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_offPeriod_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.powerSaveInfo.ledBlinkRate.offPeriod );
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_powerSaveMode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.powerSaveInfo.powerSaveMode );
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledTimeInterval_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.powerSaveInfo.ledTimeInterval );
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_numOfLeds_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.numOfLeds );
				for( i0 = 0; i0 < 13; i0++ )
				{
					BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_onPeriod_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.blinkingRate[i0].onPeriod );
					BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_offPeriod_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.blinkingRate[i0].offPeriod );
				}
				BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LedOperationalConfigComp.reserved );
			}
			if( type == 503 )
			{
				pMsg->LimitMaxTxPowerConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_LimitMaxTxPowerConfigComp_LimitMaxTxPower_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LimitMaxTxPowerConfigComp.LimitMaxTxPower );
			}
			if( type == 601 )
			{
				pMsg->IdleParametersConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdleTimeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->IdleParametersConfigComp.IdleTimeout );
				BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdlePagingInterval_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->IdleParametersConfigComp.IdlePagingInterval );
			}
			if( type == 611 )
			{
				pMsg->IdleParameterTimeoutConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_IdleParameterTimeoutConfigComp_IdleTimeout_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->IdleParameterTimeoutConfigComp.IdleTimeout );
			}
			if( type == 612 )
			{
				pMsg->IdleParameterPagingIntervalConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_IdleParameterPagingIntervalConfigComp_PagingInterval_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->IdleParameterPagingIntervalConfigComp.PagingInterval );
			}
			if( type == 613 )
			{
				pMsg->IdleParameterIdleEntrySuspendConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_IdleParameterIdleEntrySuspendConfigComp_IdleEntrySuspend_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->IdleParameterIdleEntrySuspendConfigComp.IdleEntrySuspend );
			}
			if( type == 618 )
			{
				pMsg->IdleParameterFullNeSuspendConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_IdleParameterFullNeSuspendConfigComp_FullNeSuspend_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->IdleParameterFullNeSuspendConfigComp.FullNeSuspend );
			}
			if( type == 602 )
			{
				pMsg->LinkDownTimerConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_LinkDownTimerConfigComp_LinkDown_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkDownTimerConfigComp.LinkDown );
			}
			if( type == 607 )
			{
				pMsg->ArqSupportConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ArqSupportConfigComp.GeneralState );
				BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ArqSupportConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ArqSupportConfigComp.Reserved2 );
			}
			if( type == 604 )
			{
				pMsg->LoopBackConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_OperationMode_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LoopBackConfigComp.OperationMode );
				BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LoopBackConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LoopBackConfigComp.Reserved2 );
			}
			if( type == 605 )
			{
				pMsg->ResetOnAssertConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ResetOnAssertConfigComp.GeneralState );
				BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ResetOnAssertConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ResetOnAssertConfigComp.Reserved2 );
			}
			if( type == 606 )
			{
				pMsg->WatchDogTimerConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->WatchDogTimerConfigComp.GeneralState );
				BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->WatchDogTimerConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->WatchDogTimerConfigComp.Reserved2 );
			}
			if( type == 608 )
			{
				pMsg->SlowClockConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_GeneralState_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SlowClockConfigComp.GeneralState );
				BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SlowClockConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SlowClockConfigComp.Reserved2 );
			}
			if( type == 609 )
			{
				pMsg->SelectivePLIParametersConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_EnableSelectivePLIs_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SelectivePLIParametersConfigComp.EnableSelectivePLIs );
				BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_DelayedSelectivePLI_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SelectivePLIParametersConfigComp.DelayedSelectivePLI );
				BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_ConsecutivePLIToReceive_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SelectivePLIParametersConfigComp.ConsecutivePLIToReceive );
				BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SelectivePLIParametersConfigComp.Reserved1 );
			}
			if( type == 610 )
			{
				pMsg->HarqParametersConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_HarqCategory_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->HarqParametersConfigComp.HarqCategory );
				BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->HarqParametersConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->HarqParametersConfigComp.Reserved2 );
			}
			if( type == 614 )
			{
				pMsg->D2HDataFormatConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_DataFormatMem_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HDataFormatConfigComp.DataFormatMem );
				BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HDataFormatConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->D2HDataFormatConfigComp.Reserved2 );
			}
			if( type == 615 )
			{
				pMsg->DLHostReorderConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_DLHostReorder_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DLHostReorderConfigComp.DLHostReorder );
				BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DLHostReorderConfigComp.Reserved1 );
				BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DLHostReorderConfigComp.Reserved2 );
			}
			if( type == 616 )
			{
				pMsg->PaddingPerCSConfigComp.Type = (UINT16)type;
				BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_CSType_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->PaddingPerCSConfigComp.CSType );
				BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_PaddingSize_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->PaddingPerCSConfigComp.PaddingSize );
				BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->PaddingPerCSConfigComp.Reserved );
			}

			BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetPreInitConfiguration(UINT8* pBuf, SetPreInitConfiguration_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SetPreInitConfiguration_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.PrivilegeKeyConfigComp.Type == 501 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 501 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 4; i0++ )
		{
			BM_SetPreInitConfiguration_List_CURRENT_PrivilegeKeyConfigComp_Key_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.PrivilegeKeyConfigComp.Key[i0].value );
		}
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LedOperationalConfigComp.Type == 502 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 502 );
		length = 64;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_NvmOverride_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.NvmOverride );
		for( i0 = 0; i0 < 14; i0++ )
		{
			BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led0Scheme_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.ledBehavior[i0].Led0Scheme );
			BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_ledBehavior_Led1Scheme_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.ledBehavior[i0].Led1Scheme );
		}
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_onPeriod_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.powerSaveInfo.ledBlinkRate.onPeriod );
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledBlinkRate_offPeriod_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.powerSaveInfo.ledBlinkRate.offPeriod );
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_powerSaveMode_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.powerSaveInfo.powerSaveMode );
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_powerSaveInfo_ledTimeInterval_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.powerSaveInfo.ledTimeInterval );
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_numOfLeds_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.numOfLeds );
		for( i0 = 0; i0 < 13; i0++ )
		{
			BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_onPeriod_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.blinkingRate[i0].onPeriod );
			BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_blinkingRate_offPeriod_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.blinkingRate[i0].offPeriod );
		}
		BM_SetPreInitConfiguration_List_CURRENT_LedOperationalConfigComp_reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.LedOperationalConfigComp.reserved );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LimitMaxTxPowerConfigComp.Type == 503 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 503 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_LimitMaxTxPowerConfigComp_LimitMaxTxPower_SET( base_ptr, cur_ptr, cur_bitoff, msg.LimitMaxTxPowerConfigComp.LimitMaxTxPower );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.IdleParametersConfigComp.Type == 601 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 601 );
		length = 8;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdleTimeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.IdleParametersConfigComp.IdleTimeout );
		BM_SetPreInitConfiguration_List_CURRENT_IdleParametersConfigComp_IdlePagingInterval_SET( base_ptr, cur_ptr, cur_bitoff, msg.IdleParametersConfigComp.IdlePagingInterval );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.IdleParameterTimeoutConfigComp.Type == 611 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 611 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_IdleParameterTimeoutConfigComp_IdleTimeout_SET( base_ptr, cur_ptr, cur_bitoff, msg.IdleParameterTimeoutConfigComp.IdleTimeout );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.IdleParameterPagingIntervalConfigComp.Type == 612 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 612 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_IdleParameterPagingIntervalConfigComp_PagingInterval_SET( base_ptr, cur_ptr, cur_bitoff, msg.IdleParameterPagingIntervalConfigComp.PagingInterval );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.IdleParameterIdleEntrySuspendConfigComp.Type == 613 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 613 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_IdleParameterIdleEntrySuspendConfigComp_IdleEntrySuspend_SET( base_ptr, cur_ptr, cur_bitoff, msg.IdleParameterIdleEntrySuspendConfigComp.IdleEntrySuspend );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.IdleParameterFullNeSuspendConfigComp.Type == 618 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 618 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_IdleParameterFullNeSuspendConfigComp_FullNeSuspend_SET( base_ptr, cur_ptr, cur_bitoff, msg.IdleParameterFullNeSuspendConfigComp.FullNeSuspend );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LinkDownTimerConfigComp.Type == 602 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 602 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_LinkDownTimerConfigComp_LinkDown_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkDownTimerConfigComp.LinkDown );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ArqSupportConfigComp.Type == 607 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 607 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, msg.ArqSupportConfigComp.GeneralState );
		BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.ArqSupportConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_ArqSupportConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.ArqSupportConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LoopBackConfigComp.Type == 604 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 604 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_OperationMode_SET( base_ptr, cur_ptr, cur_bitoff, msg.LoopBackConfigComp.OperationMode );
		BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.LoopBackConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_LoopBackConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.LoopBackConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ResetOnAssertConfigComp.Type == 605 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 605 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, msg.ResetOnAssertConfigComp.GeneralState );
		BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.ResetOnAssertConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_ResetOnAssertConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.ResetOnAssertConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.WatchDogTimerConfigComp.Type == 606 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 606 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, msg.WatchDogTimerConfigComp.GeneralState );
		BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.WatchDogTimerConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_WatchDogTimerConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.WatchDogTimerConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.SlowClockConfigComp.Type == 608 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 608 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_GeneralState_SET( base_ptr, cur_ptr, cur_bitoff, msg.SlowClockConfigComp.GeneralState );
		BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.SlowClockConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_SlowClockConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.SlowClockConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.SelectivePLIParametersConfigComp.Type == 609 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 609 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_EnableSelectivePLIs_SET( base_ptr, cur_ptr, cur_bitoff, msg.SelectivePLIParametersConfigComp.EnableSelectivePLIs );
		BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_DelayedSelectivePLI_SET( base_ptr, cur_ptr, cur_bitoff, msg.SelectivePLIParametersConfigComp.DelayedSelectivePLI );
		BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_ConsecutivePLIToReceive_SET( base_ptr, cur_ptr, cur_bitoff, msg.SelectivePLIParametersConfigComp.ConsecutivePLIToReceive );
		BM_SetPreInitConfiguration_List_CURRENT_SelectivePLIParametersConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.SelectivePLIParametersConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.HarqParametersConfigComp.Type == 610 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 610 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_HarqCategory_SET( base_ptr, cur_ptr, cur_bitoff, msg.HarqParametersConfigComp.HarqCategory );
		BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.HarqParametersConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_HarqParametersConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.HarqParametersConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.D2HDataFormatConfigComp.Type == 614 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 614 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_DataFormatMem_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HDataFormatConfigComp.DataFormatMem );
		BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HDataFormatConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_D2HDataFormatConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.D2HDataFormatConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.DLHostReorderConfigComp.Type == 615 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 615 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_DLHostReorder_SET( base_ptr, cur_ptr, cur_bitoff, msg.DLHostReorderConfigComp.DLHostReorder );
		BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.DLHostReorderConfigComp.Reserved1 );
		BM_SetPreInitConfiguration_List_CURRENT_DLHostReorderConfigComp_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.DLHostReorderConfigComp.Reserved2 );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.PaddingPerCSConfigComp.Type == 616 )
	{
		BM_SetPreInitConfiguration_List_SET_TYPE( cur_ptr, cur_bitoff, 616 );
		length = 4;
		BM_SetPreInitConfiguration_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_CSType_SET( base_ptr, cur_ptr, cur_bitoff, msg.PaddingPerCSConfigComp.CSType );
		BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_PaddingSize_SET( base_ptr, cur_ptr, cur_bitoff, msg.PaddingPerCSConfigComp.PaddingSize );
		BM_SetPreInitConfiguration_List_CURRENT_PaddingPerCSConfigComp_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.PaddingPerCSConfigComp.Reserved );
		BM_SetPreInitConfiguration_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetPreInitConfiguration_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_PREINIT_CONFIG );
	BM_SetPreInitConfiguration_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetPreInitConfiguration_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetPreInitConfiguration_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetPreInitConfiguration_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetPreInitConfiguration(UINT8* pBuf, SetPreInitConfiguration_type* msg)
{
	return L4BM_Set_SetPreInitConfiguration(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetPreInitConfiguration(SetPreInitConfiguration_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.PrivilegeKeyConfigComp.Type == 501 )
	{
		length += 4;
		length += 4;
	}
	if( msg.LedOperationalConfigComp.Type == 502 )
	{
		length += 64;
		length += 4;
	}
	if( msg.LimitMaxTxPowerConfigComp.Type == 503 )
	{
		length += 4;
		length += 4;
	}
	if( msg.IdleParametersConfigComp.Type == 601 )
	{
		length += 8;
		length += 4;
	}
	if( msg.IdleParameterTimeoutConfigComp.Type == 611 )
	{
		length += 4;
		length += 4;
	}
	if( msg.IdleParameterPagingIntervalConfigComp.Type == 612 )
	{
		length += 4;
		length += 4;
	}
	if( msg.IdleParameterIdleEntrySuspendConfigComp.Type == 613 )
	{
		length += 4;
		length += 4;
	}
	if( msg.IdleParameterFullNeSuspendConfigComp.Type == 618 )
	{
		length += 4;
		length += 4;
	}
	if( msg.LinkDownTimerConfigComp.Type == 602 )
	{
		length += 4;
		length += 4;
	}
	if( msg.ArqSupportConfigComp.Type == 607 )
	{
		length += 4;
		length += 4;
	}
	if( msg.LoopBackConfigComp.Type == 604 )
	{
		length += 4;
		length += 4;
	}
	if( msg.ResetOnAssertConfigComp.Type == 605 )
	{
		length += 4;
		length += 4;
	}
	if( msg.WatchDogTimerConfigComp.Type == 606 )
	{
		length += 4;
		length += 4;
	}
	if( msg.SlowClockConfigComp.Type == 608 )
	{
		length += 4;
		length += 4;
	}
	if( msg.SelectivePLIParametersConfigComp.Type == 609 )
	{
		length += 4;
		length += 4;
	}
	if( msg.HarqParametersConfigComp.Type == 610 )
	{
		length += 4;
		length += 4;
	}
	if( msg.D2HDataFormatConfigComp.Type == 614 )
	{
		length += 4;
		length += 4;
	}
	if( msg.DLHostReorderConfigComp.Type == 615 )
	{
		length += 4;
		length += 4;
	}
	if( msg.PaddingPerCSConfigComp.Type == 616 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetPreInitConfiguration(SetPreInitConfiguration_type* msg)
{
	return L4BM_GetBufferSize_SetPreInitConfiguration(*msg);
}
UINT L4BM_GetMaxBufferSize_SetPreInitConfiguration( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += 64;
	length += 4;
	length += 4;
	length += 4;
	length += 8;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_SetPreInitConfiguration(SetPreInitConfiguration_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->PrivilegeKeyConfigComp.Type = INVALID_OPCODE;
	pMsg->LedOperationalConfigComp.Type = INVALID_OPCODE;
	pMsg->LimitMaxTxPowerConfigComp.Type = INVALID_OPCODE;
	pMsg->IdleParametersConfigComp.Type = INVALID_OPCODE;
	pMsg->IdleParameterTimeoutConfigComp.Type = INVALID_OPCODE;
	pMsg->IdleParameterPagingIntervalConfigComp.Type = INVALID_OPCODE;
	pMsg->IdleParameterIdleEntrySuspendConfigComp.Type = INVALID_OPCODE;
	pMsg->IdleParameterFullNeSuspendConfigComp.Type = INVALID_OPCODE;
	pMsg->LinkDownTimerConfigComp.Type = INVALID_OPCODE;
	pMsg->ArqSupportConfigComp.Type = INVALID_OPCODE;
	pMsg->LoopBackConfigComp.Type = INVALID_OPCODE;
	pMsg->ResetOnAssertConfigComp.Type = INVALID_OPCODE;
	pMsg->WatchDogTimerConfigComp.Type = INVALID_OPCODE;
	pMsg->SlowClockConfigComp.Type = INVALID_OPCODE;
	pMsg->SelectivePLIParametersConfigComp.Type = INVALID_OPCODE;
	pMsg->HarqParametersConfigComp.Type = INVALID_OPCODE;
	pMsg->D2HDataFormatConfigComp.Type = INVALID_OPCODE;
	pMsg->DLHostReorderConfigComp.Type = INVALID_OPCODE;
	pMsg->PaddingPerCSConfigComp.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetPreInitConfiguration_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetPreInitConfiguration,
	(pf_SetL4Command)L4BM_generic_Set_SetPreInitConfiguration,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetPreInitConfiguration,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetPreInitConfiguration,
	(pf_InitL4Command)L4BM_Init_SetPreInitConfiguration
};



//
// CheckL3L4InterfaceGET
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_CheckL3L4InterfaceGET(pMsg);
	BM_CheckL3L4InterfaceGET_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CheckL3L4InterfaceGET_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CheckL3L4InterfaceGET_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_CheckL3L4InterfaceGET_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_CheckL3L4InterfaceGET_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_CheckL3L4InterfaceGET_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_CheckL3L4InterfaceGET_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 2050 )
			{
				pMsg->value.Type = (UINT16)type;
				BM_CheckL3L4InterfaceGET_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->value.value );
			}

			BM_CheckL3L4InterfaceGET_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceGET(UINT8* pBuf, CheckL3L4InterfaceGET_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_CheckL3L4InterfaceGET_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.value.Type == 2050 )
	{
		BM_CheckL3L4InterfaceGET_List_SET_TYPE( cur_ptr, cur_bitoff, 2050 );
		length = 4;
		BM_CheckL3L4InterfaceGET_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_CheckL3L4InterfaceGET_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.value.value );
		BM_CheckL3L4InterfaceGET_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_CheckL3L4InterfaceGET_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_CHECK_INTERFACE );
	BM_CheckL3L4InterfaceGET_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CheckL3L4InterfaceGET_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CheckL3L4InterfaceGET_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CheckL3L4InterfaceGET_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CheckL3L4InterfaceGET(UINT8* pBuf, CheckL3L4InterfaceGET_type* msg)
{
	return L4BM_Set_CheckL3L4InterfaceGET(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.value.Type == 2050 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type* msg)
{
	return L4BM_GetBufferSize_CheckL3L4InterfaceGET(*msg);
}
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceGET( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_CheckL3L4InterfaceGET(CheckL3L4InterfaceGET_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->value.Type = INVALID_OPCODE;

}
L4bufman_Funcs CheckL3L4InterfaceGET_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CheckL3L4InterfaceGET,
	(pf_SetL4Command)L4BM_generic_Set_CheckL3L4InterfaceGET,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CheckL3L4InterfaceGET,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CheckL3L4InterfaceGET,
	(pf_InitL4Command)L4BM_Init_CheckL3L4InterfaceGET
};



//
// ReportSII
//
L4BUFMAN_Status_t L4BM_Get_ReportSII(ReportSII_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportSII(pMsg);
	BM_ReportSII_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportSII_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportSII_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportSII_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ReportSII_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportSII_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportSII_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 193 )
			{
				pMsg->NSPIDList.Type = (UINT16)type;
				BM_ReportSII_List_CURRENT_NSPIDList_NspIdListLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NSPIDList.NspIdListLength );
				for( i0 = 0; i0 < (UINT32)pMsg->NSPIDList.NspIdListLength; i0++ )
				{
					BM_ReportSII_List_CURRENT_NSPIDList_NspIdListData_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->NSPIDList.NspIdListData[i0].value );
				}
			}
			if( type == 194 )
			{
				pMsg->NSPVerboseNameList.Type = (UINT16)type;
				BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NSPVerboseNameList.NspVerboseListLength );
				for( i0 = 0; i0 < (UINT32)pMsg->NSPVerboseNameList.NspVerboseListLength; i0++ )
				{
					BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListData_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->NSPVerboseNameList.NspVerboseListData[i0].value );
				}
			}
			if( type == 195 )
			{
				pMsg->Realm.Type = (UINT16)type;
				BM_ReportSII_List_CURRENT_Realm_RealmLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->Realm.RealmLength );
				for( i0 = 0; i0 < (UINT32)pMsg->Realm.RealmLength; i0++ )
				{
					BM_ReportSII_List_CURRENT_Realm_RealmData_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->Realm.RealmData[i0].value );
				}
			}

			BM_ReportSII_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportSII(UINT8* pBuf, ReportSII_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_ReportSII_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.NSPIDList.Type == 193 )
	{
		BM_ReportSII_List_SET_TYPE( cur_ptr, cur_bitoff, 193 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.NSPIDList.NspIdListLength + 4);
		BM_ReportSII_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportSII_List_CURRENT_NSPIDList_NspIdListLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.NSPIDList.NspIdListLength );
		for( i0 = 0; i0 < (UINT32)msg.NSPIDList.NspIdListLength; i0++ )
		{
			BM_ReportSII_List_CURRENT_NSPIDList_NspIdListData_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.NSPIDList.NspIdListData[i0].value );
		}
		BM_ReportSII_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.NSPVerboseNameList.Type == 194 )
	{
		BM_ReportSII_List_SET_TYPE( cur_ptr, cur_bitoff, 194 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.NSPVerboseNameList.NspVerboseListLength + 4);
		BM_ReportSII_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.NSPVerboseNameList.NspVerboseListLength );
		for( i0 = 0; i0 < (UINT32)msg.NSPVerboseNameList.NspVerboseListLength; i0++ )
		{
			BM_ReportSII_List_CURRENT_NSPVerboseNameList_NspVerboseListData_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.NSPVerboseNameList.NspVerboseListData[i0].value );
		}
		BM_ReportSII_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.Realm.Type == 195 )
	{
		BM_ReportSII_List_SET_TYPE( cur_ptr, cur_bitoff, 195 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.Realm.RealmLength + 4);
		BM_ReportSII_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportSII_List_CURRENT_Realm_RealmLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.Realm.RealmLength );
		for( i0 = 0; i0 < (UINT32)msg.Realm.RealmLength; i0++ )
		{
			BM_ReportSII_List_CURRENT_Realm_RealmData_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.Realm.RealmData[i0].value );
		}
		BM_ReportSII_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ReportSII_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_SII );
	BM_ReportSII_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportSII_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportSII_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportSII_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportSII(UINT8* pBuf, ReportSII_type* msg)
{
	return L4BM_Set_ReportSII(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportSII(ReportSII_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.NSPIDList.Type == 193 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.NSPIDList.NspIdListLength + 4);
		length += 4;
	}
	if( msg.NSPVerboseNameList.Type == 194 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.NSPVerboseNameList.NspVerboseListLength + 4);
		length += 4;
	}
	if( msg.Realm.Type == 195 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.Realm.RealmLength + 4);
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportSII(ReportSII_type* msg)
{
	return L4BM_GetBufferSize_ReportSII(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportSII( void )
{
	UINT32 length = HEADER_SIZE;

	length += L4BM_RoundUp4Bytes((UINT32)512 + 4);
	length += 4;
	length += L4BM_RoundUp4Bytes((UINT32)1024 + 4);
	length += 4;
	length += L4BM_RoundUp4Bytes((UINT32)512 + 4);
	length += 4;

	return length;
}
void L4BM_Init_ReportSII(ReportSII_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->NSPIDList.Type = INVALID_OPCODE;
	pMsg->NSPVerboseNameList.Type = INVALID_OPCODE;
	pMsg->Realm.Type = INVALID_OPCODE;

}
L4bufman_Funcs ReportSII_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportSII,
	(pf_SetL4Command)L4BM_generic_Set_ReportSII,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportSII,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportSII,
	(pf_InitL4Command)L4BM_Init_ReportSII
};



//
// ScanCommand
//
L4BUFMAN_Status_t L4BM_Get_ScanCommand(ScanCommand_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_ScanCommand(pMsg);
	BM_ScanCommand_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ScanCommand_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ScanCommand_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ScanCommand_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ScanCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ScanCommand_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ScanCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 186 )
			{
				pMsg->DoScanCommand.Type = (UINT16)type;
				BM_ScanCommand_List_CURRENT_DoScanCommand_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DoScanCommand.value );
			}
			if( type == 164 )
			{
				pMsg->CoexPriority.Type = (UINT16)type;
				BM_ScanCommand_List_CURRENT_CoexPriority_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->CoexPriority.value );
			}

			BM_ScanCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ScanCommand(UINT8* pBuf, ScanCommand_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_ScanCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.DoScanCommand.Type == 186 )
	{
		BM_ScanCommand_List_SET_TYPE( cur_ptr, cur_bitoff, 186 );
		length = 4;
		BM_ScanCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ScanCommand_List_CURRENT_DoScanCommand_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.DoScanCommand.value );
		BM_ScanCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.CoexPriority.Type == 164 )
	{
		BM_ScanCommand_List_SET_TYPE( cur_ptr, cur_bitoff, 164 );
		length = 4;
		BM_ScanCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ScanCommand_List_CURRENT_CoexPriority_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.CoexPriority.value );
		BM_ScanCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ScanCommand_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_SCAN );
	BM_ScanCommand_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ScanCommand_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ScanCommand_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ScanCommand_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ScanCommand(UINT8* pBuf, ScanCommand_type* msg)
{
	return L4BM_Set_ScanCommand(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ScanCommand(ScanCommand_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.DoScanCommand.Type == 186 )
	{
		length += 4;
		length += 4;
	}
	if( msg.CoexPriority.Type == 164 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ScanCommand(ScanCommand_type* msg)
{
	return L4BM_GetBufferSize_ScanCommand(*msg);
}
UINT L4BM_GetMaxBufferSize_ScanCommand( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_ScanCommand(ScanCommand_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->DoScanCommand.Type = INVALID_OPCODE;
	pMsg->CoexPriority.Type = INVALID_OPCODE;

}
L4bufman_Funcs ScanCommand_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ScanCommand,
	(pf_SetL4Command)L4BM_generic_Set_ScanCommand,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ScanCommand,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ScanCommand,
	(pf_InitL4Command)L4BM_Init_ScanCommand
};



//
// TerminateCommand
//
L4BUFMAN_Status_t L4BM_Get_TerminateCommand(TerminateCommand_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_TerminateCommand_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_TerminateCommand_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_TerminateCommand_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_TerminateCommand(UINT8* pBuf, TerminateCommand_type msg)
{
	PVOID base_ptr = pBuf;

	TerminateCommand_type tmp = msg;
	tmp = tmp;

	BM_TerminateCommand_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_TERMINATE );
	BM_TerminateCommand_Header_Version_SET( base_ptr, msg.header.Version );
	BM_TerminateCommand_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_TerminateCommand_Header_Status_SET( base_ptr, msg.header.Status );
	BM_TerminateCommand_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_TerminateCommand(UINT8* pBuf, TerminateCommand_type* msg)
{
	return L4BM_Set_TerminateCommand(pBuf, *msg);
}
UINT L4BM_GetBufferSize_TerminateCommand(TerminateCommand_type msg)
{

	TerminateCommand_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_TerminateCommand(TerminateCommand_type* msg)
{
	return L4BM_GetBufferSize_TerminateCommand(*msg);
}
UINT L4BM_GetMaxBufferSize_TerminateCommand( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_TerminateCommand(TerminateCommand_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs TerminateCommand_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_TerminateCommand,
	(pf_SetL4Command)L4BM_generic_Set_TerminateCommand,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_TerminateCommand,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_TerminateCommand,
	(pf_InitL4Command)L4BM_Init_TerminateCommand
};



//
// ReadyForPowerSave
//
L4BUFMAN_Status_t L4BM_Get_ReadyForPowerSave(ReadyForPowerSave_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_ReadyForPowerSave_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReadyForPowerSave_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReadyForPowerSave_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReadyForPowerSave(UINT8* pBuf, ReadyForPowerSave_type msg)
{
	PVOID base_ptr = pBuf;

	ReadyForPowerSave_type tmp = msg;
	tmp = tmp;

	BM_ReadyForPowerSave_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_READY_FOR_POWER_SAVE );
	BM_ReadyForPowerSave_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReadyForPowerSave_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReadyForPowerSave_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReadyForPowerSave_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReadyForPowerSave(UINT8* pBuf, ReadyForPowerSave_type* msg)
{
	return L4BM_Set_ReadyForPowerSave(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReadyForPowerSave(ReadyForPowerSave_type msg)
{

	ReadyForPowerSave_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_ReadyForPowerSave(ReadyForPowerSave_type* msg)
{
	return L4BM_GetBufferSize_ReadyForPowerSave(*msg);
}
UINT L4BM_GetMaxBufferSize_ReadyForPowerSave( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_ReadyForPowerSave(ReadyForPowerSave_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs ReadyForPowerSave_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReadyForPowerSave,
	(pf_SetL4Command)L4BM_generic_Set_ReadyForPowerSave,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReadyForPowerSave,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReadyForPowerSave,
	(pf_InitL4Command)L4BM_Init_ReadyForPowerSave
};



//
// Disconnect
//
L4BUFMAN_Status_t L4BM_Get_Disconnect(Disconnect_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_Disconnect_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_Disconnect_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_Disconnect_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_Disconnect(UINT8* pBuf, Disconnect_type msg)
{
	PVOID base_ptr = pBuf;

	Disconnect_type tmp = msg;
	tmp = tmp;

	BM_Disconnect_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_DISCONNECT );
	BM_Disconnect_Header_Version_SET( base_ptr, msg.header.Version );
	BM_Disconnect_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_Disconnect_Header_Status_SET( base_ptr, msg.header.Status );
	BM_Disconnect_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_Disconnect(UINT8* pBuf, Disconnect_type* msg)
{
	return L4BM_Set_Disconnect(pBuf, *msg);
}
UINT L4BM_GetBufferSize_Disconnect(Disconnect_type msg)
{

	Disconnect_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_Disconnect(Disconnect_type* msg)
{
	return L4BM_GetBufferSize_Disconnect(*msg);
}
UINT L4BM_GetMaxBufferSize_Disconnect( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_Disconnect(Disconnect_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs Disconnect_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_Disconnect,
	(pf_SetL4Command)L4BM_generic_Set_Disconnect,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_Disconnect,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_Disconnect,
	(pf_InitL4Command)L4BM_Init_Disconnect
};



//
// SetEapSuccess
//
L4BUFMAN_Status_t L4BM_Get_SetEapSuccess(SetEapSuccess_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_SetEapSuccess_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetEapSuccess_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetEapSuccess_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetEapSuccess(UINT8* pBuf, SetEapSuccess_type msg)
{
	PVOID base_ptr = pBuf;

	SetEapSuccess_type tmp = msg;
	tmp = tmp;

	BM_SetEapSuccess_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_EAP_SUCCESS );
	BM_SetEapSuccess_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetEapSuccess_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetEapSuccess_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetEapSuccess_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetEapSuccess(UINT8* pBuf, SetEapSuccess_type* msg)
{
	return L4BM_Set_SetEapSuccess(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetEapSuccess(SetEapSuccess_type msg)
{

	SetEapSuccess_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_SetEapSuccess(SetEapSuccess_type* msg)
{
	return L4BM_GetBufferSize_SetEapSuccess(*msg);
}
UINT L4BM_GetMaxBufferSize_SetEapSuccess( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_SetEapSuccess(SetEapSuccess_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs SetEapSuccess_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetEapSuccess,
	(pf_SetL4Command)L4BM_generic_Set_SetEapSuccess,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetEapSuccess,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetEapSuccess,
	(pf_InitL4Command)L4BM_Init_SetEapSuccess
};



//
// CmdCoexProcessStart
//
L4BUFMAN_Status_t L4BM_Get_CmdCoexProcessStart(CmdCoexProcessStart_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_CmdCoexProcessStart(pMsg);
	BM_CmdCoexProcessStart_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CmdCoexProcessStart_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CmdCoexProcessStart_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_CmdCoexProcessStart_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_CmdCoexProcessStart_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_CmdCoexProcessStart_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_CmdCoexProcessStart_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 166 )
			{
				pMsg->ProcessType.Type = (UINT16)type;
				BM_CmdCoexProcessStart_List_CURRENT_ProcessType_State_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ProcessType.State );
			}

			BM_CmdCoexProcessStart_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CmdCoexProcessStart(UINT8* pBuf, CmdCoexProcessStart_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_CmdCoexProcessStart_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.ProcessType.Type == 166 )
	{
		BM_CmdCoexProcessStart_List_SET_TYPE( cur_ptr, cur_bitoff, 166 );
		length = 4;
		BM_CmdCoexProcessStart_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_CmdCoexProcessStart_List_CURRENT_ProcessType_State_SET( base_ptr, cur_ptr, cur_bitoff, msg.ProcessType.State );
		BM_CmdCoexProcessStart_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_CmdCoexProcessStart_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_COEX_PROCESS_START );
	BM_CmdCoexProcessStart_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CmdCoexProcessStart_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CmdCoexProcessStart_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CmdCoexProcessStart_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CmdCoexProcessStart(UINT8* pBuf, CmdCoexProcessStart_type* msg)
{
	return L4BM_Set_CmdCoexProcessStart(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CmdCoexProcessStart(CmdCoexProcessStart_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.ProcessType.Type == 166 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_CmdCoexProcessStart(CmdCoexProcessStart_type* msg)
{
	return L4BM_GetBufferSize_CmdCoexProcessStart(*msg);
}
UINT L4BM_GetMaxBufferSize_CmdCoexProcessStart( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_CmdCoexProcessStart(CmdCoexProcessStart_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->ProcessType.Type = INVALID_OPCODE;

}
L4bufman_Funcs CmdCoexProcessStart_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CmdCoexProcessStart,
	(pf_SetL4Command)L4BM_generic_Set_CmdCoexProcessStart,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CmdCoexProcessStart,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CmdCoexProcessStart,
	(pf_InitL4Command)L4BM_Init_CmdCoexProcessStart
};



//
// InitCommand
//
L4BUFMAN_Status_t L4BM_Get_InitCommand(InitCommand_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_InitCommand_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_InitCommand_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_InitCommand_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_InitCommand(UINT8* pBuf, InitCommand_type msg)
{
	PVOID base_ptr = pBuf;

	InitCommand_type tmp = msg;
	tmp = tmp;

	BM_InitCommand_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_INIT );
	BM_InitCommand_Header_Version_SET( base_ptr, msg.header.Version );
	BM_InitCommand_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_InitCommand_Header_Status_SET( base_ptr, msg.header.Status );
	BM_InitCommand_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_InitCommand(UINT8* pBuf, InitCommand_type* msg)
{
	return L4BM_Set_InitCommand(pBuf, *msg);
}
UINT L4BM_GetBufferSize_InitCommand(InitCommand_type msg)
{

	InitCommand_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_InitCommand(InitCommand_type* msg)
{
	return L4BM_GetBufferSize_InitCommand(*msg);
}
UINT L4BM_GetMaxBufferSize_InitCommand( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_InitCommand(InitCommand_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs InitCommand_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_InitCommand,
	(pf_SetL4Command)L4BM_generic_Set_InitCommand,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_InitCommand,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_InitCommand,
	(pf_InitL4Command)L4BM_Init_InitCommand
};



//
// SetEapKey
//
L4BUFMAN_Status_t L4BM_Get_SetEapKey(SetEapKey_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SetEapKey(pMsg);
	BM_SetEapKey_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetEapKey_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetEapKey_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetEapKey_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SetEapKey_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetEapKey_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetEapKey_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1028 )
			{
				pMsg->EapKeyValid.Type = (UINT16)type;
				BM_SetEapKey_List_CURRENT_EapKeyValid_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->EapKeyValid.value );
			}
			if( type == 1029 )
			{
				pMsg->EapKeyMsk.Type = (UINT16)type;
				for( i0 = 0; i0 < 64; i0++ )
				{
					BM_SetEapKey_List_CURRENT_EapKeyMsk_EapKeyMskArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->EapKeyMsk.EapKeyMskArr[i0].value );
				}
			}

			BM_SetEapKey_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetEapKey(UINT8* pBuf, SetEapKey_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SetEapKey_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.EapKeyValid.Type == 1028 )
	{
		BM_SetEapKey_List_SET_TYPE( cur_ptr, cur_bitoff, 1028 );
		length = 4;
		BM_SetEapKey_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetEapKey_List_CURRENT_EapKeyValid_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.EapKeyValid.value );
		BM_SetEapKey_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.EapKeyMsk.Type == 1029 )
	{
		BM_SetEapKey_List_SET_TYPE( cur_ptr, cur_bitoff, 1029 );
		length = 64;
		BM_SetEapKey_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 64; i0++ )
		{
			BM_SetEapKey_List_CURRENT_EapKeyMsk_EapKeyMskArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.EapKeyMsk.EapKeyMskArr[i0].value );
		}
		BM_SetEapKey_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetEapKey_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_EAP_KEY );
	BM_SetEapKey_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetEapKey_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetEapKey_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetEapKey_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetEapKey(UINT8* pBuf, SetEapKey_type* msg)
{
	return L4BM_Set_SetEapKey(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetEapKey(SetEapKey_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.EapKeyValid.Type == 1028 )
	{
		length += 4;
		length += 4;
	}
	if( msg.EapKeyMsk.Type == 1029 )
	{
		length += 64;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetEapKey(SetEapKey_type* msg)
{
	return L4BM_GetBufferSize_SetEapKey(*msg);
}
UINT L4BM_GetMaxBufferSize_SetEapKey( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += 64;
	length += 4;

	return length;
}
void L4BM_Init_SetEapKey(SetEapKey_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->EapKeyValid.Type = INVALID_OPCODE;
	pMsg->EapKeyMsk.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetEapKey_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetEapKey,
	(pf_SetL4Command)L4BM_generic_Set_SetEapKey,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetEapKey,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetEapKey,
	(pf_InitL4Command)L4BM_Init_SetEapKey
};



//
// CheckL3L4InterfaceSET
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_CheckL3L4InterfaceSET(pMsg);
	BM_CheckL3L4InterfaceSET_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CheckL3L4InterfaceSET_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CheckL3L4InterfaceSET_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_CheckL3L4InterfaceSET_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_CheckL3L4InterfaceSET_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_CheckL3L4InterfaceSET_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_CheckL3L4InterfaceSET_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 2051 )
			{
				pMsg->value.Type = (UINT16)type;
				BM_CheckL3L4InterfaceSET_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->value.value );
			}

			BM_CheckL3L4InterfaceSET_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceSET(UINT8* pBuf, CheckL3L4InterfaceSET_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_CheckL3L4InterfaceSET_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.value.Type == 2051 )
	{
		BM_CheckL3L4InterfaceSET_List_SET_TYPE( cur_ptr, cur_bitoff, 2051 );
		length = 4;
		BM_CheckL3L4InterfaceSET_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_CheckL3L4InterfaceSET_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.value.value );
		BM_CheckL3L4InterfaceSET_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_CheckL3L4InterfaceSET_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_CHECK_INTERFACE );
	BM_CheckL3L4InterfaceSET_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CheckL3L4InterfaceSET_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CheckL3L4InterfaceSET_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CheckL3L4InterfaceSET_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CheckL3L4InterfaceSET(UINT8* pBuf, CheckL3L4InterfaceSET_type* msg)
{
	return L4BM_Set_CheckL3L4InterfaceSET(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.value.Type == 2051 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type* msg)
{
	return L4BM_GetBufferSize_CheckL3L4InterfaceSET(*msg);
}
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceSET( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_CheckL3L4InterfaceSET(CheckL3L4InterfaceSET_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->value.Type = INVALID_OPCODE;

}
L4bufman_Funcs CheckL3L4InterfaceSET_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CheckL3L4InterfaceSET,
	(pf_SetL4Command)L4BM_generic_Set_CheckL3L4InterfaceSET,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CheckL3L4InterfaceSET,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CheckL3L4InterfaceSET,
	(pf_InitL4Command)L4BM_Init_CheckL3L4InterfaceSET
};



//
// MOC_Broadcast
//
L4BUFMAN_Status_t L4BM_Get_MOC_Broadcast(MOC_Broadcast_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_MOC_Broadcast_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_MOC_Broadcast_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_MOC_Broadcast_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_MOC_Broadcast(UINT8* pBuf, MOC_Broadcast_type msg)
{
	PVOID base_ptr = pBuf;

	MOC_Broadcast_type tmp = msg;
	tmp = tmp;

	BM_MOC_Broadcast_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_MOC_BROADCAST );
	BM_MOC_Broadcast_Header_Version_SET( base_ptr, msg.header.Version );
	BM_MOC_Broadcast_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_MOC_Broadcast_Header_Status_SET( base_ptr, msg.header.Status );
	BM_MOC_Broadcast_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_MOC_Broadcast(UINT8* pBuf, MOC_Broadcast_type* msg)
{
	return L4BM_Set_MOC_Broadcast(pBuf, *msg);
}
UINT L4BM_GetBufferSize_MOC_Broadcast(MOC_Broadcast_type msg)
{

	MOC_Broadcast_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_MOC_Broadcast(MOC_Broadcast_type* msg)
{
	return L4BM_GetBufferSize_MOC_Broadcast(*msg);
}
UINT L4BM_GetMaxBufferSize_MOC_Broadcast( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_MOC_Broadcast(MOC_Broadcast_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs MOC_Broadcast_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_MOC_Broadcast,
	(pf_SetL4Command)L4BM_generic_Set_MOC_Broadcast,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_MOC_Broadcast,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_MOC_Broadcast,
	(pf_InitL4Command)L4BM_Init_MOC_Broadcast
};



//
// SetCoexMode
//
L4BUFMAN_Status_t L4BM_Get_SetCoexMode(SetCoexMode_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_SetCoexMode(pMsg);
	BM_SetCoexMode_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetCoexMode_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetCoexMode_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetCoexMode_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SetCoexMode_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetCoexMode_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetCoexMode_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 165 )
			{
				pMsg->CoexistenceModeType.Type = (UINT16)type;
				BM_SetCoexMode_List_CURRENT_CoexistenceModeType_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->CoexistenceModeType.value );
			}

			BM_SetCoexMode_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetCoexMode(UINT8* pBuf, SetCoexMode_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_SetCoexMode_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.CoexistenceModeType.Type == 165 )
	{
		BM_SetCoexMode_List_SET_TYPE( cur_ptr, cur_bitoff, 165 );
		length = 4;
		BM_SetCoexMode_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SetCoexMode_List_CURRENT_CoexistenceModeType_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.CoexistenceModeType.value );
		BM_SetCoexMode_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetCoexMode_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_COEX_MODE );
	BM_SetCoexMode_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetCoexMode_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetCoexMode_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetCoexMode_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetCoexMode(UINT8* pBuf, SetCoexMode_type* msg)
{
	return L4BM_Set_SetCoexMode(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetCoexMode(SetCoexMode_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.CoexistenceModeType.Type == 165 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetCoexMode(SetCoexMode_type* msg)
{
	return L4BM_GetBufferSize_SetCoexMode(*msg);
}
UINT L4BM_GetMaxBufferSize_SetCoexMode( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_SetCoexMode(SetCoexMode_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->CoexistenceModeType.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetCoexMode_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetCoexMode,
	(pf_SetL4Command)L4BM_generic_Set_SetCoexMode,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetCoexMode,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetCoexMode,
	(pf_InitL4Command)L4BM_Init_SetCoexMode
};



//
// SetTraceSeverityTable
//
L4BUFMAN_Status_t L4BM_Get_SetTraceSeverityTable(SetTraceSeverityTable_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SetTraceSeverityTable(pMsg);
	BM_SetTraceSeverityTable_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetTraceSeverityTable_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetTraceSeverityTable_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SetTraceSeverityTable_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SetTraceSeverityTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SetTraceSeverityTable_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SetTraceSeverityTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 4001 )
			{
				pMsg->TraceSeverityTable.Type = (UINT16)type;
				for( i0 = 0; i0 < 256; i0++ )
				{
					BM_SetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->TraceSeverityTable.SeverityTable[i0].value );
				}
			}

			BM_SetTraceSeverityTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetTraceSeverityTable(UINT8* pBuf, SetTraceSeverityTable_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SetTraceSeverityTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.TraceSeverityTable.Type == 4001 )
	{
		BM_SetTraceSeverityTable_List_SET_TYPE( cur_ptr, cur_bitoff, 4001 );
		length = 256;
		BM_SetTraceSeverityTable_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 256; i0++ )
		{
			BM_SetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.TraceSeverityTable.SeverityTable[i0].value );
		}
		BM_SetTraceSeverityTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SetTraceSeverityTable_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_TRACE_SEVERITY_TABLE );
	BM_SetTraceSeverityTable_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetTraceSeverityTable_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetTraceSeverityTable_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetTraceSeverityTable_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetTraceSeverityTable(UINT8* pBuf, SetTraceSeverityTable_type* msg)
{
	return L4BM_Set_SetTraceSeverityTable(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetTraceSeverityTable(SetTraceSeverityTable_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.TraceSeverityTable.Type == 4001 )
	{
		length += 256;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SetTraceSeverityTable(SetTraceSeverityTable_type* msg)
{
	return L4BM_GetBufferSize_SetTraceSeverityTable(*msg);
}
UINT L4BM_GetMaxBufferSize_SetTraceSeverityTable( void )
{
	UINT32 length = HEADER_SIZE;

	length += 256;
	length += 4;

	return length;
}
void L4BM_Init_SetTraceSeverityTable(SetTraceSeverityTable_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->TraceSeverityTable.Type = INVALID_OPCODE;

}
L4bufman_Funcs SetTraceSeverityTable_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetTraceSeverityTable,
	(pf_SetL4Command)L4BM_generic_Set_SetTraceSeverityTable,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetTraceSeverityTable,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetTraceSeverityTable,
	(pf_InitL4Command)L4BM_Init_SetTraceSeverityTable
};



//
// ReportBsInfo
//
L4BUFMAN_Status_t L4BM_Get_ReportBsInfo(ReportBsInfo_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportBsInfo(pMsg);
	BM_ReportBsInfo_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportBsInfo_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportBsInfo_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportBsInfo_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ReportBsInfo_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportBsInfo_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportBsInfo_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 196 )
			{
				pMsg->BSID.Type = (UINT16)type;
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_ReportBsInfo_List_CURRENT_BSID_FullBSID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->BSID.FullBSID[i0].value );
				}
				BM_ReportBsInfo_List_CURRENT_BSID_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->BSID.Reserved );
			}
			if( type == 197 )
			{
				pMsg->NspChangeCount.Type = (UINT16)type;
				BM_ReportBsInfo_List_CURRENT_NspChangeCount_NspChangeCount_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NspChangeCount.NspChangeCount );
				BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved1_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NspChangeCount.Reserved1 );
				BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NspChangeCount.Reserved2 );
			}

			BM_ReportBsInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportBsInfo(UINT8* pBuf, ReportBsInfo_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_ReportBsInfo_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.BSID.Type == 196 )
	{
		BM_ReportBsInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 196 );
		length = 8;
		BM_ReportBsInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_ReportBsInfo_List_CURRENT_BSID_FullBSID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.BSID.FullBSID[i0].value );
		}
		BM_ReportBsInfo_List_CURRENT_BSID_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.BSID.Reserved );
		BM_ReportBsInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.NspChangeCount.Type == 197 )
	{
		BM_ReportBsInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 197 );
		length = 4;
		BM_ReportBsInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportBsInfo_List_CURRENT_NspChangeCount_NspChangeCount_SET( base_ptr, cur_ptr, cur_bitoff, msg.NspChangeCount.NspChangeCount );
		BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved1_SET( base_ptr, cur_ptr, cur_bitoff, msg.NspChangeCount.Reserved1 );
		BM_ReportBsInfo_List_CURRENT_NspChangeCount_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.NspChangeCount.Reserved2 );
		BM_ReportBsInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ReportBsInfo_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_BS_INFO );
	BM_ReportBsInfo_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportBsInfo_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportBsInfo_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportBsInfo_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportBsInfo(UINT8* pBuf, ReportBsInfo_type* msg)
{
	return L4BM_Set_ReportBsInfo(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportBsInfo(ReportBsInfo_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.BSID.Type == 196 )
	{
		length += 8;
		length += 4;
	}
	if( msg.NspChangeCount.Type == 197 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportBsInfo(ReportBsInfo_type* msg)
{
	return L4BM_GetBufferSize_ReportBsInfo(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportBsInfo( void )
{
	UINT32 length = HEADER_SIZE;

	length += 8;
	length += 4;
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_ReportBsInfo(ReportBsInfo_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->BSID.Type = INVALID_OPCODE;
	pMsg->NspChangeCount.Type = INVALID_OPCODE;

}
L4bufman_Funcs ReportBsInfo_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportBsInfo,
	(pf_SetL4Command)L4BM_generic_Set_ReportBsInfo,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportBsInfo,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportBsInfo,
	(pf_InitL4Command)L4BM_Init_ReportBsInfo
};



//
// SetEapFail
//
L4BUFMAN_Status_t L4BM_Get_SetEapFail(SetEapFail_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_SetEapFail_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SetEapFail_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SetEapFail_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SetEapFail(UINT8* pBuf, SetEapFail_type msg)
{
	PVOID base_ptr = pBuf;

	SetEapFail_type tmp = msg;
	tmp = tmp;

	BM_SetEapFail_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_EAP_FAIL );
	BM_SetEapFail_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SetEapFail_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SetEapFail_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SetEapFail_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SetEapFail(UINT8* pBuf, SetEapFail_type* msg)
{
	return L4BM_Set_SetEapFail(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SetEapFail(SetEapFail_type msg)
{

	SetEapFail_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_SetEapFail(SetEapFail_type* msg)
{
	return L4BM_GetBufferSize_SetEapFail(*msg);
}
UINT L4BM_GetMaxBufferSize_SetEapFail( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_SetEapFail(SetEapFail_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs SetEapFail_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SetEapFail,
	(pf_SetL4Command)L4BM_generic_Set_SetEapFail,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SetEapFail,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SetEapFail,
	(pf_InitL4Command)L4BM_Init_SetEapFail
};



//
// MOC_Response
//
L4BUFMAN_Status_t L4BM_Get_MOC_Response(MOC_Response_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_MOC_Response_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_MOC_Response_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_MOC_Response_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_MOC_Response(UINT8* pBuf, MOC_Response_type msg)
{
	PVOID base_ptr = pBuf;

	MOC_Response_type tmp = msg;
	tmp = tmp;

	BM_MOC_Response_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_MOC_RESPONSE );
	BM_MOC_Response_Header_Version_SET( base_ptr, msg.header.Version );
	BM_MOC_Response_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_MOC_Response_Header_Status_SET( base_ptr, msg.header.Status );
	BM_MOC_Response_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_MOC_Response(UINT8* pBuf, MOC_Response_type* msg)
{
	return L4BM_Set_MOC_Response(pBuf, *msg);
}
UINT L4BM_GetBufferSize_MOC_Response(MOC_Response_type msg)
{

	MOC_Response_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_MOC_Response(MOC_Response_type* msg)
{
	return L4BM_GetBufferSize_MOC_Response(*msg);
}
UINT L4BM_GetMaxBufferSize_MOC_Response( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_MOC_Response(MOC_Response_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs MOC_Response_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_MOC_Response,
	(pf_SetL4Command)L4BM_generic_Set_MOC_Response,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_MOC_Response,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_MOC_Response,
	(pf_InitL4Command)L4BM_Init_MOC_Response
};



//
// GetStatistics
//
L4BUFMAN_Status_t L4BM_Get_GetStatistics(GetStatistics_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_GetStatistics(pMsg);
	BM_GetStatistics_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetStatistics_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetStatistics_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetStatistics_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetStatistics_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetStatistics_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetStatistics_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 142 )
			{
				pMsg->TimeStamp.Type = (UINT16)type;
				BM_GetStatistics_List_CURRENT_TimeStamp_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->TimeStamp.value );
			}
			if( type == 170 )
			{
				pMsg->StatisticsCommon.Type = (UINT16)type;
				BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxBytes_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->StatisticsCommon.TotalRxBytes );
				BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxBytes_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->StatisticsCommon.TotalTxBytes );
				BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxPackets_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->StatisticsCommon.TotalRxPackets );
				BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxPackets_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->StatisticsCommon.TotalTxPackets );
			}

			BM_GetStatistics_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetStatistics(UINT8* pBuf, GetStatistics_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_GetStatistics_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.TimeStamp.Type == 142 )
	{
		BM_GetStatistics_List_SET_TYPE( cur_ptr, cur_bitoff, 142 );
		length = 4;
		BM_GetStatistics_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetStatistics_List_CURRENT_TimeStamp_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.TimeStamp.value );
		BM_GetStatistics_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.StatisticsCommon.Type == 170 )
	{
		BM_GetStatistics_List_SET_TYPE( cur_ptr, cur_bitoff, 170 );
		length = 16;
		BM_GetStatistics_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxBytes_SET( base_ptr, cur_ptr, cur_bitoff, msg.StatisticsCommon.TotalRxBytes );
		BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxBytes_SET( base_ptr, cur_ptr, cur_bitoff, msg.StatisticsCommon.TotalTxBytes );
		BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalRxPackets_SET( base_ptr, cur_ptr, cur_bitoff, msg.StatisticsCommon.TotalRxPackets );
		BM_GetStatistics_List_CURRENT_StatisticsCommon_TotalTxPackets_SET( base_ptr, cur_ptr, cur_bitoff, msg.StatisticsCommon.TotalTxPackets );
		BM_GetStatistics_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetStatistics_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_STATISTICS );
	BM_GetStatistics_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetStatistics_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetStatistics_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetStatistics_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetStatistics(UINT8* pBuf, GetStatistics_type* msg)
{
	return L4BM_Set_GetStatistics(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetStatistics(GetStatistics_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.TimeStamp.Type == 142 )
	{
		length += 4;
		length += 4;
	}
	if( msg.StatisticsCommon.Type == 170 )
	{
		length += 16;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetStatistics(GetStatistics_type* msg)
{
	return L4BM_GetBufferSize_GetStatistics(*msg);
}
UINT L4BM_GetMaxBufferSize_GetStatistics( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += 16;
	length += 4;

	return length;
}
void L4BM_Init_GetStatistics(GetStatistics_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->TimeStamp.Type = INVALID_OPCODE;
	pMsg->StatisticsCommon.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetStatistics_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetStatistics,
	(pf_SetL4Command)L4BM_generic_Set_GetStatistics,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetStatistics,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetStatistics,
	(pf_InitL4Command)L4BM_Init_GetStatistics
};



//
// GetDeviceInfo
//
L4BUFMAN_Status_t L4BM_Get_GetDeviceInfo(GetDeviceInfo_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_GetDeviceInfo(pMsg);
	BM_GetDeviceInfo_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetDeviceInfo_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetDeviceInfo_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetDeviceInfo_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetDeviceInfo_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetDeviceInfo_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetDeviceInfo_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 130 )
			{
				pMsg->VersionsStrings.Type = (UINT16)type;
				BM_GetDeviceInfo_List_CURRENT_VersionsStrings_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->VersionsStrings.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->VersionsStrings.ActualLen; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_VersionsStrings_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->VersionsStrings.BufferArr[i0].value );
				}
			}
			if( type == 140 )
			{
				pMsg->DeviceDetails.Type = (UINT16)type;
				BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelType_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DeviceDetails.ModelType );
				BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeStringLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DeviceDetails.ModelTypeStringLength );
				for( i0 = 0; i0 < 124; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->DeviceDetails.ModelTypeString[i0].value );
				}
				BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DeviceDetails.ManufacturerId );
				BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdStringLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DeviceDetails.ManufacturerIdStringLength );
				for( i0 = 0; i0 < 124; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->DeviceDetails.ManufacturerIdString[i0].value );
				}
				BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductStringLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DeviceDetails.NvmProductStringLength );
				for( i0 = 0; i0 < 124; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->DeviceDetails.NvmProductString[i0].value );
				}
				for( i0 = 0; i0 < 8; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Nonce_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->DeviceDetails.Nonce[i0].value );
				}
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->DeviceDetails.MacAddress[i0].value );
				}
				BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Reserved2_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DeviceDetails.Reserved2 );
			}
			if( type == 138 )
			{
				pMsg->OdmInformation.Type = (UINT16)type;
				for( i0 = 0; i0 < 108; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_OdmInformation_OdmInformation_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->OdmInformation.OdmInformation[i0].value );
				}
			}
			if( type == 139 )
			{
				pMsg->NvmInformation.Type = (UINT16)type;
				BM_GetDeviceInfo_List_CURRENT_NvmInformation_GeneralImageVersion_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NvmInformation.GeneralImageVersion );
				BM_GetDeviceInfo_List_CURRENT_NvmInformation_ContentVersion_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NvmInformation.ContentVersion );
			}
			if( type == 137 )
			{
				pMsg->NvmManufacturer.Type = (UINT16)type;
				BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdStringLength_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->NvmManufacturer.NvmManufacturerIdStringLength );
				for( i0 = 0; i0 < 124; i0++ )
				{
					BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdString_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->NvmManufacturer.NvmManufacturerIdString[i0].value );
				}
			}
			if( type == 145 )
			{
				pMsg->DevicePID.Type = (UINT16)type;
				BM_GetDeviceInfo_List_CURRENT_DevicePID_PID_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->DevicePID.PID );
			}

			BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetDeviceInfo(UINT8* pBuf, GetDeviceInfo_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_GetDeviceInfo_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.VersionsStrings.Type == 130 )
	{
		BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 130 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.VersionsStrings.ActualLen + 2);
		BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetDeviceInfo_List_CURRENT_VersionsStrings_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.VersionsStrings.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.VersionsStrings.ActualLen; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_VersionsStrings_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.VersionsStrings.BufferArr[i0].value );
		}
		BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.DeviceDetails.Type == 140 )
	{
		BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 140 );
		length = 408;
		BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelType_SET( base_ptr, cur_ptr, cur_bitoff, msg.DeviceDetails.ModelType );
		BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeStringLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.DeviceDetails.ModelTypeStringLength );
		for( i0 = 0; i0 < 124; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ModelTypeString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.DeviceDetails.ModelTypeString[i0].value );
		}
		BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerId_SET( base_ptr, cur_ptr, cur_bitoff, msg.DeviceDetails.ManufacturerId );
		BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdStringLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.DeviceDetails.ManufacturerIdStringLength );
		for( i0 = 0; i0 < 124; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_DeviceDetails_ManufacturerIdString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.DeviceDetails.ManufacturerIdString[i0].value );
		}
		BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductStringLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.DeviceDetails.NvmProductStringLength );
		for( i0 = 0; i0 < 124; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_DeviceDetails_NvmProductString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.DeviceDetails.NvmProductString[i0].value );
		}
		for( i0 = 0; i0 < 8; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Nonce_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.DeviceDetails.Nonce[i0].value );
		}
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_DeviceDetails_MacAddress_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.DeviceDetails.MacAddress[i0].value );
		}
		BM_GetDeviceInfo_List_CURRENT_DeviceDetails_Reserved2_SET( base_ptr, cur_ptr, cur_bitoff, msg.DeviceDetails.Reserved2 );
		BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.OdmInformation.Type == 138 )
	{
		BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 138 );
		length = 108;
		BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 108; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_OdmInformation_OdmInformation_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.OdmInformation.OdmInformation[i0].value );
		}
		BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.NvmInformation.Type == 139 )
	{
		BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 139 );
		length = 4;
		BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetDeviceInfo_List_CURRENT_NvmInformation_GeneralImageVersion_SET( base_ptr, cur_ptr, cur_bitoff, msg.NvmInformation.GeneralImageVersion );
		BM_GetDeviceInfo_List_CURRENT_NvmInformation_ContentVersion_SET( base_ptr, cur_ptr, cur_bitoff, msg.NvmInformation.ContentVersion );
		BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.NvmManufacturer.Type == 137 )
	{
		BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 137 );
		length = 128;
		BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdStringLength_SET( base_ptr, cur_ptr, cur_bitoff, msg.NvmManufacturer.NvmManufacturerIdStringLength );
		for( i0 = 0; i0 < 124; i0++ )
		{
			BM_GetDeviceInfo_List_CURRENT_NvmManufacturer_NvmManufacturerIdString_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.NvmManufacturer.NvmManufacturerIdString[i0].value );
		}
		BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.DevicePID.Type == 145 )
	{
		BM_GetDeviceInfo_List_SET_TYPE( cur_ptr, cur_bitoff, 145 );
		length = 4;
		BM_GetDeviceInfo_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_GetDeviceInfo_List_CURRENT_DevicePID_PID_SET( base_ptr, cur_ptr, cur_bitoff, msg.DevicePID.PID );
		BM_GetDeviceInfo_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetDeviceInfo_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_DEVICE_INFO );
	BM_GetDeviceInfo_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetDeviceInfo_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetDeviceInfo_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetDeviceInfo_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetDeviceInfo(UINT8* pBuf, GetDeviceInfo_type* msg)
{
	return L4BM_Set_GetDeviceInfo(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetDeviceInfo(GetDeviceInfo_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.VersionsStrings.Type == 130 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.VersionsStrings.ActualLen + 2);
		length += 4;
	}
	if( msg.DeviceDetails.Type == 140 )
	{
		length += 408;
		length += 4;
	}
	if( msg.OdmInformation.Type == 138 )
	{
		length += 108;
		length += 4;
	}
	if( msg.NvmInformation.Type == 139 )
	{
		length += 4;
		length += 4;
	}
	if( msg.NvmManufacturer.Type == 137 )
	{
		length += 128;
		length += 4;
	}
	if( msg.DevicePID.Type == 145 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetDeviceInfo(GetDeviceInfo_type* msg)
{
	return L4BM_GetBufferSize_GetDeviceInfo(*msg);
}
UINT L4BM_GetMaxBufferSize_GetDeviceInfo( void )
{
	UINT32 length = HEADER_SIZE;

	length += L4BM_RoundUp4Bytes((UINT32)100 + 2);
	length += 4;
	length += 408;
	length += 4;
	length += 108;
	length += 4;
	length += 4;
	length += 4;
	length += 128;
	length += 4;
	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_GetDeviceInfo(GetDeviceInfo_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->VersionsStrings.Type = INVALID_OPCODE;
	pMsg->DeviceDetails.Type = INVALID_OPCODE;
	pMsg->OdmInformation.Type = INVALID_OPCODE;
	pMsg->NvmInformation.Type = INVALID_OPCODE;
	pMsg->NvmManufacturer.Type = INVALID_OPCODE;
	pMsg->DevicePID.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetDeviceInfo_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetDeviceInfo,
	(pf_SetL4Command)L4BM_generic_Set_GetDeviceInfo,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetDeviceInfo,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetDeviceInfo,
	(pf_InitL4Command)L4BM_Init_GetDeviceInfo
};



//
// CmdMonitorControl
//
L4BUFMAN_Status_t L4BM_Get_CmdMonitorControl(CmdMonitorControl_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_CmdMonitorControl(pMsg);
	BM_CmdMonitorControl_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CmdMonitorControl_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CmdMonitorControl_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_CmdMonitorControl_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_CmdMonitorControl_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_CmdMonitorControl_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_CmdMonitorControl_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 4002 )
			{
				pMsg->MonitorMode.Type = (UINT16)type;
				BM_CmdMonitorControl_List_CURRENT_MonitorMode_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->MonitorMode.value );
			}

			BM_CmdMonitorControl_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CmdMonitorControl(UINT8* pBuf, CmdMonitorControl_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_CmdMonitorControl_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.MonitorMode.Type == 4002 )
	{
		BM_CmdMonitorControl_List_SET_TYPE( cur_ptr, cur_bitoff, 4002 );
		length = 4;
		BM_CmdMonitorControl_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_CmdMonitorControl_List_CURRENT_MonitorMode_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.MonitorMode.value );
		BM_CmdMonitorControl_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_CmdMonitorControl_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_MONITOR_CONTROL );
	BM_CmdMonitorControl_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CmdMonitorControl_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CmdMonitorControl_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CmdMonitorControl_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CmdMonitorControl(UINT8* pBuf, CmdMonitorControl_type* msg)
{
	return L4BM_Set_CmdMonitorControl(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CmdMonitorControl(CmdMonitorControl_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.MonitorMode.Type == 4002 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_CmdMonitorControl(CmdMonitorControl_type* msg)
{
	return L4BM_GetBufferSize_CmdMonitorControl(*msg);
}
UINT L4BM_GetMaxBufferSize_CmdMonitorControl( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_CmdMonitorControl(CmdMonitorControl_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->MonitorMode.Type = INVALID_OPCODE;

}
L4bufman_Funcs CmdMonitorControl_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CmdMonitorControl,
	(pf_SetL4Command)L4BM_generic_Set_CmdMonitorControl,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CmdMonitorControl,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CmdMonitorControl,
	(pf_InitL4Command)L4BM_Init_CmdMonitorControl
};



//
// CheckL3L4InterfaceREPORT
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_CheckL3L4InterfaceREPORT(pMsg);
	BM_CheckL3L4InterfaceREPORT_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CheckL3L4InterfaceREPORT_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CheckL3L4InterfaceREPORT_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_CheckL3L4InterfaceREPORT_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_CheckL3L4InterfaceREPORT_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_CheckL3L4InterfaceREPORT_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_CheckL3L4InterfaceREPORT_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 2049 )
			{
				pMsg->value.Type = (UINT16)type;
				BM_CheckL3L4InterfaceREPORT_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->value.value );
			}

			BM_CheckL3L4InterfaceREPORT_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceREPORT(UINT8* pBuf, CheckL3L4InterfaceREPORT_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_CheckL3L4InterfaceREPORT_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.value.Type == 2049 )
	{
		BM_CheckL3L4InterfaceREPORT_List_SET_TYPE( cur_ptr, cur_bitoff, 2049 );
		length = 4;
		BM_CheckL3L4InterfaceREPORT_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_CheckL3L4InterfaceREPORT_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.value.value );
		BM_CheckL3L4InterfaceREPORT_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_CheckL3L4InterfaceREPORT_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_CHECK_INTERFACE );
	BM_CheckL3L4InterfaceREPORT_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CheckL3L4InterfaceREPORT_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CheckL3L4InterfaceREPORT_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CheckL3L4InterfaceREPORT_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CheckL3L4InterfaceREPORT(UINT8* pBuf, CheckL3L4InterfaceREPORT_type* msg)
{
	return L4BM_Set_CheckL3L4InterfaceREPORT(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.value.Type == 2049 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type* msg)
{
	return L4BM_GetBufferSize_CheckL3L4InterfaceREPORT(*msg);
}
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceREPORT( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_CheckL3L4InterfaceREPORT(CheckL3L4InterfaceREPORT_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->value.Type = INVALID_OPCODE;

}
L4bufman_Funcs CheckL3L4InterfaceREPORT_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CheckL3L4InterfaceREPORT,
	(pf_SetL4Command)L4BM_generic_Set_CheckL3L4InterfaceREPORT,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CheckL3L4InterfaceREPORT,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CheckL3L4InterfaceREPORT,
	(pf_InitL4Command)L4BM_Init_CheckL3L4InterfaceREPORT
};



//
// GetMonitorFilterTable
//
L4BUFMAN_Status_t L4BM_Get_GetMonitorFilterTable(GetMonitorFilterTable_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_GetMonitorFilterTable(pMsg);
	BM_GetMonitorFilterTable_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetMonitorFilterTable_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetMonitorFilterTable_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetMonitorFilterTable_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetMonitorFilterTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetMonitorFilterTable_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetMonitorFilterTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 4003 )
			{
				pMsg->MonitorFilterTable.Type = (UINT16)type;
				for( i0 = 0; i0 < 256; i0++ )
				{
					BM_GetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->MonitorFilterTable.FilterTable[i0].value );
				}
			}

			BM_GetMonitorFilterTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetMonitorFilterTable(UINT8* pBuf, GetMonitorFilterTable_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_GetMonitorFilterTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.MonitorFilterTable.Type == 4003 )
	{
		BM_GetMonitorFilterTable_List_SET_TYPE( cur_ptr, cur_bitoff, 4003 );
		length = 256;
		BM_GetMonitorFilterTable_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 256; i0++ )
		{
			BM_GetMonitorFilterTable_List_CURRENT_MonitorFilterTable_FilterTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.MonitorFilterTable.FilterTable[i0].value );
		}
		BM_GetMonitorFilterTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetMonitorFilterTable_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_MONITOR_FILTER_TABLE );
	BM_GetMonitorFilterTable_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetMonitorFilterTable_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetMonitorFilterTable_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetMonitorFilterTable_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetMonitorFilterTable(UINT8* pBuf, GetMonitorFilterTable_type* msg)
{
	return L4BM_Set_GetMonitorFilterTable(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetMonitorFilterTable(GetMonitorFilterTable_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.MonitorFilterTable.Type == 4003 )
	{
		length += 256;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetMonitorFilterTable(GetMonitorFilterTable_type* msg)
{
	return L4BM_GetBufferSize_GetMonitorFilterTable(*msg);
}
UINT L4BM_GetMaxBufferSize_GetMonitorFilterTable( void )
{
	UINT32 length = HEADER_SIZE;

	length += 256;
	length += 4;

	return length;
}
void L4BM_Init_GetMonitorFilterTable(GetMonitorFilterTable_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->MonitorFilterTable.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetMonitorFilterTable_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetMonitorFilterTable,
	(pf_SetL4Command)L4BM_generic_Set_GetMonitorFilterTable,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetMonitorFilterTable,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetMonitorFilterTable,
	(pf_InitL4Command)L4BM_Init_GetMonitorFilterTable
};



//
// GetTraceSeverityTable
//
L4BUFMAN_Status_t L4BM_Get_GetTraceSeverityTable(GetTraceSeverityTable_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_GetTraceSeverityTable(pMsg);
	BM_GetTraceSeverityTable_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_GetTraceSeverityTable_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_GetTraceSeverityTable_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_GetTraceSeverityTable_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_GetTraceSeverityTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_GetTraceSeverityTable_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_GetTraceSeverityTable_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 4001 )
			{
				pMsg->TraceSeverityTable.Type = (UINT16)type;
				for( i0 = 0; i0 < 256; i0++ )
				{
					BM_GetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->TraceSeverityTable.SeverityTable[i0].value );
				}
			}

			BM_GetTraceSeverityTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_GetTraceSeverityTable(UINT8* pBuf, GetTraceSeverityTable_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_GetTraceSeverityTable_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.TraceSeverityTable.Type == 4001 )
	{
		BM_GetTraceSeverityTable_List_SET_TYPE( cur_ptr, cur_bitoff, 4001 );
		length = 256;
		BM_GetTraceSeverityTable_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		for( i0 = 0; i0 < 256; i0++ )
		{
			BM_GetTraceSeverityTable_List_CURRENT_TraceSeverityTable_SeverityTable_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.TraceSeverityTable.SeverityTable[i0].value );
		}
		BM_GetTraceSeverityTable_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_GetTraceSeverityTable_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_TRACE_SEVERITY_TABLE );
	BM_GetTraceSeverityTable_Header_Version_SET( base_ptr, msg.header.Version );
	BM_GetTraceSeverityTable_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_GetTraceSeverityTable_Header_Status_SET( base_ptr, msg.header.Status );
	BM_GetTraceSeverityTable_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_GetTraceSeverityTable(UINT8* pBuf, GetTraceSeverityTable_type* msg)
{
	return L4BM_Set_GetTraceSeverityTable(pBuf, *msg);
}
UINT L4BM_GetBufferSize_GetTraceSeverityTable(GetTraceSeverityTable_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.TraceSeverityTable.Type == 4001 )
	{
		length += 256;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_GetTraceSeverityTable(GetTraceSeverityTable_type* msg)
{
	return L4BM_GetBufferSize_GetTraceSeverityTable(*msg);
}
UINT L4BM_GetMaxBufferSize_GetTraceSeverityTable( void )
{
	UINT32 length = HEADER_SIZE;

	length += 256;
	length += 4;

	return length;
}
void L4BM_Init_GetTraceSeverityTable(GetTraceSeverityTable_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->TraceSeverityTable.Type = INVALID_OPCODE;

}
L4bufman_Funcs GetTraceSeverityTable_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_GetTraceSeverityTable,
	(pf_SetL4Command)L4BM_generic_Set_GetTraceSeverityTable,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_GetTraceSeverityTable,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_GetTraceSeverityTable,
	(pf_InitL4Command)L4BM_Init_GetTraceSeverityTable
};



//
// ResetDeviceCommand
//
L4BUFMAN_Status_t L4BM_Get_ResetDeviceCommand(ResetDeviceCommand_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_ResetDeviceCommand(pMsg);
	BM_ResetDeviceCommand_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ResetDeviceCommand_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ResetDeviceCommand_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ResetDeviceCommand_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ResetDeviceCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ResetDeviceCommand_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ResetDeviceCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 132 )
			{
				pMsg->ResetDevice.Type = (UINT16)type;
				BM_ResetDeviceCommand_List_CURRENT_ResetDevice_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ResetDevice.value );
			}

			BM_ResetDeviceCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ResetDeviceCommand(UINT8* pBuf, ResetDeviceCommand_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_ResetDeviceCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.ResetDevice.Type == 132 )
	{
		BM_ResetDeviceCommand_List_SET_TYPE( cur_ptr, cur_bitoff, 132 );
		length = 4;
		BM_ResetDeviceCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ResetDeviceCommand_List_CURRENT_ResetDevice_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ResetDevice.value );
		BM_ResetDeviceCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ResetDeviceCommand_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_RESET_DEVICE );
	BM_ResetDeviceCommand_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ResetDeviceCommand_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ResetDeviceCommand_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ResetDeviceCommand_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ResetDeviceCommand(UINT8* pBuf, ResetDeviceCommand_type* msg)
{
	return L4BM_Set_ResetDeviceCommand(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ResetDeviceCommand(ResetDeviceCommand_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.ResetDevice.Type == 132 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ResetDeviceCommand(ResetDeviceCommand_type* msg)
{
	return L4BM_GetBufferSize_ResetDeviceCommand(*msg);
}
UINT L4BM_GetMaxBufferSize_ResetDeviceCommand( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_ResetDeviceCommand(ResetDeviceCommand_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->ResetDevice.Type = INVALID_OPCODE;

}
L4bufman_Funcs ResetDeviceCommand_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ResetDeviceCommand,
	(pf_SetL4Command)L4BM_generic_Set_ResetDeviceCommand,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ResetDeviceCommand,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ResetDeviceCommand,
	(pf_InitL4Command)L4BM_Init_ResetDeviceCommand
};



//
// CheckL3L4InterfaceCMD
//
L4BUFMAN_Status_t L4BM_Get_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_CheckL3L4InterfaceCMD(pMsg);
	BM_CheckL3L4InterfaceCMD_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_CheckL3L4InterfaceCMD_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_CheckL3L4InterfaceCMD_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_CheckL3L4InterfaceCMD_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_CheckL3L4InterfaceCMD_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_CheckL3L4InterfaceCMD_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_CheckL3L4InterfaceCMD_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 2048 )
			{
				pMsg->value.Type = (UINT16)type;
				BM_CheckL3L4InterfaceCMD_List_CURRENT_value_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->value.value );
			}

			BM_CheckL3L4InterfaceCMD_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_CheckL3L4InterfaceCMD(UINT8* pBuf, CheckL3L4InterfaceCMD_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_CheckL3L4InterfaceCMD_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.value.Type == 2048 )
	{
		BM_CheckL3L4InterfaceCMD_List_SET_TYPE( cur_ptr, cur_bitoff, 2048 );
		length = 4;
		BM_CheckL3L4InterfaceCMD_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_CheckL3L4InterfaceCMD_List_CURRENT_value_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.value.value );
		BM_CheckL3L4InterfaceCMD_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_CheckL3L4InterfaceCMD_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_CHECK_INTERFACE );
	BM_CheckL3L4InterfaceCMD_Header_Version_SET( base_ptr, msg.header.Version );
	BM_CheckL3L4InterfaceCMD_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_CheckL3L4InterfaceCMD_Header_Status_SET( base_ptr, msg.header.Status );
	BM_CheckL3L4InterfaceCMD_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_CheckL3L4InterfaceCMD(UINT8* pBuf, CheckL3L4InterfaceCMD_type* msg)
{
	return L4BM_Set_CheckL3L4InterfaceCMD(pBuf, *msg);
}
UINT L4BM_GetBufferSize_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.value.Type == 2048 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type* msg)
{
	return L4BM_GetBufferSize_CheckL3L4InterfaceCMD(*msg);
}
UINT L4BM_GetMaxBufferSize_CheckL3L4InterfaceCMD( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_CheckL3L4InterfaceCMD(CheckL3L4InterfaceCMD_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->value.Type = INVALID_OPCODE;

}
L4bufman_Funcs CheckL3L4InterfaceCMD_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_CheckL3L4InterfaceCMD,
	(pf_SetL4Command)L4BM_generic_Set_CheckL3L4InterfaceCMD,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_CheckL3L4InterfaceCMD,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_CheckL3L4InterfaceCMD,
	(pf_InitL4Command)L4BM_Init_CheckL3L4InterfaceCMD
};



//
// ReportState
//
L4BUFMAN_Status_t L4BM_Get_ReportState(ReportState_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_ReportState(pMsg);
	BM_ReportState_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportState_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportState_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ReportState_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ReportState_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ReportState_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ReportState_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 150 )
			{
				pMsg->ReportStateReason.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_ReportStateReason_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ReportStateReason.value );
			}
			if( type == 141 )
			{
				pMsg->SystemState.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_SystemState_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SystemState.value );
			}
			if( type == 160 )
			{
				pMsg->LinkStatus.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_LinkStatus_UpLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.UpLinkSpeed );
				BM_ReportState_List_CURRENT_LinkStatus_DownLinkSpeed_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.DownLinkSpeed );
				BM_ReportState_List_CURRENT_LinkStatus_CenterFrequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.CenterFrequency );
				BM_ReportState_List_CURRENT_LinkStatus_TxPower_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.TxPower );
				BM_ReportState_List_CURRENT_LinkStatus_RxRssi_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.RxRssi );
				BM_ReportState_List_CURRENT_LinkStatus_RxCinr_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.RxCinr );
				for( i0 = 0; i0 < 6; i0++ )
				{
					BM_ReportState_List_CURRENT_LinkStatus_BSID_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->LinkStatus.BSID[i0].value );
				}
				BM_ReportState_List_CURRENT_LinkStatus_LinkQuality_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.LinkQuality );
				BM_ReportState_List_CURRENT_LinkStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->LinkStatus.Reserved );
			}
			if( type == 161 )
			{
				pMsg->MediaStatus.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_MediaStatus_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->MediaStatus.value );
			}
			if( type == 191 )
			{
				pMsg->ConnectProgress.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_ConnectProgress_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ConnectProgress.value );
			}
			if( type == 163 )
			{
				pMsg->RFStatus.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_RFStatus_SwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RFStatus.SwRFSwitch );
				BM_ReportState_List_CURRENT_RFStatus_HwRFSwitch_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RFStatus.HwRFSwitch );
				BM_ReportState_List_CURRENT_RFStatus_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->RFStatus.Reserved );
			}
			if( type == 181 )
			{
				pMsg->ChannelInfo.Type = (UINT16)type;
				BM_ReportState_List_CURRENT_ChannelInfo_Frequency_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Frequency );
				BM_ReportState_List_CURRENT_ChannelInfo_ChannelId_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.ChannelId );
				BM_ReportState_List_CURRENT_ChannelInfo_Bandwidth_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Bandwidth );
				BM_ReportState_List_CURRENT_ChannelInfo_Fft_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Fft );
				for( i0 = 0; i0 < 15; i0++ )
				{
					BM_ReportState_List_CURRENT_ChannelInfo_Preambles_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Preambles[i0].value );
				}
				BM_ReportState_List_CURRENT_ChannelInfo_Reserved_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ChannelInfo.Reserved );
			}

			BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportState(UINT8* pBuf, ReportState_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_ReportState_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.ReportStateReason.Type == 150 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 150 );
		length = 4;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_ReportStateReason_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ReportStateReason.value );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.SystemState.Type == 141 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 141 );
		length = 4;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_SystemState_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.SystemState.value );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.LinkStatus.Type == 160 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 160 );
		length = 24;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_LinkStatus_UpLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.UpLinkSpeed );
		BM_ReportState_List_CURRENT_LinkStatus_DownLinkSpeed_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.DownLinkSpeed );
		BM_ReportState_List_CURRENT_LinkStatus_CenterFrequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.CenterFrequency );
		BM_ReportState_List_CURRENT_LinkStatus_TxPower_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.TxPower );
		BM_ReportState_List_CURRENT_LinkStatus_RxRssi_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.RxRssi );
		BM_ReportState_List_CURRENT_LinkStatus_RxCinr_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.RxCinr );
		for( i0 = 0; i0 < 6; i0++ )
		{
			BM_ReportState_List_CURRENT_LinkStatus_BSID_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.LinkStatus.BSID[i0].value );
		}
		BM_ReportState_List_CURRENT_LinkStatus_LinkQuality_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.LinkQuality );
		BM_ReportState_List_CURRENT_LinkStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.LinkStatus.Reserved );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.MediaStatus.Type == 161 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 161 );
		length = 4;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_MediaStatus_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.MediaStatus.value );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ConnectProgress.Type == 191 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 191 );
		length = 4;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_ConnectProgress_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ConnectProgress.value );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.RFStatus.Type == 163 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 163 );
		length = 4;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_RFStatus_SwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.RFStatus.SwRFSwitch );
		BM_ReportState_List_CURRENT_RFStatus_HwRFSwitch_SET( base_ptr, cur_ptr, cur_bitoff, msg.RFStatus.HwRFSwitch );
		BM_ReportState_List_CURRENT_RFStatus_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.RFStatus.Reserved );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}
	if( msg.ChannelInfo.Type == 181 )
	{
		BM_ReportState_List_SET_TYPE( cur_ptr, cur_bitoff, 181 );
		length = 24;
		BM_ReportState_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ReportState_List_CURRENT_ChannelInfo_Frequency_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Frequency );
		BM_ReportState_List_CURRENT_ChannelInfo_ChannelId_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.ChannelId );
		BM_ReportState_List_CURRENT_ChannelInfo_Bandwidth_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Bandwidth );
		BM_ReportState_List_CURRENT_ChannelInfo_Fft_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Fft );
		for( i0 = 0; i0 < 15; i0++ )
		{
			BM_ReportState_List_CURRENT_ChannelInfo_Preambles_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.ChannelInfo.Preambles[i0].value );
		}
		BM_ReportState_List_CURRENT_ChannelInfo_Reserved_SET( base_ptr, cur_ptr, cur_bitoff, msg.ChannelInfo.Reserved );
		BM_ReportState_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ReportState_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_STATE );
	BM_ReportState_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportState_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportState_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportState_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportState(UINT8* pBuf, ReportState_type* msg)
{
	return L4BM_Set_ReportState(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportState(ReportState_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.ReportStateReason.Type == 150 )
	{
		length += 4;
		length += 4;
	}
	if( msg.SystemState.Type == 141 )
	{
		length += 4;
		length += 4;
	}
	if( msg.LinkStatus.Type == 160 )
	{
		length += 24;
		length += 4;
	}
	if( msg.MediaStatus.Type == 161 )
	{
		length += 4;
		length += 4;
	}
	if( msg.ConnectProgress.Type == 191 )
	{
		length += 4;
		length += 4;
	}
	if( msg.RFStatus.Type == 163 )
	{
		length += 4;
		length += 4;
	}
	if( msg.ChannelInfo.Type == 181 )
	{
		length += 24;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ReportState(ReportState_type* msg)
{
	return L4BM_GetBufferSize_ReportState(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportState( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 24;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 4;
	length += 24;
	length += 4;

	return length;
}
void L4BM_Init_ReportState(ReportState_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->ReportStateReason.Type = INVALID_OPCODE;
	pMsg->SystemState.Type = INVALID_OPCODE;
	pMsg->LinkStatus.Type = INVALID_OPCODE;
	pMsg->MediaStatus.Type = INVALID_OPCODE;
	pMsg->ConnectProgress.Type = INVALID_OPCODE;
	pMsg->RFStatus.Type = INVALID_OPCODE;
	pMsg->ChannelInfo.Type = INVALID_OPCODE;

}
L4bufman_Funcs ReportState_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportState,
	(pf_SetL4Command)L4BM_generic_Set_ReportState,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportState,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportState,
	(pf_InitL4Command)L4BM_Init_ReportState
};



//
// SPLockRequest
//
L4BUFMAN_Status_t L4BM_Get_SPLockRequest(SPLockRequest_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SPLockRequest(pMsg);
	BM_SPLockRequest_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SPLockRequest_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SPLockRequest_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SPLockRequest_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SPLockRequest_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SPLockRequest_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SPLockRequest_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1066 )
			{
				pMsg->SPLockUnlockCodeReq.Type = (UINT16)type;
				BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->SPLockUnlockCodeReq.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->SPLockUnlockCodeReq.ActualLen; i0++ )
				{
					BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->SPLockUnlockCodeReq.BufferArr[i0].value );
				}
			}

			BM_SPLockRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SPLockRequest(UINT8* pBuf, SPLockRequest_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SPLockRequest_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.SPLockUnlockCodeReq.Type == 1066 )
	{
		BM_SPLockRequest_List_SET_TYPE( cur_ptr, cur_bitoff, 1066 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.SPLockUnlockCodeReq.ActualLen + 2);
		BM_SPLockRequest_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.SPLockUnlockCodeReq.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.SPLockUnlockCodeReq.ActualLen; i0++ )
		{
			BM_SPLockRequest_List_CURRENT_SPLockUnlockCodeReq_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.SPLockUnlockCodeReq.BufferArr[i0].value );
		}
		BM_SPLockRequest_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SPLockRequest_Header_Type_SET( base_ptr, L4_L3_OPCODE_SET_SPLOCK_UNLOCK_CODE );
	BM_SPLockRequest_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SPLockRequest_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SPLockRequest_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SPLockRequest_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SPLockRequest(UINT8* pBuf, SPLockRequest_type* msg)
{
	return L4BM_Set_SPLockRequest(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SPLockRequest(SPLockRequest_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.SPLockUnlockCodeReq.Type == 1066 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.SPLockUnlockCodeReq.ActualLen + 2);
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SPLockRequest(SPLockRequest_type* msg)
{
	return L4BM_GetBufferSize_SPLockRequest(*msg);
}
UINT L4BM_GetMaxBufferSize_SPLockRequest( void )
{
	UINT32 length = HEADER_SIZE;

	length += L4BM_RoundUp4Bytes((UINT32)32 + 2);
	length += 4;

	return length;
}
void L4BM_Init_SPLockRequest(SPLockRequest_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->SPLockUnlockCodeReq.Type = INVALID_OPCODE;

}
L4bufman_Funcs SPLockRequest_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SPLockRequest,
	(pf_SetL4Command)L4BM_generic_Set_SPLockRequest,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SPLockRequest,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SPLockRequest,
	(pf_InitL4Command)L4BM_Init_SPLockRequest
};



//
// DebugLoopback
//
L4BUFMAN_Status_t L4BM_Get_DebugLoopback(DebugLoopback_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_DebugLoopback_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_DebugLoopback_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_DebugLoopback_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_DebugLoopback(UINT8* pBuf, DebugLoopback_type msg)
{
	PVOID base_ptr = pBuf;

	DebugLoopback_type tmp = msg;
	tmp = tmp;

	BM_DebugLoopback_Header_Type_SET( base_ptr, L4_L3_OPCODE_GET_DEBUG_LOOPBACK );
	BM_DebugLoopback_Header_Version_SET( base_ptr, msg.header.Version );
	BM_DebugLoopback_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_DebugLoopback_Header_Status_SET( base_ptr, msg.header.Status );
	BM_DebugLoopback_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_DebugLoopback(UINT8* pBuf, DebugLoopback_type* msg)
{
	return L4BM_Set_DebugLoopback(pBuf, *msg);
}
UINT L4BM_GetBufferSize_DebugLoopback(DebugLoopback_type msg)
{

	DebugLoopback_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_DebugLoopback(DebugLoopback_type* msg)
{
	return L4BM_GetBufferSize_DebugLoopback(*msg);
}
UINT L4BM_GetMaxBufferSize_DebugLoopback( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_DebugLoopback(DebugLoopback_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs DebugLoopback_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_DebugLoopback,
	(pf_SetL4Command)L4BM_generic_Set_DebugLoopback,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_DebugLoopback,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_DebugLoopback,
	(pf_InitL4Command)L4BM_Init_DebugLoopback
};



//
// ReportAltAccept
//
L4BUFMAN_Status_t L4BM_Get_ReportAltAccept(ReportAltAccept_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf;

	BM_ReportAltAccept_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ReportAltAccept_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ReportAltAccept_Header_Status_GET( base_ptr, pMsg->header.Status );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ReportAltAccept(UINT8* pBuf, ReportAltAccept_type msg)
{
	PVOID base_ptr = pBuf;

	ReportAltAccept_type tmp = msg;
	tmp = tmp;

	BM_ReportAltAccept_Header_Type_SET( base_ptr, L3_L4_OPCODE_REPORT_ALT_ACCEPT );
	BM_ReportAltAccept_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ReportAltAccept_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ReportAltAccept_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ReportAltAccept_Header_Length_SET( base_ptr, 0 );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ReportAltAccept(UINT8* pBuf, ReportAltAccept_type* msg)
{
	return L4BM_Set_ReportAltAccept(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ReportAltAccept(ReportAltAccept_type msg)
{

	ReportAltAccept_type tmp = msg;
	tmp = tmp;

	return HEADER_SIZE;
}
UINT L4BM_generic_GetBufferSize_ReportAltAccept(ReportAltAccept_type* msg)
{
	return L4BM_GetBufferSize_ReportAltAccept(*msg);
}
UINT L4BM_GetMaxBufferSize_ReportAltAccept( void )
{


	return HEADER_SIZE;
}
void L4BM_Init_ReportAltAccept(ReportAltAccept_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;

}
L4bufman_Funcs ReportAltAccept_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ReportAltAccept,
	(pf_SetL4Command)L4BM_generic_Set_ReportAltAccept,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ReportAltAccept,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ReportAltAccept,
	(pf_InitL4Command)L4BM_Init_ReportAltAccept
};



//
// ModeOfOperationCommand
//
L4BUFMAN_Status_t L4BM_Get_ModeOfOperationCommand(ModeOfOperationCommand_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, type = 0;


	L4BM_Init_ModeOfOperationCommand(pMsg);
	BM_ModeOfOperationCommand_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_ModeOfOperationCommand_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_ModeOfOperationCommand_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_ModeOfOperationCommand_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_ModeOfOperationCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_ModeOfOperationCommand_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_ModeOfOperationCommand_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 131 )
			{
				pMsg->ModeOfOperation.Type = (UINT16)type;
				BM_ModeOfOperationCommand_List_CURRENT_ModeOfOperation_value_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->ModeOfOperation.value );
			}

			BM_ModeOfOperationCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_ModeOfOperationCommand(UINT8* pBuf, ModeOfOperationCommand_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE;


	BM_ModeOfOperationCommand_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.ModeOfOperation.Type == 131 )
	{
		BM_ModeOfOperationCommand_List_SET_TYPE( cur_ptr, cur_bitoff, 131 );
		length = 4;
		BM_ModeOfOperationCommand_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_ModeOfOperationCommand_List_CURRENT_ModeOfOperation_value_SET( base_ptr, cur_ptr, cur_bitoff, msg.ModeOfOperation.value );
		BM_ModeOfOperationCommand_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_ModeOfOperationCommand_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_MODE_OF_OPERATION );
	BM_ModeOfOperationCommand_Header_Version_SET( base_ptr, msg.header.Version );
	BM_ModeOfOperationCommand_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_ModeOfOperationCommand_Header_Status_SET( base_ptr, msg.header.Status );
	BM_ModeOfOperationCommand_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_ModeOfOperationCommand(UINT8* pBuf, ModeOfOperationCommand_type* msg)
{
	return L4BM_Set_ModeOfOperationCommand(pBuf, *msg);
}
UINT L4BM_GetBufferSize_ModeOfOperationCommand(ModeOfOperationCommand_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.ModeOfOperation.Type == 131 )
	{
		length += 4;
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_ModeOfOperationCommand(ModeOfOperationCommand_type* msg)
{
	return L4BM_GetBufferSize_ModeOfOperationCommand(*msg);
}
UINT L4BM_GetMaxBufferSize_ModeOfOperationCommand( void )
{
	UINT32 length = HEADER_SIZE;

	length += 4;
	length += 4;

	return length;
}
void L4BM_Init_ModeOfOperationCommand(ModeOfOperationCommand_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->ModeOfOperation.Type = INVALID_OPCODE;

}
L4bufman_Funcs ModeOfOperationCommand_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_ModeOfOperationCommand,
	(pf_SetL4Command)L4BM_generic_Set_ModeOfOperationCommand,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_ModeOfOperationCommand,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_ModeOfOperationCommand,
	(pf_InitL4Command)L4BM_Init_ModeOfOperationCommand
};



//
// SendEapResponse
//
L4BUFMAN_Status_t L4BM_Get_SendEapResponse(SendEapResponse_type* pMsg, UINT8* buf)
{
	PVOID base_ptr = buf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0, type = 0;


	L4BM_Init_SendEapResponse(pMsg);
	BM_SendEapResponse_Header_Version_GET( base_ptr, pMsg->header.Version );
	BM_SendEapResponse_Header_Accessibility_GET( base_ptr, pMsg->header.Accessibility );
	BM_SendEapResponse_Header_Status_GET( base_ptr, pMsg->header.Status );
	BM_SendEapResponse_Header_Length_GET( base_ptr, listSize );

	if( (INT16)listSize < 0 )
	{
		return L4BUFMAN_ST_FAIL;
	}
	if( (INT16)listSize > 0 )
	{

		BM_SendEapResponse_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );

		while( (INT16)listSize > 0 )
		{
			BM_SendEapResponse_List_GET_TYPE( cur_ptr, cur_bitoff, type );
			BM_SendEapResponse_List_GET_LENGTH( base_ptr, cur_ptr, cur_bitoff, length, err );
			length -= 4;
			if( type == 1027 )
			{
				pMsg->EapResponseMessage.Type = (UINT16)type;
				BM_SendEapResponse_List_CURRENT_EapResponseMessage_ActualLen_GET( base_ptr, cur_ptr, cur_bitoff, pMsg->EapResponseMessage.ActualLen );
				for( i0 = 0; i0 < (UINT32)pMsg->EapResponseMessage.ActualLen; i0++ )
				{
					BM_SendEapResponse_List_CURRENT_EapResponseMessage_BufferArr_value_GET( base_ptr, i0, cur_ptr, cur_bitoff, pMsg->EapResponseMessage.BufferArr[i0].value );
				}
			}

			BM_SendEapResponse_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
			listSize -= length;
			listSize -= 4;
		}
	}

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_Set_SendEapResponse(UINT8* pBuf, SendEapResponse_type msg)
{
	PVOID base_ptr = pBuf, cur_ptr = 0;
	UINT32 cur_bitoff = 0, err = 0, listSize = 0, length = HEADER_SIZE, i0 = 0;


	BM_SendEapResponse_List_GET_FIRST( base_ptr, cur_ptr, cur_bitoff );
	if( msg.EapResponseMessage.Type == 1027 )
	{
		BM_SendEapResponse_List_SET_TYPE( cur_ptr, cur_bitoff, 1027 );
		length = L4BM_RoundUp4Bytes((UINT32)msg.EapResponseMessage.ActualLen + 2);
		BM_SendEapResponse_List_SET_LENGTH( cur_ptr, cur_bitoff, 2, length );
		BM_SendEapResponse_List_CURRENT_EapResponseMessage_ActualLen_SET( base_ptr, cur_ptr, cur_bitoff, msg.EapResponseMessage.ActualLen );
		for( i0 = 0; i0 < (UINT32)msg.EapResponseMessage.ActualLen; i0++ )
		{
			BM_SendEapResponse_List_CURRENT_EapResponseMessage_BufferArr_value_SET( base_ptr, i0, cur_ptr, cur_bitoff, msg.EapResponseMessage.BufferArr[i0].value );
		}
		BM_SendEapResponse_List_GET_NEXT( base_ptr, cur_ptr, cur_bitoff, cur_ptr, cur_bitoff, err );
		listSize += 4;
		listSize += length;
	}

	BM_SendEapResponse_Header_Type_SET( base_ptr, L4_L3_OPCODE_CMD_SEND_EAP_RESPONSE );
	BM_SendEapResponse_Header_Version_SET( base_ptr, msg.header.Version );
	BM_SendEapResponse_Header_Accessibility_SET( base_ptr, msg.header.Accessibility );
	BM_SendEapResponse_Header_Status_SET( base_ptr, msg.header.Status );
	BM_SendEapResponse_Header_Length_SET( base_ptr, listSize );

	return L4BUFMAN_ST_OK;
}
L4BUFMAN_Status_t L4BM_generic_Set_SendEapResponse(UINT8* pBuf, SendEapResponse_type* msg)
{
	return L4BM_Set_SendEapResponse(pBuf, *msg);
}
UINT L4BM_GetBufferSize_SendEapResponse(SendEapResponse_type msg)
{
	UINT32 length = HEADER_SIZE;

	if( msg.EapResponseMessage.Type == 1027 )
	{
		length += L4BM_RoundUp4Bytes((UINT32)msg.EapResponseMessage.ActualLen + 2);
		length += 4;
	}

	return length;
}
UINT L4BM_generic_GetBufferSize_SendEapResponse(SendEapResponse_type* msg)
{
	return L4BM_GetBufferSize_SendEapResponse(*msg);
}
UINT L4BM_GetMaxBufferSize_SendEapResponse( void )
{
	UINT32 length = HEADER_SIZE;

	length += L4BM_RoundUp4Bytes((UINT32)1400 + 2);
	length += 4;

	return length;
}
void L4BM_Init_SendEapResponse(SendEapResponse_type* pMsg)
{

	pMsg->header.Version = HEADER_VERSION;
	pMsg->header.Accessibility = HEADER_ACCESSIBILITY;
	pMsg->header.Status = HEADER_STATUS;
	pMsg->EapResponseMessage.Type = INVALID_OPCODE;

}
L4bufman_Funcs SendEapResponse_Funcs = 
{
	(pf_GetL4Command)L4BM_Get_SendEapResponse,
	(pf_SetL4Command)L4BM_generic_Set_SendEapResponse,
	(pf_GetBufferSize)L4BM_generic_GetBufferSize_SendEapResponse,
	(pf_GetMaxBufferSize)L4BM_GetMaxBufferSize_SendEapResponse,
	(pf_InitL4Command)L4BM_Init_SendEapResponse
};

