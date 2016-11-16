//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_DEVICEID_A_Type.c
//
// This file applies to the SIM3U1XX_DEVICEID_A module
//
// Script: 0.58
// HAL Source: 0.4
// Version: 2

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_DEVICEID_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_DEVICEID_A_read_device_id
//
//-----------------------------------------------------------------------------
SI32_DEVICEID_Type
_SI32_DEVICEID_A_read_device_id(
   SI32_DEVICEID_A_Type * basePointer)
{
   //{{
   SI32_DEVICEID_Type id;

   id.deviceid[0] = basePointer->DEVICEID0.U32;
   id.deviceid[1] = basePointer->DEVICEID1.U32;
   id.deviceid[2] = basePointer->DEVICEID2.U32;
   id.deviceid[3] = basePointer->DEVICEID3.U32;

   return id;
   //}}
}


//-eof--------------------------------------------------------------------------
