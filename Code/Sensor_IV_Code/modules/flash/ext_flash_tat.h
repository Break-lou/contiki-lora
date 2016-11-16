#ifndef EXT_FLASH_TAT_H
#define EXT_FLASH_TAT_H
#include <stdint.h>
#define FLASH_041D 0x1c
#define FLASH_081D 0x24
#define FLASH_TYPE_MASK 0X3C

#define EXT_FALSH_READ_STATUS_CMD 	0XD7
#define EXT_FALSH_READ_ID_CMD		0X9F
#define EXT_FLASH_SLEEP_CMD			0X79
#define EXT_FLASH_WAKE_CMD			0XAB
#define EXT_FLASH_PAGE_ERASE		0X81
#define EXT_FLASH_WRITE_PAGE_CMD	0X82
#define EXT_FLASH_READ_PAGE_CMD		0XD2
#define EXT_FLASH_WRITE_BUFF1_CMD	0X84
#define EXT_FLASH_WRITE_PAGE_WITHOUT_ERASE_CMD	0X88

typedef enum
{
	ext_flash_256_bytes,
	ext_flash_264_bytes,
}ext_flash_page_size_t;

int flash_init(void);

int flash_tat_init(void);

int flash_tat_leave_sleep(void);

int flash_tat_erase_chip_nonblock(void);

int flash_tat_erase_chip(void);

int flash_tat_wait_sleep(void);

uint8_t flash_tat_check_idle(void);

uint16_t re_flash_status(void);

int flash_tat_enter_sleep(void);

int flash_tat_read_data(uint16_t page, uint16_t offset,uint8_t *pdata, uint16_t len);

int flash_tat_write_data(uint16_t page, uint8_t *pdata, uint16_t len);

int flash_tat_write_data_without_erase(uint16_t page, uint8_t *pdata, uint16_t len);

int flash_tat_into_sleep(void);

#endif

