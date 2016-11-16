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
/// @file SI32_SPI_B_Type.c
//
// Script: 0.59
// HAL Source: 0.6
// Version: 36

#include <assert.h>
#include "si32WideTypes.h"
#include "SI32_SPI_B_Type.h"


//-----------------------------------------------------------------------------
// _SI32_SPI_B_initialize
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_initialize(
   SI32_SPI_B_Type * basePointer,
   // Write to CONTROL register.
   uint32_t control,
   // Write to CONFIG register.
   uint32_t config,
   // Write to CLKRATE register.
   uint32_t clkrate)
{
   assert(clkrate < 65536);   // clkrate < 2^16
   //{{
   basePointer->CONTROL.U32 = control;
   basePointer->CONFIG.U32 = config;
   basePointer->CLKRATE.U32 = clkrate;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_tx_fifo_u32
//
// Write 32-bit data into SPI Transmit FIFO.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_tx_fifo_u32(
   SI32_SPI_B_Type * basePointer,
   // Data to write to SPI Transmit FIFO.
   uint32_t data_u32)
{
   //{{
   basePointer->DATA.U32 = data_u32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_tx_fifo_u16
//
// Write 16-bit data into SPI Transmit FIFO.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_tx_fifo_u16(
   SI32_SPI_B_Type * basePointer,
   // Data to write to SPI Transmit FIFO.
   uwide16_t data_u16)
{
   assert(data_u16 < 65536);   // data_u16 < 2^16
   //{{
   basePointer->DATA.U16 = data_u16;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_tx_fifo_u8
//
// Write 8-bit data into SPI Transmit FIFO.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_tx_fifo_u8(
   SI32_SPI_B_Type * basePointer,
   // Data to write to SPI Transmit FIFO.
   uwide8_t data_u8)
{
   assert(data_u8 < 256);   // data_u8 < 2^8
   //{{
   basePointer->DATA.U8 = data_u8;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_rx_fifo_u32
//
// Read 32-bit data from SPI Receive FIFO.
//-----------------------------------------------------------------------------
uint32_t
_SI32_SPI_B_read_rx_fifo_u32(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->DATA.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_rx_fifo_u16
//
// Read 16-bit data from SPI Receive FIFO.
//-----------------------------------------------------------------------------
uwide16_t
_SI32_SPI_B_read_rx_fifo_u16(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->DATA.U16;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_rx_fifo_u8
//
// Read 8-bit data from SPI Receive FIFO.
//-----------------------------------------------------------------------------
uwide8_t
_SI32_SPI_B_read_rx_fifo_u8(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->DATA.U8;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_control
//
// Read CONTROL register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_SPI_B_read_control(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_control
//
// Write to CONTROL register.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_control(
   SI32_SPI_B_Type * basePointer,
   uint32_t control)
{
   //{{
   basePointer->CONTROL.U32 = control;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_rx_fifo_read_request_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_rx_fifo_read_request_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.RFRQI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_rx_fifo_overrun_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_rx_fifo_overrun_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.RFORI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_rx_fifo_overrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_rx_fifo_overrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_RFORI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_tx_fifo_write_request_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_tx_fifo_write_request_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.TFRQI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_tx_fifo_overrun_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_tx_fifo_overrun_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.TFORI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_tx_fifo_overrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_tx_fifo_overrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_TFORI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_slave_selected_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_slave_selected_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.SLVSELI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_mode_fault_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_mode_fault_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.MDFI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_mode_fault_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_mode_fault_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_MDFI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_underrun_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_underrun_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.URI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_underrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_underrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_URI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_shift_register_empty_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_shift_register_empty_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.SREI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_illegal_rx_fifo_access_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_illegal_rx_fifo_access_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.RFILI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_illegal_rx_fifo_access_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_illegal_rx_fifo_access_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_RFILI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_illegal_tx_fifo_access_interrupt_pending
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_illegal_tx_fifo_access_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.TFILI;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_illegal_tx_fifo_access_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_illegal_tx_fifo_access_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_TFILI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_any_interrupt_pending
//
// Check all SPI interrupt flags.
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_any_interrupt_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)(basePointer->CONTROL.U32
                 & (SI32_SPI_B_CONTROL_RFRQI_MASK
                    | SI32_SPI_B_CONTROL_RFORI_MASK
                    | SI32_SPI_B_CONTROL_TFRQI_MASK
                    | SI32_SPI_B_CONTROL_TFORI_MASK
                    | SI32_SPI_B_CONTROL_SLVSELI_MASK
                    | SI32_SPI_B_CONTROL_MDFI_MASK
                    | SI32_SPI_B_CONTROL_URI_MASK
                    | SI32_SPI_B_CONTROL_SREI_MASK
                    | SI32_SPI_B_CONTROL_RFILI_MASK
                    | SI32_SPI_B_CONTROL_TFILI_MASK));
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_all_interrupts
//
// Clear all SPI interrupt flags.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_all_interrupts(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_RFRQI_MASK
                            | SI32_SPI_B_CONTROL_RFORI_MASK
                            | SI32_SPI_B_CONTROL_TFRQI_MASK
                            | SI32_SPI_B_CONTROL_TFORI_MASK
                            | SI32_SPI_B_CONTROL_SLVSELI_MASK
                            | SI32_SPI_B_CONTROL_MDFI_MASK
                            | SI32_SPI_B_CONTROL_URI_MASK
                            | SI32_SPI_B_CONTROL_SREI_MASK
                            | SI32_SPI_B_CONTROL_RFILI_MASK
                            | SI32_SPI_B_CONTROL_TFILI_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_get_nss_pin
//
// Get instantaneous NSS pin value.
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_get_nss_pin(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.NSSSTS;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_transfer_in_progress
//
// Check if the SPI module is busy.
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_transfer_in_progress(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool)basePointer->CONTROL.BUSYF;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_get_rx_fifo_count
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_SPI_B_get_rx_fifo_count(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.RFCNT;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_get_tx_fifo_count
//
//-----------------------------------------------------------------------------
uint32_t
_SI32_SPI_B_get_tx_fifo_count(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->CONTROL.TFCNT;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_stall_in_debug_mode
//
// Enables SPI stall in debug mode.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_stall_in_debug_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_SET = SI32_SPI_B_CONTROL_DBGMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_stall_in_debug_mode
//
// Disables SPI stall in debug mode.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_stall_in_debug_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONTROL_CLR = SI32_SPI_B_CONTROL_DBGMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_config
//
// Read CONFIG register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_SPI_B_read_config(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->CONFIG.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_config
//
// Write to CONFIG register.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_config(
   SI32_SPI_B_Type * basePointer,
   uint32_t config)
{
   //{{
   basePointer->CONFIG.U32 = config;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_rx_fifo_read_request_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_rx_fifo_read_request_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RFRQIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_rx_fifo_read_request_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_rx_fifo_read_request_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_RFRQIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_rx_fifo_read_request_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_rx_fifo_read_request_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.RFRQIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_rx_fifo_overrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_rx_fifo_overrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RFORIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_rx_fifo_overrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_rx_fifo_overrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_RFORIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_rx_fifo_overrun_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_rx_fifo_overrun_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.RFORIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_tx_fifo_write_request_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_tx_fifo_write_request_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_TFRQIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_tx_fifo_write_request_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_tx_fifo_write_request_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_TFRQIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_tx_fifo_write_request_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_tx_fifo_write_request_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.TFRQIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_tx_fifo_overrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_tx_fifo_overrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_TFORIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_tx_fifo_overrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_tx_fifo_overrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_TFORIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_tx_fifo_overrun_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_tx_fifo_overrun_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.TFORIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_slave_selected_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_slave_selected_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_SLVSELIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_slave_selected_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_slave_selected_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_SLVSELIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_slave_selected_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_slave_selected_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.SLVSELIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_mode_fault_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_mode_fault_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_MDFIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_mode_fault_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_mode_fault_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_MDFIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_mode_fault_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_mode_fault_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.MDFIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_underrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_underrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_URIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_underrun_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_underrun_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_URIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_underrun_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_underrun_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.URIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_shift_register_empty_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_shift_register_empty_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_SREIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_shift_register_empty_interrupt
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_shift_register_empty_interrupt(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_SREIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_shift_register_empty_interrupt_enabled
//
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_shift_register_empty_interrupt_enabled(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	return (bool)(basePointer->CONFIG.SREIEN);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_module
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_module(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_SPIEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_module
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_module(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_SPIEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_master_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_master_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_MSTEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_slave_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_slave_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_MSTEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_clock_mode
//
// Configure clock to standard SPI modes.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_clock_mode(
   SI32_SPI_B_Type * basePointer,
   // Clock mode.
   SI32_SPI_B_CLOCK_MODE_Enum_Type sckmode)
{
   //{{
   switch (sckmode)
   {
      case 0:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_CLKPOL_MASK
                                 | SI32_SPI_B_CONFIG_CLKPHA_MASK;
         break;
      case 1:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_CLKPOL_MASK;
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_CLKPHA_MASK;
         break;
      case 2:
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_CLKPOL_MASK;
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_CLKPHA_MASK;
         break;
      case 3:
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_CLKPOL_MASK
                                 | SI32_SPI_B_CONFIG_CLKPHA_MASK;
         break;
      default:
         break;
   }
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_clock_idle_high
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_clock_idle_high(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_CLKPOL_HIGH_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_clock_idle_low
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_clock_idle_low(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_CLKPOL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_data_change_first_edge
//
// Configure clock phase for first edge.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_data_change_first_edge(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_CLKPHA_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_data_change_second_edge
//
// Configure clock phase for second edge.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_data_change_second_edge(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_CLKPHA_EDGE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_nss_active_high
//
// Configure NSS to be active high.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_nss_active_high(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_NSSPOL_HIGH_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_nss_active_low
//
// Configure NSS to be active low.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_nss_active_low(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_NSSPOL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_direction_lsb_first
//
// Data shifted LSB-first.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_direction_lsb_first(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_DDIRSEL_LSB_FIRST_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_direction_msb_first
//
// Data shifted MSB-first.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_direction_msb_first(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_DDIRSEL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_3wire_master_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_3wire_master_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_MSTEN_MASK;
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_NSSMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_4wire_master_mode_nss_high
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_4wire_master_mode_nss_high(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_NSSMD_MASK
                           | SI32_SPI_B_CONFIG_MSTEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_4wire_master_mode_nss_low
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_4wire_master_mode_nss_low(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_NSSMD_MASK;
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_NSSMD_4_WIRE_MASTER_NSS_LOW_U32
                           | SI32_SPI_B_CONFIG_MSTEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_3wire_slave_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_3wire_slave_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_MSTEN_MASK
                           | SI32_SPI_B_CONFIG_NSSMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_4wire_slave_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_4wire_slave_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_MSTEN_MASK
                           | SI32_SPI_B_CONFIG_NSSMD_MASK;
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_NSSMD_4_WIRE_SLAVE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_clear_nss
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_clear_nss(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_NSSMD_4_WIRE_SLAVE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_set_nss
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_set_nss(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_NSSMD_4_WIRE_SLAVE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_tx_fifo_threshold
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_tx_fifo_threshold(
   SI32_SPI_B_Type * basePointer,
   // Threshold.
   SI32_SPI_B_FIFO_THRESHOLD_Enum_Type threshold)
{
   //{{
   switch (threshold)
   {
      case 0:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_TFTH_MASK;
         break;
      case 1:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_TFTH_MASK;
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_TFTH_TWO_U32;
         break;
      case 2:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_TFTH_MASK;
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_TFTH_FOUR_U32;
         break;
      case 3:
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_TFTH_EMPTY_U32;
         break;
      default:
         break;
   }
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_rx_fifo_threshold
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_rx_fifo_threshold(
   SI32_SPI_B_Type * basePointer,
   // Threshold.
   SI32_SPI_B_FIFO_THRESHOLD_Enum_Type threshold)
{
   //{{
   switch (threshold)
   {
      case 0:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_RFTH_MASK;
         break;
      case 1:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_RFTH_MASK;
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RFTH_TWO_U32;
         break;
      case 2:
         basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_RFTH_MASK;
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RFTH_FOUR_U32;
         break;
      case 3:
         basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RFTH_FULL_U32;
         break;
      default:
         break;
   }
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_set_data_length
//
// Set length for SPI transfers.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_set_data_length(
   SI32_SPI_B_Type * basePointer,
   // Number of bits per transfer (1-16).
   uint32_t dlength)
{
   assert((dlength >= 1) && (dlength <= 16));
   //{{
   basePointer->CONFIG.DSIZE = (dlength - 1);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_dma_requests
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_dma_requests(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_DMAEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_dma_requests
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_dma_requests(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_CLR = SI32_SPI_B_CONFIG_DMAEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_flush_rx_fifo
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_flush_rx_fifo(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RFIFOFL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_flush_tx_fifo
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_flush_tx_fifo(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_TFIFOFL_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_reset_module
//
// Resets the SPIEN and MSTEN bits in the CONFIG register, all bits in
// the CONTROL register and flushes the RX and TX FIFOs.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_reset_module(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   basePointer->CONFIG_SET = SI32_SPI_B_CONFIG_RESET_ACTIVE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_is_module_reset_pending
//
// returns true if a reset is still in progress.
//-----------------------------------------------------------------------------
bool
_SI32_SPI_B_is_module_reset_pending(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return (bool) basePointer->CONFIG.RESET;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_clkrate
//
// Read CLKRATE register.
//-----------------------------------------------------------------------------
uwide16_t
_SI32_SPI_B_read_clkrate(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->CLKRATE.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_clkrate
//
// Write to CLKRATE register.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_clkrate(
   SI32_SPI_B_Type * basePointer,
   uwide16_t clkrate)
{
   assert(clkrate < 65536);   // clkrate < 2^16
   //{{
   basePointer->CLKRATE.U32 = clkrate;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_set_clock_divisor
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_set_clock_divisor(
   SI32_SPI_B_Type * basePointer,
   // Clock rate divider value.
   uint32_t divisor)
{
   assert((divisor >= 1) && (divisor <= 131072));
   //{{
   basePointer->CLKRATE.CLKDIV = ((divisor/2)-1);
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_read_configmd
//
// Read CONFIGMD register.
//-----------------------------------------------------------------------------
uint32_t
_SI32_SPI_B_read_configmd(
   SI32_SPI_B_Type * basePointer)
{
   //{{
   return basePointer->CONFIGMD.U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_write_configmd
//
// Write to CONFIGMD register.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_write_configmd(
   SI32_SPI_B_Type * basePointer,
   uint32_t configmd)
{
   //{{
   basePointer->CONFIGMD.U32 = configmd;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_operation_mode_normal
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_operation_mode_normal(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_OPMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_operation_mode_receive_only
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_operation_mode_receive_only(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_OPMD_MASK;
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_OPMD_RECEIVE_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_operation_mode_transmit_only
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_operation_mode_transmit_only(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_OPMD_MASK;
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_OPMD_TRANSMIT_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_operation_mode_flow_control
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_operation_mode_flow_control(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_OPMD_FLOWCONTROL_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_auto_nss_mode
//
// NSS will automatically assert with the SPI module is configured for
// single-master mode.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_auto_nss_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_AUTONSS_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_auto_nss_mode
//
// NSS will not automatically assert with the SPI module is configured
// for single-master mode.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_auto_nss_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_AUTONSS_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_cts_flow_control
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_cts_flow_control(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_CTSEN_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_cts_flow_control
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_cts_flow_control(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_CTSEN_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_flow_control_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_flow_control_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_FLOWMD_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_flow_control_mode
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_flow_control_mode(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_FLOWMD_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_software_abort
//
// At the end of the current data transmission, the SPI module will be
// reset.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_software_abort(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_ABORT_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_software_abort
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_software_abort(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_ABORT_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_enable_transmit_data_on_request
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_enable_transmit_data_on_request(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_TXONREQ_ENABLED_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_disable_transmit_data_on_request
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_disable_transmit_data_on_request(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_TXONREQ_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_nss_data_count
//
// Selects the number of data blocks per NSS cycle.
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_nss_data_count(
   SI32_SPI_B_Type * basePointer,
   uint32_t nsscnt)
{
   assert(nsscnt < 256);   // nsscnt < 2^8
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_NSSCNT_MASK;
	basePointer->CONFIGMD_SET = nsscnt << SI32_SPI_B_CONFIGMD_NSSCNT_SHIFT;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_nss_delay
//
// Selects the number of half SPI clock cycles between NSS cycles. 0  =
// one half SPI clock cycle, 1 = two half SPI clock cycles, 2 = three
// half SPI clock cycles, ...
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_nss_delay(
   SI32_SPI_B_Type * basePointer,
   uint32_t nssdelay)
{
   assert(nssdelay < 256);   // nssdelay < 2^8
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_NSSDELAY_MASK;
	basePointer->CONFIGMD_SET = nssdelay << SI32_SPI_B_CONFIGMD_NSSDELAY_SHIFT;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_transfer_count_auto
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_transfer_count_auto(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_TFRCNT_MASK;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_transfer_count_one
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_transfer_count_one(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_TFRCNT_MASK;
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_TFRCNT_TRANSFER1_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_transfer_count_two
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_transfer_count_two(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_TFRCNT_MASK;
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_TFRCNT_TRANSFER2_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_transfer_count_three
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_transfer_count_three(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_TFRCNT_MASK;
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_TFRCNT_TRANSFER3_U32;
   //}}
}

//-----------------------------------------------------------------------------
// _SI32_SPI_B_select_transfer_count_four
//
//-----------------------------------------------------------------------------
void
_SI32_SPI_B_select_transfer_count_four(
   SI32_SPI_B_Type * basePointer)
{
   //{{
	basePointer->CONFIGMD_CLR = SI32_SPI_B_CONFIGMD_TFRCNT_MASK;
	basePointer->CONFIGMD_SET = SI32_SPI_B_CONFIGMD_TFRCNT_TRANSFER4_U32;
   //}}
}


//-eof--------------------------------------------------------------------------
