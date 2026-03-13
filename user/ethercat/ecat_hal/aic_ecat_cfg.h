#ifndef AIC_ECAT_CFG_H_
#define AIC_ECAT_CFG_H_

//EEPROM SELECTION
#define EEPROM_SIZE                     1           //0 for 1~16 Kbit, 1 for 32 Kbit~4 Mbit

//EEPROM CHECK RETRY
#define EEPROM_CHECK_RETRY_COUNT        3000

//PORT ENABLE
#define PORT0_EN                        1
#define PORT1_EN                        1
#define PORT2_EN                        0

#define PORT0_RMII_EN                   0
#define PORT1_RMII_EN                   0
#define PORT2_RMII_EN                   0

#define USING_ACTUAL_MOTOR              1
//PHY SELECTION
//#define PHY_RTL8201  //瑞昱      电压型
//#define PHY_YT8522   //裕太微    电压型
#define PHY_DP83822    //TI        电流型

#if defined PHY_YT8522
#define PHY_ID0                         0x4f51
#define PHY_ID1                         0xE928

#define PHY0_LINK_REV                   1
#define PHY1_LINK_REV                   0
#define PHY2_LINK_REV                   0

#define PHY_ADDR_OFFSET                 1
#define PHY_RESET_OUT_DLY_TIME          200
#elif defined PHY_DP83822
#define PHY_ID0                         0x2000
#define PHY_ID1                         0xA240

#define PHY0_LINK_REV                   0
#define PHY1_LINK_REV                   0
#define PHY2_LINK_REV                   0

#define PHY_ADDR_OFFSET                 1
#define PHY_RESET_OUT_DLY_TIME          200
#else
#define PHY_ID0                         0x001C
#define PHY_ID1                         0xC816

#define PHY0_LINK_REV                   1
#define PHY1_LINK_REV                   1
#define PHY2_LINK_REV                   0

#define PHY_ADDR_OFFSET                 0
#define PHY_RESET_OUT_DLY_TIME          200
#endif

//SYSCFG
#define BASE_CFG0_ETHERCAT      (BASE_SYSCFG + 0X0128)           //system config 12c+128
#define BASE_CFG1_ETHERCAT      (BASE_SYSCFG + 0X012C)

typedef struct
{
    union {
            struct
            {
                unsigned int tx_shift0 : 2;
                unsigned int tx_shift1 : 2;
                unsigned int tx_shift2 : 2;
                unsigned int phy_rst_mask : 1;
                unsigned int prom_size : 1;     //0:1-16Kbit  1:32K:4Mbit

                unsigned int phy_addr_offset : 5;
                unsigned int pdi_type : 1;      //0:on chip bus  1:spi
                unsigned int phy_rst_released : 1;       //0:reset
                unsigned int pdi_int_en : 1;        //0:enable  1:disable

                unsigned int rst_int_en : 1;        //0:enable  1:disable
                unsigned int sync0_int_en : 1;
                unsigned int sync1_int_en : 1;
                unsigned int pid_int_en : 1;
                unsigned int link0_reverse : 1;
                unsigned int link1_reverse : 1;
                unsigned int link2_reverse : 1;
                unsigned int clockout_select : 1;   //0:25M 1:50M

                unsigned int port0_type : 1;        //0:MII 1:RMII
                unsigned int port1_type : 1;
                unsigned int port2_type : 1;
                unsigned int port0_link_en : 1;
                unsigned int port1_link_en : 1;
                unsigned int port2_link_en : 1;
                unsigned int eeprom_emulation_en : 1;
                unsigned int chip_rst_en : 1;
            };
            unsigned int reg;
        } REG0;
        union {
            struct
            {
                unsigned int rmii0_rx_pha : 2;
                unsigned int port0_rxclk_rev : 1;
                unsigned int rmii0_rx_bypass : 1;
                unsigned int rmii1_rx_pha : 2;
                unsigned int port1_rxclk_rev : 1;
                unsigned int rmii1_rx_bypass : 1;

                unsigned int rmii2_rx_pha : 2;
                unsigned int port2_rxclk_rev : 1;
                unsigned int rmii2_rx_bypass : 1;
                unsigned int rmii_tx_clk_phase : 2;
                unsigned int sync_rev : 1;
                unsigned int latch_rev : 1;

                unsigned int latch0_source : 4;
                unsigned int latch1_source : 4;

                unsigned int dma_sdt_signal_sel : 2;
                unsigned int dma_src_signal_sel : 2;
                unsigned int tx_shift0_manual : 1;
                unsigned int tx_shift1_manual : 1;
                unsigned int tx_shift2_manual : 1;
                unsigned int rmii_fast_sync_en : 1;


            };
            unsigned int reg;
        } REG1;
        union {
            struct
            {
                unsigned int latch_sync_en : 1;
                unsigned int res : 31;
            };
            unsigned int reg;
        } REG2;

} ECAT_CFG;

extern ECAT_CFG *ecat_cfg;
void ecat_syscfg_init(void);
#endif

