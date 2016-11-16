//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3L1XX_SLEEPCTRL_A module
//
// Script: 0.56
// Version: 1

#ifndef __SI32_SLEEPCTRL_A_REGISTERS_H__
#define __SI32_SLEEPCTRL_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_SLEEPCTRL_A_CONTROL_Struct
{
   union
   {
      struct
      {
         // CLKDIV
         volatile uint32_t CLKDIV: 2;
         // CPMD
         volatile uint32_t CPMD: 2;
                  uint32_t reserved0: 28;
      };
      volatile uint32_t U32;
   };
};

#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_MASK  0x00000003
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_SHIFT  0
// Undivided RTC clock
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV1_VALUE  0
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV1_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV1_VALUE << SI32_SLEEPCTRL_A_CONTROL_CLKDIV_SHIFT)
// RTC clock divided by 2
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV2_VALUE  1
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV2_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV2_VALUE << SI32_SLEEPCTRL_A_CONTROL_CLKDIV_SHIFT)
// RTC clock divided by 4
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV4_VALUE  2
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV4_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV4_VALUE << SI32_SLEEPCTRL_A_CONTROL_CLKDIV_SHIFT)
// RTC clock divided by 8
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV8_VALUE  3
#define SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV8_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CLKDIV_DIV8_VALUE << SI32_SLEEPCTRL_A_CONTROL_CLKDIV_SHIFT)

#define SI32_SLEEPCTRL_A_CONTROL_CPMD_MASK  0x0000000C
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_SHIFT  2
// VBAT is passed directly to VCP
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_VBAT_VALUE  0
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_VBAT_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CPMD_VBAT_VALUE << SI32_SLEEPCTRL_A_CONTROL_CPMD_SHIFT)
// VCP equals VBAT / 2
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_VBATDIV2_VALUE  1
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_VBATDIV2_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CPMD_VBATDIV2_VALUE << SI32_SLEEPCTRL_A_CONTROL_CPMD_SHIFT)
// VCP is tri-stated
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_TRISTATE_VALUE  2
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_TRISTATE_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CPMD_TRISTATE_VALUE << SI32_SLEEPCTRL_A_CONTROL_CPMD_SHIFT)
// VCP is connected to ground
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_GROUND_VALUE  3
#define SI32_SLEEPCTRL_A_CONTROL_CPMD_GROUND_U32 \
   (SI32_SLEEPCTRL_A_CONTROL_CPMD_GROUND_VALUE << SI32_SLEEPCTRL_A_CONTROL_CPMD_SHIFT)



typedef struct SI32_SLEEPCTRL_A_Struct
{
   uint32_t                                        reserved0[4];
   struct SI32_SLEEPCTRL_A_CONTROL_Struct          CONTROL        ; // Base Address + 0x10
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved1;
} SI32_SLEEPCTRL_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_SLEEPCTRL_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

