/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_ADC_H_
#define INCLUDE_HAL_ADC_H_

#define ADC_Q1_DONE_STS         0x1
#define ADC_Q2_DONE_STS        (0x1<<4)
#define ADC_QN_DONE_STS         0x1

#define ADC_WDG0_HIL_STS        0x1
#define ADC_WDG0_LOL_STS        (0x1<<1)
#define ADC_WDG0_PZD_STS        (0x1<<2)
#define ADC_WDG0_NZD_STS        (0x1<<3)
#define ADC_WDG1_HIL_STS        (0x1<<8)
#define ADC_WDG1_LOL_STS        (0x1<<9)
#define ADC_WDG1_PZD_STS        (0x1<<10)
#define ADC_WDG1_NZD_STS        (0x1<<11)
#define ADC_WDG2_HIL_STS        (0x1<<16)
#define ADC_WDG2_LOL_STS        (0x1<<17)
#define ADC_WDG2_PZD_STS        (0x1<<18)
#define ADC_WDG2_NZD_STS        (0x1<<19)

#define ADC0_Q1FDR			(BASE_ADC0 + 0x40)
#define ADC0_Q2FDR			(BASE_ADC0 + 0x80)
#define ADC1_Q1FDR			(BASE_ADC1 + 0x40)
#define ADC1_Q2FDR			(BASE_ADC1 + 0x80)

typedef enum {
        PS_DISABLE = 0,
        PS_ENABLE,
} PS_EN;

typedef enum {
        PA0 = 0,
        PA1,
        PA2,
        PA3,
        PA4,
        PA5,
        PA6,
        PA7,
        PA8,
        PA9,
        PA10,
        PA11,
        PA12,
        PA13,
        PA14,
        PA15,
} PA_PINNO_TYPE;

typedef enum {
        SMP_RATE_1MHZ = 0,
        SMP_RATE_500KHZ,
        SMP_RATE_320KHZ,
		SMP_RATE_2MHZ,
} ADC_SMP_RATE_TYPE;

typedef enum {
        SMP_1_NODE = 0,
        SMP_2_NODE,
        SMP_3_NODE,
        SMP_4_NODE,
        SMP_5_NODE,
        SMP_6_NODE,
        SMP_7_NODE,
        SMP_8_NODE,
        SMP_9_NODE,
        SMP_10_NODE,
        SMP_11_NODE,
        SMP_12_NODE,
        SMP_13_NODE,
        SMP_14_NODE,
        SMP_15_NODE,
        SMP_16_NODE,
} ADC_SMP_NUM_TYPE;

typedef enum {
        ADCCH0 = 0,
        ADCCH1,
        ADCCH2,
        ADCCH3,
        ADCCH4,
        ADCCH5,
        ADCCH6,
        ADCCH7,
        ADCCH8,
        ADCCH9,
        ADCCH10,
        ADCCH11,
        ADCCH12,
        ADCCH13,
        ADCCH14,
        ADCCH15,
        ADCCH16,
        ADCCH17,
        ADCCH18,
        ADCCH19,
        ADCCH20,
        ADCCH21,
        ADCCH22,
        ADCCH23,
		ADC_CH_PGA0 = 0x18,
		ADC_CH_PGA1 = 0x19,
		ADC_CH_PGA2 = 0x1A,
		ADC_CH_PGA3 = 0x1B,
		ADC_CH_TS0_VS0 = 0x20,
		ADC_CH_TS1_VS1 = 0x21,
		ADC_CH_TS2_VS2 = 0x22,
		ADC_CH_TS3_VS3 = 0x23,
} ADC_CHSEL_TYPE;

typedef enum {
        SINGLE_P = 0,
        DUAL_P,
        CROSS_DUAL,
} ADC_HCL_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union ADC_MCR_REG {
        volatile u32  all;
        struct {
                volatile u32 EN:1;
                volatile u32 QUE_COMB:1;
                volatile u32 QUE_OVR:1;
                volatile u32 ADC_SMP_SYC_EN:1;
                volatile u32 rsvd0:4;
                volatile u32 ADC_ACQ:8;
                volatile u32 Q1_RST:1;
                volatile u32 Q1_INTM:1;
                volatile u32 Q1_INTE:1;
                volatile u32 rsvd1:1;
                volatile u32 Q1_TRIGA:1;
                volatile u32 Q1_TRIGE:1;
                volatile u32 Q1_TRIGS:1;
                volatile u32 QC_TRIGB:1;
                volatile u32 Q2_RST:1;
                volatile u32 Q2_INTM:1;
                volatile u32 Q2_INTE:1;
                volatile u32 rsvd2:1;
                volatile u32 Q2_TRIGB:1;
                volatile u32 rsvd3:1;
                volatile u32 Q2_TRIGS:1;
                volatile u32 rsvd4:1;
        }bit;
};

