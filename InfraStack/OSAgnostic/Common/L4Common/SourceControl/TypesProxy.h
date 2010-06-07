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
 * TypesProxy.h
 *
 * Basic types definitions. This file serves as a proxy to the actual type
 * definition files.
 * 
 * @version 1.1    07-July-2005    Yariv Barkan\n
 *    Minor changes
 *
 * @version 1.0    06-July-2005    Yariv Barkan\n
 *    Initial version
 *
 */

#ifndef __TYPES_PROXY_H
#define __TYPES_PROXY_H

#ifndef PARDILLO

// first include standard basic types
#if defined (WIN32)
	#include <Windows.h>
	
	#if defined (_OS_WIN32SIM)
		// pull in windows types only in user mode
		
	#elif defined (_KERNEL_)
		#include "NdisProxy.h"		
	#endif
	
	// all MS-Windows variants are grouped in this file
	#include "WinTypes.h"

	#define HDI_ALIGNED

#elif defined (_LINUX) || defined (LINUX)
	// use the OS Abstraction Layer for Linux
	#include "wimax_osal_types.h"
	// #error "Inside Linux define"

#elif defined (WIN64)

	#if defined (_OS_WIN32SIM)
		// pull in windows types only in user mode
		#include <Windows.h>
	#elif defined (_KERNEL_)
		#include "NdisProxy.h"		
	#endif
	
	// all MS-Windows variants are grouped in this file
	#include "WinTypes.h"

	#define HDI_ALIGNED

#elif defined (__ARMCC_VERSION)

	// arm compiler mainly for the firmware
	#include "ArmTypes.h"

	#define HDI_ALIGNED		__align(16)

#else

	#error "Platform not supported. Please define the basic types for your platform and add it here"

#endif

// types derieved from standard types
#include "CommonTypes.h"

// not actually types but we didn't want to encumber with too many include files
#include "CommonDefinitions.h"

#endif	

#endif 
