/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 *
 */

#ifndef __CPU_H__
#define __CPU_H__

//#include "all_inc.h"


#define  ATTRIBUTE_ISR __attribute__ ((interrupt ("machine")))

#ifndef __weak
#define __weak  __attribute__((weak))
#endif



typedef enum cpu_irq_id_e {
    CPU_IRQ_SOFTIRQ = 3,
	CPU_IRQ_TIMER 			=  7,
	CPU_IRQ_PBUS			= 16,
	CPU_IRQ_PFM				= 19,
	CPU_IRQ_CPM				= 20,
	CPU_IRQ_SDFM			= 21,
	CPU_IRQ_HCL				= 22,
	CPU_IRQ_CORDIC			= 23,
	CPU_IRQ_ADC				= 28,
	CPU_IRQ_DCE				= 31,
	CPU_IRQ_DMA0			= 32,
	CPU_IRQ_DMA1			= 33,
	CPU_IRQ_EtherCAT_PDI	= 34,
	CPU_IRQ_EtherCAT_Reset	= 35,
	CPU_IRQ_EtherCAT_SYNC0  = 36,
	CPU_IRQ_EtherCAT_SYNC1  = 37,

	CPU_IRQ_EMAC0			= 39,
	CPU_IRQ_SPI_ENC 		= 41,
	CPU_IRQ_SPI0 			= 42,
	CPU_IRQ_SPI1 			= 43,
	CPU_IRQ_SPI2 			= 44,
	CPU_IRQ_SPI3 			= 45,
	CPU_IRQ_SPI4 			= 46,
	CPU_IRQ_SPI5 			= 47,

	CPU_IRQ_USB_DEV			= 60,	//usb fs dual-role
	CPU_IRQ_WDOG0 			= 64,
	CPU_IRQ_WDOG1 			= 65,
	CPU_IRQ_GPA 			= 68,
	CPU_IRQ_GPB 			= 69,
	CPU_IRQ_GPC 			= 70,
	CPU_IRQ_GPD 			= 71,
	CPU_IRQ_GPE 			= 72,
	CPU_IRQ_GPF 			= 73,
	CPU_IRQ_GPG 			= 74,
	CPU_IRQ_GPK 			= 77,

	CPU_IRQ_UART0 			= 78,
	CPU_IRQ_UART1 			= 79,
	CPU_IRQ_UART2 			= 80,
	CPU_IRQ_UART3 			= 81,
	CPU_IRQ_UART4 			= 82,
	CPU_IRQ_UART5 			= 83,
	CPU_IRQ_UART6 			= 84,
	CPU_IRQ_UART7 			= 85,
	CPU_IRQ_UART8 			= 86,

	CPU_IRQ_VTS				= 91,
	CPU_IRQ_THS				= 94,
	CPU_IRQ_PWM0 			= 96,
	CPU_IRQ_PWM1 			= 97,
	CPU_IRQ_PWM2 			= 98,
	CPU_IRQ_PWM3 			= 99,
	CPU_IRQ_PWM4 			= 100,
	CPU_IRQ_PWM5 			= 101,

	CPU_IRQ_TA0_IF			= 104,
	CPU_IRQ_TA1_IF			= 105,
	CPU_IRQ_EDT0_IF			= 106,
	CPU_IRQ_EDT1_IF			= 107,
	CPU_IRQ_BISS0_IF		= 108,
	CPU_IRQ_BISS1_IF		= 109,
	CPU_IRQ_GPT0			= 110,
	CPU_IRQ_GPT1			= 111,
	CPU_IRQ_GPT2			= 112,
	CPU_IRQ_GPT3			= 113,
	CPU_IRQ_MBOX_C02C1		= 118,
	CPU_IRQ_MBOX_C12C0		= 119,

	CPU_IRQ_CE 				= 121,
	CPU_IRQ_I2C0 			= 126,
	CPU_IRQ_I2C1 			= 127,
	CPU_IRQ_I2C2 			= 128,
	CPU_IRQ_I2C3 			= 129,
	CPU_IRQ_CANFD0 			= 135,
	CPU_IRQ_CANFD1 			= 136,
	CPU_IRQ_CAN 			= 137,

	CPU_IRQ_EPWM_FAULT 		= 141,
	CPU_IRQ_EPWM0 			= 142,
	CPU_IRQ_EPWM1 			= 143,
	CPU_IRQ_EPWM2 			= 144,
	CPU_IRQ_EPWM3 			= 145,
	CPU_IRQ_EPWM4 			= 146,
	CPU_IRQ_EPWM5 			= 147,
	CPU_IRQ_EPWM6 			= 148,
	CPU_IRQ_EPWM7 			= 149,
	CPU_IRQ_EPWM8 			= 150,
	CPU_IRQ_EPWM9 			= 151,
	CPU_IRQ_EPWM10 			= 152,
	CPU_IRQ_EPWM11 			= 153,

	CPU_IRQ_CAP0			= 166,
	CPU_IRQ_CAP1			= 167,
	CPU_IRQ_CAP2			= 168,
	CPU_IRQ_CAP3			= 169,
	CPU_IRQ_CAP4			= 170,
	CPU_IRQ_CAP5			= 171,

	CPU_IRQ_QEP0			= 172,
	CPU_IRQ_QEP1			= 173,
	CPU_IRQ_QEP2			= 174,
	CPU_IRQ_QEP3			= 175,
	CPU_IRQ_QEP4			= 176,
	CPU_IRQ_QEP5			= 177,
	CPU_IRQ_QEP6			= 178,
	CPU_IRQ_QEP7			= 179,
	CPU_IRQ_QEP8			= 180,
	CPU_IRQ_QEP9			= 181,

	CPU_IRQ_QOUT0			= 182,
	CPU_IRQ_QOUT1			= 183,

	CPU_IRQ_FFT				= 186,

}cpu_irq_id_t;

