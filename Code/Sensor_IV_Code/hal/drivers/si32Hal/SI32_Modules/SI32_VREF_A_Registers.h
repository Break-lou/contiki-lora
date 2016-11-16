//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// Script: 0.57
// Version: 1

#ifndef __SI32_VREF_A_REGISTERS_H__
#define __SI32_VREF_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_VREF_A_CONTROL_Struct
{
   union
   {
      struct
      {
         // Voltage Reference Doubler
         volatile uint32_t VREF2X: 1;
         // Temperature Sensor Enable
         volatile uint32_t TEMPEN: 1;
                  uint32_t reserved0: 29;
         // Voltage Reference Enable
         volatile uint32_t VREFEN: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_VREF_A_CONTROL_VREF2X_MASK  0x00000001
#define SI32_VREF_A_CONTROL_VREF2X_SHIFT  0
// VREF output is nominally 1.2 V
#define SI32_VREF_A_CONTROL_VREF2X_DISABLED_VALUE  0
#define SI32_VREF_A_CONTROL_VREF2X_DISABLED_U32 \
   (SI32_VREF_A_CONTROL_VREF2X_DISABLED_VALUE << SI32_VREF_A_CONTROL_VREF2X_SHIFT)
// VREF output is nominally 2.4 V
#define SI32_VREF_A_CONTROL_VREF2X_ENABLED_VALUE  1
#define SI32_VREF_A_CONTROL_VREF2X_ENABLED_U32 \
   (SI32_VREF_A_CONTROL_VREF2X_ENABLED_VALUE << SI32_VREF_A_CONTROL_VREF2X_SHIFT)

#define SI32_VREF_A_CONTROL_TEMPEN_MASK  0x00000002
#define SI32_VREF_A_CONTROL_TEMPEN_SHIFT  1
// Disable the temperature sensor.
#define SI32_VREF_A_CONTROL_TEMPEN_DISABLED_VALUE  0
#define SI32_VREF_A_CONTROL_TEMPEN_DISABLED_U32 \
   (SI32_VREF_A_CONTROL_TEMPEN_DISABLED_VALUE << SI32_VREF_A_CONTROL_TEMPEN_SHIFT)
// Enable the temperature sensor.
#define SI32_VREF_A_CONTROL_TEMPEN_ENABLED_VALUE  1
#define SI32_VREF_A_CONTROL_TEMPEN_ENABLED_U32 \
   (SI32_VREF_A_CONTROL_TEMPEN_ENABLED_VALUE << SI32_VREF_A_CONTROL_TEMPEN_SHIFT)

#define SI32_VREF_A_CONTROL_VREFEN_MASK  0x80000000
#define SI32_VREF_A_CONTROL_VREFEN_SHIFT  31
// Disable the Voltage Reference.
#define SI32_VREF_A_CONTROL_VREFEN_DISABLED_VALUE  0U
#define SI32_VREF_A_CONTROL_VREFEN_DISABLED_U32 \
   (SI32_VREF_A_CONTROL_VREFEN_DISABLED_VALUE << SI32_VREF_A_CONTROL_VREFEN_SHIFT)
// Enable the Voltage Reference.
#define SI32_VREF_A_CONTROL_VREFEN_ENABLED_VALUE  1U
#define SI32_VREF_A_CONTROL_VREFEN_ENABLED_U32 \
   (SI32_VREF_A_CONTROL_VREFEN_ENABLED_VALUE << SI32_VREF_A_CONTROL_VREFEN_SHIFT)



typedef struct SI32_VREF_A_Struct
{
   struct SI32_VREF_A_CONTROL_Struct               CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
   uint32_t                                        reserved1[4];
   uint32_t                                        reserved2[4];
   uint32_t                                        reserved3[4];
} SI32_VREF_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_VREF_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

