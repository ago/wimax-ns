/*
 * WPA Supplicant
 * Copyright (c) 2005, Devicescape Software, Inc.
 * All Rights Reserved.
 *
 * Note: Unlike other files of wpa_supplicant, parts of this file is _not_
 * released under GPL/BSD license.
 */

#ifndef CONFIG_API_H
#define CONFIG_API_H

/******************* Definitions ********************/

#ifndef BIT
#define BIT(x) (1 << (x))
#endif


/* use with swc_set_cipher */
#define SWC_CIPHER_NONE BIT(0)
#define SWC_CIPHER_WEP40 BIT(1)
#define SWC_CIPHER_WEP104 BIT(2)
#define SWC_CIPHER_TKIP BIT(3)
#define SWC_CIPHER_CCMP BIT(4)
#define SWC_CIPHER_CKIP BIT(5)
#define SWC_CIPHER_CMIC BIT(6)
#define SWC_CIPHER_CKIP_CMIC BIT(7)

/* use with swc_set_key_management */
#define SWC_KEY_MGMT_IEEE8021X BIT(0)	/* WPA */
#define SWC_KEY_MGMT_PSK BIT(1)		/* WPA-PSK */
#define SWC_KEY_MGMT_NONE BIT(2)	/* No key management */
#define SWC_KEY_MGMT_IEEE8021X_NO_WPA BIT(3)	/* Plain IEEE802.1x */
#define SWC_KEY_MGMT_WPA_NONE BIT(4)		/* Special mode for adhoc+WPA */
#define SWC_KEY_MGMT_CCKM BIT(5)		/* CCKM */


/* EAP-FAST Provisioning modes */
#define SWC_FAST_PROV_AUTH BIT(0)
#define SWC_FAST_PROV_ANON BIT(1)
#define SWC_FAST_PROV_ANY (SWC_FAST_PROV_AUTH|SWC_FAST_PROV_ANON)


/* use with swc_set_proto */
#define SWC_PROTO_WPA BIT(0)
#define SWC_PROTO_RSN BIT(1)

/* use with swc_set_eap_method */
#define SWC_EAP_TYPE_NONE		 0
#define SWC_EAP_TYPE_IDENTITY		 1
#define SWC_EAP_TYPE_NOTIFICATION	 2
#define SWC_EAP_TYPE_NAK		 3
#define SWC_EAP_TYPE_MD5		 4
#define SWC_EAP_TYPE_OTP		 5
#define SWC_EAP_TYPE_GTC		 6
#define SWC_EAP_TYPE_TLS		 13
#define SWC_EAP_TYPE_LEAP		 17
#define SWC_EAP_TYPE_SIM		 18
#define SWC_EAP_TYPE_TTLS		 21
#define SWC_EAP_TYPE_PEAP		 25
#define SWC_EAP_TYPE_MSCHAPV2		 26
#define SWC_EAP_TYPE_TLV		 33
#define SWC_EAP_TYPE_FAST		 43
#define SWC_EAP_TYPE_PSK		 255 /* Not defined */
#define SWC_EAP_TYPE_AKA		 23 /* Not defined */

/* use with swc_set_auth_alg */
#define SWC_AUTH_ALG_OPEN BIT(0)
#define SWC_AUTH_ALG_SHARED BIT(1)
#define SWC_AUTH_ALG_LEAP BIT(2)

#define MAX_SSID_LEN 32
#define PMK_LEN 32
#define EAP_PSK_LEN 16
#define MAX_PASSPHRASE_LEN 64
#define NUM_WEP_KEYS 4
#define MAX_WEP_KEY_LEN 16

/* Phase2 auth methods for PEAP/TTLS/FAST use with swc_set_phase2_method */
#define SWC_PHASE2_METHOD_EAP_GTC	1
#define SWC_PHASE2_METHOD_EAP_MSCHAPV2	2
#define SWC_PHASE2_METHOD_EAP_MD5	3
#define SWC_PHASE2_METHOD_GTC		4
#define SWC_PHASE2_METHOD_MSCHAPV2	5
#define SWC_PHASE2_METHOD_MSCHAP	6
#define SWC_PHASE2_METHOD_CHAP		7
#define SWC_PHASE2_METHOD_EAP_TLS	8
#define SWC_PHASE2_METHOD_PAP		9

#define SWC_INTERFACE_TYPE_WIRELESS	1
#define SWC_INTERFACE_TYPE_WIRED	2
#define SWC_INTERFACE_TYPE_WIMAX	3

#define WPA_INTERFACE_TYPE_WIRELESS SWC_INTERFACE_TYPE_WIRELESS
#define WPA_INTERFACE_TYPE_WIRED SWC_INTERFACE_TYPE_WIRED
#define WPA_INTERFACE_TYPE_WIMAX SWC_INTERFACE_TYPE_WIMAX

/* Return status codes */
#define SWC_STATUS_SUCCESS		0
#define SWC_STATUS_GENERIC_ERROR	-1
#define SWC_STATUS_INVALID_ARG		-2
#define SWC_STATUS_NO_MEMORY		-3
#define SWC_STATUS_NO_DATA		-4
#define SWC_STATUS_BUF_TOO_SMALL	-5

#define MAX_EAP_METHODS		16
#define MAX_IFACE_NAME		128
#define MAX_ID_FIELD_LEN	128
#define MAX_PAC_FIELD_LEN	256
#define MAX_IE_LEN	256

#ifndef ETH_ALEN
#define ETH_ALEN	6
#endif

#define SWC_CALLBACK_TYPE_CREDENTIAL	1
#define SWC_CALLBACK_TYPE_EVENT		2

