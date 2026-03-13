/*
 * Copyright (c) 2024, Artinchip Technology Co., Ltd
 */
#include <all_inc.h>
#include "hal_canfd.h"
#include "stdlib.h"
static void canfd0_null(void){};
static void canfd1_null(void){};

cpu_irq_fun_t canfd0_irqhandle = canfd0_null;
cpu_irq_fun_t canfd1_irqhandle = canfd1_null;

__can_para_t can_para[CANFD_LAST + 1];



void canfd0_irq_handler(void)
{
        canfd0_irqhandle();
}

ATTRIBUTE_ISR void CANFD0_IRQHandler(void)
{
        canfd0_irq_handler();
}

void canfd1_irq_handler(void)
{
        canfd1_irqhandle();
}

ATTRIBUTE_ISR void CANFD1_IRQHandler(void)
{
        canfd1_irq_handler();
}



void canfd_irq_register(u8 num, cpu_irq_fun_t irqhandle)
{
        switch(num) {
                case 0:
                        canfd0_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_CANFD0);
                        break;
                case 1:
                        canfd1_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_CANFD1);
                        break;
                default:
                        break;
        }
}

void canfd_irq_unregister(u8 num)
{
        switch(num) {
                case 0:
                        canfd0_irqhandle = canfd0_null;
                        cpu_irq_disable(CPU_IRQ_CANFD0);
                        break;
                case 1:
                        canfd1_irqhandle = canfd1_null;
                        cpu_irq_disable(CPU_IRQ_CANFD1);
                        break;
                default:
                        break;
        }
}


u8 canfd_dlc2len(u8 dlc)
{

        if (dlc <= 8) {
                return dlc;
        } else {
                switch (dlc) {
                case 9:
                case 10:
                case 11:
                        return dlc = 8 + (dlc - 8) * 4;
                        break;
                case 0xc:
                        return 24;
                        break;
                case 0xd:
                        return 32;
                        break;
                case 0xe:
                        return 48;
                        break;
                case 0xf:
                        return 64;
                        break;
                default:
                        return 0;
                }
        }
}


u8 canfd_len2dlc(u8 len)
{
        if (len <= 8) {
                return len;
        } else {
                switch (len) {
                case 12:
                case 16:
                case 20:
                case 24:
                        return (len-8)/4 + 0x8;
                        break;
                case 32:
                        return 0xd;
                        break;
                case 48:
                        return 0xe;
                        break;
                case 64:
                        return 0xf;
                        break;
                default:
                        return 0;
                }
        }
}

/**
  * @brief  set or reset the whole controller
  * @param  para: the pointer to the structure of the can
  * @param  reset:
  *   This parameter can be one of the following values:
  *     @arg CANFD_ACT_RESET   : set the can controller
  *     @arg CANFD_NOT_RESET   : reset the can controller
  */
void canfd_set_reset_mode(__can_para_t *para, u8 reset)
{
    if(reset == CANFD_ACT_RESET) {
        para->canfd_p->CFG_STAT |= CANFD_SET_RST_MASK;
    } else {
        para->canfd_p->CFG_STAT &= ~CANFD_SET_RST_MASK;
        while(CANFD_NOT_RESET != canfd_get_reset_mode(para)) {
            continue;
        }
    }
}

/**
  * @brief  get the status of the can controller
  * @param  para: the pointer to the structure of the can
  * @retval
  *     @arg CANFD_ACT_RESET   : the can controller is in reset status
  *     @arg CANFD_NOT_RESET   : the can controller is in normal status
  */
u32 canfd_get_reset_mode(__can_para_t *para)
{
    if(para->canfd_p->CFG_STAT & CANFD_SET_RST_MASK) {
        return CANFD_ACT_RESET;
    } else {
        return CANFD_NOT_RESET;
    }
}

/**
  * @brief  get the Receive buffer status
  * @param  para: the pointer to the structure of the can
  * @retval The return value can be one of the following values:
  *     @arg CANFD_RSTAT_EMP           : receive buffer status: empty
  *     @arg CANFD_RSTAT_SOME          : receive buffer status: between empty and almost full
  *     @arg CANFD_RSTAT_ALMOSTFULL    : receive buffer status: almost full
  *     @arg CANFD_RSTAT_FULL          : receive buffer status: full
  */
u8 canfd_get_rec_ctrl_status(__can_para_t *para)
{
    return (para->canfd_p->RCTRL & CANFD_RSTAT_MASK);
}

/**
  * @brief  get the Transmit buffer status
  * @param  para: the pointer to the structure of the can
  * @retval The return value can be one of the following values:
  *     @arg CANFD_TSSTAT_EMP                  : transmission secondary STATus empty
  *     @arg CANFD_TSSTAT_LESS_EQU_HALF        : transmission secondary STATus less or equal to half
  *     @arg CANFD_TSSTAT_MORE_HALF            : transmission secondary STATus more than half
  *     @arg CANFD_TSSTAT_FULL                 : transmission secondary STATus full
  */
u8 canfd_get_tbuf_ctrl_status(__can_para_t *para)
{
    return (para->canfd_p->TCTRL & CANFD_TSSTAT_MASK);
}


/**
  * @brief  interrupt configuration
  * @param  para: the pointer to the structure of the can
  * @param  set_int_en:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_RIE_MASK                   : receive interrupt enable
  *  @arg  CANFD_ROIE_MASK                  : receive buffer overrun interrupt enable
  *  @arg  CANFD_RFIE_MASK                  : receive buffer full interrupt enable
  *  @arg  CANFD_RAFIE_MASK                 : receive buffer almost full interrupt enable
  *  @arg  CANFD_TPIE_MASK                  : transmission primary interrupt enable
  *  @arg  CANFD_TSIE_MASK                  : transmission secondary interrupt enable
  *  @arg  CANFD_EIE_MASK                   : error interrupt enable
  * @param  en:
  *    This parameter can be one of the following values:
  *  @arg  CAN_ENABLE                        : enable the interrupt
  *  @arg  CAN_DISABLE                       : disable the interrupt
  */
void canfd_cfg_interrupt(__can_para_t *para, u32 set_int_en, u32 en)
{
    if(en == CAN_ENABLE) {
        para->canfd_p->RTIE |= (set_int_en);
    } else {
        para->canfd_p->RTIE &= ~(set_int_en);
    }
}


/**
  * @brief  interrupt flag clear
  * @param  para: the pointer to the structure of the can
  * @param  clr_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_RIF_MASK                 : receive interrupt flag
  *  @arg  CANFD_ROIF_MASK                : receive buffer overrun interrupt flag
  *  @arg  CANFD_RFIF_MASK                : receive buffer full interrupt flag
  *  @arg  CANFD_RAFIF_MASK               : receive buffer almost full interrupt flag
  *  @arg  CANFD_TPIF_MASK                : transmission primary interrupt flag
  *  @arg  CANFD_TSIF_MASK                : transmission secondary interrupt flag
  *  @arg  CANFD_EIF_MASK                 : error interrupt flag
  *  @arg  CANFD_AIF_MASK                 : abort interrupt flag
  *  @arg  CANFD_ALLF_MASK                : all the interrupt flag
  */
