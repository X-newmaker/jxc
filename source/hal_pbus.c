/**
 * pbus.c
 */
#include <all_inc.h>

pbus_dev_t pbus_dev_p __attribute__((__section__(".pbusreg")));

void pbus_clk_set(pubs_clk_div_t div)
{
	pbus_dev_p.pbus_cfg.bits.clk_div	=	div;
}

void pbus_clk_out_en(void)
{
	pbus_dev_p.pbus_cfg.bits.clk_oe	=	1;
}

void pbus_clk_pol(pubs_signal_pol_t pol)
{
	pbus_dev_p.pbus_cfg.bits.clk_pol	=	pol;
}

void pbus_ncs_pol(pubs_signal_pol_t pol)
{
	pbus_dev_p.pbus_cfg.bits.ncs_pol	=	pol;
}

void pbus_nadv_pol(pubs_signal_pol_t pol)
{
	pbus_dev_p.pbus_cfg.bits.nadv_pol	=	pol;
}

void pbus_nwe_pol(pubs_signal_pol_t pol)
{
	pbus_dev_p.pbus_cfg.bits.nwe_pol	=	pol;
}

void pbus_noe_pol(pubs_signal_pol_t pol)
{
	pbus_dev_p.pbus_cfg.bits.noe_pol	=	pol;
}

void pbus_work_mode(pubs_work_mode_t mode)
{
	pbus_dev_p.pbus_cfg.bits.work_mode	=	mode;
}

void pbus_addr_bus_en(void)
{
	pbus_dev_p.pbus_cfg.bits.addr_bus_en	=	1;
}

void pbus_check_dat_en(void)
{
	pbus_dev_p.pbus_cfg.bits.ncs_check_dat_en	=	1;
}

void pbus_manu_addr_from_fifo(void)
{
	pbus_dev_p.pbus_cfg.bits.manu_addr_from_fifo	=	1;
}

void pbus_manu_addr_incr(void)
{
	pbus_dev_p.pbus_cfg.bits.manu_addr_incr	=	1;
}

void pbus_mode(pubs_mode_t mode)
{
	pbus_dev_p.pbus_cfg.bits.pbus_mode	=	mode;
}

void pbus_data_width(pubs_data_width_t width)
{
	pbus_dev_p.pbus_cfg.bits.pbus_data_width	=	width;
}

void pbus_clr(void)
{
	pbus_dev_p.pbus_ctl.bits.pbus_clr	=	1;
	while(pbus_dev_p.pbus_ctl.bits.pbus_clr != 0) {};
}

void pbus_fifo_cfg(u32 level)
{
	pbus_dev_p.pbus_fifo_cfg.bits.pbus_thr	=	level;
}

void pbus_cs_sel(u32 sel)
{
	pbus_dev_p.pbus_cfg.bits.pbus_cs_sel = sel;
}

s32 pbus_fifo_empty_sta(void)
{
	u32 sta;
	sta = pbus_dev_p.pbus_fifo_sta.bits.fifo_empty;
	return sta;
}

s32 pbus_fifo_full_sta(void)
{
	u32 sta;
	sta = pbus_dev_p.pbus_fifo_sta.bits.fifo_full;
	return sta;
}

s32 pbus_fifo_dlen_sta(void)
{
	u32 sta;
	sta = pbus_dev_p.pbus_fifo_sta.bits.fifo_dlen;
	return sta;
}

s32 pbus_sta(void)
{
	u32 sta;
	sta = pbus_dev_p.pbus_fifo_sta.bits.pbus_busy;
	return sta;
}

void pbus_tim_ncs(u32 pre, u32 pha, u32 post)
{
	pbus_dev_p.pbus_tim_ncs.bits.ncs_pre	=	pre;
	pbus_dev_p.pbus_tim_ncs.bits.ncs_pha	=	pha;
	pbus_dev_p.pbus_tim_ncs.bits.ncs_post	=	post;
}

void pbus_tim_nadv(u32 pre, u32 pha)
{
	pbus_dev_p.pbus_tim_nadv.bits.nadv_pre	=	pre;
	pbus_dev_p.pbus_tim_nadv.bits.nadv_pha	=	pha;
}

void pbus_tim_nwe(u32 pre, u32 pha0, u32 wait, u32 pha1)
{
	pbus_dev_p.pbus_tim_nwe.bits.nwe_pre	=	pre;
	pbus_dev_p.pbus_tim_nwe.bits.nwe_pha0	=	pha0;
	pbus_dev_p.pbus_tim_nwe.bits.nwe_wait	=	wait;
	pbus_dev_p.pbus_tim_nwe.bits.nwe_pha1	=	pha1;
}

