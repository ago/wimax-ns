

/*************************************************************************
**                                                                      **
**                  I N T E L ( ENVARA ) P R O P R I E T A R Y          **
**                                                                      **
**     COPYRIGHT (c)  2006 BY  INTEL  CORPORATION.  ALL RIGHTS          **
**     RESERVED.   NO  PART  OF THIS PROGRAM  OR  PUBLICATION  MAY      **
**     BE  REPRODUCED,   TRANSMITTED,   TRANSCRIBED,   STORED  IN  A    **
**     RETRIEVAL SYSTEM, OR TRANSLATED INTO ANY LANGUAGE OR COMPUTER    **
**     LANGUAGE IN ANY FORM OR BY ANY MEANS, ELECTRONIC, MECHANICAL,    **
**     MAGNETIC,  OPTICAL,  CHEMICAL, MANUAL, OR OTHERWISE,  WITHOUT    **
**     THE PRIOR WRITTEN PERMISSION OF INTEL  CORPORATION.              **
**                                                                      **
*************************************************************************/

/*
* file name     L3L4CommonDefines.h
* Date:         03/10/2006
* @version      1.0 
* @authors      Roy Ramon (roy.ramon@intel.com)
*			
*				
* Description   This file describes the commmon interface between the 80216 driver and upper applications
* 
* Modified by   Yogev Debbi (yogev.debbi@intel.com)
* Description:	Add more opcodes, definitions and enums.
*
*/


#ifndef _L3L4_COMMON_DEFIENS_H
#define _L3L4_COMMON_DEFIENS_H


//******************************************
//       Header definitions 
//******************************************

#define HEADER_SIZE 12
#define SIZE_OF_TYPE_LENGTH 4

// default values
#define HEADER_ACCESSIBILITY	0 
#define HEADER_STATUS		0

// -- VERSION field --

// Operational interface version (As of WIMAX21/BETA07) / General interface version (Before WIMAX21/BETA07)
#define VERSION_MAJOR	9		// 10 bits (0 - 1023)
#define VERSION_MINOR	3		// 16 bits (0 - 65535)
#define VERSION_BRANCH	2		//  6 bits (0 - 63)

// Production interface version (As of WIMAX21/BETA07)
#define PRODUCTION_VERSION_MAJOR	6		// 10 bits (0 - 1023)
#define PRODUCTION_VERSION_MINOR	7		// 16 bits (0 - 65535)
#define PRODUCTION_VERSION_BRANCH	0		//  6 bits (0 - 63)

// DnD interface version (As of WIMAX21/BETA07)
#define DND_VERSION_MAJOR	7		// 10 bits (0 - 1023)
#define DND_VERSION_MINOR	0		// 16 bits (0 - 65535)
#define DND_VERSION_BRANCH	0		//  6 bits (0 - 63)

// defines the version value in the L4 header
// VERSION_MAJOR is the first 10 bits (msb). VERSION_BRANCH is the last 6 bits (lsb).
// for example: if MAJOR==1, BRANCH==4: [0000 0000 01][00 0100]
//									   [   MAJOR    ][ MINOR ]
//
#define HEADER_VERSION ( (VERSION_MAJOR << 6) | VERSION_BRANCH ) 

// Macros for the version field - for use in next release
// #define GetHeaderVersionMajor(_version)  ( _version >> 6 )
// #define GetHeaderVersionBranch(_version) ( _version & 0x3F )

// -- OPCODE field --

#define RESERVED_OPCODE 0x0000 // reserved for Besor 
#define INVALID_OPCODE	0xFFFF

#define L3L4_REQUEST_OR_INDICATION_MASK ( 0x8000 ) // helps you to get the bit
#define L3L4_INDICATION_MASK			( 0x8000 ) // use OR
#define L3L4_REQUEST_MASK				( 0x7FFF ) // use AND 

#define L3L4_MODULE_MASK		( 0x7800 ) // 4 bits
#define L3L4_REQUEST_TYPE_MASK	( 0x600 )// get set Command