void canfd_clr_cfg_interrupt_flag(__can_para_t *para, u32 clr_int_flag)
{
    para->canfd_p->RTIF = (clr_int_flag);
}


/**
  * @brief  interrupt error configuration
  * @param  para: the pointer to the structure of the can
  * @param  err_int_en:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_SET_EPIE_MASK              : error passive interrupt enable
  *  @arg  CANFD_SET_ALIE_MASK              : arbitration lost interrupt enable
  *  @arg  CANFD_SET_BEIE_MASK              : bus error interrupt enable
  * @param  en:
  *    This parameter can be one of the following values:
  *  @arg  CAN_ENABLE                        : enable the interrupt
  *  @arg  CAN_DISABLE                       : disable the interrupt
  */

void canfd_err_interrupt(__can_para_t *para, u32 err_int_en, u32 en)
{
    if(en == CAN_ENABLE) {
        para->canfd_p->ERRINT |= (err_int_en);
    } else {
        para->canfd_p->ERRINT &= ~(err_int_en);
    }
}

/**
  * @brief  interrupt error flag clear
  * @param  para: the pointer to the structure of the can
  * @param  clr_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_SET_EPIF_MASK            : error passive interrupt flag
  *  @arg  CANFD_SET_ALIF_MASK            : arbitration lost interrupt flag
  *  @arg  CANFD_SET_BEIF_MASK            : bus error interrupt flag
  */
void canfd_clr_err_interrupt_flag(__can_para_t *para, u32 clr_err_flag)
{
    para->canfd_p->ERRINT = (para->canfd_p->ERRINT & ~(CANFD_SET_EPIF_MASK | CANFD_SET_ALIF_MASK | CANFD_SET_BEIF_MASK) ) | (clr_err_flag);
}

/**
  * @brief  get the given interrupt flag status
  * @param  para: the pointer to the structure of the can
  * @param  get_int_flag:
  *     This parameter can be one of the following values:
    *  @arg     CANFD_RIF_MASK                         : receive interrupt flag
    *  @arg     CANFD_ROIF_MASK                        : receive buffer overrun interrupt flag
    *  @arg     CANFD_RFIF_MASK                        : receive buffer full interrupt flag
    *  @arg     CANFD_RAFIF_MASK                       : receive buffer almost full interrupt flag
    *  @arg     CANFD_TPIF_MASK                        : transmission primary interrupt flag
    *  @arg     CANFD_TSIF_MASK                        : transmission secondary interrupt flag
    *  @arg     CANFD_EIF_MASK                         : error interrupt flag
    *  @arg     CANFD_AIF_MASK                         : abort interrupt flag
  * @retval The return value can be one of the following values:
  *     @arg CAN_SET                                    : the status of the given interrupt flag is set
  *     @arg CAN_RESET                                  : the status of the given interrupt flag is reset
  */
u8 canfd_get_cfg_interrupt(__can_para_t *para, u32 get_int_flag)
{
    return (para->canfd_p->RTIF & (get_int_flag)) ? CAN_SET : CAN_RESET;
}

/**
  * @brief  get the given error interrupt flag status
  * @param  para: the pointer to the structure of the can
  * @param  get_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_SET_EPIF_MASK            : error passive interrupt flag
  *  @arg  CANFD_SET_ALIF_MASK            : arbitration lost interrupt flag
  *  @arg  CANFD_SET_BEIF_MASK            : bus error interrupt flag
  * @retval The return value can be one of the following values:
  *     @arg CAN_SET                                    : the status of the given interrupt flag is set
  *     @arg CAN_RESET                                  : the status of the given interrupt flag is reset
  */
u8 canfd_get_err_interrupt(__can_para_t *para, u32 get_err_flag)
{
    return (para->canfd_p->ERRINT & (get_err_flag)) ? CAN_SET : CAN_RESET;
}


/**
  * @brief  clear all the interrupt flags
  */
void canfd_cfg_int_all_clr(__can_para_t *para)
{
    para->canfd_p->RTIF = CANFD_ALLF_MASK;
    para->canfd_p->ERRINT = (CANFD_SET_EPIF_MASK | CANFD_SET_ALIF_MASK | CANFD_SET_BEIF_MASK);
    para->canfd_p->RTIE = 0;
}


/**
  * @brief  translate the dlc length to bytes
  * @param  para: the pointer to the structure of the can
  * @param  dlc: the dlc length (unit bytes) of can 2.0 or FD
  * @retval : return the actual dlc length in bytes (0 ~ 64 bytes)
  *
  */
u8 canfd_get_dlc_length(__can_para_t *para, u8 dlc)
{
    /*CAN 2.0*/
    if(para->can_type == CAN_MASK) {
        if(dlc > 8) {
            dlc = 8;
        }

        return dlc;
    } /*CAN FD*/ else {
        if(dlc <= 8) {     /* dlc = 0 ~ 8 */
            return dlc;

        } else if ( (dlc >= 9) && (dlc <= 12) ) {  /* dlc = 9 ~ 12 */
            dlc = (dlc - 6) * 4;
            return dlc;

        } else {       /* dlc = 13 ~ 15 */
            dlc = (dlc - 11) * 16;
            return dlc;
        }
    }
}

/**
  * @brief  get the error type
  * @param  para: the pointer to the structure of the can
  * @retval The return value can be one of the following values:
  *     @arg CANFD_SET_NOERR_MASK              : no error
  *     @arg CANFD_SET_BIT_ERROR_MASK          : bit error
  *     @arg CANFD_SET_FORM_ERROR_MASK         : form error
  *     @arg CANFD_SET_STUFF_ERROR_MASK        : stuff error
  *     @arg CANFD_SET_ACK_ERROR_MASK          : acknowledgement error
  *     @arg CANFD_SET_CRC_ERROR_MASK          : crc error
  *     @arg CANFD_SET_OTH_ERROR_MASK          : other error
  */
u8 canfd_kindoferror(__can_para_t *para)
{
    return para->canfd_p->EALCAP & CANFD_KOER_MASK;
}


/**
  * @brief  fill the parameters in the can structure
  * @param  para: the pointer to the structure of the can
  * @param  array: the pointer to the 64 bytes data array
  */
