/*
 * wpa_supplicant - Internal definitions
 * Copyright (c) 2003-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright (c) 2004-2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef WPA_SUPPLICANT_I_H
#define WPA_SUPPLICANT_I_H

#include "driver.h"
#include "config_api.h"

#ifdef EAP_SIMPLE_CONFIG
#include "simple_config.h"
#endif /* EAP_SIMPLE_CONFIG */

struct ccx_data;
struct wpa_blacklist {
	struct wpa_blacklist *next;
	u8 bssid[ETH_ALEN];
	int count;
};


struct wpa_scan_result;
struct wpa_sm;
struct wpa_supplicant;

/*
 * Forward declarations of private structures used within the ctrl_iface
 * backends. Other parts of wpa_supplicant do not have access to data stored in
 * these structures.
 */
struct ctrl_iface_priv;
struct ctrl_iface_global_priv;

/**
 * struct wpa_interface - Parameters for wpa_supplicant_add_iface()
 */
struct wpa_interface {
	/**
	 * confname - Configuration name (file or profile) name
	 *
	 * This can also be %NULL when a configuration file is not used. In
	 * that case, ctrl_interface must be set to allow the interface to be
	 * configured.
	 */
	const char *confname;

	/**
	 * ctrl_interface - Control interface parameter
	 *
	 * If a configuration file is not used, this variable can be used to
	 * set the ctrl_interface parameter that would have otherwise been read
	 * from the configuration file. If both confname and ctrl_interface are
	 * set, ctrl_interface is used to override the value from configuration
	 * file.
	 */
	const char *ctrl_interface;

	/**
	 * driver - Driver interface name, or %NULL to use the default driver
	 */
	const char *driver;

	/**
	 * driver_param - Driver interface parameters
	 *
	 * If a configuration file is not used, this variable can be used to
	 * set the driver_param parameters that would have otherwise been read
	 * from the configuration file. If both confname and driver_param are
	 * set, driver_param is used to override the value from configuration
	 * file.
	 */
	const char *driver_param;

	/**
	 * ifname - Interface name
	 */
	const char *ifname;

#ifdef __vxworks
	wpa_config_t *cfg;
#endif /* __vxworks */
#ifdef CONFIG_BACKEND_API
	swc_config_t *cfg;
#endif /* __vxworks */
};

/**
 * struct wpa_params - Parameters for wpa_supplicant_init()
 */
struct wpa_params {
	/**
	 * daemonize - Run %wpa_supplicant in the background
	 */
	int daemonize;

	/**
	 * wait_for_interface - Wait for the network interface to appear
	 *
	 * If set, %wpa_supplicant will wait until all the configured network
	 * interfaces are available before starting processing. Please note
	 * that in many cases, a better alternative would be to start
	 * %wpa_supplicant without network interfaces and add the interfaces
	 * dynamically whenever they become available.
	 */
	int wait_for_interface;

	/**
	 * wait_for_monitor - Wait for a monitor program before starting
	 */
	int wait_for_monitor;

	/**
	 * pid_file - Path to a PID (process ID) file
	 *
	 * If this and daemonize are set, process ID of the background process
	 * will be written to the specified file.
	 */
	char *pid_file;

	/**
	 * wpa_debug_level - Debugging verbosity level (e.g., MSG_INFO)
	 */
	int wpa_debug_level;

	/**
	 * wpa_debug_show_keys - Whether keying material is included in debug
	 *
	 * This parameter can be used to allow keying material to be included
	 * in debug messages. This is a security risk and this option should
	 * not be enabled in normal configuration. If needed during
	 * development or while troubleshooting, this option can provide more
	 * details for figuring out what is happening.
	 */
	int wpa_debug_show_keys;

	/**
	 * wpa_debug_timestamp - Whether to include timestamp in debug messages
	 */
	int wpa_debug_timestamp;

	/**
	 * ctrl_interface - Global ctrl_iface path/parameter
	 */
	char *ctrl_interface;
};

/**
 * struct wpa_global - Internal, global data for all %wpa_supplicant interfaces
 *
 * This structure is initialized by calling wpa_supplicant_init() when starting
 * %wpa_supplicant.
 */
