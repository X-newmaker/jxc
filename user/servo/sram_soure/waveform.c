/*
 * user_io.c
 *
 *  Created on: 2023年8月14日
 *      Author: wen.xuan
 */
#include "all_inc.h"
#include "M680x_it.h"
extern volatile struct COR_REGS Cor_Regs;
//以下定义方便打印查看
void UartRTDataSend(void);
void UartSendFuncodeMsg(u8 group,u8 index);
void UartSanf(void);
u8 CheckSumCal(u8 buf[],u8 len);
void UartDataAnalysis(UNION_UARTAPP pdata);

u8 IsRTSend = 1;
u8 uSendFuncodeMsg = 0;
u8 uartSendGroup = 0,uartSendIndex = 0;
extern volatile struct HCL_REGS *HCL[];
#define UART_ID        	1
#define DMA_UART_SEND_INDEX         1
#define DMA_USE_UCM     1
#define	MAX_UART_RX_LEN		50
//u8 UART_TX[5]  = {0x31,0x32,0x33,0x34,0x35};
u8 UART0_RX[MAX_UART_RX_LEN]  = {0x0,0x0,0x0,0x0,0x0};
u8 UART0_RX_index = 0,UART0_RX_indexTemp = 0;
//u32 uart1_act = ACK;
//u32 uart2_act = ACK;
UNION_UARTAPP str_uartapp = {0};
u8 uartappindex = 0;

u16 uart0FrameCount = 0;
u8     uUart0RLen = 0;			//UART已经接收到的数据长度
u16  uUart0IdleCounter = 0;		//统计IDLE的中断次数

#ifndef DMA_USE_UCM
u8 uartbuf[50]  __attribute__((aligned(8))) ;
#else
//将所需的tx_dat和rx_dat buffer放在UCM区间
DMA_NOCACHE_RAM_SECTION u8 uartbuf[50] __attribute__((aligned(8))) = {0};
#endif
void uart0_isr(void)
{
        u32 sts;

//        sts = (uart_get_iir(UART_ID) & 0x7);
        sts = (uart_get_iir(UART_ID) & 0xF);//读取进入中断的状态信息

        uUart0IdleCounter++;	//统计进入串口中断的次数
        if(sts == IIR_CHAR_TIMEOUT)
        {//空闲中断
        	uUart0RLen = uart_get_rfl(UART_ID);


        	if(uUart0RLen > MAX_UART_RX_LEN - 2)
        	{
        		uUart0RLen = MAX_UART_RX_LEN - 2;//预留2个字节给数据打印次数
        	}

        	if(uUart0RLen > 0)
        	{
        		u8 i;
//                uart_receive_char(0, &upg_char);
//                if (upg_char == CTRL('R'))
//                        upg_char_inum ++;
//                else
//                        upg_char_inum = 0;
//
//                if(upg_char_inum > 5)
//                {
//                        set_reboot_upg_reson();
//                        cmu_wdog_enable();
//                        wdog_expire_now(0x0);
//                }
        		for(i=0; i< uUart0RLen; i++)
        		uart_receive_char(UART_ID, &UART0_RX[i]);//读取FIFO中的数据
        		UART0_RX_index = uUart0RLen;
        	}
        }
}

//void uart_transmit_multi_char(u8 index, u8 *buf, u8 size)
//{
//        u32 i = 0;
//        for(i=0;i<size;i++)
//        {
//                uart_transmit_char(index, (u8) buf[i]);
//        }
//}

void uart_receive_multi_char(u8 index, u8 *buf, u8 size)
{
        u32 i = 0;
        u8 *p;
        for(i=0;i<size;i++)
        {

                p = (u8 *)(buf + i);
                uart_receive_char(index, p);
        }
}

