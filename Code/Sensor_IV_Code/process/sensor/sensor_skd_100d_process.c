#include "sensor_skd_100d_process.h"
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
#include "skd_100d.h"



#define SENSOR_SKD_100D_TYPE 		0x03
#define SENSOR_SKD_100D_DATA_TYPE	0x42
#define SKD_100D_FAIL_MAX_NUM 3

#if SKD_100D_OPERATE
//void send_skd_100d_value(uint16_t skd_100d_value);
extern uint8_t (*uart_recv_option)(uint8_t data);
extern uint8_t skd_100d_recv_buff[10];
void waiting_power_skd_100d(void);
void skd_100d_sample_event(void);
void skd_100d_sample_collect(void);
uint32_t  skd_100d_data,ext_skd_100d_data=0,delat_skd_100d_data;
int16_t evaporation;							
struct etimer skd_100d_power_wait_etimer;
struct etimer skd_100d_receive_timeout_etimer;
uint8_t temp_skd_100d_value[5];
uint8_t battery_skd_100d;
uint8_t receive_fail_cnt=0;


typedef enum
{
	skd_100d_status_init = 1,
	skd_100d_status_power_on,
	skd_100d_status_collect,
	skd_100d_status_end,
	skd_100d_status_calibrate
}skd_100d_status_t;

static skd_100d_status_t skd_100d_work_status = skd_100d_status_init;

PROCESS(sensor_skd_100d_process,"sensor_skd_100d_process");
PROCESS_THREAD(sensor_skd_100d_process,ev,data)
{
	PROCESS_BEGIN();
	skd_100d_port_init();
	skd_100d_uart_init(uart_baudrate_9600);
	skd_100d_work_status = skd_100d_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("skd_100d sensor start power on... \n");
					#endif
					skd_100d_port_init();
					battery_skd_100d = battery_sample_data();
					skd_100d_work_status = skd_100d_status_power_on;
					open_skd_100d_sensor_power();	//SKD_100D??
					waiting_power_skd_100d();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &skd_100d_power_wait_etimer)
				{
					skd_100d_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &skd_100d_receive_timeout_etimer)
				{			
					if(receive_fail_cnt >= SKD_100D_FAIL_MAX_NUM)
					{				
							sensor_sixteen_buffer_put(SENSOR_SKD_100D_TYPE, 0xf4, node_parameter.MAC,
															temp_skd_100d_value, 5, battery_skd_100d, node_running_flags.sensor_sample_time);	
							skd_100d_sample_event();
					}
					else
					{
							skd_100d_sample_collect();
							receive_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_SKD_100D;
						ENABLE_LOW_POWER;		//不断电
						etimer_stop(&skd_100d_receive_timeout_etimer);	
						if(skd_100d_data_out(&skd_100d_data))
						{
								if(ext_skd_100d_data == 0)
								{
									ext_skd_100d_data = skd_100d_data;
								}
								if(skd_100d_data < ext_skd_100d_data)
								{
									temp_skd_100d_value[0]=1;
									delat_skd_100d_data = ext_skd_100d_data - skd_100d_data;
								}
								else
								{
									temp_skd_100d_value[0]=0;
									delat_skd_100d_data = skd_100d_data-ext_skd_100d_data;
								}
								
								temp_skd_100d_value[1] = delat_skd_100d_data&0xff;
								temp_skd_100d_value[2] = (delat_skd_100d_data>>8)&0xff;
							
								temp_skd_100d_value[3] = (delat_skd_100d_data>>16)&0xff;
								temp_skd_100d_value[4] = (delat_skd_100d_data>>24)&0xff;
								ext_skd_100d_data = skd_100d_data;
							
								sensor_sixteen_buffer_put(SENSOR_SKD_100D_TYPE, SENSOR_SKD_100D_DATA_TYPE, node_parameter.MAC,
												temp_skd_100d_value, 5, battery_skd_100d, node_running_flags.sensor_sample_time);				 								 
								skd_100d_sample_event();
						}							
						else
						{				
																
								receive_fail_cnt++;
								if(receive_fail_cnt >= SKD_100D_FAIL_MAX_NUM)
								{
									sensor_sixteen_buffer_put(SENSOR_SKD_100D_TYPE, 0xf3, node_parameter.MAC,
													temp_skd_100d_value, 5, battery_skd_100d, node_running_flags.sensor_sample_time);	
									skd_100d_sample_event();
								}else{
									skd_100d_sample_collect();
								}
								
						}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_skd_100d(void)
{
	if(skd_100d_work_status == skd_100d_status_power_on)
	{
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&skd_100d_power_wait_etimer, node_parameter.SPTD ms);
//		}else{
//				etimer_set(&skd_100d_power_wait_etimer, 100 ms);
//		}		
				//????
		OPERATE_SKD_100D;
	}
	else
	{
		etimer_set(&skd_100d_power_wait_etimer, 100 ms);						//????
	}
}

void skd_100d_sample_collect(void)
{	
	OPERATE_SKD_100D;
	ENABLE_LOW_POWER;//不断电
	skd_100d_port_init();
	uart_recv_option=skd_100d_analyster;
	skd_100d_sample_data();
	skd_100d_uart_enable_wake_event();
	skd_100d_work_status = skd_100d_status_collect;
	etimer_set(&skd_100d_receive_timeout_etimer, 1000 ms);
}
//SKD_100D 3????????
void skd_100d_sample_event(void)
{
	receive_fail_cnt = 0;
	skd_100d_work_status = skd_100d_status_end;
	DIS_OPERATE_SKD_100D;
	uart_rx_disable();		
	skd_100d_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
#endif
