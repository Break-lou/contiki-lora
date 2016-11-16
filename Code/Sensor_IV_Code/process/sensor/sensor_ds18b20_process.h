#ifndef __sensor_DS18B20_process__
#define __sensor_DS18B20_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if DS18B20_OPERATE
PROCESS_NAME(sensor_ds18b20_process);

void post_ds18b20_calibration(void);
#endif
#define OPERATE_DS18B20 OPERATE_DCDC0;\
												OPERATE_UART_OR_USART
#define DIS_OPERATE_DS18B20 DIS_OPERATE_DCDC0;\
													 DIS_OPERATE_UART_OR_USART
#endif

