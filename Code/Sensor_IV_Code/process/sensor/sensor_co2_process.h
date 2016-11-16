#ifndef __sensor_co2_process__
#define __sensor_co2_process__
#include "contiki-conf.h"
#include "sys/process.h"

PROCESS_NAME(sensor_co2_process);
#define OPERATE_CO2 OPERATE_UART_OR_USART;\
										OPERATE_SENSOR_POWER
#define DIS_OPERATE_CO2 DIS_OPERATE_UART_OR_USART;\
												DIS_OPERATE_SENSOR_POWER
void post_co2_calibration(void);

#endif
