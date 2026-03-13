/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_QOUT_H_
#define INCLUDE_HAL_QOUT_H_

typedef enum {
        FORWARD = 2,
        BACKWARD,
}QOUT_SW_DIR_TYP;

typedef enum {
        SRC_QEP0 = 0,
        SRC_QEP1,
        SRC_QEP2,
        SRC_QEP3,
        SRC_QEP4,
        SRC_QEP5,
        SRC_QEP6,
        SRC_QEP7,
        SRC_QEP8,
        SRC_QEP9,
        SRC_TA0,
        SRC_TA1,
        SRC_BISS0,
        SRC_BISS00,
        SRC_EDT0,
        SRC_EDT1,
		QOUT_SRC_REG,
} QOUT_SRC_TYPE;

typedef enum {
        QOUT_EPWM0 = 0,
		QOUT_EPWM1,
		QOUT_EPWM2,
		QOUT_EPWM3,
		QOUT_EPWM4,
		QOUT_EPWM5,
		QOUT_EPWM6,
		QOUT_EPWM7,
		QOUT_EPWM8,
		QOUT_EPWM9,
		QOUT_EPWM10,
		QOUT_EPWM11,
        QOUT_NOLINK,
} QOUT_LINK_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union QOUT_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 GLB_EN:1;                          //0     QOUT_GLB_EN
                volatile u32 rsvd0:1;                           //1     Reserved
                volatile u32 ERR_CANCL_EN:1;                    //2     QOUT_ERR_CANCL_EN
                volatile u32 PUL_HOMO_EN:1;						//3		PUL_HOMO_EN
                volatile u32 rsvd1:12;							//15:4	Reserved
                volatile u32 QOUT_TMR_PRD_LINK:4;				//19:16 QOUT_TMR_PRD_LINK
                volatile u32 rsvd2:12;                          //31:3  Reserved
        }bit;
};

union QOUT_CFG_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 TMR_FRE_DIV:4;                     //3:0   QOUT_TMR_FRE_DIV
                volatile u32 rsvd0:4;                           //7:4   Reserved
                volatile u32 POS_SRC_SEL:5;                     //12:8  QOUT_POS_SRC_SEL
                volatile u32 rsvd1:3;                           //15:13 Reserved
                volatile u32 OP_MOD:1;                          //16    QOUT_OP_MOD  
                volatile u32 QOUT_TMR_SYNC_EN:1;				//17	QOUT_TMR_SYNC_EN
                volatile u32 QOUT_TMR_SYNC_SEL:1;				//18	QOUT_TMR_SYNC_SEL
                volatile u32 rsvd2:13;                          //31:19 Reserved
        }bit;
};

union QOUT_INT_EN_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 TMR_INT_EN:1;                      //0     QOUT_TMR_INT_EN
                volatile u32 PUL_OVFL_INT_EN:1;                 //1     QOUT_PUL_OVFL_INT_EN 
                volatile u32 rsvd0:30;                          //31:2 Reserved        
        }bit;
};

union QOUT_STS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 TMR_STS:1;                         //0     QOUT_TMR_STS
                volatile u32 PUL_OVFL_STS:1;                    //1     QOUT_PUL_OVFL_STS
                volatile u32 rsvd0:30;                          //31:2 Reserved        
        }bit;
};

union QOUT_ABZ_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 A_EN:1;                            //0     QOUT_A_EN
                volatile u32 A_INV_EN:1;                        //1     QOUT_A_INV_EN
                volatile u32 B_EN:1;                            //2     QOUT_B_EN
                volatile u32 B_INV_EN:1;                        //3     QOUT_B_INV_EN
                volatile u32 Z_EN:1;                            //4     QOUT_Z_EN
                volatile u32 Z_INV_EN:1;                        //5     QOUT_Z_INV_EN
                volatile u32 Z_EXT_EN:1;						//6		Z_EXT_EN
                volatile u32 Z_EXT_EDG_SET:1;					//7		Z_EXT_EDG_SET
                volatile u32 rsvd0:8;                          //15:8 	Reserved
                volatile u32 T_ZEXT:5;							//20:16	T_ZEXT
                volatile u32 rsvd1:11;                          //31:21 	Reserved
        }bit;
};

union QOUT_IN_PUL_NUM_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 IN_PUL_NUM:10;                     //9:0   QOUT_IN_PUL_NUM              
                volatile u32 rsvd0:22;                          //31:10 Reserved        
        }bit;
};

union QOUT_PUL_PRD_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 PUL_PRD:22;                        //21:0  QOUT_PUL_PRD              
                volatile u32 rsvd0:10;                          //31:22 Reserved        
        }bit;
};

union QOUT_IN_POS_DATA_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 IN_POS_DATA:24;                    //23:0  QOUT_IN_POS_DATA              
                volatile u32 rsvd0:8;                           //31:24 Reserved        
        }bit;
};

union QOUT_PUL_MAX_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 PUL_MAX:24;                        //23:0  QOUT_PUL_MAX             
                volatile u32 rsvd0:8;                           //31:24 Reserved        
        }bit;
};

union QOUT_N_M_DIV_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 N_M_DIV:21;                        //20:0  QOUT_N_M_DIV
                volatile u32 rsvd0:11;                          //31:21 Reserved
        }bit;
};

union QOUT_LINE_NUM_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 LINE_NUM:22;                       //21:0  QOUT_LINE_NUM            
                volatile u32 rsvd0:10;                          //31:22 Reserved        
        }bit;
};

union QOUT_PUL_THR_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 PUL_THR:24;                        //23:0  QOUT_PUL_THR          
                volatile u32 rsvd0:8;                           //31:24 Reserved        
        }bit;
};

