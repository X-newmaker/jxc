/*
 * can.c
 *
 */

/******************************************
 * Functions for CAN operation
 * ****************************************/
#include <all_inc.h>

volatile struct CAN_REGS Can0Regs __attribute__((__section__(".can0reg")));

volatile struct CAN_REGS *CAN[] = {&Can0Regs};

can_ctrl_t can_controller[CAN_NUM];      // can_controller[0] and can_controller[1]
can_intr_event can_event[CAN_NUM];
can_message_t rx_frame;
can_message_t tx_frame;

static void can0_null(void){};
static void can1_null(void){};
cpu_irq_fun_t can0_irqhandle = can0_null;
cpu_irq_fun_t can1_irqhandle = can1_null;

ATTRIBUTE_ISR void CAN_IRQHandler(void)
{
        can0_irq_handler();
}

void can0_irq_handler(void)
{
        can0_irqhandle();
}

ATTRIBUTE_ISR void CAN1_IRQHandler(void)
{
        can1_irq_handler();
}

void can1_irq_handler(void)
{
        can1_irqhandle();
}

void can_irq_register(u8 num, cpu_irq_fun_t irqhandle)
{
        switch(num){
                case 0:
                        can0_irqhandle = irqhandle;
                        cpu_irq_enable(CPU_IRQ_CAN);
                        break;
                case 1:
                        break;
		default:
                        break;               
        }
}

void can_irq_unregister(u8 num)
{
        switch(num){
                case 0:
                        can0_irqhandle = can0_null;
                        cpu_irq_disable(CPU_IRQ_CAN);
                        break;
                default:
                        break;               
        }
}

bus_err_msg_t bus_err_code[24] = {
	{0x3, "SOF"},
	{0x2, "ID28~21"},
	{0x6, "ID20~18"},
	{0x4, "SRTR"},
	{0x5, "IDE"},
	{0x7, "ID17~13"},
	{0xf, "ID12~5"},
	{0xe, "ID4~0"},
	{0xc, "RTR"},
	{0xd, "R1"},
	{0x9, "R0"},
	{0xb, "DLC"},
	{0xA, "DATA Field"},
	{0x8, "CRC Sequence"},
	{0x18, "CRC Delimiter"},
	{0x19, "ACK Slot"},
	{0x1B, "ACK Delimiter"},
	{0x1A, "EOF"},
	{0x12, "Intermission"},
	{0x11, "Active error"},
	{0x16, "Passive error"},
	{0x13, "Tolerate dominant bits"},
	{0x17, "Error delimiter"},
	{0x1c, "Overload"}
};

/* CAN Bus Error Type */
bus_err_msg_t bus_err_type[4] = {
	{0x0, "Bit Error"},
	{0x1, "Form Error"},
	{0x2, "Stuff Error"},
	{0x3, "Other Error"}
};

/* CAN Bus Error Direction */
bus_err_msg_t bus_err_dir[2] = {
	{0x0, "error in TX direction"},
	{0x1, "error in RX direction"},
};

/* CAN Bus Arbitration Lost */
bus_err_msg_t bus_arb_lost[32] = {
	{0x0, "ID28 ArbLost"},
	{0x1, "ID27 ArbLost"},
	{0x2, "ID26 ArbLost"},
	{0x3, "ID25 ArbLost"},
	{0x4, "ID24 ArbLost"},
	{0x5, "ID23 ArbLost"},
	{0x6, "ID22 ArbLost"},
	{0x7, "ID21 ArbLost"},
	{0x8, "ID20 ArbLost"},
	{0x9, "ID19 ArbLost"},
	{0xA, "ID18 ArbLost"},
	{0xB, "SRTR ArbLost"},
	{0xC, "IDE  ArbLost"},
	{0xD, "ID17 ArbLost"},
	{0xE, "ID16 ArbLost"},
	{0xF, "ID15 ArbLost"},
	{0x10, "ID14 ArbLost"},
	{0x11, "ID13 ArbLost"},
	{0x12, "ID12 ArbLost"},
	{0x13, "ID11 ArbLost"},
	{0x14, "ID10 ArbLost"},
	{0x15, "ID9 ArbLost"},
	{0x16, "ID8 ArbLost"},
	{0x17, "ID7 ArbLost"},
	{0x18, "ID6 ArbLost"},
	{0x19, "ID5 ArbLost"},
	{0x1A, "ID4 ArbLost"},
	{0x1B, "ID3 ArbLost"},
	{0x1C, "ID2 ArbLost"},
	{0x1D, "ID1 ArbLost"},
	{0x1E, "ID0 ArbLost"},
	{0x1F, "RTR ArbLost"},
};

/*function for configuring clock and bus reset for CAN
 * return 0 for OK, and -1 for error */
