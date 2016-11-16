#include "sensor_payload.h"
#include "sx127x_radio.h"
#include "debug_util.h"
#include "sensor_parameter.h"
#include "contiki.h"
#include "crc.h"
#include "delay.h"
#include "sensor_process_include.h"
#include "system_process_include.h"
#include "ext_flash_include.h"
#include "download_history.h"
#include "broadcast_program.h"
#include <string.h>
#include <stdio.h>
#include "rtc_config.h"
BASIC_RF_PAYLOAD rf_send_payload;
BASIC_RF_PAYLOAD rf_received_payload;
RF_RX_FRAME rf_rx_frame;

uint8_t operation_temp[128];        			//临时变量
//uint8_t sensor_cache_temp_buff[129];
void disassemble_rx_frame(int8_t pktrssi);



/*******************************************************************************
  * @brief save_sensor_data()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 缓存发送FIFO的数据
	 *****************************************************************************
  */
void save_sensor_data(void)
{
	if(rf_send_payload.payload_size > 4)
	{
		if(rf_send_payload.payload_type == DATA_PACKET_PAYLOAD_TYPE)
		{
			storage_write_data(rf_send_payload.payload+4, rf_send_payload.payload_size-4);
		}
	}
}
/*******************************************************************************
  * @brief clear_rf_send_payload()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 清除发送数组
	 *****************************************************************************
  */
void clear_rf_send_payload(void)
{
	rf_send_payload.payload_b1 = 0x00;
	rf_send_payload.payload_b2 = 0x00;
	rf_send_payload.payload_basic_size = 0x00;
	rf_send_payload.payload_all_piece = 0x00;
	rf_send_payload.payload_crc = 0x00;
	rf_send_payload.payload_dest_addr = 0x00;
	rf_send_payload.payload_dest_pan_id = 0x00;
	rf_send_payload.payload_piece_num = 0x00;
	rf_send_payload.payload_size = 0x00;
	rf_send_payload.payload_src_addr = 0x00;
	rf_send_payload.payload_type = 0x00;
	rf_send_payload.protoc_flag = 0x00;
	rf_send_payload.seq_num = 0x00;
	memset(rf_send_payload.payload, 0x00, MAX_TX_BUFFER);
}


////03协议装配传感器数据包
//int assamble_sensor_data_03_payload(void)
//{
//	clear_rf_send_payload();
//	
//    union BASIC_SENSOR_SIXTEEN_UNION temp_union;
//	int size = sensor_sixteen_buffer_elements();
//    if(size <= 0)
//    {
//        return 0;
//    }
//    int i;
//    rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
//	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
//	rf_send_payload.seq_num = node_running_flags.tx_seq++;
//	rf_send_payload.payload_dest_pan_id = node_parameter.dest_pan_id;
//	rf_send_payload.payload_dest_addr = node_parameter.dest_addr;
//	rf_send_payload.payload_src_addr = node_parameter.src_addr;
//	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
//	
//	rf_send_payload.payload_type = DATA_PAYLOAD_TYPE;
//    rf_send_payload.payload_piece_num = 0x01;
//    rf_send_payload.payload_all_piece = 0x01;
//    rf_send_payload.payload[0] = node_parameter.src_pan_id&0xff;           	//SINK源PANID
//    rf_send_payload.payload[1] = (node_parameter.src_pan_id>>8)&0xff;
//    for(i = 0; i < size; i++)
//    {
//        temp_union = sensor_sixteen_buffer_get();
//		if(temp_union.basic_sensor_sp.power != 0x00)
//		{
//			memcpy((rf_send_payload.payload+2)+16*i, temp_union.data, 16);  			//复制16字节数据
//		}
//		else
//		{
//			size = size - 1;
//			if(size <= 0)	return 0;
//		}
//    }
//	rf_send_payload.payload[2+16*size] = (++node_running_flags.data_type_seq_num)&0xff;
//	rf_send_payload.payload[3+16*size] = (node_running_flags.data_type_seq_num>>8)&0xff;
//	
//    rf_send_payload.payload_size = 4 + 16*size;
//    rf_send_payload.protoc_flag = PAYLOAD_FLAG;
//    
//	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
//	
//    return 1;
//}
/*******************************************************************************
  * @brief assamble_sensor_router_payload()
  * @param  
  * @retval 1
	******************************************************************************
	 @attention 装配路由请求包
	 *****************************************************************************
  */
