/*
 * modbusRTU.c
 *
 *  Created on: 2024年2月29日
 *      Author: L
 */

#include "all_inc.h"
#include "M680x_it.h"
#define DP_RCV_CRC_ERR_NUMBER 5
#define RTU_MASTER_FRAME_NUM_MAX  100      // 主机命令帧的字符个数

uint16_t g_custom_data[CUSTOM_DATA_COUNT] = {0};
extern volatile struct UART_REGS *UART[];
void modbus_rtu_init(u8 index);
enum COMM_STATUS commStatus;       // 串口初始化为等待接收状态
COMM_SEND_DATA commSendData;
COMM_RCV_DATA commRcvData;
uint16_t commErrInfo;
uint16_t commBaudRate;
uint16_t commType;                 // 串口通讯协议类型
uint16_t commProtocol = 1;         // 通讯协议数据格式:标准modbus
uint32_t commTicker;               // *_0.5ms
uint32_t commSendTicker;
uint32_t canLinkTicker;            // *_0.5ms
uint16_t commRunCmd;               // 通讯控制运行命令字

uint16_t sendFrame[200];           // 从机响应帧
uint16_t rcvFrame[100];            // 接收数据数组(主机命令帧)
uint16_t commReadData[RTU_READ_DATA_NUM_MAX];     // 读取的数据
union SCI_FLAG sciFlag;            // SCI使用的标志
uint16_t FuncFeData;               // FE组数据
uint16_t FEHigh_group;
uint16_t FELow_grade;
uint16_t indexgroup;
uint16_t indexgrade;

uint16_t baud = 96;                 //波特率/100
int16_t  SciSendMode = 0;
int16_t  MotorParaOffset = 0;
int16_t  MotorParaLength = 0;
int16_t  rec_pa_modi_flag = 0;
uint32_t modbus_uart_no = 1;      //modbus 用的串口1


uint16_t Modbus_Standard_ErrInfo[9] = {0, 0x03, 0x01, 0x04, 0x02, 0x03, 0x04, 0x04, 0x04};

extern SERVO_PAR Servo;
extern int16_t   slaver_dp_data[];
const DSP_BAUD_REGISTER_DATA dspBaudRegData[BAUD_NUM_MAX + 1] =  // LSPCLK = SYSCLKOUT/4
{
	{  48, 0x0000, 0x0185, 10},           // 0, 4800bps
    {  96, 0x0000, 0x00c2,  5},           // 1, 9600bps
    { 192, 0x0000, 0x0060, 11},           // 2, 19200bps
    { 384, 0x0000, 0x002f, 13},           // 3, 38400bps
    { 576, 0x0000, 0x001f,  9},           // 4, 57600bps
    {1152, 0x0000, 0x000f,  4},           // 5, 115200bps
    {1280, 0x0000, 0x0008,  0},           // 6, 208300bps
    {2560, 0x0000, 0x0006, 15},           // 7, 256000bps
    {5120, 0x0000, 0x0002, 11},           // 8, 512000bps
};
const uint16_t COMM_ERR_INDEX[8] = {10, 8, 2, 7, 6, 9, 12, 13};
void uart_para_int(u8 index);
void ModbusRcvDataDeal(void);
uint16_t ModbusStartDeal(uint16_t tmp);
void UpdateSciFormat(void);
void UpdateModbusCommFormat(uint16_t baudRate);
void ModbusSendDataDeal(uint16_t err);
uint16_t ModbusCommErrCheck(void);
void CommRcvDataDeal(void);
void CommSendDataDeal(void);
void closeRTX(void);
void setRxConfig(void);
void setTxConfig(void);
void commErrorDeal(void);
void commStatusDeal(void);
void CommDataReRcv(void);//用产生空闲中断时接收处理数据

void CommDataSend(void);
void modbus_rtu_init(u8 index);

void  CommStartSend(void);
void Lina_Level0_ISR(void);    // LIN-SCI 中断
// RS485的接收发送切换
#define RTS GPIO_GRP_G, 14
#define SET_RTS_R gpio_set_val(RTS, GPIO_LEVEL_LOW);
#define SET_RTS_T gpio_set_val(RTS, GPIO_LEVEL_HIGH);
extern void ModbusRcvDataDeal(void);
extern uint16_t ModbusStartDeal(uint16_t tmp);
extern void UpdateModbusCommFormat(uint16_t baudRate);
extern void ModbusSendDataDeal(uint16_t err);
extern uint16_t ModbusCommErrCheck(void);

#define PROTOCOL_NUM    1
const protocolDeal protocolFunc[PROTOCOL_NUM] =
{
// MODBUS
    { ModbusRcvDataDeal,       ModbusStartDeal,
      UpdateModbusCommFormat,  ModbusSendDataDeal,
      ModbusCommErrCheck,
    },
};
//====================================================================
//
// 数据接收后信息解析
//
//====================================================================
void ModbusRcvDataDeal(void)
{
	commRcvData.slaveAddr = RTUslaveAddress;                // 从机地址
	commRcvData.commCmd = RTUcmd;                           // 通讯命令
	commRcvData.commAddr = (RTUhighAddr << 8) + RTUlowAddr; // 操作地址
	commRcvData.commData = (RTUhighData << 8) + RTUlowData; // 操作数据
	switch(RTUcmd)
	{
	   case SCI_CMD_READ://单字读数据
		   commRcvData.crcSize = 6;
		   commRcvData.crcRcv = (RTUhighCrc << 8) + RTUlowCrc;     // CRC校验值
	   break;
	   case SCI_CMD_WRITE://单字写数据
		   commRcvData.crcSize = 6;
		   commRcvData.crcRcv = (RTUhighCrc << 8) + RTUlowCrc;     // CRC校验值
	   break;
	   case SCI_CMD_WRITE_MULT: // 多字写数据
		   commRcvData.crcSize = 7+ rcvFrame[6];
		   commRcvData.crcRcv = (rcvFrame[commRcvData.crcSize + 1] << 8) +
                                 rcvFrame[commRcvData.crcSize];     // CRC校验值
	   break;
	   default:break;
	}

	                               // CRC校验长度
	//commRcvData.commCmdSaveEeprom = SCI_WRITE_WITH_EEPROM;  // 存储EEPROM命令
}

