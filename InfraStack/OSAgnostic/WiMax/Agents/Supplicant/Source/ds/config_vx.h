/*
 * WPA Supplicant / Configuration file parser for VxWorks
 * Copyright (c) 2003-2004, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright (c) 2004, Instant802 Networks, Inc.
 * All Rights Reserved.
 */

#ifndef CONFIG_VX_H
#define CONFIG_VX_H

#include "config_defs.h"

#ifndef BIT
#define BIT(x) (1 << (x))
#endif

#define WPA_FLAGS_DEBUG		BIT(0)
#define WPA_FLAGS_DAEMONIZE     BIT(1)
#define WPA_FLAGS_USAGE         BIT(2)
#define WPA_FLAGS_LICENSE       BIT(3)
#define WPA_FLAGS_VERSION       BIT(4)
#define WPA_FLAGS_WAIT_FOR_IF   BIT(5)
#define WPA_FLAGS_DISABLE_EAPOL	BIT(6)

#define WPA_EAP_TYPE_NONE		 0
#define WPA_EAP_TYPE_IDENTITY		 1
#define WPA_EAP_TYPE_NOTIFICATION	 2
#define WPA_EAP_TYPE_NAK		 3
#define WPA_EAP_TYPE_MD5		 4
#define WPA_EAP_TYPE_OTP		 5
#define WPA_EAP_TYPE_GTC		 6
#define WPA_EAP_TYPE_TLS		 13
#define WPA_EAP_TYPE_LEAP		 17
#define WPA_EAP_TYPE_SIM		 18
#define WPA_EAP_TYPE_TTLS		 21
#define WPA_EAP_TYPE_PEAP		 25
#define WPA_EAP_TYPE_MSCHAPV2		 26
#define WPA_EAP_TYPE_TLV		 33

#define MAX_EAP_METHODS		16

#ifndef ETH_ALEN
#define ETH_ALEN	6
#endif

typedef struct _wpa_cert {
	u8 *			ca_cert;
	u8 *			client_cert;
	u8 *			private_key;
	u8 *			private_key_passwd;
} wpa_certificate_t;

typedef struct _wpa_wep_key {
	size_t			len;
	u8			key[MAX_WEP_KEY_LEN];
} wpa_wep_key_t;

typedef struct _wpa_string {
	size_t			len;
	u8 *			string;
} wpa_string_t;

typedef struct _wpa_config {
	/* Priority group */
	int			priority;

	/* SSID */
	size_t			ssid_len;
	u8			ssid[MAX_SSID_LEN];
	int			scan_ssid; /* scan this SSID with Probe Requests */

	/* BSSID */

	int			bssid_set;
	u8			bssid[ETH_ALEN];

	/* WPA-PSK Settings */
	int			psk_set;
	u8			psk[PMK_LEN];
	char 			passphrase[MAX_PASSPHRASE_LEN];

	/* Bitfields of allowed Pairwise/Group Ciphers, WPA_CIPHER_* */
	int			pairwise_cipher;
	int			group_cipher;
	int			key_mgmt;

	/* Bitfield of allowed protocols (WPA_PROTO_*) */
	int			proto;

	/* EAP Identity */
	wpa_string_t		identity;
	wpa_string_t		anonymous_identity; /* Anonymous EAP Identity (for unencrypted use
				 		     * with EAP types that support different
				 		     * tunnelled identity, e.g., EAP-TTLS) */
	wpa_string_t		password;

	/* Certificate information */
	wpa_certificate_t	cert;
	wpa_certificate_t	cert2;

	/* EAP methods list (zero terminated) */
	u8 			eap_methods[MAX_EAP_METHODS];

	wpa_string_t		phase1;
	wpa_string_t		phase2;
	wpa_string_t		pcsc;
	wpa_string_t		pin;

	int			eapol_flags; /* bit field of IEEE 802.1X/EAPOL options */

	wpa_wep_key_t		wep_keys[NUM_WEP_KEYS];
	int			wep_tx_keyidx;

	int			eapol_version;
	int			ap_scan;

} wpa_config_t;

/* Function Prototype */

extern int wpa_supplicant (char* ifname, char * driver, wpa_config_t * cfg,
			   int flags, int debug);

#endif /* CONFIG_VX_H */
