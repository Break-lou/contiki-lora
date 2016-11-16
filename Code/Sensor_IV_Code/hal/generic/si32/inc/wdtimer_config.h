#ifndef __WDTIMER_CONFIG_H__
#define __WDTIMER_CONFIG_H__


#include <si32_device.h>
#include "SI32_WDTIMER_A_Type.h"

void wdtimer_init(void);

void wdtimer_stop(void);

void wdtimer_reset(void);

void wdtimer_start(void);


#endif
