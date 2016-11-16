//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_SARADC_A_SUPPORT_H__
#define __SI32_SARADC_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Bias Power Enum type

typedef enum SI32_SARADC_A_BIAS_POWER_Enum
{
	SI32_SARADC_A_BIAS_POWER_MAXIMUM = 0,
	SI32_SARADC_A_BIAS_POWER_HIGH    = 1,
	SI32_SARADC_A_BIAS_POWER_LOW     = 2,
	SI32_SARADC_A_BIAS_POWER_MINIMUM = 3
} SI32_SARADC_A_BIAS_POWER_Enum_Type;

//-----------------------------------------------------------------------------
// Define Burst Mode Repeat Count Enum type

typedef enum SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_Enum
{
	SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_SAMPLE_ONCE     = 0,
	SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_SAMPLE_4_TIMES  = 1,
	SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_SAMPLE_8_TIMES  = 2,
	SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_SAMPLE_16_TIMES = 3,
	SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_SAMPLE_32_TIMES = 4,
	SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_SAMPLE_64_TIMES = 5
} SI32_SARADC_A_BURST_MODE_REPEAT_COUNT_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_SARADC_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
