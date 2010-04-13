/*
 * WPA Supplicant - Configuration defines for IDE builds
 * Copyright (c) 2005 Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef CFGDEFS_H
#define CFGDEFS_H

/* For now, use this file only for WIN32 builds with MSVC */
#ifndef CONFIG_NMAKE_DEFINES
#ifndef __MINGW32_VERSION
#ifdef _WIN32

#define CONFIG_ANSI_C_EXTRA

#define CONFIG_CTRL_IFACE_CB
#define CONFIG_CTRL_IFACE
#define CONFIG_BACKEND_API  1
#undef CONFIG_WPA_REGISTRY
#define _CRT_SECURE_NO_DEPRECATE

/*
 * Generic Driver Support
 */

#undef CONFIG_DRIVER_NDISUIO
#undef CONFIG_DRIVER_NDISUIO_EVENT
#ifndef EAP_PLUGIN_METHOD_DEFINED
#define CONFIG_DRIVER_NDIS
#endif
#define CONFIG_NATIVE_WINDOWS
#undef CONFIG_DRIVER_WEXT
#undef CONFIG_DRIVER_NDISWRAPPER
#undef CONFIG_DRIVER_TEST
#undef CONFIG_DRIVER_WIRED
//#define CONFIG_NDIS_EVENTS_INTEGRATED
#undef CONFIG_NDIS_EVENTS_INTEGRATED


/*
 * Device-specific driver support
 */

#undef CONFIG_DRIVER_HOSTAP
#undef CONFIG_DRIVER_HERMES
#undef CONFIG_DRIVER_MADWIFI
#undef CONFIG_DRIVER_PRISM54
#undef CONFIG_DRIVER_ATMEL
#undef CONFIG_DRIVER_BROADCOM
#undef CONFIG_DRIVER_IPW
#undef CONFIG_DRIVER_BSD
#undef CONFIG_DRIVER_I802
#undef CONFIG_DRIVER_ISLSOFTMAC
#undef CONFIG_DRIVER_MARVELL

/*
 * Transport Layer Security support
 */

#define CONFIG_TLS_OPENSSL
#undef CONFIG_TLS_CERTICOM
#undef CONFIG_TLS_MATRIXSSL

/*
 * EAP/EAPOL
 */

#define IEEE8021X_EAPOL

#ifndef EAP_PLUGIN_METHOD_DEFINED
#define EAP_MD5
#define EAP_MSCHAPv2
#define EAP_TLS
#define EAP_PEAP
#define EAP_TTLS
#define EAP_GTC
#undef EAP_OTP
#define EAP_SIM /* EAP-SIM (enable PCSC_FUNCS, if EAP-SIM is used) */
#define EAP_PSK
#undef  EAP_PAX
#define EAP_LEAP
#define EAP_FAST
#define EAP_AKA /* EAP-AKA (enable PCSC_FUNCS, if EAP-AKA is used) */
#endif

#define PKCS12_FUNCS
#undef CONFIG_SMARTCARD
#define PCSC_FUNCS
#undef CONFIG_DNET_PCAP
#undef CONFIG_NO_STDOUT_DEBUG
#undef CONFIG_NO_CERT_TIME_CHECKS

/*
 * CCX Support
 */

#define CONFIG_CCX
#define CONFIG_CCX_NAC

/*
 * PeerKey Support
 */

#define CONFIG_PEERKEY

/*
 * IEEE 802.11w Support
 */

#define CONFIG_IEEE80211W

/*
 * Test code
 */

#undef CONFIG_EAPOL_TEST

#endif /* _WIN32 */
#endif /* __MINGW32_VERSION */
#endif /* CONFIG_NMAKE_DEFINES */

#endif /* CFGDEFS_H */
