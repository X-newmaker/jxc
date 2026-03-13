/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */
#ifndef INCLUDE_HAL_SPI_H_
#define INCLUDE_HAL_SPI_H_

#define SPI_TC_INT                      (1U << 12)

#define SPI_TXD(i)                      (BASE_SPI0 + (i * 0x1000) + 0x200)
#define SPI_RXD(i)                      (BASE_SPI0 + (i * 0x1000) + 0x300)


typedef enum {
    CS_OUT            = 0,
    CS_OUT_DE         = 1,
} CS_OUT_TYPE;

typedef enum {
    MOSI_MISO_NON_MULTIPEX            = 0,
    MOSI_MISO_MULTIPEX                = 1,
} MIO_MULTPEX_TYPE;

typedef enum {
    HW_OWN            = 0,
    SW_OWN            = 1,
} SS_OWNER_TYPE;

typedef enum {
    ACTIVE_HIGH            = 0,
    ACTIVE_LOW             = 1,
} CS_ACTIVE_TYPE;

typedef enum {
    IDLE_LOW           = 0,
    IDLE_HIGH          = 1,
} CLK_IDLE_TYPE;

typedef enum {
    PH0          = 0,
    PH1          = 1,
} SMP_PH_TYPE;

union SPI_VER_REG {
        volatile u32  all;
        struct{          
		volatile u32 VER_L:16;	
		volatile u32 VER_H:16;
        }bit;
};

union SPI_CFG_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 EN:1;	                //0     CTRL_EN
		volatile u32 MODE:1;                    //1     CTRL_MODE_SEL
                volatile u32 rsvd0:5;                   //6:2   Reserved                           
                volatile u32 RXFULL_STOP:1;             //7     RXFIFO FUll Transfer Stop Enable
                volatile u32 rsvd1:23;                  //30:8  Reserved
                volatile u32 CTRL_RST:1;                //31    Controller Reset    
        }bit;
};

union SPI_TCFG_REG {
        volatile u32  all;
        struct{                                         //bit description          
		volatile u32 CPHA:1;                    //0     CPHA                            	                
		volatile u32 CPOL:1;                    //1     CPOL
                volatile u32 CSPOL:1;                   //2     CS_POL 
                volatile u32 CS_VLD_CTL:1;              //3     CS_Valid_Control
                volatile u32 CS_NUM:2;                  //5:4   CS Pin Number
                volatile u32 CS_CTL_SEL:1;              //6     CS Control Mode Select        
                volatile u32 CS_LEVEL:1;                //7     CS Level Configuration
                volatile u32 DINVD:1;                   //8     DINVD
                volatile u32 DMY_VAL:1;                 //9     Dummy Byte Value
                volatile u32 HSWM:1;                    //10    High Speed Write Mode Configuration
                volatile u32 RXINDLY_EN:1;              //11    RX Data Inner Sample Delay Mode Enable
                volatile u32 LSB_EN:1;                  //12    Low Significant Bit Transmit Enable
                volatile u32 RXDLY_DIS:1;               //13    RX Data Delay Sample Mode Disable
                volatile u32 TXDLY_EN:1;                //14    TX Data Delay Mode Enable
                volatile u32 rsvd0:10;                  //15:24 Reserved
                volatile u32 WIRE3_EN:1;                //25    3-Wire Byte Mode Transfer Enable
                volatile u32 rsvd1:5;                   //30:26 Reserved
                volatile u32 START:1;                   //31    START
        }bit;
};

union SPI_ICR_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RF_RDY_INTE:1;	        //0     RX FIFO Ready Interrupt Enable
		volatile u32 RF_EMP_INTE:1;             //1     RX FIFO Empty Interrupt Enable
                volatile u32 RF_FUL_INTE:1;             //2     RX FIFO Full Interrupt Enable
                volatile u32 rsvd0:1;                   //3     Reserved
                volatile u32 TF_RDY_INTE:1;             //4     TX FIFO Ready Interrupt Enable
                volatile u32 TF_EMP_INTE:1;             //5     TX FIFO Empty Interrupt Enable
                volatile u32 TF_FUL_INTE:1;             //6     TX FIFO Full Interrupt Enable
                volatile u32 rsvd1:1;                   //7     Reserved
                volatile u32 RF_OVF_INTE:1;             //8     RX FIFO Overflow Interrupt Enable
                volatile u32 RF_UDR_INTE:1;             //9     RX FIFO Underrun Interrupt Enable
                volatile u32 TF_OVF_INTE:1;             //10    TX FIFO Overflow Interrupt Enable
                volatile u32 TF_UDR_INTE:1;             //11    TX FIFO Underrun Interrupt Enable
                volatile u32 TD_INTE:1;                 //12    Transfer Done Interrupt Enable
                volatile u32 CS_INTE:1;                 //13    CS Invalid Interrupt Enable
                volatile u32 rsvd2:18;                  //31:14 Reserved
        }bit;
};

