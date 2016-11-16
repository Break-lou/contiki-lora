//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/// @file SI32_LOCK_A_Type.c
//
// This file applies to the SIM3L1XX_LOCK_A module
//
// Script: 0.58
// HAL Source: 0.1
// Version: 1

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_LOCK_A_Type.h"


//-----------------------------------------------------------------------------
// _SI32_LOCK_A_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_initialize(
   SI32_LOCK_A_Type * basePointer,
   // PERIPHLOCK0 register.
   uint32_t periphlock0,
   // PERIPHLOCK1 register.
   uint32_t periphlock1)
{
   assert(periphlock1 < 2);   // periphlock1 < 2^1
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;
   basePointer->PERIPHLOCK0.U32 = periphlock0;
   basePointer->PERIPHLOCK1.U32 = periphlock1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_unlock_peripheral_locking_registers
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_unlock_peripheral_locking_registers(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_lock_peripheral_locking_registers
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_lock_peripheral_locking_registers(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_check_lock_register_status
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_LOCK_A_check_lock_register_status(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   return basePointer->KEY.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_write_periphlock0
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_write_periphlock0(
   SI32_LOCK_A_Type * basePointer,
   // Write PERIPHLOCK0 register.
   uint32_t periphlock0)
{
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;
   basePointer->PERIPHLOCK0.U32 = periphlock0;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_read_periphlock0
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_LOCK_A_read_periphlock0(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   return basePointer->PERIPHLOCK0.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_write_periphlock1
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_write_periphlock1(
   SI32_LOCK_A_Type * basePointer,
   // Write PERIPHLOCK1 register.
   uint32_t periphlock1)
{
   assert(periphlock1 < 2);   // periphlock1 < 2^1
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;
   basePointer->PERIPHLOCK1.U32 = periphlock1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_read_periphlock1
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_LOCK_A_read_periphlock1(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   return basePointer->PERIPHLOCK1.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_lock_module
//
// This function will automatically unlock and lock the interface to the
// module locks.
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_lock_module(
   SI32_LOCK_A_Type * basePointer,
   // Peripheral set to lock.
   SI32_LOCK_A_Enum_Type module)
{
   assert(module < 32);   // module < 2^5
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;

   switch (module)
   {
      case SI32_LOCK_A_SELECT_USART_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_USARTL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_SPI_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_SPIL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_I2C_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_I2CL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PCA_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_PCAL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_TIMER_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_TIMERL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_SARADC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_SARADCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_CMP_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_CMPL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_AES_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_AESL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_CRC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_CRCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_RTC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_RTCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_RSTSRC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_RSTSRCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_CLKCTRL_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_CLKCTRL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_VMON_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_VMONL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_IDAC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_IDACL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DMACTRL_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_DMACTRLL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DMAXBAR_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_DMAXBARL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LPT_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_LPTL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LDO_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_LDOL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PLL_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_PLLL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_EXTOSC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_EXTOSCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PVT_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_PVTL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LPOSC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_LPOSCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_ACCTR_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_ACCTRL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PMU_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_PMUL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DTM_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_DTML_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LCD_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_LCDL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DCDC_LOCK:
         basePointer->PERIPHLOCK0_SET =
            SI32_LOCK_A_PERIPHLOCK0_DCDCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_ENCDEC_LOCK:
         basePointer->PERIPHLOCK1_SET =
            SI32_LOCK_A_PERIPHLOCK1_ENCDECL_LOCKED_U32;
         break;
   }
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_unlock_module
//
// This function will automatically unlock and lock the interface to the
// module locks.
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_unlock_module(
   SI32_LOCK_A_Type * basePointer,
   // Peripheral set to unlock.
   SI32_LOCK_A_Enum_Type module)
{
   assert(module < 32);   // module < 2^5
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;

   switch (module)
   {
      case SI32_LOCK_A_SELECT_USART_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_USARTL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_SPI_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_SPIL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_I2C_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_I2CL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PCA_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_PCAL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_TIMER_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_TIMERL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_SARADC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_SARADCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_CMP_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_CMPL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_AES_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_AESL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_CRC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_CRCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_RTC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_RTCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_RSTSRC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_RSTSRCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_CLKCTRL_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_CLKCTRL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_VMON_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_VMONL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_IDAC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_IDACL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DMACTRL_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_DMACTRLL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DMAXBAR_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_DMAXBARL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LPT_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_LPTL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LDO_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_LDOL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PLL_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_PLLL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_EXTOSC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_EXTOSCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PVT_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_PVTL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LPOSC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_LPOSCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_ACCTR_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_ACCTRL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_PMU_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_PMUL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DTM_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_DTML_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_LCD_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_LCDL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_DCDC_LOCK:
         basePointer->PERIPHLOCK0_CLR =
            SI32_LOCK_A_PERIPHLOCK0_DCDCL_LOCKED_U32;
         break;
      case SI32_LOCK_A_SELECT_ENCDEC_LOCK:
         basePointer->PERIPHLOCK1_CLR =
            SI32_LOCK_A_PERIPHLOCK1_ENCDECL_LOCKED_U32;
         break;   }
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_is_module_locked
//
//-----------------------------------------------------------------------------
bool
_SI32_LOCK_A_is_module_locked(
   SI32_LOCK_A_Type * basePointer,
   // Peripheral set to check.
   SI32_LOCK_A_Enum_Type module)
{
   assert(module < 32);   // module < 2^5
   //{{
   uint32_t lock_status;

   switch (module)
   {
      case SI32_LOCK_A_SELECT_USART_LOCK:
         lock_status = basePointer->PERIPHLOCK0.USARTL;
         break;
      case SI32_LOCK_A_SELECT_SPI_LOCK:
         lock_status = basePointer->PERIPHLOCK0.SPIL;
         break;
      case SI32_LOCK_A_SELECT_I2C_LOCK:
         lock_status = basePointer->PERIPHLOCK0.I2CL;
         break;
      case SI32_LOCK_A_SELECT_PCA_LOCK:
         lock_status = basePointer->PERIPHLOCK0.PCAL;
         break;
      case SI32_LOCK_A_SELECT_TIMER_LOCK:
         lock_status = basePointer->PERIPHLOCK0.TIMERL;
         break;
      case SI32_LOCK_A_SELECT_SARADC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.SARADCL;
         break;
      case SI32_LOCK_A_SELECT_CMP_LOCK:
         lock_status = basePointer->PERIPHLOCK0.CMPL;
         break;
      case SI32_LOCK_A_SELECT_AES_LOCK:
         lock_status = basePointer->PERIPHLOCK0.AESL;
         break;
      case SI32_LOCK_A_SELECT_CRC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.CRCL;
         break;
      case SI32_LOCK_A_SELECT_RTC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.RTCL;
         break;
      case SI32_LOCK_A_SELECT_RSTSRC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.RSTSRCL;
         break;
      case SI32_LOCK_A_SELECT_CLKCTRL_LOCK:
         lock_status = basePointer->PERIPHLOCK0.CLKCTRL;
         break;
      case SI32_LOCK_A_SELECT_VMON_LOCK:
         lock_status = basePointer->PERIPHLOCK0.VMONL;
         break;
      case SI32_LOCK_A_SELECT_IDAC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.IDACL;
         break;
      case SI32_LOCK_A_SELECT_DMACTRL_LOCK:
         lock_status = basePointer->PERIPHLOCK0.DMACTRLL;
         break;
      case SI32_LOCK_A_SELECT_DMAXBAR_LOCK:
         lock_status = basePointer->PERIPHLOCK0.DMAXBARL;
         break;
      case SI32_LOCK_A_SELECT_LPT_LOCK:
         lock_status = basePointer->PERIPHLOCK0.LPTL;
         break;
      case SI32_LOCK_A_SELECT_LDO_LOCK:
         lock_status = basePointer->PERIPHLOCK0.LDOL;
         break;
      case SI32_LOCK_A_SELECT_PLL_LOCK:
         lock_status = basePointer->PERIPHLOCK0.PLLL;
         break;
      case SI32_LOCK_A_SELECT_PVT_LOCK:
         lock_status = basePointer->PERIPHLOCK0.PVTL;
         break;
      case SI32_LOCK_A_SELECT_EXTOSC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.EXTOSCL;
         break;
      case SI32_LOCK_A_SELECT_LPOSC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.LPOSCL;
         break;
      case SI32_LOCK_A_SELECT_ACCTR_LOCK:
         lock_status = basePointer->PERIPHLOCK0.ACCTRL;
         break;
      case SI32_LOCK_A_SELECT_PMU_LOCK:
         lock_status = basePointer->PERIPHLOCK0.PMUL;
         break;
      case SI32_LOCK_A_SELECT_DTM_LOCK:
         lock_status = basePointer->PERIPHLOCK0.DTML;
         break;
      case SI32_LOCK_A_SELECT_LCD_LOCK:
         lock_status = basePointer->PERIPHLOCK0.LCDL;
         break;
      case SI32_LOCK_A_SELECT_DCDC_LOCK:
         lock_status = basePointer->PERIPHLOCK0.DCDCL;
         break;
      case SI32_LOCK_A_SELECT_ENCDEC_LOCK:
         lock_status = basePointer->PERIPHLOCK1.ENCDECL;
         break;
   }

   return (bool)(lock_status);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_unlock_all_modules
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_unlock_all_modules(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;
   basePointer->PERIPHLOCK0_CLR =
      SI32_LOCK_A_PERIPHLOCK0_ALL_LOCKS_MASK;
   basePointer->PERIPHLOCK1_CLR = SI32_LOCK_A_PERIPHLOCK1_ALL_LOCKS_MASK;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_LOCK_A_lock_all_modules
//
//-----------------------------------------------------------------------------
void
_SI32_LOCK_A_lock_all_modules(
   SI32_LOCK_A_Type * basePointer)
{
   //{{
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_1;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_UNLOCK_VALUE_2;
   basePointer->PERIPHLOCK0_SET =
      SI32_LOCK_A_PERIPHLOCK0_ALL_LOCKS_MASK;
   basePointer->PERIPHLOCK1_SET = SI32_LOCK_A_PERIPHLOCK1_ALL_LOCKS_MASK;
   basePointer->KEY.KEY_BITS = SI32_LOCK_A_LOCK_VALUE;
   //}}
}


//-eof--------------------------------------------------------------------------
