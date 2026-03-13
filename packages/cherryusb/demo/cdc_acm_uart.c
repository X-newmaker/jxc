/*
 * Copyright (c) 2024, ArtInChip Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Authors: duanmt@artinchip.com
 */

#include <aic_core.h>
#include "usbd_core.h"
#include "usbd_cdc.h"
//#ifdef USB_DEV_EXAMPLE_CDC_ACM
#define DEBUG

#ifdef DEBUG
#undef USB_LOG_DBG
#define USB_LOG_DBG USB_LOG_INFO
#endif

/*!< endpoint address */
#define CDC_INT_EP  0x82
#define CDC_OUT_EP  0x02
#define CDC_IN_EP   0x81

#define USBD_VID           0x33C3
#define USBD_PID           0x7788
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define AICUPG_UART_DEV_NO 2

/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_ACM_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

/*!< global descriptor */
static const uint8_t cdc_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_1_1, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, CDC_MAX_MPS, 0x02),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'A', 0x00,                  /* wcChar0 */
    'r', 0x00,                  /* wcChar1 */
    't', 0x00,                  /* wcChar2 */
    'I', 0x00,                  /* wcChar3 */
    'n', 0x00,                  /* wcChar4 */
    'C', 0x00,                  /* wcChar5 */
    'h', 0x00,                  /* wcChar6 */
    'i', 0x00,                  /* wcChar7 */
    'p', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x2A,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'A', 0x00,                  /* wcChar0 */
    'r', 0x00,                  /* wcChar1 */
    't', 0x00,                  /* wcChar2 */
    'I', 0x00,                  /* wcChar3 */
    'n', 0x00,                  /* wcChar4 */
    'C', 0x00,                  /* wcChar5 */
    'h', 0x00,                  /* wcChar6 */
    'i', 0x00,                  /* wcChar7 */
    'p', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'L', 0x00,                  /* wcChar10 */
    'i', 0x00,                  /* wcChar11 */
    'n', 0x00,                  /* wcChar12 */
    'k', 0x00,                  /* wcChar13 */
    'e', 0x00,                  /* wcChar14 */
    'r', 0x00,                  /* wcChar15 */
    ' ', 0x00,                  /* wcChar16 */
    '2', 0x00,                  /* wcChar16 */
    '.', 0x00,                  /* wcChar16 */
    '0', 0x00,                  /* wcChar17 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x12,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '0', 0x00,                  /* wcChar3 */
    '0', 0x00,                  /* wcChar4 */
    '5', 0x00,                  /* wcChar5 */
    '2', 0x00,                  /* wcChar6 */
    '0', 0x00,                  /* wcChar7 */
//#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x40,
    0x01,
    0x00,
//#endif
    0x00
};

#define AICUPG_BUF_SIZE         2048

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[AICUPG_BUF_SIZE] = "";
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t write_buffer[AICUPG_BUF_SIZE] = "";

volatile bool ep_tx_busy_flag = false;
volatile uint8_t dtr_enable = 0;
volatile bool test_flag = false;    /* 测试代码 */
volatile uint16_t test_nbytes = 10; /* 测试代码 */

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

void usbd_event_handler(uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            ep_tx_busy_flag = false;
            dtr_enable = 0;
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            /* setup first out ep read transfer */
            usbd_ep_start_read(CDC_OUT_EP, read_buffer, AICUPG_BUF_SIZE);
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

void usbd_cdc_acm_bulk_out(uint8_t ep, uint32_t nbytes)
{
    memcpy(write_buffer, read_buffer, nbytes);
    USB_LOG_INFO("usbd_cdc_acm_bulk_out %d\n", nbytes);
    test_flag = true;	    /* 测试代码 */
    test_nbytes = nbytes;   /* 测试代码 */
    /* setup next out ep read transfer */
    usbd_ep_start_read(CDC_OUT_EP, read_buffer, AICUPG_BUF_SIZE);
}

void usbd_cdc_acm_bulk_in(uint8_t ep, uint32_t nbytes)
{
    if ((nbytes % CDC_MAX_MPS) == 0 && nbytes) {
        /* send zlp */
        usbd_ep_start_write(CDC_IN_EP, NULL, 0);
    } else {
        ep_tx_busy_flag = false;
    }
}

/*!< endpoint call back */
struct usbd_endpoint cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = usbd_cdc_acm_bulk_out
};

