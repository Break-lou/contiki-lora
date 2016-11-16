#include "AT_CMD.h"
#include "sx127x_app.h"
#include "system_process_include.h"
#include "software_version.h"
#include "AT_OPERATION.h"
#include "ext_flash_include.h"
#include "crc.h"
uint8_t MAC[]="MAC";
#define MAC_LEN 3
uint8_t PAN[] = "PAN";
#define PAN_LEN 3
uint8_t TDTI[] = "TDTI";
#define TDTI_LEN 4
uint8_t SSTI[] = "SSTI";
#define SSTI_LEN 4
uint8_t TSDC[] = "TSDC";
#define TSDC_LEN 4
uint8_t RTDC[] = "RTDC";
#define RTDC_LEN 4
uint8_t TPTO[] = "TPTO";
#define TPTO_LEN 4
uint8_t CFTOC[] = "CFTOC";
#define CFTOC_LEN 5
uint8_t SPTD[] = "SPTD";
#define SPTD_LEN 4
uint8_t HISN[] = "HISN";
#define HISN_LEN 4
uint8_t RNBTI[] = "RNBTI";
#define RNBTI_LEN 5
uint8_t SLBD[] = "SLBD";
#define SLBD_LEN 4
uint8_t RNRWT[] = "RNRWT";
#define RNRWT_LEN 5
uint8_t RLUN[] = "RLUN";
#define RLUN_LEN 4
uint8_t RLU[] = "RLU";
#define RLU_LEN 3
uint8_t RBSL[] = "RBSL";
#define RBSL_LEN 4
uint8_t SBW[] = "SBW";
#define SBW_LEN 3
uint8_t SCR[] = "SCR";
#define SCR_LEN 3
uint8_t SSF[] = "SSF";
#define SSF_LEN 3
uint8_t PWR[] = "PWR";
#define PWR_LEN 3
uint8_t DNM[] = "DNM";
#define DNM_LEN 3
uint8_t SLT[] = "SLT";
#define SLT_LEN 3
uint8_t FCV[] = "FCV";
#define FCV_LEN 3
uint8_t RPID[] = "RPID";
#define RPID_LEN 4
uint8_t SSC[] = "SSC";
#define SSC_LEN 3
uint8_t SCALB[] = "SCB";
#define SCALB_LEN 3
uint8_t SWV[] = "SWV";
#define SWV_LEN 3
uint8_t FRQ[] = "FRQ";
#define FRQ_LEN 3
uint8_t SETP[] = "SETP";
#define SETP_LEN 4
uint8_t DA[] = "DA";
#define DA_LEN 2
uint8_t DB[] = "DB";
#define DB_LEN 2
uint8_t SFM[] = "SFM";
#define SFM_LEN 3
uint8_t HDTC[]= "HDTC";
#define HDTC_LEN 4
uint8_t SMS[]= "SMS";
#define SMS_LEN 3
uint8_t FSRC[]= "FSRC";
#define FSRC_LEN 4
uint8_t FSRC_PAGE[]="flash_top_page";
#define FSRC_PAGE_LEN 14

#if WATER_OPERATE
uint8_t CALB[] = "CALB";
#define CALB_LEN 4
#endif 
#if S_5TM_OPERATE
uint8_t S_5TM_NUM[]="5TM_NUM";
#define S_5TM_NUM_LEN 7

uint8_t S_5TM_ADD[]="5TM_ADD";
#define S_5TM_ADD_LEN 7

uint8_t S_5TM_DEL[]="5TM_DEL";
#define S_5TM_DEL_LEN 7
#endif
#if modbus_mode
uint8_t MODBUS_CFG[]="MODBUS_CFG";
#define MODBUS_CFG_LEN 10
uint8_t MODBUS_DATA[]="MODBUS_DATA";
#define MODBUS_DATA_LEN 11
uint8_t CHECK_TYPE[]="CHECK_TYPE";
#define CHECK_TYPE_LEN 10
uint8_t CHECK_NORM[]="CHECK_NORM";
#define CHECK_NORM_LEN 10
uint8_t CHECK_NUM[]="CHECK_NUM";
#define CHECK_NUM_LEN 9
#endif