int can_cmu_init(u32 n)
{
	int i = 0;
	if(n == 0)
	{
		if(cmu_mod_get_status(CMU_MOD_CAN0)==RET_OK) return RET_FALSE;
		cmu_mod_disable(CMU_MOD_CAN0);
		for(i=0; i<0x10; i++);
		cmu_mod_enable(CMU_MOD_CAN0);
		return RET_OK;
	}
	else
	{
		if(cmu_mod_get_status(CMU_MOD_CAN1)==RET_OK) return RET_FALSE;
		cmu_mod_disable(CMU_MOD_CAN1);
		for(i=0; i<0x10; i++);
		cmu_mod_enable(CMU_MOD_CAN1);
		return RET_OK;
	}
}

/*Set CAN Operating Mode*/
void can_mode_set(u32 n, can_op_mode mode)
{

	switch(mode)
	{
		case RESET_MODE:
			(*CAN[n]).CAN_MODE.bit.RST_MOD = 0x1; 
			break;
		case LISTEN_MODE:
			(*CAN[n]).CAN_MODE.bit.LISTEN_MOD = 0x1; 
			break;
		case SELFTEST_MODE:
			(*CAN[n]).CAN_MODE.bit.SELFTEST_MOD = 0x1; 
			break;
		case SINGLE_FILTER:
			(*CAN[n]).CAN_MODE.bit.FILTER_MOD = 0x1; 
			break;
		case SLEEP_MODE:
			(*CAN[n]).CAN_MODE.bit.SLEEP_MOD = 0x1; 
			break;
		default:
			break;
	}

	can_controller[n].op_mode |= mode;       //op_mode=1, controller is not in normal operation mode
}

/*Release CAN Operating Mode*/
void can_mode_release(u32 n, u32 mode)
{

	switch(mode)
	{
		case RESET_MODE:
			(*CAN[n]).CAN_MODE.bit.RST_MOD = 0x0; 
			break;
		case LISTEN_MODE:
			(*CAN[n]).CAN_MODE.bit.LISTEN_MOD = 0x0; 
			break;
		case SELFTEST_MODE:
			(*CAN[n]).CAN_MODE.bit.SELFTEST_MOD = 0x0; 
			break;
		case SINGLE_FILTER:
			(*CAN[n]).CAN_MODE.bit.FILTER_MOD = 0x0; 
			break;
		case SLEEP_MODE:
			(*CAN[n]).CAN_MODE.bit.SLEEP_MOD = 0x0; 
			break;
		default:
			break;
	}

	can_controller[n].op_mode &= ~mode;     //op_mode=0, controller is in normal operation mode
}

/*Set CAN Module Control Command*/
void can_cmd_set(u32 n, u32 cmd)
{
	switch(cmd)
	{
		case TX_REQ:
			(*CAN[n]).CAN_MCR.bit.TX_REQ = 0x1; 
			break;
		case ABORT_REQ:
			(*CAN[n]).CAN_MCR.bit.ABORT_REQ = 0x1; 
			break;
		case RXBUF_RELEASE:
			(*CAN[n]).CAN_MCR.bit.RXB_REL = 0x1; 
			break;
		case CLEAR_OVF_FLAG:
			(*CAN[n]).CAN_MCR.bit.CLR_OVF_FLAG = 0x1; 
			break;
		case SELF_REQ:
			(*CAN[n]).CAN_MCR.bit.SELF_REQ = 0x1; 
			break;
		default:
			break;
	}

}


/*Get CAN Module Status*/
u32 can_status_get(u32 n)
{
	return ((*CAN[n]).CAN_STAT.all);
}


/*Enable Interrupt*/
void can_enable_int(u32 n, u32 temp)
{
	(*CAN[n]).CAN_INTEN.all = temp;
}

/*Disable Interrupt*/
void can_disable_int(u32 n, u32 temp)
{
	u32 reg = (*CAN[n]).CAN_INTEN.all ;
	reg &= ~temp;
	(*CAN[n]).CAN_INTEN.all = reg;
}

/*Disable All Interrupt */
void can_dis_all_int(u32 n)
{
	(*CAN[n]).CAN_INTEN.all = 0x0;
}

/*Get CAN Arbitration Lost*/
u32 can_arblost_get(u32 n)
{
	return ((*CAN[n]).CAN_ERRCODE.all);
}

/*Get CAN Bus Error Code*/
u32 can_error_code_get(u32 n)
{
	return ((*CAN[n]).CAN_ERRCODE.bit.ERR_CODE);
}

/*Get CAN Bus Error Type*/
u32 can_error_type_get(u32 n)
{
	return ((*CAN[n]).CAN_ERRCODE.bit.ERR_TYPE);
}

/*Get CAN Bus Error Direction*/
u32 can_error_dir_get(u32 n)
{
	return ((*CAN[n]).CAN_ERRCODE.bit.ERR_DIR);
}

