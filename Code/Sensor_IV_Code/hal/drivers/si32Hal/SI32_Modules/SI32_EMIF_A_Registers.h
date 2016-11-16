//-----------------------------------------------------------------------------
// Copyright (c) 2013 by Silicon Laboratories 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//-----------------------------------------------------------------------------
//
// Script: 0.62
// Version: 1

#ifndef __SI32_EMIF_A_REGISTERS_H__
#define __SI32_EMIF_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_EMIF_A_CONTROL_Struct
{
   union
   {
      struct
      {
         // Interface 0 Enable
         volatile uint32_t IF0EN: 1;
         // Interface 1 Enable
         volatile uint32_t IF1EN: 1;
                  uint32_t reserved0: 2;
         // OFF Output State Enable
         volatile uint32_t OFFSTEN: 1;
                  uint32_t reserved1: 27;
      };
      volatile uint32_t U32;
   };
};

#define SI32_EMIF_A_CONTROL_IF0EN_MASK  0x00000001
#define SI32_EMIF_A_CONTROL_IF0EN_SHIFT  0
// Disable interface 0.
#define SI32_EMIF_A_CONTROL_IF0EN_DISABLED_VALUE  0
#define SI32_EMIF_A_CONTROL_IF0EN_DISABLED_U32 \
   (SI32_EMIF_A_CONTROL_IF0EN_DISABLED_VALUE << SI32_EMIF_A_CONTROL_IF0EN_SHIFT)
// Enable interface 0.
#define SI32_EMIF_A_CONTROL_IF0EN_ENABLED_VALUE  1
#define SI32_EMIF_A_CONTROL_IF0EN_ENABLED_U32 \
   (SI32_EMIF_A_CONTROL_IF0EN_ENABLED_VALUE << SI32_EMIF_A_CONTROL_IF0EN_SHIFT)

#define SI32_EMIF_A_CONTROL_IF1EN_MASK  0x00000002
#define SI32_EMIF_A_CONTROL_IF1EN_SHIFT  1
// Disable interface 1.
#define SI32_EMIF_A_CONTROL_IF1EN_DISABLED_VALUE  0
#define SI32_EMIF_A_CONTROL_IF1EN_DISABLED_U32 \
   (SI32_EMIF_A_CONTROL_IF1EN_DISABLED_VALUE << SI32_EMIF_A_CONTROL_IF1EN_SHIFT)
// Enable interface 1.
#define SI32_EMIF_A_CONTROL_IF1EN_ENABLED_VALUE  1
#define SI32_EMIF_A_CONTROL_IF1EN_ENABLED_U32 \
   (SI32_EMIF_A_CONTROL_IF1EN_ENABLED_VALUE << SI32_EMIF_A_CONTROL_IF1EN_SHIFT)

#define SI32_EMIF_A_CONTROL_OFFSTEN_MASK  0x00000010
#define SI32_EMIF_A_CONTROL_OFFSTEN_SHIFT  4
// EMIF will not enter the off state after 4 idle cycles.
#define SI32_EMIF_A_CONTROL_OFFSTEN_DISABLED_VALUE  0
#define SI32_EMIF_A_CONTROL_OFFSTEN_DISABLED_U32 \
   (SI32_EMIF_A_CONTROL_OFFSTEN_DISABLED_VALUE << SI32_EMIF_A_CONTROL_OFFSTEN_SHIFT)
// EMIF will enter the off state after 4 idle cycles.
#define SI32_EMIF_A_CONTROL_OFFSTEN_ENABLED_VALUE  1
#define SI32_EMIF_A_CONTROL_OFFSTEN_ENABLED_U32 \
   (SI32_EMIF_A_CONTROL_OFFSTEN_ENABLED_VALUE << SI32_EMIF_A_CONTROL_OFFSTEN_SHIFT)



struct SI32_EMIF_A_STATUS_Struct
{
   union
   {
      struct
      {
         // EMIF OFF Status
         volatile uint32_t OFFSTS: 1;
         // EMIF IDLE Status
         volatile uint32_t IDLESTS: 1;
                  uint32_t reserved0: 30;
      };
      volatile uint32_t U32;
   };
};

#define SI32_EMIF_A_STATUS_OFFSTS_MASK  0x00000001
#define SI32_EMIF_A_STATUS_OFFSTS_SHIFT  0
// The EMIF bus is active.
#define SI32_EMIF_A_STATUS_OFFSTS_ON_VALUE  0
#define SI32_EMIF_A_STATUS_OFFSTS_ON_U32 \
   (SI32_EMIF_A_STATUS_OFFSTS_ON_VALUE << SI32_EMIF_A_STATUS_OFFSTS_SHIFT)
// The EMIF is in the off bus state.
#define SI32_EMIF_A_STATUS_OFFSTS_OFF_VALUE  1
#define SI32_EMIF_A_STATUS_OFFSTS_OFF_U32 \
   (SI32_EMIF_A_STATUS_OFFSTS_OFF_VALUE << SI32_EMIF_A_STATUS_OFFSTS_SHIFT)

#define SI32_EMIF_A_STATUS_IDLESTS_MASK  0x00000002
#define SI32_EMIF_A_STATUS_IDLESTS_SHIFT  1
// The EMIF has not been idle for four cycles.
#define SI32_EMIF_A_STATUS_IDLESTS_NOT_IDLE_VALUE  0
#define SI32_EMIF_A_STATUS_IDLESTS_NOT_IDLE_U32 \
   (SI32_EMIF_A_STATUS_IDLESTS_NOT_IDLE_VALUE << SI32_EMIF_A_STATUS_IDLESTS_SHIFT)
// The EMIF has been idle for four four cycles.
#define SI32_EMIF_A_STATUS_IDLESTS_IDLE_VALUE  1
#define SI32_EMIF_A_STATUS_IDLESTS_IDLE_U32 \
   (SI32_EMIF_A_STATUS_IDLESTS_IDLE_VALUE << SI32_EMIF_A_STATUS_IDLESTS_SHIFT)



typedef struct SI32_EMIF_A_Struct
{
   struct SI32_EMIF_A_CONTROL_Struct               CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
   uint32_t                                        reserved1[4];
   struct SI32_EMIF_A_STATUS_Struct                STATUS         ; // Base Address + 0x20
   uint32_t                                        reserved2;
   uint32_t                                        reserved3;
   uint32_t                                        reserved4;
} SI32_EMIF_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_EMIF_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

