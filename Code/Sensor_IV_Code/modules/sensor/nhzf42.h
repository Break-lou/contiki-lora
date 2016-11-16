#ifndef __NHZF42_H__
#define __NHZF42_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if NHZF42_OPERATE
void nhzf42_port_init(void);
void open_nhzf42_sensor_power(void);
void close_nhzf42_sensor_power(void);
void nhzf42_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_nhzf42_address(uint8_t new_address);
uint8_t set_nhzf42_baudrate(enum_uart_baudrate new_baudrate);
int nhzf42_sample_data(void);
uint8_t nhzf42_analyster(uint8_t data);
void nhzf42_uart_enable_wake_event(void);
void nhzf42_uart_disable_wake_event(void);
void clear_nhzf42_recv_buff(void);
uint8_t crc_check(uint8_t *data,uint8_t len);


#endif

#endif
