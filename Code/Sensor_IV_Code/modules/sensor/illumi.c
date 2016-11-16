#include "illumi.h"
#if ILLUMI_OPERATE
uint32_t uart_rx_cnt = 0;
uint8_t uart_test_buff[UART_BUFFER_LEN];
uint8_t ilumi_battery;
uint8_t timeout_cnt;

UART_InitTypeDef illumi_uart_set;

//ILLUMI串口设置

#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
#define ILLUMI_SERIAL_PORT 	SERIAL_PORT_UART0
#define ILLUMI_SERIAL_BAUD 	serial_baudrate_9600
/*
void illumi_param_init(void)
{
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, UART0_TX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_EN_PORT, SENSOR_POWER_EN_PIN);
	
	illumi_uart_param.duplex_mode		= serial_full_duplex_mode;
	illumi_uart_param.startbits			= serial_has_startbits;
	illumi_uart_param.tx_idlestate		= serial_tx_idle_high_state;
	illumi_uart_param.rx_idlestate		= serial_rx_idle_high_state;
	illumi_uart_param.rx_fifo_threshold	= serial_rx_fifo_threshold_one_byte;
	illumi_uart_param.baudrate 			= ILLUMI_SERIAL_BAUD;
	illumi_uart_param.wordlength 		= serial_wordlength_8bit;
	illumi_uart_param.parity 			= serial_parity_none;
	illumi_uart_param.stopbits 			= serial_stopbits_1;
	
	serial_configuration(ILLUMI_SERIAL_PORT, &illumi_uart_param);
	uart_rx_disable();
	uart_tx_disable();
}*/

void illumi_port_init(void)
{	
		uart_port_configuration();
}
void illumi_port_sleep(void)
{
		uart_port_sleep();
}
void open_illumi_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void close_illumi_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
//uart_baudrate_9600  
void illumi_uart_init(enum_uart_baudrate new_baudrate)
{
		illumi_uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		illumi_uart_set.uart_baudrate=new_baudrate;
		illumi_uart_set.uart_duplex_mode=uart_half_duplex_mode;
		illumi_uart_set.uart_wordlength=uart_wordlength_8bit;
		illumi_uart_set.uart_startbits=uart_has_startbits;
		illumi_uart_set.uart_stopbits=uart_stopbits_1;
		illumi_uart_set.uart_parity=uart_parity_none;
		illumi_uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		illumi_uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		illumi_uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&illumi_uart_set);
}
void illumi_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void illumi_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}

uint8_t illumi_analyster(uint8_t data)
{
	
		uart_test_buff[uart_rx_cnt] = data;
		
		uart_rx_cnt++;
		if(uart_rx_cnt == UART_BUFFER_LEN)
		{
			uart_rx_cnt = 0;
		}
		if(uart_rx_cnt==1)
		{
				if(uart_test_buff[0] != 0x55)
					uart_rx_cnt=0;
		}
		if(uart_rx_cnt==3)
		{
			if(uart_test_buff[2] == 0x1E)
			{
				if((uart_test_buff[0] != 0x55) || 
				(uart_test_buff[1] != 0x53))
				{
						uart_rx_cnt=0;
				}
			}
			else
			{
				uart_rx_cnt=0;
			}
		}
//		if(uart_rx_cnt == 3)
//		{
//			//接收到3个，判断前3个字符
//			if((uart_test_buff[0] != 0x55) || 
//			  (uart_test_buff[1] != 0x53) || 
//			  (uart_test_buff[2] != 0x1E))
//			{
//				uart_rx_cnt = 2;
//				uart_test_buff[0] = uart_test_buff[1];
//				uart_test_buff[1] = uart_test_buff[2];
//			}
//		}
		if(uart_rx_cnt == 8)
		{
			//接收到8个，计算校验和
			uint8_t check,i;
			uart_rx_cnt = 0;
			for(i=0;i<7;i++)
			{
				check += uart_test_buff[i];
			}
			if(check == uart_test_buff[7])
			{
				//校验和相等
				printf("check sum corret \n");
				uart_rx_disable();
				return 1;
			//	
			
			}
			else
			{
				return 0;
			}
			
		}
		return 0;

}
#endif




