#include "wdtimer_config.h"
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_PBGP_A_Type.h>
#include <si32_device.h>
#include <SI32_CLKCTRL_A_Type.h>

#define USE_WDTIMER

void wdtimer_init(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG1_MISC1|SI32_CLKCTRL_A_APBCLKG1_MISC0);		
	SI32_WDTIMER_A_disable_early_warning_interrupt(SI32_WDTIMER_0);
	SI32_WDTIMER_A_stop_counter(SI32_WDTIMER_0);
	SI32_WDTIMER_A_reset_counter(SI32_WDTIMER_0);
	SI32_WDTIMER_A_enable_stall_in_debug_mode(SI32_WDTIMER_0);
	
	while(SI32_WDTIMER_A_is_threshold_update_pending(SI32_WDTIMER_0));
	SI32_WDTIMER_A_set_early_warning_threshold (SI32_WDTIMER_0, 0x6000);    

	while(SI32_WDTIMER_A_is_threshold_update_pending(SI32_WDTIMER_0));
	SI32_WDTIMER_A_set_reset_threshold (SI32_WDTIMER_0, 0XFFFF);

	#ifdef WDTIMER_DEBUG
		NVIC_ClearPendingIRQ(WDTIMER0_IRQn);
		NVIC_EnableIRQ(WDTIMER0_IRQn);
		SI32_WDTIMER_A_enable_early_warning_interrupt(SI32_WDTIMER_0);	
	#else
		NVIC_ClearPendingIRQ(WDTIMER0_IRQn);
		NVIC_DisableIRQ(WDTIMER0_IRQn);
		SI32_WDTIMER_A_disable_early_warning_interrupt(SI32_WDTIMER_0);	
	#endif

	wdtimer_stop();
}



void wdtimer_start(void)
{
#if defined USE_WDTIMER
	SI32_WDTIMER_A_start_counter(SI32_WDTIMER_0);
#else
	SI32_WDTIMER_A_stop_counter(SI32_WDTIMER_0);
#endif
}

void wdtimer_stop(void)
{
	SI32_WDTIMER_A_stop_counter(SI32_WDTIMER_0);
}

void wdtimer_reset(void)
{
	SI32_WDTIMER_A_reset_counter(SI32_WDTIMER_0);
}



