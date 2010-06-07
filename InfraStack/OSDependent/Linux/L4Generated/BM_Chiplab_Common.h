/*****************************************************************************
 * Automatically generated by Bitman2Base V4.2.5.0 (5.0) Bitman2 (exe) V4.2.5.0 (5.0) - DO NOT EDIT!
 * Generated at 11/19/2009 12:56:05 AM
 *
 * Project : Ofer
 * Module  : ChipLabInterface
 * Author  : Barak
 * Date    : 22/7/2008
 * Purpose : isolating BufferString composite
 *****************************************************************************/

#if !defined(_BITMAN_BM_CHIPLAB_COMMON_H_)
#define _BITMAN_BM_CHIPLAB_COMMON_H_


/*lint ++flb */
// Include the Bitman common header file
#include "BitmanCommon.h"

// Include headers generated from XMLs (the source is both XMLs and the command-line)

// Include user C header files


// Bitman version Accessor...
#ifndef BM_BITMAN_VERSION
#define BM_BITMAN_VERSION 	"Bitman2Base V4.2.5.0 (5.0) Bitman2 (exe) V4.2.5.0 (5.0)"
#endif 

// Definitions

typedef UINT8 BufferString[1];

/*lint -save -e806 */ /* Small bit field is signed rather than unsigned*/
#ifdef BMI_ENDIANNESS_LITTLE
#if (!defined __arm && !defined __arc)
#pragma pack( push, 1 )
#endif
#ifdef __arm
typedef __packed struct
#elif defined __arc
typedef _Packed struct
#else
typedef struct
#endif
{
	UINT8 _BufferByte : 8;
} BMS_BufferString;

#if (!defined __arm && !defined __arc)
#pragma pack( pop )
#endif

#else /* BMI_ENDIANNESS_BIG */
#if (!defined __arm && !defined __arc)
#pragma pack( push, 1 )
#endif
#ifdef __arm
typedef __packed struct
#elif defined __arc
typedef _Packed struct
#else
typedef struct
#endif
{
	UINT8 _BufferByte : 8;
} BMS_BufferString;

#if (!defined __arm && !defined __arc)
#pragma pack( pop )
#endif

#endif	/*#ifdef BMI_ENDIANNESS_LITTLE*/
/*lint -restore */

// COMPOSITE: Full name: 'BufferString' Type: 'BufferString', Top-level, Non-instance, No bitoff root
#define BM_BufferString_BufferByte_GET_POS( base_ptr, out_ptr, out_bitoff )\
{\
	/*lint --e{*} */\
	out_ptr = base_ptr;\
	out_bitoff = 0;\
}

#define BM_BufferString_BufferByte_GET_POS_ALIGNED( base_ptr, out_ptr )\
{\
	/*lint --e{*} */\
	UINT bmlocal258_tmp_bitoff;\
	BM_BufferString_BufferByte_GET_POS( base_ptr, out_ptr, bmlocal258_tmp_bitoff );\
	BMI_NORMALIZE_BITOFF(out_ptr, bmlocal258_tmp_bitoff);\
}

#define BM_BufferString_BufferByte_POS_ALIGNED 0

// Alignment of BufferString_BufferByte: accumulated=(0,0, ABA=1), parent.base=(0,0, ABA=1)
#define BM_BufferString_BufferByte_GET_SIZE( base_ptr, out_bytes, out_bits )\
{\
	/*lint --e{*} */\
	out_bytes = 1;\
	out_bits = 0;\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_BufferString_BufferByte_GET( base_ptr, out_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal259_my_ptr;\
	UINT bmlocal260_my_bitoff;\
	BM_BufferString_BufferByte_GET_POS( base_ptr, bmlocal259_my_ptr, bmlocal260_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT8)BMI_32BIT_EXTRACT( (BMI_GET_8BIT_PTR_CONTENTS( BMI_PTR_TO_NUMERIC_CAST(bmlocal259_my_ptr)) ), 0, 8, 0);\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT8)BMI_32BIT_EXTRACT( (BMI_GET_8BIT_PTR_CONTENTS( BMI_PTR_TO_NUMERIC_CAST(bmlocal259_my_ptr)) ), 0, 8, 0);\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_GET( bmlocal259_my_ptr, bmlocal260_my_bitoff, 8, UINT8, out_val, 0xFFFFFFFF );\
	}\
}

BMI_INLINE UINT8 BM_INLINE_BufferString_BufferByte_GET(PVOID base_ptr)
{
	/*lint --e{*} */
	UINT8 bmlocal261_tmp_var;
	BM_BufferString_BufferByte_GET( base_ptr, bmlocal261_tmp_var );
	return bmlocal261_tmp_var;
}

