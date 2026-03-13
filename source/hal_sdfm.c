/*
 * hal_sdfm.c
 */

#include <all_inc.h>

volatile struct SDFM_REGS SDFMRegs __attribute__((__section__(".sdfmreg")));

static void sdfm_null(void){};
cpu_irq_fun_t sdfm_irqhandle = sdfm_null;

ATTRIBUTE_ISR void SDFM_IRQHandler(void)
{
        sdfm_irq_handler();
}

void sdfm_irq_handler(void)
{
        sdfm_irqhandle();
}

void sdfm_irq_register(cpu_irq_fun_t irqhandle)
{
        sdfm_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_SDFM);
}

void sdfm_irq_unregister(void)
{
        sdfm_irqhandle = sdfm_null;
        cpu_irq_disable(CPU_IRQ_SDFM);
}

void sdfm_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_SDFM);
        cmu_mod_enable(CMU_MOD_SDFM);
}

void sdfm_en(u8 num)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.GLB_EN.bit.SDFM0_EN = 0x1;
                break;
                case 1:
                        SDFMRegs.GLB_EN.bit.SDFM1_EN = 0x1;
                break;
                case 2:
                        SDFMRegs.GLB_EN.bit.SDFM2_EN = 0x1;
                break;
                case 3:
                        SDFMRegs.GLB_EN.bit.SDFM3_EN = 0x1;
                break;

                default:
                break;
        }
}

void sdfm_dis(u8 num)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.GLB_EN.bit.SDFM0_EN = 0x0;
                break;
                case 1:
                        SDFMRegs.GLB_EN.bit.SDFM1_EN = 0x0;
                break;
                case 2:
                        SDFMRegs.GLB_EN.bit.SDFM2_EN = 0x0;
                break;
                case 3:
                        SDFMRegs.GLB_EN.bit.SDFM3_EN = 0x0;
                break;

                default:
                break;
        }
}

void sdfm_mod_set(u8 num,SDFM_IN_MOD mod)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SDFM_CTL0.bit.SDIN_MOD = mod;
                break;
                case 1:
                        SDFMRegs.SDFM_CTL1.bit.SDIN_MOD = mod;
                break;
                case 2:
                        SDFMRegs.SDFM_CTL2.bit.SDIN_MOD = mod;
                break;
                case 3:
                        SDFMRegs.SDFM_CTL3.bit.SDIN_MOD = mod;
                break;
                default:
                break;
        }   
}

void sdfm_pinmux_init(u32 i)
{
        switch(i){
                case 0:
                        gpio_enable(GPIO_GRP_A, 0, 2, GPIO_FUN_6);
                        break;
                case 1:
                        gpio_enable(GPIO_GRP_A, 2, 2, GPIO_FUN_6);
                        break;
                case 2:
                        gpio_enable(GPIO_GRP_A, 4, 2, GPIO_FUN_6);
                        break;
                case 3:
                        gpio_enable(GPIO_GRP_A, 6, 2, GPIO_FUN_6);
                        break;
                default:
                break;
        }
}

void sdfm_psinc_set(u8 num,SINC_TYPE type, u32 osr)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.PSINC_SET0.bit.PFEN = 0x1;
                        SDFMRegs.PSINC_SET0.bit.PSINC_TYP = type;
                        SDFMRegs.PSINC_SET0.bit.POSR = osr & 0xFF;
                break;
                case 1:
                        SDFMRegs.PSINC_SET1.bit.PFEN = 0x1;
                        SDFMRegs.PSINC_SET1.bit.PSINC_TYP = type;
                        SDFMRegs.PSINC_SET1.bit.POSR = osr & 0xFF;
                break;
                case 2:
                        SDFMRegs.PSINC_SET2.bit.PFEN = 0x1;
                        SDFMRegs.PSINC_SET2.bit.PSINC_TYP = type;
                        SDFMRegs.PSINC_SET2.bit.POSR = osr & 0xFF;
                break;
                case 3:
                        SDFMRegs.PSINC_SET3.bit.PFEN = 0x1;
                        SDFMRegs.PSINC_SET3.bit.PSINC_TYP = type;
                        SDFMRegs.PSINC_SET3.bit.POSR = osr & 0xFF;
                break;
                default:
                break;
        }

}

