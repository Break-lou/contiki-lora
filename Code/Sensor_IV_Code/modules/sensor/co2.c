#include "co2.h"
#include "board_cfg.h"
#include "serial.h"
#include "delay.h"

#define CO2_MODE_CMD_LEN 5
#define CO2_Z_COMMAND_CMD_LEN 3
#define CO2_X_COMMAND_CMD_LEN 7
#define UART_RECV_BUFF_LEN 20
//3个CO2模式指令
uint8_t set_mode0[5] = {0x4b,0x20,0x30,0x0d,0x0a};
uint8_t set_mode1[5] = {0x4b,0x20,0x31,0x0d,0x0a};
uint8_t set_mode2[5] = {0x4b,0x20,0x32,0x0d,0x0a};
//Z COMMAND
uint8_t Z_command[CO2_Z_COMMAND_CMD_LEN] = {0x5a,0x0d,0x0a};
uint8_t X_command[] = {'X',' ','4','0','0',0X0D,0X0A};
//Q COMMAND
uint8_t Q_command[3] = {0x51,0x0d,0x0a};
//Y COMMAND
uint8_t Y_command[3] = {0x59,0x0d,0x0a};
//G COMMAND
uint8_t G_command[3] = {0x47,0x0d,0x0a};
//CO2电源端口PB3.3
#define SENSOR_POWER_PORT SI32_PBSTD_3
#define SENSOR_POWER_PIN  0x08
//CO2串口设置
#define CO2_SERIAL_PORT 	SERIAL_PORT_UART0
#define CO2_SERIAL_BAUD 	serial_baudrate_9600
//CO2接收缓存
uint8_t co2_recv_buff[UART_RECV_BUFF_LEN];
uint8_t co2_recv_cnt = 0;

serial_paras_t co2_uart_paras; 

void clear_co2_recv_buff(void);

int co2_param_init(void)
{
	int ret = 0;
	//对应的串口端口配置
	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, UART0_RX_PIN);
	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, UART0_TX_PIN);
	//CO2电源端口配置
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	//CO2对应的串口初始化
	co2_uart_paras.duplex_mode			= serial_full_duplex_mode;
	co2_uart_paras.startbits			= serial_has_startbits;
	co2_uart_paras.tx_idlestate			= serial_tx_idle_high_state;
	co2_uart_paras.rx_idlestate			= serial_rx_idle_high_state;
	co2_uart_paras.rx_fifo_threshold	= serial_rx_fifo_threshold_one_byte;
	co2_uart_paras.baudrate 			= CO2_SERIAL_BAUD;
	co2_uart_paras.wordlength 			= serial_wordlength_8bit;
	co2_uart_paras.parity 				= serial_parity_none;
	co2_uart_paras.stopbits 			= serial_stopbits_1;
	if (serial_configuration(CO2_SERIAL_PORT, &co2_uart_paras))
		ret = -1;

	return ret;
}
//打开CO2电源
void open_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_high(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
//关闭CO2电源
void close_sensor_power(void)
{
	SI32_PBSTD_A_set_pins_push_pull_output(SENSOR_POWER_PORT, SENSOR_POWER_PIN);
	SI32_PBSTD_A_write_pins_low(SENSOR_POWER_PORT,SENSOR_POWER_PIN);
}
//设置CO2传感器模式为模式2
uint8_t set_co2_mode2(void)
{
	//发送命令
	serial_tramsmit_bytes(CO2_SERIAL_PORT, set_mode2, CO2_MODE_CMD_LEN);
	//等待
	delayXms(20);
	//判断
	if(co2_recv_buff[1] == 'K' && co2_recv_buff[7] == '2')
	{
		//设置成功
		clear_co2_recv_buff();
		return 1;
	}else{
		//设置失败
		clear_co2_recv_buff();
		return 0;
	}
}
//发送传感器采集命令
int co2_sample_data(void)
{
	serial_tramsmit_bytes(CO2_SERIAL_PORT, Z_command, CO2_Z_COMMAND_CMD_LEN);		
	
    return 0;
}
//发送标定指令
uint8_t co2_calibrate(void)
{
	serial_tramsmit_bytes(CO2_SERIAL_PORT, X_command, CO2_X_COMMAND_CMD_LEN);	
	return 0;
}
//CO2传感器的指令结尾都是\r\n
void co2_analyster(uint8_t data)
{
	co2_recv_buff[co2_recv_cnt] = data;
	co2_recv_cnt++;
	if(co2_recv_cnt >= UART_RECV_BUFF_LEN)
	{
		co2_recv_cnt = 0;
	}
}
//计算CO2传感器数据
uint16_t get_co2_data(void)
{
	uint16_t co2_data;
	if(co2_recv_cnt < 8)
	{
		co2_data = 0xFFFF;
	}else{
		co2_data = (co2_recv_buff[3]-'0')*10000+(co2_recv_buff[4]-'0')*1000+(co2_recv_buff[5]-'0')*100
				            +(co2_recv_buff[6]-'0')*10+(co2_recv_buff[7]-'0');
	}
	clear_co2_recv_buff();
	return co2_data;
}
//清空缓存
void clear_co2_recv_buff(void)
{
	co2_recv_cnt = 0;
	memset(co2_recv_buff, 0x00, UART_RECV_BUFF_LEN);
}
//判断标定返回
uint8_t check_calibration_result(void)
{
	if(co2_recv_buff[1] == 'X')
	{
		clear_co2_recv_buff();
		return 1;
	}else{
		clear_co2_recv_buff();
		return 0;
	}
}


