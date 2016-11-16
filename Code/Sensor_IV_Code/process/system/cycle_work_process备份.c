#include "sensor_sht25_process.h"
#include "sensor_water_power.h"
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



//周期工作线程
struct etimer router_etimer;			//寻找路由定时器
struct etimer fail_router_etimer;		//路由失败定时器
struct etimer sample_cycle_etimer;		//采集周期

uint8_t compare_timeout_sample_time(void);
void sensor_sample(void);
void transmit(void);


void finish_listen_router_event(void);
void listen_router_fail_event(void);

PROCESS(cycle_work_process,"cycle_work_process");
PROCESS_THREAD(cycle_work_process,ev,data)
{
	PROCESS_BEGIN();
	while(1)
	{
		PROCESS_WAIT_EVENT();
		if(ev == KEY_PRESS_2S)
		{
			//按键保持2S事件
			etimer_stop(&sample_cycle_etimer);
			stop_sen_work_timer();
			stop_quick_work_timer();
			stop_rf_transmit_moment_etimer();
			stop_rf_transmit_timeout_etimer();
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
			stop_rf_transmit_moment_etimer();
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
			low_power_parameter();
		}
		if(ev == CHANGE_SYSTEM_STATE_TO_WORK)
		{
			//************************正常工作************************
			process_start(&sensor_manager_process, NULL);	//开启传感器管理进程
			init_low_power_parameter();
			//设置工作频段--默认433M
      RadioDriver.Init();         //射频初始化
			sx127x_modify_frq(node_parameter.FRQ);
			modify_spd_parameter();		//检测SPD参数是否要修改
			//设置变量
			node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
			
			post_rf_transmit_ev(INIT_TRANSMIT_MOMENT, NULL);//rf_transmit_process
			post_cycle_work_ev(BEGIN_SAMPLE_CYCLE_WORK, NULL);//cycle_work_process 
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
			init_low_power_parameter();
    }
		//---------------------
		if(ev == BEGIN_SAMPLE_CYCLE_WORK)
		{
			//采集周期的开始
			printf("\n\n");
			printf("****begin sample cycle work, ");
			printf_time();
			sensor_sample();
		}
		if(ev == END_SAMPLE_CYCLE_WORK)
		{
			//采集周期的结束
			printf("****end sample cycle work, ");
			printf_time();
			
			ENABLE_LOW_POWER;
		}
		
		if(ev == CALIBRATE_NEXT_SAMPLE_START_LINE)
		{
			//校准下一次采集时间起点
			uint64_t remaining_mils = (uint64_t)data;
			#if DEBUG_PRINT
				printf("calibrate next sample start line, remaining mils:%lld, ", remaining_mils);
				printf_time();
			#endif
			stop_sample_cycle_timer();
			etimer_set(&sample_cycle_etimer, remaining_mils ms);
		}
		if(ev == FULL_CYCLE_TO_MONITOR)
		{
			//开启全周期监听
			#if DEBUG_PRINT
				printf("######start full cycle to monitor###### ");
				printf_time();
			#endif
			RadioDriver.StartRx();		
			etimer_set(&router_etimer, node_parameter.SLBD s);
			node_running_flags.current_work_stage = FULL_CYCLE_MONITOR_STAGE;
			router_array.router_num = 0;
			OPERATE_RF;
			ENABLE_LOW_POWER;
		}
		if(ev == LISTEN_ROUTER_FAIL)
		{
			listen_router_fail_event();
		}
		
		//---------------------router_etimer---------------------
		if(ev == PROCESS_EVENT_TIMER && data == &router_etimer)
		{
			//监听路由定时器结束，在此判断是否有收到广播包
			finish_listen_router_event();
		}
		//---------------------sample_cycle_etimer---------------------
		if(ev == PROCESS_EVENT_TIMER && data == &sample_cycle_etimer)
		{
			//采集周期开始
			#if DEBUG_PRINT
				printf("process sample_cycle_etimer event \n");
			#endif
			post_cycle_work_ev(BEGIN_SAMPLE_CYCLE_WORK, NULL);//cycle_work_process
			//post_sensor_manager_ev(SENSOR_MANAGER_START);
		}
		//---------------------fail_router_etimer---------------------
		if(ev == PROCESS_EVENT_TIMER && data == &fail_router_etimer)
		{
			//重新开启监听前首先发送入网请求包
			#if DEBUG_PRINT
				printf("process fail_router_etimer event \n");
			#endif
			//modify by yozen 2015.10.15
			node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
//			post_cycle_work_ev(FULL_CYCLE_TO_MONITOR, NULL);
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
	node_running_flags.sensor_sample_time = get_upload_time();				//获取起始采集时间
	etimer_set(&sample_cycle_etimer, node_parameter.SSTI s);				//下一次采集时间
	save_sensor_data_from_ram_to_flash();									//采集本周期数据时，查看上周期是否还有数据要保存
	post_sensor_manager_ev(SENSOR_MANAGER_START);
}

void listen_router_fail_event(void)
{
	node_running_flags.current_work_stage = FULL_CYCLE_MONITOR_STAGE;
	#if DEBUG_PRINT
		printf("pre listen router fail cnt = %d \n", node_running_flags.listen_router_fail_cnt);
	#endif
	if(node_running_flags.listen_router_fail_cnt == 0){
		//第一次监听失败,休眠一个监听周期后再开启监听
		node_running_flags.listen_router_fail_cnt = 1;
	}else if(node_running_flags.listen_router_fail_cnt == 1){
		//第二次监听失败，休眠2个监听周期后再开启监听
		if(node_parameter.SFM == 1)
		{
			node_running_flags.listen_router_fail_cnt = 2;
		}else if(node_parameter.SFM == 2){
			node_running_flags.listen_router_fail_cnt = 1;
		}else{
			node_running_flags.listen_router_fail_cnt = 1;
		}
	}else if(node_running_flags.listen_router_fail_cnt == 2){
		//第二次监听失败，休眠2个监听周期后再开启监听
		if(node_parameter.SFM == 1)
		{
			node_running_flags.listen_router_fail_cnt = 4;
		}else if(node_parameter.SFM == 2){
			node_running_flags.listen_router_fail_cnt = 1;
		}else{
			node_running_flags.listen_router_fail_cnt = 1;
		}
	}else if(node_running_flags.listen_router_fail_cnt == 4){
		//第二次监听失败，休眠2个监听周期后再开启监听
		if(node_parameter.SFM == 1)
		{
			node_running_flags.listen_router_fail_cnt = 8;
		}else if(node_parameter.SFM == 2){
			node_running_flags.listen_router_fail_cnt = 1;
		}else{
			node_running_flags.listen_router_fail_cnt = 1;
		}
	}else if(node_running_flags.listen_router_fail_cnt == 8){
		node_running_flags.sleep_max_cnt++;
		if(node_running_flags.sleep_max_cnt >= 8){
			node_running_flags.sleep_max_cnt = 0;	//休眠到8个周期后，累计已经休眠了多少个"8周期"，一旦达到8个8周期后，直接休眠240个周期，后续则一直保持
			if(node_parameter.SFM == 1)
			{
				node_running_flags.listen_router_fail_cnt = 240;	
			}else if(node_parameter.SFM == 2){
				node_running_flags.listen_router_fail_cnt = 1;
			}else{
				node_running_flags.listen_router_fail_cnt = 1;
			}
		}
	}else{
		if(node_parameter.SFM == 1)
		{
			node_running_flags.listen_router_fail_cnt = 240;
		}else if(node_parameter.SFM == 2){
			node_running_flags.listen_router_fail_cnt = 1;
		}else{
			node_running_flags.listen_router_fail_cnt = 1;
		}
	}
	#if DEBUG_PRINT
		printf("current listen router fail cnt = %d \n", node_running_flags.listen_router_fail_cnt);
	#endif
	etimer_set(&fail_router_etimer, node_parameter.SLBD*node_running_flags.listen_router_fail_cnt s);
	DIS_OPERATE_RF;
	ENABLE_LOW_POWER;
}

void finish_listen_router_event(void)
{
	#if DEBUG_PRINT
		printf("full cycle monior over, ");
		printf_time();
	#endif
	if(router_array.router_num > 0)
	{
		//寻找到路由
		uint64_t ellapse,re_temp;
		int64_t remaining;
		uint8_t i, max_rssi_index = 0;
		//寻找信号最强的网关
		uint8_t max_rssi = 0xff;
		for(i=0; i< router_array.router_num; i++)
		{
			uint8_t temp = -(router_array.router_array[i].rssi);
			if(max_rssi > temp)
			{
				max_rssi = temp;
				max_rssi_index = i;
			}
		}
		#if DEBUG_PRINT
			printf("found max rssi father... \n");
		#endif
		//搜索到信号最强的父节点
		//记录父节点信息
		father_info.device_mac = router_array.router_array[max_rssi_index].device_mac;
		father_info.device_pan_id = router_array.router_array[max_rssi_index].device_panid;
		father_info.device_type = router_array.router_array[max_rssi_index].device_info&0x07;
		father_info.power_type = (router_array.router_array[max_rssi_index].device_info>>3)&0x01;
		father_info.broadcast_period = router_array.router_array[max_rssi_index].broadcast_period;
		father_info.listen_duration = router_array.router_array[max_rssi_index].listen_period;
		
		node_running_flags.current_work_stage = REQUEST_JOIN_PAYLOAD_STAGE;
		if(father_info.device_type == GATEWAY)
		{
			#if DEBUG_PRINT
				printf("found gateway \n");
			#endif
			node_running_flags.listen_router_fail_cnt = 0;
			node_running_flags.sleep_max_cnt = 0;
			post_rf_transmit_ev(BEGIN_TRANSMIT_CYCLE_WORK, NULL);
		}
		else
		{
			ellapse = get_real_time() - router_array.router_array[max_rssi_index].received_time;
			#if DEBUG_PRINT
				printf("ellapse = %lld \n", ellapse);
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
	}else{	
		//未监听到路由
		led_red_shining();
		listen_router_fail_event();
	}
	
}
//获取采集下一个唤醒时间
clock_time_t get_sample_cycle_next_expired_time(void)
{
	return etimer_expiration_time(&sample_cycle_etimer);
}