//====================================================================
//
// MODBUS帧头判断
// 参数: tmp-接收帧数据
// 返回: 0-帧头判断过程中
//       1-不需要帧头判断，直接存储接收数据
//
//===================================================================
uint16_t ModbusStartDeal(uint16_t tmp)
{
    if (commTicker >= 4000)                                     // 2s时间，0.5ms*4000 = 2000ms
    {
        commRcvData.rcvDataJuageFlag = 0;                       // 长时间没有收完，帧头判断复位
        commRcvData.rcvNum = 0;                       // 长时间没有收完，帧头判断复位
        commRcvData.rcvFlag = 0;
    }

    if ((commTicker > commRcvData.frameSpaceTime))              // 超过3.5个字符时间，新的一帧的开始
    {
        RTUslaveAddress = tmp;
        // 广播模式
        if (RTUslaveAddress == 0)
        {
            commRcvData.rcvNum = 1;
            commRcvData.rcvFlag = 1;                           // 接收到帧的第一个字节，且是广播模式
        }
                                                               // 本机地址
        else if (RTUslaveAddress == Servo.Pn03.CommSlaverNum.Data)
        {
            commRcvData.rcvNum = 1;
            commRcvData.rcvFlag = 2;
        }
        else                                                   // 其它地址
        {
            commRcvData.rcvFlag = 0;                           // 地址不对应，数据不接收
        }

        return 0;
    }

    return 1;
}


//====================================================================
//
// 更新通讯参数
// 1、接收数据个数
// 2、新帧开始判断时间
// 3、应答延迟时间
//
//====================================================================
void UpdateModbusCommFormat(uint16_t baudRate)
{
    static uint16_t i = 0;
    if(!i)
    {
        commRcvData.rcvNumMax = 8;      // 初始化接收长度，实际长度在中断判断
        i = 0xcc;
    }
    commRcvData.frameSpaceTime = 385 * 2 / baudRate+ 1;        // 3.5 char time=3.5*(1+8+2)/baud
    commRcvData.delay = Servo.Pn03.CommReplyDelay.Data;
//    uart_para_int(modbus_uart_no);
#if 0 //ma
    commRcvData.delay = (funcCode.code.commProtocolSec == EXTEND_COM_CAR) ? 0 : (funcCode.code.commDelay * 2);
#endif
}
//====================================================================
//
// 准备发送数据
// 参数: err-通讯命令处理出错信息,为0表示操作成功
// 返回: 1、发送数据长度
//       2、发送数据信息
//
// 转化为标准的MODBUS错误描述
// 01,命令码错误
// 02,地址错误
// 03,数据错误
// 04,命令无法处理
//====================================================================
void ModbusSendDataDeal(uint16_t err)
{
	PARAMETER_DATA *PARA_ptr_uart = (void *)&Servo.Pn00.SoftVerion;
	uint16_t cycleReadDataStartIndex;                     // 循环数据开始地址
	uint16_t indexRead,indexWrite, group, grade;
	uint16_t pzdSaveData;
	uint16_t pzdDataSaveCmd = 0;
	int16_t i;

	sendFrame[0] = rcvFrame[0];   // 回复接收帧头前2位
	sendFrame[1] = rcvFrame[1];   // 回复接收帧头前2位
	commSendData.sendNumMax = 8;  // 发送数据长度

	if (err)
	{
		// 标准的MODBUS协议
		if (commProtocol)
		{
			sendFrame[1] = rcvFrame[1]+0x80;   // 回复接收帧头前2位
			sendFrame[2] = Modbus_Standard_ErrInfo[err];
			commSendData.sendNumMax = 5;      // 发送数据长度
		}
		// 非标准的MODBUS协议
		else
		{
			sendFrame[2] = 0x80;
			sendFrame[3] = 0x01;
			sendFrame[4] = 0x00;
			sendFrame[5] = err;
		}
	}
	else if (sciFlag.bit.write)             // 写数据操作处理。若有错误，则报错，不会真正写
	{
		sendFrame[2] = RTUhighAddr;
		sendFrame[3] = RTUlowAddr;
		sendFrame[4] = RTUhighData;
		sendFrame[5] = RTUlowData;
	}
	else if (sciFlag.bit.read)              // 通讯参数读取处理，真正需要读取
	{
		uint16_t sendNum;
		uint16_t readDataStartIndex;
		sendNum = commRcvData.commData << 1;

		// 标准的MODEBUS通讯协议
		if (commProtocol)
		{
			sendFrame[2] = sendNum;                 // 接收到的是功能码个数*2
			commSendData.sendNumMax = sendNum + 5;  // 最大发送字符个数
			readDataStartIndex = 3;
		}
		// 非标准MODBUS通讯协议
		else if (commProtocol == 0)
		{
			sendFrame[2] = sendNum >> 8;              // 功能码个数高位
			sendFrame[3] = sendNum & 0x00ff;          // 功能码个数低位
			commSendData.sendNumMax = sendNum + 6;    // 最大发送字符个数
			readDataStartIndex = 4;

		}
		if(SciSendMode == 2)
		{
		    for(i = commRcvData.commData - 1; i >= 0; i--)
		    {
		        uint16_t data_index = MotorParaOffset + i;
		        uint16_t data_value;

		        if(data_index < 65)
		        {
		            // 原有监控数据
		            data_value = slaver_dp_data[data_index];
		        }
		        else if(data_index < (65 + CUSTOM_DATA_COUNT))
		        {
		            // 自定义数据（减去偏移）
		            data_value = g_custom_data[data_index - MotorParaOffset];
		        }
		        else
		        {
		            // 超出范围，填充0
		            data_value = 0;
		        }

		        sendFrame[(i << 1) + readDataStartIndex] = (u8)((data_value & 0xFF00)>>8);
		        sendFrame[(i << 1) + readDataStartIndex + 1] = (u8)(data_value & 0x00FF);
		    }
		}
        else if(SciSendMode == 3)
        {
			// 读取的数据值
			for (i = commRcvData.commData - 1; i >= 0; i--)
			{
				sendFrame[(i << 1) + readDataStartIndex] = (u8)(((PARA_ptr_uart + MotorParaOffset+i)->Data & 0xFF00)>>8);//数据内容（高位）
				sendFrame[(i << 1) + readDataStartIndex + 1] = (u8)((PARA_ptr_uart + MotorParaOffset+i)->Data & 0x00FF);     //数据内容（低位）
			}
        }
	}
}


