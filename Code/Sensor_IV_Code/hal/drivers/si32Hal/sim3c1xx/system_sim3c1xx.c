//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

#include "sim3c1xx.h"

//------------------------------------------------------------------------------
// boot oscillator is 20MHz
uint32_t SystemCoreClock = 20000000;

//------------------------------------------------------------------------------
void SystemInit(void)
{
  // To disable the pin reset delay described below, make sure the preprocessor
  // symbol si32HalOption_disable_pin_reset_delay is defined by your toolchain.
# if !defined(si32HalOption_disable_pin_reset_delay)
  // If the reset pin was the source of the last reset, delay for 500 msec.
  // Firmware can disable the debug port by inadvertantly setting the AHB
  // clock source to a disabled clock. If this happens too quickly after a
  // reset, it is not possible for a debug agent to gain control and thus
  // not possible to reprogram the on-chip flash. Adding a delay here gives
  // a debug agent sufficient time to connect.
  if ((SI32_RSTSRC_0->RESETFLAG.PINRF == 1)
  &&  (SI32_RSTSRC_0->RESETFLAG.PORRF == 0)
  &&  (SI32_RSTSRC_0->RESETFLAG.VMONRF == 0))
  {
    // Set the SysTick timer to count down 10M ticks @ 20MHz (~500 msec)
    SysTick->LOAD = 0xA00000;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    // Wait for the count down to complete
    while (0 == (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)) {}

    // Set the SysTick timer to reset values
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;
  }
# endif

  // invoke the application's system initialization.
  mySystemInit();
}

//------------------------------------------------------------------------------
void SystemCoreClockUpdate(void)
{
  // TBD - examine the clock registers and compute the system core clock value.
}

//-eof--------------------------------------------------------------------------
