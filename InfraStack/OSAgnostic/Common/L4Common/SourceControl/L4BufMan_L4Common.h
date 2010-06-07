
#ifndef _L4BUFMAN_L4COMMON_H
#define _L4BUFMAN_L4COMMON_H


#include "L4BufMan_L4Common_Desc.h"


// obsolete
typedef struct L4Buffer_struct
{
	UINT8 *buffer;
	UINT bufferLength;
} L4Buffer;


//
typedef enum _L4BUFMAN_Status_t
{
	L4BUFMAN_ST_OK	= 0x00,		// The operation had completed successfully
	L4BUFMAN_ST_FAIL			// Unknown failure
} L4BUFMAN_Status_t;


typedef void* GENERIC_STRCT;

typedef L4BUFMAN_Status_t (*pf_GetL4Command)(GENERIC_STRCT strct, UINT8* buf);
typedef L4BUFMAN_Status_t (*pf_SetL4Command)(UINT8* buf, GENERIC_STRCT strct);
typedef UINT (*pf_GetBufferSize)(GENERIC_STRCT strct);
typedef UINT (*pf_GetMaxBufferSize)();
typedef void (*pf_InitL4Command)(GENERIC_STRCT strct);

typedef struct _L4bufman_Funcs
{
	pf_GetL4Command getFunc;
	pf_SetL4Command setFunc;
	pf_GetBufferSize getBufferSizeFunc;
	pf_GetMaxBufferSize getMaxBufferSizeFunc;
	pf_InitL4Command initFunc;

} L4bufman_Funcs;

UINT32 L4BM_RoundUp4Bytes(UINT32 bytes);

UINT8* L4BM_GetContent(UINT8* buf);

UINT16 L4BM_GetOpcode(UINT8* buf);
void L4BM_SetOpcode(UINT8* buf, UINT16 opcode);

UINT16 L4BM_GetLength(UINT8* buf);
void L4BM_SetLength(UINT8* buf, UINT16 length);

UINT16 L4BM_GetVersion(UINT8* buf);
void L4BM_SetVersion(UINT8* buf, UINT16 version);

UINT16 L4BM_GetAccessibility(UINT8* buf);
void L4BM_SetAccessibility(UINT8* buf, UINT16 accessibility);

UINT16 L4BM_GetStatus(UINT8* buf);
void L4BM_SetStatus(UINT8* buf, UINT16 status);

UINT16 L4BM_GetReserved(UINT8* buf);
void L4BM_SetReserved(UINT8* buf, UINT16 reserved);

L4BUFMAN_Status_t L4BM_Get_L3L4CompleteHeader(L3L4CompleteHeader_type* pMsg, UINT8* buf);
L4BUFMAN_Status_t L4BM_Set_L3L4CompleteHeader(UINT8* pBuf, L3L4CompleteHeader_type msg);



#endif //_L4BUFMAN_L4COMMON_H
