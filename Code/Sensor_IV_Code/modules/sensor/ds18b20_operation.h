#ifndef DS18B20_OPTION_H
#define DS18B20_OPTION_H
#include <stdint.h>
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"


void temp_register(void);

int temp_initial_sample(void);

int temp_read_sample(void);

uint8_t temp_power_on_init(void);

#endif

