/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */

#include <all_inc.h>

DMA_NOCACHE_RAM_SECTION dma_link_task_p dma_ch_reg_task[4] __attribute__((aligned(32))) ; //

static void dma0_null(void){};
cpu_irq_fun_t dma0_irqhandle = dma0_null;

static void dma1_null(void){};
cpu_irq_fun_t dma1_irqhandle = dma1_null;

void dma0_irq_handler(void)
{
        dma0_irqhandle();
}

ATTRIBUTE_ISR void DMA0_IRQHandler(void)
{
        dma0_irq_handler();
}

void dma1_irq_handler(void)
{
        dma1_irqhandle();
}

ATTRIBUTE_ISR void DMA1_IRQHandler(void)
{
        dma1_irq_handler();
}

void dma_irq_register(u32 num, cpu_irq_fun_t irqhandle)
{
		switch(num){
    	case 0:
			dma0_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_DMA0);
		break;
    	case 1:
			dma1_irqhandle = irqhandle;
			cpu_irq_enable(CPU_IRQ_DMA1);
		break;
    	default:
        break;
	}
}

void dma_irq_unregister(u32 num)
{
		switch(num){
    	case 0:
    		dma0_irqhandle = dma0_null;
    		cpu_irq_disable(CPU_IRQ_DMA0);
    	break;
    	case 1:
    		dma1_irqhandle = dma1_null;
    		cpu_irq_disable(CPU_IRQ_DMA1);
    	break;
    	default:
        break;
		}
}


s32 init_dma(u8 dma_num)
{
	 if (dma_num == 0x1) {
		 cmu_mod_disable(CMU_MOD_DMA1);
		 cmu_mod_enable(CMU_MOD_DMA1);
	 }

	 else {
		 cmu_mod_disable(CMU_MOD_DMA0);
		 cmu_mod_enable(CMU_MOD_DMA0);
	}
	u32 i;
	for (i=0; i<4; i++) {
		dma_ch_reg_task[i].link_id = 0x0;
		dma_ch_reg_task[i].src_addr = 0x0;
		dma_ch_reg_task[i].dst_addr = 0x0;
	}
	 return RET_OK;
}

s32 dma_request_reg(u8 dma_num, u8 ch, dma_device_id_p src_drq, dma_task_cfg1_p src_cfg, dma_device_id_p dst_drq, dma_task_cfg1_p dst_cfg,
			  u32 block_length, u32 saddr, u32 daddr, u32 len, u32 loop_en)
{

	 u8 src_fix_word_en = 0;
	 u8 dst_fix_word_en = 0;

	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) requested is outside!\n", ch);
		 return RET_FALSE;
	 }

	 //  io_fast && width=8       ||  io_fast && width=16
	 if ((src_cfg & 0x1fc) == 0x10 || (src_cfg & 0x1fc) == 0x50) {
		 src_fix_word_en = 1;
	 }

	 //  io_fast && width=8       ||  io_fast && width=16
	 if ((dst_cfg & 0x1fc) == 0x10 || (dst_cfg & 0x1fc) == 0x50) {
		 dst_fix_word_en = 1;
	 }

	 // source addr unalign 4
	 if ((saddr & 3) != 0) {
//		 printk("SADDR UNALIGN!\n");
		 return RET_FALSE;
	 }

	 // source addr unalign 4
	 if ((daddr & 3) != 0) {
//		 printk("DADDR UNALIGN!\n");
		 return RET_FALSE;
	 }


	 dma_module_p->dma_ch[ch].dma_link_sel = dma_module_p->dma_ch[ch].dma_link_sel | 0x2;


	 dma_module_p->dma_ch[ch].dma_link_id = 0xa1c86688;


	 dma_module_p->dma_ch[ch].dma_task_cfg_1	= dst_cfg << 23 | dst_drq << 16 | src_cfg << 7 | src_drq;


	 dma_module_p->dma_ch[ch].dma_hdshk_len = block_length;
	 dma_module_p->dma_ch[ch].dma_src_addr  = saddr;
	 dma_module_p->dma_ch[ch].dma_dst_addr  = daddr;
	 dma_module_p->dma_ch[ch].dma_task_len  = 0xb8000000 | (src_fix_word_en << 25) | (dst_fix_word_en << 26) | len;

	 if (loop_en) {
		 dma_module_p->dma_ch[ch].dma_task_cfg_2	 = 0x55000000;
		 dma_module_p->dma_ch[ch].dma_next_task_add = (u32)(uaddr)(&dma_module_p->dma_ch[ch].dma_link_id);
	 } else {
		 dma_module_p->dma_ch[ch].dma_task_cfg_2	 = 0x55ff0000;
		 dma_module_p->dma_ch[ch].dma_next_task_add = 0xfffffffc;
	 }

	 dma_module_p->dma_ch[ch].dma_ch_task_add_1 = 0x0;
	 dma_module_p->dma_ch[ch].dma_ch_task_add_2 = 0x0;

//	 printk("Task Addr:0x%08x\n", (u32)(uaddr)(&dma_ch_reg_task[ch][0]));
//	 printk("DMA  Addr:0x%08x\n", (u32)(uaddr)(dma_module_p));

	 return RET_OK;
}

s32 dma_enable(u8 dma_num, u8 ch)
{

	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) enabled is outside!\n", ch);
		 return RET_FALSE;
	 }

	 dma_module_p->dma_ch[ch].dma_ch_ctl_1.bits.ch_enable = 1;

	 return RET_OK;
}

