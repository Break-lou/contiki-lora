#include "sensor_co2_process.h"
#include "sht25.h"
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sensor_sixteen.h"
#include "battery.h"
#include "co2.h"
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


#define SENSOR_CO2_TYPE 		0x01
#define SENSOR_CO2_DATA_TYPE	0x00

//void send_co2_value(uint16_t co2_value);
void waiting_sample_co2(void);
void co2_sample_event(void);
void co2_sample_fail_event(void);

uint16_t  co2_data;							
struct etimer co2_sample_etimer;
uint8_t temp_co2_value[7];
uint8_t battery_co2;

#define CO2_FAIL_MAX_NUM 3
uint8_t sample_fail_cnt;


typedef enum
{
	co2_status_init = 1,
	co2_status_power_on,
	co2_status_collect,
	co2_status_end,
	co2_status_calibrate
}co2_status_t;

static co2_status_t co2_work_status = co2_status_init;

PROCESS(sensor_co2_process,"sensor_co2_process");
PROCESS_THREAD(sensor_co2_process,ev,data)
{
	PROCESS_BEGIN();
	//上电初始化
	co2_param_init();
	uart_rx_disable();
	DCDC_SET(DCDC_3_3V);
	open_sensor_power();
	delayXms(100);
	co2_work_status = co2_status_init;
	set_co2_mode2();
	close_sensor_power();
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if( ev == SENSOR_PROCESS_START)
		{
			//电量采集
			#if DEBUG_PRINT
				printf("co2 sensor start power on... \n");
			#endif
			battery_co2 = battery_sample_data();
			co2_work_status = co2_status_power_on;
			DCDC_SET(DCDC_3_3V);
			open_sensor_power();	//CO2上电
			
			waiting_sample_co2();
		}
		//定时器到
		if( ev == PROCESS_EVENT_TIMER && data == &co2_sample_etimer)
		{	
			DIS_OPERATE_CO2;
			DISABLE_LOW_POWER;
			if(co2_work_status == co2_status_power_on)
			{
				#if DEBUG_PRINT
					printf("begin sample CO2... \n");
				#endif				
			    co2_sample_event();
			}
			else if(co2_work_status == co2_status_collect)
			{
				co2_data = get_co2_data();
				if(co2_data == 0xFFFF)
				{
					//采集失败
					sample_fail_cnt++;
					if(sample_fail_cnt >= CO2_FAIL_MAX_NUM)
					{
						//3次采集失败
						co2_sample_fail_event();
					}else{
						//重新发送采集指令
						co2_sample_event();
					}
				}else{
					//采集成功
					sample_fail_cnt = 0;
					temp_co2_value[0] = 0x00;
					temp_co2_value[1] = 0x00;
					temp_co2_value[2] = 0x00;
					temp_co2_value[3] = co2_data&0xff;
					temp_co2_value[4] = (co2_data>>8)&0xff;
					sensor_sixteen_buffer_put(SENSOR_CO2_TYPE, SENSOR_CO2_DATA_TYPE, node_parameter.MAC,
									temp_co2_value, 5, battery_co2, node_running_flags.sensor_sample_time);
					co2_work_status = co2_status_end;	
					uart_rx_disable();
					close_sensor_power();							
					post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
				}
				#if DEBUG_PRINT
					printf("co2 value: %d\n", co2_data);
				#endif
			}	
            else if(co2_work_status == co2_status_calibrate)
			{
				uint8_t ret = check_calibration_result();
				if(ret)
				{
					//标定成功
					send_calibration_ack(true);
				}else{
					//标定失败
					send_calibration_ack(false);
				}
				co2_work_status = co2_status_end;	
			}			
		}
		//收到标定事件
		if(ev == CO2_CALIBRATION )  
		{
			co2_work_status = co2_status_calibrate;
			DCDC_SET(DCDC_3_3V);
			open_sensor_power();
			delayXms(2000);		//2s延时
			uart_rx_enable();
			co2_calibrate();	//发送标定指令
			etimer_set(&co2_sample_etimer,500 ms);		//读取数据延时
		}
		
	}	
	PROCESS_END();
}


void post_co2_calibration(void)
{
	process_post(&sensor_co2_process,CO2_CALIBRATION,NULL);
}

//CO2测试
//uint8_t co2_temp_buffer[10];
//void send_co2_value(uint16_t co2_value)
//{
//	uint8_t co2_value_len;
//	uint8_t co2_value_buff[4];
//	dec_to_ascii_in_order(co2_value, co2_value_buff, &co2_value_len);
//	
//	co2_temp_buffer[0] = 'C';
//	co2_temp_buffer[1] = 'O';
//	co2_temp_buffer[2] = '2';
//	co2_temp_buffer[3] = ':';
//	memcpy(co2_temp_buffer+4, co2_value_buff, co2_value_len);
//	co2_temp_buffer[4+co2_value_len] = '\r';
//	co2_temp_buffer[5+co2_value_len] = '\n';
//	
//	RadioDriver.SetTxPacket(co2_temp_buffer, co2_value_len + 6);			//	
//}


void waiting_sample_co2(void)
{
	if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
	{
		//正常工作
		etimer_set(&co2_sample_etimer, node_parameter.SPTD ms);		//上电时间
		OPERATE_CO2;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&co2_sample_etimer, 100 ms);						//上电时间
	}
}
//CO2采集事件
void co2_sample_event(void)
{
	uart_rx_enable();
	co2_sample_data();							//发送采集指令
	etimer_set(&co2_sample_etimer, 50 ms);		//读取数据延时
	co2_work_status = co2_status_collect;
}
//CO2 3次采集均失败事件
void co2_sample_fail_event(void)
{
	sample_fail_cnt = 0;
	co2_work_status = co2_status_end;
	//采集超时，关闭电源
	uart_rx_disable();			
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
}
