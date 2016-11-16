#include "ds18b20_include.h"
#if DS18B20_OPERATE
uint8_t ROM_NO[8];
uint8_t LastDiscrepancy;
bool LastDeviceFlag = 0;
uint8_t Devices[MAX_DB18B20_NUM][8];
uint8_t DeviceNum = 0;
extern uint16_t  ds18b20_data;
bool ds18b20_search_bus(void)
{
	int search_result = false;
	uint8_t id_bit_number;
	uint8_t last_zero, rom_byte_number;
	uint8_t id_bit, cmp_id_bit;  //actully, those two variables have only two values: 0 or 1
	uint8_t rom_byte_mask, search_direction;

	// 初始化搜索过程
	id_bit_number = 1;
	last_zero = 0;
	rom_byte_number = 0;
	rom_byte_mask = 1;

	// 如果当前搜索的不是最后一个器件
	if (!LastDeviceFlag)
	{
		ds18b20_bus_reset();
		// Delay_ms(1);
		//Init_DS18B20();              		 //初始化
		delay_Xus(1000);
		// 发送搜索命令
		// OWWriteByte(0xF0);
		ds18b20_bus_write_byte(0xf0);
		// 循环进行搜索
		do
		{
			// 从单总线上读取器件的ROM码当前位以及它的补码
			id_bit = ds18b20_bus_read_bit();
			cmp_id_bit = ds18b20_bus_read_bit();
			// 检查单总线上是否存在器件
			if ((id_bit == 1) && (cmp_id_bit == 1))
				break;
			else
			{
				if (id_bit != cmp_id_bit)      // 如果两位的值不相同，各器件的当前位都相同
					search_direction = id_bit;  // 将ROM的当前位赋给搜索方向指针，用于之后的路径选择
				else
				{
					// 如果搜索的当前位比上一次出现位值差异的位，那么选泽与搜索上一个器件当前位时相同的路径
					if (id_bit_number < LastDiscrepancy)
						search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
					else
						// 如果二者相等，则采取“1”路径，如果前者大于后者，则选取“0”
						search_direction = (id_bit_number == LastDiscrepancy);
					// 如果选取了“0”路径，则在Lastzero中放置当位
					if (search_direction == 0)
					{
						last_zero = id_bit_number;
					}
				}

				// set or clear the bit in the ROM byte rom_byte_number
				// with mask rom_byte_mask
				if (search_direction == 1)
					ROM_NO[rom_byte_number] |= rom_byte_mask;
				else
					ROM_NO[rom_byte_number] &= ~rom_byte_mask;

				// serial number search direction write bit
				ds18b20_bus_write_bit(search_direction);

				// increment the byte counter id_bit_number
				// and shift the mask rom_byte_mask
				id_bit_number++;
				rom_byte_mask <<= 1;

				// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
				if (rom_byte_mask == 0)
				{
				rom_byte_number++;
				rom_byte_mask = 1;
				}
			}
		}while(rom_byte_number < 8);  // 继续搜索过程直到所有64位ROM码全部被搜索完
		
		if (!(id_bit_number < 65))
		{
			// search successful so set LastDiscrepancy,LastDeviceFlag,search_result
			LastDiscrepancy = last_zero;
			// 查找总线上最后一个器件
			if (LastDiscrepancy == 0)
				LastDeviceFlag = true;

			search_result = true;
		}
	}

	// 如果没有器件被检测到，则复位计数器使得下一个搜索命令到来后能够继续执行类似于第一次搜索的过程
	if (!search_result || !ROM_NO[0])
	{
		LastDiscrepancy = 0;
		LastDeviceFlag = false;
		search_result = false;
	}

	return search_result;
}

int ds18b20_initial_convert(void)
{
    //发送转换命令
		if(ds18b20_bus_reset())
		{}
//		return -1;
		ds18b20_bus_write_byte(DS18B20_SKIP_ROM); //忽略地址匹配,总线上只有一个器件时,或对总线所有器件操作
		ds18b20_bus_write_byte(DS18B20_CONVERT_TEM);//开始转换命令
    //等待转换完成,ds18b20默认转换精度为12位,此时最大转换时间为750ms

    return 0;
}
uint8_t calcrc_onebyte(uint8_t byte)
{
	uint8_t i,crc_1byte;     

	crc_1byte=0;                //??crc_1byte???0   

	for(i = 0; i < 8; i++)    
	{    
		if(((crc_1byte^byte)&0x01))    
		{    
			crc_1byte^=0x18;     
			crc_1byte>>=1;    
			crc_1byte|=0x80;    
		}          
		else    
		{			
			crc_1byte>>=1;  
		}			
		byte>>=1;          
	}   
	return crc_1byte; 
}	
uint8_t crc8(uint8_t *data,uint8_t len)
{
	uint8_t crc=0;
	while(len--)
	{
		crc=calcrc_onebyte(crc^*data);
		data++;
	}
	return crc;
}
uint16_t defualt_ds18b20_read_temp( void )
{	
//		uint16_t data=0;
		uint8_t data_check[9];
		if(ds18b20_bus_reset())
		{}
		ds18b20_bus_write_byte(DS18B20_SKIP_ROM);
    ds18b20_bus_write_byte(DS18B20_READ_RAM); //读RAM命令
		for(uint8_t i=0;i<9;i++)
		{
			data_check[i]=ds18b20_bus_read_byte();
		}
		if(data_check[8] ==crc8(data_check,8))
		{
			ds18b20_data=data_check[0]&0xff;
			ds18b20_data+=(data_check[1]&0xff)<<8;
			return 1;	
		}
    else
		{
			return 0;	
		}	
}


//根据DS18B20中读的温度字节,计算实际温度值
uint16_t ds18b20_calc_temperature(uint8_t *t)
{
    uint16_t tmp=(t[1]*256)+t[0];
    uint8_t sflag=0;

    if((t[1]&0xf8)==0xf8) //若负温度,从补码转换(取反加一)
    {
        sflag=1;
        tmp=~tmp;
        tmp++;
    }
    tmp&=0x07ff;    //确保前5位为0
    if(sflag) 
		tmp|=0x8000;//变负数
    return tmp;
}


int ds18b20_read_temp( uint8_t *address , uint8_t *t )
{
    uint8_t i;
		//读温度字节
    if(ds18b20_bus_reset())
		{}
//		return -1;
    ds18b20_bus_write_byte(DS18B20_MATCH_ROM); //开始地址匹配
    for(i=0;i<8;i++)                //写入数据
    {
    	ds18b20_bus_write_byte(*address++);
    }
    ds18b20_bus_write_byte(DS18B20_READ_RAM); //读RAM命令
    t[0]=ds18b20_bus_read_byte();
    t[1]=ds18b20_bus_read_byte();
	return 0;
}
#endif


