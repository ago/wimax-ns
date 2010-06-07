/*
 * WFA Simple Config: EAP routines includes
 * Copyright 2006 Devicescape Software, Inc.
 * Erik Anvik <erik@devicescape.com>
 * All Rights Reserved.
 */
#ifndef _WSC_EAP_H_
#define _WSC_EAP_H_

#include "wsc_types.h"
#include "wsc_common.h"

/* standard 802.1X EAP codes */
enum {
	WSC_EAP_CODE_REQUEST = 0x01, /* 0x01 - Registrar/AP  -> Enrollee */
	WSC_EAP_CODE_RESPONSE,       /* 0x02 - Registrar/AP <-  Enrollee */
	WSC_EAP_CODE_SUCCESS,        /* 0x03 - Registrar/AP <-> Enrollee */
	WSC_EAP_CODE_FAILURE         /* 0x04 - Registrar/AP <-> Enrollee */
};

enum {
	WSC_EAP_TYPE_NONE = 0,
	WSC_EAP_TYPE_IDENTITY,
	WSC_EAP_TYPE_NOTIFICATION,
	WSC_EAP_TYPE_NAK,
	WSC_EAP_TYPE_SIMPLE_CONFIG = 254
};

/* WSC EAP identities */
#define WSC_REGISTRAR_ID "WFA-SimpleConfig-Registrar-1-0" 
#define WSC_ENROLLEE_ID  "WFA-SimpleConfig-Enrollee-1-0"

/**
 * wsc_eap_hdr - EAP header 
 * @code: code 
 * @identifier: packet identifier
 * @length: total length of packet including header
 * @type: authentication type
 */
struct wsc_eap_hdr {
	u8  code;
	u8  identifier;
	u16 length;
	u8  type;
} _WSC_STRUCT_PACKED_;

/**
 * wsc_eap_msg_hdr - WSC vendor specific message header 
 * @vid: vendor specific identifier 
 * @vtype: vendor specific EAP type
 * @opcode: simple config op-code
 * @flags: simple config message flags
 * @msglen: message length not including header
 */
struct wsc_eap_msg_hdr {
	u8  vid[3]; 
	u32 vtype;   
	u8  opcode;  
	u8  flags;   
} _WSC_STRUCT_PACKED_;

/**
 * wsc_eap_tlv_hdr - EAP TLV (type length value) header 
 * @attribute: type identifier for the attribute 
 * @length: length in bytes of the attributes data field
 */
struct wsc_eap_tlv_hdr {
	u16 attribute;
	u16 length;
} _WSC_STRUCT_PACKED_;

#define HDR_SZ (sizeof(struct wsc_eap_msg_hdr) + sizeof(struct wsc_eap_hdr))

/* Fragmentation and Reassembly */
#define WSC_MSG_MORE_FRAGMENTS_BIT  BIT(0)
#define WSC_MSG_LENGTH_INCLUDED_BIT BIT(1)

#define WSC_MSG_MORE_FRAGS(flag) \
((flags & WSC_MSG_MORE_FRAGMENTS_BIT) ? TRUE : FALSE)

#define WSC_MSG_LENGTH_INCLUDED(flag) \
((flags & WSC_MSG_LENGTH_INCLUDED_BIT) ? TRUE : FALSE)

void wsc_eap_create_request_id(struct wsc_eap_ctx*, struct wsc_buffer_ctx*);
void wsc_eap_create_request(struct wsc_eap_ctx*, struct wsc_buffer_ctx*);
void wsc_eap_create_response(struct wsc_eap_ctx*, struct wsc_buffer_ctx*);
void wsc_eap_create_failure(struct wsc_eap_ctx*, struct wsc_buffer_ctx*);
void wsc_eap_create_response_id(struct wsc_eap_ctx*, struct wsc_buffer_ctx*);
int  wsc_eap_validate_userid(char *);
void wsc_eap_cache_recv_id(struct wsc_eap_ctx*, u8);

#endif /* _WSC_EAP_H_ */
