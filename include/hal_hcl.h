/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_HCL_H_
#define INCLUDE_HAL_HCL_H_

typedef enum{
        HCL_OPM0 = 0,
        HCL_OPM1,
        HCL_OPM2,
}HCL_OPM_TYPE;

typedef enum{
        QEP_POS = 0,
        TA_POS,
        BIS_POS,
        EDT_POS,
}HCL_POSM_TYPE;

typedef enum{
        NONE = 0,
        HCL_NODEA,
        HCL_NODEB,
        HCL_NODEC,
        HCL_NODED,
        HCL_NODEE,
        HCL_NODEF,
        HCL_NODEG,
}HCL_POINT_TYPE;

typedef enum{
        RPT_RPM = 0,
        RPT_POS,
}HCL_SPD_RPT_TYPE;

/***************************************************************************
                        Register Description
***************************************************************************/

union HCL_CFG_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 HCL_EN:1;                          //0     Hardware Current Loop Enable
                volatile u32 HCL_BPM_EN:1;                      //1     Breakpoint Mode Enable       
                volatile u32 POS_MODE:2;                        //3:2   Position Senser Mode
                volatile u32 HCL_OP_MODE:2;                     //5:4   HCL Operation Mode
                volatile u32 OUT_MODE:2;                        //7:6   OUT_MODE
                volatile u32 BP_NODE:4;                         //11:8  Breakpoint Node 
                volatile u32 RP_NODE:4;                         //15:12 Resume Point Node 
                volatile u32 DT_COMP_EN:1;                      //16    Deadtime Compensation Enable 
                volatile u32 ADC_SWAP_EN:1;                     //17    ADC Result Swap Enable
                volatile u32 FPGA_MOD_EN:1;                     //18    FPGA Mode Enable
                volatile u32 DT_COMP_SW_EN:1;                   //19    Deadtime Compensation Software Enable
                volatile u32 CUR_SRC_SEL:1;                     //20    CUR_SRC_SEL
                volatile u32 IU_SDFM_SRC:2;                     //22:21 IU_SDFM_SRC
                volatile u32 rsvd1:1;                           //23    Reserved
                volatile u32 IV_SDFM_SRC:2;                     //25:24 IV_SDFM_SRC
                volatile u32 TRG_MOD:2;                         //27:26 TRG_MOD
                volatile u32 POS_DAT_SHIFT:4;                   //31:28 POS_DAT_SHIFT
        }bit;
};

union HCL_INT_CFG_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 BP_IRQ_EN:1;                       //0     BreakPoint IRQ Enable
                volatile u32 HCL_DNE_IRQ_EN:1;                  //1     HCL IRQ Enable       
                volatile u32 D_PID_UF_EN:1;                     //2     D-PID Underflow Enable
                volatile u32 D_PID_OF_EN:1;                     //3     D-PID Overflow Enable
                volatile u32 Q_PID_UF_EN:1;                     //4     Q-PID Underflow Enable
                volatile u32 Q_PID_OF_EN:1;                     //5     Q-PID Overflow Enable
                volatile u32 FPGA_IRQ_EN:1;                     //6     FPGA Mode IRQ Enable
                volatile u32 rsvd0:25;                          //31:7  Reserved          
        }bit;
};

union HCL_INT_STS_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 BP_STS:1;                          //0     BreakPoint IRQ Status
                volatile u32 HCL_DNE_STS:1;                     //1     HCL IRQ Status       
                volatile u32 D_PID_STS:1;                       //2     D-PID Underflow Status
                volatile u32 D_PID_OF_STS:1;                    //3     D-PID Overflow Status
                volatile u32 Q_PID_UF_STS:1;                    //4     Q-PID Underflow Status
                volatile u32 Q_PID_OF_STS:1;                    //5     Q-PID Overflow Status
                volatile u32 FPGA_IRQ_STS:1;                    //6     FPGA Mode IRQ Status
                volatile u32 rsvd0:25;                          //31:7  Reserved          
        }bit;
};

union FUNC_EN_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 RP_START:1;                        //0     Resume Point Start
                volatile u32 FSM_CLR:1;                         //1     FSM Clear       
                volatile u32 PID_CLR:1;                         //2     PID Clear
                volatile u32 SPD_AVG_CLR:1;                     //3     SPD_AVG_CLR
                volatile u32 CORDIC_CLR:1;                      //4     Cordic Clear
                volatile u32 DT_COMP_CLR:1;                     //5     DT_COMP_CLR
                volatile u32 rsvd0:2;                           //7:6   Reserved
                volatile u32 FPGA_RESUME:1;                     //8     FPGA mode Resume
                volatile u32 rsvd1:23;                          //31:9  Reserved
        }bit;
};

