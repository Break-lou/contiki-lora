#ifndef __sensor_SKD_100D_process__
#define __sensor_SKD_100D_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if SKD_100D_OPERATE
PROCESS_NAME(sensor_skd_100d_process);

void post_skd_100d_calibration(void);
#endif
#define OPERATE_SKD_100D OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_SKD_100D DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
													 
#endif