union SPI_ISTS_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RF_READY:1;	        //0     RX FIFO Ready Interrupt
		volatile u32 RF_EMP:1;                  //1     RX FIFO Empty Interrupt
                volatile u32 RF_FULL:1;                 //2     RX FIFO Full Interrupt
                volatile u32 rsvd0:1;                   //3     Reserved
                volatile u32 TF_READY:1;                //4     TX FIFO Ready Interrupt   
                volatile u32 TF_EMP:1;                  //5     TX FIFO Empty Interrupt
                volatile u32 TF_FULL:1;                 //6     TX FIFO Full Interrupt
                volatile u32 rsvd1:1;                   //7     Reserved
                volatile u32 RF_OVF:1;                  //8     RX FIFO Overflow Interrupt
                volatile u32 RF_UDF:1;                  //9     RX FIFO Underrun Interrupt
                volatile u32 TF_OVF:1;                  //10    TX FIFO Overflow Interrupt
                volatile u32 TF_UDF:1;                  //11    TX FIFO Underrun Interrupt
                volatile u32 TD:1;                      //12    Transfer Done Interrupt
                volatile u32 CS_INV:1;                  //13    CS Invalid Interrupt
                volatile u32 rsvd2:18;                  //31:14 Reserved
        }bit;
};

union SPI_FCTL_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RF_WATER_MARK:8;	        //7:0   RF_WATER_MARK
		volatile u32 RF_DREQ_EN:1;              //1     RF_DREQ_EN
                volatile u32 rsvd0:6;                   //14:9  Reserved
                volatile u32 RF_RST:1;                  //15    RF_RST
                volatile u32 TF_WATER_MARK:8;           //23:16 TF_WATER_MARK
		volatile u32 TF_DREQ_EN:1;              //24    TF_DREQ_EN
                volatile u32 rsvd1:6;                   //30:25 Reserved
                volatile u32 TF_RST:1;                  //31    TF_RST
        }bit;
};

union SPI_FSTS_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 RF_CNT:8;                  //7:0   RF_CNT                  
                volatile u32 rsvd0:4;                   //11:8  Reserved
                volatile u32 RF_RBUF_CNT:3;             //14:12 RF_RBUF_CNT
                volatile u32 RF_RBUF_STS:1;             //15    RF_RBUF_STS
                volatile u32 TF_CNT:8;                  //23:16 TF_CNT
                volatile u32 rsvd1:4;                   //27:24 Reserved
                volatile u32 TF_WBUF_CNT:3;             //30:28 TF_WBUF_CNT
                volatile u32 TF_WBUF_STS:1;             //31    TF_WBUF_STS
        }bit;
};

// union SPI_WCR_REG {
//         volatile u32  all;
//         struct{          
// 		volatile u32 WCC:16;
//                 volatile u32 SWC:4;
//                 volatile u32 rsvd0:12;
//         }bit;
// };

union SPI_CCFG_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 CKDIV2:8;                  //7:0   CKDIV2
                volatile u32 CKDIV1:4;                  //11:8  CKDIV1
                volatile u32 CKDIV_SEL:1;               //12    CKDIV_SEL   
                volatile u32 rsvd0:19;                  //31:13 Reserved
        }bit;
};

union SPI_TBC_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 TB_CNT:24;                 //23:0  TB_CNT
                volatile u32 rsvd0:8;                   //31:24 Reserved
        }bit;
};

union SPI_TWC_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 TXD_CNT:24;                //23:0  TXD_CNT
                volatile u32 rsvd0:8;                   //31:24 Reserved
        }bit;
};

