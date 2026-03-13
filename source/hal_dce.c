
#include <all_inc.h>

volatile struct DCE_REGS DCE_Regs __attribute__((__section__(".dcereg")));

void dce_cmu_init(void)
{
	int i = 0;
    cmu_mod_disable(CMU_MOD_DCE);
    for(i=0; i<0x10; i++);
    cmu_mod_enable(CMU_MOD_DCE);
}

void dce_en(void)
{
	DCE_Regs.DCE_CTL.bit.CAL_EN = 0x1;
}
void dce_sel(DCE_MODE_TYP mode, DCE_DATA_SEL sel)
{
	DCE_Regs.DCE_CFG.bit.MODE_SEL = mode;
	DCE_Regs.DCE_CFG.bit.DAT_SRC_SEL = sel;
}
void dce_irq_enable(u32 en)
{
	DCE_Regs.DCE_IRQ_EN.all = (en & 0x7000003);
}
u32 get_dce_irq_sts(void)
{
	u32 sts;
	sts = (DCE_Regs.DCE_IRQ_STS.all & 0x7000003);
	return sts;
}
void dce_addr_set(u32 addr)
{
	DCE_Regs.DCE_DATA_ADDR = addr;
}
void dce_data_len_set(u32 len)
{
	DCE_Regs.DCE_DATA_LEN.bit.DATA_LEN = len;
}
void dce_crc_cfg(u32 poly,u32 poly_size,u32 crc_init,u32 crc_xor)
{
	DCE_Regs.DCE_CRC_POLY = poly;
	DCE_Regs.DCE_CRC_SIZE.bit.POLY_SIZE = poly_size;
	DCE_Regs.DCE_CRC_INIT = crc_init;
	DCE_Regs.DCE_CRC_XOROUT = crc_xor;
}
void dce_data_set(u32 data)
{
	DCE_Regs.DCE_DATA_INPUT = data;
}
void dce_rev_cfg(u32 rev)
{
	DCE_Regs.DCE_CRC_CFG.all = (rev & 0xf);
}
u32 dce_get_result(void)
{
	u32 mode = DCE_Regs.DCE_CFG.bit.MODE_SEL;
	u32 result;
	switch(mode) {
		case 1:
			result = DCE_Regs.DCE_CRC_RESULT;
			break;
		case 2:
			result = DCE_Regs.DCE_SUM_RESULT;
			break;
		default:
			break;
	}
}
