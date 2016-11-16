#include "rf_transmit_process.h"
#include "sys_event.h"
#include "board_cfg.h"
#include "sx127x_radio.h"
#include "sensor_payload.h"
#include "sensor_parameter.h"
#include "system_process_include.h"
#include "LED.h"
#include "ext_flash_include.h"
#include "power_manager.h"
#include "generic_include.h"
#include "debug_util.h"
#include <stdio.h>
#include <stdlib.h>

void init_transmit_moment_event(void);
void sensor_process_transmit(void);
void sensor_process_transmit_timeout(void);

void broadcast_join_payload_timeout_event(void);
void request_join_payload_timeout_event(void);
void transmit_sensor_data_timeout_event(void);
void transmit_sensor_history_payload_timeout_event(void);

void transmit(void);
void transmit_event(uint8_t rx_payload_size);
uint32_t get_rand_transmit_time(void);

void save_sensor_data_from_ram_to_flash(void);
void generate_random_transmit_event(void);
void check_next_sample_start_line(void);

struct etimer rf_transmit_timeout_etimer;		//发送超时定时器
struct etimer rf_transmit_duration_etimer;		//发送时刻定时器
struct etimer rf_transmit_start_line_etimer;	//设置发包起点

struct etimer rf_listen_broadcast_etimer;		//监听广播包(在周期开始的时候)
struct etimer rf_random_transmit_etimer;

PROCESS(rf_transmit_process, "rf_transmit_process");
PROCESS_THREAD(rf_transmit_process, ev, data)
{
	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == INIT_TRANSMIT_MOMENT)
		{
			//上电的时刻准备发送，计算发送时刻
			init_transmit_moment_event();//rf_transmit_start_line_etimer
		}
		if(ev == CALIBRATE_NEXT_TRANSMIT_START_LINE)
		{
			//更新通信周期起点
			uint64_t remaining_mils = (uint64_t)data;
			#if DEBUG_PRINT == 1
				printf("calibrate next transmit start line, remaining mils:%lld, ", remaining_mils);
				printf_time();
			#endif
			
			node_running_flags.is_calibrate_transmit_cycle = true;
			etimer_stop(&rf_transmit_duration_etimer);
			etimer_set(&rf_transmit_duration_etimer, remaining_mils ms);
			
			post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
		}
		
		if(ev == BEGIN_TRANSMIT_CYCLE_WORK)//通信发包
		{
			//通信周期的开始
			#if DEBUG_PRINT == 1
				printf("\n\n****begin transmit cycle, ");
				printf_time();
			#endif
			if(join_net_ack_info.is_allow_join)//是否入网
			{
				if(father_info.device_type == RELAY)//是否加入的中继网
				{
					//已经加入中继网络，先开始监听
					RadioDriver.StartRx();
					node_running_flags.current_work_stage = LISTEN_BROADCAST_STAGE;
					OPERATE_RF;
					DISABLE_LOW_POWER;
					etimer_set(&rf_listen_broadcast_etimer, CYCLE_START_LISTEN_TIME ms);		//该时间需要根据速率调整
				}else{
					//直接发送
					sensor_process_transmit();
				}
			}
			else
			{
				//否则，直接发送
				sensor_process_transmit();
			}
		}
		if(ev == END_TRANSMIT_CYCLE_WORK)
		{
			//通信周期的结束
			#if DEBUG_PRINT == 1
				printf("****end transmit cycle, ");
				printf_time();
			#endif
			if(node_running_flags.current_work_stage != FULL_CYCLE_MONITOR_STAGE)
			{
				DIS_OPERATE_RF;
			}
			ENABLE_LOW_POWER;
		}
		if(ev == GENERATE_RANDOM_TRANSMIT)
		{
			//产生随机延时
			generate_random_transmit_event();
		}
		if(ev == PREPARE_SENSOR_DATA)
		{
			//触发本周期数据发送
			node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
			sensor_process_transmit();
		}
		if(ev == PREPARE_HISTORY_DATA)
		{
			//触发历史数据发送
			node_running_flags.current_work_stage = TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE;
			sensor_process_transmit();
		}
		
		//--------------------------通信周期定时器--------------------------
		if(ev == PROCESS_EVENT_TIMER && data == &rf_transmit_duration_etimer )
		{
			//通信时刻定时器
			if(node_running_flags.is_calibrate_transmit_cycle)
			{
				node_running_flags.is_calibrate_transmit_cycle = false;
				etimer_set(&rf_transmit_duration_etimer, node_parameter.TDTI s);//重新校准后重新计时
			}
			else
			{
				if(father_info.device_type == RELAY)//判断父设备类型为中继
				{
					etimer_reset(&rf_transmit_duration_etimer);
				}
				else if(father_info.device_type == GATEWAY)//判断父设备为网关
				{
					uint16_t rand_time = get_rand_time(5000);
					uint16_t duration = node_parameter.TDTI*1000 + rand_time;
					#if DEBUG_PRINT
						printf("next transmit wakeup time:%d", duration);
					#endif
					etimer_set(&rf_transmit_duration_etimer, duration ms);
				}
			}
			//在此判断采集定时器和传输定时器唤醒的时间间隔
//			if(father_info.device_type == GATEWAY)
//			{
//				check_next_sample_start_line();
//			}
			
			 post_rf_transmit_ev(BEGIN_TRANSMIT_CYCLE_WORK, NULL);
		}
		//--------------------------通信超时事件--------------------------
		if(ev == PROCESS_EVENT_TIMER && data == &rf_transmit_timeout_etimer )
		{
			//发送超时
			sensor_process_transmit_timeout();
		}
		//--------------------------发包起点定时器--------------------------
		if(ev == PROCESS_EVENT_TIMER && data== &rf_transmit_start_line_etimer)
		{
			//初始化入网
			post_rf_transmit_ev(BEGIN_TRANSMIT_CYCLE_WORK, NULL);//rf_transmit_process
			etimer_set(&rf_transmit_duration_etimer, node_parameter.TDTI s);
		}
		//--------------------------周期开始前的广播监听--------------------------
		if(ev == PROCESS_EVENT_TIMER && data == &rf_listen_broadcast_etimer)
		{
			post_rf_transmit_ev(GENERATE_RANDOM_TRANSMIT,NULL);
		}
		//--------------------------
		if(ev == PROCESS_EVENT_TIMER && data == &rf_random_transmit_etimer)
		{
			post_rf_transmit_ev(PREPARE_SENSOR_DATA,NULL);
		}
	}
	
	PROCESS_END();
}

