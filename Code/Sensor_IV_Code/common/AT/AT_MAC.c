#include "AT_MAC.h"


uint8_t MAC[]="MAC";
#define MAC_LEN 3

void at_mac_get_handler(AT_CMD_TYPE* at_item);
void at_mac_set_handler(AT_CMD_TYPE* at_item);
	
/**
传感器MAC设置
**/
void at_mac(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_mac_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_mac_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_mac_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t mac_len;
	uint8_t mac_buff[4];
	uint16_t mac = node_parameter.src_addr;			    //获取节点MAC地址
	
	hex_to_ascii_in_order(mac, mac_buff, &mac_len);
	
	at_assamble_get_response(MAC, MAC_LEN, mac_buff, mac_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_mac_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t mac;
	ascii_to_hex_in_order((uint8_t *)&mac, 2, (*at_item).opt, (*at_item).opt_len);
	if(mac==0 || mac>=0xffff)
	{
		at_assamble_setting_response(MAC, MAC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.src_addr = mac;					//设置节点MAC地址
		update_sysparam();
		at_assamble_setting_response(MAC, MAC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}





