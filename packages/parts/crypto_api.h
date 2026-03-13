/*
 * Copyright (c) 2020-2021 Artinchip Technology Co., Ltd. All rights reserved.
 *
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */

#ifndef _CRYPTO_API_H_
#define _CRYPTO_API_H_
#include <secure.h>

s32 bignum_byteswap(u8 *bn, u32 len);
s32 bignum_le2be(u8 *src, u32 slen, u8 *dst, u32 dlen);
s32 bignum_be2le(u8 *src, u32 slen, u8 *dst, u32 dlen);

#endif /* _CRYPTO_API_H_ */
