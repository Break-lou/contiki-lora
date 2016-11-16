#include "dio_handler.h"
#include "sx127x_hal.h"
#include "spi_config.h"
#include "board_cfg.h"
#include <si32_device.h>
#include "sys_event.h"
#include "contiki.h"
#include "sensor_payload.h"
#include "sx127x_radio.h"
#include "led_process.h"
//#include "power_manager_process.h"
#include "sensor_parameter.h"
#include "debug_util.h"
#include "rtc_config.h"
#include <stdio.h>
#include "delay.h"
void DIO0_handler(void)
{
	uint8_t irqflag;
    uint8_t time = 10;
    uint8_t temp;
	
	//唤醒前恢复SPI状态
	spi1_init_from_wakeup();
	
    //读取射频中断寄存器
    SX1276_Read( REG_LR_IRQFLAGS, &temp );
    //记录中断位
    irqflag = temp;
    //清空中断标志
    do
    {
        SX1276_Write(REG_LR_IRQFLAGS,temp);    
        SX1276_Read( REG_LR_IRQFLAGS, &temp );
    }while(((temp&RFLR_IRQFLAGS_RXDONE) ==  RFLR_IRQFLAGS_RXDONE)&time--);
    //处理相应中断
    if(irqflag & RFLR_IRQFLAGS_TXDONE)
    {	//发送完成处理
			RadioDriver.StartRx();//初始接收
			LED_GREEN_OFF;
    }

    if(irqflag & RFLR_IRQFLAGS_RXDONE)
    {
        //接收中断处理
			receive_payload();
			node_running_flags.received_rtc_time = get_rtc_time();
    }
    if(irqflag & RFLR_IRQFLAGS_CADDONE)
    {
        //CADDONE中断
		printf("CAD DONE HAPPENED \n");
    }
}







