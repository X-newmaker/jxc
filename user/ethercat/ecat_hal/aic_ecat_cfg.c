#include "../ecat_hal/aic_ecat_cfg.h"
#include "ecat_def.h"

#include <all_inc.h>

ECAT_CFG *ecat_cfg = (ECAT_CFG *)BASE_CFG0_ETHERCAT;

void ecat_syscfg_init(void)
{
    cmu_mod_enable(CMU_MOD_SYSCFG);
    ecat_cfg->REG0.phy_rst_released = 0;
    ecat_cfg->REG0.prom_size = ESC_EEPROM_EMULATION ? 0 : EEPROM_SIZE;
    ecat_cfg->REG0.eeprom_emulation_en = ESC_EEPROM_EMULATION;

    ecat_cfg->REG0.phy_addr_offset = PHY_ADDR_OFFSET;

    ecat_cfg->REG0.link0_reverse = PHY0_LINK_REV;
    ecat_cfg->REG0.link1_reverse = PHY1_LINK_REV;
    ecat_cfg->REG0.link2_reverse = PHY2_LINK_REV;
    ecat_cfg->REG0.pdi_int_en    = 1;
    ecat_cfg->REG0.rst_int_en    = 1;
    ecat_cfg->REG0.sync0_int_en  = 1;

    ecat_cfg->REG0.port0_type = PORT0_RMII_EN;
    ecat_cfg->REG0.port1_type = PORT1_RMII_EN;
    ecat_cfg->REG0.port2_type = PORT2_RMII_EN;

    ecat_cfg->REG0.port0_link_en = PORT0_EN;
    ecat_cfg->REG0.port1_link_en = PORT1_EN;
    ecat_cfg->REG0.port2_link_en = PORT2_EN;
    ecat_cfg->REG0.clockout_select = 0;

    ecat_cfg->REG0.tx_shift0 = 2;
    ecat_cfg->REG0.tx_shift1 = 2;
    ecat_cfg->REG0.tx_shift2 = 2;

    ecat_cfg->REG0.phy_rst_mask = 0;
    writel(ecat_cfg->REG0.reg, BASE_CFG0_ETHERCAT);

    ecat_cfg->REG1.tx_shift0_manual = 0;
    ecat_cfg->REG1.tx_shift1_manual = 0;
    ecat_cfg->REG1.tx_shift2_manual = 0;
    ecat_cfg->REG1.rmii0_rx_bypass = 1;
    ecat_cfg->REG1.rmii1_rx_bypass = 1;
    ecat_cfg->REG1.rmii2_rx_bypass = 1;

    writel(ecat_cfg->REG1.reg, BASE_CFG1_ETHERCAT);

    writel(readl(BASE_CFG0_ETHERCAT) ^ (0x01 << 13), BASE_CFG0_ETHERCAT);//register sync


    if(PORT0_RMII_EN) {

    }
    if(PORT0_RMII_EN) {

    }
    if(PORT0_RMII_EN) {

    }

}
