#ifndef __SENSOR_SHT25_PROCESS_H__
#define __SENSOR_SHT25_PROCESS_H__

#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "generic_include.h"
#include "board_cfg.h"


PROCESS_NAME(sensor_sht25_process);
#define OPERATE_SHT25 OPERATE_485
#define DIS_OPERATE_SHT25 DIS_OPERATE_485

#endif
