/*
 * Copyright (c) 2020-2021 Artinchip Technology Co., Ltd. All rights reserved.
 *
 * Dehuang Wu <dehuang.wu@artinchip.com>
 */
#ifndef _SECURE_H_
#define _SECURE_H_
#include "all_inc.h"

#define CACHE_ALIGN(addr) ((u32)((addr) + 31) & ~(u32)31)

#define RSA2048_SIGN_LEN 256
#define RSA2048_KEY_LEN  256
#define SHA256_BYTE_LEN  32
#define MD5_BYTE_LEN  16
#define AES128_KEY_LEN 16
#define DES64_KEY_LEN 8

#define SHA1_BLOCK_SIZE   64

#define ALG_UNIT_SYMM         (0)
#define ALG_UNIT_HASH         (1)
#define ALG_UNIT_ASYM         (2)

#define ALG_DIR_ENCRYPT        (0)
#define ALG_DIR_DECRYPT        (1)

#define ALG_AES_ECB           (0x00)
#define ALG_AES_CBC           (0x01)
#define ALG_AES_CTR           (0x02)
#define ALG_AES_XTS           (0x03)
#define ALG_AES_CTS           (0x04)
#define ALG_DES_ECB           (0x10)
#define ALG_DES_CBC           (0x11)
#define ALG_TDES_ECB          (0x20)
#define ALG_TDES_CBC          (0x21)
#define ALG_RSA               (0x30)
#define ALG_SHA1              (0x40)
#define ALG_SHA224            (0x41)
#define ALG_SHA256            (0x42)
#define ALG_SHA384            (0x43)
#define ALG_SHA512            (0x44)
#define ALG_MD5               (0x45)
#define ALG_HMAC_SHA1         (0x46)
#define ALG_HMAC_SHA256       (0x47)
#define ALG_TRNG              (0x50)

#define CTR_BIT_WIDTH_16       (0)
#define CTR_BIT_WIDTH_32       (1)
#define CTR_BIT_WIDTH_64       (2)
#define CTR_BIT_WIDTH_128      (3)

#define KEY_SIZE_64            (0x00)
#define KEY_SIZE_128           (0x01)
#define KEY_SIZE_192           (0x02)
#define KEY_SIZE_256           (0x03)
#define KEY_SIZE_512           (0x04)
#define KEY_SIZE_1024          (0x05)
#define KEY_SIZE_2048          (0x06)

/*
 * Key source
 *   - User input key(RAM or Secure SRAM)
 *   - eFuse key
 */
#define CE_KEY_SRC_USER        (0)
#define CE_KEY_SRC_SSK         (1)
#define CE_KEY_SRC_HUK         (2)
#define CE_KEY_SRC_PNK         (3)
#define CE_KEY_SRC_PSK0       (4)
#define CE_KEY_SRC_PSK1       (5)
#define CE_KEY_SRC_PSK2       (6)
#define CE_KEY_SRC_PSK3       (7)

#define uaddr u64
#define PTR2U32(ptr) ((u32)(uaddr)(ptr))

struct aes_ecb_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 7; /* bit[15:9] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u8  r2[28];        /* Pad to 36 bytes */
};

struct aes_cbc_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 7; /* bit[15:9] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u32 iv_addr;
	u8  r2[24];        /* Pad to 36 bytes */
};

/*
 * CTS-CBC-CS3(Kerberos)
 */
struct aes_cts_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 7; /* bit[15:9] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u32 iv_addr;
	u8  r2[24];        /* Pad to 36 bytes */
};

struct aes_ctr_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 5; /* bit[13:9] */
	u32 ctr_width : 2; /* bit[15:14] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u32 ctr_in_addr;
	u32 ctr_out_addr;
	u8  r2[20];        /* Pad to 36 bytes */
};

struct aes_xts_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 7; /* bit[15:9] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u32 tweak_addr;
	u8  r2[24];        /* Pad to 36 bytes */
};

struct des_ecb_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 7; /* bit[15:9] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u8  r2[28];        /* Pad to 36 bytes */
};

