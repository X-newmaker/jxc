#include "all_inc.h"
#include "Const_Def.h"

#ifdef EEPROM_SPI
u32 eeprom_dev_num = 4;//SPI4
#else
u32 eeprom_dev_num = 1;//I2C0
#endif
#ifdef EEPROM_SPI

extern volatile struct SPI_REGS *SPI[];
static u8 WREN = 0x06;
static u8 WRDI = 0x04;
static u8 RSDR = 0x05;
static u8 WRSR = 0x01;
static u8 READ = 0x03;
static u8 WRITE = 0x02;
static u8 READH = 0x0B;
static u8 WRITEH = 0x0A;

void spi_init_e2prom(void)
{
	//管脚复用选择SPI4
	gpio_enable(GPIO_GRP_E, 14, 4, GPIO_FUN_3);
	//初始化CMU
	spi_cmu_init(eeprom_dev_num);
	spi_type2_clk_div(eeprom_dev_num, 4);	//clk 200M/(2*(4+1)) = 10MHz
	spi_txfifo_rst(eeprom_dev_num);
	spi_rxfifo_rst(eeprom_dev_num);
	spi_txfifo_level_set(eeprom_dev_num, 32);
	spi_rxfifo_level_set(eeprom_dev_num, 32);
	spi_rxdelay_sample(eeprom_dev_num);     //<=24Mhz都要配置

	spi_soft_rst(eeprom_dev_num);
	spi_master_en(eeprom_dev_num);
	spi_en(eeprom_dev_num);

	//mode0
	spi_clk_idle_low(eeprom_dev_num);      //bit1 = 0 CLK_POL
	spi_ph0_sample(eeprom_dev_num);         //bit0 = 0 CPHA

	spi_cs_owner_hw(eeprom_dev_num);        //硬件控制spi_cs
	/*
	 * 半双工模式下，要设置为1，全双工要设置为0
	 */
	spi_dhb_dis(eeprom_dev_num);            //bit8 = 0 DHB,接收所有数据无效


}

void SPITX_byte(u32 index,u8 data)
{
	spi_txfifo_rst(index);
	spi_int_sts_clr(index);
	spi_txdata_write(index, data);   //发送数据写入FIFO

	//每次发送前都需要重新设置计数器
	spi_mbc_set(index, 1);
	spi_mtc_set(index, 1);
	spi_stc_set(index, 1);

	spi_xch(index);
	do {
	}while((spi_get_int_sts(index)&(SPI_TC_INT)) != SPI_TC_INT);
	spi_tc_sts_clr(index);
}
u8 SPIRX_byte(u32 index,u8 data)
{
	u32 rdata;
	u8 timeout = 0, receive = 0;

	spi_rxfifo_rst(index);
	SPITX_byte(index,0x00);              //发送一个数据

	while(receive != 1)
	{
		receive = spi_get_rx_fifo_cnt(index);
		gtc_dly_time(GTC_US, 1);
		timeout++;
		if (timeout > 200) {
			return 0;
		}
	}

	rdata = spi_get_rx_dat(index);
	return(rdata);
}

void SPITX_word(u32 index,u32 data)
{
	spi_txfifo_rst(index);
	spi_int_sts_clr(index);
	spi_txdata_write(index, data);       //发送数据写入FIFO

	//每次发送前都需要重新设置计数器
	spi_mbc_set(index, 2);
	spi_mtc_set(index, 2);
	spi_stc_set(index, 2);

	spi_xch(index);
	do {
	}while((spi_get_int_sts(index)&(SPI_TC_INT)) != SPI_TC_INT);
	spi_tc_sts_clr(index);
}
u32 SPIRX_word(u32 index,u32 data)
{
	u32 rdata;
	u32 tdata;
	u8 timeout = 0, receive = 0;

	tdata = data;
	spi_rxfifo_rst(index);
	SPITX_word(index,tdata);            //发送数据，用于产生16位的时钟

	while(receive != 2)
	{
		receive = spi_get_rx_fifo_cnt(index);
		gtc_dly_time(GTC_US, 1);
		timeout++;
		if (timeout > 200) {
			return 0;
		}
	}

	rdata = spi_get_rx_dat(index);
	return(rdata);
}
void SPITX_dword(u32 index,u32 data)
{
	spi_txfifo_rst(index);
	spi_int_sts_clr(index);
	spi_txdata_write(index, data);       //发送数据写入FIFO

	//每次发送前都需要重新设置计数器
	spi_mbc_set(index, 4);
	spi_mtc_set(index, 4);
	spi_stc_set(index, 4);

	spi_xch(index);
	do {
	}while((spi_get_int_sts(index)&(SPI_TC_INT)) != SPI_TC_INT);
	spi_tc_sts_clr(index);
}
u32 SPIRX_dword(u32 index,u32 data)
{
	u32 rdata;
	u32 tdata;
	u8 timeout = 0, receive = 0;

	tdata = data;
	spi_rxfifo_rst(index);
	SPITX_dword(index,tdata);//虚发送一个数据，用于产生8位的时钟

	while(receive != 4)
	{
		receive = spi_get_rx_fifo_cnt(index);
		gtc_dly_time(GTC_US, 1);
		timeout++;
		if (timeout > 200) {
			return 0;
		}
	}

	rdata = spi_get_rx_dat(index);
	return(rdata);
}
/*
 * E2PROM写使能
 */
