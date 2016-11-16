#include "simulate_i2c.h"

extern void delay_Xus(uint32_t cnt);
/*******************************************************************************
  * @brief simulate_i2c_port_off()
  * @param  
  * @retval 
	******************************************************************************
	 @attention SCL,SCL输出拉低
	 *****************************************************************************
  */
void simulate_i2c_port_off(void)
{
	SIMULATE_I2C_SCK_OUT;
	SIMULATE_I2C_SCK_LOW;
	SIMULATE_I2C_DATA_OUT;
	SIMULATE_I2C_DATA_LOW;
}
/*******************************************************************************
  * @brief simulate_i2c_week()
  * @param  
  * @retval 
	******************************************************************************
	 @attention 
	//       ____       __     
	// DATA:     |_____|
	//            ________   
	// SCK : ____|   
	 *****************************************************************************
  */
void simulate_i2c_week(void)
{
	SIMULATE_I2C_SCK_OUT;
	SIMULATE_I2C_DATA_OUT;
	SIMULATE_I2C_SCK_LOW;
	SIMULATE_I2C_DATA_HIGH;
	delayXms(30);
	SIMULATE_I2C_SCK_HIGH;
	SIMULATE_I2C_DATA_LOW;
	
	delayXms(35);
	SIMULATE_I2C_DATA_HIGH;
	delayXms(30);
}

/*******************************************************************************
  * @brief simulate_i2c_transstart()
  * @param  
  * @retval 
	******************************************************************************
	 @attention I2C start 
	//       _____         
	// DATA:      |_______
	//          _____       
	// SCK : __|		 |_____
	 *****************************************************************************
  */
void simulate_i2c_transstart(void)
{                

	SIMULATE_I2C_SCK_OUT;
	SIMULATE_I2C_DATA_OUT;
	SIMULATE_I2C_SCK_LOW;                   //Initial state
	delay_simulate_i2c_half();
	SIMULATE_I2C_DATA_HIGH;
	delay_simulate_i2c_all();
	SIMULATE_I2C_SCK_HIGH;
	delay_simulate_i2c_all();
	SIMULATE_I2C_DATA_LOW;
	delay_simulate_i2c_all();

	SIMULATE_I2C_SCK_LOW;
	delay_simulate_i2c_all();

}

/*******************************************************************************
  * @brief simulate_i2c_retransstart()
  * @param  
  * @retval 
	******************************************************************************
	 @attention I2C start 
	//       _____         
	// DATA:      |_______
	//       _______     
	// SCK : 		    |_____
	 *****************************************************************************
  */
void simulate_i2c_retransstart(void)
{                
	SIMULATE_I2C_SCK_OUT;
	SIMULATE_I2C_DATA_OUT;
	SIMULATE_I2C_DATA_HIGH;
	delay_simulate_i2c_all();
	SIMULATE_I2C_SCK_HIGH;
	delay_simulate_i2c_all();
	SIMULATE_I2C_DATA_LOW;
	delay_simulate_i2c_all();

	SIMULATE_I2C_SCK_LOW;
	delay_simulate_i2c_all();

}

/*******************************************************************************
  * @brief simulate_i2c_transstop()
  * @param  
  * @retval 
	******************************************************************************
	 @attention I2C stop 
	//               ______
	// DATA: _______| 
	//             ________
	// SCK : _____|
	 *****************************************************************************
  */
void simulate_i2c_transstop(void)
{                          
	SIMULATE_I2C_SCK_OUT;
	SIMULATE_I2C_DATA_OUT;
	SIMULATE_I2C_SCK_LOW;
	SIMULATE_I2C_DATA_LOW;
	delay_simulate_i2c_all();
	SIMULATE_I2C_SCK_HIGH;
	delay_simulate_i2c_all();
	SIMULATE_I2C_DATA_HIGH;
	delay_simulate_i2c_all();
//	SIMULATE_I2C_SCK_LOW;
//	delay_simulate_i2c_all();
}

/*******************************************************************************
  * @brief simulate_i2c_write_byte()
  * @param  value
  * @retval error
	******************************************************************************
	 @attention I2C 写单字节 从高位到低位
							error：1未成功
										 0成功
	 *****************************************************************************
  */
