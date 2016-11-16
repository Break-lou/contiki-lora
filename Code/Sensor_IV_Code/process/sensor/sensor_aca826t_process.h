#ifndef __sensor_ACA826T_process__
#define __sensor_ACA826T_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if ACA826T_OPERATE
PROCESS_NAME(sensor_aca826t_process);

void post_ACA826T_calibration(void);
#endif
#define OPERATE_ACA826T OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_ACA826T DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#endif