//实时发送关键数据到上位机查看
void UartRTSend(void)
{
	UartSanf();//串口数据扫描监测
	if(uSendFuncodeMsg)
	{//read
		uSendFuncodeMsg = 0;
//		UartSendFuncodeMsg(uartSendGroup,uartSendIndex);
	}
	else if(IsRTSend)
	{//实时数据发送
		UartRTDataSend();
//		IsRTSend = 0;
	}

	else
	{

	}
}
//0~1 			0xAAAA
//2				0xF1
//3     		len  ∈[2~10]
//4~ 4+len-1  	data
//len+4  		checksum

void UartSanf(void)
{
	u8 dataIsCorrect = 0;
//	if(UART_RX_index != UART_RX_indexTemp)
	if(UART0_RX_index > 5)
	{
		while(UART0_RX_indexTemp < UART0_RX_index)
		{
			str_uartapp.all[uartappindex] = UART0_RX[UART0_RX_indexTemp];
			UART0_RX_indexTemp++;
			if(UART0_RX_indexTemp >= MAX_UART_RX_LEN)
			{
				UART0_RX_indexTemp = 0;
			}
			if(uartappindex == 0 || uartappindex == 1)
			{//0xAAAA
				if(str_uartapp.all[uartappindex] == 0xAA)
				{
					uartappindex++;
				}
				else
				{
					uartappindex = 0;
				}
			}
			else if(uartappindex == 2)
			{//0xF1
				if((str_uartapp.all[uartappindex] == 0xF1)||(str_uartapp.all[uartappindex] == 0xF2))
				{//0xF1:read	0xF2:write
					uartappindex++;
				}
				else
				{
					uartappindex = 0;
				}
			}
			else
			{
				uartappindex++;
				if((str_uartapp.bit.len > 0)&&((uartappindex) == (5+str_uartapp.bit.len)))
				{
//					if(CheckSumCal(str_uartapp.all,uartappindex-1) == str_uartapp.all[uartappindex-1])
					{// checksum is correct
						dataIsCorrect = 1;
					}
					uartappindex = 0;
					if(dataIsCorrect > 0)
					{
						break;
					}
				}
			}
		}
		UART0_RX_index = 0;
	}
	else
	{
		UART0_RX_indexTemp = 0;
	}
	if(dataIsCorrect)
	{
		dataIsCorrect = 0;
		UartDataAnalysis(str_uartapp);
		uart0FrameCount++;//统计准确的帧数
		uSendFuncodeMsg = str_uartapp.bit.fun;	//读写
		uartSendGroup = str_uartapp.bit.data[0];//组数据
		uartSendIndex = str_uartapp.bit.data[1];//偏移地址
	}
}
void UartDataAnalysis(UNION_UARTAPP pdata)
{

}

void UartSendFuncodeMsg(u8 group,u8 index)
{
#if 0
	u8 uartbuf[25]  __attribute__((aligned(8))) ;

	u8 len = 0,i;
	u8 checksum = 0;
	u16 utemp[5];//默认最多10条曲线，如需要增加请修改
	//帧头 0xAA
	uartbuf[len++] = 0xAA;
	uartbuf[len++] = 0xAA;
	//功能码 0xF1
	uartbuf[len++] = str_uartapp.bit.fun;
	//LEN 4
	uartbuf[len++] = 0;

#if 0
	//有效数据
	if((group > OffSvLEN2) || (FunCode_GroupEndIndex[group] <= index))
	{//超出当前组的下标则不允许操作（读写）
		return;
	}
#endif

	if(str_uartapp.bit.fun == 0xF1)
	{//读取
		utemp[0] = (u16)group<<8 | index;				//地址
		utemp[1] = GetFunCode(group,index);				//值
		utemp[2] = GetDftLowerLmt(group,index);			//下限
		utemp[3] = GetDftUpperLmt(group,index);			//上限
		utemp[4] = GetAttrib_PanelAttrib(group,index);	//属性

		uartbuf[len++] = BYTE1(utemp[0]);
		uartbuf[len++] = BYTE0(utemp[0]);// curve 1

		uartbuf[len++] = BYTE1(utemp[1]);
		uartbuf[len++] = BYTE0(utemp[1]);// curve 2

		uartbuf[len++] = BYTE1(utemp[2]);
		uartbuf[len++] = BYTE0(utemp[2]);// curve 3

		uartbuf[len++] = BYTE1(utemp[3]);
		uartbuf[len++] = BYTE0(utemp[3]);// curve 4

		uartbuf[len++] = BYTE1(utemp[4]);
		uartbuf[len++] = BYTE0(utemp[4]);// curve 4
	}
	else// if(str_uartapp.bit.fun == 0xF2)
	{//写入
		u16 data;

		data = str_uartapp.bit.data[2];
		data <<= 8;
		data += str_uartapp.bit.data[3];
		SetFunCode(group,index,data);
		for(i=0; i<str_uartapp.bit.len; i++)
		{
			uartbuf[len++] = str_uartapp.bit.data[i];
		}
	}

	uartbuf[3] = len-4;//LEN 4

	checksum = CheckSumCal(uartbuf,len);
	//校验码
	uartbuf[len++] = checksum;
	uart_dma_tx_request(UART_ID, DMA_UART_SEND_INDEX, (u32)(uartbuf), len);
	dma_enable(DMA_UART_SEND_INDEX);            //使能DMA通道0，进行一次的request操作

	memset(str_uartapp.all,0,sizeof(UNION_UARTAPP));
#endif
}

