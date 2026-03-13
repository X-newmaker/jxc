/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 * uart.c
 */
#include <all_inc.h>

volatile struct UART_REGS Uart0Regs __attribute__((__section__(".uart0reg")));
volatile struct UART_REGS Uart1Regs __attribute__((__section__(".uart1reg")));
volatile struct UART_REGS Uart2Regs __attribute__((__section__(".uart2reg")));
volatile struct UART_REGS Uart3Regs __attribute__((__section__(".uart3reg")));
volatile struct UART_REGS Uart4Regs __attribute__((__section__(".uart4reg")));
volatile struct UART_REGS Uart5Regs __attribute__((__section__(".uart5reg")));
volatile struct UART_REGS Uart6Regs __attribute__((__section__(".uart6reg")));
volatile struct UART_REGS Uart7Regs __attribute__((__section__(".uart7reg")));
volatile struct UART_REGS Uart8Regs __attribute__((__section__(".uart8reg")));

volatile struct UART_REGS *UART[] = { &Uart0Regs, &Uart1Regs, &Uart2Regs, &Uart3Regs, \
				&Uart4Regs, &Uart5Regs, &Uart6Regs, &Uart7Regs , &Uart8Regs};

static void uart0_null(void){};
static void uart1_null(void){};
static void uart2_null(void){};
static void uart3_null(void){};
static void uart4_null(void){};
static void uart5_null(void){};
static void uart6_null(void){};
static void uart7_null(void){};
static void uart8_null(void){};
cpu_irq_fun_t uart0_irqhandle = uart0_null;
cpu_irq_fun_t uart1_irqhandle = uart1_null;
cpu_irq_fun_t uart2_irqhandle = uart2_null;
cpu_irq_fun_t uart3_irqhandle = uart3_null;
cpu_irq_fun_t uart4_irqhandle = uart4_null;
cpu_irq_fun_t uart5_irqhandle = uart5_null;
cpu_irq_fun_t uart6_irqhandle = uart6_null;
cpu_irq_fun_t uart7_irqhandle = uart7_null;
cpu_irq_fun_t uart8_irqhandle = uart8_null;

ATTRIBUTE_ISR void UART0_IRQHandler(void)
{
        uart0_irq_handler();
}

void uart0_irq_handler(void)
{
        uart0_irqhandle();
}

ATTRIBUTE_ISR void UART1_IRQHandler(void)
{
        uart1_irq_handler();
}

void uart1_irq_handler(void)
{
        uart1_irqhandle();
}

ATTRIBUTE_ISR void UART2_IRQHandler(void)
{
        uart2_irq_handler();
}

void uart2_irq_handler(void)
{
        uart2_irqhandle();
}

ATTRIBUTE_ISR void UART3_IRQHandler(void)
{
        uart3_irq_handler();
}

void uart3_irq_handler(void)
{
        uart3_irqhandle();
}

ATTRIBUTE_ISR void UART4_IRQHandler(void)
{
        uart4_irq_handler();
}

void uart4_irq_handler(void)
{
        uart4_irqhandle();
}

ATTRIBUTE_ISR void UART5_IRQHandler(void)
{
        uart5_irq_handler();
}

void uart5_irq_handler(void)
{
        uart5_irqhandle();
}

ATTRIBUTE_ISR void UART6_IRQHandler(void)
{
        uart6_irq_handler();
}

void uart6_irq_handler(void)
{
        uart6_irqhandle();
}

ATTRIBUTE_ISR void UART7_IRQHandler(void)
{
        uart7_irq_handler();
}

void uart7_irq_handler(void)
{
        uart7_irqhandle();
}

ATTRIBUTE_ISR void UART8_IRQHandler(void)
{
        uart8_irq_handler();
}

void uart8_irq_handler(void)
{
        uart8_irqhandle();
}

