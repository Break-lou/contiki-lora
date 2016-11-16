#include "sensor_sca126t_process.h"
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
#include "sca126t.h"



#define SENSOR_SCA126T_TYPE 		0x03
#define SENSOR_SCA126T_DATA_TYPE	0x22
#define SCA126T_FAIL_MAX_NUM 3
#if SCA126T_OPERATE
//void send_sca126t_value(uint16_t sca126t_value);
void waiting_power_sca126t(void);
void sca126t_sample_event(void);
void sca126t_sample_collect(void);
uint8_t bcd_decimal(uint8_t bcd);
void sca126t_calibrate_process(void);
uint16_t  sca126t_x_data;			
uint16_t  sca126t_y_data;
uint16_t  sca126t_data;
struct etimer sca126t_power_wait_etimer;
struct etimer sca126t_receive_timeout_etimer;
uint8_t temp_sca126t_value[8];
uint8_t battery_sca126t;

uint8_t data_null=0;
uint8_t receive_sca126t_fail_cnt=0;


typedef enum
{
	sca126t_status_init = 1,
	sca126t_status_power_on,
	sca126t_status_collect,
	sca126t_status_end,
	sca126t_status_calibrate
}sca126t_status_t;

static sca126t_status_t sca126t_work_status = sca126t_status_init;