typedef enum {
        PRIO_0  = 0,
        PRIO_1,
        PRIO_2,
        PRIO_3,
		PRIO_4,
		PRIO_5,
		PRIO_6,
		PRIO_7,
		PRIO_8,
		PRIO_9,
		PRIO_10,
		PRIO_11,
		PRIO_12,
		PRIO_13,
		PRIO_14,
		PRIO_15,
		PRIO_16,
		PRIO_17,
		PRIO_18,
		PRIO_19,
        PRIO_20,
        PRIO_21,
        PRIO_22,
        PRIO_23,
		PRIO_24,
		PRIO_25,
		PRIO_26,
		PRIO_27,
		PRIO_28,
		PRIO_29,
		PRIO_30,
		PRIO_31,
} PRI_TYPE;	//the larger num represent the higher priority

typedef void (*cpu_irq_fun_t)(void);

s32 cpu_irq_request(cpu_irq_id_t id, cpu_irq_fun_t hdle);
s32 cpu_irq_free(cpu_irq_id_t id);
s32 cpu_irq_enable(cpu_irq_id_t id);
s32 cpu_irq_disable(cpu_irq_id_t id);
s32 cpu_irq_mode(cpu_irq_id_t id, u32 shv, u32 trig, u32 mode);
s32 cpu_irq_clear(cpu_irq_id_t id);
s32 cpu_irq_set_nlbits(u8 nlbits);
void clic_irq_set_prio(cpu_irq_id_t id, PRI_TYPE priority);
u8 clic_irq_get_prio(cpu_irq_id_t id);
void clic_cfg_set(void);
void clic_get_ip_sts(cpu_irq_id_t id);

u64 cpu_get_time(void);
s32 cpu_timer_set(u64 tval);
s32 cpu_timer_irq_request(cpu_irq_fun_t fun);
s32 cpu_timer_irq_free(void);
s32 cpu_timer_irq_enable(void);
s32 cpu_timer_irq_disable(void);
s32 cpu_nmi_irq_request(cpu_irq_fun_t fun);
s32 cpu_nmi_irq_free(void);

s32 init_cpu(void);
s32 cpu_icache_invalid_all(void);
s32 cpu_dcache_clean_all(void);
s32 cpu_dcache_clean_region(void *beg, u32 len);
s32 cpu_dcache_invalid_all(void);
s32 cpu_dcache_invalid_region(void *beg, u32 len);
s32 cpu_dcache_flush_all(void);
s32 cpu_dcache_flush_region(void *beg, u32 len);

s32 cpu_vfp_wr(void* beg, u32 len, u32 data);
s32 cpu_vfp_readonly(void* src, u32 len);
s32 cpu_vfp_cp(void* src, void* dst, u32 len);
u32 cpu_vfp_cmp(void* src, void* dst, u32 len, u32* diff);
u32 cpu_vfp_cmp_n(void* src, void* dst, u32 len, u32* diff);
void cpu_return_to_bootrom(void);

s32 cpu_stream_double(u32 addr, u32 len, u32 loop);
s32 cpu_stream_float(u32 addr, u32 len, u32 loop);

#endif //#ifndef __CPU_H__
