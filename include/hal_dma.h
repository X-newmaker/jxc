/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_DMA_H_
#define INCLUDE_HAL_DMA_H_

#include <all_inc.h>

#define DMA_NOCACHE_RAM_SECTION __attribute__((section(".ucm_data")))

#define DMA_CH_NUM		8

#define DMA_CH0_ALL_FINISH      0x00000004
#define DMA_CH1_ALL_FINISH      0x00000400
#define DMA_CH2_ALL_FINISH      0x00040000
#define DMA_CH3_ALL_FINISH      0x04000000
#define DMA_CH4_ALL_FINISH      0x00000004
#define DMA_CH5_ALL_FINISH      0x00000400
#define DMA_CH6_ALL_FINISH      0x00040000
#define DMA_CH7_ALL_FINISH      0x04000000
#define DBG_SIGNAL_EN 	1


typedef enum dma_device_id {
	DMA_ID_SRAM         =  0   ,
	DMA_ID_CS_CANFD0    =  4   ,
	DMA_ID_CS_CANFD1    =  5   ,
	DMA_ID_CS_PBUS      =  6   ,
	DMA_ID_CS_CAN       =  7   ,
	DMA_ID_CS_SPI0      =  8   ,
	DMA_ID_CS_SPI1      =  9   ,
	DMA_ID_CS_SPI2      =  10  ,
	DMA_ID_CS_SPI3      =  11  ,
	DMA_ID_CS_SPI4      =  12  ,
	DMA_ID_CS_SPI5      =  13  ,
	DMA_ID_CS_UART0     =  16  ,
	DMA_ID_CS_UART1     =  17  ,
	DMA_ID_CS_UART2     =  18  ,
	DMA_ID_CS_UART3     =  19  ,
	DMA_ID_CS_UART4     =  20  ,
	DMA_ID_CS_UART5     =  21  ,
	DMA_ID_CS_UART6     =  22  ,
	DMA_ID_CS_UART7     =  23  ,
	DMA_ID_CS_UART8     =  24  ,
	DMA_ID_CS_ADC0Q1    =  32  ,
	DMA_ID_CS_ADC0Q2    =  33  ,
	DMA_ID_CS_ADC1Q1    =  34  ,
	DMA_ID_CS_ADC1Q2    =  35  ,
	DMA_ID_CS_SDFM0     =  36  ,
	DMA_ID_CS_SDFM1     =  37  ,
	DMA_ID_CS_SDFM2     =  38  ,
	DMA_ID_CS_SDFM3     =  39  ,
	DMA_ID_CS_EPWM0     =  42  ,
	DMA_ID_CS_EPWM1     =  43  ,
	DMA_ID_CS_EPWM2     =  44  ,
	DMA_ID_CS_EPWM3     =  45  ,
	DMA_ID_CS_EPWM4     =  46  ,
	DMA_ID_CS_EPWM5     =  47  ,
	DMA_ID_CS_EPWM6     =  48  ,
	DMA_ID_CS_EPWM7     =  49  ,
	DMA_ID_CS_EPWM8     =  50  ,
	DMA_ID_CS_EPWM9     =  51  ,
	DMA_ID_CS_EPWM10    =  52  ,
	DMA_ID_CS_EPWM11    =  53  ,
	DMA_ID_CS_I2C0      =  72  ,
	DMA_ID_CS_I2C1      =  73  ,
	DMA_ID_CS_I2C2      =  74  ,
	DMA_ID_CS_I2C3      =  75  ,
	DMA_ID_CS_PWM0      =  80  ,
	DMA_ID_CS_PWM1      =  81  ,
	DMA_ID_CS_PWM2      =  82  ,
	DMA_ID_CS_PWM3      =  83  ,
	DMA_ID_CS_PWM4      =  84  ,
	DMA_ID_CS_PWM5      =  85  ,
	DMA_ID_CS_TAIF0     =  94  ,
	DMA_ID_CS_TAIF1     =  95  ,
	DMA_ID_CS_ESC       =  98  ,
	DMA_ID_CS_CAP0      =  110 ,
	DMA_ID_CS_CAP1      =  111 ,
	DMA_ID_CS_CAP2      =  112 ,
	DMA_ID_CS_CAP3      =  113 ,
	DMA_ID_CS_CAP4      =  114 ,
	DMA_ID_CS_CAP5      =  115 ,

}dma_device_id_p;


