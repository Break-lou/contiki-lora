#ifndef BOOT_H
#define BOOT_H

#include <stdint.h>

#define BOOT_INFO_START_ADDR 0XFF00

void boot(void);

void DEVICE_RedirectInterrupts(uint32_t address);

void user_app_jump(void);

#endif

