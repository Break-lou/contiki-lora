#include "sen_work_process.h"
//#include "sensor_sht25_process.h"
//#include "sensor_co2_process.h"
#include "cycle_work_process.h"
#include "sensor_payload.h"
#include "sys_event.h"
#include "board_cfg.h"
#include "sensor_parameter.h"
#include "sensor_manager_process.h"
#include "sensor_water_power.h"
#include "sensor_process_include.h"
//自检线程

struct etimer sen_work_etimer;				//自检定时器

PROCESS(sen_work_process, "sen_work_process");
PROCESS_THREAD(sen_work_process, ev, data)
{

	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == SYSTEM_ENTER_CHECK_MODE)
		{
			//开始自检
			if(node_parameter.SETP==S_5TM_TYPE)
			{
					etimer_set(&sen_work_etimer,10 s);			//设置发包周期
			}
			else if(node_parameter.SETP==MODBUS_TYPE)
			{
					etimer_set(&sen_work_etimer,5 s);	
			}
			else
			{				
					
					etimer_set(&sen_work_etimer,4*node_parameter.SPTD ms);			//设置发包周期
			}
		}
		if(ev == SYSTEM_LEAVE_CHECK_MODE)
		{
			//结束自检
			etimer_stop(&sen_work_etimer);
		}
		//----------
		if(ev == PROCESS_EVENT_TIMER && data == &sen_work_etimer)
		{
			//1秒定时到
			if(node_running_flags.sensor_system_state == SYSTEM_STATE_CONFIG)
			{
				etimer_reset(&sen_work_etimer);
				process_post(&sensor_manager_process,SENSOR_MANAGER_START,NULL );	
				
			}
			else
			{
				stop_sen_work_timer();
			}
		}
		if(ev == SYSTEM_CHECK_MODE_SAMPLE_END)
		{
			//开始发送
			assambel_sensor_sen_payload();
			transmit();
		}
	}
	
	PROCESS_END();

}

void post_sen_work_ev(process_event_t ev)
{
	process_post(&sen_work_process, ev, NULL);
}

void stop_sen_work_timer()
{
	etimer_stop(&sen_work_etimer);
}





