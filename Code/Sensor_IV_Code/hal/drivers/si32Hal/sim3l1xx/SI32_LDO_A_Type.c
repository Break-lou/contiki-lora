//-----------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/License_Agreement.htm
// 
// Silicon Laboratories - Initial API and implementation
//-----------------------------------------------------------------------------
/// @file SI32_LDO_A_Type.c
//
// This file applies to the SIM3L1XX_LDO_A module
//
// Script: 0.62
// HAL Source: 0.3
// Version: 6

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_LDO_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_LDO_A_write_control
//
// Write to CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_write_control(
   SI32_LDO_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_read_control
//
// Reads CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_LDO_A_read_control(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_digital_source_vbat_pin
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_digital_source_vbat_pin(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_DLDOSSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_digital_source_dcdc_output
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_digital_source_dcdc_output(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_DLDOSSEL_DCDC_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_digital_bias_high
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_digital_bias_high(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_DLDOBSEL_HIGH_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_digital_bias_low
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_digital_bias_low(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_DLDOBSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_set_digital_output_value
//
// Sets the output voltage of the digital LDO between 0.8 and 1.9 V in 50
// mV steps.
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_set_digital_output_value(
   SI32_LDO_A_Type * basePointer,
   uint32_t value)
{
   assert(value < 32);   // value < 2^5
   //{{
   basePointer->CONTROL.DLDOOVAL = value;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_get_digital_output_value
//
// Gets the output voltage setting of the digital LDO.
//-----------------------------------------------------------------------------
uint32_t
_SI32_LDO_A_get_digital_output_value(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.DLDOOVAL;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_memory_source_vbat_pin
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_memory_source_vbat_pin(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_MLDOSSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_memory_source_dcdc_output
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_memory_source_dcdc_output(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_MLDOSSEL_DCDC_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_memory_bias_high
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_memory_bias_high(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_MLDOBSEL_HIGH_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_memory_bias_low
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_memory_bias_low(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_MLDOBSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_set_memory_output_value
//
// Sets the output voltage of the memory LDO between 0.8 and 1.9 V in 50
// mV steps.
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_set_memory_output_value(
   SI32_LDO_A_Type * basePointer,
   uint32_t value)
{
   assert(value < 32);   // value < 2^5
   //{{
   basePointer->CONTROL.MLDOOVAL = value;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_get_memory_output_value
//
// Gets the output voltage setting of the memory LDO.
//-----------------------------------------------------------------------------
uint32_t
_SI32_LDO_A_get_memory_output_value(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.MLDOOVAL;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_analog_source_vbat_pin
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_analog_source_vbat_pin(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_ALDOSSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_analog_source_dcdc_output
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_analog_source_dcdc_output(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_ALDOSSEL_DCDC_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_analog_bias_high
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_analog_bias_high(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_ALDOBSEL_HIGH_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_analog_bias_low
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_analog_bias_low(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_ALDOBSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_set_analog_output_value
//
// Sets the output voltage of the analog LDO between 0.8 and 1.9 V in 50
// mV steps.
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_set_analog_output_value(
   SI32_LDO_A_Type * basePointer,
   uint32_t value)
{
   assert(value < 32);   // value < 2^5
   //{{
   basePointer->CONTROL.ALDOOVAL = value;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_get_analog_output_value
//
// Gets the output voltage setting of the analog LDO.
//-----------------------------------------------------------------------------
uint32_t
_SI32_LDO_A_get_analog_output_value(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.ALDOOVAL;
   //}}
}


//-eof--------------------------------------------------------------------------
