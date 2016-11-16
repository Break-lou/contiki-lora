//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3C1XX_PMU_A module
//
// Version: 1

#ifndef __SI32_PMU_A_SUPPORT_H__
#define __SI32_PMU_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define the PMU Enum type

typedef enum SI32_PMU_Wakeup_Enum
{
   SI32_RESET_WAKEUP       = 0,
   SI32_PIN_WAKEUP         = 1,
   SI32_LPTIMER0_WAKEUP    = 2,
   SI32_CMP0_WAKEUP        = 3,
   SI32_RTC0_ALARM_WAKEUP  = 4,
   SI32_RTC0_FAIL_WAKEUP   = 5,
   SI32_NO_WAKEUP          = 6,
   SI32_WAKEUP_ERROR       = 8,
} SI32_PMU_Wakeup_Enum_Type;

#ifdef __cplusplus
}

#endif

#endif // __SI32_PMU_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
