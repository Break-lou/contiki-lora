#ifndef __SENSOR_PARAMETER_H__
#define __SENSOR_PARAMETER_H__

#include "board_cfg.h"
#include <si32_device.h>
#include <stdbool.h>
#include <string.h>
#include "modbus.h"
#define DEFAULT_PAYLOAD_B1		0x41
#define DEFAULT_PAYLOAD_B2		0x88

#define PAYLOAD_FLAG 			0x0b

#define ROUTER_PAYLOAD_TYPE		0x01		//路由请求包
#define SYNTIME_PAYLOAD_TYPE	0x02		//时间请求包
#define DATA_PAYLOAD_TYPE		0x03		//数据包
#define CONFIG_PAYLOAD_TYPE     0x04        //配置包
#define UPDATE_REQUEST_TYPE		0x05		//固件单播更新请求包
#define UPDATE_DATA_TYPE		0x06		//固件单播更新数据包
#define SEN_DATA_TYPE			0x0A		//自检包
#define DATA_DOWNLOAD_REQUEST_TYPE	0x0B		//数据下载请求包
#define DATA_DOWNLOAD_DATA_TYPE		0x0C		//数据下载数据包
#define FIREWARE_BROADCAST_UPDATE_REQUEST_PAYLOAD_TYPE	0x0D	//固件广播更新请求包
#define FIREWARE_BROADCAST_UPDATE_DATA_PAYLOAD_TYPE		0x0E	//固件广播更新数据包
//新增加的协议数据类型
#define BROADCAST_PACKET_PAYLOAD_TYPE	0x10	//广播数据包
#define JOIN_NET_REQUEST_PAYLOAD_TYPE	0x11	//入网请求包
#define DATA_PACKET_PAYLOAD_TYPE		0x12	//数据通信包
#define COMUNICATION_PACKET_PAYLOAD_TYPE	0x09	//通信测试包 
#define BROADCAST_ADDR			0xFFFF

#define CONFIG_FREQUENCY		4400//4750			//	

#define BROADCAST_JOIN_PAYLOAD_STAGE 			0x01		//上电时广播路由
#define FULL_CYCLE_MONITOR_STAGE				0x02
#define REQUEST_JOIN_PAYLOAD_STAGE				0x03		//收到广播信息后请求加入
#define TRANSMIT_SENSOR_DATA_PAYLOAD_STAGE 		0x04
#define TRANSMIT_SENSOR_HISTORY_PAYLOAD_STAGE	0x05		
#define LISTEN_BROADCAST_STAGE					0x06
#define CONFIG_PAYLOAD_STAGE					0x07
#define QUICK_MODE_STAGE						0x08

#define TRANSMIT_SENSOR_DOWNLOAD_DATA		0xFF

//设备类型
#define GATEWAY	0x01
#define RELAY	0x02
#define NODE	0x03

//传感器类型定义
#define SHT25_TYPE				1
#define CO2_TYPE					2
#define ILLUMI_TYPE				3
#define UV_TYPE						4
#define VOC_TYPE					5
#define SHT25CO2_TYPE			6
#define SHT25ILLUMI_TYPE	7
#define SHT25UV_TYPE			8
#define SHT25VOC_TYPE			9
#define WATER_TYPE 				10
#define NHZF42_TYPE				11
#define DS18B20_TYPE      12
#define SOIL_MOISTURE     13  //土壤水分传感器
#define S_5TM_TYPE        14
#define NHFS15_TYPE       15  //辐射
#define ACA826T_TYPE			16
#define SCA126T_TYPE      17

#define LVDT_TYPE        	18					//LVDT
#define ROTONIC_TYPE      				19  //ROTONIC高精度
#define WATERIMMERSION_TYPE	 N_TYPE	21	//温湿度水浸
#define RAINFALL_TYPE 						22	//雨量
#define DMETER_V_TYPE							23	//位移计--上发位移值
#define DMETER_MV_TYPE						24	//位移计--上发模值
#define STRAINOMETER_V_TYPE				25	//应变计--上发应变值
#define STRAINOMETER_MV_TYPE			26	//应变计--上发模值

 #define NHZD10_TYPE       				27  //能慧光照