int assamble_sensor_router_payload(void)
{
	clear_rf_send_payload();
	
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = BROADCAST_ADDR;
	rf_send_payload.payload_dest_addr = BROADCAST_ADDR;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	rf_send_payload.payload_type = ROUTER_PAYLOAD_TYPE;
	rf_send_payload.payload_piece_num = 1;
	rf_send_payload.payload_all_piece = 1;
	rf_send_payload.payload[0] = node_parameter.PAN&0xff;
	rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	rf_send_payload.payload_size = 2;
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
	
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	return 1;
}
////装配时间请求包
//int assamble_sensor_syntime_payload(void)
//{
//	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
//	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
//	rf_send_payload.seq_num = node_running_flags.tx_seq++;
//	rf_send_payload.payload_dest_pan_id = node_parameter.dest_pan_id;
//	rf_send_payload.payload_dest_addr = node_parameter.dest_addr;
//	rf_send_payload.payload_src_addr = node_parameter.src_addr;
//	
//	rf_send_payload.payload_type = SYNTIME_PAYLOAD_TYPE;
//	rf_send_payload.payload_piece_num = 1;
//	rf_send_payload.payload_all_piece = 1;
//	rf_send_payload.payload[0] = node_parameter.src_pan_id&0xff;
//	rf_send_payload.payload[1] = (node_parameter.src_pan_id>>8)&0xff;
//	rf_send_payload.payload_size = 2;
//	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
//	
//	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
//	
//	return 1;
//}
/*******************************************************************************
  * @brief assamble_sensor_config_payload()
  * @param  
  * @retval 1
	******************************************************************************
	 @attention 装配配置包
	 *****************************************************************************
  */
int assamble_sensor_config_payload(void)
{
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = 0xFFFF;
	rf_send_payload.payload_dest_addr = 0xFFFF;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	
	rf_send_payload.payload_type = CONFIG_PAYLOAD_TYPE | 0x80;
	rf_send_payload.payload_piece_num = 1;
	rf_send_payload.payload_all_piece = 1;
	//除payload装配
	
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
	
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	return 1;
}
/*******************************************************************************
  * @brief assambel_sensor_sen_payload()
  * @param  
  * @retval 1
	******************************************************************************
	 @attention 装配自检包
	 *****************************************************************************
  */
int assambel_sensor_sen_payload(void)
{
	clear_rf_send_payload();
	
	union BASIC_SENSOR_SIXTEEN_UNION temp_union;
	int size = sensor_sixteen_buffer_elements();
    if(size <= 0)
    {
        return 0;
    }
    int i;
    rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = 0xFFFF;
	rf_send_payload.payload_dest_addr = 0xFFFF;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	rf_send_payload.payload_type = SEN_DATA_TYPE;
    rf_send_payload.payload_piece_num = 0x01;
    rf_send_payload.payload_all_piece = 0x01;
    for(i = 0; i < size; i++)
    {
        temp_union = sensor_sixteen_buffer_get();
        memcpy((rf_send_payload.payload + 16*i), temp_union.data, 16);  			//复制16字节数据
    }
	rf_send_payload.payload[16*size] = (++node_running_flags.data_type_seq_num)&0xff;
	rf_send_payload.payload[1+16*size] = (node_running_flags.data_type_seq_num>>8)&0xff;
	
    rf_send_payload.payload_size = 2 + 16*size;
    rf_send_payload.protoc_flag = PAYLOAD_FLAG;
    
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	return 1;
}
/*******************************************************************************
  * @brief assambel_data_request_payload()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 装配数据下载请求包
	 *****************************************************************************
  */
void assambel_data_request_payload(void)
{
	clear_rf_send_payload();
	
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = 0xFFFF;
	rf_send_payload.payload_dest_addr = 0xFFFF;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	
	rf_send_payload.payload_type = DATA_DOWNLOAD_REQUEST_TYPE | 0x80;
	rf_send_payload.payload_piece_num = 1;
	rf_send_payload.payload_all_piece = 1;
	rf_send_payload.payload[0] = 0x01;
	rf_send_payload.payload[1] = node_running_flags.data_download_num&0xff;
	rf_send_payload.payload[2] = (node_running_flags.data_download_num>>8)&0xff;
	rf_send_payload.payload[3] = (node_running_flags.data_download_num>>16)&0xff;
	rf_send_payload.payload[4] = (node_running_flags.data_download_num>>24)&0xff;
	rf_send_payload.payload_size = 5;
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
}
/*******************************************************************************
  * @brief assamble_data_download_payload()
  * @param  
  * @retval 0 or 1
	******************************************************************************
	 @attention 装配数据下载数据包
	 *****************************************************************************
  */
