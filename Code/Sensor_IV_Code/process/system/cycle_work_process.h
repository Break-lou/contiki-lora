#ifndef __CYCLE_WORK_H__
#define __CYCLE_WORK_H__
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "timestamp.h"


PROCESS_NAME(cycle_work_process);

void post_cycle_work_ev(process_event_t ev,process_data_t data);
void sensor_sample(void);
void stop_sample_cycle_timer(void);
clock_time_t get_sample_cycle_next_expired_time(void);
typedef struct time_t
{
		uint32_t clock;																//时间戳 	 可设置
		tm_new analay_clock;													//转换成年月日

}s_time;

#endif
