/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_SDFM_H_
#define INCLUDE_HAL_SDFM_H_

#define SDFM0_IRQ_PEND                          (0x1 << 0)
#define SDFM1_IRQ_PEND                          (0x1 << 1)
#define SDFM2_IRQ_PEND                          (0x1 << 2)
#define SDFM3_IRQ_PEND                          (0x1 << 3)
        
#define SDFM_COMP_H_STS_PEND                    (0x1 << 0)
#define SDFM_COMP_L_STS_PEND                    (0x1 << 1)
#define SDFM_MOD_FAIL_STS_PEND                  (0x1 << 2)
#define SDFM_DAT_DONE_STS_PEND                  (0x1 << 3)
#define SDFM_FIFO_STS_PEND                      (0x1 << 4)
#define SDFM_FIFO_OF_STS_PEND                   (0x1 << 5)
#define SDFM_FIFO_EMPTY_STS_PEND                (0x1 << 6)

#define SDFM_COMP_H_IRQ_EN                      (0x1 << 0)
#define SDFM_COMP_L_IRQ_EN                      (0x1 << 1)
#define SDFM_MOD_FAIL_IRQ_EN                    (0x1 << 2)
#define SDFM_DAT_DONE_IRQ_EN                    (0x1 << 3)
#define SDFM_FIFO_IRQ_EN                        (0x1 << 4)
#define SDFM_FIFO_OF_IRQ_EN                     (0x1 << 5)
#define SDFM_FIFO_EMPTY_IRQ_EN                  (0x1 << 6)

typedef enum {
        SDFM_IN_MOD0    = 0,
        SDFM_IN_MOD1,
		SDFM_IN_MOD2,
        SDFM_IN_MOD3,
} SDFM_IN_MOD;

typedef enum {
        SINC1    = 0,
        SINC1_TYP,
        SINC2,
        SINC3,
} SINC_TYPE;

typedef enum {
        EWPM0_SDFM_SYNC    = 0,
        EWPM1_SDFM_SYNC,
        EWPM2_SDFM_SYNC,
        EWPM3_SDFM_SYNC,
        EWPM4_SDFM_SYNC,
        EWPM5_SDFM_SYNC,
        EWPM6_SDFM_SYNC,
        EWPM7_SDFM_SYNC,
        EWPM8_SDFM_SYNC,
        EWPM9_SDFM_SYNC,
        EWPM10_SDFM_SYNC,
        EWPM11_SDFM_SYNC,
} SDFM_SYNC_TYPE;

typedef enum {
        WIDTH_16    = 0,
        WIDTH_32,
} DAT_WIDTH_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union SDFM_GLB_EN_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SDFM0_EN:1;                        //0     SDFM0 Enable
                volatile u32 SDFM1_EN:1;                        //1     SDFM1 Enable
                volatile u32 SDFM2_EN:1;                        //2     SDFM2 Enable
                volatile u32 SDFM3_EN:1;                        //3     SDFM3 Enable     
                volatile u32 rsvd0:28;                          //31:4  Reserved
        }bit;
};

union SDFM_GLB_IRQ_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SDFM0_IRQ_STS:1;                   //0     SDFM0 IRQ Status
                volatile u32 SDFM1_IRQ_STS:1;                   //1     SDFM1 IRQ Status
                volatile u32 SDFM2_IRQ_STS:1;                   //2     SDFM2 IRQ Status
                volatile u32 SDFM3_IRQ_STS:1;                   //3     SDFM3 IRQ Status    
                volatile u32 rsvd0:28;                          //31:4  Reserved
        }bit;
};

union SDFM_CLK_SET_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SDFM0_CLK_SEL:1;                   //0     SDFM0_CLK_SEL
                volatile u32 SDFM1_CLK_SEL:1;                   //1     SDFM1_CLK_SEL
                volatile u32 SDFM2_CLK_SEL:1;                   //2     SDFM2_CLK_SEL
                volatile u32 SDFM3_CLK_SEL:1;                   //3     SDFM3_CLK_SEL
                volatile u32 SDFM0_CLK_OUT_EN:1;                //4     SDFM0_CLK_OUT_EN
                volatile u32 SDFM1_CLK_OUT_EN:1;                //5     SDFM0_CLK_OUT_EN
                volatile u32 SDFM2_CLK_OUT_EN:1;                //6     SDFM0_CLK_OUT_EN
                volatile u32 SDFM3_CLK_OUT_EN:1;                //7     SDFM0_CLK_OUT_EN
                volatile u32 SDFM_CLK_DIV_EN:1;                 //8     SDFM_CLK_DIV_EN
                volatile u32 rsvd1:7;                           //15:9  Reserved
                volatile u32 SDFM_CLK_DIV:8;                 	//23:16     SDFM_CLK_DIV
                volatile u32 SDFM0_CLK_IN_EN:1;                 //24     SDFM0_CLK_IN_EN
                volatile u32 SDFM1_CLK_IN_EN:1;                 //25     SDFM1_CLK_IN_EN
                volatile u32 SDFM2_CLK_IN_EN:1;                 //26     SDFM2_CLK_IN_EN
                volatile u32 SDFM3_CLK_IN_EN:1;                 //27     SDFM3_CLK_IN_EN
                volatile u32 rsvd2:4;                           //31:28  Reserved
        }bit;
};

