/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
/*
 * hal_cpm.h
 *
 */

#ifndef INCLUDE_HAL_CPM_H_
#define INCLUDE_HAL_CPM_H_

#define CPM_COH_SYNC_FLT			(0x1<<0)
#define CPM_COH_LT_SYNC				(0x1<<1)
#define CPM_COL_SYNC_FLT			(0x1<<2)
#define CPM_COL_LT_SYNC				(0x1<<3)

#define CPM_COH_LT_CLR				(0x1<<0)
#define CPM_COH_LT_SYNCCLR			(0x1<<2)
#define CPM_COL_LT_CLR				(0x1<<2)
#define CPM_COL_LT_SYNCCLR			(0x1<<3)

typedef enum {
		CPM_NO_OUT = 0,
        CPM_EPWM_OUT,
		CPM_GPIO_OUT,
        CPM_EPWM_GPIO_OUT,
} CPM_OUT_EN;

typedef enum {
		COL_ASYN = 0,
        COL_SYNC,
		COL_SYNC_FLT,
        COL_LT,
} CPM_OUT_SEL;

typedef enum {
		SRC_PGA0_OUT = 0,
		SRC_PGA1_OUT,
		SRC_PGA2_OUT,
		SRC_PGA3_OUT,
		SRC_GPIO,
} CPM_PIN_SEL;

typedef enum {
		SRC_REG = 0,
		SRC_RAMP,
} CPM_HDAC_SRC;
/***************************************************************************
                        Register Description
***************************************************************************/
union CPM_GLB_EN_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 CPM0_EN:1;						//0 CPM0 Enable
		volatile u32 CPM1_EN:1;						//1 CPM1 Enable
		volatile u32 rsvd0:30;						//31:2 Reserved
	}bit;
};

union CPM_GLB_IRQ_STS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 CPM0_COH_IRQ:1;				//0 CPM0_COH_IRQ
		volatile u32 CPM0_COL_IRQ:1;				//1 CPM0_COL_IRQ
		volatile u32 CPM1_COH_IRQ:1;				//2 CPM1_COH_IRQ
		volatile u32 CPM1_COL_IRQ:1;				//3 CPM1_COL_IRQ
		volatile u32 rsvd0:28;						//31:4 Reserved
	}bit;
};

union COMP_CTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 COMPH_NSRC:1;					//0 COMPH_NSRC
		volatile u32 COMPH_INV:1;					//1 COMPH_INV
		volatile u32 COH_PWM_SEL:2;					//3:2 COH_PWM_SEL
		volatile u32 COH_GPIO_SEL:2;				//5:4 COH_GPIO_SEL
		volatile u32 COH_LT_ASYNC_EN:1;				//6 COH_LT_ASYNC_EN
		volatile u32 HDAC_EN:1;						//7 HDAC_EN
		volatile u32 rsvd0:2;						//9:8 Reserved
		volatile u32 COMPH_EN:1;					//10 COMPH_EN
		volatile u32 COH_IRQ_SEL:2;					//12:11 COH_IRQ_SEL
		volatile u32 rsvd1:3;						//15:13 Reserved
		volatile u32 COMPL_NSRC:1;					//16 COMPL_NSRC
		volatile u32 COMPL_INV:1;					//17 COMPL_INV
		volatile u32 COL_PWM_SEL:2;					//19:18 COL_PWM_SEL
		volatile u32 COL_GPIO_SEL:2;				//21:20 COL_GPIO_SEL
		volatile u32 COL_LT_ASYNC_EN:1;				//22 COL_LT_ASYNC_EN
		volatile u32 LDAC_EN:1;						//23 LDAC_EN
		volatile u32 rsvd2:2;						//25:24 Reserved
		volatile u32 COMPL_EN:1;					//26 COMPL_EN
		volatile u32 COL_IRQ_SEL:2;					//28:27 COL_IRQ_SEL
		volatile u32 rsvd3:3;						//31:29 Reserved
	}bit;
};

