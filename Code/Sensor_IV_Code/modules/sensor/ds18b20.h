#ifndef DS18B20_H
#define DS18B20_H

#include <stdint.h>
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#define MAX_DB18B20_NUM	3

#define DS18B20_READ_ROM             0x33
#define DS18B20_MATCH_ROM            0X55
#define DS18B20_SKIP_ROM             0XCC
#define DS18B20_SEARCH_ROM           0XF0
#define DS18B20_ALARM_SEARCH_ROM     0XEC
#define DS18B20_WRITE_RAM            0X40
#define DS18B20_READ_RAM             0XBE
#define DS18B20_COPY_RAM             0X48
#define DS18B20_CONVERT_TEM          0X44
#define DS18B20_EECALL_EEPROM        0XB8
#define DS18B20_READ_POWER_SUPPLY    0XB4
#if DS18B20_OPERATE
extern uint8_t Devices[MAX_DB18B20_NUM][8];
extern uint8_t DeviceNum;
extern uint8_t ROM_NO[8];

bool ds18b20_search_bus(void);

uint16_t defualt_ds18b20_read_temp( void ); 

int ds18b20_initial_convert(void);

uint16_t ds18b20_calc_temperature(uint8_t *t);

int ds18b20_read_temp( uint8_t *address , uint8_t *t );

#endif
#endif

