#include "sensor_parameter.h"
#include "flash_config.h"
#include "sys_event.h"
#include "sx127x_app.h"
#include "sx127x.h"
#include <stdio.h>
#include "ext_flash_include.h"
#define PARAM_BASE_ADDR 0xfc00
//敦煌部署版本V0.1幻数为0X39812351,新版本V0.2为0X39812352
#define PARAM_VALID_VALUE	0X16051111			
#define DEFAULT_UPDATE_FLAG 0x00
#define DEFAULT_PROGRAM_START_ADDR  0x00
#define DEFAULT_PROGRAM_END_ADDR 	0x00
#define DEFAULT_MAC 	0x3106
#define DEFAULT_PAN 	0x0001
#define DEFAULT_TDTI  60						//通信周期，单位s
#define DEFAULT_SSTI 	60  	 				//采样周期，单位s
#define DEFAULT_RTDC 	3						 //数据包重传次数	
#define DEFAULT_TSDC 	6						  //同步时间
#define DEFAULT_TPTO 	60						//超时时间（从发包到接收完成）
#define DEFAULT_HISN 	5							//上传历史记录条数
#define DEFAULT_HDTC  30							//上传历史纪录次数(每次的条数由HISN决定)

#define DEFAULT_CFTOC 	5						//连续多少个通信周期失败，重新请求路由					
#define DEFAULT_SPTD	500					//传感器上电时间ms（如CO2等）
#define DEFAULT_SLBD  	60					//监听路由周期
#define DEFAULT_RNRWT 	400					//最大路由时间
#define DEFAULT_SBW  	RFLR_MODEMCONFIG1_BW_500_KHZ
#define DEFAULT_SCR  	RFLR_MODEMCONFIG1_CODINGRATE_4_5
#define DEFAULT_SSF  	RFLR_MODEMCONFIG2_SF_7
#define DEFAULT_PWR		15
#define DEFAULT_FRQ		4330

#define DEFAULT_SETP	ROTONIC_TYPE//LVDT_TYPE//SKD_100D_TYPE//MLX90614//NHUV11_TYPE//NHZD10_TYPE//SCA126T_TYPE//ILLUMI_TYPE//NHFS15_TYPE
//S_5TM_TYPE//SOIL_MOISTURE//DS18B20_TYPE//NHZF42_TYPE//WATER_TYPE//MODBUS_TYPE//NHZF42_TYPE//
// WATER_TYPESOIL_MOISTURE////ACA826T_TYPE//
#define DEFAULT_DA		1
#define DEFAULT_DB		0
#define DEFAULT_SFM		2						//1——有监听，休眠时间指数增加	2——休眠一周期，监听一周期
#define DEFAULT_RCTDC 1


//利用jlink批量烧写的时候使用
//__attribute__ ((at(0x0000FC00)))


const NODE_PARAMETER default_node_parameter  = { PARAM_VALID_VALUE, 	\
												DEFAULT_UPDATE_FLAG, 	\
												DEFAULT_PROGRAM_START_ADDR, \
												DEFAULT_PROGRAM_END_ADDR, \
												DEFAULT_MAC, 	\
												DEFAULT_PAN, 	\
												DEFAULT_TDTI, 	\
												DEFAULT_SSTI, 	\
												DEFAULT_RTDC, 	\
												DEFAULT_TSDC, 	\
												DEFAULT_TPTO,	\
					 							DEFAULT_HISN, 	\
												DEFAULT_HDTC,  \
												DEFAULT_CFTOC, 	\
												DEFAULT_SPTD, 	\
												DEFAULT_SLBD,  	\
												DEFAULT_RNRWT,  \
												DEFAULT_SBW,  	\
												DEFAULT_SCR,  	\
												DEFAULT_SSF,  	\
												DEFAULT_PWR,	\
												DEFAULT_FRQ,	\
												DEFAULT_SETP,	\
												DEFAULT_DA,		\
												DEFAULT_DB,		\
												DEFAULT_SFM,  \
												DEFAULT_RCTDC
												};

