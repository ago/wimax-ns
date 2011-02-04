/*****************************************************************************
 * Project : Bitman 2
 * Module  : BitmanCommon.h
 * Author  : Ilya Gurvich
 * Date    : 25/7/2005
 * Purpose : Define internal Bitman macros. The code automatically generated
 *           by Bitman will rely on these basic macros.
 *
 * Compliant with Bitman2 executable V3.7.9
 *****************************************************************************/

#ifndef _BITMAN_COMMON_H_
#define _BITMAN_COMMON_H_

#include <endian.h>

#if defined __ARMCC_VERSION
	#ifndef __arm
		#define __arm
	#endif
#endif

#if defined _ARC
	#ifndef __arc
		#define __arc
	#endif
#endif

#define BMI_MACHINE_ARM_LITTLE		(1)
#define BMI_MACHINE_ARM_BIG			(2)
#define BMI_MACHINE_INTEL_LITTLE	(3)

// New definitions for machine endianness
#if BYTE_ORDER == LITTLE_ENDIAN
#define BMI_ENDIANNESS_LITTLE
#elif BYTE_ORDER == BIG_ENDIAN
#define BMI_ENDIANNESS_BIG
#endif

//In case of using Microsoft compiler, disable the following level 4 warnings 
#ifdef _MSC_VER
#pragma warning(disable : 4127) //Conditional expression is constant (e.g. if(1) or while(1) etc.)
#pragma warning(disable : 4214) //Nonstandard extension used : bit field types other than int 
#pragma warning(disable : 4514) //unreferenced inline function has been removed 
#pragma warning(disable : 4213) //nonstandard extension used : cast on l-value E.g.: *(( int * )a )++ = 3;  // C4213
#endif

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION > 220000)
#pragma diag_suppress 1441
#endif

// Disabling project level lint warnings
/*lint -e537 */ /* Repeated include */

/*lint ++flb */

/* Don't disable warning e702 (warning for right shifting) yet because it can
 * be handled individually and fixed.
 */

#include "TypesProxy.h"

#ifndef NULL
#define NULL ((PVOID)0)
#endif


#ifdef _WIN64
#define MASK_1 (0xFFFFFFFFFFFFFFFF)
#define MASK_2 (0xFFFFFFFFFFFFFFFE)
#define MASK_4 (0xFFFFFFFFFFFFFFFC)
#elif __x86_64__
#define MASK_1 (0xFFFFFFFFFFFFFFFF)
#define MASK_2 (0xFFFFFFFFFFFFFFFE)
#define MASK_4 (0xFFFFFFFFFFFFFFFC)
#else
#define MASK_1 (0xFFFFFFFF)
#define MASK_2 (0xFFFFFFFE)
#define MASK_4 (0xFFFFFFFC)
#endif

#ifndef BMI_DUMP
	#ifdef _KERNEL_
		// TODO - #include <ntddk.h> ??
		#define BMI_DUMP(str)  DbgPrint(str);
	#else
		#define BMI_DUMP(str)  printf(str);
	#endif
#endif


/* The way inline functions are declared. */
// @@@ : 5/12/09 : JSS - To enable linux
#ifdef NATIVE_LINUX
#define BMI_INLINE	static inline
#else
#define BMI_INLINE	INLINE
#endif



// Bitman volatile types
#ifdef __arc
	typedef VUCINT		BVINT;
	typedef VUCINT8		BVINT8;
	typedef VUCINT16	BVINT16;
	typedef VUCINT32	BVINT32;
	typedef VUCINT64	BVINT64;

	typedef VUCUINT		BVUINT;
	typedef VUCUINT8	BVUINT8;
	typedef VUCUINT16	BVUINT16;
	typedef VUCUINT32	BVUINT32;
	typedef VUCUINT64	BVUINT64;
#else
	typedef VINT		BVINT;
	typedef VINT8		BVINT8;
	typedef VINT16		BVINT16;
	typedef VINT32		BVINT32;
	typedef VINT64		BVINT64;

	typedef VUINT		BVUINT;
	typedef VUINT8		BVUINT8;
	typedef VUINT16		BVUINT16;
	typedef VUINT32		BVUINT32;
	typedef VUINT64		BVUINT64;
#endif

typedef BVINT*		PBVINT;
typedef BVINT8*		PBVINT8;
typedef BVINT16*	PBVINT16;
typedef BVINT32*	PBVINT32;
typedef BVINT64*	PBVINT64;

typedef BVUINT*		PBVUINT;
typedef BVUINT8*	PBVUINT8;
typedef BVUINT16*	PBVUINT16;
typedef BVUINT32*	PBVUINT32;
typedef BVUINT64*	PBVUINT64;


// Cast a pointer into a numeric value, without losing any information (bits) and backwards
#define BMI_PTR_TO_NUMERIC_CAST(ptr)	((POINTER_AND_UINT)(ptr))
#define BMI_NUMBER_TO_PTR_CAST(num)		((PVOID)(num))
#define BMI_PTR_TO_BYTE_PTR_CAST(ptr)	((PUINT8)((PVOID)(ptr)))

// Get contents of pointers
#define BMI_GET_8BIT_PTR_CONTENTS(ptr)					(*((PUINT8)((PVOID)(ptr))))
#define BMI_GET_16BIT_PTR_CONTENTS(ptr)					(*((PUINT16)((PVOID)(ptr))))
#define BMI_GET_32BIT_PTR_CONTENTS(ptr)					(*((PUINT32)((PVOID)(ptr))))
// Same but volatile
#define BMI_GET_8BIT_PTR_CONTENTS_VOLATILE(ptr)			(*((PBVUINT8)((PVOID)(ptr))))
#define BMI_GET_16BIT_PTR_CONTENTS_VOLATILE(ptr)		(*((PBVUINT16)((PVOID)(ptr))))
#define BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(ptr)		(*((PBVUINT32)((PVOID)(ptr))))

// Get contents of pointers to arrays
#define BMI_GET_8BIT_PTR_CONTENTS_INDEX(ptr,index)		(*( (PUINT8)((PVOID)(ptr)) + (index) ))
#define BMI_GET_16BIT_PTR_CONTENTS_INDEX(ptr,index)		(*( (PUINT16)((PVOID)(ptr)) + (index) ))
#define BMI_GET_32BIT_PTR_CONTENTS_INDEX(ptr,index)		(*( (PUINT32)((PVOID)(ptr)) + (index) ))
// Same but volatile
#define BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(ptr,index)		(*( (PBVUINT8)((PVOID)(ptr)) + (index) ))
#define BMI_GET_16BIT_PTR_CONTENTS_INDEX_VOLATILE(ptr,index)	(*( (PBVUINT16)((PVOID)(ptr)) + (index) ))
#define BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(ptr,index)	(*( (PBVUINT32)((PVOID)(ptr)) + (index) ))

