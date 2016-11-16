#ifndef __MODBUS_H__
#define __MODBUS_H__

#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#include <stdlib.h>
#include <assert.h>

#define modbus_receive_entire_data 01
#define modbus_receive_data_piece  02

typedef struct modbus_data_structure
{
	uint8_t modbus_send_array[20];				//发送数组
	uint8_t modbus_send_sequence[20];     //发送协议的数据结构
	uint8_t modbus_receive_array[30];	    //接收数组	
	uint8_t *modbus_check_sequence[10];		//用来检验确认的协议的序列
	uint8_t modbus_check_sequence_len;		//序列长度

	uint8_t modbus_send_array_len;    //发送的缓存总长度
//	uint8_t modbus_receive_array_len; //接收的缓存总长度
	uint8_t modbus_receive_cnt;				//接送计数
	uint8_t modbus_receive_len;				//接送长度
	uint8_t modbus_receive_data_len_num;		//接收数据长度
	uint8_t modbus_receive_data_len_locat;  //接收数据的长度的具体位置
	uint8_t modbus_send_len;					//总发送数据长度
	uint8_t modbus_send_data_len;     //发送的数据信息长度 （需校验的数据信息长度）
	
	uint16_t modbus_start_data;				//起始位数据
	uint8_t modbus_start_is:1;				//是否有起始位
	uint8_t modbus_start_bit:2;			  //起始位字节个数
	
	uint16_t modbus_address;					//地址
	uint8_t modbus_address_bit:2;     //地址字节个数
	//uint8_t modbus_address_locat:3;   //地址位置

	uint16_t modbus_fun;							//功能码
	uint8_t modbus_fun_bit:2;     		//功能码字节个数
	//uint8_t modbus_fun_locat:3;				//功能码位置
	
	uint16_t modbus_reg_address;			//寄存器地址
	uint8_t modbus_reg_address_bit:2; //寄存器地址字节个数
	//uint8_t modbus_reg_address_locat:3;	//寄存器地址位置		
	
	uint16_t modbus_reg_len;					//寄存器长度
	uint8_t modbus_reg_len_bit:2;     //寄存器长度字节个数
	//uint8_t modbus_reg_len_locat:3;		//寄存器长度位置
	
	uint16_t modbus_check_data;					//校验数据
	uint8_t modbus_check_bit:2;					//校验长度字节个数			
	//uint8_t modbus_check_locat:3;				//检验长度位置
	
	uint16_t modbus_end_data;					//结束位数据
	uint8_t modbus_end_is:1;					//是否有结束位				
	uint8_t modbus_end_bit:2;
	
	uint8_t modbus_check_style;				//校验类型								
	uint16_t modbus_check_style_value;//校验类型值
	uint16_t modbus_check_init_num;   //校验数组的初始值的位置
	uint16_t modbus_check_crc_init;   //校验值
 
	uint8_t modbus_receive_data_check_len;  //接收到的数据组中获取的数据长度 (用于校验)
//	bool modbus_start_reg_bit;			//modbus协议中存在占有2个字节							
//  bool modbus_reg_len_bit;				//modbus协议中存在占有2个字节	
//	uint8_t modbus_receive_len_style; //接收到的数据长度类型判断	
//	uint8_t modbus_receive_data_check_len;  //接收到的数据组中获取的数据长度 (用于校验)
	
	
	}modbus_structure;


void open_modbus_sensor_power(void);
void modbus_uart_init(enum_uart_baudrate new_baudrate);
void modbus_port_init(void);
void modbus_uart_enable_wake_event(void);
void modbus_uart_disable_wake_event(void);
bool modbus_send_data(modbus_structure *data);
void modbus_init(modbus_structure *new_modbus);
	uint8_t modbus_strlen(uint8_t *data,uint8_t len);
uint8_t modbus_receive(uint8_t data,modbus_structure *modbus_data);
void modbus_send_data_storage(uint8_t *data,modbus_structure *modbus_data,uint8_t len);
void modbus_cfg_sequence(modbus_structure *modbus_data);
	uint8_t modbus_receive_check(modbus_structure *modbus_data);

#endif

