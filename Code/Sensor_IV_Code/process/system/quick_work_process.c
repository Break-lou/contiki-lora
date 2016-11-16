#include "quick_work_process.h"
#include "board_cfg.h"
#include "sensor_parameter.h"
#include "sensor_payload.h"
#include "delay.h"
#include "LED.h"


void init_infos(void);

struct etimer quick_work_etimer;				//快速工作定时器
struct etimer quick_work_timeout_etimer;		//快速工作超时定时器

CInfo_t c_infos;

PROCESS(quick_work_process, "quick_work_process");
PROCESS_THREAD(quick_work_process, ev, data)
{
	PROCESS_BEGIN();
	
	init_infos();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == SYSTEM_ENTER_QUICK_MODE)
		{
			etimer_set(&quick_work_etimer, 2000 ms);
		}
		if(ev == PROCESS_EVENT_TIMER && data == &quick_work_etimer)
		{
			if(node_running_flags.sensor_system_state == SYSTEM_STATE_QUCK_WORK)
			{
				etimer_reset(&quick_work_etimer);
//				assamble_sensor_router_payload();				//旧版本通信测试
//				transmit();
				assamble_communication_test_payload();	//新版本通信测试	
				transmit();
				init_infos();
				etimer_set(&quick_work_timeout_etimer, node_parameter.RNRWT ms);
			}
			else
			{
				stop_quick_work_timer();
			}
		}
		if(ev == PROCESS_EVENT_TIMER && data == &quick_work_timeout_etimer)
		{
			//超时
			if(c_infos.g_num == 0)
			{
				led_red_shining();
			}
		}
	}
	
	PROCESS_END();
}


void post_quick_work_ev(process_event_t ev)
{
	process_post(&quick_work_process, ev, NULL);
}

void stop_quick_work_timer(void)
{
	etimer_stop(&quick_work_etimer);
}

void stop_quick_work_timeout_timer(void)
{
	etimer_stop(&quick_work_timeout_etimer);
}

void init_infos(void)
{
	c_infos.g_num = 0;
	int i=0;
	for(i=0; i<TEST_MAX_NUM; i++)
	{
		c_infos.c_info[i].g_mac = 0;
		c_infos.c_info[i].g_sensitivity = 0;
		c_infos.c_info[i].n_sensitivity = 0;
	}
}


