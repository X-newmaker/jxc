/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_CAN_H_
#define INCLUDE_HAL_CAN_H_


#define CAN_NUM      2

/* CAN Baud Rate for Simulation */
typedef enum {
	BR_2M 	 = 2000000,
	BR_1M 	 = 1000000,
	BR_900K  = 900000,
	BR_800K  = 800000,
	BR_725K  = 725000,
	BR_600K  = 600000,
	BR_400K  = 400000,
	BR_200K  = 200000,
	BR_125K  = 125000,
	BR_100K  = 100000,
	BR_50K   = 50000,
	BR_20K   = 20000
} can_sim_baudrate;

/* CAN Operating Mode */
typedef enum {
	SLEEP_MODE 	= (0x1<<4),			//Sleep Mode Selected
	SINGLE_FILTER 	= (0x1<<3),			//Single Filter Mode Selected
	//DUAL_FILTER 	= (0x0<<3),			//Dual Filter Mode Selected
	SELFTEST_MODE 	= (0x1<<2),			//Self Test Enabled
	LISTEN_MODE 	= (0x1<<1),			//Listen Only Enabled
	RESET_MODE 	= (0x1<<0)			//Reset Mode Selected
} can_op_mode;

/* CAN Control Command */
typedef enum {
	SELF_REQ 	= (0x1<<4),			//Self Reception Request
	CLEAR_OVF_FLAG 	= (0x1<<3),			//Clear Overflow Flag
	RXBUF_RELEASE 	= (0x1<<2),			//Release Receive Buffer
	ABORT_REQ 	= (0x1<<1),			//Abort Transmission Request
	TX_REQ 		= (0x1<<0)			//Transmission Request
} can_ctrl_cmd;

/* CAN Interrupt Flag */
typedef enum {
	ERRB_INT    	= (0x1<<7),				//Bus Error Interrupt
	ARBLOST_INT 	= (0x1<<6),				//Arbitration Lost	Interrupt
	ERRP_INT	= (0x1<<5),				//Error Passive Interrupt
	WAKEUP_INT 	= (0x1<<4),				//Wake-Up Interrupt
	OVF_INT 	= (0x1<<3),				//Overflow Interrupt
	ERRW_INT 	= (0x1<<2),				//Error Warning Interrupt
	TX_INT 		= (0x1<<1),				//Transmit Interrupt, Transmit Buffer Ready
	RX_INT 		= (0x1<<0)				//Receive Interrupt, Receive Buffer Ready
} can_int_flag;

/* CAN Status Flag */
typedef enum {
	BUS_OFF   	= (0x1<<7),				//Bus Off Status
	ERR_STAT 	= (0x1<<6),				//Error Status
	TX_BUSY		= (0x1<<5),				//Transmit Busy Status
	RX_BUSY 	= (0x1<<4),				//Receive Busy Status
	TX_COMPLETE 	= (0x1<<3),				//Transmission Complete Status
	TXB_READY 	= (0x1<<2),				//Transmit Buffer Ready Status
	OVF_FLAG 	= (0x1<<1),				//Receive FIFO Overflow Flag
	RXB_READY 	= (0x1<<0)				//Receive Buffer Ready Status
} can_status_flag;

/* CAN Acceptance Filter Mode */
typedef enum {
	FILTER_CLOSE 		= 0,
	SINGLE_FILTER_MODE 	= 1,
	DUAL_FILTER_MODE 	= 2
} can_filter_mode;

/* CAN Acceptance Filter Mode */
typedef enum {
        NON_SELF_TEST           = 0,
        SELF_TEST               = 1,
} can_self_test_type;

/* CAN Bus Error Message */
typedef struct {
	u32 code;
	char* msg;
} bus_err_msg_t;


/* Structure of Bus Timing 0 Configuration for CAN */
typedef struct {
    u32 brp;                    // Baud Rate Prescaler (APB clock divider, 1~1024)
    u8 sjw;                     // Synchronization Jump Width (1~4 Tq)
} can_btr0_t;

