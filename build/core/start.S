/*****************************************************************************/
/* 	entry start code 						     */
/* 	exception vector						     */
/*****************************************************************************/

#include "e907.i"

        .text
        .globl Bring
Bring:
        jal     ra, Start
        nop
        nop

	.align  6
	.globl  __Vectors
	.type   __Vectors, @object
__Vectors:
	.long   Exception_Mirq_Handler		/* 0 */
	.long   Exception_Mirq_Handler		/* 1 */
	.long   Exception_Mirq_Handler		/* 2 */
	.long   PendSV_Handler				/* 3 */
	.long   Exception_Mirq_Handler		/* 4 */
	.long   Exception_Mirq_Handler		/* 5 */
	.long   Exception_Mirq_Handler		/* 6 */
	.long   xPortSysTickHandler			/* 7 */
	.long   Exception_Mirq_Handler		/* 8 */
	.long   Exception_Mirq_Handler		/* 9 */
	.long   Exception_Mirq_Handler		/* 10 */
	.long   Exception_Mirq_Handler		/* 11 */
	.long   Exception_Mirq_Handler		/* 12 */
	.long   Exception_Mirq_Handler		/* 13 */
	.long   Exception_Mirq_Handler		/* 14 */
	.long   Exception_Mirq_Handler		/* 15 */

	/* External interrupts */
	.long   PBUS_Handler				/* 16 */
	.long   Exception_Mirq_Handler		/* 17 */
	.long   Exception_Mirq_Handler		/* 18 */
	.long   PFM_Handler					/* 19 */
	.long   CPM_IRQHandler				/* 20 */
	.long   SDFM_IRQHandler		        /* 21 */
	.long   HCL_IRQHandler				/* 22 */
	.long   CORDIC_Handler				/* 23 */
	.long   Exception_Mirq_Handler		/* 24 */
	.long   Exception_Mirq_Handler   	/* 25 */
	.long   Exception_Mirq_Handler   	/* 26 */
	.long   Exception_Mirq_Handler      /* 27 */
	.long   ADC_IRQHandler	     		/* 28 */
	.long   Exception_Mirq_Handler		/* 29 */
	.long   Exception_Mirq_Handler		/* 30 */
	.long   DCE_Handler					/* 31 */
	.long   DMA0_IRQHandler				/* 32 */
	.long   DMA1_IRQHandler				/* 33 */
	.long   ECAT_PDI_IRQHandler		    /* 34 */
	.long   ECAT_RESET_IRQHandler		/* 35 */
	.long   ECAT_SYNC0_IRQHandler		/* 36 */
	.long   ECAT_SYNC1_IRQHandler		/* 37 */
	.long   Exception_Mirq_Handler		/* 38 */
	.long   GMAC_Handler				/* 39 */
	.long   Exception_Mirq_Handler		/* 40 */
	.long   SPI_ENC_Handler				/* 41 */
	.long   SPI0_IRQHandler				/* 42 */
	.long   SPI1_IRQHandler				/* 43 */
	.long   SPI2_IRQHandler				/* 44 */
	.long   SPI3_IRQHandler				/* 45 */
	.long   SPI4_IRQHandler				/* 46 */
	.long   SPI5_IRQHandler				/* 47 */
	.long   Exception_Mirq_Handler		/* 48 */
	.long   Exception_Mirq_Handler		/* 49 */
	.long   Exception_Mirq_Handler		/* 50 */
	.long   Exception_Mirq_Handler		/* 51 */
	.long   Exception_Mirq_Handler		/* 52 */
	.long   Exception_Mirq_Handler		/* 53 */
	.long   Exception_Mirq_Handler		/* 54 */
	.long   Exception_Mirq_Handler		/* 55 */
	.long   Exception_Mirq_Handler		/* 56 */
	.long   Exception_Mirq_Handler		/* 57 */
	.long   Exception_Mirq_Handler		/* 58 */
	.long   Exception_Mirq_Handler		/* 59 */
	.long   USBD_IRQHandler				/* 60 */
	.long   Exception_Mirq_Handler		/* 61 */
	.long   Exception_Mirq_Handler		/* 62 */
	.long   Exception_Mirq_Handler		/* 63 */
	.long   WDOG0_IRQHandler			/* 64 */
	.long   WDOG1_IRQHandler			/* 65 */
	.long   Exception_Mirq_Handler		/* 66 */
	.long   Exception_Mirq_Handler		/* 67 */
	.long   GPIO_A_IRQHandler			/* 68 */
	.long   GPIO_B_IRQHandler			/* 69 */
	.long   GPIO_C_IRQHandler			/* 70 */
	.long   GPIO_D_IRQHandler			/* 71 */
	.long   GPIO_E_IRQHandler			/* 72 */
	.long   GPIO_F_IRQHandler			/* 73 */
	.long   GPIO_G_IRQHandler			/* 74 */
	.long   GPIO_H_Handler				/* 75 */
	.long   GPIO_J_Handler				/* 76 */
	.long   GPIO_K_IRQHandler			/* 77 */
	.long   UART0_IRQHandler			/* 78 */
	.long   UART1_IRQHandler			/* 79 */
	.long   UART2_IRQHandler			/* 80 */
	.long   UART3_IRQHandler			/* 81 */
	.long   UART4_IRQHandler			/* 82 */
	.long   UART5_IRQHandler			/* 83 */
	.long   UART6_IRQHandler			/* 84 */
	.long   UART7_IRQHandler			/* 85 */
	.long   UART8_IRQHandler			/* 86 */
	.long   Exception_Mirq_Handler		/* 87 */
	.long   Exception_Mirq_Handler		/* 88 */
	.long   Exception_Mirq_Handler		/* 89 */
	.long   Exception_Mirq_Handler		/* 90 */
	.long   VTS_Handler					/* 91 */
	.long   Exception_Mirq_Handler		/* 92 */
	.long   Exception_Mirq_Handler		/* 93 */
	.long   THS_IRQHandler				/* 94 */
	.long   Exception_Mirq_Handler		/* 95 */
	.long   XPWM0_IRQHandler			/* 96 */
	.long   XPWM1_IRQHandler			/* 97 */
	.long   XPWM2_IRQHandler			/* 98 */
	.long   XPWM3_IRQHandler			/* 99 */
	.long   XPWM4_IRQHandler			/* 100 */
	.long   XPWM5_IRQHandler			/* 101 */
	.long   Exception_Mirq_Handler		/* 102 */
	.long   Exception_Mirq_Handler		/* 103 */
	.long   TAIF0_IRQHandler			/* 104 */
	.long   TAIF1_IRQHandler			/* 105 */
	.long   EDTIF0_IRQHandler			/* 106 */
	.long   EDTIF1_IRQHandler			/* 107 */
	.long   BISSIF0_IRQHandler			/* 108 */
	.long   BISSIF1_IRQHandler			/* 109 */
	.long   GPT0_IRQHandler      		/* 110 */
	.long   GPT1_IRQHandler      		/* 111 */
	.long   GPT2_IRQHandler      		/* 112 */
	.long   GPT3_IRQHandler      		/* 113 */
	.long   Exception_Mirq_Handler		/* 114 */
	.long   Exception_Mirq_Handler		/* 115 */
	.long   Exception_Mirq_Handler		/* 116 */
	.long   Exception_Mirq_Handler		/* 117 */
	.long   MBOX_C02C1_IRQHandler		/* 118 */
	.long   MBOX_C12C0_IRQHandler		/* 119 */
	.long   RDC_Handler					/* 120 */
	.long   CE_Handler					/* 121 */
	.long   Exception_Mirq_Handler		/* 122 */
	.long   Exception_Mirq_Handler		/* 123 */
	.long   Exception_Mirq_Handler		/* 124 */
	.long   Exception_Mirq_Handler		/* 125 */
	.long   I2C0_IRQHandler				/* 126 */
	.long   I2C1_IRQHandler				/* 127 */
	.long   I2C2_IRQHandler				/* 128 */
	.long   I2C3_IRQHandler				/* 129 */
	.long   Exception_Mirq_Handler		/* 130 */
	.long   Exception_Mirq_Handler		/* 131 */
	.long   Exception_Mirq_Handler		/* 132 */
	.long   Exception_Mirq_Handler		/* 133 */
	.long   Exception_Mirq_Handler		/* 134 */
	.long   CANFD0_IRQHandler			/* 135 */
	.long   CANFD1_IRQHandler			/* 136 */
	.long   CAN_IRQHandler				/* 137 */
	.long   Exception_Mirq_Handler		/* 138 */
	.long   Exception_Mirq_Handler		/* 139 */
	.long   Exception_Mirq_Handler		/* 140 */
	.long   EPWM_FAULT_IRQHandler		/* 141 */
	.long   EPWM0_IRQHandler			/* 142 */
	.long   EPWM1_IRQHandler			/* 143 */
	.long   EPWM2_IRQHandler			/* 144 */
	.long   EPWM3_IRQHandler			/* 145 */
	.long   EPWM4_IRQHandler			/* 146 */
	.long   EPWM5_IRQHandler			/* 147 */
	.long   EPWM6_IRQHandler			/* 148 */
	.long   EPWM7_IRQHandler			/* 149 */
	.long   EPWM8_IRQHandler			/* 150 */
	.long   EPWM9_IRQHandler			/* 151 */
	.long   EPWM10_IRQHandler			/* 152 */
	.long   EPWM11_IRQHandler			/* 153 */
	.long   Exception_Mirq_Handler		/* 154 */
	.long   Exception_Mirq_Handler		/* 155 */
	.long   Exception_Mirq_Handler		/* 156 */
	.long   Exception_Mirq_Handler		/* 157 */
	.long   Exception_Mirq_Handler		/* 158 */
	.long   Exception_Mirq_Handler		/* 159 */
	.long   Exception_Mirq_Handler		/* 160 */
	.long   Exception_Mirq_Handler		/* 161 */
	.long   Exception_Mirq_Handler		/* 162 */
	.long   Exception_Mirq_Handler		/* 163 */
	.long   Exception_Mirq_Handler		/* 164 */
	.long   Exception_Mirq_Handler		/* 165 */
	.long   CAP0_IRQHandler				/* 166 */
	.long   CAP1_IRQHandler				/* 167 */
	.long   CAP2_IRQHandler				/* 168 */
	.long   CAP3_IRQHandler				/* 169 */
	.long   CAP4_IRQHandler				/* 170 */
	.long   CAP5_IRQHandler				/* 171 */
	.long   QEP0_IRQHandler				/* 172 */
	.long   QEP1_IRQHandler				/* 173 */
	.long   QEP2_IRQHandler				/* 174 */
	.long   QEP3_IRQHandler				/* 175 */
	.long   QEP4_IRQHandler				/* 176 */
	.long   QEP5_IRQHandler				/* 177 */
	.long   QEP6_IRQHandler				/* 178 */
	.long   QEP7_IRQHandler				/* 179 */
	.long   QEP8_IRQHandler				/* 180 */
	.long   QEP9_IRQHandler				/* 181 */
	.long   QOUT0_IRQHandler			/* 182 */
	.long   QOUT1_IRQHandler			/* 183 */
	.long   Exception_Mirq_Handler		/* 184 */
	.long   Exception_Mirq_Handler		/* 185 */
	.long   FFT_Handler					/* 186 */

	.size __Vectors,.-__Vectors

        .text
	.extern	main
	.extern clic_irq_vector
	.extern cpu_nmi_irq_handler
	.globl Start

	.align  6

