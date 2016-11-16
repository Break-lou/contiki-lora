//-----------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/License_Agreement.htm
// 
// Silicon Laboratories - Initial API and implementation
//-----------------------------------------------------------------------------
/// @file SI32_PVTOSC_A_Type.c
//
// Script: 0.62
// HAL Source: 0.3
// Version: 1

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_PVTOSC_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_initialize
//
// Writes all PVTOSC registers.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_initialize(
   SI32_PVTOSC_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_write_control
//
// Writes CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_write_control(
   SI32_PVTOSC_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_read_control
//
// Reads CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PVTOSC_A_read_control(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_enable_digital_ldo_oscillator
//
// Enables the digital LDO PVT oscillator.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_enable_digital_ldo_oscillator(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_DIGOSCEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_disable_digital_ldo_oscillator
//
// Disables the digital LDO PVT oscillator.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_disable_digital_ldo_oscillator(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_DIGOSCEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_enable_memory_ldo_oscillator
//
// Enables the memory LDO PVT oscillator.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_enable_memory_ldo_oscillator(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_MEMOSCEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_disable_memory_ldo_oscillator
//
// Disables the memory LDO PVT oscillator.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_disable_memory_ldo_oscillator(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_MEMOSCEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_select_digital_ldo_oscillator_slow_mode
//
// Selects digital LDO PVT oscillator slow mode (~50 kHz).
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_select_digital_ldo_oscillator_slow_mode(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_DIGOSCMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_select_digital_ldo_oscillator_fast_mode
//
// Selects digital LDO PVT oscillator fast mode (~6.4 MHz).
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_select_digital_ldo_oscillator_fast_mode(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_DIGOSCMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_select_memory_ldo_oscillator_slow_mode
//
// Selects memory LDO PVT oscillator slow mode (~50 kHz).
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_select_memory_ldo_oscillator_slow_mode(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_MEMOSCMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_select_memory_ldo_oscillator_fast_mode
//
// Selects memory LDO PVT oscillator fast mode (~6.4 MHz).
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_select_memory_ldo_oscillator_fast_mode(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_MEMOSCMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_select_divider_source_apb_clock
//
// Selects APB clock as the input to the clock dividers.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_select_divider_source_apb_clock(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PVTOSC_A_CONTROL_CLKSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PVTOSC_A_select_divider_source_oscillators
//
// Selects PVT oscillators as the inputs to the clock dividers.
//-----------------------------------------------------------------------------
void
_SI32_PVTOSC_A_select_divider_source_oscillators(
   SI32_PVTOSC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PVTOSC_A_CONTROL_CLKSEL_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