void post_rf_transmit_ev(process_event_t ev, process_data_t data)
{
	process_post(&rf_transmit_process, ev, data);
}

void init_transmit_moment_event(void)
{
	//上电的时候，随机获取一个数字作为发包起始时刻
	uint32_t rand_mils = get_rand_transmit_time();			//
	#if DEBUG_PRINT == 1
		printf("init transmit moment, moment = %d \n", rand_mils);
	#endif
	etimer_set(&rf_transmit_start_line_etimer, rand_mils ms);		//设置发送定时
}

void sensor_process_transmit(void)
{
	
	uint8_t info;
	#if DEBUG_PRINT == 1
		printf("process transmit, current work stage = %d, ", node_running_flags.current_work_stage);
		printf_time();
	#endif
	save_sensor_data_from_ram_to_flash();
	switch(node_running_flags.current_work_stage)
	{
		case BROADCAST_JOIN_PAYLOAD_STAGE:
			//广播请求父节点
			//屏蔽掉，为了测试
			assamble_join_net_request_payload(true);
			transmit();
			etimer_set(&rf_transmit_timeout_etimer, node_parameter.RNRWT ms);
			break;
		case FULL_CYCLE_MONITOR_STAGE:
			//全周期监听
			node_running_flags.current_work_stage = FULL_CYCLE_MONITOR_STAGE;
			post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
			break;
		case REQUEST_JOIN_PAYLOAD_STAGE:
			//主动请求指定地址父节点
			assamble_join_net_request_payload(false);
			transmit_event(33);
			break;
		case TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE:
			//本周期数据
			//检查时间同步计数
			#if DEBUG_PRINT == 1
				printf("transmit sensor data...\n");
			#endif
			node_running_flags.tsdc_cnt++;
			if(node_running_flags.tsdc_cnt >= node_parameter.TSDC)
			{
				info = 0x01;
			}else{
				info = 0x00;
			}
			if(assamble_sensor_data_payload(info))
			{
				if(node_running_flags.tsdc_cnt >= node_parameter.TSDC)
				{
					node_running_flags.tsdc_cnt = 0;
				}
				transmit_event(28);
			}
			else
			{
				#if DEBUG_PRINT == 1
					printf("no sensor data...\n");
				#endif
			}
			break;
		case TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE:
			//历史数据
			#if DEBUG_PRINT == 1
				printf("transmit history data...\n");
			#endif
			if(assamble_history_data_payload())
			{
				transmit_event(28);
			}
			else
			{
				//本周期没有历史数据，直接休眠
				#if DEBUG_PRINT == 1
					printf("no history data... \n");
				#endif
				node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
				post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
			}
			break;
		case CONFIG_PAYLOAD_STAGE:
			break;
		case QUICK_MODE_STAGE:
			break;
	}
}



