#ifndef __sensor_NHZD10_process__
#define __sensor_NHZD10_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if NHZD10_OPERATE
PROCESS_NAME(sensor_nhzd10_process);

void post_NHZD10_calibration(void);
#endif
#define OPERATE_NHZD10 OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_NHZD10 DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#endif

