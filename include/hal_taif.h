/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_TAIF_H_
#define INCLUDE_HAL_TAIF_H_

typedef enum {
	TA_2P5MHz  = 0x0,
	TA_4P0MHz  = 0x1,
	TA_6P6MHz  = 0x2,
	TA_8P0MHz  = 0x3,
	TA_16P0MHz = 0x4,
}TA_BAUD_TYPE;

typedef enum {
	T_FORMAT = 0x0,
	A_FORMAT = 0x1,
	X_FORMAT = 0x2,
}TA_FORMAT_TYPE;

typedef enum {
        T_FIELD_1 = 0x0,
        T_FIELD_3 = 0x1,
        T_FIELD_4 = 0x2,
}TA_TFIELD_NUM_TYPE;

typedef enum {
        T_DTAT_ID0 = 0x0,  // get single data
        T_DTAT_ID3 = 0x3,  // get single + multi data
		T_DTAT_ID6 = 0x6,  // write eeprom
        T_DTAT_ID7 = 0x7,  // reset error
        T_DTAT_ID8 = 0x8,  // reset single data
        T_DTAT_IDC = 0xc,  // reset multi data
		T_DTAT_IDD = 0xd,  // read eeprom
}TA_TDATAID_TYPE;

typedef enum {
	A_TX_FIELD1 = 0x0,
	A_TX_FIELD2 = 0x1,
	A_TX_FIELD4 = 0x2,
}TA_AFIELD_TX_TYPE;

typedef enum {
	A_RX_FIELD1 = 0x0,
	A_RX_FIELD2 = 0x1,
	A_RX_FIELD3 = 0x2,
	A_RX_FIELD4 = 0x3,
}TA_AFIELD_RX_TYPE;

typedef enum {
	A_RX_CDF_HWT_FIELD3 = 0,
	A_RX_CDF_HWT_FIELD4 = 1,
}TA_CDF_HWT_RXFNUM_HW;

typedef enum {
	DF012 = 0x0,
	DF456 = 0x1,
}TF_DEC_SEL;

#define CMD_DONE                     	(0x1 << 0)
#define T5_TIMEOUT						(0x1 << 1)
#define T6_TIMEOUT						(0x1 << 2)
#define HW_TRG_EXIT						(0X1 << 3)
#define XFMT_TXF						(0x1 << 8)
#define XFMT_TXF_UOVF					(0x1 << 9)
#define XFMT_TXF_DOVF					(0x1 << 10)
#define XFMT_RXF						(0x1 << 11)
#define XFMT_RXF_UOVF					(0x1 << 12)
#define XFMT_RXF_DOVF					(0x1 << 13)

/***************************************************************************
                        Register Description
***************************************************************************/
union CMD_EXC_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 CMD_EXC:1;                         //0     Command Execute
                volatile u32 rsvd0:15;                          //15:1  Reserved
                volatile u32 DBG_RST:16;                        //31:16 DBG_RST
        }bit;
};

union COM_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rsvd0:1;                      		//0     Format Select
                volatile u32 HW_TRG_EN:1;                       //1     Hardware Trigger Enable
                volatile u32 TX_COL_DET_EN:1;                   //2     Transmit Collide Detection Enable
                volatile u32 STF_CLR_RXD_EN:1;                  //3     STF_CLR_RXD_EN
                volatile u32 BDRATE_SET:3;                      //6:4   Baudrate Set
                volatile u32 rsvd1:1;                           //7     Reserved
                volatile u32 FORMAT_SEL:2;						//9:8	Format Select
                volatile u32 rsvd2:2;                           //11:10     Reserved
                volatile u32 HW_RX_ERR_BPS_EN:1;                //12    HW Mode Receive Error Bypass Enable
                volatile u32 rsvd3:19;                          //31:13  Reserved
        }bit;
};

union STS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 rsvd0:3;                     		//2:0  Reserved
                volatile u32 TX_ERR:1;                          //3     TX Error
                volatile u32 ABE_ERR:1;                         //4     Absolute Encoder Error
                volatile u32 ABE_TRG_ERR:1;                     //5     ABE_TRG_ERR
                volatile u32 AEI_STS:1;                         //6     Absolut Encoder Interface Status                  
                volatile u32 rsvd1:25;                          //31:7  Reserved
        }bit;
};