int assamble_data_download_payload(void)
{
	clear_rf_send_payload();
	
    uint16_t len = read_download_flash_data(rf_send_payload.payload+6, 16*DATA_DOWNLOAD_PER_NUM);
	if(len <= 0)
	{
		return 0;
	}
    
    rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = 0xFFFF;
	rf_send_payload.payload_dest_addr = 0xFFFF;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
    
    rf_send_payload.payload_type = DATA_DOWNLOAD_DATA_TYPE;
	rf_send_payload.payload_piece_num = 1;
	rf_send_payload.payload_all_piece = 1;
    node_running_flags.current_data_download_piece++;
	rf_send_payload.payload[0] = 0x01;		//传感器数据
	rf_send_payload.payload[1] = 0x00;		//附属信息长度
    rf_send_payload.payload[2] = node_running_flags.current_data_download_piece&0xff;
	rf_send_payload.payload[3] = (node_running_flags.current_data_download_piece>>8)&0xff;
	rf_send_payload.payload[4] = (node_running_flags.current_data_download_piece>>16)&0xff;
	rf_send_payload.payload[5] = (node_running_flags.current_data_download_piece>>24)&0xff;
    
    rf_send_payload.payload_size = 6 + len;
	
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	return 1;
}
////装配历史数据包--0x03协议
//int assamble_history_data_03_payload(void) 
//{
//	clear_rf_send_payload();
//	
//	uint16_t len = storage_read_data(rf_send_payload.payload+2, 16*node_parameter.hisn);
//	if(len <= 0)
//	{
//		return 0;
//	}
//	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
//	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
//	rf_send_payload.seq_num = node_running_flags.tx_seq++;
//	rf_send_payload.payload_dest_pan_id = node_parameter.dest_pan_id;
//	rf_send_payload.payload_dest_addr = node_parameter.dest_addr;
//	rf_send_payload.payload_src_addr = node_parameter.src_addr;
//	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
//	
//	rf_send_payload.payload_type = DATA_PAYLOAD_TYPE;
//    rf_send_payload.payload_piece_num = 0x01;
//    rf_send_payload.payload_all_piece = 0x01;
//    rf_send_payload.payload[0] = node_parameter.src_pan_id&0xff;           	//SINK源PANID
//    rf_send_payload.payload[1] = (node_parameter.src_pan_id>>8)&0xff;
//	rf_send_payload.payload[2+len] = (++node_running_flags.data_type_seq_num)&0xff;
//	rf_send_payload.payload[3+len] = (node_running_flags.data_type_seq_num>>8)&0xff;
//    rf_send_payload.payload_size = 4 + len;
//	
//    rf_send_payload.protoc_flag = PAYLOAD_FLAG;
//    
//	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;

//	return 1;
//}
/*******************************************************************************
  * @brief assamble_quick_work_data_payload()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 装配快速工作数据包
	 *****************************************************************************
  */
void assamble_quick_work_data_payload(uint8_t* buffer)
{
	clear_rf_send_payload();
	
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = 0xFFFF;
	rf_send_payload.payload_dest_addr = 0xFFFF;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	rf_send_payload.payload_type = DATA_PAYLOAD_TYPE;
    rf_send_payload.payload_piece_num = 0x01;
    rf_send_payload.payload_all_piece = 0x01;
    rf_send_payload.payload[0] = node_parameter.PAN&0xff;           	//SINK源PANID
    rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	
	memcpy(rf_send_payload.payload+2, buffer, 16);  			//复制16字节数据
	
	rf_send_payload.payload[2+16] = (++node_running_flags.data_type_seq_num)&0xff;
	rf_send_payload.payload[3+16] = (node_running_flags.data_type_seq_num>>8)&0xff;
	
	rf_send_payload.payload_size = 4 + 16;
    rf_send_payload.protoc_flag = PAYLOAD_FLAG;
    
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
}
/*******************************************************************************
  * @brief assamble_join_net_request_payload()
  * @param  is_broadcast：广播包或者指定包
  * @retval 
	******************************************************************************
	 @attention 装配入网请求包 
	 *****************************************************************************
  */
