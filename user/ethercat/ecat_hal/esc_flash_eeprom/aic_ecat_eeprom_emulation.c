/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <aic_ecat_eeprom_emulation.h>
u32 E2P_COUNT = 0;
e2p_block *e2p_info_table = NULL;
static e2p_t *e2p_valid_ctx;
static u8 xml_data[E2P_EEPROM_SIZE_4K_UP_ALIGN];
static s8 activeBlock = -1;
static s8 Old_activeBlock = -1;
static s8 receivingBlock = -1;

static void e2p_print_info(e2p_t *e2p)
{
	uint32_t info_count = E2P_COUNT;
	uint32_t valid_count = 0;

	e2p_info("------------ flash->eeprom init ok -----------");

	for (int i = 0; i < E2P_COUNT; i++) {
		if (e2p_info_table[i].valid_state == e2p_valid) {
			valid_count++;
		}
		e2p_info("----------------------[%d]----------------------", i);
		e2p_info("block_id: 0x%x", e2p_info_table[i].block_id);
		e2p_info("block_addr: 0x%x", e2p_info_table[i].block_addr);
		e2p_info("data_addr: 0x%x", e2p_info_table[i].data_addr);
		e2p_info("length: 0x%x", e2p_info_table[i].length);
		e2p_info("valid_state: 0x%x", e2p_info_table[i].valid_state);
		e2p_info("last_block_addr: 0x%x", e2p_info_table[i].last_block_addr);
		e2p_info("next_block_addr: 0x%x", e2p_info_table[i].next_block_addr);
		e2p_info("----------------------[%d]----------------------\n", i);
	}

	e2p_info("start address: 0x%08x", e2p->config.start_addr);
	e2p_info("sector count: %u", e2p->config.sector_cnt);
	e2p_info("flash earse granularity: %u", e2p->config.erase_size);
	e2p_info("version: 0x%x", e2p->config.version);
	e2p_info("end address: 0x%08x", e2p->config.start_addr + e2p->config.sector_cnt * e2p->config.erase_size);
	e2p_info("valid count percent info count( %u / %u )", valid_count, info_count);
	e2p_info("----------------------------------------------\n");
}

aic_stat_t e2p_write(u32 addr, uint8_t *data, uint16_t length)
{
	static u8 move_flag = 0;
	e2p_block *active_block = &(e2p_info_table[activeBlock]);
	e2p_config_t *cfg = &(e2p_valid_ctx->config);

	if (Old_activeBlock != activeBlock) {
		cfg->flash_read((uint8_t*) xml_data, active_block->data_addr, active_block->length);
		Old_activeBlock = activeBlock;
	}

	if (move_flag == 0) {
		for (u16 i = addr * 2; i < (addr * 2) + length; i++) {
			if ((xml_data[i] != 0xff) && (xml_data[i] != data[i - (addr * 2)])) {
				e2p_info("set move_flag i=%d..\n", i);
				move_flag = 1;
				break;
			}
		}
	}

	if (_memcmp(&xml_data[addr * 2], data, length) != 0) {
		_memcpy(&xml_data[addr * 2], data, length);
	}

	if (addr == (ESC_EEPROM_SIZE / 2) - 1) {
		if (move_flag) {
			receivingBlock = activeBlock;

			for (u8 i = 0; i < E2P_COUNT; i++) {
				receivingBlock++;
				if (receivingBlock >= E2P_COUNT) {
					Old_activeBlock = -1;
					receivingBlock = 0;
				}

				e2p_info("%d: check block[%d]\n", i, receivingBlock);
				if ((e2p_info_table[receivingBlock].valid_state == e2p_earsed)) { //activeBlock后一个block是否空闲
					e2p_info("got a new block[%d]\n", receivingBlock);
					break;
				}

				if (i == (E2P_COUNT-1)) {
					e2p_err("non free block to write, auto clean invalid block, then try again...\n");
					for (int i = 0; i < E2P_COUNT; i++) {
						e2p_block *cur_block = &e2p_info_table[i];
						if(activeBlock != i){
							e2p_info("clean invalid block[%d]\n", i);
							cfg->flash_erase(cur_block->block_addr, E2P_EEPROM_SIZE_4K_UP_ALIGN);
							cur_block->valid_state = e2p_earsed;
							cur_block->last_block_addr = 0xffffffff;
						}
					}
					Old_activeBlock = -1;
					e2p_info("clean invalid block done\n");
					return 1;
				}
			}


			active_block->next_block_addr = active_block->block_addr + active_block->length + sizeof(e2p_block);
			active_block->valid_state = e2p_invalid;
			cfg->flash_write((uint8_t*) active_block, active_block->block_addr, sizeof(e2p_block));

			e2p_block *receiving_block = &e2p_info_table[receivingBlock];
			receiving_block->block_id = receivingBlock;
			receiving_block->block_addr = active_block->next_block_addr;
			receiving_block->data_addr = active_block->next_block_addr + sizeof(e2p_block);
			receiving_block->length = E2P_EEPROM_SIZE_4K_UP_ALIGN - sizeof(e2p_block);
			receiving_block->valid_state = e2p_valid;
			receiving_block->last_block_addr = active_block->block_addr;
			cfg->flash_write((uint8_t*) receiving_block, receiving_block->block_addr, sizeof(e2p_block));
			cfg->flash_write((uint8_t*) xml_data, receiving_block->data_addr, receiving_block->length);
			activeBlock = receivingBlock;
			e2p_info("move %d to %d\n", active_block->block_id, receiving_block->block_id);
		} else {
			e2p_info("write to %d\n", active_block->block_id);
			cfg->flash_write((uint8_t*) xml_data, active_block->data_addr, active_block->length);
		}
		move_flag = 0;
	}

	return 0;
}

