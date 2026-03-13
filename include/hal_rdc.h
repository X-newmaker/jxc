/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_RDC_H_
#define INCLUDE_HAL_RDC_H_

union RDC_CTL_REG {
	volatile u32 all;
	struct {
		volatile u32 RDC_EN:1;			//0
		volatile u32 RDC_DAT_MOD:1;		//1
		volatile u32 rsvd0:30;			//31:2
	}bit;
};

union RDC_IEN_REG {
	volatile u32 all;
	struct {
		volatile u32 RDC_DONE_IEN:1;		//0
		volatile u32 rsvd0:31;			//31:1
	}bit;
};

union RDC_STS_REG {
	volatile u32 all;
	struct {
		volatile u32 RDC_DONE:1;		//0
		volatile u32 rsvd0:31;			//31:1
	}bit;
};

union RDC_CAL_TRG_REG {
	volatile u32 all;
	struct {
		volatile u32 TRG_SET:1;			//0
		volatile u32 rsvd0:31;			//31:1
	}bit;
};

union RDC_USIN_OFF_REG {
	volatile u32 all;
	struct {
		volatile u32 USIN_OFF:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_UCOS_OFF_REG {
	volatile u32 all;
	struct {
		volatile u32 UCOS_OFF:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_USIN_G_REG {
	volatile u32 all;
	struct {
		volatile u32 USIN_G:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_UCOS_G_REG {
	volatile u32 all;
	struct {
		volatile u32 UCOS_G:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_USIN_PRE_REG {
	volatile u32 all;
	struct {
		volatile u32 USIN_PRE:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_UCOS_PRE_REG {
	volatile u32 all;
	struct {
		volatile u32 UCOS_PRE:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_THETA_SEC_REG {
	volatile u32 all;
	struct {
		volatile u32 THETA_SEC:3;		//2:0
		volatile u32 rsvd0:29;			//31:3
	}bit;
};

union RDC_THETA_RDC_REG {
	volatile u32 all;
	struct {
		volatile u32 THETA_RDC:12;		//11:0
		volatile u32 rsvd0:20;			//31:12
	}bit;
};

union RDC_REG_USIN_REG {
	volatile u32 all;
	struct {
		volatile u32 REG_USIN:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

union RDC_REG_UCOS_REG {
	volatile u32 all;
	struct {
		volatile u32 REG_UCOS:14;		//13:0
		volatile u32 rsvd0:18;			//31:14
	}bit;
};

struct RDC_REGS {
	union RDC_CTL_REG		RDC_CTL;			//offset: 0x0
	union RDC_IEN_REG		RDC_IEN;			//offset: 0x4
	union RDC_STS_REG		RDC_STS;			//offset: 0x8
	union RDC_CAL_TRG_REG	RDC_CAL_TRG;		//offset: 0xC
	volatile u32 RES0[4];						//offset: 0x10~0x1C
	union RDC_USIN_OFF_REG	RDC_USIN_OFF;		//offset: 0x20
	union RDC_UCOS_OFF_REG	RDC_UCOS_OFF;		//offset: 0x24
	volatile u32 RES1;							//offset: 0x28
	union RDC_USIN_G_REG	RDC_USIN_G;			//offset: 0x2C
	union RDC_UCOS_G_REG	RDC_UCOS_G;			//offset: 0x30
	volatile u32 RES2[3];						//offset: 0x34~0x3C
	union RDC_USIN_PRE_REG	RDC_USIN_PRE;		//offset: 0x40
	union RDC_UCOS_PRE_REG	RDC_UCOS_PRE;		//offset: 0x44
	volatile u32 RES3;							//offset: 0x48
	union RDC_THETA_SEC_REG	RDC_THETA_SEC;		//offset: 0x4C
	volatile u32 RES4[4];						//offset: 0x50~0x5C
	union RDC_THETA_RDC_REG	RDC_THETA_RDC;		//offset: 0x60
	volatile u32 RES5[3];						//offset: 0x64~0x6C
	union RDC_REG_USIN_REG	RDC_REG_USIN;		//offset: 0x70
	union RDC_REG_UCOS_REG	RDC_REG_UCOS;		//offset: 0x74
};

void rdc_cmu_init(void);
void rdc_adc_dat_mode(u8 mode);
void rdc_en(u8 en);
void rcd_cal_trg(void);
void rdc_usin_off_set(u32 set);
void rdc_ucos_off_set(u32 set);
void rdc_usin_gain_set(u32 set);
void rdc_ucos_gain_set(u32 set);
void rdc_usin_reg_set(u32 set);
void rdc_ucos_reg_set(u32 set);
u32 rdc_get_theta(void);

#endif /* INCLUDE_HAL_RDC_H_ */
