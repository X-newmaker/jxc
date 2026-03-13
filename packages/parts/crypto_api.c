/*
 * Copyright (c) 2020-2021 Artinchip Technology Co., Ltd. All rights reserved.
 *
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */
#include <ce_drv.h>
#include <crypto_api.h>
#include <secure.h>
#include "all_inc.h"
#include "aic_soc.h"

#define TAG "CE  "
#define cryptodbg printk

void gen_test_data(u8* out, u32 len, u32 start)
{
	u32 i;
	for (i = 0; i<len; i++) {
		out[i] = start % 256;
		start++;
	}
}

void gen_test_key(u8 *out, u32 len)
{
	gen_test_data(out, len, 128);
}
/*
 * Swap byte order in-place
 */
s32 bignum_byteswap(u8 *bn, u32 len)
{
	u32 i, j;
	u8 val;

	if (len == 0) {
		cryptodbg("Data length error, Dst len < Src len\n");
		return -1;
	}

	i = 0;
	j = len -1;

	while (i < j) {
		val = bn[i];
		bn[i] = bn[j];
		bn[j] = val;
		i++;
		j--;
	}
	return 0;
}

/* Big Number from little-endian to big-endian */
s32 bignum_le2be(u8 *src, u32 slen, u8 *dst, u32 dlen)
{
	int i;

	if (dlen < slen) {
		cryptodbg("Data length error, Dst len < Src len\n");
		return -1;
	}

	_memset(dst, 0, dlen);
	for (i = 0; i < slen; i++)
		dst[dlen - 1 - i] = src[i];

	return 0;
}

/* Big Number from big-endian to litte-endian */
s32 bignum_be2le(u8 *src, u32 slen, u8 *dst, u32 dlen)
{
	int i;

	if (dlen < slen) {
		cryptodbg("Data length error, Dst len < Src len\n");
		return -1;
	}

	_memset(dst, 0, dlen);
	for (i = 0; i < slen; i++)
		dst[i] = src[slen - 1 - i];

	return 0;
}


/*
 * This function can be used to perform rsa decrypt one block(256 byte) data.
 *
 * Verify:
 *	Use Public key to decrypt data
 */
static s32 _rsa_calc(u8 *din, u32 ilen, u8 *dout, u32 olen, u8 *mod, u32 mlen,
		     u8 *prime, u32 plen)
{
	u8 work_buf[256 * 4 + 2 * CACHE_LINE_SIZE];
	struct task_desc *task;
	u32 unit_len = mlen;
	u8 *src_buff;
	u8 *p_n, *p_prim, *p_data, *p_result;

	task = (void *)CACHE_ALIGN(work_buf);
	src_buff = (void *)CACHE_ALIGN((((u8*)task) + sizeof(*task)));

	/*
	 * Input operand format: [E/D, MOD, DATA],
	 * Eevery unit size is mlen
	 */
	p_prim = src_buff;
	p_n = p_prim + unit_len;
	p_data = p_n + unit_len;
	p_result = p_data + unit_len;

	/*
	 * Input key data should be Big-Endian,
	 * here translate to Little-Endian
	 */
	bignum_be2le(din, ilen, p_data, unit_len);
	bignum_be2le(mod, mlen, p_n, unit_len);
	bignum_be2le(prime, plen, p_prim, unit_len);

	_memset(task, 0, sizeof(struct task_desc));

	task->alg.rsa.alg_tag = ALG_RSA;

	if (mlen == 256)
		task->alg.rsa.op_siz = KEY_SIZE_2048;
	else if (mlen == 128)
		task->alg.rsa.op_siz = KEY_SIZE_1024;
	else
		return -1;

	task->alg.rsa.m_addr = PTR2U32(p_n);
	task->alg.rsa.d_e_addr = PTR2U32(p_prim);
	task->data.in_addr = PTR2U32(p_data);
	task->data.in_len = unit_len;
	task->data.out_addr = PTR2U32(p_result);
	task->data.out_len = unit_len;

	e907_dcache_flush_region(task, sizeof(*task));
	e907_dcache_flush_region(src_buff, 256 * 4);
	ce_set_task((PTR2U32(task)));

	ce_irq_enable(ALG_UNIT_ASYM);
	ce_ctrl_start(task->alg.alg_tag);
	ce_wait_finish(ALG_UNIT_ASYM);
	ce_pending_clear(ALG_UNIT_ASYM);

	if (ce_check_err(ALG_UNIT_ASYM))
		return -1;

	/*
	 * Result translate to Big-Endian
	 */
	bignum_le2be(p_result, unit_len, dout, unit_len);
	// bignum_byteswap(dout, unit_len);
	cryptodbg("check: stack overflow = 0x%x, %d\n", stack_overflow_check(), stack_used_size());
	return 0;
}