struct usbd_endpoint cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = usbd_cdc_acm_bulk_in
};

static struct usbd_interface intf0;
static struct usbd_interface intf1;

int cdc_acm_init(void)
{
    usbd_desc_register(cdc_descriptor);
    usbd_add_interface(usbd_cdc_acm_init_intf(&intf0));
    usbd_add_interface(usbd_cdc_acm_init_intf(&intf1));
    usbd_add_endpoint(&cdc_out_ep);
    usbd_add_endpoint(&cdc_in_ep);
    usbd_initialize();
    return 0;
}

void usbd_cdc_acm_set_dtr(uint8_t intf, bool dtr)
{
    if (dtr) {
        USB_LOG_INFO("intf: %d, dtr: %d\n", intf, dtr);
        dtr_enable = 1;
    } else {
        dtr_enable = 0;
    }
}

void cdc_acm_data_send_with_dtr_test(void)
{
	if (test_flag == false) /* 测试代码 */
		return;
	test_flag = false;      /* 测试代码 */
    USB_LOG_INFO("dtr_enable: %d, busy_flag: %d test_nbytes%d\n", dtr_enable, ep_tx_busy_flag, test_nbytes);
    if (dtr_enable && ep_tx_busy_flag == false) {
        ep_tx_busy_flag = true;
        usbd_ep_start_write(CDC_IN_EP, write_buffer, test_nbytes);
        while (ep_tx_busy_flag) {
        }
    }
}

#ifdef DEBUG_ENABLE_LOCAL_UART

#pragma GCC optimize ("O0")
static int baudrate_is_valid(u32 rate)
{
    int i;
    u32 rates[] = {BAUD_RATE_115200,
                   BAUD_RATE_230400,
                   BAUD_RATE_460800,
                   BAUD_RATE_921600,
                   BAUD_RATE_2000000,
                   BAUD_RATE_3000000};

    for (i = 0; i < ARRAY_SIZE(rates); i++) {
        if (rate == rates[i])
            return 1;
    }

    return 0;
}

rt_err_t aic_uart_configure(u32 index, struct serial_configure *cfg);

void usbd_cdc_acm_set_line_coding(uint8_t intf,
                                  struct cdc_line_coding *line_coding)
{
    struct serial_configure cfg = {0};
    int ret = 0;

    if (!g_aicupg_uart)
        return;

    if (!memcmp(line_coding, &g_aicupg_line, sizeof(struct cdc_line_coding))) {
        USB_LOG_DBG("%s() No change\n", __func__);
        return;
    }

    if (!baudrate_is_valid(line_coding->dwDTERate)) {
        pr_warn("Invalid baudrate %d\n", (u32)line_coding->dwDTERate);
        return;
    }
    cfg.baud_rate = line_coding->dwDTERate;

    if (line_coding->bDataBits < DATA_BITS_5
        || line_coding->bDataBits > DATA_BITS_8) {
        pr_warn("Invalid data bits %d\n", line_coding->bDataBits);
        return;
    }
    cfg.data_bits = line_coding->bDataBits;
    cfg.stop_bits = 1;

    USB_LOG_INFO("Change UART: Baud rate %d, Bits %d, Parity %d\n",
            (u32)line_coding->dwDTERate, line_coding->bDataBits,
            line_coding->bParityType);

    ret = aic_uart_configure(AICUPG_UART_DEV_NO, &cfg);
    if (ret < 0) {
        pr_err("Failed to config UART.  ret = -%d\n", -ret);
        return;
    }
    memcpy(&g_aicupg_line, line_coding, sizeof(struct cdc_line_coding));
}

void usbd_cdc_acm_get_line_coding(uint8_t intf,
                                  struct cdc_line_coding *line_coding)
{
    if (!g_aicupg_uart)
        return;

    memcpy(line_coding, &g_aicupg_line, sizeof(struct cdc_line_coding));
}

#endif
//#endif