union VAL_13B_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 VAL:13;                            //12:0  Value
                volatile u32 rsvd0:19;                          //31:13 Reserved
        }bit;
};

union VAL_14B_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 VAL:14;                            //13:0  Value
                volatile u32 rsvd0:18;                          //31:14 Reserved
        }bit;
};

union VAL_16B_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 VAL:16;                            //15:0  Value
                volatile u32 rsvd0:16;                          //31:16 Reserved 
        }bit;
};

union VAL_18B_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 VAL:18;                            //17:0  Value
                volatile u32 rsvd0:14;                          //31:18 Reserved
        }bit;
};

union VAL_24B_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 VAL:24;                            //23:0  Value
                volatile u32 rsvd0:8;                           //31:24 Reserved 
        }bit;
};

union VAL_25B_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 VAL:25;                            //24:0  Value
                volatile u32 rsvd0:7;                           //31:25 Reserved
        }bit;
};


union VAL_20B_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 VAL:20;                            //19:0  Value
                volatile u32 rsvd0:12;                          //31:20 Reserved 
        }bit;
};

union VAL_12B_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 VAL:12;                            //11:0  Value
                volatile u32 rsvd0:20;                          //31:12 Reserved 
        }bit;
};

union HCL_CFG2_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 CUR_DAT_SRC:1;                     //0     CUR_DAT_SRC
                volatile u32 POS_DAT_SRC:1;                     //1     POS_DAT_SRC
                volatile u32 rsvd0:1;                           //2  	Reserved
                volatile u32 ETHETA_CAL_RS:5;                   //7:3  	ETHETA_CAL_RS
                volatile u32 DCP_MOD_SEL:2;                     //9:8 	DCP_MOD_SEL
                volatile u32 rsvd1:2;                           //11:10 Reserved
                volatile u32 OMEG_RS:4;                         //15:12 OMEG_RS
                volatile u32 POS_COMP_EN:1;                     //16  	POS_COMP_EN
                volatile u32 VOL_COMP_EN:1;                     //17  	POS_COMP_EN
                volatile u32 OVM_COMP_EN:1;                     //18  	OVM_COMP_EN
                volatile u32 rsvd2:1;                           //19  	Reserved
                volatile u32 SPD_CAL_RS:5;                      //24:20 SPD_CAL_RS
                volatile u32 SPD_CAL_RS1:5;                     //29:25 SPD_CAL_RS1
                volatile u32 rsvd3:2;                           //31:30 Reserved
        }bit;
};

union SPD_CFG_REG {
        volatile u32  all;
        struct{                                                 //bit description                       
                volatile u32 FLT_TIME:3;                        //2:0  FLT_TIME
                volatile u32 rsvd0:9;                           //11:3  Reserved
                volatile u32 SPD_RPT_SEL:1;                     //12    Speed Report Select
                volatile u32 rsvd1:3;                           //15:13 Reserved
                volatile u32 SPD_DEL_NUM:8;                     //23:16 Speed Delta Number
                volatile u32 HCL_ENC_RATIO:5;                   //28:24 HCL_ENC_RATIO
                volatile u32 rsvd2:2;                           //30:29  Reserved
                volatile u32 HCL_ENC_RATIO_EN:1;                //31 HCL_ENC_RATIO_EN

        }bit;
};

union SPD_OUT_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 SPD_OUT:16;                        //15:0
                volatile u32 SPD_OUT_AVG:16;                    //31:16
        }bit;
};

