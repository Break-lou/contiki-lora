#ifndef __SX127X_APP_H__
#define __SX127X_APP_H__

#include <si32_device.h>

#define MAX17dbm     1
#define MAX20dbm     0


//===================================定义===================================================
typedef enum
{
    Init_LoRa_0_5K=1,
	Init_LoRa_1K,
    Init_LoRa_4K,
    Init_LoRa_8K,
	Init_LoRa_12K
}tSX127xInitSPD;      		//定义速率枚举

typedef enum
{
    NORMAL,                	//正常      
    PARAMETER_INVALID,    	//参数不可用
    SPI_READCHECK_WRONG,  	//SPI出错
}tSX127xError;           	//定义出错枚举

typedef enum
{
    SLEEP,
    STANDBY,
    TX_ONGOING,
    RX_ONGOING,
}tSX127xState;    	//定义RF物理状态，用户可以不使用

typedef enum
{
    HOLDON,
    TX,
    LISTENING,  
}tRadio_Machine;   	//定义逻辑状态，用户可以不使用

typedef enum
{
    MASTER,
    SLAVE,
}tMasterSlave;   	//定义主从枚举 ，测试时用

typedef struct
{
    tMasterSlave   MasterSlave;  	//主从
    tSX127xState   SX127xState;  	//物理状态
    tRadio_Machine Machine;      	//逻辑状态
}stRadio_Situation;          		//定义状态结构体

tSX127xError sx127x_init(tSX127xInitSPD initPara,unsigned char Pout);
void sx127x_send_packet(uint8_t*data,uint8_t size);
void sx127x_rx_mode(uint8_t clen);
void sx127x_rx_vari_packet(uint8_t*cbuf,uint8_t *csize);
void sx127x_rx_fixi_packet(uint8_t*cbuf,uint8_t csize);
void sx127x_sleep_mode(void);
void sx127x_standby_mode(void);
uint8_t sx127x_set_frq(uint8_t ch);
void sx127x_reset(void);
uint8_t sx127x_modify_frq(uint16_t frq);
uint8_t sx127x_modify_spd(tSX127xInitSPD spd);
uint8_t sx127x_get_rssi(void);



uint8_t sx127x_read_bw(void);
void sx127x_modify_bw(uint8_t bw);
uint8_t sx127x_read_cr(void);
void sx127x_modify_cr(uint8_t cr);
uint8_t sx127x_read_sf(void);
void sx127x_modify_sf(uint8_t sf);

uint8_t check_bw(uint8_t bw);
uint8_t check_cr(uint8_t cr);
uint8_t check_sf(uint8_t sf);

uint16_t get_spd_parameter(void);
void start_cad(void);

void convert_sbw_to_ascii(uint8_t sbw, uint8_t* buffer, uint8_t* len);
uint8_t convert_ascii_to_sbw(uint8_t* bw_str);
void convert_scr_to_ascii(uint8_t scr, uint8_t* buffer, uint8_t* len);
uint8_t convert_ascii_to_scr(uint8_t* cr_str);
void convert_ssf_to_ascii(uint8_t ssf, uint8_t* buffer, uint8_t* len);
uint8_t convert_ascii_to_ssf(uint8_t* ssf_str);

#endif