void sdfm_ssinc_set(u8 num,SINC_TYPE type, u32 osr)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SSINC_SET0.bit.SFEN = 0x1;
                        SDFMRegs.SSINC_SET0.bit.SSINC_TYP = type;
                        SDFMRegs.SSINC_SET0.bit.SOSR = osr & 0x1F;
                break;
                case 1:
                        SDFMRegs.SSINC_SET1.bit.SFEN = 0x1;
                        SDFMRegs.SSINC_SET1.bit.SSINC_TYP = type;
                        SDFMRegs.SSINC_SET1.bit.SOSR = osr & 0x1F;
                break;
                case 2:
                        SDFMRegs.SSINC_SET2.bit.SFEN = 0x1;
                        SDFMRegs.SSINC_SET2.bit.SSINC_TYP = type;
                        SDFMRegs.SSINC_SET2.bit.SOSR = osr & 0x1F;
                break;
                case 3:
                        SDFMRegs.SSINC_SET3.bit.SFEN = 0x1;
                        SDFMRegs.SSINC_SET3.bit.SSINC_TYP = type;
                        SDFMRegs.SSINC_SET3.bit.SOSR = osr & 0x1F;
                break;
                default:
                break;
        }  

}

void sdfm_dat_inv_en(u8 num, u32 en)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SDFM_CTL0.bit.SDIN_DAT_INV = en & 0x1;
                break;
                case 1:
                        SDFMRegs.SDFM_CTL1.bit.SDIN_DAT_INV = en & 0x1;
                break;
                case 2:
                        SDFMRegs.SDFM_CTL2.bit.SDIN_DAT_INV = en & 0x1;
                break;
                case 3:
                        SDFMRegs.SDFM_CTL3.bit.SDIN_DAT_INV = en & 0x1;
                break;
                default:
                break;        
        }
}

void sdfm_clk_inv_en(u8 num, u32 en)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SDFM_CTL0.bit.SDIN_CLK_INV = en & 0x1;
                break;
                case 1:
                        SDFMRegs.SDFM_CTL1.bit.SDIN_CLK_INV = en & 0x1;
                break;
                case 2:
                        SDFMRegs.SDFM_CTL2.bit.SDIN_CLK_INV = en & 0x1;
                break;
                case 3:
                        SDFMRegs.SDFM_CTL3.bit.SDIN_CLK_INV = en & 0x1;
                break;
                default:
                break;        
        }
}

void sdfm_irq_en(u8 num, u32 irq_en)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SDFM_INT_EN0.all = irq_en & 0x7f;
                break;
                case 1:
                        SDFMRegs.SDFM_INT_EN1.all = irq_en & 0x7f;
                break;
                case 2:
                        SDFMRegs.SDFM_INT_EN2.all = irq_en & 0x7f;
                break;
                case 3:
                        SDFMRegs.SDFM_INT_EN3.all = irq_en & 0x7f;
                break;
                default:
                break;        
        }        
}

u32 sdfm_get_irq_sts(u8 num)
{
        u32 irq_sts = 0;
        switch(num)
        {
                case 0:
                        irq_sts = SDFMRegs.SDFM_FLG0.all;
                break;
                case 1:
                        irq_sts = SDFMRegs.SDFM_FLG1.all;
                break;
                case 2:
                        irq_sts = SDFMRegs.SDFM_FLG2.all;
                break;
                case 3:
                        irq_sts = SDFMRegs.SDFM_FLG3.all;
                break;
                default:
                break;        
        }
        return irq_sts;
}

void sdfm_clr_irq_sts(u8 num, u32 clr_sts)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SDFM_FLG0.all = clr_sts;
                break;
                case 1:
                        SDFMRegs.SDFM_FLG1.all = clr_sts;
                break;
                case 2:
                        SDFMRegs.SDFM_FLG2.all = clr_sts;
                break;
                case 3:
                        SDFMRegs.SDFM_FLG3.all = clr_sts;
                break;
                default:
                break;
        }
}

