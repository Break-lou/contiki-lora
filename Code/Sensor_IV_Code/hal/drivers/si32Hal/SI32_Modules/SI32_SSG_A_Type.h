//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_SSG_A_Type.h
//
// Script: 0.58
// HAL Source: 0.4
// Version: 1

#ifndef __SI32_SSG_A_TYPE_H__
#define __SI32_SSG_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SSG_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_SSG_A_initialize(SI32_SSG_A_Type* basePointer,
///      uint32_t config,
///      uint32_t control)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///  Write to CONFIG register.
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///  Write to CONTROL register.
///
void
_SI32_SSG_A_initialize(SI32_SSG_A_Type* /*basePointer*/,
   uint32_t, /*config*/
   uint32_t /*control*/);
///
/// @def SI32_SSG_A_initialize(basePointer, config, control)
#define SI32_SSG_A_initialize(basePointer, config, control) do{  \
   basePointer->CONFIG.U32 = config;\
   basePointer->CONTROL.U32 = control;\
} while(0)


/// @fn _SI32_SSG_A_write_config(SI32_SSG_A_Type* basePointer,
///      uint32_t config)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///  Write to CONFIG register.
///
void
_SI32_SSG_A_write_config(SI32_SSG_A_Type* /*basePointer*/,
   uint32_t /*config*/);
///
/// @def SI32_SSG_A_write_config(basePointer, config)
#define SI32_SSG_A_write_config(basePointer, config) \
   (basePointer->CONFIG.U32 = config)


/// @fn _SI32_SSG_A_read_config(SI32_SSG_A_Type* basePointer)
///
/// @return
///  Read CONFIG register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_SSG_A_read_config(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_read_config(basePointer)
#define SI32_SSG_A_read_config(basePointer) \
(basePointer->CONFIG.U32)


/// @fn _SI32_SSG_A_set_conversion_count(SI32_SSG_A_Type* basePointer,
///      uint32_t count)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  count
///  Valid range is 12 bits.
///  Desired count.
///
void
_SI32_SSG_A_set_conversion_count(SI32_SSG_A_Type* /*basePointer*/,
   uint32_t /*count*/);
///
/// @def SI32_SSG_A_set_conversion_count(basePointer, count)
#define SI32_SSG_A_set_conversion_count(basePointer, count) \
   (basePointer->CONFIG.COUNT = count)


/// @fn _SI32_SSG_A_select_speed_normal(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_select_speed_normal(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_select_speed_normal(basePointer)
#define SI32_SSG_A_select_speed_normal(basePointer) \
   (basePointer->CONFIG.SSEL = SI32_SSG_A_CONFIG_SSEL_NORMAL_VALUE)


/// @fn _SI32_SSG_A_select_speed_double(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_select_speed_double(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_select_speed_double(basePointer)
#define SI32_SSG_A_select_speed_double(basePointer) \
   (basePointer->CONFIG.SSEL = SI32_SSG_A_CONFIG_SSEL_DOUBLE_VALUE)


/// @fn _SI32_SSG_A_start_phase_generator_freerun(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_start_phase_generator_freerun(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_start_phase_generator_freerun(basePointer)
#define SI32_SSG_A_start_phase_generator_freerun(basePointer) \
   (basePointer->CONFIG.PHGFREN = SI32_SSG_A_CONFIG_PHGFREN_ENABLED_VALUE)


/// @fn _SI32_SSG_A_stop_phase_generator_freerun(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_stop_phase_generator_freerun(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_stop_phase_generator_freerun(basePointer)
#define SI32_SSG_A_stop_phase_generator_freerun(basePointer) \
   (basePointer->CONFIG.PHGFREN = SI32_SSG_A_CONFIG_PHGFREN_DISABLED_VALUE)


/// @fn _SI32_SSG_A_start_pulse_generator_freerun(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_start_pulse_generator_freerun(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_start_pulse_generator_freerun(basePointer)
#define SI32_SSG_A_start_pulse_generator_freerun(basePointer) \
   (basePointer->CONFIG.PUGFREN = SI32_SSG_A_CONFIG_PUGFREN_ENABLED_VALUE)


/// @fn _SI32_SSG_A_stop_pulse_generator_freerun(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_stop_pulse_generator_freerun(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_stop_pulse_generator_freerun(basePointer)
#define SI32_SSG_A_stop_pulse_generator_freerun(basePointer) \
   (basePointer->CONFIG.PUGFREN = SI32_SSG_A_CONFIG_PUGFREN_DISABLED_VALUE)


