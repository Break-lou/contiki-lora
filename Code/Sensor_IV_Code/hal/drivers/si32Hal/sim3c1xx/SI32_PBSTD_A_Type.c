//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_PBSTD_A_Type.c
//
// This file applies to the SIM3C1XX_PBSTD_A module
//
// Script: 0.59
// HAL Source: 0.3
// Version: 3

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_PBSTD_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_initialize(
   SI32_PBSTD_A_Type * basePointer,
   // Write to PB register.
   uint32_t pb,
   // Write to PBMDSEL register.
   uint32_t pbmdsel,
   // Write to PBSKIPEN register.
   uint32_t pbskipen,
   // Write to PBOUTMD register.
   uint32_t pboutmd,
   // Write to PBDRV register.
   uint32_t pbdrv,
   // Write to PM register.
   uint32_t pm,
   // Write to PMEN register.
   uint32_t pmen)
{
   //{{
   basePointer->PB.U32       = pb;
   basePointer->PBMDSEL.U32  = pbmdsel;
   basePointer->PBSKIPEN.U32 = pbskipen;
   basePointer->PBOUTMD.U32  = pboutmd;
   basePointer->PBDRV.U32    = pbdrv;
   basePointer->PM.U32       = pm;
   basePointer->PMEN.U32     = pmen;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pb
//
// Writes to PB register.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pb(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pb)
{
   //{{
   basePointer->PB.U32 = pb;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pb
//
// Reads PB register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pb(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PB.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pins_high
//
// Writes selected pins high.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pins_high(
   SI32_PBSTD_A_Type * basePointer,
   // Mask for pin writes : 1 = set pin to high.
   uint32_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PB_SET = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pins_low
//
// Writes selected pins low.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pins_low(
   SI32_PBSTD_A_Type * basePointer,
   // Mask for pin writes : 1 = clear pin to low.
   uint32_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PB_CLR = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pins_masked
//
// Write selected pins.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pins_masked(
   SI32_PBSTD_A_Type * basePointer,
   // Values for latch.
   uint32_t pin_value,
   // Mask value : 1 = write, 0 = ignore.
   uint32_t pin_mask)
{
   assert(pin_value < 65536);   // pin_value < 2^16
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PB_MSK = (pin_mask<<16)|(pin_value);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_toggle_pins
//
// Toggle selected pins.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_toggle_pins(
   SI32_PBSTD_A_Type * basePointer,
   // Mask for pin toggles : 1 = toggle pin.
   uint32_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PB_MSK = (pin_mask<<16)|(~(basePointer->PB.U32) & 0xFFFF);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pins
//
// Reads PBPIN register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pins(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return (basePointer->PBPIN.U32);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pin
//
// Reads the state of a single pin.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pin(
   SI32_PBSTD_A_Type * basePointer,
   // Number of the pin to read : 0 = pin 0.
   uint32_t pin_number)
{
   assert(pin_number < 65536);   // pin_number < 2^16
   //{{
   return ((basePointer->PBPIN.U32) >> pin_number) & 1;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pbmdsel
//
// Writes to PBMDSEL register.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pbmdsel(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pbmdsel)
{
   //{{
   basePointer->PBMDSEL.U32 = pbmdsel;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pbmdsel
//
// Reads PBMDSEL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pbmdsel(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBMDSEL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_set_pins_push_pull_output
//
// Sets the pins masked with 1's to digital push-pull.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_set_pins_push_pull_output(
   SI32_PBSTD_A_Type * basePointer,
   // Selects which pins to configure digital push-pull.
   uwide16_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
	basePointer->PBOUTMD_SET = pin_mask;
   basePointer->PBMDSEL_SET = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_set_pins_digital_input
//
// Sets the pins masked with 1's to open-drain input.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_set_pins_digital_input(
   SI32_PBSTD_A_Type * basePointer,
   // Selects which pins to configure open-drain input.
   uwide16_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PBOUTMD_CLR = pin_mask;
   basePointer->PB_SET      = pin_mask;
   basePointer->PBMDSEL_SET = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_set_pins_analog
//
// Sets the pins masked with 1's to analog mode.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_set_pins_analog(
   SI32_PBSTD_A_Type * basePointer,
   // Selects which pins to configure as analog.
   uwide16_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PBMDSEL_CLR = pin_mask;
   basePointer->PB_SET      = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pbskipen
//
// Writes to PBSKIPEN register.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pbskipen(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pbskipen)
{
   //{{
   basePointer->PBSKIPEN.U32 = pbskipen;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pbskipen
//
// Reads PBSKIPEN register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pbskipen(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBSKIPEN.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pboutmd
//
// Writes to PBOUTMD register.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pboutmd(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pboutmd)
{
   //{{
   basePointer->PBOUTMD.U32 = pboutmd;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pboutmd
//
// Reads PBOUTMD register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pboutmd(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBOUTMD.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pbdrv
//
// Writes to PBDRV register.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pbdrv(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pbdrv)
{
   //{{
   basePointer->PBDRV.U32 = pbdrv;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pbdrv
//
// Reads PBDRV register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pbdrv(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBDRV.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_set_pins_high_drive_strength
//
// Sets the drive strength to high for masked pins.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_set_pins_high_drive_strength(
   SI32_PBSTD_A_Type * basePointer,
   // Selects which pins to configure drive high.
   uwide16_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PBDRV_SET = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_set_pins_low_drive_strength
//
// Sets the drive strength to low for masked pins.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_set_pins_low_drive_strength(
   SI32_PBSTD_A_Type * basePointer,
   // Selects which pins to configure drive low.
   uwide16_t pin_mask)
{
   assert(pin_mask < 65536);   // pin_mask < 2^16
   //{{
   basePointer->PBDRV_CLR = pin_mask;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_enable_pullup_resistors
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_enable_pullup_resistors(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   basePointer->PBDRV_SET = SI32_PBSTD_A_PBDRV_PBPUEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_disable_pullup_resistors
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_disable_pullup_resistors(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   basePointer->PBDRV_CLR = SI32_PBSTD_A_PBDRV_PBPUEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pm
//
// Writes to PM register, available on all ports.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pm(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pm)
{
   //{{
   basePointer->PM.U32 = pm;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pm
//
// Reads PM register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pm(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PM.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_set_port_match_pin_value
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_set_port_match_pin_value(
   SI32_PBSTD_A_Type * basePointer,
   // Number of the pin to set the port match value high : 0 = pin 0.
   uint32_t pin_number)
{
   assert(pin_number < 65536);   // pin_number < 2^16
   //{{
   basePointer->PM_SET = (1 << pin_number);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_clear_port_match_pin_value
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_clear_port_match_pin_value(
   SI32_PBSTD_A_Type * basePointer,
   // Number of the pin to set the port match value low : 0 = pin 0.
   uint32_t pin_number)
{
   assert(pin_number < 65536);   // pin_number < 2^16
   //{{
   basePointer->PM_CLR = (1 << pin_number);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pmen
//
// Writes to PMEN register, available on all ports.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pmen(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pmen)
{
   //{{
   basePointer->PMEN.U32 = pmen;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pmen
//
// Reads PMEN register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pmen(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PMEN.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_enable_port_match_pin
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_enable_port_match_pin(
   SI32_PBSTD_A_Type * basePointer,
   // Number of the pin to enable port match : 0 = pin 0.
   uint32_t pin_number)
{
   assert(pin_number < 65536);   // pin_number < 2^16
   //{{
   basePointer->PMEN_SET = (1 << pin_number);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_disable_port_match_pin
//
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_disable_port_match_pin(
   SI32_PBSTD_A_Type * basePointer,
   // Number of the pin to disable port match : 0 = pin 0.
   uint32_t pin_number)
{
   assert(pin_number < 65536);   // pin_number < 2^16
   //{{
   basePointer->PMEN_CLR = (1 << pin_number);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pblock
//
// Writes to PBLOCK register, only available for P2/P3.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pblock(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pblock)
{
   //{{
   basePointer->PBLOCK.U32 = pblock;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pblock
//
// Reads PBLOCK register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pblock(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBLOCK.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pbpgmask
//
// Writes to PBPGEN register, only available for P2.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pbpgmask(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pbpgen)
{
   //{{
   basePointer->PBPGEN.U32 = pbpgen;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pbpgmask
//
// Reads PBPGEN register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pbpgmask(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBPGEN.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_write_pbpgphase
//
// Writes to PBPGPHASE register only available for P2.
//-----------------------------------------------------------------------------
void
_SI32_PBSTD_A_write_pbpgphase(
   SI32_PBSTD_A_Type * basePointer,
   uint32_t pbpgphase)
{
   //{{
   basePointer->PBPGPHASE.U32 = pbpgphase;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PBSTD_A_read_pbpgphase
//
// Reads PBPGPHASE register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PBSTD_A_read_pbpgphase(
   SI32_PBSTD_A_Type * basePointer)
{
   //{{
   return basePointer->PBPGPHASE.U32;
   //}}
}


//-eof--------------------------------------------------------------------------