#define	SWC_CRED_IDENTITY		1
#define	SWC_CRED_PASSWORD		2
#define	SWC_CRED_PIN			3
#define	SWC_CRED_NEW_PASSWORD		4
#define	SWC_CRED_OTP			5
#define	SWC_CRED_PASSPHRASE		6
#define	SWC_CRED_PSEUDONYM		7
#define SWC_CRED_FASTPAC_TUNNEL		8	/* This event is unused */
#define SWC_CRED_FASTPAC_MACHINE	9
#define SWC_CRED_FASTPAC_USER		10	
#define SWC_CRED_PRIVATE_KEY		11	
#define SWC_CRED_CA_CERTIFICATE		12
#define SWC_CRED_FAST_AID		13

/* Common WiFi / WiMax events */
#define SWC_EV_REJECTED_CREDENTIAL	1
#define SWC_EV_REJECTED_METHOD		2
#define SWC_EV_REJECTED_IDENTITY	3
#define SWC_EV_REJECTED_CERTIFICATE	4
#define SWC_EV_REJECTED_CHALLENGE	5
#define SWC_EV_RESTRICTED_LOGON_HOURS	6
#define SWC_EV_ACCOUNT_DISABLED		7
#define SWC_EV_ACCOUNT_NO_DIAL_IN	8
#define SWC_EV_TLV_INVALID		9
#define SWC_EV_TLV_UNKNOWN		10
#define SWC_EV_TLV_NAK			11
#define SWC_EV_FAST_CMAC_INVALID	12
#define SWC_EV_FAST_PROVISION_SUCCESS	13
#define SWC_EV_FAST_INVALID_PAC_KEY	14
#define SWC_EV_FAST_INVALID_PAC_OPAQUE	15
#define SWC_EV_EAP_CLEAR_TEXT_FAILURE	16
#define SWC_EV_EAP_CLEAR_TEXT_SUCCESS	17
#define SWC_EV_EAP_FAILURE		18
#define SWC_EV_EAP_SUCCESS		19
#define SWC_EV_EAP_INTERMEDIATE_FAILURE	20
#define SWC_EV_EAP_INTERMEDIATE_SUCCESS	21
#define SWC_EV_SIM_PIN_INCORRECT	22
#define SWC_EV_SIM_PIN_REQUIRED		23
#define SWC_EV_SIM_NO_READER		24
#define SWC_EV_SIM_NO_CARD		25
#define SWC_EV_SIM_FAILURE		26
#define SWC_EV_EAP_METHOD_BASE 		0x1000 /* Not a real event, just an offset */

#define SWC_EV_EAP_METHOD_TLS	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_TLS)
#define SWC_EV_EAP_METHOD_TTLS	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_TTLS)
#define SWC_EV_EAP_METHOD_PEAP	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_PEAP)
#define SWC_EV_EAP_METHOD_SIM	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_SIM)
#define SWC_EV_EAP_METHOD_AKA	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_AKA)
#define SWC_EV_EAP_METHOD_PSK	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_PSK)
#define SWC_EV_EAP_METHOD_LEAP	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_LEAP)
#define SWC_EV_EAP_METHOD_FAST	(SWC_EV_EAP_METHOD_BASE + SWC_EAP_TYPE_FAST)

/* WiFi-Only Events */
#define SWC_EV_EAPOL_STOPPED		27
#define SWC_EV_EAPOL_CONNECTING		28
#define SWC_EV_EAPOL_AUTHENTICATING	29
#define SWC_EV_EAPOL_AUTHENTICATED	30
#define SWC_EV_EAPOL_REAUTHENTICATING	31
#define SWC_EV_EAPOL_UNAUTHENTICATED	32
#define SWC_EV_EAPOL_NOT_REQUIRED	33
//#define SWC_EV_EAPOL_NOT_REQUIRED	34
#define SWC_EV_KM_REKEY			35
#define SWC_EV_KM_KEY_PAIRWISE		36
#define SWC_EV_KM_KEY_GROUP		37
#define SWC_EV_KM_KEY_INVALID		38
#define SWC_EV_KM_WEP_TIMEOUT		39
#define SWC_EV_RSN_REQ_KEY_PAIRWISE	40
#define SWC_EV_RSN_REQ_KEY_GROUP	41
#define SWC_EV_RSN_COUNTERMEASURE_START	42
#define SWC_EV_RSN_COUNTERMEASURE_STOP	43
#define SWC_EV_RSN_MULTIPLE_FIRST_MSG	44
#define SWC_EV_RSN_DISCONNECT		45
#define SWC_EV_RSN_MIC_FAILURE		46
#define SWC_EV_CCX_CCKM_ROAM		47
#define SWC_EV_PORT_STATUS_UNKNOWN	48
#define SWC_EV_PORT_STATUS_STOPPED	49
#define SWC_EV_PORT_STATUS_STARTED	50
#define SWC_EV_PORT_STATUS_LINK_DOWN	51
#define SWC_EV_PORT_STATUS_LINK_UP	52
#define SWC_EV_PORT_STATUS_LINK_RESET	53
#define SWC_EV_802_1X_START		54
#define SWC_EV_802_1X_FAILED		55
#define SWC_EV_802_1X_ACQUIRED		56
#define SWC_EV_802_1X_LOGOFF		57
#define SWC_EV_802_1X_TIMEOUT		58
#define SWC_EV_EAP_KEY_AVAILABLE	59
#define SWC_EV_EAPOL_STARTED		60
#define SWC_EV_EAPOL_TIMEOUT		61
#define SWC_EV_NO_AAA_SERVER		62
#define SWC_EV_TUNNEL_ESTABLISHED	63
#define SWC_EV_REJECTED_SERVER_CERTIFICATE	64


/******************* Data Types ********************/

