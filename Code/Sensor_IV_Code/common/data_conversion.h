#ifndef __DATA_CONVERSION_H__
#define __DATA_CONVERSION_H__



#include <stdint.h>



void ascii_to_hex_in_order(uint8_t *dest, uint8_t dest_len, uint8_t *src, uint8_t src_len);
void hex_to_ascii_in_order(uint32_t value, uint8_t *buff, uint8_t *len);
void dec_to_ascii_in_order(uint32_t value, uint8_t *buff, uint8_t *len);
void ascii_to_dec_in_order(uint8_t *dest, uint8_t dest_len, uint8_t *src, uint8_t src_len);
uint8_t ascii_to_hex(uint8_t *dest, uint8_t *src, uint8_t src_len);


#endif
