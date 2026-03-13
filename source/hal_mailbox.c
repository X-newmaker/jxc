/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
#include "all_inc.h"

static void mbox_c02c1_null(void){};
static void mbox_c12c0_null(void){};
cpu_irq_fun_t mbox_c02c1_irqhandle = mbox_c02c1_null;
cpu_irq_fun_t mbox_c12c0_irqhandle = mbox_c12c0_null;

/* INTERRUPT Context */
static mbox_cb_t g_mb_c02c1_rx_cb = NULL;
static mbox_tx_cb_t g_mb_c02c1_tx_cb = NULL;

static mbox_cb_t g_mb_c12c0_rx_cb = NULL;
static mbox_tx_cb_t g_mb_c12c0_tx_cb = NULL;

ATTRIBUTE_ISR void MBOX_C02C1_IRQHandler(void)
{
        mbox_c02c1_irq_handler();
}

ATTRIBUTE_ISR void MBOX_C12C0_IRQHandler(void)
{
        mbox_c12c0_irq_handler();
}

void mbox_c02c1_irq_handler(void)
{
        mbox_c02c1_irqhandle();
}

void mbox_c0_irq_register(cpu_irq_fun_t irqhandle)
{
        mbox_c02c1_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_MBOX_C02C1);
}

void mbox_c0_irq_unregister(void)
{
        mbox_c02c1_irqhandle = mbox_c02c1_null;
        cpu_irq_disable(CPU_IRQ_MBOX_C02C1);
}


void mbox_c12c0_irq_handler(void)
{
        mbox_c12c0_irqhandle();
}

void mbox_c1_irq_register(cpu_irq_fun_t irqhandle)
{
        mbox_c12c0_irqhandle = irqhandle;
        cpu_irq_enable(CPU_IRQ_MBOX_C12C0);
}

void mbox_c1_irq_unregister(void)
{
        mbox_c12c0_irqhandle = mbox_c12c0_null;
        cpu_irq_disable(CPU_IRQ_MBOX_C12C0);
}

void mb_cpu0_init(void)
{
	mb_int_clr(MBOX0, MBOX_IRQ_CARED);
	mb_int_all_en(MBOX0);
	mbox_c0_irq_register(mb_c02c1_isr);
}

void mb_cpu1_init(void)
{
	mb_int_clr(MBOX1, MBOX_IRQ_CARED);
	mb_int_all_en(MBOX1);
	mbox_c1_irq_register(mb_c12c0_isr);
}

/****************************/
void mb_comp_mode(u32 i)
{
	sbit(0x1<<1,MBOX_CTL(i));
}

void mb_debug_mode(u32 i)
{
	sbit(0x1,MBOX_CTL(i));
}

//**********FIFO**************//
void mb_rxfifo_rst(u32 i)
{
	sbit(0x1<<31,MBOX_FIFO_CSR(i));
}

void mb_rxfifo_level(u32 i, u32 level)
{
	cbit(0x3f<<24,MBOX_FIFO_CSR(i));
	sbit(level<<24,MBOX_FIFO_CSR(i));
}

u32 mb_rxfifo_cnt(u32 i)
{
	u32 val;
	val = readl(MBOX_FIFO_CSR(i));
	val = (val >> 16) & 0xff;
	return val;
}

void mb_txfifo_overflow_ctl(u32 i)
{
	sbit(0x1<<14,MBOX_FIFO_CSR(i));
}

void mb_txfifo_rst(u32 i)
{
	sbit(0x1<<15,MBOX_FIFO_CSR(i));
}

void mb_txfifo_level(u32 i, u32 level)
{
	cbit(0x3f<<8,MBOX_FIFO_CSR(i));
	sbit(level<<8,MBOX_FIFO_CSR(i));
}

u32 mb_txfifo_cnt(u32 i)
{
	u32 val;
	val = readl(MBOX_FIFO_CSR(i));
	val = (val >> 0) & 0xff;
	return val;
}

//**********Interrupt STS**************//
u32 mb_int_sta(u32 i)
{
	return readl(MBOX_IRQ_STAS(i));
}

void mb_int_clr(u32 i, u32 sta)
{
	writel(sta, MBOX_IRQ_STAS(i));
}

void mb_int_all_en(u32 i)
{
	writel(MBOX_IRQ_CARED, MBOX_IRQ_EN(i));
}

void mb_int_all_dis(u32 i)
{
	writel(0x0, MBOX_IRQ_EN(i));
}

//**********mailbox read/write**************//
void mb_wmsg(u32 i, u32 msg)
{
	writel(msg,MBOX_WMSG(i));
}

void mb_wcomp(u32 i, u32 wcomp)
{
	writel(wcomp,MBOX_WCOMP(i));
}

s32 mb_rmsg(u32 i)
{
	return readl(MBOX_RMSG(i));
}

s32 mb_rcomp(u32 i)
{
	return readl(MBOX_RCOMP(i));
}

u32 mb_rd(u32 i, u32 *data, u32 cnt)
{
    u32 num;

    for (num = 0; (num < cnt) && (num < MBOX_MAX_DAT_LEN - 1); num++)
        data[num] = readl(MBOX_RMSG(i));

    return num;
}

u32 mb_wr(u32 i, u32 *data, u32 cnt)
{
    u32 num;

    for (num = 0; (num < cnt) && (num < MBOX_MAX_DAT_LEN - 1); num++)
        writel(data[num], MBOX_WMSG(i));

    return num;
}

