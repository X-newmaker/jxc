/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_EPWM_H_
#define INCLUDE_HAL_EPWM_H_

typedef enum{
        P_DISABLE  = 0,
        P_ENABLE,
} P_EN;

typedef enum{
        CNT_UP  = 0,
        CNT_DOWN,
        CNT_UP_DOWN,
        CNT_STOP,
} PWM_CNT_MODE;

typedef enum{
        DIR_DECR = 0,
        DIR_INCR,
} PH_DIR_TYPE;

typedef enum{
        SHAD = 0,
        IMED,
} UPDT_TYPE;

typedef enum{
        SYNCIN_OR_SW = 0,
        SO_CNTZ,
        SO_CMPB,
        SO_NONE,        
} SYNC_OUT_TYPE;

typedef enum{
        ADIV1 = 0,
        ADIV2,
        ADIV4,
        ADIV6,
        ADIV8,
        ADIV10,
        ADIV12,
        ADIV14,        
} DIV1_TYPE;

typedef enum{
        BDIV1 = 0,
        BDIV2,
        BDIV4,
        BDIV8,
        BDIV16,
        BDIV32,
        BDIV64,
        BDIV128,        
} DIV2_TYPE;

typedef enum{
        CNT_ZRO = 0,
        CNT_PRD,
        CNT_Z_OR_P,
        NEVR_UPDT,
        PUL_ZRO,
        SYNCIN0,
        CNT_Z_OR_SYNCIN0,
        NEVR_UPDT_,
} LP_TYPE;

typedef enum{
        ACT_NONE = 0,
        ACT_LOW,
        ACT_HIGH,
        ACT_TOGL,      
} ACT_TYPE;

typedef enum{
        CTACT_NONE0 = 0,
        CTACT_LOW,
        CTACT_HIGH,
        CTACT_NONE1,     
} SW_CTACT_TYPE;

typedef enum{
        BP_CHA_AND_CHB = 0,
        BP_CHB,
        BP_CHA,
        NO_BP,      
} OUTBP_TYPE;

typedef enum{
        CHA_AND_CHB_POST = 0,
        CHA_NEGT_CHB_POST, 
        CHA_POST_CHB_NEGT,
        CHA_AND_CHB_NEGT,   
} POL_TYPE;

typedef enum{
        CHAB_SEL_PWMA = 0,
        CHA_SEL_PWMB_CHB_SEL_PWMA, 
        CHA_SEL_PWMA_CHB_SEL_PWMB,
        CHAB_SEL_PWMB,   
} INCH_SEL_TYPE;

typedef enum{
        PROTECT_HIGHZ = 0,
        PROTECT_HIGH, 
        PROTECT_LOW,
        NO_ACT,   
} PROTECT_TYPE;

typedef enum{
        FAULT_LOW = 0,
        FAULT_HIGH,  
} FAULT_TYPE;

typedef enum{
        SRC_CNT_ZRO = 0,
        SRC_CNT_PRD, 
        SRC_CNT_UAV,
        SRC_CNT_DAV,
        SRC_CNT_UBV,
        SRC_CNT_DBV,
        SRC_CNT_Z_OR_P, 
        SRC_PUL_ZRO,  
} APWM_INTR_SRC_TYPE;

typedef enum{
        SRC_NONE_OUT = 0,
        SRC_DIV1_OUT, 
        SRC_DIV2_OUT,
        SRC_DIV3_OUT,  
} SRC_DIV_TYPE;

typedef enum{
        HPWM_RISE_TYPE = 0,
        HPWM_FALL_TYPE, 
        HPWM_BOTH_TYPE,
        HPWM_NONE_TYPE,  
} HPWM_TYPE;

typedef enum{
        NONE_SW_CT = 0,
        SW_CT_LOW, 
        SW_CT_HIGH,
        NONE_SW_CT_,  
} SW_CT_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union PWM_CNT_PRDV_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PRD_VAL:16;                //15:0  EPWM_CNT_PRDV
                volatile u32 rsvd:16;                   //31:16 Reserved                          
        }bit;
};

union PWM_CNT_PHV_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PH_VAL:16;                 //15:0  EPWM_CNT_PHV
                volatile u32 rsvd:16;                   //31:16 Reserved   
        }bit;
};

union PWM_CNT_V_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_VAL:16;                //15:0  EPWM_CNT_V
                volatile u32 rsvd:16;                   //31:16 Reserved   
        }bit;
};

union PWM_CNT_CFG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_MOD:2;                 //1:0   EPWM_CNT_MOD
                volatile u32 CNT_PH_EN:1;               //2     EPWM_CNT_PH_EN
                volatile u32 CNT_PRD_UPDT:1;            //3     EPWM_CNT_PRD_UPDT
                volatile u32 PRD_LD:2;                  //5:4   EPWM_PRD_LD
                volatile u32 SW_FRC_SYNC:1;             //6     EPWM_SW_FRC_SYNC
                volatile u32 CLK_DIV1:3;                //9:7   EPWM_CLK_DIV1
                volatile u32 CLK_DIV2:3;                //12:10 EPWM_CLK_DIV2
                volatile u32 CNT_PH_DIR:1;              //13    EPWM_CNT_PH_DIR
                volatile u32 SYNC_OUT:3;                //16:14 EPWM_SYNC_OUT
                volatile u32 CMPA_SI_PULEN:1;           //17    EPWM_CMPA_SI_UPDT_PULSE_EN  
                volatile u32 CMPB_SI_PULEN:1;           //18    EPWM_CMPB_SI_UPDT_PULSE_EN
                volatile u32 CMPA_IMD_PULEN:1;          //19    EPWM_CMPA_IMD_UPDT_PULSE_EN
                volatile u32 CMPB_IMD_PULEN:1;          //20    EPWM_CMPB_IMD_UPDT_PULSE_EN
                volatile u32 PAUSE_INI_OUT_EN:1;		//21	PAUSE_INI_OUT_EN
                volatile u32 PAUSE_INI_SRC_EN:1;		//22	PAUSE_INI_SRC_EN
                volatile u32 rsvd:1;                    //23	Reserved
                volatile u32 PWM_CNT_SIG_EN:1;          //24    PWM_CNT_SIG_EN
                volatile u32 PWM_CNT_RST_RTG:1;         //25    PWM_CNT_RST_RTG
                volatile u32 PWM_CNT_RST:1;             //26    PWM_CNT_RST
                volatile u32 PWM_TRG0_RST_EN:1;         //27    PWM_TRG0_RST_EN
                volatile u32 PWM_TRG1_RST_EN:1;         //28    PWM_TRG1_RST_EN
                volatile u32 rsvd1:1;                   //29 	Reserved
                volatile u32 EPWM_EM_CTL:2;				//31:30 EPWM_EM_CTL


        }bit;
};