union BCLK_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 BCLK_SW_CFG:7;                     //6:0   BCLK Software Configure
                volatile u32 BCLK_SW_CFG_EN:1;                  //7     BCLK_SW_CFG Enable
                volatile u32 SMP_CFG:7;                         //14:8  Sample Point Configure
                volatile u32 SMP_CFG_EN:1;                      //15    SMP_CFG Enable
                volatile u32 RX_ALIGN_EN:1;                     //16    Receive Align Enable
                volatile u32 rsvd0:15;                          //31:17 Reserved
        }bit;
};

union DEC_ABS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 DEC_ABS_DAT:24;                    //23:0  Decode Absolute Single Turn Data
                volatile u32 rsvd0:8;                           //31:24 Reserved
        }bit;
};

union DEC_ABM_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 DEC_ABM_DAT:24;                    //23:0  Decode Absolute Multi Turn Data
                volatile u32 rsvd0:8;                           //31:24 Reserved
        }bit;
};

union TA_IRQ_EN_REG {
		volatile u32 all;
		struct {
				volatile u32 IRQ_CMD_DONE_EN:1;					//0 irq_cdm_done_en
				volatile u32 IRQ_CMD_TO_EN:1;					//1 IRQ_CMD_TO_EN
				volatile u32 IRQ_CMD_RXD_TO_EN:1;				//2 IRQ_CMD_RXD_TO_EN
				volatile u32 IRQ_HW_TRIG_EXIT_EN:1;				//3 IRQ_HW_TRIG_EXIT_EN
				volatile u32 IRQ_ABE_TRG_ERR_EN:1;				//4 IRQ_ABE_TRG_ERR_EN
				volatile u32 rsvd0:27;							//31:5 Reserved
		}bit;
};

union TA_IRQ_STS_REG {
		volatile u32 all;
		struct {
				volatile u32 IRQ_CMD_DONE:1;					//0 irq_cdm_done_en
				volatile u32 IRQ_CMD_TO:1;						//1 IRQ_CMD_TO
				volatile u32 IRQ_CMD_RXD_TO:1;					//2 IRQ_CMD_RXD_TO
				volatile u32 IRQ_HW_TRIG_EXIT:1;				//3 IRQ_HW_TRIG_EXIT
				volatile u32 IRQ_ABE_TRG_ERR:1;					//4 IRQ_ABE_TRG_ERR
				volatile u32 rsvd0:3;							//7:5 Reserved
				volatile u32 IRQ_XFMT_TXF:1;					//8 IRQ_XFMT_TXF
				volatile u32 IRQ_XFMT_TXF_UOVF:1;				//9 IRQ_XFMT_TXF_UOVF
				volatile u32 IRQ_XFMT_TXF_DOVF:1;				//10 IRQ_XFMT_TXF_DOVF
				volatile u32 IRQ_XFMT_RXF:1;					//11 IRQ_XFMT_RXF
				volatile u32 IRQ_XFMT_RXF_UOVF:1;				//12 IRQ_XFMT_RXF_UOVF
				volatile u32 IRQ_XFMT_RXF_DOVF:1;				//13 IRQ_XFMT_RXF_DOVF
				volatile u32 rsvd1:8;							//31:14 Reserved
		}bit;
};

union TX_ADF_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 TXAD:7;                            //6:0   Transmission Address Data Setting
                volatile u32 BUSY:1;                            //7     BUSY State Setting
                volatile u32 rsvd0:24;                          //31:8  Reserved
        }bit;
};

union TX_EDF_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 TXED:8;                            //7:0   Transmission EEPROM Data Setting
                volatile u32 rsvd0:24;                          //31:8  Reserved
        }bit;
};

union TX_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 ID:4;                              //3:0   Transmission ID Code Setting
                volatile u32 DFNUM:4;                           //7:4   Data Field Number
                volatile u32 TX_FLD_NUM:2;                      //9:8   Transmit Field Number
                volatile u32 rsvd0:22;                          //31:10 Reserved
        }bit;
};

union RX_DAT0_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RXD0:8;                            //7:0   Received Data Field 0 Data
                volatile u32 RXD1:8;                            //15:8  Received Data Field 1 Data
                volatile u32 RXD2:8;                            //23:16 Received Data Field 2 Data
                volatile u32 RXD3:8;                            //31:24 Received Data Field 3 Data
        }bit;
};

union RX_DAT1_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RXD4:8;                            //7:0   Received Data Field 4 Data
                volatile u32 RXD5:8;                            //15:8  Received Data Field 5 Data
                volatile u32 RXD6:8;                            //23:16 Received Data Field 6 Data
                volatile u32 RXD7:8;                            //31:24 Received Data Field 7 Data
        }bit;
};

