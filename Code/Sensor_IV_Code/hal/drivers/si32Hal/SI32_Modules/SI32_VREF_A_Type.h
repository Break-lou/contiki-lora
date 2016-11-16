//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_VREF_A_Type.h
//
// Script: 0.58
// HAL Source: 0.5
// Version: 1

#ifndef __SI32_VREF_A_TYPE_H__
#define __SI32_VREF_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_VREF_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_VREF_A_initialize(SI32_VREF_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Writes all VREF registers.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_VREF_A_initialize(SI32_VREF_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_VREF_A_initialize(basePointer, control)
#define SI32_VREF_A_initialize(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_VREF_A_write_control(SI32_VREF_A_Type* basePointer,
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
_SI32_VREF_A_write_control(SI32_VREF_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_VREF_A_write_control(basePointer, control)
#define SI32_VREF_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_VREF_A_read_control(SI32_VREF_A_Type* basePointer)
///
/// @brief
/// Reads CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_VREF_A_read_control(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_read_control(basePointer)
#define SI32_VREF_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_VREF_A_select_1p2_volts(SI32_VREF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VREF_A_select_1p2_volts(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_select_1p2_volts(basePointer)
#define SI32_VREF_A_select_1p2_volts(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VREF_A_CONTROL_VREF2X_MASK)


/// @fn _SI32_VREF_A_select_2p4_volts(SI32_VREF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VREF_A_select_2p4_volts(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_select_2p4_volts(basePointer)
#define SI32_VREF_A_select_2p4_volts(basePointer) \
   (basePointer->CONTROL_SET = SI32_VREF_A_CONTROL_VREF2X_MASK)


/// @fn _SI32_VREF_A_enable_temperature_sensor(SI32_VREF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VREF_A_enable_temperature_sensor(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_enable_temperature_sensor(basePointer)
#define SI32_VREF_A_enable_temperature_sensor(basePointer) \
   (basePointer->CONTROL_SET = SI32_VREF_A_CONTROL_TEMPEN_MASK)


/// @fn _SI32_VREF_A_disable_temperature_sensor(SI32_VREF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VREF_A_disable_temperature_sensor(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_disable_temperature_sensor(basePointer)
#define SI32_VREF_A_disable_temperature_sensor(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VREF_A_CONTROL_TEMPEN_MASK)


/// @fn _SI32_VREF_A_enable_voltage_reference(SI32_VREF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VREF_A_enable_voltage_reference(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_enable_voltage_reference(basePointer)
#define SI32_VREF_A_enable_voltage_reference(basePointer) \
   (basePointer->CONTROL_SET = SI32_VREF_A_CONTROL_VREFEN_MASK)


/// @fn _SI32_VREF_A_disable_voltage_reference(SI32_VREF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VREF_A_disable_voltage_reference(SI32_VREF_A_Type* /*basePointer*/);
///
/// @def SI32_VREF_A_disable_voltage_reference(basePointer)
#define SI32_VREF_A_disable_voltage_reference(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VREF_A_CONTROL_VREFEN_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_VREF_A_TYPE_H__

//-eof--------------------------------------------------------------------------
