/**************************************************************************
Copyright (c) 2007-2009, Intel Corporation. All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.

 3. Neither the name of the Intel Corporation nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

***************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_

/* Basic Types */
typedef signed char              S8;
typedef signed char              S08;
typedef unsigned char            U8;
typedef unsigned char            U08;
typedef volatile unsigned char   VU8;
typedef const unsigned char      CU8;

typedef signed short             S16;
typedef unsigned short           U16;
typedef volatile unsigned short  VU16;
typedef const unsigned short     CU16;
#define FIRST_INIT		1
typedef signed long              S32;
typedef unsigned long            U32;
typedef volatile unsigned long   VU32;
typedef const unsigned long      CU32;
#define LAST_INIT		0

#define S64     __int64
#define SW_VERSION 5, 10, 1047, 0
#define SW_VERSION_ST "5, 10, 1047, 0"
#define STANDARD_TIMEOUT 30000
#define LONG_OPERATIONS_TIMEOUT 60000
#define SHUTDOWN_TIMEOUT 3000	// To use in finalize/shutdown functions
#define TRAFFIC_CHECK_TIMEOUT 300

#define MAX_FILENAME_LEN 256
#define MAX_STRING_VALIDATE 4096


//////////////////////////////////////////////////////////////////////////
// Macros

#define ARRAY_ENTRIES(x)			( sizeof(x)/sizeof(x[0]) )
#define NULL_PTR_VAL_OR_ZERO(px)	((NULL != (px)) ? *(px) : 0 )

//////////////////////////////////////////////////////////////////////////
/*****************************************************************************/

typedef union {
  U8 byte[2];
  U16 word;
} UU16;

typedef union {
  U8 byte[4];
  U16 word[2];
  U32 dw;
} UU32;

typedef struct {
  U16 word[3];
} UU48;

typedef struct {
  U16 word[3];
  U16 reserved;
} word48_s;

typedef struct {
  U32 lo32;
  U16 hi16;
  U16 reserved;
} dw48_s;

typedef union {
  word48_s word48;
  dw48_s dw48;
} mac_addr_u;

typedef union {
  VU32* dw;
  VU16* word;
  VU8* byte;
} perif_ptr_u;

typedef union {
  U32* dw;
  U16* word;
  U8* byte;
} mem_ptr_u;

typedef union {
  U08 byte[8];  //7:0
  U16 word[4];  //7:6,5:4,3:2,1:0
  U32 dw[2];    //7:4,3:0
} UU64;

typedef union {
  U8 byte[16];
  U16 word[8];
  U32 dw[4];
} UU128; 


#define mic64_u UU64
#define iv64_u UU64
#define TSFType_u UU64
#define key128_u UU128


/*****************************************************************************/
/* Constants */

#ifndef TRUE
    #define TRUE                    (1)
#endif /* TRUE */

#ifndef FALSE
    #define FALSE                   (0)
#endif /* FALSE */

#ifndef NULL
    #define NULL                    (0)
#endif /* NULL */

#ifndef IN
    #define IN
#endif /* IN */

#ifndef OUT
    #define OUT
#endif /* OUT */

#ifndef INOUT
    #define INOUT
#endif /* INOUT */

#ifndef MAX
#define MAX(a,b)    ( ((a) > (b)) ? (a) : (b) )
#endif // MAX

#ifndef MIN
#define MIN(a,b)    ( ((a) < (b)) ? (a) : (b) )
#endif // MIN


/* defines a packed structure according to platform */
#if defined(_WIN32)     /* windows driver, SV tools */
#define PACKED_PRE
#define PACKED_POST
#elif defined(__GNUC__) /* linux driver */
#define PACKED_PRE
#define PACKED_POST         __attribute__ ((packed))
#else                   /* firmware  */
#define PACKED_PRE          _Packed
#define PACKED_POST
#endif

#ifdef PIPE_HANDLER_EXPORTS
#define EXPORT __declspec( dllexport )
#else
#define EXPORT 
#endif

typedef enum _DRIVER_STATUS
{
	DRIVER_DOWN,	
	DRIVER_UP
} DRIVER_STATUS;

//////////////////////////////////////////////////////////////////////////
// ASSERT / VERIFY

#if (!defined(WINCE))
	#if (defined(_DEBUG) || defined(DEBUG))
		#include <crtdbg.h>

		#define ASSERT()           _ASSERTE(0)
		//#define ASSERT()           { _asm{int 3} }
		#define VERIFY(f)          { if( !(f) ) { ASSERT(); } }
		//#define VERIFY(f)          { if( !(f) ){ _asm{int 3} } }
	#else // DEBUG
		#define ASSERT()            ( (void)0 )
		#define VERIFY(f)			( (void)(f) )
	#endif
#else
	#if (defined(_DEBUG) || defined(DEBUG))
		#define ASSERT( )  DBGCHK(TEXT("Unknown"), FALSE)
		#define VERIFY(exp)  DBGCHK(TEXT("Unknown"), exp)
	#else
		#define ASSERT()            ( (void)0 )
		#define VERIFY(f)			( (void)(f) )
	#endif
#endif

#endif /* _COMMON_H_ */






