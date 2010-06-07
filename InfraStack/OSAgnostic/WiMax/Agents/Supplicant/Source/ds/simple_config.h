/*
 * WFA Simple Config: Registrar command line application support
 * Copyright 2006 Devicescape Software, Inc.
 * All Rights Reserved.
 */
#ifndef _SIMPLE_CONFIG_H_
#define _SIMPLE_CONFIG_H_

#include "wsc_types.h"
#include "wsc_controller.h"
#include "wsc_attributes.h"

enum {
	SIMPLE_CFG_MODE_INACTIVE = 0,
	SIMPLE_CFG_MODE_DISCOVERY,
	SIMPLE_CFG_MODE_ACTIVE,
	SIMPLE_CFG_MODE_COMPLETE
};

/**
 * simple_config - simple config session context
 * @controller: control layey context
 * @enabled: simple config enable status
 * @init: simple config init status
 * @pbc_enabled: PBC supported flag
 * @pbc_armed: PBC button has been pressed
 * @ssid: ???
 * @passphrase: ???
 * @psk: ???
 * @file: file name used for debug and IPC messages
 * @fp: file descriptor of debug file
 * @bp: back pointer to simple config context
 * @cookie: wpa supplicant context
 */
struct simple_config {
	struct wsc_controller_ctx *controller;
	struct simplecfg_data *bp; /* hack */
        int enabled;
	int init;
        int pbc_enabled;
        int pbc_armed;
        char pin[8];        
        char *ssid;
        char *passphrase;
        char psk[32]; 
	char *file;
	FILE *fp;
	void *cookie; 
};

/**
 * simple_config_ap_cache - simple config access point list
 * @ap: ap context
 * @capable: simple config capable flag
 * @pbc_active: indicates that a registar is in PBC mode
 */
struct simple_config_ap_cache {
	struct wpa_scan_result *ap;
	int capable;
	int try;
	int pbc_active;
};

/**
 * simplecfg_data - simple config context object
 * @mode: current operating mode, e.g., discovery mode
 * @cache_len: length of ap wpa cache
 * @cache: ap cache
 * @ssid: ssid place holder
 * @ctx: simple config cookie
 */
struct simplecfg_data {
	int mode;
	int cache_len;
	int current_ap;
	int timeout;
	struct simple_config_ap_cache *cache;
	struct wpa_ssid *ssid;
	struct wpa_scan_result *ap;
	struct simple_config *ctx;
};

struct wpa_supplicant; /* hack */
int simple_config_handle_scan_event(struct wpa_supplicant*);
int simple_config_handle_assoc_event(struct wpa_supplicant*);

int simple_config_deinit(void*);
int simple_config_enable(struct simple_config*);
int simple_config_disable(struct simple_config*);
int simple_config_pbc_enable(struct simple_config*);
int simple_config_pbc_disable(struct simple_config*);
int simple_config_pbc_activate(struct simple_config*);
int simple_config_set_ssid(struct simple_config*, char*);
int simple_config_set_passphrase(struct simple_config*, char*);
int simple_config_set_pin(struct simple_config*, char*);
int simple_config_set_psk(struct simple_config*, char*, char*);
int simple_config_is_cli_command(char *buf);                                         
int simple_config_execute_cli_command(struct wpa_supplicant *wpa_s, 
                                      char *cmd, char *buf, int buflen);

/* Supplicant config bindings */
struct parse_data; /* hack */
char * wpa_config_write_simplecfg_pin(const struct parse_data*, 
				      struct wpa_ssid*); 
int wpa_config_parse_simplecfg_pin(const struct parse_data*, struct wpa_ssid*, 
				   int, const char*); 
char * wpa_config_write_simplecfg_mode(const struct parse_data*, 
				       struct wpa_ssid*);
int wpa_config_parse_simplecfg_mode(const struct parse_data*, 
				    struct wpa_ssid*, int, const char*); 
char * wpa_config_write_simplecfg_countdown(const struct parse_data*, 
					    struct wpa_ssid*);
int wpa_config_parse_simplecfg_countdown(const struct parse_data*, 
					 struct wpa_ssid*, int, const char*);
#endif /* _SIMPLE_CONFIG_H_ */
