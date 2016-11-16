#include "AT_HISN.h"
#include <stdint.h>

/**
历史数据上发条数
*/


uint8_t HISN[] = "HISN";
#define HISN_LEN 4


void at_hisn_get_handler(AT_CMD_TYPE* at_item);
void at_hisn_set_handler(AT_CMD_TYPE* at_item);


void at_hisn(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_hisn_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_hisn_set_handler(at_item);
			break;
		default:
			break;
	}
}

//获取
void at_hisn_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t hisn_len;
	uint8_t hisn_buff[4];
	uint16_t hisn = node_parameter.hisn;				//获取历史记录上次条数	
	dec_to_ascii_in_order(hisn, hisn_buff, &hisn_len);
	
	at_assamble_get_response(HISN, HISN_LEN, hisn_buff, hisn_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_hisn_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t hisn;
	ascii_to_dec_in_order((uint8_t *)&hisn, 2, (*at_item).opt, (*at_item).opt_len);
	if(hisn==0 || hisn>100)
	{
		at_assamble_setting_response(HISN, HISN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.hisn = hisn;						//设置历史记录条数
		update_sysparam();
		at_assamble_setting_response(HISN, HISN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}





