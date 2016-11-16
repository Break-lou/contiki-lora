#ifndef BATTERY_H
#define BATTERY_H

#include "si32_device.h"
#include "SI32_CLKCTRL_A_Type.h"
#include "SI32_SARADC_A_Type.h"
#include "SI32_VREF_B_Type.h"

void saradc_init(void);

void battery_init(void);

uint8_t battery_sample_data(void);

#endif


