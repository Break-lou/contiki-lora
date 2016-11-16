#ifndef __BOARD_CFG_H__
#define __BOARD_CFG_H__


#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>


#define ENTER_CRITICAL_REGION()	\
	cpu_sr = __get_PRIMASK();\
	__set_PRIMASK(1)
#define	LEAVE_CRITICAL_REGION()	\
	__set_PRIMASK(cpu_sr)
#define DISABLE_IRQ() __set_PRIMASK(1)


#define DEBUG_PRINT 0
#define FLASH_DEBUG_PRINT 0
#define relay_only 0
#define JOIN_NET_DEBUG 0 //入网调式

#define SENSOR_IV	1//1
#define HISTORY_NONE    0
#define modbus_mode     0

#define WATER_OPERATE   0
#define NHZF42_OPERATE  0
#define DS18B20_OPERATE 0
#define SOIL_OPERATE    0
#define S_5TM_OPERATE   0
#define NHFS15_OPERATE  0
#define ILLUMI_OPERATE  0
#define ACA826T_OPERATE 0
#define SCA126T_OPERATE 0
#define NHZD10_OPERATE  0
#define NHUV11_OPERATE  0
#define MLX90614_OPERATE 0
#define SKD_100D_OPERATE 0
#define LVDT_OPERATE    0
#define ROTONIC_OPERATE 1

#define PB0_DEFAULT 0x03
#define PB1_DEFAULT 0
#define PB2_DEFAULT 0
#define PB3_DEFAULT 0

//定义每个IO对应的位
//PB组
#define PBX_0	0x0001
#define PBX_1	0x0002
#define PBX_2	0x0004
#define PBX_3	0x0008
#define PBX_4	0x0010
#define PBX_5	0x0020
#define PBX_6	0x0040
#define PBX_7	0x0080
#define PBX_8	0x0100
#define PBX_9	0x0200
//Button--PB0.2

#define BUTTON_PORT			SI32_PBSTD_0
#define BUTTON_PIN			PBX_2						
#define BUTTON_PIN_NUM		2
#define BUTTON_WAKE_SOURCE	0x0008		//WAKE.3--PB0.2
#define BUTTON_INIT_POL		0xfff7			//高电平触发

//UART0_TX--PB0.7	输出
#define UART_RES 1
#define UART0_PORT	SI32_PBSTD_0
#define UART0_TX_PORT	SI32_PBSTD_0
#define UART0_TX_PIN	PBX_7
//UART0_RX--PB0.8	输入
#define UART0_RX_PORT	SI32_PBSTD_0
#define UART0_RX_PIN	PBX_8

//DIO0--PB2.0	输入
#define LORA_PORT			SI32_PBSTD_2
#define LORA_DIO0_PORT			SI32_PBSTD_2
#define LORA_DIO0_PIN			PBX_0
#define LORA_DIO0_PIN_NUM		0
#define LORA_DIO0_WAKE_SOURCE	0x1000			//WAKE.12--PB2.0
#define LORA_DIO0_INIT_POL		0xefff			//对应位置为0则为高电平触发，1为低电平触发
//DIO1--PB2.1	输入
#define LORA_DIO1_PORT	SI32_PBSTD_2
#define LORA_DIO1_PIN	PBX_1
//DIO2--PB2.2	输入
#define LORA_DIO2_PORT	SI32_PBSTD_2
#define LORA_DIO2_PIN	PBX_2
//DIO4--PB2.3	输入
#define LORA_DIO4_PORT	SI32_PBSTD_2
#define LORA_DIO4_PIN	PBX_3
//AD
//AD0 PB2.1
#define AD_PORT	SI32_PBSTD_2
#define AD0_PORT	SI32_PBSTD_2
#define AD0_PIN	PBX_1
//AD1 PB2.2
#define AD1_PORT	SI32_PBSTD_2
#define AD1_PIN	PBX_2
//SPI1_SCK--PB2.4	
#define SPI1_PORT	SI32_PBSTD_2
#define SPI1_SCK_PORT	SI32_PBSTD_2
#define SPI1_SCK_PIN	PBX_4
//SPI1_MISO--PB2.5
#define SPI1_MISO_PORT	SI32_PBSTD_2
#define SPI1_MISO_PIN	PBX_5
//SPI1_MOSI--PB2.6
#define SPI1_MOSI_PORT	SI32_PBSTD_2
#define SPI1_MOSI_PIN	PBX_6
//SPI1_NSS--PB2.7
#define SPI1_NSS_PORT	SI32_PBSTD_2
#define SPI1_NSS_PIN	PBX_7
//485SHDN P3.0
#define U485_PORT	SI32_PBSTD_3

#define U485_SHDN_PORT	SI32_PBSTD_3
#define U485_SHDN_PIN		PBX_0
//485RXEN P3.1
#define U485_RXEN_PORT	SI32_PBSTD_3
#define U485_RXEN_PIN		PBX_1
//RFSW_EN--PB3.4
#define RFSW_EN_PORT	SI32_PBSTD_3
#define RFSW_EN_PIN		PBX_4

