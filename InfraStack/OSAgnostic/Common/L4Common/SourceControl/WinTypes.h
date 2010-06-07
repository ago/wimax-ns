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
 * WinTypes.h
 *
 * This file is for MS Compilers.
 * 
 * @version 1.1    06-July-2005    Yariv Barkan\n
 *    Minor modifications
 *
 * @version 1.0    05-June-2005    Pavel Aronsky\n
 *    Initial version
 *
 */

#ifndef __WINTYPES_H
#define __WINTYPES_H

// signed
typedef signed int			INT;
typedef signed char			INT8;
typedef signed short		INT16;
typedef signed int			INT32;
typedef signed __int64		INT64;

// unsigned
typedef unsigned int		UINT;
typedef unsigned char		UINT8;
typedef unsigned short		UINT16;
typedef unsigned int		UINT32;
typedef unsigned __int64	UINT64;

//#ifndef WIN32 && WIN64
#if !defined(_OS_WIN32SIM) && !defined(_OS_WIN64IM)
	// basic boolean
	typedef int		BOOL;	
#endif

#endif // __WINTYPES_H