union RX_TSTS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RSE:1;                             //0     Read Sequence Error
                volatile u32 IDE:1;                             //1     Received ID Data Error
                volatile u32 CONTE:1;                           //2     Control Field Error
                volatile u32 CRCE:1;                            //3     CRC Error
                volatile u32 FOME:1;                            //4     Format Error
                volatile u32 SFOME:1;                           //5     Short Format Error
                volatile u32 RXEDFE:1;                          //6     Received EDF Error
                volatile u32 RXADFE:1;                          //7     Received ADF Error
                volatile u32 DFOVFE:1;                          //8     Received Data Field Overflow Error
                volatile u32 rsvd0:1;                           //9     Reserved
                volatile u32 EEBUSY:1;                           //10    EEPROM Access Reception Busy State
                volatile u32 RXID:4;                            //14:11 Received ID Data
                volatile u32 RXIDP:1;                           //15    Received ID Parity Data
                volatile u32 RXSFIC:4;                          //19:16 Received Status Field Information Code
                volatile u32 RXSFEA:2;                          //21:20 Received Status Field Encoder Alarm
                volatile u32 RXSFCA:2;                          //23:22 Received Status Field Communication Alarm
                volatile u32 RXCRC:8;                           //31:24 Received CRC Data
        }bit;
};

union RX_TDAT_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 CF:8;                            //7:0   Received Data Field cf
                volatile u32 SF:8;                            //15:8  Received Data Field sf
                volatile u32 ADF:8;                            //23:16 Received Data Field adf
                volatile u32 EDF:8;                            //31:24 Received Data Field edf
        }bit;
};

union RX_TDEC_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 TF_ABS_DEC_EN:1;                    //0   TF_ABS_DEC_EN
                volatile u32 DEC_TF_ABS_SEL:1;                   //1  DEC_TF_ABS_SEL
                volatile u32 rsvd0:2;                           //3:2     Reserved
                volatile u32 TF_ABM_DEC_EN:1;                    //4   TF_ABM_DEC_EN
                volatile u32 DEC_TF_ABM_SEL:1;                   //5  DEC_TF_ABM_SEL
                volatile u32 rsvd1:26;                           //31:6     Reserved
        }bit;
};


union TX_DATA_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 CDF_EA:3;                          //2:0   Encoder Address Setting
                volatile u32 CDF_CC:5;                          //7:3   Command Code Setting
                volatile u32 MDF0_DATA:8;                       //15:8  MDF0 DATA Setting
                volatile u32 MDF1_DATA:8;                       //23:16 MDF1 DATA Setting
                volatile u32 MDF2_DATA:8;                       //31:24 MDF2 DATA Setting
        }bit;
};

union RX_D0_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RXIF:16;                           //15:0  RX Information Field
                volatile u32 RXDF0:16;                          //31:16 RX Data Field 0
        }bit;
};

union RX_D1_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RXDF1:16;                          //15:0  RX Data Field 1
                volatile u32 RXDF2:16;                          //31:16 RX Data Field 2
        }bit;
};

union FORMT_CTL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 RXFNUM:2;                          //1:0   Recieve Field Number
                volatile u32 TXFNUM:2;                          //3:2   Transmit Field Number
                volatile u32 rsvd0:28;                          //31:4  Reserved
        }bit;
};

union RX_ASTS_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 STARTERR:1;                        //0     Start bit error
                volatile u32 STOPERR:1;                         //1     Stop bit error
                volatile u32 SINKERR:1;                         //2     Sink code error
                volatile u32 RXEAERR:1;                         //3     Received encoder address error
                volatile u32 CRCERR:1;                          //4     CRC error
                volatile u32 RXCCERR:1;                         //5     Received command code error
                volatile u32 MDATERR:1;                         //6     EEPROM data error，RX_ASTS_HW无此位
                volatile u32 MADRERR:1;                         //7     EEPROM address error，RX_ASTS_HW无此位
                volatile u32 ES0:1;                             //8     ES0状态位
                volatile u32 ES1:1;                             //9     ES1状态位
                volatile u32 ES2:1;                             //10    ES2状态位
                volatile u32 ES3:1;                             //11    ES3状态位
                volatile u32 ES:1;                              //12    ES状态位，RX_ASTS_HW无此位
                volatile u32 rsvd0:19;                          //31:13 Reserved
        }bit;
};

