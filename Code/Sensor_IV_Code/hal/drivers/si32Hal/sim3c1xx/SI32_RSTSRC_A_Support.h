//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3C1XX_RSTSRC_A module
//
// Version: 1

#ifndef __SI32_RSTSRC_A_SUPPORT_H__
#define __SI32_RSTSRC_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define the RSTSRC Enum type

typedef enum SI32_RSTSRC_Enum
{
  SI32_PIN_RESET         = 0,
  SI32_POWER_ON_RESET    = 1,
  SI32_VDD_MON_RESET     = 2,
  SI32_CORE_RESET        = 3,
  SI32_MCD_RESET         = 4,
  SI32_WDT_RESET         = 5,
  SI32_SW_RESET          = 6,
  SI32_CMP0_RESET        = 7,
  SI32_CMP1_RESET        = 8,
  SI32_RTC0_RESET        = 10,
  SI32_PMU_WAKEUP_RESET  = 11,
  SI32_RESET_ERROR       = 12
} SI32_RSTSRC_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_RSTSRC_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
