#include <system_init.h>
#include <SI32_DCDC_A_Type.h>
#include <SI32_PMU_A_Type.h>
#include <SI32_LCD_A_Type.h>
#include "board_cfg.h"

__asm void delay_us(uint32_t cnt)
{
	ALIGN
	PUSH {r1}
	MOV r1,#5		
	MUL r0,r1		
	SUB r0,#4				
loop
	SUBS r0,#1	
	CMP r0,#0
	BNE loop
	POP {r1}
	BX lr	
	
}

void system_clock_init(void)
{
	SI32_CLKCTRL_A_select_ahb_source_low_power_oscillator(SI32_CLKCTRL_0);
	SI32_CLKCTRL_A_select_ahb_divider(SI32_CLKCTRL_0, 0);
	SI32_CLKCTRL_A_select_apb_divider_1(SI32_CLKCTRL_0);
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG0_FLCTRLCEN_ENABLED_U32
												|SI32_CLKCTRL_A_APBCLKG0_PB0);
}

void wdtimer_stop(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG1_MISC1);	
	SI32_WDTIMER_A_stop_counter(SI32_WDTIMER_0);
}

void pb_init(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_PB0);
	
	//pullup disable
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_1);
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	//PB0 Setup: 输入——BUTTON,USART0_RX		输出——USART0_TX
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, BUTTON_PIN|UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, UART0_TX_PIN);
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_0, PBX_0 | PBX_1 | PBX_2 | PBX_6 | PBX_7 | PBX_8 | PBX_9);	
	
	//PB1 Setup
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_1, 0x00FF);
	
	//PB2 Setup: 输入——DIO0,DIO1,DIO2,DIO4,SPI1_MISO		输出——SPI1_SCK,SPI1_MOSI,SPI1_NSS
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_2, DIO0_PIN|DIO1_PIN|DIO2_PIN|DIO4_PIN|SPI1_MISO_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_2, SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_2, 0xFFFF);
	
	//PB3 Setup: 输出——
	SI32_PBSTD_A_set_pins_push_pull_output(	SI32_PBSTD_3, RFSW_EN_PIN|LORA_RST_PIN|
											LED_BLUE_PIN|LED_RED_PIN|LED_GREEN_PIN );
	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_3, 0xFFFF);

	led_off();
}

void vdrv_select_vbat(void)
{
	SI32_PMU_A_select_vdrv_connected_to_vbat(SI32_PMU_0);
}


void DCDC0_clk_enable(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG0_DCDC0CEN_ENABLED_U32
									  |SI32_CLKCTRL_A_APBCLKG0_LCD0CEN_ENABLED_U32);
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);
}

void pmu_set()
{
	DCDC0_clk_enable();
	SI32_LCD_A_disable_dcdc_bias (SI32_LCD_0);
	SI32_DCDC_A_disable_module(SI32_DCDC_0);
	SI32_DCDC_A_enter_bypass_mode(SI32_DCDC_0);	
	vdrv_select_vbat();
}

void system_init(void)
{
	system_clock_init();
	wdtimer_stop();
	pb_init();
	pmu_set();
}

void soft_reset(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,
										   SI32_CLKCTRL_A_APBCLKG1_MISC0);	
	SI32_RSTSRC_A_generate_software_reset(SI32_RSTSRC_0);
}

void led_off(void)
{
	LED_BLUE_OFF;
	LED_RED_OFF;
	LED_GREEN_OFF;
}
void led_on(void)
{
	LED_BLUE_ON;
	LED_RED_ON;
	LED_GREEN_ON;
}


void led_green_on(void)
{
	LED_GREEN_ON;
}

void led_green_off(void)
{
	LED_GREEN_OFF;
}

uint8_t led_green_state = 0;
uint32_t led_blink_key = 0;

void led_green_toggle(void)
{
	led_blink_key++;
	if(!(led_blink_key&0x0f))
	{
		if(led_green_state)
		{
			led_green_state = 0;
			led_green_off();
		}
		else
		{
			led_green_state = 1;
			led_green_on();
		}
	}
}



