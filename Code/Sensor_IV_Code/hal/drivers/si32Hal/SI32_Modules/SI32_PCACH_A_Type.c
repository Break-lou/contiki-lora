//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_PCACH_A_Type.c
//
// Script: 0.58
// HAL Source: 0.2
// Version: 5

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_PCACH_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_PCACH_A_initialize
//
// Writes all PCACH registers.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_initialize(
   SI32_PCACH_A_Type * basePointer,
   uint32_t mode,
   uint32_t control,
   uint32_t ccapv,
   uint32_t ccapvupd)
{
   //{{
   basePointer->MODE.U32 = mode;
   basePointer->CONTROL.U32 = control;
   basePointer->CCAPV.U32 = ccapv;
   basePointer->CCAPVUPD.U32 = ccapvupd;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_write_mode
//
// Writes to MODE register.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_write_mode(
   SI32_PCACH_A_Type * basePointer,
   uint32_t mode)
{
   //{{
   basePointer->MODE.U32 = mode;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_read_mode
//
// Reads MODE register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PCACH_A_read_mode(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   return basePointer->MODE.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_output_mode_toggle
//
// Toggle channel output at the next capture/compare event.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_output_mode_toggle(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.COSEL = SI32_PCACH_A_MODE_COSEL_TOGGLE_OUTPUT_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_output_mode_set
//
// Set the channel output at the next capture/compare event.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_output_mode_set(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.COSEL = SI32_PCACH_A_MODE_COSEL_SET_OUTPUT_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_output_mode_clear
//
// Clear the channel output at the next capture/compare event.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_output_mode_clear(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.COSEL = SI32_PCACH_A_MODE_COSEL_CLEAR_OUTPUT_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_output_mode_none
//
// Capture/compare events do not control the output state.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_output_mode_none(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.COSEL = SI32_PCACH_A_MODE_COSEL_NO_CHANGE_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_set_width_for_n_bit_edge_aligned_pwm_mode
//
// This field represents the n-bit PWM for this channel. When in n-bit
// PWM mode, the channel will behave as if the PCA Counter/Timer is only
// n bits wide.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_set_width_for_n_bit_edge_aligned_pwm_mode(
   SI32_PCACH_A_Type * basePointer,
   uint32_t nbits)
{
   assert(nbits < 16);   // nbits < 2^4
   //{{
   basePointer->MODE.PWMMD = nbits;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_operating_mode_edge_aligned_pwm
//
// Configure the channel for edge-aligned PWM mode.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_operating_mode_edge_aligned_pwm(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.CMD = SI32_PCACH_A_MODE_CMD_EDGE_PWM_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_operating_mode_center_aligned_pwm
//
// Configure the channel for center-aligned PWM mode.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_operating_mode_center_aligned_pwm(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.CMD = SI32_PCACH_A_MODE_CMD_CENTER_ALIGNED_PWM_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_operating_mode_high_frequency_square_wave
//
// Configure the channel for high-frequency/square-wave mode.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_operating_mode_high_frequency_square_wave(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.CMD =SI32_PCACH_A_MODE_CMD_HF_SQUARE_WAVE_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_operating_mode_timer_capture
//
// Configure the channel for timer/capture mode.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_operating_mode_timer_capture(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.CMD = SI32_PCACH_A_MODE_CMD_TIMER_CAPTURE_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_select_operating_mode_n_bit_edge_aligned_pwm
//
// Configure the channel for n-bit edge-aligned PWM mode.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_select_operating_mode_n_bit_edge_aligned_pwm(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->MODE.CMD = SI32_PCACH_A_MODE_CMD_N_BIT_PWM_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_write_control
//
// Writes to CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_write_control(
   SI32_PCACH_A_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_read_control
//
// Reads CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PCACH_A_read_control(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_clear_output_state
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_clear_output_state(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PCACH_A_CONTROL_COUTST_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_set_output_state
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_set_output_state(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PCACH_A_CONTROL_COUTST_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_get_output_state
//
//-----------------------------------------------------------------------------
bool
_SI32_PCACH_A_get_output_state(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.COUTST);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_enable_positive_edge_input_capture
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_enable_positive_edge_input_capture(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PCACH_A_CONTROL_CPCAPEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_disable_positive_edge_input_capture
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_disable_positive_edge_input_capture(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PCACH_A_CONTROL_CPCAPEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_enable_negative_edge_input_capture
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_enable_negative_edge_input_capture(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PCACH_A_CONTROL_CNCAPEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_disable_negative_edge_input_capture
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_disable_negative_edge_input_capture(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PCACH_A_CONTROL_CNCAPEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_is_register_update_busy
//
//-----------------------------------------------------------------------------
bool
_SI32_PCACH_A_is_register_update_busy(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.CUPDCF);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_enable_capture_compare_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_enable_capture_compare_interrupt(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PCACH_A_CONTROL_CCIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_disable_capture_compare_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_disable_capture_compare_interrupt(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PCACH_A_CONTROL_CCIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_is_capture_compare_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_PCACH_A_is_capture_compare_interrupt_enabled(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONTROL.CCIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_enable_intermediate_overflow_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_enable_intermediate_overflow_interrupt(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_PCACH_A_CONTROL_CIOVFIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_disable_intermediate_overflow_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_disable_intermediate_overflow_interrupt(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_PCACH_A_CONTROL_CIOVFIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_is_intermediate_overflow_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_PCACH_A_is_intermediate_overflow_interrupt_enabled(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONTROL.CIOVFIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_write_ccapv
//
// Writes to CCAPV register.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_write_ccapv(
   SI32_PCACH_A_Type * basePointer,
   uint32_t ccapv)
{
   //{{
   basePointer->CCAPV.U32 = ccapv;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_read_ccapv
//
// Reads CCAPV register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PCACH_A_read_ccapv(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   return (uint32_t)(basePointer->CCAPV.U32);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_write_ccapvupd
//
// Writes to  CCAPVUPD register.
//-----------------------------------------------------------------------------
void
_SI32_PCACH_A_write_ccapvupd(
   SI32_PCACH_A_Type * basePointer,
   uint32_t ccapvupd)
{
   //{{
   basePointer->CCAPVUPD.U32 = ccapvupd;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_PCACH_A_read_ccapvupd
//
// Reads CCAPVUPD register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_PCACH_A_read_ccapvupd(
   SI32_PCACH_A_Type * basePointer)
{
   //{{
   return (uint32_t)(basePointer->CCAPVUPD.U32);
   //}}
}


//-eof--------------------------------------------------------------------------
