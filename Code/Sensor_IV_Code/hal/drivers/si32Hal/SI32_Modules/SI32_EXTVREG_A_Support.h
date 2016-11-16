//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_EXTVREG_A_SUPPORT_H__
#define __SI32_EXTVREG_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Current Limit Minimum Coarse Enum type

typedef enum SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_Enum
{
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_1_UA = 1,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_2_UA = 2,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_3_UA = 3,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_4_UA = 4,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_5_UA = 5,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_6_UA = 6,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_7_UA = 7,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_8_UA = 8
} SI32_EXTVREG_A_CURRENT_LIMIT_MIN_COARSE_Enum_Type;

//-----------------------------------------------------------------------------
// Define Current Limit Minimum Fine Enum type

typedef enum SI32_EXTVREG_A_CURRENT_LIMIT_MIN_FINE_Enum
{
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_FINE_P00_UA = 0,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_FINE_P25_UA = 1,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_FINE_P50_UA = 2,
   SI32_EXTVREG_A_CURRENT_LIMIT_MIN_FINE_P75_UA = 3
} SI32_EXTVREG_A_CURRENT_LIMIT_MIN_FINE_Enum_Type;

//-----------------------------------------------------------------------------
// Define Foldback Voltage Offset Enum type

typedef enum SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_Enum
{
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_0P0_V = 0,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_0P5_V = 1,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_1P0_V = 2,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_1P5_V = 3,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_2P0_V = 4,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_2P5_V = 5,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_3P0_V = 6,
   SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_3P5_V = 7
} SI32_EXTVREG_A_FOLDBACK_VOLTAGE_OFFSET_Enum_Type;

//-----------------------------------------------------------------------------
// Define Current Limit Maximum Enum type

typedef enum SI32_EXTVREG_A_CURRENT_LIMIT_MAX_Enum
{
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_2_UA = 0,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_3_UA = 1,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_4_UA = 2,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_5_UA = 3,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_6_UA = 4,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_7_UA = 5,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_8_UA = 6,
   SI32_EXTVREG_A_CURRENT_LIMIT_MAX_9_UA = 7,
} SI32_EXTVREG_A_CURRENT_LIMIT_MAX_Enum_Type;

//-----------------------------------------------------------------------------
// Define ADC Current Sense Gain Enum type

typedef enum SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_Enum
{
   SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_16X  = 0,
   SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_8X  = 1,
   SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_4X  = 2,
   SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_2X  = 3,
   SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_11X = 4
} SI32_EXTVREG_A_ADC_CURRENT_SENSE_GAIN_Enum_Type;

//-----------------------------------------------------------------------------
// Define External Regulator Current Sense Gain Enum type

typedef enum SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_Enum
{
   SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_16X  = 0,
   SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_8X  = 1,
   SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_4X  = 2,
   SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_2X  = 3,
   SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_1X = 4
} SI32_EXTVREG_A_REG_CURRENT_SENSE_GAIN_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_EXTVREG_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