typedef enum dma_task_cfg1 {
	DMA_W08_IOS_BLK01	=0x0,
	DMA_W08_IOS_BLK04	=0x1,
	DMA_W08_IOS_BLK08	=0x2,
	DMA_W08_IOS_BLK16	=0x3,
	DMA_W08_IOB_BLK01	=0x4,
	DMA_W08_IOB_BLK04	=0x5,
	DMA_W08_IOB_BLK08	=0x6,
	DMA_W08_IOB_BLK16	=0x7,
	DMA_W08_MEM_BLK01	=0x48,
	DMA_W08_MEM_BLK04	=0x49,
	DMA_W08_MEM_BLK08	=0x4A,
	DMA_W08_MEM_BLK16	=0x4B,
	DMA_W08_MST_BLK01	=0x4C,
	DMA_W08_MST_BLK04	=0x4D,
	DMA_W08_MST_BLK08	=0x4E,
	DMA_W08_MST_BLK16	=0x4F,
	DMA_W08_IOF_BLK01	=0x10,
	DMA_W08_IOF_BLK04	=0x11,
	DMA_W08_IOF_BLK08	=0x12,
	DMA_W08_IOF_BLK16	=0x13,

	DMA_W016_IOS_BLK01	=0x20,
	DMA_W016_IOS_BLK04	=0x21,
	DMA_W016_IOS_BLK08	=0x22,
	DMA_W016_IOS_BLK16	=0x23,
	DMA_W016_IOB_BLK01	=0x24,
	DMA_W016_IOB_BLK04	=0x25,
	DMA_W016_IOB_BLK08	=0x26,
	DMA_W016_IOB_BLK16	=0x27,
	DMA_W016_MEM_BLK01	=0x48,
	DMA_W016_MEM_BLK04	=0x49,
	DMA_W016_MEM_BLK08	=0x4A,
	DMA_W016_MEM_BLK16	=0x4B,
	DMA_W016_MST_BLK01	=0x4C,
	DMA_W016_MST_BLK04	=0x4D,
	DMA_W016_MST_BLK08	=0x4E,
	DMA_W016_MST_BLK16	=0x4F,
	DMA_W016_IOF_BLK01	=0x30,
	DMA_W016_IOF_BLK04	=0x31,
	DMA_W016_IOF_BLK08	=0x32,
	DMA_W016_IOF_BLK16	=0x33,


	DMA_W32_IOS_BLK01	=0x40,
	DMA_W32_IOS_BLK04	=0x41,
	DMA_W32_IOS_BLK08	=0x42,
	DMA_W32_IOS_BLK16	=0x43,
	DMA_W32_IOB_BLK01	=0x44,
	DMA_W32_IOB_BLK04	=0x45,
	DMA_W32_IOB_BLK08	=0x46,
	DMA_W32_IOB_BLK16	=0x47,
	DMA_W32_MEM_BLK01	=0x48,
	DMA_W32_MEM_BLK04	=0x49,
	DMA_W32_MEM_BLK08	=0x4A,
	DMA_W32_MEM_BLK16	=0x4B,
	DMA_W32_MST_BLK01	=0x4C,
	DMA_W32_MST_BLK04	=0x4D,
	DMA_W32_MST_BLK08	=0x4E,
	DMA_W32_MST_BLK16	=0x4F,
	DMA_W32_IOF_BLK01	=0x50,
	DMA_W32_IOF_BLK04	=0x51,
	DMA_W32_IOF_BLK08	=0x52,
	DMA_W32_IOF_BLK16	=0x53,

	DMA_W64_IOS_BLK01	=0x60,
	DMA_W64_IOS_BLK04	=0x61,
	DMA_W64_IOS_BLK08	=0x62,
	DMA_W64_IOS_BLK16	=0x63,
	DMA_W64_IOB_BLK01	=0x64,
	DMA_W64_IOB_BLK04	=0x65,
	DMA_W64_IOB_BLK08	=0x66,
	DMA_W64_IOB_BLK16	=0x67,
	DMA_W64_MEM_BLK01	=0x48,
	DMA_W64_MEM_BLK04	=0x49,
	DMA_W64_MEM_BLK08	=0x4A,
	DMA_W64_MEM_BLK16	=0x4B,
	DMA_W64_MST_BLK01	=0x4C,
	DMA_W64_MST_BLK04	=0x4D,
	DMA_W64_MST_BLK08	=0x4E,
	DMA_W64_MST_BLK16	=0x4F,
	DMA_W64_IOF_BLK01	=0x70,
	DMA_W64_IOF_BLK04	=0x71,
	DMA_W64_IOF_BLK08	=0x72,
	DMA_W64_IOF_BLK16	=0x73,

	DMA_W128_IOS_BLK01	=0x80,
	DMA_W128_IOS_BLK04	=0x81,
	DMA_W128_IOS_BLK08	=0x82,
	DMA_W128_IOS_BLK16	=0x83,
	DMA_W128_IOB_BLK01	=0x84,
	DMA_W128_IOB_BLK04	=0x85,
	DMA_W128_IOB_BLK08	=0x86,
	DMA_W128_IOB_BLK16	=0x87,
	DMA_W128_MEM_BLK01	=0x48,
	DMA_W128_MEM_BLK04	=0x49,
	DMA_W128_MEM_BLK08	=0x4A,
	DMA_W128_MEM_BLK16	=0x4B,
	DMA_W128_MST_BLK01	=0x4C,
	DMA_W128_MST_BLK04	=0x4D,
	DMA_W128_MST_BLK08	=0x4E,
	DMA_W128_MST_BLK16	=0x4F,
	DMA_W128_IOF_BLK01	=0x90,
	DMA_W128_IOF_BLK04	=0x91,
	DMA_W128_IOF_BLK08	=0x92,
	DMA_W128_IOF_BLK16	=0x93,
}dma_task_cfg1_p;


