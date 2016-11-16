#ifndef INTERNAL_ADC_OPTION_H
#define	INTERNAL_ADC_OPTION_H

#include <stdint.h>
#include <stdlib.h>

#define INTERNAL_ADC_SLOT_MAP_LEN	8
#define INTERNAL_ADC_VREF_MAP_LEN	4
#define INTERNAL_ADC_CHARACTERISTIC_TABLE_LEN 4
#define INTERNAL_ADC_CHANNEL_NUM	31

#define INTERNAL_ADC_CONVERSION_TABLE_LEN	10


typedef enum
{
	internal_adc_channel_0 = 0,
	internal_adc_channel_1 = 1,
	internal_adc_channel_2 = 2,
	internal_adc_channel_3 = 3,
	internal_adc_channel_4 = 4,
	internal_adc_channel_5 = 5,
	internal_adc_channel_6 = 6,
	internal_adc_channel_7 = 7,
	internal_adc_channel_8 = 8,
	internal_adc_channel_9 = 9,
	internal_adc_channel_10 = 10,
	internal_adc_channel_11 = 11,
	internal_adc_channel_12 = 12,
	internal_adc_channel_13 = 13,
	internal_adc_channel_14 = 14,
	internal_adc_channel_19 = 19,
	internal_adc_channel_20 = 20,
	internal_adc_channel_22 = 22,
	internal_adc_channel_23 = 23,
	internal_adc_channel_24 = 24,
	internal_adc_channel_25 = 25,
	internal_adc_channel_26 = 26,
	internal_adc_channel_27 = 27,
	internal_adc_channel_28 = 28,
	internal_adc_channel_29 = 29,
	internal_adc_channel_30 = 30,
}enum_internal_adc_channel;
/*
typedef enum
{
	internal_adc_port_pb0_3 = 0,
	internal_adc_port_pb0_8,
	internal_adc_port_pb0_9,
	internal_adc_port_pb1_4,
	internal_adc_port_pb1_5,
	internal_adc_port_pb1_6,
	internal_adc_port_pb2_0,
	internal_adc_port_pb2_4,
	internal_adc_port_pb2_5,
	internal_adc_port_pb2_6,
	internal_adc_port_pb2_7,
	internal_adc_port_pb3_0,
	internal_adc_port_pb3_1,
	internal_adc_port_pb3_8,
	internal_adc_port_pb3_9,
	internal_adc_port_pb4_2,
	internal_adc_port_pb0_0,
	internal_adc_port_pb0_1,
	internal_adc_port_pb0_2,
	internal_adc_vss,
	internal_adc_digital_ldo_output,
	internal_adc_memory_ldo_output,
	internal_adc_vdc,
	internal_adc_vbat,
	internal_adc_half_charge_pump_output,
	internal_adc_temperature_sensor_output,
}enum_internal_adc_input_source;*/
typedef enum
{
	internal_adc_port_pb0_3 = 0,
	internal_adc_port_pb0_9,
	internal_adc_port_pb2_0,
	internal_adc_port_pb2_1,
	internal_adc_port_pb2_2,
	internal_adc_port_pb2_3, //5
	internal_adc_port_pb2_4,
	internal_adc_port_pb2_5,
	internal_adc_port_pb2_6,
	internal_adc_port_pb2_7,
	internal_adc_port_pb3_3, //10
	internal_adc_port_pb3_4,
  internal_adc_port_pb3_5,
	internal_adc_port_pb3_6,
	internal_adc_port_pb3_7,
	internal_adc_port_pb3_8, //15
	internal_adc_port_pb3_9,
	internal_adc_port_pb0_0,//20
	internal_adc_port_pb0_1,
	internal_adc_port_pb0_2,
	internal_adc_vss,
	internal_adc_digital_ldo_output,
	internal_adc_memory_ldo_output,
	internal_adc_vdc,
	internal_adc_vbat,
	internal_adc_half_charge_pump_output,
	internal_adc_temperature_sensor_output,
}enum_internal_adc_input_source;

typedef enum
{
	internal_adc_vref_via_dedicated_srcadc_voltage = 0,
	internal_adc_vref_via_vbat,	
	internal_adc_vref_via_internal_ldo,
	internal_adc_vref_pin,
}enum_internal_adc_vref;

typedef enum
{
	internal_adc_resolution_10_bit = 0,
	internal_adc_resolution_12_bit,
}enum_internal_adc_conversion_resolution;

typedef enum
{
	internal_adc_conversion_1 = 0,
	internal_adc_conversion_4,
	internal_adc_conversion_8,
	internal_adc_conversion_16,
	internal_adc_conversion_32,
	internal_adc_conversion_64,
}enum_internal_adc_conversion_num;

typedef enum
{
	internal_adc_conversion_gain_one,
	internal_adc_conversion_gain_half,
}enum_internal_adc_conversion_gain;


typedef struct internal_adc_param_t
{
	enum_internal_adc_input_source internal_adc_input_source;
	enum_internal_adc_vref internal_adc_vref;
	enum_internal_adc_conversion_resolution internal_adc_conversion_resolution;
	enum_internal_adc_conversion_num internal_adc_conversion_num;
	enum_internal_adc_conversion_gain internal_adc_conversion_gain;
	uint32_t adc_data;
}internal_adc_param;

uint32_t internal_adc_sample(void);

void internal_initial_conversion(internal_adc_param *adc_param);

#endif

