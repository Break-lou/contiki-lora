#ifndef __SKD_100D_H__
#define __SKD_100D_H__


#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#if SKD_100D_OPERATE
void skd_100d_port_init(void);
void open_skd_100d_sensor_power(void);
void close_skd_100d_sensor_power(void);
void skd_100d_uart_init(enum_uart_baudrate new_baudrate);
uint8_t set_skd_100d_address(uint8_t new_address);
uint8_t set_skd_100d_baudrate(enum_uart_baudrate new_baudrate);
int skd_100d_sample_data(void);
uint8_t skd_100d_analyster(uint8_t data);
uint8_t skd_100d_data_out(uint32_t *data);
void skd_100d_uart_enable_wake_event(void);
void skd_100d_uart_disable_wake_event(void);
void clear_skd_100d_recv_buff(void);
uint8_t crc_check(uint8_t *data,uint8_t len);


#endif

#endif
