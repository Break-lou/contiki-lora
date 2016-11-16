//-----------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//-----------------------------------------------------------------------------
//
// Script: 0.61
// Version: 1

#ifndef __SI32_PVTOSC_A_REGISTERS_H__
#define __SI32_PVTOSC_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_PVTOSC_A_CONTROL_Struct
{
   union
   {
      struct
      {
         // Digital LDO Oscillator Enable
         volatile uint32_t DIGOSCEN: 1;
         // Memory LDO Oscillator Enable
         volatile uint32_t MEMOSCEN: 1;
                  uint32_t reserved0: 2;
         // Digital LDO Oscillator Mode
         volatile uint32_t DIGOSCMD: 1;
         // High Voltage Oscillator Mode
         volatile uint32_t MEMOSCMD: 1;
         // Clock Select
         volatile uint32_t CLKSEL: 1;
                  uint32_t reserved1: 25;
      };
      volatile uint32_t U32;
   };
};

#define SI32_PVTOSC_A_CONTROL_DIGOSCEN_MASK  0x00000001
#define SI32_PVTOSC_A_CONTROL_DIGOSCEN_SHIFT  0
// Disable the digital LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_DIGOSCEN_DISABLED_VALUE  0
#define SI32_PVTOSC_A_CONTROL_DIGOSCEN_DISABLED_U32 \
   (SI32_PVTOSC_A_CONTROL_DIGOSCEN_DISABLED_VALUE << SI32_PVTOSC_A_CONTROL_DIGOSCEN_SHIFT)
// Enable the digital LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_DIGOSCEN_ENABLED_VALUE  1
#define SI32_PVTOSC_A_CONTROL_DIGOSCEN_ENABLED_U32 \
   (SI32_PVTOSC_A_CONTROL_DIGOSCEN_ENABLED_VALUE << SI32_PVTOSC_A_CONTROL_DIGOSCEN_SHIFT)

#define SI32_PVTOSC_A_CONTROL_MEMOSCEN_MASK  0x00000002
#define SI32_PVTOSC_A_CONTROL_MEMOSCEN_SHIFT  1
// Disable the memory LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_MEMOSCEN_DISABLED_VALUE  0
#define SI32_PVTOSC_A_CONTROL_MEMOSCEN_DISABLED_U32 \
   (SI32_PVTOSC_A_CONTROL_MEMOSCEN_DISABLED_VALUE << SI32_PVTOSC_A_CONTROL_MEMOSCEN_SHIFT)
// Enable the memory LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_MEMOSCEN_ENABLED_VALUE  1
#define SI32_PVTOSC_A_CONTROL_MEMOSCEN_ENABLED_U32 \
   (SI32_PVTOSC_A_CONTROL_MEMOSCEN_ENABLED_VALUE << SI32_PVTOSC_A_CONTROL_MEMOSCEN_SHIFT)

#define SI32_PVTOSC_A_CONTROL_DIGOSCMD_MASK  0x00000010
#define SI32_PVTOSC_A_CONTROL_DIGOSCMD_SHIFT  4
// Select fast mode for the digital LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_DIGOSCMD_FAST_VALUE  0
#define SI32_PVTOSC_A_CONTROL_DIGOSCMD_FAST_U32 \
   (SI32_PVTOSC_A_CONTROL_DIGOSCMD_FAST_VALUE << SI32_PVTOSC_A_CONTROL_DIGOSCMD_SHIFT)
// Select slow mode for the digital LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_DIGOSCMD_SLOW_VALUE  1
#define SI32_PVTOSC_A_CONTROL_DIGOSCMD_SLOW_U32 \
   (SI32_PVTOSC_A_CONTROL_DIGOSCMD_SLOW_VALUE << SI32_PVTOSC_A_CONTROL_DIGOSCMD_SHIFT)

#define SI32_PVTOSC_A_CONTROL_MEMOSCMD_MASK  0x00000020
#define SI32_PVTOSC_A_CONTROL_MEMOSCMD_SHIFT  5
// Select fast mode for the memory LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_MEMOSCMD_FAST_VALUE  0
#define SI32_PVTOSC_A_CONTROL_MEMOSCMD_FAST_U32 \
   (SI32_PVTOSC_A_CONTROL_MEMOSCMD_FAST_VALUE << SI32_PVTOSC_A_CONTROL_MEMOSCMD_SHIFT)
// Select slow mode for the memory LDO PVT oscillator.
#define SI32_PVTOSC_A_CONTROL_MEMOSCMD_SLOW_VALUE  1
#define SI32_PVTOSC_A_CONTROL_MEMOSCMD_SLOW_U32 \
   (SI32_PVTOSC_A_CONTROL_MEMOSCMD_SLOW_VALUE << SI32_PVTOSC_A_CONTROL_MEMOSCMD_SHIFT)

#define SI32_PVTOSC_A_CONTROL_CLKSEL_MASK  0x00000040
#define SI32_PVTOSC_A_CONTROL_CLKSEL_SHIFT  6
// Select the digital and memory oscillators as the inputs to the clock dividers.
#define SI32_PVTOSC_A_CONTROL_CLKSEL_OSCILLATORS_VALUE  0
#define SI32_PVTOSC_A_CONTROL_CLKSEL_OSCILLATORS_U32 \
   (SI32_PVTOSC_A_CONTROL_CLKSEL_OSCILLATORS_VALUE << SI32_PVTOSC_A_CONTROL_CLKSEL_SHIFT)
// Select the APB clock as the input to the clock dividers.
#define SI32_PVTOSC_A_CONTROL_CLKSEL_AHB_VALUE  1
#define SI32_PVTOSC_A_CONTROL_CLKSEL_AHB_U32 \
   (SI32_PVTOSC_A_CONTROL_CLKSEL_AHB_VALUE << SI32_PVTOSC_A_CONTROL_CLKSEL_SHIFT)



typedef struct SI32_PVTOSC_A_Struct
{
   struct SI32_PVTOSC_A_CONTROL_Struct             CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
} SI32_PVTOSC_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_PVTOSC_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