void sensor_process_transmit_timeout(void)
{
	#if DEBUG_PRINT == 1
		printf("transmit timeout happened, current work stage = %d, ",node_running_flags.current_work_stage);
		printf_time();
	#endif
	switch(node_running_flags.current_work_stage)
	{
		case BROADCAST_JOIN_PAYLOAD_STAGE:
			//广播请求包
			broadcast_join_payload_timeout_event();
			break;
		case REQUEST_JOIN_PAYLOAD_STAGE:
			//请求指定地址的入网请求包
			request_join_payload_timeout_event();
			break;
		case TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE:
			//本周期数据
			transmit_sensor_data_timeout_event();
			break;
		case TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE:
			//历史数据
			transmit_sensor_history_payload_timeout_event();
			break;
		case CONFIG_PAYLOAD_STAGE:
			break;
		case QUICK_MODE_STAGE:
			break;
	}
}

void broadcast_join_payload_timeout_event(void)
{
	if(request_join_array.num > 0)
	{
		//寻找到路由
		uint8_t i, max_rssi_index = 0;
		//寻找信号最强的网关
		uint8_t max_rssi = 0xff;
		for(i=0; i<request_join_array.num ; i++)
		{
			if(request_join_array.request_join_array[i].is_allow_join)
			{
				//寻找允许加入网络中RSSI值最大的父节点
				uint8_t temp = -(request_join_array.request_join_array[i].rssi);
				if(max_rssi > temp)
				{
					max_rssi = temp;
					max_rssi_index = i;
				}
			}
		}
		if(max_rssi == 0xff)
		{
			//表示未找到可用的网络，则开启全周期监听
			#if DEBUG_PRINT == 1
				printf("found none father,go to full cycle monitor... \n");
			#endif
			post_cycle_work_ev(FULL_CYCLE_TO_MONITOR, NULL);
			return;
		}
		//搜索结束,已经入网
		request_join_array.num = 0x00;		//清空已找到的路由数量
		
		node_running_flags.dest_mac = request_join_array.request_join_array[max_rssi_index].device_mac;
		node_running_flags.dest_pan = request_join_array.request_join_array[max_rssi_index].device_panid;
		father_info.device_mac = request_join_array.request_join_array[max_rssi_index].device_mac;
		father_info.device_pan_id = request_join_array.request_join_array[max_rssi_index].device_panid;
		father_info.broadcast_period = request_join_array.request_join_array[max_rssi_index].bpt;
		father_info.device_type = request_join_array.request_join_array[max_rssi_index].device_type;
		father_info.power_type = request_join_array.request_join_array[max_rssi_index].power_type;
		father_info.broadcast_start_line = *(uint16_t*)&(rf_received_payload.payload[10]);
		join_net_ack_info.device_type = request_join_array.request_join_array[max_rssi_index].device_type;
		join_net_ack_info.power_type = request_join_array.request_join_array[max_rssi_index].power_type;
		join_net_ack_info.devie_remaining_num = request_join_array.request_join_array[max_rssi_index].devie_remaining_num;
		join_net_ack_info.is_allow_join = request_join_array.request_join_array[max_rssi_index].is_allow_join;
		join_net_ack_info.is_syn_time = request_join_array.request_join_array[max_rssi_index].is_syn_time;
		join_net_ack_info.has_capacity = request_join_array.request_join_array[max_rssi_index].has_capacity;
		join_net_ack_info.has_downlink_data = request_join_array.request_join_array[max_rssi_index].has_downlink_data;
		join_net_ack_info.downlink_data_priority = request_join_array.request_join_array[max_rssi_index].downlink_data_priority;
		memcpy(&join_net_ack_info.current_date, &request_join_array.request_join_array[max_rssi_index].current_date, 6);
		memcpy(&join_net_ack_info.broadcast_starting_line, &request_join_array.request_join_array[max_rssi_index].broadcast_starting_line,2);
		//允许加入
		if(join_net_ack_info.is_syn_time)
		{
			//step 1:同步时间
			set_current_time_by_mils(join_net_ack_info.current_date);
			//step 2:计算下一个采集周期的起点
			calibrate_next_sample_start_line_by_mils(join_net_ack_info.current_date);
		}else{
			
		}
		node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
		post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
	}else{	
		//未监听到路由
		post_cycle_work_ev(FULL_CYCLE_TO_MONITOR, NULL);
	}
}

