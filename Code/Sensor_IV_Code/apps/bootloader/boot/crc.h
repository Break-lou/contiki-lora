#ifndef CRC_H
#define CRC_H

#include <stdint.h>

#define INITIAL_VALUE 0XFFFF
#define POLY 0x1021          

uint16_t crc_compute(uint8_t *buf, uint16_t size,uint16_t initialValue,uint8_t isLast);

#endif

