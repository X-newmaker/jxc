/**
 * spi_hal.c
 */
#include <all_inc.h>

spi_dev_t* const spi_p[6] = {
		(spi_dev_t*)BASE_SPI0,(spi_dev_t*)BASE_SPI1,(spi_dev_t*)BASE_SPI2,
		(spi_dev_t*)BASE_SPI3,(spi_dev_t*)BASE_SPI4,(spi_dev_t*)BASE_SPI5
};


static void spi0_null(void){};
static void spi1_null(void){};
static void spi2_null(void){};
static void spi3_null(void){};
static void spi4_null(void){};
static void spi5_null(void){};
cpu_irq_fun_t spi0_irqhandle = spi0_null;
cpu_irq_fun_t spi1_irqhandle = spi1_null;
cpu_irq_fun_t spi2_irqhandle = spi2_null;
cpu_irq_fun_t spi3_irqhandle = spi3_null;
cpu_irq_fun_t spi4_irqhandle = spi4_null;
cpu_irq_fun_t spi5_irqhandle = spi5_null;

ATTRIBUTE_ISR void SPI0_IRQHandler(void)
{
        spi0_irq_handler();
}

void spi0_irq_handler(void)
{
        spi0_irqhandle();
}

ATTRIBUTE_ISR void SPI1_IRQHandler(void)
{
        spi1_irq_handler();
}

void spi1_irq_handler(void)
{
        spi1_irqhandle();
}

ATTRIBUTE_ISR void SPI2_IRQHandler(void)
{
        spi2_irq_handler();
}

void spi2_irq_handler(void)
{
        spi2_irqhandle();
}

ATTRIBUTE_ISR void SPI3_IRQHandler(void)
{
        spi3_irq_handler();
}

void spi3_irq_handler(void)
{
        spi3_irqhandle();
}

ATTRIBUTE_ISR void SPI4_IRQHandler(void)
{
        spi4_irq_handler();
}

void spi4_irq_handler(void)
{
        spi4_irqhandle();
}

ATTRIBUTE_ISR void SPI5_IRQHandler(void)
{
        spi5_irq_handler();
}

void spi5_irq_handler(void)
{
        spi5_irqhandle();
}

void spi_irq_register(u8 num, cpu_irq_fun_t irqhandle)
{
        switch(num){
                case 0:
                        spi0_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_SPI0);
                        break;
                case 1:
                        spi1_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_SPI1);
                        break;
                case 2:
                        spi2_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_SPI2);
                        break;        
                case 3:
                        spi3_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_SPI3);
                        break;
                case 4:
                        spi4_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_SPI4);
                        break;
                case 5:
                        spi5_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_SPI5);
                        break;
                default:
                        break;               
        }
}

void spi_irq_unregister(u8 num)
{
        switch(num){
                case 0:
                        spi0_irqhandle = spi0_null;
                        cpu_irq_disable(CPU_IRQ_SPI0);
                        break;
                case 1:
                        spi1_irqhandle = spi1_null;
                        cpu_irq_disable(CPU_IRQ_SPI1);
                        break;
                case 2:
                        spi2_irqhandle = spi2_null;
                        cpu_irq_disable(CPU_IRQ_SPI2);
                        break;        
                case 3:
                        spi3_irqhandle = spi3_null;
                        cpu_irq_disable(CPU_IRQ_SPI3);
                        break;
                case 4:
                        spi4_irqhandle = spi4_null;
                        cpu_irq_disable(CPU_IRQ_SPI4);
                        break;
                case 5:
                        spi5_irqhandle = spi5_null;
                        cpu_irq_disable(CPU_IRQ_SPI5);
                        break;
                default:
                        break;               
        }
}

void spi_cmu_init(u8 index)
{
	cmu_mod_disable(CMU_MOD_SPI0 + index);
	cmu_mod_set_freq((CMU_MOD_SPI0 + index),200*1000*1000);	//按100MHz的2倍频率进行配置
	cmu_mod_enable(CMU_MOD_SPI0 + index);
}

void spi_soft_rst(u8 index)
{
	spi_p[index]->SPI_CFG.bit.CTRL_RST = 0x1;
}


void spi_type1_clk_div(u8 index, u32 div)
{
        spi_p[index]->SPI_CCFG.bit.CKDIV_SEL = 0x0;
        spi_p[index]->SPI_CCFG.bit.CKDIV1 = div;
}

void spi_type2_clk_div(u8 index, u32 div)
{
        spi_p[index]->SPI_CCFG.bit.CKDIV_SEL = 0x1;
        spi_p[index]->SPI_CCFG.bit.CKDIV2 = div;
}

void spi_txdrq_en(u8 index)
{
        spi_p[index]->SPI_FCTL.bit.TF_DREQ_EN = 0x1;
}

void spi_rxdrq_en(u8 index)
{
        spi_p[index]->SPI_FCTL.bit.RF_DREQ_EN = 0x1;
}

void spi_txdrq_dis(u8 index)
{
        spi_p[index]->SPI_FCTL.bit.TF_DREQ_EN = 0x0;
}

void spi_rxdrq_dis(u8 index)
{
        spi_p[index]->SPI_FCTL.bit.RF_DREQ_EN = 0x0;
}