union COMP_OUT_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 COH_IRQ_EN:1;					//0 COH_IRQ_EN
		volatile u32 COH_IRQ_MOD:1;					//1 COH_IRQ_MOD
		volatile u32 COH_IRQ_EDG:2;					//3:2 COH_IRQ_EDG
		volatile u32 COH_IRQ_LVL:1;					//4 COH_IRQ_LVL
		volatile u32 COH_GPIO_EN:1;					//5 COH_GPIO_EN
		volatile u32 COH_PWM_EN:1;					//6 COH_PWM_EN
		volatile u32 rsvd0:9;						//15:7 Reserved
		volatile u32 COL_IRQ_EN:1;					//16 COL_IRQ_EN
		volatile u32 COL_IRQ_MOD:1;					//17 COL_IRQ_MOD
		volatile u32 COL_IRQ_EDG:2;					//19:18 COL_IRQ_EDG
		volatile u32 COL_IRQ_LVL:1;					//20 COL_IRQ_LVL
		volatile u32 COL_GPIO_EN:1;					//21 COL_GPIO_EN
		volatile u32 COL_PWM_EN:1;					//22 COL_PWM_EN
		volatile u32 rsvd1:5;						//27:23 Reserved
		volatile u32 COHL_PWM_EN:1;					//28 COHL_PWM_EN
		volatile u32 COHL_GPIO_EN:1;				//29 COHL_GPIO_EN
		volatile u32 rsvd2:2;						//31:30 Reserved
	}bit;
};

union COMP_HYSCTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 COMPH_HYS_EN:3;				//2:0 COMPH_HYS_EN
		volatile u32 rsvd0:1;						//3 Reserved
		volatile u32 COMPL_HYS_EN:3;				//6:4 COMPL_HYS_EN
		volatile u32 rsvd1:1;						//7 Reserved
		volatile u32 COMP_IBIAS_EN:1;				//8 COMP_IBIAS_EN
		volatile u32 rsvd2:13;						//31:9 Reserved
	}bit;
};

union COMP_STS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 COH_SYNC_FLT:1;				//0 COH_SYNC_FLT
		volatile u32 COH_LT_SYNC:1;					//1 COH_LT_SYNC
		volatile u32 COL_SYNC_FLT:1;				//2 COL_SYNC_FLT
		volatile u32 COL_LT_SYNC:1;					//3 COL_LT_SYNC
		volatile u32 rsvd0:28;						//31:4 Reserved
	}bit;
};

union COMP_STS_CLR_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 COH_LT_CLR:1;					//0 COH_LT_CLR
		volatile u32 COH_LT_SYNCLR_EN:1;			//1 COH_LT_SYNCLR_EN
		volatile u32 COL_LT_CLR:1;					//2 COL_LT_CLR
		volatile u32 COL_LT_SYNCLR_EN:1;			//3 COL_LT_SYNCLR_EN
		volatile u32 rsvd0:28;						//31:4 Reserved
	}bit;
};

union COMP_DAC_CTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 HDAC_SRC:1;					//0 HDAC_SRC
		volatile u32 RAMP_LOAD_SEL:1;				//1 RAMP_LOAD_SEL
		volatile u32 DAC_LOAD_SEL:1;				//2 DAC_LOAD_SEL
		volatile u32 rsvd0:1;						//3 Reserved
		volatile u32 SYNC_SRC:4;					//7:4 SYNC_SRC
		volatile u32 rsvd1:24;						//31:8 Reserved
	}bit;
};

union DACH_VALS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 DACH_VALS:12;					//11:0 DACH_VALS
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

union DACH_VALA_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 DACH_VALA:12;					//11:0 DACH_VALA
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

union RAMP_MAX_REFA_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_MAX_REFA:16;				//15:0 RAMP_MAX_REFA
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union RAMP_MAX_REFS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_MAX_REFS:16;				//15:0 RAMP_MAX_REFS
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union RAMP_DEC_VALA_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_DEC_VALA:16;				//15:0 RAMP_DEC_VALA
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union RAMP_DEC_VALS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_DEC_VALS:16;				//15:0 RAMP_DEC_VALS
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union RAMP_DLYA_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_DLYA:16;					//15:0 RAMP_DLYA
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union RAMP_DLYS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_DLYS:16;					//15:0 RAMP_DLYS
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union RAMP_STS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 RAMP_STS:16;					//15:0 RAMP_STS
		volatile u32 rsvd0:16;						//31:16 Reserved
	}bit;
};

union DACL_VALS_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 DACL_VALS:12;					//11:0 DACL_VALS
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

union DACL_VALA_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 DACL_VALA:12;					//11:0 DACL_VALA
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

union LFIL_CTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 SAMP_WIN:6;					//5:0 SAMP_WIN
		volatile u32 THRESH:5;						//10:6 THRESH
		volatile u32 FIL_EN:1;						//11 FIL_EN
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

