//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
/* *INDENT-OFF* */

#ifndef __SYSTEM_SIM3U1XX_H__
#define __SYSTEM_SIM3U1XX_H__

#ifdef __cplusplus
extern "C" {
#endif

// Refer to the CMSIS_V2P00 specification for detailed documentation.
// Contains the system core clock (which is the system clock frequency supplied
// to the SysTick timer and the processor core clock). This variable can be used
// by the user application to setup the SysTick timer or configure other
// parameters. It may also be used by debugger to query the frequency of the
// debug timer or configure the trace clock speed.
// SystemCoreClock is initialized with a correct predefined value.
// The compiler must be configured to avoid the removal of this variable in case
// that the application program is not using it. It is important for debug
// systems that the variable is physically present in memory so that it can be
// examined to configure the debugger.
extern uint32_t SystemCoreClock;

// Refer to the CMSIS_V2P00 specification for detailed documentation.
// Setup the microcontroller system.
// For systems with variable clock speed it also updates the variable SystemCoreClock.
extern void SystemInit(void);

// Application specific system initialization code.  Application needs to have this function.
extern void mySystemInit(void);

// Refer to the CMSIS_V2P00 specification for detailed documentation.
// Updates the variable SystemCoreClock and must be called whenever the core
// clock is changed during program execution. SystemCoreClockUpdate() evaluates
// the clock register settings and calculates the current core clock.
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_SIM3U1XX_H__ */

//-eof--------------------------------------------------------------------------

