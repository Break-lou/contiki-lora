#include "sensor_sht25_process.h"
#include "cycle_work_process.h"
#include "contiki-conf.h"
#include "sys/etimer.h"
#include "sys/process.h"
#include "sensor_parameter.h"
#include "sensor_payload.h"
#include "delay.h"
#include "sx127x_radio.h"
#include "sx127x_app.h"
#include "ext_flash_include.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "rtc_config.h"
#include "timestamp.h"
#include "power_manager.h"
#include "debug_util.h"
#include <stdlib.h>
#include <stdio.h>
#include "clock_config.h"
#include "sensor_payload.h"
#include "delay.h"

//周期工作线程
struct etimer router_etimer;				//寻找路由定时器
struct etimer fail_router_etimer;		//路由失败定时器
struct etimer sample_cycle_etimer;		//采集周期

uint8_t compare_timeout_sample_time(void);
void sensor_sample(void);
void transmit(void);


void finish_listen_router_event(void);
void listen_router_fail_event(void);
//轮询工作进程
PROCESS(cycle_work_process,"cycle_work_process");
PROCESS_THREAD(cycle_work_process,ev,data)
{
	PROCESS_BEGIN();
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if(ev==SMS_EVENT)
		{
			delayXms(50);
			switch((uint16_t)data)
			{
				case 0: 
					node_running_flags.sensor_system_state = SYSTEM_STATE_CLOSE;
					process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_CLOSE,NULL);
					break;
				case 1: 
					node_running_flags.sensor_system_state = SYSTEM_STATE_WORK;
					process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_WORK,NULL);
					break;
				case 2:
					node_running_flags.sensor_system_state = SYSTEM_STATE_CONFIG;
					process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_CONFIG,NULL);
					break;
				case 3:
					node_running_flags.sensor_system_state = SYSTEM_STATE_QUCK_WORK;
					process_post(PROCESS_BROADCAST, CHANGE_SYSTEM_STATE_TO_QUCK_WORK,NULL);
					break;
				case 4:
					process_post(&cycle_work_process,SOFTWARE_RESET_EVENT,NULL);
					break;
			}
			
		}
		if(ev==SOFTWARE_RESET_EVENT)
		{
			set_software_reset_source();
		}
		if(ev==FORMAT_FLASH_EVENT)
		{
			
			send_set_flash_ack(format_flash());
		}
		if(ev == KEY_PRESS_2S)
		{
			//按键保持2S事件
			etimer_stop(&sample_cycle_etimer);//停止采样周期定时器
			stop_sen_work_timer();						//停止自检定时器：		sen_work_etimer
			stop_quick_work_timer();					//停止快速工作定时器：quick_work_etimer
			stop_rf_transmit_moment_etimer();	//停止通信周期定时器：rf_transmit_duration_etimer
			stop_rf_transmit_timeout_etimer();//停止通信超时定时器：rf_transmit_timeout_etimer
		}
		if(ev == CHANGE_SYSTEM_STATE_TO_CLOSE)
		{
			//************************关机************************
			wdtimer_stop();
			etimer_stop(&sample_cycle_etimer);
			etimer_stop(&router_etimer);
			etimer_stop(&fail_router_etimer);
			stop_sen_work_timer();
			stop_quick_work_timer();
			stop_led_etimer();
			//stop_rf_transmit_moment_etimer();
			stop_rf_transmit_timeout_etimer();
			stop_rf_transmit_duration_etimer();
			stop_rf_listen_broadcast_etimer();
			stop_rf_transmit_start_line_etimer();
			stop_rf_random_transmit_etimer();
			sx127x_modify_frq(node_parameter.FRQ);
			//清空参数
			clear_join_net_ack_info();
			clear_father_info();
			//休眠
			slep_low_power_parameter();
		}
		if(ev == CHANGE_SYSTEM_STATE_TO_WORK)
		{
			//************************正常工作************************
			#if DEBUG_PRINT == 1
			printf("01****cycle_work_process:  ev == CHANGE_SYSTEM_STATE_TO_WORK... \n");
			#endif
			process_start(&sensor_manager_process, NULL);	//开启传感器管理进程
 			init_low_power_parameter();
			//设置工作频段--默认433M
      RadioDriver.Init();         //射频初始化
			sx127x_modify_frq(node_parameter.FRQ);
			modify_spd_parameter();		//检测SPD参数是否要修改
			//设置变量
			node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;//系统状态量：加入网关
			post_rf_transmit_ev(INIT_TRANSMIT_MOMENT, NULL);//射频进程初始化事件
			post_cycle_work_ev(BEGIN_SAMPLE_CYCLE_WORK, NULL);//开始数据采集
			
		}
    if(ev == CHANGE_SYSTEM_STATE_TO_CONFIG)
    {
            //配置模式——进入接收模式
			wdtimer_reset();
			wdtimer_stop();
			etimer_stop(&sample_cycle_etimer);
			stop_sen_work_timer();
			stop_quick_work_timer();
			stop_rf_transmit_moment_etimer();
			stop_rf_transmit_timeout_etimer();
			stop_rf_transmit_duration_etimer();
			stop_rf_listen_broadcast_etimer();
			stop_rf_transmit_start_line_etimer();
			sx127x_modify_frq(CONFIG_FREQUENCY);
			sx127x_modify_spd(Init_LoRa_8K);
      RadioDriver.StartRx();
			
      node_running_flags.current_work_stage = CONFIG_PAYLOAD_STAGE;
			
			init_low_power_parameter();
    }
    if(ev == CHANGE_SYSTEM_STATE_TO_QUCK_WORK)
    {
            //快速工作模式
			init_low_power_parameter();
			//检测spd参数是否要修改
      RadioDriver.Init(); 
			sx127x_modify_frq(node_parameter.FRQ);
			modify_spd_parameter();
			
			node_running_flags.current_work_stage = QUICK_MODE_STAGE;
      post_quick_work_ev(SYSTEM_ENTER_QUICK_MODE);
			
			//init_low_power_parameter();
    }
		//---------------------
		if(ev == BEGIN_SAMPLE_CYCLE_WORK)
		{
			//采集周期的开始
			#if DEBUG_PRINT
				printf("\n");
				printf("3****begin sample cycle work, ");
				printf_time();
			#endif
			sensor_sample();//传感器采集并定时下一个周期
		}
		if(ev == END_SAMPLE_CYCLE_WORK)
		{
			//采集周期的结束
			#if DEBUG_PRINT
				printf("****end sample cycle work, ");
				printf_time();
			#endif
			ENABLE_LOW_POWER;//结束采集，开启低功耗
		}
		
		if(ev == CALIBRATE_NEXT_SAMPLE_START_LINE)
		{
			//校准下一次采集时间起点
			uint64_t remaining_mils = (uint64_t)data;
			#if DEBUG_PRINT
				printf("calibrate next sample start line, remaining mils:%lld, ", remaining_mils);
				printf_time();
			#endif
			stop_sample_cycle_timer();//stop:sample_cycle_etimer
			etimer_set(&sample_cycle_etimer, remaining_mils ms);//重新设置sample_cycle_etimer
		}
		if(ev == FULL_CYCLE_TO_MONITOR)
		{
			#if JOIN_NET_DEBUG == 1
					printf("\n****FULL_CYCLE_TO_MONITOR**** ");
					printf_time();
			#endif
			//开启全周期监听
			if(node_parameter.SFM == 1)
			{
				//第一种入网方式
				#if JOIN_NET_DEBUG == 1
					printf("****start full cycle to monitor sfm=1****\n");
					printf_time();
				#endif
				RadioDriver.StartRx();		
				etimer_set(&router_etimer, node_parameter.SLBD s);//监听路由周期定时
				node_running_flags.current_work_stage = FULL_CYCLE_MONITOR_STAGE;
				router_array.router_num = 0;//路由矩阵：数目为0
				OPERATE_RF;
				ENABLE_LOW_POWER;
			}else if(node_parameter.SFM == 2){
				//第二种入网方式
				#if JOIN_NET_DEBUG == 1
					printf("****start full cycle to monitor sfm=2****\n");
					printf_time();
				#endif
				//etimer_set(&router_etimer, node_parameter.SLBD s);//监听路由周期定时
//				router_array.router_num = 0;//路由矩阵：数目为0
				post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
			}
		}
		if(ev == LISTEN_ROUTER_FAIL)
		{
			listen_router_fail_event();//监听不到路由器
		}
		//---------------------router_etimer---------------------
		if(ev == PROCESS_EVENT_TIMER && data == &router_etimer)
		{
			#if JOIN_NET_DEBUG == 1
					printf("\n****router_etimer****\n ");
					printf_time();
			#endif
			//监听路由定时器结束，在此判断是否有收到广播包
			finish_listen_router_event();//完成监听路由任务
			
		}
		//---------------------sample_cycle_etimer---------------------
		if(ev == PROCESS_EVENT_TIMER && data == &sample_cycle_etimer)
		{
			//采集周期开始
			post_cycle_work_ev(BEGIN_SAMPLE_CYCLE_WORK, NULL);
			#if DEBUG_PRINT
				printf("8****cycle_work_process:  sample_cycle_etimer... \n");
			#endif
		}
		//---------------------fail_router_etimer---------------------
		if(ev == PROCESS_EVENT_TIMER && data == &fail_router_etimer)
		{
			//重新开启监听前首先发送入网请求包
			node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
			#if JOIN_NET_DEBUG == 1
			printf("\n****fail_router_etimer ok****\n");
			#endif
		}
	}	
	PROCESS_END();
}

