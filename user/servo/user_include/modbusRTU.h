/*
 * modbusRTU.h
 *
 *  Created on: 2024年2月29日
 *      Author: L
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_MODBUSRTU_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_MODBUSRTU_H_
#include "all_inc.h"
#include "M680x_it.h"
// MODBUS协议
#define RTUslaveAddress rcvFrame[0]      // RTU帧的从机地址
#define RTUcmd          rcvFrame[1]      // RTU帧的命令字
#define RTUhighAddr     rcvFrame[2]      // RTU帧的地址高字节
#define RTUlowAddr      rcvFrame[3]      // RTU帧的地址低字节
#define RTUhighData     rcvFrame[4]      // RTU帧的数据高字节
#define RTUlowData      rcvFrame[5]      // RTU帧的数据低字节
#define RTUlowCrc       rcvFrame[6]      // RTU帧的CRC校验低字节
#define RTUhighCrc      rcvFrame[7]      // RTU帧的CRC校验高字节

#define RTUhighNum      rcvFrame[4]      // RTU连续帧的数量高字节
#define RTUlowNum       rcvFrame[5]      // RTU连续帧的数量低字节
#define RTUByteCount    rcvFrame[6]      // RTU连续帧的字节计数

#define SCI_CMD_READ                0x03
#define SCI_CMD_WRITE               0x06
#define SCI_CMD_WRITE_RAM           0x07
#define SCI_CMD_WRITE_MULT          0x10
#define RTU_READ_DATA_NUM_MAX       100    // 最多读取数据个数
#define RTU_WRITE_DATA_NUM_MAX      100    // 最多写数据个数
#define BAUD_NUM_MAX                8   // 波特率选择范围的最大值
#define COMM_ERR_NONE               0   //
#define COMM_ERR_PWD                1   // 密码错误
#define COMM_ERR_CMD                2   // 读写命令错误
#define COMM_ERR_CRC                3   // CRC校验错误
#define COMM_ERR_ADDR               4   // 无效地址
#define COMM_ERR_PARA               5   // 无效参数
#define COMM_ERR_READ_ONLY          6   // 参数更改无效
#define COMM_ERR_SYSTEM_LOCKED      7   // 系统锁定
#define COMM_ERR_SAVE_FUNCCODE_BUSY 8   // 正在存储参数

#define CUSTOM_DATA_COUNT 60
extern uint16_t g_custom_data[CUSTOM_DATA_COUNT];
// 通讯波特率对应的的寄存器值
typedef struct
{
	uint16_t baudRate;    // _*100bps

	uint16_t high;
	uint16_t low;
	uint16_t M;
} DSP_BAUD_REGISTER_DATA;
// 通讯标志字
struct SCI_FLAG_BITS
{                                   // bits  description
	uint16_t read:1;                  // 0    读取功能标志位
	uint16_t write:1;                 // 1    写功能码标志位
	uint16_t crcChkErr:1;             // 2    CRC校验故障 Err3
	uint16_t rcvDataEnd:1;            // 3

	uint16_t send:1;                  // 4    有数据发送标志位，区别广播模式和非广播模式，目前未使用
	uint16_t sendDataStart:1;         // 5
	uint16_t paraOver:1;              // 6    无效参数 Err5
	uint16_t addrOver:1;              // 7    无效地址 Err4

	uint16_t cmdErr:1;                // 8    读写命令错误 Err2
	uint16_t paraReadOnly:1;          // 9    参数更改无效。参数只读，不能修改错误 Err6
	uint16_t pwdErr:1;                // 10   密码输入错误 Err1
	uint16_t pwdPass:1;               // 11   密码校验通过

	uint16_t systemLocked:1;          // 12   系统锁定 Err7
	uint16_t saveFunccodeBusy:1;      // 13   正在储存功能码 Err8
	uint16_t ExKeyBoardRead:1;        // 14   当前为外引键盘通讯读
	uint16_t ExKeyBoardWrite:1;       // 15   当前为外引键盘通讯写
};

union SCI_FLAG
{
	uint16_t               all;
    struct SCI_FLAG_BITS bit;
};
enum COMM_STATUS
{
    SCI_RECEIVE_DATA,            // SCI接收数据
    SCI_RECEIVE_OK,              // SCI接收数据完毕
    SCI_SEND_DATA_PREPARE,       // 准备发送数据
    SCI_SEND_DATA,               // SCI发送数据
    SCI_SEND_OK                  // SCI发送数据完毕
};
// 通讯波特率对应的的寄存器值
typedef struct
{
	uint16_t slaveAddr;
    uint16_t commAddr;    // _*100bps
    uint16_t commData;
    uint16_t rcvNum;
    uint16_t rcvFlag;
    uint16_t crcRcv;
    uint16_t commCmd;
    uint16_t crcSize;
    uint16_t rcvNumMax;
    uint16_t frameSpaceTime;
    uint16_t delay;
    uint16_t rcvCrcErrCounter;
    uint16_t rcvDataJuageFlag;
    uint16_t commCmdSaveEeprom;
    uint16_t dpOrModbus;
    uint16_t DpFlag1;
    uint16_t moreWriteNum; // 多写字节�
} COMM_RCV_DATA;


typedef struct
{
    uint16_t sendNumMax;
    uint16_t sendNum;
    uint16_t commData;
    uint16_t crcRcv;
    uint16_t commCmd;
    uint16_t crcSize;
} COMM_SEND_DATA;
typedef struct CommProtocolDeal
{
    void (*RcvDataDeal)(); // 接收数据处理
    uint16_t (*StartDeal)(uint16_t); // 帧头判断
    void (*UpdateCommFormat)(uint16_t); // 更新通讯配置
    void (*SendDataDeal)(uint16_t); // 发送数据处理
    uint16_t (*CommErrCheck)(); // 通讯出错
}protocolDeal;
extern int16_t  MotorParaOffset;
extern int16_t  rec_pa_modi_flag;
extern uint32_t modbus_uart_no;
extern COMM_RCV_DATA commRcvData;
extern COMM_SEND_DATA commSendData;
extern uint16_t sendFrame[200];                           // 从机响应帧
extern uint16_t rcvFrame[100];                            // 接收数据数组(主机命令帧)
extern uint16_t commReadData[RTU_READ_DATA_NUM_MAX];
extern uint32_t commTicker;
extern uint16_t commProtocol;             // 通讯协议数据格式
extern union SCI_FLAG sciFlag;
uint16_t CrcValueByteCalc(const uint16_t *data, uint16_t length);
void uart_init(u8 index, UART_CFG_PARA *uart_cfg_para);
extern void InitScia(void);
extern void SciDeal(void);
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_MODBUSRTU_H_ */