/*set error warning threshold, default value is 96 (0x60), only can be write at Reset Mode*/
void can_errwt_set(u32 n, u32 errwt)
{
	(*CAN[n]).CAN_ERRWT.bit.ERRWT = errwt;
}

/*get error warning threshold, default value is 96 (0x60)*/
u32 can_errwt_get(u32 n, u32 errwt)
{
	return ((*CAN[n]).CAN_ERRWT.all);
}

/*Get CAN TX Error Count*/
u32 can_tx_error_count_get(u32 n)
{
	return ((*CAN[n]).CAN_TXERR.all);
}

/*Get CAN RX Error Count*/
u32 can_rx_error_count_get(u32 n)
{
	return ((*CAN[n]).CAN_RXERR.all);
}


/*Get CAN Receive Message Count*/
u32 can_rx_msg_count_get(u32 n)
{
	return ((*CAN[n]).CAN_RXC.all);
}

/*Get CAN Receive Buffer Start Address*/
u32 can_rxb_start_addr_get(u32 n)
{
	return ((*CAN[n]).CAN_RSADDR.all);
}

/*Get CAN Interrut Status*/
u32 can_intr_get(u32 n)
{
	return ((*CAN[n]).CAN_INTR.all);
}

/*Get CAN Interrut Enable*/
u32 can_inten_get(u32 n)
{
	return ((*CAN[n]).CAN_INTEN.all);
}

/*Get CAN Interrut Enable*/
u32 can_mode_get(u32 n)
{
	return ((*CAN[n]).CAN_MODE.all);
}

void can_clr_rx_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.RX_INT = 0x1;
}

void can_clr_tx_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.TX_INT = 0x1;
}

void can_clr_errw_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.ERRW_INT = 0x1;
}

void can_clr_ovf_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.OVF_INT = 0x1;
}

void can_clr_errp_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.ERRP_INT = 0x1;
}

void can_clr_arbl_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.ARBLOST_INT = 0x1;
}

void can_clr_errb_int(u32 n)
{
	(*CAN[n]).CAN_INTR.bit.ERRB_INT = 0x1;
}

/*Print Bus Error Message*/
void can_buserr_msg(u32 n)
{
	u32 i;
	u32 err_code = can_error_code_get(n);
	u32 err_type = can_error_type_get(n);
	u32 err_dir = can_error_dir_get(n);
	for (i=0; i<24; i++)
	{
		if (err_code == bus_err_code[i].code)
		{
			printk("can %x err_code = %x, msg = %s\n", n, err_code, bus_err_code[i].msg);
			break;
		}
	}

	for (i=0; i<4; i++)
	{
		if (err_type == bus_err_type[i].code)
		{
			printk("can %x err_type = %x, msg = %s\n", n, err_type, bus_err_type[i].msg);
			break;
		}
	}

	for (i=0; i<2; i++)
	{
		if (err_dir == bus_err_dir[i].code)
		{
			printk("can %x err_dir = %x, msg = %s\n", n, err_dir, bus_err_dir[i].msg);
			break;
		}

	}
}

/*Print Arbitration Lost Message*/
void can_arblost_msg(u32 n)
{
	u32 i;
	u32 arb_lost = can_arblost_get(n);
	for (i=0; i<32; i++)
	{
		if (arb_lost == bus_arb_lost[i].code)
		{
			printk("can %x arbitration lost , arb_lost = %x, msg = %s\n", n, arb_lost, bus_arb_lost[i].msg);
			break;
		}
	}
}

/*Interrupt handler*/
void can_int_handler(u32 n)
{

	u32 int_flag = can_intr_get(n);
	u32 int_enable = can_inten_get(n);
	u32 intr = int_flag & int_enable;

	if (intr & ERRB_INT)       //if errb_int=1
	{
		can_clr_errb_int(n);
		can_event[n].bus_error ++;
		can_controller[n].error = 1;
		can_msg_print();
		printk("can %x bus error : interrupt = %02x\n", n, int_flag);
//		can_buserr_msg(n);       // print the error code message
	}
	if (intr & ARBLOST_INT)       //if ARBLOST_INT=1
	{
		can_clr_arbl_int(n);
		can_event[n].arbitration_lost ++;
		can_arblost_msg(n);       // print Arbitration Lost message
	}
	if (intr & ERRP_INT)       //if errb_int=1
	{
		can_clr_errp_int(n);
		can_event[n].passive_error ++;
		can_controller[n].error = 1;
		can_msg_print();
		printk("can %x passive error : interrupt = %02x\n", n, int_flag);
//		can_buserr_msg(n);       // print the error code message
	}
	if (intr & WAKEUP_INT)
	{
		can_event[n].wake_up ++;
		printk("can %x wake-up\n", n);
	}
	if (intr & OVF_INT)
	{
		can_clr_ovf_int(n);
		can_event[n].overflow ++;
		can_controller[n].error = 1;
		can_msg_print();
		printk("can %x data overflow\n", n);
//		can_buserr_msg(n);
		can_cmd_set(n, CLEAR_OVF_FLAG);     //clear overflow flag
	}
	if (intr & ERRW_INT)
	{
		can_clr_errw_int(n);
		can_event[n].error_warning ++;
		can_controller[n].error = 1;
		can_msg_print();
		printk("can %x error warning : interrupt = %02x\n", n, int_flag);
//		can_buserr_msg(n);       // print the error code message
	}
	if (intr & TXB_READY)     //Transmit buffer is released, TXB ready
	{
		can_clr_tx_int(n);
		can_event[n].txb_available ++;
		printk("can %x Transmit buffer is ready\n", n);
		can_disable_int(n, TX_INT);
		can_controller[n].txb_rdy = 1;
	}
	if (intr & RXB_READY)     //Receive buffer is not empty, RXB ready
	{
		can_clr_rx_int(n);
		can_event[n].rxb_available ++;
		can_rx_frame(n, &rx_frame);
		(*CAN[n]).CAN_INTR.all = (int_flag & 0xEF);

		printk("CAN %x Receive Ready\n", n);

	}

}