// Modules
#define L3L4_MODULE_ID_DEBUG		( 0x1000 )
#define L3L4_MODULE_ID_L4_ADAPTER	( 0x2000 )
#define L3L4_MODULE_ID_PAL			( 0x3000 )
#define L3L4_MODULE_ID_NDS			( 0x4000 )
#define L3L4_MODULE_ID_GENERAL		( 0x5000 )
#define L3L4_MODULE_ID_SUPPLICANT	( 0x6000 )
#define L3L4_MODULE_ID_PRODUCTION	( 0x7000 )

// request type

#define L3L4_REQUEST_TYPE_GET ( 0x200 )
#define L3L4_REQUEST_TYPE_SET ( 0x400 )
#define L3L4_REQUEST_TYPE_CMD ( 0x600 )
#define L3L4_INTERNAL_REQUEST ( 0x80 )


#define L3L4_GET_REQUEST_OR_INDICATION(_opcode)		( L3L4_REQUEST_OR_INDICATION_MASK & _opcode )
#define L3L4_IS_INDICATION(_opcode)					( L3L4_REQUEST_OR_INDICATION_MASK & _opcode  == L3L4_INDICATION_MASK ) // Return  True if the bit is for Indication
#define L3L4_IS_REQUEST(_opcode)					( L3L4_REQUEST_OR_INDICATION_MASK & _opcode  != L3L4_INDICATION_MASK ) // Return  True if the bit is for Request
#define L3L4_GET_OPCODE_MODULE(_opcode)				( L3L4_MODULE_MASK & _opcode )
#define L3L4_GET_OPCODE_REQUEST_TYPE(_opcode)		( L3L4_REQUEST_TYPE_MASK & _opcode )



//******************************************
//       OpCode definitions 
//******************************************
// general
// CMD
#define L4_L3_OPCODE_CMD_INIT				( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x1 )
#define L4_L3_OPCODE_CMD_TERMINATE			( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x2 )
#define L4_L3_OPCODE_CMD_MODE_OF_OPERATION	( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x3 )
#define L4_L3_OPCODE_CMD_RESET_DEVICE		( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x4 )
#define L4_L3_OPCODE_CMD_MONITOR_CONTROL    ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x5 )
#define L4_L3_OPCODE_CMD_ENTER_POWER_SAVE	( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x6 )
#define L4_L3_OPCODE_CMD_PROCESS_SP_LOCK_MO ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x7 )
#define L4_L3_OPCODE_CMD_SP_LOCK_PROCESS_UNLOCK_CODE ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x8 )
#define L4_L3_OPCODE_CMD_COEX_PROCESS_START ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0x9 )
#define L4_L3_OPCODE_CMD_COEX_PROCESS_END ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_CMD | 0xA )



// GET
#define L4_L3_OPCODE_GET_LM_VERSION     ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x1 )
#define L4_L3_OPCODE_GET_DEVICE_INFO    ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x2 )
#define L4_L3_OPCODE_GET_LINK_STATUS    ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x3 )
#define L4_L3_OPCODE_GET_STATISTICS     ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x4 )
#define L4_L3_OPCODE_GET_STATE			( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x5 )
#define L4_L3_OPCODE_GET_MEDIA_STATUS	( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x6 )
#define L4_L3_OPCODE_GET_TRACE_SEVERITY_TABLE ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x7 )
#define L4_L3_OPCODE_GET_MONITOR_FILTER_TABLE ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x8 )
#define L4_L3_OPCODE_GET_SPLOCK_STATUS ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0x9 )
#define L4_L3_OPCODE_GET_D2H_CHANNEL_MASK ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0xA )
#define L4_L3_OPCODE_GET_ACTIVATED_NSPS ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_GET | 0xB )

// SET
#define L4_L3_OPCODE_SET_TRACE_SEVERITY_TABLE ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_SET | 0x1 )
#define L4_L3_OPCODE_SET_MONITOR_FILTER_TABLE ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_SET | 0x2 )
#define L4_L3_OPCODE_SET_COEX_MODE		( L3L4_MODULE_ID_GENERAL    | L3L4_REQUEST_TYPE_SET | 0x3 )
#define L4_L3_OPCODE_SET_PREINIT_CONFIG		  ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_SET | 0x4)
#define L4_L3_OPCODE_SET_D2H_CHANNEL_MASK ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_SET | 0x5 )
#define L4_L3_OPCODE_SET_SPLOCK_UNLOCK_CODE ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_SET | 0x6 )
#define L4_L3_OPCODE_SET_ACTIVATED_NSPS ( L3L4_MODULE_ID_GENERAL| L3L4_REQUEST_TYPE_SET | 0x7 )


