/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_PWMCS_H_
#define INCLUDE_HAL_PWMCS_H_


#define EPWM0_INT_PEND                    (0x1 << 0)
#define EPWM1_INT_PEND                    (0x1 << 1)
#define EPWM2_INT_PEND                    (0x1 << 2)
#define EPWM3_INT_PEND                    (0x1 << 3)
#define EPWM4_INT_PEND                    (0x1 << 4)
#define EPWM5_INT_PEND                    (0x1 << 5)
#define EPWM6_INT_PEND                    (0x1 << 6)
#define EPWM7_INT_PEND                    (0x1 << 7)
#define EPWM8_INT_PEND                    (0x1 << 8)
#define EPWM9_INT_PEND                    (0x1 << 9)
#define EPWM10_INT_PEND                   (0x1 << 10)
#define EPWM11_INT_PEND                   (0x1 << 11)

#define EPWM0_FAULT_INT_PEND              (0x1 << 0)
#define EPWM1_FAULT_INT_PEND              (0x1 << 1)
#define EPWM2_FAULT_INT_PEND              (0x1 << 2)
#define EPWM3_FAULT_INT_PEND              (0x1 << 3)
#define EPWM4_FAULT_INT_PEND              (0x1 << 4)
#define EPWM5_FAULT_INT_PEND              (0x1 << 5)
#define EPWM6_FAULT_INT_PEND              (0x1 << 6)
#define EPWM7_FAULT_INT_PEND              (0x1 << 7)
#define EPWM8_FAULT_INT_PEND              (0x1 << 8)
#define EPWM9_FAULT_INT_PEND              (0x1 << 9)
#define EPWM10_FAULT_INT_PEND             (0x1 << 10)
#define EPWM11_FAULT_INT_PEND             (0x1 << 11)

#define CAP0_INT_PEND                     (0x1 << 0)
#define CAP1_INT_PEND                     (0x1 << 1)
#define CAP2_INT_PEND                     (0x1 << 2)
#define CAP3_INT_PEND                     (0x1 << 3)
#define CAP4_INT_PEND                     (0x1 << 4)
#define CAP5_INT_PEND                     (0x1 << 5)

#define QEP0_INT_PEND                     (0x1 << 0)
#define QEP1_INT_PEND                     (0x1 << 1)
#define QEP2_INT_PEND                     (0x1 << 2)
#define QEP3_INT_PEND                     (0x1 << 3)
#define QEP4_INT_PEND                     (0x1 << 4)
#define QEP5_INT_PEND                     (0x1 << 5)
#define QEP6_INT_PEND                     (0x1 << 6)
#define QEP7_INT_PEND                     (0x1 << 7)
#define QEP8_INT_PEND                     (0x1 << 8)
#define QEP9_INT_PEND                     (0x1 << 9)

#define EPWM_FAULT0_STS              	  (0x1 << 0)
#define EPWM_FAULT1_STS              	  (0x1 << 1)
#define EPWM_FAULT2_STS              	  (0x1 << 2)
#define EPWM_FAULT3_STS              	  (0x1 << 3)
#define EPWM_FAULT4_STS              	  (0x1 << 4)
#define EPWM_FAULT5_STS              	  (0x1 << 5)

typedef enum{
        EPWM0_SEL_SYNCI0 = 0,
		EPWM0_SEL_CPM0_COH,
		EPWM0_SEL_CPM1_COH,
}EPWM0_SYNCIN_TYPE;

typedef enum{
        SEL_SYNCI0 = 0,
        SEL_SYNCI1,
        SEL_EPWM0_SYNCO,
		SEL_EPWM3_SYNCO,
		SEL_EPWM6_SYNCO,
		SEL_EPWM9_SYNCO,
		SEL_CAP0_SYNCO,
}EPWM_SYNCIN_TYPE;

