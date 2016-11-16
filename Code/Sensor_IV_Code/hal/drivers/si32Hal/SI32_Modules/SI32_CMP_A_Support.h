//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_CMP_A_SUPPORT_H__
#define __SI32_CMP_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Input Mux Enum type

typedef enum SI32_CMP_A_INPUT_MUX_Enum
{
	SI32_CMP_A_INPUT_MUX_DIRECT   = 0,
	SI32_CMP_A_INPUT_MUX_CMPN_VSS = 1,
	SI32_CMP_A_INPUT_MUX_CMPP_DAC = 2,
	SI32_CMP_A_INPUT_MUX_CMPN_DAC = 3
} SI32_CMP_A_INPUT_MUX_Enum_Type;

//-----------------------------------------------------------------------------
// Define Respone Power Mode Enum type

typedef enum SI32_CMP_A_RESPONSE_POWER_MODE_Enum
{
	SI32_CMP_A_RESPONSE_POWER_MODE_FASTEST = 0,
	SI32_CMP_A_RESPONSE_POWER_MODE_FAST    = 1,
	SI32_CMP_A_RESPONSE_POWER_MODE_SLOW    = 2,
	SI32_CMP_A_RESPONSE_POWER_MODE_SLOWEST = 3
} SI32_CMP_A_RESPONSE_POWER_MODE_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_CMP_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