//ND&S 
//cmd
#define L4_L3_OPCODE_CMD_RF_CONTROL		( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_CMD | 0x2 )
#define L4_L3_OPCODE_CMD_SCAN			( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_CMD | 0x3 )
#define L4_L3_OPCODE_CMD_CONNECT		( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_CMD | 0x4 )
#define L4_L3_OPCODE_CMD_DISCONNECT		( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_CMD | 0x5 )
#define L4_L3_OPCODE_CMD_EXIT_IDLE		( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_CMD | 0x6 )
//SET
#define L4_L3_OPCODE_SET_SCAN_PARAM			( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_SET | 0x2 )
#define L4_L3_OPCODE_SET_IDLE_PARAM			( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_SET | 0x3 )
//GET
#define L4_L3_OPCODE_GET_SCAN_RESULT	( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_GET | 0x2 )
#define L4_L3_OPCODE_GET_IDLE_PARAM		( L3L4_MODULE_ID_NDS    | L3L4_REQUEST_TYPE_GET | 0x3 )

//SUPLICANT
//CMD
#define L4_L3_OPCODE_CMD_SEND_EAP_RESPONSE	( L3L4_MODULE_ID_SUPPLICANT  | L3L4_REQUEST_TYPE_CMD | 0x2 )

//SET
#define L4_L3_OPCODE_SET_EAP_SUCCESS		( L3L4_MODULE_ID_SUPPLICANT  | L3L4_REQUEST_TYPE_SET | 0x2 )
#define L4_L3_OPCODE_SET_EAP_FAIL			( L3L4_MODULE_ID_SUPPLICANT  | L3L4_REQUEST_TYPE_SET | 0x3 )
#define L4_L3_OPCODE_SET_EAP_KEY			( L3L4_MODULE_ID_SUPPLICANT  | L3L4_REQUEST_TYPE_SET | 0x4 )

//GET
#define L4_L3_OPCODE_GET_TLS_OPERATION_RESULT            ( L3L4_MODULE_ID_SUPPLICANT  | L3L4_REQUEST_TYPE_GET | 0x1 )

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////************ PRODUCTION *****************// ////////////////////////////////

// Get
#define L4_PRODUCTION_OPCODE_GET_PHY_METRICS							( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x1 )
#define L4_PRODUCTION_OPCODE_GET_PHY_TEMPRATURE							( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x2 )
#define L4_PRODUCTION_OPCODE_GET_PHY_DIUC_CONFIGURATION					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x3 )
#define L4_PRODUCTION_OPCODE_GET_PHY_UIUC_CONFIGURATION					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x4 )
#define L4_PRODUCTION_OPCODE_GET_GPIO									( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x5 )
#define L4_PRODUCTION_OPCODE_GET_PRODUCTION_STATE						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x6 )
#define L4_PRODUCTION_OPCODE_GET_PHY_RSSI_ADDITIONAL_PARAMS				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x7 )
#define L4_PRODUCTION_OPCODE_GET_PHY_RX_SYNC_STATUS						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x8 )
#define L4_PRODUCTION_OPCODE_GET_PHY_RX_LO_CALIB						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x9 )
#define L4_PRODUCTION_OPCODE_GET_PHY_TX_LO_CALIB						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0xA )
#define L4_PRODUCTION_OPCODE_GET_PHY_INITIAL_FREQ_OFFSET_HZ				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0xB )
#define L4_PRODUCTION_OPCODE_GET_PHY_RXIQ_VALUES						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0xC )
#define L4_PRODUCTION_OPCODE_GET_ULT									( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x10 )
#define L4_PRODUCTION_OPCODE_GET_FEM_ID								( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x11 )
#define L4_PRODUCTION_OPCODE_GET_NVM_VALID_SECTION_TABLE				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | 0x59 )


// Get internal APIs
#define L4_PRODUCTION_OPCODE_GET_PHY_CURRENT_DC_EST_MEASURE_RESULT		( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_GET | L3L4_INTERNAL_REQUEST | 0x1 )

