#include "uart.h"
#include "clock_config.h"
#include "delay.h"
#include "sensor_parameter.h"
uint8_t sample[]={0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef};//
void uart_port_configuration(void)
{
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, UART0_TX_PIN);
	SI32_PBSTD_A_write_pins_high(SI32_PBSTD_0, UART0_TX_PIN);
	//SI32_PBSTD_A_write_pbskipen(SI32_PBSTD_0, PBX_7 | PBX_8 );	
}
void uart_port_sleep(void)
{
	SI32_PBSTD_A_disable_pullup_resistors(SI32_PBSTD_0);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, PBX_7 | PBX_8);
	SI32_PBSTD_A_write_pins_high(SI32_PBSTD_0, PBX_7 | PBX_8);
	#ifdef uart_485
	RX_H; 
	TX_L;   
	#endif
}

void uart_struct_init(void)
{

		UART_InitTypeDef uart_set;
		
		uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		uart_set.uart_baudrate=uart_baudrate_9600;
		uart_set.uart_duplex_mode=uart_half_duplex_mode;//°ëË«¹¤
		uart_set.uart_wordlength=uart_wordlength_8bit;
		uart_set.uart_startbits=uart_has_startbits;
		uart_set.uart_stopbits=uart_stopbits_1;
		uart_set.uart_parity=uart_parity_none;
		uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&uart_set);
}
int uart_configuration(UART_InitTypeDef *uart_paras) {
	int ret = 0;
	uint32_t fapb = get_periph_clock();	
	#ifdef uart_485
	RX_H; 
	TX_L;   
	#else
		SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, PBX_0 | PBX_1);		
		SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3, PBX_0);
		SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3, PBX_1);
	#endif
	SI32_CLKCTRL_A_enable_apb_to_modules_0(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG0_UART0);	
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG1_MISC0);
	SI32_UART_B_flush_tx_fifo(SI32_UART_0);
	SI32_UART_B_flush_rx_fifo(SI32_UART_0);
	SI32_UART_B_write_clkdiv(SI32_UART_0, 0);
	SI32_UART_B_select_apb_clock_mode(SI32_UART_0);
	switch (uart_paras->uart_duplex_mode) {
		case uart_full_duplex_mode:
			SI32_UART_B_enter_full_duplex_mode(SI32_UART_0);
			break;
			
		case uart_half_duplex_mode:
			SI32_UART_B_enter_half_duplex_mode(SI32_UART_0);
			break;
	}

	
	switch (uart_paras->uart_wordlength) {
		case uart_wordlength_5bit:
			SI32_UART_B_select_tx_data_length(SI32_UART_0, 5);
			SI32_UART_B_select_rx_data_length(SI32_UART_0, 5);
			break;
		case uart_wordlength_6bit:
			SI32_UART_B_select_tx_data_length(SI32_UART_0, 6);
			SI32_UART_B_select_rx_data_length(SI32_UART_0, 6);
			break;
		case uart_wordlength_7bit:
			SI32_UART_B_select_tx_data_length(SI32_UART_0, 7);
			SI32_UART_B_select_rx_data_length(SI32_UART_0, 7);
			break;
		case uart_wordlength_8bit: 
			SI32_UART_B_select_tx_data_length(SI32_UART_0, 8);
			SI32_UART_B_select_rx_data_length(SI32_UART_0, 8);
			break;
		case uart_wordlength_9bit_normal:
			SI32_UART_B_select_tx_data_length(SI32_UART_0, 9);
			SI32_UART_B_select_rx_data_length(SI32_UART_0, 9);
			break;
		case uart_wordlength_9bit_fixed:
			SI32_UART_B_select_tx_data_length(SI32_UART_0, 9);
			SI32_UART_B_select_rx_data_length(SI32_UART_0, 9);
			break;
	}

	switch (uart_paras->uart_startbits) {
		case uart_has_startbits:
			SI32_UART_B_enable_tx_start_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_start_bit(SI32_UART_0);
			break;
			
		case uart_none_startbits:
			SI32_UART_B_disable_tx_start_bit(SI32_UART_0);
			SI32_UART_B_disable_rx_start_bit(SI32_UART_0);
			break;
	}

	switch (uart_paras->uart_stopbits) {
		case uart_stopbits_0:
			SI32_UART_B_disable_tx_stop_bit(SI32_UART_0);
			SI32_UART_B_disable_rx_start_bit(SI32_UART_0);
			break;	
			
		case uart_stopbits_0_5:
			SI32_UART_B_enable_tx_stop_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_stop_bit(SI32_UART_0);
			SI32_UART_B_select_tx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_TSTPMD_0P5_STOP_VALUE);
			SI32_UART_B_select_rx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_RSTPMD_0P5_STOP_VALUE);
			break;
			
		case uart_stopbits_1:
			SI32_UART_B_enable_tx_stop_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_stop_bit(SI32_UART_0);
			SI32_UART_B_select_tx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_TSTPMD_1_STOP_VALUE);
			SI32_UART_B_select_rx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_RSTPMD_1_STOP_VALUE);
			break;
			
		case uart_stopbits_1_5:
			SI32_UART_B_enable_tx_stop_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_stop_bit(SI32_UART_0);
			SI32_UART_B_select_tx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_TSTPMD_1P5_STOP_VALUE);			
			SI32_UART_B_select_rx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_RSTPMD_1P5_STOP_VALUE);			
			break;
			
		case uart_stopbits_2:
			SI32_UART_B_enable_tx_stop_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_stop_bit(SI32_UART_0);
			SI32_UART_B_select_tx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_TSTPMD_2_STOP_VALUE);			
			SI32_UART_B_select_rx_stop_bits(SI32_UART_0, SI32_UART_B_CONFIG_RSTPMD_2_STOP_VALUE);			
			break;
	}

	switch (uart_paras->uart_parity) {
		case uart_parity_none:
			SI32_UART_B_disable_tx_parity_bit(SI32_UART_0);
			SI32_UART_B_disable_rx_parity_bit(SI32_UART_0);
			SI32_UART_B_select_tx_parity(SI32_UART_0,SI32_UART_B_CONFIG_TPARMD_SPACE_VALUE);
			SI32_UART_B_select_rx_parity(SI32_UART_0,SI32_UART_B_CONFIG_RPARMD_SPACE_VALUE);
			break;	
		case uart_parity_odd:
			SI32_UART_B_enable_tx_parity_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_parity_bit(SI32_UART_0);
			SI32_UART_B_select_tx_parity(SI32_UART_0,SI32_UART_B_CONFIG_TPARMD_ODD_VALUE);
			SI32_UART_B_select_rx_parity(SI32_UART_0,SI32_UART_B_CONFIG_RPARMD_ODD_VALUE);
		case uart_parity_even:
			SI32_UART_B_enable_tx_parity_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_parity_bit(SI32_UART_0);
			SI32_UART_B_select_tx_parity(SI32_UART_0,SI32_UART_B_CONFIG_TPARMD_EVEN_VALUE);
			SI32_UART_B_select_rx_parity(SI32_UART_0,SI32_UART_B_CONFIG_RPARMD_EVEN_VALUE);
			break;
		case uart_parity_set:
		case uart_parity_clear:
			SI32_UART_B_enable_tx_parity_bit(SI32_UART_0);
			SI32_UART_B_enable_rx_parity_bit(SI32_UART_0);
			break;
	}

	switch (uart_paras->uart_tx_idlestate) {		
		case uart_tx_idle_high_state:
			SI32_UART_B_disable_tx_signal_inversion(SI32_UART_0);
			break;
			
		case uart_tx_idle_low_state:
			SI32_UART_B_enable_tx_signal_inversion(SI32_UART_0);			
			break;
	}
	
	switch (uart_paras->uart_rx_idlestate) {
		case uart_rx_idle_high_state:
			SI32_UART_B_disable_rx_signal_inversion(SI32_UART_0);
			break;
			
		case uart_rx_idle_low_state:
			SI32_UART_B_enable_rx_signal_inversion(SI32_UART_0);
			break;
	}
	switch (uart_paras->uart_rx_fifo_threshold) {
		case uart_rx_fifo_threshold_one_byte:
			SI32_UART_B_select_rx_fifo_threshold_1(SI32_UART_0);
			break;
			
		case uart_rx_fifo_threshold_two_bytes:
			SI32_UART_B_select_rx_fifo_threshold_2(SI32_UART_0);
			break;
			
		case uart_rx_fifo_threshold_four_bytes:
			SI32_UART_B_select_rx_fifo_threshold_4(SI32_UART_0);
			break;
	}
	switch (uart_paras->uart_baudrate) {
		case uart_baudrate_1200:
			switch(uart_paras->uart_source_clock)
			{
				case uart_source_clock_select_apb:						
					SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 1200)) - 1);
					SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 1200)) - 1);
					SI32_UART_B_select_apb_clock_mode(SI32_UART_0);
					break;
				case uart_source_clock_select_rtc:
					 
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 0);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 0);
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					break;
				default:
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 0);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 0);
					 break;
			}			
			break;
		case uart_baudrate_2400:
			switch(uart_paras->uart_source_clock)
			{
				case uart_source_clock_select_apb:
					SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
					SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 2400)) - 1);
					SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 2400)) - 1);
					break;
				case uart_source_clock_select_rtc:
					 
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 1);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 1);
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					break;
				default:
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 1);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 1);
					 break;
			}				
			break;
			
		case uart_baudrate_4800:
			switch(uart_paras->uart_source_clock)
			{
				case uart_source_clock_select_apb:
					SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
					SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 4800)) - 1);
					SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 4800)) - 1);
					break;
				case uart_source_clock_select_rtc:
					 
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 2);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 2);
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					break;
				default:
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 2);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 2);
					 break;					 
			}				
			break;
			
		case uart_baudrate_9600:
			switch(uart_paras->uart_source_clock)
			{
				case uart_source_clock_select_apb:
					SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
					SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 9600)) - 1);
					SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 9600)) - 1);
					break;
				case uart_source_clock_select_rtc:
					 
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 3);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 3);
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					break;
				default:
					 SI32_UART_B_select_rtc_clock_mode(SI32_UART_0);
					 SI32_UART_B_set_tx_baudrate(SI32_UART_0, 3);
					 SI32_UART_B_set_rx_baudrate(SI32_UART_0, 3);
					 break;
			}				
			break;
		case uart_baudrate_14400:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * (14400 + uart_paras->uart_baudrate_offset))) - 1);			
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 14400 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_19200:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 19200 + uart_paras->uart_baudrate_offset)) - 1);	
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 19200 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_28800:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 28800 + uart_paras->uart_baudrate_offset)) - 1);			
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 28800 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_38400:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 38400 + uart_paras->uart_baudrate_offset)) - 1);			
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 38400 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_57600:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 57600 + uart_paras->uart_baudrate_offset)) - 1);	
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 57600 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_76800:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 76800 + uart_paras->uart_baudrate_offset)) - 1);		
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 76800 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_115200:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 115200 + uart_paras->uart_baudrate_offset)) - 1);
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 115200 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_230400:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 230400 + uart_paras->uart_baudrate_offset)) - 1);	
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 230400 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
		case uart_baudrate_250000:
			SI32_UART_B_select_apb_clock_mode(SI32_UART_0);		
			SI32_UART_B_set_tx_baudrate(SI32_UART_0, (fapb/ (2 * 250000 + uart_paras->uart_baudrate_offset)) - 1);
			SI32_UART_B_set_rx_baudrate(SI32_UART_0, (fapb/ (2 * 250000 + uart_paras->uart_baudrate_offset)) - 1);			
			break;
	}
	uart_tx_disable();
	uart_rx_disable();
	if(node_parameter.SETP==S_5TM_TYPE)
	{	
		SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, UART0_RX_PIN);
		SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, UART0_TX_PIN);
	}
	
	//uart_send_bytes(sample,sizeof(sample));
	return ret;
}

