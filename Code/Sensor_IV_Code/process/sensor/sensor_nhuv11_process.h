#ifndef __sensor_NHUV11_process__
#define __sensor_NHUV11_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if NHUV11_OPERATE
PROCESS_NAME(sensor_nhuv11_process);

void post_NHUV11_calibration(void);
#endif
#define OPERATE_NHUV11 OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_NHUV11 DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#endif