union PWM_CNT_STS_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_DIR_STS:1;             //0     EPWM_CNT_DIR_STS
                volatile u32 SYNC_IN_STS:1;             //1     EPWM_SYNC_IN_STS
                volatile u32 CNT_OF_STS:1;              //2     EPWM_CNT_OF_STS                    
                volatile u32 rsvd:29;                   //31:3  Reserved
        }bit;
};

union PWM_CNT_AV_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_AV:16;                 //15:0  EPWM_CNT_AV                                   
                volatile u32 rsvd:16;                   //31:16 Reserved   
        }bit;
};

union PWM_CNT_BV_REG {
        volatile u32  all;
        struct{                                         //bit description                                                 
                volatile u32 CNT_BV:16;                 //15:0  EPWM_CNT_BV                                 
                volatile u32 rsvd:16;                   //31:16 Reserved   
        }bit;
};

union PWM_UPDT_MODE_REG {
        volatile u32  all;
        struct{                                         //bit description 
                volatile u32 CMPA_LP:3;                 //2:0   EPWM_CMPA_LP                                     
                volatile u32 CMPB_LP:3;                 //5:3   EPWM_CMPB_LP
                volatile u32 CMPA_UPDT:1;               //6     EPWM_CNT_CMPA_UPDT                    
                volatile u32 CMPB_UPDT:1;               //7     EPWM_CNT_CMPB_UPDT
                volatile u32 CMPA_SHD_STS:1;            //8     EPWM_CMPA_SHD_STS
                volatile u32 CMPB_SHD_STS:1;            //9     EPWM_CMPB_SHD_STS
                volatile u32 rsvd2:22;                  //31:10 Reserved                             
        }bit;
};

union PWM_A_ACT_REG {
        volatile u32  all;
        struct{                                         //bit description                                         
                volatile u32 ACT_CNT_Z:2;               //1:0   EPWMA_ACT_CNTZ
                volatile u32 ACT_CNT_PRD:2;             //3:2   EPWMA_ACT_CNTPRD
                volatile u32 ACT_CNT_UAV:2;             //5:4   EPWMA_ACT_CNTUAV
                volatile u32 ACT_CNT_DAV:2;             //7:6   EPWMA_ACT_CNTDAV
                volatile u32 ACT_CNT_UBV:2;             //9:8   EPWMA_ACT_CNTUBV
                volatile u32 ACT_CNT_DBV:2;             //11:10 EPWMA_ACT_CNTDBV
                volatile u32 ACT_LP:3;                  //14:12 EPWMA_ACT_LP
                volatile u32 ACT_UPDT:1;                //15    EPWMA_ACT_UPDT
                volatile u32 rsvd0:4;					//19:16 Reserved
                volatile u32 ACT_ETRG0:2;               //21:20 EPWMA_ACT_ETRG0
                volatile u32 ACT_ETRG1:2;               //23:22 EPWMA_ACT_ETRG1
                volatile u32 rsvd:8;                    //31:24 Reserved
        }bit;
};

union PWM_B_ACT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 ACT_CNT_Z:2;               //1:0   EPWMB_ACT_CNTZ
                volatile u32 ACT_CNT_PRD:2;             //3:2   EPWMB_ACT_CNTPRD
                volatile u32 ACT_CNT_UAV:2;             //5:4   EPWMB_ACT_CNTUAV
                volatile u32 ACT_CNT_DAV:2;             //7:6   EPWMB_ACT_CNTDAV
                volatile u32 ACT_CNT_UBV:2;             //9:8   EPWMB_ACT_CNTUBV
                volatile u32 ACT_CNT_DBV:2;             //11:10 EPWMB_ACT_CNTDBV
                volatile u32 ACT_LP:3;                  //14:12 EPWMB_ACT_LP
                volatile u32 ACT_UPDT:1;                //15    EPWMB_ACT_UPDT
                volatile u32 rsvd0:4;					//19:16 Reserved
                volatile u32 ACT_ETRG0:2;               //21:20 EPWMB_ACT_ETRG0
                volatile u32 ACT_ETRG1:2;               //23:22 EPWMB_ACT_ETRG1
                volatile u32 rsvd:8;                   //31:24 Reserved
        }bit;
};

union PWM_SW_ACT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 AACT_SW_OS:2;              //1:0   EPWMA_ACT_SW_OS
                volatile u32 AACT_SW_OS_EN:1;           //2     EPWMA_ACT_SW_OS_EN
                volatile u32 BACT_SW_OS:2;              //4:3   EPWMB_ACT_SW_OS
                volatile u32 BACT_SW_OS_EN:1;           //5     EPWMB_ACT_SW_OS_EN
                volatile u32 SW_CT_UPDT:3;              //8:6   EPWM_ACT_SW_CT_UPDT
                volatile u32 rsvd:23;                   //31:9  Reserved          
        }bit;
};

union PWM_SW_CT_ACT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 AACT_SW_CT:2;              //1:0   EPWMA_ACT_SW_CT
                volatile u32 BACT_SW_CT:2;              //3:2   EPWMB_ACT_SW_CT
                volatile u32 rsvd:28;                   //31:4  Reserved                            
        }bit;
};

union PWM_OUT_CONF_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 BYPASS_SET:2;              //1:0   EPWM_BP_SET[1:0]
                volatile u32 POL_SET:2;                 //3:2   EPWM_POL_SET[1:0]
                volatile u32 CH_SET:2;                  //5:4   EPWM_CH_SEL[1:0]
                volatile u32 RE_LP:2;					//7:6	EPWM_RE_LP
                volatile u32 FE_LP:2;					//9:8	EPWM_FE_LP
                volatile u32 RE_UPDT:1;					//10	EPWM_RE_UPDT
                volatile u32 FE_UPDT:1;					//11	EPWM_FE_UPDT
                volatile u32 SWAP_SEL:2;				//13:12	EPWM_SWAP_SEL
                volatile u32 DD_EN:1;					//14	EPWM_DD_EN
                volatile u32 rsvd0:1;					//15	Reserved
                volatile u32 DB_CTL_UPDT:1;				//16	EPWM_DB_CTL_UPDT
                volatile u32 DB_CTL_LP:2;				//18:17	EPWM_DB_CTL_LP
                volatile u32 rsvd:13;                   //31:19  Reserved
        }bit;
};

union PWM_RE_DZCTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 RE_DZCTL:15;               //14:0   EPWM_RE_DZCTL
                volatile u32 rsvd:17;                   //31:15 Reserved
        }bit;
};

union PWM_FE_DZCTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 FE_DZCTL:15;               //14:0   EPWM_FE_DZCTL
                volatile u32 rsvd:17;                   //31:15 Reserved
        }bit;
};

