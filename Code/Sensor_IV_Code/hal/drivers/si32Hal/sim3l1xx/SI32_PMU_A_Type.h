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
/// @file SI32_PMU_A_Type.h
//
// This file applies to the SIM3L1XX_PMU_A module
//
// Script: 0.59
// HAL Source: 0.9
// Version: 1

#ifndef __SI32_PMU_A_TYPE_H__
#define __SI32_PMU_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3L1XX_PMU_A_Registers.h"
#include "SI32_PMU_A_Support.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_PMU_A_initialize(SI32_PMU_A_Type* basePointer,
///      uint32_t control,
///      uint32_t config,
///      uint32_t wakeen,
///      uwide16_t pwen,
///      uwide16_t pwpol)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 24 bits.
///
/// @param[in]
///  config
///  Valid range is 16 bits.
///
/// @param[in]
///  wakeen
///  Valid range is 9 bits.
///
/// @param[in]
///  pwen
///  Valid range is 16 bits.
///
/// @param[in]
///  pwpol
///  Valid range is 16 bits.
///
void
_SI32_PMU_A_initialize(SI32_PMU_A_Type* /*basePointer*/,
   uint32_t, /*control*/
   uint32_t, /*config*/
   uint32_t, /*wakeen*/
   uwide16_t, /*pwen*/
   uwide16_t /*pwpol*/);
///
/// @def SI32_PMU_A_initialize(basePointer, control, config, wakeen, pwen, pwpol)
#define SI32_PMU_A_initialize(basePointer, control, config, wakeen, pwen, pwpol) do{  \
   basePointer->CONTROL.U32 = control & 0x00FF0079;\
   basePointer->CONFIG.U32 =\
      (((basePointer->CONFIG.U32)&~0x00000D70)\
      |(config&0x00000D70));\
   basePointer->WAKEEN.U32 = wakeen;\
   basePointer->PWEN.U32 = pwen;\
   basePointer->PWPOL.U32 = pwpol;\
} while(0)


/// @fn _SI32_PMU_A_read_control(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Read CONTROL register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_PMU_A_read_control(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_read_control(basePointer)
#define SI32_PMU_A_read_control(basePointer) \
(basePointer->CONTROL.U32)


/// @fn _SI32_PMU_A_write_control(SI32_PMU_A_Type* basePointer,
///      uint32_t control)
///
/// @brief
/// Write to CONTROL register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  control
///  Valid range is 24 bits.
///
void
_SI32_PMU_A_write_control(SI32_PMU_A_Type* /*basePointer*/,
   uint32_t /*control*/);
///
/// @def SI32_PMU_A_write_control(basePointer, control)
#define SI32_PMU_A_write_control(basePointer, control) \
   (basePointer->CONTROL.U32 = control & 0x00FF0079)


/// @fn _SI32_PMU_A_clear_wakeup_flags(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Clears all PMU status flags.
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_clear_wakeup_flags(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_clear_wakeup_flags(basePointer)
#define SI32_PMU_A_clear_wakeup_flags(basePointer) do{  \
     basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_WAKECLR_MASK;\
     basePointer->STATUS_CLR  = (SI32_PMU_A_STATUS_PM8EF_MASK\
         | SI32_PMU_A_STATUS_PORF_MASK);\
} while(0)


/// @fn _SI32_PMU_A_enable_pin_wake(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_pin_wake(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_pin_wake(basePointer)
#define SI32_PMU_A_enable_pin_wake(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_PWAKEEN_MASK)


/// @fn _SI32_PMU_A_disable_pin_wake(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_pin_wake(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_pin_wake(basePointer)
#define SI32_PMU_A_disable_pin_wake(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_PWAKEEN_MASK)


/// @fn _SI32_PMU_A_enable_asleep_pin_out(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_asleep_pin_out(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_asleep_pin_out(basePointer)
#define SI32_PMU_A_enable_asleep_pin_out(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_PMUASLPEN_MASK)


