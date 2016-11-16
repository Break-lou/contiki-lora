#ifndef DS18B20_BUS_H
#define DS18B20_BUS_H

#include <stdint.h>
#include <Si32_device.h>
#include <SI32_PBSTD_A_Type.h>
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"
#include "crc.h"
#define ds18b20_port SI32_PBSTD_0

#define ONE_WIRE_USE_PORT1_2    1
#define ONE_WIRE_USE_PORT1_3    2
#define ONE_WIRE_USE_PORT1_4    3
#define ONE_WIRE_USE_PORT1_5    4

#define ONE_WIRE_INTERFACE  ONE_WIRE_USE_PORT1_0

void delay_us(uint32_t cnt);

#if ONE_WIRE_INTERFACE == ONE_WIRE_USE_PORT1_0
#define DS18B20_BUS_PORT_LOW	SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0100)
#define DS18B20_BUS_PORT_HIGH	SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0100)
#define DS18B20_BUS_PORT_OUT	SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0100)
#define DS18B20_BUS_PORT_IN		SI32_PBSTD_A_set_pins_digital_input(ds18b20_port, 0X0100)

#define DS18B20_BUS_CLR_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0100);\
		SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0100)
#define DS18B20_BUS_SET_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0100);\
		SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0100)
#define DS18B20_BUS_GET_BUS		SI32_PBSTD_A_read_pin(ds18b20_port, 8)

#endif

#if ONE_WIRE_INTERFACE == ONE_WIRE_USE_PORT1_2
#define DS18B20_BUS_PORT_LOW	SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0004)
#define DS18B20_BUS_PORT_HIGH	SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0004)
#define DS18B20_BUS_PORT_OUT	SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0x0004)
#define DS18B20_BUS_PORT_IN		SI32_PBSTD_A_set_pins_digital_input(ds18b20_port, 0X0004)

#define DS18B20_BUS_CLR_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0004);\
		SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0004)
#define DS18B20_BUS_SET_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0004);\
		SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0004)
#define DS18B20_BUS_GET_BUS		SI32_PBSTD_A_read_pin(ds18b20_port, 2)

#endif

#if ONE_WIRE_INTERFACE == ONE_WIRE_USE_PORT1_3
#define DS18B20_BUS_PORT_LOW	SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0008)
#define DS18B20_BUS_PORT_HIGH	SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0008)
#define DS18B20_BUS_PORT_OUT	SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0x0008)
#define DS18B20_BUS_PORT_IN		SI32_PBSTD_A_set_pins_digital_input(ds18b20_port, 0X0008)

#define DS18B20_BUS_CLR_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0008);\
		SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0008)
#define DS18B20_BUS_SET_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0008);\
		SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0008)
#define DS18B20_BUS_GET_BUS		SI32_PBSTD_A_read_pin(ds18b20_port, 3)

#endif

#if ONE_WIRE_INTERFACE == ONE_WIRE_USE_PORT1_4
#define DS18B20_BUS_PORT_LOW	SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0010)
#define DS18B20_BUS_PORT_HIGH	SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0010)
#define DS18B20_BUS_PORT_OUT	SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0x0010)
#define DS18B20_BUS_PORT_IN		SI32_PBSTD_A_set_pins_digital_input(ds18b20_port, 0X0010)

#define DS18B20_BUS_CLR_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0010);\
		SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0010)
#define DS18B20_BUS_SET_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0010);\
		SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0010)
#define DS18B20_BUS_GET_BUS		SI32_PBSTD_A_read_pin(ds18b20_port, 4)

#endif

#if ONE_WIRE_INTERFACE == ONE_WIRE_USE_PORT1_5
#define DS18B20_BUS_PORT_LOW	SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0020)
#define DS18B20_BUS_PORT_HIGH	SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0020)
#define DS18B20_BUS_PORT_OUT	SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0x0020)
#define DS18B20_BUS_PORT_IN		SI32_PBSTD_A_set_pins_digital_input(ds18b20_port, 0X0020)

#define DS18B20_BUS_CLR_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0020);\
		SI32_PBSTD_A_write_pins_low(ds18b20_port, 0X0020)
#define DS18B20_BUS_SET_BUS		SI32_PBSTD_A_set_pins_push_pull_output(ds18b20_port, 0X0020);\
		SI32_PBSTD_A_write_pins_high(ds18b20_port, 0X0020)
#define DS18B20_BUS_GET_BUS		SI32_PBSTD_A_read_pin(ds18b20_port, 5)

#endif


#if DS18B20_OPERATE

void ds18b20_bus_init(void);

int ds18b20_bus_reset(void);

uint8_t ds18b20_bus_read_bit(void);

void ds18b20_bus_write_bit(uint8_t data);

uint8_t ds18b20_bus_read_byte(void);

void ds18b20_bus_write_byte(uint8_t data);
#endif
#endif

