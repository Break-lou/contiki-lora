//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_IVC_A_Type.c
//
// Script: 0.58
// HAL Source: 0.3
// Version: 3

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_IVC_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_IVC_A_initialize
//
// Writes all IVC registers.
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_initialize(
   SI32_IVC_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_write_control
//
// Writes CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_write_control(
   SI32_IVC_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_read_control
//
// Reads CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_IVC_A_read_control(
   SI32_IVC_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_select_channel_0_range
//
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_select_channel_0_range(
   SI32_IVC_A_Type * basePointer,
   // Desired range in mA from 1 to 6 (1 = 1 mA range, ..., 6 = 6 mA range).
   uint32_t range)
{
   assert((range >= 1) && (range <= 6));
   //{{
   basePointer->CONTROL.IN0RANGE = 6 - range;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_select_channel_1_range
//
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_select_channel_1_range(
   SI32_IVC_A_Type * basePointer,
   // Desired range in mA from 1 to 6 (1 = 1 mA range, ..., 6 = 6 mA range).
   uint32_t range)
{
   assert((range >= 1) && (range <= 6));
   //{{
   basePointer->CONTROL.IN1RANGE = 6 - range;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_enable_channel_0
//
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_enable_channel_0(
   SI32_IVC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_IVC_A_CONTROL_C0EN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_disable_channel_0
//
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_disable_channel_0(
   SI32_IVC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_IVC_A_CONTROL_C0EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_enable_channel_1
//
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_enable_channel_1(
   SI32_IVC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_IVC_A_CONTROL_C1EN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_IVC_A_disable_channel_1
//
//-----------------------------------------------------------------------------
void
_SI32_IVC_A_disable_channel_1(
   SI32_IVC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_IVC_A_CONTROL_C1EN_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
