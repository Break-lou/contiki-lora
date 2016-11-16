#include "sensor_soil_moisture_process.h"
#include "soil_moisture.h"
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
#include "led.h"

#define SENSOR_SOIL_MOISTURE_TYPE 			  0x03
#define SENSOR_SOIL_MOISTURE_DATA_TYPE		0x35
//5V
#define OPEN_SOIL_MOISTURE_SENSOR_POWER			DCDC_SET(DCDC_3_3V);\
                    SI32_PBSTD_A_set_pins_push_pull_output(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN); \
										SI32_PBSTD_A_write_pins_low(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN);\
                    SI32_PBSTD_A_set_pins_push_pull_output( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN); \
							   		SI32_PBSTD_A_write_pins_high( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN)

#define CLOSE_SOIL_MOISTURE_SENSOR_POWER	  DCDC0_off( );\
                    SI32_PBSTD_A_set_pins_push_pull_output(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN); \
										SI32_PBSTD_A_write_pins_high(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN); \
                    SI32_PBSTD_A_set_pins_push_pull_output( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN); \
										SI32_PBSTD_A_write_pins_low( WATER_POWER_EN_PORT,  WATER_POWER_EN_PIN)
#if SOIL_OPERATE
typedef enum
{
	soil_moisture_status_init = 1,
	soil_moisture_status_power_on,
	soil_moisture_status_collect,
	soil_moisture_status_end,
	soil_moisture_status_calibrate
}soil_moisture_status_t;

static soil_moisture_status_t soil_moisture_work_status = soil_moisture_status_init;

uint8_t soil_moisture_battery;
uint16_t soil_moisture_value;
uint8_t soil_moisture_temp[2];
struct etimer soil_moisture_sample_etimer;
float soil_moisture_power;
void soil_moisture_sample_end_event(void);
void waiting_sample_soil_moisture(void);

PROCESS(sensor_soil_moisture_process,"sensor_soil_moisture_process");
PROCESS_THREAD(sensor_soil_moisture_process,ev,data)
{
	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if( ev == SENSOR_PROCESS_START)
		{
			led_blue_on();
			soil_moisture_battery = battery_sample_data();	
			OPEN_SOIL_MOISTURE_SENSOR_POWER;
			waiting_sample_soil_moisture();		
			soil_moisture_work_status = soil_moisture_status_power_on;	
		}
		if( ev == PROCESS_EVENT_TIMER && data == &soil_moisture_sample_etimer)
		{	
			//delay_Xus(50000);
			led_blue_off();		
			soil_moisture_param_init();
			soil_moisture_value = soil_moisture_sample_data();			//soil_moisture_data
			soil_moisture_power = soil_moisture_value /4096.0 *3.6*25;
			soil_moisture_value = soil_moisture_sample_data();			//soil_moisture_data
			soil_moisture_temp[0] = soil_moisture_value&0xff;
			soil_moisture_temp[1] = (soil_moisture_value>>8)&0xff;
			#if DEBUG_PRINT
				printf("begin sample soil_moisture power, soil_moisture_data = %x\n", soil_moisture_value);
			#endif
			DIS_OPERATE_SENSOR_WATER;
			ENABLE_LOW_POWER;
			CLOSE_SOIL_MOISTURE_SENSOR_POWER;

			sensor_sixteen_buffer_put(SENSOR_SOIL_MOISTURE_TYPE, SENSOR_SOIL_MOISTURE_DATA_TYPE, node_parameter.MAC,
									soil_moisture_temp, 2, soil_moisture_battery, node_running_flags.sensor_sample_time);
			soil_moisture_sample_end_event();
			
				#if DEBUG_PRINT
				printf("end sample  soil_moisture power \n");
			#endif
		}
	}
	PROCESS_END();
	
}


void soil_moisture_sample_end_event(void)
{
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
void waiting_sample_soil_moisture(void)
{
//	if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
//	{
		//????
		etimer_set(&soil_moisture_sample_etimer, node_parameter.SPTD ms);		//????
		OPERATE_SENSOR_WATER;
		ENABLE_LOW_POWER;
//	}
//	else
//	{
//		etimer_set(&soil_moisture_sample_etimer, 100 ms);						//????
//	}
}
#endif