// Create a mask starting from bit 0, whose length is len. (0 to len bits)
#define BMI_8BIT_MASK(len)					((0xFF >> (8-(len))))
#define BMI_16BIT_MASK(len)					((0xFFFF >> (16-(len))))
#define BMI_32BIT_MASK(len)					((0xFFFFFFFF >> (32-(len))))

// Create a mask starting from bit pos whose length is len
#define BMI_8BIT_MASK_POSITION(len,pos)		(BMI_8BIT_MASK(len) << (pos))
#define BMI_16BIT_MASK_POSITION(len,pos)	(BMI_16BIT_MASK(len) << (pos))
#define BMI_32BIT_MASK_POSITION(len,pos)	(BMI_32BIT_MASK(len) << (pos))

// Swap the 4 bytes of a dword
#define BMI_SWAP_32BIT(x)	( ((x) >> 24) | (((x) >> 8) & 0xFF00) | (((x) << 8) & 0xFF0000) | ((x) << 24) )
// 8bit, 16bit versions not implemented

// Get len bits from val starting from bit pos, and return them starting from bit new_pos
/*#571 - Suspicious cast. cast is needed in case 'val' is an enum*/
#define BMI_8BIT_EXTRACT(val, pos, len, new_pos)								\
	( (/*lint -e(571)*/(UINT8)(BMI_8BIT_MASK(len) & (((UINT)(val)) >> (pos)))) << (new_pos) )

/*#571 - Suspicious cast. cast is needed in case 'val' is an enum*/
#define BMI_16BIT_EXTRACT(val, pos, len, new_pos)								\
	( (/*lint -e(571)*/(UINT16)(BMI_16BIT_MASK(len) & (((UINT)(val)) >> (pos)))) << (new_pos) )

/*#571 - Suspicious cast. cast is needed in case 'val' is an enum*/
#define BMI_32BIT_EXTRACT(val, pos, len, new_pos)								\
	( (/*lint -e(571)*/(UINT32)(BMI_32BIT_MASK(len) & (((UINT)(val)) >> (pos)))) << (new_pos) )

/* Assign len bits from src_value starting from src_pos bit-position
 * to dst_value starting from dst_pos.
 */

