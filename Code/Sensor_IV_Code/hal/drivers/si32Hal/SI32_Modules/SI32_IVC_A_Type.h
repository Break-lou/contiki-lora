//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_IVC_A_Type.h
//
// Script: 0.58
// HAL Source: 0.3
// Version: 1

#ifndef __SI32_IVC_A_TYPE_H__
#define __SI32_IVC_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_IVC_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_IVC_A_initialize(SI32_IVC_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Writes all IVC registers.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_IVC_A_initialize(SI32_IVC_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_IVC_A_initialize(basePointer, control)
#define SI32_IVC_A_initialize(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_IVC_A_write_control(SI32_IVC_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Writes CONTROL register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_IVC_A_write_control(SI32_IVC_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_IVC_A_write_control(basePointer, control)
#define SI32_IVC_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_IVC_A_read_control(SI32_IVC_A_Type* basePointer)
///
/// @brief
/// Reads CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_IVC_A_read_control(SI32_IVC_A_Type* /*basePointer*/);
///
/// @def SI32_IVC_A_read_control(basePointer)
#define SI32_IVC_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_IVC_A_select_channel_0_range(SI32_IVC_A_Type* basePointer,
///      uint32_t range)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  range
///  Valid range is 1 to 6.
///  Desired range in mA from 1 to 6 (1 = 1 mA range, ..., 6 = 6 mA range).
///
void
_SI32_IVC_A_select_channel_0_range(SI32_IVC_A_Type* /*basePointer*/,
   uint32_t /*range*/);
///
/// @def SI32_IVC_A_select_channel_0_range(basePointer, range)
#define SI32_IVC_A_select_channel_0_range(basePointer, range) \
   (basePointer->CONTROL.IN0RANGE = 6 - range)


/// @fn _SI32_IVC_A_select_channel_1_range(SI32_IVC_A_Type* basePointer,
///      uint32_t range)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  range
///  Valid range is 1 to 6.
///  Desired range in mA from 1 to 6 (1 = 1 mA range, ..., 6 = 6 mA range).
///
void
_SI32_IVC_A_select_channel_1_range(SI32_IVC_A_Type* /*basePointer*/,
   uint32_t /*range*/);
///
/// @def SI32_IVC_A_select_channel_1_range(basePointer, range)
#define SI32_IVC_A_select_channel_1_range(basePointer, range) \
   (basePointer->CONTROL.IN1RANGE = 6 - range)


/// @fn _SI32_IVC_A_enable_channel_0(SI32_IVC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_IVC_A_enable_channel_0(SI32_IVC_A_Type* /*basePointer*/);
///
/// @def SI32_IVC_A_enable_channel_0(basePointer)
#define SI32_IVC_A_enable_channel_0(basePointer) \
   (basePointer->CONTROL_SET = SI32_IVC_A_CONTROL_C0EN_ENABLED_U32)


/// @fn _SI32_IVC_A_disable_channel_0(SI32_IVC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_IVC_A_disable_channel_0(SI32_IVC_A_Type* /*basePointer*/);
///
/// @def SI32_IVC_A_disable_channel_0(basePointer)
#define SI32_IVC_A_disable_channel_0(basePointer) \
   (basePointer->CONTROL_CLR = SI32_IVC_A_CONTROL_C0EN_MASK)


/// @fn _SI32_IVC_A_enable_channel_1(SI32_IVC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_IVC_A_enable_channel_1(SI32_IVC_A_Type* /*basePointer*/);
///
/// @def SI32_IVC_A_enable_channel_1(basePointer)
#define SI32_IVC_A_enable_channel_1(basePointer) \
   (basePointer->CONTROL_SET = SI32_IVC_A_CONTROL_C1EN_ENABLED_U32)


/// @fn _SI32_IVC_A_disable_channel_1(SI32_IVC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_IVC_A_disable_channel_1(SI32_IVC_A_Type* /*basePointer*/);
///
/// @def SI32_IVC_A_disable_channel_1(basePointer)
#define SI32_IVC_A_disable_channel_1(basePointer) \
   (basePointer->CONTROL_CLR = SI32_IVC_A_CONTROL_C1EN_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_IVC_A_TYPE_H__

//-eof--------------------------------------------------------------------------
