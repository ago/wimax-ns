

#include "L4BufMan_L4Common.h"
#include "L4Common.h"


//
// L4bufman utils
//
UINT32 L4BM_RoundUp4Bytes(UINT32 bytes)
{
	UINT32 len = bytes;
	UINT32 bits = 0;
	BMI_ROUND_UP_4BYTES(len, bits);
	return len;
}


//
// Header accessors
//

UINT8* L4BM_GetContent(UINT8* buf)
{
	return (buf + HEADER_SIZE);
}

UINT16 L4BM_GetOpcode(UINT8* buf)
{
	PVOID base_ptr = buf;
	UINT16 opcode;
	
	BM_L3L4CompleteHeader_Type_GET(base_ptr, opcode);
	
	return opcode;
}

void L4BM_SetOpcode(UINT8* buf, UINT16 opcode)
{
	PVOID base_ptr = buf;
	
	BM_L3L4CompleteHeader_Type_SET(base_ptr, opcode);
}

UINT16 L4BM_GetLength(UINT8* buf)
{
	PVOID base_ptr = buf;
	UINT16 length;
	
	BM_L3L4CompleteHeader_Length_GET(base_ptr, length);
	
	return length;
}

void L4BM_SetLength(UINT8* buf, UINT16 length)
{
	PVOID base_ptr = buf;
	
	BM_L3L4CompleteHeader_Length_SET(base_ptr, length);
}

UINT16 L4BM_GetVersion(UINT8* buf)
{
	PVOID base_ptr = buf;
	UINT16 version;
	
	BM_L3L4CompleteHeader_Version_GET(base_ptr, version);
	
	return version;
}

void L4BM_SetVersion(UINT8* buf, UINT16 version)
{
	PVOID base_ptr = buf;
	
	BM_L3L4CompleteHeader_Version_SET(base_ptr, version);
}

UINT16 L4BM_GetAccessibility(UINT8* buf)
{
	PVOID base_ptr = buf;
	UINT16 accessibility;
	
	BM_L3L4CompleteHeader_Accessibility_GET(base_ptr, accessibility);
	
	return accessibility;
}

void L4BM_SetAccessibility(UINT8* buf, UINT16 accessibility)
{
	PVOID base_ptr = buf;
	
	BM_L3L4CompleteHeader_Accessibility_SET(base_ptr, accessibility);
}

UINT16 L4BM_GetStatus(UINT8* buf)
{
	PVOID base_ptr = buf;
	UINT16 status;

	BM_L3L4CompleteHeader_Status_GET(base_ptr, status);

	return status;
}

void L4BM_SetStatus(UINT8* buf, UINT16 status)
{
	PVOID base_ptr = buf;

	BM_L3L4CompleteHeader_Status_SET(base_ptr, status);
}

UINT16 L4BM_GetReserved(UINT8* buf)
{
	PVOID base_ptr = buf;
	UINT16 reserved;

	BM_L3L4CompleteHeader_Reserved2_GET(base_ptr, reserved);

	return reserved;
}

void L4BM_SetReserved(UINT8* buf, UINT16 reserved)
{
	PVOID base_ptr = buf;

	BM_L3L4CompleteHeader_Reserved2_SET(base_ptr, reserved);
}

L4BUFMAN_Status_t L4BM_Get_L3L4CompleteHeader(L3L4CompleteHeader_type* pMsg, UINT8* buf)
{ 
	PVOID base_ptr = buf;

	BM_L3L4CompleteHeader_Type_GET(base_ptr, pMsg->Type);
	BM_L3L4CompleteHeader_Length_GET(base_ptr, pMsg->Length);
	BM_L3L4CompleteHeader_Version_GET(base_ptr, pMsg->Version);
	BM_L3L4CompleteHeader_Accessibility_GET(base_ptr, pMsg->Accessibility);
	BM_L3L4CompleteHeader_Status_GET(base_ptr, pMsg->Status);

	return L4BUFMAN_ST_OK;
}

L4BUFMAN_Status_t L4BM_Set_L3L4CompleteHeader(UINT8* pBuf, L3L4CompleteHeader_type msg)
{ 
	PVOID base_ptr = pBuf;

	BM_L3L4CompleteHeader_Type_SET(base_ptr, msg.Type);
	BM_L3L4CompleteHeader_Length_SET(base_ptr, msg.Length);
	BM_L3L4CompleteHeader_Version_SET(base_ptr, msg.Version);
	BM_L3L4CompleteHeader_Accessibility_SET(base_ptr, msg.Accessibility);
	BM_L3L4CompleteHeader_Status_SET(base_ptr, msg.Status);

	return L4BUFMAN_ST_OK;
}




