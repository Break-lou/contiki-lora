#ifndef __AT_OPERATION__
#define __AT_OPERATION__



#include <stdint.h>
#include <stdbool.h>


//该结构体对应一条AT指令:指令名称，指令类型，操作符
typedef struct AT_CMD
{
    uint8_t name[10];
    uint8_t name_len;
    uint8_t type;
    uint8_t opt[20];
    uint8_t opt_len;
	
	uint8_t ack[20];	//AT指令回复
	uint8_t ack_len;	
}__attribute__((packed)) AT_CMD_TYPE;



#define AT_GET_TYPE '?'     //获取
#define AT_SET_TYPE '='     //设置
#define AT_OP_TYPE '>'      //操作

#define SUCCESS_ACK 1
#define FAIL_ACK 	0
#define WT_ACK		2
#define NONE     3

AT_CMD_TYPE* at_disassemble(uint8_t* at_strs, uint8_t at_str_len, uint8_t at_num);
void at_assamble_setting_response(uint8_t* cmd, uint8_t cmd_len,uint8_t* dest, uint8_t* len, uint8_t isSuccess);
void at_assamble_get_response(uint8_t* cmd, uint8_t cmd_len,uint8_t* opt_ack, uint8_t opt_ack_len, uint8_t* dest, uint8_t* len);
void clear_at_item(AT_CMD_TYPE* at_item);;
void letter_converter(uint8_t* letter, uint8_t len);

#endif
