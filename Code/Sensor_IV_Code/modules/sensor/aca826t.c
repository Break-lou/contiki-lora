#include "aca826t.h"
#if ACA826T_OPERATE
#define ACA826T_MODE_CMD_LEN 5//发送包长度
#define UART_RECV_BUFF_LEN 20//接收包长度
#define ACA826T_SET_ADDR_LEN 6
#define ACA826T_SET_BAUD_LEN 6
#define ACA826T_ADDRESS_LOCATION 5//更改数据位位置
#define ACA826T_ZERO_LEN 6//零点数据长度
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
//波特率选项
#define ACA826T_SERIAL_PORT 	SERIAL_PORT_UART0
#define ACA826T_SERIAL_BAUD 	serial_baudrate_9600

uint8_t checksum(uint8_t* data,uint8_t len);
uint8_t read_or_write_aca826t_data;
UART_InitTypeDef aca826t_uart_set;
uint8_t aca826t_address=0x00;
uint8_t default_aca826t_smple_cmd[ACA826T_MODE_CMD_LEN] 	= {0x68,0x04,0x00,0x04,0x08};
//uint8_t default_smple_half_cmd[ACA826T_MODE_CMD_LEN] = {0x0F,0x04,0x00,0x01,0x00,0x01};
uint8_t set_aca826t_address_cmd[ACA826T_SET_ADDR_LEN] 			= {0x68,0x05,0xFF,0x0F,0x00,0x13};
uint8_t set_aca826t_save_address_cmd[ACA826T_SET_ADDR_LEN] 	= {0x68,0x05,0x00,0x0F,0x00,0x15};
uint8_t set_aca826t_baudrate_cmd[ACA826T_SET_BAUD_LEN]	  = {0x68,0x05,0x00,0x0B,0x02,0x13};
uint8_t set_aca826t_zero_cmd[ACA826T_ZERO_LEN]= {0x68,0x05,0x00,0x05,0x00,0x0A};
uint8_t aca826t_recv_buff[25];
uint8_t aca826t_recv_cnt = 0;
uint8_t aca826t_data_len=250;
void aca826t_port_init(void)
{	
		uart_port_configuration();
}
void aca826t_port_sleep(void)
{
		uart_port_sleep();
}
void open_aca826t_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void close_aca826t_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
void aca826t_uart_init(enum_uart_baudrate new_baudrate)
{
		aca826t_uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		aca826t_uart_set.uart_baudrate=new_baudrate;
		aca826t_uart_set.uart_duplex_mode=uart_half_duplex_mode;//全双工
		aca826t_uart_set.uart_wordlength=uart_wordlength_8bit;
		aca826t_uart_set.uart_startbits=uart_has_startbits;
		aca826t_uart_set.uart_stopbits=uart_stopbits_1;
		aca826t_uart_set.uart_parity=uart_parity_none;
		aca826t_uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		aca826t_uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		aca826t_uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&aca826t_uart_set);
}
uint8_t set_aca826t_address(uint8_t new_address)
{
	set_aca826t_save_address_cmd[4]=new_address;
	aca826t_address=new_address;
	set_aca826t_save_address_cmd[ACA826T_SET_ADDR_LEN-1]=checksum(set_aca826t_save_address_cmd,ACA826T_SET_ADDR_LEN-1);
	uart_rx_disable();
	serial_tramsmit_bytes(ACA826T_SERIAL_PORT, set_aca826t_save_address_cmd, ACA826T_SET_ADDR_LEN);
	uart_rx_enable();
	//default_smple_half_cmd[0]=aca826t_address;

	
	return 1;
}
//设置零点：00绝对零点
//          01相对零点
void set_aca826t_zero(uint8_t data)
{
		set_aca826t_zero_cmd[4]=data;
		set_aca826t_zero_cmd[ACA826T_ZERO_LEN-1]=checksum(set_aca826t_zero_cmd,ACA826T_ZERO_LEN-1);
		uart_rx_disable();
		serial_tramsmit_bytes(ACA826T_SERIAL_PORT, set_aca826t_zero_cmd, ACA826T_ZERO_LEN);
		uart_rx_enable();
}
//设置波特率
uint8_t set_aca826t_baudrate(enum_uart_baudrate new_baudrate)
{
	switch(new_baudrate)
	{
		case uart_baudrate_2400:
			set_aca826t_baudrate_cmd[4]=0x00;
			break;
		case uart_baudrate_4800:
			set_aca826t_baudrate_cmd[4]=0x01;
			break;
		case uart_baudrate_9600:
			set_aca826t_baudrate_cmd[4]=0x02;
			break;
		case uart_baudrate_19200:
			set_aca826t_baudrate_cmd[4]=0x03;
			break;
		case uart_baudrate_38400:
			set_aca826t_baudrate_cmd[4]=0x04;
			break;
		case uart_baudrate_115200:
			set_aca826t_baudrate_cmd[4]=0x05;
			break;
		default:
			set_aca826t_baudrate_cmd[4]=0x02;
			break;	
	}
	set_aca826t_baudrate_cmd[ACA826T_SET_BAUD_LEN-1]=checksum(set_aca826t_baudrate_cmd,ACA826T_SET_BAUD_LEN-1);
	uart_rx_disable();
	serial_tramsmit_bytes(ACA826T_SERIAL_PORT, set_aca826t_baudrate_cmd, ACA826T_SET_BAUD_LEN);
	uart_rx_enable();
//	aca826t_uart_init(new_baudrate);
//	close_aca826t_sensor_power();
	return 1;
}
//读取角度命令
int aca826t_sample_data(void)
{
	default_aca826t_smple_cmd[ACA826T_MODE_CMD_LEN-1]=checksum(default_aca826t_smple_cmd,ACA826T_MODE_CMD_LEN-1);
	uart_rx_disable();	
	serial_tramsmit_bytes(ACA826T_SERIAL_PORT, default_aca826t_smple_cmd, ACA826T_MODE_CMD_LEN);	
	uart_rx_enable();	
  return 0;
}
//数据接收
uint8_t aca826t_analyster(uint8_t data)
{
	aca826t_recv_buff[aca826t_recv_cnt] = data;
	if(aca826t_recv_cnt==0)//判断提示符
	{
			if(aca826t_recv_buff[0]!=0x68)
			{
				aca826t_recv_cnt=0;
				return 0;
			}
	}
	else if(aca826t_recv_cnt==1)//判断数据长度
	{
			aca826t_data_len=aca826t_recv_buff[1];	
	}
	else if(aca826t_recv_cnt==2)//判断地址
	{
			if(aca826t_recv_buff[2]!=aca826t_address)
			{
				aca826t_data_len=250;
				aca826t_recv_cnt=0;
				return 0;
			}
	}
//	else if(aca826t_recv_cnt==3)//附加判断数据长度
//	{
//			if(aca826t_recv_buff[3]==0x84)
//			{
//				aca826t_data_len=aca826t_recv_buff[1];
//			}
//	}
	if(aca826t_recv_cnt == aca826t_data_len)//检验检测
	{
			aca826t_recv_cnt = 0;
			
			//校验
			if(aca826t_recv_buff[aca826t_data_len]==checksum(aca826t_recv_buff,aca826t_data_len))
      {   
          aca826t_data_len=250;
          return 1;
      }
      else
      {
          aca826t_data_len=250;
          return 0;
      }
	}
	
	aca826t_recv_cnt++;
	return 2;
	
}
void aca826t_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void aca826t_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void clear_aca826t_recv_buff(void)
{
	aca826t_recv_cnt = 0;
	memset(aca826t_recv_buff, 0x00, ACA826T_MODE_CMD_LEN);
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