union SPI_TMC_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 STXD_CNT:24;               //23:0  Single TX Data Counter
                volatile u32 DMY_CNT:4;                 //27:24 Dummy Bytes Counter                      
                volatile u32 DUAL_EN:1;                 //28    Dual Transfer Mode Enable
                volatile u32 QUAD_EN:1;                 //29    Quad Transfer Mode Enable
                volatile u32 rsvd0:2;                   //31:30 Reserved
        }bit;
};

union SPI_BMTC_REG {
        volatile u32  all;
        struct{                                         //bit description
		volatile u32 BMOD_SEL:2;                //1:0   Bus Mode Select
                volatile u32 BMCS_NUM:2;                //3:2   BMCS_NUM
                volatile u32 rsvd0:1;                   //4     Reserved
                volatile u32 BMCS_POL:1;                //5     BMCS_POL
                volatile u32 BMCS_CTRL_SEL:1;           //6     BMCS_CTRL_SEL
                volatile u32 BMCS_LEVEL:1;              //7     BMCS_LEVEL        
                volatile u32 BM_TXCNT:6;                //13:8  BM_TXCNT
                volatile u32 rsvd1:2;                   //15:14 Reserved
                volatile u32 BM_RXCNT:6;                //21:16 Bit-Mode RX Data Length        
                volatile u32 rsvd2:2;                   //23:22 Reserved
                volatile u32 BM_TD_INTE:1;              //24    Bit-Mode Transfer Done Interrupt Enable
                volatile u32 BM_TD:1;                   //25    Bit-Mode Transfer Done
                volatile u32 rsvd3:4;                   //29:26 Reserved
                volatile u32 BM_SMP_SEL:1;              //30    Bit-Mode Sample Mode Select
                volatile u32 BM_START:1;                //31    Bit-Mode Start Data Transfer
        }bit;
};

union SPI_BMCLK_REG {
        volatile u32  all;
        struct{                                         //bit description          
		volatile u32 BM_CKDIV:8;                //7:0   Bit-Mode Clock Divide
                volatile u32 rsvd0:24;                  //31:8  Reserved
        }bit;
};

//struct SPI_REGS {
//        union   SPI_VER_REG                 SPI_VER;                   //offset: 0x00
//        union   SPI_TCFG_REG                SPI_TCFG;                  //offset: 0x08
//        union   SPI_CFG_REG                 SPI_CFG;                   //offset: 0x04
//        volatile   u32  RES0;
//        union   SPI_ICR_REG                 SPI_ICR;                   //offset: 0x10
//        union   SPI_ISTS_REG                SPI_ISTS;                  //offset: 0x14
//        union   SPI_FCTL_REG                SPI_FCTL;                  //offset: 0x18
//        union   SPI_FSTS_REG                SPI_FSTS;                  //offset: 0x1C
//        volatile   u32  RES1;                                          //offset: 0x20
//        union   SPI_CCFG_REG                SPI_CCFG;                  //offset: 0x24
//        volatile   u32  RES2[2];
//        union   SPI_TBC_REG                 SPI_TBC;                   //offset: 0x30
//        union   SPI_TWC_REG                 SPI_TWC;                   //offset: 0x34
//        union   SPI_TMC_REG                 SPI_TMC;                   //offset: 0x38
//        volatile   u32  RES3;
//        union   SPI_BMTC_REG                SPI_BMTC;                  //offset: 0x40
//        union   SPI_BMCLK_REG               SPI_BMCLK;                 //offset: 0x44
//        volatile   u32                      SPI_BMTXD;                 //offset: 0x48
//        volatile   u32                      SPI_BMRXD;                 //offset: 0x4C
//        volatile   u32  RES4[4];                                       //offset: 0x50/4/8/C
//        volatile   u32  RES5[4];                                       //offset: 0x60/4/8/C
//        volatile   u32  RES6[4];                                       //offset: 0x70/4/8/C
//        volatile   u32  RES7[2];                                       //offset: 0x80/4
//        volatile   u32  RES8[2];                                       //offset: 0x88/C
//        volatile   u32  RES9[92];                                      //offset: 0x90 ~ 0x1FC
//        volatile   u32                      SPI_TXD;                   //offset: 0x200
//        volatile   u32  RES10[63];
//        volatile   u32                      SPI_RXD;                   //offset: 0x300
//};

