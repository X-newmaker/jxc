#ifndef INCLUDE_HAL_QEP_H_
#define INCLUDE_HAL_QEP_H_

typedef enum{
        Q_DISABLE = 0,
        Q_ENABLE,
}Q_EN;

typedef enum{
        QUAD_CNT = 0,
        DIR_CNT,
        INCR_CNT,
        DECR_CNT,
        CW_CCW_CNT,
        N_CW_CCW_CNT,
} QEP_CNT_MOD_TYPE;

typedef enum{
        I_RST = 0,
        MAX_RST,
        FI_AND_MAX_RST,
        TO_RST,
} QEP_POS_RST_TYPE;

typedef enum{
        RSVD = 0,
        ICAP_ON_RE,
        ICAP_ON_FE,
        ICAP_ON_IMARK,
} QEP_POS_ICAP_TYPE;

typedef enum {
	QEP_SRC_IO = 0,
	QEP_SRC_EPWM0_A,
	QEP_SRC_EPWM1_A,
	QEP_SRC_EPWM2_A,
	QEP_SRC_EPWM3_A,
	QEP_SRC_EPWM4_A,
	QEP_SRC_EPWM5_A,
	QEP_SRC_EPWM6_A,
	QEP_SRC_EPWM7_A,
	QEP_SRC_EPWM8_A,
	QEP_SRC_EPWM9_A,
	QEP_SRC_EPWM10_A,
	QEP_SRC_EPWM11_A,

	QEP_SRC_EPWM0_B = 0x11,
	QEP_SRC_EPWM1_B,
	QEP_SRC_EPWM2_B,
	QEP_SRC_EPWM3_B,
	QEP_SRC_EPWM4_B,
	QEP_SRC_EPWM5_B,
	QEP_SRC_EPWM6_B,
	QEP_SRC_EPWM7_B,
	QEP_SRC_EPWM8_B,
	QEP_SRC_EPWM9_B,
	QEP_SRC_EPWM10_B,
	QEP_SRC_EPWM11_B,

	QEP_SRC_QOUT0 = 0x20,
	QEP_SRC_QOUT1,
} QEP_SRC_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union QEP_DEC_CONF_REG {
        volatile u32  all;
        struct{                                                 //bit description              
                volatile u32 rsvd0:5;                           //4:0   Reserved
                volatile u32 S_INV_EN:1;                        //5     QEP_S Inverse Enable
                volatile u32 I_INV_EN:1;                        //6     QEP_I Inverse Enable  
                volatile u32 B_INV_EN:1;                        //7     QEP_B Inverse Enable
                volatile u32 A_INV_EN:1;                        //8     QEP_A Inverse Enable
                volatile u32 IGATE_EN:1;                        //9     QEP Index Gate Set
                volatile u32 SWAP_AB:1;                         //10    QEP SWAP AB
                volatile u32 QA_DEDG_EN:1;                      //11    QEP QA Double Edge Enable
                volatile u32 SRB_OUT_PIN:1;                     //12    QEP Strobe Output PIN Select
                volatile u32 SRB_OUT_EN:1;                      //13    QEP Strobe OUTPUT Enable
                volatile u32 QEP_CNT_MOD:3;                     //16:14 QEP Counter Mode
                volatile u32 rsvd1:15;                          //31:17 Reserved        
        }bit;
};

union QEP_POS_CNT_CONF_REG {
        volatile u32  all;
        struct{                                                 //bit description           
                volatile u32 WD_TMR_EN:1;                       //0     QEP Watchdog Timer Enable
                volatile u32 TMR_EN:1;                          //1     QEP Timer Enable
                volatile u32 CAP_LH_MOD:1;                      //2     QEP Capture Latch Mode Select
                volatile u32 POS_CNT_EN:1;                      //3     QEP Position Counter Enable
                volatile u32 POS_ICAP_MOD:2;                    //5:4   QEP Position Index Trigger Capture Mode
                volatile u32 POS_SCAP_MOD:1;                    //6     QEP Position Strobe Trigger Capture Mode
                volatile u32 POS_SW_INIT:1;                     //7     QEP Position Software Initialization
                volatile u32 POS_IDX_INIT:2;                    //9:8   QEP Position IDX Initialization
                volatile u32 POS_SRB_INIT:2;                    //11:10 QEP Position SRB Initialization
                volatile u32 POS_CNT_RST:2;                     //13:12 QEP Position Counter Reset
                volatile u32 rsvd0:2;                           //15:14 Reserved
                volatile u32 CVRA_LATCH_EN:1;					//16	CVRA_LATCH_EN
                volatile u32 CVRB_LATCH_EN:1;					//17	CVRB_LATCH_EN
                volatile u32 rsvd1:14;                           //31:18 Reserved
        }bit;
};

