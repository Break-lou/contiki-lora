#ifndef INTERNAL_ADC_H
#define INTERNAL_ADC_H

#include <stdint.h>
#include <si32_device.h>
#include <SI32_CLKCTRL_A_Type.h>
#include <SI32_SARADC_A_Type.h>
#include <SI32_VREF_B_Type.h>
#include <SI32_PBGP_A_Type.h>

#define ADC_PORT_GROUP	SI32_PBSTD_3
#define ADC_SIG1_PORT	0X0100
#define ADC_SIG2_PORT	0X0200

#define ADC_PORT_IN()	SI32_PBSTD_A_set_pins_digital_input(ADC_PORT_GROUP, ADC_SIG1_PORT|ADC_SIG2_PORT)
#define ADC_PORT_LOW()		\
	SI32_PBSTD_A_set_pins_push_pull_output(ADC_PORT_GROUP, ADC_SIG1_PORT|ADC_SIG2_PORT);\
	SI32_PBSTD_A_write_pins_low(ADC_PORT_GROUP, ADC_SIG1_PORT|ADC_SIG2_PORT)
	
#define ADC_PORT_POWER_OFF()	\
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, 0X0300);\
	SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3, 0X0300)

void internal_adc_init(void);


#endif
