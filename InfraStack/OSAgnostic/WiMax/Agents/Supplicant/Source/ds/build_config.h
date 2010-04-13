/*
 * wpa_supplicant/hostapd - Build time configuration defines
 * Copyright (c) 2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * All Rights Reserved.
 *
 * This header file can be used to define configuration defines that were
 * originally defined in Makefile. This is mainly meant for IDE use or for
 * systems that do not have suitable 'make' tool. In these cases, it may be
 * easier to have a single place for defining all the needed C pre-processor
 * defines.
 */

#ifndef BUILD_CONFIG_H
#define BUILD_CONFIG_H

/* Insert configuration defines, e.g., #define EAP_MD5, here, if needed. */

#ifdef _WIN32
/* Backwards compatibility - SWC 1.1 used cfgdefs.h for WinCE parameters. */
#include "cfgdefs.h"
#endif /* _WIN32 */

#endif /* BUILD_CONFIG_H */