/* Configuration for certificates */
typedef struct _wpa_cert {
	u8 *			ca_cert;
	size_t			ca_cert_len;
	int			ca_cert_binary;

	u8 *			client_cert;
	size_t			client_cert_len;
	int			client_cert_binary;

	u8 *			private_key;
	size_t			private_key_len;
	int			private_key_binary;

	char *			private_key_passwd;
} wpa_certificate_t;

/* String + length */
typedef struct _wpa_string {
	size_t			len;
	char *			string;
} wpa_string_t;

typedef struct _swc_pac {
	u8	key[MAX_PAC_FIELD_LEN];
	size_t	key_len;

	u8	opaque[MAX_PAC_FIELD_LEN];
	size_t	opaque_len;

	u8	info[MAX_PAC_FIELD_LEN];
	size_t	info_len;

	u8	a_id[MAX_ID_FIELD_LEN];
	size_t	a_id_len;

	u8	a_id_info[MAX_ID_FIELD_LEN];
	size_t	a_id_info_len;

	u8	i_id[MAX_ID_FIELD_LEN];
	size_t	i_id_len;

	u32	type;
} swc_pac_t;

struct ctrl_iface_queue_entry {
	struct ctrl_iface_queue_entry *next;
	char *buf;
	size_t len;
};

typedef struct swc_assoc_info {
	u8 req_ies[MAX_IE_LEN];
	size_t req_ies_len;
	u8 resp_ies[MAX_IE_LEN];
	size_t resp_ies_len;
	u8 beacon_ies[MAX_IE_LEN];
	size_t beacon_ies_len;
} swc_assoc_info_t;


/*
 * Events from the driver. Comments indicate the type of data we expect to
 * receive for this event, if any. Used with swc_set_driver_event
 */
typedef enum {
	SWC_DRIVER_EVENT_ASSOC, /* data = swc_assoc_info_t */
	SWC_DRIVER_EVENT_DISASSOC, /* data = 802.11 reason code for deauth */
	SWC_DRIVER_EVENT_RX, /* data = NULL, supplicant will request packet */
	SWC_DRIVER_EVENT_MICERR, /* data = NULL */
	SWC_DRIVER_EVENT_PMKID_CANDIDATE, /* data =
					   * NDIS_802_11_PMKID_CANDIDATE_LIST */
} swc_driver_event_t;

struct driver_event_queue_entry {
	struct driver_event_queue_entry *next;
	swc_driver_event_t ev;
	u8 *data;
	int len;
};

/* Definitions for callbacks for OID manipulation and L2 packet handling. */

/*
 * swc_l2_cb - Callback type for L2 operations
 * @context - l2func_ctx parameter passed to swc_set_driver_l2
 * @tx - Boolean, if non-zero request is a TX, else it's an RX
 * @data - Data to send if tx == 0, buffer to receive into if tx != 0
 * @len - Pointer to length of data to send on TX. On RX the input value is
 *        the maximum size that can be stored in data, on output it should be
 *        modified to contain the actual length of data.
 */
typedef int (*swc_l2_cb)(void *context, int tx, u8 *data, size_t *len);

/*
 * swc_oid_cb - Callback type for NDIS OID operations
 * @context - oidfunc_ctx parameter passed to swc_set_driver_oid
 * @set - Boolean, if non-zero request is a OID set, else it's an OID get
 * @data - Buffer to hold OID data on if set == 0, OID data to send if set != 0
 * @len - Pointer to length of OID data to set on if set != 0. On OID get
 * 	  the input value is the maximum size that can be stored in data, on
 * 	  output it should be modified to contain the actual length of data.
 */
typedef int (*swc_oid_cb)(void *context, int set, u8 *data, size_t *len);


#define SWC_SCARD_EVENT_INSERTED	1 /* Inserted at runtime */
#define SWC_SCARD_EVENT_REMOVED		2 /* Removed at runtime */
#define SWC_SCARD_EVENT_UPDATE		3 /* Reader updated (e.g. new card) */

#define SWC_SCARD_FLAG_CARD_PRESENT	0x1 /* Card present */
#define SWC_SCARD_FLAG_CARD_VALID	0x2 /* Card valid */
#define SWC_SCARD_FLAG_CARD_OK		0x3 /* Card valid & present */
#define SWC_SCARD_FLAG_SIM		0x4 /* Supports SIM */
#define SWC_SCARD_FLAG_SMARTCARD	0x8 /* Supports smartcard TLS */

#define SMARTCARD_MAX_STR 128
#define SMARTCARD_MAX_BLOB 4096

typedef struct swc_scard_card_info {
	char	cardname[SMARTCARD_MAX_STR + 1];
	char	csp[SMARTCARD_MAX_STR + 1];
	u32	csplen;
	u8	certhash[SMARTCARD_MAX_BLOB];
	u32	certhashlen;
	u8	certblob[SMARTCARD_MAX_BLOB];
	u32	certbloblen;
	u8	cardatr[SMARTCARD_MAX_STR];
	u32	cardatrlen;
	u32	flags;
} swc_scard_card_info_t;


typedef struct swc_scard_event {
	u32			event;
	u8			reader_name[SMARTCARD_MAX_STR + 1];
	swc_scard_card_info_t	card_info;
} swc_scard_event_t;

/*
 * swc_scard_event_cb - Callback type for smartcard events
 * @context - scardfunc_ctx parameter passed to swc_scard_set_event_cb
 * @ev - Event that occurred
 */
typedef int (*swc_scard_event_cb)(void *context, swc_scard_event_t *ev);


