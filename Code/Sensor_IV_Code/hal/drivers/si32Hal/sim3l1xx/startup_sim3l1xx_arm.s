;-------------------------------------------------------------------------------
; Copyright (c) 2011 by Silicon Laboratories Inc.  All rights reserved.
; The program contained in this listing is proprietary to Silicon Laboratories,
; headquartered in Austin, Texas, U.S.A. and is subject to worldwide copyright
; protection, including protection under the United States Copyright Act of 1976
; as an unpublished work, pursuant to Section 104 and Section 408 of Title XVII
; of the United States code.  Unauthorized copying, adaptation, distribution,
; use, or display is prohibited by this law.
;
; Silicon Laboratories provides this software solely and exclusively
; for use on Silicon Laboratories' microcontroller products.
;
; This software is provided "as is".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; SILICON LABORATORIES SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
; INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;-------------------------------------------------------------------------------
; RVMDK chain

  PRESERVE8
  THUMB
;-------------------------------------------------------------------------------
; interrupt vectors
  AREA    RESET, DATA, READONLY
  EXPORT __Vectors
  EXPORT __Vectors_End
  EXPORT __Vectors_Size
  IMPORT ||Image$$ARM_LIB_STACK$$ZI$$Limit||
  
__Vectors   
  ; stack pointer
  DCD ||Image$$ARM_LIB_STACK$$ZI$$Limit||   ; Top of Stack

  ; CPU interrupts
  DCD Reset_Handler      ; Reset Handler
  DCD NMI_Handler        ; NMI Handler
  DCD HardFault_Handler  ; Hard Fault Handler
  DCD MemManage_Handler  ; MPU Fault Handler
  DCD BusFault_Handler   ; Bus Fault Handler
  DCD UsageFault_Handler ; Usage Fault Handler
  DCD 0                  ; reserved
  DCD 0                  ; reserved
  DCD 0                  ; reserved
  DCD 0                  ; reserved
  DCD SVC_Handler        ; SVCall Handler
  DCD DebugMon_Handler   ; Debug Monitor Handler
  DCD 0                  ; reserved
  DCD PendSV_Handler     ; PendSV Handler
  DCD SysTick_Handler    ; SysTick Handler

  ; MCU interrupts
  DCD WDTIMER0_IRQHandler     ; Watchdog Timer 0
  DCD PBEXT0_IRQHandler       ; External interrupt 0
  DCD PBEXT1_IRQHandler       ; External interrupt 1
  DCD RTC0ALRM_IRQHandler     ; RTC Alarm
  DCD LPTIMER0_IRQHandler     ; Low-Power Timer
  DCD DMAERR_IRQHandler       ; DMA Error
  DCD DMACH0_IRQHandler       ; DMA Channel 0
  DCD DMACH1_IRQHandler       ; DMA Channel 1
  DCD DMACH2_IRQHandler       ; DMA Channel 2
  DCD DMACH3_IRQHandler       ; DMA Channel 3
  DCD DMACH4_IRQHandler       ; DMA Channel 4
  DCD DMACH5_IRQHandler       ; DMA Channel 5
  DCD DMACH6_IRQHandler       ; DMA Channel 6
  DCD DMACH7_IRQHandler       ; DMA Channel 7
  DCD DMACH8_IRQHandler       ; DMA Channel 8
  DCD DMACH9_IRQHandler       ; DMA Channel 9
  DCD TIMER0L_IRQHandler      ; Timer 0 Low (16 bits only)
  DCD TIMER0H_IRQHandler      ; Timer 0 High (16 or 32 bits)
  DCD TIMER1L_IRQHandler      ; Timer 1 Low (16 bits only)
  DCD TIMER1H_IRQHandler      ; Timer 1 High (16 or 32 bits)
  DCD TIMER2L_IRQHandler      ; Timer 2 Low (16 bits only)
  DCD TIMER2H_IRQHandler      ; Timer 2 High (16 or 32 bits)
  DCD ACCTR0_IRQHandler       ; Advanced Capture Counter
  DCD EPCA0_IRQHandler        ; EPCA 0 Capture Compare (any channel)
  DCD USART0_IRQHandler       ; USART 0
  DCD UART0_IRQHandler        ; UART 0
  DCD SPI0_IRQHandler         ; SPI 0
  DCD SPI1_IRQHandler         ; SPI 1
  DCD I2C0_IRQHandler         ; I2C 0
  DCD SARADC0_IRQHandler      ; ADC 0
  DCD CMP0_IRQHandler         ; Comparator 0
  DCD CMP1_IRQHandler         ; Comparator 1
  DCD DTM0_IRQHandler         ; Data Transfer Manager 0
  DCD DTM1_IRQHandler         ; Data Transfer Manager 1
  DCD DTM2_IRQHandler         ; Data Transfer Manager 2
  DCD AES0_IRQHandler         ; AES 0
  DCD ENCDEC0_IRQHandler      ; Encoder/Decoder
  DCD RTC0FAIL_IRQHandler     ; RTC clock failure
  DCD VDDLOW_IRQHandler       ; VDD low
  DCD VCPFAIL_IRQHandler      ; VCP failure
  DCD DCDC_IRQHandler         ; DCDC Converter
  DCD PMATCH_IRQHandler       ; Port Match
  DCD IDAC0_IRQHandler        ; IDAC 0
  DCD PLL0_IRQHandler         ; Phase-Locked Loop
