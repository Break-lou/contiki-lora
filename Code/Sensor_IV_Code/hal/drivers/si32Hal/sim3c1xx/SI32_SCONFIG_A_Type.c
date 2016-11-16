//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_SCONFIG_A_Type.c
//
// This file applies to the SIM3C1XX_SCONFIG_A module
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_SCONFIG_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_SCONFIG_A_initialize
//
// Writes all SCONFIG registers.
//-----------------------------------------------------------------------------
void
_SI32_SCONFIG_A_initialize(
   SI32_SCONFIG_A_Type * basePointer,
   uint32_t config)
{
   //{{
   basePointer->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SCONFIG_A_write_config
//
// Writes CONFIG register.
//-----------------------------------------------------------------------------
void
_SI32_SCONFIG_A_write_config(
   SI32_SCONFIG_A_Type * basePointer,
   uint32_t config)
{
   //{{
   basePointer->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SCONFIG_A_read_config
//
// Reads CONFIG register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_SCONFIG_A_read_config(
   SI32_SCONFIG_A_Type * basePointer)
{
   //{{
   return basePointer->CONFIG.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SCONFIG_A_enter_fast_dma_mode
//
// Run the DMA in the faster mode.
//-----------------------------------------------------------------------------
void
_SI32_SCONFIG_A_enter_fast_dma_mode(
   SI32_SCONFIG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SCONFIG_A_CONFIG_FDMAEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SCONFIG_A_exit_fast_dma_mode
//
// Run the DMA in the legacy uDMA mode.
//-----------------------------------------------------------------------------
void
_SI32_SCONFIG_A_exit_fast_dma_mode(
   SI32_SCONFIG_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SCONFIG_A_CONFIG_FDMAEN_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