void can0_int_handler()
{
	can_int_handler(0);
}

void can_msg(u32 n)
{
	u32 mode0 = can_mode_get(n);

	u32 status0 =  can_status_get(n);

	u32 rsaddr0 =  can_rxb_start_addr_get(n);

	u32 rec0 =  can_rx_error_count_get(n);

	u32 tec0 =  can_tx_error_count_get(n);


	printk("\n");
	if(mode0 & SELFTEST_MODE )  printk("can selftest_mode; ");
	if(mode0 & LISTEN_MODE )  printk("can listen_only_mode; ");
	if(mode0 & RESET_MODE )  printk("can reset_mode; ");
	else  printk("can normal_op_mode; ");
	printk("\n");

	printk("can_mode = 0x%x\n", mode0);

	if(status0 & BUS_OFF )  printk("can BUS_OFF; ");
	else  printk("can BUS_Active; ");
	if(status0 & ERR_STAT )  printk("can Error; ");
	if(status0 & TX_BUSY )  printk("can TX_BUSY; ");
	if(status0 & RX_BUSY )  printk("can RX_BUSY; ");
	if(status0 & TXB_READY )  printk("can TXB_READY; ");
	if(status0 & RXB_READY )  printk("can RXB_READY; ");
	printk("\n");

	printk("can%d_status = 0x%x\n", n,status0);
	printk("can%d_rsaddr = 0x%x\n", n,rsaddr0);
	printk("can%d_rec = %d\n", n,rec0);
	printk("can%d_tec = %d\n", n,tec0);
	printk("\n");
}

void can_msg_print(void)
{
	u32 mode0 = can_mode_get(0);
	u32 mode1 = can_mode_get(1);
	u32 status0 =  can_status_get(0);
	u32 status1 =  can_status_get(1);
	u32 rsaddr0 =  can_rxb_start_addr_get(0);
	u32 rsaddr1 =  can_rxb_start_addr_get(1);
	u32 rec0 =  can_rx_error_count_get(0);
	u32 rec1 =  can_rx_error_count_get(1);
	u32 tec0 =  can_tx_error_count_get(0);
	u32 tec1 =  can_tx_error_count_get(1);

	printk("\n");
	if(mode0 & SELFTEST_MODE )  printk("can0 selftest_mode; ");
	if(mode0 & LISTEN_MODE )  printk("can0 listen_only_mode; ");
	if(mode0 & RESET_MODE )  printk("can0 reset_mode; ");
	else  printk("can0 normal_op_mode; ");
	printk("\n");
	if(mode1 & SELFTEST_MODE )  printk("can1selftest_mode; ");
	if(mode1 & LISTEN_MODE )  printk("can1 listen_only_mode; ");
	if(mode1 & RESET_MODE )  printk("can1 reset_mode; ");
	else  printk("can1 normal_op_mode; ");
	printk("\n");
	printk("can0_mode = 0x%x, can1_mode = 0x%x\n", mode0, mode1);

	if(status0 & BUS_OFF )  printk("can0 BUS_OFF; ");
	else  printk("can0 BUS_Active; ");
	if(status0 & ERR_STAT )  printk("can0 Error; ");
	if(status0 & TX_BUSY )  printk("can0 TX_BUSY; ");
	if(status0 & RX_BUSY )  printk("can0 RX_BUSY; ");
	if(status0 & TXB_READY )  printk("can0 TXB_READY; ");
	if(status0 & RXB_READY )  printk("can0 RXB_READY; ");
	printk("\n");
	if(status1 & BUS_OFF )  printk("can1 BUS_OFF; ");
	else  printk("can1 BUS_Active; ");
	if(status1 & ERR_STAT )  printk("can1 Error; ");
	if(status1 & TX_BUSY )  printk("can1 TX_BUSY; ");
	if(status1 & RX_BUSY )  printk("can1 RX_BUSY; ");
	if(status1 & TXB_READY )  printk("can1 TXB_READY; ");
	if(status1 & RXB_READY )  printk("can1 RXB_READY; ");
	printk("\n");
	printk("can0_status = 0x%x, can1_status = 0x%x\n", status0, status1);
	printk("can0_rsaddr = 0x%x, can1_rsaddr = 0x%x\n", rsaddr0, rsaddr1);
	printk("can0_rec = %d, can1_rec = %d\n", rec0, rec1);
	printk("can0_tec = %d, can1_tec = %d\n", tec0, tec1);
	printk("\n");
}

