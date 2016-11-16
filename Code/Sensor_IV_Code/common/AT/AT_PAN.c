#include "AT_PAN.h"

/**
传感器PAN
**/
uint8_t PAN[] = "PAN";
#define PAN_LEN 3

void at_pan_get_handler(AT_CMD_TYPE* at_item);
void at_pan_set_handler(AT_CMD_TYPE* at_item);


void at_pan(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_pan_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_pan_set_handler(at_item);
			break;
		default:
			break;
	}
	
}

void at_pan_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t pan_len;
	uint8_t pan_buff[4];
	uint16_t pan = node_parameter.src_pan_id;
	
	hex_to_ascii_in_order(pan, pan_buff, &pan_len);
	
	at_assamble_get_response(PAN, PAN_LEN, pan_buff, pan_len, (*at_item).ack, &(*at_item).ack_len);
}

void at_pan_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t pan;
	ascii_to_hex_in_order((uint8_t *)&pan, 2, (*at_item).opt, (*at_item).opt_len);
	if(pan == 0 || pan >= 0xFFFF)
	{
		at_assamble_setting_response(PAN, PAN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.src_pan_id = pan;				
		update_sysparam();
		at_assamble_setting_response(PAN, PAN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);	
	}
}

