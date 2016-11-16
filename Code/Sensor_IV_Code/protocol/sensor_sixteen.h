#ifndef __SENSOR_SIXTEEN_H__
#define __SENSOR_SIXTEEN_H__


#include <si32_device.h>

#define SENSOR_SIXTEEN_RING_NUM 20

//传感器数据包(16字节)基本结构
typedef struct BASIC_SENSOR_SIXTEEN_P_t
{
	uint8_t jump:4;
	uint8_t type:4;
	uint8_t data_type;
	uint16_t node_id;
	uint32_t timestamp;
	uint8_t value[7];
	uint8_t power;
}BASIC_SENSOR_SIXTEEN_P;
//联合（优势在于共享内存，方便获取16字节）
union BASIC_SENSOR_SIXTEEN_UNION
{
	BASIC_SENSOR_SIXTEEN_P basic_sensor_sp;
	uint8_t data[16];						//共用16字节内存
};
//16字节传感器数据包联合结构体
struct SENSOR_SIXTEEN_RING_t
{
	union BASIC_SENSOR_SIXTEEN_UNION bssu[SENSOR_SIXTEEN_RING_NUM];	//
	uint8_t num;				//表示大小
	uint8_t put_ptr, get_ptr;
};



void sensor_sixteen_buffer_init(void);
int sensor_sixteen_buffer_put(uint8_t type, uint8_t data_type, uint16_t node_id, uint8_t *data, uint8_t size, uint8_t power, uint32_t sample_time);
union BASIC_SENSOR_SIXTEEN_UNION sensor_sixteen_buffer_get(void);
int sensor_sixteen_buffer_size(void);
int sensor_sixteen_buffer_elements(void);

void save_sixteen_data(void);
void save_temp_save_sixteen_data(uint8_t *data,uint8_t num);
#endif
