#include "ext_flash_include.h"
#include "crc.h"
#include <string.h>

/**
用于创造历史数据
**/

#ifdef STORAGE_DEBUG


static uint32_t debug_storage_time = 0x51713300;
static uint16_t debug_storage_cycle_interval = 1;
static uint16_t debug_storage_data_type = 0x0000;
static uint8_t debug_storage_battery = 0x74;
static uint16_t debug_storage_node_id = 0x5555;
static uint32_t debug_storage_hex_num = 500;
static uint8_t debug_storage_buff[16];
uint16_t debug_storage_cnt = 0;


void create_hex_sensor_data(uint8_t *buff)
{
	buff[0] = (uint8_t)(debug_storage_data_type>>8);
	buff[1] = (uint8_t)(debug_storage_data_type);
	buff[2] = (uint8_t)(debug_storage_node_id>>8);
	buff[3] = (uint8_t)(debug_storage_node_id);
	buff[4] = (uint8_t)(debug_storage_time);
	buff[5] = (uint8_t)(debug_storage_time>>8);
	buff[6] = (uint8_t)(debug_storage_time>>16);
	buff[7] = (uint8_t)(debug_storage_time>>24);
	buff[8] = 0X7b;
	buff[9] = 0X11;
	buff[10] = 0X66;	
	buff[11] = 0;	
	buff[12] = 0;	
	buff[13] = (uint8_t)debug_storage_cnt;	
	buff[14] = (uint8_t)(debug_storage_cnt>>8);	
	buff[15] = debug_storage_battery;
	debug_storage_cnt++;
	debug_storage_time += (debug_storage_cycle_interval<<2);
}

void debug_storage(void)
{
	while(debug_storage_hex_num--)
	{
		create_hex_sensor_data(debug_storage_buff);
		storage_write_data(debug_storage_buff, 16);
	}
}


#endif

