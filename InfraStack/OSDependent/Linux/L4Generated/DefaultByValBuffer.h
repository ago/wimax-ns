/*****************************************************************************
 * Automatically generated by Bitman2Base V4.2.5.0 (5.0) Bitman2 (exe) V4.2.5.0 (5.0) - DO NOT EDIT!
 * Generated at 11/19/2009 12:56:05 AM
 *
 * Project : Ofer
 * Module  : Default by val buffer format
 * Author  : Yakir Green
 * Date    : 19/10/2005
 * Purpose : Default by val buffer format
 *****************************************************************************/

#if !defined(_BITMAN_DEFAULTBYVALBUFFER_H_)
#define _BITMAN_DEFAULTBYVALBUFFER_H_


/*lint ++flb */
// Include the Bitman common header file
#include "BitmanCommon.h"

// Include headers generated from XMLs (the source is both XMLs and the command-line)

// Include user C header files

// Include user C header files (supplied in the command-line)


// Bitman version Accessor...
#ifndef BM_BITMAN_VERSION
#define BM_BITMAN_VERSION 	"Bitman2Base V4.2.5.0 (5.0) Bitman2 (exe) V4.2.5.0 (5.0)"
#endif 

// Definitions

typedef UINT8 DefaultByValBufferFormat[12];

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
	UINT32 _Param1; //Param1
	UINT32 _Param2; //Param2
	UINT32 _Param3; //Param3
} BMS_DefaultByValBufferFormat;

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
	UINT32 _Param3; //Param3
	UINT32 _Param2; //Param2
	UINT32 _Param1; //Param1
} BMS_DefaultByValBufferFormat;

#if (!defined __arm && !defined __arc)
#pragma pack( pop )
#endif

#endif	/*#ifdef BMI_ENDIANNESS_LITTLE*/
/*lint -restore */

// COMPOSITE: Full name: 'DefaultByValBufferFormat' Type: 'DefaultByValBufferFormat', Top-level, Non-instance, No bitoff root
#define BM_DefaultByValBufferFormat_Param1_GET_POS( base_ptr, out_ptr, out_bitoff )\
{\
	/*lint --e{*} */\
	out_ptr = base_ptr;\
	out_bitoff = 0;\
}

#define BM_DefaultByValBufferFormat_Param1_GET_POS_ALIGNED( base_ptr, out_ptr )\
{\
	/*lint --e{*} */\
	UINT bmlocal0_tmp_bitoff;\
	BM_DefaultByValBufferFormat_Param1_GET_POS( base_ptr, out_ptr, bmlocal0_tmp_bitoff );\
	BMI_NORMALIZE_BITOFF(out_ptr, bmlocal0_tmp_bitoff);\
}

#define BM_DefaultByValBufferFormat_Param1_POS_ALIGNED 0

// Alignment of DefaultByValBufferFormat_Param1: accumulated=(0,0, ABA=4), parent.base=(0,0, ABA=4)
#define BM_DefaultByValBufferFormat_Param1_GET_SIZE( base_ptr, out_bytes, out_bits )\
{\
	/*lint --e{*} */\
	out_bytes = 4;\
	out_bits = 0;\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_DefaultByValBufferFormat_Param1_GET( base_ptr, out_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal1_my_ptr;\
	UINT bmlocal2_my_bitoff;\
	BM_DefaultByValBufferFormat_Param1_GET_POS( base_ptr, bmlocal1_my_ptr, bmlocal2_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT32)BMI_32BIT_EXTRACT( (BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal1_my_ptr)) ), 0, 32, 0);\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT32)BMI_32BIT_EXTRACT( (BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal1_my_ptr)) ), 0, 32, 0);\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_GET_VOLATILE( bmlocal1_my_ptr, bmlocal2_my_bitoff, 32, UINT32, out_val, 0x00000000 );\
	}\
}

BMI_INLINE UINT32 BM_INLINE_DefaultByValBufferFormat_Param1_GET(PVOID base_ptr)
{
	/*lint --e{*} */
	UINT32 bmlocal3_tmp_var;
	BM_DefaultByValBufferFormat_Param1_GET( base_ptr, bmlocal3_tmp_var );
	return bmlocal3_tmp_var;
}

