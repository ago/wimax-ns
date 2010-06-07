#ifndef _EAP_HOST_H_
#define _EAP_HOST_H_


/* See MS docs for EAP_ATTRIBUTE_TYPE "eatVendorSpecific" */
#define EAP_HOST_EAP_VENDOR_MS	311
#define EAP_HOST_MPPE_SEND_KEY	16
#define EAP_HOST_MPPE_RECV_KEY	17
#define EAP_HOST_MPPE_ATTR_LEN	52
#define EAP_HOST_MPPE_KEY_LEN	32
#define EAP_HOST_MPPE_SALT	0 

#pragma pack(push, 1)
struct eh_mppe_key_data {
	unsigned int vendor;
	unsigned char type;
	unsigned char attrlen;
	unsigned short salt;
	unsigned char keylen;
	unsigned char keydata[32];
	unsigned char pad[15];
};
#pragma pack(pop)

struct eh_conndata {
	unsigned char identity[256];
	unsigned char anon_identity[256];
	unsigned char password[256];
	int eap_type;
	int phase2_type;
	int fast_provisionmode;
	char tls_cacert[128];
	char tls_clientcert[128];
	char tls_privatekey[128];
	char tls_privatekeypass[128];
	char fast_userpac[128];
	char fast_machpac[128];
	char sim_readername[128];
	char sim_pin[32];
	char sim_imsi[128];
};

struct eh_privdata {
	swc_config_t *sc;
	struct eap_variables *e;
	unsigned char *resp_pkt;
	unsigned int resp_pkt_len;
};



static void debug_msg(const char *fmt, ...);

#endif
