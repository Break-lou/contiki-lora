#include <internal_adc.h>

void internal_adc_init(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,SI32_CLKCTRL_A_APBCLKG0_ADC0CEN_ENABLED_U32);

	SI32_SARADC_A_select_start_of_conversion_source(SI32_SARADC_0, 0);            	// 
	SI32_SARADC_A_select_timeslot0_channel(SI32_SARADC_0, 0x1f);                    // time slot 0 temp
	SI32_SARADC_A_select_timeslot1_channel(SI32_SARADC_0, 0x1f);                    // time slot 1 Vbat
	SI32_SARADC_A_select_timeslot2_channel(SI32_SARADC_0, 0x1f);                    // close time slot 2
	SI32_SARADC_A_select_timeslot3_channel(SI32_SARADC_0, 0x1f);                    // close time slot 3
	SI32_SARADC_A_select_timeslot4_channel(SI32_SARADC_0, 0x1f);                    // close time slot 4
	SI32_SARADC_A_select_timeslot5_channel(SI32_SARADC_0, 0x1f);                    // close time slot 5
	SI32_SARADC_A_select_timeslot6_channel(SI32_SARADC_0, 0x1f);                    // close time slot 6
	SI32_SARADC_A_select_timeslot7_channel(SI32_SARADC_0, 0x1f);                    // close time slot 7
	SI32_SARADC_A_select_output_packing_mode_lower_halfword_only(SI32_SARADC_0);
	SI32_SARADC_A_select_burst_mode_clock_apb_clock(SI32_SARADC_0);
	SI32_SARADC_A_select_sar_clock_divider(SI32_SARADC_0, 3);

	// 	SI32_SARADC_A_select_vref_external(SI32_SARADC_0);

//	SI32_VREF_B_enable_temperature_sensor(SI32_VREF_0);                           // enable temperature senser
//	SI32_SARADC_A_select_vref_ldo_output(SI32_SARADC_0);                          // select internal ldo output as adc Vref
//	SI32_SARADC_A_enter_12bit_mode(SI32_SARADC_0, 0);                             // Characteristic 0 12bit mode
//	SI32_SARADC_A_enter_12bit_mode(SI32_SARADC_0, 1);                             // Characteristic 1 12bit mode
	SI32_SARADC_A_select_autoscan_mode_once(SI32_SARADC_0);
//	SI32_SARADC_A_select_channel_characteristic0_gain_half(SI32_SARADC_0);        // Characteristic 0 gain half
	SI32_SARADC_A_select_timeslot_channel_character_group(SI32_SARADC_0, 0, 0);   // time slot 0 select Characteristic 0
	SI32_SARADC_A_enable_burst_mode(SI32_SARADC_0);
	SI32_SARADC_A_disable_module(SI32_SARADC_0);
}