void spi_txfifo_level_set(u8 index, u32 level)
{
        spi_p[index]->SPI_FCTL.bit.TF_WATER_MARK = level;
}

void spi_rxfifo_level_set(u8 index, u32 level)
{
        spi_p[index]->SPI_FCTL.bit.RF_WATER_MARK = level;
}

void spi_txfifo_rst(u8 index)
{
		u32 val;
        spi_p[index]->SPI_FCTL.bit.TF_RST = 0x1;
        do {
        	val = spi_p[index]->SPI_FCTL.all;
        } while ((val & (0x1<<31)) == (0x1<<31));
}

void spi_rxfifo_rst(u8 index)
{
		u32 val;
        spi_p[index]->SPI_FCTL.bit.RF_RST = 0x1;
        do {
        	val = spi_p[index]->SPI_FCTL.all;
        } while ((val & (0x1<<15)) == (0x1<<15));
}

void spi_mbc_set(u8 index, u32 mbc)
{
        spi_p[index]->SPI_TBC.bit.TB_CNT = mbc;
}

void spi_mtc_set(u8 index, u32 mwtc)
{
        spi_p[index]->SPI_TWC.bit.TXD_CNT = mwtc;
}

void spi_stc_set(u8 index, u32 stc)
{
        spi_p[index]->SPI_TMC.bit.STXD_CNT = stc;
}

void spi_txdata_write(u8 index, u32 txd)
{
        spi_p[index]->SPI_TXD = txd;
}

void spi_xch(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.START = 0x1;
}

void spi_mosi_miso_multiplex(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.WIRE3_EN = MOSI_MISO_MULTIPEX;
}

//void spi_set_cs_out_de(u8 index)
//{
//        spi_p[index]->SPI_TCFG.bit.CS_OUT = CS_OUT_DE;
//}

void spi_dhb_en(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.DINVD = 0x1;
}

void spi_dhb_dis(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.DINVD = 0x0;
}
//在CS为软件控制时使用
void spi_cs_level_high(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CS_NUM = 0x1;
}
//在CS为软件控制时使用
void spi_cs_level_low(u8 index)
{
       spi_p[index]->SPI_TCFG.bit.CS_NUM = 0x0;
}

void spi_cs_owner_hw(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CS_CTL_SEL = HW_OWN;
}

void spi_cs_owner_sw(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CS_CTL_SEL = SW_OWN;
}

void spi_cs_unassert_inbst(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CS_VLD_CTL = 0x1;
}

void spi_cs_high_assert(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CSPOL = ACTIVE_HIGH;
}

void spi_cs_low_assert(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CSPOL = ACTIVE_LOW;
}

void spi_clk_idle_low(u8 index)
{
       spi_p[index]->SPI_TCFG.bit.CPOL = IDLE_LOW;
}

void spi_clk_idle_high(u8 index)
{
       spi_p[index]->SPI_TCFG.bit.CPOL = IDLE_HIGH;
}

void spi_ph0_sample(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CPHA = PH0;
}

void spi_ph1_sample(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.CPHA = PH1;
}

void spi_rxdelay_sample(u8 index)
{
        spi_p[index]->SPI_TCFG.bit.RXDLY_DIS = 0x1;
        spi_p[index]->SPI_TCFG.bit.RXINDLY_EN = 0x0;
}

void spi_en(u8 index)
{
        spi_p[index]->SPI_CFG.bit.EN = 0x1;
}

void spi_int_sts_clr(u8 index)
{
        spi_p[index]->SPI_ISTS.all = 0xffff;
}

void spi_master_en(u8 index)
{
        spi_p[index]->SPI_CFG.bit.MODE = 0x1;
}

u32 spi_get_int_sts(u8 index)
{
        u32 int_sts;
        int_sts = spi_p[index]->SPI_ISTS.all;
        return int_sts;
}

u32 spi_get_rx_dat(u8 index)
{
        u32 rx_dat;
        rx_dat = spi_p[index]->SPI_RXD;
        return rx_dat;
}

void spi_tc_sts_clr(u8 index)
{
        spi_p[index]->SPI_ISTS.bit.TD = 0x1;
}

s32 spi_dma_tx_request(u8 index, u8 ch, u32 saddr, u32 len)
{
        s32 ret;
        u32 fifo_addr, dst_drq;
        fifo_addr = SPI_TXD(index);
        dst_drq = DMA_ID_CS_SPI0 + index;
//        ret = dma_request(0, ch, DMA_ID_SRAM, DMA_W32_MEM_BLK16,  dst_drq, DMA_W08_IOB_BLK16, 0x10,
//                    saddr, fifo_addr, len, 1, 0);
        return ret;
}

s32 spi_dma_rx_request(u8 index, u8 ch, u32 daddr, u32 len)
{
        s32 ret;
        u32 fifo_addr, src_drq;
        fifo_addr = SPI_RXD(index);
        src_drq = DMA_ID_CS_SPI0 + index;
//        ret = dma_request(0, ch, src_drq, DMA_W08_IOB_BLK16,  DMA_ID_SRAM, DMA_W32_MEM_BLK16, 0x10,
//                    fifo_addr, daddr, len, 1, 0);
        return ret;
}

u32 spi_get_rx_fifo_cnt(u32 index)
{
    return spi_p[index]->SPI_FSTS.bit.RF_CNT;
}