union PWM_CHOP_CONF_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CHOP_EN:1;                 //0     EPWM_CHOP_EN
                volatile u32 CHOP_OS_WTH:4;             //4:1   EPWM_CHOP_OS_WTH
                volatile u32 CHOP_FRE:3;                //7:5   EPWM_CHOP_FRE
                volatile u32 CHOP_DUTY:3;               //10:8  EPWM_CHOP_DUTY
                volatile u32 OSA_EN:1;                  //11    EPWM_OSA_EN           
                volatile u32 OSB_EN:1;                  //12    EPWM_OSB_EN  
                volatile u32 ALIGN_EN:1;                //13    EPWM_CHOP_ALIGN                        
                volatile u32 rsvd:18;                   //31:14 Reserved                             
        }bit;
};

union PWM_FAULT_IN_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 NREC_FAULT0_EN:1;          //0     EPWM_NREC_FLT0_EN
                volatile u32 NREC_FAULT1_EN:1;          //1     EPWM_NREC_FLT1_EN
                volatile u32 NREC_FAULT2_EN:1;          //2     EPWM_NREC_FLT2_EN
                volatile u32 NREC_FAULT3_EN:1;          //3     EPWM_NREC_FLT3_EN
                volatile u32 NREC_FAULT4_EN:1;          //4     EPWM_NREC_FLT4_EN
                volatile u32 NREC_FAULT5_EN:1;          //5     EPWM_NREC_FLT5_EN
                volatile u32 rsvd0:2;                   //7:6   Reserved
                volatile u32 REC_FAULT0_EN:1;           //8     EPWM_REC_FLT0_EN
                volatile u32 REC_FAULT1_EN:1;           //9     EPWM_REC_FLT1_EN
                volatile u32 REC_FAULT2_EN:1;           //10    EPWM_REC_FLT2_EN
                volatile u32 REC_FAULT3_EN:1;           //11    EPWM_REC_FLT3_EN
                volatile u32 REC_FAULT4_EN:1;           //12    EPWM_REC_FLT4_EN
                volatile u32 REC_FAULT5_EN:1;           //13    EPWM_REC_FLT5_EN
                volatile u32 rsvd1:2;                   //15:14 Reserved
                volatile u32 FAULT0_POL:1;              //16    EPWM_FLT0_IN_POL    
                volatile u32 FAULT1_POL:1;              //17    EPWM_FLT1_IN_POL 
                volatile u32 FAULT2_POL:1;              //18    EPWM_FLT2_IN_POL 
                volatile u32 FAULT3_POL:1;              //19    EPWM_FLT3_IN_POL                               
                volatile u32 FAULT4_POL:1;              //20    EPWM_FLT4_IN_POL 
                volatile u32 FAULT5_POL:1;              //21    EPWM_FLT5_IN_POL                
                volatile u32 rsvd2:10;                  //31:22 Reserved                           
        }bit;
};

union PWM_FAULT_PRTCT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 A_FAULT_PRTCT:2;           //1:0   EPWMA_FLT_PRTCT
                volatile u32 B_FAULT_PRTCT:2;           //3:2   EPWMB_FLT_PRTCT
                volatile u32 rsvd0:4;                   //7:4   Reserved
                volatile u32 A_FAULT_DLY:4;			    //11:8  EPWMA_FLT_PRTCT_DLY
                volatile u32 B_FAULT_DLY:4;			    //15:11 EPWMB_FLT_PRTCT_DLY
                volatile u32 A_INIT:2;                  //17:16 EPWMA_INIT                  
                volatile u32 B_INIT:2;                  //19:18 EPWMB_INIT               
                volatile u32 rsvd1:4;                   //23:20 Reserved
                volatile u32 UNIT_US_THR:8;             //31:24 UNIT_US_THR
        }bit;
};

union PWM_FAULT_INT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 rsvd0:1;                   //0     Reserved
                volatile u32 REC_FAULT_INT_EN:1;        //1     EPWM_REC_FLT_INT_EN
                volatile u32 NREC_FAULT_INT_EN:1;       //2     EPWM_NREC_FLT_INT_EN              
                volatile u32 rsvd1:29;                  //31:3  Reserved           
        }bit;
};

union PWM_FAULT_FLG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 FAULT_FLG:1;               //0     EPWM_FLT_INT_FLAG
                volatile u32 REC_FAULT_FLG:1;           //1     EPWM_REC_FLT_FLAG
                volatile u32 NREC_FAULT_FLG:1;          //2     EPWM_NREC_FLT_FLAG              
                volatile u32 rsvd1:29;                  //31:3  Reserved                              
        }bit;
};

union PWM_FAULT_CLR_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 FAULT_CLR:1;               //0     EPWM_FLT_CLR                
                volatile u32 REC_FAULT_CLR:1;           //1     EPWM_REC_FLT_CLR
                volatile u32 NREC_FAULT_CLR:1;          //2     EPWM_NREC_FLT_CLR     
                volatile u32 rsvd1:29;                  //31:3  Reserved                             
        }bit;
};

union PWM_SWFAULT_INT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 rsvd0:1;                   //0     Reserved   
                volatile u32 REC_SWFAULT_INT_EN:1;      //1     EPWM_SW_FRC_REC_FLT 
                volatile u32 NREC_SWFAULT_INT_EN:1;     //2     EPWM_SW_FRC_NREC_FLT                
                volatile u32 rsvd1:29;                  //31:3  Reserved                             
        }bit;
};

union PWM_ADC_INT_CTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_INT_SEL:4;             //3:0   EPWM_INT_SEL
                volatile u32 PWM_INT_EN:1;              //4     EPWM_INT_EN
                volatile u32 rsvd0:3;                   //7:5   Reserved
                volatile u32 ADC_CVRA_SEL:3;            //10:8  EPWM_ADC_CVRA_SEL
                volatile u32 ADC_CVRA_EN:1;             //11    EPWM_ADC_CVRA_EN
                volatile u32 ADC_CVRB_SEL:3;            //14:12 EPWM_ADC_CVRB_SEL
                volatile u32 ADC_CVRB_EN:1;             //15    EPWM_ADC_CVRB_EN
                volatile u32 CVRA_CPM_SRC:4;            //19:16 CVRA_CPM_SRC_SEL
                volatile u32 CVRB_CPM_SRC:4;            //23:20 CVRB_CPM_SRC_SEL                 
                volatile u32 rsvd1:8;                   //31:24 Reserved                             
        }bit;
};

union PWM_ADC_INT_PRE_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_INT_DIV:4;             //3:0   EPWM_INT_DIV
                volatile u32 PWM_INT_CNT:4;             //7:4   EPWM_INT_CNT
                volatile u32 ADC_CVRA_DIV:4;            //11:8   EPWM_ADC_CVRA_DIV
                volatile u32 ADC_CVRB_DIV:4;            //15:12 ADC_CVRB_DIV
                volatile u32 ADC_CVRA_CNT:4;            //19:16 ADC_CVRA_CNT
                volatile u32 ADC_CVRB_CNT:4;            //23:30 ADC_CVRB_CNT
                volatile u32 rsvd1:8;                   //31:24 Reserved
        }bit;
};