union SDFM_SMP_SET_REG {
		volatile u32 all;
		struct {
				volatile u32 SDFM0_SMP_PH:4;					//3:0	SDFM0_SMP_PH_SET
				volatile u32 SDFM1_SMP_PH:4;					//7:4	SDFM1_SMP_PH_SET
				volatile u32 SDFM2_SMP_PH:4;					//11:8	SDFM2_SMP_PH_SET
				volatile u32 SDFM3_SMP_PH:4;					//15:12	SDFM3_SMP_PH_SET
				volatile u32 rsvd0:16;							//31:16	Reserved
		}bit;
};

union SDFM_FLG_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 COMP_H_FLG:1;                      //0     High Comparator Flag
                volatile u32 COMP_L_FLG:1;                      //1     Low Comparator Flag
                volatile u32 MOD_FAIL_FLG:1;                    //2     Modulator Fail Flag
                volatile u32 DAT_DONE_FLG:1;                    //3     Data Done Flag
                volatile u32 FIFO_FLG:1;                        //4     FIFO Flag
                volatile u32 FIFO_OF_FLG:1;                     //5     FIFO Overflow Flag
                volatile u32 FIFO_EMPTY_FLG:1;                  //6     FIFO_EMPTY_FLG
                volatile u32 COMP_HS_FLG:1;                     //7     High Comparator Flag
                volatile u32 COMP_LS_FLG:1;                     //8     Low Comparator Flag
                volatile u32 COMP_Z_FLG:1;						//9		Z Comparator Flag
                volatile u32 rsvd0:22;                          //31:10  Reserved
        }bit;
};

union SDFM_INT_EN_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 COMP_H_INT_EN:1;                   //0     High Comparator Interrupt Enableg
                volatile u32 COMP_L_INT_EN:1;                   //1     Low Comparator Interrupt Enable
                volatile u32 MOD_FAIL_INT_EN:1;                 //2     Modulator Fail Interrupt Enable
                volatile u32 DAT_DONE_INT_EN:1;                 //3     Data Done Interrupt Enable
                volatile u32 FIFO_INT_EN:1;                     //4     FIFO Interrupt Enable
                volatile u32 FIFO_OF_INT_EN:1;                  //5     FIFO Overflow Interrupt Enable
                volatile u32 FIFO_EMPTY_INT_EN:1;               //6     FIFO_EMPTY Interrupt Enable    
                volatile u32 COMP_HS_INT_EN:1;                  //7     High Comparator Interrupt Enable
                volatile u32 COMP_LS_INT_EN:1;                  //8     Low Comparator Interrupt Enable
                volatile u32 COMP_Z_INT_EN:1;					//9		Z Comparator Interrupt Enable
                volatile u32 rsvd0:22;                          //31:10  Reserved
        }bit;
};

union SDFM_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SDIN_MOD:2;                        //1:0   Serial Data Input Mode Set
                volatile u32 SDIN_CLK_INV:1;                    //2     Clock Input Invert
                volatile u32 SDIN_DAT_INV:1;                    //3     Data Input Invert
                volatile u32 SDIN_CLK_CAP:1;                    //4     SDIN_CLK_CAP
                volatile u32 rsvd0:3;                     		//7:5   Reserved
                volatile u32 SDIN_CLK_THR:8;                    //15:8  Clock Threshold
                volatile u32 rsvd1:16;                          //31:16 Reserved
        }bit;
};

union PSINC_OUT_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 DAT_OUT_WDTH:1;                    //0     Data Output Width
                volatile u32 DAT_OUT_SHIFT:5;                   //5:1   Data Shift Control
                volatile u32 rsvd0:26;                          //31:6  Reserved
        }bit;
};

union PSINC_SET_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 POSR:8;                            //7:0   PSINC Filter Oversampling Ratio
                volatile u32 PFEN:1;                            //8     PSINC Filter Enable
                volatile u32 PSINC_TYP:2;                       //10:9  PSINC Filter Type Set
                volatile u32 PSINC_SYNC_EN:1;                   //11    PSINC Filter Synchronous Enable
                volatile u32 SYNC_SRC_SEL:4;                    //15:12 PSINC Filter Synchronous Source Select
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union SSINC_TH_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 HLT:16;                            //15:0   High-level Threshold
                volatile u32 LLT:16;                            //31:16  Low-levl Threshold
        }bit;
};

