#include "sdi12_include.h"
#include "delay.h"
uint8_t sdi12_address=0x30;
uint8_t sdi12_info_command[SDI12_INFO_COMMAND_LEN] = {'0', 'I', '!'};
uint8_t sdi12_address_query_command[SDI12_ADDRESS_QUERY_COMMAND_LEN] = {'?', '!'};
uint8_t sdi12_measure_command[SDI12_MEASURE_COMMAND_LEN] = {'0', 'M', '!'};
uint8_t sdi12_data_command[SDI12_DATA_COMMAND_LEN] = {'0', 'D', '0', '!'};
uint8_t sdi12_change_address_command[SDI12_CHANGE_ADDRESS_COMMAND_LEN] = {'0', 'A', '0', '!'};
uint8_t sdi12_acknowledge_active_command[SDI12_ACKNOWLEDGE_ACTIVE_COMMAND_LEN] = {'0', '!'};
uint8_t sdi12_measure_crc_command[SDI12_MEASURE_CRC_COMMAND_LEN] = {'0','M','C', '!'};
uint8_t sdi12_end_string[SDI12_END_STRING_LEN] = {0X0D, 0X0A};
uint8_t sdi12_recv_buff[SDI12_RECV_BUFF_LEN];
uint8_t sdi12_recv_len = 0;
uint8_t sdi12_timeout_flag = 0;
uint8_t sdi12_outer_loop_ctrl;
uint8_t sdi12_inter_loop_ctrl;
uint8_t sdi12_rec_len=0;
UART_InitTypeDef sdi12_uart_param;
void sdi12_param_init(void)
{
	sdi12_uart_param.uart_source_clock = uart_source_clock_select_rtc;
	
	sdi12_uart_param.uart_baudrate = uart_baudrate_1200;
	sdi12_uart_param.uart_baudrate_offset = 0;
	sdi12_uart_param.uart_duplex_mode = uart_half_duplex_mode;
	sdi12_uart_param.uart_wordlength = uart_wordlength_7bit;
	sdi12_uart_param.uart_startbits = uart_has_startbits;
	sdi12_uart_param.uart_stopbits = uart_stopbits_1;
	sdi12_uart_param.uart_parity = 	uart_parity_even;
	//sdi12_uart_param.uart_parity =uart_parity_none;
	sdi12_uart_param.uart_rx_fifo_threshold = uart_rx_fifo_threshold_one_byte;
	sdi12_uart_param.uart_tx_idlestate = uart_tx_idle_low_state;	
	sdi12_uart_param.uart_rx_idlestate = uart_rx_idle_low_state;
	uart_configuration(&sdi12_uart_param);
}

void sdi12_break(void)
{
	SDI12_BREAK();
	//延迟16MS	
}

void sdi12_marking(void)
{	
	SDI12_MARKING();
	//延迟9MS
}
void sdi12_send_buff(uint8_t *buff, uint8_t len)
{

	uart_send_bytes(buff, len);
} 

