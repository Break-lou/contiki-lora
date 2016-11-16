#ifndef EXT_FLASH_TAT_H
#define EXT_FLASH_TAT_H

#include "si32_device.h"

#define EXT_FALSH_READ_STATUS_CMD 	0XD7
#define EXT_FALSH_READ_ID_CMD		0X9F
#define EXT_FLASH_SLEEP_CMD			0XB9
#define EXT_FLASH_WAKE_CMD			0XAB
#define EXT_FLASH_PAGE_ERASE		0X81
#define EXT_FLASH_WRITE_PAGE_CMD	0X82
#define EXT_FLASH_READ_PAGE_CMD		0XD2
#define EXT_FLASH_WRITE_BUFF1_CMD	0X84
#define EXT_FLASH_WRITE_PAGE_WITHOUT_ERASE_CMD	0X88

#define FLASH_041D 0x1c
#define FLASH_081D 0x24
#define FLASH_TYPE_MASK 0X3C

int flash_tat_init(void);

int flash_tat_read_data(uint16_t page, uint16_t offset,uint8_t *pdata, uint16_t len);

#endif

