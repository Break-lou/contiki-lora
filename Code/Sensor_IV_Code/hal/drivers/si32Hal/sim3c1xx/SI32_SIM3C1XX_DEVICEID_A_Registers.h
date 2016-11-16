//-----------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//-----------------------------------------------------------------------------
//
// This file applies to the SIM3C1XX_DEVICEID_A module
//
// Script: 0.62
// Version: 1

#ifndef __SI32_DEVICEID_A_REGISTERS_H__
#define __SI32_DEVICEID_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_DEVICEID_A_DEVICEID0_Struct
{
   union
   {
      struct
      {
         // Revision ID
         volatile uint32_t REVID: 4;
                  uint32_t reserved0: 4;
         // Package ID
         volatile uint32_t PACKID: 24;
      };
      volatile uint32_t U32;
   };
};

#define SI32_DEVICEID_A_DEVICEID0_REVID_MASK  0x0000000F
#define SI32_DEVICEID_A_DEVICEID0_REVID_SHIFT  0
// Revision A.
#define SI32_DEVICEID_A_DEVICEID0_REVID_REVA_VALUE  0
#define SI32_DEVICEID_A_DEVICEID0_REVID_REVA_U32 \
   (SI32_DEVICEID_A_DEVICEID0_REVID_REVA_VALUE << SI32_DEVICEID_A_DEVICEID0_REVID_SHIFT)
// Revision B.
#define SI32_DEVICEID_A_DEVICEID0_REVID_REVB_VALUE  1
#define SI32_DEVICEID_A_DEVICEID0_REVID_REVB_U32 \
   (SI32_DEVICEID_A_DEVICEID0_REVID_REVB_VALUE << SI32_DEVICEID_A_DEVICEID0_REVID_SHIFT)

#define SI32_DEVICEID_A_DEVICEID0_PACKID_MASK  0xFFFFFF00
#define SI32_DEVICEID_A_DEVICEID0_PACKID_SHIFT  8



struct SI32_DEVICEID_A_DEVICEID1_Struct
{
   union
   {
      struct
      {
         // Device ID 1
         volatile uint32_t DEVICEID1_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_DEVICEID_A_DEVICEID1_DEVICEID1_MASK  0xFFFFFFFF
#define SI32_DEVICEID_A_DEVICEID1_DEVICEID1_SHIFT  0



struct SI32_DEVICEID_A_DEVICEID2_Struct
{
   union
   {
      struct
      {
         // Device ID 2
         volatile uint32_t DEVICEID2_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_DEVICEID_A_DEVICEID2_DEVICEID2_MASK  0xFFFFFFFF
#define SI32_DEVICEID_A_DEVICEID2_DEVICEID2_SHIFT  0



struct SI32_DEVICEID_A_DEVICEID3_Struct
{
   union
   {
      struct
      {
         // Device ID 3
         volatile uint32_t DEVICEID3_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_DEVICEID_A_DEVICEID3_DEVICEID3_MASK  0xFFFFFFFF
#define SI32_DEVICEID_A_DEVICEID3_DEVICEID3_SHIFT  0



typedef struct SI32_DEVICEID_A_Struct
{
   struct SI32_DEVICEID_A_DEVICEID0_Struct         DEVICEID0      ; // Base Address + 0x0
   uint32_t                                        reserved0;
   uint32_t                                        reserved1;
   uint32_t                                        reserved2;
   struct SI32_DEVICEID_A_DEVICEID1_Struct         DEVICEID1      ; // Base Address + 0x10
   uint32_t                                        reserved3;
   uint32_t                                        reserved4;
   uint32_t                                        reserved5;
   struct SI32_DEVICEID_A_DEVICEID2_Struct         DEVICEID2      ; // Base Address + 0x20
   uint32_t                                        reserved6;
   uint32_t                                        reserved7;
   uint32_t                                        reserved8;
   struct SI32_DEVICEID_A_DEVICEID3_Struct         DEVICEID3      ; // Base Address + 0x30
   uint32_t                                        reserved9;
   uint32_t                                        reserved10;
   uint32_t                                        reserved11;
} SI32_DEVICEID_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_DEVICEID_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