/* Structure of Bus Timing 1 Configuration for CAN */
typedef struct {
    u8 ts1;                 	// Timing segment 1 (1~16 Tq)
    u8 ts2;                	// Timing segment 2 (1~8 Tq)
    u8 sam;      		// sam=1 triple sampling or sam=0 single sampling
} can_btr1_t;

/* Structure for a CAN Message */
typedef struct
{
	u32   id;         	 //IDE = 1, 29bit EXID; IDE = 0, 11bit STID
	u32   rtr;        	 //Remote Transmission Request bit
	u32   ide;       	 //ID Extended flag
	u32   reserved;  	 //Reserved
	u32   dlc;      	 //Data Length Code
	u32   data[8];    	 //Data Buffer
} can_message_t;

typedef struct {
	u32 bus_error;			//bus error
	u32 arbitration_lost;   	//arbitration lost
	u32 passive_error;		//passive error
	u32 wake_up;			//wake_up
	u32 overflow;			//Rx FIFO data overflow
	u32 error_warning;		//error warning
	u32 txb_available;		//former data transmit end, txb is available
	u32 rxb_available;		//Rx FIFO is not empty, has one or more data
} can_intr_event;

/* Structure for a CAN Controller */
typedef struct
{
	u32    baudrate;		//Baud rate
	u32    op_mode;			//Operating Mode
	u32    flag;
	u32    rxcode;
	u32    rxmask;
	u8     flt_mode;
	u8     txb_rdy;
	u8     rxb_rdy;
	u8     error;
} can_ctrl_t;

/* Structure of Acceptance Filter Configuration for RXCODE RXMASK*/
// #pragma anon_unions
typedef struct {
	union{
		struct {
			u32 data1 : 8,
			    data0 : 8,
			          : 4,
			    rtr   : 1,
			    id    : 11;
		};
		u32 raw_single_std;
	} single_filter_std;			//SFF, Single Filter��identifier 11bit, ID28~ID18

	union{
		struct {
			u32	    : 2,
				rtr : 1,
				id  : 29;
		};
		u32 raw_single_ext;
	}single_filter_ext;			//EFF, Single Filter, identifier 29bit, ID28~ID0

	union{
		struct {
			u32 flt1_rtr	: 1,
			    flt1_id 	: 11,
			    flt0_data0	: 8,
			    flt0_rtr 	: 1,
			    flt0_id	: 11;
		};
		u32 raw_dual_std;
	}dual_filter_std;				//SFF, Dual Filters, identifier 11bit, ID28~ID18

	union{
		struct {
			u32 flt1_id_h16 : 16,
			    flt0_id_h16 : 16;
		};
		u32 raw_dual_ext;
	}dual_filter_ext;				//EFF, Dual Filters, identifier high 16bit, ID28~ID13
} can_filter_t;

union CAN_MODE_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RST_MOD:1;                 //0     CAN_RST_MOD
		volatile u32 LISTEN_MOD:1;              //1     CAN_LISTEN_MOD
		volatile u32 SELFTEST_MOD:1;            //2     CAN_SELFTEST_MOD
		volatile u32 FILTER_MOD:1;              //3     CAN_FILTER_MOD
		volatile u32 SLEEP_MOD:1;               //4     CAN_SLEEP_MOD
		volatile u32 rsvd0:27;                  //31:5  Reserved
        }bit;
};

union CAN_MCR_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 TX_REQ:1;                  //0     CAN_TX_REQ
		volatile u32 ABORT_REQ:1;               //1     CAN_ABORT_REQ
		volatile u32 RXB_REL:1;                 //2     CAN_RXB_REL
		volatile u32 CLR_OVF_FLAG:1;            //3     CAN_CLR_OVF_FLAG
		volatile u32 SELF_REQ:1;                //4     CAN_SELF_REQ
		volatile u32 rsvd0:27;                  //31:5  Reserved
        }bit;
};

