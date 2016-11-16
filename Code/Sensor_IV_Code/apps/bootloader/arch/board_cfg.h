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



#define SENSOR_IV	1
#define BQ			0
#define TOUCHUANG 	0





//Button--PB0.2
#define BUTTON_PORT			SI32_PBSTD_0
#define BUTTON_PIN			0x0004
#define BUTTON_PIN_NUM		2
#define BUTTON_WAKE_SOURCE	0x0008			//WAKE.3--PB0.2
#define BUTTON_INIT_POL		0xfff7			//高电平触发

//UART0_TX--PB0.7	输出
#define UART0_TX_PORT	SI32_PBSTD_0
#define UART0_TX_PIN	0x0080
//UART0_RX--PB0.8	输入
#define UART0_RX_PORT	SI32_PBSTD_0
#define UART0_RX_PIN	0x0100

//DIO0--PB2.0	输入
#define DIO0_PORT			SI32_PBSTD_2
#define DIO0_PIN			0x0001
#define DIO0_PIN_NUM		0
#define DIO0_WAKE_SOURCE	0x1000			//WAKE.12--PB2.0
#define DIO0_INIT_POL		0xefff			//对应位置为0则为高电平触发，1为低电平触发
//DIO1--PB2.1	输入
#define DIO1_PORT	SI32_PBSTD_2
#define DIO1_PIN	0x0002
//DIO2--PB2.2	输入
#define DIO2_PORT	SI32_PBSTD_2
#define DIO2_PIN	0x0004
//DIO4--PB2.3	输入
#define DIO4_PORT	SI32_PBSTD_2
#define DIO4_PIN	0x0008

//SPI1_SCK--PB2.4	
#define SPI1_SCK_PORT	SI32_PBSTD_2
#define SPI1_SCK_PIN	0x0010
//SPI1_MISO--PB2.5
#define SPI1_MISO_PORT	SI32_PBSTD_2
#define SPI1_MISO_PIN	0x0020
//SPI1_MOSI--PB2.6
#define SPI1_MOSI_PORT	SI32_PBSTD_2
#define SPI1_MOSI_PIN	0x0040
//SPI1_NSS--PB2.7
#define SPI1_NSS_PORT	SI32_PBSTD_2
#define SPI1_NSS_PIN	0x0080

//RFSW_EN--PB3.4
#define RFSW_EN_PORT	SI32_PBSTD_3
#define RFSW_EN_PIN		0x0010

//LORA_RST--PB3.5
#define LORA_RST_PORT	SI32_PBSTD_3
#define LORA_RST_PIN		0x0020

//LED_BLUE--PB3.7
#define LED_BLUE_PORT	SI32_PBSTD_3
#define LED_BLUE_PIN	0x0080
//LED_RED--PB3.8
#define LED_RED_PORT	SI32_PBSTD_3
#define LED_RED_PIN		0x0100
//LED_GREEN--PB3.9
#define LED_GREEN_PORT	SI32_PBSTD_3
#define LED_GREEN_PIN	0x0200	

//FLASH_CS
#define FLASH_CS_PORT	SI32_PBSTD_3
#define FLASH_CS_PIN	PBX_6
//FLASH_RESET
#define FLASH_RESET_PORT	SI32_PBSTD_0
#define FLASH_RESET_PIN		PBX_9

#if  SENSOR_IV

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

#elif BQ

	#define LED_BLUE_OFF		SI32_PBSTD_A_set_pins_push_pull_output(LED_BLUE_PORT, LED_BLUE_PIN); \
								SI32_PBSTD_A_write_pins_low(LED_BLUE_PORT,LED_BLUE_PIN)
	#define LED_BLUE_ON			SI32_PBSTD_A_set_pins_push_pull_output(LED_BLUE_PORT, LED_BLUE_PIN); \
								SI32_PBSTD_A_write_pins_high(LED_BLUE_PORT,LED_BLUE_PIN)
	#define LED_BLUE_TOGGLE		SI32_PBSTD_A_set_pins_push_pull_output(LED_BLUE_PORT, LED_BLUE_PIN); \
								SI32_PBSTD_A_toggle_pins(LED_BLUE_PORT,LED_BLUE_PIN)

	#define LED_RED_OFF			SI32_PBSTD_A_set_pins_push_pull_output(LED_RED_PORT, LED_RED_PIN); \
								SI32_PBSTD_A_write_pins_low(LED_RED_PORT,LED_RED_PIN)
	#define LED_RED_ON			SI32_PBSTD_A_set_pins_push_pull_output(LED_RED_PORT, LED_RED_PIN); \
								SI32_PBSTD_A_write_pins_high(LED_RED_PORT,LED_RED_PIN)
	#define LED_RED_TOGGLE		SI32_PBSTD_A_set_pins_push_pull_output(LED_RED_PORT, LED_RED_PIN); \
								SI32_PBSTD_A_toggle_pins(LED_RED_PORT,LED_RED_PIN)

	#define LED_GREEN_OFF		SI32_PBSTD_A_set_pins_push_pull_output(LED_GREEN_PORT, LED_GREEN_PIN); \
								SI32_PBSTD_A_write_pins_low(LED_GREEN_PORT,LED_GREEN_PIN)
	#define LED_GREEN_ON		SI32_PBSTD_A_set_pins_push_pull_output(LED_GREEN_PORT, LED_GREEN_PIN); \
								SI32_PBSTD_A_write_pins_high(LED_GREEN_PORT,LED_GREEN_PIN)
	#define LED_GREEN_TOGGLE	SI32_PBSTD_A_set_pins_push_pull_output(LED_GREEN_PORT, LED_GREEN_PIN); \
								SI32_PBSTD_A_toggle_pins(LED_GREEN_PORT,LED_GREEN_PIN)


#endif



#define RFSW_EN_ON			SI32_PBSTD_A_set_pins_push_pull_output(RFSW_EN_PORT, RFSW_EN_PIN); \
							SI32_PBSTD_A_write_pins_high(RFSW_EN_PORT,RFSW_EN_PIN)
#define RFSW_EN_OFF			SI32_PBSTD_A_set_pins_push_pull_output(RFSW_EN_PORT, RFSW_EN_PIN); \
							SI32_PBSTD_A_write_pins_low(RFSW_EN_PORT,RFSW_EN_PIN)


#define MAX_RX_BUFFER 128
#define MAX_TX_BUFFER 96

#define ms           *32768/1000
#define s            *32768






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




#endif
