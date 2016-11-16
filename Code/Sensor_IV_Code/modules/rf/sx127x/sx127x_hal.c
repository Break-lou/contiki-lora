#include "sx127x_hal.h"
#include "spi_config.h"
#include "delay.h"

void SX1276_InitIO(void)
{
	//LORA_RST
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, SX1276_RST_PIN);
	
	//DIO0配置		配置成PMAN形式	
	uint16_t old_pwpol = SI32_PMU_A_read_pwpol(SI32_PMU_0);
	uint32_t old_pwen = SI32_PMU_A_read_pwen(SI32_PMU_0);
	SI32_PMU_A_write_pwpol(SI32_PMU_0, old_pwpol&LORA_DIO0_INIT_POL);	    		//高电平触发	0x7fff--利尔达模块	0xefff--标签模块
	SI32_PMU_A_write_pwen(SI32_PMU_0, LORA_DIO0_WAKE_SOURCE|old_pwen);		  	
}	

void SX1276_InitSPI(void)
{
	spi1_init();
}

void SX1276_SetReset(uint8_t status)
{
	if( status== RADIO_RESET_ON )
	{
		//set reset pin to 0
		SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3,SX1276_RST_PIN);
	}
	else
	{
		//set reset pin to 1
		SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3,SX1276_RST_PIN);
	}
}

void SX1276_Reset(void)
{
	SX1276_SetReset(RADIO_RESET_ON);
	//延时1ms
	delay_Xus(1000);
	SX1276_SetReset( RADIO_RESET_OFF );
	//延时15ms
	delay_Xus(15000);
}

void SX1276_WriteBuffer(uint8_t addr, uint8_t *buffer, uint8_t size)
{
	spi1_write_buffer_with_addr(addr | 0x80, buffer, size);
}

void SX1276_ReadBuffer(uint8_t addr, uint8_t *buffer, uint8_t size)
{
	spi1_read_buffer_with_addr(addr, buffer, size);
}

void SX1276_Write(uint8_t addr, uint8_t data)
{
	SX1276_WriteBuffer(addr, &data, 1);
}

void SX1276_Read(uint8_t addr, uint8_t *data)
{
	SX1276_ReadBuffer(addr, data, 1);
}

void SX1276_WirteFIFO(uint8_t *buffer, uint8_t size)
{
	SX1276_WriteBuffer(0, buffer, size);
}

void SX1276_ReadFIFO(uint8_t *buffer, uint8_t size)
{
	SX1276_ReadBuffer( 0, buffer, size );
}

void SX1276_WriteRxTx(bool txEnable)
{
	if(txEnable != 0)
	{
		//使能发送
		SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3, SX1276_TXE_PIN);
	}
	else
	{
		//使能接收
		SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3, SX1276_RXE_PIN);
	}
}

void SX1276_EnableRFSW(void)
{
	SI32_PBSTD_A_write_pins_high(RFSW_EN_PORT, RFSW_EN_PIN);
}