/* Main configuration structure */
typedef struct _swc_config {

	/* Name of network interface and type (wireless/wired) */
	char			interface_name[MAX_IFACE_NAME];
	int			interface_type;

	/* Desired SSID */
	u8			ssid[MAX_SSID_LEN];
	size_t			ssid_len;

	/* WPA-PSK data. psk is a properly generated psk hash. passphrase is
	 * an ASCII string from which we will generate a psk hash. psk_set
	 * indicates that 'psk' is valid when set to non-zero.
	 */
	int			psk_set;
	u8			psk[PMK_LEN];
	char 			passphrase[MAX_PASSPHRASE_LEN + 1];

	/* Bit flags for cipher and key management, defined in config_defs.h */
	int			pairwise_cipher;
	int			group_cipher;
	int			key_mgmt;

	/* Bitfield of allowed protocols (SWC_PROTO_*) */
	int			proto;

	/* 802.11 authentication */
	int			auth_alg;

	/* EAP Identity */
	wpa_string_t		identity;
	wpa_string_t		password;
	wpa_string_t		new_password; /* for MSCHAPv2 P/W change */
	wpa_string_t		anonymous_identity;

	/* Certificate information */
	wpa_certificate_t	cert;
	int			cert_set;
	/* Certificate information when using TLS inside of TLS */
	wpa_certificate_t	cert2;
	int			cert_set2;

	/* EAP methods list (zero terminated) */
	u8 			eap_methods[MAX_EAP_METHODS + 1];
	int			eap_methods_count;

	wpa_string_t		phase1;
	wpa_string_t		phase2;

	/* EAP-FAST related parameters */
	wpa_certificate_t	fast_trusted_cert;
	swc_pac_t		pac; /* Binary pac, deprecated.... */
	int			pac_set;
	char *			pac_file;
	char *			pac_file_data;
	size_t			pac_file_data_len;
	swc_pac_t		pac_machine;
	int			pac_machine_set;
	char *			pac_machine_file;
	char *			pac_machine_file_data;
	size_t			pac_machine_file_data_len;
	int			fast_prov_mode;

	/* CCX NAC related parameters */
	char *			nac_module_dir;
	char *			nac_lib;

	/* EAP-SIM related parameters */
	wpa_string_t		sim_reader;
	wpa_string_t		sim_pin;
	char			*sim_pseudonym;

	void *			ctrl_iface_cb;
	void *			ctrl_iface_cb_ctx;
	int			ctrl_iface; /* initialized? */

	void *			cred_export_cb;
	void *			cred_export_cb_ctx;

	/* Internal supplicant related structures */
	void *			wpa_supplicant_ctx; /* struct wpa_supplicant **/
	void *			wpa_ssid;	    /* struct wpa_ssid * */
	void *			wpa_config; 	    /* struct wpa_config * */

	void *			eap_cb_get_bool;
	void *			eap_cb_set_bool;
	void *			eap_cb_get_int;
	void *			eap_cb_set_int;
	void *			eap_cb_get_eap_req_data;
	void *			eap_cb_get_config;
	void *			eap_cb_get_config_blob;
	void *			eap_cb_set_config_blob;
	void *			eap_cb_ctx;

	struct eap_sm *		eap_sm;

	/* Use config file, for testing only */
	char *			wpa_config_file;

	os_mutex_t		mutex;
	os_mutex_t		driver_event_q_mutex;
	/* Internal flag for testing facilities */
	int			wpa_supplicant_do_status;

	int			ctrl_iface_event;
	struct ctrl_iface_queue_entry *ctrl_iface_q;
	size_t			tls_max_size;

	u8			eappsk[16];
	size_t			eappsk_len;
	int			eappsk_set;

	u8 *			nai;
	size_t			nai_len;

	swc_l2_cb		l2_cb;
	void *			l2_cb_ctx;
	swc_oid_cb		oid_cb;
	void *			oid_cb_ctx;
#ifdef CONFIG_NATIVE_WINDOWS
	HANDLE			supp_event;
	HANDLE			exit_event;
	HANDLE			impersonation_handle;
	void *			scard_ctx;
	swc_scard_event_cb	scard_event_cb;
	void *			scard_event_cb_ctx;
	os_thread_t		scard_thread;
	HANDLE			scard_thread_sync;
#endif
	void *			l2_internal;
	void *			l2_testapp;
	struct driver_event_queue_entry *driver_event_q;

	char *			driver_name;

	os_thread_t		auth_thread;
	void *			srvcert_cb;
	void *			srvcert_cb_ctx;

	int			ap_scan_mode;

	wpa_string_t		subject_match;
	wpa_string_t		subject_match2;
	wpa_string_t		alt_subject_match;
	wpa_string_t		alt_subject_match2;

#ifdef CONFIG_PEERKEY
	int			peerkey;
#endif
#ifdef CONFIG_IEEE80211W
	int			ieee80211w;
#endif
} swc_config_t;

/******************* Prototypes ********************/

/* 			GENERAL INFORMATION
 *
 * All APIs return SWC_STATUS_SUCCESS in success, or other SWC_STATUS_* error
 * codes where appropriate. Any deviations from this are noted in the function
 * descriptions.
 *
 * Any functions where a pointer/legth is used, NULL/0 can be specified to
 * not set or reset the configuration.
 *
 * swc_config_t is created and initalized using swc_config_alloc
 *
 * After this, swc_set_* functions are used to pass set the desired
 * configuration into the passed swc_config_t structure.
 *
 */

/******************* Configuration Modification ********************/

/**
 * swc_set_ssid - sets an ESSID in  configuration structure 
 * @sc - pointer to the  configuration structure
 * @ssid - pointer to SSID data
 * @ssid_len - length of SSID data provided, if zero SSID will be reset
 *
 */
int swc_set_ssid(swc_config_t *sc, unsigned char *ssid, int ssid_len);