union CAN_STAT_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RXB_STAT:1;                //0     CAN_RXB_STAT
		volatile u32 OVF_FLAG:1;                //1     CAN_OVF_FLAG
		volatile u32 TXB_STAT:1;                //2     CAN_TXB_STAT
		volatile u32 TXC_STAT:1;                //3     CAN_TXC_STAT
		volatile u32 RX_STAT:1;                 //4     CAN_RX_STAT
		volatile u32 TX_STAT:1;                 //5     CAN_TX_STAT
		volatile u32 ERR_STAT:1;                //6     CAN_ERR_STAT
		volatile u32 BUS_STAT:1;                //7     CAN_BUS_STAT
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_INTR_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RX_INT:1;                  //0     CAN_RX_INT
		volatile u32 TX_INT:1;                  //1     CAN_TX_IN
		volatile u32 ERRW_INT:1;                //2     CAN_ERRW_INT
		volatile u32 OVF_INT:1;                 //3     CAN_OVF_INT
		volatile u32 WAKEUP:1;                  //4     CAN_WAKEUP
		volatile u32 ERRP_INT:1;                //5     CAN_ERRP_INT
		volatile u32 ARBLOST_INT:1;             //6     CAN_ARBLOST_INT
		volatile u32 ERRB_INT:1;                //7     CAN_ERRB_INT
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_INTEN_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RXI_EN:1;                  //0     CAN_RXI_EN
		volatile u32 TXI_EN:1;                  //1     CAN_TXI_EN
		volatile u32 ERRW_EN:1;                 //2     CAN_ERRW_EN
		volatile u32 OVF_EN:1;                  //3     CAN_OVF_EN
		volatile u32 WAKEUP_EN:1;               //4     CAN_WAKEUP_EN
		volatile u32 ERRP_EN:1;                 //5     CAN_ERRP_EN
		volatile u32 ARBLOST_EN:1;              //6     CAN_ARBLOST_EN
		volatile u32 ERRB_EN:1;                 //7     CAN_ERRB_EN
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BTR0_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 BRP:6;                     //5:0   CAN_BRP
		volatile u32 SJW:2;                     //7:6   CAN_SJW
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BTR1_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 TS1:4;                     //3:0   CAN_TS1
		volatile u32 TS2:3;                     //6:4   CAN_TS2
		volatile u32 SAM:1;                     //7     CAN_SAM
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_ARBLOST_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 ARBLOST_CAP:4;             //3:0   CAN_ARBLOST_CAP
		volatile u32 rsvd0:28;                  //31:4  Reserved
        }bit;
};

union CAN_ERRCODE_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 ERR_CODE:5;                //4:0   CAN_ERR_CODE
		volatile u32 ERR_DIR:1;                 //5     CAN_ERR_DIR
		volatile u32 ERR_TYPE:2;                //7:6   CAN_ERR_TYPE
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_ERRWT_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 ERRWT:8;                   //7:0   CAN_ERRWT
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_RXERR_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 REC:8;                     //7:0   CAN_REC
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_TXERR_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 TEC:8;                     //7:0   CAN_TEC
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BUF0_RXC0_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 DLC:4;                     //3:0   CAN_DLC
		volatile u32 rsvd0:2;                   //5:4   Reserved
		volatile u32 RTR:1;                     //6     CAN_RTR
		volatile u32 IDE:1;                     //7     CAN_IDE
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_buf0;
	struct{          
		volatile u32 RXC0:8;                    //7:0   CAN_RXC0
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxc0;
};

union CAN_BUF1_RXC1_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 ID:8;                      //7:0   CAN_ID
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf1;
	struct{                                         //bit description
		volatile u32 RXC1:8;                    //7:0   CAN_RXCODE1
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxc1;
};

union CAN_BUF2_RXC2_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 EXID:5;                    //4:0   CAN_EXID
		volatile u32 STID_EXID:3;               //7:5   CAN_STID_EXID
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf2;
	struct{                                         //bit description
		volatile u32 RXC2:8;                    //7:0   CAN_RXCODE2
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxc2;
};

union CAN_BUF3_RXC3_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA1_EXID:8;            //7:0   CAN_STDATA1_EXID
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf3;
	struct{                                         //bit description
		volatile u32 RXC3:8;                    //7:0   CAN_RXCODE3
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxc3;
};

