#include "sensor_aca826t_process.h"
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
#include "aca826t.h"
#include "modbus.h"
#include "crc.h"


#define SENSOR_ACA826T_TYPE 		0x03
#define SENSOR_ACA826T_DATA_TYPE	0x22
#define ACA826T_FAIL_MAX_NUM 3
#if ACA826T_OPERATE
//void send_aca826t_value(uint16_t aca826t_value);
void waiting_power_aca826t(void);
void aca826t_sample_event(void);
void aca826t_sample_collect(void);
uint8_t bcd_decimal(uint8_t bcd);
uint16_t  aca826t_x_data;			
uint16_t  aca826t_y_data;
uint32_t  aca826t_data;
struct etimer aca826t_power_wait_etimer;
struct etimer aca826t_receive_timeout_etimer;
uint8_t temp_aca826t_value[8];
uint8_t battery_aca826t;
uint8_t data_length;

uint8_t receive_aca826t_fail_cnt=0;

modbus_structure aca_modbus;
uint8_t array[20]={0x68,0x04,0x00,0x04,0x08};
typedef enum
{
	aca826t_status_init = 1,
	aca826t_status_power_on,
	aca826t_status_collect,
	aca826t_status_end,
	aca826t_status_calibrate
}aca826t_status_t;

static aca826t_status_t aca826t_work_status = aca826t_status_init;

PROCESS(sensor_aca826t_process,"sensor_aca826t_process");
PROCESS_THREAD(sensor_aca826t_process,ev,data)
{
	PROCESS_BEGIN();
	aca826t_port_init();
	aca826t_uart_init(uart_baudrate_9600);
	aca826t_work_status = aca826t_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					modbus_data_memcpy(&aca_modbus,array,5);
					aca_modbus.modbus_address_bit=3;
					aca_modbus.modbus_check_init_num=1;
					aca_modbus.modbus_check_style=modbus_check_style_sum;
					aca_modbus.modbus_check_style_value=0;
					aca_modbus.modbus_check_crc_init=0;
					aca_modbus.modbus_end_bit=0;
					aca_modbus.modbus_start_bit=1;
					aca_modbus.modbus_receive_len=17;
					aca_modbus.modbus_receive_data_check_len=15;
					aca_modbus.modbus_send_data_len=3;
					aca_modbus.modbus_send_len=5;
					aca_modbus.modbus_receive_data_len_bit=2;
					#if DEBUG_PRINT
						printf("aca826t sensor start power on... \n");
					#endif
					aca826t_port_init();
					battery_aca826t = battery_sample_data();
					aca826t_work_status = aca826t_status_power_on;
					open_aca826t_sensor_power();	//ACA826T??
					waiting_power_aca826t();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &aca826t_power_wait_etimer)
				{
					aca826t_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &aca826t_receive_timeout_etimer)
				{			
					if(receive_aca826t_fail_cnt >= ACA826T_FAIL_MAX_NUM)
					{						
							aca826t_sample_event();
					}
					else
					{
							aca826t_sample_collect();
							receive_aca826t_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						etimer_stop(&aca826t_receive_timeout_etimer);	
						DIS_OPERATE_ACA826T;
						ENABLE_LOW_POWER;						
						if(aca826t_work_status == aca826t_status_collect)//接收错误
						{				
									 
								aca826t_x_data = bcd_decimal(*(((uint8_t *)data)+4)&0x0f)*100+bcd_decimal(*(((uint8_t *)data)+5));	
								aca826t_y_data = bcd_decimal(*(((uint8_t *)data)+8)&0x0f)*100+bcd_decimal(*(((uint8_t *)data)+9));								
								if(aca826t_x_data >30 && aca826t_y_data >30 )
								{
										receive_aca826t_fail_cnt++;
										if(receive_aca826t_fail_cnt >= ACA826T_FAIL_MAX_NUM)
										{
											
											aca826t_sample_event();
										}else{
											aca826t_sample_collect();
										}
								 }
								 else
								 {
											
											receive_aca826t_fail_cnt = 0;
											aca826t_data=bcd_decimal(*(((uint8_t *)data)+6))*100+bcd_decimal(*(((uint8_t *)data)+7));
									 
											temp_aca826t_value[0] =  (*(((uint8_t *)data)+4)&0xf0)+(((*(((uint8_t *)data)+8)&0xf0)>>4)&0X0f);
											temp_aca826t_value[1] = aca826t_x_data;
											temp_aca826t_value[2] = aca826t_data&0xff;
											temp_aca826t_value[3] = (aca826t_data>>8)&0xff;
											aca826t_data=bcd_decimal(*(((uint8_t *)data)+10))*100+bcd_decimal(*(((uint8_t *)data)+11));
											temp_aca826t_value[4] = aca826t_y_data;
											temp_aca826t_value[5] = aca826t_data&0xff;
											temp_aca826t_value[6] = (aca826t_data>>8)&0xff;
											
											sensor_sixteen_buffer_put(SENSOR_ACA826T_TYPE, SENSOR_ACA826T_DATA_TYPE, node_parameter.MAC,
															temp_aca826t_value, 7, battery_aca826t, node_running_flags.sensor_sample_time);				 								 
											aca826t_sample_event();
									 }
							#if DEBUG_PRINT
								printf("aca826t value: %d\n", aca826t_data);
							#endif
							}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_aca826t(void)
{
	if(aca826t_work_status == aca826t_status_power_on)
	{
		
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&aca826t_power_wait_etimer, node_parameter.SPTD ms);		//????	
//		}else{
//				etimer_set(&aca826t_power_wait_etimer, 600 ms);		//????	
//		}		
//		
		OPERATE_ACA826T;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&aca826t_power_wait_etimer, 600 ms);						//????
	}
}

void aca826t_sample_collect(void)
{	
	OPERATE_ACA826T;
	ENABLE_LOW_POWER;//不断电
	aca826t_port_init();
	aca826t_sample_data();
	//modbus_send_data(&aca_modbus);
	aca826t_uart_enable_wake_event();
	aca826t_work_status = aca826t_status_collect;
	etimer_set(&aca826t_receive_timeout_etimer, 1000 ms);
}
void aca826t_sample_event(void)
{
	receive_aca826t_fail_cnt = 0;
	DIS_OPERATE_ACA826T;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	aca826t_work_status = aca826t_status_end;
	uart_rx_disable();		
	aca826t_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
uint8_t bcd_decimal(uint8_t bcd)
{
	return bcd-(bcd >> 4)*6;
}
#endif
