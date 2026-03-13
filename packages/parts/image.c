/*
 * Copyright (c) 2020-2021 Artinchip Technology Co., Ltd. All rights reserved.
 *
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */

#include <image.h>
#include <secure.h>
#include "aic_soc.h"
#include "aic_common.h"

#define image_c_log printk
extern void sfud_hexdump(const u8 *ptr, u32 buflen);
#define TAG "IMAG"
s8 efuse_get_pll_fra0_flag(void)
{
	hal_efuse_init();
	u32 BROM_SECURE_data = 0; //����SD��������
	hal_efuse_read(1, &BROM_SECURE_data);

	return (BROM_SECURE_data >> 8)&0x1;
}

s8 efuse_get_secure_boot_flag(void)
{
	hal_efuse_init();
	u32 BROM_SECURE_data = 0; //����SD��������
	hal_efuse_read(1, &BROM_SECURE_data);

	return BROM_SECURE_data&0x1;
}

s8 efuse_get_encrypt_boot_flag(void)
{
	hal_efuse_init();
	u32 BROM_SECURE_data = 0; //����SD��������
	hal_efuse_read(1, &BROM_SECURE_data);

	return (BROM_SECURE_data >> 1)&0x1;
}


s8 efuse_get_image_checksum_flag(void)
{
	hal_efuse_init();
	u32 BROM_SECURE_data = 0; //����SD��������
	hal_efuse_read(1, &BROM_SECURE_data);

	return (BROM_SECURE_data >> 10)&0x1;
}

s32 image_verify_magic(u8 *fw_base, u32 magic)
{
	u32 fw_magic;

	_memcpy(&fw_magic, fw_base, 4);
	if (fw_magic == magic)
		return 0;

	return -1;;
}

u32 image_calc_checksum(u8 *buf, u32 size)
{
	u32 i, val, sum, rest, cnt;
	u8 *p;
	u32 *p32, *pe32;

#ifdef USE_DCE
	int ret = 0;
	u32 aligned;
	aligned = 1;
	if (((u32)buf) & 0x3)
		aligned = 0;
	if (size & 0x3)
		aligned = 0;
	if (efuse_get_image_hwchecksum_flag() && aligned) {
		dce_checksum_start(buf, size);
		ret = dce_checksum_wait();
		if (ret == 0)
			return dce_checksum_result();
		/* If DCE calculate error, use CPU calculate again */
	}
#endif
	p = buf;
	i = 0;
	sum = 0;
	cnt = size >> 2;

	if ((unsigned long)buf & 0x3) {
		for (i = 0; i < cnt; i++) {
			p = &buf[i * 4];
			val = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0];
			sum += val;
		}
	} else {
		p32 = (u32 *)buf;
		pe32 = p32 + cnt;
		while (p32 < pe32) {
			sum += *p32;
			p32++;
		}
	}

	/* Calculate not 32 bit aligned part */
	rest = size - (cnt << 2);
	p = &buf[cnt * 4];
	val = 0;
	for (i = 0; i < rest; i++)
		val += (p[i] << (i * 8));
	sum += val;

	return sum;
}

/*
 * This function is used to verify the firmware checksum value.
 *
 * When generating firmware checksum, algorithm is like this:
 * 1. Set firmware header's checksum field to 0
 * 2. Then calculate firmware's 32-bit add sum value
 * 3. checksum value is the invert of 32-bit add sum value
 *
 * When verify checksum
 * 1. Just calcuate 32-bit add sum value
 * 2. The value + 1 should be 0
 *
 * How to process non 32-bit aligned bytes: padding 0 bytes to make it aligned.
 */
s32 image_verify_checksum(u8 *fw_base, u32 size)
{
	u32 sum;

	//test_report_image_checksum(1);
	sum = image_calc_checksum(fw_base, size);
	if ((sum + 1) != 0) {
		image_c_log("sum is 0x%X\n", sum);
		return -1;;
	}
	return 0;
}

#define FW_NO_OVERLAP   0
#define FW_HEAD_OVERLAP 1
#define FW_TAIL_OVERLAP 2

