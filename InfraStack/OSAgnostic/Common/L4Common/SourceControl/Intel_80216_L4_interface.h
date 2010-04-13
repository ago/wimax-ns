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

/*
* file name     Intel_80216_L4_interface.h
* Date:         03/07/2006
* @version      1.0 
* @authors      Gal Urbach (gal.urbach@intel.com)
*				Yogev Debbi (yogev.debbi@intel.com)
*				
* Description   This file describes the L4 interface between the miniport driver and upper applications
* 
* Modified by   Name (Name@intel.com)
* Description:
*
*/


#ifndef _INTEL_80216_L4_INTERFACE_H
#define _INTEL_80216_L4_INTERFACE_H


// -- OPCODEs --

typedef UINT32 L4_INTEL_80216_OPCODE;


#define L4_OPCODE_BUFFER_MAX_LENGTH		( 8192 )

// struct that represents an OpCode header - name + length of payload
typedef struct _L4_Opcode_Header
{
    L4_INTEL_80216_OPCODE	opcode;
	UINT32					bufferLength;
} L4_Opcode_Header;


// Opcode Macros

#define L4_Opcode_Buffer_Ptr(_pHeader)			( ((UINT8*)_pHeader) + sizeof(L4_Opcode_Header) )
#define L4_Opcode_Curr_Size(_pL4_Opcode_Header)	( sizeof(L4_Opcode_Header) + _pL4_Opcode_Header->bufferLength )


// macro for instantiate a local struct (header + payload). 
// note: given size has to be known at compile time.
#define L4_Opcode_Struct_Local(bufSize) \
struct \
{									\
	L4_Opcode_Header		header;	\
	UINT8					buffer[bufSize];	\
}

/*
- example of usage

void foo()
{
	#define My_Buffer_Size 16
	#define My_Opcode 0x05

	L4_Opcode_Struct_Local(My_Buffer_Size) My_L4_Opcode_Struct;
	.
	.
	// or
	typedef L4_Opcode_Struct_Local(My_Buffer_Size) MyStructType;
	MyStructType Another_L4_Opcode_Struct;
	.
	.
	// init struct
	My_L4_Opcode_Struct.header.opCode = My_Opcode;
	My_L4_Opcode_Struct.header.bufferLengtrh = My_Buffer_Size;
	.
	.
	int size = L4_Opcode_Curr_Size(My_L4_Opcode_Struct);
	memcpy(Another_L4_Opcode_Struct, My_L4_Opcode_Struct, size);
}
*/



// Masks
#define OPCODE_MASK_GROUP			( 0xFF000000 )
#define OPCODE_MASK_MODULE			( 0x00FF0000 )
#define OPCODE_MASK_SUB_MODULE		( 0x0000FF00 )
#define OPCODE_MASK_FUNCTION		( 0x000000FF )

// Groups
#define OPCODE_GROUP_INFRA			( 0x01000000 )
#define OPCODE_GROUP_DSPS			( 0x02000000 )

// Modules
#define OPCODE_MODULE_L4_ADAPTER	( 0x00010000 )
#define OPCODE_MODULE_PAL			( 0x00020000 )
#define OPCODE_MODULE_NDS			( 0x00060000 )
#define OPCODE_MODULE_MANAGEMENT	( 0x00070000 )
/*
	TODO - here comes list of more modules
*/


// Auxiliaries
#define Get_Opcode_Group(_opcode)		( OPCODE_MASK_GROUP & _opcode )
#define Get_Opcode_Module(_opcode)		( OPCODE_MASK_MODULE & _opcode )
#define Get_Opcode_Sub_Module(_opcode)	( OPCODE_MASK_SUB_MODULE & _opcode )
#define Get_Opcode_Function(_opcode)	( OPCODE_MASK_FUNCTION & _opcode )


// OPCODEs definitions

#define L4_INTEL_80216_CMD_MOC_REQUEST	( OPCODE_GROUP_INFRA | OPCODE_MODULE_L4_ADAPTER | 0x01 )

// these for debugging the "physical" pipe
#define L4_INTEL_80216_L4_BE_LOOPBACK				( OPCODE_GROUP_INFRA | OPCODE_MODULE_L4_ADAPTER | 0x02 )
#define L4_INTEL_80216_PIPE_GET_MIRROR				( OPCODE_GROUP_INFRA | OPCODE_MODULE_L4_ADAPTER | 0x03 )
#define L4_INTEL_80216_PIPE_CMD_INDICATE_MIRROR		( OPCODE_GROUP_INFRA | OPCODE_MODULE_L4_ADAPTER | 0x04 )

// ND&S L4 op codes
#define L4_INTEL_80216_NDS_SCAN						( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x01 )
#define L4_INTEL_80216_NDS_GET_SCAN_RESULTS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x02 )
#define L4_INTEL_80216_NDS_SCAN_UPDATE_IND			( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x03 )
#define L4_INTEL_80216_NDS_GET_SYSTEM_STATE			( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x04 )
#define L4_INTEL_80216_NDS_SYSTEM_STATE_IND			( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x05 )
#define L4_INTEL_80216_NDS_GET_LINK_STATUS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x06 )

#define L4_INTEL_80216_NDS_MANUAL_CONNECT_NW		( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x08 )
#define L4_INTEL_80216_NDS_DISCONNECT_NW			( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x09 )
#define L4_INTEL_80216_NDS_GET_SIGNAL_STRENGTH		( OPCODE_GROUP_DSPS | OPCODE_MODULE_NDS | 0x10 )

