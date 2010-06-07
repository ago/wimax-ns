/*
 * WPA Supplicant - CCX (Cisco Compatible Extensions)
 * Copyright (c) 2004, Instant802 Networks, Inc.
 * Copyright (c) 2004-2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef CCX_H
#define CCX_H

#ifdef CONFIG_CCX

struct ccx_data;
struct wpa_supplicant;

struct wpa_ie_data;

struct ccx_ctx {
	int (*set_key)(void *ctx, wpa_alg alg,
		       const u8 *addr, int key_idx, int set_tx,
		       const u8 *seq, size_t seq_len,
		       const u8 *key, size_t key_len);
};

enum {
	CCX_ROGUE_AP_INVALID_AUTH_TYPE = 1,
	CCX_ROGUE_AP_AUTH_TIMEOUT = 2,
	CCX_ROGUE_AP_CHALLENGE_FROM_AP_FAILED = 3,
	CCX_ROGUE_AP_CHALLENGE_TO_AP_FAILED = 4,
};

#define CCX_ROGUE_AP_LIST_TIMEOUT 60

#ifdef CONFIG_CCX_NAC
/* NetTran Events */
#define PA_NEW_SESSION              0x00000001
#define PA_END_SESSION              0x00000002
#define PA_LINK_UP                  0x00000003
#define PA_LINK_DOWN                0x00000004
#define PA_LOG_HIGH                 0x00000005
#define PA_LOG_MEDIUM               0x00000006
#define PA_LOG_LOW                  0x00000007
#endif /* CONFIG_CCX_NAC */

struct ccx_data * ccx_init(struct wpa_supplicant *wpa_s,
			   const struct ccx_ctx *ctx);
void ccx_deinit(struct ccx_data *ccx);
int ccx_rogue_ap_add_current(struct wpa_supplicant *wpa_s, int reason);
int ccx_rogue_ap_remove_current(struct wpa_supplicant *wpa_s);
int ccx_rogue_ap_remove_all(struct ccx_data *ccx);
int ccx_rogue_ap_report(struct wpa_supplicant *wpa_s);
int ccx_parse_assoc_ie(struct wpa_supplicant *wpa_s,
		       const u8 *req_ies, size_t req_ies_len,
		       const u8 *resp_ies, size_t resp_ies_len);
int ccx_cckm_add_ie(struct wpa_supplicant *wpa_s, struct wpa_ssid *ssid,
		    u64 tsf, const u8 *ie, size_t ie_len,
		    u8 *buf, size_t buf_len);
int ccx_cckm_associate(struct wpa_supplicant *wpa_s);
int ccx_cckm_pmk_to_ptk(struct wpa_supplicant *wpa_s,
			const u8 *pmk, size_t pmk_len, const u8 *bssid,
			const u8 *own_addr, const u8 *snonce, const u8 *anonce,
			u8 *krk, size_t krk_len, u8 *ptk, size_t ptk_len);
int ccx_cckm_valid(struct ccx_data *ccx);

#ifdef CONFIG_CCX_NAC
void ccx_nac_eap_start(struct wpa_supplicant *wpa_s, int is_preauth);
int ccx_nac_eap_packet(struct wpa_supplicant *wpa_s,
		       const u8 *eap_hdr, size_t eap_len,
		       u8 **resp, size_t *resp_len,
		       int is_preauth);
void ccx_nac_eap_end(struct wpa_supplicant *wpa_s,
		     int is_preauth);
void ccx_nac_event(struct wpa_supplicant *wpa_s, unsigned int event,
		   int is_preauth);
int ccx_nac_async_event(struct wpa_supplicant *wpa_s, char *params,
			char *resp, int resp_size);

#ifdef EAP_FAST
struct eap_fast_pac;
struct eap_fast_pac ** ccx_ua_pac_db(struct wpa_supplicant *wpa_s);
#endif /* EAP_FAST */
#endif /* CONFIG_CCX_NAC */

#endif /* CONFIG_CCX */

#endif /* CCX_H */