#define MODBUS_TYPE 29
#define NHUV11_TYPE 30								//能慧紫外
#define MLX90614    31                //红外测温   
#define SKD_100D_TYPE    32                //激光测距
//软件类型
#define SOFTWARE_TYPE   1       //1--单跳
//每次数据下载条数
#define DATA_DOWNLOAD_PER_NUM	5

typedef struct NODE_PARAMETER_t
{
	uint32_t valid;				//首次运行检测该标志
	uint32_t update_flag;			
	uint32_t program_start_addr;
	uint32_t program_end_addr;	
	//设备网络参数
	uint16_t MAC;
	uint16_t PAN;
	//传输数据过程参数
	uint16_t TDTI;				//通信周期
	uint16_t SSTI;				//采样周期
	uint16_t RTDC;				//数据包重传次数
	uint16_t TSDC;				//时间同步周期数
	uint16_t TPTO;				//发送超时时间（从发包到接收完成）
	uint16_t HISN;				//一个通信周期上传历史记录条数
	uint16_t HDTC;				//几个历史通信次数
	uint16_t CFTOC;				//连续通信失败周期数（重新寻找父节点）
	//传感器采集参数
	uint16_t SPTD;				//传感器上电时间
	//建立网络过程参数
	uint16_t SLBD;				//监听广播包时间长度（全周期监听时间），单位s
	uint16_t RNRWT;				//上电广播入网请求等待时间，单位ms
	//通信速率参数
	uint16_t SBW;				
	uint16_t SCR;				
	uint16_t SSF;
	uint16_t PWR;
	uint16_t FRQ;
	//传感器类型
	uint16_t SETP;				//传感器类型
	//温度修正线性公式参数
	uint16_t DA;
	uint16_t DB;
	//搜索父节点方式
	uint8_t SFM;
	
	uint8_t RCTDC;//中继校准时间周期
	//水位校准
	#if WATER_OPERATE
	int16_t WVC;
	#endif
	#if S_5TM_OPERATE
	uint8_t channel[9];
	uint8_t channel_len;
	uint8_t channel_cnt;
	uint8_t channel_num;
	uint32_t valid_5tm; 
	#endif
	#if modbus_mode
	uint8_t modbus_array[20];		
	uint8_t modbus_array_len;
	uint8_t modbus_sequence[20];
	uint8_t modbus_sequence_len;
	uint8_t check_style;										
	uint16_t check_style_value;
	uint16_t check_crc_init; 
		
	#endif
}NODE_PARAMETER;


typedef struct NODE_RUNNING_FLAGS_t
{
	uint8_t tx_seq;						//Payload前10个字节中的序列号，无实际意义
	uint8_t current_work_stage;			//当前工作阶段
	bool has_received_ack;				//表示从发送到接收是否超时,1表示未超时，0表示超时
	
	uint16_t dest_mac;
	uint16_t dest_pan;
	
	uint16_t tsdc_cnt;					//时间同步周期数计数
	uint16_t cftoc_cnt;					//连续通信失败计数
	uint32_t rtdc_cnt;					//数据包重传次数计数
  uint32_t hdtc_cnt;					//历史数据次数计数
	uint32_t data_download_num;				//下载的数据总条数
	uint32_t current_data_download_piece;	//当前发送的片数
	uint32_t data_download_all_piece;		//下载的数据总片数，每片5条
	uint16_t data_download_request_control;	//数据下载请求包中的下载控制字段
	uint16_t data_download_control;			//数据下载数据包中的下载控制字段
	uint16_t data_download_rtyn_cnt;		//数据下载数据重传次数
	
	uint8_t data_type_seq_num;
	uint8_t sensor_system_state;
	
	uint64_t sensor_sample_time;
	
	uint8_t listen_router_fail_cnt;
	uint8_t sleep_max_cnt;
	
	uint8_t is_calibrate_transmit_cycle;
	
	uint32_t received_rtc_time;
	uint8_t relay_cal_transmit_duration_cnt;
}NODE_RUNNING_FLAGS;

