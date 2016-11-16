//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3C1XX_SCONFIG_A module
//
// Script: 0.57
// Version: 1

#ifndef __SI32_SCONFIG_A_REGISTERS_H__
#define __SI32_SCONFIG_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_SCONFIG_A_CONFIG_Struct
{
   union
   {
      struct
      {
         // Faster DMA Mode Enable
         volatile uint32_t FDMAEN: 1;
                  uint32_t reserved0: 31;
      };
      volatile uint32_t U32;
   };
};

#define SI32_SCONFIG_A_CONFIG_FDMAEN_MASK  0x00000001
#define SI32_SCONFIG_A_CONFIG_FDMAEN_SHIFT  0
// Disable the faster DMA mode.  The DMA module and channels will behave like a
// standard uDMA.
#define SI32_SCONFIG_A_CONFIG_FDMAEN_DISABLED_VALUE  0
#define SI32_SCONFIG_A_CONFIG_FDMAEN_DISABLED_U32 \
   (SI32_SCONFIG_A_CONFIG_FDMAEN_DISABLED_VALUE << SI32_SCONFIG_A_CONFIG_FDMAEN_SHIFT)
// Enable the faster DMA mode.
#define SI32_SCONFIG_A_CONFIG_FDMAEN_ENABLED_VALUE  1
#define SI32_SCONFIG_A_CONFIG_FDMAEN_ENABLED_U32 \
   (SI32_SCONFIG_A_CONFIG_FDMAEN_ENABLED_VALUE << SI32_SCONFIG_A_CONFIG_FDMAEN_SHIFT)



typedef struct SI32_SCONFIG_A_Struct
{
   struct SI32_SCONFIG_A_CONFIG_Struct             CONFIG         ; // Base Address + 0x0
   volatile uint32_t                               CONFIG_SET;
   volatile uint32_t                               CONFIG_CLR;
   uint32_t                                        reserved0;
} SI32_SCONFIG_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_SCONFIG_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

