//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_DMADESC_A_Type.h
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#ifndef __SI32_DMADESC_A_TYPE_H__
#define __SI32_DMADESC_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_DMADESC_A_Registers.h"

// support definitions
#include "SI32_DMADESC_A_Support.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_DMADESC_A_initialize(SI32_DMADESC_A_Type* basePointer,
///      uint32_t srcend,
///      uint32_t dstend,
///      uint32_t config)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  srcend
///  Valid range is 32 bits.
///  Source data end pointer.
///
/// @param[in]
///  dstend
///  Valid range is 32 bits.
///  Destination data end pointer.
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///  Transfer configuration value. See SI32_DMADESC_A_Support.h for values.
///
void
_SI32_DMADESC_A_initialize(SI32_DMADESC_A_Type* /*basePointer*/,
   uint32_t, /*srcend*/
   uint32_t, /*dstend*/
   uint32_t /*config*/);
///
/// @def SI32_DMADESC_A_initialize(basePointer, srcend, dstend, config)
#define SI32_DMADESC_A_initialize(basePointer, srcend, dstend, config) do{  \
   (basePointer)->SRCEND.U32 = srcend;\
   (basePointer)->DSTEND.U32 = dstend;\
   (basePointer)->CONFIG.U32 = config;\
} while(0)


/// @fn _SI32_DMADESC_A_configure(SI32_DMADESC_A_Type* basePointer,
///      void volatile * srcPointer,
///      void volatile * dstPointer,
///      uint32_t count,
///      uint32_t config)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  srcPointer
///  Source data pointer.
///
/// @param[in]
///  dstPointer
///  Destination data pointer.
///
/// @param[in]
///  count
///  Valid range is 9 bits.
///  Transfer count. Units are in words, half words or bytes depending on
///  the config parameter.
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///  Transfer configuration value. See SI32_DMADESC_A_Support.h for values.
///
void
_SI32_DMADESC_A_configure(SI32_DMADESC_A_Type* /*basePointer*/,
   void volatile *, /*srcPointer*/
   void volatile *, /*dstPointer*/
   uint32_t, /*count*/
   uint32_t /*config*/);
///
/// @def SI32_DMADESC_A_configure(basePointer, srcPointer, dstPointer, count, config)
#define SI32_DMADESC_A_configure(basePointer, srcPointer, dstPointer, count, config) \
   _SI32_DMADESC_A_configure(basePointer, srcPointer, dstPointer, count, config)


/// @fn _SI32_DMADESC_A_configure_memory_scatter_gather(SI32_DMADESC_A_Type* basePointer,
///      SI32_DMADESC_A_Type * descPointer,
///      uint32_t descCount)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  descPointer
///  Pointer to an array of DMA descriptors for the scatter-gather
///  transfers.
///
/// @param[in]
///  descCount
///  Valid range is 7 bits.
///  Number of scatter-gather descriptors.
///
void
_SI32_DMADESC_A_configure_memory_scatter_gather(SI32_DMADESC_A_Type* /*basePointer*/,
   SI32_DMADESC_A_Type *, /*descPointer*/
   uint32_t /*descCount*/);
///
/// @def SI32_DMADESC_A_configure_memory_scatter_gather(basePointer, descPointer, descCount)
#define SI32_DMADESC_A_configure_memory_scatter_gather(basePointer, descPointer, descCount) \
   _SI32_DMADESC_A_configure_memory_scatter_gather(basePointer, descPointer, descCount)


/// @fn _SI32_DMADESC_A_configure_peripheral_scatter_gather(SI32_DMADESC_A_Type* basePointer,
///      SI32_DMADESC_A_Type * descPointer,
///      uint32_t descCount)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  descPointer
///  Pointer to an array of DMA descriptors for the scatter-gather
///  transfers.
///
/// @param[in]
///  descCount
///  Valid range is 7 bits.
///  Number of scatter-gather descriptors.
///
void
_SI32_DMADESC_A_configure_peripheral_scatter_gather(SI32_DMADESC_A_Type* /*basePointer*/,
   SI32_DMADESC_A_Type *, /*descPointer*/
   uint32_t /*descCount*/);
///
/// @def SI32_DMADESC_A_configure_peripheral_scatter_gather(basePointer, descPointer, descCount)
#define SI32_DMADESC_A_configure_peripheral_scatter_gather(basePointer, descPointer, descCount) \
   _SI32_DMADESC_A_configure_peripheral_scatter_gather(basePointer, descPointer, descCount)


#ifdef __cplusplus
}
#endif

#endif // __SI32_DMADESC_A_TYPE_H__

//-eof--------------------------------------------------------------------------
