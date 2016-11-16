#include <stdint.h>
#include "crc.h"

uint16_t crc_ccitt_update(uint16_t crc, uint8_t data) 
{
	data ^= (uint8_t)(crc);
	data ^= data << 4;

	return ((((uint16_t) data << 8) | (crc >> 8)) ^ (uint8_t) (data >> 4) ^ ((uint16_t) data << 3));
}

/** @brief crc-ccitt truncated polynomial. */
#define POLY 0x1021          
/** @brief crc-ccitt initial value. */


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

unsigned short crc16_add(unsigned char b, unsigned short acc,uint16_t crc_style_t)
{
  /*
    acc  = (unsigned char)(acc >> 8) | (acc << 8);
    acc ^= b;
    acc ^= (unsigned char)(acc & 0xff) >> 4;
    acc ^= (acc << 8) << 4;
    acc ^= ((acc & 0xff) << 4) << 1;
  */
	uint8_t i=0,num;
  acc ^= b;
	
	for(i=0;i<8;i++)
	{
			num=acc%2;
			acc  = acc>>1;
			if(num==1)
				acc^=crc_style_t;	
								
			
	}
  return acc;
}
/*---------------------------------------------------------------------------*/
//CRC多项式:0XA001
//aac=0xffff
uint16_t crc16_ibm_generate(uint8_t *buffer, uint16_t len,uint16_t acc,uint16_t crc_style_value)
{
		uint16_t crc=acc;
		uint8_t i;
		uint8_t crc_l,crc_h;
		for(i=0;i<len;i++)
		{
				crc = crc16_add(*buffer, crc, crc_style_value);
				buffer++;
		}
		crc_l=crc/256;
		crc_h=crc%256;
		crc=crc_l+crc_h*256;
		return crc;
}
uint8_t check_bcc(uint8_t* data,uint8_t len)
{
		uint8_t check=0;
		uint8_t i;
		for(i=0;i<len;i++)
		{
				check ^= data[i];
		}
		i=check&0xff;
		return i;
}
uint8_t lrc_generate(uint8_t* data,uint8_t length)
{
		uint8_t i;     
		uint8_t result; 	
		uint16_t lrcdata=0; 
		for(i=0;i<length;i++)  
		{   
				 lrcdata+=data[i];
		}     
		lrcdata=~lrcdata;
		lrcdata++;
		result=lrcdata; 
		return result;
}
uint8_t modbus_checksum(uint8_t* data,uint8_t len)
{
		uint16_t check=0;
		uint8_t i;
		for(i=0;i<len;i++)
		{
				check += data[i];
		}
		i=check&0xff;
		return i;
}
//                                     数据	 数据长度   CRC校验起始值         校验类型							校验类型标准
uint16_t modbus_check_generate(uint8_t *data,uint8_t len,uint16_t acc,uint16_t check_style,uint16_t check_style_value)
{
	uint16_t check;
	if(check_style==modbus_check_style_crc)
	{
		check=crc16_ibm_generate(data,len,acc,check_style_value);
	}
	else if(check_style==modbus_check_style_lrc)
	{
		check=lrc_generate(data,len);
	}
	else if(check_style==modbus_check_style_bcc)	
	{
		check=check_bcc(data,len);
	}
	else if(check_style==modbus_check_style_sum)
	{
		check=modbus_checksum(data,len);
	}
	return check;
}	











