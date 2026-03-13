/*
 * Copyright (c) 2023, Artinchip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Wu Dehuang <dehuang.wu@artinchip.com>
 */

#include <sfud.h>
#include <hal_qspi.h>
#include <spinor_port.h>
#include <all_inc.h>


#if defined(AIC_USING_QSPI1)
#define AIC_DEV_QSPI1_MAX_SRC_FREQ_HZ 50000000
#define AIC_QSPI1_BUS_WIDTH_4
#define AIC_QSPI1_BUS_WIDTH 4
#define AIC_DEV_QSPI1_DELAY_MODE 2
#define AIC_QSPI1_DEVICE_SPINOR
#define AIC_QSPI1_DEVICE_SPINOR_FREQ 50000000
#endif

#if defined(AIC_USING_QSPI0)
#define AIC_DEV_QSPI0_MAX_SRC_FREQ_HZ 50000000
#define AIC_QSPI0_BUS_WIDTH_4
#define AIC_QSPI0_BUS_WIDTH 4
#define AIC_DEV_QSPI0_DELAY_MODE 2
#define AIC_QSPI0_DEVICE_SPINOR
#define AIC_QSPI0_DEVICE_SPINOR_FREQ 50000000
#endif

static struct aic_qspi_bus qspi_bus_arr[] = {
#if defined(AIC_USING_QSPI0)
    {
        .name = "qspi0",
        .idx = 0,
        .clk_id = CMU_MOD_SPI0,
        .clk_in_hz = AIC_DEV_QSPI0_MAX_SRC_FREQ_HZ,
        .bus_hz = AIC_QSPI0_DEVICE_SPINOR_FREQ,
        //.dma_port_id = DMA_ID_CS_SPI0,
        .irq_num = CPU_IRQ_SPI0,
        .dl_width = AIC_QSPI0_BUS_WIDTH,
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
        .cs_num = AIC_QSPI0_CS_NUM,
#endif
        .rxd_dylmode = AIC_DEV_QSPI0_DELAY_MODE,
    },
#endif
#if defined(AIC_USING_QSPI1)
    {
        .name = "qspi1",
        .idx = 1,
        .clk_id = CMU_MOD_SPI1,
        .clk_in_hz = AIC_DEV_QSPI1_MAX_SRC_FREQ_HZ,
        .bus_hz = AIC_QSPI1_DEVICE_SPINOR_FREQ,
        //.dma_port_id = DMA_ID_CS_SPI1,
        .irq_num = CPU_IRQ_SPI1,
        .dl_width = AIC_QSPI1_BUS_WIDTH,
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
        .cs_num = AIC_QSPI1_CS_NUM,
#endif
        .rxd_dylmode = AIC_DEV_QSPI1_DELAY_MODE,
    },
#endif
#if defined(AIC_USING_QSPI2)
    {
        .name = "qspi2",
        .idx = 2,
        .clk_id = CMU_MOD_SPI2,
        .clk_in_hz = AIC_DEV_QSPI2_MAX_SRC_FREQ_HZ,
        .bus_hz = AIC_QSPI2_DEVICE_SPINOR_FREQ,
        .dma_port_id = DMA_ID_CS_SPI2,
        .irq_num = CPU_IRQ_SPI2,
        .dl_width = AIC_QSPI2_BUS_WIDTH,
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
        .cs_num = AIC_QSPI2_CS_NUM,
#endif
        .rxd_dylmode = AIC_DEV_QSPI2_DELAY_MODE,
    },
#endif
#if defined(AIC_USING_QSPI3)
    {
        .name = "qspi3",
        .idx = 3,
        .clk_id = CMU_MOD_SPI3,
        .clk_in_hz = AIC_DEV_QSPI3_MAX_SRC_FREQ_HZ,
        .bus_hz = AIC_QSPI3_DEVICE_SPINOR_FREQ,
        .dma_port_id = DMA_ID_CS_SPI3,
        .irq_num = CPU_IRQ_SPI3,
        .dl_width = AIC_QSPI3_BUS_WIDTH,
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
        .cs_num = AIC_QSPI3_CS_NUM,
#endif
        .rxd_dylmode = AIC_DEV_QSPI3_DELAY_MODE,
    },
#endif
};

static void retry_delay_100us(void)
{
    gtc_dly_time(GTC_US, 100);
}

static struct aic_qspi_bus *get_qspi_by_index(u32 idx)
{
    struct aic_qspi_bus *qspi;
    u32 i;

    qspi = NULL;
    for (i = 0; i < ARRAY_SIZE(qspi_bus_arr); i++) {
        if (qspi_bus_arr[i].idx == idx) {
            qspi = &qspi_bus_arr[i];
            break;
        }
    }