NODE_PARAMETER node_parameter;
NODE_RUNNING_FLAGS node_running_flags;												
FIREWARE_PARAMETER fireware_parameter;																					
ROUTER_ARRAY router_array;		
JOIN_NET_ACK_INFO_t join_net_ack_info;												
REQUEST_JOIN_ARRAY_t request_join_array;							
FATHER_INFO_t father_info;																							
void sensor_parameter_init(void)
{

	copy_sysparam_to_buff((uint8_t *)&node_parameter);
	if(node_parameter.valid != PARAM_VALID_VALUE)
	{
		//若flash中没有该标记,将默认参数写入内部flash
		copy_sysparam_to_flash((uint8_t *)&default_node_parameter);
		copy_sysparam_to_buff((uint8_t *)&node_parameter);
		//format_flash();
	}
	//----------------------参数有效性检查
	//源地址
	if(node_parameter.MAC==0 || node_parameter.MAC>=0xFFFF )
	{
		set_default_param(node_parameter.MAC);
		sysparam_update_items;
	}
	//源PAN ID
	if(node_parameter.PAN==0 || node_parameter.PAN>=0xFFFF)
	{
		set_default_param(node_parameter.PAN);
		sysparam_update_items;
	}
	//发包周期
	if(node_parameter.TDTI==0 || node_parameter.TDTI>=0xFFFF)
	{
		set_default_param(node_parameter.TDTI);
		sysparam_update_items;
	}
	//采样周期
	if(node_parameter.SSTI==0 || node_parameter.SSTI>=1800)
	{
		set_default_param(node_parameter.SSTI);
		sysparam_update_items;
	}
	//数据包重传次数
	if(node_parameter.RTDC>10)
	{
		set_default_param(node_parameter.RTDC);
		sysparam_update_items;
	}
	if((node_parameter.HDTC>30)||(node_parameter.HDTC==0))
	{
		set_default_param(node_parameter.HDTC);
		sysparam_update_items;
	}
	//强制更新路由周期
	if(node_parameter.TSDC<1 || node_parameter.TSDC>100)
	{
		set_default_param(node_parameter.TSDC);
		sysparam_update_items;
	}
	//超时时间（从开始发包到接收完成）
	if(node_parameter.TPTO<40 || node_parameter.TPTO>3000)
	{
		set_default_param(node_parameter.TPTO);
		sysparam_update_items;
	}
	//发送历史条数
	if(node_parameter.HISN==0 || node_parameter.HISN>100)
	{
		set_default_param(node_parameter.HISN);
		sysparam_update_items;
	}
	//连续多少个通信周期失败，重新请求路由
	if(node_parameter.CFTOC<1 || node_parameter.CFTOC>16)
	{
		set_default_param(node_parameter.CFTOC);
		sysparam_update_items;
	}
	//传感器上电时间
	if(node_parameter.SPTD<1 || node_parameter.SPTD>60000)
	{
		set_default_param(node_parameter.SPTD);
		sysparam_update_items;
	}
	//监听路由周期
	if(node_parameter.SLBD<=0 || node_parameter.SLBD>600)
	{
		set_default_param(node_parameter.SLBD);
		sysparam_update_items;
	}
	//路由超时时间（从开始发包到接收完成）
	if(node_parameter.RNRWT<40 || node_parameter.RNRWT>3000)
	{
		set_default_param(node_parameter.RNRWT);
		sysparam_update_items;
	}
	if(!check_bw(node_parameter.SBW))
	{
		set_default_param(node_parameter.SBW);
		sysparam_update_items;
	}
	if(!check_cr(node_parameter.SCR))
	{
		set_default_param(node_parameter.SCR);
		sysparam_update_items;
	}
	if(!check_sf(node_parameter.SSF))
	{
		set_default_param(node_parameter.SSF);
		sysparam_update_items;
	}
	if(node_parameter.PWR>20)
	{
		set_default_param(node_parameter.PWR);
		sysparam_update_items;
	}
	if(node_parameter.FRQ < 4330 || node_parameter.FRQ > 5100)
	{
		set_default_param(node_parameter.FRQ);
		sysparam_update_items;
	}
	if(node_parameter.SETP == 0 || node_parameter.SETP > 30)
	{
		set_default_param(node_parameter.SETP);
		sysparam_update_items;
	}
	if(node_parameter.DA == 0xFFFF || node_parameter.DA == 0)
	{
		set_default_param(node_parameter.DA);
		sysparam_update_items;
	}
	if(node_parameter.DB == 0xFFFF)
	{
		set_default_param(node_parameter.DB);
		sysparam_update_items;
	}
	if(node_parameter.SFM != 1 && node_parameter.SFM != 2)
	{
		set_default_param(node_parameter.SFM);
		sysparam_update_items;
	}
	if((node_parameter.RCTDC == 0) &&( node_parameter.RCTDC < 5))
	{
		set_default_param(node_parameter.RCTDC);
		sysparam_update_items;
	}
	#if WATER_OPERATE
	if(node_parameter.WVC < -300 && node_parameter.WVC >300)
	{
		node_parameter.WVC=0;
		sysparam_update_items;
	}
	#endif
	//更新参数到flash
	if(sysparam_need_update)
	{
		clear_sysparam_update_flag;
		copy_sysparam_to_flash((uint8_t *)&node_parameter);
	}
	
	node_running_flags.tx_seq = 0;
	node_running_flags.current_work_stage = BROADCAST_JOIN_PAYLOAD_STAGE;
	node_running_flags.has_received_ack = false;
	node_running_flags.tsdc_cnt = 0;
	node_running_flags.cftoc_cnt = 0;
	node_running_flags.rtdc_cnt = 0;
	node_running_flags.hdtc_cnt=0;
	node_running_flags.data_download_rtyn_cnt = 0;
	node_running_flags.sensor_system_state = SYSTEM_STATE_WORK;
	node_running_flags.listen_router_fail_cnt=0;
	node_running_flags.relay_cal_transmit_duration_cnt=0;
	
	fireware_parameter.broadcast_program_recv_piece_num = 0;
	fireware_parameter.broadcast_recv_piece_size = 0;
	fireware_parameter.broadcast_sum_bytes = 0;
	fireware_parameter.fireware_all_piece = 0;
	fireware_parameter.fireware_crc = 0;
	fireware_parameter.fireware_piece_size = 0;
	fireware_parameter.fireware_update_ctr_field = 0;

	router_array.router_num = 0;
}


