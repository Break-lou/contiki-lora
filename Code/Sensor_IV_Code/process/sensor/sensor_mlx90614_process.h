#ifndef __sensor_MLX90614_process__
#define __sensor_MLX90614_process__
#include "contiki-conf.h"
#include "sys/process.h"
#if MLX90614_OPERATE
PROCESS_NAME(sensor_mlx90614_process);

void post_mlx90614_calibration(void);
#endif
 
#define OPERATE_MLX90614 OPERATE_DCDC0;\
												OPERATE_UART_OR_USART
#define DIS_OPERATE_MLX90614 DIS_OPERATE_DCDC0;\
													 DIS_OPERATE_UART_OR_USART											 
																								 
#endif

