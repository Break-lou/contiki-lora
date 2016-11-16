#ifndef __CPU_ARCH_H__
#define __CPU_ARCH_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sim3l1xx.h"

#include <si32_device.h>
#include <SI32_PBCFG_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_PBGP_A_Type.h>
#include <SI32_CLKCTRL_A_Type.h>

#include <SI32_UART_B_Type.h>
#include <SI32_USART_B_Type.h>

#include <SI32_SPI_B_Type.h>

#include <SI32_SARADC_A_Type.h>
#include <SI32_VREF_B_Type.h>

#include <SI32_RTC_B_Type.h>
#include <SI32_PMU_A_Type.h>

#include <SI32_TIMER_A_Type.h>

#include <SI32_SCONFIG_A_Type.h>
#include <SI32_DCDC_A_Type.h>
#include <SI32_LDO_A_Type.h>
#include <SI32_LCD_A_Type.h>
#include <SI32_VMON_B_Type.h>

#include <SI32_FLASHCTRL_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_VMON_B_Type.h>
#include <SI32_RSTSRC_A_Type.h>

#include <SI32_WDTIMER_A_Type.h>
#include <SI32_IDAC_A_Type.h>
#include <SI32_EXTOSC_A_Type.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "board_cfg.h"
#define INTO_CRITICAL()  			__disable_irq()	
#define EXIT_CRITICAL()				__enable_irq()
#define SYSTEM_SOFTWARE_RESET() 	INTO_CRITICAL();	\
									NVIC_SystemReset()
typedef enum {
	RESET = 0, 
	SET = !RESET
} FlagStatus;

typedef enum {
	DISABLE = 0, 
	ENABLE = !DISABLE
} FunctionalState;

typedef enum {
	ERROR = 0, 
	SUCCESS = !ERROR
} ErrorStatus;

typedef enum { 
	Bit_RESET = 0,
	Bit_SET = 1,
} BitAction;

#ifdef __cplusplus
}
#endif

#endif // __CPU_ARCH_H__