struct wpa_global {
	struct wpa_supplicant *ifaces;
	struct wpa_params params;
	struct ctrl_iface_global_priv *ctrl_iface;
};

/**
 * struct wpa_supplicant - Internal data for wpa_supplicant interface
 *
 * This structure contains the internal data for core wpa_supplicant code. This
 * should be only used directly from the core code. However, a pointer to this
 * data is used from other files as an arbitrary context pointer in calls to
 * core functions.
 */
struct wpa_supplicant {
	struct wpa_global *global;
	struct wpa_supplicant *next;
	struct l2_packet_data *l2;
	unsigned char own_addr[ETH_ALEN];
	char ifname[100];

	char *confname;
	struct wpa_config *conf;
	int countermeasures;
	os_time_t last_michael_mic_error;
	u8 bssid[ETH_ALEN];
	int reassociate; /* reassociation requested */
	int disconnected; /* all connections disabled; i.e., do no reassociate
			   * before this has been cleared */
	struct wpa_ssid *current_ssid;

	/* Selected configuration (based on Beacon/ProbeResp WPA IE) */
	int pairwise_cipher;
	int group_cipher;
	int key_mgmt;
	int mgmt_group_cipher;
	int ccx_cipher;

	void *drv_priv; /* private data used by driver_ops */

	struct wpa_ssid *prev_scan_ssid; /* previously scanned SSID;
					  * NULL = not yet initialized (start
					  * with broadcast SSID)
					  * BROADCAST_SSID_SCAN = broadcast
					  * SSID was used in the previous scan
					  */
#define BROADCAST_SSID_SCAN ((struct wpa_ssid *) 1)

	struct wpa_scan_result *scan_results;
	int num_scan_results;

	struct wpa_driver_ops *driver;
	int interface_removed; /* whether the network interface has been
				* removed */
	struct wpa_sm *wpa;
	struct eapol_sm *eapol;

	struct ctrl_iface_priv *ctrl_iface;

	wpa_states wpa_state;
	int new_connection;
	int reassociated_connection;

	int eapol_received; /* number of EAPOL packets received after the
			     * previous association event */

	struct scard_data *scard;

	unsigned char last_eapol_src[ETH_ALEN];

	int keys_cleared;

	struct wpa_blacklist *blacklist;

	int scan_req; /* manual scan request; this forces a scan even if there
		       * are no enabled networks in the configuration */

	int adhoc;

	struct ccx_data *ccx;

#ifdef EAP_SIMPLE_CONFIG
	struct simplecfg_data *scfg;	
#endif	/* EAP_SIMPLE_CONFIG */
#ifdef CONFIG_BACKEND_API
	swc_config_t *swc_config;
#endif /* __vxworks */
};


/* wpa_supplicant.c */
void wpa_supplicant_cancel_scan(struct wpa_supplicant *wpa_s);

int wpa_supplicant_reload_configuration(struct wpa_supplicant *wpa_s);

const char * wpa_supplicant_state_txt(int state);
int wpa_supplicant_driver_init(struct wpa_supplicant *wpa_s,
			       int wait_for_interface);
struct wpa_blacklist * wpa_blacklist_get(struct wpa_supplicant *wpa_s,
					 const u8 *bssid);
int wpa_blacklist_add(struct wpa_supplicant *wpa_s, const u8 *bssid);
int wpa_blacklist_del(struct wpa_supplicant *wpa_s, const u8 *bssid);
void wpa_blacklist_clear(struct wpa_supplicant *wpa_s);
int wpa_supplicant_set_suites(struct wpa_supplicant *wpa_s,
			      struct wpa_scan_result *bss,
			      struct wpa_ssid *ssid,
			      u8 *wpa_ie, size_t *wpa_ie_len);

#ifdef EAP_SIMPLE_CONFIG
void wpa_supplicant_simplecfg_init(struct wpa_supplicant *wpa_s);
void wpa_supplicant_simplecfg_start(struct wpa_supplicant *wpa_s);
void wpa_supplicant_simplecfg_exit(struct wpa_supplicant *wpa_s);
void wpa_supplicant_simplecfg_update_state(struct wpa_supplicant *wpa_s,
					   int success);
