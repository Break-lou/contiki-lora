//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3C1XX_DEVICEID_A module
//
// Version: 1

#ifndef __SI32_DEVICEID_A_SUPPORT_H__
#define __SI32_DEVICEID_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define the DEVICEID Struct

typedef struct SI32_DEVICEID_Struct
{
  volatile uint32_t deviceid[4];
} SI32_DEVICEID_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_DEVICEID_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
