/*
 * WFA Simple Config: (Wireless Simple Config) types
 * Copyright 2006 Devicescape Software, Inc.  
 * Erik Anvik <erik@devicescape.com> 
 * All Rights Reserved.
 */
#ifndef _WSC_TYPES_H_
#define _WSC_TYPES_H_

#include <linux/types.h>

/* WSC types */

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef u32
#define u32 unsigned int
#endif

#ifndef ulong
#define ulong unsigned long
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE  (1)
#endif

/* Macros */

#ifndef BIT
#define BIT(x) (1 << x)
#endif

#ifndef _WSC_STRUCT_PACKED_ 
#define _WSC_STRUCT_PACKED_ __attribute__ ((packed))
#endif

#ifndef ETH_ALEN
#define ETH_ALEN (6)
#endif

#ifndef NELEMS
#define NELEMS(a) (sizeof(a) / sizeof(a[0]))
#endif

typedef int (*PHANDLER)();

#endif /* _WSC_TYPES_H_ */