union SSINC_SET_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SOSR:5;                            //4:0    SSINC Filter Oversampling Ratio
                volatile u32 SFEN:1;                            //5      SSINC Filter Enable
                volatile u32 SSINC_TYP:2;                       //7:6    SSINC Filter Type Set
                volatile u32 rsvd0:24;                          //31:8   Reserved
        }bit;
};

union SD_DAT_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 LDAT16:16;                         //15:0   Low 16-bit Data
                volatile u32 HDAT16:16;                         //31:16  High 16-bit Data
        }bit;
};

union FIFO_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 FIFO_EN:1;                         //0      FIFO Enable
                volatile u32 FIFO_FLUSH:1;                      //1      FIFO Flush
                volatile u32 FIFO_WAIT_SYNC:1;                  //2      FIFO Wait for SYNC
                volatile u32 FIFO_SYNC_CLR:1;                   //3      FIFO SYNC Clear
                volatile u32 DMA_EN:1;                          //4      DMA Enable
                volatile u32 rsvd0:3;                           //7:5    Reserved
                volatile u32 FIFO_RXTH:6;                        //13:8   FIFO Receive Threshold
                volatile u32 rsvd1:18;                          //31:14  Reserved
        }bit;
};

union SSINC_ZLT_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 ZLT:16;                            //15:0   zero-level Threshold
                volatile u32 rsvd0:16;                           //31:16  Reserved
        }bit;
};

struct SDFM_REGS {                       
        union   SDFM_GLB_EN_REG    GLB_EN;           //offset: 0x00                       
        union   SDFM_GLB_IRQ_REG   GLB_IRQ_STS;      //offset: 0x04
        union   SDFM_CLK_SET_REG   SDFM_CLK_SET;     //offset: 0x08
        volatile u32  RES0;                      	 //offset: 0x0C
        union	SDFM_SMP_SET_REG   SDFM_SMP_SET;	 //offset: 0x10
        volatile u32  RES1[11];                      //offset: 0x14~0x3C
                                                     //SDFM0 Register
        union   SDFM_FLG_REG       SDFM_FLG0;        //offset: 0x40  
        union   SDFM_INT_EN_REG    SDFM_INT_EN0;     //offset: 0x44
        union   SDFM_CTL_REG       SDFM_CTL0;        //offset: 0x48
        union   PSINC_OUT_REG      PSINC_OUT0;       //offset: 0x4C
        union   PSINC_SET_REG      PSINC_SET0;       //offset: 0x50  
        union   SSINC_TH_REG       SSINC_TH0;        //offset: 0x54
        union   SSINC_SET_REG      SSINC_SET0;       //offset: 0x58
        union   SD_DAT_REG         SD_DAT0;          //offset: 0x5C 
        union   FIFO_CTL_REG       FIFO_CTL0;        //offset: 0x60 
        volatile u32  RES2;                          //offset: 0x64 
        volatile u32               FIFO_DAT0;        //offset: 0x68
        volatile u32  RES3;							 //offset: 0x6C
        union   SSINC_TH_REG       SSINC_STH0;       //offset: 0x70
        union	SSINC_ZLT_REG	   SSINC_ZLT0;		 //offset: 0x74
        volatile u32  RES4[2];                       //offset: 0x78/7C
                                                     //SDFM1 Register
        union   SDFM_FLG_REG       SDFM_FLG1;        //offset: 0x80  
        union   SDFM_INT_EN_REG    SDFM_INT_EN1;     //offset: 0x84
        union   SDFM_CTL_REG       SDFM_CTL1;        //offset: 0x88
        union   PSINC_OUT_REG      PSINC_OUT1;       //offset: 0x8C
        union   PSINC_SET_REG      PSINC_SET1;       //offset: 0x90  
        union   SSINC_TH_REG       SSINC_TH1;        //offset: 0x94
        union   SSINC_SET_REG      SSINC_SET1;       //offset: 0x98
        union   SD_DAT_REG         SD_DAT1;          //offset: 0x9C 
        union   FIFO_CTL_REG       FIFO_CTL1;        //offset: 0xA0 
        volatile u32  RES5;                          //offset: 0xA4
        volatile u32               FIFO_DAT1;        //offset: 0xA8 
        volatile u32  RES6;                          //offset: 0xAC
        union   SSINC_TH_REG       SSINC_STH1;       //offset: 0xB0
        union	SSINC_ZLT_REG	   SSINC_ZLT1;		 //offset: 0xB4
        volatile u32  RES7[2];                       //offset: 0xB8/BC
                                                     //SDFM2 Register
        union   SDFM_FLG_REG       SDFM_FLG2;        //offset: 0xC0  
        union   SDFM_INT_EN_REG    SDFM_INT_EN2;     //offset: 0xC4
        union   SDFM_CTL_REG       SDFM_CTL2;        //offset: 0xC8
        union   PSINC_OUT_REG      PSINC_OUT2;       //offset: 0xCC
        union   PSINC_SET_REG      PSINC_SET2;       //offset: 0xD0  
        union   SSINC_TH_REG       SSINC_TH2;        //offset: 0xD4
        union   SSINC_SET_REG      SSINC_SET2;       //offset: 0xD8
        union   SD_DAT_REG         SD_DAT2;          //offset: 0xDC 
        union   FIFO_CTL_REG       FIFO_CTL2;        //offset: 0xE0 
        volatile u32  RES8;                          //offset: 0xE4
        volatile u32               FIFO_DAT2;        //offset: 0xE8 
        volatile u32  RES9;                          //offset: 0xEC
        union   SSINC_TH_REG       SSINC_STH2;       //offset: 0xF0
        union	SSINC_ZLT_REG	   SSINC_ZLT2;		 //offset: 0xF4
        volatile u32  RES10[2];                      //offset: 0xF8/FC
                                                     //SDFM3 Register
        union   SDFM_FLG_REG       SDFM_FLG3;        //offset: 0x100  
        union   SDFM_INT_EN_REG    SDFM_INT_EN3;     //offset: 0x104
        union   SDFM_CTL_REG       SDFM_CTL3;        //offset: 0x108
        union   PSINC_OUT_REG      PSINC_OUT3;       //offset: 0x10C
        union   PSINC_SET_REG      PSINC_SET3;       //offset: 0x110  
        union   SSINC_TH_REG       SSINC_TH3;        //offset: 0x114
        union   SSINC_SET_REG      SSINC_SET3;       //offset: 0x118
        union   SD_DAT_REG         SD_DAT3;          //offset: 0x11C 
        union   FIFO_CTL_REG       FIFO_CTL3;        //offset: 0x120 
        volatile u32  RES11;                          //offset: 0x124
        volatile u32               FIFO_DAT3;        //offset: 0x128
        volatile u32  RES12;                          //offset: 0x12C
        union   SSINC_TH_REG       SSINC_STH3;       //offset: 0x130
        union	SSINC_ZLT_REG	   SSINC_ZLT3;		 //offset: 0x134
};

