#ifndef __SENSOR_WATER_POWER_H__
#define __SENSOR_WATER_POWER_H__





#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "board_cfg.h"
#include "port_config.h"
#if WATER_OPERATE
PROCESS_NAME(sensor_water_power_process);
void post_water_calibration(void);
#endif
#define OPERATE_SENSOR_WATER   OPERATE_ADC;\
															 OPERATE_SENSOR_POWER
#define DIS_OPERATE_SENSOR_WATER DIS_OPERATE_ADC;\
																 DIS_OPERATE_SENSOR_POWER





#endif
