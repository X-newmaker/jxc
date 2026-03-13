/*
 *  i2c.c
 *  Copyright (c) 2024, Artinchip Technology Co., Ltd
 *  
 *  
 */

#include "all_inc.h"

volatile struct I2C_REGS I2c0Regs __attribute__((__section__(".i2c0reg")));
volatile struct I2C_REGS I2c1Regs __attribute__((__section__(".i2c1reg")));
volatile struct I2C_REGS I2c2Regs __attribute__((__section__(".i2c2reg")));
volatile struct I2C_REGS I2c3Regs __attribute__((__section__(".i2c3reg")));

volatile struct I2C_REGS *I2C[] = {&I2c0Regs, &I2c1Regs, &I2c2Regs,&I2c3Regs};

static void i2c0_null(void){};
static void i2c1_null(void){};
static void i2c2_null(void){};
static void i2c3_null(void){};
cpu_irq_fun_t i2c0_irqhandle = i2c0_null;
cpu_irq_fun_t i2c1_irqhandle = i2c1_null;
cpu_irq_fun_t i2c2_irqhandle = i2c2_null;
cpu_irq_fun_t i2c3_irqhandle = i2c3_null;

ATTRIBUTE_ISR void I2C0_IRQHandler(void)
{
        i2c0_irq_handler();
}

void i2c0_irq_handler(void)
{
        i2c0_irqhandle();
}

ATTRIBUTE_ISR void I2C1_IRQHandler(void)
{
        i2c1_irq_handler();
}

void i2c1_irq_handler(void)
{
        i2c1_irqhandle();
}

ATTRIBUTE_ISR void I2C2_IRQHandler(void)
{
        i2c2_irq_handler();
}

void i2c2_irq_handler(void)
{
        i2c2_irqhandle();
}

ATTRIBUTE_ISR void I2C3_IRQHandler(void)
{
        i2c3_irq_handler();
}

void i2c3_irq_handler(void)
{
        i2c3_irqhandle();
}

void i2c_irq_register(u8 num, cpu_irq_fun_t irqhandle)
{
        switch(num) {
                case 0:
                        i2c0_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_I2C0);
                        break;
                case 1:
                        i2c1_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_I2C1);
                        break;
                case 2:
                        i2c2_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_I2C2);
                        break;
                case 3:
                        i2c3_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_I2C3);
                        break;
		default:
                        break;               
        }
}

void i2c_irq_unregister(u8 num)
{
        switch(num) {
                case 0:
                        i2c0_irqhandle = i2c0_null;
                        cpu_irq_disable(CPU_IRQ_I2C0);
                        break;
                case 1:
                        i2c1_irqhandle = i2c1_null;
                        cpu_irq_disable(CPU_IRQ_I2C1);
                        break;
                case 2:
                        i2c2_irqhandle = i2c2_null;
                        cpu_irq_disable(CPU_IRQ_I2C2);
                        break;
                case 3:
                        i2c3_irqhandle = i2c3_null;
                        cpu_irq_disable(CPU_IRQ_I2C3);
                        break;
                default:
                        break;               
        }
}

s32 init_i2c(u32 i2c_num)
{
	u32 i;
	cmu_mod_disable(CMU_MOD_I2C0+i2c_num);
	for(i=0; i<0x10; i++) { };
	cmu_mod_enable(CMU_MOD_I2C0+i2c_num);

	/*set clk*/
	i2c_set_clk(i2c_num,FAST_MODE);
	i2c_set_speed_mode(i2c_num,FAST_MODE);
	sda_hold(i2c_num,5);

	//i2c cfg
	i2c_set_7bit_or_10bit_address(i2c_num,ADDRESS_7BIT,ADDRESS_7BIT);
	i2c_set_address_mode(i2c_num,i2c_tx_target);//set address_MODE
	restart_en(i2c_num,1);
	master_enable(i2c_num,1);
	slave_disable(i2c_num,1);

	(*I2C[i2c_num]).I2C_INTR_MASK.all = 0x0;
	(*I2C[i2c_num]).I2C_SCL_STUCK_TIMEOUT = 0x0000FFF;
        (*I2C[i2c_num]).I2C_SDA_STUCK_TIMEOUT = 0x0000FFF;
	(*I2C[i2c_num]).I2C_CTL.bit.BUS_CLR_FEATURE_CTL = 0x1;

	//i2c enable
	i2c_enable(i2c_num,1);

	return RET_OK;
}