__Vectors_End

__Vectors_Size\
  EQU  __Vectors_End - __Vectors
  AREA    |.text|, CODE, READONLY

;-------------------------------------------------------------------------------
; default reset handler
Reset_Handler\
  PROC
    EXPORT Reset_Handler [WEAK]
    IMPORT SystemInit
    IMPORT __main
    LDR R0, = SystemInit
    BLX R0
    LDR R0, = __main
    BX  R0
  ENDP

;-------------------------------------------------------------------------------
; dummy exception handlers
NMI_Handler\
  PROC  
    EXPORT NMI_Handler [WEAK]
    B .
  ENDP

HardFault_Handler\
  PROC
    EXPORT HardFault_Handler [WEAK]
    B .
  ENDP

MemManage_Handler\
  PROC
    EXPORT MemManage_Handler [WEAK]
    B .
  ENDP

BusFault_Handler\
  PROC
    EXPORT BusFault_Handler [WEAK]
    B .
  ENDP

UsageFault_Handler\
  PROC
    EXPORT UsageFault_Handler [WEAK]
    B .
  ENDP

SVC_Handler\
  PROC
    EXPORT SVC_Handler [WEAK]
    B .
  ENDP

DebugMon_Handler\
  PROC
    EXPORT DebugMon_Handler [WEAK]
    B .
  ENDP

PendSV_Handler\
  PROC
    EXPORT PendSV_Handler [WEAK]
    B .
  ENDP

SysTick_Handler\
  PROC
    EXPORT SysTick_Handler [WEAK]
    B .
  ENDP

WDTIMER0_IRQHandler\
  PROC
    EXPORT WDTIMER0_IRQHandler [WEAK]
    B .
  ENDP

PBEXT0_IRQHandler\
  PROC
    EXPORT PBEXT0_IRQHandler [WEAK]
    B .
  ENDP

PBEXT1_IRQHandler\
  PROC
    EXPORT PBEXT1_IRQHandler [WEAK]
    B .
  ENDP

RTC0ALRM_IRQHandler\
  PROC
    EXPORT RTC0ALRM_IRQHandler [WEAK]
    B .
  ENDP

LPTIMER0_IRQHandler\
  PROC
    EXPORT LPTIMER0_IRQHandler [WEAK]
    B .
  ENDP

DMAERR_IRQHandler\
  PROC
    EXPORT DMAERR_IRQHandler [WEAK]
    B .
  ENDP

DMACH0_IRQHandler\
  PROC
    EXPORT DMACH0_IRQHandler [WEAK]
    B .
  ENDP

DMACH1_IRQHandler\
  PROC
    EXPORT DMACH1_IRQHandler [WEAK]
    B .
  ENDP

DMACH2_IRQHandler\
  PROC
    EXPORT DMACH2_IRQHandler [WEAK]
    B .
  ENDP

DMACH3_IRQHandler\
  PROC
    EXPORT DMACH3_IRQHandler [WEAK]
    B .
  ENDP

DMACH4_IRQHandler\
  PROC
    EXPORT DMACH4_IRQHandler [WEAK]
    B .
  ENDP

DMACH5_IRQHandler\
  PROC
    EXPORT DMACH5_IRQHandler [WEAK]
    B .
  ENDP

DMACH6_IRQHandler\
  PROC
    EXPORT DMACH6_IRQHandler [WEAK]
    B .
  ENDP