void post_cycle_work_ev(process_event_t ev, process_data_t data)
{
	process_post(&cycle_work_process, ev, data);
}

void stop_sample_cycle_timer(void)
{
	etimer_stop(&sample_cycle_etimer);
}


void sensor_sample(void)
{
	node_running_flags.sensor_sample_time = get_upload_time();	//采集时间
	uint64_t value = get_next_sample_value();//获取下个采集时间的值
	etimer_set(&sample_cycle_etimer, value ms);			//下一次采集时间
	uint64_t time;
	time = node_running_flags.sensor_sample_time>>2; 
	if((time%10) != 0 )
	{
		if((time%10) <= 5 )
		{
			time=time-(time%10);
		}
		else if((time%10) > 5 )
		{
			time=time-(time%10)+10;
		}
		node_running_flags.sensor_sample_time&=0x0000000000000003;
		node_running_flags.sensor_sample_time|=(time<<2);
	}
//	s_time sample_time;
//	sample_time.clock=node_running_flags.sensor_sample_time>>2;
//	gmtime_new(&sample_time.analay_clock,sample_time.clock);
//	sample_time.analay_clock.tm_sec=0;
	#if HISTORY_NONE==0
	save_sensor_data_from_ram_to_flash();	//采集本周期数据时，查看上周期是否还有数据要保存 num--	
	#endif				
	post_sensor_manager_ev(SENSOR_MANAGER_START); 	//sensor_manager_process
}
//监听路由失败：延时继续监听
void listen_router_fail_event(void)
{
	node_running_flags.current_work_stage = FULL_CYCLE_MONITOR_STAGE;//开启全监听模式
	if(node_running_flags.listen_router_fail_cnt == 0)
	{
		//第一次监听失败,休眠一个监听周期后再开启监听
		node_running_flags.listen_router_fail_cnt = 1;
	}
	else if(node_running_flags.listen_router_fail_cnt==8)
	{
		#if relay_only
		node_running_flags.listen_router_fail_cnt=1;
		#else
		node_running_flags.listen_router_fail_cnt=240;
		#endif
	}
	else if(node_parameter.SFM == 1)
	{
		node_running_flags.listen_router_fail_cnt=node_running_flags.listen_router_fail_cnt+2;
	}
	else if(node_parameter.SFM == 2)
	{
		node_running_flags.listen_router_fail_cnt=1;
	}
	else if((node_parameter.SFM != 2)&&(node_parameter.SFM != 1))
	{
		node_running_flags.listen_router_fail_cnt=1;
	}
	#if JOIN_NET_DEBUG == 1
		printf("\n****Set fail_router_etimer and Listen router fail cnt = %d ****\n", node_running_flags.listen_router_fail_cnt);
	#endif
	if(node_parameter.SFM == 1)
	{
		etimer_set(&fail_router_etimer, node_parameter.SLBD*node_running_flags.listen_router_fail_cnt s);
	}
	else if(node_parameter.SFM == 2)
	{
		etimer_set(&fail_router_etimer, 100 ms);
	}else{
		etimer_set(&fail_router_etimer, node_parameter.SLBD*node_running_flags.listen_router_fail_cnt s);
	}
	DIS_OPERATE_RF;
	ENABLE_LOW_POWER;
}

