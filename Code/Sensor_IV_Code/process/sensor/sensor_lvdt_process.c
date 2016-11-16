#include "sensor_lvdt_process.h"
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
#include "lvdt.h"
#include <stdio.h>


#define SENSOR_LVDT_TYPE 		  0x03
#define SENSOR_LVDT_DATA_TYPE	0x28
#define LVDT_DEFAULT_ADDR     0x01
#define LVDT_FAIL_MAX_NUM 3
#if LVDT_OPERATE
uint8_t battery_lvdt;
uint8_t lvdt_temp[4];

uint8_t receive_fail_cnt=0;
LVDT_status_t lvdt_statue;
struct etimer lvdt_process_etimer;
struct etimer lvdt_receive_timeout_etimer;
void waiting_power_lvdt(void);
void lvdt_sample_collect(void);
void lvdt_sample_event(void);
PROCESS(sensor_lvdt_process,"sensor_lvdt_process");
PROCESS_THREAD(sensor_lvdt_process,ev,data)
{
	PROCESS_BEGIN();
	lvdt_port_init();
  lvdt_uart_init(uart_baudrate_9600);
	lvdt_statue = lvdt_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();				
				if( ev == SENSOR_PROCESS_START)//??
				{
					lvdt_port_init();
					battery_lvdt = battery_sample_data();				
					open_lvdt_power();
					lvdt_statue =  lvdt_status_power_on; 	
					waiting_power_lvdt();	
					        				
				}		
        if( ev == PROCESS_EVENT_TIMER && data == &lvdt_process_etimer)
				{
					lvdt_sample_collect();
				}		
				if( ev == PROCESS_EVENT_TIMER && data == &lvdt_receive_timeout_etimer)
				{			
					if(receive_fail_cnt >= LVDT_FAIL_MAX_NUM)
					{				
							sensor_sixteen_buffer_put(SENSOR_LVDT_TYPE, 0xf3, node_parameter.MAC,
															lvdt_temp, 4, battery_lvdt, node_running_flags.sensor_sample_time);	
							lvdt_sample_event();
					}
					else
					{
							lvdt_sample_collect();
							receive_fail_cnt++;
					}
				}	
				if (ev == PROCESS_RECEIVE_COMPLETE_EVENT)
				{					 
					  etimer_stop(&lvdt_receive_timeout_etimer);
						DIS_OPERATE_LVDT;	
						if(lvdt_statue == lvdt_status_collect)
						{	
							
							memcpy(lvdt_temp,&lvdt_recv_buff[3],4);
							sensor_sixteen_buffer_put(SENSOR_LVDT_TYPE, SENSOR_LVDT_DATA_TYPE, node_parameter.MAC,
																		lvdt_temp, 4,battery_lvdt, node_running_flags.sensor_sample_time);							
							lvdt_sample_event();
							
						}						
				}
				
	}		
	PROCESS_END();
}
void waiting_power_lvdt(void)
{
	if(lvdt_statue == lvdt_status_power_on)
	{
		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
		{
				etimer_set(&lvdt_process_etimer, node_parameter.SPTD ms);
		}else{
				etimer_set(&lvdt_process_etimer, 150 ms);
		}						
		
	}
	else
	{
		etimer_set(&lvdt_process_etimer, 100 ms);						//????
	}
	OPERATE_LVDT;
}
void lvdt_sample_collect(void)
{	
	OPERATE_LVDT;
	lvdt_port_init();
	
	lvdt_read_distance_value(LVDT_DEFAULT_ADDR);
	lvdt_uart_enable_wake_event();
	lvdt_statue = lvdt_status_collect;
	etimer_set(&lvdt_receive_timeout_etimer, 500 ms);
}
void lvdt_sample_event(void)
{
	receive_fail_cnt = 0;
	lvdt_statue = lvdt_status_end;
	DIS_OPERATE_NHZF42;
	uart_rx_disable();		
	lvdt_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
#endif

