//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_SPI_B_Support_Guard__
#define __SI32_SPI_B_Support_Guard__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define Clock Mode ENUMS
typedef enum SI32_SPI_B_CLOCK_MODE_Enum
{
  SI32_SPI_SAMPLE_FIRST_IDLE_LOW    = 0x0,
  SI32_SPI_SHIFT_FIRST_IDLE_LOW     = 0x1,
  SI32_SPI_SAMPLE_FIRST_IDLE_HIGH   = 0x2,
  SI32_SPI_SHIFT_FIRST_IDLE_HIGH    = 0x3
} SI32_SPI_B_CLOCK_MODE_Enum_Type;


//-----------------------------------------------------------------------------
// Define the LOCK Enum type

typedef enum SI32_SPI_B_FIFO_THRESHOLD_Enum
{
  SI32_SPI_FIFO_THRESHOLD_ONE           = 0x0,
  SI32_SPI_FIFO_THRESHOLD_TWO           = 0x1,
  SI32_SPI_FIFO_THRESHOLD_FOUR          = 0x2,
  SI32_SPI_FIFO_THRESHOLD_FULL_OR_EMPTY = 0x3,
} SI32_SPI_B_FIFO_THRESHOLD_Enum_Type;

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // __SI32_SPI_A_Support_Guard__

//-eof--------------------------------------------------------------------------