#define BMI_8BIT_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)			\
	{																			\
		(dst_value) = (UINT8)(											\
			(~(BMI_8BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_8BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}

#define BMI_16BIT_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)			\
	{																			\
		(dst_value) = (UINT16)(													\
			(~(BMI_16BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_16BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}
#define BMI_32BIT_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)			\
	{																			\
		(dst_value) = (															\
			(~(BMI_32BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}

#define BMI_32BIT_ASSIGN_TYPE(dst_value, src_value, dst_pos, src_pos, len, cast_type)\
	{																			\
		(dst_value) = (cast_type)(												\
			(~(BMI_32BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}


#define BMI_32BIT_SWAP_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)						\
	{																							\
		(dst_value) = (																			\
			( BMI_SWAP_32BIT(~(BMI_32BIT_MASK_POSITION((len), (dst_pos)))) & (dst_value)) |		\
			BMI_SWAP_32BIT( BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))	)		\
			);																					\
	}
// 8bit, 16bit versions not implemented

#define BMI_8BIT_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)	\
	{																			\
		*((PBVUINT8)(&(dst_value))) = (UINT8)(			\
			(~(BMI_8BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_8BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}
#define BMI_16BIT_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)	\
	{																			\
		*((PBVUINT16)(&(dst_value))) = (UINT16)(		\
			(~(BMI_16BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_16BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}
#define BMI_32BIT_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)	\
	{																			\
		*((PBVUINT32)(&(dst_value))) = (UINT32)(							\
			(~(BMI_32BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}

#define BMI_32BIT_ASSIGN_VOLATILE_TYPE(dst_value, src_value, dst_pos, src_pos, len, cast_type)\
	{																			\
		*((PBVUINT32)(&(dst_value))) = (cast_type)(							\
			(~(BMI_32BIT_MASK_POSITION((len), (dst_pos))) & (dst_value)) |		\
			BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))			\
			);																	\
	}

#define BMI_32BIT_SWAP_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)				\
	{																							\
		*((PBVUINT32)(&(dst_value))) = (UINT32)(											\
			( BMI_SWAP_32BIT(~(BMI_32BIT_MASK_POSITION((len), (dst_pos)))) & (dst_value)) |		\
			BMI_SWAP_32BIT( BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))	)		\
			);																					\
	}
// 8bit, 16bit versions not implemented

#define BMI_8BIT_CLEAR_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)						\
	{																							\
		(dst_value) = (UINT8)(																	\
			BMI_8BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}
#define BMI_16BIT_CLEAR_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)						\
	{																							\
		(dst_value) = (UINT16)(																	\
			BMI_16BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}
#define BMI_32BIT_CLEAR_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)						\
	{																							\
		(dst_value) = (UINT32)(																	\
			BMI_32BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}

#define BMI_32BIT_CLEAR_ASSIGN_TYPE(dst_value, src_value, dst_pos, src_pos, len, cast_type)		\
	{																							\
		(dst_value) = (cast_type)(																\
			BMI_32BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}


#define BMI_32BIT_SWAP_CLEAR_ASSIGN(dst_value, src_value, dst_pos, src_pos, len)				\
	{																							\
		(dst_value) = (																			\
			BMI_SWAP_32BIT( BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))	)		\
			);																					\
	}
// 8bit, 16bit versions not implemented

#define BMI_8BIT_CLEAR_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)				\
	{																							\
		*((PBVUINT8)(&(dst_value))) = (UINT8)(							\
			BMI_8BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}
#define BMI_16BIT_CLEAR_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)			\
	{																							\
		*((PBVUINT16)(&(dst_value))) = (UINT16)(						\
			BMI_16BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}
#define BMI_32BIT_CLEAR_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)			\
	{																							\
		*((PBVUINT32)(&(dst_value))) = (UINT32)(													\
			BMI_32BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}

#define BMI_32BIT_CLEAR_ASSIGN_VOLATILE_TYPE(dst_value, src_value, dst_pos, src_pos, len, cast_type)\
	{																							\
		*((PBVUINT32)(&(dst_value))) = (cast_type)(												\
			BMI_32BIT_EXTRACT( (src_value), (src_pos), (len), (dst_pos) )						\
			);																					\
	}


#define BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE(dst_value, src_value, dst_pos, src_pos, len)		\
	{																							\
		*((PBVUINT32)(&(dst_value))) = (UINT32)(													\
			BMI_SWAP_32BIT( BMI_32BIT_EXTRACT((src_value), (src_pos), (len), (dst_pos))	)		\
			);																					\
	}
// 8bit, 16bit versions not implemented


#define BMI_NORMALIZE_BITSIZE(size_bytes, size_bits)					\
	{																	\
		(size_bytes) += ((size_bits)>>3);								\
		(size_bits) &= 7;												\
	}

// Normalize bitoff. If it exceeds 8, ptr will be advanced the right number of times.
#define BMI_NORMALIZE_BITOFF(ptr, bitoff)								\
	{																	\
		(ptr) = (PVOID)(BMI_PTR_TO_NUMERIC_CAST(ptr) + ((bitoff)>>3));	\
		(bitoff) &= 7;													\
	}
//Same as BMI_NORMALIZE_BITOFF - the ptr here arrives as an integer 
//value, therefore using BMI_NORMALIZE_BITSIZE
//because its the same algorithm as BMI_NORMALIZE_BITOFF
#define BMI_NORMALIZE_BITOFF_NUMERIC(ptr, bitoff)						\
	{																	\
		BMI_NORMALIZE_BITSIZE((ptr), (bitoff));							\
	}															



#define BMI_ROUND_UP_4BYTES(bytes, bits)								\
	{																	\
		BMI_NORMALIZE_BITSIZE( (bytes), (bits) );						\
		/*lint -save -e774 */ /* Boolean within if always evaluates to True */		\
		if( (bits) || (bytes & 0x3) )									\
		{																\
			(bytes) = ((bytes) & MASK_4) + 4;							\
			(bits) = 0;													\
		}																\
		/*lint -restore */												\
	}
#define BMI_ROUND_UP_2BYTES(bytes, bits)								\
	{																	\
		BMI_NORMALIZE_BITSIZE( (bytes), (bits) );						\
		/*lint -save -e774 */ /* Boolean within if always evaluates to True*/		\
		if( (bits) || (bytes & 0x1) )									\
		{																\
			(bytes) = ((bytes) & MASK_2) + 2;							\
			(bits) = 0;													\
		}																\
		/*lint -restore */												\
	}
#define BMI_ROUND_UP_1BYTES(bytes, bits)								\
	{																	\
		BMI_NORMALIZE_BITSIZE( (bytes), (bits) );						\
		/*lint -save -e774 */ /* Boolean within 'if' always evaluates to True*/		\
		if( (bits) )													\
		{																\
			(bytes) += 1;												\
			(bits) = 0;													\
		}																\
		/*lint -restore */												\
	}

#define BMI_ADD_ASSIGN_PTR( ptr, byte_off )\
{\
	ptr = BMI_NUMBER_TO_PTR_CAST( BMI_PTR_TO_NUMERIC_CAST(ptr) + (byte_off) );\
}

#define BULK_OFFSET_LITTLE( bulk_size, field_size, field_offset )	(field_offset)
#define BULK_OFFSET_BIG( bulk_size, field_size, field_offset )		((bulk_size)-(field_size)-(field_offset))
/* In the follow macros the operations are not performed in a loop because we
 * assume that conditions can be optimized better (especially in case of
 * compile-time constant expressions).
 */
// always use the following macro's - this is a fix related to release mode complilation
// the macro's defined in the else might read/write to an address outside the boudaries
//#if (defined __arm) || (defined WINCE) || (defined __arc)
#if 1
#define BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off )\
	POINTER_AND_UINT new_ptr;\
	POINTER_AND_UINT ptr_byte_off;\
	POINTER_AND_UINT first_bit_pos;\
	POINTER_AND_UINT last_bit_pos;\
	\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	if( MASK_1 == byte_align_off || 0xFFFFFFFF == byte_align_off )\
	{\
		new_ptr = BMI_PTR_TO_NUMERIC_CAST((base_ptr)) & MASK_4;\
		ptr_byte_off = BMI_PTR_TO_NUMERIC_CAST((base_ptr)) & 0x03;\
		first_bit_pos = ptr_byte_off*8 + (base_bitoff);\
		last_bit_pos = first_bit_pos + (bitsize);\
	}\
	else\
	{\
		new_ptr = BMI_PTR_TO_NUMERIC_CAST((base_ptr)) - byte_align_off;\
		ptr_byte_off = byte_align_off;\
		first_bit_pos = ptr_byte_off*8 + (base_bitoff);\
		last_bit_pos = first_bit_pos + (bitsize);\
	}



#define BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off )\
	POINTER_AND_UINT new_ptr;\
	POINTER_AND_UINT ptr_byte_off;\
	POINTER_AND_UINT first_bit_pos;\
	\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	if( MASK_1 == byte_align_off )\
	{\
		new_ptr = BMI_PTR_TO_NUMERIC_CAST((base_ptr)) & MASK_2;\
		ptr_byte_off = BMI_PTR_TO_NUMERIC_CAST((base_ptr)) & 0x01;\
		first_bit_pos = ptr_byte_off*8 + (base_bitoff);\
	}\
	else\
	{\
		new_ptr = BMI_PTR_TO_NUMERIC_CAST((base_ptr)) - (byte_align_off%2);\
		ptr_byte_off = (byte_align_off%2);\
		first_bit_pos = ptr_byte_off*8 + (base_bitoff);\
	}

#else /* __arm */

#define BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off )\
	POINTER_AND_UINT new_ptr;\
	UINT first_bit_pos;\
	UINT last_bit_pos;\
	\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	new_ptr = BMI_PTR_TO_NUMERIC_CAST((base_ptr));\
	first_bit_pos = (base_bitoff);\
	last_bit_pos = first_bit_pos + (bitsize);

#define BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off )\
	POINTER_AND_UINT new_ptr;\
	UINT first_bit_pos;\
	\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	new_ptr = BMI_PTR_TO_NUMERIC_CAST((base_ptr));\
	first_bit_pos = (base_bitoff);

#endif /* else __arm */


#define BMI_GENERIC_GET_LITTLE_NATIVE( base_ptr, base_bitoff, bitsize, cast_type, out_val )\
{\
	UINT last_bit_pos;\
\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
\
	last_bit_pos = bitsize + base_bitoff;\
\
	if( last_bit_pos > 8 )\
	{\
		UINT cur_pos, cur_len;\
		UINT byte_index=0;\
\
		/* 1st byte - first and middle*/ \
		cur_pos = 0;\
		cur_len = 8-base_bitoff;\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,0), base_bitoff, cur_len, cur_pos);\
		cur_pos += cur_len;\
\
		if( last_bit_pos > 16 )\
		{\
			/* 2nd byte - middle */\
			cur_len = 8;\
			(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,1), 0, cur_len, cur_pos));\
			cur_pos += cur_len;\
\
			if( last_bit_pos > 24 )\
			{\
				/* 3rd byte - middle */\
				cur_len = 8;\
				(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,2), 0, cur_len, cur_pos));\
				cur_pos += cur_len;\
\
                if( last_bit_pos > 32 )\
				{\
					/* 4th byte - middle */\
					cur_len = 8;\
					(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,3), 0, cur_len, cur_pos));\
					cur_pos += cur_len;\
\
					byte_index = 4;\
				}\
				else\
				{\
					byte_index = 3;\
				}\
			}\
			else\
			{\
				byte_index = 2;\
			}\
		}\
		else\
		{\
			byte_index = 1;\
		}\
\
		/* (byte_index)-byte - last */\
		cur_len = bitsize-cur_pos;\
		(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,byte_index), 0, cur_len, cur_pos));\
\
	}\
	else\
	{\
		/* 1st byte - first and last */\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,0), base_bitoff, bitsize, 0);\
	}\
}\

#define BMI_GENERIC_SET_LITTLE_NATIVE( base_ptr, base_bitoff, bitsize, in_val )\
{\
	UINT last_bit_pos;\
	UINT my_bitsize = bitsize; /* No additional functionality here, but eliminates ARM compiler warnings */ \
\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
\
	last_bit_pos = my_bitsize + base_bitoff;\
\
	if( last_bit_pos > 8 )\
	{\
		UINT cur_pos, cur_len;\
		UINT byte_index=0;\
\
		/* 1st byte - first and middle*/ \
		cur_pos = 0;\
		cur_len = 8-base_bitoff;\
		BMI_8BIT_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,0), (in_val), base_bitoff, cur_pos, cur_len);\
		cur_pos += cur_len;\
\
		if( last_bit_pos > 16 )\
		{\
			/* 2nd byte - middle */\
			cur_len = 8;\
			BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,1), (in_val), 0, cur_pos, cur_len);\
			cur_pos += cur_len;\
\
			if( last_bit_pos > 24 )\
			{\
				/* 3rd byte - middle */\
				cur_len = 8;\
				BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,2), (in_val), 0, cur_pos, cur_len);\
				cur_pos += cur_len;\
\
                if( last_bit_pos > 32 )\
				{\
					/* 4th byte - middle */\
					cur_len = 8;\
					BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,3), (in_val), 0, cur_pos, cur_len);\
					cur_pos += cur_len;\
\
					byte_index = 4;\
				}\
				else\
				{\
					byte_index = 3;\
				}\
			}\
			else\
			{\
				byte_index = 2;\
			}\
		}\
		else\
		{\
			byte_index = 1;\
		}\
\
		/* (byte_index)-byte - last */\
		cur_len = my_bitsize-cur_pos;\
		BMI_8BIT_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,byte_index), (in_val), 0, cur_pos, cur_len);\
	}\
	else\
	{\
		/* 1st byte - first and last */\
		BMI_8BIT_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,0), (in_val), base_bitoff, 0, my_bitsize);\
	}\
}\

