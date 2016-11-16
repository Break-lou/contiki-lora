#ifndef SHT21_H
#define SHT21_H
#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>


#define SHT21_RESET	0xfe

#define SHT21_I2C_ADDR_W	0X80
#define SHT21_I2C_ADDR_R	0X81
#define SHT21_I2C_ADDR	0X80
#define SHT21_STATUS_REG_W 0xe6   
#define SHT21_STATUS_REG_R 0xe7   

#define SHT21_MEASURE_TEMP_CMD	0XF3
#define SHT21_MEASURE_HUMI_CMD	0XF5

uint8_t sht21_softreset(void);

uint8_t sht21_read_statusreg(uint8_t *p_value);

uint8_t sht21_write_statusreg(uint8_t value);
							   
uint8_t sht21_read_sample(uint8_t *p_value, uint8_t *p_checksum);

void sht21_trigger_humi_measure(void);

void sht21_trigger_temp_measure(void);

uint16_t sht21_sample_temp(void);

uint16_t sht21_sample_humi(void);

void sht2x_test(void);


#endif


