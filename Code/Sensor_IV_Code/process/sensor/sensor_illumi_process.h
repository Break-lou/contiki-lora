#ifndef __SENSOR_ILLUMI_PROCESS_H__
#define __SENSOR_ILLUMI_PROCESS_H__



#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "board_cfg.h"


#if ILLUMI_OPERATE
PROCESS_NAME(sensor_illumi_process);

void stop_sample_illumi_timeout(void);
#endif
#define OPERATE_ILLUMI OPERATE_DCDC0; \
											 OPERATE_UART_OR_USART	
#define DIS_OPERATE_ILLUMI DIS_OPERATE_DCDC0; \
													 DIS_OPERATE_UART_OR_USART

#endif