// Set
#define L4_PRODUCTION_OPCODE_SET_PHY_TPC_CONFIG					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x1 )
#define L4_PRODUCTION_OPCODE_SET_FREQ_OFFSET_CONFIG				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x2 )
#define L4_PRODUCTION_OPCODE_SET_PHY_COMMON_PARAMS				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x3 )
#define L4_PRODUCTION_OPCODE_SET_PHY_TX_ATTENUATION				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x4 )
#define L4_PRODUCTION_OPCODE_SET_PLATFORM_TYPE					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x5 )
#define L4_PRODUCTION_OPCODE_SET_PHY_AGC_CONFIG					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x6 )
#define L4_PRODUCTION_OPCODE_SET_RF_XO_BANK_CAPACITORS_VALUE	( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x7 )

#define L4_PRODUCTION_OPCODE_SET_RF_LO_DIVIDER_DELAY			( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x8 )
#define L4_PRODUCTION_OPCODE_SET_RX_RF_ANT_ACTIVATION_MODE		( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x9 )

#define L4_PRODUCTION_OPCODE_SET_GPIO							( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | 0x62 )


// Set internal APIs
#define L4_PRODUCTION_OPCODE_SET_PHY_CALIB_CONFIGURATION		( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | L3L4_INTERNAL_REQUEST | 0x4 )
#define L4_PRODUCTION_OPCODE_SET_PHY_RX_RF_IQ_DAC				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | L3L4_INTERNAL_REQUEST | 0x5 )
#define L4_PRODUCTION_OPCODE_SET_PHY_TEMPERATURE_CONFIGURATION	( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_SET | L3L4_INTERNAL_REQUEST | 0x6 )

// Cmd
#define L4_PRODUCTION_OPCODE_CMD_START_PHY_RXTX_TEST				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x1 )
#define L4_PRODUCTION_OPCODE_CMD_STOP_PHY_TEST						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x2 )
#define L4_PRODUCTION_OPCODE_CMD_PHY_METRICS_CONFIG					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x3 )
#define L4_PRODUCTION_OPCODE_CMD_START_PHY_INIT_CALIBRATION_TEST	( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x4 )
#define L4_PRODUCTION_OPCODE_CMD_START_PHY_MAIN_CALIBRATION_TEST	( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x5 )
#define L4_PRODUCTION_OPCODE_CMD_PHY_COUNTERS_RESET_ORDER								( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x6 )
#define L4_PRODUCTION_OPCODE_CMD_START_PHY_CONT_TX_OFDM_TEST		( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x7 )
#define L4_PRODUCTION_OPCODE_CMD_PRODUCTION_ACTIVATE				( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x8 )
#define L4_PRODUCTION_OPCODE_CMD_START_PHY_SLOW_CLOCK_TEST			( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x9 )

#define L4_PRODUCTION_OPCODE_CMD_NVM_WRITE						( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x51 )
#define L4_PRODUCTION_OPCODE_CMD_NVM_READ							( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x52 )
#define L4_PRODUCTION_OPCODE_CMD_NVM_SHADOW_WRITE					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x53 )
#define L4_PRODUCTION_OPCODE_CMD_NVM_SHADOW_READ					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x54 )
#define L4_PRODUCTION_OPCODE_CMD_COPY_SHADOW_TO_NVM					( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x55 )
#define L4_PRODUCTION_OPCODE_CMD_NVM_APPLY_SHADOW_TO_OPERATIONAL_FIRMWARE ( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x56 )
#define L4_PRODUCTION_OPCODE_CMD_NVM_APPLY_EPROM_TO_OPERATIONAL_FIRMWARE	( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x58 )

#define L4_PRODUCTION_OPCODE_CMD_PLAT_START_SLOW_CLOCK_CONNECTIVITY_TEST ( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x61 )
#define L4_PRODUCTION_OPCODE_CMD_PLAT_START_WIWI_UART_CONNECTIVITY_TEST	 ( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x63 )

