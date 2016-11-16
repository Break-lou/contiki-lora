#include "modbus.h"
#include "sensor_parameter.h"
#include <string.h>
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
#if modbus_mode
uint8_t modbus_sequence_structure_model[12][12]={{"bcddeeff"},{"abcddeeffg"}};
uint8_t modbus_sequence_structure_model_num=2;
uint8_t modbus_send_data_model[12][12]={{0x01,0x03,0x00,0x00,0x00,0x02,0xff,0xff},{0x29,0x04,0x00,0x00,0x00,0x01,0xff,0xff},
																				{0x0A,0x04,0x00,0x00,0x00,0x02,0xff,0xff},{0x0B,0x04,0x00,0x00,0x00,0x01,0xff,0xff},
																				{0x02,0x03,0x00,0x00,0x00,0x02,0xff,0xff},{0x01,0x04,0x00,0x04,0x00,0x02,0xff,0xff}};
uint8_t modbus_send_data_model_num=1;
void modbus_cfg_data(modbus_structure *modbus_data);
modbus_structure sensor_modbus;
void modbus_uart_init(enum_uart_baudrate new_baudrate)
{
		UART_InitTypeDef uart_set;
		uart_set.uart_source_clock=uart_source_clock_select_rtc;
	
		uart_set.uart_baudrate=new_baudrate;
		uart_set.uart_duplex_mode=uart_half_duplex_mode;//全双工
		uart_set.uart_wordlength=uart_wordlength_8bit;
		uart_set.uart_startbits=uart_has_startbits;
		uart_set.uart_stopbits=uart_stopbits_1;
		uart_set.uart_parity=uart_parity_none;
		uart_set.uart_tx_idlestate=uart_tx_idle_high_state;
		uart_set.uart_rx_idlestate=uart_rx_idle_high_state;
		uart_set.uart_rx_fifo_threshold=uart_rx_fifo_threshold_one_byte;
		uart_configuration(&uart_set); 
}
void modbus_port_init(void)
{	
	uart_port_configuration();
}
void modbus_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void modbus_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);

}
void open_modbus_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
uint8_t modbus_strlen(uint8_t *data,uint8_t len)
{
	uint8_t i=len;
	while(*(data+(i-1))==0)
	{
		i--;
	}
	return i;
}
//modbus 初始化
void modbus_init(modbus_structure *new_modbus)
{
	uint8_t len=sizeof(modbus_send_data_model[0]);
	node_parameter.modbus_array_len=modbus_strlen(modbus_send_data_model[0],len);
	memcpy(node_parameter.modbus_array,modbus_send_data_model[0],node_parameter.modbus_array_len);
	
	node_parameter.modbus_sequence_len=strlen((char*)modbus_sequence_structure_model[0]);
	memcpy(node_parameter.modbus_sequence,modbus_sequence_structure_model[0],node_parameter.modbus_sequence_len);
	
	memcpy(new_modbus->modbus_send_array,node_parameter.modbus_array,node_parameter.modbus_array_len);
	memcpy(new_modbus->modbus_send_sequence, node_parameter.modbus_sequence, node_parameter.modbus_sequence_len);
	 
	new_modbus->modbus_send_len=node_parameter.modbus_array_len;//总发送数据长度
	new_modbus->modbus_check_sequence_len=0;			//序列长度

	new_modbus->modbus_receive_cnt=0;							//接送计数
	new_modbus->modbus_receive_len=0;							//接送长度
	new_modbus->modbus_receive_data_len_num=0;		//接收数据长度
	new_modbus->modbus_receive_data_len_locat=0;  //接收数据的长度的具体位置							
	new_modbus->modbus_send_data_len=0;    			  //发送的数据信息长度 （需校验的数据信息长度）
	
	new_modbus->modbus_start_data=0;							//起始位数据
	new_modbus->modbus_start_is=0;								//是否有起始位
	new_modbus-> modbus_start_bit=0;			  			//起始位字节个数
	
	new_modbus->modbus_address=0;									//地址
	new_modbus->modbus_address_bit=0;     				//地址字节个数
	//new_modbus->modbus_address_locat=0;   				//地址位置

	new_modbus->modbus_fun=0;											//功能码
	new_modbus->modbus_fun_bit=0;     						//功能码字节个数
	//new_modbus->modbus_fun_locat=0;								//功能码位置
	
	new_modbus->modbus_reg_address=0;							//寄存器地址
	new_modbus->modbus_reg_address_bit=0; 				//寄存器地址字节个数
	//new_modbus->modbus_reg_address_locat=0;				//寄存器地址位置		
	
	new_modbus->modbus_reg_len=0;									//寄存器长度
	new_modbus->modbus_reg_len_bit=0;     				//寄存器长度字节个数
	//new_modbus->modbus_reg_len_locat=0;						//寄存器长度位置
	
	new_modbus->modbus_check_data=0;							//校验数据
	new_modbus->modbus_check_bit=0;								//校验长度字节个数			
	//new_modbus->modbus_check_locat=0;							//检验长度位置
	
	new_modbus->modbus_end_data=0;								//结束位数据
	new_modbus->modbus_end_is=0;									//是否有结束位				
	new_modbus->modbus_end_bit=0;
	
	new_modbus->modbus_check_style=node_parameter.check_style;						//校验类型								
	new_modbus->modbus_check_style_value=node_parameter.check_style_value;//校验类型值
	new_modbus->modbus_check_init_num=0;    															//校验数组的初始值的位置
	new_modbus->modbus_check_crc_init=node_parameter.check_crc_init;    	//校验值
	
	new_modbus->modbus_receive_data_check_len=0;  												//接收到的数据组中获取的数据长度 (用于校验)
									
	
	new_modbus->modbus_check_style=modbus_check_style_crc;
	new_modbus->modbus_check_style_value=crc_rtu_default;
	new_modbus->modbus_check_crc_init=0xffff;
	
	modbus_cfg_sequence(new_modbus);//配置modbus 
	modbus_cfg_data(new_modbus);

}
bool modbus_send_data(modbus_structure *data)
{
	uint16_t check;
	uart_rx_disable();	
	data->modbus_receive_cnt=0;
	data->modbus_send_data_len=data->modbus_send_len;
	if(data->modbus_start_is)
	{
		data->modbus_check_init_num=1+data->modbus_start_bit;
		data->modbus_send_data_len-=data->modbus_start_bit;
	}
	else
	{
		data->modbus_check_init_num=1;
	}
	if(data->modbus_end_is)
	{
		data->modbus_send_data_len-=data->modbus_end_bit;
	}
	if(data->modbus_check_style==modbus_check_style_crc)
	{
		data->modbus_send_data_len-=2;
		
	}
	else if(data->modbus_check_style==modbus_check_style_sum)
	{
		data->modbus_send_data_len--;
	}
	
	check=modbus_check_generate(&data->modbus_send_array[(data->modbus_check_init_num)-1],data->modbus_send_data_len,
															data->modbus_check_crc_init,data->modbus_check_style,data->modbus_check_style_value);
	if(data->modbus_check_style==modbus_check_style_crc)
	{
			data->modbus_send_array[(data->modbus_send_len)-(data->modbus_end_is)*(data->modbus_end_bit)-2]=check/256;
			data->modbus_send_array[(data->modbus_send_len)-(data->modbus_end_is)*(data->modbus_end_bit)-1]=check%256;	
	}
	else if(data->modbus_check_style==modbus_check_style_sum)
	{
			data->modbus_send_array[(data->modbus_send_len)-(data->modbus_end_is)*(data->modbus_end_bit)-1]=check%256;
	}
	serial_tramsmit_bytes(SERIAL_PORT_UART0, data->modbus_send_array, data->modbus_send_len);		
	uart_rx_enable();	
	return true;
}

