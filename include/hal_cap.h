/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_CAP_H_
#define INCLUDE_HAL_CAP_H_

typedef enum {
        CAP_INPUT = 0,
        PWM_OUTPUT,
} CAP_MOD;

typedef enum {
        CAP_RISE_EDG = 0,
        CAP_FALL_EDG,
} CAP_EDGE_TYPE;

typedef enum {
        CAP_END_EVNT0 = 0,
        CAP_END_EVNT1,
        CAP_END_EVNT2,
        CAP_END_EVNT3,
} CAP_END_TYPE;

typedef enum {
        SRC_IO = 0,
        SRC_EPWM0_A,
        SRC_EPWM1_A,
        SRC_EPWM2_A,
        SRC_EPWM3_A,
        SRC_EPWM4_A,
        SRC_EPWM5_A,
        SRC_EPWM6_A,
        SRC_EPWM7_A,
        SRC_EPWM8_A,
        SRC_EPWM9_A,
        SRC_EPWM10_A,
        SRC_EPWM11_A,

        SRC_EPWM0_B = 0x11,
        SRC_EPWM1_B,
        SRC_EPWM2_B,
        SRC_EPWM3_B,
        SRC_EPWM4_B,
        SRC_EPWM5_B,
        SRC_EPWM6_B,
        SRC_EPWM7_B,
        SRC_EPWM8_B,
        SRC_EPWM9_B,
        SRC_EPWM10_B,
        SRC_EPWM11_B,

		SRC_CPM0_COH = 0x20,
		SRC_CPM0_COL,
		SRC_CPM0_COHL,
		SRC_CPM1_COH,
		SRC_CPM1_COL,
		SRC_CPM1_COHL,

		SRC_ECAT_SYNC0 = 0x30,
		SRC_ECAT_SYNC1,
} CAP_SRC_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union CAP_CONF1_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 EVNT0_POL:1;                       //0     Capture Event0 Polarity Set
                volatile u32 EVNT0_RST:1;                       //1     Capture Event0 Reset
                volatile u32 EVNT1_POL:1;                       //2     Capture Event1 Polarity Set
                volatile u32 EVNT1_RST:1;                       //3     Capture Event1 Reset
                volatile u32 EVNT2_POL:1;                       //4     Capture Event2 Polarity Set
                volatile u32 EVNT2_RST:1;                       //5     Capture Event2 Reset
                volatile u32 EVNT3_POL:1;                       //6     Capture Event3 Polarity Set
                volatile u32 EVNT3_RST:1;                       //7     Capture Event3 Reset
                volatile u32 REG_LD_EN:1;                       //8     Capture Register Load Enable
                volatile u32 INEDG_EVN_DIV:5;                   //13:9  Capture Input Edge Event Divisor
                volatile u32 CAP_EN_CTL:2;						//15:14 CAP_EN_CTL
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union CAP_CONF2_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 OS_MOD_EN:1;                       //0     Capture One-shot Mode Enable
                volatile u32 OS_EP:2;                           //2:1   Capture One-shot End Point      
                volatile u32 EVNT_RST:1;                        //3     Capture Event Reset 
                volatile u32 CNT_EN:1;                          //4     Capture Counter Enable 
                volatile u32 SYNC_IN_EN:1;                      //5     Capture Synchronous Input Enable 
                volatile u32 SYNC_OUT:2;                        //7:6   Capture Synchronous Output Select         
                volatile u32 SW_FRC_SYNC:1;                     //8     Capture Software Force Synchronous Signal 
                volatile u32 CAP_MOD_SEL:1;                     //9     Capture Mode Select 
                volatile u32 CAP_PWM_POL:1;                     //10    Capture PWM Output Polarity 
                volatile u32 PWM_OUT_INIT:1;                    //11    Capture PWM Output Initial Value              
                volatile u32 rsvd0:20;                          //31:12 Reserved 
        }bit;
};

union CAP_INT_EN_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rsvd0:1;                           //0     Reserved
                volatile u32 EVNT0_INT_EN:1;                    //1     Capture Event0 Interrupt Enable
                volatile u32 EVNT1_INT_EN:1;                    //2     Capture Event1 Interrupt Enable
                volatile u32 EVNT2_INT_EN:1;                    //3     Capture Event2 Interrupt Enable
                volatile u32 EVNT3_INT_EN:1;                    //4     Capture Event3 Interrupt Enable
                volatile u32 OVFL_INT_EN:1;                     //5     Counter Overflow Interrupt Enable
                volatile u32 CNT_PRD_INT_EN:1;                  //6     Counter Period Interrupt Enable
                volatile u32 CNT_CMP_INT_EN:1;                  //7     Counter Compare Interrupt Enable          
                volatile u32 rsvd1:24;                          //31:8  Reserved
        }bit;
};

union CAP_INT_FLG_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 CAP_INT_FLG:1;                     //0     Capture Interrupt Flag
                volatile u32 EVNT0_INT_FLG:1;                   //1     Capture Event0 Flag
                volatile u32 EVNT1_INT_FLG:1;                   //2     Capture Event1 Flag
                volatile u32 EVNT2_INT_FLG:1;                   //3     Capture Event2 Flag
                volatile u32 EVNT3_INT_FLG:1;                   //4     Capture Event3 Flag
                volatile u32 OVFL_INT_FLG:1;                    //5     Counter Overflow Flag
                volatile u32 CNT_PRD_INT_FLG:1;                 //6     Capture Counter Period Flag
                volatile u32 CNT_CMP_INT_FLG:1;                 //7     Capture Counter Compare Flag                  
                volatile u32 rsvd1:24;                          //31:8  Reserved
        }bit;
};

