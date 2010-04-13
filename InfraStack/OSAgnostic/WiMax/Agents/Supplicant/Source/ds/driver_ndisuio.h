/*
 * WPA Supplicant - NDIS User I/O Ethernet driver interface for Win32
 * Copyright (c) 2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright (c) 2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef DRIVER_NDISUIO_H
#define DRIVER_NDISUIO_H

struct wpa_driver_ndisuio_data;

#include "wpa2defs.h"

void wpa_driver_ndisuio_event_connect(struct wpa_driver_ndisuio_data *drv);
void wpa_driver_ndisuio_event_disconnect(struct wpa_driver_ndisuio_data *drv);
void wpa_driver_ndisuio_event_media_specific(
	struct wpa_driver_ndisuio_data *drv,
	const u8 *data, size_t data_len);

#endif /* DRIVER_NDISUIO_H */