/// @fn _SI32_PMU_A_disable_asleep_pin_out(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_asleep_pin_out(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_asleep_pin_out(basePointer)
#define SI32_PMU_A_disable_asleep_pin_out(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_PMUASLPEN_MASK)


/// @fn _SI32_PMU_A_enable_low_power_charge_pump_monitor(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_low_power_charge_pump_monitor(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_low_power_charge_pump_monitor(basePointer)
#define SI32_PMU_A_enable_low_power_charge_pump_monitor(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_CPMONEN_MASK)


/// @fn _SI32_PMU_A_disable_low_power_charge_pump_monitor(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_low_power_charge_pump_monitor(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_low_power_charge_pump_monitor(basePointer)
#define SI32_PMU_A_disable_low_power_charge_pump_monitor(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_CPMONEN_MASK)


/// @fn _SI32_PMU_A_enable_low_power_charge_pump_monitor_interrupt(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_low_power_charge_pump_monitor_interrupt(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_low_power_charge_pump_monitor_interrupt(basePointer)
#define SI32_PMU_A_enable_low_power_charge_pump_monitor_interrupt(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_CPMONIEN_MASK)


/// @fn _SI32_PMU_A_disable_low_power_charge_pump_monitor_interrupt(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_low_power_charge_pump_monitor_interrupt(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_low_power_charge_pump_monitor_interrupt(basePointer)
#define SI32_PMU_A_disable_low_power_charge_pump_monitor_interrupt(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_CPMONIEN_MASK)


/// @fn _SI32_PMU_A_enable_ram_0_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_0_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_0_retention(basePointer)
#define SI32_PMU_A_enable_ram_0_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM0REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_0_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_0_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_0_retention(basePointer)
#define SI32_PMU_A_disable_ram_0_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM0REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_1_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_1_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_1_retention(basePointer)
#define SI32_PMU_A_enable_ram_1_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM1REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_1_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_1_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_1_retention(basePointer)
#define SI32_PMU_A_disable_ram_1_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM1REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_2_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_2_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_2_retention(basePointer)
#define SI32_PMU_A_enable_ram_2_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM2REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_2_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_2_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_2_retention(basePointer)
#define SI32_PMU_A_disable_ram_2_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM2REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_3_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_3_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_3_retention(basePointer)
#define SI32_PMU_A_enable_ram_3_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM3REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_3_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_3_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_3_retention(basePointer)
#define SI32_PMU_A_disable_ram_3_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM3REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_4_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_4_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_4_retention(basePointer)
#define SI32_PMU_A_enable_ram_4_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM4REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_4_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_4_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_4_retention(basePointer)
#define SI32_PMU_A_disable_ram_4_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM4REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_5_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_5_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_5_retention(basePointer)
#define SI32_PMU_A_enable_ram_5_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM5REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_5_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_5_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_5_retention(basePointer)
#define SI32_PMU_A_disable_ram_5_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM5REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_6_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_6_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_6_retention(basePointer)
#define SI32_PMU_A_enable_ram_6_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM6REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_6_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_6_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_6_retention(basePointer)
#define SI32_PMU_A_disable_ram_6_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM6REN_MASK)


/// @fn _SI32_PMU_A_enable_ram_7_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_ram_7_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_ram_7_retention(basePointer)
#define SI32_PMU_A_enable_ram_7_retention(basePointer) \
   (basePointer->CONTROL_SET = SI32_PMU_A_CONTROL_RAM7REN_MASK)


/// @fn _SI32_PMU_A_disable_ram_7_retention(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_ram_7_retention(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_ram_7_retention(basePointer)
#define SI32_PMU_A_disable_ram_7_retention(basePointer) \
   (basePointer->CONTROL_CLR = SI32_PMU_A_CONTROL_RAM7REN_MASK)


/// @fn _SI32_PMU_A_set_ram_retention_enable_mask(SI32_PMU_A_Type* basePointer,
///      uwide8_t mask)
///
/// @brief
/// Write mask to RAMxREN bits.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  mask
///  Valid range is 8 bits.
///
void
_SI32_PMU_A_set_ram_retention_enable_mask(SI32_PMU_A_Type* /*basePointer*/,
   uwide8_t /*mask*/);
