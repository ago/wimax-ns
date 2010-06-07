/*
 * RC4 stream cipher
 * Copyright (c) 2002-2005, Jouni Malinen <jkmaline@cc.hut.fi>
 * All Rights Reserved.
 */

#ifndef RC4_H
#define RC4_H

#ifdef __vxworks
/* FIXME: avoids a symbol clash with wl driver, but would be better
 * handled by downgrading all internal symbols to locals.
 */
#define rc4	_wpa_rc4
#endif

void rc4_skip(const u8 *key, size_t keylen, size_t skip,
	      u8 *data, size_t data_len);
void rc4(u8 *buf, size_t len, const u8 *key, size_t key_len);

#endif /* RC4_H */
