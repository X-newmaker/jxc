#include "all_inc.h"
#include "aic_ecat_hw.h"
#include "aic_ecat_cfg.h"
#include "ecat_def.h"
#include "applInterface.h"
#include "ECAT_EOE.h"
#include "aic_ecat_phy.h"
#include "aic_ecat_eoe_app.h"
#include "applInterface.h"
#include "servo_drv_setting.h"
/*
 * aic_ecat_eoe_app.c
 * 本例程仅处理ICMP和ARP帧
 *
 *
 */
#ifdef EXAMPLE_ECAT_EOE

const    u8    broadcast_ethernet_addr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };


u16 eoe_cal_check_sum(u16 MBXMEM *data, u16 len)
{
    u32 crc = 0;
    u32 crc_l;
    u32 crc_h;

    while (len > 1)
    {
        crc += SWAPWORD(*data);
        data++;
        len -= 2;
    }

    if (len != 0) // odd
    {
        crc += *((u8*)data);
    }

    crc = HIWORD(crc) + LOWORD(crc);

    do
    {
    	crc_h = HIWORD(crc);
    	crc += crc_h;
    } while(HIWORD(crc) != 0);


    if (crc == 0xFFFF)
    {
        crc = 0;
    }

    return (u16)((~crc)&0xffff);
}



void eoe_receive_frame(UINT16 *pData, UINT16 length)//接收数据函数
{
	u8 *p_byte;
    switch (SWAPWORD(((ENET_FRAME_HEADER *)pData)->frame_type))
    {
        case ENET_FRAME_TYPE_ARP:
        {

            ENET_FRAME_HEADER MBXMEM *p_send_frame = (ENET_FRAME_HEADER MBXMEM *) ALLOCMEM(length);
            p_byte = p_send_frame;
            ENET_ARP_IP_HEADER MBXMEM    *p_arp_header = (ENET_ARP_IP_HEADER MBXMEM    *) &p_byte[ENET_HEADER_LEN];

            MBXMEMCPY(p_send_frame, pData, length);

            if ((MBXMEMCMP(broadcast_ethernet_addr, p_send_frame->destination.data, 4) == 0)
            && (p_arp_header->hw_type            == SWAPWORD(ENET_ARP_HW_ADDR_SPACE_ETHERNET))
            && (p_arp_header->protocol_type      == SWAPWORD(ENET_FRAME_TYPE_IP))
            && (p_arp_header->op                 == SWAPWORD(ENET_ARP_OPCODE_REQUEST))
            && (p_arp_header->hw_addr_len        == ETHERNET_ADDRESS_LEN)
            && (p_arp_header->protocol_addr_len  == 4)
            )
            {
                //swap src and dest
                MBXMEMCPY(p_send_frame->destination.data, p_send_frame->source.data, 6);
                MBXMEMCPY(p_send_frame->source.data, &aMacAdd[0], 6);

                MBXMEMCPY(p_arp_header->dest_mac.addr, p_arp_header->src_mac.addr, 6);
                MBXMEMCPY(p_arp_header->src_mac.addr, &aMacAdd[0], 6);
                MBXMEMCPY(p_arp_header->dest_ip, p_arp_header->src_ip, 4);
                MBXMEMCPY(p_arp_header->src_ip, aIpAdd, 4);
                p_arp_header->op = SWAPWORD(ENET_ARP_OPCODE_REPLY);

                //send frame, freed after the last fragment was send
                EOE_SendFrameRequest((u16 MBXMEM *) p_send_frame, (u16)(ARP_IP_HEADER_LEN + ENET_HEADER_LEN));
            }

        else
        {
            if (p_send_frame != NULL)
            {
                FREEMEM(p_send_frame);
            }
        }

    }
    break;
    case ENET_FRAME_TYPE_IP:
    {
    	ENET_IP_ICMP_FRAME MBXMEM * p_ip_header = (ENET_IP_ICMP_FRAME MBXMEM *) ALLOCMEM(length);

        MBXMEMCPY(p_ip_header, pData, length);

        if ((p_ip_header->ip.protocol == IP_PROTOCOL_ICMP)
            && (p_ip_header->ip_data.icmp.type == ICMP_TYPE_ECHO)
            && (MBXMEMCMP(p_ip_header->ip.dest, aIpAdd, 4) == 0)
            )
        {
            u16 len;
            u32 tmp;


            p_ip_header->ip_data.icmp.type = ICMP_TYPE_ECHO_REPLY;

            len = (p_ip_header->ip.len >> 8) + (((p_ip_header->ip.len) & 0xff) << 8);

            //swap src and dest
            MEMCPY(&tmp, p_ip_header->ip.src, 4);
            MEMCPY(p_ip_header->ip.src, p_ip_header->ip.dest, 4);
            MEMCPY(p_ip_header->ip.dest, &tmp, 4);

            MBXMEMCPY(p_ip_header->head.destination.data, p_ip_header->head.source.data, 6);
            MBXMEMCPY(p_ip_header->head.source.data, aMacAdd, 6);

            //cal checksum
            p_ip_header->ip.cksum = 0;
            p_ip_header->ip.cksum = SWAPWORD(eoe_cal_check_sum((u16 MBXMEM *) &p_ip_header->ip, IP_HEADER_MIN_LEN));

            p_ip_header->ip_data.icmp.cksum = 0;
            p_ip_header->ip_data.icmp.cksum = SWAPWORD(eoe_cal_check_sum((u16 MBXMEM *) &p_ip_header->ip_data.icmp, (u16)(len - 20)));

            //send frame, freed after the last fragment was send
            EOE_SendFrameRequest((u16 MBXMEM *) p_ip_header, (u16)(ENET_HEADER_LEN + len));//发送接口函数
        }
        else
        {
            if (p_ip_header != NULL)
            {
                FREEMEM(p_ip_header);
            }
        }
    }
    break;
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

        gtc_dly_time(GTC_MS, 200);                          //wait for ecat init

        ret = ecat_check_eeprom_loading();                  //check eeprom
        if(ret != RET_OK) {
              // return RET_FALSE;
        }

        ecat_phy_reset_cfg(1);                              //release phy reset

        gtc_dly_time(GTC_MS, PHY_RESET_OUT_DLY_TIME);       //wait for phy ready

        ret = ecat_phy_init();                              //check phy id and config led mode
        if(ret != RET_OK) {
               // return RET_FALSE;
        }

        ecat_timer_init();                                  //start timer for ecat

        ENABLE_ESC_INT();                                   //enable pdi irq

        return ecat_main();                                 //ecat stack runing

}

#endif
