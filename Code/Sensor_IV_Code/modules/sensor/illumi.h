#ifndef __ILLUMI_H__
#define __ILLUMI_H__


#include "uart.h"
#include "board_cfg.h"
#include <stdint.h>
#include "usart.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#define UART_BUFFER_LEN 20


#if ILLUMI_OPERATE
//void illumi_param_init(void);
void illumi_uart_init(enum_uart_baudrate new_baudrate);
void illumi_port_init(void);
void illumi_port_sleep(void);
void open_illumi_sensor_power(void);
void close_illumi_sensor_power(void);
void illumi_uart_enable_wake_event(void);
void illumi_uart_disable_wake_event(void);
uint8_t illumi_analyster(uint8_t data);
#endif
#endif
