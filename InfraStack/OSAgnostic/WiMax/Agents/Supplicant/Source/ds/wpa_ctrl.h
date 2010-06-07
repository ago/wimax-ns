/*
 * wpa_supplicant/hostapd control interface library
 * Copyright (c) 2004-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright (c) 2004-2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef WPA_CTRL_H
#define WPA_CTRL_H

#ifdef  __cplusplus
extern "C" {
#endif

/* wpa_supplicant control interface - fixed message prefixes */

/** Interactive request for identity/password/pin */
#define WPA_CTRL_REQ "CTRL-REQ-"

/** Response to identity/password/pin request */
#define WPA_CTRL_RSP "CTRL-RSP-"

/* Event messages with fixed prefix */
/** Authentication completed successfully and data connection enabled */
#define WPA_EVENT_CONNECTED "CTRL-EVENT-CONNECTED "
/** Disconnected, data connection is not available */
#define WPA_EVENT_DISCONNECTED "CTRL-EVENT-DISCONNECTED "
/** wpa_supplicant is exiting */
#define WPA_EVENT_TERMINATING "CTRL-EVENT-TERMINATING "
/** Password change was completed successfully */
#define WPA_EVENT_PASSWORD_CHANGED "CTRL-EVENT-PASSWORD-CHANGED "
/** EAP-Request/Notification received */
#define WPA_EVENT_EAP_NOTIFICATION "CTRL-EVENT-EAP-NOTIFICATION "
/** EAP authentication started (EAP-Request/Identity received) */
#define WPA_EVENT_EAP_STARTED "CTRL-EVENT-EAP-STARTED "
/** EAP method selected */
#define WPA_EVENT_EAP_METHOD "CTRL-EVENT-EAP-METHOD "
/** EAP authentication completed successfully */
#define WPA_EVENT_EAP_SUCCESS "CTRL-EVENT-EAP-SUCCESS "
/** EAP authentication failed (EAP-Failure received) */
#define WPA_EVENT_EAP_FAILURE "CTRL-EVENT-EAP-FAILURE "