void uart_irq_register(u8 num, cpu_irq_fun_t irqhandle)
{
        switch(num) {
                case 0:
                        uart0_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART0);
                        break;
                case 1:
                        uart1_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART1);
                        break;
                case 2:
                        uart2_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART2);
                        break;        
                case 3:
                        uart3_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART3);
                        break;
                case 4:
                        uart4_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART4);
                        break;
                case 5:
                        uart5_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART5);
                        break;
                case 6:
                        uart6_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART6);
                        break;        
                case 7:
                        uart7_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART7);
                        break;
                case 8:
                        uart8_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_UART8);
                        break;
                default:
                        break;               
        }
}

void uart_irq_unregister(u8 num)
{
        switch(num) {
                case 0:
                        uart0_irqhandle = uart0_null;
                        cpu_irq_disable(CPU_IRQ_UART0);
                        break;
                case 1:
                        uart1_irqhandle = uart1_null;
                        cpu_irq_disable(CPU_IRQ_UART1);
                        break;
                case 2:
                        uart2_irqhandle = uart2_null;
                        cpu_irq_disable(CPU_IRQ_UART2);
                        break;        
                case 3:
                        uart3_irqhandle = uart3_null;
                        cpu_irq_disable(CPU_IRQ_UART3);
                        break;
                case 4:
                        uart4_irqhandle = uart4_null;
                        cpu_irq_disable(CPU_IRQ_UART4);
                        break;
                case 5:
                        uart5_irqhandle = uart5_null;
                        cpu_irq_disable(CPU_IRQ_UART5);
                        break;
                case 6:
                        uart6_irqhandle = uart6_null;
                        cpu_irq_disable(CPU_IRQ_UART6);
                        break;        
                case 7:
                        uart7_irqhandle = uart7_null;
                        cpu_irq_disable(CPU_IRQ_UART7);
                        break;
                case 8:
                        uart8_irqhandle = uart8_null;
                        cpu_irq_disable(CPU_IRQ_UART8);
                        break;
                default:
                        break;               
        }
}

void uart_set_cmu(u8 index)
{
        u32 cmu_no;
        cmu_no = CMU_MOD_UART0 + index;
        cmu_mod_disable(cmu_no);
        for(u8 i=0; i<0x10; i++);
        cmu_mod_set_freq(cmu_no,48000000);
        cmu_mod_enable(cmu_no);

}


//uart_set_cmu_br(): used for baudrate 380400/460800/500000/921600/1152000/1500000/2500000/3000000
u32 uart_set_cmu_br(u8 index, UART_BR_TYPE br_rate)
{
        u32 cmu_no;
        u32 div;
        cmu_no = CMU_MOD_UART0 + index;

        switch(br_rate) {
                case BR_380400:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 21);
                        cmu_mod_enable(cmu_no);
                        div = 9;
                        break;

                case BR_460800:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 26);
                        cmu_mod_enable(cmu_no);
                        div = 6;
                        break;

                case BR_500000:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 24);
                        cmu_mod_enable(cmu_no);
                        div = 6;
                        break;

                case BR_921600:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 26);
                        cmu_mod_enable(cmu_no);
                        div = 3;
                        break;

                case BR_1152000:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 21);
                        cmu_mod_enable(cmu_no);
                        div = 3;
                        break;

                case BR_1500000:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 24);
                        cmu_mod_enable(cmu_no);
                        div = 2;
                        break;

                case BR_2500000:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 29);
                        cmu_mod_enable(cmu_no);
                        div = 1;
                        break;

                case BR_3000000:
                        cmu_mod_disable(cmu_no);
                        cmu_mod_set_div(cmu_no, 24);
                        cmu_mod_enable(cmu_no);
                        div = 1;
                        break;

                default:
                        break;
        }
        return div;

}

u32 uart_get_br_div(u8 index, u32 br_rate)
{
        u32 cmu_no;
        u32 ret;
        cmu_no = CMU_MOD_UART0 + index;
        ret = (cmu_mod_get_freq(cmu_no)/br_rate) >> 4;
        if(ret == 0)
                ret = 1;
        return ret;
}