#define BM_DefaultByValBufferFormat_Param1_SET( base_ptr, in_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal4_my_ptr;\
	UINT bmlocal5_my_bitoff;\
	BM_DefaultByValBufferFormat_Param1_GET_POS( base_ptr, bmlocal4_my_ptr, bmlocal5_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal4_my_ptr) ), (in_val), 0, 0, 32, UINT32 );\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal4_my_ptr) ), (in_val), 0, 0, 32, UINT32 );\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_SET_VOLATILE( bmlocal4_my_ptr, bmlocal5_my_bitoff, 32, in_val, 0x00000000 );\
	}\
}

// DefaultByValBufferFormat_Param1: IS_DEFAULT accessor is not defined because no default value was specified.
// DefaultByValBufferFormat_Param1: SET_DEFAULT accessor is not defined because no default value was specified.
// DefaultByValBufferFormat_Param1: IS_RESET accessor is not defined because no reset value was specified.
// DefaultByValBufferFormat_Param1: SET_RESET accessor is not defined because no reset value was specified.
// DefaultByValBufferFormat_Param1: CLEAR accessor is not defined because of incompatible access rights. Specified: RW Required: W1C, WO1C.
// DefaultByValBufferFormat_Param1: SET(W1S) accessor is not defined because of incompatible access rights. Specified: RW Required: W1S, WO1S.
#define BM_DefaultByValBufferFormat_Param1_DUMP_DEPTH( base_ptr, depth )\
{\
	/*lint --e{*} */\
	UINT32 bmlocal6_out_val;\
	BM_DefaultByValBufferFormat_Param1_GET( base_ptr, bmlocal6_out_val );\
	/*lint -e(571) */\
	BMI_FORMAT_DUMP(depth, "Param1", 32, (UINT)(bmlocal6_out_val), "%d", 1);\
}

#define BM_DefaultByValBufferFormat_Param1_DUMP( base_ptr )\
{\
	/*lint --e{*} */\
	BM_DefaultByValBufferFormat_Param1_DUMP_DEPTH( base_ptr, 0 );\
}

#define BM_DefaultByValBufferFormat_Param1_INCREMENT( base_ptr )\
{\
	/*lint --e{*} */\
	PVOID bmlocal7_my_ptr;\
	UINT bmlocal8_my_bitoff;\
	BM_DefaultByValBufferFormat_Param1_GET_POS( base_ptr, bmlocal7_my_ptr, bmlocal8_my_bitoff );\
	(*((UINT32*)bmlocal7_my_ptr))++;\
	BMI_UNUSED_VAR( bmlocal8_my_bitoff );\
}

// DefaultByValBufferFormat_Param1: Validation accessors are not defined because validation condition was not specified.
#define BM_DefaultByValBufferFormat_Param1_GET_BYTES_SIZE( base_ptr, out_bytes )\
{\
	/*lint --e{*} */\
	UINT bmlocal9_tmp_bits;\
	BM_DefaultByValBufferFormat_Param1_GET_SIZE( base_ptr, out_bytes, bmlocal9_tmp_bits );\
	BMI_ROUND_UP_1BYTES( out_bytes, bmlocal9_tmp_bits );\
}

#define BM_DefaultByValBufferFormat_Param1_BYTES_SIZE 4

#define BM_DefaultByValBufferFormat_Param2_GET_POS( base_ptr, out_ptr, out_bitoff )\
{\
	/*lint --e{*} */\
	UINT bmlocal12_acc_bytes;\
	UINT bmlocal13_acc_bits;\
	out_ptr = base_ptr;\
	out_bitoff = 0;\
	bmlocal12_acc_bytes = 4;\
	bmlocal13_acc_bits = 0;\
	BMI_ADD_ASSIGN_PTR( out_ptr, bmlocal12_acc_bytes );\
	out_bitoff += bmlocal13_acc_bits;\
}

#define BM_DefaultByValBufferFormat_Param2_GET_POS_ALIGNED( base_ptr, out_ptr )\
{\
	/*lint --e{*} */\
	UINT bmlocal14_tmp_bitoff;\
	BM_DefaultByValBufferFormat_Param2_GET_POS( base_ptr, out_ptr, bmlocal14_tmp_bitoff );\
	BMI_NORMALIZE_BITOFF(out_ptr, bmlocal14_tmp_bitoff);\
}