s32 dma_disable(u8 dma_num, u8 ch)
{
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
		 printk("DMA ERR: CH(%d) enabled is outside!\n", ch);
		 return RET_FALSE;
	 }

	 dma_module_p->dma_ch[ch].dma_ch_ctl_1.bits.ch_enable = 0;

	 return RET_OK;
}

s32 dma_wait_finish(u8 dma_num, u8 ch)
{
	 u32 rval;
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) wait is outside!\n", ch);
		 return RET_FALSE;
	 }
	 do {
		 rval = dma_module_p->dma_ch[ch].dma_ch_ctl_1.bits.ch_enable;
	 } while (rval & 0x1);
	 return RET_OK;
}

u32 dma_irq_enable(u8 dma_num, u32 ch, u32 en)// 1: enable   0: disable
{
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) irq enable is outside!\n", ch);
		 return RET_FALSE;
	 }

	 if (ch >= 12) {
		 ch = ch - 12;
		 if (en)
			 dma_module_p->dma_irq_en_4.dwval = 0x4 << (ch * 8);
		 else
			 dma_module_p->dma_irq_clr_4.dwval = 0x4 << (ch * 8);

	 } else if (ch >= 8) {
		 ch = ch - 8;
		 if (en)
			 dma_module_p->dma_irq_en_3.dwval = 0x4 << (ch * 8);

		 else
			 dma_module_p->dma_irq_clr_3.dwval = 0x4 << (ch * 8);

	 } else if (ch >= 4) {
		 ch = ch - 4;
		 if (en)
			 dma_module_p->dma_irq_en_2.dwval = 0x4 << (ch * 8);

		 else
			 dma_module_p->dma_irq_clr_2.dwval = 0x4 << (ch * 8);

	 } else {
		 if (en)
			 dma_module_p->dma_irq_en_1.dwval = 0x4 << (ch * 8);

		 else
			 dma_module_p->dma_irq_clr_1.dwval = 0x4 << (ch * 8);
	 }

	 return RET_OK;
}

u32 dma_irq_query(u8 dma_num, u8 ch)
{
	 u32 status = 0;

	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch > 3) {
		 status	= dma_module_p->dma_irq_sta_2.dwval;
	 }
	 else {
		 status	= dma_module_p->dma_irq_sta_1.dwval;
	 }
	 return status;
}

void dma_irq_sts_clr(u8 dma_num, u8 ch, u32 clr)
{

	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch > 3) {
		 dma_module_p->dma_irq_sta_2.dwval = clr;
	 }
	 else {
		 dma_module_p->dma_irq_sta_1.dwval = clr;
	 }

}


s32 dma_pause(u8 dma_num, u8 ch, u8 ctrol)
{
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) enabled is outside!\n", ch);
		 return RET_FALSE;
	 }

	 dma_module_p->dma_ch[ch].dma_ch_ctl_2.dwval = ctrol & 0xff;
	 return RET_OK;
}

s32 dma_discard_finish(u8 dma_num, u8 ch)
{
	 u32 rval;
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) wait is outside!\n", ch);
		 return RET_FALSE;
	 }
	 do {
		 rval = dma_module_p->dma_ch[ch].dma_ch_ctl_2.dwval;
	 } while (rval & 0x4);
	 return RET_OK;
}

s32 dma_fix_pri_en(u8 dma_num, u8 ch, u8 en)
{
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) wait is outside!\n", ch);
		 return RET_FALSE;
	 }
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.axi_rd_fix_pri_en = en;// enable fix priority
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.axi_wt_fix_pri_en = en;// enable fix priority
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.ahb_rd_fix_pri_en = en;// enable fix priority
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.ahb_wt_fix_pri_en = en;// enable fix priority

	 return RET_OK;
}

s32 dma_auto_pri_incthd_cfg(u8 dma_num, u8 ch, u8 cfg)
{
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) wait is outside!\n", ch);
		 return RET_FALSE;
	 }
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.axi_rd_thd_cfg = cfg;// enable fix priority
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.axi_wt_thd_cfg = cfg;// enable fix priority
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.ahb_rd_thd_cfg = cfg;// enable fix priority
	 dma_module_p->dma_ch[ch].dma_ch_ctl_3.bits.ahb_wt_thd_cfg = cfg;// enable fix priority

	 return RET_OK;
}

s32 dma_pri_set(u8 dma_num, u8 ch, u8 ch_pri)
{
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 if (ch >= DMA_CH_NUM) {
//		 printk("DMA ERR: CH(%d) wait is outside!\n", ch);
		 return RET_FALSE;
	 }
	 dma_module_p->dma_ch[ch].dma_ch_ctl_4.bits.dst_pri_cfg = ch_pri;// dst priority set
	 dma_module_p->dma_ch[ch].dma_ch_ctl_4.bits.src_pri_cfg = ch_pri;// src priority set
	 return RET_OK;
}


void dma_len_cfg(u8 dma_num, u32 ch, u32 len)
{
	u32 reg_val;
	 dma_module_reg_p * dma_module_p;

	 if (dma_num == 0x1)
		 dma_module_p = (dma_module_reg_p *)BASE_DMA1;
	 else
		 dma_module_p = (dma_module_reg_p *)BASE_DMA0;

	 reg_val = dma_module_p->dma_ch[ch].dma_task_len;
	 reg_val &= (~0x1FFFFFF);
	 reg_val |= (len & 0x1FFFFFF);
	 dma_module_p->dma_ch[ch].dma_task_len = reg_val;

}
