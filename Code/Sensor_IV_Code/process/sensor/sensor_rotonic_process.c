#include "sensor_rotonic_process.h"
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
#include "rotonic.h"

#define SENSOR_ROTONIC_TYPE 		  0x03
#define SENSOR_ROTONIC_DATA_TYPE	0x01
#define ROTONIC_DEFAULT_ADDR     0x01
#define ROTONIC_FAIL_MAX_NUM 3
#if ROTONIC_OPERATE

uint8_t battery_rotonic;
uint8_t rotonic_temp [7];
uint8_t sample_cnt;
uint8_t sample_fail_cnt1;
uint8_t receive_fail_cnt=0;
ROTONIC_status_t rotonic_statues = rotonic_status_idle;
struct etimer rotonic_process_etimer;
struct etimer rotonic_receive_timeout_etimer;
void rotonic_composite_format_data(void);
void waiting_power_rotonic(void);
void rotonic_sample_collect(void);
void rotonic_sample_event(void);
PROCESS(sensor_rotonic_process,"sensor_rotonic_process");
PROCESS_THREAD(sensor_rotonic_process,ev,data)
{
	PROCESS_BEGIN();
	rotonic_port_init();
	rotonic_param_init();
  rotonic_statues = rotonic_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();				
				if( ev == SENSOR_PROCESS_START)
				{					
					sample_cnt = 0;             				
					rotonic_port_init();
					battery_rotonic = battery_sample_data();		
					DCDC_SET(DCDC_3_3V);
					OPERATE_ROTONIC;
					rotonic_statues = rotonic_status_power_on;	
					waiting_power_rotonic();			
				}	
				else if( ev == PROCESS_EVENT_TIMER && data == &rotonic_process_etimer)
				{
					rotonic_sample_collect();
				}		
				else if( ev == PROCESS_EVENT_TIMER && data == &rotonic_receive_timeout_etimer)
				{
					if(receive_fail_cnt >= ROTONIC_FAIL_MAX_NUM)
					{				
							sensor_sixteen_buffer_put(SENSOR_ROTONIC_TYPE, 0xf3, node_parameter.MAC,
															rotonic_temp, 5, battery_rotonic, node_running_flags.sensor_sample_time);	
							rotonic_sample_event();
					}
					else
					{
							rotonic_sample_collect();
							receive_fail_cnt++;
					}
				}					
				else if (ev == PROCESS_RECEIVE_COMPLETE_EVENT)
				{			
						etimer_stop(&rotonic_receive_timeout_etimer);
						rotonic_parse_recv_data(rotonic_recv_buff);					    
						sample_cnt++;
						if( data_check(sample_cnt) )//|| node_running_flags.current_work_stage == CONFIG_PAYLOAD_STAGE)
						{
									sample_cnt=0;		
									DIS_OPERATE_ROTONIC;
									rotonic_composite_format_data();
									sensor_sixteen_buffer_put(SENSOR_ROTONIC_TYPE, SENSOR_ROTONIC_DATA_TYPE, node_parameter.MAC,
																				rotonic_temp, 5,battery_rotonic, node_running_flags.sensor_sample_time);
									rotonic_sample_event();
						}		
						else
						{
							rotonic_sample_collect();
						}
				}
		}				
	PROCESS_END();
}
void waiting_power_rotonic(void)
{
	if(rotonic_statues == rotonic_status_power_on)
	{
		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
		{
				etimer_set(&rotonic_process_etimer, node_parameter.SPTD ms);
		}else{
				etimer_set(&rotonic_process_etimer, 150 ms);
		}						
		
	}
	else
	{
		etimer_set(&rotonic_process_etimer, 100 ms);						//????
	}
	OPERATE_ROTONIC;
}
void rotonic_sample_collect(void)
{	
	OPERATE_ROTONIC;
	rotonic_port_init();
	rotonic_sample();
	rotonic_uart_enable_wake_event();
	rotonic_statues = rotonic_status_collect;
	etimer_set(&rotonic_receive_timeout_etimer, 500 ms);
}
void rotonic_composite_format_data(void)
{
	uint8_t i = 0;	
	memset(rotonic_temp,0x00,7);
	rotonic_temp[i++] = rotonic_temp_sign;
	rotonic_temp[i++] = (uint8_t)(rotonic_temp_integer);
	rotonic_temp[i++] = (uint8_t)(rotonic_temp_decimal);
	rotonic_temp[i++] = (uint8_t)(rotonic_humi_integer);
	rotonic_temp[i++] = (uint8_t)(rotonic_humi_decimal);
	rotonic_temp[i++] = 0;
	rotonic_temp[i++] = 0;
}
void rotonic_sample_event(void)
{
	receive_fail_cnt = 0;
	rotonic_statues = rotonic_status_end;
	DIS_OPERATE_ROTONIC;
	uart_rx_disable();		
	rotonic_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
#endif

