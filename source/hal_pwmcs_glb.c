/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
#include <all_inc.h>

volatile struct GLB_PWMCS_REGS Glb_Pwmcs_Regs __attribute__((__section__(".glbpwmcsreg")));

/*pwmcs 模块的CMU时钟使能：EPWM, CAP, QEP, QOUT 模块的时钟源*/
void pwmcs_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_PWMCS);
        cmu_mod_enable(CMU_MOD_PWMCS);
}

void epwm_pinmux_init(u8 i)
{
        switch(i) {
                case 0:
                        gpio_enable(GPIO_GRP_E, 0, 2, GPIO_FUN_6);
                        break;
                case 1:
                        gpio_enable(GPIO_GRP_E, 2, 2, GPIO_FUN_6);
                        break;
                case 2:
                        gpio_enable(GPIO_GRP_E, 4, 2, GPIO_FUN_6);
                        break;
                case 3:
                        gpio_enable(GPIO_GRP_E, 6, 2, GPIO_FUN_6);
                        break;
                case 4:
                        gpio_enable(GPIO_GRP_E, 8, 2, GPIO_FUN_6);
                        break;
                case 5:
                        gpio_enable(GPIO_GRP_E, 10, 2, GPIO_FUN_6);
                        break;
                case 6:
                        gpio_enable(GPIO_GRP_E, 12, 2, GPIO_FUN_6);
                        break;
                case 7:
                        gpio_enable(GPIO_GRP_E, 14, 2, GPIO_FUN_6);
                        break;
                case 8:
                        gpio_enable(GPIO_GRP_E, 16, 2, GPIO_FUN_6);
                        break;
                case 9:
                        gpio_enable(GPIO_GRP_E, 18, 2, GPIO_FUN_6);
                        break;
                case 10:
                        gpio_enable(GPIO_GRP_E, 20, 2, GPIO_FUN_6);
                        break;
                case 11:
                        gpio_enable(GPIO_GRP_E, 22, 2, GPIO_FUN_6);
                        break;
                default:
                break;
        }            
}

void epwm_clk_en(u8 i)
{
        switch(i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM0_CLK_EN = 0x1;
                        epwm_link_none(0x0);
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM1_CLK_EN = 0x1;
                        epwm_link_none(0x1);
                        break;
                case 2:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM2_CLK_EN = 0x1;
                        epwm_link_none(0x2);
                        break;
                case 3:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM3_CLK_EN = 0x1;
                        epwm_link_none(0x3);
                        break;
                case 4:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM4_CLK_EN = 0x1;
                        epwm_link_none(0x4);
                        break;
                case 5:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM5_CLK_EN = 0x1;
                        epwm_link_none(0x5);
                        break;
                case 6:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM6_CLK_EN = 0x1;
                        epwm_link_none(0x6);
                        break;
                case 7:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM7_CLK_EN = 0x1;
                        epwm_link_none(0x7);
                        break;
                case 8:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM8_CLK_EN = 0x1;
                        epwm_link_none(0x8);
                        break;
                case 9:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM9_CLK_EN = 0x1;
                        epwm_link_none(0x9);
                        break;
                case 10:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM10_CLK_EN = 0x1;
                        epwm_link_none(0xa);
                        break;
                case 11:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM11_CLK_EN = 0x1;
                        epwm_link_none(0xb);
                        break;                     
                default:
                break;
        }      
}

void epwm_clk_dis(u8 i)
{
        switch(i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM0_CLK_EN = 0x0;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM1_CLK_EN = 0x0;
                        break;
                case 2:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM2_CLK_EN = 0x0;
                        break;
                case 3:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM3_CLK_EN = 0x0;
                        break;
                case 4:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM4_CLK_EN = 0x0;
                        break;
                case 5:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM5_CLK_EN = 0x0;
                        break;
                case 6:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM6_CLK_EN = 0x0;
                        break;
                case 7:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM7_CLK_EN = 0x0;
                        break;
                case 8:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM8_CLK_EN = 0x0;
                        break;
                case 9:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM9_CLK_EN = 0x0;
                        break;
                case 10:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM10_CLK_EN = 0x0;
                        break;
                case 11:
                        Glb_Pwmcs_Regs.GLB_EPWM_CLK_CTL.bit.EPWM11_CLK_EN = 0x0;
                        break;                     
                default:
                break;
        }      
}

void epwm_global_en(void)
{
        Glb_Pwmcs_Regs.GLB_EPWM_EN.bit.GLB_EPWM_EN = 0x1;  
}

void epwm_global_dis(void)
{
        Glb_Pwmcs_Regs.GLB_EPWM_EN.bit.GLB_EPWM_EN = 0x0;  
}

void qep_clk_en(u8 i)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP0_CLK_EN = 0x1;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP1_CLK_EN = 0x1;
                        break;
                case 2:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP2_CLK_EN = 0x1;
                        break;
                case 3:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP3_CLK_EN = 0x1;
                        break;
                case 4:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP4_CLK_EN = 0x1;
                        break;
                case 5:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP5_CLK_EN = 0x1;
                        break;
                case 6:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP6_CLK_EN = 0x1;
                        break;
                case 7:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP7_CLK_EN = 0x1;
                        break;
                case 8:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP8_CLK_EN = 0x1;
                        break;
                case 9:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP9_CLK_EN = 0x1;
                        break;
                default:
                break;
        }      
}

