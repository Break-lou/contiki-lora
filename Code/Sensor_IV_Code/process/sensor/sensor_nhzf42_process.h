#ifndef __sensor_NHZF42_process__
#define __sensor_NHZF42_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if NHZF42_OPERATE
PROCESS_NAME(sensor_nhzf42_process);

void post_nhzf42_calibration(void);
#endif
#define OPERATE_NHZF42 OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_NHZF42 DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
													 
#endif