union ADC_TCR_REG {
        volatile u32  all;
        struct {
                volatile u32 Q1_TRIG_CNT:8;
                volatile u32 Q2_TRIG_CNT:8;
                volatile u32 rsvd0:16;
        }bit;
};

union ADC_NODE1_REG {
        volatile u32  all;
        struct {
                volatile u32 Q1_NODE0:8;
                volatile u32 Q1_NODE1:8;
                volatile u32 Q1_NODE2:8;
                volatile u32 Q1_NODE3:8;
        }bit;
};

union ADC_NODE1A_REG {
        volatile u32  all;
        struct {
                volatile u32 Q1_NODE4:8;
                volatile u32 Q1_NODE5:8;
                volatile u32 Q1_NODE6:8;
                volatile u32 Q1_NODE7:8;
        }bit;
};

union ADC_NODE1B_REG {
        volatile u32  all;
        struct {
                volatile u32 Q1_NODE8:8;
                volatile u32 Q1_NODE9:8;
                volatile u32 Q1_NODE10:8;
                volatile u32 Q1_NODE11:8;
        }bit;
};

union ADC_NODE2_REG {
        volatile u32  all;
        struct {
                volatile u32 Q2_NODE0:8;
                volatile u32 Q2_NODE1:8;
                volatile u32 Q2_NODE2:8;
                volatile u32 Q2_NODE3:8;
        }bit;
};

union ADC_NODE2A_REG {
        volatile u32  all;
        struct {
                volatile u32 Q2_NODE4:8;
                volatile u32 Q2_NODE5:8;
                volatile u32 Q2_NODE6:8;
                volatile u32 Q2_NODE7:8;
        }bit;
};

union ADC_NODE2B_REG {
        volatile u32  all;
        struct {
                volatile u32 Q2_NODE8:8;
                volatile u32 Q2_NODE9:8;
                volatile u32 Q2_NODE10:8;
                volatile u32 Q2_NODE11:8;
        }bit;
};


union ADC_MSR_REG {
        volatile u32  all;
        struct {
                volatile u32 Q1_INT:1;
                volatile u32 Q1_FRDY:1;                 
                volatile u32 Q1_FERR:1;
                volatile u32 rsvd0:1;
                volatile u32 Q2_INT:1;
                volatile u32 Q2_FRDY:1;                 
                volatile u32 Q2_FERR:1;
                volatile u32 rsvd1:1;
                volatile u32 Q1_BUSY:1;   
                volatile u32 Q2_BUSY:1;
                volatile u32 Q1_EOQ:1;   
                volatile u32 Q2_EOQ:1;
                volatile u32 rsvd2:4;
                volatile u32 Q1_STATE:5;
                volatile u32 Q2_STATE:5;
                volatile u32 QX_CNT:6;
        }bit;
};

union ADC_CALCSR_REG {
        volatile u32  all;
        struct {
                volatile u32 CAL_EN:1;
                volatile u32 DCAL_MSK:1;
                volatile u32 rsvd0:2;                 
                volatile u32 ADC_CAL_SEL:1;
                volatile u32 rsvd1:3;
                volatile u32 ADC_ACQ:8;
                volatile u32 CAL_VAL:14;
                volatile u32 rsvd2:1;
                volatile u32 CALVAL_UPD:1;            
        }bit;
};

union ADC_FLT_REG {
        volatile u32  all;
        struct {
                volatile u32 TRG_IN_FLT_SEL:4;
                volatile u32 TRG_IN_PRE_FLT:4;
                volatile u32 TRG_SMP_CTL_PRD:8;                   
                volatile u32 rsvd0:16;          
        }bit;
};

union ADC_Q1FCR_REG {
        volatile u32  all;
        struct {
                volatile u32 FIFO_FLUSH:1;
                volatile u32 FIFO_RDYIE:1;
                volatile u32 FIFO_DRQE:1;
                volatile u32 FIFO_ERRIE:1;                    
                volatile u32 rsvd0:4;
                volatile u32 FIFO_DRTH:6;
                volatile u32 rsvd1:2;
                volatile u32 FIFO_OFS:1;
                volatile u32 FIFO_UFS:1;
                volatile u32 rsvd2:6; 
                volatile u32 FIFO_DCNT:6;
                volatile u32 rsvd3:2;
        }bit;
};

union ADC_Q2FCR_REG {
        volatile u32  all;
        struct {
                volatile u32 FIFO_FLUSH:1;
                volatile u32 FIFO_RDYIE:1;
                volatile u32 FIFO_DRQE:1;
                volatile u32 FIFO_ERRIE:1;                    
                volatile u32 rsvd0:4;
                volatile u32 FIFO_DRTH:6;
                volatile u32 rsvd1:2;
                volatile u32 FIFO_OFS:1;
                volatile u32 FIFO_UFS:1;
                volatile u32 rsvd2:6; 
                volatile u32 FIFO_DCNT:6;
                volatile u32 rsvd3:2;
        }bit;
};

