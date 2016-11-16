//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_DCDC_A_SUPPORT_H__
#define __SI32_DCDC_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Minimum PulseWidth Type

typedef enum SI32_DCDC_MIN_PULSE_WIDTH_Enum
{
   SI32_DCDC_MIN_PULSE_WIDTH_DISABLED = 0,
   SI32_DCDC_MIN_PULSE_WIDTH_10NS     = 1,
   SI32_DCDC_MIN_PULSE_WIDTH_20NS     = 2,
   SI32_DCDC_MIN_PULSE_WIDTH_40NS     = 3
} SI32_DCDC_MIN_PULSE_WIDTH_Enum_Type;

//-----------------------------------------------------------------------------
// Define Interrupt Mode

typedef enum SI32_DCDC_INTERRUPT_MODE_Enum
{
   SI32_DCDC_INTERRUPT_MODE_LOW        = 0,
   SI32_DCDC_INTERRUPT_MODE_NOT_LOW    = 1,
   SI32_DCDC_INTERRUPT_MODE_NOT_IN_REG = 2,
   SI32_DCDC_INTERRUPT_MODE_IN_REG     = 3
} SI32_DCDC_INTERRUPT_MODE_Enum_Type;

//-----------------------------------------------------------------------------
// Define Interrupt Mode

typedef enum SI32_DCDC_READY_LOW_THRESHOLD_Enum
{
   SI32_DCDC_READY_LOW_THRESHOLD_95 = 0,
   SI32_DCDC_READY_LOW_THRESHOLD_90 = 1,
   SI32_DCDC_READY_LOW_THRESHOLD_85 = 2,
   SI32_DCDC_READY_LOW_THRESHOLD_80 = 3
} SI32_DCDC_READY_LOW_THRESHOLD_Enum_Type;


#ifdef __cplusplus
}
#endif

#endif // __SI32_DCDC_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