/* INTEL EVENTS - WIFI / WIMAX SHARED */
#define WPA_EVENT_REJECTED_CREDENTIAL	"CTRL-EVENT-REJECTED-CREDENTIAL "
#define WPA_EVENT_REJECTED_METHOD	"CTRL-EVENT-REJECTED-METHOD "
#define WPA_EVENT_REJECTED_IDENTITY	"CTRL-EVENT-REJECTED-IDENTITY "
#define WPA_EVENT_REJECTED_CERTIFICATE	"CTRL-EVENT-REJECTED-CERTIFICATE "
#define WPA_EVENT_REJECTED_SERVER_CERTIFICATE	"CTRL-EVENT-REJECTED-SERVER-CERTIFICATE "
#define WPA_EVENT_REJECTED_CHALLENGE	"CTRL-EVENT-REJECTED-CHALLENGE "
#define WPA_EVENT_RESTRICTED_LOGON_HOURS "CTRL-EVENT-RESTRICTED-LOGON-HOURS "
#define WPA_EVENT_ACCOUNT_DIABLED	"CTRL-EVENT-ACCOUNT-DISABLED "
#define WPA_EVENT_ACCOUNT_NO_DIAL_IN	"CTRL-EVENT-ACCOUNT-NO-DIAL-IN "
#define WPA_EVENT_TLV_INVALID		"CTRL-EVENT-TLV-INVALID "
#define WPA_EVENT_TLV_UNKNOWN		"CTRL-EVENT-TLV-UNKNOWN "
#define WPA_EVENT_TLV_NAK		"CTRL-EVENT-TLV-NAK "
#define WPA_EVENT_FAST_CMAC_INVALID	"CTRL-EVENT-FAST-CMAC-INVALID "
#define WPA_EVENT_FAST_PROVISION_SUCCESS "CTRL-EVENT-FAST-PROVISION-SUCCESS "
#define WPA_EVENT_FAST_INVALID_PAC_KEY	"CTRL-EVENT-FAST-INVALID-PAC-KEY "
#define WPA_EVENT_FAST_INVALID_PAC_OPAQUE "CTRL-EVENT-FAST-INVALID-PAC-OPAQUE "
#define WPA_EVENT_EAP_CLEAR_TEXT_FAILURE "CTRL-EVENT-EAP-CLEAR-TEXT-FAILURE "
#define WPA_EVENT_EAP_CLEAR_TEXT_SUCCESS "CTRL-EVENT-EAP-CLEAR-TEXT-SUCCESS "
#define WPA_EVENT_EAP_INTERMEDIATE_SUCCESS "CTRL-EVENT-EAP-INTERMEDIATE-SUCCESS "
#define WPA_EVENT_EAP_INTERMEDIATE_FAILURE "CTRL-EVENT-EAP-INTERMEDIATE-FAILURE "
#define WPA_EVENT_SIM_PIN_INCORRECT	"CTRL-EVENT-SIM-PIN-INCORRECT "
#define WPA_EVENT_SIM_PIN_REQUIRED	"CTRL-EVENT-SIM-PIN-REQUIRED "
#define WPA_EVENT_SIM_PIN_NO_READER	"CTRL-EVENT-SIM-NO-READER "
#define WPA_EVENT_SIM_PIN_NO_CARD	"CTRL-EVENT-SIM-NO-CARD "
#define WPA_EVENT_SIM_FAILURE		"CTRL-EVENT-FAILURE "
#define WPA_EVENT_EAP_TYPE_TLS		"CTRL-EVENT-EAP-TYPE-TLS "
#define WPA_EVENT_EAP_TYPE_TTLS		"CTRL-EVENT-EAP-TYPE-TTLS "
#define WPA_EVENT_EAP_TYPE_PEAP		"CTRL-EVENT-EAP-TYPE-PEAP "
#define WPA_EVENT_EAP_TYPE_SIM		"CTRL-EVENT-EAP-TYPE-SIM "
#define WPA_EVENT_EAP_TYPE_AKA		"CTRL-EVENT-EAP-TYPE-AKA "
#define WPA_EVENT_EAP_TYPE_PSK		"CTRL-EVENT-EAP-TYPE-PSK "
#define WPA_EVENT_EAP_TYPE_LEAP		"CTRL-EVENT-EAP-TYPE-LEAP "
#define WPA_EVENT_EAP_TYPE_FAST		"CTRL-EVENT-EAP-TYPE-FAST "
#define WPA_EVENT_EAP_KEY_AVAILABLE	"CTRL-EVENT-EAP-KEY-AVAILABLE "
#define WPA_EVENT_EAPOL_STARTED		"CTRL-EVENT-EAPOL-STARTED "
#define WPA_EVENT_EAPOL_TIMEOUT		"CTRL-EVENT-EAPOL-TIMEOUT "
#define WPA_EVENT_EAPOL_STOPPED		"CTRL-EVENT-EAPOL-STOPPED "
#define WPA_EVENT_EAPOL_CONNECTING	"CTRL-EVENT-EAPOL-CONNECTING "
#define WPA_EVENT_EAPOL_AUTHENTICATING	"CTRL-EVENT-EAPOL-AUTHENTICATING "
#define WPA_EVENT_EAPOL_AUTHENTICATED	"CTRL-EVENT-EAPOL-AUTHENTICATED "
#define WPA_EVENT_EAPOL_REAUTHENTICATING "CTRL-EVENT-EAPOL-REAUTHENTICATING "
#define WPA_EVENT_EAPOL_UNAUTHENTICATED	"CTRL-EVENT-EAPOL-UNAUTHENTICATED "
#define WPA_EVENT_EAPOL_NOT_REQUIRED	"CTRL-EVENT-EAPOL-NOT-REQUIRED "
#define WPA_EVENT_KM_REKEY		"CTRL-EVENT-KM-REKEY "
#define WPA_EVENT_KM_KEY_PAIRWISE	"CTRL-EVENT-KM-KEY-PAIRWISE "
#define WPA_EVENT_KM_KEY_GROUP		"CTRL-EVENT-KM-KEY-GROUP "
#define WPA_EVENT_KM_KEY_INVALID	"CTRL-EVENT-KM-KEY-INVALID "
#define WPA_EVENT_RSN_REQ_KEY_PAIRWISE	"CTRL-EVENT-RSN-REQ-KEY-PAIRWISE "
#define WPA_EVENT_RSN_REQ_KEY_GROUP	"CTRL-EVENT-RSN-REQ-KEY-GROUP "
#define WPA_EVENT_RSN_COUNTERMEASURE_START "CTRL-EVENT-RSN-COUNTERMEASURE-START "
#define WPA_EVENT_RSN_COUNTERMEASURE_STOP "CTRL-EVENT-RSN-COUNTERMEASURE-STOP "
#define WPA_EVENT_RSN_MULTIPLE_FIRST_MSG "CTRL-EVENT-RSN-MULTIPLE-FIRST-MSG "
#define WPA_EVENT_RSN_DISCONNECT	"CTRL-EVENT-RSN-DISCONNECT "
#define WPA_EVENT_RSN_MIC_FAILURE	"CTRL-EVENT-RSN-MIC-FAILURE "
#define WPA_EVENT_CCX_CCKM_ROAM		"CTRL-EVENT-CCX-CCKM-ROAM "
#define WPA_EVENT_PORT_STATUS_UNKNOWN	"CTRL-EVENT-PORT-STATUS-UNKNOWN "
#define WPA_EVENT_PORT_STATUS_STOPPED	"CTRL-EVENT-PORT-STATUS-STOPPED "
#define WPA_EVENT_PORT_STATUS_STARTED	"CTRL-EVENT-PORT-STATUS-STARTED "
#define WPA_EVENT_PORT_STATUS_LINK_DOWN	"CTRL-EVENT-PORT-STATUS-LINK-DOWN "
#define WPA_EVENT_PORT_STATUS_LINK_UP	"CTRL-EVENT-PORT-STATUS-LINK-UP "
#define WPA_EVENT_PORT_STATUS_LINK_RESET "CTRL-EVENT-PORT-STATUS-LINK-RESET "
#define WPA_EVENT_802_1X_START		"CTRL-EVENT-802-1X-START "
#define WPA_EVENT_802_1X_FAILED		"CTRL-EVENT-802-1X-FAILED "
#define WPA_EVENT_802_1X_ACQUIRED	"CTRL-EVENT-802-1X-ACQUIRED "
#define WPA_EVENT_802_1X_LOGOFF		"CTRL-EVENT-802-1X-LOGOFF "
#define WPA_EVENT_802_1X_TIMEOUT	"CTRL-EVENT-802-1X-TIMEOUT "
#define WPA_EVENT_NO_AAA_SERVER 	"CTRL-EVENT-NO-AAA-SERVER "
#define WPA_EVENT_TUNNEL_ESTABLISHED	"CTRL-EVENT-TUNNEL-ESTABLISHED "