#define BMI_GENERIC_CLEAR_LITTLE_NATIVE( base_ptr, base_bitoff, bitsize, in_val )\
{\
	UINT last_bit_pos;\
	UINT my_bitsize = bitsize; /* No additional functionality here, but eliminates ARM compiler warnings */ \
\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
\
	last_bit_pos = my_bitsize + base_bitoff;\
\
	if( last_bit_pos > 8 )\
	{\
		UINT cur_pos, cur_len;\
		UINT byte_index=0;\
\
		/* 1st byte - first and middle*/ \
		cur_pos = 0;\
		cur_len = 8-base_bitoff;\
		BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,0), (in_val), base_bitoff, cur_pos, cur_len);\
		cur_pos += cur_len;\
\
		if( last_bit_pos > 16 )\
		{\
			/* 2nd byte - middle */\
			cur_len = 8;\
			BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,1), (in_val), 0, cur_pos, cur_len);\
			cur_pos += cur_len;\
\
			if( last_bit_pos > 24 )\
			{\
				/* 3rd byte - middle */\
				cur_len = 8;\
				BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,2), (in_val), 0, cur_pos, cur_len);\
				cur_pos += cur_len;\
\
                if( last_bit_pos > 32 )\
				{\
					/* 4th byte - middle */\
					cur_len = 8;\
					BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,3), (in_val), 0, cur_pos, cur_len);\
					cur_pos += cur_len;\
\
					byte_index = 4;\
				}\
				else\
				{\
					byte_index = 3;\
				}\
			}\
			else\
			{\
				byte_index = 2;\
			}\
		}\
		else\
		{\
			byte_index = 1;\
		}\
\
		/* (byte_index)-byte - last */\
		cur_len = my_bitsize-cur_pos;\
		BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,byte_index), (in_val), 0, cur_pos, cur_len);\
	}\
	else\
	{\
		/* 1st byte - first and last */\
		BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS_INDEX(base_ptr,0), (in_val), base_bitoff, 0, my_bitsize);\
	}\
}\

//////////////////////////////////////////////////////////////////////////
#define BMI_GENERIC_GET_LITTLE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, cast_type, out_val )\
{\
	UINT last_bit_pos;\
\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
\
	last_bit_pos = bitsize + base_bitoff;\
\
	if( last_bit_pos > 8 )\
	{\
		UINT cur_pos, cur_len;\
		UINT byte_index=0;\
\
		/* 1st byte - first and middle*/ \
		cur_pos = 0;\
		cur_len = 8-base_bitoff;\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,0), base_bitoff, cur_len, cur_pos);\
		cur_pos += cur_len;\
\
		if( last_bit_pos > 16 )\
		{\
			/* 2nd byte - middle */\
			cur_len = 8;\
			(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,1), 0, cur_len, cur_pos));\
			cur_pos += cur_len;\
\
			if( last_bit_pos > 24 )\
			{\
				/* 3rd byte - middle */\
				cur_len = 8;\
				(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,2), 0, cur_len, cur_pos));\
				cur_pos += cur_len;\
