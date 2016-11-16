#include <stdint.h>
#include <string.h>
#include "download_history.h"
#include "ext_flash_include.h"

#define DOWNLOAD_HISTORY_TYPE	0X01

uint8_t download_type;
uint8_t download_over_operation;

uint16_t download_data_len;
uint16_t download_capacity;
uint16_t download_read;
uint16_t download_flash_index;
uint16_t download_flash_offset;

uint32_t download_history_seq = 0;
uint32_t recv_download_history_seq = 0;

extern uint32_t flash_content_bytes_num;
extern uint32_t flash_content_hex_bytes_num;
extern uint16_t capacity;
extern uint16_t read;
extern uint16_t flash_top_page;
extern uint16_t flash_page_offset;
extern uint8_t flash_cache_buff[];


void download_data_init(void)
{
	download_capacity = capacity;
	download_read = read;
	download_flash_index = flash_top_page;
	download_flash_offset = flash_page_offset;
}

bool download_cache_is_empty(void)
{
	return (download_capacity == FLASH_CACHE_BUFF_LEN);
}

uint16_t download_cache_read(uint8_t *buff, uint16_t len)
{
	uint16_t read_len = 0;
	uint16_t i = 0;
	uint16_t content = FLASH_CACHE_BUFF_LEN - download_capacity;
	if(len <= content)
	{
		read_len = len;
		download_capacity += len;
	}
	else
	{
		read_len = content;
		len = content;
		download_capacity = FLASH_CACHE_BUFF_LEN;
	}
	while(len--)
	{
		buff[i++] =  flash_cache_buff[download_read++];
		if(download_read == FLASH_CACHE_BUFF_LEN)
		{
			download_read = 0;
		}
	}
	return read_len;
}

uint16_t read_download_flash_data(uint8_t *history_data, uint16_t len)
{
	uint16_t temp_flash_page;
	uint16_t read_len = 0;
	
	memset(history_data, 0, len);
	while(len)
	{
		if(download_cache_is_empty())
		{
			if(download_flash_index > 0)
			{
				if(len < download_flash_offset)
				{
					flash_tat_read_data(download_flash_index, download_flash_offset-len, history_data, len);
					download_flash_offset -= len;
					read_len += len;
					len = 0;					
				}
				else
				{
					flash_tat_read_data(download_flash_index, 0, history_data, download_flash_offset);
					history_data += download_flash_offset;
					len -= download_flash_offset;
					read_len += download_flash_offset;
					download_flash_offset = FLASH_CACHE_BUFF_LEN;
					flash_tat_read_data(download_flash_index, FLASH_CACHE_BUFF_LEN, (uint8_t *)(&temp_flash_page), FLASH_INDEX_LEN);
					download_flash_index = temp_flash_page;				
				}			
			}
			else
			{
				break;
			}
		}
		else
		{
			read_len += download_cache_read(history_data, len);
			history_data += read_len;
			len -= read_len;			
		}
	}

	return read_len;
}