struct des_cbc_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 direction : 1; /* bit[8] */
	u32 r0        : 7; /* bit[15:9] */
	u32 key_src   : 4; /* bit[19:16] */
	u32 key_siz   : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 key_addr;
	u32 iv_addr;
	u8  r2[24];        /* Pad to 36 bytes */
};

struct rsa_alg_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 r0        : 12;/* bit[19:8] */
	u32 op_siz    : 4; /* bit[23:20] */
	u32 r1        : 8; /* bit[31:24] */
	u32 m_addr;
	u32 d_e_addr;
	u8  r2[24];        /* Pad to 36 bytes */
};

struct hash_alg_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 r0        : 1; /* bit[8] */
	u32 iv_mode   : 1; /* bit[9] */
	u32 r1        : 22;/* bit[31:10] */
	u32 hmac_key_addr;
	u32 iv_addr;
	u8  r2[24];        /* Pad to 36 bytes */
};

struct trng_alg_desc {
	u32 alg_tag   : 8; /* bit[7:0] */
	u32 r1        : 24;/* bit[31:8] */
	u8  r2[32];        /* Pad to 36 bytes */
};

union alg_desc {
	u8 alg_tag;
	struct aes_ecb_desc aes_ecb;
	struct aes_cbc_desc aes_cbc;
	struct aes_ctr_desc aes_ctr;
	struct aes_cts_desc aes_cts;
	struct aes_xts_desc aes_xts;
	struct des_ecb_desc des_ecb;
	struct des_cbc_desc des_cbc;
	struct rsa_alg_desc rsa;
	struct hash_alg_desc hash;
	struct hash_alg_desc hmac;
	struct trng_alg_desc trng;
};

struct data_desc {
	u32 first_flag  : 1; /* bit[0] */
	u32 last_flag   : 1; /* bit[1] */
	u32 r1          : 30;/* bit[31:2] */
	u32 total_bytelen;
	u32 in_addr;
	u32 in_len;
	u32 out_addr;
	u32 out_len;
};

struct task_desc {
	union alg_desc alg;
	struct data_desc data;
	u32 next;
};

void ce_init(void);
void ce_exit(void);

/*
 * Calculate input data's SHA-256 hash value.
 *
 * Parameters highlight:
 *  - in_len is valid data length, not buffer length.
 *  - out_buf should be 32.
 */
s32 ce_sha256(u8 *in_data, u32 in_len, u8 *out_buf, u32 out_len);

/*
 * Calculate input data's MD5 hash value.
 *
 * Parameters highlight:
 *  - in_len is valid data length, not buffer length.
 *  - out_buf should be 16.
 */
s32 ce_md5(u8 *in_data, u32 in_len, u8 *out_buf, u32 out_len);

s32 ce_ssk_hmac_sha256(u8 *in_data, u32 in_len, u8 *out_buf, u32 out_len);

/*
 * Get public key from DER format key file.
 *
 * Parameters highlight:
 *  - der: DER data buffer
 *  - n_addr: Public key's modulus address in DER data buffer
 *  - e_addr: Public exponent address in DER data buffer
 */
s32 rsa_pk_get_value(u8 *der, u32 *n_addr, u32 *n_len, u32 *e_addr, u32 *e_len);

/*
 * Use RSA public key to decrypt one block size data(Digest signature).
 *
 * Only support to decrypt one block(256 Byte) data, so input data size and
 * output buffer size should be 256.
 *
 * For BROM case:
 *   This API only used to decrypt digest signature, and the digest content
 *   locale at last 32 bytes in the decryption output. It is defined by openssl
 *   and RFC-8017.
 *
 * Parameters highlight:
 *  - ilen: digest signature data length, should be 256
 *  - olen: output buffer size, should be 256
 *  - n_mod: public key's modulus
 *  - e_pub: public exponent
 */
s32 ce_rsa_decrypt(u8 *din, u32 ilen, u8 *dout, u32 olen, u8 *n_mod, u32 n_len,
		   u8 *e_pub, u32 e_len);
u32 ce_get_key_size(u32 key_len);
s32 ce_symm_run_task(struct task_desc *task);
s32 ce_hash_run_task(struct task_desc *task);
#endif