uint8_t simulate_i2c_write_byte(uint8_t value)
{ 
	uint8_t i,error=0;  
	for (i=0x80;i>0;i >>= 1)             //shift bit for masking
	{ 
		if (i & value) 
		{
			SIMULATE_I2C_DATA_HIGH;          //masking value with i , write to SENSI-BUS
		}
		else 
		{
			SIMULATE_I2C_DATA_LOW;  
		}			
		delay_simulate_i2c_half();
		SIMULATE_I2C_SCK_HIGH;                          //clk for SENSI-BUS
		delay_simulate_i2c_all();	
		SIMULATE_I2C_SCK_LOW;
		delay_simulate_i2c_half();
	}
	delay_simulate_i2c_half();
	SIMULATE_I2C_DATA_HIGH;      //release DATA-line,the receiver send ACK(low) for response
	SIMULATE_I2C_DATA_IN;
	delay_simulate_i2c_half();
	SIMULATE_I2C_SCK_HIGH;     //clk #9 for ack 
	delay_simulate_i2c_all();
	error=SIMULATE_I2C_DATA;                       //check ack (DATA will be pulled down by SHT11)
	delay_simulate_i2c_half();
	SIMULATE_I2C_SCK_LOW; 
	delay_simulate_i2c_half();
	SIMULATE_I2C_DATA_OUT;
	delay_simulate_i2c_half();

	return error;                     //error=1 in case of no acknowledge
}


/*******************************************************************************
  * @brief simulate_i2c_read_byte()
  * @param  ack
  * @retval val
	******************************************************************************
	 @attention I2C 读单字节 从高位到低位 
							ack:1响应
									0不响应
	 *****************************************************************************
  */
uint8_t simulate_i2c_read_byte(uint8_t ack)
{ 
	uint8_t i,val=0;
	SIMULATE_I2C_DATA_HIGH;                          
	SIMULATE_I2C_DATA_IN;
	for (i=0x80;i>0;i >>= 1)             
	{ 
		SIMULATE_I2C_SCK_HIGH;                        
		delay_simulate_i2c_all();
		if (SIMULATE_I2C_DATA) 
			val=(val | i);         
		SIMULATE_I2C_SCK_LOW;  					 
		delay_simulate_i2c_all();
	}
	SIMULATE_I2C_DATA_OUT;
	//DATA=!ack;                       
	if(!ack) 
	{
		SIMULATE_I2C_DATA_HIGH;
	}
	else 
	{
		SIMULATE_I2C_DATA_LOW;
	}
	SIMULATE_I2C_SCK_HIGH;                            
	delay_simulate_i2c_all();
	SIMULATE_I2C_SCK_LOW;						    
	SIMULATE_I2C_DATA_HIGH;
	delay_simulate_i2c_all();
	return val;
}

/*******************************************************************************
  * @brief simulate_i2c_write_single_byte()
  * @param  addr，cmd，value
  * @retval 
	******************************************************************************
	 @attention I2C 写单个数据
							addr:	从机地址+写位
							cmd:	指令
							value:数据
	 *****************************************************************************
  */
void simulate_i2c_write_single_byte(uint8_t addr, uint8_t cmd, uint8_t value)
{
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr);
	simulate_i2c_write_byte(cmd);
	simulate_i2c_write_byte(value);
	simulate_i2c_transstop();
}
/*******************************************************************************
  * @brief simulate_i2c_write_buff()
  * @param  addr，cmd，*buff，len
  * @retval 
	******************************************************************************
	 @attention I2C 写多个数据
							addr:	从机地址+写位
							cmd:	指令
							*buff:数据指针
							len:  长度
	 *****************************************************************************
  */
void simulate_i2c_write_buff(uint8_t addr, uint8_t cmd, uint8_t *buff, uint8_t len)
{
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr);
	simulate_i2c_write_byte(cmd);
	while(len--)
	{
		simulate_i2c_write_byte(*buff);
		buff++;
	}
	simulate_i2c_transstop();
}
/*******************************************************************************
  * @brief simulate_i2c_read_single_byte()
  * @param  addr，cmd
  * @retval data
	******************************************************************************
	 @attention I2C 读单个数据
							addr:	从机地址
							cmd:	指令
	 *****************************************************************************
  */