void can_frame_print(can_message_t *frame)
{
	u32 i = 0;
	printk("id = 0x%x, rtr = %x, ide = %x, dlc = %x, data = ", frame->id, frame->rtr, frame->ide, frame->dlc);
	for (i=0; i<frame->dlc; i++)
		printk("0x%x ", frame->data[i]);
	printk("\n");
}


/*function for CAN initial*/
void can_init(u32 n)
{
	_memset(&can_event, 0, sizeof(can_intr_event));
	can_cmu_init(n);					//can controller reset
	can_mode_set(n, RESET_MODE);  				//set can controller going to reset mode

	can_enable_int(n, ERRB_INT|ERRP_INT|OVF_INT|RX_INT);   	//enable interrupt: bus_error, passive_error,overflow, rx_int

	//can_set_errwt(n, 96);					//set error warning, keep default value 96
	can_mode_release(n, RESET_MODE);  			//set can controller returning to normal operation mode
}

/*function for CAN exit*/
void can_exit(u32 n)
{
	if(n == 0)
	{
		cmu_mod_disable(CMU_MOD_CAN0);
	}
	else if(n == 1)
	{
		cmu_mod_disable(CMU_MOD_CAN1);
	}

	_memset(&can_controller, 0, sizeof(can_controller));
}


/*Transmit a CAN Message*/
s32 can_tx_frame(u32 n, can_message_t* frame, can_self_test_type sel_test)
{
	s32 ret = RET_OK;
	u32 temp = 0;
	int i = 0;

	while (!(can_status_get(n) & TXB_READY));  	 //Wait for TX buffer release, ready

	/*Write a Message into buffer0~buffer12*/
        temp = (frame->ide<<7)|(frame->rtr<<6)|(frame->dlc);
	(*CAN[n]).CAN_BUF0_RXC0.all = temp;

	if (frame->ide)    								//ide=1, extended frame format
	{
		(*CAN[n]).CAN_BUF1_RXC1.all = (frame->id>>21) & 0xff;
		(*CAN[n]).CAN_BUF2_RXC2.all = (frame->id>>13) & 0xff;
		(*CAN[n]).CAN_BUF3_RXC3.all = (frame->id>>5) & 0xff;
		(*CAN[n]).CAN_BUF4_RXM0.all = (frame->id & 0x1f)<<3;

		for (i=0; i<frame->dlc; i++)
		{
			writel(frame->data[i], CAN[n]+0x54+i*4);    //Data Information,buf5...
		}
	}
	else                    						//ide=0, standard frame format
	{
                (*CAN[n]).CAN_BUF1_RXC1.all = (frame->id>>3) & 0xff;
                (*CAN[n]).CAN_BUF2_RXC2.all = (frame->id & 0x7)<<5;

		for (i=0; i<frame->dlc; i++)
		{
			writel(frame->data[i], CAN[n]+0x4c+i*4);	//Data Information,buf3...
		}
	}

//	while (!(can_status_get(n) & TXB_READY));   //

	if(sel_test)
	        can_cmd_set(n, SELF_REQ);    	//Self Test Request

	else
	        can_cmd_set(n, TX_REQ);          //Transmission Request


	do {
		temp = can_status_get(n);
		if (temp & (BUS_OFF|ERR_STAT|OVF_FLAG))     //bus_off=1 or err_stat=1 or ovf_flag=1, status error
		{
			can_abort_frame(n);         //Abort Transmission
			ret = RET_FALSE;
			break;
		}
	} while (!(temp & TX_COMPLETE));   //Wait for Transmission Complete

	return ret;
}

/*Transmit series CAN Message Test*/
u32 test_tx_series_frame(u32 n, can_message_t *txmsg_tbl, int txmsg_cnt)
{
	s32 ret = RET_OK;
	int i = 0;

	for(i=0; i<txmsg_cnt; i++)
	{
		can_tx_frame(n, &txmsg_tbl[i], NON_SELF_TEST);
		can_frame_print(&txmsg_tbl[i]);
		printk("message %d was transmitted\n", i);
		printk("\n");
		gtc_dly_time(GTC_US,100);
	}
	return ret;
}