union  ADC_ACQCFG_REG {
	volatile u32  all;
	struct {
			volatile u32 ADC_ACQ1: 8;
			volatile u32 ADC_ACQ2: 8;
			volatile u32 ADC_ACQ3: 8;
			volatile u32 ADC_CLR_THR: 8;
	}bit;
};



union  ADC_SHIFT_REG {
	volatile u32  all;
	struct {
			volatile u32 SHIFT: 4;
			volatile u32 rsvd0: 28;
	}bit;
};


union ADC_Q1FDR_REG {
        volatile u32  all;
        struct {
                volatile u32 DATA:16;
                volatile u32 CHNUM:6;
                volatile u32 rsvd0:10;
        }bit;
};

union ADC_Q2FDR_REG {
        volatile u32  all;
        struct {
                volatile u32 DATA:16;
                volatile u32 CHNUM:6;
                volatile u32 rsvd0:10;
        }bit;
};

union ADC_HCL_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 HCL_RD_EN:1;                       //0     Hardware Current Loop Read Enable
                volatile u32 rsvd0:3;                           //3:1   Reserved
                volatile u32 rsvd1:2;                     		//5:4   Reserved
                volatile u32 rsvd2:26;                          //31:6  Reserved
        }bit;
};

union ADC_CTL_REG {
        volatile u32  all;
        struct {
        	volatile u32 TEST_SEL: 4;
        	volatile u32 TEST_EN: 1;
        	volatile u32 BIAS: 4;
        	volatile u32 VCM: 4;
        	volatile u32 EN_VIN_CMP: 1;
        	volatile u32 EN_CAP_CAL: 1;
        	volatile u32 rsvd0: 1;

        	volatile u32 THS_ACQ: 12;
        	volatile u32 THS_BIAS: 2;
        	volatile u32 ADC_V165_SEL: 2;
        }bit;
};

union ADC_CTL1_REG {
        volatile u32  all;
        struct {
        	volatile u32 rsvd0: 1;
        	volatile u32 ADC_ANAC_DIV: 4;
        	volatile u32 rsvd1: 3;
        	volatile u32 CLK_HC: 4;
        	volatile u32 CLK_LC: 4;
        	volatile u32 ADC_PREAMP_SET: 12;
        	volatile u32 rsvd2: 4;
        }bit;
};

union ADC_NODE1_ACQ_REG {
        volatile u32  all;
        struct {
        	volatile u32 Q1_NODE0_ACQ: 2;
        	volatile u32 Q1_NODE1_ACQ: 2;
        	volatile u32 Q1_NODE2_ACQ: 2;
        	volatile u32 Q1_NODE3_ACQ: 2;
        	volatile u32 Q1_NODE4_ACQ: 2;
        	volatile u32 Q1_NODE5_ACQ: 2;
        	volatile u32 Q1_NODE6_ACQ: 2;
        	volatile u32 Q1_NODE7_ACQ: 2;
        	volatile u32 Q1_NODE8_ACQ: 2;
        	volatile u32 Q1_NODE9_ACQ: 2;
        	volatile u32 Q1_NODE10_ACQ: 2;
        	volatile u32 Q1_NODE11_ACQ: 2;
        	volatile u32 rsvd0: 8;
        }bit;
};

union ADC_NODE2_ACQ_REG {
        volatile u32  all;
        struct {
        	volatile u32 Q2_NODE0_ACQ: 2;
        	volatile u32 Q2_NODE1_ACQ: 2;
        	volatile u32 Q2_NODE2_ACQ: 2;
        	volatile u32 Q2_NODE3_ACQ: 2;
        	volatile u32 Q2_NODE4_ACQ: 2;
        	volatile u32 Q2_NODE5_ACQ: 2;
        	volatile u32 Q2_NODE6_ACQ: 2;
        	volatile u32 Q2_NODE7_ACQ: 2;
        	volatile u32 Q2_NODE8_ACQ: 2;
        	volatile u32 Q2_NODE9_ACQ: 2;
        	volatile u32 Q2_NODE10_ACQ: 2;
        	volatile u32 Q2_NODE11_ACQ: 2;
        	volatile u32 rsvd0: 8;
        }bit;
};

union ADC_NODE1_OSR0_REG {
        volatile u32  all;
        struct {
        	volatile u32 Q1_NODE0_OSR: 4;
        	volatile u32 Q1_NODE1_OSR: 4;
        	volatile u32 Q1_NODE2_OSR: 4;
        	volatile u32 Q1_NODE3_OSR: 4;
        	volatile u32 Q1_NODE4_OSR: 4;
        	volatile u32 Q1_NODE5_OSR: 4;
        	volatile u32 Q1_NODE6_OSR: 4;
        	volatile u32 Q1_NODE7_OSR: 4;
        }bit;
};

