/*
 * WPA Supplicant - NDIS event handling with ndisuio
 * Copyright (c) 2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef EVENT_NDISUIO_H
#define EVENT_NDISUIO_H

struct event_ndisuio_data;

/*
 * Initialisation/Deinit
 */
struct event_ndisuio_data * event_ndisuio_init(unsigned int server_port, 
					       void *drv_ctx);

void event_ndisuio_deinit(struct event_ndisuio_data *event_data);

#endif /* EVENT_NDISUIO_H */
