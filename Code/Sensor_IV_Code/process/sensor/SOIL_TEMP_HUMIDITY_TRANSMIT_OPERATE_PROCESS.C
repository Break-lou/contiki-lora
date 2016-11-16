#include "SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE_PROCESS.h"
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

#include "modbus.h"
#include "crc.h"


#define SENSOR_STHTO_TYPE 		0x03
#define SENSOR_STHTO_DATA_TYPE	0x3c
#define STHTO_FAIL_MAX_NUM 3
#if SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE
//void send_sthto_value(uint16_t sthto_value);
void waiting_power_sthto(void);
void sthto_sample_event(void);
void sthto_sample_collect(void);
uint8_t bcd_decimal(uint8_t bcd);
 uint16_t  sthto_temp_data;			
uint16_t  sthto_humidity_data;
uint32_t  sthto_data;
struct etimer sthto_power_wait_etimer;
struct etimer sthto_receive_timeout_etimer;
uint8_t temp_sthto_value[8];
uint8_t battery_sthto;
uint8_t data_length;

uint8_t receive_sthto_fail_cnt=0;

modbus_structure sthto_modbus;
uint8_t array[20]={0x01,0x03,0x00,0x00,0x00,0X02,0XC4,0X0B};
typedef enum
{
	sthto_status_init = 1,
	sthto_status_power_on,
	sthto_status_collect,
	sthto_status_end,
	sthto_status_calibrate
}sthto_status_t;

static sthto_status_t sthto_work_status = sthto_status_init;
//(1-(D9*2))*(D10+D11*256)/10;
//(D12+D13*256)/10;
PROCESS(sthto_process,"sthto_process");
PROCESS_THREAD(sthto_process,ev,data)
{
	PROCESS_BEGIN();
	modbus_port_init();
	modbus_uart_init(uart_baudrate_9600);
	sthto_work_status = sthto_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT(); 
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					//modbus_data_memcpy(&sthto_modbus,array,8);
					sthto_modbus.modbus_address_bit=1;
					sthto_modbus.modbus_check_init_num=0;
					sthto_modbus.modbus_check_style=modbus_check_style_crc;
					sthto_modbus.modbus_check_style_value=crc_rtu_default;
					sthto_modbus.modbus_check_crc_init=0xffff;
					sthto_modbus.modbus_end_bit=0;
					sthto_modbus.modbus_start_bit=0;
					sthto_modbus.modbus_receive_len=9;
					sthto_modbus.modbus_receive_data_check_len=7;
					sthto_modbus.modbus_send_data_len=6;
					sthto_modbus.modbus_send_len=8;
					//sthto_modbus.modbus_receive_data_len_bit=3;
					
					#if DEBUG_PRINT
						printf("sthto sensor start power on... \n");
					#endif
					modbus_port_init();
					battery_sthto = battery_sample_data();
					sthto_work_status = sthto_status_power_on;
					SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, 0x08);
					SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3,0x08);
					waiting_power_sthto();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &sthto_power_wait_etimer)
				{
					sthto_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &sthto_receive_timeout_etimer)
				{			
					if(receive_sthto_fail_cnt >= STHTO_FAIL_MAX_NUM)
					{						
							sensor_sixteen_buffer_put(SENSOR_STHTO_TYPE, 0xf3, node_parameter.MAC,
																temp_sthto_value, 5, battery_sthto, node_running_flags.sensor_sample_time);	
							sthto_sample_event();
					}
					else
					{
							sthto_sample_collect();
							receive_sthto_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						etimer_stop(&sthto_receive_timeout_etimer);	
						DIS_OPERATE_STHTO;
						ENABLE_LOW_POWER;						
						if(sthto_work_status == sthto_status_collect)//接收错误
						{				
									 
									sthto_temp_data = bcd_decimal(*(((uint8_t *)data)+4)&0x0f)*100+bcd_decimal(*(((uint8_t *)data)+5));	
									sthto_humidity_data = bcd_decimal(*(((uint8_t *)data)+8)&0x0f)*100+bcd_decimal(*(((uint8_t *)data)+9));			
									if(sthto_modbus.modbus_receive_array[3]>0x80)
									{
										temp_sthto_value[0]=1;
										sthto_temp_data=sthto_modbus.modbus_receive_array[3]*256+sthto_modbus.modbus_receive_array[4];
										sthto_temp_data=0xffff-sthto_temp_data+1;
									}
									else
									{
										temp_sthto_value[0]=0;
										sthto_temp_data=sthto_modbus.modbus_receive_array[3]*256+sthto_modbus.modbus_receive_array[4];
									}
									sthto_humidity_data=sthto_modbus.modbus_receive_array[5]*256+sthto_modbus.modbus_receive_array[6];
									if(sthto_temp_data >100 && sthto_humidity_data >100 )
									{
											receive_sthto_fail_cnt++;
											if(receive_sthto_fail_cnt >= STHTO_FAIL_MAX_NUM)
											{
												sensor_sixteen_buffer_put(SENSOR_STHTO_TYPE, 0xf4, node_parameter.MAC,
																temp_sthto_value, 5, battery_sthto, node_running_flags.sensor_sample_time);	
												sthto_sample_event();
											}else{
												sthto_sample_collect();
											}
									 }
									 else
									 {
												
												receive_sthto_fail_cnt = 0;
												temp_sthto_value[1] = sthto_temp_data%256;
												temp_sthto_value[2] = sthto_temp_data/256;
												temp_sthto_value[3] = sthto_humidity_data%256;
												temp_sthto_value[4] = sthto_humidity_data/256;
												
												sensor_sixteen_buffer_put(SENSOR_STHTO_TYPE, SENSOR_STHTO_DATA_TYPE, node_parameter.MAC,
																temp_sthto_value, 5, battery_sthto, node_running_flags.sensor_sample_time);				 								 
												sthto_sample_event();
										}
							#if DEBUG_PRINT
								printf("sthto value: %d\n", sthto_data);
							#endif
							}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_sthto(void)
{
	if(sthto_work_status == sthto_status_power_on)
	{
		
		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
		{
				etimer_set(&sthto_power_wait_etimer, node_parameter.SPTD ms);		//????	
		}else{
				etimer_set(&sthto_power_wait_etimer, 600 ms);		//????	
		}		
		
		OPERATE_STHTO;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&sthto_power_wait_etimer, 600 ms);						//????
	}
}

void sthto_sample_collect(void)
{	
	OPERATE_STHTO;
	ENABLE_LOW_POWER;//不断电
	modbus_port_init();
	modbus_send_data(&sthto_modbus);
	modbus_uart_enable_wake_event();
	sthto_work_status = sthto_status_collect;
	//etimer_set(&sthto_receive_timeout_etimer, 1000 ms);
}
void sthto_sample_event(void)
{
	receive_sthto_fail_cnt = 0;
	DIS_OPERATE_STHTO;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	sthto_work_status = sthto_status_end;
	uart_rx_disable();		
	modbus_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
uint8_t bcd_decimal(uint8_t bcd)
{
	return bcd-(bcd >> 4)*6;
}
#endif
