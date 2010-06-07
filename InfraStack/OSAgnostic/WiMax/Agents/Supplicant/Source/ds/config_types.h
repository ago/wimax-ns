/*
 * WPA Supplicant - eapol_test/RADIUS client defines
 * Copyright (c) 2003-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * All Rights Reserved.
 */

#ifndef CONFIG_TYPES_H
#define CONFIG_TYPES_H

struct hostapd_ip_addr {
	union {
		struct in_addr v4;
#ifdef CONFIG_IPV6
		struct in6_addr v6;
#endif /* CONFIG_IPV6 */
	} u;
	int af; /* AF_INET / AF_INET6 */
};

#endif /* CONFIG_TYPES_H */
