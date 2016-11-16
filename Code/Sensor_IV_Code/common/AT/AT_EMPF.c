#include "AT_EMPF.h"
#include "ext_flash_include.h"
#include "system_process_include.h"
#include "wdtimer_config.h"

uint8_t EMPF[]="EMPF";
#define EMPF_LEN 4

void at_empf_op_handler(AT_CMD_TYPE* at_item);

void at_empf(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			
			break;
		case AT_SET_TYPE:
			
			break;
		case AT_OP_TYPE:
			at_empf_op_handler(at_item);
			break;
		default:
			break;
	}
}

void at_empf_op_handler(AT_CMD_TYPE* at_item)
{
	wdtimer_reset();
	wdtimer_stop();
	post_data_download_ev(DATA_ERASE_DATA);
	at_assamble_setting_response(EMPF, EMPF_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
}



