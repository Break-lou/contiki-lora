#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "cpu_arch.h"

typedef enum {
	usart_full_duplex_mode = 1,
	usart_half_duplex_mode,
} enum_usart_duplex_mode;

typedef enum {
	usart_baudrate_1200 = 1,
	usart_baudrate_2400,
	usart_baudrate_4800,
	usart_baudrate_9600,
	usart_baudrate_14400,
	usart_baudrate_19200,
	usart_baudrate_28800,
	usart_baudrate_38400,
	usart_baudrate_57600,
	usart_baudrate_76800,
	usart_baudrate_115200,
	usart_baudrate_230400,
} enum_usart_baudrate;

typedef enum {
	usart_wordlength_5bit = 1,
	usart_wordlength_6bit,
	usart_wordlength_7bit,
	usart_wordlength_8bit,
	usart_wordlength_9bit_normal,
	usart_wordlength_9bit_fixed,
} enum_usart_wordlength;

typedef enum {
	usart_has_startbits = 1,
	usart_none_startbits,
} enum_usart_startbits;

typedef enum {
	usart_stopbits_0 = 1,
	usart_stopbits_0_5,
	usart_stopbits_1,
	usart_stopbits_1_5,
	usart_stopbits_2,
} enum_usart_stopbits;

typedef enum {
	usart_parity_none = 1,
	usart_parity_odd,
	usart_parity_even,
	usart_parity_set,
	usart_parity_clear,
} enum_usart_parity;

typedef enum {
	usart_tx_idle_high_state = 1,
	usart_tx_idle_low_state,
} enum_usart_tx_idle_status;

typedef enum {
	usart_rx_idle_high_state = 1,
	usart_rx_idle_low_state,
} enum_usart_rx_idle_status;

typedef enum {
	usart_rx_fifo_threshold_one_byte = 1,
	usart_rx_fifo_threshold_two_bytes,
	usart_rx_fifo_threshold_four_bytes,
} enum_usart_rx_fifo_threshold;

typedef struct {
	enum_usart_duplex_mode 			usart_duplex_mode;  
	enum_usart_baudrate 			usart_baudrate;          
	enum_usart_wordlength 			usart_wordlength; 
	enum_usart_startbits 			usart_startbits;
	enum_usart_stopbits 			usart_stopbits;  
	enum_usart_parity 				usart_parity;                
	enum_usart_tx_idle_status 		usart_tx_idlestate;
	enum_usart_rx_idle_status	 	usart_rx_idlestate;
	enum_usart_rx_fifo_threshold 	usart_rx_fifo_threshold;
} USART_InitTypeDef;

int usart_configuration(USART_InitTypeDef *usart_paras);

void usart_interrupt_enable(void);
void usart_interrupt_disable(void);
void usart_tx_enable(void);
void usart_tx_disable(void);
void usart_rx_enable(void);
void usart_rx_disable(void);

void usart_send_byte(uint8_t data);
void usart_send_bytes(uint8_t *data, uint16_t size);
void usart_send_string(const char *str);

#ifdef __cplusplus
}
#endif

#endif // __USART_H__