//MBOX0 Interrupt Handler
void mb_c02c1_isr(void)
{
    static u32 index_c0 = 0, data_c0[MBOX_MAX_DAT_LEN] = {0};
    u32 sta = 0, cnt = 0;

    sta = mb_int_sta(MBOX0);
    mb_int_clr(MBOX0, sta);

    //远端接收完成标志，对应是本地完成发送
    if ((sta & MBOX_IRQ_R_RX_CMP)  == MBOX_IRQ_R_RX_CMP) {
        if (g_mb_c02c1_tx_cb)
        	g_mb_c02c1_tx_cb();
//        printk("mbox0: Peer had received data\n");
    }

    if ((sta & MBOX_IRQ_RX_UF)  == MBOX_IRQ_RX_UF) {
//    	printk("mbox0: RxFIFO is underflow!\n");
    	mb_rxfifo_rst(MBOX0);
        goto handled;
    }

    //远端发送完成标志，对应是本地完成接收
    if ((sta & MBOX_IRQ_M_TX_CMP)  == MBOX_IRQ_M_TX_CMP ) {
        cnt = mb_rxfifo_cnt(MBOX0);
//        printk("mbox0: Recv len %d Word, index %d \n", cnt, index_c0);
        if (!cnt) {
//        	printk("mbox0: No data in FIFO!\n");
            goto handled;
        }
        if (cnt > 1) {
        	mb_rd(MBOX0, &data_c0[index_c0], cnt - 1);
        	index_c0 += cnt - 1;
        }

		if (g_mb_c02c1_rx_cb)
			g_mb_c02c1_rx_cb(data_c0, index_c0);

		index_c0 = 0;

        goto handled;
    }

    if ((sta & MBOX_IRQ_TX_OF)  == MBOX_IRQ_TX_OF ) {
//        printk("mbox0: TxFIFO is overflow!\n");
        goto handled;
    }

    if ((sta & MBOX_IRQ_TX_FULL)  == MBOX_IRQ_TX_FULL ) {
//    	printk("mbox0: TxFIFO is full!\n");
        goto handled;
    }

handled:
    return;
}

//MAILBOX0 RX Complete callback
void mb_cpu0_set_rxcmp_cb(mbox_cb_t cb)
{
    if (!cb)
        return;

    /* INTERRUPT Context */
    g_mb_c02c1_rx_cb = cb;
}

//MAILBOX0 TX Complete callback
void mb_cpu0_set_txcmp_cb(mbox_tx_cb_t cb)
{
    if (!cb)
        return;

    /* INTERRUPT Context */
    g_mb_c02c1_tx_cb = cb;
}

//MBOX1 Interrupt Handler
void mb_c12c0_isr(void)
{
    static u32 index_c1 = 0, data_c1[MBOX_MAX_DAT_LEN] = {0};
    u32 sta = 0, cnt = 0;

    sta = mb_int_sta(MBOX1);
    mb_int_clr(MBOX1, sta);

    //远端接收完成标志，对应是本地完成发送
    if ((sta & MBOX_IRQ_R_RX_CMP)  == MBOX_IRQ_R_RX_CMP) {
        if (g_mb_c12c0_tx_cb)
        	g_mb_c12c0_tx_cb();
//        printk("mbox1: Peer had received data\n");
    }

    if ((sta & MBOX_IRQ_RX_UF)  == MBOX_IRQ_RX_UF) {
//    	printk("mbox1: RxFIFO is underflow!\n");
    	mb_rxfifo_rst(MBOX1);
        goto handled;
    }

    //远端发送完成标志，对应是本地完成接收
    if ((sta & MBOX_IRQ_M_TX_CMP)  == MBOX_IRQ_M_TX_CMP ) {
        cnt = mb_rxfifo_cnt(MBOX1);
//        printk("mbox1: Recv len %d Word, index %d \n", cnt, index_c1);
        if (!cnt) {
//        	printk("mbox1: No data in FIFO!\n");
            goto handled;
        }
        if (cnt > 1) {
        	mb_rd(MBOX1, &data_c1[index_c1], cnt - 1);
        	index_c1 += cnt - 1;
        }

		if (g_mb_c12c0_rx_cb)
			g_mb_c12c0_rx_cb(data_c1, index_c1);

		index_c1 = 0;

        goto handled;
    }

    if ((sta & MBOX_IRQ_TX_OF)  == MBOX_IRQ_TX_OF ) {
//        printk("mbox1: TxFIFO is overflow!\n");
        goto handled;
    }

    if ((sta & MBOX_IRQ_TX_FULL)  == MBOX_IRQ_TX_FULL ) {
//    	printk("mbox1: TxFIFO is full!\n");
        goto handled;
    }

handled:
    return;
}

//MAILBOX1 RX Complete callback
void mb_cpu1_set_rxcmp_cb(mbox_cb_t cb)
{
    if (!cb)
        return;

    /* INTERRUPT Context */
    g_mb_c12c0_rx_cb = cb;
}

//MAILBOX1 TX Complete callback
void mb_cpu1_set_txcmp_cb(mbox_tx_cb_t cb)
{
    if (!cb)
        return;

    /* INTERRUPT Context */
    g_mb_c12c0_tx_cb = cb;
}


