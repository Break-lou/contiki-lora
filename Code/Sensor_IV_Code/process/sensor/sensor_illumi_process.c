#include "sensor_illumi_process.h"
#include "illumi.h"
#include "uart.h"
#include "battery.h"
#include "sensor_parameter.h"
#include "sensor_sixteen.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "power_manager.h"
#include "debug_util.h"
#include "pmu_config.h"
#include <stdio.h>

//新叶光照


#define SENSOR_ILLUMI_TYPE 			0x03
#define SENSOR_ILLUMI_DATA_TYPE		0x24//36
								

#if ILLUMI_OPERATE
struct etimer sample_illumi_timeout;
struct etimer illumi_power_timer;
extern uint8_t (*uart_recv_option)(uint8_t data);
extern uint32_t uart_rx_cnt;
extern uint8_t uart_test_buff[UART_BUFFER_LEN];
extern uint8_t ilumi_battery;
extern uint8_t timeout_cnt;
void sample_end_event(void);

PROCESS(sensor_illumi_process,"sensor_illumi_process");
PROCESS_THREAD(sensor_illumi_process,ev,data)
{
	PROCESS_BEGIN();
	illumi_port_init();
	illumi_uart_init(uart_baudrate_9600);
	
	pmu_close();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if( ev == SENSOR_PROCESS_START)
		{
			//开始采集
			#if DEBUG_PRINT
				printf("begin sample illumi \n");
			#endif
			uart_recv_option=illumi_analyster;
			ilumi_battery = battery_sample_data();
			//open_illumi_sensor_power();							//开电源，上电1s后再开串口
			DCDC_SET(DCDC_3_3V);
			if(node_running_flags.current_work_stage != CONFIG_PAYLOAD_STAGE)
			{
				etimer_set(&illumi_power_timer, 1 s);		
			}else{
				etimer_set(&illumi_power_timer, 100 ms);	
			}				
			
			OPERATE_ILLUMI;
			ENABLE_LOW_POWER;
			
		}
		if(ev == UART_RECEIVE_DATA_OVER)
		{
			//采集结束
			#if DEBUG_PRINT
				printf("sample illumi over, illumi data = ");
				print_buff(uart_test_buff+3, 4);
				printf_time();
			#endif
			etimer_stop(&sample_illumi_timeout);
			timeout_cnt = 0;
			//uart_rx_disable();
			//pmu_close();
			sensor_sixteen_buffer_put(SENSOR_ILLUMI_TYPE, SENSOR_ILLUMI_DATA_TYPE, node_parameter.MAC,
									uart_test_buff+3, 4, ilumi_battery, node_running_flags.sensor_sample_time);	
			sample_end_event();
			DIS_OPERATE_ILLUMI;
			ENABLE_LOW_POWER;
		}
		if(ev == PROCESS_EVENT_TIMER && data == &illumi_power_timer)
		{
			//光照上电定时器
			printf("illumi power over \n");
			illumi_port_init();
			uart_rx_enable();		
			illumi_uart_enable_wake_event();
			etimer_set(&sample_illumi_timeout, 1 s);
		}
		if(ev == PROCESS_EVENT_TIMER && data == &sample_illumi_timeout)
		{
			//采集超时
			timeout_cnt++;
			#if DEBUG_PRINT
				printf("sample illumi timeout, timeout cnt = %d \n", timeout_cnt);
			#endif
			uart_rx_disable();
			if(timeout_cnt >= 3)
			{
				//采集失败
				timeout_cnt = 0;
				sample_end_event();
				DIS_OPERATE_ILLUMI;
				ENABLE_LOW_POWER;
			}else{
				//重新采集
				process_post(&sensor_illumi_process, SENSOR_PROCESS_START, NULL);
			}
		}
	
	
	}
	PROCESS_END();
}



void stop_sample_illumi_timeout(void)
{
	etimer_stop(&sample_illumi_timeout);
}

void sample_end_event(void)
{
	post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);

}

#endif