aic_stat_t e2p_read(u32 addr, uint8_t *data, uint16_t length)
{
	e2p_block *active_block = &(e2p_info_table[activeBlock]);
	e2p_config_t *cfg = &(e2p_valid_ctx->config);

	if (Old_activeBlock != activeBlock) {
		cfg->flash_read((uint8_t*) xml_data, active_block->data_addr, active_block->length);
		Old_activeBlock = activeBlock;
	}

	_memcpy(data, &xml_data[addr * 2], length);

	return 0;
}

aic_stat_t e2p_config(e2p_t *e2p)
{
	if (e2p->config.erase_size == 0 || e2p->config.sector_cnt == 0) {
		e2p_err("config error erase_size = %u, sector_cnt = %u\n", e2p->config.erase_size, e2p->config.sector_cnt);
		return E2P_ERROR_INIT_ERR;
	}

	if (e2p->config.flash_read == NULL || e2p->config.flash_write == NULL || e2p->config.flash_erase == NULL) {
		e2p_err( "Not register operate function read = %p, write = %p, erase = %p",
				e2p->config.flash_read, e2p->config.flash_write, e2p->config.flash_erase);
		return E2P_ERROR_INIT_ERR;
	}

	if ((e2p->config.sector_cnt % 2) == 1) {
		e2p_err("Sector count must be even, %u sector now, maybe %u sector?",
				e2p->config.sector_cnt, e2p->config.sector_cnt + 1);
		return E2P_ERROR_INIT_ERR;
	}

	e2p_config_t *cfg = &e2p->config;
	e2p_block block;

	for (int i = 0; i < E2P_COUNT; i++) {
		u32 read_addr = cfg->start_addr + (E2P_EEPROM_SIZE_4K_UP_ALIGN * i);
		cfg->flash_read((uint8_t*) &block, read_addr, sizeof(e2p_block));
		_memcpy(&e2p_info_table[i], (uint8_t*) &block, sizeof(e2p_block));
	}

	e2p_block dummy_block;
	_memset(&dummy_block, 0xff, sizeof(e2p_block));
	for (int i = 0; i < E2P_COUNT; i++) {
		e2p_block *cur_block = &(e2p_info_table[i]);

		if ((cur_block->valid_state == e2p_earsed) && (_memcmp(&dummy_block, (u8*) &cur_block, sizeof(e2p_block)) != 0)) {
			if (cur_block->length > E2P_EEPROM_SIZE_4K_UP_ALIGN - sizeof(e2p_block)) {
				cur_block->length = E2P_EEPROM_SIZE_4K_UP_ALIGN - sizeof(e2p_block);
			}

			//如果是已经擦除过的数据，可能cur_block的地址不在范围中。
			if ((cur_block->block_addr < cfg->start_addr) || (cur_block->block_addr > cfg->start_addr + (cfg->sector_cnt * cfg->erase_size))) {
				e2p_info("bad block: block_id=0x%x, block_addr= 0x%x\n", cur_block->block_id, cur_block->block_addr);
				cur_block->block_addr = cfg->start_addr + (E2P_EEPROM_SIZE_4K_UP_ALIGN * i);
				cur_block->data_addr = cur_block->block_addr + sizeof(e2p_block);
			}

			cfg->flash_read((uint8_t*) xml_data, cur_block->data_addr, cur_block->length);
			for (u32 j = 0; j < cur_block->length; j++) {
				if (xml_data[j] != 0xff) {
					e2p_info("xml_data[%d](0x%x) != 0xff, erase[%d]: 0x%x\n", i, xml_data[i], i, cur_block->block_addr);
					cfg->flash_erase(cur_block->block_addr, E2P_EEPROM_SIZE_4K_UP_ALIGN);
					_memset(cur_block, 0xff, sizeof(e2p_block));
					break;
				}
			}
		} else {

			if ((cur_block->next_block_addr == 0xffffffff) && (cur_block->valid_state == e2p_valid)) {
				if (activeBlock == -1) {
					activeBlock = i;
				}
			} else {

				//如果是已经擦除过的数据，可能cur_block的地址不在范围中。
				if ((cur_block->block_addr < cfg->start_addr) || (cur_block->block_addr > cfg->start_addr + (cfg->sector_cnt * cfg->erase_size))) {
					e2p_info("bad block: block_id=0x%x, block_addr= 0x%x\n", cur_block->block_id, cur_block->block_addr);
					cur_block->block_addr = cfg->start_addr + (E2P_EEPROM_SIZE_4K_UP_ALIGN * i);
					cur_block->data_addr = cur_block->block_addr + sizeof(e2p_block);
				}
				e2p_info("erase[%d]: 0x%x\n", i, cur_block->block_addr);
				cfg->flash_erase(cur_block->block_addr, E2P_EEPROM_SIZE_4K_UP_ALIGN);
				_memset(cur_block, 0xff, sizeof(e2p_block));
			}
		}
	}

	if (activeBlock == -1) {
		e2p_block *cur_block = &e2p_info_table[0];
		cur_block->block_id = 0;
		cur_block->block_addr = cfg->start_addr;
		cur_block->data_addr = cfg->start_addr + sizeof(e2p_block);
		cur_block->length = E2P_EEPROM_SIZE_4K_UP_ALIGN - sizeof(e2p_block);
		cur_block->valid_state = e2p_valid;
		cfg->flash_write((uint8_t*) cur_block, cur_block->block_addr, sizeof(e2p_block));
		activeBlock = 0;
	}
	e2p_info("using: block_id=0x%x, block_addr=0x%x, length=0x%x\n", e2p_info_table[activeBlock].block_id, e2p_info_table[activeBlock].block_addr, e2p_info_table[activeBlock].length+sizeof(e2p_block));

	Old_activeBlock = -1;
	e2p_valid_ctx = e2p;
	//e2p_print_info(e2p);

	return E2P_STATUS_OK;
}
void e2p_clear(void)
{
	e2p_config_t *cfg = &e2p_valid_ctx->config;

	E2P_CRITICAL_ENTER();
	cfg->flash_erase(cfg->start_addr, cfg->sector_cnt * cfg->erase_size);
	E2P_CRITICAL_EXIT();
}

void e2p_show_info(void)
{
	e2p_print_info(e2p_valid_ctx);
}

void e2p_enter_critical(void)
{
	e907_irq_disable();
}

void e2p_exit_critical(void)
{
	e907_irq_enable();
}


