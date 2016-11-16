#ifndef __ROTONIC__
#define __ROTONIC__

#include <stdint.h>
#include "uart.h"
#include "usart.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"

#define ROTONIC_SAMPLE_CMD_LEN 9
#define ROTONIC_RECV_BUFF_LEN	120
#define ROTONIC_VALID_DATA_LEN	104
#if ROTONIC_OPERATE
extern uint8_t rotonic_temp_sign;
extern uint8_t rotonic_temp_integer;
extern uint8_t rotonic_temp_decimal;
extern uint8_t rotonic_humi_integer;
extern uint8_t rotonic_humi_decimal;
extern uint8_t rotonic_rec_cnt;
extern uint8_t rotonic_recv_buff[ROTONIC_RECV_BUFF_LEN];
void rotonic_port_init(void);
void rotonic_port_sleep(void);
void rotonic_uart_enable_wake_event(void);
void rotonic_uart_disable_wake_event(void);
void rotonic_param_init(void);
int rotonic_sample(void);
void rotonic_rec_data(uint8_t data);
void rotonic_parse_recv_data(uint8_t *recv_buff);

bool rotonic_check(uint8_t *buf,uint8_t size);

bool data_check(uint8_t cnt);

void asc_toflaot(uint8_t *buf,uint8_t size,uint8_t *integer,uint8_t *decil,uint8_t *sig);
#endif
#endif
