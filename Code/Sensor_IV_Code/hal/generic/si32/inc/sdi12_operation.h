#ifndef SDI12_OPTION_H
#define SDI12_OPTION_H

#include <stdint.h>

#define SDI12_SENSOR_NUM_LEN 	5
#define SDI12_OUTER_LOOP_CTRL_MAX	3
#define SDI12_INNER_LOOP_CTRL_MAX	3

extern uint8_t sdi12_sensor_num;
extern uint8_t sdi12_sensor_addr_table[SDI12_SENSOR_NUM_LEN];

typedef struct sdi12_sensor_s
{
	uint8_t sdi12_sensor_addr;
	uint8_t valid_flag;
}sdi12_sensor_info;

typedef enum
{
	sdi12_travesal_state_idle,
	sdi12_travesal_state_busy,
}enum_sdi12_travesal_state;

int sdi12_traversal_sensors(uint8_t *addr);

int sdi12_sample_sensors(uint8_t addr, uint8_t crc);

int sdi12_sensor_addr_init(void);

void sdi12_bus_init(void);

#endif