/**
 * swc_set_key_management - configure key management
 * @sc - pointer to the  configuration structure
 * @key_mgmt - OR'd list of key management types
 * 		Key managements are comprised of SWC_KEY_MGMT_* values
 *
 */
int swc_set_key_management(swc_config_t *sc, int key_mgmt);

/**
 * swc_set_auth_proto - configure authentication protocol support
 * @sc - pointer to the  configuration structure
 * @proto - OR'd list of possible protocols
 * 		Auth protocols are comprised of SWC_PROTO_* values
 *
 */
int swc_set_auth_proto(swc_config_t *sc, int proto);

/**
 * swc_set_auth_alg - configure authentication algorithm for 802.11 
 * @sc - pointer to the  configuration structure
 * @alg - OR'd list of possible algs 
 * 		Auth protocols are comprised of SWC_AUTH_ALG_* values
 * Note: SWC_AUTH_ALG_SHARED is not used
 *
 */
int swc_set_auth_alg(swc_config_t *sc, int alg);

/**
 * swc_set_ciphers - configure encryption cipher support in supplicant
 * @sc - pointer to the  configuration structure
 * @pairwise - OR'd list of acceptable pairwise ciphers
 * @group - OR'd list of acceptable group ciphers
 * 		Both ciphers are comprised of SWC_CIPHER_* values
 *
 */
int swc_set_ciphers(swc_config_t *sc, int pairwise, int group);

/**
 * swc_set_psk - configure PSK to use with WPA-PSK
 * @sc - pointer to the  configuration structure
 * @psk - PSK hash to use
 *
 * Note: swc_set_psk and swc_set_psk_passphrase are mutually exclusive.
 *
 */
int swc_set_psk(swc_config_t *sc, unsigned char *psk);

/**
 * swc_set_psk_passphrase - configure passphrase to use with WPA-PSK
 * @sc - pointer to the  configuration structure
 * @passphrase - Passphrase to generate PSK hash with
 *
 * Note: swc_set_psk and swc_set_psk_passphrase are mutually exclusive. 
 *
 */
int swc_set_psk_passphrase(swc_config_t *sc, char *passphrase);

/**
 * swc_set_eap_method - Configure EAP methods to use
 * @sc - pointer to the  configuration structure
 * @eap_method - EAP method to append to list
 * 		EAP methods are comprised of SWC_EAP_TYPE_* values
 *
 * EAP methods are appended to the list in the order this function is
 * called.
 *
 */
int swc_set_eap_method(swc_config_t *sc, int eap_method);

/**
 * swc_clear_eap_methods - reset all configured EAP methods
 * @sc - pointer to the  configuration structure
 *
 * Resets the EAP methods configured for this instance
 */
int swc_clear_eap_methods(swc_config_t *sc);

/**
 * swc_set_phase2_method - Configure authentication method for phase2
 * @sc - pointer to the  configuration structure
 * @phase2_method - Authentication method to use for phase2
 * 		Phase2 Methods are comprised of SWC_PHASE2_METHOD_* values
 * 	
 */
int swc_set_phase2_method(swc_config_t *sc, int phase2_method);

/**
 * swc_clear_phase2_methods - reset all configured Phase2 methods
 * @sc - pointer to the  configuration structure
 */
int swc_clear_phase2_methods(swc_config_t *sc);

/**
 * swc_set_identity - configure identity/username
 * @sc - pointer to the  configuration structure
 * @identity - identity to configure in supplicant instance
 *
 */
int swc_set_identity(swc_config_t *sc, char *identity);

/**
 * swc_set_password - configure password corresponding to the identity
 * @sc - pointer to the  configuration structure
 * @password- password corresponding to identity
 *
 */
int swc_set_password(swc_config_t *sc, char *password);

/**
 * swc_set_new_password - configure new password for MSCHAPV2
 * @sc - pointer to the  configuration structure
 * @password- password to update
 *
 */
int swc_set_new_password(swc_config_t *sc, char *password);

/**
 * swc_set_anonymous_identity - configure anonymous/outer identity
 * @sc - pointer to the  configuration structure
 * @anonymous_identity- anonymous identity to configure in supplicant instance
 *
 */
int swc_set_anonymous_identity(swc_config_t *sc, char *anonymous_identity);


/**
 * swc_set_tls_ca_cert - TLS CA/Root certificate to use
 * @sc - pointer to the configuration structure
 * @data - pointer to CA certificate to be used
 * @datalen - length of CA certificate provided
 * @binary - boolean indicating whether data is a filename or raw certificate
 *
 * The type of information stored in the location pointed to by data depends
 * on the binary flag. If the binary flag is non-zero, then we assume data
 * points to a raw certificate to be passed to the TLS library, datalen should
 * be the length of this raw data.
 *
 * If binary is zero, we assume the location pointed to by data contains a 
 * '\0' terminated string representing either a filename or a hash blob
 * (e.g. "hash://...") for selecting a certificate of the certificate store.
 * datalen should be the length of the string include the terminating NUL.
 * When using Windows, if data is specified as "any", CA cert matching will
 * be done using any certificate in the certificate store as a possible match.
 */
int swc_set_tls_ca_cert(swc_config_t *sc, unsigned char *data,
		int datalen, int binary);

