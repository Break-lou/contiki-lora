//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_DMADESC_A_Type.c
//
// Script: 0.58
// HAL Source: 0.1
// Version: 4

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_DMADESC_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_DMADESC_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_DMADESC_A_initialize(
   SI32_DMADESC_A_Type * basePointer,
   // Source data end pointer.
   uint32_t srcend,
   // Destination data end pointer.
   uint32_t dstend,
   // Transfer configuration value. See SI32_DMADESC_A_Support.h for values.
   uint32_t config)
{
   //{{
   (basePointer)->SRCEND.U32 = srcend;
   (basePointer)->DSTEND.U32 = dstend;
   (basePointer)->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMADESC_A_configure
//
//-----------------------------------------------------------------------------
void
_SI32_DMADESC_A_configure(
   SI32_DMADESC_A_Type * basePointer,
   // Source data pointer.
   void volatile * srcPointer,
   // Destination data pointer.
   void volatile * dstPointer,
   // Transfer count. Units are in words, half words or bytes depending on
   // the config parameter.
   uint32_t count,
   // Transfer configuration value. See SI32_DMADESC_A_Support.h for values.
   uint32_t config)
{
   assert(count < 512);   // count < 2^9
   //{{
   uint32_t size;

   // Adjust the transfer count
   count -= 1;
   
   // Fill in channel structure
   basePointer->SRCEND.U32 = (uint32_t)srcPointer;
   basePointer->DSTEND.U32 = (uint32_t)dstPointer;
   basePointer->CONFIG.U32 = config;
   basePointer->CONFIG.NCOUNT = count;

   // Adjust source data pointer
   size = basePointer->CONFIG.SRCAIMD;
   if (size != SI32_DMADESC_A_CONFIG_SRCAIMD_NO_INCREMENT_VALUE)
   {
      basePointer->SRCEND.U32 += (count << size);
   }

   // Adjust destination data pointer
   size = basePointer->CONFIG.DSTAIMD;
   if (size != SI32_DMADESC_A_CONFIG_DSTAIMD_NO_INCREMENT_VALUE)
   {
      basePointer->DSTEND.U32 += (count << size);
   }
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMADESC_A_configure_memory_scatter_gather
//
//-----------------------------------------------------------------------------
void
_SI32_DMADESC_A_configure_memory_scatter_gather(
   SI32_DMADESC_A_Type * basePointer,
   // Pointer to an array of DMA descriptors for the scatter-gather
   // transfers.
   SI32_DMADESC_A_Type * descPointer,
   // Number of scatter-gather descriptors.
   uint32_t descCount)
{
   assert(descCount < 128);   // descCount < 2^7
   //{{
   (basePointer)->SRCEND.U32 = ((uint32_t)&descPointer[descCount]) - sizeof(uint32_t);
   (basePointer)->DSTEND.U32 = ((uint32_t)&basePointer[SI32_DMADESC_ALT_STRIDE+1]) - sizeof(uint32_t);
   (basePointer)->CONFIG.U32 = SI32_DMADESC_A_CONFIG_MEMORY_SG;
   (basePointer)->CONFIG.NCOUNT = (descCount * 4) - 1;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_DMADESC_A_configure_peripheral_scatter_gather
//
//-----------------------------------------------------------------------------
void
_SI32_DMADESC_A_configure_peripheral_scatter_gather(
   SI32_DMADESC_A_Type * basePointer,
   // Pointer to an array of DMA descriptors for the scatter-gather
   // transfers.
   SI32_DMADESC_A_Type * descPointer,
   // Number of scatter-gather descriptors.
   uint32_t descCount)
{
   assert(descCount < 128);   // descCount < 2^7
   //{{
   (basePointer)->SRCEND.U32 = ((uint32_t)&descPointer[descCount]) - sizeof(uint32_t);
   (basePointer)->DSTEND.U32 = ((uint32_t)&basePointer[SI32_DMADESC_ALT_STRIDE+1]) - sizeof(uint32_t);
   (basePointer)->CONFIG.U32 = SI32_DMADESC_A_CONFIG_PERIPHERAL_SG;
   (basePointer)->CONFIG.NCOUNT = (descCount * 4) - 1;
   //}}
}


//-eof--------------------------------------------------------------------------
