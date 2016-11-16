#ifndef __CO2_H__
#define __CO2_H__


#include <si32_device.h>




int co2_param_init(void);
void open_sensor_power(void);
void close_sensor_power(void);
uint8_t set_co2_mode2(void);
void co2_analyster(uint8_t data);
uint16_t get_co2_data(void);
int co2_sample_data(void);
uint8_t co2_calibrate(void);
uint8_t check_calibration_result(void);



#endif
