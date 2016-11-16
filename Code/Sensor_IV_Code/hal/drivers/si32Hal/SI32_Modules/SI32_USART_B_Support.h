//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_USART_B_SUPPORT_H__
#define __SI32_USART_B_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Stop Bits Enum type

typedef enum SI32_USART_STOP_BITS_Enum
{
   SI32_USART_B_STOP_BITS_0P5_BIT  = 0,
   SI32_USART_B_STOP_BITS_1_BIT    = 1,
   SI32_USART_B_STOP_BITS_1P5_BITS = 2,
   SI32_USART_B_STOP_BITS_2_BITS   = 3
} SI32_USART_B_STOP_BITS_Enum_Type;

//-----------------------------------------------------------------------------
// Define Parity Enum type

typedef enum SI32_USART_B_PARITY_Enum
{
   SI32_USART_B_PARITY_ODD   = 0,
   SI32_USART_B_PARITY_EVEN  = 1,
   SI32_USART_B_PARITY_SET   = 2,
   SI32_USART_B_PARITY_CLEAR = 3
} SI32_USART_B_PARITY_Enum_Type;

//-----------------------------------------------------------------------------
// Define Data Length Enum type

typedef enum SI32_USART_B_DATA_LENGTH_Enum
{
   SI32_USART_B_DATA_LENGTH_5_BITS        = 5,
   SI32_USART_B_DATA_LENGTH_6_BITS        = 6,
   SI32_USART_B_DATA_LENGTH_7_BITS        = 7,
   SI32_USART_B_DATA_LENGTH_8_BITS        = 8,
   SI32_USART_B_DATA_LENGTH_9_BITS_NORMAL = 9,
   SI32_USART_B_DATA_LENGTH_9_BITS_STORED = 9,
   SI32_USART_B_DATA_LENGTH_9_BITS_FIXED  = 10,
   SI32_USART_B_DATA_LENGTH_9_BITS_MATCH  = 10
} SI32_USART_B_DATA_LENGTH_Enum_Type;


//-----------------------------------------------------------------------------
// Define IrDA Pulse Width Enum type

typedef enum SI32_USART_B_IRDA_PULSE_WIDTH_Enum
{
	SI32_USART_B_IRDA_PULSE_WIDTH_1_16TH = 0,
	SI32_USART_B_IRDA_PULSE_WIDTH_1_8TH  = 1,
	SI32_USART_B_IRDA_PULSE_WIDTH_3_16TH = 2,
	SI32_USART_B_IRDA_PULSE_WIDTH_1_4TH  = 3
} SI32_USART_B_IRDA_PULSE_WIDTH_Enum_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_USART_B_SUPPORT_H__

//-eof--------------------------------------------------------------------------