typedef struct FIREWARE_PARAMETER_t
{
	uint8_t fireware_version[10];			//软件版本号
	uint16_t fireware_all_piece;			//文件总片数
	uint16_t fireware_piece_size;			//分片数据长度
	uint16_t fireware_crc;					//文件CRC
	uint16_t fireware_update_ctr_field;		//更新控制字段
	
	uint16_t broadcast_program_recv_piece_num;	//接收片数计数
	uint16_t broadcast_sum_bytes;
	uint16_t broadcast_recv_piece_size;		
	bool broadcast_fireware_flag;
}FIREWARE_PARAMETER;

//路由请求包中的有用信息
typedef struct ROUTER_PARAMETER_t
{
	uint16_t device_mac;		//设备地址
	uint16_t device_panid;		//设备PAN ID
	uint16_t device_info;		//设备信息
	uint8_t broadcast_period;	//广播周期
	uint8_t listen_period;		//监听时长
	int8_t rssi;				//当前路由包强度
	uint64_t received_time;		//接收到该数据包时的本地时间
}ROUTER_PARAMETER;
//路由请求包数组
#define MAX_ROUTER_NUM 10

typedef struct ROUTER_ARRAY_t
{
	ROUTER_PARAMETER router_array[MAX_ROUTER_NUM];
	uint8_t router_num;
}ROUTER_ARRAY;


typedef struct JOIN_NET_ACK_INFO
{
	//设备信息
	uint8_t device_type;						//设备类型
	uint8_t power_type;							//供电类型
	uint8_t devie_remaining_num;		//剩余可接入终端数量
	//广播周期
	uint8_t bpt;										//广播周期
	//应答信息
	uint8_t is_allow_join;					//是否允许入网
	uint8_t is_syn_time;						//是否同步
	uint8_t has_capacity;						//是否有容量
	uint8_t has_downlink_data;			//是否有下行数据
	uint8_t downlink_data_priority;	//下行数据优先级	
	//时间戳
	uint64_t current_date;	
	//广播周期起点	
	uint16_t broadcast_starting_line;	
	//以下不属于协议中内容
	//rssi
	int8_t rssi;
	uint16_t device_mac;
	uint16_t device_panid;
	uint8_t device_ack_info;				//父节点应答信息
}JOIN_NET_ACK_INFO_t;

typedef struct REQUEST_JOIN_ARRAY
{
	JOIN_NET_ACK_INFO_t request_join_array[MAX_ROUTER_NUM];
	uint8_t num;
}REQUEST_JOIN_ARRAY_t;

typedef struct FATHER_NOFO_TYPE
{
	uint16_t device_mac;			//设备MAC
	uint16_t device_pan_id;			//设备PAN ID
	uint8_t device_type;			//设备类型
	uint8_t power_type;				//供电类型
	uint8_t broadcast_period;		//广播周期
	uint8_t listen_duration;		//监听时长
	uint16_t broadcast_start_line;	//广播周期起点
	uint8_t cal_transmit_duration;
}FATHER_INFO_t;


extern NODE_PARAMETER node_parameter;
extern NODE_RUNNING_FLAGS node_running_flags;
extern FIREWARE_PARAMETER fireware_parameter;
extern ROUTER_ARRAY router_array;
extern JOIN_NET_ACK_INFO_t join_net_ack_info;	
extern REQUEST_JOIN_ARRAY_t request_join_array;	
extern FATHER_INFO_t father_info;

#define sysparam_update_items			((node_parameter.update_flag) = (((node_parameter.update_flag)==0xffffffff)?1:((node_parameter.update_flag)+1)))
#define set_default_param(x)			memcpy(&x, (uint8_t *)((uint32_t)&default_node_parameter +((uint32_t)(&x) - (uint32_t)(&node_parameter))), sizeof(x))
#define sysparam_need_update			((node_parameter.update_flag)>0)
#define clear_sysparam_update_flag		(node_parameter.update_flag = 0)

void sensor_parameter_init(void);
void update_sysparam(void);


void copy_sysparam_to_buff(uint8_t *buff);
void copy_sysparam_to_flash(uint8_t *buff);


void modify_spd_parameter(void);
void clear_router_array(void);
void clear_join_net_ack_info(void);
void clear_father_info(void);


#endif