union ADC_NODE1_OSR1_REG {
        volatile u32  all;
        struct {
        	volatile u32 Q1_NODE8_OSR: 4;
        	volatile u32 Q1_NODE9_OSR: 4;
        	volatile u32 Q1_NODE10_OSR: 4;
        	volatile u32 Q1_NODE11_OSR: 4;
        	volatile u32 rsvd0: 16;
        }bit;
};

union ADC_NODE2_OSR0_REG {
        volatile u32  all;
        struct {
        	volatile u32 Q2_NODE0_OSR: 4;
        	volatile u32 Q2_NODE1_OSR: 4;
        	volatile u32 Q2_NODE2_OSR: 4;
        	volatile u32 Q2_NODE3_OSR: 4;
        	volatile u32 Q2_NODE4_OSR: 4;
        	volatile u32 Q2_NODE5_OSR: 4;
        	volatile u32 Q2_NODE6_OSR: 4;
        	volatile u32 Q2_NODE7_OSR: 4;
        }bit;
};

union ADC_NODE2_OSR1_REG {
        volatile u32  all;
        struct {
        	volatile u32 Q2_NODE8_OSR: 4;
        	volatile u32 Q2_NODE9_OSR: 4;
        	volatile u32 Q2_NODE10_OSR: 4;
        	volatile u32 Q2_NODE11_OSR: 4;
        	volatile u32 rsvd0: 16;
        }bit;
};

union ADC_RES_FLT0_REG {
        volatile u32  all;
        struct {
        	volatile u32 CH0_FLT_SET: 4;
        	volatile u32 CH1_FLT_SET: 4;
        	volatile u32 CH2_FLT_SET: 4;
        	volatile u32 CH3_FLT_SET: 4;
        	volatile u32 CH4_FLT_SET: 4;
        	volatile u32 CH5_FLT_SET: 4;
        	volatile u32 CH6_FLT_SET: 4;
        	volatile u32 CH7_FLT_SET: 4;
        }bit;
};

union ADC_RES_FLT1_REG {
        volatile u32  all;
        struct {
        	volatile u32 CH8_FLT_SET: 4;
        	volatile u32 CH9_FLT_SET: 4;
        	volatile u32 CH10_FLT_SET: 4;
        	volatile u32 CH11_FLT_SET: 4;
        	volatile u32 CH12_FLT_SET: 4;
        	volatile u32 CH13_FLT_SET: 4;
        	volatile u32 CH14_FLT_SET: 4;
        	volatile u32 CH15_FLT_SET: 4;
        }bit;
};

union ADC_RES_FLT2_REG {
        volatile u32  all;
        struct {
        	volatile u32 CH16_FLT_SET: 4;
        	volatile u32 CH17_FLT_SET: 4;
        	volatile u32 CH18_FLT_SET: 4;
        	volatile u32 CH19_FLT_SET: 4;
        	volatile u32 CH20_FLT_SET: 4;
        	volatile u32 CH21_FLT_SET: 4;
        	volatile u32 CH22_FLT_SET: 4;
        	volatile u32 CH23_FLT_SET: 4;
        }bit;
};

union ADC_OFF_CH_REG {
        volatile u32  all;
        struct {
        	volatile u32 ADC_OFF: 16;
        	volatile u32 SIGN_EN: 1;
        	volatile u32 LS_BIT_SET: 3;
        	volatile u32 ADC_OFF_EN: 1;
        	volatile u32 rsvd0: 11;
        }bit;
};


union ADC_WDG0_CFG_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG_EN: 1;
        	volatile u32 WDG_HL_EN: 1;
        	volatile u32 WDG_LL_EN: 1;
        	volatile u32 WDG_IRQ_EN: 1;
        	volatile u32 WDG_PZD_EN: 1;
        	volatile u32 WDG_NZD_EN: 1;
        	volatile u32 rsvd0: 10;
        	volatile u32 WDG_SRC_SEL: 8;
        	volatile u32 rsvd1: 8;
        }bit;
};

union ADC_WDG0_LVL_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG_LL_SET: 16;
        	volatile u32 WDG_HL_SET: 16;
        }bit;
};

union ADC_WDG1_CFG_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG_EN: 1;
        	volatile u32 WDG_HL_EN: 1;
        	volatile u32 WDG_LL_EN: 1;
        	volatile u32 WDG_IRQ_EN: 1;
        	volatile u32 WDG_PZD_EN: 1;
        	volatile u32 WDG_NZD_EN: 1;
        	volatile u32 rsvd0: 10;
        	volatile u32 WDG_SRC_SEL: 8;
        	volatile u32 rsvd1: 8;
        }bit;
};

union ADC_WDG1_LVL_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG_LL_SET: 16;
        	volatile u32 WDG_HL_SET: 16;
        }bit;
};