void pbus_tim_noe(u32 pre, u32 pha0, u32 wait, u32 pha1)
{
	pbus_dev_p.pbus_tim_noe.bits.noe_pre	=	pre;
	pbus_dev_p.pbus_tim_noe.bits.noe_pha0	=	pha0;
	pbus_dev_p.pbus_tim_noe.bits.noe_wait	=	wait;
	pbus_dev_p.pbus_tim_noe.bits.noe_pha1	=	pha1;
}

void pbus_tim_dat(u32 pre, u32 pha0, u32 wait, u32 pha1)
{
	pbus_dev_p.pbus_tim_dat.bits.dat_pre	=	pre;
	pbus_dev_p.pbus_tim_dat.bits.dat_pha0	=	pha0;
	pbus_dev_p.pbus_tim_dat.bits.dat_wait	=	wait;
	pbus_dev_p.pbus_tim_dat.bits.dat_pha1	=	pha1;
}

void pbus_tim_adr(u32 pre, u32 pha)
{
	pbus_dev_p.pbus_tim_adr.bits.adr_pre	=	pre;
	pbus_dev_p.pbus_tim_adr.bits.adr_pha	=	pha;
}

void pbus_irq_en(void)
{
	pbus_dev_p.pbus_irq_en.bits.fifo_irq_en	=	1;
}

s32 pbus_irq_sta(void)
{
	u32 sta;
	sta = pbus_dev_p.pbus_irq_sta.bits.fifo_irq_sta;
	return sta;
}

void pbus_ncs_val_set(u32 idle, u32 pre, u32 pha, u32 post)
{
	pbus_dev_p.pbus_val_set.bits.ncs_idle_value	=	idle;
	pbus_dev_p.pbus_val_set.bits.ncs_pre_value	=	pre;
	pbus_dev_p.pbus_val_set.bits.ncs_pha_value	=	pha;
	pbus_dev_p.pbus_val_set.bits.ncs_post_value	=	post;
}

void pbus_nadv_val_set(u32 idle, u32 pre, u32 pha)
{
	pbus_dev_p.pbus_val_set.bits.nadv_idle_value	=	idle;
	pbus_dev_p.pbus_val_set.bits.nadv_pre_value	=	pre;
	pbus_dev_p.pbus_val_set.bits.nadv_pha_value	=	pha;
}

void pbus_nwe_val_set(u32 idle, u32 pre, u32 pha0, u32 wait, u32 pha1)
{
	pbus_dev_p.pbus_val_set.bits.nwe_idle_value	=	idle;
	pbus_dev_p.pbus_val_set.bits.nwe_pre_value	=	pre;
	pbus_dev_p.pbus_val_set.bits.nwe_pha0_value	=	pha0;
	pbus_dev_p.pbus_val_set.bits.nwe_wait_value	=	wait;
	pbus_dev_p.pbus_val_set.bits.nwe_pha1_value	=	pha1;
}

void pbus_noe_val_set(u32 idle, u32 pre, u32 pha0, u32 wait, u32 pha1)
{
	pbus_dev_p.pbus_val_set.bits.noe_idle_value	=	idle;
	pbus_dev_p.pbus_val_set.bits.noe_pre_value	=	pre;
	pbus_dev_p.pbus_val_set.bits.noe_pha0_value	=	pha0;
	pbus_dev_p.pbus_val_set.bits.noe_wait_value	=	wait;
	pbus_dev_p.pbus_val_set.bits.noe_pha1_value	=	pha1;
}

void pbus_data_num(u32 num)
{
	pbus_dev_p.pbus_data_num.bits.data_num	=	num - 1;
}

void pbus_start(void)
{
	pbus_dev_p.pbus_start.bits.dma_start	=	1;
	while(pbus_dev_p.pbus_start.bits.dma_start != 0) {};
}

void pbus_address(u32 address)
{
	pbus_dev_p.pbus_address.bits.address	=	address;
}

s32 pbus_read_data(void)
{
	return pbus_dev_p.pbus_data.bits.data;
}

void pbus_cmu_init(void)
{
        cmu_mod_disable(CMU_MOD_PBUS);
        gtc_dly_time(GTC_US, 10);
        cmu_mod_enable(CMU_MOD_PBUS);
}


