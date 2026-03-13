/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_COMMON_IO_H_
#define INCLUDE_COMMON_IO_H_

#include <common_type.h>

#define readb(addr)		(*((volatile u8  *)((uaddr)addr)))
#define readw(addr)		(*((volatile u16 *)((uaddr)addr)))
#define readl(addr)		(*((volatile u32 *)((uaddr)addr)))
#define writeb(v, addr)		(*((volatile u8  *)((uaddr)addr)) = (u8)(v))
#define writew(v, addr)		(*((volatile u16 *)((uaddr)addr)) = (u16)(v))
#define writel(v, addr)		(*((volatile u32 *)((uaddr)addr)) = (u32)(v))
#define wrbit(m, v, addr)	(*((volatile u32 *)((uaddr)addr)) = ((*((volatile u32  *)((uaddr)addr)) & (~(u32)(m))) | (u32)(v)))
#define sbit(v, addr)		(*((volatile u32 *)((uaddr)addr)) |=  (u32)(v))
#define cbit(v, addr)		(*((volatile u32 *)((uaddr)addr)) &= ~(u32)(v))

#define __io_br()		do {} while (0)
#define __io_ar(v)		__asm__ __volatile__ ("fence i,r" : : : "memory")
#define __io_bw()		__asm__ __volatile__ ("fence w,o" : : : "memory")
#define __io_aw()		do {} while (0)

#define rmb()			__io_ar()
#define wmb()			__io_bw()


#endif /* INCLUDE_COMMON_IO_H_ */
