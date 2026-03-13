/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_PGA_H_
#define INCLUDE_HAL_PGA_H_

union PGA_CTL_REG {
        volatile u32  all;
        struct {
        	volatile u32 PGA_EN: 1;				//0		PGA_EN
        	volatile u32 PGA_INP_EN: 1;			//1		PGA_INP_EN
        	volatile u32 PGA_INN_EN: 1;			//2		PGA_INN_EN
        	volatile u32 PGA_IN_RES_EN: 1;		//3		PGA_IN_RES_EN
        	volatile u32 PGA_R1_EN: 1;			//4		PGA_R1_EN
        	volatile u32 PGA_R2_EN: 1;			//5		PGA_R2_EN
        	volatile u32 PGA_R4_EN: 1;			//6		PGA_R4_EN
        	volatile u32 PGA_FLT_EN: 1;			//7		PGA_RFLT_EN
        	volatile u32 PGA_OP_MOD: 1;			//8		PGA_OP_MOD
        	volatile u32 PGA_EN_ATB: 1;			//9		PGA_EN_ATB
        	volatile u32 PGA_VCM_EN: 1;			//10	PGA_VCM_EN
        	volatile u32 PGA_ATB_SEL: 2;		//12:11	PGA_ATB_SEL
        	volatile u32 rsvd0: 3;				//15:13 Reserved
        	volatile u32 PGA_N_CAL: 8;			//23:16	PGA_N_CAL
        	volatile u32 PGA_P_CAL: 8;			//31:24 PGA_P_CAL
        }bit;
};

union PGA_RES_SET_REG {
        volatile u32  all;
        struct {
        	volatile u32 PGA_R1_SET: 1;
        	volatile u32 rsvd0: 3;
        	volatile u32 PGA_R2_SET: 4;
        	volatile u32 rsvd1: 4;
        	volatile u32 PGA_R3_SET: 1;
        	volatile u32 rsvd2: 3;
        	volatile u32 PGA_R4_SET: 4;
        	volatile u32 rsvd3: 4;
        	volatile u32 PGA_RFLT_SET: 3;
        	volatile u32 rsvd4: 5;
        }bit;
};

union PGA_REF_CTL_REG {
        volatile u32  all;
        struct {
        	volatile u32 PGA0_REF_SEL: 1;
        	volatile u32 PGA1_REF_SEL: 1;
        	volatile u32 PGA2_REF_SEL: 1;
        	volatile u32 PGA3_REF_SEL: 1;
        	volatile u32 PGA_VCM_ATB_SEL: 2;
        	volatile u32 ENVCM_ATB: 1;
        	volatile u32 rsvd0: 25;
        }bit;
};

typedef struct PGA_REGS {
        union   PGA_CTL_REG        PGA0_CTL;          //offset: 0x00
        union   PGA_CTL_REG        PGA1_CTL;          //offset: 0x04
        union   PGA_CTL_REG        PGA2_CTL;          //offset: 0x08
        union   PGA_CTL_REG        PGA3_CTL;          //offset: 0x0C
        volatile u32  RES0[4];						   //offset: 0x10_0x1C
        union   PGA_RES_SET_REG    PGA0_RES_SET;      //offset: 0x20
        union   PGA_RES_SET_REG    PGA1_RES_SET;      //offset: 0x24
        union   PGA_RES_SET_REG    PGA2_RES_SET;      //offset: 0x28
        union   PGA_RES_SET_REG    PGA3_RES_SET;      //offset: 0x2C
        volatile u32  RES1[4];						   //offset: 0x30_0x3C
        union   PGA_REF_CTL_REG     PGA_REF_CTL;       //offset: 0x40
}pga_reg_t;

void pga_cmu_init(void);
void pga_en(u32 n, u32 en);
void pga_inp_en(u32 n, u32 en);
void pga_inn_en(u32 n, u32 en);
void pga_inres_en(u32 n, u32 en);
void pga_ncal_set(u32 n, u32 set);
void pga_pcal_set(u32 n, u32 set);
void pga_r1_en(u32 n, u32 en);
void pga_r2_en(u32 n, u32 en);
void pga_r4_en(u32 n, u32 en);
void pga_flt_en(u32 n, u32 en);
void pga_opmod_sel(u32 n, u32 sel);
void pga_vcm_en(u32 n, u32 en);
void pga_r1_set(u32 n, u32 set);
void pga_r2_set(u32 n, u32 set);
void pga_r3_set(u32 n, u32 set);
void pga_r4_set(u32 n, u32 set);
void pga_rflt_set(u32 n, u32 set);

#endif /* INCLUDE_HAL_PGA_H_ */