void assamble_join_net_request_payload(bool is_broadcast)
{
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	if(is_broadcast){
		rf_send_payload.payload_dest_pan_id = BROADCAST_ADDR;
		rf_send_payload.payload_dest_addr = BROADCAST_ADDR;
	}else{
		rf_send_payload.payload_dest_pan_id = father_info.device_pan_id;
		rf_send_payload.payload_dest_addr = father_info.device_mac;
	}
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	
	rf_send_payload.payload_type = JOIN_NET_REQUEST_PAYLOAD_TYPE;
	rf_send_payload.payload_piece_num = 0x01;
    rf_send_payload.payload_all_piece = 0x01;
	
	//源设备PAN ID
	rf_send_payload.payload[0] = node_parameter.PAN&0xff;
	rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	//入网者信息：每项由 类型+长度+内容 构成
	rf_send_payload.payload[2] = 0x01;		//设备类型
	rf_send_payload.payload[3] = 0x01;
	rf_send_payload.payload[4] = 0x03;
	
	rf_send_payload.payload[5] = 0x02;
	rf_send_payload.payload[6] = 0x02;
	rf_send_payload.payload[7] = node_parameter.SSTI&0xff;
	rf_send_payload.payload[8] = (node_parameter.SSTI>>8)&0xff;
	
	rf_send_payload.payload_size = 9;
	
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
}
/*******************************************************************************
  * @brief assamble_sensor_data_payload()
  * @param  info：设备信息
  * @retval 
	******************************************************************************
	 @attention 装配数据通信包 
	 *****************************************************************************
  */
 int assamble_sensor_data_payload(uint8_t info)
{
	union BASIC_SENSOR_SIXTEEN_UNION temp_union;
	int size = sensor_sixteen_buffer_elements();//有没有数据根据NUM来判断  
	if(size <= 0)
	{
			return 0;
	}
	int i;
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = node_running_flags.dest_pan;
	rf_send_payload.payload_dest_addr = node_running_flags.dest_mac;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	rf_send_payload.payload_type = DATA_PACKET_PAYLOAD_TYPE;
	rf_send_payload.payload_piece_num = 0x01;
	rf_send_payload.payload_all_piece = 0x01;
	rf_send_payload.payload[0] = node_parameter.PAN&0xff;           				//SINK源PANID
	rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	rf_send_payload.payload[2] = info;
	rf_send_payload.payload[3] = (++node_running_flags.data_type_seq_num)&0xff;
	uint8_t real_size = size;
	uint8_t real_index = 0;
	for(i = 0; i < size; i++)
	{
			temp_union = sensor_sixteen_buffer_get();//num--
			if(temp_union.basic_sensor_sp.power != 0x00)
			{
				real_index++;
				memcpy((rf_send_payload.payload+4)+16*(real_index-1), temp_union.data, 16);  			//复制16字节数据
				
			}
			else
			{
				real_size--;
				if(real_size <= 0)	return 0;
			}
	}
	
	rf_send_payload.payload_size = 4 + 16*real_size;
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
    
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
  return 1;
}
/*******************************************************************************
  * @brief assamble_relay_data_payload()
  * @param  info：设备信息
  * @retval 
	******************************************************************************
	 @attention 节点--中继通信信息数据包 
	 *****************************************************************************
  */
 int assamble_relay_data_payload(uint8_t info)
{
	union BASIC_SENSOR_SIXTEEN_UNION temp_union;
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = node_running_flags.dest_pan;
	rf_send_payload.payload_dest_addr = node_running_flags.dest_mac;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
	rf_send_payload.payload_type = DATA_PACKET_PAYLOAD_TYPE;
	rf_send_payload.payload_piece_num = 0x01;
	rf_send_payload.payload_all_piece = 0x01;
	rf_send_payload.payload[0] = node_parameter.PAN&0xff;           				//SINK源PANID
	rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	rf_send_payload.payload[2] = info;
	rf_send_payload.payload[3] = (++node_running_flags.data_type_seq_num)&0xff;
	temp_union.basic_sensor_sp.type=0x03;
	temp_union.basic_sensor_sp.jump=0;
	temp_union.basic_sensor_sp.data_type=0xf0;
	temp_union.basic_sensor_sp.node_id=node_parameter.MAC;
	temp_union.basic_sensor_sp.timestamp=get_upload_time();
	memset(temp_union.basic_sensor_sp.value,0x00,7);
	temp_union.basic_sensor_sp.power=0; 
	memcpy((rf_send_payload.payload+4), temp_union.data, 16);  			//复制16字节数据
	rf_send_payload.payload_size = 4 + 16;
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
    
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	
  return 1;
}
/*******************************************************************************
  * @brief assamble_history_data_payload()
  * @param  0 or 1
  * @retval 
	******************************************************************************
	 @attention 装配历史数据包
	 *****************************************************************************
  */
