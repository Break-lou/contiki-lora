#ifndef __SENSOR_PAYLOAD_H__
#define __SENSOR_PAYLOAD_H__

#include <si32_device.h>
#include "sensor_sixteen.h"
#include "board_cfg.h"
#include "system_process_include.h"


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
	uint8_t pktrssi_register;
}BASIC_RF_PAYLOAD;

typedef struct RF_RX_FRAME_t
{
	uint8_t length;
	uint8_t data[MAX_RX_BUFFER];
}RF_RX_FRAME;

#if S_5TM_OPERATE 
#define num_len_overflow 0x01
#define add_data_error 0x02
#define add_data_len_error 0x03
#define data_add_error 0x04
#define data_del_error 0x05
#define num_set_ok 0x06
#define add_data_ok 0x07
#define del_data_ok 0x08
#define time_out   0x09
#define add_data_repeat 0x0a
void send_set_5tm_ack(uint8_t success);
#endif
int assamble_sensor_data_payload(uint8_t info);
int assamble_relay_data_payload(uint8_t info);
int assamble_sensor_router_payload(void);
int assamble_sensor_syntime_payload(void);
int assambel_sensor_sen_payload(void);
int assamble_sensor_config_payload(void);
void assambel_data_request_payload(void);
int assamble_data_download_payload(void);
int assamble_history_data_payload(void);
void assamble_quick_work_data_payload(uint8_t* buffer);
void assamble_join_net_request_payload(bool is_broadcast);
void assamble_communication_test_payload(void);

void transmit(void);
void send_sensor_payload(void);
void receive_payload(void);
void analyst_payload(void);
void save_sensor_data(void);

void send_calibration_ack(bool success);

void send_set_flash_ack(uint8_t success);

void send_testing(void);

extern BASIC_RF_PAYLOAD rf_send_payload;
extern BASIC_RF_PAYLOAD rf_received_payload;

#endif
