/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#include <all_inc.h>

#ifndef INCLUDE_HAL_I2C_H_
#define INCLUDE_HAL_I2C_H_

#define     FS_MIN_SCL_HIGH         600
#define     FS_MIN_SCL_LOW          1300
#define     SS_MIN_SCL_HIGH         4000
#define     SS_MIN_SCL_LOW          4700
#define     CLK_M                   1000000
#define     CLK_N                   1000

#define     MASTER_READ                (0x1 << 8)
#define     MASTER_WRITE               (0x0 << 8)
#define     STOP_CMD                   (0x1 << 9)
#define     NO_STOP_CMD                (0x0 << 9)
#define     RESTART_CMD                (0x1 << 10)

typedef enum tx_mode{
    i2c_tx_target = 0x0,        // normal transfer using target address
    i2c_tx_gen_call = 0x2,      // issue a general call
    i2c_tx_start = 0x3
}tx_mode_t;

typedef enum speed_mode{
    STANDARD_MODE = 0x1,        // 100Kb/s
    FAST_MODE = 0x2,            // 400Kb/s
}speed_mode_t;

typedef enum address{
    ADDRESS_7BIT = 0x0,
    ADDRESS_10BIT = 0x1,
}address_t;


union I2C_CTL_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 MASTER_MODE_EN:1;                  //0     I2C_MASTER_MODE_ENABLE
                volatile u32 SLAVE_MODE_DIS:1;                  //1     I2C_SLAVE_MODE_DISABLE
                volatile u32 ADDR10BIT_SEL_MASTER:1;            //2     I2C_10BITADDR_SELECT_MASTER
                volatile u32 ADDR10BIT_SEL_SLAVE:1;             //3     I2C_10BITADDR_SELECT_SLAVE
                volatile u32 SPEED_MODE_SEL:2;                  //5:4   I2C_SPEED_MODE_SELECT
                volatile u32 RESTART_EN:1;                      //6     I2C_RESTART_ENABLE
                volatile u32 STOP_DET_IFADDR:1;                 //7     I2C_STOP_DET_IFADDRESSED
                volatile u32 TX_EMPTY_CTL:1;                    //8     I2C_TX_EMPTY_CTL
                volatile u32 RXFIFO_FULL_HLD_CTL:1;             //9     I2C_RX_FIFO_FULL_HLD_CTL
                volatile u32 BUS_CLR_FEATURE_CTL:1;             //10    I2C_BUS_CLEAR_FEATURE_CTL
                volatile u32 rsvd0:21;                          //31:11 Reserved
        }bit;
};

union I2C_TAR_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_TAR:10;                        //9:0   I2C_TAR
                volatile u32 SB_GC_CTL:2;                       //10    I2C_START_BYTE_CTL 11 I2C_GEN_CALL_CTL
                volatile u32 rsvd0:20;                          //31:12 Reserved
        }bit;
};

union I2C_SAR_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_SAR:10;                        //9:0   I2C_SAR
                volatile u32 rsvd0:22;                          //31:10 Reserved
        }bit;
};

union I2C_ACK_GEN_CALL_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 ACK_GEN_CALL:1;                    //0     I2C_ACK_GEN_CALL
                volatile u32 rsvd0:31;                          //31:1  Reserved
        }bit;
};

union I2C_DATA_CMD_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 DAT_CMD_STOP_RS:11;                //10:0  I2C_DATA_CMD
                volatile u32 rsvd0:21;                          //31:11 Reserved
        }bit;
};

union I2C_SS_SCL_HCNT_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_SS_SCL_HCNT:16;                //15:0  I2C_SS_SCL_HCNT
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union I2C_SS_SCL_LCNT_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_SS_SCL_LCNT:16;                //15:0  I2C_SS_SCL_LCNT
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union I2C_FS_SCL_HCNT_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_FS_SCL_HCNT:16;                //15:0  I2C_FS_SCL_HCNT
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union I2C_FS_SCL_LCNT_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_FS_SCL_LCNT:16;                //15:0  I2C_FS_SCL_LCNT
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union I2C_SDA_HOLD_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_SDA_TX_HOLD:16;                //15:0  I2C_SDA_TX_HOLD
                volatile u32 I2C_SDA_RX_HOLD:8;                 //23:16 I2C_SDA_RX_HOLD
                volatile u32 rsvd0:8;                           //31:24 Reserved
        }bit;
};

