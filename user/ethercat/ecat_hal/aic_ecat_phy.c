#include <all_inc.h>

#include "aic_ecat_cfg.h"

void ecat_phy_reset_cfg(u8 released)
{
        ecat_cfg->REG0.phy_rst_released = released;
        writel(readl(BASE_CFG0_ETHERCAT) ^ (0x01 << 13), BASE_CFG0_ETHERCAT);//register sync
}


int ecat_phy_pdi_access_valid(void)
{
        if((readl(BASE_EtherCAT + 0x514) & ((0x01 << 16) | (0x01 << 25))) == 0)
            return RET_OK;
        else
            return RET_FALSE;
}

//0:ecat 1:pdi
int ecat_phy_access(u8 pdi)
{
        writeb(readb(BASE_EtherCAT + 0x517) | pdi, BASE_EtherCAT + 0x517);
        if(readb(BASE_EtherCAT + 0x517) & 0x01)
            return RET_OK;
        else
            return RET_FALSE;
}

int ecat_phy_write(u8 phy, u8 reg_addr, u16 value)
{
        int delay = 0xffff;
        u16 val;
        writeb(phy, BASE_EtherCAT + 0x512);//phy address
        writeb(reg_addr, BASE_EtherCAT + 0x513);//reg address
        writeb(value&0xff, BASE_EtherCAT + 0x514);//data low
        writeb((value>>8)&0xff, BASE_EtherCAT + 0x515);//data high
        writeb(readb(BASE_EtherCAT + 0x511) | 0x02, BASE_EtherCAT + 0x511);//initate write
        while((readb(BASE_EtherCAT + 0x511) & 0x80) && (delay != 0)) {//busy
            delay--;
        }
        if(delay)
            return RET_OK;
        else
            return RET_FALSE;
}

u16 ecat_phy_read(u8 phy, u8 reg_addr)
{
        int delay = 0xffff;
        writeb(phy, BASE_EtherCAT + 0x512);//phy address
        writeb(reg_addr, BASE_EtherCAT + 0x513);//reg address
        writeb(readb(BASE_EtherCAT + 0x511) | 0x01, BASE_EtherCAT + 0x511);//initate write
        while((readb(BASE_EtherCAT + 0x511) & 0x80) && (delay != 0)) {//busy
            delay--;
        }
        if(delay)
            return readl(BASE_EtherCAT + 0x514) & 0xffff;
        else
            return 0xffff;
}

int ecat_set_phy_led_mode(u8 phy)
{
        u16 phyid[2];
        u16 val, ret = RET_OK;
        if(ecat_phy_pdi_access_valid() == RET_OK) {
            if(ecat_phy_access(1) == RET_OK) {
                    //for(int i = 0; i<0x18; i++)
                    //    printk("reg %x:%x\n",i, ecat_phy_read(phy, i));
                    for(int i = 0; i < 2; i++) {
                        phyid[i] = ecat_phy_read(phy, i + 2);//value
                        printk("[ECAT]PHY:%d reg addr:%x value:%x\n", phy, i + 2, phyid[i]);
                    }
                    if(phyid[0] != PHY_ID0 || phyid[1] != PHY_ID1) {
                            printk("[ECAT]PHY is not support!\n");
                            ecat_phy_access(0);
                            return RET_FALSE;
                    }
                    #ifdef PHY_RTL8201
                    u8 page = 7;
                    u8 reg = 19;
                    if(ecat_phy_write(phy, 31, page) == RET_OK) {
                        val = ecat_phy_read(phy, reg);
                        val &= ~(0x03 <<4);     //mode 0
                        ecat_phy_write(phy, reg, val);
                        if(val != ecat_phy_read(phy, reg)) {
                            ret = RET_FALSE;
                        }
                        ecat_phy_write(phy, 31, 0); //switch to page 0
                    } else {
                        ret = RET_FALSE;
                    }
                    #endif
                    #ifdef PHY_YT8522
                    #define DBG_ADDR_OFF 0x1E
                    #define DBG_DATA_OFF 0x1F
                    #define DBG_LED1_OFF 0x40C3
                            ecat_phy_write(phy, DBG_ADDR_OFF, DBG_LED1_OFF);
                            val = ecat_phy_read(phy, DBG_DATA_OFF);
                            val &= ~(0x01 <<9);
                            ecat_phy_write(phy, DBG_ADDR_OFF, DBG_LED1_OFF);
                            ecat_phy_write(phy, DBG_DATA_OFF, 0x30);
                            val = ecat_phy_read(phy, DBG_DATA_OFF);
                    #endif
                    #ifdef PHY_DP83822
                           //do nothing, not need config
                           

                    #endif
            } else {
                    ret = RET_FALSE;
            }
        } else {
                ret = RET_FALSE;
        }
        ecat_phy_access(0);
        return ret;
}

int ecat_phy_init(void)
{
        s32 ret;
        ret = ecat_set_phy_led_mode(0);
        if(ret != RET_OK) {
                printk("[ECAT]phy0 configuration failed!\n");
                return RET_FALSE;
        }

        #if PORT1_EN == 1
        ret = ecat_set_phy_led_mode(1);
        if(ret != RET_OK) {
                printk("[ECAT]phy1 configuration failed!\n");
                return RET_FALSE;
        }
        #endif
        #if PORT2_EN == 1
        ret = ecat_set_phy_led_mode(2);
        if(ret != RET_OK) {
                printk("[ECAT]phy2 configuration failed!\n");
                return RET_FALSE;
        }
        #endif
        return RET_OK;
}
