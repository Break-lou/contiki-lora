#include "ext_flash_include.h"
#include "generic_include.h"
#include "delay.h"
#include "clock_config.h"
extern uint8_t flash_wake_flag;


uint32_t get_ext_flash_clkdiv(void)
{
	uint32_t clkdiv = 0;
	uint32_t fsck_temp;
	uint32_t fsck = get_periph_clock( );
	fsck >>= 1;
	while(clkdiv < 16)
	{
		fsck_temp = fsck/(clkdiv+1);
		if(fsck_temp <= EXT_FLASH_SPI_MAX_CLK)
			break;
		clkdiv++;
	}
	return clkdiv;
}


void ext_flash_spi_init(void)
{
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_0;
	uint32_t clkdiv = get_ext_flash_clkdiv(); 
	uint32_t SI32_CLKCTRL_A_APBCLKG0_SPI = SI32_CLKCTRL_A_APBCLKG0_SPI0;
	
	EXT_FLASH_CS_OUT();
	EXT_FLASH_CS_HIGH();
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_PB0);
	
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_SPI|SI32_CLKCTRL_A_APBCLKG0_FLASHCTRL0);

	SI32_PBCFG_A_enable_xbar0_peripherals(SI32_PBCFG_0, SI32_PBCFG_A_XBAR0_SPI0EN );
	SI32_PBCFG_A_enable_crossbar_0(SI32_PBCFG_0);
	
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_3wire_master_mode(SI32_SPI);
	SI32_SPI_B_select_nss_data_count(SI32_SPI, 0);	
	SI32_SPI_B_set_data_length(SI32_SPI, 8);
	
	SI32_SPI_B_write_clkrate(SI32_SPI, clkdiv);
	SI32_SPI_B_select_clock_idle_low(SI32_SPI);
	SI32_SPI_B_select_data_change_second_edge(SI32_SPI);
	SI32_SPI_B_select_direction_msb_first(SI32_SPI);
	
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);
	SI32_SPI_B_clear_all_interrupts(SI32_SPI);
	
	SI32_SPI_B_select_operation_mode_normal(SI32_SPI);
	SI32_SPI_B_enable_module(SI32_SPI);
	
	
}

void ext_flash_port_init(void)
{
	EXT_FLASH_RESET_OUT();
	EXT_FLASH_RESET_HIGH();
	EXT_FLASH_CS_OUT();
	EXT_FLASH_CS_HIGH();
	
	SPI0_SCK_OUT();
	SPI0_MISO_IN();
	SPI0_MOSI_OUT();
}
void ext_flash_reset(void)
{
	EXT_FLASH_RESET_LOW();
	delay_Xus(1000);
	EXT_FLASH_RESET_HIGH();
	delay_Xus(12);
	flash_wake_flag = 1;
}

void ext_flash_spi_init_from_wakeup(void)
{
//	SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_0, PBX_0 | PBX_1 | PBX_2 | PBX_6 | PBX_7 | PBX_8 | PBX_9);

	ext_flash_port_init();
	ext_flash_spi_init();
	ext_flash_reset();
	
//	flash_init();	
//	flash_tat_init();

}