void request_join_payload_timeout_event(void)
{
	#if DEBUG_PRINT == 1
		printf("fail to join the net... \n");
	#endif
	post_cycle_work_ev(LISTEN_ROUTER_FAIL, NULL);
	node_running_flags.current_work_stage = FULL_CYCLE_MONITOR_STAGE;
	post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
	
	led_red_shining();
}

void transmit_sensor_data_timeout_event(void)
{
	//通过软件机制判断是否已经接收到ACK
	if(node_running_flags.has_received_ack)
	{
		return;
	}
	node_running_flags.rtdc_cnt++;	//累计重传次数
	if(node_running_flags.rtdc_cnt >= node_parameter.RTDC)
	{
		#if DEBUG_PRINT == 1
			printf("fail transmit cycle, save sensor data... \n");
		#endif
		node_running_flags.rtdc_cnt = 0;
		node_running_flags.cftoc_cnt++;
		if(node_running_flags.cftoc_cnt >= node_parameter.CFTOC)
		{
			//连续通信周期失败，重新请求路由
			node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
			node_running_flags.cftoc_cnt = 0;
			join_net_ack_info.is_allow_join = false;
		}
		else
		{
			node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
		}
		save_sensor_data();
		post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
	}else{
		//可以重传
		#if DEBUG_PRINT == 1
			printf("transmit again, cnt = %d \n", node_running_flags.rtdc_cnt);
		#endif
		uint16_t timeout = node_parameter.TPTO + (16+rf_send_payload.payload_size)*8/get_spd_parameter();
		etimer_set(&rf_transmit_timeout_etimer, timeout ms);	//设置超时
		transmit();
	}
	led_red_shining();
}

void transmit_sensor_history_payload_timeout_event(void)
{
	if(node_running_flags.has_received_ack)
	{
		return;
	}
	node_running_flags.rtdc_cnt++;	//累计重传次数
	if(node_running_flags.rtdc_cnt >= node_parameter.RTDC)
	{
		#if DEBUG_PRINT == 1
			printf("fail transmit cycle, cancel read history data... \n");
		#endif
		node_running_flags.rtdc_cnt = 0;
		node_running_flags.cftoc_cnt++;
		if(node_running_flags.cftoc_cnt >= node_parameter.CFTOC)
		{
			//连续通信周期失败，重新请求路由
			node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
			node_running_flags.cftoc_cnt = 0;
		}else{
			node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
		}
		storage_cancle_read();
		node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
		post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
	}else{
		//可以重传
		#if DEBUG_PRINT == 1
			printf("transmit history, cnt = %d \n", node_running_flags.rtdc_cnt);
		#endif
		uint16_t timeout = node_parameter.TPTO + (16+rf_send_payload.payload_size)*8/get_spd_parameter();
		etimer_set(&rf_transmit_timeout_etimer, timeout ms);	//设置超时
		transmit();
	}
	led_red_shining();
}

