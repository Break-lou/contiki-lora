#include "key_process.h"
#include "led_process.h"
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "generic_include.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "sensor_parameter.h"
#include "power_manager.h"

//按键线程

uint8_t key_cnt=0;
struct etimer key_etimer;

PROCESS(key_process, "key_process");
PROCESS_THREAD(key_process,ev,data)
{
	PROCESS_BEGIN();
	while(1)
	{
		PROCESS_WAIT_EVENT_UNTIL( ev == KEY_PRESS_EVENT );	
		pinwake_disable();
		//循环检测按键
		do{
			etimer_set(&key_etimer,211 ms);
			PROCESS_WAIT_EVENT_UNTIL((ev ==  PROCESS_EVENT_TIMER)&&(data == &key_etimer));
			
			key_cnt++;
			if(key_cnt == 10)
            {
                //2秒后广播一个2S事件
				DISABLE_LOW_POWER;
                process_post(PROCESS_BROADCAST, KEY_PRESS_2S, NULL); 	//
            }
		}while(get_button_status());
		etimer_stop(&key_etimer);
		
		if(node_running_flags.sensor_system_state == SYSTEM_STATE_CLOSE)
		{
            //关机状态
			if(key_cnt>=30)
			{
                //快速工作模式
				node_running_flags.sensor_system_state = SYSTEM_STATE_QUCK_WORK;
				process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_QUCK_WORK,NULL);
			}
			else if(key_cnt>=20)
			{
                //配置模式
				node_running_flags.sensor_system_state = SYSTEM_STATE_CONFIG;
				process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_CONFIG,NULL);
			}
			else if(key_cnt>=10)
			{
                //正常工作模式
				node_running_flags.sensor_system_state = SYSTEM_STATE_WORK;
				process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_WORK,NULL);
			}
	    }
		else
		{
            //非关机状态下
            if(key_cnt>=10)
            {
               //关机
               node_running_flags.sensor_system_state = SYSTEM_STATE_CLOSE;
               process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_CLOSE,NULL);
            }
		}
		key_cnt = 0;		
		pinwake_enable();		
	}	
	PROCESS_END();
}