union RX_ADEC_CFG_REG {
	volatile u32 all;
	struct {												//bit description
		volatile u32 AF_ABS_DEC_EN:1;					//0 dec_abs_data_en
		volatile u32 AF_ABS_DEC_ST_BIT:6;				//6:1 AF_ABS_DEC_ST_BIT
		volatile u32 rsvd0:1;							//7 Reserved
		volatile u32 AF_ABS_DEC_BIT_NUM:4;				//11:8 AF_ABS_DEC_BIT_NUM
		volatile u32 rsvd1:4;							//15:12 Reserved
		volatile u32 AF_ABM_DEC_EN:1;					//16 AF_ABM_DEC_EN
		volatile u32 AF_ABM_DEC_ST_BIT:6;				//22:17 AF_ABM_DEC_ST_BIT
		volatile u32 rsvd2:1;							//23 Reserved
		volatile u32 AF_ABM_DEC_BIT_NUM:4;				//27:24 AF_ABM_DEC_BIT_NUM
		volatile u32 rsvd3:4;							//31:28 Reserved
	}bit;
};


union TA_16B_VAL_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 VAL:16;                            //15:0  Value
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union TA_RX_FLT_REG {
        volatile u32  all;
        struct {                                                 //bit description
                volatile u32 IN_FLT_SEL:4;                      //3:0   Input Filter Seclect
                volatile u32 IN_PRE_FLT:4;                      //7:4   Input Pre Filter Enable
                volatile u32 SMP_CTL_PRD:8;                     //15:8  Input Sample Control Period
                volatile u32 rsvd0:16;                          //31:16 Reserved
        }bit;
};

union XFMT_CFG1_REG {
		volatile u32 all;
		struct {
			volatile u32 rsvd0:4;						//3:0 Reserved
			volatile u32 XFMT_TXC_LEN:4;				//7:4 XFMT_TXC_LEN
			volatile u32 rsvd1:4;						//11:8 Reserved
			volatile u32 XFMT_RXC_LEN:4;				//15:12 XFMT_TXC_LEN
			volatile u32 XFMT_TXFIFO_EN:1;				//16 XFMT_TXFIFO_EN
			volatile u32 XFMT_TXFIFO_IRQ_EN:1;			//17 XFMT_TXFIFO_IRQ_EN
			volatile u32 XFMT_TXFIFO_DRQ_EN:1;			//18 XFMT_TXFIFO_DRQ_EN
			volatile u32 rsvd2:1;						//19 Reserved
			volatile u32 XFMT_RXFIFO_EN:1;				//20 XFMT_RXFIFO_EN
			volatile u32 XFMT_RXFIFO_IRQ_EN:1;			//21 XFMT_RXFIFO_IRQ_EN
			volatile u32 XFMT_RXFIFO_DRQ_EN:1;			//22 XFMT_RXFIFO_DRQ_EN
			volatile u32 rsvd3:1;						//23 Reserved
			volatile u32 TXFIFO_TH:4;					//27:24 TXFIFO_TH
			volatile u32 RXFIFO_TH:4;					//31:28 RXFIFO_TH
		}bit;
};

union XFMT_CFG2_REG {
		volatile u32 all;
		struct {
			volatile u32 XFMT_TXC_NUM:8;				//7:0 XFMT_TXC_NUM
			volatile u32 XFMT_RXC_NUM:8;				//15:8	XFMT_RXC_NUM
			volatile u32 XFMT_TXFIFO_UOVF_IRQ_EN:1;		//16 XFMT_TXFIFO_UOVF_IRQ_EN
			volatile u32 XFMT_TXFIFO_DOVF_IRQ_EN:1;		//17 XFMT_TXFIFO_DOVF_IRQ_EN
			volatile u32 XFMT_RXFIFO_UOVF_IRQ_EN:1;		//18 XFMT_RXFIFO_UOVF_IRQ_EN
			volatile u32 XFMT_RXFIFO_DOVF_IRQ_EN:1;		//19 XFMT_RXFIFO_DOVF_IRQ_EN
			volatile u32 TXFIFO_CNT:5;					//24:20 TXFIFO_CNT
			volatile u32 RXFIFO_CNT:5;					//29:25 RXFIFO_CNT
			volatile u32 rsvd0:2;						//31:30 Reserved
		}bit;
};

union XFMT_CMD_REG {
		volatile u32 all;
		struct {
			volatile u32 XCMD:18;						//17:0 XCMD
			volatile u32 rsvd:14;						//31:18 Reserved
		}bit;
};

union XFMT_DAT_REG {
		volatile u32 all;
		struct {
			volatile u32 XDAT:18;						//17:0 XDAT
			volatile u32 rsvd:14;						//31:18 Reserved
		}bit;
};

