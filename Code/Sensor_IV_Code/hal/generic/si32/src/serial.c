#include "serial.h"

int serial_configuration(enum_serial_port serial_port, serial_paras_t *serial_paras) {
	int ret = 0;

	switch (serial_port) {
		case SERIAL_PORT_UART0:
			if (uart_configuration((UART_InitTypeDef *)(serial_paras)))
				ret = -1;
			else {
				uart_tx_enable();
				uart_rx_enable();
			}
			break;
		
		case SERIAL_PORT_USART0:
			if (usart_configuration((USART_InitTypeDef *)(serial_paras)))
				ret = -1;
			else {
				usart_tx_enable();
				usart_rx_enable();
			}
			break;
		
		default:
			ret = -1;
			break;
	}
	
	return ret;
}

void serial_tramsmit_byte(enum_serial_port serial_port, uint8_t data) {	
	switch (serial_port) {
		case SERIAL_PORT_UART0:
			uart_send_byte(data);
			break;
		
		case SERIAL_PORT_USART0:
			usart_send_byte(data);
			break;
		
		default:
			break;
	}		
}

void serial_tramsmit_bytes(enum_serial_port serial_port, uint8_t *data, uint16_t size) {	
	switch (serial_port) {
		case SERIAL_PORT_UART0:
			uart_send_bytes(data, size);
			break;
		
		case SERIAL_PORT_USART0:
			usart_send_bytes(data, size);
			break;
		
		default:
			break;
	}	
}

void serial_tramsmit_string(enum_serial_port serial_port, char *string) {		
	switch (serial_port) {
		case SERIAL_PORT_UART0:
			uart_send_string(string);
			break;
		
		case SERIAL_PORT_USART0:
			usart_send_string(string);
			break;
		
		default:
			break;
	}	
}