static s32 __is_overlap(u8 *src_start, u8 *src_end, u8 *dest_start,
			  u8 *dest_end)
{
	if (src_end < dest_start)
		return FW_NO_OVERLAP;
	if (dest_end < src_start)
		return FW_NO_OVERLAP;
	// Overlap, check type
	if (dest_start < src_start)
		return FW_HEAD_OVERLAP;
	if (src_end < dest_end)
		return FW_TAIL_OVERLAP;

	return FW_NO_OVERLAP;
}

static s32 __is_sram_addr(u32 addr)
{
	/* TODO: add check here */
	return 1;
}

static u8 *__image_move(struct image_header *fw, u8 *fw_base)
{
	u8 *src_start;
	u8 *src_end;
	u8 *dest_start;
	u8 *dest_end;
	u8 *load_addr;
	s32 type = 0;
	u32 fw_len = 0;

	fw_len = fw->image_len;
	load_addr = (u8 *)fw->load_address;

	/* Maybe no need to move */
	if ((load_addr == NULL) || (fw_base == load_addr))
		return fw_base;
	/* Need to move case */
	src_start  = fw_base;
	dest_start = load_addr;
	src_end    = src_start + fw_len;
	dest_end   = dest_start + fw_len;
	type       = __is_overlap(src_start, src_end, dest_start, dest_end);
	if (type == FW_TAIL_OVERLAP) {
		/* Move from tail to head */
		while (src_end >= src_start) {
			*dest_end = *src_end;
			dest_end--;
			src_end--;
		}
	} else {
		_memcpy(dest_start, src_start, fw_len);
	}

	return dest_start;
}

u8 *image_move(u8 *fw_base)
{
	struct image_header fw;

	_memcpy(&fw, fw_base, sizeof(struct image_header));

	/* When secure boot is enabled, cannot move out the sram. */
	if (efuse_get_secure_boot_flag() && __is_sram_addr(fw.load_address) == 0)
		return NULL;

	return __image_move(&fw, fw_base);
}

s32 image_verify_md5(struct image_header *fw, u8 *fw_base)
{
	u8 *calc_md5;
	u8 work_buf[2 * CACHE_LINE_SIZE];
	u8 *img_md5;
	s32 ret;
	u32 md5_area_len;

	calc_md5 = (u8 *)CACHE_ALIGN(work_buf);
	/* MD5 area: HEAD2,DATA1,DATA2. Skip HEAD1(8Byte) */
	md5_area_len = fw->image_len - MD5_BYTE_LEN - 8;
	e907_dcache_clean_region(fw_base, CACHE_ALIGN(fw->image_len));
	ret = ce_md5(fw_base + 8, md5_area_len, calc_md5, MD5_BYTE_LEN);
	if (ret != 0) {
		image_c_log("Calculate image's MD5 failed.\n");
		return -1;;
	}
	e907_dcache_invalid_region(calc_md5, CACHE_LINE_SIZE);

	img_md5 = fw_base + fw->sign_data_offset;
	if (_memcmp(calc_md5, img_md5, MD5_BYTE_LEN)) {
		image_c_log("Image's MD5 is not correct.\n");
		return -1;;
	}
	return 0;
}

extern void ce_init(void);
static s32 __image_sign_verification(struct image_header *fw, u8 *fw_base)
{
	s32 ret = 0;
	u32 sign_area_len = 0;
	u8 *auth_code;
	u8 fw_sha256[SHA256_BYTE_LEN];

	ce_init();
	auth_code = fw_base + fw->sign_data_offset;
	sign_area_len = fw->image_len - SHA256_BYTE_LEN;
	e907_dcache_clean_region(fw_base, CACHE_ALIGN(sign_area_len));
	ret = ce_ssk_hmac_sha256(fw_base, sign_area_len, fw_sha256, SHA256_BYTE_LEN);
	if (ret != 0) {
		image_c_log("Calculate loader's HMAC SHA256 digest failed.\n");
		return -1;;
	}
	e907_dcache_invalid_region(fw_sha256, CACHE_LINE_SIZE);

	if (_memcmp(fw_sha256, auth_code, SHA256_BYTE_LEN) != 0) {
		image_c_log("Loader's hmac sha256 digest verification failed.\n");
		return -1;;
	}

	//test_report_sign_verify(1);
	return 0;
}

