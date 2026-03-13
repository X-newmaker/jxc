/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_COMMON_PRT_H_
#define INCLUDE_COMMON_PRT_H_

#include <common_type.h>

typedef struct dig_string_s{
        char buf[5];
        u32 bit_num;
} dig_string_t;

s32 printk(const char *fmt, ...);
dig_string_t dig_print(const char *fmt, ...);
#endif /* INCLUDE_COMMON_PRT_H_ */
