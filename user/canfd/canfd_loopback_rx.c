#include "all_inc.h"
/*
 * canfd_loopback_rx.c
 *
 * 此例程为canfd的接收还回例程；
 * 对TEST_CAN初始化，配置控制域和数据域的速率均为1M
 * 使用CANFD分析仪连接TEST_CAN对应的收发器H和L线
 * 通过PC对分析仪发送一帧数据
 * 当接CAN收到一帧数据时，将该帧数据原封不动发送回去。
 * 在PC可以看到发送和接收的数据是一致的
 */

#ifdef CANFD_LOOPBACK_RX

#define TEST_CAN CANFD_0



u32 canfd_lbme_cfg(__can_para_t *para)
{
    int temp;
    u8 i;
    u32 array[16];

    for(i = 0; i < 16; i ++) {
        array[i] = para->canfd_buf_p->RBUF[2 + i];
    }

    canfd_fill_parameters(&can_para[TEST_CAN], array);

    canfd_sel_ptb_stb(&can_para[TEST_CAN], CANFD_SEL_PTB);

    canfd_write_tbuf(&can_para[TEST_CAN]);

    can_para[TEST_CAN].canfd_p->RCTRL |= CANFD_SACK_MASK;
    can_para[TEST_CAN].canfd_p->CFG_STAT |= CANFD_TPSS_MASK;
    can_para[TEST_CAN].canfd_p->TCMD |= CANFD_SET_TPE_MASK;

    while(can_para[TEST_CAN].canfd_p->TCMD & CANFD_SET_TPE_MASK) {
        continue;
        }

    return 0;
}

void canfd_handler(void)
{
    u8 i;
    u32 interrupts = can_para[TEST_CAN].canfd_p->RTIF;
    u32 control = can_para[TEST_CAN].canfd_buf_p->RBUF[1];

    if(interrupts & CANFD_RIF_MASK) {
        canfd_clr_cfg_interrupt_flag(&can_para[TEST_CAN], CANFD_RIF_MASK);

        printk("[CANFD]====================\n");
        printk("receive a frame\n");
        if(control & 0x80) {
            printk("[CANFD]IDE = 1: extended frame \n");
        } else {
            printk("[CANFD]IDE = 0: standard frame \n");
            }

        if(control & 0x40) {
            printk("[CANFD]RTR = 1: remote frame \n");
        } else {
            printk("[CANFD]RTR = 0: data frame \n");
            }

        if(control & 0x20) {
            printk("[CANFD]FDF = 1: CAN FD frame \n");
        } else {
            printk("[CANFD]FDF = 0: CAN 2.0 frame \n");
            }

        printk("[CANFD]DLC = %d \n", control & 0xF);

        printk("[CANFD]ID = 0x%x \n", can_para[TEST_CAN].canfd_buf_p->RBUF[0]);

        printk("[CANFD]DATA0 = 0x%x \n", can_para[TEST_CAN].canfd_buf_p->RBUF[2]);
        printk("[CANFD]DATA1 = 0x%x \n", can_para[TEST_CAN].canfd_buf_p->RBUF[3]);

        printk("[CANFD]====================\n\n");
        //loopback rx frame
        can_para[TEST_CAN].can_type = control & 0x20 ? CANFD_MASK : CAN_MASK;
        can_para[TEST_CAN].id =  can_para[TEST_CAN].canfd_buf_p->RBUF[0];
        can_para[TEST_CAN].control.DLC =  control & 0xF;
        canfd_lbme_cfg(&can_para[TEST_CAN]);
        //switch to next rx buf
        can_para[TEST_CAN].canfd_p->RCTRL |= CANFD_RREL_MASK;
    }
}

s32 main(void)
{
        int i;
        basic_init();
        uart_dbg_gpio_init(0, GPIO_GRP_A);      //使用PA0/1管脚的UART0作为打印串口
        init_uart_dbg(0);                       //初始化UART0
        init_canfd(TEST_CAN, 40000000);
        canfd_irq_register(TEST_CAN, canfd_handler);

        printk("[CANFD]==========================\n");
        can_para[TEST_CAN].slow_bitrate = 1000000;
        can_para[TEST_CAN].fast_bitrate = 1000000;
        can_para[TEST_CAN].can_type = CANFD_MASK;
        can_para[TEST_CAN].freq_div_parameters.slow_duty_cycle = 80;
        can_para[TEST_CAN].freq_div_parameters.fast_duty_cycle = 80;
        canfd_set_reset_mode(&can_para[TEST_CAN], CANFD_ACT_RESET);
        canfd_parameters_cal(&can_para[TEST_CAN]);

        /*reset off*/
        canfd_set_reset_mode(&can_para[TEST_CAN], CANFD_NOT_RESET);

        canfd_cfg_int_all_clr(&can_para[TEST_CAN]);
        canfd_cfg_interrupt(&can_para[TEST_CAN], CANFD_RIE_MASK, CAN_ENABLE);

        return 0;
}

#endif
