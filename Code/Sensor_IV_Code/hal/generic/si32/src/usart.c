#include "usart.h"
#include "clock_config.h"

int usart_configuration(USART_InitTypeDef *usart_paras) {
	int ret = 0;
	uint32_t fapb = get_periph_clock();
	
   	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_USART0);
	SI32_PBCFG_A_enable_xbar0_peripherals(SI32_PBCFG_0, SI32_PBCFG_A_XBAR0_USART0EN);
	
	switch (usart_paras->usart_duplex_mode) {
		case usart_full_duplex_mode:
			SI32_USART_B_enter_full_duplex_mode(SI32_USART_0);
			break;
			
		case usart_half_duplex_mode:
			SI32_USART_B_enter_half_duplex_mode(SI32_USART_0);
			break;
	}

	switch (usart_paras->usart_baudrate) {
		case usart_baudrate_1200:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 1200)) - 1);	
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 1200)) - 1);
			break;
			
		case usart_baudrate_2400:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 2400)) - 1);	
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 2400)) - 1);
			break;
			
		case usart_baudrate_4800:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 4800)) - 1);
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 4800)) - 1);	
			break;
			
		case usart_baudrate_9600:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 9600)) - 1);
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 9600)) - 1);				
			break;
			
		case usart_baudrate_14400:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 14400)) - 1);			
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 14400)) - 1);			
			break;
			
		case usart_baudrate_19200:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 19200)) - 1);	
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 19200)) - 1);			
			break;
			
		case usart_baudrate_28800:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 28800)) - 1);			
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 28800)) - 1);			
			break;
			
		case usart_baudrate_38400:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 38400)) - 1);			
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 38400)) - 1);			
			break;
			
		case usart_baudrate_57600:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 57600)) - 1);	
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 57600)) - 1);			
			break;
			
		case usart_baudrate_76800:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 76800)) - 1);		
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 76800)) - 1);			
			break;
		case usart_baudrate_115200:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 115200)) - 1);
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 115200)) - 1);			
			break;
			
		case usart_baudrate_230400:
			SI32_USART_B_set_tx_baudrate(SI32_USART_0, (fapb / (2 * 230400)) - 1);	
			SI32_USART_B_set_rx_baudrate(SI32_USART_0, (fapb / (2 * 230400)) - 1);			
			break;
	}
	
	switch (usart_paras->usart_wordlength) {
		case usart_wordlength_5bit:
			SI32_USART_B_select_tx_data_length(SI32_USART_0, 5);
			SI32_USART_B_select_rx_data_length(SI32_USART_0, 5);
			break;
		case usart_wordlength_6bit:
			SI32_USART_B_select_tx_data_length(SI32_USART_0, 6);
			SI32_USART_B_select_rx_data_length(SI32_USART_0, 6);
			break;
		case usart_wordlength_7bit:
			SI32_USART_B_select_tx_data_length(SI32_USART_0, 7);
			SI32_USART_B_select_rx_data_length(SI32_USART_0, 7);
			break;
		case usart_wordlength_8bit:
			SI32_USART_B_select_tx_data_length(SI32_USART_0, 8);
			SI32_USART_B_select_rx_data_length(SI32_USART_0, 8);
			break;
		case usart_wordlength_9bit_normal:
			SI32_USART_B_select_tx_data_length(SI32_USART_0, 9);
			SI32_USART_B_select_rx_data_length(SI32_USART_0, 9);
			break;
		case usart_wordlength_9bit_fixed:
			SI32_USART_B_select_tx_data_length(SI32_USART_0, 9);
			SI32_USART_B_select_rx_data_length(SI32_USART_0, 9);
			break;
	}

	switch (usart_paras->usart_startbits) {
		case usart_has_startbits:
			SI32_USART_B_enable_tx_start_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_start_bit(SI32_USART_0);
			break;
			
		case usart_none_startbits:
			SI32_USART_B_disable_tx_start_bit(SI32_USART_0);
			SI32_USART_B_disable_rx_start_bit(SI32_USART_0);
			break;
	}

	switch (usart_paras->usart_stopbits) {
		case usart_stopbits_0:
			SI32_USART_B_disable_tx_stop_bit(SI32_USART_0);
			SI32_USART_B_disable_rx_start_bit(SI32_USART_0);
			break;	
			
		case usart_stopbits_0_5:
			SI32_USART_B_enable_tx_stop_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_stop_bit(SI32_USART_0);
			SI32_USART_B_select_tx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_0P5_STOP_VALUE);
			SI32_USART_B_select_rx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_0P5_STOP_VALUE);
			break;
			
		case usart_stopbits_1:
			SI32_USART_B_enable_tx_stop_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_stop_bit(SI32_USART_0);
			SI32_USART_B_select_tx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_1_STOP_VALUE);
			SI32_USART_B_select_rx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_1_STOP_VALUE);
			break;
			
		case usart_stopbits_1_5:
			SI32_USART_B_enable_tx_stop_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_stop_bit(SI32_USART_0);
			SI32_USART_B_select_tx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_1P5_STOP_VALUE);			
			SI32_USART_B_select_rx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_1P5_STOP_VALUE);			
			break;
			
		case usart_stopbits_2:
			SI32_USART_B_enable_tx_stop_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_stop_bit(SI32_USART_0);
			SI32_USART_B_select_tx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_2_STOP_VALUE);			
			SI32_USART_B_select_rx_stop_bits(SI32_USART_0, SI32_USART_B_CONFIG_TSTPMD_2_STOP_VALUE);			
			break;
	}

	switch (usart_paras->usart_parity) {
		case usart_parity_none:
			SI32_USART_B_disable_tx_parity_bit(SI32_USART_0);
			SI32_USART_B_disable_rx_parity_bit(SI32_USART_0);
			break;
			
		case usart_parity_odd:
			SI32_USART_B_enable_tx_parity_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_parity_bit(SI32_USART_0);
			
			SI32_USART_B_select_tx_parity(SI32_USART_0, SI32_USART_B_PARITY_ODD);
			SI32_USART_B_select_rx_parity(SI32_USART_0, SI32_USART_B_PARITY_ODD);
			break;
			
		case usart_parity_even:
			SI32_USART_B_enable_tx_parity_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_parity_bit(SI32_USART_0);
			
			SI32_USART_B_select_tx_parity(SI32_USART_0, SI32_USART_B_PARITY_EVEN);
			SI32_USART_B_select_rx_parity(SI32_USART_0, SI32_USART_B_PARITY_EVEN);		
			break;
			
		case usart_parity_set:
			SI32_USART_B_enable_tx_parity_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_parity_bit(SI32_USART_0);
			
			SI32_USART_B_select_tx_parity(SI32_USART_0, SI32_USART_B_PARITY_SET);
			SI32_USART_B_select_rx_parity(SI32_USART_0, SI32_USART_B_PARITY_SET);	
			break;
			
		case usart_parity_clear:
			SI32_USART_B_enable_tx_parity_bit(SI32_USART_0);
			SI32_USART_B_enable_rx_parity_bit(SI32_USART_0);
			
			SI32_USART_B_select_tx_parity(SI32_USART_0, SI32_USART_B_PARITY_CLEAR);
			SI32_USART_B_select_rx_parity(SI32_USART_0, SI32_USART_B_PARITY_CLEAR);			
			break;
	}

	switch (usart_paras->usart_tx_idlestate) {		
		case usart_tx_idle_high_state:
			SI32_USART_B_disable_tx_signal_inversion(SI32_USART_0);
			break;
			
		case usart_tx_idle_low_state:
			SI32_USART_B_enable_tx_signal_inversion(SI32_USART_0);			
			break;
	}
	
	switch (usart_paras->usart_rx_idlestate) {
		case usart_rx_idle_high_state:
			SI32_USART_B_disable_rx_signal_inversion(SI32_USART_0);
			break;
			
		case usart_rx_idle_low_state:
			SI32_USART_B_enable_rx_signal_inversion(SI32_USART_0);
			break;
	}
	
	switch (usart_paras->usart_rx_fifo_threshold) {
		case usart_rx_fifo_threshold_one_byte:
			SI32_USART_B_select_rx_fifo_threshold_1(SI32_USART_0);
			break;
			
		case usart_rx_fifo_threshold_two_bytes:
			SI32_USART_B_select_rx_fifo_threshold_2(SI32_USART_0);
			break;
			
		case usart_rx_fifo_threshold_four_bytes:
			SI32_USART_B_select_rx_fifo_threshold_4(SI32_USART_0);
			break;
	}
	
	return ret;
}

