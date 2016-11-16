//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_SSG_A_Type.c
//
// Script: 0.58
// HAL Source: 0.4
// Version: 3

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_SSG_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_SSG_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_initialize(
   SI32_SSG_A_Type * basePointer,
   // Write to CONFIG register.
   uint32_t config,
   // Write to CONTROL register.
   uint32_t control)
{
   //{{
   basePointer->CONFIG.U32 = config;
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_write_config
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_write_config(
   SI32_SSG_A_Type * basePointer,
   // Write to CONFIG register.
   uint32_t config)
{
   //{{
   basePointer->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_read_config
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_SSG_A_read_config(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   return basePointer->CONFIG.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_set_conversion_count
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_set_conversion_count(
   SI32_SSG_A_Type * basePointer,
   // Desired count.
   uint32_t count)
{
   assert(count < 4096);   // count < 2^12
   //{{
   basePointer->CONFIG.COUNT = count;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_select_speed_normal
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_select_speed_normal(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG.SSEL = SI32_SSG_A_CONFIG_SSEL_NORMAL_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_select_speed_double
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_select_speed_double(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG.SSEL = SI32_SSG_A_CONFIG_SSEL_DOUBLE_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_start_phase_generator_freerun
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_start_phase_generator_freerun(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG.PHGFREN = SI32_SSG_A_CONFIG_PHGFREN_ENABLED_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_stop_phase_generator_freerun
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_stop_phase_generator_freerun(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG.PHGFREN = SI32_SSG_A_CONFIG_PHGFREN_DISABLED_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_start_pulse_generator_freerun
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_start_pulse_generator_freerun(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG.PUGFREN = SI32_SSG_A_CONFIG_PUGFREN_ENABLED_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_stop_pulse_generator_freerun
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_stop_pulse_generator_freerun(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG.PUGFREN = SI32_SSG_A_CONFIG_PUGFREN_DISABLED_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_write_control
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_write_control(
   SI32_SSG_A_Type * basePointer,
   // Write to CONTROL register.
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_read_control
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_SSG_A_read_control(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex0_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex0_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX0INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex0_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex0_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX0INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex1_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex1_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX1INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex1_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex1_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX1INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex2_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex2_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX2INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex2_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex2_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX2INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex3_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex3_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX3INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex3_output_inversion
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex3_output_inversion(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX3INVEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex0_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex0_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX0EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex0_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex0_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX0EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex1_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex1_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX1EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex1_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex1_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX1EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex2_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex2_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX2EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex2_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex2_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX2EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_enable_ex3_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_enable_ex3_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SSG_A_CONTROL_EX3EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_disable_ex3_output
//
//-----------------------------------------------------------------------------
void
_SI32_SSG_A_disable_ex3_output(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SSG_A_CONTROL_EX3EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SSG_A_is_active
//
//-----------------------------------------------------------------------------
bool
_SI32_SSG_A_is_active(
   SI32_SSG_A_Type * basePointer)
{
   //{{
   return (bool) (basePointer->CONTROL.STATUS);
   //}}
}


//-eof--------------------------------------------------------------------------
