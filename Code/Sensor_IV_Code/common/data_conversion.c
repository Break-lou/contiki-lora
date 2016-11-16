#include "data_conversion.h"



void ascii_to_hex_in_order(uint8_t *dest, uint8_t dest_len, uint8_t *src, uint8_t src_len)
{
	uint32_t value = 0;
	uint8_t i = 0;
    
	while(src_len--)
	{
        value <<= 4;
		if(src[i] <= '9')
		{
			value += (src[i]-'0');
		}
		else if(((src[i] >= 'A')&&(src[i] <= 'F')))
		{
			value += (src[i] - 'A' + 0X0A);
		}
		else if(((src[i] >= 'a')&&(src[i] <= 'f')))
		{
			value += (src[i] - 'a' + 0x0A);
		}
		
		i++;
	}
	for(i = 0; i < dest_len; i++)
	{
		dest[i] = ((uint8_t *)(&value))[i];
	}	
}
uint8_t ascii_to_hex(uint8_t *dest, uint8_t *src, uint8_t src_len)
{
	uint8_t i=0,num=0,len;
	uint8_t data[30];
	len=src_len;
	//³ýÈ¥¿Õ¸ñ
	while(len--)
	{
		if(((src[i] <= '9')&&(src[i] >= '0'))||((src[i] >= 'A')&&(src[i] <= 'F'))||((src[i] >= 'a')&&(src[i] <= 'f')))
		{
			data[num]=src[i];
			num++;
		}   
		i++;
	}
	src_len=num;
	
	if(src_len%2)
	{
		return 0;
	}
	for(uint8_t i=0;i<(src_len/2);i++) 
	{
		ascii_to_hex_in_order(dest+i,1,data+(i*2),2);
	}
	return 1;
}
void hex_to_ascii_in_reverse(uint32_t value, uint8_t *buff, uint8_t *len)
{
	*len = 0;
	while(value)
	{
		*buff = (value&0x0000000f);
		if(*buff >= 0x0A)
		{
			*buff = (*buff-0x0A) + 'A';
		}
		else
		{
			*buff += '0';
		}
		buff++;
		*len += 1;
		value >>= 4;
	}
	if(*len == 0)
	{
		*buff = 0+'0';
		*len += 1;
	}	
}

void hex_to_ascii_in_order(uint32_t value, uint8_t *buff, uint8_t *len)
{
	uint8_t i;
	uint8_t temp;
	hex_to_ascii_in_reverse(value, buff, len);
	for(i = 0; i < (*len)/2; i++)
	{
		temp = buff[i];
		buff[i] = buff[*len-1-i];
		buff[*len-1-i] = temp;
	}
}

void dec_to_ascii_in_reverse(uint32_t value, uint8_t *buff, uint8_t *len)
{
	*len = 0;
	while(value)
	{
		*buff = value%10;
		*buff += '0';
		buff++;
		*len += 1;
		value /= 10;
	}
	if(*len == 0)
	{
		*buff = 0+'0';
		*len += 1;
	}
}

void dec_to_ascii_in_order(uint32_t value, uint8_t *buff, uint8_t *len)
{
	uint8_t i;
	uint8_t temp;
	dec_to_ascii_in_reverse(value, buff, len);
	for(i = 0; i < (*len)/2; i++)
	{
		temp = buff[i];
		buff[i] = buff[*len-1-i];
		buff[*len-1-i] = temp;
	}
}

void ascii_to_dec_in_order(uint8_t *dest, uint8_t dest_len, uint8_t *src, uint8_t src_len)
{
	uint32_t value = 0;
	uint8_t i = 0;
	while(src_len--)
	{
		value *= 10;
		value += (src[i++] - '0');
	}
	for(i=0; i<dest_len; i++)
	{
		dest[i] = ((uint8_t *)(&value))[i];
	}
}