/*Receive a CAN Message*/
s32 can_rx_frame(u32 n, can_message_t* frame)
{
	s32 ret = RET_FALSE;
	u32 temp = 0;
	int i = 0;

	while (!(can_status_get(n) & RXB_READY));   //Wait for RX Buffer Ready

	can_controller[n].rxb_rdy = 0;

	if (can_controller[n].error)
	{
		ret = RET_FALSE;
		can_cmd_set(n, RXBUF_RELEASE);     //Release RX Buffer
		can_controller[n].error = 0;
		goto out;
	}
//	printk("can%x_rxb_msg_count = %d\n", n, can_rx_msg_count_get(n));
	/*Get a Message from Buffer0~Buffer12*/
	temp = (*CAN[n]).CAN_BUF0_RXC0.all;
	frame->ide = temp>>7;
	frame->rtr = (temp>>6) & 0x1;
	frame->dlc = temp & 0xf;						//Get Frame Information from Buffer0
	if (frame->ide)										//ide=1, extended frame format
	{

                frame->id = (((u32)(*CAN[n]).CAN_BUF1_RXC1.all)<<21) |      //id28~21
                                    (((u32)(*CAN[n]).CAN_BUF2_RXC2.all)<<13) |      //id20~13
                                    (((u32)(*CAN[n]).CAN_BUF3_RXC3.all)<<5) |       //id12~5
                                    ((((*CAN[n]).CAN_BUF4_RXM0.all)>>3) & 0x1f);      //id4~0

		if(frame->rtr==0)              				//when rtr=1,don't need to read BUF5
		for (i = 0; i<frame->dlc; i++)
		{
			frame->data[i] = readl(CAN[n]+0x54+i*4);        //buf5...
		}
	}
	else												//ide=0, standard frame format
	{

                frame->id = (((u32)(*CAN[n]).CAN_BUF1_RXC1.all)<<3) |      //STID id10~3 / id28~21
                                    ((((*CAN[n]).CAN_BUF2_RXC2.all)>>5) & 0x7);     //STID id2~0 / id20~18

		if(frame->rtr==0)              				//when rtr=1,don't need to read BUF3
		for (i = 0; i<frame->dlc; i++)
		{
			frame->data[i] = readl(CAN[n]+0x4c+i*4);        //buf3...
		}
	}
	can_cmd_set(n, RXBUF_RELEASE);   //release rx buffer
	// can_enable_int(n, RX_INT);		//enable RX_INT interrupt
	ret = RET_OK;
out:
	return ret;
}

/*Receive series CAN Message*/
u32 test_rx_series_frame(u32 n, can_message_t *rxmsg_tbl)
{
	u32 i;
	u32 rxmsg_cnt = 0;
	rxmsg_cnt = can_rx_msg_count_get(n);
	for (i=0; i<rxmsg_cnt; i++)
	{
//		_memset(&rxmsg_tbl[i], 0, sizeof(can_message_t));
		can_msg_print();
		can_rx_frame(n, &rxmsg_tbl[i]);
		can_msg_print();
		can_frame_print(&rxmsg_tbl[i]);
		printk("message %d was received\n", i);
		gtc_dly_time(GTC_US,500);
		if(!(can_status_get(n) & RXB_READY)) break;
	}

	return RET_OK;
}


/* Abort Transmission */
void can_abort_frame(u32 n)
{
	can_cmd_set(n, ABORT_REQ);
	while (!((*CAN[n]).CAN_STAT.bit.TXB_STAT));		//wait tx buffer release, ready
}



