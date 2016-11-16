#include "system_init.h"
#include "inchip_flash.h"
#include "state.h"


uint32_t param_buff[64];

void set_close_state(void)
{
	read_from_flash_to_buff(0xfc00, (uint16_t *)param_buff, 256);
	((sys_param_t*)param_buff)->state_mode = CLOSE_MODE;
	erase_flash(0xfc00, 1, 0xff);
	write_to_flash_from_buff(0xfc00, (uint8_t *)param_buff, 256);
	//delay_us(100000);
}