/* wpa_supplicant/hostapd control interface access */

/**
 * wpa_ctrl_open - Open a control interface to wpa_supplicant/hostapd
 * @ctrl_path: Path for UNIX domain sockets; ignored if UDP sockets are used.
 * Returns: Pointer to abstract control interface data or %NULL on failure
 *
 * This function is used to open a control interface to wpa_supplicant/hostapd.
 * ctrl_path is usually /var/run/wpa_supplicant or /var/run/hostapd. This path
 * is configured in wpa_supplicant/hostapd and other programs using the control
 * interface need to use matching path configuration.
 */
struct wpa_ctrl * wpa_ctrl_open(const char *ctrl_path);


/**
 * wpa_ctrl_close - Close a control interface to wpa_supplicant/hostapd
 * @ctrl: Control interface data from wpa_ctrl_open()
 *
 * This function is used to close a control interface.
 */
void wpa_ctrl_close(struct wpa_ctrl *ctrl);


/**
 * wpa_ctrl_request - Send a command to wpa_supplicant/hostapd
 * @ctrl: Control interface data from wpa_ctrl_open()
 * @cmd: Command; usually, ASCII text, e.g., "PING"
 * @cmd_len: Length of the cmd in bytes
 * @reply: Buffer for the response
 * @reply_len: Reply buffer length
 * @msg_cb: Callback function for unsolicited messages or %NULL if not used
 * Returns: 0 on success, -1 on error (send or receive failed), -2 on timeout
 *
 * This function is used to send commands to wpa_supplicant/hostapd. Received
 * response will be written to reply and reply_len is set to the actual length
 * of the reply. This function will block for up to two seconds while waiting
 * for the reply. If unsolicited messages are received, the blocking time may
 * be longer.
 *
 * msg_cb can be used to register a callback function that will be called for
 * unsolicited messages received while waiting for the command response. These
 * messages may be received if wpa_ctrl_request() is called at the same time as
 * wpa_supplicant/hostapd is sending such a message. This can happen only if
 * the program has used wpa_ctrl_attach() to register itself as a monitor for
 * event messages. Alternatively to msg_cb, programs can register two control
 * interface connections and use one of them for commands and the other one for
 * receiving event messages, in other words, call wpa_ctrl_attach() only for
 * the control interface connection that will be used for event messages.
 */
