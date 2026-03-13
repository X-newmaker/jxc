/*
 * Copyright (c) 2023, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Wudehuang <dehuang.wu@artinchip.com>
 */

#ifndef __BL_IMAGE_H_
#define __BL_IMAGE_H_

#include "all_inc.h"

#define AIC_IMAGE_MAGIC 0x20434941	/* Magic is 'AIC ' */
#define AIC_PBP2_MAGIC  0x32504250	/* Magic is 'PBP2 ' */
#define AIC_PDAT_MAGIC  0x54414450	/* Magic is 'PDAT ' */

#define AIC_FW_BLOCK1_SIZ               256
#define AIC_FW_SIGN_ALGO_NONE           0
#define AIC_FW_SIGN_ALGO_RSA2048        1
#define AIC_FW_SIGN_ALGO_HMAC_SHA256    3

#define AIC_FW_ENCRYPT_ALGO_NONE        0
#define AIC_FW_ENCRYPT_ALGO_AES_CBC     1

struct image_header {
	/* Magic value, should be "AIC " */
	u32 magic;
	/* Image checksum value */
	u32 checksum;
	/* Image header version */
	u32 head_ver;
	/* Image size from start to end */
	u32 image_len;
	/* Fireware's version information: Anti-rollback version counter */
	u8  fwver_counter;
	u8  fwver_revision;
	u8  fwver_minor;
	u8  fwver_major;
	/* Loader binary's length */
	u32 loader_len;
	/* Loader should be loaded this address */
	u32 load_address;
	/* Loader's entry point */
	u32 entry_point;
	/* If Loader is signed by RSA, then specify the algorithm here */
	u32 sign_algo;
	/* If loader is encrypted, then specify the algorithm here */
	u32 encrypt_algo;
	/* The position of signature, offset from image start */
	u32 sign_data_offset;
	/* The length of signature */
	u32 sign_data_len;
	/* The position of public key used when sign this firmware, offset from
	 * image head. */
	u32 sign_key_offset;
	/* The public key length */
	u32 sign_key_len;
	/* If encryption algorithm is AES-CBC, then IV is required. */
	u32 iv_data_offset;
	/* The IV data length */
	u32 iv_data_len;
	/* Resource data offset, the resource content is image private data
	 * BROM don't care what is it.
	 */
	u32 priv_data_offset;
	/* Resource data length */
	u32 priv_data_len;
	u32 pbp_data_offset;
	/* Resource data length */
	u32 pbp_data_len;
	/* Padding header, make it is fit to 256 bytes. */
	//u8 padding[176];
};

struct aux_header {
	/* Magic value, should be "PBP "/"PDAT" */
	u32 magic;
	/* Image checksum value */
	u32 checksum;
	u32 head_ver;
	u32 sign_offset;
	u8 pad[16];
};

typedef int (*entry_func)(u32 boot_param, void *priv_addr, u32 priv_len);
typedef int (*pbp_entry)(u32 boot_param, void *priv_addr, u32 priv_len);

s32 image_verify_magic(u8 *fw_base, u32 magic);
s32 image_verify_checksum(u8 *fw_base, u32 size);
u32 image_calc_checksum(u8 *buf, u32 size);
u8 *image_move(u8 *fw);
s32 image_authentication(u8 *fw);
u32 image_get_fw_len(u8 *fw_base);
u32 image_get_aligned_loader_len(struct image_header *fw);
void *image_get_entry_point(u8 *fw_base);
void *image_get_load_address(u8 *fw_base);
void *image_get_private_data_addr(u8 *fw_base);
u32 image_get_private_data_len(u8 *fw_base);


#endif /* __BL_IMAGE_H_ */
