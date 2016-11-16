#include <boot.h>
#include <inchip_flash.h>
#include <ext_flash_include.h>
#include <system_init.h>
#include <crc.h>
#include "state.h"

uint8_t code_buff[258];
uint16_t code_start_page;
uint16_t code_end_page;
uint16_t code_page_index;
uint16_t crc_value;
uint16_t crc_read_value;
uint32_t boot_address;
/*
void read_end_page(void)
{
	read_from_flash_to_buff(BOOT_INFO_START_ADDR, &code_start_page, 2);
	read_from_flash_to_buff(BOOT_INFO_START_ADDR, &code_end_page, 2);
}
*/


int boot_calc_crc(void)
{
	crc_value = 0xffff;
	code_page_index = code_start_page;

	while(code_page_index <= code_end_page)
	{
		flash_tat_read_data(code_page_index, 0, code_buff, 258);
		crc_read_value = *(uint16_t *)&(code_buff[256]);
		crc_value = crc_compute(code_buff, 256, INITIAL_VALUE, 1);
		if(crc_read_value != crc_value)
			break;
		code_page_index++;
	}

	if(code_page_index <=  code_end_page)
	{
		return -1;
	}

	return 0;
}

void guide(void)
{
	boot_address = 0;
	code_page_index = code_start_page;
	while(code_page_index <= code_end_page)
	{
		led_green_toggle();
		if(!(boot_address & 0x3ff))
		{
			erase_flash(boot_address, 1, 0xff);
		}
		flash_tat_read_data(code_page_index, 0, code_buff, 256);
		write_to_flash_from_buff(boot_address, code_buff, 256);
		code_page_index++;
		boot_address += 256;
	}
}



void boot(void)
{
	int ret = 0;
	led_green_on();
	read_from_flash_to_buff(0Xfc00+8, &code_start_page, 2);
	read_from_flash_to_buff(0Xfc00+12, &code_end_page, 2);
	ret = boot_calc_crc();
	led_green_off();
	if(!ret)
	{		
		LED_RED_ON;
		guide();
		LED_RED_OFF;
//		set_close_state();
	}else
	{
		LED_BLUE_ON;
	}
}

void DEVICE_RedirectInterrupts(uint32_t address)
{
   SCB->VTOR = address;
}

#ifdef PRECISION32
void user_app_jump(void)
{
    __asm volatile ("ldr r0, =0x00002000");
    __asm volatile ("ldr sp, [r0]");
    __asm volatile ("ldr pc, [r0, #4] ");
}
#else
__asm void user_app_jump(void)
{
    LDR R0, =0
    LDR SP, [R0]; Initialze stack pointer
    LDR PC, [R0,#4] ; Initialize program counter
}
#endif
