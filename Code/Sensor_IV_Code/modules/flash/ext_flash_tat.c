#include "ext_flash_include.h"
#include <string.h>
#include "delay.h"
extern void delay_Xus(uint32_t cnt);

uint8_t flash_wake_flag = 1; // 1：flash工作状态
														 //	0：flash休眠状态

uint8_t flash_valid_flag = 0;
uint16_t flash_pages = 0;
uint16_t flash_capacity_via_KB;
extern uint16_t flash_program_start_page;//开始页
extern uint16_t flash_program_page_index;//页索引

static uint16_t flash_tat_get_status(void)
{
	uint16_t status;
	flash_hal_read_buff(EXT_FALSH_READ_STATUS_CMD, (uint8_t *)(&status), 2);
	return status;
}

static uint32_t flash_tat_get_id(void)
{
	uint32_t flash_id;
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());											
	flash_hal_read_buff(EXT_FALSH_READ_ID_CMD, (uint8_t *)(&flash_id), 4);
	while(!flash_tat_check_idle());
	flash_tat_enter_sleep();
	return flash_id;
}
uint16_t re_flash_status(void)
{
	flash_tat_leave_sleep();	
	uint16_t data = flash_tat_get_status();	
	flash_tat_enter_sleep();
	return data;
}


uint8_t flash_status;
uint32_t flash_status_invalid_cnt = 0;

uint8_t flash_tat_check_idle(void)
{
	uint8_t idle = 0;
	uint16_t status = flash_tat_get_status();	
	flash_status = status;
	if(((status&FLASH_TYPE_MASK) != FLASH_041D)&&((status&FLASH_TYPE_MASK) != FLASH_081D))
	{
		if(flash_valid_flag)	idle = 0;
		else	idle = 1;
		flash_status_invalid_cnt++;
	}
	else
	{
		if((status&0x80))		
		{
			idle = 1;
		}
		else	
		{
			idle = 0;
		}
	}

	return idle;
}
int flash_tat_enter_sleep(void)
{
	if(flash_wake_flag)
	{
		flash_wake_flag = 0;
		flash_hal_write_byte(EXT_FLASH_SLEEP_CMD);
	}
	return 0;	
}
/*
void flash_tat_into_sleep(void)
{
//	flash_hal_write_byte(EXT_FALSH_READ_STATUS_CMD);
	flash_hal_write_byte(EXT_FLASH_SLEEP_CMD);
}
*/
int flash_tat_into_sleep(void)
{
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	flash_tat_enter_sleep();
	return 0;
}
//int flash_tat_wait_sleep(void)
//{
//	flash_tat_leave_sleep();
//	while(!flash_tat_check_idle());
//	flash_tat_enter_sleep();
//	return 0;
//}
int flash_tat_leave_sleep(void)
{
	if(!flash_wake_flag)
	{        
		flash_wake_flag = 1;
		flash_hal_write_byte(EXT_FLASH_WAKE_CMD);//从休眠中唤醒
	}
	return 0;
}

static void flash_tat_set_page_size(ext_flash_page_size_t flash_page_size)
{
	uint8_t status;
	uint8_t opcode[3];
	opcode[0] = 0x2a;
	opcode[1] = 0x80;

	switch(flash_page_size)
	{
		case ext_flash_256_bytes:
			opcode[2] = 0XA6;
			break;
		case ext_flash_264_bytes:
			opcode[2] = 0xA7;
			break;
	}
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	status = flash_tat_get_status();
	if((status&FLASH_TYPE_MASK) == FLASH_081D)
	{
		flash_hal_write_buff(0x3d, opcode, 3);
		while(!flash_tat_check_idle());
	}

	flash_tat_enter_sleep();
}

int flash_tat_erase_page(uint16_t pageaddr)
{ 
	uint8_t page[3];
	page[0] = (uint8_t)(pageaddr >> 7);
	page[1] = (uint8_t)(pageaddr << 1);
	page[2] = 0;
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	flash_hal_write_buff(EXT_FLASH_PAGE_ERASE, page, 3);
	while(!flash_tat_check_idle());
	flash_tat_enter_sleep();
	return 0;
}

int flash_tat_erase_chip_nonblock(void)
{
	uint8_t cmd = 0xc7;
	uint8_t buff[3];
	buff[0] = 0x94;
	buff[1] = 0x80;
	buff[2] = 0x9a;

	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	flash_hal_write_buff(cmd, buff, 3);

	return 0;
}