int wpa_ctrl_request(struct wpa_ctrl *ctrl, const char *cmd, size_t cmd_len,
		     char *reply, size_t *reply_len,
		     void (*msg_cb)(char *msg, size_t len));


/**
 * wpa_ctrl_attach - Register as an event monitor for the control interface
 * @ctrl: Control interface data from wpa_ctrl_open()
 * Returns: 0 on success, -1 on failure, -2 on timeout
 *
 * This function registers the control interface connection as a monitor for
 * wpa_supplicant/hostapd events. After a success wpa_ctrl_attach() call, the
 * control interface connection starts receiving event messages that can be
 * read with wpa_ctrl_recv().
 */
int wpa_ctrl_attach(struct wpa_ctrl *ctrl);


/**
 * wpa_ctrl_detach - Unregister event monitor from the control interface
 * @ctrl: Control interface data from wpa_ctrl_open()
 * Returns: 0 on success, -1 on failure, -2 on timeout
 *
 * This function unregisters the control interface connection as a monitor for
 * wpa_supplicant/hostapd events, i.e., cancels the registration done with
 * wpa_ctrl_attach().
 */
int wpa_ctrl_detach(struct wpa_ctrl *ctrl);


/**
 * wpa_ctrl_recv - Receive a pending control interface message
 * @ctrl: Control interface data from wpa_ctrl_open()
 * @reply: Buffer for the message data
 * @reply_len: Length of the reply buffer
 * Returns: 0 on success, -1 on failure
 *
 * This function will receive a pending control interface message. This
 * function will block if no messages are available. The received response will
 * be written to reply and reply_len is set to the actual length of the reply.
 * wpa_ctrl_recv() is only used for event messages, i.e., wpa_ctrl_attach()
 * must have been used to register the control interface as an event monitor.
 */
int wpa_ctrl_recv(struct wpa_ctrl *ctrl, char *reply, size_t *reply_len);


/**
 * wpa_ctrl_pending - Check whether there are pending event messages
 * @ctrl: Control interface data from wpa_ctrl_open()
 * Returns: Non-zero if there are pending messages
 *
 * This function will check whether there are any pending control interface
 * message available to be received with wpa_ctrl_recv(). wpa_ctrl_pending() is
 * only used for event messages, i.e., wpa_ctrl_attach() must have been used to
 * register the control interface as an event monitor.
 */
int wpa_ctrl_pending(struct wpa_ctrl *ctrl);


/**
 * wpa_ctrl_get_fd - Get file descriptor used by the control interface
 * @ctrl: Control interface data from wpa_ctrl_open()
 * Returns: File descriptor used for the connection
 *
 * This function can be used to get the file descriptor that is used for the
 * control interface connection. The returned value can be used, e.g., with
 * select() while waiting for multiple events.
 *
 * The returned file descriptor must not be used directly for sending or
 * receiving packets; instead, the library functions wpa_ctrl_request() and
 * wpa_ctrl_recv() must be used for this.
 */
int wpa_ctrl_get_fd(struct wpa_ctrl *ctrl);

#ifdef CONFIG_CTRL_IFACE_UDP
#define WPA_CTRL_IFACE_PORT 9877
#define WPA_GLOBAL_CTRL_IFACE_PORT 9878
#endif /* CONFIG_CTRL_IFACE_UDP */


#ifdef  __cplusplus
}
#endif

#endif /* WPA_CTRL_H */