union I2C_SDA_SETUP_REG {
        volatile u32  all;
        struct{                                                 //bit description
                volatile u32 I2C_SDA_SETUP:8;                   //7:0   I2C_SDA_SETUP
                volatile u32 rsvd0:24;                          //31:8  Reserved
        }bit;
};

union I2C_INTR_MASK_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 M_RX_UNDER:1;                      //0     I2C_M_RX_UNDER
		volatile u32 rsvd0:1;                           //1     Reserved
		volatile u32 M_RX_FULL:1;                       //2     I2C_M_RX_FULL
		volatile u32 rsvd1:1;                           //3     Reserved
		volatile u32 M_TX_EMPTY:1;                      //4     I2C_M_TX_EMPTY
		volatile u32 M_RD_REQ:1;                        //5     I2C_M_RD_REQ
		volatile u32 M_TX_ABRT:1;                       //6     I2C_M_TX_ABRT
		volatile u32 M_RX_DONE:1;                       //7     I2C_M_RX_DONE
		volatile u32 M_ACTIVITY:1;                      //8     I2C_M_ACTIVITY
		volatile u32 M_STOP_DET:1;                      //9     I2C_M_STOP_DET
		volatile u32 M_START_DET:1;                     //10    I2C_M_START_DET
		volatile u32 M_GEN_CALL:1;                      //11    I2C_M_GEN_CALL
		volatile u32 rsvd2:1;                           //12    Reserved
		volatile u32 M_MASTER_ON_HOLD:1;                //13    I2C_M_MASTER_ON_HOLD
		volatile u32 M_SCL_STUCK_AT_LOW:1;              //14    I2C_M_SCL_STUCK_AT_LOW
		volatile u32 rsvd3:17;                          //31:15 Reserved
        }bit;
};

union I2C_INTR_CLR_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 C_RX_UNDER:1;                      //0     I2C_CLR_RX_UNDER
		volatile u32 rsvd0:4;                           //4:1   Reserved
		volatile u32 C_RD_REQ:1;                        //5     I2C_CLR_RD_REQ
		volatile u32 C_TX_ABRT:1;                       //6     I2C_CLR_TX_ABRT
		volatile u32 C_RX_DONE:1;                       //7     I2C_CLR_RX_DONE
		volatile u32 C_ACTIVITY:1;                      //8     I2C_CLR_ACTIVITY
		volatile u32 C_STOP_DET:1;                      //9     I2C_CLR_STOP_DET
		volatile u32 C_START_DET:1;                     //10    I2C_CLR_START_DET
		volatile u32 C_GEN_CALL:1;                      //11    I2C_CLR_GEN_CALL
		volatile u32 rsvd2:2;                           //13:12 Reserved
		volatile u32 C_SCL_STUCK_AT_LOW:1;              //14    I2C_CLR_SCL_STUCK_AT_LOW
		volatile u32 rsvd3:17;                          //31:15 Reserved
        }bit;
};

union I2C_RAW_INTR_STAT_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 RX_UNDER:1;                        //0     I2C_RX_UNDER
		volatile u32 rsvd0:1;                           //1     Reserved
		volatile u32 RX_FULL:1;                         //2     I2C_RX_FULL
		volatile u32 rsvd1:1;                           //3     Reserved
		volatile u32 TX_EMPTY:1;                        //4     I2C_TX_EMPTY
		volatile u32 RD_REQ:1;                          //5     I2C_RD_REQ
		volatile u32 TX_ABRT:1;                         //6     I2C_TX_ABRT
		volatile u32 RX_DONE:1;                         //7     I2C_RX_DONE
		volatile u32 ACTIVITY:1;                        //8     I2C_ACTIVITY
		volatile u32 STOP_DET:1;                        //9     I2C_STOP_DET
		volatile u32 START_DET:1;                       //10    I2C_START_DET
		volatile u32 GEN_CALL:1;                        //11    I2C_GEN_CALL
		volatile u32 rsvd2:1;                           //12    Reserved
		volatile u32 MASTER_ON_HOLD:1;                  //13    I2C_MASTER_ON_HOLD
		volatile u32 SCL_STUCK_AT_LOW:1;                //14    I2C_SCL_STUCK_AT_LOW
		volatile u32 rsvd3:17;                          //31:15 Reserved
        }bit;
};

