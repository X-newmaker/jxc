#include <flash_drv.h>
#include "all_inc.h"
#include "M680x_it.h"
#include "cia402appl.h"
#include "aic_ecat_cfg.h"
#include "aic_ecat_hw.h"
#include "aic_ecat_phy.h"
#include "applInterface.h"
#include "ecat_def.h"
#include "servo_drv_setting.h"
#include "ecatslv.h"
/*
 * aic_ecat_cia402_app.c
 *
 * 此例程为ethercat cia402例程；
 * 注意：由于许可问题，AIC不提供Ethercat从站协议栈代码(SSC/Src)，请从倍福下载SSC Tool并生成从站协议栈代码
 * 运行此例程需在example_setting.h中去掉注释 "#define EXAMPLE_ECAT_CIA402"，右击ecat_cia402->properties,去掉勾选 "exclued resource from build"
 */
#ifdef EXAMPLE_ECAT_CIA402
UINT16 CiA402_Init(void);
void CiA402_DeallocateAxis(void);

int ecat_main(void)
{
        HW_Init();

        MainInit();

        /*Initialize Axes structures*/
        CiA402_Init();

        /*Create basic mapping*/
        APPL_GenerateMapping(&nPdInputSize,&nPdOutputSize);

        bRunApplication = TRUE;

        do
        {
            MainLoop();
        } while (bRunApplication == TRUE);

        CiA402_DeallocateAxis();

        return 0;
}

s32 main(void)  //RET_OK
{
        s32 ret = RET_OK;

        basic_init();


        init_uart0_upg();                                  //初始化UART0

        ecat_init();                                        //ecat config and init pinmux、clock、heap and interruption

        //drv_gtc_dly_time(GTC_MS, 200);                          //wait for ecat init

        //ret = ecat_check_eeprom_loading();                  //check eeprom
//        if(ret != RET_OK) {
//               //return RET_FALSE;
//        }

        ecat_phy_reset_cfg(1);                              //release phy reset

       // drv_gtc_dly_time(GTC_MS, PHY_RESET_OUT_DLY_TIME);       //wait for phy ready

        ret = ecat_phy_init();                              //check phy id and config led mode
//        if(ret != RET_OK) {
//                return RET_FALSE;
//        }

        ecat_timer_init();                                  //start timer for ecat

        ENABLE_ESC_INT();                                   //enable pdi irq

        return ecat_main();                                 //ecat stack runing

}

#endif
