#include "nhzd10.h"
#if NHZD10_OPERATE
#define NHZD10_MODE_CMD_LEN 8//发送包长度
#define UART_RECV_BUFF_LEN 20//接收包长度
#define NHZD10_ADDRESS_LOCATION 5//更改数据位位置
#define NHZD10_DATA_LEN 6//数据长度
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
//波特率选项
#define NHZD10_SERIAL_PORT 	SERIAL_PORT_UART0
#define NHZD10_SERIAL_BAUD 	serial_baudrate_9600


uint8_t read_or_write_nhzd10_data;
UART_InitTypeDef nhzd10_uart_set;
uint8_t nhzd10_address=0x0A;
uint8_t default_nhzd10_smple_cmd[NHZD10_MODE_CMD_LEN] 	= {0x0A,0x04,0x00,0x00,0x00,0x02};
//uint8_t default_smple_half_cmd[NHZD10_MODE_CMD_LEN] = {0x0F,0x04,0x00,0x01,0x00,0x01};
uint8_t set_nhzd10_address_cmd[NHZD10_MODE_CMD_LEN] 		= {0x00,0x06,0x00,0x42,0x00,0x00};
uint8_t set_nhzd10_baudrate_cmd[NHZD10_MODE_CMD_LEN]	  = {0x00,0x06,0x00,0x40,0x00,0x00};

uint8_t nhzd10_recv_buff[9];
uint8_t nhzd10_recv_cnt = 0;

void nhzd10_port_init(void)
{	
		uart_port_configuration();
}
void nhzd10_port_sleep(void)
{
		uart_port_sleep();
}
void open_nhzd10_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void close_nhzd10_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void nhzd10_uart_init(enum_uart_baudrate new_baudrate)
{
		nhzd10_uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		nhzd10_uart_set.uart_baudrate=new_baudrate;
		nhzd10_uart_set.uart_duplex_mode=uart_half_duplex_mode;//全双工
		nhzd10_uart_set.uart_wordlength=uart_wordlength_8bit;
		nhzd10_uart_set.uart_startbits=uart_has_startbits;
		nhzd10_uart_set.uart_stopbits=uart_stopbits_1;
		nhzd10_uart_set.uart_parity=uart_parity_none;
		nhzd10_uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		nhzd10_uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		nhzd10_uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&nhzd10_uart_set);
}
uint8_t set_nhzd10_address(uint8_t new_address)
{
	uint16_t crc;
	nhzd10_address=new_address;
	set_nhzd10_address_cmd[NHZD10_ADDRESS_LOCATION]=new_address;
	crc=crc16_ibm_generate(set_nhzd10_address_cmd,NHZD10_DATA_LEN,0XFFFF,crc_rtu_default);
	
	set_nhzd10_address_cmd[6]=crc/256;
	set_nhzd10_address_cmd[7]=crc%256;
	read_or_write_nhzd10_data=0;	
	serial_tramsmit_bytes(NHZD10_SERIAL_PORT, set_nhzd10_address_cmd, NHZD10_MODE_CMD_LEN);
	
	default_nhzd10_smple_cmd[0]=nhzd10_address;

	//default_smple_half_cmd[0]=nhzd10_address;

	
	return 1;
}
uint8_t set_nhzd10_baudrate(enum_uart_baudrate new_baudrate)
{
	uint16_t crc;
	switch(new_baudrate)
	{
		case uart_baudrate_1200:
		case uart_baudrate_2400:
		case uart_baudrate_4800:
		case uart_baudrate_9600:
		case uart_baudrate_19200:
		case uart_baudrate_38400:
		case uart_baudrate_57600:
		case uart_baudrate_115200:
	//	set_nhzd10_baudrate_cmd[0]=nhzd10_address;
		set_nhzd10_baudrate_cmd[NHZD10_ADDRESS_LOCATION]=new_baudrate-1;
		crc=crc16_ibm_generate(set_nhzd10_baudrate_cmd,NHZD10_DATA_LEN,0XFFFF,crc_rtu_default);//crc校验产生
		set_nhzd10_baudrate_cmd[6]=crc/256;
		set_nhzd10_baudrate_cmd[7]=crc%256;
		read_or_write_nhzd10_data=0;
		serial_tramsmit_bytes(NHZD10_SERIAL_PORT, set_nhzd10_baudrate_cmd, NHZD10_MODE_CMD_LEN);
			break;	
		case uart_baudrate_14400:
		case uart_baudrate_28800:
		case uart_baudrate_76800:
		case uart_baudrate_230400:
		case uart_baudrate_250000:
			return 0;
		//	break;
	}
	uart_tx_disable();
	uart_rx_disable();
	nhzd10_uart_init(new_baudrate);
	return 1;
}
int nhzd10_sample_data(void)
{
	uint16_t crc;	
	
	crc=crc16_ibm_generate(default_nhzd10_smple_cmd,NHZD10_DATA_LEN,0XFFFF,crc_rtu_default);//crc校验产生
	default_nhzd10_smple_cmd[6]=crc/256;
	default_nhzd10_smple_cmd[7]=crc%256;
	read_or_write_nhzd10_data=1;	
	uart_rx_disable();	
	serial_tramsmit_bytes(NHZD10_SERIAL_PORT, default_nhzd10_smple_cmd, NHZD10_MODE_CMD_LEN);	
	uart_rx_enable();	
  return 0;
}
uint8_t nhzd10_analyster(uint8_t data)
{
	nhzd10_recv_buff[nhzd10_recv_cnt] = data;
	if(nhzd10_recv_cnt==0)
	{
			if(nhzd10_recv_buff[0]==nhzd10_address)
				nhzd10_recv_cnt++;
			else
				return 0;
	}
	else
	{
			nhzd10_recv_cnt++;
	}
	if(nhzd10_recv_cnt >= NHZD10_MODE_CMD_LEN+read_or_write_nhzd10_data)
	{
		nhzd10_recv_cnt = 0;
		return crc_nhzd10_check(nhzd10_recv_buff,NHZD10_DATA_LEN+read_or_write_nhzd10_data);
	}
	return 2;
}
void nhzd10_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void nhzd10_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void clear_nhzd10_recv_buff(void)
{
	nhzd10_recv_cnt = 0;
	memset(nhzd10_recv_buff, 0x00, NHZD10_MODE_CMD_LEN);
}

uint8_t crc_nhzd10_check(uint8_t *data,uint8_t len)
{
	uint16_t crc;
	crc=crc16_ibm_generate(data,len,0XFFFF,crc_rtu_default);
	if(((crc/256)==*(data+6+read_or_write_nhzd10_data))&&((crc%256)==*(data+7+read_or_write_nhzd10_data)))
		return 1;
	else
		return 0;
}
#endif
