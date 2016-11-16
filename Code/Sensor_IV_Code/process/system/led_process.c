#include "led_process.h"
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "generic_include.h"
#include "sensor_parameter.h"
#include "system_process_include.h"

//LED线程

#define LED_BLUE_ON_TIME	50
#define LED_RED_ON_TIME		50

extern  uint16_t key_cnt;
uint8_t led_cnt=0;
uint8_t turn_to_close_flag=0;

struct etimer led_etimer;
struct etimer led_blue_etimer;
struct etimer led_red_etimer;
PROCESS(led_process, "led_process");

PROCESS_THREAD(led_process,ev,data)
{
	PROCESS_BEGIN();
	led_start();
	while(1)
	{
		PROCESS_WAIT_EVENT();

		if(node_running_flags.sensor_system_state == SYSTEM_STATE_CLOSE)
		{
			//关机态
			if(ev ==  CHANGE_SYSTEM_STATE_TO_CLOSE)
			{
				//关机状态
				led_off();
				turn_to_close_flag = 0;
				etimer_stop(&led_etimer);	
			}
			if(ev == KEY_PRESS_2S)
			{
				//按键保持2s事件
				etimer_set(&led_etimer,87 ms);
			}
			//led_etimer定时到
			if(ev == PROCESS_EVENT_TIMER && data == &led_etimer )
			{
				led_cnt++;
				if(led_cnt >= 100) 
				{
					led_cnt = 70;
				}
				led_off();
				etimer_reset(&led_etimer);
				
			    if(key_cnt>=30)
				{
					if(led_cnt%2 == 0 )
					{
						led_blue_on();
						led_green_on();
					}
					else if(led_cnt%2 == 1 )
					{
						led_blue_off();
						led_green_off();
					}
				}
				else if(key_cnt>=20)
				{
					if(led_cnt%2 == 0)
					{
						led_red_on();
					}
					else if( led_cnt%2 == 1)
					{
						led_red_off();
					}
				}
				else if(key_cnt>= 10)
				{
					if(led_cnt%2 == 0)
					{
						led_blue_on();
					}
					else if(led_cnt%2 == 1)
					{
						led_blue_off();
					}
				}
				else
				{
					etimer_stop(&led_etimer);
				}
			}
		}
		else if(node_running_flags.sensor_system_state != SYSTEM_STATE_CLOSE)
		{		
			//非关机态
			if(ev == KEY_PRESS_2S)
			{
				//按键保持2s
				led_off();
				etimer_set(&led_etimer,100 ms);
				turn_to_close_flag = 1;
				led_cnt = 0;
			}
			else if( ev== CHANGE_SYSTEM_STATE_TO_WORK)
			{
				//工作
				led_off();
				led_cnt = 0;
				etimer_set(&led_etimer,50 ms);
			}
			else if( ev== CHANGE_SYSTEM_STATE_TO_CONFIG)
			{
				//配置
				led_off();
				led_cnt = 0;
				etimer_set(&led_etimer,0.4 s);
			}
			else if( ev== CHANGE_SYSTEM_STATE_TO_QUCK_WORK)
			{
				//快速工作
				led_off();
				led_cnt = 0;
				etimer_stop(&led_etimer);
			}
			else if(ev == PROCESS_EVENT_TIMER && data == &led_etimer )
			{
				//led_etimer定时到
				if( turn_to_close_flag == 1)
				{
					led_cnt++;
					etimer_reset(&led_etimer);
					if(led_cnt%2 == 0)
					{
						led_green_on();
					}
					else if(led_cnt%2 == 1)
					{
						led_green_off();
					}
			    }
				else if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
				{
					//工作
					led_off();
					led_cnt++;
					if(led_cnt>=4)
					{
						etimer_stop(&led_etimer);
					}
					else
					{
						//轮流运行led
						etimer_reset(&led_etimer);
						if(led_cnt%3 == 1 )
						{
							led_red_on();
						}else if(led_cnt%3 == 2 )
						{
							led_blue_on();
						}else if(led_cnt%3 == 0 )
						{
							led_green_on();
						}
					}						 
				 }
				 else if(node_running_flags.sensor_system_state == SYSTEM_STATE_CONFIG)
				 {
					 //配置模式
					 led_off();
					 led_cnt++;	
					 etimer_reset(&led_etimer);
					 if(led_cnt%3 == 1 )
					 {
						 led_red_on();
					 }
					 else if(led_cnt%3 == 2 )
					 {
						 led_blue_on();
					 } 
					 else if(led_cnt%3 == 0 )
					 {
						 led_green_on();
					 }											 
				 }
				 
				 
				 
			}
			
			
		}		
	}
	PROCESS_END();
}

void stop_led_etimer(void)
{
	etimer_stop(&led_etimer);
}

