#ifndef __SX127X_HAL_H__
#define __SX127X_HAL_H__

#include <stdint.h>
#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>
#include <SI32_PMU_A_Type.h>
#include <SI32_SPI_B_Type.h>
#include "sx127x.h"
#include "board_cfg.h"

//-------------------------硬件IO定义-------------------------
#define SX1276_DIO0_PIN		DIO0_PIN		
#define SX1276_DIO1_PIN		DIO1_PIN		
#define SX1276_DIO2_PIN		DIO2_PIN		
#define SX1276_DIO4_PIN		DIO4_PIN		
#define SX1276_TXE_PIN		RFSW_EN_PIN			
#define SX1276_RXE_PIN		RFSW_EN_PIN			

#define SX1276_RST_PIN		LORA_RST_PIN			//电路图中缺一个LORA_RST,暂用P3.4连接		

#define SX1276_RXE_OUT_LOW()			SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3,SX1276_RXE_PIN)
#define SX1276_RXE_OUT_HIGH()			SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3,SX1276_RXE_PIN)
#define SX1276_TXE_OUT_LOW()			SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3,SX1276_TXE_PIN)
#define SX1276_TXE_OUT_HIGH()			SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3,SX1276_TXE_PIN)


typedef enum
{
	RADIO_RESET_OFF=0,
    RADIO_RESET_ON,
}SX1276_tRadioResetState;

void SX1276_InitIO(void);
void SX1276_Reset(void);
void SX1276_InitSPI(void);
void SX1276_Write(uint8_t addr, uint8_t data);
void SX1276_Read(uint8_t addr, uint8_t *data);
void SX1276_WriteRxTx(bool);
void SX1276_WriteBuffer(uint8_t addr, uint8_t *buffer, uint8_t size);
void SX1276_ReadBuffer(uint8_t addr, uint8_t *buffer, uint8_t size);
void SX1276_WirteFIFO(uint8_t *buffer, uint8_t size);
void SX1276_ReadFIFO(uint8_t *buffer, uint8_t size);
void SX1276_EnableRFSW(void);

#endif
