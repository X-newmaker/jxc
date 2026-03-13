/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_FFT_H_
#define INCLUDE_HAL_FFT_H_

#define FFT_STS_CUR_CMD_DNE			(0x1 << 0)
#define FFT_STS_NXT_CMD_DNE			(0x1 << 1)
#define FFT_STS_CMD_END				(0x1 << 2)
#define FFT_STS_AXI_BUS_ERR			(0x1 << 3)
#define FFT_STS_SAT_ERR				(0x1 << 4)
#define FFT_STS_NAN_ERR				(0x1 << 5)


#define FFT_SRAM_BASE0				0x30120000
#define FFT_SRAM_BASE1				0x30128000
#define FFT_SRAM_BASE2				0x30130000
#define FFT_SRAM_BASE3				0x30138000

#define FFT_SRAM512_BASE0			0x300A0000
#define FFT_SRAM512_BASE1			0x300A8000
#define FFT_SRAM512_BASE2			0x300B0000
#define FFT_SRAM512_BASE3			0x300B8000

typedef enum {
        SRAM_CPU    = 0,
        SRAM_FFT,
} FFT_SRAM_OWNER;

typedef enum {
		REALQ31    = 0,
		REALQ15,
		COMPQ31,
		COMPQ15,
} FFT_IND_TYP;

typedef enum {
		OUTQ31    = 0,
		OUTQ15,
		OUTQ31_,	//与OUTQ31一样
		OUTQ15_,	//与OUTQ15一样
} FFT_OUTD_TYP;

typedef enum {
        FIX_IN    = 0,
		FLOAT_CVR15,
		FLOAT_CVR31,
} FFT_FLOAT_IN_TYP;

typedef enum {
        FIX_OUT   = 0,
		Q15_CVR_FLOAT,
		Q31_CVR_FLOAT,
} FFT_FLOAT_OUT_TYP;

typedef enum {
		LEN8    = 0,
		LEN16,
		LEN32,
		LEN64,
		LEN128,
		LEN256,
		LEN512,
		LEN1024,
		LEN2048,
		LEN4096,
} FFT_LEN_TYP;

typedef enum {
		SRAM_B0    = 0,			//32KB 0x30138000 ~ 0x30140000
		SRAM_B0_B1,				//64KB 0x30130000 ~ 0x30140000
		SRAM_B0_B1_B2_B3,		//128KB 0x30120000 ~ 0x30140000
} FFT_SRAM_TYP;

union FFT_CTL_REG {
        volatile u32  all;
        struct {
        	volatile u32 CAL_EN: 1;				//0		PGA_EN
        	volatile u32 rsvd0: 30;				//30:1 Reserved
        	volatile u32 SFT_RST: 1;			//31	SFT_RST
        }bit;
};

union FFT_STS_REG {
        volatile u32  all;
        struct {
        	volatile u32 CUR_CMD_DNE: 1;		//0		CUR_CMD_DNE
        	volatile u32 NXT_CMD_DNE: 1;		//1		NXT_CMD_DNE
        	volatile u32 CMD_END: 1;			//2		CMD_END
        	volatile u32 AXI_BUS_ERR: 1;		//3		AXI_BUS_ERR
        	volatile u32 AXI_NXT_CMD_ERR: 1;	//4		AXI_NXT_CMD_ERR
        	volatile u32 FP_SAT_ERR: 1;			//5		FP_SAT_ERR
        	volatile u32 FP_NAN_ERR: 1;			//6		FP_NAN_ERR
        	volatile u32 rsvd0: 5;				//11:7	Reserved
        	volatile u32 CMD_SRAM_B0_DNE: 1;	//12	CMD_SRAM_B0_DNE
        	volatile u32 CMD_SRAM_B1_DNE: 1;	//13	CMD_SRAM_B1_DNE
        	volatile u32 CMD_SRAM_B2_DNE: 1;	//14	CMD_SRAM_B2_DNE
        	volatile u32 CMD_SRAM_B3_DNE: 1;	//15	CMD_SRAM_B3_DNE
        	volatile u32 CMD_DONE_CNT:8;		//23:16	CMD_DONE_CNT
        	volatile u32 rsvd1:8;				//31:24	Reserved
        }bit;
};

