#include "AT_FRQ.h"
#include "sx127x_app.h"


uint8_t FRQ[]="FRQ";
#define FRQ_LEN 3

void at_frq_get_handler(AT_CMD_TYPE* at_item);
void at_frq_set_handler(AT_CMD_TYPE* at_item);
	
/**
传感器频段
**/
void at_frq(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_frq_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_frq_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_frq_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t frq_len;
	uint8_t frq_buff[4];
	uint16_t frq = node_running_flags.frq;			    //获取节点频率地址
	
	dec_to_ascii_in_order(frq, frq_buff, &frq_len);
	
	at_assamble_get_response(FRQ, FRQ_LEN, frq_buff, frq_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_frq_set_handler(AT_CMD_TYPE* at_item)
{
    at_assamble_setting_response(FRQ, FRQ_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	/*
	//设置
	uint8_t temp;
    uint16_t frq;
	ascii_to_dec_in_order((uint8_t *)&frq, 2, (*at_item).opt, (*at_item).opt_len);
	
	temp = sx127x_modify_frq(frq);
	if(temp)
	{
		//成功
		node_running_flags.frq = frq;
		at_assamble_setting_response(FRQ, FRQ_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		//失败
		at_assamble_setting_response(FRQ, FRQ_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	*/
}





