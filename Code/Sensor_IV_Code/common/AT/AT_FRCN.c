#include "AT_FRCN.h"

/**
强制更新周期
**/

uint8_t FRCN[] = "FRCN";
#define FRCN_LEN 4


void at_frcn_get_handler(AT_CMD_TYPE* at_item);
void at_frcn_set_handler(AT_CMD_TYPE* at_item);

void at_frcn(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_frcn_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_frcn_set_handler(at_item);
			break;
		default:
			break;
	}
}

void at_frcn_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t frcn_len;
	uint8_t frcn_buff[4];
	uint16_t frcn = node_parameter.frcn;			//获取节点MAC地址
	
	dec_to_ascii_in_order(frcn, frcn_buff, &frcn_len);
	
	at_assamble_get_response(FRCN, FRCN_LEN, frcn_buff, frcn_len, (*at_item).ack, &(*at_item).ack_len); 
}

void at_frcn_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t frcn;
	ascii_to_dec_in_order((uint8_t *)&frcn, 2, (*at_item).opt, (*at_item).opt_len);
	if(frcn<1 || frcn>100)
	{
		at_assamble_setting_response(FRCN, FRCN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.frcn = frcn;					//设置节点MAC地址
		update_sysparam();
		at_assamble_setting_response(FRCN, FRCN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}

