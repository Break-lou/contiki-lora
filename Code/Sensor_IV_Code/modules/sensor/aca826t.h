#ifndef __ACA826T_H__
#define __ACA826T_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if ACA826T_OPERATE
void aca826t_port_init(void);
void open_aca826t_sensor_power(void);
void close_aca826t_sensor_power(void);
void aca826t_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_aca826t_address(uint8_t new_address);
uint8_t set_aca826t_baudrate(enum_uart_baudrate new_baudrate);
int aca826t_sample_data(void);
uint8_t aca826t_analyster(uint8_t data);
void aca826t_uart_enable_wake_event(void);
void aca826t_uart_disable_wake_event(void);
void clear_aca826t_recv_buff(void);
uint8_t crc_aca826t_check(uint8_t *data,uint8_t len);
void set_aca826t_zero(uint8_t data);
#endif


#endif
