#ifndef __NHZD10_H__
#define __NHZD10_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if NHZD10_OPERATE
void nhzd10_port_init(void);
void open_nhzd10_sensor_power(void);
void close_nhzd10_sensor_power(void);
void nhzd10_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_nhzd10_address(uint8_t new_address);
uint8_t set_nhzd10_baudrate(enum_uart_baudrate new_baudrate);
int nhzd10_sample_data(void);
uint8_t nhzd10_analyster(uint8_t data);
void nhzd10_uart_enable_wake_event(void);
void nhzd10_uart_disable_wake_event(void);
void clear_nhzd10_recv_buff(void);
uint8_t crc_nhzd10_check(uint8_t *data,uint8_t len);

#endif


#endif
