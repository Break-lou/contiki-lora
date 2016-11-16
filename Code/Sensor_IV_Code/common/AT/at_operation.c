#include "AT_OPERATION.h"
#include "AT_CMD.h"
#include <string.h>


#define AT_DELIM ";"


uint8_t EMPTY[] = "NULL";
#define EMPTY_LEN 4

uint8_t OPTER[] = "+OPT:ER";
#define OPTER_LEN 7

AT_CMD_TYPE at_items[20];       //限制最多一次解析20条

bool at_item_analyzer(uint8_t* item,int item_len,int items_index);   //第二个参数是存储在AT指令缓存中的位置
//uint8_t get_str_len(uint8_t* str);
int8_t find_character(uint8_t* str, uint8_t str_len, uint8_t search_begin);
bool at_analyzer(AT_CMD_TYPE* at_item);
void at_null(AT_CMD_TYPE* at_item);



//第三个是实际被解析的条数
AT_CMD_TYPE* at_disassemble(uint8_t* at_strs, uint8_t at_str_len, uint8_t at_num)
{
	int i = 0;
	int index = 0;
	uint8_t begin = 0;
	
	index = find_character(at_strs, at_str_len, index);
	while(index != -1)
	{
		at_item_analyzer(at_strs+begin,index-begin,i);
		i++;
		if((index+2) >= at_str_len)
		{
			//搜索结束
			break;
		}
		else
		{
			//继续下一次搜索
			if(at_strs[index+2] == ';')
			{
				begin = index+3;
				index = find_character(at_strs, at_str_len, begin);
			}
		}
		
		
	}

	return at_items;
}
//传入的必须是带\r\n结尾的AT指令
bool at_item_analyzer(uint8_t* item,int item_len,int items_index)
{
	char i;

    for(i=0; i<item_len; i++)
    {
        if((item[i]==AT_GET_TYPE) || (item[i]==AT_SET_TYPE) || (item[i]==AT_OP_TYPE))
        {
            break;
        }
    }
    if(i == item_len)
    {
        //未找到操作符，不是正确的AT指令，默认返回"+OPT:ER"
        at_items[items_index].ack_len = OPTER_LEN;
        memcpy(at_items[items_index].ack, OPTER, at_items[items_index].ack_len);
        return true;
    }
    at_items[items_index].name_len = i;
	memcpy(at_items[items_index].name, item, at_items[items_index].name_len);
    at_items[items_index].type = item[i];
    at_items[items_index].opt_len = item_len - i - 1;	
    memcpy(at_items[items_index].opt, item+i+1, at_items[items_index].opt_len);
    //解析
    at_analyzer(&(at_items[items_index]));
    
    return true;
}
//组装设置命令的应答
void at_assamble_setting_response(uint8_t* cmd, uint8_t cmd_len,uint8_t* dest, uint8_t* len, uint8_t isSuccess)
{
	dest[0] = '+';
	memcpy(dest+1, cmd, cmd_len);
	dest[1+cmd_len] = ':';
	if(isSuccess == 1)
	{
		dest[2+cmd_len] = 'O';
		dest[3+cmd_len] = 'K';
	}
	else if(isSuccess == 0){
		dest[2+cmd_len] = 'E';
		dest[3+cmd_len] = 'R';
	}
	else if(isSuccess == 2){
		dest[2+cmd_len] = 'W';
		dest[3+cmd_len] = 'T';
	}
	else if(isSuccess == 3){
		dest[2+cmd_len] = 'N';
		dest[3+cmd_len] = 'O';
		dest[4+cmd_len] = 'N';
		dest[5+cmd_len] = 'E';
		dest[6+cmd_len] = ';';
		*len = 7+cmd_len;
		return;
	}
	dest[4+cmd_len] = ';';
	
	*len = 5+cmd_len;
}
//组装获取命令的应答
void at_assamble_get_response(uint8_t* cmd, uint8_t cmd_len,uint8_t* opt_ack, uint8_t opt_ack_len, uint8_t* dest, uint8_t* len)
{
	dest[0] = '+';
	memcpy(dest+1, cmd, cmd_len);
	dest[1+cmd_len] = ':';
	memcpy(dest+2+cmd_len, opt_ack, opt_ack_len);
	dest[2+cmd_len+opt_ack_len] = ';';
	
	*len = 3+cmd_len+opt_ack_len;
}
//解析
bool at_analyzer(AT_CMD_TYPE* at_item)
{
	//全部转换为小写
    letter_converter((*at_item).name, (*at_item).name_len);
	if((strncmp((char*)(*at_item).name, "at+mac", 6)==0))		    at_mac(at_item);
	else if((strncmp((char*)(*at_item).name, "at+pan", 6)==0))	at_pan(at_item);
	else if((strncmp((char*)(*at_item).name, "at+tdti", 7)==0))	at_tdti(at_item);
	else if((strncmp((char*)(*at_item).name, "at+ssti", 7)==0))	at_ssti(at_item);
	else if((strncmp((char*)(*at_item).name, "at+rtdc", 7)==0))	at_rtdc(at_item);
	else if((strncmp((char*)(*at_item).name, "at+tsdc", 7)==0))	at_tsdc(at_item);
    else if((strncmp((char*)(*at_item).name, "at+tpto", 7)==0))	at_tpto(at_item);
    else if((strncmp((char*)(*at_item).name, "at+hisn", 7)==0))	at_hisn(at_item);
    else if((strncmp((char*)(*at_item).name, "at+cftoc", 8)==0))	at_cftoc(at_item);
    else if((strncmp((char*)(*at_item).name, "at+sptd", 7)==0))	at_sptd(at_item);
    else if((strncmp((char*)(*at_item).name, "at+slbd", 7)==0))	at_slbd(at_item);
	else if((strncmp((char*)(*at_item).name, "at+rnrwt", 8)==0))	at_rnrwt(at_item);    
	else if((strncmp((char*)(*at_item).name, "at+sbw", 6)==0))	at_sbw(at_item);    
    else if((strncmp((char*)(*at_item).name, "at+scr", 6)==0))	at_scr(at_item);
	else if((strncmp((char*)(*at_item).name, "at+ssf", 6)==0))	at_ssf(at_item);
	else if((strncmp((char*)(*at_item).name, "at+pwr", 6)==0))	at_pwr(at_item);
	else if((strncmp((char*)(*at_item).name, "at+frq", 6)==0))	at_frq(at_item);
	else if((strncmp((char*)(*at_item).name, "at+ssc", 6)==0))	at_ssc(at_item);
	else if((strncmp((char*)(*at_item).name, "at+scb", 6)==0))	at_calb(at_item);
	else if((strncmp((char*)(*at_item).name, "at+swv", 6)==0))	at_swv(at_item);
	else if((strncmp((char*)(*at_item).name, "at+da", 5)==0))		at_da(at_item);
	else if((strncmp((char*)(*at_item).name, "at+db", 5)==0))		at_db(at_item);
	else if((strncmp((char*)(*at_item).name, "at+sfm", 6)==0))	at_sfm(at_item);
	else if((strncmp((char*)(*at_item).name, "at+setp", 7)==0))	at_setp(at_item);
	else if((strncmp((char*)(*at_item).name, "at+hdtc", 7)==0))	at_hdtc(at_item);
	else if((strncmp((char*)(*at_item).name, "at+sms", 6)==0))	at_sms(at_item);
	else if((strncmp((char*)(*at_item).name, "at+fsrc", 7)==0))	at_fsrc(at_item);
	#if S_5TM_OPERATE 
	else if((strncmp((char*)(*at_item).name, "at+5tm_num", 10)==0))	at_5tm_num(at_item);
	else if((strncmp((char*)(*at_item).name, "at+5tm_add", 10)==0))	at_5tm_add(at_item);
	else if((strncmp((char*)(*at_item).name, "at+5tm_del", 10)==0))	at_5tm_del(at_item);
  #endif																		
	#if modbus_mode
	else if((strncmp((char*)(*at_item).name, "at+m_cfg", 8)==0))	at_modbus_cfg(at_item);
	else if((strncmp((char*)(*at_item).name, "at+m_data", 9)==0))	at_modbus_data(at_item);
	else if((strncmp((char*)(*at_item).name, "at+c_type", 9)==0))	at_check_type(at_item);
	else if((strncmp((char*)(*at_item).name, "at+c_norm", 9)==0))	at_check_norm(at_item);
	else if((strncmp((char*)(*at_item).name, "at+c_num", 8)==0))	at_check_num(at_item);
	#endif
	else at_null(at_item);
	
	return true;
}




