/*
 * e2prom.h
 *
 *  Created on: 2023年9月19日
 *      Author: wenxing ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_E2PROM_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_E2PROM_H_

#include "Const_Def.h"

#ifdef	EEPROM_SPI

	extern void spi_init_e2prom(void);
	extern void spi_wren_e2prom(u32 index);
	extern void spi_write_e2prom(u32 index,u16 waddr,u16 wdata);
	extern u8 spi_rsdr_e2prom(u32 index);
	extern s16 spi_read_e2prom(u32 index, u16 raddr);
	extern u32 eeprom_dev_num;

	#define		write_e2prom		spi_write_e2prom
	#define		read_e2prom			spi_read_e2prom

#else
	extern void i2c_init_e2prom(void);
	extern void i2c_write_e2prom(u32 i2c_num,u16 waddr,u16 wdata);
	extern s16 i2c_read_e2prom(u32 i2c_num,u16 raddr);
	extern u32 eeprom_dev_num;

	#define		write_e2prom		i2c_write_e2prom
	#define		read_e2prom			i2c_read_e2prom

	#endif
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_E2PROM_H_ */
