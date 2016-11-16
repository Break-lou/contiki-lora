#include "pmatch_config.h"

void pmatch_enable(void);

void pmatch_init(void)
{
	SI32_PMU_A_enable_rtc0_alarm_wake_event(SI32_PMU_0);
	SI32_PMU_A_enable_pin_wake(SI32_PMU_0);
	SI32_PMU_A_enable_pin_wake_event(SI32_PMU_0);
	
	SI32_PMU_A_write_pwpol(SI32_PMU_0, BUTTON_INIT_POL);	    	//
	SI32_PMU_A_write_pwen(SI32_PMU_0, BUTTON_WAKE_SOURCE);	
}


void pmatch_enable(void)
{
	SI32_PMU_A_clear_wakeup_flags(SI32_PMU_0);
	SI32_PBCFG_A_enable_port_match_interrupt(SI32_PBCFG_0);
	NVIC_ClearPendingIRQ(PMATCH_IRQn);
	NVIC_EnableIRQ(PMATCH_IRQn);
}