union PWM_EVNT_FLAG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_INT_FLG:1;             //0     EPWM_INT_FLAG
                volatile u32 rsvd0:1;                   //1     Reserved     
                volatile u32 ADC_CVRA_FLG:1;            //2     EPWM_ADC_CVRA_FLAG
                volatile u32 ADC_CVRB_FLG:1;            //3     EPWM_ADC_CVRB_FLAG 
                volatile u32 CVRC_FLAG:1;				//4		EPWM_CVRC_FLAG
                volatile u32 CVRD_FLAG:1;				//5		EPWM_CVRD_FLAG
                volatile u32 rsvd1:26;                  //31:6  Reserved
        }bit;
};

union PWM_EVNT_CLR_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_INT_CLR:1;             //0     EPWM_INT_CLR
                volatile u32 rsvd0:1;                   //1     Reserved   
                volatile u32 ADC_CVRA_CLR:1;            //2     EPWM_ADC_CVRA_CLR            
                volatile u32 ADC_CVRB_CLR:1;            //3     EPWM_ADC_CVRB_CLR  
                volatile u32 CVRC_CLR:1;				//4		EPWM_CVRC_CLR
                volatile u32 CVRD_CLR:1;				//5		EPWM_CVRD_CLR
                volatile u32 rsvd1:26;                  //31:6  Reserved
        }bit;
};

union PWM_SW_FRC_EVNT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_SW_FRC_INT:1;          //0     EPWM_SW_FRC_INT       
                volatile u32 rsvd0:1;                   //1     Reserved
                volatile u32 SW_FRC_ADC_CVRA:1;         //2     EPWM_SW_FRC_ADC_CVRA
                volatile u32 SW_FRC_ADC_CVRB:1;         //3     EPWM_SW_FRC_ADC_CVRB
                volatile u32 SW_FRC_CVRC:1;				//4		EPWM_SW_FRC_CVRC
                volatile u32 SW_FRC_CVRD:1;				//5		EPWM_SW_FRC_CVRD
                volatile u32 rsvd1:26;                  //31:4  Reserved
        }bit;
};

union PWM_FLT_INCTL2_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 REC_SDFM0_COHS_EN:1;          //0     REC_SDFM0_COHS_EN
                volatile u32 REC_SDFM0_COLS_EN:1;          //1     REC_SDFM0_COLS_EN
                volatile u32 REC_SDFM0_COHLS_EN:1;         //2     REC_SDFM0_COHLS_EN
                volatile u32 REC_SDFM0_Z_EN:1;         	   //3     REC_SDFM0_Z_EN
                volatile u32 REC_SDFM1_COHS_EN:1;          //4     REC_SDFM1_COHS_EN
                volatile u32 REC_SDFM1_COLS_EN:1;          //5     REC_SDFM1_COLS_EN
                volatile u32 REC_SDFM1_COHLS_EN:1;         //6     REC_SDFM1_COHLS_EN
                volatile u32 REC_SDFM1_Z_EN:1;         	   //7     REC_SDFM1_Z_EN
                volatile u32 REC_SDFM2_COHS_EN:1;          //8     REC_SDFM2_COHS_EN
                volatile u32 REC_SDFM2_COLS_EN:1;          //9     REC_SDFM2_COLS_EN
                volatile u32 REC_SDFM2_COHLS_EN:1;         //10    REC_SDFM2_COHLS_EN
                volatile u32 REC_SDFM2_Z_EN:1;         	   //11    REC_SDFM2_Z_EN
                volatile u32 REC_SDFM3_COHS_EN:1;          //12    REC_SDFM3_COHS_EN
                volatile u32 REC_SDFM3_COLS_EN:1;          //13    REC_SDFM3_COLS_EN
                volatile u32 REC_SDFM3_COHLS_EN:1;         //14    REC_SDFM3_COHLS_EN
                volatile u32 REC_SDFM3_Z_EN:1;         	   //15    REC_SDFM3_Z_EN
                volatile u32 NREC_SDFM0_COHS_EN:1;         //16    NREC_SDFM0_COHS_EN
                volatile u32 NREC_SDFM0_COLS_EN:1;         //17    NREC_SDFM0_COLS_EN
                volatile u32 NREC_SDFM0_COHLS_EN:1;        //18    NREC_SDFM0_COHLS_EN
                volatile u32 NREC_SDFM0_Z_EN:1;            //19    NREC_SDFM0_Z_EN
                volatile u32 NREC_SDFM1_COHS_EN:1;         //20    NREC_SDFM1_COHS_EN
                volatile u32 NREC_SDFM1_COLS_EN:1;         //21    NREC_SDFM1_COLS_EN
                volatile u32 NREC_SDFM1_COHLS_EN:1;        //22    NREC_SDFM1_COHLS_EN
                volatile u32 NREC_SDFM1_Z_EN:1;            //23    NREC_SDFM1_Z_EN
                volatile u32 NREC_SDFM2_COHS_EN:1;         //24    NREC_SDFM2_COHS_EN
                volatile u32 NREC_SDFM2_COLS_EN:1;         //25    NREC_SDFM2_COLS_EN
                volatile u32 NREC_SDFM2_COHLS_EN:1;        //26    NREC_SDFM2_COHLS_EN
                volatile u32 NREC_SDFM2_Z_EN:1;            //27    NREC_SDFM2_Z_EN
                volatile u32 NREC_SDFM3_COHS_EN:1;         //28    NREC_SDFM3_COHS_EN
                volatile u32 NREC_SDFM3_COLS_EN:1;         //29    NREC_SDFM3_COLS_EN
                volatile u32 NREC_SDFM3_COHLS_EN:1;        //30    NREC_SDFM3_COHLS_EN
                volatile u32 NREC_SDFM3_Z_EN:1;            //31    NREC_SDFM3_Z_EN
        }bit;
};


union PWM_HCL_UPDT_EN_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 HCL_DUT_NUM:2;             //1:0   EPWM_HCL_DUT_NUM_SEL
                volatile u32 HCL_AXI_SEL:1;             //2     EPWM_HCL_AXI_SEL         
                volatile u32 HCL_UPDT_EN:1;             //3     EPWM_HCL_DUTY_UPDT_EN
                volatile u32 rsvd0:28;                  //31:4  Reserved                  
        }bit;
};

union PWM_HRPWM_CTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 HRPWM_EN:1;                //0     HRPWM_EN
                volatile u32 HRPWM_AOUT_LOG:1;			//1		HRPWM_AOUT_LOG
                volatile u32 HRPWM_BOUT_LOG:1;			//2		HRPWM_BOUT_LOG
                volatile u32 HRPWM_VAL_UPDT_MOD:1;		//3		HRPWM_VAL_UPDT_MOD
                volatile u32 HRPWM_VAL_LP:4;			//7:4	HRPWM_VAL_LP
                volatile u32 HRPWM_PRD_FRA_RPT:5;		//12:8	HRPWM_PRD_FRA_RPT
                volatile u32 rsvd0:3;					//15:13	Reserved
                volatile u32 HRPWM_FRA_EN:1;			//16	HRPWM_FRA_EN
                volatile u32 HRPWM_COMPA_EN:1;			//17	HRPWM_COMPA_EN
                volatile u32 HRPWM_COMPB_EN:1;			//18	HRPWM_COMPB_EN
                volatile u32 HRPWM_PRD_UPDT_MOD:1;		//19	HRPWM_PRD_UPDT_MOD
                volatile u32 HRPWM_PRD_VAL_LP:4;		//23:20	HRPWM_PRD_VAL_LP
                volatile u32 HRPWM_FRA_CNT:5;			//28:24	HRPWM_FRA_CNT
                volatile u32 rsvd1:2;                   //30:29 Reserved
        }bit;
};

