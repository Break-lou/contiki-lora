#ifndef __sensor_MODBUS_process__
#define __sensor_MODBUS_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if modbus_mode
PROCESS_NAME(sensor_modbus_process);
#endif
#define OPERATE_MODBUS OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_MODBUS DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART


#endif

