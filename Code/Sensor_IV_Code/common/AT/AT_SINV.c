#include "AT_SINV.h"

uint8_t SINV[] = "SINV";
#define SINV_LEN 4

void at_sinv_get_handler(AT_CMD_TYPE* at_item);
void at_sinv_set_handler(AT_CMD_TYPE* at_item);


/**
节点采样周期
**/
void at_sinv(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_sinv_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_sinv_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_sinv_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sinv_len;
	uint8_t sinv_buff[4];
	uint16_t sinv = node_parameter.ssti;			
	
	dec_to_ascii_in_order(sinv, sinv_buff, &sinv_len);
	
	at_assamble_get_response(SINV, SINV_LEN, sinv_buff, sinv_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_sinv_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t sinv;
	ascii_to_dec_in_order((uint8_t *)&sinv, 2, (*at_item).opt, (*at_item).opt_len);
	if(sinv==0 || sinv>=0xffff)
	{
		at_assamble_setting_response(SINV, SINV_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.ssti = sinv;			
		update_sysparam();		
		at_assamble_setting_response(SINV, SINV_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}