/*Set CAN Controller n=0~1 Baud Rate */
s32 can_baudrate_set(u32 n, u32 baud)
{
	u32 btr1;
	u32 btr0;
	u32 numtq=0, numtq_t=0, numtq_tt=0;  	 //TQ number in one bit
	u32 brp=0, brp_t=0, brp_tt=0;  		 //Baud Rate Prescaler
	u32 numtq_brp;    						//baudrate = f_pclk/numtq*brp, numtq=(1+(ts1+1)+(ts2+1))
	u8  sjw = 1;
	u8  ts1 = 0;
	u8  ts2 = 0;
	u32  sam = 0;
	u32 real_rate = 0;
	u32 error = 0;
	u32 min_error = 100;
	u32  remain_zero = 0;
	u32 f_pclk ;
	u32 baudrate = 2*baud;

	f_pclk = cmu_mod_get_freq(CMU_MOD_CAN0+n);

	can_mode_set(n, RESET_MODE);   //to reset mode
	//Calculate Baud Rate
	if (!baudrate)
		return RET_FALSE;
	numtq_brp = f_pclk/baudrate;   // numtq_brp=[1+ TS1 + TS2]*BRP

	if (numtq_brp>1280)      //numtq_t = 20, BRP[5:0] maximum 64
	{
		printk("Fpclk is too large for BRP divider\n");
	}
	for (numtq_t = 20; numtq_t>6; numtq_t--)
	{
		brp_t = numtq_brp/numtq_t; 		//numtq_brp > numtq_t
		if (!brp_t)
			continue;
		if (numtq_brp%numtq_t)
		{
			real_rate = f_pclk/(brp_t*numtq_t);
			//计算误差
			if (real_rate > baudrate)
				error = (real_rate - baudrate)*100/baudrate;
			else
				error = (baudrate-real_rate)*100/baudrate;
			if (error<min_error)
			{
				min_error = error;
				numtq_tt = numtq_t;
				brp_tt = brp_t;
			}
		}
		else
		{
			numtq = numtq_t;
			brp = brp_t;
			remain_zero = 1;
			//计算误差
			real_rate = f_pclk/(brp_t*numtq_t);
			if (real_rate>baudrate)
				min_error = (real_rate-baudrate)*100/baudrate;
			else
				min_error = (baudrate-real_rate)*100/baudrate;
			break;
		}
	}

	if (!remain_zero)
	{
		 numtq = numtq_tt;
		 brp = brp_tt;
	}

	ts2 = (numtq*20)/100;
	ts1 = numtq - ts2 - 1;
	while (ts1 > 16)
	{
		ts2 ++;
		ts1 = numtq - ts2 - 1;
	}
	sam = (baudrate<100000) ? 1 : 0;    // Baudrate < 100khz sam=1, Baudrate >= 100khz sam=0
	if (sjw>ts2)
		sjw = ts2;

	(*CAN[n]).CAN_BTR1.bit.SAM = sam;
	(*CAN[n]).CAN_BTR1.bit.TS1 = (ts1-1);
	(*CAN[n]).CAN_BTR1.bit.TS2 = (ts2-1);

	(*CAN[n]).CAN_BTR0.bit.BRP = (brp-1);
	(*CAN[n]).CAN_BTR0.bit.SJW = (sjw-1);

	btr1 = (*CAN[n]).CAN_BTR1.all;
	btr0 = (*CAN[n]).CAN_BTR0.all;

	printk("buadrate = %2dK, BTR0 =0x%x, BTR1 =0x%x, BRP = %d, SJW = %d, TS1 = %d,TS2 = %d, sam = %x, numtq = %d, sample_point = %d.%d%%, real rate = %d.%dK, error = %d%%\n",
			baud/1000, btr0, btr1,  brp, sjw, ts1, ts2,sam, numtq, (numtq-ts2)*100/numtq, ((numtq-ts2)*1000/numtq)%10,
			f_pclk/(2*numtq*brp)/1000, ((f_pclk/100)/(2*numtq*brp))%10, min_error);

	//return to transfer mode
	can_mode_release(n, RESET_MODE);
	return RET_OK;
}

