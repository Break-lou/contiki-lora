#ifndef SYSTEM_INIT_H

#include <stdint.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <Si32_device.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_WDTIMER_A_Type.h>
#include <SI32_PBCFG_A_Type.h>
#include <SI32_RSTSRC_A_Type.h>
#include <SI32_PBGP_A_Type.h>

void delay_us(uint32_t cnt);

void system_clock_init(void);

void wdtimer_stop(void);

void pb_init(void);

void system_init(void);

void soft_reset(void);

void led_off(void);

void led_on(void);

void led_green_on(void);

void led_green_off(void);

void led_green_toggle(void);

void led_blink(void);

#endif