union  dma_irq_en_1_u  	{
	u32 dwval;
	struct {
	u32 ch0_htask_irq_en 	  :   1;
	u32 ch0_task_irq_en  	  :   1;
	u32 ch0_link_irq_en  	  :   1;
	u32 ch0_error_irq_en 	  :   1;
	u32 ch0_ahbrd_illegal_en  :   1;
	u32 ch0_ahbwt_illegal_en  :   1;
	u32 ch0_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch1_htask_irq_en 	  :   1;
	u32 ch1_task_irq_en  	  :   1;
	u32 ch1_link_irq_en  	  :   1;
	u32 ch1_error_irq_en 	  :   1;
	u32 ch1_ahbrd_illegal_en  :   1;
	u32 ch1_ahbwt_illegal_en  :   1;
	u32 ch1_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch2_htask_irq_en 	  :   1;
	u32 ch2_task_irq_en  	  :   1;
	u32 ch2_link_irq_en  	  :   1;
	u32 ch2_error_irq_en 	  :   1;
	u32 ch2_ahbrd_illegal_en  :   1;
	u32 ch2_ahbwt_illegal_en  :   1;
	u32 ch2_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch3_htask_irq_en 	  :   1;
	u32 ch3_task_irq_en  	  :   1;
	u32 ch3_link_irq_en  	  :   1;
	u32 ch3_error_irq_en 	  :   1;
	u32 ch3_ahbrd_illegal_en  :   1;
	u32 ch3_ahbwt_illegal_en  :   1;
	u32 ch3_axiwt_illegal_en  :   1;
	u32 			  :   1;
	}bits;
};

