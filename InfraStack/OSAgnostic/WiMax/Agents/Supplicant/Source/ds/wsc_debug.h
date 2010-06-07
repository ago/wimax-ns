/*
 * WFA Simple Config: Debug library includes
 * Copyright 2006 Devicescape Software, Inc.
 * Erik Anvik <erik@devicescape.com>
 * All Rights Reserved.
 */
#ifndef _WSC_DEBUG_H_
#define _WSC_DEBUG_H_

#include "wsc_types.h"
#include "wsc_attributes.h"
#include "wsc_eap.h"
#include "wsc_common.h"

enum {
	WSC_DEBUG_FATAL = 0,
	WSC_DEBUG_ERROR,
	WSC_DEBUG_WARN,
	WSC_DEBUG_INFO,
	WSC_DEBUG_FLOOD
};

void wsc_debug_print_tlv(char*, int, char*);
void wsc_debug_show_eap_header(struct wsc_eap_hdr*);
void wsc_debug_show_mgmt_header(struct wsc_ie_hdr*);
void wsc_debug_show_msg_header(struct wsc_eap_msg_hdr*);
void wsc_debug_show_tlv_msg(struct wsc_eap_tlv_hdr*, u16);
void wsc_debug_dump_buffer(char*, int);
void wsc_debug_show_message(void*);
void wsc_debug_show_mac(char*);
void wsc_debug_show_packet_headers(void*);
char * wsc_debug_get_status_str(int);
char * wsc_debug_get_attribute_str(int);
char * wsc_debug_get_ret_str(int);
int wsc_debug_set_blog(void*);

void wsc_debug_msg(int , char*, ...);
void wsc_debug_set_level(int);
int  wsc_debug_set_log(char*);

#endif /* _WSC_DEBUG_H_ */