struct HCL_REGS {                       
        union   HCL_CFG_REG        HCL_CFG;          //offset: 0x00                       
        union   HCL_INT_CFG_REG    HCL_INT_CFG;      //offset: 0x04
        union   HCL_INT_STS_REG    HCL_INT_STS;      //offset: 0x08  
        union   FUNC_EN_REG        FUNC_EN;          //offset: 0x0C
        union   VAL_16B_REG        RSP_PARA0;        //offset: 0x10
        union   VAL_16B_REG        RSP_PARA1;        //offset: 0x14
        union   VAL_16B_REG        RSP_PARA2;        //offset: 0x18
        union   VAL_16B_REG        RSP_PARA3;        //offset: 0x1C
        volatile u32  RES0[8];                       //offset: 0x20/24/28/2C/30/34/38/3C   
        volatile u32  RES1[4];                       //offset: 0x40/44/48/4C
        union   HCL_CFG2_REG        HCL_CFG2;        //offset: 0x50
        union   VAL_16B_REG        USRC_DAT;         //offset: 0x54
        union   VAL_16B_REG        VSRC_DAT;         //offset: 0x58
        union   VAL_24B_REG        PSRC_DAT;         //offset: 0x5C
        union   VAL_24B_REG        REG_BUS;          //offset: 0x60
        volatile u32  RES2[39];                      //offset: 0x64~0xFC
        union   VAL_14B_REG        CUR_U_OS;         //offset: 0x100
        union   VAL_14B_REG        CUR_V_OS;         //offset: 0x104
        union   VAL_16B_REG        CUR_CAL_GAIN;     //offset: 0x108
        union   VAL_24B_REG        QEP_INIT_POS;     //offset: 0x10C
        union   VAL_24B_REG        QEP_POS_CAL;      //offset: 0x110
        union   VAL_24B_REG        QEP_MAX_POS;      //offset: 0x114  
        union   VAL_24B_REG        QEP_ELECT_MAX;    //offset: 0x118
        union   VAL_24B_REG        QEP_ELECT_FAC;    //offset: 0x11C
        union   VAL_25B_REG        ABS_POS_COMP;     //offset: 0x120
        union   VAL_24B_REG        ABS_MAX_POS;      //offset: 0x124
        union   VAL_24B_REG        ABS_ELECT_MAX;    //offset: 0x128  
        volatile u32               ABS_ELECT_FAC;    //offset: 0x12C
        volatile u32               ABS_DA_COMP;      //offset: 0x130
        volatile u32  RES3;                          //offset: 0x134
        union   VAL_16B_REG        THETA0;           //offset: 0x138
        volatile u32  RES4;                          //offset: 0x13C
        union   VAL_16B_REG        UDM0;             //offset: 0x140
        union   VAL_16B_REG        UQM0;             //offset: 0x144  
        union   VAL_16B_REG        ID_REF;           //offset: 0x148
        union   VAL_16B_REG        IQ_REF;           //offset: 0x14C
        union   VAL_16B_REG        SDFM_UOFF;        //offset: 0x150
        union   VAL_16B_REG        SDFM_VOFF;        //offset: 0x154
        volatile u32  RES5[2];                       //offset: 0x158/15C
        union   VAL_20B_REG        DPID_KP;          //offset: 0x160
        union   VAL_16B_REG        DPID_KI;          //offset: 0x164
        union   VAL_16B_REG        DPID_UMAX;        //offset: 0x168
        union   VAL_16B_REG        DPID_UMIN;        //offset: 0x16C
        union   VAL_16B_REG        DPID_COMP;        //offset: 0x170
        volatile u32  RES6[3];                       //offset: 0x174/178/17C
        union   VAL_20B_REG        QPID_KP;          //offset: 0x180
        union   VAL_16B_REG        QPID_KI;          //offset: 0x184
        union   VAL_16B_REG        QPID_UMAX;        //offset: 0x188
        union   VAL_16B_REG        QPID_UMIN;        //offset: 0x18C
        volatile u32  RES7;                          //offset: 0x190
        union   VAL_16B_REG        QPID_COMP;        //offset: 0x194
        union   VAL_16B_REG        INTG_SEP_ERR;     //offset: 0x198
        volatile u32  RES8;                          //offset: 0x19C
        union   VAL_16B_REG        DT_LP_FLT;        //offset: 0x1A0
        union   VAL_16B_REG        DT_COMP_DAT;      //offset: 0x1A4
        volatile u32  RES9[2];                       //offset: 0x1A8/1AC
        union   VAL_20B_REG        PWM_TIMCOST;      //offset: 0x1B0
        union   VAL_16B_REG        PWM_PRD;          //offset: 0x1B4
        union   VAL_16B_REG        MAXDUTY;          //offset: 0x1B8
        union   VAL_16B_REG        MINDUTY;          //offset: 0x1BC
        union   VAL_16B_REG        PRD_OM;     		 //offset: 0x1C0
        volatile u32        	   AE_SPDMCOFF0;     //offset: 0x1C4
        volatile u32        	   AE_SPDMCOFF1;     //offset: 0x1C8
        union   VAL_24B_REG        ABS_MAX_DPOS;     //offset: 0x1CC
        union   SPD_CFG_REG        SPD_CFG;          //offset: 0x1D0
        union   VAL_24B_REG        SPD_DIR_THR;      //offset: 0x1D4
        union   VAL_16B_REG        DZCP_ALPHA;       //offset: 0x1D8
        union   VAL_16B_REG        DZCP_BETA;        //offset: 0x1DC
        union   VAL_16B_REG        SDFM_GAIN;        //offset: 0x1E0
        union   VAL_14B_REG        AVG_BUS_VAL;      //offset: 0x1E4
        union   VAL_14B_REG        AVG_BUS_Q14;      //offset: 0x1E8
        union   VAL_13B_REG        VCOMP_MAX;        //offset: 0x1EC
        union   VAL_13B_REG        VCOMP_MIN;        //offset: 0x1F0
        volatile u32  RES10[3];                      //offset: 0x1F4~1FC
        union   SPD_OUT_REG        SPD_OUT;          //offset: 0x200
        volatile u32  SPD_OUT1;                      //offset: 0x204
        union   VAL_24B_REG        ELECT_OUT;        //offset: 0x208
        union   VAL_24B_REG        POS_RAW;          //offset: 0x20C
        volatile u32  RES11[28];                     //offset: 0x210~27C
        union   VAL_18B_REG        FREDIV_RATE;      //offset: 0x280
        union   VAL_16B_REG        ISDPU;            //offset: 0x284
        union   VAL_16B_REG        ISQPU;            //offset: 0x288
        union   VAL_16B_REG        LD;               //offset: 0x28C
        union   VAL_16B_REG        LQ;               //offset: 0x290
        union   VAL_16B_REG        FLUX_ROT;         //offset: 0x294
        volatile u32  RES12[26];                     //offset: 0x298~2FC
        union   VAL_14B_REG        NODA_DIU;         //offset: 0x300
        union   VAL_14B_REG        NODA_DIV;         //offset: 0x304
        union   VAL_16B_REG        NODB_PDIU;        //offset: 0x308
        union   VAL_16B_REG        NODB_PDIV;        //offset: 0x30C
        union   VAL_16B_REG        NODC_IA;          //offset: 0x310
        union   VAL_16B_REG        NODC_IB;          //offset: 0x314  
        union   VAL_16B_REG        NODD_ID;          //offset: 0x318
        union   VAL_16B_REG        NODD_IQ;          //offset: 0x31C
        union   VAL_16B_REG        NODE_UD;          //offset: 0x320
        union   VAL_16B_REG        NODE_UQ;          //offset: 0x324
        union   VAL_16B_REG        NODF_UA;          //offset: 0x328  
        union   VAL_16B_REG        NODF_UB;          //offset: 0x32C
        union   VAL_16B_REG        NODG_TD0;         //offset: 0x330
        union   VAL_16B_REG        NODG_TD1;         //offset: 0x334
        union   VAL_16B_REG        NODG_TD2;         //offset: 0x338
        union   VAL_16B_REG        COMP_ALPHA;       //offset: 0x33C
        union   VAL_16B_REG        COMP_BETA;        //offset: 0x340
        union   VAL_16B_REG        VCOMP_COFF;       //offset: 0x344
        union   VAL_16B_REG        VCOMP_UDC;        //offset: 0x348
        union   VAL_16B_REG        VCOMP_UQC;        //offset: 0x34C
};