void finish_listen_router_event(void)
{
	#if JOIN_NET_DEBUG == 1
					printf("\n****finish_listen_router_event()****");
	#endif
	if(router_array.router_num > 0)//查看analysis_process的analyst_full_cycle_monitor_payload函数中接收到的路由信息
	{
		//寻找到路由
		uint64_t ellapse,re_temp;
		int64_t remaining;
		uint8_t i, max_rssi_index = 0;
		//寻找信号最强的网关
		uint8_t max_rssi = 0xff;
		//求出收到的网关中信号最好的
		for(i=0; i< router_array.router_num; i++)
		{
			uint8_t temp = -(router_array.router_array[i].rssi);
			#if relay_only
			if((router_array.router_array[i].device_info&0x07)==RELAY)
			{
				max_rssi=temp;
				max_rssi_index = i;
			}
			#else
			if(max_rssi > temp)
			{
				max_rssi = temp;
				max_rssi_index = i;
			}
			#endif
		}
		if(max_rssi == 0xff)
		{
			//表示未找到可用的网络，则开启全周期监听
			#if JOIN_NET_DEBUG == 1
					printf("****listen_router_fail****\n");
			#endif
			//未监听到路由
			led_red_shining();
			listen_router_fail_event();//进入监听失败事件
			return;
		}
		
		//搜索到信号最强的父节点
		//记录父节点信息
		father_info.device_mac = router_array.router_array[max_rssi_index].device_mac;
		father_info.device_pan_id = router_array.router_array[max_rssi_index].device_panid;
		father_info.device_type = router_array.router_array[max_rssi_index].device_info&0x07;
		father_info.power_type = (router_array.router_array[max_rssi_index].device_info>>3)&0x01;
		father_info.broadcast_period = router_array.router_array[max_rssi_index].broadcast_period;
		father_info.listen_duration = router_array.router_array[max_rssi_index].listen_period;
		
		node_running_flags.listen_router_fail_cnt = 0;
		node_running_flags.sleep_max_cnt = 0;
		node_running_flags.current_work_stage = REQUEST_JOIN_PAYLOAD_STAGE;//收到广播信息后请求加入
		if(father_info.device_type == GATEWAY)//判断设备类型是否为网关
		{
			#if JOIN_NET_DEBUG == 1
					printf("****found gateway****\n");
			#endif	
//			post_rf_transmit_ev(BEGIN_TRANSMIT_CYCLE_WORK, NULL);//rf_transmit_process开始周期发送
			post_rf_transmit_ev(END_TRANSMIT_CYCLE_WORK, NULL);
		}
		else
		{			
			//接受到的时间即为中继广播周期的发送广播周期起点
			ellapse = get_real_time() - router_array.router_array[max_rssi_index].received_time;//获取时间差
			#if JOIN_NET_DEBUG == 1
					printf("****found relay****");
					printf("****ellapse = %lld ****\n", ellapse);
			#endif
			remaining = ((uint64_t)router_array.router_array[max_rssi_index].broadcast_period s) - ellapse;
			if(remaining < 0)
			{
				//已经超过一个广播周期，则等待下一个周期
				re_temp = remaining + (router_array.router_array[max_rssi_index].broadcast_period s);
			}else{
				re_temp = remaining;
			}
			//转换为毫秒
			re_temp = re_temp*1000/32768;
			//搜索结束，发送入网申请包
			node_running_flags.dest_mac = router_array.router_array[max_rssi_index].device_mac;
			node_running_flags.dest_pan = router_array.router_array[max_rssi_index].device_panid;		
			
			post_rf_transmit_ev(CALIBRATE_NEXT_TRANSMIT_START_LINE, (void*)re_temp);
		}
	}
	else
	{	
		#if JOIN_NET_DEBUG == 1
					printf("****listen_router_fail****\n");
		#endif
		//未监听到路由
		led_red_shining();
		listen_router_fail_event();//进入监听失败事件
	}
	
}
//获取采集下一个唤醒时间
clock_time_t get_sample_cycle_next_expired_time(void)
{
	return etimer_expiration_time(&sample_cycle_etimer);
}