/// @fn _SI32_SSG_A_write_control(SI32_SSG_A_Type* basePointer,
///      uint32_t control)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///  Write to CONTROL register.
///
void
_SI32_SSG_A_write_control(SI32_SSG_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_SSG_A_write_control(basePointer, control)
#define SI32_SSG_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_SSG_A_read_control(SI32_SSG_A_Type* basePointer)
///
/// @return
///  Read CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_SSG_A_read_control(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_read_control(basePointer)
#define SI32_SSG_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_SSG_A_enable_ex0_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex0_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex0_output_inversion(basePointer)
#define SI32_SSG_A_enable_ex0_output_inversion(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX0INVEN_MASK)


/// @fn _SI32_SSG_A_disable_ex0_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex0_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex0_output_inversion(basePointer)
#define SI32_SSG_A_disable_ex0_output_inversion(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX0INVEN_MASK)


/// @fn _SI32_SSG_A_enable_ex1_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex1_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex1_output_inversion(basePointer)
#define SI32_SSG_A_enable_ex1_output_inversion(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX1INVEN_MASK)


/// @fn _SI32_SSG_A_disable_ex1_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex1_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex1_output_inversion(basePointer)
#define SI32_SSG_A_disable_ex1_output_inversion(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX1INVEN_MASK)


/// @fn _SI32_SSG_A_enable_ex2_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex2_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex2_output_inversion(basePointer)
#define SI32_SSG_A_enable_ex2_output_inversion(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX2INVEN_MASK)


/// @fn _SI32_SSG_A_disable_ex2_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex2_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex2_output_inversion(basePointer)
#define SI32_SSG_A_disable_ex2_output_inversion(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX2INVEN_MASK)


/// @fn _SI32_SSG_A_enable_ex3_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex3_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex3_output_inversion(basePointer)
#define SI32_SSG_A_enable_ex3_output_inversion(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX3INVEN_MASK)


/// @fn _SI32_SSG_A_disable_ex3_output_inversion(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex3_output_inversion(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex3_output_inversion(basePointer)
#define SI32_SSG_A_disable_ex3_output_inversion(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX3INVEN_MASK)


/// @fn _SI32_SSG_A_enable_ex0_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex0_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex0_output(basePointer)
#define SI32_SSG_A_enable_ex0_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX0EN_MASK)


/// @fn _SI32_SSG_A_disable_ex0_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex0_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex0_output(basePointer)
#define SI32_SSG_A_disable_ex0_output(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX0EN_MASK)


/// @fn _SI32_SSG_A_enable_ex1_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex1_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex1_output(basePointer)
#define SI32_SSG_A_enable_ex1_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX1EN_MASK)


/// @fn _SI32_SSG_A_disable_ex1_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex1_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex1_output(basePointer)
#define SI32_SSG_A_disable_ex1_output(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX1EN_MASK)


/// @fn _SI32_SSG_A_enable_ex2_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex2_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex2_output(basePointer)
#define SI32_SSG_A_enable_ex2_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX2EN_MASK)


/// @fn _SI32_SSG_A_disable_ex2_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex2_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex2_output(basePointer)
#define SI32_SSG_A_disable_ex2_output(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX2EN_MASK)


/// @fn _SI32_SSG_A_enable_ex3_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_enable_ex3_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_enable_ex3_output(basePointer)
#define SI32_SSG_A_enable_ex3_output(basePointer) \
   (basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX3EN_MASK)


/// @fn _SI32_SSG_A_disable_ex3_output(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SSG_A_disable_ex3_output(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_disable_ex3_output(basePointer)
#define SI32_SSG_A_disable_ex3_output(basePointer) \
   (basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX3EN_MASK)


/// @fn _SI32_SSG_A_is_active(SI32_SSG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_SSG_A_is_active(SI32_SSG_A_Type* /*basePointer*/);
///
/// @def SI32_SSG_A_is_active(basePointer)
#define SI32_SSG_A_is_active(basePointer) \
((bool) (basePointer->CONTROL.STATUS))



#ifdef __cplusplus
}
#endif

#endif // __SI32_SSG_A_TYPE_H__

//-eof--------------------------------------------------------------------------
