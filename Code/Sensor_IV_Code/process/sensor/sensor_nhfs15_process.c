#include "sensor_nhfs15_process.h"
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
#include "nhfs15.h"



#define SENSOR_NHFS15_TYPE 		0x03
#define SENSOR_NHFS15_DATA_TYPE	0x39
#define NHFS15_FAIL_MAX_NUM 3
#if NHFS15_OPERATE
//void send_nhfs15_value(uint16_t nhfs15_value);
void waiting_power_nhfs15(void);
void nhfs15_sample_event(void);
void nhfs15_sample_collect(void);
uint16_t  nhfs15_data;						
struct etimer nhfs15_power_wait_etimer;
struct etimer nhfs15_receive_timeout_etimer;
uint8_t temp_nhfs15_value[2];
uint8_t battery_nhfs15;


uint8_t receive_nhfs15_fail_cnt=0;


typedef enum
{
	nhfs15_status_init = 1,
	nhfs15_status_power_on,
	nhfs15_status_collect,
	nhfs15_status_end,
	nhfs15_status_calibrate
}nhfs15_status_t;

static nhfs15_status_t nhfs15_work_status = nhfs15_status_init;

PROCESS(sensor_nhfs15_process,"sensor_nhfs15_process");
PROCESS_THREAD(sensor_nhfs15_process,ev,data)
{
	PROCESS_BEGIN();
	nhfs15_port_init();
	nhfs15_uart_init(uart_baudrate_9600);
	nhfs15_work_status = nhfs15_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("nhfs15 sensor start power on... \n");
					#endif
					nhfs15_port_init();
					battery_nhfs15 = battery_sample_data();
					nhfs15_work_status = nhfs15_status_power_on;
					open_nhfs15_sensor_power();	//NHFS15??
					waiting_power_nhfs15();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &nhfs15_power_wait_etimer)
				{
					nhfs15_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &nhfs15_receive_timeout_etimer)
				{			
					if(receive_nhfs15_fail_cnt >= NHFS15_FAIL_MAX_NUM)
					{						
							sensor_sixteen_buffer_put(SENSOR_NHFS15_TYPE, 0xf3, node_parameter.MAC,
															temp_nhfs15_value, 2, battery_nhfs15, node_running_flags.sensor_sample_time);		
							nhfs15_sample_event();
					}
					else
					{
							nhfs15_sample_collect();
							receive_nhfs15_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_NHFS15;
						ENABLE_LOW_POWER;		//不断电
						etimer_stop(&nhfs15_receive_timeout_etimer);	
						nhfs15_data = *(((uint8_t *)data)+4)+*(((uint8_t *)data)+3)*256;					
						if(nhfs15_work_status == nhfs15_status_collect)//接收错误
						{				
																
								if(nhfs15_data == 0xFFFF&&nhfs15_data==0)
								{
										receive_nhfs15_fail_cnt++;
										if(receive_nhfs15_fail_cnt >= NHFS15_FAIL_MAX_NUM)
										{
											sensor_sixteen_buffer_put(SENSOR_NHFS15_TYPE, 0xf4, node_parameter.MAC,
															temp_nhfs15_value, 2, battery_nhfs15, node_running_flags.sensor_sample_time);		
											nhfs15_sample_event();
										}else{
											nhfs15_sample_collect();
										}
								 }
								 else
								 {
											
											receive_nhfs15_fail_cnt = 0;
											temp_nhfs15_value[0] = nhfs15_data&0xff;
											temp_nhfs15_value[1] = (nhfs15_data>>8)&0xff;
											sensor_sixteen_buffer_put(SENSOR_NHFS15_TYPE, SENSOR_NHFS15_DATA_TYPE, node_parameter.MAC,
															temp_nhfs15_value, 2, battery_nhfs15, node_running_flags.sensor_sample_time);				 								 
											nhfs15_sample_event();
									 }
							#if DEBUG_PRINT
								printf("nhfs15 value: %d\n", nhfs15_data);
							#endif
							}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_nhfs15(void)
{
	if(nhfs15_work_status == nhfs15_status_power_on)
	{
		
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&nhfs15_power_wait_etimer, node_parameter.SPTD ms);		//????	
//		}else{
//				etimer_set(&nhfs15_power_wait_etimer, 100 ms);		//????	
//		}		
		
		OPERATE_NHFS15;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&nhfs15_power_wait_etimer, 100 ms);						//????
	}
}

void nhfs15_sample_collect(void)
{	
	OPERATE_NHFS15;
	ENABLE_LOW_POWER;//不断电
	nhfs15_port_init();
	nhfs15_sample_data();
	nhfs15_uart_enable_wake_event();
	nhfs15_work_status = nhfs15_status_collect;
	etimer_set(&nhfs15_receive_timeout_etimer, 1000 ms);
}
void nhfs15_sample_event(void)
{
	receive_nhfs15_fail_cnt = 0;
	DIS_OPERATE_NHFS15;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	nhfs15_work_status = nhfs15_status_end;
	uart_rx_disable();		
	nhfs15_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
#endif