/**************************************************************
							传感器MAC
***************************************************************/
//获取
void at_mac_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t mac_len;
	uint8_t mac_buff[4];
	uint16_t mac = node_parameter.MAC;			    //获取节点MAC地址
	
	hex_to_ascii_in_order(mac, mac_buff, &mac_len);
	
	at_assamble_get_response(MAC, MAC_LEN, mac_buff, mac_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_mac_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t mac;
	ascii_to_hex_in_order((uint8_t *)&mac, 2, (*at_item).opt, (*at_item).opt_len);
	if(mac==0)
	{
		at_assamble_setting_response(MAC, MAC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.MAC = mac;					//设置节点MAC地址
		update_sysparam();
		at_assamble_setting_response(MAC, MAC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//传感器MAC
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
/**************************************************************
							传感器PAN
***************************************************************/
//获取
void at_pan_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t pan_len;
	uint8_t pan_buff[4];
	uint16_t pan = node_parameter.PAN;
	
	hex_to_ascii_in_order(pan, pan_buff, &pan_len);
	
	at_assamble_get_response(PAN, PAN_LEN, pan_buff, pan_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_pan_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t pan;
	ascii_to_hex_in_order((uint8_t *)&pan, 2, (*at_item).opt, (*at_item).opt_len);
	if(pan == 0)
	{
		at_assamble_setting_response(PAN, PAN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.PAN = pan;				
		update_sysparam();
		at_assamble_setting_response(PAN, PAN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);	
	}
}
//传感器PAN
void at_pan(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_pan_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_pan_set_handler(at_item);
			break;
		default:
			break;
	}
	
}
/**************************************************************
						工作周期
***************************************************************/
//获取
void at_tdti_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t tdti_len;
	uint8_t tdti_buff[4];
	uint16_t tdti = node_parameter.TDTI;
	
	dec_to_ascii_in_order(tdti, tdti_buff, &tdti_len);
	
	at_assamble_get_response(TDTI, TDTI_LEN, tdti_buff, tdti_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_tdti_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t tdti;
	ascii_to_dec_in_order((uint8_t *)&tdti, 2, (*at_item).opt, (*at_item).opt_len);
	if(tdti==0 || tdti>=0xffff)
	{
		at_assamble_setting_response(TDTI, TDTI_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.TDTI = tdti;					
		update_sysparam();
		at_assamble_setting_response(TDTI, TDTI_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//工作周期
void at_tdti(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_tdti_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_tdti_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
							采集周期
***************************************************************/
//获取
void at_ssti_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t ssti_len;
	uint8_t ssti_buff[4];
	uint16_t ssti = node_parameter.SSTI;			
	
	dec_to_ascii_in_order(ssti, ssti_buff, &ssti_len);
	
	at_assamble_get_response(SSTI, SSTI_LEN, ssti_buff, ssti_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_ssti_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t ssti;
	ascii_to_dec_in_order((uint8_t *)&ssti, 2, (*at_item).opt, (*at_item).opt_len);
	if(ssti==0 || ssti>=0xffff)
	{
		at_assamble_setting_response(SSTI, SSTI_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.SSTI = ssti;			
		update_sysparam();		
		at_assamble_setting_response(SSTI, SSTI_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//采样周期
void at_ssti(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_ssti_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_ssti_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
					 时间同步更新周期数TSDC
***************************************************************/
//获取
void at_tsdc_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t tsdc_len;
	uint8_t tsdc_buff[4];
	uint16_t tsdc = node_parameter.TSDC;
	
	dec_to_ascii_in_order(tsdc, tsdc_buff, &tsdc_len);
	
	at_assamble_get_response(TSDC, TSDC_LEN, tsdc_buff, tsdc_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_tsdc_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t tsdc;
	ascii_to_dec_in_order((uint8_t *)&tsdc, 2, (*at_item).opt, (*at_item).opt_len);
	if(tsdc<5 || tsdc>20)
	{
		at_assamble_setting_response(TSDC, TSDC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.TSDC = tsdc;					
		update_sysparam();
		at_assamble_setting_response(TSDC, TSDC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//时间同步更新周期数TSDC
void at_tsdc(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_tsdc_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_tsdc_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
					 数据包重传次数RTDC
***************************************************************/
//获取
void at_rtdc_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t rtdc_len;
	uint8_t rtdc_buff[4];
	uint16_t rtdc = node_parameter.RTDC;
	
	dec_to_ascii_in_order(rtdc, rtdc_buff, &rtdc_len);
	
	at_assamble_get_response(RTDC, RTDC_LEN, rtdc_buff, rtdc_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_rtdc_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t rtdc;
	ascii_to_dec_in_order((uint8_t *)&rtdc, 2, (*at_item).opt, (*at_item).opt_len);
	if(rtdc > 10)
	{
		at_assamble_setting_response(RTDC, RTDC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.RTDC = rtdc;				
		update_sysparam();
		at_assamble_setting_response(RTDC, RTDC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);	
	}
}
//数据包重传次数RTDC
void at_rtdc(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_rtdc_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_rtdc_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
				发包超时时间（从发包到接收完成）TPTO
***************************************************************/
//获取
void at_tpto_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t tpto_len;
	uint8_t tpto_buff[4];
	uint16_t tpto = node_parameter.TPTO;			
	
	dec_to_ascii_in_order(tpto, tpto_buff, &tpto_len);
	
	at_assamble_get_response(TPTO, TPTO_LEN, tpto_buff, tpto_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_tpto_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t tpto;
	ascii_to_dec_in_order((uint8_t *)&tpto, 2, (*at_item).opt, (*at_item).opt_len);
	if(tpto<40 || tpto>1000)
	{
		at_assamble_setting_response(TPTO, TPTO_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.TPTO = tpto;				
		update_sysparam();		
		at_assamble_setting_response(TPTO, TPTO_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//发包超时时间（从发包到接收完成）TPTO
void at_tpto(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_tpto_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_tpto_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
				连续通信失败周期数（重新寻找父节点）CFTOC
***************************************************************/
//获取
void at_cftoc_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t cftoc_len;
	uint8_t cftoc_buff[4];
	uint16_t cftoc = node_parameter.CFTOC;			
	
	dec_to_ascii_in_order(cftoc, cftoc_buff, &cftoc_len);
	
	at_assamble_get_response(CFTOC, CFTOC_LEN, cftoc_buff, cftoc_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_cftoc_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t cftoc;
	ascii_to_dec_in_order((uint8_t *)&cftoc, 2, (*at_item).opt, (*at_item).opt_len);
	if(cftoc<3 || cftoc>16)
	{
		at_assamble_setting_response(CFTOC, CFTOC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.CFTOC = cftoc;				
		update_sysparam();		
		at_assamble_setting_response(CFTOC, CFTOC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//连续通信失败周期数（重新寻找父节点）CFTOC
void at_cftoc(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_cftoc_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_cftoc_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
					传感器上电时间SPTD
***************************************************************/
//获取
void at_sptd_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sptd_len;
	uint8_t sptd_buff[4];
	uint16_t sptd = node_parameter.SPTD;
	
	dec_to_ascii_in_order(sptd, sptd_buff, &sptd_len);
	
	at_assamble_get_response(SPTD, SPTD_LEN, sptd_buff, sptd_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_sptd_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t sptd;
	ascii_to_dec_in_order((uint8_t *)&sptd, 2, (*at_item).opt, (*at_item).opt_len);
	if(sptd<1 || sptd>60000)
	{
		at_assamble_setting_response(SPTD, SPTD_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.SPTD = sptd;
		update_sysparam();
		at_assamble_setting_response(SPTD, SPTD_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	
}
void at_sptd(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_sptd_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_sptd_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
				每周期最大上传历史记录条数HISN
***************************************************************/
//获取
void at_hisn_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t hisn_len;
	uint8_t hisn_buff[4];
	uint16_t hisn = node_parameter.HISN;				//获取历史记录上次条数	
	dec_to_ascii_in_order(hisn, hisn_buff, &hisn_len);
	
	at_assamble_get_response(HISN, HISN_LEN, hisn_buff, hisn_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_hisn_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t hisn;
	ascii_to_dec_in_order((uint8_t *)&hisn, 2, (*at_item).opt, (*at_item).opt_len);
	if(hisn==0 || hisn>10)
	{
		at_assamble_setting_response(HISN, HISN_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.HISN = hisn;						//设置历史记录条数
		update_sysparam();
		at_assamble_setting_response(HISN, HISN_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//每周期最大上传历史记录条数HISN
void at_hisn(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_hisn_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_hisn_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
			 监听广播包时间长度(全周期监听时间)SLBD
***************************************************************/
//获取
void at_slbd_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t slbd_len;
	uint8_t slbd_buff[4];
	uint16_t slbd = node_parameter.SLBD;				//获取历史记录上次条数	
	dec_to_ascii_in_order(slbd, slbd_buff, &slbd_len);
	
	at_assamble_get_response(SLBD, SLBD_LEN, slbd_buff, slbd_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_slbd_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t slbd;
	ascii_to_dec_in_order((uint8_t *)&slbd, 2, (*at_item).opt, (*at_item).opt_len);
	if(slbd==0 || slbd>6000)
	{
		at_assamble_setting_response(SLBD, SLBD_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.SLBD = slbd;						//设置历史记录条数
		update_sysparam();
		at_assamble_setting_response(SLBD, SLBD_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//监听广播包时间长度(全周期监听时间)SLBD
void at_slbd(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_slbd_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_slbd_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
				上电广播入网请求等待时间RNRWT
***************************************************************/
//获取
void at_rnrwt_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t rnrwt_len;
	uint8_t rnrwt_buff[4];
	uint16_t rnrwt = node_parameter.RNRWT;				
	dec_to_ascii_in_order(rnrwt, rnrwt_buff, &rnrwt_len);
	
	at_assamble_get_response(RNRWT, RNRWT_LEN, rnrwt_buff, rnrwt_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_rnrwt_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t rnrwt;
	ascii_to_dec_in_order((uint8_t *)&rnrwt, 2, (*at_item).opt, (*at_item).opt_len);
	if(rnrwt==40 || rnrwt>2000)
	{
		at_assamble_setting_response(RNRWT, RNRWT_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.RNRWT = rnrwt;						
		update_sysparam();
		at_assamble_setting_response(RNRWT, RNRWT_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//上电广播入网请求等待时间RNRWT
void at_rnrwt(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_rnrwt_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_rnrwt_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
						通信带宽SBW
***************************************************************/
//获取
void at_sbw_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t bw_len;
    uint8_t bw_buff[4];
	uint8_t bw = node_parameter.SBW;
	
	convert_sbw_to_ascii(bw, bw_buff, &bw_len);
	at_assamble_get_response(SBW, SBW_LEN, bw_buff, bw_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_sbw_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t bw;
	bw = convert_ascii_to_sbw((*at_item).opt);
	if(check_bw(bw))
	{
		node_parameter.SBW = bw;
		update_sysparam();
		at_assamble_setting_response(SBW, SBW_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		at_assamble_setting_response(SBW, SBW_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
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
/**************************************************************
						编码率SCR
***************************************************************/
//获取
void at_scr_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t cr_len;
    uint8_t cr_buff[4];
	uint8_t cr = node_parameter.SCR;
	
	convert_scr_to_ascii(cr, cr_buff, &cr_len);
	at_assamble_get_response(SCR, SCR_LEN, cr_buff, cr_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_scr_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t cr;
	cr = convert_ascii_to_scr((*at_item).opt);
	if(check_cr(cr))
	{
		node_parameter.SCR = cr;
		update_sysparam();
		at_assamble_setting_response(SCR, SCR_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		at_assamble_setting_response(SCR, SCR_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
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
/**************************************************************
						SSF
***************************************************************/
//获取
void at_ssf_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sf_len;
    uint8_t sf_buff[4];
	uint8_t sf = node_parameter.SSF;
	
	convert_ssf_to_ascii(sf, sf_buff, &sf_len);
	at_assamble_get_response(SSF, SSF_LEN, sf_buff, sf_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_ssf_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sf;
	sf = convert_ascii_to_ssf((*at_item).opt);
	if(check_sf(sf))
	{
		node_parameter.SSF = sf;
		update_sysparam();
		at_assamble_setting_response(SSF, SSF_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		at_assamble_setting_response(SSF, SSF_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
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
/**************************************************************
						   发送功率
***************************************************************/
//获取
void at_pwr_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t pwr_len;
    uint8_t pwr_buff[4];
	uint8_t pwr = node_parameter.PWR;
	
	dec_to_ascii_in_order(pwr, pwr_buff, &pwr_len);
	at_assamble_get_response(PWR, PWR_LEN, pwr_buff, pwr_len, (*at_item).ack, &(*at_item).ack_len);
}
//设置
void at_pwr_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t pwr;
	ascii_to_dec_in_order((uint8_t *)&pwr, 1, (*at_item).opt, (*at_item).opt_len);
	if(pwr>15)
	{
		at_assamble_setting_response(PWR, PWR_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.PWR = pwr;						//设置发射功率
		update_sysparam();
		at_assamble_setting_response(PWR, PWR_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
void at_pwr(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
            at_pwr_get_handler(at_item);
            break;
        case AT_SET_TYPE:
            at_pwr_set_handler(at_item);
            break;
        default:
            break;
	}
}
/**************************************************************
							传感器FRQ
***************************************************************/
//获取
void at_frq_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t frq_len;
	uint8_t frq_buff[4];
	uint16_t frq = node_parameter.FRQ;			    //获取节点MAC地址
	
	dec_to_ascii_in_order(frq, frq_buff, &frq_len);
	
	at_assamble_get_response(FRQ, FRQ_LEN, frq_buff, frq_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_frq_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t frq;
	ascii_to_dec_in_order((uint8_t *)&frq, 2, (*at_item).opt, (*at_item).opt_len);
	if(frq < 4330 || frq > 5100)
	{
		at_assamble_setting_response(FRQ, FRQ_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.FRQ = frq;					//设置节点FRQ
		update_sysparam();
		at_assamble_setting_response(FRQ, FRQ_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//传感器FRQ
void at_frq(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_frq_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_frq_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
						  传感器自检
***************************************************************/
void at_ssc_get_handler(AT_CMD_TYPE* at_item)
{
	at_assamble_get_response(SSC, SSC_LEN, "ER", 2, (*at_item).ack, &(*at_item).ack_len);
}
void at_ssc_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t opt;
	ascii_to_dec_in_order((uint8_t *)&opt, 1, (*at_item).opt, (*at_item).opt_len);
	if(opt == 1)
	{
		//开始自检
		post_sen_work_ev(SYSTEM_ENTER_CHECK_MODE);
		at_assamble_setting_response(SSC, SSC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else if(opt == 2)
	{
		//结束自检
		post_sen_work_ev(SYSTEM_LEAVE_CHECK_MODE);
		at_assamble_setting_response(SSC, SSC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
	else
	{
		//其他则任务无效
		at_assamble_setting_response(SSC, SSC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	
	
}
void at_ssc(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_ssc_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_ssc_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
						  传感器标定
***************************************************************/
void at_calb_op_handler(AT_CMD_TYPE* at_item)
{
	#if WATER_OPERATE
	if(node_parameter.SETP==WATER_TYPE)
	{
		post_water_calibration();
	}
	#endif
	#if SCA126T_OPERATE
	if(node_parameter.SETP==SCA126T_TYPE)
	{
		post_sca126t_calibration();
	}
	#endif
	//post_co2_calibration();
	at_assamble_setting_response(SCALB, SCALB_LEN, (*at_item).ack, &(*at_item).ack_len, WT_ACK);
}
//返回传感器设置数据
void at_calb_get_handler(AT_CMD_TYPE* at_item)
{
	
				    //获取节点MAC地址
	#if WATER_OPERATE
	uint16_t calb;
	uint8_t calb_len;
	uint8_t calb_buff[4];
	if(node_parameter.SETP==WATER_TYPE)
	{
		calb = node_parameter.WVC;
	}
	dec_to_ascii_in_order(calb, calb_buff, &calb_len);
	at_assamble_get_response(CALB, CALB_LEN, calb_buff, calb_len, (*at_item).ack, &(*at_item).ack_len); 
	#endif
//	#if SCA126T_OPERATE
//	if(node_parameter.SETP==SCA126T_TYPE)
//	{
//		uint8_t calb = node_parameter.channel[11];
//	}
//	dec_to_ascii_in_order(calb, calb_buff, &calb_len);
//	at_assamble_get_response(calb, CALB_LEN, calb_buff, calb_len, (*at_item).ack, &(*at_item).ack_len); 
//	#endif
	
}
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
/**************************************************************
						 版本号SWV
***************************************************************/
void at_swv_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t software_version_buff[10];
	uint8_t len;
	get_software_version(software_version_buff, &len);

	at_assamble_get_response(SWV, SWV_LEN, software_version_buff, len, (*at_item).ack, &(*at_item).ack_len); 	
}
void at_swv_set_handler(AT_CMD_TYPE* at_item)
{
	at_assamble_setting_response(SWV, SWV_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
}
void at_swv(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_swv_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_swv_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
							传感器类型SETP
***************************************************************/
//获取
void at_setp_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t setp_len;
	uint8_t setp_buff[4];
	uint16_t setp = node_parameter.SETP;			  
	
	dec_to_ascii_in_order(setp, setp_buff, &setp_len);
	
	at_assamble_get_response(SETP, SETP_LEN, setp_buff, setp_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_setp_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t setp;
	ascii_to_dec_in_order((uint8_t *)&setp, 2, (*at_item).opt, (*at_item).opt_len);
	if(setp == 0 || setp > 9)
	{
		at_assamble_setting_response(SETP, SETP_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.SETP = setp;					//设置节点FRQ
		update_sysparam();
		at_assamble_setting_response(SETP, SETP_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//传感器类型
void at_setp(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_setp_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_setp_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
										历史数据上传次数
***************************************************************/
//获取
void at_hdtc_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t hdtc_len;
	uint8_t hdtc_buff[4];
	uint16_t hdtc = node_parameter.HDTC;			  
	
	dec_to_ascii_in_order(hdtc, hdtc_buff, &hdtc_len);
	
	at_assamble_get_response(HDTC, HDTC_LEN, hdtc_buff, hdtc_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_hdtc_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t hdtc;
	ascii_to_dec_in_order((uint8_t *)&hdtc, 2, (*at_item).opt, (*at_item).opt_len);
	if((hdtc == 0)||(hdtc>30))
	{
		at_assamble_setting_response(HDTC, HDTC_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		node_parameter.HDTC = hdtc;					//设置节点FRQ
		update_sysparam();
		at_assamble_setting_response(HDTC, HDTC_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//传感器类型
void at_hdtc(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_hdtc_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_hdtc_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
							工作模式切换
***************************************************************/
//获取
void at_sms_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t setp_len;
	uint8_t setp_buff[4];
	uint16_t setp = node_parameter.SETP;			  
	
	dec_to_ascii_in_order(setp, setp_buff, &setp_len);
	
	at_assamble_get_response(SETP, SETP_LEN, setp_buff, setp_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_sms_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t sms;
	ascii_to_dec_in_order((uint8_t *)&sms, 2, (*at_item).opt, (*at_item).opt_len);
	if( sms > 9)
	{
		at_assamble_setting_response(SMS, SMS_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		process_post(&cycle_work_process,SMS_EVENT,(void *)sms);
		at_assamble_setting_response(SMS, SMS_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
//传感器类型
void at_sms(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			//at_sms_get_handler(at_item);
			break;
		case AT_SET_TYPE:  
			at_sms_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
							格式化flash
***************************************************************/
//获取
void at_fsrc_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t fsrc_len;
	uint8_t fsrc_buff[4];		  
	
	uint32_t fsrc=flash_parameter_display(4);			  
	
	dec_to_ascii_in_order(fsrc, fsrc_buff, &fsrc_len);

	at_assamble_get_response(FSRC_PAGE, FSRC_PAGE_LEN, fsrc_buff, fsrc_len, (*at_item).ack, &(*at_item).ack_len); 
	
}
void at_fsrc_op_handler(AT_CMD_TYPE* at_item)
{
	
	at_assamble_setting_response(FSRC, FSRC_LEN, (*at_item).ack, &(*at_item).ack_len, WT_ACK);
 	process_post(&cycle_work_process,FORMAT_FLASH_EVENT,NULL);
}

void at_fsrc(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_fsrc_get_handler(at_item);
			break;
		case AT_SET_TYPE:  
			
			break;
		case AT_OP_TYPE:
			at_fsrc_op_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
						 5TM/5TE设置
***************************************************************/
#if S_5TM_OPERATE
/*uint8_t S_5TM_NUM[]="5TM_NUM";
#define S_5TM_NUM_LEN 7

uint8_t S_5TM_ADD[]="5TM_ADD";
#define S_5TM_ADD_LEN 7

uint8_t S_5TM_DEL[]="5TM_DEL";
#define S_5TM_DEL_LEN 7*/
//获取
void at_num_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t num_len;
	uint8_t num_buff[4];
	uint8_t num = node_parameter.channel_len;			  
	
	dec_to_ascii_in_order(num, num_buff, &num_len);
	
	at_assamble_get_response(S_5TM_NUM, S_5TM_NUM_LEN, num_buff, num_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_num_set_handler(AT_CMD_TYPE* at_item)
{
	static uint8_t num;
	ascii_to_dec_in_order((uint8_t *)&num, 1, (*at_item).opt, (*at_item).opt_len);
	post_5tm_cfg(&num);
}
void at_5tm_num(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_num_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_num_set_handler(at_item);
			break;
		default:
			break;
	}
}
void at_add_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t add_len;
	uint8_t add_buff[4];
	uint8_t add = node_parameter.channel_len;			  
	
	dec_to_ascii_in_order(add, add_buff, &add_len);
	
	at_assamble_get_response(S_5TM_ADD, S_5TM_ADD_LEN, add_buff, add_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_add_set_handler(AT_CMD_TYPE* at_item)
{
	static uint8_t add;
	add=(*at_item).opt[0];
	//ascii_to_dec_in_order((uint8_t *)&add, 1, (*at_item).opt, (*at_item).opt_len);
	post_5tm_add(&add);
}
void at_5tm_add(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
		//	at_add_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_add_set_handler(at_item);
			break;
		default:
			break;
	}
}
void at_del_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t add_len;
	uint8_t add_buff[4];
	uint8_t add = node_parameter.channel_num;			  
	
	dec_to_ascii_in_order(add, add_buff, &add_len);
	
	at_assamble_get_response(S_5TM_ADD, S_5TM_ADD_LEN, add_buff, add_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_del_set_handler(AT_CMD_TYPE* at_item)
{
	static uint8_t del;
	del=(*at_item).opt[0];
	//ascii_to_dec_in_order((uint8_t *)&add, 1, (*at_item).opt, (*at_item).opt_len);
	post_5tm_del(&del);
}
void at_5tm_del(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			//at_del_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_del_set_handler(at_item);
			break;
		default:
			break;
	}
}
#endif
/**************************************************************
											modbus配置
***************************************************************/
#if modbus_mode
extern uint8_t modbus_sequence_structure_model[12][12];
extern uint8_t modbus_send_data_model[12][12];
extern uint8_t modbus_sequence_structure_model_num;
extern uint8_t modbus_send_data_model_num;
extern modbus_structure sensor_modbus;
//获取
void at_modbus_cfg_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t cfg_len;
	cfg_len=node_parameter.modbus_sequence_len;
	
	at_assamble_get_response(MODBUS_CFG, MODBUS_CFG_LEN, node_parameter.modbus_sequence, cfg_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_modbus_cfg_set_handler(AT_CMD_TYPE* at_item)
{
	letter_converter((*at_item).opt, (*at_item).opt_len);
	
	if((*at_item).opt_len>20)
	{ 
		at_assamble_setting_response(MODBUS_CFG, MODBUS_CFG_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	if(((*at_item).opt[0]>='0')&&((*at_item).opt[0]<='9'))
	{
		uint8_t num=(*at_item).opt[0]-'0';
		if(modbus_sequence_structure_model_num>num)
		{
			node_parameter.modbus_sequence_len=strlen((char*)modbus_sequence_structure_model[num]);
			memcpy(node_parameter.modbus_sequence,modbus_sequence_structure_model[num],node_parameter.modbus_sequence_len);
			memcpy(sensor_modbus.modbus_send_sequence, node_parameter.modbus_sequence, node_parameter.modbus_sequence_len);
			modbus_cfg_sequence(&sensor_modbus);
			update_sysparam();
			at_assamble_setting_response(MODBUS_CFG, MODBUS_CFG_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
		}
		else 
		{
			at_assamble_setting_response(MODBUS_CFG, MODBUS_CFG_LEN, (*at_item).ack, &(*at_item).ack_len, NONE);
		}
	}
	else
	{	
		node_parameter.modbus_sequence_len=(*at_item).opt_len;
		memcpy(node_parameter.modbus_sequence,(*at_item).opt,(*at_item).opt_len);
		
		memcpy(sensor_modbus.modbus_send_sequence,(*at_item).opt,(*at_item).opt_len);
		modbus_cfg_sequence(&sensor_modbus);
		update_sysparam();
		at_assamble_setting_response(MODBUS_CFG, MODBUS_CFG_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}
}
void at_modbus_cfg(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_modbus_cfg_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_modbus_cfg_set_handler(at_item);
			break;
		default:
			break;
	}
}
void at_modbus_data_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t data_len,data[40],len;
	data_len=node_parameter.modbus_array_len;
	data_len*=2;
	for(uint8_t i=0;i<data_len;i++)
	{
		hex_to_ascii_in_order(node_parameter.modbus_array[i],data+(i*2),&len);
	}
	at_assamble_get_response(MODBUS_DATA, MODBUS_DATA_LEN, data, data_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_modbus_data_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t modbus_data[20];
	uint8_t len=0;
	if((*at_item).opt_len<2)
	{
		len=(*at_item).opt[0]-'0';
		if(modbus_send_data_model_num>len)
		{
				uint8_t i=sizeof(modbus_send_data_model[0]);
				node_parameter.modbus_array_len=modbus_strlen(modbus_send_data_model[len],i);
				memcpy(node_parameter.modbus_array,modbus_send_data_model[len],node_parameter.modbus_array_len);
				modbus_send_data_storage(node_parameter.modbus_array,&sensor_modbus,node_parameter.modbus_array_len);				
				update_sysparam();
				at_assamble_setting_response(MODBUS_DATA, MODBUS_DATA_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
		}
		else
		{
			at_assamble_setting_response(MODBUS_DATA, MODBUS_DATA_LEN, (*at_item).ack, &(*at_item).ack_len, NONE);
		}
	}
	else
	{
		len=((*at_item).opt_len)/2;
		if(ascii_to_hex(modbus_data, (*at_item).opt, (*at_item).opt_len)==0)
		{
			at_assamble_setting_response(MODBUS_DATA, MODBUS_DATA_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
		}
		else
		{
			node_parameter.modbus_array_len=len;
			memcpy(node_parameter.modbus_array,modbus_data,len);
			modbus_send_data_storage(modbus_data,&sensor_modbus,len);				
			update_sysparam();
			at_assamble_setting_response(MODBUS_DATA, MODBUS_DATA_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
		}
	}
		
}

void at_modbus_data(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_modbus_data_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_modbus_data_set_handler(at_item);
			break;
		default:
			break;
	}
}

void at_check_type_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t data_len,data[10];
	data_len=3;
	if(node_parameter.check_style==modbus_check_style_crc)
	{
		data[0]='c';
		data[1]='r';
		data[2]='c';
	}
	else if(node_parameter.check_style==modbus_check_style_lrc)
	{
		data[0]='l';
		data[1]='r';
		data[2]='c';
	}
	else if(node_parameter.check_style==modbus_check_style_bcc)
	{
		data[0]='b';
		data[1]='c';
		data[2]='c';
	}
	else if(node_parameter.check_style==modbus_check_style_sum)
	{
		data[0]='s';
		data[1]='u';
		data[2]='m';
	}
	else
	{
		data[0]='e';
		data[1]='r';
		data[2]='r';
		data[3]='o';
		data[4]='r';
		data_len=5;
	}
	at_assamble_get_response(CHECK_TYPE, CHECK_TYPE_LEN, data, data_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_check_type_set_handler(AT_CMD_TYPE* at_item)
{
	letter_converter((*at_item).opt, (*at_item).opt_len);
	if(((*at_item).opt[0]=='c')&&((*at_item).opt[1]=='r')&&((*at_item).opt[2]=='c'))
	{
		sensor_modbus.modbus_check_style=modbus_check_style_crc;
		node_parameter.check_style=modbus_check_style_crc;														
		    	
	}
	else if(((*at_item).opt[0]=='l')&&((*at_item).opt[1]=='r')&&((*at_item).opt[2]=='c'))
	{
		sensor_modbus.modbus_check_style=modbus_check_style_lrc;
		node_parameter.check_style=modbus_check_style_lrc;	
	}
	else if(((*at_item).opt[0]=='b')&&((*at_item).opt[1]=='c')&&((*at_item).opt[2]=='c'))
	{
		sensor_modbus.modbus_check_style=modbus_check_style_bcc;
		node_parameter.check_style=modbus_check_style_bcc;	
	}
	else if(((*at_item).opt[0]=='s')&&((*at_item).opt[1]=='u')&&((*at_item).opt[2]=='m'))
	{
		sensor_modbus.modbus_check_style=modbus_check_style_sum;
		node_parameter.check_style=modbus_check_style_sum;	
	}
	else
	{
		at_assamble_setting_response(CHECK_TYPE, CHECK_TYPE_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
		return;
	}	
	update_sysparam();
	at_assamble_setting_response(CHECK_TYPE, CHECK_TYPE_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);

}  												

void at_check_type(AT_CMD_TYPE *at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_check_type_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_check_type_set_handler(at_item);
			break;
		default:
			break;
	}
}



void at_check_norm_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t data_len,data[10];
	data_len=3;
	if(node_parameter.check_style_value==crc_rtu_default)
	{
		data[0]='r';
		data[1]='t';
		data[2]='u';
	}
	else if(node_parameter.check_style_value==crc_ccitt_default)
	{
		data[0]='c';
		data[1]='c';
		data[2]='i';
		data[3]='t';
		data[4]='t';
		data_len=5;
	}
	else if(node_parameter.check_style_value==crc_usa_default)
	{
		data[0]='u';
		data[1]='s';
		data[2]='a';
	}
	else
	{
		data[0]='e';
		data[1]='r';
		data[2]='r';
		data[3]='o';
		data[4]='r';
		data_len=5;
	}
	at_assamble_get_response(CHECK_NORM, CHECK_NORM_LEN, data, data_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_check_norm_set_handler(AT_CMD_TYPE* at_item)
{
	letter_converter((*at_item).opt, (*at_item).opt_len);
	if(sensor_modbus.modbus_check_style!=modbus_check_style_crc)
	{
		at_assamble_setting_response(CHECK_NORM, CHECK_NORM_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
		return;
	}
	else if(((*at_item).opt[0]=='r')&&((*at_item).opt[1]=='t')&&((*at_item).opt[2]=='u'))
	{
		sensor_modbus.modbus_check_style_value=crc_rtu_default;
		node_parameter.check_style_value=crc_rtu_default;														
		    	
	}
	else if(((*at_item).opt[0]=='c')&&((*at_item).opt[1]=='c')&&((*at_item).opt[2]=='i'))
	{
		sensor_modbus.modbus_check_style_value=crc_ccitt_default;
		node_parameter.check_style_value=crc_ccitt_default;
	}
	else if(((*at_item).opt[0]=='u')&&((*at_item).opt[1]=='s')&&((*at_item).opt[2]=='a'))
	{
		sensor_modbus.modbus_check_style_value=crc_usa_default;
		node_parameter.check_style_value=crc_usa_default;	
	}
	else
	{
		at_assamble_setting_response(CHECK_NORM, CHECK_NORM_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
		return;
	}	
	update_sysparam();
	at_assamble_setting_response(CHECK_NORM, CHECK_NORM_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);

}
void at_check_norm(AT_CMD_TYPE *at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_check_norm_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_check_norm_set_handler(at_item);
			break;
		default:
			break;
	}
}
//获取
void at_check_num_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t num_len;
	uint8_t num_buff[4];
	uint16_t num = node_parameter.check_crc_init;			
	
	dec_to_ascii_in_order(num, num_buff, &num_len);
	
	at_assamble_get_response(CHECK_NUM, CHECK_NUM_LEN, num_buff, num_len, (*at_item).ack, &(*at_item).ack_len); 
}
//设置
void at_check_num_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t num;
	ascii_to_hex_in_order((uint8_t *)&num, 2, (*at_item).opt, (*at_item).opt_len);
	if(sensor_modbus.modbus_check_style!=modbus_check_style_crc)
	{
		at_assamble_setting_response(CHECK_NUM, CHECK_NUM_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
		return;
	}
	if(num>0xffff)
	{
		at_assamble_setting_response(CHECK_NUM, CHECK_NUM_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	else
	{
		sensor_modbus.modbus_check_crc_init=num;
		node_parameter.check_crc_init=num;		
		update_sysparam();		
		at_assamble_setting_response(CHECK_NUM, CHECK_NUM_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	} 
}
void at_check_num(AT_CMD_TYPE *at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_check_num_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_check_num_set_handler(at_item);
			break;
		default:
			break;
	}
}
#endif
/**************************************************************
						公式修正系数A（ax+b=y）
***************************************************************/
void at_da_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t da_len;
	uint8_t da_buffer[4];
	uint16_t da = node_parameter.DA;
	
	dec_to_ascii_in_order(da, da_buffer, &da_len);
	
	at_assamble_get_response(DA, DA_LEN, da_buffer, da_len, (*at_item).ack, &(*at_item).ack_len); 
}
void at_da_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t da;
	ascii_to_dec_in_order((uint8_t *)&da, 2, (*at_item).opt, (*at_item).opt_len);
	
	node_parameter.DA = da;					
	update_sysparam();
	at_assamble_setting_response(DA, DA_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
}
void at_da(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_da_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_da_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
						公式修正系数B（ax+b=y）
***************************************************************/
void at_db_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t db_len;
	uint8_t db_buffer[4];
	uint16_t db = node_parameter.DB;
	
	dec_to_ascii_in_order(db, db_buffer, &db_len);
	
	at_assamble_get_response(DB, DB_LEN, db_buffer, db_len, (*at_item).ack, &(*at_item).ack_len); 
}
void at_db_set_handler(AT_CMD_TYPE* at_item)
{
	uint16_t db;
	ascii_to_dec_in_order((uint8_t *)&db, 2, (*at_item).opt, (*at_item).opt_len);
	
	node_parameter.DB = db;					
	update_sysparam();
	at_assamble_setting_response(DB, DB_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
}
void at_db(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_db_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_db_set_handler(at_item);
			break;
		default:
			break;
	}
}
/**************************************************************
						搜索父节点方式
***************************************************************/
void at_sfm_get_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sfm_len;
	uint8_t sfm_buffer[4];
	uint16_t sfm = node_parameter.SFM;
	
	dec_to_ascii_in_order(sfm, sfm_buffer, &sfm_len);
	
	at_assamble_get_response(SFM, SFM_LEN, sfm_buffer, sfm_len, (*at_item).ack, &(*at_item).ack_len); 
}
void at_sfm_set_handler(AT_CMD_TYPE* at_item)
{
	uint8_t sfm;
	ascii_to_dec_in_order((uint8_t *)&sfm, 1, (*at_item).opt, (*at_item).opt_len);
	if(sfm == 1 || sfm == 2)
	{
		//成功
		node_parameter.SFM = sfm;
		update_sysparam();
		at_assamble_setting_response(SFM, SFM_LEN, (*at_item).ack, &(*at_item).ack_len, SUCCESS_ACK);
	}else{
		//失败
		at_assamble_setting_response(SFM, SFM_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
	}
	
}
void at_sfm(AT_CMD_TYPE* at_item)
{
	uint8_t type = (*at_item).type;
	switch(type)
	{
		case AT_GET_TYPE:
			at_sfm_get_handler(at_item);
			break;
		case AT_SET_TYPE:
			at_sfm_set_handler(at_item);
			break;
		default:
			break;
	}
}