void uart_interrupt_enable(void) {
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);	
}

void uart_interrupt_disable(void) {
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_DisableIRQ(UART0_IRQn);	
}

void uart_tx_enable(void) {
	_SI32_UART_B_enable_tx_output(SI32_UART_0);
	_SI32_UART_B_enable_tx(SI32_UART_0);
	#ifdef uart_485 
	RX_H;
	TX_H;  
	#endif
	SI32_UART_B_disable_tx_data_request_interrupt(SI32_UART_0);	
}

void uart_tx_disable(void) {
	SI32_UART_B_disable_tx_output(SI32_UART_0);
	SI32_UART_B_disable_tx(SI32_UART_0);
	#ifdef uart_485 
	TX_L;  
	#endif
	SI32_UART_B_disable_tx_data_request_interrupt(SI32_UART_0);
}

void uart_rx_enable(void) {
	#ifdef uart_485
	RX_L;  
	TX_L;   
	#endif
	SI32_UART_B_enable_rx(SI32_UART_0);
	SI32_UART_B_enable_rx_data_request_interrupt(SI32_UART_0);
	SI32_UART_B_clear_rx_data_request_interrupt(SI32_UART_0);	
	SI32_UART_B_clear_tx_fifo_error_interrupt(SI32_UART_0);	
	SI32_UART_B_clear_rx_fifo_error_interrupt(SI32_UART_0);
	uart_interrupt_enable();
}