void uart_tx_halt_en(u8 index)
{
	(*UART[index]).UART_HALT.bit.HALT_TX = 0x1;
}

void uart_tx_halt_dis(u8 index)
{
	(*UART[index]).UART_HALT.bit.HALT_TX = 0x0;
}

void uart_div_latch_access(u8 index)
{
	(*UART[index]).UART_HALT.bit.CHCFG_AT_BUSY = 1;

	(*UART[index]).UART_LCR.bit.DLAB = 0x1;

	(*UART[index]).UART_HALT.bit.CHANGE_UPDT = 1;	// ????LCR
	while((*UART[index]).UART_HALT.bit.CHANGE_UPDT); //???UPDATE????
	(*UART[index]).UART_HALT.bit.CHCFG_AT_BUSY = 0;
}

void uart_div_latch_clear(u8 index)
{
	(*UART[index]).UART_LCR.bit.DLAB = 0x0;
}

void uart_set_div_dlh(u8 index, u32 dlh)
{
	(*UART[index]).UART_DLH_IER.bit_dlh.DLH = dlh;
}

void uart_set_div_dll(u8 index, u32 dll)
{
	(*UART[index]).UART_RBR_THR_DLL.bit_dll.DLL = dll;
}

void uart_set_op_para(u8 index,UART_CFG_PARA *uart_cfg_para)
{

	(*UART[index]).UART_HALT.bit.CHCFG_AT_BUSY = 1;

	(*UART[index]).UART_LCR.bit.DLS = uart_cfg_para->data_length;
	(*UART[index]).UART_LCR.bit.STOP = uart_cfg_para->stop_bit;
	(*UART[index]).UART_LCR.bit.PEN = uart_cfg_para->parity_fun;
	(*UART[index]).UART_LCR.bit.EPS = uart_cfg_para->parity_mod;
	(*UART[index]).UART_LCR.bit.DLAB = 0x0;

	(*UART[index]).UART_HALT.bit.CHANGE_UPDT = 1;	// ????LCR
	while((*UART[index]).UART_HALT.bit.CHANGE_UPDT); //???UPDATE????
	(*UART[index]).UART_HALT.bit.CHCFG_AT_BUSY = 0;
}

void uart_fifo_cfg(u8 index, UART_FCR_REG *frc)
{
        (*UART[index]).UART_IIR_FCR.all = *(u32 *)frc;
}

void de_assert_time_set(u8 index, u32 de_at, u32 de_dat)
{
	(*UART[index]).UART_485_DE.bit.DE_AT = de_at;
	(*UART[index]).UART_485_DE.bit.DE_DAT = de_at;
}

void uart_set_2wire_mode(u8 index)
{
	(*UART[index]).UART_MCR.bit.UART_FUNC = RS485_2WIRE_MOD;
}

void uart_set_485_mode(u8 index)
{
	(*UART[index]).UART_MCR.bit.UART_FUNC = RS485_MOD;
}

void uart_send_char(u32 uart_no, u8 data)
{
	(*UART[uart_no]).UART_RBR_THR_DLL.bit_thr.THR = data;
}

void uart_get_char(u32 uart_no, u8 *data)
{
	*data = (*UART[uart_no]).UART_RBR_THR_DLL.bit_thr.THR;
}

void uart_set_rx_bf_addr(u8 index)
{
	(*UART[index]).UART_485_CTL.bit.RX_BF_ADDR = 0x1;

}

void uart_set_de_hwmode(u8 index)
{
	(*UART[index]).UART_485_CTL.bit.RS485_CTL_MODE = 0x0;
}

u32 uart_get_lsr(u8 index)
{
        u32 sts;
        sts = (*UART[index]).UART_LSR.all;
        return sts;
}

void uart_set_rx_enable(u8 index)
{
    (*UART[index]).UART_RX_EN.bit.RX_EN = 0x1;
}