DMACH7_IRQHandler\
  PROC
    EXPORT DMACH7_IRQHandler [WEAK]
    B .
  ENDP

DMACH8_IRQHandler\
  PROC
    EXPORT DMACH8_IRQHandler [WEAK]
    B .
  ENDP

DMACH9_IRQHandler\
  PROC
    EXPORT DMACH9_IRQHandler [WEAK]
    B .
  ENDP

TIMER0L_IRQHandler\
  PROC
    EXPORT TIMER0L_IRQHandler [WEAK]
    B .
  ENDP

TIMER0H_IRQHandler\
  PROC
    EXPORT TIMER0H_IRQHandler [WEAK]
    B .
  ENDP

TIMER1L_IRQHandler\
  PROC
    EXPORT TIMER1L_IRQHandler [WEAK]
    B .
  ENDP

TIMER1H_IRQHandler\
  PROC
    EXPORT TIMER1H_IRQHandler [WEAK]
    B .
  ENDP

TIMER2L_IRQHandler\
  PROC
    EXPORT TIMER2L_IRQHandler [WEAK]
    B .
  ENDP

TIMER2H_IRQHandler\
  PROC
    EXPORT TIMER2H_IRQHandler [WEAK]
    B .
  ENDP

ACCTR0_IRQHandler\
  PROC
    EXPORT ACCTR0_IRQHandler [WEAK]
    B .
  ENDP

EPCA0_IRQHandler\
  PROC
    EXPORT EPCA0_IRQHandler [WEAK]
    B .
  ENDP

USART0_IRQHandler\
  PROC
    EXPORT USART0_IRQHandler [WEAK]
    B .
  ENDP

UART0_IRQHandler\
  PROC
    EXPORT UART0_IRQHandler [WEAK]
    B .
  ENDP
  
SPI0_IRQHandler\
  PROC
    EXPORT SPI0_IRQHandler [WEAK]
    B .
  ENDP

SPI1_IRQHandler\
  PROC
    EXPORT SPI1_IRQHandler [WEAK]
    B .
  ENDP

I2C0_IRQHandler\
  PROC
    EXPORT I2C0_IRQHandler [WEAK]
    B .
  ENDP

SARADC0_IRQHandler\
  PROC
    EXPORT SARADC0_IRQHandler [WEAK]
    B .
  ENDP

CMP0_IRQHandler\
  PROC
    EXPORT CMP0_IRQHandler [WEAK]
    B .
  ENDP
  
CMP1_IRQHandler\
  PROC
    EXPORT CMP1_IRQHandler [WEAK]
    B .
  ENDP

DTM0_IRQHandler\
  PROC
    EXPORT DTM0_IRQHandler [WEAK]
    B .
  ENDP

DTM1_IRQHandler\
  PROC
    EXPORT DTM1_IRQHandler [WEAK]
    B .
  ENDP

DTM2_IRQHandler\
  PROC
    EXPORT DTM2_IRQHandler [WEAK]
    B .
  ENDP
  
AES0_IRQHandler\
  PROC
    EXPORT AES0_IRQHandler [WEAK]
    B .
  ENDP

ENCDEC0_IRQHandler\
  PROC
    EXPORT ENCDEC0_IRQHandler [WEAK]
    B .
  ENDP

RTC0FAIL_IRQHandler\
  PROC
    EXPORT RTC0FAIL_IRQHandler [WEAK]
    B .
  ENDP
  
VDDLOW_IRQHandler\
  PROC
    EXPORT VDDLOW_IRQHandler [WEAK]
    B .
  ENDP

VCPFAIL_IRQHandler\
  PROC
    EXPORT VCPFAIL_IRQHandler [WEAK]
    B .
  ENDP

DCDC_IRQHandler\
  PROC
    EXPORT DCDC_IRQHandler [WEAK]
    B .
  ENDP

PMATCH_IRQHandler\
  PROC
    EXPORT PMATCH_IRQHandler [WEAK]
    B .
  ENDP

IDAC0_IRQHandler\
  PROC
    EXPORT IDAC0_IRQHandler [WEAK]
    B .
  ENDP

PLL0_IRQHandler\
  PROC
    EXPORT PLL0_IRQHandler [WEAK]
    B .
  ENDP
  
  ALIGN 
      
  END

;---eof-------------------------------------------------------------------------
