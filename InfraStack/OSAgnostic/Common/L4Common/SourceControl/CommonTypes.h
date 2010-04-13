/*************************************************************************
**                                                                      **
**                  I N T E L ( ENVARA ) P R O P R I E T A R Y          **
**                                                                      **
**     COPYRIGHT (c)  2005 BY  INTEL  CORPORATION.  ALL RIGHTS          **
**     RESERVED.   NO  PART  OF THIS PROGRAM  OR  PUBLICATION  MAY      **
**     BE  REPRODUCED,   TRANSMITTED,   TRANSCRIBED,   STORED  IN  A    **
**     RETRIEVAL SYSTEM, OR TRANSLATED INTO ANY LANGUAGE OR COMPUTER    **
**     LANGUAGE IN ANY FORM OR BY ANY MEANS, ELECTRONIC, MECHANICAL,    **
**     MAGNETIC,  OPTICAL,  CHEMICAL, MANUAL, OR OTHERWISE,  WITHOUT    **
**     THE PRIOR WRITTEN PERMISSION OF INTEL  CORPORATION.              **
**                                                                      **
*************************************************************************/

/**
 * @file
 *
 * CommonTypes.h
 *
 * Types that are defined the same way in all platforms, based on
 * the basic types.
 * 
 * @version 1.0    07-July-2005    Yariv Barkan\n
 *    Initial version
 *
 */

#ifndef __COMMONTYPES_H
#define __COMMONTYPES_H

// just for completeness
typedef INT		SINT;	
typedef INT8	SINT8;
typedef INT16	SINT16;
typedef INT32	SINT32;
typedef INT64	SINT64;

// booleans

typedef UINT8		BOOL8;
typedef UINT16	BOOL16;
typedef UINT32	BOOL32;
typedef UINT64	BOOL64;

// volatiles
typedef volatile INT		VINT;
typedef volatile INT8		VINT8;
typedef volatile INT16		VINT16;
typedef volatile INT32		VINT32;
typedef volatile INT64		VINT64;

typedef volatile UINT		VUINT;
typedef volatile UINT8		VUINT8;
typedef volatile UINT16		VUINT16;
typedef volatile UINT32		VUINT32;
typedef volatile UINT64		VUINT64;

// standard pointers
typedef void*		PVOID;
typedef const void*	PCVOID;

typedef INT*		PINT;
typedef INT8*		PINT8;
typedef INT16*		PINT16;
typedef INT32*		PINT32;
typedef INT64*		PINT64;

typedef UINT*		PUINT;
typedef UINT8*		PUINT8;
typedef UINT16*		PUINT16;
typedef UINT32*		PUINT32;
typedef UINT64*		PUINT64;

// pointers to volatile
typedef VINT*		PVINT;
typedef VINT8*		PVINT8;
typedef VINT16*		PVINT16;
typedef VINT32*		PVINT32;
typedef VINT64*		PVINT64;

typedef VUINT*		PVUINT;
typedef VUINT8*		PVUINT8;
typedef VUINT16*	PVUINT16;
typedef VUINT32*	PVUINT32;
typedef VUINT64*	PVUINT64;

// strings
typedef char*		PSTR;
typedef const char*	PCSTR;

/// when you need to hold both a pointer and a number
#ifdef WIN64
typedef UINT64 POINTER_AND_UINT;
#else
typedef UINT POINTER_AND_UINT;
#endif

#if defined(PRJCFG_ESHEL_WIMAX_CORE) || defined(PRJCFG_NELSON_CORE)
//this part made for eshel use only

typedef enum status_enum{
 STATUS_SUCCESS = 0 ,
 STATUS_FAIL    = 1
}STATUS_ENUM;
#endif
#define MAX_NUMBER_OF_MEM_TRANS_DESCRIPTORS 5

typedef struct
{
    void *src;
    void *dst;
    UINT32 size; 
    UINT32 currPos;
} BufferTransferDesc, *PBufferTransferDesc;

typedef struct
{
    UINT8    numOfBuffers;
    BufferTransferDesc buffers[MAX_NUMBER_OF_MEM_TRANS_DESCRIPTORS];
} ScatteredTransactionDesc, *PScatteredTransactionDesc;

#define CYCLIC_QUEUE_MAX_NUMBER_OF_FRAGMENTS 2
typedef struct
{
    ScatteredTransactionDesc transDesc;
    UINT8  dataType;
    UINT32 currDataPos;
    UINT32 totalDataLength;
}
DataTransactionDesc, *PDataTransactionDesc;
typedef void(*PRELEASE_PACKET_FUNC)(PDataTransactionDesc); 
#ifndef NATIVE_LINUX
#include "ObsoletedTypes.h"
#endif 

#endif //__COMMONTYPES