void spi_wren_e2prom(u32 index)
{
	SPITX_byte(index,WREN);
}
/*
 * E2PROM写禁止
 */
void spid_wrdi_e2prom(u32 index)
{
	SPITX_byte(index,WRDI);
}
/*
 * E2PROM读状态查询
 */
u8 spi_rsdr_e2prom(u32 index)
{
	u32 rdata;
	spi_dhb_dis(index);            //bit8 = 0 DHB
	rdata = (SPIRX_word(index,RSDR) >> 8) & 0xff;
	return(rdata);
}
/*
 * E2PROM写状态查询
 */
u8 spi_wrsr_e2prom(u32 index)
{
	u32 rdata;
	spi_dhb_dis(index);            //bit8 = 0 DHB
	rdata = SPIRX_word(index,WRSR) >> 8;
	return(rdata);
}
/*
 * 写一个字操作
 */
void spi_write_e2prom(u32 index,u16 waddr,u16 wdata)
{
	u16 waddr_reg;
	u32 SendData;

	spi_dhb_en(index);            //bit8 = 1 DHB 丢弃所有无效数据
	waddr_reg = waddr;
	waddr_reg = waddr & 0x01FF;
	spi_wren_e2prom(index);
	if(waddr_reg<=0x00FF)
	{
		SendData = (u32)WRITE | (u32)waddr_reg << 8 | (u32)wdata << 16;
		SPITX_dword(index,SendData);
    }
	else if(waddr_reg <= 0x01FF)
	{
		SendData = (u32)WRITEH | (u32)(waddr_reg&0xff) << 8 | (u32)wdata << 16;
		SPITX_dword(index,SendData);
	}

	while ((spi_rsdr_e2prom(eeprom_dev_num) & 0x01) == 1)//等待写完成
	{

	}
//	gtc_dly_time(GTC_MS, 5);
}
/*
 * 读一个字操作
 */
