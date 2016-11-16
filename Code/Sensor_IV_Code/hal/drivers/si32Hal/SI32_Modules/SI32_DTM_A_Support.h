//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// This file applies to the SIM3L1XX_DTM_A module
//
// Version: 1

#ifndef __SI32_DTM_A_Support_Guard__
#define __SI32_DTM_A_Support_Guard__

#include <stdint.h>
#include <si32_device.h>
#include <SI32_DMAXBAR_A_Support.h>

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// These are the DTM state flags and values

// DTM Channels within a DTM module
#define DTM_DMA_A       SI32_DTM_A_STATE_DTMCHSEL_CH_A_VALUE
#define DTM_DMA_B       SI32_DTM_A_STATE_DTMCHSEL_CH_B_VALUE
#define DTM_DMA_C       SI32_DTM_A_STATE_DTMCHSEL_CH_C_VALUE
#define DTM_DMA_D       SI32_DTM_A_STATE_DTMCHSEL_CH_D_VALUE

// DTM sources for each state
#define DTM_SRC_MEMORY      15
#define DTM_SRC_DMA0T1      14    // dma_io_dmatrig1_req
#define DTM_SRC_DMA0T0      13    // dma_io_dmatrig0_req
#define DTM_SRC_ENCDEC0      9    // dma_enc0_rx_sreq
#define DTM_SRC_EPCA0        8    // dma_pca0_rx_req
#define DTM_SRC_SARADC0      7    // dma_adc0_req
#define DTM_SRC_I2C0         6    // dma_smb0_rx_sreq
#define DTM_SRC_USART0       4    // dma_usart0_rx_sreq
#define DTM_SRC_AES0         2    // dma_aes_tx_req
#define DTM_SRC_SPI1         1    // dma_spi1_rx_req
#define DTM_SRC_SPI0         0    // dma_spi0_rx_req

// DTM destinations for each state
#define DTM_DST_MEMORY      15
#define DTM_DST_DMA0T1      14    // dma_io_dmatrig1_req
#define DTM_DST_DMA0T0      13    // dma_io_dmatrig0_req
#define DTM_DST_ENCDEC0      9    // dma_enc0_tx_sreq
#define DTM_DST_EPCA0        8    // dma_pca0_tx_req
#define DTM_DST_IDAC0        7    // dma_idac10_sreq
#define DTM_DST_I2C0         6    // dma_smb0_tx_sreq
#define DTM_DST_USART0       4    // dma_usart0_tx_sreq
#define DTM_DST_AES0_XOR     3    // dma_aes_xor_req
#define DTM_DST_AES0         2    // dma_aes_rx_req
#define DTM_DST_SPI1         1    // dma_spi1_tx_req
#define DTM_DST_SPI0         0    // dma_spi0_tx_req

#define DTM_DONE            15

// Additional flags for each state
#define DTM_INHSPOL     SI32_DTM_A_STATE_INHSPOL_MASK
#define DTM_DTMINH      SI32_DTM_A_STATE_DTMINH_MASK
#define DTM_MSTDECEN    SI32_DTM_A_STATE_MSTDECEN_MASK
#define DTM_TOERRIEN    SI32_DTM_A_STATE_TOERRIEN_MASK
#define DTM_SECSTIEN    SI32_DTM_A_STATE_SECSTIEN_MASK
#define DTM_PRISTIEN    SI32_DTM_A_STATE_PRISTIEN_MASK

//-----------------------------------------------------------------------------
// Define the DTM state

#define DTM_STATE(ch, src, dst, pri, sec, cnt) \
    ( (((ch) << SI32_DTM_A_STATE_DTMCHSEL_SHIFT) & SI32_DTM_A_STATE_DTMCHSEL_MASK) \
    | (((src) << SI32_DTM_A_STATE_SRCMOD_SHIFT) & SI32_DTM_A_STATE_SRCMOD_MASK) \
    | (((dst) << SI32_DTM_A_STATE_DSTMOD_SHIFT) & SI32_DTM_A_STATE_DSTMOD_MASK) \
    | (((pri) << SI32_DTM_A_STATE_PRIST_SHIFT) & SI32_DTM_A_STATE_PRIST_MASK) \
    | (((sec) << SI32_DTM_A_STATE_SECST_SHIFT) & SI32_DTM_A_STATE_SECST_MASK) \
    | (((cnt) << SI32_DTM_A_STATE_STRELOAD_SHIFT) & SI32_DTM_A_STATE_STRELOAD_MASK) )

typedef struct SI32_DTM_A_STATE_Struct SI32_DTM_A_STATE_Type;

// Structure for associating each DTM unit with its assigned MCU resources
typedef struct SI32_DTM_Unit_Struct
{
    SI32_DTM_A_Type *               pBASE;
    uint32_t                        AHBCLKG_Mask;
    uint32_t                        APBCLKG0_Mask;
    IRQn_Type                       NVIC_IRQn;
    SI32_DMAXBAR_CHNSEL_Enum_Type   DMAXBAR_Select[4];
}
SI32_DTM_Unit_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_DTM_A_Support_Guard__

//-eof--------------------------------------------------------------------------
