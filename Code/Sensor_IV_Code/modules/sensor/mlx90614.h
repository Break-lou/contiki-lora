#ifndef MLX90614_H
#define MLX90614_H
#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>
#include "board_cfg.h"

//#define MLX90614_RESET	0xfe

#define MLX90614_I2C_ADDR_W	0x00//0XB4
#define MLX90614_I2C_ADDR_R	0x01//0XB5
#define MLX90614_I2C_ADDR	0x00//0XB4
#define MLX90614_RAM_ADRESS 0X00
#define MLX90614_EEPROM_ADRESS 0X20
#define MLX90614_SLEEP 0xFF
#define MLX90614_READ_FLAGS 0xF0
//#define MLX90614_STATUS_REG_W 0xe6   
//#define MLX90614_STATUS_REG_R 0xe7   

//#define MLX90614_MEASURE_TEMP_CMD	0XF3
//#define MLX90614_MEASURE_HUMI_CMD	0XF5
#if MLX90614_OPERATE
typedef enum{
ACK_ERROR = 0x01,
TIME_OUT_ERROR = 0x02,
CHECKSUM_ERROR = 0x04,
UNIT_ERROR = 0x08
}etError;

int mlx90614_init_config(void);			   

void mlx90614_trigger_temp_measure(void);

uint8_t mlx90614_sample_temp(uint8_t adr, uint8_t *buff);

uint16_t mlx90614_sample_humi(void);
uint8_t mlx90614_CheckCrc(uint8_t* data, uint8_t nbrOfBytes);
//void sht2x_test(void);


#endif
#endif

