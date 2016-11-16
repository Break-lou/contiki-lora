#include "battery.h"
#include "internal_adc.h"
#include "internal_adc_option.h"

//uint32_t vbat_measure;
uint8_t battery_value;


internal_adc_param battery_param;

void battery_init(void)
{
	battery_param.internal_adc_vref = internal_adc_vref_via_internal_ldo;//internal_adc_vref_via_vbat;	
	battery_param.internal_adc_input_source = internal_adc_vbat;//internal_adc_digital_ldo_output;
	battery_param.internal_adc_conversion_gain = internal_adc_conversion_gain_half;//internal_adc_conversion_gain_one;
	battery_param.internal_adc_conversion_resolution = internal_adc_resolution_12_bit;
	battery_param.internal_adc_conversion_num = internal_adc_conversion_16;	
}

uint8_t battery_calc_value(uint32_t adc_data)
{
	if(adc_data == 0)
	{
////		while(1);
	}
	battery_value = adc_data>>5;
//	battery_value = 260216/adc_data;		//259137
//	battery_value = adc_data*3/100;
	return battery_value;
}

uint8_t battery_sample_data(void)
{	
	internal_initial_conversion(&battery_param);
	return battery_calc_value(battery_param.adc_data);
}


void saradc_init(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG0_ADC0CEN_ENABLED_U32);

	SI32_SARADC_A_select_start_of_conversion_source(SI32_SARADC_0, 0);            // 
	SI32_SARADC_A_select_timeslot0_channel(SI32_SARADC_0, 31);                    // vbat
	SI32_SARADC_A_select_timeslot1_channel(SI32_SARADC_0, 31);                    // close time slot 1
	SI32_SARADC_A_select_timeslot2_channel(SI32_SARADC_0, 31);                    // close time slot 2
	SI32_SARADC_A_select_timeslot3_channel(SI32_SARADC_0, 31);                    // close time slot 3
	SI32_SARADC_A_select_timeslot4_channel(SI32_SARADC_0, 31);                    // close time slot 4
	SI32_SARADC_A_select_timeslot5_channel(SI32_SARADC_0, 31);                    // close time slot 5
	SI32_SARADC_A_select_timeslot6_channel(SI32_SARADC_0, 31);                    // close time slot 6
	SI32_SARADC_A_select_timeslot7_channel(SI32_SARADC_0, 31);                    // close time slot 7
	SI32_SARADC_A_select_output_packing_mode_lower_halfword_only(SI32_SARADC_0);
	SI32_SARADC_A_select_burst_mode_clock_apb_clock(SI32_SARADC_0);
	SI32_SARADC_A_select_sar_clock_divider(SI32_SARADC_0, 3);

	// 	SI32_SARADC_A_select_vref_external(SI32_SARADC_0);

//	SI32_VREF_B_enable_temperature_sensor(SI32_VREF_0);                           // enable temperature senser
//	SI32_SARADC_A_select_vref_ldo_output(SI32_SARADC_0);                          // select internal ldo output as adc Vref
	SI32_SARADC_A_select_vref_vdd(SI32_SARADC_0);
//	SI32_SARADC_A_select_vref_internal(SI32_SARADC_0);
	SI32_SARADC_A_enter_12bit_mode(SI32_SARADC_0, 0);                             // Characteristic 0 12bit mode
//	SI32_SARADC_A_enter_12bit_mode(SI32_SARADC_0, 1);                             // Characteristic 1 12bit mode
	SI32_SARADC_A_select_autoscan_mode_once(SI32_SARADC_0);
	SI32_SARADC_A_select_channel_characteristic0_gain_one(SI32_SARADC_0);
//	SI32_SARADC_A_select_channel_characteristic0_gain_half(SI32_SARADC_0);        // Characteristic 0 gain half
	SI32_SARADC_A_select_timeslot_channel_character_group(SI32_SARADC_0, 0, 0);   // time slot 0 select Characteristic 0
	SI32_SARADC_A_enable_burst_mode(SI32_SARADC_0);
	SI32_SARADC_A_enable_module(SI32_SARADC_0);
}


