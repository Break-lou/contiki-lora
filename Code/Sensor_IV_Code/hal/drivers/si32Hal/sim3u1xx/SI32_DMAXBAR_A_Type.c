//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_DMAXBAR_A_Type.c
//
// This file applies to the SIM3U1XX_DMAXBAR_A module
//
// Script: 0.57
// HAL Source: 0.2
// Version: 12

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_DMAXBAR_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_DMAXBAR_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_DMAXBAR_A_initialize(
   SI32_DMAXBAR_A_Type * basePointer,
   // Write to DMAXBAR0 register.
   uint32_t dmaxbar0,
   // Write to DMAXBAR1 register.
   uint32_t dmaxbar1)
{
   //{{
   basePointer->DMAXBAR0.U32 = dmaxbar0;
   basePointer->DMAXBAR1.U32 = dmaxbar1;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMAXBAR_A_read_dmaxbar0
//
// Read DMAXBAR0 register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_DMAXBAR_A_read_dmaxbar0(
   SI32_DMAXBAR_A_Type * basePointer)
{
   //{{
   return basePointer->DMAXBAR0.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMAXBAR_A_write_dmaxbar0
//
// Write to DMAXBAR0 register.
//-----------------------------------------------------------------------------
void
_SI32_DMAXBAR_A_write_dmaxbar0(
   SI32_DMAXBAR_A_Type * basePointer,
   uint32_t dmaxbar0)
{
   //{{
   basePointer->DMAXBAR0.U32 = dmaxbar0;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMAXBAR_A_read_dmaxbar1
//
// Read DMAXBAR0 register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_DMAXBAR_A_read_dmaxbar1(
   SI32_DMAXBAR_A_Type * basePointer)
{
   //{{
   return basePointer->DMAXBAR1.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMAXBAR_A_write_dmaxbar1
//
// Write to DMAXBAR1 register.
//-----------------------------------------------------------------------------
void
_SI32_DMAXBAR_A_write_dmaxbar1(
   SI32_DMAXBAR_A_Type * basePointer,
   uint32_t dmaxbar1)
{
   //{{
   basePointer->DMAXBAR1.U32 = dmaxbar1;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMAXBAR_A_select_channel_peripheral
//
// Configures the DMA crossbar for the selected DMA channel and
// peripheral function.
//-----------------------------------------------------------------------------
uint32_t
_SI32_DMAXBAR_A_select_channel_peripheral(
   SI32_DMAXBAR_A_Type * basePointer,
   // See SI32_DMAXBAR_A_Support.h for encodings.
   SI32_DMAXBAR_CHNSEL_Enum_Type chnsel)
{
   //{{
   uint32_t shift = (chnsel & 0x70) >> 2;
   uint32_t mask = 0xF << shift;
   uint32_t value = (chnsel & 0xF) << shift;

   if (chnsel & 0x80)
   {
   //Channels 8-15 are in register 1
     basePointer->DMAXBAR1_CLR = mask;
     basePointer->DMAXBAR1_SET = value;
   } else {
   //Channels 0-7 are in register 0
     basePointer->DMAXBAR0_CLR = mask;
     basePointer->DMAXBAR0_SET = value;
   }
   return SI32_DMAXBAR_CHANNEL_OF(chnsel);
   //}}
}


//-eof--------------------------------------------------------------------------