uint8_t simulate_i2c_read_single_byte(uint8_t addr, uint8_t cmd)
{
	uint8_t data =0;
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr);
	simulate_i2c_write_byte(cmd);
	simulate_i2c_transstart();
	addr |= 0x01;
	simulate_i2c_write_byte(addr);
	data = simulate_i2c_read_byte(SIMULATE_I2C_SEND_NACK);
	simulate_i2c_transstop();

	return data;
}
/*******************************************************************************
  * @brief simulate_i2c_read_mult_byte()
  * @param  addr，cmd，*buff，len
  * @retval *buff
	******************************************************************************
	 @attention I2C 读多个数据
							addr:	从机地址
							cmd:	指令
							*buff:数据指针
							len:  长度
	 *****************************************************************************
  */
void simulate_i2c_read_mult_byte(uint8_t addr, uint8_t *buff, uint8_t len)
{
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr|0x01);
	while(len--)
	{
		if(len)
		*buff++ = simulate_i2c_read_byte(SIMULATE_I2C_SEND_ACK);
		else
			*buff++ = simulate_i2c_read_byte(SIMULATE_I2C_SEND_NACK);
	}
	simulate_i2c_transstop();
}
/*******************************************************************************
  * @brief simulate_i2c_write_cmd()
  * @param  addr，cmd
  * @retval 
	******************************************************************************
	 @attention I2C 写单个指令
							addr:	从机地址+写位
							cmd:	指令
	 *****************************************************************************
  */
void simulate_i2c_write_cmd(uint8_t addr, uint8_t cmd)
{
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr);
	simulate_i2c_write_byte(cmd);
	simulate_i2c_transstop();
}
/*******************************************************************************
  * @brief simulate_i2c_write_bytes()
  * @param  buff，len
  * @retval 
	******************************************************************************
	 @attention I2C 写数组的数据(mlx90614用到)
							*buff:数据指针
							len:  长度
	 *****************************************************************************
  */
void simulate_i2c_write_bytes(uint8_t *buff, uint16_t len)
{
	
	uint16_t i;
	uint16_t num;
	write_again:
	i=0;
	num=len;
	simulate_i2c_transstart();
	while(num--)
	{
		if(simulate_i2c_write_byte(buff[i++]))
		{
			simulate_i2c_transstop();
			goto write_again;
		}
	}
	
	simulate_i2c_transstop();
}
/*******************************************************************************
  * @brief simulate_i2c_read_value_from_addr()
  * @param  addr，cmd，*value
  * @retval *value
	******************************************************************************
	 @attention I2C 写数组的数据
							addr:	从机地址+写位
							cmd:	指令
							*value:数据指针
	 *****************************************************************************
  */
void simulate_i2c_read_value_from_addr(uint8_t addr, uint8_t cmd, uint8_t *value)
{
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr);
	simulate_i2c_write_byte(cmd);
	simulate_i2c_transstart();
	simulate_i2c_write_byte(addr|0x01);
	*value = simulate_i2c_read_byte(SIMULATE_I2C_SEND_NACK);
	simulate_i2c_transstop();
}
/*******************************************************************************
  * @brief simulate_i2c_read_buff_from_addr()
  * @param  addr，cmd，*buff，len
  * @retval *buff，error
	******************************************************************************
	 @attention I2C 写数组的数据(mlx90614用到)
							addr:	从机地址+写位
							cmd:	指令
							*buff:数据指针
							len:  长度
							error：
							0：成功通信
							2：写从地址+写位无响应
							3：写从指令无响应
							4：写从地址+读位无响应
	 *****************************************************************************
  */
uint8_t simulate_i2c_read_buff_from_addr(uint8_t addr, uint8_t cmd, uint8_t *buff, uint16_t len)
{
	uint16_t i = 0;
	uint8_t error=0;
	simulate_i2c_transstart();
	if(simulate_i2c_write_byte(addr))
	{
		error=2;
		goto return_error;
	}
	if(simulate_i2c_write_byte(cmd))
	{
		error=3;
		goto return_error;
	}
	simulate_i2c_transstart();
	if(simulate_i2c_write_byte(addr|0x01))
	{
		error=4;
		goto return_error;
	}
	for(i=0; i<len; i++)
	{
		buff[i] = simulate_i2c_read_byte(SIMULATE_I2C_SEND_ACK);
	}
	return_error:
	simulate_i2c_transstop();
	return error;
}
