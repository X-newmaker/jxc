/*
 * Copyright (c) 2022-2025, ArtInChip Technology Co., Ltd
 *
 */
#include <all_inc.h>
volatile struct HCL_REGS Hcl0Regs __attribute__((__section__(".hcl0reg")));
volatile struct HCL_REGS Hcl1Regs __attribute__((__section__(".hcl1reg")));

volatile struct HCL_REGS *HCL[] = {&Hcl0Regs, &Hcl1Regs};

static void hcl_null(void){};
cpu_irq_fun_t hcl_irqhandle = hcl_null;

ATTRIBUTE_ISR void HCL_IRQHandler(void)
{
        hcl_irq_handler();
}

void hcl_irq_handler(void)
{
        hcl_irqhandle();
}

void hcl_irq_register(cpu_irq_fun_t irqhandle)
{
        hcl_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_HCL);
}

void hcl_irq_unregister(void)
{
        hcl_irqhandle = hcl_null;
        cpu_irq_disable(CPU_IRQ_HCL);
}

void hcl_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_CORDIC);
	cmu_mod_disable(CMU_MOD_HCL);

        cmu_mod_enable(CMU_MOD_CORDIC);
        cmu_mod_enable(CMU_MOD_HCL);
}

void hcl_en(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.HCL_EN = 0x1;
}

void hcl_dis(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.HCL_EN = 0x0;
}

void hcl_bpm_en(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.HCL_BPM_EN = 0x1;
}

void hcl_bpm_dis(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.HCL_BPM_EN = 0x0;
}

void hcl_set_posm(u8 n, HCL_POSM_TYPE posm)
{
	(*HCL[n]).HCL_CFG.bit.POS_MODE = posm;
}

void hcl_set_opm(u8 n, HCL_OPM_TYPE opm)
{
	(*HCL[n]).HCL_CFG.bit.HCL_OP_MODE = opm;
}

void hcl_set_bp(u8 n, HCL_POINT_TYPE point)
{
	(*HCL[n]).HCL_CFG.bit.BP_NODE = point;
}

void hcl_set_rp(u8 n, HCL_POINT_TYPE point)
{
	(*HCL[n]).HCL_CFG.bit.RP_NODE = point;
}

void hcl_dtcmp_en(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.DT_COMP_EN = 0x1;
}

void hcl_dtcmp_dis(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.DT_COMP_EN = 0x0;
}

void hcl_adc_swap_en(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.ADC_SWAP_EN = 0x1;
}

void hcl_adc_swap_dis(u8 n)
{
	(*HCL[n]).HCL_CFG.bit.ADC_SWAP_EN = 0x0;
}

void hcl_bpirq_en(u8 n)
{
	(*HCL[n]).HCL_INT_CFG.bit.BP_IRQ_EN = 0x1;
}

void hcl_bpirq_dis(u8 n)
{
	(*HCL[n]).HCL_INT_CFG.bit.BP_IRQ_EN = 0x0;
}

void hcl_doneirq_en(u8 n)
{
	(*HCL[n]).HCL_INT_CFG.bit.HCL_DNE_IRQ_EN = 0x1;
}

void hcl_doneirq_dis(u8 n)
{
	(*HCL[n]).HCL_INT_CFG.bit.HCL_DNE_IRQ_EN = 0x0;
}

void hcl_rp_start(u8 n)
{
	(*HCL[n]).FUNC_EN.bit.RP_START = 0x1;
}

void hcl_pid_clr(u8 n)
{
	(*HCL[n]).FUNC_EN.bit.PID_CLR = 0x1;
}

void hcl_cor_clr(u8 n)
{
	(*HCL[n]).FUNC_EN.bit.CORDIC_CLR = 0x1;
}

void hcl_set_rpara0(u8 n, u16 rpara0)
{
	(*HCL[n]).RSP_PARA0.bit.VAL = rpara0;
}

void hcl_set_rpara1(u8 n, u16 rpara1)
{
	(*HCL[n]).RSP_PARA1.bit.VAL = rpara1;
}

void hcl_set_rpara2(u8 n, u16 rpara2)
{
	(*HCL[n]).RSP_PARA2.bit.VAL = rpara2;
}

void hcl_set_rpara3(u8 n, u16 rpara3)
{
	(*HCL[n]).RSP_PARA3.bit.VAL = rpara3;
}

void hcl_set_udm0(u8 n, s16 udm0)
{
	(*HCL[n]).UDM0.bit.VAL = udm0;
//	printk("UDM0 set is 0x%x\n", (*HCL[n]).UDM0.all);
}

void hcl_set_uqm0(u8 n, s16 udm0)
{
	(*HCL[n]).UQM0.bit.VAL = udm0;
//	printk("UQM0 set is 0x%x\n", (*HCL[n]).UQM0.all);
}

void hcl_set_epwmprd(u8 n, u16 epwmprd)
{
	(*HCL[n]).PWM_PRD.bit.VAL = epwmprd;
//	printk("PWM_PRD set is 0x%x\n", (*HCL[n]).PWM_PRD.all);
}

