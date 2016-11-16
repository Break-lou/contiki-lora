//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

// Version: 1

#ifndef __SI32_AES_B_Support_Guard__
#define __SI32_AES_B_Support_Guard__

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Define the Initialization Vector Structure

typedef struct SI32_AES_B_Initialization_Vector_Struct
{
   volatile uint32_t iv[4];
} SI32_AES_B_Initialization_Vector_Type;

//-----------------------------------------------------------------------------
// Define the Hardware Key Structure

typedef struct SI32_AES_B_Hardware_Key_Struct
{
   volatile uint32_t hwkey[8];
} SI32_AES_B_Hardware_Key_Type;

//-----------------------------------------------------------------------------
// Define the Hardware Counter Structure

typedef struct SI32_AES_B_Hardware_Counter_Struct
{
   volatile uint32_t hwctr[4];
} SI32_AES_B_Hardware_Counter_Type;

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // __SI32_AES_B_Guard__

//-eof--------------------------------------------------------------------------
