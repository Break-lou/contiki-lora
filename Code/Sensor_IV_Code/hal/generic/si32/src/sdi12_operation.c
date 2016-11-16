#include "sdi12_include.h"

uint8_t sdi12_sensor_addr_table[SDI12_SENSOR_NUM_LEN] = {'1', '2', '3'};
sdi12_sensor_info sdi12_sensor_list[SDI12_SENSOR_NUM_LEN];
uint8_t sdi12_sensor_num = 1;
uint8_t sdi12_sensor_invalid_num = 0;
uint32_t sdi12_sensor_reactive_limit = 5;
uint32_t sdi12_sensor_active_cnt = 5;
uint8_t sdi12_sensor_traversal_index = 0;
uint8_t sdi12_reactive_lock = 0;

enum_sdi12_travesal_state sdi12_travesal_state;

/*
void sdi12_bus_init(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_1);
	usart_disable_crossbar();	
	usart_off();		
	SDI12_RELEASE_BUS();
}
*/

int sdi12_sensor_addr_init(void)
{
	int ret = 0;
	uint8_t i, addr;
	uint8_t list_i = 0;
	sdi12_sensor_invalid_num = 0;
	sdi12_param_init();
	for(i = 0; i < sdi12_sensor_num; i++)
	{
		addr = sdi12_sensor_addr_table[i];
		ret = sdi12_is_sensor_active(addr);
		if(!ret)
		{
			sdi12_sensor_list[list_i++].sdi12_sensor_addr = addr;
			sdi12_sensor_invalid_num++;
		}
	}
	return 0;
}

int sdi12_traversal_sensors(uint8_t *addr)
{
	int ret = -1;

	if(sdi12_sensor_traversal_index < sdi12_sensor_invalid_num)
	{
		ret = sdi12_sample_sensors(sdi12_sensor_list[sdi12_sensor_traversal_index].sdi12_sensor_addr, 1);
		sdi12_sensor_traversal_index++;
		*addr = sdi12_sensor_list[sdi12_sensor_traversal_index].sdi12_sensor_addr;
	}
	else
	{
		sdi12_sensor_traversal_index = 0;
		sdi12_reactive_lock = 0;
	//	while(1);
	}				

	return ret;
}


int sdi12_sample_sensors(uint8_t addr, uint8_t crc)
{
	int ret = -1;
	uint32_t time;
	uint8_t *cmd;
	uint8_t len;
//	usart_disable_crossbar();	
//	usart_off();
	sdi12_break();
	sdi12_marking();
	sdi12_enable_tx_crossbar();
	if(crc)
	{
		cmd = sdi12_measure_crc_command;
		len = SDI12_MEASURE_CRC_COMMAND_LEN;
		time = 200;
	}
	else
	{
		cmd = sdi12_measure_command;
		len = SDI12_MEASURE_COMMAND_LEN;
		time = 200;
	}
	
	sdi12_send_command(addr, cmd, len);
	if(!sdi12_recv_response(sdi12_recv_buff, &sdi12_recv_len, 80))
	{
		if(!sdi12_recv_response(sdi12_recv_buff, &sdi12_recv_len, 150))
		{
			sdi12_marking();
			sdi12_send_command(addr, sdi12_data_command, SDI12_DATA_COMMAND_LEN);
			if(!sdi12_recv_response(sdi12_recv_buff, &sdi12_recv_len, time))
			{
				ret = 0;
			}
			else
			{
				ret = -1;
			}
		}
		else
		{
			ret = -1;
		}
	}
	else
	{
		ret = -1;
	}

	//uart_disable_crossbar();	
	SDI12_RELEASE_BUS();
	return ret;
}



