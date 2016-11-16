#include "ds18b20_include.h"

uint16_t temp_value;


/*
uint16_t temp_cache[MAX_DB18B20_NUM];
uint8_t temp_sign;
uint8_t temp_exist_flag = 0;

void temp_composite_format_data(void)
{
	uint8_t i = 0;
	uint8_t data_buff[7];
	
	data_buff[i++] = temp_sign;
	data_buff[i++] = (uint8_t)temp_value;
	data_buff[i++] = (uint8_t)(temp_value>>8);
	data_buff[i++] = 0;
	data_buff[i++] = 0;
	data_buff[i++] = 0;
    data_buff[i++] = 0;
	sensor_data_hex_format_insert(SOIL_TEMP_DATA_TYPE, data_buff);
}

sensor_t *ds18b20; 

sensor_operation_item_t ds18b20_operation_array[2];

void temp_attribs_init(void)
{
	ds18b20 = get_sensor_description_array();
	
	ds18b20->sen_type = SOIL_TEMP_TYPE;
	
	ds18b20->sen_pority = 1;
	ds18b20->sen_pwr = sensor_power_vbat;
	ds18b20->sen_interface = one_wire_interface;
	memcpy((ds18b20->sen_name), "DS18B20", 7);
	ds18b20->sen_name_len = 7;

	ds18b20->need_init_flag = 1;
	ds18b20->init_operation_time = 50;
	ds18b20->init_power_up_time = 10;
	ds18b20->power_on_time = 10;
	ds18b20->power_on_operation = NULL;
	ds18b20->operation_num = 2;
	ds18b20->operation_array = ds18b20_operation_array;
	
	ds18b20_operation_array[0].next_time = 750;
	ds18b20_operation_array[0].occupy_time = 10;
	ds18b20_operation_array[0].operation = temp_initial_sample;

	ds18b20_operation_array[1].next_time = 0;
	ds18b20_operation_array[1].occupy_time = 20;
	ds18b20_operation_array[1].operation = temp_read_sample;

	ds18b20->sensor_power_on_init = temp_power_on_init;
	ds18b20->composite_format_data_operation = temp_composite_format_data;
	ds18b20->sensor_power_off = NULL;
}

void temp_register(void)
{
	temp_attribs_init();
	add_sensor_to_queue(ds18b20);
}

uint8_t temp_power_on_init(void)
{
	bool search_result ;
	ds18b20_bus_init();
	DeviceNum = 0;
	while(1)
	{
		search_result = ds18b20_search_bus();
		if(search_result == false)
		{
			break;
		}
		else
		{
			temp_exist_flag = 1;
			memcpy(Devices[0], ROM_NO, sizeof(ROM_NO));
			DeviceNum++;
		}
	}
	if(DeviceNum)
	{
		return true;
	}
	return false;
}

int temp_initial_sample(void)
{
	int sample_status = 0;

	ds18b20_bus_init();
	ds18b20_initial_convert();

	return sample_status;
}

int temp_read_sample(void)
{
	int i;
	int sample_status = 0;
	for( i = 0; i < MAX_DB18B20_NUM; i++)
	{
		temp_cache[i] = 0;
	}
	for(i = 0; i < DeviceNum; i++)
	{
		ds18b20_read_temp(Devices[i], (uint8_t *)(&(temp_cache[i])));
	}
	temp_value = temp_cache[0];

	if(temp_value == 0xFFFF)
	{
		sample_status = -1;
	}
	return sample_status;
}
*/



