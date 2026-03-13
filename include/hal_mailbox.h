/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
#include "all_inc.h"

//自定义收发的数据的命令
#define MSG_SND		0xa0a0
#define MSG_END		0xffff

struct aic_rpmsg {
    uint16_t cmd;
    uint8_t  seq;
    uint8_t  len;    /* length of data[], unit: dword */
    uint32_t data[]; /* length varies according to the scene */
};

struct aic_rpmsg_sram {
    uint16_t  cmd;
    uint16_t  seq;
    uint32_t  len;    /* length of data, unit: byte */
    uint8_t * data_addr; /* data_addr */
};

#define MBOX0	0x0
#define MBOX1 	0x1

#define MBOX_MAX_DAT_LEN    32

#define MBOX_IRQ_M_TX_CMP           (0x1<<11)
#define MBOX_IRQ_RX_UF              (0x1<<10) /* underflow */
#define MBOX_IRQ_RX_FULL            (0x1<<9)
#define MBOX_IRQ_RX_EMPTY           (0x1<<8)
#define MBOX_IRQ_R_RX_CMP           (0x1<<3)
#define MBOX_IRQ_TX_OF              (0x1<<2) /* overflow */
#define MBOX_IRQ_TX_FULL            (0x1<<1)
#define MBOX_IRQ_TX_EMPTY           (0x1<<0)
#define MBOX_IRQ_CARED              (MBOX_IRQ_R_RX_CMP | MBOX_IRQ_M_TX_CMP | MBOX_IRQ_RX_UF \
                                    | MBOX_IRQ_TX_OF)

#define	    MB(i)		            (BASE_MBOX_C02C1 + (i*0x3000))

#define		MBOX_CTL(i)			    (MB(i)+0x00)
#define		MBOX_FIFO_CSR(i)		(MB(i)+0x04)
#define		MBOX_IRQ_EN(i)	        (MB(i)+0x08)
#define		MBOX_IRQ_STAS(i)		(MB(i)+0x0C)
#define		MBOX_WMSG(i)			(MB(i)+0x10)
#define		MBOX_WCOMP(i)		    (MB(i)+0x14)
#define		MBOX_RMSG(i)			(MB(i)+0x18)
#define		MBOX_RCOMP(i)		    (MB(i)+0x1C)
#define		MBOX_VERSION(i)		    (MB(i)+0xFFC)


typedef void (*mbox_cb_t)(u32 *data, u32 len);
typedef void (*mbox_tx_cb_t)(void);

void mbox_c02c1_irq_handler(void);
void mbox_c0_irq_register(cpu_irq_fun_t irqhandle);
void mbox_c0_irq_unregister(void);
void mbox_c12c0_irq_handler(void);
void mbox_c1_irq_register(cpu_irq_fun_t irqhandle);
void mbox_c1_irq_unregister(void);
void mb_cpu0_init(void);
void mb_cpu1_init(void);

//Mailbox API
void mb_comp_mode(u32 i);
void mb_debug_mode(u32 i);
void mb_rxfifo_rst(u32 i);
void mb_rxfifo_level(u32 i, u32 level);
u32 mb_rxfifo_cnt(u32 i);
void mb_txfifo_overflow_ctl(u32 i);
void mb_txfifo_rst(u32 i);
void mb_txfifo_level(u32 i, u32 level);
u32 mb_txfifo_cnt(u32 i);
u32 mb_int_sta(u32 i);
void mb_int_clr(u32 i, u32 sta);
void mb_int_all_en(u32 i);
void mb_int_all_dis(u32 i);
void mb_wmsg(u32 i, u32 msg);
void mb_wcomp(u32 i, u32 wcomp);
s32 mb_rmsg(u32 i);
s32 mb_rcomp(u32 i);
u32 mb_rd(u32 i, u32 *data, u32 cnt);
u32 mb_wr(u32 i, u32 *data, u32 cnt);
void mb_c02c1_isr(void);
void mb_cpu0_set_rxcmp_cb(mbox_cb_t cb);
void mb_cpu0_set_txcmp_cb(mbox_tx_cb_t cb);

void mb_c12c0_isr(void);
void mb_cpu1_set_rxcmp_cb(mbox_cb_t cb);
void mb_cpu1_set_txcmp_cb(mbox_tx_cb_t cb);