typedef enum{
        LH_RISE = 0,
        LH_FALL,
}EPWM_FAULT_LH_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union GLB_EPWM_INT_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description           
        		volatile u32 EPWM0_INT_STS:1;                   //0     EPWM0 Interrupt Status
                volatile u32 EPWM1_INT_STS:1;                   //1     EPWM1 Interrupt Status
                volatile u32 EPWM2_INT_STS:1;                   //2     EPWM2 Interrupt Status	
                volatile u32 EPWM3_INT_STS:1;                   //3     EPWM3 Interrupt Status
                volatile u32 EPWM4_INT_STS:1;                   //4     EPWM4 Interrupt Status
                volatile u32 EPWM5_INT_STS:1;                   //5     EPWM5 Interrupt Status
                volatile u32 EPWM6_INT_STS:1;                   //6     EPWM6 Interrupt Status
                volatile u32 EPWM7_INT_STS:1;                   //7     EPWM7 Interrupt Status
                volatile u32 EPWM8_INT_STS:1;                   //8     EPWM8 Interrupt Status
                volatile u32 EPWM9_INT_STS:1;                   //9     EPWM9 Interrupt Status
                volatile u32 EPWM10_INT_STS:1;                  //10    EPWM10 Interrupt Status
                volatile u32 EPWM11_INT_STS:1;                  //11    EPWM11 Interrupt Status
                volatile u32 rsvd0:20;                          //31:12 Reserved
        }bit;
};

union GLB_FAULT_INT_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description 
        		volatile u32 EPWM0_FAULT_INT_STS:1;             //0     EPWM0 Fault Interrupt Status
                volatile u32 EPWM1_FAULT_INT_STS:1;             //1     EPWM1 Fault Interrupt Status
                volatile u32 EPWM2_FAULT_INT_STS:1;	        //2     EPWM2 Fault Interrupt Status
                volatile u32 EPWM3_FAULT_INT_STS:1;             //3     EPWM3 Fault Interrupt Status
                volatile u32 EPWM4_FAULT_INT_STS:1;             //4     EPWM4 Fault Interrupt Status
                volatile u32 EPWM5_FAULT_INT_STS:1;             //5     EPWM5 Fault Interrupt Status
                volatile u32 EPWM6_FAULT_INT_STS:1;             //6     EPWM6 Fault Interrupt Status
                volatile u32 EPWM7_FAULT_INT_STS:1;             //7     EPWM7 Fault Interrupt Status
                volatile u32 EPWM8_FAULT_INT_STS:1;	        //8     EPWM8 Fault Interrupt Status
                volatile u32 EPWM9_FAULT_INT_STS:1;             //9     EPWM9 Fault Interrupt Status
                volatile u32 EPWM10_FAULT_INT_STS:1;            //10    EPWM10 Fault Interrupt Status
                volatile u32 EPWM11_FAULT_INT_STS:1;            //11    EPWM11 Fault Interrupt Status                
                volatile u32 rsvd0:20;                          //31:12 Reserved
        }bit;
};

union GLB_CAP_INT_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description 
        		volatile u32 CAP0_INT_STS:1;                    //0     CAP0 Interrupt Status
                volatile u32 CAP1_INT_STS:1;                    //1     CAP1 Interrupt Status
                volatile u32 CAP2_INT_STS:1;                    //2     CAP2 Interrupt Status
                volatile u32 CAP3_INT_STS:1;                    //3     CAP3 Interrupt Status
                volatile u32 CAP4_INT_STS:1;                    //4     CAP4 Interrupt Status
                volatile u32 CAP5_INT_STS:1;		        //5     CAP5 Interrupt Status
                volatile u32 rsvd0:26;                          //31:6  Reserved
        }bit;
};

union GLB_QEP_INT_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 QEP0_INT_STS:1;                    //0     QEP0 Interrupt Status
                volatile u32 QEP1_INT_STS:1;                    //1     QEP1 Interrupt Status
                volatile u32 QEP2_INT_STS:1;                    //2     QEP2 Interrupt Status
                volatile u32 QEP3_INT_STS:1;                    //3     QEP3 Interrupt Status
                volatile u32 QEP4_INT_STS:1;                    //4     QEP4 Interrupt Status
                volatile u32 QEP5_INT_STS:1;                    //5     QEP5 Interrupt Status
                volatile u32 QEP6_INT_STS:1;                    //6     QEP6 Interrupt Status
                volatile u32 QEP7_INT_STS:1;                    //7     QEP7 Interrupt Status
                volatile u32 QEP8_INT_STS:1;                    //8     QEP8 Interrupt Status
                volatile u32 QEP9_INT_STS:1;                    //9     QEP9 Interrupt Status
                volatile u32 rsvd0:22;                          //31:10 Reserved
        }bit;
};

