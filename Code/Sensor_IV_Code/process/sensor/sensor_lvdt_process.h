#ifndef __sensor_LVDT_process__
#define __sensor_LVDT_process__
#include "contiki-conf.h"
#include "sys/process.h"

typedef enum
{
	lvdt_status_init = 1,
	lvdt_status_power_on,
	lvdt_status_collect,
	lvdt_status_end,
	lvdt_status_calibrate
}LVDT_status_t;
#define OPERATE_LVDT OPERATE_SENSOR_POWER;\
											 OPERATE_485;\
											 OPERATE_UART_OR_USART
#define DIS_OPERATE_LVDT DIS_OPERATE_SENSOR_POWER;\
													 DIS_OPERATE_485;\
													 DIS_OPERATE_UART_OR_USART
#if LVDT_OPERATE
PROCESS_NAME(sensor_lvdt_process);

void post_lvdt_calibration(void);

													 
#endif
#endif


