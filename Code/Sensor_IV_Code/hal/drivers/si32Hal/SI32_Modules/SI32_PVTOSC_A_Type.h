//-----------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/License_Agreement.htm
// 
// Silicon Laboratories - Initial API and implementation
//-----------------------------------------------------------------------------
/// @file SI32_PVTOSC_A_Type.h
//
// Script: 0.62
// HAL Source: 0.3
// Version: 1

#ifndef __SI32_PVTOSC_A_TYPE_H__
#define __SI32_PVTOSC_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_PVTOSC_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_PVTOSC_A_initialize(SI32_PVTOSC_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Writes all PVTOSC registers.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_PVTOSC_A_initialize(SI32_PVTOSC_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_PVTOSC_A_initialize(basePointer, control)
#define SI32_PVTOSC_A_initialize(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_PVTOSC_A_write_control(SI32_PVTOSC_A_Type* basePointer,
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
_SI32_PVTOSC_A_write_control(SI32_PVTOSC_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_PVTOSC_A_write_control(basePointer, control)
#define SI32_PVTOSC_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_PVTOSC_A_read_control(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Reads CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_PVTOSC_A_read_control(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_read_control(basePointer)
#define SI32_PVTOSC_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_PVTOSC_A_enable_digital_ldo_oscillator(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Enables the digital LDO PVT oscillator.
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_enable_digital_ldo_oscillator(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_enable_digital_ldo_oscillator(basePointer)
#define SI32_PVTOSC_A_enable_digital_ldo_oscillator(basePointer) \
   (basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_DIGOSCEN_MASK)


/// @fn _SI32_PVTOSC_A_disable_digital_ldo_oscillator(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Disables the digital LDO PVT oscillator.
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_disable_digital_ldo_oscillator(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_disable_digital_ldo_oscillator(basePointer)
#define SI32_PVTOSC_A_disable_digital_ldo_oscillator(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_DIGOSCEN_MASK)


/// @fn _SI32_PVTOSC_A_enable_memory_ldo_oscillator(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Enables the memory LDO PVT oscillator.
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_enable_memory_ldo_oscillator(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_enable_memory_ldo_oscillator(basePointer)
#define SI32_PVTOSC_A_enable_memory_ldo_oscillator(basePointer) \
   (basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_MEMOSCEN_MASK)


/// @fn _SI32_PVTOSC_A_disable_memory_ldo_oscillator(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Disables the memory LDO PVT oscillator.
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_disable_memory_ldo_oscillator(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_disable_memory_ldo_oscillator(basePointer)
#define SI32_PVTOSC_A_disable_memory_ldo_oscillator(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_MEMOSCEN_MASK)


/// @fn _SI32_PVTOSC_A_select_digital_ldo_oscillator_slow_mode(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Selects digital LDO PVT oscillator slow mode (~50 kHz).
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_select_digital_ldo_oscillator_slow_mode(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_select_digital_ldo_oscillator_slow_mode(basePointer)
#define SI32_PVTOSC_A_select_digital_ldo_oscillator_slow_mode(basePointer) \
   (basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_DIGOSCMD_MASK)


/// @fn _SI32_PVTOSC_A_select_digital_ldo_oscillator_fast_mode(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Selects digital LDO PVT oscillator fast mode (~6.4 MHz).
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_select_digital_ldo_oscillator_fast_mode(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_select_digital_ldo_oscillator_fast_mode(basePointer)
#define SI32_PVTOSC_A_select_digital_ldo_oscillator_fast_mode(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_DIGOSCMD_MASK)


/// @fn _SI32_PVTOSC_A_select_memory_ldo_oscillator_slow_mode(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Selects memory LDO PVT oscillator slow mode (~50 kHz).
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_select_memory_ldo_oscillator_slow_mode(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_select_memory_ldo_oscillator_slow_mode(basePointer)
#define SI32_PVTOSC_A_select_memory_ldo_oscillator_slow_mode(basePointer) \
   (basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_MEMOSCMD_MASK)


/// @fn _SI32_PVTOSC_A_select_memory_ldo_oscillator_fast_mode(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Selects memory LDO PVT oscillator fast mode (~6.4 MHz).
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_select_memory_ldo_oscillator_fast_mode(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_select_memory_ldo_oscillator_fast_mode(basePointer)
#define SI32_PVTOSC_A_select_memory_ldo_oscillator_fast_mode(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_MEMOSCMD_MASK)


/// @fn _SI32_PVTOSC_A_select_divider_source_apb_clock(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Selects APB clock as the input to the clock dividers.
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_select_divider_source_apb_clock(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_select_divider_source_apb_clock(basePointer)
#define SI32_PVTOSC_A_select_divider_source_apb_clock(basePointer) \
   (basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_CLKSEL_MASK)


/// @fn _SI32_PVTOSC_A_select_divider_source_oscillators(SI32_PVTOSC_A_Type* basePointer)
///
/// @brief
/// Selects PVT oscillators as the inputs to the clock dividers.
///
/// @param[in]
///  basePointer
///
void
_SI32_PVTOSC_A_select_divider_source_oscillators(SI32_PVTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_PVTOSC_A_select_divider_source_oscillators(basePointer)
#define SI32_PVTOSC_A_select_divider_source_oscillators(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_CLKSEL_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_PVTOSC_A_TYPE_H__

//-eof--------------------------------------------------------------------------
