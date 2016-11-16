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

#ifndef __SI32_EXTOSC_A_REGISTERS_H__
#define __SI32_EXTOSC_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_EXTOSC_A_CONTROL_Struct
{
   union
   {
      struct
      {
         // Frequency Control
         volatile uint32_t FREQCN: 3;
         // Oscillator Valid Flag
         volatile uint32_t OSCVLDF: 1;
         // Oscillator Mode
         volatile uint32_t OSCMD: 3;
                  uint32_t reserved0: 25;
      };
      volatile uint32_t U32;
   };
};

#define SI32_EXTOSC_A_CONTROL_FREQCN_MASK  0x00000007
#define SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT  0
// Set the external oscillator to range 0.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE0_VALUE  0
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE0_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE0_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 1.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE1_VALUE  1
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE1_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE1_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 2.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE2_VALUE  2
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE2_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE2_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 3.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE3_VALUE  3
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE3_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE3_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 4.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE4_VALUE  4
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE4_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE4_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 5.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE5_VALUE  5
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE5_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE5_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 6.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE6_VALUE  6
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE6_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE6_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)
// Set the external oscillator to range 7.
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE7_VALUE  7
#define SI32_EXTOSC_A_CONTROL_FREQCN_RANGE7_U32 \
   (SI32_EXTOSC_A_CONTROL_FREQCN_RANGE7_VALUE << SI32_EXTOSC_A_CONTROL_FREQCN_SHIFT)

#define SI32_EXTOSC_A_CONTROL_OSCVLDF_MASK  0x00000008
#define SI32_EXTOSC_A_CONTROL_OSCVLDF_SHIFT  3
// The external oscillator is unused or not yet stable.
#define SI32_EXTOSC_A_CONTROL_OSCVLDF_NOT_SET_VALUE  0
#define SI32_EXTOSC_A_CONTROL_OSCVLDF_NOT_SET_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCVLDF_NOT_SET_VALUE << SI32_EXTOSC_A_CONTROL_OSCVLDF_SHIFT)
// The external oscillator is running and stable.
#define SI32_EXTOSC_A_CONTROL_OSCVLDF_SET_VALUE  1
#define SI32_EXTOSC_A_CONTROL_OSCVLDF_SET_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCVLDF_SET_VALUE << SI32_EXTOSC_A_CONTROL_OSCVLDF_SHIFT)

#define SI32_EXTOSC_A_CONTROL_OSCMD_MASK  0x00000070
#define SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT  4
// External oscillator off.
#define SI32_EXTOSC_A_CONTROL_OSCMD_OFF_VALUE  0
#define SI32_EXTOSC_A_CONTROL_OSCMD_OFF_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_OFF_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)
// External CMOS clock mode.
#define SI32_EXTOSC_A_CONTROL_OSCMD_CMOS_VALUE  2
#define SI32_EXTOSC_A_CONTROL_OSCMD_CMOS_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_CMOS_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)
// External CMOS with divide by 2 stage.
#define SI32_EXTOSC_A_CONTROL_OSCMD_CMOSDIV2_VALUE  3
#define SI32_EXTOSC_A_CONTROL_OSCMD_CMOSDIV2_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_CMOSDIV2_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)
// RC oscillator mode with divide by 2 stage.
#define SI32_EXTOSC_A_CONTROL_OSCMD_RC_VALUE  4
#define SI32_EXTOSC_A_CONTROL_OSCMD_RC_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_RC_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)
// C oscillator mode with divide by 2 stage.
#define SI32_EXTOSC_A_CONTROL_OSCMD_C_VALUE  5
#define SI32_EXTOSC_A_CONTROL_OSCMD_C_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_C_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)
// Crystal oscillator mode.
#define SI32_EXTOSC_A_CONTROL_OSCMD_XTAL_VALUE  6
#define SI32_EXTOSC_A_CONTROL_OSCMD_XTAL_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_XTAL_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)
// Crystal oscillator mode with divide by 2 stage.
#define SI32_EXTOSC_A_CONTROL_OSCMD_XTALDIV2_VALUE  7
#define SI32_EXTOSC_A_CONTROL_OSCMD_XTALDIV2_U32 \
   (SI32_EXTOSC_A_CONTROL_OSCMD_XTALDIV2_VALUE << SI32_EXTOSC_A_CONTROL_OSCMD_SHIFT)



typedef struct SI32_EXTOSC_A_Struct
{
   struct SI32_EXTOSC_A_CONTROL_Struct             CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
} SI32_EXTOSC_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_EXTOSC_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

