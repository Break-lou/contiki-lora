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
/// @file SI32_SCONFIG_A_Type.h
//
// This file applies to the SIM3U1XX_SCONFIG_A module
//
// Script: 0.59
// HAL Source: 0.2
// Version: 1

#ifndef __SI32_SCONFIG_A_TYPE_H__
#define __SI32_SCONFIG_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3L1XX_SCONFIG_A_Registers.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_SCONFIG_A_initialize(SI32_SCONFIG_A_Type* basePointer,
///      uint32_t config)
///
/// @brief
/// Writes all SCONFIG registers.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///
void
_SI32_SCONFIG_A_initialize(SI32_SCONFIG_A_Type* /*basePointer*/,
   uint32_t /*config*/);
///
/// @def SI32_SCONFIG_A_initialize(basePointer, config)
#define SI32_SCONFIG_A_initialize(basePointer, config) \
   (basePointer->CONFIG.U32 = config)


/// @fn _SI32_SCONFIG_A_write_config(SI32_SCONFIG_A_Type* basePointer,
///      uint32_t config)
///
/// @brief
/// Writes CONFIG register.
///
/// @param[in]
///  basePointer
///
/// @param[in]
///  config
///  Valid range is 32 bits.
///
void
_SI32_SCONFIG_A_write_config(SI32_SCONFIG_A_Type* /*basePointer*/,
   uint32_t /*config*/);
///
/// @def SI32_SCONFIG_A_write_config(basePointer, config)
#define SI32_SCONFIG_A_write_config(basePointer, config) \
   (basePointer->CONFIG.U32 = config)


/// @fn _SI32_SCONFIG_A_read_config(SI32_SCONFIG_A_Type* basePointer)
///
/// @brief
/// Reads CONFIG register.
///
/// @param[in]
///  basePointer
///
uint32_t
_SI32_SCONFIG_A_read_config(SI32_SCONFIG_A_Type* /*basePointer*/);
///
/// @def SI32_SCONFIG_A_read_config(basePointer)
#define SI32_SCONFIG_A_read_config(basePointer) \
(basePointer->CONFIG.U32)


/// @fn _SI32_SCONFIG_A_enter_fast_dma_mode(SI32_SCONFIG_A_Type* basePointer)
///
/// @brief
/// Run the DMA in the faster mode.
///
/// @param[in]
///  basePointer
///
void
_SI32_SCONFIG_A_enter_fast_dma_mode(SI32_SCONFIG_A_Type* /*basePointer*/);
///
/// @def SI32_SCONFIG_A_enter_fast_dma_mode(basePointer)
#define SI32_SCONFIG_A_enter_fast_dma_mode(basePointer) \
   (basePointer->CONFIG_SET = SI32_SCONFIG_A_CONFIG_FDMAEN_MASK)


/// @fn _SI32_SCONFIG_A_exit_fast_dma_mode(SI32_SCONFIG_A_Type* basePointer)
///
/// @brief
/// Run the DMA in the legacy uDMA mode.
///
/// @param[in]
///  basePointer
///
void
_SI32_SCONFIG_A_exit_fast_dma_mode(SI32_SCONFIG_A_Type* /*basePointer*/);
///
/// @def SI32_SCONFIG_A_exit_fast_dma_mode(basePointer)
#define SI32_SCONFIG_A_exit_fast_dma_mode(basePointer) \
   (basePointer->CONFIG_CLR = SI32_SCONFIG_A_CONFIG_FDMAEN_MASK)


/// @fn _SI32_SCONFIG_A_enable_power_mode_8_debugging(SI32_SCONFIG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SCONFIG_A_enable_power_mode_8_debugging(SI32_SCONFIG_A_Type* /*basePointer*/);
///
/// @def SI32_SCONFIG_A_enable_power_mode_8_debugging(basePointer)
#define SI32_SCONFIG_A_enable_power_mode_8_debugging(basePointer) \
   (basePointer->CONFIG_SET = SI32_SCONFIG_A_CONFIG_PM8DBGEN_MASK)


/// @fn _SI32_SCONFIG_A_disable_power_mode_8_debugging(SI32_SCONFIG_A_Type* basePointer)
///
/// @param[in]
///  basePointer
///
void
_SI32_SCONFIG_A_disable_power_mode_8_debugging(SI32_SCONFIG_A_Type* /*basePointer*/);
///
/// @def SI32_SCONFIG_A_disable_power_mode_8_debugging(basePointer)
#define SI32_SCONFIG_A_disable_power_mode_8_debugging(basePointer) \
   (basePointer->CONFIG_CLR = SI32_SCONFIG_A_CONFIG_PM8DBGEN_MASK)



#ifdef __cplusplus
}
#endif

#endif // __SI32_SCONFIG_A_TYPE_H__

//-eof--------------------------------------------------------------------------
