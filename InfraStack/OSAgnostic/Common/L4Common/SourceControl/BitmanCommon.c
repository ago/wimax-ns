/*****************************************************************************
 * Project : Bitman 2
 * Module  : BitmanCommon.c
 * Author  : Ilya Gurvich
 * Date    : 25/7/2005
 * Purpose : Declare internal Bitman functions. The code automatically generated
 *           by Bitman will rely on these basic functions.
 *
 * Compliant with Bitman2 executable V3.7.9
 *****************************************************************************/

#include "BitmanCommon.h"

#if (!defined __arm && !defined __arc)
#include <stdio.h>
#endif


void BMI_GET_LITTLE_TLV_LENGTH(
		PVOID cur_ptr,
		UINT cur_bitoff,
		PUINT out_length_of_length,
		PUINT out_length,
		PUINT out_error_value )
{
	/*lint --e{*} */

	// The first TLV Length byte
	UINT8 first_byte;

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 8;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( NULL != out_error_value );

	// Set the invalid flag to false
	*out_error_value = BM_ERROR_SUCCESS;

	// Read the first TLV Length byte
	tmp_ptr = ((PUINT8)cur_ptr + 1);
	tmp_bitoff = cur_bitoff;
	BMI_GENERIC_32BIT_LITTLE_GET( tmp_ptr, tmp_bitoff, bitSize, UINT8, first_byte, MASK_1 );

	// Do we have the MSB set?
	if( first_byte & 0x80 )
	{
		// Remove the MSB
		first_byte &= 0x7F;

		// It's important to put the if condition here, before the
		// BM_ERROR_TLV_TOO_LONG_LENGTH check because we don't care about the error
		// condition at this stage.
		if( NULL != out_length_of_length )
		{
			*out_length_of_length = first_byte+1;
		}

		// Is the length of the length is longer than 4 bytes?
		// In this case the length of the contents would have to be bigger
		// than 4GB.
		if( first_byte > 4 )
		{
			// Set the invalid flag and return.
			*out_error_value = BM_ERROR_TLV_TOO_LONG_LENGTH;
			return;
		}

		if( NULL != out_length  )
		{
			// Read the actual length of the contents into the output variable.
			tmp_ptr = ((PUINT8)cur_ptr + 2);
			tmp_bitoff = cur_bitoff;
			BMI_GENERIC_32BIT_LITTLE_GET( tmp_ptr, tmp_bitoff, first_byte*8, UINT32, (*out_length), MASK_1 );
		}
	}
	else
	{
		// The length (including the zero-set MSB) is the returned length.
		if( NULL != out_length_of_length )
		{
			*out_length_of_length = 1;
		}

		if( NULL != out_length )
		{
			*out_length = first_byte;
		}
	}

	if( NULL != out_length  )
	{
		if (*out_length == 0 )
		{
			// Set the invalid flag and return.
			*out_error_value = BM_ERROR_TLV_ZERO_LENGTH;
		}
	}
}

void BMI_GET_BIG_TLV_LENGTH(
		PVOID cur_ptr,
		UINT cur_bitoff,
		PUINT out_length_of_length,
		PUINT out_length,
		PUINT out_error_value )
{
	/*lint --e{*} */

	// The first TLV Length byte
	UINT8 first_byte;

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 8;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( NULL != out_error_value );

	// Set the invalid flag to false
	*out_error_value = BM_ERROR_SUCCESS;

	// Read the first TLV Length byte
	tmp_ptr = ((PUINT8)cur_ptr + 1);
	tmp_bitoff = cur_bitoff;
	BMI_GENERIC_32BIT_BIG_GET( tmp_ptr, tmp_bitoff, bitSize, UINT8, first_byte, MASK_1 );

	// Do we have the MSB set?
	if( first_byte & 0x80 )
	{
		// Remove the MSB
		first_byte &= 0x7F;

		// It's important to put the if condition here, before the
		// BM_ERROR_TLV_TOO_LONG_LENGTH check because we don't care about the error
		// condition at this stage.
		if( NULL != out_length_of_length )
		{
			*out_length_of_length = first_byte+1;
		}

		// Is the length of the length is longer than 4 bytes?
		// In this case the length of the contents would have to be bigger
		// than 4GB.
		if( first_byte > 4 )
		{
			// Set the invalid flag and return.
			*out_error_value = BM_ERROR_TLV_TOO_LONG_LENGTH;
			return;
		}

		if( NULL != out_length  )
		{
			// Read the actual length of the contents into the output variable.
			tmp_ptr = (PUINT8)cur_ptr + 2;
			tmp_bitoff = cur_bitoff;
			BMI_GENERIC_32BIT_BIG_GET( tmp_ptr, tmp_bitoff, first_byte*8, UINT32, (*out_length), MASK_1 );
		}
	}
	else
	{
		// The length (including the zero-set MSB) is the returned length.
		if( NULL != out_length_of_length )
		{
			*out_length_of_length = 1;
		}

		if( NULL != out_length )
		{
			*out_length = first_byte;
		}
	}

	if( NULL != out_length  )
	{
		if (*out_length == 0 )
		{
			// Set the invalid flag and return.
			*out_error_value = BM_ERROR_TLV_ZERO_LENGTH;
		}
	}
}


