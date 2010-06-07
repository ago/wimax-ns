/*
 * WFA Simple Config: Attribute includes
 * Copyright 2006 Devicescape Software, Inc.
 * Erik Anvik <erik@devicescape.com>
 * All Rights Reserved.
 */
#ifndef _WSC_ATTRIBUTES_H_
#define _WSC_ATTRIBUTES_H_

#include "wsc_types.h"
#include "wsc_common.h"

/* WSC attributes, where ND == Not Defined */
enum {
	/* attribute description       Identifier  Length    */
	WSC_AP_CHANNEL = 0x1001,  /* 0x1001       2B       */
	WSC_ASSOC_STATE,          /* 0x1002       2B       */
	WSC_AUTH_TYPE,            /* 0x1003       2B       */
	WSC_AUTH_TYPE_FLAGS,      /* 0x1004       2B       */
	WSC_AUTHENTICATOR,        /* 0x1005       8B       */
	WSC_RESERVED1,            /* 0x1006       ND       */
	WSC_RESERVED2,            /* 0x1007       ND       */
	WSC_CONFIG_METHODS,       /* 0x1008       2B       */
	WSC_CONFIG_ERROR,         /* 0x1009       2B       */
	WSC_CONFIG_URL4,          /* 0x100A       <= 64B   */
	WSC_CONFIG_URL6,          /* 0x100B       <= 76B   */
	WSC_CONNECT_TYPE,         /* 0x100C       1B       */
	WSC_CONNECT_TYPE_FLAGS,   /* 0x100D       1B       */
	WSC_CREDENTIAL,           /* 0x100E       ND       */
	WSC_ENCRYPTION_TYPE,      /* 0x100F       2B       */
	WSC_ENCRYPTION_TYPE_FLAGS,/* 0x1010       2B       */
	WSC_DEVICE_NAME,          /* 0x1011       <= 32B   */
	WSC_DEVICE_PWD_ID,        /* 0x1012       2B       */
	WSC_DEVICE_TYPE,          /* 0x1013       <= 32B   */
	WSC_E_HASH_1,             /* 0x1014       32B      */
	WSC_E_HASH_2,             /* 0x1015       32B      */
	WSC_E_SNONCE_1,           /* 0x1016       16B      */
	WSC_E_SNONCE_2,           /* 0x1017       16B      */
	WSC_ENCRYPTED_SETTINGS,   /* 0x1018       ND       */
	WSC_RESERVED3,            /* 0x1019       ND       */
	WSC_ENROLLEE_NONCE,       /* 0x101A       16B      */
	WSC_FEATURE_ID,           /* 0x101B       4B       */
	WSC_IDENITITY,            /* 0x101C       <= 80B   */
	WSC_IDENITITY_PROOF,      /* 0x101D       ND       */
	WSC_KEY_WRAP_AUTH,        /* 0x101E       8B       */
	WSC_KEY_IDENTIFIER,       /* 0x101F       16B      */
	WSC_MAC_ADDRESS,          /* 0x1020       6B       */
	WSC_MANUFACTURER,         /* 0x1021       64B      */
	WSC_MSG_TYPE,             /* 0x1022       1B       */
	WSC_MODEL_NAME,           /* 0x1023       <= 32B   */
	WSC_MODEL_NUMBER,         /* 0x1024       <= 32B   */
	WSC_RESERVED4,            /* 0x1025       ND       */
	WSC_NETWORK_INDEX,        /* 0x1026       1B       */
	WSC_NETWORK_KEY,          /* 0x1027       <= 64B   */
	WSC_NETWORK_KEY_INDEX,    /* 0x1028       1B       */
	WSC_NEW_DEVICE_NAME,      /* 0x1029       <= 32B   */
	WSC_NEW_PASSWORD,         /* 0x102A       <= 64B   */
	WSC_RESERVED5,            /* 0x102B       ND       */
	WSC_OOB_DEVICE_PASSWORD,  /* 0x102C       <= 58B   */
	WSC_OS_VERSION,           /* 0x102D       4B       */
	WSC_RESERVED6,            /* 0x102E       ND       */
	WSC_POWER_LEVEL,          /* 0x102F       1B       */
	WSC_PSK_CURRENT,          /* 0x1030       1B       */
	WSC_PSK_MAX,              /* 0x1031       1B       */
	WSC_PUBLIC_KEY,           /* 0x1032       192B     */
	WSC_RADIO_ENABLED,        /* 0x1033       Boolean  */
	WSC_RADIO_REBOOT,         /* 0x1034       Boolean  */
	WSC_REGISTRAR_CURRENT,    /* 0x1035       1B       */
	WSC_REGISTRAR_ESTABLISHED,/* 0x1036       Boolean  */
	WSC_REGISTRAR_LIST,       /* 0x1037       <= 512B  */
	WSC_REGISTRAR_MAX,        /* 0x1038       1        */
	WSC_REGISTRAR_NONCE,      /* 0x1039       16B      */
	WSC_REQUEST_TYPE,         /* 0x103A       1B       */
	WSC_RESPONSE_TYPE,        /* 0x103B       1B       */
	WSC_RF_BAND,              /* 0x103C       1B       */
	WSC_R_HASH_1,             /* 0x103D       32B      */
	WSC_R_HASH_2,             /* 0x103E       32B      */
	WSC_R_SNONCE_1,           /* 0x103F       16B      */
	WSC_R_SNONCE_2,           /* 0x1040       16B      */
	WSC_SELECTED_REGISTRAR,   /* 0x1041       Boolean  */
	WSC_SERIAL_NUMBER,        /* 0x1042       <= 32B   */
	WSC_SID,                  /* 0x1043       32B      */
	WSC_SIMPLE_CONFIG_STATE,  /* 0x1044       1B       */
	WSC_SSID,                 /* 0x1045       32B      */
	WSC_TOTAL_NETWORKS,       /* 0x1046       1B       */
	WSC_UUID_E,               /* 0x1047       16B      */
	WSC_UUID_R,               /* 0x1048       16B      */
	WSC_VENDOR_EXTENSIONS,    /* 0x1049       <= 1024B */
	WSC_VERSION,              /* 0x104A       1B       */
	WSC_X509_CERT_REQUEST,    /* 0x104B       ND       */
	WSC_X509_CERT,            /* 0x104C       ND       */
	WSC_EAP_IDENTITY,         /* 0x104D       <= 64B   */
	WSC_MESSAGE_COUNTER,      /* 0x104E       8B       */
	WSC_PUBLIC_KEY_HASH,      /* 0x104F       20B      */
	WSC_REKEY_KEY,            /* 0x1050       32B      */
	WSC_KEY_LIFETIME,         /* 0x1051       4B       */
	WSC_PERMITTED_CONFIG,     /* 0x1052       2B       */
	WSC_SELECTED_REG_CONFIG,  /* 0x1053       2B       */
	WSC_PRIMARY_DEV_TYPE,     /* 0x1054       8B       */
	WSC_SECONDARY_DEV_LIST,   /* 0x1055       <= 128B  */
	WSC_PORTABLE_DEVICE,      /* 0x1056       1B       */	
	WSC_AP_SETUP_LOCKED,      /* 0x1057       1B       */	
	WSC_APPLICATION_LIST,     /* 0x1058       <= 512B  */	
	WSC_INIT_VECTOR           /* 0x1059       32B      */	

};