/**
 * swc_set_tls_ca_cert2 - TLS CA/Root certificate to use for Phase2 EAP-TLS
 * @sc - pointer to the configuration structure
 * @data - pointer to CA certificate to be used
 * @datalen - length of CA certificate provided
 * @binary - boolean indicating whether data is a filename or raw certificate
 *
 * The type of information stored in the location pointed to by data depends
 * on the binary flag. If the binary flag is non-zero, then we assume data
 * points to a raw certificate to be passed to the TLS library, datalen should
 * be the length of this raw data.
 *
 * If binary is zero, we assume the location pointed to by data contains a 
 * '\0' terminated string representing either a filename or a hash blob
 * (e.g. "hash://...") for selecting a certificate of the certificate store.
 * datalen should be the length of the string include the terminating NUL.
 * When using Windows, if data is specified as "any", CA cert matching will
 * be done using any certificate in the certificate store as a possible match.
 */
int swc_set_tls_ca_cert2(swc_config_t *sc, unsigned char *data,
		int datalen, int binary);

/**
 * swc_set_tls_client_cert - client certificate to use
 * @sc - pointer to the configuration structure
 * @data - pointer to certificate to be used
 * @datalen - length of certificate provided
 * @binary - boolean indicating whether data is a filename or raw certificate
 *
 * The type of information stored in the location pointed to by data depends
 * on the binary flag. If the binary flag is non-zero, then we assume data
 * points to a raw certificate to be passed to the TLS library, datalen should
 * be the length of this raw data.
 *
 * If binary is zero, we assume the location pointed to by data contains a 
 * '\0' terminated string representing either a filename or a hash blob
 * (e.g. "hash://...") for selecting a certificate of the certificate store.
 * datalen should be the length of the string include the terminating NUL.
 */
int swc_set_tls_client_cert(swc_config_t *sc, unsigned char *data,
		int datalen, int binary);

/**
 * swc_set_tls_client_cert2 - client certificate to use for phase2 EAP-TLS
 * @sc - pointer to the configuration structure
 * @data - pointer to certificate to be used
 * @datalen - length of certificate provided
 * @binary - boolean indicating whether data is a filename or raw certificate
 *
 * The type of information stored in the location pointed to by data depends
 * on the binary flag. If the binary flag is non-zero, then we assume data
 * points to a raw certificate to be passed to the TLS library, datalen should
 * be the length of this raw data.
 *
 * If binary is zero, we assume the location pointed to by data contains a 
 * '\0' terminated string representing either a filename or a hash blob
 * (e.g. "hash://...") for selecting a certificate of the certificate store.
 * datalen should be the length of the string include the terminating NUL.
 */
int swc_set_tls_client_cert2(swc_config_t *sc, unsigned char *data,
		int datalen, int binary);

/**
 * swc_set_tls_private_key - private key corresponding to client certificate
 * @sc - pointer to the configuration structure
 * @data - pointer to private key to be used
 * @datalen - length of private key provided
 * @binary - boolean indicating whether data is a filename or raw key 
 *
 * The type of information stored in the location pointed to by data depends
 * on the binary flag. If the binary flag is non-zero, then we assume data
 * points to a raw private key to be passed to the TLS library, datalen should
 * be the length of this raw data.
 *
 * If binary is zero, we assume the location pointed to by data contains a 
 * '\0' terminated string representing either a filename or a hash blob
 * (e.g. "hash://...") for selecting a certificate of the certificate store.
 * datalen should be the length of the string include the terminating NUL.
 *
 * NOTE: If you're using a private key concatenated with a client certificate,
 * then you should not use swc_set_client_cert*, but instead specify the chain
 * to this function only.
 */
int swc_set_tls_private_key(swc_config_t *sc, unsigned char *data,
		int datalen, int binary);

/**
 * swc_set_tls_private_key2 - private key for phase2 EAP-TLS
 * @sc - pointer to the configuration structure
 * @data - pointer to private key to be used
 * @datalen - length of private key provided
 * @binary - boolean indicating whether data is a filename or raw key 
 *
 * The type of information stored in the location pointed to by data depends
 * on the binary flag. If the binary flag is non-zero, then we assume data
 * points to a raw private key to be passed to the TLS library, datalen should
 * be the length of this raw data.
 *
 * If binary is zero, we assume the location pointed to by data contains a 
 * '\0' terminated string representing either a filename or a hash blob
 * (e.g. "hash://...") for selecting a certificate of the certificate store.
 * datalen should be the length of the string include the terminating NUL.
 *
 * NOTE: If you're using a private key concatenated with a client certificate,
 * then you should not use swc_set_client_cert*, but instead specify the chain
 * to this function only.
 */
int swc_set_tls_private_key2(swc_config_t *sc, unsigned char *data,
		int datalen, int binary);

/**
 * swc_set_tls_private_key_passwd - private key passphase
 * @sc - pointer to the configuration structure
 * @passwd - pointer to NUL terminated string to use as passphase
 */

int swc_set_tls_private_key_passwd(swc_config_t *sc, char *passwd);

/**
 * swc_set_tls_private_key_passwd2 - private key passphase for phase2 EAP-TLS
 * @sc - pointer to the configuration structure
 * @passwd - pointer to NUL terminated string to use as passphase
 */

int swc_set_tls_private_key_passwd2(swc_config_t *sc, char *passwd);

/**
 * swc_eap_sm_set_callbacks - set EAP state machine callbacks
 * @sc - pointer to the  configuration structure
 * @eap_cb_get_bool - callback to handle getting boolean EAP SM variables
 * @eap_cb_set_bool - callback to handle setting boolean EAP SM variables
 * @eap_cb_get_int - callback to handle getting integer EAP SM variables
 * @eap_cb_set_int - callback to handle setting integer EAP SM variables
 * @eap_cb_ctx - callback context provided to all of these functions
 */
int swc_eap_sm_set_callbacks(swc_config_t *sc,
	       	void *eap_cb_get_bool, void *eap_cb_set_bool,
		void *eap_cb_get_int, void *eap_cb_set_int,
		void *eap_cb_get_eap_req_data,
		void *eap_cb_ctx);

