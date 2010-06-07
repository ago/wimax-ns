/*
 * WFA Simple Config: controller module includes
 * Copyright 2006 Devicescape Software, Inc.
 * All Rights Reserved.
 */
#ifndef _WSC_CONTROLLER_H_
#define _WSC_CONTROLLER_H_

enum {
	WSC_GET_CFG_VERSION = 0,
	WSC_SET_CFG_VERSION,
	WSC_GET_CFG_OS_VERSION,
	WSC_SET_CFG_OS_VERSION,
	WSC_GET_CFG_R_UUID,
	WSC_SET_CFG_R_UUID,
	WSC_GET_CFG_A_FLAGS,
	WSC_SET_CFG_A_FLAGS,
	WSC_GET_CFG_E_FLAGS,
	WSC_SET_CFG_E_FLAGS,
	WSC_GET_CFG_C_FLAGS, 
	WSC_SET_CFG_C_FLAGS, 
	WSC_GET_CONFIG_PUSH_BUTTON,
	WSC_SET_CONFIG_PUSH_BUTTON,
	WSC_GET_CFG_MANF_NAME,
	WSC_SET_CFG_MANF_NAME,
	WSC_GET_CFG_M_NAME,
	WSC_SET_CFG_M_NAME,
	WSC_GET_CFG_M_NUMBER,
	WSC_SET_CFG_M_NUMBER,
	WSC_GET_CFG_S_NUMBER,
	WSC_SET_CFG_S_NUMBER,
	WSC_GET_CFG_PRIM_DEV_CAT_ID,
	WSC_SET_CFG_PRIM_DEV_CAT_ID,
	WSC_GET_OUI,
	WSC_SET_OUI,
	WSC_GET_CFG_PRIM_DEV_SUBCAT_ID,
	WSC_SET_CFG_PRIM_DEV_SUBCAT_ID,
	WSC_GET_CFG_DEV_NAME,
	WSC_SET_CFG_DEV_NAME,
	WSC_GET_CFG_DEV_PWDID,
	WSC_SET_CFG_DEV_PWDID,
	WSC_GET_CFG_DEV_PWD,
	WSC_SET_CFG_DEV_PWD,
	WSC_GET_DISCOVERY_MODE,
	WSC_SET_DISCOVERY_MODE,
	WSC_SET_PSK,
	WSC_GET_PSK
};

/* supported session modes */
enum {
	WSC_MODE_IS_ENROLLEE = 0,
	WSC_MODE_IS_REGISTRAR
};

/* supported credentials */
enum {
	WSC_CRED_IS_PSK = 0,         
	WSC_CRED_IS_CERTIFICATE  
};

/**
 * wsc_event - generic event/status type
 * @type: event type
 * @len: length of optional message
 * @text: optional verbose message text
 */
struct wsc_event {
	int type;
	int len;
	char *text;
};

/**
 * wsc_credential - generic credential type
 * @type: credential type (e.g. WPA-PSK)
 * @len: length of credential data element
 * @data: credential data (e.g. WPA-PSK data)
 */
struct wsc_credential {
	int   type; 
	int   len;  
	void *data; 
};

/**
 * wsc_control_handlers - simple config session handlers
 * @sm: control layer state machine
 * @enable: protocol layer enable method, i.e., Button press in PBC mode
 * @disable: protocol layer disable method
 * @connect: link layer connect event
 * @disconnect: link layer disconnect event
 * @reset: protocol layer reset method
 * @kickstart: protocol layer kickstart method
 * @msg: protocol layer packet message handler method
 * @step: protocol layer state machine update method
 * @ioctl: protocol layer control method
 * @deinit: protocol layer deinit method
 */
struct wsc_control_handlers {
	int (*sm)();
	int (*enable)();
	int (*disable)();
	int (*connect)();
	int (*disconnect)();
	int (*reset)();
	int (*kickstart)();
	int (*msg)();
	int (*step)();
	int (*ioctl)();
	int (*deinit)();
};

/**
 * wsc_session - simple config session context
 * @ctx: session context
 * @handler: session handlers
 */
struct wsc_session {
	struct wsc_ctx *ctx;
	struct wsc_control_handlers *handler;
};

/**
 * wsc_cadence_pattern - simple config status cadence patterns
 * @on: on time 
 * @off: off time 
 * @time_base: cadence time base i.e, milliseconds default
 */
struct wsc_cadence_pattern {
	int on;
	int off;
	int time_base;
};