union LFIL_CLK_CTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 CLK_PRE_SCALE:10;				//9:0 CLK_PRE_SCALE
		volatile u32 rsvd0:22;						//31:10 Reserved
	}bit;
};

union HFIL_CTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 SAMP_WIN:6;					//5:0 SAMP_WIN
		volatile u32 THRESH:5;						//10:6 THRESH
		volatile u32 FIL_EN:1;						//11 FIL_EN
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

union HFIL_CLK_CTL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 CLK_PRE_SCALE:10;				//9:0 CLK_PRE_SCALE
		volatile u32 rsvd0:22;						//31:10 Reserved
	}bit;
};

union IN_SRC_SEL_REG {
	volatile u32 all;
	struct {										//bit description
		volatile u32 COMPH_P_EN:1;					//0		COMPH_P_EN
		volatile u32 COMPH_P_SEL:3;					//3:1	COMPH_P_SEL
		volatile u32 COMPL_P_EN:1;					//4		COMPL_P_EN
		volatile u32 COMPL_P_SEL:3;					//7:5	COMPL_P_SEL
		volatile u32 COMP_ATB_EN:1;					//8		COMP_ATB_EN
		volatile u32 COMP_ATB_SEL:3;				//11:9	COMP_ATB_SEL
		volatile u32 rsvd0:20;						//31:12 Reserved
	}bit;
};

struct CPM_REGS {
	union CPM_GLB_EN_REG		CPM_GLB_EN;			//offset: 0x00
	union CPM_GLB_IRQ_STS_REG	CPM_GLB_IRQ_STS;	//offset: 0x04
	volatile u32 RES0[2];                           //offset: 0x08~0x0C
	union COMP_CTL_REG			COMP_CTL0;			//offset: 0x10
	union COMP_OUT_REG			COMP_OUT0;			//offset: 0x14
	union COMP_HYSCTL_REG		COMP_HYSCTL0;		//offset: 0x18
	union COMP_STS_REG			COMP_STS0;			//offset: 0x1C
	union COMP_STS_CLR_REG		COMP_STS_CLR0;		//offset: 0x20
	union COMP_DAC_CTL_REG		COMP_DAC_CTL0;		//offset: 0x24
	union DACH_VALS_REG			DACH_VALS0;			//offset: 0x28
	union DACH_VALA_REG			DACH_VALA0;			//offset: 0x2C
	union RAMP_MAX_REFA_REG		RAMP_MAX_REFA0;		//offset: 0x30
	union RAMP_MAX_REFS_REG		RAMP_MAX_REFS0;		//offset: 0x34
	union RAMP_DEC_VALA_REG		RAMP_DEC_VALA0;		//offset: 0x38
	union RAMP_DEC_VALS_REG		RAMP_DEC_VALS0;		//offset: 0x3C
	union RAMP_DLYA_REG			RAMP_DLYA0;			//offset: 0x40
	union RAMP_DLYS_REG			RAMP_DLYS0;			//offset: 0x44
	union RAMP_STS_REG			RAMP_STS0;			//offset: 0x48
	union DACL_VALS_REG			DACL_VALS0;			//offset: 0x4C
	union DACL_VALA_REG			DACL_VALA0;			//offset: 0x50
	union LFIL_CTL_REG			LFIL_CTL0;			//offset: 0x54
	union LFIL_CLK_CTL_REG		LFIL_CLK_CTL0;		//offset: 0x58
	union HFIL_CTL_REG			HFIL_CTL0;			//offset: 0x5C
	union HFIL_CLK_CTL_REG		HFIL_CLK_CTL0;		//offset: 0x60
	volatile u32 RES1[3];							//offset: 0x64~0x6C
	union IN_SRC_SEL_REG		IN_SRC_SEL0;		//offset: 0x70
	volatile u32 RES2[39];                          //offset: 0x74~0x10C
	union COMP_CTL_REG			COMP_CTL1;			//offset: 0x110
	union COMP_OUT_REG			COMP_OUT1;			//offset: 0x114
	union COMP_HYSCTL_REG		COMP_HYSCTL1;		//offset: 0x118
	union COMP_STS_REG			COMP_STS1;			//offset: 0x11C
	union COMP_STS_CLR_REG		COMP_STS_CLR1;		//offset: 0x120
	union COMP_DAC_CTL_REG		COMP_DAC_CTL1;		//offset: 0x124
	union DACH_VALS_REG			DACH_VALS1;			//offset: 0x128
	union DACH_VALA_REG			DACH_VALA1;			//offset: 0x12C
	union RAMP_MAX_REFA_REG		RAMP_MAX_REFA1;		//offset: 0x130
	union RAMP_MAX_REFS_REG		RAMP_MAX_REFS1;		//offset: 0x134
	union RAMP_DEC_VALA_REG		RAMP_DEC_VALA1;		//offset: 0x138
	union RAMP_DEC_VALS_REG		RAMP_DEC_VALS1;		//offset: 0x13C
	union RAMP_DLYA_REG			RAMP_DLYA1;			//offset: 0x140
	union RAMP_DLYS_REG			RAMP_DLYS1;			//offset: 0x144
	union RAMP_STS_REG			RAMP_STS1;			//offset: 0x148
	union DACL_VALS_REG			DACL_VALS1;			//offset: 0x14C
	union DACL_VALA_REG			DACL_VALA1;			//offset: 0x150
	union LFIL_CTL_REG			LFIL_CTL1;			//offset: 0x154
	union LFIL_CLK_CTL_REG		LFIL_CLK_CTL1;		//offset: 0x158
	union HFIL_CTL_REG			HFIL_CTL1;			//offset: 0x15C
	union HFIL_CLK_CTL_REG		HFIL_CLK_CTL1;		//offset: 0x160
	volatile u32 RES3[3];							//offset: 0x164~0x16C
	union IN_SRC_SEL_REG		IN_SRC_SEL1;		//offset: 0x170
};

