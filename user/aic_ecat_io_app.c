#include "all_inc.h"
#include "aic_ecat_hw.h"
#include "aic_ecat_cfg.h"
#include "ecat_def.h"
#include "applInterface.h"
#include "aic_ecat_phy.h"
#include "servo_drv_setting.h"
/*
 * aic_ecat_io_app.c
 *
 * 此例程为ethercat 普通IO例程；
 * 注意：由于许可问题，AIC不提供Ethercat从站协议栈代码(SSC/Src)，请从倍福下载SSC Tool并生成从站协议栈代码
 * 运行此例程需在example_setting.h中去掉注释 "#define EXAMPLE_ECAT_IO"，右击ecat_io->properties,去掉勾选 "exclued resource from build"
 * 程序运行后，可以通过TwinCat配置Value1和Value2
 * Results2值为Value1+和Value2
 *
 *
 */
#ifdef EXAMPLE_ECAT_IO

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
volatile int test_cnt = 0;
void APPL_InputMapping(UINT16* pData)
{
    *pData = Results0x6000.Results1;
    pData++;
    *pData = Results0x6000.Results2;
    pData++;
    *pData = Results0x6000.Toggle;//;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
    SetpointValues0x7000.Value1 = *pData;
    pData++;
    SetpointValues0x7000.Value2 = *pData;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
    Results0x6000.Results1 += Parameters0x8000.Inc1;
    Results0x6000.Results2 = SetpointValues0x7000.Value1+SetpointValues0x7000.Value2;
}

int ecat_main(void)
{
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

        init_uart_dbg(0);                                   //初始化UART0

        ecat_init();                                        //ecat config and init pinmux、clock、heap and interruption

        drv_gtc_dly_time(GTC_MS, 200);                          //wait for ecat init

        ret = ecat_check_eeprom_loading();                  //check eeprom
        if(ret != RET_OK) {
               return RET_FALSE;
        }

        ecat_phy_reset_cfg(1);                              //release phy reset

        drv_gtc_dly_time(GTC_MS, PHY_RESET_OUT_DLY_TIME);       //wait for phy ready

        ret = ecat_phy_init();                              //check phy id and config led mode
        if(ret != RET_OK) {
                return RET_FALSE;
        }

        ecat_timer_init();                                  //start timer for ecat

        ENABLE_ESC_INT();                                   //enable pdi irq

        return ecat_main();                                 //ecat stack runing

}

#endif
