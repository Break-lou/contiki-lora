#ifndef __SEN_WORK_PROCESS_H__
#define __SEN_WORK_PROCESS_H__

#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"

PROCESS_NAME(sen_work_process);


void stop_sen_work_timer(void);
void post_sen_work_ev(process_event_t ev);
	
#endif
