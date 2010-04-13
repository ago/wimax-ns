
#ifndef _L4BUFMAN_L4COMMON_DESC_H
#define _L4BUFMAN_L4COMMON_DESC_H


#include "TypesProxy.h"


// header
#if (defined(__arm) && !defined(WINCE)) 
__packed
#else 
#pragma pack( push, 1 )
#endif
struct L3L4CompleteHeader_struct
{
	UINT16 Type;
	UINT16 Length;
	UINT16 Version;
	UINT16 Accessibility;
	UINT16 Status;
	UINT16 Reserved2;
};
#if (!defined(__arm) || defined(WINCE)) 
#pragma pack( pop )
#endif
typedef struct L3L4CompleteHeader_struct L3L4CompleteHeader_type;

#if (defined(__arm) && !defined(WINCE)) 
__packed
#else 
#pragma pack( push, 1 )
#endif
struct L3L4Header_struct
{
	UINT16 Version;
	UINT16 Accessibility;
	UINT16 Status;
};
#if (!defined(__arm) || defined(WINCE)) 
#pragma pack( pop )
#endif
typedef struct L3L4Header_struct L3L4Header_type;



// bitman basic types
#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Uint8_struct
{
	UINT8 value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Uint8_struct Uint8_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Uint8_tlv_struct
{
	UINT16 Type;
	UINT8 value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Uint8_tlv_struct Uint8_tlv_type;


#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Uint16_struct
{
	UINT16 value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Uint16_struct Uint16_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Uint16_tlv_struct
{
	UINT16 Type;
	UINT16 value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Uint16_tlv_struct Uint16_tlv_type;


#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Uint32_struct
{
	UINT32 value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Uint32_struct Uint32_type;

#if (defined(__arm) && !defined(WINCE))
__packed
#else
#pragma pack( push, 1 )
#endif
struct Uint32_tlv_struct
{
	UINT16 Type;
	UINT32 value;
};
#if (!defined(__arm) || defined(WINCE))
#pragma pack( pop )
#endif
typedef struct Uint32_tlv_struct Uint32_tlv_type;


#endif //_L4BUFMAN_L4COMMON_DESC_H