void hcl_set_maxduty(u8 n, u16 maxduty)
{
	(*HCL[n]).MAXDUTY.bit.VAL = maxduty;
//	printk("MAXDUTY set is 0x%x\n", (*HCL[n]).MAXDUTY.all);
}

void hcl_set_minduty(u8 n, u16 minduty)
{
	(*HCL[n]).MINDUTY.bit.VAL = minduty;
//	printk("MINDUTY set is 0x%x\n", (*HCL[n]).MINDUTY.all);
}

void hcl_set_timeconst(u8 n, u32 timeconst)
{
	(*HCL[n]).PWM_TIMCOST.bit.VAL = timeconst & 0xFFFFF;
//	printk("PWM_TIMCOST set is 0x%x\n", (*HCL[n]).PWM_TIMCOST.all);
}

void hcl_set_curcal(u8 n, s16 curcal)
{
	(*HCL[n]).CUR_CAL_GAIN.bit.VAL = curcal;
//	printk("CUR_CAL_GAIN set is 0x%x\n", (*HCL[n]).CUR_CAL_GAIN.all);
}

void hcl_set_qpidkp(u8 n, s32 qpidkp)
{
	(*HCL[n]).QPID_KP.bit.VAL = qpidkp;
//	printk("QPID_KP set is 0x%x\n", (*HCL[n]).QPID_KP.all);
}

void hcl_set_qpidki(u8 n, s16 qpidki)
{
	(*HCL[n]).QPID_KI.bit.VAL = qpidki;
//	printk("QPID_KI set is 0x%x\n", (*HCL[n]).QPID_KI.all);
}

void hcl_set_qpidmax(u8 n, s16 qpidmax)
{
	(*HCL[n]).QPID_UMAX.bit.VAL = qpidmax;
//	printk("QPID_UMAX set is 0x%x\n", (*HCL[n]).QPID_UMAX.all);
}

void hcl_set_qpidmin(u8 n, s16 qpidmin)
{
	(*HCL[n]).QPID_UMIN.bit.VAL = qpidmin;
//	printk("QPID_UMIN set is 0x%x\n", (*HCL[n]).QPID_UMIN.all);
}

void hcl_set_intgsep(u8 n, s16 intgsep)
{
	(*HCL[n]).INTG_SEP_ERR.bit.VAL = intgsep;
//	printk("INTG_SEP_ERR set is 0x%x\n", (*HCL[n]).INTG_SEP_ERR.all);
}

void hcl_set_dpidkp(u8 n, s32 dpidkp)
{
	(*HCL[n]).DPID_KP.bit.VAL = dpidkp;
//	printk("DPID_KP set is 0x%x\n", (*HCL[n]).DPID_KP.all);
}

void hcl_set_dpidki(u8 n, s16 dpidki)
{
	(*HCL[n]).DPID_KI.bit.VAL = dpidki;
//	printk("DPID_KI set is 0x%x\n", (*HCL[n]).DPID_KI.all);
}

void hcl_set_dpidmax(u8 n, s16 dpidmax)
{
	(*HCL[n]).DPID_UMAX.bit.VAL = dpidmax;
//	printk("DPID_UMAX set is 0x%x\n", (*HCL[n]).DPID_UMAX.all);
}

void hcl_set_dpidmin(u8 n, s16 dpidmin)
{
	(*HCL[n]).DPID_UMIN.bit.VAL = dpidmin;
//	printk("DPID_UMIN set is 0x%x\n", (*HCL[n]).DPID_UMIN.all);
}

void hcl_set_iqref(u8 n, s16 iqref)
{
	(*HCL[n]).IQ_REF.bit.VAL = iqref;
//	printk("IQ_REF set is 0x%x\n", (*HCL[n]).IQ_REF.all);
}

void hcl_set_idref(u8 n, s16 idref)
{
	(*HCL[n]).ID_REF.bit.VAL = idref;
//	printk("ID_REF set is 0x%x\n", (*HCL[n]).ID_REF.all);
}

void hcl_set_theta0(u8 n, s16 theta0)
{
	(*HCL[n]).THETA0.bit.VAL = theta0;
//	printk("THETA0 set is 0x%x\n", (*HCL[n]).THETA0.all);
}

void hcl_set_qepmax(u8 n, u32 qepmax)
{
	(*HCL[n]).QEP_MAX_POS.bit.VAL = qepmax & 0xFFFFFF;
//	printk("QEP_MAX_POS set is 0x%x\n", (*HCL[n]).QEP_MAX_POS.all);
}

void hcl_set_qep_elec_max(u8 n, u32 qep_elec_max)
{
	(*HCL[n]).QEP_ELECT_MAX.bit.VAL = qep_elec_max & 0xFFFFFF;
//	printk("QEP_ELECT_MAX set is 0x%x\n", (*HCL[n]).QEP_ELECT_MAX.all);
}

void hcl_set_qep_elec_fact(u8 n, u32 qep_elec_fact)
{
	(*HCL[n]).QEP_ELECT_FAC.bit.VAL = qep_elec_fact & 0xFFFFFF;
//	printk("QEP_ELECT_FAC set is 0x%x\n", (*HCL[n]).QEP_ELECT_FAC.all);
}

