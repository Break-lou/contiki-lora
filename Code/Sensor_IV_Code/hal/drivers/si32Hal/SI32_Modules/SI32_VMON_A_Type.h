//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_VMON_A_Type.h
//
// Script: 0.58
// HAL Source: 0.2
// Version: 1

#ifndef __SI32_VMON_A_TYPE_H__
#define __SI32_VMON_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_VMON_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_VMON_A_initialize(SI32_VMON_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Writes all VMON registers.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///
void
_SI32_VMON_A_initialize(SI32_VMON_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_VMON_A_initialize(basePointer, control)
#define SI32_VMON_A_initialize(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_VMON_A_write_control(SI32_VMON_A_Type* basePointer,
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
_SI32_VMON_A_write_control(SI32_VMON_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_VMON_A_write_control(basePointer, control)
#define SI32_VMON_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_VMON_A_read_control(SI32_VMON_A_Type* basePointer)
///
/// @brief
/// Reads CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_VMON_A_read_control(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_read_control(basePointer)
#define SI32_VMON_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_VMON_A_enable_vreg_supply_monitor(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_enable_vreg_supply_monitor(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_enable_vreg_supply_monitor(basePointer)
#define SI32_VMON_A_enable_vreg_supply_monitor(basePointer) \
   (basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VREGINSEN_MASK)


/// @fn _SI32_VMON_A_disable_vreg_supply_monitor(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_disable_vreg_supply_monitor(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_disable_vreg_supply_monitor(basePointer)
#define SI32_VMON_A_disable_vreg_supply_monitor(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VREGINSEN_MASK)


/// @fn _SI32_VMON_A_is_vreg_low_interrupt_pending(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_VMON_A_is_vreg_low_interrupt_pending(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_is_vreg_low_interrupt_pending(basePointer)
#define SI32_VMON_A_is_vreg_low_interrupt_pending(basePointer) \
(!(bool)(basePointer->CONTROL.VREGINLI))


/// @fn _SI32_VMON_A_is_vdd_above_reset_threshold(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_VMON_A_is_vdd_above_reset_threshold(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_is_vdd_above_reset_threshold(basePointer)
#define SI32_VMON_A_is_vdd_above_reset_threshold(basePointer) \
((bool)(basePointer->CONTROL.VDDRSTF))


/// @fn _SI32_VMON_A_is_vdd_low_interrupt_pending(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_VMON_A_is_vdd_low_interrupt_pending(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_is_vdd_low_interrupt_pending(basePointer)
#define SI32_VMON_A_is_vdd_low_interrupt_pending(basePointer) \
(!(bool)(basePointer->CONTROL.VDDLI))


/// @fn _SI32_VMON_A_select_vdd_high_threshold(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_select_vdd_high_threshold(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_select_vdd_high_threshold(basePointer)
#define SI32_VMON_A_select_vdd_high_threshold(basePointer) \
   (basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VDDHITHEN_MASK)


/// @fn _SI32_VMON_A_select_vdd_standard_threshold(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_select_vdd_standard_threshold(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_select_vdd_standard_threshold(basePointer)
#define SI32_VMON_A_select_vdd_standard_threshold(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VDDHITHEN_MASK)


/// @fn _SI32_VMON_A_enable_vdd_low_interrupt(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_enable_vdd_low_interrupt(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_enable_vdd_low_interrupt(basePointer)
#define SI32_VMON_A_enable_vdd_low_interrupt(basePointer) \
   (basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VDDLIEN_MASK)


/// @fn _SI32_VMON_A_disable_vdd_low_interrupt(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_disable_vdd_low_interrupt(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_disable_vdd_low_interrupt(basePointer)
#define SI32_VMON_A_disable_vdd_low_interrupt(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VDDLIEN_MASK)


/// @fn _SI32_VMON_A_is_vdd_low_interrupt_enabled(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_VMON_A_is_vdd_low_interrupt_enabled(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_is_vdd_low_interrupt_enabled(basePointer)
#define SI32_VMON_A_is_vdd_low_interrupt_enabled(basePointer) \
((bool)(basePointer->CONTROL.VDDLIEN))


/// @fn _SI32_VMON_A_enable_vreg_low_interrupt(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_enable_vreg_low_interrupt(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_enable_vreg_low_interrupt(basePointer)
#define SI32_VMON_A_enable_vreg_low_interrupt(basePointer) \
   (basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VREGINLIEN_MASK)


/// @fn _SI32_VMON_A_disable_vreg_low_interrupt(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_disable_vreg_low_interrupt(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_disable_vreg_low_interrupt(basePointer)
#define SI32_VMON_A_disable_vreg_low_interrupt(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VREGINLIEN_MASK)


/// @fn _SI32_VMON_A_is_vreg_low_interrupt_enabled(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_VMON_A_is_vreg_low_interrupt_enabled(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_is_vreg_low_interrupt_enabled(basePointer)
#define SI32_VMON_A_is_vreg_low_interrupt_enabled(basePointer) \
((bool)(basePointer->CONTROL.VREGINLIEN))


/// @fn _SI32_VMON_A_enable_vdd_supply_monitor(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_enable_vdd_supply_monitor(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_enable_vdd_supply_monitor(basePointer)
#define SI32_VMON_A_enable_vdd_supply_monitor(basePointer) \
   (basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VMONEN_MASK)


/// @fn _SI32_VMON_A_disable_vdd_supply_monitor(SI32_VMON_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_VMON_A_disable_vdd_supply_monitor(SI32_VMON_A_Type* /*basePointer*/);
///
/// @def SI32_VMON_A_disable_vdd_supply_monitor(basePointer)
#define SI32_VMON_A_disable_vdd_supply_monitor(basePointer) \
   (basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VMONEN_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_VMON_A_TYPE_H__

//-eof--------------------------------------------------------------------------
