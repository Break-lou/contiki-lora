#include "lvdt.h"
#include "contiki.h"
#include "sensor_lvdt_process.h"
#include "sys_event.h"
#include "power_manager.h"
#include "port_config.h"

#if LVDT_OPERATE
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08

#define LVDT_RECV_BUFF_LEN			20
#define	LVDT_READ_DISTANCE_CMD_LEN	8
uint8_t lvdt_recv_buff[LVDT_RECV_BUFF_LEN];
uint8_t lvdt_read_distance_cmd[LVDT_READ_DISTANCE_CMD_LEN] = {0X01,0X04,0x00,0x04,0x00,0x02,0X30,0X0A};
void lvdt_port_init(void)
{	
		uart_port_configuration();
}
void lvdt_port_sleep(void)
{
		uart_port_sleep();
}
void open_lvdt_power()
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void lvdt_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void lvdt_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void close_lvdt_power()
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void CloseRs485()
{
		  pb_setting_before_sleep_end_485();
	    uart_rx_disable();	
		  uart_tx_disable();			
			pb_setting_before_sleep_end_uart_or_usart();//p0:7,8
}
UART_InitTypeDef lvdt_uart_set;
void lvdt_uart_init(enum_uart_baudrate new_baudrate)
{
		lvdt_uart_set.uart_source_clock = uart_source_clock_select_rtc;
	
		lvdt_uart_set.uart_baudrate=new_baudrate;
		lvdt_uart_set.uart_duplex_mode=uart_half_duplex_mode;//???
		lvdt_uart_set.uart_wordlength=uart_wordlength_8bit;
		lvdt_uart_set.uart_startbits=uart_has_startbits;
		lvdt_uart_set.uart_stopbits=uart_stopbits_1;
		lvdt_uart_set.uart_parity=uart_parity_none;
		lvdt_uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		lvdt_uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		lvdt_uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&lvdt_uart_set);
}
uint8_t lvdt_recv_cnt = 0;

void lvdt_read_distance_value(uint8_t addr)
{
	memset(lvdt_recv_buff, 0, sizeof(lvdt_recv_buff));
	lvdt_recv_cnt=0;
	uart_rx_disable();
	uart_send_bytes(lvdt_read_distance_cmd,LVDT_READ_DISTANCE_CMD_LEN);
  uart_rx_enable();	
}

void lvdt_analyster(uint8_t data)
{	
	if(lvdt_recv_cnt == 0 && data !=1 ) 
	{
		memset(lvdt_recv_buff, 0, sizeof(lvdt_recv_buff));
		lvdt_recv_cnt = 0;
		return;
	}
	if(lvdt_recv_cnt == 1 && data !=4 )
	{
		memset(lvdt_recv_buff, 0, sizeof(lvdt_recv_buff));
		lvdt_recv_cnt = 0;
		return;
	}	
	lvdt_recv_buff [lvdt_recv_cnt] = data;
	lvdt_recv_cnt++;
	if(lvdt_recv_cnt > 8)
	{
		uint16_t crc=crc16_ibm_generate(lvdt_recv_buff,7,0XFFFF,crc_rtu_default);
		uint16_t crc_data=(lvdt_recv_buff[7]<<8)+lvdt_recv_buff[8];
		if(crc_data == crc)
		{
			uart_rx_disable();
			SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
			SI32_UART_B_flush_rx_fifo(SI32_UART_0);
			process_post(&sensor_lvdt_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
		}
	}
}


//void lvdt_set_crc(uint8_t *addr, uint8_t positon)
//{
//	uint16_t crc;
//	crc = lvdt_calc_crc16(addr, positon);

//	addr[positon] = (uint8_t)(crc >> 8);
//	addr[positon+1] = (uint8_t)crc;
//}
//void operate_LVDT()
//{
//		OPERATE_SENSOR_POWER;
//		OPERATE_485;
//		OPERATE_UART_OR_USART;	
//}
void disoperate_LVDT()
{
	DIS_OPERATE_SENSOR_POWER;
	DIS_OPERATE_485;
	DIS_OPERATE_UART_OR_USART;
}
#endif
