#ifndef INCHIP_FLASH_H
#define INCHIP_FLASH_H

#include <stdint.h>
#include <Si32_device.h>
#include <SI32_FLASHCTRL_A_Type.h>
#include <SI32_VMON_B_Type.h>
#include <SI32_RSTSRC_A_Type.h>
#include <SI32_CLKCTRL_A_Type.h>

void read_from_flash_to_buff(uint32_t addr, uint16_t *buff, uint16_t len);

void erase_flash(uint32_t addr, uint16_t pages, uint16_t value);

void write_to_flash_from_buff(uint32_t addr,  uint8_t *buff, uint16_t len);

#endif

