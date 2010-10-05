/*
 * WPA Supplicant - driver interaction with Broadcom wl.o driver
 * Copyright (c) 2004-2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef DRIVER_BROADCOM_H
#define DRIVER_BROADCOM_H

typedef u32 uint32;
#ifdef __vxworks
typedef u32 uint;
#endif
typedef u16 uint16;
typedef u8 uint8;
typedef u8 uchar;
typedef s32 int32;
typedef s16 int16;
typedef s8 int8;
typedef	unsigned char	bool;			/* consistent w/BOOL */

/* require default structure packing */
//#if !defined(__GNUC__)
//#pragma pack(push,8)
//#endif

/* enable structure packing */
#if defined(__GNUC__)
#define	PACKED	__attribute__((packed))
#else
#pragma pack(push,1)
#define	PACKED
#endif

#define WPA2_PMKID_LEN	16

/*
 * The number of bytes in an ethernet (MAC) address.
 */
#define	ETHER_ADDR_LEN		6

/*
 * The number of bytes in the type field.
 */
#define	ETHER_TYPE_LEN		2

/*
 * The length of the combined header.
 */
#define	ETHER_HDR_LEN		(ETHER_ADDR_LEN*2+ETHER_TYPE_LEN)

#define	ETHER_TYPE_BRCM		0x886c		/* Broadcom Corp. */

/*
 * Structure of a 10Mb/s Ethernet header.
 */
struct	ether_header {
	uint8	ether_dhost[ETHER_ADDR_LEN];
	uint8	ether_shost[ETHER_ADDR_LEN];
	uint16	ether_type;
} PACKED;

/*
 * Structure of a 48-bit Ethernet address.
 */
struct	ether_addr {
	uint8 octet[ETHER_ADDR_LEN];
} PACKED;

#define DOT11_LLC_SNAP_HDR_LEN	8
#define DOT11_OUI_LEN			3
struct dot11_llc_snap_header {
	uint8	dsap;				/* always 0xAA */
	uint8	ssap;				/* always 0xAA */
	uint8	ctl;				/* always 0x03 */
	uint8	oui[DOT11_OUI_LEN];		/* RFC1042: 0x00 0x00 0x00
						   Bridge-Tunnel: 0x00 0x00 0xF8 */
	uint16	type;				/* ethertype */
} PACKED;

#define WPA_OUI			"\x00\x50\xF2"


struct dot11_assoc_req {
	uint16			capability;	/* capability information */
	uint16			listen;		/* listen interval */
} PACKED;

struct dot11_assoc_resp {
	uint16			capability;	/* capability information */
	uint16			status;		/* status code */
	uint16			aid;		/* association ID */
} PACKED;

#define DOT11_MAX_KEY_SIZE	32	/* max size of any key */


/* These fields are held in network order */
typedef  struct bcmeth_hdr
{
	uint16	subtype; /* Vendor specific..32769*/
	uint16	length; 
	uint8	version; /* Version is 0*/
	uint8	oui[3]; /* Broadcom OUI*/
	/* user specific Data */
	uint16	usr_subtype;
} PACKED bcmeth_hdr_t;

#define BCM_MSG_IFNAME_MAX		16

/* used by driver msgs */
typedef struct bcm_msg {
	struct ether_header eth;
	bcmeth_hdr_t bcm_hdr; 
	/* user specific Data*/
	uint8  version;
	uint8  msg_type;
	char ifname[BCM_MSG_IFNAME_MAX]; /* name of the packet incoming interface*/
	/* data portion follows */
} PACKED bcm_msg_t;

#define BCM_MSG_VERSION	1 
#define BCM_MSG_LEN	(sizeof(bcm_msg_t) - sizeof(bcmeth_hdr_t) - sizeof(struct ether_header))

/* msg_type field values for the bcm_msg_t driver messages */
#define WLC_ASSOC_MSG		1
#define WLC_DISASSOC_MSG	2
#define WLC_PTK_MIC_MSG		3
#define WLC_GTK_MIC_MSG		4
#define WLC_ASSOC_FAIL_MSG	5
#define WLC_AUTH_FAIL_MSG	6
#define WLC_PMKID_CACHE_MSG	7
#define WLC_EVENT_MSG		8