#define BM_DefaultByValBufferFormat_Param2_POS_ALIGNED 4

// Alignment of DefaultByValBufferFormat_Param2: accumulated=(0,0, ABA=4), parent.base=(0,0, ABA=4)
#define BM_DefaultByValBufferFormat_Param2_GET_SIZE( base_ptr, out_bytes, out_bits )\
{\
	/*lint --e{*} */\
	out_bytes = 4;\
	out_bits = 0;\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_DefaultByValBufferFormat_Param2_GET( base_ptr, out_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal15_my_ptr;\
	UINT bmlocal16_my_bitoff;\
	BM_DefaultByValBufferFormat_Param2_GET_POS( base_ptr, bmlocal15_my_ptr, bmlocal16_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT32)BMI_32BIT_EXTRACT( (BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal15_my_ptr)) ), 0, 32, 0);\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT32)BMI_32BIT_EXTRACT( (BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal15_my_ptr)) ), 0, 32, 0);\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_GET_VOLATILE( bmlocal15_my_ptr, bmlocal16_my_bitoff, 32, UINT32, out_val, 0x00000000 );\
	}\
}

BMI_INLINE UINT32 BM_INLINE_DefaultByValBufferFormat_Param2_GET(PVOID base_ptr)
{
	/*lint --e{*} */
	UINT32 bmlocal17_tmp_var;
	BM_DefaultByValBufferFormat_Param2_GET( base_ptr, bmlocal17_tmp_var );
	return bmlocal17_tmp_var;
}

#define BM_DefaultByValBufferFormat_Param2_SET( base_ptr, in_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal18_my_ptr;\
	UINT bmlocal19_my_bitoff;\
	BM_DefaultByValBufferFormat_Param2_GET_POS( base_ptr, bmlocal18_my_ptr, bmlocal19_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal18_my_ptr) ), (in_val), 0, 0, 32, UINT32 );\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal18_my_ptr) ), (in_val), 0, 0, 32, UINT32 );\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_SET_VOLATILE( bmlocal18_my_ptr, bmlocal19_my_bitoff, 32, in_val, 0x00000000 );\
	}\
}

// DefaultByValBufferFormat_Param2: IS_DEFAULT accessor is not defined because no default value was specified.
// DefaultByValBufferFormat_Param2: SET_DEFAULT accessor is not defined because no default value was specified.
// DefaultByValBufferFormat_Param2: IS_RESET accessor is not defined because no reset value was specified.
// DefaultByValBufferFormat_Param2: SET_RESET accessor is not defined because no reset value was specified.
// DefaultByValBufferFormat_Param2: CLEAR accessor is not defined because of incompatible access rights. Specified: RW Required: W1C, WO1C.
// DefaultByValBufferFormat_Param2: SET(W1S) accessor is not defined because of incompatible access rights. Specified: RW Required: W1S, WO1S.
#define BM_DefaultByValBufferFormat_Param2_DUMP_DEPTH( base_ptr, depth )\
{\
	/*lint --e{*} */\
	UINT32 bmlocal20_out_val;\
	BM_DefaultByValBufferFormat_Param2_GET( base_ptr, bmlocal20_out_val );\
	/*lint -e(571) */\
	BMI_FORMAT_DUMP(depth, "Param2", 32, (UINT)(bmlocal20_out_val), "%d", 1);\
}

#define BM_DefaultByValBufferFormat_Param2_DUMP( base_ptr )\
{\
	/*lint --e{*} */\
	BM_DefaultByValBufferFormat_Param2_DUMP_DEPTH( base_ptr, 0 );\
}

#define BM_DefaultByValBufferFormat_Param2_INCREMENT( base_ptr )\
{\
	/*lint --e{*} */\
	PVOID bmlocal21_my_ptr;\
	UINT bmlocal22_my_bitoff;\
	BM_DefaultByValBufferFormat_Param2_GET_POS( base_ptr, bmlocal21_my_ptr, bmlocal22_my_bitoff );\
	(*((UINT32*)bmlocal21_my_ptr))++;\
	BMI_UNUSED_VAR( bmlocal22_my_bitoff );\
}

