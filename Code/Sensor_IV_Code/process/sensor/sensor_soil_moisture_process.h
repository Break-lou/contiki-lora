#ifndef __SENSOR_SOIL_MOISTURE_POWER_H__
#define __SENSOR_SOIL_MOISTURE_POWER_H__


#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "board_cfg.h"
#include "port_config.h"
#if SOIL_OPERATE
PROCESS_NAME(sensor_soil_moisture_process);
#endif
#define OPERATE_SENSOR_SOIL_MOISTURE   OPERATE_ADC; \
																			 OPERATE_SENSOR_POWER
																			 
#define DIS_OPERATE_SENSOR_SOIL_MOISTURE DIS_OPERATE_ADC; \
																				 DIS_OPERATE_SENSOR_POWER
																				 





#endif
