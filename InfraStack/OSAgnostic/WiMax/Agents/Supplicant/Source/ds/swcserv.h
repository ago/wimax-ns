/*
 * WPA Supplicant - Secure Wireless Client Service for Windows (CE)
 * Copyright (c) 2005, Devicescape Software, Inc.
 * All Rights Reserved.
 */

#ifndef SWCSERV_H
#define SWCSERV_H

/*
 * DLL exports
 */

/* Service Init, Deinit */
__declspec(dllexport) UINT32 SWC_Init(UINT32 dwContext);
__declspec(dllexport) UINT32 SWC_Deinit(UINT32 dwContext);

/* Service IOCTL */
__declspec(dllexport) UINT32 SWC_IOControl(UINT32 dwOpen, UINT32 dwCode,
					  PBYTE pIn, UINT32 dwIn, PBYTE pOut,
					  UINT32 dwOut, UINT32 *pdwBytesWritten);

#endif /* SWCSERV_H */