union GLB_EPWM_EN_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 GLB_EPWM_EN:1;                     //0     Global EPWM Enable
        		volatile u32 rsvd0:31;                          //31:1  Reserved
        }bit;
};

union GLB_EPWM_SYNCIN_FLT_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 SYNCIN_FLT_SEL:4;                  //3:0   Synchronous Input Filter Seclect
                volatile u32 SYNCIN_PRE_FLT:4;                  //7:4   Synchronous Input Pre Filter Enable 
                volatile u32 SYNCIN_SMP_PRD:8;	                //15:8  Synchronous Input Sample Control Period 
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union GLB_EPWM_CLK_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 EPWM0_CLK_EN:1;                    //0     EPWM0 Clock Enable
                volatile u32 EPWM1_CLK_EN:1;                    //1     EPWM1 Clock Enable
                volatile u32 EPWM2_CLK_EN:1;                    //2     EPWM2 Clock Enable	
                volatile u32 EPWM3_CLK_EN:1;                    //3     EPWM3 Clock Enable
                volatile u32 EPWM4_CLK_EN:1;                    //4     EPWM4 Clock Enable
                volatile u32 EPWM5_CLK_EN:1;                    //5     EPWM5 Clock Enable
                volatile u32 EPWM6_CLK_EN:1;                    //6     EPWM6 Clock Enable
                volatile u32 EPWM7_CLK_EN:1;                    //7     EPWM7 Clock Enable
                volatile u32 EPWM8_CLK_EN:1;                    //8     EPWM8 Clock Enable
                volatile u32 EPWM9_CLK_EN:1;                    //9     EPWM9 Clock Enable
                volatile u32 EPWM10_CLK_EN:1;                   //10    EPWM10 Clock Enable
                volatile u32 EPWM11_CLK_EN:1;                   //11    EPWM11 Clock Enable
		volatile u32 rsvd0:20;                          //31:12 Reserved
        }bit;
};

union GLB_CAP_CLK_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 CAP0_CLK_EN:1;                     //0     CAP0 Clock Enable
                volatile u32 CAP1_CLK_EN:1;                     //1     CAP1 Clock Enable
                volatile u32 CAP2_CLK_EN:1;                     //2     CAP2 Clock Enable
                volatile u32 CAP3_CLK_EN:1;                     //3     CAP3 Clock Enable
                volatile u32 CAP4_CLK_EN:1;                     //4     CAP4 Clock Enable
                volatile u32 CAP5_CLK_EN:1;		        //5     CAP5 Clock Enable        
                volatile u32 rsvd0:26;                          //31:6  Reserved
        }bit;
};

union GLB_QEP_CLK_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 QEP0_CLK_EN:1;                     //0     QEP0 Clock Enable
                volatile u32 QEP1_CLK_EN:1;                     //1     QEP1 Clock Enable
                volatile u32 QEP2_CLK_EN:1;                     //2     QEP2 Clock Enable
                volatile u32 QEP3_CLK_EN:1;                     //3     QEP3 Clock Enable
                volatile u32 QEP4_CLK_EN:1;                     //4     QEP4 Clock Enable
                volatile u32 QEP5_CLK_EN:1;                     //5     QEP5 Clock Enable
                volatile u32 QEP6_CLK_EN:1;                     //6     QEP6 Clock Enable
                volatile u32 QEP7_CLK_EN:1;                     //7     QEP7 Clock Enable
                volatile u32 QEP8_CLK_EN:1;                     //8     QEP8 Clock Enable
                volatile u32 QEP9_CLK_EN:1;                     //9     QEP9 Clock Enable
		volatile u32 rsvd0:22;                          //31:10 Reserved
        }bit;
};

union GLB_QOUT_CLK_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 QOUT0_CLK_EN:1;                    //0     QOUT0 Clock Enable
                volatile u32 QOUT1_CLK_EN:1;                    //1     QOUT1 Clock Enable
                volatile u32 rsvd0:30;                          //31:2  Reserved
        }bit;
};

