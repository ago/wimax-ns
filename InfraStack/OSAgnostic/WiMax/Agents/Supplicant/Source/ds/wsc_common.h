/*
 * WFA Simple Config: Common includes
 * Copyright 2006 Devicescape Software, Inc.
 * Erik Anvik <erik@devicescape.com>
 * All Rights Reserved.
 */

#ifndef _WSC_COMMON_H_
#define _WSC_COMMON_H_

#include <endian.h>
#include <byteswap.h>
#include <openssl/dh.h>
#include "wsc_types.h"
#include "wsc_controller.h"

/**
 * wsc_ie_hdr - simple config 801.11 information element header
 * @elemid: element identifier
 * @length: length in bytes of element
 * @oui: organizational unit identifier
 */
struct wsc_ie_hdr {
	u8 elemid; 
	u16 length;
	u32 oui;
} _WSC_STRUCT_PACKED_;

/**
 * wsc_device_type_id - simple config device type identifier
 * @cat: primary category identifier
 * @oui: organizational unit identifier
 * @subcat: device sub-category
 */
struct wsc_device_type_id {
	u16 cat;    
	u32 oui;    
	u16 subcat; 
} _WSC_STRUCT_PACKED_;

/**
 * wsc_eap_ctx - simple config EAP context object
 * @request_id: current request identifier
 * @received_id: current received identifier 
 * @uid: user identifier string
 */
struct wsc_eap_ctx {
	u8 request_id;
	u8 received_id;
	u8 uid[256];
};

/**
 * wsc_buffer_ctx - simple config buffer context object
 * @outbuf: pointer to head output data buffer
 * @outlen: current output buffer length 
 * @inbuf:  pointer to head incoming data buffer
 * @inlen: current input buffer length
 * @arg: argument that contains data to move into buffer
 * @arg1: optinal argument used for variable length data elements
 * @argl: length of arg1
 */
struct wsc_buffer_ctx {
	void *outbuf; 
	u16 outlen; 
	void *inbuf;  
	u16 inlen;  
	void *arg;    
	void *arg1;   
	u16 argl;   
};

/**
 * wsc_event_msg - simple config notifier optional message  
 * @state: current session state 
 * @msg: description string
 * @data: associated data 
 */
struct wsc_event_msg {
	int state;
	char *msg;
	void *data;
};

/**
 * wsc_timer - simple config protocol timer object 
 * @start: start tick when timer is started
 * @period: number of seconds before expiration
 * @active: indicates whether or not timer is in use(1) or not in use(0) 
 * @expired: indicates whether or not timer is expired(1) or not expired(0)
 * @action: action to take in the event of a timeout
 * @cookie: argumment passed to handler when action is taken
 */
struct wsc_timer {
	int start; 
	int period;
	int active;
	int expired; 
	int (*action)(); 
	void *cookie;
};

/**
 * wsc_timer_ctx - simple config protocol timer context object 
 * @tick: 1 second timer tick counter
 * @handle: timer event handlers
 */
struct wsc_timer_ctx {
#define WSC_MAX_TIMERS (3)
	int tick;
	struct wsc_timer handle[WSC_MAX_TIMERS];
};

/**
 * wsc_event_ctx - simple config protocol event context object 
 * @started: start event indicator, e.g. PBC button press
 * @exit: indicates a termination event has occured
 * @link: indicates that the link layer is in the connected state 
 * @start: used to the start the protocol state machine
 * @stop: used to stop the protocl state machine
 * @connect: indicates that a new connection has happened
 * @disconnect: indicates that a current connection has stopped
 * @notifier: callbck used to notify control layer of protocol events 
 * @walk: walk timer identifier
 * @retry: retry time identifier
 * @timer: used to indicate timer events
 */
struct wsc_event_ctx {
	int started;         
	int exit;            
	int link; 
	int walk;            
	int retry;
	int timeout;
	struct wsc_timer_ctx timer;
	struct wsc_control_handlers *handler;           
};

/**
 * wsc_state_ctx - simple config protocol state context object 
 * @handler: state machine handler list 
 * @handle: current index, i.e. handler that is ready for execution
 * @current: current state of session
 * @retry: retry counter
 * @timeout: timeout period
 */
