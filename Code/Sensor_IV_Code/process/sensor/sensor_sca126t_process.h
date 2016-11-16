#ifndef __sensor_SCA126T_process__
#define __sensor_SCA126T_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if SCA126T_OPERATE
PROCESS_NAME(sensor_sca126t_process);

void post_SCA126T_calibration(void);
void sca126t_sample_collect(void);
void post_sca126t_calibration(void);
#endif
#define OPERATE_SCA126T OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_SCA126T DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#endif