union GLB_EPWM_RST_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 EPWM0_RST:1;                    //0     EPWM0 Rest
                volatile u32 EPWM1_RST:1;                    //1     EPWM1 Rest
                volatile u32 EPWM2_RST:1;                    //2     EPWM2 Rest
                volatile u32 EPWM3_RST:1;                    //3     EPWM3 Rest
                volatile u32 EPWM4_RST:1;                    //4     EPWM4 Rest
                volatile u32 EPWM5_RST:1;                    //5     EPWM5 Rest
                volatile u32 EPWM6_RST:1;                    //6     EPWM6 Rest
                volatile u32 EPWM7_RST:1;                    //7     EPWM7 Rest
                volatile u32 EPWM8_RST:1;                    //8     EPWM8 Rest
                volatile u32 EPWM9_RST:1;                    //9     EPWM9 Rest
                volatile u32 EPWM10_RST:1;                   //10    EPWM10 Rest
                volatile u32 EPWM11_RST:1;                   //11    EPWM11 Rest
		volatile u32 rsvd0:20;                          //31:12 Reserved
        }bit;
};

union GLB_CAP_RST_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 CAP0_RST:1;                     //0     CAP0 Rest
                volatile u32 CAP1_RST:1;                     //1     CAP1 Rest
                volatile u32 CAP2_RST:1;                     //2     CAP2 Rest
                volatile u32 CAP3_RST:1;                     //3     CAP3 Rest
                volatile u32 CAP4_RST:1;                     //4     CAP4 Rest
                volatile u32 CAP5_RST:1;		        	 //5     CAP5 Rest
                volatile u32 rsvd0:26;                          //31:6  Reserved
        }bit;
};

union GLB_QEP_RST_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 QEP0_RST:1;                     //0     QEP0 Rest
                volatile u32 QEP1_RST:1;                     //1     QEP1 Rest
                volatile u32 QEP2_RST:1;                     //2     QEP2 Rest
                volatile u32 QEP3_RST:1;                     //3     QEP3 Rest
                volatile u32 QEP4_RST:1;                     //4     QEP4 Rest
                volatile u32 QEP5_RST:1;                     //5     QEP5 Rest
                volatile u32 QEP6_RST:1;                     //6     QEP6 Rest
                volatile u32 QEP7_RST:1;                     //7     QEP7 Rest
                volatile u32 QEP8_RST:1;                     //8     QEP8 Rest
                volatile u32 QEP9_RST:1;                     //9     QEP9 Rest
		volatile u32 rsvd0:22;                          //31:10 Reserved
        }bit;
};

union GLB_QOUT_RST_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 QOUT0_RST:1;                    //0     QOUT0 Rest
                volatile u32 QOUT1_RST:1;                    //1     QOUT1 Rest
                volatile u32 rsvd0:30;                          //31:2  Reserved
        }bit;
};


union GLB_EPWM_SYNC_IN_SEL_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 EPWM0_SYNC_IN_SEL:2;               //1:0   EPWM0 Synchronous Input Select
                volatile u32 EPWM3_SYNC_IN_SEL:2;               //3:2   EPWM0 Synchronous Input Select  
                volatile u32 EPWM6_SYNC_IN_SEL:2;               //5:4   EPWM0 Synchronous Input Select  
                volatile u32 EPWM9_SYNC_IN_SEL:3;               //8:6   EPWM0 Synchronous Input Select  
                volatile u32 rsvd0:3;                           //11:9  Reserved     
                volatile u32 CAP0_SYNC_IN_SEL:3;                //14:12 CAP0 Synchronous Input Select
                volatile u32 rsvd1:1;                           //15    Reserved
                volatile u32 CAP3_SYNC_IN_SEL:3;                //18:16 CAP3 Synchronous Input Select
                volatile u32 rsvd2:5;                           //23:19 Reserved
                volatile u32 EPWM0_SYNCO_EN:1;                  //24    EPWM0 Synchronous Output Enable
                volatile u32 EPWM3_SYNCO_EN:1;                  //25    EPWM3 Synchronous Output Enable
                volatile u32 EPWM6_SYNCO_EN:1;                  //26    EPWM6 Synchronous Output Enable
                volatile u32 EPWM9_SYNCO_EN:1;                  //27    EPWM9 Synchronous Output Enable
                volatile u32 CAP0_SYNCO_EN:1;                   //28    CAP0 Synchronous Output Enable
                volatile u32 rsvd3:3;                           //31:29 Reserved
        }bit;
};