// Management L4 op codes
#define L4_INTEL_80216_MGT_RF_ON					( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x01	)
#define L4_INTEL_80216_MGT_RF_OFF					( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x02	)
#define L4_INTEL_80216_MGT_GET_RF_STATUS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x03	)
#define L4_INTEL_80216_MGT_GET_LINK_STATUS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x04	)
#define L4_INTEL_80216_MGT_GET_MEDIA_STATUS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x05	)			
#define L4_INTEL_80216_MGT_GET_LINK_STATUS_CHANGED	( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x06	)
#define L4_INTEL_80216_MGT_GET_MEDIA_STATUS_CHANGED	( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x07	)
#define L4_INTEL_80216_MGT_GET_HARDWARE_VERSION		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x08	)
#define L4_INTEL_80216_MGT_GET_SOFTWARE_VERSION		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x09	)
#define L4_INTEL_80216_MGT_GET_FIRMWARE_VERSION		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x0a	)
#define L4_INTEL_80216_MGT_GET_MAC_ADDRESS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x0b	)
#define L4_INTEL_80216_MGT_GET_SLA_INFORMATION		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x0c	)
#define L4_INTEL_80216_MGT_GET_SYSTEM_STATE			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x0d	)
#define L4_INTEL_80216_MGT_GET_LINK_SPEED			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x0e	)
#define L4_INTEL_80216_MGT_GET_CONNECTION_TIME		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x0f	)
#define L4_INTEL_80216_MGT_GET_LINK_QUALITY_PARAMS	( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x10	)
#define L4_INTEL_80216_MGT_GET_CENTER_FREQUENCY		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x11	)
#define L4_INTEL_80216_MGT_GET_CARD_STATUS			( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x12	)
#define L4_INTEL_80216_MGT_GET_LINK_STATISTICS		( OPCODE_GROUP_DSPS | OPCODE_MODULE_MANAGEMENT | 0x13	)


#define L4_INTEL_80216_PAL_DEBUG				( OPCODE_GROUP_INFRA | OPCODE_MODULE_PAL | 0x01 )

/*
	TODO - list of more opcodes (maybe separate file for that) --

#define L4_INTEL_80216_<module_name>_GET_XXX

#define L4_INTEL_80216_<module_name>_SET_XXX 

#define L4_INTEL_80216_<module_name>_CMD_XXX

*/



// -- INDICATIONs --

typedef UINT32 L4_INTEL_80216_INDICATION;

#define L4_INDICATION_BUFFER_MAX_LENGTH ( 8192 )

// struct that represents an Indication header - name + length of payload
typedef struct _L4_Indication_Header
{
	L4_INTEL_80216_INDICATION	indication;
	UINT32						bufferLength;
} L4_Indication_Header;



#define L4_Indication_Buffer_Ptr(_pHeader)				( ((UINT8*)_pHeader) + sizeof(L4_Indication_Header) )
#define L4_Indication_Curr_Size(_pL4_Indication_Header)	( sizeof(L4_Indication_Header) + _pL4_Indication_Header->bufferLength )

// macro for instantiate a local struct (header + payload). 
// note: given size has to be known at compile time.
#define L4_Indication_Struct_Local(bufSize) \
struct \
{									\
	L4_Indication_Header		header;	\
	UINT8						buffer[bufSize];	\
}


// Masks
#define INDICATION_MASK_GROUP			( 0xFF000000 )
#define INDICATION_MASK_MODULE			( 0x00FF0000 )
#define INDICATION_MASK_SUB_MODULE		( 0x0000FF00 )
#define INDICATION_MASK_FUNCTION		( 0x000000FF )

// Groups
#define INDICATION_GROUP_INFRA			( 0x01000000 )
#define INDICATION_GROUP_DSPS			( 0x02000000 )

// Modules
#define INDICATION_MODULE_L4_ADAPTER	( 0x00010000 )
/*
	TODO - here comes list of more modules
*/


// Auxiliaries
#define Get_Indication_Group(_opcode)		( INDICATION_MASK_GROUP & _opcode )
#define Get_Indication_Module(_opcode)		( INDICATION_MASK_MODULE & _opcode )
#define Get_Indication_Sub_Module(_opcode)	( INDICATION_MASK_SUB_MODULE & _opcode )
#define Get_Indication_Function(_opcode)	( INDICATION_MASK_FUNCTION & _opcode )


// INDICATIONs definitions
#define L4_INTEL_80216_IND_MOC_RESPONSE		( INDICATION_GROUP_INFRA | INDICATION_MODULE_L4_ADAPTER | 0x01 )
#define L4_INTEL_80216_IND_MOC_BROADCAST	( INDICATION_GROUP_INFRA | INDICATION_MODULE_L4_ADAPTER | 0x02 )

// this for debugging the "physical" pipe
#define L4_INTEL_80216_PIPE_IND_INDICATE_MIRROR	( INDICATION_GROUP_INFRA | INDICATION_MODULE_L4_ADAPTER | 0x03 )


/*
	TODO list of indications (maybe separate file for that) --

#define L4_INTEL_80216_<module_name>_IND_XXX

*/

#endif // _INTEL_80216_L4_INTERFACE_H