union CAP_INT_CLR_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rsvd0:1;                           //0     Reserved 
                volatile u32 EVNT0_INT_CLR:1;                   //1     Capture Event0 Flag Clear 
                volatile u32 EVNT1_INT_CLR:1;                   //2     Capture Event1 Flag Clear 
                volatile u32 EVNT2_INT_CLR:1;                   //3     Capture Event2 Flag Clear 
                volatile u32 EVNT3_INT_CLR:1;                   //4     Capture Event3 Flag Clear 
                volatile u32 OVFL_INT_CLR:1;                    //5     Counter Overflow Flag Clear
                volatile u32 CNT_PRD_INT_CLR:1;                 //6     Counter Period Flag Clear 
                volatile u32 CNT_CMP_INT_CLR:1;                 //7     Counter Compare Flag Clear          
                volatile u32 rsvd1:24;                          //31:8  Reserved 
        }bit;
};

union CAP_INT_FRC_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rsvd0:1;                           //0     Reserved 
                volatile u32 EVNT0_INT_FRC:1;                   //1     Capture Software Force Event0 
                volatile u32 EVNT1_INT_FRC:1;                   //2     Capture Software Force Event1 
                volatile u32 EVNT2_INT_FRC:1;                   //3     Capture Software Force Event2 
                volatile u32 EVNT3_INT_FRC:1;                   //4     Capture Software Force Event3 
                volatile u32 OVFL_INT_FRC:1;                    //5     Force Counter Overflow 
                volatile u32 CNT_PRD_INT_FRC:1;                 //6     Force Counter Period 
                volatile u32 CNT_CMP_INT_FRC:1;                 //7     Force Counter Compare                   
                volatile u32 rsvd1:24;                          //31:8  Reserved         
        }bit;
};

union CAP_IN_FLT_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 CAP_IN_FLT_SEL:4;                  //3:0   Input Filter Seclect
                volatile u32 CAP_IN_PRE_FLT:4;                  //7:4   Input Pre Filter Enable
                volatile u32 CAP_SMP_CTL_PRD:8;                 //15:8  Input Sample Control Period
                volatile u32 rsvd0:16;
        }bit;
};

union CAP_IN_SRC_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 CAP_IN_SRC_SEL:6;                  //5:0   Cap Input Source Seclect
                volatile u32 rsvd0:10;							//15:6  Reserved
                volatile u32 CAP_IND_NXT_EVNT:2;				//17:16 CAP_IND_NXT_EVNT
                volatile u32 rsvd1:14;							//31:18 Reserver
        }bit;
};

union CAP_DMA_CFG_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 DMA_EN:1;                  		 //0  DMA_EN
                volatile u32 DMA_REQ_SRC_SEL:3;					 //3:1  DMA_REQ_SRC_SEL
                volatile u32 rsvd0:12;				 			 //15:14 Reserved
                volatile u32 DMA_ERR_STS:1;						 //16 DMA_ERR_STS
                volatile u32 rsvd1:15;							 //31:17 Reserver
        }bit;
};

struct CAP_REGS {
        volatile u32    CAP_CNT_V;                                     //offset: 0x00                     
        volatile u32    CAP_CNT_PHV;                                   //offset: 0x04                 
        volatile u32    CAP_REG0;                                      //offset: 0x08                 
        volatile u32    CAP_REG1;                                      //offset: 0x0C                   
        volatile u32    CAP_REG2;                                      //offset: 0x10                    
        volatile u32    CAP_REG3;                                      //offset: 0x14                                
        union   CAP_CONF1_REG            CAP_CONF1;                    //offset: 0x18                         
        union   CAP_CONF2_REG            CAP_CONF2;                    //offset: 0x1C
        union   CAP_INT_EN_REG           CAP_INT_EN;                   //offset: 0x20
        union   CAP_INT_FLG_REG          CAP_INT_FLG;                  //offset: 0x24
        union   CAP_INT_CLR_REG          CAP_INT_CLR;                  //offset: 0x28
        union   CAP_INT_FRC_REG          CAP_INT_FRC;                  //offset: 0x2C 
        union   CAP_IN_FLT_REG           CAP_IN_FLT;                   //offset: 0x30
        union   CAP_IN_SRC_REG           CAP_IN_SRC;                   //offset: 0x34
        union	CAP_DMA_CFG_REG			 CAP_DMA_CFG;				   //offset: 0x38
};

void cap0_irq_handler(void);
void cap1_irq_handler(void);
void cap2_irq_handler(void);
void cap3_irq_handler(void);
void cap4_irq_handler(void);
void cap5_irq_handler(void);
void cap_irq_register(u32 num, cpu_irq_fun_t irqhandle);
void cap_irq_unregister(u32 num);
void cap_en(u8 i);
void cap_mode(u8 i , CAP_MOD mod);
u32 cap_get_cnt(u8 i);
void cap_em_control(u8 n,u32 ctl);
void cap_dma_en(u8 n);
void cap_dma_dis(u8 n);
void cap_dma_src(u8 n,u32 event);
#endif /* INCLUDE_HAL_CAP_H_ */
