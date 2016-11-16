#include <sys/clock.h>
#include <sys/cc.h>
#include <sys/etimer.h>

#include "rtc_config.h"
#include "clock_config.h"

void clock_init(void)
{
	si32_clock_init();
}


clock_time_t clock_time(void)
{
	return get_rtc_counter_value();
}


