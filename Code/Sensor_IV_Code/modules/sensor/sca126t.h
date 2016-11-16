#ifndef __SCA126T_H__
#define __SCA126T_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if SCA126T_OPERATE
void sca126t_port_init(void);
void open_sca126t_sensor_power(void);
void close_sca126t_sensor_power(void);
void sca126t_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_sca126t_address(uint8_t new_address);
uint8_t set_sca126t_baudrate(enum_uart_baudrate new_baudrate);
int sca126t_sample_data(void);
uint8_t sca126t_analyster(uint8_t data);
void sca126t_uart_enable_wake_event(void);
void sca126t_uart_disable_wake_event(void);
void clear_sca126t_recv_buff(void);
uint8_t crc_sca126t_check(uint8_t *data,uint8_t len);
uint8_t checksum(uint8_t* data,uint8_t len);
void set_sca126t_zero(uint8_t data);
#endif


#endif