int assamble_history_data_payload(void)
{
	
	uint16_t len = storage_read_data(rf_send_payload.payload+4, 16*node_parameter.HISN);
	#if HISTORY_NONE
	len=0;
	#endif
	if(len <= 0)
	{
		return 0;
	}
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = node_running_flags.dest_pan;
	rf_send_payload.payload_dest_addr = node_running_flags.dest_mac;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	
	rf_send_payload.payload_type = DATA_PACKET_PAYLOAD_TYPE;
    rf_send_payload.payload_piece_num = 0x01;
    rf_send_payload.payload_all_piece = 0x01;
    rf_send_payload.payload[0] = node_parameter.PAN&0xff;           	//SINK源PANID
    rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	rf_send_payload.payload[2] = 0x00;
	rf_send_payload.payload[3] = (++node_running_flags.data_type_seq_num)&0xff;
	
    rf_send_payload.payload_size = 4 + len;
	
    rf_send_payload.protoc_flag = PAYLOAD_FLAG;
    
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;

	return 1;
}
/*******************************************************************************
  * @brief assamble_communication_test_payload()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 装配通信测试包
	 *****************************************************************************
  */
void assamble_communication_test_payload(void)
{
	rf_send_payload.payload_b1 = DEFAULT_PAYLOAD_B1;
	rf_send_payload.payload_b2 = DEFAULT_PAYLOAD_B2;
	rf_send_payload.seq_num = node_running_flags.tx_seq++;
	rf_send_payload.payload_dest_pan_id = 0xFFFF;
	rf_send_payload.payload_dest_addr = 0xFFFF;
	rf_send_payload.payload_src_addr = node_parameter.MAC;
	
	rf_send_payload.payload_type = COMUNICATION_PACKET_PAYLOAD_TYPE;
	rf_send_payload.payload_piece_num = 0x01;
    rf_send_payload.payload_all_piece = 0x01;
	rf_send_payload.payload[0] = node_parameter.PAN&0xff;
	rf_send_payload.payload[1] = (node_parameter.PAN>>8)&0xff;
	rf_send_payload.payload[2] = c_infos.g_num;
	rf_send_payload.payload_size = 3;
	int i;
	for(i=0;i<c_infos.g_num;i++)
	{
		rf_send_payload.payload[3+i*4] = (c_infos.c_info[i].g_mac)&0xff;
		rf_send_payload.payload[4+i*4] = ((c_infos.c_info[i].g_mac>>8))&0xff;
		rf_send_payload.payload[5+i*4] = c_infos.c_info[i].n_sensitivity;
		rf_send_payload.payload[6+i*4] = c_infos.c_info[i].g_sensitivity;
		rf_send_payload.payload_size += 4;
	}
	
	rf_send_payload.payload_basic_size = 4 + rf_send_payload.payload_size;
	rf_send_payload.protoc_flag = PAYLOAD_FLAG;
}
/*******************************************************************************
  * @brief send_calibration_ack()
  * @param  success
  * @retval 
	******************************************************************************
	 @attention 发送标定完成ACK
	 *****************************************************************************
  */
void send_calibration_ack(bool success)
{
	rf_send_payload.payload[0] = 0x01;
	if(success)
	{
		memcpy(rf_send_payload.payload+1, "+SCB:OK", 7);
	}
	else
	{
		memcpy(rf_send_payload.payload+1, "+SCB:ER", 7);
	}
	rf_send_payload.payload_size = 8;
	assamble_sensor_config_payload();
	transmit();
}
/*******************************************************************************
  * @brief send_set_flash_ack()
  * @param  success
  * @retval 
	******************************************************************************
	 @attention 发送设置FLASH完成ACK
	 *****************************************************************************
  */