union PWM_HRPWMA_CFG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 HRPWM_AP_DLY:5;            //4:0   HRPWM_AP_DLY
                volatile u32 rsvd0:3;                   //7:5   Reserved
                volatile u32 HRPWM_AN_DLY:5;            //12:8  HRPWM_AN_DLY
                volatile u32 rsvd1:19;                  //31:13 Reserved
        }bit;
};

union PWM_HRPWMB_CFG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 HRPWM_BP_DLY:5;            //4:0   HRPWM_BP_DLY
                volatile u32 rsvd0:3;                   //7:5   Reserved
                volatile u32 HRPWM_BN_DLY:5;            //12:8  HRPWM_BN_DLY
                volatile u32 rsvd1:19;                  //31:13 Reserved
        }bit;
};

union PWM_HRPRD_SET_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 HRPWM_PRD_FRA_CFG:5;       //4:0 HRPWM_PRD_FRA_CFG
                volatile u32 rsvd0:27;          		//31:5 Reserved
        }bit;
};


union PWM_CNT_CV_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_CV:16;                 //15:0  EPWM_CNT_CV
                volatile u32 rsvd:16;                   //31:16 Reserved
        }bit;
};

union PWM_CNT_DV_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_DV:16;                 //15:0  EPWM_CNT_DV
                volatile u32 rsvd:16;                   //31:16 Reserved
        }bit;
};

union PWM_CVRCD_CTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_CVRC_SEL:4;            //3:0   PWM_CVRC_SEL
                volatile u32 rsvd0:3;                   //6:4   Reserved
                volatile u32 PWM_CVRC_EN:1;             //7     PWM_CVRC_EN
                volatile u32 PWM_CVRD_SEL:4;            //11:8  PWM_CVRD_SEL
                volatile u32 rsvd1:3;                   //14:12 Reserved
                volatile u32 PWM_CVRD_EN:1;             //15    PWM_CVRD_EN
                volatile u32 PWM_CVRC_DIV:4;            //19:16 PWM_CVRC_DIV
                volatile u32 PWM_CVRD_DIV:4;            //23:20 PWM_CVRD_DIV
                volatile u32 PWM_CMPC_LP:3;             //26:24 PWM_CMPC_LP
                volatile u32 PWM_CMPD_LP:3;             //29:27 PWM_CMPD_LP
                volatile u32 PWM_CNT_CMPC_UPDT:1;       //30 PWM_CNT_CMPC_UPDT
                volatile u32 PWM_CNT_CMPD_UPDT:1;       //31 PWM_CNT_CMPD_UPDT
        }bit;
};

union PWM_PSHPLL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PWM_PHSPLL_EN:1;           //0     PWM_PHSPLL_EN
                volatile u32 PP_CTL_INV_EN:1;           //1     PP_CTL_INV_EN
                volatile u32 AP_IDLE:1;                 //2     AP_IDLE
                volatile u32 BP_IDLE:1;           	    //3     BP_IDLE
                volatile u32 rsvd0:28;                  //31:4  Reserved
        }bit;
};


union PWM_PUL_OUT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 PUL_OUT_EN:1;              //0     EPWM_PUL_OUT_EN
                volatile u32 rsvd0:3;             		//3:1   Reserved
                volatile u32 PUL_SW_UPDT:1;             //4     EPWM_PUL_SW_UPDT
                volatile u32 rsvd1:27;                  //31:5  Reserved
        }bit;
};

union PWM_DMA_CFG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 DMA_EN:1;                  //0     DMA_EN
                volatile u32 DMA_MAP_EN:1;				//1		DMA_MAP_EN
                volatile u32 rsvd0:2;					//3:2	Reserved
                volatile u32 DMA_REQ_SRC:4;             //7:4   DMA_REQ_SRC
                volatile u32 DMA_CYC_NUM:3;				//10:8	DMA_CYC_NUM
                volatile u32 rsvd1:21;                  //31:11  Reserved
        }bit;
};


union PWM_NRCFLT_IN_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CPM0_COH_EN:1;             //0     EPWM_NREC_CPM0_COH_EN
                volatile u32 CPM0_COL_EN:1;             //1     EPWM_NREC_CPM0_COL_EN
                volatile u32 CPM0_COHL_EN:1;            //2     EPWM_NREC_CPM0_COHL_EN
                volatile u32 rsvd0:1;                   //3     Reserved
                volatile u32 CPM1_COH_EN:1;             //4     EPWM_NREC_CPM1_COH_EN
                volatile u32 CPM1_COL_EN:1;             //5     EPWM_NREC_CPM1_COL_EN
                volatile u32 CPM1_COHL_EN:1;            //6     EPWM_NREC_CPM1_COHL_EN
                volatile u32 rsvd1:1;                   //7     Reserved
                volatile u32 SDFM0_COH_EN:1;            //8     EPWM_NREC_SDFM0_COH_EN
                volatile u32 SDFM0_COL_EN:1;            //9     EPWM_NREC_SDFM0_COL_EN
                volatile u32 SDFM0_COHL_EN:1;           //10    EPWM_NREC_SDFM0_COHL_EN
                volatile u32 rsvd2:1;                   //11    Reserved                
                volatile u32 SDFM1_COH_EN:1;            //12    EPWM_NREC_SDFM1_COH_EN
                volatile u32 SDFM1_COL_EN:1;            //13    EPWM_NREC_SDFM1_COL_EN
                volatile u32 SDFM1_COHL_EN:1;           //14    EPWM_NREC_SDFM1_COHL_EN
                volatile u32 rsvd3:1;                   //15    Reserved          
                volatile u32 SDFM2_COH_EN:1;            //16    EPWM_NREC_SDFM2_COH_EN
                volatile u32 SDFM2_COL_EN:1;            //17    EPWM_NREC_SDFM2_COL_EN
                volatile u32 SDFM2_COHL_EN:1;           //18    EPWM_NREC_SDFM2_COHL_EN
                volatile u32 rsvd4:1;                   //19    Reserved 
                volatile u32 SDFM3_COH_EN:1;            //20    EPWM_NREC_SDFM3_COH_EN
                volatile u32 SDFM3_COL_EN:1;            //21    EPWM_NREC_SDFM3_COL_EN
                volatile u32 SDFM3_COHL_EN:1;           //22    EPWM_NREC_SDFM3_COHL_EN
                volatile u32 rsvd5:1;                   //23    Reserved 
                volatile u32 DBG_HOLD_EN:1;             //24    EPWM_DBG_HOLD_EN
                volatile u32 ADC0_WDG0_EN:1;            //25    EPWM_NREC_ADC0_WDG0_EN
                volatile u32 ADC0_WDG1_EN:1;            //26    EPWM_NREC_ADC0_WDG1_EN
                volatile u32 ADC0_WDG2_EN:1;            //27    EPWM_NREC_ADC0_WDG2_EN
                volatile u32 ADC1_WDG0_EN:1;            //28    EPWM_NREC_ADC1_WDG0_EN
                volatile u32 ADC1_WDG1_EN:1;            //29    EPWM_NREC_ADC1_WDG1_EN
                volatile u32 ADC1_WDG2_EN:1;            //30    EPWM_NREC_ADC1_WDG2_EN
                volatile u32 rsvd6:1;                   //31    Reserved
        }bit;
};