//====================================================================
//
// 通讯出错判断
// 返回: 0、通讯正常
//       1、通讯出错
//
//====================================================================
uint16_t ModbusCommErrCheck(void)
{
    if (commRcvData.rcvCrcErrCounter > DP_RCV_CRC_ERR_NUMBER)
    {
       // PROFIBUS CRC校验出错计数
       commRcvData.rcvCrcErrCounter = 0;           // 重新开始判断是否CRC校验出错
       return 1;
    }

    return 0;

}
//=====================================================================
//
// 通讯处理函数
//
//=====================================================================
void SciDeal(void)
{
	uint16_t commErrFlag;
    // 更新串口配置
    UpdateSciFormat();

    // 通讯出错检测
	// MODBUS检测方式为串口停顿时间超过通讯应答超时时间设置
	// PROFIBUS检测方式为CRC校验出错次数达到10次以上(PROFIBUS是否有必要这样处理)
    commErrFlag = protocolFunc[commType].CommErrCheck();
    // 通讯出错
    if (commErrFlag)
    {
        // 通讯出错处理
        commErrorDeal();     // 报故障并置串口为接收
    }
    else
    {
        // 通讯过程处理
        commStatusDeal();
    }
}
//=====================================================================
//
// 通讯接收中断函数
// modbus 中断
//=====================================================================

void SCI_RXD(void)
{
	uint8_t tmp;
    uart_get_char(modbus_uart_no,&tmp);//读串口数据 1位
    // 数据接收帧头判断
    if (protocolFunc[commType].StartDeal(tmp))
    {
#if 0
		// 为正常的接收数据  0-无效   1-广播地址    2-本机地址
		if (commRcvData.rcvFlag)
		{
	        // 非帧头通讯数据接收
	        CommDataReRcv(tmp);
		}
#endif
    }

    commTicker = 0;                     // 有接收数据，重新计时
}

//=====================================================================
//
// 通讯发送中断函数
//
// 发送一个字符完成，就进入该中断
//
//=====================================================================
void SCI_TXD(void)
{
	// 通讯发送数据
    CommDataSend();
    commTicker = 0;                     // 发送一个字符完成，重新计时
}