void uart_rx_disable(void) {
	uart_interrupt_disable();
	#ifdef uart_485 
	RX_H;  
	#endif
	SI32_UART_B_disable_rx(SI32_UART_0);
	SI32_UART_B_disable_rx_data_request_interrupt(SI32_UART_0);
	SI32_UART_B_clear_rx_data_request_interrupt(SI32_UART_0);	
}

void uart_send_byte(uint8_t data) {			
	while (SI32_UART_B_read_tx_fifo_count(SI32_UART_0) >= 4);
	SI32_UART_B_write_data_u8(SI32_UART_0, data);
}

void uart_send_bytes(uint8_t *data, uint16_t size) {
	uint16_t i;
	if(size==0)
	{
		return;
	}
	uart_tx_enable();
	_SI32_UART_B_flush_tx_fifo(SI32_UART_0);
	
	SI32_UART_B_clear_tx_complete_interrupt(SI32_UART_0);
	SI32_UART_B_select_tx_complete_threshold_no_more_data(SI32_UART_0);
	//SI32_UART_B_select_tx_complete_threshold_end_of_transmission(SI32_UART_0);
	SI32_UART_B_clear_tx_fifo_error_interrupt(SI32_UART_0);
	for (i=0; i<size; i++) {
		uart_send_byte(((uint8_t *)data)[i]);	
		delay_Xus(100);
	}	
	while(!(SI32_UART_0->CONTROL.U32&0x80000));
	//while(!_SI32_UART_B_is_tx_complete(SI32_UART_0));
	SI32_UART_B_clear_tx_complete_interrupt(SI32_UART_0);
	uart_tx_disable();
}

void uart_send_string(const char *str) {
	SI32_UART_B_clear_tx_complete_interrupt(SI32_UART_0);
	SI32_UART_B_select_tx_complete_threshold_no_more_data(SI32_UART_0);
	
	while(1) {
		if (*str == '\0')
			break;
		
		uart_send_byte(*str++);	
	}	
	
	while(!SI32_UART_B_is_tx_complete(SI32_UART_0));
	SI32_UART_B_clear_tx_complete_interrupt(SI32_UART_0);
}
