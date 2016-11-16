#include "skd_100d.h"
#if SKD_100D_OPERATE

#define UART_RECV_BUFF_LEN 6//接收包长度
#define SKD_100D_ADDRESS_LOCATION 5//更改数据位位置
#define SKD_100D_DATA_LEN 8//数据长度
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
//波特率选项
#define SKD_100D_SERIAL_PORT 	SERIAL_PORT_UART0
#define SKD_100D_SERIAL_BAUD 	serial_baudrate_9600

uint8_t read_or_write_skd_100d_data;
UART_InitTypeDef skd_100d_uart_set;
uint8_t skd_100d_address=0x29;
uint8_t default_smple_cmd[1] 	= {0x4f};

uint8_t skd_100d_recv_buff[10];
uint8_t skd_100d_recv_cnt = 0;

void skd_100d_port_init(void)
{	
		uart_port_configuration();
		clear_skd_100d_recv_buff();
}
void skd_100d_port_sleep(void)
{
		uart_port_sleep();
}
void open_skd_100d_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void close_skd_100d_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void skd_100d_uart_init(enum_uart_baudrate new_baudrate)
{
		skd_100d_uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		skd_100d_uart_set.uart_baudrate=new_baudrate;
		skd_100d_uart_set.uart_duplex_mode=uart_half_duplex_mode;//全双工
		skd_100d_uart_set.uart_wordlength=uart_wordlength_8bit;
		skd_100d_uart_set.uart_startbits=uart_has_startbits;
		skd_100d_uart_set.uart_stopbits=uart_stopbits_1;
		skd_100d_uart_set.uart_parity=uart_parity_none;
		skd_100d_uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		skd_100d_uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		skd_100d_uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&skd_100d_uart_set);
}

int skd_100d_sample_data(void)
{
	
	uart_rx_disable();	
	serial_tramsmit_bytes(SERIAL_PORT_UART0, default_smple_cmd, 1);	
	uart_rx_enable();	
  return 0;
}
uint8_t skd_100d_analyster(uint8_t data)
{
	skd_100d_recv_buff[skd_100d_recv_cnt] = data;
	if(skd_100d_recv_cnt==0)
	{
			if(skd_100d_recv_buff[0]==0xff)
				skd_100d_recv_cnt++;
			else
				return 0;
	}
	else if(skd_100d_recv_cnt==7)
	{
			if(skd_100d_recv_buff[7]==0xee)
			{
				skd_100d_recv_cnt++;
			}
			else
			{
				clear_skd_100d_recv_buff();
				return 0;
			}
			
	}
	else
	{
			skd_100d_recv_cnt++;
	}
	if(skd_100d_recv_cnt >= SKD_100D_DATA_LEN)
	{
		
		skd_100d_recv_cnt = 0;
		return 1;
	}
	return 2;
}
uint8_t skd_100d_data_out(uint32_t *data)
{
	uint8_t i;
	*data=0;
	for(i=1;i<(SKD_100D_DATA_LEN-1);i++)
	{
		if(skd_100d_recv_buff[i]>0x09)
		{
			goto data_out_error;
		}
		*data*=10;
		*data+=skd_100d_recv_buff[i];
	}
	if(*data == 0)
	{
		goto data_out_error;
	}
	return 1;
	data_out_error:
	return 0;
}
void skd_100d_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void skd_100d_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void clear_skd_100d_recv_buff(void)
{
	skd_100d_recv_cnt = 0;
	memset(skd_100d_recv_buff, 0x00, sizeof(skd_100d_recv_buff));
}

#endif
