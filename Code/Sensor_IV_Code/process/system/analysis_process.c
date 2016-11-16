#include "analysis_process.h"
#include "sys_event.h"
#include "sensor_payload.h"
#include "sensor_parameter.h"
#include "sx127x_radio.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "ext_flash_include.h"
#include "download_history.h"
#include "broadcast_program.h"
#include "rtc_config.h"
#include "at_operation.h"
#include "sensor_payload.h"
#include "delay.h"
#include "timestamp.h"
#include <stdio.h>
#include "power_manager.h"
#include "debug_util.h"
#include "led.h"
void syntime_event(uint64_t time, uint8_t time_slice);

extern uint32_t flash_content_hex_bytes_num;			//历史记录总条数，在ext_flash_storage.c中定义

void analyst_broadcast_join_payload(uint8_t payload_type);
void analyst_full_cycle_monitor_payload(uint8_t payload_type);
void analyst_request_join_payload(uint8_t payload_type);
void analyst_transmit_sensor_data_payload(uint8_t payload_type);
void analyst_transmit_sensor_history_payload(uint8_t payload_type);
void analyst_father_broadcast_payload(uint8_t payload_type);

void analyst_config_payload_stage_payload(uint8_t payload_type);
void analyst_quick_mode_stage_payload(uint8_t payload_type);

void calibrate_next_sample_start_line_by_mils(uint64_t timestamp);
void calibrate_next_transmit_start_line_by_mils(uint64_t timestamp,uint8_t time_slice);

//解析线程
PROCESS(analysis_process, "analysis_process");
PROCESS_THREAD(analysis_process, ev, data)
{
	PROCESS_BEGIN();
	
	while(1)
	{
		PROCESS_WAIT_EVENT();
		
		if(ev == ANALYSIS_0B_PAYLOAD)
		{
			//解析0x0B载荷
			int cpu_sr = __get_PRIMASK();
			__set_PRIMASK(1);
			
			analyst_payload();
			
			__set_PRIMASK(cpu_sr);
			
			if(node_running_flags.current_work_stage==QUICK_MODE_STAGE)
			{
				if((rf_received_payload.payload_dest_pan_id != BROADCAST_ADDR)&&(rf_received_payload.payload_dest_addr != BROADCAST_ADDR))
					led_blue_shing();
			}
//			else
//			{
//				led_blue_shing();
//			}

		}
	}
	
	PROCESS_END();
}