s32 uart_transmit_char(u8 index, u8 data)
{
        u32 timecount = 0;

        while (!(uart_get_lsr(index) & LSR_TRANS_EMPTY))
        {
                timecount ++;

                if (timecount >= UART_BUSY_TIMEOUT)
                {
                        printk("tx err\n");
                        return -1;
                }
        }

        uart_send_char(index, data);

        return 0;
}

s32 uart_receive_char(u8 index, u8 *data)
{
        u32 timecount = 0;

        while (!(uart_get_lsr(index) & LSR_DATA_READY))
        {
                timecount ++;

                if (timecount >= UART_BUSY_TIMEOUT)
                {
                        printk("rx err\n");
                        return -1;
                }
        }

        uart_get_char(index, data);

        return 0;
}

void uart_rxd_int_en(u8 index)
{
        (*UART[index]).UART_DLH_IER.bit_ier.ERBFI = 0x1;
}

void uart_txd_int_en(u8 index)
{
        (*UART[index]).UART_DLH_IER.bit_ier.ETBEI = 0x1;
}

void uart_txd_shift_empty_int_en(u8 index)
{
        (*UART[index]).UART_DLH_IER.bit_ier.SHIFT_REG_EMP_EN = 0x1;
}

void uart_rxd_int_dis(u8 index)
{
        (*UART[index]).UART_DLH_IER.bit_ier.ERBFI = 0x0;
}

void uart_txd_int_dis(u8 index)
{
        (*UART[index]).UART_DLH_IER.bit_ier.ETBEI = 0x0;
}

void uart_txd_shift_empty_int_dis(u8 index)
{
        (*UART[index]).UART_DLH_IER.bit_ier.SHIFT_REG_EMP_EN = 0x0;
}

u32 uart_get_iir(u8 index)
{
        u32 sts;
        sts = (*UART[index]).UART_IIR_FCR.all;
        return sts;
}

u32 uart_get_tfl(u8 index)
{
        u32 tfl;
        tfl = (*UART[index]).UART_TFL.bit.TFL;
        return tfl;
}

void uart_set_tfl(u8 index, u8 fifo_level)
{
       (*UART[index]).UART_TFAET.bit.TFAET = fifo_level;
}

void uart_set_rfl(u8 index, u8 fifo_level)
{
        (*UART[index]).UART_RFAET.bit.RFAET = fifo_level;
}

u32 uart_get_rfl(u8 index)
{
        u32 rfl;
        rfl = (*UART[index]).UART_RFL.bit.RFL;
        return rfl;
}

void uart_set_dma_handshake(u8 index)
{
        (*UART[index]).UART_HSK.bit.HSK = 0xe5;
}


u32 uart_get_fifo_addr(u8 index)
{
        u32 addr;
        addr =  (u32) UART[index];
        return addr;
}

s32 uart_dma_tx_request(u8 index, u8 ch, u32 saddr, u32 len)
{
        s32 ret;
        u32 fifo_addr, dst_drq;
        fifo_addr = uart_get_fifo_addr(index);
        dst_drq = DMA_ID_CS_UART0 + index;
        ret = dma_request_reg(0, ch, DMA_ID_SRAM, DMA_W32_MEM_BLK16,  dst_drq, DMA_W08_IOS_BLK01, 0x100,
                    saddr, fifo_addr, len, 0);
        return ret;
}

s32 uart_dma_rx_request(u8 index, u8 ch, u32 daddr, u32 len)
{
        s32 ret;
        u32 fifo_addr, src_drq;
        fifo_addr = uart_get_fifo_addr(index);
        src_drq = DMA_ID_CS_UART0 + index;
        ret = dma_request_reg(0, ch, src_drq, DMA_W08_IOS_BLK01,  DMA_ID_SRAM, DMA_W32_MEM_BLK16, 0x100,
                    fifo_addr, daddr, len, 0);
        return ret;
}

