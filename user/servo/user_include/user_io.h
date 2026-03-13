/*
 * user_io.h
 *
 *  Created on: 2023年8月14日
 *      Author: wenxing.ma
 */

#ifndef EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_USER_IO_H_
#define EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_USER_IO_H_
#include "GVAR_DEF.h"

extern int16_t   DI_SHOME_Enable;
extern int16_t   DI_SHOME_Finish;
extern int16_t   DI_MDC_Enable;
extern int16_t   DI_MDC_New;
extern int16_t   DI_MDC_Old;
extern int16_t   DI_ORG1_Old;
extern int16_t   DI_ORG1_New;
extern int16_t   DI_ORG1_Flag;
extern int32_t   DO_TSPD_Cnt;
extern int16_t   DI_PAUTO_New;
extern int16_t   DI_PAUTO_Old;
extern int16_t   DI_PAUTO_Delay;
extern int16_t   DI_SPD1_New;
extern int16_t   DI_SPD1_Old;
extern int16_t   DI_SPD2_New;
extern int16_t   DI_SPD2_Old;
extern int16_t   DI_MDC1;
extern int16_t   DI_ORG1_Enable;
extern int32_t   IoCheckDelay;

extern int16_t   DI_CLR_NEW;
extern int16_t   DI_CLR_OLD;
extern int16_t   DI_ALRS_NEW;
extern int16_t   DI_ALRS_OLD;
extern int16_t   DI_PTRG_New;
extern int16_t   DI_PTRG_Old;
extern int16_t   DI_SHOME_New;
extern int16_t   DI_SHOME_Old;
extern int16_t   Comm_SHOME_New;
extern int16_t   Comm_SHOME_Old;
extern int16_t   DI_POS1_New;
extern int16_t   DI_POS1_Old;
extern int16_t   DI_POS2_New;
extern int16_t   DI_POS2_Old;
extern int16_t   DI_POS2_Cnt;
extern int16_t   DI_EMC_New;
extern int16_t   DI_EMC_Old;
extern int16_t   DI_EMC_Flag;
extern int16_t   ioPrOutputfalg;

extern int16_t   DI_SHOME_Enable;
extern int16_t   DI_SHOME_Finish;

extern int16_t   DI_MDC_Enable;
extern int16_t   DI_MDC_New;
extern int16_t   DI_MDC_Old;
extern int16_t   DI_ORG1_Old;
extern int16_t   DI_ORG1_New;
extern int16_t   DI_ORG1_Flag;
extern int32_t   DO_TSPD_Cnt;

extern int16_t   DI_SetAxisNew;
extern int16_t   DI_SetAxisOld;
extern int16_t   DI_PAUTO_New;
extern int16_t   DI_PAUTO_Old;
extern int16_t   DI_PAUTO_Delay;
extern int16_t   DI_SPD1_New;
extern int16_t   DI_SPD1_Old;
extern int16_t   DI_SPD2_New;
extern int16_t   DI_SPD2_Old;
extern int16_t   DI_MDC1;
extern int16_t   DI_ORG1_Enable;

extern int16_t   Io_Output_state;
extern int16_t   Io_Input_state;
extern int16_t   Io_Input0_State;
extern int16_t   Io_Input1_State;
extern int16_t   Io_Input2_State;
extern int16_t   Io_Input3_State;
extern int16_t   Io_Input4_State;
extern int16_t   Io_Input5_State;
extern int16_t   Io_Input6_State;
extern int16_t   Io_Input7_State;
extern int16_t   Io_Input8_State;

extern int16_t   Io_Input0_Dir;
extern int16_t   Io_Input1_Dir;
extern int16_t   Io_Input2_Dir;
extern int16_t   Io_Input3_Dir;
extern int16_t   Io_Input4_Dir;
extern int16_t   Io_Input5_Dir;
extern int16_t   Io_Input6_Dir;
extern int16_t   Io_Input7_Dir;
extern int16_t   Io_Input8_Dir;

extern int16_t   Io_Output0_State;
extern int16_t   Io_Output1_State;
extern int16_t   Io_Output2_State;
extern int16_t   Io_Output3_State;
extern int16_t   Io_Output4_State;
extern int16_t   Io_Output0_Dir;
extern int16_t   Io_Output1_Dir;
extern int16_t   Io_Output2_Dir;
extern int16_t   Io_Output3_Dir;
extern int16_t   Io_Output4_Dir;

extern int16_t   PinFilterCnt0;
extern int16_t   PinFivlterCnt1;
extern int16_t   PinFilterCnt2;
extern int16_t   PinFilterCnt3;
extern int16_t   PinFilterCnt4;
extern int16_t   PinFilterCnt5;
extern int16_t   PinFilterCnt6;
extern int16_t   PinFilterCnt7;
extern int16_t   PinFilterCnt8;

extern int16_t   DI0_Force;
extern int16_t   DI1_Force;
extern int16_t   DI2_Force;
extern int16_t   DI3_Force;
extern int16_t   DI4_Force;
extern int16_t   DI5_Force;
extern int16_t   DI6_Force;
extern int16_t   DI7_Force;
extern int16_t   DI8_Force;

extern int16_t   DO0_Force;
extern int16_t   DO1_Force;
extern int16_t   DO2_Force;
extern int16_t   DO3_Force;
extern int16_t   DO4_Force;
extern int16_t   DISP_DO1;  //SRDY
extern int16_t   DISP_DO2;  //ALM
extern int16_t   DISP_DO3;  //ZSPD
extern int16_t   DISP_DO4;  //TSPD
extern int16_t   DISP_DO5;  //BRKR
extern int16_t   DISP_DO1;
extern int16_t   DISP_DO2;
extern int16_t   DISP_DO3;
extern int16_t   DISP_DO4;
extern int16_t   DISP_DO5;

extern int16_t   ioPowerOffInDelay;
extern SERVO_DI  IoDi;
extern SERVO_DO  IoDo;
extern void DesignGpio(void);
extern void CheckMotorAlarm(void);
#endif /* EXAMPLE_SVO_EXAMPLE_USER_INCLUDE_USER_IO_H_ */