void sdfm_irq_handler(void);
void sdfm_irq_register(cpu_irq_fun_t irqhandle);
void sdfm_irq_unregister(void);
void sdfm_cmu_init(void);
void sdfm_en(u8 num);
void sdfm_dis(u8 num);
void sdfm_mod_set(u8 num,SDFM_IN_MOD mod);
void sdfm_pinmux_init(u32 i);
void sdfm_psinc_set(u8 num,SINC_TYPE type, u32 osr);
void sdfm_ssinc_set(u8 num,SINC_TYPE type, u32 osr);
void sdfm_dat_inv_en(u8 num, u32 en);
void sdfm_clk_inv_en(u8 num, u32 en);
u32 sdfm_get_irq_sts(u8 num);
void sdfm_clr_irq_sts(u8 num, u32 clr_sts);
void sdfm_psinc_sync_set(u8 num, SDFM_SYNC_TYPE sync_src);
void sdfm_ssinc_set_llt(u8 num, u32 llt);
void sdfm_ssinc_set_hlt(u8 num, u32 hlt);
void sdfm_set_data_width(u8 num, DAT_WIDTH_TYPE type);
void sdfm_set_data_shift(u8 num, u32 shift);
u32 sdfm_get_data(u8 num);
u32 sdfm_get_fifo_data(u8 num);
void sdfm_fifo_en(u8 num, u32 en);
void sdfm_fifo_flush(u8 num);
void sdfm_set_fifo_rxth(u8 num, u32 rxth);
void sdfm_irq_en(u8 num, u32 irq_en);
void sdfm_clk_div(u32 div);
void sdfm_clk_out_en(u8 num);
void sdfm_clk_in_en(u8 num);
void sdfm_ssinc_set_sllt(u8 num, u32 llt);
void sdfm_ssinc_set_shlt(u8 num, u32 hlt);
void sdfm_ssinc_set_zlt(u8 num, u32 hlt);
void sdfm_smp_ph_set(u8 num,u32 smp);
void sdfm_fifo_wait_sync(u8 num, u32 en);
void sdfm_fifo_sync_clr(u8 num, u32 en);
#endif /* INCLUDE_HAL_SDFM_H_ */
