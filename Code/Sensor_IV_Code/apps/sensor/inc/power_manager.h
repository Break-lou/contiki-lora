#ifndef __POWER_MANAGER_H__
#define __POWER_MANAGER_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct LOW_POWER_FLAGS
{
	bool enable_low_power;		//是否允许低功耗总开关
	bool is_operate_spi0;
	bool is_operate_spi1;
	bool is_operate_uart_or_usart;
	bool is_operate_485;
	bool is_operate_sensor_power;
	bool is_sample_adc;

	bool is_operate_lora;
	bool is_operate_ext_flash;
	bool is_operate_dcdc0;
}LOW_POWER_FLAGS_t;

void init_low_power_parameter(void);
void slep_low_power_parameter(void);
void sensor_iv_low_power_manager(void);

extern LOW_POWER_FLAGS_t low_power_t;


#define ENABLE_LOW_POWER low_power_t.enable_low_power = true
#define DISABLE_LOW_POWER low_power_t.enable_low_power = false

#define OPERATE_DCDC0 low_power_t.is_operate_dcdc0 = true
#define DIS_OPERATE_DCDC0 low_power_t.is_operate_dcdc0 = false  

#define OPERATE_SPI0 		low_power_t.is_operate_spi0 = true
#define DIS_OPERATE_SPI0 	low_power_t.is_operate_spi0 = false

#define OPERATE_SPI1 			 low_power_t.is_operate_spi1 = true
#define DIS_OPERATE_SPI1 	 low_power_t.is_operate_spi1 = false

#define OPERATE_UART_OR_USART 		low_power_t.is_operate_uart_or_usart = true
#define DIS_OPERATE_UART_OR_USART low_power_t.is_operate_uart_or_usart = false

#define OPERATE_485			 low_power_t.is_operate_485 = true
#define DIS_OPERATE_485 	low_power_t.is_operate_485 = false

#define OPERATE_SENSOR_POWER 			low_power_t.is_operate_sensor_power = true
#define DIS_OPERATE_SENSOR_POWER 	low_power_t.is_operate_sensor_power = false

#define OPERATE_ADC	 		low_power_t.is_sample_adc= true
#define DIS_OPERATE_ADC low_power_t.is_sample_adc = false

#define OPERATE_LORA 			low_power_t.is_operate_lora = true
#define DIS_OPERATE_LORA 	low_power_t.is_operate_lora = false

#define OPERATE_EXT_FLASH 		low_power_t.is_operate_ext_flash = true
#define DIS_OPERATE_EXT_FLASH low_power_t.is_operate_ext_flash = false


#endif