    return qspi;
}

#ifdef SFUD_USING_QSPI

static u32 address_copy(u32 addr, u32 size, u8 *dst)
{
    u32 i;

    i = 0;
    while (size) {
        dst[i++] = (addr >> (8 * (size - 1))) & 0xFF;
        size--;
    }
    return i;
}

static sfud_err qspi_read(const struct __sfud_spi *spi, u32 addr,
                          sfud_qspi_read_cmd_format *rd_fmt, u8 *read_buf,
                          size_t read_size)
{
    struct aic_qspi_bus *qspi;
    struct qspi_transfer t;
    u8 cmdbuf1[16];
    u8 cmdbuf2[16];
    u32 addrsiz, cs_num = 0;
    int ret, single_cnt, rest_cnt, dummy_cnt, rest_buswidth;

    qspi = (struct aic_qspi_bus *)spi->user_data;

    single_cnt = 0;
    rest_cnt = 0;
    rest_buswidth = HAL_QSPI_BUS_WIDTH_SINGLE;
    dummy_cnt = (rd_fmt->address_lines * rd_fmt->dummy_cycles / 8);
    if (rd_fmt->instruction_lines == 1) {
        cmdbuf1[single_cnt] = rd_fmt->instruction;
        single_cnt++;
    } else if (rd_fmt->instruction_lines > 1) {
        cmdbuf2[rest_cnt] = rd_fmt->instruction;
        rest_cnt++;
        if (rd_fmt->instruction_lines > rest_buswidth)
            rest_buswidth = rd_fmt->instruction_lines;
    }

    addrsiz = rd_fmt->address_size / 8;
    if (rd_fmt->address_lines == 1) {
        single_cnt += address_copy(addr, addrsiz, &cmdbuf1[single_cnt]);
        memset(&cmdbuf1[single_cnt], 0, dummy_cnt);
        single_cnt += dummy_cnt;
    } else if (rd_fmt->address_lines > 1) {
        rest_cnt += address_copy(addr, addrsiz, &cmdbuf2[rest_cnt]);
        memset(&cmdbuf2[rest_cnt], 0, dummy_cnt);
        rest_cnt += dummy_cnt;
        if (rd_fmt->address_lines > rest_buswidth)
            rest_buswidth = rd_fmt->address_lines;
    }

#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
    cs_num = qspi->cs_num;
#endif
    hal_qspi_master_set_cs(&qspi->handle, cs_num, true);

    /* Command phase */
    if (single_cnt) {
        hal_qspi_master_set_bus_width(&qspi->handle, HAL_QSPI_BUS_WIDTH_SINGLE);
        t.rx_data = NULL;
        t.tx_data = cmdbuf1;
        t.data_len = single_cnt;
        ret = hal_qspi_master_transfer_sync(&qspi->handle, &t);
        if (ret)
            goto out;
    }
    if (rest_cnt) {
        hal_qspi_master_set_bus_width(&qspi->handle, rest_buswidth);
        t.rx_data = NULL;
        t.tx_data = cmdbuf2;
        t.data_len = rest_cnt;
        ret = hal_qspi_master_transfer_sync(&qspi->handle, &t);
        if (ret)
            goto out;
    }

    /* Read data phase */

    hal_qspi_master_set_bus_width(&qspi->handle, rd_fmt->data_lines);
    t.rx_data = read_buf;
    t.tx_data = NULL;
    t.data_len = read_size;

    ret = hal_qspi_master_transfer_sync(&qspi->handle, &t);

out:
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
    cs_num = qspi->cs_num;
#endif
    hal_qspi_master_set_cs(&qspi->handle, cs_num, false);
    return ret;
}
#endif

static sfud_err spi_set_speed(const struct __sfud_spi *spi, u32 bus_hz)
{
    struct aic_qspi_bus *qspi;

    qspi = (struct aic_qspi_bus *)spi->user_data;

    if (qspi == NULL)
        return SFUD_ERR_NOT_FOUND;

    cmu_mod_set_freq(qspi->clk_id, bus_hz);

    return SFUD_SUCCESS;
}

static sfud_err spi_get_bus_id(const struct __sfud_spi *spi, u32 *bus_id)
{
    struct aic_qspi_bus *qspi;

    qspi = (struct aic_qspi_bus *)spi->user_data;

    if (qspi == NULL)
        return SFUD_ERR_NOT_FOUND;

    *bus_id = qspi->idx;

    return SFUD_SUCCESS;
}

