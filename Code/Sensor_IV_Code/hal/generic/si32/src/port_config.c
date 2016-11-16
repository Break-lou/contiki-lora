#include "port_config.h"
#include "uart.h"
void led_all_off(void);

void port_init(void)
{
	//pullup disable
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_1);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	
	#if SENSOR_IV
	
	//PB0 Setup: 输入——BUTTON,USART0_RX		输出——USART0_TX
	SI32_PBSTD_A_set_pins_digital_input(BUTTON_PORT, BUTTON_PIN);
	SI32_PBSTD_A_set_pins_digital_input(UART0_RX_PORT, UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(UART0_TX_PORT, UART0_TX_PIN);
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_0, PBX_0 | PBX_1 | PBX_2 | PBX_6 | PBX_7 | PBX_8 | PBX_9);	
	
	//PB1 Setup
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_1, 0x00FF);
	
	//PB2 Setup: 输入——DIO0,DIO1,DIO2,DIO4,SPI1_MISO		输出——SPI1_SCK,SPI1_MOSI,SPI1_NSS
	SI32_PBSTD_A_set_pins_digital_input(LORA_PORT, LORA_DIO0_PIN|LORA_DIO4_PIN);
	SI32_PBSTD_A_set_pins_analog(AD_PORT, AD0_PIN|AD1_PIN);
	SI32_PBSTD_A_set_pins_digital_input(SPI1_PORT, SPI1_MISO_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SPI1_PORT, SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_2, 0xFFFF);
	
	//PB3 Setup: 输出——
	SI32_PBSTD_A_set_pins_push_pull_output(	RFSW_EN_PORT, RFSW_EN_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(	LORA_RST_PORT, LORA_RST_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(	LED_PORT, LED_BLUE_PIN|LED_RED_PIN|LED_GREEN_PIN );
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_3, 0xFFFF);

	led_all_off();
	
	#elif BQ
	
	//PB0 Setup: 输入——BUTTON,USART0_RX		输出——USART0_TX
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, BUTTON_PIN|UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, UART0_TX_PIN);
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_0, PBX_0 | PBX_1 | PBX_2 | PBX_6 | PBX_7 | PBX_8 | PBX_9);	
	
	//PB1 Setup
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_1, 0x00FF);
	
	//PB2 Setup: 输入——DIO0,DIO1,DIO2,DIO4,SPI1_MISO		输出——SPI1_SCK,SPI1_MOSI,SPI1_NSS
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_2, LORA_DIO0_PIN|LORA_DIO1_PIN|LORA_DIO2_PIN|LORA_DIO4_PIN|SPI1_MISO_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_2, SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_2, 0xFFFF);
	
	//PB3 Setup: 输出——
	SI32_PBSTD_A_set_pins_push_pull_output(	SI32_PBSTD_3, RFSW_EN_PIN|LORA_RST_PIN|
											LED_BLUE_PIN|LED_RED_PIN|LED_GREEN_PIN );
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_3, 0xFFFF);
	
	#endif
}


void led_all_off(void)
{
	LED_BLUE_OFF;
	LED_RED_OFF;
	LED_GREEN_OFF;
}

uint32_t get_button_status(void)
{
	uint32_t button = SI32_PBSTD_A_read_pin(BUTTON_PORT, BUTTON_PIN_NUM);
	return button;
}

//唤醒时IO输入输出设置
void pb_setting_from_wakeup(void)//按键,LORA,LED,FLASH_RST
{
	//PB0
	SI32_PBSTD_A_set_pins_digital_input(BUTTON_PORT, BUTTON_PIN);
	//PB2
	SI32_PBSTD_A_set_pins_digital_input(LORA_PORT, LORA_DIO0_PIN|LORA_DIO4_PIN);
	SI32_PBSTD_A_set_pins_analog(AD_PORT, AD0_PIN|AD1_PIN);
	SI32_PBSTD_A_set_pins_digital_input(SPI1_PORT, SPI1_MISO_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SPI1_PORT, SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);
	//PB3
	SI32_PBSTD_A_set_pins_push_pull_output(	RFSW_EN_PORT, RFSW_EN_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(	LORA_RST_PORT, LORA_RST_PIN);
	//SI32_PBSTD_A_set_pins_push_pull_output(	LED_PORT, LED_BLUE_PIN|LED_RED_PIN|LED_GREEN_PIN );
	SI32_PBSTD_A_set_pins_push_pull_output(	FLASH_CS_PORT, FLASH_CS_PIN );
}

//进入休眠时端口共同的设置
void pb_setting_before_sleep_common(void)
{
	//禁止上拉
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_1);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	//PB0端口
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, PBX_0|PBX_1);
	SI32_PBSTD_A_write_pins_low(SI32_PBSTD_0, PBX_0|PBX_1);		
	#if (DEBUG_PRINT+FLASH_DEBUG_PRINT+JOIN_NET_DEBUG) == 0
		SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, PBX_6);
		SI32_PBSTD_A_write_pins_low(SI32_PBSTD_0, PBX_6);
	#endif
	//PB1端口
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_1, 0xFFFF);
	SI32_PBSTD_A_write_pins_low(SI32_PBSTD_1, 0xFFFF);
	//PB2端口——由RF SLEEP控制
	
	//PB3端口
	SI32_PBSTD_A_set_pins_push_pull_output(LED_PORT, LED_BLUE_PIN|LED_RED_PIN|LED_GREEN_PIN);						
	SI32_PBSTD_A_write_pins_high(LED_PORT, LED_BLUE_PIN|LED_RED_PIN|LED_GREEN_PIN);
}

