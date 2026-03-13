#include "aic_ecat_hw.h"

#include <all_inc.h>

#include "aic_ecat_cfg.h"
#include "aic_ecat_phy.h"
#include "aic_ecat_fee.h"
#include "applInterface.h"
#include "coeappl.h"
#include "ecatappl.h"
#include "esc.h"

volatile UALEVENT         EscALEvent;

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0 if initialization was successful

 \brief    This function intialize the Process Data Interface (PDI) and the host controller.
*////////////////////////////////////////////////////////////////////////////////////////
UINT8 HW_Init(void)
{
    UINT32 intMask = 0;
    UINT32 u16PdiCtrl = 0;

    do
    {
        HW_EscReadDWord(u16PdiCtrl,ESC_PDI_CONTROL_OFFSET);
    } while ((u16PdiCtrl&0xff) != 0x80);

    do
    {
        intMask = 0x0093;
        HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
        intMask = 0;
        HW_EscReadDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    } while (intMask != 0x0093);
    intMask =0;
    //initialize the PDI interrupt source

    //corresponding al event request register bit is not mappped
    HW_EscWriteWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    ENABLE_ESC_INT();

    return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    This function shall be implemented if hardware resources need to be release
        when the sample application stops
*////////////////////////////////////////////////////////////////////////////////////////
void HW_Release(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    first two Bytes of ALEvent register (0x220)

 \brief  This function gets the current content of ALEvent register
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_GetALEventRegister(void)
{
    EscALEvent.Word = (volatile UINT16)(readl(BASE_EtherCAT + ESC_AL_EVENT_OFFSET) & 0xffff);
    return EscALEvent.Word;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    first two Bytes of ALEvent register (0x220)

 \brief  The SPI PDI requires an extra ESC read access functions from interrupts service routines.
        The behaviour is equal to "HW_GetALEventRegister()"
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_GetALEventRegister_Isr(void)
{
    HW_GetALEventRegister();
    return EscALEvent.Word;
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves read data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

 \brief  This function operates the SPI read access to the EtherCAT ASIC.
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscRead( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    /* HBu 24.01.06: if the SPI will be read by an interrupt routine too the
                     mailbox reading may be interrupted but an interrupted
                     reading will remain in a SPI transmission fault that will
                     reset the internal Sync Manager status. Therefore the reading
                     will be divided in 1-byte reads with disabled interrupt */
    UINT16 i = 0;
    UINT8 *pTmpData = (UINT8 *)pData;
    UINT8 temp[4];
    UINT32 rdata = 0;

    /* loop for all bytes to be read */
    while ( i < Len )
    {
        /* the reading of data from the ESC can be interrupted by the
           AL Event ISR, in that case the address has to be reinitialized,
           in that case the status flag will indicate an error because
           the reading operation was interrupted without setting the last
           sent byte to 0xFF */

    //     if(i%4==0) {
     //    rdata = readl(BASE_EtherCAT + Address + i);
    // }
    //*pTmpData = (rdata >> ((i%4)<<3))&0xff;
     *pTmpData = readb(BASE_EtherCAT + Address + i);
     pTmpData++;
     i++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves read data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

\brief  The SPI PDI requires an extra ESC read access functions from interrupts service routines.
        The behaviour is equal to "HW_EscRead()"
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    HW_EscRead(pData, Address, Len);
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves write data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

  \brief  This function operates the SPI write access to the EtherCAT ASIC.
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = 0;
    UINT8 *pTmpData = (UINT8 *)pData;
    while (i < Len) {
        writeb(pTmpData[i], BASE_EtherCAT + Address + i);
        i++;
    }

}


/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param pData        Pointer to a byte array which holds data to write or saves write data.
 \param Address     EtherCAT ASIC address ( upper limit is 0x1FFF )    for access.
 \param Len            Access size in Bytes.

 \brief  The SPI PDI requires an extra ESC write access functions from interrupts service routines.
        The behaviour is equal to "HW_EscWrite()"
*////////////////////////////////////////////////////////////////////////////////////////
void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    HW_EscWrite(pData, Address, Len);
}


#if ESC_EEPROM_EMULATION
/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0 if reload was successful

 \brief    This function is called when the master has request an EEPROM reload during EEPROM emulation

*////////////////////////////////////////////////////////////////////////////////////////
UINT16 HW_EepromReload (void)
{
    return 0;
}
#endif


static void ecat_pinmux_init(void)
{
        cmu_mod_enable(CMU_MOD_GPIO);
        //prot0
        gpio_enable(ECAT_PORT0_GRP, ECAT_PORT0_PIN_START, ECAT_PORT0_PIN_SUM, ECAT_PORT0_PIN_FUN);
        //port1
        gpio_enable(ECAT_PORT1_GRP, ECAT_PORT1_PIN_START, ECAT_PORT1_PIN_SUM, ECAT_PORT1_PIN_FUN);
        //port2
        //gpio_enable(ECAT_PORT2_GRP, ECAT_PORT2_PIN_START, ECAT_PORT2_PIN_SUM, ECAT_PORT2_PIN_FUN);
        //mi
        gpio_enable(ECAT_MI_GRP, ECAT_MI_PIN_START, ECAT_MI_PIN_SUM, ECAT_MI_PIN_FUN);
        gpio_pin_cfg(ECAT_MI_GRP, ECAT_MI_PIN_START, ECAT_MI_PIN_SUM, ECAT_MI_PIN_DRV, GPIO_PULL_NONE);
        //prom
        gpio_enable(ECAT_EEPROM_GRP, ECAT_EEPROM_PIN_START, ECAT_EEPROM_PIN_SUM, ECAT_EEPROM_PIN_FUN);
        //led
        gpio_enable(ECAT_LED_GRP, ECAT_LED_PIN_START, ECAT_LED_PIN_SUM, ECAT_LED_PIN_FUN);
        //SYNC
        //gpio_enable(ECAT_SYNC0_GRP, ECAT_SYNC0_PIN_START, ECAT_SYNC0_PIN_SUM, ECAT_SYNC0_PIN_FUN);
        //gpio_enable(ECAT_SYNC1_GRP, ECAT_SYNC1_PIN_START, ECAT_SYNC1_PIN_SUM, ECAT_SYNC1_PIN_FUN);
        //LATCH
        //gpio_enable(ECAT_LATCH0_GRP, ECAT_LATCH0_PIN_START, ECAT_LATCH0_PIN_SUM, ECAT_LATCH0_PIN_FUN);
        //gpio_enable(ECAT_LATCH1_GRP, ECAT_LATCH1_PIN_START, ECAT_LATCH1_PIN_SUM, ECAT_LATCH1_PIN_FUN);
        //PYH CLOCK
        gpio_enable(ECAT_PHY_CLK_GRP, ECAT_PHY_CLK_PIN_START, ECAT_PHY_CLK_PIN_SUM, ECAT_PHY_CLK_PIN_FUN);
        gpio_pin_cfg(ECAT_PHY_CLK_GRP, ECAT_PHY_CLK_PIN_START, ECAT_PHY_CLK_PIN_SUM, ECAT_PHY_CLK_PIN_DRV, GPIO_PULL_NONE);
}

void __attribute__ ((weak)) PDI_Isr(void){ }
void __attribute__ ((weak)) Sync0_Isr(void){ }
void __attribute__ ((weak)) Sync1_Isr(void){ }

static volatile u64 pdi_irq_in_time;
static volatile u64 pdi_irq_out_time;
static volatile u64 sync_irq_in_time;
static volatile u64 sync_irq_out_time;
ATTRIBUTE_ISR void ECAT_PDI_IRQHandler(void)
{
        PDI_Isr();
        pdi_irq_out_time = cpu_get_time();
        cpu_irq_clear(CPU_IRQ_EtherCAT_PDI);
}

ATTRIBUTE_ISR void ECAT_RESET_IRQHandler(void)
{
        cpu_irq_clear(CPU_IRQ_EtherCAT_Reset);
}

ATTRIBUTE_ISR void ECAT_SYNC0_IRQHandler(void)
{
        volatile u32 SyncState = 0;
        cpu_irq_clear(CPU_IRQ_EtherCAT_SYNC0);
        Sync0_Isr();
        HW_EscReadDWord(SyncState, ESC_DC_SYNC_STATUS);
}

ATTRIBUTE_ISR void ECAT_SYNC1_IRQHandler(void)
{
        volatile u32 SyncState = 0;
        cpu_irq_clear(CPU_IRQ_EtherCAT_SYNC1);
        Sync1_Isr();
        HW_EscReadDWord(SyncState, ESC_DC_SYNC_STATUS);
}

void print_status(void)
{
        u32 temp;
        u64 tt;
        #if 0
        //tt = gtc_get_time(GTC_US);
        printk("RE   CNT 0x300: %x %x\n", readl(BASE_EtherCAT + 0x300), readl(BASE_EtherCAT + 0x304));
        printk("FRE  CNT 0x308: %x\n", readl(BASE_EtherCAT + 0x308));
        printk("EPUE CNT 0x30C: %x\n", readl(BASE_EtherCAT + 0x30C));
        printk("LL   CNT 0x310: %x\n", readl(BASE_EtherCAT + 0x310));
        temp = readl(BASE_EtherCAT + 0x110);
        printk("p0:\t%d\t%d\t%d\n", (temp>>4)&0x01,(temp>>8)&0x01,(temp>>9)&0x01);
        printk("p1:\t%d\t%d\t%d\n", (temp>>5)&0x01,(temp>>10)&0x01,(temp>>11)&0x01);
        printk("p2:\t%d\t%d\t%d\n", (temp>>6)&0x01,(temp>>12)&0x01,(temp>>13)&0x01);
        #endif
        #if 0
        printk("EDL  CTL 0x100: %x\n", readl(BASE_EtherCAT + 0x100));
        printk("PDI  EM  0x204: %x\n", readl(BASE_EtherCAT + 0x204));
        printk("AL   ST  0x130: %x\n", readl(BASE_EtherCAT + 0x130));
        printk("AL   EV  0x220: %x\n", readl(BASE_EtherCAT + 0x220));
        printk("ED   STA 0x110: %x\n", temp);
        printk("CYC UNIT 0x980: %x\n", readl(BASE_EtherCAT + 0x980));
        printk("\tlink\tloop\tcom\n");
        printk("prom:%s\n", temp&0x01 ? "ok":"err" );
        printk("sync  time:[%08x %08x]\n", readl(BASE_EtherCAT + 0x994), readl(BASE_EtherCAT + 0x990));
        printk("l0 pt:[%08x %10u]\nl0 nt:[%08x %10u]\n", readl(BASE_EtherCAT + 0x9b4), readl(BASE_EtherCAT + 0x9b0), readl(BASE_EtherCAT + 0x9bc), readl(BASE_EtherCAT + 0x9b8));
        printk("l1 pt:[%08x %10u]\nl1 nt:[%08x %10u]\n", readl(BASE_EtherCAT + 0x9c4), readl(BASE_EtherCAT + 0x9c0), readl(BASE_EtherCAT + 0x9cc), readl(BASE_EtherCAT + 0x9c8));
        // printk("sync  time:[%08x %08x]\nl0 pt:[%08x %08x]\nl0 nt:[%08x %08x]\nl1 pt:[%08x %08x]\nl1 nt:[%08x %08x]\n",
        // readl(BASE_EtherCAT + 0x994), readl(BASE_EtherCAT + 0x990),
        // readl(BASE_EtherCAT + 0x9b4), readl(BASE_EtherCAT + 0x9b0), readl(BASE_EtherCAT + 0x9bc), readl(BASE_EtherCAT + 0x9b8),
        // readl(BASE_EtherCAT + 0x9c4), readl(BASE_EtherCAT + 0x9c0), readl(BASE_EtherCAT + 0x9cc), readl(BASE_EtherCAT + 0x9c8));

        printk("\n");
        #endif

}

static void gpt_irq_handler0(void) {
        static  u32 gpt_cnt = 0;

        u32 status = gpt_irq_status(ECAT_GPT);
        if(status & (1<<CNTR_MAX_IRQ)) {
            ECAT_CheckTimer();
        }
        gpt_irq_clear(ECAT_GPT,status);
        gpt_cnt = gpt_cnt + 1;
        if(gpt_cnt == 1000) {
                gpt_cnt = 0;
                print_status();
        }
}

void ecat_timer_init(void)
{
        cmu_mod_enable(CMU_MOD_GPT0+ECAT_GPT);
        clic_irq_set_prio(CPU_IRQ_GPT0+ECAT_GPT,7);
        gpt_irq_enable(GPT0+ECAT_GPT,CNTR_MAX_IRQ);
        gpt_irq_register(GPT0+ECAT_GPT, gpt_irq_handler0);
        init_gpt(ECAT_GPT,0x000,GPT_TRG_MODE_AUTO,GPT_RUN_MODE_LOOP,GPT_US_100,0x0,0x9);    //1ms
        cpu_irq_enable(CPU_IRQ_GPT0+ECAT_GPT);
        //pat_goto(0x11);
        gpt_en(ECAT_GPT);

}

void ecat_reset(void)
{
        writeb('R', BASE_EtherCAT+0x41);
        writeb('E', BASE_EtherCAT+0x41);
        writeb('S', BASE_EtherCAT+0x41);
}

static void ecat_irq_init(void)
{
        //cpu_irq_mode(CPU_IRQ_EtherCAT_PDI, 1, 0, 3);//trig 0=level 1=up edge 3=down edge
        cpu_irq_enable(CPU_IRQ_EtherCAT_PDI);

        cpu_irq_enable(CPU_IRQ_EtherCAT_Reset);

        cpu_irq_mode(CPU_IRQ_EtherCAT_SYNC0, 1, 1, 3);//shv=1 , trig 0=level 1=up edge 3=down edge
        cpu_irq_enable(CPU_IRQ_EtherCAT_SYNC0);

        cpu_irq_mode(CPU_IRQ_EtherCAT_SYNC1, 1, 1, 3);//shv=1 , trig 0=level 1=up edge 3=down edge
        cpu_irq_enable(CPU_IRQ_EtherCAT_SYNC1);

        DISABLE_ESC_INT();
}

void ecat_pdi_irq_disable(void)
{
        cpu_irq_disable(CPU_IRQ_EtherCAT_PDI);
}

void ecat_pdi_irq_enable(void)
{
        cpu_irq_enable(CPU_IRQ_EtherCAT_PDI);
}

u32 ecat_get_timer(void)
{
        return gpt_get_time(ECAT_GPT);
}

void ecat_clear_timer(void)
{
        writel(1, GPT_CNTR_CLR(ECAT_GPT));
}

void ecat_cmu_init(void)
{
	cmu_auth_sbit(0x06 | (2 << 4), REG_CMU_PLL_OUT);
	cmu_mod_disable(CMU_MOD_EtherCAT);
	writel(readl(BASE_CFG0_ETHERCAT) ^ (0x01 << 13), BASE_CFG0_ETHERCAT);//register sync
	for(u8 i=0; i<0x10; i++);
	cmu_mod_enable(CMU_MOD_EtherCAT);
}

s32 ecat_check_eeprom_loading(void)
{
    s32 ret = RET_OK;
    u32 cnt;
    u32 reg_val;

    while(1) {
        reg_val = readl(BASE_EtherCAT + 0x110);
        if (reg_val&0x01 == 1) {
                ret = RET_OK;//eeprom loading successful
            break;
        }
        reg_val = readl(BASE_EtherCAT + 0x500);
        if (reg_val&(0x01 << 29 ) == 1) {
                ret = 1;//i2c no ack
            break;
        } else {
            if (reg_val&(0x01 << 27 ) == 1) {
                    ret = 2;//checksum error
                break;
            }
        }

        if (cnt > EEPROM_CHECK_RETRY_COUNT) {
                ret = 3;//timeout
            break;
        }
        cnt++;
        gtc_dly_time(GTC_MS, 1);
    }
    if(ret != RET_OK) {
            switch(ret) {
                case 1: printk("[ECAT]EERPOM No ACK\n");break;
                case 2: printk("[ECAT]EERPOM Checksum Error\n");break;
                case 3: printk("[ECAT]EERPOM Check Timeout\n");break;
                default:break;
            }
            return RET_FALSE;
    }
    printk("[ECAT]EERPOM Loading Successful!\n");
    return ret;
}


s32 ecat_eeprom_access_switch(u8 sel)
{
	u16 reg = readw(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET);
	if(sel == ECAT_EEPROM_PDI_ACCESS) {
		if((reg & 0x03) == 1) {														//pdi has eeprom control
			writeb(sel, BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 1); 				//pdi takes eeprom access
			if(readb(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 1) & 0x01)
				return RET_ECAT_EEPROM_ACCESS_SUCCESS;
			return RET_ECAT_EEPROM_ACCESS_FAILED;
		}
		return RET_ECAT_EEPROM_ACCESS_NOALLOW;
	} else {
		if((reg & (0x01 << 8))) {													//pdi takes eeprom access
				writeb(sel, BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 1);
				if((readb(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 1) & 0x01) == 0)
					return RET_ECAT_EEPROM_ACCESS_SUCCESS;
				return RET_ECAT_EEPROM_ACCESS_FAILED;
			}
	}
}

s32 ecat_eeprom_read(u32 waddr, u32 wlen, u16 *wdata)
{
	u16 temp;
	u32 timeout;
	if(readb(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 1)&0x01) {
		if(readw(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 2) & (0x1 << 15))	//busy
			return RET_ECAT_EEPROM_ACCESS_NOALLOW;

		for(int i = 0; i < wlen; i++) {
			writel(waddr + i, BASE_EtherCAT + ESC_EEPROM_ADDRESS_OFFSET);		//addr
			temp = 0;
			temp &= ~(0x7 << 8);
			temp |= 1 << 8;														//read cmd
			writew(temp, BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 2);
			timeout = 0xfffff;
			do {
				temp = readw(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 2);
			} while((temp & (0x1 << 15)) && timeout--);							//wait for idle

			if(timeout == 0 || (temp & (0x1 << 13))) { 							//timeout or eeprom error
				return RET_ECAT_EEPROM_ACCESS_FAILED;
			}
			wdata[i] = readw(BASE_EtherCAT + ESC_EEPROM_DATA_OFFSET);
		}
		return RET_ECAT_EEPROM_ACCESS_SUCCESS;

	} else {
		return RET_ECAT_EEPROM_ACCESS_FAILED;
	}
}

s32 ecat_eeprom_write(u32 waddr, u32 wlen, const u16 *wdata)
{
	u16 temp;
	u32 timeout;
	if(readb(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 1)&0x01) {
		if(readw(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 2) & (0x1 << 15))	//busy
			return RET_ECAT_EEPROM_ACCESS_NOALLOW;

		for(int i = 0; i < wlen; i++) {
			writel(waddr + i, BASE_EtherCAT + ESC_EEPROM_ADDRESS_OFFSET);		//addr
			writew(wdata[i], BASE_EtherCAT + ESC_EEPROM_DATA_OFFSET);			//data

			temp = 0;
			temp &= ~(0x7 << 8);
			temp |= 1 << 9;														//write cmd
			writew(temp, BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 2);
			timeout = 0xfffff;
			for(int j = 0; j <100000; j++) { }									//delay for eeprom write and ack
			do {
				temp = readw(BASE_EtherCAT + ESC_EEPROM_CONFIG_OFFSET + 2);
			} while((temp & (0x1 << 15)) && timeout--);							//wait for idle
			if(timeout == 0 || (temp & (0x1 << 13))) { 							//timeout or eeprom error
				return RET_ECAT_EEPROM_ACCESS_FAILED;
			}
		}
		return RET_ECAT_EEPROM_ACCESS_SUCCESS;

	} else {
		return RET_ECAT_EEPROM_ACCESS_FAILED;
	}
}

void ecat_eeprom_pdi_access_test(void)
{
	u16 data[8];
	static u8 once = 1;
	if(once) {
		if(ecat_eeprom_access_switch(ECAT_EEPROM_PDI_ACCESS) == RET_ECAT_EEPROM_ACCESS_SUCCESS) {
			once = 0;
			ecat_eeprom_read(0x40, 8, data);//读取0x80的数据
			for(int i = 0; i < 8; i++)
				printk("%x ", data[i]);

			ecat_eeprom_write(0x3f8, 8, data);//将0x80的数据写入到0x7f0
			ecat_eeprom_read(0x3f8, 8, data);//读取0x7f0数据
			printk("\n");
			for(int i = 0; i < 8; i++)
				printk("%x ", data[i]);
			ecat_eeprom_access_switch(ECAT_EEPROM_ECAT_ACCESS);//交还eeprom访问权限
		}

	}
}

void ecat_init(void)
{
        aic_tlsf_heap_init();
        ecat_syscfg_init();
        ecat_pinmux_init();
        ecat_phy_reset_cfg(0);//reset phy
        ecat_cmu_init();
        ecat_irq_init();
#if ESC_EEPROM_EMULATION
        AIC_fee_Init();
#endif

}


