#ifndef EXT_FLASH_HAL_H
#define EXT_FLASH_HAL_H
#include<stdint.h>
int flash_hal_read_byte(uint8_t cmd, uint8_t *rx);

int flash_hal_write_byte(uint8_t cmd);

int flash_hal_read_buff(const uint8_t cmd, uint8_t *buf, uint16_t len);

int flash_hal_write_buff(const uint8_t cmd, const uint8_t *buf, uint16_t len);

int flash_hal_write_then_write(const uint8_t *cmd, uint16_t cmd_len, const uint8_t *buf, uint16_t buf_len);

int flash_hal_write_then_read(const uint8_t *cmd, uint16_t cmd_len, uint8_t *buf, uint16_t buf_len);


#endif

