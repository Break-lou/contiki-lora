#ifndef __NHFS15_H__
#define __NHFS15_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if NHFS15_OPERATE
void nhfs15_port_init(void);
void open_nhfs15_sensor_power(void);
void close_nhfs15_sensor_power(void);
void nhfs15_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_nhfs15_address(uint8_t new_address);
uint8_t set_nhfs15_baudrate(enum_uart_baudrate new_baudrate);
int nhfs15_sample_data(void);
uint8_t nhfs15_analyster(uint8_t data);
void nhfs15_uart_enable_wake_event(void);
void nhfs15_uart_disable_wake_event(void);
void clear_nhfs15_recv_buff(void);
uint8_t crc_nhfs15_check(uint8_t *data,uint8_t len);

#endif


#endif
