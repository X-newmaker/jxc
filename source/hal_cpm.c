/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
/*
 * hal_cpm.c
 */
#include <all_inc.h>

volatile struct CPM_REGS CPMRegs __attribute__((__section__(".cpmreg")));

static void cpm_null(void){};
cpu_irq_fun_t cpm_irqhandle = cpm_null;

ATTRIBUTE_ISR void CPM_IRQHandler(void)
{
        cpm_irq_handler();
}

void cpm_irq_handler(void)
{
        cpm_irqhandle();
}

void cpm_irq_register(cpu_irq_fun_t irqhandle)
{
        cpm_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_CPM);
}

void cpm_irq_unregister(void)
{
        cpm_irqhandle = cpm_null;
        cpu_irq_disable(CPU_IRQ_CPM);
}
void cpm_cmu_init(void)
{
	cmu_mod_disable(CMU_MOD_CPM);
	gtc_dly_time(1,1);
	cmu_mod_enable(CMU_MOD_CPM);
}
void cpm_enable(u8 n)
{
	switch(n) {
	case 0:
		CPMRegs.CPM_GLB_EN.bit.CPM0_EN = 0x1;
		break;
	case 1:
		CPMRegs.CPM_GLB_EN.bit.CPM1_EN = 0x1;
		break;
	default:
	    break;
	}
}

void cpm_disable(u8 n)
{
	switch(n) {
	case 0:
		CPMRegs.CPM_GLB_EN.bit.CPM0_EN = 0x0;
		break;
	case 1:
		CPMRegs.CPM_GLB_EN.bit.CPM1_EN = 0x0;
		break;
	default:
	    break;
	}
}

u32 cpm_irq_sts()
{
	return CPMRegs.CPM_GLB_IRQ_STS.all;
}

void cpm_irq_sts_clr(u32 sts)
{
	CPMRegs.CPM_GLB_IRQ_STS.all = sts;
}