union QEP_CAP_TMR_CONF_REG {
        volatile u32  all;
        struct{                                                 //bit description 
                volatile u32 SET_UDIST:4;                       //3:0   QEP Set Unit Distance 
                volatile u32 CAP_TMR_CLK_DIV:3;                 //6:4   QEP Capture Timer Clock Division 
                volatile u32 rsvd0:8;                           //14:7  Reserved 
                volatile u32 CAP_TMR_EN:1;                      //15    QEP Capture Timer Enable 
                volatile u32 rsvd1:16;                          //31:16 Reserved            
        }bit;
};

union QEP_POS_CMP_CONF_REG {
        volatile u32  all;
        struct{                                                 //bit description 
                volatile u32 SOUT_PW:12;                        //11:0  QEP SOUT Pulse Width 
                volatile u32 POS_CMP_EN:1;                      //12    QEP Position Compare Enable 
                volatile u32 SOUT_POL:1;                        //13    QEP SOUT Polarity
                volatile u32 POS_CMP_LP:1;                      //14    Position Compare Register Load Point
                volatile u32 POS_CMP_UPDT_MOD:1;                //15    Position Compare Register Update Mode         
                volatile u32 rsvd0:16;                          //31:16 Reserved    
        }bit;
};

union QEP_INT_EN_REG {
        volatile u32  all;
        struct{                                                 //bit description           
                volatile u32 rsvd0:1;                           //0     Reserved
                volatile u32 POS_CNT_ERR_INT_EN:1;              //1     Position Counter Error Interrupt Enable          
                volatile u32 QUADPH_ERR_INT_EN:1;               //2     Quadrature Phase Error Interrupt Enable
                volatile u32 DIR_CHG_INT_EN:1;                  //3     Direction Change Interrupt Enable
                volatile u32 WDTO_INT_EN:1;                     //4     Watchdog Timeout Interrupt Enable
                volatile u32 POS_UDFL_INT_EN:1;                 //5     Position Counter Underflow Interrupt Enable
                volatile u32 POS_OVFL_INT_EN:1;                 //6     Position Counter Overflow Interrupt Enable
                volatile u32 POS_CMPRDY_INT_EN:1;               //7     Position Compare Ready Interrupt Enable
                volatile u32 POS_CMP_INT_EN:1;                  //8     Position Compare Interrupt Enable
                volatile u32 POS_SCAP_INT_EN:1;                 //9     Strobe Capture Interrupt Enable
                volatile u32 POS_ICAP_INT_EN:1;                 //10    Index Capture Interrupt Enable
                volatile u32 TMOT_INT_EN:1;                     //11    Timer Timeout Interrupt Enable
                volatile u32 CW_CCW_ERR_INT_EN:1;               //12    CW/CCW Signal Error Interrupt Enable
                volatile u32 rsvd1:19;                          //31:13 Reserved
        }bit;
};

union QEP_INT_FLG_REG {
        volatile u32  all;
        struct{                                                 //bit description  
                volatile u32 QEP_INT_FLG:1;                     //0     QEP Interrupt       
                volatile u32 POS_CNT_ERR_INT_FLG:1;             //1     Position Counter Error Interrupt              
                volatile u32 QUADPH_ERR_INT_FLG:1;              //2     Quadrature Phase Error Interrupt                                                        
                volatile u32 DIR_CHG_INT_FLG:1;                 //3     QEP Direction Change Interrupt        
                volatile u32 WDTO_INT_FLG:1;                    //4     QEP Watchdog Timeout Interrupt                                
                volatile u32 POS_UDFL_INT_FLG:1;                //5     QEP Position Counter Underflow Interrupt                       
                volatile u32 POS_OVFL_INT_FLG:1;                //6     QEP Position Counter Overflow Interrupt                                       
                volatile u32 POS_CMPRDY_INT_FLG:1;              //7     QEP Position Compare Ready Interrupt                                       
                volatile u32 POS_CMP_INT_FLG:1;                 //8     QEP Position Compare Interrupt Flag                               
                volatile u32 POS_SCAP_INT_FLG:1;                //9     QEP Strobe Capture Interrupt        
                volatile u32 POS_ICAP_INT_FLG:1;                //10    QEP Index Capture Interrupt                       
                volatile u32 TMOT_INT_FLG:1;                    //11    QEP Timer Timeout Interrupt                               
                volatile u32 CW_CCW_ERR_INT_FLG:1;              //12    QEP CW/CCW Signal Error Interrupt
                volatile u32 rsvd0:19;                          //31:13 Reserved
        }bit;
};

