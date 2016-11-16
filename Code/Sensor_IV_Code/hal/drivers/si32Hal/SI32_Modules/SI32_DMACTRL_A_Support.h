//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_DMACTRL_A_SUPPORT_H__
#define __SI32_DMACTRL_A_SUPPORT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define State ENUMS
typedef enum SI32_DMACTRL_A_STATE_Enum
{
  SI32_DMACTRL_IDLE                      = 0x0,
  SI32_DMACTRL_READ_CHANNEL_DATA         = 0x1,
  SI32_DMACTRL_READ_SRC_PTR              = 0x2,
  SI32_DMACTRL_READ_DST_PTR              = 0x3,
  SI32_DMACTRL_READ_SRC_DATA             = 0x4,
  SI32_DMACTRL_WRITE_DST_DATA            = 0x5,
  SI32_DMACTRL_WAIT_FOR_DMA_REQ_CLEAR    = 0x6,
  SI32_DMACTRL_WRITE_CHANNEL_DATA        = 0x7,
  SI32_DMACTRL_STALLED                   = 0x8,
  SI32_DMACTRL_DONE                      = 0x9,
  SI32_DMACTRL_SCATTER_GATHER_TRANSITION = 0xA
} SI32_DMACTRL_A_STATE_Enum_Type;



#ifdef __cplusplus
}
#endif

#endif // __SI32_DMACTRL_A_SUPPORT_H__

//-eof--------------------------------------------------------------------------