void sdi12_recv_with_end_string(uint8_t *buff, uint8_t *end_str, uint8_t len)
{
	//uart_initial_recv_with_end_string(buff, end_str, len);

}
void s_5tm_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void s_5tm_uart_disable_wake_event(void)
{	
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void sdi12_enable_tx_crossbar(void)
{
	UART_TX_OUT();
	UART_RX_IN();
	uart_rx_disable();
	uart_tx_enable();
}
void sdi12_enable_rx_crossbar(void)
{	
	UART_TX_IN();
	UART_RX_IN();
	uart_tx_disable();
	uart_rx_enable();
}
void sdi12_enable_crossbar(void)
{
	UART_PORT_IN();
}

void sdi12_disable_crossbar(void)
{
	uart_rx_disable();
	uart_tx_disable();
	

}
void sdi12_send_command(uint8_t addr, uint8_t *cmd, uint8_t len)
{
	sdi12_enable_tx_crossbar();
	cmd[0] = addr;
	uart_send_bytes(cmd, len);
}
uint8_t sdi12_change_address(uint8_t src_addr, uint8_t dest_addr)
{
	uint8_t addr;
	sdi12_enable_tx_crossbar();//使能发送
	sdi12_change_address_command[0]=src_addr;
	sdi12_change_address_command[2]=dest_addr;
	sdi12_send_buff(sdi12_change_address_command, SDI12_CHANGE_ADDRESS_COMMAND_LEN);
	sdi12_enable_rx_crossbar();//使能接收
	sdi12_rec_len=3;
	return addr;
}
uint8_t sdi12_query_address(void)
{
	sdi12_enable_tx_crossbar();//使能发送
	sdi12_send_buff(sdi12_address_query_command, SDI12_ADDRESS_QUERY_COMMAND_LEN);	
	sdi12_enable_rx_crossbar();//使能接收
	//延时接收
	return 0;
}
uint8_t sdi12_address_response(uint8_t *data)
{
	uint8_t i;
	uint8_t address;
	while(1)
	{
		if((i>0)&&(data[i-1]==0X0D)&&(data[i]==0X0A))
		{
				sdi12_address=data[i-2];
				address=data[i-2];
				break;
		}
		i++;
	}
	return address;
}
//测量命令 1M!
uint8_t sdi12_measure(void)
{
	sdi12_enable_tx_crossbar();//使能发送
	sdi12_measure_command[0]=sdi12_address;
	sdi12_send_buff(sdi12_measure_command, SDI12_MEASURE_COMMAND_LEN);
	sdi12_enable_rx_crossbar();//使能接收
	sdi12_rec_len=5;
	//延时接收
	return 0;
}
uint8_t acsii_to_number(uint8_t data)
{
		if((data>0x2f)&&(data<0x3a))
			return data-0x30;
		else
			return 0;
}
//测量命令回复信息处理

measure_type sdi12_measure_response(uint8_t *data)
{
	measure_type measure_data_acsii;
	measure_data_acsii.time=acsii_to_number(data[1])*100;
	measure_data_acsii.time+=acsii_to_number(data[2])*10;
	measure_data_acsii.time+=acsii_to_number(data[3]);
	measure_data_acsii.num=acsii_to_number(data[4]);
	return measure_data_acsii;
}
//发送数据接收命令
uint8_t sdi12_data_receive(measure_type data)
{
	sdi12_enable_tx_crossbar();//使能发送
	sdi12_data_command[0]=sdi12_address;
	sdi12_send_buff(sdi12_data_command, SDI12_DATA_COMMAND_LEN);
	sdi12_enable_rx_crossbar();//使能接收
	//sdi12_rec_len=data.num;
	//延时接收
	return 0;
}

sdi_data_type sdi12_data_response(uint8_t* data)
{
	
	uint8_t i,dp=0,flag=0,num=0;
	sdi_data_type sdi12_data;
	sdi12_data.dielectric=0;
	sdi12_data.Temperature=0;
	sdi12_data.humidity=0;
	sdi12_data.dp1_num=0;
	sdi12_data.dp2_num=0;
	sdi12_data.dp3_num=0;
	while(1)
	{
			if(data[num]==sdi12_address)
			{
					break;
			}
			else
				num++;
	}
	for(i=num;data[i]!=0x0d;i++)
	{
			if(data[i]==0x2b)
			{
				flag++;
				dp=0;
				if(flag==1)
				{
					sdi12_data.dp1=0;
				}
				else if(flag==2)
				{				
					sdi12_data.dp2=0;
				}
				else if(flag==3)
				{
					sdi12_data.dp3=0;
				}
			}
			else if(data[i]==0x2d)
			{
				flag++;
				dp=0;
				if(flag==1)
				{
					sdi12_data.dp1=1;
				}
				else if(flag==2)
				{				
					sdi12_data.dp2=1;
				}
				else if(flag==3)
				{
					sdi12_data.dp3=1;
				}
			}
			else if(data[i]==0x2e)
			{
				dp=1;
			}
			else if(flag==1)
			{
					
				if(dp==1)
				{
						sdi12_data.dp3_num++;
				}		
				sdi12_data.humidity+=acsii_to_number(data[i]);
				sdi12_data.humidity*=10;

			}
			else if(flag==2)
			{		
				if(dp==1)
				{
						sdi12_data.dp1_num++;
				}		
				sdi12_data.dielectric+=acsii_to_number(data[i]);
				sdi12_data.dielectric*=10;
			}
			else if(flag==3)
			{
				
				if(dp==1)
				{
						sdi12_data.dp2_num++;
				}		
				sdi12_data.Temperature+=acsii_to_number(data[i]);
				sdi12_data.Temperature*=10;
			}
	}
	sdi12_data.dielectric=sdi12_data.dielectric/10;
	sdi12_data.Temperature=sdi12_data.Temperature/10;
	sdi12_data.humidity=sdi12_data.humidity/10;
	sdi12_data.FLAG_5TE_OR_5TM=flag;
	return sdi12_data;
}
//接收数据
uint8_t sdi_recv_buff[24];
uint8_t sdi_recv_cnt=0;
uint8_t sdi12_analyster(uint8_t data)
{
		sdi_recv_buff[sdi_recv_cnt]=data;
		if((sdi_recv_cnt>0)&&(sdi_recv_buff[sdi_recv_cnt-1]==0X0D)&&(sdi_recv_buff[sdi_recv_cnt]==0X0A))
		{			
				memset(&sdi_recv_buff[sdi_recv_cnt+1],0,24-sdi_recv_cnt-1);
				sdi_recv_cnt=0;
				return 1;
		}
		//sdi_recv_cnt++;
		if(sdi_recv_cnt==0)
		{
			if(sdi_recv_buff[0]!=sdi12_address)
				return 0;
		}
		sdi_recv_cnt++;

//		if(sdi_recv_cnt==sdi12_rec_len)
//		{
//			sdi_recv_cnt=0;
//			return 1;
//		}
		return 2;
}
uint8_t sdi12_receive(uint8_t data)
{
		sdi_recv_buff[sdi_recv_cnt]=data;
		if((sdi_recv_cnt>0)&&(sdi_recv_buff[sdi_recv_cnt-1]==0X0D)&&(sdi_recv_buff[sdi_recv_cnt]==0X0A))
		{
				memset(&sdi_recv_buff[sdi_recv_cnt+1],0,24-sdi_recv_cnt-1);
				sdi_recv_cnt=0;
				return 1;
		}
		sdi_recv_cnt++;
		if(sdi_recv_cnt==24)
			sdi_recv_cnt=0;
		return 0;
}



void soft_reset(void)
{
	SI32_CLKCTRL_A_enable_apb_to_modules_1(SI32_CLKCTRL_0, SI32_CLKCTRL_A_APBCLKG1_MISC0);	
	SI32_RSTSRC_A_generate_software_reset(SI32_RSTSRC_0);
}
int sdi12_is_sensor_active(uint8_t addr)//该传感器是否激活
{
	int ret = -1;
	memset(sdi12_recv_buff, 0, sizeof(sdi12_recv_buff));
	sdi12_break();
	sdi12_marking();
	sdi12_send_command(addr, sdi12_acknowledge_active_command, SDI12_ACKNOWLEDGE_ACTIVE_COMMAND_LEN);
	if(!sdi12_recv_response(sdi12_recv_buff, &sdi12_recv_len, 40))
	{
		
		if((sdi12_recv_buff[0] == addr) || (sdi12_recv_buff[1] == addr))
		{
			ret = 0;
		}
		else
		{
			//while(1);
			soft_reset();
		}
	}
	
	sdi12_disable_crossbar();	
	SDI12_RELEASE_BUS();

	return ret;	
}

int sdi12_recv_response(uint8_t *recv_buff, uint8_t *len, uint32_t time)
{
	int ret = -1;
//	uint32_t timeout_id;
	
	sdi12_enable_rx_crossbar();
	sdi12_recv_with_end_string(recv_buff, sdi12_end_string, SDI12_END_STRING_LEN);
//	sdi12_timeout_flag = 0;
//#if defined SDI12_USE_USART
//	usart_rx_complete_flag = 0;
//#elif defined SDI12_USE_UART
//	uart_rx_complete_flag = 0;
//#endif	
//	
//	timeout_id = os_timeout_add(time, TASK_NO_TASK, EVENT_NO_EVENT, &sdi12_timeout_flag);

//#if defined SDI12_USE_USART
//	while(!usart_rx_complete_flag && !sdi12_timeout_flag);
//	print_string(sdi12_recv_buff, usart_recv_index);
//#elif defined SDI12_USE_UART
//	while(!uart_rx_complete_flag && !sdi12_timeout_flag);
//	print_string(sdi12_recv_buff, uart_recv_index);
//#endif

//	os_timeout_delete(timeout_id);
//	sdi12_timeout_flag = 0;

//	if(uart_rx_complete_flag)
//	{
//		uart_rx_complete_flag = 0;
//		*len = uart_recv_index;
//		ret = 0;
//	}
//	else
//	{
//		*len = 0;
//	}	



//	sdi12_disable_crossbar();

	return ret;
}