void send_set_flash_ack(uint8_t success)
{
	memset(&rf_send_payload,0,sizeof(BASIC_RF_PAYLOAD));
	rf_send_payload.payload[0] = 0x01;
	if(success)
	{
		memcpy(rf_send_payload.payload+1, "+FSRC:OK;", 8);
		rf_send_payload.payload_size =9;
	}
	else
	{
		memcpy(rf_send_payload.payload+1, "+FSRC:ER;", 8);
		rf_send_payload.payload_size =9;
	}
	assamble_sensor_config_payload();
	transmit();
}
#if S_5TM_OPERATE 
void send_set_5tm_ack(uint8_t success)
{
	memset(&rf_send_payload,0,sizeof(BASIC_RF_PAYLOAD));
	rf_send_payload.payload[0] = 0x01;
	switch(success)
	{
		case num_len_overflow:
			memcpy(rf_send_payload.payload+1, "+NUM_LEN:OVER", 13);
			rf_send_payload.payload_size =14;
			break;
		case add_data_error:
			memcpy(rf_send_payload.payload+1, "+ADD_DATA:ERROR", 15);
			rf_send_payload.payload_size =16;
			break;
		case add_data_len_error://
			memcpy(rf_send_payload.payload+1, "+ADD_DATA_LEN:ERROR", 19);
			rf_send_payload.payload_size =20;
			break;
		case data_add_error:
			memcpy(rf_send_payload.payload+1, "+DATA_ADD:ERROR", 15);
			rf_send_payload.payload_size =16;
			break;
		case data_del_error://
			memcpy(rf_send_payload.payload+1, "+DATA_DEL:ERROR", 15);
			rf_send_payload.payload_size =16;
			break;
		case num_set_ok:
			memcpy(rf_send_payload.payload+1, "+NUM_SET:OK", 11);
			rf_send_payload.payload_size =12;
			break;
		case add_data_ok:
			memcpy(rf_send_payload.payload+1, "+ADD_DATA:OK", 12);
			rf_send_payload.payload_size =13;
			break;
		case del_data_ok://
			memcpy(rf_send_payload.payload+1, "+DEL_DATA:OK", 12);
			rf_send_payload.payload_size =13;
			break;
		case time_out:
			memcpy(rf_send_payload.payload+1, "+TIME_OUT", 9);
			rf_send_payload.payload_size =10;
			break;
		case add_data_repeat://
			memcpy(rf_send_payload.payload+1, "+ADD_DATA_REPEAT", 16);
			rf_send_payload.payload_size =17;
			break;
		default:
			return;
	}
	assamble_sensor_config_payload();
	transmit();
}
#endif
//void send_testing(void)
//{
//	LED_GREEN_ON;
//	RadioDriver.SetTxPacket("0x55", 1);
//}

/*******************************************************************************
  * @brief send_sensor_payload()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 发送传感器载荷
	 *****************************************************************************
  */
void send_sensor_payload(void)
{
	uint16_t calc_crc;
	operation_temp[0] = rf_send_payload.payload_b1;
	operation_temp[1] = rf_send_payload.payload_b2;
	operation_temp[2] = rf_send_payload.seq_num;
	operation_temp[3] = rf_send_payload.payload_dest_pan_id & 0xff;
	operation_temp[4] = (rf_send_payload.payload_dest_pan_id >> 8) & 0xff;
	operation_temp[5] = rf_send_payload.payload_dest_addr & 0xff;
	operation_temp[6] = (rf_send_payload.payload_dest_addr >> 8) & 0xff;
	operation_temp[7] = rf_send_payload.payload_src_addr & 0xff;
	operation_temp[8] = (rf_send_payload.payload_src_addr >> 8) & 0xff;
	operation_temp[9] = rf_send_payload.payload_basic_size;					//载荷基本格式长度
	
	operation_temp[10] = rf_send_payload.payload_type;
    operation_temp[11] = rf_send_payload.payload_piece_num;
    operation_temp[12] = rf_send_payload.payload_all_piece;
    memcpy(operation_temp + 13, rf_send_payload.payload, rf_send_payload.payload_size);
    operation_temp[13+rf_send_payload.payload_size] = rf_send_payload.protoc_flag;
	
	calc_crc = crc_compute(operation_temp, 14+rf_send_payload.payload_size, INITIAL_VALUE, 1);
	rf_send_payload.payload_crc = calc_crc;
	
	operation_temp[14+rf_send_payload.payload_size] = calc_crc&0xff;
	operation_temp[15+rf_send_payload.payload_size] = (calc_crc>>8)&0xff;
	#if DEBUG_PRINT
		// print for debug
		printf("send payload is: ");
		print_buff(operation_temp, 16+rf_send_payload.payload_size);
	#endif
    RadioDriver.SetTxPacket(operation_temp, 16+rf_send_payload.payload_size);			//	
}
/*******************************************************************************
  * @brief receive_payload()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 接收数据
	 *****************************************************************************
  */
