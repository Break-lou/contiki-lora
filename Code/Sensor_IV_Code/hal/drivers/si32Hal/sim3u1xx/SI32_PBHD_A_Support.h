//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3U1XX_PBHD_A module
//
// Version: 1

#ifndef __SI32_PBHD_A_SUPPORT_H__
#define __SI32_PBHD_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define the PBHD Slew Enum type

typedef enum SI32_PBHD_A_Slew_Enum
{
   SI32_PBHD_A_SLEW_FASTEST = 0,
   SI32_PBHD_A_SLEW_FASTER  = 1,
   SI32_PBHD_A_SLEW_SLOWER  = 2,
   SI32_PBHD_A_SLEW_SLOWEST = 3
} SI32_PBHD_A_Slew_Enum_Type;

//-----------------------------------------------------------------------------
// Define the PBHD Function Enum type

typedef enum SI32_PBHD_A_Function_Enum
{
   SI32_PBHD_A_FUNCTION_GPIO    = 0,
   SI32_PBHD_A_FUNCTION_PMLS    = 1,
   SI32_PBHD_A_FUNCTION_EPCA    = 2,
   SI32_PBHD_A_FUNCTION_UART    = 3,
   SI32_PBHD_A_FUNCTION_LPTIMER = 4
} SI32_PBHD_A_Function_Enum_Type;

//-----------------------------------------------------------------------------
// Define the PBHD Safe State Enum type

typedef enum SI32_PBHD_A_Safe_State_Enum
{
   SI32_PBHD_A_SAFE_STATE_HIZ    = 0,
   SI32_PBHD_A_SAFE_STATE_HIGH   = 1,
   SI32_PBHD_A_SAFE_STATE_LOW    = 2,
   SI32_PBHD_A_SAFE_STATE_IGNORE = 3
} SI32_PBHD_A_Safe_State_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_PBHD_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
