#include "sensor_ds18b20_process.h"
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
#include <stdio.h>
#include "ds18b20_include.h"


#define SENSOR_DS18B20_TYPE 		0x03
#define SENSOR_DS18B20_DATA_TYPE	0x03
#define DS18B20_FAIL_MAX_NUM 3 
#if DS18B20_OPERATE
//void send_ds18b20_value(uint16_t ds18b20_value);
void waiting_sample_ds18b20(void);
void ds18b20_sample_event(void);
void ds18b20_sample_collect(void);
uint16_t  ds18b20_data;
uint8_t flag_d9;							
struct etimer ds18b20_power_wait_etimer;
uint8_t temp_ds18b20_value[3];
uint8_t battery_ds18b20;


uint8_t dsbs18b20_receive_fail_cnt=0;


typedef enum
{
	ds18b20_status_init = 1,
	ds18b20_status_power_on,
	ds18b20_status_collect,
	ds18b20_status_end,
	ds18b20_status_calibrate
}ds18b20_status_t;

static ds18b20_status_t ds18b20_work_status = ds18b20_status_init;

PROCESS(sensor_ds18b20_process,"sensor_ds18b20_process");
PROCESS_THREAD(sensor_ds18b20_process,ev,data)
{
	uint8_t *data_point;
	PROCESS_BEGIN();
	ds18b20_work_status = ds18b20_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("ds18b20 sensor start power on... \n");
					#endif
					battery_ds18b20 = battery_sample_data();
					ds18b20_work_status = ds18b20_status_power_on;
					waiting_sample_ds18b20();
				} 
				if( ev == PROCESS_EVENT_TIMER && data == &ds18b20_power_wait_etimer)	
				{	
						ds18b20_sample_collect();
						if(ds18b20_work_status == ds18b20_status_collect)
						{				
								ds18b20_data=ds18b20_calc_temperature((uint8_t* )&ds18b20_data);
								flag_d9=((ds18b20_data&0x8000)>>15)&0x01;
								ds18b20_data&=0x7fff;						
								if(ds18b20_data >0x600)
								{
										dsbs18b20_receive_fail_cnt++;
										if(dsbs18b20_receive_fail_cnt >= DS18B20_FAIL_MAX_NUM)
										{
											sensor_sixteen_buffer_put(SENSOR_DS18B20_TYPE, 0xf4, node_parameter.MAC,
															temp_ds18b20_value, 3, battery_ds18b20, node_running_flags.sensor_sample_time);
											
											ds18b20_sample_event();
										}else{
											waiting_sample_ds18b20();
										}
								 }
								 else
								 {
											
											data_point=(uint8_t *)&ds18b20_data;
											dsbs18b20_receive_fail_cnt = 0;
											temp_ds18b20_value[0]=flag_d9;
											temp_ds18b20_value[1] = *data_point;
											temp_ds18b20_value[2] = *(data_point+1);
											sensor_sixteen_buffer_put(SENSOR_DS18B20_TYPE, SENSOR_DS18B20_DATA_TYPE, node_parameter.MAC,
															temp_ds18b20_value, 3, battery_ds18b20, node_running_flags.sensor_sample_time);
											ds18b20_sample_event();
								 }
							#if DEBUG_PRINT
								printf("ds18b20 value: %d\n", ds18b20_data);
							#endif
						}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_sample_ds18b20(void)
{
	if(ds18b20_work_status == ds18b20_status_power_on)
	{	
		OPERATE_DS18B20;
		ENABLE_LOW_POWER;
		DCDC_SET(DCDC_3_3V);
		ds18b20_initial_convert();	
		etimer_set(&ds18b20_power_wait_etimer, 800 ms);	
	}
	else
	{
		etimer_set(&ds18b20_power_wait_etimer, 100 ms);						//????
	}
}

void ds18b20_sample_collect(void)
{	
	if(defualt_ds18b20_read_temp())
	{	
		ds18b20_work_status = ds18b20_status_collect;
		DIS_OPERATE_DS18B20;
		ENABLE_LOW_POWER;//不断电
	}
	else
	{
		dsbs18b20_receive_fail_cnt++;
		if(dsbs18b20_receive_fail_cnt >= DS18B20_FAIL_MAX_NUM)
		{
			sensor_sixteen_buffer_put(SENSOR_DS18B20_TYPE, 0xf4, node_parameter.MAC,
							temp_ds18b20_value, 3, battery_ds18b20, node_running_flags.sensor_sample_time);
			
			ds18b20_sample_event();
		}else{
			process_post(&sensor_ds18b20_process,SENSOR_PROCESS_START,NULL);
		}
	
	}
}
void ds18b20_sample_event(void)
{
	dsbs18b20_receive_fail_cnt = 0;
	DIS_OPERATE_DS18B20;
	ds18b20_work_status = ds18b20_status_end;			
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
#endif