//spi0休眠设置
void pb_setting_before_sleep_end_spi0(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	
	SI32_PBCFG_A_disable_xbar0_peripherals(SI32_PBCFG_0, SI32_PBCFG_A_XBAR0_SPI0EN);
	
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, PBX_3 |PBX_4 | PBX_5);
	SI32_PBSTD_A_write_pins_low(SI32_PBSTD_0, PBX_3| PBX_4 | PBX_5 );	
}
//spi1休眠设置
void pb_setting_before_sleep_end_spi1(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	SI32_PBCFG_A_disable_spi1_on_crossbar(SI32_PBCFG_0);
	SI32_PBSTD_A_set_pins_push_pull_output(SPI1_PORT, SPI1_MISO_PIN|SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);
	SI32_PBSTD_A_write_pins_low(SPI1_PORT, SPI1_MISO_PIN|SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);
}
//串口休眠设置
void pb_setting_before_sleep_end_uart_or_usart(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	//PB0
	uart_rx_disable();	
  uart_tx_disable();	
	SI32_PBSTD_A_set_pins_push_pull_output(UART0_PORT, UART0_TX_PIN | UART0_RX_PIN);
	#if UART_RES
	SI32_PBSTD_A_write_pins_high(UART0_PORT, UART0_TX_PIN | UART0_RX_PIN);
	#else
	SI32_PBSTD_A_write_pins_low(UART0_PORT, UART0_TX_PIN | UART0_RX_PIN);
	#endif
	
}
void pb_setting_none_sleep_end_uart_or_usart(void)
{
	SI32_PBSTD_A_set_pins_digital_input(UART0_RX_PORT, UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(UART0_TX_PORT, UART0_TX_PIN);
	SI32_PBSTD_A_write_pins_high(UART0_TX_PORT, UART0_TX_PIN);
	//SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_0, PBX_7 | PBX_8 );	
}
//485休眠设置
void pb_setting_before_sleep_end_485(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_3);
	SI32_PBSTD_A_set_pins_push_pull_output(U485_PORT, U485_SHDN_PIN | U485_RXEN_PIN);		
	SI32_PBSTD_A_write_pins_low(U485_SHDN_PORT, U485_SHDN_PIN);
	SI32_PBSTD_A_write_pins_high(U485_RXEN_PORT, U485_RXEN_PIN);
}
//ADC休眠设置
void pb_setting_before_sleep_end_adc_power(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_3);
	SI32_PBSTD_A_set_pins_push_pull_output(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN);		
	SI32_PBSTD_A_write_pins_high(ADC_POWER_EN_PORT, ADC_POWER_EN_PIN);
	
	SI32_PBSTD_A_set_pins_push_pull_output(AD_PORT, AD0_PIN|AD1_PIN);		
	SI32_PBSTD_A_write_pins_low(AD_PORT, AD0_PIN|AD1_PIN);
}
//传感器电源设置
void pb_setting_before_sleep_end_sensor_power(void)
{
	//加入DCDC关闭
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_3);
	SI32_PBSTD_A_set_pins_push_pull_output(WATER_POWER_EN_PORT, WATER_POWER_EN_PIN);		
	SI32_PBSTD_A_write_pins_low(WATER_POWER_EN_PORT, WATER_POWER_EN_PIN);	
}
//不在操作射频时的相应端口休眠设置
void pb_setting_before_sleep_end_rf_operation(void)
{
	pb_setting_before_sleep_end_spi1();
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_3);
	//PB2
	SI32_PBSTD_A_set_pins_push_pull_output(LORA_PORT, LORA_DIO0_PIN|LORA_DIO4_PIN);
	SI32_PBSTD_A_write_pins_low(LORA_PORT, LORA_DIO0_PIN|LORA_DIO4_PIN);
	//PB3
	SI32_PBSTD_A_set_pins_push_pull_output(RFSW_EN_PORT, RFSW_EN_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(LORA_RST_PORT, LORA_RST_PIN);
	SI32_PBSTD_A_write_pins_low(RFSW_EN_PORT, RFSW_EN_PIN);
	SI32_PBSTD_A_write_pins_high(LORA_RST_PORT, LORA_RST_PIN);
}
//不在操作外部FLASH的时候端口设置
void pb_setting_before_sleep_end_ext_flash_operation(void)
{
	pb_setting_before_sleep_end_spi0();
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_3);
	//PB0端口
	SI32_PBSTD_A_set_pins_push_pull_output(FLASH_RESET_PORT, FLASH_RESET_PIN);
	SI32_PBSTD_A_write_pins_high(FLASH_RESET_PORT, FLASH_RESET_PIN);
	//PB3端口
	SI32_PBSTD_A_set_pins_push_pull_output(FLASH_CS_PORT, FLASH_CS_PIN);
	SI32_PBSTD_A_write_pins_high(FLASH_CS_PORT, FLASH_CS_PIN);	
}