int flash_tat_erase_chip(void)
{
	uint8_t cmd = 0xc7;
	uint8_t buff[3];
	buff[0] = 0x94;
	buff[1] = 0x80;
	buff[2] = 0x9a;

	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	flash_hal_write_buff(cmd, buff, 3);
	while(!flash_tat_check_idle());
	flash_tat_enter_sleep();
	return 0;
}
//自动擦除页后写入数据
int flash_tat_write_data(uint16_t page, uint8_t *pdata, uint16_t len)
{
	uint8_t cmd[4];
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	cmd[0] = EXT_FLASH_WRITE_PAGE_CMD;
	cmd[1] = (uint8_t)(page>>7);
	cmd[2] = (uint8_t)(page<<1);
	cmd[3] = 0;
	flash_hal_write_then_write(cmd, 4, pdata, len);
	delay_Xus(30);
	while(!flash_tat_check_idle());
	flash_tat_enter_sleep();
	return 0;
}
//不带擦除的向页写入数据
int flash_tat_write_data_without_erase(uint16_t page, uint8_t *pdata, uint16_t len)
{
	uint8_t cmd[4];
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	cmd[0] = EXT_FLASH_WRITE_BUFF1_CMD;
	cmd[1] = 0;
	cmd[2] = 0;
	cmd[3] = 0;
	flash_hal_write_then_write(cmd, 4, pdata, len);//接入FLASH缓冲区
	while(!flash_tat_check_idle());
	cmd[0] = EXT_FLASH_WRITE_PAGE_WITHOUT_ERASE_CMD;
	cmd[1] = (uint8_t)(page>>7);
	cmd[2] = (uint8_t)(page<<1);
	cmd[3] = 0;
	flash_hal_write_then_write(cmd, 4, pdata, len);
	while(!flash_tat_check_idle());	
	flash_tat_enter_sleep();
	return 0;

}

int flash_tat_read_data(uint16_t page, uint16_t offset,uint8_t *pdata, uint16_t len)
{
	uint8_t cmd[8];
	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());
	cmd[0] = EXT_FLASH_READ_PAGE_CMD;
	cmd[1] = (uint8_t)(page>>7);
	cmd[2] = (uint8_t)((page<<1)|(offset>>8));
	cmd[3] = (uint8_t)offset;
	cmd[4] = 0;
	cmd[5] = 0;
	cmd[6] = 0;
	cmd[7] = 0;
	flash_hal_write_then_read(cmd, 8, pdata, len);
	while(!flash_tat_check_idle());
	flash_tat_enter_sleep();
	return 0;
}
int flash_init(void)
{
	uint8_t device_id;
	uint32_t flash_id;
	ext_flash_port_init();
	ext_flash_spi_init();
	ext_flash_reset();
	flash_tat_leave_sleep();
	flash_id = flash_tat_get_id();
	device_id = (uint8_t)(flash_id>>8);
	#if FLASH_DEBUG_PRINT == 1
		printf("FLASH ID = 0x%X\n ", flash_id);
	#endif
	if((device_id&0x07) == 0x04)
	{
		flash_pages = 2048;
		flash_data_page_num = 1792;
		flash_program_start_page = 1792;
		flash_program_page_index = flash_program_start_page;
	}
	else if((device_id&0x07) == 0x05)
	{
		flash_pages = 4096;
		flash_data_page_num = 3840;
		flash_program_start_page = 3840;
		flash_program_page_index = flash_program_start_page;
	}
	else
	{
		return 0;
	}
	flash_tat_set_page_size(ext_flash_264_bytes);

	return 1;
}

int flash_tat_init(void)
{
	uint8_t device_id;
	uint32_t flash_id;
	ext_flash_port_init();
	ext_flash_spi_init();
	ext_flash_reset();
	flash_id = flash_tat_get_id();
	device_id = (uint8_t)(flash_id>>8);
	if((device_id&0x07) == 0x04)
	{
		flash_valid_flag = 1;
	}
	else if((device_id&0x07) == 0x05)
	{
		flash_valid_flag = 1;
	}
	else
	{
		flash_valid_flag = 0;
	}
	flash_tat_leave_sleep();
	flash_tat_enter_sleep();
	
	return 0;
}



