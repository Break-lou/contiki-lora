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
/// @file SI32_RTC_B_Type.h
//
// Script: 0.59
// HAL Source: 0.93
// Version: 1

#ifndef __SI32_RTC_B_TYPE_H__
#define __SI32_RTC_B_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_RTC_B_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_RTC_B_initialize(SI32_RTC_B_Type* basePointer,
///      uint32_t config,
///      uint32_t control,
///      uint32_t alarm0,
///      uint32_t alarm1,
///      uint32_t alarm2,
///      uint32_t setcap,
///      uint32_t lfocontrol)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///  Write to CONFIG register.
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///  Write to CONTROL register.
///
/// @param[in]
///  alarm0
///  Valid range is 32 bits.
///  Write to ALARM0 register.
///
/// @param[in]
///  alarm1
///  Valid range is 32 bits.
///  Write to ALARM1 register.
///
/// @param[in]
///  alarm2
///  Valid range is 32 bits.
///  Write to ALARM2 register.
///
/// @param[in]
///  setcap
///  Valid range is 32 bits.
///  Write to SETCAP register.
///
/// @param[in]
///  lfocontrol
///  Valid range is 32 bits.
///  Write to LFOCONTROL register.
///
void
_SI32_RTC_B_initialize(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t, /*config*/
   uint32_t, /*control*/
   uint32_t, /*alarm0*/
   uint32_t, /*alarm1*/
   uint32_t, /*alarm2*/
   uint32_t, /*setcap*/
   uint32_t /*lfocontrol*/);
///
/// @def SI32_RTC_B_initialize(basePointer, config, control, alarm0, alarm1, alarm2, setcap, lfocontrol)
#define SI32_RTC_B_initialize(basePointer, config, control, alarm0, alarm1, alarm2, setcap, lfocontrol) do{  \
   basePointer->CONFIG.U32 = config;\
   basePointer->CONTROL.U32 = control;\
   basePointer->ALARM0.U32 = alarm0;\
   basePointer->ALARM1.U32 = alarm1;\
   basePointer->ALARM2.U32 = alarm2;\
   basePointer->SETCAP.U32 = setcap;\
   basePointer->LFOCONTROL.U32 = lfocontrol;\
} while(0)


/// @fn _SI32_RTC_B_write_config(SI32_RTC_B_Type* basePointer,
///      uint32_t config)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///  Write to CONFIG register.
///
void
_SI32_RTC_B_write_config(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*config*/);
///
/// @def SI32_RTC_B_write_config(basePointer, config)
#define SI32_RTC_B_write_config(basePointer, config) \
   (basePointer->CONFIG.U32 = config)


/// @fn _SI32_RTC_B_read_config(SI32_RTC_B_Type* basePointer)
///
/// @return
///  Read CONFIG register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_config(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_config(basePointer)
#define SI32_RTC_B_read_config(basePointer) \
(basePointer->CONFIG.U32)


/// @fn _SI32_RTC_B_enable_alarm0_auto_reset(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_alarm0_auto_reset(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_alarm0_auto_reset(basePointer)
#define SI32_RTC_B_enable_alarm0_auto_reset(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_ALM0AREN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_alarm0_auto_reset(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_alarm0_auto_reset(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_alarm0_auto_reset(basePointer)
#define SI32_RTC_B_disable_alarm0_auto_reset(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_ALM0AREN_MASK)


/// @fn _SI32_RTC_B_start_timer(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_start_timer(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_start_timer(basePointer)
#define SI32_RTC_B_start_timer(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_RUN_START_U32)


/// @fn _SI32_RTC_B_stop_timer(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_stop_timer(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_stop_timer(basePointer)
#define SI32_RTC_B_stop_timer(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_RUN_MASK)


/// @fn _SI32_RTC_B_enable_missing_clock_detector(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_missing_clock_detector(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_missing_clock_detector(basePointer)
#define SI32_RTC_B_enable_missing_clock_detector(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_MCLKEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_missing_clock_detector(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_missing_clock_detector(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_missing_clock_detector(basePointer)
#define SI32_RTC_B_disable_missing_clock_detector(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_MCLKEN_MASK)


/// @fn _SI32_RTC_B_enable_autostep(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_autostep(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_autostep(basePointer)
#define SI32_RTC_B_enable_autostep(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_ASEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_autostep(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_autostep(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_autostep(basePointer)
#define SI32_RTC_B_disable_autostep(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_ASEN_MASK)