union PWM_RCFLT_IN_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CPM0_COH_EN:1;             //0     EPWM_REC_CPM0_COH_EN
                volatile u32 CPM0_COL_EN:1;             //1     EPWM_REC_CPM0_COL_EN
                volatile u32 CPM0_COHL_EN:1;            //2     EPWM_REC_CPM0_COHL_EN
                volatile u32 rsvd0:1;                   //3     Reserved
                volatile u32 CPM1_COH_EN:1;             //4     EPWM_REC_CPM1_COH_EN
                volatile u32 CPM1_COL_EN:1;             //5     EPWM_REC_CPM1_COL_EN
                volatile u32 CPM1_COHL_EN:1;            //6     EPWM_REC_CPM1_COHL_EN
                volatile u32 rsvd1:1;                   //7     Reserved
                volatile u32 SDFM0_COH_EN:1;            //8     EPWM_REC_SDFM0_COH_EN
                volatile u32 SDFM0_COL_EN:1;            //9     EPWM_REC_SDFM0_COL_EN
                volatile u32 SDFM0_COHL_EN:1;           //10    EPWM_REC_SDFM0_COHL_EN
                volatile u32 rsvd2:1;                   //11    Reserved                
                volatile u32 SDFM1_COH_EN:1;            //12    EPWM_REC_SDFM1_COH_EN
                volatile u32 SDFM1_COL_EN:1;            //13    EPWM_REC_SDFM1_COL_EN
                volatile u32 SDFM1_COHL_EN:1;           //14    EPWM_REC_SDFM1_COHL_EN
                volatile u32 rsvd3:1;                   //15    Reserved          
                volatile u32 SDFM2_COH_EN:1;            //16    EPWM_REC_SDFM2_COH_EN
                volatile u32 SDFM2_COL_EN:1;            //17    EPWM_REC_SDFM2_COL_EN
                volatile u32 SDFM2_COHL_EN:1;           //18    EPWM_REC_SDFM2_COHL_EN
                volatile u32 rsvd4:1;                   //19    Reserved 
                volatile u32 SDFM3_COH_EN:1;            //20    EPWM_REC_SDFM3_COH_EN
                volatile u32 SDFM3_COL_EN:1;            //21    EPWM_REC_SDFM3_COL_EN
                volatile u32 SDFM3_COHL_EN:1;           //22    EPWM_REC_SDFM3_COHL_EN
                volatile u32 rsvd5:2;                   //24:23 Reserved
                volatile u32 ADC0_WDG0_EN:1;            //25    EPWM_REC_ADC0_WDG0_EN
                volatile u32 ADC0_WDG1_EN:1;            //26    EPWM_REC_ADC0_WDG1_EN
                volatile u32 ADC0_WDG2_EN:1;            //27    EPWM_REC_ADC0_WDG2_EN
                volatile u32 ADC1_WDG0_EN:1;            //28    EPWM_REC_ADC1_WDG0_EN
                volatile u32 ADC1_WDG1_EN:1;            //29    EPWM_REC_ADC1_WDG1_EN
                volatile u32 ADC1_WDG2_EN:1;            //30    EPWM_REC_ADC1_WDG2_EN
                volatile u32 rsvd6:1;                   //31    Reserved
        }bit;
};

union PWM_SC_SCTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 rsvd0:8;                   //7:0   Reserved
                volatile u32 CPM_SYNC_SRC:3;            //10:8  EPWM_CPM_SRC_SEL
                volatile u32 CPM_SYNC_EN:1;             //11    EPWM_CPM_SYNC_EN
                volatile u32 SDFM_SYNC_SRC:3;           //14:12 EPWM_SDFM_SRC_SEL
                volatile u32 SDFM_SYNC_EN:1;            //15    EPWM_SDFM_SYNC_EN
                volatile u32 rsvd1:16;                   //31:16 Reserved  
        }bit;
};

union PWM_SC_SDIV_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CPM_SYNC_DIV:2;            //1:0   EPWM_CPM_SYNC_DIV
                volatile u32 CPM_SYNC_CNT:2;            //3:2   EPWM_CPM_SYNC_CNT
                volatile u32 SDFM_SYNC_DIV:2;           //5:4   EPWM_SDFMM_SYNC_DIV
                volatile u32 SDFM_SYNC_CNT:2;           //7:6   EPWM_SDFM_SYNC_CNT
                volatile u32 rsvd1:24;                  //31:8  Reserved  
        }bit;
};

union PWM_ETRG0_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 ETRG0_SRC_SEL:5;           //4:0   ETRG0_SRC_SEL
                volatile u32 ETRG0_SRC_POL:2;           //6:5   ETRG0_SRC_POL
                volatile u32 ETRG0_SYNC_EN:1;           //7     ETRG0_SYNC_EN
                volatile u32 ETRG0_FLT_MOD:2;           //9:8   ETRG0_FLT_MOD
                volatile u32 rsvd1:2;                   //11:10 Reserved
                volatile u32 ETRG0_FLT_ST:4;            //15:12 ETRG0_FLT_ST
                volatile u32 ETRG0_FLT_LEN:16;          //31:16 ETRG0_FLT_LEN
        }bit;
};

union PWM_ETRG1_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 ETRG1_SRC_SEL:5;           //4:0   ETRG1_SRC_SEL
                volatile u32 ETRG1_SRC_POL:2;           //6:5   ETRG1_SRC_POL
                volatile u32 ETRG1_SYNC_EN:1;           //7     ETRG0_SYNC_EN
                volatile u32 ETRG1_FLT_MOD:2;           //9:8   ETRG1_FLT_MOD
                volatile u32 rsvd1:2;                   //11:10 Reserved
                volatile u32 ETRG1_FLT_ST:4;            //15:12 ETRG1_FLT_ST
                volatile u32 ETRG1_FLT_LEN:16;          //31:16 ETRG1_FLT_LEN
        }bit;
};

