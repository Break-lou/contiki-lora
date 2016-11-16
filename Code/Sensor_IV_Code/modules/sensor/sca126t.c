#include "sca126t.h"
#if SCA126T_OPERATE
#define SCA126T_MODE_CMD_LEN 5//发送包长度
#define UART_RECV_BUFF_LEN 20//接收包长度
#define SCA126T_SET_ADDR_LEN 6
#define SCA126T_SET_BAUD_LEN 6
#define SCA126T_ADDRESS_LOCATION 5//更改数据位位置
#define SCA126T_ZERO_LEN 6//数据长度
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
//波特率选项
#define SCA126T_SERIAL_PORT 	SERIAL_PORT_UART0
#define SCA126T_SERIAL_BAUD 	serial_baudrate_9600



uint8_t read_or_write_sca126t_data;
UART_InitTypeDef sca126t_uart_set;
uint8_t sca126t_address=0x00;
uint8_t default_sca126t_smple_cmd[SCA126T_MODE_CMD_LEN] 	= {0x68,0x04,0x00,0x04,0x08};
//uint8_t default_smple_half_cmd[SCA126T_MODE_CMD_LEN] = {0x0F,0x04,0x00,0x01,0x00,0x01};
uint8_t set_sca126t_address_cmd[SCA126T_SET_ADDR_LEN] 			= {0x68,0x05,0xFF,0x0F,0x00,0x13};
uint8_t set_sca126t_save_address_cmd[SCA126T_SET_ADDR_LEN] 	= {0x68,0x05,0x00,0x0F,0x00,0x14};
uint8_t set_sca126t_baudrate_cmd[SCA126T_SET_BAUD_LEN]	  = {0x68,0x05,0x00,0x0B,0x02,0x12};
uint8_t set_sca126t_zero_cmd[SCA126T_ZERO_LEN] = {0x68,0x05,0x00,0x05,0x00,0x0A};
uint8_t sca126t_recv_buff[25];
uint8_t sca126t_recv_cnt = 0;
uint8_t sca126t_data_len=250;
void sca126t_port_init(void)
{	
		uart_port_configuration();
}
void sca126t_port_sleep(void)
{
		uart_port_sleep();
}
void open_sca126t_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void close_sca126t_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void sca126t_uart_init(enum_uart_baudrate new_baudrate)
{
		sca126t_uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		sca126t_uart_set.uart_baudrate=new_baudrate;
		sca126t_uart_set.uart_duplex_mode=uart_half_duplex_mode;//全双工
		sca126t_uart_set.uart_wordlength=uart_wordlength_8bit;
		sca126t_uart_set.uart_startbits=uart_has_startbits;
		sca126t_uart_set.uart_stopbits=uart_stopbits_1;
		sca126t_uart_set.uart_parity=uart_parity_none;
		sca126t_uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		sca126t_uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		sca126t_uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&sca126t_uart_set);
}
uint8_t set_sca126t_address(uint8_t new_address)
{
	set_sca126t_save_address_cmd[4]=new_address;
	sca126t_address=new_address;
	set_sca126t_save_address_cmd[SCA126T_SET_ADDR_LEN-1]=checksum(set_sca126t_save_address_cmd,SCA126T_SET_ADDR_LEN-1);
	uart_rx_disable();
	serial_tramsmit_bytes(SCA126T_SERIAL_PORT, set_sca126t_save_address_cmd, SCA126T_SET_ADDR_LEN);
	uart_rx_enable();
	//default_smple_half_cmd[0]=sca126t_address;

	
	return 1;
}
//设置零点：00绝对零点
//          01相对零点
void set_sca126t_zero(uint8_t data)
{
		set_sca126t_zero_cmd[4]=data;
		set_sca126t_zero_cmd[SCA126T_ZERO_LEN-1]=checksum(set_sca126t_zero_cmd,SCA126T_ZERO_LEN-1);
		uart_rx_disable();
		serial_tramsmit_bytes(SCA126T_SERIAL_PORT, set_sca126t_zero_cmd, SCA126T_ZERO_LEN);
		uart_rx_enable();
}
//设置波特率
uint8_t set_sca126t_baudrate(enum_uart_baudrate new_baudrate)
{
	switch(new_baudrate)
	{
		case uart_baudrate_2400:
			set_sca126t_baudrate_cmd[4]=0x00;
			break;
		case uart_baudrate_4800:
			set_sca126t_baudrate_cmd[4]=0x01;
			break;
		case uart_baudrate_9600:
			set_sca126t_baudrate_cmd[4]=0x02;
			break;
		case uart_baudrate_19200:
			set_sca126t_baudrate_cmd[4]=0x03;
			break;
		case uart_baudrate_38400:
			set_sca126t_baudrate_cmd[4]=0x04;
			break;
		case uart_baudrate_115200:
			set_sca126t_baudrate_cmd[4]=0x05;
			break;
		default:
			set_sca126t_baudrate_cmd[4]=0x02;
			break;	
	}
	set_sca126t_baudrate_cmd[SCA126T_SET_BAUD_LEN-1]=checksum(set_sca126t_baudrate_cmd,SCA126T_SET_BAUD_LEN-1);
	uart_rx_disable();
	serial_tramsmit_bytes(SCA126T_SERIAL_PORT, set_sca126t_baudrate_cmd, SCA126T_SET_BAUD_LEN);
	uart_rx_enable();
//	sca126t_uart_init(new_baudrate);
//	close_sca126t_sensor_power();
	return 1;
}
//读取角度命令
int sca126t_sample_data(void)
{

	default_sca126t_smple_cmd[SCA126T_MODE_CMD_LEN-1]=checksum(default_sca126t_smple_cmd,SCA126T_MODE_CMD_LEN-1);
	uart_rx_disable();	
	serial_tramsmit_bytes(SCA126T_SERIAL_PORT, default_sca126t_smple_cmd, SCA126T_MODE_CMD_LEN);	
	uart_rx_enable();	
  return 0;
}
//数据接收
uint8_t sca126t_analyster(uint8_t data)
{
	sca126t_recv_buff[sca126t_recv_cnt] = data;
	if(sca126t_recv_cnt==0)//判断提示符
	{
			if(sca126t_recv_buff[0]!=0x68)
			{
				sca126t_recv_cnt = 0;
				return 0;
			}
	}
	else if(sca126t_recv_cnt==1)//判断数据长度
	{
				sca126t_data_len=sca126t_recv_buff[1];	
	}
	else if(sca126t_recv_cnt==2)//判断地址
	{
			if(sca126t_recv_buff[2]!=sca126t_address)
			{
				sca126t_data_len=250;
				sca126t_recv_cnt = 0;
				return 0;
			}
	}
//	else if(sca126t_recv_cnt==3)//附加判断数据长度
//	{
//			if(sca126t_recv_buff[3]==0x81||sca126t_recv_buff[3]==0x82||sca126t_recv_buff[3]==0x84)
//			{
//				sca126t_data_len=sca126t_recv_buff[1];
//			}
//	}
	if(sca126t_recv_cnt == sca126t_data_len)//检验检测
	{
			sca126t_recv_cnt = 0;
			
			//校验检测
			if(sca126t_recv_buff[sca126t_data_len]==checksum(sca126t_recv_buff,sca126t_data_len))
			{		
					sca126t_recv_buff[24]=sca126t_data_len;
					sca126t_data_len=250;
					
					return 1;
			}
			else
			{
					sca126t_data_len=250;
					return 0;
			}
	}
	
	sca126t_recv_cnt++;
	return 2;
	
}
void sca126t_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void sca126t_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void clear_sca126t_recv_buff(void)
{
	sca126t_recv_cnt = 0;
	memset(sca126t_recv_buff, 0x00, SCA126T_MODE_CMD_LEN);
}
uint8_t checksum(uint8_t* data,uint8_t len)
{
		uint16_t check=0;
		uint8_t i;
		for(i=1;i<len;i++)
		{
				check += data[i];
		}
		i=check&0xff;
		return i;
}

#endif
