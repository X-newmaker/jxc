/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_UART_H_
#define INCLUDE_HAL_UART_H_

#include <all_inc.h>

#define UART_BUSY_TIMEOUT       1000000

#define LSR_PFE              0x80
#define LSR_TEMT             0x40
#define LSR_TRANS_EMPTY      0x20
#define LSR_BI               0x10
#define LSR_FE               0x08
#define LSR_PE               0x04
#define LSR_OE               0x02
#define LSR_DATA_READY       0x01


#define IIR_THR_EMPTY        	0x02    /* threshold empty */
#define IIR_RECV_DATA        	0x04    /* received data available */
#define IIR_RECV_LINE        	0x06    /* receiver line status */
#define IIR_CHAR_TIMEOUT     	0x0c    /* character timeout */

typedef enum {
    BR_380400           = 0,
    BR_460800           = 1,
    BR_500000           = 2,
    BR_921600           = 3,
    BR_1152000          = 4,
    BR_1500000          = 5,
    BR_2500000          = 6,
    BR_3000000          = 7,
} UART_BR_TYPE;

typedef enum {
    TX_RX_EN            = 0,
    TX_RX_RTS_EN        = 1,
    TX_RX_RTS_CTS_EN    = 2,
} UART_WIRE_TYPE;

typedef enum {
    UART_DLS_5 = 0,
    UART_DLS_6 = 1,
    UART_DLS_7 = 2,
    UART_DLS_8 = 3,
} UART_DLS_TYPE;

typedef enum {
    UART_STOP_TYPE0 = 0,
    UART_STOP_TYPE1 = 1,
} UART_STOP_TYPE;

typedef enum {
    UART_PARITY_DIS  = 0,
    UART_PARITY_EN   = 1,
} UART_PARITY_FUN;

typedef enum {
    UART_PARITY_MOD0  = 0,
    UART_PARITY_MOD1  = 1,
    UART_PARITY_MOD2  = 2,
    UART_PARITY_MOD3  = 3,    
} UART_PARITY_MOD;

typedef enum {
    UART_MOD         = 0,
    IRDA_MOD         = 1,
    RS485_MOD        = 2,
    RS485_2WIRE_MOD  = 3,
} UART_FUNC_MOD;

typedef enum {
    RX_ONE_CHAR                 = 0,
    RX_ONE_FORTH_FIFO           = 1,
    RX_ONE_SECOND_FIFO          = 2,
    RX_FULL                     = 3,
} UART_RX_TRIG;

typedef enum {
    TX_EMPTY                    = 0,
    TX_TWO_CHAR                 = 1,
    TX_ONE_FORTH_FIFO           = 2,
    TX_ONE_SECOND_FIFO          = 3,
} UART_TX_TRIG;

typedef struct
{
    volatile u32 FIFOE:1;                   //0     UART_FIFOE
    volatile u32 RXFIFOR:1;                 //1     UART_RXFIFOR
    volatile u32 TXFIFOR:1;                 //2     UART_TXFIFOR
    volatile u32 DMAM:1;                    //3     UART_DMAM
    volatile u32 TFT:2;                     //5:4   UART_TFT
    volatile u32 RT:2;                      //7:6   UART_RT
    volatile u32 rsvd0:24;                  //31:8  Reserved
} UART_FCR_REG;

typedef struct
{
    UART_DLS_TYPE       data_length;
    UART_STOP_TYPE      stop_bit;
    UART_PARITY_FUN     parity_fun;
    UART_PARITY_MOD     parity_mod;
    u32                 baud_rate_div;           
    UART_FCR_REG	fifo_cfg;
} UART_CFG_PARA;



