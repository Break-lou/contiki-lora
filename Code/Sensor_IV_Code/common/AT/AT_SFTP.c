#include "AT_SFTP.h"

uint8_t SFTP[] = "SFTP";
#define SFTP_LEN 4
void at_sftp_get_handler(AT_CMD_TYPE* at_item);
void at_sftp_set_handler(AT_CMD_TYPE* at_item);
/**
软件类型
**/
void at_sftp(AT_CMD_TYPE* at_item)
{
    uint8_t type = (*at_item).type;
    switch(type)
    {
        case AT_GET_TYPE:
            at_sftp_get_handler(at_item);
            break;
        case AT_SET_TYPE:
            at_sftp_set_handler(at_item);
            break;
        default:
            break;
    }
}
//获取
void at_sftp_get_handler(AT_CMD_TYPE* at_item)
{
    uint8_t sftp_len;
    uint8_t sftp_buff[4];
    uint16_t sftp = SOFTWARE_TYPE;
    
    dec_to_ascii_in_order(sftp, sftp_buff, &sftp_len);
    
    at_assamble_get_response(SFTP, SFTP_LEN, sftp_buff, sftp_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_sftp_set_handler(AT_CMD_TYPE* at_item)
{
    at_assamble_setting_response(SFTP, SFTP_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
}
