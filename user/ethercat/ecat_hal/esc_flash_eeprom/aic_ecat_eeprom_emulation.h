/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _EEPROM_EMULATION_H
#define _EEPROM_EMULATION_H

#include <stdint.h>
#include "all_inc.h"
#include "ecat_def.h"
#include "aic_ecat_cfg.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t aic_stat_t;

#define E2P_DEBUG_LEVEL_TRACE (0)
#define E2P_DEBUG_LEVEL_INFO  (1)
#define E2P_DEBUG_LEVEL_WARN  (2)
#define E2P_DEBUG_LEVEL_ERROR (3)

#define E2P_DEBUG_LEVEL   E2P_DEBUG_LEVEL_ERROR


#ifndef E2P_DEBUG_TRACE
#   if E2P_DEBUG_LEVEL <= E2P_DEBUG_LEVEL_TRACE
#       define E2P_TRACE(fmt, ...) printk("%s: %d: debug: "fmt"%s\n", __func__, __LINE__, __VA_ARGS__)
#       define e2p_trace(...) E2P_TRACE(__VA_ARGS__, "")
#   else
#       define e2p_trace(...)
#   endif
#endif

#ifndef E2P_DEBUG_INFO
#   if E2P_DEBUG_LEVEL <= E2P_DEBUG_LEVEL_INFO
#       define E2P_INFO(fmt, ...) printk(""fmt"%s\n", __VA_ARGS__)
#       define e2p_info(...) E2P_INFO(__VA_ARGS__, "")
#   else
#       define e2p_info(...)
#   endif
#endif

#ifndef E2P_DEBUG_WARN
#   if E2P_DEBUG_LEVEL <= E2P_DEBUG_LEVEL_WARN
#       define E2P_WARN(fmt, ...) printk(""fmt"%s\n", __VA_ARGS__)
#       define e2p_warn(...) E2P_WARN(__VA_ARGS__, "")
#   else
#       define e2p_warn(...)
#   endif
#endif

#ifndef E2P_DEBUG_ERROR
#   if E2P_DEBUG_LEVEL <= E2P_DEBUG_LEVEL_ERROR
#       define E2P_ERR(fmt, ...) printk(""fmt"%s\n", __VA_ARGS__)
#       define e2p_err(...) E2P_ERR(__VA_ARGS__, "")
#   else
#       define e2p_err(...)
#   endif
#endif

typedef enum {
    e2p_invalid = 0xCCCC,
    e2p_valid = 0xEEEE,
    e2p_earsed = 0xFFFF,
} e2p_valid_state;

enum {
    E2P_STATUS_OK = 0,
    E2P_ERROR,
    E2P_ERROR_NO_MEM,
    E2P_ERROR_INIT_ERR,
    E2P_ERROR_BAD_ID,
    E2P_ERROR_BAD_ADDR,
    E2P_ERROR_MUL_VAR,
};

#pragma pack(push, 1)
typedef struct {
    uint32_t block_id;
    uint32_t block_addr;
    uint32_t data_addr;
    uint16_t length;
    uint16_t valid_state;
    uint32_t last_block_addr;
    uint32_t next_block_addr;
    uint32_t crc;
} e2p_block;
#pragma pack(pop)

typedef struct {
    uint32_t start_addr;
    uint32_t sector_cnt;
    uint16_t erase_size;
    uint32_t version;

    uint32_t (*flash_read)(uint8_t *buf, uint32_t addr, uint32_t size);
    uint32_t (*flash_write)(uint8_t *buf, uint32_t addr, uint32_t size);
    void (*flash_erase)(uint32_t start_addr, uint32_t size);
} e2p_config_t;


typedef struct {
    e2p_config_t config;
} e2p_t;

#include <flash_drv.h>
extern partition_info_t partition_info;
//#define EE_FLASH_BASE	(ESCXML_PART_FLASH_OFFSET)
//#define EE_FLASH_END	(ESCXML_PART_FLASH_OFFSET + ESCXML_PART_SIZE)
//#define FLASH_EEPROM_SIZE (ESCXML_PART_SIZE)

#define ALIGN_UP(size, align) (((size) + ((align) - 1)) & ~((align) - 1))
#define E2P_EEPROM_SIZE_4K_UP_ALIGN ALIGN_UP(ESC_EEPROM_SIZE, 4096) //基于ESC_EEPROM_SIZE 4K向上对齐

//#define EE_FLASH_BASE	(partition_info.part[ESCXML].start)
//#define EE_FLASH_END	(partition_info.part[ESCXML].start + partition_info.part[ESCXML].size)
//#define FLASH_EEPROM_SIZE (partition_info.part[ESCXML].size)
#define FLASH_EARSE_SIZE 4096
//#define E2P_COUNT (FLASH_EEPROM_SIZE / E2P_EEPROM_SIZE_4K_UP_ALIGN)

extern u32 E2P_COUNT;

#define E2P_MAGIC_ID (0x41494345)       /*'A' 'I' 'C' 'E'*/

#define E2P_VALID_STATE     (0xFFFFFFF0)
#define E2P_EARSED_ID       (0xFFFFFFFF)
#define E2P_EARSED_VAR      (0xFF)

#define E2P_FLUSH_TRY       (0)
#define E2P_FLUSH_BEGIN     (1)
#define E2P_CRITICAL_ENTER()   e2p_enter_critical()
#define E2P_CRITICAL_EXIT()    e2p_exit_critical()


void e2p_enter_critical(void);
void e2p_exit_critical(void);

/**
 * @brief eeprom emulation write
 *
 * @param block_id custom id
 * @param length data length
 * @param data
 * @return aic_stat_t
 */
aic_stat_t e2p_write(u32 addr, uint8_t *data, uint16_t length);

/**
 * @brief eeprom emulation read
 * 
 * @param block_id custom id
 * @param length data length
 * @param data 
 * @return aic_stat_t
 */
aic_stat_t e2p_read(u32 addr, uint8_t *data, uint16_t length);

/**
 * @brief format whole area, 0xFF
 */
void e2p_clear(void);

/**
 * @brief show e2p instance info include config info and store info
 */
void e2p_show_info(void);


#ifdef __cplusplus
}
#endif

#endif