uint8_t modbus_receive(uint8_t data,modbus_structure *modbus_data)
{
	
	modbus_data->modbus_receive_array[modbus_data->modbus_receive_cnt] = data;
	if(modbus_data->modbus_check_sequence_len>modbus_data->modbus_receive_cnt)//检测前面的地址和功能码
	{
		if(*(modbus_data->modbus_check_sequence[modbus_data->modbus_receive_cnt])!=data)
		{
			modbus_data->modbus_receive_cnt=0;
			return 0;
		}
	} 
//	if((modbus_data->modbus_receive_data_len_locat-1)==modbus_data->modbus_receive_cnt)
//	{
//		modbus_data->modbus_receive_data_len_num=data;
//		modbus_data->modbus_receive_len=modbus_data->modbus_start_is*modbus_data->modbus_start_bit+
//																		modbus_data->modbus_address_bit+modbus_data->modbus_fun_bit+
//																		2*modbus_data->modbus_reg_len+modbus_data->modbus_check_bit+
//																		modbus_data->modbus_end_is*modbus_data->modbus_end_bit;																	
//	}
	modbus_data->modbus_receive_cnt++;
	//timers_reset(400);
	
//	if(modbus_data->modbus_receive_len==modbus_data->modbus_receive_cnt)
//	{
//			modbus_data->modbus_receive_cnt=0;
//			modbus_data->modbus_receive_data_check_len=modbus_data->modbus_receive_len-modbus_data->modbus_start_is*modbus_data->modbus_start_bit
//																									-modbus_data->modbus_end_is*modbus_data->modbus_end_bit;
//			uint16_t check=modbus_check_generate(&modbus_data->modbus_receive_array[modbus_data->modbus_check_init_num],
//																					 modbus_data->modbus_receive_data_check_len,
//																					 modbus_data->modbus_check_crc_init,modbus_data->modbus_check_style,
//																				   modbus_data->modbus_check_style_value);
//			if(modbus_data->modbus_check_style==modbus_check_style_crc)
//			{
//					if((modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-2]==check/256)&&
//					(modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-1]==check%256))
//						return 1;
//			}
//			else if(modbus_data->modbus_check_style==modbus_check_style_sum)
//			{
//					if((modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-1])==(check%256))
//						return 1;
//			} 
//			return 0;
//	}
	return 1;
}
uint8_t modbus_receive_check(modbus_structure *modbus_data)
{
	uint16_t check;
	modbus_data->modbus_receive_len=modbus_data->modbus_receive_cnt;
	modbus_data->modbus_receive_cnt=0;
	modbus_data->modbus_receive_data_check_len=modbus_data->modbus_receive_len-(modbus_data->modbus_start_is)*(modbus_data->modbus_start_bit)
																							-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-modbus_data->modbus_check_bit;
	check=modbus_check_generate(&modbus_data->modbus_receive_array[(modbus_data->modbus_check_init_num)-1],
																			 modbus_data->modbus_receive_data_check_len,
																			 modbus_data->modbus_check_crc_init,modbus_data->modbus_check_style,
																			 modbus_data->modbus_check_style_value);
	if(modbus_data->modbus_check_style==modbus_check_style_crc)
	{
			if((modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-2]!=check/256)||
			(modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-1]!=check%256))
			{
				
				return 0;
			}
			else if((modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-2]==check/256)&&
			(modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-1]==check%256))
			{
				return 1;
			}
	}
	else if(modbus_data->modbus_check_style==modbus_check_style_sum)
	{
			if((modbus_data->modbus_receive_array[(modbus_data->modbus_receive_len)-(modbus_data->modbus_end_is)*(modbus_data->modbus_end_bit)-1])==(check%256))
				return 1;
			else 
				return 0;
	} 
	return 0;
	
}
void modbus_send_data_storage(uint8_t *data,modbus_structure *modbus_data,uint8_t len)
{
	modbus_data->modbus_send_len=len;
//	if(modbus_data->modbus_send_len>modbus_data->modbus_send_array_len)
//	{
//		while(modbus_data->modbus_send_len>modbus_data->modbus_send_array_len)
//		{
//			modbus_data->modbus_send_array_len+=2;
//		}
//		modbus_data->modbus_send_array=realloc(modbus_data->modbus_send_array,modbus_data->modbus_send_array_len);
//		assert(modbus_data->modbus_send_array!=NULL);
//	}
	memcpy(modbus_data->modbus_send_array,data,modbus_data->modbus_send_len);
	modbus_cfg_data(modbus_data);
}
void modbus_cfg_data(modbus_structure *modbus_data)
{
	uint8_t len;
	len=modbus_data->modbus_send_len;
	for(uint8_t i=0;i<len;i++)
	{
		*(modbus_data->modbus_check_sequence[i])=modbus_data->modbus_send_array[i];
	}
	
}
void modbus_cfg_sequence(modbus_structure *modbus_data)
{
	uint8_t len;
	len=0;
	//加入清零操作
	modbus_data->modbus_check_sequence_len=0;
	len=node_parameter.modbus_sequence_len;//strlen((char *)modbus_data->modbus_send_sequence);
	for(uint8_t i=0;i<len;i++)
	{
		switch(modbus_data->modbus_send_sequence[i])
		{
			case 'a':
			modbus_data->modbus_start_is=1;			
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_start_data)+(1-modbus_data->modbus_start_bit);
			modbus_data->modbus_start_bit++;	
			modbus_data->modbus_check_sequence_len++;
			break;
			
			case 'b':
//			if(modbus_data->modbus_address_bit=0)
//			{
//				modbus_data->modbus_address_locat=i+1;
//			}		
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_address)+(1-modbus_data->modbus_address_bit);	
			modbus_data->modbus_address_bit++;			
			modbus_data->modbus_check_sequence_len++;
			break;
			
			case 'c':
//			if(modbus_data->modbus_fun_bit=0)
//			{
//				modbus_data->modbus_fun_locat=i+1;
//			}	
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_fun)+(1-modbus_data->modbus_fun_bit);	
			modbus_data->modbus_fun_bit++;
			modbus_data->modbus_check_sequence_len++;
			break;
			
			case 'd':
			if(modbus_data->modbus_reg_address_bit==0)
			{
//				modbus_data->modbus_reg_address_locat=i+1;
				modbus_data->modbus_receive_data_len_locat=i+1;//一般在这里就是接收到的数据长度信息的存储地方
			}		
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_reg_address)+(1-modbus_data->modbus_reg_address_bit);	
			modbus_data->modbus_reg_address_bit++;
			break;
			
			case 'e':
//			if(modbus_data->modbus_reg_len_bit=0)
//			{
//				modbus_data->modbus_reg_len_locat=i+1;
//			}		
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_reg_len)+(1-modbus_data->modbus_reg_len_bit);
			modbus_data->modbus_reg_len_bit++;	
			
			break;
		
			case 'f':
//			if(modbus_data->modbus_check_bit=0)
//			{
//				modbus_data->modbus_check_locat=i+1;
//			}			
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_check_data)+(1-modbus_data->modbus_check_bit);
			modbus_data->modbus_check_bit++;		
			break;
			
			case 'g':
			modbus_data->modbus_end_is=1;		
			modbus_data->modbus_check_sequence[i]=((uint8_t *)&modbus_data->modbus_end_data)+(1-modbus_data->modbus_end_bit);		
			modbus_data->modbus_end_bit++;
			break;
			default:
			break;
		}
	}
}
#endif



