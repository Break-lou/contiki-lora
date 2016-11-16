#ifndef __SENSOR_IV_BOOT_H__
#define __SENSOR_IV_BOOT_H__


#include "si32_device.h"


#define BOOT_START_ADDR 0x20000000

void copy_boot_to_sram(void);
void user_app_jump(void);

void DEVICE_RedirectInterrupts(uint32_t address);


#endif
