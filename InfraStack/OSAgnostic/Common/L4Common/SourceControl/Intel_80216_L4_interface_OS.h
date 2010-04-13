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
* file name     Intel_80216_L4_interface_OS.h
* Date:         13/07/2006
* @version      1.0 
* @authors      Gal Urbach (gal.urbach@intel.com)
*				Yogev Debbi (yogev.debbi@intel.com)
*				
* Description   This file describes the specific OS definitions needed for the L4 protocol
* 
* Modified by   Name (Name@intel.com)
* Description:
*
*/


#ifndef _INTEL_80216_L4_INTERFACE_OS_H
#define _INTEL_80216_L4_INTERFACE_OS_H


// -- Generic OID --

#define OID_INTEL_80216_CUSTOM		( 0xFF000000 )	// Custom OIDs start with FF...


// -- Generic STATUS --

#define STATUS_INTEL_80216_CUSTOM	( 0x20000000 )	// Custom status has "1" on 29h bit


#endif // _INTEL_80216_L4_INTERFACE_OS_H