/**
 * wsc_application - application context
 * @cookie: cookie passed to application through callback
 * @list: event list used to trigger application callback 
 * @list_len: event list length 
 * @notifier: callback registered by application 
 * @ifname: layer2 interface name
 * @auth_mode: authentication mode, e.g. PBC (push button config) 
 * @terminate: used as flag to terminate session
 * @reason: event reason code
 * @cadence: cadence patterns 
 */
struct wsc_application {
	void *cookie;
	char *list;
	int list_len;
	int (*notifier)();
	char *ifname;
	int auth_mode;
	int terminate;
	int reason;
	struct wsc_cadence_pattern cadence[4];
};

/**
 * wsc_controller_ctx - control layer context
 * @wsc: simple config protocol layer context
 * @application: application layer context
 */
struct wsc_controller_ctx {
	struct wsc_session *wsc;
	struct wsc_application *application;
};

#define MODULE "SIMPLE CONFIG: f:" __FILE__ " :"

/* TODO: Move to config file */
#define WSC_CFG_VERSION 0x10 /* MSB(4) Major LSB(4) Minor */
#define WSC_CFG_OS_VERSION 0x10000000 /* MSB(8) - 1 always - ENDIAN ?*/
#define WSC_CFG_R_UUID "Atheros  UUID-R"
#define WSC_CFG_E_UUID "Atheros  UUID-E"
#define WSC_CFG_MANF_NAME "Atheros  Manuf " "Atheros  Name  " \
"Atheros  123456" "Atheros  654321"
#define WSC_CFG_M_NAME "Atheros  Model " "Atheros  Name  " 
#define WSC_CFG_M_NUMBER "Atheros  Model " "Atheros  Number" 
#define WSC_CFG_S_NUMBER "Atheros  Serial" "Atheros  Number"
#define WSC_CFG_A_FLAGS (WSC_AUTH_OPEN | WSC_AUTH_WPA_PSK | WSC_AUTH_SHARED | \
WSC_AUTH_WPA | WSC_AUTH_WPA2 |WSC_AUTH_WPA2_PSK)
#define WSC_CFG_E_FLAGS (WSC_ENRYPT_TYPE_NONE | WSC_ENRYPT_TYPE_WEP  | \
WSC_ENRYPT_TYPE_TKIP | WSC_ENRYPT_TYPE_AES)
#define WSC_CFG_C_FLAGS (WSC_CONNECTION_ESS | WSC_CONNECTION_IBSS)
#define WSC_CFG_PRIM_DEV_CAT_ID    WSC_CAT_NETWORK_INFRASTRUCTURE
#define WSC_CFG_PRIM_DEV_SUBCAT_ID WSC_SUBCAT_AP
#define WSC_CFG_DEV_NAME "Simple Config  " "Enabled AP !!!!" 
#define WSC_CFG_DEV_PWDID WSC_PASSWORD_ID_PUSH_BUTTON
#define WSC_MODE WSC_PBC_MODE
#define WSC_MSG_TIMEOUT 5

/* public methods */
void * wsc_controller_init(int, char*);
int wsc_controller_start_session(struct wsc_controller_ctx*);
int wsc_controller_process_data(struct wsc_controller_ctx *);
int wsc_controller_session_overlap(void*);
int wsc_controller_enable_discovery_mode(struct wsc_controller_ctx*);
int wsc_controller_disable_discovery_mode(struct wsc_controller_ctx*);
int wsc_controller_session_overlap(void*);
int wsc_controller_deinit(struct wsc_controller_ctx*); 
int wsc_controller_set_auth_mode(struct wsc_controller_ctx*, int);
int wsc_controller_get_auth_mode(struct wsc_controller_ctx*);
int wsc_controller_get_client_auth_mode(struct wsc_controller_ctx*);
int wsc_controller_set_pin(struct wsc_controller_ctx*, char*);
char * wsc_controller_get_pin(struct wsc_controller_ctx*);
int wsc_controller_set_psk(struct wsc_controller_ctx*, char*);
char * wsc_controller_get_psk(struct wsc_controller_ctx*);
void * wsc_controller_create_unique_ssid();
void * wsc_controller_create_unique_psk();
int wsc_controller_generate_pin(struct wsc_controller_ctx*);
int wsc_controller_enable_session(struct wsc_controller_ctx*);
int wsc_controller_disable_session(struct wsc_controller_ctx *);
int wsc_controller_set_logging_level(char*, int);
int wsc_controller_register_event_handler(struct wsc_controller_ctx*, void*, 
					  void*, char*, int);
int wsc_controller_set_blog(void*);
#endif /* _WSC_CONTROLLER_H_ */