union  dma_irq_en_2_u  	{
	u32 dwval;
	struct {
	u32 ch4_htask_irq_en 	  :   1;
	u32 ch4_task_irq_en  	  :   1;
	u32 ch4_link_irq_en  	  :   1;
	u32 ch4_error_irq_en 	  :   1;
	u32 ch4_ahbrd_illegal_en  :   1;
	u32 ch4_ahbwt_illegal_en  :   1;
	u32 ch4_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch5_htask_irq_en 	  :   1;
	u32 ch5_task_irq_en  	  :   1;
	u32 ch5_link_irq_en  	  :   1;
	u32 ch5_error_irq_en 	  :   1;
	u32 ch5_ahbrd_illegal_en  :   1;
	u32 ch5_ahbwt_illegal_en  :   1;
	u32 ch5_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch6_htask_irq_en 	  :   1;
	u32 ch6_task_irq_en  	  :   1;
	u32 ch6_link_irq_en  	  :   1;
	u32 ch6_error_irq_en 	  :   1;
	u32 ch6_ahbrd_illegal_en  :   1;
	u32 ch6_ahbwt_illegal_en  :   1;
	u32 ch6_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch7_htask_irq_en 	  :   1;
	u32 ch7_task_irq_en  	  :   1;
	u32 ch7_link_irq_en  	  :   1;
	u32 ch7_error_irq_en 	  :   1;
	u32 ch7_ahbrd_illegal_en  :   1;
	u32 ch7_ahbwt_illegal_en  :   1;
	u32 ch7_axiwt_illegal_en  :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_en_3_u  	{
	u32 dwval;
	struct {
	u32 ch8_htask_irq_en 	  :   1;
	u32 ch8_task_irq_en  	  :   1;
	u32 ch8_link_irq_en  	  :   1;
	u32 ch8_error_irq_en 	  :   1;
	u32 ch8_ahbrd_illegal_en  :   1;
	u32 ch8_ahbwt_illegal_en  :   1;
	u32 ch8_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch9_htask_irq_en 	  :   1;
	u32 ch9_task_irq_en  	  :   1;
	u32 ch9_link_irq_en  	  :   1;
	u32 ch9_error_irq_en 	  :   1;
	u32 ch9_ahbrd_illegal_en  :   1;
	u32 ch9_ahbwt_illegal_en  :   1;
	u32 ch9_axiwt_illegal_en  :   1;
	u32 			  :   1;
	u32 ch10_htask_irq_en 	  :   1;
	u32 ch10_task_irq_en  	  :   1;
	u32 ch10_link_irq_en  	  :   1;
	u32 ch10_error_irq_en 	  :   1;
	u32 ch10_ahbrd_illegal_en :   1;
	u32 ch10_ahbwt_illegal_en :   1;
	u32 ch10_axiwt_illegal_en :   1;
	u32 			  :   1;
	u32 ch11_htask_irq_en 	  :   1;
	u32 ch11_task_irq_en  	  :   1;
	u32 ch11_link_irq_en  	  :   1;
	u32 ch11_error_irq_en 	  :   1;
	u32 ch11_ahbrd_illegal_en :   1;
	u32 ch11_ahbwt_illegal_en :   1;
	u32 ch11_axiwt_illegal_en :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_en_4_u  	{
	u32 dwval;
	struct {
	u32 ch12_htask_irq_en 	  :   1;
	u32 ch12_task_irq_en  	  :   1;
	u32 ch12_link_irq_en  	  :   1;
	u32 ch12_error_irq_en 	  :   1;
	u32 ch12_ahbrd_illegal_en :   1;
	u32 ch12_ahbwt_illegal_en :   1;
	u32 ch12_axiwt_illegal_en :   1;
	u32 			  :   1;
	u32 ch13_htask_irq_en 	  :   1;
	u32 ch13_task_irq_en  	  :   1;
	u32 ch13_link_irq_en  	  :   1;
	u32 ch13_error_irq_en 	  :   1;
	u32 ch13_ahbrd_illegal_en :   1;
	u32 ch13_ahbwt_illegal_en :   1;
	u32 ch13_axiwt_illegal_en :   1;
	u32 			  :   1;
	u32 ch14_htask_irq_en 	  :   1;
	u32 ch14_task_irq_en  	  :   1;
	u32 ch14_link_irq_en  	  :   1;
	u32 ch14_error_irq_en 	  :   1;
	u32 ch14_ahbrd_illegal_en :   1;
	u32 ch14_ahbwt_illegal_en :   1;
	u32 ch14_axiwt_illegal_en :   1;
	u32 			  :   1;
	u32 ch15_htask_irq_en 	  :   1;
	u32 ch15_task_irq_en  	  :   1;
	u32 ch15_link_irq_en  	  :   1;
	u32 ch15_error_irq_en 	  :   1;
	u32 ch15_ahbrd_illegal_en :   1;
	u32 ch15_ahbwt_illegal_en :   1;
	u32 ch15_axiwt_illegal_en :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_clr_1_u  	{
	u32 dwval;
	struct {
	u32 ch0_htask_irq_clr 	  :   1;
	u32 ch0_task_irq_clr  	  :   1;
	u32 ch0_link_irq_clr  	  :   1;
	u32 ch0_error_irq_clr 	  :   1;
	u32 ch0_ahbrd_illegal_clr :   1;
	u32 ch0_ahbwt_illegal_clr :   1;
	u32 ch0_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch1_htask_irq_clr 	  :   1;
	u32 ch1_task_irq_clr  	  :   1;
	u32 ch1_link_irq_clr  	  :   1;
	u32 ch1_error_irq_clr 	  :   1;
	u32 ch1_ahbrd_illegal_clr :   1;
	u32 ch1_ahbwt_illegal_clr :   1;
	u32 ch1_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch2_htask_irq_clr 	  :   1;
	u32 ch2_task_irq_clr  	  :   1;
	u32 ch2_link_irq_clr  	  :   1;
	u32 ch2_error_irq_clr 	  :   1;
	u32 ch2_ahbrd_illegal_clr :   1;
	u32 ch2_ahbwt_illegal_clr :   1;
	u32 ch2_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch3_htask_irq_clr 	  :   1;
	u32 ch3_task_irq_clr  	  :   1;
	u32 ch3_link_irq_clr  	  :   1;
	u32 ch3_error_irq_clr 	  :   1;
	u32 ch3_ahbrd_illegal_clr :   1;
	u32 ch3_ahbwt_illegal_clr :   1;
	u32 ch3_axiwt_illegal_clr :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_clr_2_u  	{
	u32 dwval;
	struct {
	u32 ch4_htask_irq_clr 	  :   1;
	u32 ch4_task_irq_clr  	  :   1;
	u32 ch4_link_irq_clr  	  :   1;
	u32 ch4_error_irq_clr 	  :   1;
	u32 ch4_ahbrd_illegal_clr :   1;
	u32 ch4_ahbwt_illegal_clr :   1;
	u32 ch4_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch5_htask_irq_clr 	  :   1;
	u32 ch5_task_irq_clr  	  :   1;
	u32 ch5_link_irq_clr  	  :   1;
	u32 ch5_error_irq_clr 	  :   1;
	u32 ch5_ahbrd_illegal_clr :   1;
	u32 ch5_ahbwt_illegal_clr :   1;
	u32 ch5_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch6_htask_irq_clr 	  :   1;
	u32 ch6_task_irq_clr  	  :   1;
	u32 ch6_link_irq_clr  	  :   1;
	u32 ch6_error_irq_clr 	  :   1;
	u32 ch6_ahbrd_illegal_clr :   1;
	u32 ch6_ahbwt_illegal_clr :   1;
	u32 ch6_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch7_htask_irq_clr 	  :   1;
	u32 ch7_task_irq_clr  	  :   1;
	u32 ch7_link_irq_clr  	  :   1;
	u32 ch7_error_irq_clr 	  :   1;
	u32 ch7_ahbrd_illegal_clr :   1;
	u32 ch7_ahbwt_illegal_clr :   1;
	u32 ch7_axiwt_illegal_clr :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_clr_3_u  	{
	u32 dwval;
	struct {
	u32 ch8_htask_irq_clr 	  :   1;
	u32 ch8_task_irq_clr  	  :   1;
	u32 ch8_link_irq_clr  	  :   1;
	u32 ch8_error_irq_clr 	  :   1;
	u32 ch8_ahbrd_illegal_clr :   1;
	u32 ch8_ahbwt_illegal_clr :   1;
	u32 ch8_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch9_htask_irq_clr 	  :   1;
	u32 ch9_task_irq_clr  	  :   1;
	u32 ch9_link_irq_clr  	  :   1;
	u32 ch9_error_irq_clr 	  :   1;
	u32 ch9_ahbrd_illegal_clr :   1;
	u32 ch9_ahbwt_illegal_clr :   1;
	u32 ch9_axiwt_illegal_clr :   1;
	u32 			  :   1;
	u32 ch10_htask_irq_clr 	  :   1;
	u32 ch10_task_irq_clr  	  :   1;
	u32 ch10_link_irq_clr  	  :   1;
	u32 ch10_error_irq_clr 	  :   1;
	u32 ch10_ahbrd_illegal_clr:   1;
	u32 ch10_ahbwt_illegal_clr:   1;
	u32 ch10_axiwt_illegal_clr:   1;
	u32 			  :   1;
	u32 ch11_htask_irq_clr 	  :   1;
	u32 ch11_task_irq_clr  	  :   1;
	u32 ch11_link_irq_clr  	  :   1;
	u32 ch11_error_irq_clr 	  :   1;
	u32 ch11_ahbrd_illegal_clr:   1;
	u32 ch11_ahbwt_illegal_clr:   1;
	u32 ch11_axiwt_illegal_clr:   1;
	u32 			  :   1;

	}bits;
};


union  dma_irq_clr_4_u  	{
	u32 dwval;
	struct {
	u32 ch12_htask_irq_clr 	  :   1;
	u32 ch12_task_irq_clr  	  :   1;
	u32 ch12_link_irq_clr  	  :   1;
	u32 ch12_error_irq_clr 	  :   1;
	u32 ch12_ahbrd_illegal_clr:   1;
	u32 ch12_ahbwt_illegal_clr:   1;
	u32 ch12_axiwt_illegal_clr:   1;
	u32 			  :   1;
	u32 ch13_htask_irq_clr 	  :   1;
	u32 ch13_task_irq_clr  	  :   1;
	u32 ch13_link_irq_clr  	  :   1;
	u32 ch13_error_irq_clr 	  :   1;
	u32 ch13_ahbrd_illegal_clr:   1;
	u32 ch13_ahbwt_illegal_clr:   1;
	u32 ch13_axiwt_illegal_clr:   1;
	u32 			  :   1;
	u32 ch14_htask_irq_clr 	  :   1;
	u32 ch14_task_irq_clr  	  :   1;
	u32 ch14_link_irq_clr  	  :   1;
	u32 ch14_error_irq_clr 	  :   1;
	u32 ch14_ahbrd_illegal_clr:   1;
	u32 ch14_ahbwt_illegal_clr:   1;
	u32 ch14_axiwt_illegal_clr:   1;
	u32 			  :   1;
	u32 ch15_htask_irq_clr 	  :   1;
	u32 ch15_task_irq_clr  	  :   1;
	u32 ch15_link_irq_clr  	  :   1;
	u32 ch15_error_irq_clr 	  :   1;
	u32 ch15_ahbrd_illegal_clr:   1;
	u32 ch15_ahbwt_illegal_clr:   1;
	u32 ch15_axiwt_illegal_clr:   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_sta_1_u  	{
	u32 dwval;
	struct {
	u32 ch0_htask_irq_sta 	  :   1;
	u32 ch0_task_irq_sta  	  :   1;
	u32 ch0_link_irq_sta  	  :   1;
	u32 ch0_error_irq_sta 	  :   1;
	u32 ch0_ahbrd_illegal_sta :   1;
	u32 ch0_ahbwt_illegal_sta :   1;
	u32 ch0_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch1_htask_irq_sta 	  :   1;
	u32 ch1_task_irq_sta  	  :   1;
	u32 ch1_link_irq_sta  	  :   1;
	u32 ch1_error_irq_sta 	  :   1;
	u32 ch1_ahbrd_illegal_sta :   1;
	u32 ch1_ahbwt_illegal_sta :   1;
	u32 ch1_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch2_htask_irq_sta 	  :   1;
	u32 ch2_task_irq_sta  	  :   1;
	u32 ch2_link_irq_sta  	  :   1;
	u32 ch2_error_irq_sta 	  :   1;
	u32 ch2_ahbrd_illegal_sta :   1;
	u32 ch2_ahbwt_illegal_sta :   1;
	u32 ch2_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch3_htask_irq_sta 	  :   1;
	u32 ch3_task_irq_sta  	  :   1;
	u32 ch3_link_irq_sta  	  :   1;
	u32 ch3_error_irq_sta 	  :   1;
	u32 ch3_ahbrd_illegal_sta :   1;
	u32 ch3_ahbwt_illegal_sta :   1;
	u32 ch3_axiwt_illegal_sta :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_sta_2_u  	{
	u32 dwval;
	struct {
	u32 ch4_htask_irq_sta 	  :   1;
	u32 ch4_task_irq_sta  	  :   1;
	u32 ch4_link_irq_sta  	  :   1;
	u32 ch4_error_irq_sta 	  :   1;
	u32 ch4_ahbrd_illegal_sta :   1;
	u32 ch4_ahbwt_illegal_sta :   1;
	u32 ch4_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch5_htask_irq_sta 	  :   1;
	u32 ch5_task_irq_sta  	  :   1;
	u32 ch5_link_irq_sta  	  :   1;
	u32 ch5_error_irq_sta 	  :   1;
	u32 ch5_ahbrd_illegal_sta :   1;
	u32 ch5_ahbwt_illegal_sta :   1;
	u32 ch5_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch6_htask_irq_sta 	  :   1;
	u32 ch6_task_irq_sta  	  :   1;
	u32 ch6_link_irq_sta  	  :   1;
	u32 ch6_error_irq_sta 	  :   1;
	u32 ch6_ahbrd_illegal_sta :   1;
	u32 ch6_ahbwt_illegal_sta :   1;
	u32 ch6_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch7_htask_irq_sta 	  :   1;
	u32 ch7_task_irq_sta  	  :   1;
	u32 ch7_link_irq_sta  	  :   1;
	u32 ch7_error_irq_sta 	  :   1;
	u32 ch7_ahbrd_illegal_sta :   1;
	u32 ch7_ahbwt_illegal_sta :   1;
	u32 ch7_axiwt_illegal_sta :   1;
	u32 			  :   1;

	}bits;
};

union  dma_irq_sta_3_u  	{
	u32 dwval;
	struct {
	u32 ch8_htask_irq_sta 	  :   1;
	u32 ch8_task_irq_sta  	  :   1;
	u32 ch8_link_irq_sta  	  :   1;
	u32 ch8_error_irq_sta 	  :   1;
	u32 ch8_ahbrd_illegal_sta :   1;
	u32 ch8_ahbwt_illegal_sta :   1;
	u32 ch8_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch9_htask_irq_sta 	  :   1;
	u32 ch9_task_irq_sta  	  :   1;
	u32 ch9_link_irq_sta  	  :   1;
	u32 ch9_error_irq_sta 	  :   1;
	u32 ch9_ahbrd_illegal_sta :   1;
	u32 ch9_ahbwt_illegal_sta :   1;
	u32 ch9_axiwt_illegal_sta :   1;
	u32 			  :   1;
	u32 ch10_htask_irq_sta 	  :   1;
	u32 ch10_task_irq_sta  	  :   1;
	u32 ch10_link_irq_sta  	  :   1;
	u32 ch10_error_irq_sta 	  :   1;
	u32 ch10_ahbrd_illegal_sta:   1;
	u32 ch10_ahbwt_illegal_sta:   1;
	u32 ch10_axiwt_illegal_sta:   1;
	u32 			  :   1;
	u32 ch11_htask_irq_sta 	  :   1;
	u32 ch11_task_irq_sta  	  :   1;
	u32 ch11_link_irq_sta  	  :   1;
	u32 ch11_error_irq_sta 	  :   1;
	u32 ch11_ahbrd_illegal_sta:   1;
	u32 ch11_ahbwt_illegal_sta:   1;
	u32 ch11_axiwt_illegal_sta:   1;
	u32 			  :   1;

	}bits;
};


union  dma_irq_sta_4_u  	{
	u32 dwval;
	struct {
	u32 ch12_htask_irq_sta 	  :   1;
	u32 ch12_task_irq_sta  	  :   1;
	u32 ch12_link_irq_sta  	  :   1;
	u32 ch12_error_irq_sta 	  :   1;
	u32 ch12_ahbrd_illegal_sta:   1;
	u32 ch12_ahbwt_illegal_sta:   1;
	u32 ch12_axiwt_illegal_sta:   1;
	u32 			  :   1;
	u32 ch13_htask_irq_sta 	  :   1;
	u32 ch13_task_irq_sta  	  :   1;
	u32 ch13_link_irq_sta  	  :   1;
	u32 ch13_error_irq_sta 	  :   1;
	u32 ch13_ahbrd_illegal_sta:   1;
	u32 ch13_ahbwt_illegal_sta:   1;
	u32 ch13_axiwt_illegal_sta:   1;
	u32 			  :   1;
	u32 ch14_htask_irq_sta 	  :   1;
	u32 ch14_task_irq_sta  	  :   1;
	u32 ch14_link_irq_sta  	  :   1;
	u32 ch14_error_irq_sta 	  :   1;
	u32 ch14_ahbrd_illegal_sta:   1;
	u32 ch14_ahbwt_illegal_sta:   1;
	u32 ch14_axiwt_illegal_sta:   1;
	u32 			  :   1;
	u32 ch15_htask_irq_sta 	  :   1;
	u32 ch15_task_irq_sta  	  :   1;
	u32 ch15_link_irq_sta  	  :   1;
	u32 ch15_error_irq_sta 	  :   1;
	u32 ch15_ahbrd_illegal_sta:   1;
	u32 ch15_ahbwt_illegal_sta:   1;
	u32 ch15_axiwt_illegal_sta:   1;
	u32 			  :   1;

	}bits;
};

union  dma_bus_cfg_u  	{
	u32 dwval;
	struct {   //LSB  at top ,MSB at bottom
	u32 res_3               :   3;
	u32 engine_clr_en       :   1;
	u32 axi_resp_en         :   1;
	u32 ahb_resp_en         :   1;
	u32 hprot_auto_en       :   1; //write back  is  unbufferable ,is not controled by hprot_auto_en ,and hport set
	u32 ahm_hsize_ben	:   1;
	u32 res_25              :   24;
	}bits;
};

union  dma_ch_ctl1_u  	{
	u32 dwval;
	struct {
	u32 ch_enable        :   1;
	u32                  :   3;
	u32 ch_reenable      :   1;
	u32                  :   27;
	}bits;
};


union  dma_ch_ctl2_u  	{
	u32 dwval;
	struct {
	u32 ch_pause        :   1;
	u32 ch_task_pause   :   1;
	u32 ch_abandon      :   1;
	u32 res_26          :   29;
	}bits;
};

union  dma_ch_ctl3_u  	{
	u32 dwval;
	struct {

	u32 src_mode_cfg            :   2;
	u32 dst_mode_cfg            :   2;
	u32 wt_back_en              :   1;
	u32 fifo_pri_cfg            :   2;
	u32 bus_stop_en             :   1;
	u32 axi_wt_fix_pri_en       :   1;
	u32 axi_rd_fix_pri_en       :   1;
	u32 ahb_wt_fix_pri_en       :   1;//invalid
	u32 ahb_rd_fix_pri_en       :   1;//invalid
	u32 fix_word_en             :   1;
	u32 task_bcnt_sel           :   2;
	u32 res_1                   :   1;
	u32 axi_wt_thd_cfg          :   4;
	u32 axi_rd_thd_cfg          :   4;
	u32 ahb_wt_thd_cfg          :   4;//invalid
	u32 ahb_rd_thd_cfg          :   4;//invalid
	}bits;
};


union  dma_ch_ctl4_u  	{
	u32 dwval;
	struct {
	u32 src_pri_cfg           :   2;
	u32 dst_pri_cfg           :   2;
	u32 fsm_bps_resp_ios      :   1; // for bug design to by bypass
	u32 fsm_bps_resp_iob      :   1; // for bug design to by bypass
	u32 fsm_bps_resp_mem      :   1; // for bug design to by bypass
	u32 fsm_bps_resp_memset   :   1; // for bug design to by bypass
	u32 fsm_bps_resp_wb       :   1; // for bug design to by bypass
	u32 		              :   1;
	u32      		  		  :   1;
	u32                       :   1;
	u32 fsm_frc_resp_mem      :   1;// 0:the last burst wait axi   wb response
	u32 fsm_frc_resp_memset   :   1;// 1:every one burst wait axi  wb response
	u32                       :   1;//wb  every one burst wait axi  wb response
	u32                       :   1;
	u32 src_wclk_set          :   8;
	u32 dst_wclk_set          :   8;
	}bits;
};


// ddr can not use bit field operate ,because bit field  first read  and  writeback data
// sram  have reset value is 0 ,ddr do not have reset value ,need initial
union  task_cfg_2_u  	{
	u32 dwval;
	struct {
	u32 msb8_saddr          :   8;
	u32 msb8_daddr          :   8;
	u32 msb8_taddr          :   8;
	u32 src_hport           :   4;
	u32 dst_hport           :   4;
	}bits;
};

typedef struct dma_link_task
{
	volatile u32 link_id;
	volatile u32 task_cfg_1;
	volatile u32 handshake_len;
	volatile u32 src_addr;
	volatile u32 dst_addr;
	volatile u32 task_length;
	volatile u32 task_cfg_2;
	volatile u32 next_task_addr;
	volatile u32 src_wb_data;
	volatile u32 dst_wb_data;
	volatile u32 res001;
} dma_link_task_p;


union  dma_fifo_cfg_u  	{
	u32 dwval;
	struct {
	u32 fifo_space           	   :   16;
	u32 fifo_base_addr_offset          :   16;
	}bits;
};


typedef struct dma_ch_reg {
	volatile union	dma_ch_ctl1_u          dma_ch_ctl_1;
	volatile union	dma_ch_ctl2_u  		   dma_ch_ctl_2;
	volatile u32	               		   dma_ch_task_add_1;
	volatile u32	               		   dma_ch_task_add_2;
	volatile union	dma_ch_ctl3_u  		   dma_ch_ctl_3;
	volatile union	dma_ch_ctl4_u  		   dma_ch_ctl_4;
	volatile u32				   dma_mem_set_val;
	volatile u32				   dma_task_bcnt;
	volatile u32				   dma_link_id;
	volatile u32				   dma_task_cfg_1;
	volatile u32				   dma_hdshk_len;
	volatile u32				   dma_src_addr;
	volatile u32				   dma_dst_addr;
	volatile u32				   dma_task_len;
	volatile u32				   dma_task_cfg_2;
	volatile u32				   dma_next_task_add;
	volatile u32				   dma_src_wb_addr_set;
	volatile u32				   dma_dst_wb_addr_set;
	volatile u32				   dma_src_wb_data;
	volatile u32				   dma_dst_wb_data;
	volatile u32				   dma_task_cnt;
	volatile u32				   dma_link_sel;
	 u32				   	   dma_res002[2];
	volatile u32                               dma_debug;
	volatile union	dma_fifo_cfg_u 		   dma_fifo_cfg;
		 u32    			   dma_res006[6];
} dma_ch_reg_p;


typedef struct dma_module_reg {
	volatile union  dma_irq_en_1_u  dma_irq_en_1;		//offset 0x00
	volatile union  dma_irq_en_2_u  dma_irq_en_2;		//offset 0x04
	volatile union  dma_irq_en_3_u  dma_irq_en_3;		//offset 0x08
	volatile union  dma_irq_en_4_u  dma_irq_en_4;		//offset 0x0C
	u32  dma_res001[4];									//offset 0x10/14/18/1C
	volatile union  dma_irq_clr_1_u  dma_irq_clr_1;		//offset 0x20
	volatile union  dma_irq_clr_2_u  dma_irq_clr_2;		//offset 0x24
	volatile union  dma_irq_clr_3_u  dma_irq_clr_3;		//offset 0x28
	volatile union  dma_irq_clr_4_u  dma_irq_clr_4;		//offset 0x2C
	u32  dma_res009[4];									//offset 0x30/34/38/3C
	volatile union  dma_irq_sta_1_u dma_irq_sta_1;		//offset 0x40
	volatile union  dma_irq_sta_2_u	dma_irq_sta_2;		//offset 0x44
	volatile union  dma_irq_sta_3_u dma_irq_sta_3;		//offset 0x48
	volatile union  dma_irq_sta_4_u	dma_irq_sta_4;		//offset 0x4C
	u32 dma_res010;										//offset 0x50
	volatile u32	dma_bus_addr_sel;					//offset 0x54
	volatile u32	dma_bus_start_addr;					//offset 0x58
	volatile u32	dma_bus_stop_addr;					//offset 0x5C
	u32  dma_res002[8];									//offset 0x60-6C/0x70-7C
	volatile union  dma_bus_cfg_u	dma_bus_cfg;        //offset 0x80
	u32 dma_res003;										//offset 0x84
	volatile u32    dma_link_id_set;                    //offset 0x88
	u32 dma_res004;										//offset 0x8C
	volatile u32    dma_fifo_max;           			//offset 0x90
	u32 dma_res007[3];									//offset 0x94/98/9C
	volatile u32    dma_allch_state;                    //offset 0xA0
	u32 dma_res008[3];									//offset 0xA4/A8/AC
	u32 dma_res005[20];									//offset 0xB0-BC/0xC0-CC/0xD0-DC/0xE0-EC/0xF0-FC/
	volatile dma_ch_reg_p  dma_ch[DMA_CH_NUM];
} dma_module_reg_p;


//s32 dma_request(u8 dma_num, u8 ch, dma_device_id_p src_drq, dma_task_cfg1_p src_cfg, dma_device_id_p dst_drq, dma_task_cfg1_p dst_cfg,u32 block_length,
//		u32 saddr, u32 daddr, u32 len, u32 n, u32 loop);
s32 dma_request_reg(u8 dma_num, u8 ch, dma_device_id_p src_drq, dma_task_cfg1_p src_cfg, dma_device_id_p dst_drq, dma_task_cfg1_p dst_cfg,
			  u32 block_length, u32 saddr, u32 daddr, u32 len, u32 loop_en);
s32 dma_enable(u8 dma_num, u8 ch);
s32 dma_disable(u8 dma_num, u8 ch);
s32 dma_wait_finish(u8 dma_num, u8 ch);
u32 dma_irq_enable(u8 dma_num, u32 ch, u32 en);
u32 dma_irq_query(u8 dma_num, u8 ch);
void dma_irq_sts_clr(u8 dma_num, u8 ch, u32 clr);
s32 dma_pause(u8 dma_num, u8 ch,u8 ctrol);
s32 dma_discard_finish(u8 dma_num, u8 ch);
s32 dma_fix_pri_en(u8 dma_num, u8 ch,u8 en);
s32 dma_auto_pri_incthd_cfg(u8 dma_num, u8 ch,u8 cfg);
s32 dma_pri_set(u8 dma_num, u8 ch,u8 ch_pri);
s32 init_dma(u8 dma_num);
void dma_irq_register(u32 num, cpu_irq_fun_t irqhandle);
void dma_irq_unregister(u32 num);
void dma_len_cfg(u8 dma_num, u32 ch, u32 len);
//extern  dma_link_task_p dma_ch_reg_task[16][4];

#endif /* INCLUDE_HAL_DMA_H_ */