union SYNC_SRC_IN_SEL_REG {
		volatile u32 all;
		struct {
				volatile u32 SYNCI0_IN_SRC_SEL:6;				//5:0	SYNCI0_IN_SRC_SEL
				volatile u32 rsvd0:2;							//7:6	Reserved
				volatile u32 SYNCI1_IN_SRC_SEL:6;				//13:8	SYNCI1_IN_SRC_SEL
				volatile u32 rsvd1:18;							//31:14	Reserved
		}bit;
};

union EPWM_FLT_SRC_IN_SEL_REG {
		volatile u32 all;
		struct {
				volatile u32 FALT0_IN_SRC_SEL:5;				//4:0	FALT0_IN_SRC_SEL
				volatile u32 FALT1_IN_SRC_SEL:5;				//9:5	FALT1_IN_SRC_SEL
				volatile u32 FALT2_IN_SRC_SEL:5;				//14:10	FALT2_IN_SRC_SEL
				volatile u32 FALT3_IN_SRC_SEL:5;				//19:15	FALT3_IN_SRC_SEL
				volatile u32 FALT4_IN_SRC_SEL:5;				//24:20	FALT4_IN_SRC_SEL
				volatile u32 FALT5_IN_SRC_SEL:5;				//29:25	FALT5_IN_SRC_SEL
				volatile u32 rsvd0:2;							//31:30 Reserved
		}bit;
};

union GLB_DLL_LDO_EN_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 DLL_LDO_EN:1;                      //0     DLL_LDO_EN
                volatile u32 EN_CLK:1;                          //1     EN_CLK
                volatile u32 EN_VCDL:1;                         //2     EN_VCDL
                volatile u32 EN_CP:1;                           //3     EN_CP
                volatile u32 EN_LVS:1;                          //4     EN_LVS
                volatile u32 EN_ATB:1;                          //5     EN_ATB
                volatile u32 REG_ATBSEL:2;                      //7:6   REG_ATBSEL
                volatile u32 REG_DLY:2;                         //9:8   REG_DLY
                volatile u32 REG_ICP:2;                         //11:10 REG_ICP
                volatile u32 REG_DLL_LPC_EN:1;					//12	REG_DLL_LPC_EN
                volatile u32 REG_DLL_DCC_EN:1;					//13	REG_DLL_DCC_EN
                volatile u32 rsvd0:2;                           //15:14 Reserved
                volatile u32 DLL1_LDO_EN:1;                     //16    DLL1_LDO_EN
                volatile u32 EN_CLK1:1;                         //17    EN_CLK1
                volatile u32 EN_VCDL1:1;                        //18    EN_VCDL1
                volatile u32 EN_CP1:1;                          //19    EN_CP1
                volatile u32 EN_LVS1:1;                         //20    EN_LVS1
                volatile u32 EN_ATB1:1;                         //21    EN_ATB1
                volatile u32 REG_ATBSEL1:2;                     //23:22 REG_ATBSEL1
                volatile u32 REG_DLY1:2;                        //25:24 REG_DLY1
                volatile u32 REG_ICP1:2;                        //27:26 REG_ICP1
                volatile u32 REG_DLL1_LPC_EN:1;					//28	REG_DLL1_LPC_EN
                volatile u32 REG_DLL1_DCC_EN:1;					//29	REG_DLL1_DCC_EN
                volatile u32 rsvd1:2;                           //31:30 Reserved
        }bit;
};

union GLB_QOUT_INT_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description
        		volatile u32 QOUT0_INT_STS:1;                   //0     QOUT0 Interrupt Status
                volatile u32 QOUT1_INT_STS:1;		        //1     QOUT1 Interrupt Status
                volatile u32 rsvd0:30;                          //31:2  Reserved
        }bit;
};

