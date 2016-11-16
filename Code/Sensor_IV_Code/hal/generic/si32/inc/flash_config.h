#ifndef __FLASH_CONFIG_H__
#define __FLASH_CONFIG_H__

#include <si32_device.h>
#include "SI32_CLKCTRL_A_Type.h"
#include "SI32_VMON_B_Type.h"
#include "SI32_FLASHCTRL_A_Type.h"
#include "SI32_RSTSRC_A_Type.h"



void read_from_flash_to_buff(uint32_t addr, uint8_t *buff, uint16_t len);
void write_data_to_flash(uint32_t addr,  uint8_t *buff, uint16_t len);









#endif
