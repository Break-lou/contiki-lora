#include "ext_flash_include.h"

int flash_hal_write_byte(uint8_t cmd)
{
	int ret = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	SI32_SPI_B_select_nss_data_count(SI32_SPI, 1);
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);	
	
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);	
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	EXT_FLASH_CS_LOW();
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, cmd);
	while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
	while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	EXT_FLASH_CS_HIGH();	
	return ret;
}

int flash_hal_read_byte(uint8_t cmd, uint8_t *rx)
{
	int ret = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);	
	
	EXT_FLASH_CS_LOW();
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, cmd);
	while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
	while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, 0);
	while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
	while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
	*rx = SI32_SPI_B_read_rx_fifo_u8(SI32_SPI);
	EXT_FLASH_CS_HIGH();
	return ret;

}

int flash_hal_read_buff(const uint8_t cmd, uint8_t *buf, uint16_t len)
{
	int ret = 0;
	uint16_t i = 0;	
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);
	EXT_FLASH_CS_LOW();
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, cmd);
	while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
	while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);

	while(len--)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, 0);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
		buf[i++] = SI32_SPI_B_read_rx_fifo_u8(SI32_SPI);
	}

	EXT_FLASH_CS_HIGH();
	return ret;	
}

int flash_hal_write_buff(const uint8_t cmd, const uint8_t *buf, uint16_t len)
{
	int ret = 0;
	uint16_t i = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
		
	SI32_SPI_B_select_transfer_count_one(SI32_SPI); 		
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI); 
	EXT_FLASH_CS_LOW();
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, cmd);
	while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
	while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);

	while(len--){
		SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, buf[i]);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		i++;
	}
	EXT_FLASH_CS_HIGH();

	return ret;
}

int flash_hal_write_then_read(const uint8_t *cmd, uint16_t cmd_len, uint8_t *buf, uint16_t buf_len)
{
	int ret = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
	SI32_SPI_B_select_transfer_count_four(SI32_SPI);

	SI32_SPI_B_flush_tx_fifo(SI32_SPI);
	EXT_FLASH_CS_LOW();
	while(cmd_len>=4)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u32(SI32_SPI, *(uint32_t *)cmd);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI) < 4);
		cmd_len -= 4;
		cmd += 4;
	}
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);
	while(cmd_len--)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u32(SI32_SPI, *cmd);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI) < 1);
		cmd++;
	}
	SI32_SPI_B_select_transfer_count_four(SI32_SPI);
	while(buf_len>=4)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u32(SI32_SPI, 0);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<4);
		*(uint32_t *)buf = SI32_SPI_B_read_rx_fifo_u32(SI32_SPI);
		buf += 4;
		buf_len -= 4;
	}
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);
	while(buf_len--)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, 0);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
		*buf++ = SI32_SPI_B_read_rx_fifo_u8(SI32_SPI);
	}

	EXT_FLASH_CS_HIGH();
	return ret;	
}


int flash_hal_write_then_write(const uint8_t *cmd, uint16_t cmd_len, const uint8_t *buf, uint16_t buf_len)
{
	int ret = 0;
//	uint16_t i = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
		
	SI32_SPI_B_select_transfer_count_four(SI32_SPI); 		
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI); 
	EXT_FLASH_CS_LOW();
	while(cmd_len>=4)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u32(SI32_SPI, *(uint32_t *)cmd);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<4);
		cmd_len -= 4;
		cmd += 4;
	}
	SI32_SPI_B_select_transfer_count_one(SI32_SPI); 		
	while(cmd_len--)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, *cmd);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
		cmd++;
	}
//	i = 0;
	SI32_SPI_B_select_transfer_count_four(SI32_SPI); 
	while(buf_len>=4)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u32(SI32_SPI, *(uint32_t *)buf);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<4);
		buf += 4;
		buf_len -= 4;
	}
	SI32_SPI_B_select_transfer_count_one(SI32_SPI); 	
	while(buf_len--)
	{
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
		SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, *buf);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
		buf++;
	}
	EXT_FLASH_CS_HIGH();

	return ret;
}

