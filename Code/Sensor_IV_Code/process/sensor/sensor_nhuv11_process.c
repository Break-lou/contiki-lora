#include "sensor_nhuv11_process.h"
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
#include "nhuv11.h"

#define SENSOR_NHUV11_TYPE 		0x03
#define SENSOR_NHUV11_DATA_TYPE	0x3f
#define NHUV11_FAIL_MAX_NUM 3
#if NHUV11_OPERATE
//void send_nhuv11_value(uint16_t nhuv11_value);
void waiting_power_nhuv11(void);
void nhuv11_sample_event(void);
void nhuv11_sample_collect(void);
uint32_t  nhuv11_data;						
struct etimer nhuv11_power_wait_etimer;
struct etimer nhuv11_receive_timeout_etimer;
uint8_t temp_nhuv11_value[3];
uint8_t battery_nhuv11;


uint8_t receive_nhuv11_fail_cnt=0;


typedef enum
{
	nhuv11_status_init = 1,
	nhuv11_status_power_on,
	nhuv11_status_collect,
	nhuv11_status_end,
	nhuv11_status_calibrate
}nhuv11_status_t;

static nhuv11_status_t nhuv11_work_status = nhuv11_status_init;

PROCESS(sensor_nhuv11_process,"sensor_nhuv11_process");
PROCESS_THREAD(sensor_nhuv11_process,ev,data)
{
	PROCESS_BEGIN();
	nhuv11_port_init();
	nhuv11_uart_init(uart_baudrate_9600);
	nhuv11_work_status = nhuv11_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("nhuv11 sensor start power on... \n");
					#endif
					nhuv11_port_init();
					battery_nhuv11 = battery_sample_data();
					nhuv11_work_status = nhuv11_status_power_on;
					open_nhuv11_sensor_power();	//NHUV11??
					waiting_power_nhuv11();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &nhuv11_power_wait_etimer)
				{
					nhuv11_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &nhuv11_receive_timeout_etimer)
				{			
					if(receive_nhuv11_fail_cnt >= NHUV11_FAIL_MAX_NUM)
					{											
							sensor_sixteen_buffer_put(SENSOR_NHUV11_TYPE, 0xf3, node_parameter.MAC,
															temp_nhuv11_value, 3, battery_nhuv11, node_running_flags.sensor_sample_time);	
							nhuv11_sample_event();
					}
					else
					{
							nhuv11_sample_collect();
							receive_nhuv11_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_NHUV11;
						ENABLE_LOW_POWER;		//不断电
						etimer_stop(&nhuv11_receive_timeout_etimer);	
						nhuv11_data = *(((uint8_t *)data)+4)+*(((uint8_t *)data)+3)*256;					
						if(nhuv11_work_status == nhuv11_status_collect)//接收错误
						{				
																
								if(nhuv11_data == 0xFFFF)
								{
										receive_nhuv11_fail_cnt++;
										if(receive_nhuv11_fail_cnt >= NHUV11_FAIL_MAX_NUM)
										{
											sensor_sixteen_buffer_put(SENSOR_NHUV11_TYPE, 0xf4, node_parameter.MAC,
															temp_nhuv11_value, 3, battery_nhuv11, node_running_flags.sensor_sample_time);	
											nhuv11_sample_event();
										}else{
											nhuv11_sample_collect();
										}
								 }
								 else
								 {
											
											receive_nhuv11_fail_cnt = 0;
											temp_nhuv11_value[0] = nhuv11_data&0xff; 
											temp_nhuv11_value[1] = (nhuv11_data>>8)&0xff;
											sensor_sixteen_buffer_put(SENSOR_NHUV11_TYPE, SENSOR_NHUV11_DATA_TYPE, node_parameter.MAC,
															temp_nhuv11_value, 2, battery_nhuv11, node_running_flags.sensor_sample_time);				 								 
											nhuv11_sample_event();
									 }
							#if DEBUG_PRINT
								printf("nhuv11 value: %d\n", nhuv11_data);
							#endif
							}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_nhuv11(void)
{
	if(nhuv11_work_status == nhuv11_status_power_on)
	{
		
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&nhuv11_power_wait_etimer, node_parameter.SPTD ms);		//????	
//		}else{
//				etimer_set(&nhuv11_power_wait_etimer, 100 ms);		//????	
//		}		
		
		OPERATE_NHUV11;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&nhuv11_power_wait_etimer, 100 ms);						//????
	}
}

void nhuv11_sample_collect(void)
{	
	OPERATE_NHUV11;
	ENABLE_LOW_POWER;//不断电
	nhuv11_port_init();
	nhuv11_sample_data();
	nhuv11_uart_enable_wake_event();
	nhuv11_work_status = nhuv11_status_collect;
	etimer_set(&nhuv11_receive_timeout_etimer, 1000 ms);
}
void nhuv11_sample_event(void)
{
	receive_nhuv11_fail_cnt = 0;
	DIS_OPERATE_NHUV11;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	nhuv11_work_status = nhuv11_status_end;
	uart_rx_disable();		
	nhuv11_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
#endif
