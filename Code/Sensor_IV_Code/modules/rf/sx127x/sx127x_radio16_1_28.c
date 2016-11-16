#include "sx127x_radio.h"
#include "board_cfg.h"
#include <stdio.h>
#include "sensor_parameter.h"

tRadioDriver RadioDriver;


//初始化
int lora_init(void)
{
	tSX127xError error = sx127x_init(Init_LoRa_8K, MAX17dbm);
	if(error != NORMAL)
    {
        // lora初始化异常
		#if DEBUG_PRINT
			printf("lora initialize fail \n");
		#endif
		return error; 
    }
    else
    {
        // lora初始化成功
		#if DEBUG_PRINT
			printf("lora initialize success \n");
		#endif
		return NORMAL;
    }
}	
//复位
void lora_reset(void)
{
	sx127x_reset();
}
//开始接收
void lora_start_rx()
{
	sx127x_rx_mode(100);
}
//读取接收缓存
void lora_get_rx_packet(uint8_t* buffer, uint8_t* size)
{
	sx127x_rx_vari_packet(buffer, size);
}
//发送数据包
void lora_set_tx_packet(uint8_t* buffer, uint8_t size)
{
//	start_cad();
	uint32_t cpu_sr = cpu_sr;
	ENTER_CRITICAL_REGION();
	node_running_flags.has_received_ack = false;
	sx127x_send_packet(buffer, size);
	
	LEAVE_CRITICAL_REGION();
}
//睡眠模式
void lora_set_sleep_mode()
{
	sx127x_sleep_mode();
	RFSW_EN_OFF;
}
//获取RSSI
int8_t lora_get_rssi()
{
	uint8_t pktrssi = sx127x_get_rssi();
	int8_t ret = -164 + (pktrssi*16/15);
	return ret;
}

void lora_start_cad()
{
	start_cad();
}

//射频初始化
void radio_driver_init( void )
{
	RadioDriver.Init = lora_init;
	RadioDriver.Reset = lora_reset;
	RadioDriver.StartRx = lora_start_rx;
	RadioDriver.GetRxPacket = lora_get_rx_packet;
	RadioDriver.SetTxPacket = lora_set_tx_packet;
	RadioDriver.Sleep = lora_set_sleep_mode;
	RadioDriver.GetRssi = lora_get_rssi;
	RadioDriver.StartCAD = lora_start_cad;
	
	RadioDriver.Init();         //射频初始化
	modify_spd_parameter();		//检测SPD参数是否要修改
}