/// @fn _SI32_RTC_B_set_rtc_load_capacitance(SI32_RTC_B_Type* basePointer,
///      uint32_t rtclc)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  rtclc
///  Valid range is 4 bits.
///
void
_SI32_RTC_B_set_rtc_load_capacitance(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*rtclc*/);
///
/// @def SI32_RTC_B_set_rtc_load_capacitance(basePointer, rtclc)
#define SI32_RTC_B_set_rtc_load_capacitance(basePointer, rtclc) do{  \
   basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_RTCLC_MASK;\
   basePointer->CONFIG_SET = (rtclc << SI32_RTC_B_CONFIG_RTCLC_SHIFT);\
} while(0)


/// @fn _SI32_RTC_B_enable_bias_doubler(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_bias_doubler(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_bias_doubler(basePointer)
#define SI32_RTC_B_enable_bias_doubler(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_BDEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_bias_doubler(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_bias_doubler(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_bias_doubler(basePointer)
#define SI32_RTC_B_disable_bias_doubler(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_BDEN_MASK)


/// @fn _SI32_RTC_B_enable_crystal_oscillator(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_crystal_oscillator(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_crystal_oscillator(basePointer)
#define SI32_RTC_B_enable_crystal_oscillator(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_CRYSEN_MASK)


/// @fn _SI32_RTC_B_disable_crystal_oscillator(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_crystal_oscillator(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_crystal_oscillator(basePointer)
#define SI32_RTC_B_disable_crystal_oscillator(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_CRYSEN_MASK)


/// @fn _SI32_RTC_B_enable_auto_gain_control(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_auto_gain_control(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_auto_gain_control(basePointer)
#define SI32_RTC_B_enable_auto_gain_control(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_AGCEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_auto_gain_control(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_auto_gain_control(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_auto_gain_control(basePointer)
#define SI32_RTC_B_disable_auto_gain_control(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_AGCEN_MASK)


/// @fn _SI32_RTC_B_enable_alarm0(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_alarm0(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_alarm0(basePointer)
#define SI32_RTC_B_enable_alarm0(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_ALM0EN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_alarm0(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_alarm0(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_alarm0(basePointer)
#define SI32_RTC_B_disable_alarm0(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_ALM0EN_MASK)


/// @fn _SI32_RTC_B_is_alarm0_enabled(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_alarm0_enabled(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_alarm0_enabled(basePointer)
#define SI32_RTC_B_is_alarm0_enabled(basePointer) \
((bool)(basePointer->CONFIG.ALM0EN))


/// @fn _SI32_RTC_B_enable_alarm1(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_alarm1(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_alarm1(basePointer)
#define SI32_RTC_B_enable_alarm1(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_ALM1EN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_alarm1(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_alarm1(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_alarm1(basePointer)
#define SI32_RTC_B_disable_alarm1(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_ALM1EN_MASK)


/// @fn _SI32_RTC_B_is_alarm1_enabled(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_alarm1_enabled(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_alarm1_enabled(basePointer)
#define SI32_RTC_B_is_alarm1_enabled(basePointer) \
((bool)(basePointer->CONFIG.ALM1EN))


/// @fn _SI32_RTC_B_enable_alarm2(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_alarm2(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_alarm2(basePointer)
#define SI32_RTC_B_enable_alarm2(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_ALM2EN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_alarm2(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_alarm2(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_alarm2(basePointer)
#define SI32_RTC_B_disable_alarm2(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_ALM2EN_MASK)


/// @fn _SI32_RTC_B_is_alarm2_enabled(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_alarm2_enabled(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_alarm2_enabled(basePointer)
#define SI32_RTC_B_is_alarm2_enabled(basePointer) \
((bool)(basePointer->CONFIG.ALM2EN))


/// @fn _SI32_RTC_B_enable_clock_out(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_clock_out(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_clock_out(basePointer)
#define SI32_RTC_B_enable_clock_out(basePointer) \
   (basePointer->CONFIG_SET =SI32_RTC_B_CONFIG_CLKOEN_MASK)


/// @fn _SI32_RTC_B_disable_clock_out(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_clock_out(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_clock_out(basePointer)
#define SI32_RTC_B_disable_clock_out(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_CLKOEN_MASK)