union I2C_ENABLE_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 ENABLE:1;                          //0     I2C_ENABLE
		volatile u32 ABORT:1;                           //1     I2C_ABORT
		volatile u32 TX_CMD_BLOCK:1;                    //2     I2C_TX_CMD_BLOCK
		volatile u32 SDA_STUCK_REC_EN:1;                //3     I2C_SDA_STUCK_RECOVERY_ENABLE
		volatile u32 rsvd0:28;                          //31:4  Reserved
        }bit;
};

union I2C_ENABLE_STATUS_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 I2C_EN_STATUS:1;                   //0     I2C_EN_STATUS
		volatile u32 SLV_DIS_WHILE_BUSY:1;              //1     I2C_SLV_DISABLED_WHILE_BUSY
		volatile u32 SLV_RX_DATA_LOST:1;                //2     I2C_SLV_RX_DATA_LOST
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

union I2C_STATUS_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 ACTIVITY:1;                        //0     I2C_ACTIVITY
		volatile u32 TFNF:1;                            //1     I2C_TX FIFO NOT FULL
		volatile u32 TFE:1;                             //2     I2C_TX FIFO EMPTY
		volatile u32 RFNE:1;                            //3     I2C_RX FIFO NOT EMPTY
		volatile u32 RFF:1;                             //4     I2C_RX FIFO FULL
		volatile u32 MST_ACTIVITY:1;                    //5     I2C_MST_ACTIVITY
		volatile u32 SLV_ACTIVITY:1;                    //6     I2C_SLV_ACTIVITY
		volatile u32 MST_HOLD_TXFIFO_EMPTY:1;           //7     I2C_MST_HOLD_TX_FIFO_EMPTY
		volatile u32 MST_HOLD_RXFIFO_FULL:1;            //8     I2C_MST_HOLD_RX_FIFO_FULL
		volatile u32 SLV_HOLD_TXFIFO_EMPTY:1;           //9     I2C_SLV_HOLD_TX_FIFO_EMPTY
		volatile u32 SLV_HOLD_RXFIFO_FULL:1;            //10    I2C_SLV_HOLD_RX_FIFO_FULL
		volatile u32 SDA_STUCK_NOT_REC:1;               //11    I2C_SDA_STUCK_NOT_RECOVERED
		volatile u32 rsvd0:20;                          //31:12 Reserved
        }bit;
};