struct TAIF_REGS {
        union   CMD_EXC_REG        CMD_EXC;          //offset: 0x00
        union   COM_CTL_REG        COM_CTL;          //offset: 0x04
        union   STS_REG        	   STS;          //offset: 0x08
        union   BCLK_REG           BCLK;             //offset: 0x0C
        union   DEC_ABS_REG        DEC_ABS;          //offset: 0x10
        union	DEC_ABM_REG		   DEC_ABM;			 //offset: 0x14
        volatile u32  RES0[2];                      //offset: 0x18~0x1C
        union	TA_IRQ_EN_REG	   TA_IRQ_EN;	     //offset: 0x20
        union	TA_IRQ_STS_REG	   TA_IRQ_STS;	     //offset: 0x24
        volatile u32  RES1[6];                      //offset: 0x28~0x3C
        union   TX_ADF_REG         TX_ADF;           //offset: 0x40
        union   TX_EDF_REG         TX_EDF;           //offset: 0x44 
        union   TX_CTL_REG         TX_CTL;           //offset: 0x48                    
        volatile u32  RES2;                          //offset: 0x4C
        union   RX_DAT0_REG        RX_DAT0;          //offset: 0x50
        union   RX_DAT1_REG        RX_DAT1;          //offset: 0x54
        union   RX_TSTS_REG        RX_TSTS;          //offset: 0x58
        volatile u32  RES3;                          //offset: 0x5C
        union   RX_TDAT_REG        RX_TDAT;          //offset: 0x60
        volatile u32  RES4[3];                       //offset: 0x64~0x6C
        union   RX_TDEC_REG        RX_TDEC;          //offset: 0x70
        volatile u32  RES5[3];                       //offset: 0x74~0x7C
        union   TX_DATA_REG        TX_DATA;          //offset: 0x80
        volatile u32  RES6;                          //offset: 0x84
        union   RX_D0_REG          RX_D0;            //offset: 0x88
        union   RX_D1_REG          RX_D1;            //offset: 0x8C
        union   FORMT_CTL_REG      FORMT_CTL;        //offset: 0x90
        union   RX_ASTS_REG        RX_ASTS;          //offset: 0x94
        volatile u32  RES7[6];                       //offset: 0x98~0xaC
        union   RX_ADEC_CFG_REG    RX_ADEC_CFG;      //offset: 0xB0
        volatile u32  RES8[3];                       //offset: 0xB4~0xBC
        union   TA_16B_VAL_REG     T2;               //offset: 0xC0
        union   TA_16B_VAL_REG     T3;               //offset: 0xC4
        union   TA_16B_VAL_REG     T4;               //offset: 0xC8
        union   TA_16B_VAL_REG     T5;               //offset: 0xCC
        union   TA_16B_VAL_REG     T6;               //offset: 0xD0
        union   TA_16B_VAL_REG     T9;               //offset: 0xD4
        volatile u32  RES9[2];                       //offset: 0xD8~0xDC
        union   TA_RX_FLT_REG      RX_FLT;           //offset: 0xE0
        union   TA_16B_VAL_REG     TCOL;             //offset: 0xE4
        volatile u32  RES10[6];                      //offset: 0xE8~0xFC
        union	XFMT_CFG1_REG	   XFMT_CFG1;	 	 //offset: 0x100
        union	XFMT_CFG2_REG	   XFMT_CFG2;	 	 //offset: 0x104
        volatile u32  RES11[2];                      //offset: 0x108~0x10C
        union	XFMT_CMD_REG	   XFMT_CMD[16];	 //offset: 0x110~0x14C
        volatile u32  RES12[12];                     //offset: 0x150~0x17C
        union	XFMT_DAT_REG	   XFMT_DAT[16];	 //offset: 0x180~0x1BC
};


void taif0_irq_handler(void);
void taif0_irq_register(cpu_irq_fun_t irqhandle);
void taif0_irq_unregister(void);
void taif1_irq_handler(void);
void taif1_irq_register(cpu_irq_fun_t irqhandle);
void taif1_irq_unregister(void);
void ta_cmu_init(void);
void ta_syscfg_sel(u8 n);
void ta_pinmux_init(u8 n);
void ta_reset(u8 n);
void ta_cmd_execute(u32 n);