union PWM_ETRG_ACC_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 ETRG0_ACC_EN:1;            //0     ETRG0_ACC_EN
                volatile u32 ETRG0_ACC_MOD:1;           //1     ETRG0_ACC_MOD
                volatile u32 rsvd0:6;                   //7:2   Reserved
                volatile u32 ETRG0_ACC_TH:8;            //15:8  ETRG0_ACC_TH
                volatile u32 ETRG1_ACC_EN:1;            //16    ETRG1_ACC_EN
                volatile u32 ETRG1_ACC_MOD:1;           //17    ETRG1_ACC_MOD
                volatile u32 rsvd1:6;                   //23:18 Reserved
                volatile u32 ETRG1_ACC_TH:8;            //31:24 ETRG1_ACC_TH
        }bit;
};

union PWM_GLB_CTL_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 GLB_UPDT_EN:1;            	//0     GLB_UPDT_EN
                volatile u32 GLB_LP:4;           		//4:1   GLB_LP
                volatile u32 GLB_OS_EN:1;               //5   	GLB_OS_EN
                volatile u32 rsvd0:1;					//6		Reserved
                volatile u32 GLB_LP_DIV:3;            	//9:7   GLB_LP_DIV
                volatile u32 GLB_LP_CNT:3;            	//12:10 GLB_LP_CNT
                volatile u32 rsvd1:19;                   //31:13 Reserved
        }bit;
};

union PWM_GLB_CTL2_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 GLB_OS_UPDT:1;            	//0   GLB_OS_UPDT
                volatile u32 SW_FRC_GLB_UPDT:1;         //1   SW_FRC_GLB_UPDT
                volatile u32 rsvd0:30;                  //31:2 Reserved
        }bit;
};

union PWM_GLB_CFG_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 CNT_PRD_GLBE:1;       		//0		CNT_PRD_GLBE
                volatile u32 CNT_CMPA_GLBE:1;      		//1   	CNT_CMPA_GLBE
                volatile u32 CNT_CMPB_GLBE:1;      		//2   	CNT_CMPB_GLBE
                volatile u32 PWMA_ACT_GLBE:1;			//3		PWMA_ACT_GLBE
                volatile u32 PWMB_ACT_GLBE:1;     		//4   	PWMB_ACT_GLBE
                volatile u32 ACT_SW_CT_GLBE:1;     		//5 	ACT_SW_CT_GLBE
                volatile u32 DB_CTL_GLBE:1;    			//6 	DB_CTL_GLBE
                volatile u32 CNT_CMPC_GLBE:1;			//7		CNT_CMPC_GLBE
                volatile u32 CNT_CMPD_GLBE:1;			//8		CNT_CMPD_GLBE
                volatile u32 HRPWM_VAL_GLBE:1;			//9		HRPWM_VAL_GLBE
                volatile u32 HRPWM_PRD_GLBE:1;			//10	HRPWM_PRD_GLBE
                volatile u32 RE_DZCTL_GLBE:1;			//11	RE_DZCTL_GLBE
                volatile u32 FE_DZCTL_GLBE:1;			//12	FE_DZCTL_GLBE
                volatile u32 rsvd0:19;					//31:13 Reserved
        }bit;
};

union PWM_LINK_CTL_REG {
		volatile u32 all;
		struct {
				volatile u32 CNT_PRD_LINK:4;			//3:0	CNT_PRD_LINK
				volatile u32 CNT_AV_LINK:4;				//7:4	CNT_AV_LINK
				volatile u32 CNT_BV_LINK:4;				//11:8	CNT_BV_LINK
				volatile u32 RE_DZCTL_LINK:4;			//15:12	RE_DZCTL_LINK
				volatile u32 FE_DZCTL_LINK:4;			//19:16	FE_DZCTL_LINK
				volatile u32 GLB_CTL2_LINK:4;			//23:20	GLB_CTL2_LINK
				volatile u32 HRPWM_PRD_SET_LINK:4;		//27:24	HRPWM_PRD_SET_LINK
				volatile u32 rsvd0:4;					//31:28 Reserved
		}bit;
};

union PWM_ETRG_DLY_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 ETRG0_DLY_SET:10;          //9:0	ETRG0_DLY_SET
                volatile u32 rsvd0:6;                   //15:10	Reserved
                volatile u32 ETRG1_DLY_SET:10;          //25:16	ETRG1_DLY_SET
                volatile u32 rsvd1:6;                   //31:26	Reserved
        }bit;
};

union PWM_DMA_MAP0_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 DMA_CNT0_MAP:8;          //7:0		DMA_CNT0_MAP
                volatile u32 DMA_CNT1_MAP:8;          //15:8	DMA_CNT1_MAP
                volatile u32 DMA_CNT2_MAP:8;          //23:16	DMA_CNT2_MAP
                volatile u32 DMA_CNT3_MAP:8;          //31:24	DMA_CNT3_MAP
        }bit;
};

union PWM_DMA_MAP1_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 DMA_CNT4_MAP:8;          //7:0		DMA_CNT4_MAP
                volatile u32 DMA_CNT5_MAP:8;          //15:8	DMA_CNT5_MAP
                volatile u32 DMA_CNT6_MAP:8;          //23:16	DMA_CNT6_MAP
                volatile u32 DMA_CNT7_MAP:8;          //31:24	DMA_CNT7_MAP
        }bit;
};

union PWM_TRG_OUT_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 TRIG_SEL:4;                //3:0   EPWM_CNT_TRIG_SEL
                volatile u32 TRG_OUT_INV_EN:1;			//4		TRG_OUT_INV_EN
                volatile u32 rsvd0:27;                  //31:5  Reserved
        }bit;
};


