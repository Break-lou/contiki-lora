#ifndef __LVDT_H__
#define __LVDT_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if LVDT_OPERATE
extern uint8_t lvdt_recv_buff[];
void lvdt_port_init(void);
void lvdt_port_sleep(void);
void open_lvdt_power(void);

void CloseRs485(void);

void lvdt_uart_init(enum_uart_baudrate new_baudrate);

void lvdt_read_distance_value(uint8_t addr);
void lvdt_uart_enable_wake_event(void);
void lvdt_uart_disable_wake_event(void);
//void operate_LVDT(void);

void close_lvdt_power(void);

void disoperate_LVDT(void);

void lvdt_analyster(uint8_t data);
#endif
#endif
