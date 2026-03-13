#ifndef AIC_ECAT_PHY_H_
#define AIC_ECAT_PHY_H_

void ecat_phy_reset_cfg(u8 released);
int ecat_phy_pdi_access_valid(void);
int ecat_phy_access(u8 pdi);
int ecat_phy_write(u8 phy, u8 reg_addr, u16 value);
u16 ecat_phy_read(u8 phy, u8 reg_addr);
int ecat_set_phy_led_mode(u8 phy);
int ecat_phy_init(void);

#endif