\
                if( last_bit_pos > 32 )\
				{\
					/* 4th byte - middle */\
					cur_len = 8;\
					(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,3), 0, cur_len, cur_pos));\
					cur_pos += cur_len;\
\
					byte_index = 4;\
				}\
				else\
				{\
					byte_index = 3;\
				}\
			}\
			else\
			{\
				byte_index = 2;\
			}\
		}\
		else\
		{\
			byte_index = 1;\
		}\
\
		/* (byte_index)-byte - last */\
		cur_len = bitsize-cur_pos;\
		(out_val) = (cast_type)(out_val | BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,byte_index), 0, cur_len, cur_pos));\
\
	}\
	else\
	{\
		/* 1st byte - first and last */\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,0), base_bitoff, bitsize, 0);\
	}\
}\

#define BMI_GENERIC_SET_LITTLE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, in_val )\
{\
	UINT last_bit_pos;\
	UINT my_bitsize = bitsize; /* No additional functionality here, but eliminates ARM compiler warnings */ \
\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
\
	last_bit_pos = my_bitsize + base_bitoff;\
\
	if( last_bit_pos > 8 )\
	{\
		UINT cur_pos, cur_len;\
		UINT byte_index=0;\
\
		/* 1st byte - first and middle*/ \
		cur_pos = 0;\
		cur_len = 8-base_bitoff;\
		BMI_8BIT_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,0), (in_val), base_bitoff, cur_pos, cur_len);\
		cur_pos += cur_len;\
\
		if( last_bit_pos > 16 )\
		{\
			/* 2nd byte - middle */\
			cur_len = 8;\
			BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,1), (in_val), 0, cur_pos, cur_len);\
			cur_pos += cur_len;\
\
			if( last_bit_pos > 24 )\
			{\
				/* 3rd byte - middle */\
				cur_len = 8;\
				BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,2), (in_val), 0, cur_pos, cur_len);\
				cur_pos += cur_len;\
\
                if( last_bit_pos > 32 )\
				{\
					/* 4th byte - middle */\
					cur_len = 8;\
					BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,3), (in_val), 0, cur_pos, cur_len);\
					cur_pos += cur_len;\
\
					byte_index = 4;\
				}\
				else\
				{\
					byte_index = 3;\
				}\
			}\
			else\
			{\
				byte_index = 2;\
			}\
		}\
		else\
		{\
			byte_index = 1;\
		}\
\
		/* (byte_index)-byte - last */\
		cur_len = my_bitsize-cur_pos;\
		BMI_8BIT_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,byte_index), (in_val), 0, cur_pos, cur_len);\
	}\
	else\
	{\
		/* 1st byte - first and last */\
		BMI_8BIT_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,0), (in_val), base_bitoff, 0, my_bitsize);\
	}\
}\

#define BMI_GENERIC_CLEAR_LITTLE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, in_val )\
{\
	UINT last_bit_pos;\
	UINT my_bitsize = bitsize; /* No additional functionality here, but eliminates ARM compiler warnings */ \
\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
\
	last_bit_pos = my_bitsize + base_bitoff;\
\
	if( last_bit_pos > 8 )\
	{\
		UINT cur_pos, cur_len;\
		UINT byte_index=0;\
\
		/* 1st byte - first and middle*/ \
		cur_pos = 0;\
		cur_len = 8-base_bitoff;\
		BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,0), (in_val), base_bitoff, cur_pos, cur_len);\
		cur_pos += cur_len;\
\
		if( last_bit_pos > 16 )\
		{\
			/* 2nd byte - middle */\
			cur_len = 8;\
			BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,1), (in_val), 0, cur_pos, cur_len);\
			cur_pos += cur_len;\
\
			if( last_bit_pos > 24 )\
			{\
				/* 3rd byte - middle */\
				cur_len = 8;\
				BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,2), (in_val), 0, cur_pos, cur_len);\
				cur_pos += cur_len;\
\
                if( last_bit_pos > 32 )\
				{\
					/* 4th byte - middle */\
					cur_len = 8;\
					BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,3), (in_val), 0, cur_pos, cur_len);\
					cur_pos += cur_len;\
\
					byte_index = 4;\
				}\
				else\
				{\
					byte_index = 3;\
				}\
			}\
			else\
			{\
				byte_index = 2;\
			}\
		}\
		else\
		{\
			byte_index = 1;\
		}\
\
		/* (byte_index)-byte - last */\
		cur_len = my_bitsize-cur_pos;\
		BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,byte_index), (in_val), 0, cur_pos, cur_len);\
	}\
	else\
	{\
		/* 1st byte - first and last */\
		BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_INDEX_VOLATILE(base_ptr,0), (in_val), base_bitoff, 0, my_bitsize);\
	}\
}\

// prev BMI_GENERIC_32BIT_GET_GRANULARITY_32BIT_LITTLE
#define BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_NATIVE( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), first_bit_pos, (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0), first_bit_pos, 32-first_bit_pos, 0);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1), 0, last_bit_pos-32, 32-first_bit_pos));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), first_bit_pos, (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), first_bit_pos, 32-first_bit_pos, 0);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), 0, last_bit_pos-32, 32-first_bit_pos));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// Derived from BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_LITTLE
// prev BMI_GENERIC_32BIT_GET_GRANULARITY_32BIT_LITTLE_ON_BIG_MACHINE
#define BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS(new_ptr)), first_bit_pos, (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0)), first_bit_pos, 32-first_bit_pos, 0);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1)), 0, last_bit_pos-32, 32-first_bit_pos));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP_VOLATILE( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr)), first_bit_pos, (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0)), first_bit_pos, 32-first_bit_pos, 0);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1)), 0, last_bit_pos-32, 32-first_bit_pos));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// prev BMI_GENERIC_32BIT_GET_GRANULARITY_32BIT_BIG
#define BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), 32-first_bit_pos-(bitsize), (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{/* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0), 0, 32-first_bit_pos, last_bit_pos-32);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1), 64-last_bit_pos, last_bit_pos-32, 0));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), 32-first_bit_pos-(bitsize), (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{/* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), 0, 32-first_bit_pos, last_bit_pos-32);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), 64-last_bit_pos, last_bit_pos-32, 0));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// Derived from BMI_GENERIC_32BIT_GET_GRANULARITY_32BIT_BIG
// prev BMI_GENERIC_32BIT_GET_GRANULARITY_32BIT_BIG_ON_LITTLE_MACHINE
#define BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS(new_ptr)), 32-first_bit_pos-(bitsize), (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{ /* ILYA BUG FIX: 22/3/2005: Changed the last parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0)), 0, 32-first_bit_pos, last_bit_pos-32);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1)), 64-last_bit_pos, last_bit_pos-32, 0));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP_VOLATILE( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr)), 32-first_bit_pos-(bitsize), (bitsize), 0);\
	}\
	else /* last_bit_pos = 32 */\
	{ /* ILYA BUG FIX: 22/3/2005: Changed the last parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		(out_val) = (cast_type)BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0)), 0, 32-first_bit_pos, last_bit_pos-32);\
		(out_val) = (cast_type)((/*lint -e(571)*/(UINT32)out_val) | BMI_32BIT_EXTRACT( BMI_SWAP_32BIT(BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1)), 64-last_bit_pos, last_bit_pos-32, 0));\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// prev BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_LITTLE
