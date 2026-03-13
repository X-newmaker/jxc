/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_UART_DBG_H_
#define INCLUDE_HAL_UART_DBG_H_

#include <all_inc.h>

#ifndef CTRL
#define CTRL(c) (c - '@')
#endif

#define UART_BAUDRATE	        (115200)

#define		BYTE0(data)		(*(char *)(&data))			//ȡ�Ͱ�λ
#define		BYTE1(data)		(*((char *)(&data)+1))		//ȡ�εͰ�λ
#define		BYTE2(data)		(*((char *)(&data)+2))		//ȡ�θ߰�λ
#define		BYTE3(data)		(*((char *)(&data)+3))		//ȡ�߰�λ

s32 init_uart0_upg(void);
s32 init_uart_dbg(u8 index);
u32 uart_dbg_cmu_init(u8 index);
void uart_dbg_gpio_init(void);
void dbg_uart_init(u8 index, UART_CFG_PARA *uart_cfg_para);
u32 serial_puts(char* buf, u32 n);
u32 serial_gets(char* buf, u32 n);
char serial_get_char(void);

void uart_transmit_multi_char(u8 index, u8 *buf, u8 size);

#endif /* INCLUDE_HAL_UART_DBG_H_ */