void ta_baudrate_set(u8 n, TA_BAUD_TYPE baud);
void ta_format_sel(u8 n, TA_FORMAT_TYPE format);
void ta_hw_err_bp_enable(u8 n,u32 enable);
void ta_hw_trig_en(u8 n);
void ta_hw_trig_dis(u8 n);
void ta_hw_err_bp_en(u8 n);
void ta_hw_err_bp_dis(u8 n);
void ta_tx_col_det_en(u8 n);
void ta_tx_col_det_dis(u8 n);

void ta_done_irq_en(u8 n);
void ta_cmdto_irq_en(u8 n);
void ta_rxto_irq_en(u8 n);
void ta_hw_trig_exit_irq_en(u8 n);

void ta_done_irq_clr(u8 n);
void ta_cmdto_irq_clr(u8 n);
void ta_rxto_irq_clr(u8 n);
void ta_hw_trig_exit_irq_clr(u8 n);
void ta_xfmt_txf_clr(u8 n);
void ta_xfmt_txf_uovf(u8 n);
void ta_xfmt_txf_dovf(u8 n);
void ta_xfmt_rxf_clr(u8 n);
void ta_xfmt_rxf_uovf(u8 n);
void ta_xfmt_rxf_dovf(u8 n);

void ta_rx_align_en(u32 n);

void ta_t2_set(u32 n, u16 t2);
void ta_t3_set(u32 n, u16 t3);
void ta_t4_set(u32 n, u16 t4);
void ta_t5_set(u32 n, u16 t5);
void ta_t6_set(u32 n, u16 t6);
void ta_t9_set(u32 n, u16 t9);
void ta_tcol_set(u32 n, u16 tcol);

void ta_ctl(u32 n,TA_TDATAID_TYPE id,u32 dfnum,TA_TFIELD_NUM_TYPE field);
void ta_adf(u32 n,u32 busy,u32 adf);
void ta_edf(u32 n,u32 edf);

u32 ta_get_sts(u32 n);
u32 ta_get_rx_data0(u32 n);
u32 ta_get_rx_data1(u32 n);
u32 ta_get_rx_tsts(u32 n);
u32 ta_get_rx_tdat(u32 n);

void tf_dec_abs_sel(u32 n,TF_DEC_SEL sel);
void tf_dec_abm_sel(u32 n,TF_DEC_SEL sel);

void ta_cdf(u32 n,u32 ea,u32 cc,u32 mdf0,u32 mdf1,u32 mdf2);
void ta_format_ctl(u32 n,TA_AFIELD_TX_TYPE txfiled,TA_AFIELD_RX_TYPE rxfield);
u32 ta_get_arx_d0(u32 n);
u32 ta_get_arx_d1(u32 n);
u32 ta_get_arx_if(u32 n);
u32 ta_get_arx_df0(u32 n);
u32 ta_get_arx_df1(u32 n);
u32 ta_get_arx_df2(u32 n);

u32 ta_get_rx_asts(u32 n);

void af_abs_pos_set(u8 n, u32 startbit, u32 size);
void af_abm_pos_set(u8 n, u32 startbit, u32 size);

u32 ta_get_abs_pos(u32 n);
u32 ta_get_abm_pos(u32 n);

u32 ta_get_irq_sts(u32 n);
void ta_irq_sts_clr(u32 n, u32 data);
u32 ta_get_rx_adf(u32 n);
u32 ta_get_rx_edf(u32 n);

void ta_xf_tx_len(u8 n, u32 len);
void ta_xf_rx_len(u8 n, u32 len);
void ta_xf_txfifo_en(u8 n);
void ta_xf_txfifo_dis(u8 n);
void ta_xf_txfifo_irq_en(u8 n);
void ta_xf_txfifo_drq_en(u8 n);
void ta_xf_rxfifo_en(u8 n);
void ta_xf_rxfifo_dis(u8 n);
void ta_xf_rxfifo_irq_en(u8 n);
void ta_xf_rxfifo_drq_en(u8 n);
void ta_xf_txfifo_th(u8 n,u32 th);
void ta_xf_rxfifo_th(u8 n,u32 th);

void ta_xf_tx_num(u8 n,u32 num);
void ta_xf_rx_num(u8 n,u32 num);
void ta_xf_txfifo_uovf_irq_en(u8 n);
void ta_xf_txfifo_dovf_irq_en(u8 n);
void ta_xf_rxfifo_uovf_irq_en(u8 n);
void ta_xf_rxfifo_dovf_irq_en(u8 n);

void ta_xf_xcmd(u8 n, u32 num, u32 cmd);
u32 ta_xf_xdat(u8 n, u32 num);
#endif /* INCLUDE_TAIF_H_ */
