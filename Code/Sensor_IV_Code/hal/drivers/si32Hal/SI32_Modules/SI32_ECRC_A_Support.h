//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_ECRC_A_SUPPORT_H__
#define __SI32_ECRC_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Processing Order Enum type

typedef enum SI32_ECRC_A_PROCESSING_ORDER_Enum
{
   SI32_ECRC_A_PROCESSING_ORDER_NO_BYTE_REORIENTATION = 0,
   SI32_ECRC_A_PROCESSING_ORDER_16_BIT_BIG_ENDIAN     = 1,
   SI32_ECRC_A_PROCESSING_ORDER_32_BIT_BIG_ENDIAN     = 2
} SI32_ECRC_A_PROCESSING_ORDER_Enum_Type;

//-----------------------------------------------------------------------------
// Define Device Peripheral Enum type

typedef enum SI32_ECRC_A_DEVICE_PERIPHERAL_Enum
{
   SI32_ECRC_A_DEVICE_PERIPHERAL_0  = 0,
   SI32_ECRC_A_DEVICE_PERIPHERAL_1  = 1,
   SI32_ECRC_A_DEVICE_PERIPHERAL_2  = 2,
   SI32_ECRC_A_DEVICE_PERIPHERAL_3  = 3,
   SI32_ECRC_A_DEVICE_PERIPHERAL_4  = 4,
   SI32_ECRC_A_DEVICE_PERIPHERAL_5  = 5,
   SI32_ECRC_A_DEVICE_PERIPHERAL_6  = 6,
   SI32_ECRC_A_DEVICE_PERIPHERAL_7  = 7,
   SI32_ECRC_A_DEVICE_PERIPHERAL_8  = 8,
   SI32_ECRC_A_DEVICE_PERIPHERAL_9  = 9,
   SI32_ECRC_A_DEVICE_PERIPHERAL_10 = 10,
   SI32_ECRC_A_DEVICE_PERIPHERAL_11 = 11,
   SI32_ECRC_A_DEVICE_PERIPHERAL_12 = 12,
   SI32_ECRC_A_DEVICE_PERIPHERAL_13 = 13,
   SI32_ECRC_A_DEVICE_PERIPHERAL_14 = 14,
   SI32_ECRC_A_DEVICE_PERIPHERAL_15 = 15,
} SI32_ECRC_A_DEVICE_PERIPHERAL_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_ECRC_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
