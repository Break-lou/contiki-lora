#include "rotonic.h"
#include "uart.h"
#include "contiki.h"
#include "sensor_lvdt_process.h"
#include "sys_event.h"
#include "sensor_rotonic_process.h"
#include "power_manager.h"
#include "math.h"
#if ROTONIC_OPERATE
uint8_t rotonic_sample_cmd[ROTONIC_SAMPLE_CMD_LEN]={0x7b,0x46,0x30,0x30,0x52,0x44,0x44,0x7d,0x0d};  //command packet
uint8_t rotonic_recv_buff[ROTONIC_RECV_BUFF_LEN];

UART_InitTypeDef rotonic_uart_param;

float tempData;
float humiData;
float tempBuf[4];
float humiBuf[4];


void rotonic_port_init(void)
{	
		uart_port_configuration();
}
void rotonic_port_sleep(void)
{
		uart_port_sleep();
}
void rotonic_uart_enable_wake_event(void)
{	
	SI32_PMU_A_enable_uart0_wake_event(SI32_PMU_0);
}
void rotonic_uart_disable_wake_event(void)
{
	SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
}
void rotonic_param_init(void)
{
	rotonic_uart_param.uart_source_clock = uart_source_clock_select_apb;
	rotonic_uart_param.uart_baudrate = uart_baudrate_19200;	
	rotonic_uart_param.uart_baudrate_offset = 0;
	
	rotonic_uart_param.uart_duplex_mode = uart_full_duplex_mode;
	rotonic_uart_param.uart_wordlength = uart_wordlength_8bit;
//	rotonic_uart_param.uart_parity_bit = uart_none_parity_bit;
	rotonic_uart_param.uart_startbits = uart_has_startbits;
	rotonic_uart_param.uart_stopbits = uart_stopbits_1;
	rotonic_uart_param.uart_tx_idlestate = uart_tx_idle_high_state;
	rotonic_uart_param.uart_rx_idlestate = uart_rx_idle_high_state;
	rotonic_uart_param.uart_rx_fifo_threshold = uart_rx_fifo_threshold_one_byte;

	uart_configuration(&rotonic_uart_param);
}

int rotonic_sample(void)
{
	int success = -1;		
	memset(rotonic_recv_buff, 0, ROTONIC_RECV_BUFF_LEN);
  rotonic_rec_cnt = 0;	
	uart_rx_disable();
	uart_send_bytes(rotonic_sample_cmd, ROTONIC_SAMPLE_CMD_LEN);	
	uart_rx_enable();
	return success;
}
uint8_t rotonic_rec_cnt =0;
void rotonic_rec_data(uint8_t data)
{
	if(rotonic_rec_cnt == 0 && data != '{')
	{
		rotonic_rec_cnt = 0;
		return;
	}
	if( data == 0x00)
	{
		return;
	}
	if(rotonic_rec_cnt <110)
	{
		rotonic_recv_buff [rotonic_rec_cnt++] = data;	
	}
	if(data == 0x0D )
	{
		if(rotonic_check(rotonic_recv_buff,103))
		{
			uart_rx_disable();
			SI32_PMU_A_disable_uart0_wake_event(SI32_PMU_0);
			SI32_UART_B_flush_rx_fifo(SI32_UART_0);
			process_post(&sensor_rotonic_process,PROCESS_RECEIVE_COMPLETE_EVENT,NULL);
		}
		else
		{
			rotonic_rec_cnt = 0;
		}
	}
}
uint8_t rotonic_temp_data[6];
uint8_t rotonic_humi_data[6];
uint8_t rotonic_temp_sign = 0;
uint8_t rotonic_temp_integer = 0;
uint8_t rotonic_temp_decimal = 0;
uint8_t rotonic_humi_integer = 0;
uint8_t rotonic_humi_decimal = 0;

void rotonic_parse_recv_data(uint8_t *recv_buff)
{  
  uint8_t i,j;
	uint8_t temp_start = 0;
	uint8_t humi_start = 0;
	uint8_t recv_temp_flag = 0;
	uint8_t recv_humi_flag = 0;
	for(i=0; i<ROTONIC_VALID_DATA_LEN; i++)
	{
		if((recv_buff[i] == '%') && (i < 22))//the humidity pos,'%'
		{
			if(recv_buff[i-1] == 0x3B)  //the ';'
			{
				humi_start = i-7;
				for(j=0;j<6;j++)
				{
					rotonic_humi_data[j] = recv_buff[humi_start++];
				}
				recv_humi_flag = 1;
				break;
			}
		}
		
	}
	for(; i < ROTONIC_VALID_DATA_LEN; i++)
	{
		if(recv_buff[i] == 0x43)
		{
			if(recv_buff[i-1] == 0xb0)
			{
				temp_start = i-8;
				for(j=0;j<6;j++)
				{
					rotonic_temp_data[j]= recv_buff[temp_start++];
				}
				recv_temp_flag = 1;
				break;
			}
		}
	}
	if(recv_humi_flag)
	{
    uint8_t hum_flg;		
		recv_humi_flag = 0;
		asc_toflaot(rotonic_humi_data,6,&rotonic_humi_integer,&rotonic_humi_decimal,&hum_flg);		
		humiData = rotonic_humi_integer+rotonic_humi_decimal/100.0;
	}
	if(recv_temp_flag)
	{
		recv_temp_flag = 0;
		asc_toflaot(rotonic_temp_data,6,&rotonic_temp_integer,&rotonic_temp_decimal,&rotonic_temp_sign);
		tempData = rotonic_temp_integer+rotonic_temp_decimal/100.0;
		if(rotonic_temp_sign == 1)
		{
			tempData = -1*tempData;
		}
	}
}


void asc_toflaot(uint8_t *buf,uint8_t size,uint8_t *integer,uint8_t *decil,uint8_t *sig)
{
	uint8_t i=0;
  *integer = 0;
	*decil =0;
	*sig =0;
  for(i=0;i<size;i++)
	{
		if(buf[i] == '-')
		{
			*sig = 1;
		}
		else if(buf[i] == '+')
		{
			*sig = 0;
		}
		else if(buf[i] == 0x20)
		{
			continue;
		}
		else if(buf[i]>='0' &&buf[i]<='9')
		{
			*(integer )=(*integer)*10+ buf[i]-0x30;
		}	
    else if(buf[i] == '.')
		{
			break;
		}			
	}
	if(i>= size-1)
	{
		return;
	}
	for(;i<size;i++)
	{
		if(buf[i] == 0x20)
		{
			continue;
		}
		else if(buf[i]>='0' &&buf[i]<='9')
		{
			*decil =(*decil)*10+ buf[i]-0x30;
		}	
	}
}

bool rotonic_check(uint8_t *buf,uint8_t size)
{
	uint8_t checkSum=0;
	uint8_t i=0;
	for(i=0;i<size;i++)
	{
		checkSum += buf[i];
	}
	checkSum = checkSum%64+32;
	if(checkSum == buf[i])
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool data_check(uint8_t cnt)
{
	char i;
	tempBuf[cnt]=tempData;
	humiBuf[cnt]=humiData;
	for(i=cnt;i>0;i--)
	{
		if(fabs(tempBuf[cnt]-tempBuf[i-1])<5&&fabs(humiBuf[cnt]-humiBuf[i-1])<15)
		{
			tempBuf [0]=tempBuf[cnt];
			humiBuf [0]=humiBuf[cnt];
			return true;
		}
	}
	return false;
}
#endif

