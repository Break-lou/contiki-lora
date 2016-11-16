#include "rf_receive_process.h"
#include "sys_event.h"
#include "sx127x_radio.h"
#include "sensor_payload.h"
#include "sensor_parameter.h"
#include "cycle_work_process.h"
#include "delay.h"
#include "led_process.h"
#include <stdio.h>


void triger_next_send(void);
struct etimer receive_etimer;		//周期工作


PROCESS(rf_receive_process, "rf_receive_process");
PROCESS_THREAD(rf_receive_process, ev, data)
{

	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == RF_RECEIVED_SENSOR_DATA){
			//接收到数据
			process_post(&led_process, LED_BLUE_ON_10MS_EV, NULL);
			
//			#if SENSOR_IV
//				LED_BLUE_ON;
//				delayXms(10);
//				LED_BLUE_OFF;
//			#elif BQ
//				LED_RED_ON;
//				delayXms(10);
//				LED_RED_OFF;
//			#endif
			
		}
	}
	
	PROCESS_END();

}