///
/// @def SI32_PMU_A_set_ram_retention_enable_mask(basePointer, mask)
#define SI32_PMU_A_set_ram_retention_enable_mask(basePointer, mask) do{  \
   basePointer->CONTROL.U32 =\
      ((basePointer->CONTROL.U32) & 0xFF00FFFF)\
      |(mask<<SI32_PMU_A_CONTROL_RAM0REN_SHIFT);\
} while(0)


/// @fn _SI32_PMU_A_read_config(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Read CONFIG register.
///
/// @param[in]
///  basePointer
///
uwide16_t
_SI32_PMU_A_read_config(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_read_config(basePointer)
#define SI32_PMU_A_read_config(basePointer) \
(basePointer->CONFIG.U32)


/// @fn _SI32_PMU_A_write_config(SI32_PMU_A_Type* basePointer,
///      uwide16_t config)
///
/// @brief
/// Write to CONFIG register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 16 bits.
///
void
_SI32_PMU_A_write_config(SI32_PMU_A_Type* /*basePointer*/,
   uwide16_t /*config*/);
///
/// @def SI32_PMU_A_write_config(basePointer, config)
#define SI32_PMU_A_write_config(basePointer, config) do{  \
   basePointer->CONFIG.U32 =\
      (((basePointer->CONFIG.U32)&~0x00000D70)\
      |(config&0x00000D70));\
} while(0)


/// @fn _SI32_PMU_A_select_vdrv_connected_to_vbat(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_select_vdrv_connected_to_vbat(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_select_vdrv_connected_to_vbat(basePointer)
#define SI32_PMU_A_select_vdrv_connected_to_vbat(basePointer) \
   (basePointer->CONFIG.VDRVSMD = SI32_PMU_A_CONFIG_VDRVSMD_VBAT_VALUE)


/// @fn _SI32_PMU_A_select_vdrv_connected_to_vdc(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_select_vdrv_connected_to_vdc(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_select_vdrv_connected_to_vdc(basePointer)
#define SI32_PMU_A_select_vdrv_connected_to_vdc(basePointer) \
   (basePointer->CONFIG.VDRVSMD = SI32_PMU_A_CONFIG_VDRVSMD_VDC_VALUE)


/// @fn _SI32_PMU_A_select_vdrv_high_impedence(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_select_vdrv_high_impedence(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_select_vdrv_high_impedence(basePointer)
#define SI32_PMU_A_select_vdrv_high_impedence(basePointer) \
   (basePointer->CONFIG.VDRVSMD = SI32_PMU_A_CONFIG_VDRVSMD_HIGHZ_VALUE)


/// @fn _SI32_PMU_A_enable_low_power_charge_pump(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_low_power_charge_pump(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_low_power_charge_pump(basePointer)
#define SI32_PMU_A_enable_low_power_charge_pump(basePointer) \
   (basePointer->CONFIG_SET = SI32_PMU_A_CONFIG_CPEN_MASK)


/// @fn _SI32_PMU_A_disable_low_power_charge_pump(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_low_power_charge_pump(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_low_power_charge_pump(basePointer)
#define SI32_PMU_A_disable_low_power_charge_pump(basePointer) \
   (basePointer->CONFIG_CLR = SI32_PMU_A_CONFIG_CPEN_MASK)


/// @fn _SI32_PMU_A_set_low_power_charge_pump_load(SI32_PMU_A_Type* basePointer,
///      uwide8_t load)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  load
///  Valid range is 2 bits.
///
void
_SI32_PMU_A_set_low_power_charge_pump_load(SI32_PMU_A_Type* /*basePointer*/,
   uwide8_t /*load*/);
///
/// @def SI32_PMU_A_set_low_power_charge_pump_load(basePointer, load)
#define SI32_PMU_A_set_low_power_charge_pump_load(basePointer, load) \
   (basePointer->CONFIG.CPLOAD = load)


