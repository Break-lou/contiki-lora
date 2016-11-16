//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_CRC_A_SUPPORT_H__
#define __SI32_CRC_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Polynomial Enum type

typedef enum SI32_CRC_A_POLYNOMIAL_Enum
{
   SI32_CRC_A_POLYNOMIAL_32_BIT_04C11DB7 = 0,
   SI32_CRC_A_POLYNOMIAL_16_BIT_1021     = 1,
   SI32_CRC_A_POLYNOMIAL_16_BIT_3D65     = 2,
   SI32_CRC_A_POLYNOMIAL_16_BIT_8005     = 3
} SI32_CRC_A_POLYNOMIAL_Enum_Type;

//-----------------------------------------------------------------------------
// Define Processing Order Enum type

typedef enum SI32_CRC_A_PROCESSING_ORDER_Enum
{
   SI32_CRC_A_PROCESSING_ORDER_NO_BYTE_REORIENTATION = 0,
   SI32_CRC_A_PROCESSING_ORDER_16_BIT_BIG_ENDIAN     = 1,
   SI32_CRC_A_PROCESSING_ORDER_32_BIT_BIG_ENDIAN     = 2
} SI32_CRC_A_PROCESSING_ORDER_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_CRC_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
