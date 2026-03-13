/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_COMMON_TYPE_H_
#define INCLUDE_COMMON_TYPE_H_

typedef signed 		char		s8;
typedef unsigned 	char       	u8;
typedef signed 		short		s16;
typedef unsigned 	short		u16;
typedef signed 		int		s32;
typedef unsigned 	int		u32;
typedef signed 		long long	s64;
typedef unsigned 	long long	u64;


typedef unsigned 	int 		uaddr;

typedef enum com_ret_e  {RET_FALSE  =-1,    RET_OK  = 0    }  com_ret_t ;
typedef enum com_ist_e  {IST_NON    = 0,    IST_YES = 1    }  com_ist_t ;
typedef enum cpu_mode_e {CPU_MODE_M = 0,    CPU_MODE_S  = 1}  cpu_mode_t;
typedef enum ddr_type_e {DDR_TYPE_D2= 0,    DDR_TYPE_D3 = 1}  ddr_type_t;
typedef enum psram_type_e {PSRAM_TYPE_HYPERBUS= 0,    PSRAM_TYPE_OPI = 1,    PSRAM_TYPE_XCCELA = 2}  psram_type_t;
typedef enum psram_num_e {PSRAM_NUM_DUAL= 0,    PSRAM_NUM_SINGLE = 1    }  psram_num_t;


typedef enum dma_type_e
{
	DMA_TYPE_DMA0	= 0,
	DMA_TYPE_DMA1   = 1,
	DMA_TYPE_DMA2   = 2,
	DMA_TYPE_DMA3   = 3,
	DMA_TYPE_DMA4	= 4,
	DMA_TYPE_DMA5   = 5,
	DMA_TYPE_DMA6   = 6,
	DMA_TYPE_DEFAULT  = 7,
}dma_type_t;

#define PACKED_ATTR __attribute__((packed,aligned(1)))

#ifndef NULL
#define NULL (void *)0
#endif

#endif /* INCLUDE_COMMON_TYPE_H_ */