static sfud_err spi_write_read(const struct __sfud_spi *spi,
                               const u8 *write_buf, size_t write_size,
                               u8 *read_buf, size_t read_size)
{
    struct aic_qspi_bus *qspi;
    struct qspi_transfer t;
    int ret = 0;
    u32 cs_num = 0;

    qspi = (struct aic_qspi_bus *)spi->user_data;

    hal_qspi_master_set_bus_width(&qspi->handle, HAL_QSPI_BUS_WIDTH_SINGLE);
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
    cs_num = qspi->cs_num;
#endif
    hal_qspi_master_set_cs(&qspi->handle, cs_num, true);
    if (write_size) {
        t.rx_data = NULL;
        t.tx_data = (u8 *)write_buf;
        t.data_len = write_size;
        ret = hal_qspi_master_transfer_sync(&qspi->handle, &t);
        if (ret < 0)
            goto out;
    }
    if (read_size) {
        t.rx_data = read_buf;
        t.tx_data = NULL;
        t.data_len = read_size;
        ret = hal_qspi_master_transfer_sync(&qspi->handle, &t);
    }
out:
#if defined(AIC_QSPI_MULTIPLE_CS_NUM)
    cs_num = qspi->cs_num;
#endif
    hal_qspi_master_set_cs(&qspi->handle, cs_num, false);
    return ret;
}

sfud_err sfud_spi_port_init(sfud_flash *flash)
{
    sfud_err result = SFUD_SUCCESS;

    /* port SPI device interface */
    flash->spi.wr = spi_write_read;
    flash->spi.set_speed = spi_set_speed;
    flash->spi.get_bus_id = spi_get_bus_id;
#ifdef SFUD_USING_QSPI
    flash->spi.qspi_read = (void *)qspi_read;
#endif
    flash->spi.lock = NULL;
    flash->spi.unlock = NULL;
    flash->spi.user_data = flash->user_data;
    /* 100 microsecond delay */
    flash->retry.delay = retry_delay_100us;
    /* 60 seconds timeout */
    flash->retry.times = 60 * 10000;

    return result;
}

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')
void sfud_hexdump(const u8 *ptr, u32 buflen)
{
    unsigned char *buf = (unsigned char *)ptr;
    int i, j;
    for (i = 0; i < buflen; i += 16) {
        printk("%06x: ", i);
        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printk("%02x ", buf[i + j]);
            else
                printk("   ");
        printk(" ");
        for (j = 0; j < 16; j++)
            if (i + j < buflen)
                printk("%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
        printk("\n");
    }
}

sfud_flash *sfud_probe(u32 spi_bus)
{
    sfud_err result = SFUD_SUCCESS;
    struct aic_qspi_bus *qspi;
    struct mtd_dev *mtd;
    struct mtd_partition *part, *p;
    int ret;
    struct qspi_master_config cfg = {0};
    char *partstr;

    qspi = get_qspi_by_index(spi_bus);
    if (!qspi) {
        printk("spi bus is invalid: %d\n", spi_bus);
        return NULL;
    }

    if ((qspi->probe_flag) && (qspi->attached_flash.init_ok))
        return &qspi->attached_flash;

    memset(&cfg, 0, sizeof(cfg));
    cfg.idx = qspi->idx;
    cfg.clk_in_hz = qspi->clk_in_hz;
    cfg.clk_id = qspi->clk_id;
    cfg.cpol = HAL_QSPI_CPOL_ACTIVE_HIGH;
    cfg.cpha = HAL_QSPI_CPHA_FIRST_EDGE;
    cfg.cs_polarity = HAL_QSPI_CS_POL_VALID_LOW;
    cfg.rx_dlymode = qspi->rxd_dylmode;
    cfg.tx_dlymode = aic_convert_tx_dlymode(qspi->txc_dylmode, qspi->txd_dylmode);

    ret = hal_qspi_master_init(&qspi->handle, &cfg);
    if (ret) {
        printk("hal_qspi_master_init failed. ret %d\n", ret);
        return NULL;
    }

    qspi->attached_flash.user_data = (void *)qspi;
    qspi->attached_flash.init_hz = SFUD_READ_SFDP_FREQ;
    qspi->attached_flash.bus_hz = qspi->bus_hz;

    result = sfud_device_init(&qspi->attached_flash);
    if (result != SFUD_SUCCESS) {
        printk("sfud_device_init failed: ret %d\n", result);
        return NULL;
    }

#ifdef SFUD_USING_QSPI
    sfud_qspi_fast_read_enable(&qspi->attached_flash, qspi->dl_width);
#endif

    qspi->probe_flag = true;
    return &qspi->attached_flash;
}
