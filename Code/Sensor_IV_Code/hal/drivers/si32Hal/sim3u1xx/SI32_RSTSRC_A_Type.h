//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_RSTSRC_A_Type.h
//
// This file applies to the SIM3U1XX_RSTSRC_A module
//
// Script: 0.58
// HAL Source: 0.4
// Version: 1

#ifndef __SI32_RSTSRC_A_TYPE_H__
#define __SI32_RSTSRC_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3U1XX_RSTSRC_A_Registers.h"

// support definitions
#include "SI32_RSTSRC_A_Support.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_RSTSRC_A_initialize(SI32_RSTSRC_A_Type* basePointer,
///      uint32_t reseten)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  reseten
///  Valid range is 32 bits.
///  Write to RESETEN register.
///
void
_SI32_RSTSRC_A_initialize(SI32_RSTSRC_A_Type* /*basePointer*/,
   uint32_t /*reseten*/);
///
/// @def SI32_RSTSRC_A_initialize(basePointer, reseten)
#define SI32_RSTSRC_A_initialize(basePointer, reseten) \
   (basePointer->RESETEN.U32 = reseten)


/// @fn _SI32_RSTSRC_A_write_reseten(SI32_RSTSRC_A_Type* basePointer,
///      uint32_t reseten)
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  reseten
///  Valid range is 32 bits.
///  Write to RESETEN register.
///
void
_SI32_RSTSRC_A_write_reseten(SI32_RSTSRC_A_Type* /*basePointer*/,
   uint32_t /*reseten*/);
///
/// @def SI32_RSTSRC_A_write_reseten(basePointer, reseten)
#define SI32_RSTSRC_A_write_reseten(basePointer, reseten) \
   (basePointer->RESETEN.U32 = reseten)


/// @fn _SI32_RSTSRC_A_read_reseten(SI32_RSTSRC_A_Type* basePointer)
///
/// @return
///  Read RESETEN register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RSTSRC_A_read_reseten(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_read_reseten(basePointer)
#define SI32_RSTSRC_A_read_reseten(basePointer) \
(basePointer->RESETEN.U32)


/// @fn _SI32_RSTSRC_A_enable_vdd_monitor_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_vdd_monitor_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_vdd_monitor_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_vdd_monitor_reset_source(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_VMONREN_MASK)


/// @fn _SI32_RSTSRC_A_disable_vdd_monitor_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_vdd_monitor_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_vdd_monitor_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_vdd_monitor_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_VMONREN_MASK)


/// @fn _SI32_RSTSRC_A_enable_missing_clock_detector_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_missing_clock_detector_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_missing_clock_detector_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_missing_clock_detector_reset_source(basePointer) \
   (basePointer->RESETEN_SET	= SI32_RSTSRC_A_RESETEN_MCDREN_MASK)


/// @fn _SI32_RSTSRC_A_disable_missing_clock_detector_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_missing_clock_detector_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_missing_clock_detector_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_missing_clock_detector_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_MCDREN_MASK)


/// @fn _SI32_RSTSRC_A_enable_watchdog_timer_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_watchdog_timer_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_watchdog_timer_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_watchdog_timer_reset_source(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_WDTREN_MASK)


/// @fn _SI32_RSTSRC_A_disable_watchdog_timer_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_watchdog_timer_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_watchdog_timer_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_watchdog_timer_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_WDTREN_MASK)


/// @fn _SI32_RSTSRC_A_enable_comparator0_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_comparator0_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_comparator0_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_comparator0_reset_source(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_CMP0REN_MASK)


/// @fn _SI32_RSTSRC_A_disable_comparator0_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_comparator0_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_comparator0_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_comparator0_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_CMP0REN_MASK)


/// @fn _SI32_RSTSRC_A_enable_comparator1_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_comparator1_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_comparator1_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_comparator1_reset_source(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_CMP1REN_MASK)


/// @fn _SI32_RSTSRC_A_disable_comparator1_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_comparator1_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_comparator1_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_comparator1_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_CMP1REN_MASK)


/// @fn _SI32_RSTSRC_A_enable_usb0_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_usb0_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_usb0_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_usb0_reset_source(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_USB0REN_MASK)


/// @fn _SI32_RSTSRC_A_disable_usb0_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_usb0_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_usb0_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_usb0_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_USB0REN_MASK)


/// @fn _SI32_RSTSRC_A_enable_rtc0_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_rtc0_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_rtc0_reset_source(basePointer)
#define SI32_RSTSRC_A_enable_rtc0_reset_source(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_RTC0REN_MASK)


/// @fn _SI32_RSTSRC_A_disable_rtc0_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_rtc0_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_rtc0_reset_source(basePointer)
#define SI32_RSTSRC_A_disable_rtc0_reset_source(basePointer) \
   (basePointer->RESETEN_CLR = SI32_RSTSRC_A_RESETEN_RTC0REN_MASK)


/// @fn _SI32_RSTSRC_A_generate_software_reset(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_generate_software_reset(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_generate_software_reset(basePointer)
#define SI32_RSTSRC_A_generate_software_reset(basePointer) \
   (basePointer->RESETEN_SET = SI32_RSTSRC_A_RESETEN_SWREN_ENABLED_U32)


/// @fn _SI32_RSTSRC_A_get_last_reset_source(SI32_RSTSRC_A_Type* basePointer)
///
/// @return
///  Returns the source of the last reset.
///
/// @param[in]
///  basePointer
///
SI32_RSTSRC_Enum_Type
_SI32_RSTSRC_A_get_last_reset_source(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_get_last_reset_source(basePointer)
#define SI32_RSTSRC_A_get_last_reset_source(basePointer) \
   _SI32_RSTSRC_A_get_last_reset_source(basePointer)


/// @fn _SI32_RSTSRC_A_write_config(SI32_RSTSRC_A_Type* basePointer,
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
_SI32_RSTSRC_A_write_config(SI32_RSTSRC_A_Type* /*basePointer*/,
   uint32_t /*config*/);
///
/// @def SI32_RSTSRC_A_write_config(basePointer, config)
#define SI32_RSTSRC_A_write_config(basePointer, config) \
   (basePointer->CONFIG.U32 = config)


/// @fn _SI32_RSTSRC_A_read_config(SI32_RSTSRC_A_Type* basePointer)
///
/// @return
///  Read CONFIG register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_RSTSRC_A_read_config(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_read_config(basePointer)
#define SI32_RSTSRC_A_read_config(basePointer) \
(basePointer->CONFIG.U32)


/// @fn _SI32_RSTSRC_A_enable_power_mode_9(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_enable_power_mode_9(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_enable_power_mode_9(basePointer)
#define SI32_RSTSRC_A_enable_power_mode_9(basePointer) \
   (basePointer->CONFIG_SET = SI32_RSTSRC_A_CONFIG_PMSEL_PM9_EN_U32)


/// @fn _SI32_RSTSRC_A_disable_power_mode_9(SI32_RSTSRC_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_RSTSRC_A_disable_power_mode_9(SI32_RSTSRC_A_Type* /*basePointer*/);
///
/// @def SI32_RSTSRC_A_disable_power_mode_9(basePointer)
#define SI32_RSTSRC_A_disable_power_mode_9(basePointer) \
   (basePointer->CONFIG_CLR = SI32_RSTSRC_A_CONFIG_PMSEL_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_RSTSRC_A_TYPE_H__

//-eof--------------------------------------------------------------------------