//#define CANFD_FRAME_PRINT
void canfd_fill_parameters(__can_para_t *para, u32* array)
{
    //u8 dlc_length_word = 0;
    u8 i;

    //can_para.can_clk = para->can_clk;
    para->slow_bitrate = ((para->slow_bitrate > 1000000) ? (1000000) : (para->slow_bitrate));
    para->fast_bitrate = ((para->fast_bitrate > 10000000) ? (10000000) : (para->fast_bitrate));
    //can_para.can_type = para->can_type;

    //can_para.id = para->id;

    para->id &= CAN_EFF_MASK;
    if(para->id & (CAN_EFF_MASK ^ CAN_SFF_MASK)) {
            para->control.IDE = IDE_1_EXTENDED_FORMAT;
    } else {
            para->control.IDE = IDE_0_STANDARD_FORMAT;
    }

    //para->control.DLC = para->control.DLC;
    if(para->control.DLC == 0) {
            para->control.RTR = RTR_1_REMOTE_FRAME;
    } else {
            para->control.RTR = RTR_0_DATA_FRAME;
    }

    if(para->can_type == CANFD_MASK) {
            para->control.FDF = FDF_1_CANFD_FRAME;
    } else {
            para->control.FDF = FDF_0_CAN2_0_FRAME;
    }

    if(para->fast_bitrate == para->slow_bitrate) {
            para->control.BRS = BRS_0_SLOW_BITRATE;
    } else {
            para->control.BRS = BRS_1_FAST_BITRATE;
            para->control.FDF = FDF_1_CANFD_FRAME;
    }

    para->dlc_length = canfd_get_dlc_length(para, para->control.DLC);

    para->dlc_length_word = para->dlc_length / 4;
    if(para->dlc_length % 4) {
            para->dlc_length_word ++;
    }
    //printk("[CANFD]dlc_length_word 0x%x\n", para->dlc_length_word);
    para->status = CAN_STATE_ERROR_ACTIVE;

    for(i = 0; i < 16; i ++) {
        if(i < para->dlc_length_word) {
                para->data[i] = array[i];
        } else {
                para->data[i] = 0;
        }
        //printk("[CANFD]para->data[i] 0x%x\n", para->data[i]);
    }

    printk("[CANFD]======= parameters =======\n");
    printk("[CANFD]can clk = %d MHz\n", para->can_clk);

    if(para->can_type == CAN_MASK) {
        printk("[CANFD]can type:  CAN 2.0\n");
        printk("[CANFD]baud rate = %d bps\n", para->slow_bitrate);
    } else {
        printk("[CANFD]can type:  CAN FD\n");
        printk("[CANFD]baud rate slow = %d bps\n", para->slow_bitrate);
        if(para->control.BRS == 1) {
            printk("[CANFD]baud rate fast = %d bps\n", para->fast_bitrate);
        }
    }

    if(para->control.IDE == IDE_0_STANDARD_FORMAT) {
        printk("[CANFD]standard frame\n");
    } else {
        printk("[CANFD]extended frame\n");
    }

    printk("[CANFD]ID = 0x%x\n", para->id);

    if(para->control.RTR == RTR_0_DATA_FRAME) {
        printk("[CANFD]data frame\n");
    } else {
        printk("[CANFD]remote frame\n");
    }

    printk("[CANFD]DLC = %d\n", para->control.DLC);
    printk("[CANFD]actual DLC length = %d bytes\n", para->dlc_length);

    printk("[CANFD]======= parameters =======\n");

}


/**
  * @brief  write one frame to the TBUF using the can structure
  * @param  para: the pointer to the structure of the can
  */
void canfd_write_tbuf(__can_para_t *para)
{
    u32 control;
    u8 i;

    para->canfd_buf_p->TBUF[0] = para->id;
    if(para->ttcan_para.ttsen == 1) {
        para->canfd_buf_p->TBUF[0] |= ((u32)(para->ttcan_para.ttsen) << 31);
    }
    //printk("[CANFD]0x53 ~ 0x50 = 0x%x \n", para->canfd_buf_p->TBUF[0]);

    if(para->id & (CAN_EFF_MASK ^ CAN_SFF_MASK)) {
        para->control.IDE = IDE_1_EXTENDED_FORMAT;
    } else {
        para->control.IDE = IDE_0_STANDARD_FORMAT;
    }

    //para->control.DLC = para->control.DLC;
    if(para->control.DLC == 0) {
        para->control.RTR = RTR_1_REMOTE_FRAME;
    } else {
        para->control.RTR = RTR_0_DATA_FRAME;
    }

    if(para->can_type == CANFD_MASK) {
        para->control.FDF = FDF_1_CANFD_FRAME;
    } else {
        para->control.FDF = FDF_0_CAN2_0_FRAME;
    }

    if(para->fast_bitrate == para->slow_bitrate) {
        para->control.BRS = BRS_0_SLOW_BITRATE;
    } else {
        para->control.BRS = BRS_1_FAST_BITRATE;
        para->control.FDF = FDF_1_CANFD_FRAME;
    }

    control = (para->control.IDE << CANFD_RBUF_IDE_SHIFT) | \
              (para->control.RTR << CANFD_RBUF_RTR_SHIFT) | \
              (para->control.FDF << CANFD_RBUF_FDF_SHIFT) | \
              (para->control.BRS << CANFD_RBUF_BRS_SHIFT) | \
              (para->control.DLC << CANFD_RBUF_DLC_SHIFT);

    para->canfd_buf_p->TBUF[1] = control & 0x000000FF;

    //printk("[CANFD]0x54 = 0x%x \n", para->canfd_buf_p->TBUF[1] );

    para->dlc_length = canfd_get_dlc_length(para, para->control.DLC);



    para->dlc_length_word = para->dlc_length / 4;

    if(para->dlc_length % 4) {
        para->dlc_length_word ++;
    }

    //printk("[CANFD]dlc_length_word [%d]\n", para->dlc_length_word);
    for(i = 0; i < para->dlc_length_word; i ++) {
        para->canfd_buf_p->TBUF[2 + i] = para->data[i];
        //printk("[CANFD]para->canfd_buf_p->TBUF[2 + i] 0x%x\n", para->canfd_buf_p->TBUF[2 + i]);
        //printk("[CANFD]para->data[i] 0x%x\n", para->data[i]);
    }

#if 0
    for(i = 0; i < para->dlc_length_word; i++) {
        printk("[CANFD]tx data[%d] = ", i);
        printk("0x%x \n", para->canfd_buf_p->TBUF[2 + i]);
    }

    printk("[CANFD]dlc_length = %d bytes\n", para->dlc_length);
#endif
}