/// @fn _SI32_RTC_B_enable_external_pin_clock_drive(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_external_pin_clock_drive(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_external_pin_clock_drive(basePointer)
#define SI32_RTC_B_enable_external_pin_clock_drive(basePointer) \
   (basePointer->CONFIG_SET =SI32_RTC_B_CONFIG_RTCOEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_external_pin_clock_drive(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_external_pin_clock_drive(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_external_pin_clock_drive(basePointer)
#define SI32_RTC_B_disable_external_pin_clock_drive(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_RTCOEN_MASK)


/// @fn _SI32_RTC_B_set_clock_source_rtc(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_set_clock_source_rtc(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_set_clock_source_rtc(basePointer)
#define SI32_RTC_B_set_clock_source_rtc(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_CLKSEL_MASK)


/// @fn _SI32_RTC_B_set_clock_source_lfo(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_set_clock_source_lfo(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_set_clock_source_lfo(basePointer)
#define SI32_RTC_B_set_clock_source_lfo(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_CLKSEL_LFOSCN_U32)


/// @fn _SI32_RTC_B_enable_rtc_timer(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_rtc_timer(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_rtc_timer(basePointer)
#define SI32_RTC_B_enable_rtc_timer(basePointer) \
   (basePointer->CONFIG_SET = SI32_RTC_B_CONFIG_RTCEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_rtc_timer(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_rtc_timer(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_rtc_timer(basePointer)
#define SI32_RTC_B_disable_rtc_timer(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RTC_B_CONFIG_RTCEN_MASK)


/// @fn _SI32_RTC_B_write_control(SI32_RTC_B_Type* basePointer,
///      uint32_t control)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 32 bits.
///  Write to CONTROL register.
///
void
_SI32_RTC_B_write_control(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_RTC_B_write_control(basePointer, control)
#define SI32_RTC_B_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control)


/// @fn _SI32_RTC_B_read_control(SI32_RTC_B_Type* basePointer)
///
/// @return
///  Read CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_control(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_control(basePointer)
#define SI32_RTC_B_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_RTC_B_is_alarm0_interrupt_pending(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = Interrupt pending; False = Interrupt not pending.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_alarm0_interrupt_pending(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_alarm0_interrupt_pending(basePointer)
#define SI32_RTC_B_is_alarm0_interrupt_pending(basePointer) \
((bool)(basePointer->CONTROL.ALM0I))


/// @fn _SI32_RTC_B_is_alarm1_interrupt_pending(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = Interrupt pending; False = Interrupt not pending.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_alarm1_interrupt_pending(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_alarm1_interrupt_pending(basePointer)
#define SI32_RTC_B_is_alarm1_interrupt_pending(basePointer) \
((bool)(basePointer->CONTROL.ALM1I))


/// @fn _SI32_RTC_B_is_alarm2_interrupt_pending(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = Interrupt pending; False = Interrupt not pending.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_alarm2_interrupt_pending(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_alarm2_interrupt_pending(basePointer)
#define SI32_RTC_B_is_alarm2_interrupt_pending(basePointer) \
((bool)(basePointer->CONTROL.ALM2I))


/// @fn _SI32_RTC_B_start_timer_set(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_start_timer_set(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_start_timer_set(basePointer)
#define SI32_RTC_B_start_timer_set(basePointer) \
   (basePointer->CONTROL_SET = SI32_RTC_B_CONTROL_TMRSET_SET_U32)


/// @fn _SI32_RTC_B_is_timer_set_in_progress(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = In progress; False = Not in progress.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_timer_set_in_progress(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_timer_set_in_progress(basePointer)
#define SI32_RTC_B_is_timer_set_in_progress(basePointer) \
((bool)(basePointer->CONTROL.TMRSET))


/// @fn _SI32_RTC_B_start_timer_capture(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_start_timer_capture(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_start_timer_capture(basePointer)
#define SI32_RTC_B_start_timer_capture(basePointer) \
   (basePointer->CONTROL_SET = SI32_RTC_B_CONTROL_TMRCAP_SET_U32)


/// @fn _SI32_RTC_B_is_timer_capture_in_progress(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = In progress; False = Not in progress.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_timer_capture_in_progress(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_timer_capture_in_progress(basePointer)
#define SI32_RTC_B_is_timer_capture_in_progress(basePointer) \
((bool)(basePointer->CONTROL.TMRCAP))


/// @fn _SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_clear_alarm0_interrupt(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_clear_alarm0_interrupt(basePointer)
#define SI32_RTC_B_clear_alarm0_interrupt(basePointer) \
   (basePointer->CONTROL_CLR = SI32_RTC_B_CONTROL_ALM0I_MASK)


/// @fn _SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_clear_alarm1_interrupt(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_clear_alarm1_interrupt(basePointer)
#define SI32_RTC_B_clear_alarm1_interrupt(basePointer) \
   (basePointer->CONTROL_CLR = SI32_RTC_B_CONTROL_ALM1I_MASK)


/// @fn _SI32_RTC_B_clear_alarm2_interrupt(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_clear_alarm2_interrupt(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_clear_alarm2_interrupt(basePointer)
#define SI32_RTC_B_clear_alarm2_interrupt(basePointer) \
   (basePointer->CONTROL_CLR = SI32_RTC_B_CONTROL_ALM2I_MASK)


/// @fn _SI32_RTC_B_is_external_oscillator_valid(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = Valid; False = Invalid.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_external_oscillator_valid(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_external_oscillator_valid(basePointer)
#define SI32_RTC_B_is_external_oscillator_valid(basePointer) \
((bool)(basePointer->CONTROL.CLKVF))


/// @fn _SI32_RTC_B_is_oscillator_running(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = Running; False = Not running.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_oscillator_running(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_oscillator_running(basePointer)
#define SI32_RTC_B_is_oscillator_running(basePointer) \
((bool)(basePointer->CONTROL.OSCFI == SI32_RTC_B_CONTROL_OSCFI_NOT_SET_VALUE))


/// @fn _SI32_RTC_B_clear_oscillator_fail_flag(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_clear_oscillator_fail_flag(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_clear_oscillator_fail_flag(basePointer)
#define SI32_RTC_B_clear_oscillator_fail_flag(basePointer) \
   (basePointer->CONTROL_CLR = SI32_RTC_B_CONTROL_OSCFI_MASK)


/// @fn _SI32_RTC_B_enable_high_speed_mode(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_high_speed_mode(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_high_speed_mode(basePointer)
#define SI32_RTC_B_enable_high_speed_mode(basePointer) \
   (basePointer->CONTROL_SET = SI32_RTC_B_CONTROL_HSMDEN_ENABLED_U32)


/// @fn _SI32_RTC_B_disable_high_speed_mode(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_high_speed_mode(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_high_speed_mode(basePointer)
#define SI32_RTC_B_disable_high_speed_mode(basePointer) \
   (basePointer->CONTROL_CLR = SI32_RTC_B_CONTROL_HSMDEN_MASK)


/// @fn _SI32_RTC_B_is_load_capacitance_ready(SI32_RTC_B_Type* basePointer)
///
/// @return
///  True = Ready; False = Not Ready.
///
/// @param[in]
///  basePointer
///
bool
_SI32_RTC_B_is_load_capacitance_ready(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_is_load_capacitance_ready(basePointer)
#define SI32_RTC_B_is_load_capacitance_ready(basePointer) \
((bool)(basePointer->CONTROL.LRDYF))


/// @fn _SI32_RTC_B_write_alarm0(SI32_RTC_B_Type* basePointer,
///      uint32_t alarm0)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  alarm0
///  Valid range is 32 bits.
///  Write to ALARM0 register.
///
void
_SI32_RTC_B_write_alarm0(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*alarm0*/);
///
/// @def SI32_RTC_B_write_alarm0(basePointer, alarm0)
#define SI32_RTC_B_write_alarm0(basePointer, alarm0) \
   (basePointer->ALARM0.U32 = alarm0)


/// @fn _SI32_RTC_B_read_alarm0(SI32_RTC_B_Type* basePointer)
///
/// @return
///  Read ALARM0 register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_alarm0(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_alarm0(basePointer)
#define SI32_RTC_B_read_alarm0(basePointer) \
(basePointer->ALARM0.U32)


/// @fn _SI32_RTC_B_write_alarm1(SI32_RTC_B_Type* basePointer,
///      uint32_t alarm1)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  alarm1
///  Valid range is 32 bits.
///  Write to ALARM1 register.
///
void
_SI32_RTC_B_write_alarm1(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*alarm1*/);
///
/// @def SI32_RTC_B_write_alarm1(basePointer, alarm1)
#define SI32_RTC_B_write_alarm1(basePointer, alarm1) \
   (basePointer->ALARM1.U32 = alarm1)


/// @fn _SI32_RTC_B_read_alarm1(SI32_RTC_B_Type* basePointer)
///
/// @return
///  Read ALARM1 register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_alarm1(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_alarm1(basePointer)
#define SI32_RTC_B_read_alarm1(basePointer) \
(basePointer->ALARM1.U32)


/// @fn _SI32_RTC_B_write_alarm2(SI32_RTC_B_Type* basePointer,
///      uint32_t alarm2)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  alarm2
///  Valid range is 32 bits.
///  Write to ALARM2 register.
///
void
_SI32_RTC_B_write_alarm2(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*alarm2*/);
///
/// @def SI32_RTC_B_write_alarm2(basePointer, alarm2)
#define SI32_RTC_B_write_alarm2(basePointer, alarm2) \
   (basePointer->ALARM2.U32 = alarm2)


/// @fn _SI32_RTC_B_read_alarm2(SI32_RTC_B_Type* basePointer)
///
/// @return
///  Read ALARM2 register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_alarm2(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_alarm2(basePointer)
#define SI32_RTC_B_read_alarm2(basePointer) \
(basePointer->ALARM2.U32)


/// @fn _SI32_RTC_B_write_setcap(SI32_RTC_B_Type* basePointer,
///      uint32_t setcap)
///
/// @brief
/// Set and poll TMRSET after writing to SETCAP.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  setcap
///  Valid range is 32 bits.
///  Write to SETCAP register.
///
void
_SI32_RTC_B_write_setcap(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*setcap*/);
///
/// @def SI32_RTC_B_write_setcap(basePointer, setcap)
#define SI32_RTC_B_write_setcap(basePointer, setcap) \
   (basePointer->SETCAP.U32 = setcap)


/// @fn _SI32_RTC_B_read_setcap(SI32_RTC_B_Type* basePointer)
///
/// @brief
/// Set and poll TMRCAP before reading SETCAP.
///
/// @return
///  Read SETCAP register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_setcap(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_setcap(basePointer)
#define SI32_RTC_B_read_setcap(basePointer) \
(basePointer->SETCAP.U32)


/// @fn _SI32_RTC_B_write_lfocontrol(SI32_RTC_B_Type* basePointer,
///      uint32_t lfocontrol)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  lfocontrol
///  Valid range is 32 bits.
///  Write to LFOCONTROL register.
///
void
_SI32_RTC_B_write_lfocontrol(SI32_RTC_B_Type* /*basePointer*/,
   uint32_t /*lfocontrol*/);
///
/// @def SI32_RTC_B_write_lfocontrol(basePointer, lfocontrol)
#define SI32_RTC_B_write_lfocontrol(basePointer, lfocontrol) \
   (basePointer->LFOCONTROL.U32 = lfocontrol)


/// @fn _SI32_RTC_B_read_lfocontrol(SI32_RTC_B_Type* basePointer)
///
/// @return
///  Read LFOCONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RTC_B_read_lfocontrol(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_read_lfocontrol(basePointer)
#define SI32_RTC_B_read_lfocontrol(basePointer) \
(basePointer->LFOCONTROL.U32)


/// @fn _SI32_RTC_B_enable_low_frequency_oscillator_output(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_low_frequency_oscillator_output(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_low_frequency_oscillator_output(basePointer)
#define SI32_RTC_B_enable_low_frequency_oscillator_output(basePointer) \
   (basePointer->LFOCONTROL.LFOOEN = SI32_RTC_B_LFOCONTROL_LFOOEN_ENABLED_VALUE)


/// @fn _SI32_RTC_B_disable_low_frequency_oscillator_output(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_low_frequency_oscillator_output(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_low_frequency_oscillator_output(basePointer)
#define SI32_RTC_B_disable_low_frequency_oscillator_output(basePointer) \
   (basePointer->LFOCONTROL.LFOOEN = SI32_RTC_B_LFOCONTROL_LFOOEN_DISABLED_VALUE)


/// @fn _SI32_RTC_B_enable_low_frequency_oscillator(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_enable_low_frequency_oscillator(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_enable_low_frequency_oscillator(basePointer)
#define SI32_RTC_B_enable_low_frequency_oscillator(basePointer) \
   (basePointer->LFOCONTROL.LFOSCEN = SI32_RTC_B_LFOCONTROL_LFOSCEN_ENABLED_VALUE)


/// @fn _SI32_RTC_B_disable_low_frequency_oscillator(SI32_RTC_B_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RTC_B_disable_low_frequency_oscillator(SI32_RTC_B_Type* /*basePointer*/);
///
/// @def SI32_RTC_B_disable_low_frequency_oscillator(basePointer)
#define SI32_RTC_B_disable_low_frequency_oscillator(basePointer) \
   (basePointer->LFOCONTROL.LFOSCEN = SI32_RTC_B_LFOCONTROL_LFOSCEN_DISABLED_VALUE)



#ifdef __cplusplus
}
#endif

#endif // __SI32_RTC_B_TYPE_H__

//-eof--------------------------------------------------------------------------