static s32 __image_aes_cbc_decryption(u8 *fw_base, u32 fw_len, u8 *iv_data)
{
	s32 ret = 0;
	u8 work_buf[3 * CACHE_LINE_SIZE];
	u8 *iv;
	struct task_desc *task;

	task = (void *)CACHE_ALIGN(work_buf);
	iv = (void *)CACHE_ALIGN((((u8*)task) + sizeof(*task)));
	_memset(task, 0, sizeof(*task));

	if (!fw_base) {
		image_c_log("%s, data is null.\n");
		return -1;;
	}
	if (!iv_data) {
		image_c_log("%s, iv is null.\n");
		return -1;;
	}
	_memcpy(iv, iv_data, AES128_KEY_LEN);
	task->alg.aes_cbc.alg_tag = ALG_AES_CBC;
	task->alg.aes_cbc.direction = ALG_DIR_DECRYPT;
	task->alg.aes_cbc.key_src = CE_KEY_SRC_SSK;
	task->alg.aes_cbc.key_siz = KEY_SIZE_128;
	task->alg.aes_cbc.iv_addr = PTR2U32(iv);

	/* In place decrypt */
	task->data.in_addr = PTR2U32(fw_base);
	task->data.in_len = fw_len;
	task->data.out_addr = PTR2U32(fw_base);
	task->data.out_len = fw_len;

	e907_dcache_clean_region(task, sizeof(*task));
	e907_dcache_clean_region(iv, CACHE_LINE_SIZE);
	e907_dcache_clean_region(fw_base, fw_len);

	ret = ce_symm_run_task(task);
	if (ret != 0) {
		image_c_log("Loader decryption failed.\n");
		return -1;;
	}
	//test_report_enc_boot(1);
	e907_dcache_invalid_region(fw_base, fw_len);
	return ret;
}

static s32 __loader_aes_cbc_decryption(struct image_header *fw, u8 *fw_base)
{
	u8 *loader;
	u32 loader_len;

	loader = fw_base + AIC_FW_BLOCK1_SIZ;

	/* Round up to 256 align */
	loader_len = ((fw->loader_len >> 8) << 8);
	if (fw->loader_len & 0xFF)
		loader_len += 0x100;

	return __image_aes_cbc_decryption(loader, loader_len, fw_base + fw->iv_data_offset);
}

s32 image_authentication(u8 *fw_base)
{
	s32 ret = 0;
	u32 signflag, encflag;
	struct image_header fw;

	//pat_goto(0xa1000101);
	_memcpy(&fw, fw_base, sizeof(struct image_header));

	signflag = 0;
	if (efuse_get_secure_boot_flag() || fw.sign_algo)
		signflag = 1;

	encflag = 0;
	if (efuse_get_encrypt_boot_flag() || fw.encrypt_algo)
		encflag = 1;

	if (!signflag) {
		if (efuse_get_image_checksum_flag()) {
			ret = image_verify_checksum(fw_base, fw.image_len);
			if (ret != 0) {
				image_c_log("Image check sum failed\n");
				ret = -1;
				goto out;
			}
			image_c_log("Image check sum OK\n");
		}

		/* Still need to check and decrypt image */
		goto decrypt;
	}

	/* Verify HMAC-SHA256 authentication code is required, then do it */
	if (fw.sign_algo != AIC_FW_SIGN_ALGO_HMAC_SHA256) {
		image_c_log("Fireware signature algo is not supportted.\n");
		ret = -1;
		goto out;
	}

	if (__image_sign_verification(&fw, fw_base) != 0) {
		image_c_log("Fireware signature verification failed.\n");
		ret = -1;
		goto out;
	}
	image_c_log("Fireware signature verification OK.\n");

decrypt:
	/* All is done, otherwise do decryption:
	 *  - If loader is not presence
	 *  - If loader is not encrypted
	 */
	if (!encflag || !fw.loader_len) {
		ret = 0;
		goto out;
	}

	/* Image is encrypted */
	if (fw.encrypt_algo != AIC_FW_ENCRYPT_ALGO_AES_CBC) {
		image_c_log("Fireware encyption algo is not supportted.\n");
		ret = -1;
		goto out;
	}

	if (__loader_aes_cbc_decryption(&fw, fw_base) != 0) {
		image_c_log("FSBL content decryption failed\n");
		ret = -1;
		goto out;
	}
	image_c_log("FSBL content decryption OK\n");

out:
	if (ret == 0) {
		/* Set KSR */
	}
	return ret;
}