union QEP_INT_CLR_REG {
        volatile u32  all;
        struct{                                                 //bit description           
                volatile u32 rsvd0:1;                           //0     Reserved
                volatile u32 POS_CNT_ERR_INT_CLR:1;             //1     Position Counter Error Interrupt Clear                 
                volatile u32 QUADPH_ERR_INT_CLR:1;              //2     Quadrature Phase Error Interrupt Clear        
                volatile u32 DIR_CHG_INT_CLR:1;                 //3     Direction Change Interrupt Clear
                volatile u32 WDTO_INT_CLR:1;                    //4     Watchdog Timeout Interrupt Clear        
                volatile u32 POS_UDFL_INT_CLR:1;                //5     Position Counter Underflow Interrupt Clear        
                volatile u32 POS_OVFL_INT_CLR:1;                //6     Position Counter Overflow Interrupt Clear        
                volatile u32 POS_CMPRDY_INT_CLR:1;              //7     Position Compare Ready Interrupt Clear        
                volatile u32 POS_CMP_INT_CLR:1;                 //8     Position Compare Interrupt Clear        
                volatile u32 POS_SCAP_INT_CLR:1;                //9     Strobe Capture Interrupt Clear        
                volatile u32 POS_ICAP_INT_CLR:1;                //10    Index Capture Interrupt Clear                
                volatile u32 TMOT_INT_CLR:1;                    //11    Timer Timeout Interrupt Clear        
                volatile u32 CW_CCW_ERR_INT_CLR:1;              //12    CW/CCW Signal Error Interrupt Clear
                volatile u32 rsvd1:19;                          //31:13 Reserved
        }bit;
};

union QEP_INT_FRC_REG {
        volatile u32  all;
        struct{                                                 //bit description                                                                                                
                volatile u32 rsvd0:1;                           //0     Reserved
                volatile u32 POS_CNT_ERR_INT_FRC:1;             //1     Position Counter Error Interrupt Force             
                volatile u32 QUADPH_ERR_INT_FRC:1;              //2     Quadrature Phase Error Interrupt Force             
                volatile u32 DIR_CHG_INT_FRC:1;                 //3     Direction Change Interrupt Force
                volatile u32 WDTO_INT_FRC:1;                    //4     Watchdog Timeout Interrupt Force        
                volatile u32 POS_UDFL_INT_FRC:1;                //5     Position Counter Underflow Interrupt Force         
                volatile u32 POS_OVFL_INT_FRC:1;                //6     Position Counter Overflow Interrupt Force          
                volatile u32 POS_CMPRDY_INT_FRC:1;              //7     Position Compare Ready Interrupt Force             
                volatile u32 POS_CMP_INT_FRC:1;                 //8     Position Compare Interrupt Force        
                volatile u32 POS_SCAP_INT_FRC:1;                //9     Strobe Capture Interrupt Force                
                volatile u32 POS_ICAP_INT_FRC:1;                //10    Index Capture Interrupt Force                      
                volatile u32 TMOT_INT_FRC:1;                    //11    Timer Timeout Interrupt Force                
                volatile u32 CW_CCW_ERR_INT_FRC:1;              //12    CW/CCW Signal Error Interrupt Force
                volatile u32 rsvd1:19;                          //31:13 Reserved
        }bit;
};

union QEP_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 POS_CNT_ERR:1;                     //0     Position Counter Error Flag
                volatile u32 FIDX_MKR_FLG:1;                    //1     First Index Marker Flag
                volatile u32 CAP_DERR:1;                        //2     Capture Direction Error Flag
                volatile u32 CAP_TMR_OVFL:1;                    //3     Capture Timer Overflow Flag
                volatile u32 DIR_IEVENT_FLG:1;                  //4     Direciton Flag of Index Event
                volatile u32 DIR_FLG:1;                         //5     Direction Flag
                volatile u32 FIDX_MKR_DIR_FLG:1;                //6     First Index Marker Direction Flag        
                volatile u32 UD_EVNT_FLG:1;                     //7     Unit Distance Event Flag  
                volatile u32 rsvd0:24;                          //31:8  Reserved          
        }bit;
};

