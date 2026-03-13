
#ifndef __E907_H__
#define __E907_H__


#include "common_type.h"

void e907_prediction_enable(void);
void e907_l1_icache_enable(void);
void e907_l1_dcache_enable(void);
void e907_l1_write_allocate(void);
void e907_mmu_init(u64 ppn);
void e907_mmu_enable(void);
void e907_all_cache_disable(void);
void e907_icache_invalid_all(void);
void e907_icache_invalid_region(void *start, u32 length);
void e907_dcache_clean_all(void);
void e907_dcache_clean_region(void *start, u32 length);
void e907_dcache_invalid_all(void);
void e907_dcache_invalid_region(void *start, u32 length);
void e907_dcache_flush_all(void);
void e907_dcache_flush_region(void *start, u32 length);
void e907_flush_tlb_all(void);
void e907_neon_vfp_enable(void);
void e907_irq_enable(void);
void e907_irq_disable(void);
void e907_fiq_enable(void);
void e907_fiq_disable(void);
u64 e907_time_val(void);
void e907_timer_enable(void);
void e907_pmp_init(u32* p);
void e907_tcm_init(u32 itcm, u32 dtcm);
void e907_set_mexstatus(void);
void e907_mode_switch(cpu_mode_t mode);
void e907_neon_write(void* beg, u32 len, u32 data);
void e907_neon_write_down(void* beg, u32 len, u32 data);
void e907_neon_copy(void* src, void* dst, u32 len);
u32 e907_neon_compare(void* src, void* dst, u32 len, u32* diff);
u32 e907_neon_compare_down(void* src, void* dst, u32 len, u32* diff);

#endif
