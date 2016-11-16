#include "AT_VER.h"
#include "software_version.h"

uint8_t VER[] = "VER";
#define VER_LEN 3

/**
版本号
**/

void at_ver_get_handler(AT_CMD_TYPE* at_item);
void at_ver_set_handler(AT_CMD_TYPE* at_item);


void at_ver(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_ver_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_ver_set_handler(at_item);
			break;
		default:
			break;
	}
}

void at_ver_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t software_version_buff[10];
	uint8_t len;
	get_software_version(software_version_buff, &len);

	at_assamble_get_response(VER, VER_LEN, software_version_buff, len, (*at_item).ack, &(*at_item).ack_len); 	
}

void at_ver_set_handler(AT_CMD_TYPE* at_item)
{
	at_assamble_setting_response(VER, VER_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
}