Start:
	/* disable ie and clear all interrupts */
	csrw    mie, x0
	csrw    mip, x0

	la      a0, Exception_Mirq_Handler
	csrw    mtvec, a0

	la      a0, __Vectors
	csrw    mtvt, a0

	/*enable theadisaee*/
	li 	a0, E907_MXSTATUS_THEADISAEE
	csrs 	mxstatus, a0

	li 	a0, E907_MXSTATUS_MM
	csrs 	mxstatus, a0

	li      a0, 0x2000
	csrs    mstatus, a0

	#ifdef TCM_ENABLE
	lui	a5, 0x18020
	addi	a5, a5, 0x400
	addi	a5, a5, 0x400
	li	a0, 0x1000
	sw	a0, 0(a5)
	lui	a5, 0x18000
	sw	x0, 0x160(a5)
	li	a0, 1
	sw	a0, 0x160(a5)
	lui	a0, 0x30040
	ori	a0, a0, 0x1
	csrs	mitcmcr, a0
	lui	a0, 0x30060
	ori	a0, a0, 0x1
	csrs	mdtcmcr, a0
	fence
	#endif
	/* Clear bss section */
	la      a0, __bss_start__
	la      a1, __bss_end__
	bgeu    a0, a1, 2f
1:
	sw      zero, (a0)
	addi    a0, a0, 4
	bltu    a0, a1, 1b
