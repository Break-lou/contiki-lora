#include "power_manager.h"
#include <si32_device.h>
#include "ext_flash_mcu.h"
#include "port_config.h"
#include "wdtimer_config.h"
#include "spi_config.h"
#include "ext_flash_include.h"
#include "sensor_parameter.h"
#include "system_process_include.h"
#include "etimer.h"
#include "sx127x_radio.h"
#include "rtc_config.h"
#include <stdio.h>
#include <SI32_SARADC_A_Type.h>
bool check_etimer(void);

LOW_POWER_FLAGS_t low_power_t;

void init_low_power_parameter(void)
{
/*	DIS_OPERATE_RF;
	DIS_OPERATE_EXT_FLASH;
	DIS_OPERATE_CO2;
	DIS_OPERATE_SHT25;
	DISABLE_LOW_POWER;
*/
	DIS_OPERATE_UART_OR_USART;
	DIS_OPERATE_485;
	DIS_OPERATE_SENSOR_POWER;
	DIS_OPERATE_ADC;
	DIS_OPERATE_LORA;
	DIS_OPERATE_EXT_FLASH;
	DIS_OPERATE_DCDC0;
	DISABLE_LOW_POWER;
}
void slep_low_power_parameter(void)
{
	DIS_OPERATE_UART_OR_USART;
	DIS_OPERATE_485;
	DIS_OPERATE_SENSOR_POWER;
	DIS_OPERATE_ADC;
	DIS_OPERATE_LORA;
	DIS_OPERATE_EXT_FLASH;
	DIS_OPERATE_DCDC0;
	ENABLE_LOW_POWER;
}
void rf_enter_sleep(void)
{
	#if DEBUG_PRINT
		printf("rf enter sleep\n");
	#endif
	RadioDriver.Sleep();
	pb_setting_before_sleep_end_rf_operation();
}

void ext_flash_enter_sleep(void)
{
	#if DEBUG_PRINT
		printf("ext flash enter sleep\n");
	#endif

	flash_tat_into_sleep();
  pb_setting_before_sleep_end_ext_flash_operation();
}
//进入休眠，共同的地方
void mcu_enter_sleep_common(void)
{
	//端口设置
	#if DEBUG_PRINT
		printf("mcu enter sleep... \n");
	#endif
	pb_setting_before_sleep_common();
	//DCDC设置
	//dcdc0_off();
	//看门狗设置
	wdtimer_reset();
	wdtimer_stop();
	//PM8设置
	SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);
	
	SysTick->CTRL = 0;
	SI32_CLKCTRL_A_enable_power_mode_8(SI32_CLKCTRL_0);
	SCB->SCR = SCB_SCR_SLEEPDEEP_Msk; 
	if(process_nevents())
	{
		#if DEBUG_PRINT
			printf("process nevents \n");
		#endif
		goto wakeup;
	}
	__DSB();
	__ISB();
	__WFI();
	//唤醒设置
	wakeup:
	PB0_0_OUT_HIGH;
	#if DEBUG_PRINT
		printf("wakeup from pm8 \n");
	#endif
	wdtimer_start();
	//pmu_set();
	spi1_init_from_wakeup();//开启SPI LOAR
	ext_flash_spi_init_from_wakeup();//flash
	pb_setting_from_wakeup();//按键,LORA,LED,FLASH_RST
	if((node_parameter.SETP!=S_5TM_TYPE) && (node_parameter.SETP!=MLX90614))
	{
			pb_setting_none_sleep_end_uart_or_usart();	
	}
	enable_pullup_from_wakeup();
	//P3：0,1,2,3,4未唤醒
}
void sensor_iv_low_power_manager(void)
{
	if(check_etimer())
	{
		return;
	}
	if(node_running_flags.sensor_system_state == SYSTEM_STATE_CONFIG || 
	   node_running_flags.sensor_system_state == SYSTEM_STATE_QUCK_WORK)
	{
		//在配置模式和快速工作模式下，不休眠
		return;
	}
	if(process_nevents())
	{
		#if DEBUG_PRINT
			printf("process nevents \n");
		#endif
		return;
	}
	if(low_power_t.enable_low_power)
	{		
		if(!low_power_t.is_operate_uart_or_usart)
		{
			pb_setting_before_sleep_end_uart_or_usart();//p0:7,8
			if((node_parameter.SETP==ILLUMI_TYPE)||(node_parameter.SETP==S_5TM_TYPE)||(node_parameter.SETP==MLX90614))
			{
					SI32_PBSTD_A_write_pins_low(SI32_PBSTD_0, PBX_7 | PBX_8);	
			}
		}
		else
		{
			if((node_parameter.SETP!=S_5TM_TYPE) && (node_parameter.SETP!=MLX90614))
			{
					pb_setting_none_sleep_end_uart_or_usart();	
			}
		}
		if(!low_power_t.is_operate_485)
		{
			pb_setting_before_sleep_end_485();//p3:0,1
		}
		if(!low_power_t.is_operate_sensor_power)
		{
			pb_setting_before_sleep_end_sensor_power();//p3:3	
		}
		if(!low_power_t.is_sample_adc)
		{
			pb_setting_before_sleep_end_adc_power();//P2:1,2;P3:2
		}
		if(!low_power_t.is_operate_lora)
		{
			rf_enter_sleep();//p2:0,3,4,5,6,7;p3:4,5
//			request_join_array.num=0;
//			router_array.router_num=0;
		}
		if(!low_power_t.is_operate_ext_flash)
		{
			ext_flash_enter_sleep();//p0:3,4,5,9;p3:6
		//	low_power_t.is_operate_ext_flash=true;
		}
		if(!low_power_t.is_operate_dcdc0)
		{
			pmu_close();
		}

		mcu_enter_sleep_common();
	}
	
}

bool check_etimer(void)
{
	bool ret = false;
	uint32_t current_rtc_counter = get_rtc_counter_value();
	if(etimer_pending() && ((etimer_next_expiration_time()-current_rtc_counter)<320))
	{
		ret = true;
	}else{
		ret = false;
	}
	return ret;
}
