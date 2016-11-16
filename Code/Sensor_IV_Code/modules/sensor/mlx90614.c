#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>
#include "simulate_i2c.h"
#include "mlx90614.h"
#include "delay.h"
#if MLX90614_OPERATE
//#define mlx90614_iir 0x00

//#define mlx90614_obj 0
//#define mlx90614_single_dual 1

//#define mlx90614_fir 0x07
//#define mlx90614_gain 5
//#define mlx90614_enable 0


uint8_t mlx90614_iir = 0x04;

uint8_t mlx90614_obj = 0;
uint8_t mlx90614_single_dual = 0;

uint8_t mlx90614_fir = 0x07;
uint8_t mlx90614_gain = 5;
uint8_t mlx90614_enable = 0;

uint16_t mlx90614_temp, mlx90614_humi;
uint16_t mlx90614_temp_data;
uint8_t mlx90614_checksum;
uint16_t POLYNOMIAL = 0x107; //P(x)=x^8+x^5+x^4+1 = 100000111
uint8_t config_buff[5];
uint8_t clear_eeprom[5];	

int mlx90614_init_config(void)
{	
	
	config_buff[0] = MLX90614_I2C_ADDR_W;
	config_buff[1] = 0x20|0x05;
	config_buff[2] = mlx90614_iir | (0<<3) | (mlx90614_obj<<4) | (mlx90614_single_dual<<6) | (0<<7);//1.5Ãë
	
	config_buff[3] = mlx90614_fir | (mlx90614_gain<<3) | (0<<6) | (mlx90614_enable<<7);
	config_buff[4] = mlx90614_CheckCrc(config_buff,4);
	
	clear_eeprom[0] = MLX90614_I2C_ADDR_W;
	clear_eeprom[1] = config_buff[1];
	clear_eeprom[2] = 0;
	clear_eeprom[3] = 0;
	clear_eeprom[4] = mlx90614_CheckCrc(clear_eeprom,4);

	//mlx90614_trigger_temp_measure();
	return 0;
}
uint8_t adata[6];
void mlx90614_trigger_temp_measure(void)
{
	
	mlx90614_sample_temp(0x25,adata);
	if((adata[3] == config_buff[2]) && (adata[4] == config_buff[3]))
	{
		return;
	}
	simulate_i2c_write_bytes(clear_eeprom, 5);	
	delayXms(50);
	simulate_i2c_write_bytes(config_buff, 5);
}
//????
uint8_t mlx90614_sample_temp(uint8_t adr, uint8_t *buff)
{
	uint8_t cnt=0;
	buff[0] = MLX90614_I2C_ADDR_W;
	buff[1] = adr;
	buff[2] = MLX90614_I2C_ADDR_R;
	sample_again:
	if(simulate_i2c_read_buff_from_addr(buff[0],buff[1],buff+3, 3))
	{
		cnt++;
		if(cnt<3)
		{
			goto sample_again;
		}
	}
	if(buff[5] == mlx90614_CheckCrc(buff,5))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
uint8_t mlx90614_CheckCrc(uint8_t* data, uint8_t nbrOfBytes)
{
		uint8_t crc = 0;
		uint8_t byteCtr;
		//calculates 8-Bit checksum with given polynomial
		for (byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++)
		{ 
			crc ^= (data[byteCtr]);
			for (uint8_t bit = 8; bit > 0; --bit)
			{ 
				if (crc & 0x80) 
					crc = (crc << 1) ^ POLYNOMIAL;
				else 
					crc = (crc << 1);
			}
		}
		return crc;
}
#endif


