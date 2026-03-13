/*****************************************************************************/
/* 	e907 basic operation						     */
/* 	operations for cache and tlb management				     */
/* 	operations for vfp/neon management				     */
/*****************************************************************************/

#include "e907.i"

.globl	e907_prediction_enable
.globl	e907_l1_icache_enable
.globl	e907_l1_dcache_enable
.globl	e907_l1_write_allocate
.globl	e907_mmu_init
.globl	e907_mmu_enable
.globl	e907_all_cache_disable
.globl	e907_icache_invalid_all
.globl	e907_icache_invalid_region
.globl	e907_dcache_clean_all
.globl	e907_dcache_clean_region
.globl	e907_dcache_invalid_all
.globl	e907_dcache_invalid_region
.globl	e907_dcache_flush_all
.globl	e907_dcache_flush_region
.globl	e907_neon_vfp_enable
.globl	e907_irq_enable
.globl	e907_irq_disable
.globl	e907_fiq_enable
.globl	e907_fiq_disable
.globl	e907_time_val
.globl	e907_timeout_set
.globl	e907_timeout_enable
.globl  e907_pmp_init
.globl  e907_mode_switch
.globl 	e907_tcm_init
.globl	e907_set_mexstatus

/*****************************************************************************/
/*	void e907_prediction_enable(void)				     */
/*	prediction enable and initial the return stack for simulation	     */
/*****************************************************************************/

e907_prediction_enable:

	li		t0, E907_MHINT_DPLD
	csrs		mhint, t0

	li		t0, E907_MHCR_BTB | E907_MHCR_BPE | E907_MHCR_RS
	csrs 		mhcr, t0

	ret

/*****************************************************************************/
/*	void e907_l1_icache_enable(void)				     */
/*	l1 i-cache enable						     */
/*****************************************************************************/

e907_l1_icache_enable:

	li		t0, E907_MHCR_IE
	csrs		mhcr, t0

	ret

/*****************************************************************************/
/* void e907_l1_dcache_enable(void)					     */
/* l1 d-cache enable							     */
/*****************************************************************************/

e907_l1_dcache_enable:

	li		t0, E907_MHINT_AMR
	csrc		mhint, t0
	li		t0, 1<<3
	csrs		mhint, t0

	li		t0, E907_MHINT_PREF_N
	csrs		mhint, t0

	li		t0, E907_MHCR_DE
	csrs		mhcr, t0

	li 		t0, E907_MHCR_WB
	csrs		mhcr, t0

	ret

/*****************************************************************************/
/* void e907_l1_write_allocate(void)					     */
/* l1 write allocate							     */
/*****************************************************************************/

e907_l1_write_allocate:

	li		t0,E907_MHCR_WA
	csrs		mhcr, t0

	ret

/*****************************************************************************/
/*	void e907_mode_switch(mode)	 		     		     */
/*	switch mode							     */
/*****************************************************************************/

e907_mode_switch:

	csrr	t0, mstatus
	lui	t1, 0xffffe
	ori	t1, t1, 0x7ff
	and	t0, t0, t1
	extu	a0, a0, 1, 0
	slli	a0, a0, 11
	or	t0, t0, a0
	csrw	mstatus, t0

	csrw	mepc, ra
//	csrw	stvec, ra
	csrw	sscratch, x0
	csrw	sie, x0
	csrw 	satp, x0

	mret

/*****************************************************************************/
/*	void e907_all_cache_disable(void)				     */
/*	disable all cache and mmu					     */
/*****************************************************************************/

e907_all_cache_disable:

	li		t0, E907_MHCR_IE
	csrc		mhcr, t0
	li		t0, E907_MHCR_DE
	csrc		mhcr, t0

	ret

/*****************************************************************************/
/*	void e907_icache_invalid_all(void)				     */
/*	icache invalid all						     */
/*****************************************************************************/

e907_icache_invalid_all:

	icache.iall

	ret

/*****************************************************************************/
/*	void e907_icache_invalid_region(void *start, u32 length)	     */
/*	flush icache region						     */
/*****************************************************************************/

e907_icache_invalid_region:

	add		t0, a0, a1
ic_invalid:
	icache.ipa	a0
	addi		a0, a0, E907_ICACHE_LINESIZE
	blt		a0, t0, ic_invalid

	ret

/*****************************************************************************/
/*	void e907_dcache_clean_all(void)				     */
/*	dcache clean all						     */
/*****************************************************************************/

e907_dcache_clean_all:

	dcache.call
	fence.i

	ret

