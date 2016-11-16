#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif
//
#include "cpu_arch.h"
#if ACA826T_OPERATE+NHFS15_OPERATE+NHZF42_OPERATE+NHZD10_OPERATE+SCA126T_OPERATE+SOIL_TEMP_HUMIDITY_TRANSMIT_OPERATE+modbus_mode+NHUV11_OPERATE+SKD_100D_OPERATE+LVDT_OPERATE
	 #define uart_485
#endif
#ifdef uart_485
	#define RX_L SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, PBX_1); \
							 SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3,PBX_1)
	#define RX_H SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, PBX_1); \
							 SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3,PBX_1)
	 
	#define TX_L SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, PBX_0); \
							 SI32_PBSTD_A_write_pins_low(SI32_PBSTD_3,PBX_0)
	#define TX_H SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_3, PBX_0); \
							 SI32_PBSTD_A_write_pins_high(SI32_PBSTD_3,PBX_0)  
#endif
typedef enum {
	uart_full_duplex_mode = 1,
	uart_half_duplex_mode,
} enum_uart_duplex_mode;

typedef enum {
	uart_baudrate_1200 = 1,
	uart_baudrate_2400,
	uart_baudrate_4800,
	uart_baudrate_9600,
	uart_baudrate_14400,
	uart_baudrate_19200,
	uart_baudrate_28800,
	uart_baudrate_38400,
	uart_baudrate_57600,
	uart_baudrate_76800,
	uart_baudrate_115200,
	uart_baudrate_230400,
	uart_baudrate_250000
} enum_uart_baudrate;

typedef enum {
	uart_wordlength_5bit = 1,
	uart_wordlength_6bit,
	uart_wordlength_7bit,
	uart_wordlength_8bit,
	uart_wordlength_9bit_normal,
	uart_wordlength_9bit_fixed,
} enum_uart_wordlength;

typedef enum {
	uart_has_startbits = 1,
	uart_none_startbits,
} enum_uart_startbits;

typedef enum {
	uart_stopbits_0 = 1,
	uart_stopbits_0_5,
	uart_stopbits_1,
	uart_stopbits_1_5,
	uart_stopbits_2,
} enum_uart_stopbits;

typedef enum {	
	uart_parity_none = 1,
	uart_parity_odd,
	uart_parity_even,
	uart_parity_set,
	uart_parity_clear,
} enum_uart_parity;

typedef enum {
	uart_tx_idle_high_state = 1,
	uart_tx_idle_low_state,
} enum_uart_tx_idle_status;

typedef enum {
	uart_rx_idle_high_state = 1,
	uart_rx_idle_low_state,
} enum_uart_rx_idle_status;

typedef enum {
	uart_rx_fifo_threshold_one_byte = 1,
	uart_rx_fifo_threshold_two_bytes,
	uart_rx_fifo_threshold_four_bytes,
} enum_uart_rx_fifo_threshold;

typedef enum {
	uart_clkdiv_one = 1,
	uart_clkdiv_half,
	uart_clkdiv_quarter,
} enum_uart_clkdiv;
typedef enum{
	uart_source_clock_select_rtc = 1,
	uart_source_clock_select_apb,	
}enum_uart_source_clock;
typedef struct {
	enum_uart_source_clock  			uart_source_clock;
	int 													uart_baudrate_offset;
	enum_uart_duplex_mode 				uart_duplex_mode;  
	enum_uart_baudrate 						uart_baudrate;          
	enum_uart_wordlength 					uart_wordlength; 
	enum_uart_startbits 					uart_startbits;
	enum_uart_stopbits 						uart_stopbits;  
	enum_uart_parity 							uart_parity;                
	enum_uart_tx_idle_status 			uart_tx_idlestate;
	enum_uart_rx_idle_status	 		uart_rx_idlestate;
	enum_uart_rx_fifo_threshold 	uart_rx_fifo_threshold;
} UART_InitTypeDef;
void uart_port_configuration(void);
void uart_port_sleep(void);

int uart_configuration(UART_InitTypeDef *uart_paras);
void uart_struct_init(void);
void uart_interrupt_enable(void);
void uart_interrupt_disable(void);
void uart_tx_enable(void);
void uart_tx_disable(void);
void uart_rx_enable(void);
void uart_rx_disable(void);

void uart_send_byte(uint8_t data);
void uart_send_bytes(uint8_t *data, uint16_t size);
void uart_send_string(const char *str);

#ifdef __cplusplus
}
#endif

#endif // __UART_H__