union CAN_BUF4_RXM0_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA2:3;                 //2:0   CAN_STDATA2
		volatile u32 STDATA2_EXID:5;            //7:3   CAN_STDATA2_EXID
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf4;
	struct{                                         //bit description
		volatile u32 RXM0:8;                    //7:0   CAN_RXMASK0
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxm0;
};

union CAN_BUF5_RXM1_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA3_EXDATA1:8;         //7:0   CAN_STDATA3_EXDATA1
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf5;
	struct{          
		volatile u32 RXM1:8;                    //7:0   CAN_RXMASK1;
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxm1;
};

union CAN_BUF6_RXM2_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA4_EXDATA2:8;         //7:0   CAN_STDATA4_EXDATA2
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf6;
	struct{                                         //bit description
		volatile u32 RXM2:8;                    //7:0   CAN_RXMASK2;
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxm2;
};

union CAN_BUF7_RXM3_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA5_EXDATA3:8;         //7:0   CAN_STDATA5_EXDATA3
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit_buf6;
	struct{                                         //bit description
		volatile u32 RXM3:8;                    //7:0   CAN_RXMASK3;
		volatile u32 rsvd1:24;                  //31:8  Reserved
        }bit_rxm3;
};

union CAN_BUF8_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA6_EXDATA4:8;         //7:0   CAN_STDATA6_EXDATA4
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BUF9_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA7_EXDATA5:8;         //7:0   CAN_STDATA7_EXDATA5
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BUF10_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STDATA8_EXDATA6:8;         //7:0   CAN_STDATA8_EXDATA6
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BUF11_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 EXDATA7:8;                 //7:0   CAN_EXDATA7
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_BUF12_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 EXDATA8:8;                 //7:0   CAN_EXDATA8
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_RXC_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RXC:8;                     //7:0   CAN_RXC
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_RSADDR_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RSADDR:6;                  //5:0   CAN_PSADDR
		volatile u32 rsvd0:26;                  //31:6  Reserved
        }bit;
};

union CAN_RXFIFO_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RXFIFO:8;                  //7:0   CAN_RXFIFO
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

union CAN_TXB_RO_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 TXB_RO:8;                  //7:0   CAN_TXB_RO
		volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

struct CAN_REGS {
        union   CAN_MODE_REG                CAN_MODE;              //offset: 0x00                     
        union   CAN_MCR_REG                 CAN_MCR;               //offset: 0x04                        
        union   CAN_STAT_REG                CAN_STAT;              //offset: 0x08                        
        union   CAN_INTR_REG                CAN_INTR;              //offset: 0x0C
        union   CAN_INTEN_REG               CAN_INTEN;             //offset: 0x10
	volatile   u32  RES0;
	union   CAN_BTR0_REG                CAN_BTR0;              //offset: 0x18
        union   CAN_BTR1_REG                CAN_BTR1;              //offset: 0x1C
	volatile   u32  RES1[3];	
        union   CAN_ARBLOST_REG             CAN_ARBLOST;           //offset: 0x2C
        union   CAN_ERRCODE_REG             CAN_ERRCODE;           //offset: 0x30
        union   CAN_ERRWT_REG               CAN_ERRWT;             //offset: 0x34
        union   CAN_RXERR_REG               CAN_RXERR;             //offset: 0x38
        union   CAN_TXERR_REG               CAN_TXERR;             //offset: 0x3C
        union   CAN_BUF0_RXC0_REG           CAN_BUF0_RXC0;         //offset: 0x40
        union   CAN_BUF1_RXC1_REG           CAN_BUF1_RXC1;         //offset: 0x44        
        union   CAN_BUF2_RXC2_REG           CAN_BUF2_RXC2;         //offset: 0x48
        union   CAN_BUF3_RXC3_REG           CAN_BUF3_RXC3;         //offset: 0x4C
        union   CAN_BUF4_RXM0_REG           CAN_BUF4_RXM0;         //offset: 0x50        
        union   CAN_BUF5_RXM1_REG           CAN_BUF5_RXM1;         //offset: 0x54
        union   CAN_BUF6_RXM2_REG           CAN_BUF6_RXM2;         //offset: 0x58
        union   CAN_BUF7_RXM3_REG           CAN_BUF7_RXM3;         //offset: 0x5C        
        union   CAN_BUF8_REG                CAN_BUF8;              //offset: 0x60
        union   CAN_BUF9_REG                CAN_BUF9;              //offset: 0x64
        union   CAN_BUF10_REG               CAN_BUF10;             //offset: 0x68
        union   CAN_BUF11_REG               CAN_BUF11;             //offset: 0x6C        
        union   CAN_BUF12_REG               CAN_BUF12;             //offset: 0x70
	union   CAN_RXC_REG                 CAN_RXC;               //offset: 0x74
	union   CAN_RSADDR_REG              CAN_RSADDR;            //offset: 0x78
	volatile   u32  RES2;
	union   CAN_RXFIFO_REG              CAN_RXFIFO;            //offset: 0x80
	volatile   u32  RES3[63];
	union   CAN_TXB_RO_REG              CAN_TXB_RO;            //offset: 0x180
	
};