union GLB_FAULT_STS_REG {
        volatile u32  all;      
        struct{                                                 //bit description
        		volatile u32 FAULT0_STS:1;                      //0     FAULT0 Status
        		volatile u32 FAULT1_STS:1;                      //1     FAULT1 Status
        		volatile u32 FAULT2_STS:1;                      //2     FAULT2 Status
        		volatile u32 FAULT3_STS:1;                      //3     FAULT3 Status
        		volatile u32 FAULT4_STS:1;                      //4     FAULT4 Status
        		volatile u32 FAULT5_STS:1;                      //5     FAULT5 Status
        		volatile u32 rsvd0:2;							//7:6	Reserved
        		volatile u32 FALT0_STS_LATCH:1;					//8		FALT0_STS_LATCH
        		volatile u32 FALT1_STS_LATCH:1;					//9		FALT1_STS_LATCH
        		volatile u32 FALT2_STS_LATCH:1;					//10	FALT2_STS_LATCH
        		volatile u32 FALT3_STS_LATCH:1;					//11	FALT3_STS_LATCH
        		volatile u32 FALT4_STS_LATCH:1;					//12	FALT4_STS_LATCH
        		volatile u32 FALT5_STS_LATCH:1;					//13	FALT5_STS_LATCH
        		volatile u32 rsvd1:2;                           //15:14  Reserved
        		volatile u32 FALT0_EGE_DET:1;					//16	FALT0_EGE_DET
        		volatile u32 FALT1_EGE_DET:1;					//17	FALT1_EGE_DET
        		volatile u32 FALT2_EGE_DET:1;					//18	FALT2_EGE_DET
        		volatile u32 FALT3_EGE_DET:1;					//19	FALT3_EGE_DET
        		volatile u32 FALT4_EGE_DET:1;					//20	FALT4_EGE_DET
        		volatile u32 FALT5_EGE_DET:1;					//21	FALT5_EGE_DET
        		volatile u32 rsvd2:10;                          //31:22 Reserved
        }bit;
};


union PWM_FAULTIN_FLT1_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 FAULT0_IN_FLT_SEL:4;       //3:0   EPWM_FALT0_IN_FLT_SEL
                volatile u32 FAULT0_PRE_FLT:4;          //7:4   EPWM_FALT0_PRE_FLT
                volatile u32 FAULT0_SMP_CTL:8;          //15:8  EPWM_FALT0_SMP_CTL_PRD
                volatile u32 FAULT1_IN_FLT_SEL:4;       //19:16 EPWM_FALT1_IN_FLT_SEL
                volatile u32 FAULT1_PRE_FLT:4;          //23:20 EPWM_FALT1_PRE_FLT
                volatile u32 FAULT1_SMP_CTL:8;          //31:24 EPWM_FALT1_SMP_CTL_PRD
        }bit;
};

union PWM_FAULTIN_FLT2_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 FAULT2_IN_FLT_SEL:4;       //3:0   EPWM_FALT2_IN_FLT_SEL
                volatile u32 FAULT2_PRE_FLT:4;          //7:4   EPWM_FALT2_PRE_FLT
                volatile u32 FAULT2_SMP_CTL:8;          //15:8  EPWM_FALT2_SMP_CTL_PRD
                volatile u32 FAULT3_IN_FLT_SEL:4;       //19:16 EPWM_FALT3_IN_FLT_SEL
                volatile u32 FAULT3_PRE_FLT:4;          //23:20 EPWM_FALT3_PRE_FLT
                volatile u32 FAULT3_SMP_CTL:8;          //31:24 EPWM_FALT3_SMP_CTL_PRD
        }bit;
};

union PWM_FAULTIN_FLT3_REG {
        volatile u32  all;
        struct{                                         //bit description
                volatile u32 FAULT4_IN_FLT_SEL:4;       //3:0   EPWM_FALT4_IN_FLT_SEL
                volatile u32 FAULT4_PRE_FLT:4;          //7:4   EPWM_FALT4_PRE_FLT
                volatile u32 FAULT4_SMP_CTL:8;          //15:8  EPWM_FALT4_SMP_CTL_PRD
                volatile u32 FAULT5_IN_FLT_SEL:4;       //19:16 EPWM_FALT5_IN_FLT_SEL
                volatile u32 FAULT5_PRE_FLT:4;          //23:20 EPWM_FALT5_PRE_FLT
                volatile u32 FAULT5_SMP_CTL:8;          //31:24 EPWM_FALT5_SMP_CTL_PRD
        }bit;
};

