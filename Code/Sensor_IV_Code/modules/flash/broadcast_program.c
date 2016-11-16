#include <stdint.h>
#include <string.h>
#include "broadcast_program.h"
#include "ext_flash_include.h"
#include "sensor_iv_boot.h"
#include "sensor_parameter.h"
#include "crc.h"
#include "wdtimer_config.h"


extern uint16_t flash_program_start_page;
extern uint8_t flash_cache_temp_buff[];


uint16_t broadcast_flash_index;
uint16_t broadcast_program_total_crc;
uint16_t broadcast_program_calculated_crc = 0XFFFF;

uint8_t broadcast_bit_map[128];		//标志位
uint8_t broadcast_program_buff[256];

void reset_broadcast_parameter(void);

void clear_bit_map(void)		
{
	memset(broadcast_bit_map, 0, sizeof(broadcast_bit_map));
}	

void broadcast_program_init(void)
{
	broadcast_program_total_crc = 0;
	clear_bit_map();
}

void get_broadcast_bit(uint16_t *start_bit, uint16_t *end_bit, uint16_t page, uint16_t piece_size)
{
	uint16_t start_bit_temp,end_bit_temp;
	uint32_t start_bytes = (page<<8);
	uint32_t end_bytes = ((page+1)<<8);
	start_bit_temp = start_bytes/piece_size;
	start_bit_temp += 1;
	
	end_bit_temp = end_bytes/piece_size;
	if(end_bit_temp*piece_size < end_bytes)
		end_bit_temp += 1;
	*start_bit = start_bit_temp;
	*end_bit = end_bit_temp;	
}

//无线广播烧写
int storage_write_broadcast_program(uint8_t *buff, uint16_t piece_num, uint16_t piece_size)
{
	uint32_t start_bytes = (piece_num-1) * piece_size;//每个分片的起始位
	uint16_t start_page = (start_bytes>>8);//起始位在哪个页中
	uint16_t start_offset = (start_bytes&0xff);// 页中的位置
	uint16_t start_bit,end_bit;
	uint16_t write_size;
	uint16_t writed_size = 0;
	uint16_t crc_value;
	uint16_t temp_piece_size = piece_size;
	
	while(piece_size)
	{
		if(start_offset + piece_size <= FLASH_CACHE_BUFF_LEN)
		{
			write_size = piece_size;
			piece_size -= write_size;
		}
		else
		{
			write_size = FLASH_CACHE_BUFF_LEN - start_offset;
			piece_size -= write_size;
		}		
		flash_tat_read_data(start_page + flash_program_start_page , 0, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN);				
		memcpy(flash_cache_temp_buff+start_offset, buff+writed_size, write_size);
		get_broadcast_bit(&start_bit, &end_bit, start_page, temp_piece_size);//一页能存储完整片数+不完整片数
 		while(start_bit <= end_bit)
		{
			if(!is_bit_map_set(start_bit))	
				break;
			start_bit++;
		}
		if(start_bit > end_bit)
		{	
			crc_value = crc_compute(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN,  INITIAL_VALUE, 1);
			*(uint16_t *)&(flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN]) = crc_value;
			flash_tat_write_data(start_page + flash_program_start_page, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);
		}
		else
		{
			flash_tat_write_data(start_page + flash_program_start_page, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN);
		}	

		start_page++;
		start_offset = 0;
		writed_size += write_size;
	}
	return 0;
}

void flush_broadcast_program_data(void)
{
	uint16_t start_page;
	uint16_t offset;
	uint16_t crc_value;
	uint32_t total_bytes = fireware_parameter.broadcast_sum_bytes;
	offset = (total_bytes & 0xff);
	start_page = (total_bytes>>8);
	if(offset)
	{	
		broadcast_flash_index = flash_program_start_page + start_page;		
		flash_tat_read_data(start_page+flash_program_start_page, 0, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN);
		memset(flash_cache_temp_buff+offset, 0xff, FLASH_CACHE_BUFF_LEN-offset);
		crc_value = crc_compute(flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN, INITIAL_VALUE, 1);
		*(uint16_t *)&(flash_cache_temp_buff[FLASH_CACHE_BUFF_LEN]) = crc_value;
		flash_tat_write_data(start_page + flash_program_start_page, flash_cache_temp_buff, FLASH_CACHE_BUFF_LEN+FLASH_INDEX_LEN);
	}
	else
	{
		broadcast_flash_index = flash_program_start_page + start_page - 1;		
	}
}


void broadcast_reboot(void)
{
	flush_broadcast_program_data();
	broadcast_program_calculated_crc = broadcast_calc_sum_crc();//接收的整个文件做CRC校验

	if(broadcast_program_calculated_crc == fireware_parameter.fireware_crc)
	{
		//修改参数
		node_parameter.program_start_addr = flash_program_start_page;
		node_parameter.program_end_addr = broadcast_flash_index;
		copy_sysparam_to_flash((uint8_t *)(&node_parameter));//更新系统参数
		wdtimer_stop();
		DISABLE_IRQ();			//关闭全部中断
		copy_boot_to_sram();//引导程序
		DEVICE_RedirectInterrupts(BOOT_START_ADDR);
		user_app_jump();			
	}
	else
	{
		//失败
		reset_broadcast_parameter();
	}
	
}

uint16_t broadcast_calc_sum_crc(void)
{
	uint32_t crc_bytes = 0;
	uint32_t left_bytes = fireware_parameter.broadcast_sum_bytes;
	uint16_t crc_value = 0xffff;
	uint16_t start_page = flash_program_start_page;
	
	while(left_bytes)
	{		
		if(left_bytes >= 256)
		{
			crc_bytes = 256;
		}
		else
		{
			crc_bytes = left_bytes;
		}
		flash_tat_read_data(start_page++, 0, broadcast_program_buff, 256);		
		crc_value = crc_compute(broadcast_program_buff, crc_bytes, crc_value, 0);
		left_bytes -= crc_bytes;
	}
	crc_value = crc_compute(NULL, 0, crc_value, 1);
	return crc_value;
}


void reset_broadcast_parameter()
{
	clear_bit_map();
}



