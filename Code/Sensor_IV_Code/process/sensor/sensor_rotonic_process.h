#ifndef __sensor_ROTONIC_process__
#define __sensor_ROTONIC_process__
#include "contiki-conf.h"
#include "sys/process.h"

typedef enum
{
	rotonic_status_init = 1,
	rotonic_status_power_on,
	rotonic_status_collect,
	rotonic_status_sample,
	rotonic_status_end,
  rotonic_status_idle
}ROTONIC_status_t;
#define OPERATE_ROTONIC OPERATE_UART_OR_USART;\
											  OPERATE_DCDC0

#define DIS_OPERATE_ROTONIC DIS_OPERATE_UART_OR_USART;\
													  DIS_OPERATE_DCDC0
#if ROTONIC_OPERATE
PROCESS_NAME(sensor_rotonic_process);

void rotonic_composite_format_data(void);

#endif
													 
#endif