#define BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_NATIVE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_CLEAR_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{\
		BMI_32BIT_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0), (in_val), first_bit_pos, 0, 32-first_bit_pos);\
		BMI_32BIT_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1), (in_val), 0, 32-first_bit_pos, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{\
		BMI_32BIT_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), first_bit_pos, 0, 32-first_bit_pos);\
		BMI_32BIT_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 0, 32-first_bit_pos, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}


#define BMI_GENERIC_32BIT_CLEAR_LITTLE_MACHINE_NATIVE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), first_bit_pos, 0, 32-first_bit_pos);\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 0, 32-first_bit_pos, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// Derived from BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_LITTLE
// prev BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_LITTLE_ON_BIG_MACHINE
#define BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_SWAP_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{\
		BMI_32BIT_SWAP_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0), (in_val), first_bit_pos, 0, 32-first_bit_pos);\
		BMI_32BIT_SWAP_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1), (in_val), 0, 32-first_bit_pos, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP_VOLATILE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_SWAP_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{\
		BMI_32BIT_SWAP_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), first_bit_pos, 0, 32-first_bit_pos);\
		BMI_32BIT_SWAP_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 0, 32-first_bit_pos, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}


#define BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_SWAP( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), first_bit_pos, 0, 32-first_bit_pos);\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 0, 32-first_bit_pos, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// prev BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_BIG
#define BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_CLEAR_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{/* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		BMI_32BIT_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0), (in_val), 0, last_bit_pos-32, 32-first_bit_pos);\
		BMI_32BIT_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1), (in_val), 64-last_bit_pos, 0, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE_VOLATILE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{/* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		BMI_32BIT_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), 0, last_bit_pos-32, 32-first_bit_pos);\
		BMI_32BIT_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 64-last_bit_pos, 0, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}



#define BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_NATIVE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{/* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), 0, last_bit_pos-32, 32-first_bit_pos);\
		BMI_32BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 64-last_bit_pos, 0, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
}


// Derived from BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_BIG
// prev BMI_GENERIC_32BIT_SET_GRANULARITY_32BIT_BIG_ON_LITTLE_MACHINE
#define BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within 'if' always evaluates to false*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_SWAP_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{ /* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		BMI_32BIT_SWAP_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,0), (in_val), 0, last_bit_pos-32, 32-first_bit_pos);\
		BMI_32BIT_SWAP_ASSIGN( BMI_GET_32BIT_PTR_CONTENTS_INDEX(new_ptr,1), (in_val), 64-last_bit_pos, 0, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP_VOLATILE( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e506 */ /* Constant value boolean*/\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (first_bit_pos == 0) && ((bitsize) == 32) )\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_SWAP_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{ /* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		BMI_32BIT_SWAP_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), 0, last_bit_pos-32, 32-first_bit_pos);\
		BMI_32BIT_SWAP_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 64-last_bit_pos, 0, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
	/*lint -restore */\
}

#define BMI_GENERIC_32BIT_CLEAR_LITTLE_MACHINE_SWAP( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	/*lint -save -e774 */ /* Boolean within if always evaluates to True*/\
	/*lint -save -e778 */ /* Constant expression evaluates to 0 in operation e.g.: x << ((32) - (32))*/\
	BMI_COMMON_32BIT_ADDRESS_CALC( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( last_bit_pos <= 32 )\
	{\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), 32-first_bit_pos-(bitsize), 0, (bitsize));\
	}\
	else /* last_bit_pos > 32 */\
	{ /* ILYA BUG FIX: 22/3/2005: Changed a parameter from (first_bit_pos) to (last_bit_pos-32) */ \
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,0), (in_val), 0, last_bit_pos-32, 32-first_bit_pos);\
		BMI_32BIT_SWAP_CLEAR_ASSIGN_VOLATILE( BMI_GET_32BIT_PTR_CONTENTS_INDEX_VOLATILE(new_ptr,1), (in_val), 64-last_bit_pos, 0, last_bit_pos-32);\
	}\
	/*lint -restore */\
	/*lint -restore */\
}
//////////////////////////////////////////////////////////////////////////
// 8BIT MACROs

#define BMI_GENERIC_8BIT_GET_LITTLE_MACHINE_NATIVE_NOSPAN( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	(out_val) = (cast_type)BMI_8BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS((base_ptr)), (base_bitoff), (bitsize), 0 );\
}

#define BMI_GENERIC_8BIT_SET_LITTLE_MACHINE_NATIVE_NOSPAN( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	if( (bitsize) == 8 )\
	{\
		BMI_8BIT_CLEAR_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS((base_ptr)), (in_val), (base_bitoff), 0, (bitsize) );\
	}\
	else /* else if( (bitsize) < 8 ) */\
	{\
		BMI_8BIT_ASSIGN( BMI_GET_8BIT_PTR_CONTENTS((base_ptr)), (in_val), (base_bitoff), 0, (bitsize) );\
	}\
}

#define BMI_GENERIC_8BIT_CLEAR_LITTLE_MACHINE_NATIVE_NOSPAN( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_VOLATILE((base_ptr)), (in_val), (base_bitoff), 0, (bitsize) );\
}

#define BMI_GENERIC_8BIT_GET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	(out_val) = (cast_type)BMI_8BIT_EXTRACT( BMI_GET_8BIT_PTR_CONTENTS_VOLATILE((base_ptr)), (base_bitoff), (bitsize), 0 );\
}

#define BMI_GENERIC_8BIT_SET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	BMI_NORMALIZE_BITOFF( (base_ptr), (base_bitoff) );\
	\
	if( (bitsize) == 8 )\
	{\
		BMI_8BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_VOLATILE((base_ptr)), (in_val), (base_bitoff), 0, (bitsize) );\
	}\
	else /* else if( (bitsize) < 8 ) */\
	{\
		BMI_8BIT_ASSIGN_VOLATILE( BMI_GET_8BIT_PTR_CONTENTS_VOLATILE((base_ptr)), (in_val), (base_bitoff), 0, (bitsize) );\
	}\
}

