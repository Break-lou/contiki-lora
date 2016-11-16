#include <system_init.h>
#include <inchip_flash.h>
#include <ext_flash_include.h>
#include <boot.h>

int main(void)
{
	system_init();
	led_on();
	flash_tat_init();
	led_off();
	
	boot();
	
	soft_reset();
	led_off();

	while(1)
	{
		
	}

}

