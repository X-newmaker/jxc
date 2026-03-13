/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 */
#include <all_inc.h>
#include <common_stdarg.h>
extern volatile struct UART_REGS *UART[]; 

u32 dbg_uart_index = 0;
u32 upg_char_inum = 0;

void jump_to_rom_upgmode_entry(void)
{
    u8 *p = (void *)0x30000061;
    switch (*p) {
        case 0x34:
            writel(0x40, 0x1900f100); //WRI 写入复位信息
            break;
        case 0x35:
        	writel(0x49, 0x1900f100); //WRI 写入复位信息
            break;
        default:
            return;
    }

    wdog_cmu_init();
    wdog_force_reset();
}

void uart_upg_detect_isr(void)
{
	u32 sts;
	u32 err;
	u8 upg_char;

	sts = (uart_get_iir(0) & 0x7);

	if(sts == IIR_RECV_DATA)
	{

		uart_receive_char(0, &upg_char);
		if (upg_char == CTRL('R'))
				upg_char_inum ++;
		else
				upg_char_inum = 0;

		if(upg_char_inum > 5)
		{
			jump_to_rom_upgmode_entry();
		}

	}
}

//initial uart0 as upgrade port
s32 init_uart0_upg(void)
{
	u32 div;
	u32 lcr;
	u8 index = 0;
	UART_CFG_PARA dbg_uart;

	uart_dbg_gpio_init();      //升级功能串口UART0固定选择PG17/18管脚
	//set uart cmu cfg
	div = uart_dbg_cmu_init(index);

	dbg_uart.data_length    = UART_DLS_8;
	dbg_uart.stop_bit       = UART_STOP_TYPE0;
	dbg_uart.parity_fun     = UART_PARITY_DIS;
	dbg_uart.parity_mod     = UART_PARITY_MOD0;
	dbg_uart.baud_rate_div  = div;

	dbg_uart.fifo_cfg.FIFOE        = 0x01;
	dbg_uart.fifo_cfg.RXFIFOR      = 0x01;
	dbg_uart.fifo_cfg.TXFIFOR      = 0x01;
	dbg_uart.fifo_cfg.DMAM         = 0x00;
	dbg_uart.fifo_cfg.TFT          = TX_EMPTY;
	dbg_uart.fifo_cfg.RT           = RX_ONE_CHAR;

	dbg_uart_init(index, &dbg_uart);

	uart_irq_register(index,uart_upg_detect_isr);
	uart_rxd_int_en(index);

	return RET_OK;
}

s32 init_uart_dbg(u8 index)
{
	u32 div;
	u32 lcr;
	UART_CFG_PARA dbg_uart;

//	if(index == 0) {
//		dbg_uart_index = index;
//	} else {
	        dbg_uart_index = index;
	        //set uart cmu cfg
	        div = uart_dbg_cmu_init(index);

	        dbg_uart.data_length    = UART_DLS_8;
	        dbg_uart.stop_bit       = UART_STOP_TYPE0;
	        dbg_uart.parity_fun     = UART_PARITY_DIS;
	        dbg_uart.parity_mod     = UART_PARITY_MOD0;
	        dbg_uart.baud_rate_div  = div;

		dbg_uart.fifo_cfg.FIFOE        = 0x01;
		dbg_uart.fifo_cfg.RXFIFOR      = 0x01;
		dbg_uart.fifo_cfg.TXFIFOR      = 0x01;
		dbg_uart.fifo_cfg.DMAM         = 0x00;
		dbg_uart.fifo_cfg.TFT          = TX_EMPTY;
		dbg_uart.fifo_cfg.RT           = RX_ONE_CHAR;

	        dbg_uart_init(index, &dbg_uart);
//	}

	printk("\n");
	printk("****************************\n");
	printk("dbg_uart_%d initialize valid\n",index);
	printk("****************************\n");
	return RET_OK;
}

void uart_transmit_multi_char(u8 index, u8 *buf, u8 size)
{
        u32 i = 0;
        for(i=0;i<size;i++)
        {
                uart_transmit_char(index, (u8) buf[i]);
        }
}

u32 uart_dbg_cmu_init(u8 index)
{
	u32 cmu_no;
	u32 ret;
	cmu_no = CMU_MOD_UART0 + index;
	cmu_mod_disable(cmu_no);
	cmu_mod_set_freq(cmu_no,60000000);
	cmu_mod_enable(cmu_no);
	ret = cmu_mod_get_freq(cmu_no)/(UART_BAUDRATE*16);
	if(ret == 0)
		ret = 1;
	return ret;
}

void uart_dbg_gpio_init(void)
{
	gpio_enable(GPIO_GRP_G, 17, 2, GPIO_FUN_2);
}

void dbg_uart_init(u8 index, UART_CFG_PARA *uart_cfg_para)
{
	uart_tx_halt_en(index);
	uart_div_latch_access(index);

	uart_set_div_dlh(index, (uart_cfg_para->baud_rate_div)>>8);
	uart_set_div_dll(index, (uart_cfg_para->baud_rate_div)&0xff);

	uart_div_latch_clear(index);
	uart_tx_halt_dis(index);

	uart_set_op_para(index, uart_cfg_para);

	uart_fifo_cfg(index, &uart_cfg_para->fifo_cfg);
	uart_set_rx_enable(index);
}

void serial_put_char(char c)
{
	while ((*UART[dbg_uart_index]).UART_USR.bit.TFNF == 0x0) { };
	(*UART[dbg_uart_index]).UART_RBR_THR_DLL.bit_thr.THR = c;
}

char serial_get_char(void)
{
	while ((*UART[dbg_uart_index]).UART_USR.bit.RFNE == 0x1) { };
	return (*UART[dbg_uart_index]).UART_RBR_THR_DLL.bit_rbr.RBR;
}

u32 serial_puts(char* buf, u32 n)
{
	u32 i;
	for (i=0; i<n; i++)
		serial_put_char(buf[i]);
	return n;
}

u32 serial_gets(char* buf, u32 n)
{
	u32 i;
	char c;

	for (i=0; i<n; i++) {
		c = serial_get_char();
		if (c == 0)
			break;
		buf[i] = c;
	}
	return i+1;
}