/**
 * swc_eap_sm_init - initialize EAP state machine
 * @sc - pointer to the  configuration structure
 *
 * This function is responsible for setting up the provided configuration and
 * allocating a new EAP state machine context. It should be called after all
 * other desired configuration is set up.
 */
int swc_eap_sm_init(swc_config_t *sc);

/**
 * swc_eap_sm_run - Run all pending EAP operations
 * @sc - pointer to the  configuration structure
 *
 * This function should be called whenever an EAP request is received and
 * ready to be processed by the state machine. After it is done executing,
 * a response or key can be read.
 */
int swc_eap_sm_run(swc_config_t *sc);

/**
 * swc_eap_sm_get_response - Get the response generated by the EAP SM
 * @sc - pointer to the  configuration structure
 * @data - pointer to buffer in which response should be saved
 * @datalen - pointer to size of initial buffer. outputs response length
 *
 * Returns: SWC_STATUS_NO_DATA if no response is available
 *
 * This function should be called whenever an EAP request has generated a
 * response (e.g. eapResp flag set by EAP SM).
 */
int swc_eap_sm_get_response(swc_config_t *sc, u8 *data, size_t *datalen);

/**
 * swc_eap_sm_get_key - Get the MSK generated by the EAP SM
 * @sc - pointer to the  configuration structure
 * @data - pointer to buffer in which MSK should be saved
 * @datalen - pointer to size of initial buffer. outputs MSK length
 *
 * Returns: SWC_STATUS_NO_DATA if no key is available
 *
 * This function should be called whenever an EAP request has generated a
 * success (e.g. eapSuccess flag set by EAP SM).
 */
int swc_eap_sm_get_key(swc_config_t *sc, u8 *data, size_t *datalen);


/**
 * swc_set_ctrl_iface_callback - control interface callback for async events
 * @sc - pointer to the  configuration structure
 * @ctrl_iface_cb - pointer to callback responsible for handling async events
 * @ctrl_iface_cb_ctx - pointer to callback's context
 *
 * This callback is called whenever the supplicant generates an event or
 * needs to request a credential to be configured.
 */
int swc_set_ctrl_iface_callback(swc_config_t *sc, void *ctrl_iface_cb,
				void *ctrl_iface_cb_ctx);

/**
 * swc_set_cred_export_callback - credential export callback
 * @sc - pointer to the  configuration structure
 * @cred_export_cb - pointer to callback for handling credential storage 
 * @cred_export_cb_ctx - pointer to context for callback 
 *
 * This callback is called whenever the supplicant has a credential event to
 * request the application to save
 */
int swc_set_cred_export_callback(swc_config_t *sc, void *cred_export_cb,
				void *cred_export_cb_ctx);


/**
 * swc_set_sim_pseudonym - Pseudonym for EAP-SIM
 * @sc - pointer to the  configuration structure
 * @pseudonym - Pseudonym to send to server
 */
int swc_set_sim_pseudonym(swc_config_t *sc, char *pseudonym);

/**
 * swc_set_sim_reader_name - Name of reader to use for EAP-SIM
 * @sc - pointer to the  configuration structure
 * @reader - Name of reader as returned by SCardListReaders
 *
 * If no reader is specified the first reader found will be used
 */
int swc_set_sim_reader_name(swc_config_t *sc, char *reader);

/**
 * swc_set_sim_pin - PIN for EAP-SIM
 * @sc - pointer to the  configuration structure
 * @pin - PIN
 *
 */
int swc_set_sim_pin(swc_config_t *sc, char *pin);

/**
 * swc_set_tls_max_size - Maximum size of a TLS packet.
 * @sc - pointer to the  configuration structure
 * @len - length in bytes
 *
 */
int swc_set_tls_max_size(swc_config_t *sc, int len);

/**
 * swc_set_driver_event - Indicate a driver event to the supplicant
 * @sc - pointer to the  configuration structure
 * @ev - event that occurred
 * @data - data, if any, associated with the event
 * @len - length of any data supplied
 *
 */
int swc_set_driver_event(swc_config_t *sc, swc_driver_event_t ev, 
		u8 *data, size_t len);

/**
 * swc_set_driver_l2 - Specify which L2 function supplicant should use for tx/rx
 * @sc - pointer to the  configuration structure
 * @l2func - Function to call when supplicant needs to rx/tx
 * @l2func_ctx - Context parameter supplicant should pass to l2func
 *
 */

int swc_set_driver_l2(swc_config_t *sc, swc_l2_cb l2func, void *l2func_ctx);

/**
 * swc_set_driver_oid - Specify which OID function supplicant should use NDIS
 * @sc - pointer to the  configuration structure
 * @oidfunc - Function to call when supplicant needs to set/get OIDs
 * @oidfunc_ctx - Context parameter supplicant should pass to oidfunc
 *
 */

int swc_set_driver_oid(swc_config_t *sc, swc_oid_cb oidfunc, void *oidfunc_ctx);

/**
 * swc_set_srvcert_cb - Specify which callback to call checking TLS certs
 * @sc - pointer to the  configuration structure
 * @srvcrt_cb - Function to call when supplicant has certificate
 * @srvcrt_cb_ctx - Context parameter supplicant should pass to srvcrt_cb
 *
 * void (*srvcrt_cb)(void *ctx, void *cert, int certlen);
 *
 * All certificates are X509 certs
 *
 */
int swc_set_srvcrt_cb(swc_config_t *sc, void *srvcrt_cb, void *srvcrt_cb_ctx);


/**
 * swc_set_nai - NAI for use with EAP-PSK
 * @sc - pointer to the  configuration structure
 * @nai - pointer to NAI used for EAP-PSK network
 * @nai_len - length of NAI specified
 *
 */