#define L4_PRODUCTION_OPCODE_CMD_START_PHY_PLATFORM_NOISE_ANALYSIS_TEST		( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x81 )
#define L4_PRODUCTION_OPCODE_CMD_START_RXIQ_TEST		                    ( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x82 )
#define L4_PRODUCTION_OPCODE_CMD_START_PHY_TXIQ_SSB		( L3L4_MODULE_ID_PRODUCTION | L3L4_REQUEST_TYPE_CMD | 0x83)

//Report

#define PRODUCTION_L4_OPCODE_REPORT_PRODUCTION_STATE_STATUS			( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x1 )
#define PRODUCTION_L4_OPCODE_REPORT_PHY_METRICS						( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x2 )

#define PRODUCTION_L4_OPCODE_REPORT_PHY_INIT_CALIBRATION_RESULTS	( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x3 )
#define PRODUCTION_L4_OPCODE_REPORT_PHY_MAIN_CALIBRATION_RESULTS	( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x4 )

#define PRODUCTION_L4_OPCODE_REPORT_PRODUCTION_ACTIVATE_STATUS		( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x5 )

#define PRODUCTION_L4_OPCODE_REPORT_PHY_SLOW_CLOCK_RESULTS			( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x6 )

#define PRODUCTION_L4_OPCODE_REPORT_NVM_WRITE_STATUS				( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x51 )
#define PRODUCTION_L4_OPCODE_REPORT_NVM_READ_STATUS					( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x52 )
#define PRODUCTION_L4_OPCODE_REPORT_NVM_SHADOW_WRITE_STATUS			( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x53 )
#define PRODUCTION_L4_OPCODE_REPORT_NVM_SHADOW_READ_STATUS			( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x54 )
#define PRODUCTION_L4_OPCODE_REPORT_COPY_SHADOW_TO_NVM_STATUS		( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x55 )
#define PRODUCTION_L4_OPCODE_REPORT_NVM_APPLY_SHADOW_TO_OPERATIONAL_FIRMWARE_STATUS		( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x56 )
#define PRODUCTION_L4_OPCODE_REPORT_NVM_APPLY_EPROM_TO_OPERATIONAL_FIRMWARE_STATUS		    ( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x58 )
#define PRODUCTION_L4_OPCODE_REPORT_PHY_PLATFORM_NOISE_ANALYSIS					( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x81 )

#define PRODUCTION_L4_OPCODE_REPORT_PLAT_SLOW_CLOCK_CONNECTIVITY	( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x61 )
#define PRODUCTION_L4_OPCODE_REPORT_PLAT_WIWI_UART_CONNECTIVITY		( L3L4_MODULE_ID_PRODUCTION | L3L4_INDICATION_MASK | 0x63 )


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//DEBUG
//CMD
#define L4_L3_OPCODE_CMD_MOC_REQUEST		( L3L4_MODULE_ID_L4_ADAPTER	| L3L4_REQUEST_TYPE_CMD | 0x2 )
#define L4_L3_OPCODE_CMD_CHECK_INTERFACE	( L3L4_MODULE_ID_DEBUG		| L3L4_REQUEST_TYPE_CMD | 0x3 )

//GET
#define L4_L3_OPCODE_GET_DEBUG_LOOPBACK		( L3L4_MODULE_ID_L4_ADAPTER	| L3L4_REQUEST_TYPE_GET | 0x2 )
#define L4_L3_OPCODE_GET_CHECK_INTERFACE	( L3L4_MODULE_ID_DEBUG		| L3L4_REQUEST_TYPE_GET | 0x3 )

//SET
#define L4_L3_OPCODE_SET_CHECK_INTERFACE	( L3L4_MODULE_ID_DEBUG		| L3L4_REQUEST_TYPE_SET | 0x2 )


//******************************************
//       Opcode Indications ( Report )
//******************************************
//General
#define L3_L4_OPCODE_REPORT_STATE            ( L3L4_INDICATION_MASK | L3L4_MODULE_ID_GENERAL	| 0x2 )
#define L3_L4_OPCODE_REPORT_TRACE_EVACUATE   ( L3L4_INDICATION_MASK | L3L4_MODULE_ID_GENERAL	| 0x3 )
#define L3_L4_OPCODE_REPORT_MONITOR_EVACUATE ( L3L4_INDICATION_MASK | L3L4_MODULE_ID_GENERAL	| 0x4 )
#define L3_L4_OPCODE_REPORT_READY_FOR_POWER_SAVE ( L3L4_INDICATION_MASK | L3L4_MODULE_ID_GENERAL	| 0x5 )