s16 spi_read_e2prom(u32 index, u16 raddr)
{
	u32 rdata;
	u32 tdata;
	u16 raddr_reg;

	raddr_reg = raddr;
	spi_dhb_dis(index);            //bit8 = 0 DHB 接收所有无效数据
	if(raddr_reg <= 0xff)
	{
		tdata = (u32)READ | (u32)raddr_reg << 8;
		rdata = SPIRX_dword(index,tdata) >> 16;
	}
	else if(raddr_reg <= 0x1FF)
	{
		tdata = (u32)READH | (u32)(raddr_reg&0xff) << 8;
		rdata = SPIRX_dword(index,tdata) >> 16;
	}

	return((s16)rdata);
}
#endif
#ifdef EEPROM_I2C
static u8 WREN = 0x06;
//static u8 WRDI = 0x04;
static u8 RSDR = 0x05;
//static u8 WRSR = 0x01;
static u8 READ = 0x03;
static u8 WRITE = 0x02;
static u8 READH = 0x0B;
static u8 WRITEH = 0x0A;
extern volatile struct I2C_REGS *I2C[];
u32 at24c32_addr = 0x50;
void i2c_init_e2prom(void)
{
	gpio_enable(GPIO_GRP_E, 6, 2, GPIO_FUN_2);
	init_i2c(eeprom_dev_num);
}
void i2c_at24c32_wbyte(u32 i2c_num,u32 SLAVE_ADDRESS,u8 first_addr,u8 sec_addr,u8 data)
{
	i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (first_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (sec_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
	(*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (data & 0xFF) | MASTER_WRITE | STOP_CMD );
	while( (*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET == 0x0);
	(*I2C[i2c_num]).I2C_INTR_CLR.bit.C_STOP_DET = 0x1;
}
u32 i2c_at24c32_pagew(u32 i2c_num,u32 SLAVE_ADDRESS,u8 first_addr,u8 sec_addr,u8 *data, u8 num)
{
        u32 i = 0;
        u32 write_done = 0;
        u32 timeout = 0;
        u32 timecnt;
        u32 cntval;
        cntval = 10000;
        if(num == 0 || num > 32)
        {
//                printk("num set error\n");
                return 0 ;
        }
        i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (first_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (sec_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
        do{
                if(i < (num-1)){
                        timecnt = cntval;
                        //瓒呮椂妫�娴�
                        do{
                                timecnt --;
                                if(timecnt == 0){
                                        timeout = 0x1;
                                        printk("i2c timeout\n");
                                        return timeout;
                                }
                        }while( (*I2C[i2c_num]).I2C_TXFLR.bit.TXFLR > 6);        //wait for fifo empty
                        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (data[i] & 0xFF) | MASTER_WRITE | NO_STOP_CMD );
                }
                else if(i == (num-1)){
                        timecnt = cntval;
                        //瓒呮椂妫�娴�
                        do{
                                timecnt --;
                                if(timecnt == 0){
                                        timeout = 0x1;
                                        printk("i2c timeout\n");
                                        return timeout;
                                }
                        }while( (*I2C[i2c_num]).I2C_TXFLR.bit.TXFLR > 6);        //wait for fifo empty
                        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (data[i] & 0xFF) | MASTER_WRITE | STOP_CMD );
                }
                else{
                        write_done = 0x1;
                }
                i++;
        }while(write_done == 0);
        return 0;
}
u32 i2c_at24c32_randomr(u32 i2c_num,u32 SLAVE_ADDRESS,u8 first_addr,u8 sec_addr)
{
        u32 read_val = 0;
        i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (first_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (sec_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( MASTER_READ |  STOP_CMD);
        while( (*I2C[i2c_num]).I2C_RAW_INTR_STAT.bit.STOP_DET == 0x0);
        (*I2C[i2c_num]).I2C_INTR_CLR.bit.C_STOP_DET = 0x1;
        read_val = (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS;
//      printk("val is 0x%x\n", read_val);
        return read_val;
}
u32 i2c_at24c32_sequencr(u32 i2c_num,u32 SLAVE_ADDRESS,u8 first_addr,u8 sec_addr,u8 *data, u8 num)
{
        u32 i = 0;
        u32 read_done = 0;
        u32 timeout = 0;
        u32 timecnt;
        u32 cntval;
        cntval = 10000;
        if(num == 0 || num > 32)
        {
//                printk("num set error\n");
                return 0 ;
        }
        i2c_target_address(i2c_num,SLAVE_ADDRESS);//set target address
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (first_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( (sec_addr & 0xFF) | MASTER_WRITE |  NO_STOP_CMD);
        do{
                if(i < (num-1)){
                        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( MASTER_READ |  NO_STOP_CMD);
                        timecnt = cntval;
                        do{
                                timecnt --;
                                if(timecnt == 0){
                                        timeout = 0x1;
//                                        printk("i2c timeout\n");
                                        return timeout;
                                }
                        }while( (*I2C[i2c_num]).I2C_RXFLR.bit.RXFLR == 0);        //wait for fifo not empty
                        data[i] = (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS;
                }
                else if(i == (num-1)){
                        (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS = ( MASTER_READ |  STOP_CMD);
                        timecnt = cntval;
                        do{
                                timecnt --;
                                if(timecnt == 0){
                                        timeout = 0x1;
//                                        printk("i2c timeout\n");
                                        return timeout;
                                }
                        }while( (*I2C[i2c_num]).I2C_RXFLR.bit.RXFLR == 0);        //wait for fifo not empty
                        data[i] = (*I2C[i2c_num]).I2C_DATA_CMD.bit.DAT_CMD_STOP_RS;
                }
                else{
                        read_done = 0x1;
                }
                i++;
        }while(read_done == 0);
        return 0;
}
void i2c_write_e2prom(u32 i2c_num,u16 waddr,u16 wdata)
{
	u8 data[2] = {0};		//16bits==>2x8bits
	data[0] = wdata & 0x00FF;
	data[1] = (wdata & 0xFF00)>>8;
	i2c_at24c32_pagew(i2c_num,at24c32_addr,(u8)((waddr & 0xFF00)>>8),(u8)(waddr & 0x00FF), data, 2);
	gtc_dly_time(GTC_MS,5);
}
s16 i2c_read_e2prom(u32 i2c_num,u16 raddr)
{
	u8 data[2] = {0};		//16bits==>2x8bits
	i2c_at24c32_sequencr(i2c_num,at24c32_addr,(u8)((raddr & 0xFF00)>>8),(u8)(raddr & 0x00FF), data, 2);
	return (s16)(data[0] + (data[1] <<8));
}
#endif