int swc_set_nai(swc_config_t *sc, unsigned char *nai, int nai_len);

/**
 * swc_set_eappsk - Key for use with EAP-PSK
 * @sc - pointer to the  configuration structure
 * @psk - pointer to PSK, must be 16 bytes
 *
 */
int swc_set_eappsk(swc_config_t *sc, unsigned char *psk);

/**
 * swc_set_fast_provisioning - Set the EAP-FAST provisioning mode
 * @sc - pointer to the  configuration structure
 * @prov_mode - Provisioining mode.
 * 		SWC_FAST_PROV_ANON = anonymous allowed only,
 *		SWC_FAST_PROV_AUTH = authenticated allowed only,
 *		SWC_FAST_PROV_ANY = both allowed
 *
 */
int swc_set_fast_provisioning(swc_config_t *sc, int prov_mode);

/**
 * swc_set_fast_pac_file - Set a PAC file to use with EAP-FAST
 * @sc - pointer to the  configuration structure
 * @path - pointer to pathname
 *
 */
int swc_set_fast_pac_file(swc_config_t *sc, char *path);

/**
 * swc_set_fast_pac_file_machine - Set a macine PAC file to use with EAP-FAST
 * @sc - pointer to the  configuration structure
 * @path - pointer to pathname
 *
 */
int swc_set_fast_pac_file_machine(swc_config_t *sc, char *path);

/**
 * swc_set_fast_pac - Set a PAC based on data exported to the application
 * @sc - pointer to the  configuration structure
 * @pac - pointer to PAC exported by credential export callback
 *
 */
int swc_set_fast_pac(swc_config_t *sc, swc_pac_t *pac);

/**
 * swc_set_fast_nac_module_dir - Set the NAC module directory for CCX/NAC
 * @sc - pointer to the  configuration structure
 * @path - pointer to pathname
 *
 */
int swc_set_nac_module_dir(swc_config_t *sc, char *path);

/**
 * swc_set_fast_nac_lib - Set the NAC library module pathname for CCX/NAC
 * @sc - pointer to the  configuration structure
 * @path - pointer to pathname
 *
 */
int swc_set_nac_lib(swc_config_t *sc, char *path);

#ifdef CONFIG_NATIVE_WINDOWS
/**
 * swc_set_impersonation_handle - Set the handle for impersonating a user
 * @sc - pointer to the  configuration structure
 * @path - pointer to pathname
 *
 */
int swc_set_impersonation_handle(swc_config_t *sc, HANDLE h);

/**
 * swc_scard_init - Initialize the smartcard monitoring thread
 * @sc - pointer to the  configuration structure
 * 
 * Note: swc_scard_set_event_cb should be called prior to this function to 
 *       prevent missing any initial insertion events
 */
int swc_scard_init(swc_config_t *sc);

/**
 * swc_scard_deinit - Deinitialize the smartcard monitoring thread
 * @sc - pointer to the configuration structure
 *
 */
int swc_scard_deinit(swc_config_t *sc);

/**
 * swc_scard_set_event_cb - Specify which callback to use for smartcard events
 * @sc - pointer to the configuration structure
 * @scardfunc - pointer to the callback function
 * @scardfunc_ctx - pointer to the context to be provided to the callback
 *
 */
int swc_scard_set_event_cb(swc_config_t *sc, swc_scard_event_cb scardfunc,
			void *scardfunc_ctx);
#endif

/**
 * swc_set_ap_scan_mode - Set the supplicant scan mode
 * @sc - pointer to the  configuration structure
 * @scan_mode - Scan mode setting (0, 1, or 2)
 *
 */
int swc_set_ap_scan_mode(swc_config_t *sc, int scan_mode);

/**
 * swc_set_peerkey_mode - Set the PeerKey operation mode
 * @sc - pointer to the configuration structure
 * @enabled - if specified as a non-zero value, enable PeerKey, otherwise 
 *            PeerKey is disabled
 *
 */
int swc_set_peerkey_mode(swc_config_t *sc, int enabled);

/**
 * swc_set_ieee80211w_mode - Set the IEEE 802.11w operation mode
 * @sc - pointer to the configuration structure
 * @enabled - if specified as a non-zero value, enable IEEE 802.11w, otherwise 
 *            IEEE 802.11w is disabled
 *
 */
int swc_set_ieee80211w_mode(swc_config_t *sc, int enabled);


/**
 * swc_start_authentication - Start authentication for a WiFi supplicant
 * @sc - pointer to the  configuration structure
 *
 */
int swc_start_authentication(swc_config_t *sc);

/**
 * swc_stop_authentication - Stop authentication thread for a WiFi supplicant
 * @sc - pointer to the configuration structure
 *
 */
int swc_stop_authentication(swc_config_t *sc);

/******************* High-level Configuration Manipulation ********************/

/**
 * swc_config_reset - reset a configuration structure for an interface
 * @sc - Pointer to configuration structure for interface to reset
 *
 * This function will bring the authentication context structure back to the
 * same state it was in upon return from swc_config_alloc.
 */

int swc_config_reset(swc_config_t *sc);

/**
 * swc_config_free - free memory associated with a configuration structure
 * @sc - Pointer to configuration structure to deallocate
 */

void swc_config_free(swc_config_t *sc);

/**
 * swc_config_alloc - allocate new swc_config_t structure
 * @interface_name - Name of interface structure is for
 * @interface_type - Type of interface structure is for
 *
 * Returns: Pointer to swc_config_t on success, NULL on failure
 */

swc_config_t *swc_config_alloc(char *interface_name, int interface_type);

#endif /* CONFIG_API_H */
