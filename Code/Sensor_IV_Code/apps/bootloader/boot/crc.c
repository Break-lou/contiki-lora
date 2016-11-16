#include <crc.h>

uint16_t crc_compute(uint8_t *buf, uint16_t size,uint16_t initialValue,uint8_t isLast)
{
	uint16_t index, crc;
	uint8_t v, xor_flag, byte, bit;

	crc = initialValue;
	for(index = 0; index < size; index++) 
	{
		byte = buf[index];
		v = 0x80;
		for(bit = 0; bit < 8; bit++) 
		{
			if(crc & 0x8000)
				xor_flag= 1;
			else
				xor_flag= 0;

			crc = crc << 1;

			if(byte & v)
			crc= crc + 1;

			if(xor_flag)
				crc = crc ^ POLY;
			v = v >> 1;
		}
	}

	if(isLast)
	{
		for(bit = 0; bit < 16; bit++) 
		{
			if(crc & 0x8000)
				xor_flag= 1;
			else
				xor_flag= 0;

			crc = crc << 1;

			if(xor_flag)
				crc = crc ^ POLY;
		}
	}
	return crc;
}