/**
  * @brief  ID filter configuration
  * @param  para: the pointer to the structure of the can
  * @param  filter_channel: filter channnel from 0 to 15
  * @param  acceptance_code: the 29 bits or 11 bits of target ID
  * @param  acceptance_mask: the 29 bits or 11 bits of ID mask
  *  when the bit is 0, it means the input ID bit should be the same as the target ID bit, it will be accept
  *  when the bit is 1, it means whether the input ID bit is 1 or 0, it will be accept
  * @param  id_type: CANFD_FILTER_STANDARD or CANFD_FILTER_EXTENDED or CANFD_FILTER_BOTH_FRAME
  */
static void canfd_filter_print(u32 acceptance_code, u32 acceptance_mask, u8 id_type)
{
    int i;

    printk("[CANFD]the final cover data format = B'");

    for(i= ( (id_type == CANFD_FILTER_STANDARD) ? 10 : 28); i>=0; i--) {
        if( 0 == (acceptance_mask & (1<<i)) ) {
            //temp |=  ( acceptance_code & (1<<i) );

            if(( acceptance_code & (1<<i) ) & (1<<i)) {
                printk("1");
            } else {
                printk("0");
            }
        } else {
            printk("x");
        }

        if( ( 0 == (i%4) ) && ( 0 != i ) ) {
            printk("_");
        }

        //debug_print("i = %d\n", i);
    }

    printk("(x means don't care) \n");
}

void canfd_filter_set(__can_para_t *para, u8 filter_channel, u32 acceptance_code, u32 acceptance_mask, u8 id_type)
{
    int i;
    //u32 temp = 0;
    filter_channel %= 16;  //limit to channel 0 ~ 15

    if(CANFD_NOT_RESET == canfd_get_reset_mode(para)) {
        printk("[CANFD-ERR]Not in reset mode, cannot set filter \n");
        while(1) {
            continue;
        };
    }

    //printk("[CANFD]acceptance_code = 0x%x \n", acceptance_code);
    //printk("[CANFD]acceptance_mask = 0x%x \n", acceptance_mask);

    /*select acode*/
    para->canfd_p->ACFCTRL &= ~CANFD_SELMASK;

    /*select channel*/
    para->canfd_p->ACFCTRL &= ~CANFD_ACFADR_MASK;
    para->canfd_p->ACFCTRL |= CANFD_ACFADR(filter_channel);
    //canfd_reg_bit_cfg(CANFD_ACFCTRL_TIMECFG_ACFEN_OFFSET, CANFD_ACFADR_MASK, CANFD_SET_BIT, CANFD_ACFADR(filter_channel));
    if(filter_channel >= 8) {
        para->canfd_p->ACFEN1 |= CANFD_ACCEPTANCE_FILTER_EN_MASK(filter_channel);
    } else {
        para->canfd_p->ACFEN0 |= CANFD_ACCEPTANCE_FILTER_EN_MASK(filter_channel);
    }
    //canfd_reg_bit_cfg(CANFD_ACFCTRL_TIMECFG_ACFEN_OFFSET, CANFD_ACCEPTANCE_FILTER_EN_MASK(filter_channel), CANFD_SET_BIT, CANFD_ACCEPTANCE_FILTER_EN_MASK(filter_channel) );
    //debug_print("[CAN]0xB4 0x%x \n", canfd_read_reg32(CANFD_ACFCTRL_TIMECFG_ACFEN_OFFSET));


    //printk("[CANFD]acceptance_code = 0x%x \n", acceptance_code);
    //printk("[CANFD]acceptance_mask = 0x%x \n", acceptance_mask);

    /*config*/
    para->canfd_buf_p->ACF = acceptance_code;

    //printk("[CANFD]code ACF = 0x%x \n", para->canfd_buf_p->ACF);

    //canfd_write_reg32(CANFD_ACF_OFFSET, acceptance_code);

    /*select amask*/
    para->canfd_p->ACFCTRL |= CANFD_SELMASK;
    //canfd_reg_bit_cfg(CANFD_ACFCTRL_TIMECFG_ACFEN_OFFSET, CANFD_SELMASK, CANFD_SET_BIT, CANFD_SELMASK);
    //canfd_write_reg32(CANFD_ACF_OFFSET, acceptance_mask);
    para->canfd_buf_p->ACF = acceptance_mask;

    //printk("[CANFD]mask ACF = 0x%x \n", para->canfd_buf_p->ACF);


    printk("\n[CANFD]channel %d filter setup:    ", para->canfd_p->ACFCTRL & CANFD_ACFADR_MASK);



    if(id_type == CANFD_FILTER_STANDARD) {
        para->canfd_buf_p->ACF |= CANFD_AIDEE_MASK;
        para->canfd_buf_p->ACF &= ~CANFD_AIDE_MASK;

        //canfd_reg_bit_cfg(CANFD_ACF_OFFSET, CANFD_AIDEE_MASK, CANFD_SET_BIT, CANFD_AIDEE_MASK);
        //canfd_reg_bit_cfg(CANFD_ACF_OFFSET, CANFD_AIDE_MASK, CANFD_CLR_BIT, CANFD_AIDE_MASK);
        acceptance_code &= CAN_SFF_MASK;
        acceptance_mask &= CAN_SFF_MASK;


        printk("filter only for standard frame \n");


    } else if (id_type == CANFD_FILTER_EXTENDED) {
        para->canfd_buf_p->ACF |= CANFD_AIDEE_MASK;
        para->canfd_buf_p->ACF |= CANFD_AIDE_MASK;

        //canfd_reg_bit_cfg(CANFD_ACF_OFFSET, CANFD_AIDEE_MASK, CANFD_SET_BIT, CANFD_AIDEE_MASK);
        //canfd_reg_bit_cfg(CANFD_ACF_OFFSET, CANFD_AIDE_MASK, CANFD_SET_BIT, CANFD_AIDE_MASK);
        acceptance_code &= CAN_EFF_MASK;
        acceptance_mask &= CAN_EFF_MASK;


        printk("filter only for extended frame \n");

    } else {
        para->canfd_buf_p->ACF &= ~CANFD_AIDEE_MASK;
        //canfd_reg_bit_cfg(CANFD_ACF_OFFSET, CANFD_AIDEE_MASK, CANFD_CLR_BIT, CANFD_AIDEE_MASK);
        acceptance_code &= CAN_EFF_MASK;
        acceptance_mask &= CAN_EFF_MASK;


        printk("filter for both frame \n");


    }

    para->canfd_p->ACFCTRL &= ~CANFD_SELMASK;

    //printk("[CANFD]ACODE = 0x%x \n", para->canfd_buf_p->ACF);

    para->canfd_p->ACFCTRL |= CANFD_SELMASK;

    //printk("[CANFD]AMASK = 0x%x \n", para->canfd_buf_p->ACF & ~(CANFD_AIDEE_MASK | CANFD_AIDE_MASK) );

    /*reset off*/
    //canfd_set_reset_mode(para, CANFD_NOT_RESET);

    canfd_filter_print(acceptance_code, acceptance_mask, id_type);

}