union QEP_CAP_TMRV_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 CAP_TMRV:16;                       //15:0  QEP Capture Timer    
                volatile u32 rsvd0:16;                          //31:16 Reserved                 
        }bit;
};

union QEP_CAP_DELT_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 CAP_DELT:16;                       //15:0  QEP Capture Delta Time
                volatile u32 CAP_DELT_ERR:1;                    //16    QEP Capture Delta Time ERR
                volatile u32 rsvd0:15;                          //31:17 Reserved     
        }bit;
};

union QEP_CAP_TMRLH_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 CAP_TMRLH:16;                      //15:0  QEP Capture Timer Latch              
                volatile u32 rsvd0:16;                          //31:16 Reserved                                     
        }bit;
};

union QEP_CAP_DELT_LH_REG {
        volatile u32  all;
        struct{                                                 //bit description                                   
                volatile u32 CAP_DELT_LH:16;                    //15:0  QEP Capture Delta Time Latch
                volatile u32 CAP_DELT_ERR_LH:1;                 //16    QEP Capture Delta Time ERR Latch      
                volatile u32 rsvd0:15;                          //31:17 Reserved                         
        }bit;
};

union QEP_IN_FLT1_REG {
        volatile u32  all;
        struct{                                                 //bit description 
                volatile u32 A_IN_FLT_SEL:4;                    //3:0   Input Filter Seclect
                volatile u32 A_IN_PRE_FLT:4;                    //7:4   Input Pre Filter Enable
                volatile u32 A_SMP_CTL_PRD:8;                   //15:8  Input Sample Control Period       
                volatile u32 B_IN_FLT_SEL:4;                    //19:16 Input Filter Seclect
                volatile u32 B_IN_PRE_FLT:4;                    //23:20 Input Pre Filter Enable
                volatile u32 B_SMP_CTL_PRD:8;                   //31:24 Input Sample Control Period                                
        }bit;
};

union QEP_IN_FLT2_REG {
        volatile u32  all;
        struct{                                                 //bit description               
                volatile u32 I_IN_FLT_SEL:4;                    //3:0   Input Filter Seclect
                volatile u32 I_IN_PRE_FLT:4;                    //7:4   Input Pre Filter Enable
                volatile u32 I_SMP_CTL_PRD:8;                   //15:8  Input Sample Control Period                   
                volatile u32 S_IN_FLT_SEL:4;                    //19:16 Input Filter Seclect
                volatile u32 S_IN_PRE_FLT:4;                    //23:20 Input Pre Filter Enable
                volatile u32 S_SMP_CTL_PRD:8;                   //31:24 Input Sample Control Period                      
        }bit;
};

union QEP_IN_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 QEP_IN_FLT_EN:1;                   //0     Input Filter Enable
                volatile u32 QEP_I_GATEA_EN:1;                  //1     QEP_I Internal Gate A Disable
                volatile u32 QEP_I_TYPE:1;                      //2     QEP_I Sigal Type   
                volatile u32 QEP_SMP_WIN_EN:1;                  //3     QEP sample window enable
                volatile u32 rsvd0:4;                           //7:4   Reserved
                volatile u32 QEP_IOUT_EN:1;                     //8     QEP I Output Enable
                volatile u32 QEP_SOUT_EN:1;                     //9     QEP S Output Enable
                volatile u32 rsvd1:6;                           //15:10 Reserved
                volatile u32 SMP_WIN_TH:10;                     //25:16 QEP sample window threshold
                volatile u32 rsvd2:6;                           //31:26 Reserved
        }bit;
};

union QEP_INSRC_REG {
		volatile u32 all;
		struct {
				volatile u32 QEP_A_IN_SRC_SEL:6;				//5:0 QEP_A_IN_SRC_SEL
				volatile u32 rsvd0:2;							//7:6 Reserved
				volatile u32 QEP_B_IN_SRC_SEL:6;				//13:8 QEP_B_IN_SRC_SEL
				volatile u32 rsvd1:2;							//15:14 Reserved
				volatile u32 QEP_I_IN_SRC_SEL:6;				//21:16 QEP_I_IN_SRC_SEL
				volatile u32 rsvd2:10;							//31:22 Reserved
		}bit;
};

