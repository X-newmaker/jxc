/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */

#ifndef _HAL_EFUSE_H__
#define _HAL_EFUSE_H__


int hal_efuse_init(void);
int hal_efuse_deinit(void);
int hal_efuse_wait_ready(void);
int hal_efuse_read(u32 wid, u32 *wval);
int hal_efuse_write(u32 wid, u32 wval);


#endif
