//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
//
// Script: 0.57
// Version: 1

#ifndef __SI32_AES_A_REGISTERS_H__
#define __SI32_AES_A_REGISTERS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct SI32_AES_A_CONTROL_Struct
{
   union
   {
      struct
      {
         // AES Transfer Start
         volatile uint32_t XFRSTA: 1;
         // Key Capture Enable
         volatile uint32_t KEYCPEN: 1;
         // Encryption/Decryption Mode
         volatile uint32_t EDMD: 1;
                  uint32_t reserved0: 5;
         // Software Mode Enable
         volatile uint32_t SWMDEN: 1;
         // Bypass AES Operation Enable
         volatile uint32_t BEN: 1;
         // XOR Enable
         volatile uint32_t XOREN: 2;
         // Hardware Counter Mode Enable
         volatile uint32_t HCTREN: 1;
         // Hardware Cipher-Block Chaining Mode Enable
         volatile uint32_t HCBCEN: 1;
                  uint32_t reserved1: 2;
         // Keystore Size Select
         volatile uint32_t KEYSIZE: 2;
                  uint32_t reserved2: 6;
         // Error Interrupt Enable
         volatile uint32_t ERRIEN: 1;
         // Operation Complete Interrupt Enable
         volatile uint32_t OCIEN: 1;
                  uint32_t reserved3: 4;
         // AES Debug Mode
         volatile uint32_t DBGMD: 1;
         // Module Soft Reset
         volatile uint32_t RESET: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_CONTROL_XFRSTA_MASK  0x00000001
#define SI32_AES_A_CONTROL_XFRSTA_SHIFT  0
// Start the AES operation.
#define SI32_AES_A_CONTROL_XFRSTA_START_VALUE  1
#define SI32_AES_A_CONTROL_XFRSTA_START_U32 \
   (SI32_AES_A_CONTROL_XFRSTA_START_VALUE << SI32_AES_A_CONTROL_XFRSTA_SHIFT)

#define SI32_AES_A_CONTROL_KEYCPEN_MASK  0x00000002
#define SI32_AES_A_CONTROL_KEYCPEN_SHIFT  1
// Disable key capture.
#define SI32_AES_A_CONTROL_KEYCPEN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_KEYCPEN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_KEYCPEN_DISABLED_VALUE << SI32_AES_A_CONTROL_KEYCPEN_SHIFT)
// Enable key capture.
#define SI32_AES_A_CONTROL_KEYCPEN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_KEYCPEN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_KEYCPEN_ENABLED_VALUE << SI32_AES_A_CONTROL_KEYCPEN_SHIFT)

#define SI32_AES_A_CONTROL_EDMD_MASK  0x00000004
#define SI32_AES_A_CONTROL_EDMD_SHIFT  2
// AES module performs a decryption operation
#define SI32_AES_A_CONTROL_EDMD_DECRYPT_VALUE  0
#define SI32_AES_A_CONTROL_EDMD_DECRYPT_U32 \
   (SI32_AES_A_CONTROL_EDMD_DECRYPT_VALUE << SI32_AES_A_CONTROL_EDMD_SHIFT)
// AES module performs an encryption operation.
#define SI32_AES_A_CONTROL_EDMD_ENCRYPT_VALUE  1
#define SI32_AES_A_CONTROL_EDMD_ENCRYPT_U32 \
   (SI32_AES_A_CONTROL_EDMD_ENCRYPT_VALUE << SI32_AES_A_CONTROL_EDMD_SHIFT)

#define SI32_AES_A_CONTROL_SWMDEN_MASK  0x00000100
#define SI32_AES_A_CONTROL_SWMDEN_SHIFT  8
// Disable software mode.
#define SI32_AES_A_CONTROL_SWMDEN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_SWMDEN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_SWMDEN_DISABLED_VALUE << SI32_AES_A_CONTROL_SWMDEN_SHIFT)
// Enable software mode.
#define SI32_AES_A_CONTROL_SWMDEN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_SWMDEN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_SWMDEN_ENABLED_VALUE << SI32_AES_A_CONTROL_SWMDEN_SHIFT)

#define SI32_AES_A_CONTROL_BEN_MASK  0x00000200
#define SI32_AES_A_CONTROL_BEN_SHIFT  9
// Do not bypass AES operations.
#define SI32_AES_A_CONTROL_BEN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_BEN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_BEN_DISABLED_VALUE << SI32_AES_A_CONTROL_BEN_SHIFT)
// Bypass AES operations.
#define SI32_AES_A_CONTROL_BEN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_BEN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_BEN_ENABLED_VALUE << SI32_AES_A_CONTROL_BEN_SHIFT)

#define SI32_AES_A_CONTROL_XOREN_MASK  0x00000C00
#define SI32_AES_A_CONTROL_XOREN_SHIFT  10
// Disable the XOR paths.
#define SI32_AES_A_CONTROL_XOREN_XOR_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_XOREN_XOR_DISABLED_U32 \
   (SI32_AES_A_CONTROL_XOREN_XOR_DISABLED_VALUE << SI32_AES_A_CONTROL_XOREN_SHIFT)
// Enable the XOR input path, disable the XOR output path.
#define SI32_AES_A_CONTROL_XOREN_XOR_INPUT_VALUE  1
#define SI32_AES_A_CONTROL_XOREN_XOR_INPUT_U32 \
   (SI32_AES_A_CONTROL_XOREN_XOR_INPUT_VALUE << SI32_AES_A_CONTROL_XOREN_SHIFT)
// Disable the XOR input path, enable the XOR output path.
#define SI32_AES_A_CONTROL_XOREN_XOR_OUTPUT_VALUE  2
#define SI32_AES_A_CONTROL_XOREN_XOR_OUTPUT_U32 \
   (SI32_AES_A_CONTROL_XOREN_XOR_OUTPUT_VALUE << SI32_AES_A_CONTROL_XOREN_SHIFT)

#define SI32_AES_A_CONTROL_HCTREN_MASK  0x00001000
#define SI32_AES_A_CONTROL_HCTREN_SHIFT  12
// Disable hardware counter mode.
#define SI32_AES_A_CONTROL_HCTREN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_HCTREN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_HCTREN_DISABLED_VALUE << SI32_AES_A_CONTROL_HCTREN_SHIFT)
// Enable hardware counter mode.
#define SI32_AES_A_CONTROL_HCTREN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_HCTREN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_HCTREN_ENABLED_VALUE << SI32_AES_A_CONTROL_HCTREN_SHIFT)

#define SI32_AES_A_CONTROL_HCBCEN_MASK  0x00002000
#define SI32_AES_A_CONTROL_HCBCEN_SHIFT  13
// Disable hardware cipher-block chaining (CBC) mode.
#define SI32_AES_A_CONTROL_HCBCEN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_HCBCEN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_HCBCEN_DISABLED_VALUE << SI32_AES_A_CONTROL_HCBCEN_SHIFT)
// Enable hardware cipher-block chaining (CBC) mode.
#define SI32_AES_A_CONTROL_HCBCEN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_HCBCEN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_HCBCEN_ENABLED_VALUE << SI32_AES_A_CONTROL_HCBCEN_SHIFT)

#define SI32_AES_A_CONTROL_KEYSIZE_MASK  0x00030000
#define SI32_AES_A_CONTROL_KEYSIZE_SHIFT  16
// Key is composed of 128 bits.
#define SI32_AES_A_CONTROL_KEYSIZE_KEY128_VALUE  0
#define SI32_AES_A_CONTROL_KEYSIZE_KEY128_U32 \
   (SI32_AES_A_CONTROL_KEYSIZE_KEY128_VALUE << SI32_AES_A_CONTROL_KEYSIZE_SHIFT)
// Key is composed of 192 bits.
#define SI32_AES_A_CONTROL_KEYSIZE_KEY192_VALUE  1
#define SI32_AES_A_CONTROL_KEYSIZE_KEY192_U32 \
   (SI32_AES_A_CONTROL_KEYSIZE_KEY192_VALUE << SI32_AES_A_CONTROL_KEYSIZE_SHIFT)
// Key is composed of 256 bits.
#define SI32_AES_A_CONTROL_KEYSIZE_KEY256_VALUE  2
#define SI32_AES_A_CONTROL_KEYSIZE_KEY256_U32 \
   (SI32_AES_A_CONTROL_KEYSIZE_KEY256_VALUE << SI32_AES_A_CONTROL_KEYSIZE_SHIFT)

#define SI32_AES_A_CONTROL_ERRIEN_MASK  0x01000000
#define SI32_AES_A_CONTROL_ERRIEN_SHIFT  24
// Disable the error interrupt.
#define SI32_AES_A_CONTROL_ERRIEN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_ERRIEN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_ERRIEN_DISABLED_VALUE << SI32_AES_A_CONTROL_ERRIEN_SHIFT)
// Enable the error interrupt.
#define SI32_AES_A_CONTROL_ERRIEN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_ERRIEN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_ERRIEN_ENABLED_VALUE << SI32_AES_A_CONTROL_ERRIEN_SHIFT)

#define SI32_AES_A_CONTROL_OCIEN_MASK  0x02000000
#define SI32_AES_A_CONTROL_OCIEN_SHIFT  25
// Disable the operation complete interrupt.
#define SI32_AES_A_CONTROL_OCIEN_DISABLED_VALUE  0
#define SI32_AES_A_CONTROL_OCIEN_DISABLED_U32 \
   (SI32_AES_A_CONTROL_OCIEN_DISABLED_VALUE << SI32_AES_A_CONTROL_OCIEN_SHIFT)
// Enable the operation complete interrupt.
#define SI32_AES_A_CONTROL_OCIEN_ENABLED_VALUE  1
#define SI32_AES_A_CONTROL_OCIEN_ENABLED_U32 \
   (SI32_AES_A_CONTROL_OCIEN_ENABLED_VALUE << SI32_AES_A_CONTROL_OCIEN_SHIFT)

#define SI32_AES_A_CONTROL_DBGMD_MASK  0x40000000
#define SI32_AES_A_CONTROL_DBGMD_SHIFT  30
// A debug breakpoint will cause the AES module to halt.
#define SI32_AES_A_CONTROL_DBGMD_HALT_VALUE  0
#define SI32_AES_A_CONTROL_DBGMD_HALT_U32 \
   (SI32_AES_A_CONTROL_DBGMD_HALT_VALUE << SI32_AES_A_CONTROL_DBGMD_SHIFT)
// The AES module will continue to operate while the core is halted in debug mode.
#define SI32_AES_A_CONTROL_DBGMD_RUN_VALUE  1
#define SI32_AES_A_CONTROL_DBGMD_RUN_U32 \
   (SI32_AES_A_CONTROL_DBGMD_RUN_VALUE << SI32_AES_A_CONTROL_DBGMD_SHIFT)

#define SI32_AES_A_CONTROL_RESET_MASK  0x80000000
#define SI32_AES_A_CONTROL_RESET_SHIFT  31
// AES module is not in soft reset.
#define SI32_AES_A_CONTROL_RESET_INACTIVE_VALUE  0U
#define SI32_AES_A_CONTROL_RESET_INACTIVE_U32 \
   (SI32_AES_A_CONTROL_RESET_INACTIVE_VALUE << SI32_AES_A_CONTROL_RESET_SHIFT)
// AES module is in soft reset and none of the module bits can be accessed.
#define SI32_AES_A_CONTROL_RESET_ACTIVE_VALUE  1U
#define SI32_AES_A_CONTROL_RESET_ACTIVE_U32 \
   (SI32_AES_A_CONTROL_RESET_ACTIVE_VALUE << SI32_AES_A_CONTROL_RESET_SHIFT)



struct SI32_AES_A_XFRSIZE_Struct
{
   union
   {
      struct
      {
         // Transfer Size
         volatile uint32_t XFRSIZE_BITS: 11;
                  uint32_t reserved0: 21;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_XFRSIZE_XFRSIZE_MASK  0x000007FF
#define SI32_AES_A_XFRSIZE_XFRSIZE_SHIFT  0



struct SI32_AES_A_DATAFIFO_Struct
{
   union
   {
      struct
      {
         // Input/Output Data FIFO Access
         volatile uint32_t DATAFIFO_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_DATAFIFO_DATAFIFO_MASK  0xFFFFFFFF
#define SI32_AES_A_DATAFIFO_DATAFIFO_SHIFT  0



struct SI32_AES_A_XORFIFO_Struct
{
   union
   {
      struct
      {
         // XOR Data FIFO Access
         volatile uint32_t XORFIFO_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_XORFIFO_XORFIFO_MASK  0xFFFFFFFF
#define SI32_AES_A_XORFIFO_XORFIFO_SHIFT  0



struct SI32_AES_A_HWKEY0_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 0
         volatile uint32_t HWKEY0_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY0_HWKEY0_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY0_HWKEY0_SHIFT  0



struct SI32_AES_A_HWKEY1_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 1
         volatile uint32_t HWKEY1_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY1_HWKEY1_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY1_HWKEY1_SHIFT  0



struct SI32_AES_A_HWKEY2_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 2
         volatile uint32_t HWKEY2_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY2_HWKEY2_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY2_HWKEY2_SHIFT  0



struct SI32_AES_A_HWKEY3_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 3
         volatile uint32_t HWKEY3_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY3_HWKEY3_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY3_HWKEY3_SHIFT  0



struct SI32_AES_A_HWKEY4_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 4
         volatile uint32_t HWKEY4_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY4_HWKEY4_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY4_HWKEY4_SHIFT  0



struct SI32_AES_A_HWKEY5_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 5
         volatile uint32_t HWKEY5_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY5_HWKEY5_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY5_HWKEY5_SHIFT  0



struct SI32_AES_A_HWKEY6_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 6
         volatile uint32_t HWKEY6_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY6_HWKEY6_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY6_HWKEY6_SHIFT  0



struct SI32_AES_A_HWKEY7_Struct
{
   union
   {
      struct
      {
         // Hardware Key Word 7
         volatile uint32_t HWKEY7_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWKEY7_HWKEY7_MASK  0xFFFFFFFF
#define SI32_AES_A_HWKEY7_HWKEY7_SHIFT  0



struct SI32_AES_A_HWCTR0_Struct
{
   union
   {
      struct
      {
         // Hardware Counter Word 0
         volatile uint32_t HWCTR0_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWCTR0_HWCTR0_MASK  0xFFFFFFFF
#define SI32_AES_A_HWCTR0_HWCTR0_SHIFT  0



struct SI32_AES_A_HWCTR1_Struct
{
   union
   {
      struct
      {
         // Hardware Counter Word 1
         volatile uint32_t HWCTR1_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWCTR1_HWCTR1_MASK  0xFFFFFFFF
#define SI32_AES_A_HWCTR1_HWCTR1_SHIFT  0



struct SI32_AES_A_HWCTR2_Struct
{
   union
   {
      struct
      {
         // Hardware Counter Word 2
         volatile uint32_t HWCTR2_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWCTR2_HWCTR2_MASK  0xFFFFFFFF
#define SI32_AES_A_HWCTR2_HWCTR2_SHIFT  0



struct SI32_AES_A_HWCTR3_Struct
{
   union
   {
      struct
      {
         // Hardware Counter Word 3
         volatile uint32_t HWCTR3_BITS;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_HWCTR3_HWCTR3_MASK  0xFFFFFFFF
#define SI32_AES_A_HWCTR3_HWCTR3_SHIFT  0



struct SI32_AES_A_STATUS_Struct
{
   union
   {
      struct
      {
         // Input/Output Data FIFO Underrun Flag
         volatile uint32_t DURF: 1;
         // Input/Output Data FIFO Overrun Flag
         volatile uint32_t DORF: 1;
         // XOR Data FIFO Overrun Flag
         volatile uint32_t XORF: 1;
                  uint32_t reserved0: 1;
         // Input/Output Data FIFO Level
         volatile uint32_t DFIFOLVL: 3;
                  uint32_t reserved1: 1;
         // XOR Data FIFO Level
         volatile uint32_t XFIFOLVL: 3;
                  uint32_t reserved2: 5;
         // Module Busy Flag
         volatile uint32_t BUSYF: 1;
                  uint32_t reserved3: 13;
         // Error Interrupt Flag
         volatile uint32_t ERRI: 1;
         // Operation Complete Interrupt Flag
         volatile uint32_t OCI: 1;
      };
      volatile uint32_t U32;
   };
};

#define SI32_AES_A_STATUS_DURF_MASK  0x00000001
#define SI32_AES_A_STATUS_DURF_SHIFT  0
// No input/output data FIFO underrun.
#define SI32_AES_A_STATUS_DURF_NOT_SET_VALUE  0
#define SI32_AES_A_STATUS_DURF_NOT_SET_U32 \
   (SI32_AES_A_STATUS_DURF_NOT_SET_VALUE << SI32_AES_A_STATUS_DURF_SHIFT)
// An input/output data FIFO underrun has occurred.
#define SI32_AES_A_STATUS_DURF_SET_VALUE  1
#define SI32_AES_A_STATUS_DURF_SET_U32 \
   (SI32_AES_A_STATUS_DURF_SET_VALUE << SI32_AES_A_STATUS_DURF_SHIFT)

#define SI32_AES_A_STATUS_DORF_MASK  0x00000002
#define SI32_AES_A_STATUS_DORF_SHIFT  1
// No input/output data FIFO overrun.
#define SI32_AES_A_STATUS_DORF_NOT_SET_VALUE  0
#define SI32_AES_A_STATUS_DORF_NOT_SET_U32 \
   (SI32_AES_A_STATUS_DORF_NOT_SET_VALUE << SI32_AES_A_STATUS_DORF_SHIFT)
// An input/output data FIFO overrun has occurred.
#define SI32_AES_A_STATUS_DORF_SET_VALUE  1
#define SI32_AES_A_STATUS_DORF_SET_U32 \
   (SI32_AES_A_STATUS_DORF_SET_VALUE << SI32_AES_A_STATUS_DORF_SHIFT)

#define SI32_AES_A_STATUS_XORF_MASK  0x00000004
#define SI32_AES_A_STATUS_XORF_SHIFT  2
// No XOR data FIFO overrun.
#define SI32_AES_A_STATUS_XORF_NOT_SET_VALUE  0
#define SI32_AES_A_STATUS_XORF_NOT_SET_U32 \
   (SI32_AES_A_STATUS_XORF_NOT_SET_VALUE << SI32_AES_A_STATUS_XORF_SHIFT)
// An XOR data FIFO overrun has occurred.
#define SI32_AES_A_STATUS_XORF_SET_VALUE  1
#define SI32_AES_A_STATUS_XORF_SET_U32 \
   (SI32_AES_A_STATUS_XORF_SET_VALUE << SI32_AES_A_STATUS_XORF_SHIFT)

#define SI32_AES_A_STATUS_DFIFOLVL_MASK  0x00000070
#define SI32_AES_A_STATUS_DFIFOLVL_SHIFT  4
// Input/Output data FIFO is empty.
#define SI32_AES_A_STATUS_DFIFOLVL_EMPTY_VALUE  0
#define SI32_AES_A_STATUS_DFIFOLVL_EMPTY_U32 \
   (SI32_AES_A_STATUS_DFIFOLVL_EMPTY_VALUE << SI32_AES_A_STATUS_DFIFOLVL_SHIFT)
// Input/Output data FIFO contains 1 word.
#define SI32_AES_A_STATUS_DFIFOLVL_1WORD_VALUE  1
#define SI32_AES_A_STATUS_DFIFOLVL_1WORD_U32 \
   (SI32_AES_A_STATUS_DFIFOLVL_1WORD_VALUE << SI32_AES_A_STATUS_DFIFOLVL_SHIFT)
// Input/Output data FIFO contains 2 words.
#define SI32_AES_A_STATUS_DFIFOLVL_2WORDS_VALUE  2
#define SI32_AES_A_STATUS_DFIFOLVL_2WORDS_U32 \
   (SI32_AES_A_STATUS_DFIFOLVL_2WORDS_VALUE << SI32_AES_A_STATUS_DFIFOLVL_SHIFT)
// Input/Output data FIFO contains 3 words.
#define SI32_AES_A_STATUS_DFIFOLVL_3WORDS_VALUE  3
#define SI32_AES_A_STATUS_DFIFOLVL_3WORDS_U32 \
   (SI32_AES_A_STATUS_DFIFOLVL_3WORDS_VALUE << SI32_AES_A_STATUS_DFIFOLVL_SHIFT)
// Input/Output data FIFO contains 4 words (full).
#define SI32_AES_A_STATUS_DFIFOLVL_FULL_VALUE  4
#define SI32_AES_A_STATUS_DFIFOLVL_FULL_U32 \
   (SI32_AES_A_STATUS_DFIFOLVL_FULL_VALUE << SI32_AES_A_STATUS_DFIFOLVL_SHIFT)

#define SI32_AES_A_STATUS_XFIFOLVL_MASK  0x00000700
#define SI32_AES_A_STATUS_XFIFOLVL_SHIFT  8
// XOR data FIFO is empty.
#define SI32_AES_A_STATUS_XFIFOLVL_EMPTY_VALUE  0
#define SI32_AES_A_STATUS_XFIFOLVL_EMPTY_U32 \
   (SI32_AES_A_STATUS_XFIFOLVL_EMPTY_VALUE << SI32_AES_A_STATUS_XFIFOLVL_SHIFT)
// XOR data FIFO contains 1 word.
#define SI32_AES_A_STATUS_XFIFOLVL_1WORD_VALUE  1
#define SI32_AES_A_STATUS_XFIFOLVL_1WORD_U32 \
   (SI32_AES_A_STATUS_XFIFOLVL_1WORD_VALUE << SI32_AES_A_STATUS_XFIFOLVL_SHIFT)
// XOR data FIFO contains 2 words.
#define SI32_AES_A_STATUS_XFIFOLVL_2WORDS_VALUE  2
#define SI32_AES_A_STATUS_XFIFOLVL_2WORDS_U32 \
   (SI32_AES_A_STATUS_XFIFOLVL_2WORDS_VALUE << SI32_AES_A_STATUS_XFIFOLVL_SHIFT)
// XOR data FIFO contains 3 words.
#define SI32_AES_A_STATUS_XFIFOLVL_3WORDS_VALUE  3
#define SI32_AES_A_STATUS_XFIFOLVL_3WORDS_U32 \
   (SI32_AES_A_STATUS_XFIFOLVL_3WORDS_VALUE << SI32_AES_A_STATUS_XFIFOLVL_SHIFT)
// XOR data FIFO contains 4 words (full).
#define SI32_AES_A_STATUS_XFIFOLVL_FULL_VALUE  4
#define SI32_AES_A_STATUS_XFIFOLVL_FULL_U32 \
   (SI32_AES_A_STATUS_XFIFOLVL_FULL_VALUE << SI32_AES_A_STATUS_XFIFOLVL_SHIFT)

#define SI32_AES_A_STATUS_BUSYF_MASK  0x00010000
#define SI32_AES_A_STATUS_BUSYF_SHIFT  16
// AES module is not busy.
#define SI32_AES_A_STATUS_BUSYF_NOT_SET_VALUE  0
#define SI32_AES_A_STATUS_BUSYF_NOT_SET_U32 \
   (SI32_AES_A_STATUS_BUSYF_NOT_SET_VALUE << SI32_AES_A_STATUS_BUSYF_SHIFT)
// AES module is completing an operation.
#define SI32_AES_A_STATUS_BUSYF_SET_VALUE  1
#define SI32_AES_A_STATUS_BUSYF_SET_U32 \
   (SI32_AES_A_STATUS_BUSYF_SET_VALUE << SI32_AES_A_STATUS_BUSYF_SHIFT)

#define SI32_AES_A_STATUS_ERRI_MASK  0x40000000
#define SI32_AES_A_STATUS_ERRI_SHIFT  30
// AES error interrupt has not occurred.
#define SI32_AES_A_STATUS_ERRI_NOT_SET_VALUE  0
#define SI32_AES_A_STATUS_ERRI_NOT_SET_U32 \
   (SI32_AES_A_STATUS_ERRI_NOT_SET_VALUE << SI32_AES_A_STATUS_ERRI_SHIFT)
// AES error interrupt has occurred.
#define SI32_AES_A_STATUS_ERRI_SET_VALUE  1
#define SI32_AES_A_STATUS_ERRI_SET_U32 \
   (SI32_AES_A_STATUS_ERRI_SET_VALUE << SI32_AES_A_STATUS_ERRI_SHIFT)

#define SI32_AES_A_STATUS_OCI_MASK  0x80000000
#define SI32_AES_A_STATUS_OCI_SHIFT  31
// AES operation complete interrupt has not occurred.
#define SI32_AES_A_STATUS_OCI_NOT_SET_VALUE  0U
#define SI32_AES_A_STATUS_OCI_NOT_SET_U32 \
   (SI32_AES_A_STATUS_OCI_NOT_SET_VALUE << SI32_AES_A_STATUS_OCI_SHIFT)
// AES operation complete interrupt occurred.
#define SI32_AES_A_STATUS_OCI_SET_VALUE  1U
#define SI32_AES_A_STATUS_OCI_SET_U32 \
   (SI32_AES_A_STATUS_OCI_SET_VALUE << SI32_AES_A_STATUS_OCI_SHIFT)



typedef struct SI32_AES_A_Struct
{
   struct SI32_AES_A_CONTROL_Struct                CONTROL        ; // Base Address + 0x0
   volatile uint32_t                               CONTROL_SET;
   volatile uint32_t                               CONTROL_CLR;
   uint32_t                                        reserved0;
   struct SI32_AES_A_XFRSIZE_Struct                XFRSIZE        ; // Base Address + 0x10
   uint32_t                                        reserved1;
   uint32_t                                        reserved2;
   uint32_t                                        reserved3;
   struct SI32_AES_A_DATAFIFO_Struct               DATAFIFO       ; // Base Address + 0x20
   uint32_t                                        reserved4;
   uint32_t                                        reserved5;
   uint32_t                                        reserved6;
   struct SI32_AES_A_XORFIFO_Struct                XORFIFO        ; // Base Address + 0x30
   uint32_t                                        reserved7;
   uint32_t                                        reserved8;
   uint32_t                                        reserved9;
   struct SI32_AES_A_HWKEY0_Struct                 HWKEY0         ; // Base Address + 0x40
   uint32_t                                        reserved10;
   uint32_t                                        reserved11;
   uint32_t                                        reserved12;
   struct SI32_AES_A_HWKEY1_Struct                 HWKEY1         ; // Base Address + 0x50
   uint32_t                                        reserved13;
   uint32_t                                        reserved14;
   uint32_t                                        reserved15;
   struct SI32_AES_A_HWKEY2_Struct                 HWKEY2         ; // Base Address + 0x60
   uint32_t                                        reserved16;
   uint32_t                                        reserved17;
   uint32_t                                        reserved18;
   struct SI32_AES_A_HWKEY3_Struct                 HWKEY3         ; // Base Address + 0x70
   uint32_t                                        reserved19;
   uint32_t                                        reserved20;
   uint32_t                                        reserved21;
   struct SI32_AES_A_HWKEY4_Struct                 HWKEY4         ; // Base Address + 0x80
   uint32_t                                        reserved22;
   uint32_t                                        reserved23;
   uint32_t                                        reserved24;
   struct SI32_AES_A_HWKEY5_Struct                 HWKEY5         ; // Base Address + 0x90
   uint32_t                                        reserved25;
   uint32_t                                        reserved26;
   uint32_t                                        reserved27;
   struct SI32_AES_A_HWKEY6_Struct                 HWKEY6         ; // Base Address + 0xa0
   uint32_t                                        reserved28;
   uint32_t                                        reserved29;
   uint32_t                                        reserved30;
   struct SI32_AES_A_HWKEY7_Struct                 HWKEY7         ; // Base Address + 0xb0
   uint32_t                                        reserved31;
   uint32_t                                        reserved32;
   uint32_t                                        reserved33;
   struct SI32_AES_A_HWCTR0_Struct                 HWCTR0         ; // Base Address + 0xc0
   uint32_t                                        reserved34;
   uint32_t                                        reserved35;
   uint32_t                                        reserved36;
   struct SI32_AES_A_HWCTR1_Struct                 HWCTR1         ; // Base Address + 0xd0
   uint32_t                                        reserved37;
   uint32_t                                        reserved38;
   uint32_t                                        reserved39;
   struct SI32_AES_A_HWCTR2_Struct                 HWCTR2         ; // Base Address + 0xe0
   uint32_t                                        reserved40;
   uint32_t                                        reserved41;
   uint32_t                                        reserved42;
   struct SI32_AES_A_HWCTR3_Struct                 HWCTR3         ; // Base Address + 0xf0
   uint32_t                                        reserved43;
   uint32_t                                        reserved44;
   uint32_t                                        reserved45;
   struct SI32_AES_A_STATUS_Struct                 STATUS         ; // Base Address + 0x100
   volatile uint32_t                               STATUS_SET;
   volatile uint32_t                               STATUS_CLR;
   uint32_t                                        reserved46;
} SI32_AES_A_Type;

#ifdef __cplusplus
}
#endif

#endif // __SI32_AES_A_REGISTERS_H__

//-eof--------------------------------------------------------------------------