void cpm_comph_en(u8 n,u8 en)
{
	switch(n) {
	case 0:
		CPMRegs.COMP_CTL0.bit.COMPH_EN = en;
		break;
	case 1:
		CPMRegs.COMP_CTL1.bit.COMPH_EN = en;
		break;
	default:
		break;
	}
}
void cpm_compl_en(u8 n,u8 en)
{
	switch(n) {
	case 0:
		CPMRegs.COMP_CTL0.bit.COMPL_EN = en;
		break;
	case 1:
		CPMRegs.COMP_CTL1.bit.COMPL_EN = en;
		break;
	default:
		break;
	}
}
void cpm_comph_nsrc(u8 n,u8 src)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COMPH_NSRC = src;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COMPH_NSRC = src;
			break;
		default:
			break;
		}
}
void cpm_compl_nsrc(u8 n,u8 src)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COMPL_NSRC = src;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COMPL_NSRC = src;
			break;
		default:
			break;
		}
}
void cpm_hdac_en(u8 n,u8 en)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.HDAC_EN = en;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.HDAC_EN = en;
			break;
		default:
			break;
		}
}
void cpm_ldac_en(u8 n,u8 en)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.LDAC_EN = en;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.LDAC_EN = en;
			break;
		default:
			break;
		}
}
void cpm_cohl_out(u8 n,CPM_OUT_EN out)
{
	switch(n) {
			case 0:
				if(out == CPM_EPWM_OUT) {
					CPMRegs.COMP_OUT0.bit.COHL_PWM_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COHL_GPIO_EN = 0x0;
				} else if(out == CPM_GPIO_OUT) {
					CPMRegs.COMP_OUT0.bit.COHL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COHL_PWM_EN = 0x0;
				} else if(out == CPM_EPWM_GPIO_OUT) {
					CPMRegs.COMP_OUT0.bit.COHL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COHL_PWM_EN = 0x1;
				} else if(out == CPM_NO_OUT) {
					CPMRegs.COMP_OUT0.bit.COHL_GPIO_EN = 0x0;
					CPMRegs.COMP_OUT0.bit.COHL_PWM_EN = 0x0;
				}
				break;
			case 1:
				if(out == CPM_EPWM_OUT) {
					CPMRegs.COMP_OUT1.bit.COHL_PWM_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COHL_GPIO_EN = 0x0;
				} else if(out == CPM_GPIO_OUT) {
					CPMRegs.COMP_OUT1.bit.COHL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COHL_PWM_EN = 0x0;
				} else if(out == CPM_EPWM_GPIO_OUT) {
					CPMRegs.COMP_OUT1.bit.COHL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COHL_PWM_EN = 0x1;
				} else if(out == CPM_NO_OUT) {
					CPMRegs.COMP_OUT1.bit.COHL_GPIO_EN = 0x0;
					CPMRegs.COMP_OUT1.bit.COHL_PWM_EN = 0x0;
				}
				break;
			default:
				break;
			}
}
void cpm_coh_out(u8 n,CPM_OUT_EN out)
{
	switch(n) {
			case 0:
				if(out == CPM_EPWM_OUT) {
					CPMRegs.COMP_OUT0.bit.COH_PWM_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COH_GPIO_EN = 0x0;
				} else if(out == CPM_GPIO_OUT) {
					CPMRegs.COMP_OUT0.bit.COH_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COH_PWM_EN = 0x0;
				} else if(out == CPM_EPWM_GPIO_OUT) {
					CPMRegs.COMP_OUT0.bit.COH_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COH_PWM_EN = 0x1;
				} else if(out == CPM_NO_OUT) {
					CPMRegs.COMP_OUT0.bit.COH_GPIO_EN = 0x0;
					CPMRegs.COMP_OUT0.bit.COH_PWM_EN = 0x0;
				}
				break;
			case 1:
				if(out == CPM_EPWM_OUT) {
					CPMRegs.COMP_OUT1.bit.COH_PWM_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COH_GPIO_EN = 0x0;
				} else if(out == CPM_GPIO_OUT) {
					CPMRegs.COMP_OUT1.bit.COH_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COH_PWM_EN = 0x0;
				} else if(out == CPM_EPWM_GPIO_OUT) {
					CPMRegs.COMP_OUT1.bit.COH_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COH_PWM_EN = 0x1;
				} else if(out == CPM_NO_OUT) {
					CPMRegs.COMP_OUT1.bit.COH_GPIO_EN = 0x0;
					CPMRegs.COMP_OUT1.bit.COH_PWM_EN = 0x0;
				}
				break;
			default:
				break;
			}
}
void cpm_col_out(u8 n,CPM_OUT_EN out)
{
	switch(n) {
			case 0:
				if(out == CPM_EPWM_OUT) {
					CPMRegs.COMP_OUT0.bit.COL_PWM_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COL_GPIO_EN = 0x0;
				} else if(out == CPM_GPIO_OUT) {
					CPMRegs.COMP_OUT0.bit.COL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COL_PWM_EN = 0x0;
				} else if(out == CPM_EPWM_GPIO_OUT) {
					CPMRegs.COMP_OUT0.bit.COL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT0.bit.COL_PWM_EN = 0x1;
				} else if(out == CPM_NO_OUT) {
					CPMRegs.COMP_OUT0.bit.COL_GPIO_EN = 0x0;
					CPMRegs.COMP_OUT0.bit.COL_PWM_EN = 0x0;
				}
				break;
			case 1:
				if(out == CPM_EPWM_OUT) {
					CPMRegs.COMP_OUT1.bit.COL_PWM_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COL_GPIO_EN = 0x0;
				} else if(out == CPM_GPIO_OUT) {
					CPMRegs.COMP_OUT1.bit.COL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COL_PWM_EN = 0x0;
				} else if(out == CPM_EPWM_GPIO_OUT) {
					CPMRegs.COMP_OUT1.bit.COL_GPIO_EN = 0x1;
					CPMRegs.COMP_OUT1.bit.COL_PWM_EN = 0x1;
				} else if(out == CPM_NO_OUT) {
					CPMRegs.COMP_OUT1.bit.COL_GPIO_EN = 0x0;
					CPMRegs.COMP_OUT1.bit.COL_PWM_EN = 0x0;
				}
				break;
			default:
				break;
			}
}

