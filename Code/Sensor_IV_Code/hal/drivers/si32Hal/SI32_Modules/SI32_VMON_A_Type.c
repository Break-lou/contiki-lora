//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_VMON_A_Type.c
//
// Script: 0.58
// HAL Source: 0.2
// Version: 5

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_VMON_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_VMON_A_initialize
//
// Writes all VMON registers.
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_initialize(
   SI32_VMON_A_Type * basePointer,
   uint32_t control)
{
   //{{
	basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_write_control
//
// Writes CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_write_control(
   SI32_VMON_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_read_control
//
// Reads CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_VMON_A_read_control(
   SI32_VMON_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_enable_vreg_supply_monitor
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_enable_vreg_supply_monitor(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VREGINSEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_disable_vreg_supply_monitor
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_disable_vreg_supply_monitor(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VREGINSEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_is_vreg_low_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_VMON_A_is_vreg_low_interrupt_pending(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	return !(bool)(basePointer->CONTROL.VREGINLI);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_is_vdd_above_reset_threshold
//
//-----------------------------------------------------------------------------
bool
_SI32_VMON_A_is_vdd_above_reset_threshold(
   SI32_VMON_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.VDDRSTF);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_is_vdd_low_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_VMON_A_is_vdd_low_interrupt_pending(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	return !(bool)(basePointer->CONTROL.VDDLI);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_select_vdd_high_threshold
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_select_vdd_high_threshold(
   SI32_VMON_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VDDHITHEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_select_vdd_standard_threshold
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_select_vdd_standard_threshold(
   SI32_VMON_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VDDHITHEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_enable_vdd_low_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_enable_vdd_low_interrupt(
   SI32_VMON_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VDDLIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_disable_vdd_low_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_disable_vdd_low_interrupt(
   SI32_VMON_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VDDLIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_is_vdd_low_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_VMON_A_is_vdd_low_interrupt_enabled(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONTROL.VDDLIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_enable_vreg_low_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_enable_vreg_low_interrupt(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VREGINLIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_disable_vreg_low_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_disable_vreg_low_interrupt(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VREGINLIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_is_vreg_low_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_VMON_A_is_vreg_low_interrupt_enabled(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONTROL.VREGINLIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_enable_vdd_supply_monitor
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_enable_vdd_supply_monitor(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_SET = SI32_VMON_A_CONTROL_VMONEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_VMON_A_disable_vdd_supply_monitor
//
//-----------------------------------------------------------------------------
void
_SI32_VMON_A_disable_vdd_supply_monitor(
   SI32_VMON_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_CLR = SI32_VMON_A_CONTROL_VMONEN_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