union UART_RBR_THR_DLL_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 RBR:8;                     //7:0   UART_RBR
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_rbr;
        struct {                                         //bit description
		volatile u32 THR:8;                     //7:0   UART_THR
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_thr;
        struct {                                         //bit description
		volatile u32 DLL:8;                     //7:0   UART_DLL
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_dll;
};

union UART_DLH_IER_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DLH:8;                     //7:0   UART_DLH
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_dlh;
        struct {                                         //bit description
		volatile u32 ERBFI:1;                   //0     UART_ERBFI
		volatile u32 ETBEI:1;                   //1     UART_ETBEI
		volatile u32 ELSI:1;                    //2     UART_ELSI
		volatile u32 EDSSI:1;                   //3     UART_EDSSI
		volatile u32 RS485_INT_EN:1;            //4     UART_RS485_INT_EN
		volatile u32 SHIFT_REG_EMP_EN:1;        //5     UART_SHIFTER_REG_EMPTY_EN
		volatile u32 rsvd0:1;                   //6     Reserved
		volatile u32 PTIME:1;                   //7     UART_PTIME
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_ier;
};

union UART_IIR_FCR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 IID:4;                     //3:0   UART_IID
		volatile u32 SHIFT_REG_EMP_INT:1;       //4     UART_SHIFTER_REG_EMPTY_INT
		volatile u32 rsvd0:1;                   //5     Reserved
		volatile u32 FEFLAG:2;                  //7:6   UART_FEFLAG
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_iir;
        struct {                                         //bit description
		volatile u32 FIFOE:1;                   //0     UART_FIFOE
		volatile u32 RXFIFOR:1;                 //1     UART_RXFIFOR
		volatile u32 TXFIFOR:1;                 //2     UART_TXFIFOR
		volatile u32 DMAM:1;                    //3     UART_DMAM
		volatile u32 TFT:2;                     //5:4   UART_TFT
		volatile u32 RT:2;                      //7:6   UART_RT
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_fcr;
};

union UART_LCR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DLS:2;                     //1:0   UART_DLS
		volatile u32 STOP:1;                    //2     UART_STOP
		volatile u32 PEN:1;                     //3     UART_PEN
		volatile u32 EPS:2;                     //5:4   UART_EPS
		volatile u32 BC:1;                      //6     UART_BC
		volatile u32 DLAB:1;                    //7     UART_DLAB
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_MCR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 rsvd0:1;                   //0 Reserved
		volatile u32 RTS:1;                     //1     UART_RTS
		volatile u32 rsvd1:2;                   //3:2   Reserved
		volatile u32 LOOP:1;                    //4     UART_LOOP
		volatile u32 AFCE:1;                    //5     UART_AFCE
		volatile u32 UART_FUNC:2;               //7:6   UART_FUNCTION
		volatile u32 rsvd2:24;                  //31:8  Reserved
        }bit;
};

union UART_LSR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DR:1;                      //0     UART_DR
		volatile u32 OE:1;                      //1     UART_OE
		volatile u32 PE:1;                      //2     UART_PE
		volatile u32 FE:1;                      //3     UART_FE
		volatile u32 BI:1;                      //4     UART_BI
		volatile u32 THRE:1;                    //5     UART_THRE
		volatile u32 TEMT:1;                    //6     UART_TEMT
		volatile u32 FIFOERR:1;                 //7     UART_FIFOERR
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_MSR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DCTS:1;                    //0     UART_DCTS
		volatile u32 rsvd0:3;                   //3:1   Reserved
		volatile u32 CTS:1;                     //4     UART_CTS
		volatile u32 rsvd1:27;                  //31:5  Reserved
        }bit;
};

union UART_SCH_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 SCRATCH:8;                 //7:0   UART_SCRATCH_REG
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_WRBR_WTHR_REG {
        volatile u32  all;
        struct {                                //bit description
        volatile u32 WRBR;                      //31:0   UART_WRBR_REG
        }bit_wrbr;
        struct {                                //bit description
        volatile u32 WTHR;                      //31:0   UART_WTHR_REG
        }bit_wthr;
};

union UART_WINTR_REG {
        volatile u32  all;
        struct {                                //bit description
        volatile u32 TFO_EN:1;                  //0     UART_TFO_EN
        volatile u32 RFU_EN:1;                  //1     UART_RFU_EN
        volatile u32 TFO:1;                     //2     UART_TFO
        volatile u32 RFU:1;                     //3     UART_RFU
        volatile u32 WTRR:1;                    //4     UART_WTRR
        volatile u32 RWDR:1;                    //5     UART_RWDR
        volatile u32 WRE_EN:1;                  //6     UART_WRE_EN
        volatile u32 WRE:1;                     //7     UART_WRE
        volatile u32 rsvd0:24;                  //31:8  Reserved
        }wrbr;
};

union UART_USR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 BUSY:1;                    //0     UART_BUSY
		volatile u32 TFNF:1;                    //1     UART_TFNF
		volatile u32 TFE:1;                     //2     UART_TFE
		volatile u32 RFNE:1;                    //3     UART_RFNE
		volatile u32 RFF:1;                     //4     UART_RFF
		volatile u32 rsvd0:27;                  //31:5  Reserved
        }bit;
};

union UART_TFL_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 TFL:9;                     //8:0   UART_TFL
		volatile u32 rsvd0:23;                  //31:9  Reserved
        }bit;
};

union UART_RFL_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 RFL:9;                     //8:0   UART_RFL
		volatile u32 rsvd0:23;                  //31:9  Reserved
        }bit;
};

union UART_HSK_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 HSK:8;                     //7:0   UART_HSK
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_DMAW_CTL_REG {
        volatile u32  all;
        struct {                                         //bit description
        volatile u32 DMA_WORD_WEN:1;                     //1   DMA_WORD_REN
        volatile u32 DMA_WORD_REN:1;                     //1   DMA_WORD_WEN
        volatile u32 rsvd0:30;                  //31:8  Reserved
        }bit;
};