void cpm_set_dach_val(u8 n, u32 val)
{
	switch(n) {
		case 0:
			CPMRegs.DACH_VALS0.bit.DACH_VALS = val;
			break;
		case 1:
			CPMRegs.DACH_VALS1.bit.DACH_VALS = val;
			break;
		default:
			break;
		}
}
void cpm_set_dacl_val(u8 n, u32 val)
{
	switch(n) {
		case 0:
			CPMRegs.DACL_VALS0.bit.DACL_VALS = val;
			break;
		case 1:
			CPMRegs.DACL_VALS1.bit.DACL_VALS = val;
			break;
		default:
			break;
		}
}
void cpm_set_rampmax_val(u8 n, u32 val)
{
	switch(n) {
		case 0:
			CPMRegs.RAMP_MAX_REFS0.bit.RAMP_MAX_REFS = val;
			break;
		case 1:
			CPMRegs.RAMP_MAX_REFS1.bit.RAMP_MAX_REFS = val;
			break;
		default:
			break;
		}
}
void cpm_set_rampdce_val(u8 n, u32 val)
{
	switch(n) {
		case 0:
			CPMRegs.RAMP_DEC_VALS0.bit.RAMP_DEC_VALS = val;
			break;
		case 1:
			CPMRegs.RAMP_DEC_VALS1.bit.RAMP_DEC_VALS = val;
			break;
		default:
			break;
		}
}
void cpm_set_rampdly_val(u8 n, u32 val)
{
	switch(n) {
		case 0:
			CPMRegs.RAMP_DLYS0.bit.RAMP_DLYS = val;
			break;
		case 1:
			CPMRegs.RAMP_DLYS1.bit.RAMP_DLYS = val;
			break;
		default:
			break;
		}
}
void cpm_lfil_ctl(u8 n,u8 en,u32 thr,u32 win)
{
	switch(n) {
		case 0:
			CPMRegs.LFIL_CTL0.bit.FIL_EN = en;
			CPMRegs.LFIL_CTL0.bit.THRESH = thr;
			CPMRegs.LFIL_CTL0.bit.SAMP_WIN = win;
			break;
		case 1:
			CPMRegs.LFIL_CTL1.bit.FIL_EN = en;
			CPMRegs.LFIL_CTL1.bit.THRESH = thr;
			CPMRegs.LFIL_CTL1.bit.SAMP_WIN = win;
			break;
		default:
			break;
		}
}
void cpm_hfil_ctl(u8 n,u8 en,u32 thr,u32 win)
{
	switch(n) {
		case 0:
			CPMRegs.HFIL_CTL0.bit.FIL_EN = en;
			CPMRegs.HFIL_CTL0.bit.THRESH = thr;
			CPMRegs.HFIL_CTL0.bit.SAMP_WIN = win;
			break;
		case 1:
			CPMRegs.HFIL_CTL1.bit.FIL_EN = en;
			CPMRegs.HFIL_CTL1.bit.THRESH = thr;
			CPMRegs.HFIL_CTL1.bit.SAMP_WIN = win;
			break;
		default:
			break;
		}
}
void cpm_hysctl(u8 n,u32 ibias,u32 lhys,u32 hhys)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_HYSCTL0.bit.COMP_IBIAS_EN = ibias;
			CPMRegs.COMP_HYSCTL0.bit.COMPL_HYS_EN = lhys;
			CPMRegs.COMP_HYSCTL0.bit.COMPH_HYS_EN = hhys;
			break;
		case 1:
			CPMRegs.COMP_HYSCTL1.bit.COMP_IBIAS_EN = ibias;
			CPMRegs.COMP_HYSCTL1.bit.COMPL_HYS_EN = lhys;
			CPMRegs.COMP_HYSCTL1.bit.COMPH_HYS_EN = hhys;
			break;
		default:
			break;
			}
}
void coh_pwmout_sel(u8 n,CPM_OUT_SEL sel)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COH_PWM_SEL = sel;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COH_PWM_SEL = sel;
			break;
		default:
			break;
			}
}
void coh_gpioout_sel(u8 n,CPM_OUT_SEL sel)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COH_GPIO_SEL = sel;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COH_GPIO_SEL = sel;
			break;
		default:
			break;
			}
}
void coh_irq_source(u8 n,CPM_OUT_SEL sel)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COH_IRQ_SEL = sel;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COH_IRQ_SEL = sel;
			break;
		default:
			break;
			}
}
void col_pwmout_sel(u8 n,CPM_OUT_SEL sel)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COL_PWM_SEL = sel;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COL_PWM_SEL = sel;
			break;
		default:
			break;
			}
}
void col_gpioout_sel(u8 n,CPM_OUT_SEL sel)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COL_GPIO_SEL = sel;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COL_GPIO_SEL = sel;
			break;
		default:
			break;
		}
}
void col_irq_source(u8 n,CPM_OUT_SEL sel)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COL_IRQ_SEL = sel;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COL_IRQ_SEL = sel;
			break;
		default:
			break;
		}
}
void col_irq_en(u8 n,u8 en)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_OUT0.bit.COL_IRQ_EN = en;
			break;
		case 1:
			CPMRegs.COMP_OUT1.bit.COL_IRQ_EN = en;
			break;
		default:
			break;
		}
}
void coh_irq_en(u8 n,u8 en)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_OUT0.bit.COH_IRQ_EN = en;
			break;
		case 1:
			CPMRegs.COMP_OUT1.bit.COH_IRQ_EN = en;
			break;
		default:
			break;
	}
}