/* theses fields are stored in network order */
typedef struct bcm_event_msg 
{
	uint16	version;
	uint32	msg;			/* Message (see below) */
	uint32	status;			/* Status code (see below) */
	uint32	reason;			/* Reason code (if applicable) */
	uint32	auth_type;		/* WLC_E_AUTH */
	uint32	datalen;		/* data buf */
	uint16	flags;			/* see flags below */
	uint8	addr[ETHER_ADDR_LEN];	/* Station address (if applicable) */
} PACKED bcm_event_msg_t;

#define BCM_EVENT_MSG_VERSION	1

/* flags */
#define WLC_EVENT_MSG_LINK		0x01
#define WLC_EVENT_MSG_FLUSHTXQ	0x02
#define WLC_EVENT_MSG_GROUP		0x04


#define	WL_BSS_INFO_VERSION		107	/* current version of wl_bss_info struct */

typedef struct wl_bss_info {
	uint32		version;	/* version field */
	uint32		length;		/* byte length of data in this record, starting at version and including IEs */
	struct ether_addr BSSID;
	uint16		beacon_period;	/* units are Kusec */
	uint16		capability;	/* Capability information */
	uint8		SSID_len;
	uint8		SSID[32];
	struct {
		uint	count;		/* # rates in this set */
		uint8	rates[16];	/* rates in 500kbps units w/hi bit set if basic */
	} rateset;			/* supported rates */
	uint8		channel;	/* Channel no. */
	uint16		atim_window;	/* units are Kusec */
	uint8		dtim_period;	/* DTIM period */
	int16		RSSI;		/* receive signal strength (in dBm) */
	int8		phy_noise;	/* noise (in dBm) */
	uint32		ie_length;	/* byte length of Information Elements */
	/* variable length Information Elements */
} wl_bss_info_t;

typedef struct wlc_ssid {
	uint32		SSID_len;
	uchar		SSID[32];
} wlc_ssid_t;

typedef struct wl_scan_results {
	uint32 buflen;
	uint32 version;
	uint32 count;
	wl_bss_info_t bss_info[1];
} wl_scan_results_t;


typedef struct wlc_assoc_info {
	uint32		req_len;
	uint32		resp_len;
	uint32		flags;
	struct dot11_assoc_req req;
	struct ether_addr reassoc_bssid; /* used in reassoc's */
	struct dot11_assoc_resp resp;
} wl_assoc_info_t;
/* flags */
#define WLC_ASSOC_REQ_IS_REASSOC 0x01 /* assoc req was actually a reassoc */


/* Event messages */
#define WLC_E_SET_SSID		1
#define WLC_E_JOIN		2
#define WLC_E_START		3
#define WLC_E_AUTH		4
#define WLC_E_AUTH_IND		5
#define WLC_E_DEAUTH		6
#define WLC_E_DEAUTH_IND	7
#define WLC_E_ASSOC		8
#define WLC_E_ASSOC_IND		9
#define WLC_E_REASSOC		10
#define WLC_E_REASSOC_IND	11
#define WLC_E_DISASSOC		12
#define WLC_E_DISASSOC_IND	13
#define WLC_E_QUIET_START	14	/* 802.11h Quiet period started */
#define WLC_E_QUIET_END		15	/* 802.11h Quiet period ended */
#define WLC_E_GOT_BEACONS	16
#define WLC_E_LINK		17	/* Link indication */
#define WLC_E_MIC_ERROR		18	/* TKIP MIC error occurred */
#define WLC_E_NDIS_LINK		19	/* NDIS style link indication */
#define WLC_E_ROAM		20
#define WLC_E_TXFAIL		21	/* dot11FailedCount (txfail) */
#define WLC_E_PMKID_CACHE	22
#define WLC_E_LAST		23

