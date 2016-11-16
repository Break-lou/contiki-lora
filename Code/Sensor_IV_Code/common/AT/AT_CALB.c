#include "AT_CALB.h"
#include "sensor_co2_process.h"
#include "sensor_manager_process.h"

uint8_t CALB[]="CALB";
#define CALB_LEN 4

void at_calb_op_handler(AT_CMD_TYPE* at_item);


void at_calb(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			
			break;
		case AT_SET_TYPE:
			
			break;
		case AT_OP_TYPE:
			at_calb_op_handler(at_item);
			break;
		default:
			break;
	}
}



void at_calb_op_handler(AT_CMD_TYPE* at_item)
{
	#if CO2_SENSOR
		post_co2_calibration();
	#endif
	at_assamble_setting_response(CALB, CALB_LEN, (*at_item).ack, &(*at_item).ack_len, WT_ACK);
}
