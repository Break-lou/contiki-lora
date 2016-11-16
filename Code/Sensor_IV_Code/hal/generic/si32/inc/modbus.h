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
	uint8_t modbus_send_array[20];				//��������
	uint8_t modbus_send_sequence[20];     //����Э������ݽṹ
	uint8_t modbus_receive_array[30];	    //��������	
	uint8_t *modbus_check_sequence[10];		//��������ȷ�ϵ�Э�������
	uint8_t modbus_check_sequence_len;		//���г���

	uint8_t modbus_send_array_len;    //���͵Ļ����ܳ���
//	uint8_t modbus_receive_array_len; //���յĻ����ܳ���
	uint8_t modbus_receive_cnt;				//���ͼ���
	uint8_t modbus_receive_len;				//���ͳ���
	uint8_t modbus_receive_data_len_num;		//�������ݳ���
	uint8_t modbus_receive_data_len_locat;  //�������ݵĳ��ȵľ���λ��
	uint8_t modbus_send_len;					//�ܷ������ݳ���
	uint8_t modbus_send_data_len;     //���͵�������Ϣ���� ����У���������Ϣ���ȣ�
	
	uint16_t modbus_start_data;				//��ʼλ����
	uint8_t modbus_start_is:1;				//�Ƿ�����ʼλ
	uint8_t modbus_start_bit:2;			  //��ʼλ�ֽڸ���
	
	uint16_t modbus_address;					//��ַ
	uint8_t modbus_address_bit:2;     //��ַ�ֽڸ���
	//uint8_t modbus_address_locat:3;   //��ַλ��

	uint16_t modbus_fun;							//������
	uint8_t modbus_fun_bit:2;     		//�������ֽڸ���
	//uint8_t modbus_fun_locat:3;				//������λ��
	
	uint16_t modbus_reg_address;			//�Ĵ�����ַ
	uint8_t modbus_reg_address_bit:2; //�Ĵ�����ַ�ֽڸ���
	//uint8_t modbus_reg_address_locat:3;	//�Ĵ�����ַλ��		
	
	uint16_t modbus_reg_len;					//�Ĵ�������
	uint8_t modbus_reg_len_bit:2;     //�Ĵ��������ֽڸ���
	//uint8_t modbus_reg_len_locat:3;		//�Ĵ�������λ��
	
	uint16_t modbus_check_data;					//У������
	uint8_t modbus_check_bit:2;					//У�鳤���ֽڸ���			
	//uint8_t modbus_check_locat:3;				//���鳤��λ��
	
	uint16_t modbus_end_data;					//����λ����
	uint8_t modbus_end_is:1;					//�Ƿ��н���λ				
	uint8_t modbus_end_bit:2;
	
	uint8_t modbus_check_style;				//У������								
	uint16_t modbus_check_style_value;//У������ֵ
	uint16_t modbus_check_init_num;   //У������ĳ�ʼֵ��λ��
	uint16_t modbus_check_crc_init;   //У��ֵ
 
	uint8_t modbus_receive_data_check_len;  //���յ����������л�ȡ�����ݳ��� (����У��)
//	bool modbus_start_reg_bit;			//modbusЭ���д���ռ��2���ֽ�							
//  bool modbus_reg_len_bit;				//modbusЭ���д���ռ��2���ֽ�	
//	uint8_t modbus_receive_len_style; //���յ������ݳ��������ж�	
//	uint8_t modbus_receive_data_check_len;  //���յ����������л�ȡ�����ݳ��� (����У��)
	
	
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

