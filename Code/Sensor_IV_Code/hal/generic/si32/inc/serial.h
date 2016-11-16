#ifndef __SERIAL_H__
#define __SERIAL_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "uart.h"
#include "usart.h"

typedef enum {
	serial_full_duplex_mode = 1,
	serial_half_duplex_mode,
} enum_serial_duplex_mode;

typedef enum {
	serial_baudrate_1200 = 1,
	serial_baudrate_2400,
	serial_baudrate_4800,
	serial_baudrate_9600,
	serial_baudrate_14400,
	serial_baudrate_19200,
	serial_baudrate_28800,
	serial_baudrate_38400,
	serial_baudrate_57600,
	serial_baudrate_76800,
	serial_baudrate_115200,
	serial_baudrate_230400,
} enum_serial_baudrate;
	
typedef enum {
	serial_wordlength_5bit = 1,
	serial_wordlength_6bit,
	serial_wordlength_7bit,
	serial_wordlength_8bit,
	serial_wordlength_9bit_normal,
	serial_wordlength_9bit_fixed,
} enum_serial_wordlength;

typedef enum {
	serial_has_startbits = 1,
	serial_none_startbits,
} enum_serial_startbits;

typedef enum {
	serial_stopbits_0 = 1,
	serial_stopbits_0_5,
	serial_stopbits_1,
	serial_stopbits_1_5,
	serial_stopbits_2,
} enum_serial_stopbits;

typedef enum {
	serial_parity_none = 1,
	serial_parity_odd,
	serial_parity_even,
	serial_parity_set,
	serial_parity_clear,
} enum_serial_parity;

typedef enum {
	serial_tx_idle_high_state = 1,
	serial_tx_idle_low_state,
} enum_serial_tx_idle_status;

typedef enum {
	serial_rx_idle_high_state = 1,
	serial_rx_idle_low_state,
} enum_serial_rx_idle_status;

typedef enum {
	serial_rx_fifo_threshold_one_byte = 1,
	serial_rx_fifo_threshold_two_bytes,
	serial_rx_fifo_threshold_four_bytes,
} enum_serial_rx_fifo_threshold;

typedef enum {
	SERIAL_PORT_USART0	= 1,
	SERIAL_PORT_UART0 	= 2,
} enum_serial_port;

typedef struct {
	enum_serial_duplex_mode 		duplex_mode;  
	enum_serial_baudrate 			baudrate;          
	enum_serial_wordlength 			wordlength; 
	enum_serial_startbits 			startbits;
	enum_serial_stopbits 			stopbits;  
	enum_serial_parity 				parity;                
	enum_serial_tx_idle_status 		tx_idlestate;
	enum_serial_rx_idle_status	 	rx_idlestate;
	enum_serial_rx_fifo_threshold 	rx_fifo_threshold;
} serial_paras_t;

int serial_configuration(enum_serial_port serial_port, serial_paras_t *serial_paras);
void serial_tramsmit_byte(enum_serial_port serial_port, uint8_t data);
void serial_tramsmit_bytes(enum_serial_port serial_port, uint8_t *data, uint16_t size);
void serial_tramsmit_string(enum_serial_port serial_port, char *string);

#ifdef __cplusplus
}
#endif

#endif // __SERIAL_H__