/// @fn _SI32_PMU_A_read_status(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Returns STATUS register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_PMU_A_read_status(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_read_status(basePointer)
#define SI32_PMU_A_read_status(basePointer) \
(basePointer->STATUS.U32)


/// @fn _SI32_PMU_A_is_power_mode_8_exit_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_power_mode_8_exit_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_power_mode_8_exit_flag_set(basePointer)
#define SI32_PMU_A_is_power_mode_8_exit_flag_set(basePointer) \
((bool) basePointer->STATUS.PM8EF)


/// @fn _SI32_PMU_A_is_pin_wakeup_event_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_pin_wakeup_event_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_pin_wakeup_event_flag_set(basePointer)
#define SI32_PMU_A_is_pin_wakeup_event_flag_set(basePointer) \
((bool) basePointer->STATUS.PWAKEF)


/// @fn _SI32_PMU_A_is_power_on_reset_event_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_power_on_reset_event_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_power_on_reset_event_flag_set(basePointer)
#define SI32_PMU_A_is_power_on_reset_event_flag_set(basePointer) \
((bool) basePointer->STATUS.PORF)


/// @fn _SI32_PMU_A_is_low_power_charge_pump_voltage_above_threshold(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_low_power_charge_pump_voltage_above_threshold(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_low_power_charge_pump_voltage_above_threshold(basePointer)
#define SI32_PMU_A_is_low_power_charge_pump_voltage_above_threshold(basePointer) \
((bool) basePointer->STATUS.CPSTS)


/// @fn _SI32_PMU_A_read_wakeen(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Read WAKEEN register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_PMU_A_read_wakeen(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_read_wakeen(basePointer)
#define SI32_PMU_A_read_wakeen(basePointer) \
(basePointer->WAKEEN.U32)


/// @fn _SI32_PMU_A_write_wakeen(SI32_PMU_A_Type* basePointer,
///      uint32_t wakeen)
///
/// @brief
/// Write to WAKEEN register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  wakeen
///  Valid range is 9 bits.
///
void
_SI32_PMU_A_write_wakeen(SI32_PMU_A_Type* /*basePointer*/,
   uint32_t /*wakeen*/);
///
/// @def SI32_PMU_A_write_wakeen(basePointer, wakeen)
#define SI32_PMU_A_write_wakeen(basePointer, wakeen) \
   (basePointer->WAKEEN.U32 = wakeen)


/// @fn _SI32_PMU_A_enable_rtc0_fail_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_rtc0_fail_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_rtc0_fail_wake_event(basePointer)
#define SI32_PMU_A_enable_rtc0_fail_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_RTC0FWEN_MASK)


/// @fn _SI32_PMU_A_disable_rtc0_fail_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_rtc0_fail_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_rtc0_fail_wake_event(basePointer)
#define SI32_PMU_A_disable_rtc0_fail_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_RTC0FWEN_MASK)


/// @fn _SI32_PMU_A_enable_rtc0_alarm_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_rtc0_alarm_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_rtc0_alarm_wake_event(basePointer)
#define SI32_PMU_A_enable_rtc0_alarm_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_RTC0A0WEN_MASK)


/// @fn _SI32_PMU_A_disable_rtc0_alarm_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_rtc0_alarm_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_rtc0_alarm_wake_event(basePointer)
#define SI32_PMU_A_disable_rtc0_alarm_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_RTC0A0WEN_MASK)


/// @fn _SI32_PMU_A_enable_comparator0_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_comparator0_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_comparator0_wake_event(basePointer)
#define SI32_PMU_A_enable_comparator0_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_CMP0WEN_MASK)


/// @fn _SI32_PMU_A_disable_comparator0_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_comparator0_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_comparator0_wake_event(basePointer)
#define SI32_PMU_A_disable_comparator0_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_CMP0WEN_MASK)


/// @fn _SI32_PMU_A_enable_advanced_capture_counter_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_advanced_capture_counter_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_advanced_capture_counter_wake_event(basePointer)
#define SI32_PMU_A_enable_advanced_capture_counter_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_ACC0WEN_MASK)


