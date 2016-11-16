//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_SCONFIG_A_Type.h
//
// This file applies to the SIM3C1XX_SCONFIG_A module
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#ifndef __SI32_SCONFIG_A_TYPE_H__
#define __SI32_SCONFIG_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3C1XX_SCONFIG_A_Registers.h"

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



#ifdef __cplusplus
}
#endif

#endif // __SI32_SCONFIG_A_TYPE_H__

//-eof--------------------------------------------------------------------------
