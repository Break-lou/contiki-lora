#ifndef __sensor_NHFS15_process__
#define __sensor_NHFS15_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if NHFS15_OPERATE
PROCESS_NAME(sensor_nhfs15_process);

void post_NHFS15_calibration(void);
#endif
#define OPERATE_NHFS15 OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_NHFS15 DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#endif