union UART_RX_EN_REG {
        volatile u32  all;
        struct {                                         //bit description
        volatile u32 RX_EN:1;                   //1   RX_EN
        volatile u32 rsvd0:31;                  //31:8  Reserved
        }bit;
};

union UART_HALT_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 HALT_TX:1;                 //0     UART_TX
		volatile u32 CHCFG_AT_BUSY:1;           //1     UART_CHCFG_AT_BUSY
		volatile u32 CHANGE_UPDT:1;             //2     UART_CHANGE_UPDATE
		volatile u32 rsvd0:1;                   //3     Reserved
		volatile u32 SIR_TX_INV:1;              //4     UART_SIR_TX_INV
		volatile u32 SIR_RX_INV:1;              //5     UART_SIR_RX_INV
		volatile u32 PTE:1;                     //6     UART_PTE
		volatile u32 DMA_PTE_RX:1;              //7     UART_DMA_PTE_RX
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit;
};

union UART_DBG_DLL_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DBG_DLL:8;                 //7:0   UART_DEBUG DLL
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_DBG_DLH_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DBG_DLH:8;                 //7:0   UART_DBG_DLH
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_485_DE_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DE_AT:4;                   //0:3   UART_DE_AT
		volatile u32 DE_DAT:4;                  //4:7   UART_DE_DAT
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_485_CTL_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 RS485_SLV_MOD_SEL:2;       //1:0   UART_RS485_SLAVE_MODE_SEL
		volatile u32 RX_AF_ADDR:1;              //2     UART_RX_AF_ADDR
		volatile u32 RX_BF_ADDR:1;              //3     UART_RX_BF_ADDR
		volatile u32 rsvd0:1;                   //4     Reserved
		volatile u32 RS485_ADDR_DET_F:1;        //5     UART_RS485_ADDR_DET_F
		volatile u32 AAD_ADDR_F:1;              //6     UART_AAD_ADDR_F
		volatile u32 RS485_CTL_MODE:1;          //7     UART_RS485_CTL_MODE
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit;
};

union UART_485_ADDR_MATCH_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 ADDR_MATCH:8;              //7:0   UART_ADDR_MATCH
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_BUS_IDL_CHK_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 ADJ_TIME:6;                //5:0   UART_ADJ_TIME
		volatile u32 BUS_STATUS:1;              //6     UART_BUS_STATUS
		volatile u32 BUS_IDL_CHK_EN:1;          //7     UART_BUS_IDLE_CHK_EN
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_TX_DLY_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 DLY:8;                     //7:0   UART_DLY
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_DBR_REG {
        volatile u32  all;
        struct {                                         //bit description
		volatile u32 rsvd0:3;                   //2:0   Reserved
		volatile u32 BYPASS:1;                  //3     UART_BYPASS
		volatile u32 rsvd1:28;                  //31:4  Reserved
        }bit;
};

