/*
 * WPA Supplicant - NDISUIO common functions
 * Copyright (c) 2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef NDISUIO_COMMON_H
#define NDISUIO_COMMON_H

#define MAX_NDIS_DEVICE_NAME_LEN 256

/* For Windows XP */
#ifndef NDISUIO_DEVICE_NAME
#define NDISUIO_DEVICE_NAME "\\\\.\\\\Ndisuio" 
#endif /* NDISUIO_DEVICE_NAME */

int ndisuio_common_init(void *drv_ctx);
void ndisuio_common_deinit(void);
HANDLE ndisuio_common_get_handle(void);
int ndisuio_common_bind_adapter(const char *ifname);
void ndisuio_common_enumerate_all(void);
WCHAR * ndisuio_common_bound_adapter_unicode_name_get(void);

#endif /* NDISUIO_COMMON_H */
