#include "internal_adc.h"
#include "internal_adc_option.h"

void delay_Xus(uint32_t us);
#define sample_data_num 34
uint8_t internal_adc_slot_map[INTERNAL_ADC_SLOT_MAP_LEN];

enum_internal_adc_channel internal_adc_channel_table[INTERNAL_ADC_CHANNEL_NUM] = {\
	internal_adc_channel_0,\
	internal_adc_channel_1,\
	internal_adc_channel_2,\
	internal_adc_channel_3,\
	internal_adc_channel_4,\
	internal_adc_channel_5,\
	internal_adc_channel_6,\
	internal_adc_channel_7,\
	internal_adc_channel_8,\
	internal_adc_channel_9,\
	internal_adc_channel_10,\
	internal_adc_channel_11,\
	internal_adc_channel_12,\
	internal_adc_channel_13,\
	internal_adc_channel_14,\
	internal_adc_channel_19,\
	internal_adc_channel_20,\
	internal_adc_channel_22,\
	internal_adc_channel_23,\
	internal_adc_channel_24,\
	internal_adc_channel_25,\
	internal_adc_channel_26,\
	internal_adc_channel_27,\
	internal_adc_channel_28,\
	internal_adc_channel_29,\
	internal_adc_channel_30,\
};



enum_internal_adc_channel internal_adc_get_channel(enum_internal_adc_input_source input_source)
{
	return internal_adc_channel_table[input_source];
}

void internal_initial_conversion(internal_adc_param *adc_param)
{
	uint8_t i;
	uint32_t data_max=0,data_min=4096,data,data_sum=0;
	enum_internal_adc_vref internal_adc_vref = adc_param->internal_adc_vref;
	enum_internal_adc_input_source internal_adc_input_source = adc_param->internal_adc_input_source;
	enum_internal_adc_conversion_resolution internal_adc_conversion_resolution = adc_param->internal_adc_conversion_resolution;
	enum_internal_adc_conversion_num internal_adc_conversion_num = adc_param->internal_adc_conversion_num;
	enum_internal_adc_conversion_gain internal_adc_conversion_gain = adc_param->internal_adc_conversion_gain;	
	enum_internal_adc_channel internal_adc_channel = internal_adc_get_channel(internal_adc_input_source);
	SI32_SARADC_A_select_timeslot0_channel(SI32_SARADC_0, internal_adc_channel);
	switch(internal_adc_vref)
	{
		case internal_adc_vref_via_dedicated_srcadc_voltage:
			SI32_SARADC_A_select_vref_internal(SI32_SARADC_0);
			break;
		case internal_adc_vref_via_vbat:
			SI32_SARADC_A_select_vref_vdd(SI32_SARADC_0);
			break;
		case internal_adc_vref_via_internal_ldo:
			SI32_SARADC_A_select_vref_ldo_output(SI32_SARADC_0); 
			break;
		case internal_adc_vref_pin:
			break;
	}

	switch(internal_adc_conversion_resolution)
	{
		case internal_adc_resolution_10_bit:
			SI32_SARADC_A_select_channel_characteristic0_10bit_mode(SI32_SARADC_0);
			break;
		case internal_adc_resolution_12_bit:
			SI32_SARADC_A_select_channel_characteristic0_12bit_mode(SI32_SARADC_0);
			break;
	}

	SI32_SARADC_A_select_channel_characteristic0_burst_mode_repeat_count(SI32_SARADC_0, internal_adc_conversion_num);
		
	switch(internal_adc_conversion_gain)
	{
		case internal_adc_conversion_gain_one:
			SI32_SARADC_A_select_channel_characteristic0_gain_one(SI32_SARADC_0);			
			break;
		case internal_adc_conversion_gain_half:
			SI32_SARADC_A_select_channel_characteristic0_gain_half(SI32_SARADC_0);
			break;
	}

	for(i=0;i<sample_data_num;i++)
	{
			data = internal_adc_sample();
			data_sum+=data;
			if(data>data_max)
				data_max=data;
			if(data<data_min)
				data_min=data;
	}
	data_sum=data_sum-data_max-data_min;
	adc_param->adc_data=data_sum/(sample_data_num-2);
	switch(internal_adc_conversion_num)
	{
		case internal_adc_conversion_1:
			break;
		case internal_adc_conversion_4:
			adc_param->adc_data >>= 2;
			break;
		case internal_adc_conversion_8:
			adc_param->adc_data >>= 3;
			break;
		case internal_adc_conversion_16:
			adc_param->adc_data >>= 4;
			break;
		case internal_adc_conversion_32:
			adc_param->adc_data >>= 5;
			break;
		case internal_adc_conversion_64:
			adc_param->adc_data >>= 6;
			break;
	}
	
}

uint32_t internal_adc_sample(void)
{
	uint32_t sample_data;
	uint32_t myadc_time_out_flag = 0;

	SI32_SARADC_A_enable_module(SI32_SARADC_0);
	SI32_SARADC_A_enable_autoscan( SI32_SARADC_0 );
	delay_Xus(10);

	SI32_SARADC_A_write_status(SI32_SARADC_0, 0);	

	SI32_SARADC_A_start_conversion(SI32_SARADC_0);
	myadc_time_out_flag = 0;
	while((0x04 & SI32_SARADC_A_read_status(SI32_SARADC_0)) == 0)
	{
		myadc_time_out_flag++;
		if( myadc_time_out_flag == 40000 )
		{
			return 0;
		}
	}
	
	SI32_SARADC_A_clear_single_conversion_complete_interrupt( SI32_SARADC_0 );

	SI32_SARADC_A_disable_autoscan(SI32_SARADC_0);

	sample_data = SI32_SARADC_0->DATA.U32;

	SI32_SARADC_A_write_status(SI32_SARADC_0, 0);	
	SI32_SARADC_A_disable_module(SI32_SARADC_0);

	return sample_data;
}