union UART_TFAET_REG {
        volatile u32  all;
        struct {                                         //bit description
        volatile u32 TFAET:8;                   //7:0     TFAET
        volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_RFAET_REG {
        volatile u32  all;
        struct {                                         //bit description
        volatile u32 RFAET:8;                   //7:0     RFAET
        volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union UART_LIN_CSR_REG {
        volatile u32  all;
        struct {                                         //bit description
        volatile u32 LIN_EN:1;                   //0     LIN_EN
        volatile u32 LIN_SEND_BREAK_REQ:1;       //1     LIN_SEND_BREAK_REQ
        volatile u32 LIN_BREAK_DET_LEN:2;        //3:2   LIN_BREAK_DET_LEN
        volatile u32 LIN_BREAK_DET_INT_EN:1;     //4     LIN_BREAK_DET_INT_EN
        volatile u32 LIN_BREAK_DET_FLAG : 1;     //5     LIN_BREAK_DET_FLAG
        volatile u32 rsvd0:26;                   //31:6  Reserved
        }bit;
};

union UART_X8SR_REG {
        volatile u32  all;
        struct {                                         //bit description
        volatile u32 X8_SAMPLE_EN:1;            //0     X8_SAMPLE_EN
        volatile u32 rsvd0:31;                  //31:1  Reserved
        }bit;
};

struct UART_REGS {
        union   UART_RBR_THR_DLL_REG         UART_RBR_THR_DLL;      //offset: 0x00
        union   UART_DLH_IER_REG             UART_DLH_IER;          //offset: 0x04
	union   UART_IIR_FCR_REG             UART_IIR_FCR;              //offset: 0x08   
	union   UART_LCR_REG                 UART_LCR;                  //offset: 0x0C   
	union   UART_MCR_REG                 UART_MCR;                  //offset: 0x10   
	union   UART_LSR_REG                 UART_LSR;                  //offset: 0x14   
	union   UART_MSR_REG                 UART_MSR;                  //offset: 0x18   
	union   UART_SCH_REG                 UART_SCH;                  //offset: 0x1C 
	volatile   u32  RES0[4];
	union   UART_WRBR_WTHR_REG           UART_WRBR_WTHR;            //offset: 0x30
	union   UART_WINTR_REG               UART_WINTR;                //offset: 0x34
	volatile   u32  RES1[17];
	union   UART_USR_REG                 UART_USR;                  //offset: 0x7C   
	union   UART_TFL_REG                 UART_TFL;                  //offset: 0x80   
	union   UART_RFL_REG                 UART_RFL;                  //offset: 0x84   
	union   UART_HSK_REG                 UART_HSK;                  //offset: 0x88
    union   UART_DMAW_CTL_REG            UART_DMAW_CTL;             //offset: 0x8C
	volatile   u32  RES3[4];
	union   UART_RX_EN_REG               UART_RX_EN;                //offset: 0xA0
	union   UART_HALT_REG                UART_HALT;                 //offset: 0xA4
	volatile   u32  RES5[2]; 
	union   UART_DBG_DLL_REG             UART_DBG_DLL;              //offset: 0xB0 
	union   UART_DBG_DLH_REG             UART_DBG_DLH;              //offset: 0xB4 
	union   UART_485_DE_REG              UART_485_DE;               //offset: 0xB8
	volatile   u32  RES6;
	union   UART_485_CTL_REG             UART_485_CTL;              //offset: 0xC0
	union   UART_485_ADDR_MATCH_REG      UART_485_ADDR_MATCH;       //offset: 0xC4
	union   UART_BUS_IDL_CHK_REG         UART_BUS_IDL_CHK;          //offset: 0xC8
	union   UART_TX_DLY_REG              UART_TX_DLY;               //offset: 0xCC
	union   UART_DBR_REG                 UART_DBR;                  //offset: 0xD0
	union   UART_TFAET_REG               UART_TFAET;                //offset: 0xD4
	union   UART_RFAET_REG               UART_RFAET;                //offset: 0xD8
    union   UART_LIN_CSR_REG             UART_LIN;                  //offset: 0xDC
    union   UART_X8SR_REG                UART_X8SR;                 //offset: 0xE0

};


void uart0_irq_handler(void);
void uart1_irq_handler(void);
void uart2_irq_handler(void);
void uart3_irq_handler(void);
void uart4_irq_handler(void);
void uart5_irq_handler(void);
void uart6_irq_handler(void);
void uart7_irq_handler(void);
void uart8_irq_handler(void);
void uart_irq_register(u8 num, cpu_irq_fun_t irqhandle);
void uart_irq_unregister(u8 num);
void uart_set_cmu(u8 index);
u32 uart_set_cmu_br(u8 index, UART_BR_TYPE br_rate);
u32 uart_get_br_div(u8 index, u32 br_rate);
void uart_tx_halt_en(u8 index);
void uart_tx_halt_dis(u8 index);
void uart_div_latch_access(u8 index);
void uart_div_latch_clear(u8 index);
void uart_set_div_dlh(u8 index, u32 dlh);
void uart_set_div_dll(u8 index, u32 dll);
void uart_set_op_para(u8 index,UART_CFG_PARA *uart_cfg_para);
void uart_fifo_cfg(u8 index, UART_FCR_REG *frc);
void de_assert_time_set(u8 index, u32 de_at, u32 de_dat);
void uart_set_2wire_mode(u8 index);
void uart_set_485_mode(u8 index);
void uart_send_char(u32 uart_no, u8 data);
void uart_get_char(u32 uart_no, u8 *data);
void uart_set_rx_bf_addr(u8 index);
void uart_set_de_hwmode(u8 index);
u32 uart_get_lsr(u8 index);
s32 uart_transmit_char(u8 index, u8 data);
s32 uart_receive_char(u8 index, u8 *data);
void uart_rxd_int_en(u8 index);
void uart_txd_int_en(u8 index);
void uart_txd_shift_empty_int_en(u8 index);
void uart_rxd_int_dis(u8 index);
void uart_txd_int_dis(u8 index);
void uart_txd_shift_empty_int_dis(u8 index);
u32 uart_get_iir(u8 index);
u32 uart_get_tfl(u8 index);
u32 uart_get_rfl(u8 index);
void uart_set_dma_handshake(u8 index);
u32 uart_get_fifo_addr(u8 index);
s32 uart_dma_tx_request(u8 index, u8 ch, u32 saddr, u32 len);
s32 uart_dma_rx_request(u8 index, u8 ch, u32 daddr, u32 len);
void uart_set_rx_enable(u8 index);
void uart_set_tfl(u8 index, u8 fifo_level);
void uart_set_rfl(u8 index, u8 fifo_level);
#endif /* INCLUDE_HAL_UART_H_ */