PROCESS(sensor_sca126t_process,"sensor_sca126t_process");
PROCESS_THREAD(sensor_sca126t_process,ev,data)
{
	PROCESS_BEGIN();
	sca126t_port_init();
	sca126t_uart_init(uart_baudrate_9600);
	sca126t_work_status = sca126t_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("sca126t sensor start power on... \n");
					#endif
					sca126t_port_init();
					battery_sca126t = battery_sample_data();
					sca126t_work_status = sca126t_status_power_on;
					open_sca126t_sensor_power();	//SCA126T??
					waiting_power_sca126t();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &sca126t_power_wait_etimer)
				{
					
					
					if(sca126t_work_status == sca126t_status_power_on)
					{
						sca126t_sample_collect();
					}
					else if(sca126t_work_status == sca126t_status_calibrate)
					{
							sca126t_calibrate_process();
					}
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &sca126t_receive_timeout_etimer)
				{			
					if(receive_sca126t_fail_cnt >= SCA126T_FAIL_MAX_NUM)
					{						
							
							sca126t_sample_event();
							memcpy(&temp_sca126t_value,&data_null,7);
							sensor_sixteen_buffer_put(SENSOR_SCA126T_TYPE, 0xf3, node_parameter.MAC,
															temp_sca126t_value, 7, battery_sca126t, node_running_flags.sensor_sample_time);
					}
					else
					{
							if(sca126t_work_status == sca126t_status_collect)
							{
								sca126t_sample_collect();
							}
							else if(sca126t_work_status == sca126t_status_calibrate)
							{
									sca126t_calibrate_process();
							}
							receive_sca126t_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						etimer_stop(&sca126t_receive_timeout_etimer);
						DIS_OPERATE_SCA126T;
						ENABLE_LOW_POWER;		//不断电					
						if(sca126t_work_status == sca126t_status_collect)
						{		
								if((*(((uint8_t *)data)+24))==0X0D)
								{
									
									sca126t_x_data = bcd_decimal(*(((uint8_t *)data)+4)&0x0f)*10+bcd_decimal(*(((uint8_t *)data)+5)&0xf0)/10;//+bcd_decimal(*(((uint8_t *)data)+5));	
									sca126t_y_data = bcd_decimal(*(((uint8_t *)data)+7)&0x0f)*10+bcd_decimal(*(((uint8_t *)data)+8)&0xf0)/10;//bcd_decimal(*(((uint8_t *)data)+8));
								}
								else if((*(((uint8_t *)data)+24))==0X10)
								{
									sca126t_x_data = bcd_decimal(*(((uint8_t *)data)+4)&0x0f)*100+bcd_decimal(*(((uint8_t *)data)+5));	
									sca126t_y_data = bcd_decimal(*(((uint8_t *)data)+8)&0x0f)*100+bcd_decimal(*(((uint8_t *)data)+9));
								}
								if((((*(((uint8_t *)data)+24))==0X0D)&&(sca126t_x_data >30 || sca126t_y_data >30))|| 
									(((*(((uint8_t *)data)+24))==0X10)&&(sca126t_x_data >15 || sca126t_y_data >15)) )
								{
										receive_sca126t_fail_cnt++;
										if(receive_sca126t_fail_cnt >= SCA126T_FAIL_MAX_NUM)
										{
											sca126t_sample_event();
											sca126t_sample_event();
											memcpy(&temp_sca126t_value,&data_null,7);
											sensor_sixteen_buffer_put(SENSOR_SCA126T_TYPE, 0xf4, node_parameter.MAC,
																			temp_sca126t_value, 7, battery_sca126t, node_running_flags.sensor_sample_time);
										}else{
											sca126t_sample_collect();
										}
								}							
								else
								{	
										receive_sca126t_fail_cnt = 0;
										if((*(((uint8_t *)data)+24))==0X0D)
										{
											sca126t_data=bcd_decimal(*(((uint8_t *)data)+5)&0x0f)*1000+bcd_decimal(*(((uint8_t *)data)+6))*10;
											
											temp_sca126t_value[0] = (*(((uint8_t *)data)+4)&0xf0)+(((*(((uint8_t *)data)+7)&0xf0)>>4)&0X0f);
											temp_sca126t_value[1] = sca126t_x_data;
											temp_sca126t_value[2] = sca126t_data&0xff;
											temp_sca126t_value[3] = (sca126t_data>>8)&0xff;
											sca126t_data=bcd_decimal(*(((uint8_t *)data)+8)&0x0f)*1000+bcd_decimal(*(((uint8_t *)data)+9))*10;
											temp_sca126t_value[4] = sca126t_y_data;
											temp_sca126t_value[5] = sca126t_data&0xff;
											temp_sca126t_value[6] = (sca126t_data>>8)&0xff;									
										}
										else if((*(((uint8_t *)data)+24))==0X10)
										{
											sca126t_data=bcd_decimal(*(((uint8_t *)data)+6))*100+bcd_decimal(*(((uint8_t *)data)+7));
									 
											temp_sca126t_value[0] =  (*(((uint8_t *)data)+4)&0xf0)+(((*(((uint8_t *)data)+8)&0xf0)>>4)&0X0f);
											temp_sca126t_value[1] = sca126t_x_data;
											temp_sca126t_value[2] = sca126t_data&0xff;
											temp_sca126t_value[3] = (sca126t_data>>8)&0xff;
											sca126t_data=bcd_decimal(*(((uint8_t *)data)+10))*100+bcd_decimal(*(((uint8_t *)data)+11));
											temp_sca126t_value[4] = sca126t_y_data;
											temp_sca126t_value[5] = sca126t_data&0xff;
											temp_sca126t_value[6] = (sca126t_data>>8)&0xff;
										}
										sensor_sixteen_buffer_put(SENSOR_SCA126T_TYPE, SENSOR_SCA126T_DATA_TYPE, node_parameter.MAC,
															temp_sca126t_value, 7, battery_sca126t, node_running_flags.sensor_sample_time);				 								 
										sca126t_sample_event();
											
										#if DEBUG_PRINT
											printf("sca126t value: %d\n", sca126t_data);
										#endif
								}
						}	
						else if(sca126t_work_status == sca126t_status_calibrate)
						{
								if((*(((uint8_t *)data)+4))==0x00)
								{
										send_calibration_ack(true);
								}
								else if((*(((uint8_t *)data)+4))==0xFF)
								{
									send_calibration_ack(false);
								}
						}
				}	
				if(ev == SCA126T_CALIBRATION )  
				{
					sca126t_work_status = sca126t_status_calibrate;
					open_sca126t_sensor_power();	//SCA126T??
					OPERATE_SCA126T;
					ENABLE_LOW_POWER;//不断电
					etimer_set(&sca126t_power_wait_etimer,node_parameter.SPTD ms);		//??????
				}
	}		
	PROCESS_END();
}
void waiting_power_sca126t(void)
{
	if(sca126t_work_status == sca126t_status_power_on)
	{
		
		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
		{
				etimer_set(&sca126t_power_wait_etimer, node_parameter.SPTD ms);		//????	
		}else{
				etimer_set(&sca126t_power_wait_etimer, 600 ms);		//????	
		}		
		
		OPERATE_SCA126T;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&sca126t_power_wait_etimer, 600 ms);						//????
	}
}

void sca126t_sample_collect(void)
{	
	OPERATE_SCA126T;
	ENABLE_LOW_POWER;//不断电
	sca126t_port_init();
	sca126t_sample_data();
	sca126t_uart_enable_wake_event();
	sca126t_work_status = sca126t_status_collect;
	etimer_set(&sca126t_receive_timeout_etimer, 3 s);
}
void sca126t_calibrate_process(void)
{
	OPERATE_SCA126T;
	ENABLE_LOW_POWER;//不断电
	sca126t_port_init();
	set_sca126t_zero(0x01);
	sca126t_uart_enable_wake_event();
	etimer_set(&sca126t_receive_timeout_etimer, 3 s);
}
void sca126t_sample_event(void)
{
	receive_sca126t_fail_cnt = 0;
	DIS_OPERATE_SCA126T;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	sca126t_work_status = sca126t_status_end;	
	sca126t_uart_disable_wake_event();					 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
uint8_t bcd_decimal(uint8_t bcd)
{
	return bcd-(bcd >> 4)*6;
}
void post_sca126t_calibration(void)
{
	process_post(&sensor_sca126t_process,SCA126T_CALIBRATION,NULL);
}
#endif
