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

#ifndef __SI32_VMON_B_REGISTERS_H__
#define __SI32_VMON_B_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_VMON_B_CONTROL_Struct
{
   union
   {
      struct
      {
                  uint32_t reserved0: 2;
         // VBAT Reset Threshold Status Flag
         volatile uint32_t VBATRSTF: 1;
         // VBAT Low Interrupt Flag
         volatile uint32_t VBATLI: 1;
         // VBAT High Threshold Enable
         volatile uint32_t VBATHITHEN: 1;
                  uint32_t reserved1: 1;
         // VBAT Low Interrupt Enable
         volatile uint32_t VBATLIEN: 1;
                  uint32_t reserved2: 24;
         // VBAT Supply Monitor Enable
         volatile uint32_t VMONEN: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_VMON_B_CONTROL_VBATRSTF_MASK  0x00000004
#define SI32_VMON_B_CONTROL_VBATRSTF_SHIFT  2
// The VBAT voltage is below the VBAT reset threshold.
#define SI32_VMON_B_CONTROL_VBATRSTF_VBAT_IS_BELOW_RESET_VALUE  0
#define SI32_VMON_B_CONTROL_VBATRSTF_VBAT_IS_BELOW_RESET_U32 \
   (SI32_VMON_B_CONTROL_VBATRSTF_VBAT_IS_BELOW_RESET_VALUE << SI32_VMON_B_CONTROL_VBATRSTF_SHIFT)
// The VBAT voltage is above the VBAT reset threshold.
#define SI32_VMON_B_CONTROL_VBATRSTF_VBAT_IS_ABOVE_RESET_VALUE  1
#define SI32_VMON_B_CONTROL_VBATRSTF_VBAT_IS_ABOVE_RESET_U32 \
   (SI32_VMON_B_CONTROL_VBATRSTF_VBAT_IS_ABOVE_RESET_VALUE << SI32_VMON_B_CONTROL_VBATRSTF_SHIFT)

#define SI32_VMON_B_CONTROL_VBATLI_MASK  0x00000008
#define SI32_VMON_B_CONTROL_VBATLI_SHIFT  3
// The VBAT voltage is below the early warning threshold.
#define SI32_VMON_B_CONTROL_VBATLI_VBAT_IS_LOW_VALUE  0
#define SI32_VMON_B_CONTROL_VBATLI_VBAT_IS_LOW_U32 \
   (SI32_VMON_B_CONTROL_VBATLI_VBAT_IS_LOW_VALUE << SI32_VMON_B_CONTROL_VBATLI_SHIFT)
// The VBAT voltage is above the early warning threshold.
#define SI32_VMON_B_CONTROL_VBATLI_VBAT_IS_OK_VALUE  1
#define SI32_VMON_B_CONTROL_VBATLI_VBAT_IS_OK_U32 \
   (SI32_VMON_B_CONTROL_VBATLI_VBAT_IS_OK_VALUE << SI32_VMON_B_CONTROL_VBATLI_SHIFT)

#define SI32_VMON_B_CONTROL_VBATHITHEN_MASK  0x00000010
#define SI32_VMON_B_CONTROL_VBATHITHEN_SHIFT  4
// Use the standard VBAT thresholds.
#define SI32_VMON_B_CONTROL_VBATHITHEN_DISABLED_VALUE  0
#define SI32_VMON_B_CONTROL_VBATHITHEN_DISABLED_U32 \
   (SI32_VMON_B_CONTROL_VBATHITHEN_DISABLED_VALUE << SI32_VMON_B_CONTROL_VBATHITHEN_SHIFT)
// Use the high VBAT thresholds.
#define SI32_VMON_B_CONTROL_VBATHITHEN_ENABLED_VALUE  1
#define SI32_VMON_B_CONTROL_VBATHITHEN_ENABLED_U32 \
   (SI32_VMON_B_CONTROL_VBATHITHEN_ENABLED_VALUE << SI32_VMON_B_CONTROL_VBATHITHEN_SHIFT)

#define SI32_VMON_B_CONTROL_VBATLIEN_MASK  0x00000040
#define SI32_VMON_B_CONTROL_VBATLIEN_SHIFT  6
// Disable the VBAT low interrupt.
#define SI32_VMON_B_CONTROL_VBATLIEN_DISABLED_VALUE  0
#define SI32_VMON_B_CONTROL_VBATLIEN_DISABLED_U32 \
   (SI32_VMON_B_CONTROL_VBATLIEN_DISABLED_VALUE << SI32_VMON_B_CONTROL_VBATLIEN_SHIFT)
// Enable the VBAT low interrupt.
#define SI32_VMON_B_CONTROL_VBATLIEN_ENABLED_VALUE  1
#define SI32_VMON_B_CONTROL_VBATLIEN_ENABLED_U32 \
   (SI32_VMON_B_CONTROL_VBATLIEN_ENABLED_VALUE << SI32_VMON_B_CONTROL_VBATLIEN_SHIFT)

#define SI32_VMON_B_CONTROL_VMONEN_MASK  0x80000000
#define SI32_VMON_B_CONTROL_VMONEN_SHIFT  31
// Disable the VBAT supply monitor.
#define SI32_VMON_B_CONTROL_VMONEN_DISABLED_VALUE  0U
#define SI32_VMON_B_CONTROL_VMONEN_DISABLED_U32 \
   (SI32_VMON_B_CONTROL_VMONEN_DISABLED_VALUE << SI32_VMON_B_CONTROL_VMONEN_SHIFT)
// Enable the VBAT supply monitor.
#define SI32_VMON_B_CONTROL_VMONEN_ENABLED_VALUE  1U
#define SI32_VMON_B_CONTROL_VMONEN_ENABLED_U32 \
   (SI32_VMON_B_CONTROL_VMONEN_ENABLED_VALUE << SI32_VMON_B_CONTROL_VMONEN_SHIFT)



typedef struct SI32_VMON_B_Struct
{
   struct SI32_VMON_B_CONTROL_Struct               CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
   uint32_t                                        reserved1[4];
} SI32_VMON_B_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_VMON_B_REGISTERS_H__

//-eof--------------------------------------------------------------------------

