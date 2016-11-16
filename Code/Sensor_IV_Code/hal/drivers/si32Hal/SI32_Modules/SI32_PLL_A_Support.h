//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_PLL_A_SUPPORT_H__
#define __SI32_PLL_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Spectrum Spreading Amplitude Enum type

typedef enum SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_Enum
{
	SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_0P1_PERCENT = 0,
	SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_0P2_PERCENT = 1,
	SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_0P4_PERCENT = 2,
	SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_0P8_PERCENT = 3,
	SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_1P6_PERCENT = 4
} SI32_PLL_A_SPECTRUM_SPREADING_AMPLITUDE_Enum_Type;

//-----------------------------------------------------------------------------
// Define Output Frequency Range Enum type

typedef enum SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_Enum
{
	SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_23_TO_32_MHZ = 0,
	SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_33_TO_54_MHZ = 1,
	SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_45_TO_71_MHZ = 2,
	SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_53_TO_80_MHZ = 3,
	SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_73_TO_80_MHZ = 4
} SI32_PLL_A_OUTPUT_FREQUENCY_RANGE_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_PLL_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