/**
  * @brief  receive buffer almost full warning limit configuration
  * @param  para: the pointer to the structure of the can
  * @param  fifo_limit_set: configure the receive buffer almost full warning limit, effective value from 1 ~ 7
  * @retval : return the actual limit configuration value
  */
u8 canfd_afwl_config(__can_para_t *para, u8 fifo_limit_set)
{
    u8 value;

    if(fifo_limit_set >= 8) {
        fifo_limit_set = 7;
    }

    /*clear afwl*/
    para->canfd_p->LIMIT &= ~(CANFD_SET_AFWL_MASK);
    //canfd_reg_bit_cfg(CANFD_RTIE_RTIF_ERRINT_LIMIT_OFFSET, CANFD_SET_AFWL_MASK, CANFD_CLR_BIT, CANFD_SET_AFWL_MASK);
    para->canfd_p->LIMIT |= CANFD_SET_AFWL_(fifo_limit_set);
    //canfd_reg_bit_cfg(CANFD_RTIE_RTIF_ERRINT_LIMIT_OFFSET, CANFD_SET_AFWL_MASK, CANFD_SET_BIT, CANFD_SET_AFWL_(fifo_limit_set) );

    return (para->canfd_p->LIMIT & CANFD_SET_AFWL_MASK) >> 4;
}


/**
  * @brief  clear the receive buffer until it is empty
  * @param  para: the pointer to the structure of the can
  * although the reset will clear all the receive buffer, it will also clear the other controller configuration
  * so use this method to clear the receive buffer only
  */
void canfd_clear_rbuf(__can_para_t *para)
{
    u8 i;

    while(canfd_get_rec_ctrl_status(para) != CANFD_RSTAT_EMP) {
        for(i=0; i<20; i++) {
            para->canfd_buf_p->RBUF[i];
            //canfd_read_reg32(CANFD_RUBF_OFFSET + i*4);
        }

        para->canfd_p->RCTRL |= CANFD_RREL_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET, CANFD_RREL_MASK, CANFD_SET_BIT, CANFD_RREL_MASK);
    }
}


/**
  * @brief  select the transmit buffer use PTB or STB
  * @param  para: the pointer to the structure of the can
  * @param  ptb_stb:
  *    This parameter can be one of the following values:
  *     @arg CANFD_SEL_PTB   : use PTB
  *     @arg CANFD_SEL_STB   : use STB
  */
void canfd_sel_ptb_stb(__can_para_t *para, u32 ptb_stb)
{
    if(CANFD_SEL_PTB == ptb_stb) {
        para->canfd_p->TCMD &= ~CANFD_SET_TBSEL_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET,  CANFD_SET_TBSEL_MASK, CANFD_CLR_BIT, CANFD_SET_TBSEL_MASK);
    } else {
        para->canfd_p->TCMD |= CANFD_SET_TBSEL_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET,  CANFD_SET_TBSEL_MASK, CANFD_SET_BIT, CANFD_SET_TBSEL_MASK);
    }
}

/**
  * @brief  select the BOSCH(non-ISO) or ISO frame mode
  * @param  para: the pointer to the structure of the can
  * @param  mode:
  *    This parameter can be one of the following values:
  *     @arg CANFD_BOSCH_MODE   : use BOSCH(non-ISO) frame
  *     @arg CANFD_ISO_MODE     : use ISO frame
  */
void canfd_iso_select(__can_para_t *para, u32 mode)
{
    if(CANFD_NOT_RESET == canfd_get_reset_mode(para)) {
        printk("[CAN-ERR] Not in reset mode, cannot switch ISO/BOSCH mode \n");
        while(1) {
        continue;
        }
    }

    if(CANFD_BOSCH_MODE == mode) {
        para->canfd_p->TCTRL &= ~CANFD_SET_ISO_CAN_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET, CANFD_SET_ISO_CAN_MASK, CANFD_CLR_BIT, 0);
    } else {
        para->canfd_p->TCTRL |= CANFD_SET_ISO_CAN_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET, CANFD_SET_ISO_CAN_MASK, CANFD_CLR_BIT, CANFD_SET_ISO_CAN_MASK);
    }

}


/**
  * @brief  select the FIFO mode or priority mode of STB
  * @param  para: the pointer to the structure of the can
  * @param  mode_sel:
  *    This parameter can be one of the following values:
  *     @arg CANFD_STB_FIFO_MODE        : the oldest frame send first
  *     @arg CANFD_STB_PRIORITY_MODE    : the highest priority frame send first
  */
void canfd_stb_tsmode(__can_para_t *para, u32 mode_sel)
{
    if(CANFD_STB_FIFO_MODE == mode_sel) {
        para->canfd_p->TCTRL &= ~CANFD_PRIORITY_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET,  CANFD_PRIORITY_MASK, CANFD_CLR_BIT, 0);
    } else {
        para->canfd_p->TCTRL |= CANFD_PRIORITY_MASK;
        //canfd_reg_bit_cfg(CANFD_CFG_STAT_TCMD_TCTRL_RCTRL_OFFSET,  CANFD_PRIORITY_MASK, CANFD_SET_BIT, CANFD_PRIORITY_MASK);
    }
}


/**
  * @brief  calculate the best seg and presc parameters
  * @param  para: the pointer to the structure of the can
  * @param  baudrate: set the needed baudrate unit in bps
  * @param  duty_cycle: 50 ~ 100 (%) = seg_1 / (seg_1 + seg_2)
  * @param  mode: CAN20  or CANFDSLOW or CANFDFAST
  */

static unsigned int cal_ntq(unsigned int clk_src, unsigned int presc, unsigned int baudrate)
{
    unsigned int temp1, temp2;
    unsigned int nTQ;
    nTQ = (clk_src / presc) / baudrate;
    if( ((clk_src / presc) % baudrate) && nTQ ) /*more precise to the target baudrate*/ {
        temp1 = (clk_src / presc) / nTQ;
        temp2 = (clk_src / presc) / (nTQ + 1);
        temp1 = abs(temp1 - baudrate);//(temp1 >= baudrate) ? (temp1 - baudrate) : (baudrate - temp1);
        temp2 = abs(temp2 - baudrate);//(temp2 >= baudrate) ? (temp2 - baudrate) : (baudrate - temp2);
        nTQ = temp1 > temp2 ? nTQ + 1 : nTQ;
    }
    return nTQ;
}
static unsigned int cal_seg_1(unsigned int nTQ, unsigned int duty_cycle)
{
    unsigned int temp1, temp2;
    unsigned int t_seg_1;
    t_seg_1 = nTQ * duty_cycle / 100;
    //more precise to the target duty_cycle
    if (nTQ * duty_cycle % 100) {
        temp1 = t_seg_1 * 10000 / nTQ;
        temp2 = (t_seg_1 + 1) * 10000 / nTQ;
        temp1 = abs(temp1- (duty_cycle * 100));//(temp1 >= (duty_cycle * 100)) ? (temp1 - (duty_cycle * 100)) : ((duty_cycle * 100) - temp1);
        temp2 = abs(temp2- (duty_cycle * 100));//(temp2 >= (duty_cycle * 100)) ? (temp2 - (duty_cycle * 100)) : ((duty_cycle * 100) - temp2);
        t_seg_1 = temp1 > temp2 ? t_seg_1 + 1 : t_seg_1;
    }
    return t_seg_1;
}