struct GLB_PWMCS_REGS {
        volatile u32  RES0;                                         //offset: 0x00                    
        union   GLB_EPWM_INT_STS_REG      GLB_EPWM_INT_STS;         //offset: 0x04                        
        union   GLB_FAULT_INT_STS_REG     GLB_FAULT_INT_STS;        //offset: 0x08                        
        union   GLB_CAP_INT_STS_REG       GLB_CAP_INT_STS;          //offset: 0x0C
        union   GLB_QEP_INT_STS_REG       GLB_QEP_INT_STS;          //offset: 0x10
        union   GLB_EPWM_EN_REG           GLB_EPWM_EN;              //offset: 0x14
        union   GLB_EPWM_SYNCIN_FLT_REG   GLB_EPWM_SYNCIN0_FLT;     //offset: 0x18
        union   GLB_EPWM_SYNCIN_FLT_REG   GLB_EPWM_SYNCIN1_FLT;     //offset: 0x1C
        union   GLB_EPWM_CLK_CTL_REG      GLB_EPWM_CLK_CTL;         //offset: 0x20
        union   GLB_CAP_CLK_CTL_REG       GLB_CAP_CLK_CTL;          //offset: 0x24
        union   GLB_QEP_CLK_CTL_REG       GLB_QEP_CLK_CTL;          //offset: 0x28
        union   GLB_QOUT_CLK_CTL_REG      GLB_QOUT_CLK_CTL;         //offset: 0x2C
        union	GLB_EPWM_RST_CTL_REG	  GLB_EPWM_RST_CTL;			//offset: 0x30
        union	GLB_CAP_RST_CTL_REG	  	  GLB_CAP_RST_CTL;			//offset: 0x34
        union	GLB_QEP_RST_CTL_REG	 	  GLB_QEP_RST_CTL;			//offset: 0x38
        union	GLB_QOUT_RST_CTL_REG	  GLB_QOUT_RST_CTL;			//offset: 0x3C
        volatile u32  RES1[4];                                      //offset: 0x40~4F
        union   GLB_EPWM_SYNC_IN_SEL_REG  GLB_EPWM_SYNC_IN_SEL;     //offset: 0x50
        union	SYNC_SRC_IN_SEL_REG		  SYNC_SRC_IN_SEL;			//offset: 0x54
        union	EPWM_FLT_SRC_IN_SEL_REG	  EPWM_FLT_SRC_IN_SEL;		//offset: 0x58
        volatile u32  RES2;                                         //offset: 0x5C
        union   PWM_FAULTIN_FLT1_REG      PWM_FAULTIN_FLT1;         //offset: 0x60
        union   PWM_FAULTIN_FLT2_REG      PWM_FAULTIN_FLT2;         //offset: 0x64
        union   PWM_FAULTIN_FLT3_REG      PWM_FAULTIN_FLT3;         //offset: 0x68
        volatile u32  RES3[5];                                      //offset: 0x6C~7C
        union   GLB_DLL_LDO_EN_REG        GLB_DLL_LDO_EN;           //offset: 0x80
        volatile u32  RES4;                                         //offset: 0x84
        union   GLB_FAULT_STS_REG         GLB_FAULT_STS;            //offset: 0x88
        volatile u32  RES5;                                         //offset: 0x8C
        union   GLB_QOUT_INT_STS_REG      GLB_QOUT_INT_STS;         //offset: 0x90
//        union   GLB_ADC_INT_STS_REG       GLB_ADC_INT_STS;          //offset: 0x94
};

void pwmcs_cmu_init(void);
void epwm_pinmux_init(u8 i);
void epwm_clk_en(u8 i);
void epwm_clk_dis(u8 i);
void epwm_global_en(void);
void epwm_global_dis(void);
void qep_clk_en(u8 i);
void qep_clk_dis(u8 i);
u32  glb_epwm_int_sts(void);
u32  glb_epwm_fault_int_sts(void);
u32  glb_qep_int_sts(void);
u32  glb_cap_int_sts(void);
void glb_hpwm_dll_ldo_en(void);
void glb_hpwm_dll_ldo1_en(void);
void glb_set_epwm3_synin(EPWM_SYNCIN_TYPE src);
void qout_clk_en(u8 i);
void qout_clk_dis(u8 i);
void cap_clk_en(u8 i);
void cap_clk_dis(u8 i);
u32 glb_epwm_fault_sts(void);
void glb_fault_lh_set(u8 i, EPWM_FAULT_LH_TYPE typ);
u32 glb_epwm_fault_lsts(void);

#endif /* INCLUDE_HAL_PWMCS_H_ */