union FFT_INT_EN_REG {
        volatile u32  all;
        struct {
        	volatile u32 CUR_CMD_DNE_IE: 1;		//0		CUR_CMD_DNE
        	volatile u32 NXT_CMD_DNE_IE: 1;		//1		NXT_CMD_DNE
        	volatile u32 CMD_END_IE: 1;			//2		CMD_END
        	volatile u32 AXI_BUS_ERR_IE: 1;		//3		AXI_BUS_ERR
        	volatile u32 AXI_NXT_CMD_ERR_IE: 1;	//4		AXI_NXT_CMD_ERR
        	volatile u32 FP_SAT_ERR_IE: 1;		//5		FP_SAT_ERR
        	volatile u32 FP_NAN_ERR_IE: 1;		//6		FP_NAN_ERR
        	volatile u32 rsvd0: 5;				//11:7	Reserved
        	volatile u32 CMD_SRAM_B0_DNE_IE: 1;	//12	CMD_SRAM_B0_DNE
        	volatile u32 CMD_SRAM_B1_DNE_IE: 1;	//13	CMD_SRAM_B1_DNE
        	volatile u32 CMD_SRAM_B2_DNE_IE: 1;	//14	CMD_SRAM_B2_DNE
        	volatile u32 CMD_SRAM_B3_DNE_IE: 1;	//15	CMD_SRAM_B3_DNE
        	volatile u32 rsvd1:16;				//31:16	Reserved
        }bit;
};

union FFT_SRAM_CFG_REG {
        volatile u32  all;
        struct {
        	volatile u32 SRAM_B0_CFG: 1;		//0		SRAM_B0_CFG
        	volatile u32 SRAM_B1_CFG: 1;		//1		SRAM_B1_CFG
        	volatile u32 SRAM_B2_CFG: 1;		//2		SRAM_B2_CFG
        	volatile u32 SRAM_B3_CFG: 1;		//3		SRAM_B3_CFG
        	volatile u32 rsvd0: 28;				//31:4	Reserved
        }bit;
};

union FFT_OP_CTL_REG {
		volatile u32 all;
		struct {
			volatile u32 NXT_CMD_EN:1;			//0		NXT_CMD_EN
			volatile u32 rsvd0:1;				//1		Reserved
			volatile u32 NXT_CMD_ADDR:30;		//31:2	NXT_CMD_ADDR
		}bit;
};

union FFT_OP_CMD_REG {
		volatile u32 all;
		struct {
			volatile u32 FLOAT_IN_CVR:2;		//1:0	FLOAT_IN_CVR
			volatile u32 FLOAT_OUT_CVR:2;		//3:2	FLOAT_OUT_CVR
			volatile u32 IND_TYP:2;				//5:4	IND_TYP
			volatile u32 OUTD_TYP:2;			//7:6	OUTD_TYP
			volatile u32 ABS_OUT_EN:1;			//8		ABS_OUT_EN
			volatile u32 rsvd0:23;				//31:9	Reserved
		}bit;
};

union FFT_CFG_REG {
		volatile u32 all;
		struct {
			volatile u32 IFFT_EN:1;				//0		IFFT_EN
			volatile u32 rsvd0:3;				//3:1	Reserved
			volatile u32 FFT_LEN:4;				//7:4	FFT_LEN
			volatile u32 rsvd1:24;				//31:8	Reserved
		}bit;
};

struct FFT_REGS {
        union   FFT_CTL_REG        FFT_CTL;          //offset: 0x00
        union   FFT_STS_REG        FFT_STS;          //offset: 0x04
        union   FFT_INT_EN_REG     FFT_INT_EN;       //offset: 0x08
        volatile u32  RES0;						 	 //offset: 0x0C
        union	FFT_SRAM_CFG_REG   FFT_SRAM_CFG;	 //offset: 0x10
        volatile u32			   FFT_SRAM_BASE;	 //offset: 0x14
        volatile u32  RES1[14];						 //offset: 0x18~0x4C
        union   FFT_OP_CTL_REG     FFT_OP_CTL;       //offset: 0x50
        union   FFT_OP_CMD_REG     FFT_OP_CMD;       //offset: 0x54
        union   FFT_CFG_REG        FFT_CFG;          //offset: 0x58
        volatile u32			   FFT_INBUF;      	 //offset: 0x5C
        volatile u32			   FFT_OUTBUF;       //offset: 0x60
};

void fft_cmu_init(void);
void fft_sram_syscfg_en(void);
void fft_reset(void);
void fft_en(void);
u32 fft_get_irq_sts(void);
u32 fft_get_done_cnt(void);
void fft_clr_irq_sts(u32 clr_sts);
void fft_irq_enable(u32 irq_en);
void fft_sram_own_en(FFT_SRAM_TYP sram_type);
void fft_sram_own_dis(FFT_SRAM_TYP sram_type);
void fft_sram_baseaddr_set(u32 addr);
void nxt_cmd_en(void);
void nxt_cmd_dis(void);
void nxt_cmd_addr(u32 addr);

void abs_out_enable(u32 en);
void fft_outd_type(FFT_OUTD_TYP type);
void fft_ind_type (FFT_IND_TYP type);
void fft_float_out_cvr(FFT_FLOAT_OUT_TYP cvr);
void fft_float_in_cvr(FFT_FLOAT_IN_TYP cvr);

void ifft_en(void);
void ifft_dis(void);
void fft_len(FFT_LEN_TYP len);

void fft_inbuf(u32 addr);
void fft_outbuf(u32 addr);

#endif /* INCLUDE_HAL_PGA_H_ */