union ADC_WDG2_CFG_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG_EN: 1;
        	volatile u32 WDG_HL_EN: 1;
        	volatile u32 WDG_LL_EN: 1;
        	volatile u32 WDG_IRQ_EN: 1;
        	volatile u32 WDG_PZD_EN: 1;
        	volatile u32 WDG_NZD_EN: 1;
        	volatile u32 rsvd0: 10;
        	volatile u32 WDG_SRC_SEL: 8;
        	volatile u32 rsvd1: 8;
        }bit;
};

union ADC_WDG2_LVL_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG_LL_SET: 16;
        	volatile u32 WDG_HL_SET: 16;
        }bit;
};

union ADC_WDG_STA_REG {
        volatile u32  all;
        struct {
        	volatile u32 WDG0_HIL_STA: 1;
        	volatile u32 WDG0_LOL_STA: 1;
        	volatile u32 WDG0_PZD_STA: 1;
        	volatile u32 WDG0_NZD_STA: 1;
        	volatile u32 rsvd0: 4;
        	volatile u32 WDG1_HIL_STA: 1;
        	volatile u32 WDG1_LOL_STA: 1;
        	volatile u32 WDG1_PZD_STA: 1;
        	volatile u32 WDG1_NZD_STA: 1;
        	volatile u32 rsvd1: 4;
        	volatile u32 WDG2_HIL_STA: 1;
        	volatile u32 WDG2_LOL_STA: 1;
        	volatile u32 WDG2_PZD_STA: 1;
        	volatile u32 WDG2_NZD_STA: 1;
        	volatile u32 rsvd2: 12;
        }bit;
};

union ADC_HCL_CFG_REG {
        volatile u32  all;
        struct {
        	volatile u32 TRG_HCL_SEL: 1;
        	volatile u32 HCL_SEQ_SEL: 1;
        	volatile u32 HCL_SIG_TRG_EN: 1;
        	volatile u32 rsvd0: 29;
        }bit;
};

union ADC_QN_MCR_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_EN: 1;
        	volatile u32 QN_OVR: 1;
        	volatile u32 QN_PS_EN: 1;
        	volatile u32 QN_RST: 1;
        	volatile u32 QN_INTM: 1;
        	volatile u32 QN_INTE: 1;
        	volatile u32 rsvd0: 25;
        	volatile u32 QN_SS_EN: 1;
        }bit;
};

union ADC_QN_TCR_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_TRG_NUM: 8;
        	volatile u32 rsvd0: 24;
        }bit;
};

union ADC_QN_PSI_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_PSI: 28;
        	volatile u32 rsvd0: 4;
        }bit;
};

union ADC_QN_MSR_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_INT: 1;
        	volatile u32 QN_BUSY: 1;
        	volatile u32 QN_EOQ: 1;
        	volatile u32 rsvd0: 13;
        	volatile u32 QN_STATE: 5;
        	volatile u32 rsvd1: 5;
        	volatile u32 QN_CNT: 6;
        }bit;
};

union ADC_QN_NODE0_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE0: 8;
        	volatile u32 QN_NODE1: 8;
        	volatile u32 QN_NODE2: 8;
        	volatile u32 QN_NODE3: 8;
        }bit;
};

union ADC_QN_NODE1_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE4: 8;
        	volatile u32 QN_NODE5: 8;
        	volatile u32 QN_NODE6: 8;
        	volatile u32 QN_NODE7: 8;
        }bit;
};

union ADC_QN_NODE2_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE8: 8;
        	volatile u32 QN_NODE9: 8;
        	volatile u32 QN_NODE10: 8;
        	volatile u32 QN_NODE11: 8;
        }bit;
};

union ADC_QN_NODE3_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE12: 8;
        	volatile u32 QN_NODE13: 8;
        	volatile u32 QN_NODE14: 8;
        	volatile u32 QN_NODE15: 8;
        }bit;
};

union ADC_QN_NODE4_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE16: 8;
        	volatile u32 QN_NODE17: 8;
        	volatile u32 QN_NODE18: 8;
        	volatile u32 QN_NODE19: 8;
        }bit;
};

union ADC_QN_NODE5_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE20: 8;
        	volatile u32 QN_NODE21: 8;
        	volatile u32 QN_NODE22: 8;
        	volatile u32 QN_NODE23: 8;
        }bit;
};

union ADC_QN_ACQ0_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE0_ACQ: 2;
        	volatile u32 QN_NODE1_ACQ: 2;
        	volatile u32 QN_NODE2_ACQ: 2;
        	volatile u32 QN_NODE3_ACQ: 2;
        	volatile u32 QN_NODE4_ACQ: 2;
        	volatile u32 QN_NODE5_ACQ: 2;
        	volatile u32 QN_NODE6_ACQ: 2;
        	volatile u32 QN_NODE7_ACQ: 2;
        	volatile u32 QN_NODE8_ACQ: 2;
        	volatile u32 QN_NODE9_ACQ: 2;
        	volatile u32 QN_NODE10_ACQ: 2;
        	volatile u32 QN_NODE11_ACQ: 2;
        	volatile u32 rsvd0: 8;
        }bit;
};