//////////////////////////////////////////////////////////////////////////
// 16BIT MACROs

#define BMI_GENERIC_16BIT_GET_LITTLE_MACHINE_NATIVE_NOSPAN( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	(out_val) = (cast_type)BMI_16BIT_EXTRACT( BMI_GET_16BIT_PTR_CONTENTS(new_ptr), (first_bit_pos), (bitsize), 0 );\
}

#define BMI_GENERIC_16BIT_SET_LITTLE_MACHINE_NATIVE_NOSPAN( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	if( (bitsize) == 16 )\
	{\
		BMI_16BIT_CLEAR_ASSIGN( BMI_GET_16BIT_PTR_CONTENTS(new_ptr), (in_val), first_bit_pos, 0, (bitsize) );\
	}\
	else /* else if( (bitsize) < 16 ) */\
	{\
		BMI_16BIT_ASSIGN( BMI_GET_16BIT_PTR_CONTENTS(new_ptr), (in_val), first_bit_pos, 0, (bitsize) );\
	}\
}

#define BMI_GENERIC_16BIT_CLEAR_LITTLE_MACHINE_NATIVE_NOSPAN( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	BMI_16BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_16BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize) );\
}

#define BMI_GENERIC_16BIT_GET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN( base_ptr, base_bitoff, bitsize, cast_type, out_val, byte_align_off )\
{\
	BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	(out_val) = (cast_type)BMI_16BIT_EXTRACT( BMI_GET_16BIT_PTR_CONTENTS_VOLATILE(new_ptr), first_bit_pos, (bitsize), 0 );\
}

#define BMI_GENERIC_16BIT_SET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN( base_ptr, base_bitoff, bitsize, in_val, byte_align_off )\
{\
	BMI_COMMON_16BIT_ADDRESS_CALC_NOSPAN( base_ptr, base_bitoff, bitsize, byte_align_off );\
	\
	/*lint -e{506} -e{774} */\
	if( (bitsize) == 16 )\
	{\
		BMI_16BIT_CLEAR_ASSIGN_VOLATILE( BMI_GET_16BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize) );\
	}\
	else /* else if( (bitsize) < 16 ) */\
	{\
		BMI_16BIT_ASSIGN_VOLATILE( BMI_GET_16BIT_PTR_CONTENTS_VOLATILE(new_ptr), (in_val), first_bit_pos, 0, (bitsize) );\
	}\
}

#if defined BMI_ENDIANNESS_LITTLE

	#if (defined __arm || defined __arc)
		#define BMI_MACHINE_VALUE (BMI_MACHINE_ARM_LITTLE)
	#else
		#define BMI_MACHINE_VALUE (BMI_MACHINE_INTEL_LITTLE)
	#endif

	/* 32BIT SPAN-ENABLED GENERIC ---------------------------- */
	/* NON-VOLATILE macros */
	#define BMI_GENERIC_32BIT_BIG_GET					BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_32BIT_BIG_SET					BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_32BIT_LITTLE_GET				BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_NATIVE
	#define BMI_GENERIC_32BIT_LITTLE_SET				BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_NATIVE

	/* VOLATILE macros */
	#define BMI_GENERIC_32BIT_BIG_GET_VOLATILE			BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_32BIT_BIG_SET_VOLATILE			BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_32BIT_LITTLE_GET_VOLATILE		BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_32BIT_LITTLE_SET_VOLATILE		BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_NATIVE_VOLATILE

	/* The following CLEAR macros are volatile */
	#define BMI_GENERIC_32BIT_BIG_CLEAR					BMI_GENERIC_32BIT_CLEAR_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_32BIT_LITTLE_CLEAR				BMI_GENERIC_32BIT_CLEAR_LITTLE_MACHINE_NATIVE

	/* 8BIT NOSPAN ------------------------------------------- */
	/* NON-VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_8BIT_BIG_GET_NOSPAN				BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_8BIT_BIG_SET_NOSPAN				BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_8BIT_LITTLE_GET_NOSPAN			BMI_GENERIC_8BIT_GET_LITTLE_MACHINE_NATIVE_NOSPAN
	#define BMI_GENERIC_8BIT_LITTLE_SET_NOSPAN			BMI_GENERIC_8BIT_SET_LITTLE_MACHINE_NATIVE_NOSPAN

	/* VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_8BIT_BIG_GET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_8BIT_BIG_SET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_8BIT_LITTLE_GET_VOLATILE_NOSPAN	BMI_GENERIC_8BIT_GET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN
	#define BMI_GENERIC_8BIT_LITTLE_SET_VOLATILE_NOSPAN	BMI_GENERIC_8BIT_SET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN

	/* The following CLEAR macros are volatile */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_8BIT_BIG_CLEAR_NOSPAN			BMI_GENERIC_32BIT_CLEAR_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_8BIT_LITTLE_CLEAR_NOSPAN		BMI_GENERIC_8BIT_CLEAR_LITTLE_MACHINE_NATIVE_NOSPAN

	/* 16BIT NOSPAN ------------------------------------------- */
	/* NON-VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 16 ==>> 32 */
	#define BMI_GENERIC_16BIT_BIG_GET_NOSPAN				BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_16BIT_BIG_SET_NOSPAN				BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_16BIT_LITTLE_GET_NOSPAN				BMI_GENERIC_16BIT_GET_LITTLE_MACHINE_NATIVE_NOSPAN
	#define BMI_GENERIC_16BIT_LITTLE_SET_NOSPAN				BMI_GENERIC_16BIT_SET_LITTLE_MACHINE_NATIVE_NOSPAN

	/* VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_16BIT_BIG_GET_VOLATILE_NOSPAN		BMI_GENERIC_32BIT_GET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_16BIT_BIG_SET_VOLATILE_NOSPAN		BMI_GENERIC_32BIT_SET_LITTLE_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_16BIT_LITTLE_GET_VOLATILE_NOSPAN	BMI_GENERIC_16BIT_GET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN
	#define BMI_GENERIC_16BIT_LITTLE_SET_VOLATILE_NOSPAN	BMI_GENERIC_16BIT_SET_LITTLE_MACHINE_NATIVE_VOLATILE_NOSPAN

	/* The following CLEAR macros are volatile */
	/* TEMPORARY IMPLEMENTATION 16 ==>> 32 */
	#define BMI_GENERIC_16BIT_BIG_CLEAR_NOSPAN				BMI_GENERIC_32BIT_CLEAR_LITTLE_MACHINE_SWAP
	#define BMI_GENERIC_16BIT_LITTLE_CLEAR_NOSPAN			BMI_GENERIC_16BIT_CLEAR_LITTLE_MACHINE_NATIVE_NOSPAN