void wpa_supplicant_simplecfg_event_handler(void * ctx, int code);
int wpa_supplicant_simplecfg_save_network(struct wpa_supplicant *wpa_s);
#endif /* EAP_SIMPLE_CONFIG */

void wpa_supplicant_set_non_wpa_policy(struct wpa_supplicant *wpa_s,
				       struct wpa_ssid *ssid);
void wpa_supplicant_initiate_eapol(struct wpa_supplicant *wpa_s);
int wpa_supplicant_get_scan_results(struct wpa_supplicant *wpa_s);
void wpa_clear_keys(struct wpa_supplicant *wpa_s, const u8 *addr);
void wpa_supplicant_req_auth_timeout(struct wpa_supplicant *wpa_s,
				     int sec, int usec);
void wpa_supplicant_set_state(struct wpa_supplicant *wpa_s, wpa_states state);
struct wpa_ssid * wpa_supplicant_get_ssid(struct wpa_supplicant *wpa_s);
void wpa_supplicant_cancel_auth_timeout(struct wpa_supplicant *wpa_s);
void wpa_supplicant_deauthenticate(struct wpa_supplicant *wpa_s,
				   int reason_code);
void wpa_supplicant_disassociate(struct wpa_supplicant *wpa_s,
				 int reason_code);
void wpa_supplicant_req_scan(struct wpa_supplicant *wpa_s, int sec, int usec);
int wpa_eapol_set_wep_key(void *ctx, int unicast, int keyidx,
			  const u8 *key, size_t keylen);

void wpa_show_license(void);

struct wpa_supplicant * wpa_supplicant_add_iface(struct wpa_global *global,
						 struct wpa_interface *iface);
int wpa_supplicant_remove_iface(struct wpa_global *global,
				struct wpa_supplicant *wpa_s);
struct wpa_supplicant * wpa_supplicant_get_iface(struct wpa_global *global,
						 const char *ifname);
struct wpa_global * wpa_supplicant_init(struct wpa_params *params);
int wpa_supplicant_run(struct wpa_global *global);
void wpa_supplicant_deinit(struct wpa_global *global);


/* driver_ops */
static inline void * wpa_drv_init(struct wpa_supplicant *wpa_s,
				  const char *ifname)
{
	if (wpa_s->driver->init) {
		return wpa_s->driver->init(wpa_s, ifname);
	}
	return NULL;
}

static inline void wpa_drv_deinit(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->deinit)
		wpa_s->driver->deinit(wpa_s->drv_priv);
}

static inline int wpa_drv_set_param(struct wpa_supplicant *wpa_s,
				    const char *param)
{
	if (wpa_s->driver->set_param)
		return wpa_s->driver->set_param(wpa_s->drv_priv, param);
	return 0;
}

static inline int wpa_drv_set_drop_unencrypted(struct wpa_supplicant *wpa_s,
					       int enabled)
{
	if (wpa_s->driver->set_drop_unencrypted) {
		return wpa_s->driver->set_drop_unencrypted(wpa_s->drv_priv,
							   enabled);
	}
	return -1;
}

static inline int wpa_drv_set_countermeasures(struct wpa_supplicant *wpa_s,
					      int enabled)
{
	if (wpa_s->driver->set_countermeasures) {
		return wpa_s->driver->set_countermeasures(wpa_s->drv_priv,
							  enabled);
	}
	return -1;
}

static inline int wpa_drv_set_auth_alg(struct wpa_supplicant *wpa_s,
				       int auth_alg)
{
	if (wpa_s->driver->set_auth_alg) {
		return wpa_s->driver->set_auth_alg(wpa_s->drv_priv,
						   auth_alg);
	}
	return -1;
}

static inline int wpa_drv_set_wpa(struct wpa_supplicant *wpa_s, int enabled)
{
	if (wpa_s->driver->set_wpa) {
		return wpa_s->driver->set_wpa(wpa_s->drv_priv, enabled);
	}
	return 0;
}