#define BM_BufferString_BufferByte_SET( base_ptr, in_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal262_my_ptr;\
	UINT bmlocal263_my_bitoff;\
	BM_BufferString_BufferByte_GET_POS( base_ptr, bmlocal262_my_ptr, bmlocal263_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_8BIT_PTR_CONTENTS( BMI_PTR_TO_NUMERIC_CAST(bmlocal262_my_ptr) ), (in_val), 0, 0, 8, UINT8 );\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_8BIT_PTR_CONTENTS( BMI_PTR_TO_NUMERIC_CAST(bmlocal262_my_ptr) ), (in_val), 0, 0, 8, UINT8 );\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_SET( bmlocal262_my_ptr, bmlocal263_my_bitoff, 8, in_val, 0xFFFFFFFF );\
	}\
}

// BufferString_BufferByte: IS_DEFAULT accessor is not defined because no default value was specified.
// BufferString_BufferByte: SET_DEFAULT accessor is not defined because no default value was specified.
// BufferString_BufferByte: IS_RESET accessor is not defined because no reset value was specified.
// BufferString_BufferByte: SET_RESET accessor is not defined because no reset value was specified.
// BufferString_BufferByte: CLEAR accessor is not defined because of incompatible access rights. Specified: RW Required: W1C, WO1C.
// BufferString_BufferByte: SET(W1S) accessor is not defined because of incompatible access rights. Specified: RW Required: W1S, WO1S.
#define BM_BufferString_BufferByte_DUMP_DEPTH( base_ptr, depth )\
{\
	/*lint --e{*} */\
	UINT8 bmlocal264_out_val;\
	BM_BufferString_BufferByte_GET( base_ptr, bmlocal264_out_val );\
	/*lint -e(571) */\
	BMI_FORMAT_DUMP(depth, "BufferByte", 8, (UINT)(bmlocal264_out_val), "%d", 1);\
}

#define BM_BufferString_BufferByte_DUMP( base_ptr )\
{\
	/*lint --e{*} */\
	BM_BufferString_BufferByte_DUMP_DEPTH( base_ptr, 0 );\
}

#define BM_BufferString_BufferByte_INCREMENT( base_ptr )\
{\
	/*lint --e{*} */\
	PVOID bmlocal265_my_ptr;\
	UINT bmlocal266_my_bitoff;\
	BM_BufferString_BufferByte_GET_POS( base_ptr, bmlocal265_my_ptr, bmlocal266_my_bitoff );\
	(*((UINT8*)bmlocal265_my_ptr))++;\
	BMI_UNUSED_VAR( bmlocal266_my_bitoff );\
}

// BufferString_BufferByte: Validation accessors are not defined because validation condition was not specified.
#define BM_BufferString_BufferByte_GET_BYTES_SIZE( base_ptr, out_bytes )\
{\
	/*lint --e{*} */\
	UINT bmlocal267_tmp_bits;\
	BM_BufferString_BufferByte_GET_SIZE( base_ptr, out_bytes, bmlocal267_tmp_bits );\
	BMI_ROUND_UP_1BYTES( out_bytes, bmlocal267_tmp_bits );\
}

#define BM_BufferString_BufferByte_BYTES_SIZE 1

#define BM_BufferString_GET_SIZE( base_ptr, out_bytes, out_bits )\
{\
	/*lint --e{*} */\
	out_bytes = 1;\
	out_bits = 0;\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_BufferString_GET_BYTES_SIZE( base_ptr, out_bytes )\
{\
	/*lint --e{*} */\
	UINT bmlocal270_tmp_bits;\
	BM_BufferString_GET_SIZE( base_ptr, out_bytes, bmlocal270_tmp_bits );\
	BMI_ROUND_UP_1BYTES( out_bytes, bmlocal270_tmp_bits );\
}

#define BM_BufferString_BYTES_SIZE 1

#define BM_BufferString_DUMP_DEPTH( base_ptr, depth )\
{\
	/*lint --e{*} */\
	BMI_FORMAT_NONVALUE_DUMP(depth, "BufferString", 1);\
	BM_BufferString_BufferByte_DUMP_DEPTH( base_ptr, (depth + 1) );\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_BufferString_DUMP( base_ptr )\
{\
	/*lint --e{*} */\
	BM_BufferString_DUMP_DEPTH( base_ptr, 0 );\
}


/*lint --flb */

#endif /* _BITMAN_BM_CHIPLAB_COMMON_H_ */

