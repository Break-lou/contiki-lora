//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_LDO_A_Type.c
//
// This file applies to the SIM3C1XX_LDO_A module
//
// Script: 0.58
// HAL Source: 0.1
// Version: 3

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
// _SI32_LDO_A_select_high_bias
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_high_bias(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_LDOIBIAS_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_select_low_bias
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_select_low_bias(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_LDOIBIAS_LOWBIAS_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_enable_bias
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_enable_bias(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_LDO_A_CONTROL_LDOAEN_ENABLE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LDO_A_disable_bias
//
//-----------------------------------------------------------------------------
void
_SI32_LDO_A_disable_bias(
   SI32_LDO_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_LDO_A_CONTROL_LDOAEN_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
