#include "sensor_sht25_process.h"
#include "sht25.h"
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sys_event.h"
#include "cycle_work_process.h"
#include "sensor_sixteen.h"
#include "battery.h"
#include "sensor_parameter.h"
#include "sen_work_process.h"
#include "data_conversion.h"
#include "sx127x_radio.h"
#include "led_process.h"
#include "power_manager_process.h"
#include "sensor_manager_process.h"
#include "power_manager.h"
#include <stdio.h>

typedef enum 
{
	SHT25_STATUS_INIT = 1,
	SHT25_STATUS_SAMPLE_TEMPER,
	SHT25_STATUS_SAMPLE_HUMI
}SHT25_STATUS_t;

void waiting_sample_sht25(void);
void send_humi_temper_value(uint16_t humi, uint16_t tempera);
void uart_param_init(void);
uint16_t calb_temper(uint16_t sample_temper);


#define SENSOR_SHT25_TYPE 		0x00
#define SENSOR_SHT25_DATA_TYPE	0x01

uint8_t battery;
uint16_t temper, humi;
uint8_t temp[4];

//蓝牙温湿度测试
#define BLE_TEST 0
//uart_param_t sht25_uart_param;

PROCESS(sensor_sht25_process,"sensor_sht25_process");
struct etimer sensoe_collect;
PROCESS_THREAD(sensor_sht25_process,ev,data)
{
	static SHT25_STATUS_t sht25_status = SHT25_STATUS_INIT;

	PROCESS_BEGIN();
	#if BLE_TEST
		uart_param_init();
	#endif
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if( ev == SENSOR_PROCESS_START)
		{
			#if DEBUG_PRINT
				printf("begin to sample sht25 \n");
			#endif
			//电量采集
			battery = battery_sample_data();
			//触发温度采集
			sht21_trigger_temp_measure();
			//等待80ms
			etimer_set(&sensoe_collect,80 ms);
			sht25_status = SHT25_STATUS_SAMPLE_TEMPER;
			waiting_sample_sht25();
		}
		//定时器到
		if(ev == PROCESS_EVENT_TIMER && data == &sensoe_collect)
		{
			DIS_OPERATE_SHT25;
			DISABLE_LOW_POWER;
			if(sht25_status == SHT25_STATUS_SAMPLE_TEMPER)
			{
				//温度采集
				temper = sht21_sample_temp();
				temper = calb_temper(temper);
				#if DEBUG_PRINT
					printf("temper sample complete,temper = %d \n", temper);
				#endif
				//触发湿度采集
				sht21_trigger_humi_measure();
				//等待80ms
				etimer_set(&sensoe_collect,80 ms);
				sht25_status = SHT25_STATUS_SAMPLE_HUMI;
	
				waiting_sample_sht25();
			}else if(sht25_status == SHT25_STATUS_SAMPLE_HUMI){
				//湿度采集
				humi = sht21_sample_humi();
				#if DEBUG_PRINT
					printf("humi sample complete,humi = %d \n", humi);
				#endif
				#if BLE_TEST
					send_humi_temper_value(humi, temper);
					etimer_set(&sensoe_collect,2 s);
					PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&sensoe_collect));
					process_post(&sensor_sht25_process,SENSOR_PROCESS_START,NULL );
				#endif
				
				//将传感器数据加入缓存
				temp[0] = humi&0xff;
				temp[1] = (humi>>8)&0xff;
				temp[2] = temper&0xff;
				temp[3] = (temper>>8)&0xff;
				sensor_sixteen_buffer_put(SENSOR_SHT25_TYPE, SENSOR_SHT25_DATA_TYPE, node_parameter.MAC,
									temp, 4, battery, node_running_flags.sensor_sample_time);
				post_sensor_manager_ev(SENSOR_COLLECT_DATA_END);
						
				sht25_status = SHT25_STATUS_INIT;
			}
		}
		
	}
	
	PROCESS_END();
}

//温湿度测试
uint8_t humi_temper_buffer[20];
void send_humi_temper_value(uint16_t humi, uint16_t tempera)
{
	uint8_t humi_len, tempera_len, humi_value, tempera_value;
	uint8_t humi_buffer[4], tempera_buffer[4];
	humi_value = humi/65536.0*125-6;
	tempera_value = tempera/65536.0*175.72-46.85;
	
	dec_to_ascii_in_order(humi_value, humi_buffer, &humi_len);
	dec_to_ascii_in_order(tempera_value, tempera_buffer, &tempera_len);
	
	humi_len = 2;
	tempera_len = 2;
	
	humi_temper_buffer[0] = 'H';
	humi_temper_buffer[1] = 'i';
	humi_temper_buffer[2] = 'm';
	humi_temper_buffer[3] = 'i';
	humi_temper_buffer[4] = 'l';
	humi_temper_buffer[5] = 'i';
	humi_temper_buffer[6] = ':';
	memcpy(humi_temper_buffer+7, humi_buffer, 2);
	humi_temper_buffer[humi_len+7] = ',';
	humi_temper_buffer[humi_len+8] = 'T';
	humi_temper_buffer[humi_len+9] = 'e';
	humi_temper_buffer[humi_len+10] = 'm';
	humi_temper_buffer[humi_len+11] = 'p';
	humi_temper_buffer[humi_len+12] = 'e';
	humi_temper_buffer[humi_len+13] = 'r';
	humi_temper_buffer[humi_len+14] = ':';
	memcpy(humi_temper_buffer+humi_len+15, tempera_buffer, 2);
	humi_temper_buffer[2+2+15] = '.';
	
	#if BLE_TEST
		uart_send_buff(humi_temper_buffer, 20);
	#endif

//	LED_GREEN_ON;
//	RadioDriver.SetTxPacket(humi_temper_buffer, humi_len+tempera_len+7);
}


void uart_param_init(void)
{
//	sht25_uart_param.uart_baudrate = uart_baudrate_115200;
//	sht25_uart_param.uart_baudrate_offset = 0;
//	sht25_uart_param.uart_data_len = uart_data_8_bit;
//	sht25_uart_param.uart_duplex_mode = uart_full_duplex_mode;
//	sht25_uart_param.uart_source_clock = uart_source_clock_select_apb;
//	sht25_uart_param.uart_parity_bit = uart_none_parity_bit;
//	sht25_uart_param.uart_start_bit = uart_has_start_bit;
//	sht25_uart_param.uart_stop_bit = uart_one_stop_bit;
//	sht25_uart_param.uart_tx_idle_state = uart_tx_idle_high_state;
//	sht25_uart_param.uart_rx_idle_state = uart_rx_idle_high_state;
//	sht25_uart_param.uart_rx_fifo_threshold = uart_rx_fifo_threshold_one_byte;

//	uart_init(&sht25_uart_param);
}


void waiting_sample_sht25(void)
{
	if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
	{
		//工作模式下
		OPERATE_SHT25;
		ENABLE_LOW_POWER;
	}
}

uint16_t calb_temper(uint16_t sample_temper)
{
	uint16_t temper;
	temper = node_parameter.DA*sample_temper - 3146*(node_parameter.DA-1) + node_parameter.DB*524;
	return temper;
}