void coh_p_sel(u8 n,CPM_PIN_SEL sel)
{
	switch(n) {
			case 0:
				CPMRegs.IN_SRC_SEL0.bit.COMPH_P_EN = 0x1;
				CPMRegs.IN_SRC_SEL0.bit.COMPH_P_SEL = sel;
				break;
			case 1:
				CPMRegs.IN_SRC_SEL1.bit.COMPH_P_EN = 0x1;
				CPMRegs.IN_SRC_SEL1.bit.COMPH_P_SEL = sel;
				break;
			default:
				break;
		}
}
void col_p_sel(u8 n,CPM_PIN_SEL sel)
{
	switch(n) {
				case 0:
					CPMRegs.IN_SRC_SEL0.bit.COMPL_P_EN = 0x1;
					CPMRegs.IN_SRC_SEL0.bit.COMPL_P_SEL = sel;
					break;
				case 1:
					CPMRegs.IN_SRC_SEL1.bit.COMPL_P_EN = 0x1;
					CPMRegs.IN_SRC_SEL1.bit.COMPL_P_SEL = sel;
					break;
				default:
					break;
			}
}
void cpm_atb_sel(u8 n,u32 sel)
{
	switch(n) {
				case 0:
					CPMRegs.IN_SRC_SEL0.bit.COMP_ATB_EN = 0x1;
					CPMRegs.IN_SRC_SEL0.bit.COMP_ATB_SEL = sel;
					break;
				case 1:
					CPMRegs.IN_SRC_SEL1.bit.COMP_ATB_EN = 0x1;
					CPMRegs.IN_SRC_SEL1.bit.COMP_ATB_SEL = sel;
					break;
				default:
					break;
			}
}

void coh_dac_src(u8 n,CPM_HDAC_SRC src)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_DAC_CTL0.bit.HDAC_SRC = src;
				break;
			case 1:
				CPMRegs.COMP_DAC_CTL1.bit.HDAC_SRC = src;
				break;
			default:
				break;
		}
}

void coh_ramp_ldsrc(u8 n,u32 ldsrc)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_DAC_CTL0.bit.RAMP_LOAD_SEL = ldsrc;
				break;
			case 1:
				CPMRegs.COMP_DAC_CTL1.bit.RAMP_LOAD_SEL = ldsrc;
				break;
			default:
				break;
		}
}

void coh_dac_ldsrc(u8 n,u32 ldsrc)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_DAC_CTL0.bit.DAC_LOAD_SEL = ldsrc;
				break;
			case 1:
				CPMRegs.COMP_DAC_CTL1.bit.DAC_LOAD_SEL = ldsrc;
				break;
			default:
				break;
		}
}

void coh_ramp_synsrc(u8 n,u32 synsrc)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_DAC_CTL0.bit.SYNC_SRC = synsrc;
				break;
			case 1:
				CPMRegs.COMP_DAC_CTL1.bit.SYNC_SRC = synsrc;
				break;
			default:
				break;
		}
}

void coh_lt_clr(u8 n)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_STS_CLR0.bit.COH_LT_CLR = 0x1;
				break;
			case 1:
				CPMRegs.COMP_STS_CLR1.bit.COH_LT_CLR = 0x1;
				break;
			default:
				break;
		}
}

void col_lt_clr(u8 n)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_STS_CLR0.bit.COL_LT_CLR = 0x1;
				break;
			case 1:
				CPMRegs.COMP_STS_CLR1.bit.COL_LT_CLR = 0x1;
				break;
			default:
				break;
		}
}

void coh_lt_syncclr_en(u8 n, u32 en)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_STS_CLR0.bit.COH_LT_SYNCLR_EN = en;
				break;
			case 1:
				CPMRegs.COMP_STS_CLR1.bit.COH_LT_SYNCLR_EN = en;
				break;
			default:
				break;
		}
}

void col_lt_syncclr_en(u8 n, u32 en)
{
	switch(n) {
			case 0:
				CPMRegs.COMP_STS_CLR0.bit.COL_LT_SYNCLR_EN = en;
				break;
			case 1:
				CPMRegs.COMP_STS_CLR1.bit.COL_LT_SYNCLR_EN = en;
				break;
			default:
				break;
		}
}

u32 cpm_get_sts(u8 n)
{
	u32 val;
	switch(n) {
			case 0:
				val = CPMRegs.COMP_STS0.all;
				break;
			case 1:
				val = CPMRegs.COMP_STS1.all;
				break;
			default:
				break;
		}
	return val;

}

void coh_inv_en(u8 n,u32 en)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COMPH_INV = en;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COMPH_INV = en;
			break;
		default:
			break;
		}
}

void col_inv_en(u8 n,u32 en)
{
	switch(n) {
		case 0:
			CPMRegs.COMP_CTL0.bit.COMPL_INV = en;
			break;
		case 1:
			CPMRegs.COMP_CTL1.bit.COMPL_INV = en;
			break;
		default:
			break;
		}
}
