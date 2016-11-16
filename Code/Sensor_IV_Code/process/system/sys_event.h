#ifndef __SYS_EVENT_H__
#define __SYS_EVENT_H__



#define SYSTEM_STATE_CLOSE  		0x00		//关机模式
#define SYSTEM_STATE_WORK   		0x01		//工作模式
#define SYSTEM_STATE_CONFIG  		0x02		//配置模式
#define SYSTEM_STATE_QUCK_WORK   	0x03		//快速工作模式



#define CHANGE_SYSTEM_STATE 

#define CHANGE_SYSTEM_STATE_TO_CLOSE     	0xA0    //关机事件
#define CHANGE_SYSTEM_STATE_TO_WORK      	0xA1	//正常工作事件
#define CHANGE_SYSTEM_STATE_TO_CONFIG    	0xA2    //配置模式事件
#define CHANGE_SYSTEM_STATE_TO_QUCK_WORK 	0xA3    //快速工作事件

#define SYSTEM_ENTER_CHECK_MODE			 	0xA4    //开始自检
#define SYSTEM_LEAVE_CHECK_MODE			 	0xA5  	//停止自检  
#define SYSTEM_CHECK_MODE_SAMPLE_END		0xA6	//自检下传感器采集结束

#define SYSTEM_ENTER_QUICK_MODE				0xA7

#define KEY_PRESS_EVENT            			0xB0
#define KEY_PRESS       					0xB1
#define KEY_PRESS_2S    					0xB2
#define KEY_PRESS_4S    					0xB3
#define KEY_PRESS_6S    					0xB4

#define SENSOR_PROCESS_START           		0xC0
#define SENSOR_COLLECT_DATA_END        		0xC1
#define SENSOR_MANAGER_START				0xC2

#define INIT_TRANSMIT_MOMENT				0xC3
#define SENSOR_PROCESS_TRANSMIT				0xC4

#define BEGIN_SAMPLE_CYCLE_WORK				0xC5		//采集周期的开始
#define END_SAMPLE_CYCLE_WORK				0xC6		//采集周期的结束
#define BEGIN_TRANSMIT_CYCLE_WORK			0xC7		//发送周期的开始
#define END_TRANSMIT_CYCLE_WORK				0xC8		//发送周期的结束
#define PREPARE_HISTORY_DATA				0xC9		//待发送历史数据
#define PREPARE_SENSOR_DATA					0xCA		//待发送本周期数据
#define GENERATE_RANDOM_TRANSMIT			0xCB		//产生随机发送数据起点

#define DETECTION_NEXT_HISTORY_DATA   0xCC
#define SOFTWARE_RESET_EVENT          0xCD
#define FORMAT_FLASH_EVENT            0xCE
#define SMS_EVENT                     0xCF
//#define PROCESS_CHECK_EVENT          0xFA
#define PROCESS_RECEIVE_COMPLETE_EVENT  0xF1//串口接收事件
#define PROCESS_RECEIVE_QUERY_ADDRESS_EVENT 0XF5
#define PROCESS_RECEIVE_MEASURE_COMPLETE_EVENT  0xF3
#define PROCESS_RECEIVE_DATA_COMPLETE_EVENT  0xF4
#define PROCESS_SDI12_START             0xF2
#define CALIBRATE_NEXT_SAMPLE_START_LINE	0xDA		//更新采集周期
#define PROCESS_SENSOR_NUM_CFG          0XF6
#define PROCESS_SENSOR_NUM_SET          0XF7
#define PROCESS_SENSOR_NUM_DEL          0XF9
#define PROCESS_RECEIVE_CHANGE_ADDRESS_EVENT 0xF8
#define FULL_CYCLE_TO_MONITOR				0xDB		//全周期监听
#define LISTEN_ROUTER_FAIL					0xDC

#define CALIBRATE_NEXT_TRANSMIT_START_LINE	0xDD

#define DATA_DOWNLOAD_DATA                  0xE5
#define DATA_ERASE_DATA						0xE6
#define DATA_ERASE_CHECK_OVER				0xE7

#define UART_RECEIVE_DATA_OVER              0xE8
//#define CO2_CALIBRATION						0xE9
#define WATER_CALIBRATION          0xEB
#define SCA126T_CALIBRATION        0XEC
#define ANALYSIS_0B_PAYLOAD					0xEA


#endif