#define L3_L4_OPCODE_REPORT_EMSK_RELATED_KEYS ( L3L4_INDICATION_MASK | L3L4_MODULE_ID_GENERAL	| 0x7 )
#define L3_L4_OPCODE_REPORT_SP_LOCK_STATUS      ( L3L4_INDICATION_MASK | L3L4_MODULE_ID_GENERAL	| 0x8 )



//ND&S
#define L3_L4_OPCODE_REPORT_SCAN_RESULT	( L3L4_INDICATION_MASK | L3L4_MODULE_ID_NDS			| 0x2 )
#define L3_L4_OPCODE_REPORT_BS_INFO			( L3L4_INDICATION_MASK | L3L4_MODULE_ID_NDS			| 0x3 )
#define L3_L4_OPCODE_REPORT_SII					( L3L4_INDICATION_MASK | L3L4_MODULE_ID_NDS			| 0x4 )
#define L3_L4_OPCODE_REPORT_RECENT_BS	( L3L4_INDICATION_MASK | L3L4_MODULE_ID_NDS			| 0x5 )


// Supplicant
#define L3_L4_OPCODE_REPORT_EAP_REQUEST	( L3L4_INDICATION_MASK | L3L4_MODULE_ID_SUPPLICANT	| 0x2 )
#define L3_L4_OPCODE_REPORT_EAP_RESTART	( L3L4_INDICATION_MASK | L3L4_MODULE_ID_SUPPLICANT	| 0x3 )
#define L3_L4_OPCODE_REPORT_ALT_ACCEPT	( L3L4_INDICATION_MASK | L3L4_MODULE_ID_SUPPLICANT	| 0x4 )
#define L3_L4_OPCODE_REPORT_KEY_REQUEST	( L3L4_INDICATION_MASK | L3L4_MODULE_ID_SUPPLICANT	| 0x5 )

// DEBUG
#define L3_L4_OPCODE_REPORT_MOC_RESPONSE		( L3L4_INDICATION_MASK | L3L4_MODULE_ID_L4_ADAPTER		| 0x2 )
#define L3_L4_OPCODE_REPORT_MOC_BROADCAST		( L3L4_INDICATION_MASK | L3L4_MODULE_ID_L4_ADAPTER		| 0x3 )

#define L3_L4_OPCODE_REPORT_CHECK_INTERFACE		( L3L4_INDICATION_MASK | L3L4_MODULE_ID_DEBUG	| 0x4 )

 

 



//******************************************
//       common Enums
//******************************************
// Gaps in enumeration must NOT be used in the future.
//This enum is doubled with an enum definition in L3DmMonitorGroups.bm called E_MacState
typedef enum _E_SystemState{
	E_SYSTEM_STATE_UNINITIALIZED 		= 0x01,
	E_SYSTEM_STATE_INIT					= 0x02,
	E_SYSTEM_STATE_READY				= 0x03,
	E_SYSTEM_STATE_SCAN					= 0x04,
	E_SYSTEM_STATE_CONNECTING			= 0x06,
	E_SYSTEM_STATE_WIMAX_CONNECTED		= 0x07,
	E_SYSTEM_STATE_DATA_PATH_CONNECTED	= 0x08,
	E_SYSTEM_STATE_IDLE					= 0x09,
	E_SYSTEM_STATE_DISCONNECTING		= 0x0a,
	E_SYSTEM_STATE_PRODUCTION			= 0x0d,
	E_SYSTEM_STATE_CONFIG				= 0x0e,
	E_SYSTEM_STATE_RF_OFF				= 0x0f,
	E_SYSTEM_STATE_RF_SHUTDOWN			= 0x10
}E_SystemState;

typedef enum _E_ModeOfOperation{
	E_MODE_OF_OPERATION_NORMAL = 0x01,
	E_MODE_OF_OPERATION_PRODUCTION
}E_ModeOfOperaion;

typedef enum _E_ResetCommand{
	E_RESET_COMMAND_WARM = 0x01,
	E_RESET_COMMAND_COLD
}E_ResetCommand;