void cpm_irq_handler(void);
void cpm_irq_register(cpu_irq_fun_t irqhandle);
void cpm_irq_unregister(void);
void cpm_cmu_init(void);
void cpm_enable(u8 n);
void cpm_disable(u8 n);
u32 cpm_irq_sts();
void cpm_irq_sts_clr(u32 sts);
void cpm_comph_en(u8 n,u8 en);
void cpm_compl_en(u8 n,u8 en);
void cpm_comph_nsrc(u8 n,u8 src);
void cpm_compl_nsrc(u8 n,u8 src);
void cpm_hdac_en(u8 n,u8 en);
void cpm_ldac_en(u8 n,u8 en);
void cpm_cohl_out(u8 n,CPM_OUT_EN out);
void cpm_coh_out(u8 n,CPM_OUT_EN out);
void cpm_col_out(u8 n,CPM_OUT_EN out);
void cpm_set_dach_val(u8 n, u32 val);
void cpm_set_dacl_val(u8 n, u32 val);
void cpm_set_rampmax_val(u8 n, u32 val);
void cpm_set_rampdce_val(u8 n, u32 val);
void cpm_set_rampdly_val(u8 n, u32 val);
void cpm_lfil_ctl(u8 n,u8 en,u32 thr,u32 win);
void cpm_hfil_ctl(u8 n,u8 en,u32 thr,u32 win);
void cpm_hysctl(u8 n,u32 ibias,u32 lhys,u32 hhys);
void coh_pwmout_sel(u8 n,CPM_OUT_SEL sel);
void coh_gpioout_sel(u8 n,CPM_OUT_SEL sel);
void coh_irq_source(u8 n,CPM_OUT_SEL sel);
void col_pwmout_sel(u8 n,CPM_OUT_SEL sel);
void col_gpioout_sel(u8 n,CPM_OUT_SEL sel);
void col_irq_source(u8 n,CPM_OUT_SEL sel);
void col_irq_en(u8 n,u8 en);
void coh_irq_en(u8 n,u8 en);
void coh_p_sel(u8 n,CPM_PIN_SEL sel);
void col_p_sel(u8 n,CPM_PIN_SEL sel);
void cpm_atb_sel(u8 n,u32 sel);
void coh_dac_src(u8 n,CPM_HDAC_SRC src);
void coh_ramp_ldsrc(u8 n,u32 ldsrc);
void coh_dac_ldsrc(u8 n,u32 ldsrc);
void coh_ramp_synsrc(u8 n,u32 synsrc);
void coh_lt_clr(u8 n);
void col_lt_clr(u8 n);
void coh_lt_syncclr_en(u8 n, u32 en);
void col_lt_syncclr_en(u8 n, u32 en);
u32 cpm_get_sts(u8 n);
void coh_inv_en(u8 n,u32 en);
void col_inv_en(u8 n,u32 en);
#endif /* INCLUDE_HAL_CPM_H_ */