void hcl_irq_handler(void);
void hcl_irq_register(cpu_irq_fun_t irqhandle);
void hcl_irq_unregister(void);
void hcl_cmu_init(void);
void hcl_en(u8 n);
void hcl_dis(u8 n);
void hcl_bpm_en(u8 n);
void hcl_bpm_dis(u8 n);
void hcl_set_posm(u8 n, HCL_POSM_TYPE posm);
void hcl_set_opm(u8 n, HCL_OPM_TYPE opm);
void hcl_set_bp(u8 n, HCL_POINT_TYPE point);
void hcl_set_rp(u8 n, HCL_POINT_TYPE point);
void hcl_dtcmp_en(u8 n);
void hcl_dtcmp_dis(u8 n);
void hcl_adc_swap_en(u8 n);
void hcl_adc_swap_dis(u8 n);
void hcl_bpirq_en(u8 n);
void hcl_bpirq_dis(u8 n);
void hcl_doneirq_en(u8 n);
void hcl_doneirq_dis(u8 n);
void hcl_rp_start(u8 n);
void hcl_pid_clr(u8 n);
void hcl_cor_clr(u8 n);
void hcl_set_rpara0(u8 n, u16 rpara0);
void hcl_set_rpara1(u8 n, u16 rpara1);
void hcl_set_rpara2(u8 n, u16 rpara2);
void hcl_set_rpara3(u8 n, u16 rpara3);
void hcl_set_udm0(u8 n, s16 udm0);
void hcl_set_uqm0(u8 n, s16 udm0);
void hcl_set_epwmprd(u8 n, u16 epwmprd);
void hcl_set_maxduty(u8 n, u16 maxduty);
void hcl_set_minduty(u8 n, u16 minduty);
void hcl_set_timeconst(u8 n, u32 timeconst);
void hcl_set_curcal(u8 n, s16 curcal);
void hcl_set_qpidkp(u8 n, s32 qpidkp);
void hcl_set_qpidki(u8 n, s16 qpidki);
void hcl_set_qpidmax(u8 n, s16 qpidmax);
void hcl_set_qpidmin(u8 n, s16 qpidmin);
void hcl_set_intgsep(u8 n, s16 intgsep);
void hcl_set_dpidkp(u8 n, s32 dpidkp);
void hcl_set_dpidki(u8 n, s16 dpidki);
void hcl_set_dpidmax(u8 n, s16 dpidmax);
void hcl_set_dpidmin(u8 n, s16 dpidmin);
void hcl_set_iqref(u8 n, s16 iqref);
void hcl_set_idref(u8 n, s16 idref);
void hcl_set_theta0(u8 n, s16 theta0);
void hcl_set_qepmax(u8 n, u32 qepmax);
void hcl_set_qep_elec_max(u8 n, u32 qep_elec_max);
void hcl_set_qep_elec_fact(u8 n, u32 qep_elec_fact);
void hcl_set_absmax(u8 n, u32 absmax);
void hcl_set_abs_elec_max(u8 n, u32 abs_elec_max);
void hcl_set_abs_elec_fact(u8 n, u32 abs_elec_fact);
void hcl_set_abs_elec_fact(u8 n, u32 abs_elec_fact);
void hcl_set_abs_spdmcoff(u8 n, u32 qep_spdmcoff);
void hcl_set_abs_spdmcoff1(u8 n, u32 abs_spdmcoff);
void hcl_set_abs_maxdpos(u8 n, u32 abs_maxdpos);
void hcl_set_spd_dirth(u8 n, u32 spd_dirth);
void hcl_set_spd_dirth(u8 n, u32 spd_dirth);
void hcl_set_spd_rpt(u8 n, HCL_SPD_RPT_TYPE spd_type);
void hcl_set_spd_testdel(u8 n, u8 del);
void hcl_set_dtcomp(u8 n, u16 dtcomp);
void hcl_set_dtflt(u8 n, u16 dtflt);
void hcl_set_uoff(u8 n, u16 uoff);
void hcl_set_voff(u8 n, u16 voff);
u32 hcl_get_raw_pos(u8 n);
void hcl_set_qep_init_pos(u8 n, u32 init_pos);
u32 hcl_get_spd(u8 n);

void hcl_set_cur_src(u8 n, u16 src);
void hcl_u_sdfm_src(u8 n, u16 src);
void hcl_v_sdfm_src(u8 n, u16 src);
void hcl_dual_trg_mod(u8 n, u16 mod);
void hcl_pos_rshift(u8 n, u16 shift);
void hcl_cur_dat_sel(u8 n, u16 sel);
void hcl_pos_dat_sel(u8 n, u16 sel);
void hcl_reg_usrc_set(u8 n, s16 set);
void hcl_reg_vsrc_set(u8 n, s16 set);
void hcl_reg_psrc_set(u8 n, u32 set);
void hcl_sdfm_gain_set(u8 n, u16 set);
void hcl_sdfm_uoff_set(u8 n, u16 set);
void hcl_sdfm_voff_set(u8 n, u16 set);
#endif /* INCLUDE_HAL_HCL_H_ */