void usart_interrupt_enable(void) {
	NVIC_ClearPendingIRQ(USART0_IRQn);
	NVIC_EnableIRQ(USART0_IRQn);	
}

void usart_interrupt_disable(void) {
	NVIC_ClearPendingIRQ(USART0_IRQn);
	NVIC_DisableIRQ(USART0_IRQn);	
}

void usart_tx_enable(void) {
	SI32_USART_B_enable_tx_output(SI32_USART_0);
	SI32_USART_B_enable_tx(SI32_USART_0);
	
	SI32_USART_B_disable_tx_data_request_interrupt(SI32_USART_0);	
}

void usart_tx_disable(void) {
	SI32_USART_B_disable_tx_output(SI32_USART_0);
	SI32_USART_B_disable_tx(SI32_USART_0);
	
	SI32_USART_B_disable_tx_data_request_interrupt(SI32_USART_0);
}

void usart_rx_enable(void) {
	SI32_USART_B_enable_rx(SI32_USART_0);
	SI32_USART_B_enable_rx_data_request_interrupt(SI32_USART_0);
	SI32_USART_B_clear_rx_data_request_interrupt(SI32_USART_0);	
	
	usart_interrupt_enable();
}

void usart_rx_disable(void) {
	usart_interrupt_disable();
		
	SI32_USART_B_disable_rx(SI32_USART_0);
	SI32_USART_B_disable_rx_data_request_interrupt(SI32_USART_0);
	SI32_USART_B_clear_rx_data_request_interrupt(SI32_USART_0);	
}

void usart_send_byte(uint8_t data) {			
	while (SI32_USART_B_read_tx_fifo_count(SI32_USART_0) >= 4);
	SI32_USART_B_write_data_u8(SI32_USART_0, data);
}

void usart_send_bytes(uint8_t *data, uint16_t size) {
	uint16_t i;
	
	SI32_USART_B_clear_tx_complete_interrupt(SI32_USART_0);
	SI32_USART_B_select_tx_complete_threshold_no_more_data(SI32_USART_0);
	
	for (i=0; i<size; i++) {
		usart_send_byte(((uint8_t *)data)[i]);	
	}	
	
	while(!SI32_USART_B_is_tx_complete(SI32_USART_0));
	SI32_USART_B_clear_tx_complete_interrupt(SI32_USART_0);
}

void usart_send_string(const char *str) {
	SI32_USART_B_clear_tx_complete_interrupt(SI32_USART_0);
	SI32_USART_B_select_tx_complete_threshold_no_more_data(SI32_USART_0);
	
	while(1) {
		if (*str == '\0')
			break;
		
		usart_send_byte(*str++);	
	}
	
	while(!SI32_USART_B_is_tx_complete(SI32_USART_0));
	SI32_USART_B_clear_tx_complete_interrupt(SI32_USART_0);
}