void receive_payload(void)
{
	// 从缓存中读取数据
	RadioDriver.GetRxPacket(rf_rx_frame.data, &rf_rx_frame.length);
	int8_t pktrssi = RadioDriver.GetRssi();
	#if DEBUG_PRINT+JOIN_NET_DEBUG
		printf("received frame: ");
		printf("rssi = %d \n", pktrssi);
		print_buff(rf_rx_frame.data, rf_rx_frame.length);
	#endif
	disassemble_rx_frame(pktrssi);
}
/*******************************************************************************
  * @brief disassemble_rx_frame()
  * @param  pktrssi
  * @retval 
	******************************************************************************
	 @attention 解析原始数据帧
	 *****************************************************************************
  */
void disassemble_rx_frame(int8_t pktrssi)
{
	uint16_t calc_crc;
	if(rf_rx_frame.length < 16)
	{
		#if DEBUG_PRINT
			printf("rx frame len short, rx len = %x \n", rf_rx_frame.length);
		#endif
		return;
	}
	
	rf_received_payload.payload_crc = *(uint16_t *)&(rf_rx_frame.data[rf_rx_frame.length-2]);
	calc_crc = crc_compute(rf_rx_frame.data, rf_rx_frame.length-2, INITIAL_VALUE, 1);
	if(rf_received_payload.payload_crc != calc_crc)
	{
		#if DEBUG_PRINT
			printf("crc error, received crc = %x, calc crc = %x \n", rf_received_payload.payload_crc, calc_crc);
		#endif
		return;
	}
	
	rf_received_payload.payload_b1 = rf_rx_frame.data[0];
	rf_received_payload.payload_b2 = rf_rx_frame.data[1];
	rf_received_payload.payload_dest_pan_id = *(uint16_t *)&(rf_rx_frame.data[3]);
	rf_received_payload.payload_dest_addr = *(uint16_t *)&(rf_rx_frame.data[5]);
	rf_received_payload.payload_src_addr = *(uint16_t *)&(rf_rx_frame.data[7]);
	rf_received_payload.payload_basic_size = rf_rx_frame.data[9];
	
	if(rf_received_payload.payload_dest_pan_id == node_parameter.PAN
		|| rf_received_payload.payload_dest_pan_id == BROADCAST_ADDR)
	{
		if(rf_received_payload.payload_dest_addr == node_parameter.MAC
			|| rf_received_payload.payload_dest_addr == BROADCAST_ADDR)
		{
			rf_received_payload.payload_type = rf_rx_frame.data[10];
			rf_received_payload.payload_piece_num = rf_rx_frame.data[11];
			rf_received_payload.payload_all_piece = rf_rx_frame.data[12];
			memcpy(rf_received_payload.payload, rf_rx_frame.data+13, rf_rx_frame.length-16);
			rf_received_payload.payload_size = rf_rx_frame.length - 16;
			rf_received_payload.protoc_flag = rf_rx_frame.data[rf_rx_frame.length-3];
			rf_received_payload.pktrssi = pktrssi;
			
			rf_received_payload.pktrssi_register = RadioDriver.GetPktRssiRegister();		//快速工作模式下获取PKT RSSI寄存器值
			
            if(rf_received_payload.protoc_flag == PAYLOAD_FLAG)
            {
                //协议号为0x0B的协议
                process_post(&analysis_process, ANALYSIS_0B_PAYLOAD, NULL);
            }
		}
	}
	else
	{
		#if DEBUG_PRINT
			printf("dest addr or dest pan id is not correct \n");
		#endif
	}
}