/// @fn _SI32_PMU_A_disable_advanced_capture_counter_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_advanced_capture_counter_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_advanced_capture_counter_wake_event(basePointer)
#define SI32_PMU_A_disable_advanced_capture_counter_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_ACC0WEN_MASK)


/// @fn _SI32_PMU_A_enable_lcd_vbat_monitor_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_lcd_vbat_monitor_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_lcd_vbat_monitor_wake_event(basePointer)
#define SI32_PMU_A_enable_lcd_vbat_monitor_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_LCDMONWEN_MASK)


/// @fn _SI32_PMU_A_disable_lcd_vbat_monitor_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_lcd_vbat_monitor_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_lcd_vbat_monitor_wake_event(basePointer)
#define SI32_PMU_A_disable_lcd_vbat_monitor_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_LCDMONWEN_MASK)


/// @fn _SI32_PMU_A_enable_pin_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_pin_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_pin_wake_event(basePointer)
#define SI32_PMU_A_enable_pin_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_PWAKEWEN_MASK)


/// @fn _SI32_PMU_A_disable_pin_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_pin_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_pin_wake_event(basePointer)
#define SI32_PMU_A_disable_pin_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_PWAKEWEN_MASK)


/// @fn _SI32_PMU_A_enable_lptimer0_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_lptimer0_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_lptimer0_wake_event(basePointer)
#define SI32_PMU_A_enable_lptimer0_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_LPT0WEN_MASK)


/// @fn _SI32_PMU_A_disable_lptimer0_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_lptimer0_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_lptimer0_wake_event(basePointer)
#define SI32_PMU_A_disable_lptimer0_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_LPT0WEN_MASK)


/// @fn _SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_uart0_wake_event(basePointer)
#define SI32_PMU_A_enable_uart0_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_UART0WEN_MASK)


/// @fn _SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_uart0_wake_event(basePointer)
#define SI32_PMU_A_disable_uart0_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_UART0WEN_MASK)


/// @fn _SI32_PMU_A_enable_low_power_charge_pump_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_enable_low_power_charge_pump_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_enable_low_power_charge_pump_wake_event(basePointer)
#define SI32_PMU_A_enable_low_power_charge_pump_wake_event(basePointer) \
   (basePointer->WAKEEN_SET = SI32_PMU_A_WAKEEN_CPFWEN_MASK)


/// @fn _SI32_PMU_A_disable_low_power_charge_pump_wake_event(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_PMU_A_disable_low_power_charge_pump_wake_event(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_disable_low_power_charge_pump_wake_event(basePointer)
#define SI32_PMU_A_disable_low_power_charge_pump_wake_event(basePointer) \
   (basePointer->WAKEEN_CLR = SI32_PMU_A_WAKEEN_CPFWEN_MASK)


