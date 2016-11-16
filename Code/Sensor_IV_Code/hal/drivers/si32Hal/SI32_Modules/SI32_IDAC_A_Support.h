//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_IDAC_A_SUPPORT_H__
#define __SI32_IDAC_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Output Update Trigger Enum type

typedef enum SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_Enum
{
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_DACT8              = 0,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_DACT9              = 1,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_DACT10             = 2,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_DACT11             = 3,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_ETRIG_RISING_EDGE  = 4,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_ETRIG_FALLING_EDGE = 5,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_ETRIG_ANY_EDGE     = 6,
   SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_ON_DEMAND          = 7
} SI32_IDAC_A_OUTPUT_UPDATE_TRIGGER_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_IDAC_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
