#ifndef EXT_FLASH_STORAGE_H
#define EXT_FLASH_STORAGE_H

#include <stdint.h>

#define FLASH_CACHE_BUFF_LEN 256
#define FLASH_INDEX_LEN		2
typedef struct storage_index_t
{
	uint16_t read;
	uint16_t write;	
	uint16_t page_offset;
	uint16_t current_page;
	uint16_t idlepage;
	uint16_t capacity;
}storage_index;

extern uint16_t flash_data_page_num;

void cache_init(void);

int storage_init(void);

void storage_empty(void);

int storage_cancle_read(void);

int storage_flush_program(void);
uint8_t format_flash(void);
uint32_t flash_parameter_display(uint8_t data);
int storage_write_data(uint8_t *buff, uint16_t len);

int storage_write_program(uint8_t *buff, uint16_t len);

int flash_tat_erase_page(uint16_t pageaddr);

int flash_tat_erase_chip(void);

void storage_check_stack(void);

int storage_confirm_read(void);

int storage_write_new_page(uint8_t *data);

uint16_t storage_read_data(uint8_t *buff, uint16_t len);


#endif

