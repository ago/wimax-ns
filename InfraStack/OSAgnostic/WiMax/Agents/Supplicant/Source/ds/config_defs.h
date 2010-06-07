/*
 * WPA Supplicant - configuration defines
 * Copyright (c) 2003-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright (c) 2004-2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef CONFIG_DEFS_H
#define CONFIG_DEFS_H

#define WPA_CIPHER_NONE BIT(0)
#define WPA_CIPHER_WEP40 BIT(1)
#define WPA_CIPHER_WEP104 BIT(2)
#define WPA_CIPHER_TKIP BIT(3)
#define WPA_CIPHER_CCMP BIT(4)
#define WPA_CIPHER_CKIP BIT(5)
#define WPA_CIPHER_CMIC BIT(6)
#define WPA_CIPHER_CKIP_CMIC BIT(7)
#ifdef CONFIG_IEEE80211W
#define WPA_CIPHER_AES_128_CMAC BIT(8)
#endif /* CONFIG_IEEE80211W */

#define WPA_KEY_MGMT_IEEE8021X BIT(0)
#define WPA_KEY_MGMT_PSK BIT(1)
#define WPA_KEY_MGMT_NONE BIT(2)
#define WPA_KEY_MGMT_IEEE8021X_NO_WPA BIT(3)
#define WPA_KEY_MGMT_WPA_NONE BIT(4)
#define WPA_KEY_MGMT_CCKM BIT(5)

#define WPA_PROTO_WPA BIT(0)
#define WPA_PROTO_RSN BIT(1)

#define WPA_AUTH_ALG_OPEN BIT(0)
#define WPA_AUTH_ALG_SHARED BIT(1)
#define WPA_AUTH_ALG_LEAP BIT(2)

#define MAX_SSID_LEN 32
#define PMK_LEN 32
#define EAP_PSK_LEN 16
#define MAX_PASSPHRASE_LEN 64

#define EAPOL_FLAG_REQUIRE_KEY_UNICAST BIT(0)
#define EAPOL_FLAG_REQUIRE_KEY_BROADCAST BIT(1)

#define NUM_WEP_KEYS 4
#define MAX_WEP_KEY_LEN 16

#ifdef EAP_SIMPLE_CONFIG
#define SIMPLE_CFG_SSID "wsc\0"
#define SIMPLE_CFG_SSID_LEN (strlen(SIMPLE_CFG_SSID))
#endif

#endif /* CONFIG_DEFS_H */