void i2c_set_clk(u32 i2c_num,speed_mode_t clk)
{
	u16 fs_scl_high, fs_scl_low;
	u16 ss_scl_high, ss_scl_low;
	u32 period = cmu_mod_get_freq(CMU_MOD_I2C0+i2c_num) / CLK_M;

	if(clk == STANDARD_MODE) {
		//100k 5+5=10us 
		ss_scl_high = ((u16) (((5000 * period) / CLK_N) - 8 - (*I2C[i2c_num]).I2C_FS_SPIKELEN));
    		ss_scl_low = ((u16) (((5000 * period) / CLK_N) - 1));

		(*I2C[i2c_num]).I2C_SS_SCL_HCNT.bit.I2C_SS_SCL_HCNT = ss_scl_high;
		(*I2C[i2c_num]).I2C_SS_SCL_LCNT.bit.I2C_SS_SCL_LCNT = ss_scl_low;  

	} else {
		//400k 1.167+1.333=2.5us 
		fs_scl_high = ((u16) (((1167 * period) / CLK_N) - 8 - (*I2C[i2c_num]).I2C_FS_SPIKELEN));
    		fs_scl_low = ((u16) (((1333 * period) / CLK_N) - 1));

		(*I2C[i2c_num]).I2C_FS_SCL_HCNT.bit.I2C_FS_SCL_HCNT = fs_scl_high;
		(*I2C[i2c_num]).I2C_FS_SCL_LCNT.bit.I2C_FS_SCL_LCNT = fs_scl_low;  

	}
}

void i2c_set_speed_mode(u32 i2c_num,speed_mode_t mode)
{
	(*I2C[i2c_num]).I2C_CTL.bit.SPEED_MODE_SEL = mode; 
}

void i2c_set_7bit_or_10bit_address(u32 i2c_num,address_t master_address,address_t slave_address)
{
	(*I2C[i2c_num]).I2C_CTL.bit.ADDR10BIT_SEL_MASTER = master_address; 
	(*I2C[i2c_num]).I2C_CTL.bit.ADDR10BIT_SEL_SLAVE = slave_address;
}

void sda_hold(u32 i2c_num,u32 sda)
{
	(*I2C[i2c_num]).I2C_SDA_HOLD.bit.I2C_SDA_TX_HOLD = sda; 
}

void restart_en(u32 i2c_num,u32 restart)
{
	(*I2C[i2c_num]).I2C_CTL.bit.RESTART_EN = restart;
}

void master_enable(u32 i2c_num,u32 en)
{
	(*I2C[i2c_num]).I2C_CTL.bit.MASTER_MODE_EN = en;
}

void slave_disable(u32 i2c_num,u32 dis)
{
	(*I2C[i2c_num]).I2C_CTL.bit.SLAVE_MODE_DIS = dis;
}

void i2c_enable(u32 i2c_num,u32 en)
{
	(*I2C[i2c_num]).I2C_ENABLE.bit.ENABLE = en;
}

void i2c_set_address_mode(u32 i2c_num,tx_mode_t mode)
{
	(*I2C[i2c_num]).I2C_TAR.bit.SB_GC_CTL = mode;
}

void i2c_target_address(u32 i2c_num,u32 address)
{
	(*I2C[i2c_num]).I2C_TAR.bit.I2C_TAR = address;
}

void i2c_slave_address(u32 i2c_num,u32 address)
{
	(*I2C[i2c_num]).I2C_SAR.bit.I2C_SAR = address;
}