union I2C_TX_ABRT_SOURCE_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 ABRT_7BADDR_NOACK:1;               //0     I2C_ABRT_7B_ADDR_NOACK
		volatile u32 ABRT_10BADDR1_NOACK:1;             //1     I2C_ABRT_10ADDR1_NOACK
		volatile u32 ABRT_10BADDR2_NOACK:1;             //2     I2C_ABRT_10ADDR2_NOACK
		volatile u32 ABRT_TXDATA_NOACK:1;               //3     I2C_ABRT_TXDATA_NOACK
		volatile u32 ABRT_GCALL_NOACK:1;                //4     I2C_ABRT_GCALL_NOACK
		volatile u32 ABRT_GCALL_READ:1;                 //5     I2C_ABRT_GCALL_READ
		volatile u32 rsvd0:1;                           //6     Reserved
		volatile u32 ABRT_SBYTE_ACKDET:1;               //7     I2C_ABRT_SBYTE_ACKDET
		volatile u32 rsvd1:1;                           //8     Reserved
		volatile u32 ABRT_SBYTE_NORSTRT:1;              //9     I2C_ABRT_SBYTE_NORSTRT
		volatile u32 ABRT_10BRD_NORSTRT:1;              //10    I2C_ABRT_10B_RD_NORSTRT
		volatile u32 ABRT_MASTER_DIS:1;                 //11    I2C_ABRT_MASTER_DIS
		volatile u32 ABRT_LOST:1;                       //12    I2C_ABRT_LOST
		volatile u32 ABRT_SLV_FLUSH_TXF:1;              //13    I2C_ABRT_SLVFLUSH_TXFIFO
		volatile u32 ABRT_SLV_ARBLOST:1;                //14    I2C_ABRT_SLV_ARBLOST
		volatile u32 ABRT_SLV_RDINTX:1;                 //15    I2C_ABRT_SLVRD_INTX
		volatile u32 ABRT_USR_ABRT:1;                   //16    I2C_ABRT_USER_ABRT
		volatile u32 ABRT_SDA_STUCK_LOW:1;              //17    I2C_ABRT_SDA_STUCK_AT_LOW
		volatile u32 rsvd2:5;                           //22:18 Reserved
		volatile u32 TX_FLUSH_CNT:9;                    //31:23 I2C_TX_FLUSH_CNT
        }bit;
};

union I2C_RX_TL_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 RX_TL:3;                           //2:0   I2C_RX_TL
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

union I2C_TX_TL_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 TX_TL:3;                           //2:0   I2C_TX_TL
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

union I2C_TXFLR_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 TXFLR:3;	                        //2:0   I2C_TXFLR
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

union I2C_RXFLR_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 RXFLR:3;                           //2:0   I2C_RXFLR
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

union I2C_DMA_CR_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 RDMAE:1;                           //0   RDMAE
		volatile u32 TDMAE:1;                           //1   TDMAE
		volatile u32 rsvd0:30;                          //31:2  Reserved
        }bit;
};

union I2C_DMA_TDLR_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 DMATDL:3;                          //2:0   DMATDL
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

union I2C_DMA_RDLR_REG {
        volatile u32  all;
        struct{                                                 //bit description
		volatile u32 DMARDL:3;                          //2:0   DMARDL
		volatile u32 rsvd0:29;                          //31:3  Reserved
        }bit;
};