union ADC_QN_ACQ1_REG {
        volatile u32  all;
        struct {
        	volatile u32 QN_NODE12_ACQ: 2;
        	volatile u32 QN_NODE13_ACQ: 2;
        	volatile u32 QN_NODE14_ACQ: 2;
        	volatile u32 QN_NODE15_ACQ: 2;
        	volatile u32 QN_NODE16_ACQ: 2;
        	volatile u32 QN_NODE17_ACQ: 2;
        	volatile u32 QN_NODE18_ACQ: 2;
        	volatile u32 QN_NODE19_ACQ: 2;
        	volatile u32 QN_NODE20_ACQ: 2;
        	volatile u32 QN_NODE21_ACQ: 2;
        	volatile u32 QN_NODE22_ACQ: 2;
        	volatile u32 QN_NODE23_ACQ: 2;
        	volatile u32 rsvd0: 8;
        }bit;
};

union ADC_QN_FCR_REG {
        volatile u32  all;
        struct {
        	volatile u32 FIFO_FLUSH: 1;
        	volatile u32 FIFO_RDYIE: 1;
        	volatile u32 rsvd0: 1;
        	volatile u32 FIFO_ERRIE: 1;
        	volatile u32 rsvd1: 4;
        	volatile u32 FIFO_DRTH: 6;
        	volatile u32 rsvd2: 2;
        	volatile u32 FIFO_OFS: 1;
        	volatile u32 FIFO_UFS: 1;
        	volatile u32 rsvd3: 2;
        	volatile u32 FIFO_RDY: 1;
        	volatile u32 FIFO_ERR: 1;
        	volatile u32 rsvd4: 2;
        	volatile u32 FIFO_DATA_NUM: 6;
        	volatile u32 rsvd5: 2;
        }bit;
};

union ADC_QN_FDR_REG {
        volatile u32  all;
        struct {
        	volatile u32 DATA: 16;
        	volatile u32 CHNUM: 6;
        	volatile u32 rsvd0: 10;
        }bit;
};

union ADC_CAPCALCSR_REG {
        volatile u32  all;
        struct {
        	volatile u32 CALEN: 1;
        	volatile u32 rsvd0: 3;
        	volatile u32 CAP_CAL_MODE:2;
        	volatile u32 rsvd1: 10;
        	volatile u32 CALVAL: 12;
        	volatile u32 rsvd2: 3;
        	volatile u32 CAP_CALVAL_UPD: 1;
        }bit;
};

struct ADC_REGS {                       
        union   ADC_MCR_REG        ADC_MCR;          //offset: 0x00                       
        union   ADC_TCR_REG        ADC_TCR;          //offset: 0x04
        volatile u32  RES0[2];						 //offset: 0x08_0xC
        union   ADC_MSR_REG        ADC_MSR;          //offset: 0x10
        union   ADC_CALCSR_REG     ADC_CALCSR;       //offset: 0x14
        volatile u32  RES1;                          //offset: 0x18
        union   ADC_FLT_REG        ADC_FLT;          //offset: 0x1C
        union   ADC_Q1FCR_REG      ADC_Q1FCR;        //offset: 0x20
        union   ADC_Q2FCR_REG      ADC_Q2FCR;        //offset: 0x24
    	union   ADC_ACQCFG_REG     ADC_ACQCFG;	     //offset: 0x28
    	union   ADC_SHIFT_REG      ADC_SHIFT;		 //offset: 0x2C
        volatile u32  RES2[4];            			 //offset: 0x30/34/38/3C
        union   ADC_Q1FDR_REG      ADC_Q1FDR;        //offset: 0x40
        volatile u32  RES3[15];  					 //0x44/48/4C_50_5C/60_6C/70_7C
        union   ADC_Q2FDR_REG      ADC_Q2FDR;        //offset: 0x80
        volatile u32  RES4[3];						 //0x84/88/8C
        union   ADC_HCL_CTL_REG    ADC_HCL_CTL;      //offset: 0x90

    	union  ADC_CTL_REG         ADC_CTL;			//0x94
    	union  ADC_CTL1_REG        ADC_CTL1;		//0x98
    	volatile u32  RES5;							//0x9C

    	union  ADC_NODE1_REG       ADC_NODE1;		//0xA0
    	union  ADC_NODE1A_REG      ADC_NODE1A;		//0xA4
    	union  ADC_NODE1B_REG      ADC_NODE1B;		//0xA8
    	volatile u32  RES6;							//0xAC

    	union  ADC_NODE2_REG       ADC_NODE2;		//0xB0
    	union  ADC_NODE2A_REG      ADC_NODE2A;		//0xB4
    	union  ADC_NODE2B_REG      ADC_NODE2B;		//0xB8
    	volatile u32  RES7;							//0xBC