void BMI_SET_LITTLE_TLV_LENGTH(
		PVOID cur_ptr,
		UINT cur_bitoff,
		UINT length_of_length,
		UINT length )
{
	/*lint --e{*} */

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 8;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( length_of_length > 0 );
	BMI_ASSERT( length > 0 );

	tmp_ptr = (PUINT8)cur_ptr + 1;
	tmp_bitoff = cur_bitoff;

	if( ( length_of_length == 1 ) && ( length < 128 ) )
	{
		BMI_GENERIC_32BIT_LITTLE_SET( tmp_ptr, tmp_bitoff, bitSize, (UINT32)length, MASK_1 );
	}
	else
	{
		BMI_GENERIC_32BIT_LITTLE_SET( tmp_ptr, tmp_bitoff, bitSize, ((UINT32)length_of_length | 0x80), MASK_1 ); // Turn the MSB on

		tmp_ptr = (PUINT8)cur_ptr + 2;
		tmp_bitoff = cur_bitoff;
		BMI_GENERIC_32BIT_LITTLE_SET( tmp_ptr, tmp_bitoff, (8*length_of_length), (UINT32)length, MASK_1 );
	}
}
void BMI_SET_BIG_TLV_LENGTH(
		PVOID cur_ptr,
		UINT cur_bitoff,
		UINT length_of_length,
		UINT length )
{
	/*lint --e{*} */

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 8;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( length_of_length > 0 );
	BMI_ASSERT( length > 0 );

	tmp_ptr = (PUINT8)cur_ptr + 1;
	tmp_bitoff = cur_bitoff;

	if( ( length_of_length == 1 ) && ( length < 128 ) )
	{
		BMI_GENERIC_32BIT_BIG_SET( tmp_ptr, tmp_bitoff, bitSize, (UINT32)length, MASK_1 );
	}
	else
	{
		BMI_GENERIC_32BIT_BIG_SET( tmp_ptr, tmp_bitoff, bitSize, ((UINT32)length_of_length | 0x80), MASK_1 ); // Turn the MSB on

		tmp_ptr = (PUINT8)cur_ptr + 2;
		tmp_bitoff = cur_bitoff;
		BMI_GENERIC_32BIT_BIG_SET( tmp_ptr, tmp_bitoff, (8*length_of_length), (UINT32)length, MASK_1 );
	}
}




void BMI_GET_BIG_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	PUINT out_length,
	PUINT out_error_value )
{
	/*lint --e{*} */

	// The first TLV Length byte
	UINT16 tlvLen;

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 16;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( NULL != out_error_value );

	// Set the invalid flag to false
	*out_error_value = BM_ERROR_SUCCESS;

	// Read the TLV Length 
	tmp_ptr = (PUINT8)cur_ptr + 2;
	tmp_bitoff = cur_bitoff;
	BMI_GENERIC_32BIT_BIG_GET( tmp_ptr, tmp_bitoff, bitSize, UINT16, tlvLen, MASK_1 );

	if( NULL != out_length )
	{
		*out_length = tlvLen;

		if (*out_length == 0 )
		{
			// Set the invalid flag and return.
			*out_error_value = BM_ERROR_TLV_ZERO_LENGTH;
		}
	}
}