struct I2C_REGS {
        union   I2C_CTL_REG                 I2C_CTL;                   //offset: 0x00                     
        union   I2C_TAR_REG                 I2C_TAR;                   //offset: 0x04                        
        union   I2C_SAR_REG                 I2C_SAR;                   //offset: 0x08                        
        union   I2C_ACK_GEN_CALL_REG        I2C_ACK_GEN_CALL;          //offset: 0x0C
        union   I2C_DATA_CMD_REG            I2C_DATA_CMD;              //offset: 0x10
        volatile   u32  RES0[3];
        union   I2C_SS_SCL_HCNT_REG         I2C_SS_SCL_HCNT;           //offset: 0x20
        union   I2C_SS_SCL_LCNT_REG         I2C_SS_SCL_LCNT;           //offset: 0x24
        union   I2C_FS_SCL_HCNT_REG         I2C_FS_SCL_HCNT;           //offset: 0x28
        union   I2C_FS_SCL_LCNT_REG         I2C_FS_SCL_LCNT;           //offset: 0x2C
        union   I2C_SDA_HOLD_REG            I2C_SDA_HOLD;              //offset: 0x30
        union   I2C_SDA_SETUP_REG           I2C_SDA_SETUP;             //offset: 0x34        
        union   I2C_INTR_MASK_REG           I2C_INTR_MASK;             //offset: 0x38
        union   I2C_INTR_CLR_REG            I2C_INTR_CLR;              //offset: 0x3C
        union   I2C_RAW_INTR_STAT_REG       I2C_RAW_INTR_STAT;         //offset: 0x40
        volatile   u32  RES1;
        union   I2C_ENABLE_REG              I2C_ENABLE;                //offset: 0x48
        union   I2C_ENABLE_STATUS_REG       I2C_ENABLE_STATUS;         //offset: 0x4C
        union   I2C_STATUS_REG              I2C_STATUS;                //offset: 0x50
        union   I2C_TX_ABRT_SOURCE_REG      I2C_TX_ABRT_SOURCE;        //offset: 0x54
        volatile   u32  RES2[2];
        volatile   u32  RES3[4];
        volatile   u32  RES4[4];
        volatile   u32  RES5[1];
        union   I2C_DMA_CR_REG              I2C_DMA_CR;                //offset: 0x84
        union   I2C_DMA_TDLR_REG            I2C_DMA_TDLR;              //offset: 0x88
        union   I2C_DMA_RDLR_REG            I2C_DMA_RDLR;              //offset: 0x8C
        union   I2C_RX_TL_REG               I2C_RX_TL;                 //offset: 0x90
        union   I2C_TX_TL_REG               I2C_TX_TL;                 //offset: 0x94
        union   I2C_TXFLR_REG               I2C_TXFLR;                 //offset: 0x98
        union   I2C_RXFLR_REG               I2C_RXFLR;                 //offset: 0x9C
        volatile   u32   	            I2C_SCL_STUCK_TIMEOUT;     //offset: 0xA0
        volatile   u32    		    I2C_SDA_STUCK_TIMEOUT;     //offset: 0xA4
        volatile   u32  RES6[2];
        volatile   u32         		    I2C_FS_SPIKELEN;           //offset: 0xB0
};
void i2c0_irq_handler(void);
void i2c1_irq_handler(void);
void i2c2_irq_handler(void);
void i2c3_irq_handler(void);
void i2c_irq_register(u8 num, cpu_irq_fun_t irqhandle);
void i2c_irq_unregister(u8 num);
s32  init_i2c(u32 i2c_num);
void i2c_set_clk(u32 i2c_num,speed_mode_t clk);
void i2c_set_speed_mode(u32 i2c_num,speed_mode_t mode);
void i2c_set_7bit_or_10bit_address(u32 i2c_num,address_t master_address,address_t slave_address);
void restart_en(u32 i2c_num,u32 restart);
void sda_hold(u32 i2c_num,u32 sda);
void master_enable(u32 i2c_num,u32 en);
void slave_disable(u32 i2c_num,u32 dis);
void i2c_enable(u32 i2c_num,u32 en);
void i2c_set_address_mode(u32 i2c_num,tx_mode_t mode);
void i2c_target_address(u32 i2c_num,u32 address);
void i2c_slave_address(u32 i2c_num,u32 address);
void i2c_write_byte(u32 i2c_num,u32 SLAVE_ADDRESS,u8 reg_address,u8 data);
void i2c_write_byte_16add(u32 i2c_num,u32 SLAVE_ADDRESS,u8 reg_high_address,u8 reg_low_address,u8 data);
char i2c_read_byte(u32 i2c_num,u32 SLAVE_ADDRESS,u8 reg_address);
void i2c_send_char(u32 i2c_num,u32 data);
void hal_i2c_rxdma_en(u8 i2c_num, u32 en);
void hal_i2c_txdma_en(u8 i2c_num, u32 en);
void hal_i2c_txdma_thset(u8 i2c_num, u32 set);
void hal_i2c_rxdma_thset(u8 i2c_num, u32 set);

/*提供给发送和接收使用*/
struct aic_i2c_msg
{
	u16 addr;		//slave设备地址
	u16 flags;		//扩展读写？
	u16 len;		//buffer的长度
	u8 *buf;		//buffer内容
};

//FIFO深度，根据手册。
#define I2C_FIFO_DEPTH          8

typedef enum {
	I2C_OK = 0,
	I2C_ERR = -1,
	I2C_BUSY = -2,
	I2C_TIMEOUT = -3,
	I2C_UNSPUPPORTED = -4,
}i2c_error_t;
/*i2c 发送接口*/
u32 i2c_master_receive_msg(u8 i2c_num, struct aic_i2c_msg *msg);
/*i2c 接收接口*/
u32 i2c_master_send_msg(u8 i2c_num, struct aic_i2c_msg *msg);
#endif /* INCLUDE_HAL_I2C_H_ */