void *image_get_load_address(u8 *fw_base)
{
	void *la = NULL;
	struct image_header fw;

	_memcpy(&fw, fw_base, sizeof(struct image_header));
	la = (void *)fw.load_address;

	return la;
}

void *image_get_entry_point(u8 *fw_base)
{
	void *ep = NULL;
	struct image_header fw;

	_memcpy(&fw, fw_base, sizeof(struct image_header));
	ep = (void *)fw.entry_point;

	return ep;
}

void *image_get_private_data_addr(u8 *fw_base)
{
	struct image_header fw;
	void *priv_addr = NULL;

	_memcpy(&fw, fw_base, sizeof(struct image_header));
	if (fw.priv_data_len)
		priv_addr = (void *)(fw_base + fw.priv_data_offset);
	return priv_addr;
}

u32 image_get_private_data_len(u8 *fw_base)
{
	struct image_header fw;

	if (fw_base == NULL)
		return 0;
	_memcpy(&fw, fw_base, sizeof(struct image_header));

	return fw.priv_data_len;
}

u32 image_get_fw_len(u8 *fw_base)
{
	struct image_header fw;

	if (fw_base == NULL)
		return 0;
	_memcpy(&fw, fw_base, sizeof(struct image_header));

	return fw.image_len;
}

u32 image_get_aligned_loader_len(struct image_header *fw)
{
	u32 loader_len;

	/* Round up to 256 align */
	loader_len = ((fw->loader_len >> 8) << 8);
	if (fw->loader_len & 0xFF)
		loader_len += 0x100;

	return loader_len;
}

s32 image_private_data_verify(u8 *priv_addr, u32 priv_len)
{
	struct aux_header priv_head;
	u32 sum, sign_area_len;
	u8 *auth_code;
	u8 fw_sha256[SHA256_BYTE_LEN];
	s32 ret = 0;

	if (priv_addr == NULL)
		return -1;;
	_memcpy(&priv_head, priv_addr, sizeof(struct aux_header));

	image_c_log("PDAT RAW: \n");
	sfud_hexdump(priv_addr, 32);
	if (priv_head.magic != AIC_PDAT_MAGIC) {
		image_c_log("Private Data header check failed.\n");
		return -1;;
	}

	/* Verify in the original place */
	if (efuse_get_secure_boot_flag()) {
		auth_code = priv_addr + priv_head.sign_offset;
		sign_area_len = priv_len - SHA256_BYTE_LEN;
		ret = ce_ssk_hmac_sha256(priv_addr, sign_area_len, fw_sha256,
					 SHA256_BYTE_LEN);
		if (ret != 0) {
			image_c_log("Calculate private data's HMAC SHA256 digest failed.\n");
			return -1;;
		}
		if (_memcmp(fw_sha256, auth_code, SHA256_BYTE_LEN) != 0) {
			image_c_log("Private data's hmac sha256 digest verification failed.\n");
			return -1;;
		}
		image_c_log("Private data hmac verify ok.\n");
	} else {
		sum = image_calc_checksum(priv_addr, priv_len);
		if ((sum + 1) != 0) {
			image_c_log("private sum is 0x%X\n", sum);
			return -1;;
		}
		image_c_log("Private data checksum ok.\n");
	}

	return 0;
}