struct wsc_state_ctx {
	PHANDLER *handler;
	int handle; 
	int current;
};

/**
 * wsc_key_ctx - simple config key context object 
 * @auth: authentication key used to authenticate protocol messages 
 * @aes: aes key wrap key
 * @emsk: extened master session key
 * @kdk: key derivation key
 * @dhk: diffie hellman key
 * @iv: initialization vector
 * @kwa: aes key wrap authentication checksum
 * @label: puesdo random function key label
 */
struct wsc_key_ctx {
#define WSC_AUTH_KEY_SZ (32)
#define WSC_AES_KEY_SZ  (16)
#define WSC_EMSK_KEY_SZ (32)
#define WSC_KDK_KEY_SZ  (32)
#define WSC_DHK_KEY_SZ  (32)
#define WSC_IV_SZ       (16)
#define WSC_KWA_SZ      (8)	
	char  auth[WSC_AUTH_KEY_SZ];
	char  aes[WSC_AES_KEY_SZ];
	char  emsk[WSC_EMSK_KEY_SZ];	
	char  kdk[WSC_KDK_KEY_SZ]; 
	char  dhk[WSC_DHK_KEY_SZ]; 
	char  iv [WSC_IV_SZ];
	char  kwa[WSC_KWA_SZ];
	char *label;
};

/**
 * wsc_session_ctx - simple config parameter context object 
 * @dh: diffie hellman context 
 * @lastm: last message, i.e. Mn-1   
 * @lastml: last message length 
 * @enounce: enrollee nounce 
 * @esnounce1: first half of enrollee secret nonce 
 * @esnounce2: second half of enrollee secret nonce 
 * @rnonce: registrar nonce
 * @rsnonse1: first half of registrar secret nonce 
 * @rsnonce2: secoond half of registrar secret nonce 
 * @rhash1: first half of registar message hash
 * @rhash2: second half of registar message hash
 * @ehash1: first half of enrollee message hash
 * @ehash2: second half of enrollee message hash
 * @ruuid: registrar unique user identifier
 * @euuid: enrollee unique user identifier
 * @rpkey: registrar diffie hellman public key
 * @epkey: enrollee diffie hellman public key
 * @psk1: first half of password hash 
 * @psk2: second half of password hash
 * @credential: generated session credential, e.g. WPA PSK 
 * @version: current simple config version
 * @osversion: operating system version
 * @aflags: authentication type flags
 * eflags: encryption type flags
 * cflags: connection type flags
 * cmethods: configuration methods
 * manf: manufacturer id
 * mname: model name
 * mnumber: model number
 * snumber: serial number
 * dname: device name
 * rfband: enrollee rf band
 * assocstate: association state
 * cfgerror: configuration error
 * pwdid: device password id
 * auth: authenticator - keyed hash
 * secret: diffie hellman generated shared secret
 * macaddr: enrollee MAC address
 * pwd: enrollee password
 * registrar: selected registrar
 * state: simple config state
 * devtype: primary device type
 * myaddr: local MAC address
 * pin: numeric version of enrollee pwd
 */
struct wsc_session_ctx {
#define WSC_MACADDR_SZ (6)
#define WSC_CRED_SZ    (32)
#define WSC_NONCE_SZ   (16)
#define WSC_HASH_SZ    (32)
#define WSC_DH_KEY_SZ  (192)
#define WSC_PIN_SZ     (8)
#define WSC_UUID_SZ    (16)
#define WSC_MCHECK_SZ  (8)
	DH *dh;     
	char *lastm; 
	u16 lastml; 
  
	/* enrollee nonces */
	char enonce[WSC_NONCE_SZ];  
	char esnonce1[WSC_NONCE_SZ];
	char esnonce2[WSC_NONCE_SZ];
	
	/* regisitrar nonces */	
	char rnonce[WSC_NONCE_SZ];  
	char rsnonce1[WSC_NONCE_SZ];
	char rsnonce2[WSC_NONCE_SZ];
	
	/* registrar hash's */
	char rhash1[WSC_HASH_SZ];
	char rhash2[WSC_HASH_SZ];
	
	/* enrollee hash's */
	char ehash1[WSC_HASH_SZ];
	char ehash2[WSC_HASH_SZ];
	
