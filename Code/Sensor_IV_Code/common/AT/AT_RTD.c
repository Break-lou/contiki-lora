#include "AT_RTD.h"
#include "sensor_parameter.h"

uint8_t RTD[]="RTD";
#define RTD_LEN 3

void at_rtd_get_handler(AT_CMD_TYPE* at_item);
void at_rtd_set_handler(AT_CMD_TYPE* at_item);
	
/**
传感器速率
**/
void at_rtd(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_rtd_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_rtd_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_rtd_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t rtd_len;
	uint8_t rtd_buff[4];
	uint16_t rtd = node_parameter.rtd;			    
	
	dec_to_ascii_in_order(rtd, rtd_buff, &rtd_len);
	
	at_assamble_get_response(RTD, RTD_LEN, rtd_buff, rtd_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_rtd_set_handler(AT_CMD_TYPE* at_item)
{
    //设置
    uint16_t rtd;
	ascii_to_dec_in_order((uint8_t *)&rtd, 2, (*at_item).opt, (*at_item).opt_len);
	if(rtd<=0 || rtd>600)
	{
		at_assamble_setting_response(RTD, RTD_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		//设置节点频段
		node_parameter.rtd = rtd;
		update_sysparam();
		at_assamble_setting_response(RTD, RTD_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
