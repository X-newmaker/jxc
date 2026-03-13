#include <aic_ecat_eeprom_emulation.h>
#include <flash_drv.h>
#include "aic_ecat_fee.h"
#include "ecat_def.h"

#if ESC_EEPROM_EMULATION

#include "foeappl.h"
#include "servo_drv_setting.h"
#include "applinterface.h"
#include "sfud.h"
#include "aic_ecat_cfg.h"
#include "ecatappl.h"

e2p_t e2p_info;
extern e2p_block *e2p_info_table;
extern void flash_init(void);
extern sfud_flash *me_flash;

u16 AIC_fee_Read(uint32_t wordaddr)
{
	u8 value[8];
	if (wordaddr <= ESC_EEPROM_SIZE) {
		UINT16 *pData = (UINT16*) value;
		e2p_read(wordaddr, pData, EepromReadSize);

		HW_EscWrite((MEM_ADDR*) &value[0], ESC_EEPROM_DATA_OFFSET, EepromReadSize);

	} else {
		goto AIC_fee_Read_err;
	}

	return 0;
AIC_fee_Read_err:
	return 1;
}

u16 AIC_fee_Write(uint32_t wordaddr)
{
	u8 value[8];
	u8 ret;

	if (wordaddr <= ESC_EEPROM_SIZE) {
		HW_EscRead((MEM_ADDR*) &value[0], ESC_EEPROM_DATA_OFFSET, EEPROM_WRITE_SIZE);
		ret = e2p_write(wordaddr, (u16*) &value[0], EEPROM_WRITE_SIZE);
		if(ret)
			goto AIC_fee_Read_err;
	} else {
		goto AIC_fee_Read_err;
	}

	return 0;
AIC_fee_Read_err:
	return 1;
}

u8 AIC_fee_gen_Checksum(u8 *data, u32 size)
{
	u8 crc = 0xFF;
	u8 poly = 0x07; //crc-8 polynomial x^8 + x^2 + x + 1

	for(u32 i = 0; i < size; i++) {
		crc ^= data[i];
		for(u8 j = 0; j < 8; j++) {
			if(crc & 0x80) {
				crc = (crc << 1) ^ poly;
			} else
				crc <<= 1;
		}
	}
	return crc;
}

u16 AIC_fee_Reload(void)
{
	u16 e2p_data[8];
	u8 crc;
	u32 reload_cfg = 0;
	aic_stat_t  ret = e2p_read(0, (u8 *)e2p_data, 8*2);

	if(ret) {
		return ECAT_FEE_FLASH_ERR;
	}

	crc = AIC_fee_gen_Checksum((u8 *)e2p_data, 7*2);

	if(crc == (e2p_data[7] & 0xff)) {
		//15:0 for alias
		reload_cfg |= e2p_data[4];
		//20:16 refer to register 0x141
		reload_cfg |= ((e2p_data[0] >> (8 + 1)) & 0x01) << 16;   //enhanced link det for all ports
		reload_cfg |= ((e2p_data[0] >> (8 + 4)) & 0x01) << 17;   //enhanced link det for ind port0
		reload_cfg |= ((e2p_data[0] >> (8 + 5)) & 0x01) << 18;   //enhanced link det for ind port1
		reload_cfg |= ((e2p_data[0] >> (8 + 6)) & 0x01) << 19;   //enhanced link det for ind port2
		reload_cfg |= ((e2p_data[0] >> (8 + 7)) & 0x01) << 20;   //enhanced link det for ind port3
		//24:21 for ESC DL configuration

		//27:25 for FIFO reduction

		HW_EscWriteDWord(reload_cfg, ESC_EEPROM_DATA_OFFSET);
		return ECAT_FEE_SUCCESS;
	} else {
		return ECAT_FEE_CHECKSUM_ERR;
	}

}

void AIC_fee_reload_response(void)
{
	u16 csr ;
	HW_EscRead((MEM_ADDR*) &csr, 0x502, 2);
    if ((csr & 0x20U) == 0x20U) {                                          //eeprom emulation
        if ((csr & 0x8000U) == 0x8000U) {                                  //eeprom interface is busy
            if (((csr >> 8) & 0x7) == 0x4) {                               //reload cmd
                if (AIC_fee_Reload() == ECAT_FEE_SUCCESS) {                //checksum ok
                	csr &= ~(0x01 << 11);
                } else if (AIC_fee_Reload() == ECAT_FEE_CHECKSUM_ERR){     //checksum err
                	csr |= 0x01 << 11;
                } else {                                                   //ack err
                	csr |= 0x01 << 13;
                }
                HW_EscWrite((MEM_ADDR*)&csr, 0x502, 2);                    //response
            }
        }
    }
}

uint32_t e2p_flash_read(uint8_t *buf, uint32_t addr, uint32_t size)
{
	return sfud_read(me_flash, addr, size, buf);
}

uint32_t e2p_flash_write(uint8_t *buf, uint32_t addr, uint32_t size)
{
	return sfud_write(me_flash, addr, size, buf);
}

void e2p_flash_erase(uint32_t start_addr, uint32_t size)
{
	sfud_erase(me_flash, start_addr, size);
}

void AIC_fee_Init(void)
{
	if(me_flash == NULL){
		flash_init();
	}

	part_t *part = get_part_by_name("escxml");
	if(part == NULL) {
		printk("can't find escxml partition...\n");
		return;
	}

	e2p_info.config.start_addr = part->start;
	e2p_info.config.erase_size = FLASH_EARSE_SIZE;
	e2p_info.config.sector_cnt = (part->size)/4096;
	e2p_info.config.version = 0x414943;
	e2p_info.config.flash_read = e2p_flash_read;
	e2p_info.config.flash_write = e2p_flash_write;
	e2p_info.config.flash_erase = e2p_flash_erase;
	E2P_COUNT = part->size / E2P_EEPROM_SIZE_4K_UP_ALIGN;

	volatile u8 debug = 0;
	if(debug){
		e2p_info.config.flash_erase(e2p_info.config.start_addr, e2p_info.config.sector_cnt * e2p_info.config.erase_size);
	}

	e2p_info_table = (struct e2p_block *)ALLOCMEM(sizeof(e2p_block) * E2P_COUNT);
	e2p_config(&e2p_info);
	AIC_fee_reload_response();
}
#endif
