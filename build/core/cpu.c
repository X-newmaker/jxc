/*
 * cpu.c
 */

#include "all_inc.h"
#include "e907.h"
#include "clic.h"
#include "clint.h"


static void cpu_irq_null(void) {};
volatile cpu_irq_fun_t cpu_timer_irq_vector __attribute__((aligned(16)));
volatile cpu_irq_fun_t cpu_nmi_irq_vector __attribute__((aligned(16)));

inline u64 cpu_get_time(void)
{
	return e907_time_val();
}

inline s32 cpu_timer_set(u64 tval)
{
	u64 val = e907_time_val();
	clint_mtime_cfg(val+tval);

	return RET_OK;
}

inline s32 cpu_timer_irq_request(cpu_irq_fun_t fun)
{
	cpu_irq_request(CPU_IRQ_TIMER, fun);

	return RET_OK;
}

inline s32 cpu_timer_irq_free(void)
{
	cpu_irq_request(CPU_IRQ_TIMER, cpu_irq_null);

	return RET_OK;
}

inline s32 cpu_timer_irq_enable(void)
{
	cpu_irq_enable(CPU_IRQ_TIMER);

	return RET_OK;
}

inline s32 cpu_timer_irq_disable(void)
{
	cpu_irq_disable(CPU_IRQ_TIMER);

	return RET_OK;
}

inline s32 cpu_nmi_irq_request(cpu_irq_fun_t fun)
{
	cpu_nmi_irq_vector = fun;

	return RET_OK;
}

inline s32 cpu_nmi_irq_free(void)
{
	cpu_nmi_irq_vector = cpu_irq_null;

	return RET_OK;
}

void cpu_nmi_irq_handler(void)
{
	cpu_nmi_irq_vector();
}

s32 cpu_tlb_flush(void)
{
	e907_flush_tlb_all();

	return RET_OK;
}

s32 cpu_icache_invalid_all(void)
{
	e907_icache_invalid_all();

	return RET_OK;
}

s32 cpu_dcache_clean_all(void)
{
	e907_dcache_clean_all();

	return RET_OK;
}

s32 cpu_dcache_clean_region(void *beg, u32 len)
{
	u32 b = (u32)(uaddr)beg & ~0x3f;
	u32 e = (u32)(uaddr)beg + len - 1;
	u32 l = (e + 64 - b) & ~0x3f;

	e907_dcache_clean_region((void*)(uaddr)b, l);

	return RET_OK;
}

s32 cpu_dcache_invalid_all(void)
{
	e907_dcache_invalid_all();

	return RET_OK;
}

s32 cpu_dcache_invalid_region(void *beg, u32 len)
{
	u32 b = (u32)(uaddr)beg & ~0x3f;
	u32 e = (u32)(uaddr)beg + len - 1;
	u32 l = (e + 64 - b) & ~0x3f;

	e907_dcache_invalid_region((void*)(uaddr)b, l);

	return RET_OK;
}

s32 cpu_dcache_flush_all(void)
{
	e907_dcache_flush_all();

	return RET_OK;
}

s32 cpu_dcache_flush_region(void *beg, u32 len)
{
	e907_dcache_flush_region(beg, len);

	return RET_OK;
}

s32 cpu_vfp_wr(void* beg, u32 len, u32 data)
{
	u32* pdst;
	for(pdst=(u32*)beg; pdst<(u32*)beg+len/4; pdst++)
		*pdst = data;

	return RET_OK;
}

s32 cpu_vfp_cp(void* src, void* dst, u32 len)
{
	u32* pdst = (u32*)dst;
	u32* psrc = (u32*)src;
	for(; pdst<(u32*)dst+len/4; pdst++,psrc++)
		*pdst = *psrc;

	return RET_OK;
}

u32 cpu_vfp_cmp(void* src, void* dst, u32 len, u32* diff)
{
	u32* pdst = (u32*)dst;
	u32* psrc = (u32*)src;

	for(; pdst<(u32*)dst+len/4; pdst++,psrc++)
	{
		if(*pdst ^ *psrc)
		{
			*(diff+0) = (u32)((uaddr)pdst);
			*(diff+1) = (u32)((uaddr)pdst);
			return *pdst ^ *psrc;
		}
	}

	return 0;
}

u32 cpu_vfp_cmp_n(void* src, void* dst, u32 len, u32* diff)
{
	u32* pdst = (u32*)dst+len/4-1;
	u32* psrc = (u32*)src+len/4-1;
	for(; pdst<=(u32*)dst; pdst--,psrc--)
	{
		if(*pdst ^ *psrc)
		{
			*(diff+0) = (u32)((uaddr)pdst);
			*(diff+1) = (u32)((uaddr)pdst);
			return *pdst ^ *psrc;
		}
	}

	return 0;
}

s32 init_cpu(void)
{

	e907_l1_icache_enable();
 	e907_l1_dcache_enable();

	init_clic();
 	e907_set_mexstatus();  

	e907_irq_enable();

	return RET_OK;
}