static inline int wpa_drv_associate(struct wpa_supplicant *wpa_s,
				    struct wpa_driver_associate_params *params)
{
	if (wpa_s->driver->associate) {
		return wpa_s->driver->associate(wpa_s->drv_priv, params);
	}
	return -1;
}

static inline int wpa_drv_scan(struct wpa_supplicant *wpa_s, const u8 *ssid,
			       size_t ssid_len)
{
	if (wpa_s->driver->scan) {
		return wpa_s->driver->scan(wpa_s->drv_priv, ssid, ssid_len);
	}
	return -1;
}

static inline int wpa_drv_get_scan_results(struct wpa_supplicant *wpa_s,
					   struct wpa_scan_result *results,
					   size_t max_size)
{
	if (wpa_s->driver->get_scan_results) {
		return wpa_s->driver->get_scan_results(wpa_s->drv_priv,
						       results, max_size);
	}
	return -1;
}

static inline int wpa_drv_get_bssid(struct wpa_supplicant *wpa_s, u8 *bssid)
{
	if (wpa_s->driver->get_bssid) {
		return wpa_s->driver->get_bssid(wpa_s->drv_priv, bssid);
	}
	return -1;
}

static inline int wpa_drv_get_ssid(struct wpa_supplicant *wpa_s, u8 *ssid)
{
	if (wpa_s->driver->get_ssid) {
		return wpa_s->driver->get_ssid(wpa_s->drv_priv, ssid);
	}
	return -1;
}

static inline int wpa_drv_set_key(struct wpa_supplicant *wpa_s, wpa_alg alg,
				   const u8 *addr, int key_idx, int set_tx,
				   const u8 *seq, size_t seq_len,
				   const u8 *key, size_t key_len)
{
	if (wpa_s->driver->set_key) {
		wpa_s->keys_cleared = 0;
		return wpa_s->driver->set_key(wpa_s->drv_priv, alg, addr,
					      key_idx, set_tx, seq, seq_len,
					      key, key_len);
	}
	return -1;
}

static inline int wpa_drv_deauthenticate(struct wpa_supplicant *wpa_s,
					 const u8 *addr, int reason_code)
{
	if (wpa_s->driver->deauthenticate) {
		return wpa_s->driver->deauthenticate(wpa_s->drv_priv, addr,
						     reason_code);
	}
	return -1;
}

static inline int wpa_drv_disassociate(struct wpa_supplicant *wpa_s,
				       const u8 *addr, int reason_code)
{
	if (wpa_s->driver->disassociate) {
		return wpa_s->driver->disassociate(wpa_s->drv_priv, addr,
						   reason_code);
	}
	return -1;
}

static inline int wpa_drv_add_pmkid(struct wpa_supplicant *wpa_s,
				    const u8 *bssid, const u8 *pmkid)
{
	if (wpa_s->driver->add_pmkid) {
		return wpa_s->driver->add_pmkid(wpa_s->drv_priv, bssid, pmkid);
	}
	return -1;
}

static inline int wpa_drv_remove_pmkid(struct wpa_supplicant *wpa_s,
				       const u8 *bssid, const u8 *pmkid)
{
	if (wpa_s->driver->remove_pmkid) {
		return wpa_s->driver->remove_pmkid(wpa_s->drv_priv, bssid,
						   pmkid);
	}
	return -1;
}

static inline int wpa_drv_flush_pmkid(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->flush_pmkid) {
		return wpa_s->driver->flush_pmkid(wpa_s->drv_priv);
	}
	return -1;
}

static inline int wpa_drv_get_capa(struct wpa_supplicant *wpa_s,
				   struct wpa_driver_capa *capa)
{
	if (wpa_s->driver->get_capa) {
		return wpa_s->driver->get_capa(wpa_s->drv_priv, capa);
	}
	return -1;
}

static inline void wpa_drv_poll(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->poll) {
		wpa_s->driver->poll(wpa_s->drv_priv);
	}
}

static inline const char * wpa_drv_get_ifname(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->get_ifname) {
		return wpa_s->driver->get_ifname(wpa_s->drv_priv);
	}
	return NULL;
}

