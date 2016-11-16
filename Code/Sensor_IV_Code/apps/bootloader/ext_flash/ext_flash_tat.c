#include <ext_flash_include.h>

uint8_t flash_wake_flag = 1;
uint8_t flash_valid_flag = 0;

int flash_tat_read_data(uint16_t page, uint16_t offset,uint8_t *pdata, uint16_t len)
{
	uint8_t cmd[8];
	cmd[0] = EXT_FLASH_READ_PAGE_CMD;
	cmd[1] = (uint8_t)(page>>7);
	cmd[2] = (uint8_t)((page<<1)|(offset>>8));
	cmd[3] = (uint8_t)offset;
	cmd[4] = 0;
	cmd[5] = 0;
	cmd[6] = 0;
	cmd[7] = 0;
	flash_hal_write_then_read(cmd, 8, pdata, len);

	return 0;
}

uint16_t flash_tat_get_status(void)
{
	uint16_t status;
	flash_hal_read_buff(EXT_FALSH_READ_STATUS_CMD, (uint8_t *)(&status), 2);
	return status;
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
		if((status&0x80))		idle = 1;
		else	idle = 0;
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

int flash_tat_wait_sleep(void)
{
	if(flash_tat_check_idle());
		flash_tat_enter_sleep();
	return 0;
}
int flash_tat_leave_sleep(void)
{
	if(!flash_wake_flag)
	{
		flash_wake_flag = 1;
		flash_hal_write_byte(EXT_FLASH_WAKE_CMD);
	}
	return 0;
}

uint32_t flash_tat_get_id(void)
{
	uint32_t flash_id;
//	flash_tat_leave_sleep();
	while(!flash_tat_check_idle());											//这个地方不需要等待，因为复位后默认唤醒
	flash_hal_read_buff(EXT_FALSH_READ_ID_CMD, (uint8_t *)(&flash_id), 4);
	while(!flash_tat_check_idle());
//	flash_tat_enter_sleep();
	return flash_id;
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
	
	return 0;
}
