#ifndef CRC_H_
#define CRC_H_

#define INITIAL_VALUE 0xFFFF
#include <stdint.h>
#define modbus_check_style_crc 01
#define modbus_check_style_lrc 02
#define modbus_check_style_bcc 03
#define modbus_check_style_sum 04
#define crc_rtu_default 0XA001
#define crc_ccitt_default 0x1021
#define crc_usa_default 0x8005

uint16_t crc_ccitt_update(uint16_t crc, uint8_t data) ;

uint16_t crc_compute(uint8_t *buf, uint16_t size,uint16_t initialValue,uint8_t isLast);

uint16_t crc16_ibm_generate(uint8_t *buffer, uint16_t len,uint16_t acc,uint16_t crc_style_value);
uint16_t modbus_check_generate(uint8_t *data,uint8_t len,uint16_t acc,uint16_t check_style,uint16_t check_style_value);
#endif
