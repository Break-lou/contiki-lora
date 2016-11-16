#include "sensor_sixteen.h"
#include "lib/list.h"
#include "rtc_config.h"
#include "board_cfg.h"
#include "ext_flash_include.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/******************************************************************************

******************************************************************************/

struct SENSOR_SIXTEEN_RING_t sensor_sixteen_ring_t;

/*******************************************************************************
  * @brief sensor_sixteen_buffer_init()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 16字节初始化清零
	 *****************************************************************************
  */
void sensor_sixteen_buffer_init(void)
{
	sensor_sixteen_ring_t.num = 0;
	sensor_sixteen_ring_t.get_ptr = 0;
	sensor_sixteen_ring_t.put_ptr = 0;
	
}
/*******************************************************************************
  * @brief sensor_sixteen_buffer_put()
  * @param  type，data_type，node_id，*data，size，power，sample_time
  * @retval 1,0
	******************************************************************************
	 @attention 采集的传感器数据放入16字节缓存
	 *****************************************************************************
  */
int sensor_sixteen_buffer_put(uint8_t type, uint8_t data_type, uint16_t node_id, uint8_t *data, uint8_t size, uint8_t power, uint32_t sample_time)
{
	if(sensor_sixteen_ring_t.num == (SENSOR_SIXTEEN_RING_NUM-1)) //19条记录
	{
		save_sixteen_data();
		//return 0;
	}
	uint32_t cpu_sr = cpu_sr;
	
	ENTER_CRITICAL_REGION();
	
	sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.type = type;
	sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.jump = 0;
	sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.data_type = data_type;//
	sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.node_id = node_id;
	sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.timestamp = sample_time;
	memcpy(sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.value, data, size);
	sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.put_ptr].basic_sensor_sp.power = power;
	
	sensor_sixteen_ring_t.put_ptr = (sensor_sixteen_ring_t.put_ptr + 1) % SENSOR_SIXTEEN_RING_NUM;
	sensor_sixteen_ring_t.num++;
	
	LEAVE_CRITICAL_REGION();
	
	return 1;
}
/*******************************************************************************
  * @brief sensor_sixteen_buffer_get()
  * @param  
  * @retval temp_union
	******************************************************************************
	 @attention 从16字节缓存中读出数据
	 *****************************************************************************
  */
union BASIC_SENSOR_SIXTEEN_UNION sensor_sixteen_buffer_get()
{
	union BASIC_SENSOR_SIXTEEN_UNION temp_union ;
	
	uint32_t cpu_sr = cpu_sr;
	ENTER_CRITICAL_REGION();
	if(sensor_sixteen_ring_t.num > 0) 
	{
		temp_union = (sensor_sixteen_ring_t.bssu[sensor_sixteen_ring_t.get_ptr]);
		sensor_sixteen_ring_t.get_ptr = (sensor_sixteen_ring_t.get_ptr + 1) % SENSOR_SIXTEEN_RING_NUM;
		sensor_sixteen_ring_t.num--;
	} 
	LEAVE_CRITICAL_REGION(); 
	
	return temp_union;
}
/*******************************************************************************
  * @brief sensor_sixteen_buffer_size()
  * @param  
  * @retval SENSOR_SIXTEEN_RING_NUM
	******************************************************************************
	 @attention 读出缓存总数目
	 *****************************************************************************
  */
int sensor_sixteen_buffer_size(void)
{
	return SENSOR_SIXTEEN_RING_NUM;
}
/*******************************************************************************
  * @brief sensor_sixteen_buffer_elements()
  * @param  
  * @retval num
	******************************************************************************
	 @attention 读出缓存数目
	 *****************************************************************************
  */
int sensor_sixteen_buffer_elements(void)
{
	uint32_t cpu_sr = cpu_sr;
	ENTER_CRITICAL_REGION();
	
	uint8_t num = sensor_sixteen_ring_t.num;
	
	LEAVE_CRITICAL_REGION();
	
	return num;
}
/*******************************************************************************
  * @brief save_sixteen_data()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 缓存数据存入外部FLASH
	 *****************************************************************************
  */
uint8_t temp_data[16];
void save_sixteen_data(void)
{
	uint32_t cpu_sr = cpu_sr;
	
	ENTER_CRITICAL_REGION();
	
	int eles = sensor_sixteen_buffer_elements();
	
	#if DEBUG_PRINT
		printf("sensor data eles = %d \n", eles);
	#endif
	
	if(eles > 0)
	{
		union BASIC_SENSOR_SIXTEEN_UNION temp_union;
		uint8_t i = 0;
		for(i=0; i< eles; i++)
		{
			temp_union = sensor_sixteen_buffer_get();//num--
			if(temp_union.basic_sensor_sp.power != 0x00)
			{
				memcpy(temp_data, temp_union.data, 16);  			//复制16字节数据
				storage_write_data(temp_data, 16);
			}
		}
	}
	
	LEAVE_CRITICAL_REGION();
}









