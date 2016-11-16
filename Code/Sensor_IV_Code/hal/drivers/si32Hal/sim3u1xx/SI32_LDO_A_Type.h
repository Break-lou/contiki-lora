//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_LDO_A_Type.h
//
// This file applies to the SIM3U1XX_LDO_A module
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#ifndef __SI32_LDO_A_TYPE_H__
#define __SI32_LDO_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3U1XX_LDO_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_LDO_A_write_control(SI32_LDO_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Write to CONTROL register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_LDO_A_write_control(SI32_LDO_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_LDO_A_write_control(basePointer, control)
#define SI32_LDO_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_LDO_A_read_control(SI32_LDO_A_Type* basePointer)
///
/// @brief
/// Reads CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_LDO_A_read_control(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_read_control(basePointer)
#define SI32_LDO_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_LDO_A_select_high_bias(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_high_bias(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_high_bias(basePointer)
#define SI32_LDO_A_select_high_bias(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_LDOIBIAS_MASK)


/// @fn _SI32_LDO_A_select_low_bias(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_select_low_bias(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_select_low_bias(basePointer)
#define SI32_LDO_A_select_low_bias(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_LDOIBIAS_LOWBIAS_U32)


/// @fn _SI32_LDO_A_enable_bias(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_enable_bias(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_enable_bias(basePointer)
#define SI32_LDO_A_enable_bias(basePointer) \
   (basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_LDOAEN_ENABLE_U32)


/// @fn _SI32_LDO_A_disable_bias(SI32_LDO_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_LDO_A_disable_bias(SI32_LDO_A_Type* /*basePointer*/);
///
/// @def SI32_LDO_A_disable_bias(basePointer)
#define SI32_LDO_A_disable_bias(basePointer) \
   (basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_LDOAEN_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_LDO_A_TYPE_H__

//-eof--------------------------------------------------------------------------
