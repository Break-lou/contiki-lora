;/**************************************************************************//**
; * @file     startup_ARMCM3.s
; * @brief    CMSIS Cortex-M4 Core Device Startup File
; *           for CM3 Device Series
; * @version  V1.05
; * @date     25. July 2011
; *
; * @note
; * Copyright (C) 2010-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M 
; * processor based microcontrollers.  This file can be freely distributed 
; * within development tools that are supporting such ARM based processors. 
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/


;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)
  
        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     WDTIMER0_IRQHandler     ; Watchdog Timer 0
        DCD     PBEXT0_IRQHandler       ; External interrupt 0
        DCD     PBEXT1_IRQHandler       ; External interrupt 1
        DCD     RTC0ALRM_IRQHandler     ; RTC Alarm
        DCD     DMACH0_IRQHandler       ; DMA Channel 0
        DCD     DMACH1_IRQHandler       ; DMA Channel 1
        DCD     DMACH2_IRQHandler       ; DMA Channel 2
        DCD     DMACH3_IRQHandler       ; DMA Channel 3
        DCD     DMACH4_IRQHandler       ; DMA Channel 4
        DCD     DMACH5_IRQHandler       ; DMA Channel 5
        DCD     DMACH6_IRQHandler       ; DMA Channel 6
        DCD     DMACH7_IRQHandler       ; DMA Channel 7
        DCD     DMACH8_IRQHandler       ; DMA Channel 8
        DCD     DMACH9_IRQHandler       ; DMA Channel 9
        DCD     DMACH10_IRQHandler      ; DMA Channel 10
        DCD     DMACH11_IRQHandler      ; DMA Channel 11
        DCD     DMACH12_IRQHandler      ; DMA Channel 12
        DCD     DMACH13_IRQHandler      ; DMA Channel 13
        DCD     DMACH14_IRQHandler      ; DMA Channel 14
        DCD     DMACH15_IRQHandler      ; DMA Channel 15
        DCD     TIMER0L_IRQHandler      ; Timer 0 Low (16 bits only)
        DCD     TIMER0H_IRQHandler      ; Timer 0 High (16 or 32 bits)
        DCD     TIMER1L_IRQHandler      ; Timer 1 Low (16 bits only)
        DCD     TIMER1H_IRQHandler      ; Timer 1 High (16 or 32 bits)
        DCD     EPCA0_IRQHandler        ; EPCA 0 Capture Compare (any channel)
        DCD     PCA0_IRQHandler         ; PCA 0 Capture Compare (any channel)
        DCD     PCA1_IRQHandler         ; PCA 1 Capture Compare (any channel)
        DCD     USART0_IRQHandler       ; USART 0
        DCD     USART1_IRQHandler       ; USART 1
        DCD     SPI0_IRQHandler         ; SPI 0
        DCD     SPI1_IRQHandler         ; SPI 1
        DCD     SPI2_IRQHandler         ; SPI 2
        DCD     I2C0_IRQHandler         ; I2C 0
        DCD     I2C1_IRQHandler         ; I2C 1
        DCD     USB0_IRQHandler         ; USB 0
        DCD     SARADC0_IRQHandler      ; ADC 0
        DCD     SARADC1_IRQHandler      ; ADC 1
        DCD     CMP0_IRQHandler         ; Comparator 0
        DCD     CMP1_IRQHandler         ; Comparator 1
        DCD     CAPSENSE0_IRQHandler    ; CapSense 0
        DCD     I2S0RX_IRQHandler       ; I2S 0 Receive
        DCD     I2S0TX_IRQHandler       ; I2S 0 Transmit
        DCD     AES0_IRQHandler         ; AES 0
        DCD     VDDLOW_IRQHandler       ; VDD low
        DCD     RTC0FAIL_IRQHandler     ; RTC failure
        DCD     PMATCH_IRQHandler       ; Port Match
        DCD     UART0_IRQHandler        ; UART 0
        DCD     UART1_IRQHandler        ; UART 1
        DCD     IDAC0_IRQHandler        ; IDAC 0
        DCD     IDAC1_IRQHandler        ; IDAC 1
        DCD     LPTIMER0_IRQHandler     ; Low-Power Timer
        DCD     PLL0_IRQHandler         ; Phase-Locked Loop
        DCD     VBUSINVALID_IRQHandler  ; VBUS Invalid
        DCD     VREG0LOW_IRQHandler     ; Voltage Regulator / 4
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size   EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WDTIMER0_IRQHandler
        SECTION .text:CODE:REORDER(1)
WDTIMER0_IRQHandler
        B WDTIMER0_IRQHandler

        PUBWEAK PBEXT0_IRQHandler
        SECTION .text:CODE:REORDER(1)
PBEXT0_IRQHandler
        B PBEXT0_IRQHandler

        PUBWEAK PBEXT1_IRQHandler
        SECTION .text:CODE:REORDER(1)
PBEXT1_IRQHandler
        B PBEXT1_IRQHandler

        PUBWEAK RTC0ALRM_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTC0ALRM_IRQHandler
        B RTC0ALRM_IRQHandler

        PUBWEAK DMACH0_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH0_IRQHandler
        B DMACH0_IRQHandler

        PUBWEAK DMACH1_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH1_IRQHandler
        B DMACH1_IRQHandler

        PUBWEAK DMACH2_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH2_IRQHandler
        B DMACH2_IRQHandler

        PUBWEAK DMACH3_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH3_IRQHandler
        B DMACH3_IRQHandler

        PUBWEAK DMACH4_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH4_IRQHandler
        B DMACH4_IRQHandler

        PUBWEAK DMACH5_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH5_IRQHandler
        B DMACH5_IRQHandler

        PUBWEAK DMACH6_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH6_IRQHandler
        B DMACH6_IRQHandler

        PUBWEAK DMACH7_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH7_IRQHandler
        B DMACH7_IRQHandler

        PUBWEAK DMACH8_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH8_IRQHandler
        B DMACH8_IRQHandler

        PUBWEAK DMACH9_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH9_IRQHandler
        B DMACH9_IRQHandler

        PUBWEAK DMACH10_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH10_IRQHandler
        B DMACH10_IRQHandler

        PUBWEAK DMACH11_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH11_IRQHandler
        B DMACH11_IRQHandler

        PUBWEAK DMACH12_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH12_IRQHandler
        B DMACH12_IRQHandler

        PUBWEAK DMACH13_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH13_IRQHandler
        B DMACH13_IRQHandler

        PUBWEAK DMACH14_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH14_IRQHandler
        B DMACH14_IRQHandler

        PUBWEAK DMACH15_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMACH15_IRQHandler
        B DMACH15_IRQHandler

        PUBWEAK TIMER0L_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER0L_IRQHandler
        B TIMER0L_IRQHandler

        PUBWEAK TIMER0H_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER0H_IRQHandler
        B TIMER0H_IRQHandler

        PUBWEAK TIMER1L_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER1L_IRQHandler
        B TIMER1L_IRQHandler

        PUBWEAK TIMER1H_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER1H_IRQHandler
        B TIMER1H_IRQHandler

        PUBWEAK EPCA0_IRQHandler
        SECTION .text:CODE:REORDER(1)
EPCA0_IRQHandler
        B EPCA0_IRQHandler

        PUBWEAK PCA0_IRQHandler
        SECTION .text:CODE:REORDER(1)
PCA0_IRQHandler
        B PCA0_IRQHandler

        PUBWEAK PCA1_IRQHandler
        SECTION .text:CODE:REORDER(1)
PCA1_IRQHandler
        B PCA1_IRQHandler

        PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:REORDER(1)
USART0_IRQHandler
        B USART0_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK USB0_IRQHandler
        SECTION .text:CODE:REORDER(1)
USB0_IRQHandler
        B USB0_IRQHandler

        PUBWEAK SARADC0_IRQHandler
        SECTION .text:CODE:REORDER(1)
SARADC0_IRQHandler
        B SARADC0_IRQHandler

        PUBWEAK SARADC1_IRQHandler
        SECTION .text:CODE:REORDER(1)
SARADC1_IRQHandler
        B SARADC1_IRQHandler

        PUBWEAK CMP0_IRQHandler
        SECTION .text:CODE:REORDER(1)
CMP0_IRQHandler
        B CMP0_IRQHandler

        PUBWEAK CMP1_IRQHandler
        SECTION .text:CODE:REORDER(1)
CMP1_IRQHandler
        B CMP1_IRQHandler

        PUBWEAK CAPSENSE0_IRQHandler
        SECTION .text:CODE:REORDER(1)
CAPSENSE0_IRQHandler
        B CAPSENSE0_IRQHandler

        PUBWEAK I2S0RX_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2S0RX_IRQHandler
        B I2S0RX_IRQHandler

        PUBWEAK I2S0TX_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2S0TX_IRQHandler
        B I2S0TX_IRQHandler

        PUBWEAK AES0_IRQHandler
        SECTION .text:CODE:REORDER(1)
AES0_IRQHandler
        B AES0_IRQHandler

        PUBWEAK VDDLOW_IRQHandler
        SECTION .text:CODE:REORDER(1)
VDDLOW_IRQHandler
        B VDDLOW_IRQHandler

        PUBWEAK RTC0FAIL_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTC0FAIL_IRQHandler
        B RTC0FAIL_IRQHandler

        PUBWEAK PMATCH_IRQHandler
        SECTION .text:CODE:REORDER(1)
PMATCH_IRQHandler
        B PMATCH_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK IDAC0_IRQHandler
        SECTION .text:CODE:REORDER(1)
IDAC0_IRQHandler
        B IDAC0_IRQHandler

        PUBWEAK IDAC1_IRQHandler
        SECTION .text:CODE:REORDER(1)
IDAC1_IRQHandler
        B IDAC1_IRQHandler

        PUBWEAK LPTIMER0_IRQHandler
        SECTION .text:CODE:REORDER(1)
LPTIMER0_IRQHandler
        B LPTIMER0_IRQHandler

        PUBWEAK PLL0_IRQHandler
        SECTION .text:CODE:REORDER(1)
PLL0_IRQHandler
        B PLL0_IRQHandler

        PUBWEAK VBUSINVALID_IRQHandler
        SECTION .text:CODE:REORDER(1)
VBUSINVALID_IRQHandler
        B VBUSINVALID_IRQHandler

        PUBWEAK VREG0LOW_IRQHandler
        SECTION .text:CODE:REORDER(1)
VREG0LOW_IRQHandler
        B VREG0LOW_IRQHandler

        END