s32 ce_rsa_decrypt(u8 *din, u32 ilen, u8 *dout, u32 olen, u8 *mod, u32 mlen,
		   u8 *epub, u32 elen)
{
	return _rsa_calc(din, ilen, dout, olen, mod, mlen, epub, elen);
}

u32 ce_get_key_size(u32 key_len)
{
	u32 ret = 0xFFFFFFFF;

	switch (key_len) {
	case 8:
		ret = KEY_SIZE_64;
		break;
	case 16:
		ret = KEY_SIZE_128;
		break;
	case 24:
		ret = KEY_SIZE_192;
		break;
	case 32:
		ret = KEY_SIZE_256;
		break;
	}

	return ret;
}

#if 0
void dump_task(struct task_desc *task)
{
	printk("alg_tag   0x%08X\n", task->alg.aes_cbc.alg_tag);
	printk("direction 0x%08X\n", task->alg.aes_cbc.direction);
	printk("key src   0x%08X\n", task->alg.aes_cbc.key_src);
	printk("key siz   0x%08X\n", task->alg.aes_cbc.key_siz);
	printk("key addr  0x%08X\n", task->alg.aes_cbc.key_addr);
	printk("iv addr   0x%08X\n", task->alg.aes_cbc.iv_addr);
	printk("\n");
	printk("d.first   0x%08X\n", task->data.first_flag);
	printk("d.last    0x%08X\n", task->data.last_flag);
	printk("d.total   0x%08X\n", task->data.total_bytelen);
	printk("d.inaddr  0x%08X\n", task->data.in_addr);
	printk("d.in_len  0x%08X\n", task->data.in_len);
	printk("d.outaddr 0x%08X\n", task->data.out_addr);
	printk("d.out_len 0x%08X\n", task->data.out_len);
}
#endif

s32 ce_symm_run_task(struct task_desc *task)
{
	ce_set_task((PTR2U32(task)));

	ce_irq_enable(ALG_UNIT_SYMM);
	ce_ctrl_start(task->alg.alg_tag);
	ce_wait_finish(ALG_UNIT_SYMM);
	ce_pending_clear(ALG_UNIT_SYMM);

	if (ce_check_err(ALG_UNIT_SYMM)) {
		cryptodbg("CE got error 0x%x\n", ce_check_err(ALG_UNIT_SYMM));
		return -1;
	}

	return 0;
}

s32 ce_hash_run_task(struct task_desc *task)
{
	ce_set_task((PTR2U32(task)));

	ce_irq_enable(ALG_UNIT_HASH);
	ce_ctrl_start(task->alg.alg_tag);
	ce_wait_finish(ALG_UNIT_HASH);
	ce_pending_clear(ALG_UNIT_HASH);

	if (ce_check_err(ALG_UNIT_HASH)) {
		cryptodbg("CE got error 0x%x\n", ce_check_err(ALG_UNIT_HASH));
		return -1;
	}

	return 0;
}

s32 ce_sha256(u8 *in_data, u32 in_len, u8 *out_buf, u32 out_len)
{
	struct task_desc *task;
	u8 work_buf[2 * CACHE_LINE_SIZE];

	task = (void *)CACHE_ALIGN(work_buf);
	_memset(task, 0, sizeof(struct task_desc));

	task->alg.hash.alg_tag = ALG_SHA256;
	task->alg.hash.iv_mode = 0;
	task->data.last_flag = 1;
	task->data.total_bytelen = in_len;
	task->data.in_addr = PTR2U32(in_data);
	task->data.in_len= in_len;
	task->data.out_addr = PTR2U32(out_buf);
	task->data.out_len= out_len;

	e907_dcache_flush_region(task, sizeof(*task));
	return ce_hash_run_task(task);
}