//符合AT指令格式，但未实现的指令
void at_null(AT_CMD_TYPE* at_item)
{
	at_assamble_setting_response(EMPTY, EMPTY_LEN, (*at_item).ack, &(*at_item).ack_len, FAIL_ACK);
}




//获取字符串长度，以0x00结尾
//uint8_t get_str_len(uint8_t* str)
//{
//	uint8_t t = str[0];
//	uint8_t len = 0;
//	while(t != 0x00)
//	{
//		len++;
//		t = str[len];
//	}
//	return len;
//}

//查找连续的\r\n，若找到，则返回1，否则返回0
int8_t find_character(uint8_t* str, uint8_t str_len, uint8_t search_begin)
{
	int i;
	for(i=search_begin; i<str_len; i++)
	{
		if((str[i] == '\r') && (str[i+1] == '\n'))
		{
			return i;
		}
	}
	return -1;
}

//全部转换为小写
void letter_converter(uint8_t* letter, uint8_t len)
{
    int i;
    for(i=0; i<len; i++)
    {
        if(letter[i]>='A' && letter[i]<='Z')
        {
            //大写字母转换为小写
            letter[i] = letter[i]+32;
        }
    }
}

void clear_at_item(AT_CMD_TYPE* at_item)
{
	memset(at_item->ack, 0x00, at_item->ack_len);
	memset(at_item->name, 0x00, at_item->name_len);
	memset(at_item->opt, 0x00, at_item->opt_len);
	at_item->type = 0x00;
	at_item->ack_len = 0x00;
	at_item->name_len = 0x00;
	at_item->opt_len = 0x00;
}
