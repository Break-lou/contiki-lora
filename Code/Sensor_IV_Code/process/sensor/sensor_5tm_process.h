#ifndef __sensor_5TM_process__
#define __sensor_5TM_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if S_5TM_OPERATE 
PROCESS_NAME(sensor_5tm_process);
void post_5tm_cfg(uint8_t *data);
void post_5tm_add(uint8_t *data);
void post_5tm_del(uint8_t *data);
void post_5tm_calibration(void);
#endif
#define OPERATE_5TM OPERATE_SENSOR_POWER;\
										OPERATE_UART_OR_USART
#define DIS_OPERATE_5TM DIS_OPERATE_SENSOR_POWER;\
											  DIS_OPERATE_UART_OR_USART


#endif