void hcl_set_absmax(u8 n, u32 absmax)
{
	(*HCL[n]).ABS_MAX_POS.bit.VAL = absmax & 0xFFFFFF;

}

void hcl_set_abs_elec_max(u8 n, u32 abs_elec_max)
{
	(*HCL[n]).ABS_ELECT_MAX.bit.VAL = abs_elec_max & 0xFFFFFF;
}

void hcl_set_abs_elec_fact(u8 n, u32 abs_elec_fact)
{
	(*HCL[n]).ABS_ELECT_FAC = abs_elec_fact;
}

void hcl_set_ae_spdmcoff(u8 n, u32 abs_spdmcoff)
{
	(*HCL[n]).AE_SPDMCOFF0 = abs_spdmcoff;
}

void hcl_set_ae_spdmcoff1(u8 n, u32 abs_spdmcoff)
{
	(*HCL[n]).AE_SPDMCOFF1 = abs_spdmcoff;
}

void hcl_set_abs_maxdpos(u8 n, u32 abs_maxdpos)
{
	(*HCL[n]).ABS_MAX_DPOS.bit.VAL = abs_maxdpos & 0xFFFFFF;
}

void hcl_set_spd_dirth(u8 n, u32 spd_dirth)
{
	(*HCL[n]).SPD_DIR_THR.bit.VAL = spd_dirth & 0xFFFFFF;
}

void hcl_set_spd_rpt(u8 n, HCL_SPD_RPT_TYPE spd_type)
{
	(*HCL[n]).SPD_CFG.bit.SPD_RPT_SEL = spd_type;
}

void hcl_set_spd_testdel(u8 n, u8 del)
{
	(*HCL[n]).SPD_CFG.bit.SPD_DEL_NUM = del;
}

void hcl_set_dtcomp(u8 n, u16 dtcomp)
{
	(*HCL[n]).DT_COMP_DAT.bit.VAL = dtcomp;
}

void hcl_set_dtflt(u8 n, u16 dtflt)
{
	(*HCL[n]).DT_LP_FLT.bit.VAL = dtflt;
}

void hcl_set_uoff(u8 n, u16 uoff)
{
	(*HCL[n]).CUR_U_OS.bit.VAL = uoff;
//	printk("CUR_U_OS set is 0x%x\n", (*HCL[n]).CUR_U_OS.all);
}

void hcl_set_voff(u8 n, u16 voff)
{
	(*HCL[n]).CUR_V_OS.bit.VAL = voff;
//	printk("CUR_V_OS set is 0x%x\n", (*HCL[n]).CUR_V_OS.all);
}

u32 hcl_get_raw_pos(u8 n)
{
	u32 raw_pos;
	raw_pos = (*HCL[n]).POS_RAW.all;
	return raw_pos;
}

void hcl_set_qep_init_pos(u8 n, u32 init_pos)
{
	(*HCL[n]).QEP_INIT_POS.bit.VAL = (init_pos & 0xFFFFFF);
}

u32 hcl_get_spd(u8 n)
{
	u32 spd;
	spd = (*HCL[n]).SPD_OUT.bit.SPD_OUT;
	return spd;
}

void hcl_set_cur_src(u8 n, u16 src)
{
	(*HCL[n]).HCL_CFG.bit.CUR_SRC_SEL = src;
}

void hcl_u_sdfm_src(u8 n, u16 src)
{
	(*HCL[n]).HCL_CFG.bit.IU_SDFM_SRC = src;
}

void hcl_v_sdfm_src(u8 n, u16 src)
{
	(*HCL[n]).HCL_CFG.bit.IV_SDFM_SRC = src;
}

void hcl_dual_trg_mod(u8 n, u16 mod)
{
	(*HCL[n]).HCL_CFG.bit.TRG_MOD = mod;
}

void hcl_pos_rshift(u8 n, u16 shift)
{
	(*HCL[n]).HCL_CFG.bit.POS_DAT_SHIFT = shift;
}

void hcl_cur_dat_sel(u8 n, u16 sel)
{
	(*HCL[n]).HCL_CFG2.bit.CUR_DAT_SRC = sel;
}

void hcl_pos_dat_sel(u8 n, u16 sel)
{
	(*HCL[n]).HCL_CFG2.bit.POS_DAT_SRC = sel;
}

void hcl_reg_usrc_set(u8 n, s16 set)
{
	(*HCL[n]).USRC_DAT.bit.VAL = set;
}

void hcl_reg_vsrc_set(u8 n, s16 set)
{
	(*HCL[n]).VSRC_DAT.bit.VAL = set;
}

void hcl_reg_psrc_set(u8 n, u32 set)
{
	(*HCL[n]).PSRC_DAT.bit.VAL = set;
}

void hcl_sdfm_gain_set(u8 n, u16 set)
{
	(*HCL[n]).SDFM_GAIN.bit.VAL = set;
}

void hcl_sdfm_uoff_set(u8 n, u16 set)
{
	(*HCL[n]).SDFM_UOFF.bit.VAL = set;
}

void hcl_sdfm_voff_set(u8 n, u16 set)
{
	(*HCL[n]).SDFM_VOFF.bit.VAL = set;
}