s32 ce_md5(u8 *in_data, u32 in_len, u8 *out_buf, u32 out_len)
{
	struct task_desc *task;
	u8 work_buf[2 * CACHE_LINE_SIZE];

	task = (void *)CACHE_ALIGN(work_buf);
	_memset(task, 0, sizeof(struct task_desc));

	task->alg.hash.alg_tag = ALG_MD5;
	task->alg.hash.iv_mode = 0;
	task->data.last_flag = 1;
	task->data.total_bytelen = in_len;
	task->data.in_addr = PTR2U32(in_data);
	task->data.in_len= in_len;
	task->data.out_addr = PTR2U32(out_buf);
	task->data.out_len= out_len;

	e907_dcache_flush_region(task, sizeof(*task));
	return ce_hash_run_task(task);
}

static u32 sha256_iv[] = {
	0x6a09e667UL,
	0xbb67ae85UL,
	0x3c6ef372UL,
	0xa54ff53aUL,
	0x510e527fUL,
	0x9b05688cUL,
	0x1f83d9abUL,
	0x5be0cd19UL,
};
s32 ce_ssk_hmac_sha256(u8 *in_data, u32 in_len, u8 *out_buf, u32 out_len)
{
	struct task_desc *task;
	u8 work_buf[5 * 64];
	u8 *iv, *hmac_key, *proc_key, *out_code, i;
	s32 ret = 0;

	task = (void *)CACHE_ALIGN(work_buf);
	_memset(task, 0, sizeof(struct task_desc));

	iv = (void *)CACHE_ALIGN((u8 *)task + sizeof(*task));
	out_code = (void *)CACHE_ALIGN(iv + 32);
	hmac_key = (void *)CACHE_ALIGN(out_code + 32);
	proc_key = (void *)CACHE_ALIGN(hmac_key + 64);

	/* Calc HMAC Key */
	task->alg.aes_cbc.alg_tag = ALG_AES_ECB;
	task->alg.aes_cbc.direction = ALG_DIR_ENCRYPT;
	task->alg.aes_cbc.key_src = CE_KEY_SRC_SSK;
	task->alg.aes_cbc.key_siz = KEY_SIZE_128;

	/* In place decrypt */
	task->data.in_addr = PTR2U32(in_data);
	task->data.in_len = 64;
	task->data.out_addr = PTR2U32(hmac_key);
	task->data.out_len = 64;

	e907_dcache_clean_region(task, sizeof(*task));
	e907_dcache_clean_region(in_data, 64);

	ret = ce_symm_run_task(task);
	if (ret != 0) {
		cryptodbg("Generate HMAC key failed.\n");
		return -1;
	}
	e907_dcache_invalid_region(hmac_key, 64);

	/* HMAC key process */
	for (i = 0; i < 64; i++)
		proc_key[i] = hmac_key[i] ^ 0x36;

	/* Calc HMAC, part 1 */
	_memcpy(iv, sha256_iv, 32);
	for (i = 0; i < 8; i++) {
		bignum_byteswap(iv + i * 4, 4);
	}

	_memset(task, 0, sizeof(struct task_desc));

	task->alg.hash.alg_tag = ALG_HMAC_SHA256;
	task->alg.hash.iv_mode = 1;
	task->alg.hash.iv_addr = PTR2U32(iv);
	task->data.last_flag = 0;
	task->alg.hmac.hmac_key_addr = PTR2U32(hmac_key);
	task->data.total_bytelen = in_len + 64;
	task->data.in_addr = PTR2U32(proc_key);
	task->data.in_len= 64;
	task->data.out_addr = PTR2U32(out_code);
	task->data.out_len= out_len;

	e907_dcache_clean_region(task, sizeof(*task));
	e907_dcache_clean_region(iv, 32);
	e907_dcache_clean_region(hmac_key, 64);
	e907_dcache_clean_region(proc_key, 64);

	ret = ce_hash_run_task(task);
	if (ret != 0) {
		cryptodbg("Calc HMAC code part1 failed.\n");
		return -1;
	}
	e907_dcache_invalid_region(out_code, 32);
	_memcpy(iv, out_code, 32);

	/* Update info to calc part2 */
	task->data.last_flag = 1;
	task->data.in_addr = PTR2U32(in_data);
	task->data.in_len= in_len;

	e907_dcache_clean_region(iv, 32);
	e907_dcache_clean_region(in_data, in_len);
	ret = ce_hash_run_task(task);
	if (ret != 0) {
		cryptodbg("Calc HMAC code part2 failed.\n");
		return -1;
	}
	e907_dcache_invalid_region(out_code, 32);
	_memcpy(out_buf, out_code, 32);

	return 0;
}