#elif defined BMI_ENDIANNESS_BIG

	#define BMI_MACHINE_VALUE (BMI_MACHINE_ARM_BIG)

	/* NON-VOLATILE macros */
	#define BMI_GENERIC_32BIT_BIG_GET					BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_32BIT_BIG_SET					BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_32BIT_LITTLE_GET				BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP
	#define BMI_GENERIC_32BIT_LITTLE_SET				BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP

	/* VOLATILE macros */
	#define BMI_GENERIC_32BIT_BIG_GET_VOLATILE			BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_32BIT_BIG_SET_VOLATILE			BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_32BIT_LITTLE_GET_VOLATILE		BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_32BIT_LITTLE_SET_VOLATILE		BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP_VOLATILE

	/* The following CLEAR macros are volatile */
	#define BMI_GENERIC_32BIT_BIG_CLEAR					BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_32BIT_LITTLE_CLEAR				BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_SWAP

	/* 8BIT NOSPAN ------------------------------------------- */
	/* NON-VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_8BIT_BIG_GET_NOSPAN				BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_8BIT_BIG_SET_NOSPAN				BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_8BIT_LITTLE_GET_NOSPAN			BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP
	#define BMI_GENERIC_8BIT_LITTLE_SET_NOSPAN			BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP

	/* VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_8BIT_BIG_GET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_8BIT_BIG_SET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_8BIT_LITTLE_GET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_8BIT_LITTLE_SET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP_VOLATILE

	/* The following CLEAR macros are volatile */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_8BIT_BIG_CLEAR_NOSPAN			BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_8BIT_LITTLE_CLEAR_NOSPAN		BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_SWAP

	/* 16BIT NOSPAN ------------------------------------------- */
	/* NON-VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_16BIT_BIG_GET_NOSPAN				BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_16BIT_BIG_SET_NOSPAN				BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_16BIT_LITTLE_GET_NOSPAN				BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP
	#define BMI_GENERIC_16BIT_LITTLE_SET_NOSPAN				BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP

	/* VOLATILE macros */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_16BIT_BIG_GET_VOLATILE_NOSPAN		BMI_GENERIC_32BIT_GET_BIG_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_16BIT_BIG_SET_VOLATILE_NOSPAN		BMI_GENERIC_32BIT_SET_BIG_MACHINE_NATIVE_VOLATILE
	#define BMI_GENERIC_16BIT_LITTLE_GET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_GET_BIG_MACHINE_SWAP_VOLATILE
	#define BMI_GENERIC_16BIT_LITTLE_SET_VOLATILE_NOSPAN	BMI_GENERIC_32BIT_SET_BIG_MACHINE_SWAP_VOLATILE

	/* The following CLEAR macros are volatile */
	/* TEMPORARY IMPLEMENTATION 8 ==>> 32 */
	#define BMI_GENERIC_16BIT_BIG_CLEAR_NOSPAN				BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_NATIVE
	#define BMI_GENERIC_16BIT_LITTLE_CLEAR_NOSPAN			BMI_GENERIC_32BIT_CLEAR_BIG_MACHINE_SWAP

#else
	#error The target processor endianness must be specified (BMI_MACHINE_ENDIANNESS_LITTLE/BIG. Note that BMI_ENDIANNESS_LITTLE/BIG is obsolete).
#endif

//////////////////////////////////////////////////////////////////////////
// Prototypes for functions in BitmanCommon.c
void BMI_GET_BIG_TLV_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	PUINT puiout_length_of_length,
	PUINT out_length,
	PUINT out_error_value );

void BMI_GET_LITTLE_TLV_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	PUINT puiout_length_of_length,
	PUINT out_length,
	PUINT out_error_value );

void BMI_SET_BIG_TLV_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	UINT length_of_length,
	UINT length );

void BMI_SET_LITTLE_TLV_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	UINT length_of_length,
	UINT length );


void BMI_GET_BIG_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	PUINT out_length,
	PUINT out_error_value );

void BMI_GET_LITTLE_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	PUINT out_length,
	PUINT out_error_value );

void BMI_SET_BIG_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	UINT length );

void BMI_SET_LITTLE_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	UINT length );


void BMI_FORMAT_DUMP( UINT level, PSTR name, UINT size_bits, UINT value, PCSTR val_format, BOOL addnewline );
void BMI_STR_DUMP( UINT level, PSTR name, PSTR value, BOOL addnewline );
void BMI_FORMAT_NONVALUE_DUMP( UINT level, PSTR name, BOOL addnewline );

//////////////////////////////////////////////////////////////////////////
//#ifdef __arm
//	/* The following macro was previously declared as { (x) = (x); }.
//	 * It was changed to allow treating constants as unused variables.
//	 * The previous declaration resulted in an "invalid l-value" error
//	 * because it's impossible to assign a constant into a constant.
//	 */
//	#define BMI_UNUSED_VAR(x)	{ INT tmp; tmp = (INT)(x); tmp = tmp; }
//#else
//	/* We had a problem disabling lint warning 522 for the next statement
//	 * using the "lint -e(522)" syntax. Lint had simply ignored it.
//	 */
//	#define BMI_UNUSED_VAR(x)	{  /*lint -e522*/ (x); /*lint +e522*/ }
//#endif

//#define BMI_UNUSED_VAR(x)	{INT tmp; tmp = (INT)(x); tmp = tmp; }
#define BMI_UNUSED_VAR(x)	{POINTER_AND_UINT tmp; tmp = (POINTER_AND_UINT)(x); tmp = tmp; }

//////////////////////////////////////////////////////////////////////////
// TLV Related structures
typedef struct
{
	PVOID ptr;
	UINT bitoff;
} BMI_tlv_buf_cell;

//////////////////////////////////////////////////////////////////////////
// Errors
#define BM_ERROR_SUCCESS						(0)
#define BM_ERROR_TLV_TOO_LONG_LENGTH			(1)
#define BM_ERROR_TLV_UNKNOWN_TYPE				(2)
#define BM_ERROR_TLV_ZERO_LENGTH				(3)

#define BMI_ASSERT( x )

/*lint --flb */

#endif /* _BITMAN_COMMON_H_ */

/* Leave the next new line (at the end of file) to avoid RVDS/ADS compiler warning */