void sdfm_psinc_sync_set(u8 num, SDFM_SYNC_TYPE sync_src)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.PSINC_SET0.bit.PSINC_SYNC_EN = 0x1;
                        SDFMRegs.PSINC_SET0.bit.SYNC_SRC_SEL = sync_src;
                break;
                case 1:
                        SDFMRegs.PSINC_SET1.bit.PSINC_SYNC_EN = 0x1;
                        SDFMRegs.PSINC_SET1.bit.SYNC_SRC_SEL = sync_src;
                break;
                case 2:
                        SDFMRegs.PSINC_SET2.bit.PSINC_SYNC_EN = 0x1;
                        SDFMRegs.PSINC_SET2.bit.SYNC_SRC_SEL = sync_src;
                break;
                case 3:
                        SDFMRegs.PSINC_SET3.bit.PSINC_SYNC_EN = 0x1;
                        SDFMRegs.PSINC_SET3.bit.SYNC_SRC_SEL = sync_src;
                break;
                default:
                break;        
        }            
}

void sdfm_ssinc_set_llt(u8 num, u32 llt)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SSINC_TH0.bit.LLT = llt & 0xFFFF;
                break;
                case 1:
                        SDFMRegs.SSINC_TH1.bit.LLT = llt & 0xFFFF;
                break;
                case 2:
                        SDFMRegs.SSINC_TH2.bit.LLT = llt & 0xFFFF;
                break;
                case 3:
                        SDFMRegs.SSINC_TH3.bit.LLT = llt & 0xFFFF;
                break;
                default:
                break;        
        }            
}

void sdfm_ssinc_set_hlt(u8 num, u32 hlt)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SSINC_TH0.bit.HLT = hlt & 0xFFFF;
                break;
                case 1:
                        SDFMRegs.SSINC_TH1.bit.HLT = hlt & 0xFFFF;
                break;
                case 2:
                        SDFMRegs.SSINC_TH2.bit.HLT = hlt & 0xFFFF;
                break;
                case 3:
                        SDFMRegs.SSINC_TH3.bit.HLT = hlt & 0xFFFF;
                break;
                default:
                break;        
        }            
}

void sdfm_set_data_width(u8 num, DAT_WIDTH_TYPE type)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.PSINC_OUT0.bit.DAT_OUT_WDTH = type;
                break;
                case 1:
                        SDFMRegs.PSINC_OUT1.bit.DAT_OUT_WDTH = type;
                break;
                case 2:
                        SDFMRegs.PSINC_OUT2.bit.DAT_OUT_WDTH = type;
                break;
                case 3:
                        SDFMRegs.PSINC_OUT3.bit.DAT_OUT_WDTH = type;
                break;
                default:
                break;
        }
}

void sdfm_set_data_shift(u8 num, u32 shift)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.PSINC_OUT0.bit.DAT_OUT_SHIFT = shift & 0x1f;
                break;
                case 1:
                        SDFMRegs.PSINC_OUT1.bit.DAT_OUT_SHIFT = shift & 0x1f;
                break;
                case 2:
                        SDFMRegs.PSINC_OUT2.bit.DAT_OUT_SHIFT = shift & 0x1f;
                break;
                case 3:
                        SDFMRegs.PSINC_OUT3.bit.DAT_OUT_SHIFT = shift & 0x1f;
                break;
                default:
                break;
        }
}


u32 sdfm_get_data(u8 num)
{
        u32 data = 0;
        switch(num)
        {
                case 0:
                        data = SDFMRegs.SD_DAT0.all;
                break;
                case 1:
                        data = SDFMRegs.SD_DAT1.all;
                break;
                case 2:
                        data = SDFMRegs.SD_DAT2.all;
                break;
                case 3:
                        data = SDFMRegs.SD_DAT3.all;
                break;
                default:
                break;        
        }
        return data;          
}


