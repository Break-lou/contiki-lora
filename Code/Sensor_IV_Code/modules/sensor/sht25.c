#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>
#include "simulate_i2c.h"
#include "sht25.h"

uint16_t sht21_temp, sht21_humi;
uint16_t sht21_temp_data;
uint8_t sht21_checksum;

uint8_t sht21_softreset(void)
{ 
	uint8_t error=0;  
	simulate_i2c_write_cmd(SHT21_I2C_ADDR, SHT21_RESET);
	return error;                    
}

uint8_t sht21_read_statusreg(uint8_t *p_value)
{ 
	uint8_t error=0;
	simulate_i2c_read_value_from_addr(SHT21_I2C_ADDR, SHT21_STATUS_REG_R, p_value);
	
	return error;                    
}

uint8_t sht21_write_statusreg(uint8_t value)
{ 
	uint8_t error=0;
	uint8_t read_value;
	sht21_read_statusreg(&read_value);
	value &= ~(0x31);
	read_value &= (0x31);
	value |= read_value;
	simulate_i2c_write_value_to_addr(SHT21_I2C_ADDR, SHT21_STATUS_REG_W, value);
	return error;                   
}

uint8_t tt_buff[3];
							   
uint8_t sht21_read_sample(uint8_t *p_value, uint8_t *p_checksum)
{
	uint8_t error=0;
	simulate_i2c_read_mult_byte(SHT21_I2C_ADDR, tt_buff, 3);
	*p_value = tt_buff[1];
	*(p_value+1) = tt_buff[0];
	*p_checksum = tt_buff[2];
	return error;
}

int sht21_initial_sample(void)
{	
	sht21_trigger_temp_measure();
	return 0;
}

//触发湿度采集
void sht21_trigger_humi_measure(void)
{
	simulate_i2c_write_cmd(SHT21_I2C_ADDR, SHT21_MEASURE_HUMI_CMD);	
}
//触发温度采集
void sht21_trigger_temp_measure(void)
{
	simulate_i2c_write_cmd(SHT21_I2C_ADDR, SHT21_MEASURE_TEMP_CMD);	
}
//采集温度
uint16_t sht21_sample_temp(void)
{
	sht21_read_sample((uint8_t *)(&sht21_temp_data), &sht21_checksum);
	sht21_temp = (sht21_temp_data&(~(uint16_t)(0x03)));

	return sht21_temp;
}
//采集湿度
uint16_t sht21_sample_humi(void)
{
	sht21_read_sample((uint8_t *)(&sht21_temp_data), &sht21_checksum);
	sht21_humi = (sht21_temp_data&(~(uint16_t)(0x03)));
	
	return sht21_humi;
}