/// @fn _SI32_PMU_A_get_last_wakeup_source(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
SI32_PMU_Wakeup_Enum_Type
_SI32_PMU_A_get_last_wakeup_source(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_get_last_wakeup_source(basePointer)
#define SI32_PMU_A_get_last_wakeup_source(basePointer) \
   _SI32_PMU_A_get_last_wakeup_source(basePointer) 


/// @fn _SI32_PMU_A_is_rtc0_fail_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_rtc0_fail_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_rtc0_fail_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_rtc0_fail_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.RTC0FWF)


/// @fn _SI32_PMU_A_is_rtc0_alarm_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_rtc0_alarm_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_rtc0_alarm_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_rtc0_alarm_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.RTC0A0WF)


/// @fn _SI32_PMU_A_is_comparator0_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_comparator0_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_comparator0_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_comparator0_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.CMP0WF)


/// @fn _SI32_PMU_A_is_advance_capture_counter_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_advance_capture_counter_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_advance_capture_counter_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_advance_capture_counter_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.ACC0WF)


/// @fn _SI32_PMU_A_is_lcd_monitor_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_lcd_monitor_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_lcd_monitor_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_lcd_monitor_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.LCDMONWF)


/// @fn _SI32_PMU_A_is_pin_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_pin_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_pin_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_pin_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.PWAKEWF)


/// @fn _SI32_PMU_A_is_lptimer0_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_lptimer0_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_lptimer0_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_lptimer0_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.LPT0WF)


/// @fn _SI32_PMU_A_is_uart_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_uart_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_uart_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_uart_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.UART0WF)


/// @fn _SI32_PMU_A_is_low_power_charge_pump_wakeup_flag_set(SI32_PMU_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
bool
_SI32_PMU_A_is_low_power_charge_pump_wakeup_flag_set(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_is_low_power_charge_pump_wakeup_flag_set(basePointer)
#define SI32_PMU_A_is_low_power_charge_pump_wakeup_flag_set(basePointer) \
((bool) basePointer->WAKESTATUS.CPFWF)


/// @fn _SI32_PMU_A_read_pwen(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Read PWEN register.
///
/// @param[in]
///  basePointer
///
uwide16_t
_SI32_PMU_A_read_pwen(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_read_pwen(basePointer)
#define SI32_PMU_A_read_pwen(basePointer) \
(basePointer->PWEN.U32)


/// @fn _SI32_PMU_A_write_pwen(SI32_PMU_A_Type* basePointer,
///      uwide16_t pwen)
///
/// @brief
/// Write to PWEN register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  pwen
///  Valid range is 16 bits.
///
void
_SI32_PMU_A_write_pwen(SI32_PMU_A_Type* /*basePointer*/,
   uwide16_t /*pwen*/);
///
/// @def SI32_PMU_A_write_pwen(basePointer, pwen)
#define SI32_PMU_A_write_pwen(basePointer, pwen) \
   (basePointer->PWEN.U32 = pwen)


/// @fn _SI32_PMU_A_read_pwpol(SI32_PMU_A_Type* basePointer)
///
/// @brief
/// Read PWPOL register.
///
/// @param[in]
///  basePointer
///
uwide16_t
_SI32_PMU_A_read_pwpol(SI32_PMU_A_Type* /*basePointer*/);
///
/// @def SI32_PMU_A_read_pwpol(basePointer)
#define SI32_PMU_A_read_pwpol(basePointer) \
(basePointer->PWPOL.U32)


/// @fn _SI32_PMU_A_write_pwpol(SI32_PMU_A_Type* basePointer,
///      uwide16_t pwpol)
///
/// @brief
/// Write to PWPOL register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  pwpol
///  Valid range is 16 bits.
///
void
_SI32_PMU_A_write_pwpol(SI32_PMU_A_Type* /*basePointer*/,
   uwide16_t /*pwpol*/);
///
/// @def SI32_PMU_A_write_pwpol(basePointer, pwpol)
#define SI32_PMU_A_write_pwpol(basePointer, pwpol) \
   (basePointer->PWPOL.U32 = pwpol)


/// @fn _SI32_PMU_A_set_pin_wake_events(SI32_PMU_A_Type* basePointer,
///      uwide16_t pwen,
///      uwide16_t pwpol)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  pwen
///  Valid range is 16 bits.
///  Write to PWEN register.
///
/// @param[in]
///  pwpol
///  Valid range is 16 bits.
///  Write to PWPOL register.
///
void
_SI32_PMU_A_set_pin_wake_events(SI32_PMU_A_Type* /*basePointer*/,
   uwide16_t, /*pwen*/
   uwide16_t /*pwpol*/);
///
/// @def SI32_PMU_A_set_pin_wake_events(basePointer, pwen, pwpol)
#define SI32_PMU_A_set_pin_wake_events(basePointer, pwen, pwpol) do{  \
   basePointer->PWEN.U32 = pwen;\
   basePointer->PWPOL.U32 = pwpol;\
} while(0)



#ifdef __cplusplus
}
#endif

#endif // __SI32_PMU_A_TYPE_H__

//-eof--------------------------------------------------------------------------
