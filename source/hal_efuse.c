/*
 * Copyright (c) 2022-2023, ArtInChip Technology Co., Ltd
 *
 */

#include <all_inc.h>


#define EFUSE_REG_CTL       (BASE_SID + 0x0000)
#define EFUSE_REG_ADDR      (BASE_SID + 0x0004)
#define EFUSE_REG_WDATA     (BASE_SID + 0x0008)
#define EFUSE_REG_RDATA     (BASE_SID + 0x000C)
#define EFUSE_REG_TIMING    (BASE_SID + 0x0010)
#define EFUSE_REG_PWRCFG    (BASE_SID + 0x0014)
#define EFUSE_REG_WFRID     (BASE_SID + 0x0018)
#define EFUSE_REG_PKGID     (BASE_SID + 0x001C)
#define EFUSE_REG_JTAG      (BASE_SID + 0x0080)
#define EFUSE_REG_SRAM      (BASE_SID + 0x200)

#define EFUSE_CTL_BROM_PRIV_LOCK (0x1 << 28)

#define EFUSE_MAX_WORD      64
#define EFUSE_OP_CODE       0xA1C

#define EFUSE_STS_INITIALIZING 1
#define EFUSE_STS_IDLE         2
#define EFUSE_STS_WRITING      3
#define EFUSE_STS_READING      4

int hal_efuse_init(void)
{
    cmu_mod_enable(CMU_MOD_SID);
    return 0;
}

int hal_efuse_deinit(void)
{
    cmu_mod_disable(CMU_MOD_SID);
    return 0;
}

int hal_efuse_wait_ready(void)
{
    u32 val, msk;
    int i;

    msk = (0xF << 8);
    for (i = 1000; i > 0; i--) {
        val = readl(EFUSE_REG_CTL);
        if ((val & msk) == (EFUSE_STS_IDLE << 8))
            return 0;
    }

    return -1;
}

int hal_efuse_read(u32 wid, u32 *wval)
{
    u32 i, addr, rval = 0, val = 0;

    if (wid >= EFUSE_MAX_WORD) {
        printk("Error, word id is too large.\n");
        return -1;
    }

    for (i = 0; i < 2; i++) {
        addr = (wid + EFUSE_MAX_WORD * i) << 2;
        writel(addr, EFUSE_REG_ADDR);

        /*
         * bit[27:16] OP CODE
         * bit[4] read start
         */
        val = readl(EFUSE_REG_CTL);
        val &= ~((0xFFF << 16) | (1 << 4));
        val |= ((EFUSE_OP_CODE << 16) | (1 << 4));
        writel(val, EFUSE_REG_CTL);

        /* Wait read finish */
        while(readl(EFUSE_REG_CTL) & (1 << 4));

        rval |= readl(EFUSE_REG_RDATA);
    }
    *wval = rval;

    return 0;
}

//wid: 用户手册 Secure ID 章节512 bit 空间映射定义表格的 "禁止位"
//wval: 写入的内容
//BROM_SECURE为例： wid=1， wval=根据bit定义。
int hal_efuse_write(u32 wid, u32 wval)
{
    u32 addr, val, i;

    if (wid >= EFUSE_MAX_WORD) {
        printk("Error, word id is too large.\n");
        return -1;
    }

    for (i = 0; i < 2; i++) {
        addr = (wid + EFUSE_MAX_WORD * i) << 2;
        writel(addr, EFUSE_REG_ADDR);
        writel(wval, EFUSE_REG_WDATA);

        /*
        * bit[27:16] OP CODE
        * bit[0] read start
        */
        val = readl(EFUSE_REG_CTL);
        val &= ~((0xFFF << 16) | (1 << 0));
        val |= ((EFUSE_OP_CODE << 16) | (1 << 0));
        writel(val, EFUSE_REG_CTL);

        /* Wait write finish */
        while(readl(EFUSE_REG_CTL) & (1 << 0));
    }

    return 0;
}
