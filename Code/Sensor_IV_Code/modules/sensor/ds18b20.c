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

	// ��ʼ����������
	id_bit_number = 1;
	last_zero = 0;
	rom_byte_number = 0;
	rom_byte_mask = 1;

	// �����ǰ�����Ĳ������һ������
	if (!LastDeviceFlag)
	{
		ds18b20_bus_reset();
		// Delay_ms(1);
		//Init_DS18B20();              		 //��ʼ��
		delay_Xus(1000);
		// ������������
		// OWWriteByte(0xF0);
		ds18b20_bus_write_byte(0xf0);
		// ѭ����������
		do
		{
			// �ӵ������϶�ȡ������ROM�뵱ǰλ�Լ����Ĳ���
			id_bit = ds18b20_bus_read_bit();
			cmp_id_bit = ds18b20_bus_read_bit();
			// ��鵥�������Ƿ��������
			if ((id_bit == 1) && (cmp_id_bit == 1))
				break;
			else
			{
				if (id_bit != cmp_id_bit)      // �����λ��ֵ����ͬ���������ĵ�ǰλ����ͬ
					search_direction = id_bit;  // ��ROM�ĵ�ǰλ������������ָ�룬����֮���·��ѡ��
				else
				{
					// ��������ĵ�ǰλ����һ�γ���λֵ�����λ����ôѡ����������һ��������ǰλʱ��ͬ��·��
					if (id_bit_number < LastDiscrepancy)
						search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
					else
						// ���������ȣ����ȡ��1��·�������ǰ�ߴ��ں��ߣ���ѡȡ��0��
						search_direction = (id_bit_number == LastDiscrepancy);
					// ���ѡȡ�ˡ�0��·��������Lastzero�з��õ�λ
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
		}while(rom_byte_number < 8);  // ������������ֱ������64λROM��ȫ����������
		
		if (!(id_bit_number < 65))
		{
			// search successful so set LastDiscrepancy,LastDeviceFlag,search_result
			LastDiscrepancy = last_zero;
			// �������������һ������
			if (LastDiscrepancy == 0)
				LastDeviceFlag = true;

			search_result = true;
		}
	}

	// ���û����������⵽����λ������ʹ����һ��������������ܹ�����ִ�������ڵ�һ�������Ĺ���
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
    //����ת������
		if(ds18b20_bus_reset())
		{}
//		return -1;
		ds18b20_bus_write_byte(DS18B20_SKIP_ROM); //���Ե�ַƥ��,������ֻ��һ������ʱ,�������������������
		ds18b20_bus_write_byte(DS18B20_CONVERT_TEM);//��ʼת������
    //�ȴ�ת�����,ds18b20Ĭ��ת������Ϊ12λ,��ʱ���ת��ʱ��Ϊ750ms

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
    ds18b20_bus_write_byte(DS18B20_READ_RAM); //��RAM����
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


//����DS18B20�ж����¶��ֽ�,����ʵ���¶�ֵ
uint16_t ds18b20_calc_temperature(uint8_t *t)
{
    uint16_t tmp=(t[1]*256)+t[0];
    uint8_t sflag=0;

    if((t[1]&0xf8)==0xf8) //�����¶�,�Ӳ���ת��(ȡ����һ)
    {
        sflag=1;
        tmp=~tmp;
        tmp++;
    }
    tmp&=0x07ff;    //ȷ��ǰ5λΪ0
    if(sflag) 
		tmp|=0x8000;//�为��
    return tmp;
}


int ds18b20_read_temp( uint8_t *address , uint8_t *t )
{
    uint8_t i;
		//���¶��ֽ�
    if(ds18b20_bus_reset())
		{}
//		return -1;
    ds18b20_bus_write_byte(DS18B20_MATCH_ROM); //��ʼ��ַƥ��
    for(i=0;i<8;i++)                //д������
    {
    	ds18b20_bus_write_byte(*address++);
    }
    ds18b20_bus_write_byte(DS18B20_READ_RAM); //��RAM����
    t[0]=ds18b20_bus_read_byte();
    t[1]=ds18b20_bus_read_byte();
	return 0;
}
#endif