struct QEP_REGS {
        volatile u32    QEP_POS_CNTV;                                  //offset: 0x00                     
        volatile u32    QEP_POS_CNT_SP;                                //offset: 0x04                 
        volatile u32    QEP_POS_CNT_EP;                                //offset: 0x08                 
        volatile u32    QEP_POS_CNT_CMPV;                              //offset: 0x0C                   
        volatile u32    QEP_POS_CNT_ICAPV;                             //offset: 0x10                    
        volatile u32    QEP_POS_CNT_SCAPV;                             //offset: 0x14                    
        volatile u32    QEP_POS_CNT_TOCAPV;                            //offset: 0x18                     
        volatile u32    QEP_TMR_V;                                     //offset: 0x1C            
        volatile u32    QEP_TMR_PRDV;                                  //offset: 0x20               
        volatile u32    QEP_WD_TMRV;                                   //offset: 0x24              
        volatile u32    QEP_WD_PRDV;                                   //offset: 0x28              
        union   QEP_DEC_CONF_REG            QEP_DEC_CONF;              //offset: 0x2C                         
        union   QEP_POS_CNT_CONF_REG        QEP_POS_CNT_CONF;          //offset: 0x30                       
        union   QEP_CAP_TMR_CONF_REG        QEP_POS_TMR_CONF;          //offset: 0x34  
        union   QEP_POS_CMP_CONF_REG        QEP_POS_CMP_CONF;          //offset: 0x38 
        union   QEP_INT_EN_REG              QEP_INT_EN;                //offset: 0x3C 
        union   QEP_INT_FLG_REG             QEP_INT_FLG;               //offset: 0x40 
        union   QEP_INT_CLR_REG             QEP_INT_CLR;               //offset: 0x44 
        union   QEP_INT_FRC_REG             QEP_INT_FRC;               //offset: 0x48 
        union   QEP_STS_REG                 QEP_STS;                   //offset: 0x4C
        union   QEP_CAP_TMRV_REG            QEP_CAP_TMRV;              //offset: 0x50
        union   QEP_CAP_DELT_REG            QEP_CAP_DELT;              //offset: 0x54
        union   QEP_CAP_TMRLH_REG           QEP_CAP_TMRLH;             //offset: 0x58
        union   QEP_CAP_DELT_LH_REG         QEP_CAP_DELT_LH;           //offset: 0x5C
        union   QEP_IN_FLT1_REG             QEP_IN_FLT1;               //offset: 0x60
        union   QEP_IN_FLT2_REG             QEP_IN_FLT2;               //offset: 0x64
        union   QEP_IN_CTL_REG              QEP_IN_CTL;                //offset: 0x68
        volatile u32 rsvd0[6];										   //offset: 0x6C-0x80
        volatile u32    QEP_CVRA_LATCH;                                //offset: 0x84
        volatile u32    QEP_CVRB_LATCH;                                //offset: 0x88
        union	QEP_INSRC_REG				QEP_INSRC;				   //offset: 0x8C
};

void qep0_irq_handler(void);
void qep1_irq_handler(void);
void qep2_irq_handler(void);
void qep3_irq_handler(void);
void qep4_irq_handler(void);
void qep5_irq_handler(void);
void qep6_irq_handler(void);
void qep7_irq_handler(void);
void qep8_irq_handler(void);
void qep9_irq_handler(void);
void qep_irq_register(u32 num, cpu_irq_fun_t irqhandle);
void qep_irq_unregister(u32 num);
void qep_pos_cnt_en(u8 i);
void qep_set_linenum(u8 i, u32 line_num);
void qep_set_pos_cnt_mode(u8 i, u32 mode);
void qep_set_pos_rst_mode(u8 i, u32 mode);
void qep_set_icap_mode(u8 i, u32 mode);
void qep_set_icap_int_en(u8 i);
void qep_set_a_inflt(u8 i, u32 smp_num, u32 smp_prd);
void qep_set_b_inflt(u8 i, u32 smp_num, u32 smp_prd);
void qep_set_i_inflt(u8 i, u32 smp_num, u32 smp_prd);
void qep_set_inflt_en(u8 i);
void qep_set_i_gatea_en(u8 i);
void qep_a_src_sel(u8 i,QEP_SRC_TYPE type);
void qep_b_src_sel(u8 i,QEP_SRC_TYPE type);
void qep_i_src_sel(u8 i,QEP_SRC_TYPE type);
#endif /* INCLUDE_HAL_QEP_H_ */