	/* unique user identifiers */
	char ruuid[WSC_UUID_SZ]; 
	char euuid[WSC_UUID_SZ];
  
	/* diffie hellman */
	char rpkey[WSC_DH_KEY_SZ];
	char epkey[WSC_DH_KEY_SZ];
	
	/* password keyed hashes */
	char psk1[WSC_HASH_SZ];
	char psk2[WSC_HASH_SZ];	
	
	/* session credential */
	char credential[WSC_CRED_SZ];  
	
	/* configuration */
	char version[1];               
	char osversion[8];             
	char aflags[2];                
	char eflags[2];                
	char cflags[1];                
	char cmethods[2];              
	char manf[64];              
	char mname[32];             
	char mnumber[32];          
	char snumber[32];             
	char dname[32];               
	char rfband[1];                  
	char assocstate[2];              
	char cfgerror[2];                
	char pwdid[2];                   
	char auth[WSC_MCHECK_SZ];     
	char secret[WSC_DH_KEY_SZ];   
	char macaddr[WSC_MACADDR_SZ]; 
	char pwd[WSC_PIN_SZ];         
	char registrar[4];               
	char state[1];                   
	struct wsc_device_type_id devtype;
	char myaddr[WSC_MACADDR_SZ];
	u32 pin;
};

/**
 * wsc_ctx - simple config session context object 
 * @eap: EAP protocol context
 * @event: session event context
 * @state: session state machine context
 * @session: session message/parameter context
 * @key: session key context
 * @sta: station MAC address cache and key state
 * @mem: memory buffer context
 * @ret: module return code
 * @reason: failure case reason code
 * @status: status structure used by calling methods on return
 */
struct wsc_ctx {
	struct wsc_eap_ctx *eap;     
	struct wsc_event_ctx *event;   
	struct wsc_state_ctx state;   
	struct wsc_session_ctx session; 
	struct wsc_key_ctx key;     
	struct wsc_buffer_ctx *mem;     
	int ret;
	int reason;
};

/* internal authentication states */
enum {
	WSC_INIT,
	WSC_STARTED,
	WSC_FINISHED
};

#define WSC_DH_KEY_SZ_BITS (1536)
#define WSC_DH_BASE_VALUE  (2)	

/* simple config opcode - also used to indicate session status */
enum {
	WSC_ERROR = 0,
	WSC_START,  
	WSC_ACK,    
	WSC_NACK,   
	WSC_MSG,    
	WSC_M2D,
	WSC_DONE,   
	WSC_RESET,
	WSC_TERMINATE,
	WSC_COMPLETED
};

#define MODULE "SIMPLE CONFIG: f:" __FILE__ " :"

/* defines */
#define WSC_ELEMENT_ID       221
#define WSC_OUI              0x04F25000
#define WSC_PBC_WALK_TIMEOUT 120 /* seconds */
#define WSC_RETRY_TIMEOUT    5  /* seconds */


#define WSC_VENDOR_ID        0x00372A
#define WSC_VENDOR_TYPE      0x000000001

#define WSC_PRF_LABEL        "Wi-Fi Easy and Secure Key Derivation"
#define WSC_IE_HDR_SZ        sizeof(WSC_IE_HDR)

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define LE_TO_HOST16(n) (n)
#define HOST_TO_LE16(n) (n)
#define BE_TO_HOST16(n) bswap_16(n)
#define HOST_TO_BE16(n) bswap_16(n)
#define LE_TO_HOST32(n) (n)
#define BE_TO_HOST32(n) bswap_32(n)
#define HOST_TO_BE32(n) bswap_32(n)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define LE_TO_HOST16(n) bswap_16(n)
#define HOST_TO_LE16(n) bswap_16(n)
#define BE_TO_HOST16(n) (n)
#define HOST_TO_BE16(n) (n)
#define LE_TO_HOST32(n) bswap_32(n)
#define BE_TO_HOST32(n) (n)
#define HOST_TO_BE32(n) (n)
#endif

/* Macros for handling unaligned 16-bit variables */
#define WSC_GET_BE16(a) ((u16) (((a)[0] << 8) | (a)[1]))
#define WSC_PUT_BE16(a, val)			\
	do {					\
		(a)[0] = ((u16) (val)) >> 8;	\
		(a)[1] = ((u16) (val)) & 0xff;	\
	} while (0)