2:
	la      sp, __stack_end__

#if 1
	/*initial unacheable region 0x300a0000-0x300aC000*/

	/*default sysmap addr3=0x30040000, attr=0xc*/
	/*set sysmap base addr3 = 0x300a0000, sysmap use addr high 20bit, because 4K align*/
	li	a0, 0x2ffff018
	li  t0, 0x000300a0UL
	sw  t0, (a0)
	/*set uncacheable attr*/
	li	a0, 0x2ffff01c
	li  t0, 0x0UL
	sw  t0, (a0)

	/*default sysmap addr4=0x30040000, attr=0xc*/
	/*set sysmap base addr4 = 0x300aC000, sysmap use addr high 20bit, because 4K align*/
	li	a0, 0x2ffff020
	li  t0, 0x000300aCUL
	sw  t0, (a0)
	/*set uncacheable attr*/
	li	a0, 0x2ffff024
	li  t0, 0x0UL
	sw  t0, (a0)
#endif

	la	t0, main
	jalr	ra, t0
	j 	.

/*****************************************************************************/
/*	Don't process some abort program mode				     */
/*****************************************************************************/

	.align  6

Exception_Mirq_Handler:

	addi    sp, sp, -64
	sw      t6, 60(sp)
	sw      t5, 56(sp)
	csrr	t6, mcause
	blt   	t6, x0, irq

