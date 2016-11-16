#ifndef SDI12_H_
#define SDI12_H_

#include <stdint.h>
#include <Si32_device.h>
#include <SI32_PBCFG_A_Support.h>
#include <SI32_PBSTD_A_Type.h>
#include "sensor_parameter.h"
#define SDI12_ACKNOWLEDGE_ACTIVE_COMMAND_LEN	2
#define SDI12_INFO_COMMAND_LEN	3
#define SDI12_ADDRESS_QUERY_COMMAND_LEN	2
#define SDI12_MEASURE_COMMAND_LEN	3
#define SDI12_DATA_COMMAND_LEN	4
#define SDI12_CHANGE_ADDRESS_COMMAND_LEN	4
#define SDI12_MEASURE_CRC_COMMAND_LEN	4

#define SDI12_END_STRING_LEN	2
#define SDI12_RECV_BUFF_LEN		24
#define SDI12_BREAK_TIME	16
#define SDI12_MARKING_TIME	9	

extern uint8_t sdi12_recv_buff[SDI12_RECV_BUFF_LEN];

//#define SDI12_USE_USART
#define SDI12_USE_UART


//#define SDI12_BREAK()	UART_PORT_HIGH()
//#define SDI12_MARKING()	UART_PORT_LOW()
//#define SDI12_RELEASE_BUS()	UART_PORT_IN()
#define SDI12_BREAK()	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, 0x0080);\
											SI32_PBSTD_A_write_pins_high(SI32_PBSTD_0, 0x0080)	
#define SDI12_MARKING()	SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, 0x0080);\
												SI32_PBSTD_A_write_pins_low(SI32_PBSTD_0, 0x0080)	
#define SDI12_RELEASE_BUS()	SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, 0x0080|0x0100)

#define UART_TX_OUT() SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, 0x0080)
#define UART_TX_IN()  SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, 0x0080)

#define UART_RX_OUT() SI32_PBSTD_A_set_pins_push_pull_output(SI32_PBSTD_0, 0x0100)
#define UART_RX_IN()  SI32_PBSTD_A_set_pins_digital_input(SI32_PBSTD_0, 0x0100)

#define UART_PORT_IN()		UART_TX_IN();\
													UART_RX_IN()
typedef struct {
	uint8_t time;
	uint8_t num;
} measure_type;
	
typedef struct {
	uint8_t dp1;
	uint8_t dp1_num;
	uint32_t dielectric;//电导率
	uint8_t dp2;
	uint8_t dp2_num;
	uint16_t Temperature;//温度
	uint8_t dp3;
	uint8_t dp3_num;
	uint32_t humidity;//湿度
	uint8_t FLAG_5TE_OR_5TM;
} sdi_data_type;
	

//#define sdi12_address_valid(x)
extern uint8_t sdi12_timeout_flag;

extern uint8_t sdi12_info_command[];
extern uint8_t sdi12_address_query_command[] ;
extern uint8_t sdi12_measure_command[] ;
extern uint8_t sdi12_data_command[];
extern uint8_t sdi12_change_address_command[] ;
extern uint8_t sdi12_acknowledge_active_command[];
extern uint8_t sdi12_measure_crc_command[] ;
extern uint8_t sdi12_end_string[] ;
extern uint8_t sdi12_recv_buff[];
extern uint8_t sdi12_recv_len ;
void sdi12_param_init(void);

void s_5tm_uart_enable_wake_event(void);

void s_5tm_uart_disable_wake_event(void);

void sdi12_enable_tx_crossbar(void);

void sdi12_enable_rx_crossbar(void);

void sdi12_enable_crossbar(void);

void sdi12_disable_crossbar(void);

uint8_t sdi12_analyster(uint8_t data);
uint8_t sdi12_receive(uint8_t data);
void sdi12_break(void);

void sdi12_marking(void);

measure_type sdi12_measure_response(uint8_t *data);

uint8_t sdi12_data_receive(measure_type data);
sdi_data_type sdi12_data_response(uint8_t* data);
void sdi12_send_command(uint8_t addr, uint8_t *cmd, uint8_t len);

int sdi12_recv_response(uint8_t *recv_buff, uint8_t *len, uint32_t time);

uint8_t sdi12_query_address(void);
uint8_t sdi12_address_response(uint8_t *data);
uint8_t sdi12_measure(void);
uint8_t sdi12_analyster(uint8_t data);

uint8_t acsii_to_number(uint8_t data);
uint8_t sdi12_change_address(uint8_t src_addr, uint8_t dest_addr);

int sdi12_is_sensor_active(uint8_t addr);

#endif