void BMI_GET_LITTLE_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	PUINT out_length,
	PUINT out_error_value )
{
	/*lint --e{*} */

	// The first TLV Length byte
	UINT16 tlvLen;

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 16;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( NULL != out_error_value );

	// Set the invalid flag to false
	*out_error_value = BM_ERROR_SUCCESS;

	// Read the TLV Length 
	tmp_ptr = (PUINT8)cur_ptr + 2;
	tmp_bitoff = cur_bitoff;
	BMI_GENERIC_32BIT_LITTLE_GET( tmp_ptr, tmp_bitoff, bitSize, UINT16, tlvLen, MASK_1 );

	if( NULL != out_length )
	{
		*out_length = tlvLen;

		if (*out_length == 0 )
		{
			// Set the invalid flag and return.
			*out_error_value = BM_ERROR_TLV_ZERO_LENGTH;
		}
	}
}

void BMI_SET_BIG_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	UINT length )
{
	/*lint --e{*} */

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 16;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( length > 0 );

	tmp_ptr = (PUINT8)cur_ptr + 2;
	tmp_bitoff = cur_bitoff;

	BMI_GENERIC_32BIT_BIG_SET( tmp_ptr, tmp_bitoff, bitSize, (UINT32)length, MASK_1 );
}

void BMI_SET_LITTLE_T2L2V_LENGTH(
	PVOID cur_ptr,
	UINT cur_bitoff,
	UINT length )
{
	/*lint --e{*} */

	PVOID tmp_ptr;
	UINT tmp_bitoff;

	UINT32 bitSize = 16;

	BMI_ASSERT( NULL != cur_ptr );
	BMI_ASSERT( length > 0 );

	tmp_ptr = (PUINT8)cur_ptr + 2;
	tmp_bitoff = cur_bitoff;

	BMI_GENERIC_32BIT_LITTLE_SET( tmp_ptr, tmp_bitoff, bitSize, (UINT32)length, MASK_1 );
}
#if (!defined __arm && !defined __arc)
void BMI_STR_DUMP( UINT level, PSTR name, PSTR value, BOOL addnewline )
{
	UINT i;
	for (i=0; i<level; i++)
	{
		BMI_DUMP("\t");
	}

	if (name != NULL && 0 != name[0])
	{
		BMI_DUMP(name);
		BMI_DUMP(" : ");
	}
	
	BMI_DUMP(value);

	if (addnewline)
	{
		BMI_DUMP("\n");
	}
}

void BMI_FORMAT_DUMP(UINT level, PSTR name, UINT size_bits, UINT value, PCSTR val_format, BOOL addnewline)
{
	char val_str[128] = {0};
	PCSTR type = val_format;

	//finding the '%' placeholder
	while (*type != '%' && *type != '\0')
	{
		type++;
	}
	//finding the format specifier type - should be one [duxXf]
	while (*type != 'd' && *type != 'u' && *type != 'x' && *type != 'X' && *type != 'f' && *type != '\0')
	{
		type++;
	}

	//In case size_bits is smaller than 32 bits (sizeof(value)), we need to set zero all 
	//bits that are not part of the "game" in order to get the correct value.
	//this confusion happens due to the implicit conversion that takes place 
	//when the 'value' argument is passed to the function.
	//E.g. when INT8 val = 255 is passed to 'value', it will set 'value' to 0xFFFFFFFF 
	//while it should have been 0xFF. So in this case we're turning off the 6 most significant F's 
	//0xFFFFFFFF ==> 0x000000FF.
	//However, in case the user asked for this value to be dumped as a negative value ("%d")
	//we need to turn the bits back on. see bellow - 
	value = BMI_32BIT_EXTRACT(value,0, size_bits, 0);

	if (*type == 'd')
	{
		//ignore when dealing with one bit
		if ( (size_bits > 1) && (value >> (size_bits - 1) == 1 ) )
		{
			//val is a negative number, setting all MSBs to 1
			value |= 0xFFFFFFFF << size_bits;
		}
	}

	BMI_STR_DUMP( level, name, val_str, addnewline );
}

void BMI_FORMAT_NONVALUE_DUMP(UINT level, PSTR name, BOOL addnewline)
{
	UINT i;

	for (i=0; i<level; i++)
	{
		BMI_DUMP("\t");
	}

	if (0 != name)
	{
		BMI_DUMP(name);
	}

	if (addnewline)
	{
		BMI_DUMP("\n");
	}
}


#endif

