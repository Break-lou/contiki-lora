#ifndef __SENSOR_MANAGER_PROCESS_H__
#define __SENSOR_MANAGER_PROCESS_H__


#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "sensor_parameter.h"


#define SENSOR_PROCESSES(...)					\
struct process * const sensor_processes[] = {__VA_ARGS__, NULL}

PROCESS_NAME(sensor_manager_process);


void post_sensor_manager_ev(process_event_t ev);
void sensor_process_exit(void);





#endif