/* WSC data component set */

/* association states */
enum {
	WSC_ASSOC_NOT_ASSOCIATED = 0x00, /* 0x00 */
	WSC_ASSOC_CONNECT_SUCCESS,       /* 0x01 */
	WSC_ASSOC_CONFIG_FAILURE,        /* 0x02 */
	WSC_ASSOC_FAILURE,               /* 0x03 */
	WSC_ASSOC_IP_FAILURE             /* 0x04 */
};

/* authentication types */ 
enum {
	WSC_AUTH_OPEN     = 0x0001, /* 0x0001 */
	WSC_AUTH_WPA_PSK  = 0x0002, /* 0x0002 */
	WSC_AUTH_SHARED   = 0x0004, /* 0x0004 */
	WSC_AUTH_WPA      = 0x0008, /* 0x0008 */
	WSC_AUTH_WPA2     = 0x0010, /* 0x0010 */
	WSC_AUTH_WPA2_PSK = 0x0020  /* 0x0020 */
};

/* configuration methods */ 
enum {
	WSC_CONFIG_USBA          = 0x0001, /* 0x0001 */
	WSC_CONFIG_ETHERNET      = 0x0002, /* 0x0002 */
	WSC_CONFIG_LABEL         = 0x0004, /* 0x0004 */
	WSC_CONFIG_DISPLAY       = 0x0008, /* 0x0008 */
	WSC_CONFIG_EXTERN_NFC    = 0x0010, /* 0x0010 */
	WSC_CONFIG_INTERN_NFC    = 0x0020, /* 0x0020 */
	WSC_CONFIG_NFC_INTERFACE = 0x0040, /* 0x0040 */
	WSC_CONFIG_PUSH_BUTTON   = 0x0080, /* 0x0080 */
	WSC_CONFIG_KEY_PAD       = 0x0100  /* 0x0100 */	
};

