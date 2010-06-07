/**
 * @file 
 *
 * Pal_General.h
 * 
 * This file contains general exported PAL definitions. This is not the place
 * for utility macros, inline functions, general configuration etc. The correct
 * places for these are:
 *
 * - Types/<Platform>.h - Platform specific definition of standard global types, e.g. UINT.
 * - Pal_Utils.h        - Utility macros (min/max...), Pal version of RTL (Run Time Library - memcopy etc).
 * - BitOps.h           - Bit manipulation and endianess business.
 *
 * ... (define the appropriate include files for other global definitions)
 *
 *
 * @Note: documentation on this file is Pal_General.doc.
 *
 * Revisions
 * @version 1.4    7-July-2005		Yariv Barkan	Refactoring
 * @version 1.3    20-June-2005		Yariv Barkan	Refactoring
 * @version 1.2    29-May-2005		Yariv Barkan	Coding conventions, revision for ARMC +pa
 * @version 1.1    18-May-2005		Pavel Aronsky	More bit macros, PAL_STATUS, CALLBACK, FASTCALL
 * @version 1.0    19-April-2005	Pavel Aronsky	Initial version
 *
 */

#ifndef __PAL_GENERAL_H
#define __PAL_GENERAL_H 1

// need some basic types
#include "TypesProxy.h"

// Define PAL_STATUS as *generic* UINT for efficiency, but use only lower 2 bytes (see docum.)
typedef UINT STATUS_T;

typedef	STATUS_T PAL_STATUS;

typedef PVOID PAL_HANDLE;

// Define attributes for a callback functions. *TODO*
// By default MS uses cdecl in usermode and syscall in kernel
// For other environments: revise. Currently defined as nothing.
// To override this definition, use project defines.
#if !defined(PAL_CALLBACK)
	#define PAL_CALLBACK 
#endif

#endif  //__PAL_GENERAL_H
