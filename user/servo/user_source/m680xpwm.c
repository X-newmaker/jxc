/*
 * m680xpwm.c
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */
#include "all_inc.h"
#include "M680x_it.h"
#include "m680xpwm.h"
extern volatile struct EPWM_REGS *EPWM[];
void M680X_EV1_PWM_Init(PWMGEN *p)
{

}
void FUN0_PWM_AON_BON(u32 n)  //EPWMA、B导通均可设置占空比
{
	    (*EPWM[n]).PWM_OUT_CONF.bit.CH_SET   = CHAB_SEL_PWMA;                   //两个管脚输出通道A信号
		(*EPWM[n]).PWM_OUT_CONF.bit.POL_SET = CHA_POST_CHB_NEGT;                //管脚A不反相，B反相
		(*EPWM[n]).PWM_OUT_CONF.bit.BYPASS_SET  = NO_BP;                        //不旁通
		(*EPWM[n]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_NONE0;
		(*EPWM[n]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_NONE0;
}
void FUN1_PWM_AON_BOFF(u32 n, u32 chb_lv)//EPWMA导通设置占空比、EPWMB可由软件强制高低电平off_lvl: 0x1 set low, 0x2 set high
{
        (*EPWM[n]).PWM_OUT_CONF.bit.CH_SET      = CHAB_SEL_PWMA;                //两个管脚输出通道A信号
		(*EPWM[n]).PWM_OUT_CONF.bit.POL_SET = CHA_NEGT_CHB_POST;                //管脚A反相，B不反相
        (*EPWM[n]).PWM_SW_CT_ACT.bit.BACT_SW_CT = chb_lv;
        (*EPWM[n]).PWM_OUT_CONF.bit.BYPASS_SET  = BP_CHB;                       //两个管脚输出通道B信号
        (*EPWM[n]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_NONE0;
}



void FUN2_PWM_AOFF_BON(u32 n, u32 cha_lv)//EPWMA可由软件强制高低电平、EPWMB导通设置占空比off_lvl: 0x1 set low, 0x2 set high
{
	    (*EPWM[n]).PWM_OUT_CONF.bit.CH_SET      = CHA_SEL_PWMB_CHB_SEL_PWMA;    //
	    (*EPWM[n]).PWM_OUT_CONF.bit.POL_SET = CHA_POST_CHB_NEGT;                //管脚A不反相，B反相
		(*EPWM[n]).PWM_SW_CT_ACT.bit.AACT_SW_CT = cha_lv;
        (*EPWM[n]).PWM_OUT_CONF.bit.BYPASS_SET  = NO_BP;                        //不旁通
        (*EPWM[n]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_NONE0;
}

void FUN3_PWM_AOFF_BOFF(u32 n, u32 cha_lv, u32 chb_lv)//EPWMA、B可由软件强制高低电平0x1 set low, 0x2 set high
{
	    (*EPWM[n]).PWM_OUT_CONF.bit.CH_SET      = CHA_SEL_PWMA_CHB_SEL_PWMB;    //两个管脚输出通道A信号
	    (*EPWM[n]).PWM_OUT_CONF.bit.POL_SET = CHA_POST_CHB_NEGT;                //管脚A不反相，B反相
	    (*EPWM[n]).PWM_SW_CT_ACT.bit.AACT_SW_CT = cha_lv;
        (*EPWM[n]).PWM_SW_CT_ACT.bit.BACT_SW_CT = chb_lv;
		(*EPWM[n]).PWM_OUT_CONF.bit.BYPASS_SET  = BP_CHA_AND_CHB;               //旁通
}
void M680X_EV1_PWM_On(PWMGEN *p)//pwm1.pwm_on(&pwm1);
{
	 gpio_set_val(ioPWMcsOut, GPIO_LEVEL_LOW);
	 //	 FUN0_PWM_AON_BON(Aixse1_EPWM_U);
	 //	 FUN0_PWM_AON_BON(Aixse1_EPWM_V);
	 //	 FUN0_PWM_AON_BON(Aixse1_EPWM_W);
	 (*EPWM[Aixse1_EPWM_U]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_NONE0;
	 (*EPWM[Aixse1_EPWM_U]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_NONE0;
	 (*EPWM[Aixse1_EPWM_V]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_NONE0;
	 (*EPWM[Aixse1_EPWM_V]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_NONE0;
	 (*EPWM[Aixse1_EPWM_W]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_NONE0;
	 (*EPWM[Aixse1_EPWM_W]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_NONE0;
}

void M680X_EV1_PWM_Off(PWMGEN *p)//pwm1.pwm_off(&pwm1);//关闭EPWM
{
	 gpio_set_val(ioPWMcsOut, GPIO_LEVEL_HIGH);
	 //	 FUN3_PWM_AOFF_BOFF(Aixse1_EPWM_U,CTACT_LOW,CTACT_LOW);
	 //	 FUN3_PWM_AOFF_BOFF(Aixse1_EPWM_V,CTACT_LOW,CTACT_LOW);
	 //	 FUN3_PWM_AOFF_BOFF(Aixse1_EPWM_W,CTACT_LOW,CTACT_LOW);
	 (*EPWM[Aixse1_EPWM_U]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_LOW;
	 (*EPWM[Aixse1_EPWM_U]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_LOW;
	 (*EPWM[Aixse1_EPWM_V]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_LOW;
	 (*EPWM[Aixse1_EPWM_V]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_LOW;
	 (*EPWM[Aixse1_EPWM_W]).PWM_SW_CT_ACT.bit.AACT_SW_CT = CTACT_LOW;
	 (*EPWM[Aixse1_EPWM_W]).PWM_SW_CT_ACT.bit.BACT_SW_CT = CTACT_LOW;
}
void M680X_EV1_PWM_Update(PWMGEN *p)
{

}