/* configuration errors */
enum {
	WSC_CONFIG_NO_ERROR = 0x00,        /* 0x00 */
	WSC_CONFIG_OOB_IF_READ,            /* 0x01 */
	WSC_CONFIG_DECRYPT_CRC,            /* 0x02 */
	WSC_CONFIG_24_CHAN_NO_SUPPORT,     /* 0x03 */
	WSC_CONFIG_50_CHAN_NO_SUPPORT,     /* 0x04 */
	WSC_CONFIG_SIGNAL_TOO_WEAK,        /* 0x05 */
	WSC_CONFIG_NETWORK_AUTH,           /* 0x06 */
	WSC_CONFIG_NETWORK_ASSOC,          /* 0x07 */
	WSC_CONFIG_NO_DHCP_RESPONSE,       /* 0x08 */
	WSC_CONFIG_FAIL_DHCP_CONFIG,       /* 0x09 */
	WSC_CONFIG_IP_ADDR_CONFLICT,       /* 0x0A */
	WSC_CONFIG_FAIL_REGISTRAR_CONNECT, /* 0x0B */
	WSC_CONFIG_MULTIPLE_PBC_SESSIONS,  /* 0x0C */
	WSC_CONFIG_ROUGUE_ACTIVITY,        /* 0x0D */
	WSC_CONFIG_DEVICE_BUSY,            /* 0x0E */ 
	WSC_CONFIG_SETUP_LOCKED,           /* 0x0F */ 
	WSC_CONFIG_MESSAGE_TIMEOUT,        /* 0x10 */ 
	WSC_CONFIG_REG_SESSION_TIMEOUT,    /* 0x11 */ 
	WSC_CONFIG_PASSWORD_AUTH_FAILED,   /* 0x12 */
	WSC_CONFIG_LOCK_STEP_FAIL          /* 0x13 */
};

/* connection types */
enum {
	WSC_CONNECTION_ESS = 0x01, /* 0x01 */
	WSC_CONNECTION_IBSS        /* 0x02 */
};

/* device password ID types */
enum {
	WSC_PASSWORD_ID_DEFAULT = 0x00,     /* 0x00 */
	WSC_PASSWORD_ID_USER_SPECIFIED,     /* 0x01 */
	WSC_PASSWORD_ID_MACHINE_SPECIFIED,  /* 0x02 */
	WSC_PASSWORD_ID_REKEY,              /* 0x03 */
	WSC_PASSWORD_ID_PUSH_BUTTON,        /* 0x04 */
	WSC_PASSWORD_ID_REGISTRAR_SPECIFIED /* 0x05 */
};


/* encryption type flags */
enum {
	WSC_ENRYPT_TYPE_NONE = 0x0001,
	WSC_ENRYPT_TYPE_WEP  = 0x0002,
	WSC_ENRYPT_TYPE_TKIP = 0x0004,
	WSC_ENRYPT_TYPE_AES  = 0x0008
};

/* message types */
enum {
	WSC_MSG_TYPE_BEACON = 0x01, /* 0x01 */
	WSC_MSG_TYPE_PROBE_REQ,     /* 0x02 */
	WSC_MSG_TYPE_PROBE_RESP,    /* 0x03 */
	WSC_MSG_TYPE_M1,            /* 0x04 */
	WSC_MSG_TYPE_M2,            /* 0x05 */
	WSC_MSG_TYPE_M2D,           /* 0x06 */
	WSC_MSG_TYPE_M3,            /* 0x07 */
	WSC_MSG_TYPE_M4,            /* 0x08 */ 
	WSC_MSG_TYPE_M5,            /* 0x09 */
	WSC_MSG_TYPE_M6,            /* 0x0A */
	WSC_MSG_TYPE_M7,            /* 0x0B */
	WSC_MSG_TYPE_M8,            /* 0x0C */
	WSC_MSG_TYPE_ACK,           /* 0x0D */
	WSC_MSG_TYPE_NACK,          /* 0x0E */
	WSC_MSG_TYPE_DONE           /* 0x0F */	
};