union QOUT_SW_PUL_PRD_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SW_PUL_PRD:22;                     //21:0  QOUT_SW_PUL_PRD              
                volatile u32 rsvd0:10;                          //31:22 Reserved        
        }bit;
};

union QOUT_PUL_DIR_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 SW_DIR:2;                          //1:0   QOUT_SW_DIR              
                volatile u32 rsvd0:14;                          //15:2  Reserved
                volatile u32 SW_NUM_SET:10;                     //25:16 QOUT_SW_NUM_SET
                volatile u32 rsvd1:6;                           //31:26 Reserved         
        }bit;
};

union QOUT_ERR_CNCL_TH_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 ERR_CNCL_TH:20;                    //19:0  QOUT_ERR_CNCL_TH              
                volatile u32 rsvd0:12;                          //31:20 Reserved      
        }bit;
};

union QOUT_ERR_CNCL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 ERR_CNCL_V:20;                     //19:0  QOUT_ERR_CNCL_V              
                volatile u32 rsvd0:12;                          //31:20 Reserved      
        }bit;
};

union QOUT_RPT_REMAIN_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RPT_REMAIN:20;                     //19:0  QOUT_RPT_REMAIN              
                volatile u32 rsvd0:12;                          //31:20 Reserved      
        }bit;
};

union QOUT_DED_POS_DATA_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 DED_POS_DATA:32;                    //31:0  DED_POS_DATA
        }bit;
};

union QOUT_TMR_PRD_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 QOUT_TMR_PRD:16;                    //15:0  QOUT_TMR_PRD
                volatile u32 rsvd0:16;							 //31:16 Reserved
        }bit;
};

struct QOUT_REGS {                      
        union   QOUT_CTL_REG            QOUT_CTL;                   //offset: 0x00                       
        union   QOUT_CFG_REG            QOUT_CFG;                   //offset: 0x04  
        union   QOUT_INT_EN_REG         QOUT_INT_EN;                //offset: 0x08 
        union   QOUT_STS_REG            QOUT_STS;                   //offset: 0x0C 
        union   QOUT_ABZ_REG            QOUT_ABZ;                   //offset: 0x10 
        union   QOUT_IN_PUL_NUM_REG     QOUT_IN_PUL_NUM;            //offset: 0x14 
        union   QOUT_PUL_PRD_REG        QOUT_PUL_PRD;               //offset: 0x18 
        union   QOUT_IN_POS_DATA_REG    QOUT_IN_POS_DATA;           //offset: 0x1C
        union   QOUT_PUL_MAX_REG        QOUT_PUL_MAX;               //offset: 0x20
        union   QOUT_N_M_DIV_REG        QOUT_N_M_DIV;               //offset: 0x24
        union   QOUT_LINE_NUM_REG       QOUT_LINE_NUM;              //offset: 0x28
        union   QOUT_PUL_THR_REG        QOUT_PUL_THR;               //offset: 0x2C
        union   QOUT_SW_PUL_PRD_REG     QOUT_SW_PUL_PRD;            //offset: 0x30
        volatile u32 res0;                                          //offset: 0x34
        union   QOUT_PUL_DIR_REG        QOUT_PUL_DIR;               //offset: 0x38
        volatile u32 res1;                                          //offset: 0x3C
        union   QOUT_ERR_CNCL_TH_REG    QOUT_ERR_CNCL_TH;           //offset: 0x40
        union   QOUT_ERR_CNCL_REG       QOUT_ERR_CNCL;              //offset: 0x44
        union   QOUT_RPT_REMAIN_REG     QOUT_RPT_REMAIN;            //offset: 0x48
        union	QOUT_DED_POS_DATA_REG	QOUT_DED_POS_DATA;			//offset: 0x4C
        union	QOUT_TMR_PRD_REG		QOUT_TMR_PRD;				//offset: 0x50
};


void qout0_irq_handler(void);
void qout1_irq_handler(void);
void qout_irq_register(u32 num, cpu_irq_fun_t irqhandle);
void qout_irq_unregister(u32 num);
void qout_err_cancl_en(u8 i);
void qout_err_cancl_dis(u8 i);
void qout_en(u8 i);
void qout_dis(u8 i);
void qout_pos_src_sel(u8 i, QOUT_SRC_TYPE src);
void qout_tmr_int_en(u8 i);
void qout_tmr_int_dis(u8 i);
void qout_pul_ovfl_int_en(u8 i);
void qout_pul_ovfl_int_dis(u8 i);
u32 qout_get_sts(u8 i);
void qout_a_en(u8 i);
void qout_b_en(u8 i);
void qout_z_en(u8 i);
void qout_a_inv_en(u8 i);
void qout_b_inv_en(u8 i);
void qout_z_inv_en(u8 i);
void qout_set_in_pulmax(u8 i, u32 max);
void qout_set_nm_raito(u8 i, u32 nm_ratio);
void qout_set_line(u8 i, u32 line);
void qout_set_pul_thr(u8 i, u32 pul_thr);
void qout_set_err_thr(u8 i, u32 err_thr);
void qout_set_err_cv(u8 i, u32 err_cv);
void qout_set_sw_mode(u8 i);
void qout_set_sw_pulse_dir(u8 i, QOUT_SW_DIR_TYP dir);
void qout_set_sw_pulse_num(u8 i, u32 num);
void qout_ded_pos_data(u8 i, u32 num);
void qout_z_ext(u8 i, u8 edg, u32 time);

void qout_prd_link_sel(u8 i,QOUT_LINK_TYPE sel);
void qout_sync_dis(u8 i);
void qout_sync_sel(u8 i, u8 sel);
void qout_tmr_prd(u8 i,u32 tmr_prd);
#endif /* INCLUDE_HAL_QOUT_H_ */