// 高优先级中断
void Lina_Level0_ISR(void)
{
	uint32_t LinL0IntVect;
    LinL0IntVect = uart_get_iir(modbus_uart_no);//获取接收中断标志位
	// 接收中断
	if((LinL0IntVect & IIR_RECV_DATA) == IIR_RECV_DATA)
	{
		if (commRcvData.rcvFlag == 0) //帧头判断
		{
			SCI_RXD();
		}
	}
	if((LinL0IntVect & IIR_CHAR_TIMEOUT) == IIR_CHAR_TIMEOUT)//空闲中断下，去读FIFO里面的接收数据
	{
		// 为正常的接收数据  0-无效   1-广播地址    2-本机地址
		if (commRcvData.rcvFlag)
		{
			// 非帧头通讯数据接收
			CommDataReRcv( );
		}
	}
	//  发送中断
	else if((LinL0IntVect & IIR_THR_EMPTY) == IIR_THR_EMPTY)//获取发送中断标志
	{
		SCI_TXD();
	}
}
//=====================================================================
//
// 通讯接收的数据处理函数
//
//=====================================================================
void CommRcvDataDeal(void)
{
	int16_t i, j;
	uint16_t *Comm_ptr = &ServoCommData.PositionDatah;
	PARAMETER_DATA *PARA_ptr_uart = (void *)&Servo.Pn00.SoftVerion;
	uint16_t writeErr;
	uint16_t gDataLen;
	// 不同协议的接收数据信息解析
	// 解析操作命令、地址、数据等信息
    protocolFunc[commType].RcvDataDeal();
    // 清SCI标志
    sciFlag.all = 0;

    // CRC校验
    if (commRcvData.crcRcv != CrcValueByteCalc(rcvFrame, commRcvData.crcSize))  // CRC校验故障判断
    {
        sciFlag.bit.crcChkErr = 1;                      // 置位：CRCErr、send
		commRcvData.rcvCrcErrCounter++;                 // 记录CRC校验出错次数
    }
     // 广播模式
    else if (!commRcvData.slaveAddr)
    {
		// 广播写操作
        if ((SCI_CMD_WRITE == commRcvData.commCmd)
          || (SCI_CMD_WRITE_RAM == commRcvData.commCmd))
        {
			// 置写标志
            sciFlag.bit.write = 1;
        }
        else
        {
            sciFlag.bit.cmdErr = 1;                                                 // 命令错误
        }
    }
    else //if (RTUslaveAddress == funcCode.code.commSlaveAddress) // 本机地址判断
    {
		if (SCI_CMD_READ == commRcvData.commCmd)       // 读命令操作
        {
            sciFlag.bit.read = 1;                           // 置位：read、send
        }
        else if ((SCI_CMD_WRITE == commRcvData.commCmd)
                || (SCI_CMD_WRITE_RAM == commRcvData.commCmd)
				|| (SCI_CMD_WRITE_MULT == commRcvData.commCmd))      // 写命令操作
        {
            sciFlag.bit.write = 1;
        }
        else
        {
            sciFlag.bit.cmdErr = 1;                                                 // 命令错误
        }
    }

    if(sciFlag.bit.read == 1)
    {
    	switch(commRcvData.commCmd)
    	{
			case SCI_CMD_READ:
				if(RTUhighAddr <= 4 && RTUlowAddr <= 255)
				{
					switch(RTUhighAddr)
					{
						 case 0:
							i = RTUlowAddr;
						 break;

						 case 1:
							i = Pn00_NUM + RTUlowAddr;
						 break;

						 case 2:
							i = Pn01_NUM + Pn00_NUM + RTUlowAddr;
						 break;

						 case 3:
							i = Pn02_NUM + Pn01_NUM + Pn00_NUM + RTUlowAddr;
						 break;

						 case 4:
							i = Pn03_NUM + Pn02_NUM + Pn01_NUM + Pn00_NUM + RTUlowAddr;
						 break;
						 default:break;
					}

					MotorParaOffset = i;
					MotorParaLength = (RTUhighData<<8) + RTUlowData;
					SciSendMode = 3;
				}
				if(RTUhighAddr == 5 && RTUlowAddr < (65 + CUSTOM_DATA_COUNT))				//xu改
				{
				    MotorParaOffset = RTUlowAddr;
				    MotorParaLength = (RTUhighData<<8) + RTUlowData;
				    SciSendMode = 2;

				    // 限制读取范围不超过数组边界
				    if((MotorParaOffset + MotorParaLength) > (65 + CUSTOM_DATA_COUNT))
				    {
				        MotorParaLength = (65 + CUSTOM_DATA_COUNT) - MotorParaOffset;
				    }
				}
				if(RTUhighAddr == 6 && RTUlowAddr <= 65)
				{
					MotorParaOffset = RTUlowAddr;//监控状态号
					MotorParaLength = (RTUhighData<<8) + RTUlowData;
					SciSendMode = 4; //伺服允许发送伺服监控状态
				}
				if(RTUhighAddr == 8 && RTUlowAddr == 20)
				{
					MotorParaOffset = 14;//监控状态号
					MotorParaLength = (RTUhighData<<8) + RTUlowData;
					SciSendMode = 2; //伺服允许发送伺服监控状态
				}
			break;
			default:break;
    	}
    }
    // 写数据处理
    if (sciFlag.bit.write)
    {
    	switch(commRcvData.commCmd)
    	{
			case SCI_CMD_WRITE://写一个字
				SciSendMode = 1;
				if(RTUhighAddr <= 4 && RTUlowAddr <= 255)
				{
					switch(RTUhighAddr)
					{
						 case 0:
								i = RTUlowAddr;
						 break;

						 case 1:
								i = Pn00_NUM + RTUlowAddr;
						 break;

						 case 2:
								i = Pn01_NUM + Pn00_NUM + RTUlowAddr;
						 break;

						 case 3:
								i = Pn02_NUM + Pn01_NUM + Pn00_NUM + RTUlowAddr;
						 break;

						 case 4:
								i = Pn03_NUM + Pn02_NUM + Pn01_NUM + Pn00_NUM + RTUlowAddr;
						 break;
						 default:break;
					 }
					 MotorParaOffset = i;
					(PARA_ptr_uart + i)->Data = (RTUhighData<<8) + RTUlowData;
					(PARA_ptr_uart + i)->attri.bit.Save = 1;

					//内部速度模式，轨迹规划功能使用
					if(Servo.Pn01.ContrlMode.Data == CTL_Pr) {
						if((RTUhighAddr == 4) && ((RTUlowAddr == 21) || (RTUlowAddr == 22)))
						{
							g_PosRefUpdateFlag = 1;	//位置信息有更新
						}
					}

					if (Servo.Pn01.ContrlMode.Data == CTL_Sr)
					{
						if((RTUhighAddr == 4) && (RTUlowAddr == 2))
						{
							speed_disp_sr = Servo.Pn04.SrSpeed.Data;
						}
					}

					if(Servo.Pn01.ServoON.attri.bit.Save == 1)Servo.Pn01.ServoON.attri.bit.Save = 0;//通讯时使能不保存

					if(Servo.Pn01.ContrlMode.Data == CTL_Sr ||
					   Servo.Pn01.ContrlMode.Data == CTL_JOG ||
					   Servo.Pn01.ContrlMode.Data == CTL_OL ||
					   Servo.Pn01.ContrlMode.Data == CTL_CO1 ||
					   Servo.Pn01.ContrlMode.Data == CTL_CO2 ||
					   Servo.Pn01.ContrlMode.Data == CTL_OP ||
					   Servo.Pn01.ContrlMode.Data == CTL_AUTO_Pr ||
					   Servo.Pn01.ContrlMode.Data == CTL_AUTO_TEST)
					{
						if(Servo.Pn01.ContrlMode.attri.bit.Save == 1)Servo.Pn01.ContrlMode.attri.bit.Save = 0;
					}
					if(Servo.Pn01.AutoHomeFlag.attri.bit.Save == 1)Servo.Pn01.AutoHomeFlag.attri.bit.Save = 0;
					if(Servo.Pn02.AbsaCtrlCmd.attri.bit.Save == 1)Servo.Pn02.AbsaCtrlCmd.attri.bit.Save = 0;
					if(Servo.Pn02.SpeedSaveFlag.Data == 1)
					{
					   Servo.Pn04.SpeedRef1.attri.bit.Save = 0;
					   Servo.Pn04.SpeedRef2.attri.bit.Save = 0;
					   Servo.Pn04.SpeedRef3.attri.bit.Save = 0;
					   Servo.Pn04.SpeedRef4.attri.bit.Save = 0;
					   Servo.Pn04.SpeedRef5.attri.bit.Save = 0;
					   Servo.Pn04.SpeedRef6.attri.bit.Save = 0;
					   Servo.Pn04.SpeedRef7.attri.bit.Save = 0;
					}
					rec_pa_modi_flag = 1;//参数修改标志
				}
				if(RTUhighAddr == 6 && RTUlowAddr <= 65)
				{
					MotorParaOffset = RTUlowAddr;
					*(Comm_ptr+MotorParaOffset) = (RTUhighData<<8) + RTUlowData;
				}
			break;
			case SCI_CMD_WRITE_MULT:
				SciSendMode = 1;
				gDataLen = (RTUhighNum<<8) + RTUlowNum;

				if(RTUhighAddr <= 4 && RTUlowAddr <= 255)
				{
					switch(RTUhighAddr)
					{
						case 0:
							i = RTUlowAddr;
						break;

						case 1:
							i = Pn00_NUM + RTUlowAddr;
						break;

						case 2:
							i = Pn01_NUM + Pn00_NUM + RTUlowAddr;
						break;

						case 3:
							i = Pn02_NUM + Pn01_NUM + Pn00_NUM + RTUlowAddr;
						break;

						case 4:
							i = Pn03_NUM + Pn02_NUM + Pn01_NUM + Pn00_NUM + RTUlowAddr;
						break;
						default:break;
					}
					  MotorParaOffset = i;
					  for(j = 0; j < gDataLen; j++)
					  {
							 (PARA_ptr_uart + i + j)->Data = (rcvFrame[7 + j * 2]<<8) + rcvFrame[8 + j * 2];
							 (PARA_ptr_uart + i + j)->attri.bit.Save = 1;
					  }

					  if(Servo.Pn01.ServoON.attri.bit.Save == 1)Servo.Pn01.ServoON.attri.bit.Save = 0;//通讯时使能不保存

					  if(Servo.Pn01.ContrlMode.Data == CTL_Sr ||
					   Servo.Pn01.ContrlMode.Data == CTL_JOG ||
					   Servo.Pn01.ContrlMode.Data == CTL_OL ||
					   Servo.Pn01.ContrlMode.Data == CTL_CO1 ||
					   Servo.Pn01.ContrlMode.Data == CTL_CO2 ||
					   Servo.Pn01.ContrlMode.Data == CTL_OP ||
					   Servo.Pn01.ContrlMode.Data == CTL_AUTO_Pr ||
					   Servo.Pn01.ContrlMode.Data == CTL_AUTO_TEST)
					 {
						if(Servo.Pn01.ContrlMode.attri.bit.Save == 1)Servo.Pn01.ContrlMode.attri.bit.Save = 0;
					 }
					 if(Servo.Pn01.AutoHomeFlag.attri.bit.Save == 1)Servo.Pn01.AutoHomeFlag.attri.bit.Save = 0;
					 if(Servo.Pn02.AbsaCtrlCmd.attri.bit.Save == 1)Servo.Pn02.AbsaCtrlCmd.attri.bit.Save = 0;
					 if(Servo.Pn02.SpeedSaveFlag.Data == 1)
					 {
						 Servo.Pn04.SpeedRef1.attri.bit.Save = 0;
						 Servo.Pn04.SpeedRef2.attri.bit.Save = 0;
						 Servo.Pn04.SpeedRef3.attri.bit.Save = 0;
						 Servo.Pn04.SpeedRef4.attri.bit.Save = 0;
						 Servo.Pn04.SpeedRef5.attri.bit.Save = 0;
						 Servo.Pn04.SpeedRef6.attri.bit.Save = 0;
						 Servo.Pn04.SpeedRef7.attri.bit.Save = 0;
					 }
					 rec_pa_modi_flag = 1;//参数修改标志
				 }
				if(RTUhighAddr == 6 && RTUlowAddr <= 65 && gDataLen == 2)
				{
					MotorParaOffset = RTUlowAddr;
					*(Comm_ptr+MotorParaOffset) = (rcvFrame[7]<<8) + rcvFrame[8];
					*(Comm_ptr+MotorParaOffset + 1) = (rcvFrame[9]<<8) + rcvFrame[10];
				}
			break;
			default:break;
    	}
#if 0
        // 写EEPROM
        if (SCI_CMD_WRITE == commRcvData.commCmd)
        {
            commRcvData.commCmdSaveEeprom = SCI_WRITE_WITH_EEPROM;
        }
#endif
#if 0 //ma
        {
            writeErr = CommWrite(commRcvData.commAddr, commRcvData.commData);
        }
#endif
        // 写失败
        if (writeErr)
        {
			// 标示写失败故障
            sciFlag.all |= (0x0001 << COMM_ERR_INDEX[writeErr - 1]);
        }
    }

}