/* TODO Add Network Key Table */

/* request types */
enum {
	WSC_REQ_TYPE_ENROLLEE_INFO = 0x00,  /* 0x00 */
	WSC_REQ_TYPE_ENROLLEE_8021X,        /* 0x01 */
	WSC_REQ_TYPE_REGISTRAR,             /* 0x02 */
	WSC_REQ_TYPE_WLAN_MANAGER_REGISTRAR /* 0x03 */
};

/* response types */
enum {
	WSC_RESP_TYPE_ENROLLEE_INFO = 0x00, /* 0x00 */
	WSC_RESP_TYPE_ENROLLEE_8021X,       /* 0x01 */
	WSC_RESP_TYPE_REGISTRAR,            /* 0x02 */
	WSC_RESP_TYPE_AP                    /* 0x03 */
};

/* RF bands */
enum {
	WSC_RF_BAND_24GHZ = 0x01, /* 0x01 */
	WSC_RF_BAND_50GHZ         /* 0x02 */
};

/* simple config state */
enum {
	WSC_SIMPLE_CONFIG_NOT_CONFIGURED = 0x01, /* 0x01 */
	WSC_SIMPLE_CONFIG_CONFIGURED             /* 0x02 */
};

/* primary device type ID */
enum {
	WSC_CAT_COMPUTER = 1,
	WSC_CAT_INPUT_DEVICE,           
	WSC_CAT_COPIER,			
	WSC_CAT_CAMERA,			
	WSC_CAT_STORAGE,		
	WSC_CAT_NETWORK_INFRASTRUCTURE,
	WSC_CAT_DISPLAY,
	WSC_CAT_MULTIMEDIA_DEVICE,
	WSC_CAT_GAMING_DEVICE,
	WSC_CAT_TELEPHONE
};

/* primary device subcategory */

/* computer device subcategories */
#define WSC_SUBCAT_PC 		(1)
#define WSC_SUBCAT_SERVER       (WSC_SUBCAT_PC + 1)
#define WSC_SUBCAT_MEDIA_CENTER (WSC_SUBCAT_PC + 2)

/* copier device subcategories */
#define WSC_SUBCAT_PRINTER      1
#define WSC_SUBCAT_SCANNER      (WSC_SUBCAT_PRINTER + 1)

/* camera device subcategories */
#define WSC_SUBCAT_DIGITAL_STILL_CAMERA (1)

/* storage device subcategories */
#define WSC_SUBCAT_NAS		(1)

/* network infrastructure device subcategories */
#define WSC_SUBCAT_AP		(1)
#define WSC_SUBCAT_ROUTER	(WSC_SUBCAT_AP + 1)
#define WSC_SUBCAT_SWITCH	(WSC_SUBCAT_AP + 2)

/* display device subcategories */
#define WSC_SUBCAT_TELEVISION	 (1)
#define WSC_SUBCAT_PICTURE_FRAME (WSC_SUBCAT_TELEVISION + 1)
#define WSC_SUBCAT_PROJECTOR	 (WSC_SUBCAT_TELEVISION + 2)

/* multimedia device subcategories */
#define WSC_SUBCAT_DAR		(1)
#define WSC_SUBCAT_PVR		(WSC_SUBCAT_DAR + 1)
#define WSC_SUBCAT_MCX		(WSC_SUBCAT_DAR + 2)

/* gaming device subcategories */
#define WSC_SUBCAT_XBOX		(1)
#define WSC_SUBCAT_XBOX_360	(WSC_SUBCAT_XBOX + 1)
#define WSC_SUBCAT_PLAYSTATION	(WSC_SUBCAT_XBOX + 2)

/* telephone device subcategories */
#define WSC_SUBCAT_WINDOWS_MOBILE (1)

/* create attribute stack structure - EJA */

void  wsc_attribute_create(struct wsc_buffer_ctx*, int);
void *wsc_attribute_get_msg(char*, int, u16, u16*);
int wsc_attribute_type_check(void *, int);
 
#endif /* _WSC_ATTRIBUTES_H_ */
