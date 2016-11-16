#include "AT_POT.h"


uint8_t POT[] = "POT";
#define POT_LEN 3

void at_pot_get_handler(AT_CMD_TYPE* at_item);
void at_pot_set_handler(AT_CMD_TYPE* at_item);

void at_pot(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_pot_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_pot_set_handler(at_item);
			break;
		default:
			break;
	}
}

//获取
void at_pot_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t pot_len;
	uint8_t pot_buff[4];
	uint16_t pot = node_parameter.pot;
	
	dec_to_ascii_in_order(pot, pot_buff, &pot_len);
	
	at_assamble_get_response(POT, POT_LEN, pot_buff, pot_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_pot_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t pot;
	ascii_to_dec_in_order((uint8_t *)&pot, 2, (*at_item).opt, (*at_item).opt_len);
	if(pot<1 || pot>60)
	{
		at_assamble_setting_response(POT, POT_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.pot = pot;
		update_sysparam();
		at_assamble_setting_response(POT, POT_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	
}