u8 uart0_getModbusFailData[50] = {0},uart0_getModbusFailDataLen = 0;
extern int32_t   contrl_sum_pos_frq;
void UartRTDataSend(void)
{
	u8 len = 0,i;
	u8 checksum = 0;
	int32_t itemp[10];//默认最多10条曲线，如需要增加请修改
	static u8 test_i = 0;
	//帧头 0xAA
	uartbuf[len++] = 0xAA;
	uartbuf[len++] = 0xAA;
	//功能码 0xF1
	uartbuf[len++] = 0xF1;
	//LEN 4
	uartbuf[len++] = 0;
	//有效数据
	if(Servo.Pn01.ContrlMode.Data == CTL_WITHD_TEST)
	{
		itemp[0] = _iqsin_value;       //电流指令给定
		if(HclSwitch.Hcl_EnableSw == 0)//软件电流环
		{
			itemp[1] = park1.Qs;       //电流反馈值
		}
		else                           //硬件电流环
		{
			itemp[1] = (*HCL[Aixse1_HCL_NUM]).NODD_IQ.bit.VAL;//电流反馈值
		}
		itemp[2] = rg1.rmp_out;
		itemp[3] = 0;
	}
	else
	{
		itemp[0] = encoder1.absa_theta_raw;
		itemp[1] = (s16)ilg2_vdc1.Imeas_a;
		itemp[2] = (s16)ilg2_vdc1.Imeas_b;
		itemp[3] = 20;

//		itemp[2] = (s16)park1.Cosine;
//		itemp[1] = (s16)Cor_Regs.COR_OUT2.bit.OUT_RES2;
//		itemp[2] = (s16)Cor_Regs.COR_OUT1.bit.OUT_RES1;
//		itemp[1] = (s16)(*HCL[0]).NODF_UA.bit.VAL;
//		itemp[2] = (s16)(*HCL[0]).NODF_UB.bit.VAL;
//		itemp[1] = (s16)(*HCL[0]).NODA_DIU.bit.VAL;
//		itemp[2] = (s16)(*HCL[0]).NODA_DIV.bit.VAL;
//		itemp[3] = 0;
	}
	//itemp[2] = 0;
	//itemp[3] = 0;
	uartbuf[len++] = BYTE3(itemp[0]);
	uartbuf[len++] = BYTE2(itemp[0]);// curve 3
	uartbuf[len++] = BYTE1(itemp[0]);
	uartbuf[len++] = BYTE0(itemp[0]);// curve 1

	uartbuf[len++] = BYTE1(itemp[1]);
	uartbuf[len++] = BYTE0(itemp[1]);// curve 2

	uartbuf[len++] = BYTE1(itemp[2]);
	uartbuf[len++] = BYTE0(itemp[2]);// curve 3

	uartbuf[len++] = BYTE1(itemp[3]);
	uartbuf[len++] = BYTE0(itemp[3]);// curve 4

//	uartbuf[len++] = BYTE3(itemp[2]);
//	uartbuf[len++] = BYTE2(itemp[2]);// curve 3
//	uartbuf[len++] = BYTE1(itemp[2]);
//	uartbuf[len++] = BYTE0(itemp[2]);// curve 3
//
//	uartbuf[len++] = BYTE3(itemp[3]);
//	uartbuf[len++] = BYTE2(itemp[3]);// curve 4
//	uartbuf[len++] = BYTE1(itemp[3]);
//	uartbuf[len++] = BYTE0(itemp[3]);// curve 4

	uartbuf[3] = len-4;//LEN 4

	checksum = CheckSumCal(uartbuf,len);
	//校验码
	uartbuf[len++] = checksum;

#if 1
	//cpu_dcache_clean_region(uartbuf, len);     //发送前清除cache中的缓存
	uart_dma_tx_request(UART_ID, DMA_UART_SEND_INDEX, (u32)(uartbuf), len);
	dma_enable(0, DMA_UART_SEND_INDEX);            //使能DMA通道0，进行一次的request操作
#else
	uart_transmit_multi_char(UART_ID, uartbuf, len);

#endif
}