/* Event status codes */
#define WLC_E_STATUS_SUCCESS		0
#define WLC_E_STATUS_FAIL		1
#define WLC_E_STATUS_TIMEOUT		2
#define WLC_E_STATUS_NO_NETWORKS	3
#define WLC_E_STATUS_ABORT		4

/* roam reason codes */
#define WLC_E_REASON_LOW_RSSI			1
#define WLC_E_REASON_DEAUTH				2
#define WLC_E_REASON_DISASSOC			3
#define WLC_E_REASON_BCNS_LOST			4
#define WLC_E_REASON_FAST_ROAM_FAILED	5


/* Enumerate crypto algorithms */
#define	CRYPTO_ALGO_OFF			0
#define	CRYPTO_ALGO_WEP1		1
#define	CRYPTO_ALGO_TKIP		2
#define	CRYPTO_ALGO_WEP128		3
#define CRYPTO_ALGO_AES_CCM		4
#define CRYPTO_ALGO_AES_OCB_MSDU	5
#define CRYPTO_ALGO_AES_OCB_MPDU	6
#ifndef BCMCCX
#define CRYPTO_ALGO_NALG		7
#else
#define CRYPTO_ALGO_CKIP		7
#define CRYPTO_ALGO_CKIP_MMH		8
#define CRYPTO_ALGO_WEP_MMH		9
#define CRYPTO_ALGO_NALG		10
#endif

#define WL_SOFT_KEY	(1 << 0)	/* Indicates this key is using soft encrypt */
#define WL_PRIMARY_KEY	(1 << 1)	/* Indicates this key is the primary (ie tx) key */
#ifdef BCMCCX
#define WL_CKIP_KP	(1 << 4)	/* CMIC */
#define WL_CKIP_MMH	(1 << 5)	/* CKIP */
#else
#define WL_KF_RES_4	(1 << 4)	/* Reserved for backward compat */
#define WL_KF_RES_5	(1 << 5)	/* Reserved for backward compat */
#endif


typedef struct wl_wsec_key {
	uint32		index;		/* key index */
	uint32		len;		/* key length */
	uint8		data[DOT11_MAX_KEY_SIZE];	/* key data */
	uint32		pad_1[18];
	uint32		algo;		/* CRYPTO_ALGO_AES_CCM, CRYPTO_ALGO_WEP128, etc */
	uint32		flags;		/* misc flags */
	uint32		pad_2[2];
	int		pad_3;
	int		iv_initialized;	/* has IV been initialized already? */
	int		pad_4;
	/* Rx IV */
	struct {
		uint32	hi;		/* upper 32 bits of IV */
		uint16	lo;		/* lower 16 bits of IV */
	} rxiv;
	uint32		pad_5[2];
	struct ether_addr ea;		/* per station */
} wl_wsec_key_t;


/* wireless security bitvec */
#define WEP_ENABLED		1
#define TKIP_ENABLED		2
#define AES_ENABLED		4
#define WSEC_SWFLAG		8
#ifdef BCMCCX
#define CKIP_KP_ENABLED		16
#define CKIP_MIC_ENABLED	32
#endif /* BCMCCX */

/* WPA authentication mode bitvec */
#define WPA_AUTH_DISABLED	0x0000	/* Legacy (i.e., non-WPA) */
#define WPA_AUTH_NONE		0x0001	/* none (IBSS) */
#define WPA_AUTH_UNSPECIFIED	0x0002	/* over 802.1x */
#define WPA_AUTH_PSK		0x0004	/* Pre-shared key */
#ifdef BCMCCX
#define WPA_AUTH_CCKM		0x0008	/* CCKM */
#define WPA2_AUTH_CCKM		0x0010	/* CCKM2 */
#endif	/* BCMCCX */
/*#define WPA_AUTH_8021X 0x0020*/	/* 802.1x, reserved */
#define	MAXPMKID		16	
#define WPA2_AUTH_UNSPECIFIED	0x0040	/* over 802.1x */
#define WPA2_AUTH_PSK		0x0080	/* Pre-shared key */
typedef struct _pmkid
{
	struct ether_addr	BSSID;
	uint8			PMKID[WPA2_PMKID_LEN];
} pmkid_t;

