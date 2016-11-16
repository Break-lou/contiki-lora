//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3U1XX_LDO_A module
//
// Script: 0.56
// Version: 1

#ifndef __SI32_LDO_A_REGISTERS_H__
#define __SI32_LDO_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_LDO_A_CONTROL_Struct
{
   union
   {
      struct
      {
                  uint32_t reserved0: 1;
         // LDO Bias Current Selection
         volatile uint32_t LDOIBIAS: 1;
                  uint32_t reserved1: 29;
         // LDO Analog Enable
         volatile uint32_t LDOAEN: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_LDO_A_CONTROL_LDOIBIAS_MASK  0x00000002
#define SI32_LDO_A_CONTROL_LDOIBIAS_SHIFT  1
// Select high bias.
#define SI32_LDO_A_CONTROL_LDOIBIAS_HIGHBIAS_VALUE  0
#define SI32_LDO_A_CONTROL_LDOIBIAS_HIGHBIAS_U32 \
   (SI32_LDO_A_CONTROL_LDOIBIAS_HIGHBIAS_VALUE << SI32_LDO_A_CONTROL_LDOIBIAS_SHIFT)
// Select low bias (AHB frequency <= 2.5 MHz).
#define SI32_LDO_A_CONTROL_LDOIBIAS_LOWBIAS_VALUE  1
#define SI32_LDO_A_CONTROL_LDOIBIAS_LOWBIAS_U32 \
   (SI32_LDO_A_CONTROL_LDOIBIAS_LOWBIAS_VALUE << SI32_LDO_A_CONTROL_LDOIBIAS_SHIFT)

#define SI32_LDO_A_CONTROL_LDOAEN_MASK  0x80000000
#define SI32_LDO_A_CONTROL_LDOAEN_SHIFT  31
// LDO0 analog output disabled.
#define SI32_LDO_A_CONTROL_LDOAEN_DISABLE_VALUE  0U
#define SI32_LDO_A_CONTROL_LDOAEN_DISABLE_U32 \
   (SI32_LDO_A_CONTROL_LDOAEN_DISABLE_VALUE << SI32_LDO_A_CONTROL_LDOAEN_SHIFT)
// LDO0 analog output enabled.
#define SI32_LDO_A_CONTROL_LDOAEN_ENABLE_VALUE  1U
#define SI32_LDO_A_CONTROL_LDOAEN_ENABLE_U32 \
   (SI32_LDO_A_CONTROL_LDOAEN_ENABLE_VALUE << SI32_LDO_A_CONTROL_LDOAEN_SHIFT)



typedef struct SI32_LDO_A_Struct
{
   struct SI32_LDO_A_CONTROL_Struct                CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
} SI32_LDO_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_LDO_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

