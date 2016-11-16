#include "sensor_modbus_process.h"
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
#include "modbus.h"
#include <stdio.h>
#if modbus_mode
#define SENSOR_MODBUS_TYPE 		0x03
//60--王滨温湿度，63--紫外
uint8_t SENSOR_MODBUS_DATA_TYPE=60;//
#define MODBUS_FAIL_MAX_NUM 3

//void send_modbus_value(uint16_t modbus_value);
void waiting_power_modbus(void);
void modbus_sample_event(void);
void modbus_sample_collect(void);
uint32_t  modbus_data;						
struct etimer modbus_power_wait_etimer;
struct etimer modbus_receive_timeout_etimer;
struct etimer modbus_receive_etimer;
uint8_t modbus_value[15];
uint8_t battery_modbus;
extern modbus_structure sensor_modbus;

uint8_t receive_modbus_fail_cnt=0;


typedef enum
{
	modbus_status_init = 1,
	modbus_status_power_on,
	modbus_status_collect,
	modbus_status_end,
	modbus_status_calibrate
}modbus_status_t;

static modbus_status_t modbus_work_status = modbus_status_init;

PROCESS(sensor_modbus_process,"sensor_modbus_process");
PROCESS_THREAD(sensor_modbus_process,ev,data)
{
	PROCESS_BEGIN();
	modbus_uart_init(uart_baudrate_9600);
	modbus_work_status = modbus_status_init;
	modbus_init(&sensor_modbus);
	while(1)
	{
				PROCESS_WAIT_EVENT();
				
				if( ev == SENSOR_PROCESS_START)//上电
				{
					//????
					#if DEBUG_PRINT
						printf("modbus sensor start power on... \n");
					#endif
					modbus_port_init();
					
					battery_modbus = battery_sample_data();
					modbus_work_status = modbus_status_power_on;
					open_modbus_sensor_power();	//MODBUS??
					waiting_power_modbus();
				}
				//????
				if( ev == PROCESS_EVENT_TIMER && data == &modbus_power_wait_etimer)
				{
					modbus_sample_collect();
				}
				//超时重新发送
				if(ev == PROCESS_EVENT_TIMER && data == &modbus_receive_timeout_etimer)
				{			
					etimer_stop(&modbus_receive_etimer);
					if(receive_modbus_fail_cnt >= MODBUS_FAIL_MAX_NUM)
					{											
							sensor_sixteen_buffer_put(SENSOR_MODBUS_TYPE, 0xf4, node_parameter.MAC,
															modbus_value, sensor_modbus.modbus_receive_data_len_num, battery_modbus, node_running_flags.sensor_sample_time);	
							modbus_sample_event();

					}
					else
					{
							modbus_sample_collect();
							receive_modbus_fail_cnt++;
					}
				}
				if(ev == PROCESS_EVENT_TIMER && data == &modbus_receive_etimer)
				{	
					uart_rx_disable();//关闭串口接受
					SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
					SI32_UART_B_flush_rx_fifo(SI32_UART_0);	
					
					etimer_stop(&modbus_receive_timeout_etimer);//停止接收超时
					//定位数据长度
					sensor_modbus.modbus_receive_data_len_num=sensor_modbus.modbus_receive_array[sensor_modbus.modbus_receive_data_len_locat-1];
					//校验码检测
					if(modbus_receive_check(&sensor_modbus)==1)
					{
						process_post(&sensor_modbus_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
					}
					else
					{
						process_post(&sensor_modbus_process,PROCESS_EVENT_TIMER,&modbus_receive_timeout_etimer);
						//etimer_set(&modbus_receive_timeout_etimer, 200 ms);
					}
				}
//				if(ev == PROCESS_CHECK_EVENT)
//				{
//					etimer_stop(&modbus_receive_timeout_etimer);
//					sensor_modbus.modbus_receive_data_len_num=sensor_modbus.modbus_receive_array[sensor_modbus.modbus_receive_data_len_locat-1];
//					if(modbus_receive_check(&sensor_modbus)==1)
//					{
//						process_post(&sensor_modbus_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
//					}
//				}
				if( ev == PROCESS_RECEIVE_COMPLETE_EVENT)	
				{	
						
						DIS_OPERATE_MODBUS;
						ENABLE_LOW_POWER;		//不断电
						//etimer_stop(&modbus_receive_timeout_etimer);
						memcpy(modbus_value, &(sensor_modbus.modbus_receive_array[sensor_modbus.modbus_receive_data_len_locat]),sensor_modbus.modbus_receive_data_len_num);
						if(modbus_work_status == modbus_status_collect)
						{	
								sensor_sixteen_buffer_put(SENSOR_MODBUS_TYPE, SENSOR_MODBUS_DATA_TYPE, node_parameter.MAC,
															modbus_value, sensor_modbus.modbus_receive_data_len_num, battery_modbus, node_running_flags.sensor_sample_time);				 								 
								modbus_sample_event();
						}
						
//						modbus_data = *(((uint8_t *)data)+6)+*(((uint8_t *)data)+5)*256+*(((uint8_t *)data)+4)*65536;					
//						if(modbus_work_status == modbus_status_collect)//接收错误
//						{				
//																
//								if(modbus_data == 0xFFFFFF&&modbus_data==0)
//								{
//										receive_modbus_fail_cnt++;
//										if(receive_modbus_fail_cnt >= MODBUS_FAIL_MAX_NUM)
//										{
//											sensor_sixteen_buffer_put(SENSOR_MODBUS_TYPE, 0xf4, node_parameter.MAC,
//															modbus_value, 3, battery_modbus, node_running_flags.sensor_sample_time);	
//											modbus_sample_event();
//										}else{
//											modbus_sample_collect();
//										}
//								 }
//								 else
//								 {
//											
//										
//											modbus_value[0] = modbus_data&0xff;
//											modbus_value[1] = (modbus_data>>8)&0xff;
//											modbus_value[2] = (modbus_data>>16)&0xff;
//											sensor_sixteen_buffer_put(SENSOR_MODBUS_TYPE, SENSOR_MODBUS_DATA_TYPE, node_parameter.MAC,
//															modbus_value, sensor_modbus.modbus_receive_data_len_num, battery_modbus, node_running_flags.sensor_sample_time);				 								 
//											modbus_sample_event();
//									 }
							#if DEBUG_PRINT
								printf("modbus value: %d\n", modbus_data);
							#endif
							//}	
				
				}	
	}		
	PROCESS_END();
}
void waiting_power_modbus(void)
{
	if(modbus_work_status == modbus_status_power_on)
	{
		
//		if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
//		{
				etimer_set(&modbus_power_wait_etimer, node_parameter.SPTD ms);		//????	
//		}else{
//				etimer_set(&modbus_power_wait_etimer, 100 ms);		//????	
//		}		
		
		OPERATE_MODBUS;
		ENABLE_LOW_POWER;
	}
	else
	{
		etimer_set(&modbus_power_wait_etimer, 100 ms);						//????
	}
}

void modbus_sample_collect(void)
{	
	OPERATE_MODBUS;
	ENABLE_LOW_POWER;//不断电
	modbus_port_init();
	modbus_send_data(&sensor_modbus);
	modbus_uart_enable_wake_event();
	modbus_work_status = modbus_status_collect;
	etimer_set(&modbus_receive_etimer, 500 ms);
	etimer_set(&modbus_receive_timeout_etimer, 2000 ms);
}
void modbus_sample_event(void)
{
	receive_modbus_fail_cnt = 0;
	DIS_OPERATE_MODBUS;
	ENABLE_LOW_POWER;
	uart_rx_disable();		
	modbus_work_status = modbus_status_end;		
	modbus_uart_disable_wake_event();								 									
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
	
}
#endif

