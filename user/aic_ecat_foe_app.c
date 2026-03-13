#include <flash_drv.h>
#include "all_inc.h"
#include "aic_ecat_hw.h"
#include "aic_ecat_cfg.h"
#include "ecat_def.h"
#include "applInterface.h"
#include "aic_ecat_phy.h"
#include "servo_drv_setting.h"
/*
 * aic_ecat_foe_app.c
 *
 *
 *
 */
#ifdef EXAMPLE_ECAT_FOE

#define FILE_SIZE			(4*1024)

static char test_file[FILE_SIZE];
const char *file_name = "test_file";
static u32 m_ProgramAddr = 0;

const char* ecat_foe_get_file_name(char *file_name, u16 nameSize)
{
	if(0 == _strncmp(partition_info.part[BOOTLOADER].name, file_name, nameSize)){
		m_ProgramAddr = partition_info.part[BOOTLOADER].start;
		cur_part = &partition_info.part[BOOTLOADER];
		foe_flash_log("part name: %s\n", partition_info.part[BOOTLOADER].name);
	}else if(0 == _strncmp(partition_info.part[APP].name, file_name, nameSize)){
		m_ProgramAddr = partition_info.part[APP].start;
		cur_part = &partition_info.part[APP];
		foe_flash_log("part name: %s\n", partition_info.part[APP].name);
	}else if(0 == _strncmp(partition_info.part[PARTITION].name, file_name, nameSize)){
		m_ProgramAddr = partition_info.part[PARTITION].start;
		cur_part = &partition_info.part[PARTITION];
		foe_flash_log("part name: %s\n", partition_info.part[PARTITION].name);
	}else{
		cur_part = NULL;
		return NULL;
	}
	return cur_part->name;
}

u32 ecat_foe_get_file_size(void)
{
	volatile u32 file_size = 0;
	if (cur_part != NULL) {
		flash_read_bank((u8*)&file_size, (cur_part->start + cur_part->size) - 4, 4);
		if (file_size > cur_part->size) {
			return cur_part->size;	//整个分区的大小
		} else {
			return file_size;
		}
	} else {
		return 0;
	}
}

char* ecat_foe_get_file_ptr(void)
{
	if(cur_part != NULL){
		return cur_part->name;
	}else{
		return NULL;
	}
}


u32 ecat_foe_erase_flash(void)
{

	if(cur_part != NULL){
		flash_program_start(cur_part);
		return 0;
	}else{
		return 1;	//整个分区的大小
	}
}

u32 ecat_foe_get_flash_size(void)
{
	if(cur_part != NULL){
		return cur_part->start + cur_part->size;
	}else{
		return 0;	//整个分区的大小
	}
}

u32 ecat_foe_write_flash(char *data, u32 addr_off, u32 size, BOOL bDataFollowing)
{
	if(size > 0){
		flash_write_bank(data, addr_off, size);
	}
	//memcpy(&test_file[addr_off], data, size);
	if(bDataFollowing){
		return 0;
	} else {
		volatile u32 this_size;
		volatile uint32_t file_size = (addr_off + size) - cur_part->start;
		flash_write_bank((u8 *)&file_size, (cur_part->start + cur_part->size) - 4, 4);
		flash_read_bank((u8*)&file_size, (cur_part->start + cur_part->size) - 4, 4);
		//下载完成，校验文件
		return 1; //1=校验通过 2=校验失败
	}
}


/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
volatile int test_cnt = 0;
void APPL_InputMapping(UINT16* pData)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{

}

int ecat_main(void)
{
	flash_init();
        HW_Init();

        MainInit();

        /*Create basic mapping*/
        APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);

        bRunApplication = TRUE;

        do
        {
            MainLoop();
        } while (bRunApplication == TRUE);

        HW_Release();

        return 0;
}

s32 main(void)  //RET_OK
{
        s32 ret = RET_OK;

        basic_init();

        uart_dbg_gpio_init();                  //使用PA0/1管脚的UART0作为打印串口

        init_uart_dbg(0);                                   //初始化UART0

        ecat_init();                                        //ecat config and init pinmux、clock、heap and interruption

        drv_gtc_dly_time(GTC_MS, 200);                          //wait for ecat init

        ret = ecat_check_eeprom_loading();                  //check eeprom
        if(ret != RET_OK) {
              // return RET_FALSE;
        }

        ecat_phy_reset_cfg(1);                              //release phy reset

        drv_gtc_dly_time(GTC_MS, PHY_RESET_OUT_DLY_TIME);       //wait for phy ready

        ret = ecat_phy_init();                              //check phy id and config led mode
        if(ret != RET_OK) {
               // return RET_FALSE;
        }

        ecat_timer_init();                                  //start timer for ecat

        ENABLE_ESC_INT();                                   //enable pdi irq

        return ecat_main();                                 //ecat stack runing

}

#endif
