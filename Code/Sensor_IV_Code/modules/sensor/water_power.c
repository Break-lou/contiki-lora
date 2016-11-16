#include "water_power.h"
#include "board_cfg.h"
#include "internal_adc_option.h"

#if WATER_OPERATE
internal_adc_param  water_param;



void water_param_init(void)
{
	//???IO???????PB3.3
	SI32_PBSTD_A_set_pins_analog(SI32_PBSTD_2, PBX_2);
	
	water_param.internal_adc_input_source = internal_adc_port_pb2_2;		//?PB2.7?146???,???144?PB3.3
	water_param.internal_adc_vref = internal_adc_vref_via_internal_ldo;
	water_param.internal_adc_conversion_gain = internal_adc_conversion_gain_half;
	water_param.internal_adc_conversion_resolution = internal_adc_resolution_12_bit;
	water_param.internal_adc_conversion_num = internal_adc_conversion_16;
}


uint16_t water_sample_data(void)
{
	uint16_t voc_value;
	internal_initial_conversion(&water_param);
	voc_value = (uint16_t)(water_param.adc_data);
	return voc_value;
}

#endif