////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 解析射频载荷包
// 输入参数 : 无
// 返回参数 : 无
// 说    明 : 
////////////////////////////////////////////////////////////////////////////////
void analyst_payload(void)
{
	uint8_t payload_type = rf_received_payload.payload_type;
	//根据当前的发包类型来决定数据处理
	#if DEBUG_PRINT
		printf("analyst payload, current work stage: %d \n", node_running_flags.current_work_stage);
	#endif
	switch(node_running_flags.current_work_stage)
	{
	case BROADCAST_JOIN_PAYLOAD_STAGE:
		//广播请求包
		analyst_broadcast_join_payload(payload_type);	//屏蔽掉调试用
		break;
	case FULL_CYCLE_MONITOR_STAGE:
		//全周期监听
		analyst_full_cycle_monitor_payload(payload_type);
		break;
	case REQUEST_JOIN_PAYLOAD_STAGE:
		//解析入网请求包阶段
		analyst_request_join_payload(payload_type);
		break;
	case TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE: 
		//解析本周期数据包阶段
		analyst_transmit_sensor_data_payload(payload_type);
		break;
	case TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE:
		//解析历史数据包
		analyst_transmit_sensor_history_payload(payload_type);
		break;
	case LISTEN_BROADCAST_STAGE:
		//解析指定父节点的广播数据包
		analyst_father_broadcast_payload(payload_type);
		break;
	case CONFIG_PAYLOAD_STAGE:
			//解析配置包阶段
		analyst_config_payload_stage_payload(payload_type);
    break;
	case QUICK_MODE_STAGE:
		//快速工作模式
		analyst_quick_mode_stage_payload(payload_type);
		break;
	case TRANSMIT_SENSOR_DOWNLOAD_DATA:
		
		break;
	default:
		break;
	}
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 
// 输入参数 : uint8_t payload_type 包类型
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void analyst_broadcast_join_payload(uint8_t payload_type)
{
	if(payload_type == (JOIN_NET_REQUEST_PAYLOAD_TYPE|0x80)){
		//解析请求入网ACK数据包（以广播发送入网请求）
		if(request_join_array.num >= MAX_ROUTER_NUM)
		{
			return;
		}
		int8_t rssi = RadioDriver.GetRssi();
		uint16_t src_pan_id = *(uint16_t *)&(rf_received_payload.payload[0]);
		uint8_t device_info = rf_received_payload.payload[2];
		uint8_t bpt = rf_received_payload.payload[3];
		uint8_t net_info = rf_received_payload.payload[4];
		//赋值
		if(rf_received_payload.payload_type != (JOIN_NET_REQUEST_PAYLOAD_TYPE|0x80))
		{
			return;
		}
		request_join_array.request_join_array[request_join_array.num].device_type            = device_info&0x07;
		request_join_array.request_join_array[request_join_array.num].power_type             = (device_info>>3)&0x01;
		request_join_array.request_join_array[request_join_array.num].devie_remaining_num    = (device_info>>4)&0x07;
		request_join_array.request_join_array[request_join_array.num].bpt                    = bpt;
		request_join_array.request_join_array[request_join_array.num].is_allow_join          = net_info&0x01;
		request_join_array.request_join_array[request_join_array.num].is_syn_time            = (net_info>>1)&0x01;
		request_join_array.request_join_array[request_join_array.num].has_capacity           = (net_info>>2)&0x01;
		request_join_array.request_join_array[request_join_array.num].has_downlink_data      = (net_info>>3)&0x01;
		request_join_array.request_join_array[request_join_array.num].downlink_data_priority = (net_info>>4)&0x01;
		
		memcpy(&request_join_array.request_join_array[request_join_array.num].current_date, &rf_received_payload.payload[5], 6);
		memcpy(&request_join_array.request_join_array[request_join_array.num].broadcast_starting_line, &rf_received_payload.payload[11],2);
		request_join_array.request_join_array[request_join_array.num].rssi                   = rssi;
		request_join_array.request_join_array[request_join_array.num].device_mac             = rf_received_payload.payload_src_addr;
		request_join_array.request_join_array[request_join_array.num].device_panid           = src_pan_id;
		request_join_array.num++;
		led_blue_shing();
	}
}

void analyst_full_cycle_monitor_payload(uint8_t payload_type)
{
	if(payload_type == BROADCAST_PACKET_PAYLOAD_TYPE)
	{
		//广播包
		if(router_array.router_num >= MAX_ROUTER_NUM)
		{
			return;
		}
		uint16_t src_pan_id = rf_received_payload.payload[0] + rf_received_payload.payload[1]*256;
		uint8_t device_info = rf_received_payload.payload[2];
		uint8_t broadcast_period = rf_received_payload.payload[4];
		uint8_t listen_period = rf_received_payload.payload[5];
		if(rf_received_payload.payload_type != (BROADCAST_PACKET_PAYLOAD_TYPE))
		{
			return;
		}
		router_array.router_array[router_array.router_num].device_mac       = rf_received_payload.payload_src_addr;
		router_array.router_array[router_array.router_num].device_panid     = src_pan_id;
		router_array.router_array[router_array.router_num].device_info      = device_info;
		router_array.router_array[router_array.router_num].broadcast_period = broadcast_period;
		router_array.router_array[router_array.router_num].listen_period    = listen_period;
		router_array.router_array[router_array.router_num].rssi             = rf_received_payload.pktrssi;
		router_array.router_array[router_array.router_num].received_time    = get_real_time();
		router_array.router_num++;
		led_blue_shing();
	}
}

void analyst_request_join_payload(uint8_t payload_type)
{
	
	if(payload_type == (JOIN_NET_REQUEST_PAYLOAD_TYPE|0x80))
	{
		#if JOIN_NET_DEBUG == 1
					printf("\n****analyst_request_join_payload****");
		#endif
//		uint16_t src_pan_id = rf_received_payload.payload[0] + rf_received_payload.payload[1]*256;
//		if((rf_received_payload.payload_src_addr!=father_info.device_mac)||(src_pan_id!=father_info.device_pan_id))
//		{
//			return;
//		}
		//特定地址请求入网ACK
		stop_rf_transmit_timeout_etimer();//停止发送失败超时
		
		uint8_t device_info                 = rf_received_payload.payload[2];
		uint8_t bpt                         = rf_received_payload.payload[3];
		uint8_t net_info                    = rf_received_payload.payload[4];
		if(rf_received_payload.payload_type != (JOIN_NET_REQUEST_PAYLOAD_TYPE|0x80))
		{
			post_cycle_work_ev(LISTEN_ROUTER_FAIL, NULL);
			led_red_shining();
			return;
		}
		//赋值
		join_net_ack_info.device_type            = device_info&0x07;
		join_net_ack_info.power_type             = (device_info>>3)&0x01;
		join_net_ack_info.devie_remaining_num    = (device_info>>4)&0x07;
		join_net_ack_info.is_allow_join          = net_info&0x01;
		join_net_ack_info.is_syn_time            = (net_info>>1)&0x01;
		join_net_ack_info.has_capacity           = (net_info>>2)&0x01;
		join_net_ack_info.has_downlink_data      = (net_info>>3)&0x01;
		join_net_ack_info.downlink_data_priority = (net_info>>4)&0x01;
		memcpy(&join_net_ack_info.current_date, &rf_received_payload.payload[5], 6);
		memcpy(&join_net_ack_info.broadcast_starting_line, &rf_received_payload.payload[11],2);
		father_info.broadcast_period             = bpt;
		father_info.device_type                  = device_info&0x07;
		father_info.power_type                   = (device_info>>3)&0x01;
		father_info.broadcast_start_line         = *(uint16_t*)&(rf_received_payload.payload[11]);
		
		//判断
		if(join_net_ack_info.is_allow_join)
		{
			//允许加入
			#if JOIN_NET_DEBUG == 1
					printf("****allow join net****\n");
					printf_time();
			#endif
			node_running_flags.dest_mac = father_info.device_mac;
			node_running_flags.dest_pan = father_info.device_pan_id;
			//同步时间事件
			if(join_net_ack_info.is_syn_time)
			{
				//只有父节点时间同步后才进行本地时间同步
					syntime_event(join_net_ack_info.current_date, TIME_SLICE);
			}
			//通信周期结束
			node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
			post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
			led_blue_shing();
		}
		else
		{
			//不允许加入
			#if JOIN_NET_DEBUG == 1
					printf("****not allowed to join net.****\n");
			#endif
			post_cycle_work_ev(LISTEN_ROUTER_FAIL, NULL);
			led_red_shining();
		}
		
	}
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 正常工作阶段收包事件处理
// 输入参数 : uint8_t payload_type 包类型
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void analyst_transmit_sensor_data_payload(uint8_t payload_type)
{
	//解析本周期数据包ACK
	if(payload_type == (DATA_PACKET_PAYLOAD_TYPE|0x80))
	{
		uint8_t data_ack_seq  = rf_received_payload.payload[0];
		uint16_t ack_info     = rf_received_payload.payload[1];
		uint8_t received      = (ack_info>>5) & 0x01;
		uint8_t has_syn_time  = (ack_info>>1) & 0x01;
		uint8_t has_timestamp = (ack_info>>6) & 0x01;
		uint8_t is_child      = (ack_info>>7) & 0x01;
		if(rf_received_payload.payload_type != (DATA_PACKET_PAYLOAD_TYPE|0x80))
		{
			return;
		}
		if(data_ack_seq == node_running_flags.data_type_seq_num)
		{
			//序列号相同
			#if DEBUG_PRINT
				printf("received ack \n");
			#endif
			node_running_flags.has_received_ack = true;
			stop_rf_transmit_timeout_etimer();
			node_running_flags.rtdc_cnt = 0;	//数据包重传次数清零
			node_running_flags.cftoc_cnt = 0;	//累计通信失败计数清零
			if(received)
			{
				//接收
				if(has_syn_time && has_timestamp)
				{
					//同步时间
					uint64_t received_utc_time=0;
					memcpy(&received_utc_time, rf_received_payload.payload+2, 6);
					//同步本地时间
					syntime_event(received_utc_time, TIME_SLICE_2);

				}
				else if((has_syn_time == 1) && (join_net_ack_info.is_syn_time == 0))//表示父节点同步可以执行同步操作
				{
					node_running_flags.tsdc_cnt = node_parameter.TSDC;
				}
				if((father_info.device_type==RELAY)&&(father_info.cal_transmit_duration==1))
				{
					uint64_t received_cal_time=0;
					father_info.cal_transmit_duration=0;
					memcpy(&received_cal_time, rf_received_payload.payload+(2+has_timestamp*6), 3);
					calibrate_next_transmit_start_line_by_mils(received_cal_time,TIME_SLICE_2);
				}
				if (sensor_sixteen_buffer_elements()) 
				{
					post_rf_transmit_ev(PREPARE_SENSOR_DATA, NULL);
				}
				else 
				{
					post_rf_transmit_ev(PREPARE_HISTORY_DATA, NULL);
				}
				led_blue_shing();
			}
			else
			{
				//不接收
				save_sensor_data();
				if(is_child)
				{
					node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
				}else{
					//不为子节点
					node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
					join_net_ack_info.is_allow_join = false;
				}
				post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
				led_red_shining();
			}
		} 
		else
		{
			save_sensor_data();
			led_red_shining();
			post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
		}
		
	}
	
}

void analyst_transmit_sensor_history_payload(uint8_t payload_type)
{
	//解析历史数据包ACK
	
	if(payload_type == (DATA_PACKET_PAYLOAD_TYPE|0x80))
	{
		uint8_t data_ack_seq = rf_received_payload.payload[0];
		uint16_t ack_info = rf_received_payload.payload[1];
		uint8_t received = (ack_info>>5) & 0x01;
		uint8_t is_child = (ack_info>>7) & 0x01;
		uint8_t has_syn_time = (ack_info>>1) & 0x01;
		if(rf_received_payload.payload_type != (DATA_PACKET_PAYLOAD_TYPE|0x80))
		{
			return;
		}
		if(data_ack_seq == node_running_flags.data_type_seq_num)
		{
			//序列号相同
			node_running_flags.has_received_ack = true;
			stop_rf_transmit_timeout_etimer();
			node_running_flags.rtdc_cnt = 0;	//数据包重传次数清零
			node_running_flags.cftoc_cnt = 0;	//累计通信失败计数清零
			if(received)
			{
				//接收
				storage_confirm_read();
				if((has_syn_time == 1) && (join_net_ack_info.is_syn_time == 0))//表示父节点同步可以执行同步操作
				{
					node_running_flags.tsdc_cnt = node_parameter.TSDC;
				}
				node_running_flags.hdtc_cnt++;
				if((node_running_flags.hdtc_cnt<node_parameter.HDTC)&&(father_info.device_type==GATEWAY))
				{
					process_post(&rf_transmit_process,DETECTION_NEXT_HISTORY_DATA,NULL);//会引起存储操作出错
				}
				else
				{
//					node_running_flags.hdtc_cnt=0;
					node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
					post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
				}
				led_blue_shing();
			}
			else
			{
				//不接收
				storage_cancle_read();
//				node_running_flags.hdtc_cnt=0;
				if(is_child)
				{
					node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
				}else{
					//不为子节点
					node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
					join_net_ack_info.is_allow_join = false;
				}
				post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
				led_red_shining();
//				node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
//				post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
			}
			
		}
		else
		{
			storage_cancle_read();
			led_red_shining();
			node_running_flags.current_work_stage = TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE;
			post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
		}
		
	}
	else 
	{
		led_red_shining();
	}
}
//接受到下次的校准时间同时发送数据包
void analyst_father_broadcast_payload(uint8_t payload_type)
{
	if(payload_type == BROADCAST_PACKET_PAYLOAD_TYPE)
	{
		uint16_t device_mac = rf_received_payload.payload_src_addr;
		uint16_t device_pan = rf_received_payload.payload[0] + rf_received_payload.payload[1]*256;	//源PAN ID
		if(device_mac == father_info.device_mac && device_pan == father_info.device_pan_id)
		{
			//指定的父节点广播数据包
			stop_rf_listen_broadcast_etimer();
			post_rf_transmit_ev(GENERATE_RANDOM_TRANSMIT,NULL);
			
			uint8_t device_info_lsb = rf_received_payload.payload[2];										//设备信息
			uint8_t device_info_msb = rf_received_payload.payload[3];
			uint8_t broadcast_period = rf_received_payload.payload[4];										//广播周期
			uint8_t listen_duration = rf_received_payload.payload[5];										//监听时长
			uint8_t device_type = device_info_lsb&0x07;
			uint8_t is_syn_time = device_info_msb&0x01;
			if(device_type == RELAY && is_syn_time)
			{
				#if DEBUG_PRINT
					printf("father has synchrone time \n");
				#endif
				uint64_t relay_current_utc_time = 0;
				memcpy(&relay_current_utc_time, rf_received_payload.payload+6, 6);	
				relay_current_utc_time &= 0xFFFFFFFFFFFF;
				//时间戳
				uint16_t broadcast_start_line = *(uint16_t *)&(rf_received_payload.payload[12]);		//广播时间起点
				if(relay_current_utc_time != 0)
				{
					father_info.broadcast_start_line = broadcast_start_line;
						syntime_event(relay_current_utc_time, TIME_SLICE);
					
				}
			}
			else
			{
				#if DEBUG_PRINT
					printf("father has not sysnchrone time \n");
				#endif
			}
			led_blue_shing();
		}
		
	}
}
////////////////////////////////////////////////////////////////////////////////
// 功能描述 : 配置阶段收包事件处理
// 输入参数 : uint8_t payload_type 包类型
// 返回参数 : 无
// 说明     : 
////////////////////////////////////////////////////////////////////////////////
void analyst_config_payload_stage_payload(uint8_t payload_type)
{
	led_blue_shing();
	if(payload_type == CONFIG_PAYLOAD_TYPE)
	{
		//配置包
		uint8_t config_target = (rf_received_payload.payload[0]&0xf0)>>4;   //配置对象
		uint8_t at_num = rf_received_payload.payload[0]&0x0f;               //AT指令条数
		uint8_t at_str_len = rf_received_payload.payload_size - 1;			//AT指令长度
		if(config_target == 0)
		{
			//传感器配置
			char i;
			AT_CMD_TYPE* at_items = at_disassemble(rf_received_payload.payload+1, at_str_len, at_num);
			//组装payload字段
			rf_send_payload.payload[0] = at_num&0x0f;
			rf_send_payload.payload_size = 1;
			
			uint8_t last_len = 0;
			uint8_t* at_ack = NULL;
			uint8_t at_ack_len = 0;
			for(i=0; i<at_num; i++)
			{
				at_ack = at_items[i].ack;
				at_ack_len = at_items[i].ack_len;
				memcpy(rf_send_payload.payload+1+last_len, at_ack, at_ack_len);
				
				rf_send_payload.payload_size += at_ack_len;
				last_len += at_ack_len;
				
				clear_at_item(&at_items[i]);
			}
			//组装其他字段
			assamble_sensor_config_payload();
			
			transmit();
			
			
		}
	}
	else if(payload_type == UPDATE_REQUEST_TYPE)
	{
		//固件单播更新请求包

	}
	else if(payload_type == DATA_DOWNLOAD_REQUEST_TYPE)
	{
		//数据下载请求包
		uint16_t control = *(uint16_t*)(rf_received_payload.payload+1);
		node_running_flags.data_download_request_control = control;
		//判断下载方式位，0表示重新开始，1表示续传
		if((control&0x0001) == 0x0000)
		{
			//重新开始
			download_data_init();
			
			node_running_flags.current_data_download_piece = 0;
			node_running_flags.data_download_num = flash_content_hex_bytes_num;
			if((flash_content_hex_bytes_num%DATA_DOWNLOAD_PER_NUM) == 0)
			{
				node_running_flags.data_download_all_piece = flash_content_hex_bytes_num/DATA_DOWNLOAD_PER_NUM;
			}
			else
			{
				node_running_flags.data_download_all_piece = flash_content_hex_bytes_num/DATA_DOWNLOAD_PER_NUM + 1;
			}
			
			//装配数据下载请求包ACK
			assambel_data_request_payload();
			//发送数据下载请求包ACK
			transmit();
		}
		else if((control&0x0005) == 0x0005)
		{
			//数据下载请求包确认,表示收到总条数,续传传感器数据
       process_post(&data_download_process, DATA_DOWNLOAD_DATA, NULL);
		}
	}
	else if(payload_type == (DATA_DOWNLOAD_DATA_TYPE|0x80))
	{
		//数据下载数据包
		uint32_t cur_piece = *(uint32_t*)rf_received_payload.payload;
		if(cur_piece == node_running_flags.current_data_download_piece)
		{
			//确保本次发送完成
			if(node_running_flags.current_data_download_piece == node_running_flags.data_download_all_piece)
			{
				//数据下载完成
				#if DEBUG_PRINT
					printf("data download done!!! \n");
				#endif
			}
			else
			{
				node_running_flags.data_download_rtyn_cnt = 0;
				uint16_t control = *(uint16_t*)(rf_received_payload.payload+4);
				node_running_flags.data_download_control = control;
				if((control&0x0001) == 0x0000)
				{
					//继续下载
					process_post(&data_download_process, DATA_DOWNLOAD_DATA, NULL);
				}
				else if((control&0x0001) == 0x0001)
				{
					//终止下载
					
				}
			}
		}
		else
		{
			//继续本次传输
			node_running_flags.data_download_rtyn_cnt++;
			if(node_running_flags.data_download_rtyn_cnt<3)
			{
				transmit();
			}
		}
		
		stop_data_download_timeout();	//停止超时定时器
	}
	else if(payload_type == FIREWARE_BROADCAST_UPDATE_REQUEST_PAYLOAD_TYPE)
	{
		//固件广播更新请求包
		memcpy(fireware_parameter.fireware_version, rf_received_payload.payload, 10);						//版本号
		fireware_parameter.fireware_all_piece = *(uint16_t *)(rf_received_payload.payload+10);	//文件总片数
		fireware_parameter.fireware_piece_size = *(uint16_t *)(rf_received_payload.payload+12);	//分片数据长度
		fireware_parameter.fireware_crc = *(uint16_t *)(rf_received_payload.payload+14);				//文件CRC
		fireware_parameter.fireware_update_ctr_field = *(uint16_t *)(rf_received_payload.payload+16);	//更新控制字段
	}
	else if(payload_type == FIREWARE_BROADCAST_UPDATE_DATA_PAYLOAD_TYPE)
	{
		//固件广播更新数据包
		if((fireware_parameter.fireware_update_ctr_field&0x0001) == 0x0001)
		{
			//强制更新
			uint16_t cur_piece = *(uint16_t *)rf_received_payload.payload;				//当前片数
			
			if(!is_bit_map_set(cur_piece))
			{
				//未收到该片
				set_bit_map(cur_piece);//设置当片对应的标志置1
				fireware_parameter.broadcast_recv_piece_size = rf_received_payload.payload_size - 2;		//当前片数实际长度
				fireware_parameter.broadcast_sum_bytes += fireware_parameter.broadcast_recv_piece_size; //加入总实际长度
				fireware_parameter.broadcast_program_recv_piece_num++;																	//片数计数器加一
				#if DEBUG_PRINT
				if(cur_piece == fireware_parameter.fireware_all_piece)
				{
					
						printf("the last piece");
					
				}
				#endif
				storage_write_broadcast_program(rf_received_payload.payload+2, cur_piece, fireware_parameter.fireware_piece_size);
				//写入外部FLASH
				if(fireware_parameter.fireware_all_piece == fireware_parameter.broadcast_program_recv_piece_num)
				{
					//收到全部片数，开启启动bootloader
					broadcast_reboot();
				}
				
			}
		}
	}
}

void analyst_quick_mode_stage_payload(uint8_t payload_type)
{
	if(payload_type == (ROUTER_PAYLOAD_TYPE|0x80))
	{
		//路由包反馈
		c_infos.g_num++;
	}else if(payload_type == (COMUNICATION_PACKET_PAYLOAD_TYPE|0x80))
	{
		//通信测试包反馈
		c_infos.c_info[c_infos.g_num].g_mac = rf_received_payload.payload_src_addr;
		c_infos.c_info[c_infos.g_num].n_sensitivity = rf_received_payload.pktrssi_register;
		c_infos.c_info[c_infos.g_num].g_sensitivity = rf_received_payload.payload[2];
		c_infos.g_num++;
	}
}

////计算下一个采集周期起点
//void calibrate_next_sample_start_line_by_second(uint32_t timestamp)
//{
//	int seconds = 0;
//	
//	uint64_t ellapse = timestamp - BEGIN_TIME;
//	seconds = ellapse % node_parameter.SSTI;
//	seconds = node_parameter.SSTI - seconds;
//	
//	uint64_t tick = seconds s;
//	#if DEBUG_PRINT
//		printf("remaing second = %lld \n", tick);
//	#endif
//	post_cycle_work_ev(CALIBRATE_NEXT_SAMPLE_START_LINE, (void *)tick);
//}

//计算下一个采集起点：对齐到整00秒
void calibrate_next_sample_start_line_by_mils(uint64_t timestamp)
{
	uint64_t remaining;
	uint64_t ellapse = timestamp - (uint64_t)BEGIN_TIME*1000;						//将起始时间转换为毫秒单位
	remaining = ellapse % ((uint64_t)node_parameter.SSTI*1000);						//距离本次整秒的时间
	if(remaining > 1000)
	{	
		//距离本次整秒的时间大于1秒
		remaining = node_parameter.SSTI*1000 - remaining;								//距离下一次唤醒的时间，单位ms
		if(remaining>100 && remaining<node_parameter.SSTI*2000)
		{
			stop_sample_cycle_timer();
			post_cycle_work_ev(CALIBRATE_NEXT_SAMPLE_START_LINE, (void *)remaining);
		}
	}
}
//获取下一次采集设置在采集定时器中的值
uint32_t get_next_sample_value(void)
{
	uint32_t value = 0;
	uint64_t time = 0;
	time = get_real_time()*1000/RTC_OSA;//获取当前时间（毫秒）
	uint64_t ellapse = time - (uint64_t)BEGIN_TIME*1000;//求当前时间和开始时间差
	uint32_t remain = ellapse % ((uint64_t)node_parameter.SSTI*1000);//时间差与采集周期求余：非整点整点整秒运行到此程序
	value = node_parameter.SSTI*1000 - remain;//求出下个采集等待时间
	if(value > node_parameter.SSTI*2000)
	{
		value = node_parameter.SSTI*1000;
	}
	
	return value;
}
uint32_t get_next_transmit_value(void)
{
	uint32_t value = 0;
	uint64_t time = 0;
	time = get_real_time()*1000/RTC_OSA;//获取当前时间（毫秒）
	uint64_t ellapse = time - (uint64_t)BEGIN_TIME*1000;//求当前时间和开始时间差
	uint32_t remain = ellapse % ((uint64_t)node_parameter.TDTI*1000);//时间差与采集周期求余：非整点整点整秒运行到此程序
	value = node_parameter.TDTI*1000 - remain;//求出下个发送等待时间 整分整秒
	
	time=node_parameter.SSTI*100+value;//加入阈值
	uint32_t rand_time_is=node_parameter.SSTI*1000-(200*node_parameter.SSTI);
	uint16_t rand_time = get_rand_time32(rand_time_is);//
	time+=rand_time;
	if(time > node_parameter.TDTI*2000)
	{
		time = node_parameter.TDTI*1000;
	}
	return time;
}
	
void calibrate_next_transmit_start_line_by_mils(uint64_t timestamp,uint8_t time_slice)
{
//	uint64_t remaining;
//	uint64_t ellapse = timestamp - (uint64_t)BEGIN_TIME*1000;						//将起始时间转换为毫秒单位

//	remaining = ellapse % ((uint64_t)father_info.broadcast_period*1000);			//距离下一次的广播周期的剩余的mils
//	
//	remaining = father_info.broadcast_period*1000 - remaining+father_info.broadcast_start_line*SLOT_TIME;		//1是误差修正

//	if(remaining < father_info.broadcast_period*1000)
//	{
//		post_rf_transmit_ev(CALIBRATE_NEXT_TRANSMIT_START_LINE, (void *)remaining);
//		//process_post_synch(&rf_transmit_process,CALIBRATE_NEXT_TRANSMIT_START_LINE,(void *)remaining);
//	}
	uint32_t ellapse = (get_rtc_time() - node_running_flags.received_rtc_time)/32;//变毫秒
	uint64_t current_time = timestamp - time_slice - ellapse;//下次唤醒时间=中继中继唤醒时间时间-数据传输时间-节点处理时间
	post_rf_transmit_ev(CALIBRATE_NEXT_TRANSMIT_START_LINE, (void *)current_time);
}

void syntime_event(uint64_t time, uint8_t time_slice)
{
	//step 1:同步时间
	uint32_t ellapse = (get_rtc_time() - node_running_flags.received_rtc_time)/32;//变毫秒
	uint64_t current_time = time + time_slice + ellapse;//当前时间=中继发射的时间+补偿时间+节点处理时间
	set_current_time_by_mils(current_time);							//同步本地时间
	//step 2:计算下一个采集周期的起点
	calibrate_next_sample_start_line_by_mils(current_time);	//同步采集时间起点
//	if(father_info.device_type == RELAY)
//	{	
		//中继包，同步发包起点
		//node_running_flags.received_rtc_time = get_rtc_time();
		//calibrate_next_transmit_start_line_by_mils(current_time);	//同步发包起点
//	}
}