typedef enum _E_WakeupMode{
	E_WAKEUP_MODE_WITH = 0x01,
	E_WAKEUP_MODE_WITHOUT
}E_WakeupMode;

typedef enum _E_Bandwidth{
	E_BANDWIDTH_3_5 = 0x01,
	E_BANDWIDTH_5,
	E_BANDWIDTH_7,
	E_BANDWIDTH_8_75,
	E_BANDWIDTH_10
}E_Bandwidth;

typedef enum _E_Fft{
	E_FFT_512 = 0x01,
	E_FFT_1024
}E_Fft;

typedef enum _E_MediaStatus{
	E_MEDIA_STATUS_LINK_UP   = 0x01,
	E_MEDIA_STATUS_LINK_DOWN,
	E_MEDIA_STATUS_LINK_RENEW
}E_MediaStatus;

typedef enum _E_ScanStatus{
	E_SCAN_STATUS_DONE = 0x01,
	E_SCAN_STATUS_SCANING,
	E_SCAN_STATUS_FAILURE,
	E_SCAN_STATUS_STOPPED,
	E_SCAN_STATUS_COEX_STOPPED
}E_ScanStatus;

typedef enum _E_ConnectProgress{
	E_CONNECT_PROGRESS_RANGING = 0x01,
	E_CONNECT_PROGRESS_SBC,
	E_CONNECT_PROGRESS_EAP_AUTH,
	E_CONNECT_PROGRESS_3WAY_HANDSHAKE,
	E_CONNECT_PROGRESS_REGISTRATION
}E_ConnectProgress;

typedef enum _E_ReportStateReason{
	E_REPORT_STATE_REASON_NORMAL    = 0x01,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_TO_NW,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_RANGING,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_SBC,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_EAP_AUTH,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_3WAY_HANDSHAKE,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_REGISTRATION,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_DATA_PATH,
	E_REPORT_STATE_REASON_FAIL_TO_CONNECT_COEX_NO_RF,
	E_REPORT_STATE_REASON_DISCONNECT_DREG,
	E_REPORT_STATE_REASON_DISCONNECT_ABORT,
	E_REPORT_STATE_REASON_DISCONNECT_RESET,
	E_REPORT_STATE_REASON_DISCONNECT_DROP,
	E_REPORT_STATE_REASON_SPLOCK_VALIDATION_FAILED,
	E_REPORT_STATE_REASON_DISCONNECT_SECURITY,
	E_REPORT_STATE_REASON_RESET_HW_WDT,
	E_REPORT_STATE_REASON_RESET_SW_WDT,
	E_REPORT_STATE_REASON_RESET_ASSERT,
	E_REPORT_STATE_REASON_RESET_THERMAL,
	E_REPORT_STATE_REASON_RESET_RF_KILL,
	E_REPORT_STATE_REASON_RESET_CO_EXISTENCE,
	E_REPORT_STATE_REASON_RESET_HOST,
	E_REPORT_STATE_REASON_DISCONNECT_PROTOCOL_ERROR,
	E_REPORT_STATE_REASON_FAIL_TO_DISCOVER_FULL_NAPID,
	E_REPORT_STATE_REASON_FW_REQUEST_DEV_RESET,
	E_REPORT_STATE_REASON_FW_REQUEST_FUNC_RESET
}E_ReportStateReason;

typedef enum _E_SwRfStatus{
	E_SW_RF_STATUS_ON    = 0x01,
	E_SW_RF_STATUS_OFF
}E_SwRfStatus;

typedef enum _E_HwRfStatus{
	E_HW_RF_STATUS_ON    = 0x01,
	E_HW_RF_STATUS_OFF
}E_HwRfStatus;

typedef enum _E_ScanCommand{
	E_SCAN_COMMAND_START    = 0x01,
	E_SCAN_COMMAND_STOP
}E_ScanCommand;


typedef enum _E_ScanMode{
	E_SCAN_MODE_FIND_FIRST  = 0x01,
	E_SCAN_MODE_FIND_ALL
}E_ScanMode;

typedef enum _E_ConnectionMode{
	E_CONNECTION_MODE_MANUAL = 0x01,
	E_CONNECTION_MODE_AUTOMATIC,
	E_CONNECTION_MODE_DCD_DISCOVERY
}E_ConnectionMode;

