#include "timers.h"
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <SI32_PMU_A_Type.h>
#include <SI32_TIMER_A_Type.h>
#include <sim3l1xx.h>
extern uint32_t SystemCoreClock;
void timers_init(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG0_TIMER0);//¿ªÆôÊ±ÖÓ
	SI32_TIMER_A_set_clock_divider_reload(SI32_TIMER_0,56);
	//SI32_TIMER_A_set_clock_divider_counter(SI32_TIMER_0,56);
	SI32_TIMER_A_select_high_clock_source_timer_clock_divider(SI32_TIMER_0);
	SI32_TIMER_A_select_single_timer_mode(SI32_TIMER_0);
	SI32_TIMER_A_is_high_overflow_interrupt_pending(SI32_TIMER_0);
	SI32_TIMER_A_select_split_timer_mode(SI32_TIMER_0);
	SI32_TIMER_A_select_high_auto_reload_mode(SI32_TIMER_0);
	SI32_TIMER_A_enable_stall_in_debug_mode(SI32_TIMER_0);
}
void timers_set_delay_ms(uint16_t data)
{
	uint16_t num;
	num=65536-(25*data);
	SI32_TIMER_A_set_high_count(SI32_TIMER_0,num+1);
	SI32_TIMER_A_set_high_reload(SI32_TIMER_0,num-1);
}
void timers_enable(void)
{
	NVIC_ClearPendingIRQ(TIMER0H_IRQn);
	NVIC_EnableIRQ(TIMER0H_IRQn);	
	SI32_TIMER_A_enable_high_overflow_interrupt(SI32_TIMER_0);
	SI32_TIMER_A_start_high_timer(SI32_TIMER_0);
}
void timers_disable(void)
{
	NVIC_ClearPendingIRQ(TIMER0H_IRQn);
	NVIC_DisableIRQ(TIMER0H_IRQn);	
	SI32_TIMER_A_disable_high_overflow_interrupt(SI32_TIMER_0);
	SI32_TIMER_A_stop_high_timer(SI32_TIMER_0);
}
void timers_reset(uint16_t data)
{
	timers_disable();
	timers_set_delay_ms(data);
	timers_enable();
}