// DefaultByValBufferFormat_Param2: Validation accessors are not defined because validation condition was not specified.
#define BM_DefaultByValBufferFormat_Param2_GET_BYTES_SIZE( base_ptr, out_bytes )\
{\
	/*lint --e{*} */\
	UINT bmlocal23_tmp_bits;\
	BM_DefaultByValBufferFormat_Param2_GET_SIZE( base_ptr, out_bytes, bmlocal23_tmp_bits );\
	BMI_ROUND_UP_1BYTES( out_bytes, bmlocal23_tmp_bits );\
}

#define BM_DefaultByValBufferFormat_Param2_BYTES_SIZE 4

#define BM_DefaultByValBufferFormat_Param3_GET_POS( base_ptr, out_ptr, out_bitoff )\
{\
	/*lint --e{*} */\
	UINT bmlocal26_acc_bytes;\
	UINT bmlocal27_acc_bits;\
	out_ptr = base_ptr;\
	out_bitoff = 0;\
	bmlocal26_acc_bytes = 8;\
	bmlocal27_acc_bits = 0;\
	BMI_ADD_ASSIGN_PTR( out_ptr, bmlocal26_acc_bytes );\
	out_bitoff += bmlocal27_acc_bits;\
}

#define BM_DefaultByValBufferFormat_Param3_GET_POS_ALIGNED( base_ptr, out_ptr )\
{\
	/*lint --e{*} */\
	UINT bmlocal28_tmp_bitoff;\
	BM_DefaultByValBufferFormat_Param3_GET_POS( base_ptr, out_ptr, bmlocal28_tmp_bitoff );\
	BMI_NORMALIZE_BITOFF(out_ptr, bmlocal28_tmp_bitoff);\
}

#define BM_DefaultByValBufferFormat_Param3_POS_ALIGNED 8

// Alignment of DefaultByValBufferFormat_Param3: accumulated=(0,0, ABA=4), parent.base=(0,0, ABA=4)
#define BM_DefaultByValBufferFormat_Param3_GET_SIZE( base_ptr, out_bytes, out_bits )\
{\
	/*lint --e{*} */\
	out_bytes = 4;\
	out_bits = 0;\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_DefaultByValBufferFormat_Param3_GET( base_ptr, out_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal29_my_ptr;\
	UINT bmlocal30_my_bitoff;\
	BM_DefaultByValBufferFormat_Param3_GET_POS( base_ptr, bmlocal29_my_ptr, bmlocal30_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT32)BMI_32BIT_EXTRACT( (BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal29_my_ptr)) ), 0, 32, 0);\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		(out_val) = (UINT32)BMI_32BIT_EXTRACT( (BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal29_my_ptr)) ), 0, 32, 0);\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_GET_VOLATILE( bmlocal29_my_ptr, bmlocal30_my_bitoff, 32, UINT32, out_val, 0x00000000 );\
	}\
}

BMI_INLINE UINT32 BM_INLINE_DefaultByValBufferFormat_Param3_GET(PVOID base_ptr)
{
	/*lint --e{*} */
	UINT32 bmlocal31_tmp_var;
	BM_DefaultByValBufferFormat_Param3_GET( base_ptr, bmlocal31_tmp_var );
	return bmlocal31_tmp_var;
}

#define BM_DefaultByValBufferFormat_Param3_SET( base_ptr, in_val )\
{\
	/*lint --e{*} */\
	PVOID bmlocal32_my_ptr;\
	UINT bmlocal33_my_bitoff;\
	BM_DefaultByValBufferFormat_Param3_GET_POS( base_ptr, bmlocal32_my_ptr, bmlocal33_my_bitoff );\
	if( BMI_MACHINE_ARM_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal32_my_ptr) ), (in_val), 0, 0, 32, UINT32 );\
	}\
	else if( BMI_MACHINE_INTEL_LITTLE == BMI_MACHINE_VALUE )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_TYPE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE( BMI_PTR_TO_NUMERIC_CAST(bmlocal32_my_ptr) ), (in_val), 0, 0, 32, UINT32 );\
	}\
	else\
	{\
		BMI_GENERIC_32BIT_LITTLE_SET_VOLATILE( bmlocal32_my_ptr, bmlocal33_my_bitoff, 32, in_val, 0x00000000 );\
	}\
}

