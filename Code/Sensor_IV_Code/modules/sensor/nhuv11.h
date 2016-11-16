#ifndef __NHUV11_H__
#define __NHUV11_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if NHUV11_OPERATE
void nhuv11_port_init(void);
void open_nhuv11_sensor_power(void);
void close_nhuv11_sensor_power(void);
void nhuv11_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_nhuv11_address(uint8_t new_address);
uint8_t set_nhuv11_baudrate(enum_uart_baudrate new_baudrate);
int nhuv11_sample_data(void);
uint8_t nhuv11_analyster(uint8_t data);
void nhuv11_uart_enable_wake_event(void);
void nhuv11_uart_disable_wake_event(void);
void clear_nhuv11_recv_buff(void);
uint8_t crc_nhuv11_check(uint8_t *data,uint8_t len);

#endif


#endif
