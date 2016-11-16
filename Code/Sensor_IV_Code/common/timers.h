#ifndef __TIMERS_H__
#define __TIMERS_H__
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

void timers_init(void);
void timers_set_delay_ms(uint16_t data);
void timers_enable(void);
void timers_disable(void);
void timers_reset(uint16_t data);
#endif

