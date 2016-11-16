#include "at_qut.h"
#include "data_conversion.h"
#include "sx127x_app.h"
#include "sensor_parameter.h"

void at_sbw_get_handler(AT_CMD_TYPE* at_item);
void at_sbw_set_handler(AT_CMD_TYPE* at_item);
void at_scr_get_handler(AT_CMD_TYPE* at_item);
void at_scr_set_handler(AT_CMD_TYPE* at_item);
void at_ssf_get_handler(AT_CMD_TYPE* at_item);
void at_ssf_set_handler(AT_CMD_TYPE* at_item);

uint8_t QUT[] = "QUT";
#define QUT_LEN 3

uint8_t SBW[] = "SBW";
#define SBW_LEN 3
uint8_t SCR[] = "SCR";
#define SCR_LEN 3
uint8_t SSF[] = "SSF";
#define SSF_LEN 3


/**
退出配置模式，暂时未用到该指令
**/

//类型，参数，参数长度
void at_qut(AT_CMD_TYPE* at_item)
{
	uint8_t qut_opt;
	ascii_to_hex_in_order((uint8_t *)&qut_opt, 1, (*at_item).opt, (*at_item).opt_len);
	switch(qut_opt)
	{
		case '1':
			//进入关机状态
			
			break;
		case '2':
			//进入正常工作状态
		
			break;
		case '3':
			//进入快速工作状态
			
			break;
		default:
			break;
	}
	at_assamble_setting_response(QUT, QUT_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
}


void at_sbw(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
            at_sbw_get_handler(at_item);
            break;
        case AT_SET_TYPE:
            at_sbw_set_handler(at_item);
            break;
        default:
            break;
	}
}

void at_scr(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
            at_scr_get_handler(at_item);
            break;
        case AT_SET_TYPE:
            at_scr_set_handler(at_item);
            break;
        default:
            break;
	}
}

void at_ssf(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
            at_ssf_get_handler(at_item);
            break;
        case AT_SET_TYPE:
            at_ssf_set_handler(at_item);
            break;
        default:
            break;
	}
}


void at_sbw_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t bw_len;
    uint8_t bw_buff[4];
	uint8_t bw = node_parameter.sbw;
	
	hex_to_ascii_in_order(bw, bw_buff, &bw_len);
	at_assamble_get_response(SBW, SBW_LEN, bw_buff, bw_len, (*at_item).ack, &(*at_item).ack_len);
}

void at_sbw_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t bw;
	ascii_to_hex_in_order((uint8_t *)&bw, 1, (*at_item).opt, (*at_item).opt_len);
	if(check_bw(bw))
	{
		node_parameter.sbw = bw;
		update_sysparam();
		at_assamble_setting_response(SBW, SBW_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		at_assamble_setting_response(SBW, SBW_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
}


void at_scr_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t cr_len;
    uint8_t cr_buff[4];
	uint8_t cr = node_parameter.scr;
	
	hex_to_ascii_in_order(cr, cr_buff, &cr_len);
	at_assamble_get_response(SCR, SCR_LEN, cr_buff, cr_len, (*at_item).ack, &(*at_item).ack_len);
}

void at_scr_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t cr;
	ascii_to_hex_in_order((uint8_t *)&cr, 1, (*at_item).opt, (*at_item).opt_len);
	if(check_cr(cr))
	{
		node_parameter.scr = cr;
		update_sysparam();
		at_assamble_setting_response(SCR, SCR_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		at_assamble_setting_response(SCR, SCR_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
}

void at_ssf_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sf_len;
    uint8_t sf_buff[4];
	uint8_t sf = node_parameter.ssf;
	
	hex_to_ascii_in_order(sf, sf_buff, &sf_len);
	at_assamble_get_response(SSF, SSF_LEN, sf_buff, sf_len, (*at_item).ack, &(*at_item).ack_len);
}

void at_ssf_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sf;
	ascii_to_hex_in_order((uint8_t *)&sf, 1, (*at_item).opt, (*at_item).opt_len);
	if(check_sf(sf))
	{
		node_parameter.ssf = sf;
		update_sysparam();
		at_assamble_setting_response(SSF, SSF_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		at_assamble_setting_response(SSF, SSF_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	
	
}












