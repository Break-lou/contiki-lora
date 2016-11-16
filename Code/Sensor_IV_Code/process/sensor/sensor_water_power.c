#include "sensor_water_power.h"
#include "water_power.h"
#include "power_manager.h"
#include "battery.h"
#include "sensor_parameter.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "sensor_sixteen.h"
#include <stdio.h>
#include "pmu_config.h"
#include "delay.h"
#include "port_config.h"
#include "sensor_payload.h"

#define SENSOR_WATER_TYPE 			  0x03
#define SENSOR_WATER_DATA_TYPE		0x27//39

#define OPEN_WATER_SENSOR_POWER			SI32_PBSTD_A_set_pins_push_pull_output(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN); \
										SI32_PBSTD_A_write_pins_low(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN);\
                    SI32_PBSTD_A_set_pins_push_pull_output( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN); \
							   		SI32_PBSTD_A_write_pins_high( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN)

#define CLOSE_WATER_SENSOR_POWER	  SI32_PBSTD_A_set_pins_push_pull_output(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN); \
										SI32_PBSTD_A_write_pins_high(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN); \
                    SI32_PBSTD_A_set_pins_push_pull_output( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN); \
										SI32_PBSTD_A_write_pins_low( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN)
#if WATER_OPERATE
typedef enum
{
	water_power_status_init = 1,
	water_power_status_power_on,
	water_power_status_collect,
	water_power_status_end,
	water_power_status_calibrate
}water_power_status_t;

static water_power_status_t water_power_work_status = water_power_status_init;

uint8_t water_battery;
uint16_t water_value;
uint32_t water_value_sum=0;
uint8_t water_temp[4];
struct etimer water_power_sample_etimer;
float power;
int16_t water_cal_value=0;
void water_sample_end_event(void);
void waiting_sample_water_power(void);

PROCESS(sensor_water_power_process,"sensor_water_power_process");
PROCESS_THREAD(sensor_water_power_process,ev,data)
{
	uint8_t i;
	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if( ev == SENSOR_PROCESS_START)
		{
			OPEN_WATER_SENSOR_POWER;
			water_power_work_status = water_power_status_power_on;	
			waiting_sample_water_power();
			water_battery = battery_sample_data();	//????
			water_cal_value=node_parameter.WVC;			
		}
		if( ev == PROCESS_EVENT_TIMER && data == &water_power_sample_etimer )
		{				
			water_param_init();
			water_value = water_sample_data();			//water_power_data
			power = water_value /4096.0 *3.6;
			
			water_value = water_sample_data();			//water_power_data
			water_value+=water_cal_value;
			if(water_power_work_status == water_power_status_power_on)
			{
				
				water_temp[0] = water_value&0xff;
				water_temp[1] = (water_value>>8)&0xff;
				water_temp[2] = 0x0a;
				water_temp[3] = 0;
				#if DEBUG_PRINT
					printf("begin sample water power, water_power_data = %x\n", water_value);
				#endif
				//CLOSE_WATER_SENSOR_POWER;
				if(power<0.3)
				{
					sensor_sixteen_buffer_put(SENSOR_WATER_TYPE, 0xf4, node_parameter.MAC,
										water_temp, 4, water_battery, node_running_flags.sensor_sample_time);
				}
				else
				{
					sensor_sixteen_buffer_put(SENSOR_WATER_TYPE, SENSOR_WATER_DATA_TYPE, node_parameter.MAC,
										water_temp, 4, water_battery, node_running_flags.sensor_sample_time);
				}
				water_sample_end_event();
				DIS_OPERATE_SENSOR_WATER;	
				ENABLE_LOW_POWER;
					#if DEBUG_PRINT
					printf("end sample  water power \n");
				#endif
			}
			else if(water_power_work_status == water_power_status_calibrate)
			{
				for(i=0;i<32;i++)
				{
					water_value_sum += water_sample_data();
				}
				water_value_sum/=32;
				water_cal_value=(int16_t)(455-water_value_sum);
				node_parameter.WVC=water_cal_value;
				update_sysparam();//´æÈëflash
				if((water_value_sum+node_parameter.WVC)==455)
				{
					send_calibration_ack(true);
				}
				else
				{
					send_calibration_ack(false);
				}
				water_value_sum=0;
				water_power_work_status = water_power_status_end;
			}
		}
		if(ev == WATER_CALIBRATION )  
		{
			water_power_work_status = water_power_status_calibrate;
			OPEN_WATER_SENSOR_POWER;
			OPERATE_SENSOR_WATER;
			ENABLE_LOW_POWER;
			etimer_set(&water_power_sample_etimer,node_parameter.SPTD ms);		//??????
		}
	}
	PROCESS_END();
	
}
void post_water_calibration(void)
{
	process_post(&sensor_water_power_process,WATER_CALIBRATION,NULL);
}

void water_sample_end_event(void)
{
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
void waiting_sample_water_power(void)
{
//	if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
//	{
		//????
		etimer_set(&water_power_sample_etimer, node_parameter.SPTD ms);		//????
		OPERATE_SENSOR_WATER;
		ENABLE_LOW_POWER;
//	}
//	else
//	{
//		etimer_set(&water_power_sample_etimer, 100 ms);						//????
//	}
}
#endif


