#ifndef __PORT_CONFIG_H__
#define __PORT_CONFIG_H__


#include <SI32_PBSTD_A_Type.h>
#include <SI32_PBCFG_A_Type.h>
#include <SI32_CLKCTRL_A_Type.h>
#include "board_cfg.h"



void port_init(void);
void pb_init_from_reset(void);
uint32_t get_button_status(void);
void pb_setting_from_wakeup(void);

void pb_setting_before_sleep_common(void);
 
void pb_setting_before_sleep_end_spi0(void);
void pb_setting_before_sleep_end_spi1(void);
void pb_setting_before_sleep_end_uart_or_usart(void);
void pb_setting_none_sleep_end_uart_or_usart(void);
void pb_setting_before_sleep_end_485(void);
void pb_setting_before_sleep_end_adc_power(void);
void pb_setting_before_sleep_end_sensor_power(void);
void pb_setting_before_sleep_end_rf_operation(void);
void pb_setting_before_sleep_end_ext_flash_operation(void);

#endif