// DefaultByValBufferFormat_Param3: IS_DEFAULT accessor is not defined because no default value was specified.
// DefaultByValBufferFormat_Param3: SET_DEFAULT accessor is not defined because no default value was specified.
// DefaultByValBufferFormat_Param3: IS_RESET accessor is not defined because no reset value was specified.
// DefaultByValBufferFormat_Param3: SET_RESET accessor is not defined because no reset value was specified.
// DefaultByValBufferFormat_Param3: CLEAR accessor is not defined because of incompatible access rights. Specified: RW Required: W1C, WO1C.
// DefaultByValBufferFormat_Param3: SET(W1S) accessor is not defined because of incompatible access rights. Specified: RW Required: W1S, WO1S.
#define BM_DefaultByValBufferFormat_Param3_DUMP_DEPTH( base_ptr, depth )\
{\
	/*lint --e{*} */\
	UINT32 bmlocal34_out_val;\
	BM_DefaultByValBufferFormat_Param3_GET( base_ptr, bmlocal34_out_val );\
	/*lint -e(571) */\
	BMI_FORMAT_DUMP(depth, "Param3", 32, (UINT)(bmlocal34_out_val), "%d", 1);\
}

#define BM_DefaultByValBufferFormat_Param3_DUMP( base_ptr )\
{\
	/*lint --e{*} */\
	BM_DefaultByValBufferFormat_Param3_DUMP_DEPTH( base_ptr, 0 );\
}

#define BM_DefaultByValBufferFormat_Param3_INCREMENT( base_ptr )\
{\
	/*lint --e{*} */\
	PVOID bmlocal35_my_ptr;\
	UINT bmlocal36_my_bitoff;\
	BM_DefaultByValBufferFormat_Param3_GET_POS( base_ptr, bmlocal35_my_ptr, bmlocal36_my_bitoff );\
	(*((UINT32*)bmlocal35_my_ptr))++;\
	BMI_UNUSED_VAR( bmlocal36_my_bitoff );\
}

// DefaultByValBufferFormat_Param3: Validation accessors are not defined because validation condition was not specified.
#define BM_DefaultByValBufferFormat_Param3_GET_BYTES_SIZE( base_ptr, out_bytes )\
{\
	/*lint --e{*} */\
	UINT bmlocal37_tmp_bits;\
	BM_DefaultByValBufferFormat_Param3_GET_SIZE( base_ptr, out_bytes, bmlocal37_tmp_bits );\
	BMI_ROUND_UP_1BYTES( out_bytes, bmlocal37_tmp_bits );\
}

#define BM_DefaultByValBufferFormat_Param3_BYTES_SIZE 4

#define BM_DefaultByValBufferFormat_GET_SIZE( base_ptr, out_bytes, out_bits )\
{\
	/*lint --e{*} */\
	out_bytes = 12;\
	out_bits = 0;\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_DefaultByValBufferFormat_GET_BYTES_SIZE( base_ptr, out_bytes )\
{\
	/*lint --e{*} */\
	UINT bmlocal40_tmp_bits;\
	BM_DefaultByValBufferFormat_GET_SIZE( base_ptr, out_bytes, bmlocal40_tmp_bits );\
	BMI_ROUND_UP_1BYTES( out_bytes, bmlocal40_tmp_bits );\
}

#define BM_DefaultByValBufferFormat_BYTES_SIZE 12

#define BM_DefaultByValBufferFormat_DUMP_DEPTH( base_ptr, depth )\
{\
	/*lint --e{*} */\
	BMI_FORMAT_NONVALUE_DUMP(depth, "DefaultByValBufferFormat", 1);\
	BM_DefaultByValBufferFormat_Param1_DUMP_DEPTH( base_ptr, (depth + 1) );\
	BM_DefaultByValBufferFormat_Param2_DUMP_DEPTH( base_ptr, (depth + 1) );\
	BM_DefaultByValBufferFormat_Param3_DUMP_DEPTH( base_ptr, (depth + 1) );\
	BMI_UNUSED_VAR( base_ptr );\
}

#define BM_DefaultByValBufferFormat_DUMP( base_ptr )\
{\
	/*lint --e{*} */\
	BM_DefaultByValBufferFormat_DUMP_DEPTH( base_ptr, 0 );\
}


/*lint --flb */

#endif /* _BITMAN_DEFAULTBYVALBUFFER_H_ */

