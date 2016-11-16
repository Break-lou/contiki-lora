#ifndef BROADCAST_PROGRAM_H
#define BROADCAST_PROGRAM_H

#include <stdint.h>
#include "si32_device.h"

#define BROADCAST_PROGRAM_REQUEST_PKT	0X0D
#define BROADCAST_PROGRAM_DATA_PKT	0X0E

extern uint8_t broadcast_bit_map[];

#define is_bit_map_set(x)	((broadcast_bit_map[x>>3]>>(x&0x07))&0x01)
#define set_bit_map(x)		(broadcast_bit_map[x>>3] |= (1<<(x&0x07)))//8Æ¬Ò»×é

void clear_bit_map(void);		

void broadcast_reboot(void);

void broadcast_program_init(void);

int storage_write_broadcast_program(uint8_t *buff, uint16_t piece_num, uint16_t piece_size);

uint16_t broadcast_calc_sum_crc(void);


#endif