static u8 canfd_check_t_seg(u32 min, u32 max, u32 t_seg)
{
    if((t_seg>=min) && (t_seg<=max)) {
        return 1;
        } else {
        return 0;
            }
}


static u8 canfd_check_field(u32 t_seg_1, u32 t_seg_2, u32 nTQ, u32 clk_src, u32 presc, u32 baudrate, u32 mode)
{
    if(CAN20 == mode) {
        if (canfd_check_t_seg(2, 65, t_seg_1) && canfd_check_t_seg(1, 8, t_seg_2) && (t_seg_1>=t_seg_2+2) && (nTQ>=(clk_src/presc/baudrate))) {
            return 1;
            } else {
            return 0;
                }
        } else if(CANFDSLOW==mode) {
            if(canfd_check_t_seg(2, 65, t_seg_1) && canfd_check_t_seg(1, 16, t_seg_2) && (t_seg_1>=t_seg_2+2) && (nTQ>=(clk_src/presc/baudrate))) {
                return 1;
                } else {
                return 0;
                    }
            } else if(CANFDFAST==mode) {
                    if(canfd_check_t_seg(2, 17, t_seg_1) && canfd_check_t_seg(1, 8, t_seg_2) && (t_seg_1>=t_seg_2+1) && (nTQ=(clk_src/presc/baudrate))) {
                    return 1;
                    } else {
                    return 0;
                    }
                }

   return 0;
}

static void canfd_get_best_presc(__can_para_t *para, unsigned int baudrate, unsigned int duty_cycle, unsigned int mode)
{
    unsigned int presc = 0;
    unsigned int nTQ;
    unsigned int t_seg_1;
    unsigned int t_seg_2;
    unsigned int min_baud_diff = 0;  //minimun  baud rate error rate
    unsigned int min_duty_diff = 0;  //minimun  duty cycle error rate
    unsigned int cur_baud_diff = 0;  //current  baud rate error rate
    unsigned int cur_duty_diff = 0;  //current  duty cycle error rate
    unsigned int min_presc = 1;
    unsigned int first_flag = 0;
    unsigned int temp1, temp2;
    unsigned int clk_src;
    unsigned int presc_min = 1;

    clk_src = para->can_clk * 1000000;

/*
    if(para->can_clk >= 80) {
        presc_min = 2;
       }
*/

    for (presc = presc_min; presc <= 64; presc++) /* presc loop from 1 to 256 */ {
        nTQ = cal_ntq(clk_src, presc, baudrate);

        t_seg_1 = cal_seg_1(nTQ, duty_cycle);
        t_seg_2 = nTQ - t_seg_1;

        /*
        for- CAN 2.0   t_s_seg_1 : 2 ~ 65 TQ
                      t_s_seg_2 : 1 ~ 8 TQ    t_s_seg_1 >= t_s_seg_2 + 2
                      t_s_sjw : 1 ~ 16 TQ     t_s_seg_2 >= t_s_sjw

        for- CAN FD    t_s_seg_1 : 2 ~ 65 TQ
                      t_s_seg_2 : 1 ~ 32 TQ   t_s_seg_1 >= t_s_seg_2 + 2
                      t_s_sjw : 1 ~ 16 TQ      t_s_seg_2 >= t_s_sjw
                      t_f_seg_1 : 2 ~ 17 TQ
                      t_f_seg_2 : 1 ~ 8 TQ    t_f_seg_1 >= t_f_seg_2 + 1
                      t_f_sjw : 1 ~ 8 TQ      t_f_seg_2 >= t_f_sjw
        */
                                                                                                                   /* the current baudrate nTQ limit*/
/*
        if(((t_seg_1>=2)&&(t_seg_1<=65)&&(t_seg_2>=1) &&(t_seg_2<=8)&&(t_seg_1>=t_seg_2+2)&&(nTQ>=(clk_src/presc/baudrate))&&(CAN20==mode))||\
            ((t_seg_1>=2)&&(t_seg_1<=65)&&(t_seg_2>=1)&&(t_seg_2<=16)&&(t_seg_1>=t_seg_2+2)&&(nTQ>=(clk_src/presc/baudrate))&&(CANFDSLOW==mode))||\
            ((t_seg_1>=2)&&(t_seg_1<=17)&&(t_seg_2>=1)&&(t_seg_2<=8)&&(t_seg_1>=t_seg_2+1)&&(nTQ =(clk_src/presc/baudrate))&&(CANFDFAST==mode))) {
*/
        if(canfd_check_field(t_seg_1, t_seg_2, nTQ, clk_src, presc, baudrate, mode)) {
       //if (1) {
            cur_baud_diff = abs(((clk_src/presc)/nTQ)-baudrate);//(((clk_src / presc) / nTQ) >= baudrate) ? (((clk_src / presc) / nTQ) - baudrate) : (baudrate - ((clk_src / presc) / nTQ));
            cur_duty_diff = abs((t_seg_1*10000/nTQ)-(duty_cycle*100));//((t_seg_1 * 10000 / nTQ) >= (duty_cycle * 100)) ? ((t_seg_1 * 10000 / nTQ) - (duty_cycle * 100)) : ((duty_cycle * 100) - (t_seg_1 * 10000 / nTQ));

            //first time to record the min baud rate and duty cycle error rate
            if (first_flag == 0) {
                min_baud_diff = cur_baud_diff;
                min_duty_diff = cur_duty_diff;

                min_presc = presc;
                first_flag = 1;
                if( (CAN20 == mode) || (CANFDSLOW == mode) ) {
                    para->freq_div_parameters.t_s_seg_1 = t_seg_1;
                    para->freq_div_parameters.t_s_seg_2 = t_seg_2;
                    para->freq_div_parameters.t_s_sjw = para->freq_div_parameters.t_s_seg_2;
                    para->freq_div_parameters.s_presc = presc;
                    para->freq_div_parameters.slow_baud_err = min_baud_diff;
                    para->freq_div_parameters.slow_duty_err = min_duty_diff;
                } else {
                    para->freq_div_parameters.t_f_seg_1 = t_seg_1;
                    para->freq_div_parameters.t_f_seg_2 = t_seg_2;
                    para->freq_div_parameters.t_f_sjw = para->freq_div_parameters.t_f_seg_2;
                    para->freq_div_parameters.f_presc = presc;
                    para->freq_div_parameters.fast_baud_err = min_baud_diff;
                    para->freq_div_parameters.fast_duty_err = min_duty_diff;

                    para->freq_div_parameters.tdcen = 1;    //only enalbe for CAN bit switch
                    para->freq_div_parameters.sspoff = para->freq_div_parameters.t_f_seg_1;
                }
            } else {
                                                         //when baud rate error rate is equal, then compare the duty cycle error rate
                if( (cur_baud_diff < min_baud_diff) || ((cur_baud_diff == min_baud_diff) && (min_duty_diff > cur_duty_diff) ) ) {
                    min_baud_diff = cur_baud_diff;
                    min_duty_diff = cur_duty_diff;
                    min_presc = presc;

                    if ((CAN20 == mode) || (CANFDSLOW == mode)) {
                        para->freq_div_parameters.t_s_seg_1 = t_seg_1;
                        para->freq_div_parameters.t_s_seg_2 = t_seg_2;
                        para->freq_div_parameters.t_s_sjw = para->freq_div_parameters.t_s_seg_2;
                        para->freq_div_parameters.s_presc = presc;
                        para->freq_div_parameters.slow_baud_err = min_baud_diff;
                        para->freq_div_parameters.slow_duty_err = min_duty_diff;
                    } else {
                        para->freq_div_parameters.t_f_seg_1 = t_seg_1;
                        para->freq_div_parameters.t_f_seg_2 = t_seg_2;
                        para->freq_div_parameters.t_f_sjw = para->freq_div_parameters.t_f_seg_2;
                        para->freq_div_parameters.f_presc = presc;
                        para->freq_div_parameters.fast_baud_err = min_baud_diff;
                        para->freq_div_parameters.fast_duty_err = min_duty_diff;

                        para->freq_div_parameters.tdcen = 1;
                        para->freq_div_parameters.sspoff = para->freq_div_parameters.t_f_seg_1;
                    }
                }
            }
/*
            if (CAN20 == mode) {
                printk("[CAN 2.0 list]: [PRESC]: %d, [SEG1]: %d, [SEG2]: %d [slow_baud_err]: %d, [slow_duty_err]: %d\n", presc,  t_seg_1, t_seg_2, cur_baud_diff, cur_duty_diff);
            } else if (CANFDSLOW == mode) {
                printk("[CANFD slow list]: [PRESC]: %d, [SEG1]: %d, [SEG2]: %d [slow_baud_err]: %d, [slow_duty_err]: %d\n", presc, t_seg_1, t_seg_2, cur_baud_diff, cur_duty_diff);
            } else {
                printk("[CANFD fast list]: [PRESC]: %d, [SEG1]: %d, [SEG2]: %d [fast_baud_err]: %d, [fast_duty_err]: %d\n", presc, t_seg_1, t_seg_2, cur_baud_diff, cur_duty_diff);
            }
*/
        }

    }

    printk("canfd_para_t.t_s_seg_1: %d, canfd_para_t.t_s_seg_2: %d\n", para->freq_div_parameters.t_s_seg_1, para->freq_div_parameters.t_s_seg_2);
    printk("[CANFD]=====>  The best presc: %d\n", min_presc);

}