exc:	andi  	t6, t6, 0x3ff
	addi 	t6, t6, -24
	bne	t6, x0, finish
	la 	t6, cpu_nmi_irq_handler
	j 	run

irq:	andi  	t6, t6, 0x3ff
	slli 	t6, t6, 0x2
	la 	t5, clic_irq_vector
	add 	t6, t6, t5
	lw 	t6, 0(t6)
	j 	run

run:	sw      ra,  0(sp)
	sw      a0,  4(sp)
	sw      a1,  8(sp)
	sw      a2, 12(sp)
	sw      a3, 16(sp)
	sw      a4, 20(sp)
	sw      a5, 24(sp)
	sw      a6, 28(sp)
	sw      a7, 32(sp)
	sw      t0, 36(sp)
	sw      t1, 40(sp)
	sw      t2, 44(sp)
	sw      t3, 48(sp)
	sw      t4, 52(sp)
	jalr	ra, t6
	lw      ra,  0(sp)
	lw      a0,  4(sp)
	lw      a1,  8(sp)
	lw      a2, 12(sp)
	lw      a3, 16(sp)
	lw      a4, 20(sp)
	lw      a5, 24(sp)
	lw      a6, 28(sp)
	lw      a7, 32(sp)
	lw      t0, 36(sp)
	lw      t1, 40(sp)
	lw      t2, 44(sp)
	lw      t3, 48(sp)
	lw      t4, 52(sp)
	lw      t5, 56(sp)
	j 	finish

finish:	lw      t5, 56(sp)
	lw      t6, 60(sp)
	addi    sp, sp, 64

	mret