void can0_irq_handler(void);
void can1_irq_handler(void);
void can_irq_register(u8 num, cpu_irq_fun_t irqhandle);
void can_irq_unregister(u8 num);

/* Function Declaration */
int can_cmu_init(u32 n);

/*Set/Release CAN Operating Mode*/
void can_mode_set(u32 n, can_op_mode mode);
void can_mode_release(u32 n, u32 mode);

/*Set CAN Module Control Command*/
void can_cmd_set(u32 n, u32 cmd);

/*Get CAN Status*/
u32 can_status_get(u32 n);

/*Enable/Disable interrupt */
void can_enable_int(u32 n, u32 temp);
void can_disable_int(u32 n, u32 temp);
void can_dis_all_int(u32 n);

/*Get Error Message /Arbitration Lost Message*/
u32 can_arblost_get(u32 n);
u32 can_error_code_get(u32 n);
u32 can_error_type_get(u32 n);
u32 can_error_dir_get(u32 n);

/*Set/Get CAN Error Warning Threshold*/
void can_errwt_set(u32 n, u32 errwt);
u32 can_errwt_get(u32 n, u32 errwt);

/*CAN Error Count Get*/
u32 can_tx_error_count_get(u32 n);
u32 can_rx_error_count_get(u32 n);

/*CAN Receive Message Count Get*/
u32 can_rx_msg_count_get(u32 n);

/*CAN Receive Buffer Start Address Get*/
u32 can_rxb_start_addr_get(u32 n);

/*Get CAN Interrut Status*/
u32 can_intr_get(u32 n);

/*Get CAN Interrut Enable*/
u32 can_inten_get(u32 n);

/*Get CAN Interrut Enable*/
u32 can_mode_get(u32 n);

void can_clr_rx_int(u32 n);
void can_clr_tx_int(u32 n);
void can_clr_errw_int(u32 n);
void can_clr_ovf_int(u32 n);
void can_clr_errp_int(u32 n);
void can_clr_arbl_int(u32 n);
void can_clr_errb_int(u32 n);

/*Print Error Message /Arbitration Lost Message*/
void can_buserr_msg(u32 n);
void can_arblost_msg(u32 n);

void can_int_handler(u32 n);
void can0_int_handler(void);
void can1_int_handler(void);

void can_msg(u32 n);
void can_msg_print(void);
void can_frame_print(can_message_t *frame);

void can_init(u32 n);
void can_exit(u32 n);

s32 can_tx_frame(u32 n, can_message_t* frame, can_self_test_type sel_test);
u32 test_tx_series_frame(u32 n, can_message_t *txmsg_tbl, int txmsg_cnt);
s32 can_rx_frame(u32 n, can_message_t* frame);
u32 test_rx_series_frame(u32 n, can_message_t *rxmsg_tbl);
void can_abort_frame(u32 n);
s32 can_baudrate_set(u32 n, u32 baud);
s32 can_filter_set(u32 n, u32 ide, u32 mode, can_filter_t* pcode, can_filter_t* pmask);


#endif /* INCLUDE_HAL_CAN_H_ */