void copy_sysparam_to_buff(uint8_t *buff)
{
	read_from_flash_to_buff(PARAM_BASE_ADDR, buff, sizeof(NODE_PARAMETER));
}

void copy_sysparam_to_flash(uint8_t *buff)
{
	write_data_to_flash(PARAM_BASE_ADDR, buff, sizeof(NODE_PARAMETER));
}

void update_sysparam(void)
{
	copy_sysparam_to_flash((uint8_t *)&node_parameter);
}

void modify_spd_parameter(void)
{
	sx127x_modify_bw(node_parameter.SBW);
	sx127x_modify_cr(node_parameter.SCR);
	sx127x_modify_sf(node_parameter.SSF);
}

void clear_router_array(void)
{
	int i;
	for(i=0;i<router_array.router_num;i++)
	{
		router_array.router_array[i].broadcast_period = 0;
		router_array.router_array[i].device_info = 0;
		router_array.router_array[i].listen_period = 0;
		router_array.router_array[i].rssi = 0;
	}
	router_array.router_num = 0;
}

void clear_join_net_ack_info(void)
{
	join_net_ack_info.is_allow_join = false;
	join_net_ack_info.bpt = 0;
	join_net_ack_info.broadcast_starting_line = 0;
	join_net_ack_info.current_date = 0;
	join_net_ack_info.device_mac = 0;
	join_net_ack_info.device_panid = 0;
	join_net_ack_info.device_type = 0;
	join_net_ack_info.devie_remaining_num = 0;
	join_net_ack_info.downlink_data_priority = 0;
	join_net_ack_info.has_capacity = 0;
	join_net_ack_info.has_downlink_data = 0;
	join_net_ack_info.is_syn_time = 0;
	join_net_ack_info.power_type = 0;
	join_net_ack_info.rssi = 0;
}

void clear_father_info(void)
{
	father_info.broadcast_period = 0;
	father_info.broadcast_start_line = 0;
	father_info.device_mac = 0;
	father_info.device_pan_id = 0;
	father_info.device_type = 0;
	father_info.listen_duration = 0;
	father_info.power_type = 0;
}
