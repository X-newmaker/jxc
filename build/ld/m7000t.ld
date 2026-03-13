
ENTRY(Bring)

MEMORY
{
	/* 需要在start.S中配置sysmap, 0x30044100-0x30050100的地址uncache */
	ITCM(rwx)		: ORIGIN = 0x30040100, LENGTH = 255K
	DTCM(rwx)		: ORIGIN = 0x30080000, LENGTH = 96K
	STACK(rwx)		: ORIGIN = 0x30098000, LENGTH = 32K
	UCM(rwx)		: ORIGIN = 0x300a0000, LENGTH = 48K
	SRAM (rwx)		: ORIGIN = 0x300aC000, LENGTH = 592K
	UART0(rxx) 		: ORIGIN = 0x18710000, LENGTH = 4K
	UART1(rxx) 		: ORIGIN = 0x18711000, LENGTH = 4K
	UART2(rxx) 		: ORIGIN = 0x18712000, LENGTH = 4K
	UART3(rxx) 		: ORIGIN = 0x18713000, LENGTH = 4K
	UART4(rxx) 		: ORIGIN = 0x18714000, LENGTH = 4K
	UART5(rxx) 		: ORIGIN = 0x18715000, LENGTH = 4K
	UART6(rxx) 		: ORIGIN = 0x18716000, LENGTH = 4K
	UART7(rxx) 		: ORIGIN = 0x18717000, LENGTH = 4K
	UART8(rxx) 		: ORIGIN = 0x18718000, LENGTH = 4K
	I2C0(rwx)  		: ORIGIN = 0x18720000, LENGTH = 4K
	I2C1(rwx)  		: ORIGIN = 0x18721000, LENGTH = 4K
	I2C2(rwx)  		: ORIGIN = 0x18722000, LENGTH = 4K
	I2C3(rwx)  		: ORIGIN = 0x18723000, LENGTH = 4K
	CAN0(rwx)		: ORIGIN = 0x19060000, LENGTH = 4K
	ADC0(rwx)  		: ORIGIN = 0x11050000, LENGTH = 4K
	ADC1(rwx)  		: ORIGIN = 0x11051000, LENGTH = 4K
	EPWM0(rwx) 		: ORIGIN = 0x11040000, LENGTH = 256
	EPWM1(rwx) 		: ORIGIN = 0x11040100, LENGTH = 256
	EPWM2(rwx) 		: ORIGIN = 0x11040200, LENGTH = 256
	EPWM3(rwx) 		: ORIGIN = 0x11040300, LENGTH = 256
	EPWM4(rwx) 		: ORIGIN = 0x11040400, LENGTH = 256
	EPWM5(rwx) 		: ORIGIN = 0x11040500, LENGTH = 256
	EPWM6(rwx) 		: ORIGIN = 0x11040600, LENGTH = 256
	EPWM7(rwx) 		: ORIGIN = 0x11040700, LENGTH = 256
	EPWM8(rwx) 		: ORIGIN = 0x11040800, LENGTH = 256
	EPWM9(rwx) 		: ORIGIN = 0x11040900, LENGTH = 256
	EPWM10(rwx)		: ORIGIN = 0x11040A00, LENGTH = 256
	EPWM11(rwx)		: ORIGIN = 0x11040B00, LENGTH = 256
	CAP0(rwx)  		: ORIGIN = 0x11041000, LENGTH = 256
	CAP1(rwx)  		: ORIGIN = 0x11041100, LENGTH = 256
	CAP2(rwx)  		: ORIGIN = 0x11041200, LENGTH = 256
	CAP3(rwx)       : ORIGIN = 0x11041300, LENGTH = 256
	CAP4(rwx)       : ORIGIN = 0x11041400, LENGTH = 256
	CAP5(rwx)       : ORIGIN = 0x11041500, LENGTH = 256
	QEP0(rwx)  		: ORIGIN = 0x11042000, LENGTH = 256
	QEP1(rwx)  		: ORIGIN = 0x11042100, LENGTH = 256
	QEP2(rwx)       : ORIGIN = 0x11042200, LENGTH = 256
	QEP3(rwx)       : ORIGIN = 0x11042300, LENGTH = 256
	QEP4(rwx)       : ORIGIN = 0x11042400, LENGTH = 256
	QEP5(rwx)       : ORIGIN = 0x11042500, LENGTH = 256
	QEP6(rwx)       : ORIGIN = 0x11042600, LENGTH = 256
	QEP7(rwx)       : ORIGIN = 0x11042700, LENGTH = 256
	QEP8(rwx)       : ORIGIN = 0x11042800, LENGTH = 256
	QEP9(rwx)       : ORIGIN = 0x11042900, LENGTH = 256
	QOUT0(rwx)  	: ORIGIN = 0x11043000, LENGTH = 256
	QOUT1(rwx)  	: ORIGIN = 0x11043100, LENGTH = 256	
	GLB_PWMCS(rwx)	: ORIGIN = 0x1104F000, LENGTH = 4K
	TAIF0(rwx)      : ORIGIN = 0x11080000, LENGTH = 512
	TAIF1(rwx)      : ORIGIN = 0x11080200, LENGTH = 512
	EDTIF0(rwx)		: ORIGIN = 0x11090000, LENGTH = 512
	EDTIF1(rwx)		: ORIGIN = 0x11090200, LENGTH = 512
	BISSIF0(rwx)	: ORIGIN = 0x110A0000, LENGTH = 512
	BISSIF1(rwx)	: ORIGIN = 0x110A0200, LENGTH = 512
	SDFM(rwx)		: ORIGIN = 0x110B0000, LENGTH = 4K
	CORDIC(rwx)		: ORIGIN = 0x11000000, LENGTH = 4K
	HCL0(rwx)		: ORIGIN = 0x11010000, LENGTH = 4K
	HCL1(rwx)		: ORIGIN = 0x11011000, LENGTH = 4K
	PBUS(rwx)  		: ORIGIN = 0x107F0000, LENGTH = 128K
	THS(rwx)		: ORIGIN = 0x11052000, LENGTH = 4K
	CPM(rwx)		: ORIGIN = 0x11060000, LENGTH = 4K
	XPWM0(rwx)		: ORIGIN = 0x110C0000, LENGTH = 256
	XPWM1(rwx)		: ORIGIN = 0x110C0100, LENGTH = 256
	XPWM2(rwx)		: ORIGIN = 0x110C0200, LENGTH = 256
	XPWM3(rwx)		: ORIGIN = 0x110C0300, LENGTH = 256
	XPWM4(rwx)		: ORIGIN = 0x110C0400, LENGTH = 256
	XPWM5(rwx)		: ORIGIN = 0x110C0500, LENGTH = 256
	FFT(rwx)		: ORIGIN = 0x11054000, LENGTH = 4K
	RDC(rwx)		: ORIGIN = 0x11020000, LENGTH = 4K
	DCE(rwx)		: ORIGIN = 0x10010000, LENGTH = 4K
}