    	union  ADC_NODE1_ACQ_REG   ADC_NODE1_ACQ;	//0xC0
    	union  ADC_NODE2_ACQ_REG   ADC_NODE2_ACQ;	//0xC4
    	union  ADC_NODE1_OSR0_REG  ADC_NODE1_OSR0;	//0xC8
    	union  ADC_NODE1_OSR1_REG  ADC_NODE1_OSR1;	//0xCC
    	union  ADC_NODE2_OSR0_REG  ADC_NODE2_OSR0;	//0xD0
    	union  ADC_NODE2_OSR1_REG  ADC_NODE2_OSR1;	//0xD4
    	union  ADC_RES_FLT0_REG    ADC_RES_FLT0;   	//0xD8
    	union  ADC_RES_FLT1_REG    ADC_RES_FLT1;   	//0xDC
    	union  ADC_RES_FLT2_REG    ADC_RES_FLT2;   	//0xE0
    	volatile u32   RES8[7];						//0xE4/E8/EC/F0_FC
    	volatile u32   			   ADC_RES_CH[24];	//0x100_10C/1/2/3/4/5
    	volatile u32   RES9[8];						//0x160_16C/7
    	union  ADC_OFF_CH_REG      ADC_OFF_CH[24];  //0x180_18C/9/A/B/C/D
    	volatile u32   RES10[8];					//0x1E0_1EC/1F0_1FC

    	volatile u32   RES11[8];					//0x200/204/208/20C
    												//0x210_21C

    	union  ADC_WDG0_CFG_REG     ADC_WDG0_CFG;	//0x220
    	union  ADC_WDG0_LVL_REG     ADC_WDG0_LVL;	//0x224
    	volatile u32   RES12[2];					//0x228/22C
    	union  ADC_WDG1_CFG_REG     ADC_WDG1_CFG;	//0x230
    	union  ADC_WDG1_LVL_REG     ADC_WDG1_LVL;	//0x234
    	volatile u32   RES13[2];					//0x238/23C
    	union  ADC_WDG2_CFG_REG     ADC_WDG2_CFG;	//0x240
    	union  ADC_WDG2_LVL_REG     ADC_WDG2_LVL;	//0x244
    	union  ADC_WDG_STA_REG      ADC_WDG_STA;	//0x248
    	volatile u32   RES14[5];					//0x24C/0x250_25C
    	volatile u32   RES15;						//0x260
    	union  ADC_HCL_CFG_REG      ADC_HCL_CFG;	//0x264
    	volatile u32   RES16[38];					//0x268_26C/7/8/9/A/B/C/D/E/F

    	union  ADC_QN_MCR_REG        ADC_QN_MCR;	//0x300
    	union  ADC_QN_TCR_REG        ADC_QN_TCR;	//0x304
    	union  ADC_QN_PSI_REG        ADC_QN_PSI;	//0x308
    	union  ADC_QN_MSR_REG        ADC_QN_MSR;	//0x30C
    	union  ADC_QN_NODE0_REG      ADC_QN_NODE0;	//0x310
    	union  ADC_QN_NODE1_REG      ADC_QN_NODE1;	//0x314
    	union  ADC_QN_NODE2_REG      ADC_QN_NODE2;	//0x318
    	union  ADC_QN_NODE3_REG      ADC_QN_NODE3;	//0x31C
    	union  ADC_QN_NODE4_REG      ADC_QN_NODE4;	//0x320
    	union  ADC_QN_NODE5_REG      ADC_QN_NODE5;	//0x324
    	union  ADC_QN_ACQ0_REG       ADC_QN_ACQ0;	//0x328
    	union  ADC_QN_ACQ1_REG       ADC_QN_ACQ1;	//0x32C
    	union  ADC_QN_FCR_REG        ADC_QN_FCR;	//0x330
    	union  ADC_QN_FDR_REG        ADC_QN_FDR;	//0x334
    	volatile u32   RES17[18];					//0x338
    	union  ADC_CAPCALCSR_REG   ADC_CAPCALCSR;	//0x380
    	volatile u32   ADC_DCALC[10];			    //0x384
};

