//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_DMAXBAR_A_Type.h
//
// Script: 0.57
// HAL Source: 0.2
// Version: 1

#ifndef __SI32_DMAXBAR_A_TYPE_H__
#define __SI32_DMAXBAR_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3U1XX_DMAXBAR_A_Registers.h"
#include "SI32_DMAXBAR_A_Support.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_DMAXBAR_A_initialize(SI32_DMAXBAR_A_Type* basePointer,
///      uint32_t dmaxbar0,
///      uint32_t dmaxbar1)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  dmaxbar0
///  Valid range is 32 bits.
///  Write to DMAXBAR0 register.
///
/// @param[in]
///  dmaxbar1
///  Valid range is 32 bits.
///  Write to DMAXBAR1 register.
///
void
_SI32_DMAXBAR_A_initialize(SI32_DMAXBAR_A_Type* /*basePointer*/,
   uint32_t, /*dmaxbar0*/
   uint32_t /*dmaxbar1*/);
///
/// @def SI32_DMAXBAR_A_initialize(basePointer, dmaxbar0, dmaxbar1)
#define SI32_DMAXBAR_A_initialize(basePointer, dmaxbar0, dmaxbar1) do{  \
   basePointer->DMAXBAR0.U32 = dmaxbar0;\
   basePointer->DMAXBAR1.U32 = dmaxbar1;\
} while(0)


/// @fn _SI32_DMAXBAR_A_read_dmaxbar0(SI32_DMAXBAR_A_Type* basePointer)
///
/// @brief
/// Read DMAXBAR0 register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_DMAXBAR_A_read_dmaxbar0(SI32_DMAXBAR_A_Type* /*basePointer*/);
///
/// @def SI32_DMAXBAR_A_read_dmaxbar0(basePointer)
#define SI32_DMAXBAR_A_read_dmaxbar0(basePointer) \
(basePointer->DMAXBAR0.U32)


/// @fn _SI32_DMAXBAR_A_write_dmaxbar0(SI32_DMAXBAR_A_Type* basePointer,
///      uint32_t dmaxbar0)
///
/// @brief
/// Write to DMAXBAR0 register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  dmaxbar0
///  Valid range is 32 bits.
///
void
_SI32_DMAXBAR_A_write_dmaxbar0(SI32_DMAXBAR_A_Type* /*basePointer*/,
   uint32_t /*dmaxbar0*/);
///
/// @def SI32_DMAXBAR_A_write_dmaxbar0(basePointer, dmaxbar0)
#define SI32_DMAXBAR_A_write_dmaxbar0(basePointer, dmaxbar0) \
   (basePointer->DMAXBAR0.U32 = dmaxbar0)


/// @fn _SI32_DMAXBAR_A_read_dmaxbar1(SI32_DMAXBAR_A_Type* basePointer)
///
/// @brief
/// Read DMAXBAR0 register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_DMAXBAR_A_read_dmaxbar1(SI32_DMAXBAR_A_Type* /*basePointer*/);
///
/// @def SI32_DMAXBAR_A_read_dmaxbar1(basePointer)
#define SI32_DMAXBAR_A_read_dmaxbar1(basePointer) \
(basePointer->DMAXBAR1.U32)


/// @fn _SI32_DMAXBAR_A_write_dmaxbar1(SI32_DMAXBAR_A_Type* basePointer,
///      uint32_t dmaxbar1)
///
/// @brief
/// Write to DMAXBAR1 register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  dmaxbar1
///  Valid range is 32 bits.
///
void
_SI32_DMAXBAR_A_write_dmaxbar1(SI32_DMAXBAR_A_Type* /*basePointer*/,
   uint32_t /*dmaxbar1*/);
///
/// @def SI32_DMAXBAR_A_write_dmaxbar1(basePointer, dmaxbar1)
#define SI32_DMAXBAR_A_write_dmaxbar1(basePointer, dmaxbar1) \
   (basePointer->DMAXBAR1.U32 = dmaxbar1)


/// @fn _SI32_DMAXBAR_A_select_channel_peripheral(SI32_DMAXBAR_A_Type* basePointer,
///      SI32_DMAXBAR_CHNSEL_Enum_Type chnsel)
///
/// @brief
/// Configures the DMA crossbar for the selected DMA channel and
/// peripheral function.
///
/// @return
///  The selected DMA channel.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  chnsel
///  See SI32_DMAXBAR_A_Support.h for encodings.
///
uint32_t
_SI32_DMAXBAR_A_select_channel_peripheral(SI32_DMAXBAR_A_Type* /*basePointer*/,
   SI32_DMAXBAR_CHNSEL_Enum_Type /*chnsel*/);
///
/// @def SI32_DMAXBAR_A_select_channel_peripheral(basePointer, chnsel)
#define SI32_DMAXBAR_A_select_channel_peripheral(basePointer, chnsel) \
   _SI32_DMAXBAR_A_select_channel_peripheral(basePointer, chnsel) 



#ifdef __cplusplus
}
#endif

#endif // __SI32_DMAXBAR_A_TYPE_H__

//-eof--------------------------------------------------------------------------