void transmit_event(uint8_t rx_payload_size)
{
	uint16_t timeout;
	timeout = node_parameter.TPTO + (16+rf_send_payload.payload_size+rx_payload_size)*8/get_spd_parameter();
	etimer_set(&rf_transmit_timeout_etimer, timeout ms);	//设置超时
	transmit();
}

//发送
void transmit(void)
{
	#if DEBUG_PRINT == 1
		printf("begin transmitting, ");
		printf_time();
	#endif
	LED_GREEN_ON;
	send_sensor_payload();
	
	if(node_running_flags.sensor_system_state == SYSTEM_STATE_WORK)
	{
		//只在工作模式下
		OPERATE_RF;
		ENABLE_LOW_POWER;
	}
}

void stop_rf_random_transmit_etimer(void)
{
	etimer_stop(&rf_random_transmit_etimer);
}
	

void stop_rf_transmit_timeout_etimer(void)
{
	etimer_stop(&rf_transmit_timeout_etimer);
}

void stop_rf_transmit_moment_etimer(void)
{
	etimer_stop(&rf_transmit_duration_etimer);
}

uint32_t get_rand_transmit_time(void)
{
	uint32_t ret;
	uint32_t nMs = node_parameter.TDTI*1000;
	srand(get_current_time());
	uint16_t rand_num = rand();
	if(nMs<=3000)
	{
		ret = 1000;
	}else{
		ret = 2000 + rand_num%(nMs-2000);		
	}
	
	return ret;
}

void stop_rf_listen_broadcast_etimer(void)
{
	etimer_stop(&rf_listen_broadcast_etimer);
}
	
void stop_rf_transmit_duration_etimer(void)
{
	etimer_stop(&rf_transmit_duration_etimer);
}

void stop_rf_transmit_start_line_etimer(void)
{
	etimer_stop(&rf_transmit_start_line_etimer);
}
	
void save_sensor_data_from_ram_to_flash(void)
{
	if(node_running_flags.current_work_stage != TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE &&
	   node_running_flags.current_work_stage != TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE)
	{
		save_sixteen_data();
	}
}

void generate_random_transmit_event()
{
	uint16_t listen_duration = father_info.listen_duration*SLOT_TIME;	//监听时长
	uint32_t nMs = listen_duration;
	srand(get_current_time());
	uint16_t rand_num = rand();
	uint32_t ret = rand_num%(nMs-100);
	printf("random num = %d \n", ret);
	etimer_set(&rf_random_transmit_etimer, ret ms);
}

//判断采集时间与发包时间的差距
void check_next_sample_start_line(void)
{
	clock_time_t sample_expired_time = get_sample_cycle_next_expired_time();
	clock_time_t transmit_expired_time = etimer_expiration_time(&rf_transmit_duration_etimer);
	int gap;
	if(sample_expired_time >= transmit_expired_time)
	{
		gap = sample_expired_time - transmit_expired_time;
		if(gap <= 2 s)
		{
			//传输唤醒时间早2秒内时间唤醒，则调整
			uint16_t rand_time = get_rand_time(5000);
			etimer_adjust(&rf_transmit_duration_etimer, -(rand_time ms));
		}
	}else if(transmit_expired_time > sample_expired_time){
		gap = transmit_expired_time - sample_expired_time;
		if(gap <= 2 s)
		{
			//传输唤醒时间早2秒内时间唤醒，则调整
			uint16_t rand_time = get_rand_time(5000);
			etimer_adjust(&rf_transmit_duration_etimer, rand_time ms);
		}
	}
}

