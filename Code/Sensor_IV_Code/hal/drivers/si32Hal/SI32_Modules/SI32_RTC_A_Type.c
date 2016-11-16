//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories Inc.  All rights reserved.
// The program contained in this listing is proprietary to Silicon Laboratories,
// headquartered in Austin, Texas, U.S.A. and is subject to worldwide copyright
// protection, including protection under the United States Copyright Act of 1976
// as an unpublished work, pursuant to Section 104 and Section 408 of Title XVII
// of the United States code.  Unauthorized copying, adaptation, distribution,
// use, or display is prohibited by this law.
// 
// Silicon Laboratories provides this software solely and exclusively 
// for use on Silicon Laboratories' microcontroller products.
// 
// This software is provided "as is".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// SILICON LABORATORIES SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, 
// INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
//------------------------------------------------------------------------------
/// @file SI32_RTC_A_Type.c
//
// Script: 0.59
// HAL Source: 0.6
// Version: 11

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_RTC_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_RTC_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_initialize(
   SI32_RTC_A_Type * basePointer,
   // Write to CONFIG register.
   uint32_t config,
   // Write to CONTROL register.
   uint32_t control,
   // Write to ALARM0 register.
   uint32_t alarm0,
   // Write to ALARM1 register.
   uint32_t alarm1,
   // Write to ALARM2 register.
   uint32_t alarm2,
   // Write to SETCAP register.
   uint32_t setcap,
   // Write to LFOCONTROL register.
   uint32_t lfocontrol)
{
   //{{
   basePointer->CONFIG.U32 = config;
   basePointer->CONTROL.U32 = control;
   basePointer->ALARM0.U32 = alarm0;
   basePointer->ALARM1.U32 = alarm1;
   basePointer->ALARM2.U32 = alarm2;
   basePointer->SETCAP.U32 = setcap;
   basePointer->LFOCONTROL.U32 = lfocontrol;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_config
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_config(
   SI32_RTC_A_Type * basePointer,
   // Write to CONFIG register.
   uint32_t config)
{
   //{{
   basePointer->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_config
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_config(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->CONFIG.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm0_auto_reset
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm0_auto_reset(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_ALM0AREN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm0_auto_reset
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm0_auto_reset(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_ALM0AREN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_start_timer
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_start_timer(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_RUN_START_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_stop_timer
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_stop_timer(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_RUN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_missing_clock_detector
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_missing_clock_detector(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_MCLKEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_missing_clock_detector
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_missing_clock_detector(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_MCLKEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_autostep
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_autostep(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_ASEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_autostep
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_autostep(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_ASEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_set_rtc_load_capacitance
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_set_rtc_load_capacitance(
   SI32_RTC_A_Type * basePointer,
   uint32_t rtclc)
{
   assert(rtclc < 16);   // rtclc < 2^4
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_RTCLC_MASK;
   basePointer->CONFIG_SET = (rtclc << SI32_RTC_A_CONFIG_RTCLC_SHIFT);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_bias_doubler
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_bias_doubler(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_BDEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_bias_doubler
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_bias_doubler(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_BDEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_crystal_oscillator
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_crystal_oscillator(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_CRYSEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_crystal_oscillator
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_crystal_oscillator(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_CRYSEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_auto_gain_control
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_auto_gain_control(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_AGCEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_auto_gain_control
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_auto_gain_control(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_AGCEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm0
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm0(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_ALM0EN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm0
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm0(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_ALM0EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm0_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm0_enabled(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONFIG.ALM0EN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm1
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm1(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_ALM1EN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm1
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm1(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_ALM1EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm1_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm1_enabled(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONFIG.ALM1EN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm2
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm2(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_ALM2EN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm2
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm2(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_ALM2EN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm2_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm2_enabled(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONFIG.ALM2EN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_external_pin_clock_drive
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_external_pin_clock_drive(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET =SI32_RTC_A_CONFIG_RTCOEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_external_pin_clock_drive
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_external_pin_clock_drive(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_RTCOEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_set_clock_source_rtc
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_set_clock_source_rtc(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_CLKSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_set_clock_source_lfo
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_set_clock_source_lfo(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_CLKSEL_LFOSCN_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_rtc_timer
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_rtc_timer(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_RTC_A_CONFIG_RTCEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_rtc_timer
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_rtc_timer(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_RTC_A_CONFIG_RTCEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_control
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_control(
   SI32_RTC_A_Type * basePointer,
   // Write to CONTROL register.
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_control
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_control(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm0_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm0_interrupt_pending(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.ALM0I);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm1_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm1_interrupt_pending(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.ALM1I);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm2_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm2_interrupt_pending(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.ALM2I);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_start_timer_set
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_start_timer_set(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_RTC_A_CONTROL_TMRSET_SET_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_timer_set_in_progress
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_timer_set_in_progress(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.TMRSET);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_start_timer_capture
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_start_timer_capture(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_RTC_A_CONTROL_TMRCAP_SET_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_timer_capture_in_progress
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_timer_capture_in_progress(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.TMRCAP);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_clear_alarm0_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_clear_alarm0_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_RTC_A_CONTROL_ALM0I_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_clear_alarm1_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_clear_alarm1_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_RTC_A_CONTROL_ALM1I_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_clear_alarm2_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_clear_alarm2_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_RTC_A_CONTROL_ALM2I_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_external_oscillator_valid
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_external_oscillator_valid(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.CLKVF);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_oscillator_running
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_oscillator_running(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.OSCFI == SI32_RTC_A_CONTROL_OSCFI_NOT_SET_VALUE);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_clear_oscillator_fail_flag
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_clear_oscillator_fail_flag(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_RTC_A_CONTROL_OSCFI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_high_speed_mode
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_high_speed_mode(
   SI32_RTC_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_SET = SI32_RTC_A_CONTROL_HSMDEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_high_speed_mode
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_high_speed_mode(
   SI32_RTC_A_Type * basePointer)
{
   //{{
	basePointer->CONTROL_CLR = SI32_RTC_A_CONTROL_HSMDEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_load_capacitance_ready
//
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_load_capacitance_ready(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.LRDYF);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_alarm0
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_alarm0(
   SI32_RTC_A_Type * basePointer,
   // Write to ALARM0 register.
   uint32_t alarm0)
{
   //{{
   basePointer->ALARM0.U32 = alarm0;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_alarm0
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_alarm0(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->ALARM0.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_alarm1
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_alarm1(
   SI32_RTC_A_Type * basePointer,
   // Write to ALARM1 register.
   uint32_t alarm1)
{
   //{{
   basePointer->ALARM1.U32 = alarm1;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_alarm1
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_alarm1(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->ALARM1.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_alarm2
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_alarm2(
   SI32_RTC_A_Type * basePointer,
   // Write to ALARM2 register.
   uint32_t alarm2)
{
   //{{
   basePointer->ALARM2.U32 = alarm2;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_alarm2
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_alarm2(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->ALARM2.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_setcap
//
// Set and poll TMRSET after writing to SETCAP.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_setcap(
   SI32_RTC_A_Type * basePointer,
   // Write to SETCAP register.
   uint32_t setcap)
{
   //{{
   basePointer->SETCAP.U32 = setcap;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_setcap
//
// Set and poll TMRCAP before reading SETCAP.
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_setcap(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->SETCAP.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_write_lfocontrol
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_write_lfocontrol(
   SI32_RTC_A_Type * basePointer,
   // Write to LFOCONTROL register.
   uint32_t lfocontrol)
{
   //{{
   basePointer->LFOCONTROL.U32 = lfocontrol;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_read_lfocontrol
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_RTC_A_read_lfocontrol(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return basePointer->LFOCONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_low_frequency_oscillator
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_low_frequency_oscillator(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->LFOCONTROL.LFOSCEN = SI32_RTC_A_LFOCONTROL_LFOSCEN_ENABLED_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_low_frequency_oscillator
//
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_low_frequency_oscillator(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   basePointer->LFOCONTROL.LFOSCEN = SI32_RTC_A_LFOCONTROL_LFOSCEN_DISABLED_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm0_interrupt
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_enable_alarm0.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm0_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_enable_alarm0(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm0_interrupt
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_disable_alarm0.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm0_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_disable_alarm0(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm0_interrupt_enabled
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_is_alarm0_enabled.
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm0_interrupt_enabled(
   SI32_RTC_A_Type * basePointer)
{
   //{{
	return SI32_RTC_A_is_alarm0_enabled(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm1_interrupt
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_enable_alarm1.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm1_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_enable_alarm1(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm1_interrupt
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_disable_alarm1.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm1_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_disable_alarm1(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm1_interrupt_enabled
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_is_alarm1_enabled.
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm1_interrupt_enabled(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return SI32_RTC_A_is_alarm1_enabled(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_alarm2_interrupt
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_enable_alarm2.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_alarm2_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_enable_alarm2(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_alarm2_interrupt
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_disable_alarm2.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_alarm2_interrupt(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_disable_alarm2(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_is_alarm2_interrupt_enabled
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_is_alarm2_enabled.
//-----------------------------------------------------------------------------
bool
_SI32_RTC_A_is_alarm2_interrupt_enabled(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   return SI32_RTC_A_is_alarm2_enabled(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_enable_module
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_enable_rtc_timer.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_enable_module(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_enable_rtc_timer(basePointer);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_RTC_A_disable_module
//
// WARNING: THIS FUNCTION IS DEPRECATED AS OF si32-1.1.0. NOT FOR NEW
// DESIGN. SUPERCEDED BY _SI32_RTC_A_disable_rtc_timer.
//-----------------------------------------------------------------------------
void
_SI32_RTC_A_disable_module(
   SI32_RTC_A_Type * basePointer)
{
   //{{
   SI32_RTC_A_disable_rtc_timer(basePointer);
   //}}
}


//-eof--------------------------------------------------------------------------