//=====================================================================
//
// 数据接收处理后故障整理
//
//=====================================================================
uint16_t SciErrCheck(void)
{
	uint16_t readErr;
	uint16_t operateErr;

	// 初值置无故障
	operateErr = COMM_ERR_NONE;
#if 0 //ma
    // 通讯读命令
    if (sciFlag.bit.read)               // 通讯参数读取处理
    {
        if(commRcvData.commData > RTU_READ_DATA_NUM_MAX)    // 最大读取12个数据
        {
            sciFlag.bit.paraOver = 1;   //  参数错误故障
        }
        else
        {
            readErr = CommRead(commRcvData.commAddr, commRcvData.commData);
            if (readErr)
            {
				// 数据读取. 如果错误，置故障位，不需要真正的读取
                sciFlag.all |= (0x0001 << COMM_ERR_INDEX[readErr - 1]);
            }
        }
    }

	// 故障信息处理
    if (sciFlag.bit.pwdErr)                 // 密码错误：Err01
    {
        operateErr = COMM_ERR_PWD;
    }
    else if (sciFlag.bit.cmdErr)            // 读写命令错误：Err02
    {
        operateErr = COMM_ERR_CMD;
    }
    else if (sciFlag.bit.crcChkErr)         // CRC校验错误: Err03
    {
        operateErr = COMM_ERR_CRC;
    }
    else if (sciFlag.bit.addrOver)          // 功能码无效地址：Err04
    {
        operateErr = COMM_ERR_ADDR;
    }
    else if (sciFlag.bit.paraOver)          // 功能码无效参数：Err05
    {
        operateErr = COMM_ERR_PARA;
    }
    else if (sciFlag.bit.paraReadOnly)      // 参数更改无效：Err06
    {
        operateErr = COMM_ERR_READ_ONLY;
    }
    else if (sciFlag.bit.systemLocked)      // 系统锁定：返回0x0007
    {
        operateErr = COMM_ERR_SYSTEM_LOCKED;
    }
#if 1   // 目前eeprom储存机制下，不会有该错误，但保险起见，还是保留
    else if (sciFlag.bit.saveFunccodeBusy)  // 正在存储参数：返回0x0008
    {
        operateErr = COMM_ERR_SAVE_FUNCCODE_BUSY;
    }
#endif
#endif
	return operateErr;
}
//=====================================================================
//
// 通讯发送数据处理函数
//
//=====================================================================
void CommSendDataDeal(void)
{
	uint16_t error;
	uint16_t crcSend;

    // 判断通讯读写操作故障
    error = SciErrCheck();

    // 准备协议发送数据
    protocolFunc[commType].SendDataDeal(error);

    // 准备CRC校验数据
    crcSend = CrcValueByteCalc(sendFrame, commSendData.sendNumMax - 2);
    sendFrame[commSendData.sendNumMax - 2] = crcSend & 0x00ff;    // CRC低位在前
    sendFrame[commSendData.sendNumMax - 1] = crcSend >> 8;
}


