#ifndef __SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE_PROCESS__
#define __SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE_PROCESS__
#include "contiki-conf.h"
#include "sys/process.h"
#if SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE
PROCESS_NAME(sthto_process);

void post_STHTO_calibration(void);
#endif

#define OPERATE_STHTO OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_STHTO DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#endif