void i2c_send_char(u32 i2c_num,u32 data)
{
	while( (*I2C[i2c_num]).I2C_STATUS.bit.TFNF == 0x0 ) { };
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = (data & 0xFF);
}

void i2c_write_byte(u32 i2c_num,u32 SLAVE_ADDRESS,u8 reg_address,u8 data)
{
	i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address

	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((reg_address & 0xFF) | MASTER_WRITE | NO_STOP_CMD);
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((data & 0xFF) | MASTER_WRITE | STOP_CMD);
	while((*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET == 0x0) { };
	(*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET = 0x1;
		
}

void i2c_write_byte_16add(u32 i2c_num,u32 SLAVE_ADDRESS,u8 reg_high_address,u8 reg_low_address,u8 data)
{
	i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address

	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((reg_high_address & 0xFF) | MASTER_WRITE | NO_STOP_CMD);
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((reg_low_address & 0xFF) | MASTER_WRITE | NO_STOP_CMD);	
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((data & 0xFF) | MASTER_WRITE | STOP_CMD);
	while((*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET == 0x0) { };
	(*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET = 0x1;
}

char i2c_read_byte(u32 i2c_num,u32 SLAVE_ADDRESS,u8 reg_address)
{
	u32 read_val = 0;
	i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address

	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((reg_address & 0xFF) | MASTER_WRITE | NO_STOP_CMD);
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ((reg_address & 0xFF) | MASTER_READ | STOP_CMD);
	while((*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET == 0x0) { };
	(*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET = 0x1;

	read_val = (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS;
	read_val = (read_val & 0xFF);
	return (char)read_val;//return data
}


static inline void hal_i2c_module_disable(u8 i2c_num)
{
	(*I2C[i2c_num]).I2C_ENABLE.bit.ENABLE = 0;
}

static inline void hal_i2c_module_enable(u8 i2c_num)
{
	(*I2C[i2c_num]).I2C_ENABLE.bit.ENABLE = 1;
}

void hal_i2c_target_addr(u8 i2c_num, u16 addr)
{
	(*I2C[i2c_num]).I2C_TAR.bit.I2C_TAR = addr;
}


static inline void hal_i2c_transmit_data_with_stop_bit(u8 i2c_num, u8 data)
{
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = (data & 0xFF) | MASTER_WRITE | STOP_CMD;
}

static inline void hal_i2c_transmit_data(u8 i2c_num, uint8_t data)
{
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = (data & 0xFF) | MASTER_WRITE | NO_STOP_CMD;
}

static inline void hal_i2c_set_restart_bit_with_data(u8 i2c_num, u8 data)
{
	(*I2C[i2c_num]).I2C_CTL.bit.RESTART_EN = 1;
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = (data & 0xFF) | MASTER_WRITE | NO_STOP_CMD | RESTART_CMD;

}

static inline u32 hal_i2c_get_transmit_fifo_num(u8 i2c_num)
{
	return (*I2C[i2c_num]).I2C_TXFLR.all;
}

static inline u32 hal_i2c_get_receive_fifo_num(u8 i2c_num)
{
	return (*I2C[i2c_num]).I2C_RXFLR.all;
}

static inline void hal_i2c_read_data_cmd_with_stop_bit(u8 i2c_num)
{
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = MASTER_READ | STOP_CMD;
}

static inline void hal_i2c_read_data_cmd(u8 i2c_num)
{
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = MASTER_READ | NO_STOP_CMD;
}

static inline u8 hal_i2c_get_receive_data(u8 i2c_num)
{
	return ((*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS & 0xff);
}

static int32_t hal_i2c_wait_transmit(u8 i2c_num, uint32_t timeout)
{
	int32_t ret = I2C_OK;
	do {
		uint64_t timecount = timeout + gtc_get_time(GTC_MS);
		while ((hal_i2c_get_transmit_fifo_num(i2c_num) != 0U) && (ret == I2C_OK)) {
			if (gtc_get_time(GTC_MS) >= timecount) {
				ret = I2C_TIMEOUT;
			}
		}
	} while (0);
	return ret;
}

static int32_t hal_i2c_wait_receive(u8 i2c_num, u32 wait_data_num, uint32_t timeout)
{
	int32_t ret = I2C_OK;
	do {
		uint64_t timecount = timeout + gtc_get_time(GTC_MS);
		while ((hal_i2c_get_receive_fifo_num(i2c_num) != wait_data_num) && (ret == I2C_OK)) {
			if (gtc_get_time(GTC_MS) >= timecount) {
				ret = I2C_TIMEOUT;
			}
		}
	} while (0);
	return ret;
}

/*i2c 发送接口*/
u32 i2c_master_send_msg(u8 i2c_num, struct aic_i2c_msg *msg)
{
	u32 ret = I2C_OK;
	u16 size = msg->len;
	uint32_t send_count = 0;
	uint16_t idx = 0;
	uint32_t timeout = 10;

	hal_i2c_module_disable(i2c_num);
	hal_i2c_target_addr(i2c_num, msg->addr);
	hal_i2c_module_enable(i2c_num);

	while(size > 0) {
		uint16_t send_num = size > I2C_FIFO_DEPTH ? I2C_FIFO_DEPTH : size;
		for(u16 i =0; i<send_num; i++) {
			if (idx == msg->len -1) {
				hal_i2c_transmit_data_with_stop_bit(i2c_num, msg->buf[idx]);
			} else if (idx == 0) {
				hal_i2c_set_restart_bit_with_data(i2c_num, msg->buf[idx]);
			} else {
				hal_i2c_transmit_data(i2c_num, msg->buf[idx]);
			}
			idx++;
		}
		size -= send_num;
		send_count += send_num;

		ret = hal_i2c_wait_transmit(i2c_num, timeout);
		if (ret != I2C_OK) {
			send_count = ret;
			return I2C_TIMEOUT;
		}
	}
	return send_count;
}

/*i2c 接收接口*/
u32 i2c_master_receive_msg(u8 i2c_num, struct aic_i2c_msg *msg)
{
	u32 ret = I2C_OK;
	u16 size = msg->len;
	u32 read_count = 0;
	u8 *receive_data = msg->buf;
	u32 timeout = 10;
	u32 idx = 0, count = 0;

	hal_i2c_module_disable(i2c_num);
	hal_i2c_target_addr(i2c_num, msg->addr);
	hal_i2c_module_enable(i2c_num);

	while (size > 0) {
		int32_t recv_num = size > I2C_FIFO_DEPTH ? I2C_FIFO_DEPTH : size;
		for (u16 len = 0; len < recv_num; len++) {
			if (count == msg->len - 1) {
				hal_i2c_read_data_cmd_with_stop_bit(i2c_num);
			} else {
				hal_i2c_read_data_cmd(i2c_num);
			}
			count++;
		}

		size -= recv_num;
		read_count += recv_num;
		ret = hal_i2c_wait_receive(i2c_num, recv_num, timeout);
		if (ret == I2C_OK) {
			for (u16 i = 0; i < recv_num; i++) {
				receive_data[idx] = hal_i2c_get_receive_data(i2c_num);
				idx++;
			}
		} else {
			read_count = (u32)ret;
			break;
		}
	}
	return read_count;
}

void hal_i2c_rxdma_en(u8 i2c_num, u32 en)
{
	(*I2C[i2c_num]).I2C_DMA_CR.bit.RDMAE = en & 0x1;
}

void hal_i2c_txdma_en(u8 i2c_num, u32 en)
{
	(*I2C[i2c_num]).I2C_DMA_CR.bit.TDMAE = en & 0x1;
}

void hal_i2c_txdma_thset(u8 i2c_num, u32 set)
{
	(*I2C[i2c_num]).I2C_DMA_TDLR.bit.DMATDL = set & 0x7;
}

void hal_i2c_rxdma_thset(u8 i2c_num, u32 set)
{
	(*I2C[i2c_num]).I2C_DMA_RDLR.bit.DMARDL = set & 0x7;
}

