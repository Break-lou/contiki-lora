#include "AT_SEN.h"
#include "sen_work_process.h"

uint8_t SEN[] = "SEN";
#define SEN_LEN 3

void at_sen_get_handler(AT_CMD_TYPE* at_item);
void at_sen_set_handler(AT_CMD_TYPE* at_item);

/**
传感器自检
**/
void at_sen(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_sen_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_sen_set_handler(at_item);
			break;
		default:
			break;
	}
}

void at_sen_get_handler(AT_CMD_TYPE* at_item)
{
	at_assamble_get_response(SEN, SEN_LEN, "ER", 2, (*at_item).ack, &(*at_item).ack_len);
}

void at_sen_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t opt;
	ascii_to_dec_in_order((uint8_t *)&opt, 1, (*at_item).opt, (*at_item).opt_len);
	if(opt == 1)
	{
		//开始自检
		post_sen_work_ev(SYSTEM_ENTER_CHECK_MODE);
		at_assamble_setting_response(SEN, SEN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else if(opt == 2)
	{
		//结束自检
		post_sen_work_ev(SYSTEM_LEAVE_CHECK_MODE);
		at_assamble_setting_response(SEN, SEN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		//其他则任务无效
		at_assamble_setting_response(SEN, SEN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	
	
}


