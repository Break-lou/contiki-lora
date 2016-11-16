#include "AT_RTYN.h"



/**
数据包重传次数
**/
uint8_t RTYN[] = "RTYN";
#define RTYN_LEN 4

void at_rtyn_get_handler(AT_CMD_TYPE* at_item);
void at_rtyn_set_handler(AT_CMD_TYPE* at_item);


void at_rtyn(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_rtyn_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_rtyn_set_handler(at_item);
			break;
		default:
			break;
	}
	
}

void at_rtyn_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t rtyn_len;
	uint8_t rtyn_buff[4];
	uint16_t rtyn = node_parameter.rtyn;
	
	dec_to_ascii_in_order(rtyn, rtyn_buff, &rtyn_len);
	
	at_assamble_get_response(RTYN, RTYN_LEN, rtyn_buff, rtyn_len, (*at_item).ack, &(*at_item).ack_len);
}

void at_rtyn_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t rtyn;
	ascii_to_dec_in_order((uint8_t *)&rtyn, 2, (*at_item).opt, (*at_item).opt_len);
	if(rtyn > 10)
	{
		at_assamble_setting_response(RTYN, RTYN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.rtyn = rtyn;				
		update_sysparam();
		at_assamble_setting_response(RTYN, RTYN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);	
	}
}