void qep_clk_dis(u8 i)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP0_CLK_EN = 0x0;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP1_CLK_EN = 0x0;
                        break;
                case 2:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP2_CLK_EN = 0x0;
                        break;
                case 3:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP3_CLK_EN = 0x0;
                        break;
                case 4:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP4_CLK_EN = 0x0;
                        break;
                case 5:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP5_CLK_EN = 0x0;
                        break;
                case 6:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP6_CLK_EN = 0x0;
                        break;
                case 7:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP7_CLK_EN = 0x0;
                        break;
                case 8:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP8_CLK_EN = 0x0;
                        break;
                case 9:
                        Glb_Pwmcs_Regs.GLB_QEP_CLK_CTL.bit.QEP9_CLK_EN = 0x0;
                        break;
                default:
                break;
        }      
}

u32 glb_epwm_int_sts(void)
{
        u32 pwm_int_sts;
        pwm_int_sts = Glb_Pwmcs_Regs.GLB_EPWM_INT_STS.all;
        return pwm_int_sts;
}

u32 glb_epwm_fault_int_sts(void)
{
        u32 pwm_fault_int_sts;
        pwm_fault_int_sts = Glb_Pwmcs_Regs.GLB_FAULT_INT_STS.all;
        return pwm_fault_int_sts;
}

u32 glb_cap_int_sts(void)
{
        u32 cap_int_sts;
        cap_int_sts = Glb_Pwmcs_Regs.GLB_CAP_INT_STS.all;
        return cap_int_sts;
}

u32 glb_qep_int_sts(void)
{
        u32 qep_int_sts;
        qep_int_sts = Glb_Pwmcs_Regs.GLB_QEP_INT_STS.all;
        return qep_int_sts;
}

void glb_hpwm_dll_ldo_en(void)
{
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_LVS = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.DLL_LDO_EN = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_CLK = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_VCDL = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_CP = 0x1;
        gtc_dly_time(GTC_US, 100);
}

void glb_hpwm_dll_ldo1_en(void)
{
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_LVS1 = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.DLL1_LDO_EN = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_CLK1 = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_VCDL1 = 0x1;
        gtc_dly_time(GTC_US, 100);
        Glb_Pwmcs_Regs.GLB_DLL_LDO_EN.bit.EN_CP1 = 0x1;
        gtc_dly_time(GTC_US, 100);
}


void glb_set_epwm3_synin(EPWM_SYNCIN_TYPE src)
{
        Glb_Pwmcs_Regs.GLB_EPWM_SYNC_IN_SEL.bit.EPWM3_SYNC_IN_SEL = src;
}

void qout_clk_en(u8 i)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_QOUT_CLK_CTL.bit.QOUT0_CLK_EN = 0x1;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_QOUT_CLK_CTL.bit.QOUT1_CLK_EN = 0x1;
                        break;
                default:
                break;
        }      
}

void qout_clk_dis(u8 i)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_QOUT_CLK_CTL.bit.QOUT0_CLK_EN = 0x0;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_QOUT_CLK_CTL.bit.QOUT1_CLK_EN = 0x0;
                        break;
                default:
                break;
        }      
}

void cap_clk_en(u8 i)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP0_CLK_EN = 0x1;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP1_CLK_EN = 0x1;
                        break;
                case 2:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP2_CLK_EN = 0x1;
                        break;
                case 3:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP3_CLK_EN = 0x1;
                        break;
                case 4:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP4_CLK_EN = 0x1;
                        break;
                case 5:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP5_CLK_EN = 0x1;
                        break;

                default:
                break;
        }      
}

void cap_clk_dis(u8 i)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP0_CLK_EN = 0x0;
                        break;
                case 1:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP1_CLK_EN = 0x0;
                        break;
                case 2:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP2_CLK_EN = 0x0;
                        break;
                case 3:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP3_CLK_EN = 0x0;
                        break;
                case 4:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP4_CLK_EN = 0x0;
                        break;
                case 5:
                        Glb_Pwmcs_Regs.GLB_CAP_CLK_CTL.bit.CAP5_CLK_EN = 0x0;
                        break;

                default:
                break;
        }      
}

u32 glb_epwm_fault_sts(void)
{
        u32 epwm_fault_sts;
        epwm_fault_sts = Glb_Pwmcs_Regs.GLB_FAULT_STS.all;
        epwm_fault_sts &= 0x3f;
        return epwm_fault_sts;
}

void glb_fault_lh_set(u8 i, EPWM_FAULT_LH_TYPE typ)
{
        switch (i) {
                case 0:
                        Glb_Pwmcs_Regs.GLB_FAULT_STS.bit.FALT0_EGE_DET = typ;
                        break;
                case 1:
                		Glb_Pwmcs_Regs.GLB_FAULT_STS.bit.FALT1_EGE_DET = typ;
                        break;
                case 2:
                		Glb_Pwmcs_Regs.GLB_FAULT_STS.bit.FALT2_EGE_DET = typ;
                        break;
                case 3:
                		Glb_Pwmcs_Regs.GLB_FAULT_STS.bit.FALT3_EGE_DET = typ;
                        break;
                case 4:
                		Glb_Pwmcs_Regs.GLB_FAULT_STS.bit.FALT4_EGE_DET = typ;
                        break;
                case 5:
                		Glb_Pwmcs_Regs.GLB_FAULT_STS.bit.FALT5_EGE_DET = typ;
                        break;

                default:
                break;
        }
}

u32 glb_epwm_fault_lsts(void)
{
        u32 epwm_fault_lsts;
        epwm_fault_lsts = Glb_Pwmcs_Regs.GLB_FAULT_STS.all;
        epwm_fault_lsts &= 0x3f00;
        epwm_fault_lsts = epwm_fault_lsts >> 8;
        return epwm_fault_lsts;
}