/*****************************************************************************/
/*	void e907_dcache_clean_region(void *start, u32 length)	     	     */
/*	dcache clean region 					             */
/*****************************************************************************/

e907_dcache_clean_region:

	add		t0, a0, a1
dc_clean:
	dcache.cpa	a0
	addi		a0, a0, E907_DCACHE_LINESIZE
	blt		a0, t0, dc_clean
	fence.i

	ret

/*****************************************************************************/
/*	void e907_dcache_invalid_all(void)				     */
/*	dcache invalid all						     */
/*****************************************************************************/

e907_dcache_invalid_all:

	dcache.iall
	fence.i

	ret

/*****************************************************************************/
/*	void e907_dcache_invalid_region(void *start, u32 length)	     */
/*	dcache invalid region 					             */
/*****************************************************************************/

e907_dcache_invalid_region:

	add		t0, a0, a1
dc_invalid:
	dcache.ipa	a0
	addi		a0, a0, E907_DCACHE_LINESIZE
	blt		a0, t0, dc_invalid
	fence.i

	ret

/*****************************************************************************/
/*	void e907_dcache_flush_all(void)				     */
/*	dcache flush all						     */
/*****************************************************************************/

e907_dcache_flush_all:

	# dcache.ciall
	j 	e907_dcache_clean_all
	fence.i
	j 	e907_dcache_invalid_all
	fence.i

	ret

/*****************************************************************************/
/*	void e907_dcache_flush_region(void *start, u32 length)	     	     */
/*	dcache flush region 					             */
/*****************************************************************************/

e907_dcache_flush_region:

	add		t0, a0, a1
dc_flush:
	dcache.cpa	a0
	dcache.ipa	a0
	addi		a0, a0, E907_DCACHE_LINESIZE
	blt		a0, t0, dc_flush

	ret

/*****************************************************************************/
/*	void e907_neon_vfp_enable(void)				    	     */
/*	Enable NEON/VFP							     */
/*****************************************************************************/

e907_neon_vfp_enable:

	ret


/*****************************************************************************/
/*	void e907_irq_enable(void)					     */
/*	Enable IRQ of CPU						     */
/*****************************************************************************/

e907_irq_enable:

	li		t0, E907_MSTATUS_MIE
	csrs		mstatus, t0

	ret

/*****************************************************************************/
/*	void e907_irq_disable(void)					     */
/*	disable irq of cpu						     */
/*****************************************************************************/

e907_irq_disable:

	li		t0, E907_MSTATUS_MIE
	csrc		mstatus, t0

	ret

/*****************************************************************************/
/*	u64 e907_time_val(void)					     	     */
/*									     */
/*****************************************************************************/

e907_time_val:

	csrr 		t0, timeh
	csrr		a0, time
	csrr 		a1, timeh
	bne 		t0, a1, e907_time_val

	ret

/*****************************************************************************/
/*	void e907_pmp_init(u32* p)		       	     		     */
/*	pmp init							     */
/*****************************************************************************/

e907_pmp_init:

	lw		t0, 0x00(a0)
	lw		t1, 0x04(a0)
	csrw		pmpcfg0, t0
	csrw		pmpcfg1, t1

	lw		t0, 0x08(a0)
	lw		t1, 0x0c(a0)
	lw		t2, 0x10(a0)
	lw		t3, 0x14(a0)
	csrw		pmpaddr0, t0
	csrw		pmpaddr1, t1
	csrw		pmpaddr2, t2
	csrw		pmpaddr3, t3

	lw		t0, 0x18(a0)
	lw		t1, 0x1c(a0)
	lw		t2, 0x20(a0)
	lw		t3, 0x24(a0)
	csrw		pmpaddr4, t0
	csrw		pmpaddr5, t1
	csrw		pmpaddr6, t2
	csrw		pmpaddr7, t3

	ret

/*****************************************************************************/
/*	void e907_tcm_init(u32 itcm, u32 dtcm)			     	     */
/*****************************************************************************/

e907_tcm_init:
	ori	a0, a0, 0x1
	csrw	mitcmcr, a0
	ori	a1, a1, 0x1
	csrs	mdtcmcr, a1
	fence

	ret

/*****************************************************************************/
/*	void e907_set_mexstatus(void)					     	     */
/*	zdq								     */
/*****************************************************************************/

e907_set_mexstatus:

	csrr 		t0, mexstatus
	lui             t1, 0x00010
	or		t0, t0, t1
	csrs 		mexstatus, t0

	ret
