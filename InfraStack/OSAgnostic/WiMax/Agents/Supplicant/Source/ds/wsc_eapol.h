#ifndef _WSC_EAPOL_H_
#define _WSC_EAPOL_H_

#include "wsc_types.h"
#include "wsc_common.h"

#ifndef WSC_ETH_EAPOL
#define WSC_ETH_EAPOL 0x888E
#endif

enum {
	WSC_EAPOL_EAP_PKT = 0, /* EAP Packet */
	WSC_EAPOL_START,       /* EAPOL Start */
	WSC_EAPOL_LOGOFF,      /* EAPOL Logoff */
	WSC_EAPOL_KEY,         /* EAPOL Key */
	WSC_EAPOL_ASF_ALERT    /* EAPOL Encapsulated ASF Alert */
};

/**
 * wsc_eapol_hdr - simple config EAPOL packet header 
 * @version: EAPOL version
 * @type: EAPOL message type
 * @len: EAPOL packet length w/o EAPOL header length
 */
struct wsc_eapol_hdr
{
	char version;
	char type;
	u16  len; 
} _WSC_STRUCT_PACKED_;
#define WSC_EAPOL_HDR_SZ sizeof(struct wsc_eapol_hdr)

/**
 * wsc_enet_hdr - simple config ETHERNET header 
 * @dstaddr: destination MAC address
 * @srcaddr: source MAC address
 * @prot: protocol family
 */
struct wsc_enet_hdr
{
	u8  dstaddr[ETH_ALEN];
	u8  srcaddr[ETH_ALEN];
	u16 prot;
} _WSC_STRUCT_PACKED_;
#define WSC_ENET_HDR_SZ sizeof(struct wsc_enet_hdr)

/**
 * wsc_80211_hdr - simple config 80211 header 
 * @fc: frame control
 * @duration_id: frame duration identifier
 * @addr1: 
 * @addr2: 
 * @addr3: 
 * @seq_ctrl: sequence control
 */
struct wsc_80211_hdr {
	u16 fc;
	u16 duration_id;
	u8  addr1[ETH_ALEN];
	u8  addr2[ETH_ALEN];
	u8  addr3[ETH_ALEN];
	u16 seq_ctrl;
	/* followed by 'u8 addr4[6];' if ToDS and FromDS is set in data frame
	 */
} _WSC_STRUCT_PACKED_;
/* snap header + padding */
#define WSC_80211_HDR_SZ sizeof(struct wsc_80211_hdr) + 8 

/**
 * wsc_eapol_ctx - simple config EAPOL session context object 
 * @ifname: network interface name
 * @ifindex: network interface number
 * @macaddr: network interface MAC address
 * @ipsock: newtork driver socket
 * @l2sock: packet socket
 * @protocol: desired protocol, i.e. EAPOL
 * @cookie: argument for callback
 * @start: EAPOL start callback
 * @handler: EAPOL packet handler callback
 * @mem: packet memory
 */
struct wsc_eapol_ctx {
	char ifname[IFNAMESIZ + 1]; 
	int  ifindex;
	char macaddr[ETH_ALEN];
	int  ipsock;
	int  l2sock;
	u16  protocol; 
	void *cookie;
	int (*start)();
	int (*handler)();
	struct wsc_buffer_ctx *mem;
};

void *wsc_eapol_init(char *);
void  wsc_eapol_deinit(void *);
int   wsc_eapol_receive(struct wsc_eapol_ctx*, u8*, u8*, int);
int   wsc_eapol_send_start(struct wsc_eapol_ctx*, u8*);

#endif /* _WSC_EAPOL_H_ */
