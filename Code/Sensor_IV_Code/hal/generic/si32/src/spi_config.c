#include "spi_config.h"

void vdrv_on(void);

void spi1_init(void)
{
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_1;
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_PB0);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_2, SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN);	//PB2.4 2.6 2.7 输出
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_2, SPI1_MISO_PIN);								//PB2.5 输入
	
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_SPI1|SI32_CLKCTRL_A_APBCLKG0_FLASHCTRL0);
	SI32_PBCFG_A_enable_spi1_on_crossbar(SI32_PBCFG_0); 	

	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_4wire_master_mode_nss_high(SI32_SPI);				// 
	SI32_SPI_B_select_nss_data_count(SI32_SPI, 0);	
	SI32_SPI_B_set_data_length(SI32_SPI, 8);
	
	SI32_SPI_B_write_clkrate(SI32_SPI, 1);						//SPI1时钟频率=F(APB)/2*(clkrate+1),5M APB，则SPI1频率为2.5M
	SI32_SPI_B_select_clock_idle_low(SI32_SPI);
	SI32_SPI_B_select_data_change_second_edge(SI32_SPI);
	SI32_SPI_B_select_direction_msb_first(SI32_SPI);
	
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);
	SI32_SPI_B_clear_all_interrupts(SI32_SPI);
	
	SI32_SPI_B_select_master_mode(SI32_SPI_1);
	SI32_SPI_B_enable_module(SI32_SPI);
	
	vdrv_on();

}

void vdrv_on(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG0_DCDC0CEN_ENABLED_U32
									  |SI32_CLKCTRL_A_APBCLKG0_LCD0CEN_ENABLED_U32);
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0,
									  SI32_CLKCTRL_A_APBCLKG1_MISC0CEN_ENABLED_U32);

	SI32_PMU_A_select_vdrv_connected_to_vbat(SI32_PMU_0);
}

int spi1_write_buffer_with_addr(uint8_t addr, const uint8_t* buf, uint8_t len)
{
	int ret = 0;
	uint8_t i = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_1;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_4wire_master_mode_nss_high(SI32_SPI);
	
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);
	
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);
	//NSS拉低
	SI32_SPI_B_clear_nss (SI32_SPI);	
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, addr);
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
	//NSS拉高
	SI32_SPI_B_set_nss (SI32_SPI);
	
	return ret;
}

int spi1_read_buffer_with_addr(const uint8_t addr, uint8_t* buf, uint8_t len)
{
	int ret = 0;
	uint8_t i = 0;
	SI32_SPI_B_Type* SI32_SPI = SI32_SPI_1;
	SI32_SPI_B_disable_auto_nss_mode(SI32_SPI);
	SI32_SPI_B_select_4wire_master_mode_nss_high(SI32_SPI);
	
	SI32_SPI_B_select_transfer_count_one(SI32_SPI);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	SI32_SPI_B_flush_tx_fifo(SI32_SPI);	
	SI32_SPI_B_clear_nss (SI32_SPI);
	SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, addr);
	while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));	
	while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
	SI32_SPI_B_flush_rx_fifo(SI32_SPI);		
	
	while(len--)
	{	
		SI32_SPI_B_write_tx_fifo_u8(SI32_SPI, 0);
		while(!SI32_SPI_B_is_shift_register_empty_interrupt_pending(SI32_SPI));
		while(SI32_SPI_B_get_rx_fifo_count(SI32_SPI)<1);
		buf[i++] = SI32_SPI_B_read_rx_fifo_u8(SI32_SPI);
		SI32_SPI_B_flush_rx_fifo(SI32_SPI);
	}
	SI32_SPI_B_set_nss (SI32_SPI);
	return ret;	
}

void spi1_init_from_wakeup(void)
{
	SI32_PBCFG_A_enable_spi1_on_crossbar(SI32_PBCFG_0);			
	//设置对应IO
//	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_2, 0x000000d0);
//	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_2, 0x0000020);
	SI32_PBSTD_A_set_pins_digital_input(SPI1_PORT, SPI1_MISO_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SPI1_PORT, SPI1_SCK_PIN|SPI1_MOSI_PIN|SPI1_NSS_PIN); 
	vdrv_on();
}

void spi1_setting_before_sleep(void)
{
		
	//除NSS外，均输出低
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_2);
	SI32_PBCFG_A_disable_spi1_on_crossbar(SI32_PBCFG_0);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_2, PBX_4 | PBX_5 | PBX_6 | PBX_7);
	SI32_PBSTD_A_write_pins_low(SI32_PBSTD_2, PBX_4 | PBX_5 | PBX_6 | PBX_7);
}

void spi0_setting_before_sleep(void)
{
	SI32_PBCFG_A_disable_xbar0_peripherals(SI32_PBCFG_0, SI32_PBCFG_A_XBAR0_SPI0EN);
}

