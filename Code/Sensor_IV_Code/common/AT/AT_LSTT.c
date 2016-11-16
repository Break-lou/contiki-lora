#include "AT_LSTT.h"


uint8_t LSTT[] = "LSTT";
#define LSTT_LEN 4
uint8_t RLSTT[] = "RLSTT";
#define RLSTT_LEN 5

void at_lstt_get_handler(AT_CMD_TYPE* at_item);
void at_lstt_set_handler(AT_CMD_TYPE* at_item);
void at_rlstt_get_handler(AT_CMD_TYPE* at_item);
void at_rlstt_set_handler(AT_CMD_TYPE* at_item);


/**
超时时间（从发包到接收完成）
**/
void at_lstt(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_lstt_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_lstt_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_lstt_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t lstt_len;
	uint8_t lstt_buff[4];
	uint16_t lstt = node_parameter.lstt;			
	
	dec_to_ascii_in_order(lstt, lstt_buff, &lstt_len);
	
	at_assamble_get_response(LSTT, LSTT_LEN, lstt_buff, lstt_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_lstt_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t lstt;
	ascii_to_dec_in_order((uint8_t *)&lstt, 2, (*at_item).opt, (*at_item).opt_len);
	if(lstt<40 || lstt>3000)
	{
		at_assamble_setting_response(LSTT, LSTT_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.lstt = lstt;				
		update_sysparam();		
		at_assamble_setting_response(LSTT, LSTT_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}


void at_rlstt(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_rlstt_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_rlstt_set_handler(at_item);
			break;
		default:
			break;
	}
}


//获取
void at_rlstt_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t rlstt_len;
	uint8_t rlstt_buff[4];
	uint16_t rlstt = node_parameter.rlstt;			
	
	dec_to_ascii_in_order(rlstt, rlstt_buff, &rlstt_len);
	
	at_assamble_get_response(RLSTT, RLSTT_LEN, rlstt_buff, rlstt_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_rlstt_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t rlstt;
	ascii_to_dec_in_order((uint8_t *)&rlstt, 2, (*at_item).opt, (*at_item).opt_len);
	if(rlstt<40 || rlstt>3000)
	{
		at_assamble_setting_response(RLSTT, RLSTT_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.rlstt = rlstt;				
		update_sysparam();		
		at_assamble_setting_response(RLSTT, RLSTT_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}