struct EPWM_REGS {
        union   PWM_CNT_PRDV_REG            PWM_CNT_PRDV;              //offset: 0x00                     
        union   PWM_CNT_PHV_REG             PWM_CNT_PHV;               //offset: 0x04                        
        union   PWM_CNT_V_REG               PWM_CNT_V;                 //offset: 0x08                        
        union   PWM_CNT_CFG_REG             PWM_CNT_CFG;               //offset: 0x0C
        union   PWM_CNT_STS_REG             PWM_CNT_STS;               //offset: 0x10
        union   PWM_CNT_AV_REG              PWM_CNT_AV;                //offset: 0x14
        union   PWM_CNT_BV_REG              PWM_CNT_BV;                //offset: 0x18
        union   PWM_UPDT_MODE_REG           PWM_UPDT_MODE;             //offset: 0x1C
        union   PWM_A_ACT_REG               PWM_A_ACT;                 //offset: 0x20
        union   PWM_B_ACT_REG               PWM_B_ACT;                 //offset: 0x24
        union   PWM_SW_ACT_REG              PWM_SW_ACT;                //offset: 0x28        
        union   PWM_SW_CT_ACT_REG           PWM_SW_CT_ACT;             //offset: 0x2C
        union   PWM_OUT_CONF_REG            PWM_OUT_CONF;              //offset: 0x30
        union   PWM_RE_DZCTL_REG            PWM_RE_DZCTL;              //offset: 0x34
        union   PWM_FE_DZCTL_REG            PWM_FE_DZCTL;              //offset: 0x38
        union   PWM_CHOP_CONF_REG           PWM_CHOP_CONF;             //offset: 0x3C
        union   PWM_FAULT_IN_REG            PWM_FAULT_IN;              //offset: 0x40
        union   PWM_FAULT_PRTCT_REG         PWM_FAULT_PRTCT;           //offset: 0x44
        union   PWM_FAULT_INT_REG           PWM_FAULT_INT;             //offset: 0x48
        union   PWM_FAULT_FLG_REG           PWM_FAULT_FLG;             //offset: 0x4C
        union   PWM_FAULT_CLR_REG           PWM_FAULT_CLR;             //offset: 0x50
        union   PWM_SWFAULT_INT_REG         PWM_SWFAULT_INT;           //offset: 0x54
        union   PWM_ADC_INT_CTL_REG         PWM_ADC_INT_CTL;           //offset: 0x58
        union   PWM_ADC_INT_PRE_REG         PWM_ADC_INT_PRE;           //offset: 0x5C
        union   PWM_EVNT_FLAG_REG           PWM_EVNT_FLAG;             //offset: 0x60
        union   PWM_EVNT_CLR_REG            PWM_EVNT_CLR;              //offset: 0x64
        union   PWM_SW_FRC_EVNT_REG         PWM_SW_FRC_EVNT;           //offset: 0x68
        union	PWM_FLT_INCTL2_REG			PWM_FLT_INCTL2;			   //offset: 0x6C
        volatile   u32  RES0[3];                                       //offset: 0x70\0x74\0x78
        union   PWM_HCL_UPDT_EN_REG         PWM_HCL_UPDT_EN;           //offset: 0x7C
        union   PWM_HRPWM_CTL_REG           PWM_HRPWM_CTL;              //offset: 0x80
        union   PWM_HRPWMA_CFG_REG          PWM_HRPWMA_CFG;            //offset: 0x84
        union   PWM_HRPWMB_CFG_REG         	PWM_HRPWMB_CFG;            //offset: 0x88
        union   PWM_HRPRD_SET_REG           PWM_HRPRD_SET;             //offset: 0x8C
        union   PWM_CNT_CV_REG              PWM_CNT_CV;                //offset: 0x90
        union   PWM_CNT_DV_REG              PWM_CNT_DV;                //offset: 0x94
        union   PWM_CVRCD_CTL_REG			PWM_CVRCD_CTL;			   //offset: 0x98
        union   PWM_PSHPLL_REG				PWM_PSHPLL;				   //offset: 0x9C
        union   PWM_PUL_OUT_REG             PWM_PUL_OUT;               //offset: 0xA0 
        volatile   u32                      PWM_PUL_OUT_NUM;           //offset: 0xA4
        union   PWM_DMA_CFG_REG             PWM_DMA_CFG;               //offset: 0xA8
        volatile   u32  RES3[1];                                       //offset: 0xAC
        union   PWM_NRCFLT_IN_REG           PWM_NRCFLT_IN;             //offset: 0xB0 
        union   PWM_RCFLT_IN_REG            PWM_RCFLT_IN;              //offset: 0xB4
        union   PWM_SC_SCTL_REG             PWM_SC_SCTL;               //offset: 0xB8
        union   PWM_SC_SDIV_REG             PWM_SC_SDIV;               //offset: 0xBC
        union   PWM_ETRG0_REG               PWM_ETRG0;                 //offset: 0xC0
        union   PWM_ETRG1_REG               PWM_ETRG1;                 //offset: 0xC4
        union   PWM_ETRG_ACC_REG            PWM_ETRG_ACC;              //offset: 0xC8
        union	PWM_GLB_CTL_REG				PWM_GLB_CTL;			   //offset: 0xCC
		union	PWM_GLB_CTL2_REG			PWM_GLB_CTL2;			   //offset: 0xD0
		union	PWM_GLB_CFG_REG				PWM_GLB_CFG;			   //offset: 0xD4
		union	PWM_LINK_CTL_REG			PWM_LINK_CTL;			   //offset: 0xD8
		union	PWM_ETRG_DLY_REG			PWM_ETRG_DLY;			   //offset: 0xDC
		volatile	u32						PWM_DMA_ENTRY;			   //offset: 0xE0
		union	PWM_DMA_MAP0_REG			PWM_DMA_MAP0;			   //offset: 0xE4
		union	PWM_DMA_MAP1_REG			PWM_DMA_MAP1;			   //offset: 0xE8
        volatile   u32  RES4[1];                                       //offset: 0xEC
        union   PWM_TRG_OUT_REG             PWM_TRG_OUT;               //offset: 0xF0

};

void epwm0_irq_handler(void);
void epwm1_irq_handler(void);
void epwm2_irq_handler(void);
void epwm3_irq_handler(void);
void epwm4_irq_handler(void);
void epwm5_irq_handler(void);
void epwm6_irq_handler(void);
void epwm7_irq_handler(void);
void epwm8_irq_handler(void);
void epwm9_irq_handler(void);
void epwm10_irq_handler(void);
void epwm11_irq_handler(void);
void epwm_irq_register(u32 num, cpu_irq_fun_t irqhandle);
void epwm_irq_unregister(u32 num);
void epwm_fault_irq_handler(void);
void epwm_fault_irq_register(cpu_irq_fun_t irqhandle);
void epwm_fault_irq_unregister(void);
void epwm_comp_ch_init(u8 i, u32 prd, u32 dz);
void epwm_interrupt_init(u8 i, u32 src);
void epwm_cvra_init(u8 i, u32 src);
void epwm_cvrb_init(u8 i, u32 src);
void epwm_bldc_init(u8 i, u16 periodmax);
void epwm_bldc_pwm_ch_set(u8 i, u16 cmpa);
void epwm_bldc_on_ch_set(u8 i);
void epwm_bldc_off_ch_set(u8 i);
void epwm_set_pul_num(u8 i, u32 tx_num);
void epwm_set_prd(u8 i, u32 prd);
void epwm_pul_out_en(u8 i);
void epwm_pul_out_dis(u8 i);
void epwm_set_swct_act(u8 i, u32 src, SW_CT_TYPE a_act, SW_CT_TYPE b_act);
void epwm_set_quad_out_typ0(u8 i);
void epwm_set_quad_out_typ1(u8 i);
void epwm_set_pul_dir_l(u8 i);
void epwm_set_pul_dir_h(u8 i);
void epwm_set_pul_cw(u8 i);
void epwm_set_pul_ccw(u8 i);
void epwm_int_clr(u8 i);
void epwm_link_none(u8 i);
#endif /* INCLUDE_HAL_EPWM_H_ */