__weak void Exception_Mirq_Handler(void) {}
__weak void PendSV_Handler(void) {}
__weak void xPortSysTickHandler(void) {}
__weak void PBUS_Handler(void) {}
__weak void PFM_Handler(void) {}
__weak void CPM_IRQHandler(void) {}
__weak void SDFM_IRQHandler(void) {}
__weak void HCL_IRQHandler(void) {}
__weak void CORDIC_Handler(void) {}
__weak void ADC_IRQHandler(void) {}
__weak void DCE_Handler(void) {}
__weak void DMA0_IRQHandler(void) {}
__weak void DMA1_IRQHandler(void) {}
__weak void ECAT_PDI_IRQHandler(void) {}
__weak void ECAT_RESET_IRQHandler(void) {}
__weak void ECAT_SYNC0_IRQHandler(void) {}
__weak void ECAT_SYNC1_IRQHandler(void) {}
__weak void GMAC_Handler(void) {}
__weak void SPI_ENC_Handler(void) {}
__weak void SPI0_IRQHandler(void) {}
__weak void SPI1_IRQHandler(void) {}
__weak void SPI2_IRQHandler(void) {}
__weak void SPI3_IRQHandler(void) {}
__weak void SPI4_IRQHandler(void) {}
__weak void SPI5_IRQHandler(void) {}
__weak void USBD_IRQHandler(void) {}
__weak void WDOG0_IRQHandler(void) {}
__weak void WDOG1_IRQHandler(void) {}
__weak void GPIO_A_IRQHandler(void) {}
__weak void GPIO_B_IRQHandler(void) {}
__weak void GPIO_C_IRQHandler(void) {}
__weak void GPIO_D_IRQHandler(void) {}
__weak void GPIO_E_IRQHandler(void) {}
__weak void GPIO_F_IRQHandler(void) {}
__weak void GPIO_G_IRQHandler(void) {}
__weak void GPIO_H_Handler(void) {}
__weak void GPIO_J_Handler(void) {}
__weak void GPIO_K_IRQHandler(void) {}
__weak void UART0_IRQHandler(void) {}
__weak void UART1_IRQHandler(void) {}
__weak void UART2_IRQHandler(void) {}
__weak void UART3_IRQHandler(void) {}
__weak void UART4_IRQHandler(void) {}
__weak void UART5_IRQHandler(void) {}
__weak void UART6_IRQHandler(void) {}
__weak void UART7_IRQHandler(void) {}
__weak void UART8_IRQHandler(void) {}
__weak void VTS_Handler(void) {}
__weak void THS_IRQHandler(void) {}
__weak void XPWM0_IRQHandler(void) {}
__weak void XPWM1_IRQHandler(void) {}
__weak void XPWM2_IRQHandler(void) {}
__weak void XPWM3_IRQHandler(void) {}
__weak void XPWM4_IRQHandler(void) {}
__weak void XPWM5_IRQHandler(void) {}
__weak void TAIF0_IRQHandler(void) {}
__weak void TAIF1_IRQHandler(void) {}
__weak void EDTIF0_IRQHandler(void) {}
__weak void EDTIF1_IRQHandler(void) {}
__weak void BISSIF0_IRQHandler(void) {}
__weak void BISSIF1_IRQHandler(void) {}
__weak void GPT0_IRQHandler(void) {}
__weak void GPT1_IRQHandler(void) {}
__weak void GPT2_IRQHandler(void) {}
__weak void GPT3_IRQHandler(void) {}
__weak void MBOX_C02C1_IRQHandler(void) {}
__weak void MBOX_C12C0_IRQHandler(void) {}
__weak void RDC_Handler(void) {}
__weak void CE_Handler(void) {}
__weak void I2C0_IRQHandler(void) {}
__weak void I2C1_IRQHandler(void) {}
__weak void I2C2_IRQHandler(void) {}
__weak void I2C3_IRQHandler(void) {}
__weak void CANFD0_IRQHandler(void) {}
__weak void CANFD1_IRQHandler(void) {}
__weak void CAN_IRQHandler(void) {}
__weak void EPWM_FAULT_IRQHandler(void) {}
__weak void EPWM0_IRQHandler(void) {}
__weak void EPWM1_IRQHandler(void) {}
__weak void EPWM2_IRQHandler(void) {}
__weak void EPWM3_IRQHandler(void) {}
__weak void EPWM4_IRQHandler(void) {}
__weak void EPWM5_IRQHandler(void) {}
__weak void EPWM6_IRQHandler(void) {}
__weak void EPWM7_IRQHandler(void) {}
__weak void EPWM8_IRQHandler(void) {}
__weak void EPWM9_IRQHandler(void) {}
__weak void EPWM10_IRQHandler(void) {}
__weak void EPWM11_IRQHandler(void) {}
__weak void CAP0_IRQHandler(void) {}
__weak void CAP1_IRQHandler(void) {}
__weak void CAP2_IRQHandler(void) {}
__weak void CAP3_IRQHandler(void) {}
__weak void CAP4_IRQHandler(void) {}
__weak void CAP5_IRQHandler(void) {}
__weak void QEP0_IRQHandler(void) {}
__weak void QEP1_IRQHandler(void) {}
__weak void QEP2_IRQHandler(void) {}
__weak void QEP3_IRQHandler(void) {}
__weak void QEP4_IRQHandler(void) {}
__weak void QEP5_IRQHandler(void) {}
__weak void QEP6_IRQHandler(void) {}
__weak void QEP7_IRQHandler(void) {}
__weak void QEP8_IRQHandler(void) {}
__weak void QEP9_IRQHandler(void) {}
__weak void QOUT0_IRQHandler(void) {}
__weak void QOUT1_IRQHandler(void) {}
__weak void FFT_Handler(void) {}