typedef struct spi_dev_s {
        union   SPI_VER_REG                 SPI_VER;                   //offset: 0x00                     
        union   SPI_CFG_REG                 SPI_CFG;                   //offset: 0x04
        union   SPI_TCFG_REG                SPI_TCFG;                  //offset: 0x08
        volatile   u32  RES0;                        
        union   SPI_ICR_REG                 SPI_ICR;                   //offset: 0x10
        union   SPI_ISTS_REG                SPI_ISTS;                  //offset: 0x14
        union   SPI_FCTL_REG                SPI_FCTL;                  //offset: 0x18
        union   SPI_FSTS_REG                SPI_FSTS;                  //offset: 0x1C
        volatile   u32  RES1;                                          //offset: 0x20
        union   SPI_CCFG_REG                SPI_CCFG;                  //offset: 0x24
        volatile   u32  RES2[2];
        union   SPI_TBC_REG                 SPI_TBC;                   //offset: 0x30
        union   SPI_TWC_REG                 SPI_TWC;                   //offset: 0x34
        union   SPI_TMC_REG                 SPI_TMC;                   //offset: 0x38
        volatile   u32  RES3;
        union   SPI_BMTC_REG                SPI_BMTC;                  //offset: 0x40
        union   SPI_BMCLK_REG               SPI_BMCLK;                 //offset: 0x44
        volatile   u32                      SPI_BMTXD;                 //offset: 0x48
        volatile   u32                      SPI_BMRXD;                 //offset: 0x4C
        volatile   u32  RES4[4];                                       //offset: 0x50/4/8/C
        volatile   u32  RES5[4];                                       //offset: 0x60/4/8/C
        volatile   u32  RES6[4];                                       //offset: 0x70/4/8/C
        volatile   u32  RES7[2];                                       //offset: 0x80/4
        volatile   u32  RES8[2];                                       //offset: 0x88/C
        volatile   u32  RES9[92];                                      //offset: 0x90 ~ 0x1FC
        volatile   u32                      SPI_TXD;                   //offset: 0x200 
        volatile   u32  RES10[63]; 
        volatile   u32                      SPI_RXD;                   //offset: 0x300
} spi_dev_t;

void spi0_irq_handler(void);
void spi1_irq_handler(void);
void spi2_irq_handler(void);
void spi3_irq_handler(void);
void spi4_irq_handler(void);
void spi5_irq_handler(void);
void spi_irq_register(u8 num, cpu_irq_fun_t irqhandle);
void spi_irq_unregister(u8 num);
void spi_cmu_init(u8 index);
void spi_soft_rst(u8 index);
void spi_type1_clk_div(u8 index, u32 div);
void spi_type2_clk_div(u8 index, u32 div);
void spi_txdrq_en(u8 index);
void spi_rxdrq_en(u8 index);
void spi_txdrq_dis(u8 index);
void spi_rxdrq_dis(u8 index);
void spi_txfifo_level_set(u8 index, u32 level);
void spi_rxfifo_level_set(u8 index, u32 level);
void spi_txfifo_rst(u8 index);
void spi_rxfifo_rst(u8 index);
void spi_mbc_set(u8 index, u32 mbc);
void spi_mtc_set(u8 index, u32 mwtc);
void spi_stc_set(u8 index, u32 stc);
void spi_txdata_write(u8 index, u32 txd);
void spi_xch(u8 index);
void spi_mosi_miso_multiplex(u8 index);
void spi_set_cs_out_de(u8 index);
void spi_dhb_en(u8 index);
void spi_dhb_dis(u8 index);
void spi_cs_level_high(u8 index);
void spi_cs_level_low(u8 index);
void spi_cs_owner_hw(u8 index);
void spi_cs_owner_sw(u8 index);
void spi_cs_unassert_inbst(u8 index);
void spi_cs_high_assert(u8 index);
void spi_cs_low_assert(u8 index);
void spi_clk_idle_low(u8 index);
void spi_clk_idle_high(u8 index);
void spi_ph0_sample(u8 index);
void spi_ph1_sample(u8 index);
void spi_rxdelay_sample(u8 index);
void spi_en(u8 index);
void spi_int_sts_clr(u8 index);
void spi_master_en(u8 index);
u32 spi_get_int_sts(u8 index);
u32 spi_get_rx_dat(u8 index);
void spi_tc_sts_clr(u8 index);
u32 spi_get_rx_fifo_cnt(u32 index);
#endif /* INCLUDE_HAL_SPI_H_ */
