#ifndef __SENSOR_PAYLOAD_H__
#define __SENSOR_PAYLOAD_H__

#include <si32_device.h>
#include "sensor_sixteen.h"
#include "board_cfg.h"


typedef struct BASIC_RF_PAYLOAD_t
{
	uint8_t payload_b1;
	uint8_t payload_b2;
	uint8_t seq_num;
	uint16_t payload_dest_pan_id;
	uint16_t payload_dest_addr;
	uint16_t payload_src_addr;
	uint8_t payload_basic_size;				//基本格式中的数据长度
	
	uint8_t payload_type;       			//数据类型
    uint8_t payload_piece_num;  			//分片
    uint8_t payload_all_piece;  			//总片
    uint8_t payload[MAX_TX_BUFFER];        	//payload数据
    uint8_t payload_size;       			//payload长度
    uint8_t protoc_flag;        			//协议号
	
	uint16_t payload_crc;	

	int8_t pktrssi;
}BASIC_RF_PAYLOAD;

typedef struct RF_RX_FRAME_t
{
	uint8_t length;
	uint8_t data[MAX_RX_BUFFER];
}RF_RX_FRAME;


int assamble_sensor_data_payload(uint8_t info);
int assamble_sensor_router_payload(void);
int assamble_sensor_syntime_payload(void);
int assambel_sensor_sen_payload(void);
int assamble_sensor_config_payload(void);
void assambel_data_request_payload(void);
int assamble_data_download_payload(void);
int assamble_history_data_payload(void);
void assamble_quick_work_data_payload(uint8_t* buffer);
void assamble_join_net_request_payload(bool is_broadcast);


void transmit(void);
void send_sensor_payload(void);
void receive_payload(void);
void analyst_payload(void);
void save_sensor_data(void);

void send_calibration_ack(bool success);

extern BASIC_RF_PAYLOAD rf_send_payload;
extern BASIC_RF_PAYLOAD rf_received_payload;

#endif