/*Set CAN Controller Acceptance Filter,RXCODE RXMASK
 *Parameter: n--0~1, CAN Controller 0 and 1
 * 			 ide-- IDE = 0, 11bit SFF; IDE = 1, 29bit EFF
 * 			 mode--filter mode
 *Return: 	 RET_OK
*/
s32 can_filter_set(u32 n, u32 ide, u32 mode, can_filter_t* pcode, can_filter_t* pmask)
{
	u32 temp;
	u32 code0, code1, code2, code3;
	u32 mask0, mask1, mask2, mask3;

	can_mode_set(n, RESET_MODE);			//goto reset mode
	can_controller[n].flt_mode = mode;		//filter mode
	if (mode == FILTER_CLOSE)
	{
		(*CAN[n]).CAN_BUF4_RXM0.bit_rxm0.RXM0 = 0xff;	//filter_close, match nothing
		(*CAN[n]).CAN_BUF5_RXM1.bit_rxm1.RXM1 = 0xff;	//filter_close, match nothing
		(*CAN[n]).CAN_BUF6_RXM2.bit_rxm2.RXM2 = 0xff;	//filter_close, match nothing
		(*CAN[n]).CAN_BUF7_RXM3.bit_rxm3.RXM3 = 0xff;	//filter_close, match nothing


		goto out;
	}
	else if (mode == SINGLE_FILTER_MODE)
	{
		can_mode_set(n, SINGLE_FILTER);		//enable single_filter_mode
		if(ide)
		{
			code0 = (pcode->single_filter_ext.id>>21 & 0xff);
			code1 = (pcode->single_filter_ext.id>>13 & 0xff);
			code2 = pcode->single_filter_ext.id>>5 & 0xff;
			code3 = (pcode->single_filter_ext.id & 0x1f)<<3|
					pcode->single_filter_ext.rtr<<2;

			mask0 = (pmask->single_filter_ext.id>>21 & 0xff);
			mask1 = (pmask->single_filter_ext.id>>13 & 0xff);
			mask2 = pmask->single_filter_ext.id>>5 & 0xff;
			mask3 = (pmask->single_filter_ext.id & 0x1f)<<3|
					pmask->single_filter_ext.rtr<<2;

		}
		else
		{
			code0 = (pcode->single_filter_std.id>>3 & 0xff);
			code1 = (pcode->single_filter_std.rtr<<4)|
					(pcode->single_filter_std.id & 0x7)<<5;
			code2 = pcode->single_filter_std.data0 & 0xff;
			code3 = pcode->single_filter_std.data1 & 0xff;

			mask0 = (pmask->single_filter_std.id>>3 & 0xff);
			mask1 = (pmask->single_filter_std.rtr<<4)|
					(pmask->single_filter_std.id & 0x7)<<5;
			mask2 = pmask->single_filter_std.data0 & 0xff;
			mask3 = pmask->single_filter_std.data1 & 0xff;

		}

		(*CAN[n]).CAN_BUF0_RXC0.bit_rxc0.RXC0 = code0;
		(*CAN[n]).CAN_BUF1_RXC1.bit_rxc1.RXC1 = code1;
		(*CAN[n]).CAN_BUF2_RXC2.bit_rxc2.RXC2 = code2;
		(*CAN[n]).CAN_BUF3_RXC3.bit_rxc3.RXC3 = code3;
		(*CAN[n]).CAN_BUF4_RXM0.bit_rxm0.RXM0 = mask0;
		(*CAN[n]).CAN_BUF5_RXM1.bit_rxm1.RXM1 = mask1;
		(*CAN[n]).CAN_BUF6_RXM2.bit_rxm2.RXM2 = mask2;
		(*CAN[n]).CAN_BUF7_RXM3.bit_rxm3.RXM3 = mask3;		
	
		goto out;

	}
	else if (mode == DUAL_FILTER_MODE)
	{
		can_mode_release(n, SINGLE_FILTER);
		if(ide)
		{
			code0 = (pcode->dual_filter_ext.flt0_id_h16>>8 & 0xff);
			code1 = (pcode->dual_filter_ext.flt0_id_h16 & 0xff);
			code2 = (pcode->dual_filter_ext.flt1_id_h16>>8 & 0xff);
			code3 = (pcode->dual_filter_ext.flt1_id_h16 & 0xff);

			mask0 = (pmask->dual_filter_ext.flt0_id_h16>>8 & 0xff);
			mask1 = (pmask->dual_filter_ext.flt0_id_h16 & 0xff);
			mask2 = (pmask->dual_filter_ext.flt1_id_h16>>8 & 0xff);
			mask3 = (pmask->dual_filter_ext.flt1_id_h16 & 0xff);
		}
		else
		{

			code0 = (pcode->dual_filter_std.flt0_id>>3) & 0xff;
			code1 = (pcode->dual_filter_std.flt0_data0 & 0xf0)>>4|
				   (pcode->dual_filter_std.flt0_rtr<<4)|
				   (pcode->dual_filter_std.flt0_id & 0x7)<<5;

			code2 = (pcode->dual_filter_std.flt1_id>>3) & 0xff;
			code3 = (pcode->dual_filter_std.flt0_data0 & 0x0f)|
				   (pcode->dual_filter_std.flt1_rtr<<4)|
				   (pcode->dual_filter_std.flt1_id & 0x7)<<5;

			mask0 = (pmask->dual_filter_std.flt0_id>>3) & 0xff;
			mask1 = (pmask->dual_filter_std.flt0_data0 & 0xf0)>>4|
					(pmask->dual_filter_std.flt0_rtr<<4)|
					(pmask->dual_filter_std.flt0_id & 0x7)<<5;

			mask2 = (pmask->dual_filter_std.flt1_id>>3) & 0xff;
			mask3 = (pmask->dual_filter_std.flt0_data0 & 0x0f)|
					(pmask->dual_filter_std.flt1_rtr<<4)|
					(pmask->dual_filter_std.flt1_id & 0x7)<<5;
		}

		(*CAN[n]).CAN_BUF0_RXC0.bit_rxc0.RXC0 = code0;
		(*CAN[n]).CAN_BUF1_RXC1.bit_rxc1.RXC1 = code1;
		(*CAN[n]).CAN_BUF2_RXC2.bit_rxc2.RXC2 = code2;
		(*CAN[n]).CAN_BUF3_RXC3.bit_rxc3.RXC3 = code3;
		(*CAN[n]).CAN_BUF4_RXM0.bit_rxm0.RXM0 = mask0;
		(*CAN[n]).CAN_BUF5_RXM1.bit_rxm1.RXM1 = mask1;
		(*CAN[n]).CAN_BUF6_RXM2.bit_rxm2.RXM2 = mask2;
		(*CAN[n]).CAN_BUF7_RXM3.bit_rxm3.RXM3 = mask3;	

		goto out;
	}

out:
	can_mode_release(n, RESET_MODE);    //return to normal operation mode
	return RET_OK;
}