u32 sdfm_get_fifo_data(u8 num)
{
        u32 data = 0;
        switch(num)
        {
                case 0:
                        data = SDFMRegs.FIFO_DAT0;
                break;
                case 1:
                        data = SDFMRegs.FIFO_DAT1;
                break;
                case 2:
                        data = SDFMRegs.FIFO_DAT2;
                break;
                case 3:
                        data = SDFMRegs.FIFO_DAT3;
                break;
                default:
                break;        
        }
        return data;          
}

void sdfm_fifo_en(u8 num, u32 en)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.FIFO_CTL0.bit.FIFO_EN = en & 0x1;
                break;
                case 1:
                        SDFMRegs.FIFO_CTL1.bit.FIFO_EN = en & 0x1;
                break;
                case 2:
                        SDFMRegs.FIFO_CTL2.bit.FIFO_EN = en & 0x1;
                break;
                case 3:
                        SDFMRegs.FIFO_CTL3.bit.FIFO_EN = en & 0x1;
                break;
                default:
                break;        
        }           
}

void sdfm_fifo_flush(u8 num)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.FIFO_CTL0.bit.FIFO_FLUSH = 0x1;
                break;
                case 1:
                        SDFMRegs.FIFO_CTL1.bit.FIFO_FLUSH = 0x1;
                break;
                case 2:
                        SDFMRegs.FIFO_CTL2.bit.FIFO_FLUSH = 0x1;
                break;
                case 3:
                        SDFMRegs.FIFO_CTL3.bit.FIFO_FLUSH = 0x1;
                break;
                default:
                break;        
        }           
}

void sdfm_set_fifo_rxth(u8 num, u32 rxth)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.FIFO_CTL0.bit.FIFO_RXTH = rxth & 0x3f;
                break;
                case 1:
                        SDFMRegs.FIFO_CTL1.bit.FIFO_RXTH = rxth & 0x3f;
                break;
                case 2:
                        SDFMRegs.FIFO_CTL2.bit.FIFO_RXTH = rxth & 0x3f;
                break;
                case 3:
                        SDFMRegs.FIFO_CTL3.bit.FIFO_RXTH = rxth & 0x3f;
                break;
                default:
                break;        
        }           
}

void sdfm_clk_div(u32 div)
{
	SDFMRegs.SDFM_CLK_SET.bit.SDFM_CLK_DIV_EN = 0x1;
	SDFMRegs.SDFM_CLK_SET.bit.SDFM_CLK_DIV = div - 1;
}

void sdfm_clk_out_en(u8 num)
{
	switch(num)
		{
		case 0:
			SDFMRegs.SDFM_CLK_SET.bit.SDFM0_CLK_SEL = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM0_CLK_OUT_EN = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM0_CLK_IN_EN = 0x0;
			break;
		case 1:
			SDFMRegs.SDFM_CLK_SET.bit.SDFM1_CLK_SEL = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM1_CLK_OUT_EN = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM1_CLK_IN_EN = 0x0;
			break;
		case 2:
			SDFMRegs.SDFM_CLK_SET.bit.SDFM2_CLK_SEL = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM2_CLK_OUT_EN = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM2_CLK_IN_EN = 0x0;
			break;
		case 3:
			SDFMRegs.SDFM_CLK_SET.bit.SDFM3_CLK_SEL = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM3_CLK_OUT_EN = 0x1;
			SDFMRegs.SDFM_CLK_SET.bit.SDFM3_CLK_IN_EN = 0x0;
			break;
		default:
			break;
		}
}

void sdfm_clk_in_en(u8 num)
{
	switch(num)
	{
	case 0:
		SDFMRegs.SDFM_CLK_SET.bit.SDFM0_CLK_SEL = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM0_CLK_OUT_EN = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM0_CLK_IN_EN = 0x1;
		break;
	case 1:
		SDFMRegs.SDFM_CLK_SET.bit.SDFM1_CLK_SEL = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM1_CLK_OUT_EN = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM1_CLK_IN_EN = 0x1;
		break;
	case 2:
		SDFMRegs.SDFM_CLK_SET.bit.SDFM2_CLK_SEL = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM2_CLK_OUT_EN = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM2_CLK_IN_EN = 0x1;
		break;
	case 3:
		SDFMRegs.SDFM_CLK_SET.bit.SDFM3_CLK_SEL = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM3_CLK_OUT_EN = 0x0;
		SDFMRegs.SDFM_CLK_SET.bit.SDFM3_CLK_IN_EN = 0x1;
		break;
	default:
		break;
	}
}

