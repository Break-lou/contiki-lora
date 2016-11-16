#ifndef SIMULATE_I2C_H
#define SIMULATE_I2C_H

#include <stdint.h>
#include "Si32_device.h"
#include "SI32_PBSTD_A_Type.h"
#include "delay.h"
#include "board_cfg.h"

#define SIMULATE_I2C_SEND_NACK 0
#define SIMULATE_I2C_SEND_ACK   1

//SDA--PB3.0
#define SDA_PORT	SI32_PBSTD_0
#define SDA_PIN		PBX_7
#define SDA_PIN_NUM	7
//SCL--PB3.1
#define SCL_PORT	SI32_PBSTD_0
#define SCL_PIN		PBX_8

#define SIMULATE_I2C_DATA_HIGH 	SI32_PBSTD_A_set_pins_push_pull_output(SDA_PORT, SDA_PIN); \
																SI32_PBSTD_A_write_pins_high(SDA_PORT, SDA_PIN)
#define SIMULATE_I2C_DATA_LOW	SI32_PBSTD_A_set_pins_push_pull_output(SDA_PORT, SDA_PIN);\
															SI32_PBSTD_A_write_pins_low(SDA_PORT, SDA_PIN)
#define SIMULATE_I2C_DATA_OUT	SI32_PBSTD_A_set_pins_push_pull_output(SDA_PORT, SDA_PIN)
#define SIMULATE_I2C_DATA_IN	SI32_PBSTD_A_set_pins_digital_input(SDA_PORT, SDA_PIN)
#define SIMULATE_I2C_DATA			SI32_PBSTD_A_read_pin(SDA_PORT, SDA_PIN_NUM)

#define SIMULATE_I2C_SCK_HIGH	SI32_PBSTD_A_set_pins_push_pull_output(SCL_PORT, SCL_PIN); \
															SI32_PBSTD_A_write_pins_high(SCL_PORT, SCL_PIN)
#define SIMULATE_I2C_SCK_LOW	SI32_PBSTD_A_set_pins_push_pull_output(SCL_PORT, SCL_PIN); \
															SI32_PBSTD_A_write_pins_low(SCL_PORT, SCL_PIN)
#define SIMULATE_I2C_SCK_OUT	SI32_PBSTD_A_set_pins_push_pull_output(SCL_PORT, SCL_PIN)

extern void delay_Xus(uint32_t cnt);

#define delay_simulate_i2c_all()	delay_Xus(10)
#define delay_simulate_i2c_half()	delay_Xus(5)

void simulate_i2c_week(void);
void simulate_i2c_port_off(void);

void simulate_i2c_transstart(void);

void simulate_i2c_retransstart(void);

void simulate_i2c_transstop(void);

uint8_t simulate_i2c_write_byte(uint8_t value);

uint8_t simulate_i2c_read_byte(uint8_t ack);

void simulate_i2c_write_single_byte(uint8_t addr, uint8_t cmd, uint8_t value);

void simulate_i2c_write_buff(uint8_t addr, uint8_t cmd, uint8_t *buff, uint8_t len);

uint8_t simulate_i2c_read_single_byte(uint8_t addr, uint8_t cmd);

void simulate_i2c_read_mult_byte(uint8_t addr, uint8_t *buff, uint8_t len);

void simulate_i2c_write_cmd(uint8_t addr, uint8_t cmd);

void simulate_i2c_write_value_to_addr(uint8_t addr, uint8_t cmd, uint8_t value);

void simulate_i2c_write_buff_to_addr(uint8_t addr, uint8_t cmd, uint8_t *buff, uint16_t len);

void simulate_i2c_read_value_from_addr(uint8_t addr, uint8_t cmd, uint8_t *value);

uint8_t simulate_i2c_read_buff_from_addr(uint8_t addr, uint8_t cmd, uint8_t *buff, uint16_t len);

void simulate_i2c_write_bytes(uint8_t *buff, uint16_t len);
#endif

