#include "sensor_nhzf42_process.h"
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
#include "nhzf42.h"



#define SENSOR_NHZF42_TYPE 		0x03
#define SENSOR_NHZF42_DATA_TYPE	0x3a
#define NHZF42_FAIL_MAX_NUM 3

#if NHZF42_OPERATE
//void send_nhzf42_value(uint16_t nhzf42_value);
extern uint8_t (*uart_recv_option)(uint8_t data);
void waiting_power_nhzf42(void);
void nhzf42_sample_event(void);
void nhzf42_sample_collect(void);
uint16_t  nhzf42_data,nhzf42_data_ext=100;
int16_t evaporation;							
struct etimer nhzf42_power_wait_etimer;
struct etimer nhzf42_receive_timeout_etimer;
uint8_t temp_nhzf42_value[4];
uint8_t battery_nhzf42;


uint8_t receive_fail_cnt=0;


typedef enum
{
	nhzf42_status_init = 1,
	nhzf42_status_power_on,
	nhzf42_status_collect,
	nhzf42_status_end,
	nhzf42_status_calibrate
}nhzf42_status_t;

static nhzf42_status_t nhzf42_work_status = nhzf42_status_init;

PROCESS(sensor_nhzf42_process,"sensor_nhzf42_process");
PROCESS_THREAD(sensor_nhzf42_process,ev,data)
{
	uint8_t *data_point;
	PROCESS_BEGIN();
	nhzf42_port_init();
	nhzf42_uart_init(uart_baudrate_9600);
	nhzf42_work_status = nhzf42_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("nhzf42 sensor start power on... \n");
					#endif
					nhzf42_port_init();
					battery_nhzf42 = battery_sample_data();
					nhzf42_work_status = nhzf42_status_power_on;
					open_nhzf42_sensor_power();	//NHZF42??
					waiting_power_nhzf42();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &nhzf42_power_wait_etimer)
				{
					nhzf42_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &nhzf42_receive_timeout_etimer)
				{			
					if(receive_fail_cnt >= NHZF42_FAIL_MAX_NUM)
					{				
							sensor_sixteen_buffer_put(SENSOR_NHZF42_TYPE, 0xf3, node_parameter.MAC,
															temp_nhzf42_value, 4, battery_nhzf42, node_running_flags.sensor_sample_time);	
							nhzf42_sample_event();
					}
					else
					{
							nhzf42_sample_collect();
							receive_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_NHZF42;
						ENABLE_LOW_POWER;		//不断电
						etimer_stop(&nhzf42_receive_timeout_etimer);	
						nhzf42_data = *(((uint8_t *)data)+4)+*(((uint8_t *)data)+3)*256;					
						if(nhzf42_work_status == nhzf42_status_collect)
						{				
																
								if(nhzf42_data == 0xFFFF&&nhzf42_data==0)
								{
										receive_fail_cnt++;
										if(receive_fail_cnt >= NHZF42_FAIL_MAX_NUM)
										{
											sensor_sixteen_buffer_put(SENSOR_NHZF42_TYPE, 0xf4, node_parameter.MAC,
															temp_nhzf42_value, 4, battery_nhzf42, node_running_flags.sensor_sample_time);	
											nhzf42_sample_event();
										}else{
											nhzf42_sample_collect();
										}
								 }
								 else
								 {
											
											evaporation=nhzf42_data_ext-nhzf42_data+32768;
											nhzf42_data_ext=nhzf42_data;
											data_point=(uint8_t *)&evaporation;
											receive_fail_cnt = 0;
											temp_nhzf42_value[0] = *data_point;
											temp_nhzf42_value[1] = *(data_point+1);
											data_point=(uint8_t *)&nhzf42_data;
											temp_nhzf42_value[2] = *data_point;
											temp_nhzf42_value[3] = *(data_point+1);
											sensor_sixteen_buffer_put(SENSOR_NHZF42_TYPE, SENSOR_NHZF42_DATA_TYPE, node_parameter.MAC,
															temp_nhzf42_value, 4, battery_nhzf42, node_running_flags.sensor_sample_time);				 
											//close_nhzf42_sensor_power();	
											//ENABLE_LOW_POWER;									 
											nhzf42_sample_event();
									 }
							#if DEBUG_PRINT
								printf("nhzf42 value: %d\n", nhzf42_data);
							#endif
							}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_nhzf42(void)
{
	if(nhzf42_work_status == nhzf42_status_power_on)
	{
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&nhzf42_power_wait_etimer, node_parameter.SPTD ms);
//		}else{
//				etimer_set(&nhzf42_power_wait_etimer, 100 ms);
//		}		
				//????
		OPERATE_NHZF42;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&nhzf42_power_wait_etimer, 100 ms);						//????
	}
}

void nhzf42_sample_collect(void)
{	
	OPERATE_NHZF42;
	ENABLE_LOW_POWER;//不断电
	nhzf42_port_init();
	uart_recv_option=nhzf42_analyster;
	nhzf42_sample_data();
	nhzf42_uart_enable_wake_event();
	nhzf42_work_status = nhzf42_status_collect;
	etimer_set(&nhzf42_receive_timeout_etimer, 1000 ms);
}
//NHZF42 3????????
void nhzf42_sample_event(void)
{
	receive_fail_cnt = 0;
	nhzf42_work_status = nhzf42_status_end;
	DIS_OPERATE_NHZF42;
	uart_rx_disable();		
	nhzf42_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
#endif