void adc_irq_handler(void);
void adc_irq_register(cpu_irq_fun_t irqhandle);
void adc_irq_unregister(void);
void adc_cmu_init(void);
void adc_pinmux_init(u32 pin);
void adc_fifo1_flush(u32 num);
void adc_fifo2_flush(u32 num);
void adc_q1_trig_sample_num(u32 num, u32 smpnum);
void adc_q2_trig_sample_num(u32 num, u32 smpnum);
void adc_q1_node0_set(u32 num, u32 channel);
void adc_q1_node1_set(u32 num, u32 channel);
void adc_q1_node2_set(u32 num, u32 channel);
void adc_q1_node3_set(u32 num, u32 channel);
void adc_q1_node4_set(u32 num, u32 channel);
void adc_q1_node5_set(u32 num, u32 channel);
void adc_q1_node6_set(u32 num, u32 channel);
void adc_q1_node7_set(u32 num, u32 channel);
void adc_q2_node0_set(u32 num, u32 channel);
void adc_q2_node1_set(u32 num, u32 channel);
void adc_q2_node2_set(u32 num, u32 channel);
void adc_q2_node3_set(u32 num, u32 channel);
void adc_q2_node4_set(u32 num, u32 channel);
void adc_q2_node5_set(u32 num, u32 channel);
void adc_q2_node6_set(u32 num, u32 channel);
void adc_q2_node7_set(u32 num, u32 channel);
void adc_q1_fifo_th_set(u32 num, u32 th);
void adc_q2_fifo_th_set(u32 num, u32 th);
void adc_q1_dma_en(u32 num);
void adc_q2_dma_en(u32 num);
void adc_en(u32 num);
void adc_smp_rate_set(u32 num, u32 smp_rate);
void adc_q1_int_en(u32 num);
void adc_q2_int_en(u32 num);
void adc_q1_cvra_en(u32 num);
void adc_q2_cvrb_en(u32 num);
void adc_q1_sw_trig(u32 num);
void adc_q2_sw_trig(u32 num);
void adc_hcl_en(u32 num);
void adc_hcl_mode_set(u32 num, ADC_HCL_TYPE hcl_type);
void adc_pre_set(u32 num, u32 adc_pre);
u32 adc_int_sts(u32 num);
void adc_clr_q1_int(u32 num);
void adc_clr_q2_int(u32 num);
u32 adc_read_q1(u32 num);
u32 adc_read_q2(u32 num);
void adc_cal(u32 num);
void adc_module_clk_cfg(u32 num);
void adc_init_cfg(u32 num);
u32 adc_rd_ch_res(u32 num, u32 ch);

void adc_acq1_set(u32 num, u32 acq1);
void adc_acq2_set(u32 num, u32 acq2);
void adc_acq3_set(u32 num, u32 acq3);
void adc_q1_node_smp_set(u32 num, u32 node, u32 smp);
void adc_q2_node_smp_set(u32 num, u32 node, u32 smp);
void adc_q1_osr_set(u32 num, u32 node, u32 osr);
void adc_q2_osr_set(u32 num, u32 node, u32 osr);
void adc_res_filter_set(u32 num, u32 ch, u32 filt);
void adc_off_set(u32 num, u32 ch, u32 offset);
void adc_off_en_set(u32 num, u32 ch, u32 en);
void adc_off_sgnen_set(u32 num, u32 ch, u32 sgnen);
void adc_off_lsbit_set(u32 num, u32 ch, u32 lsbit);
void adc_wdog_src_set(u32 num, u32 wdg, u32 src);
void adc_wdog_en_set(u32 num, u32 wdg, u32 en);
void adc_wdog_hlen_set(u32 num, u32 wdg, u32 hlen);
void adc_wdog_llen_set(u32 num, u32 wdg, u32 llen);
void adc_wdog_irqen_set(u32 num, u32 wdg, u32 irqen);
void adc_wdog_pzden_set(u32 num, u32 wdg, u32 pzden);
void adc_wdog_nzden_set(u32 num, u32 wdg, u32 nzden);
void adc_wdog_hil_set(u32 num, u32 wdg, u32 hil);
void adc_wdog_lol_set(u32 num, u32 wdg, u32 lol);
u32 adc_wdog_sts(u32 num);
void adc_hcl_strg_en(u32 num, u32 en);
void adc_hcl_strg_src(u32 num, u32 src);
void adc_hcl_strg_seq(u32 num, u32 seq);
void adc_qn_en(u32 num, u32 en);
void adc_qn_ovr_en(u32 num, u32 en);
void adc_qn_ps_en(u32 num, u32 en);
void adc_qn_reset(u32 num);
void adc_qn_intm_set(u32 num, u32 mod);
void adc_qn_int_en(u32 num, u32 en);
void adc_qn_sw_trg(u32 num);
void adc_qn_trg_num(u32 num, u32 trg_num);
u32 adc_qn_int_sts(u32 num);
void adc_qn_node_src(u32 num, u32 node, u32 src);
void adc_qn_node_acq(u32 num, u32 node, u32 acq);
void adc_fifon_flush(u32 num);
void adc_qn_fifo_th_set(u32 num, u32 th);
void adc_qn_rdyirq_en(u32 num, u32 en);
u32 adc_read_qn(u32 num);
void adc_capcalcsr(u32 num);
void adc_calcsr(u32 num);
void adc_12b_mod_set(u32 num);
void adc_14b_mod_set(u32 num);
#endif /* INCLUDE_HAL_ADC_H_ */