static inline const u8 * wpa_drv_get_mac_addr(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->get_mac_addr) {
		return wpa_s->driver->get_mac_addr(wpa_s->drv_priv);
	}
	return NULL;
}

static inline int wpa_drv_send_eapol(struct wpa_supplicant *wpa_s,
				     const u8 *dst, u16 proto,
				     const u8 *data, size_t data_len)
{
	if (wpa_s->driver->send_eapol)
		return wpa_s->driver->send_eapol(wpa_s->drv_priv, dst, proto,
						 data, data_len);
	return -1;
}

static inline int wpa_drv_mlme_setprotection(struct wpa_supplicant *wpa_s,
					     const u8 *addr, int protect_type,
					     int key_type)
{
	if (wpa_s->driver->mlme_setprotection)
		return wpa_s->driver->mlme_setprotection(wpa_s->drv_priv, addr,
							 protect_type,
							 key_type);
	return 0;
}


static inline int wpa_drv_set_mode(struct wpa_supplicant *wpa_s, int mode)
{
	if (wpa_s->driver->set_mode) {
		return wpa_s->driver->set_mode(wpa_s->drv_priv, mode);
	}
	return -1;
}

static inline int wpa_drv_set_beacon_int(struct wpa_supplicant *wpa_s,
					 int beacon_int)
{
	if (wpa_s->driver->set_beacon_int) {
		return wpa_s->driver->set_beacon_int(wpa_s->drv_priv,
						     beacon_int);
	}
	return -1;
}

static inline int wpa_drv_set_channel(struct wpa_supplicant *wpa_s,
				      int channel)
{
	if (wpa_s->driver->set_channel) {
		return wpa_s->driver->set_channel(wpa_s->drv_priv, channel);
	}
	return -1;
}

static inline int wpa_drv_set_ssid(struct wpa_supplicant *wpa_s,
				   const u8 *ssid, size_t ssid_len)
{
	if (wpa_s->driver->set_ssid) {
		return wpa_s->driver->set_ssid(wpa_s->drv_priv, ssid,
					       ssid_len);
	}
	return -1;
}

static inline int wpa_drv_set_bssid(struct wpa_supplicant *wpa_s,
				    const u8 *bssid)
{
	if (wpa_s->driver->set_bssid) {
		return wpa_s->driver->set_bssid(wpa_s->drv_priv, bssid);
	}
	return -1;
}

#ifdef CONFIG_CCX
static inline int wpa_drv_ccx_rogue_ap_add(struct wpa_supplicant *wpa_s,
					   const u8 *addr, int reason)
{
	if (wpa_s->driver &&
	    wpa_s->driver->ccx_rogue_ap_add) {
		return wpa_s->driver->ccx_rogue_ap_add(wpa_s->drv_priv, addr,
						       reason);
	}
	return 0;
}

static inline int wpa_drv_ccx_rogue_ap_remove(struct wpa_supplicant *wpa_s,
					      const u8 *addr)
{
	if (wpa_s->driver &&
	    wpa_s->driver->ccx_rogue_ap_remove) {
		return wpa_s->driver->ccx_rogue_ap_remove(wpa_s->drv_priv,
							  addr);
	}
	return 0;
}

static inline int wpa_drv_ccx_rogue_ap_remove_all(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver &&
	    wpa_s->driver->ccx_rogue_ap_remove_all) {
		return wpa_s->driver->ccx_rogue_ap_remove_all(wpa_s->drv_priv);
	}
	return 0;
}

static inline int wpa_drv_ccx_rogue_ap_report(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver &&
	    wpa_s->driver->ccx_rogue_ap_report) {
		return wpa_s->driver->ccx_rogue_ap_report(wpa_s->drv_priv);
	}
	return 0;
}
#endif /* CONFIG_CCX */

static inline int wpa_drv_set_mixed_cell(struct wpa_supplicant *wpa_s,
					 int enabled)
{
	if (wpa_s->driver->set_mixed_cell) {
		return wpa_s->driver->set_mixed_cell(wpa_s->drv_priv, enabled);
	}
	return -1;
}

#endif /* WPA_SUPPLICANT_I_H */