//LORA_RST--PB3.5
#define LORA_RST_PORT	SI32_PBSTD_3
#define LORA_RST_PIN		PBX_5

//SensorPower EN--PB3.2
#define ADC_POWER_EN_PORT	SI32_PBSTD_3
#define ADC_POWER_EN_PIN		PBX_2
//SensorPower EN--PB3.3
#define WATER_POWER_EN_PORT	SI32_PBSTD_3
#define WATER_POWER_EN_PIN		PBX_3

//LED_BLUE--PB3.7
#define LED_PORT	SI32_PBSTD_3
#define LED_BLUE_PORT	SI32_PBSTD_3
#define LED_BLUE_PIN	PBX_7
//LED_RED--PB3.8
#define LED_RED_PORT	SI32_PBSTD_3
#define LED_RED_PIN		PBX_8
//LED_GREEN--PB3.9
#define LED_GREEN_PORT	SI32_PBSTD_3
#define LED_GREEN_PIN	PBX_9	

//FLASH_CS
#define FLASH_CS_PORT	SI32_PBSTD_3
#define FLASH_CS_PIN	PBX_6
//FLASH_RESET
#define FLASH_RESET_PORT	SI32_PBSTD_0
#define FLASH_RESET_PIN		PBX_9

#define LED_BLUE_OFF		SI32_PBSTD_A_set_pins_push_pull_output(LED_BLUE_PORT, LED_BLUE_PIN); \
							SI32_PBSTD_A_write_pins_high(LED_BLUE_PORT,LED_BLUE_PIN)
#define LED_BLUE_ON			SI32_PBSTD_A_set_pins_push_pull_output(LED_BLUE_PORT, LED_BLUE_PIN); \
							SI32_PBSTD_A_write_pins_low(LED_BLUE_PORT,LED_BLUE_PIN)
#define LED_BLUE_TOGGLE		SI32_PBSTD_A_set_pins_push_pull_output(LED_BLUE_PORT, LED_BLUE_PIN); \
							SI32_PBSTD_A_toggle_pins(LED_BLUE_PORT,LED_BLUE_PIN)

#define LED_RED_OFF			SI32_PBSTD_A_set_pins_push_pull_output(LED_RED_PORT, LED_RED_PIN); \
							SI32_PBSTD_A_write_pins_high(LED_RED_PORT,LED_RED_PIN)
#define LED_RED_ON			SI32_PBSTD_A_set_pins_push_pull_output(LED_RED_PORT, LED_RED_PIN); \
							SI32_PBSTD_A_write_pins_low(LED_RED_PORT,LED_RED_PIN)
#define LED_RED_TOGGLE		SI32_PBSTD_A_set_pins_push_pull_output(LED_RED_PORT, LED_RED_PIN); \
							SI32_PBSTD_A_toggle_pins(LED_RED_PORT,LED_RED_PIN)

#define LED_GREEN_OFF		SI32_PBSTD_A_set_pins_push_pull_output(LED_GREEN_PORT, LED_GREEN_PIN); \
							SI32_PBSTD_A_write_pins_high(LED_GREEN_PORT,LED_GREEN_PIN)
#define LED_GREEN_ON		SI32_PBSTD_A_set_pins_push_pull_output(LED_GREEN_PORT, LED_GREEN_PIN); \
							SI32_PBSTD_A_write_pins_low(LED_GREEN_PORT,LED_GREEN_PIN)
#define LED_GREEN_TOGGLE	SI32_PBSTD_A_set_pins_push_pull_output(LED_GREEN_PORT, LED_GREEN_PIN); \
							SI32_PBSTD_A_toggle_pins(LED_GREEN_PORT,LED_GREEN_PIN)


#define RFSW_EN_ON			SI32_PBSTD_A_set_pins_push_pull_output(RFSW_EN_PORT, RFSW_EN_PIN); \
							SI32_PBSTD_A_write_pins_high(RFSW_EN_PORT,RFSW_EN_PIN)
#define RFSW_EN_OFF			SI32_PBSTD_A_set_pins_push_pull_output(RFSW_EN_PORT, RFSW_EN_PIN); \
							SI32_PBSTD_A_write_pins_low(RFSW_EN_PORT,RFSW_EN_PIN)

#define PB0_0_OUT_HIGH		SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, PBX_0); \
							SI32_PBSTD_A_write_pins_high(SI32_PBSTD_0,PBX_0)


#define MAX_RX_BUFFER 256
#define MAX_TX_BUFFER 256


#define RTC_OSA		 		32768
#define ms           *32.768
#define s            *32768

#define BEGIN_TIME 1420041600//1402934400

#define SLOT_TIME 250		//单位ms



//以下时间参数都需要根据速率调整
#define TIME_SLICE 		48		//入网请求ACK中的时间同步修正
#define TIME_SLICE_2 	42		//数据包ACK中的时间修正
#define CYCLE_START_LISTEN_TIME	35	//加入网络后，每个周期开始时的监听广播最长时间


#endif
