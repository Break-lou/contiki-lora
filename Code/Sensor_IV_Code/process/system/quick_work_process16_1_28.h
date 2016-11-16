#ifndef __QUICK_WORK_PROCESS_H__
#define __QUICK_WORK_PROCESS_H__



#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"


PROCESS_NAME(quick_work_process);

void post_quick_work_ev(process_event_t ev);
void stop_quick_work_timer(void);
void stop_quick_work_timeout_timer(void);



#endif