//=====================================================================
//
// 通讯中断发送触发函数
//
//=====================================================================
void  CommStartSend(void)
{
   uart_send_char(modbus_uart_no,(uint8_t)sendFrame[0]);  // 发送第一个数据
}
//=====================================================================
//
// 通讯数据接收配置
//

void closeRTX(void)
{
	uart_tx_halt_en(modbus_uart_no);
}

void setRxConfig(void)
{
	uart_tx_halt_en(modbus_uart_no);
}

void setTxConfig(void)
{
	uart_tx_halt_dis(modbus_uart_no);
}
//====================================================================
//
// 通讯出错处理
//
//===================================================================
void commErrorDeal(void)
{
    commStatus = SCI_RECEIVE_DATA;        // 置为接收状态
    SET_RTS_R;  // RTS = RS485_R;         // RTS置为接收
    commRcvData.rcvNum = 0;                       // 长时间没有收完，帧头判断复位
    commRcvData.rcvFlag = 0;
    setRxConfig();
}
//====================================================================
//
// 通讯状态处理
//
//===================================================================
void commStatusDeal(void)
{
	uint32_t uart_sts;
    switch (commStatus)
    {
        // 接收数据
        case SCI_RECEIVE_DATA:
            SET_RTS_R;             // RTS = RS485_R;   // RTS置为接收,防止状态不对
            setRxConfig();
            uart_txd_int_dis(modbus_uart_no);  //禁止串口发送中断
        	uart_rxd_int_en(modbus_uart_no);   //允许串口接收中断
        break;

        case SCI_RECEIVE_OK:
            CommRcvDataDeal();
            // 返回数据
            if ((commRcvData.slaveAddr)              // 非广播
                && (!sciFlag.bit.crcChkErr))         // CRC校验成功或为PROFIBUS协议
            {
                CommSendDataDeal();                 // 发送数据准备
                commStatus = SCI_SEND_DATA_PREPARE; // 接收处理完成，准备发送
            }
            else                                    // 广播，DSP响应之后不发送，继续接收
            {
                commStatus = SCI_RECEIVE_DATA;
                SET_RTS_R;  // RTS = RS485_R;       // RTS置为接收
                setRxConfig();
                uart_txd_int_dis(modbus_uart_no);  //禁止串口发送中断
                uart_rxd_int_en(modbus_uart_no);   //允许串口接收中断
            }
		break;
        // 发送数据准备
        case SCI_SEND_DATA_PREPARE:
            if ((commTicker >= commRcvData.delay)               // 应答延迟
                && (commTicker > commRcvData.frameSpaceTime))   // MODBUS为3.5个字符时间
            {
                SET_RTS_T;  // RTS = RS485_T;
                // RTS置为发送
                setTxConfig();
                commStatus = SCI_SEND_DATA;
                commSendData.sendNum = 1;              // 当前发送数据个数置为1
                CommStartSend();                       // 开始发送
				uart_rxd_int_dis(modbus_uart_no);      //禁止串口接收中断
				uart_txd_int_en(modbus_uart_no);       //允许串口发送中断
                commSendTicker = 0;
            }
        break;
        // 发送数据
        case SCI_SEND_DATA:
            commSendTicker++;
            SET_RTS_T;  // RTS = RS485_T;     // RTS置为发送,防止状态不对
            setTxConfig();
            uart_rxd_int_dis(modbus_uart_no);      //禁止串口接收中断
            uart_txd_int_en(modbus_uart_no);       //允许串口发送中断
            // 长时间数据发送不成功(1.5倍)
            if (commSendTicker >= ((uint32_t)825L*commSendData.sendNumMax/(commBaudRate*10) + 1))   // *2ms
            {
                commStatus = SCI_SEND_OK;
            }
        break;
        // 发送数据OK
        case SCI_SEND_OK:
        {
			uart_sts = uart_get_lsr(modbus_uart_no);
			if((uart_sts & 0x00000040) == 0x00000040)   // Transmitter empty flag, 真正发送完毕
			{
				commStatus = SCI_RECEIVE_DATA;  // 发送完毕后，置为接收状态
				SET_RTS_R;  // RTS = RS485_R;   // RTS置为接收
				setRxConfig();
				uart_txd_int_dis(modbus_uart_no);  //禁止串口发送中断
				uart_rxd_int_en(modbus_uart_no);   //允许串口接收中断
			}
            break;
        }
        default: break;
    }
}
//====================================================================
//
// 通讯数据接收处理
//
//===================================================================
void CommDataReRcv(void)
{
	uint8_t len;
	uint8_t tmp;
	len = uart_get_rfl(modbus_uart_no);
	commRcvData.rcvNumMax = len + 1;//FIFO接收到的字节个数+帧头的一个字节
	if (commRcvData.rcvNum < commRcvData.rcvNumMax)  // 接收一帧数据还没有完成
	{
		for(int i=commRcvData.rcvNum;i<commRcvData.rcvNumMax;i++)
		{

			uart_get_char(modbus_uart_no,(u8*)&tmp);//读串口数据
			rcvFrame[commRcvData.rcvNum++] = tmp;

		}
	}
	if (commRcvData.rcvNum >= commRcvData.rcvNumMax) // 接收一帧数据完成
	{
		// PROFIBUS置帧头判断标志
		commRcvData.rcvDataJuageFlag = 0;
		if (2 == commRcvData.rcvFlag)                // 本机地址才返回(DSP切换成发送状态)
		{
			uart_tx_halt_dis(modbus_uart_no);
			//禁止下一次接收
			uart_rxd_int_dis(modbus_uart_no);     //禁止串口接收中断
			uart_txd_int_dis(modbus_uart_no);     //禁止串口发送中断，不使能
		}
		commStatus = SCI_RECEIVE_OK;            // 标志接收数据完成
		commRcvData.rcvFlag = 0;
	}
}


