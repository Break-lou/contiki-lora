//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_EMIF_A_Type.h
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#ifndef __SI32_EMIF_A_TYPE_H__
#define __SI32_EMIF_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_EMIF_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_EMIF_A_initialize(SI32_EMIF_A_Type* basePointer,
///      uint32_t control)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///  Value for the CONTROL register.
///
void
_SI32_EMIF_A_initialize(SI32_EMIF_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_EMIF_A_initialize(basePointer, control)
#define SI32_EMIF_A_initialize(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_EMIF_A_read_control(SI32_EMIF_A_Type* basePointer)
///
/// @brief
/// Read CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_EMIF_A_read_control(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_read_control(basePointer)
#define SI32_EMIF_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_EMIF_A_write_control(SI32_EMIF_A_Type* basePointer,
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
_SI32_EMIF_A_write_control(SI32_EMIF_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_EMIF_A_write_control(basePointer, control)
#define SI32_EMIF_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_EMIF_A_disable_interface_0(SI32_EMIF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_EMIF_A_disable_interface_0(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_disable_interface_0(basePointer)
#define SI32_EMIF_A_disable_interface_0(basePointer) \
   (basePointer->CONTROL_CLR = SI32_EMIF_A_CONTROL_IF0EN_MASK)


/// @fn _SI32_EMIF_A_enable_interface_0(SI32_EMIF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_EMIF_A_enable_interface_0(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_enable_interface_0(basePointer)
#define SI32_EMIF_A_enable_interface_0(basePointer) \
   (basePointer->CONTROL_SET = SI32_EMIF_A_CONTROL_IF0EN_MASK)


/// @fn _SI32_EMIF_A_disable_interface_1(SI32_EMIF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_EMIF_A_disable_interface_1(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_disable_interface_1(basePointer)
#define SI32_EMIF_A_disable_interface_1(basePointer) \
   (basePointer->CONTROL_CLR = SI32_EMIF_A_CONTROL_IF1EN_MASK)


/// @fn _SI32_EMIF_A_enable_interface_1(SI32_EMIF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_EMIF_A_enable_interface_1(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_enable_interface_1(basePointer)
#define SI32_EMIF_A_enable_interface_1(basePointer) \
   (basePointer->CONTROL_SET = SI32_EMIF_A_CONTROL_IF1EN_MASK)


/// @fn _SI32_EMIF_A_is_interface_0_active(SI32_EMIF_A_Type* basePointer)
///
/// @return
///  Returns TRUE if IF0 active, otherwise returns FALSE.
///
/// @param[in]
///  basePointer
///
bool
_SI32_EMIF_A_is_interface_0_active(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_is_interface_0_active(basePointer)
#define SI32_EMIF_A_is_interface_0_active(basePointer) \
((bool)basePointer->CONTROL.IF0EN)


/// @fn _SI32_EMIF_A_is_interface_1_active(SI32_EMIF_A_Type* basePointer)
///
/// @return
///  Returns TRUE if IF1 active, otherwise returns FALSE.
///
/// @param[in]
///  basePointer
///
bool
_SI32_EMIF_A_is_interface_1_active(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_is_interface_1_active(basePointer)
#define SI32_EMIF_A_is_interface_1_active(basePointer) \
((bool)basePointer->CONTROL.IF1EN)


/// @fn _SI32_EMIF_A_enable_off_state(SI32_EMIF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_EMIF_A_enable_off_state(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_enable_off_state(basePointer)
#define SI32_EMIF_A_enable_off_state(basePointer) \
   (basePointer->CONTROL_SET = SI32_EMIF_A_CONTROL_OFFSTEN_MASK)


/// @fn _SI32_EMIF_A_disable_off_state(SI32_EMIF_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_EMIF_A_disable_off_state(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_disable_off_state(basePointer)
#define SI32_EMIF_A_disable_off_state(basePointer) \
   (basePointer->CONTROL_CLR = SI32_EMIF_A_CONTROL_OFFSTEN_MASK)


/// @fn _SI32_EMIF_A_is_off(SI32_EMIF_A_Type* basePointer)
///
/// @return
///  Returns TRUE if EMIF in off state, otherwise returns FALSE.
///
/// @param[in]
///  basePointer
///
bool
_SI32_EMIF_A_is_off(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_is_off(basePointer)
#define SI32_EMIF_A_is_off(basePointer) \
((bool)(basePointer->STATUS.OFFSTS))


/// @fn _SI32_EMIF_A_is_idle(SI32_EMIF_A_Type* basePointer)
///
/// @return
///  Return TRUE if EMIF idle, otherwise returns FALSE.
///
/// @param[in]
///  basePointer
///
bool
_SI32_EMIF_A_is_idle(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_is_idle(basePointer)
#define SI32_EMIF_A_is_idle(basePointer) \
((bool)(basePointer->STATUS.IDLESTS))


/// @fn _SI32_EMIF_A_is_running(SI32_EMIF_A_Type* basePointer)
///
/// @return
///  Returns TRUE if EMIF active, otherwise returns FALSE.
///
/// @param[in]
///  basePointer
///
bool
_SI32_EMIF_A_is_running(SI32_EMIF_A_Type* /*basePointer*/);
///
/// @def SI32_EMIF_A_is_running(basePointer)
#define SI32_EMIF_A_is_running(basePointer) \
   _SI32_EMIF_A_is_running(basePointer) 



#ifdef __cplusplus
}
#endif

#endif // __SI32_EMIF_A_TYPE_H__

//-eof--------------------------------------------------------------------------
