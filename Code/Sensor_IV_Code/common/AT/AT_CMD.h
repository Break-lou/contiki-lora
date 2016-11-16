#ifndef __AT_CMD_H__
#define __AT_CMD_H__



#include <stdint.h>
#include "AT_INCLUDE.h"

void at_mac(AT_CMD_TYPE* at_item);
void at_pan(AT_CMD_TYPE* at_item);
void at_tdti(AT_CMD_TYPE* at_item);
void at_tdti(AT_CMD_TYPE* at_item);
void at_ssti(AT_CMD_TYPE* at_item);
void at_tsdc(AT_CMD_TYPE* at_item);
void at_rtdc(AT_CMD_TYPE* at_item);
void at_tpto(AT_CMD_TYPE* at_item);
void at_cftoc(AT_CMD_TYPE* at_item);
void at_sptd(AT_CMD_TYPE* at_item);
void at_hisn(AT_CMD_TYPE* at_item);
void at_slbd(AT_CMD_TYPE* at_item);
void at_rnrwt(AT_CMD_TYPE* at_item);
void at_sbw(AT_CMD_TYPE* at_item);
void at_scr(AT_CMD_TYPE* at_item);
void at_ssf(AT_CMD_TYPE* at_item);
void at_pwr(AT_CMD_TYPE* at_item);
void at_frq(AT_CMD_TYPE* at_item);
void at_ssc(AT_CMD_TYPE* at_item);
void at_calb(AT_CMD_TYPE* at_item);
void at_swv(AT_CMD_TYPE* at_item);
void at_da(AT_CMD_TYPE* at_item);
void at_db(AT_CMD_TYPE* at_item);
void at_sfm(AT_CMD_TYPE* at_item);
void at_setp(AT_CMD_TYPE* at_item);
void at_hdtc(AT_CMD_TYPE* at_item);
void at_sms(AT_CMD_TYPE* at_item);
void at_fsrc(AT_CMD_TYPE* at_item);
#if S_5TM_OPERATE
void at_5tm_num(AT_CMD_TYPE* at_item);
void at_5tm_add(AT_CMD_TYPE* at_item);
void at_5tm_del(AT_CMD_TYPE* at_item);
#endif
#if modbus_mode
void at_modbus_cfg(AT_CMD_TYPE* at_item);
void at_modbus_data(AT_CMD_TYPE* at_item);
void at_check_type(AT_CMD_TYPE *at_item);
void at_check_norm(AT_CMD_TYPE *at_item);
void at_check_num(AT_CMD_TYPE *at_item);
#endif
#endif