typedef enum _E_RequestRealm{
	E_REQUEST_REALM_REQUEST = 0x01,
	E_REQUEST_REALM_DONT_REQUEST
}E_RequestRealm;

typedef enum _E_CoexistenceMode{
	E_COEXISTENCE_MODE_XOR = 0x01,
	E_COEXISTENCE_MODE_CM
}E_CoexistenceMode;

typedef enum _E_CoexistenceState{
	E_COEXISTENCE_STATE_LOW_PRIO_SCAN = 0x01,
	E_COEXISTENCE_STATE_HIGH_PRIO_SCAN,
	E_COEXISTENCE_STATE_CONNECTING
}E_CoexistenceState;

typedef enum _E_CoexistencePriority{
	E_COEXISTENCE_PRIORITY_SCAN_LOW = 0x01,
	E_COEXISTENCE_PRIORITY_SCAN_HIGH,
	E_COEXISTENCE_PRIORITY_CONNECT_LOW,
	E_COEXISTENCE_PRIORITY_CONNECT_HIGH
}E_CoexistencePriority;


typedef enum _E_HomeOperator{
	E_HOME_OPERATOR_FALSE    = 0x01,
	E_HOME_OPERATOR_TRUE
}E_HomeOperator;

typedef enum _E_EapKeyValid{
	E_EAP_KEY_VALID    = 0x01,
	E_EAP_KEY_INVALID
}E_EapKeyValid;

typedef enum _E_EnableProductionStatus{
	E_ENABLE_PRODUCTION_STATUS_SUCCESS = 0x00,
	E_ENABLE_PRODUCTION_STATUS_LOCKED = 0x01,
	E_ENABLE_PRODUCTION_STATUS_ERROR_UNKNOWN = 0x02
}E_EnableProductionStatus;

typedef enum _E_SPLockStatus{
	E_SP_LOCK_STATUS_LOCKED = 0x00,
	E_SP_LOCK_STATUS_UNLOCKED = 0x01
}E_SPLockStatus;


typedef enum _E_MonitorControl{
	E_MONITOR_CONTROL_ON = 0x01,
	E_MONITOR_CONTROL_OFF
}E_MonitorControl;

typedef enum _E_DataChannelSwitch{
	E_DATA_CHANNEL_SWITCH_ON = 0x01,
	E_DATA_CHANNEL_SWITCH_OFF
}_E_DataChannelSwitch;

typedef enum _E_DiagnosticsChannelSwitch{
	E_DIAGNOSTICS_CHANNEL_ON = 0x01,
	E_DIAGNOSTICS_CHANNEL_OFF
}_E_DiagnosticsChannelSwitch;

typedef enum _E_L3L4ResponseStatus
{
			L3L4_RESPONSE_STATUS_SUCCESS_DONE = 0x00,
			L3L4_RESPONSE_STATUS_SUCCESS_IN_PROCESS,
			L3L4_RESPONSE_STATUS_INVALID_OPCODE,
			L3L4_RESPONSE_STATUS_ERROR_BAD_STATE,
			L3L4_RESPONSE_STATUS_ILLEGAL_VALUE,
			L3L4_RESPONSE_STATUS_MISSING_PARAMS,
			L3L4_RESPONSE_STATUS_VERSION_ERROR,
			L3L4_RESPONSE_STATUS_ACCESSIBILITY_ERROR,
			L3L4_RESPONSE_STATUS_BUSY,
			L3L4_RESPONSE_STATUS_CORRUPTED_TLV,
			L3L4_RESPONSE_STATUS_UNINITIALIZED,
			L3L4_RESPONSE_STATUS_UNKNOWN_ERROR,
			L3L4_RESPONSE_STATUS_PRODUCTION_ERROR,
			L3L4_RESPONSE_STATUS_NO_RF,
			L3L4_RESPONSE_STATUS_NOT_READY_FOR_POWER_SAVE,
			L3L4_RESPONSE_STATUS_THERMAL_CRITICAL,
 
}E_L3L4ResponseStatus;

#endif //_L3L4_COMMON_DEFIENS_H