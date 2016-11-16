#include "sensor_mlx90614_process.h"
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
#include "mlx90614.h"



#define SENSOR_MLX90614_TYPE 		0x03
#define SENSOR_MLX90614_DATA_TYPE	0x41
#define MLX90614_FAIL_MAX_NUM 3

#if MLX90614_OPERATE
#define temp_ta 0x06
#define temp_t1 0x07
#define temp_t2 0x08
//void send_mlx90614_value(uint16_t mlx90614_value);
extern uint8_t (*uart_recv_option)(uint8_t data);
void waiting_power_mlx90614(void);
void mlx90614_sample_event(void);
void mlx90614_sample_collect(void);
uint16_t  mlx90614_data,mlx90614_data_ext=100;
int16_t evaporation;							
struct etimer mlx90614_power_wait_etimer;
struct etimer mlx90614_receive_timeout_etimer;
uint8_t temp_ta_mlx90614_value[6];
uint8_t temp_t1_mlx90614_value[6];
uint8_t temp_t2_mlx90614_value[6];
uint8_t temp_mlx90614_value[4];
uint8_t battery_mlx90614;
uint8_t receive_fail_cnt=0;
float temp_taa,temp_t11,temp_t22;
uint16_t atemp_ta,atemp_t1,atemp_t2;

typedef enum
{
	mlx90614_status_init = 1,
	mlx90614_status_power_on,
	mlx90614_status_collect,
	mlx90614_status_end,
	mlx90614_status_calibrate
}mlx90614_status_t;

static mlx90614_status_t mlx90614_work_status = mlx90614_status_init;

PROCESS(sensor_mlx90614_process,"sensor_mlx90614_process");
PROCESS_THREAD(sensor_mlx90614_process,ev,data)
{
	PROCESS_BEGIN();
	mlx90614_init_config();
	mlx90614_work_status = mlx90614_status_init;
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("mlx90614 sensor start power on... \n");
					#endif
					battery_mlx90614 = battery_sample_data();
					mlx90614_work_status = mlx90614_status_power_on;
					DCDC_SET(DCDC_3_3V);
					mlx90614_trigger_temp_measure();
					OPERATE_MLX90614;
					waiting_power_mlx90614();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &mlx90614_power_wait_etimer)
				{
					mlx90614_sample_collect();
				}
				//超时重新发送
				if( ev == PROCESS_EVENT_TIMER && data == &mlx90614_receive_timeout_etimer)
				{			
					if(receive_fail_cnt >= MLX90614_FAIL_MAX_NUM)
					{				
							sensor_sixteen_buffer_put(SENSOR_MLX90614_TYPE, 0xf4, node_parameter.MAC,
															temp_ta_mlx90614_value, 4, battery_mlx90614, node_running_flags.sensor_sample_time);	
							mlx90614_sample_event();
					}
					else
					{
							mlx90614_sample_collect();
							receive_fail_cnt++;
					}
				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_MLX90614;
						etimer_stop(&mlx90614_receive_timeout_etimer);	
						if((temp_t1_mlx90614_value[4]&0x80) == 0x80)									
						{
								receive_fail_cnt++;
								if(receive_fail_cnt >= MLX90614_FAIL_MAX_NUM)
								{
									sensor_sixteen_buffer_put(SENSOR_MLX90614_TYPE, 0xf3, node_parameter.MAC,
													temp_mlx90614_value, 4, battery_mlx90614, node_running_flags.sensor_sample_time);	
									mlx90614_sample_event();
								}else{
									process_post(&sensor_mlx90614_process,SENSOR_PROCESS_START,NULL);					
								}
						 }
						 else
						 {
									temp_mlx90614_value[0] = temp_t1_mlx90614_value[3];
									temp_mlx90614_value[1] = temp_t1_mlx90614_value[4];
							 
									temp_mlx90614_value[2] = temp_ta_mlx90614_value[3];
									temp_mlx90614_value[3] = temp_ta_mlx90614_value[4];
									sensor_sixteen_buffer_put(SENSOR_MLX90614_TYPE, SENSOR_MLX90614_DATA_TYPE, node_parameter.MAC,
													temp_mlx90614_value, 4, battery_mlx90614, node_running_flags.sensor_sample_time);				 
									//close_mlx90614_sensor_power();	
									//ENABLE_LOW_POWER;									 
									mlx90614_sample_event();
						 }
							#if DEBUG_PRINT
								printf("mlx90614 value: %d\n", mlx90614_data);
							#endif
				}	
				
	}		
	PROCESS_END();
}
void waiting_power_mlx90614(void)
{
	if(mlx90614_work_status == mlx90614_status_power_on)
	{
		etimer_set(&mlx90614_power_wait_etimer,1500 ms);
	}
	else
	{
		etimer_set(&mlx90614_power_wait_etimer, 100 ms);						//????
	}
}

void mlx90614_sample_collect(void)
{	
	OPERATE_MLX90614;
	ENABLE_LOW_POWER;//不断电
	if(mlx90614_sample_temp(temp_ta,temp_ta_mlx90614_value))
	{
		if((temp_ta_mlx90614_value[4]&0x80) == 0x80)
		{
			goto collect_error;
		}
		atemp_ta=temp_ta_mlx90614_value[3]+temp_ta_mlx90614_value[4]*256;
		temp_taa=((float)(atemp_ta*0.02))-273.15;
	}
	else 
	{
		goto collect_error;
	}
	if(mlx90614_sample_temp(temp_t1,temp_t1_mlx90614_value))
	{
		atemp_t1=temp_t1_mlx90614_value[3]+temp_t1_mlx90614_value[4]*256;
		temp_t11=((float)(atemp_t1*0.02))-273.15;
	}
	else 
	{
		goto collect_error;
	}
//	if(mlx90614_sample_temp(temp_t2,temp_t2_mlx90614_value))
//	{
//		atemp_t2=temp_t2_mlx90614_value[3]+temp_t2_mlx90614_value[4]*256;
//		temp_t22=((float)(atemp_t2*0.02))-273.15;
//	}	
//	else 
//	{
//		goto collect_error;
//	}
	mlx90614_work_status = mlx90614_status_collect;
	process_post(&sensor_mlx90614_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
	return;
	
	collect_error:
	process_post(&sensor_mlx90614_process,PROCESS_EVENT_TIMER,&mlx90614_receive_timeout_etimer);
	return;
}
//MLX90614 3????????
void mlx90614_sample_event(void)
{
	receive_fail_cnt = 0;
	mlx90614_work_status = mlx90614_status_end;
	DIS_OPERATE_MLX90614;
	uart_rx_disable();		
									 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
#endif
