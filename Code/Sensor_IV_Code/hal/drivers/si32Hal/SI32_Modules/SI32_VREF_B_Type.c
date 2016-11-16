//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_VREF_B_Type.c
//
// Script: 0.61
// HAL Source: 0.1
// Version: 5

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_VREF_B_Type.h"


//-----------------------------------------------------------------------------
// _SI32_VREF_B_initialize
//
// Writes all VREF registers.
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_initialize(
   SI32_VREF_B_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_write_control
//
// Writes CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_write_control(
   SI32_VREF_B_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_read_control
//
// Reads CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_VREF_B_read_control(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_select_1p2_volts
//
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_select_1p2_volts(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_VREF_B_CONTROL_VREF2X_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_select_2p4_volts
//
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_select_2p4_volts(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_VREF_B_CONTROL_VREF2X_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_enable_temperature_sensor
//
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_enable_temperature_sensor(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_VREF_B_CONTROL_TEMPEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_disable_temperature_sensor
//
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_disable_temperature_sensor(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_VREF_B_CONTROL_TEMPEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_enable_voltage_reference
//
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_enable_voltage_reference(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_VREF_B_CONTROL_VREFOUTEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VREF_B_disable_voltage_reference
//
//-----------------------------------------------------------------------------
void
_SI32_VREF_B_disable_voltage_reference(
   SI32_VREF_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_VREF_B_CONTROL_VREFOUTEN_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