void sdfm_ssinc_set_sllt(u8 num, u32 llt)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SSINC_STH0.bit.LLT = llt & 0xFFFF;
                break;
                case 1:
                        SDFMRegs.SSINC_STH1.bit.LLT = llt & 0xFFFF;
                break;
                case 2:
                        SDFMRegs.SSINC_STH2.bit.LLT = llt & 0xFFFF;
                break;
                case 3:
                        SDFMRegs.SSINC_STH3.bit.LLT = llt & 0xFFFF;
                break;
                default:
                break;
        }
}

void sdfm_ssinc_set_shlt(u8 num, u32 hlt)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SSINC_STH0.bit.HLT = hlt & 0xFFFF;
                break;
                case 1:
                        SDFMRegs.SSINC_STH1.bit.HLT = hlt & 0xFFFF;
                break;
                case 2:
                        SDFMRegs.SSINC_STH2.bit.HLT = hlt & 0xFFFF;
                break;
                case 3:
                        SDFMRegs.SSINC_STH3.bit.HLT = hlt & 0xFFFF;
                break;
                default:
                break;
        }
}

void sdfm_ssinc_set_zlt(u8 num, u32 hlt)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SSINC_ZLT0.bit.ZLT = hlt & 0xFFFF;
                break;
                case 1:
                        SDFMRegs.SSINC_ZLT1.bit.ZLT = hlt & 0xFFFF;
                break;
                case 2:
                        SDFMRegs.SSINC_ZLT2.bit.ZLT = hlt & 0xFFFF;
                break;
                case 3:
                        SDFMRegs.SSINC_ZLT3.bit.ZLT = hlt & 0xFFFF;
                break;
                default:
                break;
        }
}

void sdfm_smp_ph_set(u8 num, u32 smp)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.SDFM_SMP_SET.bit.SDFM0_SMP_PH = smp;
                break;
                case 1:
                		SDFMRegs.SDFM_SMP_SET.bit.SDFM1_SMP_PH = smp;
                break;
                case 2:
                		SDFMRegs.SDFM_SMP_SET.bit.SDFM2_SMP_PH = smp;
                break;
                case 3:
                		SDFMRegs.SDFM_SMP_SET.bit.SDFM3_SMP_PH = smp;
                break;
                default:
                break;
        }
}

void sdfm_fifo_wait_sync(u8 num, u32 en)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.FIFO_CTL0.bit.FIFO_WAIT_SYNC = en & 0x1;
                break;
                case 1:
                        SDFMRegs.FIFO_CTL1.bit.FIFO_WAIT_SYNC = en & 0x1;
                break;
                case 2:
                        SDFMRegs.FIFO_CTL2.bit.FIFO_WAIT_SYNC = en & 0x1;
                break;
                case 3:
                        SDFMRegs.FIFO_CTL3.bit.FIFO_WAIT_SYNC = en & 0x1;
                break;
                default:
                break;
        }
}

void sdfm_fifo_sync_clr(u8 num, u32 en)
{
        switch(num)
        {
                case 0:
                        SDFMRegs.FIFO_CTL0.bit.FIFO_SYNC_CLR = en & 0x1;
                break;
                case 1:
                        SDFMRegs.FIFO_CTL1.bit.FIFO_SYNC_CLR = en & 0x1;
                break;
                case 2:
                        SDFMRegs.FIFO_CTL2.bit.FIFO_SYNC_CLR = en & 0x1;
                break;
                case 3:
                        SDFMRegs.FIFO_CTL3.bit.FIFO_SYNC_CLR = en & 0x1;
                break;
                default:
                break;
        }
}