u8 CheckSumCal(u8 buf[],u8 len)
{
	u8 i;
	u8 checksum = 0;
	for(i=0; i< len;i++)
	{
		checksum += buf[i];
	}
	return checksum;
}

void UartGetData(void)
{
//	serial_get_char
}

void dma_isr(void)
{
	u32 dma_ch0_sts, dma_ch1_sts;
	u32 err;
	u32 i;

	dma_ch0_sts = dma_irq_query(0x0, DMA_UART_SEND_INDEX);

	if((dma_ch0_sts & DMA_CH1_ALL_FINISH) == DMA_CH1_ALL_FINISH)
	{
		dma_irq_sts_clr(0x0, DMA_UART_SEND_INDEX, DMA_CH1_ALL_FINISH);
	}
}

void InitUartApp(void)
{
	u32 div;
	UART_CFG_PARA uart_para;

	gpio_enable(GPIO_GRP_G, 12, 2, GPIO_FUN_2);      //选择UART1
	gpio_enable(GPIO_GRP_G, 14, 1, GPIO_FUN_O);      //485RTDSP
	gpio_set_val(GPIO_GRP_G, 14, GPIO_LEVEL_HIGH);

	//2、UART0 CMU使能
	uart_set_cmu(UART_ID);

    //3、配置参数
//    div = uart_get_br_div(UART_ID, 115200);
	div = uart_set_cmu_br(UART_ID, BR_500000);	//高的波特率打开以下定义

	uart_para.data_length 	        = UART_DLS_8;
	uart_para.stop_bit 				= UART_STOP_TYPE0;
	uart_para.parity_fun 	        = UART_PARITY_DIS;
	uart_para.parity_mod 	        = UART_PARITY_MOD0;
	uart_para.baud_rate_div 		= div;

	uart_para.fifo_cfg.FIFOE        = 0x01;
	uart_para.fifo_cfg.RXFIFOR      = 0x01;
	uart_para.fifo_cfg.TXFIFOR      = 0x01;
	uart_para.fifo_cfg.DMAM         = 0x00;
	uart_para.fifo_cfg.TFT          = TX_EMPTY;
	uart_para.fifo_cfg.RT           = RX_ONE_CHAR;
    //4、初始化UART0
    uart_init(UART_ID, &uart_para);

	uart_set_dma_handshake(UART_ID);

	//dma_irq_enable(0x0, DMA_UART_SEND_INDEX, 0x1);        //使能DMA通道0的任务完成中断
	//dma_irq_register(0x0,dma_isr);
}