/**
  * @brief  config the best seg and presc parameters
  * @param  para: the pointer to the structure of the can
  */
static void canfd_check_duty_cycle(__can_para_t *para)
{

    if(para->can_type == CAN_MASK) {
        if ( (para->freq_div_parameters.slow_duty_cycle >= 100) || (para->freq_div_parameters.slow_duty_cycle <= 50) ) {
            printk("[CANFD-ERROR]duty_cycle should be config from (50 ~ 100) \n");
            while (1) {
            continue;
            }
        }
    } else {
        if ( (para->freq_div_parameters.slow_duty_cycle >= 100) || (para->freq_div_parameters.slow_duty_cycle <= 50) || (para->freq_div_parameters.fast_duty_cycle >= 100) || (para->freq_div_parameters.fast_duty_cycle <= 50) ) {
            printk("[CANFD-ERROR]duty_cycle should be config from (50 ~ 100) \n");
            while (1) {
            continue;
            }
        }
    }
}

u8 canfd_parameters_cal(__can_para_t *para)
{
    //unsigned char duty_cycle; // xx%
    para->freq_div_parameters.t_s_seg_1 = 0;  // 0 <= (t_s_seg_1 - 2 = S_Seg_1) <= 255
    para->freq_div_parameters.t_s_seg_2 = 0;  // 0 <= (t_s_seg_2 - 1 = S_Seg_2) <= 127
    para->freq_div_parameters.t_s_sjw = 0;  // 0 <= (t_s_sjw - 1 = S_SJW) <= 127
    para->freq_div_parameters.s_presc = 0;   // 0 <= (s_presc - 1 = S_PRESC) <= 255

    para->freq_div_parameters.t_f_seg_1 = 5;  // 0 <= (t_f_seg_1 - 2 = F_Seg_1) <= 31
    para->freq_div_parameters.t_f_seg_2 = 3;  // 0 <= (t_f_seg_2 - 1 = F_Seg_2) <= 15
    para->freq_div_parameters.t_f_sjw = 3;  // 0 <= (t_f_sjw - 1 = F_SJW) <= 15
    para->freq_div_parameters.f_presc = 2;   // 0 <= (f_presc - 1 = F_PRESC) <= 255

    para->freq_div_parameters.tdcen = 0;  //if BRS = 1
    para->freq_div_parameters.sspoff = 0;

    //printk("[CANFD]parameters calculate start=======\n");
    if ((para->slow_bitrate > 1000000) || (para->fast_bitrate > 10000000) || (para->fast_bitrate < para->slow_bitrate)) {
        printk("[CANFD-ERROR]baud rate error!\n");
        while (1) {
            continue;
            }
    }

        if (para->fast_bitrate != para->slow_bitrate) {
            //printk("[CANFD]FD mode: baudrate %d bps -> %d bps\n", para->slow_bitrate, para->fast_bitrate);
        } else {
            //printk("[CANFD]2.0 mode: baudrate = %d bps\n", para->slow_bitrate);
        }

    //duty cycle should be bigger then 50 (%) and less then 100 (%), default 80 (%)
    canfd_check_duty_cycle(para);

    if (para->slow_bitrate == para->fast_bitrate) {
        canfd_get_best_presc(para, para->slow_bitrate, para->freq_div_parameters.slow_duty_cycle, CAN20);

        printk("[CANFD]2.0 mode: %d bps [Best PRESC]: %d, [SEG1]: %d, [SEG2]: %d\n", para->slow_bitrate, para->freq_div_parameters.s_presc, para->freq_div_parameters.t_s_seg_1, para->freq_div_parameters.t_s_seg_2);

    } else {
        canfd_get_best_presc(para, para->slow_bitrate, para->freq_div_parameters.slow_duty_cycle, CANFDSLOW);


        printk("[CANFD]FD mode: slow %d bps [Best PRESC]: %d, [SEG1]: %d, [SEG2]: %d\n", para->slow_bitrate, para->freq_div_parameters.s_presc, para->freq_div_parameters.t_s_seg_1, para->freq_div_parameters.t_s_seg_2);

        canfd_get_best_presc(para, para->fast_bitrate, para->freq_div_parameters.fast_duty_cycle, CANFDFAST);
/*
        if(para->fast_bitrate == 1538000) {
            para->freq_div_parameters.f_presc = 2;
            para->freq_div_parameters.t_f_seg_1 = 20;
            para->freq_div_parameters.t_f_seg_2 = 6;
            para->freq_div_parameters.t_f_sjw = 6;
            }
 */
        printk("[CANFD]FD mode: fast %d bps [Best PRESC]: %d, [SEG1]: %d, [SEG2]: %d\n", para->fast_bitrate, para->freq_div_parameters.f_presc, para->freq_div_parameters.t_f_seg_1, para->freq_div_parameters.t_f_seg_2);

    }

    if(CANFD_NOT_RESET == canfd_get_reset_mode(para)) {
        printk("[CANFD-ERROR] Not in reset mode, cannot set bit timing \n");
        while(1) {
            continue;
            }
    }

    para->canfd_p->SSEG1 = para->freq_div_parameters.t_s_seg_1 - 2;
    para->canfd_p->SSEG2 = para->freq_div_parameters.t_s_seg_2 - 1;
    para->canfd_p->SSJW  = para->freq_div_parameters.t_s_sjw - 1;
    para->canfd_p->SPRESC = para->freq_div_parameters.s_presc - 1;

    para->canfd_p->FSEG1 = para->freq_div_parameters.t_f_seg_1 - 2;
    para->canfd_p->FSEG2 = para->freq_div_parameters.t_f_seg_2 - 1;
    para->canfd_p->FSJW  = para->freq_div_parameters.t_f_sjw - 1;
    para->canfd_p->FPRESC = para->freq_div_parameters.f_presc - 1;

    //SSP offset config
    if(para->freq_div_parameters.tdcen) {
        para->canfd_p->TDC = CANFD_SET_TDCEN_MASK | (CANFD_SET_SSPOFF_MASK & para->freq_div_parameters.sspoff);
        printk("[CANFD]0xB1 TDC = 0x%X\n", para->canfd_p->TDC);
    }
/*
    printk("[CANFD]0xAB S_PRESC[7:0] = 0x%X\n", para->freq_div_parameters.s_presc - 1);
    printk("[CANFD]0xA8 S_Seg_1[7:0] = 0x%X\n", para->freq_div_parameters.t_s_seg_1 - 2);
    printk("[CANFD]0xA9 S_Seg_2[6:0] = 0x%X\n", para->freq_div_parameters.t_s_seg_2 - 1);
    printk("[CANFD]0xAA S_SJW[6:0] = 0x%X\n\n", para->freq_div_parameters.t_s_sjw - 1);

    printk("[CANFD]0xAF F_PRESC[7:0] = 0x%X\n", para->freq_div_parameters.f_presc - 1);
    printk("[CANFD]0xAC F_Seg_1[4:0] = 0x%X\n", para->freq_div_parameters.t_f_seg_1 - 2);
    printk("[CANFD]0xAD F_Seg_2[3:0] = 0x%X\n", para->freq_div_parameters.t_f_seg_2 - 1);
    printk("[CANFD]0xAE F_SJW[3:0] = 0x%X\n", para->freq_div_parameters.t_f_sjw - 1);



    printk("[CANFD]0xAB S_PRESC[7:0] = 0x%X\n", para->canfd_p->SPRESC);
    printk("[CANFD]0xA8 S_Seg_1[7:0] = 0x%X\n", para->canfd_p->SSEG1);
    printk("[CANFD]0xA9 S_Seg_2[6:0] = 0x%X\n", para->canfd_p->SSEG2);
    printk("[CANFD]0xAA S_SJW[6:0] = 0x%X\n\n", para->canfd_p->SSJW);

    printk("[CANFD]0xAF F_PRESC[7:0] = 0x%X\n", para->canfd_p->FPRESC);
    printk("[CANFD]0xAC F_Seg_1[4:0] = 0x%X\n", para->canfd_p->FSEG1);
    printk("[CANFD]0xAD F_Seg_2[3:0] = 0x%X\n", para->canfd_p->FSEG2);
    printk("[CANFD]0xAE F_SJW[3:0] = 0x%X\n", para->canfd_p->FSJW);
*/

#if defined ENV_SIM
#else
    printk("[CANFD]parameters calculate finish=======\n");
#endif
    return 0;
}