PROVIDE (__heap_end                = 0x3012C000);


SECTIONS
{

 	.itcm : {
	 	 . = ALIGN(0x4) ;
	  	__itcm_code_start = .;
	 	 *(.tcm_code)
		./user/servo/user_source/*(.text*)
	 	 . = ALIGN(0x4) ;
		  __itcm_code_end = .;
		  __itcm_heap_start = .;
	 } > ITCM AT > ITCM 

 	.dtcm : {
	 	 . = ALIGN(0x4) ;
	 	 __dtcm_data_start = .;
		  *(.tcm_data)
		./user/servo/user_source/*(.*data*)
		./user/servo/user_source/*(.rodata*)
		./user/servo/user_source/*(.*bss*)
		./user/servo/user_source/*(.got)
		./user/servo/user_source/*(.got.plt)
	 	 . = ALIGN(0x4) ;
	 	 __dtcm_data_end = .;
		  __dtcm_heap_start = .;
	 } > DTCM

	.head :
	{
		__ram_begin__ = .;
		./build/core/start.o(.text*)
		./build/core/start.o(.rodata*)
	} > SRAM

	.text :
	{
		KEEP(*(.note.gnu.build-id))
		*(.text*)
		*(.got)
		*(.got.plt)
		*(.rodata*)
		. = ALIGN(8);
	} > SRAM

	.ucm : {
		. = ALIGN(0x4) ;
		__ucm_data_start = .;
		*(.ucm_data)
		. = ALIGN(0x4) ;
		__ucm_data_end = .;
		__ucm_heap_start = .;
	} > UCM AT > UCM

	.data :
	{
		*(.*data*)
		. = ALIGN(8);
	} > SRAM

	.bss :
	{
		__bss_start__ = .;
		*(.*bss*)
		. = ALIGN(8);
		__bss_end__ = .;
	} > SRAM

	.heap :
	{
		. = ALIGN(8);
		 __heap_start = .;
	} > SRAM

	.stack :
	{
		__stack_beg__ = .;
		__stack_end__  = LENGTH(STACK);
	} > STACK

	.uart0reg :
	{
        *(.uart0reg*)
	} > UART0

	.uart1reg :
	{
        *(.uart1reg*)
	} > UART1

	.uart2reg :
	{
        *(.uart2reg*)
	} > UART2

	.uart3reg :
	{
        *(.uart3reg*)
	} > UART3

	.uart4reg :
	{
        *(.uart4reg*)
	} > UART4

	.uart5reg :
	{
        *(.uart5reg*)
	} > UART5

	.uart6reg :
	{
        *(.uart6reg*)
	} > UART6

	.uart7reg :
	{
        *(.uart7reg*)
	} > UART7

	.uart8reg :
	{
        *(.uart8reg*)
	} > UART8

	.i2c0reg :
	{
        *(.i2c0reg*)
	} > I2C0

	.i2c1reg :
	{
        *(.i2c1reg*)
	} > I2C1

	.i2c2reg :
	{
        *(.i2c2reg*)
	} > I2C2
	
	.i2c3reg :
	{
        *(.i2c3reg*)
	} > I2C3

	.can0reg :
	{
        *(.can0reg*)
	} > CAN0
	
	.adc0reg :
	{
		*(.adc0reg*)
	} > ADC0

	.adc1reg :
	{
		*(.adc1reg*)
	} > ADC1

	.epwm0reg :
	{
		*(.epwm0reg*)
	} > EPWM0

	.epwm1reg :
	{
		*(.epwm1reg*)
	} > EPWM1

	.epwm2reg :
	{
		*(.epwm2reg*)
	} > EPWM2

	.epwm3reg :
	{
		*(.epwm3reg*)
	} > EPWM3

	.epwm4reg :
	{
		*(.epwm4reg*)
	} > EPWM4

	.epwm5reg :
	{
		*(.epwm5reg*)
	} > EPWM5

	.epwm6reg :
	{
		*(.epwm6reg*)
	} > EPWM6

	.epwm7reg :
	{
		*(.epwm7reg*)
	} > EPWM7

	.epwm8reg :
	{
		*(.epwm8reg*)
	} > EPWM8

	.epwm9reg :
	{
		*(.epwm9reg*)
	} > EPWM9

	.epwm10reg :
	{
		*(.epwm10reg*)
	} > EPWM10

	.epwm11reg :
	{
		*(.epwm11reg*)
	} > EPWM11

	.cap0reg :
	{
		*(.cap0reg*)
	} > CAP0

	.cap1reg :
	{
		*(.cap1reg*)
	} > CAP1

	.cap2reg :
	{
		*(.cap2reg*)
	} > CAP2

	.cap3reg :
	{
		*(.cap3reg*)
	} > CAP3

	.cap4reg :
	{
		*(.cap4reg*)
	} > CAP4

	.cap5reg :
	{
		*(.cap5reg*)
	} > CAP5

	.qep0reg :
	{
		*(.qep0reg*)
	} > QEP0

	.qep1reg :
	{
		*(.qep1reg*)
	} > QEP1

	.qep2reg :
	{
        *(.qep2reg*)
	} > QEP2

	.qep3reg :
	{
        *(.qep3reg*)
	} > QEP3

	.qep4reg :
	{
        *(.qep4reg*)
	} > QEP4

	.qep5reg :
	{
        *(.qep5reg*)
	} > QEP5

	.qep6reg :
	{
        *(.qep6reg*)
	} > QEP6

	.qep7reg :
	{
        *(.qep7reg*)
	} > QEP7

	.qep8reg :
	{
        *(.qep8reg*)
	} > QEP8

	.qep9reg :
	{
        *(.qep9reg*)
	} > QEP9

	.qout0reg :
	{
		*(.qout0reg*)
	} > QOUT0

	.qout1reg :
	{
		*(.qout1reg*)
	} > QOUT1

	.hcl0reg :
	{
        *(.hcl0reg*)
	} > HCL0

	.hcl1reg :
	{
        *(.hcl1reg*)
	} > HCL1

	.glbpwmcsreg :
	{
		*(.glbpwmcsreg*)
	} > GLB_PWMCS

	.cordicreg :
	{
        *(.cordicreg*)
	} > CORDIC

	.taif0reg :
	{
		*(.taif0reg*)
	} > TAIF0

	.taif1reg :
	{
		*(.taif1reg*)
	} > TAIF1

	.edtif0reg :
	{
		*(.edtif0reg*)
	} > EDTIF0

	.edtif1reg :
	{
		*(.edtif1reg*)
	} > EDTIF1

	.bissif0reg :
	{
		*(.bissif0reg*)
	} > BISSIF0

	.bissif1reg :
	{
		*(.bissif1reg*)
	} > BISSIF1


	.sdfmreg :
	{
        *(.sdfmreg*)
	} > SDFM

	.thsreg :
    {
         *(.thsreg*)
     } > THS

     .cpmreg :
	{
        *(.cpmreg*)
	} > CPM

	.xpwm0reg :
	{
        *(.xpwm0reg*)
	} > XPWM0
	
	.xpwm1reg :
	{
        *(.xpwm1reg*)
	} > XPWM1
	
	.xpwm2reg :
	{
        *(.xpwm2reg*)
	} > XPWM2
	
	.xpwm3reg :
	{
        *(.xpwm3reg*)
	} > XPWM3
	
	.xpwm4reg :
	{
        *(.xpwm4reg*)
	} > XPWM4
	
	.xpwm5reg :
	{
        *(.xpwm5reg*)
	} > XPWM5
	
    .pbusreg :
    {
        *(.pbusreg*)
    } > PBUS
    
    .fftreg :
    {
        *(.fftreg*)
    } > FFT
    
      .rdcreg :
    {
        *(.rdcreg*)
    } > RDC
    
      .dcereg :
    {
        *(.dcereg*)
    } > DCE
}