#define WSC_GET_LE16(a) ((u16) (((a)[1] << 8) | (a)[0]))
#define WSC_PUT_LE16(a, val)			\
	do {					\
		(a)[1] = ((u16) (val)) >> 8;	\
		(a)[0] = ((u16) (val)) & 0xff;	\
	} while (0)

#define WSC_GET_BE24(a) ((((u32) (a)[0]) << 16) | (((u32) (a)[1]) << 8) | \
			 ((u32) (a)[2]))
#define WSC_PUT_BE24(a, val)				\
	do {						\
		(a)[0] = (u8) (((u32) (val)) >> 16);	\
		(a)[1] = (u8) (((u32) (val)) >> 8);	\
		(a)[2] = (u8) (((u32) (val)) & 0xff);	\
	} while (0)

#define WSC_GET_BE32(a) ((((u32) (a)[0]) << 24) | (((u32) (a)[1]) << 16) | \
			 (((u32) (a)[2]) << 8) | ((u32) (a)[3]))
#define WSC_PUT_BE32(a, val)				\
	do {						\
		(a)[0] = (u8) (((u32) (val)) >> 24);	\
		(a)[1] = (u8) (((u32) (val)) >> 16);	\
		(a)[2] = (u8) (((u32) (val)) >> 8);	\
		(a)[3] = (u8) (((u32) (val)) & 0xff);	\
	} while (0)

#define WSC_MALLOC(s) {malloc(s);}
#define WSC_CALLOC(n, s) {calloc(n, s);}
#define WSC_FREE(p) {if (p) {free(p); p = NULL;}}

/* public methods */
void * wsc_init(char*);
int wsc_deinit(struct wsc_ctx*);
int wsc_reset(struct wsc_ctx*);
u16 wsc_extend_buffer(struct wsc_buffer_ctx*, u16);
int wsc_generate_nonce(u8*, int);
int wsc_generate_dh_secret(struct wsc_ctx*, char*);
int wsc_generate_dh_key(DH*);
void * wsc_generate_rfc3526_prime_1536(struct wsc_ctx *); 
void wsc_generate_session_keys(struct wsc_ctx *, char *);
void wsc_hmac_sha_256(void*, int, int, char**, int*, char*);
void * wsc_generate_credential(int*);
void * wsc_encrypt_msg(struct wsc_ctx*, char*, int, int*);
int wsc_decrypt_msg(struct wsc_ctx*, char*, int, char*);
void wsc_mfree(struct wsc_buffer_ctx*);
void wsc_mreset(struct wsc_buffer_ctx*);
void wsc_areset(struct wsc_buffer_ctx*);
void wsc_get_user_password(struct wsc_ctx*);
int wsc_validate_user_password(struct wsc_ctx*);
void wsc_generate_msg_hash(struct wsc_ctx*, void*, int, void*, int, char*);
int wsc_validate_pin_chksum(unsigned long int);
int wsc_compute_pin_chksum(unsigned long int);
int wsc_ascii_pin_to_decimal(char*);
int wsc_session_in_progress(struct wsc_ctx*); 

int wsc_create_timer(struct wsc_ctx*, void*);
int wsc_delete_timer(struct wsc_ctx*, int);
int wsc_start_timer(struct wsc_ctx*, int, int);
int wsc_stop_timer(struct wsc_ctx*, int);

int wsc_create_m1(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m2(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m2d(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m3(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m4(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m5(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m6(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m7(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_m8(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_ack(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_nack(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_done(struct wsc_ctx*, struct wsc_buffer_ctx*);

void wsc_create_ie_hdr(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_beacon(struct wsc_ctx*, struct wsc_buffer_ctx*);
int wsc_create_probe_rsp(struct wsc_ctx*, struct wsc_buffer_ctx*, char);
int wsc_create_probe_req(struct wsc_ctx*, struct wsc_buffer_ctx*, char);

void * wsc_registrar_init(char*);
void * wsc_enrollee_init(char*);
int wsc_session_ctl(struct wsc_ctx*, int, void*);
#endif /* _WSC_COMMON_H_ */