typedef struct _pmkid_list
{
	uint32	npmkid;
	pmkid_t	pmkid[1];
} pmkid_list_t;

typedef struct _pmkid_cand {
	struct ether_addr	BSSID;
	uint8			preauth;
} PACKED pmkid_cand_t;

typedef struct _pmkid_cand_list {
	uint32	npmkid_cand;
	pmkid_cand_t	pmkid_cand[1];
} PACKED pmkid_cand_list_t;

/* WLC_SET_PMKID (Devicescape addition for the "old driver") */
#define WPA2_PMKID_CMD_ADD 1
#define WPA2_PMKID_CMD_FLUSH 2
typedef struct wl_pmkid_data {
	uint32		cmd; /* WPA2_PMKID_CMD_* */
	uint8		pmkid[16];
	uint8		bssid[6];
} wlc_pmkid_data_t;


#define	WLC_IOCTL_MAXLEN	8192


/* Linux network driver ioctl encoding */
typedef struct wl_ioctl {
	uint cmd;	/* common ioctl definition */
	void *buf;	/* pointer to user buffer */
	uint len;	/* length of user buffer */
	bool set;	/* get or set request (optional) */
	uint used;	/* bytes read or written (optional) */
	uint needed;	/* bytes needed (optional) */
} wl_ioctl_t;


#define WLC_GET_MAGIC				0
#define WLC_DUMP				6
#define WLC_SET_INFRA				20
#define WLC_SET_AUTH				22
#define WLC_GET_BSSID				23
#define WLC_GET_SSID				25
#define WLC_SET_SSID				26
#define WLC_SET_WEP				43
#define WLC_SET_KEY				45
#define WLC_SCAN				50
#define WLC_SCAN_RESULTS			51
#define WLC_DISASSOC				52
#define WLC_SET_AP				118
#define WLC_GET_WSEC				133
#define WLC_SET_WSEC				134
#define WLC_GET_WPA_AUTH			164
#define WLC_SET_WPA_AUTH			165
#define WLC_SCB_DEAUTHENTICATE_FOR_REASON	201
#define WLC_GET_VAR				262	/* get value of named variable */
#define WLC_SET_VAR				263	/* set named variable to value */
/* Devicescape addition for older driver: */
#define WLC_SET_PMKID				273



/* old event mechanism */

/*
 * definitions for driver messages passed from WL to NAS.
 */
/* Use this to recognize wpa and 802.1x driver messages. */
static const uint8 wl_wpa_snap_template[] =
	{ 0xaa, 0xaa, 0x03, 0x00, 0x90, 0x4c };

#define WL_WPA_MSG_IFNAME_MAX	16

/* WPA driver message */
typedef struct wl_wpa_header {
	struct ether_header eth;
	struct dot11_llc_snap_header snap;
	uint8 version;
	uint8 type;
	/* version 2 additions */
	char ifname[WL_WPA_MSG_IFNAME_MAX];
	/* version specific data */
	/* uint8 data[1]; */
} wl_wpa_header_t;

#define WL_WPA_HEADER_LEN	(ETHER_HDR_LEN + DOT11_LLC_SNAP_HDR_LEN + 2 + WL_WPA_MSG_IFNAME_MAX)

/* WPA driver message ethertype - private between wlc and nas */
#define WL_WPA_ETHER_TYPE	0x9999

/* WPA driver message current version */
#define WL_WPA_MSG_VERSION	2

/* Type field values for the 802.2 driver messages for WPA. */
#define WLC_ASSOC_MSG		1
#define WLC_DISASSOC_MSG	2
#define WLC_PTK_MIC_MSG		3
#define WLC_GTK_MIC_MSG		4


typedef struct {
	uint32 val;
	struct ether_addr ea;
	uint16 res;
} wlc_deauth_t;


#if !defined(__GNUC__)
#pragma pack(pop)
#endif

#endif /* DRIVER_BROADCOM_H */
