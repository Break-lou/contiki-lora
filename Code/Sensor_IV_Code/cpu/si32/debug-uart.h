#ifndef __DEBUG_UART_H__1V2039076V__
#define __DEBUG_UART_H__1V2039076V__



void dbg_setup_uart(void);

void dbg_set_input_handler(void (*handler)(const char *inp, unsigned int len));

unsigned int dbg_send_bytes(const unsigned char *seq, unsigned int len);


void dbg_putchar(const char ch);

void dbg_blocking_putchar(const char ch);

void dbg_drain(void);

#endif /* __DEBUG_UART_H__1V2039076V__ */
