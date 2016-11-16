//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_RSTSRC_A_Type.c
//
// This file applies to the SIM3U1XX_RSTSRC_A module
//
// Script: 0.58
// HAL Source: 0.4
// Version: 4

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_RSTSRC_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_initialize(
   SI32_RSTSRC_A_Type * basePointer,
   // Write to RESETEN register.
   uint32_t reseten)
{
   //{{
   basePointer->RESETEN.U32 = reseten;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_write_reseten
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_write_reseten(
   SI32_RSTSRC_A_Type * basePointer,
   // Write to RESETEN register.
   uint32_t reseten)
{
   //{{
   basePointer->RESETEN.U32 = reseten;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_read_reseten
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RSTSRC_A_read_reseten(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   return basePointer->RESETEN.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_vdd_monitor_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_vdd_monitor_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_VMONREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_vdd_monitor_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_vdd_monitor_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_VMONREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_missing_clock_detector_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_missing_clock_detector_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET  = SI32_RSTSRC_A_RESETEN_MCDREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_missing_clock_detector_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_missing_clock_detector_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_MCDREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_watchdog_timer_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_watchdog_timer_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_WDTREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_watchdog_timer_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_watchdog_timer_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_WDTREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_comparator0_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_comparator0_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_CMP0REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_comparator0_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_comparator0_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_CMP0REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_comparator1_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_comparator1_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_CMP1REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_comparator1_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_comparator1_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_CMP1REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_usb0_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_usb0_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_USB0REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_usb0_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_usb0_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_USB0REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_rtc0_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_rtc0_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_RTC0REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_rtc0_reset_source
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_rtc0_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_RTC0REN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_generate_software_reset
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_generate_software_reset(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_SWREN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_get_last_reset_source
//
//-----------------------------------------------------------------------------
SI32_RSTSRC_Enum_Type
_SI32_RSTSRC_A_get_last_reset_source(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   SI32_RSTSRC_Enum_Type last_reset_source;

   // First Check for a POR
   // If this bit is set, all other flags are indeterminate
   if (basePointer->RESETFLAG.PORRF ==
       SI32_RSTSRC_A_RESETFLAG_PORRF_SET_VALUE)
   {
      last_reset_source = SI32_POWER_ON_RESET;
   }
   // Now check VMON
   // If this bit is set, all other flags are indeterminate
   else if (basePointer->RESETFLAG.VMONRF ==
            SI32_RSTSRC_A_RESETFLAG_VMONRF_SET_VALUE)
   {
      last_reset_source = SI32_VDD_MON_RESET;
   }
   // If last reset was caused by neither WAKEUP nor VDD Monitor, check the
   // rest of the flags.
   else
   {
      // PMU Wake
      if (basePointer->RESETFLAG.WAKERF ==
          SI32_RSTSRC_A_RESETFLAG_WAKERF_SET_VALUE)
      {
         last_reset_source = SI32_PMU_WAKEUP_RESET;
      }
      // Pin
      else if (basePointer->RESETFLAG.PINRF ==
               SI32_RSTSRC_A_RESETFLAG_PINRF_SET_VALUE)
      {
         last_reset_source = SI32_PIN_RESET;
      }
      // Core
      else if (basePointer->RESETFLAG.CORERF ==
               SI32_RSTSRC_A_RESETFLAG_CORERF_SET_VALUE)
      {
         last_reset_source = SI32_CORE_RESET;
      }
      // Missing Clock Detector
      else if (basePointer->RESETFLAG.MCDRF ==
               SI32_RSTSRC_A_RESETFLAG_MCDRF_SET_VALUE)
      {
         last_reset_source = SI32_MCD_RESET;
      }
      // Watchdog Timer
      else if (basePointer->RESETFLAG.WDTRF ==
               SI32_RSTSRC_A_RESETFLAG_WDTRF_SET_VALUE)
      {
         last_reset_source = SI32_WDT_RESET;
      }
      // Software Reset
      else if (basePointer->RESETFLAG.SWRF ==
               SI32_RSTSRC_A_RESETFLAG_SWRF_SET_VALUE)
      {
         last_reset_source = SI32_SW_RESET;
      }
      // Comparator 0
      else if (basePointer->RESETFLAG.CMP0RF ==
               SI32_RSTSRC_A_RESETFLAG_CMP0RF_SET_VALUE)
      {
         last_reset_source = SI32_CMP0_RESET;
      }
      // Comparator 1
      else if (basePointer->RESETFLAG.CMP1RF ==
               SI32_RSTSRC_A_RESETFLAG_CMP1RF_SET_VALUE)
      {
         last_reset_source = SI32_CMP1_RESET;
      }
      // USB0
      else if (basePointer->RESETFLAG.USB0RF ==
               SI32_RSTSRC_A_RESETFLAG_USB0RF_SET_VALUE)
      {
         last_reset_source = SI32_USB0_RESET;
      }
      // RTC0
      else if (basePointer->RESETFLAG.RTC0RF ==
               SI32_RSTSRC_A_RESETFLAG_RTC0RF_SET_VALUE)
      {
         last_reset_source = SI32_RTC0_RESET;
      }
      else
      {
         last_reset_source = SI32_RESET_ERROR;
      }
   }

   return last_reset_source;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_write_config
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_write_config(
   SI32_RSTSRC_A_Type * basePointer,
   // Write to CONFIG register.
   uint32_t config)
{
   //{{
   basePointer->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_read_config
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RSTSRC_A_read_config(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   return basePointer->CONFIG.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_enable_power_mode_9
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_enable_power_mode_9(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RSTSRC_A_CONFIG_PMSEL_PM9_EN_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RSTSRC_A_disable_power_mode_9
//
//-----------------------------------------------------------------------------
void
_SI32_RSTSRC_A_disable_power_mode_9(
   SI32_RSTSRC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RSTSRC_A_CONFIG_PMSEL_MASK;
   //}}
}


//-eof--------------------------------------------------------------------------
