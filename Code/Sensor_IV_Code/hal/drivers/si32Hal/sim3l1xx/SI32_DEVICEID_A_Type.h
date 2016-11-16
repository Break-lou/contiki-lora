//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_DEVICEID_A_Type.h
//
// This file applies to the SIM3L1XX_DEVICEID_A module
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#ifndef __SI32_DEVICEID_A_TYPE_H__
#define __SI32_DEVICEID_A_TYPE_H__

// compiler dependencies
#include <stdbool.h>
#include "si32WideTypes.h"

// register definitions
#include "SI32_SIM3L1XX_DEVICEID_A_Registers.h"

// support definitions
#include "SI32_DEVICEID_A_Support.h"

#ifdef __cplusplus
extern "C" {
#endif


/// @fn _SI32_DEVICEID_A_read_device_id(SI32_DEVICEID_A_Type* basePointer)
///
/// @return
///  Device ID in 4 32-bit words.
///
/// @param[in]
///  basePointer
///
SI32_DEVICEID_Type
_SI32_DEVICEID_A_read_device_id(SI32_DEVICEID_A_Type* /*basePointer*/);
///
/// @def SI32_DEVICEID_A_read_device_id(basePointer)
#define SI32_DEVICEID_A_read_device_id(basePointer) \
   _SI32_DEVICEID_A_read_device_id(basePointer)



#ifdef __cplusplus
}
#endif

#endif // __SI32_DEVICEID_A_TYPE_H__

//-eof--------------------------------------------------------------------------
