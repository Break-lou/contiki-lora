#ifndef DOWNLOAD_HISTORY_H
#define DOWNLOAD_HISTORY_H

#include <si32_device.h>

#define DOWNLOAD_HISTORY_REQUEST	0X0B
#define DOWNLOAD_HISTORY_PACKET		0X0C


extern uint8_t download_type;
extern uint8_t download_over_operation;
extern uint16_t download_data_len;

void download_data_init(void);

uint16_t read_download_flash_data(uint8_t *history_data, uint16_t len);


#endif

