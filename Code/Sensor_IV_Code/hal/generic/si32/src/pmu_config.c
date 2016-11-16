#include "pmu_config.h"
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_PBGP_A_Type.h>
#include <si32_device.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <SI32_LCD_A_Type.h>
#include <SI32_DCDC_A_Type.h>
#include <SI32_PMU_A_Type.h>
#include <SI32_SCONFIG_A_Type.h>
#include <SI32_LDO_A_Type.h>
#include <SI32_VMON_B_Type.h>
#include <SI32_SARADC_A_Type.h>
#include "port_config.h"
#include "wdtimer_config.h"
#include "spi_config.h"
#include <stdio.h>

void DCDC0_clk_enable(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG0_DCDC0CEN_ENABLED_U32
									  |SI32_CLKCTRL_A_APBCLKG0_LCD0CEN_ENABLED_U32);
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);
}

void DCDC0_off(void)
{
	DCDC0_clk_enable();
	SI32_LCD_A_disable_dcdc_bias (SI32_LCD_0);
	SI32_DCDC_A_disable_module(SI32_DCDC_0);
}
//=================================================
void vdrv_select_vbat(void)
{
	SI32_PMU_A_select_vdrv_connected_to_vbat(SI32_PMU_0);
}

void vdrv_select_dcdc(void)
{
	SI32_PMU_A_select_vdrv_connected_to_vdc(SI32_PMU_0);
}

void vdrv_off(void)
{
	SI32_PMU_A_select_vdrv_high_impedence(SI32_PMU_0);	

}
//=======================================================
void DCDC0_init(uint8_t DCDC_V)
{
	DCDC0_clk_enable();
	SI32_LCD_A_enable_dcdc_bias (SI32_LCD_0);
	SI32_DCDC_A_enable_dcdc_oscillator(SI32_DCDC_0);   
	SI32_DCDC_A_select_clock_source_local (SI32_DCDC_0);
	SI32_DCDC_A_select_current_limit(SI32_DCDC_0, 6);
	SI32_DCDC_A_select_converter_ready_low_threshold(SI32_DCDC_0, 1);   
	SI32_DCDC_A_select_power_switch_size (SI32_DCDC_0, 0);
	SI32_DCDC_A_select_output_voltage (SI32_DCDC_0, DCDC_V);
	SI32_DCDC_A_select_minimum_pulse_width (SI32_DCDC_0, 3);			//modify by yozen 原来是0，改为3后电压波形较稳定
	
	SI32_DCDC_A_enable_async_mode(SI32_DCDC_0);		//add by yozen，增加后电压波形较稳定

	SI32_DCDC_A_enable_module (SI32_DCDC_0);
}

void DCDC_SET(uint8_t dcdc_voltage)
{
   SI32_DCDC_A_exit_bypass_mode(SI32_DCDC_0);	
	DCDC0_init(dcdc_voltage);						//cycle duty or config mode will use as this
	SI32_DCDC_A_exit_bypass_mode(SI32_DCDC_0);

}

//=================================================
void pmu_set()
{
	dcdc0_off();
	vdrv_select_vbat();
}
void pmu_close()
{
	dcdc0_off();

}

void dcdc0_off(void)
{
	DCDC0_off();
//	SI32_DCDC_A_enter_bypass_mode(SI32_DCDC_0);	
	SI32_DCDC_A_exit_bypass_mode(SI32_DCDC_0);
}

void open_debug(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);	
	SI32_SCONFIG_A_enable_power_mode_8_debugging(SI32_SCONFIG_0);
}

void pinwake_enable(void)
{
	SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);

	SI32_PMU_A_enable_pin_wake(SI32_PMU_0);
	SI32_PMU_A_enable_pin_wake_event(SI32_PMU_0);

	SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);

	NVIC_ClearPendingIRQ(PMATCH_IRQn);
	NVIC_EnableIRQ(PMATCH_IRQn);
//	SI32_PMU_0->PWEN.PW2EN=1;
}

void pinwake_disable(void)
{
	NVIC_DisableIRQ(PMATCH_IRQn);
	SI32_PMU_A_disable_pin_wake(SI32_PMU_0);
  	SI32_PMU_A_disable_pin_wake_event(SI32_PMU_0);
//	SI32_PMU_0->PWEN.PW2EN=0;	
}


void debug_output_enable(void)
{
	SI32_PBCFG_A_enable_swv(SI32_PBCFG_0);
}


//=================================================

void disable_pullup_before_sleep(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_1);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_3);
}

void enable_pullup_from_wakeup(void)
{
	SI32_PBSTD_A_enable_pullup_resistors(SI32_PBSTD_3);
}






