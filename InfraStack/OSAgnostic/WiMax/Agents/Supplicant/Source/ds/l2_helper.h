#ifndef _L2_HELPER_H_
#define _L2_HELPER_H_

#define L2_HELPER_OID_PORT 9970
#define L2_HELPER_PKT_PORT 9971

#define L2_HELPER_MAX_OID_DATA  67000
#define L2_HELPER_MAX_PKT_DATA	4096

#define L2_HELPER_MSG_OID_GET 1
#define L2_HELPER_MSG_OID_SET 2
#define L2_HELPER_MSG_PKT 3

#define L2_HELPER_RETRIES 5
#define L2_HDRLEN sizeof(struct l2_helper_msg_hdr)

#pragma pack(push, 1)
struct l2_helper_msg_oid {
	u32 oid;
	u32 oid_data_len;
	unsigned char oid_data[1];
};

struct l2_helper_msg_pkt {
	unsigned int pkt_data_len;
	unsigned char pkt_data[1];
};


struct l2_helper_msg_hdr {
	u32 type;
	int status;
	u32 len;
};
#pragma pack(pop)

struct l2_helper_msg {
	struct l2_helper_msg_hdr hdr;
	union {
		struct l2_helper_msg_oid oid;
		struct l2_helper_msg_pkt pkt;
	} u;
};

#endif /* ! _L2_HELPER_H_ */
