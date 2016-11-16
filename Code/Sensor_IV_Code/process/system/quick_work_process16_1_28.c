#include "quick_work_process.h"
#include "board_cfg.h"
#include "sensor_parameter.h"
#include "sensor_payload.h"
#include "delay.h"
#include "LED.h"

//static uint32_t quick_mode_time = 0x51713300;
//static uint16_t quick_mode_cycle_interval = 1;
//static uint16_t quick_mode_data_type = 0x0000;
//static uint8_t quick_mode_battery = 0x74;
//static uint8_t quick_mode_buff[16];


void create_hex_sensor_data(uint8_t *buff);

struct etimer quick_work_etimer;				//快速工作定时器
struct etimer quick_work_timeout_etimer;		//快速工作超时定时器


PROCESS(quick_work_process, "quick_work_process");
PROCESS_THREAD(quick_work_process, ev, data)
{
	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == SYSTEM_ENTER_QUICK_MODE)
		{
			etimer_set(&quick_work_etimer, 1 s);
		}
		if(ev == PROCESS_EVENT_TIMER && data == &quick_work_etimer)
		{
			if(node_running_flags.sensor_system_state == SYSTEM_STATE_QUCK_WORK)
			{
				etimer_reset(&quick_work_etimer);
				assamble_sensor_router_payload();
//				create_hex_sensor_data(quick_mode_buff);
//				assamble_quick_work_data_payload(quick_mode_buff);
				transmit();
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
			led_red_shining();
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

//void create_hex_sensor_data(uint8_t *buff)
//{
//	buff[0] = (uint8_t)(quick_mode_data_type>>8);
//	buff[1] = (uint8_t)(quick_mode_data_type);
//	buff[2] = (uint8_t)(node_parameter.MAC&0xff);
//	buff[3] = (uint8_t)(node_parameter.MAC>>8)&0xff;
//	buff[4] = (uint8_t)(quick_mode_time);
//	buff[5] = (uint8_t)(quick_mode_time>>8);
//	buff[6] = (uint8_t)(quick_mode_time>>16);
//	buff[7] = (uint8_t)(quick_mode_time>>24);
//	buff[8] = 0X7b;
//	buff[9] = 0X11;
//	buff[10] = 0X66;	
//	buff[11] = 0;	
//	buff[12] = 0;	
//	buff[13] = 0x00;	
//	buff[14] = 0x00;	
//	buff[15] = quick_mode_battery;
//	quick_mode_time += (quick_mode_cycle_interval<<2);
//}
