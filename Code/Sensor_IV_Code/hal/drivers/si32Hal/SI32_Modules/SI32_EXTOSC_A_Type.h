//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_EXTOSC_A_Type.h
//
// Script: 0.58
// HAL Source: 0.2
// Version: 1

#ifndef __SI32_EXTOSC_A_TYPE_H__
#define __SI32_EXTOSC_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_EXTOSC_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_EXTOSC_A_initialize(SI32_EXTOSC_A_Type* basePointer,
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
_SI32_EXTOSC_A_initialize(SI32_EXTOSC_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_EXTOSC_A_initialize(basePointer, control)
#define SI32_EXTOSC_A_initialize(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_EXTOSC_A_write_control(SI32_EXTOSC_A_Type* basePointer,
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
_SI32_EXTOSC_A_write_control(SI32_EXTOSC_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_EXTOSC_A_write_control(basePointer, control)
#define SI32_EXTOSC_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_EXTOSC_A_read_control(SI32_EXTOSC_A_Type* basePointer)
///
/// @return
///  Read CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_EXTOSC_A_read_control(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_read_control(basePointer)
#define SI32_EXTOSC_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_EXTOSC_A_set_frequency_control_range(SI32_EXTOSC_A_Type* basePointer,
///      uint32_t freqcn)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  freqcn
///  Valid range is 3 bits.
///  Frequency control range value.
///
void
_SI32_EXTOSC_A_set_frequency_control_range(SI32_EXTOSC_A_Type* /*basePointer*/,
   uint32_t /*freqcn*/);
///
/// @def SI32_EXTOSC_A_set_frequency_control_range(basePointer, freqcn)
#define SI32_EXTOSC_A_set_frequency_control_range(basePointer, freqcn) do{  \
   basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_FREQCN_MASK;\
   basePointer->CONTROL_SET = freqcn;\
} while(0)


/// @fn _SI32_EXTOSC_A_is_oscillator_valid(SI32_EXTOSC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_EXTOSC_A_is_oscillator_valid(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_is_oscillator_valid(basePointer)
#define SI32_EXTOSC_A_is_oscillator_valid(basePointer) \
((bool)(basePointer->CONTROL.OSCVLDF))


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_off(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Turn off the external oscillator circuit.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_off(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_off(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_off(basePointer) \
   (basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_OSCMD_MASK)


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_cmos(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Use external CMOS clock as the external oscillator source.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_cmos(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_cmos(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_cmos(basePointer) do{  \
   basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_OSCMD_MASK;\
   basePointer->CONTROL_SET = SI32_EXTOSC_A_CONTROL_OSCMD_CMOS_U32;\
} while(0)


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_cmos_div2(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Use external CMOS clock with divide-by-2 stage as the external
/// oscillator source.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_cmos_div2(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_cmos_div2(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_cmos_div2(basePointer) do{  \
   basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_OSCMD_MASK;\
   basePointer->CONTROL_SET = SI32_EXTOSC_A_CONTROL_OSCMD_CMOSDIV2_U32;\
} while(0)


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_rc_div2(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Use external RC oscillator with divide-by-2 stage as the external
/// oscillator source.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_rc_div2(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_rc_div2(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_rc_div2(basePointer) do{  \
   basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_OSCMD_MASK;\
   basePointer->CONTROL_SET = SI32_EXTOSC_A_CONTROL_OSCMD_RC_U32;\
} while(0)


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_c_div2(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Use external C oscillator with divide-by-2 stage as the external
/// oscillator source.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_c_div2(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_c_div2(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_c_div2(basePointer) do{  \
   basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_OSCMD_MASK;\
   basePointer->CONTROL_SET = SI32_EXTOSC_A_CONTROL_OSCMD_C_U32;\
} while(0)


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_crystal(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Use external crystal oscillator as the external oscillator source.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_crystal(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_crystal(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_crystal(basePointer) do{  \
   basePointer->CONTROL_CLR = SI32_EXTOSC_A_CONTROL_OSCMD_MASK;\
   basePointer->CONTROL_SET = SI32_EXTOSC_A_CONTROL_OSCMD_XTAL_U32;\
} while(0)


/// @fn _SI32_EXTOSC_A_select_oscillator_mode_crystal_div2(SI32_EXTOSC_A_Type* basePointer)
///
/// @brief
/// Use external crystal oscillator with divide-by-2 stage as the external
/// oscillator source.
///
/// @param[in]
///  basePointer
///
void
_SI32_EXTOSC_A_select_oscillator_mode_crystal_div2(SI32_EXTOSC_A_Type* /*basePointer*/);
///
/// @def SI32_EXTOSC_A_select_oscillator_mode_crystal_div2(basePointer)
#define SI32_EXTOSC_A_select_oscillator_mode_crystal_div2(basePointer) \
   (basePointer->CONTROL_SET	= SI32_EXTOSC_A_CONTROL_OSCMD_XTALDIV2_U32)



#ifdef __cplusplus
}
#endif

#endif // __SI32_EXTOSC_A_TYPE_H__

//-eof--------------------------------------------------------------------------
