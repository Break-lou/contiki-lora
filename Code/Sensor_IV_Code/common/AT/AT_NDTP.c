#include "AT_NDTP.h"

uint8_t NDTP[] = "NDTP";
#define NDTP_LEN 4
void at_ndtp_get_handler(AT_CMD_TYPE* at_item);
void at_ndtp_set_handler(AT_CMD_TYPE* at_item);

/**
节点类型
**/
void at_ndtp(AT_CMD_TYPE* at_item)
{
    uint8_t type = (*at_item).type;
    switch(type)
    {
        case AT_GET_TYPE:
            at_ndtp_get_handler(at_item);
            break;
        case AT_SET_TYPE:
            at_ndtp_set_handler(at_item);
            break;
        default:
            break;
    }
}
//获取
void at_ndtp_get_handler(AT_CMD_TYPE* at_item)
{
    uint8_t ndtp_len;
    uint8_t ndtp_buff[4];
    uint16_t ndtp = SENSOR_TYPE;
    
    dec_to_ascii_in_order(ndtp, ndtp_buff, &ndtp_len);
    
    at_assamble_get_response(NDTP, NDTP_LEN, ndtp_buff, ndtp_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_ndtp_set_handler(AT_CMD_TYPE* at_item)
{
    at_assamble_setting_response(NDTP, NDTP_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
}