//====================================================================
//
// 通讯数据发送处理
//
//===================================================================
void CommDataSend(void)
{
	 // 发送一帧数据没有完成
    if (commSendData.sendNum< commSendData.sendNumMax)
    {
    	for(int i=commSendData.sendNum;i<commSendData.sendNumMax;i++)
    	{
    		uart_send_char(modbus_uart_no,(uint8_t)sendFrame[commSendData.sendNum++]);
    	}
    }
	// 发送一帧数据全部完成
    else if (commSendData.sendNum >= commSendData.sendNumMax)
    {
		// 标志发送数据完成
        commStatus = SCI_SEND_OK;
    }
}

void uart_init(u8 index, UART_CFG_PARA *uart_cfg_para)
{
	uart_tx_halt_en(index);
	uart_div_latch_access(index);

	uart_set_div_dlh(index, (uart_cfg_para->baud_rate_div)>>8);
	uart_set_div_dll(index, (uart_cfg_para->baud_rate_div)&0xff);

	uart_div_latch_clear(index);
	uart_tx_halt_dis(index);

	uart_set_op_para(index, uart_cfg_para);

	uart_fifo_cfg(index, &uart_cfg_para->fifo_cfg);

	uart_set_rx_enable(index);
}
//=====================================================================
//
// 通讯初始化
//
//=====================================================================
void uart_para_int(u8 index)
{
	uint32_t div;
	UART_CFG_PARA uart_para;
	//3、配置参数
	switch(Servo.Pn03.CommBaudRate.Data)
	{
		case 0:
			div = uart_get_br_div(index, 4800);
		break;
		case 1:
			div = uart_get_br_div(index, 9600);
		break;
		case 2:
			div = uart_get_br_div(index, 19200);
		break;
		case 3:
			div = uart_get_br_div(index, 38400);
		break;
		case 4:
			div = uart_get_br_div(index, 57600);
		break;
		case 5:
			div = uart_get_br_div(index, 115200);
		break;
		case 6:
			div = uart_get_br_div(index, 128000);
		break;
		case 7:
			div = uart_get_br_div(index, 256000);
		break;
		case 8:
			div = uart_get_br_div(index, 1000000);
		break;
		case 9:
			div = uart_get_br_div(index, 2000000);
		break;
		default:
			div = uart_get_br_div(index, 115200);
		break;
	}
	switch(Servo.Pn03.CommProtocol.Data)
	{
		 case 0:  //1 + 8 + N +1
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE0;
			 uart_para.parity_fun 	= UART_PARITY_DIS;
			 uart_para.parity_mod 	= UART_PARITY_MOD0;
		 break;
		 case 1://1 + 8 + O +1
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE0;
			 uart_para.parity_fun 	= UART_PARITY_EN;
			 uart_para.parity_mod 	= UART_PARITY_MOD0;
		 break;
		 case 2://1 + 8 + E +1
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE0;
			 uart_para.parity_fun 	= UART_PARITY_EN;
			 uart_para.parity_mod 	= UART_PARITY_MOD1;
		 break;
		 case 3://1 + 8 + N +2
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE1;
			 uart_para.parity_fun 	= UART_PARITY_DIS;
			 uart_para.parity_mod 	= UART_PARITY_MOD0;
		 break;
		 case 4://1 + 8 + O + 2
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE1;
			 uart_para.parity_fun 	= UART_PARITY_EN;
			 uart_para.parity_mod 	= UART_PARITY_MOD0;
		 break;
		 case 5://1 + 8 + E + 2
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE1;
			 uart_para.parity_fun 	= UART_PARITY_EN;
			 uart_para.parity_mod 	= UART_PARITY_MOD1;
		 break;

		 default:
			 uart_para.data_length = UART_DLS_8;
			 uart_para.stop_bit 	= UART_STOP_TYPE0;
			 uart_para.parity_fun 	= UART_PARITY_DIS;
			 uart_para.parity_mod 	= UART_PARITY_MOD0;
		 break;
	}
	uart_para.baud_rate_div = div;
    uart_para.fifo_cfg.FIFOE        = 0x01;
    uart_para.fifo_cfg.RXFIFOR      = 0x01;
	uart_para.fifo_cfg.TXFIFOR      = 0x01;
	uart_para.fifo_cfg.DMAM         = 0x00;
	uart_para.fifo_cfg.TFT          = TX_EMPTY;
	uart_para.fifo_cfg.RT           = RX_FULL;  //FIFO长度用256
	uart_init(index, &uart_para);
}
void modbus_rtu_init(u8 index)
{
	// 应该放在前面
	commStatus = SCI_RECEIVE_DATA;              // 接收状态
	SET_RTS_R;  // RTS = RS485_R;               // RTS置为接收
	//1、UART CMU使能
	//**************************************
	uart_set_cmu(index);

	uart_para_int(index);
	uart_rxd_int_en(index);        //允许串口接收中断
	uart_txd_int_dis(index);       //禁止串口发送中断
	uart_txd_shift_empty_int_en(index);

	// 配置为数据接收
	setRxConfig();  //禁止发送

	uart_irq_register(index,Lina_Level0_ISR);//使能并注册串口中断
}
void InitSetScia(void)
{
#if MODBUS_485
    modbus_rtu_init(modbus_uart_no);                            //modbus RTU串口初始化,2线通讯方式
#else
    SET_RTS_T  //串口7用于调试打印输出时，485方向信号直接给高电平
    init_uart_dbg(modbus_uart_no);
#endif

}
//=====================================================================
//
// SCI通讯参数修改函数
//
//=====================================================================
void UpdateSciFormat(void)
{
	uint32_t uart_sts = 0;
	// 更新通讯配置文件
	protocolFunc[commType].UpdateCommFormat(dspBaudRegData[Servo.Pn03.CommBaudRate.Data].baudRate);
#if 0 //ma
	// 出现接收故障时处理
    uart_sts = uart_get_lsr(modbus_uart_no);
	if((uart_sts & 0x0000001E) != 0)//有通讯错误,重新初始化串口
	{
		InitSetScia();   // 初始化SCI寄存器
	}
	uart_para_int(modbus_uart_no);
#endif
}
void InitSciaGpio(void)
{
	//1、UART GPIO PINMUX配置
	//**************************************
	gpio_enable(GPIO_GRP_G, 12, 2, GPIO_FUN_2);      //选择UART1
	gpio_enable(GPIO_GRP_G, 14, 1, GPIO_FUN_O);      //485RTDSP
}
void InitScia(void)
{
	InitSciaGpio();
	InitSetScia();
}