s32 init_canfd_gpio(u32 canfd_num)
{
        if(canfd_num == CANFD_0) {
                        gpio_enable(GPIO_GRP_G,  15, 2,  GPIO_FUN_2);
                        gpio_pin_cfg(GPIO_GRP_G, 15, 2,  GPIO_DRV_180R, GPIO_PULL_NONE);
        } else {
                        gpio_enable(GPIO_GRP_D,  3, 2,  GPIO_FUN_2);
                        gpio_pin_cfg(GPIO_GRP_D, 3, 2,  GPIO_DRV_180R, GPIO_PULL_NONE);
        }
        return RET_OK;
}

s32 init_canfd_mod_clk(u32 canfd_num, u32 mod_fre)
{
        u32 i;

        cmu_mod_disable(CMU_MOD_CANFD0+canfd_num);
        cmu_mod_set_freq(CMU_MOD_CANFD0 + canfd_num, mod_fre);
        for(i=0; i<0x10; i++) { };
        cmu_mod_enable(CMU_MOD_CANFD0+canfd_num);
        return RET_OK;
}



s32 init_canfd(u32 canfd_num, u32 mod_fre)
{
        u32 i;

        init_canfd_mod_clk(canfd_num, mod_fre);
        init_canfd_gpio(canfd_num);


        for(int i = 0; i<=CANFD_LAST; i++) {
                can_para[i].canfd_p         = (struct canfd_regs*)(BASE_CANFD0 + 0x1000 * i);
                can_para[i].canfd_buf_p     = (struct canfd_buf *)(BASE_CANFD0 + 0x1000 * i);
                can_para[i].can_clk = cmu_mod_get_freq(CMU_MOD_CANFD0 + i) / (1000 * 1000);
        }


        return RET_OK;
}













