#include "sensor_nhzd10_process.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sensor_sixteen.h"
#include "battery.h"
#include "board_cfg.h"
#include "pmu_config.h"
#include "delay.h"
#include "sensor_parameter.h"
#include "data_conversion.h"
#include "sx127x_radio.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "AT_OPERATION.h"
#include "sensor_payload.h"
#include "power_manager.h"
#include "uart.h"
#include <stdio.h>
#include "nhzd10.h"

#define SENSOR_NHZD10_TYPE 		0x03
#define SENSOR_NHZD10_DATA_TYPE	0x05
#define NHZD10_FAIL_MAX_NUM 3
#if NHZD10_OPERATE
//void send_nhzd10_value(uint16_t nhzd10_value);
void waiting_power_nhzd10(void);
void nhzd10_sample_event(void);
void nhzd10_sample_collect(void);
uint32_t  nhzd10_data;						
struct etimer nhzd10_power_wait_etimer;
struct etimer nhzd10_receive_timeout_etimer;
uint8_t temp_nhzd10_value[3];
uint8_t battery_nhzd10;


uint8_t receive_nhzd10_fail_cnt=0;


typedef enum
{
	nhzd10_status_init = 1,
	nhzd10_status_power_on,
	nhzd10_status_collect,
	nhzd10_status_end,
	nhzd10_status_calibrate
}nhzd10_status_t;

static nhzd10_status_t nhzd10_work_status = nhzd10_status_init;

PROCESS(sensor_nhzd10_process,"sensor_nhzd10_process");
PROCESS_THREAD(sensor_nhzd10_process,ev,data)
{
	PROCESS_BEGIN();
	nhzd10_port_init();
	nhzd10_uart_init(uart_baudrate_9600);
	nhzd10_work_status = nhzd10_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("nhzd10 sensor start power on... \n");
					#endif
					nhzd10_port_init();
					battery_nhzd10 = battery_sample_data();
					nhzd10_work_status = nhzd10_status_power_on;
					open_nhzd10_sensor_power();	//NHZD10??
					waiting_power_nhzd10();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &nhzd10_power_wait_etimer)
				{
					nhzd10_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &nhzd10_receive_timeout_etimer)
				{			
					if(receive_nhzd10_fail_cnt >= NHZD10_FAIL_MAX_NUM)
					{											
							sensor_sixteen_buffer_put(SENSOR_NHZD10_TYPE, 0xf3, node_parameter.MAC,
															temp_nhzd10_value, 3, battery_nhzd10, node_running_flags.sensor_sample_time);	
							nhzd10_sample_event();
					}
					else
					{
							nhzd10_sample_collect();
							receive_nhzd10_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_NHZD10;
						ENABLE_LOW_POWER;		//不断电
						etimer_stop(&nhzd10_receive_timeout_etimer);	
						nhzd10_data = *(((uint8_t *)data)+6)+*(((uint8_t *)data)+5)*256+*(((uint8_t *)data)+4)*65536;					
						if(nhzd10_work_status == nhzd10_status_collect)//接收错误
						{				
																
								if(nhzd10_data == 0xFFFFFF&&nhzd10_data==0)
								{
										receive_nhzd10_fail_cnt++;
										if(receive_nhzd10_fail_cnt >= NHZD10_FAIL_MAX_NUM)
										{
											sensor_sixteen_buffer_put(SENSOR_NHZD10_TYPE, 0xf4, node_parameter.MAC,
															temp_nhzd10_value, 3, battery_nhzd10, node_running_flags.sensor_sample_time);	
											nhzd10_sample_event();
										}else{
											nhzd10_sample_collect();
										}
								 }
								 else
								 {
											
											receive_nhzd10_fail_cnt = 0;
											temp_nhzd10_value[0] = nhzd10_data&0xff;
											temp_nhzd10_value[1] = (nhzd10_data>>8)&0xff;
											temp_nhzd10_value[2] = (nhzd10_data>>16)&0xff;
											sensor_sixteen_buffer_put(SENSOR_NHZD10_TYPE, SENSOR_NHZD10_DATA_TYPE, node_parameter.MAC,
															temp_nhzd10_value, 3, battery_nhzd10, node_running_flags.sensor_sample_time);				 								 
											nhzd10_sample_event();
									 }
							#if DEBUG_PRINT
								printf("nhzd10 value: %d\n", nhzd10_data);
							#endif
							}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_nhzd10(void)
{
	if(nhzd10_work_status == nhzd10_status_power_on)
	{
		
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&nhzd10_power_wait_etimer, node_parameter.SPTD ms);		//????	
//		}else{
//				etimer_set(&nhzd10_power_wait_etimer, 100 ms);		//????	
//		}		
		
		OPERATE_NHZD10;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&nhzd10_power_wait_etimer, 100 ms);						//????
	}
}

void nhzd10_sample_collect(void)
{	
	OPERATE_NHZD10;
	ENABLE_LOW_POWER;//不断电
	nhzd10_port_init();
	nhzd10_sample_data();
	nhzd10_uart_enable_wake_event();
	nhzd10_work_status = nhzd10_status_collect;
	etimer_set(&nhzd10_receive_timeout_etimer, 1000 ms);
}
void nhzd10_sample_event(void)
{
	receive_nhzd10_fail_cnt = 0;
	DIS_OPERATE_NHZD10;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	nhzd10_work_status = nhzd10_status_end;
	uart_rx_disable();		
	nhzd10_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
#endif
