#ifndef SOFTWARE_VERSION_H
#define SOFTWARE_VERSION_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int software_version_compare(uint8_t *buff);

void get_software_version(uint8_t *version_buff, uint8_t *version_len);


#endif

