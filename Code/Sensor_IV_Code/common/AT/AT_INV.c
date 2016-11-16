#include "AT_INV.h"
#include <stdint.h>

uint8_t INV[] = "INV";
#define INV_LEN 3

void at_inv_get_handler(AT_CMD_TYPE* at_item);
void at_inv_set_handler(AT_CMD_TYPE* at_item);


/**
节点工作周期
**/
void at_inv(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_inv_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_inv_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_inv_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t inv_len;
	uint8_t inv_buff[4];
	uint16_t inv = node_parameter.tdti;			//获取节点MAC地址
	
	dec_to_ascii_in_order(inv, inv_buff, &inv_len);
	
	at_assamble_get_response(INV, INV_LEN, inv_buff, inv_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_inv_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t inv;
	ascii_to_dec_in_order((uint8_t *)&inv, 2, (*at_item).opt, (*at_item).opt_len);
	if(inv==0 || inv>=0xffff)
	{
		at_assamble_setting_response(INV, INV_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.tdti = inv;					//设置节点MAC地址
		update_sysparam();
		at_assamble_setting_response(INV, INV_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}

