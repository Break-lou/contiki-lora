#ifndef __POWER_MANAGER_PROCESS_H__
#define __POWER_MANAGER_PROCESS_H__


#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"





PROCESS_NAME(power_manager_process);

void post_power_manager_ev(process_event_t ev);



#endif
