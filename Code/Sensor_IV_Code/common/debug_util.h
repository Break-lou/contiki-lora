#ifndef __DEBUG_UTIL_H__
#define __DEBUG_UTIL_H__


#include <stdio.h>
#include <si32_device.h>

void print_buff(uint8_t *buff, uint16_t size);

void printf_time(void);

uint16_t get_rand_time(uint16_t rand_value);
uint32_t get_rand_time32(uint32_t rand_value);




#endif
